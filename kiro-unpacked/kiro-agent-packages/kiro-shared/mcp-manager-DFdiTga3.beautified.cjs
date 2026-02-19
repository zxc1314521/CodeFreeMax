"use strict";
var __defProp = Object.defineProperty;
var __defNormalProp = (obj, key, value) => key in obj ? __defProp(obj, key, {
  enumerable: true,
  configurable: true,
  writable: true,
  value
}) : obj[key] = value;
var __publicField = (obj, key, value) => __defNormalProp(obj, typeof key !== "symbol" ? key + "" : key, value);
const vscode = require("vscode");
const telemetry_definitions_index = require("./telemetry/definitions/index.cjs");
const ignore = require("./ignore-D645GLpP.cjs");
const path = require("path");
require("os");
const fs = require("fs");
require("node-machine-id");
require("axios");
require("axios-retry");
const index_js = require("@modelcontextprotocol/sdk/client/index.js");
const stdio_js = require("@modelcontextprotocol/sdk/client/stdio.js");
const paths = require("./paths-C6z4_Obm.cjs");
const zod = require("zod");
const JSONC = require("comment-json");
const types_js = require("@modelcontextprotocol/sdk/types.js");
const sse_js = require("@modelcontextprotocol/sdk/client/sse.js");
const streamableHttp_js = require("@modelcontextprotocol/sdk/client/streamableHttp.js");
const crypto = require("crypto");
const auth_js = require("@modelcontextprotocol/sdk/client/auth.js");
const http = require("http");
require("@opentelemetry/api");
require("./web-fetch-meter-DNWId8KO.cjs");

function _interopNamespaceDefault(e) {
  const n = Object.create(null, {
    [Symbol.toStringTag]: {
      value: "Module"
    }
  });
  if (e) {
    for (const k in e) {
      if (k !== "default") {
        const d = Object.getOwnPropertyDescriptor(e, k);
        Object.defineProperty(n, k, d.get ? d : {
          enumerable: true,
          get: () => e[k]
        });
      }
    }
  }
  n.default = e;
  return Object.freeze(n);
}
const vscode__namespace = /* @__PURE__ */ _interopNamespaceDefault(vscode);
const path__namespace = /* @__PURE__ */ _interopNamespaceDefault(path);
const fs__namespace = /* @__PURE__ */ _interopNamespaceDefault(fs);
const JSONC__namespace = /* @__PURE__ */ _interopNamespaceDefault(JSONC);
const http__namespace = /* @__PURE__ */ _interopNamespaceDefault(http);
const MCPOptionsSchema = zod.z.object({
  // Local (STDIO) options
  command: zod.z.string().optional(),
  args: zod.z.array(zod.z.string()).optional(),
  env: zod.z.record(zod.z.string()).optional(),
  cwd: zod.z.string().optional(),
  // Remote (StreamableHTTP / SSE) options
  url: zod.z.string().optional(),
  headers: zod.z.record(zod.z.string()).optional(),
  // Common options
  disabled: zod.z.boolean().default(false),
  autoApprove: zod.z.array(zod.z.string()).optional(),
  disabledTools: zod.z.array(zod.z.string()).optional()
});
const MCPJsonConfigSchema = zod.z.object({
  mcpServers: zod.z.record(MCPOptionsSchema),
  powers: zod.z.object({
    mcpServers: zod.z.record(MCPOptionsSchema)
  }).optional()
});
const APPROVED_ENV_VARS_KEY = "mcpApprovedEnvVars";
let hasShownWarningThisSession = false;
const globalUnapprovedVarsFound = /* @__PURE__ */ new Set();
async function showUnapprovedVarsWarningIfNeeded() {
  if (globalUnapprovedVarsFound.size > 0 && !hasShownWarningThisSession) {
    hasShownWarningThisSession = true;
    const unapprovedVars = Array.from(globalUnapprovedVarsFound);
    ignore.mcpLogger.warn(`Found unapproved environment variables in MCP config: ${unapprovedVars.join(", ")}`);
    const message =
      `🔒 Security Warning: Your MCP configuration contains environment variables that have not been approved: ${unapprovedVars.join(", ")}. These variables will not be expanded unless you approve them. Expanding untrusted environment variables could pose security risks.`;
    const selection = await vscode__namespace.window.showErrorMessage(message, "Approve & Allow");
    if (selection === "Approve & Allow") {
      const currentApproved = vscode__namespace.workspace.getConfiguration("kiroAgent").get(APPROVED_ENV_VARS_KEY,
    []);
      const updatedApproved = [... /* @__PURE__ */ new Set([...currentApproved, ...unapprovedVars])];
      await vscode__namespace.workspace.getConfiguration("kiroAgent").update(APPROVED_ENV_VARS_KEY, updatedApproved,
        vscode__namespace.ConfigurationTarget.Global);
      ignore.mcpLogger.info(`User approved environment variables: ${unapprovedVars.join(", ")}`);
      hasShownWarningThisSession = false;
      const configLocation = paths.getActiveMcpConfigLocation(getWorkspaceDirs());
      const allConfigPaths = [
        ...configLocation.workspaceConfigPaths,
        ...configLocation.userConfigPath ? [configLocation.userConfigPath] : []
      ];
      for (const configPath of allConfigPaths) {
        try {
          const now = /* @__PURE__ */ new Date();
          fs__namespace.utimesSync(configPath, now, now);
        } catch (e) {
          ignore.mcpLogger.error(
            `Failed to trigger config reload for ${configPath}: ${e instanceof Error ? e.message : String(e)}`
          );
        }
      }
      await vscode__namespace.window.showInformationMessage(
        "✅ Variables approved. Environment variables are now being expanded and MCP servers are reconnecting."
      );
    }
  }
}

function loadPowersMcpConfig() {
  const userConfigPath = path__namespace.join(paths.getHomeKiroPath(), "settings", "mcp.json");
  if (!fs__namespace.existsSync(userConfigPath)) {
    return null;
  }
  try {
    const rawContent = fs__namespace.readFileSync(userConfigPath, "utf-8");
    const parsed = JSONC__namespace.parse(rawContent);
    if (parsed && typeof parsed === "object" && "powers" in parsed && parsed.powers && typeof parsed.powers ===
      "object" && "mcpServers" in parsed.powers && typeof parsed.powers.mcpServers === "object") {
      const expandedPowers = expandEnvironmentVariables(parsed.powers);
      const expandedPowersTyped = expandedPowers;
      const powersConfigToValidate = {
        mcpServers: expandedPowersTyped.mcpServers
      };
      const result = MCPJsonConfigSchema.safeParse(powersConfigToValidate);
      if (result.success) {
        const validServers = {};
        Object.entries(result.data.mcpServers).forEach((entry) => {
          const validationResult = deepValidateMCPServerOptions(entry[0], entry[1]);
          if (validationResult.isValid) {
            validServers[entry[0]] = entry[1];
          } else {
            ignore.mcpLogger.warn(validationResult.invalidMessage || "", entry[0]);
            void surfaceConfigError(validationResult.invalidMessage || "", "powers", userConfigPath);
          }
        });
        const serverNames = Object.keys(validServers);
        ignore.mcpLogger.info(
          `[Powers Debug] loadPowersMcpConfig found ${serverNames.length} valid power servers: ${serverNames.join(", ")}`
        );
        return {
          mcpServers: validServers
        };
      } else {
        void surfaceConfigError(`Invalid powers config format: ${result.error.message}`, "powers", userConfigPath);
        return null;
      }
    }
    ignore.mcpLogger.warn("[Powers Debug] No powers.mcpServers section found in user mcp.json");
    return null;
  } catch (error) {
    const errorMsg = `Error loading powers config: ${error instanceof Error ? error.message : String(error)}`;
    ignore.mcpLogger.error("[Powers Debug] " + errorMsg);
    void surfaceConfigError(errorMsg, "powers", userConfigPath);
    return null;
  }
}
const mcpServerSources = /* @__PURE__ */ new Map();

