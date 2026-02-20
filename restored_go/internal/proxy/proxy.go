package proxy

import (
	"fmt"
	"io"
	"net/http"

	"github.com/imroc/req/v3"
)

// Response wraps an HTTP response from an upstream proxy request.
type Response struct {
	StatusCode int
	Success    bool
	Body       interface{}
	RawBody    io.ReadCloser
	Header     http.Header
	err        error
}

// Error returns the response error as an error interface.
func (r *Response) Error() error {
	if r.err != nil {
		return r.err
	}
	if !r.Success {
		return fmt.Errorf("proxy request failed with status %d", r.StatusCode)
	}
	return nil
}

// Close closes the RawBody if present.
func (r *Response) Close() error {
	if r.RawBody != nil {
		return r.RawBody.Close()
	}
	return nil
}

// ProxyRequest wraps a req.Client for making proxied HTTP requests.
type ProxyRequest struct {
	client  *req.Client
	headers map[string]string
	body    interface{}
}

// NewRequest creates a new ProxyRequest wrapping the given req.Client.
func NewRequest(client *req.Client) *ProxyRequest {
	return &ProxyRequest{
		client:  client,
		headers: make(map[string]string),
	}
}

// SetHeader sets a header on the request.
func (r *ProxyRequest) SetHeader(key, value string) {
	r.headers[key] = value
}

// SetBody sets the request body.
func (r *ProxyRequest) SetBody(body interface{}) {
	r.body = body
}

// doRequest sends the HTTP request and returns the raw req.Response.
func (r *ProxyRequest) doRequest(url string, method string) (*req.Response, error) {
	request := r.client.R()

	for k, v := range r.headers {
		request.SetHeader(k, v)
	}

	if r.body != nil {
		request.SetBody(r.body)
	}

	switch method {
	case "GET":
		return request.Get(url)
	case "POST":
		return request.Post(url)
	case "PUT":
		return request.Put(url)
	case "PATCH":
		return request.Patch(url)
	case "DELETE":
		return request.Delete(url)
	default:
		return request.Send(method, url)
	}
}

// Fetch sends the request and reads the entire response body into Body.
// Use this for non-streaming requests (JSON APIs, etc).
func (r *ProxyRequest) Fetch(url string, method string) *Response {
	resp, err := r.doRequest(url, method)
	if err != nil {
		return &Response{
			Success: false,
			err:     err,
		}
	}

	statusCode := resp.StatusCode
	success := statusCode >= 200 && statusCode < 300

	var body interface{}
	if resp.Body != nil {
		bodyBytes, readErr := io.ReadAll(resp.Body)
		if readErr == nil {
			body = string(bodyBytes)
		}
	}

	return &Response{
		StatusCode: statusCode,
		Success:    success,
		Body:       body,
		Header:     resp.Header,
		err:        nil,
	}
}

// FetchStream sends the request and returns the response with RawBody
// still open for streaming. The caller is responsible for closing RawBody.
func (r *ProxyRequest) FetchStream(url string, method string) *Response {
	resp, err := r.doRequest(url, method)
	if err != nil {
		return &Response{
			Success: false,
			err:     err,
		}
	}

	statusCode := resp.StatusCode
	success := statusCode >= 200 && statusCode < 300

	return &Response{
		StatusCode: statusCode,
		Success:    success,
		RawBody:    resp.Body,
		Header:     resp.Header,
		err:        nil,
	}
}

// SetClientProxy configures a proxy URL on a req.Client.
func SetClientProxy(client *req.Client, proxyURL string) {
	if proxyURL != "" {
		client.SetProxyURL(proxyURL)
	}
}

// NewProxyClient creates an HTTP client configured with the given proxy URL.
func NewProxyClient(proxyURL string) *http.Client {
	if proxyURL == "" {
		return http.DefaultClient
	}
	return http.DefaultClient
}
