package orchids

// sse_request.go — SSE/HTTP-based streaming request for the Orchids channel.
//
// Core function:
//   - executeSSERequest (0x1760cc0): Sends a request via HTTP SSE and streams the response
//
// This is the fallback transport when WebSocket is not available.
// Uses github.com/imroc/req/v3 HTTP client library.
//
// Flow:
//  1. Get proxy URL via getOrchidsProxyURL()
//  2. Create project via sOrchids.createProject() → get project ID
//  3. If createProject fails → fmt.Errorf and return
//  4. Create req/v3 HTTP client with 5-minute timeout (300000000000 ns)
//  5. If proxy URL provided → client.SetProxyURL()
//  6. Build ToolMapper if client tools exist
//  7. ConvertToOrchidsRequest() → build request
//  8. Set model type on request (offset 0x10 = string type, 0x18 = model name)
//  9. Set system prompt (offset 0xa8, 0xb0)
// 10. Append extra messages if provided
// 11. Marshal request to JSON
// 12. If marshal error → fmt.Errorf and return
// 13. Build cookie jar from account cookies (if exists)
// 14. Create HTTP request with headers:
//     - "Content-Type": "application/json" (0x10 bytes)
//     - "Accept": "text/event-stream" (0x11 bytes → 6 bytes value)
//     - "Authorization": "Bearer " + sessionToken (concat 7 bytes prefix)
//     - "X-Requested-With": "XMLHttpRequest" (0x17 bytes → 6 bytes)
//     - "User-Agent": long UA string (0x6f bytes → 10 bytes)
// 15. Set request body (JSON bytes)
// 16. Set response body callback (LAB_01761ac0)
// 17. Enable streaming (offset 0xe1 = 1)
// 18. Send POST request to Orchids API endpoint
// 19. If send error → fmt.Errorf and return

import (
	"encoding/json"
	"fmt"
	"net/http"
	"time"
)

// ============================================================================
// SSE HTTP Headers (from decompiled)
// ============================================================================

// Header constants decoded from decompiled SetHeader calls:
//
// SetHeader(&DAT_01c4edb3, 0x10, ..., 0xc)
//   Key: 0x10 = 16 bytes → "Content-Type"... actually "content-type" (16 with padding)
//   Val: 0xc = 12 bytes → "application/json" (partial, but standard)
//
// SetHeader(&DAT_01c50d2f, 0x11, ..., 6)
//   Key: 0x11 = 17 bytes → "Accept" (with extra)
//   Val: 6 bytes → "text/event-stream" → actually the accept value
//
// SetHeader(concat(session, "Bearer "), &DAT_01c3ddc9, ..., 0xd)
//   Key: 0xd = 13 bytes → "Authorization"
//   Val: "Bearer " + sessionToken
//
// SetHeader(&DAT_01c5c194, 0x17, ..., 6)
//   Key: 0x17 = 23 bytes → "X-Requested-With"
//   Val: 6 bytes → likely "XMLHttpRequest" or similar
//
// SetHeader(&DAT_01ca4dbb, 0x6f, ..., 10)
//   Key: 0x6f = 111 bytes → "User-Agent"
//   Val: 10 bytes → long user agent string

const (
	headerContentType    = "Content-Type"
	headerAccept         = "Accept"
	headerAuthorization  = "Authorization"
	headerXRequestedWith = "X-Requested-With"
	headerUserAgent      = "User-Agent"

	contentTypeJSON    = "application/json"
	acceptSSE          = "text/event-stream"
	xRequestedWithVal  = "XMLHttpRequest"

	// SSE client timeout: 5 minutes
	// Decompiled: *(*(lStack_d8 + 200) + 0x28) = 300000000000
	sseTimeout = 5 * time.Minute
)

// ============================================================================
// executeSSERequest
// ============================================================================

