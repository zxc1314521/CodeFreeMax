package cursor

import (
	"encoding/json"
	"fmt"
	"net/http"
	"strings"
	"time"
)

// ============================================================================
// SSE Writer — Converts Cursor Connect-RPC stream to OpenAI SSE format
// ============================================================================

// CursorSSEWriter converts Cursor's Connect-RPC protobuf streaming responses
// into OpenAI-compatible Server-Sent Events (SSE) format.
//
// The binary contains ~123 functions in logic/cursor related to SSE processing.
// Key symbols:
//   - (*CursorSSEWriter).WriteTextDelta (448B @ 0x17fd0a0)
//   - (*CursorSSEWriter).WriteThinkingDelta (448B @ 0x17fd280)
//   - (*CursorSSEWriter).WriteToolCallDelta (640B @ 0x17fd460)
//   - (*CursorSSEWriter).WriteStop (320B @ 0x17fd6a0)
//   - (*CursorSSEWriter).WriteError (256B @ 0x17fd7e0)
//   - (*CursorSSEWriter).Flush (64B @ 0x17fd8a0)
//   - (*CursorSSEWriter).writeSSEEvent (192B @ 0x17fd900)
type CursorSSEWriter struct {
	w       http.ResponseWriter
	flusher http.Flusher
	model   string
	id      string

	// State tracking for incremental tool call indices
	toolCallIndex int

	// Whether we've sent the initial role chunk
	sentRole bool

	// Accumulated usage stats
	promptTokens     int
	completionTokens int
}

// NewCursorSSEWriter creates a new SSE writer that wraps the HTTP response writer.
// Symbol: kiro2api/internal/logic/cursor.NewCursorSSEWriter (192B @ 0x17fcfe0)
func NewCursorSSEWriter(w http.ResponseWriter, model string, id string) *CursorSSEWriter {
	flusher, _ := w.(http.Flusher)

	// Set SSE headers
	w.Header().Set("Content-Type", "text/event-stream")
	w.Header().Set("Cache-Control", "no-cache")
	w.Header().Set("Connection", "keep-alive")
	w.Header().Set("Transfer-Encoding", "chunked")
	w.WriteHeader(http.StatusOK)

	return &CursorSSEWriter{
		w:       w,
		flusher: flusher,
		model:   model,
		id:      id,
	}
}

// OpenAI SSE chunk structures

type sseChunk struct {
	ID      string      `json:"id"`
	Object  string      `json:"object"`
	Created int64       `json:"created"`
	Model   string      `json:"model"`
	Choices []sseChoice `json:"choices"`
	Usage   *sseUsage   `json:"usage,omitempty"`
}

type sseChoice struct {
	Index        int      `json:"index"`
	Delta        sseDelta `json:"delta"`
	FinishReason *string  `json:"finish_reason"`
}

type sseDelta struct {
	Role      string         `json:"role,omitempty"`
	Content   string         `json:"content,omitempty"`
	ToolCalls []sseToolCall  `json:"tool_calls,omitempty"`
	Reasoning *sseReasoning  `json:"reasoning,omitempty"`
}

type sseToolCall struct {
	Index    int             `json:"index"`
	ID       string          `json:"id,omitempty"`
	Type     string          `json:"type,omitempty"`
	Function sseToolFunction `json:"function"`
}

type sseToolFunction struct {
	Name      string `json:"name,omitempty"`
	Arguments string `json:"arguments,omitempty"`
}

type sseReasoning struct {
	Content string `json:"content,omitempty"`
}

type sseUsage struct {
	PromptTokens     int `json:"prompt_tokens"`
	CompletionTokens int `json:"completion_tokens"`
	TotalTokens      int `json:"total_tokens"`
}

// writeSSEEvent writes a single SSE event to the response writer.
// Symbol: (*CursorSSEWriter).writeSSEEvent (192B @ 0x17fd900)
func (w *CursorSSEWriter) writeSSEEvent(data []byte) {
	fmt.Fprintf(w.w, "data: %s\n\n", data)
	if w.flusher != nil {
		w.flusher.Flush()
	}
}

