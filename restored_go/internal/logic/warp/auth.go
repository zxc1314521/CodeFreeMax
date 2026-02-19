package warp

// auth.go — Firebase Auth token refresh for the Warp channel.
//
// Warp uses Firebase Authentication for user identity. The refresh token
// is exchanged for a new ID token via Google's securetoken API.
//
// From decompiled: warp.RefreshToken @ 0x1712f40 (3072B)
// Key patterns:
//   - POST to https://securetoken.googleapis.com/v1/token?key=<API_KEY>
//   - Body: grant_type=refresh_token&refresh_token=<TOKEN>
//   - Response contains id_token and refresh_token
//   - Uses req/v3 Client.Clone() for isolated requests
//   - Sets proxy URL if configured
//   - Updates account in database after successful refresh

import (
	"context"
	"fmt"
	"net/url"

	"github.com/gogf/gf/v2/frame/gins"
	"github.com/imroc/req/v3"
)

// RefreshToken refreshes the Firebase ID token using the refresh token.
//
// From decompiled: kiro2api_internal_logic_warp_sWarp_RefreshToken
//
// Flow:
//   1. Check refresh token exists
//   2. Build form-encoded body: grant_type=refresh_token&refresh_token=<token>
//   3. Clone HTTP client, set proxy if configured
//   4. POST to Firebase securetoken endpoint
//   5. Parse response for new id_token and refresh_token
//   6. Update account fields and persist to database
//
// The decompiled code shows:
//   - runtime_mapassign_faststr calls for building form data map
//   - Key "grant_type" (10 chars) with value "refresh_token" (13 chars)
//   - Key "refresh_token" (13 chars) with value from account
//   - fmt.Sprintf for building the URL with API key
//   - GetWarpProxyURL() for proxy configuration
//   - Client.Clone() for request isolation
//   - WarpAccountDao.Update() after successful refresh
func (s *sWarp) RefreshToken(account *WarpAccount) error {
	logger := gins.Log()

	if account.RefreshToken == "" {
		return fmt.Errorf("no refresh token available")
	}

	// Build form data
	// From decompiled: map with "grant_type" and "refresh_token" keys
	formData := url.Values{
		"grant_type":    {"refresh_token"},
		"refresh_token": {account.RefreshToken},
	}

	// Build Firebase token URL
	// From decompiled: fmt.Sprintf with API key
	tokenURL := fmt.Sprintf("%s", WarpFirebaseURL)

	// Clone client for isolated request
	// From decompiled: github_com_imroc_req_v3_Client_Clone()
	client := s.client.Clone()

	// Set proxy if configured
	// From decompiled: GetWarpProxyURL() check and SetProxyURL()
	proxyURL := GetWarpProxyURL()
	if proxyURL != "" {
		client.SetProxyURL(proxyURL)
	}

	logger.Debugf(nil, "[Warp] Refreshing Firebase token for %s", account.Email)

	// Send request
	// From decompiled: SetBodyString with form-encoded data
	resp, err := client.R().
		SetHeader(HeaderContentType, "application/x-www-form-urlencoded").
		SetBodyString(formData.Encode()).
		Post(tokenURL)

	if err != nil {
		return fmt.Errorf("firebase token refresh request failed: %w", err)
	}

	if !resp.IsSuccessState() {
		return fmt.Errorf("firebase token refresh failed: HTTP %d: %s",
			resp.StatusCode, resp.String())
	}

	// Parse response
	var tokenResp FirebaseTokenResponse
	if err := resp.UnmarshalJson(&tokenResp); err != nil {
		return fmt.Errorf("parse firebase token response: %w", err)
	}

	// Update account with new tokens
	// From decompiled: field assignments at offsets +0x08 (refresh_token),
	// +0x38 (id_token), then WarpAccountDao.Update()
	account.IDToken = tokenResp.IDToken
	if tokenResp.RefreshToken != "" {
		account.RefreshToken = tokenResp.RefreshToken
	}

	// Persist to database
	// From decompiled: kiro2api_internal_dao_WarpAccountDao_Update()
	if err := updateWarpAccount(context.Background(), account); err != nil {
		logger.Warningf(nil, "[Warp] Failed to update account after token refresh: %v", err)
	}

	logger.Debugf(nil, "[Warp] Firebase token refreshed successfully for %s", account.Email)
	return nil
}

// refreshTokenWithClient refreshes the token using a specific HTTP client.
// Used internally when the main client needs proxy configuration.
func refreshTokenWithClient(client *req.Client, account *WarpAccount) (*FirebaseTokenResponse, error) {
	formData := url.Values{
		"grant_type":    {"refresh_token"},
		"refresh_token": {account.RefreshToken},
	}

	resp, err := client.R().
		SetHeader(HeaderContentType, "application/x-www-form-urlencoded").
		SetBodyString(formData.Encode()).
		Post(WarpFirebaseURL)

	if err != nil {
		return nil, fmt.Errorf("firebase request: %w", err)
	}

	if !resp.IsSuccessState() {
		return nil, fmt.Errorf("firebase HTTP %d: %s", resp.StatusCode, resp.String())
	}

	var tokenResp FirebaseTokenResponse
	if err := resp.UnmarshalJson(&tokenResp); err != nil {
		return nil, fmt.Errorf("parse firebase response: %w", err)
	}

	return &tokenResp, nil
}

// updateWarpAccount persists account changes to the database.
// From decompiled: kiro2api_internal_dao_WarpAccountDao_Update
func updateWarpAccount(ctx context.Context, account *WarpAccount) error {
	// In the original binary, this calls:
	//   kiro2api_internal_dao_WarpAccountDao_Update()
	// which updates the account record in the database.
	//
	// Placeholder — actual DAO implementation is in dao/migrate.go
	_ = ctx
	_ = account
	return nil
}
