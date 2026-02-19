package kiro

// helpers.go — Helper/utility functions for the Kiro channel.
//
// Functions:
//   - getContentText          (672B  @ 0x17a4a40) — Extract text from content (string or []block)
//   - generateThinkingPrefix  (192B  @ 0x17a4ce0) — Generate thinking XML prefix
//   - hasThinkingPrefix       (128B  @ 0x17a4da0) — Check if text starts with thinking prefix
//   - generateMachineId       (320B  @ 0x17a3440) — Generate a machine identifier
//   - getProxyURL             (288B  @ 0x17a1160) — Get proxy URL from account
//   - getKiroAuthBaseURL      (128B  @ 0x17a3100) — Get Kiro auth base URL
//   - checkOutboundIP         (1248B @ 0x17a4560) — Check outbound IP address
//   - checkOutboundIPOnce     (448B  @ 0x17a4340) — One-time outbound IP check
//   - buildDynamicHeaders     (896B  @ 0x17a3580) — Build dynamic request headers
//   - buildUsageLimitsHeaders (800B  @ 0x17a3900) — Build usage limits headers
//   - checkBannedResponse     (480B  @ 0x17a2ea0) — Check for banned/blocked responses

import (
	"crypto/rand"
	"encoding/hex"
	"fmt"
	"io"
	"net/http"
	"strings"
	"sync"
	"time"

	"github.com/gogf/gf/v2/frame/gins"
)

// ============================================================================
// getContentText
// ============================================================================

// getContentText extracts the text content from a message content field.
// Symbol: kiro2api/internal/logic/kiro.getContentText (672B @ 0x17a4a40)
//
// The content can be:
//   - A string (DAT_0194e220 type) → return directly
//   - A slice of content blocks (DAT_0192e960 type) → iterate and concatenate text blocks
//   - nil → return ""
//
// From decompiled:
//   if content_type == &DAT_0194e220 { return string(content) }
//   if content_type == &DAT_0192e960 { iterate blocks, extract "text" type, concatenate }
//   else { return "" }
func getContentText(content interface{}) string {
	if content == nil {
		return ""
	}

	// Case 1: content is a plain string
	if s, ok := content.(string); ok {
		return s
	}

	// Case 2: content is a slice of content blocks
	if blocks, ok := content.([]interface{}); ok {
		var textParts []string
		for _, block := range blocks {
			blockMap, ok := block.(map[string]interface{})
			if !ok {
				continue
			}

			// Check block type
			blockType, _ := blockMap["type"].(string)
			if blockType == "text" {
				if text, ok := blockMap["text"].(string); ok {
					textParts = append(textParts, text)
				}
			}
		}
		return strings.Join(textParts, "")
	}

	// Case 3: content is a map with "text" field
	if m, ok := content.(map[string]interface{}); ok {
		if text, ok := m["text"].(string); ok {
			return text
		}
	}

	return ""
}

// ============================================================================
// generateThinkingPrefix / hasThinkingPrefix
// ============================================================================

// generateThinkingPrefix generates the thinking mode XML prefix.
// Symbol: kiro2api/internal/logic/kiro.generateThinkingPrefix (192B @ 0x17a4ce0)
//
// From decompiled: builds a prefix string that wraps thinking content.
// Called at line 489: kiro2api_internal_logic_kiro_generateThinkingPrefix(pauVar14, uVar12, lVar21)
// Parameters appear to be: (messages slice, model name, model name len)
//
// The prefix is used to signal thinking/reasoning mode to the AWS Q backend.
// Format: "<antThinking>" prefix that gets prepended to the system message.
func generateThinkingPrefix(modelName string, modelNameLen int) string {
	if modelNameLen == 0 {
		return ""
	}
	return thinkingPrefix
}

// hasThinkingPrefix checks if the given text starts with the thinking prefix.
// Symbol: kiro2api/internal/logic/kiro.hasThinkingPrefix (128B @ 0x17a4da0)
//
// From decompiled at line 494:
//   cVar10 = kiro2api_internal_logic_kiro_hasThinkingPrefix()
//   if cVar10 == '\0' → prefix not found
func hasThinkingPrefix(text string) bool {
	return strings.HasPrefix(text, thinkingPrefix)
}

// ============================================================================
// generateMachineId
// ============================================================================

// generateMachineId generates a unique machine identifier for request headers.
// Symbol: kiro2api/internal/logic/kiro.generateMachineId (320B @ 0x17a3440)
//
// From decompiled: generates a random hex string used as machine identifier.
// This is used in dynamic headers to identify the client machine.
// The function uses crypto/rand to generate random bytes and hex-encodes them.
func generateMachineId() string {
	b := make([]byte, 16)
	_, err := rand.Read(b)
	if err != nil {
		// Fallback: use timestamp-based ID
		return fmt.Sprintf("kiro-%d", time.Now().UnixNano())
	}
	return hex.EncodeToString(b)
}

// ============================================================================
// getProxyURL
// ============================================================================

// getProxyURL returns the proxy URL configured for this account.
// Symbol: kiro2api/internal/logic/kiro.getProxyURL (288B @ 0x17a1160)
//
// From decompiled: accesses account fields to retrieve proxy configuration.
// Falls back to global proxy setting if account-level proxy is not set.
func getProxyURL(account map[string]interface{}) string {
	if proxyURL, ok := account["proxy_url"].(string); ok && proxyURL != "" {
		return proxyURL
	}
	return ""
}

