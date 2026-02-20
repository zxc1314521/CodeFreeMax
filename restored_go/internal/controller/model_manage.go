package controller

import (
	"kiro2api/internal/dao"

	"github.com/gogf/gf/v2/net/ghttp"
)

// ModelManageController handles model management endpoints.
type ModelManageController struct{}

// List handles GET /api/models/list — returns all models grouped by channel with full details.
func (c *ModelManageController) List(r *ghttp.Request) {
	ctx := r.Context()
	channel := r.GetQuery("channel").String()

	var models []dao.ChannelModel
	var err error
	if channel != "" {
		models, err = dao.ChannelModelList(ctx, channel)
	} else {
		models, err = dao.ChannelModelListAll(ctx)
	}

	if err != nil {
		r.Response.WriteJsonExit(map[string]interface{}{
			"code": 1,
			"msg":  "获取模型列表失败: " + err.Error(),
		})
		return
	}

	// Group by channel with full details
	grouped := make(map[string][]map[string]interface{})
	for _, m := range models {
		grouped[m.Channel] = append(grouped[m.Channel], map[string]interface{}{
			"id":         m.ID,
			"model_id":   m.ModelID,
			"name":       m.Name,
			"owned_by":   m.OwnedBy,
			"is_default": m.IsDefault,
			"enabled":    m.Enabled,
			"sort_order": m.SortOrder,
		})
	}

	r.Response.WriteJsonExit(map[string]interface{}{
		"code": 0,
		"data": grouped,
	})
}

// Save handles POST /api/models/save — creates or updates a single model.
func (c *ModelManageController) Save(r *ghttp.Request) {
	var req struct {
		ID        int64  `json:"id"`
		Channel   string `json:"channel"`
		ModelID   string `json:"model_id"`
		Name      string `json:"name"`
		OwnedBy   string `json:"owned_by"`
		IsDefault bool   `json:"is_default"`
		Enabled   bool   `json:"enabled"`
		SortOrder int    `json:"sort_order"`
	}
	if err := r.Parse(&req); err != nil {
		r.Response.WriteJsonExit(map[string]interface{}{
			"code": 1,
			"msg":  "参数解析失败: " + err.Error(),
		})
		return
	}

	if req.Channel == "" || req.ModelID == "" {
		r.Response.WriteJsonExit(map[string]interface{}{
			"code": 1,
			"msg":  "channel 和 model_id 不能为空",
		})
		return
	}

	ctx := r.Context()
	model := &dao.ChannelModel{
		ID:        req.ID,
		Channel:   req.Channel,
		ModelID:   req.ModelID,
		Name:      req.Name,
		OwnedBy:   req.OwnedBy,
		IsDefault: req.IsDefault,
		Enabled:   req.Enabled,
		SortOrder: req.SortOrder,
	}

	if err := dao.ChannelModelSave(ctx, model); err != nil {
		r.Response.WriteJsonExit(map[string]interface{}{
			"code": 1,
			"msg":  "保存失败: " + err.Error(),
		})
		return
	}

	r.Response.WriteJsonExit(map[string]interface{}{
		"code": 0,
		"msg":  "保存成功",
	})
}

// Delete handles POST /api/models/delete — deletes a model by id.
func (c *ModelManageController) Delete(r *ghttp.Request) {
	var req struct {
		ID int64 `json:"id"`
	}
	if err := r.Parse(&req); err != nil {
		r.Response.WriteJsonExit(map[string]interface{}{
			"code": 1,
			"msg":  "参数解析失败: " + err.Error(),
		})
		return
	}

	ctx := r.Context()
	if err := dao.ChannelModelDelete(ctx, req.ID); err != nil {
		r.Response.WriteJsonExit(map[string]interface{}{
			"code": 1,
			"msg":  "删除失败: " + err.Error(),
		})
		return
	}

	r.Response.WriteJsonExit(map[string]interface{}{
		"code": 0,
		"msg":  "删除成功",
	})
}

// Toggle handles POST /api/models/toggle — toggles enabled status.
func (c *ModelManageController) Toggle(r *ghttp.Request) {
	var req struct {
		ID      int64 `json:"id"`
		Enabled bool  `json:"enabled"`
	}
	if err := r.Parse(&req); err != nil {
		r.Response.WriteJsonExit(map[string]interface{}{
			"code": 1,
			"msg":  "参数解析失败: " + err.Error(),
		})
		return
	}

	ctx := r.Context()
	if err := dao.ChannelModelToggleEnabled(ctx, req.ID, req.Enabled); err != nil {
		r.Response.WriteJsonExit(map[string]interface{}{
			"code": 1,
			"msg":  "更新失败: " + err.Error(),
		})
		return
	}

	r.Response.WriteJsonExit(map[string]interface{}{
		"code": 0,
		"msg":  "更新成功",
	})
}
