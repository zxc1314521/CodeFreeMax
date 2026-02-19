package grok

// message.go — Message extraction and transformation for the Grok channel.
//
// Functions:
//   - extractMessages  (@ 0x1603860) — Extract and transform OpenAI messages to Grok format
//
// The extractMessages function converts OpenAI-format messages (with roles and
// content arrays) into Grok's internal format. It handles:
//   - Text content extraction from string or array content
//   - File/image attachment detection ("file" and "image_url" types)
//   - Input audio content detection ("input_audio" type)
//   - Role-based message grouping
//   - Last user message identification for response formatting
//
// From decompiled extractMessages (@ 0x1603860, ~600 lines C pseudocode):
//   - Iterates over input messages (param array)
//   - For each message, checks content type via interface type assertion
//   - If content is []interface{} (array), iterates items checking "type" field:
//     * "file" → returns error if fileOnly flag set, else extracts "url"/"data"
//     * "text" → extracts "text" field, trims whitespace, appends to parts
//     * "image_url" → extracts "url" from nested map
//     * "input_audio" → returns error if fileOnly flag set, else extracts "data"/"url"
//   - If content is string → trims whitespace, uses directly
//   - Groups consecutive same-role messages
//   - Finds last "user" message index for special handling
//   - Formats final output with role prefixes: "[user]: content" or "[assistant]: content"

import (
	"fmt"
	"strings"
)

// ============================================================================
// extractMessages
// ============================================================================

// extractMessages converts OpenAI-format messages into Grok conversation format.
//
// Symbol: kiro2api/internal/logic/grok.extractMessages (@ 0x1603860)
//
// Parameters:
//   - messages: slice of OpenAI message maps (role, content)
//   - fileOnly: if true, reject file/audio content with error
//
// Returns:
//   - formatted string with role-prefixed messages joined by newlines
//   - error if invalid content types encountered
//
// From decompiled (key patterns):
//   - 0x656c6966 = "file" (4 bytes) — line 2289
//   - 0x74786574 = "text" (4 bytes) — line 2362
//   - 0x72755f6567616d69 + 'l' = "image_url" (9 bytes) — line 2401
//   - 0x75615f7475706e69 + "dio" = "input_audio" (11 bytes) — line 2445-2446
//   - 0x72657375 = "user" (4 bytes) — line 2636
//   - strings.TrimSpace called on text content — line 2369
//   - strings.Join with "\n" separator — line 2572
//   - Final join with "\n\n" separator — line 2726
//   - fmt.Sprintf for role prefix formatting — line 2693
func extractMessages(messages []map[string]interface{}, fileOnly bool) (string, error) {
	type messageEntry struct {
		role    string
		content string
		parts   []string
	}

	var entries []messageEntry
	var imageURLs []string
	var fileURLs []string

	for _, msg := range messages {
		role, _ := msg["role"].(string)
		content := msg["content"]

		var textParts []string

		switch c := content.(type) {
		case string:
			// Simple string content
			trimmed := strings.TrimSpace(c)
			if trimmed != "" {
				textParts = append(textParts, trimmed)
			}

		case []interface{}:
			// Array content — iterate items
			for _, item := range c {
				itemMap, ok := item.(map[string]interface{})
				if !ok {
					continue
				}

				itemType, _ := itemMap["type"].(string)

				switch itemType {
				case "file":
					// File attachment
					// From decompiled: if fileOnly flag set, return error
					if fileOnly {
						return "", fmt.Errorf("file content not supported in this mode")
					}
					// Extract URL or data from file content
					if urlVal, ok := itemMap["url"].(string); ok && urlVal != "" {
						fileURLs = append(fileURLs, urlVal)
					} else if dataVal, ok := itemMap["data"].(string); ok && dataVal != "" {
						fileURLs = append(fileURLs, dataVal)
					}

				case "text":
					// Text content — extract and trim
					// From decompiled: runtime_mapaccess1_faststr(4, "text")
					// then strings_TrimSpace on the value
					if textVal, ok := itemMap["text"].(string); ok {
						trimmed := strings.TrimSpace(textVal)
						if trimmed != "" {
							textParts = append(textParts, trimmed)
						}
					}

				case "image_url":
					// Image URL — extract from nested map
					// From decompiled: 0x72755f6567616d69 + 'l' = "image_url"
					// then mapaccess1_faststr for "url" within the nested map
					if urlMap, ok := itemMap["image_url"].(map[string]interface{}); ok {
						if urlVal, ok := urlMap["url"].(string); ok && urlVal != "" {
							imageURLs = append(imageURLs, urlVal)
						}
					}

				case "input_audio":
					// Input audio content
					// From decompiled: 0x75615f7475706e69 + "dio" = "input_audio"
					// if fileOnly → return error
					if fileOnly {
						return "", fmt.Errorf("input_audio content not supported in this mode")
					}
					// Extract URL or data
					if urlVal, ok := itemMap["url"].(string); ok && urlVal != "" {
						fileURLs = append(fileURLs, urlVal)
					} else if dataVal, ok := itemMap["data"].(string); ok && dataVal != "" {
						fileURLs = append(fileURLs, dataVal)
					}
				}
			}

		default:
			// Skip unknown content types
			continue
		}

		if len(textParts) > 0 {
			// Join multiple text parts with newline
			// From decompiled: strings_Join(&DAT_01f34d88, 1, ...) — separator "\n"
			joined := strings.Join(textParts, "\n")
			entries = append(entries, messageEntry{
				role:    role,
				content: joined,
				parts:   textParts,
			})
		}
	}

	if len(entries) == 0 {
		return "", nil
	}

	// Find last "user" message index
	// From decompiled: reverse scan checking role == "user" (0x72657375)
	lastUserIdx := -1
	for i := len(entries) - 1; i >= 0; i-- {
		if entries[i].role == "user" {
			lastUserIdx = i
			break
		}
	}

	// Format messages with role prefixes
	// From decompiled: fmt_Sprintf with format string for role prefix
	// Non-last-user messages get "[role]: content" format
	// Last user message gets special handling
	var formatted []string
	for i, entry := range entries {
		if i == lastUserIdx {
			// Last user message — include as-is (no role prefix)
			// From decompiled: the last user message is assigned directly
			formatted = append(formatted, entry.content)
		} else {
			// Other messages — format with role prefix
			// From decompiled: fmt_Sprintf(2, 2, ...) with format pattern
			formatted = append(formatted, fmt.Sprintf("[%s]: %s", entry.role, entry.content))
		}
	}

	// Join all formatted messages with double newline
	// From decompiled: strings_Join(&DAT_01f35098, 2, ...) — separator "\n\n"
	return strings.Join(formatted, "\n\n"), nil
}

// NOTE: buildConversationMessages is defined in cache.go — removed duplicate here.
