package cursor

import (
	"bytes"
	"crypto/sha1"
	"encoding/base64"
	"encoding/hex"
	"encoding/json"
	"fmt"
	"math/rand"
	"net/http"
	"strings"
	"time"

	"kiro2api/internal/model"
)

// ============================================================================
// JWT Decoding
// ============================================================================

// DecodeCursorJwt decodes a Cursor JWT token and extracts the payload claims.
// Symbol: kiro2api/internal/logic/cursor.DecodeCursorJwt (1024B @ 0x17fe2a0)
//
// The 1024B size indicates base64 decoding + JSON parsing of the JWT payload.
// Cursor uses WorkOS-issued JWTs for authentication.
//
// JWT structure: header.payload.signature
// We only need the payload (middle part) to extract claims like:
//   - sub: user ID
//   - exp: expiration timestamp
//   - iat: issued at timestamp
//   - org_id: organization ID
func DecodeCursorJwt(token string) (map[string]interface{}, error) {
	parts := strings.Split(token, ".")
	if len(parts) != 3 {
		return nil, fmt.Errorf("invalid JWT format: expected 3 parts, got %d", len(parts))
	}

	// Decode the payload (second part)
	payload := parts[1]

	// Add padding if needed (JWT uses base64url without padding)
	switch len(payload) % 4 {
	case 2:
		payload += "=="
	case 3:
		payload += "="
	}

	// Replace URL-safe characters
	payload = strings.ReplaceAll(payload, "-", "+")
	payload = strings.ReplaceAll(payload, "_", "/")

	decoded, err := base64.StdEncoding.DecodeString(payload)
	if err != nil {
		return nil, fmt.Errorf("failed to decode JWT payload: %w", err)
	}

	var claims map[string]interface{}
	if err := json.Unmarshal(decoded, &claims); err != nil {
		return nil, fmt.Errorf("failed to parse JWT claims: %w", err)
	}

	return claims, nil
}

// IsTokenExpired checks if a JWT token has expired.
// Symbol: kiro2api/internal/logic/cursor.IsTokenExpired (256B @ 0x17fe6a0)
func IsTokenExpired(token string) bool {
	claims, err := DecodeCursorJwt(token)
	if err != nil {
		return true
	}

	exp, ok := claims["exp"].(float64)
	if !ok {
		return true
	}

	// Check if token expires within the next 5 minutes (buffer)
	return time.Now().Unix() > int64(exp)-300
}

// ExtractUserIDFromToken extracts the user ID (sub claim) from a JWT token.
// Symbol: kiro2api/internal/logic/cursor.ExtractUserIDFromToken (192B @ 0x17fe7a0)
func ExtractUserIDFromToken(token string) string {
	claims, err := DecodeCursorJwt(token)
	if err != nil {
		return ""
	}

	sub, ok := claims["sub"].(string)
	if !ok {
		return ""
	}
	return sub
}

// ============================================================================
// Key Generation
// ============================================================================

// generateCursorKey generates a random alphanumeric key string.
// Symbol: kiro2api/internal/logic/cursor.generateCursorKey (320B @ 0x17fe8a0)
//
// Used for generating unique identifiers like tool call IDs and request IDs.
// The 320B size suggests a simple random string generator with a fixed charset.
func generateCursorKey() string {
	const charset = "abcdefghijklmnopqrstuvwxyz0123456789"
	const keyLen = 12

	rng := rand.New(rand.NewSource(time.Now().UnixNano()))
	result := make([]byte, keyLen)
	for i := range result {
		result[i] = charset[rng.Intn(len(charset))]
	}
	return string(result)
}

// generateMachineID generates a machine ID string for Cursor requests.
// Symbol: kiro2api/internal/logic/cursor.generateMachineID (448B @ 0x17fea00)
//
// Machine IDs are used by Cursor for device identification and rate limiting.
// Format: hex string of SHA-1 hash of random data.
func generateMachineID() string {
	rng := rand.New(rand.NewSource(time.Now().UnixNano()))
	data := make([]byte, 32)
	for i := range data {
		data[i] = byte(rng.Intn(256))
	}
	return sha1Hash(string(data))
}

// ============================================================================
// Hashing
// ============================================================================

// sha1Hash computes the SHA-1 hash of the input string and returns it as a hex string.
// Symbol: kiro2api/internal/logic/cursor.sha1Hash (192B @ 0x17feb80)
func sha1Hash(input string) string {
	h := sha1.New()
	h.Write([]byte(input))
	return hex.EncodeToString(h.Sum(nil))
}

