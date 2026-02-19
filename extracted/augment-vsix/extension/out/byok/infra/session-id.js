"use strict";

/**
 * Session ID 管理模块
 * 
 * 功能：为每个会话窗口（conversation）生成并缓存唯一的 session ID
 * - 同一个 conversation_id 始终返回相同的 session ID
 * - 新的 conversation_id 会生成新的 session ID
 * - session ID 格式为 UUID v4
 */

const { normalizeString } = require("./util");

// conversation_id -> session_id 的映射缓存
const sessionIdCache = new Map();

/**
 * 生成 UUID v4
 */
function generateUuid() {
  const hex = "0123456789abcdef";
  let uuid = "";
  for (let i = 0; i < 36; i++) {
    if (i === 8 || i === 13 || i === 18 || i === 23) {
      uuid += "-";
    } else if (i === 14) {
      uuid += "4";
    } else if (i === 19) {
      uuid += hex[8 + Math.floor(Math.random() * 4)];
    } else {
      uuid += hex[Math.floor(Math.random() * 16)];
    }
  }
  return uuid;
}

/**
 * 根据 conversation_id 获取或创建 session ID
 * 
 * @param {string} conversationId - 会话 ID
 * @returns {string} session ID (UUID 格式)
 */
function getOrCreateSessionId(conversationId) {
  const convId = normalizeString(conversationId);
  
  // 如果没有 conversation_id，每次都生成新的（兼容无会话场景）
  if (!convId) {
    return generateUuid();
  }
  
  // 检查缓存
  if (sessionIdCache.has(convId)) {
    return sessionIdCache.get(convId);
  }
  
  // 生成新的 session ID 并缓存
  const sessionId = generateUuid();
  sessionIdCache.set(convId, sessionId);
  
  return sessionId;
}

/**
 * 清除指定会话的 session ID 缓存
 * 
 * @param {string} conversationId - 会话 ID
 * @returns {boolean} 是否成功删除
 */
function clearSessionId(conversationId) {
  const convId = normalizeString(conversationId);
  if (!convId) return false;
  return sessionIdCache.delete(convId);
}

/**
 * 清除所有 session ID 缓存
 */
function clearAllSessionIds() {
  sessionIdCache.clear();
}

/**
 * 获取当前缓存的会话数量（用于调试）
 */
function getSessionCacheSize() {
  return sessionIdCache.size;
}

module.exports = {
  getOrCreateSessionId,
  clearSessionId,
  clearAllSessionIds,
  getSessionCacheSize,
  generateUuid
};
