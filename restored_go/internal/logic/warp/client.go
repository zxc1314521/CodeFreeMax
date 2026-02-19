package warp

// client.go — HTTP client, ChatCompletions entry point, and GraphQL operations.
//
// This file contains the main entry points for the Warp channel:
//   - ChatCompletions      (0x170e5a0, 3072B)  — Main chat completion handler
//   - clientForAccount     (0x1714a80, 1536B)   — Create HTTP client per account
//   - doStreamRequest      (0x1714080, 2560B)   — Execute streaming HTTP request
//   - doCompleteRequest    (0x1713800, 2048B)   — Execute non-streaming request
//   - GetQuotaInfo         (0x1710e00, 2848B)   — GraphQL quota query
//   - RefundCredits        (0x1711800, 3776B)   — GraphQL refund operation
//   - handleStreamResponse (0x1715200, 2816B)   — Process streaming response
//   - retryWithRefresh     (0x1714e00, 1024B)   — Retry with token refresh
//
// ChatCompletions flow:
//   1. Get account from queue (round-robin)
//   2. Ensure valid auth token (refresh if expired)
//   3. Build protobuf request payload
//   4. Send HTTP request to Warp API
//   5. Process response (streaming or complete)
//   6. Convert to OpenAI-compatible format
//   7. Track quota usage

import (
	"bytes"
	"context"
	"encoding/json"
	"fmt"
	"io"
	"net/http"
	"strings"
	"sync"
	"time"

	"github.com/gogf/gf/v2/frame/gins"
	"github.com/gogf/gf/v2/net/gclient"
)

// ============================================================================
// WarpClient — Per-account HTTP client
// ============================================================================

// WarpClient wraps an HTTP client with Warp-specific configuration.
type WarpClient struct {
	client    *gclient.Client
	account   *WarpAccount
	mu        sync.Mutex
}

// clientForAccount creates or retrieves an HTTP client for the given account.
// From decompiled: kiro2api_internal_logic_warp_sWarp_clientForAccount (0x1714a80, 1536B)
//
// Sets up:
//   - Base URL: WarpAPIBase
//   - Headers: Authorization, X-Device-ID, X-App-Version, Content-Type
//   - Timeout: 300 seconds (for streaming)
//   - TLS configuration
func (s *sWarp) clientForAccount(account *WarpAccount) *WarpClient {
	client := gclient.New()

	// Set timeout for streaming
	client.SetTimeout(300 * time.Second)

	// Set headers
	// From decompiled: multiple SetHeader calls with string constants
	client.SetHeader("Authorization", fmt.Sprintf("Bearer %s", account.IDToken))
	client.SetHeader("X-Device-ID", account.DeviceID)
	client.SetHeader("X-App-Version", WarpClientVersion)
	client.SetHeader("Content-Type", "application/x-protobuf")
	client.SetHeader("Accept", "application/x-protobuf")
	client.SetHeader("User-Agent", fmt.Sprintf("Warp/%s", WarpClientVersion))

	// Set proxy if configured
	if s.proxy != "" {
		client.SetProxy(s.proxy)
	}

	return &WarpClient{
		client:  client,
		account: account,
	}
}

// ============================================================================
// ChatCompletions — Main entry point
// ============================================================================

