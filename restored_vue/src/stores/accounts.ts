import { ref, reactive, computed, watch, nextTick } from 'vue'
import { useMessage } from 'naive-ui'
import http from '../utils/http'
import { CHANNELS, enabledChannelIds, DEFAULT_CHANNEL } from './channels'

// 授权渠道
const authorizedChannels = ref<string[]>([])

export async function fetchLicenseStatus() {
  try {
    const res = await http.get('/api/license/status')
    if (res.data.code === 0) {
      authorizedChannels.value = res.data.data.authorized_channels || []
    }
  } catch {}
}

// 可用渠道（过滤需要权限但未授权的）
export const availableChannels = computed(() =>
  enabledChannelIds.filter((id) => {
    const config = CHANNELS[id]
    if (!config) return false
    if (config.requiresPermission) return authorizedChannels.value.includes(id)
    return true
  })
)

// 当前活跃渠道
const STORAGE_KEY = 'active_channel_id'

function getInitialChannel(): string {
  const saved = localStorage.getItem(STORAGE_KEY)
  if (saved && CHANNELS[saved] && CHANNELS[saved].enabled) return saved
  return DEFAULT_CHANNEL
}

// 渠道状态存储
const channelStates: Record<string, any> = reactive({})
export const activeChannelId = ref(getInitialChannel())

watch(activeChannelId, (id) => {
  localStorage.setItem(STORAGE_KEY, id)
})

function getChannelState(channelId: string) {
  if (!channelStates[channelId]) {
    channelStates[channelId] = {
      accounts: [] as any[],
      loading: false,
      totalCount: 0,
      normalCount: 0,
      filteredTotal: 0,
      currentPage: 1,
      currentPageSize: 20,
      selectedIds: [] as number[],
      refreshingIds: new Set<number>(),
      filterStatus: '',
      filterPlanType: '',
      filterNsfw: ''
    }
  }
  return channelStates[channelId]
}

// 渠道统计摘要
export const channelSummaries = computed(() =>
  availableChannels.value
    .map((id) => {
      const state = channelStates[id]
      const config = CHANNELS[id]
      return {
        channelId: id,
        name: config?.name || id,
        total: state?.totalCount || 0,
        normal: state?.normalCount || 0,
        abnormal: (state?.totalCount || 0) - (state?.normalCount || 0)
      }
    })
    .filter((s) => s.total > 0)
)

// 获取所有渠道统计
export async function fetchAllChannelStats() {
  for (const id of enabledChannelIds) {
    await fetchChannelStats(id)
  }
}

export async function fetchChannelStats(channelId: string) {
  const config = CHANNELS[channelId]
  const state = getChannelState(channelId)
  if (!config) return
  try {
    const res = await http.get(`${config.apiBase}/stats`)
    if (res.data.code === 403) return
    if (res.data.code === 0) {
      state.totalCount = res.data.data.total || 0
      state.normalCount = res.data.data.normal || 0
    }
  } catch {}
}

export function getCurrentState(channelId?: string) {
  const id = channelId || activeChannelId.value
  return getChannelState(id)
}

export function getCurrentChannelConfig() {
  return CHANNELS[activeChannelId.value] || CHANNELS[DEFAULT_CHANNEL]
}

export function switchChannel(channelId: string, message?: any) {
  if (CHANNELS[channelId]) {
    activeChannelId.value = channelId
    const state = getCurrentState(channelId)
    if (state.accounts.length === 0 && !state.loading) {
      fetchAccounts(channelId, message)
    }
  }
}

export async function fetchAccounts(channelId?: string, message?: any) {
  const id = channelId || activeChannelId.value
  const config = CHANNELS[id]
  const state = getCurrentState(id)
  if (!config) return

  state.loading = true
  try {
    const params: any = {
      page: state.currentPage,
      pageSize: state.currentPageSize
    }
    if (state.filterStatus) params.status = state.filterStatus
    if (id === 'kiro' && state.filterPlanType) params.plan_type = state.filterPlanType
    if (id === 'grok' && state.filterPlanType) params.pool = state.filterPlanType
    if (id === 'grok' && state.filterNsfw) params.nsfw = state.filterNsfw

    const res = await http.get(`${config.apiBase}/list`, { params })
    if (res.data.code === 0) {
      state.accounts = res.data.data.list || []
      state.totalCount = res.data.data.totalCount ?? res.data.data.total ?? 0
      state.normalCount = res.data.data.normalCount ?? state.accounts.filter((a: any) => a.status === 'normal').length
      state.filteredTotal = res.data.data.total ?? state.totalCount
    } else if (res.data.code !== 403) {
      message?.error(res.data.message || res.data.msg || `获取 ${config.name} 账号列表失败`)
    }
  } catch {} finally {
    state.loading = false
  }
}

