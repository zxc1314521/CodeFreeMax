package main

import (
	"context"
	"log"

	"kiro2api/internal/controller"

	"github.com/gogf/gf/v2/frame/g"
	"github.com/gogf/gf/v2/net/ghttp"
	"github.com/gogf/gf/v2/os/gcmd"
)

var (
	Main = gcmd.Command{
		Name:  "main",
		Usage: "main",
		Brief: "kiro2api - Multi-channel AI API proxy",
		Func: func(ctx context.Context, parser *gcmd.Parser) (err error) {
			s := g.Server()

			// OpenAI-compatible API endpoints
			s.Group("/v1", func(group *ghttp.RouterGroup) {
				group.GET("/models", func(r *ghttp.Request) {
					controller.RegisterModelsRoute(r)
				})
				group.POST("/chat/completions", func(r *ghttp.Request) {
					handleChatCompletions(r)
				})
			})

			// Admin API endpoints
			s.Group("/api", func(group *ghttp.RouterGroup) {
				configCtrl := &controller.ConfigController{}
				testCtrl := &controller.TestController{}

				group.POST("/config/save", configCtrl.Save)
				group.POST("/test", testCtrl.Test)
			})

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
func handleChatCompletions(r *ghttp.Request) {
	var req struct {
		Model    string        `json:"model"`
		Messages []interface{} `json:"messages"`
		Stream   bool          `json:"stream"`
	}
	if err := r.Parse(&req); err != nil {
		r.Response.WriteJson(map[string]interface{}{
			"error": map[string]interface{}{
				"message": "invalid request: " + err.Error(),
				"type":    "invalid_request_error",
			},
		})
		return
	}

	// For now, return a placeholder response
	// Each channel's ChatCompletions handler will be wired up here
	if req.Stream {
		r.Response.Header().Set("Content-Type", "text/event-stream")
		r.Response.Header().Set("Cache-Control", "no-cache")
		r.Response.Header().Set("Connection", "keep-alive")

		r.Response.Writeln("data: " + `{"id":"chatcmpl-stub","object":"chat.completion.chunk","choices":[{"index":0,"delta":{"role":"assistant","content":"kiro2api is running. Channel routing not yet configured for model: ` + req.Model + `"},"finish_reason":"stop"}]}`)
		r.Response.Writeln("data: [DONE]")
	} else {
		r.Response.WriteJson(map[string]interface{}{
			"id":      "chatcmpl-stub",
			"object":  "chat.completion",
			"model":   req.Model,
			"choices": []map[string]interface{}{
				{
					"index": 0,
					"message": map[string]interface{}{
						"role":    "assistant",
						"content": "kiro2api is running. Channel routing not yet configured for model: " + req.Model,
					},
					"finish_reason": "stop",
				},
			},
		})
	}
}

func main() {
	Main.Run(context.Background())
}
