package model

import "time"

// CursorAccount represents a Cursor IDE account in the database.
// Table: cursor_accounts
//
// Reconstructed from binary struct field offsets in buildCursorRequest and newConnectRequest:
//   - offset 0x08: ID (int64)
//   - offset 0x10: Email (string ptr + len)
//   - offset 0x20: AccessToken (string ptr + len)
//   - offset 0x30: RefreshToken (string ptr + len)
//   - offset 0x40: ClientID (string ptr + len)
//   - offset 0x50: Status (string ptr + len)
//   - offset 0x60: ProxyURL (string ptr + len)
//   - offset 0x68/0x70: ClientKey (string ptr + len)
//   - offset 0x80: MachineID (string ptr + len)
//   - offset 0x90/0x98: ChecksumSeed (string ptr + len)
//   - offset 0xa0: (ChecksumSeed referenced again in GetChecksum)
//   - offset 0xa8/0xb0: ClientVersion (string ptr + len)
//   - offset 0xb8: TokenExpiresAt (time.Time)
//   - offset 0xc8: LastUsedAt (time.Time)
//   - offset 0xd0: UsageCount (int64)
//   - offset 0xd8: MaxUsagePerToken (int64)
//   - offset 0xe0: NeedsRotation (bool)
type CursorAccount struct {
	ID               int64     `gorm:"primaryKey;autoIncrement" json:"id"`
	Email            string    `gorm:"column:email;size:255" json:"email"`
	AccessToken      string    `gorm:"column:access_token;type:text" json:"access_token"`
	RefreshToken     string    `gorm:"column:refresh_token;type:text" json:"refresh_token"`
	ClientID         string    `gorm:"column:client_id;size:255" json:"client_id"`
	Status           string    `gorm:"column:status;size:50;default:active" json:"status"`
	ProxyURL         string    `gorm:"column:proxy_url;size:512" json:"proxy_url"`
	ClientKey        string    `gorm:"column:client_key;size:255" json:"client_key"`
	MachineID        string    `gorm:"column:machine_id;size:255" json:"machine_id"`
	ChecksumSeed     string    `gorm:"column:checksum_seed;size:255" json:"checksum_seed"`
	ClientVersion    string    `gorm:"column:client_version;size:50" json:"client_version"`
	TokenExpiresAt   time.Time `gorm:"column:token_expires_at" json:"token_expires_at"`
	LastUsedAt       time.Time `gorm:"column:last_used_at" json:"last_used_at"`
	UsageCount       int64     `gorm:"column:usage_count;default:0" json:"usage_count"`
	MaxUsagePerToken int64     `gorm:"column:max_usage_per_token;default:0" json:"max_usage_per_token"`
	NeedsRotation    bool      `gorm:"column:needs_rotation;default:false" json:"needs_rotation"`

	// Gate-encrypted credential fields
	EncAccessToken  string `gorm:"column:enc_access_token;type:text" json:"enc_access_token"`
	EncRefreshToken string `gorm:"column:enc_refresh_token;type:text" json:"enc_refresh_token"`
	EncClientKey    string `gorm:"column:enc_client_key;type:text" json:"enc_client_key"`

	CreatedAt time.Time `gorm:"column:created_at;autoCreateTime" json:"created_at"`
	UpdatedAt time.Time `gorm:"column:updated_at;autoUpdateTime" json:"updated_at"`
}

// TableName returns the database table name.
func (CursorAccount) TableName() string {
	return "cursor_accounts"
}

// LoadGateCredentials decrypts Gate-encrypted credentials and populates
// the plaintext fields. Returns 0 on success, non-zero on error.
// Symbol: (*CursorAccount).LoadGateCredentials (referenced in ChatCompletions)
func (a *CursorAccount) LoadGateCredentials() int {
	// Gate decryption is handled by the gate package
	// This is a placeholder — actual implementation calls gate.Decrypt
	return 0
}

// EncryptAndSetCredentials encrypts plaintext credentials with Gate
// and stores them in the enc_* fields.
// Symbol: (*CursorAccount).EncryptAndSetCredentials (referenced in RefreshToken)
func (a *CursorAccount) EncryptAndSetCredentials() {
	// Gate encryption is handled by the gate package
	// This is a placeholder — actual implementation calls gate.Encrypt
}

// ClaudeApiAccount represents a Claude API account in the database.
// Table: claude_api_accounts
//
// Referenced throughout the claudeapi package.
type ClaudeApiAccount struct {
	ID              int64     `gorm:"primaryKey;autoIncrement" json:"id"`
	Email           string    `gorm:"column:email;size:255" json:"email"`
	APIKey          string    `gorm:"column:api_key;type:text" json:"api_key"`
	AccessToken     string    `gorm:"column:access_token;type:text" json:"access_token"`
	RefreshToken    string    `gorm:"column:refresh_token;type:text" json:"refresh_token"`
	SessionKey      string    `gorm:"column:session_key;type:text" json:"session_key"`
	SessionKeyLen   int       `gorm:"column:session_key_len" json:"session_key_len"`
	ClientID        string    `gorm:"column:client_id;size:255" json:"client_id"`
	OrganizationID  string    `gorm:"column:organization_id;size:255" json:"organization_id"`
	AccountType     string    `gorm:"column:account_type;size:50" json:"account_type"`
	Status          string    `gorm:"column:status;size:50;default:active" json:"status"`
	ProxyURL        string    `gorm:"column:proxy_url;size:512" json:"proxy_url"`
	ThinkingBudget  int       `gorm:"column:thinking_budget;default:0" json:"thinking_budget"`
	Context         string    `gorm:"column:context;type:text" json:"context"`
	TokenExpiresAt  time.Time `gorm:"column:token_expires_at" json:"token_expires_at"`

	// Gate-encrypted credential fields
	EncToken        string `gorm:"column:enc_token;type:text" json:"enc_token"`
	EncSessionKey   string `gorm:"column:enc_session_key;type:text" json:"enc_session_key"`
	EncRefreshToken string `gorm:"column:enc_refresh_token;type:text" json:"enc_refresh_token"`

	CreatedAt time.Time `gorm:"column:created_at;autoCreateTime" json:"created_at"`
	UpdatedAt time.Time `gorm:"column:updated_at;autoUpdateTime" json:"updated_at"`
}

// TableName returns the database table name.
func (ClaudeApiAccount) TableName() string {
	return "claude_api_accounts"
}

// LoadGateCredentials decrypts Gate-encrypted credentials.
func (a *ClaudeApiAccount) LoadGateCredentials() int {
	return 0
}

// EncryptAndSetCredentials encrypts credentials with Gate.
func (a *ClaudeApiAccount) EncryptAndSetCredentials() {
}