export async function deleteAccount(channelId: string, id: number, message: any) {
  const config = CHANNELS[channelId]
  if (!config) return
  try {
    const res = await http.post(`${config.apiBase}/delete`, { id })
    if (res.data.code === 0) {
      message.success('删除成功')
      await fetchAccounts(channelId, message)
    } else {
      message.error(res.data.message || res.data.msg || '删除失败')
    }
  } catch {
    message.error('系统错误')
  }
}

export async function batchDeleteAccounts(channelId: string, ids: number[], message: any) {
  const config = CHANNELS[channelId]
  const state = getCurrentState(channelId)
  if (!config || ids.length === 0) return
  try {
    const res = await http.post(`${config.apiBase}/delete-batch`, { ids })
    if (res.data.code === 0) {
      message.success(`已删除 ${res.data.data.deleted} 个账号`)
      state.selectedIds = []
      await fetchAccounts(channelId, message)
    } else {
      message.error(res.data.message || res.data.msg || '删除失败')
    }
  } catch {
    message.error('系统错误')
  }
}

export async function deleteAbnormalAccounts(channelId: string, message: any) {
  const config = CHANNELS[channelId]
  if (!config) return
  try {
    const res = await http.post(`${config.apiBase}/delete-abnormal`, {})
    if (res.data.code === 0) {
      message.success(`已删除 ${res.data.data.deleted} 个非正常账号`)
      await fetchAccounts(channelId, message)
    } else {
      message.error(res.data.message || res.data.msg || '删除失败')
    }
  } catch {
    message.error('系统错误')
  }
}

export async function recoverAbnormalAccounts(channelId: string, message: any) {
  const config = CHANNELS[channelId]
  if (!config) return
  try {
    const res = await http.post(`${config.apiBase}/recover-abnormal`, {})
    if (res.data.code === 0) {
      message.success(`已恢复 ${res.data.data.recovered} 个异常账号`)
      await fetchAccounts(channelId, message)
    } else {
      message.error(res.data.message || res.data.msg || '恢复失败')
    }
  } catch {
    message.error('系统错误')
  }
}

export async function refreshAccount(channelId: string, id: number, message: any) {
  const config = CHANNELS[channelId]
  const state = getCurrentState(channelId)
  if (!config) return

  state.refreshingIds.add(id)
  try {
    const res = await http.post(`${config.apiBase}/refresh`, { id })
    if (res.data.code === 0) {
      message.success('刷新成功')
      await fetchAccounts(channelId, message)
    } else {
      message.error(res.data.message || res.data.msg || '刷新失败')
    }
  } catch {
    message.error('系统错误')
  } finally {
    state.refreshingIds.delete(id)
  }
}

export async function queryUsage(channelId: string, id: number, message: any) {
  const config = CHANNELS[channelId]
  const state = getCurrentState(channelId)
  if (!config) return

  state.refreshingIds.add(id)
  try {
    const res = await http.post(`${config.apiBase}/query-usage`, { id })
    if (res.data.code === 0) {
      message.success('用量查询成功')
      await fetchAccounts(channelId, message)
    } else {
      message.error(res.data.message || res.data.msg || '用量查询失败')
    }
  } catch {
    message.error('系统错误')
  } finally {
    state.refreshingIds.delete(id)
  }
}

export async function exportAccounts(channelId: string, message: any) {
  const config = CHANNELS[channelId]
  const state = getCurrentState(channelId)
  if (!config) return
  try {
    const res = await http.get(`${config.apiBase}/export`, {
      params: { page: state.currentPage, pageSize: state.currentPageSize }
    })
    if (res.data.code === 0) {
      const json = JSON.stringify(res.data.data, null, 2)
      const blob = new Blob([json], { type: 'application/json' })
      const url = URL.createObjectURL(blob)
      const a = document.createElement('a')
      a.href = url
      a.download = `${channelId}_accounts_page${state.currentPage}.json`
      a.click()
      URL.revokeObjectURL(url)
      message.success('导出成功')
    } else {
      message.error(res.data.message || res.data.msg || '导出失败')
    }
  } catch {
    message.error('系统错误')
  }
}

