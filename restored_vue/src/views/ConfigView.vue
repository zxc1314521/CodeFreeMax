<script setup lang="ts">
import { ref, computed, watch, onMounted } from 'vue'
import { useMessage, NSpin, NInput, NSelect, NSwitch, NInputNumber, NFormItem, NTag, NProgress, NModal, NPagination } from 'naive-ui'
import { Eye, EyeOff, CopyOutline } from '@vicons/ionicons5'
import http from '../utils/http'
import { enabledChannelOptions, CHANNELS } from '../stores/channels'

const message = useMessage()

// ===== 基础配置 =====
const config = ref({
  api_key: '',
  proxy_url: '',
  max_retries: '3',
  retry_delay: '1000',
  credential_retries: '5',
  request_timeout: '120',
  auto_refresh_token: 'true',
  refresh_interval: '30',
  admin_password: '',
  enable_token_refresh: 'false',
  enable_usage_refresh: 'false',
  enable_token_count: 'true',
  enable_token_cache: 'true',
  token_cache_ttl: '300',
  token_cache_strategy: '1',
  kiro_proxy_url: '',
  orchids_proxy_url: '',
  antigravity_proxy_url: '',
  warp_proxy_url: '',
  kiro_use_builtin_proxy: 'false',
  warp_use_builtin_proxy: 'false',
  orchids_use_builtin_proxy: 'false',
  antigravity_use_builtin_proxy: 'false',
  warp_credit_refund: 'false',
  enable_context_compress: 'true'
})

const configLoading = ref(false)
const saving = ref(false)
const showApiKey = ref(false)
const showPassword = ref(false)
const activeTab = ref('basic')

async function fetchConfig() {
  configLoading.value = true
  try {
    const res = (await http.get('/api/config/list')).data
    if (res.code === 0) {
      config.value = { ...config.value, ...res.data }
    }
  } catch (e) {
    console.error('获取配置失败:', e)
  } finally {
    configLoading.value = false
  }
}

async function saveConfig() {
  saving.value = true
  try {
    const res = (await http.post('/api/config/save', config.value)).data
    if (res.code === 0) message.success('保存成功')
    else message.error(res.message || res.msg || '保存失败')
  } catch {
    message.error('系统错误')
  } finally {
    saving.value = false
  }
}

function copyApiKey() {
  navigator.clipboard.writeText(config.value.api_key)
  message.success('已复制到剪贴板')
}

// ===== 授权配置 =====
const licenseKey = ref('')
const authorizedChannels = ref<string[]>([])
const licenseLoading = ref(false)
const licenseVerifying = ref(false)
const builtinProxyConfigs = ref<any[]>([])
const licenseUsage = ref({ current: 0, limit: 0, remaining: 0, percent: 0 })

async function fetchLicenseStatus() {
  licenseLoading.value = true
  try {
    const res = (await http.get('/api/license/status')).data
    if (res.code === 0) {
      licenseKey.value = res.data.key || ''
      authorizedChannels.value = res.data.authorized_channels || []
      builtinProxyConfigs.value = res.data.builtin_proxy_configs || []
    }
    const usageRes = await http.get('/api/license/usage')
    if (usageRes.data.code === 0) {
      licenseUsage.value = usageRes.data.data
    }
  } catch (e) {
    console.error('Failed to fetch license status:', e)
  } finally {
    licenseLoading.value = false
  }
}

async function saveLicense() {
  if (!licenseKey.value.trim()) {
    message.warning('请输入授权码')
    return
  }
  licenseVerifying.value = true
  try {
    const res = (await http.post('/api/license/save', { key: licenseKey.value })).data
    if (res.code === 0) {
      authorizedChannels.value = res.data?.authorized_channels || []
      message.success('授权验证成功，已授权渠道: ' + authorizedChannels.value.join(', '))
    } else {
      authorizedChannels.value = res.data?.authorized_channels || []
      message.error(res.message || res.msg || '授权验证失败')
    }
  } catch (e: any) {
    authorizedChannels.value = []
    message.error(e.message || '授权验证失败')
  } finally {
    licenseVerifying.value = false
  }
}

// ===== 代理配置 =====
const proxyChannel = ref('kiro')

const proxyUrlKey = computed(() => {
  const m = proxyChannel.value
  if (m === 'kiro') return 'kiro_proxy_url'
  if (m === 'orchids') return 'orchids_proxy_url'
  if (m === 'antigravity') return 'antigravity_proxy_url'
  if (m === 'cursor') return 'cursor_proxy_url'
  if (m === 'warp') return 'warp_proxy_url'
  if (m === 'grok') return 'grok_proxy_url'
  return 'proxy_url'
})

const builtinProxyKey = computed(() => {
  const m = proxyChannel.value
  if (m === 'kiro') return 'kiro_use_builtin_proxy'
  if (m === 'orchids') return 'orchids_use_builtin_proxy'
  if (m === 'antigravity') return 'antigravity_use_builtin_proxy'
  if (m === 'warp') return 'warp_use_builtin_proxy'
  return ''
})

const proxyUrl = computed({
  get: () => (config.value as any)[proxyUrlKey.value] || '',
  set: (v: string) => { (config.value as any)[proxyUrlKey.value] = v }
})

