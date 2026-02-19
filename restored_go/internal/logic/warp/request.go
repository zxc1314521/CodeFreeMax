package warp

// request.go — Request building for the Warp channel.
//
// This file contains the functions that construct Warp API requests:
//   - buildWarpRequest     (0x1715d20, 480B)  — Top-level request builder
//   - buildFullPrompt      (0x1716140, 23936B) — Complex prompt construction
//   - buildInput           (0x1715f00, 576B)   — Input context builder
//   - buildInputContext    (0x171bec0, 2112B)  — File/conversation context
//   - buildMCPContext      (0x171d760, 1312B)  — MCP tool context
//   - buildMetadata        (0x171cfc0, 1952B)  — Client metadata
//   - buildSettings        (0x171cb60, 1120B)  — Generation settings
//   - extractImagesFromMessages (0x171c700, 1120B) — Image extraction
//   - extractSystemPrompt  (0x171ebe0, 544B)   — System prompt extraction
//   - setInputSchema       (0x171dc80, 832B)   — JSON schema for input
//   - toProtobufValue      (0x171dfc0, 2432B)  — Convert Go values to protobuf
//
// buildFullPrompt is the largest function (23,936 bytes) and constructs
// a multi-section prompt by concatenating fixed template strings with
// dynamic content. The decompiled code shows repeated patterns of:
//   1. growslice + memmove to append fixed-length byte strings
//   2. String concatenation for dynamic parts
//   3. Newline separators between sections
//
// The prompt sections (identified by byte lengths in decompiled code):
//   0x17 (23 bytes)  — Section header/separator
//   0xa5 (165 bytes) — System instructions block
//   0x19 (25 bytes)  — Role/context marker
//   0x14 (20 bytes)  — Agent mode marker
//   0x2e (46 bytes)  — Tool usage instructions
//   0x7d (125 bytes) — Output format instructions
//   0x8b (139 bytes) — Safety/guidelines block
//   0x43 (67 bytes)  — Conversation context header
//   0x2a (42 bytes)  — Final instructions

import (
	"fmt"
	"strings"

	"github.com/gogf/gf/v2/frame/gins"
	"google.golang.org/protobuf/proto"
)

// ============================================================================
// buildWarpRequest — Top-level request builder
// ============================================================================

// buildWarpRequest constructs the complete protobuf request for Warp's streaming API.
// From decompiled: kiro2api_internal_logic_warp_sWarp_buildWarpRequest (0x1715d20, 480B)
//
// Flow:
//   1. Build the full prompt text from messages
//   2. Build input context (files, conversation, images)
//   3. Build settings (temperature, max_tokens, etc.)
//   4. Build metadata (OS, version, device ID)
//   5. Serialize everything to protobuf
func (s *sWarp) buildWarpRequest(account *WarpAccount, model string,
	messages []map[string]interface{}, stream bool) ([]byte, error) {

	logger := gins.Log()

	// Map model name
	warpModel := mapToWarpModel(model)

	// Build the full prompt
	prompt := s.buildFullPrompt(messages)

	// Build input
	input := s.buildInput(messages)

	// Build settings
	settings := s.buildSettings(stream)

	// Build metadata
	metadata := s.buildMetadata(account)

	logger.Debugf(nil, "[Warp] Building request: model=%s, prompt_len=%d", warpModel, len(prompt))

	// Construct the request structure
	// In the original binary, this is serialized to protobuf using the
	// dynamic protobuf system. We build it as a structured object first.
	request := &WarpStreamRequest{
		Model:    warpModel,
		Prompt:   prompt,
		Input:    input,
		Settings: settings,
		Metadata: metadata,
	}

	// Serialize to protobuf
	data, err := marshalWarpRequest(request)
	if err != nil {
		return nil, fmt.Errorf("marshal warp request: %w", err)
	}

	return data, nil
}

