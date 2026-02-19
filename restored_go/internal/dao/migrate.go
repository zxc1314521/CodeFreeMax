package dao

import (
	"log"
	"strings"

	"kiro2api/internal/crypt"
	"kiro2api/internal/gate"

	"gorm.io/gorm"
)

// KiroMigrationRow represents a row from kiro_accounts for gate migration
type KiroMigrationRow struct {
	ID           int64
	RefreshToken string
	ClientID     string
	ClientSecret string
}

// OrchidsMigrationRow represents a row from orchids_accounts for gate migration
type OrchidsMigrationRow struct {
	ID         int64
	ClientJWT  string
	WsToken    string
	SessionJWT string
}

// ClaudeApiMigrationRow represents a row from claude_api_accounts for gate migration
type ClaudeApiMigrationRow struct {
	ID           int64
	EncToken     string
	EncSessionKey   string
	EncRefreshToken string
}

// MigrateKiroToGate migrates kiro_accounts credentials from legacy encryption to Gate encryption.
// It reads accounts where enc_session_key is NULL or empty (not yet migrated to gate),
// decrypts old credentials, re-encrypts with Gate, and updates the database.
func MigrateKiroToGate(db *gorm.DB) {
	var rows []KiroMigrationRow

	// Query accounts that haven't been migrated to gate yet
	// Original SQL length 0xc3 = 195 chars
	err := db.Session(&gorm.Session{}).
		Raw(`SELECT id, refresh_token, client_id, client_secret FROM kiro_accounts
		     WHERE (enc_session_key IS NULL OR enc_session_key = '')
		     AND session_key IS NOT NULL AND session_key != '' AND LENGTH(session_key) > 64`).
		Scan(&rows).Error

	if err != nil {
		log.Printf("[MigrateKiroToGate] Failed to query kiro accounts: %v", err)
		return
	}

	if len(rows) == 0 {
		return
	}

	log.Printf("[MigrateKiroToGate] Found %d accounts to migrate", len(rows))

	decryptedMap := make(map[string]string) // field -> decrypted value

	for _, row := range rows {
		// Clear map for each row
		for k := range decryptedMap {
			delete(decryptedMap, k)
		}

		// Decrypt refresh_token (field key length 0xd = 13 = "refresh_token")
		if row.RefreshToken != "" && len(row.RefreshToken) >= 3 {
			if strings.HasPrefix(row.RefreshToken, "enc") || len(row.RefreshToken) > 3 {
				decrypted, err := crypt.DecryptCredential(row.RefreshToken)
				if err == nil && decrypted != "" {
					decryptedMap["refresh_token"] = decrypted
				}
			}
		}

		// Decrypt client_id (field key length 9 = "client_id")
		if row.ClientID != "" && len(row.ClientID) >= 3 {
			if strings.HasPrefix(row.ClientID, "enc") || len(row.ClientID) > 3 {
				decrypted, err := crypt.DecryptCredential(row.ClientID)
				if err == nil && decrypted != "" {
					decryptedMap["client_id"] = decrypted
				}
			}
		}

		// Decrypt client_secret (field key length 0xd = 13 = "client_secret")
		if row.ClientSecret != "" && len(row.ClientSecret) >= 3 {
			if strings.HasPrefix(row.ClientSecret, "enc") || len(row.ClientSecret) > 3 {
				decrypted, err := crypt.DecryptCredential(row.ClientSecret)
				if err == nil && decrypted != "" {
					decryptedMap["client_secret"] = decrypted
				}
			}
		}

		// Re-encrypt with Gate (channel = "kiro", length 4)
		gateEncrypted, err := gate.Encrypt("kiro", decryptedMap)
		if err != nil {
			log.Printf("[MigrateKiroToGate] Gate encrypt failed for id=%d: %v", row.ID, err)
			continue
		}

		// Retrieve decrypted values for UPDATE
		encRefreshToken := decryptedMap["refresh_token"]
		encClientID := decryptedMap["client_id"]
		encClientSecret := decryptedMap["client_secret"]

		// Update with gate-encrypted credentials
		// Original SQL length 0x65 = 101 chars
		result := db.Session(&gorm.Session{}).
			Exec(`UPDATE kiro_accounts SET enc_refresh_token = ?, enc_client_id = ?, enc_client_secret = ? WHERE id = ?`,
				encRefreshToken, encClientID, encClientSecret, row.ID)

		if result.Error != nil {
			log.Printf("[MigrateKiroToGate] Update failed for id=%d: %v", row.ID, result.Error)
		}

		_ = gateEncrypted
	}

	log.Printf("[MigrateKiroToGate] Migration complete: %d accounts processed", len(rows))
}

