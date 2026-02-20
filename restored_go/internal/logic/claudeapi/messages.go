package claudeapi

import (
	"fmt"
	"io"
	"net/http"
	"net/textproto"
	"strings"
	"time"

	"kiro2api/internal/common"
	"kiro2api/internal/model"
	"kiro2api/internal/proxy"

	"github.com/gogf/gf/v2/frame/gins"
	"github.com/gogf/gf/v2/net/ghttp"
)

// ChatController.Messages is the main /v1/messages endpoint handler.
// It reads the request body, extracts session info, obtains an account
// from the concurrency pool, and proxies the request to Anthropic with
// retry logic and streaming response forwarding.
//
// Decompiled from: claudeapi.ChatController.Messages @ 0x139ce00 (6240B)
//
// Flow:
//  1. Read request body via io.ReadAll
//  2. On read error -> return JSON error {code: "error", message: ..., data: ...}
//  3. Log auth header and body length/model info
//  4. Extract session ID from session key
//  5. Create retry config, get concurrency manager
//  6. Retry loop:
//     a. Check concurrentSessionMap for existing in-flight request
//     b. Get account with slot from concurrency manager
//     c. On slot error -> log and retry with sleep
//     d. Load Gate credentials for the account
//     e. Call response handler to proxy the request
//     f. Inner retry loop over response handler attempts:
//        - 2xx -> success, stream response back
//        - 401/403/429 -> retryable, call HandleErrorResponse, clear session map
//        - 5xx -> retryable with sleep
//        - other 4xx -> non-retryable, break
//     g. On retryable error with account marked bad:
//        - Log warning, delete from session map
//        - Launch goroutine to handle error response asynchronously
//        - Release concurrency slot
//     h. On success (response available):
//        - Defer body close
//        - If 2xx and session key present -> store usage in session map
//        - Release concurrency slot, release account
//        - Copy upstream response headers
//        - Write status code
//        - Stream body in 128KB chunks, buffering error body if status >= 400
//        - Launch goroutine for post-response processing (error handling)
func (ctrl *ChatController) Messages(r *ghttp.Request) {
	ctx := r.Context()

	// xdZLD7_Ho6qQX -- likely an auth/rate-limit middleware check
	// Extracted from the first call after getting context
	authHeader := r.GetHeader("Authorization")

	// Read entire request body
	bodyBytes, err := io.ReadAll(r.Request.Body)
	if err != nil {
		r.Response.WriteJson(common.ErrorResponse{
			Code:    "error",
			Message: "read body failed",
			Data:    map[string]interface{}{},
		})
		return
	}

	// Log auth header
	logger := gins.Log()
	logger.Infof(ctx, "[ClaudeApi] Messages auth header: %s", authHeader)

	// Log body length and detect model
	bodyStr := string(bodyBytes)
	modelIdx := indexOfModel(bodyStr)
	logger.Infof(ctx, "[ClaudeApi] Messages request body length=%d, hasModel=%v", len(bodyBytes), modelIdx >= 0)

	// If body is small (< 2000 bytes), log it entirely for debugging
	if len(bodyBytes) < 2000 {
		logger.Infof(ctx, "[ClaudeApi] Messages body: %s", bodyStr)
	}

	// Extract session ID from the session key (if present)
	sessionID := ExtractSessionId(bodyBytes)

	// Create retry configuration
	retryConfig := common.NewRetryConfig()

	// Get concurrency manager for account slot allocation
	concurrencyMgr := GetConcurrencyManager()

	var lastErr error
	var lastErrAccount interface{}

	// === Main retry loop ===
	for attempt := int64(0); attempt < retryConfig.MaxRetries; attempt++ {

		// Check if there's already an in-flight request for this session
		var existingAccount *model.ClaudeApiAccount
		if sessionID != "" {
			if val, ok := concurrentSessionMap.Load(sessionID); ok {
				if acct, ok := val.(*model.ClaudeApiAccount); ok {
					existingAccount = acct
				}
			}
		}

		// Get an account with a concurrency slot
		acctIface, releaseSlot, releaseAccount, slotErr := concurrencyMgr.GetAccountWithSlot(
			ctx,
			retryConfig.TimeoutDuration,
			existingAccount,
		)

		if slotErr != nil {
			// Failed to get account slot -- log and retry
			logger.Errorf(ctx, "[ClaudeApi] Messages get account slot error: %v, attempt=%d", slotErr, attempt)
			releaseSlot()
			releaseAccount()
			lastErr = slotErr
			lastErrAccount = nil
			continue
		}

		account, _ := acctIface.(*model.ClaudeApiAccount)

		if existingAccount != nil && slotErr != nil {
			// Had an existing session but couldn't get slot -- clean up session map
			concurrentSessionMap.Delete(sessionID)
			lastErr = slotErr
			lastErrAccount = nil
			continue
		}

		// Load Gate-encrypted credentials for this account
		loadErr := account.LoadGateCredentials()
		logger.Infof(ctx, "[ClaudeApi] Messages attempt=%d, account=%d, maxRetries=%d",
			attempt, account.ID, retryConfig.MaxRetries)

		if loadErr != 0 {
			account.LoadGateCredentials()
		}

		// Get the response handler (sClaudeApi singleton)
		svc := New()
		if svc == nil {
			releaseSlot()
			panic("sClaudeApi service is nil")
		}

		// Call the upstream proxy -- inner retry loop
		var resp *proxy.Response
		retryable := false
		var innerErr error
		var innerErrAccount interface{}

		for innerAttempt := int64(0); innerAttempt < retryConfig.MaxRetries; innerAttempt++ {
			resp = svc.SendChatRequest(ctx, account, bodyBytes)

			if resp == nil {
				// No response -- error case
				if innerAttempt < retryConfig.MaxRetries-1 {
					time.Sleep(retryConfig.RetrySleep)
				}
				innerErr = nil
				innerErrAccount = nil
				continue
			}

			statusCode := resp.StatusCode

			// 2xx success -- break out
			if statusCode >= 200 && statusCode < 300 {
				break
			}

			// 401 (0x191) -- Unauthorized, retryable
			if statusCode == 401 {
				retryable = true
			} else if statusCode == 403 { // 0x193 -- Forbidden, retryable
				retryable = true
			} else if statusCode == 429 { // 0x1AD -- Rate Limited, retryable
				retryable = true
			} else {
				retryable = false
			}

			if retryable {
				// Call HandleErrorResponse to update account status
				svc.HandleErrorResponse(resp)
				innerErr = nil
				innerErrAccount = nil
				resp = nil
				break
			}

			// 5xx -- retryable with sleep
			if statusCode >= 500 && innerAttempt < retryConfig.MaxRetries-1 {
				svc.HandleErrorResponse(resp)
				time.Sleep(retryConfig.RetrySleep)
				innerErrAccount = nil
				innerErr = nil
				continue
			}

			// Other 4xx or last attempt -- non-retryable
			innerErr = nil
			innerErrAccount = nil
			break
		}

		lastErr = innerErr
		lastErrAccount = innerErrAccount

		if retryable {
			// Account was marked bad (401/403/429)
			logger.Warningf(ctx, "[ClaudeApi] Messages retryable error, account=%d, err=%v",
				account.ID, lastErr)

			// Remove from concurrent session map
			if sessionID != "" {
				concurrentSessionMap.Delete(sessionID)
			}

			// Launch async goroutine to handle the error response
			// (e.g., update account status, rate limit recovery)
			// Decompiled: runtime_newproc with closure referencing account + status
			if resp != nil {
				statusCode := resp.StatusCode
				go func(acct *model.ClaudeApiAccount, code int) {
					svc.handleApiErrorResponse(acct, code)
				}(account, statusCode)
			}

			releaseSlot()
			continue
		}

		// We have a response (success or non-retryable error)
		if resp != nil {
			// Defer close of upstream response body
			defer resp.Close()

			// On 2xx success with session key -- store in concurrent session map
			if resp.StatusCode < 300 && sessionID != "" {
				concurrentSessionMap.Store(sessionID, account)
			}

			// Release concurrency resources
			releaseSlot()
			releaseAccount()

			// Copy upstream response headers to downstream
			if resp.Header != nil {
				downstreamHeader := r.Response.RawWriter().Header()
				for key, values := range resp.Header {
					canonicalKey := textproto.CanonicalMIMEHeaderKey(key)
					for _, v := range values {
						downstreamHeader.Add(canonicalKey, v)
					}
				}
			}

			// Write status code
			r.Response.RawWriter().WriteHeader(resp.StatusCode)

			// Stream body in 128KB (0x20000) chunks
			if resp.RawBody != nil {
				var errorBodyBuf []byte
				buf := make([]byte, 0x20000) // 128KB buffer
				for {
					n, readErr := resp.RawBody.Read(buf)
					if n > 0 {
						r.Response.RawWriter().Write(buf[:n])

						// Flush if the response supports it
						if flusher, ok := r.Response.RawWriter().(http.Flusher); ok {
							flusher.Flush()
						}

						// If status >= 400, also buffer the error body
						if resp.StatusCode >= 400 {
							errorBodyBuf = append(errorBodyBuf, buf[:n]...)
						}
					}

					if readErr != nil {
						break
					}
				}

				// Post-response processing goroutine
				// If status >= 400, launch async error handler with buffered body
				if resp.StatusCode >= 400 {
					go func(acct *model.ClaudeApiAccount, respObj *proxy.Response, errBody []byte) {
						svc.handleApiErrorResponse(acct, respObj.StatusCode)
					}(account, resp, errorBodyBuf)
				}
			}

			return
		}

		// No response at all -- release and continue retry
		releaseSlot()
		releaseAccount()
	}

	// All retries exhausted
	var errMsg string
	if lastErrAccount != nil {
		if acct, ok := lastErrAccount.(*model.ClaudeApiAccount); ok {
			errMsg = fmt.Sprintf("account %d: %v", acct.ID, lastErr)
		}
	}
	if errMsg == "" {
		errMsg = "all retries exhausted"
	}

	logger.Warningf(ctx, "[ClaudeApi] Messages all retries exhausted: %s, body=%s", errMsg, string(bodyBytes))

	// FtTgl3_ZQHMyB7 -- likely a metrics/telemetry call
	r.Response.WriteJson(common.ErrorResponse{
		Code:    "error",
		Message: "upstream error",
		Data: map[string]interface{}{
			"message": errMsg,
		},
	})
}

// indexOfModel searches for a model identifier in the request body string.
// Uses internal/stringslite.Index with length 10 (likely "model\":\"" pattern).
func indexOfModel(body string) int {
	return strings.Index(body, "\"model\"")
}

// ChatController holds references for the Claude API chat endpoints.
type ChatController struct {
	svc *sClaudeApi
}
