package orchids

// stream_handler.go — SSE event handler/dispatcher for the Orchids channel.
//
// Core function:
//   - handleModelEvent (0x175d4a0): Dispatches incoming model events to appropriate handlers
//
// The Orchids streaming protocol sends events with a "type" field that determines
// how each event should be processed. This is the central event routing function.
//
// Event types handled (from switch on len(type)-6):
//   case 0  (len=6):  "finish"           → extract usage, set finish reason
//   case 4  (len=10): "text-delta"       → write text delta to SSE
//                     "text-start"       → start text block
//   case 7  (len=13): "reasoning-end"    → close reasoning block
//   case 8  (len=14): "tool-input-end"   → end tool call, write tool input
//   case 9  (len=15): "reasoning-delta"  → write thinking delta
//                     "reasoning-start"  → start reasoning block
//   case 10 (len=16): "tool-input-delta" → append tool input delta
//                     "tool-input-start" → start tool use block

import (
	"encoding/json"
	"strings"

	"github.com/google/uuid"
)

// ============================================================================
// StreamState
// ============================================================================

// StreamState tracks the state of an active streaming response.
// From decompiled: param_1 is the StreamState pointer, with fields at various offsets.
//
// Key offsets from decompiled:
//   0x18: isReasoningStarted (bool) — checked in reasoning-delta/reasoning-start
//   0x20: sentinelField (int64, init to -1)
//   0x28: isResponseStarted (bool) — checked in text-start
//   0x38: toolCallHasInput (bool) — checked in tool-input-end
//   0x60: pendingToolInput (ptr) — checked in tool-input-delta
//   0xb0: blockCount (int, init to 8)
type StreamState struct {
	// isReasoningStarted tracks whether reasoning mode has been entered
	// Offset 0x18: *(char *)(param_1 + 0x18)
	isReasoningStarted bool

	// isResponseStarted tracks whether the response has started
	// Offset 0x28: *(char *)(param_1 + 0x28)
	isResponseStarted bool

	// toolCallHasInput tracks whether current tool call has input
	// Offset 0x38: *(char *)(local_50 + 0x38)
	toolCallHasInput bool

	// pendingToolInput holds accumulated tool input JSON
	// Offset 0x60: *(long *)(param_1 + 0x60)
	pendingToolInput string

	// inputTokens from usage data
	inputTokens int64

	// outputTokens from usage data
	outputTokens int64

	// cacheReadInputTokens from usage data
	cacheReadInputTokens int64

	// finishReason stores the finish reason string
	finishReason string

	// currentToolCall holds the active tool call state
	// Offset from local_50 in tool-input-end handler
	currentToolCall *ToolCallState

	// blockCount tracks the number of content blocks
	blockCount int
}

// ToolCallState tracks the state of an active tool call.
// From decompiled: local_50 in tool-input-end, size ~0x40 bytes
// Offsets:
//   0x28: inputLength (long) — *(long *)(local_50 + 0x28)
//   0x30: toolName (string) — *(undefined8 *)(local_50 + 0x30)
//   0x38: hasInput (bool) — *(char *)(local_50 + 0x38)
type ToolCallState struct {
	ToolUseID   string
	ToolName    string
	Input       string
	InputLength int64
	HasInput    bool
}

// NewStreamState creates a new StreamState with default values.
// From decompiled: *(lStack_138 + 0x20) = 0xffffffffffffffff, *(lStack_138 + 0xb0) = 8
func NewStreamState() *StreamState {
	return &StreamState{
		blockCount: defaultBlockCount,
	}
}

// ShouldSkipModelEvent checks if this event should be skipped.
// From decompiled: kiro2api_internal_logic_orchids_StreamState_ShouldSkipModelEvent()
// Returns true if the event should be skipped (e.g., duplicate or invalid).
func (s *StreamState) ShouldSkipModelEvent() bool {
	// Decompiled: cVar1 = ShouldSkipModelEvent(); if cVar1 != '\0' return 0
	return false
}

