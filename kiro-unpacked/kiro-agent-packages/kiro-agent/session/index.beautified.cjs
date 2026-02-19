"use strict";
var Kr = Object.defineProperty;
var Qr = (n, t, e) => t in n ? Kr(n, t, {
  enumerable: !0,
  configurable: !0,
  writable: !0,
  value: e
}) : n[t] = e;
var H = (n, t, e) => Qr(n, typeof t != "symbol" ? t + "" : t, e);
Object.defineProperty(exports, Symbol.toStringTag, {
  value: "Module"
});
const _ = require("../conversation-turn-Bn5WDoGn.cjs"),
  P = require("../id-Bz2XTYCE.cjs");
require("zod");
const Et = require("../powers-BhbIVJw-.cjs"),
  Zr = require("fs"),
  es = require("path"),
  re = require("../events-ClqnULUb.cjs");

function Pr(n) {
  const t = Object.create(null, {
    [Symbol.toStringTag]: {
      value: "Module"
    }
  });
  if (n) {
    for (const e in n)
      if (e !== "default") {
        const r = Object.getOwnPropertyDescriptor(n, e);
        Object.defineProperty(t, e, r.get ? r : {
          enumerable: !0,
          get: () => n[e]
        })
      }
  }
  return t.default = n, Object.freeze(t)
}
const J = Pr(Zr),
  Te = Pr(es);

function qr(n) {
  return n && n.__esModule && Object.prototype.hasOwnProperty.call(n, "default") ? n.default : n
}
var Se, Ot;

function ts() {
  return Ot || (Ot = 1, Se = function(n, t) {
    if (typeof n != "string") throw new TypeError("Expected a string");
    return t = typeof t > "u" ? "_" : t, n.replace(/([a-z\d])([A-Z])/g, "$1" + t + "$2").replace(
      /([A-Z]+)([A-Z][a-z\d]+)/g, "$1" + t + "$2").toLowerCase()
  }), Se
}
var rs = ts();
const ss = qr(rs);
var oe = {
    exports: {}
  },
  xt;

function ns() {
  if (xt) return oe.exports;
  xt = 1;
  const n = /[\p{Lu}]/u,
    t = /[\p{Ll}]/u,
    e = /^[\p{Lu}](?![\p{Lu}])/gu,
    r = /([\p{Alpha}\p{N}_]|$)/u,
    s = /[_.\- ]+/,
    i = new RegExp("^" + s.source),
    a = new RegExp(s.source + r.source, "gu"),
    l = new RegExp("\\d+" + r.source, "gu"),
    c = (h, p, S) => {
      let m = !1,
        E = !1,
        R = !1;
      for (let b = 0; b < h.length; b++) {
        const I = h[b];
        m && n.test(I) ? (h = h.slice(0, b) + "-" + h.slice(b), m = !1, R = E, E = !0, b++) : E && R && t.test(I) ? (h =
          h.slice(0, b - 1) + "-" + h.slice(b - 1), R = E, E = !1, m = !0) : (m = p(I) === I && S(I) !== I, R = E, E =
          S(I) === I && p(I) !== I)
      }
      return h
    },
    u = (h, p) => (e.lastIndex = 0, h.replace(e, S => p(S))),
    o = (h, p) => (a.lastIndex = 0, l.lastIndex = 0, h.replace(a, (S, m) => p(m)).replace(l, S => p(S))),
    f = (h, p) => {
      if (!(typeof h == "string" || Array.isArray(h))) throw new TypeError(
        "Expected the input to be `string | string[]`");
      if (p = {
          pascalCase: !1,
          preserveConsecutiveUppercase: !1,
          ...p
        }, Array.isArray(h) ? h = h.map(R => R.trim()).filter(R => R.length).join("-") : h = h.trim(), h.length === 0)
        return "";
      const S = p.locale === !1 ? R => R.toLowerCase() : R => R.toLocaleLowerCase(p.locale),
        m = p.locale === !1 ? R => R.toUpperCase() : R => R.toLocaleUpperCase(p.locale);
      return h.length === 1 ? p.pascalCase ? m(h) : S(h) : (h !== S(h) && (h = c(h, S, m)), h = h.replace(i, ""), p
        .preserveConsecutiveUppercase ? h = u(h, S) : h = S(h), p.pascalCase && (h = m(h.charAt(0)) + h.slice(1)), o(
          h, m))
    };
  return oe.exports = f, oe.exports.default = f, oe.exports
}
ns();

function is(n, t) {
  return (t == null ? void 0 : t[n]) || ss(n)
}

function as(n, t, e) {
  const r = {};
  for (const s in n) Object.hasOwn(n, s) && (r[t(s, e)] = n[s]);
  return r
}

function $t(n) {
  return Array.isArray(n) ? [...n] : {
    ...n
  }
}

function os(n, t) {
  const e = $t(n);
  for (const [r, s] of Object.entries(t)) {
    const [i, ...a] = r.split(".").reverse();
    let l = e;
    for (const c of a.reverse()) {
      if (l[c] === void 0) break;
      l[c] = $t(l[c]), l = l[c]
    }
    l[i] !== void 0 && (l[i] = {
      lc: 1,
      type: "secret",
      id: [s]
    })
  }
  return e
}

function ls(n) {
  const t = Object.getPrototypeOf(n);
  return typeof n.lc_name == "function" && (typeof t.lc_name != "function" || n.lc_name() !== t.lc_name()) ? n
  .lc_name() : n.name
}
class yt {
  static lc_name() {
    return this.name
  }
  get lc_id() {
    return [...this.lc_namespace, ls(this.constructor)]
  }
  get lc_secrets() {}
  get lc_attributes() {}
  get lc_aliases() {}
  get lc_serializable_keys() {}
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
    }), this.lc_serializable_keys !== void 0 ? this.lc_kwargs = Object.fromEntries(Object.entries(t || {}).filter(([
      r
    ]) => {
      var s;
      return (s = this.lc_serializable_keys) == null ? void 0 : s.includes(r)
    })) : this.lc_kwargs = t ?? {}
  }
  toJSON() {
    if (!this.lc_serializable) return this.toJSONNotImplemented();
    if (this.lc_kwargs instanceof yt || typeof this.lc_kwargs != "object" || Array.isArray(this.lc_kwargs))
    return this.toJSONNotImplemented();
    const t = {},
      e = {},
      r = Object.keys(this.lc_kwargs).reduce((s, i) => (s[i] = i in this ? this[i] : this.lc_kwargs[i], s), {});
    for (let s = Object.getPrototypeOf(this); s; s = Object.getPrototypeOf(s)) Object.assign(t, Reflect.get(s,
      "lc_aliases", this)), Object.assign(e, Reflect.get(s, "lc_secrets", this)), Object.assign(r, Reflect.get(s,
      "lc_attributes", this));
    return Object.keys(e).forEach(s => {
      let i = this,
        a = r;
      const [l, ...c] = s.split(".").reverse();
      for (const u of c.reverse()) {
        if (!(u in i) || i[u] === void 0) return;
        (!(u in a) || a[u] === void 0) && (typeof i[u] == "object" && i[u] != null ? a[u] = {} : Array.isArray(i[
          u]) && (a[u] = [])), i = i[u], a = a[u]
      }
      l in i && i[l] !== void 0 && (a[l] = a[l] || i[l])
    }), {
      lc: 1,
      type: "constructor",
      id: this.lc_id,
      kwargs: as(Object.keys(e).length ? os(r, e) : r, is, t)
    }
  }
  toJSONNotImplemented() {
    return {
      lc: 1,
      type: "not_implemented",
      id: this.lc_id
    }
  }
}

function us(n, t) {
  function e(r, s) {
    if (typeof r != "object" || r === null || r === void 0) return r;
    if (s >= t) return Array.isArray(r) ? "[Array]" : "[Object]";
    if (Array.isArray(r)) return r.map(a => e(a, s + 1));
    const i = {};
    for (const a of Object.keys(r)) i[a] = e(r[a], s + 1);
    return i
  }
  return JSON.stringify(e(n, 0), null, 2)
}
class _t extends yt {
  get lc_aliases() {
    return {
      additional_kwargs: "additional_kwargs",
      response_metadata: "response_metadata"
    }
  }
  get text() {
    return typeof this.content == "string" ? this.content : Array.isArray(this.content) ? this.content.map(t =>
      typeof t == "string" ? t : t.type === "text" ? t.text : "").join("") : ""
  }
  getType() {
    return this._getType()
  }
  constructor(t, e) {
    typeof t == "string" && (t = {
        content: t,
        additional_kwargs: e,
        response_metadata: {}
      }), t.additional_kwargs || (t.additional_kwargs = {}), t.response_metadata || (t.response_metadata = {}), super(
      t), Object.defineProperty(this, "lc_namespace", {
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
      }), this.name = t.name, this.content = t.content, this.additional_kwargs = t.additional_kwargs, this
      .response_metadata = t.response_metadata, this.id = t.id
  }
  toDict() {
    return {
      type: this._getType(),
      data: this.toJSON().kwargs
    }
  }
  static lc_name() {
    return "BaseMessage"
  }
  get _printableFields() {
    return {
      id: this.id,
      content: this.content,
      name: this.name,
      additional_kwargs: this.additional_kwargs,
      response_metadata: this.response_metadata
    }
  }
  _updateId(t) {
    this.id = t, this.lc_kwargs.id = t
  }
  get [Symbol.toStringTag]() {
    return this.constructor.lc_name()
  } [Symbol.for("nodejs.util.inspect.custom")](t) {
    if (t === null) return this;
    const e = us(this._printableFields, Math.max(4, t));
    return `${this.constructor.lc_name()} ${e}`
  }
}

function cs(n) {
  const t = [],
    e = [];
  for (const r of n)
    if (r.function) {
      const s = r.function.name;
      try {
        const i = JSON.parse(r.function.arguments),
          a = {
            name: s || "",
            args: i || {},
            id: r.id
          };
        t.push(a)
      } catch {
        e.push({
          name: s,
          args: r.function.arguments,
          id: r.id,
          error: "Malformed args."
        })
      }
    } else continue;
  return [t, e]
}
class hs extends _t {
  get lc_aliases() {
    return {
      ...super.lc_aliases,
      tool_calls: "tool_calls",
      invalid_tool_calls: "invalid_tool_calls"
    }
  }
  constructor(t, e) {
    var s;
    let r;
    if (typeof t == "string") r = {
      content: t,
      tool_calls: [],
      invalid_tool_calls: [],
      additional_kwargs: e ?? {}
    };
    else {
      r = t;
      const i = (s = r.additional_kwargs) == null ? void 0 : s.tool_calls,
        a = r.tool_calls;
      i != null && i.length > 0 && (a === void 0 || a.length === 0) && console.warn([
        "New LangChain packages are available that more efficiently handle", `tool calling.

Please upgrade your packages to versions that set`, "message tool calls. e.g., `yarn add @langchain/anthropic`,",
        "yarn add @langchain/openai`, etc."
      ].join(" "));
      try {
        if (i != null && a === void 0) {
          const [l, c] = cs(i);
          r.tool_calls = l ?? [], r.invalid_tool_calls = c ?? []
        } else r.tool_calls = r.tool_calls ?? [], r.invalid_tool_calls = r.invalid_tool_calls ?? []
      } catch {
        r.tool_calls = [], r.invalid_tool_calls = []
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
    }), typeof r != "string" && (this.tool_calls = r.tool_calls ?? this.tool_calls, this.invalid_tool_calls = r
      .invalid_tool_calls ?? this.invalid_tool_calls), this.usage_metadata = r.usage_metadata
  }
  static lc_name() {
    return "AIMessage"
  }
  _getType() {
    return "ai"
  }
  get _printableFields() {
    return {
      ...super._printableFields,
      tool_calls: this.tool_calls,
      invalid_tool_calls: this.invalid_tool_calls,
      usage_metadata: this.usage_metadata
    }
  }
}
class le extends _t {
  static lc_name() {
    return "HumanMessage"
  }
  _getType() {
    return "human"
  }
  constructor(t, e) {
    super(t, e)
  }
}
class fs extends _t {
  static lc_name() {
    return "SystemMessage"
  }
  _getType() {
    return "system"
  }
  constructor(t, e) {
    super(t, e)
  }
}
var se = {
    exports: {}
  },
  we = {},
  Ce, Nt;

function ds() {
  if (Nt) return Ce;
  Nt = 1;

  function n(t, e) {
    typeof e == "boolean" && (e = {
        forever: e
      }), this._originalTimeouts = JSON.parse(JSON.stringify(t)), this._timeouts = t, this._options = e || {}, this
      ._maxRetryTime = e && e.maxRetryTime || 1 / 0, this._fn = null, this._errors = [], this._attempts = 1, this
      ._operationTimeout = null, this._operationTimeoutCb = null, this._timeout = null, this._operationStart = null,
      this._timer = null, this._options.forever && (this._cachedTimeouts = this._timeouts.slice(0))
  }
  return Ce = n, n.prototype.reset = function() {
    this._attempts = 1, this._timeouts = this._originalTimeouts.slice(0)
  }, n.prototype.stop = function() {
    this._timeout && clearTimeout(this._timeout), this._timer && clearTimeout(this._timer), this._timeouts = [], this
      ._cachedTimeouts = null
  }, n.prototype.retry = function(t) {
    if (this._timeout && clearTimeout(this._timeout), !t) return !1;
    var e = new Date().getTime();
    if (t && e - this._operationStart >= this._maxRetryTime) return this._errors.push(t), this._errors.unshift(
      new Error("RetryOperation timeout occurred")), !1;
    this._errors.push(t);
    var r = this._timeouts.shift();
    if (r === void 0)
      if (this._cachedTimeouts) this._errors.splice(0, this._errors.length - 1), r = this._cachedTimeouts.slice(-1);
      else return !1;
    var s = this;
    return this._timer = setTimeout(function() {
      s._attempts++, s._operationTimeoutCb && (s._timeout = setTimeout(function() {
        s._operationTimeoutCb(s._attempts)
      }, s._operationTimeout), s._options.unref && s._timeout.unref()), s._fn(s._attempts)
    }, r), this._options.unref && this._timer.unref(), !0
  }, n.prototype.attempt = function(t, e) {
    this._fn = t, e && (e.timeout && (this._operationTimeout = e.timeout), e.cb && (this._operationTimeoutCb = e.cb));
    var r = this;
    this._operationTimeoutCb && (this._timeout = setTimeout(function() {
      r._operationTimeoutCb()
    }, r._operationTimeout)), this._operationStart = new Date().getTime(), this._fn(this._attempts)
  }, n.prototype.try = function(t) {
    console.log("Using RetryOperation.try() is deprecated"), this.attempt(t)
  }, n.prototype.start = function(t) {
    console.log("Using RetryOperation.start() is deprecated"), this.attempt(t)
  }, n.prototype.start = n.prototype.try, n.prototype.errors = function() {
    return this._errors
  }, n.prototype.attempts = function() {
    return this._attempts
  }, n.prototype.mainError = function() {
    if (this._errors.length === 0) return null;
    for (var t = {}, e = null, r = 0, s = 0; s < this._errors.length; s++) {
      var i = this._errors[s],
        a = i.message,
        l = (t[a] || 0) + 1;
      t[a] = l, l >= r && (e = i, r = l)
    }
    return e
  }, Ce
}
var Mt;

