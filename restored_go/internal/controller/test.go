package controller

import (
	"encoding/json"
	"fmt"
	"net/http"
	"strings"

	"kiro2api/internal/dao"

	"github.com/gogf/gf/v2/net/ghttp"
)

// TestController handles test/health-check endpoints.
type TestController struct{}

// TestReq represents the request body for the test endpoint.
type TestReq struct {
	Channel    string `json:"channel"`     // len 7
	Model      string `json:"model"`       // len 5
	MaxTokens  int    `json:"max_tokens"`  // len 10
	Stream     bool   `json:"stream"`      // len 6
	Prompt     string `json:"prompt"`      // default "hello"
}

// Test handles POST /api/test — sends a test request to the specified channel
// to verify that the channel is working correctly.
func (c *TestController) Test(r *ghttp.Request) {
	var req TestReq
	if err := r.Parse(&req); err != nil {
		r.Response.WriteJson(map[string]interface{}{
			"code": 1,
			"msg":  err.Error(),
		})
		return
	}

	// Set defaults
	if req.Prompt == "" {
		req.Prompt = "hello" // len 5
	}
	if req.MaxTokens == 0 {
		req.MaxTokens = 1024 // 0x400
	}

	// Look up channel handler from registered channels map
	channelMap := dao.GetChannelMap()
	handler, ok := channelMap[req.Channel]
	if !ok {
		r.Response.WriteJson(map[string]interface{}{
			"code": 1,
			"msg":  "unsupported channel: " + req.Channel,
		})
		return
	}

	// Build a minimal OpenAI-compatible request body
	testBody := map[string]interface{}{
		"model":      req.Model,
		"max_tokens": req.MaxTokens,
		"stream":     req.Stream,
		"messages": []map[string]interface{}{
			{
				"role":    "user",
				"content": req.Prompt,
			},
		},
	}

	bodyBytes, _ := json.Marshal(testBody)

	// Get the server's listened port and build internal URL
	port := ghttp.GetServer().GetListenedPort()
	url := fmt.Sprintf("http://127.0.0.1:%d/v1/chat/completions", port)

	// Create internal HTTP request
	httpReq, err := http.NewRequestWithContext(r.Context(), "POST", url, strings.NewReader(string(bodyBytes)))
	if err != nil {
		r.Response.WriteJson(map[string]interface{}{
			"code": 1,
			"msg":  "create request failed: " + err.Error(),
		})
		return
	}

	httpReq.Header.Set("Content-Type", "application/json")

	// Execute via channel handler
	resp, err := handler.Do(httpReq)
	if err != nil {
		r.Response.WriteJson(map[string]interface{}{
			"code": 1,
			"msg":  "request failed: " + err.Error(),
		})
		return
	}
	defer resp.Body.Close()

	// Forward response
	r.Response.WriteJson(map[string]interface{}{
		"code": 0,
		"msg":  "success",
	})
}
