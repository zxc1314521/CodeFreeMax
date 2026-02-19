package kiro

// auth.go — Authentication and token management for the Kiro channel.
//
// The Kiro channel uses a custom OAuth PKCE auth service at
// https://prod.us-east-1.auth.desktop.kiro.dev for authentication.
// Token refresh uses POST /refreshToken with JSON body and Bearer auth.
//
// Auth flow:
//   1. RefreshToken checks if token is expiring soon
//   2. If refresh needed, calls authRefresh
//   3. authRefresh calls refreshToken with Kiro auth endpoint
//   4. refreshToken POSTs to {authBaseURL}/refreshToken with JSON body
//   5. Response contains new accessToken, refreshToken, expiresIn
//   6. Account is updated with new credentials

import (
	"encoding/json"
	"fmt"
	"io"
	"net/http"
	"strings"
	"sync"
	"time"

	"github.com/gogf/gf/v2/frame/gins"
	"github.com/imroc/req/v3"
)

// ============================================================================
// Auth Constants
// ============================================================================

const (
	// Kiro token refresh endpoint path
	kiroRefreshTokenPath = "/refreshToken"

	// Content-Type for token requests (JSON for Kiro auth)
	authContentType = "application/json"

	// Auth client timeout (30 seconds)
	authClientTimeout = 30 * time.Second

	// Token refresh lock timeout
	refreshLockTimeout = 60 * time.Second
)

// refreshLocks provides per-account locking for token refresh operations.
// Prevents concurrent refresh attempts for the same account.
var refreshLocks sync.Map

// getRefreshLock returns the mutex for a given account ID.
func getRefreshLock(accountID int64) *sync.Mutex {
	val, _ := refreshLocks.LoadOrStore(accountID, &sync.Mutex{})
	return val.(*sync.Mutex)
}

// ============================================================================
// RefreshToken (Public Entry Point)
// ============================================================================

// RefreshToken refreshes the access token for a Kiro account if needed.
// Symbol: kiro2api/internal/logic/kiro.(*sKiro).RefreshToken (320B @ 0x17a1280)
//
// From decompiled:
//   1. Check if token is expiring soon (tokenRefreshBufferSec = 300s)
//   2. If not expiring and access_token exists → return nil
//   3. Acquire per-account lock to prevent concurrent refreshes
//   4. Double-check after lock acquisition
//   5. Call authRefresh
//   6. On success: update account tokens (func1 closure @ 0x17a1400)
//   7. On error: log and return error (func2 closure @ 0x17a13c0)
func (s *sKiro) RefreshToken(
	client *req.Client,
	account map[string]interface{},
) error {
	logger := gins.Log()

	// Step 1: Check if token needs refresh
	if !s.isTokenExpiringSoon(account) {
		if accessToken, ok := account["access_token"].(string); ok && accessToken != "" {
			return nil
		}
	}

	// Step 2: Get account ID for locking
	accountID, _ := account["id"].(int64)

	// Step 3: Acquire per-account refresh lock
	mu := getRefreshLock(accountID)
	mu.Lock()
	defer mu.Unlock()

	// Step 4: Double-check after acquiring lock (another goroutine may have refreshed)
	if !s.isTokenExpiringSoon(account) {
		if accessToken, ok := account["access_token"].(string); ok && accessToken != "" {
			return nil
		}
	}

	// Step 5: Perform the actual refresh
	logger.Infof(nil, "[Kiro] Refreshing token for account %d", accountID)

	err := s.authRefresh(client, account)
	if err != nil {
		// func2 closure (64B @ 0x17a13c0): error handler
		logger.Warningf(nil, "[Kiro] Token refresh failed for account %d: %v", accountID, err)
		return fmt.Errorf("kiro token refresh failed for account %d: %w", accountID, err)
	}

	// func1 closure (160B @ 0x17a1400): post-refresh callback
	logger.Infof(nil, "[Kiro] Token refreshed successfully for account %d", accountID)
	return nil
}

// ============================================================================
// authRefresh
// ============================================================================

