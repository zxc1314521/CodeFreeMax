package claudeapi

import (
	"log"
	"sync"

	"kiro2api/internal/logic"
)

// init.0 is the package-level initialization function.
// Symbol: kiro2api/internal/logic/claudeapi.init.0 (96B @ 0x13906a0)
//
// The tiny size (96B) indicates it just registers the service singleton
// or sets a package-level variable.
func init() {
	log.Println("[claudeapi] package initialized")
}

// GetConcurrencyManager returns the global AccountConcurrencyManager
// for Claude API account slot allocation.
// Referenced in Messages handler at: kiro2api_internal_logic_GetConcurrencyManager
var (
	concurrencyMgr     *logic.AccountConcurrencyManager
	concurrencyMgrOnce sync.Once
)

func GetConcurrencyManager() *logic.AccountConcurrencyManager {
	concurrencyMgrOnce.Do(func() {
		concurrencyMgr = logic.NewAccountConcurrencyManager("claude_api")
	})
	return concurrencyMgr
}
