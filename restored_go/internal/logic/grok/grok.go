package grok

// grok.go — Package initialization and core types for the Grok channel.
//
// Grok is the codename for the xAI Grok backend channel.
// It uses cookie-based authentication with browser fingerprint spoofing,
// Cloudflare bypass mechanisms, and communicates with the Grok API
// for chat completions, image generation, and video generation.
//
// Symbol table summary (138 functions total, key subsystems):
//
// Core:
//   - New                          — Singleton constructor
//   - init                         — Package init
//   - ChatCompletions              — Main chat handler
//   - ImagineGenerations           — Image generation via WebSocket
//   - VideoGenerations             — Video generation (upload + post)
//
// Request Building:
//   - BuildChatPayload             (@ 0x1606520) — Build chat request payload
//   - BuildHeaders                 — Build HTTP headers with fingerprint
//   - buildVideoPayload            — Build video generation payload
//
// Message Processing:
//   - extractMessages              (@ 0x1603860) — Extract messages from response
//   - ProcessLine                  (@ 0x1612e80) — Line-by-line stream parsing
//   - CollectProcessorProcessWithUsage (@ 0x1616000) — Usage metrics collection
//
// Client/Network:
//   - GrokClient                   — HTTP client with cookie auth
//   - GrokClient.PostStream        — Streaming POST request
//   - GetCfClearance               — Cloudflare clearance cookie
//   - GetBrowserFingerprint        — Browser fingerprint generation
//   - clientForAccount             — Per-account client management
//
// Media:
//   - ImagineGenerations           (@ 0x160cd00) — Image generation handler
//   - VideoGenerations             (@ 0x161bc00) — Video generation handler
//   - classifyImage                — Image classification
//   - uploadImage                  — Image upload for video
//   - createMediaPost              — Create media post
//   - createImagePost              — Create image post
//
// Cache:
//   - CacheService                 — File caching with cleanup
//   - DownloadService              — File download and serving
//
// Helpers:
//   - isTimeoutError               — Timeout error detection
//   - generateFingerprint          — Browser fingerprint generation

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
	channelName = "grok"

	// Grok API base URL
	grokAPIBase = "https://grok.x.ai"

	// Grok API endpoints
	grokChatEndpoint  = "/api/rpc"
	grokImageEndpoint = "/api/rpc"
	grokVideoEndpoint = "/api/rpc"

	// WebSocket endpoint for image generation
	grokWSEndpoint = "wss://grok.x.ai/api/rpc"

	// Timeouts (nanoseconds)
	chatTimeoutNs     = 120_000_000_000 // 2 minutes (120s)
	imageTimeoutNs    = 120_000_000_000 // 2 minutes
	videoTimeoutNs    = 300_000_000_000 // 5 minutes
	wsReadTimeoutNs   = 5_000_000_000   // 5 seconds per WS read
	mediaStallTimeout = 15_000_000_000  // 15 seconds stall detection
	wsOverallTimeout  = 120_000_000_000 // 2 minutes overall WS timeout

	// Retry/timing
	timeoutRetryThreshold = 10_000_000_000 // 10 seconds for timeout retry

	// WebSocket close code
	wsCloseNormal = 1000
)

// ============================================================================
// Service Singleton
// ============================================================================

type sGrok struct {
	// browserFingerprint caches the generated browser fingerprint
	browserFingerprint string
	// cfClearance caches the Cloudflare clearance cookie
	cfClearance string
}

var (
	instance     *sGrok
	instanceOnce sync.Once

	// Concurrency manager for grok accounts
	grokConcurrencyMgr     *logic.AccountConcurrencyManager
	grokConcurrencyMgrOnce sync.Once
)

// New returns the singleton sGrok instance.
func New() *sGrok {
	instanceOnce.Do(func() {
		instance = &sGrok{}
	})
	return instance
}

// GetConcurrencyManager returns the global concurrency manager for Grok accounts.
func GetConcurrencyManager() *logic.AccountConcurrencyManager {
	grokConcurrencyMgrOnce.Do(func() {
		grokConcurrencyMgr = logic.NewAccountConcurrencyManager("grok")
	})
	return grokConcurrencyMgr
}

// init initializes the grok package.
func init() {
	logger := gins.Log()
	logger.Info(nil, "[Grok] Channel initialized (xAI Grok API)")
}