// executeSSERequest sends a chat completion request via HTTP SSE.
// Symbol: kiro2api/internal/logic/orchids.executeSSERequest (@ 0x1760cc0)
//
// Parameters (from decompiled):
//   param_1  (long):  account session info
//   param_2:          account ID
//   param_3:          session token
//   param_4  (long):  proxy URL length
//   param_5:          proxy URL
//   param_6:          model config
//   param_7:          model name
//   param_8:          system prompt
//   param_9  (long):  extra messages ptr
//   param_10 (*):     extra messages data
//
// Returns: error
func executeSSERequest(
	ctx *RequestContext,
	account *OrchidsAccount,
	request *ChatCompletionRequest,
	extraMessages []OrchidsConversationMessage,
) error {
	// Step 1: Get proxy URL
	// Decompiled: uStack_100 = kiro2api_internal_logic_orchids_getOrchidsProxyURL()
	proxyURL := getOrchidsProxyURL()

	// Step 2: Create project
	// Decompiled: kiro2api_internal_logic_orchids_sOrchids_createProject()
	projectID, err := New().createProject(account)
	if err != nil {
		// Decompiled: if lVar12 != 0 → fmt_Errorf(1, 1, ...)
		return fmt.Errorf("failed to create project: %v", err)
	}

	// Step 3: Create HTTP client with 5-minute timeout
	// Decompiled: github_com_imroc_req_v3_C()
	// *(*(lStack_d8 + 200) + 0x28) = 300000000000
	client := &http.Client{
		Timeout: sseTimeout,
	}

	// Step 4: Set proxy if provided
	// Decompiled: if param_4 != 0 → github_com_imroc_req_v3_Client_SetProxyURL()
	if proxyURL != "" {
		transport := &http.Transport{}
		_ = transport // Would set proxy URL here via req/v3
		client.Transport = transport
	}

	// Step 5: Build ToolMapper if client tools exist
	// Decompiled: if *(ulong *)(lStack0000000000000080 + 0x58) != 0
	var toolMapper *ToolMapper
	if len(request.Tools) > 0 {
		toolMapper = &ToolMapper{
			Tools: request.Tools,
		}
		toolMapper.buildIndex()
	}

	// Step 6: Convert to Orchids request format
	// Decompiled: ConvertToOrchidsRequest(model, config, toolMapper, request, thinkingMode, tools)
	orchidsReq := ConvertToOrchidsRequest(request, toolMapper)

	// Step 7: Set model type and name on request
	// Decompiled:
	//   *(lStack_f0 + 0x10) = &DAT_0194e220  → string type
	//   *(lStack_f0 + 0x18) = uVar3           → model name string
	orchidsReq.Model = request.Model

	// Step 8: Set system prompt
	// Decompiled:
	//   *(lVar11 + 0xa8) = uVar3  → system prompt from offset 0x18
	//   *(lVar11 + 0xb0) = ...    → system prompt from offset 0x20
	orchidsReq.System = request.Config["system"].(string)

	// Step 9: Append extra messages if provided
	// Decompiled: if param_10 != 0 → growslice + typedslicecopy at offsets 0x80-0x90
	if len(extraMessages) > 0 {
		for _, em := range extraMessages {
			orchidsReq.Messages = append(orchidsReq.Messages, OrchidsMessage{
				Role:    em.Role,
				Content: em.Content,
			})
		}
	}

	// Step 10: Marshal request to JSON
	// Decompiled: runtime_convT() → encoding_json_Marshal()
	reqBody, err := json.Marshal(orchidsReq)
	if err != nil {
		// Decompiled: if lVar6 != 0 → fmt_Errorf(1, 1, ...)
		return fmt.Errorf("failed to marshal request: %v", err)
	}

	// Step 11: Build cookie jar from account cookies
	// Decompiled: if *(lStack_d8 + 0x60) != 0 → copy cookies from account
	// The cookie jar is built by copying headers and cookies from the account's
	// stored session, including Clerk session tokens.
	var cookieJar *AccountCookieJar
	if account.ClerkToken != "" {
		cookieJar = buildCookieJar(account)
	}

	// Step 12: Create HTTP request with headers
	// Decompiled: runtime_newobject() → SetHeader calls
	_ = cookieJar
	_ = projectID

	headers := map[string]string{
		// SetHeader(&DAT_01c4edb3, 0x10, ..., 0xc)
		// "Content-Type": "application/json"
		headerContentType: contentTypeJSON,

		// SetHeader(&DAT_01c50d2f, 0x11, ..., 6)
		// "Accept": "text/event-stream"
		headerAccept: acceptSSE,

		// SetHeader(concat(session, "Bearer "), ..., 0xd)
		// "Authorization": "Bearer " + sessionToken
		// Decompiled: runtime_concatstring2(session, "Bearer ", 7)
		headerAuthorization: "Bearer " + account.SessionToken,

		// SetHeader(&DAT_01c5c194, 0x17, ..., 6)
		// "X-Requested-With": "XMLHttpRequest"
		headerXRequestedWith: xRequestedWithVal,

		// SetHeader(&DAT_01ca4dbb, 0x6f, ..., 10)
		// "User-Agent": browser-like UA string (111 bytes)
		headerUserAgent: "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/131.0.0.0 Safari/537.36",
	}

	// Step 13: Set request body
	// Decompiled: *(lStack_e8 + 0xb8) = uStack_108  → JSON body bytes
	// *(lStack_e8 + 0xc0) = uVar3                    → body length
	// *(lStack_e8 + 200) = lVar12                     → body capacity
	_ = reqBody
	_ = headers

	// Step 14: Set response body callback for streaming
	// Decompiled: *puVar10 = &LAB_01761ac0  → callback function pointer
	// puVar10[2] = uVar3                     → JSON body ref
	// puVar10[3] = lVar12                    → request ref
	// *(auVar15._8_8_ + 0xd0) = auVar15._0_8_  → set callback on request
	// *(auVar15._8_8_ + 0xe1) = 1               → enable streaming mode

	// Step 15: Send POST request
	// Decompiled: github_com_imroc_req_v3_Request_Send(&DAT_01c9dc4a, 0x4d)
	// &DAT_01c9dc4a with length 0x4d (77 bytes) = the Orchids API endpoint URL
	// Format: "POST https://api.orchids.example.com/v1/chat/completions" (approximate)

	// Step 16: Handle response
	// Decompiled: fmt_Fprintf(0x1f, ..., &DAT_01c6a717, 1, 1)
	// On success: process SSE stream via callback
	// On error: fmt_Errorf(1, 1, ..., &uStack_90)

	// The actual SSE processing happens in the callback (LAB_01761ac0)
	// which reads SSE events and calls handleModelEvent for each one.

	return fmt.Errorf("SSE request not fully implemented")
}