// StartResponse marks the response as started.
// From decompiled: kiro2api_internal_logic_orchids_StreamState_StartResponse()
func (s *StreamState) StartResponse() {
	s.isResponseStarted = true
}

// StartReasoning marks reasoning mode as started.
// From decompiled: kiro2api_internal_logic_orchids_StreamState_StartReasoning()
func (s *StreamState) StartReasoning() {
	s.isReasoningStarted = true
}

// SetInputTokens sets the input token count from usage data.
// From decompiled: kiro2api_internal_logic_orchids_StreamState_SetInputTokens()
func (s *StreamState) SetInputTokens(tokens int64) {
	s.inputTokens = tokens
}

// SetOutputTokens sets the output token count from usage data.
// From decompiled: kiro2api_internal_logic_orchids_StreamState_SetOutputTokens()
func (s *StreamState) SetOutputTokens(tokens int64) {
	s.outputTokens = tokens
}

// SetCacheReadInputTokens sets the cache read input token count.
// From decompiled: kiro2api_internal_logic_orchids_StreamState_SetCacheReadInputTokens()
func (s *StreamState) SetCacheReadInputTokens(tokens int64) {
	s.cacheReadInputTokens = tokens
}

// SetFinishReason sets the finish reason.
// From decompiled: kiro2api_internal_logic_orchids_StreamState_SetFinishReason()
func (s *StreamState) SetFinishReason(reason string) {
	s.finishReason = reason
}

// EndToolCall ends the current tool call and returns its state.
// From decompiled: kiro2api_internal_logic_orchids_StreamState_EndToolCall()
// Returns the tool call state (local_50), or nil if no active tool call.
func (s *StreamState) EndToolCall() *ToolCallState {
	tc := s.currentToolCall
	s.currentToolCall = nil
	return tc
}

// AppendToolInput appends delta text to the pending tool input.
// From decompiled: kiro2api_internal_logic_orchids_StreamState_AppendToolInput()
func (s *StreamState) AppendToolInput(delta string) {
	s.pendingToolInput += delta
}

// UpdatePendingToolInput updates the pending tool input with parsed JSON.
// From decompiled: kiro2api_internal_logic_orchids_StreamState_UpdatePendingToolInput(*local_10)
func (s *StreamState) UpdatePendingToolInput(parsed interface{}) {
	if s.currentToolCall != nil {
		if data, err := json.Marshal(parsed); err == nil {
			s.currentToolCall.Input = string(data)
		}
	}
}

// ============================================================================
// SSEWriter
// ============================================================================

// SSEWriter handles writing SSE events to the response stream.
// From decompiled: various SSEWriter methods called in handleModelEvent.
type SSEWriter struct {
	// writer is the underlying response writer
	writer interface{}
	// state is the associated stream state
	state *StreamState
}

// NewSSEWriter creates a new SSEWriter.
func NewSSEWriter(writer interface{}, state *StreamState) *SSEWriter {
	return &SSEWriter{
		writer: writer,
		state:  state,
	}
}

// WriteBlockStart writes a content block start event.
// From decompiled: kiro2api_internal_logic_orchids_SSEWriter_WriteBlockStart(blockType, index, ...)
// blockType: 4 = "text", 8 = "thinking"
// Decompiled calls:
//   text-start:      WriteBlockStart(4, 0, ..., &DAT_01c397b2, 0)  — "text" block
//   reasoning-start: WriteBlockStart(8, 0, ..., &DAT_01c3fd97, 0)  — "thinking" block
func (w *SSEWriter) WriteBlockStart(blockType int, index int, typeStr string, subIndex int) error {
	// Build content_block_start event
	event := map[string]interface{}{
		"type":  "content_block_start",
		"index": w.state.blockCount,
	}

	switch blockType {
	case 4: // text block
		event["content_block"] = map[string]interface{}{
			"type": "text",
			"text": "",
		}
	case 8: // thinking block
		event["content_block"] = map[string]interface{}{
			"type":     "thinking",
			"thinking": "",
		}
	}

	w.state.blockCount++
	return w.writeEvent("content_block_start", event)
}

