// CodeFreeMax - COMMON Channel Decompiled Functions
// 5 functions

// === context.CompressContextWithTools @ 0x1727a40 ===

long * context_CompressContextWithTools
                 (long param_1,long param_2,undefined8 param_3,long param_4,long param_5,
                 long param_6,undefined8 param_7,undefined8 param_8,long *param_9,
                 undefined8 param_10,long param_11,undefined **param_12,undefined8 *param_13)

{
  bool bVar1;
  char cVar2;
  long in_RAX;
  char *pcVar3;
  long lVar4;
  long lVar5;
  undefined8 uVar6;
  long lVar7;
  long *plVar8;
  long lVar9;
  long lVar10;
  undefined8 *puVar11;
  long extraout_RDX;
  long *extraout_RDX_00;
  long *extraout_RDX_01;
  long *extraout_RDX_02;
  long *extraout_RDX_03;
  undefined8 *unaff_RBX;
  long lVar12;
  long lVar13;
  long *in_R11;
  long unaff_R14;
  undefined8 *in_XMM15_Qa;
  undefined1 auVar14 [16];
  long lStack0000000000000040;
  undefined8 *puStack0000000000000048;
  long lStack0000000000000050;
  long lStack0000000000000058;
  long lStack0000000000000060;
  long lStack0000000000000068;
  long lStack0000000000000070;
  long *plStack0000000000000080;
  long lStack_e0;
  long lStack_d8;
  long lStack_d0;
  long lStack_c8;
  long lStack_c0;
  long lStack_b8;
  long lStack_b0;
  undefined **ppuStack_a8;
  double dStack_a0;
  undefined8 *puStack_98;
  long *plStack_90;
  undefined8 uStack_88;
  long *plStack_80;
  undefined8 *puStack_78;
  long lStack_70;
  long *plStack_68;
  long lStack_60;
  long lStack_58;
  long lStack_50;
  long lStack_48;
  undefined8 *puStack_40;
  long lStack_38;
  undefined *puStack_30;
  undefined8 uStack_28;
  undefined *puStack_20;
  undefined8 uStack_18;
  undefined8 *puStack_10;
  
  lStack0000000000000040 = in_RAX;
  lStack0000000000000050 = param_4;
  puStack0000000000000048 = unaff_RBX;
  lStack0000000000000060 = param_2;
  lStack0000000000000058 = param_1;
  lStack0000000000000068 = param_5;
  lStack0000000000000070 = param_6;
  while (plStack0000000000000080 = in_R11, &lStack_e0 <= *(long **)(unaff_R14 + 0x10)) {
    runtime_morestack_noctxt();
    in_R11 = plStack0000000000000080;
  }
  plStack_80 = (long *)0x0;
  puStack_10 = in_XMM15_Qa;
  plStack_68 = (long *)runtime_newobject();
  plStack_68[1] = lStack0000000000000058;
  plStack_68[2] = lStack0000000000000060;
  if (DAT_02e5e450 != 0) {
    plStack_68 = (long *)runtime_gcWriteBarrier2();
    *in_R11 = lStack0000000000000050;
    in_R11[1] = lStack0000000000000070;
  }
  *plStack_68 = lStack0000000000000050;
  plStack_68[3] = lStack0000000000000068;
  plStack_68[4] = lStack0000000000000070;
  *(undefined1 *)(plStack_68 + 5) = 0;
  if (plStack0000000000000080 == (long *)0x0) {
    plStack0000000000000080 = (long *)PTR_DAT_02ddfaa0;
  }
  if ((char)*plStack0000000000000080 == '\0') {
    return plStack_68;
  }
  lStack_38 = kiro2api_internal_context_GetEffectiveConfig();
  lStack_70 = kiro2api_internal_context_ExtractSessionID();
  puVar11 = puStack0000000000000048;
  if (param_11 == 0) {
    lStack_e0 = 0;
    lStack_60 = 0;
    lVar10 = 0;
  }
  else {
    auVar14 = kiro2api_internal_context_GetSummaryCache(param_11);
    lVar10 = auVar14._0_8_;
    if (puVar11 == (undefined8 *)0x0) {
      if (lVar10 == 0) {
        lStack_e0 = 0;
        lStack_60 = 0;
      }
      else {
        lStack_48 = lVar10;
        cVar2 = kiro2api_internal_context_IsCacheValid(lStack0000000000000060,lStack_38,auVar14._8_8_,lStack0000000000000058);
        if (cVar2 == '\0') {
          lVar10 = 0;
          lStack_e0 = 0;
          lStack_60 = 0;
        }
        else {
          lStack_60 = *(long *)(lStack_48 + 0x10);
          lStack_e0 = *(long *)(lStack_48 + 0x18);
          lVar10 = lStack_48;
        }
      }
    }
    else {
      lStack_e0 = 0;
      lStack_60 = 0;
    }
  }
  if (((lVar10 == 0) || (lVar10 = *(long *)(lVar10 + 0x20), lVar10 < 1)) ||
     (lStack0000000000000058 <= lVar10)) {
    lVar10 = 0;
    lStack_50 = lStack0000000000000050;
    lStack_c0 = lStack0000000000000060;
    lStack_c8 = lStack0000000000000058;
  }
  else {
    lStack_50 = (lVar10 * 0x30 & -(lStack0000000000000060 - lVar10) >> 0x3f) +
                lStack0000000000000050;
    lStack_c0 = lStack0000000000000060 - lVar10;
    lStack_c8 = lStack0000000000000058 - lVar10;
  }
  pcVar3 = (char *)kiro2api_internal_context_ShouldCompressWithContext(lStack_c0,lStack0000000000000068,param_11,lStack_c8,
                                lStack0000000000000070,param_7,param_10,param_11);
  plVar8 = plStack_68;
  plStack_68[0x10] = *(long *)(pcVar3 + 0x20);
  lVar7 = *(long *)(pcVar3 + 0x18);
  plStack_68[0xc] = lVar7;
  lVar9 = lStack_c0;
  lVar4 = lStack_c8;
  lVar5 = lStack_50;
  if (*pcVar3 == '\0') {
    lVar9 = *(long *)(pcVar3 + 8);
    plStack_68[0xb] = *(long *)(pcVar3 + 0x10);
    if (DAT_02e5e450 != 0) {
      lVar7 = plStack_68[10];
      runtime_gcWriteBarrier2();
      *param_9 = lVar9;
      param_9[1] = lVar7;
      lVar7 = extraout_RDX;
    }
    plVar8[10] = lVar9;
    if (lStack_e0 == 0) {
      plVar8[0xd] = lVar7;
      plVar8[0xf] = lVar7;
      return plVar8;
    }
    lVar4 = kiro2api_internal_context_CountTokens();
    lStack_d0 = kiro2api_internal_context_CountMessagesTokens();
    lVar5 = kiro2api_internal_context_GetContextWindow();
    lVar9 = lStack0000000000000070;
    lVar7 = lStack_d0 + lVar4;
    if ((double)lVar7 / (double)lVar5 <= *(double *)(lStack_38 + 0x20)) {
      lVar5 = kiro2api_internal_context_InjectSummaryToSystem(lStack_e0,lVar7,lStack_d0,lStack_60);
      plStack_68[3] = lVar5;
      if (DAT_02e5e450 != 0) {
        lVar5 = plStack_68[4];
        lVar12 = *plStack_68;
        lVar13 = plStack_68[6];
        runtime_gcWriteBarrier6();
        *param_9 = lVar9;
        param_9[1] = lVar5;
        param_9[2] = lStack_50;
        param_9[3] = lVar12;
        param_9[4] = lStack_60;
        param_9[5] = lVar13;
        plStack_68 = extraout_RDX_03;
      }
      plStack_68[4] = lVar9;
      plStack_68[1] = lStack_c8;
      plStack_68[2] = lStack_c0;
      *plStack_68 = lStack_50;
      *(undefined2 *)(plStack_68 + 5) = 0x101;
      plStack_68[7] = lStack_e0;
      plStack_68[6] = lStack_60;
      plStack_68[8] = lVar10;
      plStack_68[9] = lStack_c8;
      plStack_68[0xe] = lVar4;
      plStack_68[0xf] = lStack_d0;
      plStack_68[0xd] = lVar7;
      return plStack_68;
    }
    dStack_a0 = ((double)lVar7 / (double)lVar5) * DAT_01f386c8;
    uStack_88 = github_com_gogf_gf_v2_frame_gins_Log();
    uStack_28 = runtime_convT64();
    puStack_30 = &DAT_0194e5e0;
    uStack_18 = runtime_convT64(SUB84(*(double *)(lStack_38 + 0x20),0),
                             SUB84(DAT_01f386c8 * *(double *)(lStack_38 + 0x20),0));
    puStack_20 = &DAT_0194e5e0;
    github_com_gogf_gf_v2_os_glog_Logger_Infof(&DAT_01ca0903,0x54,&DAT_0194e5e0,puStack0000000000000048,&puStack_30);
    lStack_e0 = 0;
    lStack_60 = 0;
    lVar10 = 0;
    lVar9 = lStack0000000000000060;
    lVar4 = lStack0000000000000058;
    lVar5 = lStack0000000000000050;
  }
  puVar11 = puStack0000000000000048;
  if (param_11 == 0) {
    bVar1 = false;
  }
  else {
    lStack_c8 = lVar4;
    lStack_c0 = lVar9;
    lStack_50 = lVar5;
    cVar2 = kiro2api_internal_context_AcquireLock();
    if (cVar2 == '\0') {
      plStack_68[0xb] = 0x30;
      if (DAT_02e5e450 != 0) {
        lVar10 = plStack_68[10];
        runtime_gcWriteBarrier1();
        *param_9 = lVar10;
        plStack_68 = extraout_RDX_02;
      }
      plStack_68[10] = (long)&DAT_01c86b99;
      plStack_68[0xd] = plStack_68[0xc];
      plStack_68[0xf] = plStack_68[0xc];
      return plStack_68;
    }
    puStack_10 = puVar11;
    bVar1 = true;
  }
  puStack_78 = (undefined8 *)kiro2api_internal_context_SplitHistory(lStack_38);
  lVar7 = lStack_e0;
  if (puStack_78[1] != 0) {
    if (param_12 == (undefined **)0x0) {
      param_12 = &PTR_DAT_01f448c0;
      param_13 = &DAT_02e5d6a0;
    }
    ppuStack_a8 = param_12;
    puStack_40 = param_13;
    uVar6 = kiro2api_internal_context_GenerateSummaryInput(puStack_78[1],puStack_78[2],lStack_38,*puStack_78,
                         *(undefined8 *)(lStack_38 + 0x18));
    puVar11 = puStack0000000000000048;
    auVar14 = (*(code *)ppuStack_a8[3])(uVar6,lVar7);
    lVar7 = lStack0000000000000058;
    lStack_58 = auVar14._0_8_;
    if (puVar11 != (undefined8 *)0x0) {
      plVar8 = plStack_68;
      plStack_80 = (long *)kiro2api_internal_context_fallbackTruncate(lStack0000000000000050,lStack0000000000000058,auVar14._8_8_,
                                        plStack_68,lStack0000000000000060,param_10);
      puStack_98 = puStack0000000000000048;
      if (bVar1) {
        plStack_90 = plVar8;
        (*(code *)*puStack_10)();
      }
      return plStack_80;
    }
    lStack_d8 = lStack0000000000000040;
    if (param_11 != 0) {
      lStack_b0 = puStack_78[1];
      puStack_40 = (undefined8 *)kiro2api_internal_context_ComputeFingerprint(*(undefined8 *)(lStack_38 + 0x58));
      lStack_b8 = lVar7;
      lVar7 = runtime_newobject();
      *(long *)(lVar7 + 8) = param_11;
      auVar14._8_8_ = lStack_b0 + lVar10;
      auVar14._0_8_ = lVar7;
      if (DAT_02e5e450 != 0) {
        auVar14 = runtime_gcWriteBarrier3();
        *param_9 = lStack_70;
        param_9[1] = lStack_58;
        param_9[2] = (long)puStack_40;
      }
      plVar8 = auVar14._0_8_;
      *plVar8 = lStack_70;
      plVar8[3] = lStack_d8;
      plVar8[2] = lStack_58;
      plVar8[4] = auVar14._8_8_;
      plVar8[6] = lStack_b8;
      plVar8[5] = (long)puStack_40;
      kiro2api_internal_context_SetSummaryCache();
    }
    lVar7 = lStack0000000000000070;
    lVar9 = kiro2api_internal_context_InjectSummaryToSystem(lStack_d8);
    plStack_68[3] = lVar9;
    plVar8 = plStack_68;
    if (DAT_02e5e450 != 0) {
      lVar9 = plStack_68[4];
      runtime_gcWriteBarrier2();
      *param_9 = lVar7;
      param_9[1] = lVar9;
      plVar8 = extraout_RDX_00;
    }
    plVar8[4] = lVar7;
    lVar7 = puStack_78[5];
    lVar9 = puStack_78[3];
    plVar8[1] = puStack_78[4];
    plVar8[2] = lVar7;
    puVar11 = puStack_78;
    if (DAT_02e5e450 != 0) {
      lVar7 = *plVar8;
      lVar4 = plVar8[6];
      runtime_gcWriteBarrier4();
      *param_9 = lVar9;
      param_9[1] = lVar7;
      param_9[2] = lStack_58;
      param_9[3] = lVar4;
      plVar8 = extraout_RDX_01;
    }
    *plVar8 = lVar9;
    *(undefined1 *)(plVar8 + 5) = 1;
    plVar8[7] = lStack_d8;
    plVar8[6] = lStack_58;
    plVar8[8] = puVar11[1] + lVar10;
    plVar8[9] = puVar11[4];
    lVar10 = kiro2api_internal_context_CountTokens();
    plStack_68[0xe] = lVar10;
    lVar10 = kiro2api_internal_context_CountMessagesTokens();
    plStack_68[0xf] = lVar10;
    plStack_68[0xd] = plStack_68[0xe] + lVar10;
    plStack_80 = plStack_68;
    if (bVar1) {
      (*(code *)*puStack_10)();
    }
    return plStack_80;
  }
  plStack_68[0xb] = 0x30;
  plVar8 = plStack_68;
  if (DAT_02e5e450 != 0) {
    lVar10 = plStack_68[10];
    runtime_gcWriteBarrier1();
    *param_9 = lVar10;
  }
  plVar8[10] = (long)&DAT_01c86bc9;
  plVar8[0xd] = plVar8[0xc];
  plVar8[0xf] = plVar8[0xc];
  plStack_80 = plVar8;
  if (bVar1) {
    (*(code *)*puStack_10)();
  }
  return plStack_80;
}




