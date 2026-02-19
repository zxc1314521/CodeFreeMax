// CodeFreeMax - KIRO Channel Decompiled Functions
// 2 functions

// === kiro.buildKiroRequest @ 0x17a4e20 ===

void kiro_buildKiroRequest(void)

{
  undefined1 auVar1 [16];
  undefined1 auVar2 [16];
  undefined1 auVar3 [16];
  undefined1 auVar4 [16];
  undefined1 auVar5 [16];
  undefined1 auVar6 [16];
  undefined1 auVar7 [16];
  undefined1 auVar8 [16];
  ulong uVar9;
  char cVar10;
  undefined8 *puVar11;
  undefined8 uVar12;
  undefined1 (*pauVar13) [16];
  undefined1 (*pauVar14) [16];
  undefined1 (*pauVar15) [16];
  long lVar16;
  char *pcVar17;
  undefined1 *puVar18;
  undefined8 *puVar19;
  long *plVar20;
  long in_RCX;
  long lVar21;
  undefined **ppuVar22;
  undefined *puVar23;
  undefined8 extraout_RDX;
  undefined8 extraout_RDX_00;
  undefined8 extraout_RDX_01;
  long extraout_RDX_02;
  undefined1 (*extraout_RDX_03) [16];
  long unaff_RBX;
  ulong uVar24;
  undefined1 (*pauVar25) [16];
  ulong uVar26;
  undefined1 (*pauVar27) [16];
  undefined8 uVar28;
  undefined1 (*pauVar29) [16];
  long lVar30;
  undefined1 (*pauVar31) [16];
  undefined8 uVar32;
  long lVar33;
  undefined8 *puVar34;
  undefined1 (*pauVar35) [16];
  long *plVar36;
  undefined1 (*pauVar37) [16];
  undefined1 (*pauVar38) [16];
  undefined1 (*unaff_R13) [16];
  long unaff_R14;
  bool bVar39;
  undefined1 (*in_XMM15_Qa) [16];
  undefined1 (*in_XMM15_Qb) [16];
  undefined1 auVar40 [16];
  undefined1 auVar41 [16];
  undefined1 auVar42 [16];
  undefined1 auVar43 [16];
  undefined1 auVar44 [16];
  undefined1 auVar45 [16];
  undefined1 auVar46 [16];
  undefined1 auVar47 [16];
  undefined1 auVar48 [16];
  undefined1 auVar49 [16];
  undefined1 auVar50 [16];
  undefined1 auVar51 [16];
  undefined1 auVar52 [16];
  undefined1 auVar53 [16];
  undefined1 auVar54 [16];
  undefined1 auVar55 [16];
  undefined1 auVar56 [16];
  undefined1 auVar57 [16];
  undefined1 auVar58 [16];
  long lStack0000000000000010;
  long lStack0000000000000018;
  ulong uStack_ae8;
  ulong uStack_ae0;
  ulong uStack_ad8;
  ulong uStack_ad0;
  undefined1 (*pauStack_ac8) [16];
  undefined1 (*pauStack_ac0) [16];
  undefined1 (*pauStack_ab8) [16];
  undefined8 uStack_ab0;
  undefined1 (*pauStack_aa8) [16];
  undefined1 (*pauStack_aa0) [16];
  undefined8 uStack_a98;
  undefined8 uStack_a90;
  undefined1 (*pauStack_a88) [16];
  undefined1 (*pauStack_a80) [16];
  undefined8 uStack_a78;
  undefined8 uStack_a70;
  undefined1 (*pauStack_a68) [16];
  undefined1 (*pauStack_a60) [16];
  undefined1 (*pauStack_a58) [16];
  undefined1 (*pauStack_a50) [16];
  undefined1 (*pauStack_a48) [16];
  long lStack_a40;
  long lStack_a38;
  undefined1 (*pauStack_a30) [16];
  undefined1 (*pauStack_a28) [16];
  long lStack_a20;
  undefined1 (*pauStack_a18) [16];
  long lStack_a10;
  long lStack_a08;
  undefined8 uStack_a00;
  undefined8 uStack_9f8;
  undefined1 (*pauStack_9f0) [16];
  undefined1 (*pauStack_9e8) [16];
  undefined1 (*pauStack_9e0) [16];
  undefined1 (*pauStack_9d8) [16];
  undefined1 (*pauStack_9d0) [16];
  long lStack_9c8;
  undefined1 (*pauStack_9c0) [16];
  undefined1 (*pauStack_9b8) [16];
  long lStack_9b0;
  long lStack_9a8;
  undefined1 (*pauStack_9a0) [16];
  undefined1 (*pauStack_998) [16];
  undefined1 (*pauStack_990) [16];
  undefined1 (*pauStack_988) [16];
  long lStack_980;
  undefined1 (*pauStack_978) [16];
  undefined1 (*pauStack_970) [16];
  undefined1 (*pauStack_968) [16];
  undefined1 (*pauStack_960) [16];
  undefined1 *puStack_958;
  undefined8 uStack_950;
  long lStack_948;
  undefined1 (*pauStack_940) [16];
  undefined1 (*pauStack_938) [16];
  ulong uStack_930;
  ulong uStack_928;
  undefined1 (*pauStack_920) [16];
  undefined1 (*pauStack_918) [16];
  undefined1 (*pauStack_910) [16];
  undefined1 (*pauStack_908) [16];
  undefined1 (*pauStack_900) [16];
  undefined1 (*pauStack_8f8) [16];
  undefined1 (*pauStack_8f0) [16];
  undefined1 (*pauStack_8e8) [16];
  ulong uStack_8e0;
  ulong uStack_8d8;
  undefined1 (*pauStack_8d0) [16];
  undefined1 (*pauStack_8c8) [16];
  undefined1 (*pauStack_8c0) [16];
  undefined1 (*pauStack_8b8) [16];
  undefined1 (*pauStack_8b0) [16];
  undefined1 (*pauStack_8a8) [16];
  undefined1 (*pauStack_8a0) [16];
  undefined1 (*pauStack_898) [16];
  undefined1 (*pauStack_890) [16];
  undefined1 (*pauStack_888) [16];
  undefined1 (*pauStack_880) [16];
  undefined1 (*pauStack_878) [16];
  undefined1 (*pauStack_870) [16];
  undefined1 (*pauStack_868) [16];
  undefined1 (*pauStack_860) [16];
  undefined1 (*pauStack_858) [16];
  undefined1 (*pauStack_850) [16];
  undefined *puStack_848;
  long lStack_840;
  long lStack_838;
  undefined **ppuStack_830;
  undefined8 *puStack_828;
  undefined1 (*pauStack_820) [16];
  long *plStack_818;
  undefined8 *puStack_810;
  undefined1 (*pauStack_808) [16];
  undefined8 *puStack_800;
  undefined1 (*pauStack_7f8) [16];
  undefined1 (*pauStack_7f0) [16];
  undefined8 uStack_7e8;
  undefined1 (*pauStack_7e0) [16];
  undefined1 (*pauStack_7d8) [16];
  undefined1 (*pauStack_7d0) [16];
  undefined1 (*pauStack_7c8) [16];
  undefined1 (*pauStack_7c0) [16];
  undefined1 (*pauStack_7b8) [16];
  undefined1 (*pauStack_7b0) [16];
  undefined8 uStack_7a8;
  undefined1 (*pauStack_7a0) [16];
  undefined1 (*pauStack_798) [16];
  undefined1 (*pauStack_790) [16];
  undefined1 (*pauStack_788) [16];
  undefined1 (*pauStack_780) [16];
  undefined1 (*pauStack_778) [16];
  undefined1 (*pauStack_770) [16];
  undefined1 (*pauStack_768) [16];
  undefined1 (*pauStack_760) [16];
  undefined8 uStack_758;
  undefined1 (*pauStack_750) [16];
  undefined1 (*pauStack_748) [16];
  undefined1 (*pauStack_740) [16];
  undefined1 (*pauStack_738) [16];
  undefined1 (*pauStack_730) [16];
  undefined1 (*pauStack_728) [16];
  undefined1 (*pauStack_720) [16];
  undefined1 (*pauStack_718) [16];
  undefined1 (*pauStack_710) [16];
  undefined1 (*pauStack_708) [16];
  undefined1 (*pauStack_700) [16];
  undefined1 (*pauStack_6f8) [16];
  undefined1 (*pauStack_6f0) [16];
  undefined1 (*pauStack_6e8) [16];
  undefined1 (*pauStack_6e0) [16];
  undefined1 (*pauStack_6d8) [16];
  undefined1 (*pauStack_6d0) [16];
  undefined1 (*pauStack_6c8) [16];
  undefined1 (*pauStack_6c0) [16];
  undefined8 uStack_6b8;
  undefined8 uStack_6b0;
  undefined8 uStack_6a8;
  undefined1 (*pauStack_6a0) [16];
  undefined8 uStack_698;
  undefined8 uStack_690;
  undefined8 uStack_688;
  undefined8 uStack_680;
  undefined8 uStack_678;
  undefined8 uStack_670;
  undefined8 *puStack_668;
  undefined1 (*pauStack_660) [16];
  undefined1 (*pauStack_658) [16];
  undefined8 uStack_650;
  undefined8 uStack_648;
  undefined8 *puStack_640;
  long lStack_638;
  long lStack_630;
  undefined1 (*pauStack_628) [16];
  undefined1 (*pauStack_620) [16];
  undefined1 (*pauStack_618) [16];
  undefined1 (*pauStack_610) [16];
  undefined4 uStack_608;
  undefined4 uStack_604;
  undefined4 uStack_600;
  undefined4 uStack_5fc;
  undefined8 *puStack_5f8;
  undefined1 (*pauStack_5f0) [16];
  undefined1 (*pauStack_5e8) [16];
  undefined8 uStack_5e0;
  long lStack_5d8;
  undefined1 (*pauStack_5d0) [16];
  undefined1 (*pauStack_5c8) [16];
  undefined1 (*pauStack_5c0) [16];
  undefined *puStack_5b8;
  undefined8 uStack_5b0;
  undefined8 uStack_5a8;
  undefined8 uStack_5a0;
  undefined8 uStack_598;
  undefined1 (*pauStack_590) [16];
  undefined1 (*pauStack_588) [16];
  undefined1 (*pauStack_580) [16];
  undefined1 (*pauStack_578) [16];
  undefined1 (*pauStack_570) [16];
  undefined1 (*pauStack_568) [16];
  undefined8 *puStack_560;
  undefined1 (*pauStack_558) [16];
  undefined1 (*pauStack_550) [16];
  undefined1 (*pauStack_548) [16];
  undefined8 *puStack_540;
  undefined8 *puStack_538;
  undefined8 *puStack_530;
  undefined8 *puStack_528;
  undefined8 uStack_520;
  undefined8 *puStack_518;
  undefined8 *puStack_510;
  undefined1 (*pauStack_508) [16];
  long lStack_500;
  long lStack_4f8;
  undefined1 (*pauStack_4f0) [16];
  undefined1 (*pauStack_4e8) [16];
  undefined8 uStack_4e0;
  undefined1 (*pauStack_4d8) [16];
  undefined8 uStack_4d0;
  undefined1 auStack_4c8 [200];
  undefined8 uStack_400;
  undefined8 *puStack_3f8;
  undefined8 uStack_3d8;
  undefined1 auStack_3d0 [200];
  undefined8 uStack_308;
  undefined8 *puStack_300;
  undefined8 uStack_2e0;
  undefined1 auStack_2d8 [200];
  undefined8 uStack_210;
  undefined8 *puStack_208;
  undefined8 uStack_1e8;
  undefined1 auStack_1e0 [200];
  undefined8 uStack_118;
  undefined8 *puStack_110;
  undefined1 (*pauStack_f0) [16];
  undefined1 (*pauStack_e8) [16];
  undefined1 (*pauStack_e0) [16];
  undefined8 uStack_d8;
  undefined8 uStack_d0;
  undefined8 uStack_c8;
  undefined8 uStack_c0;
  undefined *puStack_b8;
  undefined8 uStack_b0;
  undefined8 *puStack_a8;
  undefined1 (*pauStack_48) [16];
  undefined1 (*pauStack_40) [16];
  undefined1 (*pauStack_38) [16];
  undefined1 (*pauStack_30) [16];
  undefined1 (*pauStack_28) [16];
  undefined1 (*pauStack_20) [16];
  undefined *puStack_18;
  undefined8 uStack_10;
  
  lStack0000000000000018 = in_RCX;
  lStack0000000000000010 = unaff_RBX;
  while (&uStack_ae8 <= *(ulong **)(unaff_R14 + 0x10)) {
    runtime_morestack_noctxt();
  }
  puVar11 = (undefined8 *)runtime_mapaccess1_faststr();
  lStack_9c8 = puVar11[1];
  uStack_648 = *puVar11;
  if (lStack_9c8 == 0) {
    puVar11 = (undefined8 *)runtime_mapaccess1_faststr();
    uStack_648 = *puVar11;
    lStack_9c8 = puVar11[1];
  }
  if (*(long *)(lStack0000000000000010 + 0x40) == 0) {
    pauVar37 = (undefined1 (*) [16])0x0;
    pauStack_6a0 = (undefined1 (*) [16])0x0;
  }
  else {
    pauVar37 = *(undefined1 (**) [16])(lStack0000000000000010 + 0x48);
    pauStack_6a0 = (undefined1 (*) [16])kiro2api_internal_logic_kiro_getContentText();
  }
  pauVar13 = *(undefined1 (**) [16])(lStack0000000000000010 + 0x10);
  puVar11 = (undefined8 *)0x0;
  pauVar14 = (undefined1 (*) [16])0x0;
  pauVar31 = (undefined1 (*) [16])0x0;
  pauVar27 = *(undefined1 (**) [16])(lStack0000000000000010 + 0x18);
  lVar21 = lStack_9c8;
  uVar12 = uStack_648;
  while (pauStack_a18 = pauVar37, pauStack_9f0 = pauVar31, puStack_668 = puVar11, 0 < (long)pauVar27
        ) {
    unaff_R13 = *(undefined1 (**) [16])*pauVar13;
    pauStack_e8 = *(undefined1 (**) [16])(*pauVar13 + 8);
    pauStack_e0 = *(undefined1 (**) [16])pauVar13[1];
    pauVar37 = *(undefined1 (**) [16])(pauVar13[1] + 8);
    uStack_d0 = *(undefined1 (**) [16])pauVar13[2];
    uStack_c8 = *(undefined1 (**) [16])(pauVar13[2] + 8);
    pauStack_9e8 = pauVar14;
    pauStack_850 = pauVar27;
    pauStack_4d8 = pauVar13;
    pauStack_f0 = unaff_R13;
    uStack_d8 = (undefined **)pauVar37;
    if (((pauStack_e8 == (undefined1 (*) [16])0x6) && (*(int *)*unaff_R13 == 0x74737973)) &&
       (*(short *)((long)*unaff_R13 + 4) == 0x6d65)) {
      uVar12 = kiro2api_internal_logic_kiro_getContentText();
      pauVar31 = pauStack_6a0;
      if (pauStack_a18 == (undefined1 (*) [16])0x0) {
        pauVar31 = (undefined1 (*) [16])0x0;
        pauVar13 = pauStack_6a0;
      }
      else {
        pauStack_9d0 = pauVar37;
        uStack_650 = uVar12;
        pauVar13 = (undefined1 (*) [16])runtime_concatstring2(&DAT_01f34d88,1);
        uVar12 = uStack_650;
        pauVar37 = pauStack_9d0;
      }
      pauStack_6a0 = (undefined1 (*) [16])runtime_concatstring2(uVar12,pauVar37,pauVar13,pauVar31);
      puVar11 = puStack_668;
      lVar21 = lStack_9c8;
      pauStack_a18 = pauVar13;
      uVar12 = uStack_648;
      pauVar14 = pauStack_9e8;
      pauVar31 = pauStack_9f0;
    }
    else if ((pauStack_e8 == (undefined1 (*) [16])0x4) && (*(int *)*unaff_R13 == 0x6c6f6f74)) {
      uStack_7a8 = runtime_makemap_small();
      puVar11 = (undefined8 *)runtime_mapassign_faststr(4);
      *puVar11 = &DAT_0194e220;
      if (DAT_02e5e450 != 0) {
        auVar40 = runtime_gcWriteBarrier1();
        puVar11 = auVar40._0_8_;
        *(long *)*pauVar31 = auVar40._8_8_;
      }
      puVar11[1] = &PTR_DAT_01f3a180;
      uStack_4e0 = runtime_convTstring();
      puVar11 = (undefined8 *)runtime_mapassign_faststr(0xb);
      *puVar11 = &DAT_0194e220;
      if (DAT_02e5e450 != 0) {
        auVar40 = runtime_gcWriteBarrier2();
        puVar11 = auVar40._0_8_;
        *(undefined8 *)*pauVar31 = uStack_4e0;
        *(long *)((long)*pauVar31 + 8) = auVar40._8_8_;
      }
      puVar11[1] = uStack_4e0;
      pauStack_858 = pauStack_e0;
      pauStack_4e8 = (undefined1 (*) [16])uStack_d8;
      puVar11 = (undefined8 *)runtime_mapassign_faststr(7,uStack_4e0,uStack_d8,&DAT_01c3dd44);
      *puVar11 = pauStack_858;
      if (DAT_02e5e450 != 0) {
        uVar12 = puVar11[1];
        puVar11 = (undefined8 *)runtime_gcWriteBarrier2();
        *(undefined1 (**) [16])*pauVar31 = pauStack_4e8;
        *(undefined8 *)((long)*pauVar31 + 8) = uVar12;
      }
      puVar11[1] = pauStack_4e8;
      pauStack_f0 = (undefined1 (*) [16])&DAT_01c3978a;
      pauStack_e8 = (undefined1 (*) [16])0x4;
      uStack_d0 = in_XMM15_Qa;
      uStack_c8 = in_XMM15_Qb;
      puVar11 = (undefined8 *)runtime_newobject();
      *puVar11 = &DAT_01a233a0;
      if (DAT_02e5e450 != 0) {
        puVar11 = (undefined8 *)runtime_gcWriteBarrier1();
        *(undefined8 *)*pauVar31 = uStack_7a8;
      }
      puVar11[1] = uStack_7a8;
      uStack_d8 = (undefined **)runtime_convTslice();
      pauStack_e0 = (undefined1 (*) [16])&DAT_0192e960;
      pauVar31 = (undefined1 (*) [16])((long)*pauStack_9f0 + 1);
      puVar11 = puStack_668;
      pauVar14 = pauStack_9e8;
      if (pauStack_9e8 < pauVar31) {
        puVar11 = (undefined8 *)runtime_growslice(1,&DAT_01ad67a0);
      }
      pauVar13 = (undefined1 (*) [16])((long)pauVar31 * 0x30);
      pauVar37 = (undefined1 (*) [16])((long)pauVar13[-3] + (long)puVar11);
      if (DAT_02e5e450 != 0) {
        pauStack_870 = pauVar14;
        pauStack_868 = pauVar31;
        pauStack_860 = pauVar13;
        lStack_4f8 = (long)puVar11;
        pauStack_4f0 = pauVar37;
        runtime_wbMove();
        puVar11 = (undefined8 *)lStack_4f8;
        pauVar14 = pauStack_870;
        pauVar13 = pauStack_860;
        pauVar31 = pauStack_868;
        pauVar37 = pauStack_4f0;
      }
      *(undefined1 (**) [16])*pauVar37 = pauStack_f0;
      *(undefined1 (**) [16])(*pauVar37 + 8) = pauStack_e8;
      *(undefined1 (**) [16])((long)pauVar13[-2] + (long)puVar11) = pauStack_e0;
      *(undefined ***)((long)pauVar13[-2] + (long)puVar11 + 8) = uStack_d8;
      *(undefined4 *)((long)pauVar13[-1] + (long)puVar11) = (undefined4)uStack_d0;
      *(undefined4 *)((long)pauVar13[-1] + (long)puVar11 + 4) = uStack_d0._4_4_;
      *(undefined4 *)((long)pauVar13[-1] + (long)puVar11 + 8) = (undefined4)uStack_c8;
      *(undefined4 *)((long)pauVar13[-1] + (long)puVar11 + 0xc) = uStack_c8._4_4_;
      lVar21 = lStack_9c8;
      uVar12 = uStack_648;
    }
    else {
      pauVar31 = (undefined1 (*) [16])((long)*pauVar31 + 1);
      if (pauVar14 < pauVar31) {
        puVar11 = (undefined8 *)runtime_growslice(1,&DAT_01ad67a0);
        lVar21 = lStack_9c8;
        uVar12 = uStack_648;
      }
      pauVar37 = (undefined1 (*) [16])((long)pauVar31 * 0x30);
      unaff_R13 = (undefined1 (*) [16])((long)pauVar37[-3] + (long)puVar11);
      if (DAT_02e5e450 != 0) {
        pauStack_880 = pauVar14;
        pauStack_878 = pauVar31;
        pauStack_860 = pauVar37;
        lStack_500 = (long)puVar11;
        pauStack_4f0 = unaff_R13;
        runtime_wbMove();
        puVar11 = (undefined8 *)lStack_500;
        lVar21 = lStack_9c8;
        uVar12 = uStack_648;
        pauVar14 = pauStack_880;
        pauVar31 = pauStack_878;
        pauVar37 = pauStack_860;
        unaff_R13 = pauStack_4f0;
      }
      *(undefined1 (**) [16])*unaff_R13 = pauStack_f0;
      *(undefined1 (**) [16])((long)*unaff_R13 + 8) = pauStack_e8;
      *(undefined1 (**) [16])((long)pauVar37[-2] + (long)puVar11) = pauStack_e0;
      *(undefined ***)((long)pauVar37[-2] + (long)puVar11 + 8) = uStack_d8;
      *(undefined4 *)((long)pauVar37[-1] + (long)puVar11) = (undefined4)uStack_d0;
      *(undefined4 *)((long)pauVar37[-1] + (long)puVar11 + 4) = uStack_d0._4_4_;
      *(undefined4 *)((long)pauVar37[-1] + (long)puVar11 + 8) = (undefined4)uStack_c8;
      *(undefined4 *)((long)pauVar37[-1] + (long)puVar11 + 0xc) = uStack_c8._4_4_;
    }
    pauVar13 = pauStack_4d8 + 3;
    pauVar37 = pauStack_a18;
    pauVar27 = (undefined1 (*) [16])((long)pauStack_850[-1] + 0xf);
  }
  pauVar14 = (undefined1 (*) [16])kiro2api_internal_logic_kiro_generateThinkingPrefix(pauVar14,uVar12,lVar21);
  pauVar13 = pauStack_6a0;
  pauVar27 = pauStack_a18;
  if (((pauVar37 != (undefined1 (*) [16])0x0) &&
      (pauVar13 = pauVar14, pauVar27 = pauVar37, pauStack_a18 != (undefined1 (*) [16])0x0)) &&
     (pauStack_888 = pauVar37, pauStack_508 = pauVar14, cVar10 = kiro2api_internal_logic_kiro_hasThinkingPrefix(),
     pauVar37 = pauStack_508, pauVar13 = pauStack_6a0, pauVar27 = pauStack_a18, cVar10 == '\0')) {
    pauVar13 = (undefined1 (*) [16])runtime_concatstring3();
    pauVar27 = pauVar37;
  }
  puVar11 = (undefined8 *)0x0;
  pauVar14 = (undefined1 (*) [16])0x0;
  pauVar29 = (undefined1 (*) [16])0x0;
  lVar21 = 0;
  pauVar37 = pauStack_9f0;
  puVar19 = puStack_668;
  pauStack_a18 = pauVar27;
  pauStack_6a0 = pauVar13;
  while (lVar21 < (long)pauVar37) {
    lVar30 = lVar21 * 0x30;
    pauVar31 = (undefined1 (*) [16])((long)puVar19 + lVar30 + 0x10);
    pauStack_f0 = *(undefined1 (**) [16])(lVar30 + (long)puVar19);
    pauStack_e8 = (undefined1 (*) [16])((undefined8 *)(lVar30 + (long)puVar19))[1];
    pauStack_e0 = *(undefined1 (**) [16])*pauVar31;
    uStack_d8 = *(undefined ***)((long)puVar19 + lVar30 + 0x18);
    uStack_d0 = *(undefined1 (**) [16])((long)puVar19 + lVar30 + 0x20);
    uStack_c8 = *(undefined1 (**) [16])((long)puVar19 + lVar30 + 0x28);
    lStack_980 = lVar21;
    if (pauVar29 == (undefined1 (*) [16])0x0) {
      if (pauVar14 == (undefined1 (*) [16])0x0) {
        pauVar14 = (undefined1 (*) [16])0x0;
        puVar11 = (undefined8 *)runtime_growslice(1,&DAT_01ad67a0);
        pauVar37 = pauStack_9f0;
        pauVar27 = pauStack_a18;
        puVar19 = puStack_668;
      }
      if (DAT_02e5e450 != 0) {
        pauStack_9b8 = pauVar14;
        puStack_640 = puVar11;
        runtime_wbMove();
        pauVar37 = pauStack_9f0;
        pauVar27 = pauStack_a18;
        puVar11 = puStack_640;
        pauVar14 = pauStack_9b8;
        puVar19 = puStack_668;
      }
      *puVar11 = pauStack_f0;
      puVar11[1] = pauStack_e8;
      puVar11[2] = pauStack_e0;
      puVar11[3] = uStack_d8;
      *(undefined4 *)(puVar11 + 4) = (undefined4)uStack_d0;
      *(undefined4 *)((long)puVar11 + 0x24) = uStack_d0._4_4_;
      *(undefined4 *)(puVar11 + 5) = (undefined4)uStack_c8;
      *(undefined4 *)((long)puVar11 + 0x2c) = uStack_c8._4_4_;
      pauVar29 = (undefined1 (*) [16])0x1;
    }
    else {
      pauVar31 = (undefined1 (*) [16])((long)pauVar29 * 0x30);
      unaff_R13 = *(undefined1 (**) [16])((long)pauVar31[-3] + (long)puVar11);
      if ((*(undefined1 (**) [16])((long)((long)pauVar31[-3] + 8) + (long)puVar11) == pauStack_e8)
         && (pauStack_898 = pauVar29, pauStack_890 = pauVar14, pauStack_850 = pauVar31,
            puStack_510 = puVar11, cVar10 = runtime_memequal(), pauVar37 = pauStack_9f0,
            pauVar27 = pauStack_a18, puVar11 = puStack_510, pauVar14 = pauStack_890,
            puVar19 = puStack_668, pauVar29 = pauStack_898, cVar10 != '\0')) {
        puVar11 = *(undefined8 **)((long)pauStack_850[-2] + (long)puStack_510);
        puVar19 = *(undefined8 **)((long)((long)pauStack_850[-2] + 8) + (long)puStack_510);
        if (puVar11 == (undefined8 *)0x0) {
          lVar21 = 0;
          pauVar37 = (undefined1 (*) [16])0x0;
          puVar11 = &DAT_02e5d6a0;
        }
        else {
          puVar34 = &DAT_0192e960;
          if (puVar11 == &DAT_0192e960) {
            puVar11 = (undefined8 *)*puVar19;
            lVar21 = puVar19[1];
            pauVar37 = (undefined1 (*) [16])puVar19[2];
          }
          else if (puVar11 == (undefined8 *)&DAT_0194e220) {
            if (puVar19[1] == 0) {
              lVar21 = 0;
              pauVar37 = (undefined1 (*) [16])0x0;
              puVar11 = &DAT_02e5d6a0;
            }
            else {
              lStack_a08 = puVar19[1];
              uStack_690 = *puVar19;
              uStack_520 = runtime_makemap_small();
              puVar11 = (undefined8 *)runtime_mapassign_faststr(4);
              *puVar11 = &DAT_0194e220;
              if (DAT_02e5e450 != 0) {
                auVar40 = runtime_gcWriteBarrier1();
                puVar11 = auVar40._0_8_;
                *puVar34 = auVar40._8_8_;
              }
              puVar11[1] = &PTR_DAT_01f398c0;
              pauStack_4d8 = (undefined1 (*) [16])runtime_convTstring();
              puVar11 = (undefined8 *)runtime_mapassign_faststr(4);
              *puVar11 = &DAT_0194e220;
              if (DAT_02e5e450 != 0) {
                auVar40 = runtime_gcWriteBarrier2();
                puVar11 = auVar40._0_8_;
                *puVar34 = pauStack_4d8;
                puVar34[1] = auVar40._8_8_;
              }
              puVar11[1] = pauStack_4d8;
              puVar11 = (undefined8 *)runtime_newobject();
              *puVar11 = &DAT_01a233a0;
              if (DAT_02e5e450 != 0) {
                puVar11 = (undefined8 *)runtime_gcWriteBarrier1();
                *puVar34 = uStack_520;
              }
              puVar11[1] = uStack_520;
              lVar21 = 1;
              pauVar37 = (undefined1 (*) [16])0x1;
            }
          }
          else {
            lVar21 = 0;
            pauVar37 = (undefined1 (*) [16])0x0;
            puVar11 = &DAT_02e5d6a0;
          }
        }
        puVar19 = &DAT_0192e960;
        if (pauStack_e0 == (undefined1 (*) [16])0x0) {
          lVar30 = 0;
          ppuVar22 = &puStack_848;
        }
        else if (pauStack_e0 == (undefined1 (*) [16])&DAT_0192e960) {
          ppuVar22 = *(undefined ***)*(undefined1 (*) [16])uStack_d8;
          lVar30 = *(long *)((long)*(undefined1 (*) [16])uStack_d8 + 8);
        }
        else if (pauStack_e0 == (undefined1 (*) [16])&DAT_0194e220) {
          if (*(long *)((long)*(undefined1 (*) [16])uStack_d8 + 8) == 0) {
            lVar30 = 0;
            ppuVar22 = &puStack_848;
          }
          else {
            lStack_a10 = *(long *)((long)*(undefined1 (*) [16])uStack_d8 + 8);
            puStack_828 = puVar11;
            uStack_698 = *(undefined8 *)*(undefined1 (*) [16])uStack_d8;
            uStack_520 = runtime_makemap_small();
            puVar11 = (undefined8 *)runtime_mapassign_faststr(4);
            *puVar11 = &DAT_0194e220;
            if (DAT_02e5e450 != 0) {
              auVar40 = runtime_gcWriteBarrier1();
              puVar11 = auVar40._0_8_;
              *puVar19 = auVar40._8_8_;
            }
            puVar11[1] = &PTR_DAT_01f398c0;
            pauStack_4d8 = (undefined1 (*) [16])runtime_convTstring();
            puVar11 = (undefined8 *)runtime_mapassign_faststr(4);
            *puVar11 = &DAT_0194e220;
            if (DAT_02e5e450 != 0) {
              auVar40 = runtime_gcWriteBarrier2();
              puVar11 = auVar40._0_8_;
              *puVar19 = pauStack_4d8;
              puVar19[1] = auVar40._8_8_;
            }
            puVar11[1] = pauStack_4d8;
            puStack_b8 = &DAT_01a233a0;
            uStack_b0 = uStack_520;
            lVar30 = 1;
            ppuVar22 = &puStack_b8;
            puVar11 = puStack_828;
          }
        }
        else {
          lVar30 = 0;
          ppuVar22 = &puStack_848;
        }
        pauVar31 = (undefined1 (*) [16])&DAT_0192e960;
        pauVar13 = (undefined1 (*) [16])(lVar30 + lVar21);
        if (pauVar37 < pauVar13) {
          ppuStack_830 = ppuVar22;
          puVar11 = (undefined8 *)
                    runtime_growslice(lVar30,&DAT_019b39a0,puStack_510,pauVar37,pauStack_850);
          ppuVar22 = ppuStack_830;
        }
        unaff_R13 = (undefined1 (*) [16])(lVar21 - (long)pauVar37 >> 0x3f & lVar21 << 4);
        pauStack_868 = pauVar13;
        pauStack_860 = pauVar37;
        puStack_528 = puVar11;
        runtime_typedslicecopy(ppuVar22,lVar30,(undefined1 *)((long)puVar11 + (long)unaff_R13),
                     (long)pauVar13 - lVar21);
        uVar12 = runtime_convTslice();
        auVar40._8_8_ = puStack_510;
        auVar40._0_8_ = uVar12;
        *(undefined8 **)((long)pauStack_850[-2] + (long)puStack_510) = &DAT_0192e960;
        pauVar37 = pauStack_850;
        if (DAT_02e5e450 != 0) {
          uVar12 = *(undefined8 *)((long)((long)pauStack_850[-2] + 8) + (long)puStack_510);
          auVar40 = runtime_gcWriteBarrier2();
          *(long *)*pauVar31 = auVar40._0_8_;
          *(undefined8 *)((long)*pauVar31 + 8) = uVar12;
        }
        *(long *)((long)pauVar37[-2] + auVar40._8_8_ + 8) = auVar40._0_8_;
        pauVar37 = pauStack_9f0;
        pauVar27 = pauStack_a18;
        puVar11 = puStack_510;
        pauVar14 = pauStack_890;
        puVar19 = puStack_668;
        pauVar29 = pauStack_898;
      }
      else {
        pauVar29 = (undefined1 (*) [16])((long)*pauVar29 + 1);
        if (pauVar14 < pauVar29) {
          puVar11 = (undefined8 *)runtime_growslice(1,&DAT_01ad67a0);
          pauVar37 = pauStack_9f0;
          pauVar27 = pauStack_a18;
          puVar19 = puStack_668;
        }
        pauVar13 = (undefined1 (*) [16])((long)pauVar29 * 0x30);
        pauVar31 = (undefined1 (*) [16])(puVar11 + (long)pauVar29 * 6 + -6);
        if (DAT_02e5e450 != 0) {
          pauStack_9c0 = pauVar29;
          pauStack_8a0 = pauVar14;
          pauStack_850 = (undefined1 (*) [16])((long)pauVar29 * 0x30);
          puStack_518 = puVar11;
          pauStack_4f0 = (undefined1 (*) [16])(puVar11 + (long)pauVar29 * 6 + -6);
          runtime_wbMove();
          pauVar37 = pauStack_9f0;
          pauVar27 = pauStack_a18;
          puVar11 = puStack_518;
          pauVar14 = pauStack_8a0;
          puVar19 = puStack_668;
          pauVar29 = pauStack_9c0;
          pauVar13 = pauStack_850;
          pauVar31 = pauStack_4f0;
        }
        puVar18 = (undefined1 *)((long)puVar11 + (long)pauVar13);
        *(undefined1 (**) [16])*pauVar31 = pauStack_f0;
        *(undefined1 (**) [16])((long)*pauVar31 + 8) = pauStack_e8;
        *(undefined1 (**) [16])(puVar18 + -0x20) = pauStack_e0;
        *(undefined ***)(puVar18 + -0x18) = uStack_d8;
        *(undefined4 *)(puVar18 + -0x10) = (undefined4)uStack_d0;
        *(undefined4 *)(puVar18 + -0xc) = uStack_d0._4_4_;
        *(undefined4 *)(puVar18 + -8) = (undefined4)uStack_c8;
        *(undefined4 *)(puVar18 + -4) = uStack_c8._4_4_;
      }
    }
    lVar21 = lStack_980 + 1;
  }
  if (pauVar29 == (undefined1 (*) [16])0x0) {
    pauStack_f0 = (undefined1 (*) [16])&DAT_01c3978a;
    pauStack_e8 = (undefined1 (*) [16])0x4;
    pauStack_e0 = (undefined1 (*) [16])&DAT_0194e220;
    uStack_d8 = &PTR_DAT_01f3a190;
    uStack_d0 = in_XMM15_Qa;
    uStack_c8 = in_XMM15_Qb;
    if (pauVar14 == (undefined1 (*) [16])0x0) {
      puVar11 = (undefined8 *)runtime_growslice(1,&DAT_01ad67a0);
      pauVar27 = pauStack_a18;
    }
    if (DAT_02e5e450 != 0) {
      puStack_530 = puVar11;
      runtime_wbMove();
      pauVar27 = pauStack_a18;
      puVar11 = puStack_530;
    }
    *puVar11 = pauStack_f0;
    puVar11[1] = pauStack_e8;
    puVar11[2] = pauStack_e0;
    puVar11[3] = uStack_d8;
    *(undefined4 *)(puVar11 + 4) = (undefined4)uStack_d0;
    *(undefined4 *)((long)puVar11 + 0x24) = uStack_d0._4_4_;
    *(undefined4 *)(puVar11 + 5) = (undefined4)uStack_c8;
    *(undefined4 *)((long)puVar11 + 0x2c) = uStack_c8._4_4_;
    pauVar29 = (undefined1 (*) [16])0x1;
  }
  pauVar37 = *(undefined1 (**) [16])(lStack0000000000000010 + 0x58);
  pauStack_9f0 = pauVar29;
  puStack_668 = puVar11;
  if (pauVar37 == (undefined1 (*) [16])0x0) {
    pauStack_ac8 = (undefined1 (*) [16])0x0;
    pauStack_ac0 = (undefined1 (*) [16])0x0;
    pauStack_7f8 = (undefined1 (*) [16])0x0;
    goto LAB_017a5f10;
  }
  pauVar13 = *(undefined1 (**) [16])(lStack0000000000000010 + 0x50);
  pauStack_ac0 = (undefined1 (*) [16])0x0;
  pauStack_7f8 = (undefined1 (*) [16])0x0;
  pauStack_ac8 = (undefined1 (*) [16])0x0;
  do {
    pauVar31 = pauStack_ac8;
    if ((long)pauVar37 < 1) {
LAB_017a5f10:
      if (pauVar27 == (undefined1 (*) [16])0x0) {
        pauVar27 = (undefined1 (*) [16])0x0;
        pauVar37 = (undefined1 (*) [16])0x0;
        auVar53._8_8_ = 0;
        auVar53._0_8_ = &DAT_02e5d6a0;
        pauVar29 = pauStack_ac8;
        puVar11 = puStack_668;
        pauVar14 = pauStack_ac0;
        pauVar13 = pauStack_7f8;
        pauVar31 = pauStack_9f0;
LAB_017a61cd:
        pauStack_970 = auVar53._8_8_;
        pauVar35 = auVar53._0_8_;
        pauVar38 = (undefined1 (*) [16])((long)pauVar31[-1] + 0xf);
        pauStack_978 = pauVar27;
        pauStack_5f0 = pauVar35;
        if ((long)pauVar38 <= (long)pauVar37) {
          if (pauVar31 <= pauVar38) goto LAB_017a89fc;
          pauStack_f0 = (undefined1 (*) [16])puVar11[(long)pauVar31 * 6 + -6];
          pauStack_e8 = (undefined1 (*) [16])puVar11[(long)pauVar31 * 6 + -5];
          pauStack_e0 = (undefined1 (*) [16])puVar11[(long)pauVar31 * 6 + -4];
          uStack_d8 = (undefined **)puVar11[(long)pauVar31 * 6 + -3];
          uStack_d0 = (undefined1 (*) [16])puVar11[(long)pauVar31 * 6 + -2];
          uStack_c8 = (undefined1 (*) [16])puVar11[(long)pauVar31 * 6 + -1];
          if (((pauStack_e8 == (undefined1 (*) [16])0x9) &&
              (pauVar31 = (undefined1 (*) [16])0x6e61747369737361,
              *(long *)*pauStack_f0 == 0x6e61747369737361)) &&
             (*(char *)((long)*pauStack_f0 + 8) == 't')) {
            pauVar27 = (undefined1 (*) [16])runtime_newobject();
            pauVar37 = (undefined1 (*) [16])uStack_d8;
            pauStack_7a0 = in_XMM15_Qa;
            pauStack_798 = in_XMM15_Qb;
            pauStack_790 = in_XMM15_Qa;
            pauStack_788 = in_XMM15_Qb;
            pauStack_590 = pauVar27;
            if (pauStack_e0 == (undefined1 (*) [16])&DAT_0192e960) {
              pauVar37 = *(undefined1 (**) [16])*(undefined1 (*) [16])uStack_d8;
              pauVar14 = *(undefined1 (**) [16])((long)*(undefined1 (*) [16])uStack_d8 + 8);
              pauVar15 = (undefined1 (*) [16])0x0;
              pauVar25 = (undefined1 (*) [16])0x0;
              pauVar38 = (undefined1 (*) [16])0x0;
              pauStack_730 = in_XMM15_Qa;
              pauStack_728 = in_XMM15_Qb;
              pauStack_720 = in_XMM15_Qa;
              pauStack_718 = in_XMM15_Qb;
              goto LAB_017a8240;
            }
            uVar12 = kiro2api_internal_logic_kiro_getContentText();
            *(undefined1 (**) [16])((long)*pauStack_590 + 8) = pauVar37;
            pauVar29 = pauStack_590;
            if (DAT_02e5e450 != 0) {
              auVar40 = runtime_gcWriteBarrier2();
              uVar12 = auVar40._0_8_;
              *pauVar35 = auVar40;
            }
            *(undefined8 *)*pauVar29 = uVar12;
            auVar44 = ZEXT816(0);
            pauVar25 = (undefined1 (*) [16])0x0;
            goto LAB_017a7cd4;
          }
          if ((pauVar27 != (undefined1 (*) [16])0x0) &&
             (*(long *)((long)pauVar35[(long)pauVar27[-1] + 0xf] + 8) == 0)) {
            puVar11 = (undefined8 *)runtime_newobject();
            pauVar37 = pauStack_978;
            puVar11[1] = 8;
            *puVar11 = &DAT_01c3ffa7;
            pauVar27 = (undefined1 (*) [16])((long)*pauStack_978 + 1);
            pauVar31 = pauStack_970;
            pauVar13 = pauStack_5f0;
            if (pauStack_970 < pauVar27) {
              puStack_540 = puVar11;
              pauVar13 = (undefined1 (*) [16])runtime_growslice(1,&DAT_01a92fc0);
              puVar11 = puStack_540;
            }
            auVar41._8_8_ = pauVar13;
            auVar41._0_8_ = puVar11;
            lVar21 = (long)pauVar37 * 0x10;
            if (DAT_02e5e450 != 0) {
              uVar12 = *(undefined8 *)pauVar13[(long)pauVar37];
              uVar28 = *(undefined8 *)((long)pauVar13[(long)pauVar37] + 8);
              auVar41 = runtime_gcWriteBarrier3();
              *(undefined8 *)*pauVar35 = uVar12;
              *(long *)((long)*pauVar35 + 8) = auVar41._0_8_;
              *(undefined8 *)pauVar35[1] = uVar28;
            }
            lVar30 = auVar41._8_8_;
            auVar53._8_8_ = pauVar31;
            auVar53._0_8_ = lVar30;
            *(undefined8 *)(lVar30 + lVar21) = 0;
            *(long *)(lVar30 + lVar21 + 8) = auVar41._0_8_;
            pauVar29 = pauStack_ac8;
            pauVar14 = pauStack_ac0;
            pauVar13 = pauStack_7f8;
          }
          pauVar37 = (undefined1 (*) [16])uStack_d8;
          pauStack_970 = auVar53._8_8_;
          pauStack_5f0 = auVar53._0_8_;
          pauStack_978 = pauVar27;
          if (pauStack_e0 != (undefined1 (*) [16])&DAT_0192e960) {
            pauStack_5c0 = (undefined1 (*) [16])kiro2api_internal_logic_kiro_getContentText();
            auVar44._8_8_ = pauStack_7f0;
            auVar44._0_8_ = pauStack_ab8;
            uVar26 = 0;
            uVar24 = 0;
            pauStack_940 = (undefined1 (*) [16])0x0;
            pauVar31 = (undefined1 (*) [16])0x0;
            pauStack_5d0 = (undefined1 (*) [16])0x0;
            pauStack_920 = pauVar37;
            pauVar37 = pauStack_970;
            goto LAB_017a6768;
          }
          pauVar37 = *(undefined1 (**) [16])*(undefined1 (*) [16])uStack_d8;
          pauVar27 = *(undefined1 (**) [16])((long)*(undefined1 (*) [16])uStack_d8 + 8);
          uVar24 = 0;
          pauVar31 = (undefined1 (*) [16])0x0;
          pauVar38 = (undefined1 (*) [16])0x0;
          uVar26 = 0;
          pauStack_5d0 = (undefined1 (*) [16])0x0;
          pauStack_940 = (undefined1 (*) [16])0x0;
          puVar23 = &DAT_0194e220;
          pauStack_750 = in_XMM15_Qa;
          pauStack_748 = in_XMM15_Qb;
          pauStack_740 = in_XMM15_Qa;
          pauStack_738 = in_XMM15_Qb;
          break;
        }
        if (pauVar31 <= pauVar37) goto LAB_017aa979;
        pauStack_f0 = (undefined1 (*) [16])puVar11[(long)pauVar37 * 6];
        pauStack_e8 = (undefined1 (*) [16])(puVar11 + (long)pauVar37 * 6)[1];
        pauStack_e0 = (undefined1 (*) [16])puVar11[(long)pauVar37 * 6 + 2];
        uStack_d8 = (undefined **)puVar11[(long)pauVar37 * 6 + 3];
        uStack_d0 = (undefined1 (*) [16])puVar11[(long)pauVar37 * 6 + 4];
        uStack_c8 = (undefined1 (*) [16])puVar11[(long)pauVar37 * 6 + 5];
        pauStack_988 = pauVar37;
        if ((pauStack_e8 != (undefined1 (*) [16])0x4) || (*(int *)*pauStack_f0 != 0x72657375)) {
          if ((pauStack_e8 == (undefined1 (*) [16])0x9) &&
             ((*(long *)*pauStack_f0 == 0x6e61747369737361 &&
              (*(char *)((long)*pauStack_f0 + 8) == 't')))) {
            pauVar29 = (undefined1 (*) [16])runtime_newobject();
            pauVar37 = (undefined1 (*) [16])uStack_d8;
            pauStack_780 = in_XMM15_Qa;
            pauStack_778 = in_XMM15_Qb;
            pauStack_770 = in_XMM15_Qa;
            pauStack_768 = in_XMM15_Qb;
            if (pauStack_e0 != (undefined1 (*) [16])&DAT_0192e960) {
              unaff_R13 = (undefined1 (*) [16])0x0;
              pauVar38 = (undefined1 (*) [16])0x0;
            }
            else {
              pauVar38 = *(undefined1 (**) [16])*(undefined1 (*) [16])uStack_d8;
              unaff_R13 = *(undefined1 (**) [16])((long)*(undefined1 (*) [16])uStack_d8 + 8);
            }
            pauStack_588 = pauVar29;
            if (pauStack_e0 != (undefined1 (*) [16])&DAT_0192e960) {
              uVar12 = kiro2api_internal_logic_kiro_getContentText();
              *(undefined1 (**) [16])((long)*pauStack_588 + 8) = pauVar37;
              pauVar31 = pauStack_588;
              if (DAT_02e5e450 != 0) {
                auVar40 = runtime_gcWriteBarrier2();
                uVar12 = auVar40._0_8_;
                *pauVar35 = auVar40;
              }
              *(undefined8 *)*pauVar31 = uVar12;
              auVar50 = ZEXT816(0);
              pauVar27 = (undefined1 (*) [16])0x0;
              goto LAB_017a8a07;
            }
            pauStack_710 = in_XMM15_Qa;
            pauStack_708 = in_XMM15_Qb;
            pauStack_700 = in_XMM15_Qa;
            pauStack_6f8 = in_XMM15_Qb;
            pauVar37 = (undefined1 (*) [16])0x0;
            pauVar27 = (undefined1 (*) [16])0x0;
            pauVar31 = (undefined1 (*) [16])0x0;
            pauVar15 = unaff_R13;
            do {
              unaff_R13 = pauStack_708;
              if ((long)pauVar15 < 1) {
                if ((undefined1 (*) [16])-(long)pauStack_708 < pauStack_700) {
                  pauVar15 = pauVar37;
                  if (pauStack_708 != (undefined1 (*) [16])0x0) {
                    runtime_panicunsafestringlen();
                    pauVar15 = pauVar37;
                  }
                  runtime_panicunsafestringnilptr();
LAB_017a943d:
                  runtime_gopanic();
LAB_017a944c:
                  runtime_gopanic();
LAB_017a945b:
                  puVar11 = &DAT_01f393c0;
                  auVar55 = runtime_gopanic();
                  goto LAB_017a946a;
                }
                *(undefined1 (**) [16])((long)*pauVar29 + 8) = pauStack_700;
                if (DAT_02e5e450 != 0) {
                  uVar12 = *(undefined8 *)*pauVar29;
                  pauVar29 = (undefined1 (*) [16])runtime_gcWriteBarrier2();
                  *(undefined1 (**) [16])*pauVar35 = unaff_R13;
                  *(undefined8 *)((long)*pauVar35 + 8) = uVar12;
                }
                auVar50._8_8_ = pauVar27;
                auVar50._0_8_ = pauVar31;
                *(undefined1 (**) [16])*pauVar29 = unaff_R13;
                pauVar31 = pauStack_588;
                pauVar27 = pauVar37;
LAB_017a8a07:
                uVar12 = auVar50._0_8_;
                if (pauStack_770 == (undefined1 (*) [16])0x0) goto LAB_017a8b2b;
                uStack_7e8 = auVar50._8_8_;
                pauVar38 = *(undefined1 (**) [16])((long)*pauVar31 + 8);
                pauVar25 = pauStack_770;
                pauVar14 = pauStack_778;
                uStack_ab0 = uVar12;
                pauStack_aa0 = pauVar27;
                if (pauVar38 == (undefined1 (*) [16])0x0) {
                  if (pauStack_770 <= (undefined1 (*) [16])-(long)pauStack_778) {
                    uVar12 = runtime_concatstring3();
                    auVar52._8_8_ = pauStack_588;
                    auVar52._0_8_ = uVar12;
                    *(undefined **)((long)*pauStack_588 + 8) = &DAT_01c4414d;
                    if (DAT_02e5e450 != 0) {
                      uVar12 = *(undefined8 *)*pauStack_588;
                      auVar52 = runtime_gcWriteBarrier2();
                      *(long *)*pauVar35 = auVar52._0_8_;
                      *(undefined8 *)((long)*pauVar35 + 8) = uVar12;
                    }
                    pauVar31 = auVar52._8_8_;
                    auVar50._8_8_ = uStack_7e8;
                    auVar50._0_8_ = uStack_ab0;
                    *(long *)*pauVar31 = auVar52._0_8_;
                    pauVar27 = pauStack_aa0;
                    goto LAB_017a8b2b;
                  }
                  if (pauStack_778 != (undefined1 (*) [16])0x0) {
                    runtime_panicunsafestringlen();
                  }
                  runtime_panicunsafestringnilptr();
                }
                else {
                  unaff_R13 = (undefined1 (*) [16])-(long)pauStack_778;
                  if (pauStack_770 <= unaff_R13) goto code_r0x017a8a54;
                }
                if (pauVar14 != (undefined1 (*) [16])0x0) {
                  runtime_panicunsafestringlen();
                }
                pauVar29 = (undefined1 (*) [16])runtime_panicunsafestringnilptr();
                pauVar37 = pauVar31;
              }
              else if (*(undefined **)*pauVar38 == &DAT_01a233a0) {
                uStack_5a0 = *(undefined8 *)(*pauVar38 + 8);
                pauVar14 = (undefined1 (*) [16])0x4;
                pauStack_8d0 = pauVar31;
                pauStack_8c8 = pauVar37;
                pauStack_850 = pauVar15;
                pauStack_558 = pauVar27;
                pauStack_4d8 = pauVar38;
                puVar11 = (undefined8 *)runtime_mapaccess1_faststr();
                if ((undefined *)*puVar11 == &DAT_0194e220) {
                  plVar20 = *(long **)puVar11[1];
                  lVar21 = ((undefined8 *)puVar11[1])[1];
                }
                else {
                  lVar21 = 0;
                  plVar20 = (long *)0x0;
                }
                pauVar25 = pauStack_8d0;
                unaff_R13 = pauStack_850;
                pauVar29 = pauStack_588;
                pauVar37 = pauStack_8c8;
                pauVar27 = pauStack_558;
                pauVar38 = pauStack_4d8;
                if (lVar21 == 4) {
                  if ((int)*plVar20 == 0x74786574) {
                    pauVar15 = (undefined1 (*) [16])&DAT_01c397b2;
                    pauVar14 = (undefined1 (*) [16])0x4;
                    puVar11 = (undefined8 *)runtime_mapaccess1_faststr();
                    pauVar29 = pauStack_588;
                    pauVar37 = pauStack_8c8;
                    pauVar27 = pauStack_558;
                    pauVar25 = pauStack_8d0;
                    pauVar38 = pauStack_4d8;
                    unaff_R13 = pauStack_850;
                    if ((undefined *)*puVar11 == &DAT_0194e220) {
                      pauVar37 = (undefined1 (*) [16])((undefined8 *)puVar11[1])[1];
                      if (pauStack_710 == (undefined1 (*) [16])0x0) {
                        pauStack_710 = (undefined1 (*) [16])&pauStack_710;
                      }
                      else {
                        pauVar13 = pauStack_710;
                        if (pauStack_710 != (undefined1 (*) [16])&pauStack_710) goto LAB_017a945b;
                      }
                      pauVar31 = (undefined1 (*) [16])((long)*pauStack_700 + (long)*pauVar37);
                      pauVar27 = pauStack_708;
                      pauVar29 = pauStack_6f8;
                      pauVar13 = pauStack_700;
                      if (pauStack_6f8 < pauVar31) {
                        pauStack_860 = pauStack_700;
                        pauStack_a28 = pauVar37;
                        uStack_6b0 = *(undefined8 *)puVar11[1];
                        pauVar27 = (undefined1 (*) [16])runtime_growslice(pauVar37,&DAT_0194e2a0);
                        pauVar14 = pauVar37;
                        pauVar13 = pauStack_860;
                      }
                      pauStack_868 = pauVar31;
                      pauStack_860 = pauVar29;
                      pauStack_4e8 = pauVar27;
                      runtime_memmove();
                      pauStack_700 = pauStack_868;
                      pauStack_6f8 = pauStack_860;
                      pauStack_708 = pauStack_4e8;
                      pauVar29 = pauStack_588;
                      pauVar37 = pauStack_8c8;
                      pauVar27 = pauStack_558;
                      pauVar25 = pauStack_8d0;
                      pauVar38 = pauStack_4d8;
                      unaff_R13 = pauStack_850;
                    }
                  }
                }
                else if (lVar21 == 8) {
                  if (*plVar20 == 0x676e696b6e696874) {
                    pauVar15 = (undefined1 (*) [16])&DAT_01c3fd97;
                    pauVar14 = (undefined1 (*) [16])0x8;
                    puVar11 = (undefined8 *)runtime_mapaccess1_faststr();
                    if ((undefined *)*puVar11 == &DAT_0194e220) {
                      pauVar13 = (undefined1 (*) [16])((undefined8 *)puVar11[1])[1];
                      if (pauStack_780 == (undefined1 (*) [16])0x0) {
                        pauStack_780 = (undefined1 (*) [16])&pauStack_780;
                      }
                      else {
                        pauVar35 = (undefined1 (*) [16])&pauStack_780;
                        if (pauStack_780 != pauVar35) goto LAB_017a944c;
                      }
                      pauVar35 = (undefined1 (*) [16])&pauStack_780;
                      pauVar37 = (undefined1 (*) [16])((long)*pauStack_770 + (long)*pauVar13);
                      pauVar31 = pauStack_778;
                      pauVar27 = pauStack_768;
                      if (pauStack_768 < pauVar37) {
                        pauStack_860 = pauStack_770;
                        pauStack_a50 = pauVar13;
                        uStack_758 = *(undefined8 *)puVar11[1];
                        pauVar31 = (undefined1 (*) [16])runtime_growslice(pauVar13,&DAT_0194e2a0);
                        pauVar14 = pauVar13;
                        pauVar13 = pauStack_a50;
                      }
                      pauStack_868 = pauVar37;
                      pauStack_860 = pauVar27;
                      pauStack_4e8 = pauVar31;
                      runtime_memmove();
                      pauStack_770 = pauStack_868;
                      pauStack_768 = pauStack_860;
                      pauStack_778 = pauStack_4e8;
                      pauVar29 = pauStack_588;
                      pauVar37 = pauStack_8c8;
                      pauVar27 = pauStack_558;
                      pauVar25 = pauStack_8d0;
                      pauVar38 = pauStack_4d8;
                      unaff_R13 = pauStack_850;
                    }
                    else {
                      pauVar13 = (undefined1 (*) [16])0x0;
                      pauVar15 = (undefined1 (*) [16])&DAT_01c397b2;
                      pauVar14 = (undefined1 (*) [16])0x4;
                      puVar11 = (undefined8 *)runtime_mapaccess1_faststr();
                      pauVar29 = pauStack_588;
                      pauVar37 = pauStack_8c8;
                      pauVar27 = pauStack_558;
                      pauVar25 = pauStack_8d0;
                      pauVar38 = pauStack_4d8;
                      unaff_R13 = pauStack_850;
                      if ((undefined *)*puVar11 == &DAT_0194e220) {
                        pauVar37 = (undefined1 (*) [16])((undefined8 *)puVar11[1])[1];
                        if (pauStack_780 == (undefined1 (*) [16])0x0) {
                          pauStack_780 = (undefined1 (*) [16])&pauStack_780;
                        }
                        else {
                          pauVar13 = pauStack_780;
                          if (pauStack_780 != (undefined1 (*) [16])&pauStack_780) goto LAB_017a943d;
                        }
                        pauVar31 = (undefined1 (*) [16])((long)*pauStack_770 + (long)*pauVar37);
                        pauVar27 = pauStack_778;
                        pauVar29 = pauStack_768;
                        pauVar13 = pauStack_770;
                        if (pauStack_768 < pauVar31) {
                          pauStack_860 = pauStack_770;
                          pauStack_a30 = pauVar37;
                          uStack_6b8 = *(undefined8 *)puVar11[1];
                          pauVar27 = (undefined1 (*) [16])runtime_growslice(pauVar37,&DAT_0194e2a0);
                          pauVar14 = pauVar37;
                          pauVar13 = pauStack_860;
                        }
                        pauStack_868 = pauVar31;
                        pauStack_860 = pauVar29;
                        pauStack_4e8 = pauVar27;
                        runtime_memmove();
                        pauStack_770 = pauStack_868;
                        pauStack_768 = pauStack_860;
                        pauStack_778 = pauStack_4e8;
                        pauVar29 = pauStack_588;
                        pauVar37 = pauStack_8c8;
                        pauVar27 = pauStack_558;
                        pauVar25 = pauStack_8d0;
                        pauVar38 = pauStack_4d8;
                        unaff_R13 = pauStack_850;
                      }
                    }
                  }
                  else if (*plVar20 == 0x6573755f6c6f6f74) {
                    puVar11 = (undefined8 *)runtime_mapaccess1_faststr(2);
                    if ((undefined *)*puVar11 == &DAT_0194e220) {
                      pauStack_7c8 = *(undefined1 (**) [16])puVar11[1];
                      pauStack_a80 = (undefined1 (*) [16])((undefined8 *)puVar11[1])[1];
                    }
                    else {
                      pauStack_a80 = (undefined1 (*) [16])0x0;
                      pauStack_7c8 = (undefined1 (*) [16])0x0;
                    }
                    puVar11 = (undefined8 *)runtime_mapaccess1_faststr(4,pauStack_a80,&DAT_0194e220,&DAT_01c39796)
                    ;
                    if ((undefined *)*puVar11 == &DAT_0194e220) {
                      pauStack_658 = *(undefined1 (**) [16])puVar11[1];
                      pauStack_9d8 = (undefined1 (*) [16])((undefined8 *)puVar11[1])[1];
                    }
                    else {
                      pauStack_9d8 = (undefined1 (*) [16])0x0;
                      pauStack_658 = (undefined1 (*) [16])0x0;
                    }
                    pauVar14 = (undefined1 (*) [16])0x5;
                    puVar11 = (undefined8 *)runtime_mapaccess1_faststr();
                    pauStack_48 = (undefined1 (*) [16])*puVar11;
                    pauStack_40 = (undefined1 (*) [16])puVar11[1];
                    pauVar13 = (undefined1 (*) [16])((long)*pauStack_8d0 + 1);
                    pauStack_38 = pauStack_658;
                    pauStack_30 = pauStack_9d8;
                    pauStack_28 = pauStack_7c8;
                    pauStack_20 = pauStack_a80;
                    pauStack_860 = pauVar13;
                    uVar12 = runtime_convT();
                    pauVar25 = pauStack_860;
                    pauVar37 = pauStack_8c8;
                    pauVar31 = pauStack_558;
                    if (pauStack_8c8 < pauStack_860) {
                      pauVar14 = (undefined1 (*) [16])0x1;
                      uStack_4e0 = uVar12;
                      pauVar31 = (undefined1 (*) [16])runtime_growslice(1,&DAT_019b39a0);
                      uVar12 = uStack_4e0;
                    }
                    auVar54._8_8_ = pauVar31;
                    auVar54._0_8_ = uVar12;
                    lVar21 = (long)pauVar25[-1] + 0xf;
                    *(undefined **)pauVar31[lVar21] = &DAT_01ad55a0;
                    if (DAT_02e5e450 != 0) {
                      uVar12 = *(undefined8 *)((long)pauVar31[lVar21] + 8);
                      auVar54 = runtime_gcWriteBarrier2();
                      *(long *)*pauVar35 = auVar54._0_8_;
                      *(undefined8 *)((long)*pauVar35 + 8) = uVar12;
                    }
                    *(long *)((long)auVar54._8_8_[lVar21] + 8) = auVar54._0_8_;
                    pauVar29 = pauStack_588;
                    pauVar27 = auVar54._8_8_;
                    pauVar38 = pauStack_4d8;
                    unaff_R13 = pauStack_850;
                  }
                }
              }
              else {
                pauVar14 = (undefined1 (*) [16])0x0;
                pauVar25 = pauVar31;
                unaff_R13 = pauVar15;
              }
              pauVar31 = pauVar25;
              pauVar38 = pauVar38 + 1;
              pauVar15 = (undefined1 (*) [16])(unaff_R13[-1] + 0xf);
            } while( true );
          }
          goto LAB_017a61c7;
        }
        pauStack_850 = (undefined1 (*) [16])((long)pauVar31 - (long)pauVar37);
        pauVar15 = (undefined1 (*) [16])runtime_newobject();
        *(long *)pauVar15[3] = lStack_9c8;
        if (DAT_02e5e450 != 0) {
          pauVar15 = (undefined1 (*) [16])runtime_gcWriteBarrier1();
          *(undefined8 *)*pauVar35 = uStack_648;
        }
        pauVar37 = (undefined1 (*) [16])uStack_d8;
        *(undefined8 *)((long)pauVar15[2] + 8) = uStack_648;
        *(undefined8 *)pauVar15[4] = 9;
        *(undefined **)((long)pauVar15[3] + 8) = &DAT_01c41eb5;
        if (pauStack_e0 != (undefined1 (*) [16])&DAT_0192e960) {
          pauVar27 = (undefined1 (*) [16])0x0;
          pauVar31 = (undefined1 (*) [16])0x0;
        }
        else {
          pauVar31 = *(undefined1 (**) [16])*(undefined1 (*) [16])uStack_d8;
          pauVar27 = *(undefined1 (**) [16])((long)*(undefined1 (*) [16])uStack_d8 + 8);
        }
        pauStack_820 = pauVar15;
        if (pauStack_e0 != (undefined1 (*) [16])&DAT_0192e960) {
          uVar12 = kiro2api_internal_logic_kiro_getContentText();
          *(undefined1 (**) [16])((long)*pauStack_820 + 8) = pauVar37;
          pauVar15 = pauStack_820;
          if (DAT_02e5e450 != 0) {
            auVar40 = runtime_gcWriteBarrier2();
            uVar12 = auVar40._0_8_;
            *pauVar35 = auVar40;
          }
          *(undefined8 *)*pauVar15 = uVar12;
          auVar55 = ZEXT816(0);
          puVar11 = (undefined8 *)0x0;
          pauVar31 = (undefined1 (*) [16])0x0;
          pauVar14 = (undefined1 (*) [16])0x0;
          pauVar13 = (undefined1 (*) [16])0x0;
LAB_017a946a:
          lVar21 = auVar55._8_8_;
          if (auVar55._0_8_ != 0) {
            *(long *)((long)pauVar15[1] + 8) = auVar55._0_8_;
            *(undefined1 (**) [16])pauVar15[2] = pauVar14;
            if (DAT_02e5e450 != 0) {
              uVar12 = *(undefined8 *)pauVar15[1];
              runtime_gcWriteBarrier2();
              *(undefined8 **)*pauVar35 = puVar11;
              *(undefined8 *)((long)*pauVar35 + 8) = uVar12;
              lVar21 = extraout_RDX_02;
            }
            *(undefined8 **)pauVar15[1] = puVar11;
          }
          pauStack_7b0 = pauVar13;
          pauStack_a68 = pauVar31;
          if (0 < lVar21) {
            auVar40 = runtime_convT64();
            uStack_10 = auVar40._0_8_;
            puStack_18 = &DAT_0194e460;
            uVar12 = fmt_Sprintf(1,1,auVar40._8_8_,&puStack_18);
            lVar21 = *(long *)((long)*pauStack_820 + 8);
            if (lVar21 == 0) {
              *(undefined8 *)((long)*pauStack_820 + 8) = 0x3c;
              pauVar15 = pauStack_820;
              if (DAT_02e5e450 != 0) {
                auVar40 = runtime_gcWriteBarrier2();
                uVar12 = auVar40._0_8_;
                *pauVar35 = auVar40;
              }
              *(undefined8 *)*pauVar15 = uVar12;
            }
            else {
              uVar28 = *(undefined8 *)*pauStack_820;
              uVar12 = runtime_concatstring3(&DAT_01f34d88,1,lVar21,lVar21,uVar12,0x3c);
              auVar56._8_8_ = pauStack_820;
              auVar56._0_8_ = uVar12;
              *(undefined8 *)((long)*pauStack_820 + 8) = uVar28;
              if (DAT_02e5e450 != 0) {
                uVar12 = *(undefined8 *)*pauStack_820;
                auVar56 = runtime_gcWriteBarrier2();
                *(long *)*pauVar35 = auVar56._0_8_;
                *(undefined8 *)((long)*pauVar35 + 8) = uVar12;
              }
              pauVar15 = auVar56._8_8_;
              *(long *)*pauVar15 = auVar56._0_8_;
            }
          }
          if (pauStack_978 == (undefined1 (*) [16])0x0) {
            pauVar31 = (undefined1 (*) [16])0x0;
            pauVar37 = (undefined1 (*) [16])0x0;
          }
          else {
            puVar11 = *(undefined8 **)((long)pauStack_5f0[(long)pauStack_978[-1] + 0xf] + 8);
            if ((puVar11 == (undefined8 *)0x0) || (puVar11[3] == 0)) {
              pauVar31 = (undefined1 (*) [16])0x0;
              pauVar37 = (undefined1 (*) [16])0x0;
            }
            else {
              puStack_540 = puVar11;
              FUN_00488ccb(auStack_1e0);
              uStack_1e8 = 0x8080808080808080;
              puStack_110 = &uStack_1e8;
              uStack_118 = runtime_rand();
              pauVar37 = (undefined1 (*) [16])puStack_540[2];
              for (pauVar31 = (undefined1 (*) [16])puStack_540[3]; 0 < (long)pauVar31;
                  pauVar31 = (undefined1 (*) [16])((long)pauVar31[-1] + 0xf)) {
                puVar11 = *(undefined8 **)(*pauVar37 + 8);
                bVar39 = *(undefined **)*pauVar37 == &DAT_01ad55a0;
                pauStack_f0 = in_XMM15_Qa;
                pauStack_e8 = in_XMM15_Qb;
                pauStack_e0 = in_XMM15_Qa;
                uStack_d8 = (undefined **)in_XMM15_Qb;
                uStack_d0 = in_XMM15_Qa;
                uStack_c8 = in_XMM15_Qb;
                if (bVar39) {
                  pauStack_f0 = (undefined1 (*) [16])*puVar11;
                  pauStack_e8 = (undefined1 (*) [16])puVar11[1];
                  pauStack_e0 = (undefined1 (*) [16])puVar11[2];
                  uStack_d8 = (undefined **)puVar11[3];
                  uStack_d0 = (undefined1 (*) [16])puVar11[4];
                  uStack_c8 = (undefined1 (*) [16])puVar11[5];
                }
                pauStack_48 = pauStack_f0;
                pauStack_40 = pauStack_e8;
                pauStack_38 = pauStack_e0;
                pauStack_30 = (undefined1 (*) [16])uStack_d8;
                pauStack_28 = uStack_d0;
                pauStack_20 = uStack_c8;
                pauStack_628 = pauStack_f0;
                pauStack_620 = pauStack_e8;
                pauStack_618 = pauStack_e0;
                pauStack_610 = (undefined1 (*) [16])uStack_d8;
                uStack_608 = (undefined4)uStack_d0;
                uStack_604 = uStack_d0._4_4_;
                uStack_600 = (undefined4)uStack_c8;
                uStack_5fc = uStack_c8._4_4_;
                if (bVar39) {
                  pauStack_850 = pauVar31;
                  pauStack_4d8 = pauVar37;
                  puVar18 = (undefined1 *)runtime_mapassign_faststr(uStack_c8,&DAT_01ad55a0,puVar11,uStack_d0);
                  *puVar18 = 1;
                  pauVar31 = pauStack_850;
                  pauVar37 = pauStack_4d8;
                }
                pauVar37 = pauVar37 + 1;
              }
              pauStack_960 = (undefined1 (*) [16])0x0;
              pauStack_5e8 = (undefined1 (*) [16])&puStack_848;
              pauStack_968 = (undefined1 (*) [16])0x0;
              pauVar37 = pauStack_a68;
              pauVar31 = pauStack_7b0;
              while (0 < (long)pauVar37) {
                pauStack_f0 = *(undefined1 (**) [16])*pauVar31;
                pauStack_e8 = *(undefined1 (**) [16])(*pauVar31 + 8);
                pauStack_e0 = *(undefined1 (**) [16])pauVar31[1];
                uStack_d8 = *(undefined ***)(pauVar31[1] + 8);
                uStack_d0 = *(undefined1 (**) [16])pauVar31[2];
                uStack_c8 = *(undefined1 (**) [16])(pauVar31[2] + 8);
                uStack_c0 = *(undefined8 *)pauVar31[3];
                pauStack_850 = pauVar37;
                pauStack_4d8 = pauVar31;
                pcVar17 = (char *)runtime_mapaccess1_faststr(uStack_c0,pauStack_f0,pauVar31,uStack_c8);
                if (*pcVar17 != '\0') {
                  pauVar31 = (undefined1 (*) [16])((long)*pauStack_968 + 1);
                  pauVar37 = pauStack_5e8;
                  if (pauStack_960 < pauVar31) {
                    pauVar37 = (undefined1 (*) [16])runtime_growslice(1,&DAT_01ad5660);
                  }
                  pauVar13 = (undefined1 (*) [16])((long)pauVar31 * 0x38);
                  pauStack_968 = pauVar31;
                  pauStack_4f0 = pauVar37;
                  if (DAT_02e5e450 != 0) {
                    pauStack_860 = (undefined1 (*) [16])((long)pauVar31 * 0x38);
                    runtime_wbMove();
                    pauVar13 = pauStack_860;
                  }
                  puVar19 = (undefined8 *)*pauVar13;
                  puVar11 = (undefined8 *)((long)pauStack_4f0[-2] + (long)puVar19);
                  *(undefined1 (**) [16])((long)((long)pauVar13[-4] + 8) + (long)pauStack_4f0) =
                       pauStack_f0;
                  *(undefined1 (**) [16])((long)pauStack_4f0[-3] + (long)*pauVar13) = pauStack_e8;
                  *(undefined1 (**) [16])((long)pauStack_4f0[-3] + (long)((long)*pauVar13 + 8)) =
                       pauStack_e0;
                  *puVar11 = uStack_d8;
                  *(undefined1 (**) [16])((long)pauStack_4f0[-2] + (long)(puVar19 + 1)) = uStack_d0;
                  *(undefined4 *)((long)pauStack_4f0[-1] + (long)puVar19) = (undefined4)uStack_c8;
                  *(undefined4 *)((long)pauStack_4f0[-1] + (long)puVar19 + 4) = uStack_c8._4_4_;
                  *(undefined4 *)((long)pauStack_4f0[-1] + (long)(puVar19 + 1)) =
                       (undefined4)uStack_c0;
                  *(undefined4 *)((long)pauStack_4f0[-1] + (long)puVar19 + 0xc) = uStack_c0._4_4_;
                  runtime_mapdelete_faststr(uStack_c0,puVar11,pauVar13,uStack_c8);
                  pauStack_5e8 = pauStack_4f0;
                }
                pauVar31 = (undefined1 (*) [16])(pauStack_4d8[3] + 8);
                pauVar37 = (undefined1 (*) [16])((long)pauStack_850[-1] + 0xf);
              }
              FUN_00488ceb(&uStack_c8);
              runtime_mapIterStart();
              pauVar31 = pauStack_5e8;
              while (pauVar37 = pauStack_968, pauVar15 = pauStack_820,
                    puStack_a8 != (undefined8 *)0x0) {
                pauStack_8e8 = pauStack_968;
                pauStack_a60 = pauStack_960;
                pauStack_7c0 = (undefined1 (*) [16])*puStack_a8;
                uStack_a78 = puStack_a8[1];
                pauStack_568 = pauVar31;
                pauStack_f0 = (undefined1 (*) [16])runtime_newobject();
                *(undefined8 *)((long)*pauStack_f0 + 8) = 0x19;
                pauVar13 = (undefined1 (*) [16])((long)*pauStack_8e8 + 1);
                *(undefined **)*pauStack_f0 = &DAT_01c5fbc8;
                pauStack_e8 = (undefined1 (*) [16])0x1;
                pauStack_e0 = (undefined1 (*) [16])0x1;
                uStack_d8 = (undefined **)&DAT_01c3dd13;
                uStack_d0 = (undefined1 (*) [16])0x7;
                uStack_c8 = pauStack_7c0;
                uStack_c0 = uStack_a78;
                pauVar37 = pauStack_568;
                pauVar31 = pauStack_a60;
                if (pauStack_a60 < pauVar13) {
                  pauVar37 = (undefined1 (*) [16])runtime_growslice(1,&DAT_01ad5660);
                }
                pauVar27 = (undefined1 (*) [16])((long)pauVar13 * 0x38);
                pauStack_968 = pauVar13;
                pauStack_960 = pauVar31;
                pauStack_4f0 = pauVar37;
                if (DAT_02e5e450 != 0) {
                  pauStack_850 = (undefined1 (*) [16])((long)pauVar13 * 0x38);
                  runtime_wbMove();
                  pauVar27 = pauStack_850;
                }
                puVar11 = (undefined8 *)*pauVar27;
                *(undefined1 (**) [16])((long)((long)pauVar27[-4] + 8) + (long)pauStack_4f0) =
                     pauStack_f0;
                *(undefined1 (**) [16])((long)pauStack_4f0[-3] + (long)*pauVar27) = pauStack_e8;
                *(undefined1 (**) [16])((long)pauStack_4f0[-3] + (long)((long)*pauVar27 + 8)) =
                     pauStack_e0;
                *(undefined ***)((long)pauStack_4f0[-2] + (long)puVar11) = uStack_d8;
                *(undefined1 (**) [16])((long)pauStack_4f0[-2] + (long)(puVar11 + 1)) = uStack_d0;
                *(undefined4 *)((long)pauStack_4f0[-1] + (long)puVar11) = (undefined4)uStack_c8;
                *(undefined4 *)((long)pauStack_4f0[-1] + (long)((long)puVar11 + 4)) =
                     uStack_c8._4_4_;
                *(undefined4 *)((long)pauStack_4f0[-1] + (long)(puVar11 + 1)) =
                     (undefined4)uStack_c0;
                *(undefined4 *)((long)pauStack_4f0[-1] + (long)((long)puVar11 + 0xc)) =
                     uStack_c0._4_4_;
                runtime_mapIterNext();
                pauVar31 = pauStack_4f0;
              }
            }
          }
          if (pauVar37 != (undefined1 (*) [16])0x0) {
            pauStack_a68 = pauVar37;
            pauStack_7b0 = pauVar31;
            FUN_00488ccb(auStack_2d8);
            uStack_2e0 = 0x8080808080808080;
            puStack_208 = &uStack_2e0;
            uStack_210 = runtime_rand();
            uStack_ad0 = 0;
            puStack_800 = &DAT_02e5d6a0;
            uStack_ae0 = 0;
            pauVar37 = pauStack_7b0;
            pauVar31 = pauStack_a68;
            while (0 < (long)pauVar31) {
              pauStack_f0 = *(undefined1 (**) [16])*pauVar37;
              pauStack_e8 = *(undefined1 (**) [16])(*pauVar37 + 8);
              pauStack_e0 = *(undefined1 (**) [16])pauVar37[1];
              uStack_d8 = *(undefined ***)(pauVar37[1] + 8);
              uStack_d0 = *(undefined1 (**) [16])pauVar37[2];
              uStack_c8 = *(undefined1 (**) [16])(pauVar37[2] + 8);
              uStack_c0 = *(undefined8 *)pauVar37[3];
              pauStack_850 = pauVar31;
              pauStack_4d8 = pauVar37;
              pcVar17 = (char *)runtime_mapaccess1_faststr(uStack_c0,uStack_ae0,pauStack_f0,uStack_c8);
              if (*pcVar17 == '\0') {
                puVar18 = (undefined1 *)runtime_mapassign_faststr(uStack_c0);
                *puVar18 = 1;
                uVar26 = uStack_ae0 + 1;
                puVar11 = puStack_800;
                uVar24 = uStack_ad0;
                if (uStack_ad0 < uVar26) {
                  puVar11 = (undefined8 *)runtime_growslice(1,&DAT_01ad5660);
                }
                pauVar37 = (undefined1 (*) [16])(uVar26 * 0x38);
                if (DAT_02e5e450 != 0) {
                  uStack_8e0 = uVar24;
                  uStack_8d8 = uVar26;
                  pauStack_860 = (undefined1 (*) [16])(uVar26 * 0x38);
                  puStack_560 = puVar11;
                  runtime_wbMove();
                  puVar11 = puStack_560;
                  uVar24 = uStack_8e0;
                  pauVar37 = pauStack_860;
                  uVar26 = uStack_8d8;
                }
                *(undefined1 (**) [16])((long)puVar11 + (long)((long)pauVar37[-4] + 8)) =
                     pauStack_f0;
                *(undefined1 (**) [16])((long)pauVar37[-3] + (long)puVar11) = pauStack_e8;
                *(undefined1 (**) [16])((long)puVar11 + (long)((long)pauVar37[-3] + 8)) =
                     pauStack_e0;
                *(undefined ***)((long)pauVar37[-2] + (long)puVar11) = uStack_d8;
                *(undefined1 (**) [16])((long)puVar11 + (long)((long)pauVar37[-2] + 8)) = uStack_d0;
                *(undefined4 *)((long)pauVar37[-1] + (long)puVar11) = (undefined4)uStack_c8;
                *(undefined4 *)((long)puVar11 + (long)pauVar37[-1] + 4) = uStack_c8._4_4_;
                *(undefined4 *)((long)puVar11 + (long)((long)pauVar37[-1] + 8)) =
                     (undefined4)uStack_c0;
                *(undefined4 *)((long)puVar11 + (long)pauVar37[-1] + 0xc) = uStack_c0._4_4_;
                puStack_800 = puVar11;
                uStack_ad0 = uVar24;
                uStack_ae0 = uVar26;
              }
              pauVar37 = (undefined1 (*) [16])(pauStack_4d8[3] + 8);
              pauVar31 = (undefined1 (*) [16])((long)pauStack_850[-1] + 0xf);
            }
            uStack_520 = runtime_makemap_small();
            pauStack_4d8 = (undefined1 (*) [16])runtime_convTslice();
            puVar11 = (undefined8 *)runtime_mapassign_faststr(0xb);
            auVar57._8_8_ = pauStack_820;
            auVar57._0_8_ = puVar11;
            *puVar11 = &DAT_0192c840;
            uVar12 = uStack_520;
            pauVar37 = pauStack_4d8;
            if (DAT_02e5e450 != 0) {
              uVar28 = *(undefined8 *)((long)pauStack_820[4] + 8);
              uVar12 = puVar11[1];
              auVar57 = runtime_gcWriteBarrier4();
              pauVar37 = pauStack_4d8;
              *(undefined1 (**) [16])*pauVar35 = pauStack_4d8;
              *(undefined8 *)((long)*pauVar35 + 8) = uVar12;
              uVar12 = uStack_520;
              *(undefined8 *)pauVar35[1] = uStack_520;
              *(undefined8 *)((long)pauVar35[1] + 8) = uVar28;
            }
            pauVar15 = auVar57._8_8_;
            *(undefined1 (**) [16])(auVar57._0_8_ + 8) = pauVar37;
            *(undefined8 *)((long)pauVar15[4] + 8) = uVar12;
          }
          lVar21 = *(long *)((long)*pauVar15 + 8);
          strings_TrimSpace();
          pauVar37 = pauStack_820;
          if (lVar21 == 0) {
            *(undefined8 *)((long)*pauStack_820 + 8) = 8;
            if (DAT_02e5e450 != 0) {
              uVar12 = *(undefined8 *)*pauStack_820;
              runtime_gcWriteBarrier1();
              *(undefined8 *)*pauVar35 = uVar12;
              pauVar37 = extraout_RDX_03;
            }
            *(undefined **)*pauVar37 = &DAT_01c3ffa7;
          }
          pauVar31 = pauStack_978;
          pauVar27 = (undefined1 (*) [16])((long)*pauStack_978 + 1);
          pauVar13 = pauStack_5f0;
          pauVar14 = pauStack_970;
          if (pauStack_970 < pauVar27) {
            pauVar13 = (undefined1 (*) [16])
                       runtime_growslice(1,&DAT_01a92fc0,pauVar37,pauStack_970,&DAT_01c3ffa7);
            pauVar37 = pauStack_820;
          }
          auVar58._8_8_ = pauVar37;
          auVar58._0_8_ = pauVar13;
          lVar21 = (long)pauVar31 * 0x10;
          if (DAT_02e5e450 != 0) {
            uVar12 = *(undefined8 *)pauVar13[(long)pauVar31];
            uVar28 = *(undefined8 *)((long)pauVar13[(long)pauVar31] + 8);
            auVar58 = runtime_gcWriteBarrier3();
            *(long *)*pauVar35 = auVar58._8_8_;
            *(undefined8 *)((long)*pauVar35 + 8) = uVar12;
            *(undefined8 *)pauVar35[1] = uVar28;
          }
          lVar30 = auVar58._0_8_;
          auVar53._8_8_ = pauVar14;
          auVar53._0_8_ = lVar30;
          *(long *)(lVar30 + lVar21) = auVar58._8_8_;
          *(undefined8 *)(lVar30 + lVar21 + 8) = 0;
          pauVar29 = pauStack_ac8;
          puVar11 = puStack_668;
          pauVar14 = pauStack_ac0;
          pauVar13 = pauStack_7f8;
          pauVar31 = pauStack_9f0;
          goto LAB_017a61c7;
        }
        puVar18 = (undefined1 *)((long)pauStack_850[-1] + 0xf);
        pauStack_6f0 = in_XMM15_Qa;
        pauStack_6e8 = in_XMM15_Qb;
        pauStack_6e0 = in_XMM15_Qa;
        pauStack_6d8 = in_XMM15_Qb;
        puVar11 = (undefined8 *)0x0;
        pauVar37 = (undefined1 (*) [16])0x0;
        pauVar13 = (undefined1 (*) [16])0x0;
        pauStack_a68 = (undefined1 (*) [16])0x0;
        pauVar14 = (undefined1 (*) [16])0x0;
        pauVar35 = (undefined1 (*) [16])0x0;
        unaff_R13 = (undefined1 (*) [16])0x0;
        puStack_958 = puVar18;
        for (; 0 < (long)pauVar27; pauVar27 = (undefined1 (*) [16])((long)pauVar27[-1] + 0xf)) {
          if (*(undefined **)*pauVar31 == &DAT_01a233a0) {
            uStack_598 = *(undefined8 *)(*pauVar31 + 8);
            pauStack_9a0 = pauVar35;
            pauStack_998 = pauVar14;
            pauStack_990 = unaff_R13;
            pauStack_8f0 = pauVar37;
            pauStack_850 = pauVar27;
            puStack_5f8 = puVar11;
            pauStack_570 = pauVar13;
            pauStack_4d8 = pauVar31;
            puVar11 = (undefined8 *)runtime_mapaccess1_faststr(4,puVar18,&DAT_01a233a0,&DAT_01c397aa);
            if ((undefined *)*puVar11 == &DAT_0194e220) {
              plVar20 = *(long **)puVar11[1];
              lVar21 = ((undefined8 *)puVar11[1])[1];
            }
            else {
              lVar21 = 0;
              plVar20 = (long *)0x0;
            }
            pauVar13 = pauStack_570;
            pauVar15 = pauStack_820;
            pauVar37 = pauStack_8f0;
            pauVar14 = pauStack_998;
            puVar11 = puStack_5f8;
            puVar18 = puStack_958;
            pauVar31 = pauStack_4d8;
            pauVar27 = pauStack_850;
            pauVar29 = pauStack_9a0;
            pauVar38 = pauStack_990;
            if (lVar21 == 4) {
              if (((int)*plVar20 == 0x74786574) &&
                 (puVar19 = (undefined8 *)runtime_mapaccess1_faststr(4,4,&DAT_0194e220,&DAT_01c397b2),
                 pauVar15 = pauStack_820, pauVar14 = pauStack_998, puVar18 = puStack_958,
                 puVar11 = puStack_5f8, pauVar31 = pauStack_4d8, pauVar27 = pauStack_850,
                 pauVar29 = pauStack_9a0, pauVar37 = pauStack_8f0, pauVar38 = pauStack_990,
                 pauVar13 = pauStack_570, (undefined *)*puVar19 == &DAT_0194e220)) {
                lVar21 = ((undefined8 *)puVar19[1])[1];
                if (pauStack_6f0 == (undefined1 (*) [16])0x0) {
                  pauStack_6f0 = (undefined1 (*) [16])&pauStack_6f0;
                }
                else if (pauStack_6f0 != (undefined1 (*) [16])&pauStack_6f0) goto LAB_017aa96a;
                pauVar37 = (undefined1 (*) [16])((long)*pauStack_6e0 + lVar21);
                pauVar31 = pauStack_6e8;
                pauVar13 = pauStack_6d8;
                if (pauStack_6d8 < pauVar37) {
                  pauStack_860 = pauStack_6e0;
                  lStack_a20 = lVar21;
                  uStack_6a8 = *(undefined8 *)puVar19[1];
                  pauVar31 = (undefined1 (*) [16])runtime_growslice(lVar21,&DAT_0194e2a0);
                }
                pauStack_868 = pauVar13;
                pauStack_860 = pauVar37;
                pauStack_4e8 = pauVar31;
                runtime_memmove();
                pauStack_6e0 = pauStack_860;
                pauStack_6d8 = pauStack_868;
                pauStack_6e8 = pauStack_4e8;
                pauVar15 = pauStack_820;
                pauVar14 = pauStack_998;
                puVar18 = puStack_958;
                puVar11 = puStack_5f8;
                pauVar31 = pauStack_4d8;
                pauVar27 = pauStack_850;
                pauVar29 = pauStack_9a0;
                pauVar37 = pauStack_8f0;
                pauVar38 = pauStack_990;
                pauVar13 = pauStack_570;
              }
            }
            else if (lVar21 == 5) {
              if (((int)*plVar20 == 0x67616d69) && (*(char *)((long)plVar20 + 4) == 'e')) {
                if ((long)puStack_958 < 6) {
                  puVar19 = (undefined8 *)runtime_mapaccess1_faststr(6,puStack_958,&DAT_0194e220,&DAT_01c3bd83);
                  pauVar15 = pauStack_820;
                  pauVar14 = pauStack_998;
                  puVar18 = puStack_958;
                  puVar11 = puStack_5f8;
                  pauVar31 = pauStack_4d8;
                  pauVar27 = pauStack_850;
                  pauVar29 = pauStack_9a0;
                  pauVar37 = pauStack_8f0;
                  pauVar38 = pauStack_990;
                  pauVar13 = pauStack_570;
                  if ((undefined *)*puVar19 == &DAT_01a233a0) {
                    uStack_680 = puVar19[1];
                    puVar11 = (undefined8 *)runtime_mapaccess1_faststr(10,uStack_680,&DAT_01a233a0,&DAT_01c44373);
                    if ((undefined *)*puVar11 == &DAT_0194e220) {
                      lStack_630 = *(long *)puVar11[1];
                      lStack_9a8 = ((long *)puVar11[1])[1];
                    }
                    else {
                      lStack_9a8 = 0;
                      lStack_630 = 0;
                    }
                    puVar11 = (undefined8 *)runtime_mapaccess1_faststr(4,lStack_9a8,&DAT_0194e220,&DAT_01c3977e);
                    if ((undefined *)*puVar11 == &DAT_0194e220) {
                      lStack_5d8 = *(long *)puVar11[1];
                      lStack_948 = ((long *)puVar11[1])[1];
                    }
                    else {
                      lStack_5d8 = 0;
                      lStack_948 = 0;
                    }
                    lVar21 = lStack_630;
                    lVar30 = lStack_9a8;
                    if ((5 < lStack_9a8) &&
                       (cVar10 = runtime_memequal(), lVar21 = lStack_630, lVar30 = lStack_9a8,
                       cVar10 != '\0')) {
                      lVar21 = lStack_630 + (ulong)((uint)(-(lStack_9a8 + -6) >> 0x3f) & 6);
                      lVar30 = lStack_9a8 + -6;
                    }
                    pauVar37 = pauStack_9a0;
                    pauVar29 = (undefined1 (*) [16])((long)*pauStack_9a0 + 1);
                    pauVar14 = pauStack_998;
                    puVar11 = puStack_5f8;
                    if (pauStack_998 < pauVar29) {
                      lStack_838 = lVar21;
                      puVar11 = (undefined8 *)runtime_growslice(1,&DAT_01a92e80,&DAT_0194e220);
                      lVar21 = lStack_838;
                    }
                    plVar20 = (long *)((long)pauVar37 * 0x20);
                    (puVar11 + 1)[(long)pauVar37 * 4] = lVar30;
                    (puVar11 + 3)[(long)pauVar37 * 4] = lStack_948;
                    lVar30 = lStack_5d8;
                    if (DAT_02e5e450 != 0) {
                      lVar16 = puVar11[(long)pauVar37 * 4];
                      lVar33 = (puVar11 + 2)[(long)pauVar37 * 4];
                      plVar36 = plVar20;
                      lVar21 = runtime_gcWriteBarrier4(plVar20,puVar11,&DAT_0194e220);
                      *plVar36 = lVar21;
                      plVar36[1] = lVar16;
                      plVar36[2] = lVar30;
                      plVar36[3] = lVar33;
                    }
                    *(long *)((long)puVar11 + (long)plVar20) = lVar21;
                    *(long *)((long)(puVar11 + 2) + (long)plVar20) = lVar30;
                    pauVar15 = pauStack_820;
                    puVar18 = puStack_958;
                    pauVar31 = pauStack_4d8;
                    pauVar27 = pauStack_850;
                    pauVar37 = pauStack_8f0;
                    pauVar38 = pauStack_990;
                    pauVar13 = pauStack_570;
                  }
                }
                else {
                  pauVar38 = (undefined1 (*) [16])((long)*pauStack_990 + 1);
                }
              }
            }
            else if ((((lVar21 == 0xb) && (*plVar20 == 0x7365725f6c6f6f74)) &&
                     ((short)plVar20[1] == 0x6c75)) && (*(char *)((long)plVar20 + 10) == 't')) {
              puVar11 = (undefined8 *)
                        runtime_mapaccess1_faststr(0xb,0x7365725f6c6f6f74,&DAT_0194e220,&DAT_01c462ec);
              if ((undefined *)*puVar11 == &DAT_0194e220) {
                pauStack_7b8 = *(undefined1 (**) [16])puVar11[1];
                uStack_a70 = ((undefined8 *)puVar11[1])[1];
              }
              else {
                uStack_a70 = 0;
                pauStack_7b8 = (undefined1 (*) [16])0x0;
              }
              lVar21 = runtime_mapaccess1_faststr(7,uStack_a70,&DAT_0194e220,&DAT_01c3dd44);
              uVar12 = *(undefined8 *)(lVar21 + 8);
              uStack_670 = kiro2api_internal_logic_kiro_getContentText();
              uStack_9f8 = uVar12;
              pauStack_f0 = (undefined1 (*) [16])runtime_newobject();
              *(undefined8 *)((long)*pauStack_f0 + 8) = uStack_9f8;
              if (DAT_02e5e450 != 0) {
                pauStack_f0 = (undefined1 (*) [16])runtime_gcWriteBarrier1();
                *(undefined8 *)*pauVar35 = uStack_670;
              }
              *(undefined8 *)*pauStack_f0 = uStack_670;
              pauStack_e8 = (undefined1 (*) [16])0x1;
              pauStack_e0 = (undefined1 (*) [16])0x1;
              uStack_d8 = (undefined **)&DAT_01c3dd13;
              uStack_d0 = (undefined1 (*) [16])0x7;
              uStack_c8 = pauStack_7b8;
              uStack_c0 = uStack_a70;
              pauVar35 = (undefined1 (*) [16])((long)*pauStack_a68 + 1);
              pauVar13 = pauStack_570;
              pauVar37 = pauStack_8f0;
              if (pauStack_8f0 < pauVar35) {
                pauVar13 = (undefined1 (*) [16])runtime_growslice(1,&DAT_01ad5660);
              }
              pauVar31 = (undefined1 (*) [16])((long)pauVar35 * 0x38);
              if (DAT_02e5e450 != 0) {
                pauStack_900 = pauVar37;
                pauStack_8f8 = pauVar35;
                pauStack_860 = (undefined1 (*) [16])((long)pauVar35 * 0x38);
                pauStack_578 = pauVar13;
                runtime_wbMove();
                pauVar13 = pauStack_578;
                pauVar37 = pauStack_900;
                pauVar31 = pauStack_860;
                pauVar35 = pauStack_8f8;
              }
              puVar18 = *pauVar13;
              *(undefined1 (**) [16])((long)((long)pauVar31[-4] + 8) + (long)pauVar13) = pauStack_f0
              ;
              *(undefined1 (**) [16])((long)pauVar31[-3] + (long)*pauVar13) = pauStack_e8;
              *(undefined1 (**) [16])((long)pauVar31[-3] + (long)(*pauVar13 + 8)) = pauStack_e0;
              *(undefined ***)((long)pauVar31[-2] + (long)puVar18) = uStack_d8;
              *(undefined1 (**) [16])((long)pauVar31[-2] + (long)(puVar18 + 8)) = uStack_d0;
              *(undefined4 *)((long)pauVar31[-1] + (long)puVar18) = (undefined4)uStack_c8;
              *(undefined4 *)((long)pauVar31[-1] + (long)(puVar18 + 4)) = uStack_c8._4_4_;
              *(undefined4 *)((long)pauVar31[-1] + (long)(puVar18 + 8)) = (undefined4)uStack_c0;
              *(undefined4 *)((long)pauVar31[-1] + (long)(puVar18 + 0xc)) = uStack_c0._4_4_;
              pauVar15 = pauStack_820;
              pauVar14 = pauStack_998;
              puVar18 = puStack_958;
              puVar11 = puStack_5f8;
              pauVar31 = pauStack_4d8;
              pauVar27 = pauStack_850;
              pauVar29 = pauStack_9a0;
              pauVar38 = pauStack_990;
              pauStack_a68 = pauVar35;
            }
          }
          else {
            uStack_598 = 0;
            pauVar29 = pauVar35;
            pauVar38 = unaff_R13;
          }
          pauVar31 = pauVar31 + 1;
          pauVar35 = pauVar29;
          unaff_R13 = pauVar38;
        }
        if (pauStack_6e0 <= (undefined1 (*) [16])-(long)pauStack_6e8) {
          *(undefined1 (**) [16])((long)*pauVar15 + 8) = pauStack_6e0;
          pauVar37 = pauStack_6e8;
          if (DAT_02e5e450 != 0) {
            uVar12 = *(undefined8 *)*pauVar15;
            pauVar31 = pauVar35;
            pauVar15 = (undefined1 (*) [16])runtime_gcWriteBarrier2();
            *(undefined1 (**) [16])*pauVar31 = pauVar37;
            *(undefined8 *)((long)*pauVar31 + 8) = uVar12;
          }
          auVar55._8_8_ = unaff_R13;
          auVar55._0_8_ = pauVar35;
          *(undefined1 (**) [16])*pauVar15 = pauVar37;
          pauVar31 = pauStack_a68;
          goto LAB_017a946a;
        }
        if (pauStack_6e8 != (undefined1 (*) [16])0x0) {
          runtime_panicunsafestringlen(puVar11,(undefined1 (*) [16])-(long)pauStack_6e8,uStack_648);
        }
        runtime_panicunsafestringnilptr();
LAB_017aa96a:
        pauVar27 = (undefined1 (*) [16])&DAT_01f393c0;
        runtime_gopanic();
        auVar53._8_8_ = pauStack_970;
        auVar53._0_8_ = pauStack_5f0;
LAB_017aa979:
        pauStack_970 = auVar53._8_8_;
        pauStack_5f0 = auVar53._0_8_;
        runtime_panicIndex();
      }
      else if (pauStack_9f0 != (undefined1 (*) [16])0x0) {
        if ((puStack_668[1] == 4) && (*(int *)*puStack_668 == 0x72657375)) {
          uVar12 = puStack_668[3];
          auVar40 = kiro2api_internal_logic_kiro_getContentText();
          pauVar37 = pauStack_6a0;
          runtime_concatstring3(&DAT_01f35098,2,auVar40._8_8_,pauStack_a18,auVar40._0_8_,uVar12);
          puStack_5b8 = (undefined *)strings_TrimSpace();
          pauStack_918 = pauVar37;
          puVar11 = (undefined8 *)runtime_newobject();
          pauVar37 = pauStack_918;
          if (pauStack_918 == (undefined1 (*) [16])0x0) {
            pauVar37 = (undefined1 (*) [16])0x8;
          }
          puVar11[1] = pauVar37;
          puVar23 = puStack_5b8;
          if (pauStack_918 == (undefined1 (*) [16])0x0) {
            puVar23 = &DAT_01c3ffa7;
          }
          if (DAT_02e5e450 != 0) {
            puVar11 = (undefined8 *)runtime_gcWriteBarrier2();
            *(undefined **)*pauVar31 = puVar23;
            *(undefined8 *)((long)*pauVar31 + 8) = uStack_648;
          }
          *puVar11 = puVar23;
          puVar11[6] = lStack_9c8;
          puVar11[5] = uStack_648;
          puVar11[8] = 9;
          puVar11[7] = &DAT_01c41eb5;
          uVar12 = 0;
          puStack_538 = puVar11;
          puVar11 = (undefined8 *)runtime_growslice(1,&DAT_01a92fc0);
          if (DAT_02e5e450 != 0) {
            uVar28 = puVar11[1];
            auVar40 = runtime_gcWriteBarrier3();
            puVar11 = auVar40._0_8_;
            *(undefined8 **)*pauVar31 = puStack_538;
            *(long *)((long)*pauVar31 + 8) = auVar40._8_8_;
            *(undefined8 *)pauVar31[1] = uVar28;
          }
          *puVar11 = puStack_538;
          puVar11[1] = 0;
          pauVar37 = (undefined1 (*) [16])0x1;
        }
        else {
          puVar11 = (undefined8 *)runtime_newobject();
          puVar11[1] = pauStack_a18;
          if (DAT_02e5e450 != 0) {
            puVar11 = (undefined8 *)runtime_gcWriteBarrier2();
            *(undefined1 (**) [16])*pauVar31 = pauStack_6a0;
            *(undefined8 *)((long)*pauVar31 + 8) = uStack_648;
          }
          *puVar11 = pauStack_6a0;
          puVar11[6] = lStack_9c8;
          puVar11[5] = uStack_648;
          puVar11[8] = 9;
          puVar11[7] = &DAT_01c41eb5;
          uVar12 = 0;
          puStack_538 = puVar11;
          puVar11 = (undefined8 *)runtime_growslice(1,&DAT_01a92fc0);
          if (DAT_02e5e450 != 0) {
            uVar28 = puVar11[1];
            auVar40 = runtime_gcWriteBarrier3();
            puVar11 = auVar40._0_8_;
            *(undefined8 **)*pauVar31 = puStack_538;
            *(long *)((long)*pauVar31 + 8) = auVar40._8_8_;
            *(undefined8 *)pauVar31[1] = uVar28;
          }
          *puVar11 = puStack_538;
          puVar11[1] = 0;
          pauVar37 = (undefined1 (*) [16])0x0;
        }
        auVar53._8_8_ = uVar12;
        auVar53._0_8_ = puVar11;
        pauVar27 = (undefined1 (*) [16])0x1;
        pauVar29 = pauStack_ac8;
        puVar11 = puStack_668;
        pauVar14 = pauStack_ac0;
        pauVar13 = pauStack_7f8;
        pauVar31 = pauStack_9f0;
        goto LAB_017a61cd;
      }
      pauVar37 = (undefined1 (*) [16])0x0;
      pauStack_7f8 = (undefined1 (*) [16])runtime_panicIndex();
      pauStack_ac0 = pauVar37;
      pauStack_ac8 = pauVar27;
    }
    else {
      pauStack_628 = *(undefined1 (**) [16])*pauVar13;
      pauVar31 = *(undefined1 (**) [16])(*pauVar13 + 8);
      pauStack_618 = *(undefined1 (**) [16])pauVar13[1];
      pauStack_610 = *(undefined1 (**) [16])(pauVar13[1] + 8);
      uStack_608 = *(undefined4 *)pauVar13[2];
      uStack_604 = *(undefined4 *)(pauVar13[2] + 4);
      pauStack_850 = pauVar37;
      pauStack_620 = pauVar31;
      pauStack_4d8 = pauVar13;
      plVar20 = (long *)strings_ToLower();
      pauVar37 = pauStack_618;
      if ((((pauVar31 != (undefined1 (*) [16])&DAT_0000000a) || (*plVar20 != 0x726165735f626577)) ||
          ((short)plVar20[1] != 0x6863)) &&
         (((pauVar31 != (undefined1 (*) [16])0x9 || (*plVar20 != 0x6372616573626577)) ||
          ((char)plVar20[1] != 'h')))) {
        pauVar31 = pauStack_618;
        pauVar13 = pauStack_610;
        if (0x2400 < (long)pauStack_610) {
          pauVar31 = (undefined1 (*) [16])
                     runtime_concatstring2(&DAT_01c38dc1,3,0x726165735f626577,0x2400,0x6372616573626577);
          pauVar13 = pauVar37;
        }
        pauVar14 = (undefined1 (*) [16])((long)*pauStack_ac8 + 1);
        pauStack_f0 = pauStack_628;
        pauStack_e8 = pauStack_620;
        uStack_d0 = (undefined1 (*) [16])CONCAT44(uStack_604,uStack_608);
        pauVar37 = pauStack_7f8;
        pauVar27 = pauStack_ac0;
        pauStack_e0 = pauVar31;
        uStack_d8 = (undefined **)pauVar13;
        if (pauStack_ac0 < pauVar14) {
          pauVar37 = (undefined1 (*) [16])
                     runtime_growslice(1,&DAT_01a377a0,0x726165735f626577,pauStack_ac0,0x6372616573626577
                                 );
        }
        pauVar31 = (undefined1 (*) [16])((long)pauVar14 * 5);
        if (DAT_02e5e450 != 0) {
          pauStack_910 = pauVar27;
          pauStack_908 = pauVar14;
          pauStack_860 = (undefined1 (*) [16])((long)pauVar14 * 5);
          pauStack_580 = pauVar37;
          runtime_wbMove();
          pauVar37 = pauStack_580;
          pauVar27 = pauStack_910;
          pauVar31 = pauStack_860;
          pauVar14 = pauStack_908;
        }
        *(undefined1 (**) [16])((long)pauVar37[5] + (undefined1 *)((long)pauVar31[-1] + 1) * 8) =
             pauStack_f0;
        *(undefined1 (**) [16])((long)pauVar37[6] + pauVar31[-1] * 8) = pauStack_e8;
        *(undefined1 (**) [16])((long)pauVar37[6] + (undefined1 *)((long)pauVar31[-1] + 1) * 8) =
             pauStack_e0;
        *(undefined4 *)((long)pauVar37[7] + pauVar31[-1] * 8) = (undefined4)uStack_d8;
        *(undefined4 *)((long)pauVar37[-1] + (long)pauVar31 * 8 + 4) = uStack_d8._4_4_;
        *(undefined4 *)((long)pauVar37[7] + (undefined1 *)((long)pauVar31[-1] + 1) * 8) =
             (undefined4)uStack_d0;
        *(undefined4 *)((long)pauVar37[-1] + (long)pauVar31 * 8 + 0xc) = uStack_d0._4_4_;
        pauStack_7f8 = pauVar37;
        pauStack_ac0 = pauVar27;
        pauStack_ac8 = pauVar14;
      }
    }
    pauVar13 = (undefined1 (*) [16])(pauStack_4d8[2] + 8);
    pauVar37 = (undefined1 (*) [16])((long)pauStack_850[-1] + 0xf);
    pauVar27 = pauStack_a18;
  } while( true );
LAB_017a7480:
  pauStack_970 = auVar53._8_8_;
  puVar11 = auVar53._0_8_;
  auVar44._8_8_ = pauStack_7f0;
  auVar44._0_8_ = pauStack_ab8;
  if ((long)pauVar27 < 1) goto LAB_017a7c75;
  if (*(undefined **)*pauVar37 == &DAT_01a233a0) {
    uStack_5b0 = *(undefined8 *)(*pauVar37 + 8);
    pauStack_938 = pauVar38;
    uStack_930 = uVar26;
    uStack_928 = uVar24;
    pauStack_850 = pauVar27;
    pauStack_5c8 = pauVar31;
    pauStack_4d8 = pauVar37;
    puVar19 = (undefined8 *)runtime_mapaccess1_faststr(4,uVar24,puVar23,&DAT_01c397aa);
    auVar8._8_8_ = pauStack_970;
    auVar8._0_8_ = pauStack_5f0;
    auVar7._8_8_ = pauStack_970;
    auVar7._0_8_ = pauStack_5f0;
    auVar6._8_8_ = pauStack_970;
    auVar6._0_8_ = pauStack_5f0;
    auVar53._8_8_ = pauStack_970;
    auVar53._0_8_ = pauStack_5f0;
    auVar5._8_8_ = pauStack_970;
    auVar5._0_8_ = pauStack_5f0;
    auVar4._8_8_ = pauStack_970;
    auVar4._0_8_ = pauStack_5f0;
    auVar3._8_8_ = pauStack_970;
    auVar3._0_8_ = pauStack_5f0;
    puVar23 = &DAT_0194e220;
    if ((undefined *)*puVar19 == &DAT_0194e220) {
      plVar20 = *(long **)puVar19[1];
      lVar21 = ((undefined8 *)puVar19[1])[1];
    }
    else {
      lVar21 = 0;
      plVar20 = (long *)0x0;
    }
    pauVar38 = pauStack_938;
    uVar24 = uStack_928;
    pauVar29 = pauStack_ac8;
    pauVar31 = pauStack_5c8;
    pauVar14 = pauStack_ac0;
    pauVar37 = pauStack_4d8;
    pauVar27 = pauStack_850;
    uVar26 = uStack_930;
    if (lVar21 == 4) {
      auVar53 = auVar3;
      if ((int)*plVar20 == 0x74786574) {
        pauVar29 = (undefined1 (*) [16])&DAT_01c397b2;
        puVar11 = (undefined8 *)runtime_mapaccess1_faststr(4);
        if ((undefined *)*puVar11 == &DAT_0194e220) {
          pauVar31 = *(undefined1 (**) [16])puVar11[1];
          pauVar13 = (undefined1 (*) [16])((undefined8 *)puVar11[1])[1];
          if (pauStack_750 == (undefined1 (*) [16])0x0) {
            pauStack_750 = (undefined1 (*) [16])&pauStack_750;
          }
          else {
            pauVar35 = (undefined1 (*) [16])&pauStack_750;
            if (pauStack_750 != pauVar35) goto LAB_017a7cc5;
          }
          pauVar37 = (undefined1 (*) [16])((long)*pauStack_740 + (long)*pauVar13);
          pauVar27 = pauStack_748;
          pauVar14 = pauStack_738;
          if (pauStack_738 < pauVar37) {
            pauStack_860 = pauStack_740;
            pauStack_a48 = pauVar13;
            pauStack_6d0 = pauVar31;
            pauVar27 = (undefined1 (*) [16])runtime_growslice(pauVar13,&DAT_0194e2a0);
          }
          pauStack_868 = pauVar14;
          pauStack_860 = pauVar37;
          pauStack_4e8 = pauVar27;
          runtime_memmove();
          pauStack_740 = pauStack_860;
          pauStack_738 = pauStack_868;
          pauStack_748 = pauStack_4e8;
        }
        auVar53._8_8_ = pauStack_970;
        auVar53._0_8_ = pauStack_5f0;
        puVar23 = &DAT_0194e220;
        pauVar29 = pauStack_ac8;
        uVar24 = uStack_928;
        pauVar14 = pauStack_ac0;
        pauVar31 = pauStack_5c8;
        pauVar37 = pauStack_4d8;
        pauVar27 = pauStack_850;
        pauVar38 = pauStack_938;
        uVar26 = uStack_930;
      }
    }
    else if (lVar21 == 5) {
      auVar53 = auVar4;
      if (((int)*plVar20 == 0x67616d69) && (auVar53 = auVar5, *(char *)((long)plVar20 + 4) == 'e'))
      {
        puVar11 = (undefined8 *)runtime_mapaccess1_faststr(6,5,&DAT_0194e220,&DAT_01c3bd83);
        auVar53._8_8_ = pauStack_970;
        auVar53._0_8_ = pauStack_5f0;
        if ((undefined *)*puVar11 == &DAT_01a233a0) {
          uStack_688 = puVar11[1];
          puVar11 = (undefined8 *)runtime_mapaccess1_faststr(10,uStack_688,&DAT_01a233a0,&DAT_01c44373);
          if ((undefined *)*puVar11 == &DAT_0194e220) {
            lStack_638 = *(long *)puVar11[1];
            lStack_9b0 = ((long *)puVar11[1])[1];
          }
          else {
            lStack_9b0 = 0;
            lStack_638 = 0;
          }
          puVar11 = (undefined8 *)runtime_mapaccess1_faststr(4,lStack_9b0,&DAT_0194e220,&DAT_01c3977e);
          if ((undefined *)*puVar11 == &DAT_0194e220) {
            uStack_5e0 = *(undefined8 *)puVar11[1];
            uStack_950 = ((undefined8 *)puVar11[1])[1];
          }
          else {
            uStack_5e0 = 0;
            uStack_950 = 0;
          }
          lVar21 = lStack_638;
          lVar30 = lStack_9b0;
          if ((5 < lStack_9b0) &&
             (cVar10 = runtime_memequal(), lVar21 = lStack_638, lVar30 = lStack_9b0, cVar10 != '\0')) {
            lVar21 = lStack_638 + (ulong)((uint)(-(lStack_9b0 + -6) >> 0x3f) & 6);
            lVar30 = lStack_9b0 + -6;
          }
          uVar9 = uStack_930;
          uVar26 = uStack_930 + 1;
          uVar24 = uStack_928;
          pauVar31 = pauStack_5c8;
          if (uStack_928 < uVar26) {
            lStack_840 = lVar21;
            pauVar31 = (undefined1 (*) [16])runtime_growslice(1,&DAT_01a92e80);
            lVar21 = lStack_840;
          }
          auVar43._8_8_ = &DAT_0194e220;
          auVar43._0_8_ = lVar21;
          puVar11 = (undefined8 *)(uVar9 * 0x20);
          *(long *)((long)pauVar31[uVar9 * 2] + 8) = lVar30;
          *(undefined8 *)((long)(pauVar31 + 1)[uVar9 * 2] + 8) = uStack_950;
          uVar12 = uStack_5e0;
          if (DAT_02e5e450 != 0) {
            uVar28 = *(undefined8 *)*(undefined1 (*) [16])((long)puVar11 + (long)pauVar31);
            uVar32 = *(undefined8 *)((long)(puVar11 + 2) + (long)pauVar31);
            puVar19 = puVar11;
            auVar43 = runtime_gcWriteBarrier4();
            *puVar19 = auVar43._0_8_;
            puVar19[1] = uVar28;
            puVar19[2] = uVar12;
            puVar19[3] = uVar32;
          }
          auVar53._8_8_ = pauStack_970;
          auVar53._0_8_ = pauStack_5f0;
          puVar23 = auVar43._8_8_;
          *(long *)((long)*pauVar31 + (long)puVar11) = auVar43._0_8_;
          *(undefined8 *)((long)pauVar31[1] + (long)puVar11) = uVar12;
          pauVar29 = pauStack_ac8;
          pauVar14 = pauStack_ac0;
          pauVar37 = pauStack_4d8;
          pauVar27 = pauStack_850;
          pauVar38 = pauStack_938;
        }
        else {
          puVar23 = &DAT_0194e220;
          pauVar29 = pauStack_ac8;
          uVar24 = uStack_928;
          pauVar14 = pauStack_ac0;
          pauVar31 = pauStack_5c8;
          pauVar37 = pauStack_4d8;
          pauVar27 = pauStack_850;
          pauVar38 = pauStack_938;
          uVar26 = uStack_930;
        }
      }
    }
    else if (((lVar21 == 0xb) && (auVar53 = auVar6, *plVar20 == 0x7365725f6c6f6f74)) &&
            ((auVar53 = auVar7, (short)plVar20[1] == 0x6c75 &&
             (auVar53 = auVar8, *(char *)((long)plVar20 + 10) == 't')))) {
      puVar19 = (undefined8 *)runtime_mapaccess1_faststr(0xb,0x7365725f6c6f6f74,&DAT_0194e220,&DAT_01c462ec);
      if ((undefined *)*puVar19 == &DAT_0194e220) {
        pauStack_7d8 = *(undefined1 (**) [16])puVar19[1];
        uStack_a90 = ((undefined8 *)puVar19[1])[1];
      }
      else {
        uStack_a90 = 0;
        pauStack_7d8 = (undefined1 (*) [16])0x0;
      }
      lVar21 = runtime_mapaccess1_faststr(7,uStack_a90,&DAT_0194e220,&DAT_01c3dd44);
      uVar12 = *(undefined8 *)(lVar21 + 8);
      uStack_678 = kiro2api_internal_logic_kiro_getContentText();
      uStack_a00 = uVar12;
      pauStack_f0 = (undefined1 (*) [16])runtime_newobject();
      *(undefined8 *)((long)*pauStack_f0 + 8) = uStack_a00;
      if (DAT_02e5e450 != 0) {
        pauStack_f0 = (undefined1 (*) [16])runtime_gcWriteBarrier1();
        *puVar11 = uStack_678;
      }
      *(undefined8 *)*pauStack_f0 = uStack_678;
      pauStack_e8 = (undefined1 (*) [16])0x1;
      pauStack_e0 = (undefined1 (*) [16])0x1;
      uStack_d8 = (undefined **)&DAT_01c3dd13;
      uStack_d0 = (undefined1 (*) [16])0x7;
      uStack_c8 = pauStack_7d8;
      uStack_c0 = uStack_a90;
      pauVar35 = (undefined1 (*) [16])((long)*pauStack_940 + 1);
      pauVar13 = pauStack_5d0;
      pauVar38 = pauStack_938;
      if (pauStack_938 < pauVar35) {
        pauVar13 = (undefined1 (*) [16])runtime_growslice(1,&DAT_01ad5660);
      }
      pauVar37 = (undefined1 (*) [16])((long)pauVar35 * 0x38);
      if (DAT_02e5e450 != 0) {
        pauStack_8b0 = pauVar38;
        pauStack_8a8 = pauVar35;
        pauStack_860 = (undefined1 (*) [16])((long)pauVar35 * 0x38);
        pauStack_548 = pauVar13;
        runtime_wbMove();
        pauVar13 = pauStack_548;
        pauVar38 = pauStack_8b0;
        pauVar37 = pauStack_860;
        pauVar35 = pauStack_8a8;
      }
      auVar53._8_8_ = pauStack_970;
      auVar53._0_8_ = pauStack_5f0;
      puVar18 = *pauVar13;
      *(undefined1 (**) [16])((long)((long)pauVar37[-4] + 8) + (long)pauVar13) = pauStack_f0;
      *(undefined1 (**) [16])((long)pauVar37[-3] + (long)*pauVar13) = pauStack_e8;
      *(undefined1 (**) [16])((long)pauVar37[-3] + (long)(*pauVar13 + 8)) = pauStack_e0;
      *(undefined ***)((long)pauVar37[-2] + (long)puVar18) = uStack_d8;
      *(undefined1 (**) [16])((long)pauVar37[-2] + (long)(puVar18 + 8)) = uStack_d0;
      *(undefined4 *)((long)pauVar37[-1] + (long)puVar18) = (undefined4)uStack_c8;
      *(undefined4 *)((long)pauVar37[-1] + (long)(puVar18 + 4)) = uStack_c8._4_4_;
      *(undefined4 *)((long)pauVar37[-1] + (long)(puVar18 + 8)) = (undefined4)uStack_c0;
      *(undefined4 *)((long)pauVar37[-1] + (long)(puVar18 + 0xc)) = uStack_c0._4_4_;
      puVar23 = &DAT_0194e220;
      pauVar29 = pauStack_ac8;
      uVar24 = uStack_928;
      pauVar14 = pauStack_ac0;
      pauVar31 = pauStack_5c8;
      pauVar37 = pauStack_4d8;
      pauVar27 = pauStack_850;
      uVar26 = uStack_930;
      pauStack_940 = pauVar35;
      pauStack_5d0 = pauVar13;
    }
  }
  else {
    uStack_5b0 = 0;
    puVar23 = &DAT_0194e220;
  }
  pauVar37 = pauVar37 + 1;
  pauVar27 = (undefined1 (*) [16])((long)pauVar27[-1] + 0xf);
  pauVar13 = pauStack_7f8;
  goto LAB_017a7480;
LAB_017a7df0:
  pauStack_7f0 = auVar44._8_8_;
  pauStack_ab8 = auVar44._0_8_;
  auVar47 = auVar44;
  if (pauStack_ab8 != (undefined1 (*) [16])0x0) {
    *(undefined1 (**) [16])((long)pauVar29[1] + 8) = pauStack_ab8;
    *(undefined1 (**) [16])pauVar29[2] = pauVar25;
    if (DAT_02e5e450 != 0) {
      uVar12 = *(undefined8 *)pauVar29[1];
      auVar47 = runtime_gcWriteBarrier2();
      auVar44._8_8_ = pauStack_7f0;
      auVar44._0_8_ = pauStack_ab8;
      *(long *)*pauVar35 = auVar47._8_8_;
      *(undefined8 *)((long)*pauVar35 + 8) = uVar12;
    }
    pauStack_7f0 = auVar44._8_8_;
    pauStack_ab8 = auVar44._0_8_;
    *(long *)pauVar29[1] = auVar47._8_8_;
    if (*(long *)((long)*pauVar29 + 8) == 0) {
      *(undefined8 *)((long)*pauVar29 + 8) = 1;
      if (DAT_02e5e450 != 0) {
        uVar12 = *(undefined8 *)*pauVar29;
        auVar47 = runtime_gcWriteBarrier1();
        auVar44._8_8_ = pauStack_7f0;
        auVar44._0_8_ = pauStack_ab8;
        *(undefined8 *)*pauVar35 = uVar12;
      }
      *(undefined **)*pauVar29 = &DAT_01f34ef0;
    }
  }
  pauVar31 = pauStack_978;
  pauStack_7f0 = auVar44._8_8_;
  pauStack_ab8 = auVar44._0_8_;
  pauVar13 = (undefined1 (*) [16])((long)*pauStack_978 + 1);
  pauVar27 = pauStack_5f0;
  pauVar37 = pauStack_970;
  if (pauStack_970 < pauVar13) {
    pauVar27 = (undefined1 (*) [16])runtime_growslice(1,&DAT_01a92fc0);
    auVar47._8_8_ = pauStack_7f0;
    auVar47._0_8_ = pauStack_ab8;
    pauVar29 = pauStack_590;
    auVar44 = auVar47;
  }
  pauStack_7f0 = auVar44._8_8_;
  pauStack_ab8 = auVar44._0_8_;
  lVar21 = (long)pauVar31 * 0x10;
  if (DAT_02e5e450 != 0) {
    uVar12 = *(undefined8 *)pauVar27[(long)pauVar31];
    uVar28 = *(undefined8 *)((long)pauVar27[(long)pauVar31] + 8);
    auVar47 = runtime_gcWriteBarrier3();
    auVar44._8_8_ = pauStack_7f0;
    auVar44._0_8_ = pauStack_ab8;
    *(undefined8 *)*pauVar35 = uVar12;
    *(undefined1 (**) [16])((long)*pauVar35 + 8) = pauVar29;
    *(undefined8 *)pauVar35[1] = uVar28;
  }
  *(undefined8 *)((long)*pauVar27 + lVar21) = 0;
  *(undefined1 (**) [16])((long)*pauVar27 + lVar21 + 8) = pauVar29;
  if (auVar47._0_8_ == 0) {
    pauStack_940 = (undefined1 (*) [16])0x0;
    pauVar14 = (undefined1 (*) [16])0x0;
  }
  else {
    pauVar31 = (undefined1 (*) [16])0x0;
    pauVar14 = (undefined1 (*) [16])0x0;
    pauStack_940 = (undefined1 (*) [16])0x0;
    pauStack_8b0 = pauVar37;
    pauStack_8a8 = pauVar13;
    pauStack_548 = pauVar27;
    while( true ) {
      pauStack_7f0 = auVar44._8_8_;
      pauStack_ab8 = auVar44._0_8_;
      pauVar29 = auVar47._8_8_;
      if ((long)auVar47._0_8_ < 1) break;
      puVar11 = *(undefined8 **)(*pauVar29 + 8);
      bVar39 = *(undefined **)*pauVar29 == &DAT_01ad55a0;
      pauStack_f0 = in_XMM15_Qa;
      pauStack_e8 = in_XMM15_Qb;
      pauStack_e0 = in_XMM15_Qa;
      uStack_d8 = (undefined **)in_XMM15_Qb;
      uStack_d0 = in_XMM15_Qa;
      uStack_c8 = in_XMM15_Qb;
      if (bVar39) {
        pauStack_f0 = (undefined1 (*) [16])*puVar11;
        pauStack_e8 = (undefined1 (*) [16])puVar11[1];
        pauStack_e0 = (undefined1 (*) [16])puVar11[2];
        uStack_d8 = (undefined **)puVar11[3];
        uStack_d0 = (undefined1 (*) [16])puVar11[4];
        uStack_c8 = (undefined1 (*) [16])puVar11[5];
      }
      pauStack_48 = pauStack_f0;
      pauStack_40 = pauStack_e8;
      pauStack_38 = pauStack_e0;
      pauStack_30 = (undefined1 (*) [16])uStack_d8;
      pauStack_28 = uStack_d0;
      pauStack_20 = uStack_c8;
      pauStack_628 = pauStack_f0;
      pauStack_620 = pauStack_e8;
      pauStack_618 = pauStack_e0;
      pauStack_610 = (undefined1 (*) [16])uStack_d8;
      uStack_608 = (undefined4)uStack_d0;
      uStack_604 = uStack_d0._4_4_;
      uStack_600 = (undefined4)uStack_c8;
      uStack_5fc = uStack_c8._4_4_;
      pauVar38 = pauStack_940;
      if (bVar39) {
        pauStack_938 = pauVar31;
        pauStack_850 = auVar47._0_8_;
        pauStack_5d0 = pauVar14;
        pauStack_4d8 = pauVar29;
        pauStack_f0 = (undefined1 (*) [16])runtime_newobject();
        *(undefined8 *)((long)*pauStack_f0 + 8) = 0x19;
        pauVar38 = (undefined1 (*) [16])((long)*pauStack_940 + 1);
        *(undefined **)*pauStack_f0 = &DAT_01c5fbc8;
        pauStack_e8 = (undefined1 (*) [16])0x1;
        pauStack_e0 = (undefined1 (*) [16])0x1;
        uStack_d8 = (undefined **)&DAT_01c3dd13;
        uStack_d0 = (undefined1 (*) [16])0x7;
        uStack_c8 = (undefined1 (*) [16])CONCAT44(uStack_604,uStack_608);
        uStack_c0 = CONCAT44(uStack_5fc,uStack_600);
        pauVar14 = pauStack_5d0;
        pauVar31 = pauStack_938;
        if (pauStack_938 < pauVar38) {
          pauVar14 = (undefined1 (*) [16])runtime_growslice(1,&DAT_01ad5660);
        }
        pauVar37 = (undefined1 (*) [16])((long)pauVar38 * 0x38);
        if (DAT_02e5e450 != 0) {
          pauStack_8c0 = pauVar31;
          pauStack_8b8 = pauVar38;
          pauStack_860 = (undefined1 (*) [16])((long)pauVar38 * 0x38);
          pauStack_550 = pauVar14;
          runtime_wbMove();
          pauVar14 = pauStack_550;
          pauVar31 = pauStack_8c0;
          pauVar37 = pauStack_860;
          pauVar38 = pauStack_8b8;
        }
        auVar44._8_8_ = pauStack_7f0;
        auVar44._0_8_ = pauStack_ab8;
        auVar47._8_8_ = pauStack_4d8;
        auVar47._0_8_ = pauStack_850;
        puVar18 = *pauVar14;
        *(undefined1 (**) [16])((long)((long)pauVar37[-4] + 8) + (long)pauVar14) = pauStack_f0;
        *(undefined1 (**) [16])((long)pauVar37[-3] + (long)*pauVar14) = pauStack_e8;
        *(undefined1 (**) [16])((long)pauVar37[-3] + (long)(*pauVar14 + 8)) = pauStack_e0;
        *(undefined ***)((long)pauVar37[-2] + (long)puVar18) = uStack_d8;
        *(undefined1 (**) [16])((long)pauVar37[-2] + (long)(puVar18 + 8)) = uStack_d0;
        *(undefined4 *)((long)pauVar37[-1] + (long)puVar18) = (undefined4)uStack_c8;
        *(undefined4 *)((long)pauVar37[-1] + (long)(puVar18 + 4)) = uStack_c8._4_4_;
        *(undefined4 *)((long)pauVar37[-1] + (long)(puVar18 + 8)) = (undefined4)uStack_c0;
        *(undefined4 *)((long)pauVar37[-1] + (long)(puVar18 + 0xc)) = uStack_c0._4_4_;
        pauVar13 = pauStack_8a8;
        pauVar27 = pauStack_548;
        pauVar37 = pauStack_8b0;
      }
      lVar21 = auVar47._0_8_;
      auVar47._8_8_ = auVar47._8_8_ + 0x10;
      auVar47._0_8_ = lVar21 + -1;
      pauStack_940 = pauVar38;
    }
  }
  pauVar31 = (undefined1 (*) [16])0x0;
  uVar24 = 0;
  uVar26 = 0;
  pauStack_5c0 = (undefined1 (*) [16])&DAT_01c3ffa7;
  pauStack_920 = (undefined1 (*) [16])0x8;
  pauStack_5d0 = pauVar14;
  pauStack_978 = pauVar13;
  pauStack_5f0 = pauVar27;
  goto LAB_017a6768;
code_r0x017a8a54:
  pauVar35 = (undefined1 (*) [16])0x2;
  uVar12 = runtime_concatstring5();
  auVar51._8_8_ = pauStack_588;
  auVar51._0_8_ = uVar12;
  *(undefined **)((long)*pauStack_588 + 8) = &DAT_01c4414d;
  if (DAT_02e5e450 != 0) {
    uVar12 = *(undefined8 *)*pauStack_588;
    auVar51 = runtime_gcWriteBarrier2();
    *(long *)*pauVar35 = auVar51._0_8_;
    *(undefined8 *)((long)*pauVar35 + 8) = uVar12;
  }
  pauVar31 = auVar51._8_8_;
  auVar50._8_8_ = uStack_7e8;
  auVar50._0_8_ = uStack_ab0;
  *(long *)*pauVar31 = auVar51._0_8_;
  pauVar27 = pauStack_aa0;
LAB_017a8b2b:
  uVar12 = auVar50._8_8_;
  if (auVar50._0_8_ != 0) {
    *(long *)((long)pauVar31[1] + 8) = auVar50._0_8_;
    *(undefined1 (**) [16])pauVar31[2] = pauVar27;
    if (DAT_02e5e450 != 0) {
      uVar12 = *(undefined8 *)pauVar31[1];
      runtime_gcWriteBarrier2();
      *(undefined8 *)*pauVar35 = extraout_RDX;
      *(undefined8 *)((long)*pauVar35 + 8) = uVar12;
      uVar12 = extraout_RDX;
    }
    *(undefined8 *)pauVar31[1] = uVar12;
    if (*(long *)((long)*pauVar31 + 8) == 0) {
      *(undefined8 *)((long)*pauVar31 + 8) = 1;
      if (DAT_02e5e450 != 0) {
        runtime_gcWriteBarrier1();
        *(undefined8 *)*pauVar35 = extraout_RDX_00;
      }
      *(undefined **)*pauVar31 = &DAT_01f34ef0;
    }
  }
  if (DAT_02e5d6d9 != '\0') {
    lVar21 = *(long *)((long)*pauVar31 + 8);
    lVar30 = *(long *)*pauVar31;
    lVar16 = lVar30;
    if (8000 < lVar21) {
      lVar16 = runtime_concatstring2(&DAT_01c80308,0x2b,lVar21,8000);
      pauVar31 = pauStack_588;
      lVar21 = lVar30;
    }
    *(long *)((long)*pauVar31 + 8) = lVar21;
    if (DAT_02e5e450 != 0) {
      runtime_gcWriteBarrier2();
      *(long *)*pauVar35 = lVar16;
      *(undefined8 *)((long)*pauVar35 + 8) = extraout_RDX_01;
    }
    *(long *)*pauVar31 = lVar16;
  }
  pauVar37 = pauStack_978;
  pauVar27 = (undefined1 (*) [16])((long)*pauStack_978 + 1);
  pauVar13 = pauStack_5f0;
  pauVar14 = pauStack_970;
  if (pauStack_970 < pauVar27) {
    pauVar13 = (undefined1 (*) [16])runtime_growslice(1,&DAT_01a92fc0);
    pauVar31 = pauStack_588;
  }
  auVar53._8_8_ = pauVar14;
  auVar53._0_8_ = pauVar13;
  lVar21 = (long)pauVar37 * 0x10;
  if (DAT_02e5e450 != 0) {
    uVar12 = *(undefined8 *)pauVar13[(long)pauVar37];
    uVar28 = *(undefined8 *)((long)pauVar13[(long)pauVar37] + 8);
    auVar53 = runtime_gcWriteBarrier3();
    *(undefined8 *)*pauVar35 = uVar12;
    *(undefined1 (**) [16])((long)*pauVar35 + 8) = pauVar31;
    *(undefined8 *)pauVar35[1] = uVar28;
  }
  *(undefined8 *)(auVar53._0_8_ + lVar21) = 0;
  *(undefined1 (**) [16])(auVar53._0_8_ + lVar21 + 8) = pauVar31;
  pauVar29 = pauStack_ac8;
  puVar11 = puStack_668;
  pauVar14 = pauStack_ac0;
  pauVar13 = pauStack_7f8;
  pauVar31 = pauStack_9f0;
LAB_017a61c7:
  pauVar37 = (undefined1 (*) [16])(*pauStack_988 + 1);
  unaff_R13 = pauVar31;
  goto LAB_017a61cd;
LAB_017a7c75:
  pauStack_5c0 = pauStack_748;
  pauStack_920 = pauStack_740;
  pauVar37 = pauStack_970;
  if ((undefined1 (*) [16])-(long)pauStack_748 < pauStack_740) {
    if (pauStack_748 != (undefined1 (*) [16])0x0) {
      runtime_panicunsafestringlen(pauVar14);
      auVar53._8_8_ = pauStack_970;
      auVar53._0_8_ = puVar11;
    }
    pauStack_970 = auVar53._8_8_;
    pauVar35 = auVar53._0_8_;
    runtime_panicunsafestringnilptr();
LAB_017a7cc5:
    pauVar25 = (undefined1 (*) [16])&DAT_01f393c0;
    auVar44 = runtime_gopanic();
LAB_017a7cd4:
    do {
      pauStack_7f0 = auVar44._8_8_;
      pauStack_ab8 = auVar44._0_8_;
      if (pauStack_790 == (undefined1 (*) [16])0x0) goto LAB_017a7df0;
      pauVar14 = *(undefined1 (**) [16])((long)*pauVar29 + 8);
      pauVar38 = pauStack_790;
      pauVar37 = pauStack_798;
      pauStack_aa8 = pauVar25;
      if (pauVar14 == (undefined1 (*) [16])0x0) {
        if (pauStack_790 <= (undefined1 (*) [16])-(long)pauStack_798) {
          uVar12 = runtime_concatstring3();
          auVar46._8_8_ = pauStack_590;
          auVar46._0_8_ = uVar12;
          *(undefined **)((long)*pauStack_590 + 8) = &DAT_01c4414d;
          if (DAT_02e5e450 != 0) {
            uVar12 = *(undefined8 *)*pauStack_590;
            auVar46 = runtime_gcWriteBarrier2();
            *(long *)*pauVar35 = auVar46._0_8_;
            *(undefined8 *)((long)*pauVar35 + 8) = uVar12;
          }
          pauVar29 = auVar46._8_8_;
          auVar44._8_8_ = pauStack_7f0;
          auVar44._0_8_ = pauStack_ab8;
          *(long *)*pauVar29 = auVar46._0_8_;
          pauVar25 = pauStack_aa8;
          goto LAB_017a7df0;
        }
        if (pauStack_798 != (undefined1 (*) [16])0x0) {
          runtime_panicunsafestringlen();
          auVar44._8_8_ = pauStack_7f0;
          auVar44._0_8_ = pauStack_ab8;
        }
        pauStack_7f0 = auVar44._8_8_;
        pauStack_ab8 = auVar44._0_8_;
        runtime_panicunsafestringnilptr();
        auVar44._8_8_ = pauStack_7f0;
        auVar44._0_8_ = pauStack_ab8;
      }
      else if (pauStack_790 <= (undefined1 (*) [16])-(long)pauStack_798) {
        pauVar35 = (undefined1 (*) [16])0x2;
        uVar12 = runtime_concatstring5();
        auVar45._8_8_ = pauStack_590;
        auVar45._0_8_ = uVar12;
        *(undefined **)((long)*pauStack_590 + 8) = &DAT_01c4414d;
        if (DAT_02e5e450 != 0) {
          uVar12 = *(undefined8 *)*pauStack_590;
          auVar45 = runtime_gcWriteBarrier2();
          *(long *)*pauVar35 = auVar45._0_8_;
          *(undefined8 *)((long)*pauVar35 + 8) = uVar12;
        }
        pauVar29 = auVar45._8_8_;
        auVar44._8_8_ = pauStack_7f0;
        auVar44._0_8_ = pauStack_ab8;
        *(long *)*pauVar29 = auVar45._0_8_;
        pauVar25 = pauStack_aa8;
        goto LAB_017a7df0;
      }
      pauStack_7f0 = auVar44._8_8_;
      pauStack_ab8 = auVar44._0_8_;
      if (pauVar37 != (undefined1 (*) [16])0x0) {
        runtime_panicunsafestringlen();
        auVar44._8_8_ = pauStack_7f0;
        auVar44._0_8_ = pauStack_ab8;
      }
      pauStack_7f0 = auVar44._8_8_;
      pauStack_ab8 = auVar44._0_8_;
      auVar48 = runtime_panicunsafestringnilptr();
      pauVar15 = pauVar29;
      while( true ) {
        pauVar27 = auVar48._0_8_;
        pauVar37 = (undefined1 (*) [16])(auVar48._8_8_ + 0x10);
        pauVar14 = (undefined1 (*) [16])((long)pauVar14[-1] + 0xf);
LAB_017a8240:
        unaff_R13 = pauStack_720;
        pauVar29 = pauStack_728;
        auVar48._8_8_ = pauVar37;
        auVar48._0_8_ = pauVar27;
        if ((long)pauVar14 < 1) break;
        if (*(undefined **)*pauVar37 == &DAT_01a233a0) {
          uStack_5a8 = *(undefined8 *)(*pauVar37 + 8);
          pauStack_ab8 = pauVar38;
          pauStack_aa8 = pauVar15;
          pauStack_850 = pauVar14;
          pauStack_7f0 = pauVar25;
          pauStack_4d8 = pauVar37;
          puVar11 = (undefined8 *)runtime_mapaccess1_faststr(4);
          auVar2._8_8_ = pauStack_4d8;
          auVar2._0_8_ = pauStack_590;
          auVar48._8_8_ = pauStack_4d8;
          auVar48._0_8_ = pauStack_590;
          auVar1._8_8_ = pauStack_4d8;
          auVar1._0_8_ = pauStack_590;
          if ((undefined *)*puVar11 == &DAT_0194e220) {
            unaff_R13 = *(undefined1 (**) [16])puVar11[1];
            lVar21 = ((undefined8 *)puVar11[1])[1];
          }
          else {
            lVar21 = 0;
            unaff_R13 = (undefined1 (*) [16])0x0;
          }
          pauVar38 = pauStack_ab8;
          pauVar15 = pauStack_aa8;
          pauVar25 = pauStack_7f0;
          pauVar14 = pauStack_850;
          if (lVar21 == 4) {
            auVar48 = auVar1;
            if (*(int *)*unaff_R13 == 0x74786574) {
              puVar11 = (undefined8 *)runtime_mapaccess1_faststr(4);
              auVar48._8_8_ = pauStack_4d8;
              auVar48._0_8_ = pauStack_590;
              pauVar15 = pauStack_aa8;
              pauVar25 = pauStack_7f0;
              pauVar38 = pauStack_ab8;
              pauVar14 = pauStack_850;
              if ((undefined *)*puVar11 == &DAT_0194e220) {
                unaff_R13 = *(undefined1 (**) [16])puVar11[1];
                lVar21 = ((undefined8 *)puVar11[1])[1];
                if (pauStack_730 == (undefined1 (*) [16])0x0) {
                  pauStack_730 = (undefined1 (*) [16])&pauStack_730;
                }
                else {
                  pauVar31 = (undefined1 (*) [16])&pauStack_730;
                  pauVar13 = pauStack_730;
                  if (pauStack_730 != pauVar31) goto LAB_017a89ed;
                }
                pauVar31 = (undefined1 (*) [16])&pauStack_730;
                pauVar37 = (undefined1 (*) [16])((long)*pauStack_720 + lVar21);
                pauVar27 = pauStack_728;
                pauVar14 = pauStack_718;
                pauVar13 = pauStack_720;
                if (pauStack_718 < pauVar37) {
                  pauStack_860 = pauStack_720;
                  lStack_a38 = lVar21;
                  pauStack_6c0 = unaff_R13;
                  pauVar27 = (undefined1 (*) [16])runtime_growslice(lVar21,&DAT_0194e2a0);
                  pauVar13 = pauStack_860;
                }
                pauStack_868 = pauVar14;
                pauStack_860 = pauVar37;
                pauStack_4e8 = pauVar27;
                runtime_memmove();
                auVar48._8_8_ = pauStack_4d8;
                auVar48._0_8_ = pauStack_590;
                pauStack_720 = pauStack_860;
                pauStack_718 = pauStack_868;
                pauStack_728 = pauStack_4e8;
                pauVar15 = pauStack_aa8;
                pauVar25 = pauStack_7f0;
                pauVar38 = pauStack_ab8;
                pauVar14 = pauStack_850;
              }
            }
          }
          else if (lVar21 == 8) {
            if (*(long *)*unaff_R13 == 0x676e696b6e696874) {
              puVar11 = (undefined8 *)runtime_mapaccess1_faststr(8);
              if ((undefined *)*puVar11 == &DAT_0194e220) {
                pauVar31 = *(undefined1 (**) [16])puVar11[1];
                pauVar13 = (undefined1 (*) [16])((undefined8 *)puVar11[1])[1];
                if (pauStack_7a0 == (undefined1 (*) [16])0x0) {
                  pauStack_7a0 = (undefined1 (*) [16])&pauStack_7a0;
                }
                else {
                  pauVar35 = (undefined1 (*) [16])&pauStack_7a0;
                  if (pauStack_7a0 != pauVar35) goto LAB_017a89de;
                }
                pauVar35 = (undefined1 (*) [16])&pauStack_7a0;
                pauVar37 = (undefined1 (*) [16])((long)*pauStack_790 + (long)*pauVar13);
                pauVar27 = pauStack_798;
                pauVar14 = pauStack_788;
                if (pauStack_788 < pauVar37) {
                  pauStack_860 = pauStack_790;
                  pauStack_a58 = pauVar13;
                  pauStack_760 = pauVar31;
                  pauVar27 = (undefined1 (*) [16])runtime_growslice(pauVar13,&DAT_0194e2a0);
                  pauVar13 = pauStack_a58;
                  pauVar31 = pauStack_760;
                }
                pauStack_868 = pauVar37;
                pauStack_860 = pauVar14;
                pauStack_4e8 = pauVar27;
                runtime_memmove();
                auVar48._8_8_ = pauStack_4d8;
                auVar48._0_8_ = pauStack_590;
                pauStack_790 = pauStack_868;
                pauStack_788 = pauStack_860;
                pauStack_798 = pauStack_4e8;
                pauVar15 = pauStack_aa8;
                pauVar25 = pauStack_7f0;
                pauVar38 = pauStack_ab8;
                pauVar14 = pauStack_850;
              }
              else {
                pauVar13 = (undefined1 (*) [16])0x0;
                pauVar31 = (undefined1 (*) [16])0x0;
                puVar11 = (undefined8 *)runtime_mapaccess1_faststr(4);
                auVar48._8_8_ = pauStack_4d8;
                auVar48._0_8_ = pauStack_590;
                pauVar15 = pauStack_aa8;
                pauVar25 = pauStack_7f0;
                pauVar38 = pauStack_ab8;
                pauVar14 = pauStack_850;
                if ((undefined *)*puVar11 == &DAT_0194e220) {
                  unaff_R13 = *(undefined1 (**) [16])puVar11[1];
                  lVar21 = ((undefined8 *)puVar11[1])[1];
                  if (pauStack_7a0 == (undefined1 (*) [16])0x0) {
                    pauStack_7a0 = (undefined1 (*) [16])&pauStack_7a0;
                  }
                  else {
                    pauVar31 = (undefined1 (*) [16])&pauStack_7a0;
                    pauVar13 = pauStack_7a0;
                    if (pauStack_7a0 != pauVar31) goto LAB_017a89cf;
                  }
                  pauVar31 = (undefined1 (*) [16])&pauStack_7a0;
                  pauVar37 = (undefined1 (*) [16])((long)*pauStack_790 + lVar21);
                  pauVar27 = pauStack_798;
                  pauVar14 = pauStack_788;
                  pauVar13 = pauStack_790;
                  if (pauStack_788 < pauVar37) {
                    pauStack_860 = pauStack_790;
                    lStack_a40 = lVar21;
                    pauStack_6c8 = unaff_R13;
                    pauVar27 = (undefined1 (*) [16])runtime_growslice(lVar21,&DAT_0194e2a0);
                    pauVar13 = pauStack_860;
                  }
                  pauStack_868 = pauVar14;
                  pauStack_860 = pauVar37;
                  pauStack_4e8 = pauVar27;
                  runtime_memmove();
                  auVar48._8_8_ = pauStack_4d8;
                  auVar48._0_8_ = pauStack_590;
                  pauStack_790 = pauStack_860;
                  pauStack_788 = pauStack_868;
                  pauStack_798 = pauStack_4e8;
                  pauVar15 = pauStack_aa8;
                  pauVar25 = pauStack_7f0;
                  pauVar38 = pauStack_ab8;
                  pauVar14 = pauStack_850;
                }
              }
            }
            else {
              auVar48 = auVar2;
              if (*(long *)*unaff_R13 == 0x6573755f6c6f6f74) {
                puVar11 = (undefined8 *)runtime_mapaccess1_faststr(2);
                if ((undefined *)*puVar11 == &DAT_0194e220) {
                  pauStack_7d0 = *(undefined1 (**) [16])puVar11[1];
                  pauStack_a88 = (undefined1 (*) [16])((undefined8 *)puVar11[1])[1];
                }
                else {
                  pauStack_a88 = (undefined1 (*) [16])0x0;
                  pauStack_7d0 = (undefined1 (*) [16])0x0;
                }
                puVar11 = (undefined8 *)runtime_mapaccess1_faststr(4,pauStack_a88,&DAT_0194e220,&DAT_01c39796);
                if ((undefined *)*puVar11 == &DAT_0194e220) {
                  pauStack_660 = *(undefined1 (**) [16])puVar11[1];
                  pauStack_9e0 = (undefined1 (*) [16])((undefined8 *)puVar11[1])[1];
                }
                else {
                  pauStack_9e0 = (undefined1 (*) [16])0x0;
                  pauStack_660 = (undefined1 (*) [16])0x0;
                }
                puVar11 = (undefined8 *)runtime_mapaccess1_faststr(5,pauStack_9e0,&DAT_0194e220,&DAT_01c3a5e4);
                pauStack_f0 = (undefined1 (*) [16])*puVar11;
                pauStack_e8 = (undefined1 (*) [16])puVar11[1];
                pauVar13 = (undefined1 (*) [16])((long)*pauStack_ab8 + 1);
                pauStack_e0 = pauStack_660;
                uStack_d8 = (undefined **)pauStack_9e0;
                uStack_d0 = pauStack_7d0;
                uStack_c8 = pauStack_a88;
                pauStack_38 = pauStack_660;
                pauStack_30 = pauStack_9e0;
                pauStack_28 = pauStack_7d0;
                pauStack_20 = pauStack_a88;
                pauStack_860 = pauVar13;
                pauStack_48 = pauStack_f0;
                pauStack_40 = pauStack_e8;
                uVar12 = runtime_convT();
                pauVar38 = pauStack_860;
                pauVar15 = pauStack_aa8;
                pauVar37 = pauStack_7f0;
                if (pauStack_aa8 < pauStack_860) {
                  uStack_4e0 = uVar12;
                  pauVar37 = (undefined1 (*) [16])runtime_growslice(1,&DAT_019b39a0);
                  uVar12 = uStack_4e0;
                }
                auVar49._8_8_ = pauVar37;
                auVar49._0_8_ = uVar12;
                puVar18 = (undefined1 *)((long)pauVar38[-1] + 0xf);
                *(undefined **)pauVar37[(long)puVar18] = &DAT_01ad55a0;
                if (DAT_02e5e450 != 0) {
                  uVar12 = *(undefined8 *)((long)pauVar37[(long)puVar18] + 8);
                  auVar49 = runtime_gcWriteBarrier2();
                  *(long *)*pauVar35 = auVar49._0_8_;
                  *(undefined8 *)((long)*pauVar35 + 8) = uVar12;
                }
                auVar48._8_8_ = pauStack_4d8;
                auVar48._0_8_ = pauStack_590;
                *(long *)((long)auVar49._8_8_[(long)puVar18] + 8) = auVar49._0_8_;
                pauVar25 = auVar49._8_8_;
                pauVar14 = pauStack_850;
              }
            }
          }
        }
      }
      if ((undefined1 (*) [16])-(long)pauStack_728 < pauStack_720) {
        if (pauStack_728 != (undefined1 (*) [16])0x0) {
          runtime_panicunsafestringlen();
        }
        runtime_panicunsafestringnilptr();
LAB_017a89cf:
        runtime_gopanic();
LAB_017a89de:
        runtime_gopanic();
LAB_017a89ed:
        pauVar27 = (undefined1 (*) [16])&DAT_01f393c0;
        runtime_gopanic();
        auVar53._8_8_ = pauStack_970;
        auVar53._0_8_ = pauVar35;
LAB_017a89fc:
        pauStack_970 = auVar53._8_8_;
        pauVar35 = auVar53._0_8_;
        auVar50 = runtime_panicIndex();
        goto LAB_017a8a07;
      }
      *(undefined1 (**) [16])((long)*pauVar27 + 8) = pauStack_720;
      if (DAT_02e5e450 != 0) {
        auVar40 = runtime_gcWriteBarrier2();
        pauVar27 = auVar40._0_8_;
        *(undefined1 (**) [16])*pauVar35 = pauVar29;
        *(long *)((long)*pauVar35 + 8) = auVar40._8_8_;
      }
      auVar44._8_8_ = pauVar25;
      auVar44._0_8_ = pauVar38;
      *(undefined1 (**) [16])*pauVar27 = pauVar29;
      pauVar29 = pauStack_590;
      pauVar25 = pauVar15;
    } while( true );
  }
LAB_017a6768:
  pauStack_7f0 = auVar44._8_8_;
  pauStack_ab8 = auVar44._0_8_;
  if (pauStack_920 == (undefined1 (*) [16])0x0) {
    if (pauStack_940 == (undefined1 (*) [16])0x0) {
      pauStack_920 = (undefined1 (*) [16])0x8;
      pauStack_5c0 = (undefined1 (*) [16])&DAT_01c3ffa7;
    }
    else {
      pauStack_920 = (undefined1 (*) [16])0x16;
      pauStack_5c0 = (undefined1 (*) [16])&DAT_01c5a6df;
    }
  }
  pauStack_970 = pauVar37;
  uStack_930 = uVar26;
  uStack_928 = uVar24;
  pauStack_5c8 = pauVar31;
  puVar11 = (undefined8 *)runtime_newobject();
  puVar11[1] = pauStack_920;
  if (DAT_02e5e450 != 0) {
    puVar11 = (undefined8 *)runtime_gcWriteBarrier2();
    *(undefined1 (**) [16])*pauVar37 = pauStack_5c0;
    *(undefined8 *)((long)*pauVar37 + 8) = uStack_648;
  }
  *puVar11 = pauStack_5c0;
  puVar11[6] = lStack_9c8;
  puVar11[5] = uStack_648;
  puVar11[8] = 9;
  puVar11[7] = &DAT_01c41eb5;
  puStack_810 = puVar11;
  if (uStack_930 != 0) {
    puVar11[3] = uStack_930;
    puVar11[4] = uStack_928;
    if (DAT_02e5e450 != 0) {
      puVar11 = (undefined8 *)runtime_gcWriteBarrier1();
      *(undefined1 (**) [16])*pauVar37 = pauStack_5c8;
    }
    puVar11[2] = pauStack_5c8;
  }
  plStack_818 = (long *)runtime_makemap_small();
  if (((pauStack_978 != (undefined1 (*) [16])0x0) &&
      (puVar11 = *(undefined8 **)(pauStack_5f0[(long)(pauStack_978[-1] + 0xf)] + 8),
      puVar11 != (undefined8 *)0x0)) && (puVar11[3] != 0)) {
    puStack_540 = puVar11;
    FUN_00488ccb(auStack_3d0);
    uStack_3d8 = 0x8080808080808080;
    puStack_300 = &uStack_3d8;
    uStack_308 = runtime_rand();
    pauVar31 = (undefined1 (*) [16])puStack_540[2];
    for (pauVar13 = (undefined1 (*) [16])puStack_540[3]; 0 < (long)pauVar13;
        pauVar13 = (undefined1 (*) [16])((long)pauVar13[-1] + 0xf)) {
      puVar11 = *(undefined8 **)(*pauVar31 + 8);
      bVar39 = *(undefined **)*pauVar31 == &DAT_01ad55a0;
      pauStack_f0 = in_XMM15_Qa;
      pauStack_e8 = in_XMM15_Qb;
      pauStack_e0 = in_XMM15_Qa;
      uStack_d8 = (undefined **)in_XMM15_Qb;
      uStack_d0 = in_XMM15_Qa;
      uStack_c8 = in_XMM15_Qb;
      if (bVar39) {
        pauStack_f0 = (undefined1 (*) [16])*puVar11;
        pauStack_e8 = (undefined1 (*) [16])puVar11[1];
        pauStack_e0 = (undefined1 (*) [16])puVar11[2];
        uStack_d8 = (undefined **)puVar11[3];
        uStack_d0 = (undefined1 (*) [16])puVar11[4];
        uStack_c8 = (undefined1 (*) [16])puVar11[5];
      }
      pauStack_48 = pauStack_f0;
      pauStack_40 = pauStack_e8;
      pauStack_38 = pauStack_e0;
      pauStack_30 = (undefined1 (*) [16])uStack_d8;
      pauStack_28 = uStack_d0;
      pauStack_20 = uStack_c8;
      pauStack_628 = pauStack_f0;
      pauStack_620 = pauStack_e8;
      pauStack_618 = pauStack_e0;
      pauStack_610 = (undefined1 (*) [16])uStack_d8;
      uStack_608 = (undefined4)uStack_d0;
      uStack_604 = uStack_d0._4_4_;
      uStack_600 = (undefined4)uStack_c8;
      uStack_5fc = uStack_c8._4_4_;
      if (bVar39) {
        pauStack_850 = pauVar13;
        pauStack_4d8 = pauVar31;
        puVar18 = (undefined1 *)runtime_mapassign_faststr(uStack_c8,&DAT_01ad55a0,puVar11,uStack_d0);
        *puVar18 = 1;
        pauVar13 = pauStack_850;
        pauVar31 = pauStack_4d8;
      }
      pauVar31 = pauVar31 + 1;
    }
    FUN_00488ccb(auStack_4c8);
    uStack_4d0 = 0x8080808080808080;
    puStack_3f8 = &uStack_4d0;
    uStack_400 = runtime_rand();
    uStack_ad8 = 0;
    pauStack_808 = (undefined1 (*) [16])&DAT_02e5d6a0;
    uStack_ae8 = 0;
    pauVar31 = pauStack_5d0;
    pauVar13 = pauStack_940;
    while (0 < (long)pauVar13) {
      pauStack_f0 = *(undefined1 (**) [16])*pauVar31;
      pauStack_e8 = *(undefined1 (**) [16])(*pauVar31 + 8);
      pauStack_e0 = *(undefined1 (**) [16])pauVar31[1];
      uStack_d8 = *(undefined ***)(pauVar31[1] + 8);
      uStack_d0 = *(undefined1 (**) [16])pauVar31[2];
      uStack_c8 = *(undefined1 (**) [16])(pauVar31[2] + 8);
      uStack_c0 = *(undefined8 *)pauVar31[3];
      pauStack_850 = pauVar13;
      pauStack_4d8 = pauVar31;
      pcVar17 = (char *)runtime_mapaccess1_faststr(uStack_c0,uStack_ae8,pauStack_f0,uStack_c8);
      if ((*pcVar17 != '\0') && (pcVar17 = (char *)runtime_mapaccess1_faststr(uStack_c0), *pcVar17 == '\0')) {
        puVar18 = (undefined1 *)runtime_mapassign_faststr(uStack_c0);
        *puVar18 = 1;
        uVar24 = uStack_ae8 + 1;
        pauVar31 = pauStack_808;
        if (uStack_ad8 < uVar24) {
          pauVar31 = (undefined1 (*) [16])runtime_growslice(1,&DAT_01ad5660);
        }
        pauVar13 = (undefined1 (*) [16])(uVar24 * 0x38);
        uStack_ae8 = uVar24;
        pauStack_4f0 = pauVar31;
        if (DAT_02e5e450 != 0) {
          pauStack_860 = (undefined1 (*) [16])(uVar24 * 0x38);
          runtime_wbMove();
          pauVar13 = pauStack_860;
        }
        puVar19 = (undefined8 *)*pauStack_4f0;
        puVar11 = (undefined8 *)((long)pauVar13[-2] + (long)puVar19);
        *(undefined1 (**) [16])((long)((long)pauVar13[-4] + 8) + (long)pauStack_4f0) = pauStack_f0;
        *(undefined1 (**) [16])((long)pauVar13[-3] + (long)*pauStack_4f0) = pauStack_e8;
        *(undefined1 (**) [16])((long)pauVar13[-3] + (long)((long)*pauStack_4f0 + 8)) = pauStack_e0;
        *puVar11 = uStack_d8;
        *(undefined1 (**) [16])((long)pauVar13[-2] + (long)(puVar19 + 1)) = uStack_d0;
        *(undefined4 *)((long)pauVar13[-1] + (long)puVar19) = (undefined4)uStack_c8;
        *(undefined4 *)((long)pauVar13[-1] + (long)((long)puVar19 + 4)) = uStack_c8._4_4_;
        *(undefined4 *)((long)pauVar13[-1] + (long)(puVar19 + 1)) = (undefined4)uStack_c0;
        *(undefined4 *)((long)pauVar13[-1] + (long)((long)puVar19 + 0xc)) = uStack_c0._4_4_;
        runtime_mapdelete_faststr(uStack_c0,puVar11,pauVar13,uStack_c8);
        pauStack_808 = pauStack_4f0;
      }
      pauVar31 = (undefined1 (*) [16])(pauStack_4d8[3] + 8);
      pauVar13 = (undefined1 (*) [16])((long)pauStack_850[-1] + 0xf);
    }
    FUN_00488ceb(&uStack_c8);
    runtime_mapIterStart();
    pauVar31 = pauStack_808;
    while (puStack_a8 != (undefined8 *)0x0) {
      pauStack_7e0 = (undefined1 (*) [16])*puStack_a8;
      uStack_a98 = puStack_a8[1];
      pauStack_808 = pauVar31;
      pauStack_f0 = (undefined1 (*) [16])runtime_newobject();
      *(undefined8 *)((long)*pauStack_f0 + 8) = 0x19;
      uVar24 = uStack_ae8 + 1;
      *(undefined **)*pauStack_f0 = &DAT_01c5fbc8;
      pauStack_e8 = (undefined1 (*) [16])0x1;
      pauStack_e0 = (undefined1 (*) [16])0x1;
      uStack_d8 = (undefined **)&DAT_01c3dd13;
      uStack_d0 = (undefined1 (*) [16])0x7;
      uStack_c8 = pauStack_7e0;
      uStack_c0 = uStack_a98;
      pauVar31 = pauStack_808;
      if (uStack_ad8 < uVar24) {
        pauVar31 = (undefined1 (*) [16])runtime_growslice(1,&DAT_01ad5660);
      }
      pauVar13 = (undefined1 (*) [16])(uVar24 * 0x38);
      uStack_ae8 = uVar24;
      pauStack_4f0 = pauVar31;
      if (DAT_02e5e450 != 0) {
        pauStack_850 = (undefined1 (*) [16])(uVar24 * 0x38);
        runtime_wbMove();
        pauVar13 = pauStack_850;
      }
      puVar11 = (undefined8 *)*pauStack_4f0;
      *(undefined1 (**) [16])((long)((long)pauVar13[-4] + 8) + (long)pauStack_4f0) = pauStack_f0;
      *(undefined1 (**) [16])((long)pauVar13[-3] + (long)*pauStack_4f0) = pauStack_e8;
      *(undefined1 (**) [16])((long)pauVar13[-3] + (long)((long)*pauStack_4f0 + 8)) = pauStack_e0;
      *(undefined ***)((long)pauVar13[-2] + (long)puVar11) = uStack_d8;
      *(undefined1 (**) [16])((long)pauVar13[-2] + (long)(puVar11 + 1)) = uStack_d0;
      *(undefined4 *)((long)pauVar13[-1] + (long)puVar11) = (undefined4)uStack_c8;
      *(undefined4 *)((long)pauVar13[-1] + (long)((long)puVar11 + 4)) = uStack_c8._4_4_;
      *(undefined4 *)((long)pauVar13[-1] + (long)(puVar11 + 1)) = (undefined4)uStack_c0;
      *(undefined4 *)((long)pauVar13[-1] + (long)((long)puVar11 + 0xc)) = uStack_c0._4_4_;
      runtime_mapIterNext();
      pauVar31 = pauStack_4f0;
    }
    if (uStack_ae8 != 0) {
      pauStack_4d8 = (undefined1 (*) [16])runtime_convTslice();
      puVar11 = (undefined8 *)runtime_mapassign_faststr(0xb);
      *puVar11 = &DAT_0192c840;
      if (DAT_02e5e450 != 0) {
        auVar40 = runtime_gcWriteBarrier2();
        puVar11 = auVar40._0_8_;
        *(undefined1 (**) [16])*pauVar37 = pauStack_4d8;
        *(long *)((long)*pauVar37 + 8) = auVar40._8_8_;
      }
      puVar11[1] = pauStack_4d8;
    }
  }
  if (pauStack_ac8 != (undefined1 (*) [16])0x0) {
    pauStack_4d8 = (undefined1 (*) [16])runtime_convTslice();
    puVar11 = (undefined8 *)runtime_mapassign_faststr(5);
    *puVar11 = &DAT_0192c800;
    if (DAT_02e5e450 != 0) {
      auVar40 = runtime_gcWriteBarrier2();
      puVar11 = auVar40._0_8_;
      *(undefined1 (**) [16])*pauVar37 = pauStack_4d8;
      *(long *)((long)*pauVar37 + 8) = auVar40._8_8_;
    }
    puVar11[1] = pauStack_4d8;
  }
  auVar42._8_8_ = puStack_810;
  auVar42._0_8_ = plStack_818;
  if (plStack_818 == (long *)0x0) {
    lVar21 = 0;
  }
  else {
    lVar21 = *plStack_818;
  }
  puVar11 = puStack_810;
  if (0 < lVar21) {
    if (DAT_02e5e450 != 0) {
      uVar12 = puStack_810[9];
      auVar42 = runtime_gcWriteBarrier2();
      *(long *)*pauVar37 = auVar42._0_8_;
      *(undefined8 *)((long)*pauVar37 + 8) = uVar12;
    }
    auVar42._8_8_[9] = auVar42._0_8_;
    puVar11 = auVar42._8_8_;
  }
  if ((DAT_02e5d6d9 != '\0') && (100 < (long)pauStack_978)) {
    pauStack_970 = (undefined1 (*) [16])((long)pauStack_970 + (100 - (long)pauStack_978));
    pauVar31 = pauStack_978 + -7;
    pauStack_978 = (undefined1 (*) [16])0x64;
    for (pauStack_5f0 = (undefined1 (*) [16])
                        (*pauStack_5f0 +
                        (-(long)pauStack_970 >> 0x3f & (long)(*pauVar31 + 0xc) * 0x10));
        (pauStack_978 != (undefined1 (*) [16])0x0 && (*(long *)(*pauStack_5f0 + 8) != 0));
        pauStack_5f0 = (undefined1 (*) [16])
                       (*pauStack_5f0 + ((uint)(-(long)pauStack_970 >> 0x3f) & 0x10))) {
      pauStack_970 = (undefined1 (*) [16])((long)pauStack_970[-1] + 0xf);
      pauStack_978 = (undefined1 (*) [16])(pauStack_978[-1] + 0xf);
    }
  }
  bVar39 = pauStack_978 == (undefined1 (*) [16])0x0;
  if (!bVar39) {
    if (*(long *)*pauStack_5f0 == 0) {
      bVar39 = pauStack_978 == (undefined1 (*) [16])0x0;
    }
    else {
      lVar21 = *(long *)(*(long *)*pauStack_5f0 + 0x48);
      if (lVar21 == 0) {
        bVar39 = pauStack_978 == (undefined1 (*) [16])0x0;
      }
      else {
        runtime_mapdelete_faststr(0xb,lVar21,puVar11,&DAT_01c462f7);
        lVar21 = *(long *)*pauStack_5f0;
        if (*(long **)(lVar21 + 0x48) == (long *)0x0) {
          lVar30 = 0;
        }
        else {
          lVar30 = **(long **)(lVar21 + 0x48);
        }
        if (lVar30 == 0) {
          if (DAT_02e5e450 != 0) {
            uVar12 = *(undefined8 *)(lVar21 + 0x48);
            runtime_gcWriteBarrier1();
            *(undefined8 *)*pauVar37 = uVar12;
          }
          *(undefined8 *)(lVar21 + 0x48) = 0;
        }
        bVar39 = pauStack_978 == (undefined1 (*) [16])0x0;
        puVar11 = puStack_810;
      }
    }
  }
  pauVar31 = pauStack_970;
  if ((bVar39) && (pauVar13 = (undefined1 (*) [16])puVar11[9], pauVar13 != (undefined1 (*) [16])0x0)
     ) {
    runtime_mapdelete_faststr(0xb,pauVar13,puVar11,&DAT_01c462f7);
    if ((long *)puStack_810[9] == (long *)0x0) {
      lVar21 = 0;
    }
    else {
      lVar21 = *(long *)puStack_810[9];
    }
    pauVar31 = pauVar13;
    if (lVar21 == 0) {
      puVar11 = puStack_810;
      if (DAT_02e5e450 != 0) {
        auVar40 = runtime_gcWriteBarrier1();
        puVar11 = auVar40._8_8_;
        *(long *)*pauVar37 = auVar40._0_8_;
      }
      puVar11[9] = 0;
    }
  }
  pauStack_4e8 = (undefined1 (*) [16])github_com_google_uuid_NewString();
  pauStack_850 = pauVar31;
  lVar21 = runtime_newobject();
  *(undefined8 *)(lVar21 + 0x28) = 6;
  *(char **)(lVar21 + 0x20) =
       "MANUALsearchdeletecreatein_useactiveclosedoutputcallId[DONE]GEMINItierIdagent-</env>darwin24.0.015.6.1inputsimagesoffset0.70.0system/usagev2.9.7%s[%d]ServerConfigSERVERDOMAINMETHOD%s#%d,Logger<html><head><body><hr />/traceactiondomainmethod/[^/]+PATCH:TRACE:/indexUSAGE\n-/--%sOutput-07:00000000 Valuesysmontimersefenceselectscalar, not       unused objs\n next= jobs= goid sweep  B -> % util alloc free  span= prev= list=, i =  code= addr=], sp= m->p= p->m=SCHED  curg= ctxt: min=  max= bad ts(...)\n m=nil base hangupkilledallow"
  ;
  *(undefined1 (**) [16])(lVar21 + 0x38) = pauStack_850;
  if (DAT_02e5e450 != 0) {
    lVar21 = runtime_gcWriteBarrier2();
    *(undefined1 (**) [16])*pauVar37 = pauStack_4e8;
    *(undefined8 **)((long)*pauVar37 + 8) = puStack_810;
  }
  *(undefined1 (**) [16])(lVar21 + 0x30) = pauStack_4e8;
  *(undefined8 **)(lVar21 + 0x40) = puStack_810;
  if (*(long *)(lStack0000000000000018 + 0xa0) != 0) {
    uVar12 = *(undefined8 *)(lStack0000000000000018 + 0x98);
    *(long *)(lVar21 + 0x68) = *(long *)(lStack0000000000000018 + 0xa0);
    if (DAT_02e5e450 != 0) {
      lVar21 = runtime_gcWriteBarrier1();
      *(undefined8 *)*pauVar37 = uVar12;
    }
    *(undefined8 *)(lVar21 + 0x60) = uVar12;
  }
  if (pauStack_978 != (undefined1 (*) [16])0x0) {
    *(undefined1 (**) [16])(lVar21 + 0x50) = pauStack_978;
    *(undefined1 (**) [16])(lVar21 + 0x58) = pauStack_970;
    if (DAT_02e5e450 != 0) {
      uVar12 = *(undefined8 *)(lVar21 + 0x48);
      lVar21 = runtime_gcWriteBarrier2();
      *(undefined1 (**) [16])*pauVar37 = pauStack_5f0;
      *(undefined8 *)((long)*pauVar37 + 8) = uVar12;
    }
    *(undefined1 (**) [16])(lVar21 + 0x48) = pauStack_5f0;
  }
  return;
}