function loadMcpConfig() {
  globalUnapprovedVarsFound.clear();
  hasShownWarningThisSession = false;
  mcpServerSources.clear();
  const configLocation = paths.getActiveMcpConfigLocation(getWorkspaceDirs());
  const userConfig = loadIndividualMcpConfig("user", configLocation.userConfigPath);
  const workspaceConfigs = configLocation.workspaceConfigPaths.map(
    (path2) => loadIndividualMcpConfig("workspace", path2)
  );
  const powersConfig = loadPowersMcpConfig();
  const finalConfig = {
    mcpServers: {}
  };
  if (userConfig) {
    for (const serverName of Object.keys(userConfig.mcpServers)) {
      finalConfig.mcpServers[serverName] = userConfig.mcpServers[serverName];
      mcpServerSources.set(serverName, "user");
    }
  }
  for (const workspaceConfig of workspaceConfigs) {
    if (workspaceConfig) {
      for (const serverName of Object.keys(workspaceConfig.mcpServers)) {
        finalConfig.mcpServers[serverName] = workspaceConfig.mcpServers[serverName];
        mcpServerSources.set(serverName, "workspace");
      }
    }
  }
  if (powersConfig) {
    for (const serverName of Object.keys(powersConfig.mcpServers)) {
      finalConfig.mcpServers[serverName] = powersConfig.mcpServers[serverName];
      mcpServerSources.set(serverName, "power");
    }
  }
  if (Object.keys(finalConfig.mcpServers).length === 0) {
    return null;
  }
  const powerServers = Array.from(mcpServerSources.entries()).filter(([_, source]) => source === "power").map(([name,
    _]) => name);
  if (powerServers.length > 0) {
    ignore.mcpLogger.info(`[Powers Debug] Loaded ${powerServers.length} power MCP servers: ${powerServers.join(", ")}`);
  }
  void showUnapprovedVarsWarningIfNeeded();
  return finalConfig;
}

function expandEnvironmentVariables(value) {
  if (typeof value === "string") {
    const approvedVars = vscode__namespace.workspace.getConfiguration("kiroAgent").get(APPROVED_ENV_VARS_KEY, []);
    return value.replace(/\$\{([^}]+)\}/g, (match, varName) => {
      if (!approvedVars.includes(varName)) {
        globalUnapprovedVarsFound.add(varName);
        return match;
      }
      const envValue = process.env[varName];
      if (envValue !== void 0) {
        if (envValue.trim().startsWith("()")) {
          return match;
        }
        ignore.mcpLogger.debug(`Expanded environment variable: ${varName}`);
        return envValue;
      }
      return match;
    });
  }
  if (Array.isArray(value)) {
    return value.map((item) => expandEnvironmentVariables(item));
  }
  if (value && typeof value === "object") {
    const expanded = {};
    for (const [key, val] of Object.entries(value)) {
      expanded[key] = expandEnvironmentVariables(val);
    }
    return expanded;
  }
  return value;
}

function loadIndividualMcpConfig(sourceName, path2) {
  if (!path2) return null;
  try {
    const configContent = fs__namespace.readFileSync(path2, "utf8");
    const parsedJson = JSONC__namespace.parse(configContent);
    const expandedJson = expandEnvironmentVariables(parsedJson);
    const result = MCPJsonConfigSchema.safeParse(expandedJson);
    if (result.success) {
      const validServers = {};
      Object.entries(result.data.mcpServers).forEach((entry) => {
        const validationResult = deepValidateMCPServerOptions(entry[0], entry[1]);
        if (validationResult.isValid) {
          validServers[entry[0]] = entry[1];
        } else {
          ignore.mcpLogger.warn(validationResult.invalidMessage || "", entry[0]);
          void surfaceConfigError(validationResult.invalidMessage || "", sourceName, path2);
        }
      });
      return {
        mcpServers: validServers,
        powers: result.data.powers
      };
    } else {
      void surfaceConfigError(
        `Invalid mcp.json format in ${sourceName} directory: ${result.error.message}`,
        sourceName,
        path2
      );
      return null;
    }
  } catch (e) {
    void surfaceConfigError(
      `Error loading mcp.json from ${sourceName} directory: ${e instanceof Error ? e.message : String(e)}`,
      sourceName,
      path2
    );
    return null;
  }
}
async function surfaceConfigError(errorMsg, sourceName, configPath) {
  ignore.mcpLogger.error(errorMsg);
  ignore.mcpLogger.show();
  const selection = await vscode__namespace.window.showErrorMessage(errorMsg, "Ask Kiro", "Open Settings");
  if (selection === "Ask Kiro") {
    const message = `I'm getting this MCP configuration error: "${errorMsg}". Can you help me fix it?`;
    await vscode__namespace.commands.executeCommand("kiroAgent.userInputFocusNoSubmit", message);
  } else if (selection === "Open Settings") {
    if (sourceName === "workspace") {
      await vscode__namespace.commands.executeCommand("kiroAgent.openWorkspaceMcpConfig", false, configPath);
    } else {
      await vscode__namespace.commands.executeCommand("kiroAgent.openUserMcpConfig", false);
    }
  }
}

function deepValidateMCPServerOptions(serverName, options) {
  if (!options.disabled && !(options.command || options.url)) {
    return {
      isValid: false,
      invalidMessage: `Enabled MCP Server ${serverName} must specify a command or URL, ignoring.`
    };
  }
  if (options.url) {
    let parsedUrl;
    try {
      parsedUrl = new URL(options.url);
    } catch {
      return {
        isValid: false,
        invalidMessage: `Invalid MCP Server ${serverName} URL: ${options.url}, ignoring.`
      };
    }
    if (parsedUrl.protocol !== "https:" && !["localhost", "127.0.0.1"].includes(parsedUrl.hostname)) {
      return {
        isValid: false,
        invalidMessage: `Remote MCP Servers must use https or localhost, ignoring.`
      };
    }
  }
  return {
    isValid: true
  };
}
async function addMCPServerConfig(serverName, config) {
  await vscode__namespace.commands.executeCommand("kiroAgent.openUserMcpConfig");
  const userConfigLocation = paths.getActiveMcpConfigLocation(getWorkspaceDirs());
  if (!userConfigLocation.userConfigPath) {
    void vscode__namespace.window.showErrorMessage("Failed to create User MCP server config");
    return;
  }
  const currentConfig = loadIndividualMcpConfig("user", userConfigLocation.userConfigPath);
  if (!currentConfig) {
    return;
  }
  if (serverName in currentConfig.mcpServers) {
    void vscode__namespace.window.showErrorMessage(`MCP Server ${serverName} already exists in user config`);
    return;
  }
  let newServerConfig;
  try {
    const parsed = JSONC__namespace.parse(config);
    if (!parsed || typeof parsed !== "object" || Array.isArray(parsed)) {
      throw new Error(`Invalid JSON object: ${config}`);
    }
    newServerConfig = {
      ...parsed,
      disabled: true
    };
  } catch (e) {
    void vscode__namespace.window.showErrorMessage(
      `Invalid MCP server config: ${e instanceof Error ? e.message : String(e)}`);
    return;
  }
  const newConfig = {
    ...currentConfig,
    mcpServers: {
      ...currentConfig.mcpServers,
      [serverName]: newServerConfig
    }
  };
  fs__namespace.writeFileSync(userConfigLocation.userConfigPath, JSONC__namespace.stringify(newConfig, null, 2));
  const selection = await vscode__namespace.window.showInformationMessage(
    `MCP Server "${serverName}" added to user config, would you like to enable it?`,
    "Enable"
  );
  if (selection === "Enable") {
    setMCPServerDisabled(serverName, false);
  }
}

function setMCPServerDisabled(serverName, disabled) {
  const disableServerTransform = (options) => {
    return {
      ...options,
      disabled
    };
  };
  applyServerConfigTransform(serverName, disableServerTransform);
}

function enableMCPTools(serverName, toolNames) {
  const enableToolsTransform = (options) => {
    const currentDisabledTools = options.disabledTools || [];
    const updatedDisabledTools = currentDisabledTools.filter((val) => !toolNames.includes(val));
    return {
      ...options,
      disabledTools: updatedDisabledTools
    };
  };
  applyServerConfigTransform(serverName, enableToolsTransform);
}

function disableMCPTools(serverName, toolNames) {
  const disableToolsTransform = (options) => {
    const currentDisabledTools = options.disabledTools || [];
    const toolsToDisable = toolNames.filter((it) => !currentDisabledTools.includes(it));
    const updatedDisabledTools = currentDisabledTools.concat(toolsToDisable);
    return {
      ...options,
      disabledTools: updatedDisabledTools
    };
  };
  applyServerConfigTransform(serverName, disableToolsTransform);
}
async function addMCPToolToAutoApproveConfig(serverName, toolName) {
  const autoApproveToolsTransform = (options) => {
    return {
      ...options,
      autoApprove: (options.autoApprove || []).concat(toolName)
    };
  };
  applyServerConfigTransform(serverName, autoApproveToolsTransform);
  const addedMessage = `Tool ${toolName} added to auto-approve list`;
  ignore.mcpLogger.info(addedMessage, serverName);
  const selection = await vscode__namespace.window.showInformationMessage(addedMessage, "Open Settings");
  if (selection === "Open Settings") {
    const matchingConfig = findConfigFileForServer(serverName);
    if (matchingConfig.sourceName === "workspace") {
      await vscode__namespace.commands.executeCommand("kiroAgent.openWorkspaceMcpConfig");
    } else {
      await vscode__namespace.commands.executeCommand("kiroAgent.openUserMcpConfig");
    }
  }
}

