package controller

import (
	"encoding/json"
	"fmt"
	"log"
	"strings"
	"sync"
	"time"

	"kiro2api/internal/dao"
	"kiro2api/internal/logic/kiro"

	"github.com/gogf/gf/v2/net/ghttp"
	"github.com/imroc/req/v3"
)

// ChannelAccount represents an account for any channel
type ChannelAccount struct {
	ID           int    `json:"id"`
	Channel      string `json:"channel"`
	Email        string `json:"email,omitempty"`
	Token        string `json:"token,omitempty"`
	AccessToken  string `json:"access_token,omitempty"`
	RefreshToken string `json:"refresh_token,omitempty"`
	IDToken      string `json:"id_token,omitempty"`
	Cookie       string `json:"cookie,omitempty"`
	SessionKey   string `json:"session_key,omitempty"`
	Password     string `json:"password,omitempty"`
	ProjectID    string `json:"project_id,omitempty"`
	OrgID        string `json:"org_id,omitempty"`
	PlanType     string `json:"plan_type,omitempty"`
	Pool         string `json:"pool,omitempty"`
	Proxy        string `json:"proxy,omitempty"`
	Status       string `json:"status"`
	Enabled      bool   `json:"enabled"`
	Nsfw         bool   `json:"nsfw,omitempty"`
	Tags         string `json:"tags,omitempty"`
	ErrorMsg     string `json:"error_msg,omitempty"`
	UsageUsed    int    `json:"usage_used"`
	UsageLimit   int    `json:"usage_limit"`
	UsageCount   int    `json:"usage_count"`
	UseCount     int    `json:"use_count"`
	Quota        string `json:"quota,omitempty"`
	ResetDate    string `json:"reset_date,omitempty"`
	TokenExpiry  string `json:"token_expiry,omitempty"`
	LastUsedAt   string `json:"last_used_at,omitempty"`
	CreatedAt    string `json:"created_at,omitempty"`

	// Kiro IDC-specific fields
	AuthMethod   string `json:"auth_method,omitempty"`    // "social" or "IdC"
	ClientID     string `json:"client_id,omitempty"`      // SSO OIDC client ID
	ClientSecret string `json:"client_secret,omitempty"`  // SSO OIDC client secret
	Region       string `json:"region,omitempty"`         // AWS region (e.g. "us-east-1")
	StartURL     string `json:"start_url,omitempty"`      // Enterprise SSO start URL
}

var (
	chAccountStore = make(map[string]map[int]*ChannelAccount) // channel -> id -> account
	chAccountMu    sync.RWMutex
	chAccountSeq   int
)

func getChannelStore(channel string) map[int]*ChannelAccount {
	if chAccountStore[channel] == nil {
		chAccountStore[channel] = make(map[int]*ChannelAccount)
	}
	return chAccountStore[channel]
}

// LoadAccountsFromDB loads all accounts from the database into the in-memory store.
// Called once at startup after database initialization.
func LoadAccountsFromDB() {
	accounts, err := dao.ChannelAccountGetAllChannels()
	if err != nil {
		log.Printf("[LoadAccountsFromDB] Failed to load accounts: %v", err)
		return
	}

	chAccountMu.Lock()
	defer chAccountMu.Unlock()

	loaded := 0
	for _, dbAcc := range accounts {
		store := getChannelStore(dbAcc.Channel)
		acc := &ChannelAccount{
			ID:           dbAcc.ID,
			Channel:      dbAcc.Channel,
			Email:        dbAcc.Email,
			Token:        dbAcc.Token,
			AccessToken:  dbAcc.AccessToken,
			RefreshToken: dbAcc.RefreshToken,
			IDToken:      dbAcc.IDToken,
			Cookie:       dbAcc.Cookie,
			SessionKey:   dbAcc.SessionKey,
			Password:     dbAcc.Password,
			ProjectID:    dbAcc.ProjectID,
			OrgID:        dbAcc.OrgID,
			PlanType:     dbAcc.PlanType,
			Pool:         dbAcc.Pool,
			Proxy:        dbAcc.Proxy,
			Status:       dbAcc.Status,
			Enabled:      dbAcc.Enabled,
			Nsfw:         dbAcc.Nsfw,
			Tags:         dbAcc.Tags,
			ErrorMsg:     dbAcc.ErrorMsg,
			UsageUsed:    dbAcc.UsageUsed,
			UsageLimit:   dbAcc.UsageLimit,
			UsageCount:   dbAcc.UsageCount,
			UseCount:     dbAcc.UseCount,
			Quota:        dbAcc.Quota,
			ResetDate:    dbAcc.ResetDate,
			TokenExpiry:  dbAcc.TokenExpiry,
			LastUsedAt:   dbAcc.LastUsedAt,
			AuthMethod:   dbAcc.AuthMethod,
			ClientID:     dbAcc.ClientID,
			ClientSecret: dbAcc.ClientSecret,
			Region:       dbAcc.Region,
			StartURL:     dbAcc.StartURL,
			CreatedAt:    dbAcc.CreatedAt.Format(time.RFC3339),
		}
		store[acc.ID] = acc
		if acc.ID > chAccountSeq {
			chAccountSeq = acc.ID
		}
		loaded++
	}

	log.Printf("[LoadAccountsFromDB] Loaded %d accounts from database", loaded)
}

