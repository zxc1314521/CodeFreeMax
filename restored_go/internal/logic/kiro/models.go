package kiro

// models.go — Data structures for the Kiro channel (AWS Q Developer API).
//
// The real Kiro API uses the generateAssistantResponse endpoint with:
//   Request: { conversationState: { chatTriggerType, conversationId, currentMessage, history }, profileArn? }
//   Response: AWS Event Stream binary protocol with assistantResponseEvent, toolUseEvent, etc.

// ============================================================================
// Request Structures (generateAssistantResponse format)
// ============================================================================

// GenerateAssistantRequest is the top-level request to generateAssistantResponse.
// Real format: { conversationState: {...}, profileArn?: "..." }
// For Builder ID users, profileArn is undefined (omitted).
// For IDC/Pro users, profileArn is the IAM Identity Center profile ARN.
type GenerateAssistantRequest struct {
	ConversationState *ConversationState `json:"conversationState"`
	ProfileArn        string             `json:"profileArn,omitempty"`
}

// ConversationState holds the conversation context.
type ConversationState struct {
	ChatTriggerType     string           `json:"chatTriggerType"`
	ConversationID      string           `json:"conversationId"`
	CurrentMessage      *CurrentMessage  `json:"currentMessage"`
	History             []HistoryMessage `json:"history,omitempty"`
	AgentContinuationID string           `json:"agentContinuationId,omitempty"`
	AgentTaskType       string           `json:"agentTaskType,omitempty"`
}

// CurrentMessage wraps the user input message.
type CurrentMessage struct {
	UserInputMessage *UserInputMessage `json:"userInputMessage"`
}

// UserInputMessage is the actual user message content.
type UserInputMessage struct {
	Content                 string                   `json:"content"`
	ModelID                 string                   `json:"modelId,omitempty"`
	Origin                  string                   `json:"origin"`
	UserInputMessageContext *UserInputMessageContext  `json:"userInputMessageContext,omitempty"`
	Images                  []ImageBlock              `json:"images,omitempty"`
}

// UserInputMessageContext holds tools, tool results, and editor state for the current message.
type UserInputMessageContext struct {
	Tools       []KiroToolDef    `json:"tools,omitempty"`
	ToolResults []KiroToolResult `json:"toolResults,omitempty"`
	EditorState *EditorState     `json:"editorState,omitempty"`
}

// EditorState represents the editor state context (can be empty object {}).
type EditorState struct {}

// ImageBlock represents an image in a message.
type ImageBlock struct {
	Format string `json:"format"`
	Source struct {
		Bytes string `json:"bytes"` // base64 encoded
	} `json:"source"`
}

// HistoryMessage is a message in the conversation history.
// Can be either userInputMessage or assistantResponseMessage.
type HistoryMessage struct {
	UserInputMessage         *UserInputMessage         `json:"userInputMessage,omitempty"`
	AssistantResponseMessage *AssistantResponseMessage  `json:"assistantResponseMessage,omitempty"`
}

// AssistantResponseMessage represents an assistant response in history.
type AssistantResponseMessage struct {
	Content   string `json:"content"`
	MessageID string `json:"messageId,omitempty"`
}

// KiroToolDef represents a tool definition in the Kiro API format.
// The API wraps tool specs in { toolSpecification: { name, description, inputSchema: { json: ... } } }
type KiroToolDef struct {
	ToolSpecification *ToolSpecification `json:"toolSpecification,omitempty"`
}

// ToolSpecification is the inner tool spec.
type ToolSpecification struct {
	Name        string           `json:"name"`
	Description string           `json:"description,omitempty"`
	InputSchema *ToolInputSchema `json:"inputSchema,omitempty"`
}

// ToolInputSchema wraps the JSON schema for a tool's input.
type ToolInputSchema struct {
	JSON interface{} `json:"json,omitempty"`
}

// KiroToolResult represents a tool result.
type KiroToolResult struct {
	Content   []ToolResultContent `json:"content"`
	Status    string              `json:"status"`
	ToolUseID string              `json:"toolUseId"`
}

// ToolResultContent is the content of a tool result.
type ToolResultContent struct {
	Text string `json:"text"`
}

// ============================================================================
// Internal Request Structures (buildKiroRequest output)
// ============================================================================

// KiroRequest is the internal request structure produced by buildKiroRequest.
// It is serialized to JSON and sent to the AWS Q Developer chat endpoint.
type KiroRequest struct {
	Model          string              `json:"model"`
	ConversationID string              `json:"conversationId"`
	ParentMessage  *KiroParentMessage  `json:"parentMessage"`
	Messages       []KiroMessage       `json:"messages"`
	Context        interface{}         `json:"context,omitempty"`
	Tools          []KiroToolDef       `json:"tools,omitempty"`
}

// KiroParentMessage is the parent message metadata in a KiroRequest.
type KiroParentMessage struct {
	Role          string                 `json:"role"`
	Model         string                 `json:"model"`
	Type          string                 `json:"type"`
	Headers       map[string]interface{} `json:"headers,omitempty"`
	SystemMessage string                 `json:"systemMessage,omitempty"`
}

// KiroMessage represents a single message in the KiroRequest messages array.
// Content can be a plain string or a []interface{} of content blocks.
type KiroMessage struct {
	Role    string      `json:"role"`
	Content interface{} `json:"content"`
}

// ============================================================================
// AWS Event Stream Response Structures
// ============================================================================

// EventStreamMessage represents a parsed AWS Event Stream binary message.
type EventStreamMessage struct {
	EventType   string
	ContentType string
	MessageType string
	Payload     []byte
	TotalLength uint32
	NextOffset  int
}

