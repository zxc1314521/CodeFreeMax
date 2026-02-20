<script setup lang="ts">
import { ref, computed, onMounted } from 'vue'
import http from '../utils/http'

interface TutorialChannelItem {
  id: number
  key: string
  name: string
  enabled: boolean
  default_model: string
  claude_protocol: boolean
  openai_protocol: boolean
  sort_order: number
}

interface TutorialExampleItem {
  id: number
  channel_key: string
  protocol: string
  tab_key: string
  tab_label: string
  content: string
  sort_order: number
}

const protocolTab = ref('openai')
const selectedClaudeChannel = ref('')
const selectedOpenaiChannel = ref('grok')
const grokTab = ref('chat')
const loading = ref(false)
const channels = ref<TutorialChannelItem[]>([])
const examples = ref<TutorialExampleItem[]>([])

const baseUrl = computed(() => window.location.origin)

// Default fallback data when API is unavailable
const defaultChannels: TutorialChannelItem[] = [
  { id: 1, key: 'kiro', name: 'Kiro', enabled: true, default_model: 'claude-sonnet-4-5', claude_protocol: true, openai_protocol: true, sort_order: 1 },
  { id: 2, key: 'orchids', name: 'Orchids', enabled: true, default_model: 'claude-sonnet-4-5', claude_protocol: true, openai_protocol: true, sort_order: 2 },
  { id: 3, key: 'antigravity', name: 'Antigravity', enabled: true, default_model: 'gemini-2.5-flash-preview', claude_protocol: true, openai_protocol: true, sort_order: 3 },
  { id: 4, key: 'cursor', name: 'Cursor', enabled: true, default_model: 'claude-4.5-sonnet', claude_protocol: false, openai_protocol: true, sort_order: 4 },
  { id: 5, key: 'warp', name: 'Warp', enabled: true, default_model: 'claude-4-5-sonnet', claude_protocol: true, openai_protocol: true, sort_order: 5 },
  { id: 6, key: 'claude_api', name: 'Claude API', enabled: true, default_model: 'claude-sonnet-4-5', claude_protocol: true, openai_protocol: false, sort_order: 6 },
  { id: 7, key: 'grok', name: 'Grok', enabled: true, default_model: 'grok-4.1-fast', claude_protocol: false, openai_protocol: true, sort_order: 7 },
]

function makeClaudeExample(channelKey: string, model: string): string {
  return `curl -X POST {baseUrl}/${channelKey}/v1/messages \\
  -H "Content-Type: application/json" \\
  -H "x-api-key: YOUR_API_KEY" \\
  -d '{
    "model": "${model}",
    "max_tokens": 4096,
    "stream": true,
    "messages": [
      {"role": "user", "content": "Hello, who are you?"}
    ]
  }'`
}

function makeOpenaiExample(channelKey: string, model: string): string {
  return `curl -X POST {baseUrl}/${channelKey}/v1/chat/completions \\
  -H "Content-Type: application/json" \\
  -H "Authorization: Bearer YOUR_API_KEY" \\
  -d '{
    "model": "${model}",
    "stream": true,
    "messages": [
      {"role": "user", "content": "Hello, who are you?"}
    ]
  }'`
}