// EnsureTextBlockAndWriteDelta ensures a text block exists and writes a text delta.
// From decompiled: kiro2api_internal_logic_orchids_SSEWriter_EnsureTextBlockAndWriteDelta(...)
// Called for "text-delta" events.
func (w *SSEWriter) EnsureTextBlockAndWriteDelta(delta string) error {
	// Write content_block_delta event with text delta
	event := map[string]interface{}{
		"type":  "content_block_delta",
		"index": w.state.blockCount - 1,
		"delta": map[string]interface{}{
			"type": "text_delta",
			"text": delta,
		},
	}
	return w.writeEvent("content_block_delta", event)
}

// WriteThinkingDelta writes a thinking/reasoning delta event.
// From decompiled: kiro2api_internal_logic_orchids_SSEWriter_WriteThinkingDelta(...)
// Called for "reasoning-delta" events when isReasoningStarted is true.
func (w *SSEWriter) WriteThinkingDelta(delta string) error {
	event := map[string]interface{}{
		"type":  "content_block_delta",
		"index": w.state.blockCount - 1,
		"delta": map[string]interface{}{
			"type":     "thinking_delta",
			"thinking": delta,
		},
	}
	return w.writeEvent("content_block_delta", event)
}

// CloseReasoningBlock closes the current reasoning/thinking block.
// From decompiled: kiro2api_internal_logic_orchids_SSEWriter_CloseReasoningBlock()
// Called for "reasoning-end" events.
func (w *SSEWriter) CloseReasoningBlock() error {
	event := map[string]interface{}{
		"type":  "content_block_stop",
		"index": w.state.blockCount - 1,
	}
	return w.writeEvent("content_block_stop", event)
}

// WriteToolInputDelta writes a tool input JSON delta event.
// From decompiled: kiro2api_internal_logic_orchids_SSEWriter_WriteToolInputDelta()
// Called for "tool-input-delta" and "tool-input-end" events.
func (w *SSEWriter) WriteToolInputDelta() error {
	if w.state.pendingToolInput == "" {
		return nil
	}
	event := map[string]interface{}{
		"type":  "content_block_delta",
		"index": w.state.blockCount - 1,
		"delta": map[string]interface{}{
			"type":          "input_json_delta",
			"partial_json": w.state.pendingToolInput,
		},
	}
	w.state.pendingToolInput = ""
	return w.writeEvent("content_block_delta", event)
}

// StartToolUseBlock starts a new tool_use content block.
// From decompiled: kiro2api_internal_logic_orchids_SSEWriter_StartToolUseBlock(...)
// Called for "tool-input-start" events.
// Parameters from decompiled:
//   puVar11: tool ID string
//   lVar6:   mapped tool name
//   lVar8:   tool name length
//   lVar5:   original tool name
func (w *SSEWriter) StartToolUseBlock(toolID string, toolName string) error {
	event := map[string]interface{}{
		"type":  "content_block_start",
		"index": w.state.blockCount,
		"content_block": map[string]interface{}{
			"type":  "tool_use",
			"id":    toolID,
			"name":  toolName,
			"input": map[string]interface{}{},
		},
	}
	w.state.blockCount++
	return w.writeEvent("content_block_start", event)
}

// writeEvent writes a generic SSE event.
// From decompiled: kiro2api_internal_logic_orchids_SSEWriter_writeEvent(&DAT_01a233a0, ...)
func (w *SSEWriter) writeEvent(eventType string, data interface{}) error {
	// Marshal data to JSON and write as SSE event
	// Format: "event: {eventType}\ndata: {json}\n\n"
	_, _ = eventType, data
	return nil
}

// ============================================================================
// handleModelEvent
// ============================================================================

