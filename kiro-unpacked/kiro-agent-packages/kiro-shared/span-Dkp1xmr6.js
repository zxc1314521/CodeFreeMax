import { SpanStatusCode, trace } from "@opentelemetry/api";
import { D as DefaultAttributes, b as APPLICATION_VERSION, i as isInitialized } from "./telemetry/definitions/index.js";
import { T as TrustedError } from "./ignore-B7xGFdAM.js";
import "path";
import "os";
import "fs";
import "vscode";
import "node-machine-id";
import "axios";
import "axios-retry";
function mapUnknownToSpanStatus(value) {
  if (typeof value == "string") {
    return value;
  }
  if (typeof value === "boolean" || typeof value === "number") {
    return value.toString();
  }
  if (value instanceof Error) {
    return {
      name: value.name,
      ...value instanceof TrustedError ? {
        message: value.message
      } : {}
      // message: value.message,
      // stack: value.stack,
    };
  }
  if (value === void 0) {
    return "undefined";
  }
  return JSON.stringify(value);
}
function isPromise(value) {
  return Boolean(value) && typeof value.then === "function";
}
function startActiveSpan(namespace, name, wrappedFunction) {
  return getTracer(namespace).startActiveSpan(name, wrappedFunction);
}
function withSpan(namespace, name, function_) {
  return getTracer(namespace).startActiveSpan(`${namespace}.${name}`, (span) => {
    try {
      span.setAttributes(DefaultAttributes);
      const result = function_(span);
      if (isPromise(result)) {
        return result.then((value) => {
          span.setStatus({ code: SpanStatusCode.OK });
          return value;
        }).catch((error) => {
          span.recordException(mapUnknownToSpanStatus(error));
          span.setStatus({
            code: SpanStatusCode.ERROR
          });
          throw error;
        }).finally(() => {
          span.end();
        });
      }
      span.setStatus({ code: SpanStatusCode.OK });
      span.end();
      return result;
    } catch (error) {
      span.recordException(mapUnknownToSpanStatus(error));
      span.setStatus({
        code: SpanStatusCode.ERROR
      });
      span.end();
      throw error;
    }
  });
}
const tracers = {};
function getTracer(namespace) {
  if (namespace in tracers) {
    return tracers[namespace];
  }
  const tracer = trace.getTracer(namespace, APPLICATION_VERSION);
  if (isInitialized()) {
    tracers[namespace] = tracer;
  }
  return tracer;
}
export {
  startActiveSpan as s,
  withSpan as w
};