const defaultExamples: TutorialExampleItem[] = [
  // Claude protocol
  { id: 1, channel_key: 'kiro', protocol: 'claude', tab_key: '', tab_label: '', content: makeClaudeExample('kiro', 'claude-sonnet-4-5'), sort_order: 1 },
  { id: 2, channel_key: 'warp', protocol: 'claude', tab_key: '', tab_label: '', content: makeClaudeExample('warp', 'claude-4-5-sonnet'), sort_order: 2 },
  { id: 3, channel_key: 'antigravity', protocol: 'claude', tab_key: '', tab_label: '', content: makeClaudeExample('antigravity', 'gemini-2.5-flash-preview'), sort_order: 3 },
  { id: 4, channel_key: 'orchids', protocol: 'claude', tab_key: '', tab_label: '', content: makeClaudeExample('orchids', 'claude-sonnet-4-5'), sort_order: 4 },
  { id: 5, channel_key: 'claude_api', protocol: 'claude', tab_key: '', tab_label: '', content: makeClaudeExample('claude_api', 'claude-sonnet-4-5'), sort_order: 5 },
  // OpenAI protocol
  { id: 6, channel_key: 'kiro', protocol: 'openai', tab_key: '', tab_label: '', content: makeOpenaiExample('kiro', 'claude-sonnet-4-5'), sort_order: 1 },
  { id: 7, channel_key: 'warp', protocol: 'openai', tab_key: '', tab_label: '', content: makeOpenaiExample('warp', 'claude-4-5-sonnet'), sort_order: 2 },
  { id: 8, channel_key: 'antigravity', protocol: 'openai', tab_key: '', tab_label: '', content: makeOpenaiExample('antigravity', 'gemini-2.5-flash-preview'), sort_order: 3 },
  { id: 9, channel_key: 'orchids', protocol: 'openai', tab_key: '', tab_label: '', content: makeOpenaiExample('orchids', 'claude-sonnet-4-5'), sort_order: 4 },
  { id: 10, channel_key: 'cursor', protocol: 'openai', tab_key: '', tab_label: '', content: makeOpenaiExample('cursor', 'claude-4.5-sonnet'), sort_order: 5 },
  // Grok sub-tabs
  { id: 11, channel_key: 'grok', protocol: 'openai', tab_key: 'chat', tab_label: '文字对话', content: `# Grok 文字对话
# 端点: /grok/v1/chat/completions
# 模型: grok-3, grok-4, grok-4.1-fast, grok-4.1-thinking 等

curl -X POST {baseUrl}/grok/v1/chat/completions \\
  -H "Content-Type: application/json" \\
  -H "Authorization: Bearer YOUR_API_KEY" \\
  -d '{
    "model": "grok-4.1-fast",
    "stream": true,
    "messages": [
      {"role": "system", "content": "你是一个专业的 AI 助手"},
      {"role": "user", "content": "请用 Python 写一个快速排序算法"}
    ]
  }'`, sort_order: 1 },
  { id: 12, channel_key: 'grok', protocol: 'openai', tab_key: 'image', tab_label: '图片生成', content: `# Grok 图片生成
# 支持两种方式: 图片 API 或 Chat API
# 参数: n (生成数量 1-10, 流式仅支持 1-2)

# 方式 1: 图片生成 API
# 端点: /grok/v1/images/generations
curl -X POST {baseUrl}/grok/v1/images/generations \\
  -H "Content-Type: application/json" \\
  -H "Authorization: Bearer YOUR_API_KEY" \\
  -d '{
    "prompt": "一只赛博朋克风格机器猫，站在城市天际线前",
    "n": 2,
    "stream": true
  }'

# 方式 2: Chat API + 图片模型
# 模型: grok-imagine-1.0
curl -X POST {baseUrl}/grok/v1/chat/completions \\
  -H "Content-Type: application/json" \\
  -H "Authorization: Bearer YOUR_API_KEY" \\
  -d '{
    "model": "grok-imagine-1.0",
    "stream": true,
    "n": 2,
    "messages": [
      {"role": "user", "content": "一只赛博朋克风格机器猫"}
    ]
  }'`, sort_order: 2 },
  { id: 13, channel_key: 'grok', protocol: 'openai', tab_key: 'video', tab_label: '视频生成', content: `# Grok 视频生成 (文生视频)
# 参数: aspect_ratio (16:9/9:16/1:1), duration (6/10秒), resolution (480p/720p)

# 方式 1: 视频生成 API
# 端点: /grok/v1/videos/generations
curl -X POST {baseUrl}/grok/v1/videos/generations \\
  -H "Content-Type: application/json" \\
  -H "Authorization: Bearer YOUR_API_KEY" \\
  -d '{
    "prompt": "一只柯基犬在花园里奔跑，阳光明媚，慢动作",
    "aspect_ratio": "16:9",
    "duration": 10,
    "resolution": "720p",
    "stream": true
  }'

# 方式 2: Chat API + 视频模型
# 模型: grok-imagine-1.0-video
curl -X POST {baseUrl}/grok/v1/chat/completions \\
  -H "Content-Type: application/json" \\
  -H "Authorization: Bearer YOUR_API_KEY" \\
  -d '{
    "model": "grok-imagine-1.0-video",
    "stream": true,
    "video_aspect_ratio": "9:16",
    "video_duration": 6,
    "video_resolution": "720p",
    "messages": [
      {"role": "user", "content": "海浪拍打码头，夕阳西下"}
    ]
  }'`, sort_order: 3 },
  { id: 14, channel_key: 'grok', protocol: 'openai', tab_key: 'image2video', tab_label: '图生视频', content: `# Grok 图生视频 (图片动起来)
# 模型: grok-imagine-1.0-video
# 图片支持 URL 或 base64

# 使用图片 URL
curl -X POST {baseUrl}/grok/v1/chat/completions \\
  -H "Content-Type: application/json" \\
  -H "Authorization: Bearer YOUR_API_KEY" \\
  -d '{
    "model": "grok-imagine-1.0-video",
    "stream": true,
    "video_aspect_ratio": "1:1",
    "video_duration": 6,
    "video_resolution": "480p",
    "messages": [
      {
        "role": "user",
        "content": [
          {"type": "image_url", "image_url": {"url": "https://example.com/image.jpg"}},
          {"type": "text", "text": "让这只猫慢慢转过头来"}
        ]
      }
    ]
  }'`, sort_order: 4 },
]

