package kiro

// stream.go — Streaming response parsing for the Kiro channel.
//
// Functions:
//   - ParseStreamResponse             (224B  @ 0x17aac80) — Entry point for stream parsing
//   - ParseStreamResponse.func1       (320B  @ 0x17aad60) — Stream parser closure (main loop)
//   - ParseStreamResponse.func1.deferwrap1 (96B @ 0x17aaea0) — Deferred cleanup
//   - extractContent                  (736B  @ 0x17aaf00) — Extract content from stream event
//
// The AWS Q Developer API returns streaming responses as Server-Sent Events (SSE).
// Each event contains a JSON payload with content deltas, tool use events,
// stop reasons, and usage information.
//
// Stream event format (from decompiled extractContent analysis):
//   {
//     "type": "content_block_delta" | "content_block_start" | "message_stop" | ...,
//     "delta": {
//       "type": "text_delta",
//       "text": "..."
//     },
//     "content_block": {
//       "type": "tool_use",
//       "id": "...",
//       "name": "..."
//     },
//     "stop_reason": "end_turn" | "tool_use" | "max_tokens",
//     "usage": {
//       "input_tokens": N,
//       "output_tokens": N
//     }
//   }

import (
	"bufio"
	"context"
	"encoding/json"
	"fmt"
	"io"
	"strings"

	"github.com/gogf/gf/v2/frame/gins"

	"kiro2api/internal/logic/common"
)

// ============================================================================
// Stream Constants
// ============================================================================

const (
	// SSE event prefixes
	sseDataPrefix  = "data: "
	sseDoneMarker  = "[DONE]"

	// Event types from AWS Q streaming
	eventContentBlockDelta = "content_block_delta"
	eventContentBlockStart = "content_block_start"
	eventContentBlockStop  = "content_block_stop"
	eventMessageStart      = "message_start"
	eventMessageDelta      = "message_delta"
	eventMessageStop       = "message_stop"

	// Delta types
	deltaTypeText     = "text_delta"
	deltaTypeThinking = "thinking_delta"
	deltaTypeToolUse  = "input_json_delta"

	// Content block types
	blockTypeText     = "text"
	blockTypeThinking = "thinking"
	blockTypeToolUse  = "tool_use"
)

// ============================================================================
// StreamEvent (raw SSE event)
// ============================================================================

// rawStreamEvent represents a raw SSE event from the AWS Q API.
type rawStreamEvent struct {
	Type  string          `json:"type"`
	Index int             `json:"index,omitempty"`
	Delta json.RawMessage `json:"delta,omitempty"`

	// For content_block_start
	ContentBlock json.RawMessage `json:"content_block,omitempty"`

	// For message_delta
	StopReason string    `json:"stop_reason,omitempty"`
	Usage      *rawUsage `json:"usage,omitempty"`

	// For message_start
	Message json.RawMessage `json:"message,omitempty"`
}

// rawDelta represents a delta object within a stream event.
type rawDelta struct {
	Type         string `json:"type"`
	Text         string `json:"text,omitempty"`
	Thinking     string `json:"thinking,omitempty"`
	PartialJSON  string `json:"partial_json,omitempty"`
	StopReason   string `json:"stop_reason,omitempty"`
}

// rawContentBlock represents a content block start event.
type rawContentBlock struct {
	Type string `json:"type"`
	ID   string `json:"id,omitempty"`
	Name string `json:"name,omitempty"`
}

// rawUsage represents usage information in the stream.
type rawUsage struct {
	InputTokens  int `json:"input_tokens"`
	OutputTokens int `json:"output_tokens"`
}

// ============================================================================
// ParseStreamResponse
// ============================================================================

// ParseStreamResponse parses a streaming response from the AWS Q Developer API
// and writes OpenAI-compatible SSE events to the SSEWriter.
//
// Symbol: kiro2api/internal/logic/kiro.(*sKiro).ParseStreamResponse (224B @ 0x17aac80)
//
// From decompiled (224 bytes — thin wrapper):
//   1. Create closure (func1 @ 0x17aad60) with captured variables
//   2. Launch the closure as the stream parser
//   3. Deferred cleanup (deferwrap1 @ 0x17aaea0)
//
// The actual parsing logic is in func1 (320B @ 0x17aad60):
//   1. Create bufio.Scanner on response body
//   2. Loop: read lines, check for "data: " prefix
//   3. Parse JSON event
//   4. Call extractContent to process each event
//   5. Write to SSEWriter
//   6. On "[DONE]" → break
func (s *sKiro) ParseStreamResponse(
	ctx context.Context,
	body io.ReadCloser,
	writer *common.SSEWriter,
	account map[string]interface{},
) error {
	logger := gins.Log()

	// Deferred cleanup (deferwrap1 @ 0x17aaea0)
	defer func() {
		if body != nil {
			body.Close()
		}
	}()

	scanner := bufio.NewScanner(body)
	// Increase scanner buffer for large events
	scanner.Buffer(make([]byte, 0, 64*1024), 1024*1024)

	var (
		currentToolUse *KiroToolUseEvent
		toolInputBuf   strings.Builder
		totalUsage     KiroUsage
		contentIndex   int
	)

	for scanner.Scan() {
		// Check context cancellation
		select {
		case <-ctx.Done():
			logger.Info(nil, "[Kiro] Stream cancelled by context")
			return ctx.Err()
		default:
		}

		line := scanner.Text()

		// Skip empty lines and non-data lines
		if !strings.HasPrefix(line, sseDataPrefix) {
			continue
		}

		data := strings.TrimPrefix(line, sseDataPrefix)
		data = strings.TrimSpace(data)

		// Check for done marker
		if data == sseDoneMarker {
			// Write final usage if available
			if totalUsage.InputTokens > 0 || totalUsage.OutputTokens > 0 {
				writer.WriteUsage(totalUsage.InputTokens, totalUsage.OutputTokens)
			}
			writer.WriteDone()
			break
		}

		// Parse the event JSON
		var event rawStreamEvent
		if err := json.Unmarshal([]byte(data), &event); err != nil {
			logger.Warningf(nil, "[Kiro] Failed to parse stream event: %v", err)
			continue
		}

		// Extract and process content
		s.handleStreamEvent(
			&event,
			writer,
			&currentToolUse,
			&toolInputBuf,
			&totalUsage,
			&contentIndex,
		)
	}

	if err := scanner.Err(); err != nil {
		return fmt.Errorf("stream scanner error: %w", err)
	}

	return nil
}

