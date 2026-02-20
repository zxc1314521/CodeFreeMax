package controller

import (
	"kiro2api/internal/dao"
	"kiro2api/internal/tokencount"

	"github.com/gogf/gf/v2/net/ghttp"
)

// ConfigController handles configuration management endpoints.
type ConfigController struct{}

// ConfigSaveReq represents the request body for saving configuration.
type ConfigSaveReq struct {
	AdminPassword             string `json:"admin_password"`
	ApiKey                    string `json:"api_key"`
	Channel                   string `json:"channel"`
	ConfigKey                 string `json:"config_key"`
	ConfigValue               string `json:"config_value"`
	RefreshInterval           string `json:"refresh_interval"`
	CursorProxyURL            string `json:"cursor_proxy_url"`
	AgentChatModel            string `json:"agent_chat_model"`
	OverloadedError           string `json:"overloaded_error"`
	EnableTokenRefresh        string `json:"enable_token_refresh"`
	EnableUsageRefresh        string `json:"enable_usage_refresh"`
	EnableTokenCount          string `json:"enable_token_count"`
	EnableTokenCache          string `json:"enable_token_cache"`
	WarpCreditRefund          string `json:"warp_credit_refund"`
	OrchidsTransportMode      string `json:"orchids_transport_mode"`
	KiroUseBuiltinProxy       string `json:"kiro_use_builtin_proxy"`
	WarpUseBuiltinProxy       string `json:"warp_use_builtin_proxy"`
	OrchidsUseBuiltinProxy    string `json:"orchids_use_builtin_proxy"`
	GrokMediaMaxConcurrent    string `json:"grok_media_max_concurrent"`
	CredentialRetries         string `json:"credential_retries"`
	AutoRefreshToken          string `json:"auto_refresh_token"`
	DefaultModel              string `json:"default_model"`
	FeatureFlags              string `json:"feature_flags"`
	InternalName              string `json:"internal_name"`
	AntigravityUseBuiltinProxy string `json:"antigravity_use_builtin_proxy"`
	AntigravityProxyURL       string `json:"antigravity_proxy_url"`
	OrchidsProxyURL           string `json:"orchids_proxy_url"`
	// Fields used by frontend
	MaxRetries            string `json:"max_retries"`
	RetryDelay            string `json:"retry_delay"`
	RequestTimeout        string `json:"request_timeout"`
	TokenCacheTtl         string `json:"token_cache_ttl"`
	TokenCacheStrategy    string `json:"token_cache_strategy"`
	KiroProxyURL          string `json:"kiro_proxy_url"`
	WarpProxyURL          string `json:"warp_proxy_url"`
	GrokProxyURL          string `json:"grok_proxy_url"`
	ProxyURL              string `json:"proxy_url"`
	EnableContextCompress string `json:"enable_context_compress"`
}

// Save handles POST /api/config/save — batch saves configuration key-value pairs.
func (c *ConfigController) Save(r *ghttp.Request) {
	var req ConfigSaveReq
	if err := r.Parse(&req); err != nil {
		r.Response.WriteJson(map[string]interface{}{
			"code": 1,
			"msg":  "parse request failed: " + err.Error(),
		})
		return
	}

	ctx := r.Context()

	// Build config map — only save non-empty fields (except api_key which can be empty)
	configMap := make(map[string]string)

	// API key: empty means "no auth", so always save
	configMap["api_key"] = req.ApiKey

	// All other fields: only save when non-empty
	optionalFields := map[string]string{
		"admin_password":               req.AdminPassword,
		"channel":                      req.Channel,
		"config_key":                   req.ConfigKey,
		"config_value":                 req.ConfigValue,
		"refresh_interval":             req.RefreshInterval,
		"cursor_proxy_url":             req.CursorProxyURL,
		"agent_chat_model":             req.AgentChatModel,
		"overloaded_error":             req.OverloadedError,
		"enable_token_refresh":         req.EnableTokenRefresh,
		"enable_usage_refresh":         req.EnableUsageRefresh,
		"enable_token_count":           req.EnableTokenCount,
		"enable_token_cache":           req.EnableTokenCache,
		"warp_credit_refund":           req.WarpCreditRefund,
		"orchids_transport_mode":       req.OrchidsTransportMode,
		"kiro_use_builtin_proxy":       req.KiroUseBuiltinProxy,
		"warp_use_builtin_proxy":       req.WarpUseBuiltinProxy,
		"orchids_use_builtin_proxy":    req.OrchidsUseBuiltinProxy,
		"grok_media_max_concurrent":    req.GrokMediaMaxConcurrent,
		"credential_retries":           req.CredentialRetries,
		"auto_refresh_token":           req.AutoRefreshToken,
		"default_model":                req.DefaultModel,
		"feature_flags":                req.FeatureFlags,
		"internal_name":                req.InternalName,
		"antigravity_use_builtin_proxy": req.AntigravityUseBuiltinProxy,
		"antigravity_proxy_url":        req.AntigravityProxyURL,
		"orchids_proxy_url":            req.OrchidsProxyURL,
		// Frontend-specific fields
		"max_retries":              req.MaxRetries,
		"retry_delay":              req.RetryDelay,
		"request_timeout":          req.RequestTimeout,
		"token_cache_ttl":          req.TokenCacheTtl,
		"token_cache_strategy":     req.TokenCacheStrategy,
		"kiro_proxy_url":           req.KiroProxyURL,
		"warp_proxy_url":           req.WarpProxyURL,
		"grok_proxy_url":           req.GrokProxyURL,
		"proxy_url":                req.ProxyURL,
		"enable_context_compress":  req.EnableContextCompress,
	}
	for k, v := range optionalFields {
		if v != "" {
			configMap[k] = v
		}
	}

	// Save batch config
	err := dao.ConfigDaoSetBatch(ctx, configMap)
	if err != nil {
		r.Response.WriteJson(map[string]interface{}{
			"code": 1,
			"msg":  "save config failed: " + err.Error(),
		})
		return
	}

	// Clear config cache after successful save
	tokencount.ClearConfigCache()

	// Update in-memory auth values
	if req.AdminPassword != "" {
		UpdateAdminPass(req.AdminPassword)
	}
	UpdateApiKey(req.ApiKey)

	r.Response.WriteJson(map[string]interface{}{
		"code": 0,
		"msg":  "success",
	})
}

// List handles GET /api/config/list — returns all configuration.
func (c *ConfigController) List(r *ghttp.Request) {
	ctx := r.Context()
	configs, err := dao.ConfigDaoGetAll(ctx)
	if err != nil {
		r.Response.WriteJsonExit(map[string]interface{}{
			"code": 1,
			"msg":  "获取配置失败: " + err.Error(),
		})
		return
	}
	r.Response.WriteJsonExit(map[string]interface{}{
		"code": 0,
		"data": configs,
	})
}