function ps() {
  return Mt || (Mt = 1, function(n) {
    var t = ds();
    n.operation = function(e) {
      var r = n.timeouts(e);
      return new t(r, {
        forever: e && (e.forever || e.retries === 1 / 0),
        unref: e && e.unref,
        maxRetryTime: e && e.maxRetryTime
      })
    }, n.timeouts = function(e) {
      if (e instanceof Array) return [].concat(e);
      var r = {
        retries: 10,
        factor: 2,
        minTimeout: 1 * 1e3,
        maxTimeout: 1 / 0,
        randomize: !1
      };
      for (var s in e) r[s] = e[s];
      if (r.minTimeout > r.maxTimeout) throw new Error("minTimeout is greater than maxTimeout");
      for (var i = [], a = 0; a < r.retries; a++) i.push(this.createTimeout(a, r));
      return e && e.forever && !i.length && i.push(this.createTimeout(a, r)), i.sort(function(l, c) {
        return l - c
      }), i
    }, n.createTimeout = function(e, r) {
      var s = r.randomize ? Math.random() + 1 : 1,
        i = Math.round(s * Math.max(r.minTimeout, 1) * Math.pow(r.factor, e));
      return i = Math.min(i, r.maxTimeout), i
    }, n.wrap = function(e, r, s) {
      if (r instanceof Array && (s = r, r = null), !s) {
        s = [];
        for (var i in e) typeof e[i] == "function" && s.push(i)
      }
      for (var a = 0; a < s.length; a++) {
        var l = s[a],
          c = e[l];
        e[l] = (function(o) {
          var f = n.operation(r),
            h = Array.prototype.slice.call(arguments, 1),
            p = h.pop();
          h.push(function(S) {
            f.retry(S) || (S && (arguments[0] = f.mainError()), p.apply(this, arguments))
          }), f.attempt(function() {
            o.apply(e, h)
          })
        }).bind(e, c), e[l].options = r
      }
    }
  }(we)), we
}
var Ie, bt;

function ms() {
  return bt || (bt = 1, Ie = ps()), Ie
}
var Pt;

function gs() {
  if (Pt) return se.exports;
  Pt = 1;
  const n = ms(),
    t = ["Failed to fetch", "NetworkError when attempting to fetch resource.",
      "The Internet connection appears to be offline.", "Network request failed"
    ];
  class e extends Error {
    constructor(l) {
      super(), l instanceof Error ? (this.originalError = l, {
          message: l
        } = l) : (this.originalError = new Error(l), this.originalError.stack = this.stack), this.name = "AbortError",
        this.message = l
    }
  }
  const r = (a, l, c) => {
      const u = c.retries - (l - 1);
      return a.attemptNumber = l, a.retriesLeft = u, a
    },
    s = a => t.includes(a),
    i = (a, l) => new Promise((c, u) => {
      l = {
        onFailedAttempt: () => {},
        retries: 10,
        ...l
      };
      const o = n.operation(l);
      o.attempt(async f => {
        try {
          c(await a(f))
        } catch (h) {
          if (!(h instanceof Error)) {
            u(new TypeError(`Non-error was thrown: "${h}". You should only throw errors.`));
            return
          }
          if (h instanceof e) o.stop(), u(h.originalError);
          else if (h instanceof TypeError && !s(h.message)) o.stop(), u(h);
          else {
            r(h, f, l);
            try {
              await l.onFailedAttempt(h)
            } catch (p) {
              u(p);
              return
            }
            o.retry(h) || u(o.mainError())
          }
        }
      })
    });
  return se.exports = i, se.exports.default = i, se.exports.AbortError = e, se.exports
}
gs();
var ue = {},
  Re = {
    exports: {}
  },
  qt;

function vs() {
  return qt || (qt = 1, function(n) {
    var t = Object.prototype.hasOwnProperty,
      e = "~";

    function r() {}
    Object.create && (r.prototype = Object.create(null), new r().__proto__ || (e = !1));

    function s(c, u, o) {
      this.fn = c, this.context = u, this.once = o || !1
    }

    function i(c, u, o, f, h) {
      if (typeof o != "function") throw new TypeError("The listener must be a function");
      var p = new s(o, f || c, h),
        S = e ? e + u : u;
      return c._events[S] ? c._events[S].fn ? c._events[S] = [c._events[S], p] : c._events[S].push(p) : (c._events[
        S] = p, c._eventsCount++), c
    }

    function a(c, u) {
      --c._eventsCount === 0 ? c._events = new r : delete c._events[u]
    }

    function l() {
      this._events = new r, this._eventsCount = 0
    }
    l.prototype.eventNames = function() {
        var u = [],
          o, f;
        if (this._eventsCount === 0) return u;
        for (f in o = this._events) t.call(o, f) && u.push(e ? f.slice(1) : f);
        return Object.getOwnPropertySymbols ? u.concat(Object.getOwnPropertySymbols(o)) : u
      }, l.prototype.listeners = function(u) {
        var o = e ? e + u : u,
          f = this._events[o];
        if (!f) return [];
        if (f.fn) return [f.fn];
        for (var h = 0, p = f.length, S = new Array(p); h < p; h++) S[h] = f[h].fn;
        return S
      }, l.prototype.listenerCount = function(u) {
        var o = e ? e + u : u,
          f = this._events[o];
        return f ? f.fn ? 1 : f.length : 0
      }, l.prototype.emit = function(u, o, f, h, p, S) {
        var m = e ? e + u : u;
        if (!this._events[m]) return !1;
        var E = this._events[m],
          R = arguments.length,
          b, I;
        if (E.fn) {
          switch (E.once && this.removeListener(u, E.fn, void 0, !0), R) {
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
              return E.fn.call(E.context, o, f, h, p, S), !0
          }
          for (I = 1, b = new Array(R - 1); I < R; I++) b[I - 1] = arguments[I];
          E.fn.apply(E.context, b)
        } else {
          var g = E.length,
            d;
          for (I = 0; I < g; I++) switch (E[I].once && this.removeListener(u, E[I].fn, void 0, !0), R) {
            case 1:
              E[I].fn.call(E[I].context);
              break;
            case 2:
              E[I].fn.call(E[I].context, o);
              break;
            case 3:
              E[I].fn.call(E[I].context, o, f);
              break;
            case 4:
              E[I].fn.call(E[I].context, o, f, h);
              break;
            default:
              if (!b)
                for (d = 1, b = new Array(R - 1); d < R; d++) b[d - 1] = arguments[d];
              E[I].fn.apply(E[I].context, b)
          }
        }
        return !0
      }, l.prototype.on = function(u, o, f) {
        return i(this, u, o, f, !1)
      }, l.prototype.once = function(u, o, f) {
        return i(this, u, o, f, !0)
      }, l.prototype.removeListener = function(u, o, f, h) {
        var p = e ? e + u : u;
        if (!this._events[p]) return this;
        if (!o) return a(this, p), this;
        var S = this._events[p];
        if (S.fn) S.fn === o && (!h || S.once) && (!f || S.context === f) && a(this, p);
        else {
          for (var m = 0, E = [], R = S.length; m < R; m++)(S[m].fn !== o || h && !S[m].once || f && S[m]
            .context !== f) && E.push(S[m]);
          E.length ? this._events[p] = E.length === 1 ? E[0] : E : a(this, p)
        }
        return this
      }, l.prototype.removeAllListeners = function(u) {
        var o;
        return u ? (o = e ? e + u : u, this._events[o] && a(this, o)) : (this._events = new r, this._eventsCount =
          0), this
      }, l.prototype.off = l.prototype.removeListener, l.prototype.addListener = l.prototype.on, l.prefixed = e, l
      .EventEmitter = l, n.exports = l
  }(Re)), Re.exports
}
var ne = {
    exports: {}
  },
  Ae, Dt;

function Es() {
  return Dt || (Dt = 1, Ae = (n, t) => (t = t || (() => {}), n.then(e => new Promise(r => {
    r(t())
  }).then(() => e), e => new Promise(r => {
    r(t())
  }).then(() => {
    throw e
  })))), Ae
}
var Ft;

function ys() {
  if (Ft) return ne.exports;
  Ft = 1;
  const n = Es();
  class t extends Error {
    constructor(s) {
      super(s), this.name = "TimeoutError"
    }
  }
  const e = (r, s, i) => new Promise((a, l) => {
    if (typeof s != "number" || s < 0) throw new TypeError("Expected `milliseconds` to be a positive number");
    if (s === 1 / 0) {
      a(r);
      return
    }
    const c = setTimeout(() => {
      if (typeof i == "function") {
        try {
          a(i())
        } catch (f) {
          l(f)
        }
        return
      }
      const u = typeof i == "string" ? i : `Promise timed out after ${s} milliseconds`,
        o = i instanceof Error ? i : new t(u);
      typeof r.cancel == "function" && r.cancel(), l(o)
    }, s);
    n(r.then(a, l), () => {
      clearTimeout(c)
    })
  });
  return ne.exports = e, ne.exports.default = e, ne.exports.TimeoutError = t, ne.exports
}
var ce = {},
  he = {},
  jt;

function _s() {
  if (jt) return he;
  jt = 1, Object.defineProperty(he, "__esModule", {
    value: !0
  });

  function n(t, e, r) {
    let s = 0,
      i = t.length;
    for (; i > 0;) {
      const a = i / 2 | 0;
      let l = s + a;
      r(t[l], e) <= 0 ? (s = ++l, i -= a + 1) : i = a
    }
    return s
  }
  return he.default = n, he
}
var Gt;

function Ts() {
  if (Gt) return ce;
  Gt = 1, Object.defineProperty(ce, "__esModule", {
    value: !0
  });
  const n = _s();
  class t {
    constructor() {
      this._queue = []
    }
    enqueue(r, s) {
      s = Object.assign({
        priority: 0
      }, s);
      const i = {
        priority: s.priority,
        run: r
      };
      if (this.size && this._queue[this.size - 1].priority >= s.priority) {
        this._queue.push(i);
        return
      }
      const a = n.default(this._queue, i, (l, c) => c.priority - l.priority);
      this._queue.splice(a, 0, i)
    }
    dequeue() {
      const r = this._queue.shift();
      return r == null ? void 0 : r.run
    }
    filter(r) {
      return this._queue.filter(s => s.priority === r.priority).map(s => s.run)
    }
    get size() {
      return this._queue.length
    }
  }
  return ce.default = t, ce
}
var Ut;

function Ss() {
  if (Ut) return ue;
  Ut = 1, Object.defineProperty(ue, "__esModule", {
    value: !0
  });
  const n = vs(),
    t = ys(),
    e = Ts(),
    r = () => {},
    s = new t.TimeoutError;
  class i extends n {
    constructor(l) {
      var c, u, o, f;
      if (super(), this._intervalCount = 0, this._intervalEnd = 0, this._pendingCount = 0, this._resolveEmpty = r,
        this._resolveIdle = r, l = Object.assign({
          carryoverConcurrencyCount: !1,
          intervalCap: 1 / 0,
          interval: 0,
          concurrency: 1 / 0,
          autoStart: !0,
          queueClass: e.default
        }, l), !(typeof l.intervalCap == "number" && l.intervalCap >= 1)) throw new TypeError(
        `Expected \`intervalCap\` to be a number from 1 and up, got \`${(u=(c=l.intervalCap)===null||c===void 0?void 0:c.toString())!==null&&u!==void 0?u:""}\` (${typeof l.intervalCap})`
        );
      if (l.interval === void 0 || !(Number.isFinite(l.interval) && l.interval >= 0)) throw new TypeError(
        `Expected \`interval\` to be a finite number >= 0, got \`${(f=(o=l.interval)===null||o===void 0?void 0:o.toString())!==null&&f!==void 0?f:""}\` (${typeof l.interval})`
        );
      this._carryoverConcurrencyCount = l.carryoverConcurrencyCount, this._isIntervalIgnored = l.intervalCap === 1 /
        0 || l.interval === 0, this._intervalCap = l.intervalCap, this._interval = l.interval, this._queue = new l
        .queueClass, this._queueClass = l.queueClass, this.concurrency = l.concurrency, this._timeout = l.timeout,
        this._throwOnTimeout = l.throwOnTimeout === !0, this._isPaused = l.autoStart === !1
    }
    get _doesIntervalAllowAnother() {
      return this._isIntervalIgnored || this._intervalCount < this._intervalCap
    }
    get _doesConcurrentAllowAnother() {
      return this._pendingCount < this._concurrency
    }
    _next() {
      this._pendingCount--, this._tryToStartAnother(), this.emit("next")
    }
    _resolvePromises() {
      this._resolveEmpty(), this._resolveEmpty = r, this._pendingCount === 0 && (this._resolveIdle(), this
        ._resolveIdle = r, this.emit("idle"))
    }
    _onResumeInterval() {
      this._onInterval(), this._initializeIntervalIfNeeded(), this._timeoutId = void 0
    }
    _isIntervalPaused() {
      const l = Date.now();
      if (this._intervalId === void 0) {
        const c = this._intervalEnd - l;
        if (c < 0) this._intervalCount = this._carryoverConcurrencyCount ? this._pendingCount : 0;
        else return this._timeoutId === void 0 && (this._timeoutId = setTimeout(() => {
          this._onResumeInterval()
        }, c)), !0
      }
      return !1
    }
    _tryToStartAnother() {
      if (this._queue.size === 0) return this._intervalId && clearInterval(this._intervalId), this._intervalId =
        void 0, this._resolvePromises(), !1;
      if (!this._isPaused) {
        const l = !this._isIntervalPaused();
        if (this._doesIntervalAllowAnother && this._doesConcurrentAllowAnother) {
          const c = this._queue.dequeue();
          return c ? (this.emit("active"), c(), l && this._initializeIntervalIfNeeded(), !0) : !1
        }
      }
      return !1
    }
    _initializeIntervalIfNeeded() {
      this._isIntervalIgnored || this._intervalId !== void 0 || (this._intervalId = setInterval(() => {
        this._onInterval()
      }, this._interval), this._intervalEnd = Date.now() + this._interval)
    }
    _onInterval() {
      this._intervalCount === 0 && this._pendingCount === 0 && this._intervalId && (clearInterval(this._intervalId),
          this._intervalId = void 0), this._intervalCount = this._carryoverConcurrencyCount ? this._pendingCount : 0,
        this._processQueue()
    }
    _processQueue() {
      for (; this._tryToStartAnother(););
    }
    get concurrency() {
      return this._concurrency
    }
    set concurrency(l) {
      if (!(typeof l == "number" && l >= 1)) throw new TypeError(
        `Expected \`concurrency\` to be a number from 1 and up, got \`${l}\` (${typeof l})`);
      this._concurrency = l, this._processQueue()
    }
    async add(l, c = {}) {
      return new Promise((u, o) => {
        const f = async () => {
          this._pendingCount++, this._intervalCount++;
          try {
            const h = this._timeout === void 0 && c.timeout === void 0 ? l() : t.default(Promise.resolve(l()),
              c.timeout === void 0 ? this._timeout : c.timeout, () => {
                (c.throwOnTimeout === void 0 ? this._throwOnTimeout : c.throwOnTimeout) && o(s)
              });
            u(await h)
          } catch (h) {
            o(h)
          }
          this._next()
        };
        this._queue.enqueue(f, c), this._tryToStartAnother(), this.emit("add")
      })
    }
    async addAll(l, c) {
      return Promise.all(l.map(async u => this.add(u, c)))
    }
    start() {
      return this._isPaused ? (this._isPaused = !1, this._processQueue(), this) : this
    }
    pause() {
      this._isPaused = !0
    }
    clear() {
      this._queue = new this._queueClass
    }
    async onEmpty() {
      if (this._queue.size !== 0) return new Promise(l => {
        const c = this._resolveEmpty;
        this._resolveEmpty = () => {
          c(), l()
        }
      })
    }
    async onIdle() {
      if (!(this._pendingCount === 0 && this._queue.size === 0)) return new Promise(l => {
        const c = this._resolveIdle;
        this._resolveIdle = () => {
          c(), l()
        }
      })
    }
    get size() {
      return this._queue.size
    }
    sizeBy(l) {
      return this._queue.filter(l).length
    }
    get pending() {
      return this._pendingCount
    }
    get isPaused() {
      return this._isPaused
    }
    get timeout() {
      return this._timeout
    }
    set timeout(l) {
      this._timeout = l
    }
  }
  return ue.default = i, ue
}
Ss();
var fe = {
    exports: {}
  },
  Le, kt;

