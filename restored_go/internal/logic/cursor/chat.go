package cursor

import (
	"bytes"
	"context"
	"encoding/json"
	"fmt"
	"io"
	"log"
	"net/http"
	"sync"
	"time"

	"kiro2api/internal/common"
	"kiro2api/internal/logic"
	"kiro2api/internal/logic/cursor/currpc"
	"kiro2api/internal/model"

	"github.com/gogf/gf/v2/frame/gins"
	"github.com/gogf/gf/v2/net/ghttp"
	"github.com/google/uuid"
)

// ============================================================================
// Concurrency Management
// ============================================================================

var (
	cursorConcurrencyMgr     *logic.AccountConcurrencyManager
	cursorConcurrencyMgrOnce sync.Once

	// concurrentSessionMap tracks in-flight sessions to enable session affinity.
	// Key: session ID, Value: *model.CursorAccount
	concurrentSessionMap sync.Map
)

// GetCursorConcurrencyManager returns the global concurrency manager for Cursor accounts.
// Symbol: kiro2api/internal/logic/cursor.GetConcurrencyManager (128B @ 0x17f5fc0)
func GetCursorConcurrencyManager() *logic.AccountConcurrencyManager {
	cursorConcurrencyMgrOnce.Do(func() {
		cursorConcurrencyMgr = logic.NewAccountConcurrencyManager("cursor")
	})
	return cursorConcurrencyMgr
}

// ============================================================================
// Chat Controller
// ============================================================================

// CursorChatController holds references for the Cursor chat endpoints.
type CursorChatController struct {
	svc *sCursor
}

// NewCursorChatController creates a new CursorChatController.
func NewCursorChatController() *CursorChatController {
	return &CursorChatController{
		svc: New(),
	}
}

// ============================================================================
// ChatCompletions — Main Endpoint Handler
// ============================================================================

