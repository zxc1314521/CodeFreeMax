package cursor

import (
	"encoding/json"
	"fmt"
	"strings"
)

// ============================================================================
// Message Content Parsing
// ============================================================================

// MessageContent represents a parsed message content block from OpenAI format.
// Used internally when converting OpenAI messages to Cursor's protobuf format.
type MessageContent struct {
	Type     string `json:"type"`               // "text", "image_url", "tool_use", "tool_result"
	Text     string `json:"text,omitempty"`
	ImageURL *struct {
		URL    string `json:"url"`
		Detail string `json:"detail,omitempty"`
	} `json:"image_url,omitempty"`
}

// ToolCall represents a tool call in the OpenAI message format.
type ToolCall struct {
	ID       string `json:"id"`
	Type     string `json:"type"`
	Function struct {
		Name      string `json:"name"`
		Arguments string `json:"arguments"`
	} `json:"function"`
}

// OpenAIMessage represents a message in the OpenAI chat completion format.
type OpenAIMessage struct {
	Role       string      `json:"role"`
	Content    interface{} `json:"content"`    // string or []MessageContent
	Name       string      `json:"name,omitempty"`
	ToolCalls  []ToolCall  `json:"tool_calls,omitempty"`
	ToolCallID string      `json:"tool_call_id,omitempty"`
}

// parseMessageContent extracts the text content and role from an OpenAI message.
// Symbol: kiro2api/internal/logic/cursor.parseMessageContent (2816B @ 0x17f6120)
//
// The function handles both string content and array content ([]MessageContent).
// From the decompiled code at line 568:
//   kiro2api_internal_logic_cursor_parseMessageContent()
//
// The 2816B size indicates complex content type switching and string extraction.
func parseMessageContent(msg *OpenAIMessage) (role string, text string) {
	if msg == nil {
		return "", ""
	}

	role = msg.Role

	switch content := msg.Content.(type) {
	case string:
		text = content
	case []interface{}:
		// Array of content blocks — extract text parts
		var parts []string
		for _, item := range content {
			if m, ok := item.(map[string]interface{}); ok {
				if t, ok := m["type"].(string); ok && t == "text" {
					if txt, ok := m["text"].(string); ok {
						parts = append(parts, txt)
					}
				}
			}
		}
		text = strings.Join(parts, "")
	}

	return role, text
}

// extractToolResultContent extracts the content from a tool_result message.
// Symbol: kiro2api/internal/logic/cursor.extractToolResultContent (544B @ 0x17f6c20)
//
// Tool results can contain text or structured content. This function
// normalizes them to a plain string for the Cursor protobuf format.
func extractToolResultContent(msg *OpenAIMessage) string {
	if msg == nil || msg.Content == nil {
		return ""
	}

	switch content := msg.Content.(type) {
	case string:
		return content
	case []interface{}:
		var parts []string
		for _, item := range content {
			if m, ok := item.(map[string]interface{}); ok {
				if t, ok := m["type"].(string); ok {
					switch t {
					case "text":
						if txt, ok := m["text"].(string); ok {
							parts = append(parts, txt)
						}
					case "image_url":
						// Image URLs in tool results are typically base64 data
						if imgURL, ok := m["image_url"].(map[string]interface{}); ok {
							if url, ok := imgURL["url"].(string); ok {
								parts = append(parts, fmt.Sprintf("[image: %s]", url))
							}
						}
					}
				}
			}
		}
		return strings.Join(parts, "\n")
	}

	return ""
}

// extractSystemPrompt extracts the system prompt from the messages array.
// Symbol: kiro2api/internal/logic/cursor.extractSystemPrompt (544B @ 0x17f7800)
//
// Scans the messages for a "system" role message and returns its content.
// From decompiled code at line 72:
//   lVar8 = kiro2api_internal_logic_cursor_extractSystemPrompt()
//
// The function is called early in buildCursorRequest to separate the system
// prompt from conversation messages.
func extractSystemPrompt(messages []OpenAIMessage) string {
	for _, msg := range messages {
		if msg.Role == roleSystem {
			_, text := parseMessageContent(&msg)
			return text
		}
	}
	return ""
}

