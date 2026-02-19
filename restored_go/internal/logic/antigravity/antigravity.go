package antigravity

// antigravity is the codename for the Google Gemini API channel.
// It uses Google's Generative AI API (generativelanguage.googleapis.com)
// with OAuth2 PKCE authentication and streaming via SSE.
//
// Symbol table summary (5 functions):
//   - convertMessagesToContents     (5120B @ 0x17b0660): OpenAI messages → Gemini contents
//   - convertContentToPartsWithMapping (2816B @ 0x17b2580): content → parts with type mapping
//   - buildAntigravityRequest       (3584B @ 0x17af640): build Gemini generateContent request
//   - doStreamRequest               (4096B @ 0x17b4940): send streaming request via req/v3
//   - RefreshToken                  (3072B @ 0x17ab9a0): Google OAuth2 token refresh
//
// Additional helper functions referenced but not decompiled:
//   - mergeAdjacentRoles: merges consecutive same-role messages
//   - cleanThinkingFieldsRecursive: removes thinking fields when not supported
//   - getContentText: extracts text from content map
//   - getProxyURL: gets proxy URL for the account
//   - convertToolsToFunctionDeclarations: converts OpenAI tools to Gemini format
//   - IsTokenExpiringSoon: checks if OAuth token is near expiry

import (
	"sync"

	"kiro2api/internal/logic"

	"github.com/gogf/gf/v2/frame/gins"
)

// ============================================================================
// Constants
// ============================================================================

const (
	// Gemini API base URL
	geminiAPIBase = "https://generativelanguage.googleapis.com"

	// Gemini streaming endpoint pattern: /v1beta/models/{model}:streamGenerateContent
	streamGenerateContentPath = "/v1beta/models/%s:streamGenerateContent?alt=sse"

	// Google OAuth2 token endpoint
	googleTokenEndpoint = "https://oauth2.googleapis.com/token"

	// Default model
	defaultGeminiModel = "gemini-2.0-flash"

	// Request timeout (30 minutes = 1800000000000 ns, from decompiled offset 0x17b4940+0x28)
	requestTimeoutNs = 1800000000000
)

// ============================================================================
// Role Constants (from hex literals in decompiled code)
// ============================================================================

// Role string hex values found in decompiled code:
//   0x6c6f6f74 = "tool" (4 bytes)
//   0x6e61747369737361 + 't' = "assistant" (9 bytes)
//   0x74737973 + 0x6d65 = "system" (6 bytes)
//   0x65646f6d + 'l' = "model" (5 bytes)
//   0x01c3a594 = pointer to "model" string
//   0x01c3978a = pointer to "user" string (4 bytes)

// ============================================================================
// Service Singleton
// ============================================================================

type sAntigravity struct{}

var (
	instance     *sAntigravity
	instanceOnce sync.Once

	// Concurrency manager
	antigravityConcurrencyMgr     *logic.AccountConcurrencyManager
	antigravityConcurrencyMgrOnce sync.Once
)

// New returns the singleton sAntigravity instance.
func New() *sAntigravity {
	instanceOnce.Do(func() {
		instance = &sAntigravity{}
	})
	return instance
}

// GetConcurrencyManager returns the global concurrency manager for Antigravity accounts.
func GetConcurrencyManager() *logic.AccountConcurrencyManager {
	antigravityConcurrencyMgrOnce.Do(func() {
		antigravityConcurrencyMgr = logic.NewAccountConcurrencyManager("antigravity")
	})
	return antigravityConcurrencyMgr
}

func init() {
	logger := gins.Log()
	logger.Info(nil, "[Antigravity] Channel initialized (Google Gemini API)")
}
