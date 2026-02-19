// CodeFreeMax - ANTIGRAVITY Channel Decompiled Functions
// 5 functions

// === antigravity.convertMessagesToContents @ 0x17b0660 ===

void antigravity_convertMessagesToContents(void)

{
  bool bVar1;
  char cVar2;
  undefined8 *puVar3;
  undefined8 uVar4;
  long lVar5;
  char *pcVar6;
  long *plVar7;
  undefined1 *puVar8;
  ulong in_RCX;
  undefined8 *puVar9;
  undefined8 *puVar10;
  long lVar11;
  ulong uVar12;
  undefined8 *unaff_RBX;
  ulong uVar13;
  ulong uVar14;
  long *plVar15;
  ulong uVar16;
  ulong uVar17;
  long lVar18;
  undefined8 *in_R11;
  long *plVar19;
  long *plVar20;
  long unaff_R14;
  long in_XMM15_Qa;
  undefined8 in_XMM15_Qb;
  undefined1 auVar21 [16];
  undefined8 *puStack0000000000000010;
  ulong uStack0000000000000018;
  ulong uStack_428;
  undefined8 *puStack_420;
  undefined8 *puStack_418;
  long lStack_410;
  long lStack_408;
  long lStack_400;
  long lStack_3f8;
  long lStack_3f0;
  long lStack_3e8;
  long lStack_3e0;
  ulong uStack_3d8;
  ulong uStack_3d0;
  long lStack_3c8;
  ulong uStack_3c0;
  ulong uStack_3b8;
  ulong uStack_3b0;
  ulong uStack_3a8;
  long lStack_3a0;
  ulong uStack_398;
  ulong uStack_390;
  undefined8 *puStack_388;
  ulong uStack_380;
  undefined8 uStack_378;
  undefined8 uStack_370;
  long lStack_368;
  long *plStack_360;
  undefined8 *puStack_358;
  long *plStack_350;
  undefined8 uStack_348;
  undefined8 uStack_340;
  long lStack_338;
  long lStack_330;
  undefined8 uStack_328;
  long lStack_320;
  long lStack_318;
  long *plStack_310;
  long lStack_308;
  undefined8 *puStack_300;
  long lStack_2f8;
  long lStack_2f0;
  long lStack_2e8;
  undefined1 *puStack_2e0;
  long *plStack_2d8;
  long *plStack_2d0;
  long lStack_2c8;
  long lStack_2c0;
  undefined8 *puStack_2b8;
  undefined8 *puStack_2b0;
  undefined8 *puStack_2a8;
  undefined8 *puStack_2a0;
  long *plStack_298;
  undefined8 *puStack_290;
  long lStack_288;
  undefined8 uStack_280;
  long lStack_278;
  undefined8 uStack_270;
  undefined8 auStack_268 [33];
  undefined1 auStack_160 [8];
  undefined8 uStack_158;
  undefined8 *puStack_150;
  undefined8 uStack_130;
  undefined1 auStack_128 [200];
  undefined8 uStack_60;
  undefined8 *puStack_58;
  long *plStack_38;
  long *plStack_30;
  undefined8 *puStack_28;
  undefined8 *puStack_20;
  undefined8 uStack_18;
  undefined8 uStack_10;
  
  while (puStack0000000000000010 = unaff_RBX, uStack0000000000000018 = in_RCX,
        &uStack_428 <= *(ulong **)(unaff_R14 + 0x10)) {
    runtime_morestack_noctxt();
    in_RCX = uStack0000000000000018;
    unaff_RBX = puStack0000000000000010;
  }
  for (lVar11 = 0; lVar11 < (long)in_RCX; lVar11 = lVar11 + 1) {
    puVar3 = (undefined8 *)unaff_RBX[lVar11 * 6 + 2];
    if (puVar3 != (undefined8 *)0x0) {
      lStack_3e8 = lVar11;
      if (*(int *)(puVar3 + 2) == -0x38a1955c) {
        if (puVar3 == &DAT_01a233a0) {
          runtime_mapdelete_faststr();
          in_RCX = uStack0000000000000018;
          lVar11 = lStack_3e8;
          unaff_RBX = puStack0000000000000010;
        }
      }
      else if ((*(int *)(puVar3 + 2) == -0xd99de8a) && (puVar3 == &DAT_0192e960)) {
        puVar3 = *(undefined8 **)unaff_RBX[lVar11 * 6 + 3];
        for (uVar17 = ((undefined8 *)unaff_RBX[lVar11 * 6 + 3])[1]; 0 < (long)uVar17;
            uVar17 = uVar17 - 1) {
          if ((undefined8 *)*puVar3 == &DAT_01a233a0) {
            uStack_380 = uVar17;
            puStack_290 = puVar3;
            runtime_mapdelete_faststr();
            in_RCX = uStack0000000000000018;
            lVar11 = lStack_3e8;
            unaff_RBX = puStack0000000000000010;
            uVar17 = uStack_380;
            puVar3 = puStack_290;
          }
          in_R11 = &DAT_01a233a0;
          puVar3 = puVar3 + 2;
        }
      }
    }
  }
  puVar3 = (undefined8 *)0x0;
  uVar12 = 0;
  uVar17 = 0;
  while (puStack_358 = puVar3, 0 < (long)in_RCX) {
    plStack_38 = (long *)*unaff_RBX;
    plStack_30 = (long *)unaff_RBX[1];
    puStack_28 = (undefined8 *)unaff_RBX[2];
    puStack_20 = (undefined8 *)unaff_RBX[3];
    uStack_18 = unaff_RBX[4];
    uStack_10 = unaff_RBX[5];
    uStack_380 = in_RCX;
    puStack_290 = unaff_RBX;
    if ((plStack_30 == (long *)&DAT_00000004) && ((int)*plStack_38 == 0x6c6f6f74)) {
      uStack_370 = runtime_makemap_small();
      puVar3 = (undefined8 *)runtime_mapassign_faststr(4);
      *puVar3 = &DAT_0194e220;
      if (DAT_02e5e450 != 0) {
        auVar21 = runtime_gcWriteBarrier1();
        puVar3 = auVar21._0_8_;
        *in_R11 = auVar21._8_8_;
      }
      puVar3[1] = &PTR_DAT_01f3a180;
      plStack_298 = (long *)runtime_convTstring();
      puVar3 = (undefined8 *)runtime_mapassign_faststr(0xb);
      *puVar3 = &DAT_0194e220;
      if (DAT_02e5e450 != 0) {
        auVar21 = runtime_gcWriteBarrier2();
        puVar3 = auVar21._0_8_;
        *in_R11 = plStack_298;
        in_R11[1] = auVar21._8_8_;
      }
      puVar3[1] = plStack_298;
      puStack_388 = puStack_28;
      puStack_2a0 = puStack_20;
      puVar3 = (undefined8 *)runtime_mapassign_faststr(7,plStack_298,puStack_20,&DAT_01c3dd44);
      *puVar3 = puStack_388;
      if (DAT_02e5e450 != 0) {
        uVar4 = puVar3[1];
        puVar3 = (undefined8 *)runtime_gcWriteBarrier2();
        *in_R11 = puStack_2a0;
        in_R11[1] = uVar4;
      }
      puVar3[1] = puStack_2a0;
      plStack_38 = (long *)&DAT_01c3978a;
      plStack_30 = (long *)&DAT_00000004;
      uStack_18 = in_XMM15_Qa;
      uStack_10 = in_XMM15_Qb;
      puVar3 = (undefined8 *)runtime_newobject();
      *puVar3 = &DAT_01a233a0;
      if (DAT_02e5e450 != 0) {
        puVar3 = (undefined8 *)runtime_gcWriteBarrier1();
        *in_R11 = uStack_370;
      }
      puVar3[1] = uStack_370;
      puStack_20 = (undefined8 *)runtime_convTslice();
      puStack_28 = &DAT_0192e960;
      uVar17 = uVar17 + 1;
      puVar3 = puStack_358;
      if (uVar12 < uVar17) {
        puVar3 = (undefined8 *)runtime_growslice(1,&DAT_01ad67a0);
      }
      lVar11 = uVar17 * 0x30;
      puVar9 = puVar3 + uVar17 * 6 + -6;
      if (DAT_02e5e450 != 0) {
        lStack_3a0 = uVar17 * 0x30;
        uStack_398 = uVar12;
        uStack_390 = uVar17;
        puStack_2b0 = puVar3 + uVar17 * 6 + -6;
        puStack_2a8 = puVar3;
        runtime_wbMove();
        puVar3 = puStack_2a8;
        uVar12 = uStack_398;
        lVar11 = lStack_3a0;
        uVar17 = uStack_390;
        puVar9 = puStack_2b0;
      }
      *puVar9 = plStack_38;
      puVar9[1] = plStack_30;
      *(undefined8 **)((long)puVar3 + lVar11 + -0x20) = puStack_28;
      *(undefined8 **)((long)puVar3 + lVar11 + -0x18) = puStack_20;
      *(undefined4 *)((long)puVar3 + lVar11 + -0x10) = (undefined4)uStack_18;
      *(undefined4 *)((long)puVar3 + lVar11 + -0xc) = uStack_18._4_4_;
      *(undefined4 *)((long)puVar3 + lVar11 + -8) = (undefined4)uStack_10;
      *(undefined4 *)((long)puVar3 + lVar11 + -4) = uStack_10._4_4_;
    }
    else {
      uVar17 = uVar17 + 1;
      if (uVar12 < uVar17) {
        puVar3 = (undefined8 *)runtime_growslice(1,&DAT_01ad67a0);
      }
      lVar11 = uVar17 * 0x30;
      puVar9 = puVar3 + uVar17 * 6 + -6;
      if (DAT_02e5e450 != 0) {
        uStack_3b0 = uVar12;
        uStack_3a8 = uVar17;
        lStack_3a0 = uVar17 * 0x30;
        puStack_2b8 = puVar3;
        puStack_2b0 = puVar3 + uVar17 * 6 + -6;
        runtime_wbMove();
        puVar3 = puStack_2b8;
        uVar12 = uStack_3b0;
        uVar17 = uStack_3a8;
        lVar11 = lStack_3a0;
        puVar9 = puStack_2b0;
      }
      *puVar9 = plStack_38;
      puVar9[1] = plStack_30;
      *(undefined8 **)((long)puVar3 + lVar11 + -0x20) = puStack_28;
      *(undefined8 **)((long)puVar3 + lVar11 + -0x18) = puStack_20;
      *(undefined4 *)((long)puVar3 + lVar11 + -0x10) = (undefined4)uStack_18;
      *(undefined4 *)((long)puVar3 + lVar11 + -0xc) = uStack_18._4_4_;
      *(undefined4 *)((long)puVar3 + lVar11 + -8) = (undefined4)uStack_10;
      *(undefined4 *)((long)puVar3 + lVar11 + -4) = uStack_10._4_4_;
    }
    unaff_RBX = puStack_290 + 6;
    in_RCX = uStack_380 - 1;
  }
  FUN_00488ccb(auStack_128);
  uStack_130 = 0x8080808080808080;
  puStack_58 = &uStack_130;
  uStack_60 = runtime_rand();
  puVar3 = puStack_358;
  for (uVar12 = uVar17; 0 < (long)uVar12; uVar12 = uVar12 - 1) {
    plStack_38 = (long *)*puVar3;
    plStack_30 = (long *)puVar3[1];
    puStack_28 = (undefined8 *)puVar3[2];
    puStack_20 = (undefined8 *)puVar3[3];
    uStack_18 = puVar3[4];
    uStack_10 = puVar3[5];
    if (puStack_28 == &DAT_0192e960) {
      plVar7 = (long *)*puStack_20;
      uStack_380 = uVar12;
      puStack_290 = puVar3;
      for (uVar16 = puStack_20[1]; 0 < (long)uVar16; uVar16 = uVar16 - 1) {
        if ((undefined8 *)*plVar7 == &DAT_01a233a0) {
          lStack_2f8 = plVar7[1];
          uStack_390 = uVar16;
          plStack_298 = plVar7;
          puVar3 = (undefined8 *)runtime_mapaccess1_faststr(4,&DAT_0192e960,uVar12,&DAT_01c397aa);
          if ((undefined8 *)*puVar3 == &DAT_0194e220) {
            plVar19 = *(long **)puVar3[1];
            lVar11 = ((undefined8 *)puVar3[1])[1];
          }
          else {
            lVar11 = 0;
            plVar19 = (long *)0x0;
          }
          puVar3 = puStack_290;
          uVar12 = uStack_380;
          uVar16 = uStack_390;
          plVar7 = plStack_298;
          if ((((lVar11 == 0xb) && (*plVar19 == 0x7365725f6c6f6f74)) &&
              ((short)plVar19[1] == 0x6c75)) && (*(char *)((long)plVar19 + 10) == 't')) {
            puVar3 = (undefined8 *)runtime_mapaccess1_faststr(0xb,0x7365725f6c6f6f74,&DAT_0194e220,&DAT_01c462ec);
            if ((undefined8 *)*puVar3 == &DAT_0194e220) {
              uVar4 = *(undefined8 *)puVar3[1];
              lVar11 = ((undefined8 *)puVar3[1])[1];
            }
            else {
              lVar11 = 0;
              uVar4 = 0;
            }
            puVar3 = puStack_290;
            uVar12 = uStack_380;
            uVar16 = uStack_390;
            plVar7 = plStack_298;
            if (lVar11 != 0) {
              puVar8 = (undefined1 *)runtime_mapassign_faststr(lVar11,lVar11,&DAT_0194e220,uVar4);
              *puVar8 = 1;
              puVar3 = puStack_290;
              uVar12 = uStack_380;
              uVar16 = uStack_390;
              plVar7 = plStack_298;
            }
          }
        }
        plVar7 = plVar7 + 2;
      }
    }
    puVar3 = puVar3 + 6;
  }
  FUN_00488cb4();
  auStack_268[0] = 0x8080808080808080;
  puStack_150 = auStack_268;
  uStack_158 = runtime_rand();
  puVar3 = puStack_358;
  puVar9 = puStack_358;
  for (uVar12 = uVar17; 0 < (long)uVar12; uVar12 = uVar12 - 1) {
    plStack_38 = (long *)*puVar3;
    plStack_30 = (long *)puVar3[1];
    puStack_28 = (undefined8 *)puVar3[2];
    puStack_20 = (undefined8 *)puVar3[3];
    uStack_18 = puVar3[4];
    uStack_10 = puVar3[5];
    if (puStack_28 == &DAT_0192e960) {
      plVar7 = (long *)*puStack_20;
      uStack_380 = uVar12;
      puStack_290 = puVar3;
      for (uVar16 = puStack_20[1]; 0 < (long)uVar16; uVar16 = uVar16 - 1) {
        if ((undefined8 *)*plVar7 == &DAT_01a233a0) {
          puVar10 = (undefined8 *)plVar7[1];
          uStack_390 = uVar16;
          puStack_300 = puVar10;
          plStack_298 = plVar7;
          puVar3 = (undefined8 *)runtime_mapaccess1_faststr();
          if ((undefined8 *)*puVar3 == &DAT_0194e220) {
            plVar19 = *(long **)puVar3[1];
            lVar11 = ((undefined8 *)puVar3[1])[1];
          }
          else {
            lVar11 = 0;
            plVar19 = (long *)0x0;
          }
          puVar3 = puStack_290;
          puVar9 = puStack_358;
          uVar12 = uStack_380;
          uVar16 = uStack_390;
          plVar7 = plStack_298;
          if ((lVar11 == 8) && (*plVar19 == 0x6573755f6c6f6f74)) {
            puVar3 = (undefined8 *)runtime_mapaccess1_faststr(2,0x6573755f6c6f6f74,&DAT_0194e220,&DAT_01c3896e);
            if ((undefined8 *)*puVar3 == &DAT_0194e220) {
              uStack_328 = *(undefined8 *)puVar3[1];
              lStack_3f8 = ((undefined8 *)puVar3[1])[1];
            }
            else {
              lStack_3f8 = 0;
              uStack_328 = 0;
            }
            puVar3 = (undefined8 *)runtime_mapaccess1_faststr(4,lStack_3f8,&DAT_0194e220,0x1c39796);
            if ((undefined8 *)*puVar3 == &DAT_0194e220) {
              uVar4 = *(undefined8 *)puVar3[1];
              lVar11 = ((undefined8 *)puVar3[1])[1];
            }
            else {
              lVar11 = 0;
              uVar4 = 0;
            }
            puVar3 = puStack_290;
            puVar9 = puStack_358;
            uVar12 = uStack_380;
            uVar16 = uStack_390;
            plVar7 = plStack_298;
            if ((lStack_3f8 != 0) && (lVar11 != 0)) {
              lStack_410 = lVar11;
              uStack_340 = uVar4;
              puVar3 = (undefined8 *)runtime_mapassign_faststr();
              puVar3[1] = lStack_410;
              if (DAT_02e5e450 != 0) {
                auVar21 = runtime_gcWriteBarrier2();
                puVar3 = auVar21._0_8_;
                *puVar10 = uStack_340;
                puVar10[1] = auVar21._8_8_;
              }
              *puVar3 = uStack_340;
              puVar3 = puStack_290;
              puVar9 = puStack_358;
              uVar12 = uStack_380;
              uVar16 = uStack_390;
              plVar7 = plStack_298;
            }
          }
        }
        plVar7 = plVar7 + 2;
      }
    }
    puVar3 = puVar3 + 6;
  }
  bVar1 = false;
  uVar12 = 0;
  plVar7 = (long *)0x0;
  uVar16 = 0;
  uVar14 = 0;
  lVar11 = 0;
  uVar13 = 0;
  do {
    if ((long)uVar17 < 1) {
      kiro2api_internal_logic_antigravity_mergeAdjacentRoles();
      return;
    }
    plStack_38 = (long *)*puVar9;
    plStack_30 = (long *)puVar9[1];
    puStack_28 = (undefined8 *)puVar9[2];
    puStack_20 = (undefined8 *)puVar9[3];
    uStack_18 = puVar9[4];
    uStack_10 = puVar9[5];
    plVar19 = plStack_30;
    plVar20 = plStack_38;
    if (((plStack_30 == (long *)&DAT_00000009) && (*plStack_38 == 0x6e61747369737361)) &&
       ((char)plStack_38[1] == 't')) {
      plVar19 = (long *)0x5;
      plVar20 = (long *)&DAT_01c3a594;
    }
    if (((plVar19 != (long *)0x6) || ((int)*plVar20 != 0x74737973)) ||
       (*(short *)((long)plVar20 + 4) != 0x6d65)) {
      if (plVar19 == (long *)0x0) {
        plVar19 = (long *)&DAT_00000004;
        plVar20 = (long *)&DAT_01c3978a;
      }
      uStack_380 = uVar17;
      plStack_360 = plVar20;
      puStack_290 = puVar9;
      if (((plVar19 == (long *)0x5) && ((int)*plVar20 == 0x65646f6d)) &&
         ((*(char *)((long)plVar20 + 4) == 'l' && (uVar12 != 0)))) {
        uVar17 = 0;
        lStack_368 = 0;
        uVar16 = 0;
        uStack_3d8 = uVar13;
        uStack_3d0 = uVar14;
        lStack_318 = lVar11;
        while (0 < (long)uVar12) {
          lStack_330 = *plVar7;
          lStack_400 = plVar7[1];
          plVar20 = plVar19;
          uStack_390 = uVar12;
          plStack_298 = plVar7;
          pcVar6 = (char *)runtime_mapaccess1_faststr();
          if (*pcVar6 == '\0') {
            plVar7 = (long *)runtime_mapaccess1_faststr(lStack_400);
            lStack_3e0 = plVar7[1];
            lStack_320 = *plVar7;
            lStack_2c8 = runtime_makemap_small();
            puVar3 = (undefined8 *)runtime_mapassign_faststr(0x10);
            *puVar3 = &DAT_0194e220;
            if (lStack_3e0 == 0) {
              lStack_320 = lStack_330;
              lStack_3e0 = lStack_400;
            }
            if (DAT_02e5e450 != 0) {
              lVar11 = puVar3[1];
              puVar3 = (undefined8 *)runtime_gcWriteBarrier1();
              *plVar20 = lVar11;
            }
            puVar3[1] = &PTR_DAT_01f3a2b0;
            lStack_2e8 = runtime_makemap_small();
            plStack_2d8 = (long *)runtime_convTstring();
            puVar3 = (undefined8 *)runtime_mapassign_faststr(4);
            *puVar3 = &DAT_0194e220;
            if (DAT_02e5e450 != 0) {
              auVar21 = runtime_gcWriteBarrier2();
              puVar3 = auVar21._0_8_;
              *plVar20 = (long)plStack_2d8;
              plVar20[1] = auVar21._8_8_;
            }
            puVar3[1] = plStack_2d8;
            lStack_2f0 = runtime_makemap_small();
            puVar3 = (undefined8 *)runtime_mapassign_faststr(6);
            *puVar3 = &DAT_0194e220;
            if (DAT_02e5e450 != 0) {
              auVar21 = runtime_gcWriteBarrier1();
              puVar3 = auVar21._0_8_;
              *plVar20 = auVar21._8_8_;
            }
            puVar3[1] = &PTR_DAT_01f3a2c0;
            puVar3 = (undefined8 *)runtime_mapassign_faststr(8);
            *puVar3 = &DAT_01a233a0;
            if (DAT_02e5e450 != 0) {
              lVar11 = puVar3[1];
              puVar3 = (undefined8 *)runtime_gcWriteBarrier2();
              *plVar20 = lStack_2f0;
              plVar20[1] = lVar11;
            }
            puVar3[1] = lStack_2f0;
            plStack_2d8 = (long *)runtime_convTstring();
            auVar21 = runtime_mapassign_faststr(2);
            *auVar21._0_8_ = &DAT_0194e220;
            if (DAT_02e5e450 != 0) {
              auVar21 = runtime_gcWriteBarrier2();
              *plVar20 = (long)plStack_2d8;
              plVar20[1] = auVar21._8_8_;
            }
            *(long **)(auVar21._0_8_ + 8) = plStack_2d8;
            puVar3 = (undefined8 *)runtime_mapassign_faststr(0x10,plStack_2d8,auVar21._8_8_,&DAT_01c4f1b3);
            *puVar3 = &DAT_01a233a0;
            if (DAT_02e5e450 != 0) {
              auVar21 = runtime_gcWriteBarrier2();
              puVar3 = auVar21._0_8_;
              *plVar20 = lStack_2e8;
              plVar20[1] = auVar21._8_8_;
            }
            puVar3[1] = lStack_2e8;
            uVar16 = uVar16 + 1;
            lVar11 = lStack_368;
            if (uVar17 < uVar16) {
              lVar11 = runtime_growslice(1);
            }
            if (DAT_02e5e450 != 0) {
              auVar21 = runtime_gcWriteBarrier2();
              lVar11 = auVar21._0_8_;
              *plVar20 = lStack_2c8;
              plVar20[1] = auVar21._8_8_;
            }
            *(long *)(lVar11 + -8 + uVar16 * 8) = lStack_2c8;
            lStack_368 = lVar11;
          }
          plVar7 = plStack_298 + 2;
          uVar12 = uStack_390 - 1;
        }
        uVar14 = uStack_3d0;
        lVar11 = lStack_318;
        uVar13 = uStack_3d8;
        if (uVar16 != 0) {
          plVar7 = plVar19;
          lStack_2c8 = runtime_makemap_small();
          puVar3 = (undefined8 *)runtime_mapassign_faststr(4);
          *puVar3 = &DAT_0194e220;
          if (DAT_02e5e450 != 0) {
            auVar21 = runtime_gcWriteBarrier1();
            puVar3 = auVar21._0_8_;
            *plVar7 = auVar21._8_8_;
          }
          puVar3[1] = &PTR_DAT_01f39720;
          plStack_298 = (long *)runtime_convTslice();
          puVar3 = (undefined8 *)runtime_mapassign_faststr();
          *puVar3 = &DAT_0192a2e0;
          if (DAT_02e5e450 != 0) {
            lVar11 = puVar3[1];
            puVar3 = (undefined8 *)runtime_gcWriteBarrier2();
            *plVar7 = (long)plStack_298;
            plVar7[1] = lVar11;
          }
          puVar3[1] = plStack_298;
          uVar13 = uStack_3d8 + 1;
          lVar11 = lStack_318;
          uVar14 = uStack_3d0;
          if (uStack_3d0 < uVar13) {
            lVar11 = runtime_growslice(1,&DAT_01a233a0);
          }
          if (DAT_02e5e450 != 0) {
            auVar21 = runtime_gcWriteBarrier2();
            lVar11 = auVar21._0_8_;
            *plVar7 = lStack_2c8;
            plVar7[1] = auVar21._8_8_;
          }
          *(long *)(lVar11 + -8 + uVar13 * 8) = lStack_2c8;
        }
        uVar16 = 0;
        uVar12 = 0;
        plVar7 = (long *)0x0;
      }
      uStack_398 = uVar13;
      uStack_390 = uVar14;
      lStack_2c0 = lVar11;
      if (puStack_28 == &DAT_0192e960) {
        plVar19 = (long *)*puStack_20;
        lStack_3c8 = puStack_20[1];
        plStack_310 = plVar19;
        for (lStack_3a0 = lStack_3c8; 0 < lStack_3a0; lStack_3a0 = lStack_3a0 + -1) {
          plVar20 = plVar19;
          if ((undefined8 *)*plVar19 == &DAT_01a233a0) {
            lStack_308 = plVar19[1];
            uStack_3c0 = uVar16;
            uStack_3b8 = uVar12;
            plStack_2d0 = plVar7;
            plStack_298 = plVar19;
            puVar3 = (undefined8 *)runtime_mapaccess1_faststr(4,plVar7,uVar12,&DAT_01c397aa);
            if ((undefined8 *)*puVar3 == &DAT_0194e220) {
              plVar15 = *(long **)puVar3[1];
              lVar11 = ((undefined8 *)puVar3[1])[1];
            }
            else {
              lVar11 = 0;
              plVar15 = (long *)0x0;
            }
            if ((lVar11 == 8) && (*plVar15 == 0x6573755f6c6f6f74)) {
              puVar3 = (undefined8 *)runtime_mapaccess1_faststr(2,8,&DAT_0194e220,&DAT_01c3896e);
              uVar17 = uStack_3b8;
              if ((undefined8 *)*puVar3 == &DAT_0194e220) {
                lVar11 = *(long *)puVar3[1];
                lVar5 = ((long *)puVar3[1])[1];
              }
              else {
                lVar5 = 0;
                lVar11 = 0;
              }
              uVar12 = uStack_3b8;
              plVar7 = plStack_2d0;
              uVar16 = uStack_3c0;
              plVar20 = plStack_298;
              if (lVar5 != 0) {
                uVar12 = uStack_3b8 + 1;
                if (uStack_3c0 < uVar12) {
                  lStack_408 = lVar5;
                  lStack_338 = lVar11;
                  if (((2 < (long)uVar12) || (bVar1)) || (uStack_3b8 != 0)) {
                    plVar7 = (long *)runtime_growslice(1);
                    lVar5 = lStack_408;
                    lVar11 = lStack_338;
                  }
                  else {
                    lStack_288 = in_XMM15_Qa;
                    uStack_280 = in_XMM15_Qb;
                    lStack_278 = in_XMM15_Qa;
                    uStack_270 = in_XMM15_Qb;
                    bVar1 = true;
                    plVar7 = &lStack_288;
                    uVar16 = 2;
                  }
                }
                lVar18 = uVar17 * 0x10;
                plVar7[uVar17 * 2 + 1] = lVar5;
                if (DAT_02e5e450 != 0) {
                  auVar21 = runtime_gcWriteBarrier2();
                  plVar7 = auVar21._0_8_;
                  *plVar19 = lVar11;
                  plVar19[1] = auVar21._8_8_;
                }
                *(long *)((long)plVar7 + lVar18) = lVar11;
                plVar20 = plStack_298;
              }
            }
            else {
              uVar12 = uStack_3b8;
              plVar7 = plStack_2d0;
              uVar16 = uStack_3c0;
              plVar20 = plStack_298;
              if ((lVar11 == 0xb) &&
                 (((*plVar15 == 0x7365725f6c6f6f74 && ((short)plVar15[1] == 0x6c75)) &&
                  (*(char *)((long)plVar15 + 10) == 't')))) {
                puVar3 = (undefined8 *)
                         runtime_mapaccess1_faststr(0xb,0x7365725f6c6f6f74,&DAT_0194e220,&DAT_01c462ec,plVar15,
                                      0x6573755f6c6f6f74);
                if ((undefined8 *)*puVar3 == &DAT_0194e220) {
                  uVar4 = *(undefined8 *)puVar3[1];
                  lVar11 = ((undefined8 *)puVar3[1])[1];
                }
                else {
                  lVar11 = 0;
                  uVar4 = 0;
                }
                uVar12 = uStack_3b8;
                plVar7 = plStack_2d0;
                uVar16 = uStack_3c0;
                plVar20 = plStack_298;
                if (lVar11 != 0) {
                  plVar19 = plStack_2d0;
                  uStack_378 = uVar4;
                  for (lVar5 = 0; uVar16 = uStack_3c0, plVar20 = plStack_298, lVar5 < (long)uVar12;
                      lVar5 = lVar5 + 1) {
                    if ((lVar11 == plVar19[1]) &&
                       (lStack_3f0 = lVar5, plStack_2d8 = plVar19, cVar2 = runtime_memequal(),
                       lVar5 = lStack_3f0, plVar19 = plStack_2d8, plVar7 = plStack_2d0,
                       uVar12 = uStack_3b8, cVar2 != '\0')) {
                      uVar12 = uStack_3b8 - 1;
                      uVar14 = uStack_3b8 - lStack_3f0;
                      puVar8 = (undefined1 *)
                               ((long)plStack_2d0 +
                               ((long)-((uStack_3c0 - lStack_3f0) + -1) >> 0x3f &
                               (lStack_3f0 + 1) * 0x10));
                      uVar17 = uVar14 - 1;
                      uVar16 = uStack_3c0;
                      if (uStack_3c0 < uVar12) {
                        uStack_3b0 = uVar14;
                        uStack_3a8 = uVar17;
                        puStack_2e0 = puVar8;
                        plVar7 = (long *)runtime_growslice(uVar17,&DAT_0194e220);
                        uVar17 = uStack_3a8;
                        uVar14 = uStack_3b0;
                        puVar8 = puStack_2e0;
                      }
                      uStack_428 = uVar16;
                      plStack_350 = plVar7;
                      runtime_typedslicecopy(puVar8,uVar17,uVar12,uVar12 - (uStack_3b8 - uVar14),puVar8,
                                   (uStack_3b8 - uVar14) * 0x10);
                      plVar7 = plStack_350;
                      uVar16 = uStack_428;
                      plVar20 = plStack_298;
                      break;
                    }
                    plVar19 = plVar19 + 2;
                  }
                }
              }
            }
          }
          plVar19 = plVar20 + 2;
        }
      }
      else {
        lStack_3c8 = 0;
        plStack_310 = (long *)0x0;
      }
      puVar3 = puStack_28;
      puVar10 = puStack_20;
      uStack_428 = uVar16;
      plStack_350 = plVar7;
      uVar4 = kiro2api_internal_logic_antigravity_sAntigravity_convertContentToPartsWithMapping(auStack_160);
      puVar9 = puStack_290;
      uVar17 = uStack_380;
      plVar7 = plStack_350;
      uVar16 = uStack_428;
      uVar14 = uStack_390;
      lVar11 = lStack_2c0;
      uVar13 = uStack_398;
      if (puVar3 != (undefined8 *)0x0) {
        puStack_420 = puVar3;
        puStack_418 = puVar10;
        uStack_348 = uVar4;
        lStack_2c8 = runtime_makemap_small();
        plStack_298 = (long *)runtime_convTstring();
        puVar3 = (undefined8 *)runtime_mapassign_faststr(4);
        *puVar3 = &DAT_0194e220;
        if (DAT_02e5e450 != 0) {
          auVar21 = runtime_gcWriteBarrier2();
          puVar3 = auVar21._0_8_;
          *plVar19 = (long)plStack_298;
          plVar19[1] = auVar21._8_8_;
        }
        puVar3[1] = plStack_298;
        plStack_298 = (long *)runtime_convTslice();
        puVar3 = (undefined8 *)runtime_mapassign_faststr(5);
        *puVar3 = &DAT_0192a2e0;
        if (DAT_02e5e450 != 0) {
          lVar11 = puVar3[1];
          puVar3 = (undefined8 *)runtime_gcWriteBarrier2();
          *plVar19 = (long)plStack_298;
          plVar19[1] = lVar11;
        }
        puVar3[1] = plStack_298;
        uVar13 = uStack_398 + 1;
        lVar11 = lStack_2c0;
        uVar14 = uStack_390;
        if (uStack_390 < uVar13) {
          lVar11 = runtime_growslice(1,&DAT_01a233a0);
        }
        if (DAT_02e5e450 != 0) {
          auVar21 = runtime_gcWriteBarrier2();
          lVar11 = auVar21._0_8_;
          *plVar19 = lStack_2c8;
          plVar19[1] = auVar21._8_8_;
        }
        *(long *)(lVar11 + -8 + uVar13 * 8) = lStack_2c8;
        puVar9 = puStack_290;
        uVar17 = uStack_380;
        plVar7 = plStack_350;
        uVar16 = uStack_428;
      }
    }
    puVar9 = puVar9 + 6;
    uVar17 = uVar17 - 1;
  } while( true );
}




