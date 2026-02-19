package cursor

import (
	"sync"

	"kiro2api/internal/dao"
)

// sCursor is the singleton service for Cursor channel logic.
// Recovered from symbol: kiro2api/internal/logic/cursor.(*sCursor)
type sCursor struct{}

var (
	instance *sCursor
	once     sync.Once
)

// New creates the singleton sCursor service instance.
// Symbol: kiro2api/internal/logic/cursor.New (160B @ 0x17f6020)
func New() *sCursor {
	once.Do(func() {
		instance = &sCursor{}
	})
	return instance
}

// init is the package-level initialization function.
// Symbol: kiro2api/internal/logic/cursor.init (96B @ 0x17f5a80)
// Symbol: kiro2api/internal/logic/cursor.init.0 (96B @ 0x17f60c0)
func init() {
	dao.RegisterMigration(dao.MigrateCursorCredentials)
}

// ============================================================================
// Constants extracted from binary strings
// ============================================================================

const (
	// Cursor API base URL
	cursorAPIBase = "https://api2.cursor.sh"

	// Connect-RPC service path for streaming chat
	// From binary: "/aiserver.v1.AiService/StreamChat"
	streamChatPath = "/aiserver.v1.AiService/StreamChat"

	// Connect protocol content type
	// From binary: "application/connect+proto"
	connectProtoContentType = "application/connect+proto"

	// Cursor client version header value
	// From binary: "0.48.7" (version may vary)
	cursorClientVersion = "0.48.7"

	// User agent for Cursor requests
	cursorUserAgent = "connect-es/1.6.1"

	// Ghost text path
	// From binary: "/aiserver.v1.AiService/StreamGhostText"
	ghostTextPath = "/aiserver.v1.AiService/StreamGhostText"

	// Thinking tag markers extracted from hex constants in buildCursorRequest
	// 0x6e696b6e6968743c = "<thinkin" (little-endian)
	// 0x3e67             = "g>"
	thinkingOpenTag = "<thinking>"
	// 0x696b6e6968742f3c = "</thinki" (little-endian)
	// 0x3e676e69         = "ing>"
	thinkingCloseTag = "</thinking>"

	// Role constants from binary string comparisons
	// 0x72657375 = "user" (little-endian int32)
	roleUser = "user"
	// 0x6e61747369737361 + 't' = "assistant"
	roleAssistant = "assistant"
	// "system"
	roleSystem = "system"
	// "tool"
	roleTool = "tool"
)