function me() {
  if (kt) return Le;
  kt = 1;
  const n = "2.0.0",
    t = 256,
    e = Number.MAX_SAFE_INTEGER || 9007199254740991,
    r = 16,
    s = t - 6;
  return Le = {
    MAX_LENGTH: t,
    MAX_SAFE_COMPONENT_LENGTH: r,
    MAX_SAFE_BUILD_LENGTH: s,
    MAX_SAFE_INTEGER: e,
    RELEASE_TYPES: ["major", "premajor", "minor", "preminor", "patch", "prepatch", "prerelease"],
    SEMVER_SPEC_VERSION: n,
    FLAG_INCLUDE_PRERELEASE: 1,
    FLAG_LOOSE: 2
  }, Le
}
var Oe, Bt;

function ge() {
  return Bt || (Bt = 1, Oe = typeof process == "object" && process.env && process.env.NODE_DEBUG && /\bsemver\b/i.test(
    process.env.NODE_DEBUG) ? (...t) => console.error("SEMVER", ...t) : () => {}), Oe
}
var Vt;

function ie() {
  return Vt || (Vt = 1, function(n, t) {
    const {
      MAX_SAFE_COMPONENT_LENGTH: e,
      MAX_SAFE_BUILD_LENGTH: r,
      MAX_LENGTH: s
    } = me(), i = ge();
    t = n.exports = {};
    const a = t.re = [],
      l = t.safeRe = [],
      c = t.src = [],
      u = t.safeSrc = [],
      o = t.t = {};
    let f = 0;
    const h = "[a-zA-Z0-9-]",
      p = [
        ["\\s", 1],
        ["\\d", s],
        [h, r]
      ],
      S = E => {
        for (const [R, b] of p) E = E.split(`${R}*`).join(`${R}{0,${b}}`).split(`${R}+`).join(`${R}{1,${b}}`);
        return E
      },
      m = (E, R, b) => {
        const I = S(R),
          g = f++;
        i(E, g, R), o[E] = g, c[g] = R, u[g] = I, a[g] = new RegExp(R, b ? "g" : void 0), l[g] = new RegExp(I, b ?
          "g" : void 0)
      };
    m("NUMERICIDENTIFIER", "0|[1-9]\\d*"), m("NUMERICIDENTIFIERLOOSE", "\\d+"), m("NONNUMERICIDENTIFIER",
        `\\d*[a-zA-Z-]${h}*`), m("MAINVERSION",
        `(${c[o.NUMERICIDENTIFIER]})\\.(${c[o.NUMERICIDENTIFIER]})\\.(${c[o.NUMERICIDENTIFIER]})`), m(
        "MAINVERSIONLOOSE",
        `(${c[o.NUMERICIDENTIFIERLOOSE]})\\.(${c[o.NUMERICIDENTIFIERLOOSE]})\\.(${c[o.NUMERICIDENTIFIERLOOSE]})`),
      m("PRERELEASEIDENTIFIER", `(?:${c[o.NONNUMERICIDENTIFIER]}|${c[o.NUMERICIDENTIFIER]})`), m(
        "PRERELEASEIDENTIFIERLOOSE", `(?:${c[o.NONNUMERICIDENTIFIER]}|${c[o.NUMERICIDENTIFIERLOOSE]})`), m(
        "PRERELEASE", `(?:-(${c[o.PRERELEASEIDENTIFIER]}(?:\\.${c[o.PRERELEASEIDENTIFIER]})*))`), m(
        "PRERELEASELOOSE", `(?:-?(${c[o.PRERELEASEIDENTIFIERLOOSE]}(?:\\.${c[o.PRERELEASEIDENTIFIERLOOSE]})*))`), m(
        "BUILDIDENTIFIER", `${h}+`), m("BUILD", `(?:\\+(${c[o.BUILDIDENTIFIER]}(?:\\.${c[o.BUILDIDENTIFIER]})*))`),
      m("FULLPLAIN", `v?${c[o.MAINVERSION]}${c[o.PRERELEASE]}?${c[o.BUILD]}?`), m("FULL", `^${c[o.FULLPLAIN]}$`), m(
        "LOOSEPLAIN", `[v=\\s]*${c[o.MAINVERSIONLOOSE]}${c[o.PRERELEASELOOSE]}?${c[o.BUILD]}?`), m("LOOSE",
        `^${c[o.LOOSEPLAIN]}$`), m("GTLT", "((?:<|>)?=?)"), m("XRANGEIDENTIFIERLOOSE",
        `${c[o.NUMERICIDENTIFIERLOOSE]}|x|X|\\*`), m("XRANGEIDENTIFIER", `${c[o.NUMERICIDENTIFIER]}|x|X|\\*`), m(
        "XRANGEPLAIN",
        `[v=\\s]*(${c[o.XRANGEIDENTIFIER]})(?:\\.(${c[o.XRANGEIDENTIFIER]})(?:\\.(${c[o.XRANGEIDENTIFIER]})(?:${c[o.PRERELEASE]})?${c[o.BUILD]}?)?)?`
        ), m("XRANGEPLAINLOOSE",
        `[v=\\s]*(${c[o.XRANGEIDENTIFIERLOOSE]})(?:\\.(${c[o.XRANGEIDENTIFIERLOOSE]})(?:\\.(${c[o.XRANGEIDENTIFIERLOOSE]})(?:${c[o.PRERELEASELOOSE]})?${c[o.BUILD]}?)?)?`
        ), m("XRANGE", `^${c[o.GTLT]}\\s*${c[o.XRANGEPLAIN]}$`), m("XRANGELOOSE",
        `^${c[o.GTLT]}\\s*${c[o.XRANGEPLAINLOOSE]}$`), m("COERCEPLAIN",
        `(^|[^\\d])(\\d{1,${e}})(?:\\.(\\d{1,${e}}))?(?:\\.(\\d{1,${e}}))?`), m("COERCE",
        `${c[o.COERCEPLAIN]}(?:$|[^\\d])`), m("COERCEFULL", c[o.COERCEPLAIN] +
        `(?:${c[o.PRERELEASE]})?(?:${c[o.BUILD]})?(?:$|[^\\d])`), m("COERCERTL", c[o.COERCE], !0), m(
        "COERCERTLFULL", c[o.COERCEFULL], !0), m("LONETILDE", "(?:~>?)"), m("TILDETRIM",
        `(\\s*)${c[o.LONETILDE]}\\s+`, !0), t.tildeTrimReplace = "$1~", m("TILDE",
        `^${c[o.LONETILDE]}${c[o.XRANGEPLAIN]}$`), m("TILDELOOSE", `^${c[o.LONETILDE]}${c[o.XRANGEPLAINLOOSE]}$`),
      m("LONECARET", "(?:\\^)"), m("CARETTRIM", `(\\s*)${c[o.LONECARET]}\\s+`, !0), t.caretTrimReplace = "$1^", m(
        "CARET", `^${c[o.LONECARET]}${c[o.XRANGEPLAIN]}$`), m("CARETLOOSE",
        `^${c[o.LONECARET]}${c[o.XRANGEPLAINLOOSE]}$`), m("COMPARATORLOOSE",
        `^${c[o.GTLT]}\\s*(${c[o.LOOSEPLAIN]})$|^$`), m("COMPARATOR", `^${c[o.GTLT]}\\s*(${c[o.FULLPLAIN]})$|^$`),
      m("COMPARATORTRIM", `(\\s*)${c[o.GTLT]}\\s*(${c[o.LOOSEPLAIN]}|${c[o.XRANGEPLAIN]})`, !0), t
      .comparatorTrimReplace = "$1$2$3", m("HYPHENRANGE",
        `^\\s*(${c[o.XRANGEPLAIN]})\\s+-\\s+(${c[o.XRANGEPLAIN]})\\s*$`), m("HYPHENRANGELOOSE",
        `^\\s*(${c[o.XRANGEPLAINLOOSE]})\\s+-\\s+(${c[o.XRANGEPLAINLOOSE]})\\s*$`), m("STAR", "(<|>)?=?\\s*\\*"), m(
        "GTE0", "^\\s*>=\\s*0\\.0\\.0\\s*$"), m("GTE0PRE", "^\\s*>=\\s*0\\.0\\.0-0\\s*$")
  }(fe, fe.exports)), fe.exports
}
var xe, Xt;

function Tt() {
  if (Xt) return xe;
  Xt = 1;
  const n = Object.freeze({
      loose: !0
    }),
    t = Object.freeze({});
  return xe = r => r ? typeof r != "object" ? n : r : t, xe
}
var $e, Wt;

function Dr() {
  if (Wt) return $e;
  Wt = 1;
  const n = /^[0-9]+$/,
    t = (r, s) => {
      if (typeof r == "number" && typeof s == "number") return r === s ? 0 : r < s ? -1 : 1;
      const i = n.test(r),
        a = n.test(s);
      return i && a && (r = +r, s = +s), r === s ? 0 : i && !a ? -1 : a && !i ? 1 : r < s ? -1 : 1
    };
  return $e = {
    compareIdentifiers: t,
    rcompareIdentifiers: (r, s) => t(s, r)
  }, $e
}
var Ne, zt;

function k() {
  if (zt) return Ne;
  zt = 1;
  const n = ge(),
    {
      MAX_LENGTH: t,
      MAX_SAFE_INTEGER: e
    } = me(),
    {
      safeRe: r,
      t: s
    } = ie(),
    i = Tt(),
    {
      compareIdentifiers: a
    } = Dr();
  class l {
    constructor(u, o) {
      if (o = i(o), u instanceof l) {
        if (u.loose === !!o.loose && u.includePrerelease === !!o.includePrerelease) return u;
        u = u.version
      } else if (typeof u != "string") throw new TypeError(
        `Invalid version. Must be a string. Got type "${typeof u}".`);
      if (u.length > t) throw new TypeError(`version is longer than ${t} characters`);
      n("SemVer", u, o), this.options = o, this.loose = !!o.loose, this.includePrerelease = !!o.includePrerelease;
      const f = u.trim().match(o.loose ? r[s.LOOSE] : r[s.FULL]);
      if (!f) throw new TypeError(`Invalid Version: ${u}`);
      if (this.raw = u, this.major = +f[1], this.minor = +f[2], this.patch = +f[3], this.major > e || this.major < 0)
        throw new TypeError("Invalid major version");
      if (this.minor > e || this.minor < 0) throw new TypeError("Invalid minor version");
      if (this.patch > e || this.patch < 0) throw new TypeError("Invalid patch version");
      f[4] ? this.prerelease = f[4].split(".").map(h => {
        if (/^[0-9]+$/.test(h)) {
          const p = +h;
          if (p >= 0 && p < e) return p
        }
        return h
      }) : this.prerelease = [], this.build = f[5] ? f[5].split(".") : [], this.format()
    }
    format() {
      return this.version = `${this.major}.${this.minor}.${this.patch}`, this.prerelease.length && (this.version +=
        `-${this.prerelease.join(".")}`), this.version
    }
    toString() {
      return this.version
    }
    compare(u) {
      if (n("SemVer.compare", this.version, this.options, u), !(u instanceof l)) {
        if (typeof u == "string" && u === this.version) return 0;
        u = new l(u, this.options)
      }
      return u.version === this.version ? 0 : this.compareMain(u) || this.comparePre(u)
    }
    compareMain(u) {
      return u instanceof l || (u = new l(u, this.options)), this.major < u.major ? -1 : this.major > u.major ? 1 :
        this.minor < u.minor ? -1 : this.minor > u.minor ? 1 : this.patch < u.patch ? -1 : this.patch > u.patch ? 1 :
        0
    }
    comparePre(u) {
      if (u instanceof l || (u = new l(u, this.options)), this.prerelease.length && !u.prerelease.length) return -1;
      if (!this.prerelease.length && u.prerelease.length) return 1;
      if (!this.prerelease.length && !u.prerelease.length) return 0;
      let o = 0;
      do {
        const f = this.prerelease[o],
          h = u.prerelease[o];
        if (n("prerelease compare", o, f, h), f === void 0 && h === void 0) return 0;
        if (h === void 0) return 1;
        if (f === void 0) return -1;
        if (f === h) continue;
        return a(f, h)
      } while (++o)
    }
    compareBuild(u) {
      u instanceof l || (u = new l(u, this.options));
      let o = 0;
      do {
        const f = this.build[o],
          h = u.build[o];
        if (n("build compare", o, f, h), f === void 0 && h === void 0) return 0;
        if (h === void 0) return 1;
        if (f === void 0) return -1;
        if (f === h) continue;
        return a(f, h)
      } while (++o)
    }
    inc(u, o, f) {
      if (u.startsWith("pre")) {
        if (!o && f === !1) throw new Error("invalid increment argument: identifier is empty");
        if (o) {
          const h = `-${o}`.match(this.options.loose ? r[s.PRERELEASELOOSE] : r[s.PRERELEASE]);
          if (!h || h[1] !== o) throw new Error(`invalid identifier: ${o}`)
        }
      }
      switch (u) {
        case "premajor":
          this.prerelease.length = 0, this.patch = 0, this.minor = 0, this.major++, this.inc("pre", o, f);
          break;
        case "preminor":
          this.prerelease.length = 0, this.patch = 0, this.minor++, this.inc("pre", o, f);
          break;
        case "prepatch":
          this.prerelease.length = 0, this.inc("patch", o, f), this.inc("pre", o, f);
          break;
        case "prerelease":
          this.prerelease.length === 0 && this.inc("patch", o, f), this.inc("pre", o, f);
          break;
        case "release":
          if (this.prerelease.length === 0) throw new Error(`version ${this.raw} is not a prerelease`);
          this.prerelease.length = 0;
          break;
        case "major":
          (this.minor !== 0 || this.patch !== 0 || this.prerelease.length === 0) && this.major++, this.minor = 0, this
            .patch = 0, this.prerelease = [];
          break;
        case "minor":
          (this.patch !== 0 || this.prerelease.length === 0) && this.minor++, this.patch = 0, this.prerelease = [];
          break;
        case "patch":
          this.prerelease.length === 0 && this.patch++, this.prerelease = [];
          break;
        case "pre": {
          const h = Number(f) ? 1 : 0;
          if (this.prerelease.length === 0) this.prerelease = [h];
          else {
            let p = this.prerelease.length;
            for (; --p >= 0;) typeof this.prerelease[p] == "number" && (this.prerelease[p]++, p = -2);
            if (p === -1) {
              if (o === this.prerelease.join(".") && f === !1) throw new Error(
                "invalid increment argument: identifier already exists");
              this.prerelease.push(h)
            }
          }
          if (o) {
            let p = [o, h];
            f === !1 && (p = [o]), a(this.prerelease[0], o) === 0 ? isNaN(this.prerelease[1]) && (this.prerelease =
              p) : this.prerelease = p
          }
          break
        }
        default:
          throw new Error(`invalid increment argument: ${u}`)
      }
      return this.raw = this.format(), this.build.length && (this.raw += `+${this.build.join(".")}`), this
    }
  }
  return Ne = l, Ne
}
var Me, Ht;

