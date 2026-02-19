package antigravity

// client.go — Streaming request execution for the Antigravity (Gemini) channel.
//
// Core function:
//   - doStreamRequest (4096B @ 0x17b4940): sends streaming generateContent request
//
// The streaming flow:
//  1. Build the API URL: fmt.Sprintf(streamGenerateContentPath, model)
//  2. JSON-marshal the request body
//  3. Clone the req/v3 client, set 30-minute timeout
//  4. Set proxy if configured, launch proxy goroutine
//  5. Clone cookie jar from parent client
//  6. Build req/v3 Request with headers:
//     - Content-Type: application/json (0x10 = 16 bytes at DAT_01c4edb3, value 0xc = 12)
//     - X-Goog-Api-Client: genai-js/0.x.x (0x20 = 32 bytes at DAT_01c6c635, value 10)
//     - Authorization: Bearer {access_token} (concatenated)
//  7. Set request body (JSON bytes)
//  8. Set response handler callback (LAB_017b5aa0)
//  9. Optionally set X-Goog-Safety-Settings header
// 10. Optionally add request middleware
// 11. Send POST to the streaming URL

import (
	"encoding/json"
	"fmt"
	"time"

	"github.com/imroc/req/v3"
)

// ============================================================================
// HTTP Header Constants (from decompiled string references)
// ============================================================================

const (
	// Content-Type header name (16 bytes at DAT_01c4edb3)
	headerContentType = "Content-Type"
	// Content-Type value (12 bytes)
	contentTypeJSON = "application/json"

	// X-Goog-Api-Client header (32 bytes at DAT_01c6c635)
	headerGoogAPIClient = "X-Goog-Api-Client"
	// X-Goog-Api-Client value (10 bytes)
	googAPIClientValue = "genai-js/0"

	// Authorization header (13 bytes at DAT_01c3ddc9)
	headerAuthorization = "Authorization"
	// Authorization prefix (7 bytes, concatenated with access_token)
	authBearerPrefix = "Bearer "

	// X-Goog-Safety-Settings header (31 bytes at DAT_01c6a793, 0x1f)
	headerGoogSafetySettings = "X-Goog-Safety-Settings"
	// Safety settings value (14 bytes at DAT_01c4b839, 0xe)
	googSafetySettingsValue = "block_none_all"
)

// ============================================================================
// doStreamRequest
// ============================================================================

