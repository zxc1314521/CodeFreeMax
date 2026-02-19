var __defProp = Object.defineProperty;
var __defNormalProp = (obj, key, value) => key in obj ? __defProp(obj, key, {
  enumerable: true,
  configurable: true,
  writable: true,
  value
}) : obj[key] = value;
var __publicField = (obj, key, value) => __defNormalProp(obj, typeof key !== "symbol" ? key + "" : key, value);
import {
  OTLPMetricExporter
} from "@opentelemetry/exporter-metrics-otlp-http";
import {
  OTLPTraceExporter
} from "@opentelemetry/exporter-trace-otlp-http";
import {
  AWSXRayIdGenerator
} from "@opentelemetry/id-generator-aws-xray";
import {
  AWSXRayPropagator
} from "@opentelemetry/propagator-aws-xray";
import {
  Resource
} from "@opentelemetry/resources";
import {
  AggregationTemporality,
  PeriodicExportingMetricReader,
  MeterProvider,
  View,
  ExponentialHistogramAggregation,
  InstrumentType
} from "@opentelemetry/sdk-metrics";
import {
  NodeSDK
} from "@opentelemetry/sdk-node";
import {
  BatchSpanProcessor
} from "@opentelemetry/sdk-trace-base";
import {
  propagation,
  metrics,
  context,
  trace,
  SpanStatusCode
} from "@opentelemetry/api";
import {
  ATTR_SERVICE_VERSION,
  ATTR_SERVICE_NAME
} from "@opentelemetry/semantic-conventions";
import * as vscode from "vscode";
import * as semver from "semver";
import {
  machineIdSync
} from "node-machine-id";
import {
  l as logger,
  b as mapUnknownToErrorType,
  i as isAbortError,
  a as isBlockedAccessError
} from "../../ignore-B7xGFdAM.js";
import "path";
import * as os from "os";
import "fs";
import "axios";
import "axios-retry";
var GenerationMode;
(function(GenerationMode2) {
  GenerationMode2["RequirementsFirst"] = "requirements-first";
  GenerationMode2["DesignFirst"] = "design-first";
})(GenerationMode || (GenerationMode = {}));
var IDEListenableEvent;
(function(IDEListenableEvent2) {
  IDEListenableEvent2["FileEdited"] = "fileEdited";
  IDEListenableEvent2["FileCreated"] = "fileCreated";
  IDEListenableEvent2["FileDeleted"] = "fileDeleted";
  IDEListenableEvent2["UserTriggered"] = "userTriggered";
  IDEListenableEvent2["UserPrompt"] = "promptSubmit";
  IDEListenableEvent2["AgentStop"] = "agentStop";
})(IDEListenableEvent || (IDEListenableEvent = {}));
var HookActionEvent;
(function(HookActionEvent2) {
  HookActionEvent2["AskAgent"] = "askAgent";
  HookActionEvent2["RunCommand"] = "runCommand";
})(HookActionEvent || (HookActionEvent = {}));
var ConfigKey;
(function(ConfigKey2) {
  ConfigKey2["DevMode"] = "enableDevMode";
  ConfigKey2["TrustedCommands"] = "trustedCommands";
  ConfigKey2["CommandDenylist"] = "commandDenylist";
  ConfigKey2["AutoApproveAgentCommands"] = "autoApproveAgentCommands";
  ConfigKey2["ConfigureMCP"] = "configureMCP";
  ConfigKey2["ExecuteBashTimeoutMs"] = "executeBashTimeoutMs";
  ConfigKey2["EnableCodebaseIndex"] = "enableCodebaseIndex";
  ConfigKey2["EnableRepositoryMapIndex"] = "enableRepositoryMapIndex";
  ConfigKey2["TrustedTools"] = "trustedTools";
})(ConfigKey || (ConfigKey = {}));
({
  [ConfigKey.DevMode]: false,
  [ConfigKey.TrustedCommands]: [],
  [ConfigKey.CommandDenylist]: [],
  [ConfigKey.AutoApproveAgentCommands]: [],
  [ConfigKey.ConfigureMCP]: "Disabled",
  [ConfigKey.ExecuteBashTimeoutMs]: void 0,
  [ConfigKey.EnableCodebaseIndex]: false,
  [ConfigKey.EnableRepositoryMapIndex]: false,
  [ConfigKey.TrustedTools]: []
});
var ConfigNamespace;
(function(ConfigNamespace2) {
  ConfigNamespace2["Extension"] = "kiroAgent";
  ConfigNamespace2["Test"] = "kiroAgent.test";
})(ConfigNamespace || (ConfigNamespace = {}));
var ExecutionStatus;
(function(ExecutionStatus2) {
  ExecutionStatus2["Queued"] = "Queued";
  ExecutionStatus2["InProgress"] = "InProgress";
  ExecutionStatus2["Paused"] = "Paused";
  ExecutionStatus2["NeedAction"] = "NeedAction";
  ExecutionStatus2["Success"] = "Success";
  ExecutionStatus2["Failed"] = "Failed";
  ExecutionStatus2["Canceled"] = "Canceled";
  ExecutionStatus2["Yielded"] = "Yielded";
})(ExecutionStatus || (ExecutionStatus = {}));
var ExecutionAssignment;
(function(ExecutionAssignment2) {
  ExecutionAssignment2["Queued"] = "Queued";
  ExecutionAssignment2["Active"] = "Active";
  ExecutionAssignment2["History"] = "History";
})(ExecutionAssignment || (ExecutionAssignment = {}));
var ChangeType;
(function(ChangeType2) {
  ChangeType2["Code"] = "Code";
})(ChangeType || (ChangeType = {}));
var OperationStatus;
(function(OperationStatus2) {
  OperationStatus2["PendingAction"] = "PendingAction";
  OperationStatus2["Running"] = "Running";
  OperationStatus2["Success"] = "Success";
  OperationStatus2["Error"] = "Error";
  OperationStatus2["Accepted"] = "Accepted";
  OperationStatus2["Rejected"] = "Rejected";
  OperationStatus2["Canceled"] = "Canceled";
  OperationStatus2["HandledError"] = "HandledError";
})(OperationStatus || (OperationStatus = {}));
var AutonomyMode;
(function(AutonomyMode2) {
  AutonomyMode2["Autopilot"] = "Autopilot";
  AutonomyMode2["Supervised"] = "Supervised";
})(AutonomyMode || (AutonomyMode = {}));
var TaskStatus;
(function(TaskStatus2) {
  TaskStatus2["NotStarted"] = "not_started";
  TaskStatus2["InProgress"] = "in_progress";
  TaskStatus2["Completed"] = "completed";
})(TaskStatus || (TaskStatus = {}));
var TelemetryNamespace;
(function(TelemetryNamespace2) {
  TelemetryNamespace2["Application"] = "kiro.application";
  TelemetryNamespace2["Feature"] = "kiro.feature";
  TelemetryNamespace2["Continue"] = "kiro.continue";
  TelemetryNamespace2["Agent"] = "kiro.agent";
  TelemetryNamespace2["Tool"] = "kiro.tool";
  TelemetryNamespace2["Parser"] = "kiro.parser";
  TelemetryNamespace2["Onboarding"] = "kiro.onboarding";
  TelemetryNamespace2["Webview"] = "kiro.webview";
  TelemetryNamespace2["Auth"] = "kiro.auth";
  TelemetryNamespace2["Billing"] = "kiro.billing";
  TelemetryNamespace2["Profiles"] = "kiro.profiles";
  TelemetryNamespace2["RemoteTools"] = "kiro.remote-tools";
})(TelemetryNamespace || (TelemetryNamespace = {}));
var JourneyId;
(function(JourneyId2) {
  JourneyId2["Onboarding"] = "onboarding";
})(JourneyId || (JourneyId = {}));
var TelemetryAttributes;
(function(TelemetryAttributes2) {
  TelemetryAttributes2["RequestId"] = "requestId";
  TelemetryAttributes2["ConversationId"] = "conversationId";
  TelemetryAttributes2["ExecutionId"] = "executionId";
  TelemetryAttributes2["ModelId"] = "ModelIdentifier";
  TelemetryAttributes2["XRayTraceId"] = "AWS-XRAY-TRACE-ID";
})(TelemetryAttributes || (TelemetryAttributes = {}));
var AuthError;
(function(AuthError2) {
  AuthError2["INVALID_TOKEN"] = "INVALID_TOKEN";
  AuthError2["NETWORK_ERROR"] = "NETWORK_ERROR";
  AuthError2["UNEXPECTED_ERROR"] = "UNEXPECTED_ERROR";
})(AuthError || (AuthError = {}));
var PowersErrorName;
(function(PowersErrorName2) {
  PowersErrorName2["InvalidPowerError"] = "InvalidPowerError";
  PowersErrorName2["McpJsonNotFoundError"] = "McpJsonNotFoundError";
  PowersErrorName2["McpJsonFetchError"] = "McpJsonFetchError";
  PowersErrorName2["PowerAlreadyInstalledError"] = "PowerAlreadyInstalledError";
  PowersErrorName2["PowerNotFoundError"] = "PowerNotFoundError";
  PowersErrorName2["PowerNotInstalledError"] = "PowerNotInstalledError";
  PowersErrorName2["PowerRegistryLoadError"] = "PowerRegistryLoadError";
  PowersErrorName2["PowerRegistrySaveError"] = "PowerRegistrySaveError";
  PowersErrorName2["PowerValidationError"] = "PowerValidationError";
  PowersErrorName2["UnknownError"] = "UnknownError";
})(PowersErrorName || (PowersErrorName = {}));
class BaggageSpanProcessor {
  constructor(options) {
    __publicField(this, "keys");
    this.keys = options.keys;
  }
  /**
   * Called when a span is started
   * @param span The span that was started
   * @param parentContext The parent context, if any
   */
  onStart(span, parentContext) {
    const baggage = propagation.getBaggage(parentContext);
    if (!baggage) {
      return;
    }
    this.keys.forEach((key) => {
      const entry = baggage.getEntry(key);
      if (entry) {
        span.setAttribute(key, entry.value);
      }
    });
  }
  /**
   * Called when a span ends
   * @param _span The span that ended
   */
  onEnd(_span) {}
  /**
   * Shuts down the processor
   */
  shutdown() {
    return Promise.resolve();
  }
  /**
   * Forces the processor to flush any pending spans
   */
  forceFlush() {
    return Promise.resolve();
  }
}
var MetricNamespace = /* @__PURE__ */ ((MetricNamespace2) => {
  MetricNamespace2["Onboarding"] = "kiro.onboarding";
  MetricNamespace2["Auth"] = "kiro.auth";
  MetricNamespace2["Session"] = "kiro.session";
  MetricNamespace2["Feature"] = "kiro.feature";
  MetricNamespace2["User"] = "kiro.user";
  MetricNamespace2["Tool"] = "kiro.tool";
  MetricNamespace2["Operation"] = "kiro.operation";
  MetricNamespace2["Periodic"] = "kiro.periodic";
  return MetricNamespace2;
})(MetricNamespace || {});
const DEFAULT_MACHINE_ID = "UNDETERMINED_MACHINE_ID";

