var g = Object.defineProperty;
var m = (n, t, e) => t in n ? g(n, t, {
  enumerable: !0,
  configurable: !0,
  writable: !0,
  value: e
}) : n[t] = e;
var y = (n, t, e) => m(n, typeof t != "symbol" ? t + "" : t, e);
import {
  AsyncStream as A
} from "../async-stream/index.js";
import {
  K as O
} from "../powers-Cm4DUTtG.js";
class l extends O {
  /**
   * Creates a new StreamedDataObjectError instance.
   * @param message - The error message.
   */
  constructor(t) {
    super(t), this.name = "StreamedDataObjectError";
  }
}
class f extends l {
  /**
   * Creates a new InvalidObjectType instance.
   * @param expectedType - The type that was expected.
   * @param dataType - The actual type that was provided.
   */
  constructor(t, e) {
    super(`Invalid object type provided: expected ${t}, got ${e}`), this.name = "InvalidObjectType";
  }
  /**
   * Required for error translation of session errors.
   * This is the string that will be shown the user if this error fails an execution.
   */
  get userFacingSessionErrorMessage() {
    return "Invalid data type";
  }
  /**
   * Return optional toast for fixing the error and proceeding.
   */
  get userFacingFixCallback() {}
}
class u extends l {
  /**
   * Creates a new InvalidTypeAtKeypath instance.
   * @param keypath - The path where the type mismatch occurred.
   * @param expectedType - The type that was expected.
   * @param actualType - The type that was actually found.
   */
  constructor(t, e, s) {
    super(`Invalid type at keypath "${t}": expected ${e}, got ${s}`), this.name = "InvalidTypeAtKeypath";
  }
  /**
   * Required for error translation of session errors.
   * This is the string that will be shown the user if this error fails an execution.
   */
  get userFacingSessionErrorMessage() {
    return "Invalid data structure";
  }
  /**
   * Return optional toast for fixing the error and proceeding.
   */
  get userFacingFixCallback() {}
}
class _ extends l {
  /**
   * Creates a new InvalidRootObject instance.
   */
  constructor() {
    super("Invalid root object: must be an array or object"), this.name = "InvalidRootObject";
  }
  /**
   * Required for error translation of session errors.
   * This is the string that will be shown the user if this error fails an execution.
   */
  get userFacingSessionErrorMessage() {
    return "Invalid data format";
  }
  /**
   * Return optional toast for fixing the error and proceeding.
   */
  get userFacingFixCallback() {}
}
class b extends l {
  /**
   * Creates a new ExpectedDataAtKeypath instance.
   * @param keypath - The path where data was expected but not found.
   */
  constructor(t) {
    super(`Expected data at keypath "${t}" but none was found`), this.name = "ExpectedDataAtKeypath";
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
const o = class o {
  /**
   * Creates a new StreamedDataObject with initial data
   * @param initialData The initial data to populate the object with
   */
  constructor(t) {
    // We will populate this as we learn about the data
    y(this, "data");
    y(this, "closed", !1);
    y(this, "streamPosition", 0);
    // We maintain references into the data to lookup by keypath if we need to
    // Keypaths are indexes like 'my-key.values.3.name'
    y(this, "dataByKeypath", /* @__PURE__ */ new Map());
    // We maintain a list of completed data keypaths
    y(this, "incompleteDataByKeypath", /* @__PURE__ */ new Set());
    y(this, "completedDataByKeypath", /* @__PURE__ */ new Set());
    // We also allow subscribing to data in the tree by keypath in an async manner
    y(this, "subscribersByKeypath", /* @__PURE__ */ new Map());
    this.data = t, this.dataByKeypath.set(o.ROOT, this.data), this._refreshDataReferencesAtKeypath(o.ROOT, this
      .data), this._updateOpenKeys(o.ROOT, t);
  }
  /**
   * Creates a new StreamedDataObject initialized with an empty array
   * @returns A new StreamedDataObject instance
   */
  static ofArray() {
    return new o([]);
  }
  /**
   * Creates a new StreamedDataObject initialized with an empty object
   * @returns A new StreamedDataObject instance
   */
  static ofObject() {
    return new o({});
  }
  /**
   * Creates a new StreamedDataObject with the provided data
   * @param data The initial data to populate the object with
   * @returns A new StreamedDataObject instance
   */
  static ofData(t) {
    if (typeof t != "object" && !Array.isArray(t))
      throw new _();
    return new o(t);
  }
  /**
   * Gets the root value of the data object
   * @returns The root value or undefined if not set
   */
  getRootValue() {
    return this.getValueAtKeypath(o.ROOT);
  }
  /**
   * Gets the value at a specific keypath
   * @param keypath The keypath to get the value from
   * @returns The value at the keypath or undefined if not found
   */
  getValueAtKeypath(t) {
    return this.dataByKeypath.get(t);
  }
  /**
   * Extends the root array with new data
   * @param data Array of data to append
   */
  extendRootArray(t) {
    this.extendArrayAtKeypath(o.ROOT, t);
  }
  /**
   * Extends an array at the given keypath with new data
   * @param keypath The keypath to the array
   * @param newData Array of data to append
   */
  extendArrayAtKeypath(t, e) {
    const s = this.dataByKeypath.get(t);
    if (!s) {
      this._setDataAtKeypath(t, e), this._updateOpenKeys(t, e);
      return;
    }
    if (Array.isArray(s) && Array.isArray(e)) {
      for (const r of e)
        this._appendArrayAtKeypath(t, r);
      this._updateOpenKeys(t, e);
      return;
    }
    if (!Array.isArray(s))
      throw new u(t, "array-like", typeof s);
    if (!Array.isArray(e))
      throw new f("array-like", typeof e);
  }
  /**
   * Appends a single item to an array at the given keypath
   * @param keypath The keypath to the array
   * @param data Item to append
   */
  appendArrayAtKeypath(t, e) {
    this._appendArrayAtKeypath(t, e), this._updateOpenKeys(t, e);
  }
  _appendArrayAtKeypath(t, e) {
    const s = this.dataByKeypath.get(t);
    if (!s)
      throw new b(t);
    if (!Array.isArray(s))
      throw new u(t, "array-like", typeof s);
    const r = s.length,
      i = `${t}.${r}`;
    s.push(e), this.dataByKeypath.set(i, e), this._refreshDataReferencesAtKeypath(i, e), this._emitArrayExtended(t,
      r, e);
  }
  /**
   * Merges data into the root object
   * @param data Object to merge
   */
  mergeRootObject(t) {
    this.mergeObjectAtKeypath(o.ROOT, t);
  }
  /**
   * Merges data into an object at the given keypath
   * @param keypath The keypath to the object
   * @param newData Object to merge
   */
  mergeObjectAtKeypath(t, e) {
    this._mergeObjectAtKeypath(t, e), this._updateOpenKeys(t, e);
  }
  _mergeObjectAtKeypath(t, e) {
    const s = this.dataByKeypath.get(t),
      r = typeof s,
      i = typeof e;
    if (!s) {
      this._setDataAtKeypath(t, e);
      return;
    }
    if (r === "object" && i === "object") {
      for (const [a, h] of Object.entries(e)) {
        const c = `${t}.${a}`;
        s[a] ? this._mergeObjectAtKeypath(c, h) : this._setDataAtKeypath(c, h);
      }
      this._emitValueWritten(t, this.dataByKeypath.get(t));
      return;
    }
    if (r !== "object")
      throw new u(t, "object", r);
    if (i !== "object")
      throw new f("object", i);
  }
  _setDataAtKeypath(t, e, s) {
    const r = t.lastIndexOf("."),
      i = t.slice(0, Math.max(0, r)),
      a = t.slice(Math.max(0, r + 1)),
      h = this.dataByKeypath.get(i);
    if (!h)
      throw new b(i);
    if (Array.isArray(e)) {
      const c = [];
      this.dataByKeypath.set(t, c), Object.assign(h, {
        [a]: c
      }), this._refreshDataReferencesAtKeypath(t, c);
      for (const [p, d] of e.entries())
        this._setDataAtKeypath(`${t}.${p}`, d);
      this._emitValueWritten(t, this.dataByKeypath.get(t));
      return;
    }
    if (typeof e == "object" && e !== null) {
      const c = {};
      this.dataByKeypath.set(t, c), Object.assign(h, {
        [a]: c
      }), this._refreshDataReferencesAtKeypath(t, c);
      for (const [p, d] of Object.entries(e))
        this._setDataAtKeypath(`${t}.${p}`, d);
      this._emitValueWritten(t, this.dataByKeypath.get(t)), this._emitValueWritten(i, this.dataByKeypath.get(i));
      return;
    }
    h[a] && h[a] === e || (this.dataByKeypath.set(t, e), Object.assign(h, {
      [a]: e
    }), this._refreshDataReferencesAtKeypath(t, e), typeof e == "string" ? this._emitStringExtended(t, e, s ||
      e) : this._emitValueWritten(t, e));
  }
  /**
   * Extends a string at the given keypath
   * @param keypath The keypath to the string
   * @param newData String to append
   */
  extendStringAtKeypath(t, e) {
    const s = this.dataByKeypath.get(t),
      r = typeof s;
    if (!s) {
      this._setDataAtKeypath(t, e), this._updateOpenKeys(t, e);
      return;
    }
    if (r === "string" && typeof e == "string") {
      const i = s + e;
      this._setDataAtKeypath(t, i, e), this._updateOpenKeys(t, i);
      return;
    }
    if (r !== "string")
      throw new u(t, "string", r);
    if (typeof e != "string")
      throw new f("string", typeof e);
  }
  _refreshDataReferencesAtKeypath(t, e) {
    if (Array.isArray(e))
      for (const [s, r] of e.entries()) {
        const i = `${t}.${s}`;
        this.dataByKeypath.set(i, r), this._refreshDataReferencesAtKeypath(i, r);
      }
    if (typeof e == "object" && e !== null)
      for (const [s, r] of Object.entries(e)) {
        const i = `${t}.${s}`;
        this.dataByKeypath.set(i, r), this._refreshDataReferencesAtKeypath(i, r);
      }
  }
  _updateOpenKeys(t, e) {
    const s = /* @__PURE__ */ new Set([
        ...this._computeParentKeypaths(t),
        ...this._computeAllObjectKeypaths(t, e)
      ]),
      r = [];
    for (const i of this.incompleteDataByKeypath)
      s.has(i) || r.push(i);
    r.sort((i, a) => a.localeCompare(i));
    for (const i of r)
      this._emitObjectCompleted(i), this.completedDataByKeypath.add(i);
    this.incompleteDataByKeypath = s;
  }
  _computeParentKeypaths(t) {
    const e = [],
      s = t.split(".");
    for (let r = 0; r < s.length; r++)
      e.push(s.slice(0, r).join("."));
    return e;
  }
  _computeAllObjectKeypaths(t, e) {
    const s = [t];
    if (Array.isArray(e))
      for (const [r, i] of e.entries()) {
        const a = `${t}.${r}`;
        s.push(...this._computeAllObjectKeypaths(a, i));
      }
    if (typeof e == "object" && e !== null)
      for (const [r, i] of Object.entries(e)) {
        const a = `${t}.${r}`;
        s.push(...this._computeAllObjectKeypaths(a, i));
      }
    return s;
  }
  /**
   * Closes all subscriptions and marks the object as closed
   */
  close() {
    const t = /* @__PURE__ */ new Set();
    for (const s of this.subscribersByKeypath.keys())
      t.add(s);
    for (const s of this.incompleteDataByKeypath.keys())
      t.add(s);
    const e = [...t].sort((s, r) => r.length - s.length);
    for (const s of e)
      s !== "*" && this._emitObjectCompleted(s);
    for (const s of this.subscribersByKeypath.keys())
      for (const r of this._getSubscribers(s))
        r.close();
    this.subscribersByKeypath.clear(), this.closed = !0;
  }
  /**
   * Subscribes to changes at a specific keypath
   * @param keypath The keypath to subscribe to
   * @returns An AsyncStream of changes
   */
  subscribe(t) {
    const e = {
        ctx: this,
        type: "ObjectSubscribed",
        streamPosition: this.streamPosition,
        keyPath: t,
        value: this._copy(this.getValueAtKeypath(t))
      },
      s = new A({
        messages: [e]
      });
    if (this.completedDataByKeypath.has(t) || this.closed) {
      const i = this.getValueAtKeypath(t) ? {
        ctx: this,
        type: "ObjectCompleted",
        streamPosition: this.streamPosition,
        keyPath: t,
        value: this._copy(this.getValueAtKeypath(t))
      } : {
        ctx: this,
        type: "ObjectCompletedWithoutData",
        streamPosition: this.streamPosition,
        keyPath: t
      };
      return s.send(i), s.close(), s;
    }
    const r = this.subscribersByKeypath.get(t) || [];
    return r.push(s), this.subscribersByKeypath.set(t, r), s;
  }
  /**
   * Checks if a specific keypath has been completed
   * @param keypath The keypath to check
   * @returns True if the keypath is completed, false otherwise
   */
  isKeypathCompleted(t) {
    return this.completedDataByKeypath.has(t);
  }
  /**
   * Subscribes to all updates from this object
   */
  subscribeAll() {
    return this.subscribe("*");
  }
  _getSubscribers(t) {
    const e = [...this.subscribersByKeypath.keys()],
      s = ["*"];
    for (const i of e)
      (t === i || t.startsWith(`${i}.`)) && s.push(i);
    return s.map((i) => this.subscribersByKeypath.get(i) || []).flatMap((i) => i);
  }
  _emitArrayExtended(t, e, s) {
    const r = this._getSubscribers(t);
    if (r.length === 0)
      return;
    const i = {
      ctx: this,
      type: "ArrayExtended",
      streamPosition: this.streamPosition,
      keyPath: t,
      index: e,
      value: this._copy(s)
    };
    for (const a of r)
      a.send(i);
  }
  _emitObjectCompleted(t) {
    const e = this._getSubscribers(t);
    if (e.length === 0)
      return;
    const s = this.getValueAtKeypath(t) ? {
      ctx: this,
      type: "ObjectCompleted",
      streamPosition: this.streamPosition,
      keyPath: t,
      value: this._copy(this.getValueAtKeypath(t))
    } : {
      ctx: this,
      type: "ObjectCompletedWithoutData",
      streamPosition: this.streamPosition,
      keyPath: t
    };
    for (const r of e)
      r.send(s);
    for (const r of this.subscribersByKeypath.get(t) || [])
      r.close();
  }
  _emitValueWritten(t, e) {
    const s = this._getSubscribers(t);
    if (s.length === 0)
      return;
    const r = {
      ctx: this,
      type: "ObjectUpdated",
      streamPosition: this.streamPosition,
      keyPath: t,
      value: this._copy(e)
    };
    for (const i of s)
      i.send(r);
  }
  _emitStringExtended(t, e, s) {
    const r = this._getSubscribers(t);
    if (r.length === 0 || !s)
      return;
    const i = {
      ctx: this,
      type: "StringExtended",
      streamPosition: this.streamPosition,
      keyPath: t,
      value: e,
      extension: s
    };
    for (const a of r)
      a.send(i);
  }
  _copy(t) {
    if (Array.isArray(t))
      return t.map((e) => this._copy(e));
    if (typeof t == "object" && t !== null) {
      const e = {};
      for (const [s, r] of Object.entries(t))
        e[s] = this._copy(r);
      return e;
    }
    return t;
  }
};
// Root data key for the tree
y(o, "ROOT", "root");
let K = o;
export {
  K as StreamedDataObject
};