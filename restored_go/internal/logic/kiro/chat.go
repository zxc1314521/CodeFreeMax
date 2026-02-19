package kiro

// chat.go — ChatCompletions entry point and related functions for the Kiro channel.
//
// Functions:
//   - ChatCompletions   (1728B @ 0x17a3c80) — Main chat handler
//   - CheckToken        (1024B @ 0x17a2aa0) — Token validity check with refresh
//   - GetUsageInfo      (320B  @ 0x17a2960) — Usage info retrieval
//   - getUsageLimits    (2176B @ 0x17a20e0) — Fetch usage limits from AWS Q API
//
// ChatCompletions flow (from decompiled 1728 bytes):
//   1. CheckToken → ensure valid access token
//   2. getUsageLimits → fetch current usage state
//   3. buildDynamicHeaders → construct request headers
//   4. buildKiroRequest → transform OpenAI request to Kiro format
//   5. JSON marshal the request body
//   6. AWS SigV4 sign the request
//   7. Send HTTP POST to AWS Q API endpoint
//   8. Check response status (checkBannedResponse)
//   9. Wrap response body in contextCloser
//  10. ParseStreamResponse → stream back to client

import (
	"context"
	"encoding/json"
	"fmt"
	"io"
	"net/http"

	"github.com/gogf/gf/v2/frame/gins"
	"github.com/imroc/req/v3"

	"kiro2api/internal/logic/common"
)

// ============================================================================
// AWS Q API Paths
// ============================================================================

const (
	// Chat completions endpoint path
	// From Kiro source: POST to /chat/completions on Q Developer API
	awsQChatPath = "/chat/completions"

	// Usage info endpoint path
	awsQUsagePath = "/usage"

	// Kiro User-Agent format
	kiroUserAgent = "KiroIDE/1.0"
)

// ============================================================================
// ChatCompletions
// ============================================================================

