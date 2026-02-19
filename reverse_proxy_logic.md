# CodeFreeMax (kiro2api) 反代逻辑还原

基于 GoReSym 符号恢复 + Ghidra 反编译 + 字符串提取的综合分析。

---

## 整体架构

```
用户请求 (OpenAI 兼容格式)
    │
    ▼
┌─────────────────────────────────────┐
│  CodeFreeMax HTTP Server (GoFrame)  │
│  /{channel}/v1/chat/completions     │
└──────────────┬──────────────────────┘
               │
    ┌──────────┼──────────┬──────────┬──────────┬──────────┬──────────┐
    ▼          ▼          ▼          ▼          ▼          ▼          ▼
  Kiro      Warp      Orchids     Grok    Antigravity  Cursor   Claude API
    │          │          │          │          │          │          │
    ▼          ▼          ▼          ▼          ▼          ▼          ▼
 AWS Q    Warp gRPC   Orchids WS  Grok REST  Google    Cursor    Anthropic
 (SigV4)  (Protobuf)  (WebSocket) (HTTP)     Cloud     Connect   (HTTP)
                                              Code      Protocol
```

### 公共组件

- **AccountQueueManager**: Redis 队列管理各通道账号池，轮询分配
- **Gate 加密系统**: 凭证加密存储 (`gate:` 前缀)，`DecryptBatch` 批量解密，`EncryptAndSetCredentials` 加密写入
- **ResponseHandler**: 统一错误处理 — 403 (handleForbidden)、402 (handlePaymentRequired)、429 (handleRateLimited)
- **CompressContextWithTools**: 上下文压缩 — token 计数、历史分割、摘要缓存、回退截断
- **代理支持**: 每个通道独立代理配置 (`kiro_use_builtin_proxy`, `warp_use_builtin_proxy`, `orchids_use_builtin_proxy`, `cursor_proxy_url`)

---

## 1. Kiro 通道 (AWS Q / CodeWhisperer)

### 上游目标
```
https://codewhisperer.us-east-1.amazonaws.com
https://q.us-east-1.amazonaws.com/generateAssistantResponse
https://q.us-east-1.amazonaws.com/getUsageLimits
```

### 认证方式
- AWS SigV4 签名 (IAM Credentials)
- 服务名: `CodeWhispererService`, `AmazonQ`
- Header: `x-amz-target`, `x-amz-json-1`, `x-amz-user-agent`, `x-amzn-trace-id`
- Agent 模式: `x-amzn-kiro-agent-mode`

### 请求流程
```
buildKiroRequest (3255 行，最大的函数):
  1. getContentText() — 提取消息文本内容
  2. hasThinkingPrefix() — 检查是否有思考前缀
  3. generateThinkingPrefix() — 生成 <thinking> 标签
  4. uuid.NewString() — 生成请求 ID
  5. 构建 AWS API 请求体
  6. SigV4 签名
  7. 发送到 AWS Q endpoint
```

### OAuth 流程
- `/kiro/oauth/authorize` — 发起 OAuth
- `/kiro/oauth/status/:state` — 轮询 OAuth 状态
- 账号管理: `kiro.db` SQLite 存储

### 模型映射
- 输入: `claude-*` 系列模型名
- 映射到: AWS Q 内部模型 ID (如 `CLAUDE_SONNET_4_20250514_V1_0`, `CLAUDE_SONNET_4_5_20250929_V1_0`)

---

## 2. Warp 通道

### 上游目标
```
https://app.warp.dev/ai/multi-agent-*          (主 API，Protobuf over HTTP)
https://app.warp.dev/graphql/v2?op=GetUserDetail
https://app.warp.dev/graphql/v2?op=ProvideNegativeFeedbackResponseForAiConversation
https://securetoken.googleapis.com/v1/token     (Token 刷新)
```

### 认证方式
- Firebase Auth Token (Google securetoken)
- 自定义 Headers:
  - `x-warp-client-id`
  - `x-warp-client-version`
  - `x-warp-experiment-id`
  - `x-warp-os-category` (macOS)
  - `x-warp-os-name`
  - `x-warp-os-version`

