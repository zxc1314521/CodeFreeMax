package controller

import (
	"context"
	"encoding/json"
	"fmt"
	"log"
	"net/http"
	"time"

	"kiro2api/internal/logic/kiro"

	"github.com/gogf/gf/v2/net/ghttp"
	"github.com/imroc/req/v3"
)

// TestController handles test/health-check endpoints.
type TestController struct{}

// TestReq represents the request body for the test endpoint.
type TestReq struct {
	Channel   string `json:"channel"`
	Model     string `json:"model"`
	MaxTokens int    `json:"max_tokens"`
	Stream    bool   `json:"stream"`
	Prompt    string `json:"prompt"`
	AccountID int    `json:"account_id"`
}

// writeTestError writes an error as SSE event to the raw writer.
func writeTestError(w http.ResponseWriter, errMsg string) {
	errJSON, _ := json.Marshal(map[string]interface{}{
		"id":     "test-error",
		"object": "chat.completion.chunk",
		"choices": []map[string]interface{}{
			{"index": 0, "delta": map[string]interface{}{"content": "[错误] " + errMsg}},
		},
	})
	w.Write([]byte("data: " + string(errJSON) + "\n\n"))
	w.Write([]byte("data: [DONE]\n\n"))
	if flusher, ok := w.(http.Flusher); ok {
		flusher.Flush()
	}
}

// Test handles POST /api/test — directly calls the kiro logic layer
// to test an account, streaming the response back to the caller.
func (c *TestController) Test(r *ghttp.Request) {
	log.Printf("[Test] ========== 收到测试请求 ==========")
	log.Printf("[Test] RemoteAddr=%s, Method=%s, URL=%s", r.GetClientIp(), r.Method, r.URL.String())

	body := r.GetBodyString()
	log.Printf("[Test] Request body: %s", body)

	var testReq TestReq
	if err := json.Unmarshal([]byte(body), &testReq); err != nil {
		log.Printf("[Test] JSON解析失败: %v", err)
		r.Response.WriteJson(map[string]interface{}{
			"code": 1,
			"msg":  "参数错误: " + err.Error(),
		})
		return
	}

	log.Printf("[Test] 解析参数: channel=%s, model=%s, account_id=%d, stream=%v, prompt_len=%d",
		testReq.Channel, testReq.Model, testReq.AccountID, testReq.Stream, len(testReq.Prompt))

	// Set defaults
	if testReq.Prompt == "" {
		testReq.Prompt = "hello"
	}
	if testReq.MaxTokens == 0 {
		testReq.MaxTokens = 1024
	}
	if testReq.Model == "" {
		testReq.Model = "kiro-claude-sonnet-4"
	}

	// Build OpenAI-compatible chat request
	chatReq := map[string]interface{}{
		"model":      testReq.Model,
		"max_tokens": testReq.MaxTokens,
		"stream":     true,
		"messages": []map[string]interface{}{
			{
				"role":    "user",
				"content": testReq.Prompt,
			},
		},
	}

	// Get account — either specific or round-robin
	var account map[string]interface{}
	var err error

	log.Printf("[Test] 获取账号: account_id=%d", testReq.AccountID)
	if testReq.AccountID > 0 {
		account, err = GetKiroAccountByID(testReq.AccountID)
	} else {
		account, err = GetNextKiroAccount()
	}
	if err != nil {
		log.Printf("[Test] 获取账号失败: %v", err)
		r.Response.WriteJson(map[string]interface{}{
			"code": 1,
			"msg":  "获取账号失败: " + err.Error(),
		})
		return
	}

	log.Printf("[Test] 账号获取成功: id=%v, channel=%v, status=%v, access_token_len=%d, refresh_token_len=%d",
		account["id"], account["channel"], account["status"],
		len(fmt.Sprintf("%v", account["access_token"])),
		len(fmt.Sprintf("%v", account["refresh_token"])))

	// Create HTTP client and kiro service
	client := req.C()
	kiroSvc := kiro.New()

	// Refresh token if needed
	log.Printf("[Test] 开始刷新Token...")
	refreshStart := time.Now()
	if refreshErr := kiroSvc.RefreshToken(client, account); refreshErr != nil {
		log.Printf("[Test] Token刷新失败 (耗时 %v): %v", time.Since(refreshStart), refreshErr)
		MarkKiroAccountError(account, "token refresh failed: "+refreshErr.Error())
		r.Response.WriteJson(map[string]interface{}{
			"code": 1,
			"msg":  "Token刷新失败: " + refreshErr.Error(),
		})
		return
	}
	log.Printf("[Test] Token刷新成功 (耗时 %v)", time.Since(refreshStart))

	// Write refreshed tokens back
	UpdateKiroAccountTokens(account)

	// Set SSE headers — must be done BEFORE any write
	log.Printf("[Test] 设置SSE响应头...")
	r.Response.Header().Set("Content-Type", "text/event-stream")
	r.Response.Header().Set("Cache-Control", "no-cache")
	r.Response.Header().Set("Connection", "keep-alive")
	r.Response.Header().Set("X-Accel-Buffering", "no")
	r.Response.Flush()

	rawWriter := r.Response.RawWriter()
	log.Printf("[Test] rawWriter type=%T", rawWriter)

	// Add a timeout context so the test doesn't hang forever (90s max)
	ctx, cancel := context.WithTimeout(r.Context(), 90*time.Second)
	defer cancel()

	// Mark token as already refreshed so ChatCompletions skips CheckToken
	account["_token_checked"] = true

	// Call kiro ChatCompletions directly
	log.Printf("[Test] 调用 ChatCompletions: account_id=%v, model=%s", account["id"], testReq.Model)
	chatStart := time.Now()
	if err := kiroSvc.ChatCompletions(ctx, rawWriter, chatReq, account, client); err != nil {
		log.Printf("[Test] ChatCompletions 失败 (耗时 %v): %v", time.Since(chatStart), err)
		writeTestError(rawWriter, err.Error())
	}
	log.Printf("[Test] ========== 测试完成 (总耗时 %v) ==========", time.Since(chatStart))
}