function Q() {
  if (Ht) return Me;
  Ht = 1;
  const n = k();
  return Me = (e, r, s = !1) => {
    if (e instanceof n) return e;
    try {
      return new n(e, r)
    } catch (i) {
      if (!s) return null;
      throw i
    }
  }, Me
}
var be, Jt;

function ws() {
  if (Jt) return be;
  Jt = 1;
  const n = Q();
  return be = (e, r) => {
    const s = n(e, r);
    return s ? s.version : null
  }, be
}
var Pe, Yt;

function Cs() {
  if (Yt) return Pe;
  Yt = 1;
  const n = Q();
  return Pe = (e, r) => {
    const s = n(e.trim().replace(/^[=v]+/, ""), r);
    return s ? s.version : null
  }, Pe
}
var qe, Kt;

function Is() {
  if (Kt) return qe;
  Kt = 1;
  const n = k();
  return qe = (e, r, s, i, a) => {
    typeof s == "string" && (a = i, i = s, s = void 0);
    try {
      return new n(e instanceof n ? e.version : e, s).inc(r, i, a).version
    } catch {
      return null
    }
  }, qe
}
var De, Qt;

function Rs() {
  if (Qt) return De;
  Qt = 1;
  const n = Q();
  return De = (e, r) => {
    const s = n(e, null, !0),
      i = n(r, null, !0),
      a = s.compare(i);
    if (a === 0) return null;
    const l = a > 0,
      c = l ? s : i,
      u = l ? i : s,
      o = !!c.prerelease.length;
    if (!!u.prerelease.length && !o) {
      if (!u.patch && !u.minor) return "major";
      if (u.compareMain(c) === 0) return u.minor && !u.patch ? "minor" : "patch"
    }
    const h = o ? "pre" : "";
    return s.major !== i.major ? h + "major" : s.minor !== i.minor ? h + "minor" : s.patch !== i.patch ? h + "patch" :
      "prerelease"
  }, De
}
var Fe, Zt;

function As() {
  if (Zt) return Fe;
  Zt = 1;
  const n = k();
  return Fe = (e, r) => new n(e, r).major, Fe
}
var je, er;

function Ls() {
  if (er) return je;
  er = 1;
  const n = k();
  return je = (e, r) => new n(e, r).minor, je
}
var Ge, tr;

function Os() {
  if (tr) return Ge;
  tr = 1;
  const n = k();
  return Ge = (e, r) => new n(e, r).patch, Ge
}
var Ue, rr;

function xs() {
  if (rr) return Ue;
  rr = 1;
  const n = Q();
  return Ue = (e, r) => {
    const s = n(e, r);
    return s && s.prerelease.length ? s.prerelease : null
  }, Ue
}
var ke, sr;

function V() {
  if (sr) return ke;
  sr = 1;
  const n = k();
  return ke = (e, r, s) => new n(e, s).compare(new n(r, s)), ke
}
var Be, nr;

function $s() {
  if (nr) return Be;
  nr = 1;
  const n = V();
  return Be = (e, r, s) => n(r, e, s), Be
}
var Ve, ir;

function Ns() {
  if (ir) return Ve;
  ir = 1;
  const n = V();
  return Ve = (e, r) => n(e, r, !0), Ve
}
var Xe, ar;

function St() {
  if (ar) return Xe;
  ar = 1;
  const n = k();
  return Xe = (e, r, s) => {
    const i = new n(e, s),
      a = new n(r, s);
    return i.compare(a) || i.compareBuild(a)
  }, Xe
}
var We, or;

function Ms() {
  if (or) return We;
  or = 1;
  const n = St();
  return We = (e, r) => e.sort((s, i) => n(s, i, r)), We
}
var ze, lr;

function bs() {
  if (lr) return ze;
  lr = 1;
  const n = St();
  return ze = (e, r) => e.sort((s, i) => n(i, s, r)), ze
}
var He, ur;

function ve() {
  if (ur) return He;
  ur = 1;
  const n = V();
  return He = (e, r, s) => n(e, r, s) > 0, He
}
var Je, cr;

function wt() {
  if (cr) return Je;
  cr = 1;
  const n = V();
  return Je = (e, r, s) => n(e, r, s) < 0, Je
}
var Ye, hr;

function Fr() {
  if (hr) return Ye;
  hr = 1;
  const n = V();
  return Ye = (e, r, s) => n(e, r, s) === 0, Ye
}
var Ke, fr;

function jr() {
  if (fr) return Ke;
  fr = 1;
  const n = V();
  return Ke = (e, r, s) => n(e, r, s) !== 0, Ke
}
var Qe, dr;

function Ct() {
  if (dr) return Qe;
  dr = 1;
  const n = V();
  return Qe = (e, r, s) => n(e, r, s) >= 0, Qe
}
var Ze, pr;

function It() {
  if (pr) return Ze;
  pr = 1;
  const n = V();
  return Ze = (e, r, s) => n(e, r, s) <= 0, Ze
}
var et, mr;

function Gr() {
  if (mr) return et;
  mr = 1;
  const n = Fr(),
    t = jr(),
    e = ve(),
    r = Ct(),
    s = wt(),
    i = It();
  return et = (l, c, u, o) => {
    switch (c) {
      case "===":
        return typeof l == "object" && (l = l.version), typeof u == "object" && (u = u.version), l === u;
      case "!==":
        return typeof l == "object" && (l = l.version), typeof u == "object" && (u = u.version), l !== u;
      case "":
      case "=":
      case "==":
        return n(l, u, o);
      case "!=":
        return t(l, u, o);
      case ">":
        return e(l, u, o);
      case ">=":
        return r(l, u, o);
      case "<":
        return s(l, u, o);
      case "<=":
        return i(l, u, o);
      default:
        throw new TypeError(`Invalid operator: ${c}`)
    }
  }, et
}
var tt, gr;

function Ps() {
  if (gr) return tt;
  gr = 1;
  const n = k(),
    t = Q(),
    {
      safeRe: e,
      t: r
    } = ie();
  return tt = (i, a) => {
    if (i instanceof n) return i;
    if (typeof i == "number" && (i = String(i)), typeof i != "string") return null;
    a = a || {};
    let l = null;
    if (!a.rtl) l = i.match(a.includePrerelease ? e[r.COERCEFULL] : e[r.COERCE]);
    else {
      const p = a.includePrerelease ? e[r.COERCERTLFULL] : e[r.COERCERTL];
      let S;
      for (;
        (S = p.exec(i)) && (!l || l.index + l[0].length !== i.length);)(!l || S.index + S[0].length !== l.index + l[0]
        .length) && (l = S), p.lastIndex = S.index + S[1].length + S[2].length;
      p.lastIndex = -1
    }
    if (l === null) return null;
    const c = l[2],
      u = l[3] || "0",
      o = l[4] || "0",
      f = a.includePrerelease && l[5] ? `-${l[5]}` : "",
      h = a.includePrerelease && l[6] ? `+${l[6]}` : "";
    return t(`${c}.${u}.${o}${f}${h}`, a)
  }, tt
}
var rt, vr;

function qs() {
  if (vr) return rt;
  vr = 1;
  class n {
    constructor() {
      this.max = 1e3, this.map = new Map
    }
    get(e) {
      const r = this.map.get(e);
      if (r !== void 0) return this.map.delete(e), this.map.set(e, r), r
    }
    delete(e) {
      return this.map.delete(e)
    }
    set(e, r) {
      if (!this.delete(e) && r !== void 0) {
        if (this.map.size >= this.max) {
          const i = this.map.keys().next().value;
          this.delete(i)
        }
        this.map.set(e, r)
      }
      return this
    }
  }
  return rt = n, rt
}
var st, Er;

function X() {
  if (Er) return st;
  Er = 1;
  const n = /\s+/g;
  class t {
    constructor(T, O) {
      if (O = s(O), T instanceof t) return T.loose === !!O.loose && T.includePrerelease === !!O.includePrerelease ?
        T : new t(T.raw, O);
      if (T instanceof i) return this.raw = T.value, this.set = [
        [T]
      ], this.formatted = void 0, this;
      if (this.options = O, this.loose = !!O.loose, this.includePrerelease = !!O.includePrerelease, this.raw = T
        .trim().replace(n, " "), this.set = this.raw.split("||").map(A => this.parseRange(A.trim())).filter(A => A
          .length), !this.set.length) throw new TypeError(`Invalid SemVer Range: ${this.raw}`);
      if (this.set.length > 1) {
        const A = this.set[0];
        if (this.set = this.set.filter(x => !m(x[0])), this.set.length === 0) this.set = [A];
        else if (this.set.length > 1) {
          for (const x of this.set)
            if (x.length === 1 && E(x[0])) {
              this.set = [x];
              break
            }
        }
      }
      this.formatted = void 0
    }
    get range() {
      if (this.formatted === void 0) {
        this.formatted = "";
        for (let T = 0; T < this.set.length; T++) {
          T > 0 && (this.formatted += "||");
          const O = this.set[T];
          for (let A = 0; A < O.length; A++) A > 0 && (this.formatted += " "), this.formatted += O[A].toString()
          .trim()
        }
      }
      return this.formatted
    }
    format() {
      return this.range
    }
    toString() {
      return this.range
    }
    parseRange(T) {
      const A = ((this.options.includePrerelease && p) | (this.options.loose && S)) + ":" + T,
        x = r.get(A);
      if (x) return x;
      const L = this.options.loose,
        $ = L ? c[u.HYPHENRANGELOOSE] : c[u.HYPHENRANGE];
      T = T.replace($, W(this.options.includePrerelease)), a("hyphen replace", T), T = T.replace(c[u.COMPARATORTRIM],
        o), a("comparator trim", T), T = T.replace(c[u.TILDETRIM], f), a("tilde trim", T), T = T.replace(c[u
        .CARETTRIM], h), a("caret trim", T);
      let D = T.split(" ").map(j => b(j, this.options)).join(" ").split(/\s+/).map(j => G(j, this.options));
      L && (D = D.filter(j => (a("loose invalid filter", j, this.options), !!j.match(c[u.COMPARATORLOOSE])))), a(
        "range list", D);
      const M = new Map,
        F = D.map(j => new i(j, this.options));
      for (const j of F) {
        if (m(j)) return [j];
        M.set(j.value, j)
      }
      M.size > 1 && M.has("") && M.delete("");
      const U = [...M.values()];
      return r.set(A, U), U
    }
    intersects(T, O) {
      if (!(T instanceof t)) throw new TypeError("a Range is required");
      return this.set.some(A => R(A, O) && T.set.some(x => R(x, O) && A.every(L => x.every($ => L.intersects($, O)))))
    }
    test(T) {
      if (!T) return !1;
      if (typeof T == "string") try {
        T = new l(T, this.options)
      } catch {
        return !1
      }
      for (let O = 0; O < this.set.length; O++)
        if (K(this.set[O], T, this.options)) return !0;
      return !1
    }
  }
  st = t;
  const e = qs(),
    r = new e,
    s = Tt(),
    i = Ee(),
    a = ge(),
    l = k(),
    {
      safeRe: c,
      t: u,
      comparatorTrimReplace: o,
      tildeTrimReplace: f,
      caretTrimReplace: h
    } = ie(),
    {
      FLAG_INCLUDE_PRERELEASE: p,
      FLAG_LOOSE: S
    } = me(),
    m = C => C.value === "<0.0.0-0",
    E = C => C.value === "",
    R = (C, T) => {
      let O = !0;
      const A = C.slice();
      let x = A.pop();
      for (; O && A.length;) O = A.every(L => x.intersects(L, T)), x = A.pop();
      return O
    },
    b = (C, T) => (C = C.replace(c[u.BUILD], ""), a("comp", C, T), C = v(C, T), a("caret", C), C = g(C, T), a("tildes",
      C), C = y(C, T), a("xrange", C), C = N(C, T), a("stars", C), C),
    I = C => !C || C.toLowerCase() === "x" || C === "*",
    g = (C, T) => C.trim().split(/\s+/).map(O => d(O, T)).join(" "),
    d = (C, T) => {
      const O = T.loose ? c[u.TILDELOOSE] : c[u.TILDE];
      return C.replace(O, (A, x, L, $, D) => {
        a("tilde", C, A, x, L, $, D);
        let M;
        return I(x) ? M = "" : I(L) ? M = `>=${x}.0.0 <${+x+1}.0.0-0` : I($) ? M =
          `>=${x}.${L}.0 <${x}.${+L+1}.0-0` : D ? (a("replaceTilde pr", D), M =
            `>=${x}.${L}.${$}-${D} <${x}.${+L+1}.0-0`) : M = `>=${x}.${L}.${$} <${x}.${+L+1}.0-0`, a("tilde return",
            M), M
      })
    },
    v = (C, T) => C.trim().split(/\s+/).map(O => w(O, T)).join(" "),
    w = (C, T) => {
      a("caret", C, T);
      const O = T.loose ? c[u.CARETLOOSE] : c[u.CARET],
        A = T.includePrerelease ? "-0" : "";
      return C.replace(O, (x, L, $, D, M) => {
        a("caret", C, x, L, $, D, M);
        let F;
        return I(L) ? F = "" : I($) ? F = `>=${L}.0.0${A} <${+L+1}.0.0-0` : I(D) ? L === "0" ? F =
          `>=${L}.${$}.0${A} <${L}.${+$+1}.0-0` : F = `>=${L}.${$}.0${A} <${+L+1}.0.0-0` : M ? (a("replaceCaret pr",
              M), L === "0" ? $ === "0" ? F = `>=${L}.${$}.${D}-${M} <${L}.${$}.${+D+1}-0` : F =
            `>=${L}.${$}.${D}-${M} <${L}.${+$+1}.0-0` : F = `>=${L}.${$}.${D}-${M} <${+L+1}.0.0-0`) : (a("no pr"),
            L === "0" ? $ === "0" ? F = `>=${L}.${$}.${D}${A} <${L}.${$}.${+D+1}-0` : F =
            `>=${L}.${$}.${D}${A} <${L}.${+$+1}.0-0` : F = `>=${L}.${$}.${D} <${+L+1}.0.0-0`), a("caret return", F),
          F
      })
    },
    y = (C, T) => (a("replaceXRanges", C, T), C.split(/\s+/).map(O => q(O, T)).join(" ")),
    q = (C, T) => {
      C = C.trim();
      const O = T.loose ? c[u.XRANGELOOSE] : c[u.XRANGE];
      return C.replace(O, (A, x, L, $, D, M) => {
        a("xRange", C, A, x, L, $, D, M);
        const F = I(L),
          U = F || I($),
          j = U || I(D),
          te = j;
        return x === "=" && te && (x = ""), M = T.includePrerelease ? "-0" : "", F ? x === ">" || x === "<" ? A =
          "<0.0.0-0" : A = "*" : x && te ? (U && ($ = 0), D = 0, x === ">" ? (x = ">=", U ? (L = +L + 1, $ = 0, D =
            0) : ($ = +$ + 1, D = 0)) : x === "<=" && (x = "<", U ? L = +L + 1 : $ = +$ + 1), x === "<" && (M =
            "-0"), A = `${x+L}.${$}.${D}${M}`) : U ? A = `>=${L}.0.0${M} <${+L+1}.0.0-0` : j && (A =
            `>=${L}.${$}.0${M} <${L}.${+$+1}.0-0`), a("xRange return", A), A
      })
    },
    N = (C, T) => (a("replaceStars", C, T), C.trim().replace(c[u.STAR], "")),
    G = (C, T) => (a("replaceGTE0", C, T), C.trim().replace(c[T.includePrerelease ? u.GTE0PRE : u.GTE0], "")),
    W = C => (T, O, A, x, L, $, D, M, F, U, j, te) => (I(A) ? O = "" : I(x) ? O = `>=${A}.0.0${C?"-0":""}` : I(L) ? O =
      `>=${A}.${x}.0${C?"-0":""}` : $ ? O = `>=${O}` : O = `>=${O}${C?"-0":""}`, I(F) ? M = "" : I(U) ? M =
      `<${+F+1}.0.0-0` : I(j) ? M = `<${F}.${+U+1}.0-0` : te ? M = `<=${F}.${U}.${j}-${te}` : C ? M =
      `<${F}.${U}.${+j+1}-0` : M = `<=${M}`, `${O} ${M}`.trim()),
    K = (C, T, O) => {
      for (let A = 0; A < C.length; A++)
        if (!C[A].test(T)) return !1;
      if (T.prerelease.length && !O.includePrerelease) {
        for (let A = 0; A < C.length; A++)
          if (a(C[A].semver), C[A].semver !== i.ANY && C[A].semver.prerelease.length > 0) {
            const x = C[A].semver;
            if (x.major === T.major && x.minor === T.minor && x.patch === T.patch) return !0
          } return !1
      }
      return !0
    };
  return st
}
var nt, yr;

