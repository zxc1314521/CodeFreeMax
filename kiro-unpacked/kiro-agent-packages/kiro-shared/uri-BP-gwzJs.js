var __defProp = Object.defineProperty;
var __defNormalProp = (obj, key, value) => key in obj ? __defProp(obj, key, { enumerable: true, configurable: true, writable: true, value }) : obj[key] = value;
var __publicField = (obj, key, value) => __defNormalProp(obj, typeof key !== "symbol" ? key + "" : key, value);
import * as vscode from "vscode";
class UriEventHandler {
  constructor() {
    __publicField(this, "_onUri", new vscode.EventEmitter());
    __publicField(this, "onUri", this._onUri.event);
  }
  /**
   * Register uri handler
   * @param context
   */
  register(context) {
    const disposable = vscode.commands.registerCommand("kiro.uri", (uri) => {
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
export {
  uriEventHandler as u
};
