package antigravity

// message.go — Message conversion from OpenAI format to Google Gemini format.
//
// Core functions:
//   - convertMessagesToContents (5120B @ 0x17b0660): main conversion pipeline
//   - convertContentToPartsWithMapping (2816B @ 0x17b2580): content → parts with type mapping
//   - mergeAdjacentRoles: merges consecutive same-role messages
//   - cleanThinkingFieldsRecursive: removes "thinking" fields when model doesn't support it
//   - getContentText: extracts text string from a content map
//
// The conversion pipeline:
//  1. Strip "cache_control" fields from all messages (DAT_01a233a0 map delete)
//  2. Convert "tool" role messages into map[string]interface{} with functionCall structure
//  3. First pass: resolve "tool_result" → look up function name from tool_use map
//  4. Second pass: resolve "tool_use" → look up function ID from tool_use map
//  5. Role normalization: "assistant" → "model", empty → "user", skip "system"
//  6. Convert content to Gemini "parts" format via convertContentToPartsWithMapping
//  7. Merge adjacent same-role messages via mergeAdjacentRoles

import (
	"strings"
)

// ============================================================================
// Content Part Types (from hex string comparisons in decompiled code)
// ============================================================================

// Hex string constants found in the decompiled code:
//   0x74786574 = "text" (4 bytes)
//   0x676e696b6e696874 = "thinking" (8 bytes)
//   0x67616d69 + 'e' = "image" (5 bytes)
//   0x6573755f6c6f6f74 = "tool_use" (8 bytes)
//   0x7365725f6c6f6f74 + 0x6c75 + 't' = "tool_result" (11 bytes)

// ============================================================================
// convertMessagesToContents
// ============================================================================

