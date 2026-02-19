"use strict";
const vscode = require("vscode");
const ignore = require("ignore");

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
const channel = vscode__namespace.window.createOutputChannel("Kiro Logs", {
  log: true
});
const logs = [];

function logLocalLevel(level, message, ...arguments_) {
  const argumentsJoined = arguments_.map((a) => typeof a === "object" ? JSON.stringify(a) : a).join(" ");
  const timestamp = ( /* @__PURE__ */ new Date()).toISOString();
  const logMessage = `[${timestamp}] [${level}] ${message} ${argumentsJoined}`;
  logs.push(logMessage);
}
const logger = {
  trace(message, ...arguments_) {
    channel.trace(message, ...arguments_);
    logLocalLevel("trace", message, ...arguments_);
  },
  debug(message, ...arguments_) {
    channel.debug(message, ...arguments_);
    logLocalLevel("debug", message, ...arguments_);
  },
  info(message, ...arguments_) {
    channel.info(message, ...arguments_);
    logLocalLevel("info", message, ...arguments_);
  },
  warn(message, ...arguments_) {
    channel.warn(message, ...arguments_);
    logLocalLevel("warn", message, ...arguments_);
  },
  error(error, ...arguments_) {
    channel.error(error, ...arguments_);
    logLocalLevel("error", `${error}`, ...arguments_);
  },
  capture() {
    const logsString = logs.join("\n");
    logs.length = 0;
    channel.clear();
    return logsString;
  }
};
const mcpLogsPerServer = /* @__PURE__ */ new Map();
const mcpLogChannel = vscode__namespace.window.createOutputChannel("Kiro - MCP Logs", {
  log: true
});

function storeMCPLogMessage(message, level, serverName, ...arguments_) {
  const argumentsJoined = arguments_.map((a) => typeof a === "object" ? JSON.stringify(a) : a).join(" ");
  const timestamp = ( /* @__PURE__ */ new Date()).toISOString();
  const logServerName = serverName || "KIRO_MCP_DEFAULT";
  const logMessage = `[${timestamp}] [${level}] [${logServerName}] ${message} ${argumentsJoined}`;
  const serverLogs = mcpLogsPerServer.get(logServerName) || [];
  serverLogs.push(logMessage);
  mcpLogsPerServer.set(logServerName, serverLogs);
}
const mcpLogger = {
  trace(message, serverName, ...arguments_) {
    const serverNamePrefix = serverName ? `[${serverName}] ` : "";
    mcpLogChannel.trace(`${serverNamePrefix}${message}`, ...arguments_);
    storeMCPLogMessage(message, "trace", serverName, ...arguments_);
  },
  debug(message, serverName, ...arguments_) {
    const serverNamePrefix = serverName ? `[${serverName}] ` : "";
    mcpLogChannel.debug(`${serverNamePrefix}${message}`, ...arguments_);
    storeMCPLogMessage(message, "debug", serverName, ...arguments_);
  },
  info(message, serverName, ...arguments_) {
    const serverNamePrefix = serverName ? `[${serverName}] ` : "";
    mcpLogChannel.info(`${serverNamePrefix}${message}`, ...arguments_);
    storeMCPLogMessage(message, "info", serverName, ...arguments_);
  },
  warn(message, serverName, ...arguments_) {
    const serverNamePrefix = serverName ? `[${serverName}] ` : "";
    mcpLogChannel.warn(`${serverNamePrefix}${message}`, ...arguments_);
    storeMCPLogMessage(message, "warn", serverName, ...arguments_);
  },
  error(error, serverName, ...arguments_) {
    const serverNamePrefix = serverName ? `[${serverName}] ` : "";
    mcpLogChannel.error(`${serverNamePrefix}${error}`, ...arguments_);
    storeMCPLogMessage(`${error}`, "error", serverName, ...arguments_);
  },
  getLogsForServer(serverName) {
    return mcpLogsPerServer.get(serverName) || [];
  },
  show() {
    mcpLogChannel.show();
  },
  capture() {
    const logsString = Array.from(mcpLogsPerServer.values()).flatMap((it) => it).join("\n");
    mcpLogsPerServer.clear();
    mcpLogChannel.clear();
    return logsString;
  }
};