// === kiro.ChatCompletions @ 0x17a0a60 ===

ulong kiro_ChatCompletions(void)

{
  char cVar1;
  int in_EAX;
  long lVar2;
  ulong in_RCX;
  undefined8 extraout_RDX;
  undefined8 extraout_RDX_00;
  undefined8 extraout_RDX_01;
  undefined8 uVar3;
  ulong uVar4;
  byte bVar5;
  long in_stack_00000040;
  ulong uStack0000000000000048;
  undefined8 uStack0000000000000050;
  ulong in_stack_00000058;
  undefined8 in_stack_00000068;
  undefined8 in_stack_00000080;
  ulong uStack0000000000000088;
  long in_stack_000000a0;
  undefined8 uStack00000000000000a8;
  undefined8 in_stack_000000b0;
  undefined8 in_stack_000000b8;
  long in_stack_000000d0;
  
  uVar4 = (ulong)((long)in_EAX * (long)(int)in_RCX) >> 0x20;
code_r0x017a0a62:
  if ((long)uVar4 >> 10 != (long)in_RCX >> 0x3f) goto code_r0x017a09ba;
code_r0x017a061f:
  do {
    uStack0000000000000048 = in_stack_00000058;
    uStack0000000000000050 = in_stack_00000080;
    uStack00000000000000a8 = in_stack_000000b0;
    lVar2 = time_Time_Year();
    if (in_stack_00000040 < lVar2) {
      return uStack0000000000000048;
    }
    do {
      time_Time_Month();
      uVar3 = *(undefined8 *)(in_stack_000000d0 + 0x50);
      runtime_mapaccess2_fast64();
      in_stack_000000b0 = uStack00000000000000a8;
      if ((char)uVar3 != '\0') goto code_r0x017a086a;
      time_Time_AddDate(0,1,extraout_RDX,uStack00000000000000a8,0);
      time_Time_Year();
      in_stack_00000080 = time_Time_Month();
      in_stack_000000b0 = 1;
      in_stack_00000058 = time_Date();
      lVar2 = time_Time_Month();
      uStack0000000000000050 = in_stack_00000080;
      uStack0000000000000048 = in_stack_00000058;
      uStack00000000000000a8 = in_stack_000000b0;
    } while (lVar2 != 1);
  } while( true );
  while( true ) {
    time_Time_AddDate(0,0,uVar3,uStack00000000000000a8,1);
    time_Time_Year();
    in_stack_00000080 = time_Time_Month();
    in_stack_000000b0 = time_Time_Day();
    in_stack_00000058 = time_Date();
    lVar2 = time_Time_Day();
    uStack0000000000000050 = in_stack_00000080;
    uStack0000000000000048 = in_stack_00000058;
    if (lVar2 == 1) break;
code_r0x017a086a:
    uStack00000000000000a8 = in_stack_000000b0;
    cVar1 = github_com_gogf_gf_v2_os_gcron_cronSchedule_checkMeetWeek(in_stack_000000b0);
    if (cVar1 == '\0') {
      bVar5 = 1;
      uVar3 = extraout_RDX_00;
    }
    else {
      time_Time_Day();
      uVar3 = *(undefined8 *)(in_stack_000000d0 + 0x40);
      runtime_mapaccess2_fast64();
      bVar5 = (byte)uVar3 ^ 1;
      uVar3 = extraout_RDX_01;
    }
    in_stack_00000080 = uStack0000000000000050;
    in_stack_00000058 = uStack0000000000000048;
    in_stack_000000b0 = uStack00000000000000a8;
    if (bVar5 == 0) goto code_r0x017a09ba;
  }
  goto code_r0x017a061f;
code_r0x017a09ba:
  uStack0000000000000048 = in_stack_00000058;
  uStack0000000000000050 = in_stack_00000080;
  uStack00000000000000a8 = in_stack_000000b0;
  cVar1 = github_com_gogf_gf_v2_os_gcron_cronSchedule_checkMeetHour(in_stack_000000b0);
  in_stack_00000080 = uStack0000000000000050;
  in_stack_000000b0 = uStack00000000000000a8;
  if (cVar1 != '\0') {
    do {
      uStack00000000000000a8 = in_stack_000000b0;
      cVar1 = github_com_gogf_gf_v2_os_gcron_cronSchedule_checkMeetMinute(in_stack_000000b0);
      in_stack_00000080 = uStack0000000000000050;
      in_stack_00000058 = uStack0000000000000048;
      in_stack_000000b0 = uStack00000000000000a8;
      if (cVar1 != '\0') goto code_r0x017a0b69;
      time_Time_Add(60000000000);
      in_stack_00000058 = time_Time_Truncate(60000000000);
      uVar4 = time_Time_absSec();
      uStack0000000000000050 = in_stack_00000080;
      uStack0000000000000048 = in_stack_00000058;
    } while ((long)(SUB168(SEXT816(-0x7777777777777777) * SEXT816((long)(uVar4 % 0xe10)),8) +
                   uVar4 % 0xe10) >> 5 != 0);
    goto code_r0x017a061f;
  }
  time_Time_Add(3600000000000);
  in_stack_00000058 = time_Time_Truncate(3600000000000);
  in_RCX = time_Time_absSec();
  in_RCX = in_RCX % 0x15180;
  uVar4 = SUB168(SEXT816(0x48d159e26af37c05) * SEXT816((long)in_RCX),8);
  goto code_r0x017a0a62;
code_r0x017a0b69:
  do {
    uStack0000000000000048 = in_stack_00000058;
    uStack00000000000000a8 = in_stack_000000b0;
    cVar1 = github_com_gogf_gf_v2_os_gcron_cronSchedule_checkMeetSecond(in_stack_000000b8,in_stack_00000058,in_stack_000000b0,in_stack_00000068,
                         uStack0000000000000050,in_stack_000000b0);
    in_stack_00000080 = uStack0000000000000050;
    if (cVar1 != '\0') {
      uStack0000000000000088 = uStack0000000000000048;
      if (in_stack_000000a0 != 0) {
        if ((long)uStack0000000000000048 < 0) {
          uStack0000000000000088 = (ulong)((uint)uStack0000000000000048 & 0x3fffffff);
        }
        return uStack0000000000000088;
      }
      runtime_gopanic();
                    /* WARNING: Subroutine does not return */
      runtime_panicdivide();
    }
    in_stack_000000b0 = uStack00000000000000a8;
    in_stack_00000058 = time_Time_Add(1000000000);
    lVar2 = time_Time_absSec();
    uStack0000000000000050 = in_stack_00000080;
  } while (0x444444444444444 <
           (lVar2 * -0x1111111111111111 << 0x3e | (ulong)(lVar2 * -0x1111111111111111) >> 2));
  goto code_r0x017a061f;
}



