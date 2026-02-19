package context

import (
	"log"
	"math"
	"sync"
)

// CompressResult holds the result of context compression.
type CompressResult struct {
	Messages         []Message // compressed/truncated messages
	MessageCount     int
	MessageLen       int
	SystemPrompt     string
	Tools            []Tool
	ToolCount        int
	Compressed       bool
	Summary          string
	SummaryLen       int
	SummaryOffset    int
	OriginalMsgCount int
	ErrorMsg         string
	ErrorCode        int
	TotalTokens      int
	SystemTokens     int
	MessageTokens    int
}

// CompressConfig holds configuration for context compression.
type CompressConfig struct {
	MaxRatio         float64 // compression threshold ratio
	SummaryModelName string
}

// SummaryCache holds cached summary data for a session.
type SummaryCache struct {
	SessionID   string
	Summary     string
	Fingerprint string
	Timestamp   int64
	Offset      int
	MsgCount    int
}

// SplitResult holds the result of splitting history into keep/summarize parts.
type SplitResult struct {
	KeepMessages      []Message
	KeepCount         int
	KeepLen           int
	SummarizeMessages []Message
	SummarizeCount    int
	SummarizeLen      int
}

// CompressContextWithTools compresses the conversation context, optionally using
// cached summaries and tool definitions to stay within token limits.
//
// Flow:
// 1. Check if compression is enabled via config
// 2. Look up cached summary if session ID is provided
// 3. Determine if compression is needed (ShouldCompressWithContext)
// 4. If not needed but cache exists, inject cached summary into system prompt
// 5. If compression needed, acquire lock, split history, generate summary, cache it
// 6. Return CompressResult with compressed messages and metadata
func CompressContextWithTools(
	messages []Message,
	tools []Tool,
	config *CompressConfig,
	sessionID string,
	summarizer Summarizer,
) *CompressResult {
	result := &CompressResult{
		Messages:     messages,
		MessageCount: len(messages),
		MessageLen:   len(messages),
		Tools:        tools,
		ToolCount:    len(tools),
		Compressed:   false,
	}

	// If no config provided, use default
	if config == nil {
		config = GetDefaultConfig()
	}

	// Check if compression is enabled
	if !config.IsEnabled() {
		return result
	}

	effectiveConfig := GetEffectiveConfig()
	extractedSessionID := ExtractSessionID()

	// Try to use cached summary
	var cachedSummary *SummaryCache
	var cachedOffset int
	var cachedSummaryText string

	if sessionID != "" {
		cachedSummary = GetSummaryCache(sessionID)
		if summarizer == nil && cachedSummary != nil {
			if IsCacheValid(len(messages), effectiveConfig, cachedSummary, len(messages)) {
				cachedSummaryText = cachedSummary.Summary
				cachedOffset = cachedSummary.Offset
			} else {
				cachedSummary = nil
			}
		} else if summarizer != nil {
			// Force re-summarize when summarizer is provided
			cachedSummary = nil
			cachedSummaryText = ""
			cachedOffset = 0
		}
	}

	// Adjust message window based on cached offset
	msgOffset := 0
	effectiveMessages := messages
	effectiveLen := len(messages)
	if cachedSummary != nil && cachedSummary.Offset > 0 && cachedSummary.Offset < len(messages) {
		msgOffset = cachedSummary.Offset
		effectiveMessages = messages[msgOffset:]
		effectiveLen = len(messages) - msgOffset
	}

	// Check if compression is needed
	compressDecision := ShouldCompressWithContext(effectiveMessages, tools, sessionID, effectiveLen)
	result.TotalTokens = compressDecision.TotalTokens
	result.SystemTokens = compressDecision.SystemTokens

	if !compressDecision.ShouldCompress {
		// No compression needed — but maybe inject cached summary
		result.ErrorMsg = compressDecision.Reason
		result.ErrorCode = compressDecision.ReasonLen

		if cachedSummaryText == "" {
			result.SystemTokens = result.SystemTokens
			result.MessageTokens = result.SystemTokens
			return result
		}

		// Check if injecting summary keeps us within budget
		systemTokens := CountTokens(effectiveMessages)
		messageTokens := CountMessagesTokens(effectiveMessages)
		contextWindow := GetContextWindow()
		totalTokens := systemTokens + messageTokens

		ratio := float64(totalTokens) / float64(contextWindow)
		if ratio <= effectiveConfig.MaxRatio {
			// Inject summary into system prompt
			newSystem := InjectSummaryToSystem(cachedSummaryText, totalTokens, messageTokens, cachedOffset)
			result.SystemPrompt = newSystem
			result.Tools = tools
			result.ToolCount = len(tools)
			result.Messages = effectiveMessages
			result.MessageCount = effectiveLen
			result.MessageLen = effectiveLen
			result.Compressed = true
			result.Summary = cachedSummaryText
			result.SummaryLen = cachedOffset
			result.SummaryOffset = cachedOffset + msgOffset
			result.OriginalMsgCount = effectiveLen
			result.SystemTokens = systemTokens
			result.MessageTokens = messageTokens
			result.TotalTokens = totalTokens
			return result
		}

		// Ratio too high, log warning and fall through to full compression
		log.Printf("[CompressContext] Token ratio %.2f exceeds threshold %.2f (budget factor %.2f), forcing full compression",
			ratio, effectiveConfig.MaxRatio, effectiveConfig.MaxRatio*1.0)
		cachedSummaryText = ""
		cachedOffset = 0
		cachedSummary = nil
		effectiveMessages = messages
		effectiveLen = len(messages)
	}

	// Full compression path
	var locked bool
	if sessionID != "" {
		if !AcquireLock(sessionID) {
			result.ErrorCode = 0x30
			result.ErrorMsg = "compression lock acquisition failed"
			result.SystemTokens = result.SystemTokens
			result.MessageTokens = result.SystemTokens
			return result
		}
		locked = true
	}

	// Split history into keep/summarize parts
	splitResult := SplitHistory(effectiveMessages, effectiveConfig)

	if splitResult.SummarizeCount == 0 {
		// Nothing to summarize
		result.ErrorCode = 0x30
		result.ErrorMsg = "no messages to summarize after split"
		result.SystemTokens = result.SystemTokens
		result.MessageTokens = result.SystemTokens
		if locked {
			ReleaseLock(sessionID)
		}
		return result
	}

	// Use default summarizer if none provided
	if summarizer == nil {
		summarizer = GetDefaultSummarizer()
	}

	// Generate summary
	summaryInput := GenerateSummaryInput(
		splitResult.SummarizeMessages,
		splitResult.SummarizeCount,
		effectiveConfig,
		splitResult.KeepMessages,
	)

	summaryText, err := summarizer.Summarize(summaryInput)
	if err != nil {
		// Fallback: truncate instead of summarize
		fallbackResult := fallbackTruncate(messages, len(messages), result, len(messages))
		if locked {
			ReleaseLock(sessionID)
		}
		return fallbackResult
	}

	// Cache the summary
	if sessionID != "" {
		fingerprint := ComputeFingerprint(effectiveConfig)
		cache := &SummaryCache{
			SessionID:   extractedSessionID,
			Summary:     summaryText,
			Fingerprint: fingerprint,
			Timestamp:   0, // set by SetSummaryCache
			Offset:      splitResult.SummarizeCount + msgOffset,
			MsgCount:    len(messages),
		}
		SetSummaryCache(sessionID, cache)
	}

	// Inject summary into system prompt
	newSystem := InjectSummaryToSystem(summaryText, 0, 0, 0)
	result.SystemPrompt = newSystem
	result.Tools = tools
	result.ToolCount = len(tools)
	result.Messages = splitResult.KeepMessages
	result.MessageCount = splitResult.KeepLen
	result.MessageLen = splitResult.KeepCount
	result.Compressed = true
	result.Summary = summaryText
	result.SummaryLen = cachedOffset
	result.SummaryOffset = splitResult.SummarizeCount + msgOffset
	result.OriginalMsgCount = splitResult.KeepLen

	// Recount tokens after compression
	result.SystemTokens = CountTokens(result.Messages)
	result.MessageTokens = CountMessagesTokens(result.Messages)
	result.TotalTokens = result.SystemTokens + result.MessageTokens

	if locked {
		ReleaseLock(sessionID)
	}
	return result
}