### 请求流程
```
ChatCompletions:
  1. isWarpModelAllowed(model) — 检查模型是否支持
  2. sWarp.CheckToken() — 验证/刷新 Firebase token
  3. sWarp.buildWarpRequest() — 构建 Protobuf 请求
  4. proto.Marshal() — 序列化为 Protobuf 二进制
  5. req.Client.Clone() — 克隆 HTTP 客户端
  6. GetWarpProxyURL() — 获取代理
  7. uuid.NewString() — 生成请求 ID
  8. WarpAccountDao.Update() — 更新账号状态
  9. SetHeader() × 多次 — 设置 Warp 特有 Headers
  10. Request.Send() — 发送到 Warp API
  11. UnmarshalMessage() — 解析 Protobuf 响应
```

### Protobuf 协议
- 包名: `warp.multi_agent.v1`
- 核心消息:
  - `Request` → `Input.UserQuery`, `Settings.ModelConfig`, `MCPContext`
  - `ResponseEvent` → `StreamFinished`, `ClientActions`, `StreamInit`
  - `Message` → `ToolCall`, `ToolCallResult`, `AgentOutput`, `AgentReasoning`
- 工具映射: `MapToolToClaudeCode` / `MapToolsToClaudeCode` — 将 Warp 工具转换为 Claude Code 格式

### buildFullPrompt (4494 行，最大函数)
```
  1. extractSystemPrompt() — 提取系统提示
  2. getContentText() — 获取消息内容
  3. sanitizeUTF8() — 清理 UTF-8
  4. json.Marshal() — 序列化工具调用结果
  5. 构建完整的 Warp multi-agent 请求
```

### Token 刷新
```
RefreshToken:
  1. POST https://securetoken.googleapis.com/v1/token
  2. grant_type=refresh_token
  3. refresh_token=<stored_token>
  4. 更新本地存储的 access_token
```

### 额度管理
```
GetQuotaInfo:
  1. CheckToken() — 确保 token 有效
  2. GraphQL: GetUserDetail — 查询用户额度
  3. 返回: totalQuota, basicCount, superCount, inUseCount

RefundCredits:
  1. GraphQL: ProvideNegativeFeedbackResponseForAiConversation
  2. 退还 Warp credits (请求失败时)
```

---

## 3. Orchids 通道 (Claude Code Web)

### 上游目标
```
wss://orchids-v2-alpha-108292236521.europe-west1.run.app/agent/ws/coding-agent  (WebSocket)
https://www.orchids.app/api/projects/create                                      (SSE 备选)
https://clerk.orchids.app/v1/client/sessions/%s/tokens                          (Token 刷新)
https://clerk.orchids.app/v1/client                                              (客户端信息)
```

### 认证方式
- Clerk Session Token
- Token 刷新: `https://clerk.orchids.app/v1/client/sessions/{session_id}/tokens?__clerk_api_version=2025-11-10`

### 传输模式 (orchids_transport_mode)
- **WebSocket** (默认): 通过 WebSocket 连接到 Orchids 后端
- **SSE**: 通过 HTTP SSE 流式传输

### WebSocket 请求流程
```
executeWebSocketRequest:
  1. ConvertToOrchidsRequest() — 将 OpenAI 格式转为 Orchids 格式
  2. ToolMapper.buildIndex() — 构建工具名映射索引
  3. GetConnectionPoolManager() — 获取连接池
  4. ConnectionPoolManager.GetConnection() — 获取/复用 WebSocket 连接
  5. getOrchidsProxyURL() — 获取代理
  6. OrchidsWebSocket.SendRequest() — 发送请求
  7. NewSSEWriter() — 创建 SSE 写入器
  8. 循环:
     a. OrchidsWebSocket.ReadMessageWithTimeout() — 读取响应
     b. handleModelEvent() — 处理模型事件
     c. SSEWriter.WriteMessageStart/WriteDelta/WriteToolInput — 写入 SSE 流
  9. StreamState 管理: SetClientToolIndex, SetFinishReason, SetInputTokens, SetOutputTokens
```

### SSE 请求流程
```
executeSSERequest:
  1. ConvertToOrchidsRequest() — 转换请求格式
  2. ToolMapper.buildIndex() — 构建工具映射
  3. sOrchids.createProject() — 创建项目 (如需要)
  4. getOrchidsProxyURL() — 获取代理
  5. Client.Clone() + SetProxyURL()
  6. SetHeader() — 设置认证头
  7. Request.Send() — 发送 HTTP 请求
  8. 流式读取 SSE 响应
```

### 工具映射
```
MapToolNameToClient:
  - MapOrchidsToolToAnthropic() — Orchids 工具名 → Anthropic 工具名
  - NormalizeToolName() — 标准化工具名

extractMessageContent / extractUserMessage:
  - parseToolResult() — 解析工具调用结果
  - 将 Orchids 消息格式转为 Anthropic Messages API 格式
```

