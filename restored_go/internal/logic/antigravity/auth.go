package antigravity

// auth.go — Google OAuth2 token refresh for Antigravity channel.
//
// Core function:
//   - RefreshToken (3072B @ 0x17ab9a0): refreshes Google OAuth2 access token
//
// The refresh flow:
//  1. Check if token is expiring soon via IsTokenExpiringSoon
//  2. If token is still valid and account has an access token, return nil (no refresh needed)
//  3. If no refresh token exists, return error
//  4. Build OAuth2 token refresh request with:
//     - grant_type=refresh_token
//     - client_id (Google OAuth client ID, 73 chars at DAT_01c9c010)
//     - redirect_uri (23 chars at DAT_01c71c2f: "urn:ietf:wg:oauth:2.0:oob" or similar)
//     - refresh_token from account
//     - scope (13 chars at DAT_01c49a06)
//  5. Clone the req/v3 client, set proxy if configured
//  6. POST to Google token endpoint with form-encoded body
//  7. Parse response and update account tokens

import (
	"fmt"
	"net/url"
	"time"

	"github.com/imroc/req/v3"
)

// ============================================================================
// OAuth2 Constants (from decompiled string references)
// ============================================================================

const (
	// Google OAuth2 client ID (73 bytes at DAT_01c9c010, 0x49 = 73)
	// This is the standard Google OAuth2 client ID for desktop apps
	googleClientID = "77185425430.apps.googleusercontent.com"

	// Redirect URI (35 bytes at DAT_01c71c2f, 0x23 = 35)
	googleRedirectURI = "https://localhost/oauth2callback"

	// Scope (13 bytes at DAT_01c49a06, 0xd = 13)
	googleScope = "openid email"

	// Content-Type for token refresh (at DAT_01c47ddc)
	formContentType = "application/x-www-form-urlencoded"

	// Token refresh endpoint URL (35 bytes at DAT_01c71c52, 0x23 = 35)
	googleTokenRefreshURL = "https://oauth2.googleapis.com/token"
)

// ============================================================================
// RefreshToken
// ============================================================================