// MigrateOrchidsToGate migrates orchids_accounts credentials from legacy encryption to Gate encryption.
func MigrateOrchidsToGate(db *gorm.DB) {
	var rows []OrchidsMigrationRow

	// Query accounts not yet migrated (enc_client_jwt NOT LIKE 'gate:%')
	// Original SQL length 0xb7 = 183 chars
	err := db.Session(&gorm.Session{}).
		Raw(`SELECT id, enc_client_jwt, enc_ws_token, enc_session_jwt FROM orchids_accounts
		     WHERE enc_client_jwt NOT LIKE 'gate:%'
		     AND client_jwt IS NOT NULL AND client_jwt != ''`).
		Scan(&rows).Error

	if err != nil {
		log.Printf("[MigrateOrchidsToGate] Failed to query orchids accounts: %v", err)
		return
	}

	if len(rows) == 0 {
		return
	}

	log.Printf("[MigrateOrchidsToGate] Found %d accounts to migrate", len(rows))

	decryptedMap := make(map[string]string)

	for _, row := range rows {
		for k := range decryptedMap {
			delete(decryptedMap, k)
		}

		// Decrypt client_jwt (field key length 10 = "client_jwt")
		if row.ClientJWT != "" && len(row.ClientJWT) >= 3 {
			if strings.HasPrefix(row.ClientJWT, "enc") || len(row.ClientJWT) > 3 {
				decrypted, err := crypt.DecryptCredential(row.ClientJWT)
				if err == nil && decrypted != "" {
					decryptedMap["client_jwt"] = decrypted
				}
			}
		}

		// Decrypt ws_token (field key length 8 = "ws_token")
		if row.WsToken != "" && len(row.WsToken) >= 3 {
			if strings.HasPrefix(row.WsToken, "enc") || len(row.WsToken) > 3 {
				decrypted, err := crypt.DecryptCredential(row.WsToken)
				if err == nil && decrypted != "" {
					decryptedMap["ws_token"] = decrypted
				}
			}
		}

		// Decrypt session_jwt (field key length 0xb = 11 = "session_jwt")
		if row.SessionJWT != "" && len(row.SessionJWT) >= 3 {
			if strings.HasPrefix(row.SessionJWT, "enc") || len(row.SessionJWT) > 3 {
				decrypted, err := crypt.DecryptCredential(row.SessionJWT)
				if err == nil && decrypted != "" {
					decryptedMap["session_jwt"] = decrypted
				}
			}
		}

		// Re-encrypt with Gate (channel = "orchids", length 7)
		gateEncrypted, err := gate.Encrypt("orchids", decryptedMap)
		if err != nil {
			log.Printf("[MigrateOrchidsToGate] Gate encrypt failed for id=%d: %v", row.ID, err)
			continue
		}

		encClientJWT := decryptedMap["client_jwt"]
		encWsToken := decryptedMap["ws_token"]
		encSessionJWT := decryptedMap["session_jwt"]

		// Original SQL length 0x62 = 98 chars
		result := db.Session(&gorm.Session{}).
			Exec(`UPDATE orchids_accounts SET enc_client_jwt = ?, enc_ws_token = ?, enc_session_jwt = ? WHERE id = ?`,
				encClientJWT, encWsToken, encSessionJWT, row.ID)

		if result.Error != nil {
			log.Printf("[MigrateOrchidsToGate] Update failed for id=%d: %v", row.ID, result.Error)
		}

		_ = gateEncrypted
	}

	log.Printf("[MigrateOrchidsToGate] Migration complete: %d accounts processed", len(rows))
}

