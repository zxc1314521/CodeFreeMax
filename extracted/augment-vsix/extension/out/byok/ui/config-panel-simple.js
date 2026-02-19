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

let currentPanel = null;

async function openSimpleConfigPanel({ vscode, ctx, cfgMgr, state }) {
  if (currentPanel) {
    currentPanel.reveal();
    return;
  }

  // 创建 Webview Panel（侧边栏视图）
  currentPanel = vscode.window.createWebviewPanel(
    "augmentByokSimpleConfig",
    "BYOK 配置",
    vscode.ViewColumn.One,
    {
      enableScripts: true,
      retainContextWhenHidden: true,
      localResourceRoots: [vscode.Uri.joinPath(ctx.extensionUri, "out")]
    }
  );

  // 初始化 SecretStorage（存储 Official Token）
  try {
    const existingToken = await ctx.secrets.get(SECRET_KEYS.OFFICIAL_TOKEN);
    if (!existingToken) {
      await ctx.secrets.store(SECRET_KEYS.OFFICIAL_TOKEN, OFFICIAL_CONFIG.apiToken);
    }
  } catch (err) {
    console.warn("Failed to initialize SecretStorage:", err);
  }

  // 获取当前配置
  const currentConfig = cfgMgr.get();

  // 从 SecretStorage 读取已保存的配置
  let savedBaseUrl = "";
  try {
    savedBaseUrl = await ctx.secrets.get(SECRET_KEYS.CLAUDE_BASE_URL) || "";
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
    enabled: state.runtimeEnabled, // 添加 runtime enabled 状态
    providers: currentConfig?.providers?.length > 0 ? [
      {
        ...currentConfig.providers[0],
        baseUrl: savedBaseUrl || "https://api.anthropic.com/v1",
        apiKey: "" // 不回显 API Key（安全考虑）
      }
    ] : []
  };

  // 渲染 HTML
  currentPanel.webview.html = renderSimpleConfigPanelHtml({
    vscode,
    webview: currentPanel.webview,
    ctx,
    init: { config: initConfig }
  });

  // 处理消息
  currentPanel.webview.onDidReceiveMessage(
    async (message) => {
      console.log("[BYOK] Received message:", message);

      switch (message.type) {
        case "saveSimpleConfig":
          console.log("[BYOK] Handling saveSimpleConfig");
          await handleSaveSimpleConfig(message, { vscode, ctx, cfgMgr, state, panel: currentPanel });
          break;

        case "testClaudeConnection":
          console.log("[BYOK] Handling testClaudeConnection");
          await handleTestClaudeConnection(message, { vscode, ctx, panel: currentPanel });
          break;

        default:
          console.log("[BYOK] Unknown message type:", message.type);
      }
    },
    undefined,
    ctx.subscriptions
  );

  // 清理
  currentPanel.onDidDispose(
    () => {
      currentPanel = null;
    },
    null,
    ctx.subscriptions
  );
}