// ============================================================================
// SSE Callback (LAB_01761ac0)
// ============================================================================

// sseResponseCallback is the callback function for processing SSE responses.
// From decompiled: LAB_01761ac0 — set as the response body handler
// This callback:
//  1. Reads SSE events line by line from the response body
//  2. Parses each "data: {...}" line as JSON
//  3. Calls handleModelEvent for each parsed event
//  4. Continues until stream ends or error occurs
func sseResponseCallback(
	state *StreamState,
	writer *SSEWriter,
	toolMapper *ToolMapper,
	clientTools []map[string]interface{},
	body []byte,
) error {
	// Parse SSE event from body
	var event map[string]interface{}
	if err := json.Unmarshal(body, &event); err != nil {
		return nil // Skip malformed events
	}

	// Dispatch to handleModelEvent
	return handleModelEvent(state, writer, event, toolMapper, clientTools)
}

// ============================================================================
// Helper types
// ============================================================================

// AccountCookieJar holds cookies for an Orchids account session.
// Built from the account's stored Clerk session data.
// Decompiled: cookie jar construction at offsets 0x10-0x38 of the jar object
type AccountCookieJar struct {
	// Headers from the account session
	Headers []HeaderPair
	// Cookies from the account session
	Cookies []CookiePair
}

// HeaderPair represents a key-value header pair.
type HeaderPair struct {
	Key   string
	Value string
}

// CookiePair represents a key-value cookie pair.
type CookiePair struct {
	Name  string
	Value string
}

// buildCookieJar builds a cookie jar from account session data.
// From decompiled: the cookie jar construction block at lines 536-606
// Copies headers (offset 0x10-0x20) and cookies (offset 0x28-0x38) from account
func buildCookieJar(account *OrchidsAccount) *AccountCookieJar {
	jar := &AccountCookieJar{}

	// Set Clerk session cookie
	jar.Cookies = append(jar.Cookies, CookiePair{
		Name:  "__session",
		Value: account.ClerkToken,
	})

	return jar
}

// createProject creates or retrieves a project for the Orchids session.
// From decompiled: kiro2api_internal_logic_orchids_sOrchids_createProject()
// Returns the project ID and any error.
func (s *sOrchids) createProject(account *OrchidsAccount) (string, error) {
	// Create project via Orchids API
	// This likely calls the Orchids project creation endpoint
	// using the account's session credentials
	return "", nil
}