function getMachineId() {
  try {
    return machineIdSync();
  } catch (_e) {
    return vscode.env.machineId || DEFAULT_MACHINE_ID;
  }
}
const MACHINE_ID = getMachineId();
const semanticVersion$1 = semver.parse(vscode.kiroVersion ?? "0.0.0");
const KIRO_CLIENT_VERSION =
  `${semanticVersion$1 == null ? void 0 : semanticVersion$1.major}.${semanticVersion$1 == null ? void 0 : semanticVersion$1.minor}`;

function userAttributes() {
  return {
    KiroClientVersion: KIRO_CLIENT_VERSION,
    machineId: MACHINE_ID
  };
}

function getUserActivityMetricAttributes(activity) {
  const attributes = {
    ...userAttributes(),
    Activity: activity
  };
  return attributes;
}

function getToolMetricAttributes(tool) {
  const attributes = {
    ...userAttributes(),
    Tool: tool
  };
  return attributes;
}
let hasOpenedIDECount;
let startedOnboardingAuthFlowCount;
let failedOnboardingAuthFlowCount;
let canceledOnboardingAuthFlowCount;
let abandonedOnboardingAuthFlowCount;
let finishedOnboardingAuthFlowCount;
let badUserInputOnboardingAuthFlowCount;

function initializeCounters$3() {
  const onboardingMeter = metrics.getMeterProvider().getMeter(MetricNamespace.Onboarding);
  hasOpenedIDECount = onboardingMeter.createCounter("opened_IDE_count", {
    description: "Counts the number of times the IDE has been opened",
    unit: "number"
  });
  startedOnboardingAuthFlowCount = onboardingMeter.createCounter("started_auth_count", {
    description: "Counts the number of times the IDE has started the auth onboarding flow",
    unit: "number"
  });
  failedOnboardingAuthFlowCount = onboardingMeter.createCounter("failed_auth_count", {
    description: "Counts the number of times the IDE has failed the onboarding auth flow",
    unit: "number"
  });
  canceledOnboardingAuthFlowCount = onboardingMeter.createCounter("canceled_auth_count", {
    description: "Counts the number of times a user canceled the onboarding auth flow",
    unit: "number"
  });
  abandonedOnboardingAuthFlowCount = onboardingMeter.createCounter("abandoned_auth_count", {
    description: "Counts the number of times a user abandons the onboarding auth flow (timeout)",
    unit: "number"
  });
  finishedOnboardingAuthFlowCount = onboardingMeter.createCounter("finished_auth_count", {
    description: "Counts the number of times the IDE has finished the onboarding auth flow",
    unit: "number"
  });
  badUserInputOnboardingAuthFlowCount = onboardingMeter.createCounter("bad_user_input_count", {
    description: "Counts the number of times bad user input was encountered during onboarding",
    unit: "number"
  });
}

