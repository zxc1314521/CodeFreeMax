import{d as j,r as b,G as u,a5 as H,N as T,c as a,b as t,e as _,f as i,t as d,P as w,a3 as C,U as p,n as c,g as s}from"./index-BOz7fGOk-1770644176259.js";import{_ as $}from"./_plugin-vue_export-helper-DlAUqK2U-1770644176259.js";const B={class:"h-full overflow-auto bg-background"},Y={class:"p-4 space-y-4"},z={class:"bg-card rounded-xl p-6 shadow-sm border border-border"},E={class:"p-3 bg-muted rounded-lg mb-4 font-mono text-sm text-foreground"},U={class:"mb-4 p-3 bg-amber-50 border border-amber-200 rounded-lg flex items-start gap-2"},L={class:"text-sm text-amber-800"},R={class:"bg-amber-100 px-1.5 py-0.5 rounded text-xs font-mono"},K={class:"overflow-x-auto"},S={class:"w-full text-sm"},V={class:"divide-y divide-border"},X={class:"px-4 py-3"},G={class:"px-2.5 py-1 text-xs font-medium rounded-full bg-amber-100 text-amber-700"},N={class:"px-4 py-3"},q={class:"text-primary font-mono text-xs"},D={class:"px-4 py-3"},F={class:"text-green-600 font-mono text-xs"},J={class:"px-4 py-3"},Q={key:0,class:"px-2 py-0.5 text-xs font-medium rounded-full bg-green-100 text-green-700 mr-1"},Z={key:1,class:"px-2 py-0.5 text-xs font-medium rounded-full bg-amber-100 text-amber-700"},W={class:"bg-card rounded-xl p-6 shadow-sm border border-border"},ee={class:"flex items-center gap-2 bg-muted rounded-lg p-1 w-fit mb-4"},te={key:0},oe={class:"flex items-center gap-2 mb-3 overflow-x-auto pb-1"},re=["onClick"],ae={key:0,class:"bg-sidebar text-primary p-4 rounded-lg overflow-x-auto text-xs font-mono"},se={key:1},ne={class:"flex items-center gap-2 mb-3 overflow-x-auto pb-1"},de=["onClick"],le={key:0},ie={class:"flex items-center gap-1 mb-3 bg-orange-500/10 dark:bg-orange-500/20 rounded-lg p-1 w-fit"},ue={class:"bg-sidebar text-primary p-4 rounded-lg overflow-x-auto text-xs font-mono"},pe={key:1,class:"bg-sidebar text-primary p-4 rounded-lg overflow-x-auto text-xs font-mono"},ce=j({__name:"TutorialView",setup(me){const m=b("openai"),g=b(""),k=b("grok"),l=b("chat"),n=u(()=>window.location.origin),f=u(()=>H.value.map(r=>{const e=T[r];return{key:r,name:e.name,defaultModel:e.defaultModel,claudeProtocol:e.claudeProtocol,openaiProtocol:e.openaiProtocol}})),v=u(()=>{const r=f.value.filter(e=>e.claudeProtocol);return r.length>0&&!g.value&&(g.value=r[0].key),r}),x=u(()=>f.value.filter(e=>e.openaiProtocol)),h=u(()=>v.value.find(r=>r.key===g.value)||v.value[0]),y=u(()=>x.value.find(r=>r.key===k.value)||x.value[0]),P=u(()=>k.value==="grok"),A=(r,e)=>`curl -X POST ${n.value}/${r}/v1/messages \\
  -H "Content-Type: application/json" \\
  -H "x-api-key: YOUR_API_KEY" \\
  -d '{
    "model": "${e}",
    "max_tokens": 4096,
    "stream": true,
    "messages": [
      {"role": "user", "content": "Hello, who are you?"}
    ]
  }'`,I=(r,e)=>`curl -X POST ${n.value}/${r}/v1/chat/completions \\
  -H "Content-Type: application/json" \\
  -H "Authorization: Bearer YOUR_API_KEY" \\
  -d '{
    "model": "${e}",
    "stream": true,
    "messages": [
      {"role": "user", "content": "Hello, who are you?"}
    ]
  }'`,O=u(()=>({chat:`# Grok 文字对话
# 端点: /grok/v1/chat/completions
# 模型: grok-3, grok-4, grok-4.1-fast, grok-4.1-thinking 等

curl -X POST ${n.value}/grok/v1/chat/completions \\
  -H "Content-Type: application/json" \\
  -H "Authorization: Bearer YOUR_API_KEY" \\
  -d '{
    "model": "grok-4.1-fast",
    "stream": true,
    "messages": [
      {
        "role": "system",
        "content": "你是一个专业的 AI 助手"
      },
      {
        "role": "user",
        "content": "请用 Python 写一个快速排序算法"
      }
    ]
  }'`,image:`# Grok 图片生成
# 支持两种方式: 图片 API 或 Chat API
# 参数: n (生成数量 1-10, 流式仅支持 1-2)

# 方式 1: 图片生成 API
# 端点: /grok/v1/images/generations
curl -X POST ${n.value}/grok/v1/images/generations \\
  -H "Content-Type: application/json" \\
  -H "Authorization: Bearer YOUR_API_KEY" \\
  -d '{
    "prompt": "一只正在发光的赛博朋克风格机器猫，霸气的站在城市天际线前",
    "n": 2,
    "stream": true
  }'

# 方式 2: Chat API + 图片模型
# 端点: /grok/v1/chat/completions
# 模型: grok-imagine-1.0
curl -X POST ${n.value}/grok/v1/chat/completions \\
  -H "Content-Type: application/json" \\
  -H "Authorization: Bearer YOUR_API_KEY" \\
  -d '{
    "model": "grok-imagine-1.0",
    "stream": true,
    "n": 2,
    "messages": [
      {
        "role": "user",
        "content": "一只正在发光的赛博朋克风格机器猫，霸气的站在城市天际线前"
      }
    ]
  }'`,video:`# Grok 视频生成 (文生视频)
# 支持两种方式: 视频 API 或 Chat API
# 参数:
#   aspect_ratio: 16:9, 9:16, 1:1, 3:2, 2:3
#   duration: 6 或 10 秒
#   resolution: 480p, 720p

# 方式 1: 视频生成 API
# 端点: /grok/v1/videos/generations
curl -X POST ${n.value}/grok/v1/videos/generations \\
  -H "Content-Type: application/json" \\
  -H "Authorization: Bearer YOUR_API_KEY" \\
  -d '{
    "prompt": "一只可爱的柯基犬在花园里奔跑玩者，阳光明媚，慢动作",
    "aspect_ratio": "16:9",
    "duration": 10,
    "resolution": "720p",
    "stream": true
  }'

# 方式 2: Chat API + 视频模型
# 端点: /grok/v1/chat/completions
# 模型: grok-imagine-1.0-video
# 扩展参数: video_aspect_ratio, video_duration, video_resolution
curl -X POST ${n.value}/grok/v1/chat/completions \\
  -H "Content-Type: application/json" \\
  -H "Authorization: Bearer YOUR_API_KEY" \\
  -d '{
    "model": "grok-imagine-1.0-video",
    "stream": true,
    "video_aspect_ratio": "9:16",
    "video_duration": 6,
    "video_resolution": "720p",
    "messages": [
      {
        "role": "user",
        "content": "海浪拍打码头，夕阳西下，金色光芒洒在水面上"
      }
    ]
  }'`,image2video:`# Grok 图生视频 (图片动起来)
# 端点: /grok/v1/chat/completions
# 模型: grok-imagine-1.0-video
# 说明: 图片支持 URL 或 base64，系统会自动上传到 Grok
# 参数: video_aspect_ratio, video_duration (6/10秒), video_resolution (480p/720p)

# 使用图片 URL
curl -X POST ${n.value}/grok/v1/chat/completions \\
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
          {
            "type": "image_url",
            "image_url": {
              "url": "https://example.com/your-image.jpg"
            }
          },
          {
            "type": "text",
            "text": "让这只猫慢慢转过头来，眩眩眼睡"
          }
        ]
      }
    ]
  }'

# 使用 base64 图片
curl -X POST ${n.value}/grok/v1/chat/completions \\
  -H "Content-Type: application/json" \\
  -H "Authorization: Bearer YOUR_API_KEY" \\
  -d '{
    "model": "grok-imagine-1.0-video",
    "stream": true,
    "video_duration": 6,
    "video_resolution": "480p",
    "messages": [
      {
        "role": "user",
        "content": [
          {
            "type": "image_url",
            "image_url": {
              "url": "data:image/jpeg;base64,/9j/4AAQSkZJRg..."
            }
          },
          {
            "type": "text",
            "text": "让这个人物微笑着点头"
          }
        ]
      }
    ]
  }'`}));return(r,e)=>(s(),a("div",B,[t("div",Y,[e[23]||(e[23]=t("div",null,[t("h1",{class:"text-xl font-bold text-foreground"},"使用教程"),t("p",{class:"text-sm text-muted-foreground mt-0.5"},"了解如何使用 API 接口")],-1)),t("div",z,[e[15]||(e[15]=t("h3",{class:"text-base font-semibold mb-4 text-foreground flex items-center gap-2"},[t("span",{class:"w-8 h-8 bg-amber-100 rounded-lg flex items-center justify-center"},[t("svg",{class:"w-4 h-4 text-amber-600",fill:"none",stroke:"currentColor",viewBox:"0 0 24 24"},[t("path",{"stroke-linecap":"round","stroke-linejoin":"round","stroke-width":"2",d:"M13.828 10.172a4 4 0 00-5.656 0l-4 4a4 4 0 105.656 5.656l1.102-1.101m-.758-4.899a4 4 0 005.656 0l4-4a4 4 0 00-5.656-5.656l-1.1 1.1"})])]),i(" API 地址格式 ")],-1)),t("div",E,d(n.value)+"/{渠道}/v1 ",1),t("div",U,[e[13]||(e[13]=t("svg",{class:"w-5 h-5 text-amber-500 flex-shrink-0 mt-0.5",fill:"none",stroke:"currentColor",viewBox:"0 0 24 24"},[t("path",{"stroke-linecap":"round","stroke-linejoin":"round","stroke-width":"2",d:"M12 9v2m0 4h.01m-6.938 4h13.856c1.54 0 2.502-1.667 1.732-3L13.732 4c-.77-1.333-2.694-1.333-3.464 0L3.34 16c-.77 1.333.192 3 1.732 3z"})],-1)),t("div",L,[e[6]||(e[6]=t("strong",null,"Claude Code 用户注意：",-1)),e[7]||(e[7]=i("配置 API 地址时请使用 ",-1)),t("code",R,d(n.value)+"/{渠道}",1),e[8]||(e[8]=i("，",-1)),e[9]||(e[9]=t("strong",{class:"text-red-600"},"不要",-1)),e[10]||(e[10]=i("添加 ",-1)),e[11]||(e[11]=t("code",{class:"bg-red-100 px-1 py-0.5 rounded text-xs font-mono"},"/v1",-1)),e[12]||(e[12]=i(" 后缀 ",-1))])]),t("div",K,[t("table",S,[e[14]||(e[14]=t("thead",{class:"bg-muted"},[t("tr",{class:"text-left text-xs font-medium text-muted-foreground uppercase"},[t("th",{class:"px-4 py-3"},"渠道"),t("th",{class:"px-4 py-3"},"API 地址"),t("th",{class:"px-4 py-3"},"默认模型"),t("th",{class:"px-4 py-3"},"支持协议")])],-1)),t("tbody",V,[(s(!0),a(w,null,C(f.value,o=>(s(),a("tr",{key:o.key,class:"hover:bg-accent/50"},[t("td",X,[t("span",G,d(o.name),1)]),t("td",N,[t("code",q,d(n.value)+"/"+d(o.key)+"/v1",1)]),t("td",D,[t("code",F,d(o.defaultModel),1)]),t("td",J,[o.claudeProtocol?(s(),a("span",Q,"Claude")):p("",!0),o.openaiProtocol?(s(),a("span",Z,"OpenAI")):p("",!0)])]))),128))])])])]),t("div",W,[e[22]||(e[22]=t("h3",{class:"text-base font-semibold mb-4 text-foreground flex items-center gap-2"},[t("span",{class:"w-8 h-8 bg-amber-100 rounded-lg flex items-center justify-center"},[t("svg",{class:"w-4 h-4 text-amber-600",fill:"none",stroke:"currentColor",viewBox:"0 0 24 24"},[t("path",{"stroke-linecap":"round","stroke-linejoin":"round","stroke-width":"2",d:"M10 20l4-16m4 4l4 4-4 4M6 16l-4-4 4-4"})])]),i(" 协议示例 ")],-1)),t("div",ee,[v.value.length>0?(s(),a("button",{key:0,onClick:e[0]||(e[0]=o=>m.value="claude"),class:c(["px-4 py-1.5 text-sm font-medium rounded-md transition-all",m.value==="claude"?"bg-card text-primary shadow-sm":"text-muted-foreground hover:text-foreground"])}," Claude 协议 ",2)):p("",!0),x.value.length>0?(s(),a("button",{key:1,onClick:e[1]||(e[1]=o=>m.value="openai"),class:c(["px-4 py-1.5 text-sm font-medium rounded-md transition-all",m.value==="openai"?"bg-card text-primary shadow-sm":"text-muted-foreground hover:text-foreground"])}," OpenAI 协议 ",2)):p("",!0)]),m.value==="claude"&&v.value.length>0?(s(),a("div",te,[e[16]||(e[16]=_('<div class="flex items-center gap-2 mb-3" data-v-e19404ec><span class="text-sm text-muted-foreground" data-v-e19404ec>端点: <code class="bg-muted px-1.5 py-0.5 rounded text-xs" data-v-e19404ec>/{渠道}/v1/messages</code></span></div><p class="text-sm text-muted-foreground mb-4" data-v-e19404ec> 使用 <code class="bg-muted px-1.5 py-0.5 rounded text-xs" data-v-e19404ec>x-api-key</code> 请求头进行认证 </p>',2)),t("div",oe,[(s(!0),a(w,null,C(v.value,o=>(s(),a("button",{key:o.key,onClick:M=>g.value=o.key,class:c(["px-3 py-1 text-xs font-medium rounded-md transition-all border whitespace-nowrap",g.value===o.key?"bg-accent text-primary border-primary/30":"bg-card text-muted-foreground border-border hover:border-primary/30"])},d(o.name),11,re))),128))]),h.value?(s(),a("pre",ae,d(A(h.value.key,h.value.defaultModel)),1)):p("",!0)])):p("",!0),m.value==="openai"&&x.value.length>0?(s(),a("div",se,[e[21]||(e[21]=_('<div class="flex items-center gap-2 mb-3" data-v-e19404ec><span class="text-sm text-muted-foreground" data-v-e19404ec>端点: <code class="bg-muted px-1.5 py-0.5 rounded text-xs" data-v-e19404ec>/{渠道}/v1/chat/completions</code></span></div><p class="text-sm text-muted-foreground mb-4" data-v-e19404ec> 使用 <code class="bg-muted px-1.5 py-0.5 rounded text-xs" data-v-e19404ec>Authorization: Bearer YOUR_API_KEY</code> 请求头进行认证 </p>',2)),t("div",ne,[(s(!0),a(w,null,C(x.value,o=>(s(),a("button",{key:o.key,onClick:M=>{k.value=o.key,l.value="chat"},class:c(["px-3 py-1 text-xs font-medium rounded-md transition-all border whitespace-nowrap",k.value===o.key?o.key==="grok"?"bg-orange-500/15 text-orange-700 dark:text-orange-400 border-orange-300 dark:border-orange-500/30":"bg-accent text-primary border-primary/30":"bg-card text-muted-foreground border-border hover:border-primary/30"])},d(o.name),11,de))),128))]),P.value?(s(),a("div",le,[t("div",ie,[t("button",{onClick:e[2]||(e[2]=o=>l.value="chat"),class:c(["px-3 py-1.5 text-xs font-medium rounded-md transition-all flex items-center gap-1.5",l.value==="chat"?"bg-card text-orange-700 dark:text-orange-400 shadow-sm":"text-orange-600 dark:text-orange-400/70 hover:text-orange-700 dark:hover:text-orange-400"])},[...e[17]||(e[17]=[t("svg",{class:"w-3.5 h-3.5",fill:"none",stroke:"currentColor",viewBox:"0 0 24 24"},[t("path",{"stroke-linecap":"round","stroke-linejoin":"round","stroke-width":"2",d:"M8 12h.01M12 12h.01M16 12h.01M21 12c0 4.418-4.03 8-9 8a9.863 9.863 0 01-4.255-.949L3 20l1.395-3.72C3.512 15.042 3 13.574 3 12c0-4.418 4.03-8 9-8s9 3.582 9 8z"})],-1),i(" 文字对话 ",-1)])],2),t("button",{onClick:e[3]||(e[3]=o=>l.value="image"),class:c(["px-3 py-1.5 text-xs font-medium rounded-md transition-all flex items-center gap-1.5",l.value==="image"?"bg-card text-orange-700 dark:text-orange-400 shadow-sm":"text-orange-600 dark:text-orange-400/70 hover:text-orange-700 dark:hover:text-orange-400"])},[...e[18]||(e[18]=[t("svg",{class:"w-3.5 h-3.5",fill:"none",stroke:"currentColor",viewBox:"0 0 24 24"},[t("path",{"stroke-linecap":"round","stroke-linejoin":"round","stroke-width":"2",d:"M4 16l4.586-4.586a2 2 0 012.828 0L16 16m-2-2l1.586-1.586a2 2 0 012.828 0L20 14m-6-6h.01M6 20h12a2 2 0 002-2V6a2 2 0 00-2-2H6a2 2 0 00-2 2v12a2 2 0 002 2z"})],-1),i(" 图片生成 ",-1)])],2),t("button",{onClick:e[4]||(e[4]=o=>l.value="video"),class:c(["px-3 py-1.5 text-xs font-medium rounded-md transition-all flex items-center gap-1.5",l.value==="video"?"bg-card text-orange-700 dark:text-orange-400 shadow-sm":"text-orange-600 dark:text-orange-400/70 hover:text-orange-700 dark:hover:text-orange-400"])},[...e[19]||(e[19]=[t("svg",{class:"w-3.5 h-3.5",fill:"none",stroke:"currentColor",viewBox:"0 0 24 24"},[t("path",{"stroke-linecap":"round","stroke-linejoin":"round","stroke-width":"2",d:"M15 10l4.553-2.276A1 1 0 0121 8.618v6.764a1 1 0 01-1.447.894L15 14M5 18h8a2 2 0 002-2V8a2 2 0 00-2-2H5a2 2 0 00-2 2v8a2 2 0 002 2z"})],-1),i(" 视频生成 ",-1)])],2),t("button",{onClick:e[5]||(e[5]=o=>l.value="image2video"),class:c(["px-3 py-1.5 text-xs font-medium rounded-md transition-all flex items-center gap-1.5",l.value==="image2video"?"bg-card text-orange-700 dark:text-orange-400 shadow-sm":"text-orange-600 dark:text-orange-400/70 hover:text-orange-700 dark:hover:text-orange-400"])},[...e[20]||(e[20]=[t("svg",{class:"w-3.5 h-3.5",fill:"none",stroke:"currentColor",viewBox:"0 0 24 24"},[t("path",{"stroke-linecap":"round","stroke-linejoin":"round","stroke-width":"2",d:"M5 3v4M3 5h4M6 17v4m-2-2h4m5-16l2.286 6.857L21 12l-5.714 2.143L13 21l-2.286-6.857L5 12l5.714-2.143L13 3z"})],-1),i(" 图生视频 ",-1)])],2)]),t("pre",ue,d(O.value[l.value]),1)])):y.value?(s(),a("pre",pe,d(I(y.value.key,y.value.defaultModel)),1)):p("",!0)])):p("",!0)]),e[24]||(e[24]=_('<div class="bg-card rounded-xl p-6 shadow-sm border border-border" data-v-e19404ec><h3 class="text-base font-semibold mb-4 text-foreground flex items-center gap-2" data-v-e19404ec><span class="w-8 h-8 bg-amber-100 rounded-lg flex items-center justify-center" data-v-e19404ec><svg class="w-4 h-4 text-amber-600" fill="none" stroke="currentColor" viewBox="0 0 24 24" data-v-e19404ec><path stroke-linecap="round" stroke-linejoin="round" stroke-width="2" d="M9.663 17h4.673M12 3v1m6.364 1.636l-.707.707M21 12h-1M4 12H3m3.343-5.657l-.707-.707m2.828 9.9a5 5 0 117.072 0l-.548.547A3.374 3.374 0 0014 18.469V19a2 2 0 11-4 0v-.531c0-.895-.356-1.754-.988-2.386l-.548-.547z" data-v-e19404ec></path></svg></span> 使用说明 </h3><ul class="space-y-3 text-sm text-muted-foreground" data-v-e19404ec><li class="flex items-start gap-2" data-v-e19404ec><span class="w-1.5 h-1.5 bg-primary rounded-full mt-2 flex-shrink-0" data-v-e19404ec></span><span data-v-e19404ec><strong class="text-foreground" data-v-e19404ec>API Key</strong>：请在配置管理中设置 API Key，用于接口认证</span></li><li class="flex items-start gap-2" data-v-e19404ec><span class="w-1.5 h-1.5 bg-primary rounded-full mt-2 flex-shrink-0" data-v-e19404ec></span><span data-v-e19404ec><strong class="text-foreground" data-v-e19404ec>模型列表</strong>：可在模型管理中查看各渠道支持的模型</span></li><li class="flex items-start gap-2" data-v-e19404ec><span class="w-1.5 h-1.5 bg-primary rounded-full mt-2 flex-shrink-0" data-v-e19404ec></span><span data-v-e19404ec><strong class="text-foreground" data-v-e19404ec>流式输出</strong>：设置 <code class="bg-muted px-1.5 py-0.5 rounded text-xs" data-v-e19404ec>stream: true</code> 启用流式响应</span></li><li class="flex items-start gap-2" data-v-e19404ec><span class="w-1.5 h-1.5 bg-primary rounded-full mt-2 flex-shrink-0" data-v-e19404ec></span><span data-v-e19404ec><strong class="text-foreground" data-v-e19404ec>系统提示词</strong>：OpenAI 协议支持 <code class="bg-muted px-1.5 py-0.5 rounded text-xs" data-v-e19404ec>role: &quot;system&quot;</code> 消息</span></li></ul></div>',1))])]))}}),xe=$(ce,[["__scopeId","data-v-e19404ec"]]);export{xe as default};
