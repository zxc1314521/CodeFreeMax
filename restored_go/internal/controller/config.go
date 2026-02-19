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
	Channel                   string `json:"channel"`                      // len 7
	ConfigKey                 string `json:"config_key"`                   // len 9 (unused in batch)
	ConfigValue               string `json:"config_value"`                 // len 0xb = 11 (unused in batch)
	RefreshInterval           string `json:"refresh_interval"`             // len 0x10 = 16
	CursorProxyURL            string `json:"cursor_proxy_url"`             // len 0x10 = 16
	AgentChatModel            string `json:"agent_chat_model"`             // len 0x10 = 16
	OverloadedError           string `json:"overloaded_error"`             // len 0xf = 15
	EnableTokenRefresh        string `json:"enable_token_refresh"`         // len 0x14 = 20
	EnableUsageRefresh        string `json:"enable_usage_refresh"`         // len 0x14 = 20
	EnableTokenCount          string `json:"enable_token_count"`           // len 0x12 = 18
	EnableTokenCache          string `json:"enable_token_cache"`           // len 0x12 = 18
	WarpCreditRefund          string `json:"warp_credit_refund"`           // len 0x12 = 18
	OrchidsTransportMode      string `json:"orchids_transport_mode"`       // len 0x16 = 22
	KiroUseBuiltinProxy       string `json:"kiro_use_builtin_proxy"`       // len 0x17 = 23
	WarpUseBuiltinProxy       string `json:"warp_use_builtin_proxy"`       // len 0x17 = 23
	OrchidsUseBuiltinProxy    string `json:"orchids_use_builtin_proxy"`    // len 0x19 = 25
	GrokMediaMaxConcurrent    string `json:"grok_media_max_concurrent"`    // len 0x1d = 29
	CredentialRetries         string `json:"credential_retries"`           // len 0x14 = 20
	AutoRefreshToken          string `json:"auto_refresh_token"`           // len 0x12 = 18
	DefaultModel              string `json:"default_model"`                // len 0xd = 13
	FeatureFlags              string `json:"feature_flags"`                // len 0xd = 13
	InternalName              string `json:"internal_name"`                // len 0xd = 13
	AntigravityUseBuiltinProxy string `json:"antigravity_use_builtin_proxy"` // len 0x1e = 30
	AntigravityProxyURL       string `json:"antigravity_proxy_url"`        // len 0x16 = 22
	OrchidsProxyURL           string `json:"orchids_proxy_url"`            // len 0x16 = 22
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

	// Build config map from non-empty fields
	configMap := make(map[string]string)

	if req.Channel != "" {
		configMap["channel"] = req.Channel // len 7
	}
	// config_key is always set (len 9)
	configMap["config_key"] = req.ConfigKey

	if req.ConfigValue != "" {
		configMap["config_value"] = req.ConfigValue // len 0xb
	}
	if req.RefreshInterval != "" {
		configMap["refresh_interval"] = req.RefreshInterval // len 0x10
	}
	if req.CursorProxyURL != "" {
		configMap["cursor_proxy_url"] = req.CursorProxyURL // len 0x10
	}
	if req.AgentChatModel != "" {
		configMap["agent_chat_model"] = req.AgentChatModel // len 0x10
	}
	if req.OverloadedError != "" {
		configMap["overloaded_error"] = req.OverloadedError // len 0xf
	}
	if req.EnableTokenRefresh != "" {
		configMap["enable_token_refresh"] = req.EnableTokenRefresh // len 0x14
	}
	if req.EnableUsageRefresh != "" {
		configMap["enable_usage_refresh"] = req.EnableUsageRefresh // len 0x14
	}
	if req.EnableTokenCount != "" {
		configMap["enable_token_count"] = req.EnableTokenCount // len 0x12
	}
	if req.EnableTokenCache != "" {
		configMap["enable_token_cache"] = req.EnableTokenCache // len 0x12
	}
	if req.WarpCreditRefund != "" {
		configMap["warp_credit_refund"] = req.WarpCreditRefund // len 0x12
	}
	if req.OrchidsTransportMode != "" {
		configMap["orchids_transport_mode"] = req.OrchidsTransportMode // len 0x16
	}
	if req.KiroUseBuiltinProxy != "" {
		configMap["kiro_use_builtin_proxy"] = req.KiroUseBuiltinProxy // len 0x17
	}
	if req.WarpUseBuiltinProxy != "" {
		configMap["warp_use_builtin_proxy"] = req.WarpUseBuiltinProxy // len 0x17
	}
	if req.OrchidsUseBuiltinProxy != "" {
		configMap["orchids_use_builtin_proxy"] = req.OrchidsUseBuiltinProxy // len 0x19
	}
	if req.GrokMediaMaxConcurrent != "" {
		configMap["grok_media_max_concurrent"] = req.GrokMediaMaxConcurrent // len 0x1d
	}
	if req.CredentialRetries != "" {
		configMap["credential_retries"] = req.CredentialRetries
	}
	if req.AutoRefreshToken != "" {
		configMap["auto_refresh_token"] = req.AutoRefreshToken
	}
	// default_model and feature_flags are always set
	configMap["default_model"] = req.DefaultModel   // len 0xd
	configMap["feature_flags"] = req.FeatureFlags   // len 0x11
	if req.AntigravityUseBuiltinProxy != "" {
		configMap["antigravity_use_builtin_proxy"] = req.AntigravityUseBuiltinProxy // len 0x16
	}
	configMap["internal_name"] = req.InternalName     // len 0x15
	configMap["default_model"] = req.DefaultModel     // len 0x10
	configMap["overloaded_error"] = req.OverloadedError // len 0xe
	if req.AntigravityProxyURL != "" {
		configMap["antigravity_proxy_url"] = req.AntigravityProxyURL
	}
	if req.OrchidsProxyURL != "" {
		configMap["orchids_proxy_url"] = req.OrchidsProxyURL
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

	r.Response.WriteJson(map[string]interface{}{
		"code": 0,
		"msg":  "success",
	})
}