function recordOnboardingStep(type) {
  try {
    if (!isInitialized()) {
      return;
    }
    const activity = "onboarding";
    const attributes = getUserActivityMetricAttributes(activity);
    switch (type) {
      case "opened-IDE":
        hasOpenedIDECount.add(1, attributes);
        break;
      case "started-login":
        startedOnboardingAuthFlowCount.add(1, attributes);
        break;
      case "failed-login":
        failedOnboardingAuthFlowCount.add(1, attributes);
        break;
      case "canceled-login":
        canceledOnboardingAuthFlowCount.add(1, attributes);
        break;
      case "abandoned-login":
        abandonedOnboardingAuthFlowCount.add(1, attributes);
        break;
      case "finished-login":
        finishedOnboardingAuthFlowCount.add(1, attributes);
        break;
      case "bad-user-input":
        badUserInputOnboardingAuthFlowCount.add(1, attributes);
        break;
    }
  } catch (e) {
    logger.error("Failed to record feature latency: ", e);
  }
}
let githubLoginCount;
let googleLoginCount;
let enterpriseIdcLoginCount;
let internalIdcLoginCount;
let builderIdLoginCount;

function initializeCounters$2() {
  const authTypeMeter = metrics.getMeterProvider().getMeter(MetricNamespace.User);
  githubLoginCount = authTypeMeter.createCounter("github_login_count", {
    description: "Counts the number of times users have logged in with GitHub",
    unit: "number"
  });
  googleLoginCount = authTypeMeter.createCounter("google_login_count", {
    description: "Counts the number of times users have logged in with Google",
    unit: "number"
  });
  enterpriseIdcLoginCount = authTypeMeter.createCounter("enterprise_idc_login_count", {
    description: "Counts the number of times users have logged in with IdC",
    unit: "number"
  });
  internalIdcLoginCount = authTypeMeter.createCounter("idc_internal_login_count", {
    description: "Counts the number of times users have logged in with IdC",
    unit: "number"
  });
  builderIdLoginCount = authTypeMeter.createCounter("builder_id_login_count", {
    description: "Counts the number of times users have logged in with Builder ID",
    unit: "number"
  });
}

function recordAuthFromSource(source) {
  try {
    if (!isInitialized()) {
      return;
    }
    const activity = "login";
    const attributes = getUserActivityMetricAttributes(activity);
    if (source.authMethod == "social") {
      switch (source.provider) {
        case "Google":
          googleLoginCount.add(1, attributes);
          break;
        case "Github":
          githubLoginCount.add(1, attributes);
          break;
      }
    } else if (source.authMethod == "IdC") {
      switch (source.provider) {
        case "BuilderId":
          builderIdLoginCount.add(1, attributes);
          break;
        case "Enterprise":
          enterpriseIdcLoginCount.add(1, attributes);
          break;
        case "Internal":
          internalIdcLoginCount.add(1, attributes);
          break;
      }
    }
  } catch (e) {
    logger.error("Failed to record auth login metrics: ", e);
  }
}
class ContextPropagation {
  /**
   * Gets a context value from the current context
   * @param key The key for the context value
   * @returns The value or undefined if not found
   */
  static getContextValue(key) {
    const baggage = propagation.getBaggage(context.active());
    if (!baggage) {
      return void 0;
    }
    const entry = baggage.getEntry(key);
    return entry == null ? void 0 : entry.value;
  }
  /**
   * Executes a function with the given context values
   * @param contextValues The context values to set
   * @param fn The function to execute
   * @returns The result of the function
   */
  static withContextValues(contextValues, fn) {
    const baggage = propagation.getBaggage(context.active()) || propagation.createBaggage();
    let updatedBaggage = baggage;
    for (const [key, value] of Object.entries(contextValues)) {
      updatedBaggage = updatedBaggage.setEntry(key, {
        value
      });
    }
    const updatedContext = propagation.setBaggage(context.active(), updatedBaggage);
    return context.with(updatedContext, () => {
      const currentSpan = trace.getActiveSpan();
      if (currentSpan) {
        for (const [key, value] of Object.entries(contextValues)) {
          currentSpan.setAttribute(key, value);
        }
      }
      return fn();
    });
  }
  /**
   * Creates attributes object with all current context values
   * @returns Attributes object with context values and additional attributes
   */
  static getTelemetryAttributes() {
    const attributes = {};
    const baggage = propagation.getBaggage(context.active());
    if (baggage) {
      baggage.getAllEntries().forEach(([key, entry]) => {
        if (Object.values(TelemetryAttributes).includes(key)) {
          attributes[key] = entry.value;
        }
      });
    }
    const activeSpan = trace.getActiveSpan();
    if (activeSpan) {
      attributes[TelemetryAttributes.XRayTraceId] =
        `${activeSpan.spanContext().traceId}@${activeSpan.spanContext().spanId}`;
    }
    return attributes;
  }
}

