package claudeapi

import (
	"context"
	"fmt"
	"log"
	"net/http"
	"time"

	"kiro2api/internal/model"
	"kiro2api/internal/proxy"

	"github.com/gogf/gf/v2/encoding/gjson"
	"github.com/gogf/gf/v2/frame/gins"
	"github.com/imroc/req/v3"
)

// ============================================================================
// Account Info & Proxy
// ============================================================================

// getProxyURL returns the configured proxy URL for a Claude API account.
// Symbol: (*sClaudeApi).getProxyURL (320B @ 0x13943a0)
//
// Reads the proxy URL from the account's configuration fields.
// Returns empty string if no proxy is configured.
func (s *sClaudeApi) getProxyURL(account *model.ClaudeApiAccount) string {
	if account == nil {
		return ""
	}
	return account.ProxyURL
}

// getAccountInfo fetches account information from the Anthropic API
// using the provided session key.
// Symbol: (*sClaudeApi).getAccountInfo (1280B @ 0x13944e0)
//
// Makes a GET request to the Anthropic API to validate the session key
// and retrieve account/organization membership details.
//
// Returns:
//   - responseBody: the parsed JSON response
//   - proxyResponse: success/error status wrapper
func (s *sClaudeApi) getAccountInfo(
	sessionKey string,
	sessionKeyLen int,
	account *model.ClaudeApiAccount,
	proxyURL string,
) (interface{}, *proxy.Response) {
	client := newClaudeConsoleClient()
	if proxyURL != "" {
		proxy.SetClientProxy(client, proxyURL)
	}

	request := proxy.NewRequest(client)
	request.SetHeader("Cookie", fmt.Sprintf("sessionKey=%s", sessionKey))

	// Fetch account info endpoint
	// Binary string: account info path with session validation
	resp := request.Fetch(fmt.Sprintf("%s/api/auth/session", anthropicConsoleBase), "GET")

	if !resp.Success {
		return nil, resp
	}

	return resp.Body, resp
}

// ============================================================================
// HTTP Client Factories
// ============================================================================

// newClaudeConsoleClient creates an HTTP client configured for the
// Anthropic console (console.anthropic.com).
// Symbol: newClaudeConsoleClient (192B @ 0x13968e0)
func newClaudeConsoleClient() *req.Client {
	client := req.C()
	client.SetBaseURL(anthropicConsoleBase)
	client.SetTimeout(30 * time.Second)
	return client
}

// newClaudePlatformClient creates an HTTP client configured for the
// Anthropic platform API (api.anthropic.com).
// Symbol: newClaudePlatformClient (192B @ 0x13969a0)
func newClaudePlatformClient() *req.Client {
	client := req.C()
	client.SetBaseURL(anthropicAPIBase)
	client.SetTimeout(120 * time.Second)
	return client
}

// newClaudeApiClient creates a fully configured HTTP client for Claude API
// requests, including auth headers, proxy, and TLS settings.
// Symbol: (*sClaudeApi).newClaudeApiClient (672B @ 0x1396640)
//
// The client is configured with:
//   - Authorization header (Bearer token or API key)
//   - Proxy URL if configured
//   - Custom TLS transport settings
//   - Timeout configuration
func (s *sClaudeApi) newClaudeApiClient(account *model.ClaudeApiAccount) *req.Client {
	client := newClaudePlatformClient()

	// Set auth header based on account type
	if account.APIKey != "" {
		client.SetCommonHeader("x-api-key", account.APIKey)
	} else if account.AccessToken != "" {
		client.SetCommonHeader("Authorization", fmt.Sprintf("Bearer %s", account.AccessToken))
	}

	// Set proxy if configured
	if account.ProxyURL != "" {
		proxy.SetClientProxy(client, account.ProxyURL)
	}

	// The binary has a closure (func1) that handles request interception
	// for adding dynamic headers per-request
	// Symbol: (*sClaudeApi).newClaudeApiClient.func1 (1408B @ 0x1397780)
	client.OnBeforeRequest(func(c *req.Client, r *req.Request) error {
		// Add anthropic-specific headers
		r.SetHeader("anthropic-version", "2023-06-01")
		if account.OrganizationID != "" {
			r.SetHeader("anthropic-organization", account.OrganizationID)
		}
		return nil
	})

	return client
}

// ============================================================================
// Chat Request Sending
// ============================================================================

