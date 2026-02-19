package claudeapi

import (
	"crypto/sha256"
	"encoding/hex"
	"encoding/json"
	"fmt"
	"strings"
)

// injectClaudeCodeContext modifies the request body JSON to inject Claude Code
// thinking mode context. It parses the "system" field, identifies text blocks
// with "type":"text", and prepends thinking mode XML tags.
//
// Decompiled from: claudeapi.injectClaudeCodeContext @ 0x13934c0 (3424B)
//
// Flow:
//  1. Unmarshal request body into map[string]interface{}
//  2. Look up "system" key in the map
//  3. If "system" is a string → check if it matches known thinking patterns
//     - Compare against two known pattern strings (PTR_DAT_02de02b0, PTR_DAT_02de02c0)
//     - If match → set hasThinking = true
//     - Wrap string into [{type: "text", text: <value>}] array format
//  4. If "system" is []interface{} (array of content blocks):
//     - Iterate each block
//     - For each block that is map[string]interface{}:
//       - Check block["type"] == "text" (len 4, DAT_01c397b2)
//       - Compare block["text"] against two known thinking mode patterns
//       - If match → set hasThinking = true
//     - Collect all blocks into a new slice
//  5. If hasThinking is still false:
//     - Create a new text block: {type: "text", text: <thinking_context>}
//     - Append to the system blocks array
//  6. Assign modified "system" back to the map
//  7. Compute SHA256 hash of the content for cache key
//  8. Look up "max_tokens" (len 10) → extract thinking budget
//     - If not found, try "metadata" (len 8) → "thinking" (len 7)
//       → extract from nested path, strip prefix after "budget: " (len 9)
//  9. Build thinking context string:
//     - Concatenate: thinkingModeEnabled + account.ThinkingBudget + "\n" + existingContext
//  10. Create metadata map with "context" key (len 7)
//  11. Marshal back to JSON and return
//
// Parameters:
//   - body: raw request body bytes
//   - account: ClaudeApiAccount (for thinking budget config)
//
// Returns:
//   - modified body bytes (or original if unmarshal fails)
func injectClaudeCodeContext(body []byte, thinkingBudget string, existingContext string) []byte {
	// Step 1: Unmarshal into generic map
	var requestMap map[string]interface{}
	if err := json.Unmarshal(body, &requestMap); err != nil {
		return body // return original on parse failure
	}

	// Step 2: Look up "system" key
	systemVal, hasSystem := requestMap["system"]
	if !hasSystem {
		return body
	}

	hasThinking := false
	var systemBlocks []interface{}

	// Step 3/4: Handle "system" as string or array
	switch sv := systemVal.(type) {
	case string:
		// Check if the string itself is a known thinking pattern
		// Binary compares against two constant strings:
		// PTR_DAT_02de02b0 (len matches "type") and PTR_DAT_02de02c0
		if sv == "text" || sv == "thinking" {
			hasThinking = true
		}

		// Wrap string into content block format
		block := map[string]interface{}{
			"type": "text", // len 4
			"text": sv,     // len 4
		}
		systemBlocks = []interface{}{block}

	case []interface{}:
		// Iterate content blocks
		for _, item := range sv {
			blockMap, ok := item.(map[string]interface{})
			if !ok {
				systemBlocks = append(systemBlocks, item)
				continue
			}

			// Check if block["type"] == "text"
			blockType, _ := blockMap["type"].(string)

			if blockType == "text" {
				// Check block["text"] against known thinking patterns
				blockText, _ := blockMap["text"].(string)

				// Compare against two known thinking mode marker strings
				// PTR_DAT_02de02b0 = thinkingModeEnabled pattern
				// PTR_DAT_02de02c0 = thinkingModeDisabled pattern
				if blockText == thinkingModeEnabled || blockText == thinkingModeDisabled {
					hasThinking = true
				}
			}

			systemBlocks = append(systemBlocks, item)
		}

	default:
		return body
	}

	// Step 5: If no thinking block found, inject one
	if !hasThinking {
		thinkingBlock := map[string]interface{}{
			"type": "text",
			"text": buildThinkingContext(thinkingBudget),
		}
		// Prepend the thinking block (insert at beginning)
		newBlocks := make([]interface{}, 0, len(systemBlocks)+1)
		newBlocks = append(newBlocks, thinkingBlock)
		newBlocks = append(newBlocks, systemBlocks...)
		systemBlocks = newBlocks
	}

	// Step 6: Assign modified system blocks back
	requestMap["system"] = systemBlocks

	// Step 7: Compute SHA256 content hash
	contentBytes, _ := json.Marshal(requestMap["system"])
	hash := sha256.Sum256(contentBytes)
	contentHash := hex.EncodeToString(hash[:])

	// Step 8: Extract thinking budget from request
	// Look for "max_tokens" (len 10) in the request
	var maxThinkingTokens string
	if mt, ok := requestMap["max_tokens"]; ok {
		maxThinkingTokens = fmt.Sprintf("%v", mt)
		// Remove "max_tokens" from the map if it was a thinking-specific field
		delete(requestMap, "max_tokens")
	} else {
		// Try nested path: "metadata" → "thinking" → extract budget
		if metadata, ok := requestMap["metadata"].(map[string]interface{}); ok {
			if thinking, ok := metadata["thinking"].(string); ok {
				// Strip prefix "budget: " (len 9) if present
				idx := strings.Index(thinking, "budget: ")
				if idx >= 0 {
					maxThinkingTokens = thinking[idx+len("budget: "):]
				}
			}
		}
	}
	_ = maxThinkingTokens // used in context building

	// Step 9: Build the full thinking context string
	// Concatenation: thinkingModeTag + thinkingBudget + "\n" + existingContext
	thinkingContext := buildFullContext(thinkingBudget, existingContext, contentHash)

	// Step 10: Create/update metadata with context
	metadataMap, ok := requestMap["metadata"].(map[string]interface{})
	if !ok {
		metadataMap = make(map[string]interface{})
	}
	metadataMap["context"] = thinkingContext
	requestMap["metadata"] = metadataMap

	// Step 11: Marshal back to JSON
	result, err := json.Marshal(requestMap)
	if err != nil {
		return body
	}
	return result
}

