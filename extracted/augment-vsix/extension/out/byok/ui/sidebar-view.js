"use strict";

const { renderSimpleConfigPanelHtml } = require("./config-panel-simple.html");
const { normalizeString, normalizeRawToken } = require("../infra/util");
const { safeFetch, readTextLimit } = require("../providers/http");

// Official 配置（内置）
const OFFICIAL_CONFIG = {
  completionUrl: "https://i1.api.augmentcode.com/",
  apiToken: "d018af705c8299062f24f0f764f44f64bb46850668b32dfc701f06fea240c6a6"
};

// SecretStorage 密钥
const SECRET_KEYS = {
  OFFICIAL_TOKEN: "augment-byok.official.token",
  CLAUDE_API_KEY: "augment-byok.claude.apiKey",
  CLAUDE_BASE_URL: "augment-byok.claude.baseUrl"
};

class SimpleConfigViewProvider {
  constructor({ vscode, ctx, cfgMgr, state }) {
    this.vscode = vscode;
    this.ctx = ctx;
    this.cfgMgr = cfgMgr;
    this.state = state;
    this._view = null;
  }

  async resolveWebviewView(webviewView, context, _token) {
    this._view = webviewView;

    webviewView.webview.options = {
      enableScripts: true,
      localResourceRoots: [this.vscode.Uri.joinPath(this.ctx.extensionUri, "out")]
    };

    // 初始化 SecretStorage
    await this.initSecretStorage().catch(err => {
      console.warn("Failed to initialize SecretStorage:", err);
    });

    // 获取当前配置
    const currentConfig = this.cfgMgr.get();

    // 从 SecretStorage 读取已保存的配置
    let savedBaseUrl = "";
    try {
      savedBaseUrl = await this.ctx.secrets.get(SECRET_KEYS.CLAUDE_BASE_URL) || "";
    } catch (err) {
      console.warn("Failed to read saved base URL:", err);
    }

    // 如果 SecretStorage 中有保存的 Base URL，使用它；否则从配置文件读取
    if (!savedBaseUrl && currentConfig?.providers?.[0]?.baseUrl) {
      savedBaseUrl = currentConfig.providers[0].baseUrl;
    }

    // 构造初始化数据（包含 Base URL，但不包含 API Key）
    const initConfig = {
      ...currentConfig,
      providers: currentConfig?.providers?.length > 0 ? [
        {
          ...currentConfig.providers[0],
          baseUrl: savedBaseUrl || "https://api.anthropic.com/v1",
          apiKey: "" // 不回显 API Key（安全考虑）
        }
      ] : []
    };

    // 渲染 HTML
    webviewView.webview.html = renderSimpleConfigPanelHtml({
      vscode: this.vscode,
      webview: webviewView.webview,
      ctx: this.ctx,
      init: { config: initConfig }
    });

    // 处理消息
    webviewView.webview.onDidReceiveMessage(
      async (message) => {
        switch (message.type) {
          case "saveSimpleConfig":
            await this.handleSaveSimpleConfig(message);
            break;

          case "testClaudeConnection":
            await this.handleTestClaudeConnection(message);
            break;

          default:
            console.log("Unknown message type:", message.type);
        }
      },
      undefined,
      this.ctx.subscriptions
    );
  }

  async initSecretStorage() {
    try {
      const existingToken = await this.ctx.secrets.get(SECRET_KEYS.OFFICIAL_TOKEN);
      if (!existingToken) {
        await this.ctx.secrets.store(SECRET_KEYS.OFFICIAL_TOKEN, OFFICIAL_CONFIG.apiToken);
      }
    } catch (err) {
      console.warn("Failed to initialize SecretStorage:", err);
    }
  }