// WriteRoleChunk sends the initial role assignment chunk.
// This is sent once at the beginning of the stream.
func (w *CursorSSEWriter) WriteRoleChunk() {
	if w.sentRole {
		return
	}
	w.sentRole = true

	chunk := sseChunk{
		ID:      w.id,
		Object:  "chat.completion.chunk",
		Created: time.Now().Unix(),
		Model:   w.model,
		Choices: []sseChoice{
			{
				Index: 0,
				Delta: sseDelta{
					Role: "assistant",
				},
			},
		},
	}

	data, _ := json.Marshal(chunk)
	w.writeSSEEvent(data)
}

// WriteTextDelta writes a text content delta chunk.
// Symbol: (*CursorSSEWriter).WriteTextDelta (448B @ 0x17fd0a0)
//
// The 448B size indicates JSON marshaling of the SSE chunk with content field.
func (w *CursorSSEWriter) WriteTextDelta(text string) {
	if !w.sentRole {
		w.WriteRoleChunk()
	}

	chunk := sseChunk{
		ID:      w.id,
		Object:  "chat.completion.chunk",
		Created: time.Now().Unix(),
		Model:   w.model,
		Choices: []sseChoice{
			{
				Index: 0,
				Delta: sseDelta{
					Content: text,
				},
			},
		},
	}

	data, _ := json.Marshal(chunk)
	w.writeSSEEvent(data)
	w.completionTokens++ // rough estimate
}

// WriteThinkingDelta writes a thinking/reasoning content delta chunk.
// Symbol: (*CursorSSEWriter).WriteThinkingDelta (448B @ 0x17fd280)
//
// Thinking deltas are sent as reasoning content in the OpenAI format.
func (w *CursorSSEWriter) WriteThinkingDelta(text string) {
	if !w.sentRole {
		w.WriteRoleChunk()
	}

	chunk := sseChunk{
		ID:      w.id,
		Object:  "chat.completion.chunk",
		Created: time.Now().Unix(),
		Model:   w.model,
		Choices: []sseChoice{
			{
				Index: 0,
				Delta: sseDelta{
					Reasoning: &sseReasoning{
						Content: text,
					},
				},
			},
		},
	}

	data, _ := json.Marshal(chunk)
	w.writeSSEEvent(data)
}

// WriteToolCallDelta writes a tool call delta chunk.
// Symbol: (*CursorSSEWriter).WriteToolCallDelta (640B @ 0x17fd460)
//
// The 640B size indicates more complex JSON with nested tool call structure.
// Tool calls are sent incrementally: first the function name, then argument chunks.
func (w *CursorSSEWriter) WriteToolCallDelta(toolCallID string, funcName string, argsChunk string) {
	if !w.sentRole {
		w.WriteRoleChunk()
	}

	tc := sseToolCall{
		Index:    w.toolCallIndex,
		Function: sseToolFunction{},
	}

	// First chunk for this tool call includes ID and type
	if toolCallID != "" {
		tc.ID = toolCallID
		tc.Type = "function"
	}
	if funcName != "" {
		tc.Function.Name = funcName
	}
	if argsChunk != "" {
		tc.Function.Arguments = argsChunk
	}

	chunk := sseChunk{
		ID:      w.id,
		Object:  "chat.completion.chunk",
		Created: time.Now().Unix(),
		Model:   w.model,
		Choices: []sseChoice{
			{
				Index: 0,
				Delta: sseDelta{
					ToolCalls: []sseToolCall{tc},
				},
			},
		},
	}

	data, _ := json.Marshal(chunk)
	w.writeSSEEvent(data)
}

// NextToolCall advances the tool call index for the next tool call.
func (w *CursorSSEWriter) NextToolCall() {
	w.toolCallIndex++
}

// WriteStop writes the final stop chunk with finish_reason.
// Symbol: (*CursorSSEWriter).WriteStop (320B @ 0x17fd6a0)
func (w *CursorSSEWriter) WriteStop(reason string) {
	if reason == "" {
		reason = "stop"
	}

	chunk := sseChunk{
		ID:      w.id,
		Object:  "chat.completion.chunk",
		Created: time.Now().Unix(),
		Model:   w.model,
		Choices: []sseChoice{
			{
				Index:        0,
				Delta:        sseDelta{},
				FinishReason: &reason,
			},
		},
		Usage: &sseUsage{
			PromptTokens:     w.promptTokens,
			CompletionTokens: w.completionTokens,
			TotalTokens:      w.promptTokens + w.completionTokens,
		},
	}

	data, _ := json.Marshal(chunk)
	w.writeSSEEvent(data)

	// Send [DONE] marker
	fmt.Fprintf(w.w, "data: [DONE]\n\n")
	if w.flusher != nil {
		w.flusher.Flush()
	}
}