// === antigravity.doStreamRequest @ 0x17b4940 ===

/* WARNING: Removing unreachable block (ram,0x017b52f7) */
/* WARNING: Removing unreachable block (ram,0x017b5375) */
/* WARNING: Removing unreachable block (ram,0x017b5393) */
/* WARNING: Removing unreachable block (ram,0x017b5389) */
/* WARNING: Removing unreachable block (ram,0x017b5398) */
/* WARNING: Removing unreachable block (ram,0x017b539a) */
/* WARNING: Removing unreachable block (ram,0x017b53ac) */
/* WARNING: Removing unreachable block (ram,0x017b5404) */
/* WARNING: Removing unreachable block (ram,0x017b53f2) */
/* WARNING: Removing unreachable block (ram,0x017b5420) */
/* WARNING: Removing unreachable block (ram,0x017b53a4) */
/* WARNING: Removing unreachable block (ram,0x017b5434) */
/* WARNING: Removing unreachable block (ram,0x017b5487) */
/* WARNING: Removing unreachable block (ram,0x017b546d) */
/* WARNING: Removing unreachable block (ram,0x017b54af) */
/* WARNING: Removing unreachable block (ram,0x017b5505) */
/* WARNING: Removing unreachable block (ram,0x017b54fb) */
/* WARNING: Removing unreachable block (ram,0x017b5515) */
/* WARNING: Removing unreachable block (ram,0x017b5552) */
/* WARNING: Removing unreachable block (ram,0x017b57ae) */
/* WARNING: Removing unreachable block (ram,0x017b57c5) */
/* WARNING: Removing unreachable block (ram,0x017b57ce) */
/* WARNING: Removing unreachable block (ram,0x017b57f5) */
/* WARNING: Removing unreachable block (ram,0x017b55c1) */
/* WARNING: Removing unreachable block (ram,0x017b5629) */
/* WARNING: Removing unreachable block (ram,0x017b5655) */
/* WARNING: Removing unreachable block (ram,0x017b572a) */
/* WARNING: Removing unreachable block (ram,0x017b573c) */
/* WARNING: Removing unreachable block (ram,0x017b5754) */
/* WARNING: Removing unreachable block (ram,0x017b566d) */
/* WARNING: Removing unreachable block (ram,0x017b569f) */
/* WARNING: Removing unreachable block (ram,0x017b569b) */
/* WARNING: Removing unreachable block (ram,0x017b56c0) */
/* WARNING: Removing unreachable block (ram,0x017b56c4) */
/* WARNING: Removing unreachable block (ram,0x017b56ca) */
/* WARNING: Removing unreachable block (ram,0x017b5703) */
/* WARNING: Removing unreachable block (ram,0x017b56df) */
/* WARNING: Removing unreachable block (ram,0x017b5710) */
/* WARNING: Removing unreachable block (ram,0x017b579b) */
/* WARNING: Removing unreachable block (ram,0x017b534d) */
/* WARNING: Removing unreachable block (ram,0x017b535e) */
/* WARNING: Removing unreachable block (ram,0x017b58ee) */
/* WARNING: Removing unreachable block (ram,0x017b5935) */
/* WARNING: Removing unreachable block (ram,0x017b5905) */
/* WARNING: Removing unreachable block (ram,0x017b590e) */
/* WARNING: Removing unreachable block (ram,0x017b57ff) */