// Summarizer interface for generating conversation summaries.
type Summarizer interface {
	Summarize(input string) (string, error)
}

// --- Stub functions (to be implemented in their respective packages) ---

var (
	defaultConfig     *CompressConfig
	defaultConfigOnce sync.Once
	summaryLocks      sync.Map
)

func GetDefaultConfig() *CompressConfig {
	defaultConfigOnce.Do(func() {
		defaultConfig = &CompressConfig{MaxRatio: 0.7}
	})
	return defaultConfig
}

func (c *CompressConfig) IsEnabled() bool {
	return c != nil && c.MaxRatio > 0
}

func GetEffectiveConfig() *CompressConfig    { return GetDefaultConfig() }
func ExtractSessionID() string               { return "" }
func GetSummaryCache(id string) *SummaryCache { return nil }
func IsCacheValid(msgLen int, cfg *CompressConfig, cache *SummaryCache, totalLen int) bool {
	return cache != nil
}

type CompressDecision struct {
	ShouldCompress bool
	Reason         string
	ReasonLen      int
	TotalTokens    int
	SystemTokens   int
}

func ShouldCompressWithContext(msgs []Message, tools []Tool, sessionID string, msgLen int) *CompressDecision {
	return &CompressDecision{}
}

func AcquireLock(sessionID string) bool  { return true }
func ReleaseLock(sessionID string)       {}
func CountTokens(msgs []Message) int     { return 0 }
func CountMessagesTokens(msgs []Message) int { return 0 }
func GetContextWindow() int              { return 200000 }
func InjectSummaryToSystem(summary string, totalTokens, msgTokens, offset int) string {
	return summary
}
func SplitHistory(msgs []Message, cfg *CompressConfig) *SplitResult {
	return &SplitResult{}
}
func GenerateSummaryInput(msgs []Message, count int, cfg *CompressConfig, keep []Message) string {
	return ""
}
func GetDefaultSummarizer() Summarizer { return nil }
func ComputeFingerprint(cfg *CompressConfig) string { return "" }
func SetSummaryCache(sessionID string, cache *SummaryCache) {}

func fallbackTruncate(msgs []Message, msgLen int, result *CompressResult, totalLen int) *CompressResult {
	// Simple truncation fallback
	half := len(msgs) / 2
	if half < 1 {
		half = 1
	}
	result.Messages = msgs[half:]
	result.MessageCount = len(result.Messages)
	result.Compressed = true
	return result
}

// Message represents a chat message.
type Message struct {
	Role    string      `json:"role"`
	Content interface{} `json:"content"`
}

// Tool represents a tool definition.
type Tool struct {
	Name        string      `json:"name"`
	Description string      `json:"description"`
	Parameters  interface{} `json:"parameters,omitempty"`
}

var _ = math.MaxFloat64 // keep import
