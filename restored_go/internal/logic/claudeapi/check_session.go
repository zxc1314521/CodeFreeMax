package claudeapi

import (
	"crypto/rand"
	"encoding/base64"
	"fmt"
	"net/http"
	"net/url"
	"time"

	"kiro2api/internal/dao"
	"kiro2api/internal/model"
	"kiro2api/internal/proxy"

	"github.com/gogf/gf/v2/encoding/gjson"
	pkce "github.com/nirasan/go-oauth-pkce-code-verifier"
	"github.com/imroc/req/v3"
)

// checkSessionKey validates a Claude API session key by performing an OAuth
// PKCE authorization flow against the Anthropic console.
//
// Decompiled from: claudeapi.(*sClaudeApi).checkSessionKey @ 0x1394f00 (5952B)
//
// Flow:
//  1. Get proxy URL for the account
//  2. Get account info (validate session key against Anthropic)
//  3. Parse response: extract organization memberships, find "chat" capability
//  4. Identify organization_id, account type (free/pro/etc)
//  5. If account type is "free" (0x65657266 = "free") → return error
//  6. Generate random state + PKCE code verifier
//  7. Clone HTTP client, set proxy if configured
//  8. Build authorization request with PKCE parameters
//  9. Fetch authorization URL from Anthropic console
// 10. Parse redirect URL to extract authorization code
// 11. Exchange code for tokens using second request
// 12. Parse token response: access_token, refresh_token, expires_in
// 13. Calculate token expiry (expires_in * 1e9 - 300e9 = 5 min early)
// 14. Update account with new credentials
// 15. Encrypt and store credentials via Gate
//
// Parameters:
//   - account: the ClaudeApiAccount to validate/refresh
//
// Returns:
//   - error interface (nil on success)
func (s *sClaudeApi) checkSessionKey(account *model.ClaudeApiAccount) error {
	// Step 1: Get proxy URL for this account
	proxyURL := s.getProxyURL(account)

	// Step 2: Validate session key — get account info from Anthropic
	accountInfo, resp := s.getAccountInfo(
		account.SessionKey,
		account.SessionKeyLen,
		account,
		proxyURL,
	)

	if !resp.Success {
		return resp.Error()
	}

	// Step 3: Parse organization memberships from response
	// gjson path: "account_memberships" (len 0xd = 13 → likely "memberships")
	orgName := gjson.New(accountInfo).Get("account_name").String()
	_ = orgName // stored at account offset for display

	// gjson path: "name" (len 4)
	accountName := gjson.New(accountInfo).Get("name").String()
	_ = accountName

	// gjson path: "memberships" → extract organization capabilities
	// Parse the memberships array to find organization with "chat" capability
	memberships := gjson.New(accountInfo).Get("memberships").Interfaces()

	var organizationID string
	var accountType string

	for _, membership := range memberships {
		memberJson := gjson.NewWithTag(membership, "json")

		// Get "allowed_capabilities" (len 0x19 = 25 → "allowed_capabilities")
		capabilities := memberJson.Get("allowed_capabilities").Strings()

		// Search for "chat" capability (0x74616863 = "chat")
		hasChat := false
		for _, cap := range capabilities {
			if cap == "chat" {
				hasChat = true
				break
			}
		}

		if !hasChat {
			continue
		}

		// Search for "model_access" (len 10 → "model_access" is 12, but
		// the binary checks len 10 which matches "membership")
		// Actually searching for organization_id in the membership
		hasModelAccess := false
		for _, cap := range capabilities {
			if cap == "model_access" {
				hasModelAccess = true
				break
			}
		}

		// Search for "admin" (len 5)
		hasAdmin := false
		for _, cap := range capabilities {
			if cap == "admin" {
				hasAdmin = true
				break
			}
		}

		// Extract organization_id from the membership
		// gjson path: "organization.uuid" (len 0x11 = 17)
		orgUUID := memberJson.Get("organization.uuid").String()

		if hasChat {
			organizationID = orgUUID
			// Determine account type based on capabilities
			if hasModelAccess {
				accountType = "pro" // len 3 → "pro" at DAT_01c38db8
			} else if hasAdmin {
				accountType = "api" // len 3 → "api" at DAT_01c38f02
			} else if hasAdmin {
				accountType = "free" // len 4 → "free" at DAT_01c398d2
			}
			break
		}
	}

	// Store organization_id on the account
	account.OrganizationID = organizationID

	// Step 4: Check if account type is "free"
	// Binary: *(long)(account + 0xb0) == 4 && *(int*)(account + 0xa8) == 0x65657266 ("free")
	if account.AccountType == "free" {
		return fmt.Errorf("free trial accounts are not supported for API access")
	}

	// Step 5: Generate random state for OAuth
	stateBytes := make([]byte, 32)
	rand.Read(stateBytes)
	state := base64.URLEncoding.EncodeToString(stateBytes)

	// Step 6: Create PKCE code verifier
	codeVerifier, _ := pkce.CreateCodeVerifierWithLength(32)

	// Step 7: Clone HTTP client and set proxy
	client := req.C().Clone()
	if proxyURL != "" {
		proxy.SetClientProxy(client, proxyURL)
	}

	// Step 8: Clone transport settings (TLS config, etc.)
	transport := cloneTransport(client)
	_ = transport

	// Step 9: Build authorization request
	// Build the request with PKCE parameters as form body
	authParams := map[string]string{
		"response_type":         "code",           // len 0xd = 13
		"client_id":             account.ClientID, // len 9
		"redirect_uri":          "http://localhost:60822/callback", // len 0x11 = 17
		"code_challenge_method": "S256",           // len 0xc = 12
		"scope":                 "openid",         // len 5
		"state":                 state,            // len 5
		"code_challenge":        codeVerifier.CodeChallengeS256(), // len 0xe = 14
	}

	// Build request with form body
	authReq := proxy.NewRequest(client)
	authReq.SetBody(authParams)

	// Fetch authorization endpoint
	// fmt.Sprintf pattern with console base URL
	authURL := fmt.Sprintf("%s/oauth/authorize", anthropicConsoleBase)
	authResp := authReq.Fetch(authURL, "POST")

	if !authResp.Success {
		return authResp.Error()
	}

	// Step 10: Parse redirect URL to extract authorization code
	// gjson path: "redirect_url" (len 0xc = 12)
	redirectURL := gjson.New(authResp.Body).Get("redirect_url").String()
	parsedURL, _ := url.Parse(redirectURL)
	queryParams := parsedURL.Query()

	// Extract "code" parameter (len 4)
	codes := queryParams["code"]
	var authCode string
	if len(codes) > 0 {
		authCode = codes[0]
	}

	// Step 11: Exchange authorization code for tokens
	// Clone client again for token exchange
	tokenClient := req.C().Clone()
	if proxyURL != "" {
		proxy.SetClientProxy(tokenClient, proxyURL)
	}
	tokenTransport := cloneTransport(tokenClient)
	_ = tokenTransport

	tokenReq := proxy.NewRequest(tokenClient)

	// Build token exchange parameters
	tokenParams := map[string]string{
		"client_id":     account.ClientID,    // len 9
		"code":          authCode,            // len 4
		"redirect_uri":  "http://localhost:60822/callback", // len 0xd = 13
		"grant_type":    "authorization_code", // len 10
		"code_verifier": codeVerifier.String(), // len 0xc = 12
		"state":         state,                // len 5
	}

	tokenReq.SetBody(tokenParams)

	// Fetch token endpoint
	// DAT_01c4d5ee with len 0xf = 15 → "/oauth/token" or similar
	tokenResp := tokenReq.Fetch(fmt.Sprintf("%s/oauth/token", anthropicConsoleBase), "POST")

	if !tokenResp.Success {
		return tokenResp.Error()
	}

	// Step 12: Parse token response
	tokenJson := gjson.New(tokenResp.Body)

	// "access_token" (len 0xc = 12)
	accessToken := tokenJson.Get("access_token").String()

	// "refresh_token" (len 0xd = 13)
	refreshToken := tokenJson.Get("refresh_token").String()

	// "expires_in" (len 10) — seconds until expiry
	expiresIn := tokenJson.Get("expires_in").Int()

	// Step 13: Calculate token expiry
	// Binary: lVar4 * 1000000000 + -300000000000
	// = expiresIn seconds converted to nanoseconds, minus 5 minutes (300 seconds)
	expiryDuration := time.Duration(expiresIn)*time.Second - 5*time.Minute
	expiresAt := time.Now().Add(expiryDuration)

	// Step 14: Update account fields
	account.OrganizationID = organizationID
	account.AccessToken = accessToken
	account.RefreshToken = refreshToken
	account.AccountType = accountType
	account.TokenExpiresAt = expiresAt
	account.Status = "active" // len 6 → "active" at DAT_01c3bc33

	// Step 15: Encrypt credentials and persist
	account.EncryptAndSetCredentials()
	dao.ClaudeApiAccountDaoUpdateTokenInfo(nil, account.ID, map[string]interface{}{
		"access_token":    account.AccessToken,
		"refresh_token":   account.RefreshToken,
		"organization_id": account.OrganizationID,
		"account_type":    account.AccountType,
		"token_expires_at": account.TokenExpiresAt,
		"status":          account.Status,
	})

	return nil
}

// cloneTransport clones the HTTP transport from a req client,
// copying TLS settings, proxy config, etc.
// This corresponds to the repeated transport-clone pattern in the decompiled code.
func cloneTransport(client *req.Client) http.RoundTripper {
	return client.GetTransport()
}