// === logic.WarmGateCredentialCache @ 0x1376560 ===

void logic_WarmGateCredentialCache(undefined *param_1)

{
  bool bVar1;
  char cVar2;
  undefined8 *in_RAX;
  undefined8 *puVar3;
  long lVar4;
  undefined8 *puVar5;
  undefined1 *puVar6;
  long lVar7;
  long lVar8;
  undefined8 *puVar9;
  undefined8 unaff_RBX;
  uint uVar10;
  undefined8 uVar11;
  long lVar12;
  undefined8 *puVar13;
  undefined8 *puVar14;
  undefined8 *puVar15;
  undefined *puVar16;
  long unaff_R14;
  undefined8 in_XMM15_Qa;
  undefined8 in_XMM15_Qb;
  undefined1 auVar17 [16];
  undefined1 auVar18 [16];
  undefined1 auVar19 [16];
  undefined1 auVar20 [16];
  undefined8 *puStack0000000000000008;
  undefined8 uStack0000000000000010;
  long lStack_4c8;
  long lStack_4c0;
  undefined8 *puStack_4b8;
  undefined8 *puStack_4b0;
  long lStack_4a8;
  long lStack_4a0;
  long lStack_498;
  long lStack_490;
  undefined8 *puStack_488;
  undefined8 *puStack_480;
  undefined8 *puStack_478;
  undefined8 *puStack_470;
  undefined8 *puStack_468;
  undefined8 *puStack_460;
  undefined8 *puStack_458;
  undefined8 *puStack_450;
  undefined8 *puStack_448;
  undefined8 *puStack_440;
  undefined8 *puStack_438;
  undefined8 *puStack_430;
  undefined8 *puStack_428;
  undefined8 *puStack_420;
  undefined8 *puStack_418;
  undefined8 *puStack_410;
  undefined8 *puStack_408;
  undefined8 *puStack_400;
  undefined8 *puStack_3f8;
  undefined8 *puStack_3f0;
  undefined8 *puStack_3e8;
  undefined8 *puStack_3e0;
  long lStack_3d8;
  undefined8 *puStack_3d0;
  long lStack_3c8;
  undefined8 *puStack_3c0;
  long lStack_3b8;
  undefined8 uStack_3b0;
  undefined8 *puStack_3a8;
  long lStack_3a0;
  undefined8 uStack_398;
  undefined *puStack_390;
  long lStack_388;
  undefined1 auStack_380 [32];
  undefined1 auStack_360 [32];
  undefined1 auStack_340 [32];
  undefined1 auStack_320 [32];
  undefined1 auStack_300 [32];
  undefined1 auStack_2e0 [32];
  undefined1 auStack_2c0 [32];
  undefined1 auStack_2a0 [32];
  undefined8 uStack_280;
  undefined8 uStack_278;
  undefined8 uStack_270;
  undefined8 uStack_268;
  undefined8 uStack_260;
  long lStack_258;
  long lStack_250;
  long lStack_248;
  long lStack_240;
  long lStack_238;
  long lStack_230;
  long *plStack_228;
  long *plStack_220;
  long *plStack_218;
  long *plStack_210;
  long lStack_208;
  undefined8 *puStack_200;
  undefined8 *puStack_1f8;
  undefined8 *puStack_1f0;
  undefined8 *puStack_1e8;
  undefined1 *puStack_1e0;
  undefined1 *puStack_1d8;
  undefined1 *puStack_1d0;
  undefined1 *puStack_1c8;
  long lStack_1c0;
  long lStack_1b8;
  long lStack_1b0;
  long lStack_1a8;
  undefined8 uStack_1a0;
  undefined8 uStack_198;
  undefined8 uStack_190;
  undefined8 uStack_188;
  long lStack_180;
  undefined8 *puStack_178;
  undefined8 *puStack_170;
  undefined8 *puStack_168;
  undefined8 *puStack_160;
  undefined8 *puStack_158;
  undefined8 *puStack_150;
  undefined8 *puStack_148;
  undefined8 *puStack_140;
  undefined8 uStack_138;
  undefined8 uStack_130;
  undefined8 uStack_128;
  undefined8 uStack_120;
  undefined8 uStack_118;
  undefined8 uStack_110;
  undefined8 uStack_108;
  undefined8 uStack_100;
  undefined8 uStack_f8;
  undefined8 uStack_f0;
  undefined8 uStack_e8;
  undefined8 uStack_e0;
  undefined8 uStack_d8;
  undefined8 uStack_d0;
  undefined8 uStack_c8;
  undefined8 uStack_c0;
  undefined8 uStack_b8;
  undefined8 uStack_b0;
  undefined8 *puStack_a8;
  undefined **ppuStack_a0;
  undefined8 auStack_98 [4];
  undefined8 auStack_78 [4];
  undefined8 auStack_58 [4];
  undefined8 auStack_38 [4];
  undefined8 *puStack_18;
  long lStack_10;
  
  puStack0000000000000008 = in_RAX;
  uStack0000000000000010 = unaff_RBX;
  while (&lStack_4c8 <= *(long **)(unaff_R14 + 0x10)) {
    runtime_morestack_noctxt();
  }
  puVar3 = (undefined8 *)xdZLD7_I72MS_J1x();
  puVar5 = puStack0000000000000008;
  if ((puVar3 == (undefined8 *)0x0) || (lStack_388 = puVar3[1], lStack_388 == 0)) {
    uStack_260 = github_com_gogf_gf_v2_frame_gins_Log();
    puVar5 = (undefined8 *)runtime_newobject();
    *puVar5 = &DAT_0194e220;
    puVar5[1] = &PTR_DAT_01f39fc0;
    github_com_gogf_gf_v2_os_glog_Logger_Warning(puVar5,1,&PTR_DAT_01f39fc0,uStack0000000000000010,1);
    return;
  }
  uStack_130 = *puVar3;
  lVar4 = kiro2api_internal_dao_AccountDao_GetAllNormal();
  if ((param_1 == (undefined *)0x0) && (puVar5 != (undefined8 *)0x0)) {
    puStack_4b0 = puVar5;
    lStack_208 = lVar4;
    if (&DAT_00000004 < puVar5) {
      puVar5 = (undefined8 *)runtime_makeslice();
    }
    else {
      puVar5 = auStack_38;
    }
    if (&DAT_00000004 < puStack_4b0) {
      puStack_1e8 = puVar5;
      puStack_1c8 = (undefined1 *)runtime_makeslice();
      puVar5 = puStack_1e8;
    }
    else {
      puStack_1c8 = auStack_2a0;
    }
    lVar4 = 0;
    uVar10 = 0;
    bVar1 = false;
    puVar3 = (undefined8 *)0x0;
    param_1 = (undefined *)0x0;
    puVar14 = puStack_4b0;
    puVar9 = puStack_4b0;
    while (lVar8 = lStack_388, puStack_450 = puVar3, (long)param_1 < (long)puStack_4b0) {
      puStack_160 = *(undefined8 **)(lStack_208 + (long)param_1 * 8);
      lStack_490 = lVar4;
      puStack_470 = puVar14;
      puStack_430 = puVar9;
      puStack_390 = param_1;
      puStack_1e8 = puVar5;
      plStack_210 = (long *)runtime_makemap_small();
      if ((4 < (long)puStack_160[0xe]) && (cVar2 = runtime_memequal(), cVar2 != '\0')) {
        uStack_398 = puStack_160[0xe];
        uStack_138 = puStack_160[0xd];
        puVar5 = (undefined8 *)runtime_mapassign_faststr(0xd,uStack_398,uStack_138,&DAT_01c49a06);
        puVar5[1] = uStack_398;
        if (DAT_02e5e450 != 0) {
          auVar20 = runtime_gcWriteBarrier2();
          puVar5 = auVar20._0_8_;
          *puVar3 = uStack_138;
          puVar3[1] = auVar20._8_8_;
        }
        *puVar5 = uStack_138;
      }
      if ((4 < (long)puStack_160[0x10]) && (cVar2 = runtime_memequal(), cVar2 != '\0')) {
        uStack_398 = puStack_160[0x10];
        uStack_138 = puStack_160[0xf];
        puVar5 = (undefined8 *)runtime_mapassign_faststr(9,uStack_398,uStack_138,&DAT_01c41e13);
        puVar5[1] = uStack_398;
        if (DAT_02e5e450 != 0) {
          auVar20 = runtime_gcWriteBarrier2();
          puVar5 = auVar20._0_8_;
          *puVar3 = uStack_138;
          puVar3[1] = auVar20._8_8_;
        }
        *puVar5 = uStack_138;
      }
      if ((4 < (long)puStack_160[0x12]) && (cVar2 = runtime_memequal(), cVar2 != '\0')) {
        uStack_398 = puStack_160[0x12];
        uStack_138 = puStack_160[0x11];
        puVar5 = (undefined8 *)runtime_mapassign_faststr(0xd,uStack_398,uStack_138,&DAT_01c49a20);
        puVar5[1] = uStack_398;
        if (DAT_02e5e450 != 0) {
          auVar20 = runtime_gcWriteBarrier2();
          puVar5 = auVar20._0_8_;
          *puVar3 = uStack_138;
          puVar3[1] = auVar20._8_8_;
        }
        *puVar5 = uStack_138;
      }
      lVar4 = lStack_490;
      if (plStack_210 == (long *)0x0) {
        lVar8 = 0;
      }
      else {
        lVar8 = *plStack_210;
      }
      puVar14 = puStack_470;
      puVar5 = puStack_1e8;
      if (lVar8 < 1) {
        uVar10 = uVar10 & 0xff;
        puVar9 = puStack_430;
        puVar3 = puStack_450;
      }
      else {
        puVar3 = (undefined8 *)(lStack_490 + 1);
        if (puStack_470 < puVar3) {
          if ((((long)puVar3 < 5) && ((char)uVar10 == '\0')) && (lStack_490 == 0)) {
            uStack_c8 = in_XMM15_Qa;
            uStack_c0 = in_XMM15_Qb;
            uStack_b8 = in_XMM15_Qa;
            uStack_b0 = in_XMM15_Qb;
            puVar5 = &uStack_c8;
            puVar14 = (undefined8 *)&DAT_00000004;
            uVar10 = 1;
          }
          else {
            puVar5 = (undefined8 *)runtime_growslice(1,&DAT_01a23240);
            uVar10 = uVar10 & 0xff;
          }
        }
        else {
          uVar10 = uVar10 & 0xff;
        }
        auVar20._8_8_ = puVar3;
        auVar20._0_8_ = plStack_210;
        puVar9 = puStack_160;
        if (DAT_02e5e450 != 0) {
          puVar3 = (undefined8 *)puVar5[lVar4];
          puVar13 = puVar3;
          auVar20 = runtime_gcWriteBarrier2();
          *puVar13 = auVar20._0_8_;
          puVar13[1] = puVar3;
        }
        lVar4 = auVar20._8_8_;
        puVar5[lVar4 + -1] = auVar20._0_8_;
        puVar3 = (undefined8 *)((long)puStack_450 + 1);
        uVar11 = *puVar9;
        puVar6 = puStack_1c8;
        puVar9 = puStack_430;
        if (puStack_430 < puVar3) {
          puStack_3e0 = puVar14;
          lStack_3d8 = lVar4;
          uStack_3b0 = uVar11;
          puStack_158 = puVar5;
          if (((4 < (long)puVar3) || (bVar1)) || (puStack_450 != (undefined8 *)0x0)) {
            puVar6 = (undefined1 *)runtime_growslice(1,&DAT_0194e420);
            uVar10 = uVar10 & 0xff;
            lVar4 = lStack_3d8;
            puVar5 = puStack_158;
            puVar14 = puStack_3e0;
            uVar11 = uStack_3b0;
          }
          else {
            bVar1 = true;
            puVar6 = auStack_320;
            puVar9 = (undefined8 *)&DAT_00000004;
          }
        }
        *(undefined8 *)(puVar6 + (long)puVar3 * 8 + -8) = uVar11;
        puStack_1c8 = puVar6;
      }
      param_1 = puStack_390 + 1;
    }
    if (lVar4 != 0) {
      lVar12 = 4;
      lVar7 = kiro2api_internal_gate_DecryptBatch();
      if (puVar5 == (undefined8 *)0x0) {
        lVar4 = DAT_02c67718;
        if (0 < lVar12) {
          lVar4 = lVar12 * 1000000000;
        }
        lStack_4c0 = lVar8;
        puVar5 = (undefined8 *)0x0;
        lStack_238 = lVar7;
        while ((long)puVar5 < lStack_4c0) {
          uVar11 = *(undefined8 *)(lStack_238 + (long)puVar5 * 8);
          lVar8 = lVar4;
          puStack_410 = puVar5;
          if (0 < lVar4) {
            uStack_188 = uVar11;
            lVar8 = math_rand_Int63n(uVar11,puVar5,
                                 SUB168(SEXT816(-0x3333333333333333) * SEXT816(lVar4),8),lVar4);
            lVar8 = lVar8 + (lVar4 - (SUB168(SEXT816(-0x3333333333333333) * SEXT816(lVar4),8) +
                                      lVar4 >> 3));
            uVar11 = uStack_188;
          }
          if (puStack_450 <= puStack_410) {
                    /* WARNING: Subroutine does not return */
            runtime_panicIndex();
          }
          kiro2api_internal_gate_SetCachedCredentialsWithTTL(uVar11,lVar8,lVar8,*(undefined8 *)(puStack_1c8 + (long)puStack_410 * 8),
                       puStack_1c8,lVar4);
          puVar5 = (undefined8 *)((long)puStack_410 + 1);
        }
        uStack_268 = github_com_gogf_gf_v2_frame_gins_Log();
        lStack_10 = runtime_convT64();
        puStack_18 = &DAT_0194e460;
        param_1 = &DAT_01c80231;
        github_com_gogf_gf_v2_os_glog_Logger_Infof(&DAT_01c80231,0x2b,&DAT_0194e460,uStack0000000000000010);
      }
      else {
        puStack_3f0 = puVar5;
        lStack_1a8 = lVar4;
        github_com_gogf_gf_v2_frame_gins_Log();
        if (puStack_3f0 == (undefined8 *)0x0) {
          puStack_18 = (undefined8 *)0x0;
        }
        else {
          puStack_18 = (undefined8 *)puStack_3f0[1];
        }
        lStack_10 = lStack_1a8;
        param_1 = &DAT_01c79821;
        github_com_gogf_gf_v2_os_glog_Logger_Errorf(&DAT_01c79821,0x27,lStack_1a8,uStack0000000000000010);
      }
    }
  }
  puVar5 = puStack0000000000000008;
  lVar4 = kiro2api_internal_dao_WarpAccountDao_GetAllNormal();
  if ((param_1 == (undefined *)0x0) && (puVar5 != (undefined8 *)0x0)) {
    lStack_258 = lVar4;
    if (&DAT_00000004 < puVar5) {
      puStack_1f0 = (undefined8 *)runtime_makeslice();
      puStack_1d0 = (undefined1 *)runtime_makeslice();
      puVar3 = puStack_1f0;
    }
    else {
      puStack_1d0 = auStack_2c0;
      puVar3 = auStack_58;
    }
    lVar4 = 0;
    uVar10 = 0;
    bVar1 = false;
    puVar9 = (undefined8 *)0x0;
    param_1 = (undefined *)0x0;
    puVar13 = puVar5;
    puVar14 = puVar5;
    while (lVar8 = lStack_388, puStack_458 = puVar9, (long)param_1 < (long)puVar5) {
      puStack_168 = *(undefined8 **)(lStack_258 + (long)param_1 * 8);
      lStack_498 = lVar4;
      puStack_478 = puVar13;
      puStack_438 = puVar14;
      puStack_390 = param_1;
      puStack_1f0 = puVar3;
      plStack_218 = (long *)runtime_makemap_small();
      if ((4 < (long)puStack_168[6]) && (cVar2 = runtime_memequal(), cVar2 != '\0')) {
        uStack_398 = puStack_168[6];
        uStack_138 = puStack_168[5];
        puVar3 = (undefined8 *)runtime_mapassign_faststr(0xd,uStack_398,uStack_138,&DAT_01c49a06);
        puVar3[1] = uStack_398;
        if (DAT_02e5e450 != 0) {
          auVar20 = runtime_gcWriteBarrier2();
          puVar3 = auVar20._0_8_;
          *puVar9 = uStack_138;
          puVar9[1] = auVar20._8_8_;
        }
        *puVar3 = uStack_138;
      }
      lVar4 = lStack_498;
      if (plStack_218 == (long *)0x0) {
        lVar8 = 0;
      }
      else {
        lVar8 = *plStack_218;
      }
      puVar13 = puStack_478;
      puVar3 = puStack_1f0;
      if (lVar8 < 1) {
        uVar10 = uVar10 & 0xff;
        puVar14 = puStack_438;
        puVar9 = puStack_458;
      }
      else {
        puVar9 = (undefined8 *)(lStack_498 + 1);
        if (puStack_478 < puVar9) {
          if ((((long)puVar9 < 5) && ((char)uVar10 == '\0')) && (lStack_498 == 0)) {
            uStack_e8 = in_XMM15_Qa;
            uStack_e0 = in_XMM15_Qb;
            uStack_d8 = in_XMM15_Qa;
            uStack_d0 = in_XMM15_Qb;
            puVar3 = &uStack_e8;
            puVar13 = (undefined8 *)&DAT_00000004;
            uVar10 = 1;
          }
          else {
            puVar3 = (undefined8 *)runtime_growslice(1,&DAT_01a23240);
            uVar10 = uVar10 & 0xff;
          }
        }
        else {
          uVar10 = uVar10 & 0xff;
        }
        auVar19._8_8_ = puVar9;
        auVar19._0_8_ = plStack_218;
        puVar14 = puStack_168;
        if (DAT_02e5e450 != 0) {
          puVar9 = (undefined8 *)puVar3[lVar4];
          puVar15 = puVar9;
          auVar19 = runtime_gcWriteBarrier2();
          *puVar15 = auVar19._0_8_;
          puVar15[1] = puVar9;
        }
        lVar4 = auVar19._8_8_;
        puVar3[lVar4 + -1] = auVar19._0_8_;
        puVar9 = (undefined8 *)((long)puStack_458 + 1);
        uVar11 = *puVar14;
        puVar6 = puStack_1d0;
        puVar14 = puStack_438;
        if (puStack_438 < puVar9) {
          puStack_3d0 = puVar13;
          lStack_3c8 = lVar4;
          uStack_3b0 = uVar11;
          puStack_150 = puVar3;
          if (((4 < (long)puVar9) || (bVar1)) || (puStack_458 != (undefined8 *)0x0)) {
            puVar6 = (undefined1 *)runtime_growslice(1,&DAT_0194e420);
            uVar10 = uVar10 & 0xff;
            lVar4 = lStack_3c8;
            puVar3 = puStack_150;
            puVar13 = puStack_3d0;
            uVar11 = uStack_3b0;
          }
          else {
            bVar1 = true;
            puVar6 = auStack_340;
            puVar14 = (undefined8 *)&DAT_00000004;
          }
        }
        *(undefined8 *)(puVar6 + (long)puVar9 * 8 + -8) = uVar11;
        puStack_1d0 = puVar6;
      }
      param_1 = puStack_390 + 1;
    }
    if (lVar4 != 0) {
      lVar12 = 4;
      lVar7 = kiro2api_internal_gate_DecryptBatch();
      if (puVar3 == (undefined8 *)0x0) {
        lVar4 = DAT_02c67718;
        if (0 < lVar12) {
          lVar4 = lVar12 * 1000000000;
        }
        lStack_4c8 = lVar8;
        puVar5 = (undefined8 *)0x0;
        lStack_240 = lVar7;
        while ((long)puVar5 < lStack_4c8) {
          uVar11 = *(undefined8 *)(lStack_240 + (long)puVar5 * 8);
          lVar8 = lVar4;
          puStack_418 = puVar5;
          if (0 < lVar4) {
            uStack_190 = uVar11;
            lVar8 = math_rand_Int63n(uVar11,puVar5,
                                 SUB168(SEXT816(-0x3333333333333333) * SEXT816(lVar4),8),lVar4);
            lVar8 = lVar8 + (lVar4 - (SUB168(SEXT816(-0x3333333333333333) * SEXT816(lVar4),8) +
                                      lVar4 >> 3));
            uVar11 = uStack_190;
          }
          if (puStack_458 <= puStack_418) {
                    /* WARNING: Subroutine does not return */
            runtime_panicIndex();
          }
          kiro2api_internal_gate_SetCachedCredentialsWithTTL(uVar11,lVar8,lVar8,*(undefined8 *)(puStack_1d0 + (long)puStack_418 * 8),
                       puStack_1d0,lVar4);
          puVar5 = (undefined8 *)((long)puStack_418 + 1);
        }
        uStack_270 = github_com_gogf_gf_v2_frame_gins_Log();
        lStack_10 = runtime_convT64();
        puStack_18 = &DAT_0194e460;
        param_1 = &DAT_01c8025c;
        github_com_gogf_gf_v2_os_glog_Logger_Infof(&DAT_01c8025c,0x2b,&DAT_0194e460,uStack0000000000000010);
      }
      else {
        puStack_3f8 = puVar3;
        lStack_1b0 = lVar4;
        github_com_gogf_gf_v2_frame_gins_Log();
        if (puStack_3f8 == (undefined8 *)0x0) {
          puStack_18 = (undefined8 *)0x0;
        }
        else {
          puStack_18 = (undefined8 *)puStack_3f8[1];
        }
        lStack_10 = lStack_1b0;
        param_1 = &DAT_01c79848;
        github_com_gogf_gf_v2_os_glog_Logger_Errorf(&DAT_01c79848,0x27,lStack_1b0,uStack0000000000000010);
      }
    }
  }
  puVar5 = puStack0000000000000008;
  lVar4 = kiro2api_internal_dao_ClaudeApiAccountDao_GetAllNormal();
  if ((param_1 == (undefined *)0x0) && (puVar5 != (undefined8 *)0x0)) {
    puStack_3e8 = puVar5;
    lStack_180 = lVar4;
    if (&DAT_00000004 < puVar5) {
      puVar5 = (undefined8 *)runtime_makeslice();
    }
    else {
      puVar5 = auStack_78;
    }
    if (&DAT_00000004 < puStack_3e8) {
      puStack_1f8 = puVar5;
      puStack_1d8 = (undefined1 *)runtime_makeslice();
      puVar5 = puStack_1f8;
    }
    else {
      puStack_1d8 = auStack_2e0;
    }
    lVar4 = 0;
    uVar10 = 0;
    bVar1 = false;
    puVar3 = (undefined8 *)0x0;
    param_1 = (undefined *)0x0;
    puVar14 = puStack_3e8;
    puVar9 = puStack_3e8;
    while (lVar8 = lStack_388, puStack_460 = puVar3, (long)param_1 < (long)puStack_3e8) {
      puStack_170 = *(undefined8 **)(lStack_180 + (long)param_1 * 8);
      lStack_4a0 = lVar4;
      puStack_480 = puVar14;
      puStack_440 = puVar9;
      puStack_390 = param_1;
      puStack_1f8 = puVar5;
      plStack_220 = (long *)runtime_makemap_small();
      if ((4 < (long)puStack_170[6]) && (cVar2 = runtime_memequal(), cVar2 != '\0')) {
        uStack_398 = puStack_170[6];
        uStack_138 = puStack_170[5];
        puVar5 = (undefined8 *)runtime_mapassign_faststr(5,uStack_398,uStack_138,&DAT_01c3a57b);
        puVar5[1] = uStack_398;
        if (DAT_02e5e450 != 0) {
          auVar20 = runtime_gcWriteBarrier2();
          puVar5 = auVar20._0_8_;
          *puVar3 = uStack_138;
          puVar3[1] = auVar20._8_8_;
        }
        *puVar5 = uStack_138;
      }
      if ((4 < (long)puStack_170[0xc]) && (cVar2 = runtime_memequal(), cVar2 != '\0')) {
        uStack_398 = puStack_170[0xc];
        uStack_138 = puStack_170[0xb];
        puVar5 = (undefined8 *)runtime_mapassign_faststr(0xb,uStack_398,uStack_138,&DAT_01c46113);
        puVar5[1] = uStack_398;
        if (DAT_02e5e450 != 0) {
          auVar20 = runtime_gcWriteBarrier2();
          puVar5 = auVar20._0_8_;
          *puVar3 = uStack_138;
          puVar3[1] = auVar20._8_8_;
        }
        *puVar5 = uStack_138;
      }
      if ((4 < (long)puStack_170[0x10]) && (cVar2 = runtime_memequal(), cVar2 != '\0')) {
        uStack_398 = puStack_170[0x10];
        uStack_138 = puStack_170[0xf];
        puVar5 = (undefined8 *)runtime_mapassign_faststr(0xd,uStack_398,uStack_138,&DAT_01c49a06);
        puVar5[1] = uStack_398;
        if (DAT_02e5e450 != 0) {
          auVar20 = runtime_gcWriteBarrier2();
          puVar5 = auVar20._0_8_;
          *puVar3 = uStack_138;
          puVar3[1] = auVar20._8_8_;
        }
        *puVar5 = uStack_138;
      }
      lVar4 = lStack_4a0;
      if (plStack_220 == (long *)0x0) {
        lVar8 = 0;
      }
      else {
        lVar8 = *plStack_220;
      }
      puVar14 = puStack_480;
      puVar5 = puStack_1f8;
      if (lVar8 < 1) {
        uVar10 = uVar10 & 0xff;
        puVar9 = puStack_440;
        puVar3 = puStack_460;
      }
      else {
        puVar3 = (undefined8 *)(lStack_4a0 + 1);
        if (puStack_480 < puVar3) {
          if ((((long)puVar3 < 5) && ((char)uVar10 == '\0')) && (lStack_4a0 == 0)) {
            uStack_108 = in_XMM15_Qa;
            uStack_100 = in_XMM15_Qb;
            uStack_f8 = in_XMM15_Qa;
            uStack_f0 = in_XMM15_Qb;
            puVar5 = &uStack_108;
            puVar14 = (undefined8 *)&DAT_00000004;
            uVar10 = 1;
          }
          else {
            puVar5 = (undefined8 *)runtime_growslice(1,&DAT_01a23240);
            uVar10 = uVar10 & 0xff;
          }
        }
        else {
          uVar10 = uVar10 & 0xff;
        }
        auVar18._8_8_ = puVar3;
        auVar18._0_8_ = plStack_220;
        puVar9 = puStack_170;
        if (DAT_02e5e450 != 0) {
          puVar3 = (undefined8 *)puVar5[lVar4];
          puVar13 = puVar3;
          auVar18 = runtime_gcWriteBarrier2();
          *puVar13 = auVar18._0_8_;
          puVar13[1] = puVar3;
        }
        lVar4 = auVar18._8_8_;
        puVar5[lVar4 + -1] = auVar18._0_8_;
        puVar3 = (undefined8 *)((long)puStack_460 + 1);
        uVar11 = *puVar9;
        puVar6 = puStack_1d8;
        puVar9 = puStack_440;
        if (puStack_440 < puVar3) {
          puStack_3c0 = puVar14;
          lStack_3b8 = lVar4;
          uStack_3b0 = uVar11;
          puStack_148 = puVar5;
          if (((4 < (long)puVar3) || (bVar1)) || (puStack_460 != (undefined8 *)0x0)) {
            puVar6 = (undefined1 *)runtime_growslice(1,&DAT_0194e420);
            uVar10 = uVar10 & 0xff;
            lVar4 = lStack_3b8;
            puVar5 = puStack_148;
            puVar14 = puStack_3c0;
            uVar11 = uStack_3b0;
          }
          else {
            bVar1 = true;
            puVar6 = auStack_360;
            puVar9 = (undefined8 *)&DAT_00000004;
          }
        }
        *(undefined8 *)(puVar6 + (long)puVar3 * 8 + -8) = uVar11;
        puStack_1d8 = puVar6;
      }
      param_1 = puStack_390 + 1;
    }
    if (lVar4 != 0) {
      lVar12 = 10;
      lVar7 = kiro2api_internal_gate_DecryptBatch();
      if (puVar5 == (undefined8 *)0x0) {
        lVar4 = DAT_02c67718;
        if (0 < lVar12) {
          lVar4 = lVar12 * 1000000000;
        }
        puVar5 = (undefined8 *)0x0;
        lStack_248 = lVar7;
        while ((long)puVar5 < lVar8) {
          uVar11 = *(undefined8 *)(lStack_248 + (long)puVar5 * 8);
          lVar7 = lVar4;
          puStack_420 = puVar5;
          if (0 < lVar4) {
            uStack_198 = uVar11;
            lVar7 = math_rand_Int63n(uVar11,puVar5,
                                 SUB168(SEXT816(-0x3333333333333333) * SEXT816(lVar4),8),lVar4);
            lVar7 = lVar7 + (lVar4 - (SUB168(SEXT816(-0x3333333333333333) * SEXT816(lVar4),8) +
                                      lVar4 >> 3));
            uVar11 = uStack_198;
          }
          if (puStack_460 <= puStack_420) {
                    /* WARNING: Subroutine does not return */
            runtime_panicIndex();
          }
          kiro2api_internal_gate_SetCachedCredentialsWithTTL(uVar11,lVar7,lVar7,*(undefined8 *)(puStack_1d8 + (long)puStack_420 * 8),
                       puStack_1d8,lVar4);
          puVar5 = (undefined8 *)((long)puStack_420 + 1);
        }
        uStack_278 = github_com_gogf_gf_v2_frame_gins_Log();
        lStack_10 = runtime_convT64();
        puStack_18 = &DAT_0194e460;
        param_1 = &DAT_01c87b0d;
        github_com_gogf_gf_v2_os_glog_Logger_Infof(&DAT_01c87b0d,0x31,&DAT_0194e460,uStack0000000000000010);
      }
      else {
        puStack_400 = puVar5;
        lStack_1b8 = lVar4;
        github_com_gogf_gf_v2_frame_gins_Log();
        if (puStack_400 == (undefined8 *)0x0) {
          puStack_18 = (undefined8 *)0x0;
        }
        else {
          puStack_18 = (undefined8 *)puStack_400[1];
        }
        lStack_10 = lStack_1b8;
        param_1 = &DAT_01c82f20;
        github_com_gogf_gf_v2_os_glog_Logger_Errorf(&DAT_01c82f20,0x2d,lStack_1b8,uStack0000000000000010);
      }
    }
  }
  lVar4 = kiro2api_internal_dao_OrchidsAccountDao_GetAllNormal();
  if ((param_1 == (undefined *)0x0) && (puStack0000000000000008 != (undefined8 *)0x0)) {
    puStack_4b8 = puStack0000000000000008;
    lStack_230 = lVar4;
    if (&DAT_00000004 < puStack0000000000000008) {
      puVar5 = (undefined8 *)runtime_makeslice();
    }
    else {
      puVar5 = auStack_98;
    }
    if (&DAT_00000004 < puStack_4b8) {
      puStack_200 = puVar5;
      puStack_1e0 = (undefined1 *)runtime_makeslice();
      puVar5 = puStack_200;
    }
    else {
      puStack_1e0 = auStack_300;
    }
    lVar4 = 0;
    uVar10 = 0;
    bVar1 = false;
    puVar3 = (undefined8 *)0x0;
    puVar16 = (undefined *)0x0;
    puVar14 = puStack_4b8;
    puVar9 = puStack_4b8;
    while (lVar8 = lStack_388, puStack_468 = puVar3, (long)puVar16 < (long)puStack_4b8) {
      puStack_178 = *(undefined8 **)(lStack_230 + (long)puVar16 * 8);
      lStack_4a8 = lVar4;
      puStack_488 = puVar14;
      puStack_448 = puVar9;
      puStack_390 = puVar16;
      puStack_200 = puVar5;
      plStack_228 = (long *)runtime_makemap_small();
      if ((4 < (long)puStack_178[8]) && (cVar2 = runtime_memequal(), cVar2 != '\0')) {
        uStack_398 = puStack_178[8];
        uStack_138 = puStack_178[7];
        puVar5 = (undefined8 *)runtime_mapassign_faststr(10,uStack_398,uStack_138,&DAT_01c4419d);
        puVar5[1] = uStack_398;
        if (DAT_02e5e450 != 0) {
          auVar20 = runtime_gcWriteBarrier2();
          puVar5 = auVar20._0_8_;
          *puVar3 = uStack_138;
          puVar3[1] = auVar20._8_8_;
        }
        *puVar5 = uStack_138;
      }
      if ((4 < (long)puStack_178[0x10]) && (cVar2 = runtime_memequal(), cVar2 != '\0')) {
        uStack_398 = puStack_178[0x10];
        uStack_138 = puStack_178[0xf];
        puVar5 = (undefined8 *)runtime_mapassign_faststr(8,uStack_398,uStack_138,&DAT_01c3fe7f);
        puVar5[1] = uStack_398;
        if (DAT_02e5e450 != 0) {
          auVar20 = runtime_gcWriteBarrier2();
          puVar5 = auVar20._0_8_;
          *puVar3 = uStack_138;
          puVar3[1] = auVar20._8_8_;
        }
        *puVar5 = uStack_138;
      }
      if ((4 < (long)puStack_178[0x15]) && (cVar2 = runtime_memequal(), cVar2 != '\0')) {
        uStack_398 = puStack_178[0x15];
        uStack_138 = puStack_178[0x14];
        puVar5 = (undefined8 *)runtime_mapassign_faststr(0xb,uStack_398,uStack_138,&DAT_01c46134);
        puVar5[1] = uStack_398;
        if (DAT_02e5e450 != 0) {
          auVar20 = runtime_gcWriteBarrier2();
          puVar5 = auVar20._0_8_;
          *puVar3 = uStack_138;
          puVar3[1] = auVar20._8_8_;
        }
        *puVar5 = uStack_138;
      }
      lVar4 = lStack_4a8;
      if (plStack_228 == (long *)0x0) {
        lVar8 = 0;
      }
      else {
        lVar8 = *plStack_228;
      }
      puVar14 = puStack_488;
      puVar5 = puStack_200;
      if (lVar8 < 1) {
        uVar10 = uVar10 & 0xff;
        puVar9 = puStack_448;
        puVar3 = puStack_468;
      }
      else {
        puVar3 = (undefined8 *)(lStack_4a8 + 1);
        if (puStack_488 < puVar3) {
          if ((((long)puVar3 < 5) && ((char)uVar10 == '\0')) && (lStack_4a8 == 0)) {
            uStack_128 = in_XMM15_Qa;
            uStack_120 = in_XMM15_Qb;
            uStack_118 = in_XMM15_Qa;
            uStack_110 = in_XMM15_Qb;
            puVar5 = &uStack_128;
            puVar14 = (undefined8 *)&DAT_00000004;
            uVar10 = 1;
          }
          else {
            puVar5 = (undefined8 *)runtime_growslice(1,&DAT_01a23240);
            uVar10 = uVar10 & 0xff;
          }
        }
        else {
          uVar10 = uVar10 & 0xff;
        }
        auVar17._8_8_ = puVar3;
        auVar17._0_8_ = plStack_228;
        puVar9 = puStack_178;
        if (DAT_02e5e450 != 0) {
          puVar3 = (undefined8 *)puVar5[lVar4];
          puVar13 = puVar3;
          auVar17 = runtime_gcWriteBarrier2();
          *puVar13 = auVar17._0_8_;
          puVar13[1] = puVar3;
        }
        lVar4 = auVar17._8_8_;
        puVar5[lVar4 + -1] = auVar17._0_8_;
        puVar3 = (undefined8 *)((long)puStack_468 + 1);
        uVar11 = *puVar9;
        puVar6 = puStack_1e0;
        puVar9 = puStack_448;
        if (puStack_448 < puVar3) {
          uStack_3b0 = uVar11;
          puStack_3a8 = puVar14;
          lStack_3a0 = lVar4;
          puStack_140 = puVar5;
          if (((4 < (long)puVar3) || (bVar1)) || (puStack_468 != (undefined8 *)0x0)) {
            puVar6 = (undefined1 *)runtime_growslice(1,&DAT_0194e420);
            uVar10 = uVar10 & 0xff;
            lVar4 = lStack_3a0;
            puVar5 = puStack_140;
            puVar14 = puStack_3a8;
            uVar11 = uStack_3b0;
          }
          else {
            bVar1 = true;
            puVar6 = auStack_380;
            puVar9 = (undefined8 *)&DAT_00000004;
          }
        }
        *(undefined8 *)(puVar6 + (long)puVar3 * 8 + -8) = uVar11;
        puStack_1e0 = puVar6;
      }
      puVar16 = puStack_390 + 1;
    }
    if (lVar4 != 0) {
      lVar12 = 7;
      lVar7 = kiro2api_internal_gate_DecryptBatch();
      if (puVar5 == (undefined8 *)0x0) {
        lVar4 = DAT_02c67718;
        if (0 < lVar12) {
          lVar4 = lVar12 * 1000000000;
        }
        puVar5 = (undefined8 *)0x0;
        lStack_250 = lVar7;
        while ((long)puVar5 < lVar8) {
          uVar11 = *(undefined8 *)(lStack_250 + (long)puVar5 * 8);
          lVar7 = lVar4;
          puStack_428 = puVar5;
          if (0 < lVar4) {
            uStack_1a0 = uVar11;
            lVar7 = math_rand_Int63n(uVar11,puVar5,
                                 SUB168(SEXT816(-0x3333333333333333) * SEXT816(lVar4),8),lVar4);
            lVar7 = lVar7 + (lVar4 - (SUB168(SEXT816(-0x3333333333333333) * SEXT816(lVar4),8) +
                                      lVar4 >> 3));
            uVar11 = uStack_1a0;
          }
          if (puStack_468 <= puStack_428) {
                    /* WARNING: Subroutine does not return */
            runtime_panicIndex();
          }
          kiro2api_internal_gate_SetCachedCredentialsWithTTL(uVar11,lVar7,lVar7,*(undefined8 *)(puStack_1e0 + (long)puStack_428 * 8),
                       puStack_1e0,lVar4);
          puVar5 = (undefined8 *)((long)puStack_428 + 1);
        }
        uStack_280 = github_com_gogf_gf_v2_frame_gins_Log();
        lStack_10 = runtime_convT64();
        puStack_18 = &DAT_0194e460;
        github_com_gogf_gf_v2_os_glog_Logger_Infof(&DAT_01c84060,0x2e,&DAT_0194e460,uStack0000000000000010,&puStack_18,1);
      }
      else {
        puStack_408 = puVar5;
        lStack_1c0 = lVar4;
        github_com_gogf_gf_v2_frame_gins_Log();
        if (puStack_408 == (undefined8 *)0x0) {
          puStack_18 = (undefined8 *)0x0;
        }
        else {
          puStack_18 = (undefined8 *)puStack_408[1];
        }
        lStack_10 = lStack_1c0;
        github_com_gogf_gf_v2_os_glog_Logger_Errorf(&DAT_01c7e894,0x2a,lStack_1c0,uStack0000000000000010,&puStack_18,1);
      }
    }
  }
  puStack_a8 = &DAT_0194e220;
  ppuStack_a0 = &PTR_DAT_01f39fd0;
  fmt_Fprintln(1,1,&PTR_DAT_01f39fd0,&puStack_a8);
  return;
}