### 响应处理 (handleModelEvent)
```
  - SSEWriter.WriteThinkingDelta() — 写入思考内容
  - SSEWriter.EnsureTextBlockAndWriteDelta() — 写入文本
  - SSEWriter.StartToolUseBlock() — 开始工具调用块
  - SSEWriter.WriteToolInputDelta() — 写入工具输入
  - StreamState.StartReasoning() — 开始推理
  - StreamState.EndToolCall() — 结束工具调用
  - StreamState.SetCacheReadInputTokens() — 缓存 token 计数
```

---

## 4. Grok 通道

### 上游目标
```
https://grok.com/rest/app-chat/conversations/new     (聊天)
https://grok.com/rest/app-chat/upload-file            (文件上传)
https://grok.com/rest/media/post/create               (媒体创建)
https://grok.com/rest/rate-limits                     (速率限制)
https://grok.com/imagine                              (图片生成)
wss://grok.com/ws/imagine/listen                      (图片/视频生成 WebSocket)
https://grok.com/auth_mgmt.AuthManagement/UpdateUserFeatureControls  (NSFW 控制)
```

### 认证方式
- Cookie-based (浏览器 Session)
- 自定义 Headers:
  - `x-xai-request-id`
  - Browser Fingerprint: `sGrok.GetBrowserFingerprint()`
  - CF Clearance: `sGrok.GetCfClearance()`

### 请求流程
```
BuildChatPayload:
  1. extractMessages() — 提取并转换消息
  2. 构建 Grok REST API payload
  3. 包含: grok_thinking, grok_image_ws, enableImageGeneration, imageAttachments 等

ProcessLine (流式响应处理):
  1. json.Unmarshal() — 解析每行 JSON
  2. StreamProcessor.filterToken() — 过滤 token
  3. StreamProcessor.BuildSSE() — 构建 SSE 事件
  4. StreamProcessor.BuildThinkingSSE() — 构建思考 SSE
  5. processAssetURLWithDownload() — 处理图片/视频资源 URL
  6. UsageTracker.AppendTextContent/AppendThinkingContent — 统计 token

CollectProcessorProcessWithUsage (非流式):
  1. bufio.Scanner.Scan() — 逐行读取
  2. json.Unmarshal() — 解析
  3. filterContent() — 过滤内容
  4. processAssetURLWithDownload() — 下载资源
  5. UsageTracker.GetUsage() — 获取 token 用量
```

### 图片生成
```
ImagineGenerations:
  1. WebSocket 连接: wss://grok.com/ws/imagine/listen
  2. gorilla/websocket.Conn.ReadMessage() — 读取生成结果
  3. classifyImage() — 分类图片
  4. 超时处理: isTimeoutError()
```

### 视频生成
```
VideoGenerations:
  1. sGrok.clientForAccount() — 获取账号客户端
  2. BuildHeaders() — 构建请求头
  3. buildVideoPayload() — 构建视频请求
  4. sGrok.createMediaPost() — 创建媒体帖子
  5. sGrok.uploadImage() — 上传参考图
  6. GrokClient.PostStream() — 流式请求
```

### NSFW 控制
- `/grok/account/nsfw-toggle` — 单个账号切换
- `/grok/account/nsfw-batch` — 批量切换
- 通过 `auth_mgmt.AuthManagement/UpdateUserFeatureControls` gRPC 调用

---

## 5. Antigravity 通道 (Augment Code)

### 上游目标
```
https://cloudcode-pa.googleapis.com       (生产环境)
https://daily-cloudcode-pa.sandbox.googleapis.com  (沙箱环境)
https://oauth2.googleapis.com/token       (OAuth Token 刷新)
```

### 认证方式
- Google OAuth2
- Scopes: `cloud-platform`, `userinfo.email`, `userinfo.profile`, `cclog`
- Token 刷新: `https://oauth2.googleapis.com/token`
- 需要 `refresh_token`, `client_id`, `client_secret`