// convertMessagesToContents converts OpenAI-format messages to Gemini "contents" format.
// Symbol: kiro2api/internal/logic/antigravity.convertMessagesToContents (5120B @ 0x17b0660)
//
// This is the most complex function in the antigravity channel (5120 bytes).
// It performs a multi-pass transformation pipeline.
//
// Input: []map[string]interface{} (OpenAI messages with role, content, tool_calls, etc.)
// Output: []map[string]interface{} (Gemini contents with role and parts)
func (s *sAntigravity) convertMessagesToContents(
	messages []map[string]interface{},
) []map[string]interface{} {

	// === Pass 0: Strip "cache_control" from all messages and their content parts ===
	// The decompiled code checks for DAT_01a233a0 (map type) and calls runtime_mapdelete_faststr
	// on the "cache_control" key.
	for _, msg := range messages {
		delete(msg, "cache_control")

		// Also strip from nested content arrays (when content is []interface{})
		if contentArr, ok := msg["content"].([]interface{}); ok {
			for _, item := range contentArr {
				if itemMap, ok := item.(map[string]interface{}); ok {
					delete(itemMap, "cache_control")
				}
			}
		}
	}

	// === Pass 1: Convert "tool" role messages to functionResponse format ===
	// When role == "tool" (0x6c6f6f74, 4 bytes), create a functionResponse part.
	// The decompiled code creates a map with:
	//   "type" → "functionResponse" (PTR_DAT_01f3a180)
	//   "tool_call_id" → msg["tool_call_id"]
	//   "content" → msg["content"] (wrapped in []interface{})
	var converted []map[string]interface{}
	for _, msg := range messages {
		role, _ := msg["role"].(string)

		if role == "tool" {
			// Convert tool message to functionResponse format
			toolCallID, _ := msg["tool_call_id"].(string)
			content := msg["content"]

			responseMap := map[string]interface{}{
				"type":         "functionResponse",
				"tool_call_id": toolCallID,
				"content":      content,
			}

			converted = append(converted, map[string]interface{}{
				"role":    "user",
				"content": []interface{}{responseMap},
			})
		} else {
			converted = append(converted, msg)
		}
	}

	// === Pass 2: Build tool_use → tool_result mapping ===
	// Iterates through converted messages looking for content arrays.
	// For each part with type == "tool_result" (11 bytes: 0x7365725f6c6f6f74 + "ult"),
	// looks up the "type" field and if it matches "tool_result", marks it in a set.
	toolResultSet := make(map[string]bool)
	for _, msg := range converted {
		if contentArr, ok := msg["content"].([]interface{}); ok {
			for _, item := range contentArr {
				if itemMap, ok := item.(map[string]interface{}); ok {
					partType, _ := itemMap["type"].(string)
					if partType == "tool_result" {
						// Look up the tool_call_id to find the corresponding tool_use
						if toolCallID, ok := itemMap["tool_call_id"].(string); ok && toolCallID != "" {
							toolResultSet[toolCallID] = true
						}
					}
				}
			}
		}
	}

	// === Pass 3: Resolve tool_use references ===
	// For each part with type == "tool_use" (8 bytes: 0x6573755f6c6f6f74),
	// look up "id" and "name" fields, and update the mapping.
	for _, msg := range converted {
		if contentArr, ok := msg["content"].([]interface{}); ok {
			for _, item := range contentArr {
				if itemMap, ok := item.(map[string]interface{}); ok {
					partType, _ := itemMap["type"].(string)
					if partType == "tool_use" {
						id, _ := itemMap["id"].(string)
						name, _ := itemMap["name"].(string)
						if id != "" && name != "" {
							// If this tool_use has a corresponding tool_result, mark it
							if _, hasResult := toolResultSet[id]; hasResult {
								itemMap["_has_result"] = true
							}
						}
					}
				}
			}
		}
	}

	// === Pass 4: Main conversion loop ===
	// Role normalization and content conversion.
	var result []map[string]interface{}
	var pendingToolUses []interface{}
	var pendingToolUseIDs []string

	for _, msg := range converted {
		role, _ := msg["role"].(string)
		content := msg["content"]
		contentType := msg["content"]
		_ = contentType

		// Role normalization:
		//   "assistant" (9 bytes: 0x6e61747369737361 + 't') → "model" (5 bytes: 0x65646f6d + 'l')
		//   empty → "user" (4 bytes: 0x01c3978a)
		//   "system" (6 bytes: 0x74737973 + 0x6d65) → skip (handled separately)
		if role == "assistant" {
			role = "model"
		}
		if role == "system" {
			// System messages are handled separately in buildAntigravityRequest
			continue
		}
		if role == "" {
			role = "user"
		}

		// Check if this is a "model" role with pending tool_calls
		if role == "model" && len(pendingToolUseIDs) > 0 {
			// Flush pending tool_use parts as functionCall entries
			var functionCallParts []interface{}
			for _, toolUseID := range pendingToolUseIDs {
				_ = toolUseID
			}
			for _, pending := range pendingToolUses {
				if pendingMap, ok := pending.(map[string]interface{}); ok {
					name, _ := pendingMap["name"].(string)
					id, _ := pendingMap["id"].(string)

					// Check if this tool_use has a result
					if _, hasResult := toolResultSet[id]; !hasResult {
						continue
					}

					// Build functionCall part
					fcPart := map[string]interface{}{
						"functionCall": map[string]interface{}{
							"name": name,
							"args": pendingMap["input"],
						},
					}
					functionCallParts = append(functionCallParts, fcPart)
				}
			}

			if len(functionCallParts) > 0 {
				result = append(result, map[string]interface{}{
					"role":  "model",
					"parts": functionCallParts,
				})
			}

			pendingToolUses = nil
			pendingToolUseIDs = nil
		}

		// Convert content to Gemini parts
		contentArr, isArray := content.([]interface{})
		if isArray {
			// Content is an array of parts — process each
			var toolUseParts []interface{}
			for _, item := range contentArr {
				if itemMap, ok := item.(map[string]interface{}); ok {
					partType, _ := itemMap["type"].(string)
					if partType == "tool_use" {
						toolUseParts = append(toolUseParts, itemMap)
						if id, ok := itemMap["id"].(string); ok {
							pendingToolUseIDs = append(pendingToolUseIDs, id)
						}
					}
				}
			}
			if len(toolUseParts) > 0 {
				pendingToolUses = append(pendingToolUses, toolUseParts...)
			}
		}

		// Convert content to parts via convertContentToPartsWithMapping
		parts := s.convertContentToPartsWithMapping(content)

		if parts != nil {
			geminiMsg := map[string]interface{}{
				"role":  role,
				"parts": parts,
			}
			result = append(result, geminiMsg)
		}
	}

	// Merge adjacent same-role messages
	result = mergeAdjacentRoles(result)

	return result
}

// ============================================================================
// convertContentToPartsWithMapping
// ============================================================================

