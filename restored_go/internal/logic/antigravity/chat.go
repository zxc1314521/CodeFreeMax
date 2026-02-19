package antigravity

// chat.go — Main ChatCompletions entry point for the Antigravity (Gemini) channel.
//
// This file provides the top-level ChatCompletions handler that:
//  1. Validates the account and refreshes tokens if needed
//  2. Maps the model name to a Gemini model ID
//  3. Builds the Gemini generateContent request
//  4. Sends the streaming request
//  5. Translates the Gemini SSE response back to OpenAI format
//
// This is the glue that connects the controller layer to the antigravity channel internals.

import (
	"context"
	"fmt"
	"net/http"

	"github.com/imroc/req/v3"
)

// ============================================================================
// ChatCompletions
// ============================================================================

// ChatCompletions handles an OpenAI-compatible chat completion request via the Gemini API.
// This is the main entry point called by the controller layer.
//
// Flow:
//  1. Get account from queue (managed by AccountConcurrencyManager)
//  2. RefreshToken if needed
//  3. Map model name → Gemini model ID
//  4. Determine if model supports thinking
//  5. buildAntigravityRequest
//  6. doStreamRequest
//  7. Stream SSE response back to client in OpenAI format
func (s *sAntigravity) ChatCompletions(
	ctx context.Context,
	w http.ResponseWriter,
	chatReq map[string]interface{},
	account map[string]interface{},
	client *req.Client,
) error {

	// Step 1: Refresh token if needed
	if err := s.RefreshToken(client, account); err != nil {
		return fmt.Errorf("refresh token: %w", err)
	}

	// Step 2: Get model name and map to Gemini model
	modelName, _ := chatReq["model"].(string)
	if modelName == "" {
		modelName = defaultGeminiModel
	}
	geminiModel := mapGeminiModel(modelName)

	// Step 3: Check if model supports thinking
	supportsThinking := modelSupportsThinking(modelName)

	// Step 4: Build the Gemini request
	request := s.buildAntigravityRequest(geminiModel, chatReq, account, supportsThinking)

	// Step 5: Send streaming request
	// The stream writer and cancel function are passed through to doStreamRequest
	// which handles the SSE streaming and response translation
	err := s.doStreamRequest(client, chatReq, account, request, w, nil)
	if err != nil {
		return fmt.Errorf("stream request: %w", err)
	}

	return nil
}
