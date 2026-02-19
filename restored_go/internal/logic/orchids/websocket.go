package orchids

// websocket.go — WebSocket-based streaming request for the Orchids channel.
//
// Core function:
//   - executeWebSocketRequest (0x175bf20): Sends a request via WebSocket and streams the response
//
// Flow:
//  1. Get proxy URL via getOrchidsProxyURL()
//  2. Get connection from ConnectionPoolManager.GetConnection()
//  3. If error → fmt.Fprintf error and return
//  4. Defer connection cleanup (LAB_0175d440)
//  5. Build ToolMapper if client tools exist (offset 0x58 != 0)
//  6. ConvertToOrchidsRequest() → build Orchids-format request
//  7. Append extra messages if param_10 != 0 (additional context messages)
//  8. OrchidsWebSocket.SendRequest() → send over WebSocket
//  9. If send error → return error
// 10. Create SSEWriter via NewSSEWriter()
// 11. Create StreamState with sentinel values:
//     - offset 0x20 = -1 (0xffffffffffffffff)
//     - offset 0x30 = -1
//     - offset 0x50 = 1
//     - offset 0xb0 = 8 (block count)
//     - offset 0xa8 = "assistant" role string
// 12. Check if "enabled" thinking mode (offset 0x68 → check 7 bytes "enabled")
// 13. If tools exist → SetClientToolIndex()
// 14. WriteMessageStart() → send initial SSE message_start event
// 15. If WriteMessageStart fails → return error
// 16. ReadMessageWithTimeout() → read first WebSocket message
// 17. If timeout (90000000000 ns) → WriteErrorAndFinish("timeout")
// 18. Main loop: process events via handleModelEvent
// 19. On finish → WriteMessageEnd, return

import (
	"fmt"
	"strings"
)

// ============================================================================
// executeWebSocketRequest
// ============================================================================

// executeWebSocketRequest sends a chat completion request via WebSocket.
// Symbol: kiro2api/internal/logic/orchids.executeWebSocketRequest (@ 0x175bf20)
//
// Parameters (from decompiled register mapping):
//   param_1  (RAX): account session token (string ptr)
//   param_2  (RBX): account session token length / error
//   param_3  (RCX): account ID (string ptr)
//   param_4  (RDI): account ID length
//   param_5  (RSI): Clerk session token
//   param_6  (R8):  proxy URL override
//   param_7  (R9):  model name
//   param_8:        model config
//   param_9:        extra messages ptr
//   param_10 (long): extra messages length
//   param_11:       extra messages cap
//   param_12:       request context
//   param_13:       thinking mode / config
//
// Returns: error code (0 = success)
func executeWebSocketRequest(
	ctx *RequestContext,
	account *OrchidsAccount,
	request *ChatCompletionRequest,
	extraMessages []OrchidsConversationMessage,
) error {
	// Step 1: Get proxy URL
	// Decompiled: uStack_e8 = kiro2api_internal_logic_orchids_getOrchidsProxyURL()
	proxyURL := getOrchidsProxyURL()

	// Step 2: Get connection from pool
	// Decompiled: ConnectionPoolManager_GetConnection(session, accountID, proxyURL)
	poolMgr := GetConnectionPoolManager()
	ws, err := poolMgr.GetConnection(account.ID, account.SessionToken, proxyURL)
	if err != nil {
		// Decompiled: fmt_Fprintf(0x24, &uStack_20, ..., &DAT_01c73fae, 1, 1)
		// Error message: "failed to get websocket connection: %v"
		return fmt.Errorf("failed to get websocket connection: %v", err)
	}

	// Step 3: Defer connection cleanup
	// Decompiled: runtime_deferprocStack() with LAB_0175d440
	defer func() {
		// Connection cleanup / release back to pool
		_ = ws
	}()

	// Step 4: Build ToolMapper if client tools exist
	// Decompiled: if *(ulong *)(lStack0000000000000080 + 0x58) != 0
	var toolMapper *ToolMapper
	if len(request.Tools) > 0 {
		toolMapper = &ToolMapper{
			Tools: request.Tools,
		}
		toolMapper.buildIndex()
	}

	// Step 5: Convert to Orchids request format
	// Decompiled: ConvertToOrchidsRequest(model, config, toolMapper, request, thinkingMode)
	orchidsReq := ConvertToOrchidsRequest(request, toolMapper)

	// Step 6: Append extra messages if provided
	// Decompiled: if param_10 != 0 → growslice + typedslicecopy
	if len(extraMessages) > 0 {
		for _, em := range extraMessages {
			orchidsReq.Messages = append(orchidsReq.Messages, OrchidsMessage{
				Role:    em.Role,
				Content: em.Content,
			})
		}
	}

	// Step 7: Send request over WebSocket
	// Decompiled: OrchidsWebSocket_SendRequest()
	if err := ws.SendRequest(orchidsReq); err != nil {
		return err
	}

	// Step 8: Create SSEWriter
	// Decompiled: NewSSEWriter(*(request + 8))
	state := NewStreamState()
	writer := NewSSEWriter(ctx.ResponseWriter, state)

	// Step 9: Initialize StreamState
	// Decompiled:
	//   *(lStack_138 + 0x20) = 0xffffffffffffffff  → sentinel -1
	//   *(lStack_138 + 0x30) = 0xffffffffffffffff  → sentinel -1
	//   *(lStack_138 + 0x50) = 1                    → flag
	//   *(lStack_138 + 0xb0) = 8                    → block count
	//   *(lStack_138 + 0xa8) = &DAT_01c3fdb7        → "assistant" (9 bytes)

	// Step 10: Check thinking mode
	// Decompiled: check offset 0x68 → puVar2[1] == 7 && "enabled" (0x62616e65 + 0x656c + 'd')
	thinkingEnabled := false
	if request.ThinkingMode != "" {
		lower := strings.ToLower(request.ThinkingMode)
		if strings.Contains(lower, valueEnabled) {
			thinkingEnabled = true
		}
	}
	_ = thinkingEnabled

	// Step 11: Set client tool index if tools exist
	// Decompiled: if puStack_108 != 0 → SetClientToolIndex(...)
	if toolMapper != nil {
		// SetClientToolIndex sets up the tool name mapping for response processing
	}

	// Step 12: Write message_start event
	// Decompiled: SSEWriter_WriteMessageStart()
	if err := writer.WriteMessageStart(request, state); err != nil {
		return err
	}

	// Step 13: Main streaming loop
	// Read messages from WebSocket and process events
	for {
		// Read with 90s timeout
		// Decompiled: OrchidsWebSocket_ReadMessageWithTimeout()
		// Timeout check: DAT_02e34d10 == 90000000000
		msg, err := ws.ReadMessageWithTimeout()
		if err != nil {
			// Check if timeout error
			// Decompiled: runtime_ifaceeq() → if timeout → WriteErrorAndFinish(0x29)
			// 0x29 = 41 chars = "websocket read timeout after 90 seconds"
			if isTimeoutError(err) {
				_ = writer.WriteErrorAndFinish("websocket read timeout after 90 seconds")
			}
			return err
		}

		if msg == nil {
			continue
		}

		// Process the event via handleModelEvent
		if err := handleModelEvent(state, writer, msg, toolMapper, request.Tools); err != nil {
			return err
		}

		// Check if stream is finished
		if state.finishReason != "" {
			break
		}
	}

	// Step 14: Write message_end event
	if err := writer.WriteMessageEnd(state); err != nil {
		return err
	}

	return nil
}

