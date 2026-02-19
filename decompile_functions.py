# Ghidra headless script to decompile functions at specific addresses
# @category Analysis
# @runtime Jython

from ghidra.app.decompiler import DecompInterface
from ghidra.util.task import ConsoleTaskMonitor
from ghidra.program.model.address import AddressSet
from ghidra.app.cmd.disassemble import DisassembleCommand
from ghidra.program.model.symbol import SourceType

# Core kiro2api functions to decompile (address, size, name)
TARGET_FUNCTIONS = [
    # === Kiro Channel ===
    (0x17a4e20, 24160, "kiro.buildKiroRequest"),
    (0x17a0a60, 2688, "kiro.ChatCompletions"),

    # === Warp Channel ===
    (0x17150e0, 3072, "warp.ChatCompletions"),
    (0x1716140, 23936, "warp.buildFullPrompt"),
    (0x1722fe0, 10144, "warp.MapToolToClaudeCode"),
    (0x1722160, 3712, "warp.MapToolsToClaudeCode"),
    (0x1712f40, 3072, "warp.RefreshToken"),
    (0x171f220, 3776, "warp.RefundCredits"),
    (0x1713b80, 2848, "warp.GetQuotaInfo"),

    # === Orchids Channel ===
    (0x175bf20, 5312, "orchids.executeWebSocketRequest"),
    (0x1760cc0, 3488, "orchids.executeSSERequest"),
    (0x1768d40, 4480, "orchids.TransformToolInput"),
    (0x1767bc0, 3456, "orchids.MapToolNameToClient"),
    (0x1754f40, 3712, "orchids.extractMessageContent"),
    (0x1753420, 3648, "orchids.extractUserMessage"),
    (0x175d4a0, 2976, "orchids.handleModelEvent"),

    # === Grok Channel ===
    (0x1612e80, 6912, "grok.ProcessLine"),
    (0x1616000, 5504, "grok.CollectProcessorProcessWithUsage"),
    (0x1606520, 3360, "grok.BuildChatPayload"),
    (0x1603860, 4544, "grok.extractMessages"),
    (0x160cd00, 4704, "grok.ImagineGenerations"),
    (0x161bc00, 3840, "grok.VideoGenerations"),

    # === Antigravity (Augment) Channel ===
    (0x17b0660, 6848, "antigravity.convertMessagesToContents"),
    (0x17b4940, 4256, "antigravity.doStreamRequest"),
    (0x17af640, 4128, "antigravity.buildAntigravityRequest"),
    (0x17ab9a0, 3520, "antigravity.RefreshToken"),
    (0x17b2580, 4320, "antigravity.convertContentToPartsWithMapping"),

    # === Cursor Channel ===
    (0x17f7de0, 9088, "cursor.buildCursorRequest"),
    (0x17fa160, 4736, "cursor.newConnectRequest"),

    # === Claude API Channel ===
    (0x139ce00, 6240, "claudeapi.ChatController.Messages"),
    (0x1394f00, 5952, "claudeapi.checkSessionKey"),
    (0x13934c0, 3424, "claudeapi.injectClaudeCodeContext"),

    # === Common/Context ===
    (0x1727a40, 3200, "context.CompressContextWithTools"),
    (0x1376560, 8672, "logic.WarmGateCredentialCache"),
    (0x1371e40, 6752, "logic.AccountQueueManager.InitializeQueue"),
    (0x137aa00, 128, "common.ResponseHandler.HandleResponse"),
    (0x137aa80, 992, "common.handleErrorResponse"),

    # === Config/Routes ===
    (0x1365fc0, 4896, "controller.ConfigController.Save"),
    (0x136bfe0, 4768, "controller.TestController.Test"),
    (0x136e2a0, 3712, "controller.RegisterModelsRoute"),

    # === DAO ===
    (0x1104dc0, 3072, "dao.migrateKiroToGate"),
    (0x1106660, 3072, "dao.migrateOrchidsToGate"),
    (0x1107440, 3072, "dao.migrateClaudeApiToGate"),
]

def prepare_function(program, addr_long, size, name):
    """Disassemble and create function at address"""
    space = program.getAddressFactory().getDefaultAddressSpace()
    start_addr = space.getAddress(addr_long)
    end_addr = space.getAddress(addr_long + size - 1)

    # Disassemble the range
    addr_set = AddressSet(start_addr, end_addr)
    cmd = DisassembleCommand(addr_set, addr_set, True)
    cmd.applyTo(program, ConsoleTaskMonitor())

    # Create function
    func = getFunctionAt(start_addr)
    if func is None:
        createFunction(start_addr, name)
        func = getFunctionAt(start_addr)
    return func

def decompile_function(decomp, func, addr_long, name):
    """Decompile a prepared function"""
    if func is None:
        return "// FAILED: Could not create function at 0x%x (%s)\n" % (addr_long, name)

    results = decomp.decompileFunction(func, 300, ConsoleTaskMonitor())
    if results is not None and results.decompileCompleted():
        dfunc = results.getDecompiledFunction()
        if dfunc is not None:
            code = dfunc.getC()
            return "// === %s @ 0x%x ===\n%s\n" % (name, addr_long, code)
        else:
            return "// FAILED: decompile returned no function for %s @ 0x%x\n" % (name, addr_long)
    else:
        errmsg = ""
        if results is not None:
            errmsg = str(results.getErrorMessage())
        return "// FAILED to decompile %s @ 0x%x: %s\n" % (name, addr_long, errmsg)

def run():
    program = currentProgram
    decomp = DecompInterface()
    decomp.openProgram(program)

    output = []
    total = len(TARGET_FUNCTIONS)

    for i, (addr, size, name) in enumerate(TARGET_FUNCTIONS):
        print("[%d/%d] Processing %s @ 0x%x (%d bytes)..." % (i+1, total, name, addr, size))
        try:
            # Step 1: Disassemble and create function
            func = prepare_function(program, addr, size, name)
            # Step 2: Decompile
            result = decompile_function(decomp, func, addr, name)
            output.append(result)
            print("  -> OK (%d chars)" % len(result))
        except Exception as e:
            output.append("// ERROR decompiling %s: %s\n" % (name, str(e)))
            print("  -> ERROR: %s" % str(e))

    # Write output
    outfile = "/data/decompiled_output.c"
    with open(outfile, "w") as f:
        f.write("// CodeFreeMax (kiro2api) - Decompiled Core Functions\n")
        f.write("// Generated by Ghidra Headless Decompiler\n")
        f.write("// 43 functions from 7 channels + common modules\n\n")
        f.write("\n".join(output))

    print("\nDone! Output written to %s (%d bytes)" % (outfile, sum(len(x) for x in output)))

run()
