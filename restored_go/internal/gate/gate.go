package gate

import (
	"time"
)

// GateConfig holds the Gate encryption configuration.
type GateConfig struct {
	Key       string
	MasterKey string
}

var globalConfig *GateConfig

func init() {
	globalConfig = &GateConfig{
		Key:       "default-gate-key",
		MasterKey: "default-master-key",
	}
}

// GetConfig returns the global Gate configuration.
func GetConfig() *GateConfig {
	return globalConfig
}

// Encrypt encrypts a map of credentials for the given channel.
func Encrypt(channel string, fields map[string]string) (string, error) {
	// Stub: return fields as-is, no actual encryption
	return "gate:stub", nil
}

// Decrypt decrypts a Gate-encrypted credential string.
func Decrypt(channel string, encrypted string) (map[string]string, error) {
	return map[string]string{}, nil
}

// DecryptBatch decrypts multiple credential maps concurrently.
func DecryptBatch(encryptedMaps []map[string]string, concurrency int) ([]map[string]string, error) {
	result := make([]map[string]string, len(encryptedMaps))
	for i, m := range encryptedMaps {
		decrypted := make(map[string]string)
		for k, v := range m {
			decrypted[k] = v
		}
		result[i] = decrypted
	}
	return result, nil
}

// GetDefaultCacheTTL returns the default cache TTL for Gate credentials.
func GetDefaultCacheTTL() time.Duration {
	return 30 * time.Minute
}

// SetCachedCredentialsWithTTL caches decrypted credentials with a TTL.
func SetCachedCredentialsWithTTL(credentials map[string]string, accountID string, ttl time.Duration) {
	// Stub: no-op
}
