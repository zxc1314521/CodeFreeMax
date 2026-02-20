package kiro

// list_models.go — ListAvailableModels API integration.
// Calls GET /ListAvailableModels on the CodeWhisperer Runtime API
// to dynamically discover available model IDs.

import (
	"encoding/json"
	"fmt"
	"io"
	"log"
	"net/http"
	"net/url"
	"os"
	"sync"
	"time"

	"github.com/gogf/gf/v2/frame/gins"
)

// AvailableModel represents a model returned by the ListAvailableModels API.
type AvailableModel struct {
	ModelID            string   `json:"modelId"`
	ModelName          string   `json:"modelName"`
	Description        string   `json:"description,omitempty"`
	RateMultiplier     float64  `json:"rateMultiplier,omitempty"`
	RateUnit           string   `json:"rateUnit,omitempty"`
	SupportedInputTypes []string `json:"supportedInputTypes,omitempty"`
	SupportsPromptCache bool    `json:"supportsPromptCache,omitempty"`
}

// listModelsResponse is the JSON response from /ListAvailableModels.
type listModelsResponse struct {
	Models       []AvailableModel `json:"models"`
	DefaultModel *AvailableModel  `json:"defaultModel,omitempty"`
	NextToken    string           `json:"nextToken,omitempty"`
}

// cachedModels stores the last fetched model list.
var (
	cachedModels     []AvailableModel
	cachedDefault    *AvailableModel
	cachedModelsTime time.Time
	cachedModelsMu   sync.RWMutex
	modelsCacheTTL   = 10 * time.Minute
)

// GetCachedModels returns the cached available models list.
func GetCachedModels() ([]AvailableModel, *AvailableModel) {
	cachedModelsMu.RLock()
	defer cachedModelsMu.RUnlock()
	return cachedModels, cachedDefault
}

// FetchAndCacheModels calls the ListAvailableModels API and caches the result.
// Called after successful token refresh.
func (s *sKiro) FetchAndCacheModels(accessToken string) {
	logger := gins.Log()

	models, defaultModel, err := s.callListAvailableModels(accessToken)
	if err != nil {
		log.Printf("[Kiro][ListModels] Failed: %v", err)
		logger.Warningf(nil, "[Kiro][ListModels] Failed: %v", err)
		return
	}

	cachedModelsMu.Lock()
	cachedModels = models
	cachedDefault = defaultModel
	cachedModelsTime = time.Now()
	cachedModelsMu.Unlock()

	// Log discovered models
	log.Printf("[Kiro][ListModels] Discovered %d models:", len(models))
	for _, m := range models {
		log.Printf("[Kiro][ListModels]   - %s (%s) rate=%.1f %s",
			m.ModelID, m.ModelName, m.RateMultiplier, m.RateUnit)
	}
	if defaultModel != nil {
		log.Printf("[Kiro][ListModels] Default: %s (%s)", defaultModel.ModelID, defaultModel.ModelName)
	}
	logger.Infof(nil, "[Kiro][ListModels] Cached %d models, default=%v",
		len(models), defaultModel != nil)
}

// callListAvailableModels makes the actual HTTP call to the CodeWhisperer API.
func (s *sKiro) callListAvailableModels(accessToken string) ([]AvailableModel, *AvailableModel, error) {
	var allModels []AvailableModel
	var defaultModel *AvailableModel
	nextToken := ""

	for {
		u := awsQAPIBase + "/ListAvailableModels"
		params := url.Values{}
		params.Set("origin", "AI_EDITOR")
		params.Set("profileArn", defaultProfileArn)
		if nextToken != "" {
			params.Set("nextToken", nextToken)
		}
		fullURL := u + "?" + params.Encode()

		req, err := http.NewRequest("GET", fullURL, nil)
		if err != nil {
			return nil, nil, fmt.Errorf("create request: %w", err)
		}
		req.Header.Set("Authorization", "Bearer "+accessToken)
		req.Header.Set("Content-Type", "application/json")

		resp, err := http.DefaultClient.Do(req)
		if err != nil {
			return nil, nil, fmt.Errorf("request: %w", err)
		}
		defer resp.Body.Close()

		body, _ := io.ReadAll(resp.Body)

		// Dump raw response for debugging
		log.Printf("[Kiro][ListModels] Raw response (HTTP %d): %s", resp.StatusCode, string(body))
		os.WriteFile("kiro_list_models_response.json", body, 0644)

		if resp.StatusCode != 200 {
			return nil, nil, fmt.Errorf("HTTP %d: %s", resp.StatusCode, string(body))
		}

		var result listModelsResponse
		if err := json.Unmarshal(body, &result); err != nil {
			return nil, nil, fmt.Errorf("parse response: %w (body: %.200s)", err, string(body))
		}

		allModels = append(allModels, result.Models...)
		if result.DefaultModel != nil && defaultModel == nil {
			defaultModel = result.DefaultModel
		}

		if result.NextToken == "" {
			break
		}
		nextToken = result.NextToken
	}

	return allModels, defaultModel, nil
}

// NeedModelRefresh returns true if the model cache is stale or empty.
func NeedModelRefresh() bool {
	cachedModelsMu.RLock()
	defer cachedModelsMu.RUnlock()
	return len(cachedModels) == 0 || time.Since(cachedModelsTime) > modelsCacheTTL
}

