package kiro

// request.go — buildKiroRequest: the core request builder for the Kiro channel.
//
// Symbol: kiro2api/internal/logic/kiro.buildKiroRequest (24160B @ 0x17a4e20)
//
// This is the largest function in the kiro channel (24KB of machine code, 3255 lines
// of decompiled C pseudocode). It transforms an OpenAI-compatible chat completion
// request into the AWS Q Developer API format.
//
// High-level flow (from decompiled analysis):
//
//   Phase 1 — Extract model (lines 317-324):
//     model = request["model"] || request["default_model"]
//
//   Phase 2 — Extract system message (lines 325-332):
//     if request has system_message field → getContentText(system_message)
//
//   Phase 3 — Message loop (lines 340-488):
//     For each message in request.messages:
//       - "system" (0x74737973 + 0x6d65): concatenate to systemMessage via concatstring2
//       - "tool" (0x6c6f6f74): build tool result map {type, tool_use_id, content}
//       - "user"/"assistant": process content blocks (text, thinking, tool_use)
//         For assistant messages with content array:
//           - "text" (0x74786574): accumulate text bytes
//           - "thinking" (0x676e696b6e696874): accumulate thinking bytes
//           - "tool_use" (0x6573755f6c6f6f74): extract id, name, input
//
//   Phase 4 — Thinking prefix (lines 489-498):
//     generateThinkingPrefix() → if system has no thinking prefix, prepend it
//
//   Phase 5 — System message truncation:
//     if DAT_02e5d6d9 (truncation flag) && len(systemMessage) > 8000 → truncate
//
//   Phase 6 — Build parent message (lines 2925-2960):
//     parentMessage = {
//       role: "MANUAL" (8 bytes, DAT_01c3ffa7) or 22-byte string if tools present
//       model: model name
//       type: "streaming" (9 bytes, DAT_01c41eb5)
//       headers: makemap_small()
//     }
//
//   Phase 7 — Process tools (lines 2961-3119):
//     Deduplicate tools by name, build tool definitions array
//     Add "customizations" key to headers map if tools present
//
//   Phase 8 — Message limit (lines 3152-3165):
//     if DAT_02e5d6d9 && len(messages) > 100 → trim to last 100
//     Remove empty trailing messages
//
//   Phase 9 — Final assembly (lines 3219-3254):
//     conversationId = uuid.NewString()
//     result = {model: "MANUAL", conversationId, parentMessage, messages, context}

import (
	"strings"

	"github.com/google/uuid"
	"github.com/gogf/gf/v2/frame/gins"
)

// ============================================================================
// Configuration flag
// ============================================================================

// truncationEnabled controls whether system message truncation and message
// limiting are active. Corresponds to DAT_02e5d6d9 in the decompiled binary.
// In production this is typically true.
var truncationEnabled = true

// ============================================================================
// buildKiroRequest
// ============================================================================

