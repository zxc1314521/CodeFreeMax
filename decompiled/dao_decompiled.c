// CodeFreeMax - DAO Channel Decompiled Functions
// 3 functions

// === dao.migrateKiroToGate @ 0x1104dc0 ===

void dao_migrateKiroToGate(long param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4)

{
  ulong uVar1;
  char cVar2;
  undefined8 in_RAX;
  long lVar3;
  undefined8 uVar4;
  undefined8 *puVar5;
  ulong uVar6;
  long lVar7;
  undefined4 *puVar8;
  undefined8 extraout_RDX;
  undefined8 unaff_RBX;
  undefined8 *in_R11;
  long unaff_R14;
  long in_XMM15_Qa;
  undefined1 auVar9 [16];
  undefined8 uStack0000000000000008;
  undefined8 uStack0000000000000010;
  undefined8 uStack0000000000000018;
  long lStack0000000000000020;
  ulong uStack_388;
  ulong uStack_380;
  undefined8 uStack_378;
  undefined8 uStack_370;
  undefined8 uStack_368;
  long lStack_360;
  undefined8 uStack_358;
  undefined8 uStack_350;
  undefined8 uStack_348;
  long lStack_340;
  undefined8 uStack_338;
  long lStack_330;
  undefined4 uStack_328;
  undefined4 uStack_324;
  undefined4 uStack_320;
  undefined4 uStack_31c;
  undefined8 uStack_318;
  undefined8 uStack_310;
  undefined8 uStack_308;
  undefined4 *puStack_300;
  ulong uStack_2f8;
  undefined8 uStack_2f0;
  undefined8 uStack_2e8;
  undefined8 uStack_2e0;
  undefined8 uStack_2d8;
  undefined1 auStack_2d0 [256];
  long lStack_1d0;
  undefined8 uStack_1c8;
  undefined8 *puStack_1c0;
  undefined8 *puStack_1a0;
  undefined8 uStack_198;
  undefined8 uStack_190;
  undefined8 uStack_188;
  undefined8 uStack_170;
  undefined8 uStack_168;
  undefined8 *puStack_140;
  undefined8 uStack_138;
  undefined8 *puStack_130;
  undefined8 uStack_128;
  undefined8 *puStack_120;
  undefined8 uStack_118;
  undefined8 *puStack_110;
  undefined8 uStack_108;
  undefined1 *puStack_100;
  undefined *puStack_f8;
  undefined8 uStack_f0;
  undefined8 **ppuStack_e8;
  undefined8 uStack_e0;
  undefined8 uStack_d8;
  undefined8 uStack_d0;
  undefined8 uStack_c8;
  undefined8 uStack_c0;
  undefined8 *puStack_b8;
  undefined8 *puStack_b0;
  undefined8 uStack_a8;
  undefined8 *puStack_a0;
  undefined8 uStack_98;
  undefined8 *puStack_90;
  undefined8 uStack_88;
  undefined8 uStack_80;
  undefined4 *puStack_78;
  undefined8 uStack_60;
  undefined8 uStack_58;
  undefined8 *puStack_30;
  undefined8 uStack_28;
  undefined8 uStack_20;
  undefined4 *puStack_18;
  undefined8 *puStack_10;
  
  uStack0000000000000008 = in_RAX;
  uStack0000000000000018 = param_4;
  uStack0000000000000010 = unaff_RBX;
  lStack0000000000000020 = param_1;
  while (&uStack_388 <= *(ulong **)(unaff_R14 + 0x10)) {
    runtime_morestack_noctxt();
  }
  puStack_10 = (undefined8 *)runtime_newobject();
  uStack_170 = uStack0000000000000008;
  uStack_168 = uStack0000000000000010;
  gorm_io_gorm_DB_Session();
  gorm_io_gorm_DB_Raw(0,0,extraout_RDX,0xc3,0);
  lVar3 = gorm_io_gorm_DB_Scan();
  uStack_188 = *(undefined8 *)(lVar3 + 0x10);
  if (*(long *)(lVar3 + 8) == 0) {
    if (puStack_10[1] != 0) {
      uStack_198 = runtime_convT64();
      puStack_1a0 = &DAT_0194e460;
      puStack_100 = &LAB_01105ae0;
      uStack_f0 = 0x39;
      puStack_f8 = &DAT_01c9059d;
      uStack_e0 = 1;
      uStack_d8 = 1;
      ppuStack_e8 = &puStack_1a0;
      log_Logger_output(&puStack_100);
      puVar5 = (undefined8 *)*puStack_10;
      for (lStack_360 = puStack_10[1]; 0 < lStack_360; lStack_360 = lStack_360 + -1) {
        uStack_350 = *puVar5;
        uStack_348 = puVar5[1];
        lStack_340 = puVar5[2];
        uStack_338 = puVar5[3];
        lStack_330 = puVar5[4];
        uStack_328 = *(undefined4 *)(puVar5 + 5);
        uStack_324 = *(undefined4 *)((long)puVar5 + 0x2c);
        uStack_320 = *(undefined4 *)(puVar5 + 6);
        uStack_31c = *(undefined4 *)((long)puVar5 + 0x34);
        lStack_1d0 = in_XMM15_Qa;
        puStack_b8 = puVar5;
        FUN_00488cb4(auStack_2d0);
        uStack_2d8 = 0x8080808080808080;
        puStack_1c0 = &uStack_2d8;
        uStack_1c8 = runtime_rand();
        if (lStack_340 != 0) {
          if (lStack_340 < 3) {
            cVar2 = '\0';
          }
          else {
            cVar2 = runtime_memequal();
          }
          lVar3 = lStack_340;
          if ((cVar2 != '\0') && (uVar4 = kiro2api_internal_crypt_DecryptCredential(), lVar3 != 0)) {
            uStack_308 = uVar4;
            puVar5 = (undefined8 *)runtime_mapassign_faststr(0xd);
            puVar5[1] = lVar3;
            if (DAT_02e5e450 != 0) {
              auVar9 = runtime_gcWriteBarrier2();
              puVar5 = auVar9._0_8_;
              *in_R11 = uStack_308;
              in_R11[1] = auVar9._8_8_;
            }
            *puVar5 = uStack_308;
          }
        }
        if (lStack_330 != 0) {
          if (lStack_330 < 3) {
            cVar2 = '\0';
          }
          else {
            cVar2 = runtime_memequal();
          }
          lVar3 = lStack_330;
          if ((cVar2 != '\0') && (uVar4 = kiro2api_internal_crypt_DecryptCredential(), lVar3 != 0)) {
            uStack_310 = uVar4;
            puVar5 = (undefined8 *)runtime_mapassign_faststr(9);
            puVar5[1] = lVar3;
            if (DAT_02e5e450 != 0) {
              auVar9 = runtime_gcWriteBarrier2();
              puVar5 = auVar9._0_8_;
              *in_R11 = uStack_310;
              in_R11[1] = auVar9._8_8_;
            }
            *puVar5 = uStack_310;
          }
        }
        if (CONCAT44(uStack_31c,uStack_320) != 0) {
          if (CONCAT44(uStack_31c,uStack_320) < 3) {
            cVar2 = '\0';
          }
          else {
            cVar2 = runtime_memequal();
          }
          if (cVar2 != '\0') {
            lVar3 = CONCAT44(uStack_31c,uStack_320);
            uVar4 = kiro2api_internal_crypt_DecryptCredential();
            if (lVar3 != 0) {
              uStack_318 = uVar4;
              puVar5 = (undefined8 *)runtime_mapassign_faststr(0xd);
              puVar5[1] = lVar3;
              if (DAT_02e5e450 != 0) {
                auVar9 = runtime_gcWriteBarrier2();
                puVar5 = auVar9._0_8_;
                *in_R11 = uStack_318;
                in_R11[1] = auVar9._8_8_;
              }
              *puVar5 = uStack_318;
            }
          }
        }
        lVar3 = lStack0000000000000020;
        if (lStack_1d0 != 0) {
          puVar8 = &DAT_01c3976e;
          uVar6 = kiro2api_internal_gate_Encrypt(4,&lStack_1d0);
          if (lVar3 == 0) {
            uStack_2f0 = uStack_348;
            uStack_2e0 = uStack_338;
            uStack_2e8 = CONCAT44(uStack_324,uStack_328);
            uStack_2f8 = uVar6;
            puVar5 = (undefined8 *)runtime_mapaccess2_faststr(0xd);
            uVar1 = uStack_2f8;
            uStack_c0 = *puVar5;
            uStack_368 = puVar5[1];
            puVar5 = (undefined8 *)runtime_mapaccess2_faststr(9);
            uStack_c8 = *puVar5;
            uStack_370 = puVar5[1];
            puVar5 = (undefined8 *)runtime_mapaccess2_faststr(0xd);
            uStack_d0 = *puVar5;
            uStack_378 = puVar5[1];
            uStack_380 = uVar6 & 0xff;
            uStack_388 = uVar1 & 0xff;
            uStack_60 = uStack0000000000000008;
            uStack_58 = uStack0000000000000010;
            uStack_358 = gorm_io_gorm_DB_Session();
            uStack_138 = runtime_convTstring();
            puStack_140 = &DAT_0194e220;
            uStack_128 = runtime_convTstring();
            puStack_130 = &DAT_0194e220;
            uStack_118 = runtime_convTstring();
            puStack_120 = &DAT_0194e220;
            uStack_108 = runtime_convT64();
            puStack_110 = &DAT_0194e420;
            lVar7 = gorm_io_gorm_DB_Exec(&puStack_140,4,&DAT_0194e420,0x65,4);
            lVar3 = *(long *)(lVar7 + 8);
            if (lVar3 != 0) {
              puStack_300 = *(undefined4 **)(lVar7 + 0x10);
              uStack_88 = runtime_convT64();
              puStack_90 = &DAT_0194e420;
              uStack_80 = 0;
              if (lVar3 != 0) {
                uStack_80 = *(undefined8 *)(lVar3 + 8);
              }
              puStack_78 = puStack_300;
              puStack_100 = &LAB_01105a20;
              uStack_f0 = 0x34;
              puStack_f8 = &DAT_01c8aea7;
              uStack_e0 = 2;
              uStack_d8 = 2;
              ppuStack_e8 = &puStack_90;
              log_Logger_output(&puStack_100);
            }
          }
          else {
            puStack_300 = puVar8;
            uStack_28 = runtime_convT64();
            puStack_30 = &DAT_0194e420;
            if (lVar3 == 0) {
              uStack_20 = 0;
            }
            else {
              uStack_20 = *(undefined8 *)(lVar3 + 8);
            }
            puStack_18 = puStack_300;
            puStack_100 = &LAB_01105a80;
            uStack_f0 = 0x3a;
            puStack_f8 = &DAT_01c913a8;
            uStack_e0 = 2;
            uStack_d8 = 2;
            ppuStack_e8 = &puStack_30;
            log_Logger_output(&puStack_100);
          }
        }
        puVar5 = puStack_b8 + 7;
      }
      lStack_360 = puStack_10[1];
      uStack_a8 = runtime_convT64();
      puStack_b0 = &DAT_0194e460;
      uStack_98 = runtime_convT64();
      puStack_a0 = &DAT_0194e460;
      puStack_100 = &LAB_011059c0;
      uStack_f0 = 0x2f;
      puStack_f8 = &DAT_01c853f9;
      uStack_e0 = 2;
      uStack_d8 = 2;
      ppuStack_e8 = &puStack_b0;
      log_Logger_output(&puStack_100);
      return;
    }
    return;
  }
  uStack_190 = *(undefined8 *)(*(long *)(lVar3 + 8) + 8);
  puStack_100 = &LAB_01105b40;
  uStack_f0 = 0x31;
  puStack_f8 = &DAT_01c87a7a;
  uStack_e0 = 1;
  uStack_d8 = 1;
  ppuStack_e8 = (undefined8 **)&uStack_190;
  log_Logger_output(&puStack_100);
  return;
}