const useBuiltinProxy = computed({
  get: () => {
    const k = builtinProxyKey.value
    return k ? (config.value as any)[k] === 'true' : false
  },
  set: (v: boolean) => {
    const k = builtinProxyKey.value
    if (k) (config.value as any)[k] = v ? 'true' : 'false'
  }
})

const currentBuiltinProxy = computed(() => {
  const m = proxyChannel.value
  return builtinProxyConfigs.value.find((c: any) => c.channel === m) || { channel: m, enabled: false, available: false }
})

// ===== Token缓存 =====
const ttlOptions = [
  { label: '1 分钟', value: '60' },
  { label: '5 分钟', value: '300' },
  { label: '15 分钟', value: '900' },
  { label: '30 分钟', value: '1800' },
  { label: '1 小时', value: '3600' },
  { label: '1 天', value: '86400' },
  { label: '3 天', value: '259200' },
  { label: '1 周', value: '604800' },
  { label: '自定义', value: 'custom' }
]

const cacheStrategyOptions = [
  { label: '完整匹配 (System + Tools)', value: '0' },
  { label: '分离缓存 (推荐)', value: '1' },
  { label: '仅缓存 System', value: '2' },
  { label: '仅缓存 Tools', value: '3' }
]

const customTtl = ref(300)
const isCustomTtl = ref(false)

const selectedTtl = computed({
  get: () => {
    if (isCustomTtl.value) return 'custom'
    const v = config.value.token_cache_ttl
    const found = ttlOptions.find(o => o.value === v && o.value !== 'custom')
    if (found) return v
    customTtl.value = parseInt(v) || 300
    isCustomTtl.value = true
    return 'custom'
  },
  set: (v: string) => {
    if (v === 'custom') {
      isCustomTtl.value = true
      config.value.token_cache_ttl = String(customTtl.value)
    } else {
      isCustomTtl.value = false
      config.value.token_cache_ttl = v
    }
  }
})

watch(customTtl, (v) => {
  if (selectedTtl.value === 'custom') config.value.token_cache_ttl = String(v)
})

const effectiveTtl = computed(() =>
  selectedTtl.value === 'custom' ? customTtl.value || 300 : parseInt(config.value.token_cache_ttl) || 300
)

const formatTime = (s: number) =>
  s >= 86400 ? `${(s / 86400).toFixed(1).replace(/\.0$/, '')}天`
  : s >= 3600 ? `${(s / 3600).toFixed(1).replace(/\.0$/, '')}小时`
  : s >= 60 ? `${(s / 60).toFixed(0)}分钟`
  : `${s}秒`

const formatMemory = (kb: number) => kb >= 1024 ? `${(kb / 1024).toFixed(1)}MB` : `${kb.toFixed(1)}KB`

const cacheMult = computed(() => config.value.token_cache_strategy === '1' ? 2 : 1)

const cacheEstimate = computed(() => {
  const ttl = effectiveTtl.value
  const mult = cacheMult.value
  const ttlText = formatTime(ttl)
  const calc = (qps: number) => formatMemory(qps * ttl * 0.5 * mult)
  return {
    ttl, ttlText, mult,
    low: { qps: 10, memory: calc(10) },
    mid: { qps: 50, memory: calc(50) },
    high: { qps: 100, memory: calc(100) }
  }
})

const cacheStats = ref({ key_count: 0, memory_used: 0, memory_used_str: '0 B', connected: false })
const cacheStatsLoading = ref(false)
const cacheClearLoading = ref(false)

async function fetchCacheStats() {
  cacheStatsLoading.value = true
  try {
    const res = await http.get('/api/token-cache/stats')
    if (res.data.code === 0) cacheStats.value = res.data.data
  } catch (e) {
    console.error('Failed to fetch cache stats:', e)
  } finally {
    cacheStatsLoading.value = false
  }
}

async function clearCache() {
  cacheClearLoading.value = true
  try {
    const res = await http.post('/api/token-cache/clear')
    if (res.data.code === 0) {
      message.success(`已清空 ${res.data.data.deleted} 条缓存`)
      await fetchCacheStats()
    } else {
      message.error(res.data.msg || '清空失败')
    }
  } catch (e: any) {
    message.error(e.message || '清空失败')
  } finally {
    cacheClearLoading.value = false
  }
}

// ===== 渠道配置 =====
const channelTab = ref('kiro')
const channelTabOptions = [
  { label: 'Kiro', value: 'kiro' },
  { label: 'Warp', value: 'warp' },
  { label: 'Grok', value: 'grok' }
]

// Kiro 模型队列
const kiroQueueConfig = ref<{ model: string; queues: string[] }[]>([])
const kiroQueueLoading = ref(false)
const kiroQueueSaving = ref(false)
const kiroQueueOptions = [
  { label: 'Ultra', value: 'ultra' },
  { label: 'Plus', value: 'plus' },
  { label: 'Pro', value: 'pro' },
  { label: 'Free', value: 'free' }
]
const kiroModelOptions = [
  { label: 'claude-opus-*', value: 'claude-opus-' },
  { label: 'claude-sonnet-*', value: 'claude-sonnet-' },
  { label: 'claude-haiku-*', value: 'claude-haiku-' },
  { label: '其它模型', value: 'default' }
]