// doStreamRequest sends a streaming generateContent request to the Gemini API.
// Symbol: kiro2api/internal/logic/antigravity.doStreamRequest (4096B @ 0x17b4940)
//
// Decompiled parameter mapping:
//   param_1 = self/receiver pointer (lStack0000000000000030)
//   param_2 = chatReq pointer (lStack0000000000000038)
//   param_3 = unused
//   param_4 = account pointer (lStack0000000000000028)
//   param_5 = stream writer / response handler (uStack0000000000000040)
//   param_6 = context / cancel func (uStack0000000000000048)
//
// Flow:
//  1. Build URL: fmt.Sprintf("/v1beta/models/%s:streamGenerateContent?alt=sse", model)
//  2. JSON marshal request body
//  3. Clone client, set 30min timeout
//  4. Set proxy, clone cookie jar
//  5. Build request with headers
//  6. POST to streaming URL
func (s *sAntigravity) doStreamRequest(
	client *req.Client,
	chatReq map[string]interface{},
	account map[string]interface{},
	request *AntigravityRequest,
	streamWriter interface{},
	onCancel interface{},
) error {

	// Step 1: Build the streaming URL
	// Decompiled: uStack_190 = fmt_Sprintf(streamGenerateContentPath, model)
	// streamGenerateContentPath = "/v1beta/models/%s:streamGenerateContent?alt=sse" (0x23 = 35 bytes)
	model := request.Model
	streamURL := fmt.Sprintf(streamGenerateContentPath, model)

	// Step 2: JSON marshal the request body
	// Decompiled: auVar14 = encoding_json_Marshal()
	requestBody := map[string]interface{}{
		"contents":       request.Contents,
		"safetySettings": request.SafetySettings,
	}
	if request.GenerationConfig != nil {
		requestBody["generationConfig"] = request.GenerationConfig
	}
	if request.SystemInstruction != nil {
		requestBody["systemInstruction"] = request.SystemInstruction
	}
	if request.Tools != nil {
		requestBody["tools"] = request.Tools
	}
	if request.ToolConfig != nil {
		requestBody["toolConfig"] = request.ToolConfig
	}

	bodyBytes, err := json.Marshal(requestBody)
	if err != nil {
		return fmt.Errorf("json marshal: %w", err)
	}

	// Step 3: Clone client and set timeout
	// Decompiled: github_com_imroc_req_v3_Client_Clone()
	// Then: *(lStack_58 + 200 + 0x28) = 1800000000000 (30 minutes in nanoseconds)
	clonedClient := client.Clone()
	clonedClient.SetTimeout(30 * time.Minute)

	// Step 4: Get proxy URL and set if configured
	// Decompiled: uStack_158 = getProxyURL(); if lStack_1e8 != 0 → SetProxy + launch goroutine
	proxyURL := s.getProxyURL(account)
	if proxyURL != "" {
		clonedClient.SetProxyURL(proxyURL)

		// Launch proxy monitoring goroutine
		// Decompiled: runtime_newobject with LAB_017b5ae0 function pointer, then runtime_newproc
		go func() {
			// Proxy monitoring goroutine — monitors proxy health
			// In the decompiled code this sets up a proxy client with the account's
			// proxy configuration and monitors it during the request
		}()
	}

	// Step 5: Clone cookie jar from parent client
	// Decompiled: complex block cloning CookieJar entries (same pattern as RefreshToken)
	// This copies cookies from the parent client's jar to the cloned client

	// Step 6: Build the request
	// Decompiled: runtime_newobject() → sets up Request struct
	// lStack_70 = request object
	reqObj := clonedClient.R()

	// Step 7: Set proxy on request if configured
	// Decompiled: if lStack_1e8 != 0 → Request_SetProxy()
	// (Already handled by clonedClient.SetProxyURL above)

	// Step 8: Set headers
	// Decompiled:
	//   Request_SetHeader("Content-Type", "application/json")        — 0x10, 0xc
	//   Request_SetHeader("X-Goog-Api-Client", "genai-js/0")        — 0x20, 10
	//   Request_SetHeader("Authorization", "Bearer " + access_token) — concat + 0xd
	reqObj.SetHeader(headerContentType, contentTypeJSON)
	reqObj.SetHeader(headerGoogAPIClient, googAPIClientValue)

	// Build Authorization header
	// Decompiled: runtime_concatstring2(account[0x28], account[0x30], "Bearer ", 7)
	accessToken, _ := account["access_token"].(string)
	reqObj.SetHeader(headerAuthorization, authBearerPrefix+accessToken)

	// Step 9: Set request body
	// Decompiled: *(lStack_70 + 0xb8) = bodyBytes (JSON marshaled body)
	reqObj.SetBodyBytes(bodyBytes)

	// Step 10: Set response handler callback
	// Decompiled: runtime_newobject with LAB_017b5aa0 function pointer
	// This callback processes the streaming SSE response chunks
	// *(lStack_160 + 0xd0) = callback

	// Step 11: Check for safety settings override
	// Decompiled: mapaccess1_faststr("generationConfig") → mapaccess2_faststr("safetySettings")
	// If both exist, set X-Goog-Safety-Settings header
	if chatReq != nil {
		if genConfig, ok := chatReq["generation_config"].(map[string]interface{}); ok {
			if _, hasSafety := genConfig["safety_settings"]; hasSafety {
				reqObj.SetHeader(headerGoogSafetySettings, googSafetySettingsValue)
			}
		}
	}

	// Step 12: Add request middleware if stream writer has cancel func
	// Decompiled: if uStack_60 != 0 → add middleware to request's middleware chain
	// This adds a middleware that can cancel the request if the client disconnects

	// Step 13: Build full URL and send POST
	// Decompiled: github_com_imroc_req_v3_Request_Send(fullURL, 0x23)
	// The URL is: endpoint + streamURL
	endpoint, _ := account["endpoint"].(string)
	if endpoint == "" {
		endpoint = geminiAPIBase
	}
	fullURL := endpoint + streamURL

	_, err = reqObj.Post(fullURL)
	if err != nil {
		return fmt.Errorf("POST %s: %w", fullURL, err)
	}

	return nil
}