async function handleSaveSimpleConfig(message, { vscode, ctx, cfgMgr, state, panel }) {
  console.log("[BYOK] handleSaveSimpleConfig called with message:", message);

  const inputApiKey = normalizeRawToken(message.apiKey);
  const inputBaseUrl = normalizeRawToken(message.baseUrl) || "https://api.anthropic.com/v1";
  const enabled = Boolean(message.enabled);

  console.log("[BYOK] Parsed input:", {
    hasApiKey: !!inputApiKey,
    baseUrl: inputBaseUrl,
    enabled
  });

  try {
    // 1. 读取已保存的 API Key 和 Base URL
    const savedApiKey = await ctx.secrets.get(SECRET_KEYS.CLAUDE_API_KEY) || "";
    const savedBaseUrl = await ctx.secrets.get(SECRET_KEYS.CLAUDE_BASE_URL) || "";

    console.log("[BYOK] Saved config:", {
      hasSavedApiKey: !!savedApiKey,
      savedBaseUrl
    });

    // 2. 确定最终使用的 API Key 和 Base URL
    const finalApiKey = inputApiKey || savedApiKey;
    const finalBaseUrl = inputBaseUrl;

    console.log("[BYOK] Final config:", {
      hasFinalApiKey: !!finalApiKey,
      finalBaseUrl
    });

    // 3. 如果没有 API Key（既没输入也没保存），则报错
    if (!finalApiKey) {
      console.log("[BYOK] No API Key found, sending error");
      panel.webview.postMessage({
        type: "saveFailed",
        error: "请输入 Claude API Key"
      });
      return;
    }

    if (!finalBaseUrl) {
      console.log("[BYOK] No Base URL found, sending error");
      panel.webview.postMessage({
        type: "saveFailed",
        error: "请输入 Claude API Base URL"
      });
      return;
    }

    // 4. 如果输入了新的 API Key，测试它
    let testResult = null;
    if (inputApiKey) {
      console.log("[BYOK] Testing new API Key...");
      panel.webview.postMessage({
        type: "statusUpdate",
        status: "testing",
        message: "正在验证 API Key..."
      });

      testResult = await testClaudeApiKey(finalApiKey, finalBaseUrl);
      console.log("[BYOK] Test result:", testResult);

      if (!testResult.ok) {
        console.log("[BYOK] API Key test failed");
        panel.webview.postMessage({
          type: "saveFailed",
          error: `API Key 无效: ${testResult.error}`
        });
        return;
      }
    } else {
      console.log("[BYOK] Using saved API Key, testing connection...");
      // 使用已保存的 Key，尝试获取模型列表（不强制要求成功）
      testResult = await testClaudeApiKey(finalApiKey, finalBaseUrl);
      console.log("[BYOK] Test result with saved key:", testResult);

      if (!testResult.ok) {
        console.log("[BYOK] Test failed, using default models");
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

    console.log("[BYOK] Saving to SecretStorage...");
    // 5. 存储 API Key 和 Base URL 到 SecretStorage
    if (inputApiKey) {
      await ctx.secrets.store(SECRET_KEYS.CLAUDE_API_KEY, finalApiKey);
    }
    await ctx.secrets.store(SECRET_KEYS.CLAUDE_BASE_URL, finalBaseUrl);

    // 6. 从 SecretStorage 读取 Official Token
    const officialToken = await ctx.secrets.get(SECRET_KEYS.OFFICIAL_TOKEN);
    console.log("[BYOK] Official token:", officialToken ? "exists" : "missing");

    // 7. 生成完整配置（上下文压缩默认开启）
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
          defaultModel: testResult.models?.[0] || "claude-3-5-sonnet-20241022",
          headers: {},
          requestDefaults: { max_tokens: 8192 }
        }
      ],
      routing: {
        rules: {
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
          "/next_edit_loc": { mode: "byok" }
        }
      },
      telemetry: {
        disabledEndpoints: []
      },
      historySummary: {
        enabled: true, // 默认开启上下文压缩
        providerId: "", // 空字符串表示使用 fallbackProvider（当前请求的 provider）
        model: "", // 空字符串表示跟随当前请求的模型
        maxTokens: 1024,
        timeoutSeconds: 60,
        triggerOnHistorySizeChars: 400000, // 40万字符触发压缩
        triggerStrategy: "auto",
        triggerOnContextRatio: 0.6, // 上下文占用60%时触发
        targetContextRatio: 0.4, // 目标压缩到40%
        historyTailSizeCharsToExclude: 150000, // 保留15万字符尾部
        minTailExchanges: 2,
        cacheTtlMs: 0,
        maxSummarizationInputChars: 250000,
        rollingSummary: true,
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
    console.log("[BYOK] Saving config to file...");
    panel.webview.postMessage({
      type: "statusUpdate",
      status: "testing",
      message: "正在保存配置..."
    });

    const saveResult = await cfgMgr.saveNow(config, "simple_panel_save");
    console.log("[BYOK] Save result:", saveResult);

    if (!saveResult.ok) {
      console.log("[BYOK] Save failed:", saveResult.reason);
      panel.webview.postMessage({
        type: "saveFailed",
        error: `保存失败: ${saveResult.reason || "unknown"}`
      });
      return;
    }

    // 9. 调用 Runtime 逻辑（重新加载配置并启用 BYOK）
    console.log("[BYOK] Reloading config...");
    cfgMgr.reloadNow("save");

    // 调用 setRuntimeEnabled（持久化启用状态）
    const { setRuntimeEnabled } = require("../config/state");
    console.log("[BYOK] Calling setRuntimeEnabled:", enabled);
    await setRuntimeEnabled(ctx, enabled);

    // 10. 成功
    console.log("[BYOK] Save successful, sending success message");
    panel.webview.postMessage({
      type: "saveSuccess",
      message: `配置保存成功！找到 ${testResult.models?.length || 0} 个模型`,
      models: testResult.models || []
    });

    // 11. 提示用户重新加载窗口
    const action = await vscode.window.showInformationMessage(
      "配置已保存！需要重新加载窗口以生效。",
      "立即重新加载",
      "稍后"
    );

    if (action === "立即重新加载") {
      await vscode.commands.executeCommand("workbench.action.reloadWindow");
    }

  } catch (err) {
    const errorMsg = err instanceof Error ? err.message : String(err);
    console.error("[BYOK] Save config failed:", err);
    panel.webview.postMessage({
      type: "saveFailed",
      error: `保存失败: ${errorMsg}`
    });
  }
}

async function handleTestClaudeConnection(message, { vscode, ctx, panel }) {
  const apiKey = normalizeRawToken(message.apiKey);
  const baseUrl = normalizeRawToken(message.baseUrl) || "https://api.anthropic.com/v1";

  if (!apiKey) {
    panel.webview.postMessage({
      type: "testFailed",
      error: "请输入 Claude API Key"
    });
    return;
  }

  if (!baseUrl) {
    panel.webview.postMessage({
      type: "testFailed",
      error: "请输入 Claude API Base URL"
    });
    return;
  }

  try {
    const result = await testClaudeApiKey(apiKey, baseUrl);

    if (result.ok) {
      panel.webview.postMessage({
        type: "testSuccess",
        message: `连接成功！找到 ${result.models?.length || 0} 个模型`,
        models: result.models || []
      });
    } else {
      panel.webview.postMessage({
        type: "testFailed",
        error: result.error || "连接失败"
      });
    }
  } catch (err) {
    const errorMsg = err instanceof Error ? err.message : String(err);
    panel.webview.postMessage({
      type: "testFailed",
      error: `测试失败: ${errorMsg}`
    });
  }
}

async function testClaudeApiKey(apiKey, baseUrl) {
  try {
    const url = baseUrl.endsWith("/") ? baseUrl + "models" : baseUrl + "/models";

    const response = await safeFetch(
      url,
      {
        method: "GET",
        headers: {
          "x-api-key": apiKey,
          "anthropic-version": "2023-06-01"
        }
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
    const models = Array.isArray(data.data)
      ? data.data.map(m => m.id).filter(Boolean)
      : [];

    // 如果没有获取到模型，使用默认列表
    const finalModels = models.length > 0 ? models : [
      "claude-3-5-sonnet-20241022",
      "claude-3-5-haiku-20241022",
      "claude-3-opus-20240229"
    ];

    return {
      ok: true,
      models: finalModels
    };
  } catch (err) {
    return {
      ok: false,
      error: err instanceof Error ? err.message : String(err)
    };
  }
}

module.exports = { openSimpleConfigPanel };

