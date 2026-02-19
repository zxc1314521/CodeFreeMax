package antigravity

// request.go — Build the Gemini API request body.
//
// Core function:
//   - buildAntigravityRequest (3584B @ 0x17af640): builds the full generateContent request
//   - convertToolsToFunctionDeclarations: converts OpenAI tools to Gemini function declarations
//
// The Gemini generateContent request structure:
// {
//   "contents": [...],                    // from convertMessagesToContents
//   "safetySettings": [...],              // 5 harm categories, all set to BLOCK_NONE
//   "generationConfig": {
//     "candidateCount": 1,
//     "responseMimeType": "text/plain",
//     "thinkingConfig": {...}             // if thinking mode enabled
//   },
//   "systemInstruction": {               // if system message present
//     "role": "user",
//     "parts": [{"text": "..."}]
//   },
//   "tools": [{"functionDeclarations": [...]}],  // if tools present
//   "toolConfig": {"functionCallingConfig": {"mode": "AUTO"}}
// }

import (
	"github.com/google/uuid"
)

// ============================================================================
// Safety Settings
// ============================================================================

// Safety setting categories from decompiled code.
// Each has "category" and "threshold" fields.
// PTR_DAT_01f3a240 through PTR_DAT_01f3a290 are the 5 harm category strings.
// PTR_DAT_01f3a250 is the threshold value "BLOCK_NONE" (shared across all).

var safetySettings = []map[string]interface{}{
	{"category": "HARM_CATEGORY_HARASSMENT", "threshold": "BLOCK_NONE"},
	{"category": "HARM_CATEGORY_HATE_SPEECH", "threshold": "BLOCK_NONE"},
	{"category": "HARM_CATEGORY_SEXUALLY_EXPLICIT", "threshold": "BLOCK_NONE"},
	{"category": "HARM_CATEGORY_DANGEROUS_CONTENT", "threshold": "BLOCK_NONE"},
	{"category": "HARM_CATEGORY_CIVIC_INTEGRITY", "threshold": "BLOCK_NONE"},
}

// ============================================================================
// buildAntigravityRequest
// ============================================================================

// AntigravityRequest represents the full Gemini API request.
type AntigravityRequest struct {
	Model             string                   `json:"model"`
	ModelID           string                   `json:"modelId"`
	Method            string                   `json:"method"`
	APIVersion        string                   `json:"apiVersion"`
	Endpoint          string                   `json:"endpoint"`
	Contents          []map[string]interface{}  `json:"contents"`
	SafetySettings    []map[string]interface{}  `json:"safetySettings"`
	GenerationConfig  map[string]interface{}    `json:"generationConfig"`
	SystemInstruction map[string]interface{}    `json:"systemInstruction,omitempty"`
	Tools             []map[string]interface{}  `json:"tools,omitempty"`
	ToolConfig        map[string]interface{}    `json:"toolConfig,omitempty"`
	RequestID         string                   `json:"requestId"`
}