### 请求流程
```
buildAntigravityRequest:
  1. uuid.NewString() — 生成请求 ID
  2. getContentText() — 提取消息内容
  3. cleanThinkingFieldsRecursive() — 清理 thinking 字段
  4. sAntigravity.convertToolsToFunctionDeclarations() — 转换工具为 Gemini 函数声明格式
  5. convertMessagesToContents() — 转换消息为 Gemini Contents 格式

doStreamRequest:
  1. json.Marshal() — 序列化请求
  2. Client.Clone() — 克隆客户端
  3. getProxyURL() / Client.SetProxy() / Request.SetProxy()
  4. SetHeader() — 设置 OAuth Bearer token
  5. Request.Send() — 发送到 Google Cloud Code API
  6. 流式读取响应

convertMessagesToContents:
  1. mergeAdjacentRoles() — 合并相邻同角色消息 (Gemini 要求)
  2. convertContentToPartsWithMapping() — 转换内容为 Parts
```

### Token 刷新
```
RefreshToken:
  1. IsTokenExpiringSoon() — 检查是否即将过期
  2. POST https://oauth2.googleapis.com/token
  3. grant_type=refresh_token
  4. 更新 access_token 和 id_token
```

### 模型映射
- 输入: `claude-*`, `gemini-*` 模型名
- 映射到: Google Cloud Code 内部模型 (Gemini 系列)
- 支持: `gemini-2.5-flash`, `gemini-2.5-pro`, `gemini-3-flash`, `gemini-3-pro` 等

---

## 6. Cursor 通道

### 上游目标
```
https://api2.cursor.sh       (主 API)
```

### 认证方式
- WorkOS Session Token: `WorkosCursorSessionToken`
- 自定义 Headers:
  - `x-cursor-client-version`
  - `x-cursor-config-version`
  - `x-cursor-streaming`
  - `x-cursor-timezone`
  - `x-cursor-checksum` — 通过 `GetChecksum()` 计算
- Connect Protocol (基于 gRPC-Web):
  - `connect-protocol-version`
  - `connect-accept-encoding`
  - `connect-content-encoding`

### 请求流程
```
buildCursorRequest (1392 行):
  1. extractSystemPrompt() — 提取系统提示
  2. extractWorkspacePath() — 提取工作区路径
  3. mapCursorModel() — 映射模型名
  4. parseMessageContent() — 解析消息内容
  5. uuid.NewString() — 生成请求 ID
  6. time.Format() — 格式化时间戳
  7. json.Marshal() — 序列化为 Connect 协议格式

newConnectRequest:
  1. uuid.NewString() — 生成请求 ID
  2. GetChecksum() — 计算校验和
  3. rand.Intn() — 随机化参数
  4. 设置 Connect Protocol headers
  5. 构建 gRPC-Web 请求
```

### 协议特点
- 使用 Connect Protocol (类 gRPC-Web)，不是标准 REST
- 路径: `/cursor/currpc` (Connect RPC)
- 二进制序列化 + 流式传输
- 库: `connect-es` (Connect for ECMAScript)

### 模型映射
- 支持: `gpt-5-*`, `claude-*`, `cursor-small`, `o1-*` 等
- 通过 `mapCursorModel()` 转换

---

## 7. Claude API 通道

### 上游目标
```
https://api.anthropic.com/v1/messages     (API 直连)
https://console.anthropic.com             (Web Session)
```

### 认证方式
- 两种模式:
  1. **API Key**: `x-api-key` header
  2. **Session Key**: 浏览器 session cookie

### Session Key 验证流程
```
checkSessionKey (681 行):
  1. ExtractSessionId() — 从 session key 提取 session ID
  2. sClaudeApi.getAccountInfo() — 获取账号信息
  3. sClaudeApi.getProxyURL() — 获取代理
  4. Client.Clone() + Client.SetProxy()
  5. Request.SetBody() — 设置请求体
  6. proxy.Request.Fetch() — 发送验证请求
  7. proxy.Response.Error() — 检查错误
  8. gjson 解析响应 — 提取组织、项目等信息
  9. CodeVerifier.CodeChallengeS256() — PKCE 验证
  10. ClaudeApiAccountDao.UpdateTokenInfo() — 更新 token 信息
  11. ClaudeApiAccount.EncryptAndSetCredentials() — 加密存储凭证
```

### 请求处理
```
ChatController.Messages:
  1. Request.GetHeader() — 获取认证头
  2. GetConcurrencyManager() — 获取并发管理器
  3. AccountConcurrencyManager.GetClaudeApiAccountWithSlot() — 获取可用账号
  4. ClaudeApiAccount.LoadGateCredentials() — 加载加密凭证
  5. NewRetryConfig() — 创建重试配置
  6. 转发请求到 Anthropic API
  7. 流式写入响应
```