export function copyToClipboard(text: string, message: any) {
  navigator.clipboard.writeText(text)
  message.success('已复制到剪贴板')
}

export async function batchRefreshUsage(
  channelId: string,
  planType: string,
  scope: string,
  onProgress: (data: any) => void,
  message: any
) {
  const config = CHANNELS[channelId]
  if (!config) return
  const state = getCurrentState(channelId)

  const params: any = {
    scope,
    page: state.currentPage,
    pageSize: state.currentPageSize
  }
  if (channelId === 'kiro') params.plan_type = planType
  else if (channelId === 'grok') params.pool = planType

  const token = localStorage.getItem('auth_token')
  const headers: Record<string, string> = { 'Content-Type': 'application/json' }
  if (token) headers['X-Auth-Token'] = token

  const response = await fetch(`${config.apiBase}/batch-refresh-usage`, {
    method: 'POST',
    headers,
    body: JSON.stringify(params)
  })

  const reader = response.body?.getReader()
  const decoder = new TextDecoder()
  let buffer = ''

  if (reader) {
    while (true) {
      const { done, value } = await reader.read()
      if (done) break
      buffer += decoder.decode(value, { stream: true })
      const lines = buffer.split('\n')
      buffer = lines.pop() || ''
      let eventType = ''
      for (const line of lines) {
        if (line.startsWith('event: ')) {
          eventType = line.slice(7)
        } else if (line.startsWith('data: ')) {
          try {
            const data = JSON.parse(line.slice(6))
            if (eventType === 'result') {
              onProgress({
                current: data.index,
                total: data.total,
                success: data.success,
                failed: data.index - data.success,
                result: data.result
              })
            } else if (eventType === 'done') {
              message.success(`批量刷新完成: 成功 ${data.success} 个, 失败 ${data.failed} 个`)
            }
          } catch {}
        }
      }
    }
  }
  await fetchAccounts(channelId, message)
}

export function setPage(channelId: string, page: number, message?: any) {
  const state = getCurrentState(channelId)
  state.currentPage = page
  state.selectedIds = []
  fetchAccounts(channelId, message)
}

export function setPageSize(channelId: string, pageSize: number, message?: any) {
  const state = getCurrentState(channelId)
  state.currentPageSize = pageSize
  state.currentPage = 1
  state.selectedIds = []
  fetchAccounts(channelId, message)
}

export function toggleSelectAll(channelId: string) {
  const state = getCurrentState(channelId)
  if (state.selectedIds.length === state.accounts.length) {
    state.selectedIds = []
  } else {
    state.selectedIds = state.accounts.map((a: any) => a.id)
  }
}

export function toggleSelectItem(channelId: string, id: number) {
  const state = getCurrentState(channelId)
  const idx = state.selectedIds.indexOf(id)
  if (idx > -1) {
    state.selectedIds.splice(idx, 1)
  } else {
    state.selectedIds.push(id)
  }
}

export function setFilterStatus(channelId: string, status: string, message?: any) {
  const state = getCurrentState(channelId)
  state.filterStatus = status
  state.currentPage = 1
  state.selectedIds = []
  fetchAccounts(channelId, message)
}

export async function updateProxy(channelId: string, id: number, proxy: string, message: any): Promise<boolean> {
  const config = CHANNELS[channelId]
  if (!config) return false
  try {
    const res = await http.post(`${config.apiBase}/update-proxy`, { id, proxy })
    if (res.data.code === 0) {
      message.success('代理更新成功')
      await fetchAccounts(channelId, message)
      return true
    } else {
      message.error(res.data.message || res.data.msg || '更新失败')
      return false
    }
  } catch {
    message.error('系统错误')
    return false
  }
}

export function setFilterPlanType(channelId: string, planType: string, message?: any) {
  const state = getCurrentState(channelId)
  state.filterPlanType = planType
  state.currentPage = 1
  state.selectedIds = []
  fetchAccounts(channelId, message)
}

export function setFilterNsfw(channelId: string, nsfw: string, message?: any) {
  const state = getCurrentState(channelId)
  state.filterNsfw = nsfw
  state.currentPage = 1
  state.selectedIds = []
  fetchAccounts(channelId, message)
}
