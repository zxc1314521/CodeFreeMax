package warp

// models.go — Data models and types for the Warp channel.
//
// Warp uses a custom dynamic protobuf system (not generated .pb.go files).
// The binary loads .proto file descriptor sets at runtime and uses reflection
// to build/parse protobuf messages.
//
// From GoReSym symbols:
//   - NewMessage, SetFieldValue, GetStringField, GetNestedMessage
//   - GetRepeatedField, SetNestedMessage, AppendToRepeatedField
//   - UnmarshalMessage, ListMessageFields
//   - loadFileDescriptorSet, ensureProtoInitialized, registerNestedMessages
//   - extractFieldTextRecursive, ExtractOutputText, ExtractReasoningText
//   - DetectContentType

// ============================================================================
// Request/Response Models
// ============================================================================

// WarpStreamRequest represents the protobuf request sent to Warp's streaming API.
// From decompiled: buildWarpRequest constructs this via protobuf fields.
//
// Protobuf structure (inferred from field numbers and buildFullPrompt):
//   message WarpStreamRequest {
//     string model = 1;           // e.g. "claude_sonnet_4"
//     string prompt = 2;          // full prompt text
//     WarpInput input = 3;        // input context
//     WarpSettings settings = 4;  // generation settings
//     WarpMetadata metadata = 5;  // client metadata
//   }
type WarpStreamRequest struct {
	Model    string        `json:"model"`
	Prompt   string        `json:"prompt"`
	Input    *WarpInput    `json:"input,omitempty"`
	Settings *WarpSettings `json:"settings,omitempty"`
	Metadata *WarpMetadata `json:"metadata,omitempty"`
}

// WarpInput represents the input context for a Warp request.
// From decompiled: buildInput (0x1715f00, 576B) and buildInputContext (0x171bec0, 2112B)
type WarpInput struct {
	Context    *WarpInputContext `json:"context,omitempty"`
	Images     []WarpImage       `json:"images,omitempty"`
	MCPContext *WarpMCPContext   `json:"mcp_context,omitempty"`
	Schema     interface{}       `json:"schema,omitempty"`
}

// WarpInputContext represents the input context with files and conversation.
// From decompiled: buildInputContext
type WarpInputContext struct {
	Files        []WarpFile        `json:"files,omitempty"`
	Conversation []WarpConvMessage `json:"conversation,omitempty"`
}

// WarpFile represents a file reference in the input context.
type WarpFile struct {
	Path    string `json:"path"`
	Content string `json:"content,omitempty"`
}

// WarpConvMessage represents a conversation message in the input.
type WarpConvMessage struct {
	Role    string `json:"role"`
	Content string `json:"content"`
}

// WarpImage represents an image attachment.
// From decompiled: extractImagesFromMessages (0x171c700, 1120B)
type WarpImage struct {
	URL      string `json:"url,omitempty"`
	Base64   string `json:"base64,omitempty"`
	MimeType string `json:"mime_type,omitempty"`
}

// WarpSettings represents generation settings.
// From decompiled: buildSettings (0x171cb60, 1120B)
type WarpSettings struct {
	Temperature    float64 `json:"temperature,omitempty"`
	MaxTokens      int     `json:"max_tokens,omitempty"`
	TopP           float64 `json:"top_p,omitempty"`
	Stream         bool    `json:"stream"`
	AgentMode      bool    `json:"agent_mode,omitempty"`
	ThinkingBudget int     `json:"thinking_budget,omitempty"`
}

// WarpMetadata represents client metadata sent with requests.
// From decompiled: buildMetadata (0x171cfc0, 1952B)
type WarpMetadata struct {
	OS         string `json:"os"`
	OSVersion  string `json:"os_version"`
	AppVersion string `json:"app_version"`
	DeviceID   string `json:"device_id"`
	RequestID  string `json:"request_id"`
	Timezone   string `json:"timezone"`
	AppName    string `json:"app_name"`
}

// WarpMCPContext represents MCP (Model Context Protocol) context.
// From decompiled: buildMCPContext (0x171d760, 1312B)
type WarpMCPContext struct {
	Tools   []WarpMCPTool   `json:"tools,omitempty"`
	Servers []WarpMCPServer `json:"servers,omitempty"`
}

// WarpMCPTool represents an MCP tool definition.
type WarpMCPTool struct {
	Name        string      `json:"name"`
	Description string      `json:"description,omitempty"`
	InputSchema interface{} `json:"input_schema,omitempty"`
}