function replaceBaseUrl(content: string): string {
  return content.replace(/\{baseUrl\}/g, baseUrl.value)
}

async function fetchData() {
  loading.value = true
  try {
    const res = (await http.get('/api/tutorial/channels')).data
    if (res.code === 0 && res.data) {
      channels.value = res.data.channels?.length ? res.data.channels : defaultChannels
      examples.value = res.data.examples?.length ? res.data.examples : defaultExamples
    } else {
      channels.value = defaultChannels
      examples.value = defaultExamples
    }
  } catch (e) {
    console.error('Failed to fetch tutorial data, using defaults:', e)
    channels.value = defaultChannels
    examples.value = defaultExamples
  } finally {
    loading.value = false
  }
}

onMounted(() => { fetchData() })

const channelList = computed(() =>
  channels.value.filter(ch => ch.enabled).map(ch => ({
    key: ch.key,
    name: ch.name,
    defaultModel: ch.default_model,
    claudeProtocol: ch.claude_protocol,
    openaiProtocol: ch.openai_protocol
  }))
)

const claudeChannels = computed(() => {
  const list = channelList.value.filter(ch => ch.claudeProtocol)
  if (list.length > 0 && !selectedClaudeChannel.value) {
    selectedClaudeChannel.value = list[0].key
  }
  return list
})

const openaiChannels = computed(() => channelList.value.filter(ch => ch.openaiProtocol))

const currentClaudeChannel = computed(() =>
  claudeChannels.value.find(ch => ch.key === selectedClaudeChannel.value) || claudeChannels.value[0]
)

const currentOpenaiChannel = computed(() =>
  openaiChannels.value.find(ch => ch.key === selectedOpenaiChannel.value) || openaiChannels.value[0]
)

const isGrokSelected = computed(() => selectedOpenaiChannel.value === 'grok')

function getClaudeExample(channelKey: string): string {
  const ex = examples.value.find(e => e.channel_key === channelKey && e.protocol === 'claude')
  return ex ? replaceBaseUrl(ex.content) : ''
}

function getOpenaiExample(channelKey: string): string {
  const ex = examples.value.find(e => e.channel_key === channelKey && e.protocol === 'openai' && !e.tab_key)
  return ex ? replaceBaseUrl(ex.content) : ''
}

const grokTabs = computed(() => {
  return examples.value
    .filter(e => e.channel_key === 'grok' && e.protocol === 'openai' && e.tab_key)
    .sort((a, b) => a.sort_order - b.sort_order)
    .map(e => ({ key: e.tab_key, label: e.tab_label }))
})

const grokExamples = computed<Record<string, string>>(() => {
  const result: Record<string, string> = {}
  examples.value
    .filter(e => e.channel_key === 'grok' && e.protocol === 'openai' && e.tab_key)
    .forEach(e => { result[e.tab_key] = replaceBaseUrl(e.content) })
  return result
})
</script>