// Known thinking mode marker strings (from binary constants)
const (
	// These are the two constant strings compared against in the binary
	// at PTR_DAT_02de02b0 and PTR_DAT_02de02c0
	thinkingModeEnabled  = "<thinking_mode>enabled</thinking_mode>"
	thinkingModeDisabled = "<thinking_mode>disabled</thinking_mode>"
)

// buildThinkingContext creates the thinking mode XML tag with budget.
// Template: "<thinking_mode>enabled</thinking_mode><max_thinking_length>%d</max_thinking_length>"
func buildThinkingContext(budget string) string {
	if budget == "" {
		return thinkingModeEnabled
	}
	return fmt.Sprintf("%s<max_thinking_length>%s</max_thinking_length>", thinkingModeEnabled, budget)
}

// buildFullContext concatenates the thinking context with existing context.
// Binary pattern: runtime_concatstring2 called 3 times:
//   1. contentHash + "," (separator)
//   2. thinkingBudget + "\n"
//   3. existingContext + "\n"
func buildFullContext(thinkingBudget string, existingContext string, contentHash string) string {
	parts := []string{contentHash}
	result := strings.Join(parts, ",")

	if thinkingBudget != "" {
		result = thinkingBudget + "\n" + result
	}
	if existingContext != "" {
		result = existingContext + "\n" + result
	}

	return result
}

// ExtractSessionId extracts a session identifier from the request body.
// Symbol: kiro2api/internal/logic/claudeapi.ExtractSessionId (384B @ 0x1394220)
//
// This is a standalone function (not a method on sClaudeApi).
// It parses the body to find a session key/ID for concurrent request tracking.
func ExtractSessionId(body []byte) string {
	var requestMap map[string]interface{}
	if err := json.Unmarshal(body, &requestMap); err != nil {
		return ""
	}

	// Look for session-related fields in the request
	// The binary uses string comparison with specific field names
	if sid, ok := requestMap["session_id"].(string); ok {
		return sid
	}

	// Check metadata for session info
	if metadata, ok := requestMap["metadata"].(map[string]interface{}); ok {
		if sid, ok := metadata["session_id"].(string); ok {
			return sid
		}
	}

	return ""
}
