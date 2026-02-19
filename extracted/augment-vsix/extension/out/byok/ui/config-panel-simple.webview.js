(function () {
  "use strict";

  const vscode = acquireVsCodeApi();

  // 状态管理
  const state = {
    apiKey: "",
    baseUrl: "https://api.anthropic.com/v1",
    enabled: false,
    models: [],
    defaultModel: "", // 默认模型（从 /get-models 返回）
    status: "unconfigured",
    statusMessage: "未配置"
  };

  // 初始化
  function init() {
    try {
      const initEl = document.getElementById("byokInit");
      if (initEl) {
        const initData = JSON.parse(initEl.textContent || "{}");
        if (initData.config) {
          const provider = initData.config.providers?.[0];
          if (provider) {
            state.apiKey = provider.apiKey || "";
            state.baseUrl = provider.baseUrl || "https://api.anthropic.com/v1";
            state.models = provider.models || [];
          }
          state.enabled = initData.config.enabled !== false;
        }
      }
    } catch (err) {
      console.error("Failed to parse init data:", err);
    }

    render();
    // attachEventListeners() 已在 render() 内部调用
  }

  // 渲染 UI
  function render() {
    const app = document.getElementById("simple-app");
    if (!app) return;

    // 保存当前输入值（防止重新渲染时丢失）
    const currentApiKey = document.getElementById("claude-api-key")?.value || state.apiKey;
    const currentBaseUrl = document.getElementById("claude-base-url")?.value || state.baseUrl;
    state.apiKey = currentApiKey;
    state.baseUrl = currentBaseUrl;

    app.innerHTML = `
      <div class="simple-config-container">
        <div class="header">
          <h1>🚀 CodeFreeMax <small style="font-size: 0.5em; opacity: 0.7;">v3.2.0</small></h1>
          <p>快速配置 Claude API 端点和密钥 - <a href="https://github.com/ssmDo/kiro2api" target="_blank">查看项目文档</a></p>
        </div>

        <div class="config-section">
          <label for="claude-base-url">Claude API Base URL</label>
          <input
            type="text"
            id="claude-base-url"
            placeholder="https://api.anthropic.com/v1"
            value="${escapeHtml(state.baseUrl)}"
            autocomplete="off"
          />
          <small>默认使用官方端点，如需使用代理或中转服务请修改</small>
        </div>

        <div class="config-section">
          <label for="claude-api-key">Claude API Key</label>
          <input
            type="password"
            id="claude-api-key"
            placeholder="sk-ant-api03-xxx..."
            value="${escapeHtml(state.apiKey)}"
            autocomplete="off"
          />
          <small>从 <a href="https://console.anthropic.com/" target="_blank">Anthropic Console</a> 获取 API Key</small>
        </div>

        <div class="config-section">
          <div class="checkbox-wrapper">
            <input type="checkbox" id="enable-plugin" ${state.enabled ? "checked" : ""} />
            <label for="enable-plugin">启用插件（保存后生效）</label>
          </div>
        </div>

        <div class="actions">
          <button id="save-btn" class="primary">
            <span class="btn-text">保存配置</span>
          </button>
          <button id="test-btn" class="secondary">
            <span class="btn-text">测试连接</span>
          </button>
        </div>

        <div class="status status-${state.status}" id="status">
          <span class="status-icon">${getStatusIcon(state.status)}</span>
          <span class="status-text">${escapeHtml(state.statusMessage)}</span>
        </div>

        ${state.models.length > 0 ? `
        <div class="models-section">
          <h3>可用模型 (${state.models.length})</h3>
          <div class="models-list">
            ${state.models.map((model) => {
              const isDefault = state.defaultModel ? model === state.defaultModel : state.models.indexOf(model) === 0;
              return `
              <div class="model-item ${isDefault ? 'default' : ''}">
                ${escapeHtml(model)}${isDefault ? ' (默认)' : ''}
              </div>
            `;
            }).join('')}
          </div>
        </div>
        ` : ''}
      </div>
    `;

    // 重新绑定事件监听器（因为 innerHTML 重写会丢失之前的监听器）
    attachEventListeners();
  }

  // 绑定事件监听器
  function attachEventListeners() {
    const baseUrlInput = document.getElementById("claude-base-url");
    const apiKeyInput = document.getElementById("claude-api-key");
    const enableCheckbox = document.getElementById("enable-plugin");
    const saveBtn = document.getElementById("save-btn");
    const testBtn = document.getElementById("test-btn");

    if (baseUrlInput) {
      baseUrlInput.addEventListener("input", (e) => {
        state.baseUrl = e.target.value.trim();
      });
    }

    if (apiKeyInput) {
      apiKeyInput.addEventListener("input", (e) => {
        state.apiKey = e.target.value.trim();
      });
    }

    if (enableCheckbox) {
      enableCheckbox.addEventListener("change", (e) => {
        state.enabled = e.target.checked;
      });
    }

    if (saveBtn) {
      saveBtn.addEventListener("click", handleSave);
    }

    if (testBtn) {
      testBtn.addEventListener("click", handleTest);
    }
  }

  // 处理保存
  async function handleSave() {
    console.log("[BYOK Frontend] handleSave called");
    console.log("[BYOK Frontend] Current state:", state);

    if (!state.apiKey) {
      console.log("[BYOK Frontend] No API Key, showing error");
      updateStatus("error", "请输入 Claude API Key");
      return;
    }

    if (!state.baseUrl) {
      console.log("[BYOK Frontend] No Base URL, showing error");
      updateStatus("error", "请输入 Claude API Base URL");
      return;
    }

    updateStatus("testing", "正在保存配置...");
    disableButtons(true);

    const message = {
      type: "saveSimpleConfig",
      apiKey: state.apiKey,
      baseUrl: state.baseUrl,
      enabled: state.enabled
    };

    console.log("[BYOK Frontend] Sending message:", message);
    vscode.postMessage(message);
  }

  // 处理测试连接
  async function handleTest() {
    if (!state.apiKey) {
      updateStatus("error", "请输入 Claude API Key");
      return;
    }

    if (!state.baseUrl) {
      updateStatus("error", "请输入 Claude API Base URL");
      return;
    }

    updateStatus("testing", "正在测试连接...");
    disableButtons(true);

    vscode.postMessage({
      type: "testClaudeConnection",
      apiKey: state.apiKey,
      baseUrl: state.baseUrl
    });
  }

  // 更新状态
  function updateStatus(status, message) {
    state.status = status;
    state.statusMessage = message;

    const statusEl = document.getElementById("status");
    if (statusEl) {
      statusEl.className = `status status-${status}`;
      statusEl.innerHTML = `
        <span class="status-icon">${getStatusIcon(status)}</span>
        <span class="status-text">${escapeHtml(message)}</span>
      `;
    }
  }

  // 获取状态图标
  function getStatusIcon(status) {
    const icons = {
      unconfigured: "⏳",
      testing: '<span class="spinner"></span>',
      success: "✅",
      error: "❌"
    };
    return icons[status] || "⏳";
  }

  // 禁用/启用按钮
  function disableButtons(disabled) {
    const saveBtn = document.getElementById("save-btn");
    const testBtn = document.getElementById("test-btn");

    if (saveBtn) saveBtn.disabled = disabled;
    if (testBtn) testBtn.disabled = disabled;
  }

  // HTML 转义
  function escapeHtml(str) {
    const div = document.createElement("div");
    div.textContent = str;
    return div.innerHTML;
  }

  // 处理来自后端的消息
  window.addEventListener("message", (event) => {
    const message = event.data;
    console.log("[BYOK Frontend] Received message from backend:", message);

    switch (message.type) {
      case "saveSuccess":
        console.log("[BYOK Frontend] Save success");
        state.models = message.models || [];
        state.defaultModel = message.defaultModel || "";
        updateStatus("success", message.message || "配置保存成功！");
        disableButtons(false);
        render();
        break;

      case "saveFailed":
        console.log("[BYOK Frontend] Save failed:", message.error);
        updateStatus("error", message.error || "保存失败");
        disableButtons(false);
        break;

      case "testSuccess":
        console.log("[BYOK Frontend] Test success");
        state.models = message.models || [];
        state.defaultModel = message.defaultModel || "";
        updateStatus("success", `连接成功！找到 ${message.models?.length || 0} 个模型`);
        disableButtons(false);
        render();
        break;

      case "testFailed":
        console.log("[BYOK Frontend] Test failed:", message.error);
        updateStatus("error", message.error || "连接失败");
        disableButtons(false);
        break;

      case "statusUpdate":
        console.log("[BYOK Frontend] Status update:", message.status, message.message);
        updateStatus(message.status, message.message);
        break;

      default:
        console.log("[BYOK Frontend] Unknown message type:", message.type);
    }
  });

  // 启动
  if (document.readyState === "loading") {
    document.addEventListener("DOMContentLoaded", init);
  } else {
    init();
  }
})();

