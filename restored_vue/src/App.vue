<script setup lang="ts">
import { ref, computed, onMounted } from 'vue'
import { useRouter, useRoute } from 'vue-router'
import { NConfigProvider, NMessageProvider, NDialogProvider } from 'naive-ui'
import http from './utils/http'
import { isAuthenticated, logout } from './utils/auth'

const router = useRouter()
const route = useRoute()

const sidebarCollapsed = ref(false)

const iconSvgs: Record<string, string> = {
  dashboard: '<rect x="2" y="2" width="6" height="6" rx="1.5" stroke="currentColor" stroke-width="1.4"/><rect x="10" y="2" width="6" height="6" rx="1.5" stroke="currentColor" stroke-width="1.4"/><rect x="2" y="10" width="6" height="6" rx="1.5" stroke="currentColor" stroke-width="1.4"/><rect x="10" y="10" width="6" height="6" rx="1.5" stroke="currentColor" stroke-width="1.4"/>',
  accounts: '<circle cx="9" cy="6" r="3" stroke="currentColor" stroke-width="1.4"/><path d="M3 15.5C3 12.5 5.5 10.5 9 10.5C12.5 10.5 15 12.5 15 15.5" stroke="currentColor" stroke-width="1.4" stroke-linecap="round"/>',
  config: '<circle cx="9" cy="9" r="2.5" stroke="currentColor" stroke-width="1.4"/><path d="M9 2V4M9 14V16M2 9H4M14 9H16M4.2 4.2L5.6 5.6M12.4 12.4L13.8 13.8M13.8 4.2L12.4 5.6M5.6 12.4L4.2 13.8" stroke="currentColor" stroke-width="1.4" stroke-linecap="round"/>',
  models: '<rect x="3" y="2" width="12" height="14" rx="2" stroke="currentColor" stroke-width="1.4"/><path d="M6 6H12M6 9H10M6 12H8" stroke="currentColor" stroke-width="1.4" stroke-linecap="round"/>',
  tutorial: '<path d="M3 3H13C14.1 3 15 3.9 15 5V15L12 13H5C3.9 13 3 12.1 3 11V3Z" stroke="currentColor" stroke-width="1.4" stroke-linejoin="round"/><path d="M6 7H12M6 10H9" stroke="currentColor" stroke-width="1.4" stroke-linecap="round"/>',
}

const menuItems = [
  { key: 'dashboard', label: '仪表盘', path: '/dashboard', icon: 'dashboard' },
  { key: 'accounts', label: '账号管理', path: '/accounts', icon: 'accounts' },
  { key: 'config', label: '配置管理', path: '/config', icon: 'config' },
  { key: 'models', label: '模型管理', path: '/models', icon: 'models' },
  { key: 'tutorial', label: '使用教程', path: '/tutorial', icon: 'tutorial' },
]

const activeMenu = computed(() => {
  const p = route.path
  const item = menuItems.find(m => p.startsWith(m.path))
  return item ? item.key : ''
})

function navigateTo(path: string) {
  router.push(path)
}

function handleLogout() {
  logout()
  router.push('/login')
}

const showUserMenu = ref(false)

function onClickOutsideUserMenu(e: MouseEvent) {
  const el = document.querySelector('.user-menu-wrapper')
  if (el && !el.contains(e.target as Node)) {
    showUserMenu.value = false
  }
}

const version = ref('')
async function fetchVersion() {
  try {
    const res = (await http.get('/api/version')).data
    if (res.code === 0) version.value = res.data?.version || ''
  } catch {}
}

onMounted(() => {
  if (isAuthenticated()) {
    fetchVersion()
  }
  document.addEventListener('click', onClickOutsideUserMenu)
})
</script>