// toDBAccount converts an in-memory ChannelAccount to a dao.DBChannelAccount for persistence.
func toDBAccount(acc *ChannelAccount) *dao.DBChannelAccount {
	dbAcc := &dao.DBChannelAccount{
		ID:           acc.ID,
		Channel:      acc.Channel,
		Email:        acc.Email,
		Token:        acc.Token,
		AccessToken:  acc.AccessToken,
		RefreshToken: acc.RefreshToken,
		IDToken:      acc.IDToken,
		Cookie:       acc.Cookie,
		SessionKey:   acc.SessionKey,
		Password:     acc.Password,
		ProjectID:    acc.ProjectID,
		OrgID:        acc.OrgID,
		PlanType:     acc.PlanType,
		Pool:         acc.Pool,
		Proxy:        acc.Proxy,
		Status:       acc.Status,
		Enabled:      acc.Enabled,
		Nsfw:         acc.Nsfw,
		Tags:         acc.Tags,
		ErrorMsg:     acc.ErrorMsg,
		UsageUsed:    acc.UsageUsed,
		UsageLimit:   acc.UsageLimit,
		UsageCount:   acc.UsageCount,
		UseCount:     acc.UseCount,
		Quota:        acc.Quota,
		ResetDate:    acc.ResetDate,
		TokenExpiry:  acc.TokenExpiry,
		LastUsedAt:   acc.LastUsedAt,
		AuthMethod:   acc.AuthMethod,
		ClientID:     acc.ClientID,
		ClientSecret: acc.ClientSecret,
		Region:       acc.Region,
		StartURL:     acc.StartURL,
	}
	return dbAcc
}

type ChannelAccountController struct{}

// Stats returns channel account statistics
func (c *ChannelAccountController) Stats(r *ghttp.Request) {
	channel := extractChannel(r)
	chAccountMu.RLock()
	store := getChannelStore(channel)
	total := len(store)
	normal := 0
	for _, acc := range store {
		if acc.Status == "normal" {
			normal++
		}
	}
	chAccountMu.RUnlock()

	r.Response.WriteJsonExit(map[string]interface{}{
		"code": 0,
		"data": map[string]interface{}{
			"total":  total,
			"normal": normal,
		},
	})
}

// List returns paginated account list for a channel
func (c *ChannelAccountController) List(r *ghttp.Request) {
	channel := extractChannel(r)
	page := r.Get("page", 1).Int()
	pageSize := r.Get("pageSize", 20).Int()
	status := r.Get("status", "").String()
	planType := r.Get("plan_type", "").String()
	pool := r.Get("pool", "").String()
	nsfw := r.Get("nsfw", "").String()

	chAccountMu.RLock()
	store := getChannelStore(channel)
	var filtered []*ChannelAccount
	for _, acc := range store {
		if status != "" && acc.Status != status {
			continue
		}
		if planType != "" && acc.PlanType != planType {
			continue
		}
		if pool != "" && acc.Pool != pool {
			continue
		}
		if nsfw == "enabled" && !acc.Nsfw {
			continue
		}
		if nsfw == "disabled" && acc.Nsfw {
			continue
		}
		filtered = append(filtered, acc)
	}
	totalCount := len(store)
	normalCount := 0
	for _, acc := range store {
		if acc.Status == "normal" {
			normalCount++
		}
	}
	chAccountMu.RUnlock()

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
			"list":        filtered[start:end],
			"total":       total,
			"totalCount":  totalCount,
			"normalCount": normalCount,
		},
	})
}