undefined8
antigravity_doStreamRequest
          (long param_1,long param_2,undefined8 param_3,long param_4,undefined8 param_5,
          undefined8 param_6)

{
  undefined8 uVar1;
  undefined8 *puVar2;
  undefined8 **ppuVar3;
  long lVar4;
  ulong uVar5;
  long lVar6;
  undefined8 extraout_RDX;
  undefined8 extraout_RDX_00;
  undefined8 extraout_RDX_01;
  long extraout_RDX_02;
  undefined8 extraout_RDX_03;
  char cVar7;
  long unaff_RBX;
  long lVar8;
  ulong uVar9;
  undefined8 uVar10;
  long lVar11;
  ulong uVar12;
  long lVar13;
  undefined1 (*in_R11) [16];
  long unaff_R14;
  undefined8 in_XMM15_Qa;
  ulong in_XMM15_Qb;
  undefined1 auVar14 [16];
  undefined1 auVar15 [16];
  undefined1 auVar16 [16];
  undefined1 auVar17 [16];
  long lStack0000000000000020;
  long lStack0000000000000028;
  long lStack0000000000000030;
  long lStack0000000000000038;
  undefined8 uStack0000000000000040;
  undefined8 uStack0000000000000048;
  undefined1 (*pauStack0000000000000058) [16];
  undefined8 **ppuStack_1f0;
  long lStack_1e8;
  ulong uStack_1d8;
  ulong uStack_1d0;
  long lStack_1b8;
  long lStack_1b0;
  undefined8 uStack_190;
  undefined8 *puStack_188;
  undefined8 uStack_178;
  undefined8 uStack_170;
  long lStack_160;
  undefined8 uStack_158;
  long lStack_150;
  undefined8 *puStack_130;
  long lStack_128;
  long lStack_120;
  undefined8 uStack_118;
  undefined8 uStack_110;
  long lStack_70;
  undefined8 uStack_68;
  ulong uStack_60;
  long lStack_58;
  long lStack_50;
  long lStack_48;
  undefined8 uStack_40;
  undefined8 uStack_38;
  undefined8 *puStack_30;
  undefined8 uStack_28;
  undefined8 *puStack_20;
  undefined **ppuStack_18;
  
  lStack0000000000000028 = param_4;
  lStack0000000000000020 = unaff_RBX;
  lStack0000000000000038 = param_2;
  lStack0000000000000030 = param_1;
  uStack0000000000000040 = param_5;
  uStack0000000000000048 = param_6;
  while (&ppuStack_1f0 <= *(undefined8 ****)(unaff_R14 + 0x10)) {
    pauStack0000000000000058 = in_R11;
    runtime_morestack_noctxt();
    in_R11 = pauStack0000000000000058;
  }
  uStack_28 = runtime_convTstring();
  puStack_30 = &DAT_0194e220;
  puStack_20 = &DAT_0194e220;
  ppuStack_18 = &PTR_DAT_01f3a2e0;
  ppuVar3 = &puStack_30;
  lVar11 = 2;
  uVar10 = 2;
  uStack_190 = fmt_Sprintf();
  lVar13 = lStack0000000000000038;
  auVar14 = encoding_json_Marshal();
  uStack_170 = auVar14._0_8_;
  if (lVar11 == 0) {
    ppuStack_1f0 = ppuVar3;
    lStack_58 = github_com_imroc_req_v3_Client_Clone();
    lVar11 = lStack0000000000000028;
    lStack_50 = lStack0000000000000020;
    lStack_48 = lStack0000000000000028;
    *(undefined8 *)(*(long *)(lStack_58 + 200) + 0x28) = 1800000000000;
    uStack_158 = kiro2api_internal_logic_antigravity_getProxyURL();
    lStack_1e8 = lVar11;
    if (lVar11 != 0) {
      kiro2api_internal_proxy_Client_SetProxy(*(undefined8 *)(lStack0000000000000030 + 8),
                   *(undefined8 *)(lStack0000000000000030 + 0x10),lStack0000000000000030,lVar11);
      uStack_110 = *(undefined8 *)(lStack0000000000000030 + 8);
      uStack_1d0 = *(ulong *)(lStack0000000000000030 + 0x10);
      puVar2 = (undefined8 *)runtime_newobject();
      *puVar2 = &LAB_017b5ae0;
      puVar2[2] = lStack_1e8;
      if (DAT_02e5e450 != 0) {
        puVar2 = (undefined8 *)runtime_gcWriteBarrier2();
        *(undefined8 *)*in_R11 = uStack_158;
        *(undefined8 *)(*in_R11 + 8) = uStack_110;
      }
      puVar2[1] = uStack_158;
      puVar2[4] = uStack_1d0;
      puVar2[3] = uStack_110;
      runtime_newproc();
    }
    lStack_150 = lStack_58;
    if (*(undefined8 **)(lStack_58 + 0x60) == (undefined8 *)0x0) {
      lStack_1b8 = 0;
    }
    else {
      puStack_188 = *(undefined8 **)(lStack_58 + 0x60);
      puVar2 = (undefined8 *)runtime_newobject();
      *puVar2 = *puStack_188;
      auVar14._8_8_ = puStack_188[1];
      auVar14._0_8_ = puVar2;
      puVar2 = puStack_188;
      if (DAT_02e5e450 != 0) {
        auVar14 = runtime_gcWriteBarrier1();
        *(long *)*in_R11 = auVar14._8_8_;
      }
      lStack_1b8 = auVar14._0_8_;
      *(long *)(lStack_1b8 + 8) = auVar14._8_8_;
      uStack_1d8 = *(long *)(lStack_1b8 + 0x18);
      uVar9 = *(ulong *)(lStack_1b8 + 0x20);
      uStack_1d0 = puVar2[3];
      uVar5 = uStack_1d8 + uStack_1d0;
      uVar10 = *(undefined8 *)(lStack_1b8 + 0x10);
      uStack_118 = puVar2[2];
      if (uVar9 < uVar5) {
        uVar10 = runtime_growslice(uStack_1d0,&DAT_019ea040);
      }
      lVar4 = uVar5 - uStack_1d8;
      lVar6 = uStack_1d8 - uVar9;
      in_R11 = (undefined1 (*) [16])(uStack_1d8 << 3);
      uStack_1d8 = uVar9;
      lVar11 = uStack_1d0;
      uStack_1d0 = uVar5;
      uVar1 = uStack_118;
      uStack_118 = uVar10;
      runtime_typedslicecopy(uVar1,lVar11,lVar6 >> 0x3f & (ulong)in_R11,lVar4);
      *(ulong *)(lStack_1b8 + 0x18) = uStack_1d0;
      *(ulong *)(lStack_1b8 + 0x20) = uStack_1d8;
      lVar11 = lStack_1b8;
      if (DAT_02e5e450 != 0) {
        runtime_gcWriteBarrier2();
        *(undefined8 *)*in_R11 = uStack_118;
        *(undefined8 *)(*in_R11 + 8) = extraout_RDX;
      }
      *(undefined8 *)(lVar11 + 0x10) = uStack_118;
      uStack_1d8 = *(long *)(lVar11 + 0x30);
      uVar9 = *(ulong *)(lVar11 + 0x38);
      uStack_1d0 = puStack_188[6];
      uVar5 = uStack_1d8 + uStack_1d0;
      lVar11 = *(long *)(lVar11 + 0x28);
      lStack_120 = puStack_188[5];
      if (uVar9 < uVar5) {
        lVar11 = runtime_growslice(uStack_1d0,&DAT_019cbd00);
      }
      lVar8 = uVar5 - uStack_1d8;
      lVar6 = uStack_1d8 - uVar9;
      uVar12 = uStack_1d8 << 3;
      uStack_1d8 = uVar5;
      lVar4 = uStack_1d0;
      uStack_1d0 = uVar9;
      uVar10 = lStack_120;
      lStack_120 = lVar11;
      runtime_typedslicecopy(uVar10,lVar4,(lVar6 >> 0x3f & uVar12) + lVar11,lVar8);
      *(ulong *)(lStack_1b8 + 0x30) = uStack_1d8;
      *(ulong *)(lStack_1b8 + 0x38) = uStack_1d0;
      if (DAT_02e5e450 != 0) {
        uVar10 = *(undefined8 *)(lStack_1b8 + 0x28);
        runtime_gcWriteBarrier2();
        *(long *)*in_R11 = lStack_120;
        *(undefined8 *)(*in_R11 + 8) = uVar10;
      }
      *(long *)(lStack_1b8 + 0x28) = lStack_120;
    }
    lVar11 = runtime_newobject();
    if (DAT_02e5e450 != 0) {
      lVar11 = runtime_gcWriteBarrier2();
      *(long *)*in_R11 = lStack_150;
      *(long *)(*in_R11 + 8) = lStack_1b8;
    }
    auVar15._8_8_ = lStack_50;
    auVar15._0_8_ = lVar11;
    *(long *)(lVar11 + 0xf8) = lStack_150;
    *(long *)(lVar11 + 0x130) = lStack_1b8;
    if (lStack_50 != 0) {
      *(long *)(lVar11 + 0x160) = lStack_50;
      lVar11 = lStack_48;
      if (DAT_02e5e450 != 0) {
        auVar15 = runtime_gcWriteBarrier1();
        *(long *)*in_R11 = lVar11;
      }
      *(long *)(auVar15._0_8_ + 0x168) = lVar11;
    }
    lStack_70 = auVar15._0_8_;
    uStack_68 = in_XMM15_Qa;
    uStack_60 = in_XMM15_Qb;
    if (lStack_1e8 != 0) {
      kiro2api_internal_proxy_Request_SetProxy(*(undefined8 *)(lStack0000000000000030 + 8),
                   *(undefined8 *)(lStack0000000000000030 + 0x10));
      auVar15._8_8_ = extraout_RDX_00;
      auVar15._0_8_ = lStack_70;
    }
    lStack_70 = auVar15._0_8_;
    github_com_imroc_req_v3_Request_SetHeader(&DAT_01c4edb3,0x10,auVar15._8_8_,0xc);
    github_com_imroc_req_v3_Request_SetHeader(&DAT_01c6c635,0x20,extraout_RDX_01,10);
    lStack_128 = lStack_70;
    auVar14 = runtime_concatstring2(*(undefined8 *)(lStack0000000000000030 + 0x28),
                           *(undefined8 *)(lStack0000000000000030 + 0x30),lStack0000000000000030,7);
    github_com_imroc_req_v3_Request_SetHeader(auVar14._0_8_,&DAT_01c3ddc9,auVar14._8_8_,0xd);
    *(long *)(lStack_70 + 0xc0) = lVar13;
    *(undefined8 ***)(lStack_70 + 200) = ppuStack_1f0;
    lStack_160 = lStack_70;
    if (DAT_02e5e450 != 0) {
      uVar10 = *(undefined8 *)(lStack_70 + 0xb8);
      runtime_gcWriteBarrier2();
      *(undefined8 *)*in_R11 = uStack_170;
      *(undefined8 *)(*in_R11 + 8) = uVar10;
      lStack_160 = extraout_RDX_02;
    }
    *(undefined8 *)(lStack_160 + 0xb8) = uStack_170;
    puVar2 = (undefined8 *)runtime_newobject();
    auVar16._8_8_ = lStack_160;
    auVar16._0_8_ = puVar2;
    *puVar2 = &LAB_017b5aa0;
    puVar2[2] = lVar13;
    puVar2[3] = ppuStack_1f0;
    if (DAT_02e5e450 != 0) {
      uVar10 = *(undefined8 *)(lStack_160 + 0xd0);
      auVar16 = runtime_gcWriteBarrier3();
      *(undefined8 *)*in_R11 = uStack_170;
      *(long *)(*in_R11 + 8) = auVar16._0_8_;
      *(undefined8 *)in_R11[1] = uVar10;
    }
    *(undefined8 *)(auVar16._0_8_ + 8) = uStack_170;
    *(long *)(auVar16._8_8_ + 0xd0) = auVar16._0_8_;
    uStack_178 = *(undefined8 *)(lStack0000000000000038 + 0x50);
    puVar2 = (undefined8 *)runtime_mapaccess1_faststr(0x10);
    if ((undefined8 *)*puVar2 == &DAT_01a233a0) {
      cVar7 = (char)puVar2[1];
      runtime_mapaccess2_faststr(0xe,puVar2[1],&DAT_01a233a0,&DAT_01c4b839);
    }
    else {
      cVar7 = '\0';
    }
    uVar10 = uStack_178;
    runtime_mapaccess2_faststr(5);
    if ((cVar7 != '\0') && ((char)uVar10 != '\0')) {
      github_com_imroc_req_v3_Request_SetHeader(&DAT_01c6a793,0x1f,cVar7,0xe);
    }
    if (uStack_60 != 0) {
      uStack_1d0 = uStack_60;
      uStack_110 = uStack_68;
      lStack_1b0 = *(long *)(lStack_70 + 0xf8);
      puVar2 = (undefined8 *)runtime_newobject();
      *puVar2 = &LAB_017b5a40;
      puVar2[2] = uStack_1d0;
      if (DAT_02e5e450 != 0) {
        puVar2 = (undefined8 *)runtime_gcWriteBarrier1();
        *(undefined8 *)*in_R11 = uStack_110;
      }
      puVar2[1] = uStack_110;
      uVar5 = *(ulong *)(lStack_1b0 + 0xf8);
      uVar9 = *(long *)(lStack_1b0 + 0xf0) + 1;
      auVar17._8_8_ = lStack_1b0;
      auVar17._0_8_ = *(undefined8 *)(lStack_1b0 + 0xe8);
      if (uVar5 < uVar9) {
        puStack_130 = puVar2;
        uVar10 = runtime_growslice(1,&DAT_019ea0a0);
        auVar17._8_8_ = lStack_1b0;
        auVar17._0_8_ = uVar10;
        *(ulong *)(lStack_1b0 + 0xf8) = uVar5;
        if (DAT_02e5e450 != 0) {
          uVar10 = *(undefined8 *)(lStack_1b0 + 0xe8);
          auVar17 = runtime_gcWriteBarrier2();
          *(long *)*in_R11 = auVar17._0_8_;
          *(undefined8 *)(*in_R11 + 8) = uVar10;
        }
        *(long *)(auVar17._8_8_ + 0xe8) = auVar17._0_8_;
        puVar2 = puStack_130;
      }
      lVar13 = auVar17._0_8_;
      *(ulong *)(auVar17._8_8_ + 0xf0) = uVar9;
      if (DAT_02e5e450 != 0) {
        auVar14 = runtime_gcWriteBarrier2();
        puVar2 = auVar14._0_8_;
        *in_R11 = auVar14;
      }
      *(undefined8 **)(lVar13 + -8 + uVar9 * 8) = puVar2;
    }
    uVar10 = 4;
    github_com_imroc_req_v3_Request_Send(uStack_190,0x23);
    uStack_40 = DAT_01c3979a;
    uStack_38 = uVar10;
    uVar10 = fmt_Errorf(1,1,extraout_RDX_03,&uStack_40);
    return uVar10;
  }
  uStack_40 = *(undefined8 *)(lVar11 + 8);
  uStack_38 = uVar10;
  uVar10 = fmt_Errorf(1,1,auVar14._8_8_,&uStack_40);
  return uVar10;
}




