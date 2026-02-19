package orchids

// tool_mapper.go — Tool name mapping and input transformation for the Orchids channel.
//
// Two core functions:
//   - TransformToolInput  (0x1768d40): Transforms tool input parameters to match Orchids expectations
//   - MapToolNameToClient (0x1767bc0): Maps tool names between Orchids and Anthropic/client formats
//
// Orchids uses its own tool naming convention that differs from Anthropic's.
// These functions handle the bidirectional mapping and input format transformation.

import (
	"strings"
)

// ============================================================================
// ToolMapper
// ============================================================================

// ToolMapper manages the mapping between client tool definitions and Orchids tool names.
// From decompiled: kiro2api_internal_logic_orchids_ToolMapper_buildIndex()
type ToolMapper struct {
	// tools is the original tool definitions from the client request
	Tools []map[string]interface{}
	// index maps normalized tool names to their definitions
	index map[string]map[string]interface{}
}

// buildIndex builds the tool name index for fast lookup.
// From decompiled: kiro2api_internal_logic_orchids_ToolMapper_buildIndex(uStack_148)
func (tm *ToolMapper) buildIndex() {
	tm.index = make(map[string]map[string]interface{}, len(tm.Tools))
	for _, tool := range tm.Tools {
		if name, ok := tool[keyName].(string); ok {
			tm.index[strings.ToLower(name)] = tool
		}
	}
}

// ============================================================================
// NormalizedTool
// ============================================================================

// NormalizedTool holds the normalized form of a tool name for matching.
// From decompiled: kiro2api_internal_logic_orchids_NormalizeToolName()
// The struct has fields at offsets:
//   0x00: original name (string)
//   0x08: original name length
//   0x18: lowercase name (string)
//   0x20: lowercase name length
//   0x28: snake_case name (string)
//   0x30: snake_case name length
type NormalizedTool struct {
	Original  string // offset 0x00
	Lowercase string // offset 0x18
	SnakeCase string // offset 0x28
}

// NormalizeToolName normalizes a tool name for matching.
// From decompiled: kiro2api_internal_logic_orchids_NormalizeToolName()
func NormalizeToolName(name string) *NormalizedTool {
	if name == "" {
		return &NormalizedTool{}
	}
	lower := strings.ToLower(name)
	snake := toSnakeCase(lower)
	return &NormalizedTool{
		Original:  name,
		Lowercase: lower,
		SnakeCase: snake,
	}
}

// ============================================================================
// TransformToolInput
// ============================================================================

