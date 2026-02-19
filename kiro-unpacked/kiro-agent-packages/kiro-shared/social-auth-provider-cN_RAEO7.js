var __defProp = Object.defineProperty;
var __typeError = (msg) => {
  throw TypeError(msg);
};
var __defNormalProp = (obj, key, value) => key in obj ? __defProp(obj, key, { enumerable: true, configurable: true, writable: true, value }) : obj[key] = value;
var __publicField = (obj, key, value) => __defNormalProp(obj, typeof key !== "symbol" ? key + "" : key, value);
var __accessCheck = (obj, member, msg) => member.has(obj) || __typeError("Cannot " + msg);
var __privateGet = (obj, member, getter) => (__accessCheck(obj, member, "read from private field"), getter ? getter.call(obj) : member.get(obj));
var __privateAdd = (obj, member, value) => member.has(obj) ? __typeError("Cannot add the same private member more than once") : member instanceof WeakSet ? member.add(obj) : member.set(obj, value);
var __privateSet = (obj, member, value, setter) => (__accessCheck(obj, member, "write to private field"), setter ? setter.call(obj, value) : member.set(obj, value), value);
var _lastInstance;
import * as vscode from "vscode";
import * as os from "os";
import * as fs from "fs";
import * as path from "path";
import crypto from "crypto";
import { U as UnexpectedIssueError, w as ServerListenError, v as ServerTimeoutError, o as MissingPortError, s as AuthProviderDeniedAccess, t as AuthProviderFailure, p as MissingCodeError, q as MissingStateError, r as InvalidStateError, C as CanceledError, c as AbandonedError, A as AuthServiceClient, S as SSOOIDCClient, g as InvalidIdCAuthError, F as FileSystemAccessError, z as SSOMissingCodeError, B as SSOMissingStateError, D as SSOInvalidStateError, E as getUnknownErrorDetails, y as SSORedirectTimeoutError } from "./sso-oidc-client-BbOoOoXP.js";
import http__default from "http";
import { e as TelemetryNamespace } from "./telemetry/definitions/index.js";
import { l as logger, T as TrustedError } from "./ignore-B7xGFdAM.js";
import "node-machine-id";
import "axios";
import "axios-retry";
import { w as withSpan } from "./span-Dkp1xmr6.js";
import "@opentelemetry/api";
import "./web-fetch-meter-CVTg62lw.js";
import { u as uriEventHandler } from "./uri-BP-gwzJs.js";
const _AuthSSOServer = class _AuthSSOServer {
  constructor(state) {
    __publicField(this, "baseUrl", `http://127.0.0.1`);
    __publicField(this, "oauthCallback", "/oauth/callback");
    __publicField(this, "authenticationFlowTimeoutInMs", 6e5);
    __publicField(this, "authenticationWarningTimeoutInMs", 6e4);
    __publicField(this, "listenTimeoutMs", 1e4);
    __publicField(this, "authenticationPromise");
    __publicField(this, "deferred");
    __publicField(this, "server");
    __publicField(this, "connections");
    __publicField(this, "_closed", false);
    this.state = state;
    this.authenticationPromise = new Promise((resolve, reject) => {
      this.deferred = { resolve, reject };
    });
    this.connections = [];
    this.server = http__default.createServer((request, response) => {
      response.setHeader("Access-Control-Allow-Methods", "GET");
      if (!request.url) {
        return;
      }
      const url = new URL(request.url, this.baseUrl);
      switch (url.pathname) {
        case this.oauthCallback: {
          this.handleAuthentication(url.searchParams, response);
          break;
        }
        default: {
          logger.info("Unexpected invocation of AuthSSOServer. Path: %s", url.pathname);
        }
      }
    });
    this.server.on("connection", (connection) => {
      this.connections.push(connection);
    });
  }
  /** Gets the last initialized instance */
  static get lastInstance() {
    return __privateGet(_AuthSSOServer, _lastInstance);
  }
  /**
   * Initializes a new AuthSSOServer
   * @param state - The state parameter for validation
   */
  static init(state = "") {
    return withSpan(TelemetryNamespace.Auth, "auth-server.init", async () => {
      const lastInstance = __privateGet(_AuthSSOServer, _lastInstance);
      if (lastInstance !== void 0 && !lastInstance.closed) {
        try {
          await lastInstance.close();
        } catch (error) {
          logger.error("Failed to close already existing auth server in AuthSSOServer.init(): %s", error);
        }
      }
      logger.debug("AuthSSOServer: Initialized new auth server.");
      const instance = new _AuthSSOServer(state);
      __privateSet(_AuthSSOServer, _lastInstance, instance);
      return instance;
    });
  }
  /** Starts the server */
  start(ports) {
    return withSpan(TelemetryNamespace.Auth, "auth-server.start", async (span) => {
      let portIndex = 0;
      if (this.server.listening) {
        throw new UnexpectedIssueError("AuthSSOServer: Server already started");
      }
      return new Promise((resolve, reject) => {
        this.server.on("close", () => {
          reject(new UnexpectedIssueError("AuthSSOServer: Server has closed"));
        });
        this.server.on("error", (error) => {
          if (ports && ports.length > portIndex + 1) {
            this.listen(ports[++portIndex]);
          } else {
            reject(new ServerListenError(error.message, ports));
          }
        });
        const timeout = setTimeout(() => {
          if (!this.server.listening) {
            void this.close();
            reject(new ServerTimeoutError());
          }
        }, this.listenTimeoutMs);
        this.server.on("listening", () => {
          clearTimeout(timeout);
          if (!this.server.address()) {
            reject(new MissingPortError());
          }
          span.setAttribute("redirectUri", this.redirectUri);
          resolve();
        });
        this.listen((ports == null ? void 0 : ports[0]) || 0);
      });
    });
  }
  listen(port) {
    this.server.listen(port, "127.0.0.1");
  }
  /**
   * Attempts to close the server and swallows exceptions
   */
  attemptClose() {
    const doClose = async () => {
      try {
        await this.close();
      } catch (_e) {
      }
    };
    void doClose();
  }
  /** Closes the server */
  close() {
    return withSpan(TelemetryNamespace.Auth, "auth-server.close", async (span) => {
      try {
        span.setAttribute("redirectUri", this.redirectUri);
      } catch (_e) {
        span.setAttribute("redirectUri", "");
      }
      return new Promise((resolve, reject) => {
        if (this._closed) {
          resolve();
          return;
        }
        if (!this.server.listening) {
          reject(new UnexpectedIssueError("AuthSSOServer: Server not started"));
        }
        logger.debug("AuthSSOServer: Attempting to close server.");
        for (const connection of this.connections) {
          connection.destroy();
        }
        this.server.close((error) => {
          if (error) {
            reject(error);
          }
          this._closed = true;
          logger.debug("AuthSSOServer: Server closed successfully.");
          resolve();
        });
      });
    });
  }
  /** Gets the redirect URI */
  get redirectUri() {
    return `${this.baseLocation}${this.oauthCallback}`;
  }
  get baseLocation() {
    return `${this.baseUrl}:${this.getPort()}`;
  }
  /** Gets whether the server is closed */
  get closed() {
    return this._closed;
  }
  /** Gets the server address */
  getAddress() {
    return this.server.address();
  }
  getPort() {
    const address = this.getAddress();
    if (address instanceof Object) {
      return address.port;
    } else if (typeof address === "string") {
      return Number.parseInt(address);
    } else {
      throw new MissingPortError();
    }
  }
  // TODO: Redirect to a nicer page later with proper UI feedback
  redirect(response) {
    response.writeHead(200, { "Content-Type": "text/html" });
    const message = "You can close this window";
    response.write(message);
    response.end();
  }
  handleAuthentication(parameters, response) {
    var _a;
    const error = parameters.get("error");
    const errorDescription = parameters.get("error_description");
    if (error && errorDescription) {
      if (error === "access_denied") {
        this.handleRequestRejection(response, new AuthProviderDeniedAccess());
      } else {
        this.handleRequestRejection(response, new AuthProviderFailure(`${error}: ${errorDescription}`));
      }
      return;
    }
    const code = parameters.get("code");
    if (!code) {
      this.handleRequestRejection(response, new MissingCodeError());
      return;
    }
    if (this.state) {
      const state = parameters.get("state");
      if (!state) {
        this.handleRequestRejection(response, new MissingStateError());
        return;
      }
      if (state !== this.state) {
        this.handleRequestRejection(response, new InvalidStateError());
        return;
      }
    }
    (_a = this.deferred) == null ? void 0 : _a.resolve(code);
    this.redirect(response);
  }
  handleRequestRejection(response, error) {
    var _a;
    this.redirect(response);
    (_a = this.deferred) == null ? void 0 : _a.reject(error);
  }
  /** Cancels the current authentication flow */
  cancelCurrentFlow() {
    var _a;
    logger.debug("AuthSSOServer: Canceling current login flow");
    (_a = this.deferred) == null ? void 0 : _a.reject(new CanceledError("user cancellation"));
  }
  /** Waits for authorization to complete */
  async waitForAuthorization() {
    const warningTimeout = setTimeout(() => {
      logger.warn("AuthSSOServer: Authentication is taking a long time");
    }, this.authenticationWarningTimeoutInMs);
    try {
      return await Promise.race([
        this.authenticationPromise,
        new Promise((_resolve, reject) => {
          setTimeout(() => {
            reject(new AbandonedError());
          }, this.authenticationFlowTimeoutInMs);
        })
      ]);
    } finally {
      clearTimeout(warningTimeout);
      this.attemptClose();
    }
  }
};
_lastInstance = new WeakMap();
// Last initialized instance of the Auth Server
__privateAdd(_AuthSSOServer, _lastInstance);
let AuthSSOServer = _AuthSSOServer;
const CLIENT_REG_INVALIDATION_OFFSET_SECONDS = 15 * 60;
const BUILDER_ID_START_URL = "https://view.awsapps.com/start";
const INTERNAL_SSO_START_URL = "https://amzn.awsapps.com/start";
class ClientRegistrationStorage {
  constructor() {
    __publicField(this, "cacheDirectory", path.join(os.homedir(), ".aws", "sso", "cache"));
  }
  getClientRegistrationPath(clientIdHash) {
    return path.join(this.cacheDirectory, `${clientIdHash}.json`);
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
  /**
   * Writes client registration to cache
   */
  writeClientRegistration(clientIdHash, registration) {
    this.ensureCacheDirectory();
    const filePath = this.getClientRegistrationPath(clientIdHash);
    try {
      fs.writeFileSync(filePath, JSON.stringify(registration, void 0, 2));
    } catch (_e) {
      throw new FileSystemAccessError(filePath);
    }
  }
  /**
   * Reads the currently cached client registration
   */
  readClientRegistration(clientIdHash) {
    const filePath = this.getClientRegistrationPath(clientIdHash);
    if (fs.existsSync(filePath)) {
      try {
        const fileContent = fs.readFileSync(filePath, "utf8");
        try {
          return JSON.parse(fileContent);
        } catch (_e) {
          return void 0;
        }
      } catch (_e) {
        throw new FileSystemAccessError(filePath);
      }
    }
  }
  /**
   * Deletes the cached client registration file
   */
  deleteClientRegistration(clientIdHash) {
    const filePath = this.getClientRegistrationPath(clientIdHash);
    if (fs.existsSync(filePath)) {
      try {
        fs.unlinkSync(filePath);
      } catch (_e) {
        throw new FileSystemAccessError(filePath);
      }
    }
  }
}
const GRANT_SCOPES = ["completions", "analysis", "conversations", "transformations", "taskassist"];
class IDCAuthProvider {
  constructor() {
    __publicField(this, "storage");
    __publicField(this, "authServiceClient");
    __publicField(this, "scopes");
    __publicField(this, "authServer");
    this.storage = new ClientRegistrationStorage();
    this.authServiceClient = new AuthServiceClient();
    const scopePrefix = vscode.workspace.getConfiguration("codewhisperer.config").get("scopePrefix") ?? "codewhisperer";
    this.scopes = GRANT_SCOPES.map((scope) => {
      return `${scopePrefix}:${scope}`;
    });
  }
  getClientIdHash(startUrl) {
    return crypto.createHash("sha1").update(JSON.stringify({ startUrl })).digest("hex");
  }
  tokenResponseToToken(tokenResponse, clientIdHash, provider, region) {
    const now = /* @__PURE__ */ new Date();
    const expiresAt = new Date(now.getTime() + Number(tokenResponse.expiresIn) * 1e3);
    return {
      accessToken: tokenResponse.accessToken,
      refreshToken: tokenResponse.refreshToken,
      expiresAt: expiresAt.toISOString(),
      clientIdHash,
      authMethod: "IdC",
      provider,
      region
    };
  }
  isClientRegistrationExpired(clientReg) {
    if (!clientReg.expiresAt) {
      return true;
    }
    const expiresAt = new Date(clientReg.expiresAt);
    const now = /* @__PURE__ */ new Date();
    return expiresAt.valueOf() < now.valueOf() + CLIENT_REG_INVALIDATION_OFFSET_SECONDS * 1e3;
  }
  async registerClient(startUrl, region, hasUserProvidedInput = false) {
    return withSpan(TelemetryNamespace.Auth, "idc-provider.register", async () => {
      const clientIdHash = this.getClientIdHash(startUrl);
      const ssoClient = new SSOOIDCClient(region);
      const clientRegistrationResp = await ssoClient.registerClient(
        {
          clientName: "Kiro IDE",
          clientType: "public",
          scopes: this.scopes,
          grantTypes: ["authorization_code", "refresh_token"],
          redirectUris: ["http://127.0.0.1/oauth/callback"],
          issuerUrl: startUrl
        },
        hasUserProvidedInput
      );
      const clientReg = {
        clientId: clientRegistrationResp.clientId,
        clientSecret: clientRegistrationResp.clientSecret,
        expiresAt: new Date(clientRegistrationResp.clientSecretExpiresAt * 1e3).toISOString()
      };
      this.storage.writeClientRegistration(clientIdHash, clientReg);
      return clientReg;
    });
  }
  getStartUrl(options) {
    if (options.provider === "Enterprise") {
      return options.startUrl;
    } else if (options.provider === "BuilderId") {
      return BUILDER_ID_START_URL;
    } else {
      return INTERNAL_SSO_START_URL;
    }
  }
  /**
   * Authenticates via IDC method using browser-based OAuth flow using start url
   * @returns Promise that resolves to the token data when authentication is complete
   */
  async authenticate(options) {
    return withSpan(TelemetryNamespace.Auth, "idc-provider.authenticate", async (span) => {
      span.setAttribute("authProvider", options.provider);
      if (options.authMethod !== "IdC") {
        throw new UnexpectedIssueError("IdC auth: invalid auth method");
      }
      const startUrl = this.getStartUrl(options);
      const region = options.region || "us-east-1";
      const ssoClient = new SSOOIDCClient(region);
      const clientRegistration = await this.registerClient(startUrl, region, options.provider === "Enterprise");
      const state = crypto.randomUUID();
      this.authServer = await AuthSSOServer.init(state);
      try {
        await this.authServer.start();
      } catch (error) {
        const trustedError = new TrustedError(
          `Failed to start authentication server. This is likely due to network or firewall restrictions preventing the local server from starting. ${error instanceof Error ? error.message : String(error)}`
        );
        logger.error("AuthServer start failed:", trustedError);
        throw trustedError;
      }
      const codeVerifier = crypto.randomBytes(32).toString("base64url");
      const codeChallenge = crypto.createHash("sha256").update(codeVerifier).digest().toString("base64url");
      const redirectUri = this.authServer.redirectUri;
      const parameters = new URLSearchParams({
        response_type: "code",
        client_id: clientRegistration.clientId,
        redirect_uri: redirectUri,
        scopes: this.scopes.join(","),
        state,
        code_challenge: codeChallenge,
        code_challenge_method: "S256"
      });
      const authorizeUrl = `https://oidc.${region}.amazonaws.com/authorize?${parameters.toString()}`;
      await vscode.env.openExternal(vscode.Uri.parse(authorizeUrl));
      let code;
      try {
        code = await this.authServer.waitForAuthorization();
      } finally {
        this.authServer = void 0;
      }
      const response = await ssoClient.createToken({
        clientId: clientRegistration.clientId,
        clientSecret: clientRegistration.clientSecret,
        grantType: "authorization_code",
        redirectUri,
        code,
        codeVerifier
      });
      const token = this.tokenResponseToToken(response, this.getClientIdHash(startUrl), options.provider, region);
      await this.handleProfiles(token);
      return token;
    });
  }
  /**
   * Cancels a currently ongoing sign-in flow
   */
  cancelAuth() {
    if (this.authServer) {
      this.authServer.cancelCurrentFlow();
    }
  }
  /**
   * Refreshes token granted through IDC auth
   * @returns Promise that resolves to the refreshed token data
   */
  async refreshToken(token) {
    return withSpan(TelemetryNamespace.Auth, "idc-provider.refreshToken", async (span) => {
      span.setAttribute("authProvider", token.provider);
      if (token.authMethod !== "IdC") {
        throw new UnexpectedIssueError("IdC auth: invalid auth method");
      }
      const { refreshToken, clientIdHash, provider, region } = token;
      try {
        const clientToken = this.storage.readClientRegistration(clientIdHash);
        const tokenRegion = region || "us-east-1";
        const ssoClient = new SSOOIDCClient(tokenRegion);
        if (!clientToken || this.isClientRegistrationExpired(clientToken)) {
          throw new InvalidIdCAuthError("IdC auth: No valid client registration found");
        }
        const token2 = await ssoClient.createToken({
          clientId: clientToken.clientId,
          clientSecret: clientToken.clientSecret,
          refreshToken,
          grantType: "refresh_token"
        });
        return this.tokenResponseToToken(token2, clientIdHash, provider, tokenRegion);
      } catch (error) {
        logger.error("Error refreshing token:", error);
        throw error;
      }
    });
  }
  /**
   * Logs the user out of a session generated through IDC auth
   * @returns Promise that resolves when logout was complete
   */
  logout(token) {
    try {
      if (token.authMethod !== "IdC") {
        throw new UnexpectedIssueError("IdC auth: invalid auth method");
      }
      this.storage.deleteClientRegistration(token.clientIdHash);
    } catch (error) {
      logger.error("Error deleting client registration during logout:", error);
    }
    return Promise.resolve();
  }
  /**
   * Deletes the user account for IDC auth provider.
   * Only supported for BuilderId accounts.
   * @param token - The token cache data
   * @throws {Error} Throws if account deletion is not supported for the provider type
   */
  async deleteAccount(token) {
    return withSpan(TelemetryNamespace.Auth, "idc-provider.deleteAccount", async (span) => {
      span.setAttribute("authProvider", token.provider);
      if (token.authMethod !== "IdC") {
        throw new UnexpectedIssueError("IdC auth: invalid auth method");
      }
      if (token.provider === "BuilderId") {
        return this.authServiceClient.deleteAccount(token.accessToken);
      } else {
        throw new Error("Account deletion not supported for enterprise auth");
      }
    });
  }
  /**
   * Handles profile selection for Enterprise authentication.
   * For non-Enterprise providers, this method returns early without action.
   * For Enterprise providers, it retrieves available profiles and either:
   * - Automatically selects the profile if only one is available
   * - Shows a profile selector UI if multiple profiles are available
   * @param token - The token cache data containing authentication information
   * @throws {UnexpectedIssueError} When profile listing fails or returns an error
   * @returns Promise that resolves when profile handling is complete
   */
  async handleProfiles(token) {
    if (token.provider !== "Enterprise") {
      return;
    }
    const { data: profiles, error } = await vscode.commands.executeCommand(
      "kiro.profiles.listAvailableProfiles",
      { accessToken: token.accessToken }
    );
    if (error) {
      throw new UnexpectedIssueError(error.message);
    }
    if (profiles) {
      if (profiles.length === 1) {
        vscode.commands.executeCommand("kiro.profiles.selectProfile", profiles[0]);
      }
      if (profiles.length > 1) {
        vscode.commands.executeCommand("kiro.profiles.showProfileSelector", { isDismissible: false });
      }
    }
  }
}
const withTimeout = async (awaited, length, errorConstructor = Error) => Promise.race([
  awaited,
  new Promise((_resolve, reject) => setTimeout(() => reject(new errorConstructor()), length))
]);
const REDIRECT_URI_PATH = "/authenticate-success";
const REDIRECT_URI = `kiro://kiro.kiroAgent${REDIRECT_URI_PATH}`;
const REDIRECT_TIMEOUT = 6e5;
class SocialAuthProvider {
  constructor() {
    __publicField(this, "authServiceClient");
    __publicField(this, "_cancelAuth");
    this.authServiceClient = new AuthServiceClient();
  }
  tokenResponseToToken({ accessToken, refreshToken, profileArn, expiresIn }, provider) {
    const now = /* @__PURE__ */ new Date();
    const expiresAt = new Date(now.getTime() + Number(expiresIn) * 1e3).toISOString();
    return { accessToken, refreshToken, profileArn, expiresAt, authMethod: "social", provider };
  }
  /**
   * Handles the OAuth2 authorization code response from the redirect URI
   * @param requestState - The state parameter to validate against CSRF attacks
   * @returns Promise that resolves to the authorization code
   */
  async handleCodeResponse(requestState) {
    let uriHandler;
    return new Promise((resolve, reject) => {
      this._cancelAuth = (err) => {
        this._cancelAuth = void 0;
        uriHandler.dispose();
        reject(err);
      };
      uriHandler = uriEventHandler.onUri((uri) => {
        if (uri.authority !== "kiro.kiroAgent" || uri.path !== REDIRECT_URI_PATH) {
          return;
        }
        try {
          const parameters = new URLSearchParams(uri.query);
          const code = parameters.get("code");
          const state = parameters.get("state");
          if (!code) {
            throw new SSOMissingCodeError();
          }
          if (!state) {
            throw new SSOMissingStateError();
          }
          if (state !== requestState) {
            throw new SSOInvalidStateError();
          }
          resolve(code);
        } catch (error) {
          if (error instanceof Error) {
            reject(error);
            return;
          }
          reject(new UnexpectedIssueError(`SocialAuth: Unknown code response error: ${getUnknownErrorDetails(error)}`));
        } finally {
          this._cancelAuth = void 0;
          uriHandler.dispose();
        }
      });
    });
  }
  /**
   * Authenticates via social auth.
   * @returns Promise that resolves to the token data when authentication is complete
   */
  async authenticate(options) {
    return withSpan(TelemetryNamespace.Auth, "social-provider.authenticate", async (span) => {
      span.setAttribute("authProvider", options.provider);
      if (options.authMethod !== "social") {
        throw new UnexpectedIssueError("SocialAuth: invalid auth method");
      }
      const { invitationCode, provider } = options;
      span.setAttribute("withInvitationCode", !!invitationCode);
      const redirectUri = REDIRECT_URI;
      const state = crypto.randomUUID();
      const codeVerifier = crypto.randomBytes(32).toString("base64url");
      const codeChallenge = crypto.createHash("sha256").update(codeVerifier).digest().toString("base64url");
      await this.authServiceClient.login({ provider, redirectUri, codeChallenge, state });
      const code = await withTimeout(this.handleCodeResponse(state), REDIRECT_TIMEOUT, SSORedirectTimeoutError);
      const response = await this.authServiceClient.createToken({
        code,
        codeVerifier,
        redirectUri,
        invitationCode
      });
      return this.tokenResponseToToken(response, provider);
    });
  }
  /**
   * Cancels a currently ongoing sign-in flow
   */
  cancelAuth() {
    var _a;
    (_a = this._cancelAuth) == null ? void 0 : _a.call(this, new CanceledError("user cancellation"));
  }
  /**
   * Refreshes token granted through social auth
   * @returns Promise that resolves to the refreshed token data
   */
  async refreshToken(token) {
    return withSpan(TelemetryNamespace.Auth, "social-provider.refreshToken", async (span) => {
      span.setAttribute("authProvider", token.provider);
      if (token.authMethod !== "social") {
        throw new UnexpectedIssueError("SocialAuth: invalid auth method");
      }
      const { refreshToken, profileArn, provider } = token;
      try {
        const token2 = await this.authServiceClient.refreshToken({ refreshToken });
        token2.profileArn = profileArn;
        return this.tokenResponseToToken(token2, provider);
      } catch (error) {
        logger.error("Error refreshing token:", error);
        throw error;
      }
    });
  }
  /**
   * Logs the user out of a session generated through social auth
   * @returns Promise that resolves when logout was complete
   */
  async logout(token) {
    return withSpan(TelemetryNamespace.Auth, "social-provider.logout", async (span) => {
      span.setAttribute("authProvider", token.provider);
      if (!token.refreshToken) {
        return;
      }
      return this.authServiceClient.logout({ refreshToken: token.refreshToken });
    });
  }
  /**
   * Deletes the user account using the social auth provider.
   * @param token - The token cache data containing access token
   */
  async deleteAccount(token) {
    return withSpan(TelemetryNamespace.Auth, "social-provider.deleteAccount", async (span) => {
      span.setAttribute("authProvider", token.provider);
      return this.authServiceClient.deleteAccount(token.accessToken);
    });
  }
}
export {
  ClientRegistrationStorage as C,
  IDCAuthProvider as I,
  SocialAuthProvider as S
};
