package dao

import (
	"log"
	"time"

	"gorm.io/gorm"
)

// DBChannelAccount is the GORM model for the channel_accounts table.
type DBChannelAccount struct {
	ID           int       `json:"id" gorm:"primaryKey;autoIncrement"`
	Channel      string    `json:"channel" gorm:"index;size:50;not null"`
	Email        string    `json:"email" gorm:"size:200"`
	Token        string    `json:"token" gorm:"type:text"`
	AccessToken  string    `json:"access_token" gorm:"type:text"`
	RefreshToken string    `json:"refresh_token" gorm:"type:text"`
	IDToken      string    `json:"id_token" gorm:"type:text"`
	Cookie       string    `json:"cookie" gorm:"type:text"`
	SessionKey   string    `json:"session_key" gorm:"type:text"`
	Password     string    `json:"password" gorm:"size:200"`
	ProjectID    string    `json:"project_id" gorm:"size:200"`
	OrgID        string    `json:"org_id" gorm:"size:200"`
	PlanType     string    `json:"plan_type" gorm:"size:50"`
	Pool         string    `json:"pool" gorm:"size:50"`
	Proxy        string    `json:"proxy" gorm:"size:500"`
	Status       string    `json:"status" gorm:"size:20;default:normal"`
	Enabled      bool      `json:"enabled" gorm:"default:true"`
	Nsfw         bool      `json:"nsfw" gorm:"default:false"`
	Tags         string    `json:"tags" gorm:"size:500"`
	ErrorMsg     string    `json:"error_msg" gorm:"type:text"`
	UsageUsed    int       `json:"usage_used" gorm:"default:0"`
	UsageLimit   int       `json:"usage_limit" gorm:"default:0"`
	UsageCount   int       `json:"usage_count" gorm:"default:0"`
	UseCount     int       `json:"use_count" gorm:"default:0"`
	Quota        string    `json:"quota" gorm:"size:100"`
	ResetDate    string    `json:"reset_date" gorm:"size:50"`
	TokenExpiry  string    `json:"token_expiry" gorm:"size:50"`
	LastUsedAt   string    `json:"last_used_at" gorm:"size:50"`
	AuthMethod   string    `json:"auth_method" gorm:"size:20"`
	ClientID     string    `json:"client_id" gorm:"column:client_id;size:200"`
	ClientSecret string    `json:"client_secret" gorm:"type:text"`
	Region       string    `json:"region" gorm:"size:50"`
	StartURL     string    `json:"start_url" gorm:"column:start_url;size:500"`
	CreatedAt    time.Time `json:"created_at" gorm:"autoCreateTime"`
	UpdatedAt    time.Time `json:"updated_at" gorm:"autoUpdateTime"`
}

func (DBChannelAccount) TableName() string {
	return "channel_accounts"
}

// MigrateChannelAccounts auto-migrates the channel_accounts table.
func MigrateChannelAccounts(database *gorm.DB) {
	if err := database.AutoMigrate(&DBChannelAccount{}); err != nil {
		log.Printf("[dao] Failed to migrate channel_accounts: %v", err)
	}
}

// ChannelAccountInsert inserts a new account and returns the auto-generated ID.
func ChannelAccountInsert(acc *DBChannelAccount) error {
	return db.Create(acc).Error
}

// ChannelAccountInsertBatch inserts multiple accounts.
func ChannelAccountInsertBatch(accounts []*DBChannelAccount) error {
	if len(accounts) == 0 {
		return nil
	}
	return db.Create(accounts).Error
}

// ChannelAccountGetAll returns all accounts for a channel.
func ChannelAccountGetAll(channel string) ([]*DBChannelAccount, error) {
	var list []*DBChannelAccount
	err := db.Where("channel = ?", channel).Find(&list).Error
	return list, err
}

// ChannelAccountGetAllChannels returns all accounts across all channels.
func ChannelAccountGetAllChannels() ([]*DBChannelAccount, error) {
	var list []*DBChannelAccount
	err := db.Find(&list).Error
	return list, err
}

// ChannelAccountUpdate updates specific fields of an account by ID.
func ChannelAccountUpdate(id int, fields map[string]interface{}) error {
	return db.Model(&DBChannelAccount{}).Where("id = ?", id).Updates(fields).Error
}

// ChannelAccountDeleteByID deletes an account by ID.
func ChannelAccountDeleteByID(id int) error {
	return db.Delete(&DBChannelAccount{}, id).Error
}

// ChannelAccountDeleteByIDs deletes accounts by IDs.
func ChannelAccountDeleteByIDs(ids []int) error {
	if len(ids) == 0 {
		return nil
	}
	return db.Delete(&DBChannelAccount{}, ids).Error
}

// ChannelAccountDeleteAbnormal deletes all non-normal accounts for a channel.
func ChannelAccountDeleteAbnormal(channel string) (int64, error) {
	result := db.Where("channel = ? AND status != ?", channel, "normal").Delete(&DBChannelAccount{})
	return result.RowsAffected, result.Error
}

// ChannelAccountRecoverAbnormal sets all non-normal accounts back to normal for a channel.
func ChannelAccountRecoverAbnormal(channel string) (int64, error) {
	result := db.Model(&DBChannelAccount{}).
		Where("channel = ? AND status != ?", channel, "normal").
		Updates(map[string]interface{}{"status": "normal", "error_msg": ""})
	return result.RowsAffected, result.Error
}

// ChannelAccountGetMaxID returns the max ID in the table (for sequence init).
func ChannelAccountGetMaxID() (int, error) {
	var maxID int
	err := db.Model(&DBChannelAccount{}).Select("COALESCE(MAX(id), 0)").Scan(&maxID).Error
	return maxID, err
}