// Add handles adding accounts (batch token field)
func (c *ChannelAccountController) Add(r *ghttp.Request) {
	channel := extractChannel(r)
	body := r.GetBodyString()

	// Parse JSON body into map
	var req map[string]interface{}
	if err := json.Unmarshal([]byte(body), &req); err != nil {
		r.Response.WriteJsonExit(map[string]interface{}{"code": 1, "message": "参数错误: " + err.Error()})
		return
	}

	// Find the token array from known field names
	tokenFields := []string{
		"refreshTokens", "clientJwts", "tokens", "refresh_tokens",
		"session_keys", "ssoTokens", "cookies",
	}
	var tokens []string
	for _, field := range tokenFields {
		if val, ok := req[field]; ok {
			if arr, ok := val.([]interface{}); ok {
				for _, v := range arr {
					if s, ok := v.(string); ok && s != "" {
						tokens = append(tokens, s)
					}
				}
			}
			break
		}
	}

	if len(tokens) == 0 {
		r.Response.WriteJsonExit(map[string]interface{}{"code": 1, "message": "未找到有效Token"})
		return
	}

	chAccountMu.Lock()
	store := getChannelStore(channel)
	success := 0
	var dbAccounts []*dao.DBChannelAccount
	for _, token := range tokens {
		chAccountSeq++
		acc := &ChannelAccount{
			ID:        chAccountSeq,
			Channel:   channel,
			Token:     token,
			Status:    "normal",
			Enabled:   true,
			CreatedAt: time.Now().Format(time.RFC3339),
		}
		if channel == "kiro" {
			if strings.Contains(token, "----") {
				// IDC format: refreshToken----clientId----clientSecret----region
				parts := strings.SplitN(token, "----", 4)
				acc.RefreshToken = parts[0]
				acc.Token = parts[0]
				acc.AuthMethod = "IdC"
				if len(parts) >= 2 {
					acc.ClientID = parts[1]
				}
				if len(parts) >= 3 {
					acc.ClientSecret = parts[2]
				}
				if len(parts) >= 4 {
					acc.Region = parts[3]
				}
				if acc.Region == "" {
					acc.Region = "us-east-1"
				}
			} else {
				// Social auth: pure refreshToken
				acc.RefreshToken = token
				acc.Token = token
				acc.AuthMethod = "social"
			}
		}
		store[chAccountSeq] = acc
		dbAccounts = append(dbAccounts, toDBAccount(acc))
		success++
	}
	chAccountMu.Unlock()

	// Persist to database
	if len(dbAccounts) > 0 {
		if err := dao.ChannelAccountInsertBatch(dbAccounts); err != nil {
			log.Printf("[Add] Failed to persist accounts to DB: %v", err)
		}
	}

	r.Response.WriteJsonExit(map[string]interface{}{
		"code": 0,
		"data": map[string]interface{}{"success": success, "total": len(tokens)},
	})
}

// Delete handles single account deletion
func (c *ChannelAccountController) Delete(r *ghttp.Request) {
	channel := extractChannel(r)
	var req struct {
		ID int `json:"id"`
	}
	if err := r.Parse(&req); err != nil {
		r.Response.WriteJsonExit(map[string]interface{}{"code": 1, "message": "参数错误"})
		return
	}

	chAccountMu.Lock()
	store := getChannelStore(channel)
	delete(store, req.ID)
	chAccountMu.Unlock()

	// Persist to database
	if err := dao.ChannelAccountDeleteByID(req.ID); err != nil {
		log.Printf("[Delete] Failed to delete account %d from DB: %v", req.ID, err)
	}

	r.Response.WriteJsonExit(map[string]interface{}{"code": 0, "message": "删除成功"})
}

// DeleteBatch handles batch deletion
func (c *ChannelAccountController) DeleteBatch(r *ghttp.Request) {
	channel := extractChannel(r)
	var req struct {
		IDs []int `json:"ids"`
	}
	if err := r.Parse(&req); err != nil {
		r.Response.WriteJsonExit(map[string]interface{}{"code": 1, "message": "参数错误"})
		return
	}

	chAccountMu.Lock()
	store := getChannelStore(channel)
	deleted := 0
	var deletedIDs []int
	for _, id := range req.IDs {
		if _, ok := store[id]; ok {
			delete(store, id)
			deletedIDs = append(deletedIDs, id)
			deleted++
		}
	}
	chAccountMu.Unlock()

	// Persist to database
	if len(deletedIDs) > 0 {
		if err := dao.ChannelAccountDeleteByIDs(deletedIDs); err != nil {
			log.Printf("[DeleteBatch] Failed to delete accounts from DB: %v", err)
		}
	}

	r.Response.WriteJsonExit(map[string]interface{}{
		"code": 0,
		"data": map[string]interface{}{"deleted": deleted},
	})
}

// DeleteAbnormal deletes all abnormal accounts
func (c *ChannelAccountController) DeleteAbnormal(r *ghttp.Request) {
	channel := extractChannel(r)

	chAccountMu.Lock()
	store := getChannelStore(channel)
	deleted := 0
	var deletedIDs []int
	for id, acc := range store {
		if acc.Status != "normal" {
			delete(store, id)
			deletedIDs = append(deletedIDs, id)
			deleted++
		}
	}
	chAccountMu.Unlock()

	// Persist to database
	if len(deletedIDs) > 0 {
		if err := dao.ChannelAccountDeleteByIDs(deletedIDs); err != nil {
			log.Printf("[DeleteAbnormal] Failed to delete abnormal accounts from DB: %v", err)
		}
	}

	r.Response.WriteJsonExit(map[string]interface{}{
		"code": 0,
		"data": map[string]interface{}{"deleted": deleted},
	})
}

