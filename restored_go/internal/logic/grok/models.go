package grok

// models.go — Data models for the Grok channel.
//
// Structures derived from decompiled BuildChatPayload, extractMessages,
// ProcessLine, ImagineGenerations, and VideoGenerations functions.
//
// Grok API uses a map[string]interface{} based payload format with
// nested structures for messages, conversation settings, and media.

// ============================================================================
// Chat Request/Response Models
// ============================================================================

// GrokChatPayload represents the full chat request payload sent to Grok API.
// Derived from BuildChatPayload (@ 0x1606520) which constructs a map with:
//   - "responses"           ([]map) — conversation messages
//   - "systemPromptName"    (string) — system prompt identifier
//   - "grokModelOptionId"   (string) — model selection
//   - "conversationId"      (string) — conversation ID
//   - "returnSearchResults" (bool)   — search results flag
//   - "returnCitations"     (bool)   — citations flag
//   - "respondWithMediaType" (map)   — media type settings
//   - "imageGenerationCount" (int)   — number of images to generate
//   - "forceConcise"        (bool)   — concise mode
//   - "toolOverrides"       (map)    — tool override settings
//   - "isDeepsearch"        (bool)   — deep search mode
//   - "disableTextFollowUp" (bool)   — disable text follow-up
//   - "enableImageGeneration" (bool) — enable image generation
//   - "imageAttachments"    ([]map)  — attached images
//   - "fileAttachments"     ([]map)  — attached files
type GrokChatPayload map[string]interface{}

// GrokMessage represents a single message in the conversation.
// From extractMessages (@ 0x1603860):
//   - role: "user" or "assistant"
//   - content: text content
//   - fileAttachments: optional file attachments
//   - imageAttachments: optional image attachments
type GrokMessage struct {
	Role    string   `json:"role"`
	Content string   `json:"content"`
	Parts   []string `json:"parts,omitempty"`
}

// GrokStreamEvent represents a parsed line from the streaming response.
// From ProcessLine (@ 0x1612e80):
//   - "result" field contains the response data
//   - "error" field indicates errors
//   - "image" field for image generation results
type GrokStreamEvent struct {
	Result *GrokResult `json:"result,omitempty"`
	Error  *GrokError  `json:"error,omitempty"`
}

// GrokResult represents the result object in a stream event.
// From ProcessLine analysis of map access patterns:
//   - "response" (string) — text response content
//   - "modelResponse" (map) — full model response
//   - "token" (string) — token for streaming
type GrokResult struct {
	Response      string                 `json:"response,omitempty"`
	ModelResponse map[string]interface{} `json:"modelResponse,omitempty"`
	Token         string                 `json:"token,omitempty"`
	IsThinking    bool                   `json:"isThinking,omitempty"`
}

// GrokError represents an error in the stream response.
type GrokError struct {
	Message string `json:"message,omitempty"`
	Code    string `json:"code,omitempty"`
}

// ============================================================================
// Usage Tracking Models
// ============================================================================

// GrokUsage tracks token usage for a response.
// From CollectProcessorProcessWithUsage (@ 0x1616000):
//   - Collects input/output token counts
//   - Tracks timing information
type GrokUsage struct {
	InputTokens  int `json:"input_tokens"`
	OutputTokens int `json:"output_tokens"`
}

// CollectResult holds the collected response with usage metrics.
type CollectResult struct {
	Content    string     `json:"content"`
	Usage      *GrokUsage `json:"usage,omitempty"`
	StopReason string     `json:"stop_reason,omitempty"`
}

// ============================================================================
// Image Generation Models
// ============================================================================

// ImagineRequest represents an image generation request.
// From ImagineGenerations (@ 0x160cd00):
//   - Uses WebSocket connection for real-time updates
//   - Tracks generation progress with completion flags
type ImagineRequest struct {
	Prompt     string `json:"prompt"`
	Count      int    `json:"count"`
	AccountKey string `json:"-"`
}

// ImagineResult represents a single image generation result.
// From ImagineGenerations decompiled analysis:
//   - "url" field for the generated image URL
//   - "mediaType" field for MIME type classification
//   - "isComplete" flag for completion tracking
type ImagineResult struct {
	URL        string `json:"url,omitempty"`
	MediaType  string `json:"mediaType,omitempty"`
	IsComplete bool   `json:"isComplete,omitempty"`
}

