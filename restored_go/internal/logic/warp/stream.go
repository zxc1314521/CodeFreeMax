package warp

// stream.go — Streaming response processing for the Warp channel.
//
// Warp streams protobuf-encoded responses over HTTP. Each chunk is a
// length-prefixed protobuf message that needs to be parsed and converted
// to OpenAI-compatible SSE format.
//
// The streaming protocol:
//   1. HTTP response with Content-Type: application/x-protobuf
//   2. Each chunk: 4-byte big-endian length prefix + protobuf bytes
//   3. Protobuf message contains output_text, reasoning_text, tool calls, etc.
//   4. Stream ends with a message containing done=true or usage info
//
// From decompiled patterns in ChatCompletions:
//   - Response body is read in chunks
//   - Each chunk is unmarshaled via UnmarshalMessage
//   - ExtractOutputText / ExtractReasoningText extract content
//   - DetectContentType determines the response type
//   - Tool calls are mapped via MapToolToClaudeCode / MapToolsToClaudeCode

import (
	"bufio"
	"encoding/binary"
	"encoding/json"
	"fmt"
	"io"
	"strings"
	"time"

	"github.com/gogf/gf/v2/frame/gins"
)

// ============================================================================
// StreamProcessor
// ============================================================================

// StreamProcessor handles parsing and converting Warp's protobuf stream
// to OpenAI-compatible SSE events.
type StreamProcessor struct {
	reader    io.Reader
	toolMap   map[string]string
	model     string
	requestID string
}

// NewStreamProcessor creates a new StreamProcessor.
func NewStreamProcessor(reader io.Reader, model string, requestID string) *StreamProcessor {
	return &StreamProcessor{
		reader:    reader,
		toolMap:   warpToClaudeToolMap,
		model:     model,
		requestID: requestID,
	}
}

// ============================================================================
// OpenAI SSE Response Types
// ============================================================================

// SSEChatCompletionChunk represents an OpenAI-compatible streaming chunk.
type SSEChatCompletionChunk struct {
	ID      string       `json:"id"`
	Object  string       `json:"object"`
	Created int64        `json:"created"`
	Model   string       `json:"model"`
	Choices []SSEChoice  `json:"choices"`
	Usage   *SSEUsage    `json:"usage,omitempty"`
}

// SSEChoice represents a choice in a streaming chunk.
type SSEChoice struct {
	Index        int      `json:"index"`
	Delta        SSEDelta `json:"delta"`
	FinishReason *string  `json:"finish_reason"`
}

// SSEDelta represents the delta content in a streaming chunk.
type SSEDelta struct {
	Role      string          `json:"role,omitempty"`
	Content   string          `json:"content,omitempty"`
	ToolCalls []SSEToolCall   `json:"tool_calls,omitempty"`
}

// SSEToolCall represents a tool call in a streaming chunk.
type SSEToolCall struct {
	Index    int             `json:"index"`
	ID       string          `json:"id,omitempty"`
	Type     string          `json:"type,omitempty"`
	Function SSEToolFunction `json:"function"`
}

// SSEToolFunction represents the function details of a tool call.
type SSEToolFunction struct {
	Name      string `json:"name,omitempty"`
	Arguments string `json:"arguments,omitempty"`
}

// SSEUsage represents token usage in a streaming response.
type SSEUsage struct {
	PromptTokens     int `json:"prompt_tokens"`
	CompletionTokens int `json:"completion_tokens"`
	TotalTokens      int `json:"total_tokens"`
}

// ============================================================================
// ProcessStream — Main streaming loop
// ============================================================================