const getModelQueues = (model: string) => kiroQueueConfig.value.find(c => c.model === model)?.queues || []
const setModelQueues = (model: string, queues: string[]) => {
  const idx = kiroQueueConfig.value.findIndex(c => c.model === model)
  if (queues.length === 0) {
    if (idx !== -1) kiroQueueConfig.value.splice(idx, 1)
  } else if (idx !== -1) {
    kiroQueueConfig.value[idx].queues = queues
  } else {
    kiroQueueConfig.value.push({ model, queues })
  }
}

async function fetchKiroConfig() {
  kiroQueueLoading.value = true
  try {
    const res = await http.get('/api/kiro/model-queue-config')
    if (res.data.code === 0 && res.data.data) {
      kiroQueueConfig.value = Object.entries(res.data.data).map(([model, queues]) => ({
        model, queues: queues as string[]
      }))
    }
  } catch (e) {
    console.error('Failed to fetch kiro config:', e)
  } finally {
    kiroQueueLoading.value = false
  }
}

async function saveKiroConfig() {
  kiroQueueSaving.value = true
  try {
    const data: Record<string, string[]> = {}
    for (const item of kiroQueueConfig.value) {
      if (item.model && item.queues.length > 0) data[item.model] = item.queues
    }
    const res = await http.post('/api/kiro/model-queue-config', data)
    if (res.data.code === 0) message.success('Kiro 模型队列配置保存成功')
    else message.error(res.data.msg || '保存失败')
  } catch (e: any) {
    message.error(e.message || '保存失败')
  } finally {
    kiroQueueSaving.value = false
  }
}

// ===== Grok 配置 =====
const grokConfig = ref({
  temporary: true,
  stream: true,
  thinking: false,
  timeout: 120,
  cf_clearance: '',
  app_url: '',
  image_format: 'url',
  video_format: 'url',
  nsfw_max_concurrent: 10,
  nsfw_batch_size: 50,
  assets_max_concurrent: 25,
  media_max_concurrent: 50,
  cache_enable_auto_clean: true,
  cache_limit_mb: 1024,
  nsfw_enabled: false,
  media_allow_exhaust: true
})

const currentOrigin = computed(() => window.location.origin)
const grokLoading = ref(false)
const grokSaving = ref(false)
const nsfwBatchLoading = ref(false)
const nsfwProgress = ref({ show: false, current: 0, total: 0, success: 0, failed: 0, action: '开启' })

async function fetchGrokConfig() {
  grokLoading.value = true
  try {
    const res = await http.get('/api/grok/config')
    if (res.data.code === 0 && res.data.data) Object.assign(grokConfig.value, res.data.data)
  } catch (e) {
    console.error('Failed to fetch grok config:', e)
  } finally {
    grokLoading.value = false
  }
}

async function saveGrokConfig() {
  grokSaving.value = true
  try {
    const res = await http.post('/api/grok/config/save', grokConfig.value)
    if (res.data.code === 0) message.success('Grok 配置保存成功')
    else message.error(res.data.msg || '保存失败')
  } catch (e: any) {
    message.error(e.message || '保存失败')
  } finally {
    grokSaving.value = false
  }
}

async function nsfwBatchToggle(enabled: boolean) {
  nsfwBatchLoading.value = true
  nsfwProgress.value = { show: true, current: 0, total: 0, success: 0, failed: 0, action: enabled ? '开启' : '关闭' }
  let done = false
  let finalEnabled = enabled
  try {
    const token = localStorage.getItem('auth_token')
    const headers: Record<string, string> = { 'Content-Type': 'application/json' }
    if (token) headers['X-Auth-Token'] = token
    const resp = await fetch('/api/grok/account/nsfw-batch', {
      method: 'POST', headers, body: JSON.stringify({ enabled })
    })
    if (!resp.ok || !resp.body) throw new Error(`请求失败 (${resp.status})`)
    const reader = resp.body.getReader()
    const decoder = new TextDecoder()
    let buffer = ''
    while (true) {
      const { done: isDone, value } = await reader.read()
      if (isDone) break
      buffer += decoder.decode(value, { stream: true })
      const lines = buffer.split('\n')
      buffer = lines.pop() || ''
      let eventType = ''
      for (const line of lines) {
        if (line.startsWith('event: ')) eventType = line.slice(7)
        else if (line.startsWith('data: ')) {
          const data = JSON.parse(line.slice(6))
          if (eventType === 'progress') {
            nsfwProgress.value = { ...nsfwProgress.value, show: true, current: data.current, total: data.total, success: data.success, failed: data.failed }
          } else if (eventType === 'done') {
            done = true
            if (typeof data.enabled === 'boolean') finalEnabled = data.enabled
            message.success(`NSFW 批量${enabled ? '开启' : '关闭'}完成：成功 ${data.success} 个，失败 ${data.failed} 个`)
          } else if (eventType === 'error') {
            throw new Error(data.message || '批量切换失败')
          }
        }
      }
    }
  } catch (e: any) {
    message.error(e.message || `NSFW 批量${enabled ? '开启' : '关闭'}失败`)
  } finally {
    nsfwBatchLoading.value = false
    setTimeout(() => { nsfwProgress.value.show = false }, 1000)
  }
  if (done) grokConfig.value.nsfw_enabled = finalEnabled
  return done
}

