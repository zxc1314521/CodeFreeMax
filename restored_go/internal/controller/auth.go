package controller

import (
	"context"
	"crypto/rand"
	"encoding/hex"
	"log"
	"sync"
	"time"

	"kiro2api/internal/dao"

	"github.com/gogf/gf/v2/net/ghttp"
)

// Simple in-memory token store
var (
	authTokens = make(map[string]time.Time)
	tokenMu    sync.RWMutex
	adminPass  = "admin123" // default password, overridden by DB value
	apiKey     = ""         // API key for /v1 endpoints, empty = no auth
	apiKeyMu   sync.RWMutex
)

// LoadAuthConfig loads admin_password and api_key from the database.
// Call this after DB is initialized.
func LoadAuthConfig() {
	ctx := context.Background()
	if pw, err := dao.ConfigDaoGet(ctx, "admin_password"); err == nil && pw != "" {
		adminPass = pw
		log.Println("[Auth] Admin password loaded from database")
	}
	apiKeyMu.Lock()
	if ak, err := dao.ConfigDaoGet(ctx, "api_key"); err == nil && ak != "" {
		apiKey = ak
		log.Println("[Auth] API key loaded from database")
	}
	apiKeyMu.Unlock()
}

// UpdateAdminPass updates the in-memory admin password (called after config save).
func UpdateAdminPass(newPass string) {
	if newPass != "" {
		log.Printf("[Auth] UpdateAdminPass: old=%q new=%q", adminPass, newPass)
		adminPass = newPass
	}
}

// GetAdminPass returns the current in-memory admin password (for debugging).
func GetAdminPass() string {
	return adminPass
}

// UpdateApiKey updates the in-memory API key (called after config save).
func UpdateApiKey(newKey string) {
	apiKeyMu.Lock()
	apiKey = newKey
	apiKeyMu.Unlock()
}

// GetApiKey returns the current API key.
func GetApiKey() string {
	apiKeyMu.RLock()
	defer apiKeyMu.RUnlock()
	return apiKey
}

type AuthController struct{}

func (c *AuthController) Login(r *ghttp.Request) {
	var req struct {
		Password string `json:"password"`
	}
	if err := r.Parse(&req); err != nil {
		r.Response.WriteJsonExit(map[string]interface{}{
			"code":    1,
			"message": "参数错误",
		})
	}

	log.Printf("[Auth] Login attempt: input=%q stored=%q match=%v", req.Password, adminPass, req.Password == adminPass)

	if req.Password != adminPass {
		r.Response.WriteJsonExit(map[string]interface{}{
			"code":    1,
			"message": "密码错误",
		})
	}

	// Generate token
	b := make([]byte, 32)
	rand.Read(b)
	token := hex.EncodeToString(b)
	expiresAt := time.Now().Add(24 * time.Hour)

	tokenMu.Lock()
	authTokens[token] = expiresAt
	tokenMu.Unlock()

	r.Response.WriteJsonExit(map[string]interface{}{
		"code": 0,
		"data": map[string]interface{}{
			"token":     token,
			"expiresAt": expiresAt.Format(time.RFC3339),
		},
	})
}

func (c *AuthController) Logout(r *ghttp.Request) {
	token := r.GetHeader("X-Auth-Token")
	if token != "" {
		tokenMu.Lock()
		delete(authTokens, token)
		tokenMu.Unlock()
	}
	r.Response.WriteJsonExit(map[string]interface{}{
		"code": 0,
	})
}

// AuthMiddleware checks X-Auth-Token header
func AuthMiddleware(r *ghttp.Request) {
	token := r.GetHeader("X-Auth-Token")
	if token == "" {
		r.Response.Status = 401
		r.Response.WriteJsonExit(map[string]interface{}{
			"code":    401,
			"message": "未认证",
		})
	}

	tokenMu.RLock()
	exp, ok := authTokens[token]
	tokenMu.RUnlock()

	if !ok || time.Now().After(exp) {
		tokenMu.Lock()
		delete(authTokens, token)
		tokenMu.Unlock()
		r.Response.Status = 401
		r.Response.WriteJsonExit(map[string]interface{}{
			"code":    401,
			"message": "认证已过期",
		})
	}

	r.Middleware.Next()
}

// ApiKeyMiddleware checks Authorization: Bearer <key> header for /v1 endpoints.
// If no API key is configured, all requests are allowed.
func ApiKeyMiddleware(r *ghttp.Request) {
	key := GetApiKey()
	if key == "" {
		// No API key configured, skip auth
		r.Middleware.Next()
		return
	}

	auth := r.GetHeader("Authorization")
	if auth == "" {
		r.Response.Status = 401
		r.Response.WriteJsonExit(map[string]interface{}{
			"error": map[string]interface{}{
				"message": "Missing Authorization header. Expected: Bearer <api_key>",
				"type":    "authentication_error",
			},
		})
	}

	// Extract Bearer token
	const prefix = "Bearer "
	if len(auth) <= len(prefix) || auth[:len(prefix)] != prefix {
		r.Response.Status = 401
		r.Response.WriteJsonExit(map[string]interface{}{
			"error": map[string]interface{}{
				"message": "Invalid Authorization header format. Expected: Bearer <api_key>",
				"type":    "authentication_error",
			},
		})
	}

	token := auth[len(prefix):]
	if token != key {
		r.Response.Status = 401
		r.Response.WriteJsonExit(map[string]interface{}{
			"error": map[string]interface{}{
				"message": "Invalid API key",
				"type":    "authentication_error",
			},
		})
	}

	r.Middleware.Next()
}