// handleModelEvent dispatches incoming model events to appropriate handlers.
// Symbol: kiro2api/internal/logic/orchids.handleModelEvent (@ 0x175d4a0)
//
// Parameters (from decompiled):
//   param_1 (long):       StreamState pointer
//   param_2 (undefined*): SSEWriter pointer
//   param_3:              event data (map)
//   param_4 (undefined*): tool mapper pointer
//   param_5 (long):       client tools length (for MapToolNameToClient)
//
// Algorithm:
//  1. Check ShouldSkipModelEvent() → if true, return 0
//  2. Extract "data" field from event → get nested map
//  3. Extract "type" field from data → get event type string
//  4. If data is nil, return 0
//  5. Switch on len(type) - 6:
//     - case 0 (finish): extract usage, set tokens, set finish reason
//     - case 4 (text-delta/text-start): write text delta or start text block
//     - case 7 (reasoning-end): close reasoning block
//     - case 8 (tool-input-end): end tool call, unmarshal input, write delta
//     - case 9 (reasoning-delta/reasoning-start): write thinking delta or start
//     - case 10 (tool-input-delta/tool-input-start): append/start tool input
//  6. Return error code (0 = success)
func handleModelEvent(
	state *StreamState,
	writer *SSEWriter,
	event map[string]interface{},
	toolMapper *ToolMapper,
	clientTools []map[string]interface{},
) error {
	// Step 1: Check if event should be skipped
	if state.ShouldSkipModelEvent() {
		return nil
	}

	// Step 2: Extract "data" field → nested map
	// Decompiled: mapaccess1_faststr(5) for "data" key
	dataRaw, ok := event[keyData]
	if !ok {
		return nil
	}
	data, ok := dataRaw.(map[string]interface{})
	if !ok {
		return nil
	}

	// Step 3: Extract "type" field from data
	// Decompiled: mapaccess1_faststr(4, ..., "type")
	eventType, ok := getStringField(data, keyType)
	if !ok || eventType == "" {
		return nil
	}

	// Step 4: Also extract the nested data map (for delta/usage access)
	// Decompiled: local_68 = puVar2[1] (the data map reference)

	// Step 5: Switch on event type
	// Decompiled: switch(lVar6 + -6) where lVar6 = len(type)
	switch eventType {

	// ---- case 0: "finish" (6 chars) ----
	case eventFinish:
		return handleFinishEvent(state, writer, data)

	// ---- case 4: "text-delta" (10 chars) ----
	case eventTextDelta:
		// Extract "delta" field → get text value
		// Decompiled: mapaccess1_faststr(5, ..., "delta")
		delta, ok := getStringField(data, keyDelta)
		if !ok || delta == "" {
			return nil
		}
		return writer.EnsureTextBlockAndWriteDelta(delta)

	// ---- case 4: "text-start" (10 chars) ----
	case eventTextStart:
		// Only start if response hasn't started yet
		// Decompiled: *(char *)(param_1 + 0x28) == '\0'
		if !state.isResponseStarted {
			state.StartResponse()
			// WriteBlockStart(4, 0, "text", 0)
			return writer.WriteBlockStart(4, 0, "text", 0)
		}

	// ---- case 7: "reasoning-end" (13 chars) ----
	case eventReasoningEnd:
		return writer.CloseReasoningBlock()

	// ---- case 8: "tool-input-end" (14 chars) ----
	case eventToolInputEnd:
		return handleToolInputEnd(state, writer)

	// ---- case 9: "reasoning-delta" (15 chars) ----
	case eventReasoningDelta:
		// Only write if reasoning has started
		// Decompiled: *(char *)(param_1 + 0x18) != '\0'
		delta, ok := getStringField(data, keyDelta)
		if !ok || delta == "" {
			return nil
		}
		if state.isReasoningStarted {
			return writer.WriteThinkingDelta(delta)
		}

	// ---- case 9: "reasoning-start" (15 chars) ----
	case eventReasoningStart:
		// Only start if reasoning hasn't started yet
		// Decompiled: *(char *)(param_1 + 0x18) == '\0'
		if !state.isReasoningStarted {
			state.StartReasoning()
			// WriteBlockStart(8, 0, "thinking", 0)
			return writer.WriteBlockStart(8, 0, "thinking", 0)
		}

	// ---- case 10: "tool-input-delta" (16 chars) ----
	case eventToolInputDelta:
		// Append delta to pending tool input
		// Decompiled: mapaccess1_faststr(5, ..., "delta")
		delta, ok := getStringField(data, keyDelta)
		if !ok || delta == "" {
			return nil
		}
		state.AppendToolInput(delta)
		// Write delta if there's an active tool call
		// Decompiled: *(long *)(param_1 + 0x60) != 0
		if state.pendingToolInput != "" {
			return writer.WriteToolInputDelta()
		}

	// ---- case 10: "tool-input-start" (16 chars) ----
	case eventToolInputStart:
		return handleToolInputStart(state, writer, data, toolMapper, clientTools)
	}

	return nil
}

