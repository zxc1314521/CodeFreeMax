package grok

// request.go — Request building for the Grok channel.
//
// Functions:
//   - BuildChatPayload     (@ 0x1606520) — Build the full chat request payload
//   - BuildHeaders         — Build HTTP headers with auth and fingerprint
//   - buildVideoPayload    — Build video generation request payload
//
// BuildChatPayload (@ 0x1606520, ~350 lines C pseudocode):
//   Constructs a deeply nested map[string]interface{} payload for the Grok API.
//   The decompiled code shows extensive use of runtime_makemap, runtime_mapassign_faststr
//   with string length parameters that reveal the key names:
//
//   Top-level keys (from mapassign_faststr length params):
//     9  bytes → "responses"
//     9  bytes → "modelName" (convTstring)
//     9  bytes → (another 9-byte key)
//     7  bytes → "grokModelOptionId" (nested)
//     0xf bytes (15) → "systemPromptName" (convTslice)
//     0x10 bytes (16) → "conversationId" or "imageAttachments" (convTslice)
//     0xd bytes (13) → "forceConcise" or "isDeepsearch"
//     0x15 bytes (21) → "respondWithMediaType"
//     0x10 bytes (16) → "imageGenerationCount"
//     0x19 bytes (25) → "disableTextFollowUp"
//     0x14 bytes (20) → "enableImageGeneration" or "returnSearchResults"
//     0x14 bytes (20) → "imageAttachments" (int type → DAT_0194e460)
//     0xc bytes (12) → "forceConcise"
//
//   Nested "toolOverrides" map (from second makemap_small block):
//     0xd bytes (13) → "toolOverrides"
//     0x10 bytes (16) → (sub-key)
//     0x11 bytes (17) → (sub-key)
//     0xb bytes (11) → (sub-key)
//     0x14 bytes (20) → (sub-key)
//     0xd bytes (13) → (sub-key)
//     0xf bytes (15) → (sub-key)
//     0xb bytes (11) → (sub-key)
//     0x1b bytes (27) → (sub-key)
//
//   Nested "respondWithMediaType" map:
//     8  bytes → "metadata"
//     0x13 bytes (19) → (sub-key)
//     0x13 bytes (19) → (sub-key)
//     0x10 bytes (16) → (sub-key)
//
//   Nested metadata sub-map:
//     0xf bytes (15) → (sub-key)
//     0x10 bytes (16) → (sub-key, int type)
//     0xb bytes (11) → (sub-key, int type)
//     0xc bytes (12) → (sub-key, int type)
//     0xd bytes (13) → (sub-key, int type)
//     0xe bytes (14) → (sub-key, int type)
//     0xd bytes (13) → (sub-key, map type)

import (
	"crypto/rand"
	"encoding/hex"
	"fmt"
	"strings"
)

// ============================================================================
// BuildChatPayload
// ============================================================================

