var __defProp = Object.defineProperty;
var __defNormalProp = (obj, key, value) => key in obj ? __defProp(obj, key, { enumerable: true, configurable: true, writable: true, value }) : obj[key] = value;
var __publicField = (obj, key, value) => __defNormalProp(obj, typeof key !== "symbol" ? key + "" : key, value);
import { F as FileSystemAccessError, i as isBadAuthIssue, M as MissingTokenError, a as MalformedTokenError, I as InvalidAuthError, b as SignInBlockedError, C as CanceledError, c as AbandonedError, d as InvalidUserInputError, e as AccessDeniedError, f as InvalidSSOAuthError, g as InvalidIdCAuthError, N as NetworkIssueError, U as UnexpectedIssueError, h as AuthError, j as UserEnvironmentError, k as UserFacingError } from "./sso-oidc-client-BbOoOoXP.js";
import { l, s, t, x, u, n, r, p, o, q, D, z, B, y, m, w, v, E } from "./sso-oidc-client-BbOoOoXP.js";
import * as vscode from "vscode";
import { l as logger } from "./ignore-B7xGFdAM.js";
import { f, c, D as D2, T, e, d, g, i, a, b, m as m2 } from "./ignore-B7xGFdAM.js";
import * as path from "path";
import * as os from "os";
import * as fs from "fs";
import "node-machine-id";
import "axios";
import "axios-retry";
import { MetricReporter, e as TelemetryNamespace, f as recordOnboardingStep, g as recordAuthFromSource } from "./telemetry/definitions/index.js";
import { A, b as b2, C, Feature, M, Telemetry, T as T2, a as a2, c as c2, d as d2, i as i2, r as r2 } from "./telemetry/definitions/index.js";
import { S as SocialAuthProvider, I as IDCAuthProvider } from "./social-auth-provider-cN_RAEO7.js";
import { w as withSpan } from "./span-Dkp1xmr6.js";
import { s as s2 } from "./span-Dkp1xmr6.js";
import "@opentelemetry/api";
import { R, W, r as r3, a as a3, b as b3, c as c3, d as d3, e as e2 } from "./web-fetch-meter-CVTg62lw.js";
import { exec } from "child_process";
import { promisify } from "util";
import { c as c4, a as a4, b as b4, M as M2, d as d4, h, g as g2, e as e3, i as i3, f as f2, l as l2, m as m3, r as r4, s as s3 } from "./mcp-manager-ChA9kCeg.js";
import { J, M as M3, c as c5, a as a5, g as g3 } from "./journey-tracker-BM6FRGIs.js";
import { u as u2 } from "./uri-BP-gwzJs.js";
import { b as b5, g as g4, a as a6 } from "./paths-CZlww8F7.js";
import { F, c as c6, M as M4, T as T3, W as W2, b as b6, a as a7, u as u3 } from "./web-fetch-client-Cgle-lGV.js";
import { g as g5 } from "./machine-id-DDyBZGvP.js";
const KIRO_AUTH_TOKEN_FILE_NAME = "kiro-auth-token.json";
const SOCIAL_PROVIDERS = ["Google", "Github"];
const IDC_PROVIDERS = ["Enterprise", "BuilderId", "Internal"];
class TokenStorage {
  constructor() {
    __publicField(this, "tokenCache");
    __publicField(this, "cacheDirectory", path.join(os.homedir(), ".aws", "sso", "cache"));
    __publicField(this, "_onDidChange", new vscode.EventEmitter());
    __publicField(this, "watchListener");
    this.watchListener = () => {
      this.clearCache();
      this._onDidChange.fire();
    };
    fs.watchFile(this.getAuthTokenPath(), this.watchListener);
  }
  /**
   * Cleans up internal state
   */
  dispose() {
    fs.unwatchFile(this.getAuthTokenPath(), this.watchListener);
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
    return path.join(this.cacheDirectory, KIRO_AUTH_TOKEN_FILE_NAME);
  }
  ensureCacheDirectory() {
    try {
      if (!fs.existsSync(this.cacheDirectory)) {
        fs.mkdirSync(this.cacheDirectory, { recursive: true });
      }
    } catch (_e) {
      throw new FileSystemAccessError(this.cacheDirectory);
    }
  }
  writeTokenToLocalCache(token) {
    this.tokenCache = token;
  }
  writeTokenToDisk(token) {
    this.ensureCacheDirectory();
    const tokenPath = this.getAuthTokenPath();
    try {
      fs.writeFileSync(tokenPath, JSON.stringify(token, void 0, 2));
    } catch (_e) {
      throw new FileSystemAccessError(tokenPath);
    }
  }
  clearCache() {
    this.tokenCache = void 0;
  }
  readTokenFromDisk() {
    const tokenPath = this.getAuthTokenPath();
    if (fs.existsSync(tokenPath)) {
      try {
        const cacheContents = fs.readFileSync(tokenPath, "utf8");
        try {
          return JSON.parse(cacheContents);
        } catch (e4) {
          logger.error("Error trying to parse the token file.", e4);
          return void 0;
        }
      } catch (_e) {
        throw new FileSystemAccessError(tokenPath);
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
      if (fs.existsSync(tokenPath)) {
        fs.unlinkSync(tokenPath);
      }
    } catch (_e) {
      throw new FileSystemAccessError(tokenPath);
    }
    this._onDidChange.fire();
  }
}
const _ProfileStorage = class _ProfileStorage {
  constructor(context) {
    __publicField(this, "profileUri");
    __publicField(this, "PROFILE_FILE_NAME", "profile.json");
    this.profileUri = vscode.Uri.joinPath(context.globalStorageUri, this.PROFILE_FILE_NAME);
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
    await this.ensureDirectoryExists(vscode.Uri.joinPath(this.profileUri, ".."));
    try {
      const jsonContent = JSON.stringify(profile, null, 2);
      const content = new TextEncoder().encode(jsonContent);
      await vscode.workspace.fs.writeFile(this.profileUri, content);
    } catch (error) {
      logger.error("[ProfileStorage] Failed to write profile", { error });
    }
  }
  /**
   * Reads the current profile from persistent storage.
   * @returns The current profile, or undefined if no valid profile exists
   */
  async readProfile() {
    try {
      const fileContent = await vscode.workspace.fs.readFile(this.profileUri);
      const fileText = new TextDecoder().decode(fileContent);
      const parsedData = JSON.parse(fileText);
      if (this.validateProfile(parsedData)) {
        return parsedData;
      } else {
        logger.error("[ProfileStorage] Invalid profile data structure in storage file");
        return void 0;
      }
    } catch (error) {
      if (error instanceof vscode.FileSystemError && error.code === "FileNotFound") {
        return void 0;
      }
      logger.error("[ProfileStorage] Error reading profile", { error });
      return void 0;
    }
  }
  /**
   * Deletes the current profile from persistent storage.
   * @throws Will not throw - errors are logged and handled gracefully
   */
  async deleteProfile() {
    try {
      await vscode.workspace.fs.delete(this.profileUri);
    } catch (error) {
      if (error instanceof vscode.FileSystemError && error.code === "FileNotFound") {
        return;
      }
      logger.error("[ProfileStorage] Error deleting profile", { error });
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
      await vscode.workspace.fs.createDirectory(dirUri);
    } catch (error) {
      if (error instanceof vscode.FileSystemError && error.code === "FileExists") {
        return;
      }
      logger.error("[ProfileStorage] Failed to create directory", { dirUri: dirUri.toString(), error });
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
const Metrics = new MetricReporter(TelemetryNamespace.Auth, "auth-provider");
const ERROR_MAPPER = (error) => {
  if (error instanceof SignInBlockedError) {
    return {
      blocked: 1
    };
  } else if (error instanceof CanceledError) {
    return {
      abort: 1
    };
  } else if (error instanceof AbandonedError) {
    return {
      abandon: 1
    };
  } else if (error instanceof InvalidUserInputError) {
    return {
      badInput: 1
    };
  } else if (error instanceof UserEnvironmentError) {
    return {
      environmentIssue: 1
    };
  } else if (isBadAuthIssue(error)) {
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
  return error instanceof AuthError ? error : new UnexpectedIssueError("Auth provider: unexpected issue");
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
    __publicField(this, "_onDidChangeLoginStatus", new vscode.EventEmitter());
    __publicField(this, "_onDidPerformUserInitiatedLogout", new vscode.EventEmitter());
    __publicField(this, "disposables", []);
    this.storage = new TokenStorage();
    this.providers = {
      IdC: new IDCAuthProvider(),
      social: new SocialAuthProvider()
    };
    if (vscode.window.state.focused) {
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
      vscode.window.onDidChangeWindowState((event) => {
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
        await withSpan(TelemetryNamespace.Auth, "auth-provider.scheduled-refresh", () => {
          return this.refreshToken();
        });
      }
    } catch (error) {
      const token = this.storage.readToken();
      if (isBadAuthIssue(error) && token && this.isAuthTokenExpiredWithinSeconds(token, AUTH_TOKEN_INVALIDATION_OFFSET_SECONDS)) {
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
        throw new MissingTokenError("No valid token found");
      }
      if (!this.isAuthTokenExpired(token)) {
        return token;
      }
      if (token.refreshToken && attemptRefresh) {
        return await withSpan(TelemetryNamespace.Auth, "auth-provider.getTokenData", async () => {
          await this.refreshToken();
          return await this.getTokenData({ attemptRefresh: false });
        });
      }
      throw new MalformedTokenError("No valid token found");
    } catch (error) {
      if (isBadAuthIssue(error)) {
        void this.logoutAndForget();
      }
      logger.error("Failed to retrieve auth token:", error);
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
    return Metrics.withTrace(getTraceConfig("logout", token.provider), async (span) => {
      span.setAttribute("authProvider", token.provider);
      try {
        this.storage.clearToken();
        await ProfileStorage.getInstance().deleteProfile();
        const provider = this.providers[token.authMethod];
        await provider.logout(token);
      } catch (e4) {
        logger.error("Failed to logout:", e4);
        throw translateError(e4);
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
      throw new InvalidAuthError("Not logged in");
    }
    const token = this.storage.readToken();
    if (!token) {
      throw new MissingTokenError("No token available");
    }
    return Metrics.withTrace(getTraceConfig("deleteAccount", token.provider), async (span) => {
      span.setAttribute("authProvider", token.provider);
      const provider = this.providers[token.authMethod];
      try {
        await provider.deleteAccount(token);
        this.storage.clearToken();
        this._onDidPerformUserInitiatedLogout.fire();
      } catch (e4) {
        logger.error("Failed to delete account:", e4);
        throw translateError(e4);
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
      throw new InvalidAuthError("No valid refresh token found");
    }
    return Metrics.withTrace(getTraceConfig("refreshToken", token.provider), async (span) => {
      var _a;
      span.setAttribute("authProvider", token.provider);
      try {
        const provider = this.providers[token.authMethod];
        const newToken = await provider.refreshToken(token);
        if (((_a = this.storage.readToken()) == null ? void 0 : _a.refreshToken) === token.refreshToken) {
          this.storage.writeToken(newToken);
        }
      } catch (e4) {
        logger.error("Failed to refresh token:", e4);
        throw e4;
      }
    });
  }
  async openInternalLink(path2) {
    const callbackUri = await vscode.env.asExternalUri(
      vscode.Uri.parse(`${vscode.env.uriScheme}://kiro.kiroAgent${path2}`)
    );
    await vscode.env.openExternal(callbackUri);
  }
  /**
   * Authenticates the user with any of the available login options: social (Google, Github),
   * builderId, enterprise or internal login
   */
  async authenticateWithOptions(options) {
    recordOnboardingStep("started-login");
    return Metrics.withTrace(getTraceConfig("authenticate", options.provider), async (span) => {
      span.setAttribute("authProvider", options.provider);
      if (this.isLoggedIn()) {
        await this.logout();
      }
      try {
        const provider = this.providers[options.authMethod];
        const token = await provider.authenticate(options);
        this.storage.writeToken(token);
        await this.openInternalLink("/did-authenticate");
        recordOnboardingStep("finished-login");
        recordAuthFromSource(options);
      } catch (error) {
        if (error instanceof SignInBlockedError) {
          logger.info("Sign-in temporarily not allowed");
        } else if (error instanceof CanceledError) {
          logger.info("Authentication canceled");
          recordOnboardingStep("canceled-login");
        } else if (error instanceof AbandonedError) {
          logger.info("Authentication timed out");
          recordOnboardingStep("abandoned-login");
        } else if (error instanceof InvalidUserInputError) {
          logger.error("Authentication failed due to bad user input:", error);
          recordOnboardingStep("bad-user-input");
        } else {
          logger.error("Authentication failed:", error);
          recordOnboardingStep("failed-login");
          void vscode.window.showErrorMessage("Failed to authenticate with Kiro.");
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
    if (error instanceof AccessDeniedError || error instanceof MissingTokenError || error instanceof MalformedTokenError || error instanceof InvalidAuthError || error instanceof InvalidSSOAuthError || error instanceof InvalidIdCAuthError) {
      return this.showInvalidSessionErrorMessage();
    } else if (error instanceof NetworkIssueError) {
      return this.showNetworkIssueErrorMessage();
    } else {
      return this.showUnknownIssueErrorMessage();
    }
  }
  async showInvalidSessionErrorMessage() {
    return withSpan(TelemetryNamespace.Auth, "auth-provider.manual-error-resolve", async () => {
      if (this.authErrorMessagePromises.AccessDenied) {
        return this.authErrorMessagePromises.AccessDenied;
      }
      const promise = vscode.window.showErrorMessage(
        "Could not complete the request because your session is invalid or expired.",
        "Refresh session",
        "Login"
      );
      this.authErrorMessagePromises.AccessDenied = promise;
      let action = await promise;
      if (action === "Refresh session") {
        try {
          await this.refreshToken();
          void vscode.window.showInformationMessage("Your session was successfully refreshed.");
        } catch (_e) {
          void this.logoutAndForget();
          action = await vscode.window.showErrorMessage("We are unable to refresh your session.", "Login");
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
    const promise = vscode.window.showErrorMessage(
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
    const promise = vscode.window.showErrorMessage("An unexpected issue occurred.", "Dismiss");
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
const execAsync = promisify(exec);
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
    __publicField(this, "_onDidChangeSessions", new vscode.EventEmitter());
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
    __publicField(this, "_onDidReceiveSignInRequest", new vscode.EventEmitter());
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
      if (error instanceof AuthError) {
        throw error.toUserFacingError(DEFAULT_USER_FACING_ERROR_MESSAGE);
      }
      throw new UserFacingError(DEFAULT_USER_FACING_ERROR_MESSAGE);
    }
  }
  cancelSignIn() {
    authProvider.cancelSignIn();
  }
}
async function registerAuthProviderExtension(context) {
  const signInController = new SignInController();
  const extensionInstance = new AuthProviderExtension(signInController);
  const authProviderRegistration = vscode.authentication.registerAuthenticationProvider(
    PROVIDER_ID,
    AuthProviderExtension.name,
    extensionInstance
  );
  const isInternalUser = await isMwinitToolAvailable();
  const signInControllerRegistration = vscode.authentication.registerSignInController(PROVIDER_ID, signInController, {
    isInternalUser
  });
  context.subscriptions.push(extensionInstance, authProviderRegistration, signInControllerRegistration, authProvider);
}
export {
  A as APPLICATION_NAME,
  b2 as APPLICATION_VERSION,
  AbandonedError,
  AccessDeniedError,
  AuthError,
  l as AuthErrorType,
  AuthProvider,
  s as AuthProviderDeniedAccess,
  t as AuthProviderFailure,
  CanceledError,
  C as ContextPropagation,
  f as DEFAULT_IGNORE,
  c as DEFAULT_IGNORE_DIRS,
  D2 as DEFAULT_IGNORE_FILETYPES,
  F as FETCH_TIMEOUT_MS,
  x as FailedToConnectError,
  Feature,
  FileSystemAccessError,
  InvalidAuthError,
  InvalidIdCAuthError,
  u as InvalidInvitationCodeError,
  InvalidSSOAuthError,
  n as InvalidStartUrlError,
  r as InvalidStateError,
  InvalidUserInputError,
  J as JourneyTracker,
  c6 as MAX_CONTENT_SIZE,
  M4 as MAX_RETRY_ATTEMPTS,
  c4 as MCPConnection,
  a4 as MCPJsonConfigSchema,
  b4 as MCPManagerSingleton,
  M2 as MCPOptionsSchema,
  MalformedTokenError,
  M as MetricNamespace,
  MetricReporter,
  M3 as Metrics,
  p as MissingCodeError,
  o as MissingPortError,
  q as MissingStateError,
  MissingTokenError,
  NetworkIssueError,
  ProfileStorage,
  R as RemoteToolRecorder,
  D as SSOInvalidStateError,
  z as SSOMissingCodeError,
  B as SSOMissingStateError,
  y as SSORedirectTimeoutError,
  m as ServerIssueError,
  w as ServerListenError,
  v as ServerTimeoutError,
  SignInBlockedError,
  T3 as TRUNCATED_CONTENT_SIZE,
  Telemetry,
  T2 as Tool,
  a2 as ToolRecorder,
  T as TrustedError,
  UnexpectedIssueError,
  UserEnvironmentError,
  UserFacingError,
  W2 as WebFetchClient,
  W as WebFetchRecorder,
  b6 as addAgentModeHeadersMiddleware,
  d4 as addMCPServerConfig,
  h as addMCPToolToAutoApproveConfig,
  a7 as addPrivacyHeadersMiddleware,
  authProvider,
  c5 as createCounter,
  a5 as createHistogram,
  e as defaultIgnoreDir,
  d as defaultIgnoreFile,
  g2 as disableMCPTools,
  e3 as enableMCPTools,
  i3 as findConfigFileForServer,
  f2 as formatToolName,
  b5 as getActiveMcpConfigLocation,
  g4 as getHomeKiroPath,
  g3 as getJourneyTracker,
  g5 as getMachineId,
  E as getUnknownErrorDetails,
  a6 as getWorkspaceKiroPath,
  g as gitIgnoreArrayFromFile,
  c2 as initializeBaggagePropagation,
  d2 as initializeTelemetry,
  i as isAbortError,
  isBadAuthIssue,
  a as isBlockedAccessError,
  i2 as isInitialized,
  l2 as loadMcpConfig,
  logger,
  b as mapUnknownToErrorType,
  m2 as mcpLogger,
  m3 as mcpServerSources,
  providerLabel,
  r2 as recordBashToolEvent,
  r3 as recordChatWebviewEvent,
  a3 as recordPowersEvent,
  b3 as recordPowersHistogram,
  c3 as recordRemoteToolsEvent,
  d3 as recordRemoteToolsHistogram,
  e2 as recordWebFetchEvent,
  registerAuthProviderExtension,
  registerProfileStorage,
  r4 as resetApprovedEnvVars,
  s3 as setMCPServerDisabled,
  s2 as startActiveSpan,
  u3 as updateResolvedIDESetting,
  u2 as uriEventHandler,
  withSpan
};