// ChatCompletions handles an OpenAI-compatible chat completion request via the
// AWS Q Developer API. This is the main entry point called by the controller layer.
//
// Symbol: kiro2api/internal/logic/kiro.(*sKiro).ChatCompletions (1728B @ 0x17a3c80)
//
// From decompiled (1728 bytes):
//   1. Call CheckToken to validate/refresh the access token
//   2. Call getUsageLimits to get current usage state
//   3. Build dynamic headers (machine ID, IP, timestamp)
//   4. Call buildKiroRequest to transform the request
//   5. JSON marshal the request body
//   6. Build HTTP request with SigV4 signing
//   7. Send POST to AWS Q endpoint
//   8. Check response for ban indicators
//   9. Wrap body in contextCloser for cancellation support
//  10. Call ParseStreamResponse to stream back to client
//
// The function signature follows the same pattern as other channels
// (antigravity, orchids, cursor).
func (s *sKiro) ChatCompletions(
	ctx context.Context,
	w http.ResponseWriter,
	chatReq map[string]interface{},
	account map[string]interface{},
	client *req.Client,
) error {
	logger := gins.Log()

	// ========================================================================
	// Step 1: Check and refresh token
	// From decompiled: first call in ChatCompletions is CheckToken
	// ========================================================================
	valid, checkErr := s.CheckToken(client, account)
	if checkErr != nil {
		return fmt.Errorf("[Kiro] token check failed: %w", checkErr)
	}
	if !valid {
		return fmt.Errorf("[Kiro] token is invalid")
	}

	// ========================================================================
	// Step 2: Get usage limits
	// From decompiled: getUsageLimits called after CheckToken
	// ========================================================================
	limits, err := s.getUsageLimits(client, account)
	if err != nil {
		logger.Warningf(nil, "[Kiro] Failed to get usage limits: %v", err)
		// Non-fatal — continue without limits
	}

	// ========================================================================
	// Step 3: Build dynamic headers
	// From decompiled: buildDynamicHeaders (896B @ 0x17a3580)
	// ========================================================================
	dynamicHeaders := s.buildDynamicHeaders(account)

	// Add usage limits headers if available
	if limits != nil {
		limitsHeaders := buildUsageLimitsHeaders(limits)
		for k, v := range limitsHeaders {
			dynamicHeaders[k] = v
		}
	}

	// ========================================================================
	// Step 4: Build the Kiro request
	// From decompiled: buildKiroRequest (24160B @ 0x17a4e20)
	// ========================================================================
	kiroReq := s.buildKiroRequest(chatReq, account)

	// Inject dynamic headers into parent message
	if kiroReq.ParentMessage != nil {
		for k, v := range dynamicHeaders {
			kiroReq.ParentMessage.Headers[k] = v
		}
	}

	// ========================================================================
	// Step 5: Marshal request body
	// From decompiled: encoding_json_Marshal() call
	// ========================================================================
	reqBody, err := json.Marshal(kiroReq)
	if err != nil {
		return fmt.Errorf("[Kiro] marshal request: %w", err)
	}

	// ========================================================================
	// Step 6: Build and sign the HTTP request
	// From decompiled: AWS SigV4 signing with access token
	// The request is signed using the account's access token as the
	// AWS session credential.
	// ========================================================================
	accessToken, _ := account["access_token"].(string)
	endpoint := awsQAPIBase
	if ep, ok := account["endpoint"].(string); ok && ep != "" {
		endpoint = ep
	}

	requestURL := endpoint + awsQChatPath

	// Create the HTTP request via req/v3 client
	// Updated: Uses Bearer auth + Kiro-specific headers instead of SigV4
	httpReq := client.R().
		SetContext(ctx).
		SetHeader("Content-Type", "application/json").
		SetHeader("Authorization", "Bearer "+accessToken).
		SetHeader("Accept", "text/event-stream").
		SetHeader("User-Agent", kiroUserAgent).
		SetHeader("x-amzn-kiro-agent-mode", "none").
		SetHeader("x-amzn-codewhisperer-optout", "false").
		SetHeader("x-kiro-machineid", s.machineID).
		SetBody(reqBody)

	// Add dynamic headers to HTTP request
	for k, v := range dynamicHeaders {
		httpReq.SetHeader(k, v)
	}

	logger.Infof(nil, "[Kiro] Sending chat request to %s (model: %s, messages: %d)",
		requestURL, kiroReq.Model, len(kiroReq.Messages))

	// ========================================================================
	// Step 7: Send the request
	// From decompiled: client.Do() or similar HTTP send
	// ========================================================================
	resp, err := httpReq.Post(requestURL)
	if err != nil {
		return fmt.Errorf("[Kiro] request failed: %w", err)
	}

	// ========================================================================
	// Step 8: Check response status
	// From decompiled: checkBannedResponse (480B @ 0x17a2ea0)
	// ========================================================================
	statusCode := resp.StatusCode
	if statusCode != http.StatusOK {
		bodyBytes, _ := io.ReadAll(resp.Body)
		resp.Body.Close()
		bodyStr := string(bodyBytes)

		if s.checkBannedResponse(statusCode, bodyStr) {
			logger.Warningf(nil, "[Kiro] Account banned/blocked, status: %d", statusCode)
			return fmt.Errorf("[Kiro] account banned (HTTP %d): %s", statusCode, bodyStr)
		}

		logger.Warningf(nil, "[Kiro] Request failed with status %d: %s", statusCode, bodyStr)
		return fmt.Errorf("[Kiro] request failed (HTTP %d): %s", statusCode, bodyStr)
	}

	// ========================================================================
	// Step 9: Wrap response body with context cancellation
	// From decompiled: contextCloser wraps the response body
	// ========================================================================
	body := newContextCloser(ctx, resp.Body)

	// ========================================================================
	// Step 10: Stream the response
	// From decompiled: ParseStreamResponse (224B @ 0x17aac80)
	// ========================================================================
	writer := common.NewSSEWriter(w)

	if err := s.ParseStreamResponse(ctx, body, writer, account); err != nil {
		logger.Warningf(nil, "[Kiro] Stream error: %v", err)
		return fmt.Errorf("[Kiro] stream error: %w", err)
	}

	return nil
}