// authRefresh performs the core authentication refresh logic.
// Updated: Uses Kiro's custom /refreshToken endpoint with JSON body and Bearer auth.
func (s *sKiro) authRefresh(
	client *req.Client,
	account map[string]interface{},
) error {
	// Extract refresh token
	refreshToken, _ := account["refresh_token"].(string)
	if refreshToken == "" {
		accountID, _ := account["id"].(int64)
		return fmt.Errorf("kiro account %d has no refresh token", accountID)
	}

	// Get Kiro auth base URL
	authBase := getKiroAuthBaseURL(account)

	// Get current access token for Bearer auth
	accessToken, _ := account["access_token"].(string)

	// Get proxy URL
	proxyURL := getProxyURL(account)

	// Perform the token refresh
	tokenResp, err := s.refreshToken(client, authBase, accessToken, refreshToken, proxyURL)
	if err != nil {
		return err
	}

	// Update account with new tokens
	if tokenResp.AccessToken != "" {
		account["access_token"] = tokenResp.AccessToken
	}
	if tokenResp.RefreshToken != "" {
		account["refresh_token"] = tokenResp.RefreshToken
	}
	if tokenResp.ExpiresIn > 0 {
		account["token_expiry"] = time.Now().Unix() + tokenResp.ExpiresIn
	}
	if tokenResp.IDToken != "" {
		account["id_token"] = tokenResp.IDToken
	}

	return nil
}

// ============================================================================
// refreshToken
// ============================================================================

// refreshToken performs the Kiro token refresh HTTP request.
// Updated: Uses POST /refreshToken with JSON body and Bearer auth header.
//
// Request format:
//   POST {authBaseURL}/refreshToken
//   Authorization: Bearer {accessToken}
//   Content-Type: application/json
//   Body: {"refreshToken": "{refreshToken}"}
//
// Response format:
//   {"accessToken": "...", "refreshToken": "...", "expiresIn": 3600}
func (s *sKiro) refreshToken(
	client *req.Client,
	authBaseURL string,
	accessToken string,
	refreshToken string,
	proxyURL string,
) (*KiroTokenResponse, error) {
	logger := gins.Log()

	// Step 1: Build token endpoint URL
	tokenURL := authBaseURL + kiroRefreshTokenPath

	// Step 2: Build JSON body
	reqBody := map[string]string{
		"refreshToken": refreshToken,
	}
	bodyBytes, err := json.Marshal(reqBody)
	if err != nil {
		return nil, fmt.Errorf("marshal refresh request: %w", err)
	}

	// Step 3: Create auth HTTP client
	authClient := newKiroAuthClient(client, proxyURL)

	// Step 4: Build and send request
	reqObj := authClient.R()
	reqObj.SetHeader("Content-Type", authContentType)
	if accessToken != "" {
		reqObj.SetHeader("Authorization", "Bearer "+accessToken)
	}
	reqObj.SetBodyBytes(bodyBytes)

	logger.Debugf(nil, "[Kiro] POST %s", tokenURL)

	resp, err := reqObj.Post(tokenURL)
	if err != nil {
		return nil, fmt.Errorf("POST %s: %w", tokenURL, err)
	}

	// Step 5: Read response body
	respBytes := resp.Bytes()

	// Step 6: Check HTTP status
	if resp.StatusCode != http.StatusOK {
		logger.Warningf(nil, "[Kiro] Token refresh returned HTTP %d: %s",
			resp.StatusCode, truncateStr(string(respBytes), 200))
		return nil, fmt.Errorf("token refresh HTTP %d: %s", resp.StatusCode, string(respBytes))
	}

	// Step 7: Parse JSON response
	var tokenResp KiroTokenResponse
	if err := json.Unmarshal(respBytes, &tokenResp); err != nil {
		return nil, fmt.Errorf("parse token response: %w", err)
	}

	// Step 8: Validate response
	if tokenResp.AccessToken == "" {
		return nil, fmt.Errorf("token refresh returned empty access_token")
	}

	return &tokenResp, nil
}

