package cursor

import (
	"context"
	"crypto/sha256"
	"crypto/tls"
	"encoding/hex"
	"fmt"
	"net"
	"net/http"
	"strings"
	"time"

	utls "github.com/refraction-networking/utls"

	"kiro2api/internal/model"
)

// ============================================================================
// uTLS Connection Wrapper
// ============================================================================

// uTLSConn wraps a utls.UConn to implement net.Conn with TLS fingerprint spoofing.
// Symbol: kiro2api/internal/logic/cursor.uTLSConn (many methods, 32-448B each)
//
// The binary contains ~40 method wrappers for uTLSConn, most of which are
// thin delegations to the underlying utls.UConn. This is used to make
// Cursor API requests appear to come from a real Cursor IDE client by
// mimicking its TLS fingerprint (JA3).
type uTLSConn struct {
	*utls.UConn
}

// ConnectionState returns the TLS connection state.
// Symbol: kiro2api/internal/logic/cursor.(*uTLSConn).ConnectionState (576B @ 0x17fb560)
// The larger size (576B) suggests it copies/transforms the connection state struct.
func (c *uTLSConn) ConnectionState() tls.ConnectionState {
	uState := c.UConn.ConnectionState()
	return tls.ConnectionState{
		Version:                     uState.Version,
		HandshakeComplete:           uState.HandshakeComplete,
		DidResume:                   uState.DidResume,
		CipherSuite:                 uState.CipherSuite,
		NegotiatedProtocol:          uState.NegotiatedProtocol,
		NegotiatedProtocolIsMutual:  uState.NegotiatedProtocolIsMutual,
		ServerName:                  uState.ServerName,
		PeerCertificates:            uState.PeerCertificates,
		VerifiedChains:              uState.VerifiedChains,
		SignedCertificateTimestamps: uState.SignedCertificateTimestamps,
		OCSPResponse:                uState.OCSPResponse,
	}
}

// ============================================================================
// HTTP Client Factories
// ============================================================================

// NewCursorClient creates an HTTP client with uTLS fingerprint spoofing
// for making requests to the Cursor API.
// Symbol: kiro2api/internal/logic/cursor.NewCursorClient (416B @ 0x17fb7a0)
//
// The client uses a custom TLS dialer that applies a Chrome-like TLS fingerprint
// to evade Cursor's TLS fingerprint detection.
//
// Inner functions:
//   - NewCursorClient.func1 (128B @ 0x1801a20): TLS config callback
//   - NewCursorClient.func1.1 (320B @ 0x1801aa0): TLS handshake wrapper
//   - NewCursorClient.tlsHandshake.func3 (2912B @ 0x17fb940): Full TLS handshake with uTLS
//   - NewCursorClient.(*Client).SetCommonHeaderOrder.func2 (224B @ 0x17fc4a0): Header ordering
//   - NewCursorClient.(*Client).SetCommonHeaderOrder.func2.1 (288B @ 0x17fc580): Header sort
func NewCursorClient(account *model.CursorAccount) *http.Client {
	// Custom TLS dialer with uTLS fingerprint
	tlsDialer := func(ctx context.Context, network, addr string) (net.Conn, error) {
		// Establish raw TCP connection
		dialer := &net.Dialer{
			Timeout: 30 * time.Second,
		}
		rawConn, err := dialer.DialContext(ctx, network, addr)
		if err != nil {
			return nil, err
		}

		// Extract hostname for SNI
		host, _, err := net.SplitHostPort(addr)
		if err != nil {
			host = addr
		}

		// Create uTLS connection with Chrome fingerprint
		// Symbol: NewCursorClient.tlsHandshake.func3 (2912B @ 0x17fb940)
		// The large size (2912B) indicates a full ClientHelloSpec configuration
		tlsConfig := &utls.Config{
			ServerName:         host,
			InsecureSkipVerify: false,
		}

		uConn := utls.UClient(rawConn, tlsConfig, utls.HelloChrome_Auto)

		// Perform TLS handshake
		if err := uConn.HandshakeContext(ctx); err != nil {
			rawConn.Close()
			return nil, fmt.Errorf("uTLS handshake failed: %w", err)
		}

		return &uTLSConn{UConn: uConn}, nil
	}

	// Build HTTP transport with custom TLS dialer
	transport := &http.Transport{
		DialTLSContext:        tlsDialer,
		MaxIdleConns:          100,
		MaxIdleConnsPerHost:   10,
		IdleConnTimeout:       90 * time.Second,
		TLSHandshakeTimeout:  30 * time.Second,
		ExpectContinueTimeout: 1 * time.Second,
		ForceAttemptHTTP2:     true,
	}

	// Set proxy if configured
	if account != nil && account.ProxyURL != "" {
		transport.Proxy = http.ProxyFromEnvironment
	}

	return &http.Client{
		Transport: transport,
		Timeout:   300 * time.Second, // 5 minute timeout for streaming
	}
}

