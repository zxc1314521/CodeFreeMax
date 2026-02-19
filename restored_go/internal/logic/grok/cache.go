package grok

// cache.go — Cache and download services for the Grok channel.
//
// Functions:
//   - CacheService          — File caching for generated media (images/videos)
//   - DownloadService       — Download and proxy media files
//   - buildConversationMessages — Convert OpenAI messages to Grok format
//
// From decompiled patterns in models.go and ImagineGenerations:
//   - CacheService stores generated media locally with TTL
//   - DownloadService fetches remote media and caches it
//   - buildConversationMessages transforms OpenAI-format messages
//     into Grok's "responses" array format
//
// The cache service is referenced in grok.go (sGrok struct) and used
// by ImagineGenerations and VideoGenerations to store generated media
// for later retrieval via the download endpoint.

import (
	"context"
	"fmt"
	"io"
	"net/http"
	"os"
	"path/filepath"
	"strings"
	"sync"
	"time"

	"github.com/gogf/gf/v2/frame/gins"
)

// ============================================================================
// CacheService
// ============================================================================

// CacheService manages local file caching for generated media.
//
// From decompiled: kiro2api_internal_logic_grok_CacheService type
// Referenced in sGrok struct and used by media generation functions.
//
// The cache stores files on disk with metadata tracking for TTL-based
// expiration. Files are keyed by a hash of their source URL.
type CacheService struct {
	mu       sync.RWMutex
	cacheDir string
	entries  map[string]*CacheEntry
	ttl      time.Duration
}

// CacheEntry represents a cached file with metadata.
type CacheEntry struct {
	FilePath  string
	URL       string
	CreatedAt time.Time
	Size      int64
}

// NewCacheService creates a new CacheService with the given cache directory and TTL.
// From decompiled: kiro2api_internal_logic_grok_NewCacheService
func NewCacheService(cacheDir string, ttl time.Duration) *CacheService {
	// Ensure cache directory exists
	os.MkdirAll(cacheDir, 0755)

	cs := &CacheService{
		cacheDir: cacheDir,
		entries:  make(map[string]*CacheEntry),
		ttl:      ttl,
	}

	// Start background cleanup goroutine
	// From decompiled: go routine launched in init
	go cs.cleanupLoop()

	return cs
}

// Get retrieves a cached file path by key.
// Returns empty string if not found or expired.
func (cs *CacheService) Get(key string) string {
	cs.mu.RLock()
	defer cs.mu.RUnlock()

	entry, ok := cs.entries[key]
	if !ok {
		return ""
	}

	// Check TTL expiration
	if time.Since(entry.CreatedAt) > cs.ttl {
		return ""
	}

	return entry.FilePath
}

// Put stores a file in the cache.
// Returns the local file path.
func (cs *CacheService) Put(key string, data []byte, ext string) (string, error) {
	cs.mu.Lock()
	defer cs.mu.Unlock()

	// Build file path
	filename := key + ext
	filePath := filepath.Join(cs.cacheDir, filename)

	// Write file
	if err := os.WriteFile(filePath, data, 0644); err != nil {
		return "", fmt.Errorf("write cache file: %w", err)
	}

	// Store entry
	cs.entries[key] = &CacheEntry{
		FilePath:  filePath,
		CreatedAt: time.Now(),
		Size:      int64(len(data)),
	}

	return filePath, nil
}

// PutFromURL stores a file in the cache by downloading from a URL.
func (cs *CacheService) PutFromURL(key string, url string, ext string) (string, error) {
	// Download the file
	data, err := downloadFile(url)
	if err != nil {
		return "", fmt.Errorf("download for cache: %w", err)
	}

	return cs.Put(key, data, ext)
}

// Delete removes a cached file by key.
func (cs *CacheService) Delete(key string) {
	cs.mu.Lock()
	defer cs.mu.Unlock()

	entry, ok := cs.entries[key]
	if !ok {
		return
	}

	// Remove file from disk
	os.Remove(entry.FilePath)
	delete(cs.entries, key)
}

// cleanupLoop periodically removes expired cache entries.
// From decompiled: background goroutine with ticker
func (cs *CacheService) cleanupLoop() {
	ticker := time.NewTicker(5 * time.Minute)
	defer ticker.Stop()

	for range ticker.C {
		cs.cleanup()
	}
}

// cleanup removes expired entries from the cache.
func (cs *CacheService) cleanup() {
	cs.mu.Lock()
	defer cs.mu.Unlock()

	now := time.Now()
	for key, entry := range cs.entries {
		if now.Sub(entry.CreatedAt) > cs.ttl {
			os.Remove(entry.FilePath)
			delete(cs.entries, key)
		}
	}
}

