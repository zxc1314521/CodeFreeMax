package controller

import (
	"fmt"
	"strings"
	"sync"
	"time"

	"github.com/gogf/gf/v2/net/ghttp"
)

type Account struct {
	ID        string `json:"id"`
	Channel   string `json:"channel"`
	Email     string `json:"email"`
	Token     string `json:"token"`
	Password  string `json:"password,omitempty"`
	Cookie    string `json:"cookie"`
	Remark    string `json:"remark"`
	Plan      string `json:"plan"`
	Status    string `json:"status"`
	Enabled   bool   `json:"enabled"`
	LastUsed  string `json:"last_used,omitempty"`
	ErrorMsg  string `json:"error_msg,omitempty"`
	UsageUsed int    `json:"usage_used"`
	UsageLimit int   `json:"usage_limit"`
}

var (
	accountStore = make(map[string]*Account) // id -> account
	accountMu    sync.RWMutex
	accountSeq   int
)

type AccountsController struct{}

func (c *AccountsController) List(r *ghttp.Request) {
	channel := r.Get("channel", "kiro").String()
	search := r.Get("search", "").String()
	status := r.Get("status", "").String()
	page := r.Get("page", 1).Int()
	pageSize := r.Get("pageSize", 20).Int()

	accountMu.RLock()
	var filtered []*Account
	for _, acc := range accountStore {
		if acc.Channel != channel {
			continue
		}
		if status != "" && acc.Status != status {
			continue
		}
		if search != "" && !strings.Contains(acc.Email, search) && !strings.Contains(acc.Token, search) {
			continue
		}
		filtered = append(filtered, acc)
	}
	accountMu.RUnlock()

	total := len(filtered)
	start := (page - 1) * pageSize
	if start > total {
		start = total
	}
	end := start + pageSize
	if end > total {
		end = total
	}

	r.Response.WriteJsonExit(map[string]interface{}{
		"code": 0,
		"data": map[string]interface{}{
			"list":  filtered[start:end],
			"total": total,
		},
	})
}

func (c *AccountsController) Add(r *ghttp.Request) {
	var req struct {
		Channel  string `json:"channel"`
		Email    string `json:"email"`
		Token    string `json:"token"`
		Password string `json:"password"`
		Cookie   string `json:"cookie"`
		Remark   string `json:"remark"`
	}
	if err := r.Parse(&req); err != nil {
		r.Response.WriteJsonExit(map[string]interface{}{"code": 1, "message": "参数错误"})
	}

	accountMu.Lock()
	accountSeq++
	id := fmt.Sprintf("%d", accountSeq)
	acc := &Account{
		ID:      id,
		Channel: req.Channel,
		Email:   req.Email,
		Token:   req.Token,
		Password: req.Password,
		Cookie:  req.Cookie,
		Remark:  req.Remark,
		Status:  "active",
		Enabled: true,
	}
	accountStore[id] = acc
	accountMu.Unlock()

	r.Response.WriteJsonExit(map[string]interface{}{"code": 0, "message": "添加成功", "data": acc})
}

func (c *AccountsController) Update(r *ghttp.Request) {
	var req struct {
		ID       string `json:"id"`
		Email    string `json:"email"`
		Token    string `json:"token"`
		Password string `json:"password"`
		Cookie   string `json:"cookie"`
		Remark   string `json:"remark"`
	}
	if err := r.Parse(&req); err != nil {
		r.Response.WriteJsonExit(map[string]interface{}{"code": 1, "message": "参数错误"})
	}

	accountMu.Lock()
	acc, ok := accountStore[req.ID]
	if !ok {
		accountMu.Unlock()
		r.Response.WriteJsonExit(map[string]interface{}{"code": 1, "message": "账号不存在"})
	}
	if req.Email != "" {
		acc.Email = req.Email
	}
	if req.Token != "" {
		acc.Token = req.Token
	}
	if req.Password != "" {
		acc.Password = req.Password
	}
	if req.Cookie != "" {
		acc.Cookie = req.Cookie
	}
	acc.Remark = req.Remark
	accountMu.Unlock()

	r.Response.WriteJsonExit(map[string]interface{}{"code": 0, "message": "更新成功"})
}