function wrapCallback(props) {
  return function(...args) {
    var _a, _b, _c, _d;
    let isPromise = false;
    const startTime = performance.now();
    try {
      (_a = props.before) == null ? void 0 : _a.call(props);
      const result = props.callback.apply(this, args);
      if (result instanceof Promise) {
        isPromise = true;
        return result.then((result2) => {
          var _a2;
          (_a2 = props.success) == null ? void 0 : _a2.call(props);
          return result2;
        }).catch((error) => {
          var _a2;
          (_a2 = props.failure) == null ? void 0 : _a2.call(props, error);
          throw error;
        }).finally(() => {
          var _a2;
          (_a2 = props.after) == null ? void 0 : _a2.call(props, performance.now() - startTime);
        });
      }
      (_b = props.success) == null ? void 0 : _b.call(props);
      return result;
    } catch (error) {
      (_c = props.failure) == null ? void 0 : _c.call(props, error);
      throw error;
    } finally {
      if (!isPromise) {
        (_d = props.after) == null ? void 0 : _d.call(props, performance.now() - startTime);
      }
    }
  };
}
const PERIODIC_RATE = 1e3 * 60 * 15;
const _MetricReporter = class _MetricReporter {
  constructor(namespace, scope) {
    __publicField(this, "namespace");
    __publicField(this, "scope");
    this.namespace = namespace;
    this.scope = scope;
  }
  extendScope(value) {
    return this.scope ? `${this.scope}.${value}` : value;
  }
  static toNumber(value) {
    if (typeof value === "boolean") {
      return value ? 1 : 0;
    }
    return value;
  }
  getOperationTrackers(metricName, errorType) {
    const completeName = this.extendScope(metricName);
    const meter = metrics.getMeterProvider().getMeter(this.namespace);
    return {
      abort: meter.createCounter(`${completeName}.abort`, {
        unit: "number"
      }),
      abandon: meter.createCounter(`${completeName}.abandon`, {
        unit: "number"
      }),
      badInput: meter.createCounter(`${completeName}.badInput`, {
        unit: "number"
      }),
      unauthorized: meter.createCounter(`${completeName}.unauthorized`, {
        unit: "number"
      }),
      count: meter.createCounter(`${completeName}.count`, {
        unit: "number"
      }),
      failure: meter.createCounter(`${completeName}.failure`, {
        unit: "number"
      }),
      blocked: meter.createCounter(`${completeName}.blocked`, {
        unit: "number"
      }),
      environmentIssue: meter.createCounter(`${completeName}.environmentIssue`, {
        unit: "number"
      }),
      errorType: meter.createCounter(`${completeName}.errorType.${errorType}`, {
        unit: "number"
      }),
      success: meter.createCounter(`${completeName}.success`, {
        unit: "number"
      }),
      latency: meter.createHistogram(`${completeName}.latency`, {
        unit: "ms"
      })
    };
  }
  static async handlePeriodicReporters() {
    const reporter = metrics.getMeterProvider().getMeter(MetricNamespace.Periodic);
    for (const [trackerName, handler] of this.periodicReporters) {
      const report = await handler();
      for (const metricName of Object.keys(report)) {
        const attributes = {
          ...DefaultAttributes,
          Periodic: trackerName
        };
        const fullName = `${trackerName}.${metricName}`;
        const value = this.toNumber(report[metricName]);
        if (value === void 0) {
          continue;
        }
        reporter.createHistogram(fullName, {
          unit: "number"
        }).record(value, attributes);
      }
    }
  }
  /**
   * Start the periodic metric reporter
   */
  static startPeriodicReporterLoop() {
    if (this.periodicReporterTimeout) {
      clearInterval(this.periodicReporterTimeout);
    }
    this.periodicReporterTimeout = setInterval(() => void this.handlePeriodicReporters(), PERIODIC_RATE);
  }
  /**
   * Reports metrics under a given scope with a histogram reporter
   */
  reportHistogramMetrics(metricReport, dimensions = {}) {
    const reporter = metrics.getMeterProvider().getMeter(this.namespace);
    const attributes = {
      ...DefaultAttributes,
      Operation: this.scope,
      ...dimensions,
      ...ContextPropagation.getTelemetryAttributes()
    };
    for (const metricName of Object.keys(metricReport)) {
      const fullName = this.extendScope(metricName);
      const value = _MetricReporter.toNumber(metricReport[metricName]);
      if (value === void 0) {
        continue;
      }
      reporter.createHistogram(fullName).record(value, attributes);
    }
  }
  /**
   * Reports metrics under a given scope with a counter reporter
   */
  reportCountMetrics(metricReport, dimensions = {}) {
    const reporter = metrics.getMeterProvider().getMeter(this.namespace);
    const attributes = {
      ...DefaultAttributes,
      Operation: this.scope,
      ...ContextPropagation.getTelemetryAttributes(),
      ...dimensions
    };
    for (const metricName of Object.keys(metricReport)) {
      const fullName = this.extendScope(metricName);
      const value = _MetricReporter.toNumber(metricReport[metricName]);
      if (value === void 0) {
        continue;
      }
      reporter.createCounter(fullName).add(value, attributes);
    }
  }
  /**
   * Wraps a function in metrics, creating a new function which will emit the given metrics
   */
  wrapMetrics(operationName, fn) {
    const baseAttributes = {
      ...DefaultAttributes,
      Operation: operationName
    };
    return wrapCallback({
      callback: fn,
      before: () => {
        const attributes = {
          ...baseAttributes,
          ...ContextPropagation.getTelemetryAttributes()
        };
        this.getOperationTrackers(operationName).count.add(1, attributes);
      },
      success: () => {
        const attributes = {
          ...baseAttributes,
          ...ContextPropagation.getTelemetryAttributes()
        };
        this.getOperationTrackers(operationName).success.add(1, attributes);
      },
      failure: (error) => {
        const errorType = mapUnknownToErrorType(error);
        const tracker = this.getOperationTrackers(operationName, errorType);
        const attributes = {
          ...baseAttributes,
          ...ContextPropagation.getTelemetryAttributes()
        };
        const isAbort = isAbortError(error);
        const isBlocked = isBlockedAccessError(error);
        if (isAbort) {
          tracker.abort.add(1, {
            ...attributes,
            errorType
          });
          tracker.blocked.add(0, {
            ...attributes,
            errorType
          });
          tracker.failure.add(0, {
            ...attributes,
            errorType
          });
        } else if (isBlocked) {
          tracker.abort.add(0, {
            ...attributes,
            errorType
          });
          tracker.blocked.add(1, {
            ...attributes,
            errorType
          });
          tracker.failure.add(0, {
            ...attributes,
            errorType
          });
        } else {
          tracker.abort.add(0, {
            ...attributes,
            errorType
          });
          tracker.blocked.add(0, {
            ...attributes,
            errorType
          });
          tracker.failure.add(1, {
            ...attributes,
            errorType
          });
        }
        tracker.errorType.add(1, {
          ...attributes,
          errorType
        });
        tracker.success.add(0, attributes);
      },
      after: (duration) => {
        const attributes = {
          ...baseAttributes,
          ...ContextPropagation.getTelemetryAttributes()
        };
        this.getOperationTrackers(operationName).latency.record(duration, attributes);
      }
    });
  }
  /**
   * Calls a function with metrics directly
   */
  callWithMetrics(operationName, fn) {
    return this.wrapMetrics(operationName, fn)();
  }
  /**
   * Sets up a periodic metric reporter with a given id
   */
  periodicallyCaptureMetrics(tracker) {
    _MetricReporter.periodicReporters.set(this.scope || "default", tracker);
  }
  /**
   * Force the periodic metrics capture to run
   */
  forcePeriodicCapture() {
    void _MetricReporter.handlePeriodicReporters();
  }
  /**
   * Decorator to handle adding metrics to a function
   */
  Metric(operationName) {
    const wrapper = this.wrapMetrics.bind(this);
    return function(_, propertyKey, descriptor) {
      const original = descriptor.value;
      const functionName = typeof propertyKey === "string" ? propertyKey : String(propertyKey);
      const metricName = operationName || functionName;
      const newFunction = wrapper(metricName, original);
      descriptor.value = newFunction;
    };
  }
  /**
   * Wraps a function in a trace, creating a new function which will emit x-ray traces
   */
  wrapTrace(traceName, fn, getAdditionalDimensions) {
    const baseAttributes = {
      ...DefaultAttributes,
      Operation: traceName
    };
    const fullTraceName = `${this.scope}.${traceName}`;
    const tracer = trace.getTracer(TelemetryNamespace.Application, APPLICATION_VERSION);
    const trackers = this.getOperationTrackers.bind(this);
    return function(...args) {
      const bound = () => fn.apply(this, args);
      return tracer.startActiveSpan(fullTraceName, (span) => {
        const handler = wrapCallback({
          callback: bound,
          before: () => {
            const attributes = {
              ...baseAttributes,
              ...ContextPropagation.getTelemetryAttributes(),
              ...getAdditionalDimensions ? getAdditionalDimensions() : {}
            };
            span.setAttributes(baseAttributes);
            trackers(traceName).count.add(1, attributes);
          },
          success: () => {
            span.setStatus({
              code: SpanStatusCode.OK
            });
            const attributes = {
              ...baseAttributes,
              ...ContextPropagation.getTelemetryAttributes(),
              ...getAdditionalDimensions ? getAdditionalDimensions() : {}
            };
            trackers(traceName).success.add(1, attributes);
          },
          failure: (error) => {
            const errorType = mapUnknownToErrorType(error);
            const tracker = trackers(traceName, errorType);
            span.setStatus({
              code: SpanStatusCode.ERROR,
              message: errorType
            });
            span.setAttribute("errorType", errorType);
            const attributes = {
              ...baseAttributes,
              ...ContextPropagation.getTelemetryAttributes(),
              ...getAdditionalDimensions ? getAdditionalDimensions() : {},
              errorType
            };
            const isAbort = isAbortError(error);
            const isBlocked = isBlockedAccessError(error);
            if (isAbort) {
              tracker.abort.add(1, {
                ...attributes,
                errorType
              });
              tracker.blocked.add(0, {
                ...attributes,
                errorType
              });
              tracker.failure.add(0, {
                ...attributes,
                errorType
              });
            } else if (isBlocked) {
              tracker.abort.add(0, {
                ...attributes,
                errorType
              });
              tracker.blocked.add(1, {
                ...attributes,
                errorType
              });
              tracker.failure.add(0, {
                ...attributes,
                errorType
              });
            } else {
              tracker.abort.add(0, {
                ...attributes,
                errorType
              });
              tracker.blocked.add(0, {
                ...attributes,
                errorType
              });
              tracker.failure.add(1, {
                ...attributes,
                errorType
              });
            }
            tracker.errorType.add(1, attributes);
            tracker.success.add(0, attributes);
          },
          after: (duration) => {
            const attributes = {
              ...baseAttributes,
              ...ContextPropagation.getTelemetryAttributes(),
              ...getAdditionalDimensions ? getAdditionalDimensions() : {}
            };
            trackers(traceName).latency.record(duration, attributes);
            span.end();
          }
        });
        return handler();
      });
    };
  }
  /**
   * Calls a function with trace directly
   */
  callWithTrace(traceName, fn) {
    return this.wrapTrace(traceName, fn)();
  }
  /**
   * Executes the callback function while emitting x-ray traces
   */
  withTrace({
    traceName,
    metricAliases,
    errorMapper
  }, fn) {
    const baseAttributes = {
      ...DefaultAttributes,
      Operation: traceName
    };
    const fullTraceName = `${this.scope}.${traceName}`;
    const tracer = trace.getTracer(TelemetryNamespace.Application, APPLICATION_VERSION);
    const trackers = this.getOperationTrackers.bind(this);
    const metricNames = [traceName, ...metricAliases || []];
    const bound = (span) => fn.apply(this, [span]);
    return tracer.startActiveSpan(fullTraceName, (span) => {
      const handler = wrapCallback({
        callback: () => bound(span),
        before: () => {
          const attributes = {
            ...baseAttributes,
            ...ContextPropagation.getTelemetryAttributes()
          };
          span.setAttributes(baseAttributes);
          metricNames.forEach((metricName) => {
            const metricAttributes = {
              ...attributes,
              Operation: metricName
            };
            trackers(metricName).count.add(1, metricAttributes);
          });
        },
        success: () => {
          span.setStatus({
            code: SpanStatusCode.OK
          });
          const attributes = {
            ...baseAttributes,
            ...ContextPropagation.getTelemetryAttributes()
          };
          metricNames.forEach((metricName) => {
            const metricAttributes = {
              ...attributes,
              Operation: metricName
            };
            trackers(metricName).success.add(1, metricAttributes);
          });
        },
        failure: (error) => {
          const errorType = mapUnknownToErrorType(error);
          const trackerList = metricNames.map((metricName) => ({
            tracker: trackers(metricName, errorType),
            metricName
          }));
          span.setStatus({
            code: SpanStatusCode.ERROR,
            message: errorType
          });
          span.setAttribute("errorType", errorType);
          const attributes = {
            ...baseAttributes,
            ...ContextPropagation.getTelemetryAttributes(),
            errorType
          };
          const errorCounts = errorMapper(error);
          Object.keys(errorCounts).forEach((errorType2) => {
            trackerList.forEach(({
              tracker,
              metricName
            }) => {
              const metricAttributes = {
                ...attributes,
                Operation: metricName,
                errorType: errorType2
              };
              tracker[errorType2].add(errorCounts[errorType2], metricAttributes);
            });
          });
          trackerList.forEach(({
            tracker,
            metricName
          }) => {
            const metricAttributes = {
              ...attributes,
              Operation: metricName
            };
            tracker.errorType.add(1, metricAttributes);
            tracker.success.add(0, metricAttributes);
          });
        },
        after: (duration) => {
          const attributes = {
            ...baseAttributes,
            ...ContextPropagation.getTelemetryAttributes()
          };
          metricNames.forEach((metricName) => {
            const metricAttributes = {
              ...attributes,
              Operation: metricName
            };
            trackers(metricName).latency.record(duration, metricAttributes);
          });
          span.end();
        }
      });
      return handler();
    });
  }
  /**
   * Sets up trace which can be closed when needed, not tied to a scope
   */
  createTrace(traceName) {
    const attributes = {
      ...DefaultAttributes,
      Operation: traceName
    };
    const fullTraceName = `${this.scope}.${traceName}`;
    const tracer = trace.getTracer(TelemetryNamespace.Application, APPLICATION_VERSION);
    let span = void 0;
    return {
      start: () => {
        span = tracer.startSpan(fullTraceName, {
          attributes
        });
      },
      success: () => {
        if (span) {
          span.setStatus({
            code: SpanStatusCode.OK
          });
          span.end();
        }
      },
      fail: (error) => {
        if (span) {
          const errorType = mapUnknownToErrorType(error);
          span.setStatus({
            code: SpanStatusCode.ERROR,
            message: errorType
          });
          span.end();
        }
      },
      setAttributes: (attributes2) => {
        if (span) {
          span.setAttributes(attributes2);
        }
      }
    };
  }
  /**
   * Decorator to handle adding traces to a function
   */
  Trace(operationName, getAdditionalDimensions) {
    const wrapper = this.wrapTrace.bind(this);
    return function(_, propertyKey, descriptor) {
      const original = descriptor.value;
      const functionName = typeof propertyKey === "string" ? propertyKey : String(propertyKey);
      const metricName = operationName || functionName;
      const newFunction = wrapper(metricName, original, getAdditionalDimensions);
      descriptor.value = newFunction;
    };
  }
};
__publicField(_MetricReporter, "periodicReporters", /* @__PURE__ */ new Map());
__publicField(_MetricReporter, "periodicReporterTimeout");
let MetricReporter = _MetricReporter;
const machineId = getMachineId();
const platform = `${os.platform()}-${os.release()}`;
const version = vscode.kiroVersion ?? "0.0.0";
const semanticVersion = semver.parse(version);
const channel = version.split("-").length === 1 ? "stable" : "insider";
const KiroClientVersion =
  `${semanticVersion == null ? void 0 : semanticVersion.major}.${semanticVersion == null ? void 0 : semanticVersion.minor}`;