// ============================================================================
// ValidateRefreshToken
// ============================================================================

// ValidateRefreshToken checks if the account's refresh token is still valid.
// Symbol: kiro2api/internal/logic/kiro.(*sKiro).ValidateRefreshToken (128B @ 0x17a3080)
//
// From decompiled (128 bytes — very small):
//   Simple check: return refresh_token != "" && token_expiry > now
//   This is a lightweight validation without making an HTTP request.
func (s *sKiro) ValidateRefreshToken(account map[string]interface{}) bool {
	refreshToken, _ := account["refresh_token"].(string)
	if refreshToken == "" {
		return false
	}

	// Check if token_expiry exists and is in the future
	expiry, ok := account["token_expiry"].(int64)
	if !ok || expiry == 0 {
		// No expiry set — token might still be valid, return true
		return true
	}

	return time.Now().Unix() < expiry
}

// ============================================================================
// isTokenExpiringSoon
// ============================================================================

// isTokenExpiringSoon checks if the access token is near expiry.
// Similar to antigravity.IsTokenExpiringSoon but uses tokenRefreshBufferSec (300s).
func (s *sKiro) isTokenExpiringSoon(account map[string]interface{}) bool {
	expiry, ok := account["token_expiry"].(int64)
	if !ok || expiry == 0 {
		return true
	}
	return time.Now().Unix()+tokenRefreshBufferSec >= expiry
}

// ============================================================================
// getUsageLimits
// ============================================================================

// getUsageLimits retrieves the usage limits for a Kiro account from the API.
// Symbol: kiro2api/internal/logic/kiro.(*sKiro).getUsageLimits (2176B @ 0x17a20e0)
//
// From decompiled (2176 bytes):
//   1. Build request to usage limits endpoint
//   2. Set authorization header with access_token
//   3. GET request to {endpoint}/usageLimits or similar
//   4. Parse JSON response into UsageLimits struct
//   5. Return limits or error
func (s *sKiro) getUsageLimits(
	client *req.Client,
	account map[string]interface{},
) (*UsageLimits, error) {
	logger := gins.Log()

	accessToken, _ := account["access_token"].(string)
	if accessToken == "" {
		return nil, fmt.Errorf("no access token for usage limits request")
	}

	// Build endpoint URL
	endpoint, _ := account["endpoint"].(string)
	if endpoint == "" {
		endpoint = awsQAPIBase
	}
	usageURL := endpoint + "/usageLimits"

	// Get proxy
	proxyURL := getProxyURL(account)

	// Create client
	clonedClient := client.Clone()
	if proxyURL != "" {
		clonedClient.SetProxyURL(proxyURL)
	}
	clonedClient.SetTimeout(authClientTimeout)

	// Build request
	reqObj := clonedClient.R()
	reqObj.SetHeader("Authorization", "Bearer "+accessToken)

	logger.Debugf(nil, "[Kiro] GET %s", usageURL)

	resp, err := reqObj.Get(usageURL)
	if err != nil {
		return nil, fmt.Errorf("GET %s: %w", usageURL, err)
	}

	if resp.StatusCode != http.StatusOK {
		bodyStr := truncateStr(resp.String(), 200)
		return nil, fmt.Errorf("usage limits HTTP %d: %s", resp.StatusCode, bodyStr)
	}

	var limits UsageLimits
	if err := resp.UnmarshalJson(&limits); err != nil {
		return nil, fmt.Errorf("parse usage limits: %w", err)
	}

	return &limits, nil
}

// ============================================================================
// GetUsageInfo
// ============================================================================

// GetUsageInfo retrieves usage information for a Kiro account.
// Symbol: kiro2api/internal/logic/kiro.(*sKiro).GetUsageInfo (320B @ 0x17a2960)
//
// From decompiled (320 bytes):
//   1. Call getUsageLimits to get current limits
//   2. Format into a response map
//   3. Return usage info
func (s *sKiro) GetUsageInfo(
	client *req.Client,
	account map[string]interface{},
) (map[string]interface{}, error) {
	limits, err := s.getUsageLimits(client, account)
	if err != nil {
		return nil, err
	}

	result := map[string]interface{}{
		"tier_id":       limits.TierID,
		"monthly_usage": limits.MonthlyUsage,
		"daily_usage":   limits.DailyUsage,
		"limits":        limits.Limits,
	}

	return result, nil
}

