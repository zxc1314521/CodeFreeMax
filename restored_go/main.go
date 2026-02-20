package main

import (
	"context"
	"io"
	"log"
	"os"
	"kiro2api/internal/controller"
	"kiro2api/internal/dao"
	"kiro2api/internal/logic/kiro"

	"github.com/gogf/gf/v2/frame/g"
	"github.com/gogf/gf/v2/net/ghttp"
	"github.com/gogf/gf/v2/os/gcmd"
	"github.com/glebarez/sqlite"
	"github.com/imroc/req/v3"
	"gorm.io/gorm"
)

func init() {
	os.MkdirAll("./data", 0755)
	logFile, err := os.OpenFile("./data/kiro2api.log", os.O_CREATE|os.O_WRONLY|os.O_APPEND, 0644)
	if err != nil {
		log.Printf("Failed to open log file: %v", err)
		return
	}
	// Write to both stdout and log file
	mw := io.MultiWriter(os.Stdout, logFile)
	log.SetOutput(mw)
	log.Println("[kiro2api] Log file initialized: ./data/kiro2api.log")
}

var (
	Main = gcmd.Command{
		Name:  "main",
		Usage: "main",
		Brief: "kiro2api - Multi-channel AI API proxy",
		Func: func(ctx context.Context, parser *gcmd.Parser) (err error) {
			s := g.Server()

			// CORS middleware for frontend dev server
			s.Use(func(r *ghttp.Request) {
				r.Response.CORSDefault()
				r.Middleware.Next()
			})

			// Initialize SQLite database
			dbPath := "./data/kiro2api.db"
			if err := os.MkdirAll("./data", 0755); err != nil {
				log.Fatalf("Failed to create data directory: %v", err)
			}
			database, err := gorm.Open(sqlite.Open(dbPath), &gorm.Config{})
			if err != nil {
				log.Fatalf("Failed to open database: %v", err)
			}
			dao.SetDB(database)
			log.Println("[kiro2api] Database initialized:", dbPath)

			// Run migrations
			dao.MigrateTutorialChannels(database)
			dao.MigrateChannelModels(database)
			dao.MigrateChannelAccounts(database)
			dao.MigrateSystemConfig(database)

			// Load accounts from database into memory
			controller.LoadAccountsFromDB()

			// Load auth config (admin password, API key) from database
			controller.LoadAuthConfig()

			// Auth endpoints (no auth middleware)
			authCtrl := &controller.AuthController{}
			s.Group("/api/auth", func(group *ghttp.RouterGroup) {
				group.POST("/login", authCtrl.Login)
				group.POST("/logout", authCtrl.Logout)
				// Temporary debug endpoint — remove after fixing login issue
				group.GET("/debug-password", func(r *ghttp.Request) {
					ctx := r.Context()
					dbPass, _ := dao.ConfigDaoGet(ctx, "admin_password")
					r.Response.WriteJsonExit(map[string]interface{}{
						"code": 0,
						"data": map[string]interface{}{
							"db_password":     dbPass,
							"memory_password": controller.GetAdminPass(),
						},
					})
				})
			})

			// OpenAI-compatible API endpoints (with optional API key auth)
			s.Group("/v1", func(group *ghttp.RouterGroup) {
				group.Middleware(controller.ApiKeyMiddleware)
				group.GET("/models", func(r *ghttp.Request) {
					controller.RegisterModelsRoute(r)
				})
				group.POST("/chat/completions", func(r *ghttp.Request) {
					handleChatCompletions(r)
				})
			})

			// Admin API endpoints (with auth middleware)
			s.Group("/api", func(group *ghttp.RouterGroup) {
				group.Middleware(controller.AuthMiddleware)

				configCtrl := &controller.ConfigController{}
				testCtrl := &controller.TestController{}
				tutorialCtrl := &controller.TutorialController{}
				modelManageCtrl := &controller.ModelManageController{}

				// Stats & version
				group.GET("/stats", controller.GlobalStats)
				group.GET("/version", func(r *ghttp.Request) {
					r.Response.WriteJsonExit(map[string]interface{}{
						"code": 0,
						"data": map[string]interface{}{
							"version": "1.0.0",
						},
					})
				})

				// Config
				group.POST("/config/save", configCtrl.Save)
				group.GET("/config/list", configCtrl.List)

				// Tutorial channels
				group.GET("/tutorial/channels", tutorialCtrl.List)
				group.POST("/tutorial/channels/save", tutorialCtrl.Save)
				group.POST("/tutorial/channels/delete", tutorialCtrl.Delete)

				// Model management
				group.GET("/models/list", modelManageCtrl.List)
				group.POST("/models/save", modelManageCtrl.Save)
				group.POST("/models/delete", modelManageCtrl.Delete)
				group.POST("/models/toggle", modelManageCtrl.Toggle)

				// Test
				group.POST("/test", testCtrl.Test)

				// Per-channel account routes
				controller.RegisterChannelRoutes(group)

				// Kiro model queue config
				group.GET("/kiro/model-queue-config", func(r *ghttp.Request) {
					r.Response.WriteJsonExit(map[string]interface{}{
						"code": 0,
						"data": map[string]interface{}{
							"queues": []map[string]interface{}{},
						},
					})
				})
				group.POST("/kiro/model-queue-config", func(r *ghttp.Request) {
					r.Response.WriteJsonExit(map[string]interface{}{"code": 0, "message": "保存成功"})
				})

				// Grok config
				group.GET("/grok/config", func(r *ghttp.Request) {
					r.Response.WriteJsonExit(map[string]interface{}{
						"code": 0,
						"data": map[string]interface{}{
							"nsfw_enabled":    false,
							"cache_enabled":   true,
							"cache_ttl":       3600,
							"max_retry":       3,
							"request_timeout": 60,
						},
					})
				})
				group.POST("/grok/config/save", func(r *ghttp.Request) {
					r.Response.WriteJsonExit(map[string]interface{}{"code": 0, "message": "保存成功"})
				})

				// Grok account batch operations
				group.POST("/grok/account/nsfw-batch", func(r *ghttp.Request) {
					r.Response.WriteJsonExit(map[string]interface{}{"code": 0, "data": map[string]interface{}{"updated": 0}})
				})
				group.POST("/grok/account/clear-assets-batch", func(r *ghttp.Request) {
					r.Response.WriteJsonExit(map[string]interface{}{"code": 0, "data": map[string]interface{}{"cleared": 0}})
				})

				// Grok cache management
				group.GET("/grok/cache/stats", func(r *ghttp.Request) {
					r.Response.WriteJsonExit(map[string]interface{}{
						"code": 0,
						"data": map[string]interface{}{"total": 0, "size": "0 B", "hit_rate": 0},
					})
				})
				group.GET("/grok/cache/list", func(r *ghttp.Request) {
					r.Response.WriteJsonExit(map[string]interface{}{
						"code": 0,
						"data": map[string]interface{}{"list": []interface{}{}, "total": 0},
					})
				})
				group.POST("/grok/cache/delete", func(r *ghttp.Request) {
					r.Response.WriteJsonExit(map[string]interface{}{"code": 0, "message": "删除成功"})
				})
				group.POST("/grok/cache/clear", func(r *ghttp.Request) {
					r.Response.WriteJsonExit(map[string]interface{}{"code": 0, "message": "清除成功"})
				})

				// License (stub)
				group.GET("/license/status", func(r *ghttp.Request) {
					r.Response.WriteJsonExit(map[string]interface{}{
						"code": 0,
						"data": map[string]interface{}{
							"status":  "active",
							"plan":    "pro",
							"expires": "2099-12-31",
						},
					})
				})
				group.GET("/license/usage", func(r *ghttp.Request) {
					r.Response.WriteJsonExit(map[string]interface{}{
						"code": 0,
						"data": map[string]interface{}{"used": 0, "limit": 999999},
					})
				})
				group.POST("/license/save", func(r *ghttp.Request) {
					r.Response.WriteJsonExit(map[string]interface{}{"code": 0, "message": "保存成功"})
				})

				// Token cache (stub)
				group.GET("/token-cache/stats", func(r *ghttp.Request) {
					r.Response.WriteJsonExit(map[string]interface{}{"code": 0, "data": map[string]interface{}{"count": 0, "size": 0}})
				})
				group.POST("/token-cache/clear", func(r *ghttp.Request) {
					r.Response.WriteJsonExit(map[string]interface{}{"code": 0, "message": "清除成功"})
				})
			})

			// Antigravity OAuth (outside /api group, no auth required for OAuth flow)
			antigravityOAuth := &controller.ChannelAccountController{}
			s.Group("/oauth/antigravity", func(group *ghttp.RouterGroup) {
				group.POST("/authorize", antigravityOAuth.OAuthAuthorize)
				group.GET("/status", antigravityOAuth.OAuthStatus)
			})

			// Per-channel model listing: /{channel}/v1/models
			channelModels := []string{"kiro", "orchids", "antigravity", "cursor", "warp", "claude_api", "grok"}
			for _, ch := range channelModels {
				chName := ch
				s.BindHandler("/"+chName+"/v1/models", func(r *ghttp.Request) {
					controller.RegisterChannelModelsRoute(r, chName)
				})
			}

			// Health check
			s.BindHandler("/health", func(r *ghttp.Request) {
				r.Response.WriteJson(map[string]interface{}{
					"status": "ok",
					"name":   "kiro2api",
				})
			})

			log.Println("[kiro2api] Server starting...")
			s.Run()
			return nil
		},
	}
)