// === antigravity.buildAntigravityRequest @ 0x17af640 ===

long antigravity_buildAntigravityRequest
               (int *param_1,ulong param_2,undefined8 param_3,long param_4,byte param_5)

{
  undefined8 *puVar1;
  long lVar2;
  undefined8 uVar3;
  undefined8 uVar4;
  long lVar5;
  ulong uVar6;
  undefined *puVar7;
  long unaff_RBX;
  int *piVar8;
  undefined8 *in_R11;
  long unaff_R14;
  undefined1 auVar9 [16];
  undefined1 auVar10 [16];
  long lStack0000000000000010;
  long lStack0000000000000018;
  int *piStack0000000000000020;
  ulong uStack0000000000000028;
  byte bStack0000000000000030;
  undefined8 uStack_88;
  undefined8 uStack_80;
  undefined8 *puStack_78;
  undefined8 uStack_70;
  undefined *puStack_68;
  undefined8 uStack_60;
  undefined8 uStack_58;
  long lStack_50;
  undefined8 uStack_48;
  undefined8 *puStack_40;
  undefined8 uStack_38;
  undefined8 uStack_30;
  undefined8 uStack_28;
  undefined8 uStack_20;
  undefined8 uStack_18;
  int *piStack_10;
  
  lStack0000000000000018 = param_4;
  lStack0000000000000010 = unaff_RBX;
  uStack0000000000000028 = param_2;
  piStack0000000000000020 = param_1;
  bStack0000000000000030 = param_5;
  while (&uStack_88 <= *(undefined8 **)(unaff_R14 + 0x10)) {
    runtime_morestack_noctxt();
  }
  lVar5 = *(long *)(lStack0000000000000010 + 0x10);
  uStack_58 = antigravity_convertMessagesToContents(*(undefined8 *)(lStack0000000000000010 + 0x20));
  if (bStack0000000000000030 == 0) {
    for (lVar2 = 0; lVar2 < lVar5; lVar2 = lVar2 + 1) {
      kiro2api_internal_logic_antigravity_cleanThinkingFieldsRecursive();
    }
  }
  uStack_70 = runtime_makemap_small();
  piStack_10 = (int *)runtime_convTslice();
  puVar1 = (undefined8 *)runtime_mapassign_faststr(8);
  *puVar1 = &DAT_0192a2e0;
  if (DAT_02e5e450 != 0) {
    auVar9 = runtime_gcWriteBarrier2();
    puVar1 = auVar9._0_8_;
    *in_R11 = piStack_10;
    in_R11[1] = auVar9._8_8_;
  }
  puVar1[1] = piStack_10;
  uStack_18 = runtime_makemap_small();
  puVar1 = (undefined8 *)runtime_mapassign_faststr(8);
  *puVar1 = &DAT_0194e220;
  if (DAT_02e5e450 != 0) {
    auVar9 = runtime_gcWriteBarrier1();
    puVar1 = auVar9._0_8_;
    *in_R11 = auVar9._8_8_;
  }
  puVar1[1] = &PTR_DAT_01f3a240;
  puVar1 = (undefined8 *)runtime_mapassign_faststr(9);
  *puVar1 = &DAT_0194e220;
  if (DAT_02e5e450 != 0) {
    uVar3 = puVar1[1];
    puVar1 = (undefined8 *)runtime_gcWriteBarrier1();
    *in_R11 = uVar3;
  }
  puVar1[1] = &PTR_DAT_01f3a250;
  uStack_20 = runtime_makemap_small();
  puVar1 = (undefined8 *)runtime_mapassign_faststr(8);
  *puVar1 = &DAT_0194e220;
  if (DAT_02e5e450 != 0) {
    auVar9 = runtime_gcWriteBarrier1();
    puVar1 = auVar9._0_8_;
    *in_R11 = auVar9._8_8_;
  }
  puVar1[1] = &PTR_DAT_01f3a260;
  puVar1 = (undefined8 *)runtime_mapassign_faststr(9);
  *puVar1 = &DAT_0194e220;
  if (DAT_02e5e450 != 0) {
    uVar3 = puVar1[1];
    puVar1 = (undefined8 *)runtime_gcWriteBarrier1();
    *in_R11 = uVar3;
  }
  puVar1[1] = &PTR_DAT_01f3a250;
  uStack_28 = runtime_makemap_small();
  puVar1 = (undefined8 *)runtime_mapassign_faststr(8);
  *puVar1 = &DAT_0194e220;
  if (DAT_02e5e450 != 0) {
    auVar9 = runtime_gcWriteBarrier1();
    puVar1 = auVar9._0_8_;
    *in_R11 = auVar9._8_8_;
  }
  puVar1[1] = &PTR_DAT_01f3a270;
  puVar1 = (undefined8 *)runtime_mapassign_faststr(9);
  *puVar1 = &DAT_0194e220;
  if (DAT_02e5e450 != 0) {
    uVar3 = puVar1[1];
    puVar1 = (undefined8 *)runtime_gcWriteBarrier1();
    *in_R11 = uVar3;
  }
  puVar1[1] = &PTR_DAT_01f3a250;
  uStack_30 = runtime_makemap_small();
  puVar1 = (undefined8 *)runtime_mapassign_faststr(8);
  *puVar1 = &DAT_0194e220;
  if (DAT_02e5e450 != 0) {
    auVar9 = runtime_gcWriteBarrier1();
    puVar1 = auVar9._0_8_;
    *in_R11 = auVar9._8_8_;
  }
  puVar1[1] = &PTR_DAT_01f3a280;
  puVar1 = (undefined8 *)runtime_mapassign_faststr(9);
  *puVar1 = &DAT_0194e220;
  if (DAT_02e5e450 != 0) {
    uVar3 = puVar1[1];
    puVar1 = (undefined8 *)runtime_gcWriteBarrier1();
    *in_R11 = uVar3;
  }
  puVar1[1] = &PTR_DAT_01f3a250;
  uStack_38 = runtime_makemap_small();
  puVar1 = (undefined8 *)runtime_mapassign_faststr(8);
  *puVar1 = &DAT_0194e220;
  if (DAT_02e5e450 != 0) {
    auVar9 = runtime_gcWriteBarrier1();
    puVar1 = auVar9._0_8_;
    *in_R11 = auVar9._8_8_;
  }
  puVar1[1] = &PTR_DAT_01f3a290;
  puVar1 = (undefined8 *)runtime_mapassign_faststr(9);
  *puVar1 = &DAT_0194e220;
  if (DAT_02e5e450 != 0) {
    uVar3 = puVar1[1];
    puVar1 = (undefined8 *)runtime_gcWriteBarrier1();
    *in_R11 = uVar3;
  }
  puVar1[1] = &PTR_DAT_01f3a250;
  puVar1 = (undefined8 *)runtime_newobject();
  if (DAT_02e5e450 != 0) {
    puVar1 = (undefined8 *)runtime_gcWriteBarrier5();
    *in_R11 = uStack_18;
    in_R11[1] = uStack_20;
    in_R11[2] = uStack_28;
    in_R11[3] = uStack_30;
    in_R11[4] = uStack_38;
  }
  *puVar1 = uStack_18;
  puVar1[1] = uStack_20;
  puVar1[2] = uStack_28;
  puVar1[3] = uStack_30;
  puVar1[4] = uStack_38;
  piStack_10 = (int *)runtime_convTslice();
  puVar1 = (undefined8 *)runtime_mapassign_faststr(0xe);
  *puVar1 = &DAT_0192a2e0;
  if (DAT_02e5e450 != 0) {
    uVar3 = puVar1[1];
    puVar1 = (undefined8 *)runtime_gcWriteBarrier2();
    *in_R11 = piStack_10;
    in_R11[1] = uVar3;
  }
  puVar1[1] = piStack_10;
  uStack_18 = runtime_makemap_small();
  piStack_10 = (int *)runtime_convTstring();
  puVar1 = (undefined8 *)runtime_mapassign_faststr(4);
  *puVar1 = &DAT_0194e220;
  if (DAT_02e5e450 != 0) {
    auVar9 = runtime_gcWriteBarrier2();
    puVar1 = auVar9._0_8_;
    *in_R11 = piStack_10;
    in_R11[1] = auVar9._8_8_;
  }
  puVar1[1] = piStack_10;
  uStack_20 = runtime_makemap_small();
  piStack_10 = (int *)runtime_convTstring();
  puVar1 = (undefined8 *)runtime_mapassign_faststr(4);
  *puVar1 = &DAT_0194e220;
  if (DAT_02e5e450 != 0) {
    auVar9 = runtime_gcWriteBarrier2();
    puVar1 = auVar9._0_8_;
    *in_R11 = piStack_10;
    in_R11[1] = auVar9._8_8_;
  }
  puVar1[1] = piStack_10;
  puStack_78 = (undefined8 *)runtime_newobject();
  if (DAT_02e5e450 != 0) {
    puStack_78 = (undefined8 *)runtime_gcWriteBarrier2();
    *in_R11 = uStack_18;
    in_R11[1] = uStack_20;
  }
  *puStack_78 = uStack_18;
  puStack_78[1] = uStack_20;
  if ((*(long *)(lStack0000000000000010 + 0x40) != 0) &&
     (lVar5 = *(long *)(lStack0000000000000010 + 0x48), puStack_40 = puStack_78,
     uVar3 = kiro2api_internal_logic_antigravity_getContentText(), puStack_78 = puStack_40, lVar5 != 0)) {
    uStack_80 = uVar3;
    uStack_18 = runtime_makemap_small();
    piStack_10 = (int *)runtime_convTstring();
    puVar1 = (undefined8 *)runtime_mapassign_faststr(4);
    *puVar1 = &DAT_0194e220;
    if (DAT_02e5e450 != 0) {
      auVar9 = runtime_gcWriteBarrier2();
      puVar1 = auVar9._0_8_;
      *in_R11 = piStack_10;
      in_R11[1] = auVar9._8_8_;
    }
    puVar1[1] = piStack_10;
    puStack_78 = (undefined8 *)runtime_growslice(1,&DAT_01a233a0);
    if (DAT_02e5e450 != 0) {
      auVar9 = runtime_gcWriteBarrier2();
      puStack_78 = auVar9._0_8_;
      *in_R11 = uStack_18;
      in_R11[1] = auVar9._8_8_;
    }
    puStack_78[2] = uStack_18;
  }
  uStack_18 = runtime_makemap_small();
  puVar1 = (undefined8 *)runtime_mapassign_faststr(4);
  *puVar1 = &DAT_0194e220;
  if (DAT_02e5e450 != 0) {
    auVar9 = runtime_gcWriteBarrier1();
    puVar1 = auVar9._0_8_;
    *in_R11 = auVar9._8_8_;
  }
  puVar1[1] = &PTR_DAT_01f39720;
  piStack_10 = (int *)runtime_convTslice();
  puVar1 = (undefined8 *)runtime_mapassign_faststr(5);
  *puVar1 = &DAT_0192a2e0;
  if (DAT_02e5e450 != 0) {
    uVar3 = puVar1[1];
    puVar1 = (undefined8 *)runtime_gcWriteBarrier2();
    *in_R11 = piStack_10;
    in_R11[1] = uVar3;
  }
  puVar1[1] = piStack_10;
  puVar1 = (undefined8 *)runtime_mapassign_faststr(0x11);
  *puVar1 = &DAT_01a233a0;
  if (DAT_02e5e450 != 0) {
    uVar3 = puVar1[1];
    puVar1 = (undefined8 *)runtime_gcWriteBarrier2();
    *in_R11 = uStack_18;
    in_R11[1] = uVar3;
  }
  puVar1[1] = uStack_18;
  uStack_60 = runtime_makemap_small();
  puVar1 = (undefined8 *)runtime_mapassign_faststr(0xf);
  *puVar1 = &DAT_0194e460;
  if (DAT_02e5e450 != 0) {
    auVar9 = runtime_gcWriteBarrier1();
    puVar1 = auVar9._0_8_;
    *in_R11 = auVar9._8_8_;
  }
  puVar1[1] = &DAT_01f38770;
  piStack_10 = (int *)runtime_convTslice();
  puVar1 = (undefined8 *)runtime_mapassign_faststr(0xd);
  *puVar1 = &DAT_0192e8e0;
  if (DAT_02e5e450 != 0) {
    auVar9 = runtime_gcWriteBarrier2();
    puVar1 = auVar9._0_8_;
    *in_R11 = piStack_10;
    in_R11[1] = auVar9._8_8_;
  }
  puVar1[1] = piStack_10;
  uVar6 = (ulong)bStack0000000000000030;
  piVar8 = piStack_10;
  if (bStack0000000000000030 != 0) {
    if ((((uStack0000000000000028 == 0) || ((long)uStack0000000000000028 < 6)) ||
        (*piStack0000000000000020 != 0x75616c63)) || ((short)piStack0000000000000020[1] != 0x6564))
    {
      uVar6 = uStack0000000000000028;
      piVar8 = piStack0000000000000020;
      if (*(long *)(lStack0000000000000010 + 0x68) != 0) {
        uStack_18 = runtime_makemap_small();
        piStack_10 = (int *)runtime_convT64();
        auVar9 = runtime_mapassign_faststr(0xe);
        *auVar9._0_8_ = &DAT_0194e460;
        if (DAT_02e5e450 != 0) {
          auVar9 = runtime_gcWriteBarrier2();
          *in_R11 = piStack_10;
          in_R11[1] = auVar9._8_8_;
        }
        *(int **)(auVar9._0_8_ + 8) = piStack_10;
        puVar1 = (undefined8 *)runtime_mapassign_faststr(0xe,piStack_10,auVar9._8_8_,&DAT_01c4b839);
        *puVar1 = &DAT_01a233a0;
        if (DAT_02e5e450 != 0) {
          uVar3 = puVar1[1];
          puVar1 = (undefined8 *)runtime_gcWriteBarrier2();
          *in_R11 = uStack_18;
          in_R11[1] = uVar3;
        }
        puVar1[1] = uStack_18;
        uVar6 = uStack0000000000000028;
        piVar8 = piStack0000000000000020;
      }
    }
    else {
      uStack_18 = runtime_makemap_small();
      puVar1 = (undefined8 *)runtime_mapassign_faststr(0xe);
      *puVar1 = &DAT_0194e460;
      if (DAT_02e5e450 != 0) {
        auVar9 = runtime_gcWriteBarrier1();
        puVar1 = auVar9._0_8_;
        *in_R11 = auVar9._8_8_;
      }
      puVar1[1] = &DAT_01f38728;
      puVar1 = (undefined8 *)runtime_mapassign_faststr(0xe);
      *puVar1 = &DAT_01a233a0;
      if (DAT_02e5e450 != 0) {
        uVar3 = puVar1[1];
        puVar1 = (undefined8 *)runtime_gcWriteBarrier2();
        *in_R11 = uStack_18;
        in_R11[1] = uVar3;
      }
      puVar1[1] = uStack_18;
      uVar6 = uStack0000000000000028;
      piVar8 = piStack0000000000000020;
    }
  }
  uVar3 = uStack_70;
  puVar1 = (undefined8 *)runtime_mapassign_faststr(0x10,piVar8,uVar6,&DAT_01c4f193);
  *puVar1 = &DAT_01a233a0;
  if (DAT_02e5e450 != 0) {
    uVar4 = puVar1[1];
    puVar1 = (undefined8 *)runtime_gcWriteBarrier2();
    *in_R11 = uStack_60;
    in_R11[1] = uVar4;
  }
  puVar1[1] = uStack_60;
  if (*(long *)(lStack0000000000000010 + 0x58) != 0) {
    lVar5 = *(long *)(lStack0000000000000010 + 0x50);
    kiro2api_internal_logic_antigravity_sAntigravity_convertToolsToFunctionDeclarations(*(undefined8 *)(lStack0000000000000010 + 0x60));
    uVar3 = 0;
    if (lVar5 != 0) {
      piStack_10 = (int *)runtime_convTslice();
      puVar1 = (undefined8 *)runtime_mapassign_faststr(5);
      *puVar1 = &DAT_0192a2e0;
      if (DAT_02e5e450 != 0) {
        uVar3 = puVar1[1];
        puVar1 = (undefined8 *)runtime_gcWriteBarrier2();
        *in_R11 = piStack_10;
        in_R11[1] = uVar3;
      }
      puVar1[1] = piStack_10;
      uStack_18 = runtime_makemap_small();
      uStack_20 = runtime_makemap_small();
      puVar1 = (undefined8 *)runtime_mapassign_faststr(4);
      *puVar1 = &DAT_0194e220;
      if (DAT_02e5e450 != 0) {
        auVar9 = runtime_gcWriteBarrier1();
        puVar1 = auVar9._0_8_;
        *in_R11 = auVar9._8_8_;
      }
      puVar1[1] = &PTR_DAT_01f3a2a0;
      puVar1 = (undefined8 *)runtime_mapassign_faststr(0x15);
      *puVar1 = &DAT_01a233a0;
      if (DAT_02e5e450 != 0) {
        uVar3 = puVar1[1];
        puVar1 = (undefined8 *)runtime_gcWriteBarrier2();
        *in_R11 = uStack_20;
        in_R11[1] = uVar3;
      }
      uVar3 = uStack_70;
      puVar1[1] = uStack_20;
      puVar1 = (undefined8 *)runtime_mapassign_faststr(10);
      *puVar1 = &DAT_01a233a0;
      if (DAT_02e5e450 != 0) {
        uVar4 = puVar1[1];
        puVar1 = (undefined8 *)runtime_gcWriteBarrier2();
        *in_R11 = uStack_18;
        in_R11[1] = uVar4;
      }
      puVar1[1] = uStack_18;
    }
  }
  lVar5 = *(long *)(lStack0000000000000018 + 0x60);
  puStack_68 = *(undefined **)(lStack0000000000000018 + 0x58);
  uStack_48 = github_com_google_uuid_NewString();
  uStack_88 = uVar3;
  lVar2 = runtime_newobject();
  *(ulong *)(lVar2 + 8) = uStack0000000000000028;
  puVar7 = puStack_68;
  if (lVar5 == 0) {
    puVar7 = &DAT_01c570d6;
    lVar5 = 0x14;
  }
  auVar9._8_8_ = puVar7;
  auVar9._0_8_ = lVar2;
  if (DAT_02e5e450 != 0) {
    auVar9 = runtime_gcWriteBarrier1();
    *in_R11 = piStack0000000000000020;
  }
  puVar1 = auVar9._0_8_;
  *puVar1 = piStack0000000000000020;
  puVar1[3] = 0xb;
  puVar1[2] = &DAT_01c45ff5;
  puVar1[5] = 5;
  puVar1[4] = 
  "agentqueryreseteventtodosWritefilesshellchunkpartsitemstitlepaths<env>Agentarm642.1.7SkillmacOStasksstartMacOSnanos%s_%ddiffsplansskill.jsonPATCHx-appuser_ravenbytesQuery3.0.0ROUTE%s#%d</tr>debug%s:%d*fuzz*listPOST:HEAD:IndexInputshort%s,%s=j=02=G=15-0700%dh%sdefersweeptestRtestWexecWhchanexecRschedsudogtimergscanmheaptracepanicsleepamd64gcing MB,  got= ...\n max=scav  ptr ] = (trap:init  ms, fault and  tab= tag= top=[...], fp:deny"
  ;
  puVar1[7] = lVar5;
  if (DAT_02e5e450 != 0) {
    auVar9 = runtime_gcWriteBarrier1();
    *in_R11 = auVar9._8_8_;
  }
  lStack_50 = auVar9._0_8_;
  *(long *)(lStack_50 + 0x30) = auVar9._8_8_;
  uVar3 = runtime_concatstring2(uStack_48,uStack_88,auVar9._8_8_,6);
  auVar10._8_8_ = lStack_50;
  auVar10._0_8_ = uVar3;
  *(char **)(lStack_50 + 0x48) =
       "agent-</env>darwin24.0.015.6.1inputsimagesoffset0.70.0system/usagev2.9.7%s[%d]ServerConfigSERVERDOMAINMETHOD%s#%d,Logger<html><head><body><hr />/traceactiondomainmethod/[^/]+PATCH:TRACE:/indexUSAGE\n-/--%sOutput-07:00000000 Valuesysmontimersefenceselectscalar, not       unused objs\n next= jobs= goid sweep  B -> % util alloc free  span= prev= list=, i =  code= addr=], sp= m->p= p->m=SCHED  curg= ctxt: min=  max= bad ts(...)\n m=nil base hangupkilledallow"
  ;
  if (DAT_02e5e450 != 0) {
    uVar3 = *(undefined8 *)(lStack_50 + 0x40);
    uVar4 = *(undefined8 *)(lStack_50 + 0x50);
    auVar10 = runtime_gcWriteBarrier4();
    *in_R11 = auVar10._0_8_;
    in_R11[1] = uVar3;
    in_R11[2] = uStack_70;
    in_R11[3] = uVar4;
  }
  lVar5 = auVar10._8_8_;
  *(long *)(lVar5 + 0x40) = auVar10._0_8_;
  *(undefined8 *)(lVar5 + 0x50) = uStack_70;
  return lVar5;
}