async function handleNsfwToggle(enabled: boolean) {
  if (!nsfwBatchLoading.value) await nsfwBatchToggle(enabled)
}

async function clearAssetsBatch() {
  try {
    const res = await http.post('/api/grok/account/clear-assets-batch', {})
    if (res.data.code === 0) message.success(`已清理 ${res.data.data?.cleared || 0} 个账号的资源缓存`)
    else message.error(res.data.msg || '清理失败')
  } catch (e: any) {
    message.error(e.message || '清理失败')
  }
}

// Grok 缓存管理
const grokCacheStats = ref({ local_image: { count: 0, size_mb: 0 }, local_video: { count: 0, size_mb: 0 } })
const grokCacheLoading = ref(false)
const imageClearing = ref(false)
const videoClearing = ref(false)
const cacheFiles = ref<any[]>([])
const cacheFilesTotal = ref(0)
const cacheFilesPage = ref(1)
const cacheFilesPageSize = ref(20)
const cacheFileType = ref('image')
const cacheFilesLoading = ref(false)
const showCacheDialog = ref(false)
const previewUrl = ref('')
const previewType = ref('image')
const showPreview = ref(false)

async function fetchGrokCacheStats() {
  grokCacheLoading.value = true
  try {
    const res = await http.get('/api/grok/cache/stats')
    if (res.data.code === 0 && res.data.data) {
      const d = res.data.data
      grokCacheStats.value = {
        local_image: { count: 0, size_mb: 0, ...d.local_image },
        local_video: { count: 0, size_mb: 0, ...d.local_video },
      }
    }
  } catch (e) {
    console.error('Failed to fetch grok cache stats:', e)
  } finally {
    grokCacheLoading.value = false
  }
}

async function fetchCacheFiles() {
  cacheFilesLoading.value = true
  try {
    const res = await http.get('/api/grok/cache/list', {
      params: { type: cacheFileType.value, page: cacheFilesPage.value, page_size: cacheFilesPageSize.value }
    })
    if (res.data.code === 0 && res.data.data) {
      cacheFiles.value = res.data.data.items || []
      cacheFilesTotal.value = res.data.data.total || 0
    }
  } catch (e) {
    console.error('Failed to fetch grok cache files:', e)
  } finally {
    cacheFilesLoading.value = false
  }
}

function openCacheList(type: string) {
  cacheFileType.value = type
  cacheFilesPage.value = 1
  showCacheDialog.value = true
  fetchCacheFiles()
}

function previewFile(file: any) {
  const url = cacheFileType.value === 'video' && file.preview_url ? file.preview_url : file.view_url
  if (!url) return
  const full = url.startsWith('http') ? url : (grokConfig.value.app_url || '') + url
  previewUrl.value = full
  previewType.value = cacheFileType.value
  showPreview.value = true
}

async function deleteCacheFile(name: string) {
  try {
    const res = await http.post('/api/grok/cache/delete', { type: cacheFileType.value, name })
    if (res.data.code === 0 && res.data.data?.deleted) {
      message.success('删除成功')
      await fetchCacheFiles()
      await fetchGrokCacheStats()
    } else {
      message.error(res.data.msg || '删除失败')
    }
  } catch (e: any) {
    message.error(e.message || '删除失败')
  }
}

async function clearGrokCache(type: string) {
  if (type === 'image') imageClearing.value = true
  else videoClearing.value = true
  try {
    const res = await http.post('/api/grok/cache/clear', { type })
    if (res.data.code === 0) {
      const d = res.data.data || {}
      message.success(`已清理 ${d.count || 0} 个${type === 'image' ? '图片' : '视频'} (${(d.size_mb || 0).toFixed(2)} MB)`)
      await fetchGrokCacheStats()
      if (showCacheDialog.value && cacheFileType.value === type) await fetchCacheFiles()
    } else {
      message.error(res.data.msg || '清理失败')
    }
  } catch (e: any) {
    message.error(e.message || '清理失败')
  } finally {
    if (type === 'image') imageClearing.value = false
    else videoClearing.value = false
  }
}

const formatFileSize = (bytes: number) =>
  bytes < 1024 ? bytes + ' B'
  : bytes < 1024 * 1024 ? (bytes / 1024).toFixed(1) + ' KB'
  : (bytes / 1024 / 1024).toFixed(2) + ' MB'

const formatDate = (ms: number) =>
  new Date(ms).toLocaleString('zh-CN', { timeZone: 'Asia/Shanghai' })

onMounted(() => {
  fetchConfig()
  fetchLicenseStatus()
  fetchCacheStats()
  fetchKiroConfig()
  fetchGrokConfig()
  fetchGrokCacheStats()
})
</script>