// ChatCompletions handles an OpenAI-compatible chat completion request.
// From decompiled: kiro2api_internal_logic_warp_sWarp_ChatCompletions (0x170e5a0, 3072B)
//
// This is the main entry point called by the controller layer.
// Flow:
//   1. Parse the incoming request
//   2. Get an account from the queue
//   3. Ensure auth token is valid
//   4. Build the Warp protobuf request
//   5. Send to Warp API
//   6. Process and convert response
//   7. Return OpenAI-compatible response
func (s *sWarp) ChatCompletions(ctx context.Context, req *ChatCompletionRequest,
	writer http.ResponseWriter) error {

	logger := gins.Log()

	// Get account from queue
	// From decompiled: calls queue.GetAccount with channel name
	account, err := s.getAccount(ctx)
	if err != nil {
		return fmt.Errorf("get warp account: %w", err)
	}

	logger.Infof(ctx, "[Warp] Using account: %s, model: %s, stream: %v",
		account.Email, req.Model, req.Stream)

	// Ensure auth token is valid
	// From decompiled: checks token expiry, calls RefreshToken if needed
	if err := s.ensureValidToken(ctx, account); err != nil {
		return fmt.Errorf("ensure valid token: %w", err)
	}

	// Build the protobuf request
	// From decompiled: calls buildWarpRequest
	payload, err := s.buildWarpRequest(account, req.Model, req.Messages, req.Stream)
	if err != nil {
		return fmt.Errorf("build warp request: %w", err)
	}

	// Create client for this account
	warpClient := s.clientForAccount(account)

	if req.Stream {
		return s.doStreamRequest(ctx, warpClient, payload, req.Model, writer)
	}

	return s.doCompleteRequest(ctx, warpClient, payload, req.Model, writer)
}

// ============================================================================
// ensureValidToken
// ============================================================================

// ensureValidToken checks if the account's auth token is still valid
// and refreshes it if expired.
// From decompiled: token expiry check pattern in ChatCompletions
func (s *sWarp) ensureValidToken(ctx context.Context, account *WarpAccount) error {
	if account.IDToken == "" || account.TokenExpiry.Before(time.Now()) {
		logger := gins.Log()
		logger.Infof(ctx, "[Warp] Token expired for %s, refreshing...", account.Email)

		if err := s.RefreshToken(account); err != nil {
			return fmt.Errorf("refresh token: %w", err)
		}
	}
	return nil
}

// ============================================================================
// doStreamRequest — Streaming HTTP request
// ============================================================================

// doStreamRequest sends a streaming request to the Warp API and pipes
// the response as SSE events to the HTTP writer.
// From decompiled: kiro2api_internal_logic_warp_sWarp_doStreamRequest (0x1714080, 2560B)
func (s *sWarp) doStreamRequest(ctx context.Context, wc *WarpClient,
	payload []byte, model string, writer http.ResponseWriter) error {

	logger := gins.Log()

	// Build request URL
	url := fmt.Sprintf("%s%s", WarpAPIBase, WarpStreamPath)

	// Send HTTP request
	// From decompiled: gclient.Post with protobuf body
	resp, err := wc.client.Post(ctx, url, payload)
	if err != nil {
		return fmt.Errorf("warp stream request: %w", err)
	}
	defer resp.Close()

	// Check response status
	if resp.StatusCode != http.StatusOK {
		body := resp.ReadAllString()
		logger.Warningf(ctx, "[Warp] Stream request failed: status=%d, body=%s",
			resp.StatusCode, body)

		// Check if token expired (401)
		if resp.StatusCode == http.StatusUnauthorized {
			return s.retryWithRefresh(ctx, wc, payload, model, writer, true)
		}

		return fmt.Errorf("warp API error: status %d, body: %s", resp.StatusCode, body)
	}

	// Set SSE headers
	writer.Header().Set("Content-Type", "text/event-stream")
	writer.Header().Set("Cache-Control", "no-cache")
	writer.Header().Set("Connection", "keep-alive")
	writer.Header().Set("X-Accel-Buffering", "no")

	// Generate request ID
	requestID := fmt.Sprintf("warp-%d", time.Now().UnixNano())

	// Process the protobuf stream
	processor := NewStreamProcessor(resp.Body, model, requestID)
	events, errs := processor.ProcessStream()

	// Flush events to the writer
	flusher, canFlush := writer.(http.Flusher)

	for {
		select {
		case event, ok := <-events:
			if !ok {
				return nil
			}
			if _, err := fmt.Fprint(writer, event); err != nil {
				logger.Warningf(ctx, "[Warp] Error writing SSE event: %v", err)
				return nil
			}
			if canFlush {
				flusher.Flush()
			}

		case err, ok := <-errs:
			if !ok {
				return nil
			}
			if err != nil {
				logger.Warningf(ctx, "[Warp] Stream processing error: %v", err)
				return err
			}

		case <-ctx.Done():
			logger.Infof(ctx, "[Warp] Stream cancelled by client")
			return nil
		}
	}
}