// RecoverAbnormal recovers all abnormal accounts
func (c *ChannelAccountController) RecoverAbnormal(r *ghttp.Request) {
	channel := extractChannel(r)

	chAccountMu.Lock()
	store := getChannelStore(channel)
	recovered := 0
	for _, acc := range store {
		if acc.Status != "normal" {
			acc.Status = "normal"
			acc.ErrorMsg = ""
			recovered++
		}
	}
	chAccountMu.Unlock()

	// Persist to database
	if recovered > 0 {
		if _, err := dao.ChannelAccountRecoverAbnormal(channel); err != nil {
			log.Printf("[RecoverAbnormal] Failed to recover accounts in DB: %v", err)
		}
	}

	r.Response.WriteJsonExit(map[string]interface{}{
		"code": 0,
		"data": map[string]interface{}{"recovered": recovered},
	})
}

// Refresh refreshes a single account (performs real token refresh for kiro)
func (c *ChannelAccountController) Refresh(r *ghttp.Request) {
	channel := extractChannel(r)
	var reqBody struct {
		ID int `json:"id"`
	}
	if err := r.Parse(&reqBody); err != nil {
		r.Response.WriteJsonExit(map[string]interface{}{"code": 1, "message": "参数错误"})
		return
	}

	chAccountMu.RLock()
	store := getChannelStore(channel)
	acc, ok := store[reqBody.ID]
	chAccountMu.RUnlock()

	if !ok {
		r.Response.WriteJsonExit(map[string]interface{}{"code": 1, "message": "账号不存在"})
		return
	}

	if channel == "kiro" {
		// Real token refresh for kiro accounts
		accountMap := ChannelAccountToMap(acc)
		client := req.C()
		kiroSvc := kiro.New()
		if err := kiroSvc.RefreshToken(client, accountMap); err != nil {
			log.Printf("[Refresh] Kiro token refresh failed for account %d: %v", reqBody.ID, err)
			chAccountMu.Lock()
			acc.Status = "error"
			acc.ErrorMsg = "refresh failed: " + err.Error()
			chAccountMu.Unlock()
			// Persist error status to DB
			dao.ChannelAccountUpdate(reqBody.ID, map[string]interface{}{"status": "error", "error_msg": "refresh failed: " + err.Error()})
			r.Response.WriteJsonExit(map[string]interface{}{"code": 1, "message": "刷新失败: " + err.Error()})
			return
		}
		// Write back refreshed tokens
		UpdateKiroAccountTokens(accountMap)
		chAccountMu.Lock()
		acc.Status = "normal"
		acc.ErrorMsg = ""
		acc.LastUsedAt = time.Now().Format(time.RFC3339)
		chAccountMu.Unlock()

		// Fetch usage info after successful token refresh
		usageFields := map[string]interface{}{
			"status": "normal", "error_msg": "", "last_used_at": acc.LastUsedAt,
			"access_token": acc.AccessToken, "refresh_token": acc.RefreshToken, "token_expiry": acc.TokenExpiry,
		}
		usageInfo, usageErr := kiroSvc.GetUsageInfo(client, accountMap)
		if usageErr != nil {
			log.Printf("[Refresh] GetUsageInfo failed for account %d: %v", reqBody.ID, usageErr)
		}
		if usageErr == nil && usageInfo != nil {
			usageUsed, _ := usageInfo["usage_used"].(int)
			usageLimit, _ := usageInfo["usage_limit"].(int)
			subscriptionTitle, _ := usageInfo["subscription_title"].(string)
			email, _ := usageInfo["email"].(string)
			resetDate, _ := usageInfo["reset_date"].(string)
			chAccountMu.Lock()
			acc.UsageUsed = usageUsed
			acc.UsageLimit = usageLimit
			if subscriptionTitle != "" {
				acc.PlanType = normalizePlanType(subscriptionTitle)
			}
			if email != "" {
				acc.Email = email
			}
			if resetDate != "" {
				acc.ResetDate = resetDate
			}
			chAccountMu.Unlock()
			usageFields["usage_used"] = usageUsed
			usageFields["usage_limit"] = usageLimit
			if subscriptionTitle != "" {
				usageFields["plan_type"] = normalizePlanType(subscriptionTitle)
			}
			if email != "" {
				usageFields["email"] = email
			}
			if resetDate != "" {
				usageFields["reset_date"] = resetDate
			}
		}

		// Persist refreshed state to DB
		dao.ChannelAccountUpdate(reqBody.ID, usageFields)
	} else {
		chAccountMu.Lock()
		acc.LastUsedAt = time.Now().Format(time.RFC3339)
		acc.Status = "normal"
		chAccountMu.Unlock()
	}

	r.Response.WriteJsonExit(map[string]interface{}{"code": 0, "message": "刷新成功"})
}

