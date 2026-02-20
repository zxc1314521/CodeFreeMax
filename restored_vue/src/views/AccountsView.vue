<script setup lang="ts">
import { ref, computed, onMounted } from 'vue'
import { useMessage, NTag, NSwitch, NPopconfirm, NPagination, NModal, NInput, NSelect, NProgress } from 'naive-ui'
import http from '../utils/http'
import { CHANNELS, type ChannelConfig } from '../stores/channels'
import {
  activeChannelId, switchChannel, getCurrentState, getCurrentChannelConfig,
  fetchAccounts, deleteAccount, batchDeleteAccounts, deleteAbnormalAccounts,
  recoverAbnormalAccounts, refreshAccount, exportAccounts, copyToClipboard,
  batchRefreshUsage, setPage, toggleSelectAll, toggleSelectItem,
  setFilterStatus, setFilterPlanType, setFilterNsfw, updateProxy,
  fetchAllChannelStats, availableChannels, queryUsage
} from '../stores/accounts'

const message = useMessage()
const channelConfig = computed(() => getCurrentChannelConfig())
const state = computed(() => getCurrentState())
const columns = computed(() => (channelConfig.value.columns || []).filter(c => c.type !== 'actions'))

const showAddModal = ref(false)
const addTokenText = ref('')
const addSaving = ref(false)
const addMode = ref<'manual' | 'idc'>('manual')
const oauthLoading = ref(false)
const oauthData = ref<any>(null)
const showOAuthModal = ref(false)
const oauthPolling = ref<any>(null)
const showProxyModal = ref(false)
const proxyEditId = ref<number>(0)
const proxyEditValue = ref('')
const proxySaving = ref(false)
const showBatchRefreshModal = ref(false)
const batchRefreshScope = ref('page')
const batchRefreshProgress = ref({ show: false, current: 0, total: 0, success: 0, failed: 0 })
const batchRefreshing = ref(false)
const showDetailModal = ref(false)
const detailAccount = ref<any>(null)
const showTestModal = ref(false)
const testAccount = ref<any>(null)
const testPrompt = ref('你好，请简单介绍一下你自己')
const testModel = ref('')
const testStream = ref(true)
const testLoading = ref(false)
const testResult = ref('')
const testAbort = ref<AbortController | null>(null)
const testModelOptions = ref<{ label: string; value: string }[]>([])
const testModelLoading = ref(false)

const maskToken = (t: string) => !t ? '-' : t.length <= 12 ? t : t.slice(0, 6) + '...' + t.slice(-6)
const formatDate = (d: string) => !d ? '-' : new Date(d).toLocaleString('zh-CN', { timeZone: 'Asia/Shanghai' })
const getField = (row: any, field: string | string[] | undefined) => {
  if (!field) return ''
  if (Array.isArray(field)) { for (const f of field) { if (row[f]) return row[f] } return '' }
  return row[field] ?? ''
}

const planTypeOptions = computed(() => {
  const ch = activeChannelId.value
  if (ch === 'kiro') return [{ label: '全部', value: '' }, { label: 'Ultra', value: 'ultra' }, { label: 'Plus', value: 'plus' }, { label: 'Pro', value: 'pro' }, { label: 'Free', value: 'free' }]
  if (ch === 'grok') return [{ label: '全部', value: '' }, { label: 'Premium+', value: 'premium_plus' }, { label: 'Premium', value: 'premium' }, { label: 'Free', value: 'free' }]
  if (ch === 'antigravity') return [{ label: '全部', value: '' }, { label: 'Paid', value: 'paid' }, { label: 'Free', value: 'free' }]
  return []
})
const statusOptions = [{ label: '全部', value: '' }, { label: '正常', value: 'normal' }, { label: '异常', value: 'error' }, { label: '禁用', value: 'disabled' }]
const nsfwOptions = [{ label: '全部', value: '' }, { label: '已开启', value: 'enabled' }, { label: '未开启', value: 'disabled' }]

async function handleAddTokens() {
  const text = addTokenText.value.trim()
  if (!text) { message.warning('请输入Token'); return }
  const config = channelConfig.value
  addSaving.value = true
  try {
    const tokens = text.split('\n').map(s => s.trim()).filter(Boolean)
    const res = await http.post(`${config.apiBase}/add`, { [config.batchTokenFieldName]: tokens })
    if (res.data.code === 0) {
      message.success(`添加完成: 成功 ${res.data.data?.success || tokens.length} 个`)
      showAddModal.value = false; addTokenText.value = ''
      await fetchAccounts(activeChannelId.value, message)
    } else message.error(res.data.message || res.data.msg || '添加失败')
  } catch (e: any) { message.error(e.message || '添加失败') }
  finally { addSaving.value = false }
}

