import {
  K as d,
  T as j
} from "./powers-D5ei-qtJ.js";
import {
  randomUUID as P
} from "crypto";
import {
  MetricReporter as S
} from "@kiro/shared";
import * as m from "zod";
import * as x from "os";
class U extends d {
  /**
   * Creates a new AbortedException instance
   * @param message - Custom error message describing why the operation was aborted
   */
  constructor(r = "Operation was aborted by user or system") {
    super(r);
  }
  /**
   * Required for error translation of session errors.
   * This is the string that will be shown the user if this error fails an execution.
   */
  get userFacingSessionErrorMessage() {
    return "Execution Aborted";
  }
  /**
   * Return optional toast for fixing the error and proceeding.
   */
  get userFacingFixCallback() {}
}
class I extends d {
  /**
   * Creates a new RunCommandNoWorkingDirectoryError instance
   */
  constructor() {
    super("No workspace directory available for command execution");
  }
  /**
   * Required for error translation of session errors.
   * This is the string that will be shown the user if this error fails an execution.
   */
  get userFacingSessionErrorMessage() {
    return "No workspace directory is available for command execution. Please open a workspace folder.";
  }
  /**
   * Return optional toast for fixing the error and proceeding.
   */
  get userFacingFixCallback() {}
}
class C extends d {
  /**
   * Creates a new PromptTemplateKeyError instance
   */
  constructor(r) {
    super(`Invalid values provided for the prompt template: ${r}`);
  }
  /**
   * Required for error translation of session errors.
   * This is the string that will be shown the user if this error fails an execution.
   */
  get userFacingSessionErrorMessage() {
    return "Invalid Prompt Submitted - Please report a bug";
  }
  /**
   * Return optional toast for fixing the error and proceeding.
   */
  get userFacingFixCallback() {}
}
class K extends d {
  /**
   * Creates a new MissingRequiredKeysError instance
   * @param expectedKeys - Array of key names that were expected but not found
   * @param receivedObject - The actual object that was received and is missing keys
   */
  constructor(r, n) {
    super(`Missing required keys: [${r.join(", ")}] in received object: ${JSON.stringify(n)}`);
  }
  /**
   * Required for error translation of session errors.
   * This is the string that will be shown the user if this error fails an execution.
   */
  get userFacingSessionErrorMessage() {
    return "Missing required data";
  }
  /**
   * Return optional toast for fixing the error and proceeding.
   */
  get userFacingFixCallback() {}
}
class T extends d {
  /**
   * Creates a new UnsupportedModelProvider instance
   * @param provider - The identifier of the unsupported model provider
   */
  constructor(r) {
    super(`Unsupported model provider: '${r}' when trying to load model`);
  }
  /**
   * Required for error translation of session errors.
   * This is the string that will be shown the user if this error fails an execution.
   */
  get userFacingSessionErrorMessage() {
    return "Unsupported model provider";
  }
  /**
   * Return optional toast for fixing the error and proceeding.
   */
  get userFacingFixCallback() {}
}

function y(e, r) {
  var n = Object.keys(e);
  if (Object.getOwnPropertySymbols) {
    var t = Object.getOwnPropertySymbols(e);
    r && (t = t.filter(function(o) {
      return Object.getOwnPropertyDescriptor(e, o).enumerable;
    })), n.push.apply(n, t);
  }
  return n;
}

function w(e) {
  for (var r = 1; r < arguments.length; r++) {
    var n = arguments[r] != null ? arguments[r] : {};
    r % 2 ? y(Object(n), !0).forEach(function(t) {
      N(e, t, n[t]);
    }) : Object.getOwnPropertyDescriptors ? Object.defineProperties(e, Object.getOwnPropertyDescriptors(n)) : y(
      Object(n)).forEach(function(t) {
      Object.defineProperty(e, t, Object.getOwnPropertyDescriptor(n, t));
    });
  }
  return e;
}

function N(e, r, n) {
  return r = M(r), r in e ? Object.defineProperty(e, r, {
    value: n,
    enumerable: !0,
    configurable: !0,
    writable: !0
  }) : e[r] = n, e;
}

function M(e) {
  var r = F(e, "string");
  return typeof r == "symbol" ? r : String(r);
}

function F(e, r) {
  if (typeof e != "object" || e === null) return e;
  var n = e[Symbol.toPrimitive];
  if (n !== void 0) {
    var t = n.call(e, r);
    if (typeof t != "object") return t;
    throw new TypeError("@@toPrimitive must return a primitive value.");
  }
  return (r === "string" ? String : Number)(e);
}
const h = O({});