function Ee() {
  if (yr) return nt;
  yr = 1;
  const n = Symbol("SemVer ANY");
  class t {
    static get ANY() {
      return n
    }
    constructor(o, f) {
      if (f = e(f), o instanceof t) {
        if (o.loose === !!f.loose) return o;
        o = o.value
      }
      o = o.trim().split(/\s+/).join(" "), a("comparator", o, f), this.options = f, this.loose = !!f.loose, this
        .parse(o), this.semver === n ? this.value = "" : this.value = this.operator + this.semver.version, a("comp",
          this)
    }
    parse(o) {
      const f = this.options.loose ? r[s.COMPARATORLOOSE] : r[s.COMPARATOR],
        h = o.match(f);
      if (!h) throw new TypeError(`Invalid comparator: ${o}`);
      this.operator = h[1] !== void 0 ? h[1] : "", this.operator === "=" && (this.operator = ""), h[2] ? this.semver =
        new l(h[2], this.options.loose) : this.semver = n
    }
    toString() {
      return this.value
    }
    test(o) {
      if (a("Comparator.test", o, this.options.loose), this.semver === n || o === n) return !0;
      if (typeof o == "string") try {
        o = new l(o, this.options)
      } catch {
        return !1
      }
      return i(o, this.operator, this.semver, this.options)
    }
    intersects(o, f) {
      if (!(o instanceof t)) throw new TypeError("a Comparator is required");
      return this.operator === "" ? this.value === "" ? !0 : new c(o.value, f).test(this.value) : o.operator === "" ?
        o.value === "" ? !0 : new c(this.value, f).test(o.semver) : (f = e(f), f.includePrerelease && (this.value ===
          "<0.0.0-0" || o.value === "<0.0.0-0") || !f.includePrerelease && (this.value.startsWith("<0.0.0") || o
          .value.startsWith("<0.0.0")) ? !1 : !!(this.operator.startsWith(">") && o.operator.startsWith(">") || this
          .operator.startsWith("<") && o.operator.startsWith("<") || this.semver.version === o.semver.version &&
          this.operator.includes("=") && o.operator.includes("=") || i(this.semver, "<", o.semver, f) && this
          .operator.startsWith(">") && o.operator.startsWith("<") || i(this.semver, ">", o.semver, f) && this
          .operator.startsWith("<") && o.operator.startsWith(">")))
    }
  }
  nt = t;
  const e = Tt(),
    {
      safeRe: r,
      t: s
    } = ie(),
    i = Gr(),
    a = ge(),
    l = k(),
    c = X();
  return nt
}
var it, _r;

function ye() {
  if (_r) return it;
  _r = 1;
  const n = X();
  return it = (e, r, s) => {
    try {
      r = new n(r, s)
    } catch {
      return !1
    }
    return r.test(e)
  }, it
}
var at, Tr;

function Ds() {
  if (Tr) return at;
  Tr = 1;
  const n = X();
  return at = (e, r) => new n(e, r).set.map(s => s.map(i => i.value).join(" ").trim().split(" ")), at
}
var ot, Sr;

function Fs() {
  if (Sr) return ot;
  Sr = 1;
  const n = k(),
    t = X();
  return ot = (r, s, i) => {
    let a = null,
      l = null,
      c = null;
    try {
      c = new t(s, i)
    } catch {
      return null
    }
    return r.forEach(u => {
      c.test(u) && (!a || l.compare(u) === -1) && (a = u, l = new n(a, i))
    }), a
  }, ot
}
var lt, wr;

function js() {
  if (wr) return lt;
  wr = 1;
  const n = k(),
    t = X();
  return lt = (r, s, i) => {
    let a = null,
      l = null,
      c = null;
    try {
      c = new t(s, i)
    } catch {
      return null
    }
    return r.forEach(u => {
      c.test(u) && (!a || l.compare(u) === 1) && (a = u, l = new n(a, i))
    }), a
  }, lt
}
var ut, Cr;

function Gs() {
  if (Cr) return ut;
  Cr = 1;
  const n = k(),
    t = X(),
    e = ve();
  return ut = (s, i) => {
    s = new t(s, i);
    let a = new n("0.0.0");
    if (s.test(a) || (a = new n("0.0.0-0"), s.test(a))) return a;
    a = null;
    for (let l = 0; l < s.set.length; ++l) {
      const c = s.set[l];
      let u = null;
      c.forEach(o => {
        const f = new n(o.semver.version);
        switch (o.operator) {
          case ">":
            f.prerelease.length === 0 ? f.patch++ : f.prerelease.push(0), f.raw = f.format();
          case "":
          case ">=":
            (!u || e(f, u)) && (u = f);
            break;
          case "<":
          case "<=":
            break;
          default:
            throw new Error(`Unexpected operation: ${o.operator}`)
        }
      }), u && (!a || e(a, u)) && (a = u)
    }
    return a && s.test(a) ? a : null
  }, ut
}
var ct, Ir;

function Us() {
  if (Ir) return ct;
  Ir = 1;
  const n = X();
  return ct = (e, r) => {
    try {
      return new n(e, r).range || "*"
    } catch {
      return null
    }
  }, ct
}
var ht, Rr;

function Rt() {
  if (Rr) return ht;
  Rr = 1;
  const n = k(),
    t = Ee(),
    {
      ANY: e
    } = t,
    r = X(),
    s = ye(),
    i = ve(),
    a = wt(),
    l = It(),
    c = Ct();
  return ht = (o, f, h, p) => {
    o = new n(o, p), f = new r(f, p);
    let S, m, E, R, b;
    switch (h) {
      case ">":
        S = i, m = l, E = a, R = ">", b = ">=";
        break;
      case "<":
        S = a, m = c, E = i, R = "<", b = "<=";
        break;
      default:
        throw new TypeError('Must provide a hilo val of "<" or ">"')
    }
    if (s(o, f, p)) return !1;
    for (let I = 0; I < f.set.length; ++I) {
      const g = f.set[I];
      let d = null,
        v = null;
      if (g.forEach(w => {
          w.semver === e && (w = new t(">=0.0.0")), d = d || w, v = v || w, S(w.semver, d.semver, p) ? d = w : E(w
            .semver, v.semver, p) && (v = w)
        }), d.operator === R || d.operator === b || (!v.operator || v.operator === R) && m(o, v.semver)) return !1;
      if (v.operator === b && E(o, v.semver)) return !1
    }
    return !0
  }, ht
}
var ft, Ar;

function ks() {
  if (Ar) return ft;
  Ar = 1;
  const n = Rt();
  return ft = (e, r, s) => n(e, r, ">", s), ft
}
var dt, Lr;

function Bs() {
  if (Lr) return dt;
  Lr = 1;
  const n = Rt();
  return dt = (e, r, s) => n(e, r, "<", s), dt
}
var pt, Or;

function Vs() {
  if (Or) return pt;
  Or = 1;
  const n = X();
  return pt = (e, r, s) => (e = new n(e, s), r = new n(r, s), e.intersects(r, s)), pt
}
var mt, xr;

function Xs() {
  if (xr) return mt;
  xr = 1;
  const n = ye(),
    t = V();
  return mt = (e, r, s) => {
    const i = [];
    let a = null,
      l = null;
    const c = e.sort((h, p) => t(h, p, s));
    for (const h of c) n(h, r, s) ? (l = h, a || (a = h)) : (l && i.push([a, l]), l = null, a = null);
    a && i.push([a, null]);
    const u = [];
    for (const [h, p] of i) h === p ? u.push(h) : !p && h === c[0] ? u.push("*") : p ? h === c[0] ? u.push(`<=${p}`) :
      u.push(`${h} - ${p}`) : u.push(`>=${h}`);
    const o = u.join(" || "),
      f = typeof r.raw == "string" ? r.raw : String(r);
    return o.length < f.length ? o : r
  }, mt
}
var gt, $r;

function Ws() {
  if ($r) return gt;
  $r = 1;
  const n = X(),
    t = Ee(),
    {
      ANY: e
    } = t,
    r = ye(),
    s = V(),
    i = (f, h, p = {}) => {
      if (f === h) return !0;
      f = new n(f, p), h = new n(h, p);
      let S = !1;
      e: for (const m of f.set) {
        for (const E of h.set) {
          const R = c(m, E, p);
          if (S = S || R !== null, R) continue e
        }
        if (S) return !1
      }
      return !0
    },
    a = [new t(">=0.0.0-0")],
    l = [new t(">=0.0.0")],
    c = (f, h, p) => {
      if (f === h) return !0;
      if (f.length === 1 && f[0].semver === e) {
        if (h.length === 1 && h[0].semver === e) return !0;
        p.includePrerelease ? f = a : f = l
      }
      if (h.length === 1 && h[0].semver === e) {
        if (p.includePrerelease) return !0;
        h = l
      }
      const S = new Set;
      let m, E;
      for (const y of f) y.operator === ">" || y.operator === ">=" ? m = u(m, y, p) : y.operator === "<" || y
        .operator === "<=" ? E = o(E, y, p) : S.add(y.semver);
      if (S.size > 1) return null;
      let R;
      if (m && E) {
        if (R = s(m.semver, E.semver, p), R > 0) return null;
        if (R === 0 && (m.operator !== ">=" || E.operator !== "<=")) return null
      }
      for (const y of S) {
        if (m && !r(y, String(m), p) || E && !r(y, String(E), p)) return null;
        for (const q of h)
          if (!r(y, String(q), p)) return !1;
        return !0
      }
      let b, I, g, d, v = E && !p.includePrerelease && E.semver.prerelease.length ? E.semver : !1,
        w = m && !p.includePrerelease && m.semver.prerelease.length ? m.semver : !1;
      v && v.prerelease.length === 1 && E.operator === "<" && v.prerelease[0] === 0 && (v = !1);
      for (const y of h) {
        if (d = d || y.operator === ">" || y.operator === ">=", g = g || y.operator === "<" || y.operator === "<=", m) {
          if (w && y.semver.prerelease && y.semver.prerelease.length && y.semver.major === w.major && y.semver.minor ===
            w.minor && y.semver.patch === w.patch && (w = !1), y.operator === ">" || y.operator === ">=") {
            if (b = u(m, y, p), b === y && b !== m) return !1
          } else if (m.operator === ">=" && !r(m.semver, String(y), p)) return !1
        }
        if (E) {
          if (v && y.semver.prerelease && y.semver.prerelease.length && y.semver.major === v.major && y.semver.minor ===
            v.minor && y.semver.patch === v.patch && (v = !1), y.operator === "<" || y.operator === "<=") {
            if (I = o(E, y, p), I === y && I !== E) return !1
          } else if (E.operator === "<=" && !r(E.semver, String(y), p)) return !1
        }
        if (!y.operator && (E || m) && R !== 0) return !1
      }
      return !(m && g && !E && R !== 0 || E && d && !m && R !== 0 || w || v)
    },
    u = (f, h, p) => {
      if (!f) return h;
      const S = s(f.semver, h.semver, p);
      return S > 0 ? f : S < 0 || h.operator === ">" && f.operator === ">=" ? h : f
    },
    o = (f, h, p) => {
      if (!f) return h;
      const S = s(f.semver, h.semver, p);
      return S < 0 ? f : S > 0 || h.operator === "<" && f.operator === "<=" ? h : f
    };
  return gt = i, gt
}
var vt, Nr;

function zs() {
  if (Nr) return vt;
  Nr = 1;
  const n = ie(),
    t = me(),
    e = k(),
    r = Dr(),
    s = Q(),
    i = ws(),
    a = Cs(),
    l = Is(),
    c = Rs(),
    u = As(),
    o = Ls(),
    f = Os(),
    h = xs(),
    p = V(),
    S = $s(),
    m = Ns(),
    E = St(),
    R = Ms(),
    b = bs(),
    I = ve(),
    g = wt(),
    d = Fr(),
    v = jr(),
    w = Ct(),
    y = It(),
    q = Gr(),
    N = Ps(),
    G = Ee(),
    W = X(),
    K = ye(),
    C = Ds(),
    T = Fs(),
    O = js(),
    A = Gs(),
    x = Us(),
    L = Rt(),
    $ = ks(),
    D = Bs(),
    M = Vs(),
    F = Xs(),
    U = Ws();
  return vt = {
    parse: s,
    valid: i,
    clean: a,
    inc: l,
    diff: c,
    major: u,
    minor: o,
    patch: f,
    prerelease: h,
    compare: p,
    rcompare: S,
    compareLoose: m,
    compareBuild: E,
    sort: R,
    rsort: b,
    gt: I,
    lt: g,
    eq: d,
    neq: v,
    gte: w,
    lte: y,
    cmp: q,
    coerce: N,
    Comparator: G,
    Range: W,
    satisfies: K,
    toComparators: C,
    maxSatisfying: T,
    minSatisfying: O,
    minVersion: A,
    validRange: x,
    outside: L,
    gtr: $,
    ltr: D,
    intersects: M,
    simplifyRange: F,
    subset: U,
    SemVer: e,
    re: n.re,
    src: n.src,
    tokens: n.t,
    SEMVER_SPEC_VERSION: t.SEMVER_SPEC_VERSION,
    RELEASE_TYPES: t.RELEASE_TYPES,
    compareIdentifiers: r.compareIdentifiers,
    rcompareIdentifiers: r.rcompareIdentifiers
  }, vt
}
zs();
new TextEncoder;
var pe = {
  exports: {}
};
pe.exports;
var Mr;