async function startOAuth() {
  const config = channelConfig.value
  if (!config.oauth?.enabled) return
  oauthLoading.value = true
  try {
    const res = await http.post(config.oauth.authorizeUrl, {})
    if (res.data.code === 0) { oauthData.value = res.data.data; showOAuthModal.value = true; startOAuthPolling() }
    else message.error(res.data.message || '授权失败')
  } catch (e: any) { message.error(e.message || '授权失败') }
  finally { oauthLoading.value = false }
}
function startOAuthPolling() {
  const config = channelConfig.value; if (!config.oauth) return; stopOAuthPolling()
  oauthPolling.value = setInterval(async () => {
    try {
      const res = await http.get(config.oauth!.statusUrl, { params: { device_code: oauthData.value?.device_code } })
      if (res.data.code === 0 && res.data.data?.status === 'authorized') {
        stopOAuthPolling(); showOAuthModal.value = false; message.success('授权成功')
        await fetchAccounts(activeChannelId.value, message)
      }
    } catch {}
  }, 3000)
}
function stopOAuthPolling() { if (oauthPolling.value) { clearInterval(oauthPolling.value); oauthPolling.value = null } }

function openProxyEdit(id: number, proxy: string) { proxyEditId.value = id; proxyEditValue.value = proxy || ''; showProxyModal.value = true }
async function saveProxy() {
  proxySaving.value = true
  const ok = await updateProxy(activeChannelId.value, proxyEditId.value, proxyEditValue.value, message)
  proxySaving.value = false; if (ok) showProxyModal.value = false
}

async function handleBatchRefreshUsage() {
  batchRefreshing.value = true; batchRefreshProgress.value = { show: true, current: 0, total: 0, success: 0, failed: 0 }
  try {
    await batchRefreshUsage(activeChannelId.value, state.value.filterPlanType, batchRefreshScope.value,
      (data) => { batchRefreshProgress.value = { show: true, ...data } }, message)
  } finally { batchRefreshing.value = false; showBatchRefreshModal.value = false }
}

function openDetail(row: any) { detailAccount.value = row; showDetailModal.value = true }
function openTest(row: any) {
  testAccount.value = row
  testResult.value = ''
  testModel.value = getCurrentChannelConfig().defaultModel || ''
  showTestModal.value = true
  fetchTestModels()
}
async function fetchTestModels() {
  testModelLoading.value = true
  testModelOptions.value = []
  try {
    const res = await http.get('/api/models/list', { params: { channel: activeChannelId.value } })
    if (res.data.code === 0 && res.data.data) {
      const models = res.data.data[activeChannelId.value] || []
      testModelOptions.value = models
        .filter((m: any) => m.enabled)
        .map((m: any) => ({ label: m.name || m.model_id, value: m.model_id }))
    }
  } catch {}
  testModelLoading.value = false
}
async function handleTest() {
  if (testLoading.value) return
  testLoading.value = true
  testResult.value = ''
  const abort = new AbortController()
  testAbort.value = abort

  const token = localStorage.getItem('auth_token')
  const headers: Record<string, string> = { 'Content-Type': 'application/json' }
  if (token) headers['X-Auth-Token'] = token

  try {
    const res = await fetch('/api/test', {
      method: 'POST',
      headers,
      signal: abort.signal,
      body: JSON.stringify({
        channel: activeChannelId.value,
        model: testModel.value,
        prompt: testPrompt.value,
        stream: testStream.value,
        max_tokens: 2048,
        account_id: testAccount.value?.id
      })
    })

    if (!res.ok) {
      const text = await res.text()
      testResult.value = `请求失败 (HTTP ${res.status}): ${text}`
      testLoading.value = false
      return
    }

    if (testStream.value && res.headers.get('content-type')?.includes('text/event-stream')) {
      const reader = res.body?.getReader()
      const decoder = new TextDecoder()
      let buffer = ''
      if (reader) {
        while (true) {
          const { done, value } = await reader.read()
          if (done) break
          buffer += decoder.decode(value, { stream: true })
          const lines = buffer.split('\n')
          buffer = lines.pop() || ''
          for (const line of lines) {
            if (line.startsWith('data: ')) {
              const data = line.slice(6).trim()
              if (data === '[DONE]') continue
              try {
                const parsed = JSON.parse(data)
                const delta = parsed.choices?.[0]?.delta?.content
                if (delta) testResult.value += delta
              } catch {}
            }
          }
        }
      }
    } else {
      const text = await res.text()
      try {
        const parsed = JSON.parse(text)
        if (parsed.code === 1) {
          testResult.value = `错误: ${parsed.msg || parsed.message}`
        } else if (parsed.choices?.[0]?.message?.content) {
          testResult.value = parsed.choices[0].message.content
        } else {
          testResult.value = text
        }
      } catch {
        testResult.value = text
      }
    }
  } catch (e: any) {
    if (e.name !== 'AbortError') {
      testResult.value = `请求异常: ${e.message}`
    }
  } finally {
    testLoading.value = false
    testAbort.value = null
  }
}
function stopTest() {
  testAbort.value?.abort()
  testLoading.value = false
}
function handleSwitchChannel(id: string) { switchChannel(id, message) }
function handleExport() { exportAccounts(activeChannelId.value, message) }
function handleDeleteAbnormal() { deleteAbnormalAccounts(activeChannelId.value, message) }
function handleRecoverAbnormal() { recoverAbnormalAccounts(activeChannelId.value, message) }
function handleBatchDelete() { batchDeleteAccounts(activeChannelId.value, state.value.selectedIds, message) }

