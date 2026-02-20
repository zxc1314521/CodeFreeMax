package kiro

// stream.go — AWS Event Stream binary protocol parser for the Kiro channel.
//
// The AWS Q Developer /generateAssistantResponse endpoint returns responses
// using the AWS Event Stream binary protocol (NOT SSE).
//
// Binary message format:
//   [4 bytes] total message length (big-endian uint32)
//   [4 bytes] headers length (big-endian uint32)
//   [4 bytes] prelude CRC32
//   [headers_length bytes] headers
//   [body bytes] JSON payload
//   [4 bytes] message CRC32
//
// Headers are key-value pairs:
//   [1 byte] name length
//   [name_length bytes] name string
//   [1 byte] type tag (7=string, 6=binary, ...)
//   For string: [2 bytes] value length + [value_length bytes] value
//
// Key headers: :event-type, :message-type, :content-type
//
// Event types from de_ChatResponseStream:
//   - assistantResponseEvent  → { content: "..." }
//   - reasoningContentEvent   → { redactedContent, signature }
//   - toolUseEvent            → { name, toolUseId, input, stop }
//   - messageMetadataEvent    → { conversationId }
//   - metadataEvent           → { tokenUsage: { inputTokens, outputTokens } }
//   - meteringEvent           → { usage, unit, unitPlural }
//   - followupPromptEvent     → { followupPrompt }
//   - codeEvent, intentsEvent, citationEvent, etc.

import (
	"context"
	"encoding/binary"
	"encoding/json"
	"fmt"
	"io"
	"log"

	"kiro2api/internal/logic/common"
)

// ============================================================================
// AWS Event Stream Constants
// ============================================================================

const (
	// Minimum message size: 4 (total len) + 4 (headers len) + 4 (prelude CRC) + 4 (message CRC)
	minMessageLen = 16

	// Header type tags
	headerTypeString byte = 7
)

// ============================================================================
// Event payload structs (JSON bodies inside event stream messages)
// ============================================================================

// assistantResponsePayload is the JSON body of an assistantResponseEvent.
type assistantResponsePayload struct {
	Content string `json:"content"`
}

// toolUsePayload is the JSON body of a toolUseEvent.
type toolUsePayload struct {
	Name      string `json:"name"`
	ToolUseID string `json:"toolUseId"`
	Input     string `json:"input"`
	Stop      bool   `json:"stop"`
}

// metadataPayload is the JSON body of a metadataEvent.
type metadataPayload struct {
	TokenUsage *tokenUsagePayload `json:"tokenUsage,omitempty"`
}

// tokenUsagePayload is token usage info inside metadataEvent.
type tokenUsagePayload struct {
	InputTokens  int `json:"inputTokens"`
	OutputTokens int `json:"outputTokens"`
}

// reasoningPayload is the JSON body of a reasoningContentEvent.
type reasoningPayload struct {
	RedactedContent string `json:"redactedContent"`
	Signature       string `json:"signature"`
}

// ============================================================================
// ParseStreamResponse — AWS Event Stream binary protocol
// ============================================================================

// ParseStreamResponse reads AWS Event Stream binary messages from the response
// body and writes OpenAI-compatible SSE events to the SSEWriter.
func (s *sKiro) ParseStreamResponse(
	ctx context.Context,
	body io.ReadCloser,
	writer *common.SSEWriter,
	account map[string]interface{},
) error {
	defer func() {
		if body != nil {
			body.Close()
		}
	}()

	var (
		totalUsage KiroUsage
		msgCount   int
	)

	for {
		// Check context cancellation
		select {
		case <-ctx.Done():
			log.Printf("[Kiro][Stream] Cancelled by context after %d messages", msgCount)
			return ctx.Err()
		default:
		}

		// Read one AWS Event Stream message
		eventType, payload, err := readEventStreamMessage(body)
		if err == io.EOF || err == io.ErrUnexpectedEOF {
			log.Printf("[Kiro][Stream] Stream ended after %d messages", msgCount)
			break
		}
		if err != nil {
			log.Printf("[Kiro][Stream] Read error after %d messages: %v", msgCount, err)
			return fmt.Errorf("event stream read error: %w", err)
		}

		msgCount++
		if msgCount <= 5 {
			log.Printf("[Kiro][Stream] Message %d: event-type=%q, payload_len=%d, payload=%.200s",
				msgCount, eventType, len(payload), string(payload))
		}

		// Dispatch by event type
		switch eventType {
		case "assistantResponseEvent":
			var ev assistantResponsePayload
			if err := json.Unmarshal(payload, &ev); err == nil && ev.Content != "" {
				writer.WriteContent(ev.Content)
			}

		case "reasoningContentEvent":
			var ev reasoningPayload
			if err := json.Unmarshal(payload, &ev); err == nil && ev.RedactedContent != "" {
				writer.WriteThinking(ev.RedactedContent)
			}

		case "toolUseEvent":
			var ev toolUsePayload
			if err := json.Unmarshal(payload, &ev); err == nil {
				if ev.Name != "" {
					writer.WriteToolCallStart(ev.ToolUseID, ev.Name)
				}
				if ev.Input != "" {
					writer.WriteToolCallDelta(ev.Input)
				}
				if ev.Stop {
					writer.WriteToolCallEnd()
				}
			}

		case "metadataEvent":
			var ev metadataPayload
			if err := json.Unmarshal(payload, &ev); err == nil && ev.TokenUsage != nil {
				totalUsage.InputTokens = ev.TokenUsage.InputTokens
				totalUsage.OutputTokens = ev.TokenUsage.OutputTokens
			}

		case "messageMetadataEvent":
			// Log full payload to identify actual model info from AWS
			log.Printf("[Kiro][Stream] messageMetadataEvent payload: %s", string(payload))

		case "followupPromptEvent", "codeEvent",
			"intentsEvent", "citationEvent", "supplementaryWebLinksEvent",
			"interactionComponentsEvent", "contextUsageEvent",
			"dryRunSucceedEvent", "invalidStateEvent", "meteringEvent",
			"toolResultEvent", "codeReferenceEvent":
			// Known event types we don't need to forward
			if msgCount <= 10 {
				log.Printf("[Kiro][Stream] Skipping event: %s", eventType)
			}

		default:
			log.Printf("[Kiro][Stream] Unknown event type: %s", eventType)
		}
	}

	// Write final usage + done
	if totalUsage.InputTokens > 0 || totalUsage.OutputTokens > 0 {
		writer.WriteUsage(totalUsage.InputTokens, totalUsage.OutputTokens)
	}
	writer.WriteStopReason("stop")
	writer.WriteDone()

	log.Printf("[Kiro][Stream] Complete: %d messages, usage: in=%d out=%d",
		msgCount, totalUsage.InputTokens, totalUsage.OutputTokens)
	return nil
}

