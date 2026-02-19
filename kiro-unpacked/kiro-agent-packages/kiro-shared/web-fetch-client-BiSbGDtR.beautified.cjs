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
const ignore = require("./ignore-D645GLpP.cjs");
const axios = require("axios");
const axiosRetry = require("axios-retry").default;

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

function addPrivacyHeadersMiddleware(client, clientName = "CodeWhisperer") {
  const contentCollectionEnabled = vscode__namespace.workspace.getConfiguration("telemetry").get(
    "dataSharing.contentCollectionForServiceImprovement", false);
  if (!contentCollectionEnabled) {
    ignore.logger.debug(`${clientName}: content collection is disabled, setting x-amzn-codewhisperer-optout to true`);
    const middleware = (next) => async (args) => {
      const requestArgs = args;
      requestArgs.request.headers = {
        ...requestArgs.request.headers,
        "x-amzn-codewhisperer-optout": "true"
      };
      return next(args);
    };
    const clientWithMiddleware = client;
    clientWithMiddleware.middlewareStack.add(middleware, {
      step: "build"
    });
  }
}

function addAgentModeHeadersMiddleware(client, agentMode) {
  const middleware = (next) => async (args) => {
    const requestArgs = args;
    requestArgs.request.headers = {
      ...requestArgs.request.headers,
      "x-amzn-kiro-agent-mode": agentMode
    };
    return next(args);
  };
  const clientWithMiddleware = client;
  clientWithMiddleware.middlewareStack.add(middleware, {
    step: "build"
  });
}
async function updateResolvedIDESetting(section, setting, value, scope) {
  var _a;
  const settings = vscode__namespace.workspace.getConfiguration(section, scope);
  if (((_a = settings.inspect(setting)) == null ? void 0 : _a.workspaceValue) !== void 0) {
    await settings.update(setting, value, vscode__namespace.ConfigurationTarget.Workspace);
  } else {
    await settings.update(setting, value, vscode__namespace.ConfigurationTarget.Global);
  }
}
const FETCH_TIMEOUT_MS = 3e4;
const MAX_RETRY_ATTEMPTS = 1;
const MAX_CONTENT_SIZE = 10 * 1024 * 1024;
const TRUNCATED_CONTENT_SIZE = 8 * 1024;
class WebFetchClient {
  constructor(options = {}) {
    __publicField(this, "client");
    const {
      timeout = FETCH_TIMEOUT_MS,
        maxRetries = MAX_RETRY_ATTEMPTS,
        maxContentSize = MAX_CONTENT_SIZE,
        userAgent = "KiroIDE"
    } = options;
    this.client = axios.create({
      timeout,
      maxRedirects: 5,
      maxContentLength: maxContentSize,
      maxBodyLength: maxContentSize,
      validateStatus: (status) => status >= 200 && status < 300,
      headers: {
        "User-Agent": userAgent,
        Accept: "text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8",
        "Accept-Encoding": "gzip, deflate"
      },
      decompress: true
    });
    axiosRetry(this.client, {
      retries: maxRetries,
      retryCondition: (error) => {
        if (error.response && error.response.status >= 400 && error.response.status < 500) {
          return false;
        }
        return axiosRetry.isNetworkOrIdempotentRequestError(error) || error.response !== void 0 && error
          .response.status >= 500 && error.response.status < 600;
      },
      // eslint-disable-next-line @typescript-eslint/unbound-method
      retryDelay: axiosRetry.exponentialDelay,
      onRetry: (retryCount, error) => {
        var _a;
        ignore.logger.warn(
          `[WebFetchClient] Retry attempt ${retryCount} for ${(_a = error.config) == null ? void 0 : _a.url}: ${error.message}`
          );
      }
    });
  }
  /**
   * Fetch HTML content from a URL
   */
  async fetchHtml(url) {
    var _a, _b;
    try {
      const response = await this.client.get(url, {
        responseType: "text"
      });
      const finalUrl = ((_b = (_a = response.request) == null ? void 0 : _a.res) == null ? void 0 : _b.responseUrl) ||
        response.config.url || url;
      const contentType = String(response.headers["content-type"] || "");
      return {
        data: response.data,
        statusCode: response.status,
        contentType,
        finalUrl
      };
    } catch (error) {
      if (axios.isAxiosError(error)) {
        const axiosError = error;
        if (axiosError.code === "ECONNABORTED" || axiosError.code === "ETIMEDOUT") {
          throw new Error(`Request timeout after ${this.client.defaults.timeout}ms`);
        }
        if (axiosError.code === "ERR_BAD_REQUEST" && axiosError.message.includes("maxContentLength")) {
          throw new Error(`Content too large: exceeds maximum of ${this.client.defaults.maxContentLength} bytes`);
        }
        if (axiosError.response) {
          throw new Error(`HTTP ${axiosError.response.status}: ${axiosError.response.statusText}`);
        }
        throw new Error(`Network error: ${axiosError.message}`);
      }
      throw error;
    }
  }
  /**
   * Get the underlying axios instance for advanced usage
   */
  getAxiosInstance() {
    return this.client;
  }
}
exports.FETCH_TIMEOUT_MS = FETCH_TIMEOUT_MS;
exports.MAX_CONTENT_SIZE = MAX_CONTENT_SIZE;
exports.MAX_RETRY_ATTEMPTS = MAX_RETRY_ATTEMPTS;
exports.TRUNCATED_CONTENT_SIZE = TRUNCATED_CONTENT_SIZE;
exports.WebFetchClient = WebFetchClient;
exports.addAgentModeHeadersMiddleware = addAgentModeHeadersMiddleware;
exports.addPrivacyHeadersMiddleware = addPrivacyHeadersMiddleware;
exports.updateResolvedIDESetting = updateResolvedIDESetting;