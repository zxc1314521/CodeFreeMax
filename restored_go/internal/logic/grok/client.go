package grok

// client.go — HTTP client and network operations for the Grok channel.
//
// Functions:
//   - GrokClient                — HTTP client wrapper with cookie auth
//   - GrokClient.PostStream     — Streaming POST request
//   - clientForAccount          — Per-account client management
//   - isTimeoutError            — Timeout error detection
//   - newGrokClient             — Client constructor with proxy support
//
// The Grok channel uses cookie-based authentication (auth_token, ct0)
// with Cloudflare bypass (cf_clearance) and browser fingerprint spoofing.
// HTTP requests go through the imroc/req/v3 client library.
//
// From decompiled patterns:
//   - clientForAccount creates/reuses per-account HTTP clients
//   - PostStream sends POST with streaming response handling
//   - isTimeoutError checks for net.Error timeout (used in ImagineGenerations)
//   - Cloudflare clearance and browser fingerprint are injected into headers

import (
	"context"
	"encoding/json"
	"fmt"
	"io"
	"net"
	"net/http"
	"strings"
	"time"

	"github.com/gogf/gf/v2/frame/gins"
	"github.com/imroc/req/v3"

	"kiro2api/internal/logic/common"
)

// ============================================================================
// GrokClient
// ============================================================================

// GrokClient wraps an HTTP client configured for Grok API requests.
// From decompiled: kiro2api_internal_logic_grok_GrokClient type
// with methods PostStream, and associated per-account management.
type GrokClient struct {
	client  *req.Client
	headers GrokHeaders
	baseURL string
}

// NewGrokClient creates a new GrokClient with the given configuration.
// From decompiled: newGrokClient with proxy support and timeout configuration.
func NewGrokClient(proxyURL string, timeout time.Duration) *GrokClient {
	client := req.C().
		SetTimeout(timeout).
		SetRedirectPolicy(req.NoRedirectPolicy())

	if proxyURL != "" {
		client.SetProxyURL(proxyURL)
	}

	// Disable HTTP/2 to match browser behavior
	// From decompiled: transport configuration patterns
	client.GetTransport().
		DisableKeepAlives = false

	return &GrokClient{
		client:  client,
		baseURL: grokAPIBase,
	}
}

// SetHeaders sets the default headers for all requests.
func (gc *GrokClient) SetHeaders(headers GrokHeaders) {
	gc.headers = headers
}

// ============================================================================
// PostStream
// ============================================================================

// PostStream sends a POST request and returns the streaming response body.
//
// From decompiled: kiro2api_internal_logic_grok_GrokClient_PostStream
// Called in VideoGenerations (@ 0x161bc00) and ChatCompletions.
//
// Parameters:
//   - ctx: context for cancellation
//   - path: API endpoint path
//   - payload: request body (will be JSON marshaled)
//   - headers: additional headers to merge with defaults
//
// Returns:
//   - io.ReadCloser for the streaming response body
//   - HTTP status code
//   - error if request fails
func (gc *GrokClient) PostStream(
	ctx context.Context,
	path string,
	payload interface{},
	headers GrokHeaders,
) (io.ReadCloser, int, error) {
	logger := gins.Log()

	// Marshal payload
	bodyBytes, err := json.Marshal(payload)
	if err != nil {
		return nil, 0, fmt.Errorf("marshal payload: %w", err)
	}

	// Build request
	url := gc.baseURL + path
	httpReq := gc.client.R().
		SetContext(ctx).
		SetBody(bodyBytes)

	// Apply default headers
	for k, v := range gc.headers {
		httpReq.SetHeader(k, v)
	}

	// Apply additional headers (override defaults)
	for k, v := range headers {
		httpReq.SetHeader(k, v)
	}

	// Ensure streaming headers
	httpReq.SetHeader("Accept", "text/event-stream")
	httpReq.SetHeader("Content-Type", "application/json")

	logger.Debugf(nil, "[Grok] POST %s (body: %d bytes)", url, len(bodyBytes))

	// Send request
	resp, err := httpReq.Post(url)
	if err != nil {
		return nil, 0, fmt.Errorf("POST %s: %w", path, err)
	}

	statusCode := resp.StatusCode
	if statusCode != http.StatusOK {
		bodyContent, _ := io.ReadAll(resp.Body)
		resp.Body.Close()
		logger.Warningf(nil, "[Grok] POST %s failed (HTTP %d): %s", path, statusCode, string(bodyContent))
		return nil, statusCode, fmt.Errorf("HTTP %d: %s", statusCode, string(bodyContent))
	}

	return resp.Body, statusCode, nil
}

