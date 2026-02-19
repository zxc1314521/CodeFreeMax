package common

import "time"

// ErrorResponse represents an error response used across channels.
type ErrorResponse struct {
	Code    string                 `json:"code"`
	Message string                 `json:"message"`
	Data    map[string]interface{} `json:"data,omitempty"`
}

// OpenAIErrorResponse represents an OpenAI-compatible error response.
type OpenAIErrorResponse struct {
	Error struct {
		Message string `json:"message"`
		Type    string `json:"type"`
		Code    string `json:"code,omitempty"`
	} `json:"error"`
}

// NewErrorResponse creates a new ErrorResponse with the given message and type.
func NewErrorResponse(message, errType string) ErrorResponse {
	return ErrorResponse{
		Code:    errType,
		Message: message,
	}
}

// RetryConfig holds retry configuration for upstream requests.
type RetryConfig struct {
	MaxRetries      int64
	RetryDelay      time.Duration
	MaxRetryDelay   time.Duration
	TimeoutDuration int64
	RetrySleep      time.Duration
}

// NewRetryConfig returns a default RetryConfig.
func NewRetryConfig() *RetryConfig {
	return &RetryConfig{
		MaxRetries:      3,
		RetryDelay:      500 * time.Millisecond,
		MaxRetryDelay:   5 * time.Second,
		TimeoutDuration: 30,
		RetrySleep:      1 * time.Second,
	}
}
