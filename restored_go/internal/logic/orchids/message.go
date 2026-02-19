package orchids

// message.go — Message content extraction for the Orchids channel.
//
// Two core functions:
//   - extractMessageContent (0x1754f40): Extracts text/image/document/tool content from Orchids messages
//   - extractUserMessage    (0x1753420): Finds the last user message in conversation history
//
// The Orchids message format uses a content array where each element is a map with:
//   { "type": "text"|"image"|"document"|"thinking"|"reasoning"|"input_text"|"tool_use"|"tool_result",
//     "text": "...",           // for text type
//     "source": { "media_type": "...", "data": "..." },  // for image type
//     "name": "...",           // for tool_use type
//     "id": "...",             // for tool_use type
//     "input": { ... },        // for tool_use type
//   }

import (
	"encoding/json"
	"fmt"
	"strings"
)

// ============================================================================
// extractMessageContent
// ============================================================================

// extractMessageContent extracts text content from an Orchids message's content field.
// Symbol: kiro2api/internal/logic/orchids.extractMessageContent (@ 0x1754f40)
//
// The content field can be:
//   - A string (type == &DAT_0194e220 / string type) → return directly
//   - A slice of maps (type == &DAT_0192e960 / slice type) → iterate and extract
//   - nil → return empty
//
// For slice content, each element is checked by "type" field:
//   - "text"        → extract "text" field, append to text parts
//   - "image"       → extract source.media_type + source.data, format as markdown
//   - "document"    → extract source.data, format as markdown
//   - "tool_use"    → extract id, name, input, format as tool_use block
//   - "tool_result" → parse via parseToolResult, format as tool_result block
//   - "thinking"    → skip (filtered out)
//   - "reasoning"   → skip (filtered out)
//   - "input_text"  → skip (filtered out)
//
// Returns: concatenated text string, tool results slice
func extractMessageContent(
	content interface{},
	contentType interface{},
) (string, []ToolResult) {
	if contentType == nil {
		return "", nil
	}

	// Case 1: content is a plain string
	if str, ok := content.(string); ok {
		return str, nil
	}

	// Case 2: content is a slice of content blocks
	contentSlice, ok := content.([]interface{})
	if !ok {
		return "", nil
	}

	var textParts []string
	var toolResults []ToolResult

	for _, item := range contentSlice {
		block, ok := item.(map[string]interface{})
		if !ok {
			continue
		}

		// Get the "type" field
		// Decompiled: mapaccess1_faststr(4, ..., "type")
		blockType, _ := getStringField(block, keyType)

		switch blockType {
		case typeThinking, typeReasoning, typeInputText:
			// Skip thinking/reasoning/input_text blocks
			// Decompiled: checks for "thinking" (8 bytes, 0x676e696b6e696874),
			// "reasoning" (9 bytes), "input_text" (10 bytes) → continue
			continue

		case typeText:
			// Extract "text" field
			// Decompiled: mapaccess1_faststr(4) for "text" key
			if text, ok := getStringField(block, keyData); ok && text != "" {
				// Check for "<search_quality_reflection>" marker
				// Decompiled: internal_stringslite_Index(0x11) — 17 bytes = "<search_quality_r..."
				if !strings.Contains(text, "<search_quality_reflection>") {
					text = strings.TrimSpace(text)
					if text != "" {
						textParts = append(textParts, text)
					}
				}
			}

		case typeImage:
			// Extract image: source.media_type + source.data
			// Decompiled: mapaccess1_faststr(6) for "source" → mapaccess1_faststr(10) for "media_type"
			//             + mapaccess1_faststr(4) for "data"
			if source, ok := block[keySource].(map[string]interface{}); ok {
				mediaType, _ := getStringField(source, keyMediaType)
				data, _ := getStringField(source, keyData)
				// Format: ![image](data:media_type;base64,data)
				// Decompiled: fmt_Sprintf with 2 args, result length 0xd (13 = "![image](...)")
				formatted := fmt.Sprintf("![image](data:%s;base64,%s)", mediaType, data)
				textParts = append(textParts, formatted)
			}

		case typeDocument:
			// Extract document: source.data
			// Decompiled: mapaccess1_faststr(6) for "source" → mapaccess1_faststr(4) for "data"
			if source, ok := block[keySource].(map[string]interface{}); ok {
				data, _ := getStringField(source, keyData)
				// Format: [document](data)
				// Decompiled: fmt_Sprintf with 1 arg, result length 0xd
				formatted := fmt.Sprintf("[document](%s)", data)
				textParts = append(textParts, formatted)
			}

		case typeToolUse:
			// Extract tool_use: id, name, input
			// Decompiled: mapaccess1_faststr(2) for "id", mapaccess1_faststr(4) for "name",
			//             mapaccess1_faststr(5) for "input"
			id, _ := getStringField(block, keyID)
			name, _ := getStringField(block, keyName)

			// Marshal input to JSON string
			var inputStr string
			if input, ok := block[keyInput]; ok {
				inputBytes, err := json.Marshal(input)
				if err == nil {
					inputStr = string(inputBytes)
				}
			}

			// Format: <tool_use id="..." name="..." input="...">
			// Decompiled: fmt_Sprintf with 3 args, result length 0x20 (32)
			formatted := fmt.Sprintf(`<tool_use id="%s" name="%s" input="%s">`, id, name, inputStr)
			textParts = append(textParts, formatted)

		case typeToolResult:
			// Parse tool_result via parseToolResult
			// Decompiled: kiro2api_internal_logic_orchids_parseToolResult()
			// Returns a ToolResult struct (0x38 bytes)
			tr := parseToolResult(block)
			if tr != nil {
				toolResults = append(toolResults, *tr)

				// If tool result has content with name, format as text
				// Decompiled: checks plStack_130[1] != 0 && *(long)(*plStack_130 + 8) != 0
				if tr.Name != "" && tr.ToolUseID != "" {
					// Format: <tool_result name="..." tool_use_id="...">
					// Decompiled: fmt_Sprintf with 2 args, result length 0x23 (35)
					formatted := fmt.Sprintf(`<tool_result name="%s" tool_use_id="%s">`, tr.Name, tr.ToolUseID)
					textParts = append(textParts, formatted)
				}
			}
		}
	}

	// Join all text parts with newline separator
	// Decompiled: strings_Join(&DAT_01f34d88, 1, ...) — separator is "\n" (1 byte)
	result := strings.Join(textParts, "\n")
	return result, toolResults
}

