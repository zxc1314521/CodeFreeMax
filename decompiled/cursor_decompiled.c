// CodeFreeMax - CURSOR Channel Decompiled Functions
// 2 functions

// === cursor.buildCursorRequest @ 0x17f7de0 ===

/* WARNING: Removing unreachable block (ram,0x017f82e2) */

void cursor_buildCursorRequest(void)

{
  long lVar1;
  long lVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  undefined4 uVar5;
  char cVar6;
  undefined8 in_RAX;
  undefined2 *puVar7;
  long lVar8;
  long lVar9;
  undefined *puVar10;
  undefined8 uVar11;
  long lVar12;
  char *pcVar13;
  undefined8 uVar14;
  undefined4 *puVar15;
  long lVar16;
  undefined8 uVar17;
  long *plVar18;
  undefined8 extraout_RDX;
  int *piVar19;
  undefined1 *puVar20;
  undefined8 extraout_RDX_00;
  undefined8 *puVar21;
  undefined8 *unaff_RBX;
  ulong uVar22;
  undefined *puVar23;
  undefined1 *unaff_RBP;
  undefined8 uVar24;
  undefined8 uVar25;
  long lVar26;
  ulong uVar27;
  ulong uVar28;
  long lVar29;
  undefined8 *puVar30;
  undefined1 (*pauVar31) [16];
  long unaff_R14;
  bool bVar32;
  undefined8 in_XMM15_Qa;
  undefined8 in_XMM15_Qb;
  undefined1 auVar33 [16];
  undefined1 auVar34 [16];
  undefined1 auVar35 [16];
  undefined1 auVar36 [16];
  undefined1 auVar37 [16];
  undefined1 auVar38 [16];
  undefined1 auVar39 [16];
  undefined1 auVar40 [16];
  
code_r0x017f7de0:
  puVar20 = (undefined1 *)register0x00000020;
  if (*(undefined1 **)(unaff_R14 + 0x10) < (undefined1 *)((long)register0x00000020 + -0x300)) {
    *(undefined1 **)((long)register0x00000020 + -8) = unaff_RBP;
    puVar20 = (undefined1 *)((long)register0x00000020 + -0x380);
    *(undefined8 **)((long)register0x00000020 + 0x10) = unaff_RBX;
    *(undefined8 *)((long)register0x00000020 + -0x388) = 0x17f7e16;
    puVar7 = (undefined2 *)runtime_mallocgc();
    *(undefined2 **)((long)register0x00000020 + -0x58) = puVar7;
    *puVar7 = 1;
    uVar11 = *(undefined8 *)(*(long *)((long)register0x00000020 + 0x10) + 0x48);
    *(undefined8 *)((long)register0x00000020 + -0x388) = 0x17f7e38;
    lVar8 = kiro2api_internal_logic_cursor_extractSystemPrompt();
    lVar12 = *(long *)((long)register0x00000020 + 0x10);
    puVar21 = *(undefined8 **)(lVar12 + 0x10);
    lVar26 = *(long *)(lVar12 + 0x18);
    uVar22 = 0;
    lVar9 = 0;
    uVar28 = 0;
    unaff_RBP = (undefined1 *)((long)register0x00000020 + -8);
    while( true ) {
      *(long *)((long)register0x00000020 + -0x1b8) = lVar8;
      *(undefined8 *)((long)register0x00000020 + -0x2e0) = uVar11;
      *(ulong *)((long)register0x00000020 + -0x2a0) = uVar28;
      *(long *)((long)register0x00000020 + -0x168) = lVar9;
      if (lVar26 < 1) break;
      *(long *)((long)register0x00000020 + -0x218) = lVar26;
      *(undefined8 **)((long)register0x00000020 + -0x60) = puVar21;
      uVar14 = puVar21[1];
      *(undefined8 *)((long)register0x00000020 + -0x160) = *puVar21;
      *(undefined8 *)((long)register0x00000020 + -0x158) = uVar14;
      uVar14 = puVar21[3];
      *(undefined8 *)((long)register0x00000020 + -0x150) = puVar21[2];
      *(undefined8 *)((long)register0x00000020 + -0x148) = uVar14;
      uVar3 = *(undefined4 *)((long)puVar21 + 0x24);
      uVar4 = *(undefined4 *)(puVar21 + 5);
      uVar5 = *(undefined4 *)((long)puVar21 + 0x2c);
      *(undefined4 *)((long)register0x00000020 + -0x140) = *(undefined4 *)(puVar21 + 4);
      *(undefined4 *)((long)register0x00000020 + -0x13c) = uVar3;
      *(undefined4 *)((long)register0x00000020 + -0x138) = uVar4;
      *(undefined4 *)((long)register0x00000020 + -0x134) = uVar5;
      if (((*(long *)((long)register0x00000020 + -0x158) == 6) &&
          (**(int **)((long)register0x00000020 + -0x160) == 0x74737973)) &&
         ((short)(*(int **)((long)register0x00000020 + -0x160))[1] == 0x6d65)) {
        *(ulong *)((long)register0x00000020 + -0x298) = uVar22;
        *(undefined8 *)((long)register0x00000020 + -0x388) = 0x17f7f10;
        kiro2api_internal_logic_cursor_parseMessageContent();
        *(undefined1 **)((long)register0x00000020 + -0x390) = unaff_RBP;
        *(undefined8 *)((long)register0x00000020 + -0x388) = 0x17f7f2f;
        FUN_0048905a((undefined1 *)((long)register0x00000020 + -0x160),
                     (undefined1 *)((long)register0x00000020 + -0x380));
        unaff_RBP = *(undefined1 **)((long)register0x00000020 + -0x390);
        uVar14 = *(undefined8 *)((long)register0x00000020 + -0x160);
        uVar24 = *(undefined8 *)((long)register0x00000020 + -0x158);
        if (*(long *)((long)register0x00000020 + -0x2e0) == 0) {
          auVar33._8_8_ = extraout_RDX;
          auVar33._0_8_ = *(undefined8 *)((long)register0x00000020 + -0x1b8);
          uVar17 = 0;
        }
        else {
          *(undefined8 *)((long)register0x00000020 + -0x2f0) = uVar24;
          *(undefined8 *)((long)register0x00000020 + -0x210) = uVar14;
          uVar17 = *(undefined8 *)((long)register0x00000020 + -0x1b8);
          *(undefined8 *)((long)register0x00000020 + -0x388) = 0x17f7f85;
          auVar33 = runtime_concatstring2(&DAT_01f34d88,1);
          uVar24 = *(undefined8 *)((long)register0x00000020 + -0x2f0);
          uVar14 = *(undefined8 *)((long)register0x00000020 + -0x210);
        }
        uVar11 = auVar33._0_8_;
        *(undefined8 *)((long)register0x00000020 + -0x388) = 0x17f7fa5;
        lVar8 = runtime_concatstring2(uVar14,uVar24,auVar33._8_8_,uVar17);
        lVar12 = *(long *)((long)register0x00000020 + 0x10);
        puVar21 = *(undefined8 **)((long)register0x00000020 + -0x60);
        lVar26 = *(long *)((long)register0x00000020 + -0x218);
        uVar22 = *(ulong *)((long)register0x00000020 + -0x298);
        uVar28 = *(ulong *)((long)register0x00000020 + -0x2a0);
        lVar9 = *(long *)((long)register0x00000020 + -0x168);
      }
      else {
        uVar28 = uVar28 + 1;
        if (uVar22 < uVar28) {
          *(undefined8 *)((long)register0x00000020 + -0x388) = 0x17f7ffc;
          lVar9 = runtime_growslice(1,&DAT_01ad67a0);
          lVar12 = *(long *)((long)register0x00000020 + 0x10);
          puVar21 = *(undefined8 **)((long)register0x00000020 + -0x60);
          lVar26 = *(long *)((long)register0x00000020 + -0x218);
          lVar8 = *(long *)((long)register0x00000020 + -0x1b8);
          uVar11 = *(undefined8 *)((long)register0x00000020 + -0x2e0);
        }
        lVar29 = uVar28 * 0x30;
        puVar30 = (undefined8 *)(lVar29 + lVar9 + -0x30);
        if (DAT_02e5e450 != 0) {
          *(long *)((long)register0x00000020 + -0x68) = lVar9;
          *(ulong *)((long)register0x00000020 + -0x220) = uVar28;
          *(ulong *)((long)register0x00000020 + -0x228) = uVar22;
          *(undefined8 **)((long)register0x00000020 + -0x70) = puVar30;
          *(long *)((long)register0x00000020 + -0x230) = lVar29;
          *(undefined8 *)((long)register0x00000020 + -0x388) = 0x17f8086;
          runtime_wbMove();
          lVar8 = *(long *)((long)register0x00000020 + -0x1b8);
          uVar22 = *(ulong *)((long)register0x00000020 + -0x228);
          lVar12 = *(long *)((long)register0x00000020 + 0x10);
          uVar11 = *(undefined8 *)((long)register0x00000020 + -0x2e0);
          puVar21 = *(undefined8 **)((long)register0x00000020 + -0x60);
          lVar26 = *(long *)((long)register0x00000020 + -0x218);
          lVar9 = *(long *)((long)register0x00000020 + -0x68);
          uVar28 = *(ulong *)((long)register0x00000020 + -0x220);
          lVar29 = *(long *)((long)register0x00000020 + -0x230);
          puVar30 = *(undefined8 **)((long)register0x00000020 + -0x70);
        }
        lVar29 = lVar29 + lVar9;
        uVar14 = *(undefined8 *)((long)register0x00000020 + -0x158);
        *puVar30 = *(undefined8 *)((long)register0x00000020 + -0x160);
        puVar30[1] = uVar14;
        uVar14 = *(undefined8 *)((long)register0x00000020 + -0x148);
        *(undefined8 *)(lVar29 + -0x20) = *(undefined8 *)((long)register0x00000020 + -0x150);
        *(undefined8 *)(lVar29 + -0x18) = uVar14;
        uVar3 = *(undefined4 *)((long)register0x00000020 + -0x13c);
        uVar4 = *(undefined4 *)((long)register0x00000020 + -0x138);
        uVar5 = *(undefined4 *)((long)register0x00000020 + -0x134);
        *(undefined4 *)(lVar29 + -0x10) = *(undefined4 *)((long)register0x00000020 + -0x140);
        *(undefined4 *)(lVar29 + -0xc) = uVar3;
        *(undefined4 *)(lVar29 + -8) = uVar4;
        *(undefined4 *)(lVar29 + -4) = uVar5;
      }
      puVar21 = puVar21 + 6;
      lVar26 = lVar26 + -1;
    }
    uVar11 = *(undefined8 *)(lVar12 + 0x70);
    *(undefined8 *)((long)register0x00000020 + -0x388) = 0x17f811a;
    puVar10 = (undefined *)kiro2api_internal_logic_cursor_extractWorkspacePath(lVar26,puVar21,uVar11);
    puVar21 = *(undefined8 **)((long)register0x00000020 + -0x168);
    if (lVar8 == 0) {
      puVar10 = &DAT_01c44459;
    }
    *(undefined **)((long)register0x00000020 + -0x208) = puVar10;
    if (lVar8 == 0) {
      lVar8 = 10;
    }
    *(long *)((long)register0x00000020 + -0x2e8) = lVar8;
    lVar12 = 0;
    uVar22 = 0;
    uVar27 = 0;
    auVar40 = ZEXT816(0x2e5d6a0);
    puVar30 = &DAT_02e5d6a0;
    uVar28 = 0;
    do {
      *(ulong *)((long)register0x00000020 + -0x288) = uVar22;
      *(ulong *)((long)register0x00000020 + -0x290) = uVar27;
      *(long *)((long)register0x00000020 + -0xe0) = auVar40._0_8_;
      *(long *)((long)register0x00000020 + -0x260) = auVar40._8_8_;
      *(ulong *)((long)register0x00000020 + -0x268) = uVar28;
      *(undefined8 **)((long)register0x00000020 + -200) = puVar30;
      if (*(long *)((long)register0x00000020 + -0x2a0) <= lVar12) {
        *(undefined8 *)((long)register0x00000020 + -0x388) = 0x17f8f5d;
        puVar21 = (undefined8 *)runtime_newobject(uVar22,10);
        *(undefined8 **)((long)register0x00000020 + -0x10) = puVar21;
        puVar21[1] = 5;
        *puVar21 = 
        "Agentarm642.1.7SkillmacOStasksstartMacOSnanos%s_%ddiffsplansskill.jsonPATCHx-appuser_ravenbytesQuery3.0.0ROUTE%s#%d</tr>debug%s:%d*fuzz*listPOST:HEAD:IndexInputshort%s,%s=j=02=G=15-0700%dh%sdefersweeptestRtestWexecWhchanexecRschedsudogtimergscanmheaptracepanicsleepamd64gcing MB,  got= ...\n max=scav  ptr ] = (trap:init  ms, fault and  tab= tag= top=[...], fp:deny"
        ;
        puVar10 = *(undefined **)(*(long *)((long)register0x00000020 + 0x10) + 8);
        *(undefined8 *)((long)register0x00000020 + -0x388) = 0x17f8f8b;
        uVar11 = kiro2api_internal_logic_cursor_mapCursorModel();
        *(undefined **)((long)register0x00000020 + -0x280) = puVar10;
        *(undefined8 *)((long)register0x00000020 + -0xd8) = uVar11;
        *(undefined8 *)((long)register0x00000020 + -0x388) = 0x17f8fa7;
        pcVar13 = (char *)runtime_newobject();
        *(char **)((long)register0x00000020 + -0x18) = pcVar13;
        lVar12 = *(long *)((long)register0x00000020 + -0x280);
        if (lVar12 < 4) {
          cVar6 = '\0';
        }
        else {
          puVar10 = &DAT_01c398ba;
          *(undefined8 *)((long)register0x00000020 + -0x388) = 0x17f8fe5;
          cVar6 = runtime_memequal();
          lVar12 = *(long *)((long)register0x00000020 + -0x280);
          pcVar13 = *(char **)((long)register0x00000020 + -0x18);
        }
        *pcVar13 = cVar6;
        if (lVar12 < 9) {
          cVar6 = '\0';
        }
        else {
          puVar10 = &DAT_01c41ed0;
          *(undefined8 *)((long)register0x00000020 + -0x388) = 0x17f902b;
          cVar6 = runtime_memequal();
          pcVar13 = *(char **)((long)register0x00000020 + -0x18);
        }
        if ((*pcVar13 == '\0') && (cVar6 != '\0')) {
          *pcVar13 = '\x01';
        }
        *(undefined8 *)((long)register0x00000020 + -0x388) = 0x17f9055;
        puVar21 = (undefined8 *)runtime_newobject();
        *(undefined8 **)((long)register0x00000020 + -0x20) = puVar21;
        puVar23 = *(undefined **)((long)register0x00000020 + -0x280);
        if (3 < (long)puVar23) {
          puVar10 = &DAT_01c398ba;
          *(undefined8 *)((long)register0x00000020 + -0x388) = 0x17f908c;
          cVar6 = runtime_memequal();
          if (cVar6 == '\0') {
            puVar21 = *(undefined8 **)((long)register0x00000020 + -0x20);
            puVar23 = *(undefined **)((long)register0x00000020 + -0x280);
          }
          else {
            puVar23 = (undefined *)(*(long *)((long)register0x00000020 + -0x280) + -4);
            puVar21 = *(undefined8 **)((long)register0x00000020 + -0x20);
            puVar10 = puVar23;
          }
        }
        puVar21[1] = puVar23;
        if (DAT_02e5e450 == 0) {
          uVar11 = *(undefined8 *)((long)register0x00000020 + -0xd8);
        }
        else {
          uVar14 = *puVar21;
          *(undefined8 *)((long)register0x00000020 + -0x388) = 0x17f90d8;
          puVar21 = (undefined8 *)runtime_gcWriteBarrier2();
          uVar11 = *(undefined8 *)((long)register0x00000020 + -0xd8);
          *puVar30 = uVar11;
          puVar30[1] = uVar14;
        }
        *puVar21 = uVar11;
        *(undefined8 *)((long)register0x00000020 + -0x388) = 0x17f90f6;
        uVar11 = runtime_newobject();
        *(undefined8 *)((long)register0x00000020 + -0x30) = uVar11;
        *(undefined8 *)((long)register0x00000020 + -0x388) = 0x17f910a;
        auVar40 = runtime_newobject();
        puVar15 = auVar40._0_8_;
        *(undefined4 **)((long)register0x00000020 + -0x80) = puVar15;
        *puVar15 = 5;
        *(undefined8 *)(puVar15 + 1) = 0x600000007;
        *(undefined8 *)(puVar15 + 3) = 0x800000003;
        *(undefined8 *)(puVar15 + 5) = 0xa0000000f;
        *(undefined8 *)(puVar15 + 7) = 0x120000000b;
        *(undefined8 *)(puVar15 + 9) = 0x280000002a;
        *(undefined8 *)(puVar15 + 0xb) = 0x2700000026;
        puVar23 = *(undefined **)((long)register0x00000020 + -0x2e0);
        if (puVar23 == (undefined *)0x0) {
          uVar11 = 0;
          puVar23 = (undefined *)0x0;
        }
        else if ((long)puVar23 < 0x1001) {
          uVar11 = *(undefined8 *)((long)register0x00000020 + -0x1b8);
        }
        else {
          puVar23 = *(undefined **)((long)register0x00000020 + -0x1b8);
          *(undefined8 *)((long)register0x00000020 + -0x388) = 0x17f91b3;
          uVar11 = runtime_concatstring2(&DAT_01c38dc1,3,auVar40._8_8_,0x1000);
          puVar10 = puVar23;
        }
        *(undefined **)((long)register0x00000020 + -600) = puVar23;
        *(undefined8 *)((long)register0x00000020 + -0xc0) = uVar11;
        *(undefined8 *)((long)register0x00000020 + -0x388) = 0x17f91dc;
        uVar11 = github_com_google_uuid_NewString();
        *(undefined8 *)((long)register0x00000020 + -0x78) = uVar11;
        *(undefined **)((long)register0x00000020 + -0x218) = puVar10;
        *(undefined8 *)((long)register0x00000020 + -0x388) = 0x17f91f1;
        auVar40 = time_Now();
        puVar20 = auVar40._8_8_;
        lVar12 = auVar40._0_8_;
        *(long *)((long)register0x00000020 + -0x1d0) = lVar12;
        *(undefined **)((long)register0x00000020 + -0x1c8) = puVar10;
        *(undefined **)((long)register0x00000020 + -0x1c0) = puVar23;
        if (lVar12 < 0) {
          puVar20 = &DAT_dd7b17f80 + ((ulong)(lVar12 * 2) >> 0x1f);
          *(undefined1 **)((long)register0x00000020 + -0x1c8) = puVar20;
          *(ulong *)((long)register0x00000020 + -0x1d0) = (ulong)(auVar40._0_4_ & 0x3fffffff);
        }
        *(undefined8 *)((long)register0x00000020 + -0x1c0) = 0;
        uVar11 = *(undefined8 *)((long)register0x00000020 + -0x1c8);
        *(undefined8 *)((long)register0x00000020 + -0x388) = 0x17f926d;
        uVar14 = time_Time_Format(&DAT_01c5e198,0x18,puVar20,0);
        *(undefined8 *)((long)register0x00000020 + -0x88) = uVar14;
        *(undefined8 *)((long)register0x00000020 + -0x220) = uVar11;
        *(undefined8 *)((long)register0x00000020 + -0x388) = 0x17f9289;
        puVar15 = (undefined4 *)runtime_newobject();
        *(undefined4 **)((long)register0x00000020 + -0x108) = puVar15;
        *puVar15 = 2;
        *(undefined8 *)((long)register0x00000020 + -0x388) = 0x17f92a5;
        uVar11 = runtime_newobject();
        *(undefined8 *)((long)register0x00000020 + -0x110) = uVar11;
        *(undefined8 *)((long)register0x00000020 + -0x388) = 0x17f92b9;
        lVar12 = runtime_newobject();
        *(undefined8 *)(lVar12 + 0x10) = *(undefined8 *)((long)register0x00000020 + -0x290);
        *(undefined8 *)(lVar12 + 0x18) = *(undefined8 *)((long)register0x00000020 + -0x288);
        if (DAT_02e5e450 == 0) {
          uVar11 = *(undefined8 *)((long)register0x00000020 + -0xe0);
          uVar14 = *(undefined8 *)((long)register0x00000020 + -0x58);
        }
        else {
          *(undefined8 *)((long)register0x00000020 + -0x388) = 0x17f92f1;
          lVar12 = runtime_gcWriteBarrier2();
          uVar11 = *(undefined8 *)((long)register0x00000020 + -0xe0);
          *puVar30 = uVar11;
          uVar14 = *(undefined8 *)((long)register0x00000020 + -0x58);
          puVar30[1] = uVar14;
        }
        *(long *)((long)register0x00000020 + -0x180) = lVar12;
        *(undefined8 *)(lVar12 + 8) = uVar11;
        *(undefined8 *)(lVar12 + 0x38) = uVar14;
        *(undefined8 *)((long)register0x00000020 + -0x388) = 0x17f9325;
        lVar12 = runtime_newobject();
        *(undefined8 *)(lVar12 + 0x10) = *(undefined8 *)((long)register0x00000020 + -600);
        if (DAT_02e5e450 == 0) {
          lVar26 = *(long *)((long)register0x00000020 + -0x180);
          uVar11 = *(undefined8 *)((long)register0x00000020 + -0x58);
          uVar14 = *(undefined8 *)((long)register0x00000020 + -0xc0);
        }
        else {
          lVar26 = *(long *)((long)register0x00000020 + -0x180);
          uVar24 = *(undefined8 *)(lVar26 + 0x48);
          *(undefined8 *)((long)register0x00000020 + -0x388) = 0x17f9369;
          auVar40 = runtime_gcWriteBarrier5();
          lVar12 = auVar40._0_8_;
          uVar14 = *(undefined8 *)((long)register0x00000020 + -0xc0);
          *puVar30 = uVar14;
          *(undefined1 (*) [16])(puVar30 + 1) = auVar40;
          uVar11 = *(undefined8 *)((long)register0x00000020 + -0x58);
          puVar30[3] = uVar11;
          puVar30[4] = uVar24;
        }
        *(undefined8 *)(lVar12 + 8) = uVar14;
        *(long *)(lVar26 + 0x40) = lVar12;
        *(undefined8 *)(lVar26 + 0x48) = uVar11;
        *(undefined8 *)((long)register0x00000020 + -0x388) = 0x17f93a5;
        lVar12 = runtime_newobject();
        if (DAT_02e5e450 == 0) {
          lVar26 = *(long *)((long)register0x00000020 + -0x180);
          uVar11 = *(undefined8 *)((long)register0x00000020 + -0x58);
          uVar14 = *(undefined8 *)((long)register0x00000020 + -0x78);
          uVar24 = *(undefined8 *)((long)register0x00000020 + -0x20);
          uVar17 = *(undefined8 *)((long)register0x00000020 + -0x18);
        }
        else {
          lVar26 = *(long *)((long)register0x00000020 + -0x180);
          uVar14 = *(undefined8 *)(lVar26 + 0x110);
          uVar25 = *(undefined8 *)(lVar26 + 0x150);
          *(undefined8 *)((long)register0x00000020 + -0x388) = 0x17f93f7;
          auVar40 = runtime_gcWriteBarrier8();
          lVar12 = auVar40._0_8_;
          uVar24 = *(undefined8 *)((long)register0x00000020 + -0x20);
          *puVar30 = uVar24;
          uVar17 = *(undefined8 *)((long)register0x00000020 + -0x18);
          puVar30[1] = uVar17;
          *(undefined1 (*) [16])(puVar30 + 2) = auVar40;
          uVar11 = *(undefined8 *)((long)register0x00000020 + -0x58);
          puVar30[4] = uVar11;
          puVar30[5] = uVar14;
          uVar14 = *(undefined8 *)((long)register0x00000020 + -0x78);
          puVar30[6] = uVar14;
          puVar30[7] = uVar25;
        }
        *(undefined8 *)(lVar12 + 8) = uVar24;
        *(undefined8 *)(lVar12 + 0x40) = uVar17;
        *(long *)(lVar26 + 0x50) = lVar12;
        *(undefined8 *)(lVar26 + 0x110) = uVar11;
        *(undefined8 *)(lVar26 + 0x158) = *(undefined8 *)((long)register0x00000020 + -0x218);
        *(undefined8 *)(lVar26 + 0x150) = uVar14;
        *(undefined8 *)((long)register0x00000020 + -0x388) = 0x17f946b;
        lVar12 = runtime_newobject();
        *(undefined8 *)(lVar12 + 0x10) = 6;
        *(char **)(lVar12 + 8) =
             "darwin24.0.015.6.1inputsimagesoffset0.70.0system/usagev2.9.7%s[%d]ServerConfigSERVERDOMAINMETHOD%s#%d,Logger<html><head><body><hr />/traceactiondomainmethod/[^/]+PATCH:TRACE:/indexUSAGE\n-/--%sOutput-07:00000000 Valuesysmontimersefenceselectscalar, not       unused objs\n next= jobs= goid sweep  B -> % util alloc free  span= prev= list=, i =  code= addr=], sp= m->p= p->m=SCHED  curg= ctxt: min=  max= bad ts(...)\n m=nil base hangupkilledallow"
        ;
        *(undefined8 *)(lVar12 + 0x20) = 5;
        *(char **)(lVar12 + 0x18) =
             "arm642.1.7SkillmacOStasksstartMacOSnanos%s_%ddiffsplansskill.jsonPATCHx-appuser_ravenbytesQuery3.0.0ROUTE%s#%d</tr>debug%s:%d*fuzz*listPOST:HEAD:IndexInputshort%s,%s=j=02=G=15-0700%dh%sdefersweeptestRtestWexecWhchanexecRschedsudogtimergscanmheaptracepanicsleepamd64gcing MB,  got= ...\n max=scav  ptr ] = (trap:init  ms, fault and  tab= tag= top=[...], fp:deny"
        ;
        *(undefined8 *)(lVar12 + 0x30) = 6;
        *(char **)(lVar12 + 0x28) =
             "24.0.015.6.1inputsimagesoffset0.70.0system/usagev2.9.7%s[%d]ServerConfigSERVERDOMAINMETHOD%s#%d,Logger<html><head><body><hr />/traceactiondomainmethod/[^/]+PATCH:TRACE:/indexUSAGE\n-/--%sOutput-07:00000000 Valuesysmontimersefenceselectscalar, not       unused objs\n next= jobs= goid sweep  B -> % util alloc free  span= prev= list=, i =  code= addr=], sp= m->p= p->m=SCHED  curg= ctxt: min=  max= bad ts(...)\n m=nil base hangupkilledallow"
        ;
        *(undefined8 *)(lVar12 + 0x40) = 8;
        *(undefined **)(lVar12 + 0x38) = &DAT_01c40047;
        *(undefined8 *)(lVar12 + 0x50) = *(undefined8 *)((long)register0x00000020 + -0x220);
        if (DAT_02e5e450 == 0) {
          lVar26 = *(long *)((long)register0x00000020 + -0x180);
          uVar11 = *(undefined8 *)((long)register0x00000020 + -0x88);
        }
        else {
          lVar26 = *(long *)((long)register0x00000020 + -0x180);
          *(undefined8 *)((long)register0x00000020 + -0x388) = 0x17f94f2;
          auVar40 = runtime_gcWriteBarrier3();
          lVar12 = auVar40._0_8_;
          uVar11 = *(undefined8 *)((long)register0x00000020 + -0x88);
          *puVar30 = uVar11;
          *(undefined1 (*) [16])(puVar30 + 1) = auVar40;
        }
        *(undefined8 *)(lVar12 + 0x48) = uVar11;
        *(long *)(lVar26 + 0x180) = lVar12;
        *(undefined1 *)(lVar26 + 0x188) = 1;
        *(undefined8 *)(lVar26 + 0x28) = *(undefined8 *)((long)register0x00000020 + -0x268);
        *(undefined8 *)(lVar26 + 0x30) = *(undefined8 *)((long)register0x00000020 + -0x260);
        lVar9 = *(long *)((long)register0x00000020 + -0x58);
        lVar12 = lVar9 + 1;
        if (DAT_02e5e450 == 0) {
          uVar11 = *(undefined8 *)((long)register0x00000020 + -0x30);
          uVar14 = *(undefined8 *)((long)register0x00000020 + -0x108);
          lVar8 = *(long *)((long)register0x00000020 + -0x110);
          lVar29 = *(long *)((long)register0x00000020 + -0x10);
          uVar24 = *(undefined8 *)((long)register0x00000020 + -200);
          uVar17 = *(undefined8 *)((long)register0x00000020 + -0x80);
        }
        else {
          uVar11 = *(undefined8 *)(lVar26 + 0x20);
          uVar14 = *(undefined8 *)(lVar26 + 0x1e8);
          uVar17 = *(undefined8 *)(lVar26 + 0x200);
          uVar25 = *(undefined8 *)(lVar26 + 0x240);
          *(undefined8 *)((long)register0x00000020 + -0x388) = 0x17f9597;
          runtime_gcWriteBarrier8();
          uVar24 = *(undefined8 *)((long)register0x00000020 + -200);
          *puVar30 = uVar24;
          puVar30[1] = uVar11;
          puVar30[2] = extraout_RDX_00;
          puVar30[3] = uVar14;
          uVar11 = *(undefined8 *)((long)register0x00000020 + -0x30);
          puVar30[4] = uVar11;
          puVar30[5] = uVar17;
          uVar14 = *(undefined8 *)((long)register0x00000020 + -0x108);
          puVar30[6] = uVar14;
          puVar30[7] = uVar25;
          lVar9 = *(long *)(lVar26 + 0x260);
          lVar29 = *(long *)(lVar26 + 0x268);
          plVar18 = *(long **)(lVar26 + 0x278);
          lVar1 = *(long *)(lVar26 + 0x280);
          lVar2 = *(long *)(lVar26 + 0x288);
          *(undefined8 *)((long)register0x00000020 + -0x388) = 0x17f95f9;
          lVar16 = runtime_gcWriteBarrier8();
          *plVar18 = lVar12;
          plVar18[1] = lVar9;
          lVar8 = *(long *)((long)register0x00000020 + -0x110);
          plVar18[2] = lVar8;
          plVar18[3] = lVar29;
          plVar18[4] = lVar16;
          plVar18[5] = lVar1;
          lVar29 = *(long *)((long)register0x00000020 + -0x10);
          plVar18[6] = lVar29;
          plVar18[7] = lVar2;
          puVar30 = *(undefined8 **)(lVar26 + 0x198);
          *(undefined8 *)((long)register0x00000020 + -0x388) = 0x17f9637;
          auVar40 = runtime_gcWriteBarrier2();
          lVar9 = auVar40._8_8_;
          uVar17 = *(undefined8 *)((long)register0x00000020 + -0x80);
          *puVar30 = uVar17;
          puVar30[1] = auVar40._0_8_;
        }
        *(undefined8 *)(lVar26 + 0x20) = uVar24;
        *(long *)(lVar26 + 0x1e8) = lVar9;
        *(undefined8 *)(lVar26 + 0x200) = uVar11;
        *(undefined8 *)(lVar26 + 0x240) = uVar14;
        *(long *)(lVar26 + 0x260) = lVar12;
        *(long *)(lVar26 + 0x268) = lVar8;
        *(long *)(lVar26 + 0x278) = lVar9;
        *(long *)(lVar26 + 0x280) = lVar12;
        *(long *)(lVar26 + 0x288) = lVar29;
        *(undefined8 *)(lVar26 + 0x1a0) = 0xd;
        *(undefined8 *)(lVar26 + 0x1a8) = 0xd;
        *(undefined8 *)(lVar26 + 0x198) = uVar17;
        *(undefined8 *)((long)register0x00000020 + -0x388) = 0x17f96ab;
        puVar21 = (undefined8 *)runtime_newobject();
        if (DAT_02e5e450 == 0) {
          uVar11 = *(undefined8 *)((long)register0x00000020 + -0x180);
        }
        else {
          *(undefined8 *)((long)register0x00000020 + -0x388) = 0x17f96c5;
          puVar21 = (undefined8 *)runtime_gcWriteBarrier1();
          uVar11 = *(undefined8 *)((long)register0x00000020 + -0x180);
          *puVar30 = uVar11;
        }
        *(undefined8 **)((long)register0x00000020 + -0x90) = puVar21;
        *puVar21 = uVar11;
        *(undefined8 *)((long)register0x00000020 + -0x388) = 0x17f96e7;
        lVar12 = runtime_newobject();
        *(undefined ***)(lVar12 + 8) = &PTR_DAT_01f432c0;
        if (DAT_02e5e450 == 0) {
          uVar11 = *(undefined8 *)((long)register0x00000020 + -0x90);
        }
        else {
          *(undefined8 *)((long)register0x00000020 + -0x388) = 0x17f970a;
          lVar12 = runtime_gcWriteBarrier1();
          uVar11 = *(undefined8 *)((long)register0x00000020 + -0x90);
          *puVar30 = uVar11;
        }
        *(undefined8 *)(lVar12 + 0x10) = uVar11;
        return;
      }
      *(long *)((long)register0x00000020 + -0x270) = lVar12;
      *(undefined8 **)((long)register0x00000020 + -0x60) = puVar21;
      uVar11 = puVar21[1];
      *(undefined8 *)((long)register0x00000020 + -0x160) = *puVar21;
      *(undefined8 *)((long)register0x00000020 + -0x158) = uVar11;
      uVar11 = puVar21[3];
      *(undefined8 *)((long)register0x00000020 + -0x150) = puVar21[2];
      *(undefined8 *)((long)register0x00000020 + -0x148) = uVar11;
      uVar3 = *(undefined4 *)((long)puVar21 + 0x24);
      uVar4 = *(undefined4 *)(puVar21 + 5);
      uVar5 = *(undefined4 *)((long)puVar21 + 0x2c);
      *(undefined4 *)((long)register0x00000020 + -0x140) = *(undefined4 *)(puVar21 + 4);
      *(undefined4 *)((long)register0x00000020 + -0x13c) = uVar3;
      *(undefined4 *)((long)register0x00000020 + -0x138) = uVar4;
      *(undefined4 *)((long)register0x00000020 + -0x134) = uVar5;
      *(undefined8 *)((long)register0x00000020 + -0x2a8) =
           *(undefined8 *)((long)register0x00000020 + -0x158);
      *(undefined8 *)((long)register0x00000020 + -0x178) =
           *(undefined8 *)((long)register0x00000020 + -0x160);
      *(undefined8 *)((long)register0x00000020 + -0x388) = 0x17f8255;
      kiro2api_internal_logic_cursor_parseMessageContent();
      *(undefined1 **)((long)register0x00000020 + -0x390) = unaff_RBP;
      *(undefined8 *)((long)register0x00000020 + -0x388) = 0x17f826f;
      FUN_0048905a((undefined1 *)((long)register0x00000020 + -0x160));
      unaff_RBP = *(undefined1 **)((long)register0x00000020 + -0x390);
      *(undefined8 *)((long)register0x00000020 + -0x100) = in_XMM15_Qa;
      *(undefined8 *)((long)register0x00000020 + -0xf8) = in_XMM15_Qb;
      *(undefined8 *)((long)register0x00000020 + -0xf0) = in_XMM15_Qa;
      *(undefined8 *)((long)register0x00000020 + -0xe8) = in_XMM15_Qb;
      if (*(long *)((long)register0x00000020 + -0x2a8) == 4) {
        piVar19 = *(int **)((long)register0x00000020 + -0x178);
        if (((*piVar19 == 0x72657375) && (*(long *)((long)register0x00000020 + -0x270) == 0)) &&
           (lVar12 = *(long *)((long)register0x00000020 + -0x2e0), lVar12 != 0)) {
          *(undefined1 **)((long)register0x00000020 + -0x100) =
               (undefined1 *)((long)register0x00000020 + -0x100);
          uVar14 = 0;
          *(undefined8 *)((long)register0x00000020 + -0x388) = 0x17f82fe;
          uVar11 = runtime_growslice(lVar12,&DAT_0194e2a0);
          *(undefined8 *)((long)register0x00000020 + -0x218) = uVar14;
          *(long *)((long)register0x00000020 + -0x220) = lVar12;
          *(undefined8 *)((long)register0x00000020 + -0x78) = uVar11;
          *(undefined8 *)((long)register0x00000020 + -0x388) = 0x17f833a;
          runtime_memmove();
          *(undefined8 *)((long)register0x00000020 + -0xf0) =
               *(undefined8 *)((long)register0x00000020 + -0x220);
          *(undefined8 *)((long)register0x00000020 + -0xe8) =
               *(undefined8 *)((long)register0x00000020 + -0x218);
          *(undefined8 *)((long)register0x00000020 + -0xf8) =
               *(undefined8 *)((long)register0x00000020 + -0x78);
          if (*(long *)((long)register0x00000020 + -0x158) != 0) {
            if (*(undefined1 **)((long)register0x00000020 + -0x100) == (undefined1 *)0x0) {
              *(undefined1 **)((long)register0x00000020 + -0x100) =
                   (undefined1 *)((long)register0x00000020 + -0x100);
            }
            else if (*(undefined1 **)((long)register0x00000020 + -0x100) !=
                     (undefined1 *)((long)register0x00000020 + -0x100)) goto LAB_017fa12b;
            uVar28 = *(ulong *)((long)register0x00000020 + -0xe8);
            lVar12 = *(long *)((long)register0x00000020 + -0xf0);
            uVar22 = lVar12 + 2;
            lVar26 = *(long *)((long)register0x00000020 + -0xf8);
            if (uVar28 < uVar22) {
              *(long *)((long)register0x00000020 + -0x218) = lVar12;
              *(undefined8 *)((long)register0x00000020 + -0x388) = 0x17f83ef;
              lVar26 = runtime_growslice(2,&DAT_0194e2a0,uVar22,uVar28,
                                    (undefined1 *)((long)register0x00000020 + -0x100));
              lVar12 = *(long *)((long)register0x00000020 + -0x218);
            }
            *(undefined2 *)(lVar26 + lVar12) = 0xa0a;
            *(ulong *)((long)register0x00000020 + -0xf0) = uVar22;
            *(ulong *)((long)register0x00000020 + -0xe8) = uVar28;
            *(long *)((long)register0x00000020 + -0xf8) = lVar26;
          }
          piVar19 = *(int **)((long)register0x00000020 + -0x178);
        }
      }
      else {
        piVar19 = *(int **)((long)register0x00000020 + -0x178);
      }
      lVar12 = *(long *)((long)register0x00000020 + -0x158);
      lVar26 = *(long *)((long)register0x00000020 + -0x160);
      if (*(undefined1 **)((long)register0x00000020 + -0x100) == (undefined1 *)0x0) {
        *(undefined1 **)((long)register0x00000020 + -0x100) =
             (undefined1 *)((long)register0x00000020 + -0x100);
      }
      else if (*(undefined1 **)((long)register0x00000020 + -0x100) !=
               (undefined1 *)((long)register0x00000020 + -0x100)) goto LAB_017fa118;
      pauVar31 = (undefined1 (*) [16])((long)register0x00000020 + -0x100);
      uVar28 = *(ulong *)((long)register0x00000020 + -0xe8);
      uVar22 = lVar12 + *(long *)((long)register0x00000020 + -0xf0);
      uVar11 = *(undefined8 *)((long)register0x00000020 + -0xf8);
      if (uVar28 < uVar22) {
        *(long *)((long)register0x00000020 + -0x2b0) = lVar12;
        *(long *)((long)register0x00000020 + -0x188) = lVar26;
        *(long *)((long)register0x00000020 + -0x218) = *(long *)((long)register0x00000020 + -0xf0);
        *(undefined8 *)((long)register0x00000020 + -0x388) = 0x17f8516;
        uVar11 = runtime_growslice(lVar12,&DAT_0194e2a0,piVar19);
        lVar26 = *(long *)((long)register0x00000020 + -0x188);
      }
      *(undefined8 *)((long)register0x00000020 + -0x78) = uVar11;
      *(ulong *)((long)register0x00000020 + -0x218) = uVar28;
      *(ulong *)((long)register0x00000020 + -0x220) = uVar22;
      *(undefined8 *)((long)register0x00000020 + -0x388) = 0x17f8557;
      runtime_memmove();
      *(long *)((long)register0x00000020 + -0xf0) = *(long *)((long)register0x00000020 + -0x220);
      *(undefined8 *)((long)register0x00000020 + -0xe8) =
           *(undefined8 *)((long)register0x00000020 + -0x218);
      *(undefined8 *)((long)register0x00000020 + -0xf8) =
           *(undefined8 *)((long)register0x00000020 + -0x78);
      if (*(long *)((long)register0x00000020 + -0x148) != 0) {
        if (*(long *)((long)register0x00000020 + -0x220) != 0) {
          if (*(undefined1 **)((long)register0x00000020 + -0x100) == (undefined1 *)0x0) {
            *(undefined1 **)((long)register0x00000020 + -0x100) =
                 (undefined1 *)((long)register0x00000020 + -0x100);
          }
          else if (*(undefined1 **)((long)register0x00000020 + -0x100) !=
                   (undefined1 *)((long)register0x00000020 + -0x100)) goto LAB_017fa105;
          uVar28 = *(ulong *)((long)register0x00000020 + -0xe8);
          lVar12 = *(long *)((long)register0x00000020 + -0xf0);
          uVar22 = lVar12 + 2;
          lVar26 = *(long *)((long)register0x00000020 + -0xf8);
          if (uVar28 < uVar22) {
            *(long *)((long)register0x00000020 + -0x218) = lVar12;
            *(undefined8 *)((long)register0x00000020 + -0x388) = 0x17f861a;
            lVar26 = runtime_growslice(2,&DAT_0194e2a0);
            lVar12 = *(long *)((long)register0x00000020 + -0x218);
          }
          *(undefined2 *)(lVar26 + lVar12) = 0xa0a;
          *(ulong *)((long)register0x00000020 + -0xf0) = uVar22;
          *(ulong *)((long)register0x00000020 + -0xe8) = uVar28;
          *(long *)((long)register0x00000020 + -0xf8) = lVar26;
        }
        if (*(undefined1 **)((long)register0x00000020 + -0x100) == (undefined1 *)0x0) {
          *(undefined1 **)((long)register0x00000020 + -0x100) =
               (undefined1 *)((long)register0x00000020 + -0x100);
        }
        else if (*(undefined1 **)((long)register0x00000020 + -0x100) !=
                 (undefined1 *)((long)register0x00000020 + -0x100)) goto LAB_017fa0f1;
        lVar12 = *(long *)((long)register0x00000020 + -0xf0);
        uVar22 = lVar12 + 10;
        uVar28 = *(ulong *)((long)register0x00000020 + -0xe8);
        lVar26 = *(long *)((long)register0x00000020 + -0xf8);
        if (uVar28 < uVar22) {
          *(long *)((long)register0x00000020 + -0x218) = lVar12;
          *(undefined8 *)((long)register0x00000020 + -0x388) = 0x17f86b4;
          lVar26 = runtime_growslice(10,&DAT_0194e2a0);
          lVar12 = *(long *)((long)register0x00000020 + -0x218);
        }
        *(undefined8 *)(lVar26 + lVar12) = 0x6e696b6e6968743c;
        *(undefined2 *)(lVar26 + 8 + lVar12) = 0x3e67;
        *(ulong *)((long)register0x00000020 + -0xf0) = uVar22;
        *(ulong *)((long)register0x00000020 + -0xe8) = uVar28;
        *(long *)((long)register0x00000020 + -0xf8) = lVar26;
        lVar12 = *(long *)((long)register0x00000020 + -0x148);
        if (*(undefined1 **)((long)register0x00000020 + -0x100) == (undefined1 *)0x0) {
          *(undefined1 **)((long)register0x00000020 + -0x100) =
               (undefined1 *)((long)register0x00000020 + -0x100);
        }
        else if (*(undefined1 **)((long)register0x00000020 + -0x100) !=
                 (undefined1 *)((long)register0x00000020 + -0x100)) goto LAB_017fa0de;
        uVar28 = *(ulong *)((long)register0x00000020 + -0xe8);
        uVar22 = lVar12 + *(long *)((long)register0x00000020 + -0xf0);
        uVar11 = *(undefined8 *)((long)register0x00000020 + -0xf8);
        if (uVar28 < uVar22) {
          *(undefined8 *)((long)register0x00000020 + -400) =
               *(undefined8 *)((long)register0x00000020 + -0x150);
          *(long *)((long)register0x00000020 + -0x2b8) = lVar12;
          *(long *)((long)register0x00000020 + -0x218) = *(long *)((long)register0x00000020 + -0xf0)
          ;
          *(undefined8 *)((long)register0x00000020 + -0x388) = 0x17f876c;
          uVar11 = runtime_growslice(lVar12,&DAT_0194e2a0);
        }
        *(ulong *)((long)register0x00000020 + -0x218) = uVar28;
        *(ulong *)((long)register0x00000020 + -0x220) = uVar22;
        *(undefined8 *)((long)register0x00000020 + -0x78) = uVar11;
        *(undefined8 *)((long)register0x00000020 + -0x388) = 0x17f87aa;
        runtime_memmove();
        *(undefined8 *)((long)register0x00000020 + -0xf0) =
             *(undefined8 *)((long)register0x00000020 + -0x220);
        *(undefined8 *)((long)register0x00000020 + -0xe8) =
             *(undefined8 *)((long)register0x00000020 + -0x218);
        *(undefined8 *)((long)register0x00000020 + -0xf8) =
             *(undefined8 *)((long)register0x00000020 + -0x78);
        if (*(undefined1 **)((long)register0x00000020 + -0x100) == (undefined1 *)0x0) {
          *(undefined1 **)((long)register0x00000020 + -0x100) =
               (undefined1 *)((long)register0x00000020 + -0x100);
        }
        else if (*(undefined1 **)((long)register0x00000020 + -0x100) !=
                 (undefined1 *)((long)register0x00000020 + -0x100)) goto LAB_017fa0cb;
        lVar26 = *(long *)((long)register0x00000020 + -0xf0);
        uVar22 = lVar26 + 0xb;
        uVar28 = *(ulong *)((long)register0x00000020 + -0xe8);
        lVar12 = *(long *)((long)register0x00000020 + -0xf8);
        if (uVar28 < uVar22) {
          *(long *)((long)register0x00000020 + -0x218) = lVar26;
          *(undefined8 *)((long)register0x00000020 + -0x388) = 0x17f8850;
          lVar12 = runtime_growslice(0xb,&DAT_0194e2a0);
          lVar26 = *(long *)((long)register0x00000020 + -0x218);
        }
        *(undefined8 *)(lVar12 + lVar26) = 0x696b6e6968742f3c;
        *(undefined4 *)(lVar12 + 7 + lVar26) = 0x3e676e69;
        *(ulong *)((long)register0x00000020 + -0xf0) = uVar22;
        *(ulong *)((long)register0x00000020 + -0xe8) = uVar28;
        *(long *)((long)register0x00000020 + -0xf8) = lVar12;
      }
      puVar21 = *(undefined8 **)((long)register0x00000020 + -0x140);
      lVar12 = *(long *)((long)register0x00000020 + -0x138);
      while (0 < lVar12) {
        *(long *)((long)register0x00000020 + -0x218) = lVar12;
        *(undefined8 **)((long)register0x00000020 + -0x98) = puVar21;
        uVar11 = puVar21[1];
        *(undefined8 *)((long)register0x00000020 + -0x200) = *puVar21;
        *(undefined8 *)((long)register0x00000020 + -0x1f8) = uVar11;
        uVar11 = puVar21[3];
        *(undefined8 *)((long)register0x00000020 + -0x1f0) = puVar21[2];
        *(undefined8 *)((long)register0x00000020 + -0x1e8) = uVar11;
        uVar3 = *(undefined4 *)((long)puVar21 + 0x24);
        uVar4 = *(undefined4 *)(puVar21 + 5);
        uVar5 = *(undefined4 *)((long)puVar21 + 0x2c);
        *(undefined4 *)((long)register0x00000020 + -0x1e0) = *(undefined4 *)(puVar21 + 4);
        *(undefined4 *)((long)register0x00000020 + -0x1dc) = uVar3;
        *(undefined4 *)((long)register0x00000020 + -0x1d8) = uVar4;
        *(undefined4 *)((long)register0x00000020 + -0x1d4) = uVar5;
        if (*(long *)((long)register0x00000020 + -0xf0) != 0) {
          if (*(undefined1 **)((long)register0x00000020 + -0x100) == (undefined1 *)0x0) {
            *(undefined1 **)((long)register0x00000020 + -0x100) =
                 (undefined1 *)((long)register0x00000020 + -0x100);
          }
          else if (*(undefined1 **)((long)register0x00000020 + -0x100) !=
                   (undefined1 *)((long)register0x00000020 + -0x100)) goto LAB_017fa0b8;
          uVar28 = *(ulong *)((long)register0x00000020 + -0xe8);
          lVar12 = *(long *)((long)register0x00000020 + -0xf0);
          uVar22 = lVar12 + 2;
          lVar26 = *(long *)((long)register0x00000020 + -0xf8);
          if (uVar28 < uVar22) {
            *(long *)((long)register0x00000020 + -0x220) = lVar12;
            *(undefined8 *)((long)register0x00000020 + -0x388) = 0x17f97ef;
            lVar26 = runtime_growslice(2,&DAT_0194e2a0);
            lVar12 = *(long *)((long)register0x00000020 + -0x220);
          }
          *(undefined2 *)(lVar26 + lVar12) = 0xa0a;
          *(ulong *)((long)register0x00000020 + -0xf0) = uVar22;
          *(ulong *)((long)register0x00000020 + -0xe8) = uVar28;
          *(long *)((long)register0x00000020 + -0xf8) = lVar26;
        }
        *(undefined8 *)((long)register0x00000020 + -0x50) = in_XMM15_Qa;
        *(undefined8 *)((long)register0x00000020 + -0x48) = in_XMM15_Qb;
        *(undefined8 *)((long)register0x00000020 + -0x40) = in_XMM15_Qa;
        *(undefined8 *)((long)register0x00000020 + -0x38) = in_XMM15_Qb;
        *(undefined8 *)((long)register0x00000020 + -0x388) = 0x17f9857;
        uVar11 = runtime_convTstring();
        *(undefined8 **)((long)register0x00000020 + -0x50) = &DAT_0194e220;
        *(undefined8 *)((long)register0x00000020 + -0x48) = uVar11;
        *(undefined8 *)((long)register0x00000020 + -0x388) = 0x17f9885;
        auVar40 = runtime_convTstring();
        *(undefined8 **)((long)register0x00000020 + -0x40) = &DAT_0194e220;
        *(long *)((long)register0x00000020 + -0x38) = auVar40._0_8_;
        lVar12 = 2;
        *(undefined8 *)((long)register0x00000020 + -0x388) = 0x17f98bd;
        lVar26 = fmt_Sprintf(2,2,auVar40._8_8_,(undefined1 *)((long)register0x00000020 + -0x50));
        if (*(undefined1 **)((long)register0x00000020 + -0x100) == (undefined1 *)0x0) {
          *(undefined1 **)((long)register0x00000020 + -0x100) =
               (undefined1 *)((long)register0x00000020 + -0x100);
        }
        else if (*(undefined1 **)((long)register0x00000020 + -0x100) !=
                 (undefined1 *)((long)register0x00000020 + -0x100)) goto LAB_017fa0a5;
        uVar28 = *(ulong *)((long)register0x00000020 + -0xe8);
        uVar22 = *(long *)((long)register0x00000020 + -0xf0) + 0x18;
        uVar11 = *(undefined8 *)((long)register0x00000020 + -0xf8);
        if (uVar28 < uVar22) {
          *(undefined8 *)((long)register0x00000020 + -0x2c0) = 0x18;
          *(long *)((long)register0x00000020 + -0x198) = lVar26;
          *(long *)((long)register0x00000020 + -0x220) = *(long *)((long)register0x00000020 + -0xf0)
          ;
          lVar12 = 0x18;
          *(undefined8 *)((long)register0x00000020 + -0x388) = 0x17f993b;
          uVar11 = runtime_growslice(0x18,&DAT_0194e2a0);
          lVar26 = *(long *)((long)register0x00000020 + -0x198);
        }
        *(ulong *)((long)register0x00000020 + -0x220) = uVar28;
        *(ulong *)((long)register0x00000020 + -0x228) = uVar22;
        *(undefined8 *)((long)register0x00000020 + -0x78) = uVar11;
        *(undefined8 *)((long)register0x00000020 + -0x388) = 0x17f9985;
        runtime_memmove();
        *(undefined8 *)((long)register0x00000020 + -0xf0) =
             *(undefined8 *)((long)register0x00000020 + -0x228);
        *(undefined8 *)((long)register0x00000020 + -0xe8) =
             *(undefined8 *)((long)register0x00000020 + -0x220);
        *(undefined8 *)((long)register0x00000020 + -0xf8) =
             *(undefined8 *)((long)register0x00000020 + -0x78);
        if (*(long *)((long)register0x00000020 + -0x1e0) != 0) {
          lVar26 = *(long *)((long)register0x00000020 + -0x1d8);
          *(undefined8 *)((long)register0x00000020 + -0x388) = 0x17f99d6;
          lVar9 = encoding_json_Marshal();
          if (lVar12 == 0) {
            if (*(undefined1 **)((long)register0x00000020 + -0x100) == (undefined1 *)0x0) {
              *(undefined1 **)((long)register0x00000020 + -0x100) =
                   (undefined1 *)((long)register0x00000020 + -0x100);
            }
            else if (*(undefined1 **)((long)register0x00000020 + -0x100) !=
                     (undefined1 *)((long)register0x00000020 + -0x100)) goto LAB_017fa091;
            uVar28 = *(ulong *)((long)register0x00000020 + -0xe8);
            lVar12 = *(long *)((long)register0x00000020 + -0xf0);
            uVar22 = lVar12 + 1;
            lVar8 = *(long *)((long)register0x00000020 + -0xf8);
            if (uVar28 < uVar22) {
              *(long *)((long)register0x00000020 + -0x278) = lVar26;
              *(long *)((long)register0x00000020 + -0xd0) = lVar9;
              *(long *)((long)register0x00000020 + -0x220) = lVar12;
              *(undefined8 *)((long)register0x00000020 + -0x388) = 0x17f9a6d;
              lVar8 = runtime_growslice(1,&DAT_0194e2a0,lVar12,uVar28,
                                   (undefined1 *)((long)register0x00000020 + -0x100));
              lVar12 = *(long *)((long)register0x00000020 + -0x220);
              lVar9 = *(long *)((long)register0x00000020 + -0xd0);
            }
            *(undefined1 *)(lVar8 + lVar12) = 10;
            *(ulong *)((long)register0x00000020 + -0xf0) = uVar22;
            *(ulong *)((long)register0x00000020 + -0xe8) = uVar28;
            *(long *)((long)register0x00000020 + -0xf8) = lVar8;
            *(undefined8 *)((long)register0x00000020 + -0x388) = 0x17f9ab8;
            lVar26 = runtime_slicebytetostring();
            if (*(undefined1 **)((long)register0x00000020 + -0x100) == (undefined1 *)0x0) {
              *(undefined1 **)((long)register0x00000020 + -0x100) =
                   (undefined1 *)((long)register0x00000020 + -0x100);
            }
            else if (*(undefined1 **)((long)register0x00000020 + -0x100) !=
                     (undefined1 *)((long)register0x00000020 + -0x100)) goto LAB_017fa07e;
            uVar22 = *(ulong *)((long)register0x00000020 + -0xe8);
            lVar12 = *(long *)((long)register0x00000020 + -0xf0);
            uVar11 = *(undefined8 *)((long)register0x00000020 + -0xf8);
            if (uVar22 < (ulong)(lVar12 + lVar9)) {
              *(long *)((long)register0x00000020 + -0x2c8) = lVar9;
              *(long *)((long)register0x00000020 + -0x1a0) = lVar26;
              *(long *)((long)register0x00000020 + -0x220) = lVar12;
              *(undefined8 *)((long)register0x00000020 + -0x388) = 0x17f9b3e;
              uVar11 = runtime_growslice(lVar9,&DAT_0194e2a0,lVar12,uVar22,
                                    (undefined1 *)((long)register0x00000020 + -0x100));
              lVar26 = *(long *)((long)register0x00000020 + -0x1a0);
            }
            *(ulong *)((long)register0x00000020 + -0x220) = uVar22;
            *(long *)((long)register0x00000020 + -0x228) = lVar12 + lVar9;
            *(undefined8 *)((long)register0x00000020 + -0x78) = uVar11;
            *(undefined8 *)((long)register0x00000020 + -0x388) = 0x17f9b85;
            runtime_memmove();
            *(undefined8 *)((long)register0x00000020 + -0xf0) =
                 *(undefined8 *)((long)register0x00000020 + -0x228);
            *(undefined8 *)((long)register0x00000020 + -0xe8) =
                 *(undefined8 *)((long)register0x00000020 + -0x220);
            *(undefined8 *)((long)register0x00000020 + -0xf8) =
                 *(undefined8 *)((long)register0x00000020 + -0x78);
          }
        }
        puVar21 = (undefined8 *)(*(long *)((long)register0x00000020 + -0x98) + 0x30);
        lVar12 = *(long *)((long)register0x00000020 + -0x218) + -1;
      }
      puVar21 = *(undefined8 **)((long)register0x00000020 + -0x128);
      lVar12 = *(long *)((long)register0x00000020 + -0x120);
      while (0 < lVar12) {
        *(long *)((long)register0x00000020 + -0x218) = lVar12;
        *(undefined8 **)((long)register0x00000020 + -0x98) = puVar21;
        *(undefined8 *)((long)register0x00000020 + -0x160) = *puVar21;
        uVar11 = puVar21[2];
        *(undefined8 *)((long)register0x00000020 + -0x158) = puVar21[1];
        *(undefined8 *)((long)register0x00000020 + -0x150) = uVar11;
        uVar3 = *(undefined4 *)((long)puVar21 + 0x1c);
        uVar4 = *(undefined4 *)(puVar21 + 4);
        uVar5 = *(undefined4 *)((long)puVar21 + 0x24);
        *(undefined4 *)((long)register0x00000020 + -0x148) = *(undefined4 *)(puVar21 + 3);
        *(undefined4 *)((long)register0x00000020 + -0x144) = uVar3;
        *(undefined4 *)((long)register0x00000020 + -0x140) = uVar4;
        *(undefined4 *)((long)register0x00000020 + -0x13c) = uVar5;
        if (*(long *)((long)register0x00000020 + -0xf0) != 0) {
          if (*(undefined1 **)((long)register0x00000020 + -0x100) == (undefined1 *)0x0) {
            *(undefined1 **)((long)register0x00000020 + -0x100) =
                 (undefined1 *)((long)register0x00000020 + -0x100);
          }
          else if (*(undefined1 **)((long)register0x00000020 + -0x100) !=
                   (undefined1 *)((long)register0x00000020 + -0x100)) goto LAB_017fa06b;
          uVar28 = *(ulong *)((long)register0x00000020 + -0xe8);
          lVar12 = *(long *)((long)register0x00000020 + -0xf0);
          uVar22 = lVar12 + 2;
          lVar26 = *(long *)((long)register0x00000020 + -0xf8);
          if (uVar28 < uVar22) {
            *(long *)((long)register0x00000020 + -0x220) = lVar12;
            *(undefined8 *)((long)register0x00000020 + -0x388) = 0x17f9c8a;
            lVar26 = runtime_growslice(2,&DAT_0194e2a0);
            lVar12 = *(long *)((long)register0x00000020 + -0x220);
          }
          *(undefined2 *)(lVar26 + lVar12) = 0xa0a;
          *(ulong *)((long)register0x00000020 + -0xf0) = uVar22;
          *(ulong *)((long)register0x00000020 + -0xe8) = uVar28;
          *(long *)((long)register0x00000020 + -0xf8) = lVar26;
        }
        *(undefined1 *)((long)register0x00000020 + -0x319) =
             *(undefined1 *)((long)register0x00000020 + -0x140);
        *(undefined8 *)((long)register0x00000020 + -0x50) = in_XMM15_Qa;
        *(undefined8 *)((long)register0x00000020 + -0x48) = in_XMM15_Qb;
        *(undefined8 *)((long)register0x00000020 + -0x40) = in_XMM15_Qa;
        *(undefined8 *)((long)register0x00000020 + -0x38) = in_XMM15_Qb;
        *(undefined8 *)((long)register0x00000020 + -0x388) = 0x17f9cfe;
        uVar11 = runtime_convTstring();
        *(undefined8 **)((long)register0x00000020 + -0x50) = &DAT_0194e220;
        *(undefined8 *)((long)register0x00000020 + -0x48) = uVar11;
        *(undefined8 *)((long)register0x00000020 + -0x388) = 0x17f9d45;
        auVar40 = runtime_convTstring();
        *(undefined8 **)((long)register0x00000020 + -0x40) = &DAT_0194e220;
        *(long *)((long)register0x00000020 + -0x38) = auVar40._0_8_;
        *(undefined8 *)((long)register0x00000020 + -0x388) = 0x17f9d7d;
        lVar26 = fmt_Sprintf(2,2,auVar40._8_8_,(undefined1 *)((long)register0x00000020 + -0x50));
        if (*(undefined1 **)((long)register0x00000020 + -0x100) == (undefined1 *)0x0) {
          *(undefined1 **)((long)register0x00000020 + -0x100) =
               (undefined1 *)((long)register0x00000020 + -0x100);
        }
        else if (*(undefined1 **)((long)register0x00000020 + -0x100) !=
                 (undefined1 *)((long)register0x00000020 + -0x100)) goto LAB_017fa058;
        uVar28 = *(ulong *)((long)register0x00000020 + -0xe8);
        uVar22 = *(long *)((long)register0x00000020 + -0xf0) + 0x22;
        uVar11 = *(undefined8 *)((long)register0x00000020 + -0xf8);
        if (uVar28 < uVar22) {
          *(undefined8 *)((long)register0x00000020 + -0x2d0) = 0x22;
          *(long *)((long)register0x00000020 + -0x1a8) = lVar26;
          *(long *)((long)register0x00000020 + -0x220) = *(long *)((long)register0x00000020 + -0xf0)
          ;
          *(undefined8 *)((long)register0x00000020 + -0x388) = 0x17f9dfb;
          uVar11 = runtime_growslice(0x22,&DAT_0194e2a0);
          lVar26 = *(long *)((long)register0x00000020 + -0x1a8);
        }
        *(ulong *)((long)register0x00000020 + -0x220) = uVar28;
        *(ulong *)((long)register0x00000020 + -0x228) = uVar22;
        *(undefined8 *)((long)register0x00000020 + -0x78) = uVar11;
        *(undefined8 *)((long)register0x00000020 + -0x388) = 0x17f9e45;
        runtime_memmove();
        *(undefined8 *)((long)register0x00000020 + -0xf0) =
             *(undefined8 *)((long)register0x00000020 + -0x228);
        *(undefined8 *)((long)register0x00000020 + -0xe8) =
             *(undefined8 *)((long)register0x00000020 + -0x220);
        *(undefined8 *)((long)register0x00000020 + -0xf8) =
             *(undefined8 *)((long)register0x00000020 + -0x78);
        if (*(long *)((long)register0x00000020 + -0x148) != 0) {
          if (*(undefined1 **)((long)register0x00000020 + -0x100) == (undefined1 *)0x0) {
            *(undefined1 **)((long)register0x00000020 + -0x100) =
                 (undefined1 *)((long)register0x00000020 + -0x100);
          }
          else if (*(undefined1 **)((long)register0x00000020 + -0x100) !=
                   (undefined1 *)((long)register0x00000020 + -0x100)) goto LAB_017fa045;
          uVar28 = *(ulong *)((long)register0x00000020 + -0xe8);
          lVar12 = *(long *)((long)register0x00000020 + -0xf0);
          uVar22 = lVar12 + 1;
          lVar26 = *(long *)((long)register0x00000020 + -0xf8);
          if (uVar28 < uVar22) {
            *(long *)((long)register0x00000020 + -0x220) = lVar12;
            *(undefined8 *)((long)register0x00000020 + -0x388) = 0x17f9f05;
            lVar26 = runtime_growslice(1,&DAT_0194e2a0);
            lVar12 = *(long *)((long)register0x00000020 + -0x220);
          }
          *(undefined1 *)(lVar26 + lVar12) = 10;
          *(ulong *)((long)register0x00000020 + -0xf0) = uVar22;
          *(ulong *)((long)register0x00000020 + -0xe8) = uVar28;
          *(long *)((long)register0x00000020 + -0xf8) = lVar26;
          lVar12 = *(long *)((long)register0x00000020 + -0x148);
          lVar26 = *(long *)((long)register0x00000020 + -0x150);
          if (*(undefined1 **)((long)register0x00000020 + -0x100) == (undefined1 *)0x0) {
            *(undefined1 **)((long)register0x00000020 + -0x100) =
                 (undefined1 *)((long)register0x00000020 + -0x100);
          }
          else if (*(undefined1 **)((long)register0x00000020 + -0x100) !=
                   (undefined1 *)((long)register0x00000020 + -0x100)) goto LAB_017fa02f;
          uVar28 = *(ulong *)((long)register0x00000020 + -0xe8);
          uVar22 = lVar12 + *(long *)((long)register0x00000020 + -0xf0);
          uVar11 = *(undefined8 *)((long)register0x00000020 + -0xf8);
          if (uVar28 < uVar22) {
            *(long *)((long)register0x00000020 + -0x1b0) = lVar26;
            *(long *)((long)register0x00000020 + -0x2d8) = lVar12;
            *(long *)((long)register0x00000020 + -0x220) =
                 *(long *)((long)register0x00000020 + -0xf0);
            *(undefined8 *)((long)register0x00000020 + -0x388) = 0x17f9fac;
            uVar11 = runtime_growslice(lVar12,&DAT_0194e2a0);
            lVar26 = *(long *)((long)register0x00000020 + -0x1b0);
          }
          *(ulong *)((long)register0x00000020 + -0x220) = uVar28;
          *(ulong *)((long)register0x00000020 + -0x228) = uVar22;
          *(undefined8 *)((long)register0x00000020 + -0x78) = uVar11;
          *(undefined8 *)((long)register0x00000020 + -0x388) = 0x17f9fea;
          runtime_memmove();
          *(undefined8 *)((long)register0x00000020 + -0xf0) =
               *(undefined8 *)((long)register0x00000020 + -0x228);
          *(undefined8 *)((long)register0x00000020 + -0xe8) =
               *(undefined8 *)((long)register0x00000020 + -0x220);
          *(undefined8 *)((long)register0x00000020 + -0xf8) =
               *(undefined8 *)((long)register0x00000020 + -0x78);
        }
        puVar21 = (undefined8 *)(*(long *)((long)register0x00000020 + -0x98) + 0x28);
        lVar12 = *(long *)((long)register0x00000020 + -0x218) + -1;
      }
      lVar12 = *(long *)((long)register0x00000020 + -0xf8);
      if ((ulong)-lVar12 < *(ulong *)((long)register0x00000020 + -0xf0)) goto LAB_017fa020;
      *(ulong *)((long)register0x00000020 + -0x2f8) = *(ulong *)((long)register0x00000020 + -0xf0);
      *(long *)((long)register0x00000020 + -0x78) = lVar12;
      *(undefined8 *)((long)register0x00000020 + -0x388) = 0x17f88fe;
      uVar11 = github_com_google_uuid_NewString();
      *(undefined8 *)((long)register0x00000020 + -0x88) = uVar11;
      *(long *)((long)register0x00000020 + -0x218) = lVar26;
      *(undefined8 *)((long)register0x00000020 + -0x388) = 0x17f891a;
      lVar26 = runtime_newobject();
      lVar12 = *(long *)((long)register0x00000020 + -0x2f8);
      bVar32 = lVar12 == 0;
      auVar34._8_8_ = 1;
      auVar34._0_8_ = lVar26;
      if (bVar32) {
        lVar12 = 1;
      }
      *(long *)(lVar26 + 0x10) = lVar12;
      puVar10 = *(undefined **)((long)register0x00000020 + -0x78);
      if (bVar32) {
        puVar10 = &DAT_01f34ef0;
      }
      if (DAT_02e5e450 == 0) {
        uVar11 = *(undefined8 *)((long)register0x00000020 + -0x88);
        lVar26 = *(long *)((long)register0x00000020 + -0x2a8);
        lVar12 = *(long *)((long)register0x00000020 + -0x2a8);
      }
      else {
        *(undefined8 *)((long)register0x00000020 + -0x388) = 0x17f8971;
        auVar34 = runtime_gcWriteBarrier2();
        *(undefined **)*pauVar31 = puVar10;
        uVar11 = *(undefined8 *)((long)register0x00000020 + -0x88);
        *(undefined8 *)(*pauVar31 + 8) = uVar11;
        lVar26 = *(long *)((long)register0x00000020 + -0x2a8);
        lVar12 = lVar26;
      }
      lVar9 = auVar34._0_8_;
      *(long *)((long)register0x00000020 + -0xb8) = lVar9;
      *(undefined **)(lVar9 + 8) = puVar10;
      *(undefined8 *)(lVar9 + 0x118) = *(undefined8 *)((long)register0x00000020 + -0x218);
      *(undefined8 *)(lVar9 + 0x110) = uVar11;
      if (lVar12 == 4) {
        plVar18 = *(long **)((long)register0x00000020 + -0x178);
        if ((int)*plVar18 == 0x72657375) {
          lVar12 = *(long *)((long)register0x00000020 + -0x270);
          if (lVar12 == 0) {
            *(undefined8 *)((long)register0x00000020 + -0x388) = 0x17f89e5;
            lVar12 = runtime_newobject();
            *(undefined8 *)(lVar12 + 8) = *(undefined8 *)((long)register0x00000020 + -0x2e8);
            if (DAT_02e5e450 == 0) {
              auVar35._8_8_ = *(undefined8 *)((long)register0x00000020 + -0xb8);
              auVar35._0_8_ = lVar12;
              uVar11 = *(undefined8 *)((long)register0x00000020 + -0x208);
            }
            else {
              uVar14 = *(undefined8 *)(*(long *)((long)register0x00000020 + -0xb8) + 0xe0);
              *(undefined8 *)((long)register0x00000020 + -0x388) = 0x17f8a25;
              auVar35 = runtime_gcWriteBarrier3();
              uVar11 = *(undefined8 *)((long)register0x00000020 + -0x208);
              *(undefined8 *)*pauVar31 = uVar11;
              *(long *)(*pauVar31 + 8) = auVar35._0_8_;
              *(undefined8 *)pauVar31[1] = uVar14;
            }
            lVar12 = auVar35._8_8_;
            *auVar35._0_8_ = uVar11;
            *(undefined8 *)(lVar12 + 0xe8) = 1;
            *(undefined8 *)(lVar12 + 0xf0) = 1;
            *(undefined8 **)(lVar12 + 0xe0) = auVar35._0_8_;
            plVar18 = *(long **)((long)register0x00000020 + -0x178);
            auVar34._8_8_ = 1;
            auVar34._0_8_ = lVar12;
            lVar12 = *(long *)((long)register0x00000020 + -0x270);
            lVar26 = *(long *)((long)register0x00000020 + -0x2a8);
          }
        }
        else {
          lVar12 = *(long *)((long)register0x00000020 + -0x270);
        }
      }
      else {
        plVar18 = *(long **)((long)register0x00000020 + -0x178);
        lVar12 = *(long *)((long)register0x00000020 + -0x270);
      }
      if (((lVar26 == 9) && (*plVar18 == 0x6e61747369737361)) && ((char)plVar18[1] == 't')) {
        *(undefined4 *)(auVar34._0_8_ + 0x18) = 2;
        *(undefined8 *)((long)register0x00000020 + -0x388) = 0x17f8ada;
        uVar11 = runtime_newobject(0x6e61747369737361,lVar12,auVar34._8_8_);
        *(undefined8 *)((long)register0x00000020 + -0x28) = uVar11;
        *(undefined8 *)((long)register0x00000020 + -0x388) = 0x17f8ae7;
        uVar11 = github_com_google_uuid_NewString();
        puVar21 = *(undefined8 **)((long)register0x00000020 + -0x28);
        puVar21[1] = &DAT_01f34ef0;
        if (DAT_02e5e450 != 0) {
          *(undefined8 *)((long)register0x00000020 + -0x388) = 0x17f8b05;
          auVar40 = runtime_gcWriteBarrier2();
          uVar11 = auVar40._0_8_;
          *pauVar31 = auVar40;
        }
        *puVar21 = uVar11;
        *(undefined8 *)((long)register0x00000020 + -0x388) = 0x17f8b14;
        uVar11 = github_com_google_uuid_NewString();
        *(undefined **)((long)register0x00000020 + -0x218) = &DAT_01f34ef0;
        *(undefined8 *)((long)register0x00000020 + -0x78) = uVar11;
        *(undefined8 *)((long)register0x00000020 + -0x388) = 0x17f8b30;
        lVar12 = runtime_newobject();
        *(undefined4 *)(lVar12 + 0x18) = 2;
        *(undefined8 *)(lVar12 + 0x118) = *(undefined8 *)((long)register0x00000020 + -0x218);
        if (DAT_02e5e450 == 0) {
          uVar11 = *(undefined8 *)((long)register0x00000020 + -0x78);
          uVar14 = *(undefined8 *)((long)register0x00000020 + -0x28);
        }
        else {
          *(undefined8 *)((long)register0x00000020 + -0x388) = 0x17f8b67;
          lVar12 = runtime_gcWriteBarrier2();
          uVar11 = *(undefined8 *)((long)register0x00000020 + -0x78);
          *(undefined8 *)*pauVar31 = uVar11;
          uVar14 = *(undefined8 *)((long)register0x00000020 + -0x28);
          *(undefined8 *)(*pauVar31 + 8) = uVar14;
        }
        *(long *)((long)register0x00000020 + -0x170) = lVar12;
        *(undefined8 *)(lVar12 + 0x110) = uVar11;
        *(undefined8 *)(lVar12 + 0x120) = uVar14;
        *(undefined8 *)((long)register0x00000020 + -0x388) = 0x17f8ba5;
        lVar12 = runtime_newobject();
        *(undefined8 *)(lVar12 + 0x10) = 4;
        *(undefined8 **)(lVar12 + 8) = &DAT_01c397b2;
        *(undefined8 *)(lVar12 + 0x20) = 9;
        *(undefined **)(lVar12 + 0x18) = &DAT_01c41efd;
        if (DAT_02e5e450 == 0) {
          lVar26 = *(long *)((long)register0x00000020 + -0x170);
        }
        else {
          lVar26 = *(long *)((long)register0x00000020 + -0x170);
          *(undefined8 *)((long)register0x00000020 + -0x388) = 0x17f8bf2;
          auVar40 = runtime_gcWriteBarrier2();
          lVar12 = auVar40._0_8_;
          *pauVar31 = auVar40;
        }
        *(long *)(lVar26 + 0x370) = lVar12;
        *(undefined8 *)((long)register0x00000020 + -0x388) = 0x17f8c0c;
        lVar12 = runtime_newobject();
        *(undefined4 *)(lVar12 + 0x20) = 2;
        lVar26 = *(long *)((long)register0x00000020 + -0x170);
        uVar11 = *(undefined8 *)(lVar26 + 0x110);
        *(undefined8 *)(lVar12 + 0x10) = *(undefined8 *)(lVar26 + 0x118);
        if (DAT_02e5e450 != 0) {
          *(undefined8 *)((long)register0x00000020 + -0x388) = 0x17f8c3b;
          lVar12 = runtime_gcWriteBarrier1();
          *(undefined8 *)*pauVar31 = uVar11;
        }
        *(undefined8 *)(lVar12 + 8) = uVar11;
        auVar36._8_8_ = *(undefined8 *)(lVar26 + 0x120);
        auVar36._0_8_ = lVar12;
        if (DAT_02e5e450 != 0) {
          *(undefined8 *)((long)register0x00000020 + -0x388) = 0x17f8c57;
          auVar36 = runtime_gcWriteBarrier1();
          *(long *)*pauVar31 = auVar36._8_8_;
        }
        lVar9 = auVar36._0_8_;
        *(long *)(lVar9 + 0x18) = auVar36._8_8_;
        uVar22 = *(long *)((long)register0x00000020 + -0x268) + 1;
        uVar28 = *(ulong *)((long)register0x00000020 + -0x260);
        if (uVar28 < uVar22) {
          *(long *)((long)register0x00000020 + -0xa0) = lVar9;
          *(undefined8 *)((long)register0x00000020 + -0x388) = 0x17f8ca6;
          lVar12 = runtime_growslice(1,&DAT_01b241a0);
          lVar9 = *(long *)((long)register0x00000020 + -0xa0);
          lVar26 = *(long *)((long)register0x00000020 + -0x170);
        }
        else {
          lVar12 = *(long *)((long)register0x00000020 + -200);
        }
        auVar37._8_8_ = uVar28;
        auVar37._0_8_ = lVar9;
        if (DAT_02e5e450 != 0) {
          uVar11 = *(undefined8 *)(lVar12 + -8 + uVar22 * 8);
          *(undefined8 *)((long)register0x00000020 + -0x388) = 0x17f8ccf;
          auVar37 = runtime_gcWriteBarrier2();
          *(long *)*pauVar31 = auVar37._0_8_;
          *(undefined8 *)(*pauVar31 + 8) = uVar11;
        }
        uVar11 = auVar37._8_8_;
        *(long *)(lVar12 + -8 + uVar22 * 8) = auVar37._0_8_;
        uVar27 = *(long *)((long)register0x00000020 + -0x290) + 1;
        uVar28 = *(ulong *)((long)register0x00000020 + -0x288);
        if (uVar28 < uVar27) {
          *(long *)((long)register0x00000020 + -0xa8) = lVar12;
          *(ulong *)((long)register0x00000020 + -0x238) = uVar22;
          *(undefined8 *)((long)register0x00000020 + -0x240) = uVar11;
          *(undefined8 *)((long)register0x00000020 + -0x388) = 0x17f8d34;
          lVar9 = runtime_growslice(1,&DAT_01c05960);
          uVar11 = *(undefined8 *)((long)register0x00000020 + -0x240);
          lVar12 = *(long *)((long)register0x00000020 + -0xa8);
          lVar26 = *(long *)((long)register0x00000020 + -0x170);
          uVar22 = *(ulong *)((long)register0x00000020 + -0x238);
        }
        else {
          lVar9 = *(long *)((long)register0x00000020 + -0xe0);
        }
        auVar38._8_8_ = uVar11;
        auVar38._0_8_ = lVar9;
        if (DAT_02e5e450 != 0) {
          uVar11 = *(undefined8 *)(lVar9 + -8 + uVar27 * 8);
          *(undefined8 *)((long)register0x00000020 + -0x388) = 0x17f8d6d;
          auVar38 = runtime_gcWriteBarrier2();
          *(long *)*pauVar31 = lVar26;
          *(undefined8 *)(*pauVar31 + 8) = uVar11;
        }
        *(long *)(auVar38._0_8_ + -8 + uVar27 * 8) = lVar26;
      }
      else {
        *(undefined4 *)(auVar34._0_8_ + 0x18) = 1;
        lVar12 = *(long *)((long)register0x00000020 + -200);
        uVar22 = *(ulong *)((long)register0x00000020 + -0x268);
        uVar28 = *(ulong *)((long)register0x00000020 + -0x288);
        auVar38._8_8_ = *(undefined8 *)((long)register0x00000020 + -0x260);
        auVar38._0_8_ = *(undefined8 *)((long)register0x00000020 + -0xe0);
        uVar27 = *(ulong *)((long)register0x00000020 + -0x290);
      }
      *(long *)((long)register0x00000020 + -200) = lVar12;
      *(ulong *)((long)register0x00000020 + -0x290) = uVar27;
      *(ulong *)((long)register0x00000020 + -0x288) = uVar28;
      *(long *)((long)register0x00000020 + -0xe0) = auVar38._0_8_;
      *(long *)((long)register0x00000020 + -0x260) = auVar38._8_8_;
      *(ulong *)((long)register0x00000020 + -0x268) = uVar22;
      *(undefined8 *)((long)register0x00000020 + -0x388) = 0x17f8df8;
      lVar12 = runtime_newobject();
      lVar26 = *(long *)((long)register0x00000020 + -0xb8);
      *(undefined4 *)(lVar12 + 0x20) = *(undefined4 *)(lVar26 + 0x18);
      uVar11 = *(undefined8 *)(lVar26 + 0x110);
      *(undefined8 *)(lVar12 + 0x10) = *(undefined8 *)(lVar26 + 0x118);
      if (DAT_02e5e450 != 0) {
        *(undefined8 *)((long)register0x00000020 + -0x388) = 0x17f8e27;
        lVar12 = runtime_gcWriteBarrier1();
        *(undefined8 *)*pauVar31 = uVar11;
      }
      *(undefined8 *)(lVar12 + 8) = uVar11;
      lVar9 = *(long *)((long)register0x00000020 + -0x268);
      uVar28 = lVar9 + 1;
      uVar22 = *(ulong *)((long)register0x00000020 + -0x260);
      if (uVar22 < uVar28) {
        *(long *)((long)register0x00000020 + -0xa0) = lVar12;
        *(undefined8 *)((long)register0x00000020 + -0x388) = 0x17f8e74;
        puVar30 = (undefined8 *)runtime_growslice(1,&DAT_01b241a0);
        lVar12 = *(long *)((long)register0x00000020 + -0xa0);
        lVar26 = *(long *)((long)register0x00000020 + -0xb8);
      }
      else {
        puVar30 = *(undefined8 **)((long)register0x00000020 + -200);
      }
      auVar39._8_8_ = uVar22;
      auVar39._0_8_ = lVar12;
      if (DAT_02e5e450 != 0) {
        uVar11 = puVar30[lVar9];
        *(undefined8 *)((long)register0x00000020 + -0x388) = 0x17f8e9d;
        auVar39 = runtime_gcWriteBarrier2();
        *(long *)*pauVar31 = auVar39._0_8_;
        *(undefined8 *)(*pauVar31 + 8) = uVar11;
      }
      uVar11 = auVar39._8_8_;
      puVar30[lVar9] = auVar39._0_8_;
      uVar27 = *(long *)((long)register0x00000020 + -0x290) + 1;
      uVar22 = *(ulong *)((long)register0x00000020 + -0x288);
      if (uVar22 < uVar27) {
        *(undefined8 **)((long)register0x00000020 + -0xb0) = puVar30;
        *(ulong *)((long)register0x00000020 + -0x248) = uVar28;
        *(undefined8 *)((long)register0x00000020 + -0x250) = uVar11;
        *(undefined8 *)((long)register0x00000020 + -0x388) = 0x17f8f06;
        lVar12 = runtime_growslice(1,&DAT_01c05960);
        uVar11 = *(undefined8 *)((long)register0x00000020 + -0x250);
        puVar30 = *(undefined8 **)((long)register0x00000020 + -0xb0);
        lVar26 = *(long *)((long)register0x00000020 + -0xb8);
        uVar28 = *(ulong *)((long)register0x00000020 + -0x248);
      }
      else {
        lVar12 = *(long *)((long)register0x00000020 + -0xe0);
      }
      auVar40._8_8_ = uVar11;
      auVar40._0_8_ = lVar12;
      if (DAT_02e5e450 != 0) {
        uVar11 = *(undefined8 *)(lVar12 + -8 + uVar27 * 8);
        *(undefined8 *)((long)register0x00000020 + -0x388) = 0x17f8f45;
        auVar40 = runtime_gcWriteBarrier2();
        *(long *)*pauVar31 = lVar26;
        *(undefined8 *)(*pauVar31 + 8) = uVar11;
      }
      *(long *)(auVar40._0_8_ + -8 + uVar27 * 8) = lVar26;
      puVar21 = (undefined8 *)(*(long *)((long)register0x00000020 + -0x60) + 0x30);
      lVar12 = *(long *)((long)register0x00000020 + -0x270) + 1;
    } while( true );
  }
  goto LAB_017fa13f;
LAB_017fa020:
  if (lVar12 != 0) {
    *(undefined8 *)((long)register0x00000020 + -0x388) = 0x17fa02a;
    runtime_panicunsafestringlen();
  }
  *(undefined8 *)((long)register0x00000020 + -0x388) = 0x17fa02f;
  runtime_panicunsafestringnilptr();
LAB_017fa02f:
  *(undefined8 *)((long)register0x00000020 + -0x388) = 0x17fa045;
  runtime_gopanic();
LAB_017fa045:
  *(undefined8 *)((long)register0x00000020 + -0x388) = 0x17fa058;
  runtime_gopanic();
LAB_017fa058:
  *(undefined8 *)((long)register0x00000020 + -0x388) = 0x17fa06b;
  runtime_gopanic();
LAB_017fa06b:
  *(undefined8 *)((long)register0x00000020 + -0x388) = 0x17fa07e;
  runtime_gopanic();
LAB_017fa07e:
  *(undefined8 *)((long)register0x00000020 + -0x388) = 0x17fa091;
  runtime_gopanic();
LAB_017fa091:
  *(undefined8 *)((long)register0x00000020 + -0x388) = 0x17fa0a5;
  runtime_gopanic();
LAB_017fa0a5:
  *(undefined8 *)((long)register0x00000020 + -0x388) = 0x17fa0b8;
  runtime_gopanic();
LAB_017fa0b8:
  *(undefined8 *)((long)register0x00000020 + -0x388) = 0x17fa0cb;
  runtime_gopanic();
LAB_017fa0cb:
  *(undefined8 *)((long)register0x00000020 + -0x388) = 0x17fa0de;
  runtime_gopanic();
LAB_017fa0de:
  *(undefined8 *)((long)register0x00000020 + -0x388) = 0x17fa0f1;
  runtime_gopanic();
LAB_017fa0f1:
  *(undefined8 *)((long)register0x00000020 + -0x388) = 0x17fa105;
  runtime_gopanic();
LAB_017fa105:
  *(undefined8 *)((long)register0x00000020 + -0x388) = 0x17fa118;
  runtime_gopanic();
LAB_017fa118:
  *(undefined8 *)((long)register0x00000020 + -0x388) = 0x17fa12b;
  runtime_gopanic();
LAB_017fa12b:
  unaff_RBX = &DAT_01f393c0;
  *(undefined8 *)((long)register0x00000020 + -0x388) = 0x17fa13e;
  in_RAX = runtime_gopanic();
LAB_017fa13f:
  *(undefined8 *)(puVar20 + 8) = in_RAX;
  *(undefined8 **)(puVar20 + 0x10) = unaff_RBX;
  *(undefined8 *)(puVar20 + -8) = 0x17fa14e;
  runtime_morestack_noctxt();
  in_RAX = *(undefined8 *)(puVar20 + 8);
  unaff_RBX = *(undefined8 **)(puVar20 + 0x10);
  register0x00000020 = (BADSPACEBASE *)puVar20;
  goto code_r0x017f7de0;
}