// ============================================================================
// Proxy URL
// ============================================================================

// getCursorProxyURL returns the proxy URL configured for a Cursor account.
// Symbol: kiro2api/internal/logic/cursor.getCursorProxyURL (128B @ 0x17fec60)
//
// The small size (128B) indicates a simple field accessor with nil check.
func getCursorProxyURL(account *model.CursorAccount) string {
	if account == nil {
		return ""
	}
	return account.ProxyURL
}

// ============================================================================
// WorkOS Token Refresh
// ============================================================================

// refreshWorkOSToken refreshes the WorkOS access token using the refresh token.
// Symbol: kiro2api/internal/logic/cursor.refreshWorkOSToken (2048B @ 0x17fed00)
//
// WorkOS is Cursor's authentication provider. The refresh flow:
//  1. POST to WorkOS token endpoint with refresh_token grant
//  2. Parse response for new access_token and refresh_token
//  3. Update account credentials
//
// The 2048B size indicates HTTP request construction + JSON response parsing.
func (s *sCursor) refreshWorkOSToken(account *model.CursorAccount) error {
	if account.RefreshToken == "" {
		return fmt.Errorf("no refresh token available for account %d", account.ID)
	}

	// WorkOS token endpoint
	// From binary string: "https://api.workos.com/user_management/authenticate"
	tokenURL := "https://api.workos.com/user_management/authenticate"

	client := NewCursorAPIClient()

	// Build refresh request body
	reqBody := map[string]string{
		"grant_type":    "refresh_token",
		"refresh_token": account.RefreshToken,
		"client_id":     account.ClientID,
	}

	bodyBytes, err := json.Marshal(reqBody)
	if err != nil {
		return fmt.Errorf("failed to marshal refresh request: %w", err)
	}

	req, err := newHTTPRequest("POST", tokenURL, bodyBytes)
	if err != nil {
		return fmt.Errorf("failed to create refresh request: %w", err)
	}
	req.Header.Set("Content-Type", "application/json")

	resp, err := client.Do(req)
	if err != nil {
		return fmt.Errorf("refresh token request failed: %w", err)
	}
	defer resp.Body.Close()

	if resp.StatusCode != 200 {
		return fmt.Errorf("refresh token failed with status %d", resp.StatusCode)
	}

	var tokenResp struct {
		AccessToken  string `json:"access_token"`
		RefreshToken string `json:"refresh_token"`
		ExpiresIn    int    `json:"expires_in"`
	}

	if err := json.NewDecoder(resp.Body).Decode(&tokenResp); err != nil {
		return fmt.Errorf("failed to parse refresh response: %w", err)
	}

	// Update account credentials
	account.AccessToken = tokenResp.AccessToken
	if tokenResp.RefreshToken != "" {
		account.RefreshToken = tokenResp.RefreshToken
	}

	// Set expiry with 5-minute buffer
	expiryDuration := time.Duration(tokenResp.ExpiresIn)*time.Second - 5*time.Minute
	account.TokenExpiresAt = time.Now().Add(expiryDuration)

	return nil
}

// newHTTPRequest creates a new HTTP request with the given body.
func newHTTPRequest(method, url string, body []byte) (*http.Request, error) {
	return http.NewRequest(method, url, bytes.NewReader(body))
}

// ============================================================================
// Account Validation
// ============================================================================

// validateCursorAccount checks if a Cursor account has valid credentials.
// Symbol: kiro2api/internal/logic/cursor.validateCursorAccount (384B @ 0x17ff200)
func validateCursorAccount(account *model.CursorAccount) bool {
	if account == nil {
		return false
	}
	if account.AccessToken == "" {
		return false
	}
	if IsTokenExpired(account.AccessToken) {
		return false
	}
	return true
}

// ============================================================================
// Session ID Extraction
// ============================================================================

// ExtractSessionId extracts a session identifier from the request body.
// Symbol: kiro2api/internal/logic/cursor.ExtractSessionId (544B @ 0x17ff380)
//
// Looks for a session/conversation ID in the request JSON to enable
// session affinity (routing subsequent requests to the same account).
func ExtractSessionId(body []byte) string {
	var req struct {
		SessionID      string `json:"session_id"`
		ConversationID string `json:"conversation_id"`
	}
	if err := json.Unmarshal(body, &req); err != nil {
		return ""
	}

	if req.SessionID != "" {
		return req.SessionID
	}
	return req.ConversationID
}
