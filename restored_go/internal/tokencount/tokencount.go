package tokencount

import (
	"context"
	"sync"
)

var (
	configCache     map[string]string
	configCacheMu   sync.RWMutex
)

func init() {
	configCache = make(map[string]string)
}

// ClearConfigCache clears the cached configuration values.
func ClearConfigCache() {
	configCacheMu.Lock()
	defer configCacheMu.Unlock()
	configCache = make(map[string]string)
}

// GetConfigValue returns a cached config value by key.
func GetConfigValue(ctx context.Context, key string) string {
	configCacheMu.RLock()
	defer configCacheMu.RUnlock()
	return configCache[key]
}

// CountTokens estimates the token count for a given text.
func CountTokens(text string) int {
	// Simple estimation: ~4 chars per token
	return len(text) / 4
}
