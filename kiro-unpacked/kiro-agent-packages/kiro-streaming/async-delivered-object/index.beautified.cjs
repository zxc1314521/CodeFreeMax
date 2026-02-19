"use strict";
var i = Object.defineProperty;
var o = (t, e, r) => e in t ? i(t, e, {
  enumerable: !0,
  configurable: !0,
  writable: !0,
  value: r
}) : t[e] = r;
var s = (t, e, r) => o(t, typeof e != "symbol" ? e + "" : e, r);
Object.defineProperty(exports, Symbol.toStringTag, {
  value: "Module"
});
const l = require("../powers-Bsu2Ho0l.cjs");
class u extends l.KiroError {
  constructor() {
    super("Cannot update a completed AsyncDeliveredObject")
  }
  get userFacingSessionErrorMessage() {
    return "Closed stream had unexpected results delivered"
  }
  get userFacingFixCallback() {}
}
class n {
  constructor(e) {
    s(this, "value");
    s(this, "isComplete", !1);
    s(this, "resolvePromise");
    s(this, "promise");
    this.value = e, this.promise = new Promise(r => {
      this.resolvePromise = r
    })
  }
  getCurrentValue() {
    return this.value
  }
  isCompleted() {
    return this.isComplete
  }
  update(e) {
    if (this.isComplete) throw new u;
    this.value = e
  }
  complete(e) {
    this.isComplete || (e !== void 0 && (this.value = e), this.isComplete = !0, this.resolvePromise && this
      .resolvePromise(this.value))
  }
  getCompletionPromise() {
    return this.isComplete ? Promise.resolve(this.value) : this.promise
  }
  async waitForCompletion() {
    return this.getCompletionPromise()
  }
}
exports.AsyncDeliveredObject = n;