const statusColorMap: Record<string, string> = { normal: 'success', error: 'error', disabled: 'warning', expired: 'default' }
const statusLabelMap: Record<string, string> = { normal: '正常', error: '异常', disabled: '禁用', expired: '过期' }
const planColorMap: Record<string, string> = { ultra: '#8b5cf6', plus: '#3b82f6', pro: '#10b981', free: '#6b7280', premium_plus: '#f59e0b', premium: '#3b82f6', paid: '#10b981' }

onMounted(() => { fetchAllChannelStats(); fetchAccounts(activeChannelId.value, message) })
</script>

<template>
  <div class="accounts-page">
    <!-- Channel tabs -->
    <div class="channel-tabs">
      <button v-for="chId in availableChannels" :key="chId"
        :class="['ch-tab', { active: activeChannelId === chId }]"
        @click="handleSwitchChannel(chId)">
        {{ CHANNELS[chId]?.name || chId }}
      </button>
    </div>

    <!-- Stats bar -->
    <div class="stats-bar">
      <div class="stat-item">
        <span class="stat-label">总数</span>
        <span class="stat-value">{{ state.totalCount }}</span>
      </div>
      <div class="stat-item">
        <span class="stat-label">正常</span>
        <span class="stat-value text-green">{{ state.normalCount }}</span>
      </div>
      <div class="stat-item">
        <span class="stat-label">异常</span>
        <span class="stat-value text-red">{{ state.totalCount - state.normalCount }}</span>
      </div>
    </div>

    <!-- Toolbar -->
    <div class="toolbar">
      <div class="toolbar-left">
        <button class="btn btn-primary" @click="showAddModal = true; addMode = 'manual'">
          {{ activeChannelId === 'kiro' ? '添加账号' : '添加Token' }}
        </button>
        <button v-if="channelConfig.oauth?.enabled && activeChannelId !== 'kiro'" class="btn btn-green" :disabled="oauthLoading" @click="startOAuth">
          {{ oauthLoading ? '授权中...' : 'OAuth登录' }}
        </button>
        <button class="btn btn-blue" @click="showBatchRefreshModal = true">批量刷新用量</button>
        <button class="btn" @click="handleExport">导出</button>
      </div>
      <div class="toolbar-right">
        <NSelect v-model:value="state.filterStatus" :options="statusOptions" size="small" style="width:100px"
          @update:value="(v: string) => setFilterStatus(activeChannelId, v, message)" />
        <NSelect v-if="planTypeOptions.length > 0" v-model:value="state.filterPlanType" :options="planTypeOptions"
          size="small" style="width:120px"
          @update:value="(v: string) => setFilterPlanType(activeChannelId, v, message)" />
        <NSelect v-if="activeChannelId === 'grok'" v-model:value="state.filterNsfw" :options="nsfwOptions"
          size="small" style="width:100px"
          @update:value="(v: string) => setFilterNsfw(activeChannelId, v, message)" />
      </div>
    </div>

    <!-- Batch actions -->
    <div v-if="state.selectedIds.length > 0" class="batch-bar">
      <span>已选 {{ state.selectedIds.length }} 项</span>
      <NPopconfirm @positive-click="handleBatchDelete">
        <template #trigger><button class="btn btn-danger btn-sm">批量删除</button></template>
        确定删除选中的 {{ state.selectedIds.length }} 个账号？
      </NPopconfirm>
      <NPopconfirm @positive-click="handleDeleteAbnormal">
        <template #trigger><button class="btn btn-warning btn-sm">删除异常</button></template>
        确定删除所有异常账号？
      </NPopconfirm>
      <NPopconfirm @positive-click="handleRecoverAbnormal">
        <template #trigger><button class="btn btn-sm">恢复异常</button></template>
        确定恢复所有异常账号？
      </NPopconfirm>
    </div>

    <!-- Table -->
    <div class="table-wrap" :class="{ loading: state.loading }">
      <table class="data-table">
        <thead>
          <tr>
            <th class="col-check">
              <input type="checkbox" :checked="state.selectedIds.length === state.accounts.length && state.accounts.length > 0"
                @change="toggleSelectAll(activeChannelId)" />
            </th>
            <th>序号</th>
            <th v-for="col in columns" :key="col.key" :style="col.width ? { width: col.width } : col.minWidth ? { minWidth: col.minWidth } : {}">
              {{ col.label }}
            </th>
            <th>操作</th>
          </tr>
        </thead>
        <tbody>
          <tr v-if="state.accounts.length === 0">
            <td :colspan="columns.length + 3" class="empty-row">暂无数据</td>
          </tr>
          <tr v-for="(row, idx) in state.accounts" :key="row.id"
            :class="{ selected: state.selectedIds.includes(row.id) }">
            <td class="col-check">
              <input type="checkbox" :checked="state.selectedIds.includes(row.id)"
                @change="toggleSelectItem(activeChannelId, row.id)" />
            </td>
            <td>{{ (state.currentPage - 1) * state.currentPageSize + idx + 1 }}</td>
            <td v-for="col in columns" :key="col.key">
              <!-- Status column -->
              <template v-if="col.key === 'status'">
                <NTag :type="statusColorMap[row.status] || 'default'" size="small">
                  {{ statusLabelMap[row.status] || row.status }}
                </NTag>
              </template>
              <!-- Enabled column -->
              <template v-else-if="col.key === 'enabled'">
                <NSwitch :value="row.enabled" size="small"
                  @update:value="(v: boolean) => { row.enabled = v }" />
              </template>
              <!-- Plan/subscription column -->
              <template v-else-if="col.key === 'plan_type' || col.key === 'pool'">
                <span class="plan-badge" :style="{ background: planColorMap[getField(row, col.field)] || '#6b7280' }">
                  {{ getField(row, col.field) || '-' }}
                </span>
              </template>
              <!-- Usage column -->
              <template v-else-if="col.key === 'usage'">
                <div class="usage-cell">
                  <span class="usage-text">{{ row.usage_used ?? 0 }} / {{ row.usage_limit ?? '∞' }}</span>
                  <div v-if="row.usage_limit" class="usage-bar">
                    <div class="usage-bar-fill" :style="{
                      width: Math.min(100, (row.usage_used || 0) / row.usage_limit * 100) + '%',
                      background: (row.usage_used || 0) / row.usage_limit > 0.8 ? '#ef4444' : (row.usage_used || 0) / row.usage_limit > 0.5 ? '#f59e0b' : '#10b981'
                    }"></div>
                  </div>
                  <span v-if="row.usage_limit" class="usage-remain">剩余 {{ row.usage_limit - (row.usage_used || 0) }}</span>
                </div>
              </template>
              <!-- Token column (masked) -->
              <template v-else-if="col.key === 'token' || col.key === 'cookie' || col.key === 'access_token'">
                <span class="token-cell" @click="copyToClipboard(getField(row, col.field), message)">
                  {{ maskToken(getField(row, col.field)) }}
                </span>
              </template>
              <!-- Proxy column -->
              <template v-else-if="col.key === 'proxy'">
                <span class="proxy-cell" @click="openProxyEdit(row.id, getField(row, col.field))">
                  {{ getField(row, col.field) || '点击设置' }}
                </span>
              </template>
              <!-- Date columns -->
              <template v-else-if="col.key === 'last_used' || col.key === 'created_at' || col.key === 'updated_at'">
                {{ formatDate(getField(row, col.field)) }}
              </template>
              <!-- NSFW column -->
              <template v-else-if="col.key === 'nsfw'">
                <NTag :type="row.nsfw ? 'warning' : 'default'" size="small">{{ row.nsfw ? '是' : '否' }}</NTag>
              </template>
              <!-- Default text -->
              <template v-else>
                {{ getField(row, col.field) || '-' }}
              </template>
            </td>
            <td class="action-cell">
              <button class="btn-link" @click="openDetail(row)">详情</button>
              <button class="btn-link" @click="openTest(row)">测试</button>
              <button v-if="activeChannelId === 'kiro'" class="btn-link" :disabled="state.refreshingIds.has(row.id)"
                @click="queryUsage(activeChannelId, row.id, message)">
                {{ state.refreshingIds.has(row.id) ? '查询中' : '用量' }}
              </button>
              <button class="btn-link" :disabled="state.refreshingIds.has(row.id)"
                @click="refreshAccount(activeChannelId, row.id, message)">
                {{ state.refreshingIds.has(row.id) ? '刷新中' : '刷新' }}
              </button>
              <NPopconfirm @positive-click="deleteAccount(activeChannelId, row.id, message)">
                <template #trigger><button class="btn-link text-red">删除</button></template>
                确定删除此账号？
              </NPopconfirm>
            </td>
          </tr>
        </tbody>
      </table>
    </div>

    <!-- Pagination -->
    <div class="pagination-bar">
      <NPagination :page="state.currentPage" :page-size="state.currentPageSize"
        :item-count="state.filteredTotal || state.totalCount"
        :page-sizes="[10, 20, 50, 100]" show-size-picker
        @update:page="(p: number) => setPage(activeChannelId, p, message)"
        @update:page-size="(s: number) => { state.currentPageSize = s; state.currentPage = 1; fetchAccounts(activeChannelId, message) }" />
    </div>

    <!-- Add Token/Account Modal -->
    <NModal v-model:show="showAddModal" :title="activeChannelId === 'kiro' ? '添加 Kiro 账号' : '添加Token'" preset="card" style="width:560px">
      <!-- Kiro: tabbed UI -->
      <template v-if="activeChannelId === 'kiro'">
        <div class="add-tabs">
          <button :class="['add-tab', addMode === 'idc' ? 'active' : '']" @click="addMode = 'idc'">AWS IDC 授权登录</button>
          <button :class="['add-tab', addMode === 'manual' ? 'active' : '']" @click="addMode = 'manual'">手动添加凭据</button>
        </div>
        <!-- IDC tab -->
        <div v-if="addMode === 'idc'" class="add-tab-content">
          <p class="add-hint">通过 AWS IAM Identity Center (IDC) 设备授权流程添加账号。</p>
          <p class="add-hint">点击下方按钮发起授权，然后在浏览器中完成登录。</p>
          <div style="text-align:center;margin-top:16px">
            <button class="btn btn-green" :disabled="oauthLoading" @click="startOAuth" style="padding:8px 28px;font-size:14px">
              {{ oauthLoading ? '授权中...' : 'AWS IDC 授权登录' }}
            </button>
          </div>
        </div>
        <!-- Manual tab -->
        <div v-if="addMode === 'manual'" class="add-tab-content">
          <p class="add-hint">每行一个凭据，支持两种格式：</p>
          <div class="format-box">
            <p><span class="format-label">格式1</span> Social 账号（Google/GitHub 登录）— 纯 refreshToken：</p>
            <code>refreshToken</code>
            <p style="margin-top:8px"><span class="format-label">格式2</span> IDC/Enterprise 账号（用 ---- 分隔）：</p>
            <code>refreshToken----clientId----clientSecret----region</code>
            <p style="margin-top:6px;font-size:11px;color:#888">IDC 凭据可从 Kiro IDE 的 ~/.aws/sso/cache/ 目录获取 clientId 和 clientSecret</p>
          </div>
          <NInput v-model:value="addTokenText" type="textarea" :rows="6"
            placeholder="请粘贴 Kiro 凭据，每行一个..." style="margin-top:10px" />
        </div>
      </template>
      <!-- Other channels: simple textarea -->
      <template v-else>
        <p style="margin-bottom:8px;color:#999">每行一个Token{{ channelConfig.batchTokenFieldName === 'cookies' ? ' (Cookie)' : '' }}</p>
        <NInput v-model:value="addTokenText" type="textarea" :rows="8" placeholder="每行一个Token" />
      </template>
      <template #footer>
        <div style="display:flex;justify-content:flex-end;gap:8px">
          <button class="btn" @click="showAddModal = false">取消</button>
          <button v-if="!(activeChannelId === 'kiro' && addMode === 'idc')"
            class="btn btn-primary" :disabled="addSaving" @click="handleAddTokens">
            {{ addSaving ? '添加中...' : '确定添加' }}
          </button>
        </div>
      </template>
    </NModal>

    <!-- OAuth Modal -->
    <NModal v-model:show="showOAuthModal" title="OAuth授权" preset="card" style="width:480px" @after-leave="stopOAuthPolling">
      <div v-if="oauthData" style="text-align:center">
        <p style="margin-bottom:12px">请在浏览器中打开以下链接完成授权：</p>
        <a :href="oauthData.verification_uri_complete || oauthData.verification_uri" target="_blank" class="oauth-link">
          {{ oauthData.verification_uri_complete || oauthData.verification_uri }}
        </a>
        <p v-if="oauthData.user_code" style="margin-top:12px">
          授权码: <strong style="font-size:18px;letter-spacing:2px">{{ oauthData.user_code }}</strong>
        </p>
        <p style="margin-top:16px;color:#999">等待授权中...</p>
      </div>
    </NModal>

    <!-- Proxy Edit Modal -->
    <NModal v-model:show="showProxyModal" title="编辑代理" preset="card" style="width:420px">
      <NInput v-model:value="proxyEditValue" placeholder="http://host:port 或 socks5://host:port" />
      <template #footer>
        <div style="display:flex;justify-content:flex-end;gap:8px">
          <button class="btn" @click="showProxyModal = false">取消</button>
          <button class="btn btn-primary" :disabled="proxySaving" @click="saveProxy">保存</button>
        </div>
      </template>
    </NModal>

    <!-- Batch Refresh Usage Modal -->
    <NModal v-model:show="showBatchRefreshModal" title="批量刷新用量" preset="card" style="width:420px">
      <div style="margin-bottom:12px">
        <label>刷新范围：</label>
        <NSelect v-model:value="batchRefreshScope" :options="[{ label: '当前页', value: 'page' }, { label: '全部', value: 'all' }]" size="small" style="width:120px;display:inline-flex" />
      </div>
      <div v-if="batchRefreshProgress.show" style="margin-top:12px">
        <NProgress :percentage="batchRefreshProgress.total ? Math.round(batchRefreshProgress.current / batchRefreshProgress.total * 100) : 0" />
        <p style="margin-top:4px;font-size:12px;color:#999">
          {{ batchRefreshProgress.current }} / {{ batchRefreshProgress.total }} — 成功: {{ batchRefreshProgress.success }}, 失败: {{ batchRefreshProgress.failed }}
        </p>
      </div>
      <template #footer>
        <div style="display:flex;justify-content:flex-end;gap:8px">
          <button class="btn" @click="showBatchRefreshModal = false">取消</button>
          <button class="btn btn-primary" :disabled="batchRefreshing" @click="handleBatchRefreshUsage">
            {{ batchRefreshing ? '刷新中...' : '开始刷新' }}
          </button>
        </div>
      </template>
    </NModal>

    <!-- Detail Modal -->
    <NModal v-model:show="showDetailModal" title="账号详情" preset="card" style="width:560px">
      <div v-if="detailAccount" class="detail-grid">
        <template v-for="col in columns" :key="col.key">
          <div class="detail-label">{{ col.label }}</div>
          <div class="detail-value">
            <template v-if="col.key === 'status'">
              <NTag :type="statusColorMap[detailAccount.status] || 'default'" size="small">
                {{ statusLabelMap[detailAccount.status] || detailAccount.status }}
              </NTag>
            </template>
            <template v-else-if="col.key === 'token' || col.key === 'cookie' || col.key === 'access_token'">
              <span class="token-cell" @click="copyToClipboard(getField(detailAccount, col.field), message)">
                {{ getField(detailAccount, col.field) || '-' }}
              </span>
            </template>
            <template v-else>{{ getField(detailAccount, col.field) || '-' }}</template>
          </div>
        </template>
        <div class="detail-label">错误信息</div>
        <div class="detail-value text-red">{{ detailAccount.error_msg || '-' }}</div>
      </div>
    </NModal>

    <!-- Test Modal -->
    <NModal v-model:show="showTestModal" title="测试账号" preset="card" style="width:600px" @after-leave="stopTest">
      <div v-if="testAccount" class="test-modal-body">
        <div class="test-info">
          <span class="test-info-label">账号 #{{ testAccount.id }}</span>
          <span v-if="testAccount.email" class="test-info-email">{{ testAccount.email }}</span>
          <NTag v-if="testAccount.auth_method" size="small" style="margin-left:6px">{{ testAccount.auth_method }}</NTag>
        </div>
        <div class="test-form">
          <div class="test-form-row">
            <label class="test-label">模型</label>
            <NSelect v-model:value="testModel" :options="testModelOptions" :loading="testModelLoading"
              filterable tag placeholder="选择模型" size="small" style="flex:1" />
          </div>
          <div class="test-form-row">
            <label class="test-label">提示词</label>
            <NInput v-model:value="testPrompt" type="textarea" :rows="3" placeholder="输入测试内容..." size="small" style="flex:1" />
          </div>
        </div>
        <div class="test-output-wrap">
          <div class="test-output-header">
            <span>输出结果</span>
            <div style="display:flex;align-items:center;gap:8px">
              <span v-if="testLoading" class="test-streaming-dot">流式输出中...</span>
              <button v-if="testResult" class="btn-copy" @click="copyToClipboard(testResult, message)">📋 复制</button>
            </div>
          </div>
          <div class="test-output" :class="{ empty: !testResult && !testLoading }">
            <template v-if="testResult">{{ testResult }}</template>
            <template v-else-if="testLoading">等待响应...</template>
            <template v-else>点击"开始测试"发送请求</template>
          </div>
        </div>
      </div>
      <template #footer>
        <div style="display:flex;justify-content:flex-end;gap:8px">
          <button class="btn" @click="showTestModal = false">关闭</button>
          <button v-if="testLoading" class="btn btn-danger" @click="stopTest">停止</button>
          <button v-else class="btn btn-primary" @click="handleTest">开始测试</button>
        </div>
      </template>
    </NModal>
  </div>