// buildKiroRequest transforms an OpenAI-compatible request into the AWS Q Developer
// API request format.
//
// Symbol: kiro2api/internal/logic/kiro.buildKiroRequest (24160B @ 0x17a4e20)
//
// Parameters (from decompiled stack layout):
//   lStack0000000000000010 = request data (OpenAI format map)
//   lStack0000000000000018 = account/context data
//
// The request data contains:
//   offset 0x10: messages slice ptr
//   offset 0x18: messages slice len
//   offset 0x40: system message flag (non-zero if present)
//   offset 0x48: system message content ptr
//   offset 0x50: tools slice ptr (pauStack_ac8)
//   offset 0x58: tools slice len (pauStack_ac0)
//   offset 0x98: context ptr
//   offset 0xa0: context len
//
// Returns a *KiroRequest ready to be serialized and sent.
func (s *sKiro) buildKiroRequest(
	requestData map[string]interface{},
	accountData map[string]interface{},
) *KiroRequest {
	logger := gins.Log()

	// ========================================================================
	// Phase 1: Extract model name
	// Decompiled lines 317-324:
	//   puVar11 = runtime_mapaccess1_faststr()  → model
	//   if lStack_9c8 == 0 → fallback to second mapaccess
	// ========================================================================
	model := ""
	if m, ok := requestData["model"].(string); ok && m != "" {
		model = m
	}
	if model == "" {
		if m, ok := requestData["default_model"].(string); ok && m != "" {
			model = m
		}
	}

	// ========================================================================
	// Phase 2: Extract initial system message
	// Decompiled lines 325-332:
	//   if *(lStack0000000000000010 + 0x40) == 0 → systemMessage = ""
	//   else → systemMessage = getContentText(*(lStack0000000000000010 + 0x48))
	// ========================================================================
	systemMessage := ""
	if sysMsg, ok := requestData["system_message"]; ok && sysMsg != nil {
		systemMessage = getContentText(sysMsg)
	}

	// ========================================================================
	// Phase 3: Message processing loop
	// Decompiled lines 340-488:
	//   Iterates through messages array (0x30 bytes per message struct)
	//   Each message has: role(0x00), role_len(0x08), content_type(0x10),
	//                     content_data(0x18), extra1(0x20), extra2(0x28)
	// ========================================================================
	// Support both []interface{} and []map[string]interface{} — Go type assertions
	// require exact type match, so we must handle both forms.
	var messages []interface{}
	if m, ok := requestData["messages"].([]interface{}); ok {
		messages = m
	} else if m2, ok := requestData["messages"].([]map[string]interface{}); ok {
		messages = make([]interface{}, len(m2))
		for i, v := range m2 {
			messages[i] = v
		}
	}

	var kiroMessages []KiroMessage
	var toolResults []KiroMessage // tool role messages get special handling
	var hasTools bool              // tracks if any tool_use content was seen

	for _, msg := range messages {
		msgMap, ok := msg.(map[string]interface{})
		if !ok {
			continue
		}

		role, _ := msgMap["role"].(string)
		content := msgMap["content"]

		switch role {
		case "system":
			// ============================================================
			// System message handling (lines 353-374)
			// Decompiled: role == "system" (0x74737973 + 0x6d65, 6 bytes)
			//   text = getContentText(content)
			//   if systemMessage != "" → systemMessage = systemMessage + "\n" + text
			//   else → systemMessage = text
			// ============================================================
			text := getContentText(content)
			if systemMessage != "" {
				systemMessage = systemMessage + "\n" + text
			} else {
				systemMessage = text
			}

		case "tool":
			// ============================================================
			// Tool result handling (lines 376-451)
			// Decompiled: role == "tool" (0x6c6f6f74, 4 bytes)
			//   1. makemap_small() → create result map
			//   2. mapassign_faststr(4, "type") → PTR_DAT_01f3a180 (tool result type)
			//   3. convTstring() → mapassign_faststr(0xb, "tool_use_id") → from content
			//   4. mapassign_faststr(7, "content") → content text
			//   5. Wrap in slice, set content type to slice (DAT_0192e960)
			//   6. Set role to "tool" (DAT_01c3978a, 4 bytes)
			// ============================================================
			toolUseID, _ := msgMap["tool_call_id"].(string)
			if toolUseID == "" {
				toolUseID, _ = msgMap["tool_use_id"].(string)
			}
			contentText := getContentText(content)

			toolResultMap := map[string]interface{}{
				"type":        "tool_result",
				"tool_use_id": toolUseID,
				"content":     contentText,
			}

			kiroMessages = append(kiroMessages, KiroMessage{
				Role:    "tool",
				Content: []interface{}{toolResultMap},
			})

		default:
			// ============================================================
			// User/Assistant message handling (lines 452-488 for simple,
			// lines 800-2886 for content array processing)
			//
			// Simple case (lines 452-484):
			//   Append message directly with role and content
			//
			// Content array case (assistant with structured content):
			//   Iterate content blocks, check type:
			//     "text" (0x74786574) → accumulate text bytes
			//     "thinking" (0x676e696b6e696874) → accumulate thinking bytes
			//     "tool_use" (0x6573755f6c6f6f74) → extract id, name, input
			// ============================================================
			kiroMsg := s.processMessage(role, content, &hasTools)
			kiroMessages = append(kiroMessages, kiroMsg)
		}
	}

	// Append any tool results after regular messages
	kiroMessages = append(kiroMessages, toolResults...)

	// ========================================================================
	// Phase 4: Thinking prefix
	// Decompiled lines 489-498:
	//   thinkingPrefix = generateThinkingPrefix(messages, model, modelLen)
	//   if systemMessage != "" && thinkingPrefix != "" && !hasThinkingPrefix(systemMessage):
	//     systemMessage = thinkingPrefix + "\n" + systemMessage
	// ========================================================================
	thinkingPfx := generateThinkingPrefix(model, len(model))
	if thinkingPfx != "" && systemMessage != "" && !hasThinkingPrefix(systemMessage) {
		systemMessage = thinkingPfx + "\n" + systemMessage
	}

	// ========================================================================
	// Phase 5: System message truncation
	// Decompiled: if DAT_02e5d6d9 != 0 && len(systemMessage) > 8000 → truncate
	// ========================================================================
	if truncationEnabled && len(systemMessage) > maxSystemMessageLen {
		logger.Warningf(nil, "[Kiro] System message truncated from %d to %d chars",
			len(systemMessage), maxSystemMessageLen)
		systemMessage = systemMessage[:maxSystemMessageLen]
	}

	// ========================================================================
	// Phase 6: Build parent message
	// Decompiled lines 2925-2960:
	//   if pauStack_920 == 0:
	//     if pauStack_940 == 0 → role = "MANUAL" (8 bytes, DAT_01c3ffa7)
	//     else → role = 22-byte string (DAT_01c5a6df) — "MANUAL_WITH_TOOL_CALLS"
	//   parentMessage = newobject()
	//   parentMessage[0] = role
	//   parentMessage[5] = model ptr (uStack_648)
	//   parentMessage[6] = model len (lStack_9c8)
	//   parentMessage[7] = "streaming" (DAT_01c41eb5)
	//   parentMessage[8] = 9 (len of "streaming")
	//   if systemMessage != "" → parentMessage[2] = systemMessage
	// ========================================================================
	parentRole := defaultModel // "MANUAL"
	if hasTools {
		parentRole = "MANUAL_WITH_TOOL_CALLS"
	}

	parentMessage := &KiroParentMessage{
		Role:    parentRole,
		Model:   model,
		Type:    "streaming",
		Headers: make(map[string]interface{}),
	}

	if systemMessage != "" {
		parentMessage.SystemMessage = systemMessage
	}

	// ========================================================================
	// Phase 7: Process tools
	// Decompiled lines 2961-3119:
	//   If last message has tools (content blocks with tool_use):
	//     1. Iterate tool_use blocks, build dedup map
	//     2. Iterate request tools (pauStack_5d0/pauStack_940), filter by dedup
	//     3. Build tool definitions (0x38 bytes each): name, description, input_schema
	//     4. Iterate remaining dedup map entries, add placeholder tools
	//     5. If tools exist → mapassign_faststr(0xb, "customizations") = tools slice
	//   If pauStack_ac8 (request-level tools) exist:
	//     mapassign_faststr(5, "tools") = tools slice
	// ========================================================================
	var toolDefs []KiroToolDef
	if tools, ok := requestData["tools"].([]interface{}); ok {
		toolDefs = s.processTools(tools)
	}

	// Add tools to parent message headers if present
	if len(toolDefs) > 0 {
		parentMessage.Headers["customizations"] = toolDefs
	}

	// ========================================================================
	// Phase 8: Message limit enforcement
	// Decompiled lines 3152-3165:
	//   if DAT_02e5d6d9 != 0 && len(messages) > 100:
	//     trim messages to last 100
	//     skip leading empty messages
	// ========================================================================
	if truncationEnabled && len(kiroMessages) > maxMessagesLimit {
		logger.Warningf(nil, "[Kiro] Messages truncated from %d to %d",
			len(kiroMessages), maxMessagesLimit)
		// Keep the last maxMessagesLimit messages
		startIdx := len(kiroMessages) - maxMessagesLimit
		kiroMessages = kiroMessages[startIdx:]

		// Skip leading empty messages (decompiled: check *(long *)(*pauStack_5f0 + 8) != 0)
		for len(kiroMessages) > 0 {
			if getContentText(kiroMessages[0].Content) != "" {
				break
			}
			kiroMessages = kiroMessages[1:]
		}
	}

	// Remove trailing empty assistant messages
	// Decompiled lines 3166-3217: check last message, remove empty headers map
	for len(kiroMessages) > 0 {
		last := kiroMessages[len(kiroMessages)-1]
		if last.Role == "" && getContentText(last.Content) == "" {
			kiroMessages = kiroMessages[:len(kiroMessages)-1]
		} else {
			break
		}
	}

	// ========================================================================
	// Phase 9: Final assembly
	// Decompiled lines 3219-3254:
	//   conversationId = uuid.NewString()
	//   result = newobject()
	//   result[0x20] = "MANUAL" (6 bytes) — model field
	//   result[0x28] = 6
	//   result[0x30] = conversationId
	//   result[0x38] = conversationId len
	//   result[0x40] = parentMessage
	//   result[0x48] = messages ptr
	//   result[0x50] = messages len
	//   result[0x58] = messages cap
	//   if account[0xa0] != 0 → result[0x60] = context ptr, result[0x68] = context len
	// ========================================================================
	conversationID := uuid.NewString()

	// Use the extracted model for the top-level request (not hardcoded defaultModel).
	// defaultModel ("MANUAL") is only the fallback when no model is specified.
	requestModel := model
	if requestModel == "" {
		requestModel = defaultModel
	}

	request := &KiroRequest{
		Model:          requestModel,
		ConversationID: conversationID,
		ParentMessage:  parentMessage,
		Messages:       kiroMessages,
	}

	// Add context from account data if present
	if ctx, ok := accountData["context"]; ok && ctx != nil {
		request.Context = ctx
	}

	// Add tools at request level if present
	if len(toolDefs) > 0 {
		request.Tools = toolDefs
	}

	return request
}