// ============================================================================
// Event sub-handlers
// ============================================================================

// handleFinishEvent handles the "finish" event type.
// Extracts usage data (input_tokens, output_tokens, cache_read_input_tokens)
// and sets the finish reason.
//
// Decompiled flow:
//  1. mapaccess1_faststr(0xc) for "stop_reason" → get stop reason string
//  2. mapaccess1_faststr(5) for "usage" → get usage map
//  3. From usage: mapaccess1_faststr(0xb) for "input_tokens" → float64
//  4. From usage: mapaccess1_faststr(0xc) for "output_tokens" → float64
//  5. From usage: mapaccess1_faststr(0x11) for "cache_read_input_tokens" → float64
//  6. SetInputTokens, SetOutputTokens, SetCacheReadInputTokens
//  7. Check stop_reason: "tool-calls" (10 bytes) → SetFinishReason("tool_use")
//                        "stop" (4 bytes) → SetFinishReason("end_turn")
func handleFinishEvent(state *StreamState, writer *SSEWriter, data map[string]interface{}) error {
	// Extract stop_reason
	// Decompiled: mapaccess1_faststr(0xc, ..., "stop_reason")
	stopReason, _ := getStringField(data, keyStopReason)

	// Extract usage map
	// Decompiled: mapaccess1_faststr(5, ..., "usage")
	if usageRaw, ok := data[keyUsage]; ok {
		if usage, ok := usageRaw.(map[string]interface{}); ok {
			// Extract token counts (stored as float64 in JSON)
			// Decompiled: type check against &DAT_0194e5e0 (float64 type)
			if v, ok := usage[keyInputTokens].(float64); ok {
				state.SetInputTokens(int64(v))
			}
			if v, ok := usage[keyOutputTokens].(float64); ok {
				state.SetOutputTokens(int64(v))
			}
			if v, ok := usage[keyCacheReadInputTokens].(float64); ok {
				state.SetCacheReadInputTokens(int64(v))
			}
		}
	}

	// Set finish reason based on stop_reason
	// Decompiled: "tool-calls" (10 bytes, 0x6c61632d6c6f6f74 + 0x736c) → "tool_use"
	//             "stop" (4 bytes, 0x706f7473) → "end_turn"
	switch stopReason {
	case finishToolCalls:
		state.SetFinishReason("tool_use")
	case finishStop:
		state.SetFinishReason("end_turn")
	}

	return nil
}

// handleToolInputEnd handles the "tool-input-end" event.
// Ends the current tool call, optionally unmarshals accumulated input JSON,
// and writes the final tool input delta + content_block_stop event.
//
// Decompiled flow:
//  1. EndToolCall() → get tool call state (local_50)
//  2. If local_50 == 0, return 0
//  3. If *(long *)(local_50 + 0x28) != 0 (has input):
//     a. runtime_newobject() → allocate map
//     b. runtime_stringtoslicebyte() → convert input string to bytes
//     c. encoding_json_Unmarshal() → parse JSON
//     d. If success: UpdatePendingToolInput(*local_10)
//  4. If *(char *)(local_50 + 0x38) == '\0' (no hasInput flag) AND has input:
//     a. WriteToolInputDelta()
//  5. Build content_block_stop event with index
//  6. writeEvent("content_block_stop", event)
func handleToolInputEnd(state *StreamState, writer *SSEWriter) error {
	// Step 1: End tool call
	tc := state.EndToolCall()
	if tc == nil {
		return nil
	}

	// Step 2: If tool call has accumulated input, unmarshal it
	// Decompiled: *(long *)(local_50 + 0x28) != 0
	if tc.InputLength > 0 || tc.Input != "" {
		var parsed interface{}
		if err := json.Unmarshal([]byte(tc.Input), &parsed); err == nil {
			state.UpdatePendingToolInput(parsed)
		}
	}

	// Step 3: Write remaining tool input delta if needed
	// Decompiled: *(char *)(local_50 + 0x38) == '\0' && *(long *)(local_50 + 0x28) != 0
	if !tc.HasInput && tc.Input != "" {
		if err := writer.WriteToolInputDelta(); err != nil {
			return err
		}
	}

	// Step 4: Build and write content_block_stop event
	// Decompiled: runtime_makemap_small() → mapassign_faststr(4) for "type" → "content_block_stop"
	//             mapassign_faststr(5) for "index" → runtime_convT64(local_98)
	// local_98 = *(undefined8 *)(local_50 + 0x30) — the tool name/index
	event := map[string]interface{}{
		keyType:  "content_block_stop",
		"index": writer.state.blockCount - 1,
	}
	return writer.writeEvent("content_block_stop", event)
}