// extractWorkingDirFromSystemPrompt extracts the working directory path
// from a Cursor-style system prompt.
// Symbol: kiro2api/internal/logic/cursor.extractWorkingDirFromSystemPrompt (480B @ 0x17f7a20)
//
// Cursor system prompts often contain a working directory reference like:
//   "You are working in /path/to/project"
// This function parses that out for use in the protobuf request.
func extractWorkingDirFromSystemPrompt(systemPrompt string) string {
	// Look for common patterns in Cursor system prompts
	markers := []string{
		"working directory is ",
		"working in ",
		"cwd: ",
	}

	for _, marker := range markers {
		idx := strings.Index(strings.ToLower(systemPrompt), marker)
		if idx >= 0 {
			rest := systemPrompt[idx+len(marker):]
			// Extract until newline or end of string
			if nlIdx := strings.IndexByte(rest, '\n'); nlIdx >= 0 {
				return strings.TrimSpace(rest[:nlIdx])
			}
			return strings.TrimSpace(rest)
		}
	}
	return ""
}

// extractWorkspacePath extracts the workspace path from the system prompt.
// Symbol: kiro2api/internal/logic/cursor.extractWorkspacePath (480B @ 0x17f7c00)
//
// Similar to extractWorkingDirFromSystemPrompt but looks for workspace-specific markers.
func extractWorkspacePath(systemPrompt string) string {
	markers := []string{
		"workspace: ",
		"project root: ",
		"repository: ",
	}

	for _, marker := range markers {
		idx := strings.Index(strings.ToLower(systemPrompt), marker)
		if idx >= 0 {
			rest := systemPrompt[idx+len(marker):]
			if nlIdx := strings.IndexByte(rest, '\n'); nlIdx >= 0 {
				return strings.TrimSpace(rest[:nlIdx])
			}
			return strings.TrimSpace(rest)
		}
	}
	return ""
}

// findMatchingBrace finds the index of the matching closing brace for a JSON object.
// Symbol: kiro2api/internal/logic/cursor.findMatchingBrace (192B @ 0x17fcf80)
//
// Used by parseBracketToolCalls to extract complete JSON objects from text.
func findMatchingBrace(s string, start int) int {
	depth := 0
	for i := start; i < len(s); i++ {
		switch s[i] {
		case '{':
			depth++
		case '}':
			depth--
			if depth == 0 {
				return i
			}
		}
	}
	return -1
}

// parseBracketToolCalls parses tool calls embedded in text using bracket notation.
// Symbol: kiro2api/internal/logic/cursor.parseBracketToolCalls (1280B @ 0x17fca80)
//
// Some models return tool calls inline in text using a bracket format like:
//   [tool_name({"arg": "value"})]
// This function extracts those into structured ToolCall objects.
func parseBracketToolCalls(text string) (cleanText string, toolCalls []ToolCall) {
	cleanText = text
	idx := 0

	for idx < len(cleanText) {
		// Find opening bracket
		openBracket := strings.Index(cleanText[idx:], "[")
		if openBracket < 0 {
			break
		}
		openBracket += idx

		// Find the function name and opening paren
		parenIdx := strings.Index(cleanText[openBracket:], "(")
		if parenIdx < 0 {
			idx = openBracket + 1
			continue
		}
		parenIdx += openBracket

		funcName := strings.TrimSpace(cleanText[openBracket+1 : parenIdx])
		if funcName == "" {
			idx = openBracket + 1
			continue
		}

		// Find the JSON argument object
		braceStart := strings.Index(cleanText[parenIdx:], "{")
		if braceStart < 0 {
			idx = parenIdx + 1
			continue
		}
		braceStart += parenIdx

		braceEnd := findMatchingBrace(cleanText, braceStart)
		if braceEnd < 0 {
			idx = braceStart + 1
			continue
		}

		// Find closing bracket
		closeBracket := strings.Index(cleanText[braceEnd:], "]")
		if closeBracket < 0 {
			idx = braceEnd + 1
			continue
		}
		closeBracket += braceEnd

		// Extract the JSON arguments
		argsJSON := cleanText[braceStart : braceEnd+1]

		// Validate JSON
		var jsonCheck json.RawMessage
		if json.Unmarshal([]byte(argsJSON), &jsonCheck) != nil {
			idx = closeBracket + 1
			continue
		}

		tc := ToolCall{
			ID:   fmt.Sprintf("call_%s", generateCursorKey()),
			Type: "function",
		}
		tc.Function.Name = funcName
		tc.Function.Arguments = argsJSON
		toolCalls = append(toolCalls, tc)

		// Remove the tool call from text
		cleanText = cleanText[:openBracket] + cleanText[closeBracket+1:]
		// Don't advance idx — re-scan from same position
	}

	cleanText = strings.TrimSpace(cleanText)
	return cleanText, toolCalls
}
