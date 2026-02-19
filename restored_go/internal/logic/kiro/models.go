package kiro

// models.go — Data structures for the Kiro channel (AWS Q Developer API).
//
// Structures derived from buildKiroRequest (24160B @ 0x17a4e20) analysis:
//   - KiroRequest: the final request sent to AWS Q API
//   - KiroMessage: individual message in the conversation
//   - KiroContent: content block within a message (text, thinking, tool_use)
//   - KiroToolUse: tool use block structure
//   - KiroStreamEvent: streaming response event
//   - UsageLimits: usage tracking structure
//
// The request format follows the AWS Q Developer conversationMessage pattern:
// {
//   "conversationId": "uuid",
//   "parentMessageId": "uuid",
//   "message": {
//     "role": "user",
//     "content": "...",
//     "context": {...}
//   },
//   "systemMessage": "...",
//   "tools": [...],
//   "dynamicHeaders": {...}
// }

// ============================================================================
// Request Structures
// ============================================================================

// KiroRequest represents the complete request to the AWS Q Developer API.
// Built by buildKiroRequest (24160B @ 0x17a4e20).
//
// Field offsets from decompiled newobject at end of buildKiroRequest:
//   offset 0x00: role (ptr)          — "MANUAL" (6 bytes, DAT_01c41eb5 → 9 bytes)
//   offset 0x08: role len
//   offset 0x10: systemMessage (ptr)
//   offset 0x18: systemMessage len
//   offset 0x20: model (ptr)         — from uStack_648 / lStack_9c8
//   offset 0x28: model len           — 6 (for "MANUAL")
//   offset 0x30: conversationId      — from uuid.NewString()
//   offset 0x38: conversationId len
//   offset 0x40: parentMessage       — puStack_810 (the message object)
//   offset 0x48: messages slice ptr
//   offset 0x50: messages slice len
//   offset 0x58: messages slice cap
//   offset 0x60: context ptr         — from lStack0000000000000018 + 0x98
//   offset 0x68: context len
type KiroRequest struct {
	// Model is the model identifier (e.g. "MANUAL", or mapped model name)
	// From decompiled: puVar11[7] = &DAT_01c41eb5 ("streaming"), puVar11[8] = 9
	// Actually: role field at offset 0x20-0x28 stores model name
	Model    string `json:"model"`
	ModelLen int    `json:"-"`

	// SystemMessage is the concatenated system prompt
	// From decompiled: pauStack_6a0 accumulates system messages via concatstring2
	// Truncated to maxSystemMessageLen (8000) if DAT_02e5d6d9 != 0
	SystemMessage string `json:"systemMessage,omitempty"`

	// ConversationID is a UUID for the conversation
	// From decompiled: github_com_google_uuid_NewString() at line 3219
	ConversationID string `json:"conversationId"`

	// ParentMessage is the constructed parent message object
	// From decompiled: puStack_810 = runtime_newobject() at line 2939
	ParentMessage *KiroParentMessage `json:"parentMessage"`

	// Messages is the array of conversation messages
	// From decompiled: pauStack_978 (len), pauStack_970 (cap), pauStack_5f0 (ptr)
	Messages []KiroMessage `json:"messages"`

	// Context is optional additional context
	// From decompiled: lStack0000000000000018 + 0x98/0xa0
	Context interface{} `json:"context,omitempty"`

	// Tools is the list of available tools
	// From decompiled: pauStack_ac8 (tools slice)
	Tools []KiroToolDef `json:"tools,omitempty"`
}

// KiroParentMessage represents the parent message in the request.
// From decompiled: runtime_newobject() at line 2939, fields set at lines 2940-2960.
//
// Field offsets:
//   0x00: role ptr           — from pauStack_5c0
//   0x08: role len           — from pauStack_920
//   0x10: systemMessage ptr  — from pauStack_5c8 (if uStack_930 != 0)
//   0x18: systemMessage len
//   0x20: model ptr          — from uStack_648
//   0x28: model len          — from lStack_9c8
//   0x30: type ptr           — "streaming" (DAT_01c41eb5, 9 bytes)
//   0x38: type len           — 9
//   0x40: headers map        — plStack_818 (from runtime_makemap_small)
//   0x48: headers map ptr
type KiroParentMessage struct {
	// Role is the message role
	// From decompiled: pauStack_5c0 / pauStack_920
	// Default: "MANUAL" (8 bytes at DAT_01c3ffa7) if pauStack_920 == 0 && pauStack_940 == 0
	// Or: 22-byte string (DAT_01c5a6df) if pauStack_940 != 0
	Role string `json:"role"`

	// SystemMessage is the system prompt for this message
	SystemMessage string `json:"systemMessage,omitempty"`

	// Model is the model name
	Model    string `json:"model"`
	ModelLen int    `json:"-"`

	// Type is the request type, always "streaming"
	// From decompiled: puVar11[7] = &DAT_01c41eb5, puVar11[8] = 9
	Type string `json:"type"`

	// Headers is a map of dynamic headers
	// From decompiled: plStack_818 = runtime_makemap_small()
	Headers map[string]interface{} `json:"headers,omitempty"`
}

