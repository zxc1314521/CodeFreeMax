package grok

// media.go — Image and video generation for the Grok channel.
//
// Functions:
//   - ImagineGenerations   (@ 0x160cd00) — Image generation via WebSocket
//   - VideoGenerations     (@ 0x161bc00) — Video generation (upload + post)
//   - classifyImage        — Classify image result from WebSocket message
//   - uploadImage          — Upload image for video generation
//   - createMediaPost      — Create media post (text-to-video)
//   - createImagePost      — Create image post (image-to-video)
//
// ImagineGenerations (@ 0x160cd00, ~440 lines C pseudocode):
//   Uses WebSocket connection to receive real-time image generation updates.
//   Key patterns from decompiled:
//   1. Extract request params (prompt, count, account key)
//   2. Set up deferred cleanup (deferprocStack x2)
//   3. Generate random seed (runtime_rand + 0x8080808080808080 mask)
//   4. Record start time (time_Now)
//   5. Main WebSocket read loop:
//      a. Check overall timeout (120s = 119999999999 ns)
//      b. Check context cancellation (selectnbrecv)
//      c. Set per-read deadline (time_Time_Add 5s)
//      d. Set WebSocket read deadline
//      e. Read WebSocket message (gorilla/websocket.Conn.ReadMessage)
//      f. On timeout error → check stall detection (15s with no progress)
//      g. On success → JSON unmarshal into map
//      h. Check "type" field:
//         - "error" → extract message/code, log warning, send error response
//         - "image" → classifyImage, track progress, send result
//      i. Track completion count vs requested count
//      j. Stall detection: if mediaProgress exists, no completions, >15s → abort
//   6. On WebSocket close (code 1000) → normal exit
//   7. On completion count reached → log info, exit
//
// VideoGenerations (@ 0x161bc00, ~250 lines C pseudocode):
//   Handles video generation with optional image upload.
//   Key patterns from decompiled:
//   1. Extract request params from input struct at offsets:
//      +0x08: account key (uStack_2b0)
//      +0x10: prompt (plVar7 / plStack_2b8)
//      +0x18: context/channel (lStack_420)
//      +0x20: image URL (uStack_2c0)
//      +0x28: image data (lVar8 = length check)
//      +0x30: callback URL (puStack_78)
//      +0x38: callback URL length (lStack_108)
//      +0x48: additional params (uStack_b0)
//      +0x50: extra config (puVar9)
//   2. Log debug with prompt and hasImage flag
//   3. If no image data (lVar8 == 0):
//      → Call createMediaPost (text-to-video)
//   4. If image data present:
//      a. Check if URL starts with "data:image/" (23 bytes memequal)
//         → If not base64 data URL, call uploadImage first
//      b. Call createImagePost with uploaded image reference
//   5. On error → log error, return formatted error
//   6. On success → log debug with post ID
//   7. Get CF clearance and browser fingerprint
//   8. Build headers via BuildHeaders
//   9. Set "Referer" header (7 bytes key → mapassign_faststr)
//   10. Handle callback URL (default "grok" if empty)
//   11. Build video payload via buildVideoPayload
//   12. Log debug with payload details
//   13. Create per-account client via clientForAccount
//   14. Send streaming POST via GrokClient.PostStream
//   15. On error → log error, return formatted error

import (
	"context"
	"encoding/json"
	"fmt"
	"strings"
	"time"

	"github.com/gogf/gf/v2/frame/gins"
	"github.com/gorilla/websocket"
)

// ============================================================================
// ImagineGenerations
// ============================================================================

