// CodeFreeMax - CONTROLLER Channel Decompiled Functions
// 3 functions

// === controller.ConfigController.Save @ 0x1365fc0 ===

void controller_ConfigController_Save(void)

{
  undefined *puVar1;
  long lVar2;
  undefined8 uVar3;
  undefined8 *puVar4;
  undefined8 uVar5;
  undefined8 *in_R11;
  long unaff_R14;
  undefined8 in_XMM15_Qa;
  undefined8 in_XMM15_Qb;
  undefined1 auVar6 [16];
  undefined8 uStack_160;
  undefined8 uStack_158;
  undefined8 uStack_150;
  undefined8 uStack_148;
  undefined1 auStack_140 [256];
  undefined1 auStack_40 [8];
  undefined8 uStack_38;
  undefined8 *puStack_30;
  undefined8 *puStack_10;
  
  while (&uStack_160 <= *(undefined8 **)(unaff_R14 + 0x10)) {
    runtime_morestack_noctxt();
  }
  puStack_10 = (undefined8 *)runtime_newobject();
  lVar2 = github_com_gogf_gf_v2_net_ghttp_Request_doParse(0);
  if (lVar2 != 0) {
    uVar3 = runtime_makemap_small();
    uStack_150 = uVar3;
    puVar4 = (undefined8 *)runtime_mapassign_faststr(4);
    *puVar4 = &DAT_0194e460;
    if (DAT_02e5e450 != 0) {
      uVar5 = puVar4[1];
      puVar4 = (undefined8 *)runtime_gcWriteBarrier1();
      *in_R11 = uVar5;
    }
    puVar4[1] = &DAT_01f386d0;
    auVar6 = (**(code **)(lVar2 + 0x18))();
    runtime_concatstring2(auVar6._0_8_,uVar3,auVar6._8_8_,0xe);
    uStack_158 = runtime_convTstring();
    puVar4 = (undefined8 *)runtime_mapassign_faststr(3);
    *puVar4 = &DAT_0194e220;
    if (DAT_02e5e450 != 0) goto LAB_0136612d;
    do {
      puVar4[1] = uStack_158;
      github_com_gogf_gf_v2_net_ghttp_Response_WriteJson();
      runtime_gopanic();
LAB_0136612d:
      auVar6 = runtime_gcWriteBarrier2();
      puVar4 = auVar6._0_8_;
      *in_R11 = uStack_158;
      in_R11[1] = auVar6._8_8_;
    } while( true );
  }
  github_com_gogf_gf_v2_net_ghttp_Request_Context();
  FUN_00488cb4(auStack_140);
  uStack_148 = 0x8080808080808080;
  puStack_30 = &uStack_148;
  uStack_38 = runtime_rand();
  lVar2 = puStack_10[1];
  if (lVar2 != 0) {
    uStack_160 = *puStack_10;
    puVar4 = (undefined8 *)runtime_mapassign_faststr(7);
    puVar4[1] = lVar2;
    if (DAT_02e5e450 != 0) {
      auVar6 = runtime_gcWriteBarrier2();
      puVar4 = auVar6._0_8_;
      *in_R11 = uStack_160;
      in_R11[1] = auVar6._8_8_;
    }
    *puVar4 = uStack_160;
  }
  uVar3 = puStack_10[3];
  uStack_160 = puStack_10[2];
  puVar4 = (undefined8 *)runtime_mapassign_faststr(9);
  puVar4[1] = uVar3;
  if (DAT_02e5e450 != 0) {
    auVar6 = runtime_gcWriteBarrier2();
    puVar4 = auVar6._0_8_;
    *in_R11 = uStack_160;
    in_R11[1] = auVar6._8_8_;
  }
  *puVar4 = uStack_160;
  lVar2 = puStack_10[5];
  if (lVar2 != 0) {
    uStack_160 = puStack_10[4];
    puVar4 = (undefined8 *)runtime_mapassign_faststr(0xb,lVar2,uStack_160,&DAT_01c46000);
    puVar4[1] = lVar2;
    if (DAT_02e5e450 != 0) {
      auVar6 = runtime_gcWriteBarrier2();
      puVar4 = auVar6._0_8_;
      *in_R11 = uStack_160;
      in_R11[1] = auVar6._8_8_;
    }
    *puVar4 = uStack_160;
  }
  lVar2 = puStack_10[7];
  if (lVar2 != 0) {
    uStack_160 = puStack_10[6];
    puVar4 = (undefined8 *)runtime_mapassign_faststr(0xb,lVar2,uStack_160,&DAT_01c4600b);
    puVar4[1] = lVar2;
    if (DAT_02e5e450 != 0) {
      auVar6 = runtime_gcWriteBarrier2();
      puVar4 = auVar6._0_8_;
      *in_R11 = uStack_160;
      in_R11[1] = auVar6._8_8_;
    }
    *puVar4 = uStack_160;
  }
  lVar2 = puStack_10[9];
  if (lVar2 != 0) {
    uStack_160 = puStack_10[8];
    puVar4 = (undefined8 *)runtime_mapassign_faststr(0x12,lVar2,uStack_160,&DAT_01c52eed);
    puVar4[1] = lVar2;
    if (DAT_02e5e450 != 0) {
      auVar6 = runtime_gcWriteBarrier2();
      puVar4 = auVar6._0_8_;
      *in_R11 = uStack_160;
      in_R11[1] = auVar6._8_8_;
    }
    *puVar4 = uStack_160;
  }
  lVar2 = puStack_10[0xb];
  if (lVar2 != 0) {
    uStack_160 = puStack_10[10];
    puVar4 = (undefined8 *)runtime_mapassign_faststr(0xf,lVar2,uStack_160,&DAT_01c4d07b);
    puVar4[1] = lVar2;
    if (DAT_02e5e450 != 0) {
      auVar6 = runtime_gcWriteBarrier2();
      puVar4 = auVar6._0_8_;
      *in_R11 = uStack_160;
      in_R11[1] = auVar6._8_8_;
    }
    *puVar4 = uStack_160;
  }
  lVar2 = puStack_10[0xd];
  if (lVar2 != 0) {
    uStack_160 = puStack_10[0xc];
    puVar4 = (undefined8 *)runtime_mapassign_faststr(0x12,lVar2,uStack_160,&DAT_01c52eff);
    puVar4[1] = lVar2;
    if (DAT_02e5e450 != 0) {
      auVar6 = runtime_gcWriteBarrier2();
      puVar4 = auVar6._0_8_;
      *in_R11 = uStack_160;
      in_R11[1] = auVar6._8_8_;
    }
    *puVar4 = uStack_160;
  }
  lVar2 = puStack_10[0xf];
  if (lVar2 != 0) {
    uStack_160 = puStack_10[0xe];
    puVar4 = (undefined8 *)runtime_mapassign_faststr(0x10,lVar2,uStack_160,&DAT_01c4edf3);
    puVar4[1] = lVar2;
    if (DAT_02e5e450 != 0) {
      auVar6 = runtime_gcWriteBarrier2();
      puVar4 = auVar6._0_8_;
      *in_R11 = uStack_160;
      in_R11[1] = auVar6._8_8_;
    }
    *puVar4 = uStack_160;
  }
  lVar2 = puStack_10[0x11];
  if (lVar2 != 0) {
    uStack_160 = puStack_10[0x10];
    puVar4 = (undefined8 *)runtime_mapassign_faststr(0xe,lVar2,uStack_160,&DAT_01c4b457);
    puVar4[1] = lVar2;
    if (DAT_02e5e450 != 0) {
      auVar6 = runtime_gcWriteBarrier2();
      puVar4 = auVar6._0_8_;
      *in_R11 = uStack_160;
      in_R11[1] = auVar6._8_8_;
    }
    *puVar4 = uStack_160;
  }
  lVar2 = puStack_10[0x13];
  if (lVar2 != 0) {
    uStack_160 = puStack_10[0x12];
    puVar4 = (undefined8 *)runtime_mapassign_faststr(0x14,lVar2,uStack_160,&DAT_01c56bc2);
    puVar4[1] = lVar2;
    if (DAT_02e5e450 != 0) {
      auVar6 = runtime_gcWriteBarrier2();
      puVar4 = auVar6._0_8_;
      *in_R11 = uStack_160;
      in_R11[1] = auVar6._8_8_;
    }
    *puVar4 = uStack_160;
  }
  lVar2 = puStack_10[0x15];
  if (lVar2 != 0) {
    uStack_160 = puStack_10[0x14];
    puVar4 = (undefined8 *)runtime_mapassign_faststr(0x14,lVar2,uStack_160,&DAT_01c56bd6);
    puVar4[1] = lVar2;
    if (DAT_02e5e450 != 0) {
      auVar6 = runtime_gcWriteBarrier2();
      puVar4 = auVar6._0_8_;
      *in_R11 = uStack_160;
      in_R11[1] = auVar6._8_8_;
    }
    *puVar4 = uStack_160;
  }
  lVar2 = puStack_10[0x17];
  if (lVar2 != 0) {
    uStack_160 = puStack_10[0x16];
    puVar4 = (undefined8 *)runtime_mapassign_faststr(0x12,lVar2,uStack_160,&DAT_01c52f11);
    puVar4[1] = lVar2;
    if (DAT_02e5e450 != 0) {
      auVar6 = runtime_gcWriteBarrier2();
      puVar4 = auVar6._0_8_;
      *in_R11 = uStack_160;
      in_R11[1] = auVar6._8_8_;
    }
    *puVar4 = uStack_160;
  }
  lVar2 = puStack_10[0x19];
  if (lVar2 != 0) {
    uStack_160 = puStack_10[0x18];
    puVar4 = (undefined8 *)runtime_mapassign_faststr(0x12,lVar2,uStack_160,&DAT_01c52f23);
    puVar4[1] = lVar2;
    if (DAT_02e5e450 != 0) {
      auVar6 = runtime_gcWriteBarrier2();
      puVar4 = auVar6._0_8_;
      *in_R11 = uStack_160;
      in_R11[1] = auVar6._8_8_;
    }
    *puVar4 = uStack_160;
  }
  lVar2 = puStack_10[0x1b];
  if (lVar2 != 0) {
    uStack_160 = puStack_10[0x1a];
    puVar4 = (undefined8 *)runtime_mapassign_faststr(0xf,lVar2,uStack_160,&DAT_01c4d08a);
    puVar4[1] = lVar2;
    if (DAT_02e5e450 != 0) {
      auVar6 = runtime_gcWriteBarrier2();
      puVar4 = auVar6._0_8_;
      *in_R11 = uStack_160;
      in_R11[1] = auVar6._8_8_;
    }
    *puVar4 = uStack_160;
  }
  lVar2 = puStack_10[0x1d];
  if (lVar2 != 0) {
    uStack_160 = puStack_10[0x1c];
    puVar4 = (undefined8 *)runtime_mapassign_faststr(0x14,lVar2,uStack_160,&DAT_01c56c62);
    puVar4[1] = lVar2;
    if (DAT_02e5e450 != 0) {
      auVar6 = runtime_gcWriteBarrier2();
      puVar4 = auVar6._0_8_;
      *in_R11 = uStack_160;
      in_R11[1] = auVar6._8_8_;
    }
    *puVar4 = uStack_160;
  }
  lVar2 = puStack_10[0x1f];
  if (lVar2 != 0) {
    uStack_160 = puStack_10[0x1e];
    puVar4 = (undefined8 *)runtime_mapassign_faststr(0x17,lVar2,uStack_160,&DAT_01c5bf27);
    puVar4[1] = lVar2;
    if (DAT_02e5e450 != 0) {
      auVar6 = runtime_gcWriteBarrier2();
      puVar4 = auVar6._0_8_;
      *in_R11 = uStack_160;
      in_R11[1] = auVar6._8_8_;
    }
    *puVar4 = uStack_160;
  }
  uVar3 = puStack_10[0x21];
  uStack_160 = puStack_10[0x20];
  puVar4 = (undefined8 *)runtime_mapassign_faststr(0xe,uVar3,uStack_160,&DAT_01c4b473);
  puVar4[1] = uVar3;
  if (DAT_02e5e450 != 0) {
    auVar6 = runtime_gcWriteBarrier2();
    puVar4 = auVar6._0_8_;
    *in_R11 = uStack_160;
    in_R11[1] = auVar6._8_8_;
  }
  *puVar4 = uStack_160;
  uVar3 = puStack_10[0x23];
  uStack_160 = puStack_10[0x22];
  puVar4 = (undefined8 *)runtime_mapassign_faststr(0x11,uVar3,uStack_160,&DAT_01c50ceb);
  puVar4[1] = uVar3;
  if (DAT_02e5e450 != 0) {
    auVar6 = runtime_gcWriteBarrier2();
    puVar4 = auVar6._0_8_;
    *in_R11 = uStack_160;
    in_R11[1] = auVar6._8_8_;
  }
  *puVar4 = uStack_160;
  lVar2 = puStack_10[0x25];
  if (lVar2 != 0) {
    uStack_160 = puStack_10[0x24];
    puVar4 = (undefined8 *)runtime_mapassign_faststr(0x16,lVar2,uStack_160,&DAT_01c5a48d);
    puVar4[1] = lVar2;
    if (DAT_02e5e450 != 0) {
      auVar6 = runtime_gcWriteBarrier2();
      puVar4 = auVar6._0_8_;
      *in_R11 = uStack_160;
      in_R11[1] = auVar6._8_8_;
    }
    *puVar4 = uStack_160;
  }
  uVar3 = puStack_10[0x27];
  uStack_160 = puStack_10[0x26];
  puVar4 = (undefined8 *)runtime_mapassign_faststr(0x15,uVar3,uStack_160,&DAT_01c58a30);
  puVar4[1] = uVar3;
  if (DAT_02e5e450 != 0) {
    auVar6 = runtime_gcWriteBarrier2();
    puVar4 = auVar6._0_8_;
    *in_R11 = uStack_160;
    in_R11[1] = auVar6._8_8_;
  }
  *puVar4 = uStack_160;
  uVar3 = puStack_10[0x29];
  uStack_160 = puStack_10[0x28];
  puVar4 = (undefined8 *)runtime_mapassign_faststr(0x10,uVar3,uStack_160,&DAT_01c4ee03);
  puVar4[1] = uVar3;
  if (DAT_02e5e450 != 0) {
    auVar6 = runtime_gcWriteBarrier2();
    puVar4 = auVar6._0_8_;
    *in_R11 = uStack_160;
    in_R11[1] = auVar6._8_8_;
  }
  *puVar4 = uStack_160;
  uVar3 = puStack_10[0x2b];
  uStack_160 = puStack_10[0x2a];
  puVar4 = (undefined8 *)runtime_mapassign_faststr(0xe,uVar3,uStack_160,&DAT_01c4b481);
  puVar4[1] = uVar3;
  if (DAT_02e5e450 != 0) {
    auVar6 = runtime_gcWriteBarrier2();
    puVar4 = auVar6._0_8_;
    *in_R11 = uStack_160;
    in_R11[1] = auVar6._8_8_;
  }
  *puVar4 = uStack_160;
  lVar2 = puStack_10[0x2d];
  if (lVar2 != 0) {
    uStack_160 = puStack_10[0x2c];
    puVar4 = (undefined8 *)runtime_mapassign_faststr(0x16,lVar2,uStack_160,&DAT_01c5a4a3);
    puVar4[1] = lVar2;
    if (DAT_02e5e450 != 0) {
      auVar6 = runtime_gcWriteBarrier2();
      puVar4 = auVar6._0_8_;
      *in_R11 = uStack_160;
      in_R11[1] = auVar6._8_8_;
    }
    *puVar4 = uStack_160;
  }
  lVar2 = puStack_10[0x2f];
  if (lVar2 != 0) {
    uStack_160 = puStack_10[0x2e];
    puVar4 = (undefined8 *)runtime_mapassign_faststr(0x16,lVar2,uStack_160,&DAT_01c5a4b9);
    puVar4[1] = lVar2;
    if (DAT_02e5e450 != 0) {
      auVar6 = runtime_gcWriteBarrier2();
      puVar4 = auVar6._0_8_;
      *in_R11 = uStack_160;
      in_R11[1] = auVar6._8_8_;
    }
    *puVar4 = uStack_160;
  }
  lVar2 = puStack_10[0x31];
  if (lVar2 != 0) {
    uStack_160 = puStack_10[0x30];
    puVar4 = (undefined8 *)runtime_mapassign_faststr(0x19,lVar2,uStack_160,&DAT_01c5fa06);
    puVar4[1] = lVar2;
    if (DAT_02e5e450 != 0) {
      auVar6 = runtime_gcWriteBarrier2();
      puVar4 = auVar6._0_8_;
      *in_R11 = uStack_160;
      in_R11[1] = auVar6._8_8_;
    }
    *puVar4 = uStack_160;
  }
  lVar2 = puStack_10[0x33];
  if (lVar2 != 0) {
    uStack_160 = puStack_10[0x32];
    puVar4 = (undefined8 *)runtime_mapassign_faststr(0x1d,lVar2,uStack_160,&DAT_01c66c58);
    puVar4[1] = lVar2;
    if (DAT_02e5e450 != 0) {
      auVar6 = runtime_gcWriteBarrier2();
      puVar4 = auVar6._0_8_;
      *in_R11 = uStack_160;
      in_R11[1] = auVar6._8_8_;
    }
    *puVar4 = uStack_160;
  }
  lVar2 = puStack_10[0x35];
  if (lVar2 != 0) {
    uStack_160 = puStack_10[0x34];
    puVar4 = (undefined8 *)runtime_mapassign_faststr(0x12,lVar2,uStack_160,&DAT_01c52f35);
    puVar4[1] = lVar2;
    if (DAT_02e5e450 != 0) {
      auVar6 = runtime_gcWriteBarrier2();
      puVar4 = auVar6._0_8_;
      *in_R11 = uStack_160;
      in_R11[1] = auVar6._8_8_;
    }
    *puVar4 = uStack_160;
  }
  lVar2 = kiro2api_internal_dao_ConfigDao_SetBatch(auStack_40);
  puVar1 = PTR_DAT_02ddf0d0;
  if (lVar2 == 0) {
    if (DAT_02e5e450 != 0) {
      runtime_wbZero();
    }
    *(undefined8 *)puVar1 = in_XMM15_Qa;
    *(undefined8 *)(puVar1 + 8) = in_XMM15_Qb;
    *(undefined8 *)(puVar1 + 0x10) = in_XMM15_Qa;
    *(undefined8 *)(puVar1 + 0x18) = in_XMM15_Qb;
    *(undefined8 *)(puVar1 + 0x20) = in_XMM15_Qa;
    *(undefined8 *)(puVar1 + 0x28) = in_XMM15_Qb;
    kiro2api_internal_tokencount_ClearConfigCache();
    uStack_150 = runtime_makemap_small();
    puVar4 = (undefined8 *)runtime_mapassign_faststr(4);
    *puVar4 = &DAT_0194e460;
    if (DAT_02e5e450 != 0) {
      auVar6 = runtime_gcWriteBarrier1();
      puVar4 = auVar6._0_8_;
      *in_R11 = auVar6._8_8_;
    }
    puVar4[1] = &DAT_01f385c0;
    puVar4 = (undefined8 *)runtime_mapassign_faststr(3);
    *puVar4 = &DAT_0194e220;
    if (DAT_02e5e450 != 0) goto LAB_013666b9;
    do {
      puVar4[1] = &PTR_DAT_01f39650;
      github_com_gogf_gf_v2_net_ghttp_Response_WriteJson();
      runtime_gopanic();
LAB_013666b9:
      auVar6 = runtime_gcWriteBarrier1();
      puVar4 = auVar6._0_8_;
      *in_R11 = auVar6._8_8_;
    } while( true );
  }
  uVar3 = runtime_makemap_small();
  uStack_150 = uVar3;
  puVar4 = (undefined8 *)runtime_mapassign_faststr(4);
  *puVar4 = &DAT_0194e460;
  if (DAT_02e5e450 != 0) {
    uVar5 = puVar4[1];
    puVar4 = (undefined8 *)runtime_gcWriteBarrier1();
    *in_R11 = uVar5;
  }
  puVar4[1] = &DAT_01f386e0;
  auVar6 = (**(code **)(lVar2 + 0x18))();
  runtime_concatstring2(auVar6._0_8_,uVar3,auVar6._8_8_,0x14);
  uStack_158 = runtime_convTstring();
  puVar4 = (undefined8 *)runtime_mapassign_faststr(3);
  *puVar4 = &DAT_0194e220;
  if (DAT_02e5e450 != 0) goto LAB_01366805;
  do {
    puVar4[1] = uStack_158;
    github_com_gogf_gf_v2_net_ghttp_Response_WriteJson();
    runtime_gopanic();
LAB_01366805:
    auVar6 = runtime_gcWriteBarrier2();
    puVar4 = auVar6._0_8_;
    *in_R11 = uStack_158;
    in_R11[1] = auVar6._8_8_;
  } while( true );
}




