package dao

import (
	"context"
	"log"
	"time"

	"gorm.io/gorm"
)

// ChannelModel represents a model entry for a specific channel.
type ChannelModel struct {
	ID        int64     `json:"id" gorm:"primaryKey;autoIncrement"`
	Channel   string    `json:"channel" gorm:"index;size:50;not null"`
	ModelID   string    `json:"model_id" gorm:"size:200;not null"`
	Name      string    `json:"name" gorm:"size:200"`
	OwnedBy   string    `json:"owned_by" gorm:"size:100"`
	IsDefault bool      `json:"is_default" gorm:"default:false"`
	Enabled   bool      `json:"enabled" gorm:"default:true"`
	SortOrder int       `json:"sort_order" gorm:"default:0"`
	CreatedAt time.Time `json:"created_at" gorm:"autoCreateTime"`
	UpdatedAt time.Time `json:"updated_at" gorm:"autoUpdateTime"`
}

func (ChannelModel) TableName() string {
	return "channel_models"
}

// MigrateChannelModels creates the table and seeds default data.
// Also auto-inserts any missing models from the default list.
func MigrateChannelModels(database *gorm.DB) {
	err := database.AutoMigrate(&ChannelModel{})
	if err != nil {
		log.Printf("[ChannelModelDAO] Failed to migrate: %v", err)
		return
	}

	var count int64
	database.Model(&ChannelModel{}).Count(&count)
	if count == 0 {
		models := defaultChannelModels()
		database.Create(&models)
		log.Printf("[ChannelModelDAO] Seeded %d default channel models", len(models))
		return
	}

	// Auto-insert missing models from default list
	defaults := defaultChannelModels()
	inserted := 0
	for _, dm := range defaults {
		var exists int64
		database.Model(&ChannelModel{}).
			Where("channel = ? AND model_id = ?", dm.Channel, dm.ModelID).
			Count(&exists)
		if exists == 0 {
			dm.ID = 0 // let auto-increment assign
			if err := database.Create(&dm).Error; err != nil {
				log.Printf("[ChannelModelDAO] Failed to insert %s/%s: %v", dm.Channel, dm.ModelID, err)
			} else {
				inserted++
				log.Printf("[ChannelModelDAO] Auto-inserted missing model: %s/%s", dm.Channel, dm.ModelID)
			}
		}
	}
	if inserted > 0 {
		log.Printf("[ChannelModelDAO] Auto-inserted %d missing models", inserted)
	}
}