// ============================================================================
// processMessage
// ============================================================================

// processMessage processes a single user or assistant message, handling both
// simple string content and structured content arrays.
//
// From decompiled:
//   - Simple content (DAT_0194e220 type): pass through as string
//   - Array content (DAT_0192e960 type): iterate blocks, process by type
//     - "text": accumulate into text buffer (pauStack_710/720/730 byte slices)
//     - "thinking": accumulate into thinking buffer (pauStack_790/798/7a0)
//     - "tool_use": extract id/name/input, build tool use block
func (s *sKiro) processMessage(role string, content interface{}, hasTools *bool) KiroMessage {
	if content == nil {
		return KiroMessage{Role: role, Content: ""}
	}

	// Simple string content
	if text, ok := content.(string); ok {
		return KiroMessage{Role: role, Content: text}
	}

	// Array content — process each block
	blocks, ok := content.([]interface{})
	if !ok {
		return KiroMessage{Role: role, Content: getContentText(content)}
	}

	var resultBlocks []interface{}
	var textBuf strings.Builder
	var thinkingBuf strings.Builder

	for _, block := range blocks {
		blockMap, ok := block.(map[string]interface{})
		if !ok {
			continue
		}

		blockType, _ := blockMap["type"].(string)

		switch blockType {
		case "text":
			// ============================================================
			// Text block (0x74786574)
			// Decompiled lines 1049-1093, 2688-2732:
			//   mapaccess1_faststr("text") → get text value
			//   Accumulate into byte slice (pauStack_710/720/730)
			//   Uses runtime_growslice + runtime_memmove for append
			// ============================================================
			if text, ok := blockMap["text"].(string); ok {
				textBuf.WriteString(text)
			}

		case "thinking":
			// ============================================================
			// Thinking block (0x676e696b6e696874)
			// Decompiled lines 1097-1099, 2736-2820:
			//   mapaccess1_faststr("thinking") → get thinking text
			//   If type is "thinking" and has "text" subfield:
			//     Accumulate into thinking byte slice (pauStack_790/798/7a0)
			//   Else: check for "text" key as fallback
			// ============================================================
			if text, ok := blockMap["thinking"].(string); ok {
				thinkingBuf.WriteString(text)
			} else if text, ok := blockMap["text"].(string); ok {
				thinkingBuf.WriteString(text)
			}

		case "tool_use":
			// ============================================================
			// Tool use block (0x6573755f6c6f6f74)
			// Decompiled lines 2825-2883:
			//   mapaccess1_faststr("id", 2) → tool use ID
			//   mapaccess1_faststr("name", 4) → tool name
			//   mapaccess1_faststr("input", 5) → tool input
			//   Build tool use struct, append to messages
			// ============================================================
			*hasTools = true
			toolUseBlock := map[string]interface{}{
				"type":  "tool_use",
				"id":    blockMap["id"],
				"name":  blockMap["name"],
				"input": blockMap["input"],
			}
			resultBlocks = append(resultBlocks, toolUseBlock)

		default:
			// Pass through unknown block types
			resultBlocks = append(resultBlocks, blockMap)
		}
	}

	// Build final content
	// If we have text accumulated, add it as a text block
	if textBuf.Len() > 0 {
		textBlock := map[string]interface{}{
			"type": "text",
			"text": textBuf.String(),
		}
		// Prepend text block before tool_use blocks
		resultBlocks = append([]interface{}{textBlock}, resultBlocks...)
	}

	// If we have thinking accumulated, add it as a thinking block
	if thinkingBuf.Len() > 0 {
		thinkingBlock := map[string]interface{}{
			"type":     "thinking",
			"thinking": thinkingBuf.String(),
		}
		// Prepend thinking block before everything
		resultBlocks = append([]interface{}{thinkingBlock}, resultBlocks...)
	}

	// If only simple text, return as string
	if len(resultBlocks) == 0 && textBuf.Len() == 0 && thinkingBuf.Len() == 0 {
		return KiroMessage{Role: role, Content: ""}
	}
	if len(resultBlocks) == 1 {
		if tb, ok := resultBlocks[0].(map[string]interface{}); ok {
			if tb["type"] == "text" {
				return KiroMessage{Role: role, Content: tb["text"]}
			}
		}
	}

	return KiroMessage{Role: role, Content: resultBlocks}
}