// BuildChatPayload constructs the full chat request payload for the Grok API.
//
// Symbol: kiro2api/internal/logic/grok.BuildChatPayload (@ 0x1606520)
//
// Parameters:
//   - model: the model name/ID
//   - systemPrompt: system prompt text
//   - messages: OpenAI-format messages
//   - imageAttachments: optional image attachments
//   - fileAttachments: optional file attachments
//
// From decompiled (350 lines):
//   1. Copy imageAttachments and fileAttachments slices
//   2. Build top-level map with conversation settings
//   3. Build nested "toolOverrides" map with boolean flags
//   4. Build nested "respondWithMediaType" map
//   5. Build nested metadata map with numeric settings
//   6. Return the complete payload map
func BuildChatPayload(
	model string,
	systemPrompt string,
	conversationID string,
	messages []map[string]interface{},
	imageAttachments []map[string]interface{},
	fileAttachments []map[string]interface{},
) GrokChatPayload {
	// Merge attachments
	// From decompiled: runtime_typedslicecopy for both attachment slices
	var allAttachments []map[string]interface{}
	if len(imageAttachments) > 0 {
		allAttachments = append(allAttachments, imageAttachments...)
	}
	if len(fileAttachments) > 0 {
		allAttachments = append(allAttachments, fileAttachments...)
	}

	// Build the top-level payload map
	// From decompiled: runtime_makemap() followed by many mapassign_faststr calls
	payload := GrokChatPayload{
		// 9 bytes: "responses" — conversation messages
		"responses": buildConversationMessages(messages),

		// 9 bytes: model name (convTstring)
		"modelName": model,

		// 9 bytes: another string field
		"grokModelOptionId": model,

		// 15 bytes: "systemPromptName" (convTslice)
		"systemPromptName": systemPrompt,

		// 16 bytes: "conversationId" (convTslice)
		"conversationId": conversationID,

		// 13 bytes: "forceConcise" → bool (false)
		// From decompiled: DAT_01f8a680 = false
		"forceConcise": false,

		// 21 bytes: "respondWithMediaType" → bool (true)
		// From decompiled: DAT_01f8a688 = true
		"respondWithMediaType": true,

		// 16 bytes: "imageGenerationCount" → bool (false)
		"imageGenerationCount": false,

		// 25 bytes: "disableTextFollowUp" → bool (false)
		"disableTextFollowUp": false,

		// 20 bytes: "enableImageGeneration" → bool (true)
		"enableImageGeneration": true,

		// 20 bytes: "imageAttachments" → int (0)
		// From decompiled: DAT_0194e460 (int type), DAT_01f34d38 (value)
		"imageAttachments": allAttachments,

		// 12 bytes: "forceConcise" → bool (false)
		"returnCitations": false,
	}

	// Build "toolOverrides" nested map
	// From decompiled: runtime_makemap_small() for toolOverrides
	// Contains boolean flags for various tool capabilities
	toolOverrides := map[string]interface{}{
		// 13 bytes key
		"searchEnabled": true,
		// 16 bytes key
		"imageGenEnabled": true,
		// 17 bytes key
		"trendingEnabled":  true,
		// 11 bytes key
		"xPostSearch": false,
		// 20 bytes key
		"webSearchEnabled":    false,
		// 13 bytes key
		"codeExecution": false,
		// 15 bytes key
		"fileProcessing": false,
		// 11 bytes key
		"xMediaSearch": false,
		// 27 bytes key
		"reasoningSearchEnabled": false,
	}
	payload["toolOverrides"] = toolOverrides

	// Build "respondWithMediaType" nested map
	// From decompiled: third makemap_small() block
	// Contains media type configuration
	respondMedia := map[string]interface{}{
		// 8 bytes: "metadata"
		"metadata": buildMediaMetadata(),
		// 19 bytes: sub-key with nested map
		"imageModelConfigs": map[string]interface{}{
			// 7 bytes: model ID
			"modelId": model,
		},
		// 16 bytes: sub-key
		"videoModelConfig": map[string]interface{}{},
	}
	payload["respondWithMediaType"] = respondMedia

	return payload
}

// buildMediaMetadata constructs the metadata sub-map for respondWithMediaType.
// From decompiled: nested makemap_small() with int-typed values.
func buildMediaMetadata() map[string]interface{} {
	return map[string]interface{}{
		// 15 bytes: "serverSideStats" → bool (false)
		"serverSideStats": false,
		// 16 bytes: int type → DAT_01f34d38
		"imageGenAttempts": 0,
		// 11 bytes: int type → DAT_01f38730
		"videoLength": 0,
		// 12 bytes: int type → DAT_01f38738
		"videoBitrate": 0,
		// 13 bytes: int type → DAT_01f38730
		"videoQuality": 0,
		// 14 bytes: int type → DAT_01f38740
		"videoFrameRate": 0,
		// 13 bytes: map type → nested map
		"imageSettings": map[string]interface{}{},
	}
}

// ============================================================================
// BuildHeaders
// ============================================================================