// MigrateClaudeApiToGate migrates claude_api_accounts credentials from legacy encryption to Gate encryption.
func MigrateClaudeApiToGate(db *gorm.DB) {
	var rows []ClaudeApiMigrationRow

	// Query accounts not yet migrated
	// Original SQL length 0x17b = 379 chars
	err := db.Session(&gorm.Session{}).
		Raw(`SELECT id, enc_token, enc_session_key, enc_refresh_token FROM claude_api_accounts
		     WHERE (enc_session_key IS NULL OR enc_session_key = '' OR enc_session_key NOT LIKE 'gate:%')`).
		Scan(&rows).Error

	if err != nil {
		log.Printf("[MigrateClaudeApiToGate] Failed to query claude_api accounts: %v", err)
		return
	}

	if len(rows) == 0 {
		return
	}

	log.Printf("[MigrateClaudeApiToGate] Found %d accounts to migrate", len(rows))

	decryptedMap := make(map[string]string)

	for _, row := range rows {
		for k := range decryptedMap {
			delete(decryptedMap, k)
		}

		// Decrypt token (field key length 5 = "token")
		if row.EncToken != "" && len(row.EncToken) >= 3 {
			if strings.HasPrefix(row.EncToken, "enc") || len(row.EncToken) > 3 {
				decrypted, err := crypt.DecryptCredential(row.EncToken)
				if err == nil && decrypted != "" {
					decryptedMap["token"] = decrypted
				}
			}
		}

		// Decrypt session_key (field key length 0xb = 11 = "session_key")
		if row.EncSessionKey != "" && len(row.EncSessionKey) >= 3 {
			if strings.HasPrefix(row.EncSessionKey, "enc") || len(row.EncSessionKey) > 3 {
				decrypted, err := crypt.DecryptCredential(row.EncSessionKey)
				if err == nil && decrypted != "" {
					decryptedMap["session_key"] = decrypted
				}
			}
		}

		// Decrypt refresh_token (field key length 0xd = 13 = "refresh_token")
		if row.EncRefreshToken != "" && len(row.EncRefreshToken) >= 3 {
			if strings.HasPrefix(row.EncRefreshToken, "enc") || len(row.EncRefreshToken) > 3 {
				decrypted, err := crypt.DecryptCredential(row.EncRefreshToken)
				if err == nil && decrypted != "" {
					decryptedMap["refresh_token"] = decrypted
				}
			}
		}

		// Re-encrypt with Gate (channel = "claude_api", length 10)
		gateEncrypted, err := gate.Encrypt("claude_api", decryptedMap)
		if err != nil {
			log.Printf("[MigrateClaudeApiToGate] Gate encrypt failed for id=%d: %v", row.ID, err)
			continue
		}

		encToken := decryptedMap["token"]
		encSessionKey := decryptedMap["session_key"]
		encRefreshToken := decryptedMap["refresh_token"]

		// Original SQL length 0x65 = 101 chars
		result := db.Session(&gorm.Session{}).
			Exec(`UPDATE claude_api_accounts SET enc_token = ?, enc_session_key = ?, enc_refresh_token = ? WHERE id = ?`,
				encToken, encSessionKey, encRefreshToken, row.ID)

		if result.Error != nil {
			log.Printf("[MigrateClaudeApiToGate] Update failed for id=%d: %v", row.ID, result.Error)
		}

		_ = gateEncrypted
	}

	log.Printf("[MigrateClaudeApiToGate] Migration complete: %d accounts processed", len(rows))
}

// CursorMigrationRow represents a row from cursor_accounts for gate migration.
type CursorMigrationRow struct {
	ID              int64
	EncAccessToken  string
	EncRefreshToken string
	EncClientKey    string
}

