package cursor

import (
	"encoding/json"
	"fmt"
	"math/rand"
	"net/http"
	"net/textproto"
	"strings"
	"time"

	"github.com/google/uuid"

	"kiro2api/internal/logic/cursor/currpc"
	"kiro2api/internal/model"
)

// ============================================================================
// Request Building — buildCursorRequest
// ============================================================================

// buildCursorRequest converts an OpenAI-format chat completion request into
// a Cursor Connect-RPC protobuf request.
// Symbol: kiro2api/internal/logic/cursor.(*sCursor).buildCursorRequest (9088B @ 0x17f7de0)
//
// This is the largest function in the cursor package. From the decompiled code:
//
// Flow:
//  1. Allocate a bool flag (mallocgc, 2 bytes) — line 67-69: *puVar7 = 1
//  2. Extract system prompt via extractSystemPrompt — line 72
//  3. Iterate over messages array (puVar21 = messages ptr, lVar26 = len) — line 80
//  4. For each message:
//     a. Parse message content via parseMessageContent — line 568
//     b. Check role == "user" (0x72657375) — line 579
//        - If user role and first message (lVar12==0) and has system prompt:
//          prepend system prompt content to user message
//        - Append "\n\n" separator (0x0a0a) between parts
//     c. Append text content to byte buffer (runtime_growslice + runtime_memmove)
//     d. If message has thinking content (offset 0x148):
//        - Wrap in <thinking>...</thinking> tags
//        - Hex: 0x6e696b6e6968743c = "<thinkin", 0x3e67 = "g>"
//        - Hex: 0x696b6e6968742f3c = "</thinki", 0x3e676e69 = "ing>"
//     e. Process tool_calls (offset 0x140, 0x138) — inner loop at line 754
//        - For each tool call: format as "%s: %s" (name: arguments)
//        - Append 0x18 bytes (24 chars) per formatted tool call
//        - If tool call has arguments (offset 0x1e0), marshal to JSON
//        - Append "\n" + JSON string
//     f. Process tool_results (offset 0x128, 0x120) — inner loop at line 904
//        - For each tool result: format as "%s: %s" (id: content)
//        - Append 0x22 bytes (34 chars) per formatted result
//        - If has content (offset 0x148), append "\n" + content
//  5. Convert accumulated byte buffer to string — line 1041-1044
//  6. Generate UUID for conversation ID — line 1046
//  7. Create CursorRequest protobuf message — line 1050
//     - Set content field (offset 0x10) = accumulated text length or 1
//     - Set content data (offset 0x08) = text bytes or empty marker
//  8. Check role for special handling:
//     - "user" (0x72657375) with first message: create UserMessage with system prompt
//       - Set message type (offset 0x18) = 2 for user
//       - Create inner message with UUID and content
//     - "assistant" (0x6e61747369737361 + 't'): set type = 2
//       - Create assistant response message with tool use info
//       - Append to both messages slice and conversation parts slice
//     - Default: set type = 1 (user message)
//  9. Build final CursorMessage with role type and content reference
// 10. Append to messages slice (runtime_growslice with &DAT_01b241a0)
// 11. Append to conversation parts slice (runtime_growslice with &DAT_01c05960)
// 12. Return the constructed protobuf request
func (s *sCursor) buildCursorRequest(
	account *model.CursorAccount,
	requestBody []byte,
) (*currpc.StreamUnifiedChatRequestWithTools, error) {

	// Parse the OpenAI-format request
	var openAIReq struct {
		Model       string          `json:"model"`
		Messages    []OpenAIMessage `json:"messages"`
		Stream      bool            `json:"stream"`
		Temperature *float64        `json:"temperature,omitempty"`
		MaxTokens   *int            `json:"max_tokens,omitempty"`
	}
	if err := json.Unmarshal(requestBody, &openAIReq); err != nil {
		return nil, fmt.Errorf("failed to parse request body: %w", err)
	}

	// Map the model name to Cursor's internal identifier
	cursorModel := mapCursorModel(openAIReq.Model)

	// Extract system prompt from messages
	systemPrompt := extractSystemPrompt(openAIReq.Messages)

	// Extract working directory and workspace path from system prompt
	workingDir := extractWorkingDirFromSystemPrompt(systemPrompt)
	workspacePath := extractWorkspacePath(systemPrompt)

	// Build the conversation content by iterating messages
	// This corresponds to the main loop in the decompiled code (line 80-1330)
	var contentBuf []byte
	var messages []*currpc.CursorMessage
	var conversationParts []*currpc.ConversationPart
	isFirstUserMessage := true

	for _, msg := range openAIReq.Messages {
		if msg.Role == roleSystem {
			// System messages are handled separately via extractSystemPrompt
			continue
		}

		role, text := parseMessageContent(&msg)

		// Build content buffer for this message
		var msgContent []byte

		// For the first user message, prepend system prompt if available
		// Decompiled: role == "user" (0x72657375) && lVar12 == 0 && systemPrompt != ""
		if role == roleUser && isFirstUserMessage && systemPrompt != "" {
			msgContent = append(msgContent, []byte(systemPrompt)...)
			if len(text) > 0 {
				msgContent = append(msgContent, '\n', '\n')
			}
			isFirstUserMessage = false
		}

		// Append the message text content
		if len(text) > 0 {
			msgContent = append(msgContent, []byte(text)...)
		}

		// Handle thinking content — wrap in <thinking>...</thinking> tags
		// Decompiled: offset 0x148 check, hex constants for tags
		if msg.Role == roleAssistant {
			// Check for thinking content in the message
			thinkingContent := extractThinkingContent(&msg)
			if thinkingContent != "" {
				if len(msgContent) > 0 {
					msgContent = append(msgContent, '\n', '\n')
				}
				msgContent = append(msgContent, []byte(thinkingOpenTag)...)
				msgContent = append(msgContent, []byte(thinkingContent)...)
				msgContent = append(msgContent, []byte(thinkingCloseTag)...)
			}
		}

		// Handle tool_calls — format as "name: arguments"
		// Decompiled: inner loop at line 754, fmt_Sprintf with "%s: %s"
		for _, tc := range msg.ToolCalls {
			if len(contentBuf) > 0 || len(msgContent) > 0 {
				msgContent = append(msgContent, '\n', '\n')
			}
			formatted := fmt.Sprintf("%s: %s", tc.Function.Name, tc.Function.Arguments)
			msgContent = append(msgContent, []byte(formatted)...)

			// If tool call has structured arguments, also marshal as JSON
			if tc.Function.Arguments != "" {
				var args interface{}
				if json.Unmarshal([]byte(tc.Function.Arguments), &args) == nil {
					jsonBytes, err := json.Marshal(args)
					if err == nil {
						msgContent = append(msgContent, '\n')
						msgContent = append(msgContent, jsonBytes...)
					}
				}
			}
		}

		// Handle tool results — format as "id: content"
		// Decompiled: inner loop at line 904, fmt_Sprintf with "%s: %s"
		if msg.Role == roleTool && msg.ToolCallID != "" {
			toolContent := extractToolResultContent(&msg)
			if len(msgContent) > 0 {
				msgContent = append(msgContent, '\n', '\n')
			}
			formatted := fmt.Sprintf("%s: %s", msg.ToolCallID, toolContent)
			msgContent = append(msgContent, []byte(formatted)...)

			if toolContent != "" {
				msgContent = append(msgContent, '\n')
				msgContent = append(msgContent, []byte(toolContent)...)
			}
		}

		// Separator between messages
		if len(contentBuf) > 0 && len(msgContent) > 0 {
			contentBuf = append(contentBuf, '\n', '\n')
		}
		contentBuf = append(contentBuf, msgContent...)

		// Generate UUID for this message
		// Decompiled: github_com_google_uuid_NewString() at line 1046
		msgID := uuid.NewString()

		// Create the CursorMessage based on role
		// Decompiled: role type assignment at offset 0x18
		cursorMsg := &currpc.CursorMessage{
			Content:   string(msgContent),
			MessageID: msgID,
		}

		switch role {
		case roleUser:
			cursorMsg.Role = currpc.RoleUser // type = 1
			if isFirstUserMessage {
				isFirstUserMessage = false
			}
		case roleAssistant:
			// Decompiled: "assistant" check (0x6e61747369737361 + 't'), type = 2
			cursorMsg.Role = currpc.RoleAssistant

			// For assistant messages with tool calls, create additional tool use entries
			if len(msg.ToolCalls) > 0 {
				toolUseMsg := &currpc.CursorMessage{
					MessageID: uuid.NewString(),
					Content:   "",
					Role:      currpc.RoleAssistant,
				}

				// Create tool use part with function info
				// Decompiled: offset 0x370 = tool use reference
				toolUsePart := &currpc.ConversationPart{
					MessageID: toolUseMsg.MessageID,
					Role:      currpc.RoleAssistant,
					// Tool info at offset 0x08 = "tool", 0x10 = 4
					// Tool name at offset 0x18 = "assistant", 0x20 = 9
					ToolInfo: &currpc.ToolInfo{
						Type: "tool",
						Name: "assistant",
					},
				}

				messages = append(messages, toolUseMsg)
				conversationParts = append(conversationParts, toolUsePart)
			}
		case roleTool:
			cursorMsg.Role = currpc.RoleTool
		default:
			cursorMsg.Role = currpc.RoleUser
		}

		messages = append(messages, cursorMsg)

		// Build conversation part
		// Decompiled: runtime_growslice with &DAT_01b241a0 (messages) and &DAT_01c05960 (parts)
		part := &currpc.ConversationPart{
			MessageID: cursorMsg.MessageID,
			Role:      cursorMsg.Role,
		}
		conversationParts = append(conversationParts, part)
	}

	// Build the final protobuf request
	req := &currpc.StreamUnifiedChatRequestWithTools{
		ModelName:         cursorModel,
		ConversationID:    uuid.NewString(),
		Messages:          messages,
		ConversationParts: conversationParts,
		SystemPrompt:      systemPrompt,
		WorkingDirectory:  workingDir,
		WorkspacePath:     workspacePath,
	}

	// Set optional parameters
	if openAIReq.Temperature != nil {
		req.Temperature = *openAIReq.Temperature
	}
	if openAIReq.MaxTokens != nil {
		req.MaxTokens = int32(*openAIReq.MaxTokens)
	}

	return req, nil
}