// === cursor.newConnectRequest @ 0x17fa160 ===

undefined8 *
cursor_newConnectRequest
          (undefined8 param_1,long param_2,undefined8 param_3,undefined8 param_4,undefined8 param_5,
          undefined8 param_6)

{
  undefined8 uVar1;
  long *plVar2;
  undefined8 uVar3;
  undefined8 *puVar4;
  long lVar5;
  undefined8 *puVar6;
  undefined8 extraout_RDX;
  undefined8 unaff_RBX;
  undefined1 *puVar7;
  ulong uVar8;
  undefined1 (*in_R11) [16];
  undefined1 (*pauVar9) [16];
  long unaff_R14;
  undefined1 auVar10 [16];
  undefined8 uStack0000000000000010;
  undefined8 uStack0000000000000018;
  undefined8 uStack0000000000000020;
  long lStack0000000000000028;
  undefined8 uStack0000000000000030;
  undefined8 uStack0000000000000038;
  undefined4 auStack_228 [2];
  undefined1 auStack_220 [56];
  undefined8 uStack_1e8;
  undefined8 uStack_1e0;
  undefined8 uStack_1d8;
  undefined8 uStack_1d0;
  undefined8 uStack_1c8;
  undefined8 uStack_1c0;
  undefined8 uStack_1b8;
  undefined8 uStack_1b0;
  undefined8 uStack_1a8;
  undefined8 uStack_1a0;
  undefined8 uStack_198;
  undefined8 uStack_190;
  undefined8 uStack_188;
  undefined8 uStack_180;
  undefined8 uStack_178;
  undefined8 uStack_170;
  undefined8 uStack_168;
  undefined8 uStack_160;
  undefined1 *puStack_158;
  long lStack_150;
  undefined8 uStack_148;
  undefined8 uStack_140;
  undefined8 uStack_138;
  undefined8 uStack_130;
  undefined8 uStack_128;
  undefined *puStack_120;
  undefined8 uStack_118;
  long lStack_110;
  undefined8 uStack_108;
  undefined8 uStack_100;
  undefined8 uStack_f8;
  undefined8 uStack_f0;
  undefined8 uStack_e8;
  undefined8 uStack_e0;
  undefined8 uStack_d8;
  undefined8 uStack_d0;
  undefined8 uStack_c8;
  undefined1 *puStack_c0;
  undefined8 *puStack_b8;
  undefined8 uStack_b0;
  undefined8 uStack_a8;
  undefined8 uStack_a0;
  undefined8 uStack_98;
  undefined8 uStack_90;
  undefined8 uStack_88;
  undefined8 uStack_80;
  undefined8 uStack_78;
  undefined8 uStack_70;
  undefined8 *puStack_68;
  undefined8 uStack_60;
  undefined8 uStack_58;
  undefined **ppuStack_50;
  undefined8 uStack_48;
  undefined8 uStack_40;
  undefined8 uStack_38;
  undefined8 *puStack_20;
  undefined8 uStack_18;
  undefined8 uStack_10;
  
  uStack0000000000000018 = param_4;
  uStack0000000000000010 = unaff_RBX;
  lStack0000000000000028 = param_2;
  uStack0000000000000020 = param_1;
  uStack0000000000000030 = param_5;
  uStack0000000000000038 = param_6;
  while (auStack_220 <= *(undefined1 **)(unaff_R14 + 0x10)) {
    runtime_morestack_noctxt();
  }
  puStack_b8 = (undefined8 *)runtime_newobject();
  if (DAT_02e5e450 != 0) {
    puStack_b8 = (undefined8 *)runtime_gcWriteBarrier1();
    *(undefined8 *)*in_R11 = uStack0000000000000010;
  }
  *puStack_b8 = uStack0000000000000010;
  puStack_b8[0xd] = 0;
  uStack_58 = runtime_makemap_small();
  puVar4 = puStack_b8;
  if (DAT_02e5e450 != 0) {
    auVar10 = runtime_gcWriteBarrier2();
    uStack_58 = auVar10._0_8_;
    *in_R11 = auVar10;
  }
  puVar4[0xd] = uStack_58;
  auVar10 = runtime_convTstring();
  uStack_18 = auVar10._0_8_;
  puStack_20 = &DAT_0194e220;
  uStack_80 = fmt_Sprintf(1,1,auVar10._8_8_,&puStack_20);
  uStack_118 = 9;
  uStack_60 = net_textproto_CanonicalMIMEHeaderKey();
  uStack_108 = 0xd;
  puStack_68 = (undefined8 *)runtime_newobject();
  puStack_68[1] = uStack_118;
  if (DAT_02e5e450 != 0) {
    puStack_68 = (undefined8 *)runtime_gcWriteBarrier1();
    *(undefined8 *)*in_R11 = uStack_80;
  }
  *puStack_68 = uStack_80;
  plVar2 = (long *)runtime_mapassign_faststr(uStack_108);
  plVar2[1] = 1;
  plVar2[2] = 1;
  if (DAT_02e5e450 != 0) {
    lVar5 = *plVar2;
    plVar2 = (long *)runtime_gcWriteBarrier2();
    *(undefined8 **)*in_R11 = puStack_68;
    *(long *)(*in_R11 + 8) = lVar5;
  }
  *plVar2 = (long)puStack_68;
  puVar4 = puStack_b8;
  if (puStack_b8[0xd] == 0) {
    uVar3 = runtime_makemap_small();
    puVar4 = puStack_b8;
    if (DAT_02e5e450 != 0) {
      auVar10 = runtime_gcWriteBarrier2();
      uVar3 = auVar10._0_8_;
      *in_R11 = auVar10;
    }
    puVar4[0xd] = uVar3;
  }
  puStack_c0 = (undefined1 *)puVar4[0xd];
  uStack_60 = net_textproto_CanonicalMIMEHeaderKey();
  uStack_108 = 0x17;
  puStack_68 = (undefined8 *)runtime_newobject();
  puVar7 = puStack_c0;
  puStack_68[1] = 5;
  *puStack_68 = 
  "2.1.7SkillmacOStasksstartMacOSnanos%s_%ddiffsplansskill.jsonPATCHx-appuser_ravenbytesQuery3.0.0ROUTE%s#%d</tr>debug%s:%d*fuzz*listPOST:HEAD:IndexInputshort%s,%s=j=02=G=15-0700%dh%sdefersweeptestRtestWexecWhchanexecRschedsudogtimergscanmheaptracepanicsleepamd64gcing MB,  got= ...\n max=scav  ptr ] = (trap:init  ms, fault and  tab= tag= top=[...], fp:deny"
  ;
  puVar4 = (undefined8 *)runtime_mapassign_faststr(uStack_108);
  puVar4[1] = 1;
  puVar4[2] = 1;
  if (DAT_02e5e450 != 0) {
    uVar3 = *puVar4;
    puVar4 = (undefined8 *)runtime_gcWriteBarrier2();
    *(undefined8 **)*in_R11 = puStack_68;
    *(undefined8 *)(*in_R11 + 8) = uVar3;
  }
  *puVar4 = puStack_68;
  puVar4 = puStack_b8;
  if (puStack_b8[0xd] == 0) {
    uVar3 = runtime_makemap_small();
    puVar4 = puStack_b8;
    if (DAT_02e5e450 != 0) {
      auVar10 = runtime_gcWriteBarrier2();
      uVar3 = auVar10._0_8_;
      *in_R11 = auVar10;
    }
    puVar4[0xd] = uVar3;
  }
  uStack_c8 = puVar4[0xd];
  github_com_google_uuid_NewString();
  uStack_100 = strings_Replace(1,0,extraout_RDX,&DAT_01f34f48,0,0xffffffffffffffff);
  puStack_158 = puVar7;
  lVar5 = time_Now();
  if (lVar5 < 0) {
    puVar7 = &DAT_dd7b17f80 + ((ulong)(lVar5 * 2) >> 0x1f);
  }
  lStack_150 = (long)puVar7 * 1000000000 + (long)(int)((uint)lVar5 & 0x3fffffff) +
               -0x5e4dfc14c2e60000;
  uStack_10 = runtime_newobject();
  math_rand_rngSource_Seed();
  uVar8 = (ulong)DAT_01f49500;
  do {
    lVar5 = (uVar8 & *(ulong *)PTR_DAT_02de5e00) * 0x10;
    if (*(undefined **)(PTR_DAT_02de5e00 + lVar5 + 8) == &DAT_01a368a0) {
      uStack_40 = *(undefined8 *)(PTR_DAT_02de5e00 + lVar5 + 0x10);
      goto LAB_017fa5a3;
    }
    uVar8 = uVar8 + 1;
  } while (*(undefined **)(PTR_DAT_02de5e00 + lVar5 + 8) != (undefined *)0x0);
  uStack_40 = runtime_typeAssert();
LAB_017fa5a3:
  ppuStack_50 = &PTR_DAT_01f494f0;
  uStack_48 = uStack_10;
  uStack_38 = uStack_10;
  uStack_1e8 = 0x6200000061;
  uStack_1e0 = 0x6400000063;
  uStack_1d8 = 0x6600000065;
  uStack_1d0 = 0x6800000067;
  uStack_1c8 = 0x6a00000069;
  uStack_1c0 = 0x6c0000006b;
  uStack_1b8 = 0x6e0000006d;
  uStack_1b0 = 0x700000006f;
  uStack_1a8 = 0x7200000071;
  uStack_1a0 = 0x7400000073;
  uStack_198 = 0x7600000075;
  uStack_190 = 0x7800000077;
  uStack_188 = 0x7a00000079;
  uStack_180 = 0x3200000031;
  uStack_178 = 0x3400000033;
  uStack_170 = 0x3600000035;
  uStack_168 = 0x3800000037;
  uStack_160 = 0x3000000039;
  lVar5 = 0;
  while( true ) {
    if (0xf < lVar5) {
      pauVar9 = (undefined1 (*) [16])auStack_228;
      runtime_slicerunetostring(0x10);
      uStack_88 = runtime_concatstring5(uStack_100,puStack_158,&DAT_01c38ee4,3,&DAT_01f34f48,1,&DAT_01c38ee4,
                               3);
      puStack_120 = &DAT_01c38ee1;
      uStack_60 = net_textproto_CanonicalMIMEHeaderKey();
      uStack_108 = 0xb;
      puVar4 = (undefined8 *)runtime_newobject();
      puVar4[1] = puStack_120;
      uVar3 = uStack_88;
      if (DAT_02e5e450 != 0) {
        puVar4 = (undefined8 *)runtime_gcWriteBarrier1();
        uVar3 = uStack_88;
        *(undefined8 *)*pauVar9 = uStack_88;
      }
      *puVar4 = uVar3;
      puStack_68 = puVar4;
      plVar2 = (long *)runtime_mapassign_faststr(uStack_108);
      plVar2[1] = 1;
      plVar2[2] = 1;
      puVar4 = puStack_68;
      if (DAT_02e5e450 != 0) {
        lVar5 = *plVar2;
        plVar2 = (long *)runtime_gcWriteBarrier2();
        puVar4 = puStack_68;
        *(undefined8 **)*pauVar9 = puStack_68;
        *(long *)((long)*pauVar9 + 8) = lVar5;
      }
      *plVar2 = (long)puVar4;
      puVar4 = puStack_b8;
      if (puStack_b8[0xd] == 0) {
        uVar3 = runtime_makemap_small();
        puVar4 = puStack_b8;
        if (DAT_02e5e450 != 0) {
          auVar10 = runtime_gcWriteBarrier2();
          uVar3 = auVar10._0_8_;
          *pauVar9 = auVar10;
        }
        puVar4[0xd] = uVar3;
      }
      uStack_128 = *(undefined8 *)(lStack0000000000000028 + 0x70);
      uStack_90 = *(undefined8 *)(lStack0000000000000028 + 0x68);
      uStack_d0 = puVar4[0xd];
      uStack_60 = net_textproto_CanonicalMIMEHeaderKey();
      uStack_108 = 0xc;
      puVar4 = (undefined8 *)runtime_newobject();
      puVar4[1] = uStack_128;
      uVar3 = uStack_90;
      if (DAT_02e5e450 != 0) {
        puVar4 = (undefined8 *)runtime_gcWriteBarrier1();
        uVar3 = uStack_90;
        *(undefined8 *)*pauVar9 = uStack_90;
      }
      *puVar4 = uVar3;
      puStack_68 = puVar4;
      plVar2 = (long *)runtime_mapassign_faststr(uStack_108);
      plVar2[1] = 1;
      plVar2[2] = 1;
      puVar4 = puStack_68;
      if (DAT_02e5e450 != 0) {
        lVar5 = *plVar2;
        plVar2 = (long *)runtime_gcWriteBarrier2();
        puVar4 = puStack_68;
        *(undefined8 **)*pauVar9 = puStack_68;
        *(long *)((long)*pauVar9 + 8) = lVar5;
      }
      *plVar2 = (long)puVar4;
      puVar4 = puStack_b8;
      if (puStack_b8[0xd] == 0) {
        uVar3 = runtime_makemap_small();
        puVar4 = puStack_b8;
        if (DAT_02e5e450 != 0) {
          auVar10 = runtime_gcWriteBarrier2();
          uVar3 = auVar10._0_8_;
          *pauVar9 = auVar10;
        }
        puVar4[0xd] = uVar3;
      }
      uStack_d8 = puVar4[0xd];
      uStack_60 = net_textproto_CanonicalMIMEHeaderKey();
      uStack_108 = 0x11;
      puStack_68 = (undefined8 *)runtime_newobject();
      puStack_68[1] = 0xd;
      *puStack_68 = &DAT_01c49caa;
      puVar6 = (undefined8 *)runtime_mapassign_faststr(uStack_108);
      puVar6[1] = 1;
      puVar6[2] = 1;
      puVar4 = puStack_68;
      if (DAT_02e5e450 != 0) {
        uVar3 = *puVar6;
        puVar6 = (undefined8 *)runtime_gcWriteBarrier2();
        puVar4 = puStack_68;
        *(undefined8 **)*pauVar9 = puStack_68;
        *(undefined8 *)((long)*pauVar9 + 8) = uVar3;
      }
      *puVar6 = puVar4;
      puVar4 = puStack_b8;
      if (puStack_b8[0xd] == 0) {
        uVar3 = runtime_makemap_small();
        puVar4 = puStack_b8;
        if (DAT_02e5e450 != 0) {
          auVar10 = runtime_gcWriteBarrier2();
          uVar3 = auVar10._0_8_;
          *pauVar9 = auVar10;
        }
        puVar4[0xd] = uVar3;
      }
      uStack_e0 = puVar4[0xd];
      github_com_google_uuid_NewString();
      auVar10 = runtime_convTstring();
      uStack_18 = auVar10._0_8_;
      puStack_20 = &DAT_0194e220;
      uStack_98 = fmt_Sprintf(1,1,auVar10._8_8_,&puStack_20);
      uStack_130 = 7;
      uStack_60 = net_textproto_CanonicalMIMEHeaderKey();
      uStack_108 = 0xf;
      puVar4 = (undefined8 *)runtime_newobject();
      puVar4[1] = uStack_130;
      uVar3 = uStack_98;
      if (DAT_02e5e450 != 0) {
        puVar4 = (undefined8 *)runtime_gcWriteBarrier1();
        uVar3 = uStack_98;
        *(undefined8 *)*pauVar9 = uStack_98;
      }
      uVar1 = uStack_e0;
      *puVar4 = uVar3;
      puStack_68 = puVar4;
      plVar2 = (long *)runtime_mapassign_faststr(uStack_108);
      plVar2[1] = 1;
      plVar2[2] = 1;
      puVar4 = puStack_68;
      if (DAT_02e5e450 != 0) {
        lVar5 = *plVar2;
        plVar2 = (long *)runtime_gcWriteBarrier2();
        puVar4 = puStack_68;
        *(undefined8 **)*pauVar9 = puStack_68;
        *(long *)((long)*pauVar9 + 8) = lVar5;
      }
      *plVar2 = (long)puVar4;
      puVar4 = puStack_b8;
      if (puStack_b8[0xd] == 0) {
        uVar3 = runtime_makemap_small();
        puVar4 = puStack_b8;
        if (DAT_02e5e450 != 0) {
          auVar10 = runtime_gcWriteBarrier2();
          uVar3 = auVar10._0_8_;
          *pauVar9 = auVar10;
        }
        puVar4[0xd] = uVar3;
      }
      uStack_e8 = puVar4[0xd];
      uStack_a0 = github_com_google_uuid_NewString();
      uStack_138 = uVar1;
      uStack_60 = net_textproto_CanonicalMIMEHeaderKey();
      uStack_108 = 0x17;
      puVar4 = (undefined8 *)runtime_newobject();
      puVar4[1] = uStack_138;
      uVar3 = uStack_a0;
      if (DAT_02e5e450 != 0) {
        puVar4 = (undefined8 *)runtime_gcWriteBarrier1();
        uVar3 = uStack_a0;
        *(undefined8 *)*pauVar9 = uStack_a0;
      }
      *puVar4 = uVar3;
      puStack_68 = puVar4;
      plVar2 = (long *)runtime_mapassign_faststr(uStack_108);
      plVar2[1] = 1;
      plVar2[2] = 1;
      puVar4 = puStack_68;
      if (DAT_02e5e450 != 0) {
        auVar10 = runtime_gcWriteBarrier2();
        puVar4 = puStack_68;
        plVar2 = auVar10._0_8_;
        *(undefined8 **)*pauVar9 = puStack_68;
        *(long *)((long)*pauVar9 + 8) = auVar10._8_8_;
      }
      *plVar2 = (long)puVar4;
      puVar4 = puStack_b8;
      if (puStack_b8[0xd] == 0) {
        uVar3 = runtime_makemap_small();
        auVar10._8_8_ = puStack_b8;
        auVar10._0_8_ = uVar3;
        if (DAT_02e5e450 != 0) {
          uVar3 = puStack_b8[0xd];
          auVar10 = runtime_gcWriteBarrier2();
          *(long *)*pauVar9 = auVar10._0_8_;
          *(undefined8 *)((long)*pauVar9 + 8) = uVar3;
        }
        puVar4 = auVar10._8_8_;
        puVar4[0xd] = auVar10._0_8_;
      }
      uVar3 = *(undefined8 *)(lStack0000000000000028 + 0x90);
      uStack_f0 = puVar4[0xd];
      uStack_a8 = kiro2api_internal_logic_cursor_GetChecksum(*(undefined8 *)(lStack0000000000000028 + 0xa0),lStack0000000000000028
                               ,uStack_f0,*(undefined8 *)(lStack0000000000000028 + 0x98));
      uStack_140 = uVar3;
      uStack_60 = net_textproto_CanonicalMIMEHeaderKey();
      uStack_108 = 0x11;
      puVar4 = (undefined8 *)runtime_newobject();
      puVar4[1] = uStack_140;
      uVar3 = uStack_a8;
      if (DAT_02e5e450 != 0) {
        puVar4 = (undefined8 *)runtime_gcWriteBarrier1();
        uVar3 = uStack_a8;
        *(undefined8 *)*pauVar9 = uStack_a8;
      }
      *puVar4 = uVar3;
      puStack_68 = puVar4;
      plVar2 = (long *)runtime_mapassign_faststr(uStack_108);
      plVar2[1] = 1;
      plVar2[2] = 1;
      puVar4 = puStack_68;
      if (DAT_02e5e450 != 0) {
        lVar5 = *plVar2;
        plVar2 = (long *)runtime_gcWriteBarrier2();
        puVar4 = puStack_68;
        *(undefined8 **)*pauVar9 = puStack_68;
        *(long *)((long)*pauVar9 + 8) = lVar5;
      }
      *plVar2 = (long)puVar4;
      puVar4 = puStack_b8;
      if (puStack_b8[0xd] == 0) {
        uVar3 = runtime_makemap_small();
        puVar4 = puStack_b8;
        if (DAT_02e5e450 != 0) {
          auVar10 = runtime_gcWriteBarrier2();
          uVar3 = auVar10._0_8_;
          *pauVar9 = auVar10;
        }
        puVar4[0xd] = uVar3;
      }
      uStack_70 = puVar4[0xd];
      uStack_60 = net_textproto_CanonicalMIMEHeaderKey();
      uStack_108 = 0xc;
      puStack_68 = (undefined8 *)runtime_newobject();
      puStack_68[1] = 5;
      *puStack_68 = &DAT_01c3a54e;
      puVar6 = (undefined8 *)runtime_mapassign_faststr(uStack_108);
      puVar6[1] = 1;
      puVar6[2] = 1;
      puVar4 = puStack_68;
      if (DAT_02e5e450 != 0) {
        uVar3 = *puVar6;
        puVar6 = (undefined8 *)runtime_gcWriteBarrier2();
        puVar4 = puStack_68;
        *(undefined8 **)*pauVar9 = puStack_68;
        *(undefined8 *)((long)*pauVar9 + 8) = uVar3;
      }
      *puVar6 = puVar4;
      puVar4 = puStack_b8;
      if (puStack_b8[0xd] == 0) {
        uVar3 = runtime_makemap_small();
        puVar4 = puStack_b8;
        if (DAT_02e5e450 != 0) {
          auVar10 = runtime_gcWriteBarrier2();
          uVar3 = auVar10._0_8_;
          *pauVar9 = auVar10;
        }
        puVar4[0xd] = uVar3;
      }
      uStack_f8 = puVar4[0xd];
      uStack_60 = net_textproto_CanonicalMIMEHeaderKey();
      uStack_108 = 0x1a;
      puStack_68 = (undefined8 *)runtime_newobject();
      puStack_68[1] = 5;
      *puStack_68 = &DAT_01c3a54e;
      puVar6 = (undefined8 *)runtime_mapassign_faststr(uStack_108);
      puVar6[1] = 1;
      puVar6[2] = 1;
      puVar4 = puStack_68;
      if (DAT_02e5e450 != 0) {
        uVar3 = *puVar6;
        puVar6 = (undefined8 *)runtime_gcWriteBarrier2();
        puVar4 = puStack_68;
        *(undefined8 **)*pauVar9 = puStack_68;
        *(undefined8 *)((long)*pauVar9 + 8) = uVar3;
      }
      *puVar6 = puVar4;
      puVar4 = puStack_b8;
      if (puStack_b8[0xd] == 0) {
        uVar3 = runtime_makemap_small();
        puVar4 = puStack_b8;
        if (DAT_02e5e450 != 0) {
          auVar10 = runtime_gcWriteBarrier2();
          uVar3 = auVar10._0_8_;
          *pauVar9 = auVar10;
        }
        puVar4[0xd] = uVar3;
      }
      uStack_148 = *(undefined8 *)(lStack0000000000000028 + 0xb0);
      uStack_b0 = *(undefined8 *)(lStack0000000000000028 + 0xa8);
      uStack_70 = puVar4[0xd];
      uStack_60 = net_textproto_CanonicalMIMEHeaderKey();
      uStack_108 = 0xc;
      puVar4 = (undefined8 *)runtime_newobject();
      puVar4[1] = uStack_148;
      uVar3 = uStack_b0;
      if (DAT_02e5e450 != 0) {
        puVar4 = (undefined8 *)runtime_gcWriteBarrier1();
        uVar3 = uStack_b0;
        *(undefined8 *)*pauVar9 = uStack_b0;
      }
      *puVar4 = uVar3;
      puStack_68 = puVar4;
      plVar2 = (long *)runtime_mapassign_faststr(uStack_108);
      plVar2[1] = 1;
      plVar2[2] = 1;
      puVar4 = puStack_68;
      if (DAT_02e5e450 != 0) {
        lVar5 = *plVar2;
        plVar2 = (long *)runtime_gcWriteBarrier2();
        puVar4 = puStack_68;
        *(undefined8 **)*pauVar9 = puStack_68;
        *(long *)((long)*pauVar9 + 8) = lVar5;
      }
      *plVar2 = (long)puVar4;
      puVar4 = puStack_b8;
      if (puStack_b8[0xd] == 0) {
        uVar3 = runtime_makemap_small();
        puVar4 = puStack_b8;
        if (DAT_02e5e450 != 0) {
          auVar10 = runtime_gcWriteBarrier2();
          uVar3 = auVar10._0_8_;
          *pauVar9 = auVar10;
        }
        puVar4[0xd] = uVar3;
      }
      uStack_78 = puVar4[0xd];
      uStack_60 = net_textproto_CanonicalMIMEHeaderKey();
      uStack_108 = 0xc;
      puVar4 = (undefined8 *)runtime_newobject();
      puVar4[1] = uStack0000000000000038;
      if (DAT_02e5e450 != 0) {
        puVar4 = (undefined8 *)runtime_gcWriteBarrier1();
        *(undefined8 *)*pauVar9 = uStack0000000000000030;
      }
      *puVar4 = uStack0000000000000030;
      puStack_68 = puVar4;
      plVar2 = (long *)runtime_mapassign_faststr(uStack_108);
      plVar2[1] = 1;
      plVar2[2] = 1;
      if (DAT_02e5e450 != 0) {
        lVar5 = *plVar2;
        plVar2 = (long *)runtime_gcWriteBarrier2();
        *(undefined8 **)*pauVar9 = puStack_68;
        *(long *)((long)*pauVar9 + 8) = lVar5;
      }
      *plVar2 = (long)puStack_68;
      return puStack_b8;
    }
    lStack_110 = lVar5;
    uVar8 = math_rand_Rand_Intn();
    lVar5 = lStack_110;
    if (0x23 < uVar8) break;
    auStack_228[lStack_110] = *(undefined4 *)((long)&uStack_1e8 + uVar8 * 4);
    lVar5 = lVar5 + 1;
  }
                    /* WARNING: Subroutine does not return */
  runtime_panicIndex();
}