// AssistantResponseEvent is the payload of an assistantResponseEvent.
type AssistantResponseEvent struct {
	Content string `json:"content"`
}

// ToolUseEvent is the payload of a toolUseEvent.
type ToolUseEvent struct {
	Name      string `json:"name"`
	ToolUseID string `json:"toolUseId"`
	Input     string `json:"input"`
	Stop      bool   `json:"stop"`
}

// MeteringEvent is the payload of a meteringEvent.
type MeteringEvent struct {
	Usage int    `json:"usage"`
	Unit  string `json:"unit"`
}

// MessageMetadataEvent is the payload of a messageMetadataEvent.
type MessageMetadataEvent struct {
	ConversationID string `json:"conversationId"`
}

// ReasoningContentEvent is the payload of a reasoningContentEvent.
type ReasoningContentEvent struct {
	Text          string `json:"text"`
	ReasoningText string `json:"reasoningText"`
}

// FollowupPromptEvent is the payload of a followupPromptEvent.
type FollowupPromptEvent struct {
	FollowupPrompt string `json:"followupPrompt"`
}

// KiroToolUseEvent represents a tool use event being accumulated during streaming.
type KiroToolUseEvent struct {
	ID    string
	Name  string
	Input string
}

// KiroUsage represents token usage information.
type KiroUsage struct {
	InputTokens  int
	OutputTokens int
}

// ============================================================================
// Usage Limits Structures (CodeWhisperer API)
// ============================================================================

// CodeWhispererUsageResponse represents the response from
// https://codewhisperer.us-east-1.amazonaws.com/getUsageLimits
type CodeWhispererUsageResponse struct {
	DaysUntilReset     *int                    `json:"daysUntilReset,omitempty"`
	NextDateReset      *float64                `json:"nextDateReset,omitempty"`
	UserInfo           *CWUserInfo             `json:"userInfo,omitempty"`
	SubscriptionInfo   *CWSubscriptionInfo     `json:"subscriptionInfo,omitempty"`
	UsageBreakdownList []CWUsageBreakdown      `json:"usageBreakdownList,omitempty"`
	OverageConfig      *CWOverageConfiguration `json:"overageConfiguration,omitempty"`
}

type CWUserInfo struct {
	Email  string `json:"email,omitempty"`
	UserID string `json:"userId,omitempty"`
}

type CWSubscriptionInfo struct {
	SubscriptionTitle string `json:"subscriptionTitle,omitempty"`
	Type              string `json:"type,omitempty"`
}

type CWOverageConfiguration struct {
	OverageStatus string `json:"overageStatus,omitempty"`
}

type CWUsageBreakdown struct {
	UsageLimit                 *int            `json:"usageLimit,omitempty"`
	CurrentUsage               *int            `json:"currentUsage,omitempty"`
	UsageLimitWithPrecision    *float64        `json:"usageLimitWithPrecision,omitempty"`
	CurrentUsageWithPrecision  *float64        `json:"currentUsageWithPrecision,omitempty"`
	NextDateReset              *float64        `json:"nextDateReset,omitempty"`
	FreeTrialInfo              *CWFreeTrialInfo `json:"freeTrialInfo,omitempty"`
	Bonuses                    []CWBonusInfo   `json:"bonuses,omitempty"`
	DisplayName                string          `json:"displayName,omitempty"`
	ResourceType               string          `json:"resourceType,omitempty"`
	Unit                       string          `json:"unit,omitempty"`
}

type CWFreeTrialInfo struct {
	UsageLimit   *int    `json:"usageLimit,omitempty"`
	CurrentUsage *int    `json:"currentUsage,omitempty"`
	Status       string  `json:"freeTrialStatus,omitempty"`
}

type CWBonusInfo struct {
	BonusCode   string   `json:"bonusCode,omitempty"`
	DisplayName string   `json:"displayName,omitempty"`
	UsageLimit  *float64 `json:"usageLimit,omitempty"`
	CurrentUsage *float64 `json:"currentUsage,omitempty"`
	Status      string   `json:"status,omitempty"`
}

// UsageLimits is kept for backward compatibility with buildUsageLimitsHeaders in chat.go
type UsageLimits struct {
	TierID       string         `json:"tierId,omitempty"`
	MonthlyUsage map[string]int64 `json:"monthlyUsage,omitempty"`
	DailyUsage   map[string]int64 `json:"dailyUsage,omitempty"`
	Limits       map[string]int64 `json:"limits,omitempty"`
}

// ============================================================================
// Auth Structures
// ============================================================================

// KiroTokenResponse represents the token refresh response.
// From decompiled: authRefresh (1280B @ 0x17a14a0) parses the response.
type KiroTokenResponse struct {
	AccessToken  string `json:"accessToken"`
	ExpiresIn    int64  `json:"expiresIn"`
	RefreshToken string `json:"refreshToken,omitempty"`
	TokenType    string `json:"tokenType,omitempty"`
	IDToken      string `json:"idToken,omitempty"`
}

// KiroAccount represents the account fields used by the kiro channel.
// Updated: Removed OIDC-specific fields (client_id, client_secret, start_url, idc_base_url),
// added Kiro auth service URL field.
type KiroAccount struct {
	ID           int64  `json:"id"`
	AccessToken  string `json:"access_token"`
	RefreshToken string `json:"refresh_token"`
	TokenExpiry  int64  `json:"token_expiry"`
	Region       string `json:"region"`
	Endpoint     string `json:"endpoint"`
	ProxyURL     string `json:"proxy_url"`
	AuthBaseURL  string `json:"auth_base_url"` // Kiro auth service URL override
}
