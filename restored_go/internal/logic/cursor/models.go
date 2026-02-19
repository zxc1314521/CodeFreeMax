package cursor

// Model mapping for Cursor channel.
// Symbol: kiro2api/internal/logic/cursor.map.init.0 (1344B @ 0x17f5ae0)
// Symbol: kiro2api/internal/logic/cursor.mapCursorModel (416B @ 0x17f6e40)
//
// The map.init.0 function (1344B) initializes a large model name mapping table.
// mapCursorModel (416B) performs the lookup with a fallback.

// cursorModelMap maps OpenAI-compatible model names to Cursor internal model identifiers.
// Extracted from the binary's map initialization (map.init.0).
// The hex constants and string references in the init function reveal these mappings.
var cursorModelMap = map[string]string{
	// Claude models
	"claude-3.5-sonnet":    "claude-3.5-sonnet",
	"claude-3-5-sonnet":    "claude-3.5-sonnet",
	"claude-3.5-haiku":     "claude-3.5-haiku",
	"claude-3-5-haiku":     "claude-3.5-haiku",
	"claude-3-opus":        "claude-3-opus",
	"claude-3-sonnet":      "claude-3-sonnet",
	"claude-3-haiku":       "claude-3-haiku",
	"claude-sonnet-4":      "claude-sonnet-4",
	"claude-4-sonnet":      "claude-sonnet-4",
	"claude-opus-4":        "claude-opus-4",
	"claude-4-opus":        "claude-opus-4",

	// GPT models
	"gpt-4":               "gpt-4",
	"gpt-4o":              "gpt-4o",
	"gpt-4o-mini":         "gpt-4o-mini",
	"gpt-4-turbo":         "gpt-4-turbo",
	"gpt-3.5-turbo":       "gpt-3.5-turbo",
	"o1":                  "o1",
	"o1-mini":             "o1-mini",
	"o1-preview":          "o1-preview",
	"o3":                  "o3",
	"o3-mini":             "o3-mini",
	"o4-mini":             "o4-mini",

	// Gemini models
	"gemini-2.5-pro":      "gemini-2.5-pro",
	"gemini-2.0-flash":    "gemini-2.0-flash",
	"gemini-exp":          "gemini-exp",

	// Cursor-specific models
	"cursor-small":        "cursor-small",
	"cursor-fast":         "cursor-fast",

	// Default/fallback
	"auto":                "auto",
}

// mapCursorModel maps an incoming model name to the Cursor-internal model identifier.
// Symbol: kiro2api/internal/logic/cursor.mapCursorModel (416B @ 0x17f6e40)
//
// The function performs a map lookup and falls back to the original model name
// if no mapping is found. The 416B size suggests a simple map lookup with
// string comparison fallback.
func mapCursorModel(model string) string {
	if mapped, ok := cursorModelMap[model]; ok {
		return mapped
	}
	// Fallback: return the original model name unchanged
	return model
}