const KiroClientVersionStr =
  `${semanticVersion == null ? void 0 : semanticVersion.major}-${semanticVersion == null ? void 0 : semanticVersion.minor}`;
const PlatformUsage = new MetricReporter(TelemetryNamespace.Application);
const DefaultAttributes = {
  KiroClientVersion,
  machineId,
  platform,
  channel,
  version
};

function periodicAttributes() {
  PlatformUsage.reportCountMetrics({
    osPlatform: 1
  }, {
    Operation: os.platform()
  });
  PlatformUsage.reportCountMetrics({
    kiroChannel: 1
  }, {
    Operation: channel
  });
  return {
    [`AppPlatform.${os.platform()}`]: true,
    [`AppVersion.${KiroClientVersionStr}`]: true
  };
}
logger.info(`Loading telemetry with client attributes`, DefaultAttributes);
const FeatureMetrics = new MetricReporter(TelemetryNamespace.Feature, "features");
let recentlyUsedFeatures = /* @__PURE__ */ new Set();
FeatureMetrics.periodicallyCaptureMetrics(() => {
  const resultMetrics = {};
  for (const feature of recentlyUsedFeatures) {
    resultMetrics[`${feature}.usedByUser`] = true;
  }
  if (recentlyUsedFeatures.size > 0) {
    resultMetrics[`anyAIFeaturesUsed`] = true;
  }
  recentlyUsedFeatures = /* @__PURE__ */ new Set();
  return resultMetrics;
});