// ============================================================================
// extractUserMessage
// ============================================================================

// extractUserMessage extracts the last user message text from the conversation.
// Symbol: kiro2api/internal/logic/orchids.extractUserMessage (@ 0x1753420)
//
// Algorithm:
//  1. Iterate messages from the end (lVar17 = len-1, decrement)
//  2. For each message, check if role == "user" (4 bytes, 0x72657375)
//  3. If content is a string → TrimSpace and return if non-empty
//  4. If content is a slice → iterate blocks looking for "text" type
//     - Skip blocks with "<search_quality_reflection>" marker
//     - Collect text parts, join with "\n", TrimSpace
//  5. If no text found in current user message, check for tool_result blocks
//     - If only tool_results found (bVar2=true), return special marker
//  6. Continue to previous messages if current user message has no text
//
// Special return values:
//   - Normal text: the extracted user message string
//   - Tool-only:   returns "&DAT_01ca80bc" marker (indicates tool-result-only message)
//   - Empty:       returns nil/empty (no user message found)
func extractUserMessage(messages []OrchidsConversationMessage) (string, bool) {
	if len(messages) == 0 {
		return "", false
	}

	// Iterate from the end of the conversation
	for i := len(messages) - 1; i >= 0; i-- {
		msg := messages[i]

		// Check if role == "user"
		// Decompiled: lStack_a0 == 4 && *piStack_a8 == 0x72657375
		if msg.Role != "user" {
			continue
		}

		// Case 1: Content is a plain string
		if msg.ContentType == "string" {
			if str, ok := msg.Content.(string); ok {
				str = strings.TrimSpace(str)
				if str != "" {
					return str, false
				}
			}
		}

		// Case 2: Content is a slice of content blocks
		if msg.ContentType == "slice" {
			contentSlice, ok := msg.Content.([]interface{})
			if !ok {
				continue
			}

			var textParts []string
			hasToolResultOnly := false
			hasText := false

			for _, item := range contentSlice {
				block, ok := item.(map[string]interface{})
				if !ok {
					continue
				}

				blockType, _ := getStringField(block, keyType)

				switch blockType {
				case typeText:
					// Extract text, check for search_quality_reflection marker
					if text, ok := getStringField(block, keyData); ok {
						// Decompiled: internal_stringslite_Index(0x11) — check for marker
						if strings.Contains(text, "<search_quality_reflection>") {
							continue
						}
						text = strings.TrimSpace(text)
						if text != "" {
							textParts = append(textParts, text)
							hasText = true
						}
					}

				case typeImage:
					// Format image as markdown
					if source, ok := block[keySource].(map[string]interface{}); ok {
						mediaType, _ := getStringField(source, keyMediaType)
						data, _ := getStringField(source, keyData)
						formatted := fmt.Sprintf("![image](data:%s;base64,%s)", mediaType, data)
						textParts = append(textParts, formatted)
						hasText = true
					}

				case typeDocument:
					// Format document
					if source, ok := block[keySource].(map[string]interface{}); ok {
						data, _ := getStringField(source, keyData)
						formatted := fmt.Sprintf("[document](%s)", data)
						textParts = append(textParts, formatted)
						hasText = true
					}

				case typeToolResult:
					// Parse tool result
					tr := parseToolResult(block)
					if tr != nil {
						hasToolResultOnly = true
					}
				}
			}

			if hasText {
				result := strings.Join(textParts, "\n")
				result = strings.TrimSpace(result)
				if result != "" {
					return result, false
				}
			}

			// If we found tool results but no text, mark as tool-result-only
			// Decompiled: bVar2=true && uStack_130 != 0 → return &DAT_01ca80bc
			if hasToolResultOnly && !hasText {
				return "", true // tool-result-only marker
			}
		}
	}

	return "", false
}

