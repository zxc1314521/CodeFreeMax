<script setup lang="ts">
import { ref, computed, onMounted } from 'vue'
import { useRouter } from 'vue-router'
import { CHANNELS } from '../stores/channels'
import {
  availableChannels, activeChannelId, switchChannel,
  fetchAllChannelStats, channelSummaries
} from '../stores/accounts'
import http from '../utils/http'

const router = useRouter()
const loading = ref(false)

const stats = ref({
  total_accounts: 0,
  active_accounts: 0,
  total_requests: 0,
  success_rate: 100
})

async function fetchStats() {
  loading.value = true
  try {
    const res = await http.get('/api/stats')
    if (res.data.code === 0 && res.data.data) {
      stats.value = { ...stats.value, ...res.data.data }
    }
  } catch {}
  finally { loading.value = false }
}

function goToChannel(chId: string) {
  switchChannel(chId)
  router.push('/accounts')
}

const channelCards = computed(() =>
  availableChannels.value.map(id => {
    const config = CHANNELS[id]
    const summary = channelSummaries.value.find(s => s.channelId === id)
    return {
      id,
      name: config?.name || id,
      color: config?.color || 'gray',
      total: summary?.total || 0,
      normal: summary?.normal || 0,
      abnormal: summary?.abnormal || 0
    }
  })
)

const colorMap: Record<string, string> = {
  amber: '#f59e0b', purple: '#8b5cf6', green: '#10b981',
  indigo: '#6366f1', cyan: '#06b6d4', orange: '#f97316', gray: '#6b7280'
}

const colorBgMap: Record<string, string> = {
  amber: 'rgba(245,158,11,.08)', purple: 'rgba(139,92,246,.08)', green: 'rgba(16,185,129,.08)',
  indigo: 'rgba(99,102,241,.08)', cyan: 'rgba(6,182,212,.08)', orange: 'rgba(249,115,22,.08)', gray: 'rgba(107,114,128,.08)'
}

onMounted(() => { fetchStats(); fetchAllChannelStats() })
</script>

<template>
  <div class="dashboard-page">
    <div class="page-header">
      <h1>仪表盘</h1>
      <p class="page-desc">系统运行状态总览</p>
    </div>

    <!-- Global stats -->
    <div class="global-stats">
      <div class="gs-card">
        <div class="gs-icon gs-icon-default">
          <svg width="20" height="20" viewBox="0 0 20 20" fill="none"><circle cx="10" cy="7" r="3.5" stroke="currentColor" stroke-width="1.5"/><path d="M3.5 17.5C3.5 14 6 11.5 10 11.5C14 11.5 16.5 14 16.5 17.5" stroke="currentColor" stroke-width="1.5" stroke-linecap="round"/></svg>
        </div>
        <div class="gs-info">
          <div class="gs-value">{{ stats.total_accounts }}</div>
          <div class="gs-label">总账号</div>
        </div>
      </div>
      <div class="gs-card">
        <div class="gs-icon gs-icon-green">
          <svg width="20" height="20" viewBox="0 0 20 20" fill="none"><path d="M10 2L12.5 7.5L18 8.5L14 12.5L15 18L10 15.5L5 18L6 12.5L2 8.5L7.5 7.5L10 2Z" stroke="currentColor" stroke-width="1.5" stroke-linejoin="round"/></svg>
        </div>
        <div class="gs-info">
          <div class="gs-value text-green">{{ stats.active_accounts }}</div>
          <div class="gs-label">活跃账号</div>
        </div>
      </div>
      <div class="gs-card">
        <div class="gs-icon gs-icon-blue">
          <svg width="20" height="20" viewBox="0 0 20 20" fill="none"><path d="M3 10L7 14L17 4" stroke="currentColor" stroke-width="1.8" stroke-linecap="round" stroke-linejoin="round"/></svg>
        </div>
        <div class="gs-info">
          <div class="gs-value text-blue">{{ stats.total_requests }}</div>
          <div class="gs-label">总请求数</div>
        </div>
      </div>
      <div class="gs-card">
        <div class="gs-icon gs-icon-purple">
          <svg width="20" height="20" viewBox="0 0 20 20" fill="none"><circle cx="10" cy="10" r="7" stroke="currentColor" stroke-width="1.5"/><path d="M10 6V10.5L13 13" stroke="currentColor" stroke-width="1.5" stroke-linecap="round" stroke-linejoin="round"/></svg>
        </div>
        <div class="gs-info">
          <div class="gs-value text-purple">{{ stats.success_rate }}%</div>
          <div class="gs-label">成功率</div>
        </div>
      </div>
    </div>

    <!-- Channel cards -->
    <div class="section-header">
      <h2 class="section-title">渠道概览</h2>
      <span class="section-count">{{ channelCards.length }} 个渠道</span>
    </div>
    <div class="channel-grid">
      <div v-for="ch in channelCards" :key="ch.id" class="ch-card" @click="goToChannel(ch.id)">
        <div class="ch-card-header">
          <div class="ch-badge" :style="{ background: colorBgMap[ch.color] || colorBgMap.gray, color: colorMap[ch.color] || colorMap.gray }">
            {{ ch.name.charAt(0) }}
          </div>
          <span class="ch-name">{{ ch.name }}</span>
          <svg class="ch-arrow" width="14" height="14" viewBox="0 0 14 14" fill="none"><path d="M5 3L9 7L5 11" stroke="currentColor" stroke-width="1.3" stroke-linecap="round" stroke-linejoin="round"/></svg>
        </div>
        <div class="ch-card-body">
          <div class="ch-stat">
            <span class="ch-stat-val">{{ ch.total }}</span>
            <span class="ch-stat-lbl">总数</span>
          </div>
          <div class="ch-divider"></div>
          <div class="ch-stat">
            <span class="ch-stat-val text-green">{{ ch.normal }}</span>
            <span class="ch-stat-lbl">正常</span>
          </div>
          <div class="ch-divider"></div>
          <div class="ch-stat">
            <span class="ch-stat-val text-red">{{ ch.abnormal }}</span>
            <span class="ch-stat-lbl">异常</span>
          </div>
        </div>
      </div>
    </div>
  </div>