// === controller.TestController.Test @ 0x136bfe0 ===

/* WARNING: Removing unreachable block (ram,0x0136c50f) */
/* WARNING: Removing unreachable block (ram,0x0136c5b2) */
/* WARNING: Removing unreachable block (ram,0x0136c5a8) */
/* WARNING: Removing unreachable block (ram,0x0136c5c9) */
/* WARNING: Removing unreachable block (ram,0x0136c688) */
/* WARNING: Removing unreachable block (ram,0x0136c67e) */
/* WARNING: Removing unreachable block (ram,0x0136c698) */
/* WARNING: Removing unreachable block (ram,0x0136c6ec) */
/* WARNING: Removing unreachable block (ram,0x0136c6e2) */
/* WARNING: Removing unreachable block (ram,0x0136c703) */
/* WARNING: Removing unreachable block (ram,0x0136c72f) */
/* WARNING: Removing unreachable block (ram,0x0136c7a2) */
/* WARNING: Removing unreachable block (ram,0x0136c797) */
/* WARNING: Removing unreachable block (ram,0x0136c7b2) */
/* WARNING: Removing unreachable block (ram,0x0136c808) */
/* WARNING: Removing unreachable block (ram,0x0136c7fe) */
/* WARNING: Removing unreachable block (ram,0x0136c81f) */
/* WARNING: Removing unreachable block (ram,0x0136c822) */
/* WARNING: Removing unreachable block (ram,0x0136c84e) */
/* WARNING: Removing unreachable block (ram,0x0136c8c2) */
/* WARNING: Removing unreachable block (ram,0x0136c8b7) */
/* WARNING: Removing unreachable block (ram,0x0136c8d2) */
/* WARNING: Removing unreachable block (ram,0x0136c928) */
/* WARNING: Removing unreachable block (ram,0x0136c91e) */
/* WARNING: Removing unreachable block (ram,0x0136c93f) */
/* WARNING: Removing unreachable block (ram,0x0136c942) */
/* WARNING: Removing unreachable block (ram,0x0136cd67) */
/* WARNING: Removing unreachable block (ram,0x0136ce9f) */
/* WARNING: Removing unreachable block (ram,0x0136cdb6) */
/* WARNING: Removing unreachable block (ram,0x0136ce30) */
/* WARNING: Removing unreachable block (ram,0x0136ce85) */
/* WARNING: Removing unreachable block (ram,0x0136c969) */
/* WARNING: Removing unreachable block (ram,0x0136ca06) */
/* WARNING: Removing unreachable block (ram,0x0136ca13) */
/* WARNING: Removing unreachable block (ram,0x0136cc43) */
/* WARNING: Removing unreachable block (ram,0x0136cc4c) */
/* WARNING: Removing unreachable block (ram,0x0136ccd2) */
/* WARNING: Removing unreachable block (ram,0x0136cd03) */
/* WARNING: Removing unreachable block (ram,0x0136cd12) */
/* WARNING: Removing unreachable block (ram,0x0136cd1e) */
/* WARNING: Removing unreachable block (ram,0x0136cd4a) */
/* WARNING: Removing unreachable block (ram,0x0136cd3d) */
/* WARNING: Removing unreachable block (ram,0x0136cc10) */
/* WARNING: Removing unreachable block (ram,0x0136c9f1) */
/* WARNING: Removing unreachable block (ram,0x0136ca3e) */
/* WARNING: Removing unreachable block (ram,0x0136ca96) */
/* WARNING: Removing unreachable block (ram,0x0136cabc) */
/* WARNING: Removing unreachable block (ram,0x0136caeb) */
/* WARNING: Removing unreachable block (ram,0x0136cb92) */
/* WARNING: Removing unreachable block (ram,0x0136caf7) */
/* WARNING: Removing unreachable block (ram,0x0136cb6e) */
/* WARNING: Removing unreachable block (ram,0x0136cab4) */
/* WARNING: Removing unreachable block (ram,0x0136ca64) */
/* WARNING: Removing unreachable block (ram,0x0136ca7f) */
/* WARNING: Removing unreachable block (ram,0x0136cbb8) */
/* WARNING: Removing unreachable block (ram,0x0136cc09) */
/* WARNING: Removing unreachable block (ram,0x0136cbcc) */
/* WARNING: Removing unreachable block (ram,0x0136cbd5) */
/* WARNING: Removing unreachable block (ram,0x0136cb9f) */
/* WARNING: Removing unreachable block (ram,0x0136cb77) */