// ChatCompletions is the main /v1/chat/completions endpoint handler for the Cursor channel.
// Symbol: kiro2api/internal/logic/cursor.(*sCursor).ChatCompletions (6912B @ 0x17f8200)
//
// This is the largest handler function. From the symbol table:
//   - ChatCompletions (6912B @ 0x17f8200): main handler
//   - ChatCompletions.func1 (256B @ 0x17f9e60): deferred cleanup
//   - ChatCompletions.func2 (1024B @ 0x17f9f60): async error handler goroutine
//   - ChatCompletions.func3 (512B @ 0x17fa060): post-response processing
//
// Flow (mirrors claudeapi.Messages pattern):
//  1. Read request body
//  2. Extract session ID for affinity
//  3. Retry loop:
//     a. Get account with concurrency slot
//     b. Load Gate credentials
//     c. Check/refresh token
//     d. Build Cursor Connect-RPC request (buildCursorRequest)
//     e. Create HTTP request with headers (newConnectRequest)
//     f. Send request via uTLS client
//     g. Handle response:
//        - 2xx → stream response via SSE writer
//        - 401/403/429 → retryable, update account status
//        - 5xx → retryable with backoff
//        - other 4xx → non-retryable
//  4. On success: convert Connect-RPC stream to OpenAI SSE format
//  5. On all retries exhausted: return error JSON
func (ctrl *CursorChatController) ChatCompletions(r *ghttp.Request) {
	ctx := r.Context()
	logger := gins.Log()

	// Read request body
	bodyBytes, err := io.ReadAll(r.Request.Body)
	if err != nil {
		r.Response.WriteJson(common.ErrorResponse{
			Code:    "error",
			Message: "read body failed",
			Data:    map[string]interface{}{},
		})
		return
	}

	// Log request info
	authHeader := r.GetHeader("Authorization")
	logger.Infof(ctx, "[Cursor] ChatCompletions auth=%s, bodyLen=%d", authHeader, len(bodyBytes))

	// Extract session ID for session affinity
	sessionID := ExtractSessionId(bodyBytes)

	// Parse model from request for SSE writer
	var reqPeek struct {
		Model  string `json:"model"`
		Stream bool   `json:"stream"`
	}
	json.Unmarshal(bodyBytes, &reqPeek)

	// Create retry configuration
	retryConfig := common.NewRetryConfig()

	// Get concurrency manager
	concurrencyMgr := GetCursorConcurrencyManager()

	svc := New()
	var lastErr error

	// === Main retry loop ===
	for attempt := int64(0); attempt < retryConfig.MaxRetries; attempt++ {

		// Check for existing session affinity
		var existingAccount *model.CursorAccount
		if sessionID != "" {
			if val, ok := concurrentSessionMap.Load(sessionID); ok {
				if acct, ok := val.(*model.CursorAccount); ok {
					existingAccount = acct
				}
			}
		}

		// Get account with concurrency slot
		acctIface, releaseSlot, releaseAccount, slotErr := concurrencyMgr.GetAccountWithSlot(
			ctx,
			retryConfig.TimeoutDuration,
			existingAccount,
		)

		if slotErr != nil {
			logger.Errorf(ctx, "[Cursor] ChatCompletions get slot error: %v, attempt=%d", slotErr, attempt)
			releaseSlot()
			releaseAccount()
			lastErr = slotErr
			continue
		}

		account, _ := acctIface.(*model.CursorAccount)

		// Load Gate-encrypted credentials
		loadErr := account.LoadGateCredentials()
		if loadErr != 0 {
			account.LoadGateCredentials()
		}

		logger.Infof(ctx, "[Cursor] ChatCompletions attempt=%d, account=%d", attempt, account.ID)

		// Check and refresh token if needed
		if !svc.CheckToken(account) {
			logger.Warningf(ctx, "[Cursor] ChatCompletions token invalid for account %d, refreshing", account.ID)
			if refreshErr := svc.RefreshToken(account); refreshErr != nil {
				logger.Errorf(ctx, "[Cursor] ChatCompletions token refresh failed: %v", refreshErr)
				releaseSlot()
				releaseAccount()
				lastErr = refreshErr

				// Clean up session map
				if sessionID != "" {
					concurrentSessionMap.Delete(sessionID)
				}
				continue
			}
		}

		// Build Cursor Connect-RPC protobuf request
		cursorReq, buildErr := svc.buildCursorRequest(account, bodyBytes)
		if buildErr != nil {
			logger.Errorf(ctx, "[Cursor] ChatCompletions build request error: %v", buildErr)
			releaseSlot()
			releaseAccount()
			lastErr = buildErr
			continue
		}

		// Serialize protobuf request
		protoBytes, marshalErr := marshalCursorRequest(cursorReq)
		if marshalErr != nil {
			logger.Errorf(ctx, "[Cursor] ChatCompletions marshal error: %v", marshalErr)
			releaseSlot()
			releaseAccount()
			lastErr = marshalErr
			continue
		}

		// Frame with Connect protocol prefix
		framedBody := encodeBytes2Base64(protoBytes)

		// Create HTTP request with all Cursor headers
		httpReq, reqErr := svc.newConnectRequest(account, streamChatPath, framedBody, "", "")
		if reqErr != nil {
			logger.Errorf(ctx, "[Cursor] ChatCompletions create request error: %v", reqErr)
			releaseSlot()
			releaseAccount()
			lastErr = reqErr
			continue
		}

		// Set the body on the request
		httpReq.Body = io.NopCloser(bytes.NewReader(framedBody))
		httpReq.ContentLength = int64(len(framedBody))

		// Send request via uTLS client
		client := NewCursorClient(account)
		resp, doErr := client.Do(httpReq)
		if doErr != nil {
			logger.Errorf(ctx, "[Cursor] ChatCompletions request failed: %v", doErr)
			releaseSlot()
			releaseAccount()
			lastErr = doErr
			continue
		}

		statusCode := resp.StatusCode

		// Handle non-2xx responses
		if statusCode < 200 || statusCode >= 300 {
			resp.Body.Close()

			retryable := false
			switch {
			case statusCode == 401:
				// Unauthorized — invalidate token, retryable
				logger.Warningf(ctx, "[Cursor] 401 Unauthorized for account %d", account.ID)
				account.AccessToken = ""
				account.Status = "invalid"
				retryable = true

			case statusCode == 403:
				// Forbidden — account suspended, retryable
				logger.Warningf(ctx, "[Cursor] 403 Forbidden for account %d", account.ID)
				account.Status = "suspended"
				retryable = true

			case statusCode == 429:
				// Rate limited — retryable
				logger.Warningf(ctx, "[Cursor] 429 Rate Limited for account %d", account.ID)
				account.Status = "rate_limited"
				retryable = true

			case statusCode >= 500:
				// Server error — retryable with backoff
				logger.Warningf(ctx, "[Cursor] %d Server Error for account %d", statusCode, account.ID)
				retryable = true
				time.Sleep(retryConfig.RetrySleep)

			default:
				// Other 4xx — non-retryable
				retryable = false
			}

			if retryable {
				if sessionID != "" {
					concurrentSessionMap.Delete(sessionID)
				}

				// Async error handling goroutine
				// Symbol: ChatCompletions.func2 (1024B @ 0x17f9f60)
				go func(acct *model.CursorAccount, code int) {
					svc.handleCursorErrorResponse(acct, code)
				}(account, statusCode)

				releaseSlot()
				continue
			}

			// Non-retryable error — return error to client
			releaseSlot()
			releaseAccount()

			r.Response.WriteJson(common.ErrorResponse{
				Code:    "error",
				Message: fmt.Sprintf("upstream error: %d", statusCode),
				Data:    map[string]interface{}{},
			})
			return
		}

		// === 2xx Success — Stream response ===
		defer resp.Body.Close()

		// Store session affinity
		if sessionID != "" {
			concurrentSessionMap.Store(sessionID, account)
		}

		// Release concurrency resources
		releaseSlot()
		releaseAccount()

		// Stream the Connect-RPC response as OpenAI SSE
		completionID := fmt.Sprintf("chatcmpl-%s", uuid.NewString()[:8])
		sseWriter := NewCursorSSEWriter(r.Response.Writer, reqPeek.Model, completionID)

		streamErr := svc.handleCursorStreamResponse(ctx, resp, sseWriter)
		if streamErr != nil {
			logger.Errorf(ctx, "[Cursor] ChatCompletions stream error: %v", streamErr)
			sseWriter.WriteError(streamErr.Error())
		}

		// Post-response processing goroutine
		// Symbol: ChatCompletions.func3 (512B @ 0x17fa060)
		go func(acct *model.CursorAccount) {
			// Toggle token if needed (usage tracking, rotation)
			svc.toggleCursorToken(acct)
		}(account)

		return
	}

	// All retries exhausted
	logger.Warningf(ctx, "[Cursor] ChatCompletions all retries exhausted: %v", lastErr)

	r.Response.WriteJson(common.ErrorResponse{
		Code:    "error",
		Message: "upstream error",
		Data: map[string]interface{}{
			"message": fmt.Sprintf("all retries exhausted: %v", lastErr),
		},
	})
}