<template>
  <div class="config-view">
    <div class="page-header">
      <h1>配置管理</h1>
      <p>管理系统基础配置、负载均衡、授权等设置</p>
    </div>
    <n-spin :show="configLoading">
      <div class="tab-bar">
        <button v-for="tab in [{key:'basic',name:'基础配置'},{key:'license',name:'授权配置'},{key:'proxy',name:'代理配置'},{key:'channel',name:'渠道配置'}]" :key="tab.key" @click="activeTab=tab.key" :class="['tab-btn', activeTab===tab.key ? 'active' : '']">{{ tab.name }}</button>
      </div>
      <!-- 基础配置 -->
      <div v-show="activeTab==='basic'" class="tab-panel">
        <div class="config-section">
          <h3>管理员密码</h3>
          <div class="input-row">
            <n-input v-model:value="config.admin_password" :type="showPassword?'text':'password'" placeholder="设置管理后台登录密码" />
            <button @click="showPassword=!showPassword" class="icon-btn">{{ showPassword ? '隐藏' : '显示' }}</button>
          </div>
          <p class="hint">用于管理后台登录认证，修改后需要重新登录</p>
        </div>
        <div class="config-section">
          <h3>API密钥</h3>
          <div class="input-row">
            <n-input v-model:value="config.api_key" :type="showApiKey?'text':'password'" placeholder="设置API访问密钥" />
            <button @click="showApiKey=!showApiKey" class="icon-btn">{{ showApiKey ? '隐藏' : '显示' }}</button>
            <button @click="copyApiKey" class="icon-btn">复制</button>
          </div>
          <p class="hint">用于API接口认证，留空则不启用认证</p>
        </div>
        <div class="config-section">
          <h3>重试配置</h3>
          <div class="form-grid-3">
            <n-form-item label="最大重试次数"><n-input v-model:value="config.max_retries" placeholder="3" /></n-form-item>
            <n-form-item label="重试延迟(ms)"><n-input v-model:value="config.retry_delay" placeholder="1000" /></n-form-item>
            <n-form-item label="凭证切换次数"><n-input v-model:value="config.credential_retries" placeholder="5" /></n-form-item>
          </div>
        </div>
        <div class="config-section">
          <h3>请求配置</h3>
          <div class="form-grid-2">
            <n-form-item label="请求超时(秒)"><n-input v-model:value="config.request_timeout" placeholder="120" /></n-form-item>
            <n-form-item label="Token刷新间隔(分钟)"><n-input v-model:value="config.refresh_interval" placeholder="30" /></n-form-item>
          </div>
        </div>
        <div class="config-section">
          <h3>自动刷新设置</h3>
          <div class="switch-row">
            <n-switch :value="config.enable_token_refresh==='true'" @update:value="v=>config.enable_token_refresh=v?'true':'false'" />
            <span>自动刷新Token {{ config.enable_token_refresh==='true' ? '(已开启)' : '(已关闭)' }}</span>
          </div>
          <p class="hint indent">开启后系统每10分钟执行一次定时任务</p>
          <div class="switch-row">
            <n-switch :value="config.enable_usage_refresh==='true'" @update:value="v=>config.enable_usage_refresh=v?'true':'false'" />
            <span>自动刷新用量 {{ config.enable_usage_refresh==='true' ? '(已开启)' : '(已关闭)' }}</span>
          </div>
          <p class="hint warning">建议关闭自动刷新，避免频繁刷新被检测</p>
        </div>
        <div class="config-section">
          <h3>Token计数设置</h3>
          <div class="switch-row">
            <n-switch :value="config.enable_token_count==='true'" @update:value="v=>config.enable_token_count=v?'true':'false'" />
            <span>输出Token计数 {{ config.enable_token_count==='true' ? '(已开启)' : '(已关闭)' }}</span>
          </div>
          <div class="switch-row">
            <n-switch :value="config.enable_token_cache==='true'" :disabled="config.enable_token_count!=='true'" @update:value="v=>config.enable_token_cache=v?'true':'false'" />
            <span>缓存Token计数</span>
          </div>
          <div v-if="config.enable_token_cache==='true'&&config.enable_token_count==='true'" class="cache-config">
            <div class="cache-row"><span>缓存时间</span><n-select v-model:value="selectedTtl" :options="ttlOptions" style="width:160px" /><n-input-number v-if="selectedTtl==='custom'" v-model:value="customTtl" :min="10" :max="2592000" style="width:140px" /></div>
            <div class="cache-row"><span>缓存策略</span><n-select v-model:value="config.token_cache_strategy" :options="cacheStrategyOptions" style="width:280px" /></div>
            <div class="cache-stats">
              <span v-if="cacheStats.connected">缓存: {{ cacheStats.key_count }} 条 / {{ cacheStats.memory_used_str }}</span>
              <span v-else class="error">Redis 未连接</span>
              <button @click="fetchCacheStats" :disabled="cacheStatsLoading" class="small-btn">刷新</button>
              <button @click="clearCache" :disabled="cacheClearLoading||cacheStats.key_count===0" class="small-btn danger">清空</button>
            </div>
          </div>
        </div>
        <div class="config-section">
          <h3>上下文压缩</h3>
          <div class="switch-row">
            <n-switch :value="config.enable_context_compress==='true'" @update:value="v=>config.enable_context_compress=v?'true':'false'" />
            <span>上下文压缩 {{ config.enable_context_compress==='true' ? '(已开启)' : '(已关闭)' }}</span>
          </div>
        </div>
      </div>