func (c *AccountsController) Delete(r *ghttp.Request) {
	var req struct {
		Channel string   `json:"channel"`
		IDs     []string `json:"ids"`
	}
	if err := r.Parse(&req); err != nil {
		r.Response.WriteJsonExit(map[string]interface{}{"code": 1, "message": "参数错误"})
	}

	accountMu.Lock()
	for _, id := range req.IDs {
		delete(accountStore, id)
	}
	accountMu.Unlock()

	r.Response.WriteJsonExit(map[string]interface{}{"code": 0, "message": "删除成功"})
}

func (c *AccountsController) Toggle(r *ghttp.Request) {
	var req struct {
		Channel string `json:"channel"`
		ID      string `json:"id"`
		Enabled bool   `json:"enabled"`
	}
	if err := r.Parse(&req); err != nil {
		r.Response.WriteJsonExit(map[string]interface{}{"code": 1, "message": "参数错误"})
	}

	accountMu.Lock()
	acc, ok := accountStore[req.ID]
	if ok {
		acc.Enabled = req.Enabled
	}
	accountMu.Unlock()

	if !ok {
		r.Response.WriteJsonExit(map[string]interface{}{"code": 1, "message": "账号不存在"})
	}
	r.Response.WriteJsonExit(map[string]interface{}{"code": 0, "message": "操作成功"})
}

func (c *AccountsController) Refresh(r *ghttp.Request) {
	var req struct {
		Channel string `json:"channel"`
		ID      string `json:"id"`
	}
	if err := r.Parse(&req); err != nil {
		r.Response.WriteJsonExit(map[string]interface{}{"code": 1, "message": "参数错误"})
	}

	accountMu.Lock()
	acc, ok := accountStore[req.ID]
	if ok {
		acc.LastUsed = time.Now().Format(time.RFC3339)
		acc.Status = "active"
	}
	accountMu.Unlock()

	if !ok {
		r.Response.WriteJsonExit(map[string]interface{}{"code": 1, "message": "账号不存在"})
	}
	r.Response.WriteJsonExit(map[string]interface{}{"code": 0, "message": "刷新成功"})
}

func (c *AccountsController) BatchAdd(r *ghttp.Request) {
	var req struct {
		Channel string `json:"channel"`
		Items   []struct {
			Email    string `json:"email"`
			Token    string `json:"token"`
			Password string `json:"password"`
			Cookie   string `json:"cookie"`
		} `json:"items"`
	}
	if err := r.Parse(&req); err != nil {
		r.Response.WriteJsonExit(map[string]interface{}{"code": 1, "message": "参数错误"})
	}

	accountMu.Lock()
	count := 0
	for _, item := range req.Items {
		accountSeq++
		id := fmt.Sprintf("%d", accountSeq)
		accountStore[id] = &Account{
			ID:      id,
			Channel: req.Channel,
			Email:   item.Email,
			Token:   item.Token,
			Password: item.Password,
			Cookie:  item.Cookie,
			Status:  "active",
			Enabled: true,
		}
		count++
	}
	accountMu.Unlock()

	r.Response.WriteJsonExit(map[string]interface{}{"code": 0, "message": fmt.Sprintf("成功添加 %d 个账号", count)})
}

func (c *AccountsController) BatchOperation(r *ghttp.Request) {
	var req struct {
		Channel   string   `json:"channel"`
		IDs       []string `json:"ids"`
		Operation string   `json:"operation"`
	}
	if err := r.Parse(&req); err != nil {
		r.Response.WriteJsonExit(map[string]interface{}{"code": 1, "message": "参数错误"})
	}

	accountMu.Lock()
	for _, id := range req.IDs {
		acc, ok := accountStore[id]
		if !ok {
			continue
		}
		switch req.Operation {
		case "enable":
			acc.Enabled = true
		case "disable":
			acc.Enabled = false
		case "refresh":
			acc.Status = "active"
			acc.LastUsed = time.Now().Format(time.RFC3339)
		case "delete":
			delete(accountStore, id)
		}
	}
	accountMu.Unlock()

	r.Response.WriteJsonExit(map[string]interface{}{"code": 0, "message": "操作成功"})
}