// ImagineGenerations handles image generation requests via WebSocket.
//
// Symbol: kiro2api/internal/logic/grok.ImagineGenerations (@ 0x160cd00)
//
// The function connects to the Grok WebSocket endpoint and receives
// real-time image generation updates. It tracks progress, handles
// timeouts, and detects stalls.
//
// From decompiled (440 lines):
//   - Overall timeout: 120 seconds (119999999999 ns)
//   - Per-read timeout: 5 seconds (5000000000 ns)
//   - Stall detection: 15 seconds with no completions
//   - Tracks completion count vs requested count
//   - Handles "error" and "image" type messages
//   - Uses classifyImage to process image results
//   - MediaProgress linked list for stall detection
func (s *sGrok) ImagineGenerations(
	ctx context.Context,
	req *ImagineRequest,
	resultCh chan<- interface{},
) {
	logger := gins.Log()

	// Deferred cleanup (deferprocStack x2 in decompiled)
	defer close(resultCh)
	defer func() {
		if r := recover(); r != nil {
			logger.Warningf(nil, "[Grok] ImagineGenerations panic: %v", r)
		}
	}()

	// Generate random seed
	// From decompiled: runtime_rand() with 0x8080808080808080 mask
	startTime := time.Now()

	// Record overall start time
	// From decompiled: time_Now() called twice — once for seed, once for timing
	overallStart := time.Now()

	var (
		completionCount int
		mediaProgress   *MediaProgress
		completionMap   = make(map[string]*bool) // URL → isComplete tracking
	)

	// Main WebSocket read loop
	// From decompiled: do-while loop with timeout checks
	for {
		// Check overall timeout (120 seconds)
		// From decompiled: if 119999999999 < time_Since(overallStart)
		if time.Since(overallStart) > time.Duration(wsOverallTimeout) {
			logger.Warningf(nil, "[Grok] Image generation timeout after %v, account: %s",
				time.Since(overallStart), req.AccountKey)

			// Send timeout error via channel
			// From decompiled: FUN_0048903e builds error response
			sendError(resultCh, "error", "timeout", "Image generation timed out")

			// Check context cancellation
			select {
			case <-ctx.Done():
				return
			default:
			}
			return
		}

		// Check context cancellation (non-blocking)
		// From decompiled: selectnbrecv on context done channel
		select {
		case <-ctx.Done():
			return
		default:
		}

		// Set per-read deadline (5 seconds)
		// From decompiled: time_Time_Add(5000000000)
		readDeadline := time.Now().Add(time.Duration(wsReadTimeoutNs))

		// Connect to WebSocket and set read deadline
		// From decompiled: gorilla/websocket.Conn operations
		conn, _, err := websocket.DefaultDialer.DialContext(ctx, grokWSEndpoint, nil)
		if err != nil {
			logger.Warningf(nil, "[Grok] WebSocket connect error: %v", err)
			sendError(resultCh, "error", "connection", err.Error())
			return
		}
		defer conn.Close()

		conn.SetReadDeadline(readDeadline)

		// Read WebSocket message
		// From decompiled: gorilla_websocket_Conn_ReadMessage()
		_, msgBytes, err := conn.ReadMessage()
		if err != nil {
			// Check if timeout error
			// From decompiled: isTimeoutError check
			if isTimeoutError(err) {
				// Stall detection: if mediaProgress exists, no completions, >15s
				// From decompiled: puStack_370 != nil && lStack_418 == 0 && time_Since > 15s
				if mediaProgress != nil && completionCount == 0 {
					if time.Since(startTime) > time.Duration(mediaStallTimeout) {
						// Stall detected — abort
						sendError(resultCh, "error", "timeout", "Image generation stalled - no progress")
						select {
						case <-ctx.Done():
							return
						default:
						}
						return
					}
				}

				// Also check: completionCount > 0 && time_Since > 10s
				// From decompiled: lStack_418 >= 1 && time_Since > 10000000000
				if completionCount > 0 && time.Since(startTime) > time.Duration(timeoutRetryThreshold) {
					// Partial completion with stall — finish with what we have
					logger.Infof(nil, "[Grok] Image generation partial complete: %d/%d, account: %s",
						completionCount, req.Count, req.AccountKey)
					return
				}

				continue // Retry read
			}

			// Check for normal WebSocket close (code 1000)
			// From decompiled: ppuVar12 == &PTR_DAT_01f43240 → close frame check
			if websocket.IsCloseError(err, websocket.CloseNormalClosure) {
				return
			}

			// Non-timeout error
			// From decompiled: log warning with error details
			logger.Warningf(nil, "[Grok] WebSocket read error: %v, account: %s", err, req.AccountKey)
			sendError(resultCh, "error", "websocket", err.Error())
			select {
			case <-ctx.Done():
				return
			default:
			}
			return
		}

		// Parse WebSocket message
		// From decompiled: encoding_json_Unmarshal into runtime_newobject
		var wsMsg map[string]interface{}
		if err := json.Unmarshal(msgBytes, &wsMsg); err != nil {
			continue // Skip malformed messages
		}

		// Check "type" field
		// From decompiled: mapaccess1_faststr(4) for "type" key (4 bytes)
		typeStr, _ := getStringField(wsMsg, "type")

		switch typeStr {
		case "error":
			// Error response
			// From decompiled: extract "message" (8 bytes) and "code" fields
			errMsg, _ := getStringField(wsMsg, "message")
			errCode, _ := getStringField(wsMsg, "code")
			logger.Warningf(nil, "[Grok] Image generation error: %s - %s, account: %s",
				errCode, errMsg, req.AccountKey)

			sendError(resultCh, "error", errCode, errMsg)
			select {
			case <-ctx.Done():
				return
			default:
			}
			return

		case "image":
			// Image result
			// From decompiled: classifyImage call, then progress tracking
			classified := classifyImage(wsMsg)
			if classified == nil {
				continue
			}

			// Track media progress for stall detection
			// From decompiled: first "medium" type → create MediaProgress
			if classified.MediaType == "medium" && mediaProgress == nil {
				mediaProgress = &MediaProgress{
					StartTime: time.Now(),
				}
				startTime = time.Now() // Reset stall timer
			}

			// Track completion
			// From decompiled: isComplete flag check and counter increment
			if classified.IsComplete {
				existing, tracked := completionMap[classified.URL]
				if !tracked || (existing != nil && !*existing) {
					completionCount++
					t := true
					completionMap[classified.URL] = &t
				}
			} else if _, tracked := completionMap[classified.URL]; !tracked {
				f := false
				completionMap[classified.URL] = &f
			}

			// Send result via channel
			// From decompiled: FUN_0048903e builds response, then selectgo
			select {
			case resultCh <- classified:
			case <-ctx.Done():
				return
			}

			// Check if all images complete
			// From decompiled: if lVar1 <= lStack_418 (count <= completionCount)
			if completionCount >= req.Count {
				logger.Infof(nil, "[Grok] Image generation complete: %d images, account: %s",
					completionCount, req.AccountKey)
				return
			}

			// Reset stall timer on progress
			if classified.IsComplete {
				startTime = time.Now()
			}
		}
	}
}

