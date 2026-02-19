var i = Object.defineProperty;
var o = (t, e, s) => e in t ? i(t, e, {
  enumerable: !0,
  configurable: !0,
  writable: !0,
  value: s
}) : t[e] = s;
var r = (t, e, s) => o(t, typeof e != "symbol" ? e + "" : e, s);
import {
  K as l
} from "../powers-Cm4DUTtG.js";
class m extends l {
  /**
   * Creates a new CompletedObjectUpdateError instance
   */
  constructor() {
    super("Cannot update a completed AsyncDeliveredObject");
  }
  /**
   * Required for error translation of session errors.
   * This is the string that will be shown the user if this error fails an execution.
   */
  get userFacingSessionErrorMessage() {
    return "Closed stream had unexpected results delivered";
  }
  /**
   * Return optional toast for fixing the error and proceeding.
   */
  get userFacingFixCallback() {}
}
class a {
  /**
   * Creates a new AsyncDeliveredObject instance
   * @param initialValue Optional initial value for the object
   */
  constructor(e) {
    r(this, "value");
    r(this, "isComplete", !1);
    r(this, "resolvePromise");
    r(this, "promise");
    this.value = e, this.promise = new Promise((s) => {
      this.resolvePromise = s;
    });
  }
  /**
   * Gets the current value, if one exists
   * @returns The current value or undefined if not set
   */
  getCurrentValue() {
    return this.value;
  }
  /**
   * Checks if this object has been marked as complete
   * @returns True if the object is complete
   */
  isCompleted() {
    return this.isComplete;
  }
  /**
   * Updates the current value
   * @param newValue The new value to set
   * @throws Error if the object is already completed
   */
  update(e) {
    if (this.isComplete)
      throw new m();
    this.value = e;
  }
  /**
   * Marks the object as complete, preventing further updates
   * @param finalValue Optional final value to set before completing
   */
  complete(e) {
    this.isComplete || (e !== void 0 && (this.value = e), this.isComplete = !0, this.resolvePromise && this
      .resolvePromise(this.value));
  }
  /**
   * Gets a promise that will resolve when the object is completed
   * @returns Promise that resolves with the final value
   */
  getCompletionPromise() {
    return this.isComplete ? Promise.resolve(this.value) : this.promise;
  }
  /**
   * Waits for this object to be completed
   * @returns Promise that resolves with the final value
   */
  async waitForCompletion() {
    return this.getCompletionPromise();
  }
}
export {
  a as AsyncDeliveredObject
};