// extractThinkingContent extracts thinking/reasoning content from an assistant message.
// Used internally by buildCursorRequest to detect and wrap thinking blocks.
func extractThinkingContent(msg *OpenAIMessage) string {
	if msg == nil || msg.Content == nil {
		return ""
	}

	switch content := msg.Content.(type) {
	case []interface{}:
		for _, item := range content {
			if m, ok := item.(map[string]interface{}); ok {
				if t, ok := m["type"].(string); ok && t == "thinking" {
					if txt, ok := m["thinking"].(string); ok {
						return txt
					}
				}
			}
		}
	}
	return ""
}

// ============================================================================
// Connect Request Building — newConnectRequest
// ============================================================================

// newConnectRequest creates an HTTP request configured for the Cursor Connect-RPC
// protocol with all required headers for authentication and anti-detection.
// Symbol: kiro2api/internal/logic/cursor.(*sCursor).newConnectRequest (4736B @ 0x17fa160)
//
// From the decompiled code (line 1397-1981):
//
// Flow:
//  1. Create new http.Request object — line 1495: runtime_newobject()
//  2. Set the account reference — line 1500: *puStack_b8 = account
//  3. Initialize headers map — line 1502: runtime_makemap_small()
//  4. Set "Authorization" header — line 1513-1533:
//     - Format: fmt.Sprintf("%s", token) with convTstring
//     - Key length 0xd = 13 = "Authorization"
//     - CanonicalMIMEHeaderKey("authorization")
//  5. Set "User-Agent" header — line 1546-1563:
//     - Key length 0x17 = 23 (but canonical form)
//     - Value: "2.1.7" (version string from binary)
//  6. Generate request ID — line 1576-1577:
//     - uuid.NewString() with "-" replaced by "" (strings.Replace)
//  7. Generate timestamp seed — line 1579-1584:
//     - time.Now() converted to Unix nanoseconds
//     - Used to seed math/rand for random string generation
//  8. Generate random 16-char string — line 1619-1978:
//     - Character set: a-z (0x61-0x7a) + 1-9,0 (0x31-0x39,0x30) = 36 chars
//     - Hex pairs in uStack_1e8..uStack_160 decode to: 'a','b','c',...'z','1','2',...'9','0'
//     - Loop 16 times (0xf < lVar5), pick random index from 36 chars
//     - Concatenate: requestID + "-" + randomStr + "-" + randomStr
//  9. Set "X-Request-Id" header — line 1624-1650:
//     - Key: "x-request-id" (length 0xb = 11... canonical form)
//     - Value: concatenated ID string
// 10. Set "X-Cursor-Client-Key" header — line 1662-1688:
//     - Key length 0xc = 12
//     - Value from account offset 0x68/0x70 (ClientKey)
// 11. Set "Content-Type" header — line 1700-1717:
//     - Key length 0x11 = 17
//     - Value: "application/proto" (length 0xd = 13) from &DAT_01c49caa
// 12. Set "X-Ghost-Mode" header — line 1730-1760:
//     - uuid.NewString() formatted
//     - Key length 0xf = 15
// 13. Set "X-Cursor-Timezone" header — line 1773-1798:
//     - uuid.NewString() for value
//     - Key length 0x17 = 23
// 14. Set "X-Cursor-Checksum" header — line 1813-1841:
//     - Calls GetChecksum(account offset 0xa0, account, headers, account offset 0x98)
//     - Key length 0x11 = 17
//     - Value from account offset 0x90/0x98 (checksum data)
// 15. Set "Connect-Protocol-Version" header — line 1853-1870:
//     - Value: "proto" (length 5) from &DAT_01c3a54e
//     - Key length 0xc = 12
// 16. Set "Connect-Accept-Encoding" header — line 1882-1899:
//     - Value: "proto" (length 5)
//     - Key length 0x1a = 26
// 17. Set "X-Cursor-Client-Version" header — line 1911-1937:
//     - Value from account offset 0xa8/0xb0 (ClientVersion)
//     - Key length 0xc = 12
// 18. Set custom header (param_5/param_6) — line 1949-1969:
//     - Additional header passed as function parameters
//     - Key length 0xc = 12
// 19. Return the constructed request — line 1970
func (s *sCursor) newConnectRequest(
	account *model.CursorAccount,
	path string,
	body []byte,
	extraHeaderKey string,
	extraHeaderValue string,
) (*http.Request, error) {

	// Build the full URL
	baseURL := getCursorProxyURL(account)
	if baseURL == "" {
		baseURL = cursorAPIBase
	}
	fullURL := baseURL + path

	// Create the HTTP request
	req, err := http.NewRequest("POST", fullURL, nil)
	if err != nil {
		return nil, fmt.Errorf("failed to create request: %w", err)
	}

	// Initialize headers
	headers := make(http.Header)

	// 1. Authorization header (key length 0xd = 13)
	// Decompiled: fmt_Sprintf with convTstring, CanonicalMIMEHeaderKey
	token := account.AccessToken
	headers.Set(textproto.CanonicalMIMEHeaderKey("authorization"),
		fmt.Sprintf("Bearer %s", token))

	// 2. User-Agent header (key length 0x17)
	// Decompiled: value "2.1.7" from binary string pool
	headers.Set(textproto.CanonicalMIMEHeaderKey("user-agent"), cursorUserAgent)

	// 3. Generate request ID
	// Decompiled: uuid.NewString() + strings.Replace("-", "", -1)
	requestID := strings.Replace(uuid.NewString(), "-", "", -1)

	// 4. Generate timestamp-seeded random string (16 chars)
	// Decompiled: character set a-z,1-9,0 (36 chars), loop 16 times
	now := time.Now()
	seed := now.UnixNano()
	rng := rand.New(rand.NewSource(seed))

	charset := []rune{
		'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j',
		'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't',
		'u', 'v', 'w', 'x', 'y', 'z',
		'1', '2', '3', '4', '5', '6', '7', '8', '9', '0',
	}

	randomStr := make([]rune, 16)
	for i := 0; i < 16; i++ {
		randomStr[i] = charset[rng.Intn(len(charset))]
	}

	// 5. X-Request-Id header
	// Decompiled: concatstring5 with requestID + "-" + randomStr + "-" + randomStr
	xRequestID := fmt.Sprintf("%s-%s-%s", requestID, string(randomStr[:8]), string(randomStr[8:]))
	headers.Set(textproto.CanonicalMIMEHeaderKey("x-request-id"), xRequestID)

	// 6. X-Cursor-Client-Key header (key length 0xc)
	// Decompiled: value from account offset 0x68/0x70
	if account.ClientKey != "" {
		headers.Set(textproto.CanonicalMIMEHeaderKey("x-cursor-client-key"), account.ClientKey)
	}

	// 7. Content-Type header (key length 0x11)
	// Decompiled: value "application/proto" (0xd = 13 chars) from &DAT_01c49caa
	headers.Set(textproto.CanonicalMIMEHeaderKey("content-type"), connectProtoContentType)

	// 8. X-Ghost-Mode header
	// Decompiled: uuid.NewString() formatted, key length 0xf
	ghostID := uuid.NewString()
	headers.Set(textproto.CanonicalMIMEHeaderKey("x-ghost-mode"),
		fmt.Sprintf("%s", ghostID))

	// 9. X-Cursor-Timezone header
	// Decompiled: uuid.NewString(), key length 0x17
	timezoneID := uuid.NewString()
	headers.Set(textproto.CanonicalMIMEHeaderKey("x-cursor-timezone"), timezoneID)

	// 10. X-Cursor-Checksum header (key length 0x11)
	// Decompiled: calls GetChecksum with account fields
	checksum := GetChecksum(account.ChecksumSeed, account, headers, account.MachineID)
	headers.Set(textproto.CanonicalMIMEHeaderKey("x-cursor-checksum"), checksum)

	// 11. Connect-Protocol-Version header (key length 0xc)
	// Decompiled: value "proto" (length 5)
	headers.Set(textproto.CanonicalMIMEHeaderKey("connect-protocol-version"), "proto")

	// 12. Connect-Accept-Encoding header (key length 0x1a)
	// Decompiled: value "proto" (length 5)
	headers.Set(textproto.CanonicalMIMEHeaderKey("connect-accept-encoding"), "proto")

	// 13. X-Cursor-Client-Version header (key length 0xc)
	// Decompiled: value from account offset 0xa8/0xb0
	clientVersion := account.ClientVersion
	if clientVersion == "" {
		clientVersion = cursorClientVersion
	}
	headers.Set(textproto.CanonicalMIMEHeaderKey("x-cursor-client-version"), clientVersion)

	// 14. Extra header from parameters
	// Decompiled: param_5/param_6 passed through
	if extraHeaderKey != "" && extraHeaderValue != "" {
		headers.Set(textproto.CanonicalMIMEHeaderKey(extraHeaderKey), extraHeaderValue)
	}

	req.Header = headers
	return req, nil
}
