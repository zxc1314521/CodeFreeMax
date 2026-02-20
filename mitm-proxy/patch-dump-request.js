/**
 * Patch Kiro's actual extension.js to dump the full request JSON to a file.
 * 
 * Target: D:\Program Files\Kiro\resources\app\extensions\kiro.kiro-agent\dist\extension.js
 * 
 * Usage:
 *   1. Close Kiro first
 *   2. Run: node patch-dump-request.js
 *   3. Start Kiro, send a chat message
 *   4. Check: %TEMP%\kiro_request_dump.json
 *   5. To restore: node patch-dump-request.js --restore
 */

const fs = require('fs');
const path = require('path');

const EXTENSION_PATH = 'D:\\Program Files\\Kiro\\resources\\app\\extensions\\kiro.kiro-agent\\dist\\extension.js';
const BACKUP_PATH = EXTENSION_PATH + '.bak';

// Restore mode
if (process.argv.includes('--restore')) {
  if (fs.existsSync(BACKUP_PATH)) {
    fs.copyFileSync(BACKUP_PATH, EXTENSION_PATH);
    console.log('Restored from backup.');
  } else {
    console.log('No backup found.');
  }
  process.exit(0);
}

if (!fs.existsSync(EXTENSION_PATH)) {
  console.error('Extension not found:', EXTENSION_PATH);
  process.exit(1);
}

// Create backup
if (!fs.existsSync(BACKUP_PATH)) {
  console.log('Creating backup...');
  fs.copyFileSync(EXTENSION_PATH, BACKUP_PATH);
  console.log('Backup saved to:', BACKUP_PATH);
}

console.log('Reading extension...');
let code = fs.readFileSync(EXTENSION_PATH, 'utf8');

// Check if already patched
if (code.includes('[KIRO-DUMP]')) {
  console.log('Already patched! Use --restore to undo first.');
  process.exit(0);
}

// The exact pattern to find (line 702983 area)
const SEARCH = 'qChatLogger.appendLine(input);\n        Metrics18.reportCountMetrics({';

const INJECT = `qChatLogger.appendLine(input);
        // [KIRO-DUMP] Injected request dumper
        try{const _f=require("fs"),_o=require("os"),_p=require("path");const _d=_p.join(_o.tmpdir(),"kiro_request_dump.json");_f.writeFileSync(_d,input);console.log("[KIRO-DUMP] Written to:",_d)}catch(_e){console.error("[KIRO-DUMP]",_e.message)}
        Metrics18.reportCountMetrics({`;

const idx = code.indexOf(SEARCH);
if (idx === -1) {
  console.error('Pattern not found! Kiro may have been updated.');
  // Debug: find nearby
  const alt = 'qChatLogger.appendLine(input)';
  let si = 0;
  while ((si = code.indexOf(alt, si)) >= 0) {
    console.log(`\nFound at offset ${si}:`);
    console.log(code.substring(si, si + 200));
    si += alt.length;
  }
  process.exit(1);
}

code = code.substring(0, idx) + INJECT + code.substring(idx + SEARCH.length);

console.log('Writing patched extension...');
fs.writeFileSync(EXTENSION_PATH, code);
console.log('\nDone! Patch applied successfully.');
console.log('');
console.log('Next steps:');
console.log('  1. Start Kiro');
console.log('  2. Send a chat message');
console.log('  3. Check: %TEMP%\\kiro_request_dump.json');
console.log('');
console.log('To restore original: node patch-dump-request.js --restore');