// ============================================================================
// newKiroAuthClient
// ============================================================================

// newKiroAuthClient creates an HTTP client configured for auth requests.
// Symbol: kiro2api/internal/logic/kiro.newKiroAuthClient (288B @ 0x17a3320)
//
// From decompiled (288 bytes):
//   1. Clone the base client
//   2. Set proxy if configured
//   3. Set timeout to authClientTimeout
//   4. Configure TLS settings
//   5. Set redirect policy (func1 closure @ 0x17ab1e0)
//
// The func1 closure (640B @ 0x17ab1e0) handles redirect logic,
// likely preventing redirects during auth or following specific redirect patterns.
func newKiroAuthClient(baseClient *req.Client, proxyURL string) *req.Client {
	authClient := baseClient.Clone()

	if proxyURL != "" {
		authClient.SetProxyURL(proxyURL)
	}

	authClient.SetTimeout(authClientTimeout)

	// Disable redirects for auth requests
	// From decompiled: func1 closure (640B @ 0x17ab1e0) sets redirect policy
	authClient.SetRedirectPolicy(req.NoRedirectPolicy())

	return authClient
}

// ============================================================================
// CheckToken
// ============================================================================

// CheckToken verifies the access token is valid by making a lightweight API call.
// Symbol: kiro2api/internal/logic/kiro.(*sKiro).CheckToken (1024B @ 0x17a2aa0)
//
// From decompiled (1024 bytes):
//   1. Extract access_token from account
//   2. Build a lightweight request to the API (e.g., /userInfo or /health)
//   3. Set Authorization header
//   4. Check response status
//   5. If 401/403 → token invalid
//   6. If 200 → token valid
//   7. Return validity status
func (s *sKiro) CheckToken(
	client *req.Client,
	account map[string]interface{},
) (bool, error) {
	logger := gins.Log()

	accessToken, _ := account["access_token"].(string)
	if accessToken == "" {
		return false, nil
	}

	// Build endpoint URL
	endpoint, _ := account["endpoint"].(string)
	if endpoint == "" {
		endpoint = awsQAPIBase
	}

	// Use usage limits endpoint as a lightweight check
	checkURL := endpoint + "/usageLimits"

	// Get proxy
	proxyURL := getProxyURL(account)

	// Create client
	authClient := newKiroAuthClient(client, proxyURL)

	// Build request
	reqObj := authClient.R()
	reqObj.SetHeader("Authorization", "Bearer "+accessToken)

	resp, err := reqObj.Get(checkURL)
	if err != nil {
		logger.Warningf(nil, "[Kiro] CheckToken request failed: %v", err)
		return false, err
	}

	// Check response
	switch resp.StatusCode {
	case http.StatusOK:
		return true, nil
	case http.StatusUnauthorized, http.StatusForbidden:
		logger.Infof(nil, "[Kiro] Token invalid (HTTP %d)", resp.StatusCode)
		return false, nil
	default:
		// Unexpected status — treat as potentially valid
		logger.Warningf(nil, "[Kiro] CheckToken unexpected HTTP %d", resp.StatusCode)
		return true, nil
	}
}

// ============================================================================
// Utility
// ============================================================================

// truncateStr truncates a string to maxLen characters.
func truncateStr(s string, maxLen int) string {
	if len(s) <= maxLen {
		return s
	}
	return s[:maxLen] + "..."
}

// readResponseBody reads and returns the response body as a string.
// Used internally for error reporting.
func readResponseBody(resp *http.Response) string {
	if resp == nil || resp.Body == nil {
		return ""
	}
	defer resp.Body.Close()
	body, err := io.ReadAll(resp.Body)
	if err != nil {
		return ""
	}
	return strings.TrimSpace(string(body))
}
