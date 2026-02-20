// 渠道配置定义
export interface ChannelColumn {
  key: string
  label: string
  width?: string
  minWidth?: string
  type: string
  field?: string | string[]
  align?: string
  copyable?: boolean
}

export interface ChannelOAuth {
  enabled: boolean
  type?: string
  authorizeUrl: string
  statusUrl: string
  buttonText: string
}

export interface ChannelConfig {
  id: string
  name: string
  enabled: boolean
  color: string
  apiBase: string
  tokenFieldName: string
  tokenFieldLabel: string
  tokenPlaceholder: string
  batchTokenFieldName: string
  hasUsageInfo: boolean
  claudeProtocol: boolean
  openaiProtocol: boolean
  defaultModel: string
  requiresPermission?: boolean
  oauth?: ChannelOAuth
  columns: ChannelColumn[]
}

export const CHANNELS: Record<string, ChannelConfig> = {
  kiro: {
    id: 'kiro',
    name: 'Kiro',
    enabled: true,
    color: 'amber',
    apiBase: '/api/kiro/account',
    tokenFieldName: 'refreshToken',
    tokenFieldLabel: 'RefreshToken',
    tokenPlaceholder: '请粘贴 Kiro 的 RefreshToken，支持批量添加（一行一个）\n\n支持两种格式:\n1. 纯Token格式: refreshToken\n2. IDC格式: refreshToken----clientId----clientSecret----region',
    batchTokenFieldName: 'refreshTokens',
    hasUsageInfo: true,
    claudeProtocol: true,
    openaiProtocol: true,
    defaultModel: 'claude-sonnet-4-5',
    oauth: {
      enabled: true,
      type: 'device_code',
      authorizeUrl: '/api/kiro/oauth/authorize',
      statusUrl: '/api/kiro/oauth/status',
      buttonText: 'AWS IDC 授权登录'
    },
    columns: [
      { key: 'id', label: 'ID', width: '60px', type: 'text', field: 'id' },
      { key: 'auth_method', label: '类型', width: '70px', type: 'text', field: 'auth_method' },
      { key: 'email', label: '邮箱', minWidth: '180px', type: 'email', field: 'email', copyable: true },
      { key: 'token', label: 'Token', minWidth: '200px', type: 'token', field: 'access_token', copyable: true },
      { key: 'plan_type', label: '订阅', width: '80px', type: 'plan', field: 'plan_type' },
      { key: 'usage', label: '用量', width: '160px', type: 'usage' },
      { key: 'status', label: '状态', width: '120px', minWidth: '120px', type: 'status', field: 'status' },
      { key: 'usage_count', label: '调用', width: '60px', align: 'center', type: 'text', field: 'usage_count' },
      { key: 'last_used_at', label: '最后调用', width: '100px', type: 'date', field: 'last_used_at' },
      { key: 'reset_date', label: '重置日期', width: '90px', type: 'text', field: 'reset_date' },
      { key: 'proxy', label: '代理', width: '90px', type: 'text', field: 'proxy', copyable: true },
      { key: 'actions', label: '操作', width: '120px', align: 'center', type: 'actions' }
    ]
  },
  orchids: {
    id: 'orchids',
    name: 'Orchids',
    enabled: true,
    color: 'purple',
    apiBase: '/api/orchids/account',
    tokenFieldName: 'clientJwt',
    tokenFieldLabel: 'ClientJwt',
    tokenPlaceholder: '请粘贴 Orchids 的 ClientJwt，支持批量添加（一行一个）',
    batchTokenFieldName: 'clientJwts',
    hasUsageInfo: false,
    claudeProtocol: true,
    openaiProtocol: true,
    defaultModel: 'claude-sonnet-4-5',
    columns: [
      { key: 'id', label: 'ID', width: '60px', type: 'text', field: 'id' },
      { key: 'token', label: 'Token', minWidth: '200px', type: 'token', field: 'token', copyable: true },
      { key: 'status', label: '状态', width: '120px', minWidth: '120px', type: 'status', field: 'status' },
      { key: 'usage_count', label: '调用', width: '60px', align: 'center', type: 'text', field: 'usage_count' },
      { key: 'last_used_at', label: '最后调用', width: '100px', type: 'date', field: 'last_used_at' },
      { key: 'proxy', label: '代理', width: '90px', type: 'text', field: 'proxy', copyable: true },
      { key: 'actions', label: '操作', width: '120px', align: 'center', type: 'actions' }
    ]
  },
  antigravity: {
    id: 'antigravity',
    name: 'Antigravity',
    enabled: true,
    color: 'green',
    apiBase: '/api/antigravity/account',
    tokenFieldName: 'refreshToken',
    tokenFieldLabel: 'RefreshToken',
    tokenPlaceholder: '请粘贴 Antigravity 的 RefreshToken，支持批量添加（一行一个）',
    batchTokenFieldName: 'refreshTokens',
    hasUsageInfo: false,
    claudeProtocol: true,
    openaiProtocol: true,
    defaultModel: 'gemini-2.5-flash-preview',
    oauth: {
      enabled: true,
      authorizeUrl: '/oauth/antigravity/authorize',
      statusUrl: '/oauth/antigravity/status',
      buttonText: 'Google 授权登录'
    },
    columns: [
      { key: 'id', label: 'ID', width: '60px', type: 'text', field: 'id' },
      { key: 'email', label: '邮箱', minWidth: '180px', type: 'email', field: 'email', copyable: true },
      { key: 'project_id', label: 'Project ID', minWidth: '120px', type: 'text', field: 'project_id', copyable: true },
      { key: 'plan_type', label: '订阅', width: '70px', type: 'plan', field: 'plan_type' },
      { key: 'token', label: 'Token', minWidth: '200px', type: 'token', field: ['id_token', 'token'], copyable: true },
      { key: 'status', label: '状态', width: '120px', minWidth: '120px', type: 'status', field: 'status' },
      { key: 'usage_count', label: '调用', width: '60px', align: 'center', type: 'text', field: 'usage_count' },
      { key: 'last_used_at', label: '最后调用', width: '100px', type: 'date', field: 'last_used_at' },
      { key: 'proxy', label: '代理', width: '90px', type: 'text', field: 'proxy', copyable: true },
      { key: 'actions', label: '操作', width: '120px', align: 'center', type: 'actions' }
    ]
  },
  cursor: {
    id: 'cursor',
    name: 'Cursor',
    enabled: true,
    color: 'indigo',
    apiBase: '/api/cursor/account',
    tokenFieldName: 'token',
    tokenFieldLabel: 'Session Token',
    tokenPlaceholder: '请粘贴 Cursor 的 WorkosCursorSessionToken，支持批量添加（一行一个）',
    batchTokenFieldName: 'tokens',
    hasUsageInfo: false,
    claudeProtocol: false,
    openaiProtocol: true,
    defaultModel: 'claude-4.5-sonnet',
    columns: [
      { key: 'id', label: 'ID', width: '60px', type: 'text', field: 'id' },
      { key: 'email', label: '邮箱', minWidth: '180px', type: 'email', field: 'email', copyable: true },
      { key: 'plan_type', label: '订阅', width: '70px', type: 'plan', field: 'plan_type' },
      { key: 'token', label: 'Token', minWidth: '200px', type: 'token', field: 'token', copyable: true },
      { key: 'status', label: '状态', width: '120px', minWidth: '120px', type: 'status', field: 'status' },
      { key: 'usage_count', label: '调用', width: '60px', align: 'center', type: 'text', field: 'usage_count' },
      { key: 'last_used_at', label: '最后调用', width: '100px', type: 'date', field: 'last_used_at' },
      { key: 'proxy', label: '代理', width: '90px', type: 'text', field: 'proxy', copyable: true },
      { key: 'actions', label: '操作', width: '120px', align: 'center', type: 'actions' }
    ]
  },
  warp: {
    id: 'warp',
    name: 'Warp',
    enabled: true,
    color: 'cyan',
    apiBase: '/api/warp/account',
    tokenFieldName: 'refresh_token',
    tokenFieldLabel: 'RefreshToken',
    tokenPlaceholder: '请粘贴 Warp 的 Firebase RefreshToken，支持批量添加（一行一个）',
    batchTokenFieldName: 'refresh_tokens',
    hasUsageInfo: false,
    claudeProtocol: true,
    openaiProtocol: true,
    defaultModel: 'claude-4-5-sonnet',
    columns: [
      { key: 'id', label: 'ID', width: '60px', type: 'text', field: 'id' },
      { key: 'token', label: 'Token', minWidth: '200px', type: 'token', field: 'id_token', copyable: true },
      { key: 'usage', label: '用量', width: '160px', type: 'usage' },
      { key: 'status', label: '状态', width: '120px', minWidth: '120px', type: 'status', field: 'status' },
      { key: 'usage_count', label: '调用', width: '60px', align: 'center', type: 'text', field: 'usage_count' },
      { key: 'last_used_at', label: '最后调用', width: '100px', type: 'date', field: 'last_used_at' },
      { key: 'proxy', label: '代理', width: '90px', type: 'text', field: 'proxy', copyable: true },
      { key: 'actions', label: '操作', width: '120px', align: 'center', type: 'actions' }
    ]
  },
  claude_api: {
    id: 'claude_api',
    name: 'Claude API',
    enabled: true,
    color: 'amber',
    apiBase: '/api/claude_api/account',
    tokenFieldName: 'session_key',
    tokenFieldLabel: 'SessionKey',
    tokenPlaceholder: '请粘贴 Claude 的 SessionKey (sk-ant-sid 开头)，支持批量添加（一行一个）',
    batchTokenFieldName: 'session_keys',
    hasUsageInfo: false,
    claudeProtocol: true,
    openaiProtocol: false,
    defaultModel: 'claude-sonnet-4-5',
    requiresPermission: true,
    columns: [
      { key: 'id', label: 'ID', width: '60px', type: 'text', field: 'id' },
      { key: 'email', label: '邮箱', minWidth: '180px', type: 'email', field: 'email', copyable: true },
      { key: 'org_id', label: 'OrgId', minWidth: '120px', type: 'text', field: 'org_id', copyable: true },
      { key: 'plan_type', label: '订阅', width: '80px', type: 'plan', field: 'plan_type' },
      { key: 'token_expiry', label: 'Token过期', width: '120px', type: 'expire', field: 'token_expiry' },
      { key: 'status', label: '状态', width: '120px', minWidth: '120px', type: 'status', field: 'status' },
      { key: 'usage_count', label: '调用', width: '60px', align: 'center', type: 'text', field: 'usage_count' },
      { key: 'last_used_at', label: '最后调用', width: '100px', type: 'date', field: 'last_used_at' },
      { key: 'proxy', label: '代理', width: '90px', type: 'text', field: 'proxy', copyable: true },
      { key: 'actions', label: '操作', width: '120px', align: 'center', type: 'actions' }
    ]
  },
  grok: {
    id: 'grok',
    name: 'Grok',
    enabled: true,
    color: 'orange',
    apiBase: '/api/grok/account',
    tokenFieldName: 'ssoToken',
    tokenFieldLabel: 'SSO Token',
    tokenPlaceholder: '请粘贴 Grok 的 SSO Cookie 值，支持批量添加（一行一个）',
    batchTokenFieldName: 'ssoTokens',
    hasUsageInfo: true,
    claudeProtocol: false,
    openaiProtocol: true,
    defaultModel: 'grok-4.1-fast',
    columns: [
      { key: 'id', label: 'ID', width: '60px', type: 'text', field: 'id' },
      { key: 'token', label: 'Token', minWidth: '200px', type: 'token', field: 'token', copyable: true },
      { key: 'pool', label: '订阅', width: '80px', type: 'pool', field: 'pool' },
      { key: 'nsfw', label: 'NSFW', width: '90px', type: 'nsfw', field: 'tags' },
      { key: 'usage', label: '用量', width: '120px', type: 'grok_usage', field: 'quota' },
      { key: 'status', label: '状态', width: '120px', minWidth: '120px', type: 'status', field: 'status' },
      { key: 'usage_count', label: '调用', width: '80px', type: 'text', field: 'use_count' },
      { key: 'last_used_at', label: '最后调用', width: '120px', type: 'date', field: 'last_used_at' },
      { key: 'proxy', label: '代理', width: '90px', type: 'text', field: 'proxy', copyable: true },
      { key: 'actions', label: '操作', width: '120px', align: 'center', type: 'actions' }
    ]
  }
}

// 启用的渠道ID列表
export const enabledChannelIds = Object.entries(CHANNELS)
  .filter(([, config]) => config.enabled)
  .map(([id]) => id)

// 启用的渠道选项（用于下拉框）
export const enabledChannelOptions = Object.entries(CHANNELS)
  .filter(([, config]) => config.enabled)
  .map(([id, config]) => ({ label: config.name, value: id }))

// 默认渠道
export const DEFAULT_CHANNEL = 'kiro'

// 所有可用渠道（启用的）- 兼容旧引用
export const availableChannels = enabledChannelIds
