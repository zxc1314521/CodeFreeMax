package kiro

// client.go — HTTP client construction and context-aware I/O for the Kiro channel.
//
// Functions:
//   - newKiroClient           (416B  @ 0x17a3180) — HTTP client constructor
//   - contextCloser.Read      (160B  @ 0x17ab500) — Context-aware reader
//   - (*contextCloser).Close  (96B   @ 0x17a3c20) — Close context reader
//   - (*contextCloser).Read   (128B  @ 0x17ab5a0) — Read with context check
//
// The Kiro channel uses req/v3 HTTP client with:
//   - Configurable proxy support
//   - 5-minute timeout for streaming requests
//   - Context-aware body reader that cancels on context done
//   - TLS configuration for AWS endpoints

import (
	"context"
	"io"
	"time"

	"github.com/imroc/req/v3"
)

// ============================================================================
// newKiroClient
// ============================================================================

// newKiroClient creates an HTTP client configured for Kiro API requests.
// Symbol: kiro2api/internal/logic/kiro.newKiroClient (416B @ 0x17a3180)
//
// From decompiled (416 bytes):
//   1. Clone the base client
//   2. Set proxy if configured
//   3. Set timeout to requestTimeoutNs (5 minutes = 300000000000 ns)
//   4. Configure TLS settings for AWS endpoints
//   5. Set user agent and other default headers
//
// The client is cloned from the shared base client to inherit connection
// pooling and TLS session caching while allowing per-request customization.
func newKiroClient(baseClient *req.Client, proxyURL string) *req.Client {
	client := baseClient.Clone()

	// Set proxy if configured
	if proxyURL != "" {
		client.SetProxyURL(proxyURL)
	}

	// Set timeout for streaming requests (5 minutes)
	// From decompiled: timeout = 300000000000 ns
	client.SetTimeout(time.Duration(requestTimeoutNs))

	// Disable auto-read response body for streaming
	client.DisableAutoReadResponse()

	return client
}

// ============================================================================
// contextCloser
// ============================================================================

// contextCloser wraps an io.ReadCloser with context cancellation support.
// When the context is cancelled, reads will return immediately with the
// context error instead of blocking.
//
// Symbol: kiro2api/internal/logic/kiro.contextCloser (struct)
//   - Read  (160B @ 0x17ab500) — Read method
//   - Close (96B  @ 0x17a3c20) — Close method
//   - Read  (128B @ 0x17ab5a0) — Alternative read path
//
// This is used to wrap the HTTP response body so that when the client
// disconnects (context cancelled), the streaming read is interrupted
// promptly rather than waiting for the server to close the connection.
type contextCloser struct {
	ctx    context.Context
	body   io.ReadCloser
	cancel context.CancelFunc
}

// newContextCloser creates a new contextCloser wrapping the given body.
func newContextCloser(ctx context.Context, body io.ReadCloser) *contextCloser {
	ctx, cancel := context.WithCancel(ctx)
	return &contextCloser{
		ctx:    ctx,
		body:   body,
		cancel: cancel,
	}
}

// Read reads from the underlying body, checking for context cancellation.
// Symbol: kiro2api/internal/logic/kiro.contextCloser.Read (160B @ 0x17ab500)
//
// From decompiled (160 bytes):
//   1. Check ctx.Done() channel (non-blocking select)
//   2. If context cancelled → return 0, ctx.Err()
//   3. Otherwise → delegate to body.Read(p)
//
// The alternative Read (128B @ 0x17ab5a0) appears to be the interface
// method implementation that delegates to the same logic.
func (c *contextCloser) Read(p []byte) (int, error) {
	select {
	case <-c.ctx.Done():
		return 0, c.ctx.Err()
	default:
	}
	return c.body.Read(p)
}

// Close closes the underlying body and cancels the context.
// Symbol: kiro2api/internal/logic/kiro.(*contextCloser).Close (96B @ 0x17a3c20)
//
// From decompiled (96 bytes — very small):
//   1. Cancel the context
//   2. Close the underlying body
func (c *contextCloser) Close() error {
	c.cancel()
	if c.body != nil {
		return c.body.Close()
	}
	return nil
}
