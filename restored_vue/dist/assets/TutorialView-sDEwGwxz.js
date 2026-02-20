import{d as R,e as V,c as n,a as o,b as r,t as s,F as P,f as A,R as m,M as d,bz as S,r as u,g as i,h as z,o as l,_ as $}from"./index-0b7F522w.js";const X={class:"tutorial-page"},G={class:"card"},N={class:"api-format"},F={class:"warning-box"},q={class:"code-inline"},D={class:"table-wrap"},W={class:"data-table"},Z={class:"badge badge-amber"},J={class:"code-primary"},Q={class:"code-green"},ee={key:0,class:"badge badge-green"},oe={key:1,class:"badge badge-amber"},te={class:"card"},ae={class:"tab-bar"},ne={key:0},le={class:"channel-tabs"},re=["onClick"],se={key:0,class:"code-block"},ie={key:1},de={class:"channel-tabs"},ce=["onClick"],ue={key:0},pe={class:"grok-tabs"},ke=["onClick"],_e={class:"code-block"},ve={key:1,class:"code-block"},ge=R({__name:"TutorialView",setup(be){const p=u("openai"),k=u(""),_=u("grok"),f=u("chat"),T=u(!1),h=u([]),c=u([]),C=i(()=>window.location.origin),w=[{id:1,key:"kiro",name:"Kiro",enabled:!0,default_model:"claude-sonnet-4-5",claude_protocol:!0,openai_protocol:!0,sort_order:1},{id:2,key:"orchids",name:"Orchids",enabled:!0,default_model:"claude-sonnet-4-5",claude_protocol:!0,openai_protocol:!0,sort_order:2},{id:3,key:"antigravity",name:"Antigravity",enabled:!0,default_model:"gemini-2.5-flash-preview",claude_protocol:!0,openai_protocol:!0,sort_order:3},{id:4,key:"cursor",name:"Cursor",enabled:!0,default_model:"claude-4.5-sonnet",claude_protocol:!1,openai_protocol:!0,sort_order:4},{id:5,key:"warp",name:"Warp",enabled:!0,default_model:"claude-4-5-sonnet",claude_protocol:!0,openai_protocol:!0,sort_order:5},{id:6,key:"claude_api",name:"Claude API",enabled:!0,default_model:"claude-sonnet-4-5",claude_protocol:!0,openai_protocol:!1,sort_order:6},{id:7,key:"grok",name:"Grok",enabled:!0,default_model:"grok-4.1-fast",claude_protocol:!1,openai_protocol:!0,sort_order:7}];function v(t,e){return`curl -X POST {baseUrl}/${t}/v1/messages \\
  -H "Content-Type: application/json" \\
  -H "x-api-key: YOUR_API_KEY" \\
  -d '{
    "model": "${e}",
    "max_tokens": 4096,
    "stream": true,
    "messages": [
      {"role": "user", "content": "Hello, who are you?"}
    ]
  }'`}function g(t,e){return`curl -X POST {baseUrl}/${t}/v1/chat/completions \\
  -H "Content-Type: application/json" \\
  -H "Authorization: Bearer YOUR_API_KEY" \\
  -d '{
    "model": "${e}",
    "stream": true,
    "messages": [
      {"role": "user", "content": "Hello, who are you?"}
    ]
  }'`}const x=[{id:1,channel_key:"kiro",protocol:"claude",tab_key:"",tab_label:"",content:v("kiro","claude-sonnet-4-5"),sort_order:1},{id:2,channel_key:"warp",protocol:"claude",tab_key:"",tab_label:"",content:v("warp","claude-4-5-sonnet"),sort_order:2},{id:3,channel_key:"antigravity",protocol:"claude",tab_key:"",tab_label:"",content:v("antigravity","gemini-2.5-flash-preview"),sort_order:3},{id:4,channel_key:"orchids",protocol:"claude",tab_key:"",tab_label:"",content:v("orchids","claude-sonnet-4-5"),sort_order:4},{id:5,channel_key:"claude_api",protocol:"claude",tab_key:"",tab_label:"",content:v("claude_api","claude-sonnet-4-5"),sort_order:5},{id:6,channel_key:"kiro",protocol:"openai",tab_key:"",tab_label:"",content:g("kiro","claude-sonnet-4-5"),sort_order:1},{id:7,channel_key:"warp",protocol:"openai",tab_key:"",tab_label:"",content:g("warp","claude-4-5-sonnet"),sort_order:2},{id:8,channel_key:"antigravity",protocol:"openai",tab_key:"",tab_label:"",content:g("antigravity","gemini-2.5-flash-preview"),sort_order:3},{id:9,channel_key:"orchids",protocol:"openai",tab_key:"",tab_label:"",content:g("orchids","claude-sonnet-4-5"),sort_order:4},{id:10,channel_key:"cursor",protocol:"openai",tab_key:"",tab_label:"",content:g("cursor","claude-4.5-sonnet"),sort_order:5},{id:11,channel_key:"grok",protocol:"openai",tab_key:"chat",tab_label:"文字对话",content:`# Grok 文字对话
# 端点: /grok/v1/chat/completions
# 模型: grok-3, grok-4, grok-4.1-fast, grok-4.1-thinking 等

curl -X POST {baseUrl}/grok/v1/chat/completions \\
  -H "Content-Type: application/json" \\
  -H "Authorization: Bearer YOUR_API_KEY" \\
  -d '{
    "model": "grok-4.1-fast",
    "stream": true,
    "messages": [
      {"role": "system", "content": "你是一个专业的 AI 助手"},
      {"role": "user", "content": "请用 Python 写一个快速排序算法"}
    ]
  }'`,sort_order:1},{id:12,channel_key:"grok",protocol:"openai",tab_key:"image",tab_label:"图片生成",content:`# Grok 图片生成
# 支持两种方式: 图片 API 或 Chat API
# 参数: n (生成数量 1-10, 流式仅支持 1-2)

# 方式 1: 图片生成 API
# 端点: /grok/v1/images/generations
curl -X POST {baseUrl}/grok/v1/images/generations \\
  -H "Content-Type: application/json" \\
  -H "Authorization: Bearer YOUR_API_KEY" \\
  -d '{
    "prompt": "一只赛博朋克风格机器猫，站在城市天际线前",
    "n": 2,
    "stream": true
  }'

# 方式 2: Chat API + 图片模型
# 模型: grok-imagine-1.0
curl -X POST {baseUrl}/grok/v1/chat/completions \\
  -H "Content-Type: application/json" \\
  -H "Authorization: Bearer YOUR_API_KEY" \\
  -d '{
    "model": "grok-imagine-1.0",
    "stream": true,
    "n": 2,
    "messages": [
      {"role": "user", "content": "一只赛博朋克风格机器猫"}
    ]
  }'`,sort_order:2},{id:13,channel_key:"grok",protocol:"openai",tab_key:"video",tab_label:"视频生成",content:`# Grok 视频生成 (文生视频)
# 参数: aspect_ratio (16:9/9:16/1:1), duration (6/10秒), resolution (480p/720p)

# 方式 1: 视频生成 API
# 端点: /grok/v1/videos/generations
curl -X POST {baseUrl}/grok/v1/videos/generations \\
  -H "Content-Type: application/json" \\
  -H "Authorization: Bearer YOUR_API_KEY" \\
  -d '{
    "prompt": "一只柯基犬在花园里奔跑，阳光明媚，慢动作",
    "aspect_ratio": "16:9",
    "duration": 10,
    "resolution": "720p",
    "stream": true
  }'

# 方式 2: Chat API + 视频模型
# 模型: grok-imagine-1.0-video
curl -X POST {baseUrl}/grok/v1/chat/completions \\
  -H "Content-Type: application/json" \\
  -H "Authorization: Bearer YOUR_API_KEY" \\
  -d '{
    "model": "grok-imagine-1.0-video",
    "stream": true,
    "video_aspect_ratio": "9:16",
    "video_duration": 6,
    "video_resolution": "720p",
    "messages": [
      {"role": "user", "content": "海浪拍打码头，夕阳西下"}
    ]
  }'`,sort_order:3},{id:14,channel_key:"grok",protocol:"openai",tab_key:"image2video",tab_label:"图生视频",content:`# Grok 图生视频 (图片动起来)
# 模型: grok-imagine-1.0-video
# 图片支持 URL 或 base64

# 使用图片 URL
curl -X POST {baseUrl}/grok/v1/chat/completions \\
  -H "Content-Type: application/json" \\
  -H "Authorization: Bearer YOUR_API_KEY" \\
  -d '{
    "model": "grok-imagine-1.0-video",
    "stream": true,
    "video_aspect_ratio": "1:1",
    "video_duration": 6,
    "video_resolution": "480p",
    "messages": [
      {
        "role": "user",
        "content": [
          {"type": "image_url", "image_url": {"url": "https://example.com/image.jpg"}},
          {"type": "text", "text": "让这只猫慢慢转过头来"}
        ]
      }
    ]
  }'`,sort_order:4}];function I(t){return t.replace(/\{baseUrl\}/g,C.value)}async function E(){var t,e;T.value=!0;try{const a=(await z.get("/api/tutorial/channels")).data;a.code===0&&a.data?(h.value=(t=a.data.channels)!=null&&t.length?a.data.channels:w,c.value=(e=a.data.examples)!=null&&e.length?a.data.examples:x):(h.value=w,c.value=x)}catch(a){console.error("Failed to fetch tutorial data, using defaults:",a),h.value=w,c.value=x}finally{T.value=!1}}V(()=>{E()});const O=i(()=>h.value.filter(t=>t.enabled).map(t=>({key:t.key,name:t.name,defaultModel:t.default_model,claudeProtocol:t.claude_protocol,openaiProtocol:t.openai_protocol}))),b=i(()=>{const t=O.value.filter(e=>e.claudeProtocol);return t.length>0&&!k.value&&(k.value=t[0].key),t}),y=i(()=>O.value.filter(t=>t.openaiProtocol)),U=i(()=>b.value.find(t=>t.key===k.value)||b.value[0]),H=i(()=>y.value.find(t=>t.key===_.value)||y.value[0]),B=i(()=>_.value==="grok");function L(t){const e=c.value.find(a=>a.channel_key===t&&a.protocol==="claude");return e?I(e.content):""}function M(t){const e=c.value.find(a=>a.channel_key===t&&a.protocol==="openai"&&!a.tab_key);return e?I(e.content):""}const j=i(()=>c.value.filter(t=>t.channel_key==="grok"&&t.protocol==="openai"&&t.tab_key).sort((t,e)=>t.sort_order-e.sort_order).map(t=>({key:t.tab_key,label:t.tab_label}))),K=i(()=>{const t={};return c.value.filter(e=>e.channel_key==="grok"&&e.protocol==="openai"&&e.tab_key).forEach(e=>{t[e.tab_key]=I(e.content)}),t});return(t,e)=>(l(),n("div",X,[e[17]||(e[17]=o("h2",{class:"page-title"},"使用教程",-1)),e[18]||(e[18]=o("p",{class:"page-desc"},"了解如何使用 API 接口",-1)),o("div",G,[e[11]||(e[11]=o("h3",{class:"card-title"},[o("span",{class:"card-icon icon-link"},[o("svg",{width:"14",height:"14",viewBox:"0 0 14 14",fill:"none"},[o("path",{d:"M6 8L8 6M5 9L3.5 10.5C2.7 11.3 2.7 12.6 3.5 13.4V13.4C4.3 14.2 5.6 14.2 6.4 13.4L8 11.8M8 5L9.5 3.5C10.3 2.7 11.6 2.7 12.4 3.5V3.5C13.2 4.3 13.2 5.6 12.4 6.4L10.8 8",stroke:"currentColor","stroke-width":"1.3","stroke-linecap":"round"})])]),r(" API 地址格式 ")],-1)),o("div",N,s(C.value)+"/{渠道}/v1",1),o("div",F,[e[9]||(e[9]=o("svg",{class:"warning-icon",width:"16",height:"16",viewBox:"0 0 16 16",fill:"none"},[o("path",{d:"M8 1L15 14H1L8 1Z",stroke:"currentColor","stroke-width":"1.3","stroke-linejoin":"round"}),o("path",{d:"M8 6V9M8 11.5V11",stroke:"currentColor","stroke-width":"1.3","stroke-linecap":"round"})],-1)),o("div",null,[e[2]||(e[2]=o("strong",null,"Claude Code 用户注意：",-1)),e[3]||(e[3]=r("配置 API 地址时请使用 ",-1)),o("code",q,s(C.value)+"/{渠道}",1),e[4]||(e[4]=r("， ",-1)),e[5]||(e[5]=o("strong",{class:"text-danger"},"不要",-1)),e[6]||(e[6]=r("添加 ",-1)),e[7]||(e[7]=o("code",{class:"code-inline code-danger"},"/v1",-1)),e[8]||(e[8]=r(" 后缀 ",-1))])]),o("div",D,[o("table",W,[e[10]||(e[10]=o("thead",null,[o("tr",null,[o("th",null,"渠道"),o("th",null,"API 地址"),o("th",null,"默认模型"),o("th",null,"支持协议")])],-1)),o("tbody",null,[(l(!0),n(P,null,A(O.value,a=>(l(),n("tr",{key:a.key},[o("td",null,[o("span",Z,s(a.name),1)]),o("td",null,[o("code",J,s(C.value)+"/"+s(a.key)+"/v1",1)]),o("td",null,[o("code",Q,s(a.defaultModel),1)]),o("td",null,[a.claudeProtocol?(l(),n("span",ee,"Claude")):d("",!0),a.openaiProtocol?(l(),n("span",oe,"OpenAI")):d("",!0)])]))),128))])])])]),o("div",te,[e[16]||(e[16]=o("h3",{class:"card-title"},[o("span",{class:"card-icon icon-code"},[o("svg",{width:"14",height:"14",viewBox:"0 0 14 14",fill:"none"},[o("path",{d:"M4.5 3.5L1 7L4.5 10.5M9.5 3.5L13 7L9.5 10.5",stroke:"currentColor","stroke-width":"1.3","stroke-linecap":"round","stroke-linejoin":"round"})])]),r(" 协议示例 ")],-1)),o("div",ae,[b.value.length>0?(l(),n("button",{key:0,onClick:e[0]||(e[0]=a=>p.value="claude"),class:m(["tab-btn",{active:p.value==="claude"}])}," Claude 协议 ",2)):d("",!0),y.value.length>0?(l(),n("button",{key:1,onClick:e[1]||(e[1]=a=>p.value="openai"),class:m(["tab-btn",{active:p.value==="openai"}])}," OpenAI 协议 ",2)):d("",!0)]),p.value==="claude"&&b.value.length>0?(l(),n("div",ne,[e[12]||(e[12]=o("div",{class:"endpoint-info"},[r(" 端点: "),o("code",{class:"code-inline"},"/{渠道}/v1/messages")],-1)),e[13]||(e[13]=o("p",{class:"auth-info"},[r(" 使用 "),o("code",{class:"code-inline"},"x-api-key"),r(" 请求头进行认证 ")],-1)),o("div",le,[(l(!0),n(P,null,A(b.value,a=>(l(),n("button",{key:a.key,onClick:Y=>k.value=a.key,class:m(["ch-tab",{active:k.value===a.key}])},s(a.name),11,re))),128))]),U.value?(l(),n("pre",se,s(L(U.value.key)),1)):d("",!0)])):d("",!0),p.value==="openai"&&y.value.length>0?(l(),n("div",ie,[e[14]||(e[14]=o("div",{class:"endpoint-info"},[r(" 端点: "),o("code",{class:"code-inline"},"/{渠道}/v1/chat/completions")],-1)),e[15]||(e[15]=o("p",{class:"auth-info"},[r(" 使用 "),o("code",{class:"code-inline"},"Authorization: Bearer YOUR_API_KEY"),r(" 请求头进行认证 ")],-1)),o("div",de,[(l(!0),n(P,null,A(y.value,a=>(l(),n("button",{key:a.key,onClick:Y=>{_.value=a.key,f.value="chat"},class:m(["ch-tab",{active:_.value===a.key},a.key==="grok"&&_.value===a.key?"grok-active":""])},s(a.name),11,ce))),128))]),B.value?(l(),n("div",ue,[o("div",pe,[(l(!0),n(P,null,A(j.value,a=>(l(),n("button",{key:a.key,onClick:Y=>f.value=a.key,class:m(["grok-tab",{active:f.value===a.key}])},s(a.label),11,ke))),128))]),o("pre",_e,s(K.value[f.value]),1)])):H.value?(l(),n("pre",ve,s(M(H.value.key)),1)):d("",!0)])):d("",!0)]),e[19]||(e[19]=S('<div class="card" data-v-adcfdb4f><h3 class="card-title" data-v-adcfdb4f><span class="card-icon icon-tip" data-v-adcfdb4f><svg width="14" height="14" viewBox="0 0 14 14" fill="none" data-v-adcfdb4f><circle cx="7" cy="6" r="4.5" stroke="currentColor" stroke-width="1.3" data-v-adcfdb4f></circle><path d="M5.5 11H8.5M6 10V8.5C6 8 5 7.5 5 6C5 4.9 5.9 4 7 4C8.1 4 9 4.9 9 6C9 7.5 8 8 8 8.5V10" stroke="currentColor" stroke-width="1.3" stroke-linecap="round" stroke-linejoin="round" data-v-adcfdb4f></path></svg></span> 使用说明 </h3><ul class="tips-list" data-v-adcfdb4f><li data-v-adcfdb4f><strong data-v-adcfdb4f>API Key</strong>：请在配置管理中设置 API Key，用于接口认证</li><li data-v-adcfdb4f><strong data-v-adcfdb4f>模型列表</strong>：可在模型管理中查看各渠道支持的模型</li><li data-v-adcfdb4f><strong data-v-adcfdb4f>流式输出</strong>：设置 <code class="code-inline" data-v-adcfdb4f>stream: true</code> 启用流式响应</li><li data-v-adcfdb4f><strong data-v-adcfdb4f>系统提示词</strong>：OpenAI 协议支持 <code class="code-inline" data-v-adcfdb4f>role: &quot;system&quot;</code> 消息</li></ul></div>',1))]))}}),me=$(ge,[["__scopeId","data-v-adcfdb4f"]]);export{me as default};
