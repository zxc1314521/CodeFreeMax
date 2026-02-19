"use strict";
var o = Object.defineProperty;
var l = (t, s, e) => s in t ? o(t, s, {
  enumerable: !0,
  configurable: !0,
  writable: !0,
  value: e
}) : t[s] = e;
var a = (t, s, e) => l(t, typeof s != "symbol" ? s + "" : s, e);
Object.defineProperty(exports, Symbol.toStringTag, {
  value: "Module"
});
class n extends Error {
  constructor(s) {
    super(s), this.name = "StreamError"
  }
}
class r extends n {
  constructor(s) {
    const e = s ? `Stream '${s}' is complete, cannot listen for more messages` :
      "Stream is complete, cannot listen for more messages";
    super(e)
  }
}
class h extends n {
  constructor(s) {
    const e = s ? `Stream '${s}' already has a listener, streams can only have one listener` :
      "Stream already has a listener, streams can only have one listener";
    super(e)
  }
}
class i {
  constructor(s = {}) {
    a(this, "messages", []);
    a(this, "onMessagesAvailable");
    a(this, "onStreamEnd", []);
    a(this, "notifyMessagesAvailable");
    a(this, "done", !1);
    a(this, "id");
    this.id = s.id, this.messages = (s.messages || []).map(e => ({
      type: "message",
      data: e
    }))
  }
  static fromArray(s) {
    const e = new i({
      messages: s
    });
    return e.close(), e
  }
  static fromString(s) {
    const e = new i({
      messages: [...s]
    });
    return e.close(), e
  }
  async listenForAvailableMessages() {
    if (this.done) throw new r(this.id);
    if (this.onMessagesAvailable) throw new h(this.id);
    return this.onMessagesAvailable = new Promise(s => {
      this.notifyMessagesAvailable = s
    }), this.onMessagesAvailable
  }
  async * [Symbol.asyncIterator]() {
    for (this.messages.length === 0 && !this.done && await this.listenForAvailableMessages(); this.messages.length >
      0 || !this.done;) {
      const s = this.messages.shift();
      if (s === void 0) {
        await this.listenForAvailableMessages();
        continue
      }
      if (s.type === "error") throw s.data;
      if (s.type === "close") break;
      yield s.data
    }
  }
  async next() {
    const s = this.messages.shift();
    if (s) {
      if (s.type === "error") throw s.data;
      if (s.type === "close") throw new r(this.id);
      return s.data
    }
    if (this.done) throw new r(this.id);
    return await this.listenForAvailableMessages(), this.next()
  }
  async all() {
    const s = [];
    for await (const e of this) s.push(e);
    return s
  }
  async last() {
    return (await this.all()).at(-1)
  }
  send(s) {
    this.messages.push({
      type: "message",
      data: s
    }), this.onMessagesAvailable = void 0, this.notifyMessagesAvailable && this.notifyMessagesAvailable()
  }
  trySend(s) {
    return this.done ? !1 : (this.send(s), !0)
  }
  close() {
    this.done = !0, this.messages.push({
      type: "close"
    }), this.onMessagesAvailable = void 0, this.notifyMessagesAvailable && this.notifyMessagesAvailable();
    for (const s of this.onStreamEnd) s()
  }
  tryClose() {
    return this.done ? !1 : (this.close(), !0)
  }
  error(s) {
    this.messages.unshift({
      type: "error",
      data: s
    }), this.notifyMessagesAvailable && this.notifyMessagesAvailable(), this.done = !0, this.messages.push({
      type: "close"
    });
    for (const e of this.onStreamEnd) e()
  }
  onEnd(s) {
    this.onStreamEnd.push(s)
  }
}
exports.AsyncStream = i;