// ============================================================================
// Stream Response Handler
// ============================================================================

// handleCursorStreamResponse reads the Connect-RPC streaming response and
// converts it to OpenAI SSE format via the CursorSSEWriter.
// Symbol: kiro2api/internal/logic/cursor.(*sCursor).handleCursorStreamResponse (3072B @ 0x17f9400)
//
// The 3072B size indicates a complex read loop with protobuf parsing and
// event type dispatching.
//
// Flow:
//  1. Read chunks from response body in a loop
//  2. Parse each chunk via ParseCursorStreamChunk
//  3. For each event, dispatch to the appropriate SSE writer method:
//     - "text" → WriteTextDelta
//     - "thinking" → WriteThinkingDelta
//     - "tool_call" → WriteToolCallDelta (start)
//     - "tool_call_args" → WriteToolCallDelta (arguments)
//     - "stop" → WriteStop
//     - "usage" → SetPromptTokens
//     - "error" → WriteError
func (s *sCursor) handleCursorStreamResponse(
	ctx context.Context,
	resp *http.Response,
	sseWriter *CursorSSEWriter,
) error {
	logger := gins.Log()

	// Read buffer — 128KB like claudeapi
	buf := make([]byte, 0x20000)
	var accumulated []byte

	for {
		n, readErr := resp.Body.Read(buf)
		if n > 0 {
			accumulated = append(accumulated, buf[:n]...)

			// Try to parse complete frames from accumulated data
			for len(accumulated) >= 5 {
				// Check if we have a complete frame
				frameLen := uint32(accumulated[1])<<24 | uint32(accumulated[2])<<16 |
					uint32(accumulated[3])<<8 | uint32(accumulated[4])
				totalLen := int(frameLen) + 5

				if len(accumulated) < totalLen {
					break // incomplete frame, wait for more data
				}

				// Extract complete frame
				frame := accumulated[:totalLen]
				accumulated = accumulated[totalLen:]

				// Parse the frame into events
				events, parseErr := ParseCursorStreamChunk(frame)
				if parseErr != nil {
					logger.Warningf(ctx, "[Cursor] stream parse error: %v", parseErr)
					continue
				}

				// Dispatch events to SSE writer
				for _, event := range events {
					switch event.Type {
					case "text":
						sseWriter.WriteTextDelta(event.Text)

					case "thinking":
						sseWriter.WriteThinkingDelta(event.Text)

					case "tool_call":
						sseWriter.WriteToolCallDelta(event.ToolCallID, event.FunctionName, "")

					case "tool_call_args":
						sseWriter.WriteToolCallDelta("", "", event.Arguments)

					case "stop":
						sseWriter.WriteStop(event.StopReason)
						return nil

					case "usage":
						sseWriter.SetPromptTokens(event.PromptTokens)

					case "error":
						sseWriter.WriteError(event.ErrorMessage)
						return fmt.Errorf("upstream error: %s", event.ErrorMessage)
					}
				}
			}
		}

		if readErr != nil {
			if readErr == io.EOF {
				// End of stream — send stop if not already sent
				sseWriter.WriteStop("stop")
				return nil
			}
			return fmt.Errorf("read error: %w", readErr)
		}
	}
}