// ============================================================================
// processTools
// ============================================================================

// processTools processes the tools array from the OpenAI request format
// into KiroToolDef format, with deduplication.
//
// From decompiled lines 2961-3119:
//   1. Build dedup map from tool_use blocks in last assistant message
//   2. Iterate request tools (0x38 bytes each):
//      - Extract name (offset 0x00), description (offset 0x10), input_schema (offset 0x20)
//      - Check dedup map: if tool name already seen in tool_use, skip
//      - Otherwise add to tool definitions
//   3. For remaining entries in dedup map (tool_use IDs not matched):
//      - Create placeholder tool with name from dedup map
//      - Description: "custom_tool_definition" (25 bytes, DAT_01c5fbc8)
//      - Input: "content" (7 bytes, DAT_01c3dd13)
func (s *sKiro) processTools(tools []interface{}) []KiroToolDef {
	seen := make(map[string]bool)
	var toolDefs []KiroToolDef

	for _, tool := range tools {
		toolMap, ok := tool.(map[string]interface{})
		if !ok {
			continue
		}

		// OpenAI format: tool has "function" wrapper
		funcMap, _ := toolMap["function"].(map[string]interface{})
		if funcMap == nil {
			funcMap = toolMap // Direct format
		}

		name, _ := funcMap["name"].(string)
		if name == "" {
			continue
		}

		// Dedup check
		if seen[name] {
			continue
		}
		seen[name] = true

		description, _ := funcMap["description"].(string)
		inputSchema := funcMap["parameters"]
		if inputSchema == nil {
			inputSchema = funcMap["input_schema"]
		}

		toolDef := KiroToolDef{
			ToolSpecification: &ToolSpecification{
				Name:        name,
				Description: description,
			},
		}
		if inputSchema != nil {
			toolDef.ToolSpecification.InputSchema = &ToolInputSchema{
				JSON: inputSchema,
			}
		}

		toolDefs = append(toolDefs, toolDef)
	}

	return toolDefs
}