// KiroMessage represents a single message in the conversation.
// From decompiled: the message struct is 0x30 (48) bytes, iterated in buildKiroRequest.
//
// Struct layout (0x30 bytes per message):
//   0x00: role ptr
//   0x08: role len
//   0x10: content type ptr (interface type)
//   0x18: content data ptr (interface data)
//   0x20: extra field 1 (padding/flags)
//   0x28: extra field 2 (padding/flags)
type KiroMessage struct {
	// Role is the message role: "user", "assistant", "system", "tool"
	Role string `json:"role"`

	// Content can be a string or array of content blocks
	// From decompiled: content type checked against DAT_0192e960 (slice) and DAT_0194e220 (string)
	Content interface{} `json:"content"`
}

// KiroContentBlock represents a content block within a message.
// From decompiled: mapaccess1_faststr checks for "type", "text", "thinking", "tool_use"
//
// Content block types found in buildKiroRequest:
//   "text"     — 0x74786574 (4 bytes) at line 1049, 2688
//   "thinking" — 0x676e696b6e696874 (8 bytes) at line 1097, 2736
//   "tool_use" — 0x6573755f6c6f6f74 (8 bytes) at line 2825
type KiroContentBlock struct {
	Type  string      `json:"type"`
	Text  string      `json:"text,omitempty"`
	ID    string      `json:"id,omitempty"`
	Name  string      `json:"name,omitempty"`
	Input interface{} `json:"input,omitempty"`
}

// KiroToolDef represents a tool definition in the request.
// From decompiled: tool processing loop at lines 2962-3119
// Each tool is 0x38 (56) bytes in the slice.
//
// Tool struct layout (0x38 bytes):
//   0x00: name ptr
//   0x08: name len
//   0x10: description ptr
//   0x18: description len
//   0x20: input_schema ptr
//   0x28: input_schema len
//   0x30: extra fields
type KiroToolDef struct {
	Name        string      `json:"name"`
	Description string      `json:"description,omitempty"`
	InputSchema interface{} `json:"input_schema,omitempty"`
}

// ============================================================================
// Tool Result Structures
// ============================================================================

// KiroToolResult represents a tool result message.
// From decompiled: role == "tool" (0x6c6f6f74) branch at line 376
// Creates a map with:
//   "type" → PTR_DAT_01f3a180 (tool result type)
//   "tool_use_id" → from content (11 bytes key, mapassign_faststr(0xb))
//   "content" → from message content (7 bytes key, DAT_01c3dd44)
type KiroToolResult struct {
	Type      string `json:"type"`
	ToolUseID string `json:"tool_use_id"`
	Content   string `json:"content"`
}

// ============================================================================
// Response / Stream Structures
// ============================================================================

// KiroStreamEvent represents a streaming response event from AWS Q.
// From decompiled: ParseStreamResponse (224B @ 0x17aac80) and extractContent (736B @ 0x17aaf00)
type KiroStreamEvent struct {
	// Type is the event type
	Type string `json:"type,omitempty"`

	// Content is the text content delta
	Content string `json:"content,omitempty"`

	// StopReason indicates why generation stopped
	StopReason string `json:"stop_reason,omitempty"`

	// Usage contains token usage information
	Usage *KiroUsage `json:"usage,omitempty"`

	// ToolUse contains tool call information
	ToolUse *KiroToolUseEvent `json:"tool_use,omitempty"`
}

// KiroToolUseEvent represents a tool use event in the stream.
type KiroToolUseEvent struct {
	ID    string `json:"id"`
	Name  string `json:"name"`
	Input string `json:"input"`
}

// KiroUsage represents token usage information.
type KiroUsage struct {
	InputTokens  int `json:"input_tokens"`
	OutputTokens int `json:"output_tokens"`
}

// ============================================================================
// Usage Limits Structures
// ============================================================================

// UsageLimits represents the usage limits for a Kiro account.
// From decompiled: getUsageLimits (2176B @ 0x17a20e0) and GetUsageInfo (320B @ 0x17a2960)
type UsageLimits struct {
	// TierID is the account tier identifier
	// From decompiled: "tierId" key in response (6 bytes)
	TierID string `json:"tierId,omitempty"`

	// MonthlyUsage tracks per-month usage
	MonthlyUsage map[string]int64 `json:"monthlyUsage,omitempty"`

	// DailyUsage tracks per-day usage
	DailyUsage map[string]int64 `json:"dailyUsage,omitempty"`

	// Limits contains the configured limits
	Limits map[string]int64 `json:"limits,omitempty"`
}

// ============================================================================
// Auth Structures
// ============================================================================

// KiroTokenResponse represents the token refresh response.
// From decompiled: authRefresh (1280B @ 0x17a14a0) parses the response.
type KiroTokenResponse struct {
	AccessToken  string `json:"accessToken"`
	ExpiresIn    int64  `json:"expiresIn"`
	RefreshToken string `json:"refreshToken,omitempty"`
	TokenType    string `json:"tokenType,omitempty"`
	IDToken      string `json:"idToken,omitempty"`
}

// KiroAccount represents the account fields used by the kiro channel.
// Updated: Removed OIDC-specific fields (client_id, client_secret, start_url, idc_base_url),
// added Kiro auth service URL field.
type KiroAccount struct {
	ID           int64  `json:"id"`
	AccessToken  string `json:"access_token"`
	RefreshToken string `json:"refresh_token"`
	TokenExpiry  int64  `json:"token_expiry"`
	Region       string `json:"region"`
	Endpoint     string `json:"endpoint"`
	ProxyURL     string `json:"proxy_url"`
	AuthBaseURL  string `json:"auth_base_url"` // Kiro auth service URL override
}