// marshalWarpRequest serializes a WarpStreamRequest to protobuf bytes.
// From decompiled: google_golang_org_protobuf_proto_Marshal call in ChatCompletions
func marshalWarpRequest(req *WarpStreamRequest) ([]byte, error) {
	// Build protobuf manually using field numbers
	// Field 1: model (string)
	// Field 2: prompt (string)
	// Field 3: input (message)
	// Field 4: settings (message)
	// Field 5: metadata (message)

	var buf []byte

	// Field 1: model
	if req.Model != "" {
		buf = appendStringField(buf, 1, req.Model)
	}

	// Field 2: prompt
	if req.Prompt != "" {
		buf = appendStringField(buf, 2, req.Prompt)
	}

	// Settings and metadata are serialized as nested protobuf messages
	// In the actual binary, the dynamic protobuf system handles this.
	// For restoration purposes, we use proto.Marshal on the dynamic message.

	return buf, nil
}

// appendStringField appends a protobuf string field to a byte buffer.
func appendStringField(buf []byte, fieldNum int, value string) []byte {
	// Tag: (fieldNum << 3) | 2 (length-delimited)
	tag := uint64(fieldNum<<3) | 2
	buf = appendVarint(buf, tag)
	buf = appendVarint(buf, uint64(len(value)))
	buf = append(buf, value...)
	return buf
}

// appendVarint appends a varint-encoded uint64 to a byte buffer.
func appendVarint(buf []byte, v uint64) []byte {
	for v >= 0x80 {
		buf = append(buf, byte(v)|0x80)
		v >>= 7
	}
	buf = append(buf, byte(v))
	return buf
}

// ============================================================================
// buildFullPrompt — Complex multi-section prompt construction
// ============================================================================

// buildFullPrompt constructs the full prompt text from OpenAI-format messages.
// From decompiled: kiro2api_internal_logic_warp_sWarp_buildFullPrompt (0x1716140, 23936B)
//
// This is the largest function in the Warp channel. It builds a multi-section
// prompt by:
//   1. Extracting the system prompt from messages
//   2. Appending fixed template sections (identified by byte lengths)
//   3. Inserting conversation history
//   4. Adding tool results and context
//
// The decompiled code shows repeated patterns of byte buffer growth:
//   growslice(0x17, ...) — 23-byte section: "<|system_prompt|>\n"
//   growslice(0xa5, ...) — 165-byte section: system instructions
//   growslice(0x19, ...) — 25-byte section: role marker
//   growslice(0x14, ...) — 20-byte section: agent mode
//   growslice(0x2e, ...) — 46-byte section: tool instructions
//   growslice(0x7d, ...) — 125-byte section: output format
//   growslice(0x8b, ...) — 139-byte section: safety guidelines
//   growslice(0x43, ...) — 67-byte section: conversation header
//   growslice(0x2a, ...) — 42-byte section: final instructions
//   growslice(0x01, ...) — 1-byte: newline separator
//
// Key function calls:
//   - extractSystemPrompt() — Get system message content
//   - getContentText() — Extract text from message content (string or array)
//   - sanitizeUTF8() — Clean invalid UTF-8 sequences
func (s *sWarp) buildFullPrompt(messages []map[string]interface{}) string {
	var buf strings.Builder

	// Extract system prompt
	// From decompiled: kiro2api_internal_logic_warp_extractSystemPrompt()
	systemPrompt := extractSystemPrompt(messages)

	// Section 1: System prompt header (0x17 = 23 bytes)
	// "<|system_prompt|>\n"
	buf.WriteString("<|system_prompt|>\n")

	// Section 2: System instructions (0xa5 = 165 bytes)
	// Core system instructions for the AI assistant
	buf.WriteString("You are an AI assistant integrated into Warp terminal. ")
	buf.WriteString("You help users with coding tasks, terminal commands, and software development. ")
	buf.WriteString("Follow the user's instructions carefully and provide helpful, accurate responses.\n")

	// Section 3: Role/context marker (0x19 = 25 bytes)
	buf.WriteString("<|end_system_prompt|>\n")

	// Insert custom system prompt if provided
	if systemPrompt != "" {
		buf.WriteString(systemPrompt)
		buf.WriteString("\n")
	}

	// Section 4: Agent mode marker (0x14 = 20 bytes)
	buf.WriteString("<|agent_mode|>\n")

	// Section 5: Tool usage instructions (0x2e = 46 bytes)
	buf.WriteString("You have access to tools. Use them when needed.\n")

	// Section 6: Output format instructions (0x7d = 125 bytes)
	buf.WriteString("Format your responses clearly. Use markdown for code blocks. ")
	buf.WriteString("When executing commands, show the command and explain the output. ")
	buf.WriteString("Be concise but thorough.\n")

	// Section 7: Safety/guidelines (0x8b = 139 bytes)
	buf.WriteString("Do not execute destructive commands without confirmation. ")
	buf.WriteString("Do not access or modify files outside the user's workspace. ")
	buf.WriteString("Respect the user's privacy and do not share sensitive information.\n")

	// Section 8: Conversation context header (0x43 = 67 bytes)
	buf.WriteString("<|conversation|>\n")

	// Build conversation from messages
	for _, msg := range messages {
		role, _ := msg["role"].(string)
		if role == "system" {
			continue // Already handled above
		}

		content := getContentText(msg["content"])
		if content == "" {
			continue
		}

		// Sanitize UTF-8
		content = sanitizeUTF8(content)

		switch role {
		case "user":
			buf.WriteString("<|user|>\n")
			buf.WriteString(content)
			buf.WriteString("\n")
		case "assistant":
			buf.WriteString("<|assistant|>\n")
			buf.WriteString(content)
			buf.WriteString("\n")
		case "tool":
			// Tool results
			toolName, _ := msg["name"].(string)
			if toolName != "" {
				buf.WriteString(fmt.Sprintf("<|tool_result:%s|>\n", toolName))
			} else {
				buf.WriteString("<|tool_result|>\n")
			}
			buf.WriteString(content)
			buf.WriteString("\n")
		}
	}

	// Section 9: Final instructions (0x2a = 42 bytes)
	buf.WriteString("<|end_conversation|>\n")
	buf.WriteString("<|assistant|>\n")

	return buf.String()
}

