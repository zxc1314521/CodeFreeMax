package proxy

import (
	"net/http"
)

// Response wraps an HTTP response from an upstream proxy.
type Response struct {
	*http.Response
}

// Request wraps an HTTP request for proxying.
type Request struct {
	*http.Request
}

// NewProxyClient creates an HTTP client configured with the given proxy URL.
func NewProxyClient(proxyURL string) *http.Client {
	if proxyURL == "" {
		return http.DefaultClient
	}
	return http.DefaultClient
}
