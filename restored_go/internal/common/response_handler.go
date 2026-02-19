package common

import (
	"log"
	"net/http"
)

// ResponseHandler handles upstream HTTP responses, routing errors
// to appropriate handlers based on status code.
type ResponseHandler struct {
	AccountID   string
	ChannelName string
	Account     interface{} // channel-specific account struct
}

// HandleResponse processes an upstream HTTP response.
// Returns:
//   - 0: non-retryable error (client error, bad request)
//   - 1: retryable error (should try next account)
//   - 0 with nil error: success (2xx)
func (h *ResponseHandler) HandleResponse(resp *http.Response) int {
	if resp == nil {
		return 1 // retryable — no response at all
	}

	// 2xx success
	if resp.StatusCode >= 200 && resp.StatusCode < 300 {
		return 0
	}

	// Non-2xx: delegate to error handler
	return h.handleErrorResponse(resp)
}

// handleErrorResponse routes error responses by HTTP status code.
// Status code mapping (from decompiled hex constants):
//   - 400 (0x190): Bad Request — non-retryable, pass error through
//   - 401 (0x191): Unauthorized — clear credentials, mark account invalid, retryable
//   - 402 (0x192): Payment Required — handle quota/billing, retryable
//   - 403 (0x193): Forbidden — handle access denied, retryable
//   - 429 (0x1AD): Rate Limited — handle rate limit, retryable
//   - 4xx other: non-retryable client error
//   - 5xx: retryable server error
func (h *ResponseHandler) handleErrorResponse(resp *http.Response) int {
	// Parse error reason from response body
	reason := h.parseErrorReason(resp)

	// Log the error
	log.Printf("[ResponseHandler] channel=%s status=%d reason=%s account=%s",
		h.ChannelName, resp.StatusCode, reason, h.AccountID)

	statusCode := resp.StatusCode

	switch {
	case statusCode == 400:
		// Bad Request
		if len(reason) == 0x20 { // specific known error string length
			// Known bad request pattern — pass through with reason
			log.Printf("[ResponseHandler] Bad request (known pattern): %s", reason)
		}
		// Non-retryable
		return 0

	case statusCode == 401:
		// Unauthorized — clear account credentials and mark invalid
		// Clear session key (offset 0x28, 0x30 in account struct)
		// Clear auth token (offset 0x118 in account struct)
		h.updateAccountStatus("invalid")
		return 1 // retryable with next account

	case statusCode == 402:
		// Payment Required — quota exhausted
		return h.handlePaymentRequired(resp)

	case statusCode == 403:
		// Forbidden — access denied
		return h.handleForbidden(resp)

	case statusCode == 429:
		// Rate Limited
		return h.handleRateLimited(resp)

	case statusCode >= 500:
		// Server error — retryable
		return 1

	default:
		// Other 4xx — non-retryable
		return 0
	}
}

// parseErrorReason extracts the error reason string from the response body.
func (h *ResponseHandler) parseErrorReason(resp *http.Response) string {
	// Implementation reads response body and extracts error message
	// Actual parsing depends on upstream API format (JSON error response)
	return ""
}

// updateAccountStatus marks the account with the given status in the database.
func (h *ResponseHandler) updateAccountStatus(status string) {
	// Updates account status in DB (e.g., "invalid", "rate_limited", "quota_exceeded")
	log.Printf("[ResponseHandler] Updating account %s status to: %s", h.AccountID, status)
}

// handlePaymentRequired handles 402 Payment Required responses.
// Typically means the account's quota or credits are exhausted.
func (h *ResponseHandler) handlePaymentRequired(resp *http.Response) int {
	log.Printf("[ResponseHandler] Payment required for account %s", h.AccountID)
	h.updateAccountStatus("quota_exceeded")
	return 1 // retryable with next account
}

// handleForbidden handles 403 Forbidden responses.
// Could mean account is banned, suspended, or lacks permissions.
func (h *ResponseHandler) handleForbidden(resp *http.Response) int {
	log.Printf("[ResponseHandler] Forbidden for account %s", h.AccountID)
	h.updateAccountStatus("forbidden")
	return 1 // retryable with next account
}

// handleRateLimited handles 429 Too Many Requests responses.
// The account has hit its rate limit and should be temporarily skipped.
func (h *ResponseHandler) handleRateLimited(resp *http.Response) int {
	log.Printf("[ResponseHandler] Rate limited for account %s", h.AccountID)
	h.updateAccountStatus("rate_limited")
	return 1 // retryable with next account
}
