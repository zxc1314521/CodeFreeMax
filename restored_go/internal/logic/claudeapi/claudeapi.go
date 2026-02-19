package claudeapi

import (
	"crypto/sha256"
	"encoding/hex"
	"encoding/json"
	"fmt"
	"log"
	"net/http"
	"net/url"
	"strings"
	"sync"
	"time"

	"kiro2api/internal/common"
	"kiro2api/internal/dao"
	"kiro2api/internal/gate"
	"kiro2api/internal/model"
	"kiro2api/internal/proxy"

	"github.com/gogf/gf/v2/encoding/gjson"
	"github.com/gogf/gf/v2/frame/gins"
	"github.com/gogf/gf/v2/net/ghttp"
	"github.com/imroc/req/v3"
	pkce "github.com/nirasan/go-oauth-pkce-code-verifier"
)

// sClaudeApi is the singleton service for Claude API channel logic.
// Recovered from symbol: kiro2api/internal/logic/claudeapi.(*sClaudeApi)
type sClaudeApi struct{}

var (
	instance *sClaudeApi
	once     sync.Once
)

// New creates the singleton sClaudeApi service instance.
// Symbol: kiro2api/internal/logic/claudeapi.New (192B @ 0x13905e0)
func New() *sClaudeApi {
	once.Do(func() {
		instance = &sClaudeApi{}
	})
	return instance
}

// concurrentSessionMap tracks in-flight session IDs to avoid duplicate
// concurrent requests for the same session key.
// Uses sync.Map equivalent (internal/sync.HashTrieMap in the binary).
var concurrentSessionMap sync.Map

// ============================================================================
// Constants extracted from binary strings
// ============================================================================

const (
	anthropicAPIBase     = "https://api.anthropic.com"
	anthropicConsoleBase = "https://console.anthropic.com"

	// Claude Code context injection template
	// From binary: "<thinking_mode>enabled</thinking_mode><max_thinking_length>%d</max_thinking_length>"
	thinkingModeTemplate = "<thinking_mode>enabled</thinking_mode><max_thinking_length>%d</max_thinking_length>"
)
