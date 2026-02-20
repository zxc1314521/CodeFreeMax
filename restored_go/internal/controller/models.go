package controller

import (
	"kiro2api/internal/dao"
	"kiro2api/internal/logic/kiro"

	"github.com/gogf/gf/v2/net/ghttp"
)

// ModelInfo represents a single model entry in the /v1/models response.
type ModelInfo struct {
	ID         string   `json:"id"`
	Object     string   `json:"object"`
	Created    int64    `json:"created"`
	OwnedBy   string   `json:"owned_by"`
	Permission []string `json:"permission,omitempty"`
}

// ModelConfigDetail represents per-model configuration details.
type ModelConfigDetail struct {
	ChannelName string `json:"channel_name"`
	Disabled    bool   `json:"disabled"`
	ModelName   string `json:"model_name"`
	ChannelID   string `json:"channel_id"`
}

// RegisterModelsRoute registers the GET /v1/models endpoint.
// This endpoint returns the list of available models, compatible with OpenAI's /v1/models format.
func RegisterModelsRoute(r *ghttp.Request) {
	ctx := r.Context()

	// Get channel from query parameter
	channel := r.GetRequest("channel").String()

	// Fetch model configs from database
	modelConfigs, err := dao.ModelConfigDaoGetByChannel(ctx, channel)
	if err != nil {
		r.Response.WriteJson(map[string]interface{}{
			"object":        "error",
			"data":          []interface{}{},
			"model_configs": map[string]interface{}{},
		})
		return
	}

	// Build model list (OpenAI-compatible format)
	models := make([]map[string]interface{}, 0, len(modelConfigs))
	var defaultModel string

	for _, mc := range modelConfigs {
		model := map[string]interface{}{
			"id":                        mc.ModelName,
			"max_completion_tokens":     0,     // default 0
			"max_prompt_tokens":         0,     // default 0
			"context_window_tokens":     65536, // 0x10000
			"owned_by":                  mc.ChannelName,
			"supports": []string{
				"chat", "code", "edit", "complete", // 4 items
			},
		}
		models = append(models, model)

		// Track default model (first one with is_default=true)
		if mc.IsDefault {
			defaultModel = mc.ModelName
		}
	}

	// If no default found, use first model
	if defaultModel == "" && len(modelConfigs) > 0 {
		defaultModel = modelConfigs[0].ModelName
	}

	// Build channel_models map: channel_name -> model_name mapping
	channelModels := make(map[string]string)

	// Append dynamically discovered Kiro models from AWS ListAvailableModels API
	awsModels, awsDefault := kiro.GetCachedModels()
	for _, am := range awsModels {
		// Skip if already in the list
		found := false
		for _, existing := range models {
			if existing["id"] == am.ModelID {
				found = true
				break
			}
		}
		if !found {
			models = append(models, map[string]interface{}{
				"id":                    am.ModelID,
				"max_completion_tokens": 0,
				"max_prompt_tokens":     0,
				"context_window_tokens": 200000,
				"owned_by":              "kiro",
				"description":           am.Description,
				"supports":              []string{"chat", "code", "edit", "complete"},
			})
			channelModels[am.ModelID] = "kiro"
		}
	}
	if awsDefault != nil && defaultModel == "" {
		defaultModel = awsDefault.ModelID
	}
	// Build model_details map: model_name -> detail
	modelDetails := make(map[string]map[string]interface{})

	for _, mc := range modelConfigs {
		channelModels[mc.ModelName] = mc.ChannelName

		detail := map[string]interface{}{
			"channel_name": mc.ChannelName,
			"disabled":     !mc.Disabled, // inverted
			"model_name":   mc.ModelName,
			"channel_id":   mc.ChannelID,
		}
		modelDetails[mc.ModelName] = detail
	}

	// Build response
	response := map[string]interface{}{
		"object":                 defaultModel,
		"data":                   models,
		"supports_vision":       true,
		"supports_streaming":    true,
		"channel_models":        channelModels,
		"model_details":         channelModels,
		"model_channel_details": modelDetails,
		"channel_model_details": modelDetails,
		"default_model":         defaultModel,
		"internal_name":         defaultModel,
		"supports_vision_flag":  true,
		"supports_stream_flag":  true,
		"model_configs":         models,
	}

	r.Response.WriteJson(response)
}

// RegisterChannelModelsRoute handles GET /{channel}/v1/models — returns enabled models for a specific channel.
func RegisterChannelModelsRoute(r *ghttp.Request, channel string) {
	ctx := r.Context()

	channelModels, err := dao.ChannelModelList(ctx, channel)
	if err != nil {
		r.Response.WriteJson(map[string]interface{}{
			"object": "list",
			"data":   []interface{}{},
		})
		return
	}

	models := make([]map[string]interface{}, 0, len(channelModels))
	for _, cm := range channelModels {
		if !cm.Enabled {
			continue
		}
		models = append(models, map[string]interface{}{
			"id":       cm.ModelID,
			"object":   "model",
			"created":  1700000000,
			"owned_by": cm.OwnedBy,
		})
	}

	r.Response.WriteJson(map[string]interface{}{
		"object": "list",
		"data":   models,
	})
}
