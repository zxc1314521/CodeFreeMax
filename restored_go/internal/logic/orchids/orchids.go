package orchids

// orchids.go — Package initialization and core types for the Orchids channel.
//
// Orchids is a Claude-compatible AI service that uses Clerk for authentication
// and supports both WebSocket and SSE streaming protocols.
//
// Key characteristics discovered from decompilation:
//   - Uses Clerk session tokens for authentication
//   - Dual transport: WebSocket (primary) and SSE (fallback)
//   - Connection pooling via ConnectionPoolManager
//   - Tool use support with custom tool name mapping (Orchids ↔ Anthropic)
//   - Streaming via SSEWriter with block-based event protocol
//   - Thinking/reasoning mode support
//
// Decompiled functions (7 total, 2,907 lines):
//   - executeWebSocketRequest  (0x175bf20) — WebSocket streaming
//   - executeSSERequest        (0x1760cc0) — SSE/HTTP streaming
//   - TransformToolInput       (0x1768d40) — Tool input transformation
//   - MapToolNameToClient      (0x1767bc0) — Tool name mapping
//   - extractMessageContent    (0x1754f40) — Content extraction from messages
//   - extractUserMessage       (0x1753420) — Last user message extraction
//   - handleModelEvent         (0x175d4a0) — SSE event handler/dispatcher

import (
	"sync"
)

// ============================================================================
// Constants
// ============================================================================

const (
	// Channel name identifier
	channelName = "orchids"

	// WebSocket read timeout (90 seconds = 90000000000 nanoseconds)
	// From decompiled: DAT_02e34d10 == 90000000000
	wsReadTimeout = 90_000_000_000

	// SSE client timeout (5 minutes = 300000000000 nanoseconds)
	// From decompiled: *(*(lStack_d8 + 200) + 0x28) = 300000000000
	sseClientTimeout = 300_000_000_000

	// Stream state sentinel values
	// From decompiled: *(lStack_138 + 0x20) = 0xffffffffffffffff
	sentinelUnset int64 = -1

	// Default block count for SSEWriter
	// From decompiled: *(lStack_138 + 0xb0) = 8
	defaultBlockCount = 8
)

// ============================================================================
// String constants from binary (hex-decoded)
// ============================================================================

// Content type identifiers (from mapaccess1_faststr key lengths)
const (
	// "type" — 4 bytes, 0x74797065 → used in mapaccess1_faststr(4, ...)
	keyType = "type"

	// "text" — 4 bytes, 0x74786574
	typeText = "text"

	// "image" — 5 bytes, 0x67616d69 + 'e'
	typeImage = "image"

	// "document" — 8 bytes, 0x746e656d75636f64
	typeDocument = "document"

	// "thinking" — 8 bytes, 0x676e696b6e696874
	typeThinking = "thinking"

	// "reasoning" — 9 bytes, 0x6e696e6f73616572 + 'g'
	typeReasoning = "reasoning"

	// "input_text" — 10 bytes, 0x65745f7475706e69 + 0x7478
	typeInputText = "input_text"

	// "tool_use" — 8 bytes, 0x6573755f6c6f6f74
	typeToolUse = "tool_use"

	// "tool_result" — 11 bytes, 0x7365725f6c6f6f74 + 0x6c75 + 't'
	typeToolResult = "tool_result"

	// "enabled" — 7 bytes, 0x62616e65 + 0x656c + 'd'
	valueEnabled = "enabled"
)

