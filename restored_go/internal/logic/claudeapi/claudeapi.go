package claudeapi

import (
	"sync"
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
