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
	"log"
	"net/http"
	"os"
	"time"

	"github.com/gogf/gf/v2/frame/gins"
	"github.com/imroc/req/v3"

	"kiro2api/internal/logic/common"
)

// ============================================================================
// AWS Q API Paths
// ============================================================================

const (
	// generateAssistantResponse endpoint path
	// From Kiro source: b12.bp("/generateAssistantResponse") at line 667083
	awsQChatPath = "/generateAssistantResponse"

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
	// Step 1: Check and refresh token (skip if already verified by caller)
	// From decompiled: first call in ChatCompletions is CheckToken
	// ========================================================================
	log.Printf("[Kiro][ChatCompletions] === START === account_id=%v model=%v", account["id"], chatReq["model"])
	log.Printf("[Kiro][ChatCompletions] access_token present=%v (len=%d), refresh_token present=%v",
		account["access_token"] != nil && account["access_token"] != "",
		len(fmt.Sprintf("%v", account["access_token"])),
		account["refresh_token"] != nil && account["refresh_token"] != "")

	if _, skip := account["_token_checked"].(bool); !skip {
		log.Printf("[Kiro][ChatCompletions] Step 1: CheckToken starting...")
		valid, checkErr := s.CheckToken(client, account)
		if checkErr != nil {
			log.Printf("[Kiro][ChatCompletions] Step 1: CheckToken FAILED: %v", checkErr)
			return fmt.Errorf("[Kiro] token check failed: %w", checkErr)
		}
		if !valid {
			log.Printf("[Kiro][ChatCompletions] Step 1: CheckToken returned invalid")
			return fmt.Errorf("[Kiro] token is invalid")
		}
		log.Printf("[Kiro][ChatCompletions] Step 1: CheckToken OK")

		// Fetch available models synchronously if cache is stale
		if NeedModelRefresh() {
			accessTok, _ := account["access_token"].(string)
			if accessTok != "" {
				log.Printf("[Kiro][ChatCompletions] Fetching available models (sync)...")
				s.FetchAndCacheModels(accessTok)
			}
		}
	} else {
		log.Printf("[Kiro][ChatCompletions] Step 1: Skipping CheckToken (already verified)")
		logger.Info(nil, "[Kiro] Skipping CheckToken (already verified by caller)")
	}

	// ========================================================================
	// Step 2: Get usage limits (non-blocking, skip on timeout)
	// From decompiled: getUsageLimits called after CheckToken
	// ========================================================================
	log.Printf("[Kiro][ChatCompletions] Step 2: getUsageLimits starting...")
	var limits *UsageLimits
	limitsCh := make(chan struct{})
	go func() {
		defer close(limitsCh)
		var limitsErr error
		limits, limitsErr = s.getUsageLimits(client, account)
		if limitsErr != nil {
			log.Printf("[Kiro][ChatCompletions] Step 2: getUsageLimits error: %v", limitsErr)
			logger.Warningf(nil, "[Kiro] Failed to get usage limits: %v", limitsErr)
		}
	}()
	// Wait at most 10 seconds for usage limits — don't block the chat request
	select {
	case <-limitsCh:
		log.Printf("[Kiro][ChatCompletions] Step 2: getUsageLimits completed, limits=%v", limits != nil)
	case <-time.After(10 * time.Second):
		log.Printf("[Kiro][ChatCompletions] Step 2: getUsageLimits TIMEOUT (10s)")
		logger.Warning(nil, "[Kiro] Usage limits request timed out, continuing without limits")
		limits = nil
	case <-ctx.Done():
		log.Printf("[Kiro][ChatCompletions] Step 2: context cancelled while waiting for limits")
		return ctx.Err()
	}

	// ========================================================================
	// Step 3: Build request (dynamic headers no longer needed — real Kiro SDK
	// only sends Authorization, Content-Type, User-Agent, agent-mode, optout)
	// ========================================================================

	log.Printf("[Kiro][ChatCompletions] Step 4: buildKiroRequest...")
	genReq := s.buildGenerateAssistantRequest(chatReq, account)
	log.Printf("[Kiro][ChatCompletions] Step 4: genReq built, conversationID=%s, hasHistory=%v",
		genReq.ConversationState.ConversationID, len(genReq.ConversationState.History) > 0)

	log.Printf("[Kiro][ChatCompletions] Step 5: Marshal request body...")
	reqBody, err := json.Marshal(genReq)
	if err != nil {
		log.Printf("[Kiro][ChatCompletions] Step 5: Marshal FAILED: %v", err)
		return fmt.Errorf("[Kiro] marshal request: %w", err)
	}
	log.Printf("[Kiro][ChatCompletions] Step 5: Marshal OK, body size=%d bytes", len(reqBody))
	log.Printf("[Kiro][ChatCompletions] Step 5: REQUEST BODY: %s", string(reqBody))
	// Dump request body to file for debugging
	os.WriteFile("kiro_our_request.json", reqBody, 0644)

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
	proxyURL := getProxyURL(account)
	log.Printf("[Kiro][ChatCompletions] Step 6: endpoint=%s, requestURL=%s, proxyURL=%q, accessToken_len=%d",
		endpoint, requestURL, proxyURL, len(accessToken))

	streamClient := newKiroClient(client, proxyURL)

	// Headers match real Kiro client (CodeWhispererStreaming SDK):
	//   - Authorization: Bearer <token> (HttpBearerAuthSigner)
	//   - Content-Type: application/json
	//   - User-Agent: KiroIDE <version> <machineId> (customUserAgent)
	//   - x-amzn-kiro-agent-mode: vibe (addAgentModeHeadersMiddleware)
	//   - x-amzn-codewhisperer-optout: false (addPrivacyHeadersMiddleware)
	httpReq := streamClient.R().
		SetContext(ctx).
		SetHeader("Content-Type", "application/json").
		SetHeader("Authorization", "Bearer "+accessToken).
		SetHeader("User-Agent", fmt.Sprintf("KiroIDE 1.0.0 %s", s.machineID)).
		SetHeader("x-amzn-kiro-agent-mode", "vibe").
		SetHeader("x-amzn-codewhisperer-optout", "false").
		SetBody(reqBody)

	log.Printf("[Kiro][ChatCompletions] Step 7: Sending POST to %s ...", requestURL)
	sendStart := time.Now()
	resp, err := httpReq.Post(requestURL)
	sendDuration := time.Since(sendStart)
	if err != nil {
		log.Printf("[Kiro][ChatCompletions] Step 7: POST FAILED after %v: %v", sendDuration, err)
		return fmt.Errorf("[Kiro] request failed: %w", err)
	}
	log.Printf("[Kiro][ChatCompletions] Step 7: POST completed in %v, status=%d", sendDuration, resp.StatusCode)

	// ========================================================================
	// Step 8: Check response status
	// From decompiled: checkBannedResponse (480B @ 0x17a2ea0)
	// ========================================================================
	statusCode := resp.StatusCode
	log.Printf("[Kiro][ChatCompletions] Step 8: Response status=%d, content-type=%s",
		statusCode, resp.Header.Get("Content-Type"))
	if statusCode != http.StatusOK {
		bodyBytes, _ := io.ReadAll(resp.Body)
		resp.Body.Close()
		bodyStr := string(bodyBytes)
		log.Printf("[Kiro][ChatCompletions] Step 8: Non-200 response body (first 500 chars): %.500s", bodyStr)

		if s.checkBannedResponse(statusCode, bodyStr) {
			log.Printf("[Kiro][ChatCompletions] Step 8: Account BANNED, status=%d", statusCode)
			return fmt.Errorf("[Kiro] account banned (HTTP %d): %s", statusCode, bodyStr)
		}

		log.Printf("[Kiro][ChatCompletions] Step 8: Request FAILED, status=%d", statusCode)
		return fmt.Errorf("[Kiro] request failed (HTTP %d): %s", statusCode, bodyStr)
	}

	log.Printf("[Kiro][ChatCompletions] Step 9: Wrapping response body with contextCloser...")
	body := newContextCloser(ctx, resp.Body)

	log.Printf("[Kiro][ChatCompletions] Step 10: Starting ParseStreamResponse...")
	writer := common.NewSSEWriter(w)
	if modelName, ok := chatReq["model"].(string); ok && modelName != "" {
		writer.SetModel(modelName)
	} else {
		writer.SetModel("claude-sonnet-4.5")
	}

	streamStart := time.Now()
	if err := s.ParseStreamResponse(ctx, body, writer, account); err != nil {
		log.Printf("[Kiro][ChatCompletions] Step 10: ParseStreamResponse FAILED after %v: %v", time.Since(streamStart), err)
		return fmt.Errorf("[Kiro] stream error: %w", err)
	}

	log.Printf("[Kiro][ChatCompletions] === DONE === stream completed in %v", time.Since(streamStart))
	return nil
}