// === dao.migrateOrchidsToGate @ 0x1106660 ===

void dao_migrateOrchidsToGate(long param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4)

{
  ulong uVar1;
  char cVar2;
  undefined8 in_RAX;
  long lVar3;
  undefined8 uVar4;
  undefined8 *puVar5;
  ulong uVar6;
  long lVar7;
  undefined *puVar8;
  undefined8 extraout_RDX;
  undefined8 unaff_RBX;
  undefined8 *in_R11;
  long unaff_R14;
  long in_XMM15_Qa;
  undefined1 auVar9 [16];
  undefined8 uStack0000000000000008;
  undefined8 uStack0000000000000010;
  undefined8 uStack0000000000000018;
  long lStack0000000000000020;
  ulong uStack_388;
  ulong uStack_380;
  undefined8 uStack_378;
  undefined8 uStack_370;
  undefined8 uStack_368;
  long lStack_360;
  undefined8 uStack_358;
  undefined8 uStack_350;
  undefined8 uStack_348;
  long lStack_340;
  undefined8 uStack_338;
  long lStack_330;
  undefined4 uStack_328;
  undefined4 uStack_324;
  undefined4 uStack_320;
  undefined4 uStack_31c;
  undefined8 uStack_318;
  undefined8 uStack_310;
  undefined8 uStack_308;
  undefined *puStack_300;
  ulong uStack_2f8;
  undefined8 uStack_2f0;
  undefined8 uStack_2e8;
  undefined8 uStack_2e0;
  undefined8 uStack_2d8;
  undefined1 auStack_2d0 [256];
  long lStack_1d0;
  undefined8 uStack_1c8;
  undefined8 *puStack_1c0;
  undefined8 *puStack_1a0;
  undefined8 uStack_198;
  undefined8 uStack_190;
  undefined8 uStack_188;
  undefined8 uStack_170;
  undefined8 uStack_168;
  undefined8 *puStack_140;
  undefined8 uStack_138;
  undefined8 *puStack_130;
  undefined8 uStack_128;
  undefined8 *puStack_120;
  undefined8 uStack_118;
  undefined8 *puStack_110;
  undefined8 uStack_108;
  undefined1 *puStack_100;
  undefined *puStack_f8;
  undefined8 uStack_f0;
  undefined8 **ppuStack_e8;
  undefined8 uStack_e0;
  undefined8 uStack_d8;
  undefined8 uStack_d0;
  undefined8 uStack_c8;
  undefined8 uStack_c0;
  undefined8 *puStack_b8;
  undefined8 *puStack_b0;
  undefined8 uStack_a8;
  undefined8 *puStack_a0;
  undefined8 uStack_98;
  undefined8 *puStack_90;
  undefined8 uStack_88;
  undefined8 uStack_80;
  undefined *puStack_78;
  undefined8 uStack_60;
  undefined8 uStack_58;
  undefined8 *puStack_30;
  undefined8 uStack_28;
  undefined8 uStack_20;
  undefined *puStack_18;
  undefined8 *puStack_10;
  
  uStack0000000000000008 = in_RAX;
  uStack0000000000000018 = param_4;
  uStack0000000000000010 = unaff_RBX;
  lStack0000000000000020 = param_1;
  while (&uStack_388 <= *(ulong **)(unaff_R14 + 0x10)) {
    runtime_morestack_noctxt();
  }
  puStack_10 = (undefined8 *)runtime_newobject();
  uStack_170 = uStack0000000000000008;
  uStack_168 = uStack0000000000000010;
  gorm_io_gorm_DB_Session();
  gorm_io_gorm_DB_Raw(0,0,extraout_RDX,0xb7,0);
  lVar3 = gorm_io_gorm_DB_Scan();
  uStack_188 = *(undefined8 *)(lVar3 + 0x10);
  if (*(long *)(lVar3 + 8) == 0) {
    if (puStack_10[1] != 0) {
      uStack_198 = runtime_convT64();
      puStack_1a0 = &DAT_0194e460;
      puStack_100 = &LAB_01107380;
      uStack_f0 = 0x3c;
      puStack_f8 = &DAT_01c92f8f;
      uStack_e0 = 1;
      uStack_d8 = 1;
      ppuStack_e8 = &puStack_1a0;
      log_Logger_output(&puStack_100);
      puVar5 = (undefined8 *)*puStack_10;
      for (lStack_360 = puStack_10[1]; 0 < lStack_360; lStack_360 = lStack_360 + -1) {
        uStack_350 = *puVar5;
        uStack_348 = puVar5[1];
        lStack_340 = puVar5[2];
        uStack_338 = puVar5[3];
        lStack_330 = puVar5[4];
        uStack_328 = *(undefined4 *)(puVar5 + 5);
        uStack_324 = *(undefined4 *)((long)puVar5 + 0x2c);
        uStack_320 = *(undefined4 *)(puVar5 + 6);
        uStack_31c = *(undefined4 *)((long)puVar5 + 0x34);
        lStack_1d0 = in_XMM15_Qa;
        puStack_b8 = puVar5;
        FUN_00488cb4(auStack_2d0);
        uStack_2d8 = 0x8080808080808080;
        puStack_1c0 = &uStack_2d8;
        uStack_1c8 = runtime_rand();
        if (lStack_340 != 0) {
          if (lStack_340 < 3) {
            cVar2 = '\0';
          }
          else {
            cVar2 = runtime_memequal();
          }
          lVar3 = lStack_340;
          if ((cVar2 != '\0') && (uVar4 = kiro2api_internal_crypt_DecryptCredential(), lVar3 != 0)) {
            uStack_308 = uVar4;
            puVar5 = (undefined8 *)runtime_mapassign_faststr(10);
            puVar5[1] = lVar3;
            if (DAT_02e5e450 != 0) {
              auVar9 = runtime_gcWriteBarrier2();
              puVar5 = auVar9._0_8_;
              *in_R11 = uStack_308;
              in_R11[1] = auVar9._8_8_;
            }
            *puVar5 = uStack_308;
          }
        }
        if (lStack_330 != 0) {
          if (lStack_330 < 3) {
            cVar2 = '\0';
          }
          else {
            cVar2 = runtime_memequal();
          }
          lVar3 = lStack_330;
          if ((cVar2 != '\0') && (uVar4 = kiro2api_internal_crypt_DecryptCredential(), lVar3 != 0)) {
            uStack_310 = uVar4;
            puVar5 = (undefined8 *)runtime_mapassign_faststr(8);
            puVar5[1] = lVar3;
            if (DAT_02e5e450 != 0) {
              auVar9 = runtime_gcWriteBarrier2();
              puVar5 = auVar9._0_8_;
              *in_R11 = uStack_310;
              in_R11[1] = auVar9._8_8_;
            }
            *puVar5 = uStack_310;
          }
        }
        if (CONCAT44(uStack_31c,uStack_320) != 0) {
          if (CONCAT44(uStack_31c,uStack_320) < 3) {
            cVar2 = '\0';
          }
          else {
            cVar2 = runtime_memequal();
          }
          if (cVar2 != '\0') {
            lVar3 = CONCAT44(uStack_31c,uStack_320);
            uVar4 = kiro2api_internal_crypt_DecryptCredential();
            if (lVar3 != 0) {
              uStack_318 = uVar4;
              puVar5 = (undefined8 *)runtime_mapassign_faststr(0xb);
              puVar5[1] = lVar3;
              if (DAT_02e5e450 != 0) {
                auVar9 = runtime_gcWriteBarrier2();
                puVar5 = auVar9._0_8_;
                *in_R11 = uStack_318;
                in_R11[1] = auVar9._8_8_;
              }
              *puVar5 = uStack_318;
            }
          }
        }
        lVar3 = lStack0000000000000020;
        if (lStack_1d0 != 0) {
          puVar8 = &DAT_01c3dd05;
          uVar6 = kiro2api_internal_gate_Encrypt(7,&lStack_1d0);
          if (lVar3 == 0) {
            uStack_2e0 = uStack_348;
            uStack_2f0 = uStack_338;
            uStack_2e8 = CONCAT44(uStack_324,uStack_328);
            uStack_2f8 = uVar6;
            puVar5 = (undefined8 *)runtime_mapaccess2_faststr(10);
            uVar1 = uStack_2f8;
            uStack_c0 = *puVar5;
            uStack_368 = puVar5[1];
            puVar5 = (undefined8 *)runtime_mapaccess2_faststr(8);
            uStack_c8 = *puVar5;
            uStack_370 = puVar5[1];
            puVar5 = (undefined8 *)runtime_mapaccess2_faststr(0xb);
            uStack_d0 = *puVar5;
            uStack_378 = puVar5[1];
            uStack_380 = uVar6 & 0xff;
            uStack_388 = uVar1 & 0xff;
            uStack_60 = uStack0000000000000008;
            uStack_58 = uStack0000000000000010;
            uStack_358 = gorm_io_gorm_DB_Session();
            uStack_138 = runtime_convTstring();
            puStack_140 = &DAT_0194e220;
            uStack_128 = runtime_convTstring();
            puStack_130 = &DAT_0194e220;
            uStack_118 = runtime_convTstring();
            puStack_120 = &DAT_0194e220;
            uStack_108 = runtime_convT64();
            puStack_110 = &DAT_0194e420;
            lVar7 = gorm_io_gorm_DB_Exec(&puStack_140,4,&DAT_0194e420,0x62,4);
            lVar3 = *(long *)(lVar7 + 8);
            if (lVar3 != 0) {
              puStack_300 = *(undefined **)(lVar7 + 0x10);
              uStack_88 = runtime_convT64();
              puStack_90 = &DAT_0194e420;
              uStack_80 = 0;
              if (lVar3 != 0) {
                uStack_80 = *(undefined8 *)(lVar3 + 8);
              }
              puStack_78 = puStack_300;
              puStack_100 = &LAB_011072c0;
              uStack_f0 = 0x37;
              puStack_f8 = &DAT_01c8e57d;
              uStack_e0 = 2;
              uStack_d8 = 2;
              ppuStack_e8 = &puStack_90;
              log_Logger_output(&puStack_100);
            }
          }
          else {
            puStack_300 = puVar8;
            uStack_28 = runtime_convT64();
            puStack_30 = &DAT_0194e420;
            if (lVar3 == 0) {
              uStack_20 = 0;
            }
            else {
              uStack_20 = *(undefined8 *)(lVar3 + 8);
            }
            puStack_18 = puStack_300;
            puStack_100 = &LAB_01107320;
            uStack_f0 = 0x3d;
            puStack_f8 = &DAT_01c93da9;
            uStack_e0 = 2;
            uStack_d8 = 2;
            ppuStack_e8 = &puStack_30;
            log_Logger_output(&puStack_100);
          }
        }
        puVar5 = puStack_b8 + 7;
      }
      lStack_360 = puStack_10[1];
      uStack_a8 = runtime_convT64();
      puStack_b0 = &DAT_0194e460;
      uStack_98 = runtime_convT64();
      puStack_a0 = &DAT_0194e460;
      puStack_100 = &LAB_01107260;
      uStack_f0 = 0x32;
      puStack_f8 = &DAT_01c88c49;
      uStack_e0 = 2;
      uStack_d8 = 2;
      ppuStack_e8 = &puStack_b0;
      log_Logger_output(&puStack_100);
      return;
    }
    return;
  }
  uStack_190 = *(undefined8 *)(*(long *)(lVar3 + 8) + 8);
  puStack_100 = &LAB_011073e0;
  uStack_f0 = 0x34;
  puStack_f8 = &DAT_01c8af0f;
  uStack_e0 = 1;
  uStack_d8 = 1;
  ppuStack_e8 = (undefined8 **)&uStack_190;
  log_Logger_output(&puStack_100);
  return;
}