// ============================================================================
// Token Management
// ============================================================================

// CheckToken validates whether the account's token is still valid.
// Symbol: kiro2api/internal/logic/cursor.(*sCursor).CheckToken (768B @ 0x17ff500)
//
// Checks JWT expiry and validates the token structure.
func (s *sCursor) CheckToken(account *model.CursorAccount) bool {
	if account == nil || account.AccessToken == "" {
		return false
	}

	// Check if token has expired
	if !account.TokenExpiresAt.IsZero() && time.Now().Before(account.TokenExpiresAt) {
		return true
	}

	// Check JWT expiry directly
	return !IsTokenExpired(account.AccessToken)
}

// RefreshToken refreshes the Cursor account's access token.
// Symbol: kiro2api/internal/logic/cursor.(*sCursor).RefreshToken (1536B @ 0x17ff800)
//
// Delegates to refreshWorkOSToken for the actual refresh flow.
func (s *sCursor) RefreshToken(account *model.CursorAccount) error {
	if account == nil {
		return fmt.Errorf("nil account")
	}

	err := s.refreshWorkOSToken(account)
	if err != nil {
		log.Printf("[Cursor] RefreshToken failed for account %d: %v", account.ID, err)
		return err
	}

	// Persist updated credentials
	account.EncryptAndSetCredentials()

	log.Printf("[Cursor] RefreshToken success for account %d", account.ID)
	return nil
}

// toggleCursorToken performs post-request token management.
// Symbol: kiro2api/internal/logic/cursor.(*sCursor).toggleCursorToken (512B @ 0x17ffa00)
//
// Called after a successful request to:
//   - Track usage count
//   - Rotate to a different token if usage threshold is reached
//   - Update last-used timestamp
func (s *sCursor) toggleCursorToken(account *model.CursorAccount) {
	if account == nil {
		return
	}

	// Update last used timestamp
	account.LastUsedAt = time.Now()

	// Increment usage counter
	account.UsageCount++

	// Check if we should rotate the token
	// (e.g., after N requests, switch to a different account)
	if account.MaxUsagePerToken > 0 && account.UsageCount >= account.MaxUsagePerToken {
		log.Printf("[Cursor] toggleCursorToken: account %d reached usage limit %d, marking for rotation",
			account.ID, account.MaxUsagePerToken)
		account.NeedsRotation = true
	}
}

// ============================================================================
// Error Response Handler
// ============================================================================

// handleCursorErrorResponse handles error responses from the Cursor API.
// Symbol: kiro2api/internal/logic/cursor.(*sCursor).handleCursorErrorResponse (1792B @ 0x17ffc00)
//
// Similar to claudeapi.handleApiErrorResponse but with Cursor-specific handling.
func (s *sCursor) handleCursorErrorResponse(account *model.CursorAccount, statusCode int) {
	if account == nil {
		return
	}

	switch {
	case statusCode == 401:
		// Unauthorized — clear token, attempt refresh
		log.Printf("[Cursor] handleCursorErrorResponse: 401 for account %d, invalidating", account.ID)
		account.Status = "invalid"
		account.AccessToken = ""

		// Attempt background refresh
		_ = s.refreshWorkOSToken(account)

	case statusCode == 403:
		// Forbidden — account suspended
		log.Printf("[Cursor] handleCursorErrorResponse: 403 for account %d, suspended", account.ID)
		account.Status = "suspended"

	case statusCode == 429:
		// Rate limited
		log.Printf("[Cursor] handleCursorErrorResponse: 429 for account %d, rate limited", account.ID)
		account.Status = "rate_limited"

	case statusCode >= 500:
		// Server error — don't change account status
		log.Printf("[Cursor] handleCursorErrorResponse: %d server error for account %d", statusCode, account.ID)

	default:
		log.Printf("[Cursor] handleCursorErrorResponse: unhandled status %d for account %d", statusCode, account.ID)
	}
}

// ============================================================================
// Protobuf Marshaling Placeholder
// ============================================================================

// marshalCursorRequest serializes the StreamUnifiedChatRequestWithTools to protobuf bytes.
// This delegates to the currpc package's proto.Marshal.
func marshalCursorRequest(req *currpc.StreamUnifiedChatRequestWithTools) ([]byte, error) {
	return currpc.Marshal(req)
}
