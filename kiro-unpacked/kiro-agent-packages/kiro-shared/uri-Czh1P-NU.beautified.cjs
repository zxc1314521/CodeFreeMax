"use strict";
var __defProp = Object.defineProperty;
var __defNormalProp = (obj, key, value) => key in obj ? __defProp(obj, key, {
  enumerable: true,
  configurable: true,
  writable: true,
  value
}) : obj[key] = value;
var __publicField = (obj, key, value) => __defNormalProp(obj, typeof key !== "symbol" ? key + "" : key, value);
const vscode = require("vscode");

function _interopNamespaceDefault(e) {
  const n = Object.create(null, {
    [Symbol.toStringTag]: {
      value: "Module"
    }
  });
  if (e) {
    for (const k in e) {
      if (k !== "default") {
        const d = Object.getOwnPropertyDescriptor(e, k);
        Object.defineProperty(n, k, d.get ? d : {
          enumerable: true,
          get: () => e[k]
        });
      }
    }
  }
  n.default = e;
  return Object.freeze(n);
}
const vscode__namespace = /* @__PURE__ */ _interopNamespaceDefault(vscode);
class UriEventHandler {
  constructor() {
    __publicField(this, "_onUri", new vscode__namespace.EventEmitter());
    __publicField(this, "onUri", this._onUri.event);
  }
  /**
   * Register uri handler
   * @param context
   */
  register(context) {
    const disposable = vscode__namespace.commands.registerCommand("kiro.uri", (uri) => {
      this._onUri.fire(uri);
    });
    context.subscriptions.push(disposable);
  }
  /**
   * Dispose this object and free resources.
   */
  dispose() {
    this._onUri.dispose();
  }
}
const uriEventHandler = new UriEventHandler();
exports.uriEventHandler = uriEventHandler;