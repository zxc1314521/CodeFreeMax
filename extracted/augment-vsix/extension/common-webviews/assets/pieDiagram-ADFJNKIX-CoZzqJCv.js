import{V as b,P as F,aB as P,_ as o,g as V,s as j,a as L,b as q,t as H,q as K,l as R,c as G,F as J,K as Q,a4 as U,e as X,z as Y,H as Z}from"./mermaid-BF5da6U1.js";import{p as tt}from"./chunk-4BX2VUAB-DwxLpe_I.js";import{p as et}from"./treemap-KMMF4GRG-BHLPsMSr.js";import{d as E}from"./arc-HlZqGIJl.js";import{o as at}from"./ordinal-D4oIQs1t.js";import"./debounce-BNOmQ76Y.js";import"./SimpleMonaco-BBDXOnfl.js";import"./_commonjsHelpers-CwkBNZ52.js";import"./min-BK871UjU.js";import"./_baseUniq-D51PL97z.js";import"./noop-CVINQ7cR.js";import"./init-CpIN3PJq.js";try{T=typeof window<"u"?window:typeof global<"u"?global:typeof globalThis<"u"?globalThis:typeof self<"u"?self:{},(W=new T.Error().stack)&&(T._sentryDebugIds=T._sentryDebugIds||{},T._sentryDebugIds[W]="4ee96586-4eb3-4a0c-ac26-a2b937f4d90c",T._sentryDebugIdIdentifier="sentry-dbid-4ee96586-4eb3-4a0c-ac26-a2b937f4d90c")}catch{}var T,W;function nt(t,r){return r<t?-1:r>t?1:r>=t?0:NaN}function rt(t){return t}var it=Z.pie,_={sections:new Map,showData:!1},M=_.sections,O=_.showData,lt=structuredClone(it),N={getConfig:o((()=>structuredClone(lt)),"getConfig"),clear:o((()=>{M=new Map,O=_.showData,Y()}),"clear"),setDiagramTitle:K,getDiagramTitle:H,setAccTitle:q,getAccTitle:L,setAccDescription:j,getAccDescription:V,addSection:o((({label:t,value:r})=>{if(r<0)throw new Error(`"${t}" has invalid value: ${r}. Negative values are not allowed in pie charts. All slice values must be >= 0.`);M.has(t)||(M.set(t,r),R.debug(`added new section: ${t}, with value: ${r}`))}),"addSection"),getSections:o((()=>M),"getSections"),setShowData:o((t=>{O=t}),"setShowData"),getShowData:o((()=>O),"getShowData")},st=o(((t,r)=>{tt(t,r),r.setShowData(t.showData),t.sections.map(r.addSection)}),"populateDb"),ot={parse:o((async t=>{const r=await et("pie",t);R.debug(r),st(r,N)}),"parse")},pt=o((t=>`
  .pieCircle{
    stroke: ${t.pieStrokeColor};
    stroke-width : ${t.pieStrokeWidth};
    opacity : ${t.pieOpacity};
  }
  .pieOuterCircle{
    stroke: ${t.pieOuterStrokeColor};
    stroke-width: ${t.pieOuterStrokeWidth};
    fill: none;
  }
  .pieTitleText {
    text-anchor: middle;
    font-size: ${t.pieTitleTextSize};
    fill: ${t.pieTitleTextColor};
    font-family: ${t.fontFamily};
  }
  .slice {
    font-family: ${t.fontFamily};
    fill: ${t.pieSectionTextColor};
    font-size:${t.pieSectionTextSize};
    // fill: white;
  }
  .legend text {
    fill: ${t.pieLegendTextColor};
    font-family: ${t.fontFamily};
    font-size: ${t.pieLegendTextSize};
  }
`),"getStyles"),ct=o((t=>{const r=[...t.values()].reduce(((i,s)=>i+s),0),I=[...t.entries()].map((([i,s])=>({label:i,value:s}))).filter((i=>i.value/r*100>=1)).sort(((i,s)=>s.value-i.value));return(function(){var i=rt,s=nt,p=null,x=b(0),g=b(F),A=b(0);function l(e){var a,m,C,c,h,u=(e=P(e)).length,y=0,S=new Array(u),d=new Array(u),f=+x.apply(this,arguments),v=Math.min(F,Math.max(-F,g.apply(this,arguments)-f)),D=Math.min(Math.abs(v)/u,A.apply(this,arguments)),k=D*(v<0?-1:1);for(a=0;a<u;++a)(h=d[S[a]=a]=+i(e[a],a,e))>0&&(y+=h);for(s!=null?S.sort((function(w,$){return s(d[w],d[$])})):p!=null&&S.sort((function(w,$){return p(e[w],e[$])})),a=0,C=y?(v-u*k)/y:0;a<u;++a,f=c)m=S[a],c=f+((h=d[m])>0?h*C:0)+k,d[m]={data:e[m],index:a,value:h,startAngle:f,endAngle:c,padAngle:D};return d}return l.value=function(e){return arguments.length?(i=typeof e=="function"?e:b(+e),l):i},l.sortValues=function(e){return arguments.length?(s=e,p=null,l):s},l.sort=function(e){return arguments.length?(p=e,s=null,l):p},l.startAngle=function(e){return arguments.length?(x=typeof e=="function"?e:b(+e),l):x},l.endAngle=function(e){return arguments.length?(g=typeof e=="function"?e:b(+e),l):g},l.padAngle=function(e){return arguments.length?(A=typeof e=="function"?e:b(+e),l):A},l})().value((i=>i.value))(I)}),"createPieArcs"),Dt={parser:ot,db:N,renderer:{draw:o(((t,r,I,B)=>{R.debug(`rendering pie chart
`+t);const i=B.db,s=G(),p=J(i.getConfig(),s.pie),x=18,g=450,A=g,l=Q(r),e=l.append("g");e.attr("transform","translate(225,225)");const{themeVariables:a}=s;let[m]=U(a.pieOuterStrokeWidth);m??=2;const C=p.textPosition,c=Math.min(A,g)/2-40,h=E().innerRadius(0).outerRadius(c),u=E().innerRadius(c*C).outerRadius(c*C);e.append("circle").attr("cx",0).attr("cy",0).attr("r",c+m/2).attr("class","pieOuterCircle");const y=i.getSections(),S=ct(y),d=[a.pie1,a.pie2,a.pie3,a.pie4,a.pie5,a.pie6,a.pie7,a.pie8,a.pie9,a.pie10,a.pie11,a.pie12];let f=0;y.forEach((n=>{f+=n}));const v=S.filter((n=>(n.data.value/f*100).toFixed(0)!=="0")),D=at(d);e.selectAll("mySlices").data(v).enter().append("path").attr("d",h).attr("fill",(n=>D(n.data.label))).attr("class","pieCircle"),e.selectAll("mySlices").data(v).enter().append("text").text((n=>(n.data.value/f*100).toFixed(0)+"%")).attr("transform",(n=>"translate("+u.centroid(n)+")")).style("text-anchor","middle").attr("class","slice"),e.append("text").text(i.getDiagramTitle()).attr("x",0).attr("y",-200).attr("class","pieTitleText");const k=[...y.entries()].map((([n,z])=>({label:n,value:z}))),w=e.selectAll(".legend").data(k).enter().append("g").attr("class","legend").attr("transform",((n,z)=>"translate(216,"+(22*z-22*k.length/2)+")"));w.append("rect").attr("width",x).attr("height",x).style("fill",(n=>D(n.label))).style("stroke",(n=>D(n.label))),w.append("text").attr("x",22).attr("y",14).text((n=>i.getShowData()?`${n.label} [${n.value}]`:n.label));const $=512+Math.max(...w.selectAll("text").nodes().map((n=>n?.getBoundingClientRect().width??0)));l.attr("viewBox",`0 0 ${$} 450`),X(l,g,$,p.useMaxWidth)}),"draw")},styles:pt};export{Dt as diagram};
//# sourceMappingURL=pieDiagram-ADFJNKIX-CoZzqJCv.js.map