</template>

<style scoped>
.accounts-page { padding: 0; }
.channel-tabs { display: flex; gap: 4px; padding: 12px 16px; background: var(--body-color); border-bottom: 1px solid var(--border-color); flex-wrap: wrap; }
.ch-tab { padding: 6px 16px; border: 1px solid var(--border-color); border-radius: 6px; background: transparent; color: var(--text-color-3); cursor: pointer; font-size: 13px; transition: all .2s; }
.ch-tab:hover { border-color: var(--primary-color); color: var(--text-color-2); }
.ch-tab.active { background: var(--primary-color); border-color: var(--primary-color); color: #fff; }

.stats-bar { display: flex; gap: 24px; padding: 12px 16px; background: var(--card-color); border-bottom: 1px solid var(--border-color); }
.stat-item { display: flex; align-items: center; gap: 6px; }
.stat-label { color: var(--text-color-3); font-size: 13px; }
.stat-value { font-size: 16px; font-weight: 600; color: var(--text-color); }
.text-green { color: #10b981; }
.text-red { color: #ef4444; }

.toolbar { display: flex; justify-content: space-between; align-items: center; padding: 10px 16px; gap: 8px; flex-wrap: wrap; }
.toolbar-left, .toolbar-right { display: flex; gap: 8px; align-items: center; flex-wrap: wrap; }

.btn { padding: 5px 14px; border: 1px solid var(--border-color); border-radius: 5px; background: var(--card-color); color: var(--text-color-2); cursor: pointer; font-size: 13px; transition: all .15s; white-space: nowrap; }
.btn:hover { border-color: var(--primary-color); color: var(--text-color); }
.btn:disabled { opacity: .5; cursor: not-allowed; }
.btn-primary { background: #5b6abf; border-color: #5b6abf; color: #fff; }
.btn-primary:hover { background: #6b7acf; }
.btn-green { background: #059669; border-color: #059669; color: #fff; }
.btn-green:hover { background: #10b981; }
.btn-blue { background: #2563eb; border-color: #2563eb; color: #fff; }
.btn-blue:hover { background: #3b82f6; }
.btn-danger { background: #dc2626; border-color: #dc2626; color: #fff; }
.btn-danger:hover { background: #ef4444; }
.btn-warning { background: #d97706; border-color: #d97706; color: #fff; }
.btn-warning:hover { background: #f59e0b; }
.btn-sm { padding: 3px 10px; font-size: 12px; }

.batch-bar { display: flex; align-items: center; gap: 10px; padding: 8px 16px; background: #eef2ff; border-bottom: 1px solid var(--border-color); font-size: 13px; color: #4338ca; }

.table-wrap { overflow-x: auto; position: relative; }
.table-wrap.loading { opacity: .6; pointer-events: none; }
.data-table { width: 100%; border-collapse: collapse; font-size: 13px; }
.data-table th { background: var(--body-color); color: var(--text-color-3); font-weight: 500; padding: 8px 10px; text-align: left; border-bottom: 1px solid var(--border-color); white-space: nowrap; position: sticky; top: 0; z-index: 1; }
.data-table td { padding: 7px 10px; border-bottom: 1px solid var(--border-color); color: var(--text-color); max-width: 200px; overflow: hidden; text-overflow: ellipsis; white-space: nowrap; }
.data-table tr:hover td { background: var(--hover-color); }
.data-table tr.selected td { background: #eef2ff; }
.col-check { width: 36px; text-align: center; }
.empty-row { text-align: center; color: var(--text-color-3); padding: 40px 0 !important; }

.token-cell { cursor: pointer; color: #5b6abf; font-family: monospace; font-size: 12px; }
.token-cell:hover { text-decoration: underline; }
.proxy-cell { cursor: pointer; color: #d97706; font-size: 12px; }
.proxy-cell:hover { text-decoration: underline; }
.plan-badge { display: inline-block; padding: 1px 8px; border-radius: 10px; color: #fff; font-size: 11px; font-weight: 500; }

.btn-link { background: none; border: none; color: #5b6abf; cursor: pointer; font-size: 12px; padding: 2px 6px; }
.btn-link:hover { text-decoration: underline; }
.btn-link:disabled { color: var(--text-color-3); cursor: not-allowed; }
.action-cell { white-space: nowrap; }

.pagination-bar { display: flex; justify-content: flex-end; padding: 12px 16px; }

.oauth-link { color: #5b6abf; word-break: break-all; }
.detail-grid { display: grid; grid-template-columns: 100px 1fr; gap: 8px 12px; }
.detail-label { color: var(--text-color-3); font-size: 13px; text-align: right; }
.detail-value { color: var(--text-color); font-size: 13px; word-break: break-all; }

.add-tabs { display: flex; gap: 0; border-bottom: 1px solid var(--border-color); margin-bottom: 14px; }
.add-tab { padding: 8px 18px; border: none; background: transparent; color: var(--text-color-3); cursor: pointer; font-size: 13px; font-weight: 500; border-bottom: 2px solid transparent; transition: all .15s; }
.add-tab:hover { color: var(--text-color-2); }
.add-tab.active { color: var(--primary-color); border-bottom-color: var(--primary-color); }
.add-tab-content { min-height: 120px; }
.add-hint { color: #999; font-size: 13px; line-height: 1.6; margin-bottom: 4px; }
.format-box { background: var(--body-color); border: 1px solid var(--border-color); border-radius: 6px; padding: 10px 14px; margin-top: 8px; font-size: 12px; color: var(--text-color-2); }
.format-box code { display: block; background: var(--card-color); border: 1px solid var(--border-color); border-radius: 4px; padding: 4px 8px; margin-top: 4px; font-family: monospace; font-size: 11px; color: var(--primary-color); word-break: break-all; }
.format-box p { margin: 0; }
.format-label { display: inline-block; background: var(--primary-color); color: #fff; font-size: 10px; padding: 1px 6px; border-radius: 3px; margin-right: 4px; }

.test-modal-body { display: flex; flex-direction: column; gap: 12px; }
.test-info { display: flex; align-items: center; gap: 8px; font-size: 13px; color: var(--text-color-2); }
.test-info-label { font-weight: 600; color: var(--text-color); }
.test-info-email { color: var(--text-color-3); }
.test-form { display: flex; flex-direction: column; gap: 10px; }
.test-form-row { display: flex; align-items: flex-start; gap: 10px; }
.test-label { width: 50px; font-size: 13px; color: var(--text-color-2); line-height: 28px; flex-shrink: 0; text-align: right; }
.test-output-wrap { margin-top: 4px; }
.test-output-header { display: flex; justify-content: space-between; align-items: center; font-size: 13px; color: var(--text-color-2); margin-bottom: 6px; }
.test-streaming-dot { color: #10b981; font-size: 12px; animation: blink 1s infinite; }
.btn-copy { background: transparent; border: 1px solid var(--border-color); border-radius: 4px; padding: 2px 8px; font-size: 12px; color: var(--text-color-2); cursor: pointer; transition: all .2s; }
.btn-copy:hover { border-color: var(--primary-color); color: var(--primary-color); }
@keyframes blink { 0%, 100% { opacity: 1; } 50% { opacity: .4; } }
.test-output { background: var(--body-color); border: 1px solid var(--border-color); border-radius: 6px; padding: 12px; font-size: 13px; line-height: 1.6; color: var(--text-color); min-height: 120px; max-height: 300px; overflow-y: auto; white-space: pre-wrap; word-break: break-all; }
.test-output.empty { color: var(--text-color-3); font-style: italic; }

.usage-cell { display: flex; flex-direction: column; gap: 2px; min-width: 80px; }
.usage-text { font-size: 12px; font-weight: 500; color: var(--text-color); }
.usage-bar { height: 4px; background: var(--border-color); border-radius: 2px; overflow: hidden; }
.usage-bar-fill { height: 100%; border-radius: 2px; transition: width .3s; }
.usage-remain { font-size: 11px; color: var(--text-color-3); }
</style>