// Export exports accounts
func (c *ChannelAccountController) Export(r *ghttp.Request) {
	channel := extractChannel(r)

	chAccountMu.RLock()
	store := getChannelStore(channel)
	var list []*ChannelAccount
	for _, acc := range store {
		list = append(list, acc)
	}
	chAccountMu.RUnlock()

	r.Response.WriteJsonExit(map[string]interface{}{
		"code": 0,
		"data": list,
	})
}

// UpdateProxy updates account proxy
func (c *ChannelAccountController) UpdateProxy(r *ghttp.Request) {
	channel := extractChannel(r)
	var req struct {
		ID    int    `json:"id"`
		Proxy string `json:"proxy"`
	}
	if err := r.Parse(&req); err != nil {
		r.Response.WriteJsonExit(map[string]interface{}{"code": 1, "message": "参数错误"})
		return
	}

	chAccountMu.Lock()
	store := getChannelStore(channel)
	acc, ok := store[req.ID]
	if ok {
		acc.Proxy = req.Proxy
	}
	chAccountMu.Unlock()

	if !ok {
		r.Response.WriteJsonExit(map[string]interface{}{"code": 1, "message": "账号不存在"})
		return
	}

	// Persist to database
	dao.ChannelAccountUpdate(req.ID, map[string]interface{}{"proxy": req.Proxy})

	r.Response.WriteJsonExit(map[string]interface{}{"code": 0, "message": "代理更新成功"})
}

// BatchRefreshUsage handles SSE batch refresh
func (c *ChannelAccountController) BatchRefreshUsage(r *ghttp.Request) {
	channel := extractChannel(r)
	var reqBody struct {
		Scope    string `json:"scope"`
		Page     int    `json:"page"`
		PageSize int    `json:"pageSize"`
	}
	if err := r.Parse(&reqBody); err != nil {
		r.Response.WriteJsonExit(map[string]interface{}{"code": 1, "message": "参数错误"})
		return
	}

	r.Response.Header().Set("Content-Type", "text/event-stream")
	r.Response.Header().Set("Cache-Control", "no-cache")
	r.Response.Header().Set("Connection", "keep-alive")

	chAccountMu.RLock()
	store := getChannelStore(channel)
	var accounts []*ChannelAccount
	for _, acc := range store {
		accounts = append(accounts, acc)
	}
	chAccountMu.RUnlock()

	total := len(accounts)
	success := 0
	failed := 0
	kiroSvc := kiro.New()
	client := req.C()

	for i, acc := range accounts {
		result := "ok"

		if channel == "kiro" {
			accountMap := ChannelAccountToMap(acc)

			// Refresh token first to ensure valid access_token
			if err := kiroSvc.RefreshToken(client, accountMap); err != nil {
				log.Printf("[BatchRefreshUsage] Token refresh failed for account %d: %v", acc.ID, err)
				result = "token refresh failed: " + err.Error()
				failed++

				r.Response.Writefln("event: result")
				r.Response.Writefln("data: {\"index\":%d,\"total\":%d,\"success\":%d,\"result\":\"%s\"}", i+1, total, success, result)
				r.Response.Writeln("")
				r.Response.Flush()
				continue
			}
			UpdateKiroAccountTokens(accountMap)

			// Fetch real usage from Kiro API
			usageInfo, err := kiroSvc.GetUsageInfo(client, accountMap)
			if err != nil {
				log.Printf("[BatchRefreshUsage] GetUsageInfo failed for account %d: %v", acc.ID, err)
				result = "usage fetch failed: " + err.Error()
				failed++

				r.Response.Writefln("event: result")
				r.Response.Writefln("data: {\"index\":%d,\"total\":%d,\"success\":%d,\"result\":\"%s\"}", i+1, total, success, result)
				r.Response.Writeln("")
				r.Response.Flush()
				continue
			}

			// Extract usage numbers from the response
			usageUsed, _ := usageInfo["usage_used"].(int)
			usageLimit, _ := usageInfo["usage_limit"].(int)
			subscriptionTitle, _ := usageInfo["subscription_title"].(string)
			batchEmail, _ := usageInfo["email"].(string)
			resetDate, _ := usageInfo["reset_date"].(string)

			// Update in-memory
			chAccountMu.Lock()
			acc.UsageUsed = usageUsed
			acc.UsageLimit = usageLimit
			acc.LastUsedAt = time.Now().Format(time.RFC3339)
			acc.Status = "normal"
			acc.ErrorMsg = ""
			if subscriptionTitle != "" {
				acc.PlanType = normalizePlanType(subscriptionTitle)
			}
			if batchEmail != "" {
				acc.Email = batchEmail
			}
			if resetDate != "" {
				acc.ResetDate = resetDate
			}
			chAccountMu.Unlock()

			// Persist to database
			dbFields := map[string]interface{}{
				"usage_used": usageUsed, "usage_limit": usageLimit,
				"last_used_at": acc.LastUsedAt, "status": "normal", "error_msg": "",
				"access_token": acc.AccessToken, "refresh_token": acc.RefreshToken, "token_expiry": acc.TokenExpiry,
			}
			if subscriptionTitle != "" {
				dbFields["plan_type"] = normalizePlanType(subscriptionTitle)
			}
			if batchEmail != "" {
				dbFields["email"] = batchEmail
			}
			if resetDate != "" {
				dbFields["reset_date"] = resetDate
			}
			dao.ChannelAccountUpdate(acc.ID, dbFields)
			success++
		} else {
			// Non-kiro channels: just update timestamp
			chAccountMu.Lock()
			acc.LastUsedAt = time.Now().Format(time.RFC3339)
			chAccountMu.Unlock()
			success++
		}

		r.Response.Writefln("event: result")
		r.Response.Writefln("data: {\"index\":%d,\"total\":%d,\"success\":%d,\"result\":\"%s\"}", i+1, total, success, result)
		r.Response.Writeln("")
		r.Response.Flush()
	}

	r.Response.Writefln("event: done")
	r.Response.Writefln("data: {\"success\":%d,\"failed\":%d}", success, total-success)
	r.Response.Writeln("")
	r.Response.Flush()
}

