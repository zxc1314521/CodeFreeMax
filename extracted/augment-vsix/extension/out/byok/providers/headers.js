"use strict";

const { normalizeRawToken, normalizeString } = require("../infra/util");

function withJsonContentType(headers) {
  return { "content-type": "application/json", ...(headers && typeof headers === "object" ? headers : {}) };
}

function openAiAuthHeaders(apiKey, extraHeaders) {
  const key = normalizeRawToken(apiKey);
  const headers = { ...(extraHeaders && typeof extraHeaders === "object" ? extraHeaders : {}) };
  const hasAuthHeader = Object.keys(headers).some((k) => String(k || "").trim().toLowerCase() === "authorization");
  if (!hasAuthHeader && key) headers.authorization = `Bearer ${key}`;
  return headers;
}

function anthropicAuthHeaders(apiKey, extraHeaders, opts) {
  const key = normalizeRawToken(apiKey);
  const forceBearer = opts && typeof opts === "object" ? Boolean(opts.forceBearer) : false;
  const headers = { ...(extraHeaders && typeof extraHeaders === "object" ? extraHeaders : {}) };
  const lowerKeys = new Set(Object.keys(headers).map((k) => String(k || "").trim().toLowerCase()));
  if (!lowerKeys.has("x-api-key") && key) headers["x-api-key"] = key;
  if (!lowerKeys.has("anthropic-version")) headers["anthropic-version"] = "2023-06-01";
  if (forceBearer && !lowerKeys.has("authorization") && key) headers.authorization = `Bearer ${key}`;
  return headers;
}

/**
 * 注入 x-session-id header
 * @param {Object} headers - 原始 headers
 * @param {string} sessionId - session ID
 * @returns {Object} 包含 x-session-id 的 headers
 */
function withSessionId(headers, sessionId) {
  const sid = normalizeString(sessionId);
  if (!sid) return headers;
  return { ...(headers && typeof headers === "object" ? headers : {}), "x-session-id": sid };
}

module.exports = { withJsonContentType, openAiAuthHeaders, anthropicAuthHeaders, withSessionId };
