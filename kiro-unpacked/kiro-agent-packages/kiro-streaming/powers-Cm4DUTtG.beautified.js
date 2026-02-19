var e;
(function(r) {
  r.RequirementsFirst = "requirements-first", r.DesignFirst = "design-first";
})(e || (e = {}));
var n;
(function(r) {
  r.FileEdited = "fileEdited", r.FileCreated = "fileCreated", r.FileDeleted = "fileDeleted", r.UserTriggered =
    "userTriggered", r.UserPrompt = "promptSubmit", r.AgentStop = "agentStop";
})(n || (n = {}));
var d;
(function(r) {
  r.AskAgent = "askAgent", r.RunCommand = "runCommand";
})(d || (d = {}));
var o;
(function(r) {
  r.DevMode = "enableDevMode", r.TrustedCommands = "trustedCommands", r.CommandDenylist = "commandDenylist", r
    .AutoApproveAgentCommands = "autoApproveAgentCommands", r.ConfigureMCP = "configureMCP", r.ExecuteBashTimeoutMs =
    "executeBashTimeoutMs", r.EnableCodebaseIndex = "enableCodebaseIndex", r.EnableRepositoryMapIndex =
    "enableRepositoryMapIndex", r.TrustedTools = "trustedTools";
})(o || (o = {}));
o.DevMode + "", o.TrustedCommands + "", o.CommandDenylist + "", o.AutoApproveAgentCommands + "", o.ConfigureMCP + "", o
  .ExecuteBashTimeoutMs + "", o.EnableCodebaseIndex + "", o.EnableRepositoryMapIndex + "", o.TrustedTools + "";
var i;
(function(r) {
  r.Extension = "kiroAgent", r.Test = "kiroAgent.test";
})(i || (i = {}));
var t;
(function(r) {
  r.Queued = "Queued", r.InProgress = "InProgress", r.Paused = "Paused", r.NeedAction = "NeedAction", r.Success =
    "Success", r.Failed = "Failed", r.Canceled = "Canceled", r.Yielded = "Yielded";
})(t || (t = {}));
var s;
(function(r) {
  r.Queued = "Queued", r.Active = "Active", r.History = "History";
})(s || (s = {}));
var u;
(function(r) {
  r.Code = "Code";
})(u || (u = {}));
var a;
(function(r) {
  r.PendingAction = "PendingAction", r.Running = "Running", r.Success = "Success", r.Error = "Error", r.Accepted =
    "Accepted", r.Rejected = "Rejected", r.Canceled = "Canceled", r.HandledError = "HandledError";
})(a || (a = {}));
var c;
(function(r) {
  r.Autopilot = "Autopilot", r.Supervised = "Supervised";
})(c || (c = {}));
var l;
(function(r) {
  r.NotStarted = "not_started", r.InProgress = "in_progress", r.Completed = "completed";
})(l || (l = {}));
class C extends Error {
  /**
   * Creates a new KiroError instance
   * @param message - The error message
   */
  constructor(f) {
    super(f), this.name = this.constructor.name, Error.captureStackTrace && Error.captureStackTrace(this, this
      .constructor);
  }
  /**
   * Prepares the error for JSON serialization
   * @returns the object
   */
  toJSON() {
    return {
      // eslint-disable-next-line @typescript-eslint/no-misused-spread
      ...this,
      userFacingSessionErrorMessage: this.userFacingSessionErrorMessage
    };
  }
}
var g;
(function(r) {
  r.Application = "kiro.application", r.Feature = "kiro.feature", r.Continue = "kiro.continue", r.Agent =
    "kiro.agent", r.Tool = "kiro.tool", r.Parser = "kiro.parser", r.Onboarding = "kiro.onboarding", r.Webview =
    "kiro.webview", r.Auth = "kiro.auth", r.Billing = "kiro.billing", r.Profiles = "kiro.profiles", r.RemoteTools =
    "kiro.remote-tools";
})(g || (g = {}));
var R;
(function(r) {
  r.Onboarding = "onboarding";
})(R || (R = {}));
var E;
(function(r) {
  r.RequestId = "requestId", r.ConversationId = "conversationId", r.ExecutionId = "executionId", r.ModelId =
    "ModelIdentifier", r.XRayTraceId = "AWS-XRAY-TRACE-ID";
})(E || (E = {}));
var v;
(function(r) {
  r.INVALID_TOKEN = "INVALID_TOKEN", r.NETWORK_ERROR = "NETWORK_ERROR", r.UNEXPECTED_ERROR = "UNEXPECTED_ERROR";
})(v || (v = {}));
var A;
(function(r) {
  r.InvalidPowerError = "InvalidPowerError", r.McpJsonNotFoundError = "McpJsonNotFoundError", r.McpJsonFetchError =
    "McpJsonFetchError", r.PowerAlreadyInstalledError = "PowerAlreadyInstalledError", r.PowerNotFoundError =
    "PowerNotFoundError", r.PowerNotInstalledError = "PowerNotInstalledError", r.PowerRegistryLoadError =
    "PowerRegistryLoadError", r.PowerRegistrySaveError = "PowerRegistrySaveError", r.PowerValidationError =
    "PowerValidationError", r.UnknownError = "UnknownError";
})(A || (A = {}));
export {
  C as K
};