// ============================================================================
// VideoGenerations
// ============================================================================

// VideoGenerations handles video generation requests.
//
// Symbol: kiro2api/internal/logic/grok.VideoGenerations (@ 0x161bc00)
//
// From decompiled (250 lines):
//   1. Log debug with prompt and hasImage flag
//   2. If no image → createMediaPost (text-to-video)
//   3. If image present:
//      a. Check if base64 data URL (23 bytes "data:image/" prefix)
//      b. If not → uploadImage first
//      c. createImagePost with image reference
//   4. Build headers with CF clearance and fingerprint
//   5. Set Referer header
//   6. Build video payload
//   7. Send streaming POST
//   8. Return error on failure
func (s *sGrok) VideoGenerations(
	ctx context.Context,
	req *VideoRequest,
	account map[string]interface{},
) error {
	logger := gins.Log()

	accountKey, _ := account["key"].(string)

	// Log debug
	// From decompiled: Logger_Debugf with prompt and hasImage flag
	hasImage := req.ImageURL != "" || req.ImageData != ""
	logger.Debugf(nil, "[Grok] Video generation: prompt=%s, hasImage=%v, account=%s",
		req.Prompt, hasImage, accountKey)

	var mediaPostID string

	if !hasImage {
		// Text-to-video: create media post directly
		// From decompiled: createMediaPost call when lVar8 == 0
		postID, err := s.createMediaPost(ctx, account, req.Prompt, accountKey)
		if err != nil {
			logger.Errorf(nil, "[Grok] Create media post failed: %v, account=%s", err, accountKey)
			return fmt.Errorf("[Grok] create media post: %w", err)
		}
		mediaPostID = postID
		logger.Debugf(nil, "[Grok] Media post created: %s", mediaPostID)
	} else {
		// Image-to-video: may need to upload image first
		imageRef := req.ImageURL
		if imageRef == "" {
			imageRef = req.ImageData
		}

		// Check if base64 data URL
		// From decompiled: runtime_memequal for 23-byte "data:image/" prefix check
		if !strings.HasPrefix(imageRef, "data:image/") {
			// Not a data URL — need to upload image
			logger.Debugf(nil, "[Grok] Uploading image for video generation, account=%s", accountKey)

			uploadedRef, err := s.uploadImage(ctx, account, imageRef, accountKey)
			if err != nil {
				logger.Errorf(nil, "[Grok] Upload image failed: %v, account=%s", err, accountKey)
				return fmt.Errorf("[Grok] upload image: %w", err)
			}
			imageRef = uploadedRef
		}

		// Create image post
		// From decompiled: createImagePost with uploaded image reference
		postID, err := s.createImagePost(ctx, account, imageRef, accountKey, req.Prompt)
		if err != nil {
			logger.Errorf(nil, "[Grok] Create image post failed: %v, account=%s", err, accountKey)
			return fmt.Errorf("[Grok] create image post: %w", err)
		}
		mediaPostID = postID
		logger.Debugf(nil, "[Grok] Image post created: %s, account=%s", mediaPostID, accountKey)
	}

	// Build headers
	// From decompiled: GetCfClearance, GetBrowserFingerprint, BuildHeaders
	cfClearance := s.GetCfClearance()
	fingerprint := s.GetBrowserFingerprint()
	userAgent, _ := account["user_agent"].(string)
	cookie, _ := account["cookie"].(string)
	headers := BuildHeaders(account, fingerprint, userAgent, cfClearance, cookie)

	// Set Referer header
	// From decompiled: mapassign_faststr(7) → "Referer" (7 bytes)
	// Value is the full URL (0x18 = 24 bytes length)
	headers["Referer"] = grokAPIBase + "/chat"

	// Handle callback URL
	// From decompiled: if lStack_108 == 0 → default "grok" (4 bytes)
	callbackPath := grokVideoEndpoint

	// Build video payload
	// From decompiled: buildVideoPayload call
	payload := buildVideoPayload(req.Prompt, mediaPostID, "")

	// Log debug with payload details
	// From decompiled: Logger_Debugf with 3 convTstring args (prompt, count, payload)
	logger.Debugf(nil, "[Grok] Video POST: endpoint=%s, postID=%s, prompt=%s",
		callbackPath, mediaPostID, req.Prompt)

	// Create per-account client and send streaming POST
	// From decompiled: clientForAccount then GrokClient_PostStream
	client := s.clientForAccount(account)
	_, _, err := client.PostStream(ctx, callbackPath, payload, headers)
	if err != nil {
		logger.Errorf(nil, "[Grok] Video POST failed: %v, account=%s", err, accountKey)
		return fmt.Errorf("[Grok] video generation: %w", err)
	}

	return nil
}