void controller_TestController_Test(void)

{
  long lVar1;
  undefined8 *puVar2;
  undefined8 uVar3;
  undefined8 *puVar4;
  undefined8 uVar5;
  long extraout_RDX;
  long unaff_RBX;
  undefined8 *in_R11;
  long unaff_R14;
  undefined1 auVar6 [16];
  long lStack0000000000000010;
  undefined8 uStack_1e8;
  undefined8 *puStack_1e0;
  undefined8 uStack_1c0;
  ulong uStack_1b8;
  undefined8 *puStack_1b0;
  undefined *puStack_198;
  undefined8 uStack_170;
  undefined8 uStack_168;
  undefined8 uStack_150;
  undefined8 uStack_148;
  undefined8 uStack_140;
  undefined8 uStack_108;
  undefined8 uStack_100;
  undefined8 uStack_d0;
  undefined8 uStack_c8;
  undefined8 *puStack_38;
  undefined8 uStack_30;
  undefined8 *puStack_28;
  undefined8 uStack_20;
  long lStack_18;
  
  lStack0000000000000010 = unaff_RBX;
  while (&uStack_1e8 <= *(undefined8 **)(unaff_R14 + 0x10)) {
    runtime_morestack_noctxt();
  }
  lStack_18 = runtime_newobject();
  lVar1 = github_com_gogf_gf_v2_net_ghttp_Request_doParse(0);
  if (lVar1 != 0) {
    puStack_198 = &DAT_01904e20;
    uStack_d0 = runtime_makemap_small();
    puVar2 = (undefined8 *)runtime_mapassign_faststr(4);
    *puVar2 = &DAT_0194e460;
    if (DAT_02e5e450 != 0) {
      uVar3 = puVar2[1];
      puVar2 = (undefined8 *)runtime_gcWriteBarrier1();
      *in_R11 = uVar3;
    }
    puVar2[1] = &DAT_01f34d28;
    (**(code **)(lVar1 + 0x18))();
    uStack_c8 = runtime_convTstring();
    puVar2 = (undefined8 *)runtime_mapassign_faststr(7);
    *puVar2 = &DAT_0194e220;
    if (DAT_02e5e450 != 0) goto LAB_0136d225;
    do {
      puVar2[1] = uStack_c8;
      uStack_140 = *(undefined8 *)(lStack0000000000000010 + 0x20);
      github_com_gogf_gf_v2_net_ghttp_Response_WriteJson();
      runtime_gopanic();
LAB_0136d225:
      auVar6 = runtime_gcWriteBarrier2();
      puVar2 = auVar6._0_8_;
      *in_R11 = uStack_c8;
      in_R11[1] = auVar6._8_8_;
    } while( true );
  }
  lVar1 = lStack_18;
  if (*(long *)(lStack_18 + 0x30) == 0) {
    *(undefined8 *)(lStack_18 + 0x30) = 5;
    if (DAT_02e5e450 != 0) {
      uVar3 = *(undefined8 *)(lStack_18 + 0x28);
      runtime_gcWriteBarrier1();
      *in_R11 = uVar3;
      lVar1 = extraout_RDX;
    }
    *(undefined **)(lVar1 + 0x28) = &DAT_01c3a58f;
  }
  if (*(long *)(lVar1 + 0x40) == 0) {
    *(undefined8 *)(lVar1 + 0x40) = 0x400;
  }
  uVar3 = DAT_02e33260;
  puVar2 = (undefined8 *)runtime_mapaccess2_faststr(*(undefined8 *)(lVar1 + 0x10));
  uStack_100 = *puVar2;
  uStack_1c0 = puVar2[1];
  if ((char)uVar3 == '\0') {
    uStack_d0 = runtime_makemap_small();
    puVar2 = (undefined8 *)runtime_mapassign_faststr(4);
    *puVar2 = &DAT_0194e460;
    if (DAT_02e5e450 != 0) {
      auVar6 = runtime_gcWriteBarrier1();
      puVar2 = auVar6._0_8_;
      *in_R11 = auVar6._8_8_;
    }
    puVar2[1] = &DAT_01f34d28;
    runtime_concatstring2(*(undefined8 *)(lStack_18 + 8),*(undefined8 *)(lStack_18 + 0x10),lStack_18,0x14);
    uStack_c8 = runtime_convTstring();
    puVar2 = (undefined8 *)runtime_mapassign_faststr(7);
    *puVar2 = &DAT_0194e220;
    if (DAT_02e5e450 != 0) goto LAB_0136d0f6;
    do {
      puVar2[1] = uStack_c8;
      uStack_148 = *(undefined8 *)(lStack0000000000000010 + 0x20);
      github_com_gogf_gf_v2_net_ghttp_Response_WriteJson();
      runtime_gopanic();
LAB_0136d0f6:
      auVar6 = runtime_gcWriteBarrier2();
      puVar2 = auVar6._0_8_;
      *in_R11 = uStack_c8;
      in_R11[1] = auVar6._8_8_;
    } while( true );
  }
  uStack_108 = runtime_makemap_small();
  uStack_c8 = runtime_convTstring();
  puVar2 = (undefined8 *)runtime_mapassign_faststr(5);
  *puVar2 = &DAT_0194e220;
  if (DAT_02e5e450 != 0) {
    auVar6 = runtime_gcWriteBarrier2();
    puVar2 = auVar6._0_8_;
    *in_R11 = uStack_c8;
    in_R11[1] = auVar6._8_8_;
  }
  puVar2[1] = uStack_c8;
  uStack_d0 = runtime_makemap_small();
  puVar2 = (undefined8 *)runtime_mapassign_faststr(4);
  *puVar2 = &DAT_0194e220;
  if (DAT_02e5e450 != 0) {
    auVar6 = runtime_gcWriteBarrier1();
    puVar2 = auVar6._0_8_;
    *in_R11 = auVar6._8_8_;
  }
  puVar2[1] = &PTR_DAT_01f39720;
  uStack_c8 = runtime_convTstring();
  puVar2 = (undefined8 *)runtime_mapassign_faststr(7);
  *puVar2 = &DAT_0194e220;
  if (DAT_02e5e450 != 0) {
    auVar6 = runtime_gcWriteBarrier2();
    puVar2 = auVar6._0_8_;
    *in_R11 = uStack_c8;
    in_R11[1] = auVar6._8_8_;
  }
  puVar2[1] = uStack_c8;
  puVar2 = (undefined8 *)runtime_newobject();
  if (DAT_02e5e450 != 0) {
    puVar2 = (undefined8 *)runtime_gcWriteBarrier1();
    *in_R11 = uStack_d0;
  }
  *puVar2 = uStack_d0;
  uStack_c8 = runtime_convTslice();
  puVar2 = (undefined8 *)runtime_mapassign_faststr(8);
  *puVar2 = &DAT_0192a2e0;
  if (DAT_02e5e450 != 0) {
    auVar6 = runtime_gcWriteBarrier2();
    puVar2 = auVar6._0_8_;
    *in_R11 = uStack_c8;
    in_R11[1] = auVar6._8_8_;
  }
  puVar2[1] = uStack_c8;
  uStack_1b8 = (ulong)*(byte *)(lStack_18 + 0x38);
  puVar2 = (undefined8 *)runtime_mapassign_faststr(6,uStack_c8,uStack_1b8,&DAT_01c3bc15);
  *puVar2 = &DAT_0194e620;
  auVar6._8_8_ = &DAT_01f8a680 + uStack_1b8 * 8;
  auVar6._0_8_ = puVar2;
  if (DAT_02e5e450 != 0) {
    uVar3 = puVar2[1];
    auVar6 = runtime_gcWriteBarrier1();
    *in_R11 = uVar3;
  }
  *(long *)(auVar6._0_8_ + 8) = auVar6._8_8_;
  uStack_c8 = runtime_convT64();
  puVar2 = (undefined8 *)runtime_mapassign_faststr(10);
  puVar4 = &DAT_0194e460;
  *puVar2 = &DAT_0194e460;
  if (DAT_02e5e450 != 0) {
    auVar6 = runtime_gcWriteBarrier2();
    puVar2 = auVar6._0_8_;
    *in_R11 = uStack_c8;
    in_R11[1] = auVar6._8_8_;
  }
  uVar3 = uStack_108;
  puVar2[1] = uStack_c8;
  uStack_168 = encoding_json_Marshal();
  uStack_1e8 = uVar3;
  puStack_1e0 = puVar4;
  github_com_gogf_gf_v2_net_ghttp_Server_GetListenedPort();
  uStack_30 = runtime_convT64();
  puStack_38 = &DAT_0194e460;
  auVar6 = runtime_convTstring();
  uStack_20 = auVar6._0_8_;
  puStack_28 = &DAT_0194e220;
  uStack_170 = fmt_Sprintf(2,2,auVar6._8_8_,&puStack_38);
  puVar2 = (undefined8 *)runtime_newobject();
  puVar2[1] = uStack_1e8;
  puVar2[2] = puStack_1e0;
  if (DAT_02e5e450 != 0) {
    puVar2 = (undefined8 *)runtime_gcWriteBarrier1();
    *in_R11 = uStack_168;
  }
  *puVar2 = uStack_168;
  puVar2[3] = 0;
  puVar2[4] = 0xffffffffffffffff;
  puVar2 = &DAT_01c39792;
  net_http_NewRequestWithContext(4,uStack_170,uStack_168,&DAT_01c39792,0x15,&PTR_DAT_01f430e0);
  puStack_1b0 = puVar2;
  uVar3 = runtime_makemap_small();
  uStack_d0 = uVar3;
  puVar2 = (undefined8 *)runtime_mapassign_faststr(4);
  *puVar2 = &DAT_0194e460;
  if (DAT_02e5e450 != 0) {
    uVar5 = puVar2[1];
    puVar2 = (undefined8 *)runtime_gcWriteBarrier1();
    *in_R11 = uVar5;
  }
  puVar2[1] = &DAT_01f34d28;
  auVar6 = (*DAT_02e5d6b8)();
  runtime_concatstring2(auVar6._0_8_,uVar3,auVar6._8_8_,0x14);
  uStack_c8 = runtime_convTstring();
  puVar2 = (undefined8 *)runtime_mapassign_faststr(7);
  *puVar2 = &DAT_0194e220;
  if (DAT_02e5e450 != 0) goto LAB_0136cfc9;
  do {
    puVar2[1] = uStack_c8;
    uStack_150 = *(undefined8 *)(lStack0000000000000010 + 0x20);
    github_com_gogf_gf_v2_net_ghttp_Response_WriteJson();
    runtime_gopanic();
LAB_0136cfc9:
    auVar6 = runtime_gcWriteBarrier2();
    puVar2 = auVar6._0_8_;
    *in_R11 = uStack_c8;
    in_R11[1] = auVar6._8_8_;
  } while( true );
}




