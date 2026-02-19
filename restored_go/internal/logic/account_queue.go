package logic

import (
	"context"
	"fmt"
	"log"
	"strconv"

	"kiro2api/internal/dao"

	"github.com/redis/go-redis/v9"
)

// AccountQueueManager manages Redis-based account queues for round-robin
// account selection across all channels.
type AccountQueueManager struct {
	RedisClient *redis.Client
}

// channelQueueKey maps channel names to their Redis queue key names.
// Decoded from hex string comparisons in the binary:
//   "warp"        (0x70726177) -> "account_queue:warp"                len 0x1b = 27
//   "cursor"      (0x73727563 + 0x726f) -> "account_queue:cursor"    len 0x1d = 29
//   "orchids"     (0x6863726f + 0x6469 + 's') -> "account_queue:orchids" len 0x1e = 30
//   "grok:pro"    (0x6f72703a6b6f7267) -> "account_queue:grok:pro"   len 0x1f = 31
//   "kiro:pro"    (0x6f72703a6f72696b) -> "account_queue:kiro:pro"   len 0x1f = 31
//   "grok:free"   (0x6572663a6b6f7267 + 'e') -> "account_queue:grok:free" len 0x20 = 32
//   "kiro:free"   (0x6572663a6f72696b + 'e') -> "account_queue:kiro:free" len 0x20 = 32
//   "kiro:plus"   (0x756c703a6f72696b + 's') -> "account_queue:kiro:plus" len 0x20 = 32
//   "claude_api"  (0x615f656475616c63 + 0x6970) -> "account_queue:claude_api" len 0x21 = 33
//   "kiro:ultra"  (0x746c753a6f72696b + 0x6172) -> "account_queue:kiro:ultra" len 0x21 = 33
//   "antigravity" (0x7661726769746e61 + 0x7469 + 'y') -> "account_queue:antigravity" len 0x22 = 34
func channelQueueKey(channel string) string {
	return "account_queue:" + channel
}

// InitializeQueue initializes the Redis account queue for a given channel.
// It fetches all normal accounts from the database, filters out already-queued
// account IDs, and pushes new ones into the Redis list.
//
// The channel parameter supports sub-channels like "kiro:pro", "kiro:free",
// "kiro:plus", "kiro:ultra", "grok:pro", "grok:free".
func (m *AccountQueueManager) InitializeQueue(ctx context.Context, channel string) error {
	queueKey := channelQueueKey(channel)

	// Step 1: Create a Redis list subscription to track queue operations
	// Build log fields for structured logging
	logFields := []interface{}{
		"channel", channel,
		"action", "initialize",
		"queue_key", queueKey,
		"status", "starting",
	}

	// Subscribe to list operations (BLPOP pattern with timeout)
	subCmd := m.RedisClient.BLPop(ctx, 0, queueKey)
	existingIDs := subCmd.Val()
	existingCount := len(existingIDs)

	_ = logFields

	// Step 2: Parse existing IDs into a set for O(1) lookup
	existingSet := make(map[uint64]bool)
	for _, idStr := range existingIDs {
		id, err := strconv.ParseUint(idStr, 10, 64)
		if err == nil {
			existingSet[id] = true
		}
	}

	// Step 3: Fetch accounts based on channel type and filter
	accountIDs, err := m.fetchAccountIDsForChannel(ctx, channel)
	if err != nil {
		return fmt.Errorf("fetch accounts for channel %s failed: %w", channel, err)
	}

	// Step 4: Filter out already-queued accounts, collect new IDs to push
	var newIDs []interface{}
	for _, id := range accountIDs {
		if !existingSet[id] {
			newIDs = append(newIDs, id)
		}
	}

	// Step 5: Remove stale IDs (in queue but no longer in DB)
	removedCount := 0
	for existingID := range existingSet {
		found := false
		for _, id := range accountIDs {
			if id == existingID {
				found = true
				break
			}
		}
		if !found {
			// Remove from queue via LREM
			m.RedisClient.LRem(ctx, queueKey, 0, existingID)
			removedCount++
		}
	}

	if removedCount > 0 {
		log.Printf("[AccountQueue] %s: removed %d stale accounts from queue", channel, removedCount)
	}

	// Step 6: Push new account IDs to the queue
	if len(newIDs) > 0 {
		// Convert to string interface slice for RPush
		pushArgs := make([]interface{}, len(newIDs))
		for i, id := range newIDs {
			pushArgs[i] = fmt.Sprintf("%d", id)
		}

		cmd := m.RedisClient.RPush(ctx, queueKey, pushArgs...)
		if cmd.Err() != nil {
			return fmt.Errorf("RPush to %s failed: %w", queueKey, cmd.Err())
		}

		log.Printf("[AccountQueue] %s: pushed %d new accounts to queue", channel, len(newIDs))
	}

	// Step 7: Set queue length via LLEN for monitoring
	queueLen := m.RedisClient.LLen(ctx, queueKey).Val()
	log.Printf("[AccountQueue] %s: queue initialized, total=%d, existing=%d, new=%d",
		channel, queueLen, existingCount, len(newIDs))

	return nil
}