// ============================================================================
// classifyImage
// ============================================================================

// classifyImage extracts and classifies an image result from a WebSocket message.
//
// From decompiled: kiro2api_internal_logic_grok_classifyImage
// Called in ImagineGenerations when type == "image".
//
// Returns nil if the message doesn't contain valid image data.
// The returned struct has fields at specific offsets:
//   +0x10: URL, +0x18: URL length
//   +0x20: mediaType, +0x28: mediaType length
//   +0x48: isComplete flag
func classifyImage(msg map[string]interface{}) *ImageClassification {
	// Extract "url" field
	// From decompiled: mapaccess1_faststr for "url" (3 bytes)
	url, ok := getStringField(msg, "url")
	if !ok || url == "" {
		return nil
	}

	// Extract "mediaType" field
	// From decompiled: mapaccess1_faststr for "mediaType" (9 bytes → but accessed as "type" 4 bytes)
	mediaType, _ := getStringField(msg, "mediaType")

	// Extract "isComplete" field
	// From decompiled: byte at offset +0x48
	isComplete := false
	if v, ok := msg["isComplete"]; ok {
		if b, ok := v.(bool); ok {
			isComplete = b
		}
	}

	return &ImageClassification{
		URL:        url,
		MediaType:  mediaType,
		IsComplete: isComplete,
	}
}

