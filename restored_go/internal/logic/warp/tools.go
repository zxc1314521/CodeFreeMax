package warp

// tools.go — Tool name mapping between Warp and Claude Code formats.
//
// Warp has its own set of tool names that need to be mapped to/from
// Claude Code's tool naming convention. This is used when:
//   1. Receiving tool calls from Warp's response → map to Claude Code names
//   2. Sending tool results back → map Claude Code names to Warp names
//
// From decompiled:
//   - MapToolToClaudeCode   (0x1722fe0, 10144B) — Map single tool call
//   - MapToolsToClaudeCode  (0x1722160, 3712B)  — Map array of tool calls
//   - getSliceFromInterface (0x1721ec0, 672B)    — Extract slice from interface
//   - extractSkillNameFromPath (0x1725940, 256B) — Extract skill name from path
//   - sanitizeFileName      (0x1725780, 448B)    — Sanitize file names
//   - stripLineNumberPrefixes (0x1725a40, 896B)  — Strip line number prefixes
//
// MapToolToClaudeCode is 10,144 bytes — the second largest function.
// It contains a switch statement on tool name with cases for:
//   "grep"           (4 bytes,  0x70657267)
//   "subagent"       (8 bytes,  0x746e656761627573)
//   "file_glob"      (9 bytes,  0x6f6c675f656c6966 + 'b')
//   "read_files"     (10 bytes, 0x6c69665f64616572 + "es")
//   "edit_file"      (9 bytes)
//   "write_file"     (10 bytes)
//   "run_command"    (11 bytes)
//   "list_directory" (14 bytes)
//
// Each case transforms the tool arguments to match Claude Code's expected format.

import (
	"fmt"
	"path/filepath"
	"regexp"
	"strings"

	"github.com/gogf/gf/v2/frame/gins"
)

// ============================================================================
// MapToolsToClaudeCode — Map array of tool calls
// ============================================================================

// MapToolsToClaudeCode maps an array of Warp tool calls to Claude Code format.
// From decompiled: kiro2api_internal_logic_warp_MapToolsToClaudeCode (0x1722160, 3712B)
//
// Special handling for "read_files" tool:
//   - If the tool has multiple file paths, it splits into individual Read calls
//   - Each file gets its own tool call with index suffix: "Read_0", "Read_1", etc.
//   - From decompiled: checks for "read_files" (10 bytes, 0x6c69665f64616572 + "es")
//     and iterates over the file list with fmt.Sprintf("%s_%d", ...) for naming
//
// For other tools, delegates to MapToolToClaudeCode for individual mapping.
func MapToolsToClaudeCode(toolName string, args map[string]interface{},
	toolMap map[string]string) []ClaudeCodeTool {

	logger := gins.Log()

	// Special case: read_files with multiple paths
	// From decompiled: string comparison with "read_files" then getSliceFromInterface
	if toolName == "read_files" {
		paths := getSliceFromInterface(args["paths"])
		if len(paths) > 1 {
			var tools []ClaudeCodeTool
			for i, p := range paths {
				pathStr, ok := p.(string)
				if !ok {
					continue
				}

				// From decompiled: fmt.Sprintf with "%s_%d" pattern
				// and mapaccess for "type" field
				newArgs := map[string]interface{}{
					"file_path": pathStr,
				}

				// Check for line range arguments
				// From decompiled: mapaccess1_faststr for "start" and "end" fields
				if start, ok := args["start"]; ok {
					newArgs["offset"] = start
				}
				if end, ok := args["end"]; ok {
					newArgs["limit"] = end
				}

				name := fmt.Sprintf("Read_%d", i)
				tools = append(tools, ClaudeCodeTool{
					Name:      name,
					Arguments: newArgs,
				})
			}

			logger.Debugf(nil, "[Warp] Split read_files into %d individual Read calls", len(tools))
			return tools
		}
	}

	// Single tool mapping
	mapped := MapToolToClaudeCode(toolName, args, toolMap)
	return []ClaudeCodeTool{mapped}
}

