"use strict";
var __defProp = Object.defineProperty;
var __defNormalProp = (obj, key, value) => key in obj ? __defProp(obj, key, { enumerable: true, configurable: true, writable: true, value }) : obj[key] = value;
var __publicField = (obj, key, value) => __defNormalProp(obj, typeof key !== "symbol" ? key + "" : key, value);
Object.defineProperty(exports, Symbol.toStringTag, { value: "Module" });
const ssoOidcClient = require("./sso-oidc-client-buZgGo34.cjs");
const vscode = require("vscode");
const ignore = require("./ignore-D645GLpP.cjs");
const path = require("path");
const os = require("os");
const fs = require("fs");
require("node-machine-id");
require("axios");
require("axios-retry");
const telemetry_definitions_index = require("./telemetry/definitions/index.cjs");
const socialAuthProvider = require("./social-auth-provider-p2CkM1hk.cjs");
const span = require("./span-CaZ6i9Jj.cjs");
require("@opentelemetry/api");
const webFetchMeter = require("./web-fetch-meter-DNWId8KO.cjs");
const child_process = require("child_process");
const util = require("util");
const mcpManager = require("./mcp-manager-DFdiTga3.cjs");
const journeyTracker = require("./journey-tracker-DGZqYFGz.cjs");
const uri = require("./uri-Czh1P-NU.cjs");
const paths = require("./paths-C6z4_Obm.cjs");
const webFetchClient = require("./web-fetch-client-BiSbGDtR.cjs");
const machineId = require("./machine-id-hff6ippA.cjs");
function _interopNamespaceDefault(e) {
  const n = Object.create(null, { [Symbol.toStringTag]: { value: "Module" } });
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
const os__namespace = /* @__PURE__ */ _interopNamespaceDefault(os);
const fs__namespace = /* @__PURE__ */ _interopNamespaceDefault(fs);
const KIRO_AUTH_TOKEN_FILE_NAME = "kiro-auth-token.json";
const SOCIAL_PROVIDERS = ["Google", "Github"];
const IDC_PROVIDERS = ["Enterprise", "BuilderId", "Internal"];
class TokenStorage {
  constructor() {
    __publicField(this, "tokenCache");
    __publicField(this, "cacheDirectory", path__namespace.join(os__namespace.homedir(), ".aws", "sso", "cache"));
    __publicField(this, "_onDidChange", new vscode__namespace.EventEmitter());
    __publicField(this, "watchListener");
    this.watchListener = () => {
      this.clearCache();
      this._onDidChange.fire();
    };
    fs__namespace.watchFile(this.getAuthTokenPath(), this.watchListener);
  }
  /**
   * Cleans up internal state
   */
  dispose() {
    fs__namespace.unwatchFile(this.getAuthTokenPath(), this.watchListener);
  }
  /**
   * Event that triggers where there is a change in login status
   */
  get onDidChange() {
    return this._onDidChange.event;
  }
  readTokenFromLocalCache() {
    return this.tokenCache;
  }
  getAuthTokenPath() {
    return path__namespace.join(this.cacheDirectory, KIRO_AUTH_TOKEN_FILE_NAME);
  }
  ensureCacheDirectory() {
    try {
      if (!fs__namespace.existsSync(this.cacheDirectory)) {
        fs__namespace.mkdirSync(this.cacheDirectory, { recursive: true });
      }
    } catch (_e) {
      throw new ssoOidcClient.FileSystemAccessError(this.cacheDirectory);
    }
  }
  writeTokenToLocalCache(token) {
    this.tokenCache = token;
  }
  writeTokenToDisk(token) {
    this.ensureCacheDirectory();
    const tokenPath = this.getAuthTokenPath();
    try {
      fs__namespace.writeFileSync(tokenPath, JSON.stringify(token, void 0, 2));
    } catch (_e) {
      throw new ssoOidcClient.FileSystemAccessError(tokenPath);
    }
  }
  clearCache() {
    this.tokenCache = void 0;
  }
  readTokenFromDisk() {
    const tokenPath = this.getAuthTokenPath();
    if (fs__namespace.existsSync(tokenPath)) {
      try {
        const cacheContents = fs__namespace.readFileSync(tokenPath, "utf8");
        try {
          return JSON.parse(cacheContents);
        } catch (e) {
          ignore.logger.error("Error trying to parse the token file.", e);
          return void 0;
        }
      } catch (_e) {
        throw new ssoOidcClient.FileSystemAccessError(tokenPath);
      }
    }
  }
  /**
   * The method removed internal token inconsistencies enabled through redundant data stored in the token (authMethod vs. provider)
   * We treat the provider as the source of truth and, if provided, we determine authMethod based on that.
   */
  sanitizeToken(token) {
    if (SOCIAL_PROVIDERS.includes(token.provider)) {
      return { ...token, authMethod: "social" };
    } else if (IDC_PROVIDERS.includes(token.provider)) {
      return { ...token, authMethod: "IdC" };
    }
    return token;
  }
  /**
   * Retrieves the currently cached auth token
   */
  readToken() {
    const localToken = this.readTokenFromLocalCache();
    if (localToken) {
      return this.sanitizeToken(localToken);
    }
    const tokenFromDisk = this.readTokenFromDisk();
    if (tokenFromDisk) {
      this.writeTokenToLocalCache(tokenFromDisk);
      return this.sanitizeToken(tokenFromDisk);
    }
  }
  /**
   * Writes an auth token to cache
   */
  writeToken(token) {
    this.writeTokenToDisk(token);
    this.clearCache();
    this._onDidChange.fire();
  }
  /**
   * Deletes cached auth token
   */
  clearToken() {
    this.clearCache();
    const tokenPath = this.getAuthTokenPath();
    try {
      if (fs__namespace.existsSync(tokenPath)) {
        fs__namespace.unlinkSync(tokenPath);
      }
    } catch (_e) {
      throw new ssoOidcClient.FileSystemAccessError(tokenPath);
    }
    this._onDidChange.fire();
  }
}
const _ProfileStorage = class _ProfileStorage {
  constructor(context) {
    __publicField(this, "profileUri");
    __publicField(this, "PROFILE_FILE_NAME", "profile.json");
    this.profileUri = vscode__namespace.Uri.joinPath(context.globalStorageUri, this.PROFILE_FILE_NAME);
  }
  /**
   * Initialize the ProfileStorage singleton instance.
   * This should be called once during extension activation.
   * Safe to call multiple times - will only initialize once.
   * @param context - The VSCode extension context
   */
  static initializeInstance(context) {
    if (!_ProfileStorage.instance) {
      _ProfileStorage.instance = new _ProfileStorage(context);
    }
  }
  /**
   * Get the ProfileStorage singleton instance.
   * @returns The singleton instance
   * @throws Error if not initialized
   */
  static getInstance() {
    if (!_ProfileStorage.instance) {
      throw new Error("ProfileStorage must be initialized before use. Call initializeInstance() first.");
    }
    return _ProfileStorage.instance;
  }
  /**
   * Writes a profile to persistent storage.
   * @param profile - The profile to persist
   * @throws Will not throw - errors are logged and handled gracefully
   */
  async writeProfile(profile) {
    await this.ensureDirectoryExists(vscode__namespace.Uri.joinPath(this.profileUri, ".."));
    try {
      const jsonContent = JSON.stringify(profile, null, 2);
      const content = new TextEncoder().encode(jsonContent);
      await vscode__namespace.workspace.fs.writeFile(this.profileUri, content);
    } catch (error) {
      ignore.logger.error("[ProfileStorage] Failed to write profile", { error });
    }
  }
  /**
   * Reads the current profile from persistent storage.
   * @returns The current profile, or undefined if no valid profile exists
   */
  async readProfile() {
    try {
      const fileContent = await vscode__namespace.workspace.fs.readFile(this.profileUri);
      const fileText = new TextDecoder().decode(fileContent);
      const parsedData = JSON.parse(fileText);
      if (this.validateProfile(parsedData)) {
        return parsedData;
      } else {
        ignore.logger.error("[ProfileStorage] Invalid profile data structure in storage file");
        return void 0;
      }
    } catch (error) {
      if (error instanceof vscode__namespace.FileSystemError && error.code === "FileNotFound") {
        return void 0;
      }
      ignore.logger.error("[ProfileStorage] Error reading profile", { error });
      return void 0;
    }
  }
  /**
   * Deletes the current profile from persistent storage.
   * @throws Will not throw - errors are logged and handled gracefully
   */
  async deleteProfile() {
    try {
      await vscode__namespace.workspace.fs.delete(this.profileUri);
    } catch (error) {
      if (error instanceof vscode__namespace.FileSystemError && error.code === "FileNotFound") {
        return;
      }
      ignore.logger.error("[ProfileStorage] Error deleting profile", { error });
    }
  }
  /**
   * Gets the URI for the profile storage file.
   *
   * Uses the extension's global storage URI to ensure the profile persists
   * across workspaces and is accessible by all IDE windows.
   *
   * This method allows external components to set up their own file watchers
   * or perform other operations that need the profile file location.
   * @returns The URI to the profile storage file
   */
  getProfileFileUri() {
    return this.profileUri;
  }
  /**
   * Ensures that the storage directory exists, creating it if necessary.
   * @param dirUri - The directory URI to ensure exists
   */
  async ensureDirectoryExists(dirUri) {
    try {
      await vscode__namespace.workspace.fs.createDirectory(dirUri);
    } catch (error) {
      if (error instanceof vscode__namespace.FileSystemError && error.code === "FileExists") {
        return;
      }
      ignore.logger.error("[ProfileStorage] Failed to create directory", { dirUri: dirUri.toString(), error });
    }
  }
  /**
   * Validates that an object conforms to the Profile interface.
   * @param data - The data to validate
   * @returns True if the data is a valid Profile, false otherwise
   */
  validateProfile(data) {
    return !!data && typeof data === "object" && "arn" in data && "name" in data && typeof data.arn === "string" && typeof data.name === "string" && data.arn.length > 0 && data.name.length > 0;
  }
};
__publicField(_ProfileStorage, "instance");
let ProfileStorage = _ProfileStorage;
function registerProfileStorage(context) {
  ProfileStorage.initializeInstance(context);
}
const AUTH_TOKEN_INVALIDATION_OFFSET_SECONDS = 3 * 60;
const REFRESH_BEFORE_EXPIRY_SECONDS = 10 * 60;
const REFRESH_LOOP_INTERVAL_SECONDS = 60;
const Metrics = new telemetry_definitions_index.MetricReporter(telemetry_definitions_index.TelemetryNamespace.Auth, "auth-provider");
const ERROR_MAPPER = (error) => {
  if (error instanceof ssoOidcClient.SignInBlockedError) {
    return {
      blocked: 1
    };
  } else if (error instanceof ssoOidcClient.CanceledError) {
    return {
      abort: 1
    };
  } else if (error instanceof ssoOidcClient.AbandonedError) {
    return {
      abandon: 1
    };
  } else if (error instanceof ssoOidcClient.InvalidUserInputError) {
    return {
      badInput: 1
    };
  } else if (error instanceof ssoOidcClient.UserEnvironmentError) {
    return {
      environmentIssue: 1
    };
  } else if (ssoOidcClient.isBadAuthIssue(error)) {
    return {
      unauthorized: 1
    };
  } else {
    return {
      failure: 1
    };
  }
};
function translateError(error) {
  return error instanceof ssoOidcClient.AuthError ? error : new ssoOidcClient.UnexpectedIssueError("Auth provider: unexpected issue");
}
function getProviderForMetrics(provider) {
  return (provider == null ? void 0 : provider.toString()) || "unknown";
}
function getTraceConfig(name, provider) {
  return {
    traceName: `${getProviderForMetrics(provider)}.${name}`,
    errorMapper: ERROR_MAPPER,
    metricAliases: [name]
  };
}
class AuthProvider {
  constructor() {
    __publicField(this, "storage");
    __publicField(this, "signInDeferred");
    __publicField(this, "signInPromise");
    __publicField(this, "providers");
    __publicField(this, "authErrorMessagePromises", {
      AccessDenied: null,
      NetworkIssue: null,
      Unknown: null
    });
    __publicField(this, "refreshSettled", Promise.resolve());
    __publicField(this, "refreshLoopTimeout");
    __publicField(this, "_onDidChangeLoginStatus", new vscode__namespace.EventEmitter());
    __publicField(this, "_onDidPerformUserInitiatedLogout", new vscode__namespace.EventEmitter());
    __publicField(this, "disposables", []);
    this.storage = new TokenStorage();
    this.providers = {
      IdC: new socialAuthProvider.IDCAuthProvider(),
      social: new socialAuthProvider.SocialAuthProvider()
    };
    if (vscode__namespace.window.state.focused) {
      this.startRefreshLoop();
    }
    this.disposables.push(
      this.storage,
      {
        dispose: () => {
          this.stopRefreshLoop();
        }
      },
      this.storage.onDidChange(() => {
        this.handleTokenChanges();
      }),
      vscode__namespace.window.onDidChangeWindowState((event) => {
        if (event.focused) {
          this.startRefreshLoop();
        } else {
          this.stopRefreshLoop();
        }
      })
    );
  }
  /**
   * Event that triggers where there is a change in login status
   */
  get onDidChangeLoginStatus() {
    return this._onDidChangeLoginStatus.event;
  }
  /**
   * Event that triggers when user initiates a logout
   * We treat this separately from other changes to the login status because a user initiated logout
   * will result in the sign-in page to be rendered again.
   */
  get onDidPerformUserInitiatedLogout() {
    return this._onDidPerformUserInitiatedLogout.event;
  }
  /**
   * Cleans up internal state
   */
  dispose() {
    this.disposables.forEach((disposable) => {
      disposable.dispose();
    });
  }
  stopRefreshLoop() {
    if (this.refreshLoopTimeout) {
      clearInterval(this.refreshLoopTimeout);
    }
  }
  startRefreshLoop() {
    this.stopRefreshLoop();
    this.refreshSettled = this.attemptRefreshIfCloseToExpiry();
    this.refreshLoopTimeout = setInterval(() => {
      this.refreshSettled = this.attemptRefreshIfCloseToExpiry();
    }, REFRESH_LOOP_INTERVAL_SECONDS * 1e3);
  }
  /**
   * Handles changes of the token inside the storage
   * This ensures that changes made to the file system reflect correctly on the UI
   * More importantly, it ensures that an action performed in one IDE window reflect
   * correctly in all other open IDE windows.
   */
  handleTokenChanges() {
    if (this.isLoggedIn()) {
      const token = this.storage.readToken();
      if (this.signInDeferred) {
        this.signInDeferred.resolve(token);
      }
      this._onDidChangeLoginStatus.fire({
        isSignedIn: true,
        token
      });
    } else {
      this._onDidChangeLoginStatus.fire({
        isSignedIn: false,
        token: void 0
      });
    }
  }
  async attemptRefreshIfCloseToExpiry() {
    try {
      const token = this.storage.readToken();
      if (!token) {
        return;
      }
      if (!token.expiresAt || !token.accessToken) {
        return;
      }
      if (this.isAuthTokenExpiredWithinSeconds(token, REFRESH_BEFORE_EXPIRY_SECONDS)) {
        await span.withSpan(telemetry_definitions_index.TelemetryNamespace.Auth, "auth-provider.scheduled-refresh", () => {
          return this.refreshToken();
        });
      }
    } catch (error) {
      const token = this.storage.readToken();
      if (ssoOidcClient.isBadAuthIssue(error) && token && this.isAuthTokenExpiredWithinSeconds(token, AUTH_TOKEN_INVALIDATION_OFFSET_SECONDS)) {
        void this.logoutAndForget();
      }
    }
  }
  isAuthTokenExpiredWithinSeconds(token, seconds) {
    if (!token.expiresAt || !token.accessToken) {
      return true;
    }
    const expiresAt = new Date(token.expiresAt);
    const now = /* @__PURE__ */ new Date();
    return expiresAt.valueOf() < now.valueOf() + seconds * 1e3;
  }
  isAuthTokenExpired(token) {
    return this.isAuthTokenExpiredWithinSeconds(token, AUTH_TOKEN_INVALIDATION_OFFSET_SECONDS);
  }
  /**
   * Returns the current auth token if authenticated
   * @returns Promise that resolves to the token (string)
   */
  async getToken() {
    return (await this.getTokenData()).accessToken;
  }
  /**
   * Returns the current auth token if authenticated
   * @returns The token read from cache / disk
   */
  readToken() {
    return this.storage.readToken();
  }
  /**
   * Returns the current profileArn if authenticated
   * @returns Promise that resolves to the profileArn (string)
   */
  async getProfileArn() {
    const token = await this.getTokenData();
    if ("profileArn" in token) {
      return token.profileArn;
    }
    const profile = await ProfileStorage.getInstance().readProfile();
    return profile == null ? void 0 : profile.arn;
  }
  /**
   * Returns the current auth token by trying various methods to read or re-generate it
   * (including attempting to refresh the token if expired)
   * @returns Promise that resolves to the token (LocalTokenCacheData)
   */
  async getTokenData({ attemptRefresh } = { attemptRefresh: true }) {
    await this.refreshSettled;
    try {
      const token = this.storage.readToken();
      if (!token) {
        throw new ssoOidcClient.MissingTokenError("No valid token found");
      }
      if (!this.isAuthTokenExpired(token)) {
        return token;
      }
      if (token.refreshToken && attemptRefresh) {
        return await span.withSpan(telemetry_definitions_index.TelemetryNamespace.Auth, "auth-provider.getTokenData", async () => {
          await this.refreshToken();
          return await this.getTokenData({ attemptRefresh: false });
        });
      }
      throw new ssoOidcClient.MalformedTokenError("No valid token found");
    } catch (error) {
      if (ssoOidcClient.isBadAuthIssue(error)) {
        void this.logoutAndForget();
      }
      ignore.logger.error("Failed to retrieve auth token:", error);
      throw translateError(error);
    }
  }
  /**
   * Whether the user is currently considered to be logged in
   */
  isLoggedIn() {
    const token = this.storage.readToken();
    return !!(token == null ? void 0 : token.refreshToken);
  }
  /**
   * Logs the user out of the session
   * @returns Promise that resolves when logout is complete
   */
  async logout() {
    if (!this.isLoggedIn()) {
      return;
    }
    const token = this.storage.readToken();
    if (!token) {
      return;
    }
    return Metrics.withTrace(getTraceConfig("logout", token.provider), async (span2) => {
      span2.setAttribute("authProvider", token.provider);
      try {
        this.storage.clearToken();
        await ProfileStorage.getInstance().deleteProfile();
        const provider = this.providers[token.authMethod];
        await provider.logout(token);
      } catch (e) {
        ignore.logger.error("Failed to logout:", e);
        throw translateError(e);
      }
    });
  }
  async logoutAndForget() {
    try {
      await this.logout();
    } catch (_e) {
    }
  }
  /**
   * Deletes the user account
   * @returns Promise that resolves when account deletion is complete
   */
  async deleteAccount() {
    if (!this.isLoggedIn()) {
      throw new ssoOidcClient.InvalidAuthError("Not logged in");
    }
    const token = this.storage.readToken();
    if (!token) {
      throw new ssoOidcClient.MissingTokenError("No token available");
    }
    return Metrics.withTrace(getTraceConfig("deleteAccount", token.provider), async (span2) => {
      span2.setAttribute("authProvider", token.provider);
      const provider = this.providers[token.authMethod];
      try {
        await provider.deleteAccount(token);
        this.storage.clearToken();
        this._onDidPerformUserInitiatedLogout.fire();
      } catch (e) {
        ignore.logger.error("Failed to delete account:", e);
        throw translateError(e);
      }
    });
  }
  /**
   * Attempts to refresh the auth token
   * @returns Promise that resolves when token refresh is complete
   */
  async refreshToken() {
    const token = this.storage.readToken();
    if (!(token == null ? void 0 : token.refreshToken)) {
      throw new ssoOidcClient.InvalidAuthError("No valid refresh token found");
    }
    return Metrics.withTrace(getTraceConfig("refreshToken", token.provider), async (span2) => {
      var _a;
      span2.setAttribute("authProvider", token.provider);
      try {
        const provider = this.providers[token.authMethod];
        const newToken = await provider.refreshToken(token);
        if (((_a = this.storage.readToken()) == null ? void 0 : _a.refreshToken) === token.refreshToken) {
          this.storage.writeToken(newToken);
        }
      } catch (e) {
        ignore.logger.error("Failed to refresh token:", e);
        throw e;
      }
    });
  }
  async openInternalLink(path2) {
    const callbackUri = await vscode__namespace.env.asExternalUri(
      vscode__namespace.Uri.parse(`${vscode__namespace.env.uriScheme}://kiro.kiroAgent${path2}`)
    );
    await vscode__namespace.env.openExternal(callbackUri);
  }
  /**
   * Authenticates the user with any of the available login options: social (Google, Github),
   * builderId, enterprise or internal login
   */
  async authenticateWithOptions(options) {
    telemetry_definitions_index.recordOnboardingStep("started-login");
    return Metrics.withTrace(getTraceConfig("authenticate", options.provider), async (span2) => {
      span2.setAttribute("authProvider", options.provider);
      if (this.isLoggedIn()) {
        await this.logout();
      }
      try {
        const provider = this.providers[options.authMethod];
        const token = await provider.authenticate(options);
        this.storage.writeToken(token);
        await this.openInternalLink("/did-authenticate");
        telemetry_definitions_index.recordOnboardingStep("finished-login");
        telemetry_definitions_index.recordAuthFromSource(options);
      } catch (error) {
        if (error instanceof ssoOidcClient.SignInBlockedError) {
          ignore.logger.info("Sign-in temporarily not allowed");
        } else if (error instanceof ssoOidcClient.CanceledError) {
          ignore.logger.info("Authentication canceled");
          telemetry_definitions_index.recordOnboardingStep("canceled-login");
        } else if (error instanceof ssoOidcClient.AbandonedError) {
          ignore.logger.info("Authentication timed out");
          telemetry_definitions_index.recordOnboardingStep("abandoned-login");
        } else if (error instanceof ssoOidcClient.InvalidUserInputError) {
          ignore.logger.error("Authentication failed due to bad user input:", error);
          telemetry_definitions_index.recordOnboardingStep("bad-user-input");
        } else {
          ignore.logger.error("Authentication failed:", error);
          telemetry_definitions_index.recordOnboardingStep("failed-login");
          void vscode__namespace.window.showErrorMessage("Failed to authenticate with Kiro.");
        }
        await this.logout();
        throw error;
      }
    });
  }
  /**
   * Cancels any current ongoing sign-in flow
   */
  cancelSignIn() {
    this.providers.IdC.cancelAuth();
    this.providers.social.cancelAuth();
  }
  /**
   * Consumers of the auth provider should call this method when a token issued through this provider
   * was rejected by the invoked service.
   */
  async handleAuthError(error) {
    if (error instanceof ssoOidcClient.AccessDeniedError || error instanceof ssoOidcClient.MissingTokenError || error instanceof ssoOidcClient.MalformedTokenError || error instanceof ssoOidcClient.InvalidAuthError || error instanceof ssoOidcClient.InvalidSSOAuthError || error instanceof ssoOidcClient.InvalidIdCAuthError) {
      return this.showInvalidSessionErrorMessage();
    } else if (error instanceof ssoOidcClient.NetworkIssueError) {
      return this.showNetworkIssueErrorMessage();
    } else {
      return this.showUnknownIssueErrorMessage();
    }
  }
  async showInvalidSessionErrorMessage() {
    return span.withSpan(telemetry_definitions_index.TelemetryNamespace.Auth, "auth-provider.manual-error-resolve", async () => {
      if (this.authErrorMessagePromises.AccessDenied) {
        return this.authErrorMessagePromises.AccessDenied;
      }
      const promise = vscode__namespace.window.showErrorMessage(
        "Could not complete the request because your session is invalid or expired.",
        "Refresh session",
        "Login"
      );
      this.authErrorMessagePromises.AccessDenied = promise;
      let action = await promise;
      if (action === "Refresh session") {
        try {
          await this.refreshToken();
          void vscode__namespace.window.showInformationMessage("Your session was successfully refreshed.");
        } catch (_e) {
          void this.logoutAndForget();
          action = await vscode__namespace.window.showErrorMessage("We are unable to refresh your session.", "Login");
        }
      }
      if (action === "Login") {
        await this.logout();
        this._onDidPerformUserInitiatedLogout.fire();
      }
      this.authErrorMessagePromises.AccessDenied = null;
    });
  }
  async showNetworkIssueErrorMessage() {
    if (this.authErrorMessagePromises.NetworkIssue) {
      return this.authErrorMessagePromises.NetworkIssue;
    }
    const promise = vscode__namespace.window.showErrorMessage(
      "Could not communicate with the service. Please check your network connection.",
      "Dismiss"
    );
    this.authErrorMessagePromises.NetworkIssue = promise;
    await promise;
    this.authErrorMessagePromises.NetworkIssue = null;
  }
  async showUnknownIssueErrorMessage() {
    if (this.authErrorMessagePromises.Unknown) {
      return this.authErrorMessagePromises.Unknown;
    }
    const promise = vscode__namespace.window.showErrorMessage("An unexpected issue occurred.", "Dismiss");
    this.authErrorMessagePromises.Unknown = promise;
    await promise;
    this.authErrorMessagePromises.Unknown = null;
  }
  /**
   * Returns a promise that resolves once the user is logged in
   */
  async waitForSignIn() {
    if (this.isLoggedIn()) {
      return this.storage.readToken();
    }
    if (!this.signInPromise) {
      this.signInPromise = new Promise((resolve) => {
        this.signInDeferred = { resolve };
      }).then((token) => {
        this.signInPromise = void 0;
        this.signInDeferred = void 0;
        return token;
      });
    }
    return this.signInPromise;
  }
}
const execAsync = util.promisify(child_process.exec);
const MIDWAY_COMMAND = "mwinit";
const WHICH_COMMAND = process.platform == "win32" ? "where.exe" : "which";
async function isMwinitToolAvailable() {
  try {
    await execAsync(`${WHICH_COMMAND} ${MIDWAY_COMMAND}`);
    return true;
  } catch {
    return false;
  }
}
const PROVIDER_ID = "kiro";
const DEFAULT_USER_FACING_ERROR_MESSAGE = "There was an error signing you in. Please try again.";
const authProvider = new AuthProvider();
const providerLabel = {
  BuilderId: "BuilderId",
  Enterprise: "AWS IAM Identity Center",
  Internal: "Amazon internal (Midway)",
  Github: "GitHub",
  Google: "Google"
};
class AuthProviderSession {
  constructor(provider) {
    __publicField(this, "account");
    __publicField(this, "id", PROVIDER_ID);
    __publicField(this, "scopes", []);
    __publicField(this, "accessToken", "");
    this.account = { id: PROVIDER_ID, label: provider ? providerLabel[provider] : "" };
  }
}
class AuthProviderExtension {
  constructor(controller) {
    __publicField(this, "disposables", []);
    __publicField(this, "_onDidChangeSessions", new vscode__namespace.EventEmitter());
    this.controller = controller;
    this.disposables.push(
      authProvider.onDidChangeLoginStatus(({ token, isSignedIn }) => {
        if (isSignedIn) {
          this._onDidChangeSessions.fire({
            removed: [],
            added: [new AuthProviderSession(token.provider)],
            changed: []
          });
        } else {
          this._onDidChangeSessions.fire({
            removed: [new AuthProviderSession()],
            added: [],
            changed: []
          });
        }
      }),
      authProvider.onDidPerformUserInitiatedLogout(() => {
        this.controller.showSignInPage();
      })
    );
  }
  get onDidChangeSessions() {
    return this._onDidChangeSessions.event;
  }
  dispose() {
    this.disposables.forEach((disposable) => {
      disposable.dispose();
    });
  }
  async getSessions(_scopes, _options) {
    if (authProvider.isLoggedIn()) {
      const token = authProvider.readToken();
      return Promise.resolve([new AuthProviderSession(token.provider)]);
    }
    return Promise.resolve([]);
  }
  async createSession(_scopes, _options) {
    if (authProvider.isLoggedIn()) {
      const token2 = authProvider.readToken();
      return new AuthProviderSession(token2.provider);
    }
    this.controller.showSignInPage();
    const token = await authProvider.waitForSignIn();
    return new AuthProviderSession(token.provider);
  }
  async removeSession(_sessionId) {
    if (!authProvider.isLoggedIn()) {
      return;
    }
    await authProvider.logout();
    this.controller.showSignInPage();
  }
}
__publicField(AuthProviderExtension, "name", "Kiro");
class SignInController {
  constructor() {
    __publicField(this, "_onDidReceiveSignInRequest", new vscode__namespace.EventEmitter());
  }
  get onDidReceiveSignInRequest() {
    return this._onDidReceiveSignInRequest.event;
  }
  showSignInPage() {
    this._onDidReceiveSignInRequest.fire();
  }
  async signIn(providerConfiguration) {
    try {
      return await authProvider.authenticateWithOptions(providerConfiguration);
    } catch (error) {
      if (error instanceof ssoOidcClient.AuthError) {
        throw error.toUserFacingError(DEFAULT_USER_FACING_ERROR_MESSAGE);
      }
      throw new ssoOidcClient.UserFacingError(DEFAULT_USER_FACING_ERROR_MESSAGE);
    }
  }
  cancelSignIn() {
    authProvider.cancelSignIn();
  }
}
async function registerAuthProviderExtension(context) {
  const signInController = new SignInController();
  const extensionInstance = new AuthProviderExtension(signInController);
  const authProviderRegistration = vscode__namespace.authentication.registerAuthenticationProvider(
    PROVIDER_ID,
    AuthProviderExtension.name,
    extensionInstance
  );
  const isInternalUser = await isMwinitToolAvailable();
  const signInControllerRegistration = vscode__namespace.authentication.registerSignInController(PROVIDER_ID, signInController, {
    isInternalUser
  });
  context.subscriptions.push(extensionInstance, authProviderRegistration, signInControllerRegistration, authProvider);
}
exports.AbandonedError = ssoOidcClient.AbandonedError;
exports.AccessDeniedError = ssoOidcClient.AccessDeniedError;
exports.AuthError = ssoOidcClient.AuthError;
exports.AuthErrorType = ssoOidcClient.AuthErrorType;
exports.AuthProviderDeniedAccess = ssoOidcClient.AuthProviderDeniedAccess;
exports.AuthProviderFailure = ssoOidcClient.AuthProviderFailure;
exports.CanceledError = ssoOidcClient.CanceledError;
exports.FailedToConnectError = ssoOidcClient.FailedToConnectError;
exports.FileSystemAccessError = ssoOidcClient.FileSystemAccessError;
exports.InvalidAuthError = ssoOidcClient.InvalidAuthError;
exports.InvalidIdCAuthError = ssoOidcClient.InvalidIdCAuthError;
exports.InvalidInvitationCodeError = ssoOidcClient.InvalidInvitationCodeError;
exports.InvalidSSOAuthError = ssoOidcClient.InvalidSSOAuthError;
exports.InvalidStartUrlError = ssoOidcClient.InvalidStartUrlError;
exports.InvalidStateError = ssoOidcClient.InvalidStateError;
exports.InvalidUserInputError = ssoOidcClient.InvalidUserInputError;
exports.MalformedTokenError = ssoOidcClient.MalformedTokenError;
exports.MissingCodeError = ssoOidcClient.MissingCodeError;
exports.MissingPortError = ssoOidcClient.MissingPortError;
exports.MissingStateError = ssoOidcClient.MissingStateError;
exports.MissingTokenError = ssoOidcClient.MissingTokenError;
exports.NetworkIssueError = ssoOidcClient.NetworkIssueError;
exports.SSOInvalidStateError = ssoOidcClient.SSOInvalidStateError;
exports.SSOMissingCodeError = ssoOidcClient.SSOMissingCodeError;
exports.SSOMissingStateError = ssoOidcClient.SSOMissingStateError;
exports.SSORedirectTimeoutError = ssoOidcClient.SSORedirectTimeoutError;
exports.ServerIssueError = ssoOidcClient.ServerIssueError;
exports.ServerListenError = ssoOidcClient.ServerListenError;
exports.ServerTimeoutError = ssoOidcClient.ServerTimeoutError;
exports.SignInBlockedError = ssoOidcClient.SignInBlockedError;
exports.UnexpectedIssueError = ssoOidcClient.UnexpectedIssueError;
exports.UserEnvironmentError = ssoOidcClient.UserEnvironmentError;
exports.UserFacingError = ssoOidcClient.UserFacingError;
exports.getUnknownErrorDetails = ssoOidcClient.getUnknownErrorDetails;
exports.isBadAuthIssue = ssoOidcClient.isBadAuthIssue;
exports.DEFAULT_IGNORE = ignore.DEFAULT_IGNORE;
exports.DEFAULT_IGNORE_DIRS = ignore.DEFAULT_IGNORE_DIRS;
exports.DEFAULT_IGNORE_FILETYPES = ignore.DEFAULT_IGNORE_FILETYPES;
exports.TrustedError = ignore.TrustedError;
exports.defaultIgnoreDir = ignore.defaultIgnoreDir;
exports.defaultIgnoreFile = ignore.defaultIgnoreFile;
exports.gitIgnoreArrayFromFile = ignore.gitIgnoreArrayFromFile;
exports.isAbortError = ignore.isAbortError;
exports.isBlockedAccessError = ignore.isBlockedAccessError;
exports.logger = ignore.logger;
exports.mapUnknownToErrorType = ignore.mapUnknownToErrorType;
exports.mcpLogger = ignore.mcpLogger;
exports.APPLICATION_NAME = telemetry_definitions_index.APPLICATION_NAME;
exports.APPLICATION_VERSION = telemetry_definitions_index.APPLICATION_VERSION;
exports.ContextPropagation = telemetry_definitions_index.ContextPropagation;
exports.Feature = telemetry_definitions_index.Feature;
exports.MetricNamespace = telemetry_definitions_index.MetricNamespace;
exports.MetricReporter = telemetry_definitions_index.MetricReporter;
exports.Telemetry = telemetry_definitions_index.Telemetry;
exports.Tool = telemetry_definitions_index.Tool;
exports.ToolRecorder = telemetry_definitions_index.ToolRecorder;
exports.initializeBaggagePropagation = telemetry_definitions_index.initializeBaggagePropagation;
exports.initializeTelemetry = telemetry_definitions_index.initializeTelemetry;
exports.isInitialized = telemetry_definitions_index.isInitialized;
exports.recordBashToolEvent = telemetry_definitions_index.recordBashToolEvent;
exports.startActiveSpan = span.startActiveSpan;
exports.withSpan = span.withSpan;
exports.RemoteToolRecorder = webFetchMeter.RemoteToolRecorder;
exports.WebFetchRecorder = webFetchMeter.WebFetchRecorder;
exports.recordChatWebviewEvent = webFetchMeter.recordChatWebviewEvent;
exports.recordPowersEvent = webFetchMeter.recordPowersEvent;
exports.recordPowersHistogram = webFetchMeter.recordPowersHistogram;
exports.recordRemoteToolsEvent = webFetchMeter.recordRemoteToolsEvent;
exports.recordRemoteToolsHistogram = webFetchMeter.recordRemoteToolsHistogram;
exports.recordWebFetchEvent = webFetchMeter.recordWebFetchEvent;
exports.MCPConnection = mcpManager.MCPConnection;
exports.MCPJsonConfigSchema = mcpManager.MCPJsonConfigSchema;
exports.MCPManagerSingleton = mcpManager.MCPManagerSingleton;
exports.MCPOptionsSchema = mcpManager.MCPOptionsSchema;
exports.addMCPServerConfig = mcpManager.addMCPServerConfig;
exports.addMCPToolToAutoApproveConfig = mcpManager.addMCPToolToAutoApproveConfig;
exports.disableMCPTools = mcpManager.disableMCPTools;
exports.enableMCPTools = mcpManager.enableMCPTools;
exports.findConfigFileForServer = mcpManager.findConfigFileForServer;
exports.formatToolName = mcpManager.formatToolName;
exports.loadMcpConfig = mcpManager.loadMcpConfig;
exports.mcpServerSources = mcpManager.mcpServerSources;
exports.resetApprovedEnvVars = mcpManager.resetApprovedEnvVars;
exports.setMCPServerDisabled = mcpManager.setMCPServerDisabled;
exports.JourneyTracker = journeyTracker.JourneyTracker;
exports.Metrics = journeyTracker.Metrics;
exports.createCounter = journeyTracker.createCounter;
exports.createHistogram = journeyTracker.createHistogram;
exports.getJourneyTracker = journeyTracker.getJourneyTracker;
exports.uriEventHandler = uri.uriEventHandler;
exports.getActiveMcpConfigLocation = paths.getActiveMcpConfigLocation;
exports.getHomeKiroPath = paths.getHomeKiroPath;
exports.getWorkspaceKiroPath = paths.getWorkspaceKiroPath;
exports.FETCH_TIMEOUT_MS = webFetchClient.FETCH_TIMEOUT_MS;
exports.MAX_CONTENT_SIZE = webFetchClient.MAX_CONTENT_SIZE;
exports.MAX_RETRY_ATTEMPTS = webFetchClient.MAX_RETRY_ATTEMPTS;
exports.TRUNCATED_CONTENT_SIZE = webFetchClient.TRUNCATED_CONTENT_SIZE;
exports.WebFetchClient = webFetchClient.WebFetchClient;
exports.addAgentModeHeadersMiddleware = webFetchClient.addAgentModeHeadersMiddleware;
exports.addPrivacyHeadersMiddleware = webFetchClient.addPrivacyHeadersMiddleware;
exports.updateResolvedIDESetting = webFetchClient.updateResolvedIDESetting;
exports.getMachineId = machineId.getMachineId;
exports.AuthProvider = AuthProvider;
exports.ProfileStorage = ProfileStorage;
exports.authProvider = authProvider;
exports.providerLabel = providerLabel;
exports.registerAuthProviderExtension = registerAuthProviderExtension;
exports.registerProfileStorage = registerProfileStorage;