<!-- 授权配置 -->
      <div v-show="activeTab==='license'" class="tab-panel">
        <n-spin :show="licenseLoading">
          <div class="config-section">
            <h3>当前授权状态</h3>
            <div class="tag-row">
              <n-tag v-for="ch in authorizedChannels" :key="ch" type="success" size="small">{{ ch }}</n-tag>
              <span v-if="authorizedChannels.length===0" class="hint">暂无授权渠道</span>
            </div>
          </div>
          <div class="config-section">
            <h3>每日用量</h3>
            <n-progress :percentage="licenseUsage.percent" :indicator-placement="'inside'" />
            <p class="hint">已使用 {{ licenseUsage.current }} / {{ licenseUsage.limit }}，剩余 {{ licenseUsage.remaining }}</p>
          </div>
          <div class="config-section">
            <h3>授权码</h3>
            <n-input v-model:value="licenseKey" type="textarea" placeholder="请输入授权码" :rows="3" />
            <button @click="saveLicense" :disabled="licenseVerifying" class="primary-btn mt-3">{{ licenseVerifying ? '验证中...' : '保存并验证' }}</button>
          </div>
        </n-spin>
      </div>
      <!-- 代理配置 -->
      <div v-show="activeTab==='proxy'" class="tab-panel">
        <div class="config-section">
          <h3>选择渠道</h3>
          <n-select v-model:value="proxyChannel" :options="[{label:'Kiro',value:'kiro'},{label:'Warp',value:'warp'},{label:'Orchids',value:'orchids'},{label:'Antigravity',value:'antigravity'},{label:'Cursor',value:'cursor'},{label:'Grok',value:'grok'}]" style="width:200px" />
        </div>
        <div class="config-section" v-if="builtinProxyKey">
          <h3>内置代理</h3>
          <div class="switch-row">
            <n-switch v-model:value="useBuiltinProxy" :disabled="!currentBuiltinProxy.available" />
            <span>使用内置代理 {{ useBuiltinProxy ? '(已开启)' : '(已关闭)' }}</span>
          </div>
          <p v-if="!currentBuiltinProxy.available" class="hint warning">当前渠道暂无可用内置代理</p>
        </div>
        <div class="config-section">
          <h3>自定义代理地址</h3>
          <n-input v-model:value="proxyUrl" placeholder="http://127.0.0.1:7890 或 socks5://127.0.0.1:1080" :disabled="useBuiltinProxy" />
          <p class="hint">支持 HTTP/HTTPS/SOCKS5 代理协议</p>
        </div>
      </div>
      <!-- 渠道配置 -->
      <div v-show="activeTab==='channel'" class="tab-panel">
        <div class="channel-tabs">
          <button v-for="ct in channelTabOptions" :key="ct.value" @click="channelTab=ct.value" :class="['tab-btn small', channelTab===ct.value?'active':'']">{{ ct.label }}</button>
        </div>
        <!-- Kiro -->
        <div v-show="channelTab==='kiro'" class="channel-panel">
          <n-spin :show="kiroQueueLoading">
            <div class="config-section">
              <h3>模型队列配置</h3>
              <p class="hint">为不同模型设置优先使用的队列等级</p>
              <div v-for="model in kiroModelOptions" :key="model.value" class="queue-row">
                <span class="model-label">{{ model.label }}</span>
                <n-select multiple :value="getModelQueues(model.value)" @update:value="v=>setModelQueues(model.value,v)" :options="kiroQueueOptions" style="flex:1" placeholder="选择队列" />
              </div>
              <button @click="saveKiroConfig" :disabled="kiroQueueSaving" class="primary-btn mt-3">{{ kiroQueueSaving ? '保存中...' : '保存 Kiro 配置' }}</button>
            </div>
          </n-spin>
        </div>
        <!-- Warp -->
        <div v-show="channelTab==='warp'" class="channel-panel">
          <div class="config-section">
            <h3>Warp 设置</h3>
            <div class="switch-row">
              <n-switch :value="config.warp_credit_refund==='true'" @update:value="v=>config.warp_credit_refund=v?'true':'false'" />
              <span>Credit Refund {{ config.warp_credit_refund==='true' ? '(已开启)' : '(已关闭)' }}</span>
            </div>
            <p class="hint indent">开启后Warp渠道会在请求完成后尝试退还Credit</p>
          </div>
        </div>
        <!-- Grok -->
        <div v-show="channelTab==='grok'" class="channel-panel">
          <n-spin :show="grokLoading">
            <div class="config-section">
              <h3>基础设置</h3>
              <div class="switch-row"><n-switch v-model:value="grokConfig.temporary" /><span>临时对话模式</span></div>
              <div class="switch-row"><n-switch v-model:value="grokConfig.stream" /><span>流式输出</span></div>
              <div class="switch-row"><n-switch v-model:value="grokConfig.thinking" /><span>思考模式</span></div>
              <n-form-item label="请求超时(秒)"><n-input-number v-model:value="grokConfig.timeout" :min="10" :max="600" /></n-form-item>
            </div>
            <div class="config-section">
              <h3>网络设置</h3>
              <n-form-item label="CF Clearance"><n-input v-model:value="grokConfig.cf_clearance" placeholder="cf_clearance cookie" /></n-form-item>
              <n-form-item label="应用地址"><n-input v-model:value="grokConfig.app_url" :placeholder="currentOrigin" /></n-form-item>
            </div>
            <div class="config-section">
              <h3>媒体格式</h3>
              <div class="form-grid-2">
                <n-form-item label="图片格式"><n-select v-model:value="grokConfig.image_format" :options="[{label:'URL',value:'url'},{label:'Base64',value:'base64'},{label:'本地缓存',value:'local'}]" /></n-form-item>
                <n-form-item label="视频格式"><n-select v-model:value="grokConfig.video_format" :options="[{label:'URL',value:'url'},{label:'本地缓存',value:'local'}]" /></n-form-item>
              </div>
            </div>
            <div class="config-section">
              <h3>并发设置</h3>
              <div class="form-grid-2">
                <n-form-item label="NSFW最大并发"><n-input-number v-model:value="grokConfig.nsfw_max_concurrent" :min="1" :max="100" /></n-form-item>
                <n-form-item label="NSFW批量大小"><n-input-number v-model:value="grokConfig.nsfw_batch_size" :min="1" :max="200" /></n-form-item>
                <n-form-item label="资源最大并发"><n-input-number v-model:value="grokConfig.assets_max_concurrent" :min="1" :max="100" /></n-form-item>
                <n-form-item label="媒体最大并发"><n-input-number v-model:value="grokConfig.media_max_concurrent" :min="1" :max="200" /></n-form-item>
              </div>
            </div>
            <div class="config-section">
              <h3>NSFW 批量管理</h3>
              <div class="switch-row">
                <n-switch :value="grokConfig.nsfw_enabled" @update:value="handleNsfwToggle" :disabled="nsfwBatchLoading" />
                <span>NSFW {{ grokConfig.nsfw_enabled ? '(已开启)' : '(已关闭)' }}</span>
              </div>
              <div v-if="nsfwProgress.show" class="progress-info">
                <n-progress :percentage="nsfwProgress.total?Math.round(nsfwProgress.current/nsfwProgress.total*100):0" :indicator-placement="'inside'" />
                <p class="hint">{{ nsfwProgress.action }}中: {{ nsfwProgress.current }}/{{ nsfwProgress.total }}</p>
              </div>
              <button @click="clearAssetsBatch" class="small-btn mt-2">清理资源缓存</button>
            </div>
            <div class="config-section">
              <h3>缓存管理</h3>
              <div class="switch-row"><n-switch v-model:value="grokConfig.cache_enable_auto_clean" /><span>自动清理</span></div>
              <n-form-item label="缓存上限(MB)"><n-input-number v-model:value="grokConfig.cache_limit_mb" :min="100" :max="10240" /></n-form-item>
              <n-spin :show="grokCacheLoading">
                <div class="cache-stats-grid">
                  <div class="cache-stat-card">
                    <span>图片缓存</span>
                    <strong>{{ grokCacheStats.local_image.count }} 个 / {{ grokCacheStats.local_image.size_mb.toFixed(2) }} MB</strong>
                    <div class="btn-row">
                      <button @click="openCacheList('image')" class="small-btn">查看</button>
                      <button @click="clearGrokCache('image')" :disabled="imageClearing" class="small-btn danger">{{ imageClearing ? '清理中...' : '清理' }}</button>
                    </div>
                  </div>
                  <div class="cache-stat-card">
                    <span>视频缓存</span>
                    <strong>{{ grokCacheStats.local_video.count }} 个 / {{ grokCacheStats.local_video.size_mb.toFixed(2) }} MB</strong>
                    <div class="btn-row">
                      <button @click="openCacheList('video')" class="small-btn">查看</button>
                      <button @click="clearGrokCache('video')" :disabled="videoClearing" class="small-btn danger">{{ videoClearing ? '清理中...' : '清理' }}</button>
                    </div>
                  </div>
                </div>
              </n-spin>
            </div>
            <button @click="saveGrokConfig" :disabled="grokSaving" class="primary-btn mt-3">{{ grokSaving ? '保存中...' : '保存 Grok 配置' }}</button>
          </n-spin>
        </div>
      </div>
      <!-- 全局保存 -->
      <div class="save-bar">
        <button @click="saveConfig" :disabled="saving" class="primary-btn large">{{ saving ? '保存中...' : '保存配置' }}</button>
      </div>
    </n-spin>
    <!-- 缓存文件弹窗 -->
    <n-modal v-model:show="showCacheDialog" preset="card" :title="cacheFileType==='image'?'图片缓存':'视频缓存'" style="width:700px;max-width:90vw">
      <n-spin :show="cacheFilesLoading">
        <div class="cache-file-list">
          <div v-for="file in cacheFiles" :key="file.name" class="cache-file-item">
            <span class="file-name">{{ file.name }}</span>
            <span class="file-size">{{ formatFileSize(file.size) }}</span>
            <span class="file-date">{{ formatDate(file.modified) }}</span>
            <button @click="previewFile(file)" class="small-btn">预览</button>
            <button @click="deleteCacheFile(file.name)" class="small-btn danger">删除</button>
          </div>
          <div v-if="cacheFiles.length===0" class="empty-hint">暂无缓存文件</div>
        </div>
        <n-pagination v-if="cacheFilesTotal>cacheFilesPageSize" v-model:page="cacheFilesPage" :page-count="Math.ceil(cacheFilesTotal/cacheFilesPageSize)" @update:page="fetchCacheFiles" style="margin-top:12px" />
      </n-spin>
    </n-modal>
    <n-modal v-model:show="showPreview" preset="card" title="预览" style="width:800px;max-width:90vw">
      <img v-if="previewType==='image'" :src="previewUrl" style="max-width:100%;max-height:70vh;object-fit:contain" />
      <video v-else :src="previewUrl" controls style="max-width:100%;max-height:70vh" />
    </n-modal>
  </div>
