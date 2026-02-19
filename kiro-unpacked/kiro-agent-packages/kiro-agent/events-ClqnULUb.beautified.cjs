"use strict";
var a = Object.defineProperty;
var p = (r, t, s) => t in r ? a(r, t, {
  enumerable: !0,
  configurable: !0,
  writable: !0,
  value: s
}) : r[t] = s;
var o = (r, t, s) => p(r, typeof t != "symbol" ? t + "" : t, s);
const u = require("./id-Bz2XTYCE.cjs");
class S {
  constructor() {
    o(this, "typeSubscriptions", new Map);
    o(this, "sessionSubscriptions", new Map);
    o(this, "tokenToSubscription", new Map)
  }
  async emit(t) {
    const s = this.getSubscribersForEvent(t);
    s.size !== 0 && await Promise.all(Array.from(s).map(e => this.executeHandler(e.handler, t)))
  }
  subscribe(t, s) {
    const e = u.generateId(),
      i = {
        token: e,
        handler: s,
        eventType: t
      };
    this.typeSubscriptions.has(t) || this.typeSubscriptions.set(t, new Set);
    const n = this.typeSubscriptions.get(t);
    return n && n.add(i), this.tokenToSubscription.set(e, i), e
  }
  subscribeToSession(t, s) {
    var n;
    const e = u.generateId(),
      i = {
        token: e,
        handler: s,
        sessionId: t
      };
    return this.sessionSubscriptions.has(t) || this.sessionSubscriptions.set(t, new Set), (n = this
      .sessionSubscriptions.get(t)) == null || n.add(i), this.tokenToSubscription.set(e, i), e
  }
  unsubscribe(t) {
    const s = this.tokenToSubscription.get(t);
    if (s) {
      if (s.eventType) {
        const e = this.typeSubscriptions.get(s.eventType);
        e && (e.delete(s), e.size === 0 && this.typeSubscriptions.delete(s.eventType))
      }
      if (s.sessionId) {
        const e = this.sessionSubscriptions.get(s.sessionId);
        e && (e.delete(s), e.size === 0 && this.sessionSubscriptions.delete(s.sessionId))
      }
      this.tokenToSubscription.delete(t)
    }
  }
  async emitBatch(t) {
    const s = new Set;
    for (const i of t) this.getSubscribersForEvent(i).forEach(c => s.add(c));
    if (s.size === 0) return;
    const e = [];
    for (const i of t) {
      const n = this.getSubscribersForEvent(i);
      for (const c of n) e.push(this.executeHandler(c.handler, i))
    }
    await Promise.all(e)
  }
  getSubscriptionCount() {
    return this.tokenToSubscription.size
  }
  clearAllSubscriptions() {
    this.typeSubscriptions.clear(), this.sessionSubscriptions.clear(), this.tokenToSubscription.clear()
  }
  getSubscribersForEvent(t) {
    const s = new Set,
      e = this.typeSubscriptions.get(t.type);
    e && e.forEach(n => s.add(n));
    const i = this.sessionSubscriptions.get(t.sessionId);
    return i && i.forEach(n => s.add(n)), s
  }
  async executeHandler(t, s) {
    try {
      await t(s)
    } catch (e) {
      const i = e instanceof Error ? e.message : String(e);
      process.stderr.write(`Event handler failed: ${JSON.stringify({eventType:s.type,sessionId:s.sessionId,error:i})}
`)
    }
  }
}
var b = (r => (r.User = "user", r.Agent = "agent", r.Tool = "tool", r.System = "system", r))(b || {});
exports.EventBus = S;
exports.EventSource = b;