// WriteError writes an error event to the SSE stream.
// Symbol: (*CursorSSEWriter).WriteError (256B @ 0x17fd7e0)
func (w *CursorSSEWriter) WriteError(errMsg string) {
	errData := map[string]interface{}{
		"error": map[string]interface{}{
			"message": errMsg,
			"type":    "server_error",
		},
	}
	data, _ := json.Marshal(errData)
	w.writeSSEEvent(data)

	// Send [DONE] after error
	fmt.Fprintf(w.w, "data: [DONE]\n\n")
	if w.flusher != nil {
		w.flusher.Flush()
	}
}

// SetPromptTokens sets the prompt token count for usage reporting.
func (w *CursorSSEWriter) SetPromptTokens(count int) {
	w.promptTokens = count
}

// Flush forces a flush of the response writer.
// Symbol: (*CursorSSEWriter).Flush (64B @ 0x17fd8a0)
func (w *CursorSSEWriter) Flush() {
	if w.flusher != nil {
		w.flusher.Flush()
	}
}

// ============================================================================
// Cursor Stream Response Parsing
// ============================================================================

// CursorStreamEvent represents a parsed event from the Cursor Connect-RPC stream.
// The binary processes these events in a large switch statement with ~15 cases.
type CursorStreamEvent struct {
	Type string // "text", "thinking", "tool_call", "tool_call_args", "stop", "error", "usage"

	// Text content (for "text" and "thinking" types)
	Text string

	// Tool call info (for "tool_call" and "tool_call_args" types)
	ToolCallID   string
	FunctionName string
	Arguments    string

	// Stop reason (for "stop" type)
	StopReason string

	// Error info (for "error" type)
	ErrorMessage string

	// Usage info (for "usage" type)
	PromptTokens     int
	CompletionTokens int
}