// Event type strings from handleModelEvent switch
const (
	// "finish" — 6 bytes, 0x696e6966 + 0x6873
	eventFinish = "finish"

	// "text-delta" — 10 bytes, 0x6c65642d74786574 + 0x6174
	eventTextDelta = "text-delta"

	// "text-start" — 10 bytes, 0x6174732d74786574 + 0x7472
	eventTextStart = "text-start"

	// "reasoning-end" — 13 bytes, 0x6e696e6f73616572 + 0x6e652d67 + 'd'
	eventReasoningEnd = "reasoning-end"

	// "tool-input-end" — 14 bytes, 0x706e692d6c6f6f74 + 0x652d7475 + 0x646e
	eventToolInputEnd = "tool-input-end"

	// "reasoning-delta" — 15 bytes, 0x6e696e6f73616572 + 0x65642d67 + 0x746c + 'a'
	eventReasoningDelta = "reasoning-delta"

	// "reasoning-start" — 15 bytes, 0x6e696e6f73616572 + 0x74732d67 + 0x7261 + 't'
	eventReasoningStart = "reasoning-start"

	// "tool-input-delta" — 16 bytes, 0x706e692d6c6f6f74 + 0x61746c65642d7475
	eventToolInputDelta = "tool-input-delta"

	// "tool-input-start" — 16 bytes, 0x706e692d6c6f6f74 + 0x74726174732d7475
	eventToolInputStart = "tool-input-start"
)

// Finish reason strings
const (
	// "tool-calls" — 10 bytes, 0x6c61632d6c6f6f74 + 0x736c
	finishToolCalls = "tool-calls"

	// "stop" — 4 bytes, 0x706f7473
	finishStop = "stop"
)

// Map access key strings
const (
	// "delta" — 5 bytes, used in mapaccess1_faststr(5, ..., "delta")
	keyDelta = "delta"

	// "data" — 4 bytes
	keyData = "data"

	// "usage" — 5 bytes
	keyUsage = "usage"

	// "stop_reason" — 12 bytes (0xc), 0x6e6f736165725f706f7473
	keyStopReason = "stop_reason"

	// "input_tokens" — 11 bytes (0xb)
	keyInputTokens = "input_tokens"

	// "output_tokens" — 12 bytes (0xc)
	keyOutputTokens = "output_tokens"

	// "cache_read_input_tokens" — 17 bytes (0x11)
	keyCacheReadInputTokens = "cache_read_input_tokens"

	// "id" — 2 bytes
	keyID = "id"

	// "name" — 4 bytes
	keyName = "name"

	// "tool_name" — 8 bytes (0x3ffe7 → "tool_name")
	keyToolName = "tool_name"

	// "content" — 7 bytes
	keyContent = "content"

	// "input" — 5 bytes
	keyInput = "input"

	// "source" — 6 bytes
	keySource = "source"

	// "media_type" — 10 bytes
	keyMediaType = "media_type"

	// "file_path" — 9 bytes, 0x7461705f656c6966 + 'h'
	keyFilePath = "file_path"

	// "path" — 4 bytes, 0x68746170
	keyPath = "path"
)

// ============================================================================
// Singleton
// ============================================================================

var (
	instance *sOrchids
	once     sync.Once
)

// sOrchids is the singleton service for the Orchids channel.
type sOrchids struct {
	// proxyURL is the configured proxy URL for outbound requests
	proxyURL string
}

// New returns the singleton sOrchids instance.
func New() *sOrchids {
	once.Do(func() {
		instance = &sOrchids{}
	})
	return instance
}

// ============================================================================
// Connection Pool Manager
// ============================================================================

// ConnectionPoolManager manages WebSocket connection pools for Orchids.
// From decompiled: kiro2api_internal_logic_orchids_GetConnectionPoolManager()
type ConnectionPoolManager struct {
	// pools maps account identifiers to their WebSocket connection pools
	pools sync.Map
}

var (
	poolManager     *ConnectionPoolManager
	poolManagerOnce sync.Once
)

// GetConnectionPoolManager returns the singleton ConnectionPoolManager.
func GetConnectionPoolManager() *ConnectionPoolManager {
	poolManagerOnce.Do(func() {
		poolManager = &ConnectionPoolManager{}
	})
	return poolManager
}

// GetConnection retrieves or creates a WebSocket connection from the pool.
// From decompiled: ConnectionPoolManager_GetConnection(param1, param2, ..., proxyURL)
// Returns the connection and an error.
func (m *ConnectionPoolManager) GetConnection(
	accountID string,
	sessionToken string,
	proxyURL string,
) (*OrchidsWebSocket, error) {
	// Look up existing connection in pool
	if conn, ok := m.pools.Load(accountID); ok {
		return conn.(*OrchidsWebSocket), nil
	}

	// Create new connection
	ws, err := newOrchidsWebSocket(accountID, sessionToken, proxyURL)
	if err != nil {
		return nil, err
	}

	// Store in pool (race-safe: if another goroutine stored first, use theirs)
	actual, loaded := m.pools.LoadOrStore(accountID, ws)
	if loaded {
		// Another goroutine created the connection first, close ours
		ws.Close()
		return actual.(*OrchidsWebSocket), nil
	}

	return ws, nil
}