// === antigravity.RefreshToken @ 0x17ab9a0 ===

/* WARNING: Removing unreachable block (ram,0x017ac173) */
/* WARNING: Removing unreachable block (ram,0x017ac5e6) */
/* WARNING: Removing unreachable block (ram,0x017ac60e) */
/* WARNING: Removing unreachable block (ram,0x017ac666) */
/* WARNING: Removing unreachable block (ram,0x017ac18d) */
/* WARNING: Removing unreachable block (ram,0x017ac196) */
/* WARNING: Removing unreachable block (ram,0x017ac1ec) */
/* WARNING: Removing unreachable block (ram,0x017ac1f7) */
/* WARNING: Removing unreachable block (ram,0x017ac1fb) */
/* WARNING: Removing unreachable block (ram,0x017ac235) */
/* WARNING: Removing unreachable block (ram,0x017ac282) */
/* WARNING: Removing unreachable block (ram,0x017ac292) */
/* WARNING: Removing unreachable block (ram,0x017ac2fe) */
/* WARNING: Removing unreachable block (ram,0x017ac31d) */
/* WARNING: Removing unreachable block (ram,0x017ac362) */
/* WARNING: Removing unreachable block (ram,0x017ac339) */
/* WARNING: Removing unreachable block (ram,0x017ac34a) */
/* WARNING: Removing unreachable block (ram,0x017ac35a) */
/* WARNING: Removing unreachable block (ram,0x017ac365) */
/* WARNING: Removing unreachable block (ram,0x017ac38e) */
/* WARNING: Removing unreachable block (ram,0x017ac377) */
/* WARNING: Removing unreachable block (ram,0x017ac392) */
/* WARNING: Removing unreachable block (ram,0x017ac488) */
/* WARNING: Removing unreachable block (ram,0x017ac4ba) */
/* WARNING: Removing unreachable block (ram,0x017ac4cc) */
/* WARNING: Removing unreachable block (ram,0x017ac4e0) */
/* WARNING: Removing unreachable block (ram,0x017ac56f) */
/* WARNING: Removing unreachable block (ram,0x017ac57a) */
/* WARNING: Removing unreachable block (ram,0x017ac57e) */
/* WARNING: Removing unreachable block (ram,0x017ac5b8) */
/* WARNING: Removing unreachable block (ram,0x017ac5c5) */

