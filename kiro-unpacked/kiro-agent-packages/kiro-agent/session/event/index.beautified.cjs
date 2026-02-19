"use strict";
Object.defineProperty(exports, Symbol.toStringTag, {
  value: "Module"
});
const c = require("../../events-ClqnULUb.cjs"),
  e = require("../../id-Bz2XTYCE.cjs");

function l(t, n, a, r, o = c.EventSource.System, d) {
  return {
    id: e.generateId(),
    sessionId: t,
    timestamp: e.now(),
    type: "session_created",
    source: o,
    correlationId: d,
    data: {
      title: n,
      sessionType: a,
      initialContext: r
    }
  }
}

function u(t, n, a, r, o = c.EventSource.System, d) {
  return {
    id: e.generateId(),
    sessionId: t,
    timestamp: e.now(),
    type: "session_updated",
    source: o,
    correlationId: d,
    data: {
      field: n,
      oldValue: a,
      newValue: r
    }
  }
}

function s(t, n, a, r = c.EventSource.User, o) {
  return {
    id: e.generateId(),
    sessionId: t,
    timestamp: e.now(),
    type: "session_deleted",
    source: r,
    correlationId: o,
    data: {
      title: n,
      messageCount: a
    }
  }
}

function p(t, n, a, r = c.EventSource.Agent, o) {
  return {
    id: e.generateId(),
    sessionId: t,
    timestamp: e.now(),
    type: "message_added",
    source: r,
    correlationId: o,
    data: {
      messageId: n,
      messageType: a
    }
  }
}

function v(t, n, a, r, o = c.EventSource.Agent, d) {
  return {
    id: e.generateId(),
    sessionId: t,
    timestamp: e.now(),
    type: "streaming_update",
    source: o,
    correlationId: d,
    data: {
      messageId: n,
      partialContent: a,
      totalContent: r
    }
  }
}

function E(t, n, a, r, o = c.EventSource.Agent, d) {
  return {
    id: e.generateId(),
    sessionId: t,
    timestamp: e.now(),
    type: "message_completed",
    source: o,
    correlationId: d,
    data: {
      messageId: n,
      finalContent: a,
      toolCallCount: r
    }
  }
}

function m(t, n, a, r, o, d = c.EventSource.Agent, i) {
  return {
    id: e.generateId(),
    sessionId: t,
    timestamp: e.now(),
    type: "tool_call_approval_required",
    source: d,
    correlationId: i,
    data: {
      toolCallId: n,
      toolName: a,
      args: r,
      description: o
    }
  }
}

function g(t, n, a, r, o = c.EventSource.User, d) {
  return {
    id: e.generateId(),
    sessionId: t,
    timestamp: e.now(),
    type: "tool_call_approval_decided",
    source: o,
    correlationId: d,
    data: {
      toolCallId: n,
      approved: a,
      userComment: r
    }
  }
}

function S(t, n, a, r = c.EventSource.Tool, o) {
  return {
    id: e.generateId(),
    sessionId: t,
    timestamp: e.now(),
    type: "tool_call_started",
    source: r,
    correlationId: o,
    data: {
      toolCallId: n,
      toolName: a
    }
  }
}

function _(t, n, a, r, o = c.EventSource.Tool, d) {
  return {
    id: e.generateId(),
    sessionId: t,
    timestamp: e.now(),
    type: "tool_call_completed",
    source: o,
    correlationId: d,
    data: {
      toolCallId: n,
      success: a,
      duration: r
    }
  }
}

function C(t, n, a, r, o = c.EventSource.System, d) {
  return {
    id: e.generateId(),
    sessionId: t,
    timestamp: e.now(),
    type: "tool_call_status_changed",
    source: o,
    correlationId: d,
    data: {
      toolCallId: n,
      oldStatus: a,
      newStatus: r
    }
  }
}

function y(t, n, a, r, o = c.EventSource.Agent, d) {
  return {
    id: e.generateId(),
    sessionId: t,
    timestamp: e.now(),
    type: "execution_started",
    source: o,
    correlationId: d,
    data: {
      executionId: n,
      agentType: a,
      userInput: r
    }
  }
}

function f(t, n, a, r, o, d = c.EventSource.Agent, i) {
  return {
    id: e.generateId(),
    sessionId: t,
    timestamp: e.now(),
    type: "execution_completed",
    source: d,
    correlationId: i,
    data: {
      executionId: n,
      status: a,
      duration: r,
      metrics: o
    }
  }
}

function w(t, n, a, r, o = c.EventSource.Agent, d) {
  return {
    id: e.generateId(),
    sessionId: t,
    timestamp: e.now(),
    type: "execution_error",
    source: o,
    correlationId: d,
    data: {
      executionId: n,
      error: a,
      recoverable: r
    }
  }
}
exports.EventBus = c.EventBus;
exports.EventSource = c.EventSource;
exports.createExecutionCompletedEvent = f;
exports.createExecutionErrorEvent = w;
exports.createExecutionStartedEvent = y;
exports.createMessageAddedEvent = p;
exports.createMessageCompletedEvent = E;
exports.createSessionCreatedEvent = l;
exports.createSessionDeletedEvent = s;
exports.createSessionUpdatedEvent = u;
exports.createStreamingUpdateEvent = v;
exports.createToolCallApprovalDecidedEvent = g;
exports.createToolCallApprovalRequiredEvent = m;
exports.createToolCallCompletedEvent = _;
exports.createToolCallStartedEvent = S;
exports.createToolCallStatusChangedEvent = C;