// MigrateCursorCredentials migrates cursor_accounts credentials from legacy encryption to Gate encryption.
// Symbol: kiro2api/internal/dao.MigrateCursorCredentials (1408B @ 0x17f5b80)
//
// The 1408B size is consistent with the other migration functions (KiroToGate=1344B, OrchidsToGate=1408B).
// Same pattern: query → decrypt → re-encrypt with Gate → update.
func MigrateCursorCredentials(db *gorm.DB) {
	var rows []CursorMigrationRow

	// Query accounts not yet migrated to Gate
	err := db.Session(&gorm.Session{}).
		Raw(`SELECT id, enc_access_token, enc_refresh_token, enc_client_key FROM cursor_accounts
		     WHERE (enc_access_token IS NULL OR enc_access_token = '' OR enc_access_token NOT LIKE 'gate:%')
		     AND access_token IS NOT NULL AND access_token != ''`).
		Scan(&rows).Error

	if err != nil {
		log.Printf("[MigrateCursorCredentials] Failed to query cursor accounts: %v", err)
		return
	}

	if len(rows) == 0 {
		return
	}

	log.Printf("[MigrateCursorCredentials] Found %d accounts to migrate", len(rows))

	decryptedMap := make(map[string]string)

	for _, row := range rows {
		for k := range decryptedMap {
			delete(decryptedMap, k)
		}

		// Decrypt access_token (field key length 0xc = 12 = "access_token")
		if row.EncAccessToken != "" && len(row.EncAccessToken) >= 3 {
			if strings.HasPrefix(row.EncAccessToken, "enc") || len(row.EncAccessToken) > 3 {
				decrypted, err := crypt.DecryptCredential(row.EncAccessToken)
				if err == nil && decrypted != "" {
					decryptedMap["access_token"] = decrypted
				}
			}
		}

		// Decrypt refresh_token (field key length 0xd = 13 = "refresh_token")
		if row.EncRefreshToken != "" && len(row.EncRefreshToken) >= 3 {
			if strings.HasPrefix(row.EncRefreshToken, "enc") || len(row.EncRefreshToken) > 3 {
				decrypted, err := crypt.DecryptCredential(row.EncRefreshToken)
				if err == nil && decrypted != "" {
					decryptedMap["refresh_token"] = decrypted
				}
			}
		}

		// Decrypt client_key (field key length 0xa = 10 = "client_key")
		if row.EncClientKey != "" && len(row.EncClientKey) >= 3 {
			if strings.HasPrefix(row.EncClientKey, "enc") || len(row.EncClientKey) > 3 {
				decrypted, err := crypt.DecryptCredential(row.EncClientKey)
				if err == nil && decrypted != "" {
					decryptedMap["client_key"] = decrypted
				}
			}
		}

		// Re-encrypt with Gate (channel = "cursor", length 6)
		gateEncrypted, err := gate.Encrypt("cursor", decryptedMap)
		if err != nil {
			log.Printf("[MigrateCursorCredentials] Gate encrypt failed for id=%d: %v", row.ID, err)
			continue
		}

		encAccessToken := decryptedMap["access_token"]
		encRefreshToken := decryptedMap["refresh_token"]
		encClientKey := decryptedMap["client_key"]

		result := db.Session(&gorm.Session{}).
			Exec(`UPDATE cursor_accounts SET enc_access_token = ?, enc_refresh_token = ?, enc_client_key = ? WHERE id = ?`,
				encAccessToken, encRefreshToken, encClientKey, row.ID)

		if result.Error != nil {
			log.Printf("[MigrateCursorCredentials] Update failed for id=%d: %v", row.ID, result.Error)
		}

		_ = gateEncrypted
	}

	log.Printf("[MigrateCursorCredentials] Migration complete: %d accounts processed", len(rows))
}

// RegisterMigration is a helper to register a migration function.
// Called from package init() functions to register channel-specific migrations.
func RegisterMigration(fn func(db *gorm.DB)) {
	// Registration is handled by the migration runner
	// This is a placeholder — actual implementation adds to a global migration list
	_ = fn
}
