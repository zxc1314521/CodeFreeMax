package dao

import (
	"context"
	"log"
	"time"

	"gorm.io/gorm"
)

// TutorialChannel represents a channel entry in the tutorial page.
type TutorialChannel struct {
	ID             int64     `json:"id" gorm:"primaryKey;autoIncrement"`
	Key            string    `json:"key" gorm:"uniqueIndex;size:50;not null"`
	Name           string    `json:"name" gorm:"size:100;not null"`
	Enabled        bool      `json:"enabled" gorm:"default:true"`
	DefaultModel   string    `json:"default_model" gorm:"size:100"`
	ClaudeProtocol bool      `json:"claude_protocol" gorm:"default:false"`
	OpenaiProtocol bool      `json:"openai_protocol" gorm:"default:false"`
	SortOrder      int       `json:"sort_order" gorm:"default:0"`
	CreatedAt      time.Time `json:"created_at" gorm:"autoCreateTime"`
	UpdatedAt      time.Time `json:"updated_at" gorm:"autoUpdateTime"`
}

func (TutorialChannel) TableName() string {
	return "tutorial_channels"
}

// TutorialExample represents a protocol example for a channel.
// For most channels there are 1-2 examples (claude/openai).
// For Grok there are multiple sub-tabs (chat, image, video, image2video).
type TutorialExample struct {
	ID         int64     `json:"id" gorm:"primaryKey;autoIncrement"`
	ChannelKey string    `json:"channel_key" gorm:"index;size:50;not null"`
	Protocol   string    `json:"protocol" gorm:"size:20;not null"` // "claude" or "openai"
	TabKey     string    `json:"tab_key" gorm:"size:50"`           // e.g. "chat", "image", "video", "image2video" (for Grok)
	TabLabel   string    `json:"tab_label" gorm:"size:100"`        // e.g. "文字对话", "图片生成"
	Content    string    `json:"content" gorm:"type:text;not null"` // curl example content
	SortOrder  int       `json:"sort_order" gorm:"default:0"`
	CreatedAt  time.Time `json:"created_at" gorm:"autoCreateTime"`
	UpdatedAt  time.Time `json:"updated_at" gorm:"autoUpdateTime"`
}

func (TutorialExample) TableName() string {
	return "tutorial_examples"
}

// MigrateTutorialChannels creates tables and seeds default data.
func MigrateTutorialChannels(database *gorm.DB) {
	err := database.AutoMigrate(&TutorialChannel{}, &TutorialExample{})
	if err != nil {
		log.Printf("[TutorialDAO] Failed to migrate tutorial tables: %v", err)
		return
	}

	// Seed channels if empty
	var chCount int64
	database.Model(&TutorialChannel{}).Count(&chCount)
	if chCount == 0 {
		channels := []TutorialChannel{
			{Key: "kiro", Name: "Kiro", Enabled: true, DefaultModel: "claude-sonnet-4-5", ClaudeProtocol: true, OpenaiProtocol: true, SortOrder: 1},
			{Key: "orchids", Name: "Orchids", Enabled: true, DefaultModel: "claude-sonnet-4-5", ClaudeProtocol: true, OpenaiProtocol: true, SortOrder: 2},
			{Key: "antigravity", Name: "Antigravity", Enabled: true, DefaultModel: "gemini-2.5-flash-preview", ClaudeProtocol: true, OpenaiProtocol: true, SortOrder: 3},
			{Key: "cursor", Name: "Cursor", Enabled: true, DefaultModel: "claude-4.5-sonnet", ClaudeProtocol: false, OpenaiProtocol: true, SortOrder: 4},
			{Key: "warp", Name: "Warp", Enabled: true, DefaultModel: "claude-4-5-sonnet", ClaudeProtocol: true, OpenaiProtocol: true, SortOrder: 5},
			{Key: "claude_api", Name: "Claude API", Enabled: true, DefaultModel: "claude-sonnet-4-5", ClaudeProtocol: true, OpenaiProtocol: false, SortOrder: 6},
			{Key: "grok", Name: "Grok", Enabled: true, DefaultModel: "grok-4.1-fast", ClaudeProtocol: false, OpenaiProtocol: true, SortOrder: 7},
		}
		database.Create(&channels)
		log.Printf("[TutorialDAO] Seeded %d default tutorial channels", len(channels))
	}

	// Seed examples if empty
	var exCount int64
	database.Model(&TutorialExample{}).Count(&exCount)
	if exCount == 0 {
		examples := defaultTutorialExamples()
		database.Create(&examples)
		log.Printf("[TutorialDAO] Seeded %d default tutorial examples", len(examples))
	}
}