function reportUsage(feature) {
  FeatureMetrics.reportCountMetrics({
    [`${feature}.used`]: true
  });
  recentlyUsedFeatures.add(feature);
}
const Telemetry = new MetricReporter(TelemetryNamespace.Application);
Telemetry.periodicallyCaptureMetrics(() => periodicAttributes());
const Feature = {
  reportUsage
};
var Tool = /* @__PURE__ */ ((Tool2) => {
  Tool2["WriteFile"] = "WriteFile";
  Tool2["GrepSearch"] = "GrepSearch";
  Tool2["FileSearch"] = "FileSearch";
  Tool2["ReplaceText"] = "ReplaceText";
  Tool2["EditCode"] = "EditCode";
  Tool2["SelfLabel"] = "SelfLabel";
  Tool2["AppendLines"] = "AppendLines";
  Tool2["DeleteFile"] = "DeleteFile";
  Tool2["ExecuteShell"] = "ExecuteShell";
  Tool2["ControlProcess"] = "ControlProcess";
  Tool2["ListProcesses"] = "ListProcesses";
  Tool2["GetProcessOutput"] = "GetProcessOutput";
  Tool2["OpenFolder"] = "OpenFolder";
  Tool2["FindFiles"] = "FindFiles";
  Tool2["GetUserInput"] = "GetUserInput";
  Tool2["ReadFile"] = "ReadFile";
  Tool2["ReadMultipleFiles"] = "ReadMultipleFiles";
  Tool2["NativeSearch"] = "NativeSearch";
  Tool2["MCPWrapper"] = "MCPWrapper";
  Tool2["TaskStatus"] = "TaskStatus";
  Tool2["PBTStatus"] = "PBTStatus";
  Tool2["GetDiagnostics"] = "GetDiagnostics";
  Tool2["Prework"] = "Prework";
  Tool2["ReadCode"] = "ReadCode";
  Tool2["InvokeSubAgent"] = "InvokeSubAgent";
  Tool2["ReportProgress"] = "ReportProgress";
  Tool2["KiroPowers"] = "KiroPowers";
  Tool2["SubagentResponse"] = "SubagentResponse";
  Tool2["WebFetch"] = "WebFetch";
  return Tool2;
})(Tool || {});
const TOOL_CONFIG = {
  [
    "WriteFile"
    /* WriteFile */
  ]: {
    name: "write_file",
    description: "Tracks write file tool"
  },
  [
    "GrepSearch"
    /* GrepSearch */
  ]: {
    name: "grep_search",
    description: "Tracks grep search tool"
  },
  [
    "FileSearch"
    /* FileSearch */
  ]: {
    name: "file_search",
    description: "Tracks file search tool"
  },
  [
    "ReplaceText"
    /* ReplaceText */
  ]: {
    name: "replace_text",
    description: "Tracks replace text tool"
  },
  [
    "EditCode"
    /* EditCode */
  ]: {
    name: "edit_code",
    description: "Tracks edit code tool"
  },
  [
    "SelfLabel"
    /* SelfLabel */
  ]: {
    name: "self_label",
    description: "Tracks self label tool"
  },
  [
    "AppendLines"
    /* AppendLines */
  ]: {
    name: "append_lines",
    description: "Tracks append lines tool"
  },
  [
    "DeleteFile"
    /* DeleteFile */
  ]: {
    name: "delete_file",
    description: "Tracks delete file tool"
  },
  [
    "ExecuteShell"
    /* ExecuteShell */
  ]: {
    name: "execute_shell",
    description: "Tracks execute shell tool"
  },
  [
    "ControlProcess"
    /* ControlProcess */
  ]: {
    name: "control_process",
    description: "Tracks control process tool"
  },
  [
    "ListProcesses"
    /* ListProcesses */
  ]: {
    name: "list_processes",
    description: "Tracks list processes tool"
  },
  [
    "GetProcessOutput"
    /* GetProcessOutput */
  ]: {
    name: "get_process_output",
    description: "Tracks get process output tool"
  },
  [
    "OpenFolder"
    /* OpenFolder */
  ]: {
    name: "open_folder",
    description: "Tracks open folder tool"
  },
  [
    "FindFiles"
    /* FindFiles */
  ]: {
    name: "find_files",
    description: "Tracks find files tool"
  },
  [
    "GetUserInput"
    /* GetUserInput */
  ]: {
    name: "get_user_input",
    description: "Tracks get user input tool including fix suggestions"
  },
  [
    "ReadFile"
    /* ReadFile */
  ]: {
    name: "read_file",
    description: "Tracks read file tool"
  },
  [
    "ReadMultipleFiles"
    /* ReadMultipleFiles */
  ]: {
    name: "read_multiple_files",
    description: "Tracks read multiple files tool"
  },
  [
    "NativeSearch"
    /* NativeSearch */
  ]: {
    name: "native_search",
    description: "Tracks native search tool"
  },
  [
    "MCPWrapper"
    /* MCPWrapper */
  ]: {
    name: "mcp_wrapper",
    description: "Tracks any custom MCP tool call"
  },
  [
    "TaskStatus"
    /* TaskStatus */
  ]: {
    name: "task_status",
    description: "Tracks the task status tool"
  },
  [
    "PBTStatus"
    /* PBTStatus */
  ]: {
    name: "pbt_status",
    description: "Tracks the PBT status tool"
  },
  [
    "GetDiagnostics"
    /* GetDiagnostics */
  ]: {
    name: "get_diagnostics",
    description: "Tracks get diagnostics tool"
  },
  [
    "Prework"
    /* Prework */
  ]: {
    name: "prework",
    description: "Tracks the prework tool"
  },
  [
    "ReadCode"
    /* ReadCode */
  ]: {
    name: "read_code",
    description: "Tracks read code tool"
  },
  [
    "InvokeSubAgent"
    /* InvokeSubAgent */
  ]: {
    name: "invoke_sub_agent",
    description: "Tracks invoke sub-agent tool"
  },
  [
    "ReportProgress"
    /* ReportProgress */
  ]: {
    name: "report_progress",
    description: "Tracks report progress tool"
  },
  [
    "KiroPowers"
    /* KiroPowers */
  ]: {
    name: "kiro_powers",
    description: "Tracks Kiro Powers tool"
  },
  [
    "SubagentResponse"
    /* SubagentResponse */
  ]: {
    name: "subagent_response",
    description: "Tracks subagent response tool"
  },
  [
    "WebFetch"
    /* WebFetch */
  ]: {
    name: "web_fetch",
    description: "Tracks web fetch tool"
  }
};
const ToolUsage = new MetricReporter(TelemetryNamespace.Tool, "tools");
let invocationCounter;
let failureCounter;
let errorCounter;
let faultCounter;
let durationHistogram;