// ImageClassification holds the result of classifyImage.
// From ImagineGenerations: classifyImage returns struct with fields at offsets:
//   +0x10: URL string pointer
//   +0x18: URL string length
//   +0x20: mediaType string pointer
//   +0x28: mediaType string length
//   +0x48: isComplete flag (byte)
type ImageClassification struct {
	URL        string `json:"url"`
	MediaType  string `json:"mediaType"`
	IsComplete bool   `json:"isComplete"`
}

// MediaProgress tracks WebSocket-based media generation progress.
// From ImagineGenerations: puStack_370 is a progress tracker object:
//   - Created on first "medium" type result
//   - Stores start time for stall detection
//   - Linked list of previous progress objects
type MediaProgress struct {
	StartTime interface{} // time.Time stored as interface
	Previous  *MediaProgress
}

// ============================================================================
// Video Generation Models
// ============================================================================

// VideoRequest represents a video generation request.
// From VideoGenerations (@ 0x161bc00):
//   - Supports both text-to-video and image-to-video
//   - Image upload required for image-to-video
type VideoRequest struct {
	Prompt     string `json:"prompt"`
	ImageURL   string `json:"imageUrl,omitempty"`
	ImageData  string `json:"imageData,omitempty"`
	AccountKey string `json:"-"`
}

// VideoResult represents a video generation result.
type VideoResult struct {
	URL        string `json:"url,omitempty"`
	MediaType  string `json:"mediaType,omitempty"`
	IsComplete bool   `json:"isComplete,omitempty"`
}

// ============================================================================
// HTTP/Auth Models
// ============================================================================

// GrokHeaders represents the HTTP headers for Grok API requests.
// From BuildHeaders analysis — includes browser fingerprint spoofing:
//   - Standard headers (Content-Type, Accept, etc.)
//   - Cookie-based auth (ct0, auth_token)
//   - Cloudflare clearance (cf_clearance)
//   - Browser fingerprint headers
type GrokHeaders map[string]string

// GrokAccount represents a Grok account configuration.
// Fields derived from map access patterns across all decompiled functions.
type GrokAccount struct {
	Cookie          string `json:"cookie"`
	AuthToken       string `json:"auth_token"`
	CT0             string `json:"ct0"`
	CfClearance     string `json:"cf_clearance"`
	Proxy           string `json:"proxy,omitempty"`
	UserAgent       string `json:"user_agent,omitempty"`
	BrowserFP       string `json:"browser_fp,omitempty"`
}

// ============================================================================
// Conversation Settings (from BuildChatPayload)
// ============================================================================

// ConversationSettings holds the boolean flags and settings for a chat payload.
// Derived from the many mapassign_faststr calls in BuildChatPayload:
//   - 0xd bytes "returnSearchResults" → bool (false)
//   - 0x15 bytes "respondWithMediaType" → bool (true)
//   - 0x10 bytes "imageGenerationCount" → bool (false)
//   - 0x19 bytes "disableTextFollowUp" → bool (false)
//   - 0x14 bytes "enableImageGeneration" → bool (true)
//   - 0x14 bytes "imageAttachments" → int (0)
//   - 0xc bytes "forceConcise" → bool (false)
type ConversationSettings struct {
	ReturnSearchResults   bool `json:"returnSearchResults"`
	ReturnCitations       bool `json:"returnCitations"`
	ForceConcise          bool `json:"forceConcise"`
	IsDeepsearch          bool `json:"isDeepsearch"`
	DisableTextFollowUp   bool `json:"disableTextFollowUp"`
	EnableImageGeneration bool `json:"enableImageGeneration"`
	ImageGenerationCount  int  `json:"imageGenerationCount"`
}

// ============================================================================
// Cache/Download Models
// ============================================================================

// NOTE: CacheEntry is defined in cache.go — removed duplicate here.

// DownloadTask represents an async download task.
// From DownloadService subsystem (4 functions).
type DownloadTask struct {
	URL      string `json:"url"`
	CacheKey string `json:"cache_key"`
	Status   string `json:"status"` // "pending", "downloading", "complete", "error"
}
