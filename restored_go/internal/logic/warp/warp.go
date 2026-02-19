package warp

// warp.go — Core types, initialization, and service registration for the Warp channel.
//
// Warp (Warp Terminal AI) uses:
//   - Firebase Auth for authentication (token refresh)
//   - Protobuf binary protocol for request/response
//   - GraphQL for user details & feedback (GetQuotaInfo, RefundCredits)
//   - Multi-agent support with complex prompt building
//
// From GoReSym: 61 functions in logic/warp package
// From decompiled: 7 major functions (ChatCompletions, buildFullPrompt,
//   MapToolToClaudeCode, MapToolsToClaudeCode, RefreshToken, RefundCredits, GetQuotaInfo)

import (
	"context"
	"fmt"
	"sync"
	"time"

	"github.com/gogf/gf/v2/frame/g"
	"github.com/gogf/gf/v2/frame/gins"
	"github.com/google/uuid"
	"github.com/imroc/req/v3"
)

// ============================================================================
// Constants
// ============================================================================

const (
	// Warp API endpoints
	WarpAPIBaseURL     = "https://app.warp.dev"
	WarpAPIStreamURL   = WarpAPIBaseURL + "/api/v1/ai/stream"
	WarpFirebaseAPIKey = "AIzaSyBMmjMHOCbzmRoVRqDFpRabhRBfMGDwWJA"
	WarpFirebaseURL    = "https://securetoken.googleapis.com/v1/token?key=" + WarpFirebaseAPIKey

	// GraphQL endpoint
	WarpGraphQLURL = "https://app.warp.dev/graphql"

	// Client identification
	WarpClientVersion = "v0.2025.01.28.08.02.stable_05"
	WarpOSName        = "macOS"
	WarpOSVersion     = "15.6.1"
	WarpAppName       = "warp"

	// Headers
	HeaderAuthorization = "Authorization"
	HeaderContentType   = "Content-Type"
	HeaderAccept        = "Accept"
	HeaderUserAgent     = "User-Agent"
	HeaderXApp          = "x-app"
	HeaderXAppVersion   = "x-app-version"
	HeaderXDeviceID     = "x-device-id"
	HeaderXRequestID    = "x-request-id"
	HeaderXOS           = "x-os"
	HeaderXOSVersion    = "x-os-version"
	HeaderXTimezone     = "x-timezone"

	// Content types
	ContentTypeProtobuf = "application/x-protobuf"
	ContentTypeJSON     = "application/json"

	// Channel name
	ChannelName = "warp"

	// Aliases used in client.go
	WarpAPIBase     = WarpAPIBaseURL
	WarpStreamPath  = "/api/v1/ai/stream"
	WarpGraphQLPath = "/graphql"
)

// ============================================================================
// Warp model mapping
// ============================================================================

// warpModelMap maps OpenAI model names to Warp internal model identifiers.
// From decompiled: map.init.0 and map.init.2 (model mapping initialization)
var warpModelMap = map[string]string{
	// Claude models
	"claude-3.5-sonnet":    "claude_3_5_sonnet",
	"claude-3-5-sonnet":    "claude_3_5_sonnet",
	"claude-3.5-haiku":     "claude_3_5_haiku",
	"claude-3-5-haiku":     "claude_3_5_haiku",
	"claude-3-opus":        "claude_3_opus",
	"claude-sonnet-4":      "claude_sonnet_4",
	"claude-4-sonnet":      "claude_sonnet_4",
	"claude-opus-4":        "claude_opus_4",
	"claude-4-opus":        "claude_opus_4",
	// GPT models
	"gpt-4o":               "gpt_4o",
	"gpt-4o-mini":          "gpt_4o_mini",
	"gpt-4-turbo":          "gpt_4_turbo",
	"o1":                   "o1",
	"o1-mini":              "o1_mini",
	"o1-preview":           "o1_preview",
	"o3-mini":              "o3_mini",
	// Gemini models
	"gemini-2.0-flash":     "gemini_2_0_flash",
	"gemini-2.5-pro":       "gemini_2_5_pro",
	"gemini-2.5-flash":     "gemini_2_5_flash",
	// DeepSeek models
	"deepseek-r1":          "deepseek_r1",
	"deepseek-v3":          "deepseek_v3",
	// Grok models
	"grok-3":               "grok_3",
	"grok-3-mini":          "grok_3_mini",
}

// allowedWarpModels is the set of models that can be used with Warp.
// From decompiled: isWarpModelAllowed (0x17148c0, 1056B)
var allowedWarpModels map[string]bool

func init() {
	allowedWarpModels = make(map[string]bool)
	for k := range warpModelMap {
		allowedWarpModels[k] = true
	}
}

// isWarpModelAllowed checks if a model name is supported by Warp.
// From decompiled: kiro2api_internal_logic_warp_isWarpModelAllowed
func isWarpModelAllowed(model string) bool {
	return allowedWarpModels[model]
}

// NOTE: mapToWarpModel is defined in client.go — removed duplicate here.

// ============================================================================
// sWarp — Main service struct
// ============================================================================