// handleToolInputStart handles the "tool-input-start" event.
// Starts a new tool_use content block with the tool's ID and name.
//
// Decompiled flow:
//  1. mapaccess1_faststr(2) for "id" → get tool ID
//  2. mapaccess1_faststr(8) for "tool_name" → get tool name
//  3. If no ID: generate UUID via github.com/google/uuid.NewRandom()
//     - encodeHex() → slicebytetostring() → concatstring2("toolu_", uuid[:12])
//     - Result format: "toolu_" + first 12 hex chars of UUID
//  4. If tool name exists and clientTools provided:
//     - MapToolNameToClient(toolName, clientTools, toolMapper)
//  5. StartToolUseBlock(toolID, mappedName)
func handleToolInputStart(
	state *StreamState,
	writer *SSEWriter,
	data map[string]interface{},
	toolMapper *ToolMapper,
	clientTools []map[string]interface{},
) error {
	// Extract tool ID
	// Decompiled: mapaccess1_faststr(2, ..., "id")
	toolID, _ := getStringField(data, keyID)

	// Extract tool name
	// Decompiled: mapaccess1_faststr(8, ..., "tool_name")
	toolName, _ := getStringField(data, keyToolName)

	// If no tool ID, generate one
	// Decompiled: if local_a0 == (undefined *)0x0 → uuid.NewRandom()
	// Format: "toolu_" + first 12 hex chars of UUID
	// Decompiled: runtime_concatstring2(auVar12._0_8_, 0xc, auVar12._8_8_, 6)
	// 6 = len("toolu_"), 0xc = 12 hex chars
	if toolID == "" {
		newUUID, err := uuid.NewRandom()
		if err == nil {
			// "toolu_" prefix + first 12 chars of hex-encoded UUID
			// Decompiled: &DAT_01c3bccf = "toolu_" (6 bytes)
			hexStr := newUUID.String()
			// Remove dashes and take first 12 chars
			hexStr = strings.ReplaceAll(hexStr, "-", "")
			if len(hexStr) > 12 {
				hexStr = hexStr[:12]
			}
			toolID = "toolu_" + hexStr
		}
	}

	// Map tool name to client name if tools are provided
	// Decompiled: if param_5 != 0 → MapToolNameToClient(0)
	mappedName := toolName
	if len(clientTools) > 0 && toolName != "" {
		mappedName = MapToolNameToClient(toolName, clientTools, toolMapper)
	}

	// Start the tool use block
	// Decompiled: SSEWriter_StartToolUseBlock(puVar11, lVar6, lVar8, lVar5, lVar8)
	if err := writer.StartToolUseBlock(toolID, mappedName); err != nil {
		return err
	}

	// Initialize new tool call state
	state.currentToolCall = &ToolCallState{
		ToolUseID: toolID,
		ToolName:  mappedName,
	}

	return nil
}

// strings import is used by handleToolInputStart for UUID formatting
var _ = strings.ReplaceAll