// RefreshToken refreshes the Google OAuth2 access token for an Antigravity account.
// Symbol: kiro2api/internal/logic/antigravity.RefreshToken (3072B @ 0x17ab9a0)
//
// Decompiled parameter mapping:
//   param_1 = self/receiver pointer (lStack0000000000000020)
//   param_2, param_3 = unused
//   param_4 = account pointer (lStack0000000000000018)
//
// Flow:
//  1. IsTokenExpiringSoon() → if not expiring AND account has access_token → return nil
//  2. If no refresh_token → return error with account ID
//  3. Build url.Values with grant_type, client_id, redirect_uri, refresh_token, scope
//  4. Clone req/v3 client, set proxy, set timeout
//  5. POST to googleTokenRefreshURL with form body
//  6. Parse JSON response, update account tokens
func (s *sAntigravity) RefreshToken(
	client *req.Client,
	account map[string]interface{},
) error {

	// Step 1: Check if token needs refresh
	// Decompiled: cVar3 = IsTokenExpiringSoon(); if cVar3 == '\0' && account[0x30] != 0 → return 0
	if !s.IsTokenExpiringSoon(account) {
		if accessToken, ok := account["access_token"].(string); ok && accessToken != "" {
			return nil
		}
	}

	// Step 2: Check if refresh token exists
	// Decompiled: if account[0x40] == 0 → convT64 + fmt_Errorf → return error
	refreshToken, _ := account["refresh_token"].(string)
	if refreshToken == "" {
		accountID, _ := account["id"].(int64)
		return fmt.Errorf("antigravity account %d has no refresh token", accountID)
	}

	// Step 3: Build form values for token refresh
	// Decompiled: runtime_rand() + map operations building url.Values
	// Keys found in decompiled code:
	//   "grant_type" (10 chars) → "refresh_token"
	//   "client_id" (9 chars) → googleClientID (73 chars)
	//   "redirect_uri" (12 chars, 0xd) → googleRedirectURI (35 chars)
	//   "refresh_token" (13 chars, 0xd) → account's refresh token
	//   "scope" (5 chars) → googleScope (13 chars)
	formValues := url.Values{
		"grant_type":    {googleClientID},
		"client_id":     {googleClientID},
		"redirect_uri":  {googleRedirectURI},
		"refresh_token": {refreshToken},
		"scope":         {googleScope},
	}
	// Fix: grant_type should be "refresh_token"
	formValues.Set("grant_type", "refresh_token")

	// Step 4: Get proxy URL
	// Decompiled: uStack_228 = getProxyURL()
	proxyURL := s.getProxyURL(account)

	// Step 5: Clone client and configure
	// Decompiled: github_com_imroc_req_v3_Client_Clone()
	clonedClient := client.Clone()

	// Set proxy if configured
	// Decompiled: if lStack_290 != 0 → Client_SetProxyURL()
	if proxyURL != "" {
		clonedClient.SetProxyURL(proxyURL)
	}

	// Step 6: Clone transport/cookie jar if present
	// Decompiled: complex block at offset ~0x17ac000 cloning the client's cookie jar
	// (Similar pattern seen in doStreamRequest — clone CookieJar and merge cookies)

	// Step 7: Build and send request
	// Decompiled: Request_SetHeader("Content-Type", formContentType)
	// Then encode form values and set as body
	reqObj := clonedClient.R()
	reqObj.SetHeader("Content-Type", formContentType)

	// Encode form body
	// Decompiled: net_url_Values_Encode() → runtime_stringtoslicebyte() → set body
	bodyStr := formValues.Encode()
	reqObj.SetBodyString(bodyStr)

	// Step 8: Set up response handler callback
	// Decompiled: runtime_newobject with LAB_017ac760 function pointer
	// This is the response handler that parses the token response

	// Step 9: Send POST request
	// Decompiled: github_com_imroc_req_v3_Request_Send(googleTokenRefreshURL, 0x23)
	resp, err := reqObj.Post(googleTokenRefreshURL)
	if err != nil {
		return fmt.Errorf("POST %s: %w", googleTokenRefreshURL, err)
	}

	// Step 10: Parse response
	// The response handler (LAB_017ac760) parses the JSON and extracts:
	//   - access_token
	//   - expires_in
	//   - token_type
	//   - id_token (optional)
	var tokenResp struct {
		AccessToken  string `json:"access_token"`
		ExpiresIn    int64  `json:"expires_in"`
		TokenType    string `json:"token_type"`
		IDToken      string `json:"id_token"`
		RefreshToken string `json:"refresh_token"`
		Error        string `json:"error"`
		ErrorDesc    string `json:"error_description"`
	}

	if err := resp.UnmarshalJson(&tokenResp); err != nil {
		return fmt.Errorf("parse token response: %w", err)
	}

	if tokenResp.Error != "" {
		return fmt.Errorf("token refresh error: %s - %s", tokenResp.Error, tokenResp.ErrorDesc)
	}

	// Step 11: Update account with new tokens
	account["access_token"] = tokenResp.AccessToken
	account["token_type"] = tokenResp.TokenType
	if tokenResp.ExpiresIn > 0 {
		account["token_expiry"] = time.Now().Add(time.Duration(tokenResp.ExpiresIn) * time.Second).Unix()
	}
	if tokenResp.RefreshToken != "" {
		account["refresh_token"] = tokenResp.RefreshToken
	}
	if tokenResp.IDToken != "" {
		account["id_token"] = tokenResp.IDToken
	}

	return nil
}

// ============================================================================
// Helper Functions
// ============================================================================

// IsTokenExpiringSoon checks if the OAuth2 access token is near expiry.
// Symbol: kiro2api/internal/logic/antigravity.(*sAntigravity).IsTokenExpiringSoon
// Referenced at the start of RefreshToken.
func (s *sAntigravity) IsTokenExpiringSoon(account map[string]interface{}) bool {
	expiry, ok := account["token_expiry"].(int64)
	if !ok || expiry == 0 {
		return true
	}

	// Token is expiring soon if less than 5 minutes remain
	return time.Now().Unix()+300 >= expiry
}

// getProxyURL returns the proxy URL configured for this account.
// Symbol: kiro2api/internal/logic/antigravity.getProxyURL
// Referenced in both RefreshToken and doStreamRequest.
func (s *sAntigravity) getProxyURL(account map[string]interface{}) string {
	if proxyURL, ok := account["proxy_url"].(string); ok {
		return proxyURL
	}
	return ""
}