// ============================================================================
// getKiroAuthBaseURL
// ============================================================================

// getKiroAuthBaseURL returns the Kiro auth service base URL.
// Updated: Uses Kiro's custom OAuth PKCE auth service instead of AWS IDC OIDC.
func getKiroAuthBaseURL(account map[string]interface{}) string {
	if authURL, ok := account["auth_base_url"].(string); ok && authURL != "" {
		return authURL
	}
	return kiroAuthBaseURL
}

// ============================================================================
// checkOutboundIP / checkOutboundIPOnce
// ============================================================================

// checkOutboundIP checks and caches the outbound IP address.
// Symbol: kiro2api/internal/logic/kiro.checkOutboundIP (1248B @ 0x17a4560)
//
// From decompiled: makes an HTTP request to an IP detection service,
// parses the response, and caches the result. Used for request headers.
func (s *sKiro) checkOutboundIP() string {
	if s.outboundIP != "" {
		return s.outboundIP
	}

	// Try to detect outbound IP via HTTP request
	client := &http.Client{Timeout: 10 * time.Second}
	resp, err := client.Get("https://api.ipify.org")
	if err != nil {
		return ""
	}
	defer resp.Body.Close()

	body, err := io.ReadAll(resp.Body)
	if err != nil {
		return ""
	}

	ip := strings.TrimSpace(string(body))
	s.outboundIP = ip
	return ip
}

// checkOutboundIPOnce performs a one-time outbound IP check.
// Symbol: kiro2api/internal/logic/kiro.checkOutboundIPOnce (448B @ 0x17a4340)
//
// From decompiled: uses sync.Once to ensure the IP check runs only once.
// Spawns a goroutine (gowrap1 @ 0x17a4500) for async execution.
func (s *sKiro) checkOutboundIPOnce() {
	outboundIPOnce.Do(func() {
		// Run IP check in background goroutine
		// Symbol: checkOutboundIPOnce.gowrap1 (96B @ 0x17a4500)
		go func() {
			s.checkOutboundIP()
		}()
	})
}

// ============================================================================
// buildDynamicHeaders
// ============================================================================

// buildDynamicHeaders builds the dynamic headers map for Kiro API requests.
// Updated: Includes Kiro-specific headers from source analysis:
//   - x-amzn-kiro-agent-mode: agent mode identifier
//   - x-amzn-codewhisperer-optout: opt-out flag
//   - x-kiro-machineid: machine identifier
//   - x-machine-id: legacy machine ID
func (s *sKiro) buildDynamicHeaders(account map[string]interface{}) map[string]string {
	headers := make(map[string]string)

	// Kiro-specific headers (from Kiro source analysis)
	headers["x-amzn-kiro-agent-mode"] = "none"
	headers["x-amzn-codewhisperer-optout"] = "false"
	headers["x-kiro-machineid"] = s.machineID

	// Legacy machine ID header
	headers["x-machine-id"] = s.machineID

	// Outbound IP header (if detected)
	if s.outboundIP != "" {
		headers["x-outbound-ip"] = s.outboundIP
	}

	// Timestamp header
	headers["x-request-time"] = fmt.Sprintf("%d", time.Now().Unix())

	// Region header from account
	if region, ok := account["region"].(string); ok && region != "" {
		headers["x-region"] = region
	}

	return headers
}

// ============================================================================
// buildUsageLimitsHeaders
// ============================================================================

// buildUsageLimitsHeaders builds headers related to usage limits.
// Symbol: kiro2api/internal/logic/kiro.buildUsageLimitsHeaders (800B @ 0x17a3900)
//
// From decompiled: constructs headers from usage limits data.
// These are included in the request to inform the backend of current usage state.
func buildUsageLimitsHeaders(limits *UsageLimits) map[string]string {
	headers := make(map[string]string)

	if limits == nil {
		return headers
	}

	if limits.TierID != "" {
		headers["x-tier-id"] = limits.TierID
	}

	return headers
}

// ============================================================================
// checkBannedResponse
// ============================================================================

// bannedResponseMu protects concurrent access to banned response checking.
var bannedResponseMu sync.Mutex

// checkBannedResponse checks if the response indicates the account is banned.
// Symbol: kiro2api/internal/logic/kiro.(*sKiro).checkBannedResponse (480B @ 0x17a2ea0)
//
// From decompiled: checks response status codes and body content for ban indicators.
// Returns true if the response indicates the account is banned/blocked.
//
// Checked conditions:
//   - HTTP 401 (Unauthorized)
//   - HTTP 403 (Forbidden)
//   - HTTP 429 (Rate Limited)
//   - Response body contains specific ban keywords
func (s *sKiro) checkBannedResponse(statusCode int, body string) bool {
	bannedResponseMu.Lock()
	defer bannedResponseMu.Unlock()

	logger := gins.Log()

	switch statusCode {
	case http.StatusUnauthorized: // 401
		logger.Warning(nil, "[Kiro] Account unauthorized (401)")
		return true
	case http.StatusForbidden: // 403
		logger.Warning(nil, "[Kiro] Account forbidden (403)")
		return true
	case http.StatusTooManyRequests: // 429
		logger.Warning(nil, "[Kiro] Account rate limited (429)")
		return false // Rate limited but not banned
	}

	// Check for ban keywords in response body
	if strings.Contains(body, "banned") || strings.Contains(body, "suspended") {
		logger.Warning(nil, "[Kiro] Account appears banned based on response content")
		return true
	}

	return false
}
