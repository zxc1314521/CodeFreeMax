package controller

import (
	"kiro2api/internal/dao"

	"github.com/gogf/gf/v2/net/ghttp"
)

// TutorialController handles tutorial channel configuration endpoints.
type TutorialController struct{}

// List handles GET /api/tutorial/channels — returns all tutorial channels and examples.
func (c *TutorialController) List(r *ghttp.Request) {
	ctx := r.Context()
	channels, err := dao.TutorialChannelList(ctx)
	if err != nil {
		r.Response.WriteJsonExit(map[string]interface{}{
			"code": 1,
			"msg":  "获取教程渠道列表失败: " + err.Error(),
		})
		return
	}

	examples, err := dao.TutorialExampleList(ctx)
	if err != nil {
		r.Response.WriteJsonExit(map[string]interface{}{
			"code": 1,
			"msg":  "获取教程示例失败: " + err.Error(),
		})
		return
	}

	r.Response.WriteJsonExit(map[string]interface{}{
		"code": 0,
		"data": map[string]interface{}{
			"channels": channels,
			"examples": examples,
		},
	})
}

// Save handles POST /api/tutorial/channels/save — batch saves tutorial channels and examples.
func (c *TutorialController) Save(r *ghttp.Request) {
	var req struct {
		Channels []dao.TutorialChannel `json:"channels"`
		Examples []dao.TutorialExample `json:"examples"`
	}
	if err := r.Parse(&req); err != nil {
		r.Response.WriteJsonExit(map[string]interface{}{
			"code": 1,
			"msg":  "参数解析失败: " + err.Error(),
		})
		return
	}

	ctx := r.Context()

	// Set sort_order for channels based on array index if not provided
	for i := range req.Channels {
		if req.Channels[i].SortOrder == 0 {
			req.Channels[i].SortOrder = i + 1
		}
	}

	if len(req.Channels) > 0 {
		if err := dao.TutorialChannelBatchSave(ctx, req.Channels); err != nil {
			r.Response.WriteJsonExit(map[string]interface{}{
				"code": 1,
				"msg":  "保存渠道失败: " + err.Error(),
			})
			return
		}
	}

	if len(req.Examples) > 0 {
		for i := range req.Examples {
			if req.Examples[i].SortOrder == 0 {
				req.Examples[i].SortOrder = i + 1
			}
		}
		if err := dao.TutorialExampleBatchSave(ctx, req.Examples); err != nil {
			r.Response.WriteJsonExit(map[string]interface{}{
				"code": 1,
				"msg":  "保存示例失败: " + err.Error(),
			})
			return
		}
	}

	r.Response.WriteJsonExit(map[string]interface{}{
		"code": 0,
		"msg":  "保存成功",
	})
}

// Delete handles POST /api/tutorial/channels/delete — deletes a tutorial channel.
func (c *TutorialController) Delete(r *ghttp.Request) {
	var req struct {
		ID int64 `json:"id"`
	}
	if err := r.Parse(&req); err != nil || req.ID == 0 {
		r.Response.WriteJsonExit(map[string]interface{}{
			"code": 1,
			"msg":  "参数错误",
		})
		return
	}

	ctx := r.Context()
	if err := dao.TutorialChannelDelete(ctx, req.ID); err != nil {
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