<template>
  <div class="tutorial-page">
    <h2 class="page-title">使用教程</h2>
    <p class="page-desc">了解如何使用 API 接口</p>

    <!-- API 地址格式 -->
    <div class="card">
      <h3 class="card-title">
        <span class="card-icon icon-link">
          <svg width="14" height="14" viewBox="0 0 14 14" fill="none"><path d="M6 8L8 6M5 9L3.5 10.5C2.7 11.3 2.7 12.6 3.5 13.4V13.4C4.3 14.2 5.6 14.2 6.4 13.4L8 11.8M8 5L9.5 3.5C10.3 2.7 11.6 2.7 12.4 3.5V3.5C13.2 4.3 13.2 5.6 12.4 6.4L10.8 8" stroke="currentColor" stroke-width="1.3" stroke-linecap="round"/></svg>
        </span>
        API 地址格式
      </h3>
      <div class="api-format">{{ baseUrl }}/{渠道}/v1</div>
      <div class="warning-box">
        <svg class="warning-icon" width="16" height="16" viewBox="0 0 16 16" fill="none"><path d="M8 1L15 14H1L8 1Z" stroke="currentColor" stroke-width="1.3" stroke-linejoin="round"/><path d="M8 6V9M8 11.5V11" stroke="currentColor" stroke-width="1.3" stroke-linecap="round"/></svg>
        <div>
          <strong>Claude Code 用户注意：</strong>配置 API 地址时请使用
          <code class="code-inline">{{ baseUrl }}/{渠道}</code>，
          <strong class="text-danger">不要</strong>添加
          <code class="code-inline code-danger">/v1</code> 后缀
        </div>
      </div>

      <!-- 渠道表格 -->
      <div class="table-wrap">
        <table class="data-table">
          <thead>
            <tr>
              <th>渠道</th>
              <th>API 地址</th>
              <th>默认模型</th>
              <th>支持协议</th>
            </tr>
          </thead>
          <tbody>
            <tr v-for="ch in channelList" :key="ch.key">
              <td><span class="badge badge-amber">{{ ch.name }}</span></td>
              <td><code class="code-primary">{{ baseUrl }}/{{ ch.key }}/v1</code></td>
              <td><code class="code-green">{{ ch.defaultModel }}</code></td>
              <td>
                <span v-if="ch.claudeProtocol" class="badge badge-green">Claude</span>
                <span v-if="ch.openaiProtocol" class="badge badge-amber">OpenAI</span>
              </td>
            </tr>
          </tbody>
        </table>
      </div>
    </div>

    <!-- 协议示例 -->
    <div class="card">
      <h3 class="card-title">
        <span class="card-icon icon-code">
          <svg width="14" height="14" viewBox="0 0 14 14" fill="none"><path d="M4.5 3.5L1 7L4.5 10.5M9.5 3.5L13 7L9.5 10.5" stroke="currentColor" stroke-width="1.3" stroke-linecap="round" stroke-linejoin="round"/></svg>
        </span>
        协议示例
      </h3>

      <div class="tab-bar">
        <button v-if="claudeChannels.length > 0"
          @click="protocolTab = 'claude'"
          :class="['tab-btn', { active: protocolTab === 'claude' }]">
          Claude 协议
        </button>
        <button v-if="openaiChannels.length > 0"
          @click="protocolTab = 'openai'"
          :class="['tab-btn', { active: protocolTab === 'openai' }]">
          OpenAI 协议
        </button>
      </div>

      <!-- Claude 协议 -->
      <div v-if="protocolTab === 'claude' && claudeChannels.length > 0">
        <div class="endpoint-info">
          端点: <code class="code-inline">/{渠道}/v1/messages</code>
        </div>
        <p class="auth-info">
          使用 <code class="code-inline">x-api-key</code> 请求头进行认证
        </p>
        <div class="channel-tabs">
          <button v-for="ch in claudeChannels" :key="ch.key"
            @click="selectedClaudeChannel = ch.key"
            :class="['ch-tab', { active: selectedClaudeChannel === ch.key }]">
            {{ ch.name }}
          </button>
        </div>
        <pre v-if="currentClaudeChannel" class="code-block">{{ getClaudeExample(currentClaudeChannel.key) }}</pre>
      </div>

      <!-- OpenAI 协议 -->
      <div v-if="protocolTab === 'openai' && openaiChannels.length > 0">
        <div class="endpoint-info">
          端点: <code class="code-inline">/{渠道}/v1/chat/completions</code>
        </div>
        <p class="auth-info">
          使用 <code class="code-inline">Authorization: Bearer YOUR_API_KEY</code> 请求头进行认证
        </p>
        <div class="channel-tabs">
          <button v-for="ch in openaiChannels" :key="ch.key"
            @click="selectedOpenaiChannel = ch.key; grokTab = 'chat'"
            :class="['ch-tab', { active: selectedOpenaiChannel === ch.key }, ch.key === 'grok' && selectedOpenaiChannel === ch.key ? 'grok-active' : '']">
            {{ ch.name }}
          </button>
        </div>

        <!-- Grok 子标签 -->
        <div v-if="isGrokSelected">
          <div class="grok-tabs">
            <button v-for="tab in grokTabs" :key="tab.key"
              @click="grokTab = tab.key"
              :class="['grok-tab', { active: grokTab === tab.key }]">
              {{ tab.label }}
            </button>
          </div>
          <pre class="code-block">{{ grokExamples[grokTab] }}</pre>
        </div>
        <pre v-else-if="currentOpenaiChannel" class="code-block">{{ getOpenaiExample(currentOpenaiChannel.key) }}</pre>
      </div>
    </div>

    <!-- 使用说明 -->
    <div class="card">
      <h3 class="card-title">
        <span class="card-icon icon-tip">
          <svg width="14" height="14" viewBox="0 0 14 14" fill="none"><circle cx="7" cy="6" r="4.5" stroke="currentColor" stroke-width="1.3"/><path d="M5.5 11H8.5M6 10V8.5C6 8 5 7.5 5 6C5 4.9 5.9 4 7 4C8.1 4 9 4.9 9 6C9 7.5 8 8 8 8.5V10" stroke="currentColor" stroke-width="1.3" stroke-linecap="round" stroke-linejoin="round"/></svg>
        </span>
        使用说明
      </h3>
      <ul class="tips-list">
        <li><strong>API Key</strong>：请在配置管理中设置 API Key，用于接口认证</li>
        <li><strong>模型列表</strong>：可在模型管理中查看各渠道支持的模型</li>
        <li><strong>流式输出</strong>：设置 <code class="code-inline">stream: true</code> 启用流式响应</li>
        <li><strong>系统提示词</strong>：OpenAI 协议支持 <code class="code-inline">role: "system"</code> 消息</li>
      </ul>
    </div>
  </div>