// TransformToolInput transforms tool input parameters to match Orchids format.
// Symbol: kiro2api/internal/logic/orchids.TransformToolInput (@ 0x1768d40)
//
// The function handles several tool type patterns based on the tool name:
//
// 1. "ls" (2 bytes, 0x736c) with argument containing "/" → pass through
// 2. "ls" + "glob" (global ls) → wrap in {"path": ..., "type": "glob"} format
//    - Decompiled: checks (short)*plStack_d8 == 0x736c (ls) and lStack_108 == 4 && *piStack_88 == 0x626f6c67 (glob)
// 3. "list" (4 bytes, 0x7473696c) or "glob" (4 bytes, 0x626f6c67) with "/" → pass through
// 4. "ls" with "." in path → pass through
// 5. "read" (4 bytes, 0x64616572) or "readfile" (8 bytes, 0x656c696664616572):
//    - Extract "file_path" or "path" from input
//    - If contains "/" separator → extract path component
//    - Build new map with "file_path" key
// 6. "bash" tool (4 bytes, 0x68736162) or tools containing "edit"/"write":
//    - Extract "content" field
//    - If content has value, wrap as string
//    - Extract "path" field, append to new map
// 7. Default: pass through original input
//
// Parameters:
//   toolName: the normalized tool name (lowercase)
//   funcName: the original function name
//   input:    the tool input map
//
// Returns: transformed input map
func TransformToolInput(toolName, funcName string, input map[string]interface{}) map[string]interface{} {
	if input == nil {
		input = make(map[string]interface{})
	}

	lowerTool := strings.ToLower(toolName)
	lowerFunc := strings.ToLower(funcName)

	// Pattern 1 & 3: "ls", "list", "glob" with "/" in content → pass through
	// Decompiled: (short)*plStack_d8 == 0x736c (ls) → Index("/")
	// Also: (int)*plStack_d8 == 0x626f6c67 (glob) or 0x7473696c (list) → Index("/")
	if lowerTool == "ls" || lowerTool == "list" || lowerTool == "glob" {
		if strings.Contains(lowerFunc, "/") {
			return input
		}
	}

	// Pattern 2: "ls" tool with "glob" function → wrap with type
	// Decompiled: (short)*plStack_d8 == 0x736c && lStack_108 == 4 && *piStack_88 == 0x626f6c67
	if lowerTool == "ls" && lowerFunc == "glob" {
		result := make(map[string]interface{})
		// Copy all entries from input
		for k, v := range input {
			result[k] = v
		}
		// Ensure "content" key exists with type info
		// Decompiled: mapaccess2_faststr(7) for "content" → if not found, add default
		if _, ok := result[keyContent]; !ok {
			result[keyContent] = []interface{}{}
		}
		return result
	}

	// Pattern 4: "ls" with "." → pass through
	// Decompiled: (short)*plStack_d8 == 0x736c && Index(".")
	if lowerTool == "ls" && strings.Contains(lowerFunc, ".") {
		return input
	}

	// Pattern 5: "read" or "readfile" → extract and normalize file_path
	// Decompiled: (int)*plStack_d8 == 0x64616572 (read) or *plStack_d8 == 0x656c696664616572 (readfile)
	if lowerTool == "read" || lowerTool == "readfile" {
		result := make(map[string]interface{})

		// Try to get file_path first (9 bytes: "file_path")
		// Decompiled: mapaccess1_faststr(9) for "file_path"
		filePath := ""
		if fp, ok := getStringField(input, keyFilePath); ok && fp != "" {
			filePath = fp
		} else if fp, ok := getStringField(input, keyPath); ok && fp != "" {
			// Fallback to "path" (4 bytes)
			// Decompiled: mapaccess1_faststr(4) for "path"
			filePath = fp
		}

		// Check for "/" separator in path
		// Decompiled: internal_stringslite_Index(10, ..., "/")
		if idx := strings.Index(filePath, "/"); idx >= 0 {
			// Has path separator — use as-is
		}

		// Also check for "file_path" in nested content
		// Decompiled: mapaccess1_faststr(10, ..., "file_path")
		if filePath == "" {
			if content, ok := input[keyContent].(string); ok && content != "" {
				filePath = content
			}
		}

		// Build result with normalized "file_path" key
		// Decompiled: mapassign_faststr(10) for "file_path"
		result[keyFilePath] = filePath

		// Copy other fields except file_path and path
		for k, v := range input {
			if k != keyFilePath && k != keyPath {
				result[k] = v
			}
		}

		return result
	}

	// Pattern 6: "bash" tool or tools with "edit"/"write" in name
	// Decompiled: (int)*plStack_d8 == 0x68736162 (bash)
	// Also: Index("edit") or Index("write")
	if lowerTool == "bash" || strings.Contains(lowerTool, "edit") || strings.Contains(lowerTool, "write") {
		result := make(map[string]interface{})

		// Extract "content" field
		// Decompiled: mapaccess1_faststr(7) for "content"
		if content, ok := getStringField(input, keyContent); ok && content != "" {
			result[keyContent] = content
		}

		// Extract "path" field
		// Decompiled: mapaccess1_faststr(4) for "path"
		if path, ok := getStringField(input, keyPath); ok && path != "" {
			// Concatenate path with content if both exist
			// Decompiled: runtime_concatstring2(content, path, "\n", 7)
			if existingContent, ok := result[keyContent].(string); ok && existingContent != "" {
				result[keyContent] = existingContent + "\n" + path
			} else {
				result[keyContent] = path
			}
		} else {
			// If no path, add default empty
			// Decompiled: mapassign_faststr(7) → PTR_DAT_01f3a1d0
			if _, ok := result[keyContent]; !ok {
				result[keyContent] = ""
			}
		}

		return result
	}

	// Default: pass through
	return input
}

// ============================================================================
// MapToolNameToClient
// ============================================================================