// ============================================================================
// DownloadService
// ============================================================================

// DownloadService handles downloading and proxying media files.
//
// From decompiled: kiro2api_internal_logic_grok_DownloadService type
// Referenced in sGrok struct, used to proxy generated images/videos
// back to the client.
type DownloadService struct {
	cache      *CacheService
	httpClient *http.Client
}

// NewDownloadService creates a new DownloadService.
// From decompiled: kiro2api_internal_logic_grok_NewDownloadService
func NewDownloadService(cache *CacheService) *DownloadService {
	return &DownloadService{
		cache: cache,
		httpClient: &http.Client{
			Timeout: 60 * time.Second,
		},
	}
}

// Download fetches a file from URL, caches it, and returns the local path.
// If already cached, returns the cached path directly.
func (ds *DownloadService) Download(ctx context.Context, key string, url string) (string, error) {
	// Check cache first
	if cached := ds.cache.Get(key); cached != "" {
		return cached, nil
	}

	// Determine file extension from URL
	ext := extractExtension(url)

	// Download and cache
	return ds.cache.PutFromURL(key, url, ext)
}

// ServeFile serves a cached file via HTTP response.
func (ds *DownloadService) ServeFile(w http.ResponseWriter, filePath string) error {
	f, err := os.Open(filePath)
	if err != nil {
		return fmt.Errorf("open cached file: %w", err)
	}
	defer f.Close()

	// Detect content type
	buf := make([]byte, 512)
	n, _ := f.Read(buf)
	contentType := http.DetectContentType(buf[:n])
	f.Seek(0, io.SeekStart)

	w.Header().Set("Content-Type", contentType)
	io.Copy(w, f)
	return nil
}

// ============================================================================
// buildConversationMessages
// ============================================================================

// buildConversationMessages converts OpenAI-format messages to Grok's
// "responses" array format.
//
// From decompiled: called in BuildChatPayload to transform messages.
// Grok expects a specific format for conversation history:
//   - "query" for user messages
//   - "response" for assistant messages
//   - Each entry has "message" and "sender" fields
//
// OpenAI format:
//   [{"role": "user", "content": "Hello"}, {"role": "assistant", "content": "Hi"}]
//
// Grok format:
//   [{"message": "Hello", "sender": 1}, {"message": "Hi", "sender": 2}]
func buildConversationMessages(messages []map[string]interface{}) []map[string]interface{} {
	var responses []map[string]interface{}

	for _, msg := range messages {
		role, _ := msg["role"].(string)
		content := extractTextContent(msg["content"])

		if content == "" {
			continue
		}

		var sender int
		switch role {
		case "user":
			sender = 1 // Human/user
		case "assistant":
			sender = 2 // AI/assistant
		default:
			continue // Skip system and other roles
		}

		responses = append(responses, map[string]interface{}{
			"message": content,
			"sender":  sender,
		})
	}

	return responses
}

// extractTextContent extracts plain text from OpenAI message content.
// Handles both string content and array-of-parts content.
func extractTextContent(content interface{}) string {
	switch c := content.(type) {
	case string:
		return c
	case []interface{}:
		var parts []string
		for _, item := range c {
			if m, ok := item.(map[string]interface{}); ok {
				if m["type"] == "text" {
					if t, ok := m["text"].(string); ok {
						parts = append(parts, t)
					}
				}
			}
		}
		return strings.Join(parts, "\n")
	}
	return ""
}

// ============================================================================
// Helpers
// ============================================================================

// downloadFile downloads a file from a URL and returns its contents.
func downloadFile(url string) ([]byte, error) {
	logger := gins.Log()

	resp, err := http.Get(url)
	if err != nil {
		return nil, fmt.Errorf("download %s: %w", url, err)
	}
	defer resp.Body.Close()

	if resp.StatusCode != http.StatusOK {
		return nil, fmt.Errorf("download %s: HTTP %d", url, resp.StatusCode)
	}

	data, err := io.ReadAll(resp.Body)
	if err != nil {
		return nil, fmt.Errorf("read body %s: %w", url, err)
	}

	logger.Debugf(nil, "[Grok] Downloaded %s: %d bytes", url, len(data))
	return data, nil
}

// extractExtension extracts the file extension from a URL.
func extractExtension(url string) string {
	// Strip query params
	if idx := strings.Index(url, "?"); idx != -1 {
		url = url[:idx]
	}

	// Find last dot
	if idx := strings.LastIndex(url, "."); idx != -1 {
		ext := url[idx:]
		if len(ext) <= 5 { // Reasonable extension length
			return ext
		}
	}

	return ".bin"
}