</template>

<style scoped>
.tutorial-page { padding: 20px 24px; }
.page-title { font-size: 20px; font-weight: 600; color: var(--text-color); margin-bottom: 4px; }
.page-desc { font-size: 13px; color: var(--text-color-3); margin-bottom: 20px; }

.card {
  background: var(--card-color);
  border: 1px solid var(--border-color);
  border-radius: 12px;
  padding: 20px 24px;
  margin-bottom: 16px;
}
.card-title {
  font-size: 15px;
  font-weight: 600;
  color: var(--text-color);
  margin-bottom: 16px;
  display: flex;
  align-items: center;
  gap: 8px;
}
.card-icon {
  width: 28px;
  height: 28px;
  border-radius: 8px;
  display: flex;
  align-items: center;
  justify-content: center;
  font-size: 14px;
  color: var(--primary-color);
  background: var(--primary-color-light, rgba(91,106,191,.12));
}

.api-format {
  padding: 10px 14px;
  background: var(--body-color);
  border-radius: 8px;
  font-family: monospace;
  font-size: 13px;
  color: var(--text-color);
  margin-bottom: 12px;
}

.warning-box {
  display: flex;
  align-items: flex-start;
  gap: 8px;
  padding: 10px 14px;
  background: rgba(245,158,11,.06);
  border: 1px solid rgba(245,158,11,.2);
  border-radius: 8px;
  margin-bottom: 16px;
  font-size: 13px;
  color: var(--text-color-2);
}
.warning-icon { flex-shrink: 0; margin-top: 1px; color: #f59e0b; }
.text-danger { color: var(--error-color, #d93025); }

.code-inline {
  background: var(--body-color);
  padding: 1px 6px;
  border-radius: 4px;
  font-family: monospace;
  font-size: 12px;
}
.code-danger {
  background: rgba(217,48,37,.08);
  color: var(--error-color, #d93025);
}
.code-primary {
  font-family: monospace;
  font-size: 12px;
  color: var(--primary-color);
}
.code-green {
  font-family: monospace;
  font-size: 12px;
  color: #059669;
}

/* Table */
.table-wrap { overflow-x: auto; }
.data-table { width: 100%; border-collapse: collapse; font-size: 13px; }
.data-table th {
  background: var(--body-color);
  color: var(--text-color-3);
  font-weight: 500;
  padding: 8px 12px;
  text-align: left;
  border-bottom: 1px solid var(--border-color);
  font-size: 12px;
  text-transform: uppercase;
}
.data-table td {
  padding: 10px 12px;
  border-bottom: 1px solid var(--border-color);
  color: var(--text-color);
}
.data-table tr:hover td { background: var(--hover-color); }

.badge {
  display: inline-block;
  padding: 2px 10px;
  font-size: 12px;
  font-weight: 500;
  border-radius: 12px;
  margin-right: 4px;
}
.badge-amber { background: rgba(245,158,11,.1); color: #d97706; }
.badge-green { background: rgba(16,185,129,.1); color: #059669; }

/* Tabs */
.tab-bar {
  display: flex;
  gap: 4px;
  background: var(--body-color);
  border-radius: 8px;
  padding: 4px;
  margin-bottom: 16px;
  width: fit-content;
}
.tab-btn {
  padding: 6px 16px;
  font-size: 13px;
  font-weight: 500;
  border-radius: 6px;
  border: none;
  background: transparent;
  color: var(--text-color-3);
  cursor: pointer;
  transition: all .2s;
}
.tab-btn:hover { color: var(--text-color); }
.tab-btn.active {
  background: var(--card-color);
  color: var(--primary-color);
  box-shadow: 0 1px 3px rgba(0,0,0,.08);
}

.endpoint-info {
  font-size: 13px;
  color: var(--text-color-3);
  margin-bottom: 6px;
}
.auth-info {
  font-size: 13px;
  color: var(--text-color-3);
  margin-bottom: 12px;
}

/* Channel sub-tabs */
.channel-tabs {
  display: flex;
  gap: 6px;
  margin-bottom: 12px;
  overflow-x: auto;
  padding-bottom: 4px;
}
.ch-tab {
  padding: 4px 12px;
  font-size: 12px;
  font-weight: 500;
  border-radius: 6px;
  border: 1px solid var(--border-color);
  background: var(--card-color);
  color: var(--text-color-3);
  cursor: pointer;
  transition: all .15s;
  white-space: nowrap;
}
.ch-tab:hover { border-color: var(--primary-color); color: var(--text-color); }
.ch-tab.active {
  background: rgba(91, 106, 191, 0.1);
  color: var(--primary-color);
  border-color: rgba(91, 106, 191, 0.3);
}
.ch-tab.grok-active {
  background: rgba(249, 115, 22, 0.1);
  color: #ea580c;
  border-color: rgba(249, 115, 22, 0.3);
}

/* Grok sub-tabs */
.grok-tabs {
  display: flex;
  gap: 4px;
  background: rgba(249, 115, 22, 0.08);
  border-radius: 8px;
  padding: 4px;
  margin-bottom: 12px;
  width: fit-content;
}
.grok-tab {
  padding: 5px 12px;
  font-size: 12px;
  font-weight: 500;
  border-radius: 6px;
  border: none;
  background: transparent;
  color: #c2410c;
  cursor: pointer;
  transition: all .2s;
}
.grok-tab:hover { color: #ea580c; }
.grok-tab.active {
  background: var(--card-color);
  color: #ea580c;
  box-shadow: 0 1px 3px rgba(0,0,0,.08);
}

/* Code block */
.code-block {
  background: var(--body-color);
  color: var(--text-color);
  padding: 16px;
  border-radius: 8px;
  overflow-x: auto;
  overflow-y: auto;
  max-height: 400px;
  font-family: 'Menlo', 'Monaco', 'Courier New', monospace;
  font-size: 12px;
  line-height: 1.6;
  border: 1px solid var(--border-color);
  margin: 0;
  white-space: pre;
}

/* Tips */
.tips-list {
  list-style: none;
  padding: 0;
  margin: 0;
}
.tips-list li {
  position: relative;
  padding: 6px 0 6px 16px;
  font-size: 13px;
  color: var(--text-color-3);
}
.tips-list li::before {
  content: '';
  position: absolute;
  left: 0;
  top: 14px;
  width: 6px;
  height: 6px;
  border-radius: 50%;
  background: var(--primary-color);
}
.tips-list li strong { color: var(--text-color); }
</style>