// ============================================================================
// OrchidsWebSocket
// ============================================================================

// OrchidsWebSocket wraps a WebSocket connection to the Orchids service.
type OrchidsWebSocket struct {
	accountID    string
	sessionToken string
	proxyURL     string
	// conn holds the underlying WebSocket connection
	conn interface{}
	mu   sync.Mutex
}

// newOrchidsWebSocket creates a new WebSocket connection to Orchids.
func newOrchidsWebSocket(accountID, sessionToken, proxyURL string) (*OrchidsWebSocket, error) {
	ws := &OrchidsWebSocket{
		accountID:    accountID,
		sessionToken: sessionToken,
		proxyURL:     proxyURL,
	}
	return ws, nil
}

// Close closes the WebSocket connection.
func (ws *OrchidsWebSocket) Close() error {
	ws.mu.Lock()
	defer ws.mu.Unlock()
	// Close underlying connection
	return nil
}

// SendRequest sends a request over the WebSocket connection.
// From decompiled: OrchidsWebSocket_SendRequest()
func (ws *OrchidsWebSocket) SendRequest(request *OrchidsRequest) error {
	ws.mu.Lock()
	defer ws.mu.Unlock()
	// Marshal and send request
	return nil
}

// ReadMessageWithTimeout reads a message with the configured timeout.
// From decompiled: OrchidsWebSocket_ReadMessageWithTimeout()
// Timeout is 90 seconds (wsReadTimeout).
func (ws *OrchidsWebSocket) ReadMessageWithTimeout() (map[string]interface{}, error) {
	// Read with 90s timeout
	return nil, nil
}

// ============================================================================
// OrchidsRequest
// ============================================================================

// OrchidsRequest represents a request to the Orchids API.
// Built by ConvertToOrchidsRequest from OpenAI-format chat request.
type OrchidsRequest struct {
	// Messages in Orchids format
	// Offset 0x80-0x90: messages slice (ptr, len, cap)
	Messages []OrchidsMessage

	// Model identifier
	// Offset 0x10: model type pointer
	Model interface{}

	// Model name string
	// Offset 0x18: model name
	ModelName string

	// System prompt
	// Offset 0xa8-0xb0: system (ptr, len)
	System string

	// Max tokens
	// Offset 0xc0-0xc8: max_tokens and related config
	MaxTokens int
	Config    map[string]interface{}
}

// OrchidsMessage represents a single message in Orchids format.
type OrchidsMessage struct {
	Role    string
	Content interface{} // string or []map[string]interface{}
	// Tool-related fields
	ToolResults []ToolResult
}

// ============================================================================
// ToolResult
// ============================================================================

// ToolResult represents a parsed tool result from the message content.
// Size: 0x38 bytes (56 bytes = 7 fields)
// From decompiled: parseToolResult returns a struct with fields at offsets:
//   0x00: Name (string ptr)
//   0x08: Name length
//   0x10: ToolUseID (string ptr)
//   0x18: ToolUseID length
//   0x20: Content
//   0x28: IsError (bool at +0x28)
//   0x2c: flags
//   0x30: additional flags
//   0x34: additional flags
type ToolResult struct {
	Name      string
	ToolUseID string
	Content   interface{}
	IsError   bool
	HasInput  bool
	// Additional flags from the 0x38-byte struct
	Flag1 bool
	Flag2 bool
}

// ============================================================================
// Proxy URL
// ============================================================================

// getOrchidsProxyURL returns the configured proxy URL for the Orchids channel.
// From decompiled: kiro2api_internal_logic_orchids_getOrchidsProxyURL()
func getOrchidsProxyURL() string {
	if instance != nil {
		return instance.proxyURL
	}
	return ""
}