// ProcessStream reads the protobuf stream and yields OpenAI SSE events.
// Returns a channel of SSE event strings.
//
// From decompiled: The ChatCompletions function sets up a closure that
// reads the response body and processes each protobuf chunk.
// The closure is passed to req.Request.Send() as a response handler.
func (sp *StreamProcessor) ProcessStream() (<-chan string, <-chan error) {
	events := make(chan string, 64)
	errs := make(chan error, 1)

	go func() {
		defer close(events)
		defer close(errs)

		logger := gins.Log()
		reader := bufio.NewReaderSize(sp.reader, 64*1024)

		// Send initial role event
		initialChunk := sp.buildChunk("", "assistant", nil, nil)
		if data, err := json.Marshal(initialChunk); err == nil {
			events <- fmt.Sprintf("data: %s\n\n", data)
		}

		toolCallIndex := 0

		for {
			// Read length-prefixed protobuf message
			// From decompiled: 4-byte big-endian length prefix
			var msgLen uint32
			if err := binary.Read(reader, binary.BigEndian, &msgLen); err != nil {
				if err == io.EOF {
					break
				}
				logger.Warningf(nil, "[Warp] Error reading message length: %v", err)
				errs <- fmt.Errorf("read message length: %w", err)
				return
			}

			// Sanity check message length
			if msgLen > 10*1024*1024 { // 10MB max
				errs <- fmt.Errorf("message too large: %d bytes", msgLen)
				return
			}

			// Read protobuf bytes
			msgBytes := make([]byte, msgLen)
			if _, err := io.ReadFull(reader, msgBytes); err != nil {
				logger.Warningf(nil, "[Warp] Error reading message body: %v", err)
				errs <- fmt.Errorf("read message body: %w", err)
				return
			}

			// Parse the raw protobuf without descriptor
			// From decompiled: UnmarshalMessage is called on each chunk
			fields := ParseRawProtobuf(msgBytes)

			// Extract content based on field numbers
			// Field patterns (inferred from decompiled):
			//   Field 1: output text (bytes/string)
			//   Field 2: reasoning text (bytes/string)
			//   Field 3: tool calls (nested message)
			//   Field 4: done flag (varint)
			//   Field 5: usage info (nested message)
			//   Field 6: error message (bytes/string)

			// Check for output text (field 1)
			if values, ok := fields[1]; ok {
				for _, v := range values {
					if textBytes, ok := v.([]byte); ok {
						text := string(textBytes)
						if text != "" {
							chunk := sp.buildChunk(text, "", nil, nil)
							if data, err := json.Marshal(chunk); err == nil {
								events <- fmt.Sprintf("data: %s\n\n", data)
							}
						}
					}
				}
			}

			// Check for reasoning text (field 2)
			if values, ok := fields[2]; ok {
				for _, v := range values {
					if textBytes, ok := v.([]byte); ok {
						text := string(textBytes)
						if text != "" {
							// Send reasoning as content with prefix
							chunk := sp.buildChunk(text, "", nil, nil)
							if data, err := json.Marshal(chunk); err == nil {
								events <- fmt.Sprintf("data: %s\n\n", data)
							}
						}
					}
				}
			}

			// Check for tool calls (field 3)
			if values, ok := fields[3]; ok {
				for _, v := range values {
					if toolBytes, ok := v.([]byte); ok {
						toolFields := ParseRawProtobuf(toolBytes)
						toolCall := sp.parseToolCall(toolFields, toolCallIndex)
						if toolCall != nil {
							chunk := sp.buildChunk("", "", []SSEToolCall{*toolCall}, nil)
							if data, err := json.Marshal(chunk); err == nil {
								events <- fmt.Sprintf("data: %s\n\n", data)
							}
							toolCallIndex++
						}
					}
				}
			}

			// Check for done flag (field 4)
			if values, ok := fields[4]; ok {
				for _, v := range values {
					if done, ok := v.(uint64); ok && done == 1 {
						// Parse usage if available (field 5)
						var usage *SSEUsage
						if usageValues, ok := fields[5]; ok {
							for _, uv := range usageValues {
								if usageBytes, ok := uv.([]byte); ok {
									usage = sp.parseUsage(usageBytes)
								}
							}
						}

						// Send final chunk with finish_reason
						finishReason := "stop"
						if toolCallIndex > 0 {
							finishReason = "tool_calls"
						}
						chunk := sp.buildChunk("", "", nil, usage)
						chunk.Choices[0].FinishReason = &finishReason
						if data, err := json.Marshal(chunk); err == nil {
							events <- fmt.Sprintf("data: %s\n\n", data)
						}
						events <- "data: [DONE]\n\n"
						return
					}
				}
			}

			// Check for error (field 6)
			if values, ok := fields[6]; ok {
				for _, v := range values {
					if errBytes, ok := v.([]byte); ok {
						errMsg := string(errBytes)
						if errMsg != "" {
							logger.Warningf(nil, "[Warp] Stream error: %s", errMsg)
							errs <- fmt.Errorf("warp stream error: %s", errMsg)
							return
						}
					}
				}
			}
		}

		// Stream ended without explicit done — send DONE
		events <- "data: [DONE]\n\n"
	}()

	return events, errs
}

// ============================================================================
// Non-streaming response processing
// ============================================================================