func defaultTutorialExamples() []TutorialExample {
	// Use {baseUrl} as placeholder — frontend will replace it with window.location.origin
	return []TutorialExample{
		// Claude protocol examples
		{ChannelKey: "kiro", Protocol: "claude", Content: `curl -X POST {baseUrl}/kiro/v1/messages \
  -H "Content-Type: application/json" \
  -H "x-api-key: YOUR_API_KEY" \
  -d '{
    "model": "claude-sonnet-4-5",
    "max_tokens": 4096,
    "stream": true,
    "messages": [
      {"role": "user", "content": "Hello, who are you?"}
    ]
  }'`, SortOrder: 1},
		{ChannelKey: "warp", Protocol: "claude", Content: `curl -X POST {baseUrl}/warp/v1/messages \
  -H "Content-Type: application/json" \
  -H "x-api-key: YOUR_API_KEY" \
  -d '{
    "model": "claude-4-5-sonnet",
    "max_tokens": 4096,
    "stream": true,
    "messages": [
      {"role": "user", "content": "Hello, who are you?"}
    ]
  }'`, SortOrder: 2},
		{ChannelKey: "antigravity", Protocol: "claude", Content: `curl -X POST {baseUrl}/antigravity/v1/messages \
  -H "Content-Type: application/json" \
  -H "x-api-key: YOUR_API_KEY" \
  -d '{
    "model": "gemini-2.5-flash-preview",
    "max_tokens": 4096,
    "stream": true,
    "messages": [
      {"role": "user", "content": "Hello, who are you?"}
    ]
  }'`, SortOrder: 3},
		{ChannelKey: "orchids", Protocol: "claude", Content: `curl -X POST {baseUrl}/orchids/v1/messages \
  -H "Content-Type: application/json" \
  -H "x-api-key: YOUR_API_KEY" \
  -d '{
    "model": "claude-sonnet-4-5",
    "max_tokens": 4096,
    "stream": true,
    "messages": [
      {"role": "user", "content": "Hello, who are you?"}
    ]
  }'`, SortOrder: 4},
		{ChannelKey: "claude_api", Protocol: "claude", Content: `curl -X POST {baseUrl}/claude_api/v1/messages \
  -H "Content-Type: application/json" \
  -H "x-api-key: YOUR_API_KEY" \
  -d '{
    "model": "claude-sonnet-4-5",
    "max_tokens": 4096,
    "stream": true,
    "messages": [
      {"role": "user", "content": "Hello, who are you?"}
    ]
  }'`, SortOrder: 5},

		// OpenAI protocol examples (non-Grok)
		{ChannelKey: "kiro", Protocol: "openai", Content: `curl -X POST {baseUrl}/kiro/v1/chat/completions \
  -H "Content-Type: application/json" \
  -H "Authorization: Bearer YOUR_API_KEY" \
  -d '{
    "model": "claude-sonnet-4-5",
    "stream": true,
    "messages": [
      {"role": "user", "content": "Hello, who are you?"}
    ]
  }'`, SortOrder: 1},
		{ChannelKey: "warp", Protocol: "openai", Content: `curl -X POST {baseUrl}/warp/v1/chat/completions \
  -H "Content-Type: application/json" \
  -H "Authorization: Bearer YOUR_API_KEY" \
  -d '{
    "model": "claude-4-5-sonnet",
    "stream": true,
    "messages": [
      {"role": "user", "content": "Hello, who are you?"}
    ]
  }'`, SortOrder: 2},
		{ChannelKey: "antigravity", Protocol: "openai", Content: `curl -X POST {baseUrl}/antigravity/v1/chat/completions \
  -H "Content-Type: application/json" \
  -H "Authorization: Bearer YOUR_API_KEY" \
  -d '{
    "model": "gemini-2.5-flash-preview",
    "stream": true,
    "messages": [
      {"role": "user", "content": "Hello, who are you?"}
    ]
  }'`, SortOrder: 3},
		{ChannelKey: "orchids", Protocol: "openai", Content: `curl -X POST {baseUrl}/orchids/v1/chat/completions \
  -H "Content-Type: application/json" \
  -H "Authorization: Bearer YOUR_API_KEY" \
  -d '{
    "model": "claude-sonnet-4-5",
    "stream": true,
    "messages": [
      {"role": "user", "content": "Hello, who are you?"}
    ]
  }'`, SortOrder: 4},
		{ChannelKey: "cursor", Protocol: "openai", Content: `curl -X POST {baseUrl}/cursor/v1/chat/completions \
  -H "Content-Type: application/json" \
  -H "Authorization: Bearer YOUR_API_KEY" \
  -d '{
    "model": "claude-4.5-sonnet",
    "stream": true,
    "messages": [
      {"role": "user", "content": "Hello, who are you?"}
    ]
  }'`, SortOrder: 5},

		// Grok OpenAI protocol — 4 sub-tabs
		{ChannelKey: "grok", Protocol: "openai", TabKey: "chat", TabLabel: "文字对话", Content: `# Grok 文字对话
# 端点: /grok/v1/chat/completions
# 模型: grok-3, grok-4, grok-4.1-fast, grok-4.1-thinking 等

curl -X POST {baseUrl}/grok/v1/chat/completions \
  -H "Content-Type: application/json" \
  -H "Authorization: Bearer YOUR_API_KEY" \
  -d '{
    "model": "grok-4.1-fast",
    "stream": true,
    "messages": [
      {"role": "system", "content": "你是一个专业的 AI 助手"},
      {"role": "user", "content": "请用 Python 写一个快速排序算法"}
    ]
  }'`, SortOrder: 1},
		{ChannelKey: "grok", Protocol: "openai", TabKey: "image", TabLabel: "图片生成", Content: `# Grok 图片生成
# 支持两种方式: 图片 API 或 Chat API
# 参数: n (生成数量 1-10, 流式仅支持 1-2)

# 方式 1: 图片生成 API
# 端点: /grok/v1/images/generations
curl -X POST {baseUrl}/grok/v1/images/generations \
  -H "Content-Type: application/json" \
  -H "Authorization: Bearer YOUR_API_KEY" \
  -d '{
    "prompt": "一只赛博朋克风格机器猫，站在城市天际线前",
    "n": 2,
    "stream": true
  }'

# 方式 2: Chat API + 图片模型
# 模型: grok-imagine-1.0
curl -X POST {baseUrl}/grok/v1/chat/completions \
  -H "Content-Type: application/json" \
  -H "Authorization: Bearer YOUR_API_KEY" \
  -d '{
    "model": "grok-imagine-1.0",
    "stream": true,
    "n": 2,
    "messages": [
      {"role": "user", "content": "一只赛博朋克风格机器猫"}
    ]
  }'`, SortOrder: 2},
		{ChannelKey: "grok", Protocol: "openai", TabKey: "video", TabLabel: "视频生成", Content: `# Grok 视频生成 (文生视频)
# 参数: aspect_ratio (16:9/9:16/1:1), duration (6/10秒), resolution (480p/720p)

# 方式 1: 视频生成 API
# 端点: /grok/v1/videos/generations
curl -X POST {baseUrl}/grok/v1/videos/generations \
  -H "Content-Type: application/json" \
  -H "Authorization: Bearer YOUR_API_KEY" \
  -d '{
    "prompt": "一只柯基犬在花园里奔跑，阳光明媚，慢动作",
    "aspect_ratio": "16:9",
    "duration": 10,
    "resolution": "720p",
    "stream": true
  }'

# 方式 2: Chat API + 视频模型
# 模型: grok-imagine-1.0-video
curl -X POST {baseUrl}/grok/v1/chat/completions \
  -H "Content-Type: application/json" \
  -H "Authorization: Bearer YOUR_API_KEY" \
  -d '{
    "model": "grok-imagine-1.0-video",
    "stream": true,
    "video_aspect_ratio": "9:16",
    "video_duration": 6,
    "video_resolution": "720p",
    "messages": [
      {"role": "user", "content": "海浪拍打码头，夕阳西下"}
    ]
  }'`, SortOrder: 3},
		{ChannelKey: "grok", Protocol: "openai", TabKey: "image2video", TabLabel: "图生视频", Content: `# Grok 图生视频 (图片动起来)
# 模型: grok-imagine-1.0-video
# 图片支持 URL 或 base64

# 使用图片 URL
curl -X POST {baseUrl}/grok/v1/chat/completions \
  -H "Content-Type: application/json" \
  -H "Authorization: Bearer YOUR_API_KEY" \
  -d '{
    "model": "grok-imagine-1.0-video",
    "stream": true,
    "video_aspect_ratio": "1:1",
    "video_duration": 6,
    "video_resolution": "480p",
    "messages": [
      {
        "role": "user",
        "content": [
          {"type": "image_url", "image_url": {"url": "https://example.com/image.jpg"}},
          {"type": "text", "text": "让这只猫慢慢转过头来"}
        ]
      }
    ]
  }'`, SortOrder: 4},
	}
}