func defaultChannelModels() []ChannelModel {
	i := 0
	m := func(channel, modelID, name, ownedBy string, isDefault bool) ChannelModel {
		i++
		return ChannelModel{
			Channel:   channel,
			ModelID:   modelID,
			Name:      name,
			OwnedBy:   ownedBy,
			IsDefault: isDefault,
			Enabled:   true,
			SortOrder: i,
		}
	}

	return []ChannelModel{
		// Kiro
		m("kiro", "claude-opus-4-6", "Claude Opus 4.6", "kiro", true),
		m("kiro", "claude-sonnet-4-5", "Claude Sonnet 4.5", "kiro", false),
		m("kiro", "claude-sonnet-4", "Claude Sonnet 4", "kiro", false),
		m("kiro", "claude-opus-4", "Claude Opus 4", "kiro", false),
		m("kiro", "claude-haiku-4", "Claude Haiku 4", "kiro", false),
		m("kiro", "claude-3-5-sonnet", "Claude 3.5 Sonnet", "kiro", false),
		m("kiro", "claude-3-5-haiku", "Claude 3.5 Haiku", "kiro", false),

		// Orchids
		m("orchids", "claude-opus-4-6", "Claude Opus 4.6", "orchids", true),
		m("orchids", "claude-sonnet-4-5", "Claude Sonnet 4.5", "orchids", false),
		m("orchids", "claude-sonnet-4", "Claude Sonnet 4", "orchids", false),
		m("orchids", "claude-opus-4", "Claude Opus 4", "orchids", false),
		m("orchids", "claude-haiku-4", "Claude Haiku 4", "orchids", false),
		m("orchids", "claude-3-5-sonnet", "Claude 3.5 Sonnet", "orchids", false),
		m("orchids", "claude-3-5-haiku", "Claude 3.5 Haiku", "orchids", false),

		// Antigravity
		m("antigravity", "gemini-2.5-pro", "Gemini 2.5 Pro", "antigravity", true),
		m("antigravity", "gemini-2.5-flash", "Gemini 2.5 Flash", "antigravity", false),
		m("antigravity", "gemini-2.5-flash-preview", "Gemini 2.5 Flash Preview", "antigravity", false),
		m("antigravity", "gemini-2.0-flash", "Gemini 2.0 Flash", "antigravity", false),
		m("antigravity", "gemini-2.0-flash-lite", "Gemini 2.0 Flash Lite", "antigravity", false),

		// Cursor
		m("cursor", "claude-4-5-sonnet", "Claude 4.5 Sonnet", "cursor", true),
		m("cursor", "claude-4-sonnet", "Claude 4 Sonnet", "cursor", false),
		m("cursor", "claude-3.5-sonnet", "Claude 3.5 Sonnet", "cursor", false),
		m("cursor", "gpt-4o", "GPT-4o", "cursor", false),
		m("cursor", "gpt-4.1", "GPT-4.1", "cursor", false),
		m("cursor", "gpt-4.1-mini", "GPT-4.1 Mini", "cursor", false),
		m("cursor", "o3", "O3", "cursor", false),
		m("cursor", "o4-mini", "O4 Mini", "cursor", false),
		m("cursor", "gemini-2.5-pro", "Gemini 2.5 Pro", "cursor", false),
		m("cursor", "gemini-2.5-flash", "Gemini 2.5 Flash", "cursor", false),
		m("cursor", "cursor-small", "Cursor Small", "cursor", false),

		// Warp
		m("warp", "claude-sonnet-4-5", "Claude Sonnet 4.5", "warp", true),
		m("warp", "claude-sonnet-4", "Claude Sonnet 4", "warp", false),
		m("warp", "claude-opus-4", "Claude Opus 4", "warp", false),
		m("warp", "claude-haiku-4", "Claude Haiku 4", "warp", false),
		m("warp", "claude-3-5-sonnet", "Claude 3.5 Sonnet", "warp", false),
		m("warp", "claude-3-5-haiku", "Claude 3.5 Haiku", "warp", false),

		// Claude API
		m("claude_api", "claude-sonnet-4-5", "Claude Sonnet 4.5", "claude_api", true),
		m("claude_api", "claude-sonnet-4", "Claude Sonnet 4", "claude_api", false),
		m("claude_api", "claude-opus-4", "Claude Opus 4", "claude_api", false),
		m("claude_api", "claude-haiku-4", "Claude Haiku 4", "claude_api", false),
		m("claude_api", "claude-3-5-sonnet", "Claude 3.5 Sonnet", "claude_api", false),
		m("claude_api", "claude-3-5-haiku", "Claude 3.5 Haiku", "claude_api", false),

		// Grok
		m("grok", "grok-4", "Grok 4", "grok", true),
		m("grok", "grok-4.1-fast", "Grok 4.1 Fast", "grok", false),
		m("grok", "grok-4.1-mini-fast", "Grok 4.1 Mini Fast", "grok", false),
		m("grok", "grok-4.1-thinking", "Grok 4.1 Thinking", "grok", false),
		m("grok", "grok-3", "Grok 3", "grok", false),
		m("grok", "grok-3-fast", "Grok 3 Fast", "grok", false),
		m("grok", "grok-3-mini", "Grok 3 Mini", "grok", false),
		m("grok", "grok-imagine-1.0", "Grok Imagine 1.0", "grok", false),
		m("grok", "grok-imagine-1.0-video", "Grok Imagine Video", "grok", false),
	}
}

// ChannelModelList returns all models for a given channel.
func ChannelModelList(ctx context.Context, channel string) ([]ChannelModel, error) {
	var list []ChannelModel
	q := db.WithContext(ctx).Order("sort_order ASC, id ASC")
	if channel != "" {
		q = q.Where("channel = ?", channel)
	}
	err := q.Find(&list).Error
	return list, err
}

// ChannelModelListAll returns all models.
func ChannelModelListAll(ctx context.Context) ([]ChannelModel, error) {
	var list []ChannelModel
	err := db.WithContext(ctx).Order("channel ASC, sort_order ASC, id ASC").Find(&list).Error
	return list, err
}

// ChannelModelGetByID returns a single model by ID.
func ChannelModelGetByID(ctx context.Context, id int64) (*ChannelModel, error) {
	var m ChannelModel
	err := db.WithContext(ctx).First(&m, id).Error
	if err != nil {
		return nil, err
	}
	return &m, nil
}

// ChannelModelSave creates or updates a single model.
func ChannelModelSave(ctx context.Context, model *ChannelModel) error {
	if model.ID > 0 {
		return db.WithContext(ctx).Save(model).Error
	}
	return db.WithContext(ctx).Create(model).Error
}

// ChannelModelBatchSave replaces all models for a given channel.
func ChannelModelBatchSave(ctx context.Context, channel string, models []ChannelModel) error {
	return db.WithContext(ctx).Transaction(func(tx *gorm.DB) error {
		if err := tx.Where("channel = ?", channel).Delete(&ChannelModel{}).Error; err != nil {
			return err
		}
		if len(models) > 0 {
			return tx.Create(&models).Error
		}
		return nil
	})
}

// ChannelModelDelete deletes a model by id.
func ChannelModelDelete(ctx context.Context, id int64) error {
	return db.WithContext(ctx).Delete(&ChannelModel{}, id).Error
}

// ChannelModelToggleEnabled toggles the enabled status of a model.
func ChannelModelToggleEnabled(ctx context.Context, id int64, enabled bool) error {
	return db.WithContext(ctx).Model(&ChannelModel{}).Where("id = ?", id).Update("enabled", enabled).Error
}