</template>

<style scoped>
.config-view { padding: 16px; height: 100%; overflow: auto; }
.page-header h1 { font-size: 20px; font-weight: 700; margin: 0; }
.page-header p { font-size: 13px; color: var(--text-color-3); margin: 4px 0 0; }
.tab-bar { display: flex; gap: 4px; background: var(--card-color); border-radius: 8px; padding: 4px; margin: 16px 0; width: fit-content; border: 1px solid var(--border-color); }
.tab-btn { padding: 6px 16px; font-size: 13px; font-weight: 500; border-radius: 6px; border: none; background: transparent; color: var(--text-color-3); cursor: pointer; transition: all .2s; }
.tab-btn.active { background: var(--primary-color); color: #fff; box-shadow: 0 1px 3px rgba(0,0,0,.1); }
.tab-btn.small { padding: 4px 12px; font-size: 12px; }
.tab-panel { background: var(--card-color); border-radius: 12px; padding: 24px; border: 1px solid var(--border-color); }
.config-section { margin-bottom: 24px; }
.config-section h3 { font-size: 15px; font-weight: 600; margin: 0 0 12px; }
.input-row { display: flex; align-items: center; gap: 8px; }
.switch-row { display: flex; align-items: center; gap: 12px; margin-bottom: 4px; }
.form-grid-2 { display: grid; grid-template-columns: 1fr 1fr; gap: 16px; }
.form-grid-3 { display: grid; grid-template-columns: 1fr 1fr 1fr; gap: 16px; }
.hint { font-size: 12px; color: var(--text-color-3); margin: 4px 0 0; }
.hint.indent { margin-left: 48px; }
.hint.warning { color: var(--error-color); }
.tag-row { display: flex; gap: 6px; flex-wrap: wrap; }
.icon-btn { padding: 6px 10px; border: 1px solid var(--border-color); border-radius: 6px; background: transparent; cursor: pointer; font-size: 12px; color: var(--text-color-2); }
.icon-btn:hover { background: var(--hover-color); }
.primary-btn { padding: 8px 20px; background: var(--primary-color); color: #fff; border: none; border-radius: 6px; cursor: pointer; font-size: 13px; font-weight: 500; }
.primary-btn:disabled { opacity: .5; cursor: not-allowed; }
.primary-btn.large { padding: 10px 32px; font-size: 14px; }
.small-btn { padding: 4px 10px; font-size: 12px; border: 1px solid var(--border-color); border-radius: 4px; background: transparent; cursor: pointer; color: var(--text-color-2); }
.small-btn:hover { background: var(--hover-color); }
.small-btn.danger { color: var(--error-color); border-color: var(--error-color); }
.small-btn:disabled { opacity: .5; cursor: not-allowed; }
.save-bar { margin-top: 20px; display: flex; justify-content: flex-end; }
.cache-config { margin-top: 12px; margin-left: 16px; padding: 16px; background: var(--body-color); border-radius: 8px; border: 1px solid var(--border-color); }
.cache-row { display: flex; align-items: center; gap: 12px; margin-bottom: 12px; }
.cache-row span { font-size: 13px; min-width: 80px; }
.cache-stats { display: flex; align-items: center; gap: 8px; font-size: 13px; margin-top: 8px; }
.cache-stats .error { color: var(--error-color); }
.cache-stats-grid { display: grid; grid-template-columns: 1fr 1fr; gap: 12px; margin-top: 12px; }
.cache-stat-card { padding: 12px; background: var(--body-color); border-radius: 8px; border: 1px solid var(--border-color); display: flex; flex-direction: column; gap: 6px; }
.cache-stat-card span { font-size: 12px; color: var(--text-color-3); }
.cache-stat-card strong { font-size: 14px; }
.btn-row { display: flex; gap: 6px; margin-top: 4px; }
.channel-tabs { display: flex; gap: 4px; margin-bottom: 16px; }
.channel-panel { margin-top: 8px; }
.queue-row { display: flex; align-items: center; gap: 12px; margin-bottom: 8px; }
.model-label { font-size: 13px; min-width: 120px; font-family: monospace; }
.progress-info { margin-top: 8px; }
.cache-file-list { max-height: 400px; overflow: auto; }
.cache-file-item { display: flex; align-items: center; gap: 8px; padding: 8px 0; border-bottom: 1px solid var(--border-color); font-size: 13px; }
.file-name { flex: 1; overflow: hidden; text-overflow: ellipsis; white-space: nowrap; }
.file-size { width: 80px; text-align: right; color: var(--text-color-3); }
.file-date { width: 140px; color: var(--text-color-3); }
.empty-hint { text-align: center; padding: 24px; color: var(--text-color-3); font-size: 13px; }
.mt-2 { margin-top: 8px; }
.mt-3 { margin-top: 12px; }
</style>