// ============================================================================
// OrchidsConversationMessage
// ============================================================================

// OrchidsConversationMessage represents a message in the conversation history.
// Size: 0x30 bytes (48 bytes) per message in the decompiled array.
// Fields at offsets:
//   0x00: Role (string ptr)
//   0x08: Role length
//   0x10: ContentType (interface type ptr)
//   0x18: ContentType (interface data ptr)
//   0x20: Content data
//   0x28: Flags (bool fields)
//   0x2c: Additional flags
type OrchidsConversationMessage struct {
	Role        string      // "user", "assistant", "system"
	ContentType string      // "string" or "slice"
	Content     interface{} // string or []interface{}
	Flags       uint32      // packed boolean flags
}

// ============================================================================
// Helpers
// ============================================================================

// getStringField safely extracts a string value from a map.
func getStringField(m map[string]interface{}, key string) (string, bool) {
	v, ok := m[key]
	if !ok {
		return "", false
	}
	s, ok := v.(string)
	return s, ok
}

// parseToolResult parses a tool_result content block into a ToolResult struct.
// From decompiled: kiro2api_internal_logic_orchids_parseToolResult()
// The tool_result block has:
//   { "type": "tool_result", "tool_use_id": "...", "content": "...", "is_error": bool }
func parseToolResult(block map[string]interface{}) *ToolResult {
	if block == nil {
		return nil
	}

	tr := &ToolResult{}

	// Extract tool_use_id
	if id, ok := getStringField(block, "tool_use_id"); ok {
		tr.ToolUseID = id
	}

	// Extract name (if present)
	if name, ok := getStringField(block, keyName); ok {
		tr.Name = name
	}

	// Extract content
	tr.Content = block[keyContent]

	// Extract is_error flag
	if isErr, ok := block["is_error"].(bool); ok {
		tr.IsError = isErr
	}

	// Extract has_input flag (from the 0x38 offset)
	if hasInput, ok := block["has_input"].(bool); ok {
		tr.HasInput = hasInput
	}

	return tr
}
