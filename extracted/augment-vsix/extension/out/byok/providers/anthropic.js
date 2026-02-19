"use strict";

const { joinBaseUrl, safeFetch, readTextLimit } = require("./http");
const { parseSse } = require("./sse");
const { normalizeString, requireString, normalizeRawToken } = require("../infra/util");
const { withJsonContentType, anthropicAuthHeaders } = require("./headers");
const { normalizeUsageInt, makeToolMetaGetter, assertSseResponse } = require("./provider-util");
const { debug } = require("../infra/log");
const {
  STOP_REASON_END_TURN,
  STOP_REASON_TOOL_USE_REQUESTED,
  mapAnthropicStopReasonToAugment,
  rawResponseNode,
  toolUseStartNode,
  toolUseNode,
  thinkingNode,
  tokenUsageNode,
  mainTextFinishedNode,
  makeBackChatChunk
} = require("../core/augment-protocol");

// ===== Warp/Claude Code 工具适配层 =====
// /warp/v1/messages 已经把 Warp 工具映射为 Claude Code 工具:
//   run_shell_command -> Bash
//   read_files -> Read  
//   edit_files -> Edit
//   create_file -> Write
//   grep -> Grep
//   file_glob -> Glob
//   web_search -> WebSearch
//   codebase_semantic_search -> Grep
// 这里再把 Claude Code 工具转换为 Augment 认识的格式

function parseJsonSafe(jsonStr) {
  try {
    return JSON.parse(jsonStr || "{}");
  } catch {
    return {};
  }
}

