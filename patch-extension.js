const fs = require('fs');
const path = 'extracted/augment-vsix/extension/out/extension.js';
let code = fs.readFileSync(path, 'utf8');

// Pattern 1: checkToolCallSafe(t){return Promise.resolve(t.agentMode==="auto")}
// Replace with: checkToolCallSafe(t){return Promise.resolve(!0)}
const p1 = 'checkToolCallSafe(t){return Promise.resolve(t.agentMode==="auto")}';
const r1 = 'checkToolCallSafe(t){return Promise.resolve(!0)}';

// Pattern 2: checkToolCallSafe(t){if(t.agentMode==="auto")return!0;
// Replace with: checkToolCallSafe(t){return!0;
const p2 = 'checkToolCallSafe(t){if(t.agentMode==="auto")return!0;';
const r2 = 'checkToolCallSafe(t){return!0;';

let count = 0;

let idx1 = code.indexOf(p1);
while (idx1 >= 0) {
  console.log(`Found pattern 1 at offset ${idx1}`);
  code = code.substring(0, idx1) + r1 + code.substring(idx1 + p1.length);
  count++;
  idx1 = code.indexOf(p1, idx1 + r1.length);
}

let idx2 = code.indexOf(p2);
while (idx2 >= 0) {
  console.log(`Found pattern 2 at offset ${idx2}`);
  code = code.substring(0, idx2) + r2 + code.substring(idx2 + p2.length);
  count++;
  idx2 = code.indexOf(p2, idx2 + r2.length);
}

// Pattern 3: the toolSafety check version
// checkToolCallSafe(t){let r=this.findToolIdByName(t.toolName),...
// We want to make this also return true always
const p3 = 'checkToolCallSafe(t){let r=this.findToolIdByName(t.toolName),n=this._toolMap.get(r);switch(r){default:return n?.toolSafety===2?Cp().checkToolSafety(r,JSON.stringify(t.input)):Promise.resolve(n?.toolSafety===1)}}';
const r3 = 'checkToolCallSafe(t){return Promise.resolve(!0)}';

let idx3 = code.indexOf(p3);
while (idx3 >= 0) {
  console.log(`Found pattern 3 at offset ${idx3}`);
  code = code.substring(0, idx3) + r3 + code.substring(idx3 + p3.length);
  count++;
  idx3 = code.indexOf(p3, idx3 + r3.length);
}

if (count > 0) {
  fs.writeFileSync(path, code);
  console.log(`\nPatched ${count} locations successfully.`);
} else {
  console.log('No patterns found! Dumping nearby context for debugging...');
  const searchTerm = 'checkToolCallSafe';
  let si = 0;
  while ((si = code.indexOf(searchTerm, si)) >= 0) {
    console.log(`\n@${si}: ${code.substring(si, si + 120)}`);
    si += searchTerm.length;
  }
}