function initializeCounters$1() {
  const toolUsageMeter = metrics.getMeterProvider().getMeter(MetricNamespace.Tool);
  invocationCounter = toolUsageMeter.createCounter(`count`, {
    description: `tool invoke count`,
    unit: "number"
  });
  failureCounter = toolUsageMeter.createCounter(`failure`, {
    description: `tool failure count`,
    unit: "number"
  });
  errorCounter = toolUsageMeter.createCounter(`error`, {
    description: `tool error count (e.g. invalid input from model)`,
    unit: "number"
  });
  faultCounter = toolUsageMeter.createCounter(`fault`, {
    description: `tool fault count (e.g. internal tool failure)`,
    unit: "number"
  });
  durationHistogram = toolUsageMeter.createHistogram(`duration`, {
    description: `tool duration`,
    unit: "ms"
  });
}
class ToolRecorder {
  constructor(tool) {
    __publicField(this, "attributes");
    __publicField(this, "startTime");
    this.tool = tool;
    this.attributes = getToolMetricAttributes(TOOL_CONFIG[tool].name);
    this.startTime = performance.now();
    if (!isInitialized()) return;
    invocationCounter.add(1, this.attributes);
  }
  /**
   * Create a new recorder for a tool execution, and record the initial invoke.
   */
  static start(tool) {
    ToolUsage.reportCountMetrics({
      toolUsage: 1
    }, {
      Operation: `useTool.${tool}`
    });
    ToolUsage.reportCountMetrics({
      [`${tool}.invoke`]: 1,
      invoke: 1
    });
    return new ToolRecorder(tool);
  }
  /**
   * Record success metric and duration for a tool.
   */
  recordToolSuccess() {
    if (!isInitialized()) return;
    failureCounter.add(0, this.attributes);
    errorCounter.add(0, this.attributes);
    faultCounter.add(0, this.attributes);
    durationHistogram.record(performance.now() - this.startTime, this.attributes);
    const latency = performance.now() - this.startTime;
    ToolUsage.reportCountMetrics({
      [`${this.tool}.success`]: 1,
      [`${this.tool}.failure`]: 0,
      [`${this.tool}.error`]: 0,
      [`${this.tool}.fault`]: 0,
      toolSuccess: 1,
      toolFailure: 0,
      toolError: 0,
      toolFault: 0
    });
    ToolUsage.reportHistogramMetrics({
      [`${this.tool}.latency`]: latency,
      latency
    });
  }
  /**
   * Record custom histogram metric for this tool.
   */
  recordHistogram(metricName, value, dimensions) {
    const fullMetricName = `${this.tool}.${metricName}`;
    ToolUsage.reportHistogramMetrics({
      [fullMetricName]: value,
      [metricName]: value
    }, dimensions);
  }
  /**
   * Record when a tool encounters an invalid input failure.
   * This will ALSO publish a fault, so maintain compatibility with existing dashboards
   */
  recordToolError(error) {
    if (!isInitialized()) return;
    failureCounter.add(1, this.attributes);
    errorCounter.add(1, this.attributes);
    faultCounter.add(0, this.attributes);
    durationHistogram.record(performance.now() - this.startTime, this.attributes);
    const latency = performance.now() - this.startTime;
    const errorType = mapUnknownToErrorType(error);
    ToolUsage.reportCountMetrics({
      [`${this.tool}.success`]: 0,
      [`${this.tool}.failure`]: 1,
      [`${this.tool}.error`]: 1,
      [`${this.tool}.fault`]: 0,
      [`${this.tool}.error.${errorType}`]: 1,
      toolSuccess: 0,
      toolFailure: 1,
      toolError: 1,
      toolFault: 0,
      [`toolError.${errorType}`]: 1
    });
    ToolUsage.reportHistogramMetrics({
      [`${this.tool}.latency`]: latency,
      latency
    });
  }
  /**
   * Record when a tool encounters an internal exception.
   * This will ALSO publish a fault, so maintain compatibility with existing dashboards
   */
  recordToolFault(error) {
    if (!isInitialized()) return;
    failureCounter.add(1, this.attributes);
    errorCounter.add(0, this.attributes);
    faultCounter.add(1, this.attributes);
    durationHistogram.record(performance.now() - this.startTime, this.attributes);
    const latency = performance.now() - this.startTime;
    const errorType = mapUnknownToErrorType(error);
    ToolUsage.reportCountMetrics({
      [`${this.tool}.success`]: 0,
      [`${this.tool}.failure`]: 1,
      [`${this.tool}.error`]: 0,
      [`${this.tool}.fault`]: 1,
      [`${this.tool}.error.${errorType}`]: 1,
      toolSuccess: 0,
      toolFailure: 1,
      toolError: 0,
      toolFault: 1,
      [`toolError.${errorType}`]: 1
    });
    ToolUsage.reportHistogramMetrics({
      [`${this.tool}.latency`]: latency,
      latency
    });
  }
}
const AGENT_SUGGESTED_PREFIX = "Agent suggested bash execution count:";
const USER_ACTION_PREFIX = "User action count:";
let agentSuggestedCommand;
let agentCommandRequiredReview;
let userRejectedCommand;
let userAcceptedCommand;
let userTrustedCommand;
let userEditedCommand;
let userSelectedTrustOptionFull;
let userSelectedTrustOptionPartial;
let userSelectedTrustOptionBase;
let userDeselectedTrustOption;
const EVENT_COUNTER_MAP = /* @__PURE__ */ new Map();