// ProcessComplete reads the entire protobuf response and returns a
// complete OpenAI-compatible chat completion response.
func (sp *StreamProcessor) ProcessComplete() (map[string]interface{}, error) {
	data, err := io.ReadAll(sp.reader)
	if err != nil {
		return nil, fmt.Errorf("read response body: %w", err)
	}

	// Parse the protobuf response
	fields := ParseRawProtobuf(data)

	// Extract content
	var contentParts []string

	// Output text (field 1)
	if values, ok := fields[1]; ok {
		for _, v := range values {
			if textBytes, ok := v.([]byte); ok {
				contentParts = append(contentParts, string(textBytes))
			}
		}
	}

	content := strings.Join(contentParts, "")

	// Build response
	response := map[string]interface{}{
		"id":      fmt.Sprintf("chatcmpl-%s", sp.requestID),
		"object":  "chat.completion",
		"created": time.Now().Unix(),
		"model":   sp.model,
		"choices": []map[string]interface{}{
			{
				"index": 0,
				"message": map[string]interface{}{
					"role":    "assistant",
					"content": content,
				},
				"finish_reason": "stop",
			},
		},
	}

	// Add usage if available (field 5)
	if usageValues, ok := fields[5]; ok {
		for _, uv := range usageValues {
			if usageBytes, ok := uv.([]byte); ok {
				if usage := sp.parseUsage(usageBytes); usage != nil {
					response["usage"] = usage
				}
			}
		}
	}

	return response, nil
}

// ============================================================================
// Helper methods
// ============================================================================

// buildChunk creates an SSE chat completion chunk.
func (sp *StreamProcessor) buildChunk(content string, role string,
	toolCalls []SSEToolCall, usage *SSEUsage) SSEChatCompletionChunk {

	delta := SSEDelta{}
	if role != "" {
		delta.Role = role
	}
	if content != "" {
		delta.Content = content
	}
	if len(toolCalls) > 0 {
		delta.ToolCalls = toolCalls
	}

	chunk := SSEChatCompletionChunk{
		ID:      fmt.Sprintf("chatcmpl-%s", sp.requestID),
		Object:  "chat.completion.chunk",
		Created: time.Now().Unix(),
		Model:   sp.model,
		Choices: []SSEChoice{
			{
				Index: 0,
				Delta: delta,
			},
		},
	}

	if usage != nil {
		chunk.Usage = usage
	}

	return chunk
}

// parseToolCall parses a tool call from raw protobuf fields.
func (sp *StreamProcessor) parseToolCall(fields map[uint32][]interface{}, index int) *SSEToolCall {
	// Tool call protobuf structure (inferred):
	//   Field 1: tool name (string)
	//   Field 2: arguments (string/JSON)
	//   Field 3: tool call ID (string)

	var name, argsStr, id string

	if values, ok := fields[1]; ok && len(values) > 0 {
		if b, ok := values[0].([]byte); ok {
			name = string(b)
		}
	}
	if values, ok := fields[2]; ok && len(values) > 0 {
		if b, ok := values[0].([]byte); ok {
			argsStr = string(b)
		}
	}
	if values, ok := fields[3]; ok && len(values) > 0 {
		if b, ok := values[0].([]byte); ok {
			id = string(b)
		}
	}

	if name == "" {
		return nil
	}

	// Map tool name to Claude Code format
	mappedName := name
	if mapped, ok := warpToClaudeToolMap[name]; ok {
		mappedName = mapped
	}

	if id == "" {
		id = fmt.Sprintf("call_%s_%d", name, index)
	}

	return &SSEToolCall{
		Index: index,
		ID:    id,
		Type:  "function",
		Function: SSEToolFunction{
			Name:      mappedName,
			Arguments: argsStr,
		},
	}
}

// parseUsage parses usage information from raw protobuf bytes.
func (sp *StreamProcessor) parseUsage(data []byte) *SSEUsage {
	fields := ParseRawProtobuf(data)

	// Usage protobuf structure (inferred):
	//   Field 1: input_tokens (varint)
	//   Field 2: output_tokens (varint)

	usage := &SSEUsage{}

	if values, ok := fields[1]; ok && len(values) > 0 {
		if v, ok := values[0].(uint64); ok {
			usage.PromptTokens = int(v)
		}
	}
	if values, ok := fields[2]; ok && len(values) > 0 {
		if v, ok := values[0].(uint64); ok {
			usage.CompletionTokens = int(v)
		}
	}

	usage.TotalTokens = usage.PromptTokens + usage.CompletionTokens
	return usage
}