// handleChatCompletions routes chat completion requests to the appropriate channel.
// Currently routes all requests to the Kiro channel with round-robin account selection.
func handleChatCompletions(r *ghttp.Request) {
	// Parse the request body into a generic map for the kiro logic layer
	var chatReq map[string]interface{}
	if err := r.Parse(&chatReq); err != nil {
		r.Response.WriteJson(map[string]interface{}{
			"error": map[string]interface{}{
				"message": "invalid request: " + err.Error(),
				"type":    "invalid_request_error",
			},
		})
		return
	}

	// Select next available kiro account via round-robin
	account, err := controller.GetNextKiroAccount()
	if err != nil {
		r.Response.WriteJson(map[string]interface{}{
			"error": map[string]interface{}{
				"message": "no available accounts: " + err.Error(),
				"type":    "server_error",
			},
		})
		return
	}

	// Create HTTP client
	client := req.C()

	// Refresh token if needed
	kiroSvc := kiro.New()
	if refreshErr := kiroSvc.RefreshToken(client, account); refreshErr != nil {
		log.Printf("[kiro2api] Token refresh failed for account %v: %v", account["id"], refreshErr)
		controller.MarkKiroAccountError(account, "token refresh failed: "+refreshErr.Error())
		r.Response.WriteJson(map[string]interface{}{
			"error": map[string]interface{}{
				"message": "token refresh failed: " + refreshErr.Error(),
				"type":    "authentication_error",
			},
		})
		return
	}

	// Write refreshed tokens back to in-memory store
	controller.UpdateKiroAccountTokens(account)

	// Set SSE headers on the raw writer to bypass GoFrame buffering
	rawWriter := r.Response.RawWriter()
	rawWriter.Header().Set("Content-Type", "text/event-stream")
	rawWriter.Header().Set("Cache-Control", "no-cache")
	rawWriter.Header().Set("Connection", "keep-alive")

	// Call kiro ChatCompletions
	if err := kiroSvc.ChatCompletions(r.Context(), rawWriter, chatReq, account, client); err != nil {
		log.Printf("[kiro2api] ChatCompletions error for account %v: %v", account["id"], err)
		// If the error indicates a banned/auth issue, mark the account
		errStr := err.Error()
		if contains(errStr, "banned", "unauthorized", "forbidden", "401", "403") {
			controller.MarkKiroAccountError(account, errStr)
		}
		return
	}
}

// contains checks if s contains any of the substrings.
func contains(s string, subs ...string) bool {
	for _, sub := range subs {
		if len(s) >= len(sub) {
			for i := 0; i <= len(s)-len(sub); i++ {
				if s[i:i+len(sub)] == sub {
					return true
				}
			}
		}
	}
	return false
}

func main() {
	Main.Run(context.Background())
}