// MapToolNameToClient maps an Orchids tool name back to the client's tool name.
// Symbol: kiro2api/internal/logic/orchids.MapToolNameToClient (@ 0x1767bc0)
//
// The matching algorithm tries multiple strategies in order:
//  1. Exact match on original name
//  2. Match on lowercase name
//  3. Match on snake_case name
//  4. Reverse lookup via alias map (mapaccess2_faststr on snake_case)
//  5. Alias-based matching with case-insensitive comparison
//  6. Reverse alias lookup on each client tool's snake_case
//  7. EqualFold (case-insensitive) match on alias values
//  8. Fuzzy matching with scoring (match count, distance)
//  9. Fallback to MapOrchidsToolToAnthropic
//
// Parameters:
//   orchidsName: the tool name as returned by Orchids
//   clientTools: the client's original tool definitions (from request)
//   toolMapper:  optional ToolMapper with alias index
//
// Returns: the client-side tool name
func MapToolNameToClient(
	orchidsName string,
	clientTools []map[string]interface{},
	toolMapper *ToolMapper,
) string {
	normalized := NormalizeToolName(orchidsName)

	// If normalized name is empty, return original
	// Decompiled: if *(long *)(lVar5 + 8) == 0 → return uStack0000000000000010
	if normalized.Original == "" {
		return orchidsName
	}

	// If no client tools, fall back to MapOrchidsToolToAnthropic
	// Decompiled: if lVar18 == 0 → MapOrchidsToolToAnthropic()
	if len(clientTools) == 0 {
		return MapOrchidsToolToAnthropic(orchidsName)
	}

	// Strategy 1: Exact match on original name
	// Decompiled: first for loop comparing *(long *)(lVar5 + 8) == puVar6[1] + memequal
	for _, tool := range clientTools {
		if name, ok := tool[keyName].(string); ok {
			if name == normalized.Original {
				return name
			}
		}
	}

	// Strategy 2: Match on lowercase name
	// Decompiled: second for loop comparing *(lVar5 + 0x18) with puVar6[2]+0x18
	for _, tool := range clientTools {
		if name, ok := tool[keyName].(string); ok {
			if strings.ToLower(name) == normalized.Lowercase {
				return name
			}
		}
	}

	// Strategy 3: Match on snake_case name
	// Decompiled: third for loop comparing *(lVar5 + 0x28) with puVar6[2]+0x28
	for _, tool := range clientTools {
		if name, ok := tool[keyName].(string); ok {
			if toSnakeCase(strings.ToLower(name)) == normalized.SnakeCase {
				return name
			}
		}
	}

	// Strategy 4: Reverse lookup via global alias map
	// Decompiled: mapaccess2_faststr on snake_case → get alias list → iterate
	if aliases, ok := orchidsToolAliases[normalized.SnakeCase]; ok {
		for _, tool := range clientTools {
			if name, ok := tool[keyName].(string); ok {
				for _, alias := range aliases {
					toolSnake := toSnakeCase(strings.ToLower(name))
					if toolSnake == alias {
						return name
					}
					// Also try lowercase comparison
					if strings.ToLower(name) == alias {
						return name
					}
				}
			}
		}
	}

	// Strategy 5: Reverse alias lookup on each client tool
	// Decompiled: for each client tool, mapaccess2_faststr on its snake_case
	for _, tool := range clientTools {
		if name, ok := tool[keyName].(string); ok {
			toolSnake := toSnakeCase(strings.ToLower(name))
			if toolAliases, ok := orchidsToolAliases[toolSnake]; ok {
				for _, alias := range toolAliases {
					if alias == normalized.SnakeCase {
						return name
					}
					if alias == normalized.Lowercase {
						return name
					}
				}
			}
		}
	}

	// Strategy 6: Case-insensitive match via EqualFold on aliases
	// Decompiled: mapaccess2_faststr → strings_EqualFold
	if aliases, ok := orchidsToolAliases[normalized.SnakeCase]; ok {
		for _, tool := range clientTools {
			if name, ok := tool[keyName].(string); ok {
				for _, alias := range aliases {
					if strings.EqualFold(name, alias) {
						return name
					}
				}
			}
		}
	}

	// Strategy 7: Fuzzy matching with scoring
	// Decompiled: complex scoring loop with match count and distance
	// Only used when toolMapper is provided with tool count > 0
	if toolMapper != nil && len(toolMapper.Tools) > 0 {
		type candidate struct {
			name       string
			matchCount int
			distance   int
		}

		// Collect alias keys for matching
		aliasKeys := collectAliasKeys(toolMapper)

		var candidates []candidate

		for _, tool := range clientTools {
			name, ok := tool[keyName].(string)
			if !ok {
				continue
			}

			// Check if tool has aliases
			toolAliases := getToolAliases(tool)
			if toolAliases == nil {
				continue
			}
			aliasCount := len(toolAliases)

			// Count how many alias keys match
			matchCount := 0
			for _, ak := range aliasKeys {
				if _, found := toolMapper.index[ak]; found {
					break
				}
				matchCount++
			}

			if matchCount >= len(aliasKeys) && len(aliasKeys) > 0 {
				distance := aliasCount - matchCount
				candidates = append(candidates, candidate{
					name:       name,
					matchCount: matchCount,
					distance:   distance,
				})
			}
		}

		// Select best candidate (highest matchCount, lowest distance)
		if len(candidates) > 0 {
			best := candidates[0]
			for _, c := range candidates[1:] {
				if c.matchCount > best.matchCount ||
					(c.matchCount == best.matchCount && c.distance < best.distance) {
					best = c
				}
			}
			return best.name
		}
	}

	// Strategy 8: Final fallback to MapOrchidsToolToAnthropic
	return MapOrchidsToolToAnthropic(orchidsName)
}