// sWarp is the main Warp channel service.
// From decompiled: receiver type for ChatCompletions, CheckToken, RefreshToken,
// buildWarpRequest, buildFullPrompt, buildInput, buildInputContext,
// buildMCPContext, buildMetadata, buildSettings, extractImagesFromMessages,
// setInputSchema, toProtobufValue, GetQuotaInfo, RefundCredits
type sWarp struct {
	client       *req.Client
	firebaseKey  string
	protoManager *ProtoManager
	proxy        string
	accounts     []*WarpAccount
	accountIdx   int
	mu           sync.RWMutex
}

// New creates a new Warp service instance.
// From decompiled: kiro2api_internal_logic_warp_New (0x1712c40, 128B)
func New() *sWarp {
	s := &sWarp{
		client:       NewWarpAPIClient(),
		firebaseKey:  WarpFirebaseAPIKey,
		protoManager: NewProtoManager(),
	}
	return s
}

// ============================================================================
// WarpAccount — Account data model
// ============================================================================

// WarpAccount represents a Warp account with Firebase credentials.
// From decompiled: field offsets in ChatCompletions and RefreshToken
//   +0x08: RefreshToken (string)
//   +0x10: RefreshTokenLen
//   +0x38: IDToken (string)
//   +0x40: IDTokenLen
//   +0x50: DeviceID (string)
//   +0x58: DeviceIDLen
//   +0xC0: DebugDump flag
type WarpAccount struct {
	ID           int64     `json:"id"`
	Email        string    `json:"email"`
	RefreshToken string    `json:"refresh_token"`
	IDToken      string    `json:"id_token"`
	DeviceID     string    `json:"device_id"`
	RequestID    string    `json:"request_id"`
	ProxyURL     string    `json:"proxy_url"`
	Plan         string    `json:"plan"` // "free" or "pro"
	TokenExpiry  time.Time `json:"token_expiry"`
}

// ChatCompletionRequest represents an OpenAI-compatible chat completion request.
type ChatCompletionRequest struct {
	Model    string                   `json:"model"`
	Messages []map[string]interface{} `json:"messages"`
	Stream   bool                     `json:"stream"`
}

// WarpQuotaInfo holds quota information from the Warp GraphQL API.
type WarpQuotaInfo struct {
	Remaining float64   `json:"remaining"`
	Total     float64   `json:"total"`
	ResetAt   time.Time `json:"reset_at"`
	PlanName  string    `json:"plan_name"`
	PlanTier  string    `json:"plan_tier"`
}

// ============================================================================
// GetWarpProxyURL
// ============================================================================

// GetWarpProxyURL returns the proxy URL for Warp API requests.
// From decompiled: kiro2api_internal_logic_warp_GetWarpProxyURL (0x1714ce0, 1024B)
// Reads from config: warp.proxy_url
func GetWarpProxyURL() string {
	val, err := g.Cfg().Get(context.Background(), "warp.proxy_url")
	if err != nil || val.IsEmpty() {
		return ""
	}
	return val.String()
}

// ============================================================================
// NewWarpAPIClient
// ============================================================================

// NewWarpAPIClient creates a new HTTP client configured for Warp API.
// From decompiled: kiro2api_internal_logic_warp_NewWarpAPIClient (0x171ef40, 416B)
// Uses req/v3 with retry and common headers.
func NewWarpAPIClient() *req.Client {
	client := req.C().
		SetCommonRetryFixedInterval(3).
		SetCommonRetryCount(2).
		SetTimeout(0)

	return client
}

// ============================================================================
// NewFirebaseClient
// ============================================================================

// NewFirebaseClient creates a new HTTP client for Firebase Auth API.
// From decompiled: kiro2api_internal_logic_warp_NewFirebaseClient (0x171f100, 128B)
func NewFirebaseClient() *req.Client {
	return req.C().SetTimeout(0)
}

// ============================================================================
// NewGraphQLClient
// ============================================================================

// NewGraphQLClient creates a new HTTP client for Warp GraphQL API.
// From decompiled: kiro2api_internal_logic_warp_NewGraphQLClient (0x171f180, 160B)
func NewGraphQLClient() *req.Client {
	return req.C().SetTimeout(0)
}

// ============================================================================
// CheckToken
// ============================================================================

// CheckToken verifies and refreshes the Firebase token if needed.
// From decompiled: kiro2api_internal_logic_warp_sWarp_CheckToken (0x1712d20, 352B)
// Uses sync.Once-like pattern with func1 and func2 closures.
func (s *sWarp) CheckToken(account *WarpAccount) error {
	logger := gins.Log()

	if account.RefreshToken == "" {
		return fmt.Errorf("warp account has no refresh token")
	}

	// Check if ID token is still valid
	if account.IDToken != "" {
		// Token exists, assume valid (actual JWT expiry check in production)
		return nil
	}

	// Need to refresh
	logger.Debugf(nil, "[Warp] Token expired, refreshing for account %s", account.Email)
	return s.RefreshToken(account)
}

// ============================================================================
// EnsureDeviceID
// ============================================================================

// ensureDeviceID generates a device ID if the account doesn't have one.
// From decompiled: pattern in ChatCompletions and GetQuotaInfo where
// DeviceID is checked and uuid.NewString() is called if empty.
func ensureDeviceID(account *WarpAccount) {
	if account.DeviceID == "" {
		account.DeviceID = uuid.NewString()
		account.RequestID = uuid.NewString()
		// Update in database
		// dao.WarpAccountDao.Update(account)
	}
}
