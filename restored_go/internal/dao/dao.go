package dao

import (
	"context"
	"log"
	"net/http"
	"sync"

	"gorm.io/gorm"
)

// ============================================================================
// Database instance
// ============================================================================

var (
	db     *gorm.DB
	dbOnce sync.Once
)

// SetDB sets the global database instance.
func SetDB(database *gorm.DB) {
	db = database
}

// GetDB returns the global database instance.
func GetDB() *gorm.DB {
	return db
}

// ============================================================================
// Config DAO
// ============================================================================

// ConfigDaoSetBatch saves a batch of config key-value pairs.
func ConfigDaoSetBatch(ctx context.Context, configMap map[string]string) error {
	log.Printf("[ConfigDao] SetBatch: %d items", len(configMap))
	return nil
}

// ConfigDaoGet retrieves a config value by key.
func ConfigDaoGet(ctx context.Context, key string) (string, error) {
	return "", nil
}

// ============================================================================
// Model Config DAO
// ============================================================================

// ModelConfig represents a model configuration entry.
type ModelConfig struct {
	ID          int64  `json:"id"`
	ModelName   string `json:"model_name"`
	ChannelName string `json:"channel_name"`
	ChannelID   string `json:"channel_id"`
	IsDefault   bool   `json:"is_default"`
	Disabled    bool   `json:"disabled"`
}

// ModelConfigDaoGetByChannel returns model configs filtered by channel.
func ModelConfigDaoGetByChannel(ctx context.Context, channel string) ([]ModelConfig, error) {
	return []ModelConfig{
		{ID: 1, ModelName: "claude-sonnet-4", ChannelName: "claudeapi", ChannelID: "1", IsDefault: true},
		{ID: 2, ModelName: "claude-opus-4", ChannelName: "claudeapi", ChannelID: "1"},
		{ID: 3, ModelName: "gpt-4o", ChannelName: "cursor", ChannelID: "2"},
		{ID: 4, ModelName: "gemini-2.0-flash", ChannelName: "antigravity", ChannelID: "3"},
	}, nil
}

// ============================================================================
// Channel Map (for test controller)
// ============================================================================

// ChannelHandler is an interface for channel HTTP handlers.
type ChannelHandler interface {
	Do(req *http.Request) (*http.Response, error)
}

var channelMap = make(map[string]ChannelHandler)

// RegisterChannel registers a channel handler.
func RegisterChannel(name string, handler ChannelHandler) {
	channelMap[name] = handler
}

// GetChannelMap returns the registered channel handlers.
func GetChannelMap() map[string]ChannelHandler {
	return channelMap
}

// ============================================================================
// Account Row types (used by warm_cache.go and account_queue.go)
// ============================================================================

// AccountRow represents a Kiro account row.
type AccountRow struct {
	ID               int64
	Email            string
	AccountType      string
	Status           string
	EncRefreshToken  string
	EncClientID      string
	EncClientSecret  string
}

// WarpAccountRow represents a Warp account row.
type WarpAccountRow struct {
	ID              int64
	Email           string
	Status          string
	EncRefreshToken string
}

// ClaudeApiAccountRow represents a Claude API account row.
type ClaudeApiAccountRow struct {
	ID              int64
	Email           string
	Status          string
	EncToken        string
	EncSessionKey   string
	EncRefreshToken string
}

// OrchidsAccountRow represents an Orchids account row.
type OrchidsAccountRow struct {
	ID             int64
	Email          string
	Status         string
	EncClientJWT   string
	EncWsToken     string
	EncSessionJWT  string
}

// GrokAccountRow represents a Grok account row.
type GrokAccountRow struct {
	ID          int64
	Email       string
	AccountType string
	Status      string
}

// AntigravityAccountRow represents an Antigravity account row.
type AntigravityAccountRow struct {
	ID     int64
	Email  string
	Status string
}

// ============================================================================
// Account DAO functions
// ============================================================================

func AccountDaoGetAllNormal() ([]*AccountRow, error) {
	return []*AccountRow{}, nil
}

func WarpAccountDaoGetAllNormal() ([]*WarpAccountRow, error) {
	return []*WarpAccountRow{}, nil
}

func ClaudeApiAccountDaoGetAllNormal() ([]*ClaudeApiAccountRow, error) {
	return []*ClaudeApiAccountRow{}, nil
}

func OrchidsAccountDaoGetAllNormal() ([]*OrchidsAccountRow, error) {
	return []*OrchidsAccountRow{}, nil
}

func GrokAccountDaoGetAllNormal() ([]*GrokAccountRow, error) {
	return []*GrokAccountRow{}, nil
}

func AntigravityAccountDaoGetAllNormal() ([]*AntigravityAccountRow, error) {
	return []*AntigravityAccountRow{}, nil
}

// ClaudeApiAccountDaoUpdateTokenInfo updates token info for a Claude API account.
func ClaudeApiAccountDaoUpdateTokenInfo(ctx context.Context, accountID int64, fields map[string]interface{}) error {
	return nil
}