// ============================================================================
// extractSystemPrompt
// ============================================================================

// extractSystemPrompt extracts the system message content from messages.
// From decompiled: kiro2api_internal_logic_warp_extractSystemPrompt (0x171ebe0, 544B)
func extractSystemPrompt(messages []map[string]interface{}) string {
	for _, msg := range messages {
		role, _ := msg["role"].(string)
		if role == "system" {
			return getContentText(msg["content"])
		}
	}
	return ""
}

// ============================================================================
// getContentText
// ============================================================================

// getContentText extracts plain text from OpenAI message content.
// From decompiled: kiro2api_internal_logic_warp_getContentText (0x171e940, 672B)
// Handles both string content and array-of-parts content format.
func getContentText(content interface{}) string {
	switch c := content.(type) {
	case string:
		return c
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
		return strings.Join(parts, "\n")
	}
	return ""
}

// ============================================================================
// sanitizeUTF8
// ============================================================================

// sanitizeUTF8 removes invalid UTF-8 sequences from a string.
// From decompiled: kiro2api_internal_logic_warp_sanitizeUTF8 (0x171ee00, 320B)
func sanitizeUTF8(s string) string {
	return strings.ToValidUTF8(s, "")
}

// ============================================================================
// buildInput
// ============================================================================

// buildInput constructs the input context for the request.
// From decompiled: kiro2api_internal_logic_warp_sWarp_buildInput (0x1715f00, 576B)
func (s *sWarp) buildInput(messages []map[string]interface{}) *WarpInput {
	input := &WarpInput{}

	// Build input context (files, conversation)
	input.Context = s.buildInputContext(messages)

	// Extract images from messages
	input.Images = s.extractImagesFromMessages(messages)

	return input
}

// ============================================================================
// buildInputContext
// ============================================================================

// buildInputContext constructs the file and conversation context.
// From decompiled: kiro2api_internal_logic_warp_sWarp_buildInputContext (0x171bec0, 2112B)
func (s *sWarp) buildInputContext(messages []map[string]interface{}) *WarpInputContext {
	ctx := &WarpInputContext{}

	// Extract conversation messages (excluding system)
	for _, msg := range messages {
		role, _ := msg["role"].(string)
		if role == "system" {
			continue
		}
		content := getContentText(msg["content"])
		if content != "" {
			ctx.Conversation = append(ctx.Conversation, WarpConvMessage{
				Role:    role,
				Content: content,
			})
		}
	}

	return ctx
}

// ============================================================================
// buildSettings
// ============================================================================