function applyServerConfigTransform(serverName, transform) {
  const matchingConfig = findConfigFileForServer(serverName);
  const rawContent = fs__namespace.readFileSync(matchingConfig.path, "utf-8");
  const parsed = JSONC__namespace.parse(rawContent);
  const fullConfig = parsed && typeof parsed === "object" ? parsed : {};
  if (matchingConfig.sourceName === "powers") {
    if (!fullConfig.powers) {
      fullConfig.powers = {
        mcpServers: {}
      };
    }
    if (!fullConfig.powers.mcpServers) {
      fullConfig.powers.mcpServers = {};
    }
    const existingConfig = fullConfig.powers.mcpServers[serverName] ?? {};
    fullConfig.powers.mcpServers[serverName] = transform(existingConfig);
  } else {
    if (!fullConfig.mcpServers) {
      fullConfig.mcpServers = {};
    }
    const existingConfig = fullConfig.mcpServers[serverName] ?? {};
    fullConfig.mcpServers[serverName] = transform(existingConfig);
  }
  fs__namespace.writeFileSync(matchingConfig.path, JSONC__namespace.stringify(fullConfig, null, 2));
}

function findConfigFileForServer(serverName) {
  var _a, _b;
  const configLocation = paths.getActiveMcpConfigLocation(getWorkspaceDirs());
  if (!configLocation.userConfigPath && configLocation.workspaceConfigPaths.length === 0) {
    throw new Error("No MCP config file found");
  }
  for (let i = configLocation.workspaceConfigPaths.length - 1; i >= 0; i--) {
    const workspacePath = configLocation.workspaceConfigPaths[i];
    const config = loadIndividualMcpConfig("workspace", workspacePath);
    if (config && serverName in config.mcpServers) {
      return {
        path: workspacePath,
        config,
        sourceName: "workspace"
      };
    }
  }
  if (configLocation.userConfigPath) {
    const config = loadIndividualMcpConfig("user", configLocation.userConfigPath);
    if (config && serverName in config.mcpServers) {
      return {
        path: configLocation.userConfigPath,
        config,
        sourceName: "user"
      };
    }
    const rawContent = fs__namespace.readFileSync(configLocation.userConfigPath, "utf-8");
    const parsed = JSONC__namespace.parse(rawContent);
    const fullConfig = parsed && typeof parsed === "object" ? parsed : {};
    if ((_b = (_a = fullConfig.powers) == null ? void 0 : _a.mcpServers) == null ? void 0 : _b[serverName]) {
      const powersConfig = {
        mcpServers: fullConfig.powers.mcpServers
      };
      return {
        path: configLocation.userConfigPath,
        config: powersConfig,
        sourceName: "powers"
      };
    }
  }
  throw new Error(`Server ${serverName} not found in any MCP config file`);
}

function getWorkspaceDirs() {
  const workspaceFolders = vscode__namespace.workspace.workspaceFolders;
  return workspaceFolders == null ? void 0 : workspaceFolders.map((folder) => folder.uri.fsPath);
}