// TutorialChannelList returns all tutorial channels ordered by sort_order.
func TutorialChannelList(ctx context.Context) ([]TutorialChannel, error) {
	var list []TutorialChannel
	err := db.WithContext(ctx).Order("sort_order ASC, id ASC").Find(&list).Error
	return list, err
}

// TutorialExampleList returns all tutorial examples ordered by channel and sort_order.
func TutorialExampleList(ctx context.Context) ([]TutorialExample, error) {
	var list []TutorialExample
	err := db.WithContext(ctx).Order("channel_key ASC, sort_order ASC, id ASC").Find(&list).Error
	return list, err
}

// TutorialChannelBatchSave replaces all tutorial channels with the provided list.
func TutorialChannelBatchSave(ctx context.Context, channels []TutorialChannel) error {
	return db.WithContext(ctx).Transaction(func(tx *gorm.DB) error {
		if err := tx.Exec("DELETE FROM tutorial_channels").Error; err != nil {
			return err
		}
		if len(channels) > 0 {
			return tx.Create(&channels).Error
		}
		return nil
	})
}

// TutorialExampleBatchSave replaces all tutorial examples with the provided list.
func TutorialExampleBatchSave(ctx context.Context, examples []TutorialExample) error {
	return db.WithContext(ctx).Transaction(func(tx *gorm.DB) error {
		if err := tx.Exec("DELETE FROM tutorial_examples").Error; err != nil {
			return err
		}
		if len(examples) > 0 {
			return tx.Create(&examples).Error
		}
		return nil
	})
}

// TutorialChannelDelete deletes a tutorial channel by id.
func TutorialChannelDelete(ctx context.Context, id int64) error {
	return db.WithContext(ctx).Delete(&TutorialChannel{}, id).Error
}

// TutorialExampleDelete deletes a tutorial example by id.
func TutorialExampleDelete(ctx context.Context, id int64) error {
	return db.WithContext(ctx).Delete(&TutorialExample{}, id).Error
}