// convertContentToPartsWithMapping converts a single message's content to Gemini parts format.
// Symbol: kiro2api/internal/logic/antigravity.(*sAntigravity).convertContentToPartsWithMapping (2816B @ 0x17b2580)
//
// Handles multiple content types:
//   - string → [{"text": content}]
//   - []interface{} with type-tagged parts:
//     - "text" → {"text": value}
//     - "thinking" → {"thought": true, "text": value}  (Gemini thinking mode)
//     - "image" → {"inlineData": {"mimeType": ..., "data": ...}}
//     - "tool_use" → {"functionCall": {"name": ..., "args": ...}}
//     - "tool_result" → {"functionResponse": {"name": ..., "response": {"content": ...}}}
func (s *sAntigravity) convertContentToPartsWithMapping(content interface{}) []interface{} {
	if content == nil {
		return nil
	}

	switch v := content.(type) {
	case string:
		// Simple string content → single text part
		if v == "" {
			return nil
		}
		return []interface{}{
			map[string]interface{}{
				"text": v,
			},
		}

	case []interface{}:
		// Array of typed content parts
		var parts []interface{}

		for _, item := range v {
			itemMap, ok := item.(map[string]interface{})
			if !ok {
				continue
			}

			partType, _ := itemMap["type"].(string)

			switch partType {
			case "text":
				// Text part: {"type": "text", "text": "..."}
				// → {"text": "..."}
				text, _ := itemMap["text"].(string)
				if text != "" {
					parts = append(parts, map[string]interface{}{
						"text": text,
					})
				}

			case "thinking":
				// Thinking part: {"type": "thinking", "thinking": "..."}
				// → {"thought": true, "text": "..."}
				// Hex: 0x676e696b6e696874 = "thinking" (8 bytes)
				thinking, _ := itemMap["thinking"].(string)
				if thinking != "" {
					parts = append(parts, map[string]interface{}{
						"thought": true,
						"text":    thinking,
					})
				}

			case "image":
				// Image part: {"type": "image", "source": {"media_type": ..., "data": ...}}
				// → {"inlineData": {"mimeType": ..., "data": ...}}
				// Hex: 0x67616d69 + 'e' = "image" (5 bytes)
				if source, ok := itemMap["source"].(map[string]interface{}); ok {
					mimeType, _ := source["media_type"].(string)
					data, _ := source["data"].(string)

					inlineData := map[string]interface{}{
						"mimeType": mimeType,
						"data":     data,
					}
					parts = append(parts, map[string]interface{}{
						"inlineData": inlineData,
					})
				}

			case "tool_use":
				// Tool use part: {"type": "tool_use", "id": ..., "name": ..., "input": ...}
				// → {"functionCall": {"name": ..., "args": ...}}
				// Hex: 0x6573755f6c6f6f74 = "tool_use" (8 bytes)
				name, _ := itemMap["name"].(string)
				id, _ := itemMap["id"].(string)
				input := itemMap["input"]

				fcPart := map[string]interface{}{
					"functionCall": map[string]interface{}{
						"name": name,
						"args": input,
					},
					"id": id,
				}
				parts = append(parts, fcPart)

			case "tool_result":
				// Tool result part: {"type": "tool_result", "tool_use_id": ..., "content": ...}
				// → {"functionResponse": {"name": ..., "response": {"content": ...}}}
				// Hex: 0x7365725f6c6f6f74 + 0x6c75 + 't' = "tool_result" (11 bytes)
				toolUseID, _ := itemMap["tool_use_id"].(string)
				resultContent := itemMap["content"]

				// Get the text content
				contentText := getContentText(resultContent)
				contentText = strings.TrimSpace(contentText)
				if contentText == "" {
					contentText = "No output returned."
				}

				frPart := map[string]interface{}{
					"functionResponse": map[string]interface{}{
						"name": toolUseID,
						"response": map[string]interface{}{
							"content": contentText,
						},
						"id": toolUseID,
					},
				}
				parts = append(parts, frPart)
			}
		}

		return parts

	default:
		return nil
	}
}

// ============================================================================
// Helper Functions
// ============================================================================

// mergeAdjacentRoles merges consecutive messages with the same role.
// Symbol: kiro2api/internal/logic/antigravity.mergeAdjacentRoles (referenced at end of convertMessagesToContents)
//
// Gemini API requires alternating user/model roles. This function merges
// consecutive same-role messages by combining their parts arrays.
func mergeAdjacentRoles(contents []map[string]interface{}) []map[string]interface{} {
	if len(contents) <= 1 {
		return contents
	}

	var merged []map[string]interface{}

	for _, msg := range contents {
		role, _ := msg["role"].(string)
		parts, _ := msg["parts"].([]interface{})

		if len(merged) > 0 {
			lastMsg := merged[len(merged)-1]
			lastRole, _ := lastMsg["role"].(string)

			if lastRole == role {
				// Same role — merge parts
				existingParts, _ := lastMsg["parts"].([]interface{})
				lastMsg["parts"] = append(existingParts, parts...)
				continue
			}
		}

		merged = append(merged, map[string]interface{}{
			"role":  role,
			"parts": parts,
		})
	}

	return merged
}

// cleanThinkingFieldsRecursive removes "thinking" type parts from content arrays.
// Symbol: kiro2api/internal/logic/antigravity.cleanThinkingFieldsRecursive
// Called when the model doesn't support thinking mode (bStack0000000000000030 == 0).
func cleanThinkingFieldsRecursive(content interface{}) {
	switch v := content.(type) {
	case []interface{}:
		for i := len(v) - 1; i >= 0; i-- {
			if itemMap, ok := v[i].(map[string]interface{}); ok {
				if partType, _ := itemMap["type"].(string); partType == "thinking" {
					// Remove thinking part by replacing with nil (will be filtered later)
					v[i] = nil
				}
			}
		}
	case map[string]interface{}:
		delete(v, "thinking")
	}
}

// getContentText extracts a text string from content which may be a string or a structured object.
// Symbol: kiro2api/internal/logic/antigravity.getContentText
func getContentText(content interface{}) string {
	if content == nil {
		return ""
	}

	switch v := content.(type) {
	case string:
		return v
	case []interface{}:
		// Look for the first text part
		for _, item := range v {
			if itemMap, ok := item.(map[string]interface{}); ok {
				if text, ok := itemMap["text"].(string); ok {
					return text
				}
			}
		}
	case map[string]interface{}:
		if text, ok := v["text"].(string); ok {
			return text
		}
		if text, ok := v["content"].(string); ok {
			return text
		}
	}

	return ""
}