// QueryUsage queries usage info for a single account without full token refresh.
// If the token is expired it will refresh first, then fetch usage.
func (c *ChannelAccountController) QueryUsage(r *ghttp.Request) {
	channel := extractChannel(r)
	var reqBody struct {
		ID int `json:"id"`
	}
	if err := r.Parse(&reqBody); err != nil {
		r.Response.WriteJsonExit(map[string]interface{}{"code": 1, "message": "参数错误"})
		return
	}

	chAccountMu.RLock()
	store := getChannelStore(channel)
	acc, ok := store[reqBody.ID]
	chAccountMu.RUnlock()

	if !ok {
		r.Response.WriteJsonExit(map[string]interface{}{"code": 1, "message": "账号不存在"})
		return
	}

	if channel != "kiro" {
		r.Response.WriteJsonExit(map[string]interface{}{"code": 1, "message": "该渠道不支持用量查询"})
		return
	}

	accountMap := ChannelAccountToMap(acc)
	client := req.C()
	kiroSvc := kiro.New()

	// Ensure token is valid
	if err := kiroSvc.RefreshToken(client, accountMap); err != nil {
		r.Response.WriteJsonExit(map[string]interface{}{"code": 1, "message": "Token刷新失败: " + err.Error()})
		return
	}
	UpdateKiroAccountTokens(accountMap)

	// Fetch usage
	usageInfo, err := kiroSvc.GetUsageInfo(client, accountMap)
	if err != nil {
		r.Response.WriteJsonExit(map[string]interface{}{"code": 1, "message": "用量查询失败: " + err.Error()})
		return
	}

	usageUsed, _ := usageInfo["usage_used"].(int)
	usageLimit, _ := usageInfo["usage_limit"].(int)
	subscriptionTitle, _ := usageInfo["subscription_title"].(string)
	email, _ := usageInfo["email"].(string)
	resetDate, _ := usageInfo["reset_date"].(string)

	// Update in-memory
	chAccountMu.Lock()
	acc.UsageUsed = usageUsed
	acc.UsageLimit = usageLimit
	if subscriptionTitle != "" {
		acc.PlanType = normalizePlanType(subscriptionTitle)
	}
	if email != "" {
		acc.Email = email
	}
	if resetDate != "" {
		acc.ResetDate = resetDate
	}
	chAccountMu.Unlock()

	// Persist to DB
	dbFields := map[string]interface{}{
		"usage_used": usageUsed, "usage_limit": usageLimit,
		"access_token": acc.AccessToken, "refresh_token": acc.RefreshToken, "token_expiry": acc.TokenExpiry,
	}
	if subscriptionTitle != "" {
		dbFields["plan_type"] = normalizePlanType(subscriptionTitle)
	}
	if email != "" {
		dbFields["email"] = email
	}
	if resetDate != "" {
		dbFields["reset_date"] = resetDate
	}
	dao.ChannelAccountUpdate(reqBody.ID, dbFields)

	r.Response.WriteJsonExit(map[string]interface{}{
		"code": 0,
		"message": "查询成功",
		"data": map[string]interface{}{
			"usage_used":         usageUsed,
			"usage_limit":        usageLimit,
			"subscription_title": subscriptionTitle,
			"email":              email,
			"reset_date":         resetDate,
			"days_until_reset":   usageInfo["days_until_reset"],
		},
	})
}