function isAbortError(error) {
  return error instanceof Error && (error.name.includes("Abort") || error.message.includes("Aborted"));
}

function isBlockedAccessError(error) {
  return error instanceof Error && (error.name.includes("NewUserAccessPausedError") || error.message.includes(
    "Kiro access not available for this account"));
}

function mapUnknownToErrorType(error) {
  const errorType = error instanceof Error ? error.name : "UnknownError";
  const isAbort = isAbortError(error);
  return isAbort ? "AbortedError" : errorType;
}
class TrustedError extends Error {}
const DEFAULT_IGNORE_FILETYPES = [
  "*.DS_Store",
  "*-lock.json",
  "*.lock",
  "*.log",
  "*.ttf",
  "*.png",
  "*.jpg",
  "*.jpeg",
  "*.gif",
  "*.mp4",
  "*.svg",
  "*.ico",
  "*.pdf",
  "*.zip",
  "*.gz",
  "*.tar",
  "*.dmg",
  "*.tgz",
  "*.rar",
  "*.7z",
  "*.exe",
  "*.dll",
  "*.obj",
  "*.o",
  "*.o.d",
  "*.a",
  "*.lib",
  "*.so",
  "*.dylib",
  "*.ncb",
  "*.sdf",
  "*.woff",
  "*.woff2",
  "*.eot",
  "*.cur",
  "*.avi",
  "*.mpg",
  "*.mpeg",
  "*.mov",
  "*.mp3",
  "*.mp4",
  "*.mkv",
  "*.mkv",
  "*.webm",
  "*.jar",
  "*.onnx",
  "*.parquet",
  "*.pqt",
  "*.wav",
  "*.webp",
  "*.db",
  "*.sqlite",
  "*.wasm",
  "*.plist",
  "*.profraw",
  "*.gcda",
  "*.gcno",
  "go.sum",
  "*.env",
  "*.gitignore",
  "*.gitkeep",
  "*.continueignore",
  "*.kiroignore",
  "*.cursorignore",
  "config.json",
  "*.csv",
  "*.uasset",
  "*.pdb",
  "*.bin",
  "*.chat",
  "*.swp",
  "*.pag",
  "*.jsonl",
  "*.eslintcache",
  "*.ts.map",
  "*.js.map",
  "*.d.ts"
  // "*.prompt", // can be incredibly confusing for the LLM to have another set of instructions injected into the prompt
];
const DEFAULT_IGNORE_DIRS = [
  ".git/",
  ".svn/",
  ".vscode/",
  ".idea/",
  ".vs/",
  "venv/",
  ".venv/",
  "env/",
  ".env/",
  "node_modules/",
  "dist/",
  "build/",
  "Build/",
  "target/",
  "out/",
  "bin/",
  ".pytest_cache/",
  ".vscode-test/",
  ".continue/",
  "__pycache__/",
  "site-packages/",
  ".gradle/",
  ".mvn/",
  ".cache/",
  "gems/",
  "vendor/",
  ".next/",
  ".kiro/"
];
const defaultIgnoreFile = ignore().add(DEFAULT_IGNORE_FILETYPES);
const defaultIgnoreDir = ignore().add(DEFAULT_IGNORE_DIRS);
const DEFAULT_IGNORE = DEFAULT_IGNORE_FILETYPES.join("\n") + "\n" + DEFAULT_IGNORE_DIRS.join("\n");

function gitIgnoreArrayFromFile(file) {
  return file.split(/\r?\n/).map((l) => l.trim()).filter((l) => !/^#|^$/.test(l));
}
exports.DEFAULT_IGNORE = DEFAULT_IGNORE;
exports.DEFAULT_IGNORE_DIRS = DEFAULT_IGNORE_DIRS;
exports.DEFAULT_IGNORE_FILETYPES = DEFAULT_IGNORE_FILETYPES;
exports.TrustedError = TrustedError;
exports.defaultIgnoreDir = defaultIgnoreDir;
exports.defaultIgnoreFile = defaultIgnoreFile;
exports.gitIgnoreArrayFromFile = gitIgnoreArrayFromFile;
exports.isAbortError = isAbortError;
exports.isBlockedAccessError = isBlockedAccessError;
exports.logger = logger;
exports.mapUnknownToErrorType = mapUnknownToErrorType;
exports.mcpLogger = mcpLogger;