// ============================================================================
// MapOrchidsToolToAnthropic
// ============================================================================

// MapOrchidsToolToAnthropic maps an Orchids-native tool name to its Anthropic equivalent.
// From decompiled: kiro2api_internal_logic_orchids_MapOrchidsToolToAnthropic()
func MapOrchidsToolToAnthropic(orchidsName string) string {
	if mapped, ok := orchidsToAnthropicMap[orchidsName]; ok {
		return mapped
	}
	return orchidsName
}

// ============================================================================
// Alias Maps
// ============================================================================

// orchidsToolAliases maps tool snake_case names to their known aliases.
// Built from the decompiled map initialization code.
// Decompiled: mapassign_faststr with various key lengths (2, 4, 6, 7)
var orchidsToolAliases = map[string][]string{
	// "id" → "text" (2 bytes key, 4 bytes value)
	"id": {"text"},
	// "name" → "text" (4 bytes key, 4 bytes value)
	"name": {"text"},
	// "content" → "code" (7 bytes key, 4 bytes value)
	"content": {"code"},
	// "source" → "input" (6 bytes key, 5 bytes value)
	"source": {"input"},
}

// orchidsToAnthropicMap maps Orchids tool names to Anthropic tool names.
var orchidsToAnthropicMap = map[string]string{
	// Common tool name mappings
	"str_replace_editor": "str_replace_editor",
	"bash":               "bash",
	"computer":           "computer",
	"text_editor":        "text_editor",
}

// ============================================================================
// Helpers
// ============================================================================

// toSnakeCase converts a string to snake_case.
func toSnakeCase(s string) string {
	var result strings.Builder
	for i, r := range s {
		if r >= 'A' && r <= 'Z' {
			if i > 0 {
				result.WriteByte('_')
			}
			result.WriteByte(byte(r - 'A' + 'a'))
		} else if r == '-' || r == ' ' {
			result.WriteByte('_')
		} else {
			result.WriteRune(r)
		}
	}
	return result.String()
}

// collectAliasKeys collects all alias keys from the tool mapper.
func collectAliasKeys(tm *ToolMapper) []string {
	var keys []string
	for k := range tm.index {
		keys = append(keys, k)
	}
	return keys
}

// getToolAliases returns the aliases for a tool definition.
func getToolAliases(tool map[string]interface{}) []string {
	aliases, ok := tool["aliases"].([]interface{})
	if !ok {
		return nil
	}
	result := make([]string, 0, len(aliases))
	for _, a := range aliases {
		if s, ok := a.(string); ok {
			result = append(result, s)
		}
	}
	return result
}