function Hs() {
  return Mr || (Mr = 1, function(n) {
    const e = (i = 0) => a => `\x1B[${38+i};5;${a}m`,
      r = (i = 0) => (a, l, c) => `\x1B[${38+i};2;${a};${l};${c}m`;

    function s() {
      const i = new Map,
        a = {
          modifier: {
            reset: [0, 0],
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
      a.color.gray = a.color.blackBright, a.bgColor.bgGray = a.bgColor.bgBlackBright, a.color.grey = a.color
        .blackBright, a.bgColor.bgGrey = a.bgColor.bgBlackBright;
      for (const [l, c] of Object.entries(a)) {
        for (const [u, o] of Object.entries(c)) a[u] = {
          open: `\x1B[${o[0]}m`,
          close: `\x1B[${o[1]}m`
        }, c[u] = a[u], i.set(o[0], o[1]);
        Object.defineProperty(a, l, {
          value: c,
          enumerable: !1
        })
      }
      return Object.defineProperty(a, "codes", {
          value: i,
          enumerable: !1
        }), a.color.close = "\x1B[39m", a.bgColor.close = "\x1B[49m", a.color.ansi256 = e(), a.color.ansi16m = r(),
        a.bgColor.ansi256 = e(10), a.bgColor.ansi16m = r(10), Object.defineProperties(a, {
          rgbToAnsi256: {
            value: (l, c, u) => l === c && c === u ? l < 8 ? 16 : l > 248 ? 231 : Math.round((l - 8) / 247 * 24) +
              232 : 16 + 36 * Math.round(l / 255 * 5) + 6 * Math.round(c / 255 * 5) + Math.round(u / 255 * 5),
            enumerable: !1
          },
          hexToRgb: {
            value: l => {
              const c = /(?<colorString>[a-f\d]{6}|[a-f\d]{3})/i.exec(l.toString(16));
              if (!c) return [0, 0, 0];
              let {
                colorString: u
              } = c.groups;
              u.length === 3 && (u = u.split("").map(f => f + f).join(""));
              const o = Number.parseInt(u, 16);
              return [o >> 16 & 255, o >> 8 & 255, o & 255]
            },
            enumerable: !1
          },
          hexToAnsi256: {
            value: l => a.rgbToAnsi256(...a.hexToRgb(l)),
            enumerable: !1
          }
        }), a
    }
    Object.defineProperty(n, "exports", {
      enumerable: !0,
      get: s
    })
  }(pe)), pe.exports
}
var Js = Hs();
const Ys = qr(Js),
  {
    color: Rn
  } = Ys;
new Set("ABCDEFGHIJKLMNOPQRSTUVXYZabcdefghijklmnopqrstuvxyz0123456789");
class At {}
class Ur extends At {
  writeSession(t) {
    const e = [];
    t.initialContext.systemMessage && e.push(new fs(t.initialContext.systemMessage));
    for (const r of t.history) e.push(...this.writeMessageTuple(r));
    return t.nextMessage && e.push(...this.writeMessageTuple(t.nextMessage)), e.length > 0 && !(e[e.length -
      1] instanceof le) && e.push(new le("Please continue.")), e
  }
  writeMessageTuple(t) {
    const e = [],
      r = Array.isArray(t.user.content) ? t.user.content.map(s => s.type === "text" ? s.text : `[${s.type}]`).join(
        " ") : t.user.content;
    if (e.push(new le(r)), e.push(new hs(t.assistant.content)), t.toolResponse) {
      const s = t.toolResponse.responses.map(i => i.content).join(`
`);
      e.push(new le(`Tool response: ${s}`))
    }
    return e
  }
}
class kr extends At {
  writeSession(t) {
    const e = [];
    for (const r of t.history) e.push(...this.writeMessageTuple(r));
    return t.nextMessage && e.push(...this.writeMessageTuple(t.nextMessage)), e
  }
  writeMessageTuple(t) {
    var s;
    const e = {
        id: t.user.id,
        type: "user",
        content: t.user.content,
        timestamp: t.timestamp
      },
      r = {
        id: t.assistant.id,
        type: "assistant",
        content: t.assistant.content,
        timestamp: t.timestamp,
        toolCalls: (s = t.assistant.toolCalls) == null ? void 0 : s.map(i => ({
          id: i.id,
          name: i.name,
          status: i.status,
          parameters: i.args
        })),
        isStreaming: t.assistant.isStreaming
      };
    return [e, r]
  }
}
class Y {
  constructor(t, e, r, s, i, a, l, c, u, o) {
    H(this, "langchainWriter");
    H(this, "uiWriter");
    this.id = t, this.title = e, this.sessionType = r, this.createdAt = s, this.lastModified = i, this.version = a,
      this.initialContext = l, this.history = c, this.nextMessage = u, this.executionMetadata = o
  }
  getMessageById(t) {
    var e;
    return ((e = this.nextMessage) == null ? void 0 : e.id) === t ? this.nextMessage : this.history.find(r => r.id ===
      t)
  }
  getLastMessage() {
    if (this.nextMessage) return this.nextMessage;
    if (this.history.length !== 0) return this.history[this.history.length - 1]
  }
  getPendingApprovals() {
    const t = [];
    this.nextMessage && t.push(...this.nextMessage.pendingApprovals);
    for (const e of this.history) t.push(...e.pendingApprovals);
    return t
  }
  getStreamingMessage() {
    if (this.nextMessage && this.nextMessage.assistant.isStreaming) return this.nextMessage;
    const t = this.history.length > 0 ? this.history[this.history.length - 1] : void 0;
    if (t && t.assistant.isStreaming) return t
  }
  getLangchainWriter() {
    return this.langchainWriter || (this.langchainWriter = new Ur), this.langchainWriter
  }
  getUIWriter() {
    return this.uiWriter || (this.uiWriter = new kr), this.uiWriter
  }
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
    }
  }
  static fromJSON(t) {
    return new Y(t.id, t.title, t.sessionType, t.createdAt, t.lastModified, t.version, t.initialContext, t.history, t
      .nextMessage, t.executionMetadata)
  }
  getMessageCount() {
    return this.history.length + (this.nextMessage ? 1 : 0)
  }
  isWaitingForToolResponse() {
    return this.getPendingApprovals().some(e => e.status === _.ToolCallStatus.Executing)
  }
  hasApprovalRequired() {
    return this.getPendingApprovals().some(e => e.status === _.ToolCallStatus.AwaitingApproval)
  }
  validate() {
    var s;
    const t = [],
      e = [],
      r = this.history.filter(i => i.assistant.isStreaming);
    if ((s = this.nextMessage) != null && s.assistant.isStreaming && r.push(this.nextMessage), r.length > 1 && t
    .push({
        code: "MULTIPLE_STREAMING_MESSAGES",
        message: `Multiple streaming messages detected: ${r.length}`,
        severity: "error"
      }), r.length === 1) {
      const i = this.getLastMessage();
      i && !i.assistant.isStreaming && t.push({
        code: "STREAMING_NOT_LAST",
        message: "Streaming message must be the last message",
        severity: "error"
      })
    }
    for (const i of [...this.history, ...this.nextMessage ? [this.nextMessage] : []])
      if (i.assistant.toolCalls)
        for (const a of i.assistant.toolCalls) a.status === _.ToolCallStatus.Completed && !i.toolResponse && t.push({
          code: "MISSING_TOOL_RESPONSE",
          message: `Tool call ${a.id} marked completed but no response found`,
          path: `message.${i.id}.toolCall.${a.id}`,
          severity: "error"
        }), a.status === _.ToolCallStatus.Approved && !a.approvedAt && e.push({
          code: "MISSING_APPROVAL_TIMESTAMP",
          message: `Tool call ${a.id} approved but no approval timestamp`,
          path: `message.${i.id}.toolCall.${a.id}`,
          severity: "warning"
        }), (a.status === _.ToolCallStatus.Executing || a.status === _.ToolCallStatus.Completed || a.status === _
          .ToolCallStatus.Failed) && !a.executedAt && e.push({
          code: "MISSING_EXECUTION_TIMESTAMP",
          message: `Tool call ${a.id} in status ${a.status} but no execution timestamp`,
          path: `message.${i.id}.toolCall.${a.id}`,
          severity: "warning"
        });
    for (let i = 1; i < this.history.length; i++) {
      const a = this.history[i - 1],
        l = this.history[i];
      l.timestamp < a.timestamp && t.push({
        code: "INVALID_MESSAGE_ORDER",
        message: `Message ${l.id} has earlier timestamp than previous message ${a.id}`,
        severity: "error"
      })
    }
    return {
      isValid: t.length === 0,
      errors: Object.freeze([...t]),
      warnings: Object.freeze([...e])
    }
  }
}

function Ks(n) {
  const t = P.now();
  return new Y(n.id, n.title, n.sessionType, t, t, 0, n.initialContext, [], void 0, n.executionMetadata)
}

function B(n, t, e) {
  const r = P.now(),
    s = n.version + 1,
    i = new Y(n.id, t.title ?? n.title, t.sessionType ?? n.sessionType, n.createdAt, t.lastModified ?? r, t.version ??
      s, t.initialContext ?? n.initialContext, t.history ?? n.history, "nextMessage" in t ? t.nextMessage : n
      .nextMessage, "executionMetadata" in t ? t.executionMetadata : n.executionMetadata);
  return e && (e.cacheSession(i), e.saveSessionAsync(i)), i
}

function Qs(n, t, e) {
  return B(n, {
    history: [...n.history, t]
  }, e)
}

function Z(n, t) {
  return B(n, {
    nextMessage: t
  })
}

function Zs(n) {
  return n.nextMessage ? B(n, {
    history: [...n.history, n.nextMessage],
    nextMessage: void 0
  }) : n
}

function en(n, t) {
  return B(n, {
    title: t
  })
}

function tn(n, t) {
  return B(n, {
    executionMetadata: t
  })
}

function rn(n) {
  return B(n, {
    executionMetadata: void 0
  })
}
class sn extends Et.KiroError {
  constructor(t, e, r) {
    super(`Invalid tool call status transition from ${e} to ${r}`), this.toolCallId = t, this.fromStatus = e, this
      .toStatus = r, this.name = "InvalidTransitionError"
  }
  get userFacingSessionErrorMessage() {
    return `Tool call status transition failed. Cannot change from ${this.fromStatus} to ${this.toStatus}.`
  }
  get userFacingFixCallback() {}
}
class ae extends Et.KiroError {
  constructor(t, e, r) {
    super(`Cannot ${r} tool call in status ${e}`), this.toolCallId = t, this.currentStatus = e, this.operation = r,
      this.name = "InvalidToolCallStateError"
  }
  get userFacingSessionErrorMessage() {
    return `Tool call operation failed. Cannot ${this.operation} when status is ${this.currentStatus}.`
  }
  get userFacingFixCallback() {}
}
class nn extends Et.KiroError {
  constructor(t, e) {
    super(`Tool call execution error: ${e}`), this.toolCallId = t, this.reason = e, this.name =
      "ToolCallExecutionError"
  }
  get userFacingSessionErrorMessage() {
    return `Tool execution failed: ${this.reason}`
  }
  get userFacingFixCallback() {}
}
const _e = {
  pending: [_.ToolCallStatus.AwaitingApproval, _.ToolCallStatus.Executing, _.ToolCallStatus.Failed],
  awaiting_approval: [_.ToolCallStatus.Approved, _.ToolCallStatus.Denied],
  approved: [_.ToolCallStatus.Executing, _.ToolCallStatus.Failed],
  denied: [],
  executing: [_.ToolCallStatus.Completed, _.ToolCallStatus.Failed],
  completed: [],
  failed: []
};

function Lt(n, t) {
  return _e[n].includes(t)
}

function an(n) {
  return _e[n]
}

function on(n) {
  return _e[n].length === 0
}

function Br(n) {
  const t = P.now();
  return {
    id: n.id,
    name: n.name,
    args: n.args,
    status: _.ToolCallStatus.Pending,
    requestedAt: t,
    requiresApproval: n.requiresApproval ?? !1
  }
}

function ln(n) {
  return {
    ...Br({
      ...n,
      requiresApproval: !0
    }),
    status: _.ToolCallStatus.AwaitingApproval
  }
}

function ee(n, t, e) {
  if (!Lt(n.status, t)) throw new sn(n.id, n.status, t);
  const r = P.now(),
    s = {
      ...e
    };
  return t === _.ToolCallStatus.Approved && !s.approvedAt && (s.approvedAt = r), t === _.ToolCallStatus.Executing && !s
    .executedAt && (s.executedAt = r), (t === _.ToolCallStatus.Completed || t === _.ToolCallStatus.Failed) && !s
    .completedAt && (s.completedAt = r), {
      ...n,
      status: t,
      ...s
    }
}

function un(n, t) {
  if (n.status !== _.ToolCallStatus.AwaitingApproval) throw new ae(n.id, n.status, "approve");
  const e = P.now(),
    r = {
      approved: !0,
      userComment: t,
      decidedAt: e
    };
  return ee(n, _.ToolCallStatus.Approved, {
    approvalDecision: r,
    approvedAt: e
  })
}

function cn(n, t) {
  if (n.status !== _.ToolCallStatus.AwaitingApproval) throw new ae(n.id, n.status, "deny");
  const e = P.now(),
    r = {
      approved: !1,
      userComment: t,
      decidedAt: e
    };
  return ee(n, _.ToolCallStatus.Denied, {
    approvalDecision: r
  })
}

function hn(n, t) {
  if (![_.ToolCallStatus.Pending, _.ToolCallStatus.Approved].includes(n.status)) throw new ae(n.id, n.status,
    "start execution for");
  const r = P.now(),
    s = {
      executionId: t,
      startTime: r
    };
  return ee(n, _.ToolCallStatus.Executing, {
    executionMetadata: s,
    executedAt: r
  })
}

function fn(n, t) {
  if (n.status !== _.ToolCallStatus.Executing) throw new ae(n.id, n.status, "complete");
  if (!n.executionMetadata) throw new nn(n.id, "execution metadata is missing");
  const e = P.now(),
    r = {
      ...n.executionMetadata,
      endTime: e,
      duration: t ?? e - n.executionMetadata.startTime
    };
  return ee(n, _.ToolCallStatus.Completed, {
    executionMetadata: r,
    completedAt: e
  })
}

function dn(n, t, e) {
  var l, c;
  if (![_.ToolCallStatus.Pending, _.ToolCallStatus.Approved, _.ToolCallStatus.Executing].includes(n.status))
  throw new ae(n.id, n.status, "fail");
  const s = P.now(),
    i = ((l = n.executionMetadata) == null ? void 0 : l.startTime) ?? n.requestedAt,
    a = {
      executionId: ((c = n.executionMetadata) == null ? void 0 : c.executionId) ?? "unknown",
      startTime: i,
      endTime: s,
      duration: e ?? s - i,
      error: t
    };
  return ee(n, _.ToolCallStatus.Failed, {
    executionMetadata: a,
    completedAt: s
  })
}

function pn(n) {
  return {
    callId: n.callId,
    content: n.content,
    success: !0,
    executedAt: P.now(),
    duration: n.duration,
    metadata: n.metadata
  }
}

function mn(n) {
  return {
    callId: n.callId,
    content: n.error,
    success: !1,
    executedAt: P.now(),
    duration: n.duration,
    metadata: n.metadata
  }
}

function gn(n) {
  return n.requiresApproval && n.status === _.ToolCallStatus.AwaitingApproval
}

function vn(n) {
  return n.status === _.ToolCallStatus.Executing
}

function En(n) {
  return n.status === _.ToolCallStatus.Completed || n.status === _.ToolCallStatus.Failed
}

function yn(n) {
  return n.status === _.ToolCallStatus.Completed
}