### Claude Code 上下文注入
```
injectClaudeCodeContext:
  1. json.Unmarshal() — 解析请求体
  2. sha256.Sum256() — 计算内容哈希
  3. 注入 Claude Code 特有的上下文 (thinking_mode, max_thinking_length)
  4. json.Marshal() — 重新序列化

  注入内容: <thinking_mode>enabled</thinking_mode><max_thinking_length>%d</max_thinking_length>
```

---

## 凭证管理系统 (Gate)

### 加密存储
```
数据库字段:
  - enc_token          — 加密的 access token
  - enc_session_key    — 加密的 session key
  - enc_refresh_token  — 加密的 refresh token

加密格式: "gate:" 前缀 + 加密数据

迁移函数:
  - migrateKiroToGate      — Kiro 账号迁移到 Gate 加密
  - migrateOrchidsToGate   — Orchids 账号迁移
  - migrateClaudeApiToGate — Claude API 账号迁移

流程:
  1. DecryptCredential() — 解密旧格式
  2. gate.Encrypt() — 用 Gate 重新加密
  3. DB.Exec() — 更新数据库
```

### 缓存预热
```
WarmGateCredentialCache:
  1. 各通道 DAO.GetAllNormal() — 获取所有正常账号
  2. gate.DecryptBatch() — 批量解密
  3. gate.SetCachedCredentialsWithTTL() — 设置带 TTL 的缓存
  4. 随机延迟: rand.Int63n() — 防止缓存雪崩
```

---

## 账号队列管理

```
AccountQueueManager.InitializeQueue:
  1. 加载各通道所有正常账号:
     - AccountDao (Kiro)
     - WarpAccountDao
     - OrchidsAccountDao
     - GrokAccountDao
     - AntigravityAccountDao
     - ClaudeApiAccountDao
  2. redis.RPush() — 推入 Redis 队列
  3. 请求时从队列头部取出，用完放回尾部 (轮询)
```

---

## 错误处理

```
ResponseHandler.HandleResponse:
  → handleErrorResponse:
    - parseErrorReason() — 解析错误原因
    - handleForbidden() — 403: 账号被封/无权限
    - handlePaymentRequired() — 402: 额度用完
    - handleRateLimited() — 429: 速率限制
    - updateAccountStatus() — 更新账号状态 (标记异常等)
```

---

## 模型名统一映射

系统接受多种模型名格式，内部统一映射:

| 用户输入 | 实际模型 |
|---------|---------|
| claude-4.5-opus, claude-opus-4-5 | Claude Opus 4.5 |
| claude-4.5-sonnet, claude-sonnet-4-5 | Claude Sonnet 4.5 |
| claude-4-opus, claude-opus-4 | Claude Opus 4 |
| claude-4.5-opus-thinking | Claude Opus 4.5 (extended thinking) |
| claude-4.5-opus-high-thinking | Claude Opus 4.5 High (thinking) |
| claude-4-6-opus, claude-opus-4-6 | Claude Opus 4.6 |
| gpt-5-high, gpt-5-low, gpt-5-medium | GPT-5 各档位 |
| gpt-5-1-codex-*, gpt-5-2-codex-* | Codex 系列 |
| gemini-2.5-flash, gemini-2.5-pro | Gemini 2.5 系列 |
| gemini-3-flash, gemini-3-pro | Gemini 3 系列 |
| grok-4.1-mini, grok-4-heavy | Grok 系列 |

---

## 配置项

| 配置键 | 说明 |
|-------|------|
| `kiro_use_builtin_proxy` | Kiro 通道使用内置代理 |
| `warp_use_builtin_proxy` | Warp 通道使用内置代理 |
| `orchids_use_builtin_proxy` | Orchids 通道使用内置代理 |
| `orchids_transport_mode` | Orchids 传输模式 (websocket/sse) |
| `cursor_proxy_url` | Cursor 通道代理 URL |
| `grok_media_max_concurrent` | Grok 媒体最大并发数 |
| `agent_chat_model` | Agent 聊天默认模型 |
| `refresh_interval` | Token 刷新间隔 |
| `enable_token_refresh` | 启用 Token 自动刷新 |
| `enable_usage_refresh` | 启用用量自动刷新 |
| `enable_token_count` | 启用 Token 计数 |
| `enable_token_cache` | 启用 Token 缓存 |
| `warp_credit_refund` | Warp 积分退还 |
