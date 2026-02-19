import { n as r, a as c } from "./id-DsOIUs_E.js";
var p = /* @__PURE__ */ ((e) => (e.Chat = "chat", e.Spec = "spec", e.Hook = "hook", e))(p || {}), l = /* @__PURE__ */ ((e) => (e.Queued = "queued", e.Running = "running", e.WaitingForApproval = "waiting_for_approval", e.Completed = "completed", e.Failed = "failed", e.Aborted = "aborted", e))(l || {}), m = /* @__PURE__ */ ((e) => (e.ChatAgent = "chat", e.AskAgent = "ask", e.SpecGeneration = "spec", e.CreateHook = "hook", e.TestGeneration = "test", e.ValidationDriven = "validation", e))(m || {}), o = /* @__PURE__ */ ((e) => (e.Pending = "pending", e.AwaitingApproval = "awaiting_approval", e.Approved = "approved", e.Denied = "denied", e.Executing = "executing", e.Completed = "completed", e.Failed = "failed", e))(o || {});
function h(e, t) {
  return {
    file: e,
    range: t
  };
}
function A(e, t, s, a, n) {
  return {
    file: e,
    range: {
      start: { line: t, character: s },
      end: { line: a, character: n }
    }
  };
}
function F(e) {
  return {
    tools: e.tools,
    systemMessage: e.systemMessage,
    contextFiles: e.contextFiles ?? [],
    steeringFiles: e.steeringFiles ?? [],
    workspaceInfo: e.workspaceInfo
  };
}
function v() {
  return {
    tools: [],
    systemMessage: "",
    contextFiles: [],
    steeringFiles: []
  };
}
function x(e, t) {
  return {
    ...e,
    tools: t
  };
}
function R(e, t) {
  return {
    ...e,
    systemMessage: t
  };
}
function M(e, t) {
  return {
    ...e,
    contextFiles: [...e.contextFiles, ...t]
  };
}
function w(e, t) {
  return {
    ...e,
    steeringFiles: [...e.steeringFiles, ...t]
  };
}
function k(e, t) {
  return {
    ...e,
    workspaceInfo: t
  };
}
class d {
  constructor(t, s, a, n, i) {
    this.id = t, this.timestamp = s, this.user = a, this.assistant = n, this.toolResponse = i;
  }
  /**
   * A turn is complete when:
   * 1. The assistant message is not streaming
   * 2. There are no pending approvals
   */
  get isComplete() {
    return !this.assistant.isStreaming && this.pendingApprovals.length === 0;
  }
  /**
   * Get all tool calls awaiting approval
   */
  get pendingApprovals() {
    var t;
    return ((t = this.assistant.toolCalls) == null ? void 0 : t.filter(({ status: s }) => s === o.AwaitingApproval)) ?? [];
  }
  /**
   * Check if this tuple has any tool calls
   */
  get hasToolCalls() {
    return !!this.assistant.toolCalls && this.assistant.toolCalls.length > 0;
  }
  /**
   * Get the overall execution status of this message tuple
   */
  get executionStatus() {
    return this.assistant.isStreaming ? l.Running : this.pendingApprovals.length > 0 ? l.WaitingForApproval : !this.assistant.toolCalls || this.assistant.toolCalls.length === 0 ? l.Completed : this.assistant.toolCalls.some(({ status: t }) => t === o.Failed) ? l.Failed : this.assistant.toolCalls.some(({ status: t }) => t === o.Executing) ? l.Running : this.assistant.toolCalls.every(({ status: t }) => t === o.Completed) ? l.Completed : l.Queued;
  }
}
function I(e) {
  return new d(e.id, r(), e.user, e.assistant, e.toolResponse);
}
function b(e) {
  const t = typeof e.content == "string" ? [{ type: "text", text: e.content }] : e.content;
  return {
    id: e.id,
    content: t,
    contextItems: e.contextItems,
    timestamp: r(),
    metadata: e.metadata
  };
}
function W(e) {
  return {
    id: e.id,
    content: e.content,
    toolCalls: e.toolCalls,
    isStreaming: e.isStreaming ?? !1,
    timestamp: r(),
    metadata: e.metadata
  };
}
function _(e) {
  return {
    id: e.id,
    responses: e.responses,
    timestamp: r()
  };
}
function g(e, t) {
  return {
    ...e,
    content: t,
    timestamp: r()
  };
}
function q(e) {
  return {
    ...e,
    isStreaming: !1,
    timestamp: r()
  };
}
function D(e, t) {
  const s = e.toolCalls ?? [];
  return {
    ...e,
    toolCalls: [...s, t],
    timestamp: r()
  };
}
function f(e, t, s, a) {
  if (!e.toolCalls)
    return e;
  const n = e.toolCalls.map((i) => i.id === t ? {
    ...i,
    status: s,
    ...a
  } : i);
  return {
    ...e,
    toolCalls: n,
    timestamp: r()
  };
}
function u(e, t) {
  return new d(
    e.id,
    e.timestamp,
    e.user,
    t,
    e.toolResponse
  );
}
function G(e, t) {
  return new d(
    e.id,
    e.timestamp,
    e.user,
    e.assistant,
    t
  );
}
function H(e, t) {
  const s = g(e.assistant, t);
  return u(e, s);
}
function L(e, t, s) {
  const a = r(), n = {};
  s === o.Approved && (n.approvedAt = a), s === o.Executing && (n.executedAt = a), (s === o.Completed || s === o.Failed) && (n.completedAt = a);
  const i = f(
    e.assistant,
    t,
    s,
    n
  );
  return u(e, i);
}
function Q(e, t) {
  var n, i;
  const s = ((n = e.toolResponse) == null ? void 0 : n.responses) ?? [], a = {
    id: ((i = e.toolResponse) == null ? void 0 : i.id) ?? c(),
    responses: [...s, t],
    timestamp: r()
  };
  return new d(e.id, e.timestamp, e.user, e.assistant, a);
}
export {
  m as A,
  d as C,
  l as E,
  p as S,
  o as T,
  A as a,
  F as b,
  h as c,
  v as d,
  R as e,
  M as f,
  w as g,
  k as h,
  I as i,
  b as j,
  W as k,
  _ as l,
  g as m,
  q as n,
  D as o,
  f as p,
  u as q,
  G as r,
  H as s,
  L as t,
  x as u,
  Q as v
};