undefined8 antigravity_RefreshToken(long param_1,undefined8 param_2,undefined8 param_3,long param_4)

{
  ulong uVar1;
  long lVar2;
  char cVar3;
  long *plVar4;
  undefined8 *puVar5;
  long lVar6;
  undefined8 uVar7;
  undefined8 uVar8;
  ulong uVar9;
  long lVar10;
  undefined *puVar11;
  ulong uVar12;
  long extraout_RDX;
  undefined8 extraout_RDX_00;
  ulong uVar13;
  long *in_R11;
  long unaff_R14;
  undefined1 auVar14 [16];
  undefined1 auVar15 [16];
  undefined1 auVar16 [16];
  long lStack0000000000000018;
  long lStack0000000000000020;
  undefined1 auStack_2a0 [8];
  long lStack_298;
  long lStack_290;
  undefined8 uStack_288;
  undefined *puStack_280;
  ulong uStack_268;
  ulong uStack_260;
  long lStack_250;
  long lStack_248;
  undefined8 *puStack_240;
  long lStack_230;
  undefined8 uStack_228;
  long lStack_1d8;
  long lStack_1d0;
  undefined8 uStack_1c0;
  undefined1 auStack_1b8 [328];
  undefined8 uStack_70;
  undefined8 *puStack_68;
  undefined *puStack_48;
  undefined8 uStack_40;
  long lStack_30;
  long lStack_28;
  long *plStack_20;
  
  lStack0000000000000018 = param_4;
  lStack0000000000000020 = param_1;
  while (auStack_2a0 <= *(undefined1 **)(unaff_R14 + 0x10)) {
    runtime_morestack_noctxt();
  }
  cVar3 = kiro2api_internal_logic_antigravity_sAntigravity_IsTokenExpiringSoon();
  if ((cVar3 == '\0') && (*(long *)(lStack0000000000000020 + 0x30) != 0)) {
    return 0;
  }
  if (*(long *)(lStack0000000000000020 + 0x40) == 0) {
    auVar14 = runtime_convT64();
    uStack_40 = auVar14._0_8_;
    puStack_48 = &DAT_0194e420;
    uVar7 = fmt_Errorf(1,1,auVar14._8_8_,&puStack_48);
    return uVar7;
  }
  FUN_00488c9d(auStack_1b8);
  uStack_1c0 = 0x8080808080808080;
  puStack_68 = &uStack_1c0;
  uStack_70 = runtime_rand();
  plStack_20 = (long *)runtime_newobject();
  plStack_20[1] = 0x49;
  *plStack_20 = (long)&DAT_01c9c010;
  plVar4 = (long *)runtime_mapassign_faststr(9);
  plVar4[1] = 1;
  plVar4[2] = 1;
  if (DAT_02e5e450 != 0) {
    lVar6 = *plVar4;
    plVar4 = (long *)runtime_gcWriteBarrier2();
    *in_R11 = (long)plStack_20;
    in_R11[1] = lVar6;
  }
  *plVar4 = (long)plStack_20;
  plStack_20 = (long *)runtime_newobject();
  plStack_20[1] = 0x23;
  *plStack_20 = (long)&DAT_01c71c2f;
  plVar4 = (long *)runtime_mapassign_faststr(0xd);
  plVar4[1] = 1;
  plVar4[2] = 1;
  if (DAT_02e5e450 != 0) {
    lVar6 = *plVar4;
    plVar4 = (long *)runtime_gcWriteBarrier2();
    *in_R11 = (long)plStack_20;
    in_R11[1] = lVar6;
  }
  *plVar4 = (long)plStack_20;
  lStack_298 = *(long *)(lStack0000000000000020 + 0x40);
  lStack_248 = *(long *)(lStack0000000000000020 + 0x38);
  plVar4 = (long *)runtime_newobject();
  plVar4[1] = lStack_298;
  if (DAT_02e5e450 != 0) {
    plVar4 = (long *)runtime_gcWriteBarrier1();
    *in_R11 = lStack_248;
  }
  *plVar4 = lStack_248;
  plStack_20 = plVar4;
  plVar4 = (long *)runtime_mapassign_faststr(0xd);
  plVar4[1] = 1;
  plVar4[2] = 1;
  if (DAT_02e5e450 != 0) {
    lVar6 = *plVar4;
    plVar4 = (long *)runtime_gcWriteBarrier2();
    *in_R11 = (long)plStack_20;
    in_R11[1] = lVar6;
  }
  *plVar4 = (long)plStack_20;
  plStack_20 = (long *)runtime_newobject();
  plStack_20[1] = 0xd;
  *plStack_20 = (long)&DAT_01c49a06;
  puVar5 = (undefined8 *)runtime_mapassign_faststr(10);
  puVar5[1] = 1;
  puVar5[2] = 1;
  if (DAT_02e5e450 != 0) {
    auVar14 = runtime_gcWriteBarrier2();
    puVar5 = auVar14._0_8_;
    *in_R11 = (long)plStack_20;
    in_R11[1] = auVar14._8_8_;
  }
  lVar6 = lStack0000000000000018;
  *puVar5 = plStack_20;
  uStack_228 = kiro2api_internal_logic_antigravity_getProxyURL();
  lStack_290 = lVar6;
  lStack_1d8 = github_com_imroc_req_v3_Client_Clone();
  if (lStack_290 != 0) {
    github_com_imroc_req_v3_Client_SetProxyURL();
  }
  if (*(undefined8 **)(lStack_1d8 + 0x60) == (undefined8 *)0x0) {
    lStack_250 = 0;
  }
  else {
    puStack_240 = *(undefined8 **)(lStack_1d8 + 0x60);
    puVar5 = (undefined8 *)runtime_newobject();
    *puVar5 = *puStack_240;
    auVar14._8_8_ = puStack_240[1];
    auVar14._0_8_ = puVar5;
    puVar5 = puStack_240;
    if (DAT_02e5e450 != 0) {
      auVar14 = runtime_gcWriteBarrier1();
      *in_R11 = auVar14._8_8_;
    }
    lStack_250 = auVar14._0_8_;
    *(long *)(lStack_250 + 8) = auVar14._8_8_;
    uStack_268 = *(long *)(lStack_250 + 0x18);
    uVar9 = *(ulong *)(lStack_250 + 0x20);
    uStack_260 = puVar5[3];
    uVar1 = uStack_268 + uStack_260;
    lVar6 = *(long *)(lStack_250 + 0x10);
    lStack_28 = puVar5[2];
    if (uVar9 < uVar1) {
      lVar6 = runtime_growslice(uStack_260,&DAT_019ea040);
    }
    lVar10 = uVar1 - uStack_268;
    uVar12 = (long)(uStack_268 - uVar9) >> 0x3f;
    in_R11 = (long *)(uStack_268 << 3 & uVar12);
    uStack_268 = uVar1;
    lVar2 = uStack_260;
    uStack_260 = uVar9;
    uVar7 = lStack_28;
    lStack_28 = lVar6;
    runtime_typedslicecopy(uVar7,lVar2,uVar12,lVar10);
    *(ulong *)(lStack_250 + 0x18) = uStack_268;
    *(ulong *)(lStack_250 + 0x20) = uStack_260;
    lVar6 = lStack_250;
    if (DAT_02e5e450 != 0) {
      runtime_gcWriteBarrier2();
      *in_R11 = lStack_28;
      in_R11[1] = extraout_RDX;
    }
    *(long *)(lVar6 + 0x10) = lStack_28;
    uStack_268 = *(long *)(lVar6 + 0x30);
    uVar9 = *(ulong *)(lVar6 + 0x38);
    uStack_260 = puStack_240[6];
    uVar1 = uStack_268 + uStack_260;
    lVar6 = *(long *)(lVar6 + 0x28);
    lStack_30 = puStack_240[5];
    if (uVar9 < uVar1) {
      lVar6 = runtime_growslice(uStack_260,&DAT_019cbd00);
    }
    lVar10 = uVar1 - uStack_268;
    uVar13 = uStack_268 << 3;
    uVar12 = (long)(uStack_268 - uVar9) >> 0x3f;
    uStack_268 = uVar9;
    lVar2 = uStack_260;
    uStack_260 = uVar1;
    uVar7 = lStack_30;
    lStack_30 = lVar6;
    runtime_typedslicecopy(uVar7,lVar2,uVar12,lVar10,uVar13 & uVar12);
    *(ulong *)(lStack_250 + 0x30) = uStack_260;
    *(ulong *)(lStack_250 + 0x38) = uStack_268;
    if (DAT_02e5e450 != 0) {
      lVar6 = *(long *)(lStack_250 + 0x28);
      runtime_gcWriteBarrier2();
      *in_R11 = lStack_30;
      in_R11[1] = lVar6;
    }
    *(long *)(lStack_250 + 0x28) = lStack_30;
  }
  lVar6 = runtime_newobject();
  if (DAT_02e5e450 != 0) {
    lVar6 = runtime_gcWriteBarrier2();
    *in_R11 = lStack_1d8;
    in_R11[1] = lStack_250;
  }
  *(long *)(lVar6 + 0xf8) = lStack_1d8;
  *(long *)(lVar6 + 0x130) = lStack_250;
  lStack_230 = github_com_imroc_req_v3_Request_SetHeader(&DAT_01c6e5ef,0x21,lStack_1d8,0xc);
  uVar7 = net_url_Values_Encode();
  puVar11 = &DAT_01c47ddc;
  uVar8 = runtime_stringtoslicebyte();
  auVar15._8_8_ = lStack_230;
  auVar15._0_8_ = uVar8;
  *(undefined8 *)(lStack_230 + 0xc0) = uVar7;
  *(undefined **)(lStack_230 + 200) = puVar11;
  uStack_288 = uVar7;
  puStack_280 = puVar11;
  if (DAT_02e5e450 != 0) {
    lVar6 = *(long *)(lStack_230 + 0xb8);
    auVar15 = runtime_gcWriteBarrier2();
    *in_R11 = auVar15._0_8_;
    in_R11[1] = lVar6;
  }
  lStack_1d0 = auVar15._0_8_;
  *(long *)(auVar15._8_8_ + 0xb8) = lStack_1d0;
  puVar5 = (undefined8 *)runtime_newobject();
  auVar16._8_8_ = lStack_230;
  auVar16._0_8_ = puVar5;
  *puVar5 = &LAB_017ac760;
  puVar5[2] = uStack_288;
  puVar5[3] = puStack_280;
  if (DAT_02e5e450 != 0) {
    lVar6 = *(long *)(lStack_230 + 0xd0);
    auVar16 = runtime_gcWriteBarrier3();
    *in_R11 = lStack_1d0;
    in_R11[1] = auVar16._0_8_;
    in_R11[2] = lVar6;
  }
  *(long *)(auVar16._0_8_ + 8) = lStack_1d0;
  *(long *)(auVar16._8_8_ + 0xd0) = auVar16._0_8_;
  uVar7 = 4;
  github_com_imroc_req_v3_Request_Send(&DAT_01c71c52,0x23);
  puStack_48 = DAT_01c3979a;
  uStack_40 = uVar7;
  uVar7 = fmt_Errorf(1,1,extraout_RDX_00,&puStack_48);
  return uVar7;
}