// OAuthAuthorize handles OAuth device code flow initiation
func (c *ChannelAccountController) OAuthAuthorize(r *ghttp.Request) {
	channel := extractChannel(r)
	deviceCode := fmt.Sprintf("dev_%s_%d", channel, time.Now().UnixNano())

	r.Response.WriteJsonExit(map[string]interface{}{
		"code": 0,
		"data": map[string]interface{}{
			"device_code":               deviceCode,
			"user_code":                 "ABCD-1234",
			"verification_uri":          "https://example.com/activate",
			"verification_uri_complete": "https://example.com/activate?code=ABCD-1234",
			"expires_in":                900,
			"interval":                  5,
		},
	})
}

// OAuthStatus checks OAuth authorization status
func (c *ChannelAccountController) OAuthStatus(r *ghttp.Request) {
	r.Response.WriteJsonExit(map[string]interface{}{
		"code": 0,
		"data": map[string]interface{}{
			"status": "pending",
		},
	})
}

// extractChannel gets the channel name from the URL path
// normalizePlanType extracts a short plan type from subscription titles like "Kiro Pro" → "pro"
func normalizePlanType(subscriptionTitle string) string {
	t := strings.TrimSpace(subscriptionTitle)
	if t == "" {
		return ""
	}
	lower := strings.ToLower(t)
	// Handle "Kiro Pro", "Kiro Free", "Kiro Plus", "Kiro Ultra" etc.
	for _, plan := range []string{"ultra", "plus", "pro", "free"} {
		if strings.Contains(lower, plan) {
			return plan
		}
	}
	return lower
}

func extractChannel(r *ghttp.Request) string {
	// URL pattern: /api/{channel}/account/...
	path := r.URL.Path
	parts := strings.Split(strings.Trim(path, "/"), "/")
	if len(parts) >= 2 {
		return parts[1] // api/{channel}/...
	}
	return "kiro"
}

// RegisterChannelRoutes registers all per-channel account routes
func RegisterChannelRoutes(group *ghttp.RouterGroup) {
	ctrl := &ChannelAccountController{}
	channels := []string{"kiro", "orchids", "antigravity", "cursor", "warp", "claude_api", "grok"}

	for _, ch := range channels {
		prefix := "/" + ch + "/account"
		group.GET(prefix+"/stats", ctrl.Stats)
		group.GET(prefix+"/list", ctrl.List)
		group.POST(prefix+"/add", ctrl.Add)
		group.POST(prefix+"/delete", ctrl.Delete)
		group.POST(prefix+"/delete-batch", ctrl.DeleteBatch)
		group.POST(prefix+"/delete-abnormal", ctrl.DeleteAbnormal)
		group.POST(prefix+"/recover-abnormal", ctrl.RecoverAbnormal)
		group.POST(prefix+"/refresh", ctrl.Refresh)
		group.GET(prefix+"/export", ctrl.Export)
		group.POST(prefix+"/update-proxy", ctrl.UpdateProxy)
		group.POST(prefix+"/batch-refresh-usage", ctrl.BatchRefreshUsage)
		group.POST(prefix+"/query-usage", ctrl.QueryUsage)

		// OAuth routes (only for channels that support it)
		if ch == "kiro" {
			group.POST("/"+ch+"/oauth/authorize", ctrl.OAuthAuthorize)
			group.GET("/"+ch+"/oauth/status", ctrl.OAuthStatus)
		}
	}

	// Antigravity OAuth is at /oauth/antigravity/...
}

// ============================================================================
// Account Selection & Conversion (for chat completions routing)
// ============================================================================

// kiroRoundRobinIdx tracks the round-robin index for kiro account selection
var kiroRoundRobinIdx int

// GetNextKiroAccount selects the next available kiro account using round-robin.
// Returns the account as map[string]interface{} for use by kiro logic layer.
// Only selects accounts with status="normal" and enabled=true.
func GetNextKiroAccount() (map[string]interface{}, error) {
	chAccountMu.Lock()
	defer chAccountMu.Unlock()

	store := getChannelStore("kiro")
	if len(store) == 0 {
		return nil, fmt.Errorf("no kiro accounts available")
	}

	// Collect normal+enabled accounts
	var candidates []*ChannelAccount
	for _, acc := range store {
		if acc.Status == "normal" && acc.Enabled {
			candidates = append(candidates, acc)
		}
	}
	if len(candidates) == 0 {
		return nil, fmt.Errorf("no normal kiro accounts available")
	}

	// Round-robin selection
	idx := kiroRoundRobinIdx % len(candidates)
	kiroRoundRobinIdx++
	selected := candidates[idx]

	// Update use count and last used
	selected.UseCount++
	selected.LastUsedAt = time.Now().Format(time.RFC3339)

	return ChannelAccountToMap(selected), nil
}