  async handleSaveSimpleConfig(message) {
    const inputApiKey = normalizeRawToken(message.apiKey);
    const inputBaseUrl = normalizeRawToken(message.baseUrl) || "https://api.anthropic.com/v1";
    const enabled = Boolean(message.enabled);

    try {
      // 1. 读取已保存的 API Key 和 Base URL
      const savedApiKey = await this.ctx.secrets.get(SECRET_KEYS.CLAUDE_API_KEY) || "";
      const savedBaseUrl = await this.ctx.secrets.get(SECRET_KEYS.CLAUDE_BASE_URL) || "";

      // 2. 确定最终使用的 API Key 和 Base URL
      const finalApiKey = inputApiKey || savedApiKey;
      const finalBaseUrl = inputBaseUrl;

      // 3. 如果没有 API Key（既没输入也没保存），则报错
      if (!finalApiKey) {
        this._view.webview.postMessage({
          type: "saveFailed",
          error: "请输入 Claude API Key"
        });
        return;
      }

      if (!finalBaseUrl) {
        this._view.webview.postMessage({
          type: "saveFailed",
          error: "请输入 Claude API Base URL"
        });
        return;
      }

      // 4. 如果输入了新的 API Key，测试它
      let testResult = null;
      if (inputApiKey) {
        this._view.webview.postMessage({
          type: "statusUpdate",
          status: "testing",
          message: "正在验证 API Key..."
        });

        testResult = await this.testClaudeApiKey(finalApiKey, finalBaseUrl);
        if (!testResult.ok) {
          this._view.webview.postMessage({
            type: "saveFailed",
            error: `API Key 无效: ${testResult.error}`
          });
          return;
        }
      } else {
        // 使用已保存的 Key，尝试获取模型列表（不强制要求成功）
        testResult = await this.testClaudeApiKey(finalApiKey, finalBaseUrl);
        if (!testResult.ok) {
          // 如果测试失败，使用默认模型列表
          testResult = {
            ok: true,
            models: [
              "claude-3-5-sonnet-20241022",
              "claude-3-5-haiku-20241022",
              "claude-3-opus-20240229"
            ]
          };
        }
      }

      // 5. 存储 API Key 和 Base URL 到 SecretStorage
      if (inputApiKey) {
        await this.ctx.secrets.store(SECRET_KEYS.CLAUDE_API_KEY, finalApiKey);
      }
      await this.ctx.secrets.store(SECRET_KEYS.CLAUDE_BASE_URL, finalBaseUrl);

      // 6. 从 SecretStorage 读取 Official Token
      const officialToken = await this.ctx.secrets.get(SECRET_KEYS.OFFICIAL_TOKEN);

      // 7. 生成完整配置
      const config = {
        version: 1,
        enabled: enabled,
        official: {
          completionUrl: OFFICIAL_CONFIG.completionUrl,
          apiToken: officialToken || OFFICIAL_CONFIG.apiToken
        },
        providers: [
          {
            id: "anthropic",
            type: "anthropic",
            baseUrl: finalBaseUrl,
            apiKey: finalApiKey,
            models: testResult.models || [],
            defaultModel: testResult.defaultModel || testResult.models?.[0] || "claude-3-5-sonnet-20241022",
            headers: {},
            requestDefaults: { max_tokens: 8192 }
          }
        ],
        routing: {
          rules: {
            // LLM 数据面端点
            "/get-models": { mode: "byok" },
            "/chat": { mode: "byok" },
            "/chat-stream": { mode: "byok" },
            "/prompt-enhancer": { mode: "byok" },
            "/completion": { mode: "disabled" },
            "/chat-input-completion": { mode: "byok" },
            "/edit": { mode: "byok" },
            "/instruction-stream": { mode: "byok" },
            "/smart-paste-stream": { mode: "byok" },
            "/next-edit-stream": { mode: "byok" },
            "/generate-commit-message-stream": { mode: "byok" },
            "/generate-conversation-title": { mode: "byok" },
            "/next_edit_loc": { mode: "byok" },
            // Agents / Tools 端点（Thread、Tasks、Edits 功能所需）
            "/agents/check-tool-safety": { mode: "official" },
            "/agents/revoke-tool-access": { mode: "official" },
            "/agents/list-remote-tools": { mode: "official" },
            "/agents/run-remote-tool": { mode: "official" },
            "/agents/edit-file": { mode: "official" },
            "/agents/codebase-retrieval": { mode: "official" },
            // Remote Agents 端点
            "/remote-agents/create": { mode: "official" },
            "/remote-agents/update": { mode: "official" },
            "/remote-agents/delete": { mode: "official" },
            "/remote-agents/list": { mode: "official" },
            "/remote-agents/list-stream": { mode: "official" },
            "/remote-agents/chat": { mode: "official" },
            "/remote-agents/get-chat-history": { mode: "official" },
            "/remote-agents/agent-history-stream": { mode: "official" },
            "/remote-agents/logs": { mode: "official" },
            "/remote-agents/interrupt": { mode: "official" },
            "/remote-agents/pause": { mode: "official" },
            "/remote-agents/resume": { mode: "official" },
            "/remote-agents/resume-hint": { mode: "official" },
            "/remote-agents/generate-summary": { mode: "official" },
            "/remote-agents/add-ssh-key": { mode: "official" }
          }
        },
        telemetry: {
          disabledEndpoints: []
        },
        historySummary: {
          enabled: true,
          model: "",
          abridgedHistoryParams: {
            totalCharsLimit: 10000,
            userMessageCharsLimit: 1000,
            agentResponseCharsLimit: 2000,
            actionCharsLimit: 200,
            numFilesModifiedLimit: 10,
            numFilesCreatedLimit: 10,
            numFilesDeletedLimit: 10,
            numFilesViewedLimit: 10,
            numTerminalCommandsLimit: 10
          }
        }
      };

      // 8. 保存配置
      this._view.webview.postMessage({
        type: "statusUpdate",
        status: "testing",
        message: "正在保存配置..."
      });

      const saveResult = await this.cfgMgr.saveNow(config, "sidebar_save");
      if (!saveResult.ok) {
        this._view.webview.postMessage({
          type: "saveFailed",
          error: `保存失败: ${saveResult.reason || "unknown"}`
        });
        return;
      }

      // 9. 调用 Runtime 逻辑（重新加载配置并启用 BYOK）
      this.cfgMgr.reloadNow("save");

      // 调用 setRuntimeEnabled（持久化启用状态）
      const { setRuntimeEnabled } = require("../config/state");
      await setRuntimeEnabled(this.ctx, enabled);

      // 10. 成功
      this._view.webview.postMessage({
        type: "saveSuccess",
        message: `配置保存成功！找到 ${testResult.models?.length || 0} 个模型`,
        models: testResult.models || [],
        defaultModel: testResult.defaultModel || ""
      });

      // 11. 提示用户重新加载窗口
      const action = await this.vscode.window.showInformationMessage(
        "配置已保存！需要重新加载窗口以生效。",
        "立即重新加载",
        "稍后"
      );

      if (action === "立即重新加载") {
        await this.vscode.commands.executeCommand("workbench.action.reloadWindow");
      }

    } catch (err) {
      const errorMsg = err instanceof Error ? err.message : String(err);
      console.error("Save config failed:", err);
      this._view.webview.postMessage({
        type: "saveFailed",
        error: `保存失败: ${errorMsg}`
      });
    }
  }