</template>

<style scoped>
.dashboard-page { padding: 24px 28px; }
.page-header { margin-bottom: 24px; }
.page-header h1 { font-size: 20px; font-weight: 700; color: var(--text-color); margin: 0; }
.page-desc { font-size: 13px; color: var(--text-color-3); margin: 4px 0 0; }

.global-stats { display: grid; grid-template-columns: repeat(4, 1fr); gap: 14px; }
.gs-card {
  background: var(--card-color); border: 1px solid var(--border-color);
  border-radius: 10px; padding: 18px 16px;
  display: flex; align-items: center; gap: 14px;
  transition: border-color .15s;
}
.gs-card:hover { border-color: #d0d4da; }
.gs-icon {
  width: 40px; height: 40px; border-radius: 10px;
  display: flex; align-items: center; justify-content: center;
  flex-shrink: 0;
}
.gs-icon-default { background: var(--body-color); color: var(--text-color-2); }
.gs-icon-green { background: rgba(16,185,129,.08); color: #10b981; }
.gs-icon-blue { background: rgba(59,130,246,.08); color: #3b82f6; }
.gs-icon-purple { background: rgba(139,92,246,.08); color: #8b5cf6; }
.gs-info { display: flex; flex-direction: column; }
.gs-value { font-size: 24px; font-weight: 700; color: var(--text-color); line-height: 1.1; }
.gs-label { font-size: 12px; color: var(--text-color-3); margin-top: 3px; }
.text-green { color: #10b981 !important; }
.text-blue { color: #3b82f6 !important; }
.text-purple { color: #8b5cf6 !important; }
.text-red { color: #ef4444 !important; }

.section-header { display: flex; align-items: baseline; gap: 8px; margin: 28px 0 14px; }
.section-title { font-size: 15px; font-weight: 600; color: var(--text-color); margin: 0; }
.section-count { font-size: 12px; color: var(--text-color-3); }

.channel-grid { display: grid; grid-template-columns: repeat(auto-fill, minmax(230px, 1fr)); gap: 14px; }
.ch-card {
  background: var(--card-color); border: 1px solid var(--border-color);
  border-radius: 10px; padding: 16px; cursor: pointer;
  transition: all .15s;
}
.ch-card:hover { border-color: var(--primary-color); box-shadow: 0 2px 8px rgba(91,106,191,.08); }
.ch-card-header { display: flex; align-items: center; gap: 10px; margin-bottom: 16px; }
.ch-badge {
  width: 32px; height: 32px; border-radius: 8px;
  display: flex; align-items: center; justify-content: center;
  font-size: 14px; font-weight: 700; flex-shrink: 0;
}
.ch-name { font-size: 14px; font-weight: 600; color: var(--text-color); flex: 1; }
.ch-arrow { color: var(--text-color-3); opacity: 0; transition: opacity .15s; }
.ch-card:hover .ch-arrow { opacity: 1; }
.ch-card-body { display: flex; justify-content: space-between; align-items: center; }
.ch-stat { display: flex; flex-direction: column; align-items: center; flex: 1; }
.ch-stat-val { font-size: 18px; font-weight: 700; color: var(--text-color); }
.ch-stat-lbl { font-size: 11px; color: var(--text-color-3); margin-top: 2px; }
.ch-divider { width: 1px; height: 28px; background: var(--border-color); }

@media (max-width: 768px) {
  .global-stats { grid-template-columns: repeat(2, 1fr); }
}
</style>