// GetKiroAccountByID returns a specific kiro account by ID as map[string]interface{}.
func GetKiroAccountByID(id int) (map[string]interface{}, error) {
	chAccountMu.RLock()
	defer chAccountMu.RUnlock()

	store := getChannelStore("kiro")
	acc, ok := store[id]
	if !ok {
		return nil, fmt.Errorf("kiro account %d not found", id)
	}
	if acc.Status != "normal" || !acc.Enabled {
		return nil, fmt.Errorf("kiro account %d is not available (status=%s)", id, acc.Status)
	}
	return ChannelAccountToMap(acc), nil
}

// UpdateKiroAccountTokens writes refreshed tokens back to the in-memory store.
// Called after a successful token refresh to persist the new credentials.
func UpdateKiroAccountTokens(accountMap map[string]interface{}) {
	chAccountMu.Lock()
	defer chAccountMu.Unlock()

	store := getChannelStore("kiro")
	idFloat, _ := accountMap["id"].(int64)
	id := int(idFloat)
	acc, ok := store[id]
	if !ok {
		return
	}
	dbFields := map[string]interface{}{}
	if v, ok := accountMap["access_token"].(string); ok && v != "" {
		acc.AccessToken = v
		dbFields["access_token"] = v
	}
	if v, ok := accountMap["refresh_token"].(string); ok && v != "" {
		acc.RefreshToken = v
		dbFields["refresh_token"] = v
	}
	if v, ok := accountMap["token_expiry"].(int64); ok && v > 0 {
		acc.TokenExpiry = time.Unix(v, 0).Format(time.RFC3339)
		dbFields["token_expiry"] = acc.TokenExpiry
	}

	// Persist to database
	if len(dbFields) > 0 {
		if err := dao.ChannelAccountUpdate(id, dbFields); err != nil {
			log.Printf("[UpdateKiroAccountTokens] Failed to persist tokens for account %d: %v", id, err)
		}
	}
}

// MarkKiroAccountError marks a kiro account as abnormal with an error message.
func MarkKiroAccountError(accountMap map[string]interface{}, errMsg string) {
	chAccountMu.Lock()
	defer chAccountMu.Unlock()

	store := getChannelStore("kiro")
	idFloat, _ := accountMap["id"].(int64)
	id := int(idFloat)
	acc, ok := store[id]
	if !ok {
		return
	}
	acc.Status = "error"
	acc.ErrorMsg = errMsg

	// Persist to database
	if err := dao.ChannelAccountUpdate(id, map[string]interface{}{"status": "error", "error_msg": errMsg}); err != nil {
		log.Printf("[MarkKiroAccountError] Failed to persist error for account %d: %v", id, err)
	}
}

// ChannelAccountToMap converts a ChannelAccount struct to map[string]interface{}
// for use by the kiro logic layer which expects map-based account access.
func ChannelAccountToMap(acc *ChannelAccount) map[string]interface{} {
	m := map[string]interface{}{
		"id":            int64(acc.ID),
		"channel":       acc.Channel,
		"token":         acc.Token,
		"access_token":  acc.AccessToken,
		"refresh_token": acc.RefreshToken,
		"id_token":      acc.IDToken,
		"proxy_url":     acc.Proxy,
		"status":        acc.Status,
		"enabled":       acc.Enabled,
		"use_count":     acc.UseCount,
		"auth_method":   acc.AuthMethod,
		"client_id":     acc.ClientID,
		"client_secret": acc.ClientSecret,
		"region":        acc.Region,
		"start_url":     acc.StartURL,
	}

	// Parse token_expiry string back to int64 unix timestamp
	if acc.TokenExpiry != "" {
		if t, err := time.Parse(time.RFC3339, acc.TokenExpiry); err == nil {
			m["token_expiry"] = t.Unix()
		}
	}

	return m
}

// GlobalStats returns aggregated stats across all channels
func GlobalStats(r *ghttp.Request) {
	chAccountMu.RLock()
	totalAccounts := 0
	activeAccounts := 0
	for _, store := range chAccountStore {
		for _, acc := range store {
			totalAccounts++
			if acc.Status == "normal" && acc.Enabled {
				activeAccounts++
			}
		}
	}
	chAccountMu.RUnlock()

	r.Response.WriteJsonExit(map[string]interface{}{
		"code": 0,
		"data": map[string]interface{}{
			"total_accounts":  totalAccounts,
			"active_accounts": activeAccounts,
			"total_requests":  0,
			"success_rate":    100,
		},
	})
}