function initializeEventCounterMap() {
  EVENT_COUNTER_MAP.set("agent-suggested-command", agentSuggestedCommand);
  EVENT_COUNTER_MAP.set("agent-command-required-review", agentCommandRequiredReview);
  EVENT_COUNTER_MAP.set("user-rejected-command", userRejectedCommand);
  EVENT_COUNTER_MAP.set("user-accepted-command", userAcceptedCommand);
  EVENT_COUNTER_MAP.set("user-trusted-command", userTrustedCommand);
  EVENT_COUNTER_MAP.set("user-edited-command", userEditedCommand);
  EVENT_COUNTER_MAP.set("user-selected-trust-option-full", userSelectedTrustOptionFull);
  EVENT_COUNTER_MAP.set("user-selected-trust-option-partial", userSelectedTrustOptionPartial);
  EVENT_COUNTER_MAP.set("user-selected-trust-option-base", userSelectedTrustOptionBase);
  EVENT_COUNTER_MAP.set("user-deselected-trust-option", userDeselectedTrustOption);
}

function initializeCounters() {
  const commandMeter = metrics.getMeterProvider().getMeter(MetricNamespace.Session);
  agentSuggestedCommand = commandMeter.createCounter("agent_suggested_command", {
    description: `${AGENT_SUGGESTED_PREFIX} total`,
    unit: "number"
  });
  agentCommandRequiredReview = commandMeter.createCounter("agent_command_required_review", {
    description: `${AGENT_SUGGESTED_PREFIX} required manual review`,
    unit: "number"
  });
  userRejectedCommand = commandMeter.createCounter("user_rejected_command", {
    description: `${USER_ACTION_PREFIX} rejected command`,
    unit: "number"
  });
  userAcceptedCommand = commandMeter.createCounter("user_accepted_command", {
    description: `${USER_ACTION_PREFIX} accepted command`,
    unit: "number"
  });
  userTrustedCommand = commandMeter.createCounter("user_trusted_command", {
    description: `${USER_ACTION_PREFIX} trusted command`,
    unit: "number"
  });
  userEditedCommand = commandMeter.createCounter("user_edited_command", {
    description: `${USER_ACTION_PREFIX} edited command`,
    unit: "number"
  });
  userSelectedTrustOptionFull = commandMeter.createCounter("user_selected_trust_option_full", {
    description: `${USER_ACTION_PREFIX} selected full trust option`,
    unit: "number"
  });
  userSelectedTrustOptionPartial = commandMeter.createCounter("user_selected_trust_option_partial", {
    description: `${USER_ACTION_PREFIX} selected partial trust option`,
    unit: "number"
  });
  userSelectedTrustOptionBase = commandMeter.createCounter("user_selected_trust_option_base", {
    description: `${USER_ACTION_PREFIX} selected base trust option`,
    unit: "number"
  });
  userDeselectedTrustOption = commandMeter.createCounter("user_deselected_trust_option", {
    description: `${USER_ACTION_PREFIX} cancelled trust selection`,
    unit: "number"
  });
  initializeEventCounterMap();
}

function recordBashToolEvent(type) {
  try {
    const activity = "bash_execution";
    const attributes = getUserActivityMetricAttributes(activity);
    const counter = EVENT_COUNTER_MAP.get(type);
    if (counter) {
      counter.add(1, attributes);
    }
  } catch (e) {
    logger.error("Failed to record bash execution outcome: ", e);
  }
}
const APPLICATION_NAME = "kiroAgent";
const APPLICATION_VERSION = "0.0.1";
const USER_MACHINE_ID = getMachineId();
const EXPORT_INTERVAL_MILLIS = 5e3;
let isTelemetryInitialized = false;

function isInitialized() {
  return isTelemetryInitialized;
}

function initializeBaggagePropagation(propagator) {
  propagation.setGlobalPropagator(propagator);
}

function initializeTelemetry(configuration) {
  const TELEMETRY_ENDPOINT = configuration.endpoint;
  const resource = Resource.empty().merge(
    new Resource({
      [ATTR_SERVICE_NAME]: APPLICATION_NAME,
      [ATTR_SERVICE_VERSION]: APPLICATION_VERSION
    })
  );
  const traceExporter = new OTLPTraceExporter({
    url: TELEMETRY_ENDPOINT + "/v1/traces",
    headers: {
      "x-kiro-machineid": USER_MACHINE_ID
    }
  });
  const metricExporter = new OTLPMetricExporter({
    // CloudWatch expects delta aggregation. If this is cumulative, cloudwatch
    // will collect duplicate metrics and our sample counts will be inflated
    url: TELEMETRY_ENDPOINT + "/v1/metrics",
    temporalityPreference: AggregationTemporality.DELTA,
    headers: {
      "x-kiro-machineid": USER_MACHINE_ID
    }
  });
  const metricReader = new PeriodicExportingMetricReader({
    exporter: metricExporter,
    exportIntervalMillis: EXPORT_INTERVAL_MILLIS
  });
  const meterProvider = new MeterProvider({
    resource,
    views: [
      new View({
        instrumentType: InstrumentType.HISTOGRAM,
        aggregation: new ExponentialHistogramAggregation()
      })
    ]
  });
  meterProvider.addMetricReader(metricReader);
  metrics.setGlobalMeterProvider(meterProvider);
  const batchSpanProcessor = new BatchSpanProcessor(traceExporter);
  const baggageSpanProcessor = new BaggageSpanProcessor({
    // Only extract known baggage keys
    keys: Object.values(TelemetryAttributes)
  });
  const idGenerator = new AWSXRayIdGenerator();
  const textMapPropagator = new AWSXRayPropagator();
  const telemetrySDK = new NodeSDK({
    textMapPropagator,
    resource,
    spanProcessors: [batchSpanProcessor, baggageSpanProcessor],
    traceExporter,
    idGenerator,
    autoDetectResources: false
  });
  telemetrySDK.start();
  initializeBaggagePropagation(textMapPropagator);
  initializeCounters$3();
  initializeCounters$2();
  initializeCounters$1();
  initializeCounters();
  isTelemetryInitialized = true;
  recordOnboardingStep("opened-IDE");
  return new vscode.Disposable(() => telemetrySDK.shutdown());
}
export {
  APPLICATION_NAME as A,
  ContextPropagation as C,
  DefaultAttributes as D,
  Feature,
  MetricNamespace as M,
  MetricReporter,
  Tool as T,
  Telemetry,
  ToolRecorder as a,
  APPLICATION_VERSION as b,
  initializeBaggagePropagation as c,
  initializeTelemetry as d,
  TelemetryNamespace as e,
  recordOnboardingStep as f,
  recordAuthFromSource as g,
  isInitialized as i,
  recordBashToolEvent as r
};