// WarpMCPServer represents an MCP server configuration.
type WarpMCPServer struct {
	Name string `json:"name"`
	URL  string `json:"url"`
}

// ============================================================================
// Response Models
// ============================================================================

// WarpStreamResponse represents a parsed protobuf streaming response.
// From decompiled: ProcessLine parses protobuf responses into this structure.
type WarpStreamResponse struct {
	OutputText    string `json:"output_text,omitempty"`
	ReasoningText string `json:"reasoning_text,omitempty"`
	Done          bool   `json:"done"`
	Error         string `json:"error,omitempty"`
	Usage         *WarpUsage `json:"usage,omitempty"`
}

// WarpUsage represents token usage information.
type WarpUsage struct {
	InputTokens  int `json:"input_tokens"`
	OutputTokens int `json:"output_tokens"`
}

// ============================================================================
// Firebase Auth Models
// ============================================================================

// FirebaseTokenRequest represents a Firebase token refresh request.
// From decompiled: RefreshToken builds this JSON body.
type FirebaseTokenRequest struct {
	GrantType    string `json:"grant_type"`
	RefreshToken string `json:"refresh_token"`
}

// FirebaseTokenResponse represents a Firebase token refresh response.
type FirebaseTokenResponse struct {
	AccessToken  string `json:"access_token"`
	ExpiresIn    string `json:"expires_in"`
	TokenType    string `json:"token_type"`
	RefreshToken string `json:"refresh_token"`
	IDToken      string `json:"id_token"`
	UserID       string `json:"user_id"`
	ProjectID    string `json:"project_id"`
}

// ============================================================================
// GraphQL Models
// ============================================================================

// GraphQLRequest represents a GraphQL request body.
// From decompiled: GetQuotaInfo and RefundCredits build GraphQL queries.
type GraphQLRequest struct {
	Query         string                 `json:"query"`
	Variables     map[string]interface{} `json:"variables,omitempty"`
	OperationName string                `json:"operationName,omitempty"`
}

// GraphQLResponse represents a generic GraphQL response.
type GraphQLResponse struct {
	Data   map[string]interface{} `json:"data,omitempty"`
	Errors []GraphQLError         `json:"errors,omitempty"`
}

// GraphQLError represents a GraphQL error.
type GraphQLError struct {
	Message string `json:"message"`
}

// ============================================================================
// QuotaInfo
// ============================================================================

// QuotaInfo represents the user's quota/credit information.
// From decompiled: GetQuotaInfo returns this.
type QuotaInfo struct {
	TotalCredits     int64  `json:"total_credits"`
	UsedCredits      int64  `json:"used_credits"`
	RemainingCredits int64  `json:"remaining_credits"`
	Plan             string `json:"plan"`
	ResetDate        string `json:"reset_date"`
}

// ============================================================================
// Tool Mapping Models
// ============================================================================

// WarpToolCall represents a tool call from Warp's response.
// From decompiled: MapToolToClaudeCode and MapToolsToClaudeCode
type WarpToolCall struct {
	Name      string                 `json:"name"`
	Arguments map[string]interface{} `json:"arguments,omitempty"`
}

// ClaudeCodeTool represents a mapped tool call in Claude Code format.
type ClaudeCodeTool struct {
	Name      string                 `json:"name"`
	Arguments map[string]interface{} `json:"arguments,omitempty"`
}

// ============================================================================
// Tool name mapping
// ============================================================================

// warpToClaudeToolMap maps Warp tool names to Claude Code tool names.
// From decompiled: MapToolToClaudeCode switch cases on tool names:
//   "grep" (4 bytes, 0x70657267)
//   "subagent" (8 bytes, 0x746e656761627573)
//   "file_glob" (9 bytes, 0x6f6c675f656c6966 + 'b')
//   "read_files" (10 bytes)
//   "edit_file" (9 bytes)
//   "write_file" (10 bytes)
//   "run_command" (11 bytes)
//   "list_directory" (14 bytes)
var warpToClaudeToolMap = map[string]string{
	"grep":           "Grep",
	"subagent":       "Task",
	"file_glob":      "Glob",
	"read_files":     "Read",
	"edit_file":      "Edit",
	"write_file":     "Write",
	"run_command":    "Bash",
	"list_directory": "ListDirectory",
	"search_files":   "Search",
	"create_file":    "Write",
}
