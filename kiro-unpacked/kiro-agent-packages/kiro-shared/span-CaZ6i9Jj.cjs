"use strict";
const api = require("@opentelemetry/api");
const telemetry_definitions_index = require("./telemetry/definitions/index.cjs");
const ignore = require("./ignore-D645GLpP.cjs");
require("path");
require("os");
require("fs");
require("vscode");
require("node-machine-id");
require("axios");
require("axios-retry");
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
      ...value instanceof ignore.TrustedError ? {
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
      span.setAttributes(telemetry_definitions_index.DefaultAttributes);
      const result = function_(span);
      if (isPromise(result)) {
        return result.then((value) => {
          span.setStatus({ code: api.SpanStatusCode.OK });
          return value;
        }).catch((error) => {
          span.recordException(mapUnknownToSpanStatus(error));
          span.setStatus({
            code: api.SpanStatusCode.ERROR
          });
          throw error;
        }).finally(() => {
          span.end();
        });
      }
      span.setStatus({ code: api.SpanStatusCode.OK });
      span.end();
      return result;
    } catch (error) {
      span.recordException(mapUnknownToSpanStatus(error));
      span.setStatus({
        code: api.SpanStatusCode.ERROR
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
  const tracer = api.trace.getTracer(namespace, telemetry_definitions_index.APPLICATION_VERSION);
  if (telemetry_definitions_index.isInitialized()) {
    tracers[namespace] = tracer;
  }
  return tracer;
}
exports.startActiveSpan = startActiveSpan;
exports.withSpan = withSpan;