// === logic.AccountQueueManager.InitializeQueue @ 0x1371e40 ===

undefined1 *
logic_AccountQueueManager_InitializeQueue
          (long *param_1,long param_2,undefined8 param_3,long param_4)

{
  long *plVar1;
  undefined **ppuVar2;
  bool bVar3;
  byte bVar4;
  long *in_RAX;
  undefined8 uVar5;
  long lVar6;
  undefined1 *puVar7;
  long *plVar8;
  char *pcVar9;
  long lVar10;
  ulong uVar11;
  ulong uVar12;
  long *plVar13;
  undefined *puVar14;
  undefined8 extraout_RDX;
  undefined8 extraout_RDX_00;
  ulong uVar15;
  long unaff_RBX;
  long lVar16;
  undefined1 *puVar17;
  long lVar18;
  long *plVar19;
  long *in_R11;
  undefined8 *puVar20;
  long unaff_R14;
  undefined8 *in_XMM15_Qa;
  undefined1 auVar21 [16];
  undefined1 auVar22 [16];
  undefined1 auVar23 [16];
  undefined1 auVar24 [16];
  long *plStack0000000000000008;
  long lStack0000000000000010;
  long lStack0000000000000018;
  long *plStack0000000000000020;
  long lStack0000000000000028;
  undefined8 uStack_3c8;
  ulong uStack_3c0;
  undefined8 uStack_3b8;
  long lStack_3b0;
  long lStack_3a8;
  long lStack_3a0;
  long lStack_398;
  long lStack_390;
  long lStack_388;
  long lStack_380;
  long lStack_378;
  long lStack_370;
  long lStack_368;
  long lStack_360;
  undefined8 uStack_358;
  long *plStack_350;
  undefined1 auStack_348 [32];
  undefined1 auStack_328 [32];
  undefined8 uStack_308;
  undefined1 auStack_300 [128];
  undefined8 uStack_280;
  undefined1 auStack_278 [128];
  long lStack_1f8;
  long lStack_1f0;
  undefined *puStack_1e8;
  long *plStack_1e0;
  long *plStack_1d8;
  undefined8 uStack_1d0;
  undefined8 uStack_1c8;
  undefined8 uStack_1c0;
  undefined1 *puStack_1b8;
  undefined8 uStack_1b0;
  undefined1 *puStack_1a8;
  undefined8 *puStack_1a0;
  undefined8 *puStack_198;
  undefined8 *puStack_190;
  long lStack_188;
  long lStack_180;
  long lStack_178;
  long lStack_170;
  long lStack_168;
  long lStack_160;
  long lStack_158;
  long lStack_150;
  long lStack_148;
  long lStack_140;
  undefined1 *puStack_138;
  undefined8 *puStack_130;
  long lStack_128;
  undefined8 *puStack_120;
  undefined1 auStack_118 [48];
  undefined8 *puStack_e8;
  undefined8 uStack_c0;
  undefined8 *puStack_b8;
  undefined8 *puStack_98;
  undefined8 uStack_90;
  undefined8 *puStack_88;
  undefined8 uStack_80;
  undefined8 *puStack_78;
  undefined8 *puStack_18;
  long *plStack_10;
  
  plStack0000000000000008 = in_RAX;
  lStack0000000000000018 = param_4;
  lStack0000000000000010 = unaff_RBX;
  lStack0000000000000028 = param_2;
  plStack0000000000000020 = param_1;
  while (&uStack_3c8 <= *(undefined8 **)(unaff_R14 + 0x10)) {
    runtime_morestack_noctxt();
  }
  if (lStack0000000000000028 < 8) {
    if (lStack0000000000000028 == 4) {
      if ((int)*plStack0000000000000020 != 0x70726177) goto LAB_01372082;
      puVar14 = (undefined *)0x1b;
      puStack_1e8 = &DAT_01c636e3;
    }
    else if (lStack0000000000000028 == 6) {
      if (((int)*plStack0000000000000020 == 0x73727563) &&
         (*(short *)((long)plStack0000000000000020 + 4) == 0x726f)) {
        puVar14 = (undefined *)0x1d;
        puStack_1e8 = &DAT_01c66d23;
      }
      else {
LAB_01372082:
        puStack_1e8 = (undefined *)runtime_concatstring3();
        puVar14 = &DAT_01c41f3c;
      }
    }
    else {
      if ((((lStack0000000000000028 != 7) || ((int)*plStack0000000000000020 != 0x6863726f)) ||
          (*(short *)((long)plStack0000000000000020 + 4) != 0x6469)) ||
         (*(char *)((long)plStack0000000000000020 + 6) != 's')) goto LAB_01372082;
      puVar14 = (undefined *)0x1e;
      puStack_1e8 = &DAT_01c68ae2;
    }
  }
  else if (lStack0000000000000028 < 10) {
    if (lStack0000000000000028 == 8) {
      if (*plStack0000000000000020 == 0x6f72703a6b6f7267) {
        puVar14 = (undefined *)0x1f;
        puStack_1e8 = &DAT_01c6a61f;
      }
      else {
        if (*plStack0000000000000020 != 0x6f72703a6f72696b) goto LAB_01372082;
        puVar14 = (undefined *)0x1f;
        puStack_1e8 = &DAT_01c6a600;
      }
    }
    else if ((*plStack0000000000000020 == 0x6572663a6b6f7267) &&
            ((char)plStack0000000000000020[1] == 'e')) {
      puVar14 = (undefined *)0x20;
      puStack_1e8 = &DAT_01c6c495;
    }
    else if ((*plStack0000000000000020 == 0x6572663a6f72696b) &&
            ((char)plStack0000000000000020[1] == 'e')) {
      puVar14 = (undefined *)0x20;
      puStack_1e8 = &DAT_01c6c455;
    }
    else {
      in_R11 = (long *)0x756c703a6f72696b;
      if ((*plStack0000000000000020 != 0x756c703a6f72696b) ||
         ((char)plStack0000000000000020[1] != 's')) goto LAB_01372082;
      puVar14 = (undefined *)0x20;
      puStack_1e8 = &DAT_01c6c475;
    }
  }
  else if (lStack0000000000000028 == 10) {
    if ((*plStack0000000000000020 == 0x615f656475616c63) &&
       ((short)plStack0000000000000020[1] == 0x6970)) {
      puVar14 = (undefined *)0x21;
      puStack_1e8 = &DAT_01c6e484;
    }
    else {
      if ((*plStack0000000000000020 != 0x746c753a6f72696b) ||
         ((short)plStack0000000000000020[1] != 0x6172)) goto LAB_01372082;
      puVar14 = (undefined *)0x21;
      puStack_1e8 = &DAT_01c6e463;
    }
  }
  else {
    if ((((lStack0000000000000028 != 0xb) || (*plStack0000000000000020 != 0x7661726769746e61)) ||
        ((short)plStack0000000000000020[1] != 0x7469)) ||
       (*(char *)((long)plStack0000000000000020 + 10) != 'y')) goto LAB_01372082;
    puVar14 = (undefined *)0x22;
    puStack_1e8 = &DAT_01c6ffdd;
  }
  puStack_190 = *(undefined8 **)(*plStack0000000000000008 + 8);
  puStack_120 = (undefined8 *)runtime_newobject();
  *puStack_120 = &DAT_0194e220;
  puStack_120[1] = &PTR_DAT_01f39f50;
  uVar5 = runtime_convTstring();
  auVar21._8_8_ = puStack_120;
  auVar21._0_8_ = uVar5;
  puStack_120[2] = &DAT_0194e220;
  if (DAT_02e5e450 != 0) {
    lVar10 = puStack_120[3];
    lVar6 = puStack_120[5];
    lVar16 = puStack_120[7];
    auVar21 = runtime_gcWriteBarrier4();
    *in_R11 = auVar21._0_8_;
    in_R11[1] = lVar10;
    in_R11[2] = lVar6;
    in_R11[3] = lVar16;
  }
  lVar10 = auVar21._8_8_;
  *(long *)(lVar10 + 0x18) = auVar21._0_8_;
  *(undefined8 **)(lVar10 + 0x20) = &DAT_0194e3e0;
  *(undefined **)(lVar10 + 0x28) = &DAT_01f385c0;
  *(undefined8 **)(lVar10 + 0x30) = &DAT_0194e3e0;
  *(undefined **)(lVar10 + 0x38) = &DAT_01f38728;
  plStack_1d8 = (long *)runtime_newobject();
  *plStack_1d8 = lStack0000000000000010;
  if (DAT_02e5e450 != 0) {
    plStack_1d8 = (long *)runtime_gcWriteBarrier2();
    *in_R11 = lStack0000000000000018;
    in_R11[1] = (long)puStack_120;
  }
  plStack_1d8[1] = lStack0000000000000018;
  plStack_1d8[3] = 4;
  plStack_1d8[4] = 4;
  plStack_1d8[2] = (long)puStack_120;
  (*(code *)*puStack_190)(plStack_1d8,(code *)*puStack_190,puStack_190,&PTR_DAT_01f60b20);
  ppuVar2 = (undefined **)plStack_1d8[5];
  lStack_1f0 = plStack_1d8[0xb];
  lVar10 = plStack_1d8[0xc];
  plStack_10 = (long *)plStack_1d8[6];
  uVar5 = extraout_RDX;
  if (ppuVar2 == (undefined **)0x0) {
    bVar4 = 0;
  }
  else if (ppuVar2 == &PTR_DAT_01f431e0) {
    lStack_1f8 = (long)plStack_10;
    bVar4 = runtime_ifaceeq();
    bVar4 = bVar4 ^ 1;
    plStack_10 = (long *)lStack_1f8;
    uVar5 = extraout_RDX_00;
  }
  else {
    bVar4 = 1;
  }
  if (bVar4 != 0) {
    puStack_18 = (undefined8 *)0x0;
    if (ppuVar2 != (undefined **)0x0) {
      puStack_18 = (undefined8 *)ppuVar2[1];
    }
    puVar17 = (undefined1 *)fmt_Errorf(1,1,uVar5,&puStack_18,puStack_18,lStack_1f0);
    return puVar17;
  }
  puVar17 = auStack_278;
  FUN_00488ce2();
  uStack_280 = 0x8080808080808080;
  puStack_b8 = &uStack_280;
  uStack_c0 = runtime_rand();
  lVar6 = lStack_1f0;
  while (lVar16 = lStack0000000000000010, 0 < lVar10) {
    lVar16 = *(long *)(lVar6 + 8);
    puVar17 = &DAT_00000040;
    plStack_350 = (long *)lVar10;
    lStack_128 = lVar6;
    strconv_ParseUint();
    if (lVar16 == 0) {
      puVar7 = (undefined1 *)runtime_mapassign_fast64();
      *puVar7 = 1;
    }
    lVar6 = lStack_128 + 0x10;
    lVar10 = (long)plStack_350 + -1;
  }
  if (lStack0000000000000028 < 8) {
    if (lStack0000000000000028 == 4) {
      if (((int)*plStack0000000000000020 == 0x6b6f7267) ||
         ((int)*plStack0000000000000020 == 0x6f72696b)) {
        return (undefined1 *)0x0;
      }
      if ((int)*plStack0000000000000020 == 0x70726177) {
        lVar10 = kiro2api_internal_dao_WarpAccountDao_GetAllNormal();
        if (puVar17 != (undefined1 *)0x0) {
          return puVar17;
        }
        lStack_398 = lVar16;
        plVar19 = (long *)0x0;
        puStack_138 = (undefined1 *)0x0;
        plVar8 = (long *)0x0;
        lStack_170 = lVar10;
        for (plVar13 = (long *)0x0; (long)plVar13 < lVar16; plVar13 = (long *)((long)plVar13 + 1)) {
          plVar8 = (long *)((long)plVar8 + 1);
          uVar5 = **(undefined8 **)(lVar10 + (long)plVar13 * 8);
          if (plVar19 < plVar8) {
            uStack_358 = uVar5;
            plStack_350 = plVar13;
            puStack_138 = (undefined1 *)runtime_growslice(1,&DAT_0194e420);
            lVar10 = lStack_170;
            plVar13 = plStack_350;
            lVar16 = lStack_398;
            uVar5 = uStack_358;
          }
          *(undefined8 *)(puStack_138 + (long)plVar8 * 8 + -8) = uVar5;
        }
        goto LAB_0137294a;
      }
    }
    else if (lStack0000000000000028 == 6) {
      if (((int)*plStack0000000000000020 == 0x73727563) &&
         (*(short *)((long)plStack0000000000000020 + 4) == 0x726f)) {
        return (undefined1 *)0x0;
      }
    }
    else if ((((lStack0000000000000028 == 7) && ((int)*plStack0000000000000020 == 0x6863726f)) &&
             (*(short *)((long)plStack0000000000000020 + 4) == 0x6469)) &&
            (*(char *)((long)plStack0000000000000020 + 6) == 's')) {
      lVar10 = kiro2api_internal_dao_OrchidsAccountDao_GetAllNormal();
      if (puVar17 != (undefined1 *)0x0) {
        return puVar17;
      }
      lStack_368 = lVar16;
      bVar3 = false;
      plVar19 = (long *)0x0;
      puStack_138 = (undefined1 *)0x0;
      plVar8 = (long *)0x0;
      lStack_140 = lVar10;
      for (plVar13 = (long *)0x0; (long)plVar13 < lVar16; plVar13 = (long *)((long)plVar13 + 1)) {
        plVar1 = (long *)((long)plVar8 + 1);
        uVar5 = **(undefined8 **)(lVar10 + (long)plVar13 * 8);
        if (plVar19 < plVar1) {
          uStack_358 = uVar5;
          plStack_350 = plVar13;
          if (((4 < (long)plVar1) || (bVar3)) || (plVar8 != (long *)0x0)) {
            puStack_138 = (undefined1 *)runtime_growslice(1,&DAT_0194e420);
            lVar10 = lStack_140;
            plVar13 = plStack_350;
            lVar16 = lStack_368;
            uVar5 = uStack_358;
          }
          else {
            puStack_138 = auStack_328;
            plVar19 = (long *)&DAT_00000004;
            bVar3 = true;
          }
        }
        *(undefined8 *)(puStack_138 + (long)plVar1 * 8 + -8) = uVar5;
        plVar8 = plVar1;
      }
      goto LAB_0137294a;
    }
LAB_01372885:
    auVar21 = runtime_convTstring();
    plStack_10 = auVar21._0_8_;
    puStack_18 = &DAT_0194e220;
    puVar17 = (undefined1 *)fmt_Errorf(1,1,auVar21._8_8_,&puStack_18);
    return puVar17;
  }
  if (lStack0000000000000028 < 10) {
    if (lStack0000000000000028 == 8) {
      if (*plStack0000000000000020 == 0x6f72703a6b6f7267) {
        lVar10 = kiro2api_internal_dao_GrokAccountDao_GetAllNormal();
        if (puVar17 != (undefined1 *)0x0) {
          return puVar17;
        }
        lStack_3b0 = lVar16;
        plVar19 = (long *)0x0;
        puStack_138 = (undefined1 *)0x0;
        plVar8 = (long *)0x0;
        lStack_188 = lVar10;
        for (plVar13 = (long *)0x0; (long)plVar13 < lVar16; plVar13 = (long *)((long)plVar13 + 1)) {
          puVar20 = *(undefined8 **)(lVar10 + (long)plVar13 * 8);
          if (((puVar20[10] == 3) && (*(short *)puVar20[9] == 0x7270)) &&
             ((char)((short *)puVar20[9])[1] == 'o')) {
            plVar8 = (long *)((long)plVar8 + 1);
            uVar5 = *puVar20;
            if (plVar19 < plVar8) {
              uStack_358 = *puVar20;
              plStack_350 = plVar13;
              puStack_138 = (undefined1 *)runtime_growslice(1,&DAT_0194e420);
              lVar10 = lStack_188;
              plVar13 = plStack_350;
              lVar16 = lStack_3b0;
              uVar5 = uStack_358;
            }
            *(undefined8 *)(puStack_138 + (long)plVar8 * 8 + -8) = uVar5;
          }
        }
      }
      else {
        if (*plStack0000000000000020 != 0x6f72703a6f72696b) goto LAB_01372885;
        lVar10 = kiro2api_internal_dao_AccountDao_GetAllNormal();
        if (puVar17 != (undefined1 *)0x0) {
          return puVar17;
        }
        lStack_378 = lVar16;
        plVar19 = (long *)0x0;
        puStack_138 = (undefined1 *)0x0;
        plVar8 = (long *)0x0;
        lStack_150 = lVar10;
        for (plVar13 = (long *)0x0; (long)plVar13 < lVar16; plVar13 = (long *)((long)plVar13 + 1)) {
          puVar20 = *(undefined8 **)(lVar10 + (long)plVar13 * 8);
          if (((puVar20[0x18] == 3) && (*(short *)puVar20[0x17] == 0x7270)) &&
             ((char)((short *)puVar20[0x17])[1] == 'o')) {
            plVar8 = (long *)((long)plVar8 + 1);
            uVar5 = *puVar20;
            if (plVar19 < plVar8) {
              uStack_358 = *puVar20;
              plStack_350 = plVar13;
              puStack_138 = (undefined1 *)runtime_growslice(1,&DAT_0194e420);
              lVar10 = lStack_150;
              plVar13 = plStack_350;
              lVar16 = lStack_378;
              uVar5 = uStack_358;
            }
            *(undefined8 *)(puStack_138 + (long)plVar8 * 8 + -8) = uVar5;
          }
        }
      }
    }
    else if ((*plStack0000000000000020 == 0x6572663a6b6f7267) &&
            ((char)plStack0000000000000020[1] == 'e')) {
      lVar10 = kiro2api_internal_dao_GrokAccountDao_GetAllNormal();
      if (puVar17 != (undefined1 *)0x0) {
        return puVar17;
      }
      lStack_3a8 = lVar16;
      plVar19 = (long *)0x0;
      puStack_138 = (undefined1 *)0x0;
      plVar8 = (long *)0x0;
      lStack_180 = lVar10;
      for (plVar13 = (long *)0x0; (long)plVar13 < lVar16; plVar13 = (long *)((long)plVar13 + 1)) {
        puVar20 = *(undefined8 **)(lVar10 + (long)plVar13 * 8);
        if ((puVar20[10] == 4) && (*(int *)puVar20[9] == 0x65657266)) {
          plVar8 = (long *)((long)plVar8 + 1);
          uVar5 = *puVar20;
          if (plVar19 < plVar8) {
            uStack_358 = *puVar20;
            plStack_350 = plVar13;
            puStack_138 = (undefined1 *)runtime_growslice(1,&DAT_0194e420);
            lVar10 = lStack_180;
            plVar13 = plStack_350;
            lVar16 = lStack_3a8;
            uVar5 = uStack_358;
          }
          *(undefined8 *)(puStack_138 + (long)plVar8 * 8 + -8) = uVar5;
        }
      }
    }
    else if ((*plStack0000000000000020 == 0x6572663a6f72696b) &&
            ((char)plStack0000000000000020[1] == 'e')) {
      lVar10 = kiro2api_internal_dao_AccountDao_GetAllNormal();
      if (puVar17 != (undefined1 *)0x0) {
        return puVar17;
      }
      lStack_370 = lVar16;
      plVar19 = (long *)0x0;
      puStack_138 = (undefined1 *)0x0;
      plVar8 = (long *)0x0;
      lStack_148 = lVar10;
      for (plVar13 = (long *)0x0; (long)plVar13 < lVar16; plVar13 = (long *)((long)plVar13 + 1)) {
        puVar20 = *(undefined8 **)(lVar10 + (long)plVar13 * 8);
        if ((puVar20[0x18] == 4) && (*(int *)puVar20[0x17] == 0x65657266)) {
          plVar8 = (long *)((long)plVar8 + 1);
          uVar5 = *puVar20;
          if (plVar19 < plVar8) {
            uStack_358 = *puVar20;
            plStack_350 = plVar13;
            puStack_138 = (undefined1 *)runtime_growslice(1,&DAT_0194e420);
            lVar10 = lStack_148;
            plVar13 = plStack_350;
            lVar16 = lStack_370;
            uVar5 = uStack_358;
          }
          *(undefined8 *)(puStack_138 + (long)plVar8 * 8 + -8) = uVar5;
        }
      }
    }
    else {
      if ((*plStack0000000000000020 != 0x756c703a6f72696b) ||
         ((char)plStack0000000000000020[1] != 's')) goto LAB_01372885;
      lVar10 = kiro2api_internal_dao_AccountDao_GetAllNormal();
      if (puVar17 != (undefined1 *)0x0) {
        return puVar17;
      }
      lStack_380 = lVar16;
      plVar19 = (long *)0x0;
      puStack_138 = (undefined1 *)0x0;
      plVar8 = (long *)0x0;
      lStack_158 = lVar10;
      for (plVar13 = (long *)0x0; (long)plVar13 < lVar16; plVar13 = (long *)((long)plVar13 + 1)) {
        puVar20 = *(undefined8 **)(lVar10 + (long)plVar13 * 8);
        if ((puVar20[0x18] == 4) && (*(int *)puVar20[0x17] == 0x73756c70)) {
          plVar8 = (long *)((long)plVar8 + 1);
          uVar5 = *puVar20;
          if (plVar19 < plVar8) {
            uStack_358 = *puVar20;
            plStack_350 = plVar13;
            puStack_138 = (undefined1 *)runtime_growslice(1,&DAT_0194e420);
            lVar10 = lStack_158;
            plVar13 = plStack_350;
            lVar16 = lStack_380;
            uVar5 = uStack_358;
          }
          *(undefined8 *)(puStack_138 + (long)plVar8 * 8 + -8) = uVar5;
        }
      }
    }
  }
  else if (lStack0000000000000028 == 10) {
    if ((*plStack0000000000000020 == 0x615f656475616c63) &&
       ((short)plStack0000000000000020[1] == 0x6970)) {
      lVar10 = kiro2api_internal_dao_ClaudeApiAccountDao_GetAllNormal();
      if (puVar17 != (undefined1 *)0x0) {
        return puVar17;
      }
      lStack_3a0 = lVar16;
      plVar19 = (long *)0x0;
      puStack_138 = (undefined1 *)0x0;
      plVar8 = (long *)0x0;
      lStack_178 = lVar10;
      for (plVar13 = (long *)0x0; (long)plVar13 < lVar16; plVar13 = (long *)((long)plVar13 + 1)) {
        plVar8 = (long *)((long)plVar8 + 1);
        uVar5 = **(undefined8 **)(lVar10 + (long)plVar13 * 8);
        if (plVar19 < plVar8) {
          uStack_358 = uVar5;
          plStack_350 = plVar13;
          puStack_138 = (undefined1 *)runtime_growslice(1,&DAT_0194e420);
          lVar10 = lStack_178;
          plVar13 = plStack_350;
          lVar16 = lStack_3a0;
          uVar5 = uStack_358;
        }
        *(undefined8 *)(puStack_138 + (long)plVar8 * 8 + -8) = uVar5;
      }
    }
    else {
      if ((*plStack0000000000000020 != 0x746c753a6f72696b) ||
         ((short)plStack0000000000000020[1] != 0x6172)) goto LAB_01372885;
      lVar10 = kiro2api_internal_dao_AccountDao_GetAllNormal();
      if (puVar17 != (undefined1 *)0x0) {
        return puVar17;
      }
      lStack_388 = lVar16;
      plVar19 = (long *)0x0;
      puStack_138 = (undefined1 *)0x0;
      plVar8 = (long *)0x0;
      lStack_160 = lVar10;
      for (plVar13 = (long *)0x0; (long)plVar13 < lVar16; plVar13 = (long *)((long)plVar13 + 1)) {
        puVar20 = *(undefined8 **)(lVar10 + (long)plVar13 * 8);
        if (((puVar20[0x18] == 5) && (*(int *)puVar20[0x17] == 0x72746c75)) &&
           ((char)((int *)puVar20[0x17])[1] == 'a')) {
          plVar8 = (long *)((long)plVar8 + 1);
          uVar5 = *puVar20;
          if (plVar19 < plVar8) {
            uStack_358 = *puVar20;
            plStack_350 = plVar13;
            puStack_138 = (undefined1 *)runtime_growslice(1,&DAT_0194e420);
            lVar10 = lStack_160;
            plVar13 = plStack_350;
            lVar16 = lStack_388;
            uVar5 = uStack_358;
          }
          *(undefined8 *)(puStack_138 + (long)plVar8 * 8 + -8) = uVar5;
        }
      }
    }
  }
  else {
    if (((lStack0000000000000028 != 0xb) || (*plStack0000000000000020 != 0x7661726769746e61)) ||
       (((short)plStack0000000000000020[1] != 0x7469 ||
        (*(char *)((long)plStack0000000000000020 + 10) != 'y')))) goto LAB_01372885;
    lVar10 = kiro2api_internal_dao_AntigravityAccountDao_GetAllNormal();
    if (puVar17 != (undefined1 *)0x0) {
      return puVar17;
    }
    lStack_390 = lVar16;
    plVar19 = (long *)0x0;
    puStack_138 = (undefined1 *)0x0;
    plVar8 = (long *)0x0;
    lStack_168 = lVar10;
    for (plVar13 = (long *)0x0; (long)plVar13 < lVar16; plVar13 = (long *)((long)plVar13 + 1)) {
      plVar8 = (long *)((long)plVar8 + 1);
      uVar5 = **(undefined8 **)(lVar10 + (long)plVar13 * 8);
      if (plVar19 < plVar8) {
        uStack_358 = uVar5;
        plStack_350 = plVar13;
        puStack_138 = (undefined1 *)runtime_growslice(1,&DAT_0194e420);
        lVar10 = lStack_168;
        plVar13 = plStack_350;
        lVar16 = lStack_390;
        uVar5 = uStack_358;
      }
      *(undefined8 *)(puStack_138 + (long)plVar8 * 8 + -8) = uVar5;
    }
  }
LAB_0137294a:
  puStack_e8 = in_XMM15_Qa;
  if ((long)plVar8 < 9) {
    plVar8 = (long *)FUN_00488ce2(auStack_300);
    uStack_308 = 0x8080808080808080;
    puStack_e8 = &uStack_308;
  }
  plStack_350 = plVar8;
  uStack_1b0 = runtime_makemap();
  lVar10 = 0;
  while (lVar10 < (long)plStack_350) {
    lStack_360 = lVar10;
    puVar17 = (undefined1 *)runtime_mapassign_fast64();
    *puVar17 = 1;
    lVar10 = lStack_360 + 1;
  }
  FUN_00488ceb(&puStack_98);
  runtime_mapIterStart();
  lVar10 = 0;
  while (puStack_78 != (undefined8 *)0x0) {
    uStack_3b8 = *puStack_78;
    pcVar9 = (char *)runtime_mapaccess1_fast64();
    if (*pcVar9 == '\0') {
      puStack_198 = *(undefined8 **)(*plStack0000000000000008 + 8);
      lStack_128 = runtime_convT64();
      puStack_120 = (undefined8 *)runtime_newobject();
      *puStack_120 = &DAT_0194e220;
      puStack_120[1] = &PTR_DAT_01f39f70;
      uVar5 = runtime_convTstring();
      auVar22._8_8_ = puStack_120;
      auVar22._0_8_ = uVar5;
      puStack_120[2] = &DAT_0194e220;
      if (DAT_02e5e450 != 0) {
        lVar6 = puStack_120[3];
        lVar16 = puStack_120[5];
        lVar18 = puStack_120[7];
        auVar22 = runtime_gcWriteBarrier5();
        *in_R11 = auVar22._0_8_;
        in_R11[1] = lVar6;
        in_R11[2] = lVar16;
        in_R11[3] = lStack_128;
        in_R11[4] = lVar18;
      }
      lVar6 = auVar22._8_8_;
      *(long *)(lVar6 + 0x18) = auVar22._0_8_;
      *(undefined8 **)(lVar6 + 0x20) = &DAT_0194e3e0;
      *(undefined **)(lVar6 + 0x28) = &DAT_01f385c0;
      *(undefined8 **)(lVar6 + 0x30) = &DAT_0194e420;
      *(long *)(lVar6 + 0x38) = lStack_128;
      plVar8 = (long *)runtime_newobject();
      *plVar8 = lStack0000000000000010;
      if (DAT_02e5e450 != 0) {
        plVar8 = (long *)runtime_gcWriteBarrier2();
        *in_R11 = lStack0000000000000018;
        in_R11[1] = (long)puStack_120;
      }
      plVar8[1] = lStack0000000000000018;
      plVar8[3] = 4;
      plVar8[4] = 4;
      plVar8[2] = (long)puStack_120;
      (*(code *)*puStack_198)(plVar8);
      lVar10 = lVar10 + 1;
    }
    runtime_mapIterNext();
  }
  if (0 < lVar10) {
    uStack_1c0 = github_com_gogf_gf_v2_frame_gins_Log();
    uStack_90 = runtime_convTstring();
    puStack_98 = &DAT_0194e220;
    uStack_80 = runtime_convT64();
    puStack_88 = &DAT_0194e460;
    github_com_gogf_gf_v2_os_glog_Logger_Infof(&DAT_01c87adc);
  }
  uVar11 = 0;
  bVar3 = false;
  uVar12 = 0;
  puStack_1a8 = (undefined1 *)0x0;
  lVar10 = 0;
  while (lVar10 < (long)plStack_350) {
    uStack_3c8 = *(undefined8 *)(puStack_138 + lVar10 * 8);
    lStack_360 = lVar10;
    pcVar9 = (char *)runtime_mapaccess1_fast64();
    if (*pcVar9 == '\0') {
      uVar15 = uVar11 + 1;
      if (uVar12 < uVar15) {
        if (((4 < (long)uVar15) || (bVar3)) || (uVar11 != 0)) {
          puStack_1a8 = (undefined1 *)runtime_growslice(1,&DAT_0194e420);
        }
        else {
          uVar12 = 4;
          bVar3 = true;
          puStack_1a8 = auStack_348;
        }
      }
      *(undefined8 *)(puStack_1a8 + uVar15 * 8 + -8) = uStack_3c8;
      uVar11 = uVar15;
    }
    lVar10 = lStack_360 + 1;
  }
  plVar8 = plStack_350;
  if (uVar11 != 0) {
    if (uVar11 < 3) {
      puVar17 = auStack_118;
    }
    else {
      puVar17 = (undefined1 *)runtime_makeslice();
    }
    uVar15 = 0;
    uVar12 = uVar11;
    puStack_1b8 = puVar17;
    while ((long)uVar15 < (long)uVar12) {
      uStack_3c0 = uVar15;
      uVar5 = runtime_convT64();
      auVar24._8_8_ = uStack_3c0;
      auVar24._0_8_ = uVar5;
      if (uVar11 <= uStack_3c0) {
                    /* WARNING: Subroutine does not return */
        runtime_panicIndex();
      }
      lVar10 = uStack_3c0 * 0x10;
      puVar20 = &DAT_0194e420;
      *(undefined8 **)(puStack_1b8 + lVar10) = &DAT_0194e420;
      puVar17 = puStack_1b8;
      uVar12 = uVar11;
      if (DAT_02e5e450 != 0) {
        uVar5 = *(undefined8 *)(puStack_1b8 + lVar10 + 8);
        auVar24 = runtime_gcWriteBarrier2();
        *puVar20 = auVar24._0_8_;
        puVar20[1] = uVar5;
      }
      *(long *)(puVar17 + lVar10 + 8) = auVar24._0_8_;
      uVar15 = auVar24._8_8_ + 1;
    }
    lVar10 = github_com_redis_go-redis_v9_cmdable_RPush(puStack_1e8,puVar14,*(undefined8 *)(*plStack0000000000000008 + 8),
                          lStack0000000000000018,puVar17,uVar12);
    plVar8 = *(long **)(lVar10 + 0x30);
    if (*(long *)(lVar10 + 0x28) != 0) {
      puStack_18 = *(undefined8 **)(*(long *)(lVar10 + 0x28) + 8);
      plStack_10 = plVar8;
      puVar17 = (undefined1 *)fmt_Errorf(1,1,puStack_18,&puStack_18);
      return puVar17;
    }
    uStack_1c8 = github_com_gogf_gf_v2_frame_gins_Log();
    uStack_90 = runtime_convTstring();
    puStack_98 = &DAT_0194e220;
    uStack_80 = runtime_convT64();
    puStack_88 = &DAT_0194e460;
    github_com_gogf_gf_v2_os_glog_Logger_Infof(&DAT_01c84032,0x2e,&DAT_0194e460,lStack0000000000000018,&puStack_98,2);
  }
  puStack_1a0 = *(undefined8 **)(*plStack0000000000000008 + 8);
  puStack_130 = (undefined8 *)runtime_newobject();
  *puStack_130 = &DAT_0194e220;
  puStack_130[1] = &PTR_DAT_01f39f80;
  uVar5 = runtime_convTstring();
  auVar23._8_8_ = puStack_130;
  auVar23._0_8_ = uVar5;
  puStack_130[2] = &DAT_0194e220;
  if (DAT_02e5e450 != 0) {
    lVar10 = puStack_130[3];
    auVar23 = runtime_gcWriteBarrier2();
    *plVar8 = auVar23._0_8_;
    plVar8[1] = lVar10;
  }
  *(long *)(auVar23._8_8_ + 0x18) = auVar23._0_8_;
  plStack_1e0 = (long *)runtime_newobject();
  *plStack_1e0 = lStack0000000000000010;
  if (DAT_02e5e450 != 0) {
    plStack_1e0 = (long *)runtime_gcWriteBarrier2();
    *plVar8 = lStack0000000000000018;
    plVar8[1] = (long)puStack_130;
  }
  plStack_1e0[1] = lStack0000000000000018;
  plStack_1e0[3] = 2;
  plStack_1e0[4] = 2;
  plStack_1e0[2] = (long)puStack_130;
  (*(code *)*puStack_1a0)(plStack_1e0,(code *)*puStack_1a0,puStack_1a0,&PTR_DAT_01f60aa8);
  uStack_1d0 = github_com_gogf_gf_v2_frame_gins_Log();
  uStack_90 = runtime_convTstring();
  puStack_98 = &DAT_0194e220;
  auVar21 = runtime_convT64();
  uStack_80 = auVar21._0_8_;
  puStack_88 = &DAT_0194e3e0;
  github_com_gogf_gf_v2_os_glog_Logger_Infof(&DAT_01c7b3e6,0x28,auVar21._8_8_,lStack0000000000000018,&puStack_98,2);
  return (undefined1 *)0x0;
}




