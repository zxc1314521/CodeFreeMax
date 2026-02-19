var o = Object.defineProperty;
var l = (t, s, e) => s in t ? o(t, s, {
  enumerable: !0,
  configurable: !0,
  writable: !0,
  value: e
}) : t[s] = e;
var a = (t, s, e) => l(t, typeof s != "symbol" ? s + "" : s, e);
class n extends Error {
  /**
   * Creates a new StreamError instance.
   * @param message - The error message to be displayed
   */
  constructor(s) {
    super(s), this.name = "StreamError";
  }
}
class i extends n {
  /**
   * Creates a new StreamAlreadyClosedError instance.
   * Initializes with a predefined message indicating the stream is complete.
   * @param streamId - Optional identifier for the stream that caused the error
   */
  constructor(s) {
    const e = s ? `Stream '${s}' is complete, cannot listen for more messages` :
      "Stream is complete, cannot listen for more messages";
    super(e);
  }
}
class h extends n {
  /**
   * Creates a new StreamAlreadyHasListenerError instance.
   * Initializes with a predefined message indicating that multiple listeners are not allowed.
   * @param streamId - Optional identifier for the stream that caused the error
   */
  constructor(s) {
    const e = s ? `Stream '${s}' already has a listener, streams can only have one listener` :
      "Stream already has a listener, streams can only have one listener";
    super(e);
  }
}
class r {
  /**
   * Creates a new AsyncStream instance.
   * @param parameters - Configuration object for the stream
   * @param parameters.id - Optional identifier for the stream
   * @param parameters.messages - Optional array of initial messages to populate the stream
   */
  constructor(s = {}) {
    // Queue of messages waiting to be consumed
    a(this, "messages", []);
    // Promise that resolves when new messages become available
    a(this, "onMessagesAvailable");
    a(this, "onStreamEnd", []);
    // Callback function to resolve the onMessagesAvailable promise
    a(this, "notifyMessagesAvailable");
    // Flag indicating whether the stream has been closed
    a(this, "done", !1);
    // Optional identifier for the stream
    a(this, "id");
    this.id = s.id, this.messages = (s.messages || []).map((e) => ({
      type: "message",
      data: e
    }));
  }
  /**
   * Creates an AsyncStream from an array of values.
   * @param values Array of values to convert into a stream
   * @returns AsyncStream containing the array values
   */
  static fromArray(s) {
    const e = new r({
      messages: s
    });
    return e.close(), e;
  }
  /**
   * Creates an AsyncStream from a string, with each character as a message.
   * @param text String to convert into a stream
   * @returns AsyncStream containing the string characters
   */
  static fromString(s) {
    const e = new r({
      messages: [...s]
    });
    return e.close(), e;
  }
  /**
   * Sets up a listener for new messages in the stream.
   * @throws {StreamAlreadyClosedError} If the stream has been closed
   * @throws {StreamAlreadyHasListenerError} If another listener is already waiting
   * @returns Promise that resolves when new messages are available
   */
  async listenForAvailableMessages() {
    if (this.done)
      throw new i(this.id);
    if (this.onMessagesAvailable)
      throw new h(this.id);
    return this.onMessagesAvailable = new Promise((s) => {
      this.notifyMessagesAvailable = s;
    }), this.onMessagesAvailable;
  }
  /**
   * Implementation of the AsyncIterable interface. Allows the stream to be
   * consumed using for-await-of loops.
   * @yields Messages of type T from the stream
   * @throws Any error that was pushed to the stream
   */
  async * [Symbol.asyncIterator]() {
    for (this.messages.length === 0 && !this.done && await this.listenForAvailableMessages(); this.messages.length >
      0 || !this.done;) {
      const s = this.messages.shift();
      if (s === void 0) {
        await this.listenForAvailableMessages();
        continue;
      }
      if (s.type === "error")
        throw s.data;
      if (s.type === "close")
        break;
      yield s.data;
    }
  }
  /**
   * Retrieves the next message from the stream.
   * @throws {StreamAlreadyClosedError} If the stream has been closed
   * @throws Any error that was pushed to the stream
   * @returns Promise that resolves with the next message in the stream
   */
  async next() {
    const s = this.messages.shift();
    if (s) {
      if (s.type === "error")
        throw s.data;
      if (s.type === "close")
        throw new i(this.id);
      return s.data;
    }
    if (this.done)
      throw new i(this.id);
    return await this.listenForAvailableMessages(), this.next();
  }
  /**
   * Reads all messages from the stream and returns them as an array.
   * @returns Promise that resolves with array of all messages
   */
  async all() {
    const s = [];
    for await (const e of this)
    s.push(e);
    return s;
  }
  /**
   * Gets the last message from the stream and closes it.
   * @returns Promise that resolves with the final message
   */
  async last() {
    return (await this.all()).at(-1);
  }
  /**
   * Pushes a new message onto the stream.
   * @param value The message to add to the stream
   */
  send(s) {
    this.messages.push({
      type: "message",
      data: s
    }), this.onMessagesAvailable = void 0, this.notifyMessagesAvailable && this.notifyMessagesAvailable();
  }
  /**
   * Attempts to push a new message onto the stream if it's not closed.
   * @param value The message to add to the stream
   * @returns Boolean indicating whether the message was sent successfully
   */
  trySend(s) {
    return this.done ? !1 : (this.send(s), !0);
  }
  /**
   * Closes the stream, preventing any further messages from being sent.
   * Any pending listeners will be notified.
   */
  close() {
    this.done = !0, this.messages.push({
      type: "close"
    }), this.onMessagesAvailable = void 0, this.notifyMessagesAvailable && this.notifyMessagesAvailable();
    for (const s of this.onStreamEnd)
      s();
  }
  /**
   * Attempts to close the stream if it's not already closed.
   * @returns Boolean indicating whether the stream was closed successfully
   */
  tryClose() {
    return this.done ? !1 : (this.close(), !0);
  }
  /**
   * Pushes an error onto the stream and closes it.
   * The error will be thrown when consumed by listeners.
   * Errors are placed at the front of the queue to be thrown immediately.
   * @param error The error to propagate through the stream
   */
  error(s) {
    this.messages.unshift({
      type: "error",
      data: s
    }), this.notifyMessagesAvailable && this.notifyMessagesAvailable(), this.done = !0, this.messages.push({
      type: "close"
    });
    for (const e of this.onStreamEnd)
      e();
  }
  /**
   * Registers a callback function to be executed when the stream ends.
   * @param callback Function to execute when the stream closes
   */
  onEnd(s) {
    this.onStreamEnd.push(s);
  }
}
export {
  r as AsyncStream
};