function resetApprovedEnvVars() {
  vscode__namespace.workspace.getConfiguration("kiroAgent").update(APPROVED_ENV_VARS_KEY, [], vscode__namespace
    .ConfigurationTarget.Global);
  hasShownWarningThisSession = false;
  ignore.mcpLogger.info("Reset approved environment variables list");
}
class CredentialStorageManager {
  constructor(secretStorage, options) {
    __publicField(this, "secretStorage");
    __publicField(this, "connectionHash");
    __publicField(this, "keyPrefix", "kiro.mcp");
    this.secretStorage = secretStorage;
    this.connectionHash = this.calculateConnectionHash(options.url || "", options.headers || {});
  }
  /**
   * Calculate a unique hash from server URL and headers to isolate credentials
   * per server configuration.
   */
  calculateConnectionHash(serverUrl, headers) {
    const normalizedUrl = serverUrl.trim().toLowerCase();
    const sortedHeaders = Object.keys(headers).sort().map((key) => `${key}:${headers[key]}`).join("|");
    const combined = `${normalizedUrl}|${sortedHeaders}`;
    return crypto.createHash("sha256").update(combined).digest("hex");
  }
  /**
   * Get the storage key for client information
   */
  getClientKey() {
    return `${this.keyPrefix}.${this.connectionHash}.client`;
  }
  /**
   * Get the storage key for tokens
   */
  getTokensKey() {
    return `${this.keyPrefix}.${this.connectionHash}.tokens`;
  }
  /**
   * Get the storage key for code verifier
   */
  getVerifierKey() {
    return `${this.keyPrefix}.${this.connectionHash}.verifier`;
  }
  /**
   * Save OAuth client information to SecretStorage
   */
  async saveClientInfo(clientInfo) {
    try {
      const stored = {
        client_id: clientInfo.client_id,
        client_secret: clientInfo.client_secret,
        client_id_issued_at: clientInfo.client_id_issued_at,
        client_secret_expires_at: clientInfo.client_secret_expires_at,
        created_at: Date.now()
      };
      await this.secretStorage.store(this.getClientKey(), JSON.stringify(stored));
    } catch (error) {
      throw new Error(`Failed to save client information: ${error instanceof Error ? error.message : String(error)}`);
    }
  }
  /**
   * Type guard to validate StoredClientInfo structure
   */
  isValidStoredClientInfo(obj) {
    return obj !== null && typeof obj === "object" && "client_id" in obj && typeof obj.client_id === "string" && obj
      .client_id.length > 0;
  }
  /**
   * Type guard to validate StoredTokens structure
   */
  isValidStoredTokens(obj) {
    return obj !== null && typeof obj === "object" && "access_token" in obj && "token_type" in obj && typeof obj
      .access_token === "string" && typeof obj.token_type === "string" && obj.access_token.length > 0 && obj
      .token_type.length > 0;
  }
  /**
   * Type guard to validate StoredVerifier structure
   */
  isValidStoredVerifier(obj) {
    return obj !== null && typeof obj === "object" && "code_verifier" in obj && typeof obj.code_verifier ===
      "string" && obj.code_verifier.length > 0;
  }
  /**
   * Load OAuth client information from SecretStorage
   */
  async loadClientInfo() {
    try {
      const stored = await this.secretStorage.get(this.getClientKey());
      if (!stored) {
        return void 0;
      }
      const parsed = JSON.parse(stored);
      if (!this.isValidStoredClientInfo(parsed)) {
        await this.clearCredentials("client");
        return void 0;
      }
      return parsed;
    } catch {
      await this.clearCredentials("client");
      return void 0;
    }
  }
  /**
   * Save OAuth tokens to SecretStorage with timestamp metadata
   */
  async saveTokens(tokens) {
    try {
      const now = Date.now();
      const stored = {
        access_token: tokens.access_token,
        refresh_token: tokens.refresh_token,
        token_type: tokens.token_type,
        expires_in: tokens.expires_in,
        scope: tokens.scope,
        created_at: now,
        // Calculate expires_at if expires_in is provided
        expires_at: tokens.expires_in ? now + tokens.expires_in * 1e3 : void 0
      };
      await this.secretStorage.store(this.getTokensKey(), JSON.stringify(stored));
    } catch (error) {
      throw new Error(`Failed to save tokens: ${error instanceof Error ? error.message : String(error)}`);
    }
  }
  /**
   * Load OAuth tokens from SecretStorage
   */
  async loadTokens() {
    try {
      const stored = await this.secretStorage.get(this.getTokensKey());
      if (!stored) {
        return void 0;
      }
      const parsed = JSON.parse(stored);
      if (!this.isValidStoredTokens(parsed)) {
        await this.clearCredentials("tokens");
        return void 0;
      }
      return parsed;
    } catch {
      await this.clearCredentials("tokens");
      return void 0;
    }
  }
  /**
   * Save PKCE code verifier to SecretStorage
   */
  async saveCodeVerifier(verifier) {
    try {
      const stored = {
        code_verifier: verifier,
        created_at: Date.now()
      };
      await this.secretStorage.store(this.getVerifierKey(), JSON.stringify(stored));
    } catch (error) {
      throw new Error(`Failed to save code verifier: ${error instanceof Error ? error.message : String(error)}`);
    }
  }
  /**
   * Load PKCE code verifier from SecretStorage
   */
  async loadCodeVerifier() {
    try {
      const stored = await this.secretStorage.get(this.getVerifierKey());
      if (!stored) {
        return void 0;
      }
      const parsed = JSON.parse(stored);
      if (!this.isValidStoredVerifier(parsed)) {
        await this.clearCredentials("verifier");
        return void 0;
      }
      return parsed.code_verifier;
    } catch {
      await this.clearCredentials("verifier");
      return void 0;
    }
  }
  /**
   * Clear credentials from SecretStorage based on scope
   * @param scope - Which credentials to clear: 'all', 'client', 'tokens', or 'verifier'
   */
  async clearCredentials(scope) {
    try {
      switch (scope) {
        case "all":
          await Promise.all([
            this.secretStorage.delete(this.getClientKey()),
            this.secretStorage.delete(this.getTokensKey()),
            this.secretStorage.delete(this.getVerifierKey())
          ]);
          break;
        case "client":
          await this.secretStorage.delete(this.getClientKey());
          break;
        case "tokens":
          await this.secretStorage.delete(this.getTokensKey());
          break;
        case "verifier":
          await this.secretStorage.delete(this.getVerifierKey());
          break;
      }
    } catch (error) {
      throw new Error(`Failed to clear credentials: ${error instanceof Error ? error.message : String(error)}`);
    }
  }
}
class MCPAuthProvider {
  /**
   * Creates a new MCP OAuth authentication provider.
   * @param secretStorage - VS Code's secret storage for persisting credentials across sessions.
   *                       If undefined, credentials will only be stored in memory.
   * @param options - MCP configuration options containing server-specific settings
   * @param startOAuth - Whether this provider should initiate OAuth flows. Set to false
   *                    if credentials are already available and no new flow is needed.
   */
  constructor(secretStorage, options, startOAuth) {
    /** The OAuth redirect URL for the authorization flow */
    __publicField(this, "_redirectUrl");
    /** Base OAuth client metadata configuration */
    __publicField(this, "_baseClientMetadata");
    /** OAuth state parameter for CSRF protection */
    __publicField(this, "_state");
    /** Optional credential storage manager for persistence */
    __publicField(this, "credentialStorage");
    /** In-memory cache for OAuth client information (session-scoped) */
    __publicField(this, "_clientInformation");
    /** In-memory cache for OAuth tokens (session-scoped) */
    __publicField(this, "_tokens");
    /** In-memory cache for PKCE code verifier (session-scoped) */
    __publicField(this, "_codeVerifier");
    this.startOAuth = startOAuth;
    this._baseClientMetadata = {
      redirect_uris: [],
      // Will be populated dynamically
      client_name: "kiro",
      grant_types: ["authorization_code", "refresh_token"],
      response_types: ["code"],
      token_endpoint_auth_method: "client_secret_basic"
    };
    this._state = crypto.randomUUID();
    if (secretStorage) {
      this.credentialStorage = new CredentialStorageManager(secretStorage, options);
    }
  }
  /**
   * Gets the OAuth redirect URL for the authorization flow.
   * @returns The redirect URL where the authorization server will send the user after authentication.
   *          Returns a placeholder URL if OAuth flow is not intended to start.
   * @throws {Error} If no redirect URL is available when OAuth flow should start
   */
  get redirectUrl() {
    if (!this.startOAuth) {
      return "http://localhost";
    }
    if (!this._redirectUrl) {
      throw new Error("No redirect URL available");
    }
    return this._redirectUrl;
  }
  /**
   * Sets the OAuth redirect URL for the authorization flow.
   * @param url - The redirect URL where the authorization server will send the user after authentication
   */
  set redirectUrl(url) {
    this._redirectUrl = url;
  }
  /**
   * Gets the OAuth client metadata including the current redirect URL.
   * @returns Complete OAuth client metadata with redirect URIs populated
   */
  get clientMetadata() {
    return {
      ...this._baseClientMetadata,
      redirect_uris: [this.redirectUrl]
    };
  }
  /**
   * Gets the OAuth state parameter for CSRF protection.
   * @returns A unique state string used to prevent cross-site request forgery attacks
   */
  state() {
    return this._state;
  }
  /**
   * Retrieves the OAuth client information (client ID, secret, etc.).
   *
   * First checks the in-memory cache, then falls back to persistent storage if available.
   * @returns Promise resolving to client information if available, undefined otherwise
   */
  async clientInformation() {
    if (this._clientInformation) {
      return this._clientInformation;
    }
    if (this.credentialStorage) {
      this._clientInformation = await this.credentialStorage.loadClientInfo();
      return this._clientInformation;
    }
    return void 0;
  }
  /**
   * Saves OAuth client information to both memory and persistent storage.
   *
   * Extracts the essential client information from the full client data and stores it
   * in the in-memory cache and optionally in persistent storage.
   * @param clientInformation - Complete OAuth client information received from the authorization server
   */
  async saveClientInformation(clientInformation) {
    const clientInfo = {
      client_id: clientInformation.client_id,
      client_secret: clientInformation.client_secret,
      client_id_issued_at: clientInformation.client_id_issued_at,
      client_secret_expires_at: clientInformation.client_secret_expires_at
    };
    this._clientInformation = clientInfo;
    if (this.credentialStorage) {
      await this.credentialStorage.saveClientInfo(clientInfo);
    }
  }
  /**
   * Retrieves the OAuth tokens (access token, refresh token, etc.).
   *
   * First checks the in-memory cache, then falls back to persistent storage if available.
   * @returns Promise resolving to OAuth tokens if available, undefined otherwise
   */
  async tokens() {
    if (this._tokens) {
      return this._tokens;
    }
    if (this.credentialStorage) {
      this._tokens = await this.credentialStorage.loadTokens();
      return this._tokens;
    }
    return void 0;
  }
  /**
   * Saves OAuth tokens to both memory and persistent storage.
   * @param tokens - OAuth tokens including access token, refresh token, and metadata
   */
  async saveTokens(tokens) {
    this._tokens = tokens;
    if (this.credentialStorage) {
      await this.credentialStorage.saveTokens(tokens);
    }
  }
  /**
   * Redirects the user to the OAuth authorization URL.
   *
   * Opens the authorization URL in the user's default browser if OAuth flow should start.
   * If the browser fails to open, shows an error message with the URL for manual copying.
   * @param authorizationUrl - The OAuth authorization URL to redirect the user to
   * @throws {Error} If the browser fails to open and manual intervention is required
   */
  async redirectToAuthorization(authorizationUrl) {
    try {
      if (this.startOAuth) {
        await vscode__namespace.env.openExternal(authorizationUrl.href);
      }
    } catch (error) {
      vscode__namespace.window.showErrorMessage(
        `Failed to open browser for authentication. Please copy and paste the URL into your browser: ${authorizationUrl}`
      );
      throw new Error(`Failed to open browser.`);
    }
  }
  /**
   * Saves the PKCE code verifier for the OAuth flow.
   *
   * The code verifier is used in the Proof Key for Code Exchange (PKCE) extension
   * to OAuth 2.0 for enhanced security in public clients.
   * @param codeVerifier - The randomly generated code verifier string
   */
  async saveCodeVerifier(codeVerifier) {
    this._codeVerifier = codeVerifier;
    if (this.credentialStorage) {
      await this.credentialStorage.saveCodeVerifier(codeVerifier);
    }
  }
  /**
   * Retrieves the PKCE code verifier for the OAuth flow.
   *
   * First checks the in-memory cache, then falls back to persistent storage if available.
   * @returns Promise resolving to the code verifier string
   * @throws {Error} If no code verifier is found in memory or storage
   */
  async codeVerifier() {
    if (this._codeVerifier) {
      return this._codeVerifier;
    }
    if (this.credentialStorage) {
      this._codeVerifier = await this.credentialStorage.loadCodeVerifier();
      if (this._codeVerifier) {
        return this._codeVerifier;
      }
    }
    throw new Error("Code verifier not found. Make sure to call saveCodeVerifier first.");
  }
  /**
   * Invalidates and clears credentials based on the specified scope.
   *
   * Clears credentials from both the in-memory cache and persistent storage.
   * This is useful for logout functionality or when credentials become invalid.
   * @param scope - The scope of credentials to invalidate:
   *                - 'all': Clear all credentials (client info, tokens, code verifier)
   *                - 'client': Clear only client information
   *                - 'tokens': Clear only OAuth tokens
   *                - 'verifier': Clear only the code verifier
   */
  async invalidateCredentials(scope) {
    switch (scope) {
      case "all":
        this._clientInformation = void 0;
        this._tokens = void 0;
        this._codeVerifier = void 0;
        break;
      case "client":
        this._clientInformation = void 0;
        break;
      case "tokens":
        this._tokens = void 0;
        break;
      case "verifier":
        this._codeVerifier = void 0;
        break;
    }
    if (this.credentialStorage) {
      await this.credentialStorage.clearCredentials(scope);
    }
  }
}
class OAuthRedirectServer {
  constructor() {
    __publicField(this, "server");
    __publicField(this, "callbackUrl");
    __publicField(this, "callbackPromise", null);
    __publicField(this, "callbackResolve", null);
    __publicField(this, "callbackReject", null);
    __publicField(this, "serverCloseTimeout", 5e3);
  }
  // 5 seconds timeout for server close
  /**
   * Starts the OAuth redirect server on an available port.
   * @returns Promise that resolves with the URL for callback when server is ready
   */
  async start() {
    ignore.mcpLogger.info("Starting server for MCP OAuth redirect...");
    try {
      this.callbackUrl = await this.attemptServerStart();
      ignore.mcpLogger.info(`Server for MCP OAuth redirect started on ${this.callbackUrl}`);
      return this.callbackUrl;
    } catch (error) {
      throw new Error(
        `Failed to start OAuth redirect server: ${error instanceof Error ? error.message : "Unknown error"}`
      );
    }
  }
  /**
   * Attempts to start the server once.
   */
  attemptServerStart() {
    return new Promise((resolve, reject) => {
      this.server = http__namespace.createServer(this.handleRequest.bind(this));
      this.server.on("error", (error) => reject(error));
      this.server.on("listening", () => {
        var _a;
        const address = (_a = this.server) == null ? void 0 : _a.address();
        if (address && typeof address === "object") {
          this.callbackUrl = `http://localhost:${address.port}/oauth/callback`;
          resolve(this.callbackUrl);
        } else {
          reject(new Error("Failed to get server address after successful listen"));
        }
      });
      try {
        this.server.listen(0, "localhost");
      } catch (error) {
        reject(new Error(
          `Failed to start listening: ${error instanceof Error ? error.message : "Unknown error"}`));
      }
    });
  }
  /**
   * Stops the OAuth redirect server and cleans up resources with timeout protection.
   * @returns Promise that resolves when server is fully stopped
   */
  async stop() {
    ignore.mcpLogger.info("Stopping server for MCP OAuth redirect");
    if (!this.server) {
      return;
    }
    return new Promise((resolve, reject) => {
      var _a;
      const timeoutId = setTimeout(() => {
        void this.forceCleanup().then(resolve, reject);
      }, this.serverCloseTimeout);
      (_a = this.server) == null ? void 0 : _a.close((error) => {
        clearTimeout(timeoutId);
        this.cleanup();
        if (error) {
          reject(new Error(`Error during graceful server shutdown: ${error.message}`));
        } else {
          resolve();
        }
      });
    });
  }
  /**
   * Forces immediate cleanup of server resources without waiting for graceful shutdown.
   */
  async forceCleanup() {
    if (this.server) {
      this.server.closeAllConnections();
      try {
        await new Promise((resolve) => {
          var _a;
          if ((_a = this.server) == null ? void 0 : _a.listening) {
            this.server.close(() => resolve());
          } else {
            resolve();
          }
        });
      } catch {}
    }
    this.cleanup();
  }
  /**
   * Gets the callback URL for OAuth redirects.
   * @returns The full callback URL or undefined if server is not started
   */
  getCallbackUrl() {
    return this.callbackUrl;
  }
  /**
   * Waits for an OAuth callback to be received.
   * @returns Promise that resolves with the authorization code and state
   */
  async waitForCallback() {
    if (!this.callbackPromise) {
      this.callbackPromise = new Promise((resolve, reject) => {
        this.callbackResolve = resolve;
        this.callbackReject = reject;
      });
    }
    return this.callbackPromise;
  }
  /**
   * Handles incoming HTTP requests to the OAuth redirect server.
   * Currently provides basic routing for the OAuth callback endpoint.
   */
  handleRequest(request, response) {
    const parsedUrl = new URL(request.url || "", this.callbackUrl);
    if (parsedUrl.pathname === "/oauth/callback") {
      this.handleOAuthCallback(request, response, parsedUrl.searchParams);
    } else {
      response.writeHead(404, {
        "Content-Type": "text/plain"
      });
      response.end("Not Found");
    }
  }
  /**
   * Handles OAuth callback requests.
   * Extracts authorization code and state parameters, validates the request,
   * and resolves the callback promise with the extracted data.
   */
  handleOAuthCallback(_request, response, queryParams) {
    try {
      if (queryParams.has("error")) {
        const error = {
          error: queryParams.get("error") || "",
          description: queryParams.get("error_description") || void 0,
          errorUri: queryParams.get("error_uri") || void 0,
          state: queryParams.get("state") || void 0
        };
        this.sendErrorResponse(response, error);
        if (this.callbackReject) {
          this.callbackReject(
            new Error(
              `OAuth authorization failed: ${error.error} - ${error.description || "No description provided"}`)
          );
          this.resetCallbacks();
        }
        return;
      }
      const code = queryParams.get("code");
      const state = queryParams.get("state");
      if (!code || !state) {
        this.sendValidationErrorResponse(response, "code and state parameters are required");
        if (this.callbackReject) {
          this.callbackReject(new Error("OAuth callback missing authorization code or state"));
          this.resetCallbacks();
        }
        return;
      }
      this.sendSuccessResponse(response);
      if (this.callbackResolve) {
        this.callbackResolve({
          code,
          state
        });
        this.resetCallbacks();
      }
    } catch (error) {
      this.sendInternalErrorResponse(response);
      if (this.callbackReject) {
        this.callbackReject(error instanceof Error ? error : new Error("Unknown error processing OAuth callback"));
        this.resetCallbacks();
      }
    }
  }
  /**
   * Sends a success response to the OAuth callback request.
   */
  sendSuccessResponse(response) {
    response.writeHead(200, {
      "Content-Type": "text/html"
    });
    response.end(`
      <!DOCTYPE html>
      <html>
        <head>
          <title>OAuth Authorization Successful</title>
          <style>
            body { font-family: Arial, sans-serif; text-align: center; padding: 50px; }
            .success { color: #964cd3ff; }
            .container { max-width: 500px; margin: 0 auto; }
          </style>
        </head>
        <body>
          <div class="container">
            <h1 class="success">Authorization Successful</h1>
            <p>You have successfully authorized.</p>
            <p>You can now close this window and return to Kiro.</p>
          </div>
        </body>
      </html>
    `);
  }
  /**
   * Sends an error response for OAuth authorization errors.
   */
  sendErrorResponse(response, error) {
    response.writeHead(400, {
      "Content-Type": "text/html"
    });
    response.end(`
      <!DOCTYPE html>
      <html>
        <head>
          <title>OAuth Authorization Failed</title>
          <style>
            body { font-family: Arial, sans-serif; text-align: center; padding: 50px; }
            .error { color: #dc3545; }
            .container { max-width: 500px; margin: 0 auto; }
            .error-details { background: #f8f9fa; padding: 15px; border-radius: 5px; margin: 20px 0; }
          </style>
        </head>
        <body>
          <div class="container">
            <h1 class="error">Authorization Failed</h1>
            <p>The OAuth authorization was not successful.</p>
            <div class="error-details">
              <strong>Error:</strong> ${this.escapeHtml(error.error)}<br>
              ${error.description ? `<strong>Description:</strong> ${this.escapeHtml(error.description)}<br>` : ""}
            </div>
            <p>Please close this window and try again.</p>
          </div>
        </body>
      </html>
    `);
  }
  /**
   * Sends a validation error response for malformed requests.
   */
  sendValidationErrorResponse(response, message) {
    response.writeHead(400, {
      "Content-Type": "text/html"
    });
    response.end(`
      <!DOCTYPE html>
      <html>
        <head>
          <title>Invalid OAuth Callback</title>
          <style>
            body { font-family: Arial, sans-serif; text-align: center; padding: 50px; }
            .error { color: #dc3545; }
            .container { max-width: 500px; margin: 0 auto; }
          </style>
        </head>
        <body>
          <div class="container">
            <h1 class="error">Invalid Request</h1>
            <p>${this.escapeHtml(message)}</p>
            <p>Please close this window and try again.</p>
          </div>
        </body>
      </html>
    `);
  }
  /**
   * Sends an internal server error response.
   */
  sendInternalErrorResponse(response) {
    response.writeHead(500, {
      "Content-Type": "text/html"
    });
    response.end(`
      <!DOCTYPE html>
      <html>
        <head>
          <title>Server Error</title>
          <style>
            body { font-family: Arial, sans-serif; text-align: center; padding: 50px; }
            .error { color: #dc3545; }
            .container { max-width: 500px; margin: 0 auto; }
          </style>
        </head>
        <body>
          <div class="container">
            <h1 class="error">Server Error</h1>
            <p>An internal server error occurred while processing the OAuth callback.</p>
            <p>Please close this window and try again.</p>
          </div>
        </body>
      </html>
    `);
  }
  /**
   * Escapes HTML characters to prevent XSS attacks.
   */
  escapeHtml(text) {
    const map = {
      "&": "&amp;",
      "<": "&lt;",
      ">": "&gt;",
      '"': "&quot;",
      "'": "&#039;"
    };
    return text.replace(/[&<>"']/g, (m) => map[m]);
  }
  resetCallbacks() {
    this.callbackPromise = null;
    this.callbackResolve = null;
    this.callbackReject = null;
  }
  /**
   * Cleans up server resources and resets internal state.
   */
  cleanup() {
    this.server = void 0;
    this.callbackUrl = void 0;
    if (this.callbackReject) {
      this.callbackReject(new Error("OAuth server stopped before callback was received"));
    }
    this.resetCallbacks();
  }
}
const MAX_TOOL_NAME_LENGTH = 64;

function formatToolName(serverName, toolName, namesUsed) {
  let sanitizedName = `mcp_${serverName}_${toolName}`;
  sanitizedName = sanitizedName.replace(/[\s-]/g, "_");
  sanitizedName = sanitizedName.replace(/[^a-zA-Z0-9_]/g, "");
  if (sanitizedName.length > MAX_TOOL_NAME_LENGTH) {
    sanitizedName = sanitizedName.slice(0, MAX_TOOL_NAME_LENGTH);
  }
  if (namesUsed.has(sanitizedName)) {
    const suffix = `_${Math.floor(100 * Math.random())}`;
    sanitizedName = sanitizedName.slice(0, MAX_TOOL_NAME_LENGTH - suffix.length) + suffix;
  }
  return sanitizedName;
}
class MCPConnection {
  constructor(options, serverName, cwd, secretStorage, useOAuth = false) {
    __publicField(this, "mcpClient");
    __publicField(this, "oauthRedirectServer");
    __publicField(this, "oauthProvider");
    __publicField(this, "isConnected", false);
    __publicField(this, "connectPromise", null);
    this.options = options;
    this.serverName = serverName;
    this.cwd = cwd;
    this.secretStorage = secretStorage;
    this.useOAuth = useOAuth;
    if (options.disabled) {
      throw new Error("Cannot connect to disabled server");
    }
    this.mcpClient = new index_js.Client({
      name: "kiro",
      version: "0.0.0"
    }, {
      capabilities: {}
    });
    if (useOAuth) {
      this.oauthRedirectServer = new OAuthRedirectServer();
    }
    this.oauthProvider = new MCPAuthProvider(secretStorage, options, useOAuth);
  }
  constructSSETransport(options) {
    return new sse_js.SSEClientTransport(new URL(options.url || ""), {
      requestInit: {
        headers: options.headers
      },
      authProvider: this.oauthProvider
    });
  }
  constructStreamableHTTPTransport(options) {
    return new streamableHttp_js.StreamableHTTPClientTransport(new URL(options.url || ""), {
      requestInit: {
        headers: options.headers
      },
      authProvider: this.oauthProvider
    });
  }
  constructStdioTransport(options, cwd) {
    const env = {
      ...stdio_js.getDefaultEnvironment(),
      ...options.env
    };
    const transport = new stdio_js.StdioClientTransport({
      command: options.command || "",
      args: options.args,
      env,
      stderr: "overlapped",
      cwd: options.cwd || cwd
    });
    if (transport.stderr !== null) {
      transport.stderr.on("data", (data) => {
        ignore.mcpLogger.warn(`Log from MCP Server: ${data}`, this.serverName);
      });
    }
    return transport;
  }
  async connectClient(signal, fallbackToStreamableHttp = false) {
    if (this.isConnected) {
      return;
    }
    if (this.connectPromise) {
      await this.connectPromise;
      return;
    }
    let transport;
    let transportType;
    if (this.options.command) {
      transport = this.constructStdioTransport(this.options, this.cwd);
      transportType = "Stdio";
    } else if (fallbackToStreamableHttp) {
      transport = this.constructStreamableHTTPTransport(this.options);
      transportType = "StreamableHTTP";
    } else {
      transport = this.constructSSETransport(this.options);
      transportType = "SSE";
    }
    this.connectPromise = this.mcpClient.connect(transport, {
      signal
    });
    try {
      await this.connectPromise;
      this.isConnected = true;
      ignore.mcpLogger.info(`Connected to server with transport type: ${transportType}`, this.serverName);
    } catch (error) {
      if (error instanceof sse_js.SseError && !fallbackToStreamableHttp) {
        this.connectPromise = null;
        await this.connectClient(signal, true);
      } else if (error instanceof auth_js.UnauthorizedError && this.oauthRedirectServer && (
          transport instanceof streamableHttp_js.StreamableHTTPClientTransport || transport instanceof sse_js
          .SSEClientTransport)) {
        const {
          code,
          state
        } = await this.oauthRedirectServer.waitForCallback();
        if (state !== this.oauthProvider.state()) {
          throw new Error("Invalid OAuth state");
        }
        await transport.finishAuth(code);
        ignore.mcpLogger.info(`Received authorization code, completing OAuth`, this.serverName);
        this.connectPromise = null;
        await this.connectClient(signal, fallbackToStreamableHttp);
      } else {
        throw error;
      }
    } finally {
      this.connectPromise = null;
    }
  }
  /**
   * Closes the connection, clearing resources. Log but not throw on error.
   */
  async close() {
    try {
      await this.mcpClient.close();
      ignore.mcpLogger.info("MCP connection closed successfully", this.serverName);
    } catch (error) {
      ignore.mcpLogger.warn(
        `Error closing MCP connection: ${error instanceof Error ? error.message : String(error)}`,
        this.serverName
      );
    }
  }
  /**
   * Connects to MCP server and initializes available tools and resources.
   */
  async syncResourcesAndTools(serverName, signal) {
    if (this.oauthRedirectServer) {
      await this.oauthProvider.invalidateCredentials("all");
      const callbackUrl = await this.oauthRedirectServer.start();
      this.oauthProvider.redirectUrl = callbackUrl;
    }
    await this.connectClient(signal);
    const namesUsed = /* @__PURE__ */ new Set();
    const contextReferences = [];
    let mcpTools = void 0;
    try {
      const capabilities = this.mcpClient.getServerCapabilities();
      if (capabilities == null ? void 0 : capabilities.tools) {
        try {
          const {
            tools
          } = await this.mcpClient.listTools({}, {
            signal
          });
          mcpTools = tools.map((tool) => {
            const sanitizedUniqueName = formatToolName(serverName, tool.name, namesUsed);
            namesUsed.add(sanitizedUniqueName);
            const source = mcpServerSources.get(serverName);
            return {
              sanitizedUniqueName,
              serverName,
              toolName: tool.name,
              description: tool.description,
              inputSchema: tool.inputSchema,
              // caller updates tags with configured autoApproved and disabled tools
              requireConsent: true,
              disabled: false,
              source
              // Use actual source from config loading
            };
          });
          const serverContextReferences = tools.map((tool) => ({
            serverName,
            type: "tool",
            name: tool.name,
            description: tool.description || "",
            uri: tool.name
          }));
          contextReferences.push(...serverContextReferences);
        } catch (e) {
          if (e instanceof types_js.McpError && e.code === types_js.ErrorCode.MethodNotFound.valueOf()) {
            ignore.mcpLogger.warn("MCP server does not support listing tools. Skipping...", serverName);
          } else {
            throw e;
          }
        }
      }
      if (capabilities == null ? void 0 : capabilities.resources) {
        try {
          const {
            resources
          } = await this.mcpClient.listResources({}, {
            signal
          });
          const serverContextReferences = resources.map((resource) => ({
            serverName,
            type: "resource",
            name: resource.name || "",
            description: resource.description || "",
            uri: resource.uri || ""
          }));
          contextReferences.push(...serverContextReferences);
        } catch (e) {
          if (e instanceof types_js.McpError && e.code === types_js.ErrorCode.MethodNotFound.valueOf()) {
            ignore.mcpLogger.warn("MCP server does not support listing resources. Skipping...", serverName);
          } else {
            throw e;
          }
        }
      }
      return {
        tools: mcpTools,
        contextReferences
      };
    } catch (error) {
      const errorMsg = error instanceof Error ? error.message : String(error);
      ignore.mcpLogger.error(`Error getting tools and resources from MCP server: ${errorMsg}`, serverName);
      throw error;
    } finally {
      if (this.oauthRedirectServer) {
        await this.oauthRedirectServer.stop();
      }
    }
  }
}
const MCP_CONNECTION_TIMEOUT = 3e5;
const MCP_TOOL_COUNT_WARN_THESHOLD = 50;
const _MCPManagerSingleton = class _MCPManagerSingleton {
  constructor() {
    __publicField(this, "metricReporter");
    __publicField(this, "secretStorage");
    // Track connection states with different statuses
    __publicField(this, "connectionStates");
    __publicField(this, "hasShownToolCountWarning");
    this.connectionStates = /* @__PURE__ */ new Map();
    this.metricReporter = new telemetry_definitions_index.MetricReporter(telemetry_definitions_index
      .TelemetryNamespace.Application, "mcp");
    this.metricReporter.periodicallyCaptureMetrics(() => this.metrics());
    this.hasShownToolCountWarning = false;
  }
  /**
   * Get MCPManagerSingleton instance.
   */
  static getInstance() {
    if (!_MCPManagerSingleton.instance) {
      _MCPManagerSingleton.instance = new _MCPManagerSingleton();
    }
    return _MCPManagerSingleton.instance;
  }
  /**
   * Set the secret storage for OAuth credential management.
   */
  setSecretStorage(secretStorage) {
    this.secretStorage = secretStorage;
  }
  /**
   * Sets configured tools for an MCP server connection.
   */
  static setConfiguredTools(serverName, tools) {
    if (!tools) {
      this.configuredMCPTools.delete(serverName);
      return;
    }
    this.configuredMCPTools.set(serverName, tools);
  }
  /**
   * Gets configured tools for all MCP server connections.
   * Returns immediately with the currently available tools.
   */
  static getConfiguredTools() {
    return Array.from(this.configuredMCPTools.values()).flatMap((val) => val);
  }
  /**
   * Sets context references for an MCP server connection.
   */
  static setContextReferences(serverName, references) {
    if (!references) {
      this.mcpContextReferences.delete(serverName);
      return;
    }
    this.mcpContextReferences.set(serverName, references);
  }
  /**
   * Gets context references for all MCP server connections.
   * Returns immediately with the currently available context references.
   */
  static getContextReferences() {
    return Array.from(this.mcpContextReferences.values()).flatMap((val) => val);
  }
  /**
   * Returns the connection states for MCP connections.
   */
  getConnectionStates() {
    return Array.from(this.connectionStates.values());
  }
  setConnectionState(serverName, connectionState) {
    if (!connectionState) {
      this.connectionStates.delete(serverName);
    } else {
      this.connectionStates.set(serverName, connectionState);
    }
    vscode__namespace.commands.executeCommand("kiroAgent.views.mcpServerStatus.refresh");
  }
  /**
   * Register an MCP server and immediately start connecting to it in the background.
   * Avoids duplicate connection attempts for the same server
   */
  registerServer(serverName, options, configuredIndex, useOAuth, onConnectionChange, cwd) {
    const existingState = this.connectionStates.get(serverName);
    if (existingState) {
      if (existingState.status === "connecting" || existingState.status === "connected") {
        ignore.mcpLogger.info(`MCP server is already ${existingState.status}`, serverName);
        return;
      }
    }
    ignore.mcpLogger.info("Registering MCP server and starting connection", serverName);
    const connectionPromise = this.connectToServer(
      serverName,
      options,
      configuredIndex,
      useOAuth,
      onConnectionChange,
      cwd
    );
    this.setConnectionState(serverName, {
      status: "connecting",
      serverName,
      connectionPromise,
      options,
      configuredIndex,
      onConnectionChange
    });
  }
  /**
   * Show VSCode error message for MCP connection failure with option to view logs
   */
  async showConnectionErrorMessage(serverName, errorMessage) {
    const message = `Failed to connect to MCP server "${serverName}": ${errorMessage}`;
    const action = await vscode__namespace.window.showErrorMessage(message, "Show Logs");
    if (action === "Show Logs") {
      ignore.mcpLogger.show();
    }
  }
  async connectToServer(serverName, options, configuredIndex, useOAuth, onConnectionChange, cwd) {
    return this.metricReporter.callWithTrace("connectToServer", async () => {
      await this.startConnection(serverName, options, configuredIndex, useOAuth, onConnectionChange, cwd);
    });
  }
  // Updates provided tool configs to include flags for requireConsent and disabled based on provided lists.
  updateToolTags(autoApprove, disabledTools, tools) {
    if (!tools) return void 0;
    return tools.map((tool) => ({
      ...tool,
      requireConsent: !autoApprove || !autoApprove.includes(tool.toolName),
      disabled: !!disabledTools && disabledTools.includes(tool.toolName)
    }));
  }
  /**
   * Start a connection to an MCP server.
   */
  async startConnection(serverName, options, configuredIndex, useOAuth, onConnectionChange, cwd) {
    var _a;
    let connection;
    const abortController = new AbortController();
    const timeoutId = setTimeout(() => {
      const timeoutMessage = "MCP server connection and syncing tools and resources timed out after 5 minutes";
      ignore.mcpLogger.error(timeoutMessage, serverName);
      abortController.abort(timeoutMessage);
    }, MCP_CONNECTION_TIMEOUT);
    try {
      connection = new MCPConnection(options, serverName, cwd, this.secretStorage, useOAuth);
      const resourcesAndTools = await connection.syncResourcesAndTools(serverName, abortController.signal);
      const currentState = this.connectionStates.get(serverName);
      if (!currentState || currentState.status === "disabled") {
        ignore.mcpLogger.warn("Connection disabled or removed during connection, removing...", serverName);
        await connection.close();
        return;
      }
      const taggedTools = this.updateToolTags(options.autoApprove, options.disabledTools, resourcesAndTools.tools);
      ignore.mcpLogger.info("Successfully connected and synced tools and resources for MCP server", serverName);
      this.setConnectionState(serverName, {
        status: "connected",
        connection,
        serverName,
        options,
        configuredIndex,
        availableTools: taggedTools,
        availableContextReferences: resourcesAndTools.contextReferences,
        onConnectionChange
      });
      _MCPManagerSingleton.setConfiguredTools(
        serverName,
        taggedTools == null ? void 0 : taggedTools.filter((it) => !it.disabled)
      );
      _MCPManagerSingleton.setContextReferences(
        serverName,
        (_a = resourcesAndTools.contextReferences) == null ? void 0 : _a.filter(
          (it) => it.type !== "tool" || !(options.disabledTools || []).includes(it.name)
        )
      );
      const allTools = _MCPManagerSingleton.getConfiguredTools();
      const numTools = allTools.filter((tool) => tool.source !== "power").length;
      if (!this.hasShownToolCountWarning && numTools > MCP_TOOL_COUNT_WARN_THESHOLD) {
        const warnMessage = `
          You have ${numTools} MCP tools enabled.
          We recommend disabling servers or tools to keep this below ${MCP_TOOL_COUNT_WARN_THESHOLD}, as too many tools lead to
          degraded agent tool selection and high token usage consuming significant context.
        `;
        vscode__namespace.window.showWarningMessage(warnMessage);
        this.hasShownToolCountWarning = true;
      }
      if (onConnectionChange) {
        onConnectionChange(serverName);
      }
    } catch (error) {
      if (connection) {
        await connection.close();
      }
      const currentState = this.connectionStates.get(serverName);
      if (!currentState || currentState.status === "disabled") {
        return;
      }
      const errorMsg = error instanceof Error ? error.message : String(error);
      const errorCode = error instanceof Error && "code" in error ? error.code : void 0;
      const failedStatus = errorMsg === "Unauthorized" || errorCode === 401 ? "unauthorized" : "failed";
      this.setConnectionState(serverName, {
        status: failedStatus,
        serverName,
        options,
        configuredIndex,
        onConnectionChange
      });
      ignore.mcpLogger.error(`Error connecting to MCP server: ${errorMsg}`, serverName);
      if (failedStatus === "unauthorized") {
        const message =
          `Authentication for MCP Server "${serverName}" required. Servers that support OAuth can be authenticated through Kiro.`;
        const action = await vscode__namespace.window.showInformationMessage(message, "Authenticate");
        if (action === "Authenticate") {
          await this.resetConnection(serverName, true);
        }
      } else {
        await this.showConnectionErrorMessage(serverName, errorMsg);
      }
      throw error;
    } finally {
      clearTimeout(timeoutId);
    }
  }
  /**
   * Get connection to MCP server.
   * Only returns already established connections.
   */
  getConnection(serverName) {
    const state = this.connectionStates.get(serverName);
    return (state == null ? void 0 : state.status) === "connected" ? state.connection : void 0;
  }
  /**
   * Remove connection to MCP server.
   * If options provided as disabled, keep the connection state as disabled, else remove entirely.
   */
  async removeConnection(serverName, options, configuredIndex, onConnectionChange) {
    const state = this.connectionStates.get(serverName);
    _MCPManagerSingleton.configuredMCPTools.delete(serverName);
    _MCPManagerSingleton.mcpContextReferences.delete(serverName);
    if (options == null ? void 0 : options.disabled) {
      this.setConnectionState(serverName, {
        status: "disabled",
        serverName,
        options,
        configuredIndex: configuredIndex || 0
      });
    } else {
      this.setConnectionState(serverName, void 0);
    }
    if (state == null ? void 0 : state.connection) {
      await state.connection.close();
    }
    if (onConnectionChange) {
      try {
        onConnectionChange(serverName);
      } catch (error) {
        ignore.mcpLogger.warn(
          `Error in onConnectionChange callback: ${error instanceof Error ? error.message : String(error)}`,
          serverName
        );
      }
    }
  }
  /**
   * Reload MCP configuration by comparing current connections with provided config.
   * - Keeps existing connections for servers still in the config
   * - Closes connections for servers no longer in the config
   * - Creates new connections for servers newly added to the config
   * @param mcpConfig The current MCP configuration with server definitions
   * @param onConnectionChange Optional callback function that's executed after a connection is changed
   */
  async reloadMcpConfig(mcpConfig, onConnectionChange, cwd) {
    var _a;
    if (!mcpConfig) {
      ignore.mcpLogger.info("No MCP servers configured, closing all existing connections");
      const serverNames = Array.from(this.connectionStates.keys());
      for (const serverName of serverNames) {
        await this.removeConnection(serverName, void 0, void 0, onConnectionChange);
      }
      return;
    }
    const currentServerNames = new Set(this.connectionStates.keys());
    const configuredServerNames = new Set(Object.keys(mcpConfig.mcpServers));
    const serversWithConfigRemoved = Array.from(currentServerNames).filter(
      (serverName) => !configuredServerNames.has(serverName)
    );
    const serversWithConfigAdded = Array.from(configuredServerNames).map((serverName, index) => {
      return {
        serverName,
        index
      };
    }).filter(({
      serverName
    }) => !currentServerNames.has(serverName));
    const serversWithConfigModified = Array.from(configuredServerNames).map((serverName, index) => {
      return {
        serverName,
        index
      };
    }).filter(({
      serverName
    }) => currentServerNames.has(serverName));
    for (const serverName of serversWithConfigRemoved) {
      ignore.mcpLogger.info("Removing MCP server as it is no longer in the configuration", serverName);
      await this.removeConnection(serverName, void 0, void 0, onConnectionChange);
    }
    for (const {
        serverName,
        index
      }
      of serversWithConfigAdded) {
      const serverConfig = mcpConfig.mcpServers[serverName];
      if (!serverConfig.disabled) {
        ignore.mcpLogger.info("Adding new MCP server from updated configuration", serverName);
        this.registerServer(serverName, serverConfig, index, false, onConnectionChange, cwd);
      } else {
        ignore.mcpLogger.info("New MCP server from updated configuration is disabled", serverName);
        await this.removeConnection(serverName, serverConfig, index, onConnectionChange);
      }
    }
    for (const {
        serverName,
        index
      }
      of serversWithConfigModified) {
      const existingState = this.connectionStates.get(serverName);
      const newConfig = mcpConfig.mcpServers[serverName];
      const connectionConfigChanged = JSON.stringify({
        ...existingState == null ? void 0 : existingState.options,
        autoApprove: [],
        disabledTools: []
      }) !== JSON.stringify({
        ...newConfig,
        autoApprove: [],
        disabledTools: []
      });
      if (connectionConfigChanged) {
        if (!newConfig.disabled) {
          ignore.mcpLogger.info("Configuration changed for MCP server, reconnecting", serverName);
          await this.removeConnection(serverName, newConfig, index, onConnectionChange);
          this.registerServer(serverName, newConfig, index, false, onConnectionChange, cwd);
        } else {
          ignore.mcpLogger.info("Configuration disabled for MCP server, disconnecting", serverName);
          await this.removeConnection(serverName, newConfig, index, onConnectionChange);
        }
      } else if (existingState) {
        existingState.configuredIndex = index;
        const taggedTools = this.updateToolTags(
          newConfig.autoApprove,
          newConfig.disabledTools,
          existingState.availableTools
        );
        existingState.availableTools = taggedTools;
        this.setConnectionState(serverName, existingState);
        _MCPManagerSingleton.setConfiguredTools(
          serverName,
          taggedTools == null ? void 0 : taggedTools.filter((it) => !it.disabled)
        );
        _MCPManagerSingleton.setContextReferences(
          serverName,
          (_a = existingState.availableContextReferences) == null ? void 0 : _a.filter(
            (it) => it.type !== "tool" || !(newConfig.disabledTools || []).includes(it.name)
          )
        );
        if (onConnectionChange) {
          onConnectionChange(serverName);
        }
      }
    }
  }
  /**
   * Resets the connection for the server name based on existing connection status.
   */
  async resetConnection(serverName, useOAuth = false) {
    const currentConnection = this.connectionStates.get(serverName);
    if (!currentConnection) {
      ignore.mcpLogger.warn("No connection found", serverName);
      return;
    }
    ignore.mcpLogger.info("Reconnecting to server", serverName);
    await this.removeConnection(
      serverName,
      currentConnection.options,
      currentConnection.configuredIndex,
      currentConnection.onConnectionChange
    );
    this.registerServer(
      serverName,
      currentConnection.options,
      currentConnection.configuredIndex,
      useOAuth,
      currentConnection.onConnectionChange
    );
  }
  /**
   * Resets the singleton, removing connections and clearing static state.
   */
  static async reset() {
    const instance = _MCPManagerSingleton.instance;
    if (!instance) {
      return;
    }
    const connections = instance.getConnectionStates();
    try {
      await Promise.all(connections.map((it) => instance.removeConnection(it.serverName)));
    } catch (e) {
      ignore.mcpLogger.error(
        `Error removing connection for MCP server: ${e instanceof Error ? e.message : String(e)}`);
    }
    _MCPManagerSingleton.instance = void 0;
  }
  metrics() {
    const connections = this.getConnectionStates();
    const disabledConnections = connections.filter((connection) => connection.status === "disabled");
    const failedConnections = connections.filter((connection) => connection.status === "failed");
    const unauthorizedConnections = connections.filter((connection) => connection.status === "unauthorized");
    const tools = connections.flatMap((connection) => connection.availableTools || []);
    const autoApprovedTools = tools.filter((tool) => !tool.requireConsent);
    const disabledTools = tools.filter((tool) => tool.disabled);
    return {
      enabledMCPServers: connections.length - disabledConnections.length,
      disabledMCPServers: disabledConnections.length,
      failedMCPServers: failedConnections.length,
      unauthorizedMCPServers: unauthorizedConnections.length,
      availableMCPTools: tools.length,
      autoApprovedMCPTools: autoApprovedTools.length,
      disabledMCPTools: disabledTools.length
    };
  }
};
__publicField(_MCPManagerSingleton, "instance");
__publicField(_MCPManagerSingleton, "configuredMCPTools", /* @__PURE__ */ new Map());
__publicField(_MCPManagerSingleton, "mcpContextReferences", /* @__PURE__ */ new Map());
let MCPManagerSingleton = _MCPManagerSingleton;
exports.MCPConnection = MCPConnection;
exports.MCPJsonConfigSchema = MCPJsonConfigSchema;
exports.MCPManagerSingleton = MCPManagerSingleton;
exports.MCPOptionsSchema = MCPOptionsSchema;
exports.addMCPServerConfig = addMCPServerConfig;
exports.addMCPToolToAutoApproveConfig = addMCPToolToAutoApproveConfig;
exports.disableMCPTools = disableMCPTools;
exports.enableMCPTools = enableMCPTools;
exports.findConfigFileForServer = findConfigFileForServer;
exports.formatToolName = formatToolName;
exports.loadMcpConfig = loadMcpConfig;
exports.mcpServerSources = mcpServerSources;
exports.resetApprovedEnvVars = resetApprovedEnvVars;
exports.setMCPServerDisabled = setMCPServerDisabled;