// ============================================================================
// MapToolToClaudeCode — Map single tool call
// ============================================================================

// MapToolToClaudeCode maps a single Warp tool call to Claude Code format.
// From decompiled: kiro2api_internal_logic_warp_MapToolToClaudeCode (0x1722fe0, 10144B)
//
// The function contains a large switch statement on tool name length and content.
// Each case transforms the arguments to match Claude Code's expected schema.
//
// Tool mappings and argument transformations:
//
//   "grep" → "Grep"
//     - "pattern" → "pattern"
//     - "path" → "path" (optional)
//     - "include" → "glob" (optional)
//
//   "subagent" → "Task"
//     - Copies all arguments as-is
//
//   "file_glob" → "Glob"
//     - "pattern" → "pattern"
//     - "path" → "path" (optional)
//
//   "read_files" → "Read"
//     - "paths" → "file_path" (first element)
//     - "start" → "offset"
//     - "end" → "limit"
//
//   "edit_file" → "Edit"
//     - "path" → "file_path"
//     - "old_string" → "old_string"
//     - "new_string" → "new_string"
//
//   "write_file" → "Write"
//     - "path" → "file_path"
//     - "content" → "content"
//
//   "run_command" → "Bash"
//     - "command" → "command"
//     - "timeout" → "timeout" (optional)
//
//   "list_directory" → "ListDirectory"
//     - "path" → "path"
func MapToolToClaudeCode(toolName string, args map[string]interface{},
	toolMap map[string]string) ClaudeCodeTool {

	// Get mapped name
	mappedName := toolName
	if mapped, ok := toolMap[toolName]; ok {
		mappedName = mapped
	} else if mapped, ok := warpToClaudeToolMap[toolName]; ok {
		mappedName = mapped
	}

	newArgs := make(map[string]interface{})

	// From decompiled: switch on tool name length then content
	switch toolName {
	case "grep":
		// "grep" (4 bytes, 0x70657267)
		// Map: pattern, path, include→glob
		if v, ok := args["pattern"]; ok {
			newArgs["pattern"] = v
		}
		if v, ok := args["path"]; ok {
			newArgs["path"] = v
		}
		// From decompiled: mapaccess2_faststr for "include" field
		if v, ok := args["include"]; ok {
			newArgs["glob"] = v
		}

	case "subagent":
		// "subagent" (8 bytes, 0x746e656761627573)
		// Copy all arguments, map to Task
		// From decompiled: mapIterStart/mapIterNext loop copying all k/v pairs
		for k, v := range args {
			newArgs[k] = v
		}

	case "file_glob":
		// "file_glob" (9 bytes, 0x6f6c675f656c6966 + 'b')
		if v, ok := args["pattern"]; ok {
			newArgs["pattern"] = v
		}
		if v, ok := args["path"]; ok {
			newArgs["path"] = v
		}

	case "read_files":
		// "read_files" (10 bytes)
		// Extract first path from paths array
		// From decompiled: getSliceFromInterface then index [0]
		paths := getSliceFromInterface(args["paths"])
		if len(paths) > 0 {
			if pathStr, ok := paths[0].(string); ok {
				newArgs["file_path"] = pathStr
			}
		}
		// Line range
		if v, ok := args["start"]; ok {
			newArgs["offset"] = v
		}
		if v, ok := args["end"]; ok {
			newArgs["limit"] = v
		}

	case "edit_file":
		// "edit_file" (9 bytes)
		if v, ok := args["path"]; ok {
			newArgs["file_path"] = sanitizeFileName(fmt.Sprintf("%v", v))
		}
		if v, ok := args["old_string"]; ok {
			// From decompiled: stripLineNumberPrefixes called on old_string
			newArgs["old_string"] = stripLineNumberPrefixes(fmt.Sprintf("%v", v))
		}
		if v, ok := args["new_string"]; ok {
			newArgs["new_string"] = stripLineNumberPrefixes(fmt.Sprintf("%v", v))
		}

	case "write_file":
		// "write_file" (10 bytes)
		if v, ok := args["path"]; ok {
			newArgs["file_path"] = sanitizeFileName(fmt.Sprintf("%v", v))
		}
		if v, ok := args["content"]; ok {
			// From decompiled: stripLineNumberPrefixes on content
			newArgs["content"] = stripLineNumberPrefixes(fmt.Sprintf("%v", v))
		}

	case "run_command":
		// "run_command" (11 bytes)
		if v, ok := args["command"]; ok {
			newArgs["command"] = v
		}
		if v, ok := args["timeout"]; ok {
			newArgs["timeout"] = v
		}

	case "list_directory":
		// "list_directory" (14 bytes)
		if v, ok := args["path"]; ok {
			newArgs["path"] = v
		}

	default:
		// Unknown tool — pass through all arguments
		for k, v := range args {
			newArgs[k] = v
		}
	}

	return ClaudeCodeTool{
		Name:      mappedName,
		Arguments: newArgs,
	}
}