function O(e) {
  return r.withOptions = (n) => O(w(w({}, e), n)), r;

  function r(n, ...t) {
    const o = typeof n == "string" ? [n] : n.raw,
      {
        alignValues: u = !1,
        escapeSpecialCharacters: c = Array.isArray(n),
        trimWhitespace: l = !0
      } = e;
    let i = "";
    for (let a = 0; a < o.length; a++) {
      let s = o[a];
      if (c && (s = s.replace(/\\\n[ \t]*/g, "").replace(/\\`/g, "`").replace(/\\\$/g, "$").replace(/\\\{/g, "{")), i +=
        s, a < t.length) {
        const g = u ? A(t[a], i) : t[a];
        i += g;
      }
    }
    const p = i.split(`
`);
    let f = null;
    for (const a of p) {
      const s = a.match(/^(\s+)\S+/);
      if (s) {
        const g = s[1].length;
        f ? f = Math.min(f, g) : f = g;
      }
    }
    if (f !== null) {
      const a = f;
      i = p.map((s) => s[0] === " " || s[0] === "	" ? s.slice(a) : s).join(`
`);
    }
    return l && (i = i.trim()), c && (i = i.replace(/\\n/g, `
`)), i;
  }
}

function A(e, r) {
  if (typeof e != "string" || !e.includes(`
`))
    return e;
  const t = r.slice(r.lastIndexOf(`
`) + 1).match(/^(\s+)/);
  if (t) {
    const o = t[1];
    return e.replace(/\n/g, `
${o}`);
  }
  return e;
}

function Z({
  prompt: e,
  keys: r
}) {
  const n = h(e).trim();
  return {
    format(t = {}) {
      if (Object.keys(t).length !== r.length || Object.keys(t).some((o) => !r.includes(o)))
        throw new C(`Saw ${Object.keys(t).join(", ")}, expected ${r.join(", ")}`);
      return E(n, t);
    }
  };
}

function _(e) {
  const r = h(e).trim();
  return {
    format() {
      return r;
    }
  };
}

function V(e) {
  return e.map((r) => r.trim()).join(`

`);
}

function E(e, r) {
  const n = {};
  for (const t of Object.keys(r)) {
    const o = P();
    n[t] = o, e = e.replaceAll(`{{${t}}}`, o);
  }
  for (const [t, o] of Object.entries(r))
    e = e.replaceAll(n[t], o.toString());
  return e;
}
const v = new S(j.Agent, "NumberCoercion");

function R(e, r, n) {
  if (!e || typeof e != "object")
    return e;
  const t = {
      ...e
    },
    o = r.shape;
  let u = 0;
  for (const [c, l] of Object.entries(o))
    if (c in t) {
      const i = t[c],
        p = b(i, l);
      p.wasCoerced && (t[c] = p.value, u++);
    }
  return u > 0 && v.reportCountMetrics({
    stringToNumberCoercions: u,
    schemasProcessed: 1
  }, {
    operation: "stringToNumberCoercion",
    toolId: n
  }), t;
}

function b(e, r) {
  let n = r;
  for (; n instanceof m.ZodOptional || n instanceof m.ZodNullable || n instanceof m.ZodDefault;)
    n = n._def.innerType;
  if (n instanceof m.ZodNumber && typeof e == "string" && !isNaN(Number(e)) && e.trim() !== "")
    return {
      value: Number(e),
      wasCoerced: !0
    };
  if (n instanceof m.ZodArray && Array.isArray(e)) {
    const t = n._def.type;
    let o = !1;
    return {
      value: e.map((c) => {
        const l = b(c, t);
        return l.wasCoerced && (o = !0), l.value;
      }),
      wasCoerced: o
    };
  }
  if (n instanceof m.ZodObject && e && typeof e == "object") {
    const t = {
      ...e
    };
    let o = !1;
    const u = n.shape;
    for (const [c, l] of Object.entries(u))
      if (c in t) {
        const i = b(t[c], l);
        i.wasCoerced && (t[c] = i.value, o = !0);
      }
    return {
      value: t,
      wasCoerced: o
    };
  }
  return {
    value: e,
    wasCoerced: !1
  };
}

function W(e) {
  let r = "";
  const n = [];
  for (const t of e)
    ["text", "mention"].includes(t.type) && t.text && (r += t.text), t.type === "imageUrl" && t.imageUrl && n.push(t
      .imageUrl.url);
  return {
    entireMessage: r,
    imageBase64Urls: n
  };
}

function q() {
  const e = x.platform();
  switch (e) {
    case "win32":
      return "Windows";
    case "darwin":
      return "macOS";
    case "linux":
      return "Linux";
    default:
      return e;
  }
}
export {
  U as AgentAbortedException,
  K as MissingRequiredKeysError,
  C as PromptTemplateKeyError,
  I as RunCommandNoWorkingDirectoryError,
  T as UnsupportedModelProvider,
  R as coerceNumbersInSchema,
  q as getOperatingSystem,
  V as joinPrompts,
  W as parseMessagePartArray,
  Z as promptTemplate,
  _ as rawPromptString
};