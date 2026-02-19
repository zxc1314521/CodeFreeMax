package logic

import (
	"fmt"
	"log"
	"math/rand"
	"time"

	"kiro2api/internal/dao"
	"kiro2api/internal/gate"
)

// WarmGateCredentialCache pre-decrypts and caches Gate-encrypted credentials
// for all account types (Kiro, Warp, ClaudeAPI, Orchids) at startup.
// This avoids cold-start latency when the first request arrives.
func WarmGateCredentialCache() {
	gateConfig := gate.GetConfig()
	if gateConfig == nil || gateConfig.Key == "" {
		log.Println("[WarmGateCredentialCache] WARNING: Gate config not found or key is empty")
		return
	}

	masterKey := gateConfig.MasterKey

	// === Kiro accounts ===
	warmChannelAccounts("kiro", func() ([]*dao.AccountRow, error) {
		return dao.AccountDaoGetAllNormal()
	}, func(account *dao.AccountRow) map[string]string {
		fields := make(map[string]string)
		if len(account.EncRefreshToken) > 4 && hasGatePrefix(account.EncRefreshToken) {
			fields["refresh_token"] = account.EncRefreshToken // len 0xd = 13
		}
		if len(account.EncClientID) > 4 && hasGatePrefix(account.EncClientID) {
			fields["client_id"] = account.EncClientID // len 9
		}
		if len(account.EncClientSecret) > 4 && hasGatePrefix(account.EncClientSecret) {
			fields["client_secret"] = account.EncClientSecret // len 0xd = 13
		}
		return fields
	}, func(account *dao.AccountRow) string {
		return fmt.Sprintf("%d", account.ID)
	}, masterKey, 4) // concurrency = 4

	// === Warp accounts ===
	warmChannelAccounts("warp", func() ([]*dao.WarpAccountRow, error) {
		return dao.WarpAccountDaoGetAllNormal()
	}, func(account *dao.WarpAccountRow) map[string]string {
		fields := make(map[string]string)
		if len(account.EncRefreshToken) > 4 && hasGatePrefix(account.EncRefreshToken) {
			fields["refresh_token"] = account.EncRefreshToken // len 0xd = 13
		}
		return fields
	}, func(account *dao.WarpAccountRow) string {
		return fmt.Sprintf("%d", account.ID)
	}, masterKey, 4) // concurrency = 4

	// === Claude API accounts ===
	warmChannelAccounts("claude_api", func() ([]*dao.ClaudeApiAccountRow, error) {
		return dao.ClaudeApiAccountDaoGetAllNormal()
	}, func(account *dao.ClaudeApiAccountRow) map[string]string {
		fields := make(map[string]string)
		if len(account.EncToken) > 4 && hasGatePrefix(account.EncToken) {
			fields["token"] = account.EncToken // len 5
		}
		if len(account.EncSessionKey) > 4 && hasGatePrefix(account.EncSessionKey) {
			fields["session_key"] = account.EncSessionKey // len 0xb = 11
		}
		if len(account.EncRefreshToken) > 4 && hasGatePrefix(account.EncRefreshToken) {
			fields["refresh_token"] = account.EncRefreshToken // len 0xd = 13
		}
		return fields
	}, func(account *dao.ClaudeApiAccountRow) string {
		return fmt.Sprintf("%d", account.ID)
	}, masterKey, 10) // concurrency = 10

	// === Orchids accounts ===
	warmChannelAccounts("orchids", func() ([]*dao.OrchidsAccountRow, error) {
		return dao.OrchidsAccountDaoGetAllNormal()
	}, func(account *dao.OrchidsAccountRow) map[string]string {
		fields := make(map[string]string)
		if len(account.EncClientJWT) > 4 && hasGatePrefix(account.EncClientJWT) {
			fields["client_jwt"] = account.EncClientJWT // len 10
		}
		if len(account.EncWsToken) > 4 && hasGatePrefix(account.EncWsToken) {
			fields["ws_token"] = account.EncWsToken // len 8
		}
		if len(account.EncSessionJWT) > 4 && hasGatePrefix(account.EncSessionJWT) {
			fields["session_jwt"] = account.EncSessionJWT // len 0xb = 11
		}
		return fields
	}, func(account *dao.OrchidsAccountRow) string {
		return fmt.Sprintf("%d", account.ID)
	}, masterKey, 7) // concurrency = 7

	fmt.Println("[WarmGateCredentialCache] Gate credential cache warming complete")
}

// warmChannelAccounts is a generic helper that warms the Gate credential cache
// for a specific channel type. It:
// 1. Fetches all normal accounts from the DAO
// 2. Extracts encrypted fields from each account
// 3. Batch-decrypts via Gate
// 4. Caches decrypted credentials with a randomized TTL
func warmChannelAccounts[T any](
	channelName string,
	getAllNormal func() ([]*T, error),
	extractFields func(*T) map[string]string,
	extractID func(*T) string,
	masterKey string,
	concurrency int,
) {
	accounts, err := getAllNormal()
	if err != nil {
		return
	}

	if len(accounts) == 0 {
		return
	}

	// Collect encrypted field maps and account IDs
	var encryptedMaps []map[string]string
	var accountIDs []string

	for _, account := range accounts {
		fields := extractFields(account)
		if len(fields) == 0 {
			continue
		}
		encryptedMaps = append(encryptedMaps, fields)
		accountIDs = append(accountIDs, extractID(account))
	}

	if len(encryptedMaps) == 0 {
		return
	}

	// Batch decrypt
	decryptedMaps, err := gate.DecryptBatch(encryptedMaps, concurrency)
	if err != nil {
		log.Printf("[WarmGateCredentialCache] %s: batch decrypt failed: %v", channelName, err)
		return
	}

	// Cache with randomized TTL
	baseTTL := gate.GetDefaultCacheTTL()
	if concurrency > 0 {
		baseTTL = time.Duration(concurrency) * time.Second
	}

	for i, decrypted := range decryptedMaps {
		ttl := baseTTL
		if baseTTL > 0 {
			// Add jitter: TTL + rand(0, TTL/5)
			jitter := rand.Int63n(int64(baseTTL) / 5)
			ttl = baseTTL + time.Duration(jitter)
		}
		gate.SetCachedCredentialsWithTTL(decrypted, accountIDs[i], ttl)
	}

	log.Printf("[WarmGateCredentialCache] %s: cached %d accounts", channelName, len(decryptedMaps))
}

// hasGatePrefix checks if a string starts with the Gate encryption prefix.
func hasGatePrefix(s string) bool {
	return len(s) > 5 && s[:5] == "gate:"
}