// ============================================================================
// clientForAccount
// ============================================================================

// clientForAccount creates or retrieves a GrokClient configured for a specific account.
//
// From decompiled: kiro2api_internal_logic_grok_sGrok_clientForAccount
// Called in ImagineGenerations and VideoGenerations before making API requests.
//
// The client is configured with:
//   - Account-specific proxy
//   - Cookie-based auth headers
//   - Browser fingerprint
//   - Cloudflare clearance
func (s *sGrok) clientForAccount(account map[string]interface{}) *GrokClient {
	// Extract proxy URL
	proxyURL, _ := account["proxy"].(string)

	// Create client with appropriate timeout
	client := NewGrokClient(proxyURL, time.Duration(chatTimeoutNs))

	// Build headers for this account
	fingerprint := s.GetBrowserFingerprint()
	cfClearance := s.GetCfClearance()
	userAgent, _ := account["user_agent"].(string)
	cookie, _ := account["cookie"].(string)

	headers := BuildHeaders(account, fingerprint, userAgent, cfClearance, cookie)
	client.SetHeaders(headers)

	return client
}

// ============================================================================
// isTimeoutError
// ============================================================================

// isTimeoutError checks if an error is a network timeout error.
//
// From decompiled: kiro2api_internal_logic_grok_isTimeoutError
// Used in ImagineGenerations (@ 0x160cd00) to detect WebSocket read timeouts
// and decide whether to retry or abort.
//
// The function unwraps the error chain and checks for net.Error with Timeout().
func isTimeoutError(err error) bool {
	if err == nil {
		return false
	}

	// Check for net.Error timeout
	if netErr, ok := err.(net.Error); ok {
		return netErr.Timeout()
	}

	// Check wrapped errors
	if strings.Contains(err.Error(), "timeout") ||
		strings.Contains(err.Error(), "deadline exceeded") {
		return true
	}

	return false
}

// ============================================================================
// ChatCompletions
// ============================================================================

// ChatCompletions handles an OpenAI-compatible chat completion request via the Grok API.
// This is the main entry point called by the controller layer.
//
// Flow (derived from decompiled patterns across all functions):
//   1. Extract model and messages from request
//   2. Format system prompt from messages
//   3. Build chat payload via BuildChatPayload
//   4. Build headers with auth, fingerprint, CF clearance
//   5. Send streaming POST request
//   6. Parse streaming response via ParseStreamResponse
func (s *sGrok) ChatCompletions(
	ctx context.Context,
	w http.ResponseWriter,
	chatReq map[string]interface{},
	account map[string]interface{},
) error {
	logger := gins.Log()

	// Extract model
	model, _ := chatReq["model"].(string)
	model = mapModelName(model)

	// Extract messages
	var messages []map[string]interface{}
	if msgList, ok := chatReq["messages"].([]interface{}); ok {
		for _, m := range msgList {
			if msg, ok := m.(map[string]interface{}); ok {
				messages = append(messages, msg)
			}
		}
	}

	// Format system prompt
	systemPrompt := formatSystemPrompt(messages)

	// Filter out system messages for the conversation
	var convMessages []map[string]interface{}
	for _, msg := range messages {
		role, _ := msg["role"].(string)
		if role != "system" {
			convMessages = append(convMessages, msg)
		}
	}

	// Generate conversation ID
	conversationID := generateConversationID()

	// Build payload
	payload := BuildChatPayload(
		model,
		systemPrompt,
		conversationID,
		convMessages,
		nil, // imageAttachments
		nil, // fileAttachments
	)

	logger.Infof(nil, "[Grok] Chat request: model=%s, messages=%d", model, len(convMessages))

	// Create per-account client
	client := s.clientForAccount(account)

	// Build additional headers
	fingerprint := s.GetBrowserFingerprint()
	cfClearance := s.GetCfClearance()
	userAgent, _ := account["user_agent"].(string)
	cookie, _ := account["cookie"].(string)
	headers := BuildHeaders(account, fingerprint, userAgent, cfClearance, cookie)

	// Send streaming request
	body, statusCode, err := client.PostStream(ctx, grokChatEndpoint, payload, headers)
	if err != nil {
		logger.Warningf(nil, "[Grok] Chat request failed (HTTP %d): %v", statusCode, err)
		return fmt.Errorf("[Grok] chat request failed: %w", err)
	}

	// Parse and stream response
	writer := common.NewSSEWriter(w)
	if err := s.ParseStreamResponse(ctx, body, writer, account); err != nil {
		logger.Warningf(nil, "[Grok] Stream error: %v", err)
		return fmt.Errorf("[Grok] stream error: %w", err)
	}

	return nil
}