// === antigravity.convertContentToPartsWithMapping @ 0x17b2580 ===

undefined8 *
kiro2api_internal_logic_antigravity_sAntigravity_convertContentToPartsWithMapping(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 *param_4)

{
  ulong uVar1;
  undefined8 *puVar2;
  long lVar3;
  undefined8 uVar4;
  undefined8 *unaff_RBX;
  ulong uVar5;
  long lVar6;
  long *plVar7;
  undefined8 *in_R11;
  long unaff_R14;
  undefined1 auVar8 [16];
  undefined8 *puStack0000000000000018;
  undefined8 local_d8;
  undefined8 local_d0;
  long local_c8;
  undefined8 local_c0;
  long local_b8;
  undefined8 *local_b0;
  long local_a8;
  undefined8 local_a0;
  undefined8 local_98;
  undefined8 local_90;
  undefined8 local_88;
  undefined *local_80;
  undefined8 *local_78;
  undefined8 local_70;
  undefined8 local_68;
  undefined8 local_60;
  undefined8 local_58;
  undefined8 local_50;
  undefined8 local_48;
  undefined8 local_40;
  undefined8 local_38;
  undefined8 local_30;
  undefined8 local_28;
  undefined8 local_20;
  undefined8 *local_18;
  undefined8 local_10;
  
  puStack0000000000000018 = param_4;
  if (&local_d8 <= *(undefined8 **)(unaff_R14 + 0x10)) {
    runtime_morestack_noctxt();
    puVar2 = (undefined8 *)kiro2api_internal_logic_antigravity_sAntigravity_convertContentToPartsWithMapping(param_1);
    return puVar2;
  }
  if (unaff_RBX != (undefined8 *)0x0) {
    if (*(int *)(unaff_RBX + 2) == -0xd99de8a) {
      if (unaff_RBX == &DAT_0192e960) {
        local_18 = (undefined8 *)*param_4;
        uVar1 = 0;
        local_78 = (undefined8 *)0x0;
        uVar5 = 0;
        for (local_a8 = param_4[1]; 0 < local_a8; local_a8 = local_a8 + -1) {
          if ((undefined8 *)*local_18 == &DAT_01a233a0) {
            local_38 = local_18[1];
            puVar2 = (undefined8 *)runtime_mapaccess1_faststr(4,local_a8,local_18,&DAT_01c397aa);
            if ((undefined8 *)*puVar2 == &DAT_0194e220) {
              plVar7 = *(long **)puVar2[1];
              lVar6 = ((undefined8 *)puVar2[1])[1];
            }
            else {
              lVar6 = 0;
              plVar7 = (long *)0x0;
            }
            if (lVar6 < 6) {
              if (lVar6 == 4) {
                if ((((int)*plVar7 == 0x74786574) &&
                    (puVar2 = (undefined8 *)runtime_mapaccess1_faststr(4,4,&DAT_0194e220,&DAT_01c397b2),
                    (undefined8 *)*puVar2 == &DAT_0194e220)) && (((undefined8 *)puVar2[1])[1] != 0))
                {
                  local_90 = *(undefined8 *)puVar2[1];
                  local_10 = runtime_makemap_small();
                  local_20 = runtime_convTstring();
                  puVar2 = (undefined8 *)runtime_mapassign_faststr(4);
                  *puVar2 = &DAT_0194e220;
                  if (DAT_02e5e450 != 0) {
                    auVar8 = runtime_gcWriteBarrier2();
                    puVar2 = auVar8._0_8_;
                    *in_R11 = local_20;
                    in_R11[1] = auVar8._8_8_;
                  }
                  puVar2[1] = local_20;
                  puVar2 = local_78;
                  if (uVar1 < uVar5 + 1) {
                    puVar2 = (undefined8 *)runtime_growslice(1,&DAT_01a233a0);
                  }
                  if (DAT_02e5e450 != 0) {
                    auVar8 = runtime_gcWriteBarrier2();
                    puVar2 = auVar8._0_8_;
                    *in_R11 = local_10;
                    in_R11[1] = auVar8._8_8_;
                  }
                  puVar2[uVar5] = local_10;
                  local_78 = puVar2;
                  uVar5 = uVar5 + 1;
                }
              }
              else if (((lVar6 == 5) && ((int)*plVar7 == 0x67616d69)) &&
                      ((*(char *)((long)plVar7 + 4) == 'e' &&
                       (puVar2 = (undefined8 *)runtime_mapaccess1_faststr(6,5,&DAT_0194e220,&DAT_01c3bd83),
                       (undefined8 *)*puVar2 == &DAT_01a233a0)))) {
                local_88 = puVar2[1];
                puVar2 = (undefined8 *)runtime_mapaccess1_faststr(10,local_88,&DAT_01a233a0,&DAT_01c44373);
                if ((undefined8 *)*puVar2 == &DAT_0194e220) {
                  local_68 = *(undefined8 *)puVar2[1];
                }
                else {
                  local_68 = 0;
                }
                puVar2 = (undefined8 *)runtime_mapaccess1_faststr(4);
                if ((undefined8 *)*puVar2 == &DAT_0194e220) {
                  local_48 = *(undefined8 *)puVar2[1];
                  local_c0 = ((undefined8 *)puVar2[1])[1];
                }
                else {
                  local_c0 = 0;
                  local_48 = 0;
                }
                local_10 = runtime_makemap_small();
                local_28 = runtime_makemap_small();
                local_20 = runtime_convTstring();
                puVar2 = (undefined8 *)runtime_mapassign_faststr(8);
                *puVar2 = &DAT_0194e220;
                if (DAT_02e5e450 != 0) {
                  auVar8 = runtime_gcWriteBarrier2();
                  puVar2 = auVar8._0_8_;
                  *in_R11 = local_20;
                  in_R11[1] = auVar8._8_8_;
                }
                puVar2[1] = local_20;
                local_20 = runtime_convTstring();
                auVar8 = runtime_mapassign_faststr(4);
                *auVar8._0_8_ = &DAT_0194e220;
                if (DAT_02e5e450 != 0) {
                  auVar8 = runtime_gcWriteBarrier2();
                  *in_R11 = local_20;
                  in_R11[1] = auVar8._8_8_;
                }
                *(undefined8 *)(auVar8._0_8_ + 8) = local_20;
                puVar2 = (undefined8 *)runtime_mapassign_faststr(10,local_20,auVar8._8_8_,&DAT_01c4441d);
                *puVar2 = &DAT_01a233a0;
                if (DAT_02e5e450 != 0) {
                  auVar8 = runtime_gcWriteBarrier2();
                  puVar2 = auVar8._0_8_;
                  *in_R11 = local_28;
                  in_R11[1] = auVar8._8_8_;
                }
                puVar2[1] = local_28;
                puVar2 = local_78;
                if (uVar1 < uVar5 + 1) {
                  puVar2 = (undefined8 *)runtime_growslice(1);
                }
                if (DAT_02e5e450 != 0) {
                  auVar8 = runtime_gcWriteBarrier2();
                  puVar2 = auVar8._0_8_;
                  *in_R11 = local_10;
                  in_R11[1] = auVar8._8_8_;
                }
                puVar2[uVar5] = local_10;
                local_78 = puVar2;
                uVar5 = uVar5 + 1;
              }
            }
            else if (lVar6 == 8) {
              if (*plVar7 == 0x676e696b6e696874) {
                puVar2 = (undefined8 *)
                         runtime_mapaccess1_faststr(8,0x676e696b6e696874,&DAT_0194e220,&DAT_01c3fd97);
                if (((undefined8 *)*puVar2 == &DAT_0194e220) && (((undefined8 *)puVar2[1])[1] != 0))
                {
                  local_98 = *(undefined8 *)puVar2[1];
                  local_10 = runtime_makemap_small();
                  puVar2 = (undefined8 *)runtime_mapassign_faststr(7);
                  *puVar2 = &DAT_0194e620;
                  if (DAT_02e5e450 != 0) {
                    auVar8 = runtime_gcWriteBarrier1();
                    puVar2 = auVar8._0_8_;
                    *in_R11 = auVar8._8_8_;
                  }
                  puVar2[1] = &DAT_01f8a688;
                  local_20 = runtime_convTstring();
                  puVar2 = (undefined8 *)runtime_mapassign_faststr(4);
                  *puVar2 = &DAT_0194e220;
                  if (DAT_02e5e450 != 0) {
                    auVar8 = runtime_gcWriteBarrier2();
                    puVar2 = auVar8._0_8_;
                    *in_R11 = local_20;
                    in_R11[1] = auVar8._8_8_;
                  }
                  puVar2[1] = local_20;
                  puVar2 = local_78;
                  if (uVar1 < uVar5 + 1) {
                    puVar2 = (undefined8 *)runtime_growslice(1,&DAT_01a233a0);
                  }
                  if (DAT_02e5e450 != 0) {
                    auVar8 = runtime_gcWriteBarrier2();
                    puVar2 = auVar8._0_8_;
                    *in_R11 = local_10;
                    in_R11[1] = auVar8._8_8_;
                  }
                  puVar2[uVar5] = local_10;
                  local_78 = puVar2;
                  uVar5 = uVar5 + 1;
                }
              }
              else if (*plVar7 == 0x6573755f6c6f6f74) {
                puVar2 = (undefined8 *)runtime_mapaccess1_faststr(4,0x676e696b6e696874,&DAT_0194e220,0x1c39796);
                if ((undefined8 *)*puVar2 == &DAT_0194e220) {
                  local_70 = *(undefined8 *)puVar2[1];
                  uVar4 = ((undefined8 *)puVar2[1])[1];
                }
                else {
                  uVar4 = 0;
                  local_70 = 0;
                }
                puVar2 = (undefined8 *)runtime_mapaccess1_faststr(2,uVar4,&DAT_0194e220,&DAT_01c3896e);
                if ((undefined8 *)*puVar2 == &DAT_0194e220) {
                  local_58 = *(undefined8 *)puVar2[1];
                  local_d0 = ((undefined8 *)puVar2[1])[1];
                }
                else {
                  local_d0 = 0;
                  local_58 = 0;
                }
                puVar2 = (undefined8 *)runtime_mapaccess1_faststr(5,local_d0,&DAT_0194e220,&DAT_01c3a5e4);
                local_60 = puVar2[1];
                local_d8 = *puVar2;
                local_10 = runtime_makemap_small();
                puVar2 = (undefined8 *)runtime_mapassign_faststr(0x10);
                *puVar2 = &DAT_0194e220;
                if (DAT_02e5e450 != 0) {
                  uVar4 = puVar2[1];
                  puVar2 = (undefined8 *)runtime_gcWriteBarrier1();
                  *in_R11 = uVar4;
                }
                puVar2[1] = &PTR_DAT_01f3a2b0;
                local_28 = runtime_makemap_small();
                local_20 = runtime_convTstring();
                auVar8 = runtime_mapassign_faststr(4);
                *auVar8._0_8_ = &DAT_0194e220;
                if (DAT_02e5e450 != 0) {
                  auVar8 = runtime_gcWriteBarrier2();
                  *in_R11 = local_20;
                  in_R11[1] = auVar8._8_8_;
                }
                *(undefined8 *)(auVar8._0_8_ + 8) = local_20;
                puVar2 = (undefined8 *)runtime_mapassign_faststr(4,local_20,auVar8._8_8_,&DAT_01c398ae);
                *puVar2 = local_d8;
                if (DAT_02e5e450 != 0) {
                  uVar4 = puVar2[1];
                  puVar2 = (undefined8 *)runtime_gcWriteBarrier2();
                  *in_R11 = local_60;
                  in_R11[1] = uVar4;
                }
                puVar2[1] = local_60;
                local_20 = runtime_convTstring();
                auVar8 = runtime_mapassign_faststr(2);
                *auVar8._0_8_ = &DAT_0194e220;
                if (DAT_02e5e450 != 0) {
                  auVar8 = runtime_gcWriteBarrier2();
                  *in_R11 = local_20;
                  in_R11[1] = auVar8._8_8_;
                }
                *(undefined8 *)(auVar8._0_8_ + 8) = local_20;
                puVar2 = (undefined8 *)runtime_mapassign_faststr(0xc,local_20,auVar8._8_8_,&DAT_01c481a8);
                *puVar2 = &DAT_01a233a0;
                if (DAT_02e5e450 != 0) {
                  auVar8 = runtime_gcWriteBarrier2();
                  puVar2 = auVar8._0_8_;
                  *in_R11 = local_28;
                  in_R11[1] = auVar8._8_8_;
                }
                puVar2[1] = local_28;
                puVar2 = local_78;
                if (uVar1 < uVar5 + 1) {
                  puVar2 = (undefined8 *)runtime_growslice(1);
                }
                if (DAT_02e5e450 != 0) {
                  auVar8 = runtime_gcWriteBarrier2();
                  puVar2 = auVar8._0_8_;
                  *in_R11 = local_10;
                  in_R11[1] = auVar8._8_8_;
                }
                puVar2[uVar5] = local_10;
                local_78 = puVar2;
                uVar5 = uVar5 + 1;
              }
            }
            else if ((((lVar6 == 0xb) && (*plVar7 == 0x7365725f6c6f6f74)) &&
                     ((short)plVar7[1] == 0x6c75)) && (*(char *)((long)plVar7 + 10) == 't')) {
              puVar2 = (undefined8 *)
                       runtime_mapaccess1_faststr(0xb,0x7365725f6c6f6f74,&DAT_0194e220,&DAT_01c462ec);
              if ((undefined8 *)*puVar2 == &DAT_0194e220) {
                local_a0 = *(undefined8 *)puVar2[1];
                lVar6 = ((undefined8 *)puVar2[1])[1];
              }
              else {
                lVar6 = 0;
                local_a0 = 0;
              }
              puVar2 = (undefined8 *)runtime_mapaccess1_faststr(lVar6,lVar6,&DAT_0194e220,local_a0);
              local_c8 = puVar2[1];
              local_50 = *puVar2;
              lVar3 = runtime_mapaccess1_faststr(7);
              in_R11 = *(undefined8 **)(lVar3 + 8);
              local_80 = (undefined *)kiro2api_internal_logic_antigravity_getContentText();
              strings_TrimSpace();
              local_b0 = in_R11;
              local_10 = runtime_makemap_small();
              puVar2 = (undefined8 *)runtime_mapassign_faststr(0x10);
              *puVar2 = &DAT_0194e220;
              if (local_c8 == 0) {
                local_50 = local_a0;
                local_c8 = lVar6;
              }
              if (local_b0 == (undefined8 *)0x0) {
                in_R11 = (undefined8 *)&DAT_0000001e;
                local_80 = &DAT_01c68c68;
              }
              if (DAT_02e5e450 != 0) {
                uVar4 = puVar2[1];
                puVar2 = (undefined8 *)runtime_gcWriteBarrier1();
                *in_R11 = uVar4;
              }
              puVar2[1] = &PTR_DAT_01f3a2b0;
              local_28 = runtime_makemap_small();
              local_20 = runtime_convTstring();
              puVar2 = (undefined8 *)runtime_mapassign_faststr(4);
              *puVar2 = &DAT_0194e220;
              if (DAT_02e5e450 != 0) {
                auVar8 = runtime_gcWriteBarrier2();
                puVar2 = auVar8._0_8_;
                *in_R11 = local_20;
                in_R11[1] = auVar8._8_8_;
              }
              puVar2[1] = local_20;
              local_30 = runtime_makemap_small();
              local_20 = runtime_convTstring();
              auVar8 = runtime_mapassign_faststr(6);
              *auVar8._0_8_ = &DAT_0194e220;
              if (DAT_02e5e450 != 0) {
                auVar8 = runtime_gcWriteBarrier2();
                *in_R11 = local_20;
                in_R11[1] = auVar8._8_8_;
              }
              *(undefined8 *)(auVar8._0_8_ + 8) = local_20;
              puVar2 = (undefined8 *)runtime_mapassign_faststr(8,local_20,auVar8._8_8_,&DAT_01c3ff27);
              *puVar2 = &DAT_01a233a0;
              if (DAT_02e5e450 != 0) {
                uVar4 = puVar2[1];
                puVar2 = (undefined8 *)runtime_gcWriteBarrier2();
                *in_R11 = local_30;
                in_R11[1] = uVar4;
              }
              puVar2[1] = local_30;
              local_20 = runtime_convTstring();
              auVar8 = runtime_mapassign_faststr(2);
              *auVar8._0_8_ = &DAT_0194e220;
              if (DAT_02e5e450 != 0) {
                auVar8 = runtime_gcWriteBarrier2();
                *in_R11 = local_20;
                in_R11[1] = auVar8._8_8_;
              }
              *(undefined8 *)(auVar8._0_8_ + 8) = local_20;
              puVar2 = (undefined8 *)runtime_mapassign_faststr(0x10,local_20,auVar8._8_8_,&DAT_01c4f1b3);
              *puVar2 = &DAT_01a233a0;
              if (DAT_02e5e450 != 0) {
                auVar8 = runtime_gcWriteBarrier2();
                puVar2 = auVar8._0_8_;
                *in_R11 = local_28;
                in_R11[1] = auVar8._8_8_;
              }
              puVar2[1] = local_28;
              puVar2 = local_78;
              if (uVar1 < uVar5 + 1) {
                puVar2 = (undefined8 *)runtime_growslice(1);
              }
              if (DAT_02e5e450 != 0) {
                auVar8 = runtime_gcWriteBarrier2();
                puVar2 = auVar8._0_8_;
                *in_R11 = local_10;
                in_R11[1] = auVar8._8_8_;
              }
              puVar2[uVar5] = local_10;
              local_78 = puVar2;
              uVar5 = uVar5 + 1;
            }
          }
          local_18 = local_18 + 2;
        }
        return local_78;
      }
    }
    else if ((*(int *)(unaff_RBX + 2) == -0x778cd48) && (unaff_RBX == &DAT_0194e220)) {
      local_b8 = param_4[1];
      if (local_b8 != 0) {
        local_40 = *param_4;
        local_10 = runtime_makemap_small();
        local_18 = (undefined8 *)runtime_convTstring();
        auVar8 = runtime_mapassign_faststr(4);
        *auVar8._0_8_ = &DAT_0194e220;
        if (DAT_02e5e450 != 0) {
          auVar8 = runtime_gcWriteBarrier2();
          *in_R11 = local_18;
          in_R11[1] = auVar8._8_8_;
        }
        *(undefined8 **)(auVar8._0_8_ + 8) = local_18;
        puVar2 = (undefined8 *)runtime_growslice(1,&DAT_01a233a0,auVar8._8_8_,0);
        if (DAT_02e5e450 != 0) {
          auVar8 = runtime_gcWriteBarrier2();
          puVar2 = auVar8._0_8_;
          *in_R11 = local_10;
          in_R11[1] = auVar8._8_8_;
        }
        *puVar2 = local_10;
        return puVar2;
      }
      return (undefined8 *)0x0;
    }
  }
  return (undefined8 *)0x0;
}



