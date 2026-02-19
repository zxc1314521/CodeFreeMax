"use strict";

function escapeJsonForHtml(s) {
  return String(s ?? "").replace(/</g, "\\u003c");
}

function renderSimpleConfigPanelHtml({ vscode, webview, ctx, init }) {
  const cacheBust = String(Date.now().toString(16));
  const mainUri = webview.asWebviewUri(vscode.Uri.joinPath(ctx.extensionUri, "out", "byok", "ui", "config-panel-simple.webview.js")) + `?v=${cacheBust}`;
  const styleUri = webview.asWebviewUri(vscode.Uri.joinPath(ctx.extensionUri, "out", "byok", "ui", "config-panel-simple.css")) + `?v=${cacheBust}`;

  const csp = [
    "default-src 'none'",
    `img-src ${webview.cspSource} https: data:`,
    `style-src ${webview.cspSource} 'unsafe-inline'`,
    `script-src ${webview.cspSource}`
  ].join("; ");

  const initJson = escapeJsonForHtml(JSON.stringify(init || {}, null, 2));

  return `<!doctype html>
<html>
<head>
  <meta charset="utf-8" />
  <meta name="viewport" content="width=device-width, initial-scale=1" />
  <meta http-equiv="Content-Security-Policy" content="${csp}">
  <title>BYOK 快速配置</title>
  <link rel="stylesheet" href="${styleUri}">
</head>
<body>
  <script id="byokInit" type="application/json">${initJson}</script>
  <div id="simple-app"></div>
  <script src="${mainUri}"></script>
</body>
</html>`;
}

module.exports = { renderSimpleConfigPanelHtml };

