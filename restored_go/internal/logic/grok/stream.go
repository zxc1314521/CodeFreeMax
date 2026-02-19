package grok

// stream.go — Streaming response parsing for the Grok channel.
//
// Functions:
//   - ProcessLine                       (@ 0x1612e80) — Line-by-line stream response parsing
//   - CollectProcessorProcessWithUsage  (@ 0x1616000) — Response collection with usage tracking
//
// The Grok API returns streaming responses as newline-delimited JSON.
// Each line contains a JSON object with a "result" field that holds
// the response data, including text tokens, thinking indicators,
// image results, and error information.
//
// ProcessLine (@ 0x1612e80, ~700 lines C pseudocode):
//   The decompiled code shows a complex line parser that:
//   1. Receives a raw line from the HTTP response stream
//   2. Parses JSON into map[string]interface{}
//   3. Checks for "result" key via mapaccess1_faststr
//   4. Within result, checks for multiple sub-keys:
//      - "response" (text token)
//      - "modelResponse" (full model response with usage)
//      - "token" (streaming token)
//      - "isThinking" (thinking mode indicator)
//   5. Writes parsed content to the SSEWriter
//   6. Handles error responses via "error" key
//
// CollectProcessorProcessWithUsage (@ 0x1616000, ~200 lines C pseudocode):
//   Wraps ProcessLine to collect the full response and track usage:
//   1. Accumulates all text tokens into a buffer
//   2. Extracts input/output token counts from modelResponse
//   3. Returns CollectResult with content, usage, and stop reason

import (
	"bufio"
	"context"
	"encoding/json"
	"fmt"
	"io"
	"strings"
	"time"

	"github.com/gogf/gf/v2/frame/gins"

	"kiro2api/internal/logic/common"
)

// ============================================================================
// Stream Constants
// ============================================================================

const (
	// Response result keys (from mapaccess1_faststr patterns in ProcessLine)
	keyResult        = "result"
	keyError         = "error"
	keyResponse      = "response"
	keyModelResponse = "modelResponse"
	keyToken         = "token"
	keyIsThinking    = "isThinking"
	keyMessage       = "message"
	keyCode          = "code"

	// Usage keys within modelResponse
	keyInputTokens  = "inputTokens"
	keyOutputTokens = "outputTokens"

	// Model response sub-keys
	keyFinalResponse = "finalResponse"
	keyUsage         = "usage"
)

// ============================================================================
// ProcessLine
// ============================================================================