// ParseCursorStreamChunk parses a raw protobuf chunk from the Cursor Connect-RPC
// stream into a sequence of CursorStreamEvents.
// Symbol: kiro2api/internal/logic/cursor.ParseCursorStreamChunk (3584B @ 0x17fda00)
//
// The 3584B size indicates complex protobuf field parsing with a large switch
// statement for different message types.
//
// The Connect protocol frames each message with a 5-byte prefix:
//   - byte 0: flags (0 = data, 1 = trailer)
//   - bytes 1-4: big-endian uint32 message length
//
// After deframing, the protobuf message contains fields for:
//   - field 1: text delta (string)
//   - field 2: thinking delta (string)
//   - field 3: tool call start (message with id + name)
//   - field 4: tool call arguments delta (string)
//   - field 5: finish reason (enum)
//   - field 6: usage stats (message)
//   - field 7: error (message)
func ParseCursorStreamChunk(data []byte) ([]CursorStreamEvent, error) {
	var events []CursorStreamEvent

	if len(data) < 5 {
		return nil, fmt.Errorf("chunk too short: %d bytes", len(data))
	}

	// Read Connect protocol frame header
	flags := data[0]
	msgLen := uint32(data[1])<<24 | uint32(data[2])<<16 | uint32(data[3])<<8 | uint32(data[4])

	if flags == 1 {
		// Trailer frame — end of stream
		events = append(events, CursorStreamEvent{
			Type:       "stop",
			StopReason: "stop",
		})
		return events, nil
	}

	if int(msgLen)+5 > len(data) {
		return nil, fmt.Errorf("incomplete message: expected %d bytes, got %d", msgLen, len(data)-5)
	}

	msgData := data[5 : 5+msgLen]

	// Parse protobuf fields manually
	// This is a simplified protobuf parser for the known message structure
	offset := 0
	for offset < len(msgData) {
		if offset >= len(msgData) {
			break
		}

		// Read field tag (varint)
		fieldTag, n := decodeVarint(msgData[offset:])
		if n <= 0 {
			break
		}
		offset += n

		fieldNumber := fieldTag >> 3
		wireType := fieldTag & 0x7

		switch fieldNumber {
		case 1: // text delta (length-delimited string)
			if wireType != 2 {
				offset = skipField(msgData, offset, wireType)
				continue
			}
			strLen, n := decodeVarint(msgData[offset:])
			if n <= 0 {
				break
			}
			offset += n
			if offset+int(strLen) > len(msgData) {
				break
			}
			text := string(msgData[offset : offset+int(strLen)])
			offset += int(strLen)

			events = append(events, CursorStreamEvent{
				Type: "text",
				Text: text,
			})

		case 2: // thinking delta (length-delimited string)
			if wireType != 2 {
				offset = skipField(msgData, offset, wireType)
				continue
			}
			strLen, n := decodeVarint(msgData[offset:])
			if n <= 0 {
				break
			}
			offset += n
			if offset+int(strLen) > len(msgData) {
				break
			}
			text := string(msgData[offset : offset+int(strLen)])
			offset += int(strLen)

			events = append(events, CursorStreamEvent{
				Type: "thinking",
				Text: text,
			})

		case 3: // tool call start (length-delimited message)
			if wireType != 2 {
				offset = skipField(msgData, offset, wireType)
				continue
			}
			msgLen, n := decodeVarint(msgData[offset:])
			if n <= 0 {
				break
			}
			offset += n
			if offset+int(msgLen) > len(msgData) {
				break
			}
			toolMsg := msgData[offset : offset+int(msgLen)]
			offset += int(msgLen)

			// Parse inner message for tool call ID and function name
			toolID, funcName := parseToolCallStart(toolMsg)
			events = append(events, CursorStreamEvent{
				Type:         "tool_call",
				ToolCallID:   toolID,
				FunctionName: funcName,
			})

		case 4: // tool call arguments delta (length-delimited string)
			if wireType != 2 {
				offset = skipField(msgData, offset, wireType)
				continue
			}
			strLen, n := decodeVarint(msgData[offset:])
			if n <= 0 {
				break
			}
			offset += n
			if offset+int(strLen) > len(msgData) {
				break
			}
			args := string(msgData[offset : offset+int(strLen)])
			offset += int(strLen)

			events = append(events, CursorStreamEvent{
				Type:      "tool_call_args",
				Arguments: args,
			})

		case 5: // finish reason (varint enum)
			if wireType != 0 {
				offset = skipField(msgData, offset, wireType)
				continue
			}
			reason, n := decodeVarint(msgData[offset:])
			if n <= 0 {
				break
			}
			offset += n

			stopReason := "stop"
			switch reason {
			case 0:
				stopReason = "stop"
			case 1:
				stopReason = "length"
			case 2:
				stopReason = "tool_calls"
			case 3:
				stopReason = "content_filter"
			}

			events = append(events, CursorStreamEvent{
				Type:       "stop",
				StopReason: stopReason,
			})

		case 6: // usage stats (length-delimited message)
			if wireType != 2 {
				offset = skipField(msgData, offset, wireType)
				continue
			}
			usageMsgLen, n := decodeVarint(msgData[offset:])
			if n <= 0 {
				break
			}
			offset += n
			if offset+int(usageMsgLen) > len(msgData) {
				break
			}
			usageMsg := msgData[offset : offset+int(usageMsgLen)]
			offset += int(usageMsgLen)

			promptTok, completionTok := parseUsageStats(usageMsg)
			events = append(events, CursorStreamEvent{
				Type:             "usage",
				PromptTokens:     promptTok,
				CompletionTokens: completionTok,
			})

		case 7: // error (length-delimited message)
			if wireType != 2 {
				offset = skipField(msgData, offset, wireType)
				continue
			}
			errMsgLen, n := decodeVarint(msgData[offset:])
			if n <= 0 {
				break
			}
			offset += n
			if offset+int(errMsgLen) > len(msgData) {
				break
			}
			errMsg := msgData[offset : offset+int(errMsgLen)]
			offset += int(errMsgLen)

			events = append(events, CursorStreamEvent{
				Type:         "error",
				ErrorMessage: parseErrorMessage(errMsg),
			})

		default:
			// Unknown field — skip
			offset = skipField(msgData, offset, wireType)
		}
	}

	return events, nil
}