// ============================================================================
// doCompleteRequest — Non-streaming HTTP request
// ============================================================================

// doCompleteRequest sends a non-streaming request to the Warp API.
// From decompiled: kiro2api_internal_logic_warp_sWarp_doCompleteRequest (0x1713800, 2048B)
func (s *sWarp) doCompleteRequest(ctx context.Context, wc *WarpClient,
	payload []byte, model string, writer http.ResponseWriter) error {

	logger := gins.Log()

	url := fmt.Sprintf("%s%s", WarpAPIBase, WarpStreamPath)

	resp, err := wc.client.Post(ctx, url, payload)
	if err != nil {
		return fmt.Errorf("warp complete request: %w", err)
	}
	defer resp.Close()

	if resp.StatusCode != http.StatusOK {
		body := resp.ReadAllString()
		logger.Warningf(ctx, "[Warp] Complete request failed: status=%d, body=%s",
			resp.StatusCode, body)

		if resp.StatusCode == http.StatusUnauthorized {
			return s.retryWithRefresh(ctx, wc, payload, model, writer, false)
		}

		return fmt.Errorf("warp API error: status %d", resp.StatusCode)
	}

	// Generate request ID
	requestID := fmt.Sprintf("warp-%d", time.Now().UnixNano())

	// Process complete response
	processor := NewStreamProcessor(resp.Body, model, requestID)
	result, err := processor.ProcessComplete()
	if err != nil {
		return fmt.Errorf("process complete response: %w", err)
	}

	// Write JSON response
	writer.Header().Set("Content-Type", "application/json")
	return json.NewEncoder(writer).Encode(result)
}

// ============================================================================
// retryWithRefresh — Retry after token refresh
// ============================================================================

// retryWithRefresh refreshes the auth token and retries the request.
// From decompiled: kiro2api_internal_logic_warp_sWarp_retryWithRefresh (0x1714e00, 1024B)
func (s *sWarp) retryWithRefresh(ctx context.Context, wc *WarpClient,
	payload []byte, model string, writer http.ResponseWriter, stream bool) error {

	logger := gins.Log()
	logger.Infof(ctx, "[Warp] Retrying with refreshed token for %s", wc.account.Email)

	// Refresh the token
	if err := s.RefreshToken(wc.account); err != nil {
		return fmt.Errorf("refresh token on retry: %w", err)
	}

	// Update client headers with new token
	wc.client.SetHeader("Authorization", fmt.Sprintf("Bearer %s", wc.account.IDToken))

	// Retry the request
	if stream {
		return s.doStreamRequest(ctx, wc, payload, model, writer)
	}
	return s.doCompleteRequest(ctx, wc, payload, model, writer)
}

// ============================================================================
// getAccount — Get account from queue
// ============================================================================

// getAccount retrieves the next available Warp account from the queue.
// From decompiled: queue.GetAccount call in ChatCompletions
func (s *sWarp) getAccount(ctx context.Context) (*WarpAccount, error) {
	// In the original binary, this calls the account queue manager
	// which does round-robin selection from the Redis-backed queue.
	// The queue key is "warp" or "warp_pro" depending on model.
	//
	// For restoration, we return the first configured account.
	s.mu.RLock()
	defer s.mu.RUnlock()

	if len(s.accounts) == 0 {
		return nil, fmt.Errorf("no warp accounts configured")
	}

	// Round-robin selection
	s.accountIdx = (s.accountIdx + 1) % len(s.accounts)
	return s.accounts[s.accountIdx], nil
}

// ============================================================================
// GraphQL Operations
// ============================================================================