// ProcessLine parses a single line from the Grok streaming response and
// writes the extracted content to the SSEWriter.
//
// Symbol: kiro2api/internal/logic/grok.ProcessLine (@ 0x1612e80)
//
// From decompiled (700 lines):
//   1. Parse line as JSON into map[string]interface{}
//   2. Check for "error" key → if present, extract message and return error
//   3. Check for "result" key → extract response data
//   4. Within result:
//      a. Check "isThinking" (bool) → toggle thinking mode
//      b. Check "token" (string) → write text delta
//      c. Check "response" (string) → write text content
//      d. Check "modelResponse" (map) → extract final response and usage
//   5. Return nil on success, error on failure
//
// The function handles multiple response formats:
//   - Streaming tokens: {"result": {"token": "Hello"}}
//   - Thinking mode: {"result": {"isThinking": true, "token": "..."}}
//   - Final response: {"result": {"modelResponse": {...}}}
//   - Errors: {"error": {"message": "...", "code": "..."}}
func ProcessLine(
	line string,
	writer *common.SSEWriter,
	isThinking *bool,
	usage *GrokUsage,
) error {
	line = strings.TrimSpace(line)
	if line == "" {
		return nil
	}

	// Parse JSON
	var data map[string]interface{}
	if err := json.Unmarshal([]byte(line), &data); err != nil {
		// Skip non-JSON lines silently
		return nil
	}

	// Check for error response
	// From decompiled: mapaccess1_faststr for "error" key
	if errObj, ok := data[keyError]; ok && errObj != nil {
		if errMap, ok := errObj.(map[string]interface{}); ok {
			msg, _ := errMap[keyMessage].(string)
			code, _ := errMap[keyCode].(string)
			if msg != "" {
				return fmt.Errorf("grok error [%s]: %s", code, msg)
			}
		}
	}

	// Check for result
	// From decompiled: mapaccess1_faststr for "result" key
	resultObj, ok := data[keyResult]
	if !ok || resultObj == nil {
		return nil
	}

	resultMap, ok := resultObj.(map[string]interface{})
	if !ok {
		return nil
	}

	// Check thinking mode toggle
	// From decompiled: "isThinking" boolean check
	if thinkingVal, ok := resultMap[keyIsThinking]; ok {
		if thinking, ok := thinkingVal.(bool); ok {
			if thinking && !*isThinking {
				// Entering thinking mode
				*isThinking = true
				writer.WriteThinkingStart()
			} else if !thinking && *isThinking {
				// Exiting thinking mode
				*isThinking = false
				writer.WriteThinkingEnd()
			}
		}
	}

	// Check for streaming token
	// From decompiled: mapaccess1_faststr for "token" key
	if token, ok := resultMap[keyToken].(string); ok && token != "" {
		if *isThinking {
			writer.WriteThinking(token)
		} else {
			writer.WriteContent(token)
		}
		return nil
	}

	// Check for text response (non-streaming)
	// From decompiled: mapaccess1_faststr for "response" key
	if response, ok := resultMap[keyResponse].(string); ok && response != "" {
		writer.WriteContent(response)
		return nil
	}

	// Check for model response (final response with usage)
	// From decompiled: mapaccess1_faststr for "modelResponse" key
	if modelResp, ok := resultMap[keyModelResponse]; ok && modelResp != nil {
		if modelMap, ok := modelResp.(map[string]interface{}); ok {
			// Extract final response text
			if finalResp, ok := modelMap[keyFinalResponse].(string); ok && finalResp != "" {
				writer.WriteContent(finalResp)
			}

			// Extract usage information
			if usageObj, ok := modelMap[keyUsage]; ok {
				if usageMap, ok := usageObj.(map[string]interface{}); ok {
					if inputTokens, ok := usageMap[keyInputTokens].(float64); ok {
						usage.InputTokens = int(inputTokens)
					}
					if outputTokens, ok := usageMap[keyOutputTokens].(float64); ok {
						usage.OutputTokens = int(outputTokens)
					}
				}
			}

			// Write usage to SSE
			if usage.InputTokens > 0 || usage.OutputTokens > 0 {
				writer.WriteUsage(usage.InputTokens, usage.OutputTokens)
			}

			// Write stop reason
			writer.WriteStopReason("stop")
			writer.WriteDone()
		}
	}

	return nil
}

// ============================================================================
// ParseStreamResponse
// ============================================================================

// ParseStreamResponse reads the streaming response body line by line
// and processes each line through ProcessLine.
//
// This is the main entry point for stream parsing, analogous to
// kiro's ParseStreamResponse but adapted for Grok's newline-delimited JSON format.
func (s *sGrok) ParseStreamResponse(
	ctx context.Context,
	body io.ReadCloser,
	writer *common.SSEWriter,
	account map[string]interface{},
) error {
	logger := gins.Log()

	defer func() {
		if body != nil {
			body.Close()
		}
	}()

	scanner := bufio.NewScanner(body)
	scanner.Buffer(make([]byte, 0, 64*1024), 1024*1024)

	var (
		isThinking bool
		usage      GrokUsage
	)

	for scanner.Scan() {
		// Check context cancellation
		select {
		case <-ctx.Done():
			logger.Info(nil, "[Grok] Stream cancelled by context")
			return ctx.Err()
		default:
		}

		line := scanner.Text()
		if err := ProcessLine(line, writer, &isThinking, &usage); err != nil {
			logger.Warningf(nil, "[Grok] ProcessLine error: %v", err)
			return err
		}
	}

	if err := scanner.Err(); err != nil {
		return fmt.Errorf("stream scanner error: %w", err)
	}

	return nil
}