// === controller.RegisterModelsRoute @ 0x136e2a0 ===

/* WARNING: Removing unreachable block (ram,0x0136e2fe) */
/* WARNING: Removing unreachable block (ram,0x0136e31e) */
/* WARNING: Removing unreachable block (ram,0x0136e326) */
/* WARNING: Removing unreachable block (ram,0x0136e32e) */
/* WARNING: Removing unreachable block (ram,0x0136e310) */
/* WARNING: Removing unreachable block (ram,0x0136e33a) */
/* WARNING: Removing unreachable block (ram,0x0136e349) */
/* WARNING: Removing unreachable block (ram,0x0136e351) */

void controller_RegisterModelsRoute(void)

{
  byte bVar1;
  undefined4 *puVar3;
  long lVar4;
  undefined8 uVar5;
  undefined8 uVar6;
  undefined8 *puVar7;
  ulong uVar8;
  long lVar9;
  undefined8 unaff_RBX;
  ulong uVar10;
  undefined *puVar11;
  long lVar12;
  undefined8 *in_R11;
  long unaff_R14;
  undefined1 auVar13 [16];
  long lStack_78;
  long *plStack_70;
  undefined8 uStack_68;
  long lStack_60;
  undefined8 uStack_58;
  long lStack_50;
  long lStack_48;
  undefined8 uStack_40;
  undefined8 uStack_38;
  ulong uVar2;
  
  while (&lStack_78 <= *(long **)(unaff_R14 + 0x10)) {
    runtime_morestack_noctxt();
  }
  auVar13 = github_com_gogf_gf_v2_net_ghttp_Request_Context();
  uVar2 = auVar13._0_8_;
  github_com_gogf_gf_v2_net_ghttp_Request_GetRequest(0,0,auVar13._8_8_,8,0);
  github_com_gogf_gf_v2_container_gvar_Var_String();
  puVar3 = &DAT_01c3976e;
  plStack_70 = (long *)kiro2api_internal_dao_ModelConfigDao_GetByChannel(&DAT_01c3976e,4,PTR_DAT_02ddf0e8,unaff_RBX);
  if (puVar3 != (undefined4 *)0x0) {
    runtime_makemap_small();
    puVar7 = (undefined8 *)runtime_mapassign_faststr(0xd);
    *puVar7 = &DAT_0194e220;
    if (DAT_02e5e450 != 0) {
      auVar13 = runtime_gcWriteBarrier1();
      puVar7 = auVar13._0_8_;
      *in_R11 = auVar13._8_8_;
    }
    puVar7[1] = &DAT_01f39670;
    uVar5 = runtime_convTslice();
    puVar7 = (undefined8 *)runtime_mapassign_faststr(6);
    *puVar7 = &DAT_0192a2e0;
    if (DAT_02e5e450 != 0) {
      uVar6 = puVar7[1];
      puVar7 = (undefined8 *)runtime_gcWriteBarrier2();
      *in_R11 = uVar5;
      in_R11[1] = uVar6;
    }
    puVar7[1] = uVar5;
    uVar5 = runtime_makemap_small();
    puVar7 = (undefined8 *)runtime_mapassign_faststr(0xd);
    *puVar7 = &DAT_01a233a0;
    if (DAT_02e5e450 != 0) {
      auVar13 = runtime_gcWriteBarrier2();
      puVar7 = auVar13._0_8_;
      *in_R11 = uVar5;
      in_R11[1] = auVar13._8_8_;
    }
    puVar7[1] = uVar5;
    github_com_gogf_gf_v2_net_ghttp_Response_WriteJson();
    return;
  }
  lVar4 = runtime_makeslice();
  lVar9 = 0;
  uStack_38 = 0;
  uVar10 = 0;
  lVar12 = 0;
  uVar8 = uVar2;
  while (lStack_60 = lVar4, lVar12 < (long)uVar2) {
    lStack_48 = plStack_70[lVar12];
    lStack_78 = lVar12;
    uVar5 = runtime_makemap_small();
    uVar6 = runtime_convTstring();
    auVar13 = runtime_mapassign_faststr(4);
    *auVar13._0_8_ = &DAT_0194e220;
    if (DAT_02e5e450 != 0) {
      auVar13 = runtime_gcWriteBarrier2();
      *in_R11 = uVar6;
      in_R11[1] = auVar13._8_8_;
    }
    *(undefined8 *)(auVar13._0_8_ + 8) = uVar6;
    puVar7 = (undefined8 *)runtime_mapassign_faststr(0x1b,uVar6,auVar13._8_8_,&DAT_01c63518);
    *puVar7 = &DAT_0194e460;
    if (DAT_02e5e450 != 0) {
      uVar6 = puVar7[1];
      puVar7 = (undefined8 *)runtime_gcWriteBarrier1();
      *in_R11 = uVar6;
    }
    puVar7[1] = &DAT_01f385c0;
    puVar7 = (undefined8 *)runtime_mapassign_faststr(0x1b);
    *puVar7 = &DAT_0194e460;
    if (DAT_02e5e450 != 0) {
      uVar6 = puVar7[1];
      puVar7 = (undefined8 *)runtime_gcWriteBarrier1();
      *in_R11 = uVar6;
    }
    puVar7[1] = &DAT_01f385c0;
    puVar7 = (undefined8 *)runtime_mapassign_faststr(0x15);
    *puVar7 = &DAT_0194e460;
    if (DAT_02e5e450 != 0) {
      uVar6 = puVar7[1];
      puVar7 = (undefined8 *)runtime_gcWriteBarrier1();
      *in_R11 = uVar6;
    }
    puVar7[1] = &DAT_01f386f8;
    uVar6 = runtime_convTstring();
    puVar7 = (undefined8 *)runtime_mapassign_faststr(0xd);
    *puVar7 = &DAT_0194e220;
    if (DAT_02e5e450 != 0) {
      auVar13 = runtime_gcWriteBarrier2();
      puVar7 = auVar13._0_8_;
      *in_R11 = uVar6;
      in_R11[1] = auVar13._8_8_;
    }
    puVar7[1] = uVar6;
    puVar7 = (undefined8 *)runtime_newobject();
    puVar7[1] = 4;
    *puVar7 = &DAT_01c3979a;
    puVar7[3] = 4;
    puVar7[2] = 0x1c3979e;
    puVar7[5] = 4;
    puVar7[4] = &DAT_01c397a2;
    puVar7[7] = 8;
    puVar7[6] = &DAT_01c3fd97;
    uVar6 = runtime_convTslice();
    puVar7 = (undefined8 *)runtime_mapassign_faststr(0xc);
    *puVar7 = &DAT_0192e8e0;
    if (DAT_02e5e450 != 0) {
      auVar13 = runtime_gcWriteBarrier2();
      puVar7 = auVar13._0_8_;
      *in_R11 = uVar6;
      in_R11[1] = auVar13._8_8_;
    }
    puVar7[1] = uVar6;
    uVar10 = uVar10 + 1;
    lVar4 = lStack_60;
    if (uVar8 < uVar10) {
      lVar4 = runtime_growslice(1,&DAT_01a233a0);
    }
    if (DAT_02e5e450 != 0) {
      auVar13 = runtime_gcWriteBarrier2();
      lVar4 = auVar13._0_8_;
      *in_R11 = uVar5;
      in_R11[1] = auVar13._8_8_;
    }
    *(undefined8 *)(lVar4 + -8 + uVar10 * 8) = uVar5;
    if (*(char *)(lStack_48 + 0x38) != '\0') {
      lVar9 = *(long *)(lStack_48 + 0x20);
      uStack_38 = *(undefined8 *)(lStack_48 + 0x18);
    }
    lVar12 = lStack_78 + 1;
  }
  if ((lVar9 == 0) && (uVar2 != 0)) {
    uStack_38 = *(undefined8 *)(*plStack_70 + 0x18);
  }
  uStack_68 = runtime_makemap_small();
  uStack_58 = runtime_makemap_small();
  lVar9 = 0;
  while (lVar9 < (long)uVar2) {
    lStack_50 = plStack_70[lVar9];
    uStack_40 = *(undefined8 *)(lStack_50 + 0x28);
    uVar5 = *(undefined8 *)(lStack_50 + 0x20);
    uVar6 = *(undefined8 *)(lStack_50 + 0x18);
    lStack_78 = lVar9;
    puVar7 = (undefined8 *)runtime_mapassign_faststr();
    puVar7[1] = uVar5;
    if (DAT_02e5e450 != 0) {
      uVar5 = *puVar7;
      puVar7 = (undefined8 *)runtime_gcWriteBarrier2();
      *in_R11 = uVar6;
      in_R11[1] = uVar5;
    }
    *puVar7 = uVar6;
    uVar5 = runtime_makemap_small();
    uVar6 = runtime_convTstring();
    puVar7 = (undefined8 *)runtime_mapassign_faststr(0xb);
    *puVar7 = &DAT_0194e220;
    if (DAT_02e5e450 != 0) {
      auVar13 = runtime_gcWriteBarrier2();
      puVar7 = auVar13._0_8_;
      *in_R11 = uVar6;
      in_R11[1] = auVar13._8_8_;
    }
    puVar7[1] = uVar6;
    bVar1 = *(byte *)(lStack_50 + 0x39);
    puVar7 = (undefined8 *)runtime_mapassign_faststr(8,uVar6,bVar1,&DAT_01c3fd9f);
    *puVar7 = &DAT_0194e620;
    puVar11 = &DAT_01f8a680 + (ulong)(bVar1 ^ 1) * 8;
    if (DAT_02e5e450 != 0) {
      uVar6 = puVar7[1];
      puVar7 = (undefined8 *)runtime_gcWriteBarrier1();
      *in_R11 = uVar6;
    }
    puVar7[1] = puVar11;
    uVar6 = runtime_convTstring();
    puVar7 = (undefined8 *)runtime_mapassign_faststr(0xb);
    *puVar7 = &DAT_0194e220;
    if (DAT_02e5e450 != 0) {
      auVar13 = runtime_gcWriteBarrier2();
      puVar7 = auVar13._0_8_;
      *in_R11 = uVar6;
      in_R11[1] = auVar13._8_8_;
    }
    puVar7[1] = uVar6;
    uVar6 = runtime_convTstring();
    puVar7 = (undefined8 *)runtime_mapassign_faststr(9);
    *puVar7 = &DAT_0194e220;
    if (DAT_02e5e450 != 0) {
      auVar13 = runtime_gcWriteBarrier2();
      puVar7 = auVar13._0_8_;
      *in_R11 = uVar6;
      in_R11[1] = auVar13._8_8_;
    }
    puVar7[1] = uVar6;
    puVar7 = (undefined8 *)
             runtime_mapassign_faststr(*(undefined8 *)(lStack_50 + 0x20),uVar6,lStack_50,
                          *(undefined8 *)(lStack_50 + 0x18));
    if (DAT_02e5e450 != 0) {
      auVar13 = runtime_gcWriteBarrier2();
      puVar7 = auVar13._0_8_;
      *in_R11 = uVar5;
      in_R11[1] = auVar13._8_8_;
    }
    *puVar7 = uVar5;
    lVar9 = lStack_78 + 1;
  }
  runtime_makemap_small();
  uVar5 = runtime_convTstring();
  puVar7 = (undefined8 *)runtime_mapassign_faststr(0xd);
  *puVar7 = &DAT_0194e220;
  if (DAT_02e5e450 != 0) {
    auVar13 = runtime_gcWriteBarrier2();
    puVar7 = auVar13._0_8_;
    *in_R11 = uVar5;
    in_R11[1] = auVar13._8_8_;
  }
  puVar7[1] = uVar5;
  uVar5 = runtime_convTslice();
  puVar7 = (undefined8 *)runtime_mapassign_faststr(6);
  *puVar7 = &DAT_0192a2e0;
  if (DAT_02e5e450 != 0) {
    auVar13 = runtime_gcWriteBarrier2();
    puVar7 = auVar13._0_8_;
    *in_R11 = uVar5;
    in_R11[1] = auVar13._8_8_;
  }
  puVar7[1] = uVar5;
  uVar5 = runtime_makemap();
  puVar7 = (undefined8 *)runtime_mapassign_faststr(0x15);
  *puVar7 = &DAT_0194e620;
  if (DAT_02e5e450 != 0) {
    uVar6 = puVar7[1];
    puVar7 = (undefined8 *)runtime_gcWriteBarrier1();
    *in_R11 = uVar6;
  }
  puVar7[1] = &DAT_01f8a688;
  puVar7 = (undefined8 *)runtime_mapassign_faststr(0x13);
  *puVar7 = &DAT_0194e620;
  if (DAT_02e5e450 != 0) {
    uVar6 = puVar7[1];
    puVar7 = (undefined8 *)runtime_gcWriteBarrier1();
    *in_R11 = uVar6;
  }
  puVar7[1] = &DAT_01f8a688;
  puVar7 = (undefined8 *)runtime_mapassign_faststr(0xe);
  *puVar7 = &DAT_01a23240;
  if (DAT_02e5e450 != 0) {
    uVar6 = puVar7[1];
    puVar7 = (undefined8 *)runtime_gcWriteBarrier2();
    *in_R11 = uStack_68;
    in_R11[1] = uVar6;
  }
  puVar7[1] = uStack_68;
  puVar7 = (undefined8 *)runtime_mapassign_faststr(0xd);
  auVar13._8_8_ = &DAT_01a23240;
  auVar13._0_8_ = puVar7;
  *puVar7 = &DAT_01a23240;
  if (DAT_02e5e450 != 0) {
    auVar13 = runtime_gcWriteBarrier2();
    *in_R11 = uStack_68;
    in_R11[1] = auVar13._8_8_;
  }
  *(undefined8 *)(auVar13._0_8_ + 8) = uStack_68;
  puVar7 = (undefined8 *)runtime_mapassign_faststr(0x13,uStack_68,auVar13._8_8_,&DAT_01c54d4b);
  *puVar7 = &DAT_01a23ba0;
  if (DAT_02e5e450 != 0) {
    uVar6 = puVar7[1];
    puVar7 = (undefined8 *)runtime_gcWriteBarrier2();
    *in_R11 = uStack_58;
    in_R11[1] = uVar6;
  }
  puVar7[1] = uStack_58;
  puVar7 = (undefined8 *)runtime_mapassign_faststr(0x11);
  *puVar7 = &DAT_01a23ba0;
  if (DAT_02e5e450 != 0) {
    uVar6 = puVar7[1];
    puVar7 = (undefined8 *)runtime_gcWriteBarrier2();
    *in_R11 = uStack_58;
    in_R11[1] = uVar6;
  }
  puVar7[1] = uStack_58;
  uVar6 = runtime_convTstring();
  puVar7 = (undefined8 *)runtime_mapassign_faststr(0x10);
  *puVar7 = &DAT_0194e220;
  if (DAT_02e5e450 != 0) {
    auVar13 = runtime_gcWriteBarrier2();
    puVar7 = auVar13._0_8_;
    *in_R11 = uVar6;
    in_R11[1] = auVar13._8_8_;
  }
  puVar7[1] = uVar6;
  uVar6 = runtime_convTstring();
  auVar13 = runtime_mapassign_faststr(0xe);
  *auVar13._0_8_ = &DAT_0194e220;
  if (DAT_02e5e450 != 0) {
    auVar13 = runtime_gcWriteBarrier2();
    *in_R11 = uVar6;
    in_R11[1] = auVar13._8_8_;
  }
  *(undefined8 *)(auVar13._0_8_ + 8) = uVar6;
  puVar7 = (undefined8 *)runtime_mapassign_faststr(0x15,uVar6,auVar13._8_8_,&DAT_01c58a99);
  *puVar7 = &DAT_0194e620;
  if (DAT_02e5e450 != 0) {
    uVar6 = puVar7[1];
    puVar7 = (undefined8 *)runtime_gcWriteBarrier1();
    *in_R11 = uVar6;
  }
  puVar7[1] = &DAT_01f8a688;
  puVar7 = (undefined8 *)runtime_mapassign_faststr(0x13);
  *puVar7 = &DAT_0194e620;
  if (DAT_02e5e450 != 0) {
    auVar13 = runtime_gcWriteBarrier1();
    puVar7 = auVar13._0_8_;
    *in_R11 = auVar13._8_8_;
  }
  puVar7[1] = &DAT_01f8a688;
  puVar7 = (undefined8 *)runtime_mapassign_faststr(0xd);
  *puVar7 = &DAT_01a233a0;
  if (DAT_02e5e450 != 0) {
    auVar13 = runtime_gcWriteBarrier2();
    puVar7 = auVar13._0_8_;
    *in_R11 = uVar5;
    in_R11[1] = auVar13._8_8_;
  }
  puVar7[1] = uVar5;
  github_com_gogf_gf_v2_net_ghttp_Response_WriteJson();
  return;
}