// ============================================================================
// readEventStreamMessage — binary protocol reader
// ============================================================================

// readEventStreamMessage reads a single AWS Event Stream binary message from r.
// Returns the :event-type header value and the JSON payload body.
//
// AWS Event Stream binary format:
//   [4 bytes] total_length    (big-endian uint32)
//   [4 bytes] headers_length  (big-endian uint32)
//   [4 bytes] prelude_crc32
//   [headers_length bytes] headers
//   [payload bytes] body      (total_length - headers_length - 16)
//   [4 bytes] message_crc32
func readEventStreamMessage(r io.Reader) (eventType string, payload []byte, err error) {
	// Read the 12-byte prelude: total_length(4) + headers_length(4) + prelude_crc(4)
	prelude := make([]byte, 12)
	if _, err = io.ReadFull(r, prelude); err != nil {
		return "", nil, err
	}

	totalLen := binary.BigEndian.Uint32(prelude[0:4])
	headersLen := binary.BigEndian.Uint32(prelude[4:8])
	// prelude CRC at prelude[8:12] — we skip validation for simplicity

	if totalLen < minMessageLen || totalLen > 16*1024*1024 {
		return "", nil, fmt.Errorf("invalid message length: %d", totalLen)
	}

	// Read the rest of the message: headers + body + message_crc
	remaining := int(totalLen) - 12
	buf := make([]byte, remaining)
	if _, err = io.ReadFull(r, buf); err != nil {
		return "", nil, err
	}

	// Parse headers
	headerBytes := buf[:headersLen]
	eventType, _ = parseEventStreamHeaders(headerBytes)

	// Extract body (between headers and trailing 4-byte message CRC)
	bodyStart := int(headersLen)
	bodyEnd := remaining - 4 // exclude message CRC
	if bodyEnd > bodyStart {
		payload = buf[bodyStart:bodyEnd]
	}

	return eventType, payload, nil
}

// ============================================================================
// parseEventStreamHeaders
// ============================================================================

// parseEventStreamHeaders parses AWS Event Stream headers and returns
// the :event-type and :message-type values.
//
// Header format:
//   [1 byte]  name_length
//   [N bytes] name
//   [1 byte]  type_tag (7 = string)
//   For string: [2 bytes] value_length + [M bytes] value
func parseEventStreamHeaders(data []byte) (eventType, messageType string) {
	pos := 0
	for pos < len(data) {
		if pos >= len(data) {
			break
		}

		// Name length
		nameLen := int(data[pos])
		pos++
		if pos+nameLen > len(data) {
			break
		}

		name := string(data[pos : pos+nameLen])
		pos += nameLen

		if pos >= len(data) {
			break
		}

		// Type tag
		typeTag := data[pos]
		pos++

		switch typeTag {
		case headerTypeString: // 7 = string
			if pos+2 > len(data) {
				return
			}
			valLen := int(binary.BigEndian.Uint16(data[pos : pos+2]))
			pos += 2
			if pos+valLen > len(data) {
				return
			}
			val := string(data[pos : pos+valLen])
			pos += valLen

			switch name {
			case ":event-type":
				eventType = val
			case ":message-type":
				messageType = val
			}

		case 0, 1: // boolean true/false — no value bytes
			// no additional bytes

		case 2: // byte
			pos++

		case 3: // short
			pos += 2

		case 4: // integer
			pos += 4

		case 5: // long
			pos += 8

		case 6: // binary
			if pos+2 > len(data) {
				return
			}
			binLen := int(binary.BigEndian.Uint16(data[pos : pos+2]))
			pos += 2 + binLen

		case 8: // timestamp
			pos += 8

		case 9: // uuid
			pos += 16

		default:
			// Unknown type — can't continue parsing
			return
		}
	}
	return
}
