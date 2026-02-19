"use strict";
const o = require("./id-Bz2XTYCE.cjs");
var p = (e => (e.Chat = "chat", e.Spec = "spec", e.Hook = "hook", e))(p || {}),
  l = (e => (e.Queued = "queued", e.Running = "running", e.WaitingForApproval = "waiting_for_approval", e.Completed =
    "completed", e.Failed = "failed", e.Aborted = "aborted", e))(l || {}),
  c = (e => (e.ChatAgent = "chat", e.AskAgent = "ask", e.SpecGeneration = "spec", e.CreateHook = "hook", e
    .TestGeneration = "test", e.ValidationDriven = "validation", e))(c || {}),
  r = (e => (e.Pending = "pending", e.AwaitingApproval = "awaiting_approval", e.Approved = "approved", e.Denied =
    "denied", e.Executing = "executing", e.Completed = "completed", e.Failed = "failed", e))(r || {});

function C(e, t) {
  return {
    file: e,
    range: t
  }
}

function f(e, t, s, a, n) {
  return {
    file: e,
    range: {
      start: {
        line: t,
        character: s
      },
      end: {
        line: a,
        character: n
      }
    }
  }
}

function h(e) {
  return {
    tools: e.tools,
    systemMessage: e.systemMessage,
    contextFiles: e.contextFiles ?? [],
    steeringFiles: e.steeringFiles ?? [],
    workspaceInfo: e.workspaceInfo
  }
}

function A() {
  return {
    tools: [],
    systemMessage: "",
    contextFiles: [],
    steeringFiles: []
  }
}

function F(e, t) {
  return {
    ...e,
    tools: t
  }
}

function v(e, t) {
  return {
    ...e,
    systemMessage: t
  }
}

function x(e, t) {
  return {
    ...e,
    contextFiles: [...e.contextFiles, ...t]
  }
}

function w(e, t) {
  return {
    ...e,
    steeringFiles: [...e.steeringFiles, ...t]
  }
}

function T(e, t) {
  return {
    ...e,
    workspaceInfo: t
  }
}
class d {
  constructor(t, s, a, n, i) {
    this.id = t, this.timestamp = s, this.user = a, this.assistant = n, this.toolResponse = i
  }
  get isComplete() {
    return !this.assistant.isStreaming && this.pendingApprovals.length === 0
  }
  get pendingApprovals() {
    var t;
    return ((t = this.assistant.toolCalls) == null ? void 0 : t.filter(({
      status: s
    }) => s === r.AwaitingApproval)) ?? []
  }
  get hasToolCalls() {
    return !!this.assistant.toolCalls && this.assistant.toolCalls.length > 0
  }
  get executionStatus() {
    return this.assistant.isStreaming ? l.Running : this.pendingApprovals.length > 0 ? l.WaitingForApproval : !this
      .assistant.toolCalls || this.assistant.toolCalls.length === 0 ? l.Completed : this.assistant.toolCalls.some(({
        status: t
      }) => t === r.Failed) ? l.Failed : this.assistant.toolCalls.some(({
        status: t
      }) => t === r.Executing) ? l.Running : this.assistant.toolCalls.every(({
        status: t
      }) => t === r.Completed) ? l.Completed : l.Queued
  }
}

function M(e) {
  return new d(e.id, o.now(), e.user, e.assistant, e.toolResponse)
}

function R(e) {
  const t = typeof e.content == "string" ? [{
    type: "text",
    text: e.content
  }] : e.content;
  return {
    id: e.id,
    content: t,
    contextItems: e.contextItems,
    timestamp: o.now(),
    metadata: e.metadata
  }
}

function k(e) {
  return {
    id: e.id,
    content: e.content,
    toolCalls: e.toolCalls,
    isStreaming: e.isStreaming ?? !1,
    timestamp: o.now(),
    metadata: e.metadata
  }
}

function I(e) {
  return {
    id: e.id,
    responses: e.responses,
    timestamp: o.now()
  }
}

function g(e, t) {
  return {
    ...e,
    content: t,
    timestamp: o.now()
  }
}

function y(e) {
  return {
    ...e,
    isStreaming: !1,
    timestamp: o.now()
  }
}

function L(e, t) {
  const s = e.toolCalls ?? [];
  return {
    ...e,
    toolCalls: [...s, t],
    timestamp: o.now()
  }
}

function m(e, t, s, a) {
  if (!e.toolCalls) return e;
  const n = e.toolCalls.map(i => i.id === t ? {
    ...i,
    status: s,
    ...a
  } : i);
  return {
    ...e,
    toolCalls: n,
    timestamp: o.now()
  }
}

function u(e, t) {
  return new d(e.id, e.timestamp, e.user, t, e.toolResponse)
}

function S(e, t) {
  return new d(e.id, e.timestamp, e.user, e.assistant, t)
}

function W(e, t) {
  const s = g(e.assistant, t);
  return u(e, s)
}

function _(e, t, s) {
  const a = o.now(),
    n = {};
  s === r.Approved && (n.approvedAt = a), s === r.Executing && (n.executedAt = a), (s === r.Completed || s === r
    .Failed) && (n.completedAt = a);
  const i = m(e.assistant, t, s, n);
  return u(e, i)
}

function b(e, t) {
  var n, i;
  const s = ((n = e.toolResponse) == null ? void 0 : n.responses) ?? [],
    a = {
      id: ((i = e.toolResponse) == null ? void 0 : i.id) ?? o.generateMessageId(),
      responses: [...s, t],
      timestamp: o.now()
    };
  return new d(e.id, e.timestamp, e.user, e.assistant, a)
}
exports.AgentType = c;
exports.ConversationTurn = d;
exports.ExecutionStatus = l;
exports.SessionType = p;
exports.ToolCallStatus = r;
exports.addContextFiles = x;
exports.addSteeringFiles = w;
exports.addToolCallToAssistant = L;
exports.addToolResponseToMessageTuple = b;
exports.addToolResponseToTuple = S;
exports.completeAssistantMessage = y;
exports.createAssistantMessage = k;
exports.createContextMessage = h;
exports.createConversationTurn = M;
exports.createEmptyContext = A;
exports.createFileLocation = C;
exports.createRangeLocation = f;
exports.createToolResponseMessage = I;
exports.createUserMessage = R;
exports.updateAssistantContent = g;
exports.updateContextSystemMessage = v;
exports.updateContextTools = F;
exports.updateConversationTurnAssistant = u;
exports.updateConversationTurnAssistantContent = W;
exports.updateConversationTurnToolCall = _;
exports.updateToolCallStatusInAssistant = m;
exports.updateWorkspaceInfo = T;