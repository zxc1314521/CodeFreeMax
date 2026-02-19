import { E as d } from "../../events-gUtXgKVx.js";
import { a as D } from "../../events-gUtXgKVx.js";
import { n as i, g as s } from "../../id-DsOIUs_E.js";
function l(e, t, a, n, r = d.System, o) {
  return {
    id: s(),
    sessionId: e,
    timestamp: i(),
    type: "session_created",
    source: r,
    correlationId: o,
    data: {
      title: t,
      sessionType: a,
      initialContext: n
    }
  };
}
function u(e, t, a, n, r = d.System, o) {
  return {
    id: s(),
    sessionId: e,
    timestamp: i(),
    type: "session_updated",
    source: r,
    correlationId: o,
    data: {
      field: t,
      oldValue: a,
      newValue: n
    }
  };
}
function _(e, t, a, n = d.User, r) {
  return {
    id: s(),
    sessionId: e,
    timestamp: i(),
    type: "session_deleted",
    source: n,
    correlationId: r,
    data: {
      title: t,
      messageCount: a
    }
  };
}
function E(e, t, a, n = d.Agent, r) {
  return {
    id: s(),
    sessionId: e,
    timestamp: i(),
    type: "message_added",
    source: n,
    correlationId: r,
    data: {
      messageId: t,
      messageType: a
    }
  };
}
function v(e, t, a, n, r = d.Agent, o) {
  return {
    id: s(),
    sessionId: e,
    timestamp: i(),
    type: "streaming_update",
    source: r,
    correlationId: o,
    data: {
      messageId: t,
      partialContent: a,
      totalContent: n
    }
  };
}
function f(e, t, a, n, r = d.Agent, o) {
  return {
    id: s(),
    sessionId: e,
    timestamp: i(),
    type: "message_completed",
    source: r,
    correlationId: o,
    data: {
      messageId: t,
      finalContent: a,
      toolCallCount: n
    }
  };
}
function g(e, t, a, n, r, o = d.Agent, p) {
  return {
    id: s(),
    sessionId: e,
    timestamp: i(),
    type: "tool_call_approval_required",
    source: o,
    correlationId: p,
    data: {
      toolCallId: t,
      toolName: a,
      args: n,
      description: r
    }
  };
}
function y(e, t, a, n, r = d.User, o) {
  return {
    id: s(),
    sessionId: e,
    timestamp: i(),
    type: "tool_call_approval_decided",
    source: r,
    correlationId: o,
    data: {
      toolCallId: t,
      approved: a,
      userComment: n
    }
  };
}
function S(e, t, a, n = d.Tool, r) {
  return {
    id: s(),
    sessionId: e,
    timestamp: i(),
    type: "tool_call_started",
    source: n,
    correlationId: r,
    data: {
      toolCallId: t,
      toolName: a
    }
  };
}
function A(e, t, a, n, r = d.Tool, o) {
  return {
    id: s(),
    sessionId: e,
    timestamp: i(),
    type: "tool_call_completed",
    source: r,
    correlationId: o,
    data: {
      toolCallId: t,
      success: a,
      duration: n
    }
  };
}
function C(e, t, a, n, r = d.System, o) {
  return {
    id: s(),
    sessionId: e,
    timestamp: i(),
    type: "tool_call_status_changed",
    source: r,
    correlationId: o,
    data: {
      toolCallId: t,
      oldStatus: a,
      newStatus: n
    }
  };
}
function x(e, t, a, n, r = d.Agent, o) {
  return {
    id: s(),
    sessionId: e,
    timestamp: i(),
    type: "execution_started",
    source: r,
    correlationId: o,
    data: {
      executionId: t,
      agentType: a,
      userInput: n
    }
  };
}
function T(e, t, a, n, r, o = d.Agent, p) {
  return {
    id: s(),
    sessionId: e,
    timestamp: i(),
    type: "execution_completed",
    source: o,
    correlationId: p,
    data: {
      executionId: t,
      status: a,
      duration: n,
      metrics: r
    }
  };
}
function U(e, t, a, n, r = d.Agent, o) {
  return {
    id: s(),
    sessionId: e,
    timestamp: i(),
    type: "execution_error",
    source: r,
    correlationId: o,
    data: {
      executionId: t,
      error: a,
      recoverable: n
    }
  };
}
export {
  D as EventBus,
  d as EventSource,
  T as createExecutionCompletedEvent,
  U as createExecutionErrorEvent,
  x as createExecutionStartedEvent,
  E as createMessageAddedEvent,
  f as createMessageCompletedEvent,
  l as createSessionCreatedEvent,
  _ as createSessionDeletedEvent,
  u as createSessionUpdatedEvent,
  v as createStreamingUpdateEvent,
  y as createToolCallApprovalDecidedEvent,
  g as createToolCallApprovalRequiredEvent,
  A as createToolCallCompletedEvent,
  S as createToolCallStartedEvent,
  C as createToolCallStatusChangedEvent
};