// ============================================================================
// handleStreamEvent
// ============================================================================

// handleStreamEvent processes a single stream event and writes to the SSEWriter.
// This corresponds to the main body of ParseStreamResponse.func1 (320B @ 0x17aad60).
func (s *sKiro) handleStreamEvent(
	event *rawStreamEvent,
	writer *common.SSEWriter,
	currentToolUse **KiroToolUseEvent,
	toolInputBuf *strings.Builder,
	totalUsage *KiroUsage,
	contentIndex *int,
) {
	switch event.Type {
	case eventContentBlockStart:
		// New content block starting
		var block rawContentBlock
		if err := json.Unmarshal(event.ContentBlock, &block); err != nil {
			return
		}

		switch block.Type {
		case blockTypeToolUse:
			// Start of a tool use block
			*currentToolUse = &KiroToolUseEvent{
				ID:   block.ID,
				Name: block.Name,
			}
			toolInputBuf.Reset()
			// Write tool call start
			writer.WriteToolCallStart(block.ID, block.Name)
		case blockTypeText:
			// Text block start — nothing special needed
		case blockTypeThinking:
			// Thinking block start
			writer.WriteThinkingStart()
		}

	case eventContentBlockDelta:
		// Content delta within a block
		var delta rawDelta
		if err := json.Unmarshal(event.Delta, &delta); err != nil {
			return
		}

		switch delta.Type {
		case deltaTypeText:
			// Text content delta
			if delta.Text != "" {
				writer.WriteContent(delta.Text)
				*contentIndex++
			}

		case deltaTypeThinking:
			// Thinking content delta
			if delta.Thinking != "" {
				writer.WriteThinking(delta.Thinking)
			}

		case deltaTypeToolUse:
			// Tool use input JSON delta
			if delta.PartialJSON != "" {
				toolInputBuf.WriteString(delta.PartialJSON)
				writer.WriteToolCallDelta(delta.PartialJSON)
			}
		}

	case eventContentBlockStop:
		// Content block finished
		if *currentToolUse != nil {
			(*currentToolUse).Input = toolInputBuf.String()
			writer.WriteToolCallEnd()
			*currentToolUse = nil
		}

	case eventMessageDelta:
		// Message-level delta (stop reason, usage)
		var delta rawDelta
		if event.Delta != nil {
			json.Unmarshal(event.Delta, &delta)
			if delta.StopReason != "" {
				writer.WriteStopReason(mapStopReason(delta.StopReason))
			}
		}
		if event.Usage != nil {
			totalUsage.InputTokens = event.Usage.InputTokens
			totalUsage.OutputTokens = event.Usage.OutputTokens
		}

	case eventMessageStart:
		// Message start — extract initial usage if present
		if event.Usage != nil {
			totalUsage.InputTokens = event.Usage.InputTokens
		}

	case eventMessageStop:
		// Message complete
		if event.Usage != nil {
			totalUsage.OutputTokens = event.Usage.OutputTokens
		}
	}
}

// ============================================================================
// extractContent
// ============================================================================

// extractContent extracts the text content from a stream event.
// Symbol: kiro2api/internal/logic/kiro.extractContent (736B @ 0x17aaf00)
//
// From decompiled (736 bytes):
//   1. Check event type
//   2. For content_block_delta with text_delta → return text
//   3. For content_block_delta with thinking_delta → return thinking text
//   4. For message_delta → return stop_reason
//   5. Otherwise return empty
//
// This is a simpler extraction function used for non-streaming contexts
// or for extracting content from individual events.
func extractContent(event *rawStreamEvent) string {
	if event == nil {
		return ""
	}

	switch event.Type {
	case eventContentBlockDelta:
		var delta rawDelta
		if err := json.Unmarshal(event.Delta, &delta); err != nil {
			return ""
		}
		switch delta.Type {
		case deltaTypeText:
			return delta.Text
		case deltaTypeThinking:
			return delta.Thinking
		case deltaTypeToolUse:
			return delta.PartialJSON
		}

	case eventMessageDelta:
		var delta rawDelta
		if event.Delta != nil {
			json.Unmarshal(event.Delta, &delta)
			return delta.StopReason
		}
	}

	return ""
}

// ============================================================================
// mapStopReason
// ============================================================================

// mapStopReason maps AWS Q stop reasons to OpenAI-compatible stop reasons.
func mapStopReason(reason string) string {
	switch reason {
	case "end_turn":
		return "stop"
	case "tool_use":
		return "tool_calls"
	case "max_tokens":
		return "length"
	case "stop_sequence":
		return "stop"
	default:
		return reason
	}
}