// buildAntigravityRequest builds the complete Gemini generateContent request body.
// Symbol: kiro2api/internal/logic/antigravity.buildAntigravityRequest (3584B @ 0x17af640)
//
// Parameters:
//   - modelName: the requested model name (e.g. "gemini-2.0-flash", "claude-*")
//   - modelNameLen: length of model name string
//   - chatReq: the parsed OpenAI ChatCompletionRequest
//   - account: the antigravity account with credentials
//   - supportsThinking: whether the model supports thinking mode (byte param_5)
//
// Decompiled parameter mapping:
//   param_1 (int*) + param_2 (ulong) = model name string (ptr + len)
//   param_3 = unused
//   param_4 = chatReq pointer (lStack0000000000000018)
//   param_5 = supportsThinking flag (bStack0000000000000030)
//   unaff_RBX = account pointer (lStack0000000000000010)
func (s *sAntigravity) buildAntigravityRequest(
	modelName string,
	chatReq map[string]interface{},
	account map[string]interface{},
	supportsThinking bool,
) *AntigravityRequest {

	// Get messages from chatReq and convert to Gemini contents
	messages, _ := chatReq["messages"].([]map[string]interface{})
	contents := s.convertMessagesToContents(messages)

	// If thinking mode is NOT supported, clean thinking fields
	// Decompiled: if (bStack0000000000000030 == 0) { for ... cleanThinkingFieldsRecursive() }
	if !supportsThinking {
		for _, content := range contents {
			cleanThinkingFieldsRecursive(content)
		}
	}

	// Build the request body map
	requestBody := map[string]interface{}{
		"contents": contents,
	}

	// === Safety Settings ===
	// 5 harm categories, each with category + threshold = "BLOCK_NONE"
	// Decompiled: 5 iterations of runtime_makemap_small + mapassign_faststr("category", ...) + mapassign_faststr("threshold", ...)
	requestBody["safetySettings"] = safetySettings

	// === Generation Config ===
	// Decompiled: map with "candidateCount" → 1, "responseMimeType" → "text/plain"
	generationConfig := map[string]interface{}{
		"candidateCount":   1,
		"responseMimeType": "text/plain",
	}

	// === System Instruction ===
	// Decompiled: if chatReq[0x40] != 0 (system message exists)
	// Gets system message text via getContentText, wraps in {"role": "user", "parts": [{"text": ...}]}
	if systemMsg, ok := chatReq["system"]; ok && systemMsg != nil {
		systemText := getContentText(systemMsg)
		if systemText != "" {
			systemInstruction := map[string]interface{}{
				"role": "user",
				"parts": []interface{}{
					map[string]interface{}{
						"text": systemText,
					},
				},
			}
			requestBody["systemInstruction"] = systemInstruction
		}
	}

	// === Thinking Config ===
	// Decompiled: if supportsThinking && model starts with "claude" (0x75616c63 + 0x6564)
	//   → thinkingConfig with "thinkingBudget" = 10000 (PTR_DAT_01f38728)
	// else if supportsThinking && chatReq has maxTokens
	//   → thinkingConfig with "thinkingBudget" = maxTokens, "includeThoughts" = true
	if supportsThinking {
		if len(modelName) >= 6 && modelName[:6] == "claude" {
			// Claude models: set thinking budget to a fixed value
			generationConfig["thinkingConfig"] = map[string]interface{}{
				"thinkingBudget": 10000,
				"includeThoughts": true,
			}
		} else if maxTokens, ok := chatReq["max_tokens"]; ok && maxTokens != nil {
			// Other models: use max_tokens as thinking budget
			generationConfig["thinkingConfig"] = map[string]interface{}{
				"thinkingBudget":  maxTokens,
				"includeThoughts": true,
			}
		}
	}

	requestBody["generationConfig"] = generationConfig

	// === Tools / Function Declarations ===
	// Decompiled: if chatReq[0x58] != 0 (tools present)
	// Calls convertToolsToFunctionDeclarations, then wraps in:
	//   "tools": [{"functionDeclarations": [...]}]
	//   "toolConfig": {"functionCallingConfig": {"mode": "AUTO"}}
	if tools, ok := chatReq["tools"]; ok && tools != nil {
		toolsList, _ := tools.([]interface{})
		if len(toolsList) > 0 {
			functionDeclarations := s.convertToolsToFunctionDeclarations(toolsList)
			if len(functionDeclarations) > 0 {
				requestBody["tools"] = []interface{}{
					map[string]interface{}{
						"functionDeclarations": functionDeclarations,
					},
				}
				requestBody["toolConfig"] = map[string]interface{}{
					"functionCallingConfig": map[string]interface{}{
						"mode": "AUTO",
					},
				}
			}
		}
	}

	// === Build final request struct ===
	// Decompiled: gets endpoint from account[0x58]+account[0x60]
	// Falls back to default endpoint "generativelanguage.googleapis.com/v1beta" (0x14 = 20 bytes at DAT_01c570d6)
	endpoint, _ := account["endpoint"].(string)
	if endpoint == "" {
		endpoint = "generativelanguage.googleapis.com/v1beta"
	}

	requestID := uuid.NewString()

	req := &AntigravityRequest{
		Model:    modelName,
		ModelID:  modelName,
		Method:   "POST",
		APIVersion: "v1beta",
		Endpoint: endpoint,
		RequestID: requestID,
	}

	// Store the request body in the struct fields
	req.Contents, _ = requestBody["contents"].([]map[string]interface{})
	req.SafetySettings, _ = requestBody["safetySettings"].([]map[string]interface{})
	req.GenerationConfig, _ = requestBody["generationConfig"].(map[string]interface{})
	if si, ok := requestBody["systemInstruction"].(map[string]interface{}); ok {
		req.SystemInstruction = si
	}
	if t, ok := requestBody["tools"].([]map[string]interface{}); ok {
		req.Tools = t
	}
	if tc, ok := requestBody["toolConfig"].(map[string]interface{}); ok {
		req.ToolConfig = tc
	}

	return req
}

// ============================================================================
// convertToolsToFunctionDeclarations
// ============================================================================

// convertToolsToFunctionDeclarations converts OpenAI-format tools to Gemini function declarations.
// Symbol: kiro2api/internal/logic/antigravity.(*sAntigravity).convertToolsToFunctionDeclarations
// Referenced at offset 0x17af640+0x508 in buildAntigravityRequest.
//
// OpenAI tool format:
//   {"type": "function", "function": {"name": "...", "description": "...", "parameters": {...}}}
//
// Gemini function declaration format:
//   {"name": "...", "description": "...", "parameters": {...}}
func (s *sAntigravity) convertToolsToFunctionDeclarations(tools []interface{}) []interface{} {
	var declarations []interface{}

	for _, tool := range tools {
		toolMap, ok := tool.(map[string]interface{})
		if !ok {
			continue
		}

		toolType, _ := toolMap["type"].(string)
		if toolType != "function" {
			continue
		}

		fn, ok := toolMap["function"].(map[string]interface{})
		if !ok {
			continue
		}

		declaration := map[string]interface{}{
			"name":        fn["name"],
			"description": fn["description"],
		}

		if params, ok := fn["parameters"]; ok && params != nil {
			declaration["parameters"] = params
		}

		declarations = append(declarations, declaration)
	}

	return declarations
}