// === dao.migrateClaudeApiToGate @ 0x1107440 ===

void dao_migrateClaudeApiToGate
               (long param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4)

{
  ulong uVar1;
  char cVar2;
  undefined8 in_RAX;
  long lVar3;
  undefined8 uVar4;
  undefined8 *puVar5;
  ulong uVar6;
  long lVar7;
  undefined *puVar8;
  undefined8 extraout_RDX;
  undefined8 unaff_RBX;
  undefined8 *in_R11;
  long unaff_R14;
  long in_XMM15_Qa;
  undefined1 auVar9 [16];
  undefined8 uStack0000000000000008;
  undefined8 uStack0000000000000010;
  undefined8 uStack0000000000000018;
  long lStack0000000000000020;
  ulong uStack_388;
  ulong uStack_380;
  undefined8 uStack_378;
  undefined8 uStack_370;
  undefined8 uStack_368;
  long lStack_360;
  undefined8 uStack_358;
  undefined8 uStack_350;
  undefined8 uStack_348;
  long lStack_340;
  undefined8 uStack_338;
  long lStack_330;
  undefined4 uStack_328;
  undefined4 uStack_324;
  undefined4 uStack_320;
  undefined4 uStack_31c;
  undefined8 uStack_318;
  undefined8 uStack_310;
  undefined8 uStack_308;
  undefined *puStack_300;
  ulong uStack_2f8;
  undefined8 uStack_2f0;
  undefined8 uStack_2e8;
  undefined8 uStack_2e0;
  undefined8 uStack_2d8;
  undefined1 auStack_2d0 [256];
  long lStack_1d0;
  undefined8 uStack_1c8;
  undefined8 *puStack_1c0;
  undefined8 *puStack_1a0;
  undefined8 uStack_198;
  undefined8 uStack_190;
  undefined8 uStack_188;
  undefined8 uStack_170;
  undefined8 uStack_168;
  undefined8 *puStack_140;
  undefined8 uStack_138;
  undefined8 *puStack_130;
  undefined8 uStack_128;
  undefined8 *puStack_120;
  undefined8 uStack_118;
  undefined8 *puStack_110;
  undefined8 uStack_108;
  undefined1 *puStack_100;
  undefined *puStack_f8;
  undefined8 uStack_f0;
  undefined8 **ppuStack_e8;
  undefined8 uStack_e0;
  undefined8 uStack_d8;
  undefined8 uStack_d0;
  undefined8 uStack_c8;
  undefined8 uStack_c0;
  undefined8 *puStack_b8;
  undefined8 *puStack_b0;
  undefined8 uStack_a8;
  undefined8 *puStack_a0;
  undefined8 uStack_98;
  undefined8 *puStack_90;
  undefined8 uStack_88;
  undefined8 uStack_80;
  undefined *puStack_78;
  undefined8 uStack_60;
  undefined8 uStack_58;
  undefined8 *puStack_30;
  undefined8 uStack_28;
  undefined8 uStack_20;
  undefined *puStack_18;
  undefined8 *puStack_10;
  
  uStack0000000000000008 = in_RAX;
  uStack0000000000000018 = param_4;
  uStack0000000000000010 = unaff_RBX;
  lStack0000000000000020 = param_1;
  while (&uStack_388 <= *(ulong **)(unaff_R14 + 0x10)) {
    runtime_morestack_noctxt();
  }
  puStack_10 = (undefined8 *)runtime_newobject();
  uStack_170 = uStack0000000000000008;
  uStack_168 = uStack0000000000000010;
  gorm_io_gorm_DB_Session();
  gorm_io_gorm_DB_Raw(0,0,extraout_RDX,0x17b,0);
  lVar3 = gorm_io_gorm_DB_Scan();
  uStack_188 = *(undefined8 *)(lVar3 + 0x10);
  if (*(long *)(lVar3 + 8) == 0) {
    if (puStack_10[1] != 0) {
      uStack_198 = runtime_convT64();
      puStack_1a0 = &DAT_0194e460;
      puStack_100 = &LAB_01108160;
      uStack_f0 = 0x3f;
      puStack_f8 = &DAT_01c95733;
      uStack_e0 = 1;
      uStack_d8 = 1;
      ppuStack_e8 = &puStack_1a0;
      log_Logger_output(&puStack_100);
      puVar5 = (undefined8 *)*puStack_10;
      for (lStack_360 = puStack_10[1]; 0 < lStack_360; lStack_360 = lStack_360 + -1) {
        uStack_350 = *puVar5;
        uStack_348 = puVar5[1];
        lStack_340 = puVar5[2];
        uStack_338 = puVar5[3];
        lStack_330 = puVar5[4];
        uStack_328 = *(undefined4 *)(puVar5 + 5);
        uStack_324 = *(undefined4 *)((long)puVar5 + 0x2c);
        uStack_320 = *(undefined4 *)(puVar5 + 6);
        uStack_31c = *(undefined4 *)((long)puVar5 + 0x34);
        lStack_1d0 = in_XMM15_Qa;
        puStack_b8 = puVar5;
        FUN_00488cb4(auStack_2d0);
        uStack_2d8 = 0x8080808080808080;
        puStack_1c0 = &uStack_2d8;
        uStack_1c8 = runtime_rand();
        if (lStack_340 != 0) {
          if (lStack_340 < 3) {
            cVar2 = '\0';
          }
          else {
            cVar2 = runtime_memequal();
          }
          lVar3 = lStack_340;
          if ((cVar2 != '\0') && (uVar4 = kiro2api_internal_crypt_DecryptCredential(), lVar3 != 0)) {
            uStack_308 = uVar4;
            puVar5 = (undefined8 *)runtime_mapassign_faststr(5);
            puVar5[1] = lVar3;
            if (DAT_02e5e450 != 0) {
              auVar9 = runtime_gcWriteBarrier2();
              puVar5 = auVar9._0_8_;
              *in_R11 = uStack_308;
              in_R11[1] = auVar9._8_8_;
            }
            *puVar5 = uStack_308;
          }
        }
        if (lStack_330 != 0) {
          if (lStack_330 < 3) {
            cVar2 = '\0';
          }
          else {
            cVar2 = runtime_memequal();
          }
          lVar3 = lStack_330;
          if ((cVar2 != '\0') && (uVar4 = kiro2api_internal_crypt_DecryptCredential(), lVar3 != 0)) {
            uStack_310 = uVar4;
            puVar5 = (undefined8 *)runtime_mapassign_faststr(0xb);
            puVar5[1] = lVar3;
            if (DAT_02e5e450 != 0) {
              auVar9 = runtime_gcWriteBarrier2();
              puVar5 = auVar9._0_8_;
              *in_R11 = uStack_310;
              in_R11[1] = auVar9._8_8_;
            }
            *puVar5 = uStack_310;
          }
        }
        if (CONCAT44(uStack_31c,uStack_320) != 0) {
          if (CONCAT44(uStack_31c,uStack_320) < 3) {
            cVar2 = '\0';
          }
          else {
            cVar2 = runtime_memequal();
          }
          if (cVar2 != '\0') {
            lVar3 = CONCAT44(uStack_31c,uStack_320);
            uVar4 = kiro2api_internal_crypt_DecryptCredential();
            if (lVar3 != 0) {
              uStack_318 = uVar4;
              puVar5 = (undefined8 *)runtime_mapassign_faststr(0xd);
              puVar5[1] = lVar3;
              if (DAT_02e5e450 != 0) {
                auVar9 = runtime_gcWriteBarrier2();
                puVar5 = auVar9._0_8_;
                *in_R11 = uStack_318;
                in_R11[1] = auVar9._8_8_;
              }
              *puVar5 = uStack_318;
            }
          }
        }
        lVar3 = lStack0000000000000020;
        if (lStack_1d0 != 0) {
          puVar8 = &DAT_01c44107;
          uVar6 = kiro2api_internal_gate_Encrypt(10,&lStack_1d0);
          if (lVar3 == 0) {
            uStack_2f0 = uStack_348;
            uStack_2e8 = uStack_338;
            uStack_2e0 = CONCAT44(uStack_324,uStack_328);
            uStack_2f8 = uVar6;
            puVar5 = (undefined8 *)runtime_mapaccess2_faststr(5);
            uVar1 = uStack_2f8;
            uStack_c0 = *puVar5;
            uStack_368 = puVar5[1];
            puVar5 = (undefined8 *)runtime_mapaccess2_faststr(0xb);
            uStack_c8 = *puVar5;
            uStack_370 = puVar5[1];
            puVar5 = (undefined8 *)runtime_mapaccess2_faststr(0xd);
            uStack_d0 = *puVar5;
            uStack_378 = puVar5[1];
            uStack_380 = uVar6 & 0xff;
            uStack_388 = uVar1 & 0xff;
            uStack_60 = uStack0000000000000008;
            uStack_58 = uStack0000000000000010;
            uStack_358 = gorm_io_gorm_DB_Session();
            uStack_138 = runtime_convTstring();
            puStack_140 = &DAT_0194e220;
            uStack_128 = runtime_convTstring();
            puStack_130 = &DAT_0194e220;
            uStack_118 = runtime_convTstring();
            puStack_120 = &DAT_0194e220;
            uStack_108 = runtime_convT64();
            puStack_110 = &DAT_0194e420;
            lVar7 = gorm_io_gorm_DB_Exec(&puStack_140,4,&DAT_0194e420,0x65,4);
            lVar3 = *(long *)(lVar7 + 8);
            if (lVar3 != 0) {
              puStack_300 = *(undefined **)(lVar7 + 0x10);
              uStack_88 = runtime_convT64();
              puStack_90 = &DAT_0194e420;
              uStack_80 = 0;
              if (lVar3 != 0) {
                uStack_80 = *(undefined8 *)(lVar3 + 8);
              }
              puStack_78 = puStack_300;
              puStack_100 = &LAB_011080a0;
              uStack_f0 = 0x3a;
              puStack_f8 = &DAT_01c9141c;
              uStack_e0 = 2;
              uStack_d8 = 2;
              ppuStack_e8 = &puStack_90;
              log_Logger_output(&puStack_100);
            }
          }
          else {
            puStack_300 = puVar8;
            uStack_28 = runtime_convT64();
            puStack_30 = &DAT_0194e420;
            if (lVar3 == 0) {
              uStack_20 = 0;
            }
            else {
              uStack_20 = *(undefined8 *)(lVar3 + 8);
            }
            puStack_18 = puStack_300;
            puStack_100 = &LAB_01108100;
            uStack_f0 = 0x40;
            puStack_f8 = &DAT_01c96050;
            uStack_e0 = 2;
            uStack_d8 = 2;
            ppuStack_e8 = &puStack_30;
            log_Logger_output(&puStack_100);
          }
        }
        puVar5 = puStack_b8 + 7;
      }
      lStack_360 = puStack_10[1];
      uStack_a8 = runtime_convT64();
      puStack_b0 = &DAT_0194e460;
      uStack_98 = runtime_convT64();
      puStack_a0 = &DAT_0194e460;
      puStack_100 = &LAB_01108040;
      uStack_f0 = 0x35;
      puStack_f8 = &DAT_01c8be85;
      uStack_e0 = 2;
      uStack_d8 = 2;
      ppuStack_e8 = &puStack_b0;
      log_Logger_output(&puStack_100);
      return;
    }
    return;
  }
  uStack_190 = *(undefined8 *)(*(long *)(lVar3 + 8) + 8);
  puStack_100 = &LAB_011081c0;
  uStack_f0 = 0x37;
  puStack_f8 = &DAT_01c8e5b4;
  uStack_e0 = 1;
  uStack_d8 = 1;
  ppuStack_e8 = (undefined8 **)&uStack_190;
  log_Logger_output(&puStack_100);
  return;
}