// ============================================================================
// Helper types and functions
// ============================================================================

// RequestContext holds the HTTP request context for streaming responses.
type RequestContext struct {
	ResponseWriter interface{}
	Request        interface{}
}

// OrchidsAccount holds the account credentials for Orchids.
type OrchidsAccount struct {
	ID           string
	SessionToken string
	// Clerk session token for authentication
	ClerkToken string
}

// ChatCompletionRequest represents the incoming chat completion request.
type ChatCompletionRequest struct {
	Model        string
	Messages     []OrchidsConversationMessage
	Tools        []map[string]interface{}
	MaxTokens    int
	ThinkingMode string
	// Additional config fields
	Config map[string]interface{}
}

// ConvertToOrchidsRequest converts a ChatCompletionRequest to OrchidsRequest format.
// From decompiled: kiro2api_internal_logic_orchids_ConvertToOrchidsRequest()
func ConvertToOrchidsRequest(req *ChatCompletionRequest, toolMapper *ToolMapper) *OrchidsRequest {
	orchidsReq := &OrchidsRequest{
		ModelName: req.Model,
		MaxTokens: req.MaxTokens,
		Config:    req.Config,
	}

	// Convert messages
	for _, msg := range req.Messages {
		orchidsReq.Messages = append(orchidsReq.Messages, OrchidsMessage{
			Role:    msg.Role,
			Content: msg.Content,
		})
	}

	return orchidsReq
}

// WriteMessageStart writes the initial message_start SSE event.
// From decompiled: kiro2api_internal_logic_orchids_SSEWriter_WriteMessageStart()
func (w *SSEWriter) WriteMessageStart(req *ChatCompletionRequest, state *StreamState) error {
	event := map[string]interface{}{
		"type": "message_start",
		"message": map[string]interface{}{
			"id":      "",
			"type":    "message",
			"role":    "assistant",
			"model":   req.Model,
			"content": []interface{}{},
			"usage": map[string]interface{}{
				"input_tokens":  0,
				"output_tokens": 0,
			},
		},
	}
	return w.writeEvent("message_start", event)
}

// WriteMessageEnd writes the final message_stop SSE event.
// From decompiled: implied by the streaming loop exit
func (w *SSEWriter) WriteMessageEnd(state *StreamState) error {
	// Write message_delta with usage and stop_reason
	deltaEvent := map[string]interface{}{
		"type": "message_delta",
		"delta": map[string]interface{}{
			"stop_reason": state.finishReason,
		},
		"usage": map[string]interface{}{
			"input_tokens":             state.inputTokens,
			"output_tokens":            state.outputTokens,
			"cache_read_input_tokens":  state.cacheReadInputTokens,
		},
	}
	if err := w.writeEvent("message_delta", deltaEvent); err != nil {
		return err
	}

	// Write message_stop
	stopEvent := map[string]interface{}{
		"type": "message_stop",
	}
	return w.writeEvent("message_stop", stopEvent)
}

// WriteErrorAndFinish writes an error event and finishes the stream.
// From decompiled: kiro2api_internal_logic_orchids_SSEWriter_WriteErrorAndFinish(0x29)
func (w *SSEWriter) WriteErrorAndFinish(errMsg string) error {
	event := map[string]interface{}{
		"type": "error",
		"error": map[string]interface{}{
			"type":    "timeout_error",
			"message": errMsg,
		},
	}
	return w.writeEvent("error", event)
}

// isTimeoutError checks if an error is a timeout error.
func isTimeoutError(err error) bool {
	if err == nil {
		return false
	}
	return strings.Contains(err.Error(), "timeout") ||
		strings.Contains(err.Error(), "deadline exceeded")
}