// === common.ResponseHandler.HandleResponse @ 0x137aa00 ===

undefined8 common_ResponseHandler_HandleResponse(void)

{
  undefined8 uVar1;
  long unaff_RBX;
  long unaff_R14;
  
  while (&stack0x00000000 <= *(undefined1 **)(unaff_R14 + 0x10)) {
    runtime_morestack_noctxt();
  }
  if (unaff_RBX != 0) {
    if (*(long *)(unaff_RBX + 0x10) - 200U < 100) {
      return 0;
    }
    uVar1 = kiro2api_internal_common_ResponseHandler_handleErrorResponse();
    return uVar1;
  }
  return 1;
}




// === common.handleErrorResponse @ 0x137aa80 ===

undefined8 kiro2api_internal_common_ResponseHandler_handleErrorResponse(void)

{
  char cVar1;
  long in_RAX;
  undefined8 uVar2;
  undefined8 *puVar3;
  long in_RCX;
  long lVar4;
  undefined8 extraout_RDX;
  long unaff_RBX;
  undefined8 *in_R11;
  long unaff_R14;
  undefined1 auVar5 [16];
  long lStack0000000000000008;
  long lStack0000000000000018;
  undefined8 *local_38;
  undefined8 uStack_30;
  undefined8 *local_28;
  undefined8 uStack_20;
  undefined8 *local_18;
  undefined8 uStack_10;
  
  lStack0000000000000018 = in_RCX;
  if (&uStack_10 <= *(undefined8 **)(unaff_R14 + 0x10)) {
    runtime_morestack_noctxt();
    uVar2 = kiro2api_internal_common_ResponseHandler_handleErrorResponse();
    return uVar2;
  }
  lStack0000000000000008 = in_RAX;
  uVar2 = kiro2api_internal_common_ResponseHandler_parseErrorReason();
  github_com_gogf_gf_v2_frame_gins_Log();
  uStack_30 = runtime_convT64();
  local_38 = &DAT_0194e460;
  uStack_20 = runtime_convTstring();
  local_28 = &DAT_0194e220;
  auVar5 = runtime_convT64();
  uStack_10 = auVar5._0_8_;
  local_18 = &DAT_0194e420;
  github_com_gogf_gf_v2_os_glog_Logger_Warningf(&DAT_01c9a4eb,0x46,auVar5._8_8_,*(undefined8 *)(lStack0000000000000008 + 8),&local_38
               ,3);
  if (lStack0000000000000018 < 0x192) {
    if (lStack0000000000000018 == 400) {
      if ((unaff_RBX == 0x20) && (cVar1 = runtime_memequal(), cVar1 != '\0')) {
        puVar3 = (undefined8 *)runtime_newobject();
        puVar3[1] = 0x20;
        if (DAT_02e5e450 != 0) {
          puVar3 = (undefined8 *)runtime_gcWriteBarrier1();
          *in_R11 = uVar2;
        }
        *puVar3 = uVar2;
      }
      else {
        puVar3 = (undefined8 *)runtime_newobject();
        puVar3[1] = unaff_RBX;
        if (DAT_02e5e450 != 0) {
          puVar3 = (undefined8 *)runtime_gcWriteBarrier1();
          *in_R11 = uVar2;
        }
        *puVar3 = uVar2;
      }
      return 0;
    }
    if (lStack0000000000000018 == 0x191) {
      lVar4 = *(long *)(lStack0000000000000008 + 0x10);
      *(undefined8 *)(lVar4 + 0x30) = 0;
      if (DAT_02e5e450 != 0) {
        auVar5 = runtime_gcWriteBarrier1();
        lStack0000000000000008 = auVar5._0_8_;
        *in_R11 = auVar5._8_8_;
      }
      *(undefined8 *)(lVar4 + 0x28) = 0;
      lVar4 = *(long *)(lStack0000000000000008 + 0x10);
      if (DAT_02e5e450 != 0) {
        runtime_gcWriteBarrier1();
        *in_R11 = extraout_RDX;
      }
      *(undefined8 *)(lVar4 + 0x118) = 0;
      kiro2api_internal_common_ResponseHandler_updateAccountStatus();
      return 1;
    }
  }
  else {
    if (lStack0000000000000018 == 0x192) {
      uVar2 = kiro2api_internal_common_ResponseHandler_handlePaymentRequired();
      return uVar2;
    }
    if (lStack0000000000000018 == 0x193) {
      uVar2 = kiro2api_internal_common_ResponseHandler_handleForbidden();
      return uVar2;
    }
    if (lStack0000000000000018 == 0x1ad) {
      uVar2 = kiro2api_internal_common_ResponseHandler_handleRateLimited();
      return uVar2;
    }
  }
  if (lStack0000000000000018 < 500) {
    puVar3 = (undefined8 *)runtime_newobject();
    puVar3[1] = unaff_RBX;
    if (DAT_02e5e450 != 0) {
      puVar3 = (undefined8 *)runtime_gcWriteBarrier1();
      *in_R11 = uVar2;
    }
    *puVar3 = uVar2;
    return 0;
  }
  puVar3 = (undefined8 *)runtime_newobject();
  puVar3[1] = unaff_RBX;
  if (DAT_02e5e450 != 0) {
    puVar3 = (undefined8 *)runtime_gcWriteBarrier1();
    *in_R11 = uVar2;
  }
  *puVar3 = uVar2;
  return 1;
}