// 从 shell 命令中提取操作类型和目标
function parseShellCommand(cmd) {
  const command = normalizeString(cmd).trim();
  if (!command) return null;
  
  // ls 命令 -> Read directory
  if (/^ls\b/.test(command)) {
    const match = command.match(/ls\s+(?:-[a-zA-Z]+\s+)*(.+)/);
    const path = match ? match[1].trim() : ".";
    return { type: "list_dir", path: path.replace(/["']/g, "") };
  }
  
  // cat 命令 -> Read file
  if (/^cat\b/.test(command)) {
    const match = command.match(/cat\s+(?:-[a-zA-Z]+\s+)*(.+)/);
    const path = match ? match[1].trim() : "";
    if (path) return { type: "read_file", path: path.replace(/["']/g, "") };
  }
  
  // head/tail 命令 -> Read file
  if (/^(head|tail)\b/.test(command)) {
    const match = command.match(/(head|tail)\s+(?:-[a-zA-Z0-9]+\s+)*(.+)/);
    const path = match ? match[2].trim() : "";
    if (path) return { type: "read_file", path: path.replace(/["']/g, "") };
  }
  
  // grep 命令 -> Search
  if (/^(grep|rg)\b/.test(command)) {
    return { type: "search", command };
  }
  
  // find 命令 -> Search files
  if (/^find\b/.test(command)) {
    return { type: "search_files", command };
  }
  
  // mkdir 命令 -> Create directory
  if (/^mkdir\b/.test(command)) {
    const match = command.match(/mkdir\s+(?:-[a-zA-Z]+\s+)*(.+)/);
    const path = match ? match[1].trim() : "";
    if (path) return { type: "create_dir", path: path.replace(/["']/g, "") };
  }
  
  // rm 命令 -> Delete
  if (/^rm\b/.test(command)) {
    return { type: "delete", command };
  }
  
  // mv/cp 命令 -> Move/Copy
  if (/^(mv|cp)\b/.test(command)) {
    return { type: command.startsWith("mv") ? "move" : "copy", command };
  }
  
  // 其他命令保持原样
  return { type: "shell", command };
}

// 主转换函数 - 转换 Claude Code 工具名为 Augment 工具名
function convertWarpToolToAugment(toolName, inputJsonStr) {
  const name = normalizeString(toolName);
  const nameLower = name.toLowerCase();
  
  // Claude Code 内置工具名 (由 /warp/v1/messages 映射后的)
  const claudeCodeTools = ["bash", "read", "edit", "write", "grep", "glob", "websearch"];
  
  // 也支持原始 Warp 工具名（兼容 /warp-aug/v1/messages）
  const warpTools = ["run_shell_command", "read_files", "edit_files", "apply_file_diffs", 
                     "create_file", "file_glob", "file_glob_v2", 
                     "search_codebase", "codebase_semantic_search", "web_search"];
  
  if (!claudeCodeTools.includes(nameLower) && !warpTools.includes(nameLower)) return null;
  
  const input = parseJsonSafe(inputJsonStr);
  
  // Claude Code 工具转换
  switch (nameLower) {
    case "bash":
    case "run_shell_command": {
      // Bash 工具 - 解析命令内容决定转换
      const cmd = normalizeString(input.command);
      const parsed = parseShellCommand(cmd);
      if (!parsed) return null;
      
      switch (parsed.type) {
        case "list_dir":
          return { name: "Read directory", inputJson: JSON.stringify({ path: parsed.path }) };
        case "read_file":
          return { name: "Read file", inputJson: JSON.stringify({ path: parsed.path }) };
        case "search":
        case "search_files":
          return { name: "Search", inputJson: JSON.stringify({ query: parsed.command }) };
        case "create_dir":
          return { name: "Create directory", inputJson: JSON.stringify({ path: parsed.path }) };
        default:
          return { name: "Execute command", inputJson: JSON.stringify({ command: cmd }) };
      }
    }
    
    case "read":
    case "read_files": {
      // Read 工具 -> Read file
      const files = Array.isArray(input.files) ? input.files : [];
      const path = normalizeString(input.path || input.file_path);
      
      if (path) {
        return { name: "Read file", inputJson: JSON.stringify({ path }) };
      }
      if (files.length === 1) {
        const f = files[0];
        return { name: "Read file", inputJson: JSON.stringify({ path: normalizeString(f.path || f.name || f) }) };
      }
      if (files.length > 1) {
        return { name: "Read files", inputJson: JSON.stringify({ files: files.map(f => normalizeString(f.path || f.name || f)) }) };
      }
      return null;
    }
    
    case "edit":
    case "edit_files":
    case "apply_file_diffs": {
      // Edit 工具 -> Edit file
      return { name: "Edit file", inputJson: inputJsonStr };
    }
    
    case "write":
    case "create_file": {
      // Write 工具 -> Create file
      return { name: "Create file", inputJson: inputJsonStr };
    }
    
    case "grep": {
      // Grep 工具 -> Search
      return {
        name: "Search",
        inputJson: JSON.stringify({
          query: Array.isArray(input.queries) ? input.queries.join(" ") : normalizeString(input.query || input.pattern),
          path: normalizeString(input.path)
        })
      };
    }
    
    case "glob":
    case "file_glob":
    case "file_glob_v2": {
      // Glob 工具 -> Find files
      return {
        name: "Find files",
        inputJson: JSON.stringify({
          patterns: input.patterns || input.pattern,
          path: normalizeString(input.search_dir || input.path)
        })
      };
    }
    
    case "websearch":
    case "web_search": {
      // WebSearch 工具 -> Web search
      return { name: "Web search", inputJson: inputJsonStr };
    }
    
    case "search_codebase":
    case "codebase_semantic_search": {
      // 语义搜索 -> Semantic search
      return {
        name: "Semantic search",
        inputJson: JSON.stringify({
          query: normalizeString(input.query),
          path: normalizeString(input.codebase_path)
        })
      };
    }
    
    default:
      return null;
  }
}
// ===== Warp/Claude Code 工具适配层结束 =====

function pickMaxTokens(requestDefaults) {
  const v = requestDefaults && typeof requestDefaults === "object" ? requestDefaults.max_tokens ?? requestDefaults.maxTokens : undefined;
  const n = Number(v);
  return Number.isFinite(n) && n > 0 ? n : 1024;
}

function buildAnthropicRequest({ baseUrl, apiKey, model, system, messages, tools, extraHeaders, requestDefaults, stream }) {
  const url = joinBaseUrl(requireString(baseUrl, "Anthropic baseUrl"), "messages");
  const key = normalizeRawToken(apiKey);
  const extra = extraHeaders && typeof extraHeaders === "object" ? extraHeaders : {};
  if (!key && Object.keys(extra).length === 0) throw new Error("Anthropic apiKey 未配置（且 headers 为空）");
  const m = requireString(model, "Anthropic model");
  if (!Array.isArray(messages) || !messages.length) throw new Error("Anthropic messages 为空");

  const body = {
    ...(requestDefaults && typeof requestDefaults === "object" ? requestDefaults : null),
    model: m,
    max_tokens: pickMaxTokens(requestDefaults),
    messages,
    stream: Boolean(stream)
  };
  if (typeof system === "string" && system.trim()) body.system = system.trim();
  if (Array.isArray(tools) && tools.length) {
    body.tools = tools;
    body.tool_choice = { type: "auto" };
  }
  const headers = withJsonContentType(anthropicAuthHeaders(key, extraHeaders));
  if (stream) headers.accept = "text/event-stream";
  return { url, headers, body };
}

async function anthropicCompleteText({ baseUrl, apiKey, model, system, messages, timeoutMs, abortSignal, extraHeaders, requestDefaults }) {
  const { url, headers, body } = buildAnthropicRequest({ baseUrl, apiKey, model, system, messages, tools: [], extraHeaders, requestDefaults, stream: false });

  const resp = await safeFetch(
    url,
    {
      method: "POST",
      headers,
      body: JSON.stringify(body)
    },
    { timeoutMs, abortSignal, label: "Anthropic" }
  );

  if (!resp.ok) throw new Error(`Anthropic ${resp.status}: ${await readTextLimit(resp, 500)}`.trim());
  const json = await resp.json().catch(() => null);
  const extractText = (obj) => {
    const rec = obj && typeof obj === "object" ? obj : null;
    if (!rec) return "";
    if (typeof rec.content === "string" && rec.content.trim()) return rec.content;
    const blocks = Array.isArray(rec.content) ? rec.content : [];
    const text = blocks.map((b) => (b && b.type === "text" && typeof b.text === "string" ? b.text : "")).join("");
    if (text.trim()) return text;
    return "";
  };

  const out = extractText(json) || extractText(json?.message) || normalizeString(json?.completion ?? json?.output_text ?? json?.outputText ?? json?.text);
  if (out) return out;

  // 兼容部分网关：OpenAI 形状（choices[0].message.content 或 choices[0].text）
  const oai = json && typeof json === "object" ? json : {};
  const choice0 = Array.isArray(oai.choices) ? oai.choices[0] : null;
  const m = choice0 && typeof choice0 === "object" ? choice0.message : null;
  const oaiText = normalizeString(m?.content) || normalizeString(choice0?.text);
  if (oaiText) return oaiText;

  const types = Array.isArray(json?.content)
    ? json.content
        .map((b) => normalizeString(b?.type) || "unknown")
        .filter(Boolean)
        .slice(0, 10)
        .join(",")
    : "";
  throw new Error(`Anthropic 响应缺少可解析文本（content_types=${types || "n/a"}）`.trim());
}

async function* anthropicStreamTextDeltas({ baseUrl, apiKey, model, system, messages, timeoutMs, abortSignal, extraHeaders, requestDefaults }) {
  const { url, headers, body } = buildAnthropicRequest({ baseUrl, apiKey, model, system, messages, tools: [], extraHeaders, requestDefaults, stream: true });

  const resp = await safeFetch(
    url,
    {
      method: "POST",
      headers,
      body: JSON.stringify(body)
    },
    { timeoutMs, abortSignal, label: "Anthropic(stream)" }
  );

  if (!resp.ok) throw new Error(`Anthropic(stream) ${resp.status}: ${await readTextLimit(resp, 500)}`.trim());
  await assertSseResponse(resp, { label: "Anthropic(stream)", expectedHint: "请确认 baseUrl 指向 Anthropic /messages SSE" });
  let dataEvents = 0;
  let parsedChunks = 0;
  let emitted = 0;
  for await (const ev of parseSse(resp)) {
    const data = normalizeString(ev?.data);
    if (!data) continue;
    dataEvents += 1;
    let json;
    try { json = JSON.parse(data); } catch { continue; }
    parsedChunks += 1;
    if (json?.type === "message_stop") break;
    if (json?.type === "content_block_delta" && json.delta && json.delta.type === "text_delta" && typeof json.delta.text === "string") {
      const t = json.delta.text;
      if (t) { emitted += 1; yield t; }
    }
  }
  if (emitted === 0) throw new Error(`Anthropic(stream) 未解析到任何 SSE delta（data_events=${dataEvents}, parsed_chunks=${parsedChunks}）；请检查 baseUrl 是否为 Anthropic SSE`.trim());
}

async function* anthropicChatStreamChunks({ baseUrl, apiKey, model, system, messages, tools, timeoutMs, abortSignal, extraHeaders, requestDefaults, toolMetaByName, supportToolUseStart }) {
  const { url, headers, body } = buildAnthropicRequest({ baseUrl, apiKey, model, system, messages, tools, extraHeaders, requestDefaults, stream: true });
  const resp = await safeFetch(url, { method: "POST", headers, body: JSON.stringify(body) }, { timeoutMs, abortSignal, label: "Anthropic(chat-stream)" });
  if (!resp.ok) throw new Error(`Anthropic(chat-stream) ${resp.status}: ${await readTextLimit(resp, 500)}`.trim());
  await assertSseResponse(resp, { label: "Anthropic(chat-stream)", expectedHint: "请确认 baseUrl 指向 Anthropic /messages SSE" });

  const getToolMeta = makeToolMetaGetter(toolMetaByName);

  let nodeId = 0;
  let fullText = "";
  let stopReason = null;
  let stopReasonSeen = false;
  let sawToolUse = false;
  let usageInputTokens = null;
  let usageOutputTokens = null;
  let usageCacheReadInputTokens = null;
  let usageCacheCreationInputTokens = null;
  let currentBlockType = "";
  let toolUseId = "";
  let toolName = "";
  let toolInputJson = "";
  let thinkingBuf = "";
  let dataEvents = 0;
  let parsedChunks = 0;
  let emittedChunks = 0;

  for await (const ev of parseSse(resp)) {
    const data = normalizeString(ev?.data);
    if (!data) continue;
    dataEvents += 1;
    let json;
    try {
      json = JSON.parse(data);
    } catch {
      continue;
    }
    parsedChunks += 1;
    const eventType = normalizeString(json?.type) || normalizeString(ev?.event);

    const usage = (json?.message && typeof json.message === "object" ? json.message.usage : null) || json?.usage;
    if (usage && typeof usage === "object") {
      const it = normalizeUsageInt(usage.input_tokens);
      const ot = normalizeUsageInt(usage.output_tokens);
      const cr = normalizeUsageInt(usage.cache_read_input_tokens);
      const cc = normalizeUsageInt(usage.cache_creation_input_tokens);
      if (it != null) usageInputTokens = it;
      if (ot != null) usageOutputTokens = ot;
      if (cr != null) usageCacheReadInputTokens = cr;
      if (cc != null) usageCacheCreationInputTokens = cc;
    }

    if (eventType === "content_block_start") {
      const block = json?.content_block && typeof json.content_block === "object" ? json.content_block : null;
      currentBlockType = normalizeString(block?.type);
      if (currentBlockType === "tool_use") {
        toolUseId = normalizeString(block?.id);
        toolName = normalizeString(block?.name);
        toolInputJson = "";
      } else if (currentBlockType === "thinking") {
        thinkingBuf = "";
      }
      continue;
    }

    if (eventType === "content_block_delta") {
      const delta = json?.delta && typeof json.delta === "object" ? json.delta : null;
      const dt = normalizeString(delta?.type);
      if (dt === "text_delta" && typeof delta?.text === "string" && delta.text) {
        const t = delta.text;
        fullText += t;
        nodeId += 1;
        emittedChunks += 1;
        yield makeBackChatChunk({ text: t, nodes: [rawResponseNode({ id: nodeId, content: t })] });
      } else if (dt === "input_json_delta" && typeof delta?.partial_json === "string" && delta.partial_json) {
        toolInputJson += delta.partial_json;
      } else if (dt === "thinking_delta" && typeof delta?.thinking === "string" && delta.thinking) {
        thinkingBuf += delta.thinking;
      }
      continue;
    }

    if (eventType === "content_block_stop") {
      if (currentBlockType === "thinking") {
        const summary = normalizeString(thinkingBuf);
        if (summary) {
          nodeId += 1;
          emittedChunks += 1;
          yield makeBackChatChunk({ text: "", nodes: [thinkingNode({ id: nodeId, summary })] });
        }
        thinkingBuf = "";
      }
      if (currentBlockType === "tool_use") {
        let name = normalizeString(toolName);
        let id = normalizeString(toolUseId);
        // ===== Warp 工具适配 =====
        // 将 Warp 工具名转换为 Augment 认识的工具名
        const warpToolResult = convertWarpToolToAugment(name, toolInputJson);
        if (warpToolResult) {
          name = warpToolResult.name;
          toolInputJson = warpToolResult.inputJson;
          debug(`[Warp Adapter] 工具转换: ${toolName} -> ${name}`);
        }
        // ===== Warp 工具适配结束 =====
        if (name) {
          if (!id) id = `tool-${nodeId + 1}`;
          const inputJson = normalizeString(toolInputJson) || "{}";
          const meta = getToolMeta(name);
          sawToolUse = true;
          if (supportToolUseStart === true) {
            nodeId += 1;
            emittedChunks += 1;
            yield makeBackChatChunk({ text: "", nodes: [toolUseStartNode({ id: nodeId, toolUseId: id, toolName: name, inputJson, mcpServerName: meta.mcpServerName, mcpToolName: meta.mcpToolName })] });
          }
          nodeId += 1;
          emittedChunks += 1;
          yield makeBackChatChunk({ text: "", nodes: [toolUseNode({ id: nodeId, toolUseId: id, toolName: name, inputJson, mcpServerName: meta.mcpServerName, mcpToolName: meta.mcpToolName })] });
        }
        toolUseId = "";
        toolName = "";
        toolInputJson = "";
      }
      currentBlockType = "";
      continue;
    }

    if (eventType === "message_delta") {
      const delta = json?.delta && typeof json.delta === "object" ? json.delta : null;
      const sr = normalizeString(delta?.stop_reason);
      if (sr) {
        stopReasonSeen = true;
        stopReason = mapAnthropicStopReasonToAugment(sr);
      }
      continue;
    }

    if (eventType === "message_stop") break;
    if (eventType === "error") {
      const msg = normalizeString(json?.error?.message) || normalizeString(json?.message) || "upstream error event";
      yield makeBackChatChunk({ text: `❌ 上游返回 error event: ${msg}`.trim(), stop_reason: STOP_REASON_END_TURN });
      return;
    }
  }

  if (currentBlockType === "thinking") {
    const summary = normalizeString(thinkingBuf);
    if (summary) {
      nodeId += 1;
      emittedChunks += 1;
      yield makeBackChatChunk({ text: "", nodes: [thinkingNode({ id: nodeId, summary })] });
    }
  }

  const hasUsage = usageInputTokens != null || usageOutputTokens != null || usageCacheReadInputTokens != null || usageCacheCreationInputTokens != null;
  if (emittedChunks === 0 && !hasUsage && !sawToolUse) {
    throw new Error(`Anthropic(chat-stream) 未解析到任何上游 SSE 内容（data_events=${dataEvents}, parsed_chunks=${parsedChunks}）；请检查 baseUrl 是否为 Anthropic /messages SSE`);
  }

  if (hasUsage) {
    nodeId += 1;
    yield makeBackChatChunk({ text: "", nodes: [tokenUsageNode({ id: nodeId, inputTokens: usageInputTokens, outputTokens: usageOutputTokens, cacheReadInputTokens: usageCacheReadInputTokens, cacheCreationInputTokens: usageCacheCreationInputTokens })] });
  }

  const finalNodes = [];
  if (fullText) {
    nodeId += 1;
    finalNodes.push(mainTextFinishedNode({ id: nodeId, content: fullText }));
  }

  const stop_reason = stopReasonSeen && stopReason != null ? stopReason : sawToolUse ? STOP_REASON_TOOL_USE_REQUESTED : STOP_REASON_END_TURN;
  yield makeBackChatChunk({ text: "", nodes: finalNodes, stop_reason });
}

module.exports = { anthropicCompleteText, anthropicStreamTextDeltas, anthropicChatStreamChunks };