<template>
  <n-config-provider>
    <n-message-provider>
      <n-dialog-provider>
        <div v-if="route.path==='/login'" class="login-wrapper">
          <router-view />
        </div>

        <div v-else class="app-layout">
          <aside :class="['sidebar', sidebarCollapsed ? 'collapsed' : '']">
            <div class="sidebar-header">
              <div class="logo" v-show="!sidebarCollapsed">
                <div class="logo-mark">C</div>
                <div class="logo-info">
                  <span class="logo-text">CodeFreeMax</span>
                  <span v-if="version" class="version-tag">v{{ version }}</span>
                </div>
              </div>
              <button @click="sidebarCollapsed=!sidebarCollapsed" class="collapse-btn" :title="sidebarCollapsed ? '展开' : '收起'">
                <svg width="16" height="16" viewBox="0 0 16 16" fill="none">
                  <path v-if="!sidebarCollapsed" d="M10 12L6 8L10 4" stroke="currentColor" stroke-width="1.5" stroke-linecap="round" stroke-linejoin="round"/>
                  <path v-else d="M6 12L10 8L6 4" stroke="currentColor" stroke-width="1.5" stroke-linecap="round" stroke-linejoin="round"/>
                </svg>
              </button>
            </div>

            <nav class="sidebar-nav">
              <button
                v-for="item in menuItems" :key="item.key"
                @click="navigateTo(item.path)"
                :class="['nav-item', activeMenu===item.key ? 'active' : '']"
                :title="item.label"
              >
                <svg class="nav-svg" width="18" height="18" viewBox="0 0 18 18" fill="none" v-html="iconSvgs[item.icon]"></svg>
                <span v-show="!sidebarCollapsed" class="nav-label">{{ item.label }}</span>
              </button>
            </nav>

          </aside>

          <div class="main-wrapper">
            <header class="top-bar">
              <div></div>
              <div class="user-menu-wrapper">
                <button class="avatar-btn" @click.stop="showUserMenu = !showUserMenu">
                  <div class="avatar">
                    <svg width="16" height="16" viewBox="0 0 16 16" fill="none">
                      <circle cx="8" cy="5.5" r="2.8" stroke="currentColor" stroke-width="1.3"/>
                      <path d="M2.5 14C2.5 11.2 4.7 9.2 8 9.2C11.3 9.2 13.5 11.2 13.5 14" stroke="currentColor" stroke-width="1.3" stroke-linecap="round"/>
                    </svg>
                  </div>
                  <span class="avatar-label">管理员</span>
                  <svg class="chevron" :class="{ open: showUserMenu }" width="12" height="12" viewBox="0 0 12 12" fill="none">
                    <path d="M3 4.5L6 7.5L9 4.5" stroke="currentColor" stroke-width="1.3" stroke-linecap="round" stroke-linejoin="round"/>
                  </svg>
                </button>
                <Transition name="dropdown">
                  <div v-if="showUserMenu" class="user-dropdown">
                    <button class="dropdown-item logout" @click="handleLogout">
                      <svg width="14" height="14" viewBox="0 0 14 14" fill="none">
                        <path d="M5 12H3C2.45 12 2 11.55 2 11V3C2 2.45 2.45 2 3 2H5" stroke="currentColor" stroke-width="1.2" stroke-linecap="round"/>
                        <path d="M9.5 9.5L12 7L9.5 4.5M5.5 7H11.5" stroke="currentColor" stroke-width="1.2" stroke-linecap="round" stroke-linejoin="round"/>
                      </svg>
                      退出登录
                    </button>
                  </div>
                </Transition>
              </div>
            </header>
            <main class="main-content">
              <router-view />
            </main>
          </div>
        </div>
      </n-dialog-provider>
    </n-message-provider>
  </n-config-provider>
</template>

<style>
:root {
  --sidebar-width: 216px;
  --sidebar-collapsed-width: 56px;
  --primary-color: #5b6abf;
  --primary-color-hover: rgba(91,106,191,0.08);
  --primary-color-light: rgba(91,106,191,0.12);
  --bg-color: #f8f9fb;
  --card-color: #ffffff;
  --border-color: #eaedf0;
  --text-color: #1a1d21;
  --text-color-2: #5f6368;
  --text-color-3: #9aa0a6;
  --hover-color: #f3f4f7;
  --body-color: #f3f4f7;
  --error-color: #d93025;
  --success-color: #188038;
  --radius: 8px;
}
* { margin: 0; padding: 0; box-sizing: border-box; }
body {
  font-family: 'Inter', 'Noto Sans SC', 'PingFang SC', 'Microsoft YaHei', -apple-system, BlinkMacSystemFont, 'Segoe UI', sans-serif;
  background: var(--bg-color);
  color: var(--text-color);
  -webkit-font-smoothing: antialiased;
  -moz-osx-font-smoothing: grayscale;
  font-feature-settings: 'cv02', 'cv03', 'cv04', 'cv11';
}
</style>

<style scoped>
.login-wrapper { min-height: 100vh; display: flex; align-items: center; justify-content: center; background: var(--bg-color); }
.app-layout { display: flex; min-height: 100vh; background: var(--bg-color); }

