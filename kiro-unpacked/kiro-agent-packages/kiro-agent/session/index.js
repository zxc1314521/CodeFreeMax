var Wr = Object.defineProperty;
var zr = (n, t, e) => t in n ? Wr(n, t, { enumerable: !0, configurable: !0, writable: !0, value: e }) : n[t] = e;
var z = (n, t, e) => zr(n, typeof t != "symbol" ? t + "" : t, e);
import { T as $, j as Hr, k as Jr, i as Yr, s as xt, C as ge, t as $t, v as Nt, S as Kr } from "../conversation-turn-CSAggVnf.js";
import { A as Bn, E as Vn, f as Xn, g as Wn, o as zn, r as Hn, n as Jn, b as Yn, d as Kn, c as Qn, a as Zn, l as ei, m as ti, e as ri, u as si, q as ni, p as ii, h as ai } from "../conversation-turn-CSAggVnf.js";
import { n as j, a as Ie, b as Qr, g as K } from "../id-DsOIUs_E.js";
import { c as ui, t as li } from "../id-DsOIUs_E.js";
import "zod";
import { K as _t } from "../powers-D5ei-qtJ.js";
import * as H from "fs";
import * as Se from "path";
import { a as Zr, E as oe } from "../events-gUtXgKVx.js";
function jr(n) {
  return n && n.__esModule && Object.prototype.hasOwnProperty.call(n, "default") ? n.default : n;
}
var Re, bt;
function es() {
  return bt || (bt = 1, Re = function(n, t) {
    if (typeof n != "string")
      throw new TypeError("Expected a string");
    return t = typeof t > "u" ? "_" : t, n.replace(/([a-z\d])([A-Z])/g, "$1" + t + "$2").replace(/([A-Z]+)([A-Z][a-z\d]+)/g, "$1" + t + "$2").toLowerCase();
  }), Re;
}
var ts = es();
const rs = /* @__PURE__ */ jr(ts);
var ue = { exports: {} }, Mt;
function ss() {
  if (Mt) return ue.exports;
  Mt = 1;
  const n = /[\p{Lu}]/u, t = /[\p{Ll}]/u, e = /^[\p{Lu}](?![\p{Lu}])/gu, r = /([\p{Alpha}\p{N}_]|$)/u, s = /[_.\- ]+/, i = new RegExp("^" + s.source), a = new RegExp(s.source + r.source, "gu"), u = new RegExp("\\d+" + r.source, "gu"), c = (h, p, w) => {
    let m = !1, E = !1, T = !1;
    for (let M = 0; M < h.length; M++) {
      const R = h[M];
      m && n.test(R) ? (h = h.slice(0, M) + "-" + h.slice(M), m = !1, T = E, E = !0, M++) : E && T && t.test(R) ? (h = h.slice(0, M - 1) + "-" + h.slice(M - 1), T = E, E = !1, m = !0) : (m = p(R) === R && w(R) !== R, T = E, E = w(R) === R && p(R) !== R);
    }
    return h;
  }, l = (h, p) => (e.lastIndex = 0, h.replace(e, (w) => p(w))), o = (h, p) => (a.lastIndex = 0, u.lastIndex = 0, h.replace(a, (w, m) => p(m)).replace(u, (w) => p(w))), f = (h, p) => {
    if (!(typeof h == "string" || Array.isArray(h)))
      throw new TypeError("Expected the input to be `string | string[]`");
    if (p = {
      pascalCase: !1,
      preserveConsecutiveUppercase: !1,
      ...p
    }, Array.isArray(h) ? h = h.map((T) => T.trim()).filter((T) => T.length).join("-") : h = h.trim(), h.length === 0)
      return "";
    const w = p.locale === !1 ? (T) => T.toLowerCase() : (T) => T.toLocaleLowerCase(p.locale), m = p.locale === !1 ? (T) => T.toUpperCase() : (T) => T.toLocaleUpperCase(p.locale);
    return h.length === 1 ? p.pascalCase ? m(h) : w(h) : (h !== w(h) && (h = c(h, w, m)), h = h.replace(i, ""), p.preserveConsecutiveUppercase ? h = l(h, w) : h = w(h), p.pascalCase && (h = m(h.charAt(0)) + h.slice(1)), o(h, m));
  };
  return ue.exports = f, ue.exports.default = f, ue.exports;
}
ss();
function ns(n, t) {
  return (t == null ? void 0 : t[n]) || rs(n);
}
function is(n, t, e) {
  const r = {};
  for (const s in n)
    Object.hasOwn(n, s) && (r[t(s, e)] = n[s]);
  return r;
}
function Pt(n) {
  return Array.isArray(n) ? [...n] : { ...n };
}
function as(n, t) {
  const e = Pt(n);
  for (const [r, s] of Object.entries(t)) {
    const [i, ...a] = r.split(".").reverse();
    let u = e;
    for (const c of a.reverse()) {
      if (u[c] === void 0)
        break;
      u[c] = Pt(u[c]), u = u[c];
    }
    u[i] !== void 0 && (u[i] = {
      lc: 1,
      type: "secret",
      id: [s]
    });
  }
  return e;
}
function os(n) {
  const t = Object.getPrototypeOf(n);
  return typeof n.lc_name == "function" && (typeof t.lc_name != "function" || n.lc_name() !== t.lc_name()) ? n.lc_name() : n.name;
}
class wt {
  /**
   * The name of the serializable. Override to provide an alias or
   * to preserve the serialized module name in minified environments.
   *
   * Implemented as a static method to support loading logic.
   */
  static lc_name() {
    return this.name;
  }
  /**
   * The final serialized identifier for the module.
   */
  get lc_id() {
    return [
      ...this.lc_namespace,
      os(this.constructor)
    ];
  }
  /**
   * A map of secrets, which will be omitted from serialization.
   * Keys are paths to the secret in constructor args, e.g. "foo.bar.baz".
   * Values are the secret ids, which will be used when deserializing.
   */
  get lc_secrets() {
  }
  /**
   * A map of additional attributes to merge with constructor args.
   * Keys are the attribute names, e.g. "foo".
   * Values are the attribute values, which will be serialized.
   * These attributes need to be accepted by the constructor as arguments.
   */
  get lc_attributes() {
  }
  /**
   * A map of aliases for constructor args.
   * Keys are the attribute names, e.g. "foo".
   * Values are the alias that will replace the key in serialization.
   * This is used to eg. make argument names match Python.
   */
  get lc_aliases() {
  }
  /**
   * A manual list of keys that should be serialized.
   * If not overridden, all fields passed into the constructor will be serialized.
   */
  get lc_serializable_keys() {
  }
  constructor(t, ...e) {
    Object.defineProperty(this, "lc_serializable", {
      enumerable: !0,
      configurable: !0,
      writable: !0,
      value: !1
    }), Object.defineProperty(this, "lc_kwargs", {
      enumerable: !0,
      configurable: !0,
      writable: !0,
      value: void 0
    }), this.lc_serializable_keys !== void 0 ? this.lc_kwargs = Object.fromEntries(Object.entries(t || {}).filter(([r]) => {
      var s;
      return (s = this.lc_serializable_keys) == null ? void 0 : s.includes(r);
    })) : this.lc_kwargs = t ?? {};
  }
  toJSON() {
    if (!this.lc_serializable)
      return this.toJSONNotImplemented();
    if (
      // eslint-disable-next-line no-instanceof/no-instanceof
      this.lc_kwargs instanceof wt || typeof this.lc_kwargs != "object" || Array.isArray(this.lc_kwargs)
    )
      return this.toJSONNotImplemented();
    const t = {}, e = {}, r = Object.keys(this.lc_kwargs).reduce((s, i) => (s[i] = i in this ? this[i] : this.lc_kwargs[i], s), {});
    for (let s = Object.getPrototypeOf(this); s; s = Object.getPrototypeOf(s))
      Object.assign(t, Reflect.get(s, "lc_aliases", this)), Object.assign(e, Reflect.get(s, "lc_secrets", this)), Object.assign(r, Reflect.get(s, "lc_attributes", this));
    return Object.keys(e).forEach((s) => {
      let i = this, a = r;
      const [u, ...c] = s.split(".").reverse();
      for (const l of c.reverse()) {
        if (!(l in i) || i[l] === void 0)
          return;
        (!(l in a) || a[l] === void 0) && (typeof i[l] == "object" && i[l] != null ? a[l] = {} : Array.isArray(i[l]) && (a[l] = [])), i = i[l], a = a[l];
      }
      u in i && i[u] !== void 0 && (a[u] = a[u] || i[u]);
    }), {
      lc: 1,
      type: "constructor",
      id: this.lc_id,
      kwargs: is(Object.keys(e).length ? as(r, e) : r, ns, t)
    };
  }
  toJSONNotImplemented() {
    return {
      lc: 1,
      type: "not_implemented",
      id: this.lc_id
    };
  }
}
function us(n, t) {
  function e(r, s) {
    if (typeof r != "object" || r === null || r === void 0)
      return r;
    if (s >= t)
      return Array.isArray(r) ? "[Array]" : "[Object]";
    if (Array.isArray(r))
      return r.map((a) => e(a, s + 1));
    const i = {};
    for (const a of Object.keys(r))
      i[a] = e(r[a], s + 1);
    return i;
  }
  return JSON.stringify(e(n, 0), null, 2);
}
class It extends wt {
  get lc_aliases() {
    return {
      additional_kwargs: "additional_kwargs",
      response_metadata: "response_metadata"
    };
  }
  /**
   * Get text content of the message.
   */
  get text() {
    return typeof this.content == "string" ? this.content : Array.isArray(this.content) ? this.content.map((t) => typeof t == "string" ? t : t.type === "text" ? t.text : "").join("") : "";
  }
  /** The type of the message. */
  getType() {
    return this._getType();
  }
  constructor(t, e) {
    typeof t == "string" && (t = {
      content: t,
      additional_kwargs: e,
      response_metadata: {}
    }), t.additional_kwargs || (t.additional_kwargs = {}), t.response_metadata || (t.response_metadata = {}), super(t), Object.defineProperty(this, "lc_namespace", {
      enumerable: !0,
      configurable: !0,
      writable: !0,
      value: ["langchain_core", "messages"]
    }), Object.defineProperty(this, "lc_serializable", {
      enumerable: !0,
      configurable: !0,
      writable: !0,
      value: !0
    }), Object.defineProperty(this, "content", {
      enumerable: !0,
      configurable: !0,
      writable: !0,
      value: void 0
    }), Object.defineProperty(this, "name", {
      enumerable: !0,
      configurable: !0,
      writable: !0,
      value: void 0
    }), Object.defineProperty(this, "additional_kwargs", {
      enumerable: !0,
      configurable: !0,
      writable: !0,
      value: void 0
    }), Object.defineProperty(this, "response_metadata", {
      enumerable: !0,
      configurable: !0,
      writable: !0,
      value: void 0
    }), Object.defineProperty(this, "id", {
      enumerable: !0,
      configurable: !0,
      writable: !0,
      value: void 0
    }), this.name = t.name, this.content = t.content, this.additional_kwargs = t.additional_kwargs, this.response_metadata = t.response_metadata, this.id = t.id;
  }
  toDict() {
    return {
      type: this._getType(),
      data: this.toJSON().kwargs
    };
  }
  static lc_name() {
    return "BaseMessage";
  }
  // Can't be protected for silly reasons
  get _printableFields() {
    return {
      id: this.id,
      content: this.content,
      name: this.name,
      additional_kwargs: this.additional_kwargs,
      response_metadata: this.response_metadata
    };
  }
  // this private method is used to update the ID for the runtime
  // value as well as in lc_kwargs for serialisation
  _updateId(t) {
    this.id = t, this.lc_kwargs.id = t;
  }
  get [Symbol.toStringTag]() {
    return this.constructor.lc_name();
  }
  // Override the default behavior of console.log
  [Symbol.for("nodejs.util.inspect.custom")](t) {
    if (t === null)
      return this;
    const e = us(this._printableFields, Math.max(4, t));
    return `${this.constructor.lc_name()} ${e}`;
  }
}
function ls(n) {
  const t = [], e = [];
  for (const r of n)
    if (r.function) {
      const s = r.function.name;
      try {
        const i = JSON.parse(r.function.arguments), a = {
          name: s || "",
          args: i || {},
          id: r.id
        };
        t.push(a);
      } catch {
        e.push({
          name: s,
          args: r.function.arguments,
          id: r.id,
          error: "Malformed args."
        });
      }
    } else
      continue;
  return [t, e];
}
class cs extends It {
  get lc_aliases() {
    return {
      ...super.lc_aliases,
      tool_calls: "tool_calls",
      invalid_tool_calls: "invalid_tool_calls"
    };
  }
  constructor(t, e) {
    var s;
    let r;
    if (typeof t == "string")
      r = {
        content: t,
        tool_calls: [],
        invalid_tool_calls: [],
        additional_kwargs: e ?? {}
      };
    else {
      r = t;
      const i = (s = r.additional_kwargs) == null ? void 0 : s.tool_calls, a = r.tool_calls;
      i != null && i.length > 0 && (a === void 0 || a.length === 0) && console.warn([
        "New LangChain packages are available that more efficiently handle",
        `tool calling.

Please upgrade your packages to versions that set`,
        "message tool calls. e.g., `yarn add @langchain/anthropic`,",
        "yarn add @langchain/openai`, etc."
      ].join(" "));
      try {
        if (i != null && a === void 0) {
          const [u, c] = ls(i);
          r.tool_calls = u ?? [], r.invalid_tool_calls = c ?? [];
        } else
          r.tool_calls = r.tool_calls ?? [], r.invalid_tool_calls = r.invalid_tool_calls ?? [];
      } catch {
        r.tool_calls = [], r.invalid_tool_calls = [];
      }
    }
    super(r), Object.defineProperty(this, "tool_calls", {
      enumerable: !0,
      configurable: !0,
      writable: !0,
      value: []
    }), Object.defineProperty(this, "invalid_tool_calls", {
      enumerable: !0,
      configurable: !0,
      writable: !0,
      value: []
    }), Object.defineProperty(this, "usage_metadata", {
      enumerable: !0,
      configurable: !0,
      writable: !0,
      value: void 0
    }), typeof r != "string" && (this.tool_calls = r.tool_calls ?? this.tool_calls, this.invalid_tool_calls = r.invalid_tool_calls ?? this.invalid_tool_calls), this.usage_metadata = r.usage_metadata;
  }
  static lc_name() {
    return "AIMessage";
  }
  _getType() {
    return "ai";
  }
  get _printableFields() {
    return {
      ...super._printableFields,
      tool_calls: this.tool_calls,
      invalid_tool_calls: this.invalid_tool_calls,
      usage_metadata: this.usage_metadata
    };
  }
}
class le extends It {
  static lc_name() {
    return "HumanMessage";
  }
  _getType() {
    return "human";
  }
  constructor(t, e) {
    super(t, e);
  }
}
class hs extends It {
  static lc_name() {
    return "SystemMessage";
  }
  _getType() {
    return "system";
  }
  constructor(t, e) {
    super(t, e);
  }
}
var te = { exports: {} }, Te = {}, Ce, qt;
function fs() {
  if (qt) return Ce;
  qt = 1;
  function n(t, e) {
    typeof e == "boolean" && (e = { forever: e }), this._originalTimeouts = JSON.parse(JSON.stringify(t)), this._timeouts = t, this._options = e || {}, this._maxRetryTime = e && e.maxRetryTime || 1 / 0, this._fn = null, this._errors = [], this._attempts = 1, this._operationTimeout = null, this._operationTimeoutCb = null, this._timeout = null, this._operationStart = null, this._timer = null, this._options.forever && (this._cachedTimeouts = this._timeouts.slice(0));
  }
  return Ce = n, n.prototype.reset = function() {
    this._attempts = 1, this._timeouts = this._originalTimeouts.slice(0);
  }, n.prototype.stop = function() {
    this._timeout && clearTimeout(this._timeout), this._timer && clearTimeout(this._timer), this._timeouts = [], this._cachedTimeouts = null;
  }, n.prototype.retry = function(t) {
    if (this._timeout && clearTimeout(this._timeout), !t)
      return !1;
    var e = (/* @__PURE__ */ new Date()).getTime();
    if (t && e - this._operationStart >= this._maxRetryTime)
      return this._errors.push(t), this._errors.unshift(new Error("RetryOperation timeout occurred")), !1;
    this._errors.push(t);
    var r = this._timeouts.shift();
    if (r === void 0)
      if (this._cachedTimeouts)
        this._errors.splice(0, this._errors.length - 1), r = this._cachedTimeouts.slice(-1);
      else
        return !1;
    var s = this;
    return this._timer = setTimeout(function() {
      s._attempts++, s._operationTimeoutCb && (s._timeout = setTimeout(function() {
        s._operationTimeoutCb(s._attempts);
      }, s._operationTimeout), s._options.unref && s._timeout.unref()), s._fn(s._attempts);
    }, r), this._options.unref && this._timer.unref(), !0;
  }, n.prototype.attempt = function(t, e) {
    this._fn = t, e && (e.timeout && (this._operationTimeout = e.timeout), e.cb && (this._operationTimeoutCb = e.cb));
    var r = this;
    this._operationTimeoutCb && (this._timeout = setTimeout(function() {
      r._operationTimeoutCb();
    }, r._operationTimeout)), this._operationStart = (/* @__PURE__ */ new Date()).getTime(), this._fn(this._attempts);
  }, n.prototype.try = function(t) {
    console.log("Using RetryOperation.try() is deprecated"), this.attempt(t);
  }, n.prototype.start = function(t) {
    console.log("Using RetryOperation.start() is deprecated"), this.attempt(t);
  }, n.prototype.start = n.prototype.try, n.prototype.errors = function() {
    return this._errors;
  }, n.prototype.attempts = function() {
    return this._attempts;
  }, n.prototype.mainError = function() {
    if (this._errors.length === 0)
      return null;
    for (var t = {}, e = null, r = 0, s = 0; s < this._errors.length; s++) {
      var i = this._errors[s], a = i.message, u = (t[a] || 0) + 1;
      t[a] = u, u >= r && (e = i, r = u);
    }
    return e;
  }, Ce;
}
var Dt;
function ds() {
  return Dt || (Dt = 1, function(n) {
    var t = fs();
    n.operation = function(e) {
      var r = n.timeouts(e);
      return new t(r, {
        forever: e && (e.forever || e.retries === 1 / 0),
        unref: e && e.unref,
        maxRetryTime: e && e.maxRetryTime
      });
    }, n.timeouts = function(e) {
      if (e instanceof Array)
        return [].concat(e);
      var r = {
        retries: 10,
        factor: 2,
        minTimeout: 1 * 1e3,
        maxTimeout: 1 / 0,
        randomize: !1
      };
      for (var s in e)
        r[s] = e[s];
      if (r.minTimeout > r.maxTimeout)
        throw new Error("minTimeout is greater than maxTimeout");
      for (var i = [], a = 0; a < r.retries; a++)
        i.push(this.createTimeout(a, r));
      return e && e.forever && !i.length && i.push(this.createTimeout(a, r)), i.sort(function(u, c) {
        return u - c;
      }), i;
    }, n.createTimeout = function(e, r) {
      var s = r.randomize ? Math.random() + 1 : 1, i = Math.round(s * Math.max(r.minTimeout, 1) * Math.pow(r.factor, e));
      return i = Math.min(i, r.maxTimeout), i;
    }, n.wrap = function(e, r, s) {
      if (r instanceof Array && (s = r, r = null), !s) {
        s = [];
        for (var i in e)
          typeof e[i] == "function" && s.push(i);
      }
      for (var a = 0; a < s.length; a++) {
        var u = s[a], c = e[u];
        e[u] = (function(o) {
          var f = n.operation(r), h = Array.prototype.slice.call(arguments, 1), p = h.pop();
          h.push(function(w) {
            f.retry(w) || (w && (arguments[0] = f.mainError()), p.apply(this, arguments));
          }), f.attempt(function() {
            o.apply(e, h);
          });
        }).bind(e, c), e[u].options = r;
      }
    };
  }(Te)), Te;
}
var Ae, Ft;
function ps() {
  return Ft || (Ft = 1, Ae = ds()), Ae;
}
var jt;
function ms() {
  if (jt) return te.exports;
  jt = 1;
  const n = ps(), t = [
    "Failed to fetch",
    // Chrome
    "NetworkError when attempting to fetch resource.",
    // Firefox
    "The Internet connection appears to be offline.",
    // Safari
    "Network request failed"
    // `cross-fetch`
  ];
  class e extends Error {
    constructor(u) {
      super(), u instanceof Error ? (this.originalError = u, { message: u } = u) : (this.originalError = new Error(u), this.originalError.stack = this.stack), this.name = "AbortError", this.message = u;
    }
  }
  const r = (a, u, c) => {
    const l = c.retries - (u - 1);
    return a.attemptNumber = u, a.retriesLeft = l, a;
  }, s = (a) => t.includes(a), i = (a, u) => new Promise((c, l) => {
    u = {
      onFailedAttempt: () => {
      },
      retries: 10,
      ...u
    };
    const o = n.operation(u);
    o.attempt(async (f) => {
      try {
        c(await a(f));
      } catch (h) {
        if (!(h instanceof Error)) {
          l(new TypeError(`Non-error was thrown: "${h}". You should only throw errors.`));
          return;
        }
        if (h instanceof e)
          o.stop(), l(h.originalError);
        else if (h instanceof TypeError && !s(h.message))
          o.stop(), l(h);
        else {
          r(h, f, u);
          try {
            await u.onFailedAttempt(h);
          } catch (p) {
            l(p);
            return;
          }
          o.retry(h) || l(o.mainError());
        }
      }
    });
  });
  return te.exports = i, te.exports.default = i, te.exports.AbortError = e, te.exports;
}
ms();
var ce = {}, Le = { exports: {} }, Gt;
function gs() {
  return Gt || (Gt = 1, function(n) {
    var t = Object.prototype.hasOwnProperty, e = "~";
    function r() {
    }
    Object.create && (r.prototype = /* @__PURE__ */ Object.create(null), new r().__proto__ || (e = !1));
    function s(c, l, o) {
      this.fn = c, this.context = l, this.once = o || !1;
    }
    function i(c, l, o, f, h) {
      if (typeof o != "function")
        throw new TypeError("The listener must be a function");
      var p = new s(o, f || c, h), w = e ? e + l : l;
      return c._events[w] ? c._events[w].fn ? c._events[w] = [c._events[w], p] : c._events[w].push(p) : (c._events[w] = p, c._eventsCount++), c;
    }
    function a(c, l) {
      --c._eventsCount === 0 ? c._events = new r() : delete c._events[l];
    }
    function u() {
      this._events = new r(), this._eventsCount = 0;
    }
    u.prototype.eventNames = function() {
      var l = [], o, f;
      if (this._eventsCount === 0) return l;
      for (f in o = this._events)
        t.call(o, f) && l.push(e ? f.slice(1) : f);
      return Object.getOwnPropertySymbols ? l.concat(Object.getOwnPropertySymbols(o)) : l;
    }, u.prototype.listeners = function(l) {
      var o = e ? e + l : l, f = this._events[o];
      if (!f) return [];
      if (f.fn) return [f.fn];
      for (var h = 0, p = f.length, w = new Array(p); h < p; h++)
        w[h] = f[h].fn;
      return w;
    }, u.prototype.listenerCount = function(l) {
      var o = e ? e + l : l, f = this._events[o];
      return f ? f.fn ? 1 : f.length : 0;
    }, u.prototype.emit = function(l, o, f, h, p, w) {
      var m = e ? e + l : l;
      if (!this._events[m]) return !1;
      var E = this._events[m], T = arguments.length, M, R;
      if (E.fn) {
        switch (E.once && this.removeListener(l, E.fn, void 0, !0), T) {
          case 1:
            return E.fn.call(E.context), !0;
          case 2:
            return E.fn.call(E.context, o), !0;
          case 3:
            return E.fn.call(E.context, o, f), !0;
          case 4:
            return E.fn.call(E.context, o, f, h), !0;
          case 5:
            return E.fn.call(E.context, o, f, h, p), !0;
          case 6:
            return E.fn.call(E.context, o, f, h, p, w), !0;
        }
        for (R = 1, M = new Array(T - 1); R < T; R++)
          M[R - 1] = arguments[R];
        E.fn.apply(E.context, M);
      } else {
        var g = E.length, d;
        for (R = 0; R < g; R++)
          switch (E[R].once && this.removeListener(l, E[R].fn, void 0, !0), T) {
            case 1:
              E[R].fn.call(E[R].context);
              break;
            case 2:
              E[R].fn.call(E[R].context, o);
              break;
            case 3:
              E[R].fn.call(E[R].context, o, f);
              break;
            case 4:
              E[R].fn.call(E[R].context, o, f, h);
              break;
            default:
              if (!M) for (d = 1, M = new Array(T - 1); d < T; d++)
                M[d - 1] = arguments[d];
              E[R].fn.apply(E[R].context, M);
          }
      }
      return !0;
    }, u.prototype.on = function(l, o, f) {
      return i(this, l, o, f, !1);
    }, u.prototype.once = function(l, o, f) {
      return i(this, l, o, f, !0);
    }, u.prototype.removeListener = function(l, o, f, h) {
      var p = e ? e + l : l;
      if (!this._events[p]) return this;
      if (!o)
        return a(this, p), this;
      var w = this._events[p];
      if (w.fn)
        w.fn === o && (!h || w.once) && (!f || w.context === f) && a(this, p);
      else {
        for (var m = 0, E = [], T = w.length; m < T; m++)
          (w[m].fn !== o || h && !w[m].once || f && w[m].context !== f) && E.push(w[m]);
        E.length ? this._events[p] = E.length === 1 ? E[0] : E : a(this, p);
      }
      return this;
    }, u.prototype.removeAllListeners = function(l) {
      var o;
      return l ? (o = e ? e + l : l, this._events[o] && a(this, o)) : (this._events = new r(), this._eventsCount = 0), this;
    }, u.prototype.off = u.prototype.removeListener, u.prototype.addListener = u.prototype.on, u.prefixed = e, u.EventEmitter = u, n.exports = u;
  }(Le)), Le.exports;
}
var re = { exports: {} }, Oe, kt;
function vs() {
  return kt || (kt = 1, Oe = (n, t) => (t = t || (() => {
  }), n.then(
    (e) => new Promise((r) => {
      r(t());
    }).then(() => e),
    (e) => new Promise((r) => {
      r(t());
    }).then(() => {
      throw e;
    })
  ))), Oe;
}
var Ut;
function Es() {
  if (Ut) return re.exports;
  Ut = 1;
  const n = vs();
  class t extends Error {
    constructor(s) {
      super(s), this.name = "TimeoutError";
    }
  }
  const e = (r, s, i) => new Promise((a, u) => {
    if (typeof s != "number" || s < 0)
      throw new TypeError("Expected `milliseconds` to be a positive number");
    if (s === 1 / 0) {
      a(r);
      return;
    }
    const c = setTimeout(() => {
      if (typeof i == "function") {
        try {
          a(i());
        } catch (f) {
          u(f);
        }
        return;
      }
      const l = typeof i == "string" ? i : `Promise timed out after ${s} milliseconds`, o = i instanceof Error ? i : new t(l);
      typeof r.cancel == "function" && r.cancel(), u(o);
    }, s);
    n(
      // eslint-disable-next-line promise/prefer-await-to-then
      r.then(a, u),
      () => {
        clearTimeout(c);
      }
    );
  });
  return re.exports = e, re.exports.default = e, re.exports.TimeoutError = t, re.exports;
}
var he = {}, fe = {}, Bt;
function ys() {
  if (Bt) return fe;
  Bt = 1, Object.defineProperty(fe, "__esModule", { value: !0 });
  function n(t, e, r) {
    let s = 0, i = t.length;
    for (; i > 0; ) {
      const a = i / 2 | 0;
      let u = s + a;
      r(t[u], e) <= 0 ? (s = ++u, i -= a + 1) : i = a;
    }
    return s;
  }
  return fe.default = n, fe;
}
var Vt;
function _s() {
  if (Vt) return he;
  Vt = 1, Object.defineProperty(he, "__esModule", { value: !0 });
  const n = ys();
  class t {
    constructor() {
      this._queue = [];
    }
    enqueue(r, s) {
      s = Object.assign({ priority: 0 }, s);
      const i = {
        priority: s.priority,
        run: r
      };
      if (this.size && this._queue[this.size - 1].priority >= s.priority) {
        this._queue.push(i);
        return;
      }
      const a = n.default(this._queue, i, (u, c) => c.priority - u.priority);
      this._queue.splice(a, 0, i);
    }
    dequeue() {
      const r = this._queue.shift();
      return r == null ? void 0 : r.run;
    }
    filter(r) {
      return this._queue.filter((s) => s.priority === r.priority).map((s) => s.run);
    }
    get size() {
      return this._queue.length;
    }
  }
  return he.default = t, he;
}
var Xt;
function ws() {
  if (Xt) return ce;
  Xt = 1, Object.defineProperty(ce, "__esModule", { value: !0 });
  const n = gs(), t = Es(), e = _s(), r = () => {
  }, s = new t.TimeoutError();
  class i extends n {
    constructor(u) {
      var c, l, o, f;
      if (super(), this._intervalCount = 0, this._intervalEnd = 0, this._pendingCount = 0, this._resolveEmpty = r, this._resolveIdle = r, u = Object.assign({ carryoverConcurrencyCount: !1, intervalCap: 1 / 0, interval: 0, concurrency: 1 / 0, autoStart: !0, queueClass: e.default }, u), !(typeof u.intervalCap == "number" && u.intervalCap >= 1))
        throw new TypeError(`Expected \`intervalCap\` to be a number from 1 and up, got \`${(l = (c = u.intervalCap) === null || c === void 0 ? void 0 : c.toString()) !== null && l !== void 0 ? l : ""}\` (${typeof u.intervalCap})`);
      if (u.interval === void 0 || !(Number.isFinite(u.interval) && u.interval >= 0))
        throw new TypeError(`Expected \`interval\` to be a finite number >= 0, got \`${(f = (o = u.interval) === null || o === void 0 ? void 0 : o.toString()) !== null && f !== void 0 ? f : ""}\` (${typeof u.interval})`);
      this._carryoverConcurrencyCount = u.carryoverConcurrencyCount, this._isIntervalIgnored = u.intervalCap === 1 / 0 || u.interval === 0, this._intervalCap = u.intervalCap, this._interval = u.interval, this._queue = new u.queueClass(), this._queueClass = u.queueClass, this.concurrency = u.concurrency, this._timeout = u.timeout, this._throwOnTimeout = u.throwOnTimeout === !0, this._isPaused = u.autoStart === !1;
    }
    get _doesIntervalAllowAnother() {
      return this._isIntervalIgnored || this._intervalCount < this._intervalCap;
    }
    get _doesConcurrentAllowAnother() {
      return this._pendingCount < this._concurrency;
    }
    _next() {
      this._pendingCount--, this._tryToStartAnother(), this.emit("next");
    }
    _resolvePromises() {
      this._resolveEmpty(), this._resolveEmpty = r, this._pendingCount === 0 && (this._resolveIdle(), this._resolveIdle = r, this.emit("idle"));
    }
    _onResumeInterval() {
      this._onInterval(), this._initializeIntervalIfNeeded(), this._timeoutId = void 0;
    }
    _isIntervalPaused() {
      const u = Date.now();
      if (this._intervalId === void 0) {
        const c = this._intervalEnd - u;
        if (c < 0)
          this._intervalCount = this._carryoverConcurrencyCount ? this._pendingCount : 0;
        else
          return this._timeoutId === void 0 && (this._timeoutId = setTimeout(() => {
            this._onResumeInterval();
          }, c)), !0;
      }
      return !1;
    }
    _tryToStartAnother() {
      if (this._queue.size === 0)
        return this._intervalId && clearInterval(this._intervalId), this._intervalId = void 0, this._resolvePromises(), !1;
      if (!this._isPaused) {
        const u = !this._isIntervalPaused();
        if (this._doesIntervalAllowAnother && this._doesConcurrentAllowAnother) {
          const c = this._queue.dequeue();
          return c ? (this.emit("active"), c(), u && this._initializeIntervalIfNeeded(), !0) : !1;
        }
      }
      return !1;
    }
    _initializeIntervalIfNeeded() {
      this._isIntervalIgnored || this._intervalId !== void 0 || (this._intervalId = setInterval(() => {
        this._onInterval();
      }, this._interval), this._intervalEnd = Date.now() + this._interval);
    }
    _onInterval() {
      this._intervalCount === 0 && this._pendingCount === 0 && this._intervalId && (clearInterval(this._intervalId), this._intervalId = void 0), this._intervalCount = this._carryoverConcurrencyCount ? this._pendingCount : 0, this._processQueue();
    }
    /**
    Executes all queued functions until it reaches the limit.
    */
    _processQueue() {
      for (; this._tryToStartAnother(); )
        ;
    }
    get concurrency() {
      return this._concurrency;
    }
    set concurrency(u) {
      if (!(typeof u == "number" && u >= 1))
        throw new TypeError(`Expected \`concurrency\` to be a number from 1 and up, got \`${u}\` (${typeof u})`);
      this._concurrency = u, this._processQueue();
    }
    /**
    Adds a sync or async task to the queue. Always returns a promise.
    */
    async add(u, c = {}) {
      return new Promise((l, o) => {
        const f = async () => {
          this._pendingCount++, this._intervalCount++;
          try {
            const h = this._timeout === void 0 && c.timeout === void 0 ? u() : t.default(Promise.resolve(u()), c.timeout === void 0 ? this._timeout : c.timeout, () => {
              (c.throwOnTimeout === void 0 ? this._throwOnTimeout : c.throwOnTimeout) && o(s);
            });
            l(await h);
          } catch (h) {
            o(h);
          }
          this._next();
        };
        this._queue.enqueue(f, c), this._tryToStartAnother(), this.emit("add");
      });
    }
    /**
    	    Same as `.add()`, but accepts an array of sync or async functions.
    
    	    @returns A promise that resolves when all functions are resolved.
    	    */
    async addAll(u, c) {
      return Promise.all(u.map(async (l) => this.add(l, c)));
    }
    /**
    Start (or resume) executing enqueued tasks within concurrency limit. No need to call this if queue is not paused (via `options.autoStart = false` or by `.pause()` method.)
    */
    start() {
      return this._isPaused ? (this._isPaused = !1, this._processQueue(), this) : this;
    }
    /**
    Put queue execution on hold.
    */
    pause() {
      this._isPaused = !0;
    }
    /**
    Clear the queue.
    */
    clear() {
      this._queue = new this._queueClass();
    }
    /**
    	    Can be called multiple times. Useful if you for example add additional items at a later time.
    
    	    @returns A promise that settles when the queue becomes empty.
    	    */
    async onEmpty() {
      if (this._queue.size !== 0)
        return new Promise((u) => {
          const c = this._resolveEmpty;
          this._resolveEmpty = () => {
            c(), u();
          };
        });
    }
    /**
    	    The difference with `.onEmpty` is that `.onIdle` guarantees that all work from the queue has finished. `.onEmpty` merely signals that the queue is empty, but it could mean that some promises haven't completed yet.
    
    	    @returns A promise that settles when the queue becomes empty, and all promises have completed; `queue.size === 0 && queue.pending === 0`.
    	    */
    async onIdle() {
      if (!(this._pendingCount === 0 && this._queue.size === 0))
        return new Promise((u) => {
          const c = this._resolveIdle;
          this._resolveIdle = () => {
            c(), u();
          };
        });
    }
    /**
    Size of the queue.
    */
    get size() {
      return this._queue.size;
    }
    /**
    	    Size of the queue, filtered by the given options.
    
    	    For example, this can be used to find the number of items remaining in the queue with a specific priority level.
    	    */
    sizeBy(u) {
      return this._queue.filter(u).length;
    }
    /**
    Number of pending promises.
    */
    get pending() {
      return this._pendingCount;
    }
    /**
    Whether the queue is currently paused.
    */
    get isPaused() {
      return this._isPaused;
    }
    get timeout() {
      return this._timeout;
    }
    /**
    Set the timeout for future operations.
    */
    set timeout(u) {
      this._timeout = u;
    }
  }
  return ce.default = i, ce;
}
ws();
var de = { exports: {} }, xe, Wt;
function ve() {
  if (Wt) return xe;
  Wt = 1;
  const n = "2.0.0", t = 256, e = Number.MAX_SAFE_INTEGER || /* istanbul ignore next */
  9007199254740991, r = 16, s = t - 6;
  return xe = {
    MAX_LENGTH: t,
    MAX_SAFE_COMPONENT_LENGTH: r,
    MAX_SAFE_BUILD_LENGTH: s,
    MAX_SAFE_INTEGER: e,
    RELEASE_TYPES: [
      "major",
      "premajor",
      "minor",
      "preminor",
      "patch",
      "prepatch",
      "prerelease"
    ],
    SEMVER_SPEC_VERSION: n,
    FLAG_INCLUDE_PRERELEASE: 1,
    FLAG_LOOSE: 2
  }, xe;
}
var $e, zt;
function Ee() {
  return zt || (zt = 1, $e = typeof process == "object" && process.env && process.env.NODE_DEBUG && /\bsemver\b/i.test(process.env.NODE_DEBUG) ? (...t) => console.error("SEMVER", ...t) : () => {
  }), $e;
}
var Ht;
function se() {
  return Ht || (Ht = 1, function(n, t) {
    const {
      MAX_SAFE_COMPONENT_LENGTH: e,
      MAX_SAFE_BUILD_LENGTH: r,
      MAX_LENGTH: s
    } = ve(), i = Ee();
    t = n.exports = {};
    const a = t.re = [], u = t.safeRe = [], c = t.src = [], l = t.safeSrc = [], o = t.t = {};
    let f = 0;
    const h = "[a-zA-Z0-9-]", p = [
      ["\\s", 1],
      ["\\d", s],
      [h, r]
    ], w = (E) => {
      for (const [T, M] of p)
        E = E.split(`${T}*`).join(`${T}{0,${M}}`).split(`${T}+`).join(`${T}{1,${M}}`);
      return E;
    }, m = (E, T, M) => {
      const R = w(T), g = f++;
      i(E, g, T), o[E] = g, c[g] = T, l[g] = R, a[g] = new RegExp(T, M ? "g" : void 0), u[g] = new RegExp(R, M ? "g" : void 0);
    };
    m("NUMERICIDENTIFIER", "0|[1-9]\\d*"), m("NUMERICIDENTIFIERLOOSE", "\\d+"), m("NONNUMERICIDENTIFIER", `\\d*[a-zA-Z-]${h}*`), m("MAINVERSION", `(${c[o.NUMERICIDENTIFIER]})\\.(${c[o.NUMERICIDENTIFIER]})\\.(${c[o.NUMERICIDENTIFIER]})`), m("MAINVERSIONLOOSE", `(${c[o.NUMERICIDENTIFIERLOOSE]})\\.(${c[o.NUMERICIDENTIFIERLOOSE]})\\.(${c[o.NUMERICIDENTIFIERLOOSE]})`), m("PRERELEASEIDENTIFIER", `(?:${c[o.NONNUMERICIDENTIFIER]}|${c[o.NUMERICIDENTIFIER]})`), m("PRERELEASEIDENTIFIERLOOSE", `(?:${c[o.NONNUMERICIDENTIFIER]}|${c[o.NUMERICIDENTIFIERLOOSE]})`), m("PRERELEASE", `(?:-(${c[o.PRERELEASEIDENTIFIER]}(?:\\.${c[o.PRERELEASEIDENTIFIER]})*))`), m("PRERELEASELOOSE", `(?:-?(${c[o.PRERELEASEIDENTIFIERLOOSE]}(?:\\.${c[o.PRERELEASEIDENTIFIERLOOSE]})*))`), m("BUILDIDENTIFIER", `${h}+`), m("BUILD", `(?:\\+(${c[o.BUILDIDENTIFIER]}(?:\\.${c[o.BUILDIDENTIFIER]})*))`), m("FULLPLAIN", `v?${c[o.MAINVERSION]}${c[o.PRERELEASE]}?${c[o.BUILD]}?`), m("FULL", `^${c[o.FULLPLAIN]}$`), m("LOOSEPLAIN", `[v=\\s]*${c[o.MAINVERSIONLOOSE]}${c[o.PRERELEASELOOSE]}?${c[o.BUILD]}?`), m("LOOSE", `^${c[o.LOOSEPLAIN]}$`), m("GTLT", "((?:<|>)?=?)"), m("XRANGEIDENTIFIERLOOSE", `${c[o.NUMERICIDENTIFIERLOOSE]}|x|X|\\*`), m("XRANGEIDENTIFIER", `${c[o.NUMERICIDENTIFIER]}|x|X|\\*`), m("XRANGEPLAIN", `[v=\\s]*(${c[o.XRANGEIDENTIFIER]})(?:\\.(${c[o.XRANGEIDENTIFIER]})(?:\\.(${c[o.XRANGEIDENTIFIER]})(?:${c[o.PRERELEASE]})?${c[o.BUILD]}?)?)?`), m("XRANGEPLAINLOOSE", `[v=\\s]*(${c[o.XRANGEIDENTIFIERLOOSE]})(?:\\.(${c[o.XRANGEIDENTIFIERLOOSE]})(?:\\.(${c[o.XRANGEIDENTIFIERLOOSE]})(?:${c[o.PRERELEASELOOSE]})?${c[o.BUILD]}?)?)?`), m("XRANGE", `^${c[o.GTLT]}\\s*${c[o.XRANGEPLAIN]}$`), m("XRANGELOOSE", `^${c[o.GTLT]}\\s*${c[o.XRANGEPLAINLOOSE]}$`), m("COERCEPLAIN", `(^|[^\\d])(\\d{1,${e}})(?:\\.(\\d{1,${e}}))?(?:\\.(\\d{1,${e}}))?`), m("COERCE", `${c[o.COERCEPLAIN]}(?:$|[^\\d])`), m("COERCEFULL", c[o.COERCEPLAIN] + `(?:${c[o.PRERELEASE]})?(?:${c[o.BUILD]})?(?:$|[^\\d])`), m("COERCERTL", c[o.COERCE], !0), m("COERCERTLFULL", c[o.COERCEFULL], !0), m("LONETILDE", "(?:~>?)"), m("TILDETRIM", `(\\s*)${c[o.LONETILDE]}\\s+`, !0), t.tildeTrimReplace = "$1~", m("TILDE", `^${c[o.LONETILDE]}${c[o.XRANGEPLAIN]}$`), m("TILDELOOSE", `^${c[o.LONETILDE]}${c[o.XRANGEPLAINLOOSE]}$`), m("LONECARET", "(?:\\^)"), m("CARETTRIM", `(\\s*)${c[o.LONECARET]}\\s+`, !0), t.caretTrimReplace = "$1^", m("CARET", `^${c[o.LONECARET]}${c[o.XRANGEPLAIN]}$`), m("CARETLOOSE", `^${c[o.LONECARET]}${c[o.XRANGEPLAINLOOSE]}$`), m("COMPARATORLOOSE", `^${c[o.GTLT]}\\s*(${c[o.LOOSEPLAIN]})$|^$`), m("COMPARATOR", `^${c[o.GTLT]}\\s*(${c[o.FULLPLAIN]})$|^$`), m("COMPARATORTRIM", `(\\s*)${c[o.GTLT]}\\s*(${c[o.LOOSEPLAIN]}|${c[o.XRANGEPLAIN]})`, !0), t.comparatorTrimReplace = "$1$2$3", m("HYPHENRANGE", `^\\s*(${c[o.XRANGEPLAIN]})\\s+-\\s+(${c[o.XRANGEPLAIN]})\\s*$`), m("HYPHENRANGELOOSE", `^\\s*(${c[o.XRANGEPLAINLOOSE]})\\s+-\\s+(${c[o.XRANGEPLAINLOOSE]})\\s*$`), m("STAR", "(<|>)?=?\\s*\\*"), m("GTE0", "^\\s*>=\\s*0\\.0\\.0\\s*$"), m("GTE0PRE", "^\\s*>=\\s*0\\.0\\.0-0\\s*$");
  }(de, de.exports)), de.exports;
}
var Ne, Jt;
function St() {
  if (Jt) return Ne;
  Jt = 1;
  const n = Object.freeze({ loose: !0 }), t = Object.freeze({});
  return Ne = (r) => r ? typeof r != "object" ? n : r : t, Ne;
}
var be, Yt;
function Gr() {
  if (Yt) return be;
  Yt = 1;
  const n = /^[0-9]+$/, t = (r, s) => {
    if (typeof r == "number" && typeof s == "number")
      return r === s ? 0 : r < s ? -1 : 1;
    const i = n.test(r), a = n.test(s);
    return i && a && (r = +r, s = +s), r === s ? 0 : i && !a ? -1 : a && !i ? 1 : r < s ? -1 : 1;
  };
  return be = {
    compareIdentifiers: t,
    rcompareIdentifiers: (r, s) => t(s, r)
  }, be;
}
var Me, Kt;
function U() {
  if (Kt) return Me;
  Kt = 1;
  const n = Ee(), { MAX_LENGTH: t, MAX_SAFE_INTEGER: e } = ve(), { safeRe: r, t: s } = se(), i = St(), { compareIdentifiers: a } = Gr();
  class u {
    constructor(l, o) {
      if (o = i(o), l instanceof u) {
        if (l.loose === !!o.loose && l.includePrerelease === !!o.includePrerelease)
          return l;
        l = l.version;
      } else if (typeof l != "string")
        throw new TypeError(`Invalid version. Must be a string. Got type "${typeof l}".`);
      if (l.length > t)
        throw new TypeError(
          `version is longer than ${t} characters`
        );
      n("SemVer", l, o), this.options = o, this.loose = !!o.loose, this.includePrerelease = !!o.includePrerelease;
      const f = l.trim().match(o.loose ? r[s.LOOSE] : r[s.FULL]);
      if (!f)
        throw new TypeError(`Invalid Version: ${l}`);
      if (this.raw = l, this.major = +f[1], this.minor = +f[2], this.patch = +f[3], this.major > e || this.major < 0)
        throw new TypeError("Invalid major version");
      if (this.minor > e || this.minor < 0)
        throw new TypeError("Invalid minor version");
      if (this.patch > e || this.patch < 0)
        throw new TypeError("Invalid patch version");
      f[4] ? this.prerelease = f[4].split(".").map((h) => {
        if (/^[0-9]+$/.test(h)) {
          const p = +h;
          if (p >= 0 && p < e)
            return p;
        }
        return h;
      }) : this.prerelease = [], this.build = f[5] ? f[5].split(".") : [], this.format();
    }
    format() {
      return this.version = `${this.major}.${this.minor}.${this.patch}`, this.prerelease.length && (this.version += `-${this.prerelease.join(".")}`), this.version;
    }
    toString() {
      return this.version;
    }
    compare(l) {
      if (n("SemVer.compare", this.version, this.options, l), !(l instanceof u)) {
        if (typeof l == "string" && l === this.version)
          return 0;
        l = new u(l, this.options);
      }
      return l.version === this.version ? 0 : this.compareMain(l) || this.comparePre(l);
    }
    compareMain(l) {
      return l instanceof u || (l = new u(l, this.options)), this.major < l.major ? -1 : this.major > l.major ? 1 : this.minor < l.minor ? -1 : this.minor > l.minor ? 1 : this.patch < l.patch ? -1 : this.patch > l.patch ? 1 : 0;
    }
    comparePre(l) {
      if (l instanceof u || (l = new u(l, this.options)), this.prerelease.length && !l.prerelease.length)
        return -1;
      if (!this.prerelease.length && l.prerelease.length)
        return 1;
      if (!this.prerelease.length && !l.prerelease.length)
        return 0;
      let o = 0;
      do {
        const f = this.prerelease[o], h = l.prerelease[o];
        if (n("prerelease compare", o, f, h), f === void 0 && h === void 0)
          return 0;
        if (h === void 0)
          return 1;
        if (f === void 0)
          return -1;
        if (f === h)
          continue;
        return a(f, h);
      } while (++o);
    }
    compareBuild(l) {
      l instanceof u || (l = new u(l, this.options));
      let o = 0;
      do {
        const f = this.build[o], h = l.build[o];
        if (n("build compare", o, f, h), f === void 0 && h === void 0)
          return 0;
        if (h === void 0)
          return 1;
        if (f === void 0)
          return -1;
        if (f === h)
          continue;
        return a(f, h);
      } while (++o);
    }
    // preminor will bump the version up to the next minor release, and immediately
    // down to pre-release. premajor and prepatch work the same way.
    inc(l, o, f) {
      if (l.startsWith("pre")) {
        if (!o && f === !1)
          throw new Error("invalid increment argument: identifier is empty");
        if (o) {
          const h = `-${o}`.match(this.options.loose ? r[s.PRERELEASELOOSE] : r[s.PRERELEASE]);
          if (!h || h[1] !== o)
            throw new Error(`invalid identifier: ${o}`);
        }
      }
      switch (l) {
        case "premajor":
          this.prerelease.length = 0, this.patch = 0, this.minor = 0, this.major++, this.inc("pre", o, f);
          break;
        case "preminor":
          this.prerelease.length = 0, this.patch = 0, this.minor++, this.inc("pre", o, f);
          break;
        case "prepatch":
          this.prerelease.length = 0, this.inc("patch", o, f), this.inc("pre", o, f);
          break;
        // If the input is a non-prerelease version, this acts the same as
        // prepatch.
        case "prerelease":
          this.prerelease.length === 0 && this.inc("patch", o, f), this.inc("pre", o, f);
          break;
        case "release":
          if (this.prerelease.length === 0)
            throw new Error(`version ${this.raw} is not a prerelease`);
          this.prerelease.length = 0;
          break;
        case "major":
          (this.minor !== 0 || this.patch !== 0 || this.prerelease.length === 0) && this.major++, this.minor = 0, this.patch = 0, this.prerelease = [];
          break;
        case "minor":
          (this.patch !== 0 || this.prerelease.length === 0) && this.minor++, this.patch = 0, this.prerelease = [];
          break;
        case "patch":
          this.prerelease.length === 0 && this.patch++, this.prerelease = [];
          break;
        // This probably shouldn't be used publicly.
        // 1.0.0 'pre' would become 1.0.0-0 which is the wrong direction.
        case "pre": {
          const h = Number(f) ? 1 : 0;
          if (this.prerelease.length === 0)
            this.prerelease = [h];
          else {
            let p = this.prerelease.length;
            for (; --p >= 0; )
              typeof this.prerelease[p] == "number" && (this.prerelease[p]++, p = -2);
            if (p === -1) {
              if (o === this.prerelease.join(".") && f === !1)
                throw new Error("invalid increment argument: identifier already exists");
              this.prerelease.push(h);
            }
          }
          if (o) {
            let p = [o, h];
            f === !1 && (p = [o]), a(this.prerelease[0], o) === 0 ? isNaN(this.prerelease[1]) && (this.prerelease = p) : this.prerelease = p;
          }
          break;
        }
        default:
          throw new Error(`invalid increment argument: ${l}`);
      }
      return this.raw = this.format(), this.build.length && (this.raw += `+${this.build.join(".")}`), this;
    }
  }
  return Me = u, Me;
}
var Pe, Qt;
function Z() {
  if (Qt) return Pe;
  Qt = 1;
  const n = U();
  return Pe = (e, r, s = !1) => {
    if (e instanceof n)
      return e;
    try {
      return new n(e, r);
    } catch (i) {
      if (!s)
        return null;
      throw i;
    }
  }, Pe;
}
var qe, Zt;
function Is() {
  if (Zt) return qe;
  Zt = 1;
  const n = Z();
  return qe = (e, r) => {
    const s = n(e, r);
    return s ? s.version : null;
  }, qe;
}
var De, er;
function Ss() {
  if (er) return De;
  er = 1;
  const n = Z();
  return De = (e, r) => {
    const s = n(e.trim().replace(/^[=v]+/, ""), r);
    return s ? s.version : null;
  }, De;
}
var Fe, tr;
function Rs() {
  if (tr) return Fe;
  tr = 1;
  const n = U();
  return Fe = (e, r, s, i, a) => {
    typeof s == "string" && (a = i, i = s, s = void 0);
    try {
      return new n(
        e instanceof n ? e.version : e,
        s
      ).inc(r, i, a).version;
    } catch {
      return null;
    }
  }, Fe;
}
var je, rr;
function Ts() {
  if (rr) return je;
  rr = 1;
  const n = Z();
  return je = (e, r) => {
    const s = n(e, null, !0), i = n(r, null, !0), a = s.compare(i);
    if (a === 0)
      return null;
    const u = a > 0, c = u ? s : i, l = u ? i : s, o = !!c.prerelease.length;
    if (!!l.prerelease.length && !o) {
      if (!l.patch && !l.minor)
        return "major";
      if (l.compareMain(c) === 0)
        return l.minor && !l.patch ? "minor" : "patch";
    }
    const h = o ? "pre" : "";
    return s.major !== i.major ? h + "major" : s.minor !== i.minor ? h + "minor" : s.patch !== i.patch ? h + "patch" : "prerelease";
  }, je;
}
var Ge, sr;
function Cs() {
  if (sr) return Ge;
  sr = 1;
  const n = U();
  return Ge = (e, r) => new n(e, r).major, Ge;
}
var ke, nr;
function As() {
  if (nr) return ke;
  nr = 1;
  const n = U();
  return ke = (e, r) => new n(e, r).minor, ke;
}
var Ue, ir;
function Ls() {
  if (ir) return Ue;
  ir = 1;
  const n = U();
  return Ue = (e, r) => new n(e, r).patch, Ue;
}
var Be, ar;
function Os() {
  if (ar) return Be;
  ar = 1;
  const n = Z();
  return Be = (e, r) => {
    const s = n(e, r);
    return s && s.prerelease.length ? s.prerelease : null;
  }, Be;
}
var Ve, or;
function V() {
  if (or) return Ve;
  or = 1;
  const n = U();
  return Ve = (e, r, s) => new n(e, s).compare(new n(r, s)), Ve;
}
var Xe, ur;
function xs() {
  if (ur) return Xe;
  ur = 1;
  const n = V();
  return Xe = (e, r, s) => n(r, e, s), Xe;
}
var We, lr;
function $s() {
  if (lr) return We;
  lr = 1;
  const n = V();
  return We = (e, r) => n(e, r, !0), We;
}
var ze, cr;
function Rt() {
  if (cr) return ze;
  cr = 1;
  const n = U();
  return ze = (e, r, s) => {
    const i = new n(e, s), a = new n(r, s);
    return i.compare(a) || i.compareBuild(a);
  }, ze;
}
var He, hr;
function Ns() {
  if (hr) return He;
  hr = 1;
  const n = Rt();
  return He = (e, r) => e.sort((s, i) => n(s, i, r)), He;
}
var Je, fr;
function bs() {
  if (fr) return Je;
  fr = 1;
  const n = Rt();
  return Je = (e, r) => e.sort((s, i) => n(i, s, r)), Je;
}
var Ye, dr;
function ye() {
  if (dr) return Ye;
  dr = 1;
  const n = V();
  return Ye = (e, r, s) => n(e, r, s) > 0, Ye;
}
var Ke, pr;
function Tt() {
  if (pr) return Ke;
  pr = 1;
  const n = V();
  return Ke = (e, r, s) => n(e, r, s) < 0, Ke;
}
var Qe, mr;
function kr() {
  if (mr) return Qe;
  mr = 1;
  const n = V();
  return Qe = (e, r, s) => n(e, r, s) === 0, Qe;
}
var Ze, gr;
function Ur() {
  if (gr) return Ze;
  gr = 1;
  const n = V();
  return Ze = (e, r, s) => n(e, r, s) !== 0, Ze;
}
var et, vr;
function Ct() {
  if (vr) return et;
  vr = 1;
  const n = V();
  return et = (e, r, s) => n(e, r, s) >= 0, et;
}
var tt, Er;
function At() {
  if (Er) return tt;
  Er = 1;
  const n = V();
  return tt = (e, r, s) => n(e, r, s) <= 0, tt;
}
var rt, yr;
function Br() {
  if (yr) return rt;
  yr = 1;
  const n = kr(), t = Ur(), e = ye(), r = Ct(), s = Tt(), i = At();
  return rt = (u, c, l, o) => {
    switch (c) {
      case "===":
        return typeof u == "object" && (u = u.version), typeof l == "object" && (l = l.version), u === l;
      case "!==":
        return typeof u == "object" && (u = u.version), typeof l == "object" && (l = l.version), u !== l;
      case "":
      case "=":
      case "==":
        return n(u, l, o);
      case "!=":
        return t(u, l, o);
      case ">":
        return e(u, l, o);
      case ">=":
        return r(u, l, o);
      case "<":
        return s(u, l, o);
      case "<=":
        return i(u, l, o);
      default:
        throw new TypeError(`Invalid operator: ${c}`);
    }
  }, rt;
}
var st, _r;
function Ms() {
  if (_r) return st;
  _r = 1;
  const n = U(), t = Z(), { safeRe: e, t: r } = se();
  return st = (i, a) => {
    if (i instanceof n)
      return i;
    if (typeof i == "number" && (i = String(i)), typeof i != "string")
      return null;
    a = a || {};
    let u = null;
    if (!a.rtl)
      u = i.match(a.includePrerelease ? e[r.COERCEFULL] : e[r.COERCE]);
    else {
      const p = a.includePrerelease ? e[r.COERCERTLFULL] : e[r.COERCERTL];
      let w;
      for (; (w = p.exec(i)) && (!u || u.index + u[0].length !== i.length); )
        (!u || w.index + w[0].length !== u.index + u[0].length) && (u = w), p.lastIndex = w.index + w[1].length + w[2].length;
      p.lastIndex = -1;
    }
    if (u === null)
      return null;
    const c = u[2], l = u[3] || "0", o = u[4] || "0", f = a.includePrerelease && u[5] ? `-${u[5]}` : "", h = a.includePrerelease && u[6] ? `+${u[6]}` : "";
    return t(`${c}.${l}.${o}${f}${h}`, a);
  }, st;
}
var nt, wr;
function Ps() {
  if (wr) return nt;
  wr = 1;
  class n {
    constructor() {
      this.max = 1e3, this.map = /* @__PURE__ */ new Map();
    }
    get(e) {
      const r = this.map.get(e);
      if (r !== void 0)
        return this.map.delete(e), this.map.set(e, r), r;
    }
    delete(e) {
      return this.map.delete(e);
    }
    set(e, r) {
      if (!this.delete(e) && r !== void 0) {
        if (this.map.size >= this.max) {
          const i = this.map.keys().next().value;
          this.delete(i);
        }
        this.map.set(e, r);
      }
      return this;
    }
  }
  return nt = n, nt;
}
var it, Ir;
function X() {
  if (Ir) return it;
  Ir = 1;
  const n = /\s+/g;
  class t {
    constructor(_, L) {
      if (L = s(L), _ instanceof t)
        return _.loose === !!L.loose && _.includePrerelease === !!L.includePrerelease ? _ : new t(_.raw, L);
      if (_ instanceof i)
        return this.raw = _.value, this.set = [[_]], this.formatted = void 0, this;
      if (this.options = L, this.loose = !!L.loose, this.includePrerelease = !!L.includePrerelease, this.raw = _.trim().replace(n, " "), this.set = this.raw.split("||").map((C) => this.parseRange(C.trim())).filter((C) => C.length), !this.set.length)
        throw new TypeError(`Invalid SemVer Range: ${this.raw}`);
      if (this.set.length > 1) {
        const C = this.set[0];
        if (this.set = this.set.filter((O) => !m(O[0])), this.set.length === 0)
          this.set = [C];
        else if (this.set.length > 1) {
          for (const O of this.set)
            if (O.length === 1 && E(O[0])) {
              this.set = [O];
              break;
            }
        }
      }
      this.formatted = void 0;
    }
    get range() {
      if (this.formatted === void 0) {
        this.formatted = "";
        for (let _ = 0; _ < this.set.length; _++) {
          _ > 0 && (this.formatted += "||");
          const L = this.set[_];
          for (let C = 0; C < L.length; C++)
            C > 0 && (this.formatted += " "), this.formatted += L[C].toString().trim();
        }
      }
      return this.formatted;
    }
    format() {
      return this.range;
    }
    toString() {
      return this.range;
    }
    parseRange(_) {
      const C = ((this.options.includePrerelease && p) | (this.options.loose && w)) + ":" + _, O = r.get(C);
      if (O)
        return O;
      const A = this.options.loose, x = A ? c[l.HYPHENRANGELOOSE] : c[l.HYPHENRANGE];
      _ = _.replace(x, W(this.options.includePrerelease)), a("hyphen replace", _), _ = _.replace(c[l.COMPARATORTRIM], o), a("comparator trim", _), _ = _.replace(c[l.TILDETRIM], f), a("tilde trim", _), _ = _.replace(c[l.CARETTRIM], h), a("caret trim", _);
      let q = _.split(" ").map((F) => M(F, this.options)).join(" ").split(/\s+/).map((F) => G(F, this.options));
      A && (q = q.filter((F) => (a("loose invalid filter", F, this.options), !!F.match(c[l.COMPARATORLOOSE])))), a("range list", q);
      const b = /* @__PURE__ */ new Map(), D = q.map((F) => new i(F, this.options));
      for (const F of D) {
        if (m(F))
          return [F];
        b.set(F.value, F);
      }
      b.size > 1 && b.has("") && b.delete("");
      const k = [...b.values()];
      return r.set(C, k), k;
    }
    intersects(_, L) {
      if (!(_ instanceof t))
        throw new TypeError("a Range is required");
      return this.set.some((C) => T(C, L) && _.set.some((O) => T(O, L) && C.every((A) => O.every((x) => A.intersects(x, L)))));
    }
    // if ANY of the sets match ALL of its comparators, then pass
    test(_) {
      if (!_)
        return !1;
      if (typeof _ == "string")
        try {
          _ = new u(_, this.options);
        } catch {
          return !1;
        }
      for (let L = 0; L < this.set.length; L++)
        if (Y(this.set[L], _, this.options))
          return !0;
      return !1;
    }
  }
  it = t;
  const e = Ps(), r = new e(), s = St(), i = _e(), a = Ee(), u = U(), {
    safeRe: c,
    t: l,
    comparatorTrimReplace: o,
    tildeTrimReplace: f,
    caretTrimReplace: h
  } = se(), { FLAG_INCLUDE_PRERELEASE: p, FLAG_LOOSE: w } = ve(), m = (S) => S.value === "<0.0.0-0", E = (S) => S.value === "", T = (S, _) => {
    let L = !0;
    const C = S.slice();
    let O = C.pop();
    for (; L && C.length; )
      L = C.every((A) => O.intersects(A, _)), O = C.pop();
    return L;
  }, M = (S, _) => (S = S.replace(c[l.BUILD], ""), a("comp", S, _), S = v(S, _), a("caret", S), S = g(S, _), a("tildes", S), S = y(S, _), a("xrange", S), S = N(S, _), a("stars", S), S), R = (S) => !S || S.toLowerCase() === "x" || S === "*", g = (S, _) => S.trim().split(/\s+/).map((L) => d(L, _)).join(" "), d = (S, _) => {
    const L = _.loose ? c[l.TILDELOOSE] : c[l.TILDE];
    return S.replace(L, (C, O, A, x, q) => {
      a("tilde", S, C, O, A, x, q);
      let b;
      return R(O) ? b = "" : R(A) ? b = `>=${O}.0.0 <${+O + 1}.0.0-0` : R(x) ? b = `>=${O}.${A}.0 <${O}.${+A + 1}.0-0` : q ? (a("replaceTilde pr", q), b = `>=${O}.${A}.${x}-${q} <${O}.${+A + 1}.0-0`) : b = `>=${O}.${A}.${x} <${O}.${+A + 1}.0-0`, a("tilde return", b), b;
    });
  }, v = (S, _) => S.trim().split(/\s+/).map((L) => I(L, _)).join(" "), I = (S, _) => {
    a("caret", S, _);
    const L = _.loose ? c[l.CARETLOOSE] : c[l.CARET], C = _.includePrerelease ? "-0" : "";
    return S.replace(L, (O, A, x, q, b) => {
      a("caret", S, O, A, x, q, b);
      let D;
      return R(A) ? D = "" : R(x) ? D = `>=${A}.0.0${C} <${+A + 1}.0.0-0` : R(q) ? A === "0" ? D = `>=${A}.${x}.0${C} <${A}.${+x + 1}.0-0` : D = `>=${A}.${x}.0${C} <${+A + 1}.0.0-0` : b ? (a("replaceCaret pr", b), A === "0" ? x === "0" ? D = `>=${A}.${x}.${q}-${b} <${A}.${x}.${+q + 1}-0` : D = `>=${A}.${x}.${q}-${b} <${A}.${+x + 1}.0-0` : D = `>=${A}.${x}.${q}-${b} <${+A + 1}.0.0-0`) : (a("no pr"), A === "0" ? x === "0" ? D = `>=${A}.${x}.${q}${C} <${A}.${x}.${+q + 1}-0` : D = `>=${A}.${x}.${q}${C} <${A}.${+x + 1}.0-0` : D = `>=${A}.${x}.${q} <${+A + 1}.0.0-0`), a("caret return", D), D;
    });
  }, y = (S, _) => (a("replaceXRanges", S, _), S.split(/\s+/).map((L) => P(L, _)).join(" ")), P = (S, _) => {
    S = S.trim();
    const L = _.loose ? c[l.XRANGELOOSE] : c[l.XRANGE];
    return S.replace(L, (C, O, A, x, q, b) => {
      a("xRange", S, C, O, A, x, q, b);
      const D = R(A), k = D || R(x), F = k || R(q), ee = F;
      return O === "=" && ee && (O = ""), b = _.includePrerelease ? "-0" : "", D ? O === ">" || O === "<" ? C = "<0.0.0-0" : C = "*" : O && ee ? (k && (x = 0), q = 0, O === ">" ? (O = ">=", k ? (A = +A + 1, x = 0, q = 0) : (x = +x + 1, q = 0)) : O === "<=" && (O = "<", k ? A = +A + 1 : x = +x + 1), O === "<" && (b = "-0"), C = `${O + A}.${x}.${q}${b}`) : k ? C = `>=${A}.0.0${b} <${+A + 1}.0.0-0` : F && (C = `>=${A}.${x}.0${b} <${A}.${+x + 1}.0-0`), a("xRange return", C), C;
    });
  }, N = (S, _) => (a("replaceStars", S, _), S.trim().replace(c[l.STAR], "")), G = (S, _) => (a("replaceGTE0", S, _), S.trim().replace(c[_.includePrerelease ? l.GTE0PRE : l.GTE0], "")), W = (S) => (_, L, C, O, A, x, q, b, D, k, F, ee) => (R(C) ? L = "" : R(O) ? L = `>=${C}.0.0${S ? "-0" : ""}` : R(A) ? L = `>=${C}.${O}.0${S ? "-0" : ""}` : x ? L = `>=${L}` : L = `>=${L}${S ? "-0" : ""}`, R(D) ? b = "" : R(k) ? b = `<${+D + 1}.0.0-0` : R(F) ? b = `<${D}.${+k + 1}.0-0` : ee ? b = `<=${D}.${k}.${F}-${ee}` : S ? b = `<${D}.${k}.${+F + 1}-0` : b = `<=${b}`, `${L} ${b}`.trim()), Y = (S, _, L) => {
    for (let C = 0; C < S.length; C++)
      if (!S[C].test(_))
        return !1;
    if (_.prerelease.length && !L.includePrerelease) {
      for (let C = 0; C < S.length; C++)
        if (a(S[C].semver), S[C].semver !== i.ANY && S[C].semver.prerelease.length > 0) {
          const O = S[C].semver;
          if (O.major === _.major && O.minor === _.minor && O.patch === _.patch)
            return !0;
        }
      return !1;
    }
    return !0;
  };
  return it;
}
var at, Sr;
function _e() {
  if (Sr) return at;
  Sr = 1;
  const n = Symbol("SemVer ANY");
  class t {
    static get ANY() {
      return n;
    }
    constructor(o, f) {
      if (f = e(f), o instanceof t) {
        if (o.loose === !!f.loose)
          return o;
        o = o.value;
      }
      o = o.trim().split(/\s+/).join(" "), a("comparator", o, f), this.options = f, this.loose = !!f.loose, this.parse(o), this.semver === n ? this.value = "" : this.value = this.operator + this.semver.version, a("comp", this);
    }
    parse(o) {
      const f = this.options.loose ? r[s.COMPARATORLOOSE] : r[s.COMPARATOR], h = o.match(f);
      if (!h)
        throw new TypeError(`Invalid comparator: ${o}`);
      this.operator = h[1] !== void 0 ? h[1] : "", this.operator === "=" && (this.operator = ""), h[2] ? this.semver = new u(h[2], this.options.loose) : this.semver = n;
    }
    toString() {
      return this.value;
    }
    test(o) {
      if (a("Comparator.test", o, this.options.loose), this.semver === n || o === n)
        return !0;
      if (typeof o == "string")
        try {
          o = new u(o, this.options);
        } catch {
          return !1;
        }
      return i(o, this.operator, this.semver, this.options);
    }
    intersects(o, f) {
      if (!(o instanceof t))
        throw new TypeError("a Comparator is required");
      return this.operator === "" ? this.value === "" ? !0 : new c(o.value, f).test(this.value) : o.operator === "" ? o.value === "" ? !0 : new c(this.value, f).test(o.semver) : (f = e(f), f.includePrerelease && (this.value === "<0.0.0-0" || o.value === "<0.0.0-0") || !f.includePrerelease && (this.value.startsWith("<0.0.0") || o.value.startsWith("<0.0.0")) ? !1 : !!(this.operator.startsWith(">") && o.operator.startsWith(">") || this.operator.startsWith("<") && o.operator.startsWith("<") || this.semver.version === o.semver.version && this.operator.includes("=") && o.operator.includes("=") || i(this.semver, "<", o.semver, f) && this.operator.startsWith(">") && o.operator.startsWith("<") || i(this.semver, ">", o.semver, f) && this.operator.startsWith("<") && o.operator.startsWith(">")));
    }
  }
  at = t;
  const e = St(), { safeRe: r, t: s } = se(), i = Br(), a = Ee(), u = U(), c = X();
  return at;
}
var ot, Rr;
function we() {
  if (Rr) return ot;
  Rr = 1;
  const n = X();
  return ot = (e, r, s) => {
    try {
      r = new n(r, s);
    } catch {
      return !1;
    }
    return r.test(e);
  }, ot;
}
var ut, Tr;
function qs() {
  if (Tr) return ut;
  Tr = 1;
  const n = X();
  return ut = (e, r) => new n(e, r).set.map((s) => s.map((i) => i.value).join(" ").trim().split(" ")), ut;
}
var lt, Cr;
function Ds() {
  if (Cr) return lt;
  Cr = 1;
  const n = U(), t = X();
  return lt = (r, s, i) => {
    let a = null, u = null, c = null;
    try {
      c = new t(s, i);
    } catch {
      return null;
    }
    return r.forEach((l) => {
      c.test(l) && (!a || u.compare(l) === -1) && (a = l, u = new n(a, i));
    }), a;
  }, lt;
}
var ct, Ar;
function Fs() {
  if (Ar) return ct;
  Ar = 1;
  const n = U(), t = X();
  return ct = (r, s, i) => {
    let a = null, u = null, c = null;
    try {
      c = new t(s, i);
    } catch {
      return null;
    }
    return r.forEach((l) => {
      c.test(l) && (!a || u.compare(l) === 1) && (a = l, u = new n(a, i));
    }), a;
  }, ct;
}
var ht, Lr;
function js() {
  if (Lr) return ht;
  Lr = 1;
  const n = U(), t = X(), e = ye();
  return ht = (s, i) => {
    s = new t(s, i);
    let a = new n("0.0.0");
    if (s.test(a) || (a = new n("0.0.0-0"), s.test(a)))
      return a;
    a = null;
    for (let u = 0; u < s.set.length; ++u) {
      const c = s.set[u];
      let l = null;
      c.forEach((o) => {
        const f = new n(o.semver.version);
        switch (o.operator) {
          case ">":
            f.prerelease.length === 0 ? f.patch++ : f.prerelease.push(0), f.raw = f.format();
          /* fallthrough */
          case "":
          case ">=":
            (!l || e(f, l)) && (l = f);
            break;
          case "<":
          case "<=":
            break;
          /* istanbul ignore next */
          default:
            throw new Error(`Unexpected operation: ${o.operator}`);
        }
      }), l && (!a || e(a, l)) && (a = l);
    }
    return a && s.test(a) ? a : null;
  }, ht;
}
var ft, Or;
function Gs() {
  if (Or) return ft;
  Or = 1;
  const n = X();
  return ft = (e, r) => {
    try {
      return new n(e, r).range || "*";
    } catch {
      return null;
    }
  }, ft;
}
var dt, xr;
function Lt() {
  if (xr) return dt;
  xr = 1;
  const n = U(), t = _e(), { ANY: e } = t, r = X(), s = we(), i = ye(), a = Tt(), u = At(), c = Ct();
  return dt = (o, f, h, p) => {
    o = new n(o, p), f = new r(f, p);
    let w, m, E, T, M;
    switch (h) {
      case ">":
        w = i, m = u, E = a, T = ">", M = ">=";
        break;
      case "<":
        w = a, m = c, E = i, T = "<", M = "<=";
        break;
      default:
        throw new TypeError('Must provide a hilo val of "<" or ">"');
    }
    if (s(o, f, p))
      return !1;
    for (let R = 0; R < f.set.length; ++R) {
      const g = f.set[R];
      let d = null, v = null;
      if (g.forEach((I) => {
        I.semver === e && (I = new t(">=0.0.0")), d = d || I, v = v || I, w(I.semver, d.semver, p) ? d = I : E(I.semver, v.semver, p) && (v = I);
      }), d.operator === T || d.operator === M || (!v.operator || v.operator === T) && m(o, v.semver))
        return !1;
      if (v.operator === M && E(o, v.semver))
        return !1;
    }
    return !0;
  }, dt;
}
var pt, $r;
function ks() {
  if ($r) return pt;
  $r = 1;
  const n = Lt();
  return pt = (e, r, s) => n(e, r, ">", s), pt;
}
var mt, Nr;
function Us() {
  if (Nr) return mt;
  Nr = 1;
  const n = Lt();
  return mt = (e, r, s) => n(e, r, "<", s), mt;
}
var gt, br;
function Bs() {
  if (br) return gt;
  br = 1;
  const n = X();
  return gt = (e, r, s) => (e = new n(e, s), r = new n(r, s), e.intersects(r, s)), gt;
}
var vt, Mr;
function Vs() {
  if (Mr) return vt;
  Mr = 1;
  const n = we(), t = V();
  return vt = (e, r, s) => {
    const i = [];
    let a = null, u = null;
    const c = e.sort((h, p) => t(h, p, s));
    for (const h of c)
      n(h, r, s) ? (u = h, a || (a = h)) : (u && i.push([a, u]), u = null, a = null);
    a && i.push([a, null]);
    const l = [];
    for (const [h, p] of i)
      h === p ? l.push(h) : !p && h === c[0] ? l.push("*") : p ? h === c[0] ? l.push(`<=${p}`) : l.push(`${h} - ${p}`) : l.push(`>=${h}`);
    const o = l.join(" || "), f = typeof r.raw == "string" ? r.raw : String(r);
    return o.length < f.length ? o : r;
  }, vt;
}
var Et, Pr;
function Xs() {
  if (Pr) return Et;
  Pr = 1;
  const n = X(), t = _e(), { ANY: e } = t, r = we(), s = V(), i = (f, h, p = {}) => {
    if (f === h)
      return !0;
    f = new n(f, p), h = new n(h, p);
    let w = !1;
    e: for (const m of f.set) {
      for (const E of h.set) {
        const T = c(m, E, p);
        if (w = w || T !== null, T)
          continue e;
      }
      if (w)
        return !1;
    }
    return !0;
  }, a = [new t(">=0.0.0-0")], u = [new t(">=0.0.0")], c = (f, h, p) => {
    if (f === h)
      return !0;
    if (f.length === 1 && f[0].semver === e) {
      if (h.length === 1 && h[0].semver === e)
        return !0;
      p.includePrerelease ? f = a : f = u;
    }
    if (h.length === 1 && h[0].semver === e) {
      if (p.includePrerelease)
        return !0;
      h = u;
    }
    const w = /* @__PURE__ */ new Set();
    let m, E;
    for (const y of f)
      y.operator === ">" || y.operator === ">=" ? m = l(m, y, p) : y.operator === "<" || y.operator === "<=" ? E = o(E, y, p) : w.add(y.semver);
    if (w.size > 1)
      return null;
    let T;
    if (m && E) {
      if (T = s(m.semver, E.semver, p), T > 0)
        return null;
      if (T === 0 && (m.operator !== ">=" || E.operator !== "<="))
        return null;
    }
    for (const y of w) {
      if (m && !r(y, String(m), p) || E && !r(y, String(E), p))
        return null;
      for (const P of h)
        if (!r(y, String(P), p))
          return !1;
      return !0;
    }
    let M, R, g, d, v = E && !p.includePrerelease && E.semver.prerelease.length ? E.semver : !1, I = m && !p.includePrerelease && m.semver.prerelease.length ? m.semver : !1;
    v && v.prerelease.length === 1 && E.operator === "<" && v.prerelease[0] === 0 && (v = !1);
    for (const y of h) {
      if (d = d || y.operator === ">" || y.operator === ">=", g = g || y.operator === "<" || y.operator === "<=", m) {
        if (I && y.semver.prerelease && y.semver.prerelease.length && y.semver.major === I.major && y.semver.minor === I.minor && y.semver.patch === I.patch && (I = !1), y.operator === ">" || y.operator === ">=") {
          if (M = l(m, y, p), M === y && M !== m)
            return !1;
        } else if (m.operator === ">=" && !r(m.semver, String(y), p))
          return !1;
      }
      if (E) {
        if (v && y.semver.prerelease && y.semver.prerelease.length && y.semver.major === v.major && y.semver.minor === v.minor && y.semver.patch === v.patch && (v = !1), y.operator === "<" || y.operator === "<=") {
          if (R = o(E, y, p), R === y && R !== E)
            return !1;
        } else if (E.operator === "<=" && !r(E.semver, String(y), p))
          return !1;
      }
      if (!y.operator && (E || m) && T !== 0)
        return !1;
    }
    return !(m && g && !E && T !== 0 || E && d && !m && T !== 0 || I || v);
  }, l = (f, h, p) => {
    if (!f)
      return h;
    const w = s(f.semver, h.semver, p);
    return w > 0 ? f : w < 0 || h.operator === ">" && f.operator === ">=" ? h : f;
  }, o = (f, h, p) => {
    if (!f)
      return h;
    const w = s(f.semver, h.semver, p);
    return w < 0 ? f : w > 0 || h.operator === "<" && f.operator === "<=" ? h : f;
  };
  return Et = i, Et;
}
var yt, qr;
function Ws() {
  if (qr) return yt;
  qr = 1;
  const n = se(), t = ve(), e = U(), r = Gr(), s = Z(), i = Is(), a = Ss(), u = Rs(), c = Ts(), l = Cs(), o = As(), f = Ls(), h = Os(), p = V(), w = xs(), m = $s(), E = Rt(), T = Ns(), M = bs(), R = ye(), g = Tt(), d = kr(), v = Ur(), I = Ct(), y = At(), P = Br(), N = Ms(), G = _e(), W = X(), Y = we(), S = qs(), _ = Ds(), L = Fs(), C = js(), O = Gs(), A = Lt(), x = ks(), q = Us(), b = Bs(), D = Vs(), k = Xs();
  return yt = {
    parse: s,
    valid: i,
    clean: a,
    inc: u,
    diff: c,
    major: l,
    minor: o,
    patch: f,
    prerelease: h,
    compare: p,
    rcompare: w,
    compareLoose: m,
    compareBuild: E,
    sort: T,
    rsort: M,
    gt: R,
    lt: g,
    eq: d,
    neq: v,
    gte: I,
    lte: y,
    cmp: P,
    coerce: N,
    Comparator: G,
    Range: W,
    satisfies: Y,
    toComparators: S,
    maxSatisfying: _,
    minSatisfying: L,
    minVersion: C,
    validRange: O,
    outside: A,
    gtr: x,
    ltr: q,
    intersects: b,
    simplifyRange: D,
    subset: k,
    SemVer: e,
    re: n.re,
    src: n.src,
    tokens: n.t,
    SEMVER_SPEC_VERSION: t.SEMVER_SPEC_VERSION,
    RELEASE_TYPES: t.RELEASE_TYPES,
    compareIdentifiers: r.compareIdentifiers,
    rcompareIdentifiers: r.rcompareIdentifiers
  }, yt;
}
Ws();
new TextEncoder();
var me = { exports: {} };
me.exports;
var Dr;
function zs() {
  return Dr || (Dr = 1, function(n) {
    const e = (i = 0) => (a) => `\x1B[${38 + i};5;${a}m`, r = (i = 0) => (a, u, c) => `\x1B[${38 + i};2;${a};${u};${c}m`;
    function s() {
      const i = /* @__PURE__ */ new Map(), a = {
        modifier: {
          reset: [0, 0],
          // 21 isn't widely supported and 22 does the same thing
          bold: [1, 22],
          dim: [2, 22],
          italic: [3, 23],
          underline: [4, 24],
          overline: [53, 55],
          inverse: [7, 27],
          hidden: [8, 28],
          strikethrough: [9, 29]
        },
        color: {
          black: [30, 39],
          red: [31, 39],
          green: [32, 39],
          yellow: [33, 39],
          blue: [34, 39],
          magenta: [35, 39],
          cyan: [36, 39],
          white: [37, 39],
          // Bright color
          blackBright: [90, 39],
          redBright: [91, 39],
          greenBright: [92, 39],
          yellowBright: [93, 39],
          blueBright: [94, 39],
          magentaBright: [95, 39],
          cyanBright: [96, 39],
          whiteBright: [97, 39]
        },
        bgColor: {
          bgBlack: [40, 49],
          bgRed: [41, 49],
          bgGreen: [42, 49],
          bgYellow: [43, 49],
          bgBlue: [44, 49],
          bgMagenta: [45, 49],
          bgCyan: [46, 49],
          bgWhite: [47, 49],
          // Bright color
          bgBlackBright: [100, 49],
          bgRedBright: [101, 49],
          bgGreenBright: [102, 49],
          bgYellowBright: [103, 49],
          bgBlueBright: [104, 49],
          bgMagentaBright: [105, 49],
          bgCyanBright: [106, 49],
          bgWhiteBright: [107, 49]
        }
      };
      a.color.gray = a.color.blackBright, a.bgColor.bgGray = a.bgColor.bgBlackBright, a.color.grey = a.color.blackBright, a.bgColor.bgGrey = a.bgColor.bgBlackBright;
      for (const [u, c] of Object.entries(a)) {
        for (const [l, o] of Object.entries(c))
          a[l] = {
            open: `\x1B[${o[0]}m`,
            close: `\x1B[${o[1]}m`
          }, c[l] = a[l], i.set(o[0], o[1]);
        Object.defineProperty(a, u, {
          value: c,
          enumerable: !1
        });
      }
      return Object.defineProperty(a, "codes", {
        value: i,
        enumerable: !1
      }), a.color.close = "\x1B[39m", a.bgColor.close = "\x1B[49m", a.color.ansi256 = e(), a.color.ansi16m = r(), a.bgColor.ansi256 = e(10), a.bgColor.ansi16m = r(10), Object.defineProperties(a, {
        rgbToAnsi256: {
          value: (u, c, l) => u === c && c === l ? u < 8 ? 16 : u > 248 ? 231 : Math.round((u - 8) / 247 * 24) + 232 : 16 + 36 * Math.round(u / 255 * 5) + 6 * Math.round(c / 255 * 5) + Math.round(l / 255 * 5),
          enumerable: !1
        },
        hexToRgb: {
          value: (u) => {
            const c = /(?<colorString>[a-f\d]{6}|[a-f\d]{3})/i.exec(u.toString(16));
            if (!c)
              return [0, 0, 0];
            let { colorString: l } = c.groups;
            l.length === 3 && (l = l.split("").map((f) => f + f).join(""));
            const o = Number.parseInt(l, 16);
            return [
              o >> 16 & 255,
              o >> 8 & 255,
              o & 255
            ];
          },
          enumerable: !1
        },
        hexToAnsi256: {
          value: (u) => a.rgbToAnsi256(...a.hexToRgb(u)),
          enumerable: !1
        }
      }), a;
    }
    Object.defineProperty(n, "exports", {
      enumerable: !0,
      get: s
    });
  }(me)), me.exports;
}
var Hs = zs();
const Js = /* @__PURE__ */ jr(Hs), { color: vn } = Js;
new Set("ABCDEFGHIJKLMNOPQRSTUVXYZabcdefghijklmnopqrstuvxyz0123456789");
class Vr {
}
class Ys extends Vr {
  /**
   * Write the session into a langchain message array.
   */
  writeSession(t) {
    const e = [];
    t.initialContext.systemMessage && e.push(new hs(t.initialContext.systemMessage));
    for (const r of t.history)
      e.push(...this.writeMessageTuple(r));
    return t.nextMessage && e.push(...this.writeMessageTuple(t.nextMessage)), e.length > 0 && !(e[e.length - 1] instanceof le) && e.push(new le("Please continue.")), e;
  }
  /**
   * Write a particular message tuple into langchain types.
   */
  writeMessageTuple(t) {
    const e = [], r = Array.isArray(t.user.content) ? t.user.content.map((s) => s.type === "text" ? s.text : `[${s.type}]`).join(" ") : t.user.content;
    if (e.push(new le(r)), e.push(new cs(t.assistant.content)), t.toolResponse) {
      const s = t.toolResponse.responses.map((i) => i.content).join(`
`);
      e.push(new le(`Tool response: ${s}`));
    }
    return e;
  }
}
class Ks extends Vr {
  /**
   * Write a session into a series of UI events.
   */
  writeSession(t) {
    const e = [];
    for (const r of t.history)
      e.push(...this.writeMessageTuple(r));
    return t.nextMessage && e.push(...this.writeMessageTuple(t.nextMessage)), e;
  }
  /**
   * Write a message tuple into a series of UI events.
   */
  writeMessageTuple(t) {
    var s;
    const e = {
      id: t.user.id,
      type: "user",
      content: t.user.content,
      timestamp: t.timestamp
    }, r = {
      id: t.assistant.id,
      type: "assistant",
      content: t.assistant.content,
      timestamp: t.timestamp,
      toolCalls: (s = t.assistant.toolCalls) == null ? void 0 : s.map(
        (i) => ({
          id: i.id,
          name: i.name,
          status: i.status,
          parameters: i.args
        })
      ),
      isStreaming: t.assistant.isStreaming
    };
    return [e, r];
  }
}
class Q {
  constructor(t, e, r, s, i, a, u, c, l, o) {
    z(this, "langchainWriter");
    z(this, "uiWriter");
    this.id = t, this.title = e, this.sessionType = r, this.createdAt = s, this.lastModified = i, this.version = a, this.initialContext = u, this.history = c, this.nextMessage = l, this.executionMetadata = o;
  }
  /**
   * Get a message by its ID
   */
  getMessageById(t) {
    var e;
    return ((e = this.nextMessage) == null ? void 0 : e.id) === t ? this.nextMessage : this.history.find((r) => r.id === t);
  }
  /**
   * Get the last message in the conversation
   */
  getLastMessage() {
    if (this.nextMessage)
      return this.nextMessage;
    if (this.history.length !== 0)
      return this.history[this.history.length - 1];
  }
  /**
   * Get all tool calls that are awaiting approval
   */
  getPendingApprovals() {
    const t = [];
    this.nextMessage && t.push(...this.nextMessage.pendingApprovals);
    for (const e of this.history)
      t.push(...e.pendingApprovals);
    return t;
  }
  /**
   * Get the currently streaming message, if any
   */
  getStreamingMessage() {
    if (this.nextMessage && this.nextMessage.assistant.isStreaming)
      return this.nextMessage;
    const t = this.history.length > 0 ? this.history[this.history.length - 1] : void 0;
    if (t && t.assistant.isStreaming)
      return t;
  }
  /**
   * Get a LangChain message writer for this session
   */
  getLangchainWriter() {
    return this.langchainWriter || (this.langchainWriter = new Ys()), this.langchainWriter;
  }
  /**
   * Get a UI message writer for this session
   */
  getUIWriter() {
    return this.uiWriter || (this.uiWriter = new Ks()), this.uiWriter;
  }
  /**
   * Serialize the session to JSON format for persistence
   */
  toJSON() {
    return {
      id: this.id,
      title: this.title,
      sessionType: this.sessionType,
      createdAt: this.createdAt,
      lastModified: this.lastModified,
      version: this.version,
      initialContext: this.initialContext,
      history: this.history,
      nextMessage: this.nextMessage,
      executionMetadata: this.executionMetadata
    };
  }
  /**
   * Create a Session instance from serialized JSON data
   */
  static fromJSON(t) {
    return new Q(
      t.id,
      t.title,
      t.sessionType,
      t.createdAt,
      t.lastModified,
      t.version,
      t.initialContext,
      t.history,
      t.nextMessage,
      t.executionMetadata
    );
  }
  /**
   * Get the total number of messages in the session
   */
  getMessageCount() {
    return this.history.length + (this.nextMessage ? 1 : 0);
  }
  /**
   * Check if the session is waiting for tool responses
   */
  isWaitingForToolResponse() {
    return this.getPendingApprovals().some((e) => e.status === $.Executing);
  }
  /**
   * Check if the session has any approval requests pending
   */
  hasApprovalRequired() {
    return this.getPendingApprovals().some((e) => e.status === $.AwaitingApproval);
  }
  /**
   * Validate the session state
   */
  validate() {
    var s;
    const t = [], e = [], r = this.history.filter((i) => i.assistant.isStreaming);
    if ((s = this.nextMessage) != null && s.assistant.isStreaming && r.push(this.nextMessage), r.length > 1 && t.push({
      code: "MULTIPLE_STREAMING_MESSAGES",
      message: `Multiple streaming messages detected: ${r.length}`,
      severity: "error"
    }), r.length === 1) {
      const i = this.getLastMessage();
      i && !i.assistant.isStreaming && t.push({
        code: "STREAMING_NOT_LAST",
        message: "Streaming message must be the last message",
        severity: "error"
      });
    }
    for (const i of [...this.history, ...this.nextMessage ? [this.nextMessage] : []])
      if (i.assistant.toolCalls)
        for (const a of i.assistant.toolCalls)
          a.status === $.Completed && !i.toolResponse && t.push({
            code: "MISSING_TOOL_RESPONSE",
            message: `Tool call ${a.id} marked completed but no response found`,
            path: `message.${i.id}.toolCall.${a.id}`,
            severity: "error"
          }), a.status === $.Approved && !a.approvedAt && e.push({
            code: "MISSING_APPROVAL_TIMESTAMP",
            message: `Tool call ${a.id} approved but no approval timestamp`,
            path: `message.${i.id}.toolCall.${a.id}`,
            severity: "warning"
          }), (a.status === $.Executing || a.status === $.Completed || a.status === $.Failed) && !a.executedAt && e.push({
            code: "MISSING_EXECUTION_TIMESTAMP",
            message: `Tool call ${a.id} in status ${a.status} but no execution timestamp`,
            path: `message.${i.id}.toolCall.${a.id}`,
            severity: "warning"
          });
    for (let i = 1; i < this.history.length; i++) {
      const a = this.history[i - 1], u = this.history[i];
      u.timestamp < a.timestamp && t.push({
        code: "INVALID_MESSAGE_ORDER",
        message: `Message ${u.id} has earlier timestamp than previous message ${a.id}`,
        severity: "error"
      });
    }
    return {
      isValid: t.length === 0,
      errors: Object.freeze([...t]),
      warnings: Object.freeze([...e])
    };
  }
}
function En(n) {
  const t = j();
  return new Q(
    n.id,
    n.title,
    n.sessionType,
    t,
    t,
    0,
    n.initialContext,
    [],
    void 0,
    n.executionMetadata
  );
}
function B(n, t, e) {
  const r = j(), s = n.version + 1, i = new Q(
    n.id,
    t.title ?? n.title,
    t.sessionType ?? n.sessionType,
    n.createdAt,
    t.lastModified ?? r,
    t.version ?? s,
    t.initialContext ?? n.initialContext,
    t.history ?? n.history,
    "nextMessage" in t ? t.nextMessage : n.nextMessage,
    "executionMetadata" in t ? t.executionMetadata : n.executionMetadata
  );
  return e && (e.cacheSession(i), e.saveSessionAsync(i)), i;
}
function yn(n, t, e) {
  return B(
    n,
    {
      history: [...n.history, t]
    },
    e
  );
}
function ne(n, t) {
  return B(n, {
    nextMessage: t
  });
}
function _n(n) {
  return n.nextMessage ? B(n, {
    history: [...n.history, n.nextMessage],
    nextMessage: void 0
  }) : n;
}
function wn(n, t) {
  return B(n, { title: t });
}
function In(n, t) {
  return B(n, { executionMetadata: t });
}
function Sn(n) {
  return B(n, { executionMetadata: void 0 });
}
class Qs extends _t {
  constructor(t, e, r) {
    super(`Invalid tool call status transition from ${e} to ${r}`), this.toolCallId = t, this.fromStatus = e, this.toStatus = r, this.name = "InvalidTransitionError";
  }
  /**
   * Return the user-facing message.
   */
  get userFacingSessionErrorMessage() {
    return `Tool call status transition failed. Cannot change from ${this.fromStatus} to ${this.toStatus}.`;
  }
  /**
   * User facing callback.
   */
  get userFacingFixCallback() {
  }
}
class ie extends _t {
  constructor(t, e, r) {
    super(`Cannot ${r} tool call in status ${e}`), this.toolCallId = t, this.currentStatus = e, this.operation = r, this.name = "InvalidToolCallStateError";
  }
  /**
   * Return the user-facing message.
   */
  get userFacingSessionErrorMessage() {
    return `Tool call operation failed. Cannot ${this.operation} when status is ${this.currentStatus}.`;
  }
  /**
   * User facing callback.
   */
  get userFacingFixCallback() {
  }
}
class Zs extends _t {
  constructor(t, e) {
    super(`Tool call execution error: ${e}`), this.toolCallId = t, this.reason = e, this.name = "ToolCallExecutionError";
  }
  /**
   * Return the user-facing message.
   */
  get userFacingSessionErrorMessage() {
    return `Tool execution failed: ${this.reason}`;
  }
  /**
   * User facing callback.
   */
  get userFacingFixCallback() {
  }
}
const Ot = {
  pending: [$.AwaitingApproval, $.Executing, $.Failed],
  awaiting_approval: [$.Approved, $.Denied],
  approved: [$.Executing, $.Failed],
  denied: [],
  // Terminal state
  executing: [$.Completed, $.Failed],
  completed: [],
  // Terminal state
  failed: []
  // Terminal state
};
function Xr(n, t) {
  return Ot[n].includes(t);
}
function Rn(n) {
  return Ot[n];
}
function Tn(n) {
  return Ot[n].length === 0;
}
function en(n) {
  const t = j();
  return {
    id: n.id,
    name: n.name,
    args: n.args,
    status: $.Pending,
    requestedAt: t,
    requiresApproval: n.requiresApproval ?? !1
  };
}
function Cn(n) {
  return {
    ...en({
      ...n,
      requiresApproval: !0
    }),
    status: $.AwaitingApproval
  };
}
function ae(n, t, e) {
  if (!Xr(n.status, t))
    throw new Qs(n.id, n.status, t);
  const r = j(), s = { ...e };
  return t === $.Approved && !s.approvedAt && (s.approvedAt = r), t === $.Executing && !s.executedAt && (s.executedAt = r), (t === $.Completed || t === $.Failed) && !s.completedAt && (s.completedAt = r), {
    ...n,
    status: t,
    ...s
  };
}
function An(n, t) {
  if (n.status !== $.AwaitingApproval)
    throw new ie(n.id, n.status, "approve");
  const e = j(), r = {
    approved: !0,
    userComment: t,
    decidedAt: e
  };
  return ae(n, $.Approved, {
    approvalDecision: r,
    approvedAt: e
  });
}
function Ln(n, t) {
  if (n.status !== $.AwaitingApproval)
    throw new ie(n.id, n.status, "deny");
  const e = j(), r = {
    approved: !1,
    userComment: t,
    decidedAt: e
  };
  return ae(n, $.Denied, {
    approvalDecision: r
  });
}
function On(n, t) {
  if (![$.Pending, $.Approved].includes(n.status))
    throw new ie(n.id, n.status, "start execution for");
  const r = j(), s = {
    executionId: t,
    startTime: r
  };
  return ae(n, $.Executing, {
    executionMetadata: s,
    executedAt: r
  });
}
function xn(n, t) {
  if (n.status !== $.Executing)
    throw new ie(n.id, n.status, "complete");
  if (!n.executionMetadata)
    throw new Zs(n.id, "execution metadata is missing");
  const e = j(), r = {
    ...n.executionMetadata,
    endTime: e,
    duration: t ?? e - n.executionMetadata.startTime
  };
  return ae(n, $.Completed, {
    executionMetadata: r,
    completedAt: e
  });
}
function $n(n, t, e) {
  var u, c;
  if (![$.Pending, $.Approved, $.Executing].includes(n.status))
    throw new ie(n.id, n.status, "fail");
  const s = j(), i = ((u = n.executionMetadata) == null ? void 0 : u.startTime) ?? n.requestedAt, a = {
    executionId: ((c = n.executionMetadata) == null ? void 0 : c.executionId) ?? "unknown",
    startTime: i,
    endTime: s,
    duration: e ?? s - i,
    error: t
  };
  return ae(n, $.Failed, {
    executionMetadata: a,
    completedAt: s
  });
}
function Nn(n) {
  return {
    callId: n.callId,
    content: n.content,
    success: !0,
    executedAt: j(),
    duration: n.duration,
    metadata: n.metadata
  };
}
function bn(n) {
  return {
    callId: n.callId,
    content: n.error,
    success: !1,
    executedAt: j(),
    duration: n.duration,
    metadata: n.metadata
  };
}
function Mn(n) {
  return n.requiresApproval && n.status === $.AwaitingApproval;
}
function Pn(n) {
  return n.status === $.Executing;
}
function qn(n) {
  return n.status === $.Completed || n.status === $.Failed;
}
function Dn(n) {
  return n.status === $.Completed;
}
function Fn(n) {
  var t;
  return (t = n.executionMetadata) == null ? void 0 : t.duration;
}
class J {
  // ============================================================================
  // Factory Methods for Common Operations
  // ============================================================================
  /**
   * Create an edit to start a new user message and assistant response
   */
  static startUserMessage(t, e) {
    return new tn(t, e);
  }
  /**
   * Create an edit to update streaming content
   */
  static updateStreamingContent(t, e) {
    return new rn(t, e);
  }
  /**
   * Create an edit to add a tool call to a message
   */
  static addToolCall(t, e) {
    return new sn(t, e);
  }
  /**
   * Create an edit to update a tool call's status
   */
  static updateToolCallStatus(t, e) {
    return new nn(t, e);
  }
  /**
   * Create an edit to add a tool response
   */
  static addToolResponse(t, e) {
    return new an(t, e);
  }
  /**
   * Create an edit to complete a message (stop streaming and commit to history)
   */
  static completeMessage(t) {
    return new on(t);
  }
}
class tn extends J {
  constructor(t, e) {
    super(), this.content = t, this.context = e;
  }
  /**
   * Validate that a new user message can be started
   */
  validate(t) {
    const e = [], r = [];
    this.content.length === 0 && e.push({
      code: "EMPTY_USER_MESSAGE",
      message: "User message cannot be empty",
      severity: "error"
    });
    const s = t.getStreamingMessage();
    s && e.push({
      code: "STREAMING_MESSAGE_EXISTS",
      message: `Cannot start new message while message ${s.id} is still streaming`,
      severity: "error",
      context: { streamingMessageId: s.id }
    });
    const i = t.getPendingApprovals();
    return i.length > 0 && e.push({
      code: "PENDING_APPROVALS_EXIST",
      message: `Cannot start new message while ${i.length} tool calls await approval`,
      severity: "error",
      context: { pendingApprovalIds: i.map((a) => a.id) }
    }), {
      isValid: e.length === 0,
      errors: e,
      warnings: r
    };
  }
  /**
   * Apply the edit to start a new user message
   */
  apply(t) {
    const e = Hr({
      id: Ie(),
      content: this.content,
      contextItems: this.context
    }), r = Jr({
      id: Ie(),
      content: "",
      isStreaming: !0
    }), s = Yr({
      id: Ie(),
      user: e,
      assistant: r
    });
    return Promise.resolve(ne(t, s));
  }
}
class rn extends J {
  constructor(t, e) {
    super(), this.messageId = t, this.content = e;
  }
  /**
   * Validate that streaming content can be updated
   */
  validate(t) {
    const e = [], r = [], s = t.getMessageById(this.messageId);
    return s ? (s.assistant.isStreaming || e.push({
      code: "MESSAGE_NOT_STREAMING",
      message: `Cannot update content of non-streaming message ${this.messageId}`,
      severity: "error",
      context: { messageId: this.messageId }
    }), {
      isValid: e.length === 0,
      errors: e,
      warnings: r
    }) : (e.push({
      code: "MESSAGE_NOT_FOUND",
      message: `Message ${this.messageId} not found`,
      severity: "error",
      context: { messageId: this.messageId }
    }), { isValid: !1, errors: e, warnings: r });
  }
  /**
   * Apply the edit to update streaming content
   */
  apply(t) {
    var r;
    if (((r = t.nextMessage) == null ? void 0 : r.id) === this.messageId) {
      const s = xt(t.nextMessage, this.content);
      return Promise.resolve(ne(t, s));
    }
    const e = t.history.map((s) => s.id === this.messageId ? xt(s, this.content) : s);
    return Promise.resolve(B(t, { history: e }));
  }
}
class sn extends J {
  constructor(t, e) {
    super(), this.messageId = t, this.toolCall = e;
  }
  /**
   * Validate that a tool call can be added
   */
  validate(t) {
    var i;
    const e = [], r = [], s = t.getMessageById(this.messageId);
    return s ? (this.toolCall.id || e.push({
      code: "INVALID_TOOL_CALL",
      message: "Tool call must have an ID",
      severity: "error"
    }), this.toolCall.name || e.push({
      code: "INVALID_TOOL_CALL",
      message: "Tool call must have a name",
      severity: "error"
    }), (i = s.assistant.toolCalls) != null && i.some((a) => a.id === this.toolCall.id) && e.push({
      code: "DUPLICATE_TOOL_CALL",
      message: `Tool call with ID ${this.toolCall.id} already exists in message ${this.messageId}`,
      severity: "error",
      context: { toolCallId: this.toolCall.id, messageId: this.messageId }
    }), {
      isValid: e.length === 0,
      errors: e,
      warnings: r
    }) : (e.push({
      code: "MESSAGE_NOT_FOUND",
      message: `Message ${this.messageId} not found`,
      severity: "error",
      context: { messageId: this.messageId }
    }), { isValid: !1, errors: e, warnings: r });
  }
  /**
   * Apply the edit to add a tool call
   */
  apply(t) {
    var r;
    if (((r = t.nextMessage) == null ? void 0 : r.id) === this.messageId) {
      const s = t.nextMessage.assistant.toolCalls || [], i = {
        ...t.nextMessage.assistant,
        toolCalls: [...s, this.toolCall]
      }, a = new ge(
        t.nextMessage.id,
        t.nextMessage.timestamp,
        t.nextMessage.user,
        i,
        t.nextMessage.toolResponse
      );
      return Promise.resolve(ne(t, a));
    }
    const e = t.history.map((s) => {
      if (s.id === this.messageId) {
        const i = s.assistant.toolCalls || [], a = {
          ...s.assistant,
          toolCalls: [...i, this.toolCall]
        };
        return new ge(s.id, s.timestamp, s.user, a, s.toolResponse);
      }
      return s;
    });
    return Promise.resolve(B(t, { history: e }));
  }
}
class nn extends J {
  constructor(t, e) {
    super(), this.toolCallId = t, this.newStatus = e;
  }
  /**
   * Validate that a tool call status can be updated
   */
  validate(t) {
    var i;
    const e = [], r = [];
    let s;
    if ((i = t.nextMessage) != null && i.assistant.toolCalls && (s = t.nextMessage.assistant.toolCalls.find((a) => a.id === this.toolCallId)), !s) {
      for (const a of t.history)
        if (a.assistant.toolCalls && (s = a.assistant.toolCalls.find((u) => u.id === this.toolCallId), s))
          break;
    }
    return s ? (Xr(s.status, this.newStatus) || e.push({
      code: "INVALID_STATUS_TRANSITION",
      message: `Invalid tool call status transition from ${s.status} to ${this.newStatus}`,
      severity: "error",
      context: {
        toolCallId: this.toolCallId,
        currentStatus: s.status,
        newStatus: this.newStatus
      }
    }), {
      isValid: e.length === 0,
      errors: e,
      warnings: r
    }) : (e.push({
      code: "TOOL_CALL_NOT_FOUND",
      message: `Tool call ${this.toolCallId} not found`,
      severity: "error",
      context: { toolCallId: this.toolCallId }
    }), { isValid: !1, errors: e, warnings: r });
  }
  /**
   * Apply the edit to update tool call status
   */
  apply(t) {
    var r, s;
    if ((s = (r = t.nextMessage) == null ? void 0 : r.assistant.toolCalls) != null && s.some((i) => i.id === this.toolCallId)) {
      const i = $t(t.nextMessage, this.toolCallId, this.newStatus);
      return Promise.resolve(ne(t, i));
    }
    const e = t.history.map((i) => {
      var a;
      return (a = i.assistant.toolCalls) != null && a.some((u) => u.id === this.toolCallId) ? $t(i, this.toolCallId, this.newStatus) : i;
    });
    return Promise.resolve(B(t, { history: e }));
  }
}
class an extends J {
  constructor(t, e) {
    super(), this.messageId = t, this.response = e;
  }
  /**
   * Validate that a tool response can be added
   */
  validate(t) {
    var a;
    const e = [], r = [], s = t.getMessageById(this.messageId);
    return s ? (((a = s.assistant.toolCalls) == null ? void 0 : a.find((u) => u.id === this.response.callId)) || e.push({
      code: "TOOL_CALL_NOT_FOUND",
      message: `Tool call ${this.response.callId} not found in message ${this.messageId}`,
      severity: "error",
      context: { toolCallId: this.response.callId, messageId: this.messageId }
    }), this.response.content || r.push({
      code: "EMPTY_TOOL_RESPONSE",
      message: "Tool response has empty content",
      severity: "warning",
      context: { toolCallId: this.response.callId }
    }), {
      isValid: e.length === 0,
      errors: e,
      warnings: r
    }) : (e.push({
      code: "MESSAGE_NOT_FOUND",
      message: `Message ${this.messageId} not found`,
      severity: "error",
      context: { messageId: this.messageId }
    }), { isValid: !1, errors: e, warnings: r });
  }
  /**
   * Apply the edit to add a tool response
   */
  apply(t) {
    var r;
    if (((r = t.nextMessage) == null ? void 0 : r.id) === this.messageId) {
      const s = Nt(t.nextMessage, this.response);
      return Promise.resolve(ne(t, s));
    }
    const e = t.history.map((s) => s.id === this.messageId ? Nt(s, this.response) : s);
    return Promise.resolve(B(t, { history: e }));
  }
}
class on extends J {
  constructor(t) {
    super(), this.messageId = t;
  }
  /**
   * Validate that a message can be completed
   */
  validate(t) {
    const e = [], r = [], s = t.getMessageById(this.messageId);
    return s ? (s.assistant.isStreaming || r.push({
      code: "MESSAGE_ALREADY_COMPLETE",
      message: `Message ${this.messageId} is already complete`,
      severity: "warning",
      context: { messageId: this.messageId }
    }), s.pendingApprovals.length > 0 && e.push({
      code: "PENDING_APPROVALS_EXIST",
      message: `Cannot complete message ${this.messageId} with ${s.pendingApprovals.length} pending approvals`,
      severity: "error",
      context: {
        messageId: this.messageId,
        pendingApprovalIds: s.pendingApprovals.map((i) => i.id)
      }
    }), {
      isValid: e.length === 0,
      errors: e,
      warnings: r
    }) : (e.push({
      code: "MESSAGE_NOT_FOUND",
      message: `Message ${this.messageId} not found`,
      severity: "error",
      context: { messageId: this.messageId }
    }), { isValid: !1, errors: e, warnings: r });
  }
  /**
   * Apply the edit to complete a message
   */
  apply(t) {
    var r;
    if (((r = t.nextMessage) == null ? void 0 : r.id) === this.messageId) {
      const s = new ge(
        t.nextMessage.id,
        t.nextMessage.timestamp,
        t.nextMessage.user,
        {
          ...t.nextMessage.assistant,
          isStreaming: !1
        },
        t.nextMessage.toolResponse
      );
      return Promise.resolve(
        B(t, {
          history: [...t.history, s],
          nextMessage: void 0
        })
      );
    }
    const e = t.history.map((s) => s.id === this.messageId ? new ge(
      s.id,
      s.timestamp,
      s.user,
      {
        ...s.assistant,
        isStreaming: !1
      },
      s.toolResponse
    ) : s);
    return Promise.resolve(B(t, { history: e }));
  }
}
var pe = { exports: {} }, Fr;
function un() {
  if (Fr) return pe.exports;
  Fr = 1;
  var n = typeof Reflect == "object" ? Reflect : null, t = n && typeof n.apply == "function" ? n.apply : function(d, v, I) {
    return Function.prototype.apply.call(d, v, I);
  }, e;
  n && typeof n.ownKeys == "function" ? e = n.ownKeys : Object.getOwnPropertySymbols ? e = function(d) {
    return Object.getOwnPropertyNames(d).concat(Object.getOwnPropertySymbols(d));
  } : e = function(d) {
    return Object.getOwnPropertyNames(d);
  };
  function r(g) {
    console && console.warn && console.warn(g);
  }
  var s = Number.isNaN || function(d) {
    return d !== d;
  };
  function i() {
    i.init.call(this);
  }
  pe.exports = i, pe.exports.once = T, i.EventEmitter = i, i.prototype._events = void 0, i.prototype._eventsCount = 0, i.prototype._maxListeners = void 0;
  var a = 10;
  function u(g) {
    if (typeof g != "function")
      throw new TypeError('The "listener" argument must be of type Function. Received type ' + typeof g);
  }
  Object.defineProperty(i, "defaultMaxListeners", {
    enumerable: !0,
    get: function() {
      return a;
    },
    set: function(g) {
      if (typeof g != "number" || g < 0 || s(g))
        throw new RangeError('The value of "defaultMaxListeners" is out of range. It must be a non-negative number. Received ' + g + ".");
      a = g;
    }
  }), i.init = function() {
    (this._events === void 0 || this._events === Object.getPrototypeOf(this)._events) && (this._events = /* @__PURE__ */ Object.create(null), this._eventsCount = 0), this._maxListeners = this._maxListeners || void 0;
  }, i.prototype.setMaxListeners = function(d) {
    if (typeof d != "number" || d < 0 || s(d))
      throw new RangeError('The value of "n" is out of range. It must be a non-negative number. Received ' + d + ".");
    return this._maxListeners = d, this;
  };
  function c(g) {
    return g._maxListeners === void 0 ? i.defaultMaxListeners : g._maxListeners;
  }
  i.prototype.getMaxListeners = function() {
    return c(this);
  }, i.prototype.emit = function(d) {
    for (var v = [], I = 1; I < arguments.length; I++) v.push(arguments[I]);
    var y = d === "error", P = this._events;
    if (P !== void 0)
      y = y && P.error === void 0;
    else if (!y)
      return !1;
    if (y) {
      var N;
      if (v.length > 0 && (N = v[0]), N instanceof Error)
        throw N;
      var G = new Error("Unhandled error." + (N ? " (" + N.message + ")" : ""));
      throw G.context = N, G;
    }
    var W = P[d];
    if (W === void 0)
      return !1;
    if (typeof W == "function")
      t(W, this, v);
    else
      for (var Y = W.length, S = w(W, Y), I = 0; I < Y; ++I)
        t(S[I], this, v);
    return !0;
  };
  function l(g, d, v, I) {
    var y, P, N;
    if (u(v), P = g._events, P === void 0 ? (P = g._events = /* @__PURE__ */ Object.create(null), g._eventsCount = 0) : (P.newListener !== void 0 && (g.emit(
      "newListener",
      d,
      v.listener ? v.listener : v
    ), P = g._events), N = P[d]), N === void 0)
      N = P[d] = v, ++g._eventsCount;
    else if (typeof N == "function" ? N = P[d] = I ? [v, N] : [N, v] : I ? N.unshift(v) : N.push(v), y = c(g), y > 0 && N.length > y && !N.warned) {
      N.warned = !0;
      var G = new Error("Possible EventEmitter memory leak detected. " + N.length + " " + String(d) + " listeners added. Use emitter.setMaxListeners() to increase limit");
      G.name = "MaxListenersExceededWarning", G.emitter = g, G.type = d, G.count = N.length, r(G);
    }
    return g;
  }
  i.prototype.addListener = function(d, v) {
    return l(this, d, v, !1);
  }, i.prototype.on = i.prototype.addListener, i.prototype.prependListener = function(d, v) {
    return l(this, d, v, !0);
  };
  function o() {
    if (!this.fired)
      return this.target.removeListener(this.type, this.wrapFn), this.fired = !0, arguments.length === 0 ? this.listener.call(this.target) : this.listener.apply(this.target, arguments);
  }
  function f(g, d, v) {
    var I = { fired: !1, wrapFn: void 0, target: g, type: d, listener: v }, y = o.bind(I);
    return y.listener = v, I.wrapFn = y, y;
  }
  i.prototype.once = function(d, v) {
    return u(v), this.on(d, f(this, d, v)), this;
  }, i.prototype.prependOnceListener = function(d, v) {
    return u(v), this.prependListener(d, f(this, d, v)), this;
  }, i.prototype.removeListener = function(d, v) {
    var I, y, P, N, G;
    if (u(v), y = this._events, y === void 0)
      return this;
    if (I = y[d], I === void 0)
      return this;
    if (I === v || I.listener === v)
      --this._eventsCount === 0 ? this._events = /* @__PURE__ */ Object.create(null) : (delete y[d], y.removeListener && this.emit("removeListener", d, I.listener || v));
    else if (typeof I != "function") {
      for (P = -1, N = I.length - 1; N >= 0; N--)
        if (I[N] === v || I[N].listener === v) {
          G = I[N].listener, P = N;
          break;
        }
      if (P < 0)
        return this;
      P === 0 ? I.shift() : m(I, P), I.length === 1 && (y[d] = I[0]), y.removeListener !== void 0 && this.emit("removeListener", d, G || v);
    }
    return this;
  }, i.prototype.off = i.prototype.removeListener, i.prototype.removeAllListeners = function(d) {
    var v, I, y;
    if (I = this._events, I === void 0)
      return this;
    if (I.removeListener === void 0)
      return arguments.length === 0 ? (this._events = /* @__PURE__ */ Object.create(null), this._eventsCount = 0) : I[d] !== void 0 && (--this._eventsCount === 0 ? this._events = /* @__PURE__ */ Object.create(null) : delete I[d]), this;
    if (arguments.length === 0) {
      var P = Object.keys(I), N;
      for (y = 0; y < P.length; ++y)
        N = P[y], N !== "removeListener" && this.removeAllListeners(N);
      return this.removeAllListeners("removeListener"), this._events = /* @__PURE__ */ Object.create(null), this._eventsCount = 0, this;
    }
    if (v = I[d], typeof v == "function")
      this.removeListener(d, v);
    else if (v !== void 0)
      for (y = v.length - 1; y >= 0; y--)
        this.removeListener(d, v[y]);
    return this;
  };
  function h(g, d, v) {
    var I = g._events;
    if (I === void 0)
      return [];
    var y = I[d];
    return y === void 0 ? [] : typeof y == "function" ? v ? [y.listener || y] : [y] : v ? E(y) : w(y, y.length);
  }
  i.prototype.listeners = function(d) {
    return h(this, d, !0);
  }, i.prototype.rawListeners = function(d) {
    return h(this, d, !1);
  }, i.listenerCount = function(g, d) {
    return typeof g.listenerCount == "function" ? g.listenerCount(d) : p.call(g, d);
  }, i.prototype.listenerCount = p;
  function p(g) {
    var d = this._events;
    if (d !== void 0) {
      var v = d[g];
      if (typeof v == "function")
        return 1;
      if (v !== void 0)
        return v.length;
    }
    return 0;
  }
  i.prototype.eventNames = function() {
    return this._eventsCount > 0 ? e(this._events) : [];
  };
  function w(g, d) {
    for (var v = new Array(d), I = 0; I < d; ++I)
      v[I] = g[I];
    return v;
  }
  function m(g, d) {
    for (; d + 1 < g.length; d++)
      g[d] = g[d + 1];
    g.pop();
  }
  function E(g) {
    for (var d = new Array(g.length), v = 0; v < d.length; ++v)
      d[v] = g[v].listener || g[v];
    return d;
  }
  function T(g, d) {
    return new Promise(function(v, I) {
      function y(N) {
        g.removeListener(d, P), I(N);
      }
      function P() {
        typeof g.removeListener == "function" && g.removeListener("error", y), v([].slice.call(arguments));
      }
      R(g, d, P, { once: !0 }), d !== "error" && M(g, y, { once: !0 });
    });
  }
  function M(g, d, v) {
    typeof g.on == "function" && R(g, "error", d, v);
  }
  function R(g, d, v, I) {
    if (typeof g.on == "function")
      I.once ? g.once(d, v) : g.on(d, v);
    else if (typeof g.addEventListener == "function")
      g.addEventListener(d, function y(P) {
        I.once && g.removeEventListener(d, y), v(P);
      });
    else
      throw new TypeError('The "emitter" argument must be of type EventEmitter. Received type ' + typeof g);
  }
  return pe.exports;
}
var ln = un();
class cn extends Error {
  constructor(t) {
    super(t), this.name = "ConcurrentModificationError";
  }
}
class jn {
  constructor(t) {
    z(this, "sessionsDir");
    this.sessionsDir = Se.join(t, "sessions");
  }
  /**
   * Ensure the sessions directory exists
   */
  async ensureSessionsDir() {
    try {
      await H.promises.mkdir(this.sessionsDir, { recursive: !0 });
    } catch (t) {
      if (t.code !== "EEXIST")
        throw t;
    }
  }
  /**
   * Get the file path for a session
   */
  getSessionPath(t) {
    return Se.join(this.sessionsDir, `${t}.json`);
  }
  /**
   * Save session data to file system
   */
  async saveSession(t) {
    await this.ensureSessionsDir();
    const e = this.getSessionPath(t.id), r = JSON.stringify(t, null, 2);
    await H.promises.writeFile(e, r, "utf8");
  }
  /**
   * Load session data from file system
   */
  async loadSession(t) {
    try {
      const e = this.getSessionPath(t), r = await H.promises.readFile(e, "utf8");
      return JSON.parse(r);
    } catch (e) {
      if (e.code === "ENOENT")
        return null;
      throw e;
    }
  }
  /**
   * Delete session data from file system
   */
  async deleteSession(t) {
    try {
      const e = this.getSessionPath(t);
      await H.promises.unlink(e);
    } catch (e) {
      if (e.code !== "ENOENT")
        throw e;
    }
  }
  /**
   * List all session IDs in storage
   */
  async listSessionIds() {
    try {
      return await this.ensureSessionsDir(), (await H.promises.readdir(this.sessionsDir)).filter((e) => e.endsWith(".json")).map((e) => Se.basename(e, ".json"));
    } catch (t) {
      if (t.code === "ENOENT")
        return [];
      throw t;
    }
  }
  /**
   * Get session metadata without loading full session
   */
  async getSessionInfo(t) {
    try {
      const e = this.getSessionPath(t), r = await H.promises.readFile(e, "utf8"), s = JSON.parse(r);
      let i = 0;
      return i += s.history.length, s.nextMessage && i++, {
        id: s.id,
        title: s.title,
        lastModified: s.lastModified,
        messageCount: i
      };
    } catch (e) {
      if (e.code === "ENOENT")
        return null;
      throw e;
    }
  }
  /**
   * Save session with version check for optimistic concurrency control
   */
  async saveWithVersion(t, e) {
    await this.ensureSessionsDir();
    const r = this.getSessionPath(t.id);
    try {
      const a = await H.promises.readFile(r, "utf8"), u = JSON.parse(a);
      if (u.version !== e)
        throw new cn(`Expected version ${e}, got ${u.version}`);
    } catch (a) {
      if (a.code !== "ENOENT")
        throw a;
    }
    const s = {
      ...t,
      version: e + 1,
      lastModified: j()
    }, i = JSON.stringify(s, null, 2);
    await H.promises.writeFile(r, i, "utf8");
  }
}
class Gn extends ln.EventEmitter {
  constructor(e, r) {
    super();
    z(this, "storage");
    z(this, "sessionCache", /* @__PURE__ */ new Map());
    z(this, "eventBus");
    z(this, "sessionLocks", /* @__PURE__ */ new Map());
    this.storage = e, this.eventBus = r || new Zr();
  }
  /**
   * Add a session to the cache
   */
  cacheSession(e) {
    this.sessionCache.set(e.id, e), this.emit("sessionChanged", {
      sessionId: e.id,
      changeType: "updated"
    });
  }
  /**
   * Get a cached session
   */
  getCachedSession(e) {
    return this.sessionCache.get(e);
  }
  /**
   * Remove a session from cache
   */
  removeCachedSession(e) {
    this.sessionCache.delete(e), this.emit("sessionChanged", {
      sessionId: e,
      changeType: "deleted"
    });
  }
  /**
   * List cached sessions
   */
  listCachedSessions() {
    return Array.from(this.sessionCache.values()).map((e) => ({
      id: e.id,
      title: e.title,
      lastModified: e.lastModified,
      messageCount: e.history.length + (e.nextMessage ? 1 : 0)
    }));
  }
  /**
   * Add a listener for session change events
   */
  onSessionChanged(e) {
    return this.on("sessionChanged", e);
  }
  /**
   * Remove a listener for session change events
   */
  offSessionChanged(e) {
    return this.off("sessionChanged", e);
  }
  /**
   * Clear the session cache
   */
  clearCache() {
    this.sessionCache.clear();
  }
  /**
   * Get the number of cached sessions
   */
  getCacheSize() {
    return this.sessionCache.size;
  }
  /**
   * Create a new session
   */
  async createSession(e) {
    const r = Qr(), s = j(), i = e.initialContext || {
      systemMessage: "",
      tools: [],
      contextFiles: [],
      steeringFiles: []
    }, a = new Q(
      r,
      e.title,
      Kr.Chat,
      s,
      s,
      0,
      i,
      [],
      void 0,
      void 0
    );
    return this.setupAutoSave(a), this.storage && await this.storage.saveSession(a.toJSON()), this.sessionCache.set(r, a), this.emit("sessionChanged", {
      sessionId: r,
      changeType: "created"
    }), a;
  }
  /**
   * Get an existing session by ID
   */
  async getSession(e) {
    const r = this.sessionCache.get(e);
    if (r)
      return r;
    if (this.storage) {
      const s = await this.storage.loadSession(e);
      if (!s)
        throw new Error(`Session not found: ${e}`);
      const i = Q.fromJSON(s);
      return this.setupAutoSave(i), this.sessionCache.set(e, i), i;
    }
    throw new Error(`Session not found: ${e}`);
  }
  /**
   * Delete a session
   */
  async deleteSession(e) {
    this.sessionCache.delete(e), this.storage && await this.storage.deleteSession(e), this.emit("sessionChanged", {
      sessionId: e,
      changeType: "deleted"
    });
  }
  /**
   * List sessions with pagination support
   */
  async listSessions(e = {}) {
    const { offset: r = 0, limit: s = 50 } = e;
    if (!this.storage)
      return this.listCachedSessions().slice(r, r + s);
    const a = (await this.storage.listSessionIds()).map(
      (l) => {
        var o;
        return ((o = this.storage) == null ? void 0 : o.getSessionInfo(l)) ?? Promise.resolve(null);
      }
    );
    return (await Promise.all(a)).filter((l) => l !== null).sort((l, o) => o.lastModified - l.lastModified).slice(r, r + s);
  }
  /**
   * Check if a session exists
   */
  async sessionExists(e) {
    return this.sessionCache.has(e) ? !0 : this.storage ? await this.storage.loadSession(e) !== null : !1;
  }
  /**
   * Save a session asynchronously (fire and forget)
   */
  async saveSessionAsync(e) {
    if (this.storage)
      try {
        await this.storage.saveSession(e.toJSON());
      } catch (r) {
        r instanceof Error && this.emit("error", new Error(`Failed to auto-save session ${e.id}: ${r.message}`));
      }
  }
  /**
   * Save a session synchronously
   */
  async saveSession(e) {
    this.storage && await this.storage.saveSession(e.toJSON());
  }
  /**
   * Set up auto-save functionality for a session
   */
  setupAutoSave(e) {
    this.storage;
  }
  // ============================================================================
  // User Interaction Entry Points
  // ============================================================================
  /**
   * Submit a user message to a session
   * This is the primary entry point for user input
   */
  async submitUserMessage(e, r, s = []) {
    await this.withSessionLock(e, async (i) => {
      var c;
      const a = [{ type: "text", text: r }], u = J.startUserMessage(a, s);
      await this.applySessionEdit(i, u), await this.eventBus.emit({
        id: K(),
        sessionId: e,
        timestamp: j(),
        type: "message_added",
        source: oe.User,
        data: {
          messageId: ((c = i.nextMessage) == null ? void 0 : c.id) || K(),
          messageType: "user"
        }
      });
    });
  }
  /**
   * Approve or deny a tool call
   * This is the entry point for tool call approval decisions
   */
  async approveToolCall(e, r, s) {
    await this.withSessionLock(e, async (i) => {
      const a = s.approved ? $.Approved : $.Denied, u = J.updateToolCallStatus(r, a);
      await this.applySessionEdit(i, u), await this.eventBus.emit({
        id: K(),
        sessionId: e,
        timestamp: j(),
        type: "tool_call_approval_decided",
        source: oe.User,
        data: {
          toolCallId: r,
          approved: s.approved,
          userComment: s.userComment
        }
      });
    });
  }
  // ============================================================================
  // Typed Event Subscription Methods
  // ============================================================================
  /**
   * Subscribe to a specific event type across all sessions
   */
  onEvent(e, r) {
    return this.eventBus.subscribe(e, r);
  }
  /**
   * Subscribe to all events for a specific session
   */
  onSessionEvent(e, r) {
    return this.eventBus.subscribeToSession(e, r);
  }
  /**
   * Unsubscribe from events using a subscription token
   */
  unsubscribe(e) {
    this.eventBus.unsubscribe(e);
  }
  // ============================================================================
  // Session-Aware Agent Dispatch Integration
  // ============================================================================
  /**
   * Dispatch user input to appropriate agent based on session context
   * This will be fully implemented in Task 6
   */
  dispatchToAgent(e) {
    const r = K();
    return Promise.resolve({
      executionId: r,
      sessionId: e.sessionId,
      status: "queued"
    });
  }
  // ============================================================================
  // Atomic Session Editing with Optimistic Concurrency Control
  // ============================================================================
  /**
   * Apply a session edit atomically with validation and event emission
   */
  async applySessionEdit(e, r) {
    const s = r.validate(e);
    if (!s.isValid)
      throw new Error(`Session edit validation failed: ${s.errors.map((a) => a.message).join(", ")}`);
    const i = await r.apply(e);
    return this.storage && await this.storage.saveWithVersion(i.toJSON(), e.version), this.sessionCache.set(e.id, i), await this.eventBus.emit({
      id: K(),
      sessionId: e.id,
      timestamp: j(),
      type: "session_updated",
      source: oe.System,
      data: {
        field: "session_edit_applied",
        oldValue: e.version,
        newValue: i.version
      }
    }), i;
  }
  /**
   * Apply multiple session edits atomically
   */
  async applySessionEdits(e, r) {
    for (const i of r) {
      const a = i.validate(e);
      if (!a.isValid)
        throw new Error(`Session edit validation failed: ${a.errors.map((u) => u.message).join(", ")}`);
    }
    let s = e;
    for (const i of r)
      s = await i.apply(s);
    return this.storage && await this.storage.saveWithVersion(s.toJSON(), e.version), this.sessionCache.set(e.id, s), await this.eventBus.emit({
      id: K(),
      sessionId: e.id,
      timestamp: j(),
      type: "session_updated",
      source: oe.System,
      data: {
        field: "batch_edits_applied",
        oldValue: e.version,
        newValue: s.version
      }
    }), s;
  }
  // ============================================================================
  // Race Condition Prevention
  // ============================================================================
  /**
   * Execute an operation with exclusive access to a session
   * Prevents race conditions by ensuring only one operation per session at a time
   */
  async withSessionLock(e, r) {
    const s = this.sessionLocks.get(e);
    s && await s;
    let i;
    const a = new Promise((u) => {
      i = u;
    });
    this.sessionLocks.set(e, a);
    try {
      const u = await this.getSession(e);
      return await r(u);
    } finally {
      this.sessionLocks.delete(e), i && i();
    }
  }
  /**
   * Edit a session atomically with lock protection
   */
  async editSession(e, ...r) {
    await this.withSessionLock(e, async (s) => {
      await this.applySessionEdits(s, r);
    });
  }
  // ============================================================================
  // Event Bus Access
  // ============================================================================
  /**
   * Get the event bus instance for direct access
   */
  getEventBus() {
    return this.eventBus;
  }
  /**
   * Emit an event through the event bus
   */
  async emitEvent(e) {
    await this.eventBus.emit(e);
  }
}
export {
  sn as AddToolCallEdit,
  an as AddToolResponseEdit,
  Bn as AgentType,
  on as CompleteMessageEdit,
  cn as ConcurrentModificationError,
  ge as ConversationTurn,
  Vn as ExecutionStatus,
  jn as FileSystemSessionStorage,
  Ys as LangchainMessageWriter,
  Vr as MessageWriter,
  Q as Session,
  J as SessionEdit,
  Gn as SessionManager,
  Kr as SessionType,
  tn as StartUserMessageEdit,
  Ot as TOOL_CALL_TRANSITIONS,
  $ as ToolCallStatus,
  Ks as UIMessageWriter,
  rn as UpdateStreamingContentEdit,
  nn as UpdateToolCallStatusEdit,
  Xn as addContextFiles,
  yn as addMessageToHistory,
  Wn as addSteeringFiles,
  zn as addToolCallToAssistant,
  Nt as addToolResponseToMessageTuple,
  Hn as addToolResponseToTuple,
  An as approveToolCall,
  Sn as clearSessionExecutionMetadata,
  _n as commitNextMessage,
  Jn as completeAssistantMessage,
  xn as completeToolCallExecution,
  Jr as createAssistantMessage,
  Yn as createContextMessage,
  Yr as createConversationTurn,
  Kn as createEmptyContext,
  bn as createFailedToolResponse,
  Qn as createFileLocation,
  Zn as createRangeLocation,
  En as createSession,
  en as createToolCall,
  Cn as createToolCallAwaitingApproval,
  Nn as createToolResponse,
  ei as createToolResponseMessage,
  Hr as createUserMessage,
  Ln as denyToolCall,
  $n as failToolCallExecution,
  K as generateId,
  Ie as generateMessageId,
  Qr as generateSessionId,
  ui as generateToolCallId,
  Fn as getExecutionDuration,
  Rn as getValidNextStates,
  qn as isComplete,
  Pn as isInProgress,
  Tn as isTerminalStatus,
  Xr as isValidTransition,
  j as now,
  Mn as requiresApproval,
  ne as setNextMessage,
  On as startToolCallExecution,
  li as timestamp,
  ti as updateAssistantContent,
  ri as updateContextSystemMessage,
  si as updateContextTools,
  ni as updateConversationTurnAssistant,
  xt as updateConversationTurnAssistantContent,
  $t as updateConversationTurnToolCall,
  B as updateSession,
  In as updateSessionExecutionMetadata,
  wn as updateSessionTitle,
  ae as updateToolCallStatus,
  ii as updateToolCallStatusInAssistant,
  ai as updateWorkspaceInfo,
  Dn as wasSuccessful
};
