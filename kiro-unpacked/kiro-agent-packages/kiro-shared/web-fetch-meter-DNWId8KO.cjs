"use strict";
var __defProp = Object.defineProperty;
var __defNormalProp = (obj, key, value) => key in obj ? __defProp(obj, key, { enumerable: true, configurable: true, writable: true, value }) : obj[key] = value;
var __publicField = (obj, key, value) => __defNormalProp(obj, typeof key !== "symbol" ? key + "" : key, value);
const telemetry_definitions_index = require("./telemetry/definitions/index.cjs");
const ChatUIMetrics = new telemetry_definitions_index.MetricReporter(telemetry_definitions_index.TelemetryNamespace.Feature, "chatUI");
function recordChatWebviewEvent(event) {
  try {
    if (event.value) {
      ChatUIMetrics.reportHistogramMetrics({ [event.type]: event.value }, event.dimensions);
      return;
    }
    ChatUIMetrics.reportCountMetrics({ [event.type]: 1 }, event.dimensions);
  } catch {
  }
}
const PowersMetrics = new telemetry_definitions_index.MetricReporter(telemetry_definitions_index.TelemetryNamespace.Feature, "powers");
function recordPowersEvent(event) {
  try {
    PowersMetrics.reportCountMetrics({ [event.type]: 1 }, event.dimensions || {});
  } catch {
  }
}
function recordPowersHistogram(metricName, value, dimensions) {
  try {
    PowersMetrics.reportHistogramMetrics({ [metricName]: value }, dimensions || {});
  } catch {
  }
}
const RemoteToolsMetrics = new telemetry_definitions_index.MetricReporter(telemetry_definitions_index.TelemetryNamespace.Feature, "remote_tools");
function recordRemoteToolsEvent(event) {
  try {
    RemoteToolsMetrics.reportCountMetrics({ [event.type]: 1 }, event.dimensions || {});
  } catch {
  }
}
function recordRemoteToolsHistogram(metricName, value, dimensions) {
  try {
    RemoteToolsMetrics.reportHistogramMetrics({ [metricName]: value }, dimensions || {});
  } catch {
  }
}
class RemoteToolRecorder {
  constructor(toolName, additionalDimensions) {
    __publicField(this, "startTime");
    __publicField(this, "dimensions");
    this.startTime = performance.now();
    this.dimensions = { toolName, ...additionalDimensions };
    recordRemoteToolsEvent({ type: "remoteToolInvoked", dimensions: this.dimensions });
  }
  /**
   * Create a new recorder for a remote tool execution, and record the initial invoke.
   */
  static start(toolName, additionalDimensions) {
    return new RemoteToolRecorder(toolName, additionalDimensions);
  }
  /**
   * Record success metric and duration for a remote tool.
   */
  recordSuccess() {
    const duration = performance.now() - this.startTime;
    recordRemoteToolsEvent({ type: "remoteToolSuccess", dimensions: this.dimensions });
    recordRemoteToolsHistogram("remoteToolDuration", duration, this.dimensions);
  }
  /**
   * Record error metric and duration for a remote tool (invalid input).
   */
  recordError() {
    const duration = performance.now() - this.startTime;
    recordRemoteToolsEvent({ type: "remoteToolError", dimensions: this.dimensions });
    recordRemoteToolsHistogram("remoteToolDuration", duration, this.dimensions);
  }
  /**
   * Record failure metric and duration for a remote tool (internal failure).
   */
  recordFault() {
    const duration = performance.now() - this.startTime;
    recordRemoteToolsEvent({ type: "remoteToolFault", dimensions: this.dimensions });
    recordRemoteToolsHistogram("remoteToolDuration", duration, this.dimensions);
  }
  /**
   * Record rejection metric and duration for a remote tool (user rejected).
   */
  recordRejection() {
    const duration = performance.now() - this.startTime;
    recordRemoteToolsEvent({ type: "remoteToolRejected", dimensions: this.dimensions });
    recordRemoteToolsHistogram("remoteToolDuration", duration, this.dimensions);
    recordRemoteToolsHistogram("userApproval", 0, { ...this.dimensions, action: "reject" });
  }
  /**
   * Record acceptance metric for a remote tool (user accepted).
   */
  recordAcceptance() {
    recordRemoteToolsEvent({ type: "remoteToolAccepted", dimensions: this.dimensions });
    recordRemoteToolsHistogram("userApproval", 1, { ...this.dimensions, action: "accept" });
  }
  /**
   * Record trust metric for a remote tool (user trusted).
   */
  recordTrust() {
    recordRemoteToolsEvent({ type: "remoteToolTrusted", dimensions: this.dimensions });
    recordRemoteToolsHistogram("userApproval", 2, { ...this.dimensions, action: "trust" });
  }
}
const WebFetchMetrics = new telemetry_definitions_index.MetricReporter(telemetry_definitions_index.TelemetryNamespace.Feature, "web_fetch");
function recordWebFetchEvent(event) {
  try {
    WebFetchMetrics.reportCountMetrics({ [event.type]: 1 }, event.dimensions || {});
  } catch {
  }
}
class WebFetchRecorder {
  constructor(baseRecorder) {
    __publicField(this, "baseRecorder");
    __publicField(this, "dimensions");
    __publicField(this, "fetchStartTime");
    this.baseRecorder = baseRecorder;
    this.dimensions = {};
  }
  /**
   * Create a new WebFetch recorder and record the initial invoke.
   */
  static start() {
    const baseRecorder = telemetry_definitions_index.ToolRecorder.start(telemetry_definitions_index.Tool.WebFetch);
    return new WebFetchRecorder(baseRecorder);
  }
  /**
   * Mark the start of the actual fetch operation.
   */
  startFetch() {
    this.fetchStartTime = performance.now();
  }
  /**
   * Record success metric and all web fetch histograms.
   */
  recordToolSuccess(result) {
    if (result) {
      this.baseRecorder.recordHistogram("contentSize", result.contentLength, this.dimensions);
      if (result.truncated) {
        recordWebFetchEvent({
          type: "webFetchContentTruncated",
          dimensions: this.dimensions
        });
      }
      if (result.matchCount !== void 0) {
        recordWebFetchEvent({
          type: "webFetchSelectiveMatches",
          dimensions: { ...this.dimensions, matchCount: result.matchCount.toString() }
        });
        this.baseRecorder.recordHistogram("matchCount", result.matchCount, this.dimensions);
      }
    }
    if (this.fetchStartTime !== void 0) {
      const fetchDuration = performance.now() - this.fetchStartTime;
      this.baseRecorder.recordHistogram("fetchTime", fetchDuration, this.dimensions);
    }
    this.baseRecorder.recordToolSuccess();
  }
  /**
   * Record error metric and duration for the tool.
   */
  recordToolError(error) {
    this.baseRecorder.recordToolError(error);
  }
  /**
   * Record fault metric and duration for the tool.
   */
  recordToolFault(error) {
    this.baseRecorder.recordToolFault(error);
  }
  /**
   * Record the mode used for web fetch.
   */
  recordModeUsed(mode) {
    this.dimensions.mode = mode;
    recordWebFetchEvent({
      type: "webFetchModeUsed",
      dimensions: { mode }
    });
    const modeValue = mode === "full" ? 1 : mode === "truncated" ? 2 : 3;
    this.baseRecorder.recordHistogram("modeUsage", modeValue, { mode });
  }
  /**
   * Record when query parameters are stripped from URL.
   */
  recordUrlCleaned(originalUrl, cleanUrl) {
    const hasQuery = originalUrl !== cleanUrl;
    if (hasQuery) {
      recordWebFetchEvent({
        type: "webFetchUrlCleanedEvent",
        dimensions: { hasQuery: "true" }
      });
    }
  }
  /**
   * Record when an unsafe URL is blocked.
   */
  recordUnsafeUrlBlocked(url) {
    const protocol = new URL(url).protocol;
    recordWebFetchEvent({
      type: "webFetchUnsafeUrlBlocked",
      dimensions: { urlProtocol: protocol }
    });
    this.baseRecorder.recordHistogram("unsafeUrlAttempts", 1, { protocol });
  }
  /**
   * Record when a redirect to unsafe URL is blocked.
   */
  recordRedirectBlocked(originalUrl, redirectUrl) {
    recordWebFetchEvent({
      type: "webFetchRedirectBlocked",
      dimensions: {
        originalProtocol: new URL(originalUrl).protocol,
        redirectProtocol: new URL(redirectUrl).protocol
      }
    });
  }
  /**
   * Record when user accepts a web fetch request.
   */
  recordUserAccepted() {
    recordWebFetchEvent({
      type: "webFetchAccepted",
      dimensions: this.dimensions
    });
    this.baseRecorder.recordHistogram("userApproval", 1, { action: "accept" });
  }
  /**
   * Record when user trusts web fetch (accepts and enables auto-approval).
   */
  recordUserTrusted() {
    recordWebFetchEvent({
      type: "webFetchTrusted",
      dimensions: this.dimensions
    });
    this.baseRecorder.recordHistogram("userApproval", 2, { action: "trust" });
  }
  /**
   * Record when user rejects a web fetch request.
   */
  recordUserRejected() {
    recordWebFetchEvent({
      type: "webFetchRejected",
      dimensions: this.dimensions
    });
    this.baseRecorder.recordHistogram("userApproval", 0, { action: "reject" });
  }
}
exports.RemoteToolRecorder = RemoteToolRecorder;
exports.WebFetchRecorder = WebFetchRecorder;
exports.recordChatWebviewEvent = recordChatWebviewEvent;
exports.recordPowersEvent = recordPowersEvent;
exports.recordPowersHistogram = recordPowersHistogram;
exports.recordRemoteToolsEvent = recordRemoteToolsEvent;
exports.recordRemoteToolsHistogram = recordRemoteToolsHistogram;
exports.recordWebFetchEvent = recordWebFetchEvent;