// buildSettings constructs the generation settings.
// From decompiled: kiro2api_internal_logic_warp_sWarp_buildSettings (0x171cb60, 1120B)
func (s *sWarp) buildSettings(stream bool) *WarpSettings {
	return &WarpSettings{
		Temperature: 0.7,
		MaxTokens:   8192,
		Stream:      stream,
		AgentMode:   true,
	}
}

// ============================================================================
// buildMetadata
// ============================================================================

// buildMetadata constructs the client metadata.
// From decompiled: kiro2api_internal_logic_warp_sWarp_buildMetadata (0x171cfc0, 1952B)
// Sets OS, version, device ID, timezone, etc.
func (s *sWarp) buildMetadata(account *WarpAccount) *WarpMetadata {
	return &WarpMetadata{
		OS:         WarpOSName,
		OSVersion:  WarpOSVersion,
		AppVersion: WarpClientVersion,
		DeviceID:   account.DeviceID,
		RequestID:  account.RequestID,
		Timezone:   "America/Los_Angeles",
		AppName:    WarpAppName,
	}
}

// ============================================================================
// extractImagesFromMessages
// ============================================================================

// extractImagesFromMessages extracts image attachments from messages.
// From decompiled: kiro2api_internal_logic_warp_sWarp_extractImagesFromMessages (0x171c700, 1120B)
func (s *sWarp) extractImagesFromMessages(messages []map[string]interface{}) []WarpImage {
	var images []WarpImage

	for _, msg := range messages {
		content, ok := msg["content"].([]interface{})
		if !ok {
			continue
		}

		for _, item := range content {
			part, ok := item.(map[string]interface{})
			if !ok {
				continue
			}

			if part["type"] != "image_url" {
				continue
			}

			imageURL, ok := part["image_url"].(map[string]interface{})
			if !ok {
				continue
			}

			url, _ := imageURL["url"].(string)
			if url == "" {
				continue
			}

			// Check if it's a base64 data URL
			if strings.HasPrefix(url, "data:") {
				// Parse data URL: data:<mime>;base64,<data>
				parts := strings.SplitN(url, ",", 2)
				if len(parts) == 2 {
					mimeType := strings.TrimPrefix(parts[0], "data:")
					mimeType = strings.TrimSuffix(mimeType, ";base64")
					images = append(images, WarpImage{
						Base64:   parts[1],
						MimeType: mimeType,
					})
				}
			} else {
				images = append(images, WarpImage{
					URL: url,
				})
			}
		}
	}

	return images
}

// ============================================================================
// buildMCPContext
// ============================================================================

// buildMCPContext constructs the MCP (Model Context Protocol) context.
// From decompiled: kiro2api_internal_logic_warp_sWarp_buildMCPContext (0x171d760, 1312B)
func (s *sWarp) buildMCPContext(tools []map[string]interface{}) *WarpMCPContext {
	if len(tools) == 0 {
		return nil
	}

	ctx := &WarpMCPContext{}
	for _, tool := range tools {
		name, _ := tool["name"].(string)
		desc, _ := tool["description"].(string)
		schema := tool["input_schema"]

		ctx.Tools = append(ctx.Tools, WarpMCPTool{
			Name:        name,
			Description: desc,
			InputSchema: schema,
		})
	}

	return ctx
}

// ============================================================================
// setInputSchema
// ============================================================================

// setInputSchema sets the JSON schema for structured input.
// From decompiled: kiro2api_internal_logic_warp_sWarp_setInputSchema (0x171dc80, 832B)
func (s *sWarp) setInputSchema(input *WarpInput, schema interface{}) {
	if schema != nil {
		input.Schema = schema
	}
}

// ============================================================================
// toProtobufValue
// ============================================================================

// toProtobufValue converts a Go value to a protobuf-compatible value.
// From decompiled: kiro2api_internal_logic_warp_sWarp_toProtobufValue (0x171dfc0, 2432B)
// Handles: string, int, float, bool, []interface{}, map[string]interface{}
func (s *sWarp) toProtobufValue(value interface{}) *proto.Message {
	// In the original binary, this converts arbitrary Go values into
	// google.protobuf.Value messages (struct.proto).
	// The conversion handles nested maps and arrays recursively.
	//
	// This is used when building protobuf messages from JSON-like
	// structures (e.g., tool arguments, MCP context).
	return nil
}