function _n(n) {
  var t;
  return (t = n.executionMetadata) == null ? void 0 : t.duration
}
class z {
  static startUserMessage(t, e) {
    return new Vr(t, e)
  }
  static updateStreamingContent(t, e) {
    return new Xr(t, e)
  }
  static addToolCall(t, e) {
    return new Wr(t, e)
  }
  static updateToolCallStatus(t, e) {
    return new zr(t, e)
  }
  static addToolResponse(t, e) {
    return new Hr(t, e)
  }
  static completeMessage(t) {
    return new Jr(t)
  }
}
class Vr extends z {
  constructor(t, e) {
    super(), this.content = t, this.context = e
  }
  validate(t) {
    const e = [],
      r = [];
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
      context: {
        streamingMessageId: s.id
      }
    });
    const i = t.getPendingApprovals();
    return i.length > 0 && e.push({
      code: "PENDING_APPROVALS_EXIST",
      message: `Cannot start new message while ${i.length} tool calls await approval`,
      severity: "error",
      context: {
        pendingApprovalIds: i.map(a => a.id)
      }
    }), {
      isValid: e.length === 0,
      errors: e,
      warnings: r
    }
  }
  apply(t) {
    const e = _.createUserMessage({
        id: P.generateMessageId(),
        content: this.content,
        contextItems: this.context
      }),
      r = _.createAssistantMessage({
        id: P.generateMessageId(),
        content: "",
        isStreaming: !0
      }),
      s = _.createConversationTurn({
        id: P.generateMessageId(),
        user: e,
        assistant: r
      });
    return Promise.resolve(Z(t, s))
  }
}
class Xr extends z {
  constructor(t, e) {
    super(), this.messageId = t, this.content = e
  }
  validate(t) {
    const e = [],
      r = [],
      s = t.getMessageById(this.messageId);
    return s ? (s.assistant.isStreaming || e.push({
      code: "MESSAGE_NOT_STREAMING",
      message: `Cannot update content of non-streaming message ${this.messageId}`,
      severity: "error",
      context: {
        messageId: this.messageId
      }
    }), {
      isValid: e.length === 0,
      errors: e,
      warnings: r
    }) : (e.push({
      code: "MESSAGE_NOT_FOUND",
      message: `Message ${this.messageId} not found`,
      severity: "error",
      context: {
        messageId: this.messageId
      }
    }), {
      isValid: !1,
      errors: e,
      warnings: r
    })
  }
  apply(t) {
    var r;
    if (((r = t.nextMessage) == null ? void 0 : r.id) === this.messageId) {
      const s = _.updateConversationTurnAssistantContent(t.nextMessage, this.content);
      return Promise.resolve(Z(t, s))
    }
    const e = t.history.map(s => s.id === this.messageId ? _.updateConversationTurnAssistantContent(s, this.content) :
      s);
    return Promise.resolve(B(t, {
      history: e
    }))
  }
}
class Wr extends z {
  constructor(t, e) {
    super(), this.messageId = t, this.toolCall = e
  }
  validate(t) {
    var i;
    const e = [],
      r = [],
      s = t.getMessageById(this.messageId);
    return s ? (this.toolCall.id || e.push({
      code: "INVALID_TOOL_CALL",
      message: "Tool call must have an ID",
      severity: "error"
    }), this.toolCall.name || e.push({
      code: "INVALID_TOOL_CALL",
      message: "Tool call must have a name",
      severity: "error"
    }), (i = s.assistant.toolCalls) != null && i.some(a => a.id === this.toolCall.id) && e.push({
      code: "DUPLICATE_TOOL_CALL",
      message: `Tool call with ID ${this.toolCall.id} already exists in message ${this.messageId}`,
      severity: "error",
      context: {
        toolCallId: this.toolCall.id,
        messageId: this.messageId
      }
    }), {
      isValid: e.length === 0,
      errors: e,
      warnings: r
    }) : (e.push({
      code: "MESSAGE_NOT_FOUND",
      message: `Message ${this.messageId} not found`,
      severity: "error",
      context: {
        messageId: this.messageId
      }
    }), {
      isValid: !1,
      errors: e,
      warnings: r
    })
  }
  apply(t) {
    var r;
    if (((r = t.nextMessage) == null ? void 0 : r.id) === this.messageId) {
      const s = t.nextMessage.assistant.toolCalls || [],
        i = {
          ...t.nextMessage.assistant,
          toolCalls: [...s, this.toolCall]
        },
        a = new _.ConversationTurn(t.nextMessage.id, t.nextMessage.timestamp, t.nextMessage.user, i, t.nextMessage
          .toolResponse);
      return Promise.resolve(Z(t, a))
    }
    const e = t.history.map(s => {
      if (s.id === this.messageId) {
        const i = s.assistant.toolCalls || [],
          a = {
            ...s.assistant,
            toolCalls: [...i, this.toolCall]
          };
        return new _.ConversationTurn(s.id, s.timestamp, s.user, a, s.toolResponse)
      }
      return s
    });
    return Promise.resolve(B(t, {
      history: e
    }))
  }
}
class zr extends z {
  constructor(t, e) {
    super(), this.toolCallId = t, this.newStatus = e
  }
  validate(t) {
    var i;
    const e = [],
      r = [];
    let s;
    if ((i = t.nextMessage) != null && i.assistant.toolCalls && (s = t.nextMessage.assistant.toolCalls.find(a => a
        .id === this.toolCallId)), !s) {
      for (const a of t.history)
        if (a.assistant.toolCalls && (s = a.assistant.toolCalls.find(l => l.id === this.toolCallId), s)) break
    }
    return s ? (Lt(s.status, this.newStatus) || e.push({
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
      context: {
        toolCallId: this.toolCallId
      }
    }), {
      isValid: !1,
      errors: e,
      warnings: r
    })
  }
  apply(t) {
    var r, s;
    if ((s = (r = t.nextMessage) == null ? void 0 : r.assistant.toolCalls) != null && s.some(i => i.id === this
        .toolCallId)) {
      const i = _.updateConversationTurnToolCall(t.nextMessage, this.toolCallId, this.newStatus);
      return Promise.resolve(Z(t, i))
    }
    const e = t.history.map(i => {
      var a;
      return (a = i.assistant.toolCalls) != null && a.some(l => l.id === this.toolCallId) ? _
        .updateConversationTurnToolCall(i, this.toolCallId, this.newStatus) : i
    });
    return Promise.resolve(B(t, {
      history: e
    }))
  }
}
class Hr extends z {
  constructor(t, e) {
    super(), this.messageId = t, this.response = e
  }
  validate(t) {
    var a;
    const e = [],
      r = [],
      s = t.getMessageById(this.messageId);
    return s ? (((a = s.assistant.toolCalls) == null ? void 0 : a.find(l => l.id === this.response.callId)) || e
  .push({
      code: "TOOL_CALL_NOT_FOUND",
      message: `Tool call ${this.response.callId} not found in message ${this.messageId}`,
      severity: "error",
      context: {
        toolCallId: this.response.callId,
        messageId: this.messageId
      }
    }), this.response.content || r.push({
      code: "EMPTY_TOOL_RESPONSE",
      message: "Tool response has empty content",
      severity: "warning",
      context: {
        toolCallId: this.response.callId
      }
    }), {
      isValid: e.length === 0,
      errors: e,
      warnings: r
    }) : (e.push({
      code: "MESSAGE_NOT_FOUND",
      message: `Message ${this.messageId} not found`,
      severity: "error",
      context: {
        messageId: this.messageId
      }
    }), {
      isValid: !1,
      errors: e,
      warnings: r
    })
  }
  apply(t) {
    var r;
    if (((r = t.nextMessage) == null ? void 0 : r.id) === this.messageId) {
      const s = _.addToolResponseToMessageTuple(t.nextMessage, this.response);
      return Promise.resolve(Z(t, s))
    }
    const e = t.history.map(s => s.id === this.messageId ? _.addToolResponseToMessageTuple(s, this.response) : s);
    return Promise.resolve(B(t, {
      history: e
    }))
  }
}
class Jr extends z {
  constructor(t) {
    super(), this.messageId = t
  }
  validate(t) {
    const e = [],
      r = [],
      s = t.getMessageById(this.messageId);
    return s ? (s.assistant.isStreaming || r.push({
      code: "MESSAGE_ALREADY_COMPLETE",
      message: `Message ${this.messageId} is already complete`,
      severity: "warning",
      context: {
        messageId: this.messageId
      }
    }), s.pendingApprovals.length > 0 && e.push({
      code: "PENDING_APPROVALS_EXIST",
      message: `Cannot complete message ${this.messageId} with ${s.pendingApprovals.length} pending approvals`,
      severity: "error",
      context: {
        messageId: this.messageId,
        pendingApprovalIds: s.pendingApprovals.map(i => i.id)
      }
    }), {
      isValid: e.length === 0,
      errors: e,
      warnings: r
    }) : (e.push({
      code: "MESSAGE_NOT_FOUND",
      message: `Message ${this.messageId} not found`,
      severity: "error",
      context: {
        messageId: this.messageId
      }
    }), {
      isValid: !1,
      errors: e,
      warnings: r
    })
  }
  apply(t) {
    var r;
    if (((r = t.nextMessage) == null ? void 0 : r.id) === this.messageId) {
      const s = new _.ConversationTurn(t.nextMessage.id, t.nextMessage.timestamp, t.nextMessage.user, {
        ...t.nextMessage.assistant,
        isStreaming: !1
      }, t.nextMessage.toolResponse);
      return Promise.resolve(B(t, {
        history: [...t.history, s],
        nextMessage: void 0
      }))
    }
    const e = t.history.map(s => s.id === this.messageId ? new _.ConversationTurn(s.id, s.timestamp, s.user, {
      ...s.assistant,
      isStreaming: !1
    }, s.toolResponse) : s);
    return Promise.resolve(B(t, {
      history: e
    }))
  }
}
var de = {
    exports: {}
  },
  br;