// GetQuotaInfo queries the Warp GraphQL API for account quota information.
// From decompiled: kiro2api_internal_logic_warp_sWarp_GetQuotaInfo (0x1710e00, 2848B)
//
// GraphQL query:
//   query GetQuotaInfo {
//     user {
//       quota {
//         remaining
//         total
//         resetAt
//       }
//       plan {
//         name
//         tier
//       }
//     }
//   }
//
// Returns quota info including remaining credits, total, and reset time.
func (s *sWarp) GetQuotaInfo(ctx context.Context, account *WarpAccount) (*WarpQuotaInfo, error) {
	logger := gins.Log()

	// Ensure valid token
	if err := s.ensureValidToken(ctx, account); err != nil {
		return nil, err
	}

	// Build GraphQL request
	query := `query GetQuotaInfo {
		user {
			quota {
				remaining
				total
				resetAt
			}
			plan {
				name
				tier
			}
		}
	}`

	reqBody := map[string]interface{}{
		"query":     query,
		"variables": map[string]interface{}{},
	}

	bodyBytes, err := json.Marshal(reqBody)
	if err != nil {
		return nil, fmt.Errorf("marshal graphql request: %w", err)
	}

	// Send GraphQL request
	url := fmt.Sprintf("%s%s", WarpAPIBase, WarpGraphQLPath)

	client := gclient.New()
	client.SetHeader("Authorization", fmt.Sprintf("Bearer %s", account.IDToken))
	client.SetHeader("Content-Type", "application/json")
	if s.proxy != "" {
		client.SetProxy(s.proxy)
	}

	resp, err := client.Post(ctx, url, bytes.NewReader(bodyBytes))
	if err != nil {
		return nil, fmt.Errorf("graphql request: %w", err)
	}
	defer resp.Close()

	if resp.StatusCode != http.StatusOK {
		body := resp.ReadAllString()
		logger.Warningf(ctx, "[Warp] GetQuotaInfo failed: status=%d, body=%s",
			resp.StatusCode, body)
		return nil, fmt.Errorf("graphql error: status %d", resp.StatusCode)
	}

	// Parse response
	var graphqlResp struct {
		Data struct {
			User struct {
				Quota struct {
					Remaining float64 `json:"remaining"`
					Total     float64 `json:"total"`
					ResetAt   string  `json:"resetAt"`
				} `json:"quota"`
				Plan struct {
					Name string `json:"name"`
					Tier string `json:"tier"`
				} `json:"plan"`
			} `json:"user"`
		} `json:"data"`
		Errors []struct {
			Message string `json:"message"`
		} `json:"errors"`
	}

	if err := json.NewDecoder(resp.Body).Decode(&graphqlResp); err != nil {
		return nil, fmt.Errorf("decode graphql response: %w", err)
	}

	if len(graphqlResp.Errors) > 0 {
		return nil, fmt.Errorf("graphql errors: %s", graphqlResp.Errors[0].Message)
	}

	// Parse reset time
	var resetAt time.Time
	if graphqlResp.Data.User.Quota.ResetAt != "" {
		resetAt, _ = time.Parse(time.RFC3339, graphqlResp.Data.User.Quota.ResetAt)
	}

	return &WarpQuotaInfo{
		Remaining: graphqlResp.Data.User.Quota.Remaining,
		Total:     graphqlResp.Data.User.Quota.Total,
		ResetAt:   resetAt,
		PlanName:  graphqlResp.Data.User.Plan.Name,
		PlanTier:  graphqlResp.Data.User.Plan.Tier,
	}, nil
}