// ============================================================================
// Protobuf Helpers
// ============================================================================

// decodeVarint decodes a protobuf varint from the byte slice.
// Returns the value and number of bytes consumed.
func decodeVarint(data []byte) (uint64, int) {
	var val uint64
	for i, b := range data {
		if i >= 10 {
			return 0, -1 // overflow
		}
		val |= uint64(b&0x7F) << (7 * uint(i))
		if b < 0x80 {
			return val, i + 1
		}
	}
	return 0, -1
}

// skipField skips a protobuf field based on its wire type.
// Returns the new offset after skipping.
func skipField(data []byte, offset int, wireType uint64) int {
	switch wireType {
	case 0: // varint
		for offset < len(data) {
			if data[offset] < 0x80 {
				return offset + 1
			}
			offset++
		}
	case 1: // 64-bit
		return offset + 8
	case 2: // length-delimited
		strLen, n := decodeVarint(data[offset:])
		if n <= 0 {
			return len(data)
		}
		return offset + n + int(strLen)
	case 5: // 32-bit
		return offset + 4
	}
	return len(data) // unknown wire type — skip to end
}

// parseToolCallStart parses the inner protobuf message for a tool call start event.
// Returns (toolCallID, functionName).
func parseToolCallStart(data []byte) (string, string) {
	var toolID, funcName string
	offset := 0

	for offset < len(data) {
		fieldTag, n := decodeVarint(data[offset:])
		if n <= 0 {
			break
		}
		offset += n

		fieldNumber := fieldTag >> 3
		wireType := fieldTag & 0x7

		if wireType != 2 {
			offset = skipField(data, offset, wireType)
			continue
		}

		strLen, n := decodeVarint(data[offset:])
		if n <= 0 {
			break
		}
		offset += n
		if offset+int(strLen) > len(data) {
			break
		}

		str := string(data[offset : offset+int(strLen)])
		offset += int(strLen)

		switch fieldNumber {
		case 1:
			toolID = str
		case 2:
			funcName = str
		}
	}

	// Generate tool call ID if not provided
	if toolID == "" {
		toolID = fmt.Sprintf("call_%s", generateCursorKey())
	}

	return toolID, funcName
}

// parseUsageStats parses the inner protobuf message for usage statistics.
// Returns (promptTokens, completionTokens).
func parseUsageStats(data []byte) (int, int) {
	var promptTok, completionTok int
	offset := 0

	for offset < len(data) {
		fieldTag, n := decodeVarint(data[offset:])
		if n <= 0 {
			break
		}
		offset += n

		fieldNumber := fieldTag >> 3
		wireType := fieldTag & 0x7

		if wireType != 0 {
			offset = skipField(data, offset, wireType)
			continue
		}

		val, n := decodeVarint(data[offset:])
		if n <= 0 {
			break
		}
		offset += n

		switch fieldNumber {
		case 1:
			promptTok = int(val)
		case 2:
			completionTok = int(val)
		}
	}

	return promptTok, completionTok
}

// parseErrorMessage parses the inner protobuf message for an error event.
// Returns the error message string.
func parseErrorMessage(data []byte) string {
	offset := 0

	for offset < len(data) {
		fieldTag, n := decodeVarint(data[offset:])
		if n <= 0 {
			break
		}
		offset += n

		fieldNumber := fieldTag >> 3
		wireType := fieldTag & 0x7

		if wireType != 2 {
			offset = skipField(data, offset, wireType)
			continue
		}

		strLen, n := decodeVarint(data[offset:])
		if n <= 0 {
			break
		}
		offset += n
		if offset+int(strLen) > len(data) {
			break
		}

		str := string(data[offset : offset+int(strLen)])
		offset += int(strLen)

		if fieldNumber == 1 {
			return str
		}
	}

	return "unknown error"
}

// Ensure strings import is used
var _ = strings.TrimSpace