function Tn() {
  if (br) return de.exports;
  br = 1;
  var n = typeof Reflect == "object" ? Reflect : null,
    t = n && typeof n.apply == "function" ? n.apply : function(d, v, w) {
      return Function.prototype.apply.call(d, v, w)
    },
    e;
  n && typeof n.ownKeys == "function" ? e = n.ownKeys : Object.getOwnPropertySymbols ? e = function(d) {
    return Object.getOwnPropertyNames(d).concat(Object.getOwnPropertySymbols(d))
  } : e = function(d) {
    return Object.getOwnPropertyNames(d)
  };

  function r(g) {
    console && console.warn && console.warn(g)
  }
  var s = Number.isNaN || function(d) {
    return d !== d
  };

  function i() {
    i.init.call(this)
  }
  de.exports = i, de.exports.once = R, i.EventEmitter = i, i.prototype._events = void 0, i.prototype._eventsCount = 0, i
    .prototype._maxListeners = void 0;
  var a = 10;

  function l(g) {
    if (typeof g != "function") throw new TypeError('The "listener" argument must be of type Function. Received type ' +
      typeof g)
  }
  Object.defineProperty(i, "defaultMaxListeners", {
    enumerable: !0,
    get: function() {
      return a
    },
    set: function(g) {
      if (typeof g != "number" || g < 0 || s(g)) throw new RangeError(
        'The value of "defaultMaxListeners" is out of range. It must be a non-negative number. Received ' +
        g + ".");
      a = g
    }
  }), i.init = function() {
    (this._events === void 0 || this._events === Object.getPrototypeOf(this)._events) && (this._events = Object
      .create(null), this._eventsCount = 0), this._maxListeners = this._maxListeners || void 0
  }, i.prototype.setMaxListeners = function(d) {
    if (typeof d != "number" || d < 0 || s(d)) throw new RangeError(
      'The value of "n" is out of range. It must be a non-negative number. Received ' + d + ".");
    return this._maxListeners = d, this
  };

  function c(g) {
    return g._maxListeners === void 0 ? i.defaultMaxListeners : g._maxListeners
  }
  i.prototype.getMaxListeners = function() {
    return c(this)
  }, i.prototype.emit = function(d) {
    for (var v = [], w = 1; w < arguments.length; w++) v.push(arguments[w]);
    var y = d === "error",
      q = this._events;
    if (q !== void 0) y = y && q.error === void 0;
    else if (!y) return !1;
    if (y) {
      var N;
      if (v.length > 0 && (N = v[0]), N instanceof Error) throw N;
      var G = new Error("Unhandled error." + (N ? " (" + N.message + ")" : ""));
      throw G.context = N, G
    }
    var W = q[d];
    if (W === void 0) return !1;
    if (typeof W == "function") t(W, this, v);
    else
      for (var K = W.length, C = S(W, K), w = 0; w < K; ++w) t(C[w], this, v);
    return !0
  };

  function u(g, d, v, w) {
    var y, q, N;
    if (l(v), q = g._events, q === void 0 ? (q = g._events = Object.create(null), g._eventsCount = 0) : (q
        .newListener !== void 0 && (g.emit("newListener", d, v.listener ? v.listener : v), q = g._events), N = q[d]),
      N === void 0) N = q[d] = v, ++g._eventsCount;
    else if (typeof N == "function" ? N = q[d] = w ? [v, N] : [N, v] : w ? N.unshift(v) : N.push(v), y = c(g), y > 0 &&
      N.length > y && !N.warned) {
      N.warned = !0;
      var G = new Error("Possible EventEmitter memory leak detected. " + N.length + " " + String(d) +
        " listeners added. Use emitter.setMaxListeners() to increase limit");
      G.name = "MaxListenersExceededWarning", G.emitter = g, G.type = d, G.count = N.length, r(G)
    }
    return g
  }
  i.prototype.addListener = function(d, v) {
    return u(this, d, v, !1)
  }, i.prototype.on = i.prototype.addListener, i.prototype.prependListener = function(d, v) {
    return u(this, d, v, !0)
  };

  function o() {
    if (!this.fired) return this.target.removeListener(this.type, this.wrapFn), this.fired = !0, arguments.length ===
      0 ? this.listener.call(this.target) : this.listener.apply(this.target, arguments)
  }

  function f(g, d, v) {
    var w = {
        fired: !1,
        wrapFn: void 0,
        target: g,
        type: d,
        listener: v
      },
      y = o.bind(w);
    return y.listener = v, w.wrapFn = y, y
  }
  i.prototype.once = function(d, v) {
    return l(v), this.on(d, f(this, d, v)), this
  }, i.prototype.prependOnceListener = function(d, v) {
    return l(v), this.prependListener(d, f(this, d, v)), this
  }, i.prototype.removeListener = function(d, v) {
    var w, y, q, N, G;
    if (l(v), y = this._events, y === void 0) return this;
    if (w = y[d], w === void 0) return this;
    if (w === v || w.listener === v) --this._eventsCount === 0 ? this._events = Object.create(null) : (delete y[d], y
      .removeListener && this.emit("removeListener", d, w.listener || v));
    else if (typeof w != "function") {
      for (q = -1, N = w.length - 1; N >= 0; N--)
        if (w[N] === v || w[N].listener === v) {
          G = w[N].listener, q = N;
          break
        } if (q < 0) return this;
      q === 0 ? w.shift() : m(w, q), w.length === 1 && (y[d] = w[0]), y.removeListener !== void 0 && this.emit(
        "removeListener", d, G || v)
    }
    return this
  }, i.prototype.off = i.prototype.removeListener, i.prototype.removeAllListeners = function(d) {
    var v, w, y;
    if (w = this._events, w === void 0) return this;
    if (w.removeListener === void 0) return arguments.length === 0 ? (this._events = Object.create(null), this
      ._eventsCount = 0) : w[d] !== void 0 && (--this._eventsCount === 0 ? this._events = Object.create(null) :
      delete w[d]), this;
    if (arguments.length === 0) {
      var q = Object.keys(w),
        N;
      for (y = 0; y < q.length; ++y) N = q[y], N !== "removeListener" && this.removeAllListeners(N);
      return this.removeAllListeners("removeListener"), this._events = Object.create(null), this._eventsCount = 0,
        this
    }
    if (v = w[d], typeof v == "function") this.removeListener(d, v);
    else if (v !== void 0)
      for (y = v.length - 1; y >= 0; y--) this.removeListener(d, v[y]);
    return this
  };

  function h(g, d, v) {
    var w = g._events;
    if (w === void 0) return [];
    var y = w[d];
    return y === void 0 ? [] : typeof y == "function" ? v ? [y.listener || y] : [y] : v ? E(y) : S(y, y.length)
  }
  i.prototype.listeners = function(d) {
    return h(this, d, !0)
  }, i.prototype.rawListeners = function(d) {
    return h(this, d, !1)
  }, i.listenerCount = function(g, d) {
    return typeof g.listenerCount == "function" ? g.listenerCount(d) : p.call(g, d)
  }, i.prototype.listenerCount = p;

  function p(g) {
    var d = this._events;
    if (d !== void 0) {
      var v = d[g];
      if (typeof v == "function") return 1;
      if (v !== void 0) return v.length
    }
    return 0
  }
  i.prototype.eventNames = function() {
    return this._eventsCount > 0 ? e(this._events) : []
  };

  function S(g, d) {
    for (var v = new Array(d), w = 0; w < d; ++w) v[w] = g[w];
    return v
  }

  function m(g, d) {
    for (; d + 1 < g.length; d++) g[d] = g[d + 1];
    g.pop()
  }

  function E(g) {
    for (var d = new Array(g.length), v = 0; v < d.length; ++v) d[v] = g[v].listener || g[v];
    return d
  }

  function R(g, d) {
    return new Promise(function(v, w) {
      function y(N) {
        g.removeListener(d, q), w(N)
      }

      function q() {
        typeof g.removeListener == "function" && g.removeListener("error", y), v([].slice.call(arguments))
      }
      I(g, d, q, {
        once: !0
      }), d !== "error" && b(g, y, {
        once: !0
      })
    })
  }

  function b(g, d, v) {
    typeof g.on == "function" && I(g, "error", d, v)
  }

  function I(g, d, v, w) {
    if (typeof g.on == "function") w.once ? g.once(d, v) : g.on(d, v);
    else if (typeof g.addEventListener == "function") g.addEventListener(d, function y(q) {
      w.once && g.removeEventListener(d, y), v(q)
    });
    else throw new TypeError('The "emitter" argument must be of type EventEmitter. Received type ' + typeof g)
  }
  return de.exports
}
var Sn = Tn();
class Yr extends Error {
  constructor(t) {
    super(t), this.name = "ConcurrentModificationError"
  }
}
class wn {
  constructor(t) {
    H(this, "sessionsDir");
    this.sessionsDir = Te.join(t, "sessions")
  }
  async ensureSessionsDir() {
    try {
      await J.promises.mkdir(this.sessionsDir, {
        recursive: !0
      })
    } catch (t) {
      if (t.code !== "EEXIST") throw t
    }
  }
  getSessionPath(t) {
    return Te.join(this.sessionsDir, `${t}.json`)
  }
  async saveSession(t) {
    await this.ensureSessionsDir();
    const e = this.getSessionPath(t.id),
      r = JSON.stringify(t, null, 2);
    await J.promises.writeFile(e, r, "utf8")
  }
  async loadSession(t) {
    try {
      const e = this.getSessionPath(t),
        r = await J.promises.readFile(e, "utf8");
      return JSON.parse(r)
    } catch (e) {
      if (e.code === "ENOENT") return null;
      throw e
    }
  }
  async deleteSession(t) {
    try {
      const e = this.getSessionPath(t);
      await J.promises.unlink(e)
    } catch (e) {
      if (e.code !== "ENOENT") throw e
    }
  }
  async listSessionIds() {
    try {
      return await this.ensureSessionsDir(), (await J.promises.readdir(this.sessionsDir)).filter(e => e.endsWith(
        ".json")).map(e => Te.basename(e, ".json"))
    } catch (t) {
      if (t.code === "ENOENT") return [];
      throw t
    }
  }
  async getSessionInfo(t) {
    try {
      const e = this.getSessionPath(t),
        r = await J.promises.readFile(e, "utf8"),
        s = JSON.parse(r);
      let i = 0;
      return i += s.history.length, s.nextMessage && i++, {
        id: s.id,
        title: s.title,
        lastModified: s.lastModified,
        messageCount: i
      }
    } catch (e) {
      if (e.code === "ENOENT") return null;
      throw e
    }
  }
  async saveWithVersion(t, e) {
    await this.ensureSessionsDir();
    const r = this.getSessionPath(t.id);
    try {
      const a = await J.promises.readFile(r, "utf8"),
        l = JSON.parse(a);
      if (l.version !== e) throw new Yr(`Expected version ${e}, got ${l.version}`)
    } catch (a) {
      if (a.code !== "ENOENT") throw a
    }
    const s = {
        ...t,
        version: e + 1,
        lastModified: P.now()
      },
      i = JSON.stringify(s, null, 2);
    await J.promises.writeFile(r, i, "utf8")
  }
}
class Cn extends Sn.EventEmitter {
  constructor(e, r) {
    super();
    H(this, "storage");
    H(this, "sessionCache", new Map);
    H(this, "eventBus");
    H(this, "sessionLocks", new Map);
    this.storage = e, this.eventBus = r || new re.EventBus
  }
  cacheSession(e) {
    this.sessionCache.set(e.id, e), this.emit("sessionChanged", {
      sessionId: e.id,
      changeType: "updated"
    })
  }
  getCachedSession(e) {
    return this.sessionCache.get(e)
  }
  removeCachedSession(e) {
    this.sessionCache.delete(e), this.emit("sessionChanged", {
      sessionId: e,
      changeType: "deleted"
    })
  }
  listCachedSessions() {
    return Array.from(this.sessionCache.values()).map(e => ({
      id: e.id,
      title: e.title,
      lastModified: e.lastModified,
      messageCount: e.history.length + (e.nextMessage ? 1 : 0)
    }))
  }
  onSessionChanged(e) {
    return this.on("sessionChanged", e)
  }
  offSessionChanged(e) {
    return this.off("sessionChanged", e)
  }
  clearCache() {
    this.sessionCache.clear()
  }
  getCacheSize() {
    return this.sessionCache.size
  }
  async createSession(e) {
    const r = P.generateSessionId(),
      s = P.now(),
      i = e.initialContext || {
        systemMessage: "",
        tools: [],
        contextFiles: [],
        steeringFiles: []
      },
      a = new Y(r, e.title, _.SessionType.Chat, s, s, 0, i, [], void 0, void 0);
    return this.setupAutoSave(a), this.storage && await this.storage.saveSession(a.toJSON()), this.sessionCache.set(
      r, a), this.emit("sessionChanged", {
      sessionId: r,
      changeType: "created"
    }), a
  }
  async getSession(e) {
    const r = this.sessionCache.get(e);
    if (r) return r;
    if (this.storage) {
      const s = await this.storage.loadSession(e);
      if (!s) throw new Error(`Session not found: ${e}`);
      const i = Y.fromJSON(s);
      return this.setupAutoSave(i), this.sessionCache.set(e, i), i
    }
    throw new Error(`Session not found: ${e}`)
  }
  async deleteSession(e) {
    this.sessionCache.delete(e), this.storage && await this.storage.deleteSession(e), this.emit("sessionChanged", {
      sessionId: e,
      changeType: "deleted"
    })
  }
  async listSessions(e = {}) {
    const {
      offset: r = 0,
      limit: s = 50
    } = e;
    if (!this.storage) return this.listCachedSessions().slice(r, r + s);
    const a = (await this.storage.listSessionIds()).map(u => {
      var o;
      return ((o = this.storage) == null ? void 0 : o.getSessionInfo(u)) ?? Promise.resolve(null)
    });
    return (await Promise.all(a)).filter(u => u !== null).sort((u, o) => o.lastModified - u.lastModified).slice(r,
      r + s)
  }
  async sessionExists(e) {
    return this.sessionCache.has(e) ? !0 : this.storage ? await this.storage.loadSession(e) !== null : !1
  }
  async saveSessionAsync(e) {
    if (this.storage) try {
      await this.storage.saveSession(e.toJSON())
    } catch (r) {
      r instanceof Error && this.emit("error", new Error(`Failed to auto-save session ${e.id}: ${r.message}`))
    }
  }
  async saveSession(e) {
    this.storage && await this.storage.saveSession(e.toJSON())
  }
  setupAutoSave(e) {
    this.storage
  }
  async submitUserMessage(e, r, s = []) {
    await this.withSessionLock(e, async i => {
      var c;
      const a = [{
          type: "text",
          text: r
        }],
        l = z.startUserMessage(a, s);
      await this.applySessionEdit(i, l), await this.eventBus.emit({
        id: P.generateId(),
        sessionId: e,
        timestamp: P.now(),
        type: "message_added",
        source: re.EventSource.User,
        data: {
          messageId: ((c = i.nextMessage) == null ? void 0 : c.id) || P.generateId(),
          messageType: "user"
        }
      })
    })
  }
  async approveToolCall(e, r, s) {
    await this.withSessionLock(e, async i => {
      const a = s.approved ? _.ToolCallStatus.Approved : _.ToolCallStatus.Denied,
        l = z.updateToolCallStatus(r, a);
      await this.applySessionEdit(i, l), await this.eventBus.emit({
        id: P.generateId(),
        sessionId: e,
        timestamp: P.now(),
        type: "tool_call_approval_decided",
        source: re.EventSource.User,
        data: {
          toolCallId: r,
          approved: s.approved,
          userComment: s.userComment
        }
      })
    })
  }
  onEvent(e, r) {
    return this.eventBus.subscribe(e, r)
  }
  onSessionEvent(e, r) {
    return this.eventBus.subscribeToSession(e, r)
  }
  unsubscribe(e) {
    this.eventBus.unsubscribe(e)
  }
  dispatchToAgent(e) {
    const r = P.generateId();
    return Promise.resolve({
      executionId: r,
      sessionId: e.sessionId,
      status: "queued"
    })
  }
  async applySessionEdit(e, r) {
    const s = r.validate(e);
    if (!s.isValid) throw new Error(`Session edit validation failed: ${s.errors.map(a=>a.message).join(", ")}`);
    const i = await r.apply(e);
    return this.storage && await this.storage.saveWithVersion(i.toJSON(), e.version), this.sessionCache.set(e.id,
      i), await this.eventBus.emit({
        id: P.generateId(),
        sessionId: e.id,
        timestamp: P.now(),
        type: "session_updated",
        source: re.EventSource.System,
        data: {
          field: "session_edit_applied",
          oldValue: e.version,
          newValue: i.version
        }
      }), i
  }
  async applySessionEdits(e, r) {
    for (const i of r) {
      const a = i.validate(e);
      if (!a.isValid) throw new Error(`Session edit validation failed: ${a.errors.map(l=>l.message).join(", ")}`)
    }
    let s = e;
    for (const i of r) s = await i.apply(s);
    return this.storage && await this.storage.saveWithVersion(s.toJSON(), e.version), this.sessionCache.set(e.id,
      s), await this.eventBus.emit({
        id: P.generateId(),
        sessionId: e.id,
        timestamp: P.now(),
        type: "session_updated",
        source: re.EventSource.System,
        data: {
          field: "batch_edits_applied",
          oldValue: e.version,
          newValue: s.version
        }
      }), s
  }
  async withSessionLock(e, r) {
    const s = this.sessionLocks.get(e);
    s && await s;
    let i;
    const a = new Promise(l => {
      i = l
    });
    this.sessionLocks.set(e, a);
    try {
      const l = await this.getSession(e);
      return await r(l)
    } finally {
      this.sessionLocks.delete(e), i && i()
    }
  }
  async editSession(e, ...r) {
    await this.withSessionLock(e, async s => {
      await this.applySessionEdits(s, r)
    })
  }
  getEventBus() {
    return this.eventBus
  }
  async emitEvent(e) {
    await this.eventBus.emit(e)
  }
}
exports.AgentType = _.AgentType;
exports.ConversationTurn = _.ConversationTurn;
exports.ExecutionStatus = _.ExecutionStatus;
exports.SessionType = _.SessionType;
exports.ToolCallStatus = _.ToolCallStatus;
exports.addContextFiles = _.addContextFiles;
exports.addSteeringFiles = _.addSteeringFiles;
exports.addToolCallToAssistant = _.addToolCallToAssistant;
exports.addToolResponseToMessageTuple = _.addToolResponseToMessageTuple;
exports.addToolResponseToTuple = _.addToolResponseToTuple;
exports.completeAssistantMessage = _.completeAssistantMessage;
exports.createAssistantMessage = _.createAssistantMessage;
exports.createContextMessage = _.createContextMessage;
exports.createConversationTurn = _.createConversationTurn;
exports.createEmptyContext = _.createEmptyContext;
exports.createFileLocation = _.createFileLocation;
exports.createRangeLocation = _.createRangeLocation;
exports.createToolResponseMessage = _.createToolResponseMessage;
exports.createUserMessage = _.createUserMessage;
exports.updateAssistantContent = _.updateAssistantContent;
exports.updateContextSystemMessage = _.updateContextSystemMessage;
exports.updateContextTools = _.updateContextTools;
exports.updateConversationTurnAssistant = _.updateConversationTurnAssistant;
exports.updateConversationTurnAssistantContent = _.updateConversationTurnAssistantContent;
exports.updateConversationTurnToolCall = _.updateConversationTurnToolCall;
exports.updateToolCallStatusInAssistant = _.updateToolCallStatusInAssistant;
exports.updateWorkspaceInfo = _.updateWorkspaceInfo;
exports.generateId = P.generateId;
exports.generateMessageId = P.generateMessageId;
exports.generateSessionId = P.generateSessionId;
exports.generateToolCallId = P.generateToolCallId;
exports.now = P.now;
exports.timestamp = P.timestamp;
exports.AddToolCallEdit = Wr;
exports.AddToolResponseEdit = Hr;
exports.CompleteMessageEdit = Jr;
exports.ConcurrentModificationError = Yr;
exports.FileSystemSessionStorage = wn;
exports.LangchainMessageWriter = Ur;
exports.MessageWriter = At;
exports.Session = Y;
exports.SessionEdit = z;
exports.SessionManager = Cn;
exports.StartUserMessageEdit = Vr;
exports.TOOL_CALL_TRANSITIONS = _e;
exports.UIMessageWriter = kr;
exports.UpdateStreamingContentEdit = Xr;
exports.UpdateToolCallStatusEdit = zr;
exports.addMessageToHistory = Qs;
exports.approveToolCall = un;
exports.clearSessionExecutionMetadata = rn;
exports.commitNextMessage = Zs;
exports.completeToolCallExecution = fn;
exports.createFailedToolResponse = mn;
exports.createSession = Ks;
exports.createToolCall = Br;
exports.createToolCallAwaitingApproval = ln;
exports.createToolResponse = pn;
exports.denyToolCall = cn;
exports.failToolCallExecution = dn;
exports.getExecutionDuration = _n;
exports.getValidNextStates = an;
exports.isComplete = En;
exports.isInProgress = vn;
exports.isTerminalStatus = on;
exports.isValidTransition = Lt;
exports.requiresApproval = gn;
exports.setNextMessage = Z;
exports.startToolCallExecution = hn;
exports.updateSession = B;
exports.updateSessionExecutionMetadata = tn;
exports.updateSessionTitle = en;
exports.updateToolCallStatus = ee;
exports.wasSuccessful = yn;