.sidebar {
  width: var(--sidebar-width);
  background: var(--card-color);
  border-right: 1px solid var(--border-color);
  display: flex; flex-direction: column;
  transition: width .2s cubic-bezier(.4,0,.2,1);
  flex-shrink: 0; height: 100vh; position: sticky; top: 0;
}
.sidebar.collapsed { width: var(--sidebar-collapsed-width); }

.sidebar-header {
  display: flex; align-items: center; justify-content: space-between;
  padding: 16px 12px; border-bottom: 1px solid var(--border-color); min-height: 56px;
}
.logo { display: flex; align-items: center; gap: 10px; }
.logo-mark {
  width: 28px; height: 28px;
  background: var(--primary-color); color: #fff;
  border-radius: 7px;
  display: flex; align-items: center; justify-content: center;
  font-size: 14px; font-weight: 700; letter-spacing: -0.5px;
}
.logo-info { display: flex; flex-direction: column; }
.logo-text { font-size: 14px; font-weight: 600; color: var(--text-color); letter-spacing: -0.3px; }
.version-tag { font-size: 10px; color: var(--text-color-3); margin-top: 1px; }

.collapse-btn {
  background: none; border: none; cursor: pointer;
  color: var(--text-color-3); padding: 4px; border-radius: 6px;
  display: flex; align-items: center; justify-content: center;
  transition: all .15s;
}
.collapse-btn:hover { background: var(--hover-color); color: var(--text-color-2); }

.sidebar-nav {
  flex: 1; padding: 8px; display: flex; flex-direction: column; gap: 1px; overflow-y: auto;
}
.nav-item {
  display: flex; align-items: center; gap: 10px;
  padding: 8px 10px; border-radius: 7px;
  border: none; background: transparent; cursor: pointer;
  color: var(--text-color-2); font-size: 13px; font-weight: 500;
  transition: all .12s; text-align: left; width: 100%;
}
.nav-item:hover { background: var(--hover-color); color: var(--text-color); }
.nav-item.active {
  background: var(--primary-color-light);
  color: var(--primary-color); font-weight: 600;
}
.nav-svg { flex-shrink: 0; }
.nav-label { white-space: nowrap; overflow: hidden; }

.main-wrapper { flex: 1; display: flex; flex-direction: column; min-width: 0; }

.top-bar {
  display: flex; align-items: center; justify-content: space-between;
  padding: 0 24px; height: 52px; flex-shrink: 0;
  background: var(--card-color);
  border-bottom: 1px solid var(--border-color);
}

.user-menu-wrapper { position: relative; }

.avatar-btn {
  display: flex; align-items: center; gap: 8px;
  padding: 5px 10px 5px 5px; border-radius: 8px;
  border: 1px solid var(--border-color); background: var(--card-color);
  cursor: pointer; transition: all .15s; color: var(--text-color-2);
}
.avatar-btn:hover { background: var(--hover-color); border-color: var(--text-color-3); }

.avatar {
  width: 28px; height: 28px; border-radius: 50%;
  background: var(--primary-color-light); color: var(--primary-color);
  display: flex; align-items: center; justify-content: center;
}

.avatar-label { font-size: 13px; font-weight: 500; color: var(--text-color); }

.chevron { transition: transform .2s; color: var(--text-color-3); }
.chevron.open { transform: rotate(180deg); }

.user-dropdown {
  position: absolute; right: 0; top: calc(100% + 6px);
  background: var(--card-color); border: 1px solid var(--border-color);
  border-radius: 8px; padding: 4px; min-width: 140px;
  box-shadow: 0 4px 16px rgba(0,0,0,.08);
  z-index: 100;
}

.dropdown-item {
  display: flex; align-items: center; gap: 8px;
  width: 100%; padding: 8px 12px; border: none; background: none;
  border-radius: 6px; cursor: pointer;
  font-size: 13px; color: var(--text-color-2); transition: all .12s;
}
.dropdown-item:hover { background: var(--hover-color); }
.dropdown-item.logout:hover { background: rgba(217,48,37,.06); color: var(--error-color); }

.dropdown-enter-active { transition: all .15s ease-out; }
.dropdown-leave-active { transition: all .1s ease-in; }
.dropdown-enter-from, .dropdown-leave-to { opacity: 0; transform: translateY(-4px); }

.main-content { flex: 1; overflow: auto; min-width: 0; }
</style>