// RefundCredits requests a credit refund via the Warp GraphQL API.
// From decompiled: kiro2api_internal_logic_warp_sWarp_RefundCredits (0x1711800, 3776B)
//
// GraphQL mutation:
//   mutation RefundCredits($requestId: String!, $reason: String) {
//     refundCredits(requestId: $requestId, reason: $reason) {
//       success
//       creditsRefunded
//       newBalance
//     }
//   }
//
// Called when a request fails or is cancelled to refund the consumed credits.
func (s *sWarp) RefundCredits(ctx context.Context, account *WarpAccount,
	requestID string, reason string) error {

	logger := gins.Log()

	if err := s.ensureValidToken(ctx, account); err != nil {
		return err
	}

	mutation := `mutation RefundCredits($requestId: String!, $reason: String) {
		refundCredits(requestId: $requestId, reason: $reason) {
			success
			creditsRefunded
			newBalance
		}
	}`

	reqBody := map[string]interface{}{
		"query": mutation,
		"variables": map[string]interface{}{
			"requestId": requestID,
			"reason":    reason,
		},
	}

	bodyBytes, err := json.Marshal(reqBody)
	if err != nil {
		return fmt.Errorf("marshal refund request: %w", err)
	}

	url := fmt.Sprintf("%s%s", WarpAPIBase, WarpGraphQLPath)

	client := gclient.New()
	client.SetHeader("Authorization", fmt.Sprintf("Bearer %s", account.IDToken))
	client.SetHeader("Content-Type", "application/json")
	if s.proxy != "" {
		client.SetProxy(s.proxy)
	}

	resp, err := client.Post(ctx, url, bytes.NewReader(bodyBytes))
	if err != nil {
		return fmt.Errorf("refund request: %w", err)
	}
	defer resp.Close()

	if resp.StatusCode != http.StatusOK {
		body := resp.ReadAllString()
		logger.Warningf(ctx, "[Warp] RefundCredits failed: status=%d, body=%s",
			resp.StatusCode, body)
		return fmt.Errorf("refund error: status %d", resp.StatusCode)
	}

	// Parse response
	var graphqlResp struct {
		Data struct {
			RefundCredits struct {
				Success         bool    `json:"success"`
				CreditsRefunded float64 `json:"creditsRefunded"`
				NewBalance      float64 `json:"newBalance"`
			} `json:"refundCredits"`
		} `json:"data"`
		Errors []struct {
			Message string `json:"message"`
		} `json:"errors"`
	}

	if err := json.NewDecoder(resp.Body).Decode(&graphqlResp); err != nil {
		return fmt.Errorf("decode refund response: %w", err)
	}

	if len(graphqlResp.Errors) > 0 {
		return fmt.Errorf("refund errors: %s", graphqlResp.Errors[0].Message)
	}

	if !graphqlResp.Data.RefundCredits.Success {
		return fmt.Errorf("refund failed for request %s", requestID)
	}

	logger.Infof(ctx, "[Warp] Refunded %.2f credits for request %s, new balance: %.2f",
		graphqlResp.Data.RefundCredits.CreditsRefunded, requestID,
		graphqlResp.Data.RefundCredits.NewBalance)

	return nil
}

// ============================================================================
// mapToWarpModel — Model name mapping
// ============================================================================

// mapToWarpModel maps an OpenAI model name to a Warp model identifier.
// From decompiled: string comparison chain in ChatCompletions
func mapToWarpModel(model string) string {
	// Normalize model name
	model = strings.ToLower(strings.TrimSpace(model))

	switch {
	case strings.Contains(model, "claude-3.5-sonnet"),
		strings.Contains(model, "claude-3-5-sonnet"):
		return "claude_sonnet"
	case strings.Contains(model, "claude-3.5-haiku"),
		strings.Contains(model, "claude-3-5-haiku"):
		return "claude_haiku"
	case strings.Contains(model, "claude-3-opus"),
		strings.Contains(model, "claude-3.0-opus"):
		return "claude_opus"
	case strings.Contains(model, "gpt-4o"):
		return "gpt4o"
	case strings.Contains(model, "gpt-4"):
		return "gpt4"
	case strings.Contains(model, "o1"):
		return "o1"
	case strings.Contains(model, "o3"):
		return "o3"
	default:
		// Default to claude_sonnet
		return "claude_sonnet"
	}
}

// Ensure unused imports are referenced
var (
	_ = io.EOF
	_ = strings.NewReader
)
