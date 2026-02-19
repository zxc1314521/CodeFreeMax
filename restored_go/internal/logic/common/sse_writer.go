package common

import (
	"encoding/json"
	"fmt"
	"net/http"
	"sync"

	"github.com/google/uuid"
)

// SSEWriter writes Server-Sent Events to an HTTP response writer.
type SSEWriter struct {
	w       http.ResponseWriter
	flusher http.Flusher
	mu      sync.Mutex
	id      string
	model   string
}

// NewSSEWriter creates a new SSEWriter wrapping the given ResponseWriter.
func NewSSEWriter(w http.ResponseWriter) *SSEWriter {
	flusher, _ := w.(http.Flusher)
	w.Header().Set("Content-Type", "text/event-stream")
	w.Header().Set("Cache-Control", "no-cache")
	w.Header().Set("Connection", "keep-alive")
	return &SSEWriter{
		w:       w,
		flusher: flusher,
		id:      "chatcmpl-" + uuid.New().String(),
	}
}

// SetModel sets the model name for SSE chunks.
func (s *SSEWriter) SetModel(model string) {
	s.model = model
}

func (s *SSEWriter) writeSSE(data interface{}) error {
	s.mu.Lock()
	defer s.mu.Unlock()
	jsonBytes, err := json.Marshal(data)
	if err != nil {
		return err
	}
	_, err = fmt.Fprintf(s.w, "data: %s\n\n", jsonBytes)
	if err != nil {
		return err
	}
	if s.flusher != nil {
		s.flusher.Flush()
	}
	return nil
}

// WriteContent writes a text content delta.
func (s *SSEWriter) WriteContent(content string) error {
	return s.writeSSE(map[string]interface{}{
		"id":      s.id,
		"object":  "chat.completion.chunk",
		"model":   s.model,
		"choices": []map[string]interface{}{
			{"index": 0, "delta": map[string]interface{}{"content": content}},
		},
	})
}

// WriteThinkingStart writes the start of a thinking block.
func (s *SSEWriter) WriteThinkingStart() error {
	return s.writeSSE(map[string]interface{}{
		"id":      s.id,
		"object":  "chat.completion.chunk",
		"model":   s.model,
		"choices": []map[string]interface{}{
			{"index": 0, "delta": map[string]interface{}{"reasoning": ""}},
		},
	})
}

// WriteThinkingEnd writes the end of a thinking block.
func (s *SSEWriter) WriteThinkingEnd() error {
	return nil // no-op, thinking ends when content starts
}

// WriteThinking writes a thinking content delta.
func (s *SSEWriter) WriteThinking(content string) error {
	return s.writeSSE(map[string]interface{}{
		"id":      s.id,
		"object":  "chat.completion.chunk",
		"model":   s.model,
		"choices": []map[string]interface{}{
			{"index": 0, "delta": map[string]interface{}{"reasoning": content}},
		},
	})
}

// WriteToolCallStart writes the start of a tool call.
func (s *SSEWriter) WriteToolCallStart(id string, name string) error {
	return s.writeSSE(map[string]interface{}{
		"id":      s.id,
		"object":  "chat.completion.chunk",
		"model":   s.model,
		"choices": []map[string]interface{}{
			{"index": 0, "delta": map[string]interface{}{
				"tool_calls": []map[string]interface{}{
					{"index": 0, "id": id, "type": "function", "function": map[string]interface{}{"name": name, "arguments": ""}},
				},
			}},
		},
	})
}

// WriteToolCallDelta writes a tool call argument delta.
func (s *SSEWriter) WriteToolCallDelta(delta string) error {
	return s.writeSSE(map[string]interface{}{
		"id":      s.id,
		"object":  "chat.completion.chunk",
		"model":   s.model,
		"choices": []map[string]interface{}{
			{"index": 0, "delta": map[string]interface{}{
				"tool_calls": []map[string]interface{}{
					{"index": 0, "function": map[string]interface{}{"arguments": delta}},
				},
			}},
		},
	})
}

// WriteToolCallEnd writes the end of a tool call.
func (s *SSEWriter) WriteToolCallEnd() error {
	return nil
}

// WriteStopReason writes the stop reason.
func (s *SSEWriter) WriteStopReason(reason string) error {
	return s.writeSSE(map[string]interface{}{
		"id":      s.id,
		"object":  "chat.completion.chunk",
		"model":   s.model,
		"choices": []map[string]interface{}{
			{"index": 0, "delta": map[string]interface{}{}, "finish_reason": reason},
		},
	})
}

// WriteUsage writes usage information.
func (s *SSEWriter) WriteUsage(inputTokens, outputTokens int) error {
	return s.writeSSE(map[string]interface{}{
		"id":      s.id,
		"object":  "chat.completion.chunk",
		"model":   s.model,
		"usage": map[string]interface{}{
			"prompt_tokens":     inputTokens,
			"completion_tokens": outputTokens,
			"total_tokens":      inputTokens + outputTokens,
		},
	})
}

// WriteDone writes the [DONE] marker.
func (s *SSEWriter) WriteDone() error {
	s.mu.Lock()
	defer s.mu.Unlock()
	_, err := fmt.Fprintf(s.w, "data: [DONE]\n\n")
	if s.flusher != nil {
		s.flusher.Flush()
	}
	return err
}