// ============================================================================
// CollectProcessorProcessWithUsage
// ============================================================================

// CollectProcessorProcessWithUsage reads the full streaming response,
// collects all text content, and returns the result with usage metrics.
//
// Symbol: kiro2api/internal/logic/grok.CollectProcessorProcessWithUsage (@ 0x1616000)
//
// From decompiled (200 lines):
//   1. Create a content buffer (strings.Builder)
//   2. Read lines from response body
//   3. For each line, parse JSON and extract text tokens
//   4. Accumulate tokens into buffer
//   5. Extract usage from final modelResponse
//   6. Return CollectResult with content, usage, stop reason
//
// This is used for non-streaming (collect) mode where the full response
// is needed before returning to the caller.
func CollectProcessorProcessWithUsage(
	ctx context.Context,
	body io.ReadCloser,
) (*CollectResult, error) {
	logger := gins.Log()

	defer func() {
		if body != nil {
			body.Close()
		}
	}()

	scanner := bufio.NewScanner(body)
	scanner.Buffer(make([]byte, 0, 64*1024), 1024*1024)

	var (
		contentBuf strings.Builder
		usage      GrokUsage
		stopReason string
		startTime  = time.Now()
	)

	for scanner.Scan() {
		// Check context cancellation
		select {
		case <-ctx.Done():
			return nil, ctx.Err()
		default:
		}

		line := strings.TrimSpace(scanner.Text())
		if line == "" {
			continue
		}

		// Parse JSON
		var data map[string]interface{}
		if err := json.Unmarshal([]byte(line), &data); err != nil {
			continue
		}

		// Check for error
		if errObj, ok := data[keyError]; ok && errObj != nil {
			if errMap, ok := errObj.(map[string]interface{}); ok {
				msg, _ := errMap[keyMessage].(string)
				code, _ := errMap[keyCode].(string)
				if msg != "" {
					return nil, fmt.Errorf("grok error [%s]: %s", code, msg)
				}
			}
		}

		// Extract result
		resultObj, ok := data[keyResult]
		if !ok || resultObj == nil {
			continue
		}

		resultMap, ok := resultObj.(map[string]interface{})
		if !ok {
			continue
		}

		// Collect streaming tokens
		if token, ok := resultMap[keyToken].(string); ok && token != "" {
			contentBuf.WriteString(token)
		}

		// Collect text response
		if response, ok := resultMap[keyResponse].(string); ok && response != "" {
			contentBuf.WriteString(response)
		}

		// Extract model response (final)
		if modelResp, ok := resultMap[keyModelResponse]; ok && modelResp != nil {
			if modelMap, ok := modelResp.(map[string]interface{}); ok {
				// Final response text
				if finalResp, ok := modelMap[keyFinalResponse].(string); ok && finalResp != "" {
					contentBuf.WriteString(finalResp)
				}

				// Usage
				if usageObj, ok := modelMap[keyUsage]; ok {
					if usageMap, ok := usageObj.(map[string]interface{}); ok {
						if v, ok := usageMap[keyInputTokens].(float64); ok {
							usage.InputTokens = int(v)
						}
						if v, ok := usageMap[keyOutputTokens].(float64); ok {
							usage.OutputTokens = int(v)
						}
					}
				}

				stopReason = "stop"
			}
		}
	}

	if err := scanner.Err(); err != nil {
		return nil, fmt.Errorf("collect scanner error: %w", err)
	}

	elapsed := time.Since(startTime)
	logger.Infof(nil, "[Grok] Collected response: %d chars, %d input tokens, %d output tokens, elapsed %v",
		contentBuf.Len(), usage.InputTokens, usage.OutputTokens, elapsed)

	return &CollectResult{
		Content:    contentBuf.String(),
		Usage:      &usage,
		StopReason: stopReason,
	}, nil
}
