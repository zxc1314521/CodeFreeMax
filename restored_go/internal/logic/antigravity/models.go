package antigravity

// models.go — Model mapping for the Antigravity (Google Gemini) channel.
//
// Maps OpenAI-compatible model names to Gemini model identifiers.
// The antigravity channel supports Gemini models natively and also
// accepts Claude/GPT model names, mapping them to appropriate Gemini equivalents.
//
// From the decompiled code, model name checks include:
//   - "claude" prefix check (0x75616c63 + 0x6564, 6 bytes) → triggers special thinking config
//   - Default model fallback to "gemini-2.0-flash"

// geminiModelMap maps OpenAI-compatible model names to Gemini API model identifiers.
var geminiModelMap = map[string]string{
	// Gemini 2.5 models
	"gemini-2.5-pro":           "gemini-2.5-pro-preview-06-05",
	"gemini-2.5-flash":         "gemini-2.5-flash-preview-05-20",
	"gemini-2.5-pro-preview":   "gemini-2.5-pro-preview-06-05",
	"gemini-2.5-flash-preview": "gemini-2.5-flash-preview-05-20",

	// Gemini 2.0 models
	"gemini-2.0-flash":     "gemini-2.0-flash",
	"gemini-2.0-flash-exp": "gemini-2.0-flash-exp",

	// Gemini 1.5 models
	"gemini-1.5-pro":   "gemini-1.5-pro",
	"gemini-1.5-flash": "gemini-1.5-flash",

	// Gemini experimental
	"gemini-exp": "gemini-exp-1206",

	// Passthrough — if already a valid Gemini model ID
	"gemini-2.5-pro-preview-06-05":   "gemini-2.5-pro-preview-06-05",
	"gemini-2.5-flash-preview-05-20": "gemini-2.5-flash-preview-05-20",
}

// supportsThinkingModels lists models that support Gemini's thinking mode.
// When thinking is enabled, the request includes thinkingConfig with thinkingBudget.
var supportsThinkingModels = map[string]bool{
	"gemini-2.5-pro":                  true,
	"gemini-2.5-pro-preview-06-05":    true,
	"gemini-2.5-flash":                true,
	"gemini-2.5-flash-preview-05-20":  true,
}

// mapGeminiModel maps an incoming model name to a Gemini API model identifier.
// If the model is not found in the map, it is returned as-is (passthrough).
func mapGeminiModel(model string) string {
	if mapped, ok := geminiModelMap[model]; ok {
		return mapped
	}
	// Passthrough — assume it's already a valid Gemini model ID
	return model
}

// modelSupportsThinking checks if the given model supports Gemini thinking mode.
// From decompiled code: the thinking flag (param_5/bStack0000000000000030) controls
// whether thinkingConfig is included in the request.
func modelSupportsThinking(model string) bool {
	mapped := mapGeminiModel(model)
	return supportsThinkingModels[mapped]
}