// SendChatRequest sends a chat completion request to the Anthropic API.
// Symbol: (*sClaudeApi).SendChatRequest (2272B @ 0x13920e0)
//
// Handles:
//   - Building the request with proper headers
//   - Injecting Claude Code context (thinking mode)
//   - Forwarding to the /v1/messages endpoint
//   - Returning the streaming response
func (s *sClaudeApi) SendChatRequest(
	ctx context.Context,
	account *model.ClaudeApiAccount,
	body []byte,
) *proxy.Response {
	logger := gins.Log()

	// Inject Claude Code thinking context into the request body
	modifiedBody := injectClaudeCodeContext(body, account.ThinkingBudget, account.Context)

	// Create API client for this account
	client := s.newClaudeApiClient(account)

	request := proxy.NewRequest(client)
	request.SetBody(modifiedBody)
	request.SetHeader("Content-Type", "application/json")

	// Enable streaming
	request.SetHeader("Accept", "text/event-stream")

	logger.Infof(ctx, "[ClaudeApi] SendChatRequest account=%d, org=%s",
		account.ID, account.OrganizationID)

	resp := request.Fetch(fmt.Sprintf("%s/v1/messages", anthropicAPIBase), "POST")
	return resp
}

// SendCountTokens sends a token counting request to the Anthropic API.
// Symbol: (*sClaudeApi).SendCountTokens (2656B @ 0x13929c0)
//
// Similar to SendChatRequest but targets the /v1/messages/count_tokens endpoint.
func (s *sClaudeApi) SendCountTokens(
	ctx context.Context,
	account *model.ClaudeApiAccount,
	body []byte,
) *proxy.Response {
	client := s.newClaudeApiClient(account)

	request := proxy.NewRequest(client)
	request.SetBody(body)
	request.SetHeader("Content-Type", "application/json")

	resp := request.Fetch(fmt.Sprintf("%s/v1/messages/count_tokens", anthropicAPIBase), "POST")
	return resp
}

// ============================================================================
// Token Management
// ============================================================================

// CheckToken validates whether the account's token is still valid.
// Symbol: (*sClaudeApi).CheckToken (1312B @ 0x13949e0)
//
// Checks token expiry and refreshes if needed.
// Returns true if the token is valid (or was successfully refreshed).
func (s *sClaudeApi) CheckToken(account *model.ClaudeApiAccount) bool {
	if account == nil {
		return false
	}

	// Check if token has expired
	if !account.TokenExpiresAt.IsZero() && time.Now().Before(account.TokenExpiresAt) {
		return true // token still valid
	}

	// Token expired or no expiry set — attempt refresh
	if account.RefreshToken != "" {
		err := s.RefreshToken(account)
		if err != nil {
			log.Printf("[ClaudeApi] CheckToken refresh failed for account %d: %v", account.ID, err)
			return false
		}
		return true
	}

	// No refresh token — try session key validation
	if account.SessionKey != "" {
		err := s.checkSessionKey(account)
		if err != nil {
			log.Printf("[ClaudeApi] CheckToken session key check failed for account %d: %v", account.ID, err)
			return false
		}
		return true
	}

	return false
}

// RefreshToken refreshes the OAuth access token using the refresh token.
// Symbol: (*sClaudeApi).RefreshToken (1952B @ 0x1396a60)
//
// Sends a token refresh request to the Anthropic OAuth endpoint and
// updates the account with new access/refresh tokens.
func (s *sClaudeApi) RefreshToken(account *model.ClaudeApiAccount) error {
	client := newClaudeConsoleClient()
	if account.ProxyURL != "" {
		proxy.SetClientProxy(client, account.ProxyURL)
	}

	request := proxy.NewRequest(client)
	request.SetBody(map[string]string{
		"grant_type":    "refresh_token",
		"refresh_token": account.RefreshToken,
		"client_id":     account.ClientID,
	})

	resp := request.Fetch(fmt.Sprintf("%s/oauth/token", anthropicConsoleBase), "POST")
	if !resp.Success {
		return resp.Error()
	}

	tokenJson := gjson.New(resp.Body)
	account.AccessToken = tokenJson.Get("access_token").String()
	account.RefreshToken = tokenJson.Get("refresh_token").String()

	expiresIn := tokenJson.Get("expires_in").Int()
	expiryDuration := time.Duration(expiresIn)*time.Second - 5*time.Minute
	account.TokenExpiresAt = time.Now().Add(expiryDuration)

	account.EncryptAndSetCredentials()

	return nil
}

// authRefresh performs a full authentication refresh cycle.
// Symbol: (*sClaudeApi).authRefresh (2112B @ 0x13918a0)
//
// This is a more comprehensive refresh that may involve re-authentication
// rather than just token refresh. Used when RefreshToken fails.
func (s *sClaudeApi) authRefresh(account *model.ClaudeApiAccount) error {
	// First try token refresh
	if account.RefreshToken != "" {
		err := s.RefreshToken(account)
		if err == nil {
			return nil
		}
		log.Printf("[ClaudeApi] authRefresh token refresh failed, trying session key: %v", err)
	}

	// Fall back to session key validation (full PKCE flow)
	if account.SessionKey != "" {
		return s.checkSessionKey(account)
	}

	return fmt.Errorf("no refresh token or session key available for account %d", account.ID)
}