// ============================================================================
// Media Post Creation
// ============================================================================

// createMediaPost creates a media post for text-to-video generation.
// From decompiled: kiro2api_internal_logic_grok_sGrok_createMediaPost
// Called in VideoGenerations when no image is provided.
func (s *sGrok) createMediaPost(
	ctx context.Context,
	account map[string]interface{},
	prompt string,
	accountKey string,
) (string, error) {
	client := s.clientForAccount(account)

	payload := map[string]interface{}{
		"prompt": prompt,
		"type":   "video",
	}

	headers := GrokHeaders{
		"Content-Type": "application/json",
	}

	body, _, err := client.PostStream(ctx, grokVideoEndpoint, payload, headers)
	if err != nil {
		return "", fmt.Errorf("create media post: %w", err)
	}
	defer body.Close()

	var resp map[string]interface{}
	if err := json.NewDecoder(body).Decode(&resp); err != nil {
		return "", fmt.Errorf("decode media post response: %w", err)
	}

	postID, _ := resp["postId"].(string)
	if postID == "" {
		return "", fmt.Errorf("no postId in response")
	}

	return postID, nil
}

// createImagePost creates an image post for image-to-video generation.
// From decompiled: kiro2api_internal_logic_grok_sGrok_createImagePost
// Called in VideoGenerations when image is provided.
func (s *sGrok) createImagePost(
	ctx context.Context,
	account map[string]interface{},
	imageRef string,
	accountKey string,
	prompt string,
) (string, error) {
	client := s.clientForAccount(account)

	payload := map[string]interface{}{
		"prompt":   prompt,
		"imageRef": imageRef,
		"type":     "video",
	}

	headers := GrokHeaders{
		"Content-Type": "application/json",
	}

	body, _, err := client.PostStream(ctx, grokVideoEndpoint, payload, headers)
	if err != nil {
		return "", fmt.Errorf("create image post: %w", err)
	}
	defer body.Close()

	var resp map[string]interface{}
	if err := json.NewDecoder(body).Decode(&resp); err != nil {
		return "", fmt.Errorf("decode image post response: %w", err)
	}

	postID, _ := resp["postId"].(string)
	if postID == "" {
		return "", fmt.Errorf("no postId in response")
	}

	return postID, nil
}

// uploadImage uploads an image for video generation.
// From decompiled: kiro2api_internal_logic_grok_sGrok_uploadImage
// Called in VideoGenerations when image URL is not a data URL.
func (s *sGrok) uploadImage(
	ctx context.Context,
	account map[string]interface{},
	imageURL string,
	accountKey string,
) (string, error) {
	client := s.clientForAccount(account)

	payload := map[string]interface{}{
		"url": imageURL,
	}

	headers := GrokHeaders{
		"Content-Type": "application/json",
	}

	body, _, err := client.PostStream(ctx, grokImageEndpoint, payload, headers)
	if err != nil {
		return "", fmt.Errorf("upload image: %w", err)
	}
	defer body.Close()

	var resp map[string]interface{}
	if err := json.NewDecoder(body).Decode(&resp); err != nil {
		return "", fmt.Errorf("decode upload response: %w", err)
	}

	ref, _ := resp["imageRef"].(string)
	if ref == "" {
		return "", fmt.Errorf("no imageRef in upload response")
	}

	return ref, nil
}

// ============================================================================
// Helpers
// ============================================================================

// sendError sends an error result through the channel.
func sendError(ch chan<- interface{}, errType, code, message string) {
	ch <- map[string]interface{}{
		"type":    errType,
		"code":    code,
		"message": message,
	}
}

// getStringField extracts a string field from a map.
func getStringField(m map[string]interface{}, key string) (string, bool) {
	v, ok := m[key]
	if !ok {
		return "", false
	}
	s, ok := v.(string)
	return s, ok
}