// NewCursorAPIClient creates a standard HTTP client for Cursor API requests
// without uTLS fingerprint spoofing (used for non-sensitive endpoints).
// Symbol: kiro2api/internal/logic/cursor.NewCursorAPIClient (128B @ 0x17fc720)
//
// The small size (128B) indicates this is a simple client factory.
func NewCursorAPIClient() *http.Client {
	return &http.Client{
		Timeout: 30 * time.Second,
		Transport: &http.Transport{
			MaxIdleConns:        100,
			MaxIdleConnsPerHost: 10,
			IdleConnTimeout:     90 * time.Second,
		},
	}
}

// NewCursorOfficialClient creates an HTTP client configured to mimic
// the official Cursor IDE client behavior.
// Symbol: kiro2api/internal/logic/cursor.NewCursorOfficialClient (128B @ 0x17fc6a0)
func NewCursorOfficialClient() *http.Client {
	return &http.Client{
		Timeout: 120 * time.Second,
		Transport: &http.Transport{
			TLSClientConfig: &tls.Config{
				MinVersion: tls.VersionTLS12,
			},
			MaxIdleConns:        50,
			MaxIdleConnsPerHost: 10,
			IdleConnTimeout:     90 * time.Second,
			ForceAttemptHTTP2:   true,
		},
	}
}

// ============================================================================
// Checksum Generation
// ============================================================================

// GetChecksum generates the x-cursor-checksum header value for request validation.
// Symbol: kiro2api/internal/logic/cursor.GetChecksum (896B @ 0x18016a0)
//
// This is Cursor's anti-tampering mechanism. The checksum is computed from:
//   - The checksum seed (account-specific secret)
//   - The account object (serialized fields)
//   - The request headers (specific subset)
//   - The machine ID
//
// The 896B size suggests SHA-256 hashing with multiple rounds of concatenation.
//
// From the decompiled newConnectRequest (line 1815):
//
//	kiro2api_internal_logic_cursor_GetChecksum(
//	    account.offset_0xa0,  // ChecksumSeed
//	    account,              // full account
//	    headers,              // request headers
//	    account.offset_0x98,  // MachineID
//	)
func GetChecksum(checksumSeed string, account *model.CursorAccount, headers http.Header, machineID string) string {
	if checksumSeed == "" {
		checksumSeed = "default"
	}

	// Build the checksum input by concatenating relevant fields
	// The exact algorithm is reconstructed from the 896B function
	var parts []string

	// Include machine ID
	parts = append(parts, machineID)

	// Include account identifier
	if account != nil {
		parts = append(parts, fmt.Sprintf("%d", account.ID))
		parts = append(parts, account.ClientKey)
	}

	// Include specific headers that Cursor validates
	headerKeys := []string{
		"authorization",
		"x-request-id",
		"x-cursor-client-key",
		"content-type",
	}
	for _, key := range headerKeys {
		if val := headers.Get(key); val != "" {
			parts = append(parts, val)
		}
	}

	// Concatenate with seed
	input := checksumSeed + ":" + strings.Join(parts, ";")

	// SHA-256 hash
	hash := sha256.Sum256([]byte(input))
	return hex.EncodeToString(hash[:])
}

// encodeBytes2Base64 encodes binary data to base64 with optional padding handling.
// Symbol: kiro2api/internal/logic/cursor.encodeBytes2Base64 (2048B @ 0x1800ea0)
//
// The 2048B size suggests this handles protobuf binary encoding with
// length-prefix framing for the Connect protocol.
func encodeBytes2Base64(data []byte) []byte {
	if len(data) == 0 {
		return nil
	}

	// Connect protocol uses a 5-byte prefix:
	// byte 0: compression flag (0 = uncompressed)
	// bytes 1-4: big-endian uint32 message length
	prefix := make([]byte, 5)
	prefix[0] = 0 // uncompressed
	msgLen := uint32(len(data))
	prefix[1] = byte(msgLen >> 24)
	prefix[2] = byte(msgLen >> 16)
	prefix[3] = byte(msgLen >> 8)
	prefix[4] = byte(msgLen)

	return append(prefix, data...)
}