// BuildHeaders constructs the HTTP headers for a Grok API request.
// Includes cookie-based authentication, browser fingerprint spoofing,
// and Cloudflare bypass headers.
//
// From decompiled patterns across multiple functions:
//   - Cookie header with auth_token, ct0, cf_clearance
//   - X-Csrf-Token header (ct0 value)
//   - User-Agent with browser fingerprint
//   - Accept and Content-Type headers
//   - Origin and Referer for CORS
func BuildHeaders(
	account map[string]interface{},
	fingerprint string,
	userAgent string,
	cfClearance string,
	cookie string,
) GrokHeaders {
	// Extract auth tokens from account
	ct0, _ := account["ct0"].(string)
	authToken, _ := account["auth_token"].(string)

	// Build cookie string
	// From decompiled: cookie construction with auth_token, ct0, cf_clearance
	cookieParts := []string{}
	if authToken != "" {
		cookieParts = append(cookieParts, "auth_token="+authToken)
	}
	if ct0 != "" {
		cookieParts = append(cookieParts, "ct0="+ct0)
	}
	if cfClearance != "" {
		cookieParts = append(cookieParts, "cf_clearance="+cfClearance)
	}
	if cookie != "" {
		cookieParts = append(cookieParts, cookie)
	}

	headers := GrokHeaders{
		"Content-Type":    "application/json",
		"Accept":          "*/*",
		"Accept-Language": "en-US,en;q=0.9",
		"Origin":          grokAPIBase,
		"Referer":         grokAPIBase + "/",
		"Cookie":          strings.Join(cookieParts, "; "),
	}

	// CSRF token
	if ct0 != "" {
		headers["X-Csrf-Token"] = ct0
	}

	// User-Agent with fingerprint
	if userAgent != "" {
		headers["User-Agent"] = userAgent
	}

	return headers
}

// ============================================================================
// buildVideoPayload
// ============================================================================

// buildVideoPayload constructs the payload for video generation requests.
// From VideoGenerations (@ 0x161bc00): buildVideoPayload called after
// headers are constructed.
func buildVideoPayload(
	prompt string,
	mediaPostID string,
	conversationID string,
) map[string]interface{} {
	return map[string]interface{}{
		"prompt":         prompt,
		"mediaPostId":    mediaPostID,
		"conversationId": conversationID,
	}
}

// ============================================================================
// Browser Fingerprint Generation
// ============================================================================

// GetBrowserFingerprint returns a cached or newly generated browser fingerprint.
// From decompiled: kiro2api_internal_logic_grok_sGrok_GetBrowserFingerprint
func (s *sGrok) GetBrowserFingerprint() string {
	if s.browserFingerprint != "" {
		return s.browserFingerprint
	}
	s.browserFingerprint = generateFingerprint()
	return s.browserFingerprint
}

// GetCfClearance returns the cached Cloudflare clearance cookie.
// From decompiled: kiro2api_internal_logic_grok_sGrok_GetCfClearance
func (s *sGrok) GetCfClearance() string {
	return s.cfClearance
}

// generateFingerprint generates a random browser fingerprint string.
// From decompiled: uses runtime_rand() and hex encoding
func generateFingerprint() string {
	b := make([]byte, 16)
	rand.Read(b)
	return hex.EncodeToString(b)
}

// ============================================================================
// buildImagePayload
// ============================================================================

// buildImagePayload constructs the payload for image generation requests.
func buildImagePayload(prompt string, count int) map[string]interface{} {
	return map[string]interface{}{
		"prompt": prompt,
		"count":  count,
	}
}

// ============================================================================
// Model Mapping
// ============================================================================

// mapModelName maps OpenAI model names to Grok model option IDs.
func mapModelName(model string) string {
	switch {
	case strings.Contains(model, "grok-3"):
		return "grok-3"
	case strings.Contains(model, "grok-2"):
		return "grok-2"
	case strings.Contains(model, "grok-vision"):
		return "grok-2-vision"
	default:
		return model
	}
}

// formatSystemPrompt formats the system prompt for Grok API.
// Returns empty string if no system message found.
func formatSystemPrompt(messages []map[string]interface{}) string {
	for _, msg := range messages {
		role, _ := msg["role"].(string)
		if role != "system" {
			continue
		}
		content := msg["content"]
		switch c := content.(type) {
		case string:
			return strings.TrimSpace(c)
		case []interface{}:
			var parts []string
			for _, item := range c {
				if m, ok := item.(map[string]interface{}); ok {
					if m["type"] == "text" {
						if t, ok := m["text"].(string); ok {
							parts = append(parts, t)
						}
					}
				}
			}
			return strings.TrimSpace(strings.Join(parts, "\n"))
		}
	}
	return ""
}

// generateConversationID generates a new conversation ID.
func generateConversationID() string {
	b := make([]byte, 16)
	rand.Read(b)
	return fmt.Sprintf("%x-%x-%x-%x-%x", b[0:4], b[4:6], b[6:8], b[8:10], b[10:16])
}
