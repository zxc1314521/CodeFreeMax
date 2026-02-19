var u = Object.defineProperty;
var a = (r, t, s) => t in r ? u(r, t, { enumerable: !0, configurable: !0, writable: !0, value: s }) : r[t] = s;
var n = (r, t, s) => a(r, typeof t != "symbol" ? t + "" : t, s);
import { g as b } from "./id-DsOIUs_E.js";
class d {
  constructor() {
    // Map of event type to subscriptions
    n(this, "typeSubscriptions", /* @__PURE__ */ new Map());
    // Map of session ID to subscriptions
    n(this, "sessionSubscriptions", /* @__PURE__ */ new Map());
    // Map of token to subscription for cleanup
    n(this, "tokenToSubscription", /* @__PURE__ */ new Map());
  }
  /**
   * Emit an event to all subscribers
   * Handlers are executed concurrently
   */
  // eslint-disable-next-line @typescript-eslint/no-unnecessary-type-parameters
  async emit(t) {
    const s = this.getSubscribersForEvent(t);
    s.size !== 0 && await Promise.all(Array.from(s).map((e) => this.executeHandler(e.handler, t)));
  }
  /**
   * Subscribe to a specific event type
   * Returns a token that can be used to unsubscribe
   */
  subscribe(t, s) {
    const e = b(), i = {
      token: e,
      handler: s,
      eventType: t
    };
    this.typeSubscriptions.has(t) || this.typeSubscriptions.set(t, /* @__PURE__ */ new Set());
    const o = this.typeSubscriptions.get(t);
    return o && o.add(i), this.tokenToSubscription.set(e, i), e;
  }
  /**
   * Subscribe to all events for a specific session
   * Returns a token that can be used to unsubscribe
   */
  subscribeToSession(t, s) {
    var o;
    const e = b(), i = {
      token: e,
      handler: s,
      sessionId: t
    };
    return this.sessionSubscriptions.has(t) || this.sessionSubscriptions.set(t, /* @__PURE__ */ new Set()), (o = this.sessionSubscriptions.get(t)) == null || o.add(i), this.tokenToSubscription.set(e, i), e;
  }
  /**
   * Unsubscribe from events using a subscription token
   */
  unsubscribe(t) {
    const s = this.tokenToSubscription.get(t);
    if (s) {
      if (s.eventType) {
        const e = this.typeSubscriptions.get(s.eventType);
        e && (e.delete(s), e.size === 0 && this.typeSubscriptions.delete(s.eventType));
      }
      if (s.sessionId) {
        const e = this.sessionSubscriptions.get(s.sessionId);
        e && (e.delete(s), e.size === 0 && this.sessionSubscriptions.delete(s.sessionId));
      }
      this.tokenToSubscription.delete(t);
    }
  }
  /**
   * Emit multiple events in a batch
   * All handlers are executed concurrently
   */
  async emitBatch(t) {
    const s = /* @__PURE__ */ new Set();
    for (const i of t)
      this.getSubscribersForEvent(i).forEach((c) => s.add(c));
    if (s.size === 0)
      return;
    const e = [];
    for (const i of t) {
      const o = this.getSubscribersForEvent(i);
      for (const c of o)
        e.push(this.executeHandler(c.handler, i));
    }
    await Promise.all(e);
  }
  /**
   * Get the number of active subscriptions
   */
  getSubscriptionCount() {
    return this.tokenToSubscription.size;
  }
  /**
   * Clear all subscriptions (useful for testing)
   */
  clearAllSubscriptions() {
    this.typeSubscriptions.clear(), this.sessionSubscriptions.clear(), this.tokenToSubscription.clear();
  }
  // ============================================================================
  // Private Helper Methods
  // ============================================================================
  /**
   * Get all subscribers that should receive this event
   */
  getSubscribersForEvent(t) {
    const s = /* @__PURE__ */ new Set(), e = this.typeSubscriptions.get(t.type);
    e && e.forEach((o) => s.add(o));
    const i = this.sessionSubscriptions.get(t.sessionId);
    return i && i.forEach((o) => s.add(o)), s;
  }
  /**
   * Execute a handler with error isolation
   * Errors in one handler don't affect other handlers
   */
  async executeHandler(t, s) {
    try {
      await t(s);
    } catch (e) {
      const i = e instanceof Error ? e.message : String(e);
      process.stderr.write(
        `Event handler failed: ${JSON.stringify({
          eventType: s.type,
          sessionId: s.sessionId,
          error: i
        })}
`
      );
    }
  }
}
var p = /* @__PURE__ */ ((r) => (r.User = "user", r.Agent = "agent", r.Tool = "tool", r.System = "system", r))(p || {});
export {
  p as E,
  d as a
};