// ============================================================================
// buildGenerateAssistantRequest
// ============================================================================

// buildGenerateAssistantRequest transforms an OpenAI-compatible request into the
// AWS Q Developer generateAssistantResponse format.
//
// The real Kiro API expects:
//   POST /generateAssistantResponse
//   {
//     "conversationState": {
//       "chatTriggerType": "MANUAL",
//       "conversationId": "<uuid>",
//       "currentMessage": {
//         "userInputMessage": { "content": "...", "modelId": "...", "origin": "IDE" }
//       },
//       "history": [ { "userInputMessage": {...} }, { "assistantResponseMessage": {...} }, ... ]
//     },
//     "profileArn": ""
//   }
func (s *sKiro) buildGenerateAssistantRequest(
	requestData map[string]interface{},
	accountData map[string]interface{},
) *GenerateAssistantRequest {
	logger := gins.Log()

	// Extract model and map to AWS Q model ID
	model := ""
	if m, ok := requestData["model"].(string); ok && m != "" {
		model = m
	}
	if model == "" {
		if m, ok := requestData["default_model"].(string); ok && m != "" {
			model = m
		}
	}
	// Map OpenAI model name to AWS Q model ID
	qModelID := mapModelID(model)
	logger.Infof(nil, "[Kiro] Model mapping: %q -> %q", model, qModelID)

	// Extract system message(s) — collect from requestData and from messages
	systemMessage := ""
	if sysMsg, ok := requestData["system_message"]; ok && sysMsg != nil {
		systemMessage = getContentText(sysMsg)
	}

	// Parse messages
	var messages []interface{}
	if m, ok := requestData["messages"].([]interface{}); ok {
		messages = m
	} else if m2, ok := requestData["messages"].([]map[string]interface{}); ok {
		messages = make([]interface{}, len(m2))
		for i, v := range m2 {
			messages[i] = v
		}
	}

	// Collect system messages from the messages array
	for _, msg := range messages {
		msgMap, ok := msg.(map[string]interface{})
		if !ok {
			continue
		}
		role, _ := msgMap["role"].(string)
		if role == "system" {
			text := getContentText(msgMap["content"])
			if systemMessage != "" {
				systemMessage = systemMessage + "\n" + text
			} else {
				systemMessage = text
			}
		}
	}

	// Build history — real Kiro puts system prompt as history[0] userInputMessage
	// followed by assistant reply "I will follow these instructions."
	var history []HistoryMessage

	if systemMessage != "" {
		history = append(history, HistoryMessage{
			UserInputMessage: &UserInputMessage{
				Content: systemMessage,
				ModelID: qModelID,
				Origin:  "AI_EDITOR",
			},
		})
		history = append(history, HistoryMessage{
			AssistantResponseMessage: &AssistantResponseMessage{
				Content: "I will follow these instructions.\n\nUnderstood.",
			},
		})
	}

	// Find the last user message index (skip system messages)
	lastUserIdx := -1
	for i := len(messages) - 1; i >= 0; i-- {
		msgMap, ok := messages[i].(map[string]interface{})
		if !ok {
			continue
		}
		role, _ := msgMap["role"].(string)
		if role == "user" {
			lastUserIdx = i
			break
		}
	}

	// Build history from non-system messages; last user message becomes currentMessage
	var lastUserContent string
	for i, msg := range messages {
		msgMap, ok := msg.(map[string]interface{})
		if !ok {
			continue
		}

		role, _ := msgMap["role"].(string)
		content := msgMap["content"]

		switch role {
		case "system":
			// Already handled above as history[0]+[1]
		case "user":
			text := getContentText(content)
			if i == lastUserIdx {
				lastUserContent = text
			} else {
				history = append(history, HistoryMessage{
					UserInputMessage: &UserInputMessage{
						Content: text,
						ModelID: qModelID,
						Origin:  "AI_EDITOR",
					},
				})
			}
		case "assistant":
			text := getContentText(content)
			history = append(history, HistoryMessage{
				AssistantResponseMessage: &AssistantResponseMessage{
					Content: text,
				},
			})
		case "tool":
			// Tool results — skip for now
		}
	}

	// Fallback: if no user message found, use a placeholder
	if lastUserContent == "" {
		lastUserContent = "Hello"
	}

	// Process tools
	var toolDefs []KiroToolDef
	if tools, ok := requestData["tools"].([]interface{}); ok {
		toolDefs = s.processTools(tools)
	}

	// Build userInputMessageContext — editorState is always required (even as empty {})
	msgContext := &UserInputMessageContext{
		EditorState: &EditorState{},
	}
	if len(toolDefs) > 0 {
		msgContext.Tools = toolDefs
	}

	// Truncate history if needed
	if truncationEnabled && len(history) > maxMessagesLimit {
		logger.Warningf(nil, "[Kiro] History truncated from %d to %d",
			len(history), maxMessagesLimit)
		startIdx := len(history) - maxMessagesLimit
		history = history[startIdx:]
	}

	conversationID := uuid.NewString()
	agentContinuationID := uuid.NewString()

	// profileArn: present for IDC/Pro users, absent for Builder ID users.
	// AWS SDK's take() skips undefined values, so omitempty handles this correctly.
	profileArn, _ := accountData["profile_arn"].(string)

	return &GenerateAssistantRequest{
		ConversationState: &ConversationState{
			ChatTriggerType:     "MANUAL",
			ConversationID:      conversationID,
			AgentContinuationID: agentContinuationID,
			AgentTaskType:       "vibe",
			CurrentMessage: &CurrentMessage{
				UserInputMessage: &UserInputMessage{
					Content:                 lastUserContent,
					ModelID:                 qModelID,
					Origin:                  "AI_EDITOR",
					UserInputMessageContext: msgContext,
				},
			},
			History: history,
		},
		ProfileArn: profileArn,
	}
}