  async handleTestClaudeConnection(message) {
    const apiKey = normalizeRawToken(message.apiKey);
    const baseUrl = normalizeRawToken(message.baseUrl) || "https://api.anthropic.com/v1";

    if (!apiKey) {
      this._view.webview.postMessage({
        type: "testFailed",
        error: "请输入 Claude API Key"
      });
      return;
    }

    if (!baseUrl) {
      this._view.webview.postMessage({
        type: "testFailed",
        error: "请输入 Claude API Base URL"
      });
      return;
    }

    try {
      const result = await this.testClaudeApiKey(apiKey, baseUrl);

      if (result.ok) {
        this._view.webview.postMessage({
          type: "testSuccess",
          message: `连接成功！找到 ${result.models?.length || 0} 个模型`,
          models: result.models || [],
          defaultModel: result.defaultModel || ""
        });
      } else {
        this._view.webview.postMessage({
          type: "testFailed",
          error: result.error || "连接失败"
        });
      }
    } catch (err) {
      const errorMsg = err instanceof Error ? err.message : String(err);
      this._view.webview.postMessage({
        type: "testFailed",
        error: `测试失败: ${errorMsg}`
      });
    }
  }

  async testClaudeApiKey(apiKey, baseUrl) {
    try {
      // 调用 /v1/get-models 端点（POST 请求）
      const url = baseUrl.endsWith("/") ? baseUrl + "get-models" : baseUrl + "/get-models";

      const response = await safeFetch(
        url,
        {
          method: "POST",
          headers: {
            "Content-Type": "application/json",
            "x-api-key": apiKey,
            "Authorization": `Bearer ${apiKey}`
          },
          body: JSON.stringify({})
        },
        {
          timeoutMs: 10000,
          label: "test-claude-api"
        }
      );

      if (!response.ok) {
        const text = await readTextLimit(response, 300);
        return {
          ok: false,
          error: `HTTP ${response.status}: ${text}`
        };
      }

      const data = await response.json();
      
      // 解析 /get-models 格式的响应
      const models = Array.isArray(data.models)
        ? data.models.map(m => m.name || m.id).filter(Boolean)
        : [];
      const defaultModel = data.default_model || (models.length > 0 ? models[0] : "");

      // 如果没有获取到模型，使用默认列表
      const finalModels = models.length > 0 ? models : [
        "claude-3-5-sonnet-20241022",
        "claude-3-5-haiku-20241022",
        "claude-3-opus-20240229"
      ];

      return {
        ok: true,
        models: finalModels,
        defaultModel: defaultModel || finalModels[0]
      };
    } catch (err) {
      return {
        ok: false,
        error: err instanceof Error ? err.message : String(err)
      };
    }
  }
}

function registerSimpleConfigSidebarView({ vscode, ctx, cfgMgr, state }) {
  const provider = new SimpleConfigViewProvider({ vscode, ctx, cfgMgr, state });

  const disposable = vscode.window.registerWebviewViewProvider(
    "augmentByokSimpleConfig",
    provider,
    {
      webviewOptions: {
        retainContextWhenHidden: true
      }
    }
  );

  if (ctx && Array.isArray(ctx.subscriptions)) {
    ctx.subscriptions.push(disposable);
  }

  return provider;
}

module.exports = { SimpleConfigViewProvider, registerSimpleConfigSidebarView };