// ============================================================================
// Helper functions
// ============================================================================

// getSliceFromInterface extracts a slice from an interface{} value.
// From decompiled: kiro2api_internal_logic_warp_getSliceFromInterface (0x1721ec0, 672B)
// Handles: []interface{}, []string, and single values (wrapped in slice).
func getSliceFromInterface(v interface{}) []interface{} {
	if v == nil {
		return nil
	}

	switch val := v.(type) {
	case []interface{}:
		return val
	case []string:
		result := make([]interface{}, len(val))
		for i, s := range val {
			result[i] = s
		}
		return result
	default:
		// Wrap single value in slice
		return []interface{}{v}
	}
}

// extractSkillNameFromPath extracts a skill/tool name from a file path.
// From decompiled: kiro2api_internal_logic_warp_extractSkillNameFromPath (0x1725940, 256B)
// Example: "/path/to/skill.json" → "skill"
func extractSkillNameFromPath(path string) string {
	base := filepath.Base(path)
	ext := filepath.Ext(base)
	if ext != "" {
		base = base[:len(base)-len(ext)]
	}
	return base
}

// sanitizeFileName sanitizes a file name/path for safe usage.
// From decompiled: kiro2api_internal_logic_warp_sanitizeFileName (0x1725780, 448B)
// Removes potentially dangerous path components.
func sanitizeFileName(name string) string {
	// Remove null bytes
	name = strings.ReplaceAll(name, "\x00", "")

	// Normalize path separators
	name = filepath.Clean(name)

	// Remove leading/trailing whitespace
	name = strings.TrimSpace(name)

	return name
}

// stripLineNumberPrefixes removes line number prefixes from text.
// From decompiled: kiro2api_internal_logic_warp_stripLineNumberPrefixes (0x1725a40, 896B)
//
// Warp's editor sometimes includes line numbers in code content like:
//   "  1\tfunction foo() {"
//   "  2\t  return bar;"
//   "  3\t}"
//
// This function strips those prefixes to get clean code content.
// Pattern: optional whitespace + digits + tab
var lineNumberPrefixRe = regexp.MustCompile(`(?m)^\s*\d+\t`)

func stripLineNumberPrefixes(text string) string {
	// Check if the text has line number prefixes
	lines := strings.Split(text, "\n")
	if len(lines) == 0 {
		return text
	}

	// Heuristic: check if most lines start with the pattern
	matchCount := 0
	for _, line := range lines {
		if line == "" {
			continue
		}
		if lineNumberPrefixRe.MatchString(line) {
			matchCount++
		}
	}

	// Only strip if majority of non-empty lines have the prefix
	nonEmpty := 0
	for _, line := range lines {
		if line != "" {
			nonEmpty++
		}
	}

	if nonEmpty > 0 && float64(matchCount)/float64(nonEmpty) > 0.5 {
		return lineNumberPrefixRe.ReplaceAllString(text, "")
	}

	return text
}