// fetchAccountIDsForChannel returns account IDs for the given channel,
// applying sub-channel filters (pro/free/plus/ultra) where applicable.
func (m *AccountQueueManager) fetchAccountIDsForChannel(ctx context.Context, channel string) ([]uint64, error) {
	switch channel {
	case "warp":
		accounts, err := dao.WarpAccountDaoGetAllNormal()
		if err != nil {
			return nil, err
		}
		ids := make([]uint64, len(accounts))
		for i, a := range accounts {
			ids[i] = uint64(a.ID)
		}
		return ids, nil

	case "cursor":
		// Cursor doesn't use account queue (returns empty)
		return nil, nil

	case "grok", "kiro":
		// Plain grok/kiro without sub-channel — return empty
		return nil, nil

	case "orchids":
		accounts, err := dao.OrchidsAccountDaoGetAllNormal()
		if err != nil {
			return nil, err
		}
		ids := make([]uint64, len(accounts))
		for i, a := range accounts {
			ids[i] = uint64(a.ID)
		}
		return ids, nil

	case "grok:pro":
		// Grok pro accounts: filter by account_type == "pro" (len 3, 0x7270 + 'o')
		accounts, err := dao.GrokAccountDaoGetAllNormal()
		if err != nil {
			return nil, err
		}
		var ids []uint64
		for _, a := range accounts {
			if a.AccountType == "pro" {
				ids = append(ids, uint64(a.ID))
			}
		}
		return ids, nil

	case "kiro:pro":
		// Kiro pro accounts: filter by account_type == "pro"
		accounts, err := dao.AccountDaoGetAllNormal()
		if err != nil {
			return nil, err
		}
		var ids []uint64
		for _, a := range accounts {
			if a.AccountType == "pro" {
				ids = append(ids, uint64(a.ID))
			}
		}
		return ids, nil

	case "grok:free":
		// Grok free accounts: filter by account_type == "free" (len 4, 0x65657266)
		accounts, err := dao.GrokAccountDaoGetAllNormal()
		if err != nil {
			return nil, err
		}
		var ids []uint64
		for _, a := range accounts {
			if a.AccountType == "free" {
				ids = append(ids, uint64(a.ID))
			}
		}
		return ids, nil

	case "kiro:free":
		// Kiro free accounts: filter by account_type == "free"
		accounts, err := dao.AccountDaoGetAllNormal()
		if err != nil {
			return nil, err
		}
		var ids []uint64
		for _, a := range accounts {
			if a.AccountType == "free" {
				ids = append(ids, uint64(a.ID))
			}
		}
		return ids, nil

	case "kiro:plus":
		// Kiro plus accounts: filter by account_type == "plus" (len 4, 0x73756c70)
		accounts, err := dao.AccountDaoGetAllNormal()
		if err != nil {
			return nil, err
		}
		var ids []uint64
		for _, a := range accounts {
			if a.AccountType == "plus" {
				ids = append(ids, uint64(a.ID))
			}
		}
		return ids, nil

	case "claude_api":
		accounts, err := dao.ClaudeApiAccountDaoGetAllNormal()
		if err != nil {
			return nil, err
		}
		ids := make([]uint64, len(accounts))
		for i, a := range accounts {
			ids[i] = uint64(a.ID)
		}
		return ids, nil

	case "kiro:ultra":
		// Kiro ultra accounts: filter by account_type == "ultra" (len 5, 0x72746c75 + 'a')
		accounts, err := dao.AccountDaoGetAllNormal()
		if err != nil {
			return nil, err
		}
		var ids []uint64
		for _, a := range accounts {
			if a.AccountType == "ultra" {
				ids = append(ids, uint64(a.ID))
			}
		}
		return ids, nil

	case "antigravity":
		accounts, err := dao.AntigravityAccountDaoGetAllNormal()
		if err != nil {
			return nil, err
		}
		ids := make([]uint64, len(accounts))
		for i, a := range accounts {
			ids[i] = uint64(a.ID)
		}
		return ids, nil

	default:
		return nil, fmt.Errorf("unsupported channel: %s", channel)
	}
}