// ============================================================================
// Error Handling
// ============================================================================

// HandleErrorResponse is the top-level error response handler.
// Symbol: (*sClaudeApi).HandleErrorResponse (160B @ 0x1393420)
//
// This is a thin wrapper that delegates to handleApiErrorResponse.
// The small size (160B) confirms it's just a dispatch function.
func (s *sClaudeApi) HandleErrorResponse(resp *proxy.Response) {
	if resp == nil {
		return
	}
	s.handleApiErrorResponse(nil, resp.StatusCode)
}

// handleApiErrorResponse handles API error responses by status code,
// updating account status and triggering appropriate recovery actions.
// Symbol: (*sClaudeApi).handleApiErrorResponse (2432B @ 0x1390700)
//
// Status code routing:
//   - 401: Unauthorized → invalidate credentials, attempt re-auth
//   - 402: Payment Required → mark account as quota exhausted
//   - 403: Forbidden → mark account as suspended
//   - 429: Rate Limited → apply backoff, update rate limit state
//   - 5xx: Server Error → log and potentially retry
//
// The function also has a closure:
// Symbol: (*sClaudeApi).handleApiErrorResponse.func1 (256B @ 0x1391080)
// which handles deferred cleanup operations.
func (s *sClaudeApi) handleApiErrorResponse(account *model.ClaudeApiAccount, statusCode int) {
	logger := gins.Log()
	ctx := context.Background()

	if account == nil {
		logger.Warningf(ctx, "[ClaudeApi] handleApiErrorResponse called with nil account, status=%d", statusCode)
		return
	}

	switch {
	case statusCode == 401:
		// Unauthorized — clear credentials
		logger.Warningf(ctx, "[ClaudeApi] 401 Unauthorized for account %d, invalidating", account.ID)
		account.Status = "invalid"
		account.AccessToken = ""
		// Attempt re-authentication in background
		go func() {
			_ = s.authRefresh(account)
		}()

	case statusCode == 402:
		// Payment Required — quota exhausted
		logger.Warningf(ctx, "[ClaudeApi] 402 Payment Required for account %d", account.ID)
		account.Status = "quota_exhausted"

	case statusCode == 403:
		// Forbidden — account suspended or access revoked
		logger.Warningf(ctx, "[ClaudeApi] 403 Forbidden for account %d", account.ID)
		account.Status = "suspended"

	case statusCode == 429:
		// Rate Limited
		logger.Warningf(ctx, "[ClaudeApi] 429 Rate Limited for account %d", account.ID)
		account.Status = "rate_limited"

	case statusCode >= 500:
		// Server Error — log but don't change account status
		logger.Warningf(ctx, "[ClaudeApi] %d Server Error for account %d", statusCode, account.ID)

	default:
		logger.Infof(ctx, "[ClaudeApi] Unhandled error status %d for account %d", statusCode, account.ID)
	}
}

// ============================================================================
// Account Settings
// ============================================================================

// patchAccountSettings updates account settings on the Anthropic platform.
// Symbol: (*sClaudeApi).patchAccountSettings (1824B @ 0x1391180)
//
// Sends a PATCH request to update organization/account settings.
func (s *sClaudeApi) patchAccountSettings(account *model.ClaudeApiAccount, settings map[string]interface{}) error {
	client := s.newClaudeApiClient(account)

	request := proxy.NewRequest(client)
	request.SetBody(settings)

	resp := request.Fetch(
		fmt.Sprintf("%s/api/organizations/%s/settings", anthropicConsoleBase, account.OrganizationID),
		"PATCH",
	)

	if !resp.Success {
		return resp.Error()
	}
	return nil
}

// ============================================================================
// Organization Usage
// ============================================================================

// GetOrganizationUsage fetches usage statistics for the account's organization.
// Symbol: (*sClaudeApi).GetOrganizationUsage (1408B @ 0x1397200)
func (s *sClaudeApi) GetOrganizationUsage(account *model.ClaudeApiAccount) (interface{}, error) {
	client := s.newClaudeApiClient(account)

	request := proxy.NewRequest(client)
	resp := request.Fetch(
		fmt.Sprintf("%s/api/organizations/%s/usage", anthropicConsoleBase, account.OrganizationID),
		"GET",
	)

	if !resp.Success {
		return nil, resp.Error()
	}
	return resp.Body, nil
}
