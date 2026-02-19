package kiro

// kiro.go — Package initialization and core types for the Kiro channel.
//
// Kiro is the codename for the AWS Q Developer / Kiro IDE backend channel.
// It uses AWS-style authentication with SigV4-like signing, token refresh,
// and communicates with the AWS Q API for chat completions.
//
// Symbol table summary (37 functions total):
//
// Core:
//   - New                     (160B  @ 0x17a1060) — Singleton constructor
//   - init                    (224B  @ 0x17a0f80) — Package init
//   - init.0                  (96B   @ 0x17a1100) — Secondary init
//
// Authentication:
//   - RefreshToken            (320B  @ 0x17a1280) — Public refresh entry point
//   - RefreshToken.func1      (160B  @ 0x17a1400) — Closure for refresh
//   - RefreshToken.func2      (64B   @ 0x17a13c0) — Closure for refresh
//   - authRefresh             (1280B @ 0x17a14a0) — Core auth refresh logic
//   - refreshToken            (1760B @ 0x17a19a0) — Internal token refresh
//   - refreshToken.gowrap1    (96B   @ 0x17a2080) — Goroutine wrapper
//   - ValidateRefreshToken    (128B  @ 0x17a3080) — Token validation
//   - getKiroAuthBaseURL      (128B  @ 0x17a3100) — Kiro auth base URL
//   - newKiroAuthClient       (288B  @ 0x17a3320) — Auth HTTP client
//   - newKiroAuthClient.func1 (640B  @ 0x17ab1e0) — Auth client closure
//
// Request Building:
//   - buildKiroRequest        (24160B @ 0x17a4e20) — Main request builder (massive)
//   - buildDynamicHeaders     (896B  @ 0x17a3580) — Dynamic request headers
//   - buildUsageLimitsHeaders (800B  @ 0x17a3900) — Usage limits headers
//   - generateThinkingPrefix  (192B  @ 0x17a4ce0) — Thinking mode prefix
//   - hasThinkingPrefix       (128B  @ 0x17a4da0) — Check thinking prefix
//   - getContentText          (672B  @ 0x17a4a40) — Extract text from content
//
// Chat:
//   - ChatCompletions         (1728B @ 0x17a3c80) — Main chat handler
//   - CheckToken              (1024B @ 0x17a2aa0) — Token validity check
//   - GetUsageInfo            (320B  @ 0x17a2960) — Usage info retrieval
//   - getUsageLimits          (2176B @ 0x17a20e0) — Usage limits from API
//   - checkBannedResponse     (480B  @ 0x17a2ea0) — Check for banned responses
//
// Streaming:
//   - ParseStreamResponse         (224B @ 0x17aac80) — Stream response parser
//   - ParseStreamResponse.func1   (320B @ 0x17aad60) — Stream parser closure
//   - ParseStreamResponse.func1.deferwrap1 (96B @ 0x17aaea0) — Deferred cleanup
//   - extractContent              (736B @ 0x17aaf00) — Extract content from stream
//
// Client/Network:
//   - newKiroClient           (416B  @ 0x17a3180) — HTTP client constructor
//   - getProxyURL             (288B  @ 0x17a1160) — Proxy URL retrieval
//   - checkOutboundIP         (1248B @ 0x17a4560) — Outbound IP check
//   - checkOutboundIPOnce     (448B  @ 0x17a4340) — One-time IP check
//   - checkOutboundIPOnce.gowrap1 (96B @ 0x17a4500) — IP check goroutine
//   - contextCloser.Read      (160B  @ 0x17ab500) — Context-aware reader
//   - (*contextCloser).Close  (96B   @ 0x17a3c20) — Close context reader
//   - (*contextCloser).Read   (128B  @ 0x17ab5a0) — Read with context
//
// Helpers:
//   - generateMachineId       (320B  @ 0x17a3440) — Machine ID generation

import (
	"sync"

	"kiro2api/internal/logic"

	"github.com/gogf/gf/v2/frame/gins"
)

// ============================================================================
// Constants
// ============================================================================

const (
	// Channel name identifier
	channelName = "kiro"

	// AWS Q API base URL
	// Updated: Kiro uses the Q Developer endpoint, not the legacy codewhisperer endpoint
	awsQAPIBase = "https://q.us-east-1.amazonaws.com"

	// Kiro auth base URL
	// Updated: Kiro uses its own OAuth PKCE auth service, not AWS IDC OIDC
	kiroAuthBaseURL = "https://prod.us-east-1.auth.desktop.kiro.dev"

	// Default model name
	// From decompiled: "MANUAL" string at offset 0x17a4e20+3219 in the big string literal
	defaultModel = "MANUAL"

	// Thinking prefix marker
	// From decompiled: generateThinkingPrefix (192B @ 0x17a4ce0)
	// and hasThinkingPrefix (128B @ 0x17a4da0)
	thinkingPrefix = "<antThinking>"
	thinkingSuffix = "</antThinking>"

	// Max system message length (8000 chars)
	// From decompiled: if 8000 < lVar21 { runtime_concatstring2(&DAT_01c80308, 0x2b, lVar21, 8000) }
	maxSystemMessageLen = 8000

	// Max messages limit (100)
	// From decompiled: if 100 < (long)pauStack_978 { pauStack_978 = 0x64 }
	maxMessagesLimit = 100

	// Request timeout (5 minutes = 300000000000 ns)
	requestTimeoutNs = 300_000_000_000

	// Token refresh interval
	tokenRefreshBufferSec = 300 // 5 minutes before expiry
)

// ============================================================================
// Role Constants (from hex literals in decompiled code)
// ============================================================================

// Role string hex values found in buildKiroRequest:
//   0x74737973 + 0x6d65 = "system" (6 bytes) — line 353-354
//   0x6c6f6f74 = "tool" (4 bytes) — line 376
//   0x72657375 = "user" (4 bytes) — line 910
//   0x6e61747369737361 + 't' = "assistant" (9 bytes) — lines 801-803, 911-913

// Content type identifiers:
//   0x74786574 = "text" (4 bytes) — line 1049, 2688
//   0x676e696b6e696874 = "thinking" (8 bytes) — line 1097, 2736
//   0x6573755f6c6f6f74 = "tool_use" (8 bytes) — line 2825

// ============================================================================
// Service Singleton
// ============================================================================

type sKiro struct {
	// outboundIP caches the detected outbound IP address
	outboundIP string
	// machineID is a generated machine identifier for request headers
	machineID string
}

var (
	instance     *sKiro
	instanceOnce sync.Once

	// Concurrency manager for kiro accounts
	kiroConcurrencyMgr     *logic.AccountConcurrencyManager
	kiroConcurrencyMgrOnce sync.Once

	// One-time outbound IP check
	outboundIPOnce sync.Once
)

// New returns the singleton sKiro instance.
// Symbol: kiro2api/internal/logic/kiro.New (160B @ 0x17a1060)
func New() *sKiro {
	instanceOnce.Do(func() {
		instance = &sKiro{}
		instance.machineID = generateMachineId()
	})
	return instance
}

// GetConcurrencyManager returns the global concurrency manager for Kiro accounts.
func GetConcurrencyManager() *logic.AccountConcurrencyManager {
	kiroConcurrencyMgrOnce.Do(func() {
		kiroConcurrencyMgr = logic.NewAccountConcurrencyManager("kiro")
	})
	return kiroConcurrencyMgr
}

// init initializes the kiro package.
// Symbol: kiro2api/internal/logic/kiro.init (224B @ 0x17a0f80)
func init() {
	logger := gins.Log()
	logger.Info(nil, "[Kiro] Channel initialized (AWS Q Developer API)")
}
