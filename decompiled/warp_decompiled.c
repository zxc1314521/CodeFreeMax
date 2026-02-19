// CodeFreeMax - WARP Channel Decompiled Functions
// 7 functions

// === warp.ChatCompletions @ 0x17150e0 ===

/* WARNING: Removing unreachable block (ram,0x01715399) */
/* WARNING: Removing unreachable block (ram,0x017153af) */
/* WARNING: Removing unreachable block (ram,0x017153ca) */
/* WARNING: Removing unreachable block (ram,0x017153e5) */
/* WARNING: Removing unreachable block (ram,0x01715415) */
/* WARNING: Removing unreachable block (ram,0x01715c7f) */
/* WARNING: Removing unreachable block (ram,0x01715a0e) */
/* WARNING: Removing unreachable block (ram,0x01715a83) */
/* WARNING: Removing unreachable block (ram,0x01715a16) */
/* WARNING: Removing unreachable block (ram,0x01715a4f) */
/* WARNING: Removing unreachable block (ram,0x01715a28) */
/* WARNING: Removing unreachable block (ram,0x01715a39) */
/* WARNING: Removing unreachable block (ram,0x01715c2e) */
/* WARNING: Removing unreachable block (ram,0x01715c75) */
/* WARNING: Removing unreachable block (ram,0x01715c45) */
/* WARNING: Removing unreachable block (ram,0x01715c4e) */
/* WARNING: Removing unreachable block (ram,0x01715b63) */

undefined8 warp_ChatCompletions(long param_1,long param_2,undefined8 param_3,long param_4)

{
  ulong uVar1;
  long lVar2;
  char cVar3;
  undefined8 uVar4;
  undefined8 uVar5;
  undefined8 *puVar6;
  long lVar7;
  undefined8 uVar8;
  long lVar9;
  undefined8 *puVar10;
  long lVar11;
  ulong uVar12;
  undefined8 uVar13;
  undefined8 extraout_RDX;
  ulong uVar14;
  undefined8 extraout_RDX_00;
  long lVar15;
  undefined8 extraout_RDX_01;
  undefined8 extraout_RDX_02;
  undefined8 extraout_RDX_03;
  undefined8 extraout_RDX_04;
  undefined8 extraout_RDX_05;
  undefined8 extraout_RDX_06;
  undefined8 extraout_RDX_07;
  undefined8 extraout_RDX_08;
  undefined8 extraout_RDX_09;
  undefined8 extraout_RDX_10;
  long unaff_RBX;
  undefined1 (*in_R11) [16];
  long unaff_R14;
  undefined1 auVar16 [16];
  undefined1 auVar17 [16];
  long lStack0000000000000010;
  long lStack0000000000000018;
  long lStack0000000000000020;
  long lStack0000000000000028;
  undefined1 auStack_78 [8];
  long lStack_70;
  long lStack_68;
  undefined8 *puStack_38;
  long lStack_30;
  undefined8 uStack_20;
  undefined8 uStack_18;
  undefined8 uStack_10;
  
  lStack0000000000000018 = param_4;
  lStack0000000000000010 = unaff_RBX;
  lStack0000000000000020 = param_1;
  while (lStack0000000000000028 = param_2, auStack_78 <= *(undefined1 **)(unaff_R14 + 0x10)) {
    runtime_morestack_noctxt();
    param_2 = lStack0000000000000028;
  }
  xdZLD7_EhcRHSSrp7n();
  (*(code *)*DAT_02e33490)();
  (*(code *)*DAT_02e33498)();
  (*(code *)*DAT_02e334a0)();
  cVar3 = kiro2api_internal_logic_warp_isWarpModelAllowed(*(undefined8 *)(lStack0000000000000028 + 8));
  lVar9 = lStack0000000000000010;
  if (cVar3 == '\0') {
    auVar16 = runtime_convTstring();
    lStack_30 = auVar16._0_8_;
    puStack_38 = &DAT_0194e220;
    fmt_Errorf(1,1,auVar16._8_8_,&puStack_38);
    return 0;
  }
  auVar16 = kiro2api_internal_logic_warp_sWarp_CheckToken(lStack0000000000000020);
  if (auVar16._0_8_ != 0) {
    puStack_38 = *(undefined8 **)(auVar16._0_8_ + 8);
    lStack_30 = lVar9;
    fmt_Errorf(1,1,auVar16._8_8_,&puStack_38);
    return 0;
  }
  (*(code *)*DAT_02e334a8)();
  (*(code *)*DAT_02e334b0)();
  lVar9 = lStack0000000000000010;
  lVar11 = lStack0000000000000018;
  lVar15 = lStack0000000000000028;
  auVar16 = kiro2api_internal_logic_warp_sWarp_buildWarpRequest();
  uVar13 = auVar16._0_8_;
  if (lVar9 == 0) {
    auVar16 = google_golang_org_protobuf_proto_Marshal();
    uVar4 = auVar16._0_8_;
    if (lVar15 == 0) {
      (**(code **)PTR_PTR_02ddf1c8)();
      (**(code **)PTR_PTR_02ddf1c0)();
      if (*(long *)(lStack0000000000000028 + 0xc0) != 0) {
        os_WriteFile(uVar13,lVar11,extraout_RDX,uVar4);
        kiro2api_internal_logic_warp_UnmarshalMessage();
      }
      lStack_68 = github_com_imroc_req_v3_Client_Clone();
      *(undefined1 *)(lStack_68 + 0x49) = 1;
      (**(code **)PTR_PTR_02ddf1d0)();
      (**(code **)PTR_PTR_02ddf1e8)();
      lVar9 = lStack0000000000000018;
      uVar5 = kiro2api_internal_logic_warp_GetWarpProxyURL();
      uVar8 = 0;
      if (lVar9 != 0) {
        github_com_imroc_req_v3_Client_SetProxyURL();
        uVar8 = uVar5;
      }
      if (*(long *)(lStack0000000000000020 + 0x58) == 0) {
        uVar5 = github_com_google_uuid_NewString();
        *(undefined8 *)(lStack0000000000000020 + 0x58) = uVar8;
        lVar9 = lStack0000000000000020;
        if (DAT_02e5e450 != 0) {
          auVar16 = runtime_gcWriteBarrier2();
          uVar5 = auVar16._0_8_;
          *in_R11 = auVar16;
        }
        *(undefined8 *)(lVar9 + 0x50) = uVar5;
        kiro2api_internal_dao_WarpAccountDao_Update();
      }
      puVar10 = *(undefined8 **)(lStack_68 + 0x60);
      if (puVar10 == (undefined8 *)0x0) {
        lVar7 = 0;
      }
      else {
        puVar6 = (undefined8 *)runtime_newobject();
        *puVar6 = *puVar10;
        auVar16._8_8_ = puVar10[1];
        auVar16._0_8_ = puVar6;
        puVar6 = puVar10;
        if (DAT_02e5e450 != 0) {
          auVar16 = runtime_gcWriteBarrier1();
          *(long *)*in_R11 = auVar16._8_8_;
        }
        lVar7 = auVar16._0_8_;
        *(long *)(lVar7 + 8) = auVar16._8_8_;
        lVar9 = *(long *)(lVar7 + 0x18);
        uVar12 = *(ulong *)(lVar7 + 0x20);
        lVar15 = puVar6[3];
        uVar1 = lVar9 + lVar15;
        uVar8 = *(undefined8 *)(lVar7 + 0x10);
        uStack_10 = puVar6[2];
        if (uVar12 < uVar1) {
          uVar8 = runtime_growslice(lVar15,&DAT_019ea040);
        }
        uVar14 = (long)(lVar9 - uVar12) >> 0x3f;
        in_R11 = (undefined1 (*) [16])(lVar9 << 3 & uVar14);
        uVar5 = uStack_10;
        uStack_10 = uVar8;
        runtime_typedslicecopy(uVar5,lVar15,uVar14,uVar1 - lVar9);
        *(ulong *)(lVar7 + 0x18) = uVar1;
        *(ulong *)(lVar7 + 0x20) = uVar12;
        lVar9 = lVar7;
        if (DAT_02e5e450 != 0) {
          runtime_gcWriteBarrier2();
          *(undefined8 *)*in_R11 = uStack_10;
          *(undefined8 *)(*in_R11 + 8) = extraout_RDX_00;
        }
        *(undefined8 *)(lVar9 + 0x10) = uStack_10;
        lVar15 = *(long *)(lVar9 + 0x30);
        uVar12 = *(ulong *)(lVar9 + 0x38);
        lVar2 = puVar10[6];
        uVar1 = lVar15 + lVar2;
        uVar8 = *(undefined8 *)(lVar9 + 0x28);
        uStack_18 = puVar10[5];
        if (uVar12 < uVar1) {
          uVar8 = runtime_growslice(lVar2,&DAT_019cbd00);
        }
        uVar14 = (long)(lVar15 - uVar12) >> 0x3f;
        uVar5 = uStack_18;
        uStack_18 = uVar8;
        runtime_typedslicecopy(uVar5,lVar2,uVar14,uVar1 - lVar15,lVar15 << 3 & uVar14);
        *(ulong *)(lVar7 + 0x30) = uVar1;
        *(ulong *)(lVar7 + 0x38) = uVar12;
        if (DAT_02e5e450 != 0) {
          uVar8 = *(undefined8 *)(lVar7 + 0x28);
          runtime_gcWriteBarrier2();
          *(undefined8 *)*in_R11 = uStack_18;
          *(undefined8 *)(*in_R11 + 8) = uVar8;
        }
        *(undefined8 *)(lVar7 + 0x28) = uStack_18;
      }
      lVar9 = runtime_newobject();
      if (DAT_02e5e450 != 0) {
        lVar9 = runtime_gcWriteBarrier2();
        *(long *)*in_R11 = lStack_68;
        *(long *)(*in_R11 + 8) = lVar7;
      }
      *(long *)(lVar9 + 0xf8) = lStack_68;
      *(long *)(lVar9 + 0x130) = lVar7;
      lVar15 = 0;
      if (lStack0000000000000010 != 0) {
        *(long *)(lVar9 + 0x160) = lStack0000000000000010;
        if (DAT_02e5e450 != 0) {
          lVar9 = runtime_gcWriteBarrier1();
          *(long *)*in_R11 = lStack0000000000000018;
        }
        *(long *)(lVar9 + 0x168) = lStack0000000000000018;
        lVar15 = lStack0000000000000018;
      }
      github_com_imroc_req_v3_Request_SetHeader(&DAT_01c40057,8,lVar15,0x10);
      github_com_imroc_req_v3_Request_SetHeader(&DAT_01c66e9c,0x1d,extraout_RDX_01,0x15);
      github_com_imroc_req_v3_Request_SetHeader("macOStasksstartMacOSnanos%s_%ddiffsplansskill.jsonPATCHx-appuser_ravenbytesQuery3.0.0ROUTE%s#%d</tr>debug%s:%d*fuzz*listPOST:HEAD:IndexInputshort%s,%s=j=02=G=15-0700%dh%sdefersweeptestRtestWexecWhchanexecRschedsudogtimergscanmheaptracepanicsleepamd64gcing MB,  got= ...\n max=scav  ptr ] = (trap:init  ms, fault and  tab= tag= top=[...], fp:deny"
                   ,5,extraout_RDX_02,0x12);
      github_com_imroc_req_v3_Request_SetHeader("macOStasksstartMacOSnanos%s_%ddiffsplansskill.jsonPATCHx-appuser_ravenbytesQuery3.0.0ROUTE%s#%d</tr>debug%s:%d*fuzz*listPOST:HEAD:IndexInputshort%s,%s=j=02=G=15-0700%dh%sdefersweeptestRtestWexecWhchanexecRschedsudogtimergscanmheaptracepanicsleepamd64gcing MB,  got= ...\n max=scav  ptr ] = (trap:init  ms, fault and  tab= tag= top=[...], fp:deny"
                   ,5,extraout_RDX_03,0xe);
      github_com_imroc_req_v3_Request_SetHeader("15.6.1inputsimagesoffset0.70.0system/usagev2.9.7%s[%d]ServerConfigSERVERDOMAINMETHOD%s#%d,Logger<html><head><body><hr />/traceactiondomainmethod/[^/]+PATCH:TRACE:/indexUSAGE\n-/--%sOutput-07:00000000 Valuesysmontimersefenceselectscalar, not       unused objs\n next= jobs= goid sweep  B -> % util alloc free  span= prev= list=, i =  code= addr=], sp= m->p= p->m=SCHED  curg= ctxt: min=  max= bad ts(...)\n m=nil base hangupkilledallow"
                   ,6,extraout_RDX_04,0x11);
      github_com_imroc_req_v3_Request_SetHeader(*(undefined8 *)(lStack0000000000000020 + 0x50),
                   *(undefined8 *)(lStack0000000000000020 + 0x58),lStack0000000000000020,0x14);
      uStack_20 = github_com_imroc_req_v3_Request_SetHeader(&DAT_01c5a78f,0x16,extraout_RDX_05,0xc);
      auVar16 = runtime_concatstring2(*(undefined8 *)(lStack0000000000000020 + 0x38),
                             *(undefined8 *)(lStack0000000000000020 + 0x40),lStack0000000000000020,7
                            );
      github_com_imroc_req_v3_Request_SetHeader(auVar16._0_8_,&DAT_01c3ddc9,auVar16._8_8_,0xd);
      github_com_imroc_req_v3_Request_SetHeader(&DAT_01c50d2f,0x11,extraout_RDX_06,6);
      github_com_imroc_req_v3_Request_SetHeader(&DAT_01c3df2e,7,extraout_RDX_07,0xf);
      github_com_imroc_req_v3_Request_SetHeader(&DAT_01c48208,0xc,extraout_RDX_08,4);
      lStack_70 = github_com_imroc_req_v3_Request_SetHeader(0,0,extraout_RDX_09,10);
      *(undefined8 *)(lStack_70 + 0xc0) = uVar13;
      *(long *)(lStack_70 + 200) = lVar11;
      if (DAT_02e5e450 != 0) {
        uVar8 = *(undefined8 *)(lStack_70 + 0xb8);
        lStack_70 = runtime_gcWriteBarrier2();
        *(undefined8 *)*in_R11 = uVar4;
        *(undefined8 *)(*in_R11 + 8) = uVar8;
      }
      *(undefined8 *)(lStack_70 + 0xb8) = uVar4;
      puVar10 = (undefined8 *)runtime_newobject();
      auVar17._8_8_ = lStack_70;
      auVar17._0_8_ = puVar10;
      *puVar10 = &LAB_01715ce0;
      puVar10[2] = uVar13;
      puVar10[3] = lVar11;
      if (DAT_02e5e450 != 0) {
        uVar13 = *(undefined8 *)(lStack_70 + 0xd0);
        auVar17 = runtime_gcWriteBarrier3();
        *(undefined8 *)*in_R11 = uVar4;
        *(long *)(*in_R11 + 8) = auVar17._0_8_;
        *(undefined8 *)in_R11[1] = uVar13;
      }
      *(undefined8 *)(auVar17._0_8_ + 8) = uVar4;
      *(long *)(auVar17._8_8_ + 0xd0) = auVar17._0_8_;
      uVar13 = 4;
      github_com_imroc_req_v3_Request_Send(&DAT_01c71fbd,0x23);
      puStack_38 = DAT_01c3979a;
      lStack_30 = uVar13;
      fmt_Errorf(1,1,extraout_RDX_10,&puStack_38);
      return 0;
    }
    puStack_38 = *(undefined8 **)(lVar15 + 8);
    lStack_30 = param_2;
    fmt_Errorf(1,1,auVar16._8_8_,&puStack_38);
    return 0;
  }
  puStack_38 = *(undefined8 **)(lVar9 + 8);
  lStack_30 = lVar11;
  fmt_Errorf(1,1,auVar16._8_8_,&puStack_38);
  return 0;
}




// === warp.buildFullPrompt @ 0x1716140 ===

void warp_buildFullPrompt
               (undefined8 *param_1,undefined8 param_2,undefined8 param_3,undefined8 *param_4)

{
  undefined1 *puVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  uint uVar5;
  undefined8 in_RAX;
  undefined8 uVar6;
  long lVar7;
  long lVar8;
  undefined8 uVar9;
  undefined1 *puVar10;
  ulong uVar11;
  undefined8 *puVar12;
  ulong uVar13;
  long lVar14;
  undefined8 *puVar15;
  long extraout_RDX;
  undefined8 *unaff_RBX;
  undefined1 *puVar16;
  undefined1 *unaff_RBP;
  undefined1 *puVar17;
  undefined8 *puVar18;
  long *plVar19;
  undefined8 in_R10;
  long unaff_R14;
  bool bVar20;
  undefined8 in_XMM15_Qa;
  undefined8 in_XMM15_Qb;
  undefined1 auVar21 [16];
  
  do {
    puVar16 = (undefined1 *)register0x00000020;
    puVar17 = unaff_RBP;
    if (*(undefined1 **)(unaff_R14 + 0x10) < (undefined1 *)((long)register0x00000020 + -0x238)) {
      puVar17 = (undefined1 *)((long)register0x00000020 + -8);
      *(undefined1 **)((long)register0x00000020 + -8) = unaff_RBP;
      puVar16 = (undefined1 *)((long)register0x00000020 + -0x2b8);
      *(undefined8 **)((long)register0x00000020 + 0x20) = param_1;
      *(undefined8 *)((long)register0x00000020 + -0x148) = in_XMM15_Qa;
      *(undefined8 *)((long)register0x00000020 + -0x140) = in_XMM15_Qb;
      *(undefined8 *)((long)register0x00000020 + -0x138) = in_XMM15_Qa;
      *(undefined8 *)((long)register0x00000020 + -0x130) = in_XMM15_Qb;
      lVar7 = param_1[9];
      *(undefined8 *)((long)register0x00000020 + -0x2c0) = 0x1716185;
      uVar6 = kiro2api_internal_logic_warp_extractSystemPrompt();
      if (lVar7 == 0) {
LAB_017163e3:
        if (*(undefined1 **)((long)register0x00000020 + -0x148) == (undefined1 *)0x0) {
          *(undefined1 **)((long)register0x00000020 + -0x148) =
               (undefined1 *)((long)register0x00000020 + -0x148);
LAB_0171641d:
          uVar11 = *(ulong *)((long)register0x00000020 + -0x130);
          uVar13 = *(long *)((long)register0x00000020 + -0x138) + 0x17;
          uVar6 = *(undefined8 *)((long)register0x00000020 + -0x140);
          if (uVar11 < uVar13) {
            *(long *)((long)register0x00000020 + -0x1a0) =
                 *(long *)((long)register0x00000020 + -0x138);
            param_1 = (undefined8 *)0x17;
            *(undefined8 *)((long)register0x00000020 + -0x2c0) = 0x171645a;
            uVar6 = runtime_growslice(0x17,&DAT_0194e2a0,uVar13,uVar11,
                                 (undefined1 *)((long)register0x00000020 + -0x148));
          }
          *(ulong *)((long)register0x00000020 + -0x1a0) = uVar11;
          *(ulong *)((long)register0x00000020 + -0x1a8) = uVar13;
          *(undefined8 *)((long)register0x00000020 + -0x10) = uVar6;
          param_4 = (undefined8 *)0x17;
          *(undefined8 *)((long)register0x00000020 + -0x2c0) = 0x1716491;
          runtime_memmove();
          *(undefined8 *)((long)register0x00000020 + -0x138) =
               *(undefined8 *)((long)register0x00000020 + -0x1a8);
          *(undefined8 *)((long)register0x00000020 + -0x130) =
               *(undefined8 *)((long)register0x00000020 + -0x1a0);
          *(undefined8 *)((long)register0x00000020 + -0x140) =
               *(undefined8 *)((long)register0x00000020 + -0x10);
          if (*(undefined1 **)((long)register0x00000020 + -0x148) == (undefined1 *)0x0) {
            *(undefined1 **)((long)register0x00000020 + -0x148) =
                 (undefined1 *)((long)register0x00000020 + -0x148);
LAB_017164fd:
            uVar11 = *(ulong *)((long)register0x00000020 + -0x130);
            uVar13 = *(long *)((long)register0x00000020 + -0x138) + 0xa5;
            uVar6 = *(undefined8 *)((long)register0x00000020 + -0x140);
            if (uVar11 < uVar13) {
              *(long *)((long)register0x00000020 + -0x1a0) =
                   *(long *)((long)register0x00000020 + -0x138);
              param_1 = (undefined8 *)0xa5;
              *(undefined8 *)((long)register0x00000020 + -0x2c0) = 0x1716545;
              uVar6 = runtime_growslice(0xa5,&DAT_0194e2a0,uVar13,uVar11,
                                   (undefined1 *)((long)register0x00000020 + -0x148));
            }
            *(undefined8 *)((long)register0x00000020 + -0x10) = uVar6;
            *(ulong *)((long)register0x00000020 + -0x1a0) = uVar11;
            *(ulong *)((long)register0x00000020 + -0x1a8) = uVar13;
            param_4 = (undefined8 *)0xa5;
            *(undefined8 *)((long)register0x00000020 + -0x2c0) = 0x171657c;
            runtime_memmove();
            *(undefined8 *)((long)register0x00000020 + -0x138) =
                 *(undefined8 *)((long)register0x00000020 + -0x1a8);
            *(undefined8 *)((long)register0x00000020 + -0x130) =
                 *(undefined8 *)((long)register0x00000020 + -0x1a0);
            *(undefined8 *)((long)register0x00000020 + -0x140) =
                 *(undefined8 *)((long)register0x00000020 + -0x10);
            if (*(undefined1 **)((long)register0x00000020 + -0x148) == (undefined1 *)0x0) {
              *(undefined1 **)((long)register0x00000020 + -0x148) =
                   (undefined1 *)((long)register0x00000020 + -0x148);
LAB_017165e5:
              uVar11 = *(ulong *)((long)register0x00000020 + -0x130);
              uVar13 = *(long *)((long)register0x00000020 + -0x138) + 0x19;
              uVar6 = *(undefined8 *)((long)register0x00000020 + -0x140);
              if (uVar11 < uVar13) {
                *(long *)((long)register0x00000020 + -0x1a0) =
                     *(long *)((long)register0x00000020 + -0x138);
                param_1 = (undefined8 *)&DAT_00000019;
                *(undefined8 *)((long)register0x00000020 + -0x2c0) = 0x1716625;
                uVar6 = runtime_growslice(0x19,&DAT_0194e2a0,uVar13,uVar11,
                                     (undefined1 *)((long)register0x00000020 + -0x148));
              }
              *(ulong *)((long)register0x00000020 + -0x1a0) = uVar11;
              *(ulong *)((long)register0x00000020 + -0x1a8) = uVar13;
              *(undefined8 *)((long)register0x00000020 + -0x10) = uVar6;
              param_4 = (undefined8 *)&DAT_00000019;
              *(undefined8 *)((long)register0x00000020 + -0x2c0) = 0x171665c;
              runtime_memmove();
              *(undefined8 *)((long)register0x00000020 + -0x138) =
                   *(undefined8 *)((long)register0x00000020 + -0x1a8);
              *(undefined8 *)((long)register0x00000020 + -0x130) =
                   *(undefined8 *)((long)register0x00000020 + -0x1a0);
              *(undefined8 *)((long)register0x00000020 + -0x140) =
                   *(undefined8 *)((long)register0x00000020 + -0x10);
              if (*(undefined1 **)((long)register0x00000020 + -0x148) == (undefined1 *)0x0) {
                *(undefined1 **)((long)register0x00000020 + -0x148) =
                     (undefined1 *)((long)register0x00000020 + -0x148);
LAB_017166c5:
                uVar11 = *(ulong *)((long)register0x00000020 + -0x130);
                uVar13 = *(long *)((long)register0x00000020 + -0x138) + 0x14;
                uVar6 = *(undefined8 *)((long)register0x00000020 + -0x140);
                if (uVar11 < uVar13) {
                  *(long *)((long)register0x00000020 + -0x1a0) =
                       *(long *)((long)register0x00000020 + -0x138);
                  param_1 = (undefined8 *)0x14;
                  *(undefined8 *)((long)register0x00000020 + -0x2c0) = 0x1716705;
                  uVar6 = runtime_growslice(0x14,&DAT_0194e2a0,uVar13,uVar11,
                                       (undefined1 *)((long)register0x00000020 + -0x148));
                }
                *(ulong *)((long)register0x00000020 + -0x1a0) = uVar11;
                *(ulong *)((long)register0x00000020 + -0x1a8) = uVar13;
                *(undefined8 *)((long)register0x00000020 + -0x10) = uVar6;
                param_4 = (undefined8 *)0x14;
                *(undefined8 *)((long)register0x00000020 + -0x2c0) = 0x171673c;
                runtime_memmove();
                *(undefined8 *)((long)register0x00000020 + -0x138) =
                     *(undefined8 *)((long)register0x00000020 + -0x1a8);
                *(undefined8 *)((long)register0x00000020 + -0x130) =
                     *(undefined8 *)((long)register0x00000020 + -0x1a0);
                *(undefined8 *)((long)register0x00000020 + -0x140) =
                     *(undefined8 *)((long)register0x00000020 + -0x10);
                if (*(undefined1 **)((long)register0x00000020 + -0x148) == (undefined1 *)0x0) {
                  *(undefined1 **)((long)register0x00000020 + -0x148) =
                       (undefined1 *)((long)register0x00000020 + -0x148);
LAB_017167a5:
                  uVar11 = *(ulong *)((long)register0x00000020 + -0x130);
                  uVar13 = *(long *)((long)register0x00000020 + -0x138) + 0x2e;
                  uVar6 = *(undefined8 *)((long)register0x00000020 + -0x140);
                  if (uVar11 < uVar13) {
                    *(long *)((long)register0x00000020 + -0x1a0) =
                         *(long *)((long)register0x00000020 + -0x138);
                    param_1 = (undefined8 *)&DAT_0000002e;
                    *(undefined8 *)((long)register0x00000020 + -0x2c0) = 0x17167e5;
                    uVar6 = runtime_growslice(0x2e,&DAT_0194e2a0,uVar13,uVar11,
                                         (undefined1 *)((long)register0x00000020 + -0x148));
                  }
                  *(ulong *)((long)register0x00000020 + -0x1a0) = uVar11;
                  *(ulong *)((long)register0x00000020 + -0x1a8) = uVar13;
                  *(undefined8 *)((long)register0x00000020 + -0x10) = uVar6;
                  param_4 = (undefined8 *)&DAT_0000002e;
                  *(undefined8 *)((long)register0x00000020 + -0x2c0) = 0x171681c;
                  runtime_memmove();
                  *(undefined8 *)((long)register0x00000020 + -0x138) =
                       *(undefined8 *)((long)register0x00000020 + -0x1a8);
                  *(undefined8 *)((long)register0x00000020 + -0x130) =
                       *(undefined8 *)((long)register0x00000020 + -0x1a0);
                  *(undefined8 *)((long)register0x00000020 + -0x140) =
                       *(undefined8 *)((long)register0x00000020 + -0x10);
                  if (*(undefined1 **)((long)register0x00000020 + -0x148) == (undefined1 *)0x0) {
                    *(undefined1 **)((long)register0x00000020 + -0x148) =
                         (undefined1 *)((long)register0x00000020 + -0x148);
LAB_01716885:
                    uVar11 = *(ulong *)((long)register0x00000020 + -0x130);
                    uVar13 = *(long *)((long)register0x00000020 + -0x138) + 0x7d;
                    uVar6 = *(undefined8 *)((long)register0x00000020 + -0x140);
                    if (uVar11 < uVar13) {
                      *(long *)((long)register0x00000020 + -0x1a0) =
                           *(long *)((long)register0x00000020 + -0x138);
                      param_1 = (undefined8 *)0x7d;
                      *(undefined8 *)((long)register0x00000020 + -0x2c0) = 0x17168c5;
                      uVar6 = runtime_growslice(0x7d,&DAT_0194e2a0,uVar13,uVar11,
                                           (undefined1 *)((long)register0x00000020 + -0x148));
                    }
                    *(ulong *)((long)register0x00000020 + -0x1a0) = uVar13;
                    *(ulong *)((long)register0x00000020 + -0x1a8) = uVar11;
                    *(undefined8 *)((long)register0x00000020 + -0x10) = uVar6;
                    param_4 = (undefined8 *)0x7d;
                    *(undefined8 *)((long)register0x00000020 + -0x2c0) = 0x17168fc;
                    runtime_memmove();
                    *(undefined8 *)((long)register0x00000020 + -0x138) =
                         *(undefined8 *)((long)register0x00000020 + -0x1a0);
                    *(undefined8 *)((long)register0x00000020 + -0x130) =
                         *(undefined8 *)((long)register0x00000020 + -0x1a8);
                    *(undefined8 *)((long)register0x00000020 + -0x140) =
                         *(undefined8 *)((long)register0x00000020 + -0x10);
                    if (*(undefined1 **)((long)register0x00000020 + -0x148) == (undefined1 *)0x0) {
                      *(undefined1 **)((long)register0x00000020 + -0x148) =
                           (undefined1 *)((long)register0x00000020 + -0x148);
LAB_01716965:
                      uVar11 = *(ulong *)((long)register0x00000020 + -0x130);
                      uVar13 = *(long *)((long)register0x00000020 + -0x138) + 0x8b;
                      uVar6 = *(undefined8 *)((long)register0x00000020 + -0x140);
                      if (uVar11 < uVar13) {
                        *(long *)((long)register0x00000020 + -0x1a0) =
                             *(long *)((long)register0x00000020 + -0x138);
                        param_1 = (undefined8 *)0x8b;
                        *(undefined8 *)((long)register0x00000020 + -0x2c0) = 0x17169a5;
                        uVar6 = runtime_growslice(0x8b,&DAT_0194e2a0,uVar13,uVar11,
                                             (undefined1 *)((long)register0x00000020 + -0x148));
                      }
                      *(ulong *)((long)register0x00000020 + -0x1a0) = uVar11;
                      *(ulong *)((long)register0x00000020 + -0x1a8) = uVar13;
                      *(undefined8 *)((long)register0x00000020 + -0x10) = uVar6;
                      param_4 = (undefined8 *)0x8b;
                      *(undefined8 *)((long)register0x00000020 + -0x2c0) = 0x17169dc;
                      runtime_memmove();
                      *(undefined8 *)((long)register0x00000020 + -0x138) =
                           *(undefined8 *)((long)register0x00000020 + -0x1a8);
                      *(undefined8 *)((long)register0x00000020 + -0x130) =
                           *(undefined8 *)((long)register0x00000020 + -0x1a0);
                      *(undefined8 *)((long)register0x00000020 + -0x140) =
                           *(undefined8 *)((long)register0x00000020 + -0x10);
                      if (*(undefined1 **)((long)register0x00000020 + -0x148) == (undefined1 *)0x0)
                      {
                        *(undefined1 **)((long)register0x00000020 + -0x148) =
                             (undefined1 *)((long)register0x00000020 + -0x148);
LAB_01716a45:
                        uVar11 = *(ulong *)((long)register0x00000020 + -0x130);
                        uVar13 = *(long *)((long)register0x00000020 + -0x138) + 0x43;
                        uVar6 = *(undefined8 *)((long)register0x00000020 + -0x140);
                        if (uVar11 < uVar13) {
                          *(long *)((long)register0x00000020 + -0x1a0) =
                               *(long *)((long)register0x00000020 + -0x138);
                          param_1 = (undefined8 *)&DAT_00000043;
                          *(undefined8 *)((long)register0x00000020 + -0x2c0) = 0x1716a85;
                          uVar6 = runtime_growslice(0x43,&DAT_0194e2a0,uVar13,uVar11,
                                               (undefined1 *)((long)register0x00000020 + -0x148));
                        }
                        *(ulong *)((long)register0x00000020 + -0x1a0) = uVar11;
                        *(ulong *)((long)register0x00000020 + -0x1a8) = uVar13;
                        *(undefined8 *)((long)register0x00000020 + -0x10) = uVar6;
                        param_4 = (undefined8 *)&DAT_00000043;
                        *(undefined8 *)((long)register0x00000020 + -0x2c0) = 0x1716abc;
                        runtime_memmove();
                        *(undefined8 *)((long)register0x00000020 + -0x138) =
                             *(undefined8 *)((long)register0x00000020 + -0x1a8);
                        *(undefined8 *)((long)register0x00000020 + -0x130) =
                             *(undefined8 *)((long)register0x00000020 + -0x1a0);
                        *(undefined8 *)((long)register0x00000020 + -0x140) =
                             *(undefined8 *)((long)register0x00000020 + -0x10);
                        if (*(undefined1 **)((long)register0x00000020 + -0x148) == (undefined1 *)0x0
                           ) {
                          *(undefined1 **)((long)register0x00000020 + -0x148) =
                               (undefined1 *)((long)register0x00000020 + -0x148);
LAB_01716b25:
                          uVar11 = *(ulong *)((long)register0x00000020 + -0x130);
                          uVar13 = *(long *)((long)register0x00000020 + -0x138) + 0x2a;
                          uVar6 = *(undefined8 *)((long)register0x00000020 + -0x140);
                          if (uVar11 < uVar13) {
                            *(long *)((long)register0x00000020 + -0x1a0) =
                                 *(long *)((long)register0x00000020 + -0x138);
                            param_1 = (undefined8 *)&DAT_0000002a;
                            *(undefined8 *)((long)register0x00000020 + -0x2c0) = 0x1716b65;
                            uVar6 = runtime_growslice(0x2a,&DAT_0194e2a0,uVar13,uVar11,
                                                 (undefined1 *)((long)register0x00000020 + -0x148));
                          }
                          *(ulong *)((long)register0x00000020 + -0x1a0) = uVar11;
                          *(ulong *)((long)register0x00000020 + -0x1a8) = uVar13;
                          *(undefined8 *)((long)register0x00000020 + -0x10) = uVar6;
                          param_4 = (undefined8 *)&DAT_0000002a;
                          *(undefined8 *)((long)register0x00000020 + -0x2c0) = 0x1716b9c;
                          runtime_memmove();
                          *(undefined8 *)((long)register0x00000020 + -0x138) =
                               *(undefined8 *)((long)register0x00000020 + -0x1a8);
                          *(undefined8 *)((long)register0x00000020 + -0x130) =
                               *(undefined8 *)((long)register0x00000020 + -0x1a0);
                          *(undefined8 *)((long)register0x00000020 + -0x140) =
                               *(undefined8 *)((long)register0x00000020 + -0x10);
                          if (*(undefined1 **)((long)register0x00000020 + -0x148) ==
                              (undefined1 *)0x0) {
                            *(undefined1 **)((long)register0x00000020 + -0x148) =
                                 (undefined1 *)((long)register0x00000020 + -0x148);
LAB_01716c05:
                            param_4 = *(undefined8 **)((long)register0x00000020 + -0x130);
                            lVar7 = *(long *)((long)register0x00000020 + -0x138);
                            puVar12 = (undefined8 *)(lVar7 + 1);
                            lVar8 = *(long *)((long)register0x00000020 + -0x140);
                            if (param_4 < puVar12) {
                              *(long *)((long)register0x00000020 + -0x1a0) = lVar7;
                              param_1 = (undefined8 *)0x1;
                              *(undefined8 *)((long)register0x00000020 + -0x2c0) = 0x1716c45;
                              lVar8 = runtime_growslice(1,&DAT_0194e2a0);
                              lVar7 = *(long *)((long)register0x00000020 + -0x1a0);
                            }
                            *(undefined1 *)(lVar8 + lVar7) = 10;
                            *(undefined8 **)((long)register0x00000020 + -0x138) = puVar12;
                            *(undefined8 **)((long)register0x00000020 + -0x130) = param_4;
                            *(long *)((long)register0x00000020 + -0x140) = lVar8;
                            if (*(undefined1 **)((long)register0x00000020 + -0x148) ==
                                (undefined1 *)0x0) {
                              *(undefined1 **)((long)register0x00000020 + -0x148) =
                                   (undefined1 *)((long)register0x00000020 + -0x148);
LAB_01716c97:
                              uVar11 = *(ulong *)((long)register0x00000020 + -0x130);
                              uVar13 = *(long *)((long)register0x00000020 + -0x138) + 0x37;
                              uVar6 = *(undefined8 *)((long)register0x00000020 + -0x140);
                              if (uVar11 < uVar13) {
                                *(long *)((long)register0x00000020 + -0x1a0) =
                                     *(long *)((long)register0x00000020 + -0x138);
                                param_1 = (undefined8 *)0x37;
                                *(undefined8 *)((long)register0x00000020 + -0x2c0) = 0x1716cd4;
                                uVar6 = runtime_growslice(0x37,&DAT_0194e2a0);
                              }
                              *(ulong *)((long)register0x00000020 + -0x1a0) = uVar11;
                              *(ulong *)((long)register0x00000020 + -0x1a8) = uVar13;
                              *(undefined8 *)((long)register0x00000020 + -0x10) = uVar6;
                              param_4 = (undefined8 *)0x37;
                              *(undefined8 *)((long)register0x00000020 + -0x2c0) = 0x1716d0b;
                              runtime_memmove();
                              *(undefined8 *)((long)register0x00000020 + -0x138) =
                                   *(undefined8 *)((long)register0x00000020 + -0x1a8);
                              *(undefined8 *)((long)register0x00000020 + -0x130) =
                                   *(undefined8 *)((long)register0x00000020 + -0x1a0);
                              *(undefined8 *)((long)register0x00000020 + -0x140) =
                                   *(undefined8 *)((long)register0x00000020 + -0x10);
                              if (*(undefined1 **)((long)register0x00000020 + -0x148) ==
                                  (undefined1 *)0x0) {
                                *(undefined1 **)((long)register0x00000020 + -0x148) =
                                     (undefined1 *)((long)register0x00000020 + -0x148);
LAB_01716d74:
                                param_4 = *(undefined8 **)((long)register0x00000020 + -0x130);
                                lVar7 = *(long *)((long)register0x00000020 + -0x138);
                                puVar12 = (undefined8 *)(lVar7 + 1);
                                lVar8 = *(long *)((long)register0x00000020 + -0x140);
                                if (param_4 < puVar12) {
                                  *(long *)((long)register0x00000020 + -0x1a0) = lVar7;
                                  param_1 = (undefined8 *)0x1;
                                  *(undefined8 *)((long)register0x00000020 + -0x2c0) = 0x1716db1;
                                  lVar8 = runtime_growslice(1,&DAT_0194e2a0);
                                  lVar7 = *(long *)((long)register0x00000020 + -0x1a0);
                                }
                                *(undefined1 *)(lVar8 + lVar7) = 10;
                                *(undefined8 **)((long)register0x00000020 + -0x138) = puVar12;
                                *(undefined8 **)((long)register0x00000020 + -0x130) = param_4;
                                *(long *)((long)register0x00000020 + -0x140) = lVar8;
                                if (*(undefined1 **)((long)register0x00000020 + -0x148) ==
                                    (undefined1 *)0x0) {
                                  *(undefined1 **)((long)register0x00000020 + -0x148) =
                                       (undefined1 *)((long)register0x00000020 + -0x148);
LAB_01716e01:
                                  uVar11 = *(ulong *)((long)register0x00000020 + -0x130);
                                  uVar13 = *(long *)((long)register0x00000020 + -0x138) + 0x16;
                                  uVar6 = *(undefined8 *)((long)register0x00000020 + -0x140);
                                  if (uVar11 < uVar13) {
                                    *(long *)((long)register0x00000020 + -0x1a0) =
                                         *(long *)((long)register0x00000020 + -0x138);
                                    param_1 = (undefined8 *)0x16;
                                    *(undefined8 *)((long)register0x00000020 + -0x2c0) = 0x1716e45;
                                    uVar6 = runtime_growslice(0x16,&DAT_0194e2a0);
                                  }
                                  *(ulong *)((long)register0x00000020 + -0x1a0) = uVar11;
                                  *(ulong *)((long)register0x00000020 + -0x1a8) = uVar13;
                                  *(undefined8 *)((long)register0x00000020 + -0x10) = uVar6;
                                  param_4 = (undefined8 *)0x16;
                                  *(undefined8 *)((long)register0x00000020 + -0x2c0) = 0x1716e7c;
                                  runtime_memmove();
                                  *(undefined8 *)((long)register0x00000020 + -0x138) =
                                       *(undefined8 *)((long)register0x00000020 + -0x1a8);
                                  *(undefined8 *)((long)register0x00000020 + -0x130) =
                                       *(undefined8 *)((long)register0x00000020 + -0x1a0);
                                  *(undefined8 *)((long)register0x00000020 + -0x140) =
                                       *(undefined8 *)((long)register0x00000020 + -0x10);
                                  if (*(undefined1 **)((long)register0x00000020 + -0x148) ==
                                      (undefined1 *)0x0) {
                                    *(undefined1 **)((long)register0x00000020 + -0x148) =
                                         (undefined1 *)((long)register0x00000020 + -0x148);
LAB_01716ee5:
                                    uVar11 = *(ulong *)((long)register0x00000020 + -0x130);
                                    uVar13 = *(long *)((long)register0x00000020 + -0x138) + 0x2d;
                                    uVar6 = *(undefined8 *)((long)register0x00000020 + -0x140);
                                    if (uVar11 < uVar13) {
                                      *(long *)((long)register0x00000020 + -0x1a0) =
                                           *(long *)((long)register0x00000020 + -0x138);
                                      param_1 = (undefined8 *)0x2d;
                                      *(undefined8 *)((long)register0x00000020 + -0x2c0) = 0x1716f25
                                      ;
                                      uVar6 = runtime_growslice(0x2d,&DAT_0194e2a0,uVar13,uVar11,
                                                           (undefined1 *)
                                                           ((long)register0x00000020 + -0x148));
                                    }
                                    *(ulong *)((long)register0x00000020 + -0x1a0) = uVar11;
                                    *(ulong *)((long)register0x00000020 + -0x1a8) = uVar13;
                                    *(undefined8 *)((long)register0x00000020 + -0x10) = uVar6;
                                    param_4 = (undefined8 *)0x2d;
                                    *(undefined8 *)((long)register0x00000020 + -0x2c0) = 0x1716f5c;
                                    runtime_memmove();
                                    *(undefined8 *)((long)register0x00000020 + -0x138) =
                                         *(undefined8 *)((long)register0x00000020 + -0x1a8);
                                    *(undefined8 *)((long)register0x00000020 + -0x130) =
                                         *(undefined8 *)((long)register0x00000020 + -0x1a0);
                                    *(undefined8 *)((long)register0x00000020 + -0x140) =
                                         *(undefined8 *)((long)register0x00000020 + -0x10);
                                    if (*(undefined1 **)((long)register0x00000020 + -0x148) ==
                                        (undefined1 *)0x0) {
                                      *(undefined1 **)((long)register0x00000020 + -0x148) =
                                           (undefined1 *)((long)register0x00000020 + -0x148);
LAB_01716fc5:
                                      uVar11 = *(ulong *)((long)register0x00000020 + -0x130);
                                      uVar13 = *(long *)((long)register0x00000020 + -0x138) + 0x26;
                                      uVar6 = *(undefined8 *)((long)register0x00000020 + -0x140);
                                      if (uVar11 < uVar13) {
                                        *(long *)((long)register0x00000020 + -0x1a0) =
                                             *(long *)((long)register0x00000020 + -0x138);
                                        param_1 = (undefined8 *)&DAT_00000026;
                                        *(undefined8 *)((long)register0x00000020 + -0x2c0) =
                                             0x1717005;
                                        uVar6 = runtime_growslice(0x26,&DAT_0194e2a0,uVar13,uVar11,
                                                             (undefined1 *)
                                                             ((long)register0x00000020 + -0x148));
                                      }
                                      *(ulong *)((long)register0x00000020 + -0x1a0) = uVar11;
                                      *(ulong *)((long)register0x00000020 + -0x1a8) = uVar13;
                                      *(undefined8 *)((long)register0x00000020 + -0x10) = uVar6;
                                      param_4 = (undefined8 *)&DAT_00000026;
                                      *(undefined8 *)((long)register0x00000020 + -0x2c0) = 0x171703c
                                      ;
                                      runtime_memmove();
                                      *(undefined8 *)((long)register0x00000020 + -0x138) =
                                           *(undefined8 *)((long)register0x00000020 + -0x1a8);
                                      *(undefined8 *)((long)register0x00000020 + -0x130) =
                                           *(undefined8 *)((long)register0x00000020 + -0x1a0);
                                      *(undefined8 *)((long)register0x00000020 + -0x140) =
                                           *(undefined8 *)((long)register0x00000020 + -0x10);
                                      if (*(undefined1 **)((long)register0x00000020 + -0x148) ==
                                          (undefined1 *)0x0) {
                                        *(undefined1 **)((long)register0x00000020 + -0x148) =
                                             (undefined1 *)((long)register0x00000020 + -0x148);
LAB_017170a5:
                                        uVar11 = *(ulong *)((long)register0x00000020 + -0x130);
                                        uVar13 = *(long *)((long)register0x00000020 + -0x138) + 0x25
                                        ;
                                        uVar6 = *(undefined8 *)((long)register0x00000020 + -0x140);
                                        if (uVar11 < uVar13) {
                                          *(long *)((long)register0x00000020 + -0x1a0) =
                                               *(long *)((long)register0x00000020 + -0x138);
                                          param_1 = (undefined8 *)&DAT_00000025;
                                          *(undefined8 *)((long)register0x00000020 + -0x2c0) =
                                               0x17170e5;
                                          uVar6 = runtime_growslice(0x25,&DAT_0194e2a0,uVar13,uVar11,
                                                               (undefined1 *)
                                                               ((long)register0x00000020 + -0x148));
                                        }
                                        *(ulong *)((long)register0x00000020 + -0x1a0) = uVar11;
                                        *(ulong *)((long)register0x00000020 + -0x1a8) = uVar13;
                                        *(undefined8 *)((long)register0x00000020 + -0x10) = uVar6;
                                        param_4 = (undefined8 *)&DAT_00000025;
                                        *(undefined8 *)((long)register0x00000020 + -0x2c0) =
                                             0x171711c;
                                        runtime_memmove();
                                        *(undefined8 *)((long)register0x00000020 + -0x138) =
                                             *(undefined8 *)((long)register0x00000020 + -0x1a8);
                                        *(undefined8 *)((long)register0x00000020 + -0x130) =
                                             *(undefined8 *)((long)register0x00000020 + -0x1a0);
                                        *(undefined8 *)((long)register0x00000020 + -0x140) =
                                             *(undefined8 *)((long)register0x00000020 + -0x10);
                                        if (*(undefined1 **)((long)register0x00000020 + -0x148) ==
                                            (undefined1 *)0x0) {
                                          *(undefined1 **)((long)register0x00000020 + -0x148) =
                                               (undefined1 *)((long)register0x00000020 + -0x148);
LAB_01717185:
                                          uVar11 = *(ulong *)((long)register0x00000020 + -0x130);
                                          uVar13 = *(long *)((long)register0x00000020 + -0x138) +
                                                   100;
                                          uVar6 = *(undefined8 *)((long)register0x00000020 + -0x140)
                                          ;
                                          if (uVar11 < uVar13) {
                                            *(long *)((long)register0x00000020 + -0x1a0) =
                                                 *(long *)((long)register0x00000020 + -0x138);
                                            param_1 = (undefined8 *)0x64;
                                            *(undefined8 *)((long)register0x00000020 + -0x2c0) =
                                                 0x17171c5;
                                            uVar6 = runtime_growslice(100,&DAT_0194e2a0,uVar13,uVar11,
                                                                 (undefined1 *)
                                                                 ((long)register0x00000020 + -0x148)
                                                                );
                                          }
                                          *(ulong *)((long)register0x00000020 + -0x1a0) = uVar11;
                                          *(ulong *)((long)register0x00000020 + -0x1a8) = uVar13;
                                          *(undefined8 *)((long)register0x00000020 + -0x10) = uVar6;
                                          param_4 = (undefined8 *)0x64;
                                          *(undefined8 *)((long)register0x00000020 + -0x2c0) =
                                               0x17171fc;
                                          runtime_memmove();
                                          *(undefined8 *)((long)register0x00000020 + -0x138) =
                                               *(undefined8 *)((long)register0x00000020 + -0x1a8);
                                          *(undefined8 *)((long)register0x00000020 + -0x130) =
                                               *(undefined8 *)((long)register0x00000020 + -0x1a0);
                                          *(undefined8 *)((long)register0x00000020 + -0x140) =
                                               *(undefined8 *)((long)register0x00000020 + -0x10);
                                          if (*(undefined1 **)((long)register0x00000020 + -0x148) ==
                                              (undefined1 *)0x0) {
                                            *(undefined1 **)((long)register0x00000020 + -0x148) =
                                                 (undefined1 *)((long)register0x00000020 + -0x148);
LAB_01717265:
                                            uVar11 = *(ulong *)((long)register0x00000020 + -0x130);
                                            uVar13 = *(long *)((long)register0x00000020 + -0x138) +
                                                     0x20;
                                            uVar6 = *(undefined8 *)
                                                     ((long)register0x00000020 + -0x140);
                                            if (uVar11 < uVar13) {
                                              *(long *)((long)register0x00000020 + -0x1a0) =
                                                   *(long *)((long)register0x00000020 + -0x138);
                                              param_1 = (undefined8 *)&DAT_00000020;
                                              *(undefined8 *)((long)register0x00000020 + -0x2c0) =
                                                   0x17172a5;
                                              uVar6 = runtime_growslice(0x20,&DAT_0194e2a0,uVar13,uVar11,
                                                                   (undefined1 *)
                                                                   ((long)register0x00000020 +
                                                                   -0x148));
                                            }
                                            *(ulong *)((long)register0x00000020 + -0x1a0) = uVar11;
                                            *(ulong *)((long)register0x00000020 + -0x1a8) = uVar13;
                                            *(undefined8 *)((long)register0x00000020 + -0x10) =
                                                 uVar6;
                                            param_4 = (undefined8 *)&DAT_00000020;
                                            *(undefined8 *)((long)register0x00000020 + -0x2c0) =
                                                 0x17172dc;
                                            runtime_memmove();
                                            *(undefined8 *)((long)register0x00000020 + -0x138) =
                                                 *(undefined8 *)((long)register0x00000020 + -0x1a8);
                                            *(undefined8 *)((long)register0x00000020 + -0x130) =
                                                 *(undefined8 *)((long)register0x00000020 + -0x1a0);
                                            *(undefined8 *)((long)register0x00000020 + -0x140) =
                                                 *(undefined8 *)((long)register0x00000020 + -0x10);
                                            if (*(undefined1 **)((long)register0x00000020 + -0x148)
                                                == (undefined1 *)0x0) {
                                              *(undefined1 **)((long)register0x00000020 + -0x148) =
                                                   (undefined1 *)((long)register0x00000020 + -0x148)
                                              ;
LAB_01717345:
                                              uVar11 = *(ulong *)((long)register0x00000020 + -0x130)
                                              ;
                                              uVar13 = *(long *)((long)register0x00000020 + -0x138)
                                                       + 0x25;
                                              uVar6 = *(undefined8 *)
                                                       ((long)register0x00000020 + -0x140);
                                              if (uVar11 < uVar13) {
                                                *(long *)((long)register0x00000020 + -0x1a0) =
                                                     *(long *)((long)register0x00000020 + -0x138);
                                                param_1 = (undefined8 *)&DAT_00000025;
                                                *(undefined8 *)((long)register0x00000020 + -0x2c0) =
                                                     0x1717385;
                                                uVar6 = runtime_growslice(0x25,&DAT_0194e2a0,uVar13,
                                                                     uVar11,(undefined1 *)
                                                                            ((long)
                                                  register0x00000020 + -0x148));
                                              }
                                              *(ulong *)((long)register0x00000020 + -0x1a0) = uVar11
                                              ;
                                              *(ulong *)((long)register0x00000020 + -0x1a8) = uVar13
                                              ;
                                              *(undefined8 *)((long)register0x00000020 + -0x10) =
                                                   uVar6;
                                              param_4 = (undefined8 *)&DAT_00000025;
                                              *(undefined8 *)((long)register0x00000020 + -0x2c0) =
                                                   0x17173bc;
                                              runtime_memmove();
                                              *(undefined8 *)((long)register0x00000020 + -0x138) =
                                                   *(undefined8 *)
                                                    ((long)register0x00000020 + -0x1a8);
                                              *(undefined8 *)((long)register0x00000020 + -0x130) =
                                                   *(undefined8 *)
                                                    ((long)register0x00000020 + -0x1a0);
                                              *(undefined8 *)((long)register0x00000020 + -0x140) =
                                                   *(undefined8 *)((long)register0x00000020 + -0x10)
                                              ;
                                              if (*(undefined1 **)
                                                   ((long)register0x00000020 + -0x148) ==
                                                  (undefined1 *)0x0) {
                                                *(undefined1 **)((long)register0x00000020 + -0x148)
                                                     = (undefined1 *)
                                                       ((long)register0x00000020 + -0x148);
LAB_01717425:
                                                uVar11 = *(ulong *)((long)register0x00000020 +
                                                                   -0x130);
                                                uVar13 = *(long *)((long)register0x00000020 + -0x138
                                                                  ) + 0x29;
                                                uVar6 = *(undefined8 *)
                                                         ((long)register0x00000020 + -0x140);
                                                if (uVar11 < uVar13) {
                                                  *(long *)((long)register0x00000020 + -0x1a0) =
                                                       *(long *)((long)register0x00000020 + -0x138);
                                                  param_1 = (undefined8 *)0x29;
                                                  *(undefined8 *)((long)register0x00000020 + -0x2c0)
                                                       = 0x1717465;
                                                  uVar6 = runtime_growslice(0x29,&DAT_0194e2a0,uVar13,
                                                                       uVar11,(undefined1 *)
                                                                              ((long)
                                                  register0x00000020 + -0x148));
                                                }
                                                *(ulong *)((long)register0x00000020 + -0x1a0) =
                                                     uVar11;
                                                *(ulong *)((long)register0x00000020 + -0x1a8) =
                                                     uVar13;
                                                *(undefined8 *)((long)register0x00000020 + -0x10) =
                                                     uVar6;
                                                param_4 = (undefined8 *)0x29;
                                                *(undefined8 *)((long)register0x00000020 + -0x2c0) =
                                                     0x171749c;
                                                runtime_memmove();
                                                *(undefined8 *)((long)register0x00000020 + -0x138) =
                                                     *(undefined8 *)
                                                      ((long)register0x00000020 + -0x1a8);
                                                *(undefined8 *)((long)register0x00000020 + -0x130) =
                                                     *(undefined8 *)
                                                      ((long)register0x00000020 + -0x1a0);
                                                *(undefined8 *)((long)register0x00000020 + -0x140) =
                                                     *(undefined8 *)
                                                      ((long)register0x00000020 + -0x10);
                                                if (*(undefined1 **)
                                                     ((long)register0x00000020 + -0x148) ==
                                                    (undefined1 *)0x0) {
                                                  *(undefined1 **)
                                                   ((long)register0x00000020 + -0x148) =
                                                       (undefined1 *)
                                                       ((long)register0x00000020 + -0x148);
LAB_01717505:
                                                  param_4 = *(undefined8 **)
                                                             ((long)register0x00000020 + -0x130);
                                                  lVar7 = *(long *)((long)register0x00000020 +
                                                                   -0x138);
                                                  puVar12 = (undefined8 *)(lVar7 + 1);
                                                  lVar8 = *(long *)((long)register0x00000020 +
                                                                   -0x140);
                                                  if (param_4 < puVar12) {
                                                    *(long *)((long)register0x00000020 + -0x1a0) =
                                                         lVar7;
                                                    param_1 = (undefined8 *)0x1;
                                                    *(undefined8 *)
                                                     ((long)register0x00000020 + -0x2c0) = 0x1717545
                                                    ;
                                                    lVar8 = runtime_growslice(1,&DAT_0194e2a0);
                                                    lVar7 = *(long *)((long)register0x00000020 +
                                                                     -0x1a0);
                                                  }
                                                  *(undefined1 *)(lVar8 + lVar7) = 10;
                                                  *(undefined8 **)
                                                   ((long)register0x00000020 + -0x138) = puVar12;
                                                  *(undefined8 **)
                                                   ((long)register0x00000020 + -0x130) = param_4;
                                                  *(long *)((long)register0x00000020 + -0x140) =
                                                       lVar8;
                                                  if (*(undefined1 **)
                                                       ((long)register0x00000020 + -0x148) ==
                                                      (undefined1 *)0x0) {
                                                    *(undefined1 **)
                                                     ((long)register0x00000020 + -0x148) =
                                                         (undefined1 *)
                                                         ((long)register0x00000020 + -0x148);
LAB_01717597:
                                                    uVar11 = *(ulong *)((long)register0x00000020 +
                                                                       -0x130);
                                                    uVar13 = *(long *)((long)register0x00000020 +
                                                                      -0x138) + 0x1c;
                                                    uVar6 = *(undefined8 *)
                                                             ((long)register0x00000020 + -0x140);
                                                    if (uVar11 < uVar13) {
                                                      *(long *)((long)register0x00000020 + -0x1a0) =
                                                           *(long *)((long)register0x00000020 +
                                                                    -0x138);
                                                      param_1 = (undefined8 *)0x1c;
                                                      *(undefined8 *)
                                                       ((long)register0x00000020 + -0x2c0) =
                                                           0x17175d4;
                                                      uVar6 = runtime_growslice(0x1c,&DAT_0194e2a0);
                                                    }
                                                    *(ulong *)((long)register0x00000020 + -0x1a0) =
                                                         uVar11;
                                                    *(ulong *)((long)register0x00000020 + -0x1a8) =
                                                         uVar13;
                                                    *(undefined8 *)
                                                     ((long)register0x00000020 + -0x10) = uVar6;
                                                    param_4 = (undefined8 *)0x1c;
                                                    *(undefined8 *)
                                                     ((long)register0x00000020 + -0x2c0) = 0x171760b
                                                    ;
                                                    runtime_memmove();
                                                    *(undefined8 *)
                                                     ((long)register0x00000020 + -0x138) =
                                                         *(undefined8 *)
                                                          ((long)register0x00000020 + -0x1a8);
                                                    *(undefined8 *)
                                                     ((long)register0x00000020 + -0x130) =
                                                         *(undefined8 *)
                                                          ((long)register0x00000020 + -0x1a0);
                                                    *(undefined8 *)
                                                     ((long)register0x00000020 + -0x140) =
                                                         *(undefined8 *)
                                                          ((long)register0x00000020 + -0x10);
                                                    if (*(undefined1 **)
                                                         ((long)register0x00000020 + -0x148) ==
                                                        (undefined1 *)0x0) {
                                                      *(undefined1 **)
                                                       ((long)register0x00000020 + -0x148) =
                                                           (undefined1 *)
                                                           ((long)register0x00000020 + -0x148);
LAB_01717674:
                                                      uVar11 = *(ulong *)((long)register0x00000020 +
                                                                         -0x130);
                                                      uVar13 = *(long *)((long)register0x00000020 +
                                                                        -0x138) + 0x25;
                                                      uVar6 = *(undefined8 *)
                                                               ((long)register0x00000020 + -0x140);
                                                      if (uVar11 < uVar13) {
                                                        *(long *)((long)register0x00000020 + -0x1a0)
                                                             = *(long *)((long)register0x00000020 +
                                                                        -0x138);
                                                        param_1 = (undefined8 *)&DAT_00000025;
                                                        *(undefined8 *)
                                                         ((long)register0x00000020 + -0x2c0) =
                                                             0x17176b1;
                                                        uVar6 = runtime_growslice(0x25,&DAT_0194e2a0,
                                                                             uVar13,uVar11,
                                                                             (undefined1 *)
                                                                             ((long)
                                                  register0x00000020 + -0x148));
                                                  }
                                                  *(ulong *)((long)register0x00000020 + -0x1a0) =
                                                       uVar11;
                                                  *(ulong *)((long)register0x00000020 + -0x1a8) =
                                                       uVar13;
                                                  *(undefined8 *)((long)register0x00000020 + -0x10)
                                                       = uVar6;
                                                  param_4 = (undefined8 *)&DAT_00000025;
                                                  *(undefined8 *)((long)register0x00000020 + -0x2c0)
                                                       = 0x17176e8;
                                                  runtime_memmove();
                                                  *(undefined8 *)((long)register0x00000020 + -0x138)
                                                       = *(undefined8 *)
                                                          ((long)register0x00000020 + -0x1a8);
                                                  *(undefined8 *)((long)register0x00000020 + -0x130)
                                                       = *(undefined8 *)
                                                          ((long)register0x00000020 + -0x1a0);
                                                  *(undefined8 *)((long)register0x00000020 + -0x140)
                                                       = *(undefined8 *)
                                                          ((long)register0x00000020 + -0x10);
                                                  if (*(undefined1 **)
                                                       ((long)register0x00000020 + -0x148) ==
                                                      (undefined1 *)0x0) {
                                                    *(undefined1 **)
                                                     ((long)register0x00000020 + -0x148) =
                                                         (undefined1 *)
                                                         ((long)register0x00000020 + -0x148);
LAB_01717751:
                                                    uVar11 = *(ulong *)((long)register0x00000020 +
                                                                       -0x130);
                                                    uVar13 = *(long *)((long)register0x00000020 +
                                                                      -0x138) + 0x49;
                                                    uVar6 = *(undefined8 *)
                                                             ((long)register0x00000020 + -0x140);
                                                    if (uVar11 < uVar13) {
                                                      *(long *)((long)register0x00000020 + -0x1a0) =
                                                           *(long *)((long)register0x00000020 +
                                                                    -0x138);
                                                      param_1 = (undefined8 *)&DAT_00000049;
                                                      *(undefined8 *)
                                                       ((long)register0x00000020 + -0x2c0) =
                                                           0x171778e;
                                                      uVar6 = runtime_growslice(0x49,&DAT_0194e2a0,uVar13
                                                                           ,uVar11,(undefined1 *)
                                                                                   ((long)
                                                  register0x00000020 + -0x148));
                                                  }
                                                  *(ulong *)((long)register0x00000020 + -0x1a0) =
                                                       uVar11;
                                                  *(ulong *)((long)register0x00000020 + -0x1a8) =
                                                       uVar13;
                                                  *(undefined8 *)((long)register0x00000020 + -0x10)
                                                       = uVar6;
                                                  param_4 = (undefined8 *)&DAT_00000049;
                                                  *(undefined8 *)((long)register0x00000020 + -0x2c0)
                                                       = 0x17177c5;
                                                  runtime_memmove();
                                                  *(undefined8 *)((long)register0x00000020 + -0x138)
                                                       = *(undefined8 *)
                                                          ((long)register0x00000020 + -0x1a8);
                                                  *(undefined8 *)((long)register0x00000020 + -0x130)
                                                       = *(undefined8 *)
                                                          ((long)register0x00000020 + -0x1a0);
                                                  *(undefined8 *)((long)register0x00000020 + -0x140)
                                                       = *(undefined8 *)
                                                          ((long)register0x00000020 + -0x10);
                                                  if (*(undefined1 **)
                                                       ((long)register0x00000020 + -0x148) ==
                                                      (undefined1 *)0x0) {
                                                    *(undefined1 **)
                                                     ((long)register0x00000020 + -0x148) =
                                                         (undefined1 *)
                                                         ((long)register0x00000020 + -0x148);
LAB_0171782f:
                                                    uVar11 = *(ulong *)((long)register0x00000020 +
                                                                       -0x130);
                                                    uVar13 = *(long *)((long)register0x00000020 +
                                                                      -0x138) + 0x41;
                                                    uVar6 = *(undefined8 *)
                                                             ((long)register0x00000020 + -0x140);
                                                    if (uVar11 < uVar13) {
                                                      *(long *)((long)register0x00000020 + -0x1a0) =
                                                           *(long *)((long)register0x00000020 +
                                                                    -0x138);
                                                      param_1 = (undefined8 *)&DAT_00000041;
                                                      *(undefined8 *)
                                                       ((long)register0x00000020 + -0x2c0) =
                                                           0x171786c;
                                                      uVar6 = runtime_growslice(0x41,&DAT_0194e2a0,uVar13
                                                                           ,uVar11,(undefined1 *)
                                                                                   ((long)
                                                  register0x00000020 + -0x148));
                                                  }
                                                  *(ulong *)((long)register0x00000020 + -0x1a0) =
                                                       uVar13;
                                                  *(ulong *)((long)register0x00000020 + -0x1a8) =
                                                       uVar11;
                                                  *(undefined8 *)((long)register0x00000020 + -0x10)
                                                       = uVar6;
                                                  param_4 = (undefined8 *)&DAT_00000041;
                                                  *(undefined8 *)((long)register0x00000020 + -0x2c0)
                                                       = 0x17178a5;
                                                  runtime_memmove();
                                                  *(undefined8 *)((long)register0x00000020 + -0x138)
                                                       = *(undefined8 *)
                                                          ((long)register0x00000020 + -0x1a0);
                                                  *(undefined8 *)((long)register0x00000020 + -0x130)
                                                       = *(undefined8 *)
                                                          ((long)register0x00000020 + -0x1a8);
                                                  *(undefined8 *)((long)register0x00000020 + -0x140)
                                                       = *(undefined8 *)
                                                          ((long)register0x00000020 + -0x10);
                                                  if (*(undefined1 **)
                                                       ((long)register0x00000020 + -0x148) ==
                                                      (undefined1 *)0x0) {
                                                    *(undefined1 **)
                                                     ((long)register0x00000020 + -0x148) =
                                                         (undefined1 *)
                                                         ((long)register0x00000020 + -0x148);
LAB_0171790f:
                                                    uVar11 = *(ulong *)((long)register0x00000020 +
                                                                       -0x130);
                                                    uVar13 = *(long *)((long)register0x00000020 +
                                                                      -0x138) + 0x28;
                                                    uVar6 = *(undefined8 *)
                                                             ((long)register0x00000020 + -0x140);
                                                    if (uVar11 < uVar13) {
                                                      *(long *)((long)register0x00000020 + -0x1a0) =
                                                           *(long *)((long)register0x00000020 +
                                                                    -0x138);
                                                      param_1 = (undefined8 *)&DAT_00000028;
                                                      *(undefined8 *)
                                                       ((long)register0x00000020 + -0x2c0) =
                                                           0x171794c;
                                                      uVar6 = runtime_growslice(0x28,&DAT_0194e2a0,uVar13
                                                                           ,uVar11,(undefined1 *)
                                                                                   ((long)
                                                  register0x00000020 + -0x148));
                                                  }
                                                  *(ulong *)((long)register0x00000020 + -0x1a0) =
                                                       uVar11;
                                                  *(ulong *)((long)register0x00000020 + -0x1a8) =
                                                       uVar13;
                                                  *(undefined8 *)((long)register0x00000020 + -0x10)
                                                       = uVar6;
                                                  param_4 = (undefined8 *)&DAT_00000028;
                                                  *(undefined8 *)((long)register0x00000020 + -0x2c0)
                                                       = 0x1717985;
                                                  runtime_memmove();
                                                  *(undefined8 *)((long)register0x00000020 + -0x138)
                                                       = *(undefined8 *)
                                                          ((long)register0x00000020 + -0x1a8);
                                                  *(undefined8 *)((long)register0x00000020 + -0x130)
                                                       = *(undefined8 *)
                                                          ((long)register0x00000020 + -0x1a0);
                                                  *(undefined8 *)((long)register0x00000020 + -0x140)
                                                       = *(undefined8 *)
                                                          ((long)register0x00000020 + -0x10);
                                                  if (*(undefined1 **)
                                                       ((long)register0x00000020 + -0x148) ==
                                                      (undefined1 *)0x0) {
                                                    *(undefined1 **)
                                                     ((long)register0x00000020 + -0x148) =
                                                         (undefined1 *)
                                                         ((long)register0x00000020 + -0x148);
LAB_017179ef:
                                                    uVar11 = *(ulong *)((long)register0x00000020 +
                                                                       -0x130);
                                                    uVar13 = *(long *)((long)register0x00000020 +
                                                                      -0x138) + 0x48;
                                                    uVar6 = *(undefined8 *)
                                                             ((long)register0x00000020 + -0x140);
                                                    if (uVar11 < uVar13) {
                                                      *(long *)((long)register0x00000020 + -0x1a0) =
                                                           *(long *)((long)register0x00000020 +
                                                                    -0x138);
                                                      param_1 = (undefined8 *)&DAT_00000048;
                                                      *(undefined8 *)
                                                       ((long)register0x00000020 + -0x2c0) =
                                                           0x1717a2c;
                                                      uVar6 = runtime_growslice(0x48,&DAT_0194e2a0,uVar13
                                                                           ,uVar11,(undefined1 *)
                                                                                   ((long)
                                                  register0x00000020 + -0x148));
                                                  }
                                                  *(ulong *)((long)register0x00000020 + -0x1a0) =
                                                       uVar11;
                                                  *(ulong *)((long)register0x00000020 + -0x1a8) =
                                                       uVar13;
                                                  *(undefined8 *)((long)register0x00000020 + -0x10)
                                                       = uVar6;
                                                  param_4 = (undefined8 *)&DAT_00000048;
                                                  *(undefined8 *)((long)register0x00000020 + -0x2c0)
                                                       = 0x1717a65;
                                                  runtime_memmove();
                                                  *(undefined8 *)((long)register0x00000020 + -0x138)
                                                       = *(undefined8 *)
                                                          ((long)register0x00000020 + -0x1a8);
                                                  *(undefined8 *)((long)register0x00000020 + -0x130)
                                                       = *(undefined8 *)
                                                          ((long)register0x00000020 + -0x1a0);
                                                  *(undefined8 *)((long)register0x00000020 + -0x140)
                                                       = *(undefined8 *)
                                                          ((long)register0x00000020 + -0x10);
                                                  if (*(undefined1 **)
                                                       ((long)register0x00000020 + -0x148) ==
                                                      (undefined1 *)0x0) {
                                                    *(undefined1 **)
                                                     ((long)register0x00000020 + -0x148) =
                                                         (undefined1 *)
                                                         ((long)register0x00000020 + -0x148);
LAB_01717acf:
                                                    param_4 = *(undefined8 **)
                                                               ((long)register0x00000020 + -0x130);
                                                    lVar7 = *(long *)((long)register0x00000020 +
                                                                     -0x138);
                                                    puVar12 = (undefined8 *)(lVar7 + 1);
                                                    lVar8 = *(long *)((long)register0x00000020 +
                                                                     -0x140);
                                                    if (param_4 < puVar12) {
                                                      *(long *)((long)register0x00000020 + -0x1a0) =
                                                           lVar7;
                                                      param_1 = (undefined8 *)0x1;
                                                      *(undefined8 *)
                                                       ((long)register0x00000020 + -0x2c0) =
                                                           0x1717b0c;
                                                      lVar8 = runtime_growslice(1,&DAT_0194e2a0);
                                                      lVar7 = *(long *)((long)register0x00000020 +
                                                                       -0x1a0);
                                                    }
                                                    *(undefined1 *)(lVar8 + lVar7) = 10;
                                                    *(undefined8 **)
                                                     ((long)register0x00000020 + -0x138) = puVar12;
                                                    *(undefined8 **)
                                                     ((long)register0x00000020 + -0x130) = param_4;
                                                    *(long *)((long)register0x00000020 + -0x140) =
                                                         lVar8;
                                                    if (*(undefined1 **)
                                                         ((long)register0x00000020 + -0x148) ==
                                                        (undefined1 *)0x0) {
                                                      *(undefined1 **)
                                                       ((long)register0x00000020 + -0x148) =
                                                           (undefined1 *)
                                                           ((long)register0x00000020 + -0x148);
LAB_01717b5c:
                                                      uVar11 = *(ulong *)((long)register0x00000020 +
                                                                         -0x130);
                                                      uVar13 = *(long *)((long)register0x00000020 +
                                                                        -0x138) + 0x1d;
                                                      uVar6 = *(undefined8 *)
                                                               ((long)register0x00000020 + -0x140);
                                                      if (uVar11 < uVar13) {
                                                        *(long *)((long)register0x00000020 + -0x1a0)
                                                             = *(long *)((long)register0x00000020 +
                                                                        -0x138);
                                                        param_1 = (undefined8 *)&DAT_0000001d;
                                                        *(undefined8 *)
                                                         ((long)register0x00000020 + -0x2c0) =
                                                             0x1717b99;
                                                        uVar6 = runtime_growslice(0x1d,&DAT_0194e2a0);
                                                      }
                                                      *(ulong *)((long)register0x00000020 + -0x1a0)
                                                           = uVar13;
                                                      *(ulong *)((long)register0x00000020 + -0x1a8)
                                                           = uVar11;
                                                      *(undefined8 *)
                                                       ((long)register0x00000020 + -0x10) = uVar6;
                                                      param_4 = (undefined8 *)&DAT_0000001d;
                                                      *(undefined8 *)
                                                       ((long)register0x00000020 + -0x2c0) =
                                                           0x1717bd0;
                                                      runtime_memmove();
                                                      *(undefined8 *)
                                                       ((long)register0x00000020 + -0x138) =
                                                           *(undefined8 *)
                                                            ((long)register0x00000020 + -0x1a0);
                                                      *(undefined8 *)
                                                       ((long)register0x00000020 + -0x130) =
                                                           *(undefined8 *)
                                                            ((long)register0x00000020 + -0x1a8);
                                                      *(undefined8 *)
                                                       ((long)register0x00000020 + -0x140) =
                                                           *(undefined8 *)
                                                            ((long)register0x00000020 + -0x10);
                                                      if (*(undefined1 **)
                                                           ((long)register0x00000020 + -0x148) ==
                                                          (undefined1 *)0x0) {
                                                        *(undefined1 **)
                                                         ((long)register0x00000020 + -0x148) =
                                                             (undefined1 *)
                                                             ((long)register0x00000020 + -0x148);
LAB_01717c3d:
                                                        uVar11 = *(ulong *)((long)register0x00000020
                                                                           + -0x130);
                                                        uVar13 = *(long *)((long)register0x00000020
                                                                          + -0x138) + 0x55;
                                                        uVar6 = *(undefined8 *)
                                                                 ((long)register0x00000020 + -0x140)
                                                        ;
                                                        if (uVar11 < uVar13) {
                                                          *(long *)((long)register0x00000020 +
                                                                   -0x1a0) =
                                                               *(long *)((long)register0x00000020 +
                                                                        -0x138);
                                                          param_1 = (undefined8 *)0x55;
                                                          *(undefined8 *)
                                                           ((long)register0x00000020 + -0x2c0) =
                                                               0x1717c7a;
                                                          uVar6 = runtime_growslice(0x55,&DAT_0194e2a0,
                                                                               uVar13,uVar11,
                                                                               (undefined1 *)
                                                                               ((long)
                                                  register0x00000020 + -0x148));
                                                  }
                                                  *(ulong *)((long)register0x00000020 + -0x1a0) =
                                                       uVar11;
                                                  *(ulong *)((long)register0x00000020 + -0x1a8) =
                                                       uVar13;
                                                  *(undefined8 *)((long)register0x00000020 + -0x10)
                                                       = uVar6;
                                                  param_4 = (undefined8 *)0x55;
                                                  *(undefined8 *)((long)register0x00000020 + -0x2c0)
                                                       = 0x1717cb1;
                                                  runtime_memmove();
                                                  *(undefined8 *)((long)register0x00000020 + -0x138)
                                                       = *(undefined8 *)
                                                          ((long)register0x00000020 + -0x1a8);
                                                  *(undefined8 *)((long)register0x00000020 + -0x130)
                                                       = *(undefined8 *)
                                                          ((long)register0x00000020 + -0x1a0);
                                                  *(undefined8 *)((long)register0x00000020 + -0x140)
                                                       = *(undefined8 *)
                                                          ((long)register0x00000020 + -0x10);
                                                  if (*(undefined1 **)
                                                       ((long)register0x00000020 + -0x148) ==
                                                      (undefined1 *)0x0) {
                                                    *(undefined1 **)
                                                     ((long)register0x00000020 + -0x148) =
                                                         (undefined1 *)
                                                         ((long)register0x00000020 + -0x148);
LAB_01717d1d:
                                                    uVar11 = *(ulong *)((long)register0x00000020 +
                                                                       -0x130);
                                                    uVar13 = *(long *)((long)register0x00000020 +
                                                                      -0x138) + 0x65;
                                                    uVar6 = *(undefined8 *)
                                                             ((long)register0x00000020 + -0x140);
                                                    if (uVar11 < uVar13) {
                                                      *(long *)((long)register0x00000020 + -0x1a0) =
                                                           *(long *)((long)register0x00000020 +
                                                                    -0x138);
                                                      param_1 = (undefined8 *)0x65;
                                                      *(undefined8 *)
                                                       ((long)register0x00000020 + -0x2c0) =
                                                           0x1717d5a;
                                                      uVar6 = runtime_growslice(0x65,&DAT_0194e2a0,uVar13
                                                                           ,uVar11,(undefined1 *)
                                                                                   ((long)
                                                  register0x00000020 + -0x148));
                                                  }
                                                  *(ulong *)((long)register0x00000020 + -0x1a0) =
                                                       uVar11;
                                                  *(ulong *)((long)register0x00000020 + -0x1a8) =
                                                       uVar13;
                                                  *(undefined8 *)((long)register0x00000020 + -0x10)
                                                       = uVar6;
                                                  param_4 = (undefined8 *)0x65;
                                                  *(undefined8 *)((long)register0x00000020 + -0x2c0)
                                                       = 0x1717d91;
                                                  runtime_memmove();
                                                  *(undefined8 *)((long)register0x00000020 + -0x138)
                                                       = *(undefined8 *)
                                                          ((long)register0x00000020 + -0x1a8);
                                                  *(undefined8 *)((long)register0x00000020 + -0x130)
                                                       = *(undefined8 *)
                                                          ((long)register0x00000020 + -0x1a0);
                                                  *(undefined8 *)((long)register0x00000020 + -0x140)
                                                       = *(undefined8 *)
                                                          ((long)register0x00000020 + -0x10);
                                                  if (*(undefined1 **)
                                                       ((long)register0x00000020 + -0x148) ==
                                                      (undefined1 *)0x0) {
                                                    *(undefined1 **)
                                                     ((long)register0x00000020 + -0x148) =
                                                         (undefined1 *)
                                                         ((long)register0x00000020 + -0x148);
LAB_01717dfd:
                                                    uVar11 = *(ulong *)((long)register0x00000020 +
                                                                       -0x130);
                                                    uVar13 = *(long *)((long)register0x00000020 +
                                                                      -0x138) + 0x5e;
                                                    uVar6 = *(undefined8 *)
                                                             ((long)register0x00000020 + -0x140);
                                                    if (uVar11 < uVar13) {
                                                      *(long *)((long)register0x00000020 + -0x1a0) =
                                                           *(long *)((long)register0x00000020 +
                                                                    -0x138);
                                                      param_1 = (undefined8 *)0x5e;
                                                      *(undefined8 *)
                                                       ((long)register0x00000020 + -0x2c0) =
                                                           0x1717e3a;
                                                      uVar6 = runtime_growslice(0x5e,&DAT_0194e2a0,uVar13
                                                                           ,uVar11,(undefined1 *)
                                                                                   ((long)
                                                  register0x00000020 + -0x148));
                                                  }
                                                  *(ulong *)((long)register0x00000020 + -0x1a0) =
                                                       uVar11;
                                                  *(ulong *)((long)register0x00000020 + -0x1a8) =
                                                       uVar13;
                                                  *(undefined8 *)((long)register0x00000020 + -0x10)
                                                       = uVar6;
                                                  param_4 = (undefined8 *)0x5e;
                                                  *(undefined8 *)((long)register0x00000020 + -0x2c0)
                                                       = 0x1717e71;
                                                  runtime_memmove();
                                                  *(undefined8 *)((long)register0x00000020 + -0x138)
                                                       = *(undefined8 *)
                                                          ((long)register0x00000020 + -0x1a8);
                                                  *(undefined8 *)((long)register0x00000020 + -0x130)
                                                       = *(undefined8 *)
                                                          ((long)register0x00000020 + -0x1a0);
                                                  *(undefined8 *)((long)register0x00000020 + -0x140)
                                                       = *(undefined8 *)
                                                          ((long)register0x00000020 + -0x10);
                                                  if (*(undefined1 **)
                                                       ((long)register0x00000020 + -0x148) ==
                                                      (undefined1 *)0x0) {
                                                    *(undefined1 **)
                                                     ((long)register0x00000020 + -0x148) =
                                                         (undefined1 *)
                                                         ((long)register0x00000020 + -0x148);
LAB_01717edd:
                                                    uVar11 = *(ulong *)((long)register0x00000020 +
                                                                       -0x130);
                                                    uVar13 = *(long *)((long)register0x00000020 +
                                                                      -0x138) + 0x5e;
                                                    uVar6 = *(undefined8 *)
                                                             ((long)register0x00000020 + -0x140);
                                                    if (uVar11 < uVar13) {
                                                      *(long *)((long)register0x00000020 + -0x1a0) =
                                                           *(long *)((long)register0x00000020 +
                                                                    -0x138);
                                                      param_1 = (undefined8 *)0x5e;
                                                      *(undefined8 *)
                                                       ((long)register0x00000020 + -0x2c0) =
                                                           0x1717f1a;
                                                      uVar6 = runtime_growslice(0x5e,&DAT_0194e2a0,uVar13
                                                                           ,uVar11,(undefined1 *)
                                                                                   ((long)
                                                  register0x00000020 + -0x148));
                                                  }
                                                  *(ulong *)((long)register0x00000020 + -0x1a0) =
                                                       uVar11;
                                                  *(ulong *)((long)register0x00000020 + -0x1a8) =
                                                       uVar13;
                                                  *(undefined8 *)((long)register0x00000020 + -0x10)
                                                       = uVar6;
                                                  param_4 = (undefined8 *)0x5e;
                                                  *(undefined8 *)((long)register0x00000020 + -0x2c0)
                                                       = 0x1717f51;
                                                  runtime_memmove();
                                                  *(undefined8 *)((long)register0x00000020 + -0x138)
                                                       = *(undefined8 *)
                                                          ((long)register0x00000020 + -0x1a8);
                                                  *(undefined8 *)((long)register0x00000020 + -0x130)
                                                       = *(undefined8 *)
                                                          ((long)register0x00000020 + -0x1a0);
                                                  *(undefined8 *)((long)register0x00000020 + -0x140)
                                                       = *(undefined8 *)
                                                          ((long)register0x00000020 + -0x10);
                                                  if (*(undefined1 **)
                                                       ((long)register0x00000020 + -0x148) ==
                                                      (undefined1 *)0x0) {
                                                    *(undefined1 **)
                                                     ((long)register0x00000020 + -0x148) =
                                                         (undefined1 *)
                                                         ((long)register0x00000020 + -0x148);
LAB_01717fbd:
                                                    uVar11 = *(ulong *)((long)register0x00000020 +
                                                                       -0x130);
                                                    uVar13 = *(long *)((long)register0x00000020 +
                                                                      -0x138) + 0x54;
                                                    uVar6 = *(undefined8 *)
                                                             ((long)register0x00000020 + -0x140);
                                                    if (uVar11 < uVar13) {
                                                      *(long *)((long)register0x00000020 + -0x1a0) =
                                                           *(long *)((long)register0x00000020 +
                                                                    -0x138);
                                                      param_1 = (undefined8 *)0x54;
                                                      *(undefined8 *)
                                                       ((long)register0x00000020 + -0x2c0) =
                                                           0x1717ffa;
                                                      uVar6 = runtime_growslice(0x54,&DAT_0194e2a0,uVar13
                                                                           ,uVar11,(undefined1 *)
                                                                                   ((long)
                                                  register0x00000020 + -0x148));
                                                  }
                                                  *(ulong *)((long)register0x00000020 + -0x1a0) =
                                                       uVar11;
                                                  *(ulong *)((long)register0x00000020 + -0x1a8) =
                                                       uVar13;
                                                  *(undefined8 *)((long)register0x00000020 + -0x10)
                                                       = uVar6;
                                                  param_4 = (undefined8 *)0x54;
                                                  *(undefined8 *)((long)register0x00000020 + -0x2c0)
                                                       = 0x1718031;
                                                  runtime_memmove();
                                                  *(undefined8 *)((long)register0x00000020 + -0x138)
                                                       = *(undefined8 *)
                                                          ((long)register0x00000020 + -0x1a8);
                                                  *(undefined8 *)((long)register0x00000020 + -0x130)
                                                       = *(undefined8 *)
                                                          ((long)register0x00000020 + -0x1a0);
                                                  *(undefined8 *)((long)register0x00000020 + -0x140)
                                                       = *(undefined8 *)
                                                          ((long)register0x00000020 + -0x10);
                                                  if (*(undefined1 **)
                                                       ((long)register0x00000020 + -0x148) ==
                                                      (undefined1 *)0x0) {
                                                    *(undefined1 **)
                                                     ((long)register0x00000020 + -0x148) =
                                                         (undefined1 *)
                                                         ((long)register0x00000020 + -0x148);
LAB_0171809d:
                                                    param_4 = *(undefined8 **)
                                                               ((long)register0x00000020 + -0x130);
                                                    lVar7 = *(long *)((long)register0x00000020 +
                                                                     -0x138);
                                                    puVar12 = (undefined8 *)(lVar7 + 1);
                                                    lVar8 = *(long *)((long)register0x00000020 +
                                                                     -0x140);
                                                    if (param_4 < puVar12) {
                                                      *(long *)((long)register0x00000020 + -0x1a0) =
                                                           lVar7;
                                                      param_1 = (undefined8 *)0x1;
                                                      *(undefined8 *)
                                                       ((long)register0x00000020 + -0x2c0) =
                                                           0x17180da;
                                                      lVar8 = runtime_growslice(1,&DAT_0194e2a0);
                                                      lVar7 = *(long *)((long)register0x00000020 +
                                                                       -0x1a0);
                                                    }
                                                    *(undefined1 *)(lVar8 + lVar7) = 10;
                                                    *(undefined8 **)
                                                     ((long)register0x00000020 + -0x138) = puVar12;
                                                    *(undefined8 **)
                                                     ((long)register0x00000020 + -0x130) = param_4;
                                                    *(long *)((long)register0x00000020 + -0x140) =
                                                         lVar8;
                                                    if (*(undefined1 **)
                                                         ((long)register0x00000020 + -0x148) ==
                                                        (undefined1 *)0x0) {
                                                      *(undefined1 **)
                                                       ((long)register0x00000020 + -0x148) =
                                                           (undefined1 *)
                                                           ((long)register0x00000020 + -0x148);
LAB_0171812d:
                                                      uVar11 = *(ulong *)((long)register0x00000020 +
                                                                         -0x130);
                                                      uVar13 = *(long *)((long)register0x00000020 +
                                                                        -0x138) + 0x14;
                                                      uVar6 = *(undefined8 *)
                                                               ((long)register0x00000020 + -0x140);
                                                      if (uVar11 < uVar13) {
                                                        *(long *)((long)register0x00000020 + -0x1a0)
                                                             = *(long *)((long)register0x00000020 +
                                                                        -0x138);
                                                        param_1 = (undefined8 *)0x14;
                                                        *(undefined8 *)
                                                         ((long)register0x00000020 + -0x2c0) =
                                                             0x171816a;
                                                        uVar6 = runtime_growslice(0x14,&DAT_0194e2a0);
                                                      }
                                                      *(ulong *)((long)register0x00000020 + -0x1a0)
                                                           = uVar11;
                                                      *(ulong *)((long)register0x00000020 + -0x1a8)
                                                           = uVar13;
                                                      *(undefined8 *)
                                                       ((long)register0x00000020 + -0x10) = uVar6;
                                                      param_4 = (undefined8 *)0x14;
                                                      *(undefined8 *)
                                                       ((long)register0x00000020 + -0x2c0) =
                                                           0x17181a5;
                                                      runtime_memmove();
                                                      *(undefined8 *)
                                                       ((long)register0x00000020 + -0x138) =
                                                           *(undefined8 *)
                                                            ((long)register0x00000020 + -0x1a8);
                                                      *(undefined8 *)
                                                       ((long)register0x00000020 + -0x130) =
                                                           *(undefined8 *)
                                                            ((long)register0x00000020 + -0x1a0);
                                                      *(undefined8 *)
                                                       ((long)register0x00000020 + -0x140) =
                                                           *(undefined8 *)
                                                            ((long)register0x00000020 + -0x10);
                                                      if (*(undefined1 **)
                                                           ((long)register0x00000020 + -0x148) ==
                                                          (undefined1 *)0x0) {
                                                        *(undefined1 **)
                                                         ((long)register0x00000020 + -0x148) =
                                                             (undefined1 *)
                                                             ((long)register0x00000020 + -0x148);
LAB_0171820f:
                                                        uVar11 = *(ulong *)((long)register0x00000020
                                                                           + -0x130);
                                                        uVar13 = *(long *)((long)register0x00000020
                                                                          + -0x138) + 0x23;
                                                        uVar6 = *(undefined8 *)
                                                                 ((long)register0x00000020 + -0x140)
                                                        ;
                                                        if (uVar11 < uVar13) {
                                                          *(long *)((long)register0x00000020 +
                                                                   -0x1a0) =
                                                               *(long *)((long)register0x00000020 +
                                                                        -0x138);
                                                          param_1 = (undefined8 *)&DAT_00000023;
                                                          *(undefined8 *)
                                                           ((long)register0x00000020 + -0x2c0) =
                                                               0x171824c;
                                                          uVar6 = runtime_growslice(0x23,&DAT_0194e2a0,
                                                                               uVar13,uVar11,
                                                                               (undefined1 *)
                                                                               ((long)
                                                  register0x00000020 + -0x148));
                                                  }
                                                  *(ulong *)((long)register0x00000020 + -0x1a0) =
                                                       uVar11;
                                                  *(ulong *)((long)register0x00000020 + -0x1a8) =
                                                       uVar13;
                                                  *(undefined8 *)((long)register0x00000020 + -0x10)
                                                       = uVar6;
                                                  param_4 = (undefined8 *)&DAT_00000023;
                                                  *(undefined8 *)((long)register0x00000020 + -0x2c0)
                                                       = 0x1718285;
                                                  runtime_memmove();
                                                  *(undefined8 *)((long)register0x00000020 + -0x138)
                                                       = *(undefined8 *)
                                                          ((long)register0x00000020 + -0x1a8);
                                                  *(undefined8 *)((long)register0x00000020 + -0x130)
                                                       = *(undefined8 *)
                                                          ((long)register0x00000020 + -0x1a0);
                                                  *(undefined8 *)((long)register0x00000020 + -0x140)
                                                       = *(undefined8 *)
                                                          ((long)register0x00000020 + -0x10);
                                                  if (*(undefined1 **)
                                                       ((long)register0x00000020 + -0x148) ==
                                                      (undefined1 *)0x0) {
                                                    *(undefined1 **)
                                                     ((long)register0x00000020 + -0x148) =
                                                         (undefined1 *)
                                                         ((long)register0x00000020 + -0x148);
LAB_017182ef:
                                                    uVar11 = *(ulong *)((long)register0x00000020 +
                                                                       -0x130);
                                                    uVar13 = *(long *)((long)register0x00000020 +
                                                                      -0x138) + 0x27;
                                                    uVar6 = *(undefined8 *)
                                                             ((long)register0x00000020 + -0x140);
                                                    if (uVar11 < uVar13) {
                                                      *(long *)((long)register0x00000020 + -0x1a0) =
                                                           *(long *)((long)register0x00000020 +
                                                                    -0x138);
                                                      param_1 = (undefined8 *)&DAT_00000027;
                                                      *(undefined8 *)
                                                       ((long)register0x00000020 + -0x2c0) =
                                                           0x171832c;
                                                      uVar6 = runtime_growslice(0x27,&DAT_0194e2a0,uVar13
                                                                           ,uVar11,(undefined1 *)
                                                                                   ((long)
                                                  register0x00000020 + -0x148));
                                                  }
                                                  *(ulong *)((long)register0x00000020 + -0x1a0) =
                                                       uVar11;
                                                  *(ulong *)((long)register0x00000020 + -0x1a8) =
                                                       uVar13;
                                                  *(undefined8 *)((long)register0x00000020 + -0x10)
                                                       = uVar6;
                                                  param_4 = (undefined8 *)&DAT_00000027;
                                                  *(undefined8 *)((long)register0x00000020 + -0x2c0)
                                                       = 0x1718365;
                                                  runtime_memmove();
                                                  *(undefined8 *)((long)register0x00000020 + -0x138)
                                                       = *(undefined8 *)
                                                          ((long)register0x00000020 + -0x1a8);
                                                  *(undefined8 *)((long)register0x00000020 + -0x130)
                                                       = *(undefined8 *)
                                                          ((long)register0x00000020 + -0x1a0);
                                                  *(undefined8 *)((long)register0x00000020 + -0x140)
                                                       = *(undefined8 *)
                                                          ((long)register0x00000020 + -0x10);
                                                  if (*(undefined1 **)
                                                       ((long)register0x00000020 + -0x148) ==
                                                      (undefined1 *)0x0) {
                                                    *(undefined1 **)
                                                     ((long)register0x00000020 + -0x148) =
                                                         (undefined1 *)
                                                         ((long)register0x00000020 + -0x148);
LAB_017183cf:
                                                    param_4 = *(undefined8 **)
                                                               ((long)register0x00000020 + -0x130);
                                                    lVar7 = *(long *)((long)register0x00000020 +
                                                                     -0x138);
                                                    puVar12 = (undefined8 *)(lVar7 + 1);
                                                    lVar8 = *(long *)((long)register0x00000020 +
                                                                     -0x140);
                                                    if (param_4 < puVar12) {
                                                      *(long *)((long)register0x00000020 + -0x1a0) =
                                                           lVar7;
                                                      param_1 = (undefined8 *)0x1;
                                                      *(undefined8 *)
                                                       ((long)register0x00000020 + -0x2c0) =
                                                           0x171840c;
                                                      lVar8 = runtime_growslice(1,&DAT_0194e2a0);
                                                      lVar7 = *(long *)((long)register0x00000020 +
                                                                       -0x1a0);
                                                    }
                                                    *(undefined1 *)(lVar8 + lVar7) = 10;
                                                    *(undefined8 **)
                                                     ((long)register0x00000020 + -0x138) = puVar12;
                                                    *(undefined8 **)
                                                     ((long)register0x00000020 + -0x130) = param_4;
                                                    *(long *)((long)register0x00000020 + -0x140) =
                                                         lVar8;
                                                    if (*(undefined1 **)
                                                         ((long)register0x00000020 + -0x148) ==
                                                        (undefined1 *)0x0) {
                                                      *(undefined1 **)
                                                       ((long)register0x00000020 + -0x148) =
                                                           (undefined1 *)
                                                           ((long)register0x00000020 + -0x148);
LAB_0171845c:
                                                      uVar11 = *(ulong *)((long)register0x00000020 +
                                                                         -0x130);
                                                      uVar13 = *(long *)((long)register0x00000020 +
                                                                        -0x138) + 0x16;
                                                      uVar6 = *(undefined8 *)
                                                               ((long)register0x00000020 + -0x140);
                                                      if (uVar11 < uVar13) {
                                                        *(long *)((long)register0x00000020 + -0x1a0)
                                                             = *(long *)((long)register0x00000020 +
                                                                        -0x138);
                                                        param_1 = (undefined8 *)0x16;
                                                        *(undefined8 *)
                                                         ((long)register0x00000020 + -0x2c0) =
                                                             0x1718499;
                                                        uVar6 = runtime_growslice(0x16,&DAT_0194e2a0);
                                                      }
                                                      *(undefined8 *)
                                                       ((long)register0x00000020 + -0x10) = uVar6;
                                                      *(ulong *)((long)register0x00000020 + -0x1a0)
                                                           = uVar11;
                                                      *(ulong *)((long)register0x00000020 + -0x1a8)
                                                           = uVar13;
                                                      param_4 = (undefined8 *)0x16;
                                                      *(undefined8 *)
                                                       ((long)register0x00000020 + -0x2c0) =
                                                           0x17184d0;
                                                      runtime_memmove();
                                                      *(undefined8 *)
                                                       ((long)register0x00000020 + -0x138) =
                                                           *(undefined8 *)
                                                            ((long)register0x00000020 + -0x1a8);
                                                      *(undefined8 *)
                                                       ((long)register0x00000020 + -0x130) =
                                                           *(undefined8 *)
                                                            ((long)register0x00000020 + -0x1a0);
                                                      *(undefined8 *)
                                                       ((long)register0x00000020 + -0x140) =
                                                           *(undefined8 *)
                                                            ((long)register0x00000020 + -0x10);
                                                      if (*(undefined1 **)
                                                           ((long)register0x00000020 + -0x148) ==
                                                          (undefined1 *)0x0) {
                                                        *(undefined1 **)
                                                         ((long)register0x00000020 + -0x148) =
                                                             (undefined1 *)
                                                             ((long)register0x00000020 + -0x148);
LAB_0171853d:
                                                        uVar11 = *(ulong *)((long)register0x00000020
                                                                           + -0x130);
                                                        uVar13 = *(long *)((long)register0x00000020
                                                                          + -0x138) + 0x23;
                                                        uVar6 = *(undefined8 *)
                                                                 ((long)register0x00000020 + -0x140)
                                                        ;
                                                        if (uVar11 < uVar13) {
                                                          *(long *)((long)register0x00000020 +
                                                                   -0x1a0) =
                                                               *(long *)((long)register0x00000020 +
                                                                        -0x138);
                                                          param_1 = (undefined8 *)&DAT_00000023;
                                                          *(undefined8 *)
                                                           ((long)register0x00000020 + -0x2c0) =
                                                               0x171857a;
                                                          uVar6 = runtime_growslice(0x23,&DAT_0194e2a0,
                                                                               uVar13,uVar11,
                                                                               (undefined1 *)
                                                                               ((long)
                                                  register0x00000020 + -0x148));
                                                  }
                                                  *(ulong *)((long)register0x00000020 + -0x1a0) =
                                                       uVar11;
                                                  *(ulong *)((long)register0x00000020 + -0x1a8) =
                                                       uVar13;
                                                  *(undefined8 *)((long)register0x00000020 + -0x10)
                                                       = uVar6;
                                                  param_4 = (undefined8 *)&DAT_00000023;
                                                  *(undefined8 *)((long)register0x00000020 + -0x2c0)
                                                       = 0x17185b1;
                                                  runtime_memmove();
                                                  *(undefined8 *)((long)register0x00000020 + -0x138)
                                                       = *(undefined8 *)
                                                          ((long)register0x00000020 + -0x1a8);
                                                  *(undefined8 *)((long)register0x00000020 + -0x130)
                                                       = *(undefined8 *)
                                                          ((long)register0x00000020 + -0x1a0);
                                                  *(undefined8 *)((long)register0x00000020 + -0x140)
                                                       = *(undefined8 *)
                                                          ((long)register0x00000020 + -0x10);
                                                  if (*(undefined1 **)
                                                       ((long)register0x00000020 + -0x148) ==
                                                      (undefined1 *)0x0) {
                                                    *(undefined1 **)
                                                     ((long)register0x00000020 + -0x148) =
                                                         (undefined1 *)
                                                         ((long)register0x00000020 + -0x148);
LAB_0171861d:
                                                    uVar11 = *(ulong *)((long)register0x00000020 +
                                                                       -0x130);
                                                    uVar13 = *(long *)((long)register0x00000020 +
                                                                      -0x138) + 0x1f;
                                                    uVar6 = *(undefined8 *)
                                                             ((long)register0x00000020 + -0x140);
                                                    if (uVar11 < uVar13) {
                                                      *(long *)((long)register0x00000020 + -0x1a0) =
                                                           *(long *)((long)register0x00000020 +
                                                                    -0x138);
                                                      param_1 = (undefined8 *)&DAT_0000001f;
                                                      *(undefined8 *)
                                                       ((long)register0x00000020 + -0x2c0) =
                                                           0x171865a;
                                                      uVar6 = runtime_growslice(0x1f,&DAT_0194e2a0,uVar13
                                                                           ,uVar11,(undefined1 *)
                                                                                   ((long)
                                                  register0x00000020 + -0x148));
                                                  }
                                                  *(ulong *)((long)register0x00000020 + -0x1a0) =
                                                       uVar11;
                                                  *(ulong *)((long)register0x00000020 + -0x1a8) =
                                                       uVar13;
                                                  *(undefined8 *)((long)register0x00000020 + -0x10)
                                                       = uVar6;
                                                  param_4 = (undefined8 *)&DAT_0000001f;
                                                  *(undefined8 *)((long)register0x00000020 + -0x2c0)
                                                       = 0x1718691;
                                                  runtime_memmove();
                                                  *(undefined8 *)((long)register0x00000020 + -0x138)
                                                       = *(undefined8 *)
                                                          ((long)register0x00000020 + -0x1a8);
                                                  *(undefined8 *)((long)register0x00000020 + -0x130)
                                                       = *(undefined8 *)
                                                          ((long)register0x00000020 + -0x1a0);
                                                  *(undefined8 *)((long)register0x00000020 + -0x140)
                                                       = *(undefined8 *)
                                                          ((long)register0x00000020 + -0x10);
                                                  if (*(undefined1 **)
                                                       ((long)register0x00000020 + -0x148) ==
                                                      (undefined1 *)0x0) {
                                                    *(undefined1 **)
                                                     ((long)register0x00000020 + -0x148) =
                                                         (undefined1 *)
                                                         ((long)register0x00000020 + -0x148);
LAB_017186fd:
                                                    uVar11 = *(ulong *)((long)register0x00000020 +
                                                                       -0x130);
                                                    uVar13 = *(long *)((long)register0x00000020 +
                                                                      -0x138) + 0x1b;
                                                    uVar6 = *(undefined8 *)
                                                             ((long)register0x00000020 + -0x140);
                                                    if (uVar11 < uVar13) {
                                                      *(long *)((long)register0x00000020 + -0x1a0) =
                                                           *(long *)((long)register0x00000020 +
                                                                    -0x138);
                                                      param_1 = (undefined8 *)&DAT_0000001b;
                                                      *(undefined8 *)
                                                       ((long)register0x00000020 + -0x2c0) =
                                                           0x171873a;
                                                      uVar6 = runtime_growslice(0x1b,&DAT_0194e2a0,uVar13
                                                                           ,uVar11,(undefined1 *)
                                                                                   ((long)
                                                  register0x00000020 + -0x148));
                                                  }
                                                  *(ulong *)((long)register0x00000020 + -0x1a0) =
                                                       uVar11;
                                                  *(ulong *)((long)register0x00000020 + -0x1a8) =
                                                       uVar13;
                                                  *(undefined8 *)((long)register0x00000020 + -0x10)
                                                       = uVar6;
                                                  param_4 = (undefined8 *)&DAT_0000001b;
                                                  *(undefined8 *)((long)register0x00000020 + -0x2c0)
                                                       = 0x1718771;
                                                  runtime_memmove();
                                                  *(undefined8 *)((long)register0x00000020 + -0x138)
                                                       = *(undefined8 *)
                                                          ((long)register0x00000020 + -0x1a8);
                                                  *(undefined8 *)((long)register0x00000020 + -0x130)
                                                       = *(undefined8 *)
                                                          ((long)register0x00000020 + -0x1a0);
                                                  *(undefined8 *)((long)register0x00000020 + -0x140)
                                                       = *(undefined8 *)
                                                          ((long)register0x00000020 + -0x10);
                                                  if (*(undefined1 **)
                                                       ((long)register0x00000020 + -0x148) ==
                                                      (undefined1 *)0x0) {
                                                    *(undefined1 **)
                                                     ((long)register0x00000020 + -0x148) =
                                                         (undefined1 *)
                                                         ((long)register0x00000020 + -0x148);
LAB_017187dd:
                                                    param_4 = *(undefined8 **)
                                                               ((long)register0x00000020 + -0x130);
                                                    lVar7 = *(long *)((long)register0x00000020 +
                                                                     -0x138);
                                                    puVar12 = (undefined8 *)(lVar7 + 1);
                                                    lVar8 = *(long *)((long)register0x00000020 +
                                                                     -0x140);
                                                    if (param_4 < puVar12) {
                                                      *(long *)((long)register0x00000020 + -0x1a0) =
                                                           lVar7;
                                                      param_1 = (undefined8 *)0x1;
                                                      *(undefined8 *)
                                                       ((long)register0x00000020 + -0x2c0) =
                                                           0x171881a;
                                                      lVar8 = runtime_growslice(1,&DAT_0194e2a0);
                                                      lVar7 = *(long *)((long)register0x00000020 +
                                                                       -0x1a0);
                                                    }
                                                    *(undefined1 *)(lVar8 + lVar7) = 10;
                                                    *(undefined8 **)
                                                     ((long)register0x00000020 + -0x138) = puVar12;
                                                    *(undefined8 **)
                                                     ((long)register0x00000020 + -0x130) = param_4;
                                                    *(long *)((long)register0x00000020 + -0x140) =
                                                         lVar8;
                                                    if (*(undefined1 **)
                                                         ((long)register0x00000020 + -0x148) ==
                                                        (undefined1 *)0x0) {
                                                      *(undefined1 **)
                                                       ((long)register0x00000020 + -0x148) =
                                                           (undefined1 *)
                                                           ((long)register0x00000020 + -0x148);
LAB_0171886d:
                                                      uVar11 = *(ulong *)((long)register0x00000020 +
                                                                         -0x130);
                                                      uVar13 = *(long *)((long)register0x00000020 +
                                                                        -0x138) + 0x1b;
                                                      uVar6 = *(undefined8 *)
                                                               ((long)register0x00000020 + -0x140);
                                                      if (uVar11 < uVar13) {
                                                        *(long *)((long)register0x00000020 + -0x1a0)
                                                             = *(long *)((long)register0x00000020 +
                                                                        -0x138);
                                                        param_1 = (undefined8 *)&DAT_0000001b;
                                                        *(undefined8 *)
                                                         ((long)register0x00000020 + -0x2c0) =
                                                             0x17188aa;
                                                        uVar6 = runtime_growslice(0x1b,&DAT_0194e2a0);
                                                      }
                                                      *(ulong *)((long)register0x00000020 + -0x1a0)
                                                           = uVar11;
                                                      *(ulong *)((long)register0x00000020 + -0x1a8)
                                                           = uVar13;
                                                      *(undefined8 *)
                                                       ((long)register0x00000020 + -0x10) = uVar6;
                                                      param_4 = (undefined8 *)&DAT_0000001b;
                                                      *(undefined8 *)
                                                       ((long)register0x00000020 + -0x2c0) =
                                                           0x17188e5;
                                                      runtime_memmove();
                                                      *(undefined8 *)
                                                       ((long)register0x00000020 + -0x138) =
                                                           *(undefined8 *)
                                                            ((long)register0x00000020 + -0x1a8);
                                                      *(undefined8 *)
                                                       ((long)register0x00000020 + -0x130) =
                                                           *(undefined8 *)
                                                            ((long)register0x00000020 + -0x1a0);
                                                      *(undefined8 *)
                                                       ((long)register0x00000020 + -0x140) =
                                                           *(undefined8 *)
                                                            ((long)register0x00000020 + -0x10);
                                                      if (*(undefined1 **)
                                                           ((long)register0x00000020 + -0x148) ==
                                                          (undefined1 *)0x0) {
                                                        *(undefined1 **)
                                                         ((long)register0x00000020 + -0x148) =
                                                             (undefined1 *)
                                                             ((long)register0x00000020 + -0x148);
LAB_0171894f:
                                                        uVar11 = *(ulong *)((long)register0x00000020
                                                                           + -0x130);
                                                        uVar13 = *(long *)((long)register0x00000020
                                                                          + -0x138) + 0x79;
                                                        uVar6 = *(undefined8 *)
                                                                 ((long)register0x00000020 + -0x140)
                                                        ;
                                                        if (uVar11 < uVar13) {
                                                          *(long *)((long)register0x00000020 +
                                                                   -0x1a0) =
                                                               *(long *)((long)register0x00000020 +
                                                                        -0x138);
                                                          param_1 = (undefined8 *)0x79;
                                                          *(undefined8 *)
                                                           ((long)register0x00000020 + -0x2c0) =
                                                               0x171898c;
                                                          uVar6 = runtime_growslice(0x79,&DAT_0194e2a0,
                                                                               uVar13,uVar11,
                                                                               (undefined1 *)
                                                                               ((long)
                                                  register0x00000020 + -0x148));
                                                  }
                                                  *(ulong *)((long)register0x00000020 + -0x1a0) =
                                                       uVar11;
                                                  *(ulong *)((long)register0x00000020 + -0x1a8) =
                                                       uVar13;
                                                  *(undefined8 *)((long)register0x00000020 + -0x10)
                                                       = uVar6;
                                                  param_4 = (undefined8 *)0x79;
                                                  *(undefined8 *)((long)register0x00000020 + -0x2c0)
                                                       = 0x17189c5;
                                                  runtime_memmove();
                                                  *(undefined8 *)((long)register0x00000020 + -0x138)
                                                       = *(undefined8 *)
                                                          ((long)register0x00000020 + -0x1a8);
                                                  *(undefined8 *)((long)register0x00000020 + -0x130)
                                                       = *(undefined8 *)
                                                          ((long)register0x00000020 + -0x1a0);
                                                  *(undefined8 *)((long)register0x00000020 + -0x140)
                                                       = *(undefined8 *)
                                                          ((long)register0x00000020 + -0x10);
                                                  if (*(undefined1 **)
                                                       ((long)register0x00000020 + -0x148) ==
                                                      (undefined1 *)0x0) {
                                                    *(undefined1 **)
                                                     ((long)register0x00000020 + -0x148) =
                                                         (undefined1 *)
                                                         ((long)register0x00000020 + -0x148);
LAB_01718a2f:
                                                    uVar11 = *(ulong *)((long)register0x00000020 +
                                                                       -0x130);
                                                    uVar13 = *(long *)((long)register0x00000020 +
                                                                      -0x138) + 0x56;
                                                    uVar6 = *(undefined8 *)
                                                             ((long)register0x00000020 + -0x140);
                                                    if (uVar11 < uVar13) {
                                                      *(long *)((long)register0x00000020 + -0x1a0) =
                                                           *(long *)((long)register0x00000020 +
                                                                    -0x138);
                                                      param_1 = (undefined8 *)0x56;
                                                      *(undefined8 *)
                                                       ((long)register0x00000020 + -0x2c0) =
                                                           0x1718a6c;
                                                      uVar6 = runtime_growslice(0x56,&DAT_0194e2a0,uVar13
                                                                           ,uVar11,(undefined1 *)
                                                                                   ((long)
                                                  register0x00000020 + -0x148));
                                                  }
                                                  *(ulong *)((long)register0x00000020 + -0x1a0) =
                                                       uVar11;
                                                  *(ulong *)((long)register0x00000020 + -0x1a8) =
                                                       uVar13;
                                                  *(undefined8 *)((long)register0x00000020 + -0x10)
                                                       = uVar6;
                                                  param_4 = (undefined8 *)0x56;
                                                  *(undefined8 *)((long)register0x00000020 + -0x2c0)
                                                       = 0x1718aa5;
                                                  runtime_memmove();
                                                  *(undefined8 *)((long)register0x00000020 + -0x138)
                                                       = *(undefined8 *)
                                                          ((long)register0x00000020 + -0x1a8);
                                                  *(undefined8 *)((long)register0x00000020 + -0x130)
                                                       = *(undefined8 *)
                                                          ((long)register0x00000020 + -0x1a0);
                                                  *(undefined8 *)((long)register0x00000020 + -0x140)
                                                       = *(undefined8 *)
                                                          ((long)register0x00000020 + -0x10);
                                                  if (*(undefined1 **)
                                                       ((long)register0x00000020 + -0x148) ==
                                                      (undefined1 *)0x0) {
                                                    *(undefined1 **)
                                                     ((long)register0x00000020 + -0x148) =
                                                         (undefined1 *)
                                                         ((long)register0x00000020 + -0x148);
LAB_01718b0f:
                                                    uVar11 = *(ulong *)((long)register0x00000020 +
                                                                       -0x130);
                                                    uVar13 = *(long *)((long)register0x00000020 +
                                                                      -0x138) + 0x43;
                                                    uVar6 = *(undefined8 *)
                                                             ((long)register0x00000020 + -0x140);
                                                    if (uVar11 < uVar13) {
                                                      *(long *)((long)register0x00000020 + -0x1a0) =
                                                           *(long *)((long)register0x00000020 +
                                                                    -0x138);
                                                      param_1 = (undefined8 *)&DAT_00000043;
                                                      *(undefined8 *)
                                                       ((long)register0x00000020 + -0x2c0) =
                                                           0x1718b4c;
                                                      uVar6 = runtime_growslice(0x43,&DAT_0194e2a0,uVar13
                                                                           ,uVar11,(undefined1 *)
                                                                                   ((long)
                                                  register0x00000020 + -0x148));
                                                  }
                                                  *(undefined8 *)((long)register0x00000020 + -0x10)
                                                       = uVar6;
                                                  *(ulong *)((long)register0x00000020 + -0x1a0) =
                                                       uVar11;
                                                  *(ulong *)((long)register0x00000020 + -0x1a8) =
                                                       uVar13;
                                                  param_4 = (undefined8 *)&DAT_00000043;
                                                  *(undefined8 *)((long)register0x00000020 + -0x2c0)
                                                       = 0x1718b85;
                                                  runtime_memmove();
                                                  *(undefined8 *)((long)register0x00000020 + -0x138)
                                                       = *(undefined8 *)
                                                          ((long)register0x00000020 + -0x1a8);
                                                  *(undefined8 *)((long)register0x00000020 + -0x130)
                                                       = *(undefined8 *)
                                                          ((long)register0x00000020 + -0x1a0);
                                                  *(undefined8 *)((long)register0x00000020 + -0x140)
                                                       = *(undefined8 *)
                                                          ((long)register0x00000020 + -0x10);
                                                  if (*(undefined1 **)
                                                       ((long)register0x00000020 + -0x148) ==
                                                      (undefined1 *)0x0) {
                                                    *(undefined1 **)
                                                     ((long)register0x00000020 + -0x148) =
                                                         (undefined1 *)
                                                         ((long)register0x00000020 + -0x148);
LAB_01718bef:
                                                    param_4 = *(undefined8 **)
                                                               ((long)register0x00000020 + -0x130);
                                                    lVar7 = *(long *)((long)register0x00000020 +
                                                                     -0x138);
                                                    puVar12 = (undefined8 *)(lVar7 + 1);
                                                    lVar8 = *(long *)((long)register0x00000020 +
                                                                     -0x140);
                                                    if (param_4 < puVar12) {
                                                      *(long *)((long)register0x00000020 + -0x1a0) =
                                                           lVar7;
                                                      param_1 = (undefined8 *)0x1;
                                                      *(undefined8 *)
                                                       ((long)register0x00000020 + -0x2c0) =
                                                           0x1718c2c;
                                                      lVar8 = runtime_growslice(1,&DAT_0194e2a0);
                                                      lVar7 = *(long *)((long)register0x00000020 +
                                                                       -0x1a0);
                                                    }
                                                    *(undefined1 *)(lVar8 + lVar7) = 10;
                                                    *(undefined8 **)
                                                     ((long)register0x00000020 + -0x138) = puVar12;
                                                    *(undefined8 **)
                                                     ((long)register0x00000020 + -0x130) = param_4;
                                                    *(long *)((long)register0x00000020 + -0x140) =
                                                         lVar8;
                                                    if (*(undefined1 **)
                                                         ((long)register0x00000020 + -0x148) ==
                                                        (undefined1 *)0x0) {
                                                      *(undefined1 **)
                                                       ((long)register0x00000020 + -0x148) =
                                                           (undefined1 *)
                                                           ((long)register0x00000020 + -0x148);
LAB_01718c7c:
                                                      uVar11 = *(ulong *)((long)register0x00000020 +
                                                                         -0x130);
                                                      uVar13 = *(long *)((long)register0x00000020 +
                                                                        -0x138) + 0x16;
                                                      uVar6 = *(undefined8 *)
                                                               ((long)register0x00000020 + -0x140);
                                                      if (uVar11 < uVar13) {
                                                        *(long *)((long)register0x00000020 + -0x1a0)
                                                             = *(long *)((long)register0x00000020 +
                                                                        -0x138);
                                                        param_1 = (undefined8 *)0x16;
                                                        *(undefined8 *)
                                                         ((long)register0x00000020 + -0x2c0) =
                                                             0x1718cb9;
                                                        uVar6 = runtime_growslice(0x16,&DAT_0194e2a0);
                                                      }
                                                      *(ulong *)((long)register0x00000020 + -0x1a0)
                                                           = uVar11;
                                                      *(ulong *)((long)register0x00000020 + -0x1a8)
                                                           = uVar13;
                                                      *(undefined8 *)
                                                       ((long)register0x00000020 + -0x10) = uVar6;
                                                      param_4 = (undefined8 *)0x16;
                                                      *(undefined8 *)
                                                       ((long)register0x00000020 + -0x2c0) =
                                                           0x1718cf0;
                                                      runtime_memmove();
                                                      *(undefined8 *)
                                                       ((long)register0x00000020 + -0x138) =
                                                           *(undefined8 *)
                                                            ((long)register0x00000020 + -0x1a8);
                                                      *(undefined8 *)
                                                       ((long)register0x00000020 + -0x130) =
                                                           *(undefined8 *)
                                                            ((long)register0x00000020 + -0x1a0);
                                                      *(undefined8 *)
                                                       ((long)register0x00000020 + -0x140) =
                                                           *(undefined8 *)
                                                            ((long)register0x00000020 + -0x10);
                                                      if (*(undefined1 **)
                                                           ((long)register0x00000020 + -0x148) ==
                                                          (undefined1 *)0x0) {
                                                        *(undefined1 **)
                                                         ((long)register0x00000020 + -0x148) =
                                                             (undefined1 *)
                                                             ((long)register0x00000020 + -0x148);
LAB_01718d5d:
                                                        uVar11 = *(ulong *)((long)register0x00000020
                                                                           + -0x130);
                                                        uVar13 = *(long *)((long)register0x00000020
                                                                          + -0x138) + 0x2a;
                                                        uVar6 = *(undefined8 *)
                                                                 ((long)register0x00000020 + -0x140)
                                                        ;
                                                        if (uVar11 < uVar13) {
                                                          *(long *)((long)register0x00000020 +
                                                                   -0x1a0) =
                                                               *(long *)((long)register0x00000020 +
                                                                        -0x138);
                                                          param_1 = (undefined8 *)&DAT_0000002a;
                                                          *(undefined8 *)
                                                           ((long)register0x00000020 + -0x2c0) =
                                                               0x1718d9a;
                                                          uVar6 = runtime_growslice(0x2a,&DAT_0194e2a0,
                                                                               uVar13,uVar11,
                                                                               (undefined1 *)
                                                                               ((long)
                                                  register0x00000020 + -0x148));
                                                  }
                                                  *(ulong *)((long)register0x00000020 + -0x1a0) =
                                                       uVar11;
                                                  *(ulong *)((long)register0x00000020 + -0x1a8) =
                                                       uVar13;
                                                  *(undefined8 *)((long)register0x00000020 + -0x10)
                                                       = uVar6;
                                                  param_4 = (undefined8 *)&DAT_0000002a;
                                                  *(undefined8 *)((long)register0x00000020 + -0x2c0)
                                                       = 0x1718dd1;
                                                  runtime_memmove();
                                                  *(undefined8 *)((long)register0x00000020 + -0x138)
                                                       = *(undefined8 *)
                                                          ((long)register0x00000020 + -0x1a8);
                                                  *(undefined8 *)((long)register0x00000020 + -0x130)
                                                       = *(undefined8 *)
                                                          ((long)register0x00000020 + -0x1a0);
                                                  *(undefined8 *)((long)register0x00000020 + -0x140)
                                                       = *(undefined8 *)
                                                          ((long)register0x00000020 + -0x10);
                                                  if (*(undefined1 **)
                                                       ((long)register0x00000020 + -0x148) ==
                                                      (undefined1 *)0x0) {
                                                    *(undefined1 **)
                                                     ((long)register0x00000020 + -0x148) =
                                                         (undefined1 *)
                                                         ((long)register0x00000020 + -0x148);
LAB_01718e3d:
                                                    uVar11 = *(ulong *)((long)register0x00000020 +
                                                                       -0x130);
                                                    uVar13 = *(long *)((long)register0x00000020 +
                                                                      -0x138) + 0x3a;
                                                    uVar6 = *(undefined8 *)
                                                             ((long)register0x00000020 + -0x140);
                                                    if (uVar11 < uVar13) {
                                                      *(long *)((long)register0x00000020 + -0x1a0) =
                                                           *(long *)((long)register0x00000020 +
                                                                    -0x138);
                                                      param_1 = (undefined8 *)0x3a;
                                                      *(undefined8 *)
                                                       ((long)register0x00000020 + -0x2c0) =
                                                           0x1718e7a;
                                                      uVar6 = runtime_growslice(0x3a,&DAT_0194e2a0,uVar13
                                                                           ,uVar11,(undefined1 *)
                                                                                   ((long)
                                                  register0x00000020 + -0x148));
                                                  }
                                                  *(ulong *)((long)register0x00000020 + -0x1a0) =
                                                       uVar13;
                                                  *(ulong *)((long)register0x00000020 + -0x1a8) =
                                                       uVar11;
                                                  *(undefined8 *)((long)register0x00000020 + -0x10)
                                                       = uVar6;
                                                  param_4 = (undefined8 *)0x3a;
                                                  *(undefined8 *)((long)register0x00000020 + -0x2c0)
                                                       = 0x1718eb1;
                                                  runtime_memmove();
                                                  *(undefined8 *)((long)register0x00000020 + -0x138)
                                                       = *(undefined8 *)
                                                          ((long)register0x00000020 + -0x1a0);
                                                  *(undefined8 *)((long)register0x00000020 + -0x130)
                                                       = *(undefined8 *)
                                                          ((long)register0x00000020 + -0x1a8);
                                                  *(undefined8 *)((long)register0x00000020 + -0x140)
                                                       = *(undefined8 *)
                                                          ((long)register0x00000020 + -0x10);
                                                  if (*(undefined1 **)
                                                       ((long)register0x00000020 + -0x148) ==
                                                      (undefined1 *)0x0) {
                                                    *(undefined1 **)
                                                     ((long)register0x00000020 + -0x148) =
                                                         (undefined1 *)
                                                         ((long)register0x00000020 + -0x148);
LAB_01718f1d:
                                                    uVar11 = *(ulong *)((long)register0x00000020 +
                                                                       -0x130);
                                                    uVar13 = *(long *)((long)register0x00000020 +
                                                                      -0x138) + 0x28;
                                                    uVar6 = *(undefined8 *)
                                                             ((long)register0x00000020 + -0x140);
                                                    if (uVar11 < uVar13) {
                                                      *(long *)((long)register0x00000020 + -0x1a0) =
                                                           *(long *)((long)register0x00000020 +
                                                                    -0x138);
                                                      param_1 = (undefined8 *)&DAT_00000028;
                                                      *(undefined8 *)
                                                       ((long)register0x00000020 + -0x2c0) =
                                                           0x1718f5a;
                                                      uVar6 = runtime_growslice(0x28,&DAT_0194e2a0,uVar13
                                                                           ,uVar11,(undefined1 *)
                                                                                   ((long)
                                                  register0x00000020 + -0x148));
                                                  }
                                                  *(ulong *)((long)register0x00000020 + -0x1a0) =
                                                       uVar11;
                                                  *(ulong *)((long)register0x00000020 + -0x1a8) =
                                                       uVar13;
                                                  *(undefined8 *)((long)register0x00000020 + -0x10)
                                                       = uVar6;
                                                  param_4 = (undefined8 *)&DAT_00000028;
                                                  *(undefined8 *)((long)register0x00000020 + -0x2c0)
                                                       = 0x1718f91;
                                                  runtime_memmove();
                                                  *(undefined8 *)((long)register0x00000020 + -0x138)
                                                       = *(undefined8 *)
                                                          ((long)register0x00000020 + -0x1a8);
                                                  *(undefined8 *)((long)register0x00000020 + -0x130)
                                                       = *(undefined8 *)
                                                          ((long)register0x00000020 + -0x1a0);
                                                  *(undefined8 *)((long)register0x00000020 + -0x140)
                                                       = *(undefined8 *)
                                                          ((long)register0x00000020 + -0x10);
                                                  if (*(undefined1 **)
                                                       ((long)register0x00000020 + -0x148) ==
                                                      (undefined1 *)0x0) {
                                                    *(undefined1 **)
                                                     ((long)register0x00000020 + -0x148) =
                                                         (undefined1 *)
                                                         ((long)register0x00000020 + -0x148);
LAB_01718ffd:
                                                    uVar11 = *(ulong *)((long)register0x00000020 +
                                                                       -0x130);
                                                    uVar13 = *(long *)((long)register0x00000020 +
                                                                      -0x138) + 0x1f;
                                                    uVar6 = *(undefined8 *)
                                                             ((long)register0x00000020 + -0x140);
                                                    if (uVar11 < uVar13) {
                                                      *(long *)((long)register0x00000020 + -0x1a0) =
                                                           *(long *)((long)register0x00000020 +
                                                                    -0x138);
                                                      param_1 = (undefined8 *)&DAT_0000001f;
                                                      *(undefined8 *)
                                                       ((long)register0x00000020 + -0x2c0) =
                                                           0x171903a;
                                                      uVar6 = runtime_growslice(0x1f,&DAT_0194e2a0,uVar13
                                                                           ,uVar11,(undefined1 *)
                                                                                   ((long)
                                                  register0x00000020 + -0x148));
                                                  }
                                                  *(ulong *)((long)register0x00000020 + -0x1a0) =
                                                       uVar11;
                                                  *(ulong *)((long)register0x00000020 + -0x1a8) =
                                                       uVar13;
                                                  *(undefined8 *)((long)register0x00000020 + -0x10)
                                                       = uVar6;
                                                  param_4 = (undefined8 *)&DAT_0000001f;
                                                  *(undefined8 *)((long)register0x00000020 + -0x2c0)
                                                       = 0x1719071;
                                                  runtime_memmove();
                                                  *(undefined8 *)((long)register0x00000020 + -0x138)
                                                       = *(undefined8 *)
                                                          ((long)register0x00000020 + -0x1a8);
                                                  *(undefined8 *)((long)register0x00000020 + -0x130)
                                                       = *(undefined8 *)
                                                          ((long)register0x00000020 + -0x1a0);
                                                  *(undefined8 *)((long)register0x00000020 + -0x140)
                                                       = *(undefined8 *)
                                                          ((long)register0x00000020 + -0x10);
                                                  if (*(undefined1 **)
                                                       ((long)register0x00000020 + -0x148) ==
                                                      (undefined1 *)0x0) {
                                                    *(undefined1 **)
                                                     ((long)register0x00000020 + -0x148) =
                                                         (undefined1 *)
                                                         ((long)register0x00000020 + -0x148);
LAB_017190dd:
                                                    param_4 = *(undefined8 **)
                                                               ((long)register0x00000020 + -0x130);
                                                    lVar7 = *(long *)((long)register0x00000020 +
                                                                     -0x138);
                                                    puVar12 = (undefined8 *)(lVar7 + 1);
                                                    lVar8 = *(long *)((long)register0x00000020 +
                                                                     -0x140);
                                                    if (param_4 < puVar12) {
                                                      *(long *)((long)register0x00000020 + -0x1a0) =
                                                           lVar7;
                                                      param_1 = (undefined8 *)0x1;
                                                      *(undefined8 *)
                                                       ((long)register0x00000020 + -0x2c0) =
                                                           0x171911a;
                                                      lVar8 = runtime_growslice(1,&DAT_0194e2a0);
                                                      lVar7 = *(long *)((long)register0x00000020 +
                                                                       -0x1a0);
                                                    }
                                                    *(undefined1 *)(lVar8 + lVar7) = 10;
                                                    *(undefined8 **)
                                                     ((long)register0x00000020 + -0x138) = puVar12;
                                                    *(undefined8 **)
                                                     ((long)register0x00000020 + -0x130) = param_4;
                                                    *(long *)((long)register0x00000020 + -0x140) =
                                                         lVar8;
                                                    if (*(undefined1 **)
                                                         ((long)register0x00000020 + -0x148) ==
                                                        (undefined1 *)0x0) {
                                                      *(undefined1 **)
                                                       ((long)register0x00000020 + -0x148) =
                                                           (undefined1 *)
                                                           ((long)register0x00000020 + -0x148);
LAB_0171916d:
                                                      uVar11 = *(ulong *)((long)register0x00000020 +
                                                                         -0x130);
                                                      uVar13 = *(long *)((long)register0x00000020 +
                                                                        -0x138) + 0x2d;
                                                      uVar6 = *(undefined8 *)
                                                               ((long)register0x00000020 + -0x140);
                                                      if (uVar11 < uVar13) {
                                                        *(long *)((long)register0x00000020 + -0x1a0)
                                                             = *(long *)((long)register0x00000020 +
                                                                        -0x138);
                                                        param_1 = (undefined8 *)0x2d;
                                                        *(undefined8 *)
                                                         ((long)register0x00000020 + -0x2c0) =
                                                             0x17191aa;
                                                        uVar6 = runtime_growslice(0x2d,&DAT_0194e2a0);
                                                      }
                                                      *(ulong *)((long)register0x00000020 + -0x1a0)
                                                           = uVar13;
                                                      *(ulong *)((long)register0x00000020 + -0x1a8)
                                                           = uVar11;
                                                      *(undefined8 *)
                                                       ((long)register0x00000020 + -0x10) = uVar6;
                                                      param_4 = (undefined8 *)0x2d;
                                                      *(undefined8 *)
                                                       ((long)register0x00000020 + -0x2c0) =
                                                           0x17191e5;
                                                      runtime_memmove();
                                                      *(undefined8 *)
                                                       ((long)register0x00000020 + -0x138) =
                                                           *(undefined8 *)
                                                            ((long)register0x00000020 + -0x1a0);
                                                      *(undefined8 *)
                                                       ((long)register0x00000020 + -0x130) =
                                                           *(undefined8 *)
                                                            ((long)register0x00000020 + -0x1a8);
                                                      *(undefined8 *)
                                                       ((long)register0x00000020 + -0x140) =
                                                           *(undefined8 *)
                                                            ((long)register0x00000020 + -0x10);
                                                      if (*(undefined1 **)
                                                           ((long)register0x00000020 + -0x148) ==
                                                          (undefined1 *)0x0) {
                                                        *(undefined1 **)
                                                         ((long)register0x00000020 + -0x148) =
                                                             (undefined1 *)
                                                             ((long)register0x00000020 + -0x148);
LAB_0171924f:
                                                        uVar11 = *(ulong *)((long)register0x00000020
                                                                           + -0x130);
                                                        uVar13 = *(long *)((long)register0x00000020
                                                                          + -0x138) + 0x31;
                                                        uVar6 = *(undefined8 *)
                                                                 ((long)register0x00000020 + -0x140)
                                                        ;
                                                        if (uVar11 < uVar13) {
                                                          *(long *)((long)register0x00000020 +
                                                                   -0x1a0) =
                                                               *(long *)((long)register0x00000020 +
                                                                        -0x138);
                                                          param_1 = (undefined8 *)0x31;
                                                          *(undefined8 *)
                                                           ((long)register0x00000020 + -0x2c0) =
                                                               0x171928c;
                                                          uVar6 = runtime_growslice(0x31,&DAT_0194e2a0,
                                                                               uVar13,uVar11,
                                                                               (undefined1 *)
                                                                               ((long)
                                                  register0x00000020 + -0x148));
                                                  }
                                                  *(ulong *)((long)register0x00000020 + -0x1a0) =
                                                       uVar11;
                                                  *(ulong *)((long)register0x00000020 + -0x1a8) =
                                                       uVar13;
                                                  *(undefined8 *)((long)register0x00000020 + -0x10)
                                                       = uVar6;
                                                  param_4 = (undefined8 *)0x31;
                                                  *(undefined8 *)((long)register0x00000020 + -0x2c0)
                                                       = 0x17192c5;
                                                  runtime_memmove();
                                                  *(undefined8 *)((long)register0x00000020 + -0x138)
                                                       = *(undefined8 *)
                                                          ((long)register0x00000020 + -0x1a8);
                                                  *(undefined8 *)((long)register0x00000020 + -0x130)
                                                       = *(undefined8 *)
                                                          ((long)register0x00000020 + -0x1a0);
                                                  *(undefined8 *)((long)register0x00000020 + -0x140)
                                                       = *(undefined8 *)
                                                          ((long)register0x00000020 + -0x10);
                                                  if (*(undefined1 **)
                                                       ((long)register0x00000020 + -0x148) ==
                                                      (undefined1 *)0x0) {
                                                    *(undefined1 **)
                                                     ((long)register0x00000020 + -0x148) =
                                                         (undefined1 *)
                                                         ((long)register0x00000020 + -0x148);
LAB_0171932f:
                                                    uVar11 = *(ulong *)((long)register0x00000020 +
                                                                       -0x130);
                                                    uVar13 = *(long *)((long)register0x00000020 +
                                                                      -0x138) + 0x2d;
                                                    uVar6 = *(undefined8 *)
                                                             ((long)register0x00000020 + -0x140);
                                                    if (uVar11 < uVar13) {
                                                      *(long *)((long)register0x00000020 + -0x1a0) =
                                                           *(long *)((long)register0x00000020 +
                                                                    -0x138);
                                                      param_1 = (undefined8 *)0x2d;
                                                      *(undefined8 *)
                                                       ((long)register0x00000020 + -0x2c0) =
                                                           0x171936c;
                                                      uVar6 = runtime_growslice(0x2d,&DAT_0194e2a0,uVar13
                                                                           ,uVar11,(undefined1 *)
                                                                                   ((long)
                                                  register0x00000020 + -0x148));
                                                  }
                                                  *(ulong *)((long)register0x00000020 + -0x1a0) =
                                                       uVar11;
                                                  *(ulong *)((long)register0x00000020 + -0x1a8) =
                                                       uVar13;
                                                  *(undefined8 *)((long)register0x00000020 + -0x10)
                                                       = uVar6;
                                                  param_4 = (undefined8 *)0x2d;
                                                  *(undefined8 *)((long)register0x00000020 + -0x2c0)
                                                       = 0x17193a5;
                                                  runtime_memmove();
                                                  *(undefined8 *)((long)register0x00000020 + -0x138)
                                                       = *(undefined8 *)
                                                          ((long)register0x00000020 + -0x1a8);
                                                  *(undefined8 *)((long)register0x00000020 + -0x130)
                                                       = *(undefined8 *)
                                                          ((long)register0x00000020 + -0x1a0);
                                                  *(undefined8 *)((long)register0x00000020 + -0x140)
                                                       = *(undefined8 *)
                                                          ((long)register0x00000020 + -0x10);
                                                  if (*(undefined1 **)
                                                       ((long)register0x00000020 + -0x148) ==
                                                      (undefined1 *)0x0) {
                                                    *(undefined1 **)
                                                     ((long)register0x00000020 + -0x148) =
                                                         (undefined1 *)
                                                         ((long)register0x00000020 + -0x148);
LAB_0171940f:
                                                    uVar11 = *(ulong *)((long)register0x00000020 +
                                                                       -0x130);
                                                    uVar13 = *(long *)((long)register0x00000020 +
                                                                      -0x138) + 0x5c;
                                                    uVar6 = *(undefined8 *)
                                                             ((long)register0x00000020 + -0x140);
                                                    if (uVar11 < uVar13) {
                                                      *(long *)((long)register0x00000020 + -0x1a0) =
                                                           *(long *)((long)register0x00000020 +
                                                                    -0x138);
                                                      param_1 = (undefined8 *)0x5c;
                                                      *(undefined8 *)
                                                       ((long)register0x00000020 + -0x2c0) =
                                                           0x171944c;
                                                      uVar6 = runtime_growslice(0x5c,&DAT_0194e2a0,uVar13
                                                                           ,uVar11,(undefined1 *)
                                                                                   ((long)
                                                  register0x00000020 + -0x148));
                                                  }
                                                  *(ulong *)((long)register0x00000020 + -0x1a0) =
                                                       uVar11;
                                                  *(ulong *)((long)register0x00000020 + -0x1a8) =
                                                       uVar13;
                                                  *(undefined8 *)((long)register0x00000020 + -0x10)
                                                       = uVar6;
                                                  param_4 = (undefined8 *)0x5c;
                                                  *(undefined8 *)((long)register0x00000020 + -0x2c0)
                                                       = 0x1719485;
                                                  runtime_memmove();
                                                  *(undefined8 *)((long)register0x00000020 + -0x138)
                                                       = *(undefined8 *)
                                                          ((long)register0x00000020 + -0x1a8);
                                                  *(undefined8 *)((long)register0x00000020 + -0x130)
                                                       = *(undefined8 *)
                                                          ((long)register0x00000020 + -0x1a0);
                                                  *(undefined8 *)((long)register0x00000020 + -0x140)
                                                       = *(undefined8 *)
                                                          ((long)register0x00000020 + -0x10);
                                                  if (*(undefined1 **)
                                                       ((long)register0x00000020 + -0x148) ==
                                                      (undefined1 *)0x0) {
                                                    *(undefined1 **)
                                                     ((long)register0x00000020 + -0x148) =
                                                         (undefined1 *)
                                                         ((long)register0x00000020 + -0x148);
LAB_017194ef:
                                                    uVar11 = *(ulong *)((long)register0x00000020 +
                                                                       -0x130);
                                                    uVar13 = *(long *)((long)register0x00000020 +
                                                                      -0x138) + 0x39;
                                                    uVar6 = *(undefined8 *)
                                                             ((long)register0x00000020 + -0x140);
                                                    if (uVar11 < uVar13) {
                                                      *(long *)((long)register0x00000020 + -0x1a0) =
                                                           *(long *)((long)register0x00000020 +
                                                                    -0x138);
                                                      param_1 = (undefined8 *)&DAT_00000039;
                                                      *(undefined8 *)
                                                       ((long)register0x00000020 + -0x2c0) =
                                                           0x171952c;
                                                      uVar6 = runtime_growslice(0x39,&DAT_0194e2a0,uVar13
                                                                           ,uVar11,(undefined1 *)
                                                                                   ((long)
                                                  register0x00000020 + -0x148));
                                                  }
                                                  *(ulong *)((long)register0x00000020 + -0x1a0) =
                                                       uVar13;
                                                  *(ulong *)((long)register0x00000020 + -0x1a8) =
                                                       uVar11;
                                                  *(undefined8 *)((long)register0x00000020 + -0x10)
                                                       = uVar6;
                                                  param_4 = (undefined8 *)&DAT_00000039;
                                                  *(undefined8 *)((long)register0x00000020 + -0x2c0)
                                                       = 0x1719565;
                                                  runtime_memmove();
                                                  *(undefined8 *)((long)register0x00000020 + -0x138)
                                                       = *(undefined8 *)
                                                          ((long)register0x00000020 + -0x1a0);
                                                  *(undefined8 *)((long)register0x00000020 + -0x130)
                                                       = *(undefined8 *)
                                                          ((long)register0x00000020 + -0x1a8);
                                                  *(undefined8 *)((long)register0x00000020 + -0x140)
                                                       = *(undefined8 *)
                                                          ((long)register0x00000020 + -0x10);
                                                  if (*(undefined1 **)
                                                       ((long)register0x00000020 + -0x148) ==
                                                      (undefined1 *)0x0) {
                                                    *(undefined1 **)
                                                     ((long)register0x00000020 + -0x148) =
                                                         (undefined1 *)
                                                         ((long)register0x00000020 + -0x148);
LAB_017195cf:
                                                    uVar11 = *(ulong *)((long)register0x00000020 +
                                                                       -0x130);
                                                    uVar13 = *(long *)((long)register0x00000020 +
                                                                      -0x138) + 0x8e;
                                                    uVar6 = *(undefined8 *)
                                                             ((long)register0x00000020 + -0x140);
                                                    if (uVar11 < uVar13) {
                                                      *(long *)((long)register0x00000020 + -0x1a0) =
                                                           *(long *)((long)register0x00000020 +
                                                                    -0x138);
                                                      param_1 = (undefined8 *)0x8e;
                                                      *(undefined8 *)
                                                       ((long)register0x00000020 + -0x2c0) =
                                                           0x171960f;
                                                      uVar6 = runtime_growslice(0x8e,&DAT_0194e2a0,uVar13
                                                                           ,uVar11,(undefined1 *)
                                                                                   ((long)
                                                  register0x00000020 + -0x148));
                                                  }
                                                  *(ulong *)((long)register0x00000020 + -0x1a0) =
                                                       uVar11;
                                                  *(ulong *)((long)register0x00000020 + -0x1a8) =
                                                       uVar13;
                                                  *(undefined8 *)((long)register0x00000020 + -0x10)
                                                       = uVar6;
                                                  param_4 = (undefined8 *)0x8e;
                                                  *(undefined8 *)((long)register0x00000020 + -0x2c0)
                                                       = 0x1719646;
                                                  runtime_memmove();
                                                  *(undefined8 *)((long)register0x00000020 + -0x138)
                                                       = *(undefined8 *)
                                                          ((long)register0x00000020 + -0x1a8);
                                                  *(undefined8 *)((long)register0x00000020 + -0x130)
                                                       = *(undefined8 *)
                                                          ((long)register0x00000020 + -0x1a0);
                                                  *(undefined8 *)((long)register0x00000020 + -0x140)
                                                       = *(undefined8 *)
                                                          ((long)register0x00000020 + -0x10);
                                                  if (*(undefined1 **)
                                                       ((long)register0x00000020 + -0x148) ==
                                                      (undefined1 *)0x0) {
                                                    *(undefined1 **)
                                                     ((long)register0x00000020 + -0x148) =
                                                         (undefined1 *)
                                                         ((long)register0x00000020 + -0x148);
LAB_017196af:
                                                    uVar11 = *(ulong *)((long)register0x00000020 +
                                                                       -0x130);
                                                    uVar13 = *(long *)((long)register0x00000020 +
                                                                      -0x138) + 0x16;
                                                    uVar6 = *(undefined8 *)
                                                             ((long)register0x00000020 + -0x140);
                                                    if (uVar11 < uVar13) {
                                                      *(long *)((long)register0x00000020 + -0x1a0) =
                                                           *(long *)((long)register0x00000020 +
                                                                    -0x138);
                                                      param_1 = (undefined8 *)0x16;
                                                      *(undefined8 *)
                                                       ((long)register0x00000020 + -0x2c0) =
                                                           0x17196ec;
                                                      uVar6 = runtime_growslice(0x16,&DAT_0194e2a0,uVar13
                                                                           ,uVar11,(undefined1 *)
                                                                                   ((long)
                                                  register0x00000020 + -0x148));
                                                  }
                                                  *(ulong *)((long)register0x00000020 + -0x1a0) =
                                                       uVar11;
                                                  *(ulong *)((long)register0x00000020 + -0x1a8) =
                                                       uVar13;
                                                  *(undefined8 *)((long)register0x00000020 + -0x10)
                                                       = uVar6;
                                                  param_4 = (undefined8 *)0x16;
                                                  *(undefined8 *)((long)register0x00000020 + -0x2c0)
                                                       = 0x1719725;
                                                  runtime_memmove();
                                                  *(undefined8 *)((long)register0x00000020 + -0x138)
                                                       = *(undefined8 *)
                                                          ((long)register0x00000020 + -0x1a8);
                                                  *(undefined8 *)((long)register0x00000020 + -0x130)
                                                       = *(undefined8 *)
                                                          ((long)register0x00000020 + -0x1a0);
                                                  *(undefined8 *)((long)register0x00000020 + -0x140)
                                                       = *(undefined8 *)
                                                          ((long)register0x00000020 + -0x10);
                                                  lVar7 = *(long *)((long)register0x00000020 + 0x20)
                                                  ;
                                                  if (*(long *)(lVar7 + 0x98) == 0)
                                                  goto LAB_01719947;
                                                  if (*(undefined1 **)
                                                       ((long)register0x00000020 + -0x148) ==
                                                      (undefined1 *)0x0) {
                                                    *(undefined1 **)
                                                     ((long)register0x00000020 + -0x148) =
                                                         (undefined1 *)
                                                         ((long)register0x00000020 + -0x148);
LAB_017197a4:
                                                    uVar11 = *(ulong *)((long)register0x00000020 +
                                                                       -0x130);
                                                    uVar13 = *(long *)((long)register0x00000020 +
                                                                      -0x138) + 0x13;
                                                    uVar6 = *(undefined8 *)
                                                             ((long)register0x00000020 + -0x140);
                                                    if (uVar11 < uVar13) {
                                                      *(long *)((long)register0x00000020 + -0x1a0) =
                                                           *(long *)((long)register0x00000020 +
                                                                    -0x138);
                                                      param_1 = (undefined8 *)&DAT_00000013;
                                                      *(undefined8 *)
                                                       ((long)register0x00000020 + -0x2c0) =
                                                           0x17197e5;
                                                      uVar6 = runtime_growslice(0x13,&DAT_0194e2a0);
                                                    }
                                                    *(ulong *)((long)register0x00000020 + -0x1a0) =
                                                         uVar11;
                                                    *(ulong *)((long)register0x00000020 + -0x1a8) =
                                                         uVar13;
                                                    *(undefined8 *)
                                                     ((long)register0x00000020 + -0x10) = uVar6;
                                                    puVar12 = (undefined8 *)&DAT_00000013;
                                                    *(undefined8 *)
                                                     ((long)register0x00000020 + -0x2c0) = 0x171981c
                                                    ;
                                                    runtime_memmove();
                                                    *(undefined8 *)
                                                     ((long)register0x00000020 + -0x138) =
                                                         *(undefined8 *)
                                                          ((long)register0x00000020 + -0x1a8);
                                                    *(undefined8 *)
                                                     ((long)register0x00000020 + -0x130) =
                                                         *(undefined8 *)
                                                          ((long)register0x00000020 + -0x1a0);
                                                    *(undefined8 *)
                                                     ((long)register0x00000020 + -0x140) =
                                                         *(undefined8 *)
                                                          ((long)register0x00000020 + -0x10);
                                                    if (*(undefined1 **)
                                                         ((long)register0x00000020 + -0x148) ==
                                                        (undefined1 *)0x0) {
                                                      *(undefined1 **)
                                                       ((long)register0x00000020 + -0x148) =
                                                           (undefined1 *)
                                                           ((long)register0x00000020 + -0x148);
LAB_01719885:
                                                      uVar11 = *(ulong *)((long)register0x00000020 +
                                                                         -0x130);
                                                      uVar13 = *(long *)((long)register0x00000020 +
                                                                        -0x138) + 0x39;
                                                      uVar6 = *(undefined8 *)
                                                               ((long)register0x00000020 + -0x140);
                                                      if (uVar11 < uVar13) {
                                                        *(long *)((long)register0x00000020 + -0x1a0)
                                                             = *(long *)((long)register0x00000020 +
                                                                        -0x138);
                                                        *(undefined8 *)
                                                         ((long)register0x00000020 + -0x2c0) =
                                                             0x17198c5;
                                                        uVar6 = runtime_growslice(0x39,&DAT_0194e2a0,
                                                                             uVar13,uVar11,
                                                                             (undefined1 *)
                                                                             ((long)
                                                  register0x00000020 + -0x148));
                                                  }
                                                  *(ulong *)((long)register0x00000020 + -0x1a0) =
                                                       uVar11;
                                                  *(ulong *)((long)register0x00000020 + -0x1a8) =
                                                       uVar13;
                                                  *(undefined8 *)((long)register0x00000020 + -0x10)
                                                       = uVar6;
                                                  puVar12 = (undefined8 *)&DAT_00000039;
                                                  *(undefined8 *)((long)register0x00000020 + -0x2c0)
                                                       = 0x17198fc;
                                                  runtime_memmove();
                                                  *(undefined8 *)((long)register0x00000020 + -0x138)
                                                       = *(undefined8 *)
                                                          ((long)register0x00000020 + -0x1a8);
                                                  *(undefined8 *)((long)register0x00000020 + -0x130)
                                                       = *(undefined8 *)
                                                          ((long)register0x00000020 + -0x1a0);
                                                  *(undefined8 *)((long)register0x00000020 + -0x140)
                                                       = *(undefined8 *)
                                                          ((long)register0x00000020 + -0x10);
                                                  lVar7 = *(long *)((long)register0x00000020 + 0x20)
                                                  ;
                                                  puVar18 = *(undefined8 **)(lVar7 + 0x90);
                                                  param_1 = *(undefined8 **)(lVar7 + 0x98);
                                                  while (0 < (long)param_1) {
                                                    *(undefined8 **)
                                                     ((long)register0x00000020 + -0x1a0) = param_1;
                                                    *(undefined8 **)
                                                     ((long)register0x00000020 + -0x18) = puVar18;
                                                    *(undefined8 *)
                                                     ((long)register0x00000020 + -0x10) = *puVar18;
                                                    *(undefined8 *)
                                                     ((long)register0x00000020 + -0x1a8) =
                                                         puVar18[1];
                                                    *(undefined8 *)
                                                     ((long)register0x00000020 + -0x28) = puVar18[2]
                                                    ;
                                                    *(undefined8 *)
                                                     ((long)register0x00000020 + -0x1b0) =
                                                         puVar18[3];
                                                    *(undefined8 *)
                                                     ((long)register0x00000020 + -0x38) =
                                                         in_XMM15_Qa;
                                                    *(undefined8 *)
                                                     ((long)register0x00000020 + -0x30) =
                                                         in_XMM15_Qb;
                                                    *(undefined8 *)
                                                     ((long)register0x00000020 + -0x2c0) = 0x171b49a
                                                    ;
                                                    auVar21 = runtime_convTstring();
                                                    *(undefined8 **)
                                                     ((long)register0x00000020 + -0x38) =
                                                         &DAT_0194e220;
                                                    *(long *)((long)register0x00000020 + -0x30) =
                                                         auVar21._0_8_;
                                                    *(undefined8 *)
                                                     ((long)register0x00000020 + -0x2c0) = 0x171b4d2
                                                    ;
                                                    uVar6 = fmt_Sprintf(1,1,auVar21._8_8_,
                                                                         (undefined1 *)
                                                                         ((long)register0x00000020 +
                                                                         -0x38));
                                                    *(undefined8 *)
                                                     ((long)register0x00000020 + -0x150) = uVar6;
                                                    *(undefined8 *)
                                                     ((long)register0x00000020 + -0x220) = 0x1a;
                                                    *(undefined8 *)
                                                     ((long)register0x00000020 + -0x58) =
                                                         in_XMM15_Qa;
                                                    *(undefined8 *)
                                                     ((long)register0x00000020 + -0x50) =
                                                         in_XMM15_Qb;
                                                    *(undefined8 *)
                                                     ((long)register0x00000020 + -0x48) =
                                                         in_XMM15_Qa;
                                                    *(undefined8 *)
                                                     ((long)register0x00000020 + -0x40) =
                                                         in_XMM15_Qb;
                                                    *(undefined8 *)
                                                     ((long)register0x00000020 + -0x2c0) = 0x171b509
                                                    ;
                                                    uVar6 = runtime_convTstring();
                                                    *(undefined8 **)
                                                     ((long)register0x00000020 + -0x58) =
                                                         &DAT_0194e220;
                                                    *(undefined8 *)
                                                     ((long)register0x00000020 + -0x50) = uVar6;
                                                    *(undefined8 *)
                                                     ((long)register0x00000020 + -0x2c0) = 0x171b535
                                                    ;
                                                    auVar21 = runtime_convTstring();
                                                    *(undefined8 **)
                                                     ((long)register0x00000020 + -0x48) =
                                                         &DAT_0194e220;
                                                    *(long *)((long)register0x00000020 + -0x40) =
                                                         auVar21._0_8_;
                                                    param_1 = (undefined8 *)0x2;
                                                    *(undefined8 *)
                                                     ((long)register0x00000020 + -0x2c0) = 0x171b56d
                                                    ;
                                                    uVar6 = fmt_Sprintf(2,2,auVar21._8_8_,
                                                                         (undefined1 *)
                                                                         ((long)register0x00000020 +
                                                                         -0x58));
                                                    puVar12 = *(undefined8 **)
                                                               ((long)register0x00000020 + -0x148);
                                                    if (puVar12 == (undefined8 *)0x0) {
                                                      *(undefined1 **)
                                                       ((long)register0x00000020 + -0x148) =
                                                           (undefined1 *)
                                                           ((long)register0x00000020 + -0x148);
                                                    }
                                                    else if (puVar12 !=
                                                             (undefined8 *)
                                                             ((long)register0x00000020 + -0x148))
                                                    goto LAB_0171b972;
                                                    uVar11 = *(ulong *)((long)register0x00000020 +
                                                                       -0x130);
                                                    uVar13 = *(long *)((long)register0x00000020 +
                                                                      -0x138) + 9;
                                                    in_R10 = *(undefined8 *)
                                                              ((long)register0x00000020 + -0x140);
                                                    if (uVar11 < uVar13) {
                                                      *(undefined8 *)
                                                       ((long)register0x00000020 + -0x1e0) = 9;
                                                      *(undefined8 *)
                                                       ((long)register0x00000020 + -0xf0) = uVar6;
                                                      *(long *)((long)register0x00000020 + -0x1a8) =
                                                           *(long *)((long)register0x00000020 +
                                                                    -0x138);
                                                      *(undefined8 *)
                                                       ((long)register0x00000020 + -0x2c0) =
                                                           0x171b5eb;
                                                      in_R10 = runtime_growslice(9,&DAT_0194e2a0);
                                                    }
                                                    *(ulong *)((long)register0x00000020 + -0x1a8) =
                                                         uVar11;
                                                    *(ulong *)((long)register0x00000020 + -0x1b0) =
                                                         uVar13;
                                                    *(undefined8 *)
                                                     ((long)register0x00000020 + -0x10) = in_R10;
                                                    *(undefined8 *)
                                                     ((long)register0x00000020 + -0x2c0) = 0x171b633
                                                    ;
                                                    runtime_memmove();
                                                    *(undefined8 *)
                                                     ((long)register0x00000020 + -0x138) =
                                                         *(undefined8 *)
                                                          ((long)register0x00000020 + -0x1b0);
                                                    *(undefined8 *)
                                                     ((long)register0x00000020 + -0x130) =
                                                         *(undefined8 *)
                                                          ((long)register0x00000020 + -0x1a8);
                                                    *(undefined8 *)
                                                     ((long)register0x00000020 + -0x140) =
                                                         *(undefined8 *)
                                                          ((long)register0x00000020 + -0x10);
                                                    *(undefined8 *)
                                                     ((long)register0x00000020 + -0x38) =
                                                         in_XMM15_Qa;
                                                    *(undefined8 *)
                                                     ((long)register0x00000020 + -0x30) =
                                                         in_XMM15_Qb;
                                                    *(undefined8 *)
                                                     ((long)register0x00000020 + -0x2c0) = 0x171b685
                                                    ;
                                                    uVar6 = runtime_convTstring();
                                                    *(undefined8 **)
                                                     ((long)register0x00000020 + -0x38) =
                                                         &DAT_0194e220;
                                                    *(undefined8 *)
                                                     ((long)register0x00000020 + -0x30) = uVar6;
                                                    puVar12 = (undefined8 *)
                                                              ((long)register0x00000020 + -0x38);
                                                    param_1 = (undefined8 *)0x1;
                                                    *(undefined8 *)
                                                     ((long)register0x00000020 + -0x2c0) = 0x171b6bd
                                                    ;
                                                    uVar6 = fmt_Sprintf(1,1);
                                                    if (*(undefined1 **)
                                                         ((long)register0x00000020 + -0x148) ==
                                                        (undefined1 *)0x0) {
                                                      *(undefined1 **)
                                                       ((long)register0x00000020 + -0x148) =
                                                           (undefined1 *)
                                                           ((long)register0x00000020 + -0x148);
                                                    }
                                                    else if (*(undefined1 **)
                                                              ((long)register0x00000020 + -0x148) !=
                                                             (undefined1 *)
                                                             ((long)register0x00000020 + -0x148))
                                                    goto LAB_0171b95f;
                                                    param_4 = *(undefined8 **)
                                                               ((long)register0x00000020 + -0x130);
                                                    lVar7 = *(long *)((long)register0x00000020 +
                                                                     -0x138);
                                                    puVar18 = (undefined8 *)(lVar7 + 0x11);
                                                    in_R10 = *(undefined8 *)
                                                              ((long)register0x00000020 + -0x140);
                                                    puVar12 = (undefined8 *)&DAT_00000011;
                                                    if (param_4 < puVar18) {
                                                      *(undefined8 *)
                                                       ((long)register0x00000020 + -0x1e8) = 0x11;
                                                      *(undefined8 *)
                                                       ((long)register0x00000020 + -0xf8) = uVar6;
                                                      *(long *)((long)register0x00000020 + -0x1a8) =
                                                           lVar7;
                                                      *(undefined8 *)
                                                       ((long)register0x00000020 + -0x2c0) =
                                                           0x171b747;
                                                      in_R10 = runtime_growslice(0x11,&DAT_0194e2a0,lVar7
                                                                            ,param_4,(undefined1 *)
                                                                                     ((long)
                                                  register0x00000020 + -0x148));
                                                  puVar12 = *(undefined8 **)
                                                             ((long)register0x00000020 + -0x1e8);
                                                  }
LAB_0171b3cc:
                                                  *(undefined8 **)
                                                   ((long)register0x00000020 + -0x1a8) = param_4;
                                                  *(undefined8 **)
                                                   ((long)register0x00000020 + -0x1b0) = puVar18;
                                                  *(undefined8 *)((long)register0x00000020 + -0x10)
                                                       = in_R10;
                                                  *(undefined8 *)((long)register0x00000020 + -0x2c0)
                                                       = 0x171b3f5;
                                                  runtime_memmove();
                                                  *(undefined8 *)((long)register0x00000020 + -0x138)
                                                       = *(undefined8 *)
                                                          ((long)register0x00000020 + -0x1b0);
                                                  *(undefined8 *)((long)register0x00000020 + -0x130)
                                                       = *(undefined8 *)
                                                          ((long)register0x00000020 + -0x1a8);
                                                  *(undefined8 *)((long)register0x00000020 + -0x140)
                                                       = *(undefined8 *)
                                                          ((long)register0x00000020 + -0x10);
                                                  puVar18 = (undefined8 *)
                                                            (*(long *)((long)register0x00000020 +
                                                                      -0x18) + 0x20);
                                                  lVar7 = *(long *)((long)register0x00000020 + 0x20)
                                                  ;
                                                  param_1 = (undefined8 *)
                                                            (*(long *)((long)register0x00000020 +
                                                                      -0x1a0) + -1);
                                                  }
                                                  if (*(undefined1 **)
                                                       ((long)register0x00000020 + -0x148) ==
                                                      (undefined1 *)0x0) {
                                                    *(undefined1 **)
                                                     ((long)register0x00000020 + -0x148) =
                                                         (undefined1 *)
                                                         ((long)register0x00000020 + -0x148);
LAB_0171b7a3:
                                                    uVar11 = *(ulong *)((long)register0x00000020 +
                                                                       -0x130);
                                                    uVar13 = *(long *)((long)register0x00000020 +
                                                                      -0x138) + 0x4c;
                                                    uVar6 = *(undefined8 *)
                                                             ((long)register0x00000020 + -0x140);
                                                    if (uVar11 < uVar13) {
                                                      *(long *)((long)register0x00000020 + -0x1a0) =
                                                           *(long *)((long)register0x00000020 +
                                                                    -0x138);
                                                      param_1 = (undefined8 *)0x4c;
                                                      *(undefined8 *)
                                                       ((long)register0x00000020 + -0x2c0) =
                                                           0x171b7e5;
                                                      uVar6 = runtime_growslice(0x4c,&DAT_0194e2a0,lVar7,
                                                                           uVar11,uVar13,
                                                                           (undefined1 *)
                                                                           ((long)register0x00000020
                                                                           + -0x148));
                                                    }
                                                    *(ulong *)((long)register0x00000020 + -0x1a0) =
                                                         uVar11;
                                                    *(ulong *)((long)register0x00000020 + -0x1a8) =
                                                         uVar13;
                                                    *(undefined8 *)
                                                     ((long)register0x00000020 + -0x10) = uVar6;
                                                    puVar12 = (undefined8 *)0x4c;
                                                    *(undefined8 *)
                                                     ((long)register0x00000020 + -0x2c0) = 0x171b81c
                                                    ;
                                                    runtime_memmove();
                                                    *(undefined8 *)
                                                     ((long)register0x00000020 + -0x138) =
                                                         *(undefined8 *)
                                                          ((long)register0x00000020 + -0x1a8);
                                                    *(undefined8 *)
                                                     ((long)register0x00000020 + -0x130) =
                                                         *(undefined8 *)
                                                          ((long)register0x00000020 + -0x1a0);
                                                    *(undefined8 *)
                                                     ((long)register0x00000020 + -0x140) =
                                                         *(undefined8 *)
                                                          ((long)register0x00000020 + -0x10);
                                                    if (*(undefined1 **)
                                                         ((long)register0x00000020 + -0x148) ==
                                                        (undefined1 *)0x0) {
                                                      *(undefined1 **)
                                                       ((long)register0x00000020 + -0x148) =
                                                           (undefined1 *)
                                                           ((long)register0x00000020 + -0x148);
                                                    }
                                                    else if (*(undefined1 **)
                                                              ((long)register0x00000020 + -0x148) !=
                                                             (undefined1 *)
                                                             ((long)register0x00000020 + -0x148)) {
                                                      *(undefined8 *)
                                                       ((long)register0x00000020 + -0x2c0) =
                                                           0x171b94c;
                                                      runtime_gopanic();
                                                      goto LAB_0171b94c;
                                                    }
                                                    uVar11 = *(ulong *)((long)register0x00000020 +
                                                                       -0x130);
                                                    uVar13 = *(long *)((long)register0x00000020 +
                                                                      -0x138) + 0x15;
                                                    uVar6 = *(undefined8 *)
                                                             ((long)register0x00000020 + -0x140);
                                                    if (uVar11 < uVar13) {
                                                      *(long *)((long)register0x00000020 + -0x1a0) =
                                                           *(long *)((long)register0x00000020 +
                                                                    -0x138);
                                                      *(undefined8 *)
                                                       ((long)register0x00000020 + -0x2c0) =
                                                           0x171b8c5;
                                                      uVar6 = runtime_growslice(0x15,&DAT_0194e2a0,uVar13
                                                                           ,uVar11,(undefined1 *)
                                                                                   ((long)
                                                  register0x00000020 + -0x148));
                                                  }
                                                  *(ulong *)((long)register0x00000020 + -0x1a0) =
                                                       uVar11;
                                                  *(ulong *)((long)register0x00000020 + -0x1a8) =
                                                       uVar13;
                                                  *(undefined8 *)((long)register0x00000020 + -0x10)
                                                       = uVar6;
                                                  param_4 = (undefined8 *)&DAT_00000015;
                                                  *(undefined8 *)((long)register0x00000020 + -0x2c0)
                                                       = 0x171b8fc;
                                                  runtime_memmove();
                                                  *(undefined8 *)((long)register0x00000020 + -0x138)
                                                       = *(undefined8 *)
                                                          ((long)register0x00000020 + -0x1a8);
                                                  *(undefined8 *)((long)register0x00000020 + -0x130)
                                                       = *(undefined8 *)
                                                          ((long)register0x00000020 + -0x1a0);
                                                  *(undefined8 *)((long)register0x00000020 + -0x140)
                                                       = *(undefined8 *)
                                                          ((long)register0x00000020 + -0x10);
                                                  lVar7 = *(long *)((long)register0x00000020 + 0x20)
                                                  ;
LAB_01719947:
                                                  if (*(long *)(lVar7 + 0x18) < 2)
                                                  goto LAB_01719a65;
                                                  if (*(undefined8 **)
                                                       ((long)register0x00000020 + -0x148) ==
                                                      (undefined8 *)0x0) {
                                                    *(undefined1 **)
                                                     ((long)register0x00000020 + -0x148) =
                                                         (undefined1 *)
                                                         ((long)register0x00000020 + -0x148);
                                                  }
                                                  else {
                                                    puVar18 = (undefined8 *)
                                                              ((long)register0x00000020 + -0x148);
                                                    if (*(undefined8 **)
                                                         ((long)register0x00000020 + -0x148) !=
                                                        puVar18) {
                                                      puVar12 = &DAT_01f393c0;
                                                      *(undefined8 *)
                                                       ((long)register0x00000020 + -0x2c0) =
                                                           0x171b3cc;
                                                      runtime_gopanic();
                                                      goto LAB_0171b3cc;
                                                    }
                                                  }
                                                  uVar11 = *(ulong *)((long)register0x00000020 +
                                                                     -0x130);
                                                  uVar13 = *(long *)((long)register0x00000020 +
                                                                    -0x138) + 0x17;
                                                  uVar6 = *(undefined8 *)
                                                           ((long)register0x00000020 + -0x140);
                                                  if (uVar11 < uVar13) {
                                                    *(long *)((long)register0x00000020 + -0x1a0) =
                                                         *(long *)((long)register0x00000020 + -0x138
                                                                  );
                                                    *(undefined8 *)
                                                     ((long)register0x00000020 + -0x2c0) = 0x17199cc
                                                    ;
                                                    uVar6 = runtime_growslice(0x17,&DAT_0194e2a0);
                                                  }
                                                  *(ulong *)((long)register0x00000020 + -0x1a0) =
                                                       uVar11;
                                                  *(ulong *)((long)register0x00000020 + -0x1a8) =
                                                       uVar13;
                                                  *(undefined8 *)((long)register0x00000020 + -0x10)
                                                       = uVar6;
                                                  *(undefined8 *)((long)register0x00000020 + -0x2c0)
                                                       = 0x1719a05;
                                                  runtime_memmove();
                                                  *(undefined8 *)((long)register0x00000020 + -0x138)
                                                       = *(undefined8 *)
                                                          ((long)register0x00000020 + -0x1a8);
                                                  *(undefined8 *)((long)register0x00000020 + -0x130)
                                                       = *(undefined8 *)
                                                          ((long)register0x00000020 + -0x1a0);
                                                  *(undefined8 *)((long)register0x00000020 + -0x140)
                                                       = *(undefined8 *)
                                                          ((long)register0x00000020 + -0x10);
                                                  lVar7 = *(long *)((long)register0x00000020 + 0x20)
                                                  ;
                                                  uVar13 = *(long *)(lVar7 + 0x18) - 1;
                                                  if (*(ulong *)(lVar7 + 0x20) < uVar13)
                                                  goto LAB_0171b3b1;
                                                  *(ulong *)((long)register0x00000020 + -0x1a0) =
                                                       uVar13;
                                                  puVar12 = *(undefined8 **)(lVar7 + 0x10);
                                                  lVar8 = 0;
                                                  break;
                                                  }
                                                  if (*(undefined1 **)
                                                       ((long)register0x00000020 + -0x148) ==
                                                      (undefined1 *)
                                                      ((long)register0x00000020 + -0x148))
                                                  goto LAB_0171b7a3;
LAB_0171b94c:
                                                  *(undefined8 *)((long)register0x00000020 + -0x2c0)
                                                       = 0x171b95f;
                                                  runtime_gopanic();
LAB_0171b95f:
                                                  *(undefined8 *)((long)register0x00000020 + -0x2c0)
                                                       = 0x171b972;
                                                  runtime_gopanic();
LAB_0171b972:
                                                  *(undefined8 *)((long)register0x00000020 + -0x2c0)
                                                       = 0x171b985;
                                                  runtime_gopanic();
                                                  }
                                                  else if (*(undefined1 **)
                                                            ((long)register0x00000020 + -0x148) ==
                                                           (undefined1 *)
                                                           ((long)register0x00000020 + -0x148))
                                                  goto LAB_01719885;
                                                  *(undefined8 *)((long)register0x00000020 + -0x2c0)
                                                       = 0x171b998;
                                                  runtime_gopanic();
                                                  param_4 = puVar12;
                                                  }
                                                  else if (*(undefined1 **)
                                                            ((long)register0x00000020 + -0x148) ==
                                                           (undefined1 *)
                                                           ((long)register0x00000020 + -0x148))
                                                  goto LAB_017197a4;
                                                  *(undefined8 *)((long)register0x00000020 + -0x2c0)
                                                       = 0x171b9ab;
                                                  runtime_gopanic();
                                                  }
                                                  else if (*(undefined1 **)
                                                            ((long)register0x00000020 + -0x148) ==
                                                           (undefined1 *)
                                                           ((long)register0x00000020 + -0x148))
                                                  goto LAB_017196af;
                                                  *(undefined8 *)((long)register0x00000020 + -0x2c0)
                                                       = 0x171b9be;
                                                  runtime_gopanic();
                                                  }
                                                  else if (*(undefined1 **)
                                                            ((long)register0x00000020 + -0x148) ==
                                                           (undefined1 *)
                                                           ((long)register0x00000020 + -0x148))
                                                  goto LAB_017195cf;
                                                  *(undefined8 *)((long)register0x00000020 + -0x2c0)
                                                       = 0x171b9d1;
                                                  runtime_gopanic();
                                                  }
                                                  else if (*(undefined1 **)
                                                            ((long)register0x00000020 + -0x148) ==
                                                           (undefined1 *)
                                                           ((long)register0x00000020 + -0x148))
                                                  goto LAB_017194ef;
                                                  *(undefined8 *)((long)register0x00000020 + -0x2c0)
                                                       = 0x171b9e5;
                                                  runtime_gopanic();
                                                  }
                                                  else if (*(undefined1 **)
                                                            ((long)register0x00000020 + -0x148) ==
                                                           (undefined1 *)
                                                           ((long)register0x00000020 + -0x148))
                                                  goto LAB_0171940f;
                                                  *(undefined8 *)((long)register0x00000020 + -0x2c0)
                                                       = 0x171b9f8;
                                                  runtime_gopanic();
                                                  }
                                                  else if (*(undefined1 **)
                                                            ((long)register0x00000020 + -0x148) ==
                                                           (undefined1 *)
                                                           ((long)register0x00000020 + -0x148))
                                                  goto LAB_0171932f;
                                                  *(undefined8 *)((long)register0x00000020 + -0x2c0)
                                                       = 0x171ba0b;
                                                  runtime_gopanic();
                                                  }
                                                  else if (*(undefined1 **)
                                                            ((long)register0x00000020 + -0x148) ==
                                                           (undefined1 *)
                                                           ((long)register0x00000020 + -0x148))
                                                  goto LAB_0171924f;
                                                  *(undefined8 *)((long)register0x00000020 + -0x2c0)
                                                       = 0x171ba1e;
                                                  runtime_gopanic();
                                                  }
                                                  else if (*(undefined1 **)
                                                            ((long)register0x00000020 + -0x148) ==
                                                           (undefined1 *)
                                                           ((long)register0x00000020 + -0x148))
                                                  goto LAB_0171916d;
                                                  *(undefined8 *)((long)register0x00000020 + -0x2c0)
                                                       = 0x171ba31;
                                                  runtime_gopanic();
                                                  }
                                                  else if (*(undefined1 **)
                                                            ((long)register0x00000020 + -0x148) ==
                                                           (undefined1 *)
                                                           ((long)register0x00000020 + -0x148))
                                                  goto LAB_017190dd;
                                                  *(undefined8 *)((long)register0x00000020 + -0x2c0)
                                                       = 0x171ba45;
                                                  runtime_gopanic();
                                                  }
                                                  else if (*(undefined1 **)
                                                            ((long)register0x00000020 + -0x148) ==
                                                           (undefined1 *)
                                                           ((long)register0x00000020 + -0x148))
                                                  goto LAB_01718ffd;
                                                  *(undefined8 *)((long)register0x00000020 + -0x2c0)
                                                       = 0x171ba58;
                                                  runtime_gopanic();
                                                  }
                                                  else if (*(undefined1 **)
                                                            ((long)register0x00000020 + -0x148) ==
                                                           (undefined1 *)
                                                           ((long)register0x00000020 + -0x148))
                                                  goto LAB_01718f1d;
                                                  *(undefined8 *)((long)register0x00000020 + -0x2c0)
                                                       = 0x171ba6b;
                                                  runtime_gopanic();
                                                  }
                                                  else if (*(undefined1 **)
                                                            ((long)register0x00000020 + -0x148) ==
                                                           (undefined1 *)
                                                           ((long)register0x00000020 + -0x148))
                                                  goto LAB_01718e3d;
                                                  *(undefined8 *)((long)register0x00000020 + -0x2c0)
                                                       = 0x171ba7e;
                                                  runtime_gopanic();
                                                  }
                                                  else if (*(undefined1 **)
                                                            ((long)register0x00000020 + -0x148) ==
                                                           (undefined1 *)
                                                           ((long)register0x00000020 + -0x148))
                                                  goto LAB_01718d5d;
                                                  *(undefined8 *)((long)register0x00000020 + -0x2c0)
                                                       = 0x171ba91;
                                                  runtime_gopanic();
                                                  }
                                                  else if (*(undefined1 **)
                                                            ((long)register0x00000020 + -0x148) ==
                                                           (undefined1 *)
                                                           ((long)register0x00000020 + -0x148))
                                                  goto LAB_01718c7c;
                                                  *(undefined8 *)((long)register0x00000020 + -0x2c0)
                                                       = 0x171baa5;
                                                  runtime_gopanic();
                                                  }
                                                  else if (*(undefined1 **)
                                                            ((long)register0x00000020 + -0x148) ==
                                                           (undefined1 *)
                                                           ((long)register0x00000020 + -0x148))
                                                  goto LAB_01718bef;
                                                  *(undefined8 *)((long)register0x00000020 + -0x2c0)
                                                       = 0x171bab8;
                                                  runtime_gopanic();
                                                  }
                                                  else if (*(undefined1 **)
                                                            ((long)register0x00000020 + -0x148) ==
                                                           (undefined1 *)
                                                           ((long)register0x00000020 + -0x148))
                                                  goto LAB_01718b0f;
                                                  *(undefined8 *)((long)register0x00000020 + -0x2c0)
                                                       = 0x171bacb;
                                                  runtime_gopanic();
                                                  }
                                                  else if (*(undefined1 **)
                                                            ((long)register0x00000020 + -0x148) ==
                                                           (undefined1 *)
                                                           ((long)register0x00000020 + -0x148))
                                                  goto LAB_01718a2f;
                                                  *(undefined8 *)((long)register0x00000020 + -0x2c0)
                                                       = 0x171bade;
                                                  runtime_gopanic();
                                                  }
                                                  else if (*(undefined1 **)
                                                            ((long)register0x00000020 + -0x148) ==
                                                           (undefined1 *)
                                                           ((long)register0x00000020 + -0x148))
                                                  goto LAB_0171894f;
                                                  *(undefined8 *)((long)register0x00000020 + -0x2c0)
                                                       = 0x171baf1;
                                                  runtime_gopanic();
                                                  }
                                                  else if (*(undefined1 **)
                                                            ((long)register0x00000020 + -0x148) ==
                                                           (undefined1 *)
                                                           ((long)register0x00000020 + -0x148))
                                                  goto LAB_0171886d;
                                                  *(undefined8 *)((long)register0x00000020 + -0x2c0)
                                                       = 0x171bb05;
                                                  runtime_gopanic();
                                                  }
                                                  else if (*(undefined1 **)
                                                            ((long)register0x00000020 + -0x148) ==
                                                           (undefined1 *)
                                                           ((long)register0x00000020 + -0x148))
                                                  goto LAB_017187dd;
                                                  *(undefined8 *)((long)register0x00000020 + -0x2c0)
                                                       = 0x171bb18;
                                                  runtime_gopanic();
                                                  }
                                                  else if (*(undefined1 **)
                                                            ((long)register0x00000020 + -0x148) ==
                                                           (undefined1 *)
                                                           ((long)register0x00000020 + -0x148))
                                                  goto LAB_017186fd;
                                                  *(undefined8 *)((long)register0x00000020 + -0x2c0)
                                                       = 0x171bb2b;
                                                  runtime_gopanic();
                                                  }
                                                  else if (*(undefined1 **)
                                                            ((long)register0x00000020 + -0x148) ==
                                                           (undefined1 *)
                                                           ((long)register0x00000020 + -0x148))
                                                  goto LAB_0171861d;
                                                  *(undefined8 *)((long)register0x00000020 + -0x2c0)
                                                       = 0x171bb3e;
                                                  runtime_gopanic();
                                                  }
                                                  else if (*(undefined1 **)
                                                            ((long)register0x00000020 + -0x148) ==
                                                           (undefined1 *)
                                                           ((long)register0x00000020 + -0x148))
                                                  goto LAB_0171853d;
                                                  *(undefined8 *)((long)register0x00000020 + -0x2c0)
                                                       = 0x171bb51;
                                                  runtime_gopanic();
                                                  }
                                                  else if (*(undefined1 **)
                                                            ((long)register0x00000020 + -0x148) ==
                                                           (undefined1 *)
                                                           ((long)register0x00000020 + -0x148))
                                                  goto LAB_0171845c;
                                                  *(undefined8 *)((long)register0x00000020 + -0x2c0)
                                                       = 0x171bb65;
                                                  runtime_gopanic();
                                                  }
                                                  else if (*(undefined1 **)
                                                            ((long)register0x00000020 + -0x148) ==
                                                           (undefined1 *)
                                                           ((long)register0x00000020 + -0x148))
                                                  goto LAB_017183cf;
                                                  *(undefined8 *)((long)register0x00000020 + -0x2c0)
                                                       = 0x171bb78;
                                                  runtime_gopanic();
                                                  }
                                                  else if (*(undefined1 **)
                                                            ((long)register0x00000020 + -0x148) ==
                                                           (undefined1 *)
                                                           ((long)register0x00000020 + -0x148))
                                                  goto LAB_017182ef;
                                                  *(undefined8 *)((long)register0x00000020 + -0x2c0)
                                                       = 0x171bb8b;
                                                  runtime_gopanic();
                                                  }
                                                  else if (*(undefined1 **)
                                                            ((long)register0x00000020 + -0x148) ==
                                                           (undefined1 *)
                                                           ((long)register0x00000020 + -0x148))
                                                  goto LAB_0171820f;
                                                  *(undefined8 *)((long)register0x00000020 + -0x2c0)
                                                       = 0x171bb9e;
                                                  runtime_gopanic();
                                                  }
                                                  else if (*(undefined1 **)
                                                            ((long)register0x00000020 + -0x148) ==
                                                           (undefined1 *)
                                                           ((long)register0x00000020 + -0x148))
                                                  goto LAB_0171812d;
                                                  *(undefined8 *)((long)register0x00000020 + -0x2c0)
                                                       = 0x171bbb1;
                                                  runtime_gopanic();
                                                  }
                                                  else if (*(undefined1 **)
                                                            ((long)register0x00000020 + -0x148) ==
                                                           (undefined1 *)
                                                           ((long)register0x00000020 + -0x148))
                                                  goto LAB_0171809d;
                                                  *(undefined8 *)((long)register0x00000020 + -0x2c0)
                                                       = 0x171bbc5;
                                                  runtime_gopanic();
                                                  }
                                                  else if (*(undefined1 **)
                                                            ((long)register0x00000020 + -0x148) ==
                                                           (undefined1 *)
                                                           ((long)register0x00000020 + -0x148))
                                                  goto LAB_01717fbd;
                                                  *(undefined8 *)((long)register0x00000020 + -0x2c0)
                                                       = 0x171bbd8;
                                                  runtime_gopanic();
                                                  }
                                                  else if (*(undefined1 **)
                                                            ((long)register0x00000020 + -0x148) ==
                                                           (undefined1 *)
                                                           ((long)register0x00000020 + -0x148))
                                                  goto LAB_01717edd;
                                                  *(undefined8 *)((long)register0x00000020 + -0x2c0)
                                                       = 0x171bbeb;
                                                  runtime_gopanic();
                                                  }
                                                  else if (*(undefined1 **)
                                                            ((long)register0x00000020 + -0x148) ==
                                                           (undefined1 *)
                                                           ((long)register0x00000020 + -0x148))
                                                  goto LAB_01717dfd;
                                                  *(undefined8 *)((long)register0x00000020 + -0x2c0)
                                                       = 0x171bbfe;
                                                  runtime_gopanic();
                                                  }
                                                  else if (*(undefined1 **)
                                                            ((long)register0x00000020 + -0x148) ==
                                                           (undefined1 *)
                                                           ((long)register0x00000020 + -0x148))
                                                  goto LAB_01717d1d;
                                                  *(undefined8 *)((long)register0x00000020 + -0x2c0)
                                                       = 0x171bc11;
                                                  runtime_gopanic();
                                                  }
                                                  else if (*(undefined1 **)
                                                            ((long)register0x00000020 + -0x148) ==
                                                           (undefined1 *)
                                                           ((long)register0x00000020 + -0x148))
                                                  goto LAB_01717c3d;
                                                  *(undefined8 *)((long)register0x00000020 + -0x2c0)
                                                       = 0x171bc25;
                                                  runtime_gopanic();
                                                  }
                                                  else if (*(undefined1 **)
                                                            ((long)register0x00000020 + -0x148) ==
                                                           (undefined1 *)
                                                           ((long)register0x00000020 + -0x148))
                                                  goto LAB_01717b5c;
                                                  *(undefined8 *)((long)register0x00000020 + -0x2c0)
                                                       = 0x171bc38;
                                                  runtime_gopanic();
                                                  }
                                                  else if (*(undefined1 **)
                                                            ((long)register0x00000020 + -0x148) ==
                                                           (undefined1 *)
                                                           ((long)register0x00000020 + -0x148))
                                                  goto LAB_01717acf;
                                                  *(undefined8 *)((long)register0x00000020 + -0x2c0)
                                                       = 0x171bc4b;
                                                  runtime_gopanic();
                                                  }
                                                  else if (*(undefined1 **)
                                                            ((long)register0x00000020 + -0x148) ==
                                                           (undefined1 *)
                                                           ((long)register0x00000020 + -0x148))
                                                  goto LAB_017179ef;
                                                  *(undefined8 *)((long)register0x00000020 + -0x2c0)
                                                       = 0x171bc5e;
                                                  runtime_gopanic();
                                                  }
                                                  else if (*(undefined1 **)
                                                            ((long)register0x00000020 + -0x148) ==
                                                           (undefined1 *)
                                                           ((long)register0x00000020 + -0x148))
                                                  goto LAB_0171790f;
                                                  *(undefined8 *)((long)register0x00000020 + -0x2c0)
                                                       = 0x171bc71;
                                                  runtime_gopanic();
                                                  }
                                                  else if (*(undefined1 **)
                                                            ((long)register0x00000020 + -0x148) ==
                                                           (undefined1 *)
                                                           ((long)register0x00000020 + -0x148))
                                                  goto LAB_0171782f;
                                                  *(undefined8 *)((long)register0x00000020 + -0x2c0)
                                                       = 0x171bc85;
                                                  runtime_gopanic();
                                                  }
                                                  else if (*(undefined1 **)
                                                            ((long)register0x00000020 + -0x148) ==
                                                           (undefined1 *)
                                                           ((long)register0x00000020 + -0x148))
                                                  goto LAB_01717751;
                                                  *(undefined8 *)((long)register0x00000020 + -0x2c0)
                                                       = 0x171bc98;
                                                  runtime_gopanic();
                                                  }
                                                  else if (*(undefined1 **)
                                                            ((long)register0x00000020 + -0x148) ==
                                                           (undefined1 *)
                                                           ((long)register0x00000020 + -0x148))
                                                  goto LAB_01717674;
                                                  *(undefined8 *)((long)register0x00000020 + -0x2c0)
                                                       = 0x171bcab;
                                                  runtime_gopanic();
                                                  }
                                                  else if (*(undefined1 **)
                                                            ((long)register0x00000020 + -0x148) ==
                                                           (undefined1 *)
                                                           ((long)register0x00000020 + -0x148))
                                                  goto LAB_01717597;
                                                  *(undefined8 *)((long)register0x00000020 + -0x2c0)
                                                       = 0x171bcbe;
                                                  runtime_gopanic();
                                                }
                                                else if (*(undefined1 **)
                                                          ((long)register0x00000020 + -0x148) ==
                                                         (undefined1 *)
                                                         ((long)register0x00000020 + -0x148))
                                                goto LAB_01717505;
                                                *(undefined8 *)((long)register0x00000020 + -0x2c0) =
                                                     0x171bcd1;
                                                runtime_gopanic();
                                              }
                                              else if (*(undefined1 **)
                                                        ((long)register0x00000020 + -0x148) ==
                                                       (undefined1 *)
                                                       ((long)register0x00000020 + -0x148))
                                              goto LAB_01717425;
                                              *(undefined8 *)((long)register0x00000020 + -0x2c0) =
                                                   0x171bce5;
                                              runtime_gopanic();
                                            }
                                            else if (*(undefined1 **)
                                                      ((long)register0x00000020 + -0x148) ==
                                                     (undefined1 *)
                                                     ((long)register0x00000020 + -0x148))
                                            goto LAB_01717345;
                                            *(undefined8 *)((long)register0x00000020 + -0x2c0) =
                                                 0x171bcf8;
                                            runtime_gopanic();
                                          }
                                          else if (*(undefined1 **)
                                                    ((long)register0x00000020 + -0x148) ==
                                                   (undefined1 *)((long)register0x00000020 + -0x148)
                                                  ) goto LAB_01717265;
                                          *(undefined8 *)((long)register0x00000020 + -0x2c0) =
                                               0x171bd0b;
                                          runtime_gopanic();
                                        }
                                        else if (*(undefined1 **)((long)register0x00000020 + -0x148)
                                                 == (undefined1 *)
                                                    ((long)register0x00000020 + -0x148))
                                        goto LAB_01717185;
                                        *(undefined8 *)((long)register0x00000020 + -0x2c0) =
                                             0x171bd1e;
                                        runtime_gopanic();
                                      }
                                      else if (*(undefined1 **)((long)register0x00000020 + -0x148)
                                               == (undefined1 *)((long)register0x00000020 + -0x148))
                                      goto LAB_017170a5;
                                      *(undefined8 *)((long)register0x00000020 + -0x2c0) = 0x171bd31
                                      ;
                                      runtime_gopanic();
                                    }
                                    else if (*(undefined1 **)((long)register0x00000020 + -0x148) ==
                                             (undefined1 *)((long)register0x00000020 + -0x148))
                                    goto LAB_01716fc5;
                                    *(undefined8 *)((long)register0x00000020 + -0x2c0) = 0x171bd45;
                                    runtime_gopanic();
                                  }
                                  else if (*(undefined1 **)((long)register0x00000020 + -0x148) ==
                                           (undefined1 *)((long)register0x00000020 + -0x148))
                                  goto LAB_01716ee5;
                                  *(undefined8 *)((long)register0x00000020 + -0x2c0) = 0x171bd58;
                                  runtime_gopanic();
                                }
                                else if (*(undefined1 **)((long)register0x00000020 + -0x148) ==
                                         (undefined1 *)((long)register0x00000020 + -0x148))
                                goto LAB_01716e01;
                                *(undefined8 *)((long)register0x00000020 + -0x2c0) = 0x171bd6b;
                                runtime_gopanic();
                              }
                              else if (*(undefined1 **)((long)register0x00000020 + -0x148) ==
                                       (undefined1 *)((long)register0x00000020 + -0x148))
                              goto LAB_01716d74;
                              *(undefined8 *)((long)register0x00000020 + -0x2c0) = 0x171bd7e;
                              runtime_gopanic();
                            }
                            else if (*(undefined1 **)((long)register0x00000020 + -0x148) ==
                                     (undefined1 *)((long)register0x00000020 + -0x148))
                            goto LAB_01716c97;
                            *(undefined8 *)((long)register0x00000020 + -0x2c0) = 0x171bd91;
                            runtime_gopanic();
                          }
                          else if (*(undefined1 **)((long)register0x00000020 + -0x148) ==
                                   (undefined1 *)((long)register0x00000020 + -0x148))
                          goto LAB_01716c05;
                          *(undefined8 *)((long)register0x00000020 + -0x2c0) = 0x171bda5;
                          runtime_gopanic();
                        }
                        else if (*(undefined1 **)((long)register0x00000020 + -0x148) ==
                                 (undefined1 *)((long)register0x00000020 + -0x148))
                        goto LAB_01716b25;
                        *(undefined8 *)((long)register0x00000020 + -0x2c0) = 0x171bdb8;
                        runtime_gopanic();
                      }
                      else if (*(undefined1 **)((long)register0x00000020 + -0x148) ==
                               (undefined1 *)((long)register0x00000020 + -0x148)) goto LAB_01716a45;
                      *(undefined8 *)((long)register0x00000020 + -0x2c0) = 0x171bdcb;
                      runtime_gopanic();
                    }
                    else if (*(undefined1 **)((long)register0x00000020 + -0x148) ==
                             (undefined1 *)((long)register0x00000020 + -0x148)) goto LAB_01716965;
                    *(undefined8 *)((long)register0x00000020 + -0x2c0) = 0x171bdde;
                    runtime_gopanic();
                  }
                  else if (*(undefined1 **)((long)register0x00000020 + -0x148) ==
                           (undefined1 *)((long)register0x00000020 + -0x148)) goto LAB_01716885;
                  *(undefined8 *)((long)register0x00000020 + -0x2c0) = 0x171bdf1;
                  runtime_gopanic();
                }
                else if (*(undefined1 **)((long)register0x00000020 + -0x148) ==
                         (undefined1 *)((long)register0x00000020 + -0x148)) goto LAB_017167a5;
                *(undefined8 *)((long)register0x00000020 + -0x2c0) = 0x171be05;
                runtime_gopanic();
              }
              else if (*(undefined1 **)((long)register0x00000020 + -0x148) ==
                       (undefined1 *)((long)register0x00000020 + -0x148)) goto LAB_017166c5;
              *(undefined8 *)((long)register0x00000020 + -0x2c0) = 0x171be18;
              runtime_gopanic();
            }
            else if (*(undefined1 **)((long)register0x00000020 + -0x148) ==
                     (undefined1 *)((long)register0x00000020 + -0x148)) goto LAB_017165e5;
            *(undefined8 *)((long)register0x00000020 + -0x2c0) = 0x171be2b;
            runtime_gopanic();
          }
          else if (*(undefined1 **)((long)register0x00000020 + -0x148) ==
                   (undefined1 *)((long)register0x00000020 + -0x148)) goto LAB_017164fd;
          *(undefined8 *)((long)register0x00000020 + -0x2c0) = 0x171be3e;
          runtime_gopanic();
        }
        else if (*(undefined1 **)((long)register0x00000020 + -0x148) ==
                 (undefined1 *)((long)register0x00000020 + -0x148)) goto LAB_0171641d;
        *(undefined8 *)((long)register0x00000020 + -0x2c0) = 0x171be51;
        runtime_gopanic();
LAB_0171be51:
        *(undefined8 *)((long)register0x00000020 + -0x2c0) = 0x171be65;
        runtime_gopanic();
      }
      else {
        *(long *)((long)register0x00000020 + -0x228) = lVar7;
        *(undefined8 *)((long)register0x00000020 + -0x158) = uVar6;
        param_4 = (undefined8 *)&DAT_01c4d5b2;
        param_1 = (undefined8 *)0xf;
        *(undefined8 *)((long)register0x00000020 + -0x2c0) = 0x17161af;
        lVar7 = internal_stringslite_Index();
        if (lVar7 < 0) {
          param_4 = (undefined8 *)&DAT_01c4f203;
          param_1 = (undefined8 *)&DAT_00000010;
          *(undefined8 *)((long)register0x00000020 + -0x2c0) = 0x17161dd;
          lVar7 = internal_stringslite_Index();
          bVar20 = -1 < lVar7;
        }
        else {
          bVar20 = true;
        }
        if (bVar20) goto LAB_017163e3;
        puVar12 = *(undefined8 **)((long)register0x00000020 + -0x228);
        if ((long)puVar12 < 0xc351) {
          uVar6 = *(undefined8 *)((long)register0x00000020 + -0x158);
        }
        else {
          puVar12 = *(undefined8 **)((long)register0x00000020 + -0x158);
          param_4 = (undefined8 *)0xc350;
          param_1 = (undefined8 *)&DAT_01c68ca4;
          *(undefined8 *)((long)register0x00000020 + -0x2c0) = 0x1716239;
          uVar6 = runtime_concatstring2(&DAT_01c68ca4,0x1e);
        }
        if (*(undefined1 **)((long)register0x00000020 + -0x148) == (undefined1 *)0x0) {
          *(undefined1 **)((long)register0x00000020 + -0x148) =
               (undefined1 *)((long)register0x00000020 + -0x148);
LAB_01716272:
          puVar10 = *(undefined1 **)((long)register0x00000020 + -0x130);
          lVar7 = *(long *)((long)register0x00000020 + -0x138);
          puVar1 = (undefined1 *)((long)puVar12 + lVar7);
          in_R10 = *(undefined8 *)((long)register0x00000020 + -0x140);
          param_4 = puVar12;
          if (puVar10 < puVar1) {
            *(long *)((long)register0x00000020 + -0x1a0) = lVar7;
            *(undefined8 **)((long)register0x00000020 + -0x228) = puVar12;
            *(undefined8 *)((long)register0x00000020 + -0x158) = uVar6;
            *(undefined8 *)((long)register0x00000020 + -0x2c0) = 0x17162c5;
            in_R10 = runtime_growslice(puVar12,&DAT_0194e2a0,lVar7,puVar10,
                                  (undefined1 *)((long)register0x00000020 + -0x148));
            param_4 = *(undefined8 **)((long)register0x00000020 + -0x228);
            param_1 = puVar12;
          }
          *(undefined1 **)((long)register0x00000020 + -0x1a0) = puVar10;
          *(undefined1 **)((long)register0x00000020 + -0x1a8) = puVar1;
          *(undefined8 *)((long)register0x00000020 + -0x10) = in_R10;
          *(undefined8 *)((long)register0x00000020 + -0x2c0) = 0x171630c;
          runtime_memmove();
          *(undefined8 *)((long)register0x00000020 + -0x138) =
               *(undefined8 *)((long)register0x00000020 + -0x1a8);
          *(undefined8 *)((long)register0x00000020 + -0x130) =
               *(undefined8 *)((long)register0x00000020 + -0x1a0);
          *(undefined8 *)((long)register0x00000020 + -0x140) =
               *(undefined8 *)((long)register0x00000020 + -0x10);
          if (*(undefined1 **)((long)register0x00000020 + -0x148) == (undefined1 *)0x0) {
            *(undefined1 **)((long)register0x00000020 + -0x148) =
                 (undefined1 *)((long)register0x00000020 + -0x148);
LAB_01716375:
            param_4 = *(undefined8 **)((long)register0x00000020 + -0x130);
            lVar7 = *(long *)((long)register0x00000020 + -0x138);
            puVar12 = (undefined8 *)(lVar7 + 2);
            lVar8 = *(long *)((long)register0x00000020 + -0x140);
            if (param_4 < puVar12) {
              *(long *)((long)register0x00000020 + -0x1a0) = lVar7;
              param_1 = (undefined8 *)0x2;
              *(undefined8 *)((long)register0x00000020 + -0x2c0) = 0x17163b2;
              lVar8 = runtime_growslice(2,&DAT_0194e2a0,puVar12,param_4,
                                   (undefined1 *)((long)register0x00000020 + -0x148));
              lVar7 = *(long *)((long)register0x00000020 + -0x1a0);
            }
            *(undefined2 *)(lVar8 + lVar7) = 0xa0a;
            *(undefined8 **)((long)register0x00000020 + -0x138) = puVar12;
            *(undefined8 **)((long)register0x00000020 + -0x130) = param_4;
            *(long *)((long)register0x00000020 + -0x140) = lVar8;
            goto LAB_017163e3;
          }
          if (*(undefined1 **)((long)register0x00000020 + -0x148) ==
              (undefined1 *)((long)register0x00000020 + -0x148)) goto LAB_01716375;
          goto LAB_0171be51;
        }
        if (*(undefined1 **)((long)register0x00000020 + -0x148) ==
            (undefined1 *)((long)register0x00000020 + -0x148)) goto LAB_01716272;
      }
      unaff_RBX = &DAT_01f393c0;
      *(undefined8 *)((long)register0x00000020 + -0x2c0) = 0x171be78;
      in_RAX = runtime_gopanic();
    }
    *(undefined8 *)(puVar16 + 8) = in_RAX;
    *(undefined8 **)(puVar16 + 0x10) = unaff_RBX;
    *(undefined8 **)(puVar16 + 0x18) = param_4;
    *(undefined8 **)(puVar16 + 0x20) = param_1;
    *(undefined8 *)(puVar16 + -8) = 0x171be92;
    runtime_morestack_noctxt();
    in_RAX = *(undefined8 *)(puVar16 + 8);
    unaff_RBX = *(undefined8 **)(puVar16 + 0x10);
    param_4 = *(undefined8 **)(puVar16 + 0x18);
    param_1 = *(undefined8 **)(puVar16 + 0x20);
    register0x00000020 = (BADSPACEBASE *)puVar16;
    unaff_RBP = puVar17;
  } while( true );
LAB_0171a46c:
  if (lVar8 < (long)uVar13) {
    *(long *)((long)register0x00000020 + -0x1c0) = lVar8;
    *(undefined8 **)((long)register0x00000020 + -0x18) = puVar12;
    uVar6 = puVar12[1];
    *(undefined8 *)((long)register0x00000020 + -0xd8) = *puVar12;
    *(undefined8 *)((long)register0x00000020 + -0xd0) = uVar6;
    uVar6 = puVar12[3];
    *(undefined8 *)((long)register0x00000020 + -200) = puVar12[2];
    *(undefined8 *)((long)register0x00000020 + -0xc0) = uVar6;
    uVar2 = *(undefined4 *)((long)puVar12 + 0x24);
    uVar3 = *(undefined4 *)(puVar12 + 5);
    uVar4 = *(undefined4 *)((long)puVar12 + 0x2c);
    *(undefined4 *)((long)register0x00000020 + -0xb8) = *(undefined4 *)(puVar12 + 4);
    *(undefined4 *)((long)register0x00000020 + -0xb4) = uVar2;
    *(undefined4 *)((long)register0x00000020 + -0xb0) = uVar3;
    *(undefined4 *)((long)register0x00000020 + -0xac) = uVar4;
    plVar19 = *(long **)((long)register0x00000020 + -0xd8);
    if (*(long *)((long)register0x00000020 + -0xd0) == 4) {
      if ((int)*plVar19 == 0x72657375) {
        lVar7 = *(long *)((long)register0x00000020 + -0xc0);
        *(undefined8 *)((long)register0x00000020 + -0x2c0) = 0x171a4e8;
        uVar6 = kiro2api_internal_logic_warp_getContentText();
        if (lVar7 != 0) {
          *(long *)((long)register0x00000020 + -0x230) = lVar7;
          *(undefined8 *)((long)register0x00000020 + -0x160) = uVar6;
          *(undefined8 *)((long)register0x00000020 + -0x58) = in_XMM15_Qa;
          *(undefined8 *)((long)register0x00000020 + -0x50) = in_XMM15_Qb;
          *(undefined8 *)((long)register0x00000020 + -0x48) = in_XMM15_Qa;
          *(undefined8 *)((long)register0x00000020 + -0x40) = in_XMM15_Qb;
          *(undefined8 *)((long)register0x00000020 + -0x2c0) = 0x171a525;
          uVar6 = runtime_convT64();
          *(undefined8 **)((long)register0x00000020 + -0x58) = &DAT_0194e460;
          *(undefined8 *)((long)register0x00000020 + -0x50) = uVar6;
          *(undefined8 *)((long)register0x00000020 + -0x2c0) = 0x171a551;
          uVar6 = runtime_convTstring();
          *(undefined8 **)((long)register0x00000020 + -0x48) = &DAT_0194e220;
          *(undefined8 *)((long)register0x00000020 + -0x40) = uVar6;
          *(undefined8 *)((long)register0x00000020 + -0x2c0) = 0x171a589;
          uVar6 = fmt_Sprintf();
          if (*(undefined1 **)((long)register0x00000020 + -0x148) == (undefined1 *)0x0) {
            *(undefined1 **)((long)register0x00000020 + -0x148) =
                 (undefined1 *)((long)register0x00000020 + -0x148);
          }
          else if (*(undefined1 **)((long)register0x00000020 + -0x148) !=
                   (undefined1 *)((long)register0x00000020 + -0x148)) {
LAB_0171b39e:
            *(undefined8 *)((long)register0x00000020 + -0x2c0) = 0x171b3b1;
            runtime_gopanic();
LAB_0171b3b1:
                    /* WARNING: Subroutine does not return */
            *(undefined8 *)((long)register0x00000020 + -0x2c0) = 0x171b3b9;
            runtime_panicSliceAcap();
          }
          uVar11 = *(ulong *)((long)register0x00000020 + -0x130);
          uVar13 = *(long *)((long)register0x00000020 + -0x138) + 0xf;
          uVar9 = *(undefined8 *)((long)register0x00000020 + -0x140);
          if (uVar11 < uVar13) {
            *(undefined8 *)((long)register0x00000020 + -0x1f0) = 0xf;
            *(undefined8 *)((long)register0x00000020 + -0x100) = uVar6;
            *(long *)((long)register0x00000020 + -0x1a8) =
                 *(long *)((long)register0x00000020 + -0x138);
            *(undefined8 *)((long)register0x00000020 + -0x2c0) = 0x171a608;
            uVar9 = runtime_growslice(0xf);
          }
          *(ulong *)((long)register0x00000020 + -0x1a8) = uVar11;
          *(ulong *)((long)register0x00000020 + -0x1b0) = uVar13;
          *(undefined8 *)((long)register0x00000020 + -0x10) = uVar9;
          *(undefined8 *)((long)register0x00000020 + -0x2c0) = 0x171a650;
          runtime_memmove();
          *(undefined8 *)((long)register0x00000020 + -0x138) =
               *(undefined8 *)((long)register0x00000020 + -0x1b0);
          *(undefined8 *)((long)register0x00000020 + -0x130) =
               *(undefined8 *)((long)register0x00000020 + -0x1a8);
          *(undefined8 *)((long)register0x00000020 + -0x140) =
               *(undefined8 *)((long)register0x00000020 + -0x10);
        }
        if (*(undefined8 **)((long)register0x00000020 + -200) == &DAT_0192e960) {
          puVar12 = (undefined8 *)**(undefined8 **)((long)register0x00000020 + -0xc0);
          for (lVar7 = (*(undefined8 **)((long)register0x00000020 + -0xc0))[1]; 0 < lVar7;
              lVar7 = lVar7 + -1) {
            if ((undefined *)*puVar12 == &DAT_01a233a0) {
              uVar6 = puVar12[1];
              *(undefined8 **)((long)register0x00000020 + -0x20) = puVar12;
              *(long *)((long)register0x00000020 + -0x1a8) = lVar7;
              *(undefined8 *)((long)register0x00000020 + -0x90) = uVar6;
              *(undefined8 *)((long)register0x00000020 + -0x2c0) = 0x171b0e5;
              puVar12 = (undefined8 *)runtime_mapaccess1_faststr(4);
              if ((undefined8 *)*puVar12 == &DAT_0194e220) {
                plVar19 = *(long **)puVar12[1];
                lVar7 = ((undefined8 *)puVar12[1])[1];
              }
              else {
                lVar7 = 0;
                plVar19 = (long *)0x0;
              }
              if ((((lVar7 == 0xb) && (*plVar19 == 0x7365725f6c6f6f74)) &&
                  ((short)plVar19[1] == 0x6c75)) && (*(char *)((long)plVar19 + 10) == 't')) {
                *(undefined8 *)((long)register0x00000020 + -0x2c0) = 0x171b166;
                puVar12 = (undefined8 *)runtime_mapaccess1_faststr(0xb);
                if ((undefined8 *)*puVar12 == &DAT_0194e220) {
                  uVar6 = *(undefined8 *)puVar12[1];
                  uVar9 = ((undefined8 *)puVar12[1])[1];
                }
                else {
                  uVar9 = 0;
                  uVar6 = 0;
                }
                *(undefined8 *)((long)register0x00000020 + -0x260) = uVar9;
                *(undefined8 *)((long)register0x00000020 + -400) = uVar6;
                *(undefined8 *)((long)register0x00000020 + -0x2c0) = 0x171b1b1;
                lVar7 = runtime_mapaccess1_faststr(7,uVar9,&DAT_0194e220,&DAT_01c3dd44);
                uVar6 = *(undefined8 *)(lVar7 + 8);
                *(undefined8 *)((long)register0x00000020 + -0x2c0) = 0x171b1c5;
                uVar9 = kiro2api_internal_logic_warp_getContentText();
                *(undefined8 *)((long)register0x00000020 + -0xe0) = uVar9;
                *(undefined8 *)((long)register0x00000020 + -0x1d0) = uVar6;
                *(undefined8 *)((long)register0x00000020 + -0x58) = in_XMM15_Qa;
                *(undefined8 *)((long)register0x00000020 + -0x50) = in_XMM15_Qb;
                *(undefined8 *)((long)register0x00000020 + -0x48) = in_XMM15_Qa;
                *(undefined8 *)((long)register0x00000020 + -0x40) = in_XMM15_Qb;
                *(undefined8 *)((long)register0x00000020 + -0x2c0) = 0x171b1f9;
                uVar6 = runtime_convTstring();
                *(undefined8 **)((long)register0x00000020 + -0x58) = &DAT_0194e220;
                *(undefined8 *)((long)register0x00000020 + -0x50) = uVar6;
                *(undefined8 *)((long)register0x00000020 + -0x2c0) = 0x171b225;
                uVar6 = runtime_convTstring();
                *(undefined8 **)((long)register0x00000020 + -0x48) = &DAT_0194e220;
                *(undefined8 *)((long)register0x00000020 + -0x40) = uVar6;
                *(undefined8 *)((long)register0x00000020 + -0x2c0) = 0x171b25d;
                uVar6 = fmt_Sprintf();
                if (*(undefined1 **)((long)register0x00000020 + -0x148) == (undefined1 *)0x0) {
                  *(undefined1 **)((long)register0x00000020 + -0x148) =
                       (undefined1 *)((long)register0x00000020 + -0x148);
                }
                else if (*(undefined1 **)((long)register0x00000020 + -0x148) !=
                         (undefined1 *)((long)register0x00000020 + -0x148)) {
                  *(undefined8 *)((long)register0x00000020 + -0x2c0) = 0x171b39e;
                  runtime_gopanic();
                  goto LAB_0171b39e;
                }
                uVar11 = *(ulong *)((long)register0x00000020 + -0x130);
                uVar13 = *(long *)((long)register0x00000020 + -0x138) + 0x18;
                uVar9 = *(undefined8 *)((long)register0x00000020 + -0x140);
                if (uVar11 < uVar13) {
                  *(undefined8 *)((long)register0x00000020 + -0x1f8) = 0x18;
                  *(undefined8 *)((long)register0x00000020 + -0x108) = uVar6;
                  *(long *)((long)register0x00000020 + -0x1b0) =
                       *(long *)((long)register0x00000020 + -0x138);
                  *(undefined8 *)((long)register0x00000020 + -0x2c0) = 0x171b2e5;
                  uVar9 = runtime_growslice(0x18);
                }
                *(ulong *)((long)register0x00000020 + -0x1b0) = uVar11;
                *(ulong *)((long)register0x00000020 + -0x1b8) = uVar13;
                *(undefined8 *)((long)register0x00000020 + -0x10) = uVar9;
                *(undefined8 *)((long)register0x00000020 + -0x2c0) = 0x171b32c;
                runtime_memmove();
                *(undefined8 *)((long)register0x00000020 + -0x138) =
                     *(undefined8 *)((long)register0x00000020 + -0x1b8);
                *(undefined8 *)((long)register0x00000020 + -0x130) =
                     *(undefined8 *)((long)register0x00000020 + -0x1b0);
                *(undefined8 *)((long)register0x00000020 + -0x140) =
                     *(undefined8 *)((long)register0x00000020 + -0x10);
              }
              lVar7 = *(long *)((long)register0x00000020 + -0x1a8);
              puVar12 = *(undefined8 **)((long)register0x00000020 + -0x20);
            }
            puVar12 = puVar12 + 2;
          }
        }
LAB_0171b06b:
        lVar8 = *(long *)((long)register0x00000020 + -0x1c0);
        uVar13 = *(ulong *)((long)register0x00000020 + -0x1a0);
        lVar7 = *(long *)((long)register0x00000020 + 0x20);
        puVar12 = *(undefined8 **)((long)register0x00000020 + -0x18);
      }
    }
    else if (((*(long *)((long)register0x00000020 + -0xd0) == 9) && (*plVar19 == 0x6e61747369737361)
             ) && ((char)plVar19[1] == 't')) {
      puVar12 = *(undefined8 **)((long)register0x00000020 + -0xc0);
      if (*(undefined8 **)((long)register0x00000020 + -200) == &DAT_0192e960) {
        puVar18 = (undefined8 *)*puVar12;
        for (lVar7 = puVar12[1]; 0 < lVar7; lVar7 = lVar7 + -1) {
          if ((undefined *)*puVar18 == &DAT_01a233a0) {
            uVar6 = puVar18[1];
            *(undefined8 **)((long)register0x00000020 + -0x20) = puVar18;
            *(long *)((long)register0x00000020 + -0x1a8) = lVar7;
            *(undefined8 *)((long)register0x00000020 + -0x98) = uVar6;
            *(undefined8 *)((long)register0x00000020 + -0x2c0) = 0x171aa5c;
            puVar12 = (undefined8 *)runtime_mapaccess1_faststr(4);
            if ((undefined8 *)*puVar12 == &DAT_0194e220) {
              plVar19 = *(long **)puVar12[1];
              lVar7 = ((undefined8 *)puVar12[1])[1];
            }
            else {
              lVar7 = 0;
              plVar19 = (long *)0x0;
            }
            if (((lVar7 == 8) && (*plVar19 == 0x676e696b6e696874)) ||
               ((lVar7 == 9 && ((*plVar19 == 0x6e696e6f73616572 && ((char)plVar19[1] == 'g')))))) {
              puVar18 = *(undefined8 **)((long)register0x00000020 + -0x20);
              lVar7 = *(long *)((long)register0x00000020 + -0x1a8);
            }
            else {
              if (lVar7 == 4) {
                if ((int)*plVar19 == 0x74786574) {
                  *(undefined8 *)((long)register0x00000020 + -0x2c0) = 0x171ab4b;
                  puVar12 = (undefined8 *)runtime_mapaccess1_faststr(4);
                  if ((undefined8 *)*puVar12 == &DAT_0194e220) {
                    uVar6 = *(undefined8 *)puVar12[1];
                    lVar7 = ((undefined8 *)puVar12[1])[1];
                  }
                  else {
                    lVar7 = 0;
                    uVar6 = 0;
                  }
                  if (lVar7 != 0) {
                    *(undefined8 *)((long)register0x00000020 + -0x168) = uVar6;
                    *(long *)((long)register0x00000020 + -0x238) = lVar7;
                    *(undefined8 *)((long)register0x00000020 + -0x58) = in_XMM15_Qa;
                    *(undefined8 *)((long)register0x00000020 + -0x50) = in_XMM15_Qb;
                    *(undefined8 *)((long)register0x00000020 + -0x48) = in_XMM15_Qa;
                    *(undefined8 *)((long)register0x00000020 + -0x40) = in_XMM15_Qb;
                    *(undefined8 *)((long)register0x00000020 + -0x2c0) = 0x171aba5;
                    uVar6 = runtime_convT64();
                    *(undefined8 **)((long)register0x00000020 + -0x58) = &DAT_0194e460;
                    *(undefined8 *)((long)register0x00000020 + -0x50) = uVar6;
                    *(undefined8 *)((long)register0x00000020 + -0x2c0) = 0x171abd1;
                    uVar6 = runtime_convTstring();
                    *(undefined8 **)((long)register0x00000020 + -0x48) = &DAT_0194e220;
                    *(undefined8 *)((long)register0x00000020 + -0x40) = uVar6;
                    *(undefined8 *)((long)register0x00000020 + -0x2c0) = 0x171ac09;
                    uVar6 = fmt_Sprintf();
                    if (*(undefined1 **)((long)register0x00000020 + -0x148) == (undefined1 *)0x0) {
                      *(undefined1 **)((long)register0x00000020 + -0x148) =
                           (undefined1 *)((long)register0x00000020 + -0x148);
                    }
                    else if (*(undefined1 **)((long)register0x00000020 + -0x148) !=
                             (undefined1 *)((long)register0x00000020 + -0x148)) goto LAB_0171b058;
                    uVar11 = *(ulong *)((long)register0x00000020 + -0x130);
                    uVar13 = *(long *)((long)register0x00000020 + -0x138) + 0x14;
                    uVar9 = *(undefined8 *)((long)register0x00000020 + -0x140);
                    if (uVar11 < uVar13) {
                      *(undefined8 *)((long)register0x00000020 + -0x200) = 0x14;
                      *(undefined8 *)((long)register0x00000020 + -0x110) = uVar6;
                      *(long *)((long)register0x00000020 + -0x1b0) =
                           *(long *)((long)register0x00000020 + -0x138);
                      *(undefined8 *)((long)register0x00000020 + -0x2c0) = 0x171ac88;
                      uVar9 = runtime_growslice(0x14);
                    }
                    *(ulong *)((long)register0x00000020 + -0x1b0) = uVar11;
                    *(ulong *)((long)register0x00000020 + -0x1b8) = uVar13;
                    *(undefined8 *)((long)register0x00000020 + -0x10) = uVar9;
                    *(undefined8 *)((long)register0x00000020 + -0x2c0) = 0x171acd0;
                    runtime_memmove();
                    *(undefined8 *)((long)register0x00000020 + -0x138) =
                         *(undefined8 *)((long)register0x00000020 + -0x1b8);
                    *(undefined8 *)((long)register0x00000020 + -0x130) =
                         *(undefined8 *)((long)register0x00000020 + -0x1b0);
                    *(undefined8 *)((long)register0x00000020 + -0x140) =
                         *(undefined8 *)((long)register0x00000020 + -0x10);
                  }
                }
              }
              else if ((lVar7 == 8) && (*plVar19 == 0x6573755f6c6f6f74)) {
                *(undefined8 *)((long)register0x00000020 + -0x2c0) = 0x171ad49;
                puVar12 = (undefined8 *)runtime_mapaccess1_faststr(2);
                if ((undefined8 *)*puVar12 == &DAT_0194e220) {
                  uVar6 = *(undefined8 *)puVar12[1];
                  uVar9 = ((undefined8 *)puVar12[1])[1];
                }
                else {
                  uVar9 = 0;
                  uVar6 = 0;
                }
                *(undefined8 *)((long)register0x00000020 + -0x250) = uVar9;
                *(undefined8 *)((long)register0x00000020 + -0x180) = uVar6;
                *(undefined8 *)((long)register0x00000020 + -0x2c0) = 0x171ad94;
                puVar12 = (undefined8 *)runtime_mapaccess1_faststr(4,uVar9,&DAT_0194e220,&DAT_01c39796);
                if ((undefined8 *)*puVar12 == &DAT_0194e220) {
                  uVar6 = *(undefined8 *)puVar12[1];
                  uVar9 = ((undefined8 *)puVar12[1])[1];
                }
                else {
                  uVar9 = 0;
                  uVar6 = 0;
                }
                *(undefined8 *)((long)register0x00000020 + -600) = uVar9;
                *(undefined8 *)((long)register0x00000020 + -0x188) = uVar6;
                *(undefined8 *)((long)register0x00000020 + -0x2c0) = 0x171ade5;
                runtime_mapaccess1_faststr(5,uVar9,&DAT_0194e220,&DAT_01c3a5e4);
                *(undefined8 *)((long)register0x00000020 + -0x2c0) = 0x171adf4;
                lVar8 = encoding_json_Marshal();
                *(undefined8 *)((long)register0x00000020 + -0x2c0) = 0x171ae05;
                auVar21 = runtime_slicebytetostring();
                lVar7 = auVar21._0_8_;
                if (500 < lVar8) {
                  *(undefined8 *)((long)register0x00000020 + -0x2c0) = 0x171ae29;
                  lVar7 = runtime_concatstring2(&DAT_01c38dc1,3,auVar21._8_8_,500);
                  lVar8 = auVar21._0_8_;
                }
                *(long *)((long)register0x00000020 + -0x1c8) = lVar8;
                *(long *)((long)register0x00000020 + -0xa8) = lVar7;
                *(undefined8 *)((long)register0x00000020 + -0x88) = in_XMM15_Qa;
                *(undefined8 *)((long)register0x00000020 + -0x80) = in_XMM15_Qb;
                *(undefined8 *)((long)register0x00000020 + -0x78) = in_XMM15_Qa;
                *(undefined8 *)((long)register0x00000020 + -0x70) = in_XMM15_Qb;
                *(undefined8 *)((long)register0x00000020 + -0x68) = in_XMM15_Qa;
                *(undefined8 *)((long)register0x00000020 + -0x60) = in_XMM15_Qb;
                *(undefined8 *)((long)register0x00000020 + -0x2c0) = 0x171ae66;
                uVar6 = runtime_convTstring();
                *(undefined8 **)((long)register0x00000020 + -0x88) = &DAT_0194e220;
                *(undefined8 *)((long)register0x00000020 + -0x80) = uVar6;
                *(undefined8 *)((long)register0x00000020 + -0x2c0) = 0x171ae8f;
                uVar6 = runtime_convTstring();
                *(undefined8 **)((long)register0x00000020 + -0x78) = &DAT_0194e220;
                *(undefined8 *)((long)register0x00000020 + -0x70) = uVar6;
                *(undefined8 *)((long)register0x00000020 + -0x2c0) = 0x171aebb;
                uVar6 = runtime_convTstring();
                *(undefined8 **)((long)register0x00000020 + -0x68) = &DAT_0194e220;
                *(undefined8 *)((long)register0x00000020 + -0x60) = uVar6;
                *(undefined8 *)((long)register0x00000020 + -0x2c0) = 0x171aef3;
                uVar6 = fmt_Sprintf();
                if (*(undefined1 **)((long)register0x00000020 + -0x148) == (undefined1 *)0x0) {
                  *(undefined1 **)((long)register0x00000020 + -0x148) =
                       (undefined1 *)((long)register0x00000020 + -0x148);
                }
                else if (*(undefined1 **)((long)register0x00000020 + -0x148) !=
                         (undefined1 *)((long)register0x00000020 + -0x148)) {
                  *(undefined8 *)((long)register0x00000020 + -0x2c0) = 0x171b058;
                  runtime_gopanic();
LAB_0171b058:
                  *(undefined8 *)((long)register0x00000020 + -0x2c0) = 0x171b06b;
                  runtime_gopanic();
                  goto LAB_0171b06b;
                }
                uVar11 = *(ulong *)((long)register0x00000020 + -0x130);
                uVar13 = *(long *)((long)register0x00000020 + -0x138) + 0x1f;
                uVar9 = *(undefined8 *)((long)register0x00000020 + -0x140);
                if (uVar11 < uVar13) {
                  *(undefined8 *)((long)register0x00000020 + -0x208) = 0x1f;
                  *(undefined8 *)((long)register0x00000020 + -0x118) = uVar6;
                  *(long *)((long)register0x00000020 + -0x1b0) =
                       *(long *)((long)register0x00000020 + -0x138);
                  *(undefined8 *)((long)register0x00000020 + -0x2c0) = 0x171af75;
                  uVar9 = runtime_growslice(0x1f);
                }
                *(undefined8 *)((long)register0x00000020 + -0x10) = uVar9;
                *(ulong *)((long)register0x00000020 + -0x1b0) = uVar13;
                *(ulong *)((long)register0x00000020 + -0x1b8) = uVar11;
                *(undefined8 *)((long)register0x00000020 + -0x2c0) = 0x171afbd;
                runtime_memmove();
                *(undefined8 *)((long)register0x00000020 + -0x138) =
                     *(undefined8 *)((long)register0x00000020 + -0x1b0);
                *(undefined8 *)((long)register0x00000020 + -0x130) =
                     *(undefined8 *)((long)register0x00000020 + -0x1b8);
                *(undefined8 *)((long)register0x00000020 + -0x140) =
                     *(undefined8 *)((long)register0x00000020 + -0x10);
              }
              puVar18 = *(undefined8 **)((long)register0x00000020 + -0x20);
              lVar7 = *(long *)((long)register0x00000020 + -0x1a8);
            }
          }
LAB_0171aa05:
          puVar18 = puVar18 + 2;
        }
      }
      else {
        lVar7 = 0;
        puVar18 = (undefined8 *)0x0;
        *(undefined8 *)((long)register0x00000020 + -0x2c0) = 0x171a72d;
        uVar6 = kiro2api_internal_logic_warp_getContentText();
        if (puVar12 != (undefined8 *)0x0) {
          *(undefined8 **)((long)register0x00000020 + -0x240) = puVar12;
          *(undefined8 *)((long)register0x00000020 + -0x170) = uVar6;
          *(undefined8 *)((long)register0x00000020 + -0x58) = in_XMM15_Qa;
          *(undefined8 *)((long)register0x00000020 + -0x50) = in_XMM15_Qb;
          *(undefined8 *)((long)register0x00000020 + -0x48) = in_XMM15_Qa;
          *(undefined8 *)((long)register0x00000020 + -0x40) = in_XMM15_Qb;
          *(undefined8 *)((long)register0x00000020 + -0x2c0) = 0x171a765;
          uVar6 = runtime_convT64();
          *(undefined8 **)((long)register0x00000020 + -0x58) = &DAT_0194e460;
          *(undefined8 *)((long)register0x00000020 + -0x50) = uVar6;
          *(undefined8 *)((long)register0x00000020 + -0x2c0) = 0x171a78e;
          uVar6 = runtime_convTstring();
          *(undefined8 **)((long)register0x00000020 + -0x48) = &DAT_0194e220;
          *(undefined8 *)((long)register0x00000020 + -0x40) = uVar6;
          *(undefined8 *)((long)register0x00000020 + -0x2c0) = 0x171a7c6;
          uVar6 = fmt_Sprintf();
          if (*(undefined1 **)((long)register0x00000020 + -0x148) == (undefined1 *)0x0) {
            *(undefined1 **)((long)register0x00000020 + -0x148) =
                 (undefined1 *)((long)register0x00000020 + -0x148);
          }
          else if (*(undefined1 **)((long)register0x00000020 + -0x148) !=
                   (undefined1 *)((long)register0x00000020 + -0x148)) {
            *(undefined8 *)((long)register0x00000020 + -0x2c0) = 0x171aa05;
            runtime_gopanic();
            goto LAB_0171aa05;
          }
          uVar11 = *(ulong *)((long)register0x00000020 + -0x130);
          uVar13 = *(long *)((long)register0x00000020 + -0x138) + 0x14;
          uVar9 = *(undefined8 *)((long)register0x00000020 + -0x140);
          if (uVar11 < uVar13) {
            *(undefined8 *)((long)register0x00000020 + -0x210) = 0x14;
            *(undefined8 *)((long)register0x00000020 + -0x120) = uVar6;
            *(long *)((long)register0x00000020 + -0x1a8) =
                 *(long *)((long)register0x00000020 + -0x138);
            *(undefined8 *)((long)register0x00000020 + -0x2c0) = 0x171a848;
            uVar9 = runtime_growslice(0x14);
          }
          *(ulong *)((long)register0x00000020 + -0x1a8) = uVar11;
          *(ulong *)((long)register0x00000020 + -0x1b0) = uVar13;
          *(undefined8 *)((long)register0x00000020 + -0x10) = uVar9;
          *(undefined8 *)((long)register0x00000020 + -0x2c0) = 0x171a890;
          runtime_memmove();
          *(undefined8 *)((long)register0x00000020 + -0x138) =
               *(undefined8 *)((long)register0x00000020 + -0x1b0);
          *(undefined8 *)((long)register0x00000020 + -0x130) =
               *(undefined8 *)((long)register0x00000020 + -0x1a8);
          *(undefined8 *)((long)register0x00000020 + -0x140) =
               *(undefined8 *)((long)register0x00000020 + -0x10);
        }
      }
      goto LAB_0171a9cc;
    }
  }
  else {
    if (*(undefined1 **)((long)register0x00000020 + -0x148) == (undefined1 *)0x0) {
      *(undefined1 **)((long)register0x00000020 + -0x148) =
           (undefined1 *)((long)register0x00000020 + -0x148);
LAB_0171a902:
      uVar11 = *(ulong *)((long)register0x00000020 + -0x130);
      uVar13 = *(long *)((long)register0x00000020 + -0x138) + 0x19;
      uVar6 = *(undefined8 *)((long)register0x00000020 + -0x140);
      if (uVar11 < uVar13) {
        *(long *)((long)register0x00000020 + -0x1a0) = *(long *)((long)register0x00000020 + -0x138);
        *(undefined8 *)((long)register0x00000020 + -0x2c0) = 0x171a945;
        uVar6 = runtime_growslice(0x19,&DAT_0194e2a0,lVar7,uVar11,uVar13,
                             (undefined1 *)((long)register0x00000020 + -0x148));
      }
      *(ulong *)((long)register0x00000020 + -0x1a0) = uVar11;
      *(ulong *)((long)register0x00000020 + -0x1a8) = uVar13;
      *(undefined8 *)((long)register0x00000020 + -0x10) = uVar6;
      *(undefined8 *)((long)register0x00000020 + -0x2c0) = 0x171a97c;
      runtime_memmove();
      *(undefined8 *)((long)register0x00000020 + -0x138) =
           *(undefined8 *)((long)register0x00000020 + -0x1a8);
      *(undefined8 *)((long)register0x00000020 + -0x130) =
           *(undefined8 *)((long)register0x00000020 + -0x1a0);
      *(undefined8 *)((long)register0x00000020 + -0x140) =
           *(undefined8 *)((long)register0x00000020 + -0x10);
      lVar7 = *(long *)((long)register0x00000020 + 0x20);
LAB_01719a65:
      uVar13 = *(ulong *)(lVar7 + 0x18);
      if (uVar13 - 1 < uVar13) {
        lVar14 = uVar13 * 0x30;
        lVar8 = *(long *)(lVar7 + 0x10);
        lVar7 = lVar14 + lVar8;
        uVar6 = *(undefined8 *)(lVar14 + lVar8 + -0x28);
        *(undefined8 *)((long)register0x00000020 + -0xd8) = *(undefined8 *)(lVar14 + lVar8 + -0x30);
        *(undefined8 *)((long)register0x00000020 + -0xd0) = uVar6;
        uVar6 = *(undefined8 *)(lVar14 + lVar8 + -0x18);
        *(undefined8 *)((long)register0x00000020 + -200) = *(undefined8 *)(lVar14 + lVar8 + -0x20);
        *(undefined8 *)((long)register0x00000020 + -0xc0) = uVar6;
        uVar2 = *(undefined4 *)(lVar7 + -0xc);
        uVar3 = *(undefined4 *)(lVar7 + -8);
        uVar4 = *(undefined4 *)(lVar7 + -4);
        *(undefined4 *)((long)register0x00000020 + -0xb8) = *(undefined4 *)(lVar7 + -0x10);
        *(undefined4 *)((long)register0x00000020 + -0xb4) = uVar2;
        *(undefined4 *)((long)register0x00000020 + -0xb0) = uVar3;
        *(undefined4 *)((long)register0x00000020 + -0xac) = uVar4;
        if (*(long *)((long)register0x00000020 + -0xd0) != 4) goto LAB_01719b32;
        if (**(int **)((long)register0x00000020 + -0xd8) != 0x72657375) goto LAB_01719b32;
        puVar12 = *(undefined8 **)((long)register0x00000020 + -0xc0);
        *(undefined8 *)((long)register0x00000020 + -0x2c0) = 0x1719aeb;
        uVar6 = kiro2api_internal_logic_warp_getContentText();
        if (*(undefined8 **)((long)register0x00000020 + -200) != &DAT_0192e960) {
          lVar7 = 0;
          puVar18 = (undefined8 *)0x0;
        }
        else {
          puVar18 = (undefined8 *)**(undefined8 **)((long)register0x00000020 + -0xc0);
          lVar7 = (*(undefined8 **)((long)register0x00000020 + -0xc0))[1];
        }
        *(undefined8 **)((long)register0x00000020 + -0x248) = puVar12;
        *(undefined8 *)((long)register0x00000020 + -0x178) = uVar6;
        if (*(undefined8 **)((long)register0x00000020 + -200) != &DAT_0192e960) {
          puVar15 = (undefined8 *)0x0;
          goto LAB_01719b6f;
        }
        puVar15 = (undefined8 *)0x0;
        do {
          if (lVar7 < 1) {
LAB_01719b6f:
            if (puVar12 != (undefined8 *)0x0) {
              if (*(undefined8 **)((long)register0x00000020 + -0x148) == (undefined8 *)0x0) {
                *(undefined1 **)((long)register0x00000020 + -0x148) =
                     (undefined1 *)((long)register0x00000020 + -0x148);
              }
              else {
                puVar18 = (undefined8 *)((long)register0x00000020 + -0x148);
                if (*(undefined8 **)((long)register0x00000020 + -0x148) != puVar18)
                goto LAB_0171a111;
              }
              uVar11 = *(ulong *)((long)register0x00000020 + -0x130);
              uVar13 = *(long *)((long)register0x00000020 + -0x138) + 0x12;
              uVar6 = *(undefined8 *)((long)register0x00000020 + -0x140);
              if (uVar11 < uVar13) {
                *(long *)((long)register0x00000020 + -0x1a0) =
                     *(long *)((long)register0x00000020 + -0x138);
                *(undefined8 *)((long)register0x00000020 + -0x2c0) = 0x1719bf1;
                uVar6 = runtime_growslice(0x12);
              }
              *(ulong *)((long)register0x00000020 + -0x1a0) = uVar11;
              *(ulong *)((long)register0x00000020 + -0x1a8) = uVar13;
              *(undefined8 *)((long)register0x00000020 + -0x10) = uVar6;
              puVar15 = (undefined8 *)0x12;
              *(undefined8 *)((long)register0x00000020 + -0x2c0) = 0x1719c2c;
              runtime_memmove();
              *(undefined8 *)((long)register0x00000020 + -0x138) =
                   *(undefined8 *)((long)register0x00000020 + -0x1a8);
              *(undefined8 *)((long)register0x00000020 + -0x130) =
                   *(undefined8 *)((long)register0x00000020 + -0x1a0);
              *(undefined8 *)((long)register0x00000020 + -0x140) =
                   *(undefined8 *)((long)register0x00000020 + -0x10);
              if (*(undefined8 **)((long)register0x00000020 + -0x148) == (undefined8 *)0x0) {
                *(undefined1 **)((long)register0x00000020 + -0x148) =
                     (undefined1 *)((long)register0x00000020 + -0x148);
              }
              else {
                puVar18 = (undefined8 *)((long)register0x00000020 + -0x148);
                if (*(undefined8 **)((long)register0x00000020 + -0x148) != puVar18)
                goto LAB_0171a0fe;
              }
              uVar11 = *(ulong *)((long)register0x00000020 + -0x130);
              puVar15 = *(undefined8 **)((long)register0x00000020 + -0x248);
              uVar13 = *(long *)((long)register0x00000020 + -0x138) + (long)puVar15;
              uVar6 = *(undefined8 *)((long)register0x00000020 + -0x140);
              if (uVar11 < uVar13) {
                *(long *)((long)register0x00000020 + -0x1a0) =
                     *(long *)((long)register0x00000020 + -0x138);
                *(undefined8 *)((long)register0x00000020 + -0x2c0) = 0x1719ccf;
                uVar6 = runtime_growslice();
                puVar15 = *(undefined8 **)((long)register0x00000020 + -0x248);
              }
              *(ulong *)((long)register0x00000020 + -0x1a0) = uVar11;
              *(ulong *)((long)register0x00000020 + -0x1a8) = uVar13;
              *(undefined8 *)((long)register0x00000020 + -0x10) = uVar6;
              *(undefined8 *)((long)register0x00000020 + -0x2c0) = 0x1719d07;
              runtime_memmove();
              *(undefined8 *)((long)register0x00000020 + -0x138) =
                   *(undefined8 *)((long)register0x00000020 + -0x1a8);
              *(undefined8 *)((long)register0x00000020 + -0x130) =
                   *(undefined8 *)((long)register0x00000020 + -0x1a0);
              *(undefined8 *)((long)register0x00000020 + -0x140) =
                   *(undefined8 *)((long)register0x00000020 + -0x10);
              if (*(undefined8 **)((long)register0x00000020 + -0x148) == (undefined8 *)0x0) {
                *(undefined1 **)((long)register0x00000020 + -0x148) =
                     (undefined1 *)((long)register0x00000020 + -0x148);
              }
              else {
                puVar18 = (undefined8 *)((long)register0x00000020 + -0x148);
                if (*(undefined8 **)((long)register0x00000020 + -0x148) != puVar18)
                goto LAB_0171a0eb;
              }
              uVar11 = *(ulong *)((long)register0x00000020 + -0x130);
              uVar13 = *(long *)((long)register0x00000020 + -0x138) + 0x13;
              uVar6 = *(undefined8 *)((long)register0x00000020 + -0x140);
              if (uVar11 < uVar13) {
                *(long *)((long)register0x00000020 + -0x1a0) =
                     *(long *)((long)register0x00000020 + -0x138);
                *(undefined8 *)((long)register0x00000020 + -0x2c0) = 0x1719da5;
                uVar6 = runtime_growslice(0x13);
              }
              *(ulong *)((long)register0x00000020 + -0x1a0) = uVar11;
              *(ulong *)((long)register0x00000020 + -0x1a8) = uVar13;
              *(undefined8 *)((long)register0x00000020 + -0x10) = uVar6;
              *(undefined8 *)((long)register0x00000020 + -0x2c0) = 0x1719ddc;
              runtime_memmove();
              *(undefined8 *)((long)register0x00000020 + -0x138) =
                   *(undefined8 *)((long)register0x00000020 + -0x1a8);
              *(undefined8 *)((long)register0x00000020 + -0x130) =
                   *(undefined8 *)((long)register0x00000020 + -0x1a0);
              *(undefined8 *)((long)register0x00000020 + -0x140) =
                   *(undefined8 *)((long)register0x00000020 + -0x10);
LAB_01719b32:
              puVar15 = (undefined8 *)-*(long *)((long)register0x00000020 + -0x140);
              puVar12 = *(undefined8 **)((long)register0x00000020 + -0x138);
              if (puVar12 <= puVar15) {
                *(undefined8 *)((long)register0x00000020 + -0x2c0) = 0x1719b52;
                kiro2api_internal_logic_warp_sanitizeUTF8();
                return;
              }
              if (*(long *)((long)register0x00000020 + -0x140) != 0) {
                *(undefined8 *)((long)register0x00000020 + -0x2c0) = 0x1719b6a;
                runtime_panicunsafestringlen();
              }
              *(undefined8 *)((long)register0x00000020 + -0x2c0) = 0x1719b6f;
              runtime_panicunsafestringnilptr();
              goto LAB_01719b6f;
            }
            if ((char)puVar15 == '\0') goto LAB_01719b32;
            if (*(undefined8 **)((long)register0x00000020 + -0x148) == (undefined8 *)0x0) {
              *(undefined1 **)((long)register0x00000020 + -0x148) =
                   (undefined1 *)((long)register0x00000020 + -0x148);
LAB_01719e52:
              uVar11 = *(ulong *)((long)register0x00000020 + -0x130);
              uVar13 = *(long *)((long)register0x00000020 + -0x138) + 0x12;
              uVar6 = *(undefined8 *)((long)register0x00000020 + -0x140);
              if (uVar11 < uVar13) {
                *(long *)((long)register0x00000020 + -0x1a0) =
                     *(long *)((long)register0x00000020 + -0x138);
                *(undefined8 *)((long)register0x00000020 + -0x2c0) = 0x1719e8f;
                uVar6 = runtime_growslice(0x12);
              }
              *(ulong *)((long)register0x00000020 + -0x1a0) = uVar11;
              *(ulong *)((long)register0x00000020 + -0x1a8) = uVar13;
              *(undefined8 *)((long)register0x00000020 + -0x10) = uVar6;
              puVar15 = (undefined8 *)0x12;
              *(undefined8 *)((long)register0x00000020 + -0x2c0) = 0x1719ec6;
              runtime_memmove();
              *(undefined8 *)((long)register0x00000020 + -0x138) =
                   *(undefined8 *)((long)register0x00000020 + -0x1a8);
              *(undefined8 *)((long)register0x00000020 + -0x130) =
                   *(undefined8 *)((long)register0x00000020 + -0x1a0);
              *(undefined8 *)((long)register0x00000020 + -0x140) =
                   *(undefined8 *)((long)register0x00000020 + -0x10);
              if (*(undefined8 **)((long)register0x00000020 + -0x148) == (undefined8 *)0x0) {
                *(undefined1 **)((long)register0x00000020 + -0x148) =
                     (undefined1 *)((long)register0x00000020 + -0x148);
LAB_01719f2f:
                uVar11 = *(ulong *)((long)register0x00000020 + -0x130);
                uVar13 = *(long *)((long)register0x00000020 + -0x138) + 0x5b;
                uVar6 = *(undefined8 *)((long)register0x00000020 + -0x140);
                if (uVar11 < uVar13) {
                  *(long *)((long)register0x00000020 + -0x1a0) =
                       *(long *)((long)register0x00000020 + -0x138);
                  *(undefined8 *)((long)register0x00000020 + -0x2c0) = 0x1719f6c;
                  uVar6 = runtime_growslice(0x5b);
                }
                *(ulong *)((long)register0x00000020 + -0x1a0) = uVar11;
                *(ulong *)((long)register0x00000020 + -0x1a8) = uVar13;
                *(undefined8 *)((long)register0x00000020 + -0x10) = uVar6;
                puVar15 = (undefined8 *)0x5b;
                *(undefined8 *)((long)register0x00000020 + -0x2c0) = 0x1719fa5;
                runtime_memmove();
                *(undefined8 *)((long)register0x00000020 + -0x138) =
                     *(undefined8 *)((long)register0x00000020 + -0x1a8);
                *(undefined8 *)((long)register0x00000020 + -0x130) =
                     *(undefined8 *)((long)register0x00000020 + -0x1a0);
                *(undefined8 *)((long)register0x00000020 + -0x140) =
                     *(undefined8 *)((long)register0x00000020 + -0x10);
                if (*(undefined8 **)((long)register0x00000020 + -0x148) == (undefined8 *)0x0) {
                  *(undefined1 **)((long)register0x00000020 + -0x148) =
                       (undefined1 *)((long)register0x00000020 + -0x148);
                }
                else {
                  puVar18 = (undefined8 *)((long)register0x00000020 + -0x148);
                  if (*(undefined8 **)((long)register0x00000020 + -0x148) != puVar18) {
                    *(undefined8 *)((long)register0x00000020 + -0x2c0) = 0x171a0c5;
                    runtime_gopanic();
                    goto LAB_0171a0c5;
                  }
                }
                uVar11 = *(ulong *)((long)register0x00000020 + -0x130);
                uVar13 = *(long *)((long)register0x00000020 + -0x138) + 0x12;
                uVar6 = *(undefined8 *)((long)register0x00000020 + -0x140);
                if (uVar11 < uVar13) {
                  *(long *)((long)register0x00000020 + -0x1a0) =
                       *(long *)((long)register0x00000020 + -0x138);
                  *(undefined8 *)((long)register0x00000020 + -0x2c0) = 0x171a045;
                  uVar6 = runtime_growslice(0x12);
                }
                *(ulong *)((long)register0x00000020 + -0x1a0) = uVar11;
                *(ulong *)((long)register0x00000020 + -0x1a8) = uVar13;
                *(undefined8 *)((long)register0x00000020 + -0x10) = uVar6;
                *(undefined8 *)((long)register0x00000020 + -0x2c0) = 0x171a07c;
                runtime_memmove();
                *(undefined8 *)((long)register0x00000020 + -0x138) =
                     *(undefined8 *)((long)register0x00000020 + -0x1a8);
                *(undefined8 *)((long)register0x00000020 + -0x130) =
                     *(undefined8 *)((long)register0x00000020 + -0x1a0);
                *(undefined8 *)((long)register0x00000020 + -0x140) =
                     *(undefined8 *)((long)register0x00000020 + -0x10);
                goto LAB_01719b32;
              }
              puVar18 = (undefined8 *)((long)register0x00000020 + -0x148);
              if (*(undefined8 **)((long)register0x00000020 + -0x148) == puVar18) goto LAB_01719f2f;
LAB_0171a0c5:
              *(undefined8 *)((long)register0x00000020 + -0x2c0) = 0x171a0d8;
              runtime_gopanic();
            }
            else {
              puVar18 = (undefined8 *)((long)register0x00000020 + -0x148);
              if (*(undefined8 **)((long)register0x00000020 + -0x148) == puVar18) goto LAB_01719e52;
            }
            *(undefined8 *)((long)register0x00000020 + -0x2c0) = 0x171a0eb;
            runtime_gopanic();
LAB_0171a0eb:
            *(undefined8 *)((long)register0x00000020 + -0x2c0) = 0x171a0fe;
            runtime_gopanic();
LAB_0171a0fe:
            *(undefined8 *)((long)register0x00000020 + -0x2c0) = 0x171a111;
            runtime_gopanic();
LAB_0171a111:
            puVar12 = &DAT_01f393c0;
            *(undefined8 *)((long)register0x00000020 + -0x2c0) = 0x171a125;
            runtime_gopanic();
            lVar7 = extraout_RDX;
          }
          else if ((undefined *)*puVar18 == &DAT_01a233a0) {
            uVar6 = puVar18[1];
            *(undefined8 **)((long)register0x00000020 + -0x18) = puVar18;
            *(long *)((long)register0x00000020 + -0x1a0) = lVar7;
            *(undefined8 *)((long)register0x00000020 + -0xa0) = uVar6;
            *(char *)((long)register0x00000020 + -0x289) = (char)puVar15;
            *(undefined8 *)((long)register0x00000020 + -0x2c0) = 0x171a186;
            puVar12 = (undefined8 *)runtime_mapaccess1_faststr(4);
            if ((undefined8 *)*puVar12 == &DAT_0194e220) {
              plVar19 = *(long **)puVar12[1];
              lVar7 = ((undefined8 *)puVar12[1])[1];
            }
            else {
              lVar7 = 0;
              plVar19 = (long *)0x0;
            }
            if (lVar7 == 0xb) {
              if (*plVar19 == 0x7365725f6c6f6f74) {
                if ((short)plVar19[1] == 0x6c75) {
                  if (*(char *)((long)plVar19 + 10) == 't') {
                    *(undefined8 *)((long)register0x00000020 + -0x2c0) = 0x171a207;
                    puVar12 = (undefined8 *)runtime_mapaccess1_faststr(0xb);
                    if ((undefined8 *)*puVar12 == &DAT_0194e220) {
                      uVar6 = *(undefined8 *)puVar12[1];
                      uVar9 = ((undefined8 *)puVar12[1])[1];
                    }
                    else {
                      uVar9 = 0;
                      uVar6 = 0;
                    }
                    *(undefined8 *)((long)register0x00000020 + -0x268) = uVar9;
                    *(undefined8 *)((long)register0x00000020 + -0x198) = uVar6;
                    *(undefined8 *)((long)register0x00000020 + -0x2c0) = 0x171a254;
                    lVar7 = runtime_mapaccess1_faststr(7,uVar9,&DAT_0194e220,&DAT_01c3dd44);
                    uVar6 = *(undefined8 *)(lVar7 + 8);
                    *(undefined8 *)((long)register0x00000020 + -0x2c0) = 0x171a265;
                    uVar9 = kiro2api_internal_logic_warp_getContentText();
                    *(undefined8 *)((long)register0x00000020 + -0xe8) = uVar9;
                    *(undefined8 *)((long)register0x00000020 + -0x1d8) = uVar6;
                    *(undefined8 *)((long)register0x00000020 + -0x58) = in_XMM15_Qa;
                    *(undefined8 *)((long)register0x00000020 + -0x50) = in_XMM15_Qb;
                    *(undefined8 *)((long)register0x00000020 + -0x48) = in_XMM15_Qa;
                    *(undefined8 *)((long)register0x00000020 + -0x40) = in_XMM15_Qb;
                    *(undefined8 *)((long)register0x00000020 + -0x2c0) = 0x171a299;
                    uVar6 = runtime_convTstring();
                    *(undefined8 **)((long)register0x00000020 + -0x58) = &DAT_0194e220;
                    *(undefined8 *)((long)register0x00000020 + -0x50) = uVar6;
                    *(undefined8 *)((long)register0x00000020 + -0x2c0) = 0x171a2c5;
                    uVar6 = runtime_convTstring();
                    *(undefined8 **)((long)register0x00000020 + -0x48) = &DAT_0194e220;
                    *(undefined8 *)((long)register0x00000020 + -0x40) = uVar6;
                    *(undefined8 *)((long)register0x00000020 + -0x2c0) = 0x171a2fd;
                    uVar6 = fmt_Sprintf();
                    if (*(undefined1 **)((long)register0x00000020 + -0x148) == (undefined1 *)0x0) {
                      *(undefined1 **)((long)register0x00000020 + -0x148) =
                           (undefined1 *)((long)register0x00000020 + -0x148);
                    }
                    else if (*(undefined1 **)((long)register0x00000020 + -0x148) !=
                             (undefined1 *)((long)register0x00000020 + -0x148)) goto LAB_0171a445;
                    uVar11 = *(ulong *)((long)register0x00000020 + -0x130);
                    uVar13 = *(long *)((long)register0x00000020 + -0x138) + 0x3d;
                    uVar9 = *(undefined8 *)((long)register0x00000020 + -0x140);
                    if (uVar11 < uVar13) {
                      *(undefined8 *)((long)register0x00000020 + -0x218) = 0x3d;
                      *(undefined8 *)((long)register0x00000020 + -0x128) = uVar6;
                      *(long *)((long)register0x00000020 + -0x1a8) =
                           *(long *)((long)register0x00000020 + -0x138);
                      *(undefined8 *)((long)register0x00000020 + -0x2c0) = 0x171a385;
                      uVar9 = runtime_growslice(0x3d);
                    }
                    *(ulong *)((long)register0x00000020 + -0x1a8) = uVar11;
                    *(ulong *)((long)register0x00000020 + -0x1b0) = uVar13;
                    *(undefined8 *)((long)register0x00000020 + -0x10) = uVar9;
                    *(undefined8 *)((long)register0x00000020 + -0x2c0) = 0x171a3cc;
                    runtime_memmove();
                    *(undefined8 *)((long)register0x00000020 + -0x138) =
                         *(undefined8 *)((long)register0x00000020 + -0x1b0);
                    *(undefined8 *)((long)register0x00000020 + -0x130) =
                         *(undefined8 *)((long)register0x00000020 + -0x1a8);
                    *(undefined8 *)((long)register0x00000020 + -0x140) =
                         *(undefined8 *)((long)register0x00000020 + -0x10);
                    uVar5 = 1;
                  }
                  else {
                    uVar5 = (uint)*(byte *)((long)register0x00000020 + -0x289);
                  }
                }
                else {
                  uVar5 = (uint)*(byte *)((long)register0x00000020 + -0x289);
                }
              }
              else {
                uVar5 = (uint)*(byte *)((long)register0x00000020 + -0x289);
              }
            }
            else {
              uVar5 = (uint)*(byte *)((long)register0x00000020 + -0x289);
            }
            lVar7 = *(long *)((long)register0x00000020 + -0x1a0);
            puVar12 = *(undefined8 **)((long)register0x00000020 + -0x248);
            puVar18 = *(undefined8 **)((long)register0x00000020 + -0x18);
            puVar15 = (undefined8 *)(ulong)uVar5;
          }
          puVar18 = puVar18 + 2;
          lVar7 = lVar7 + -1;
        } while( true );
      }
      goto LAB_0171a458;
    }
    if (*(undefined1 **)((long)register0x00000020 + -0x148) ==
        (undefined1 *)((long)register0x00000020 + -0x148)) goto LAB_0171a902;
    *(undefined8 *)((long)register0x00000020 + -0x2c0) = 0x171a9cc;
    runtime_gopanic();
LAB_0171a9cc:
    lVar8 = *(long *)((long)register0x00000020 + -0x1c0);
    uVar13 = *(ulong *)((long)register0x00000020 + -0x1a0);
    lVar7 = *(long *)((long)register0x00000020 + 0x20);
    puVar12 = *(undefined8 **)((long)register0x00000020 + -0x18);
  }
  puVar12 = puVar12 + 6;
  lVar8 = lVar8 + 1;
  goto LAB_0171a46c;
LAB_0171a445:
  *(undefined8 *)((long)register0x00000020 + -0x2c0) = 0x171a458;
  runtime_gopanic();
LAB_0171a458:
                    /* WARNING: Subroutine does not return */
  *(undefined8 *)((long)register0x00000020 + -0x2c0) = 0x171a465;
  runtime_panicIndex();
}




// === warp.MapToolToClaudeCode @ 0x1722fe0 ===

undefined8
warp_MapToolToClaudeCode
          (undefined8 param_1,long *param_2,undefined8 param_3,undefined8 param_4,undefined8 param_5
          ,undefined8 param_6)

{
  long *plVar1;
  undefined8 uVar2;
  char cVar3;
  undefined8 in_RAX;
  undefined8 *puVar4;
  long lVar5;
  undefined8 uVar6;
  undefined8 *puVar7;
  undefined8 unaff_RBX;
  long lVar8;
  undefined8 *in_R11;
  long unaff_R14;
  undefined1 auVar9 [16];
  undefined8 uStack0000000000000008;
  undefined8 uStack0000000000000010;
  undefined8 uStack0000000000000018;
  undefined8 uStack0000000000000020;
  long *plStack0000000000000028;
  undefined8 uStack0000000000000030;
  undefined8 uStack0000000000000038;
  undefined8 uStack_288;
  undefined8 uStack_280;
  undefined8 uStack_278;
  undefined8 uStack_270;
  undefined8 uStack_268;
  undefined8 uStack_260;
  long lStack_258;
  undefined8 uStack_250;
  undefined8 uStack_248;
  undefined8 uStack_240;
  undefined8 uStack_238;
  undefined8 uStack_230;
  undefined8 uStack_228;
  undefined8 uStack_220;
  undefined8 uStack_218;
  long lStack_210;
  long lStack_208;
  long lStack_200;
  long lStack_1f8;
  long lStack_1f0;
  long lStack_1e8;
  long lStack_1e0;
  long lStack_1d8;
  undefined8 uStack_198;
  undefined8 uStack_190;
  undefined8 uStack_188;
  undefined8 uStack_180;
  undefined8 uStack_178;
  undefined8 uStack_170;
  undefined8 uStack_168;
  undefined8 uStack_160;
  undefined8 uStack_158;
  undefined8 uStack_150;
  undefined8 uStack_148;
  undefined8 uStack_140;
  undefined8 uStack_138;
  undefined8 uStack_130;
  undefined8 uStack_128;
  undefined8 uStack_120;
  undefined8 uStack_118;
  undefined8 uStack_110;
  undefined8 uStack_108;
  undefined8 uStack_100;
  long *plStack_f8;
  undefined8 uStack_f0;
  undefined8 uStack_e8;
  undefined8 uStack_e0;
  undefined8 uStack_d8;
  undefined8 uStack_d0;
  undefined8 uStack_c8;
  undefined8 uStack_c0;
  undefined8 uStack_b8;
  undefined8 uStack_b0;
  undefined8 uStack_a8;
  long *plStack_a0;
  undefined8 *puStack_98;
  undefined8 uStack_90;
  undefined8 *puStack_88;
  undefined8 uStack_80;
  undefined8 *puStack_78;
  undefined8 *puStack_70;
  undefined8 *puStack_18;
  undefined8 uStack_10;
  
  uStack0000000000000008 = in_RAX;
  uStack0000000000000018 = param_4;
  uStack0000000000000010 = unaff_RBX;
  plStack0000000000000028 = param_2;
  uStack0000000000000020 = param_1;
  uStack0000000000000030 = param_5;
  uStack0000000000000038 = param_6;
  while (&uStack_288 <= *(undefined8 **)(unaff_R14 + 0x10)) {
    runtime_morestack_noctxt();
  }
  uStack_e8 = runtime_makemap_small();
  uVar6 = DAT_02e33508;
  uStack_108 = uStack0000000000000018;
  uStack_100 = uStack0000000000000020;
  uStack_118 = uStack0000000000000008;
  uStack_110 = uStack0000000000000010;
  plStack_f8 = plStack0000000000000028;
  uStack_f0 = uStack0000000000000030;
  puVar4 = (undefined8 *)runtime_mapaccess2_faststr(uStack0000000000000030);
  uVar2 = DAT_02e33508;
  if ((char)uVar6 == '\0') {
    puVar4 = (undefined8 *)runtime_mapaccess2_faststr(uStack0000000000000010);
    if ((char)uVar2 != '\0') {
      plStack_f8 = (long *)*puVar4;
      uStack_f0 = puVar4[1];
    }
  }
  else {
    plStack_f8 = (long *)*puVar4;
    uStack_f0 = puVar4[1];
  }
  uVar6 = uStack0000000000000038;
  switch(uStack0000000000000030) {
  case 4:
    if ((int)*plStack0000000000000028 == 0x70657267) {
      lVar5 = runtime_mapaccess1_faststr(7);
      lVar5 = *(long *)(lVar5 + 8);
      puVar4 = (undefined8 *)kiro2api_internal_logic_warp_getSliceFromInterface();
      if (lVar5 != 0) {
        uStack_218 = *puVar4;
        plStack_a0 = (long *)puVar4[1];
        puVar4 = (undefined8 *)runtime_mapassign_faststr(7);
        *puVar4 = uStack_218;
        if (DAT_02e5e450 != 0) {
          auVar9 = runtime_gcWriteBarrier2();
          puVar4 = auVar9._0_8_;
          *in_R11 = plStack_a0;
          in_R11[1] = auVar9._8_8_;
        }
        puVar4[1] = plStack_a0;
      }
      uVar6 = uStack0000000000000038;
      puVar4 = (undefined8 *)runtime_mapaccess2_faststr(4);
      if ((char)uVar6 == '\0') {
        return uStack_118;
      }
      uStack_278 = *puVar4;
      uStack_138 = puVar4[1];
      puVar4 = (undefined8 *)runtime_mapassign_faststr(4);
      *puVar4 = uStack_278;
      if (DAT_02e5e450 != 0) {
        auVar9 = runtime_gcWriteBarrier2();
        puVar4 = auVar9._0_8_;
        *in_R11 = uStack_138;
        in_R11[1] = auVar9._8_8_;
      }
      puVar4[1] = uStack_138;
      return uStack_118;
    }
    break;
  case 8:
    if (*plStack0000000000000028 == 0x746e656761627573) {
      FUN_00488ceb(&puStack_98);
      runtime_mapIterStart();
      while (puStack_78 != (undefined8 *)0x0) {
        uVar6 = *puStack_70;
        uStack_180 = puStack_70[1];
        puVar4 = (undefined8 *)runtime_mapassign_faststr(puStack_78[1],uVar6,uStack_180,*puStack_78);
        *puVar4 = uVar6;
        if (DAT_02e5e450 != 0) {
          uVar6 = puVar4[1];
          puVar4 = (undefined8 *)runtime_gcWriteBarrier2();
          *in_R11 = uStack_180;
          in_R11[1] = uVar6;
        }
        puVar4[1] = uStack_180;
        runtime_mapIterNext();
      }
      return uStack_118;
    }
    break;
  case 9:
    if ((*plStack0000000000000028 == 0x6f6c675f656c6966) &&
       ((char)plStack0000000000000028[1] == 'b')) {
LAB_017242dd:
      lVar5 = runtime_mapaccess1_faststr(8);
      lVar5 = *(long *)(lVar5 + 8);
      puVar4 = (undefined8 *)kiro2api_internal_logic_warp_getSliceFromInterface();
      if (lVar5 != 0) {
        uStack_218 = *puVar4;
        plStack_a0 = (long *)puVar4[1];
        puVar4 = (undefined8 *)runtime_mapassign_faststr(7);
        *puVar4 = uStack_218;
        if (DAT_02e5e450 != 0) {
          auVar9 = runtime_gcWriteBarrier2();
          puVar4 = auVar9._0_8_;
          *in_R11 = plStack_a0;
          in_R11[1] = auVar9._8_8_;
        }
        puVar4[1] = plStack_a0;
      }
      uVar6 = uStack0000000000000038;
      puVar4 = (undefined8 *)runtime_mapaccess2_faststr(10);
      if ((char)uVar6 == '\0') {
        return uStack_118;
      }
      uStack_250 = *puVar4;
      uStack_e0 = puVar4[1];
      puVar4 = (undefined8 *)runtime_mapassign_faststr(4);
      *puVar4 = uStack_250;
      if (DAT_02e5e450 != 0) {
        auVar9 = runtime_gcWriteBarrier2();
        puVar4 = auVar9._0_8_;
        *in_R11 = uStack_e0;
        in_R11[1] = auVar9._8_8_;
      }
      puVar4[1] = uStack_e0;
      return uStack_118;
    }
    break;
  case 10:
    if ((char)*plStack0000000000000028 < 'f') {
      if ((*plStack0000000000000028 == 0x6c69665f74696465) &&
         ((short)plStack0000000000000028[1] == 0x7365)) goto LAB_01724afd;
      if ((*plStack0000000000000028 == 0x616c705f74696465) &&
         ((short)plStack0000000000000028[1] == 0x736e)) {
        lVar5 = runtime_mapaccess1_faststr(5);
        lVar5 = *(long *)(lVar5 + 8);
        puVar4 = (undefined8 *)kiro2api_internal_logic_warp_getSliceFromInterface();
        if (lVar5 == 0) {
          return uStack_118;
        }
        if ((undefined *)*puVar4 == (undefined *)0x0) {
          lStack_210 = 0;
        }
        else if ((undefined *)*puVar4 == &DAT_01a233a0) {
          lStack_210 = puVar4[1];
        }
        else {
          lStack_210 = 0;
        }
        if (lStack_210 == 0) {
          return uStack_118;
        }
        puVar4 = (undefined8 *)runtime_mapaccess1_faststr(7);
        puVar7 = &DAT_0194e220;
        if ((undefined8 *)*puVar4 == &DAT_0194e220) {
          lVar5 = *(long *)(puVar4[1] + 8);
        }
        else {
          lVar5 = 0;
        }
        uVar6 = 0;
        if (lVar5 != 0) {
          auVar9 = runtime_convTstring();
          uStack_10 = auVar9._0_8_;
          puStack_18 = &DAT_0194e220;
          fmt_Sprintf(1,1,auVar9._8_8_,&puStack_18);
          uStack_a8 = runtime_convTstring();
          auVar9 = runtime_mapassign_faststr(9);
          *auVar9._0_8_ = &DAT_0194e220;
          if (DAT_02e5e450 != 0) {
            auVar9 = runtime_gcWriteBarrier2();
            *in_R11 = uStack_a8;
            in_R11[1] = auVar9._8_8_;
          }
          puVar7 = auVar9._8_8_;
          *(undefined8 *)(auVar9._0_8_ + 8) = uStack_a8;
          uVar6 = uStack_a8;
        }
        puVar4 = (undefined8 *)
                 runtime_mapaccess1_faststr(6,uVar6,puVar7,
                              "searchdeletecreatein_useactiveclosedoutputcallId[DONE]GEMINItierIdagent-</env>darwin24.0.015.6.1inputsimagesoffset0.70.0system/usagev2.9.7%s[%d]ServerConfigSERVERDOMAINMETHOD%s#%d,Logger<html><head><body><hr />/traceactiondomainmethod/[^/]+PATCH:TRACE:/indexUSAGE\n-/--%sOutput-07:00000000 Valuesysmontimersefenceselectscalar, not       unused objs\n next= jobs= goid sweep  B -> % util alloc free  span= prev= list=, i =  code= addr=], sp= m->p= p->m=SCHED  curg= ctxt: min=  max= bad ts(...)\n m=nil base hangupkilledallow"
                             );
        if ((undefined8 *)*puVar4 == &DAT_0194e220) {
          uStack_a8 = runtime_convTstring();
          puVar4 = (undefined8 *)runtime_mapassign_faststr(10);
          *puVar4 = &DAT_0194e220;
          if (DAT_02e5e450 != 0) {
            auVar9 = runtime_gcWriteBarrier2();
            puVar4 = auVar9._0_8_;
            *in_R11 = uStack_a8;
            in_R11[1] = auVar9._8_8_;
          }
          puVar4[1] = uStack_a8;
        }
        lVar5 = lStack_210;
        puVar4 = (undefined8 *)runtime_mapaccess2_faststr(7);
        if ((char)lVar5 == '\0') {
          return uStack_118;
        }
        uVar6 = *puVar4;
        uStack_150 = puVar4[1];
        puVar4 = (undefined8 *)runtime_mapassign_faststr(10);
        *puVar4 = uVar6;
        if (DAT_02e5e450 != 0) {
          auVar9 = runtime_gcWriteBarrier2();
          puVar4 = auVar9._0_8_;
          *in_R11 = uStack_150;
          in_R11[1] = auVar9._8_8_;
        }
        puVar4[1] = uStack_150;
        return uStack_118;
      }
    }
    else {
      if ((*plStack0000000000000028 == 0x6c69665f64616572) &&
         ((short)plStack0000000000000028[1] == 0x7365)) {
        lVar5 = runtime_mapaccess1_faststr(5);
        lVar5 = *(long *)(lVar5 + 8);
        puVar4 = (undefined8 *)kiro2api_internal_logic_warp_getSliceFromInterface();
        if (lVar5 == 0) {
          return uStack_118;
        }
        if ((undefined *)*puVar4 == (undefined *)0x0) {
          lStack_1d8 = 0;
        }
        else if ((undefined *)*puVar4 == &DAT_01a233a0) {
          lStack_1d8 = puVar4[1];
        }
        else {
          lStack_1d8 = 0;
        }
        if (lStack_1d8 == 0) {
          return uStack_118;
        }
        puVar4 = (undefined8 *)runtime_mapaccess1_faststr(4);
        if ((undefined8 *)*puVar4 == &DAT_0194e220) {
          uStack_a8 = runtime_convTstring();
          puVar4 = (undefined8 *)runtime_mapassign_faststr(9);
          *puVar4 = &DAT_0194e220;
          if (DAT_02e5e450 != 0) {
            auVar9 = runtime_gcWriteBarrier2();
            puVar4 = auVar9._0_8_;
            *in_R11 = uStack_a8;
            in_R11[1] = auVar9._8_8_;
          }
          puVar4[1] = uStack_a8;
        }
        else {
          puVar4 = (undefined8 *)runtime_mapaccess1_faststr(4);
          if ((undefined8 *)*puVar4 == &DAT_0194e220) {
            uStack_a8 = runtime_convTstring();
            puVar4 = (undefined8 *)runtime_mapassign_faststr(9);
            *puVar4 = &DAT_0194e220;
            if (DAT_02e5e450 != 0) {
              auVar9 = runtime_gcWriteBarrier2();
              puVar4 = auVar9._0_8_;
              *in_R11 = uStack_a8;
              in_R11[1] = auVar9._8_8_;
            }
            puVar4[1] = uStack_a8;
          }
        }
        lVar5 = runtime_mapaccess1_faststr(0xb);
        lVar5 = *(long *)(lVar5 + 8);
        puVar4 = (undefined8 *)kiro2api_internal_logic_warp_getSliceFromInterface();
        if (lVar5 == 0) {
          return uStack_118;
        }
        if ((undefined *)*puVar4 == (undefined *)0x0) {
          lStack_1e0 = 0;
        }
        else if ((undefined *)*puVar4 == &DAT_01a233a0) {
          lStack_1e0 = puVar4[1];
        }
        else {
          lStack_1e0 = 0;
        }
        if (lStack_1e0 == 0) {
          return uStack_118;
        }
        puVar4 = (undefined8 *)runtime_mapaccess1_faststr(5);
        puVar7 = &DAT_0194e3e0;
        if ((undefined8 *)*puVar4 == &DAT_0194e3e0) {
          lVar5 = *(long *)puVar4[1];
        }
        else {
          puVar4 = (undefined8 *)
                   runtime_mapaccess1_faststr(5,0,&DAT_0194e3e0,
                                "startMacOSnanos%s_%ddiffsplansskill.jsonPATCHx-appuser_ravenbytesQuery3.0.0ROUTE%s#%d</tr>debug%s:%d*fuzz*listPOST:HEAD:IndexInputshort%s,%s=j=02=G=15-0700%dh%sdefersweeptestRtestWexecWhchanexecRschedsudogtimergscanmheaptracepanicsleepamd64gcing MB,  got= ...\n max=scav  ptr ] = (trap:init  ms, fault and  tab= tag= top=[...], fp:deny"
                               );
          puVar7 = (undefined8 *)&DAT_0194e420;
          if ((undefined *)*puVar4 == &DAT_0194e420) {
            lVar5 = *(long *)puVar4[1];
          }
          else {
            puVar4 = (undefined8 *)runtime_mapaccess1_faststr(5);
            if ((undefined *)*puVar4 == &DAT_0194e5e0) {
              lVar5 = (long)*(double *)puVar4[1];
            }
            else {
              lVar5 = 0;
            }
            puVar7 = (undefined8 *)&DAT_0194e420;
          }
        }
        puVar4 = (undefined8 *)runtime_mapaccess1_faststr(3,lVar5,puVar7,&DAT_01c38eed);
        if ((undefined8 *)*puVar4 == &DAT_0194e3e0) {
          lStack_258 = *(long *)puVar4[1];
        }
        else {
          puVar4 = (undefined8 *)runtime_mapaccess1_faststr(3);
          if ((undefined *)*puVar4 == &DAT_0194e420) {
            lStack_258 = *(long *)puVar4[1];
          }
          else {
            puVar4 = (undefined8 *)runtime_mapaccess1_faststr(3);
            if ((undefined *)*puVar4 == &DAT_0194e5e0) {
              lStack_258 = (long)*(double *)puVar4[1];
            }
            else {
              lStack_258 = 0;
            }
          }
        }
        if (lVar5 < 1) {
          return uStack_118;
        }
        if (lStack_258 < 1) {
          return uStack_118;
        }
        if (lStack_258 < lVar5) {
          return uStack_118;
        }
        uStack_a8 = runtime_convT64();
        puVar4 = (undefined8 *)runtime_mapassign_faststr(6);
        *puVar4 = &DAT_0194e3e0;
        if (DAT_02e5e450 != 0) {
          uVar6 = puVar4[1];
          puVar4 = (undefined8 *)runtime_gcWriteBarrier2();
          *in_R11 = uStack_a8;
          in_R11[1] = uVar6;
        }
        puVar4[1] = uStack_a8;
        uStack_a8 = runtime_convT64();
        puVar4 = (undefined8 *)runtime_mapassign_faststr(5);
        *puVar4 = &DAT_0194e3e0;
        if (DAT_02e5e450 != 0) {
          auVar9 = runtime_gcWriteBarrier2();
          puVar4 = auVar9._0_8_;
          *in_R11 = uStack_a8;
          in_R11[1] = auVar9._8_8_;
        }
        puVar4[1] = uStack_a8;
        return uStack_118;
      }
      if ((*plStack0000000000000028 == 0x616c705f64616572) &&
         ((short)plStack0000000000000028[1] == 0x736e)) {
        lVar5 = runtime_mapaccess1_faststr(5);
        lVar5 = *(long *)(lVar5 + 8);
        puVar4 = (undefined8 *)kiro2api_internal_logic_warp_getSliceFromInterface();
        if (lVar5 == 0) {
          return uStack_118;
        }
        if ((undefined *)*puVar4 == (undefined *)0x0) {
          lVar5 = 0;
        }
        else if ((undefined *)*puVar4 == &DAT_01a233a0) {
          lVar5 = puVar4[1];
        }
        else {
          lVar5 = 0;
        }
        if (lVar5 == 0) {
          return uStack_118;
        }
        puVar4 = (undefined8 *)runtime_mapaccess1_faststr(7);
        if ((undefined8 *)*puVar4 == &DAT_0194e220) {
          puVar7 = *(undefined8 **)puVar4[1];
          lVar5 = ((long *)puVar4[1])[1];
        }
        else {
          lVar5 = 0;
          puVar7 = (undefined8 *)0x0;
        }
        if (lVar5 == 0) {
          return uStack_118;
        }
        auVar9 = runtime_convTstring();
        uStack_10 = auVar9._0_8_;
        puStack_18 = &DAT_0194e220;
        fmt_Sprintf(1,1,auVar9._8_8_,&puStack_18);
        uStack_a8 = runtime_convTstring();
        puVar4 = (undefined8 *)runtime_mapassign_faststr(9);
        *puVar4 = &DAT_0194e220;
        if (DAT_02e5e450 != 0) {
          auVar9 = runtime_gcWriteBarrier2();
          puVar4 = auVar9._0_8_;
          *puVar7 = uStack_a8;
          puVar7[1] = auVar9._8_8_;
        }
        puVar4[1] = uStack_a8;
        return uStack_118;
      }
      if ((*plStack0000000000000028 == 0x696b735f64616572) &&
         ((short)plStack0000000000000028[1] == 0x6c6c)) {
        puVar4 = (undefined8 *)runtime_mapaccess1_faststr(0x10);
        if ((undefined8 *)*puVar4 == &DAT_0194e220) {
          lVar5 = *(long *)(puVar4[1] + 8);
        }
        else {
          puVar4 = (undefined8 *)runtime_mapaccess1_faststr(10,0,&DAT_0194e220,&DAT_01c44481,0);
          if ((undefined8 *)*puVar4 == &DAT_0194e220) {
            lVar5 = *(long *)(puVar4[1] + 8);
            kiro2api_internal_logic_warp_extractSkillNameFromPath();
          }
          else {
            puVar4 = (undefined8 *)runtime_mapaccess1_faststr(10);
            if ((undefined8 *)*puVar4 == &DAT_0194e220) {
              lVar5 = *(long *)(puVar4[1] + 8);
            }
            else {
              lVar5 = 0;
            }
          }
        }
        puVar4 = &DAT_0194e220;
        uVar6 = 0;
        if (lVar5 != 0) {
          uStack_a8 = runtime_convTstring();
          auVar9 = runtime_mapassign_faststr(5);
          *auVar9._0_8_ = &DAT_0194e220;
          if (DAT_02e5e450 != 0) {
            auVar9 = runtime_gcWriteBarrier2();
            *in_R11 = uStack_a8;
            in_R11[1] = auVar9._8_8_;
          }
          puVar4 = auVar9._8_8_;
          *(undefined8 *)(auVar9._0_8_ + 8) = uStack_a8;
          uVar6 = uStack_a8;
        }
        uVar2 = uStack0000000000000038;
        puVar4 = (undefined8 *)runtime_mapaccess2_faststr(4,uVar6,puVar4,&DAT_01c398ae);
        if ((char)uVar2 == '\0') {
          return uStack_118;
        }
        uStack_220 = *puVar4;
        uStack_b0 = puVar4[1];
        puVar4 = (undefined8 *)runtime_mapassign_faststr(4);
        *puVar4 = uStack_220;
        if (DAT_02e5e450 != 0) {
          auVar9 = runtime_gcWriteBarrier2();
          puVar4 = auVar9._0_8_;
          *in_R11 = uStack_b0;
          in_R11[1] = auVar9._8_8_;
        }
        puVar4[1] = uStack_b0;
        return uStack_118;
      }
    }
    break;
  case 0xb:
    if ((*plStack0000000000000028 == 0x665f657461657263) &&
       (((short)plStack0000000000000028[1] == 0x6c69 &&
        (*(char *)((long)plStack0000000000000028 + 10) == 'e')))) {
      puVar4 = (undefined8 *)runtime_mapaccess2_faststr(9);
      if ((char)uVar6 != '\0') {
        uStack_270 = *puVar4;
        uStack_130 = puVar4[1];
        puVar4 = (undefined8 *)runtime_mapassign_faststr(9);
        *puVar4 = uStack_270;
        if (DAT_02e5e450 != 0) {
          auVar9 = runtime_gcWriteBarrier2();
          puVar4 = auVar9._0_8_;
          *in_R11 = uStack_130;
          in_R11[1] = auVar9._8_8_;
        }
        puVar4[1] = uStack_130;
      }
      uVar6 = uStack0000000000000038;
      puVar4 = (undefined8 *)runtime_mapaccess2_faststr(8);
      if ((char)uVar6 == '\0') {
        return uStack_118;
      }
      uStack_248 = *puVar4;
      uStack_c8 = puVar4[1];
      puVar4 = (undefined8 *)runtime_mapassign_faststr(7);
      *puVar4 = uStack_248;
      if (DAT_02e5e450 != 0) {
        auVar9 = runtime_gcWriteBarrier2();
        puVar4 = auVar9._0_8_;
        *in_R11 = uStack_c8;
        in_R11[1] = auVar9._8_8_;
      }
      puVar4[1] = uStack_c8;
      return uStack_118;
    }
    if (((*plStack0000000000000028 == 0x705f657461657263) &&
        ((short)plStack0000000000000028[1] == 0x616c)) &&
       (*(char *)((long)plStack0000000000000028 + 10) == 'n')) {
      puVar4 = (undefined8 *)runtime_mapaccess1_faststr(8);
      if ((undefined *)*puVar4 == (undefined *)0x0) {
        lStack_200 = 0;
      }
      else if ((undefined *)*puVar4 == &DAT_01a233a0) {
        lStack_200 = puVar4[1];
      }
      else {
        lStack_200 = 0;
      }
      if (lStack_200 == 0) {
        return uStack_118;
      }
      puVar4 = (undefined8 *)runtime_mapaccess1_faststr(5);
      if ((undefined8 *)*puVar4 == &DAT_0194e220) {
        uStack_168 = *(undefined8 *)puVar4[1];
      }
      else {
        uStack_168 = 0;
      }
      puVar4 = (undefined8 *)runtime_mapaccess1_faststr(0x10);
      if ((undefined8 *)*puVar4 == &DAT_0194e220) {
        uStack_d8 = *(undefined8 *)puVar4[1];
        uStack_238 = ((undefined8 *)puVar4[1])[1];
      }
      else {
        uStack_238 = 0;
        uStack_d8 = 0;
      }
      kiro2api_internal_logic_warp_sanitizeFileName();
      auVar9 = runtime_convTstring();
      uStack_10 = auVar9._0_8_;
      puStack_18 = &DAT_0194e220;
      fmt_Sprintf(1,1,auVar9._8_8_,&puStack_18);
      uStack_a8 = runtime_convTstring();
      puVar4 = (undefined8 *)runtime_mapassign_faststr(9);
      *puVar4 = &DAT_0194e220;
      if (DAT_02e5e450 != 0) {
        auVar9 = runtime_gcWriteBarrier2();
        puVar4 = auVar9._0_8_;
        *in_R11 = uStack_a8;
        in_R11[1] = auVar9._8_8_;
      }
      puVar4[1] = uStack_a8;
      uStack_a8 = runtime_convTstring();
      puVar4 = (undefined8 *)runtime_mapassign_faststr(7);
      *puVar4 = &DAT_0194e220;
      if (DAT_02e5e450 != 0) {
        auVar9 = runtime_gcWriteBarrier2();
        puVar4 = auVar9._0_8_;
        *in_R11 = uStack_a8;
        in_R11[1] = auVar9._8_8_;
      }
      puVar4[1] = uStack_a8;
      return uStack_118;
    }
    break;
  case 0xc:
    if ((*plStack0000000000000028 == 0x6f6c675f656c6966) &&
       ((int)plStack0000000000000028[1] == 0x32765f62)) goto LAB_017242dd;
    break;
  case 0xd:
    if (((*plStack0000000000000028 == 0x70636d5f6c6c6163) &&
        ((int)plStack0000000000000028[1] == 0x6f6f745f)) &&
       (*(char *)((long)plStack0000000000000028 + 0xc) == 'l')) {
      puVar4 = (undefined8 *)runtime_mapaccess1_faststr(9);
      if ((undefined8 *)*puVar4 == &DAT_0194e220) {
        uStack_158 = *(undefined8 *)puVar4[1];
        lVar5 = ((undefined8 *)puVar4[1])[1];
      }
      else {
        lVar5 = 0;
        uStack_158 = 0;
      }
      puVar4 = (undefined8 *)runtime_mapaccess1_faststr(4,lVar5,&DAT_0194e220,&DAT_01c39796);
      if ((undefined8 *)*puVar4 == &DAT_0194e220) {
        uVar6 = *(undefined8 *)puVar4[1];
        lVar8 = ((undefined8 *)puVar4[1])[1];
      }
      else {
        lVar8 = 0;
        uVar6 = 0;
      }
      if ((lVar5 != 0) && (lVar8 != 0)) {
        uStack_170 = uVar6;
        uStack_90 = runtime_convTstring();
        puStack_98 = &DAT_0194e220;
        auVar9 = runtime_convTstring();
        uStack_80 = auVar9._0_8_;
        puStack_88 = &DAT_0194e220;
        plStack_f8 = (long *)fmt_Sprintf(2,2,auVar9._8_8_,&puStack_98);
        uStack_f0 = 0xb;
      }
      puVar4 = (undefined8 *)runtime_mapaccess1_faststr(5);
      if ((undefined *)*puVar4 == &DAT_01a233a0) {
        FUN_00488ceb(&puStack_98,puVar4[1]);
        runtime_mapIterStart();
        while (puStack_78 != (undefined8 *)0x0) {
          uVar6 = *puStack_70;
          uStack_188 = puStack_70[1];
          puVar4 = (undefined8 *)runtime_mapassign_faststr(puStack_78[1],uVar6,uStack_188,*puStack_78);
          *puVar4 = uVar6;
          if (DAT_02e5e450 != 0) {
            uVar6 = puVar4[1];
            puVar4 = (undefined8 *)runtime_gcWriteBarrier2();
            *in_R11 = uStack_188;
            in_R11[1] = uVar6;
          }
          puVar4[1] = uStack_188;
          runtime_mapIterNext();
        }
        return uStack_118;
      }
      FUN_00488ceb(&puStack_98,0);
      runtime_mapIterStart();
      while (puStack_78 != (undefined8 *)0x0) {
        plVar1 = (long *)*puStack_78;
        if (((puStack_78[1] != 4) || ((int)*plVar1 != 0x656d616e)) &&
           ((puStack_78[1] != 9 || ((*plVar1 != 0x695f726576726573 || ((char)plVar1[1] != 'd'))))))
        {
          uVar6 = *puStack_70;
          uStack_190 = puStack_70[1];
          puVar4 = (undefined8 *)runtime_mapassign_faststr();
          *puVar4 = uVar6;
          if (DAT_02e5e450 != 0) {
            uVar6 = puVar4[1];
            puVar4 = (undefined8 *)runtime_gcWriteBarrier2();
            *in_R11 = uStack_190;
            in_R11[1] = uVar6;
          }
          puVar4[1] = uStack_190;
        }
        runtime_mapIterNext();
      }
      return uStack_118;
    }
    break;
  case 0xe:
    if (((*plStack0000000000000028 == 0x636f645f74696465) &&
        ((int)plStack0000000000000028[1] == 0x6e656d75)) &&
       (*(short *)((long)plStack0000000000000028 + 0xc) == 0x7374)) {
      lVar5 = runtime_mapaccess1_faststr(5);
      lVar5 = *(long *)(lVar5 + 8);
      puVar4 = (undefined8 *)kiro2api_internal_logic_warp_getSliceFromInterface();
      if (lVar5 == 0) {
        return uStack_118;
      }
      if ((undefined *)*puVar4 == (undefined *)0x0) {
        lStack_208 = 0;
      }
      else if ((undefined *)*puVar4 == &DAT_01a233a0) {
        lStack_208 = puVar4[1];
      }
      else {
        lStack_208 = 0;
      }
      if (lStack_208 == 0) {
        return uStack_118;
      }
      puVar4 = (undefined8 *)runtime_mapaccess1_faststr(0xb);
      puVar7 = &DAT_0194e220;
      if ((undefined8 *)*puVar4 == &DAT_0194e220) {
        lVar5 = *(long *)(puVar4[1] + 8);
      }
      else {
        lVar5 = 0;
      }
      uVar6 = 0;
      if (lVar5 != 0) {
        auVar9 = runtime_convTstring();
        uStack_10 = auVar9._0_8_;
        puStack_18 = &DAT_0194e220;
        fmt_Sprintf(1,1,auVar9._8_8_,&puStack_18);
        uStack_a8 = runtime_convTstring();
        auVar9 = runtime_mapassign_faststr(9);
        *auVar9._0_8_ = &DAT_0194e220;
        if (DAT_02e5e450 != 0) {
          auVar9 = runtime_gcWriteBarrier2();
          *in_R11 = uStack_a8;
          in_R11[1] = auVar9._8_8_;
        }
        puVar7 = auVar9._8_8_;
        *(undefined8 *)(auVar9._0_8_ + 8) = uStack_a8;
        uVar6 = uStack_a8;
      }
      puVar4 = (undefined8 *)
               runtime_mapaccess1_faststr(6,uVar6,puVar7,
                            "searchdeletecreatein_useactiveclosedoutputcallId[DONE]GEMINItierIdagent-</env>darwin24.0.015.6.1inputsimagesoffset0.70.0system/usagev2.9.7%s[%d]ServerConfigSERVERDOMAINMETHOD%s#%d,Logger<html><head><body><hr />/traceactiondomainmethod/[^/]+PATCH:TRACE:/indexUSAGE\n-/--%sOutput-07:00000000 Valuesysmontimersefenceselectscalar, not       unused objs\n next= jobs= goid sweep  B -> % util alloc free  span= prev= list=, i =  code= addr=], sp= m->p= p->m=SCHED  curg= ctxt: min=  max= bad ts(...)\n m=nil base hangupkilledallow"
                           );
      if ((undefined8 *)*puVar4 == &DAT_0194e220) {
        uStack_a8 = runtime_convTstring();
        puVar4 = (undefined8 *)runtime_mapassign_faststr(10);
        *puVar4 = &DAT_0194e220;
        if (DAT_02e5e450 != 0) {
          auVar9 = runtime_gcWriteBarrier2();
          puVar4 = auVar9._0_8_;
          *in_R11 = uStack_a8;
          in_R11[1] = auVar9._8_8_;
        }
        puVar4[1] = uStack_a8;
      }
      lVar5 = lStack_208;
      puVar4 = (undefined8 *)runtime_mapaccess2_faststr(7);
      if ((char)lVar5 == '\0') {
        return uStack_118;
      }
      uStack_288 = *puVar4;
      uStack_148 = puVar4[1];
      puVar4 = (undefined8 *)runtime_mapassign_faststr(10);
      *puVar4 = uStack_288;
      if (DAT_02e5e450 != 0) {
        auVar9 = runtime_gcWriteBarrier2();
        puVar4 = auVar9._0_8_;
        *in_R11 = uStack_148;
        in_R11[1] = auVar9._8_8_;
      }
      puVar4[1] = uStack_148;
      return uStack_118;
    }
    if (((*plStack0000000000000028 == 0x636f645f64616572) &&
        ((int)plStack0000000000000028[1] == 0x6e656d75)) &&
       (*(short *)((long)plStack0000000000000028 + 0xc) == 0x7374)) {
      lVar5 = runtime_mapaccess1_faststr(9);
      lVar5 = *(long *)(lVar5 + 8);
      puVar4 = (undefined8 *)kiro2api_internal_logic_warp_getSliceFromInterface();
      if (lVar5 == 0) {
        return uStack_118;
      }
      if ((undefined *)*puVar4 == (undefined *)0x0) {
        lVar5 = 0;
      }
      else if ((undefined *)*puVar4 == &DAT_01a233a0) {
        lVar5 = puVar4[1];
      }
      else {
        lVar5 = 0;
      }
      if (lVar5 == 0) {
        return uStack_118;
      }
      puVar4 = (undefined8 *)runtime_mapaccess1_faststr(0xb);
      if ((undefined8 *)*puVar4 == &DAT_0194e220) {
        puVar7 = *(undefined8 **)puVar4[1];
        lVar5 = ((long *)puVar4[1])[1];
      }
      else {
        lVar5 = 0;
        puVar7 = (undefined8 *)0x0;
      }
      if (lVar5 == 0) {
        return uStack_118;
      }
      auVar9 = runtime_convTstring();
      uStack_10 = auVar9._0_8_;
      puStack_18 = &DAT_0194e220;
      fmt_Sprintf(1,1,auVar9._8_8_,&puStack_18);
      uStack_a8 = runtime_convTstring();
      puVar4 = (undefined8 *)runtime_mapassign_faststr(9);
      *puVar4 = &DAT_0194e220;
      if (DAT_02e5e450 != 0) {
        auVar9 = runtime_gcWriteBarrier2();
        puVar4 = auVar9._0_8_;
        *puVar7 = uStack_a8;
        puVar7[1] = auVar9._8_8_;
      }
      puVar4[1] = uStack_a8;
      return uStack_118;
    }
    break;
  case 0x10:
    if ((*plStack0000000000000028 == 0x69665f796c707061) &&
       (plStack0000000000000028[1] == 0x73666669645f656c)) {
LAB_01724afd:
      lVar5 = runtime_mapaccess1_faststr(9);
      lVar5 = *(long *)(lVar5 + 8);
      puVar4 = (undefined8 *)kiro2api_internal_logic_warp_getSliceFromInterface();
      if (lVar5 != 0) {
        plStack_f8 = (long *)0x1c3a67a;
        uStack_f0 = 5;
        if ((undefined *)*puVar4 == (undefined *)0x0) {
          lVar5 = 0;
        }
        else if ((undefined *)*puVar4 == &DAT_01a233a0) {
          lVar5 = puVar4[1];
        }
        else {
          lVar5 = 0;
        }
        if (lVar5 == 0) {
          return uStack_118;
        }
        lStack_1e8 = lVar5;
        puVar4 = (undefined8 *)runtime_mapaccess2_faststr(9);
        if ((char)lVar5 != '\0') {
          uStack_260 = *puVar4;
          uStack_120 = puVar4[1];
          puVar4 = (undefined8 *)runtime_mapassign_faststr(9);
          *puVar4 = uStack_260;
          if (DAT_02e5e450 != 0) {
            auVar9 = runtime_gcWriteBarrier2();
            puVar4 = auVar9._0_8_;
            *in_R11 = uStack_120;
            in_R11[1] = auVar9._8_8_;
          }
          puVar4[1] = uStack_120;
        }
        lVar5 = lStack_1e8;
        puVar4 = (undefined8 *)runtime_mapaccess2_faststr(7);
        if ((char)lVar5 == '\0') {
          return uStack_118;
        }
        uStack_240 = *puVar4;
        uStack_c0 = puVar4[1];
        puVar4 = (undefined8 *)runtime_mapassign_faststr(7);
        *puVar4 = uStack_240;
        if (DAT_02e5e450 != 0) {
          auVar9 = runtime_gcWriteBarrier2();
          puVar4 = auVar9._0_8_;
          *in_R11 = uStack_c0;
          in_R11[1] = auVar9._8_8_;
        }
        puVar4[1] = uStack_c0;
        return uStack_118;
      }
      lVar5 = runtime_mapaccess1_faststr(5);
      lVar5 = *(long *)(lVar5 + 8);
      puVar4 = (undefined8 *)kiro2api_internal_logic_warp_getSliceFromInterface();
      if (lVar5 == 0) {
        return uStack_118;
      }
      if ((undefined *)*puVar4 == (undefined *)0x0) {
        lVar5 = 0;
      }
      else if ((undefined *)*puVar4 == &DAT_01a233a0) {
        lVar5 = puVar4[1];
      }
      else {
        lVar5 = 0;
      }
      if (lVar5 == 0) {
        return uStack_118;
      }
      lStack_1f0 = lVar5;
      puVar4 = (undefined8 *)runtime_mapaccess2_faststr(9);
      if ((char)lVar5 != '\0') {
        uStack_268 = *puVar4;
        uStack_128 = puVar4[1];
        puVar4 = (undefined8 *)runtime_mapassign_faststr(9);
        *puVar4 = uStack_268;
        if (DAT_02e5e450 != 0) {
          auVar9 = runtime_gcWriteBarrier2();
          puVar4 = auVar9._0_8_;
          *in_R11 = uStack_128;
          in_R11[1] = auVar9._8_8_;
        }
        puVar4[1] = uStack_128;
      }
      puVar4 = (undefined8 *)runtime_mapaccess1_faststr(6);
      if ((undefined8 *)*puVar4 == &DAT_0194e220) {
        kiro2api_internal_logic_warp_stripLineNumberPrefixes();
        uStack_a8 = runtime_convTstring();
        puVar4 = (undefined8 *)runtime_mapassign_faststr(10);
        *puVar4 = &DAT_0194e220;
        if (DAT_02e5e450 != 0) {
          auVar9 = runtime_gcWriteBarrier2();
          puVar4 = auVar9._0_8_;
          *in_R11 = uStack_a8;
          in_R11[1] = auVar9._8_8_;
        }
        puVar4[1] = uStack_a8;
      }
      lVar5 = lStack_1f0;
      puVar4 = (undefined8 *)runtime_mapaccess2_faststr(7);
      if ((char)lVar5 == '\0') {
        return uStack_118;
      }
      uStack_280 = *puVar4;
      uStack_140 = puVar4[1];
      puVar4 = (undefined8 *)runtime_mapassign_faststr(10);
      *puVar4 = uStack_280;
      if (DAT_02e5e450 != 0) {
        auVar9 = runtime_gcWriteBarrier2();
        puVar4 = auVar9._0_8_;
        *in_R11 = uStack_140;
        in_R11[1] = auVar9._8_8_;
      }
      puVar4[1] = uStack_140;
      return uStack_118;
    }
    if ((*plStack0000000000000028 == 0x645f657461657263) &&
       (plStack0000000000000028[1] == 0x73746e656d75636f)) {
      lVar5 = runtime_mapaccess1_faststr(0xd);
      lVar5 = *(long *)(lVar5 + 8);
      puVar4 = (undefined8 *)kiro2api_internal_logic_warp_getSliceFromInterface();
      if (lVar5 == 0) {
        return uStack_118;
      }
      if ((undefined *)*puVar4 == (undefined *)0x0) {
        lStack_1f8 = 0;
      }
      else if ((undefined *)*puVar4 == &DAT_01a233a0) {
        lStack_1f8 = puVar4[1];
      }
      else {
        lStack_1f8 = 0;
      }
      if (lStack_1f8 == 0) {
        return uStack_118;
      }
      puVar4 = (undefined8 *)runtime_mapaccess1_faststr(5);
      if ((undefined8 *)*puVar4 == &DAT_0194e220) {
        uStack_160 = *(undefined8 *)puVar4[1];
      }
      else {
        uStack_160 = 0;
      }
      puVar4 = (undefined8 *)runtime_mapaccess1_faststr(7);
      if ((undefined8 *)*puVar4 == &DAT_0194e220) {
        uStack_d0 = *(undefined8 *)puVar4[1];
        uStack_230 = ((undefined8 *)puVar4[1])[1];
      }
      else {
        uStack_230 = 0;
        uStack_d0 = 0;
      }
      kiro2api_internal_logic_warp_sanitizeFileName();
      auVar9 = runtime_convTstring();
      uStack_10 = auVar9._0_8_;
      puStack_18 = &DAT_0194e220;
      fmt_Sprintf(1,1,auVar9._8_8_,&puStack_18);
      uStack_a8 = runtime_convTstring();
      puVar4 = (undefined8 *)runtime_mapassign_faststr(9);
      *puVar4 = &DAT_0194e220;
      if (DAT_02e5e450 != 0) {
        auVar9 = runtime_gcWriteBarrier2();
        puVar4 = auVar9._0_8_;
        *in_R11 = uStack_a8;
        in_R11[1] = auVar9._8_8_;
      }
      puVar4[1] = uStack_a8;
      uStack_a8 = runtime_convTstring();
      puVar4 = (undefined8 *)runtime_mapassign_faststr(7);
      *puVar4 = &DAT_0194e220;
      if (DAT_02e5e450 != 0) {
        auVar9 = runtime_gcWriteBarrier2();
        puVar4 = auVar9._0_8_;
        *in_R11 = uStack_a8;
        in_R11[1] = auVar9._8_8_;
      }
      puVar4[1] = uStack_a8;
      return uStack_118;
    }
    break;
  case 0x11:
    plStack_a0 = plStack0000000000000028;
    cVar3 = runtime_memequal();
    if (cVar3 != '\0') {
      puVar4 = (undefined8 *)runtime_mapaccess1_faststr(9);
      if ((undefined8 *)*puVar4 == &DAT_0194e220) {
        lVar5 = *(long *)(puVar4[1] + 8);
      }
      else {
        lVar5 = 0;
      }
      if (lVar5 != 0) {
        auVar9 = runtime_convTstring();
        uStack_10 = auVar9._0_8_;
        puStack_18 = &DAT_0194e220;
        plStack_f8 = (long *)fmt_Sprintf(1,1,auVar9._8_8_,&puStack_18);
        uStack_f0 = 0x16;
      }
      uVar6 = uStack0000000000000038;
      puVar4 = (undefined8 *)runtime_mapaccess2_faststr(3);
      if ((char)uVar6 == '\0') {
        return uStack_118;
      }
      uVar6 = *puVar4;
      uStack_178 = puVar4[1];
      puVar4 = (undefined8 *)runtime_mapassign_faststr(3);
      *puVar4 = uVar6;
      if (DAT_02e5e450 != 0) {
        auVar9 = runtime_gcWriteBarrier2();
        puVar4 = auVar9._0_8_;
        *in_R11 = uStack_178;
        in_R11[1] = auVar9._8_8_;
      }
      puVar4[1] = uStack_178;
      return uStack_118;
    }
    cVar3 = runtime_memequal();
    uVar6 = uStack0000000000000038;
    if (cVar3 != '\0') {
      puVar4 = (undefined8 *)runtime_mapaccess2_faststr(7);
      if ((char)uVar6 == '\0') {
        return uStack_118;
      }
      uStack_228 = *puVar4;
      uStack_b8 = puVar4[1];
      puVar4 = (undefined8 *)runtime_mapassign_faststr(7);
      *puVar4 = uStack_228;
      if (DAT_02e5e450 != 0) {
        auVar9 = runtime_gcWriteBarrier2();
        puVar4 = auVar9._0_8_;
        *in_R11 = uStack_b8;
        in_R11[1] = auVar9._8_8_;
      }
      puVar4[1] = uStack_b8;
      return uStack_118;
    }
  }
  FUN_00488ceb(&puStack_98);
  runtime_mapIterStart();
  while (puStack_78 != (undefined8 *)0x0) {
    uVar6 = *puStack_70;
    uStack_198 = puStack_70[1];
    puVar4 = (undefined8 *)runtime_mapassign_faststr(puStack_78[1],uVar6,uStack_198,*puStack_78);
    *puVar4 = uVar6;
    if (DAT_02e5e450 != 0) {
      uVar6 = puVar4[1];
      puVar4 = (undefined8 *)runtime_gcWriteBarrier2();
      *in_R11 = uStack_198;
      in_R11[1] = uVar6;
    }
    puVar4[1] = uStack_198;
    runtime_mapIterNext();
  }
  return uStack_118;
}




// === warp.MapToolsToClaudeCode @ 0x1722160 ===

undefined8 *
warp_MapToolsToClaudeCode
          (undefined8 param_1,long *param_2,undefined8 param_3,undefined8 param_4,long param_5,
          undefined8 param_6)

{
  long lVar1;
  undefined8 *puVar2;
  undefined8 uVar3;
  ulong uVar4;
  long lVar5;
  undefined8 *puVar6;
  undefined8 unaff_RBX;
  ulong uVar7;
  long *plVar8;
  undefined8 uVar9;
  undefined8 uVar10;
  long lVar11;
  undefined8 *puVar12;
  long unaff_R14;
  undefined1 auVar13 [16];
  undefined8 uStack0000000000000010;
  undefined8 uStack0000000000000018;
  undefined8 uStack0000000000000020;
  long *plStack0000000000000028;
  long lStack0000000000000030;
  undefined8 uStack0000000000000038;
  long lStack_148;
  long lStack_140;
  long lStack_138;
  long lStack_130;
  ulong uStack_128;
  ulong uStack_120;
  ulong uStack_118;
  ulong uStack_110;
  long lStack_108;
  long lStack_100;
  long lStack_f8;
  undefined8 *puStack_f0;
  undefined8 *puStack_e8;
  undefined8 uStack_e0;
  undefined8 uStack_d8;
  long lStack_d0;
  undefined8 uStack_c8;
  undefined8 uStack_c0;
  undefined8 uStack_b8;
  undefined8 uStack_b0;
  long *plStack_a8;
  undefined4 uStack_a0;
  undefined4 uStack_9c;
  undefined4 uStack_98;
  undefined4 uStack_94;
  undefined8 *puStack_90;
  undefined8 uStack_88;
  undefined8 *puStack_80;
  undefined8 uStack_78;
  undefined8 *puStack_70;
  undefined8 *puStack_68;
  undefined8 uStack_60;
  undefined8 uStack_58;
  undefined8 *puStack_50;
  undefined8 *puStack_48;
  undefined *puStack_40;
  undefined8 uStack_38;
  undefined8 uStack_30;
  long lStack_28;
  long *plStack_20;
  undefined8 uStack_18;
  undefined8 uStack_10;
  
  uStack0000000000000018 = param_4;
  uStack0000000000000010 = unaff_RBX;
  plStack0000000000000028 = param_2;
  uStack0000000000000020 = param_1;
  lStack0000000000000030 = param_5;
  uStack0000000000000038 = param_6;
  while (&lStack_148 <= *(long **)(unaff_R14 + 0x10)) {
    runtime_morestack_noctxt();
  }
  if (((lStack0000000000000030 == 10) && (*plStack0000000000000028 == 0x6c69665f64616572)) &&
     ((short)plStack0000000000000028[1] == 0x7365)) {
    lVar1 = runtime_mapaccess1_faststr();
    lVar1 = *(long *)(lVar1 + 8);
    puVar2 = (undefined8 *)kiro2api_internal_logic_warp_getSliceFromInterface();
    if (1 < lVar1) {
      uVar4 = 0;
      uVar7 = 0;
      puVar6 = (undefined8 *)0x0;
      lStack_140 = lVar1;
      for (lVar5 = 0; lVar5 < lVar1; lVar5 = lVar5 + 1) {
        if ((undefined8 *)*puVar2 == (undefined8 *)0x0) {
          lVar11 = 0;
        }
        else if ((undefined8 *)*puVar2 == &DAT_01a233a0) {
          lVar11 = puVar2[1];
        }
        else {
          lVar11 = 0;
        }
        puVar12 = &DAT_01a233a0;
        if (lVar11 != 0) {
          lStack_148 = lVar5;
          lStack_f8 = lVar11;
          puStack_e8 = puVar6;
          puStack_50 = puVar2;
          uStack_88 = runtime_convTstring();
          puStack_90 = &DAT_0194e220;
          auVar13 = runtime_convT64();
          uStack_78 = auVar13._0_8_;
          puStack_80 = &DAT_0194e460;
          uStack_58 = fmt_Sprintf(2,2,auVar13._8_8_,&puStack_90);
          lStack_108 = 5;
          uStack_10 = runtime_makemap_small();
          uStack_30 = uStack_58;
          lStack_28 = lStack_108;
          puStack_40 = &DAT_01c3989a;
          uStack_38 = 4;
          plStack_20 = (long *)&DAT_01c3989a;
          uStack_18 = 4;
          puVar2 = (undefined8 *)runtime_mapaccess1_faststr(4);
          if ((undefined8 *)*puVar2 == &DAT_0194e220) {
            uStack_60 = runtime_convTstring();
            puVar2 = (undefined8 *)runtime_mapassign_faststr(9);
            *puVar2 = &DAT_0194e220;
            if (DAT_02e5e450 != 0) {
              auVar13 = runtime_gcWriteBarrier2();
              puVar2 = auVar13._0_8_;
              *puVar12 = uStack_60;
              puVar12[1] = auVar13._8_8_;
            }
            puVar2[1] = uStack_60;
          }
          else {
            puVar2 = (undefined8 *)runtime_mapaccess1_faststr(4);
            if ((undefined8 *)*puVar2 == &DAT_0194e220) {
              uStack_60 = runtime_convTstring();
              puVar2 = (undefined8 *)runtime_mapassign_faststr(9);
              *puVar2 = &DAT_0194e220;
              if (DAT_02e5e450 != 0) {
                auVar13 = runtime_gcWriteBarrier2();
                puVar2 = auVar13._0_8_;
                *puVar12 = uStack_60;
                puVar12[1] = auVar13._8_8_;
              }
              puVar2[1] = uStack_60;
            }
          }
          lVar1 = runtime_mapaccess1_faststr(0xb);
          lVar1 = *(long *)(lVar1 + 8);
          puVar2 = (undefined8 *)kiro2api_internal_logic_warp_getSliceFromInterface();
          if (lVar1 != 0) {
            if ((undefined8 *)*puVar2 == (undefined8 *)0x0) {
              lVar1 = 0;
            }
            else if ((undefined8 *)*puVar2 == &DAT_01a233a0) {
              lVar1 = puVar2[1];
            }
            else {
              lVar1 = 0;
            }
            if (lVar1 != 0) {
              lStack_100 = lVar1;
              puVar2 = (undefined8 *)runtime_mapaccess1_faststr(5);
              puVar6 = &DAT_0194e3e0;
              if ((undefined8 *)*puVar2 == &DAT_0194e3e0) {
                lVar1 = *(long *)puVar2[1];
              }
              else {
                puVar2 = (undefined8 *)
                         runtime_mapaccess1_faststr(5,0,&DAT_0194e3e0,
                                      "startMacOSnanos%s_%ddiffsplansskill.jsonPATCHx-appuser_ravenbytesQuery3.0.0ROUTE%s#%d</tr>debug%s:%d*fuzz*listPOST:HEAD:IndexInputshort%s,%s=j=02=G=15-0700%dh%sdefersweeptestRtestWexecWhchanexecRschedsudogtimergscanmheaptracepanicsleepamd64gcing MB,  got= ...\n max=scav  ptr ] = (trap:init  ms, fault and  tab= tag= top=[...], fp:deny"
                                     );
                puVar6 = (undefined8 *)&DAT_0194e420;
                if ((undefined *)*puVar2 == &DAT_0194e420) {
                  lVar1 = *(long *)puVar2[1];
                }
                else {
                  puVar2 = (undefined8 *)runtime_mapaccess1_faststr(5);
                  if ((undefined *)*puVar2 == &DAT_0194e5e0) {
                    lVar1 = (long)*(double *)puVar2[1];
                  }
                  else {
                    lVar1 = 0;
                  }
                  puVar6 = (undefined8 *)&DAT_0194e420;
                }
              }
              puVar2 = (undefined8 *)runtime_mapaccess1_faststr(3,lVar1,puVar6,&DAT_01c38eed);
              if ((undefined8 *)*puVar2 == &DAT_0194e3e0) {
                lVar5 = *(long *)puVar2[1];
              }
              else {
                puVar2 = (undefined8 *)runtime_mapaccess1_faststr(3);
                if ((undefined *)*puVar2 == &DAT_0194e420) {
                  lVar5 = *(long *)puVar2[1];
                }
                else {
                  puVar2 = (undefined8 *)runtime_mapaccess1_faststr(3);
                  if ((undefined *)*puVar2 == &DAT_0194e5e0) {
                    lVar5 = (long)*(double *)puVar2[1];
                  }
                  else {
                    lVar5 = 0;
                  }
                }
              }
              if (((0 < lVar1) && (0 < lVar5)) && (lVar1 <= lVar5)) {
                lStack_138 = lVar5;
                uStack_60 = runtime_convT64();
                puVar2 = (undefined8 *)runtime_mapassign_faststr(6);
                *puVar2 = &DAT_0194e3e0;
                if (DAT_02e5e450 != 0) {
                  uVar3 = puVar2[1];
                  puVar2 = (undefined8 *)runtime_gcWriteBarrier2();
                  *puVar12 = uStack_60;
                  puVar12[1] = uVar3;
                }
                puVar2[1] = uStack_60;
                uStack_60 = runtime_convT64();
                puVar2 = (undefined8 *)runtime_mapassign_faststr(5);
                *puVar2 = &DAT_0194e3e0;
                if (DAT_02e5e450 != 0) {
                  auVar13 = runtime_gcWriteBarrier2();
                  puVar2 = auVar13._0_8_;
                  *puVar12 = uStack_60;
                  puVar12[1] = auVar13._8_8_;
                }
                puVar2[1] = uStack_60;
              }
            }
          }
          uVar7 = uVar7 + 1;
          puVar6 = puStack_e8;
          if (uVar4 < uVar7) {
            puVar6 = (undefined8 *)runtime_growslice(1,&DAT_01b0e9a0);
          }
          lVar1 = uVar7 * 0x38;
          if (DAT_02e5e450 != 0) {
            uStack_128 = uVar4;
            uStack_120 = uVar7;
            lStack_108 = uVar7 * 0x38;
            puStack_70 = puVar6;
            runtime_wbMove();
            puVar6 = puStack_70;
            uVar4 = uStack_128;
            lVar1 = lStack_108;
            uVar7 = uStack_120;
          }
          *(undefined **)(lVar1 + -0x38 + (long)puVar6) = puStack_40;
          *(undefined8 *)((long)puVar6 + lVar1 + -0x30) = uStack_38;
          *(undefined8 *)((long)puVar6 + lVar1 + -0x28) = uStack_30;
          *(long *)((long)puVar6 + lVar1 + -0x20) = lStack_28;
          *(long **)((long)puVar6 + lVar1 + -0x18) = plStack_20;
          *(undefined4 *)((long)puVar6 + lVar1 + -0x10) = (undefined4)uStack_18;
          *(undefined4 *)((long)puVar6 + lVar1 + -0xc) = uStack_18._4_4_;
          *(undefined4 *)((long)puVar6 + lVar1 + -8) = (undefined4)uStack_10;
          *(undefined4 *)((long)puVar6 + lVar1 + -4) = uStack_10._4_4_;
          puVar2 = puStack_50;
          lVar5 = lStack_148;
          lVar1 = lStack_140;
        }
        puVar2 = puVar2 + 2;
      }
      if (uVar7 != 0) {
        return puVar6;
      }
    }
  }
  if ((((lStack0000000000000030 == 10) && (*plStack0000000000000028 == 0x6c69665f74696465)) &&
      ((short)plStack0000000000000028[1] == 0x7365)) ||
     (((lStack0000000000000030 == 0x10 && (*plStack0000000000000028 == 0x69665f796c707061)) &&
      (plStack0000000000000028[1] == 0x73666669645f656c)))) {
    lVar1 = runtime_mapaccess1_faststr();
    lVar1 = *(long *)(lVar1 + 8);
    puVar2 = (undefined8 *)kiro2api_internal_logic_warp_getSliceFromInterface();
    if (1 < lVar1) {
      uVar4 = 0;
      uVar7 = 0;
      puVar6 = (undefined8 *)0x0;
      lStack_130 = lVar1;
      for (lVar5 = 0; lVar5 < lVar1; lVar5 = lVar5 + 1) {
        if ((undefined8 *)*puVar2 == (undefined8 *)0x0) {
          lVar11 = 0;
        }
        else if ((undefined8 *)*puVar2 == &DAT_01a233a0) {
          lVar11 = puVar2[1];
        }
        else {
          lVar11 = 0;
        }
        puVar12 = &DAT_01a233a0;
        if (lVar11 != 0) {
          puStack_f0 = puVar6;
          lStack_d0 = lVar11;
          puStack_50 = puVar2;
          uStack_88 = runtime_convTstring();
          puStack_90 = &DAT_0194e220;
          auVar13 = runtime_convT64();
          uStack_78 = auVar13._0_8_;
          puStack_80 = &DAT_0194e460;
          uStack_58 = fmt_Sprintf(2,2,auVar13._8_8_,&puStack_90);
          lStack_108 = 5;
          uStack_10 = runtime_makemap_small();
          lVar1 = lStack_d0;
          uStack_30 = uStack_58;
          lStack_28 = lStack_108;
          puStack_40 = &DAT_01c3988e;
          uStack_38 = 4;
          plStack_20 = (long *)&DAT_01c3988e;
          uStack_18 = 4;
          puVar2 = (undefined8 *)runtime_mapaccess2_faststr(9);
          if ((char)lVar1 != '\0') {
            uVar3 = *puVar2;
            uStack_d8 = puVar2[1];
            puVar2 = (undefined8 *)runtime_mapassign_faststr(9);
            *puVar2 = uVar3;
            if (DAT_02e5e450 != 0) {
              auVar13 = runtime_gcWriteBarrier2();
              puVar2 = auVar13._0_8_;
              *puVar12 = uStack_d8;
              puVar12[1] = auVar13._8_8_;
            }
            puVar2[1] = uStack_d8;
          }
          puVar2 = (undefined8 *)runtime_mapaccess1_faststr(6);
          if ((undefined8 *)*puVar2 == &DAT_0194e220) {
            kiro2api_internal_logic_warp_stripLineNumberPrefixes();
            uStack_60 = runtime_convTstring();
            puVar2 = (undefined8 *)runtime_mapassign_faststr(10);
            *puVar2 = &DAT_0194e220;
            if (DAT_02e5e450 != 0) {
              auVar13 = runtime_gcWriteBarrier2();
              puVar2 = auVar13._0_8_;
              *puVar12 = uStack_60;
              puVar12[1] = auVar13._8_8_;
            }
            puVar2[1] = uStack_60;
          }
          lVar1 = lStack_d0;
          puVar2 = (undefined8 *)runtime_mapaccess2_faststr(7);
          if ((char)lVar1 != '\0') {
            uVar3 = *puVar2;
            uStack_e0 = puVar2[1];
            puVar2 = (undefined8 *)runtime_mapassign_faststr(10);
            *puVar2 = uVar3;
            if (DAT_02e5e450 != 0) {
              auVar13 = runtime_gcWriteBarrier2();
              puVar2 = auVar13._0_8_;
              *puVar12 = uStack_e0;
              puVar12[1] = auVar13._8_8_;
            }
            puVar2[1] = uStack_e0;
          }
          uVar7 = uVar7 + 1;
          puVar6 = puStack_f0;
          if (uVar4 < uVar7) {
            puVar6 = (undefined8 *)runtime_growslice(1,&DAT_01b0e9a0);
          }
          lVar1 = uVar7 * 0x38;
          if (DAT_02e5e450 != 0) {
            uStack_118 = uVar4;
            uStack_110 = uVar7;
            lStack_108 = uVar7 * 0x38;
            puStack_68 = puVar6;
            runtime_wbMove();
            puVar6 = puStack_68;
            uVar4 = uStack_118;
            lVar1 = lStack_108;
            uVar7 = uStack_110;
          }
          *(undefined **)(lVar1 + -0x38 + (long)puVar6) = puStack_40;
          *(undefined8 *)((long)puVar6 + lVar1 + -0x30) = uStack_38;
          *(undefined8 *)((long)puVar6 + lVar1 + -0x28) = uStack_30;
          *(long *)((long)puVar6 + lVar1 + -0x20) = lStack_28;
          *(long **)((long)puVar6 + lVar1 + -0x18) = plStack_20;
          *(undefined4 *)((long)puVar6 + lVar1 + -0x10) = (undefined4)uStack_18;
          *(undefined4 *)((long)puVar6 + lVar1 + -0xc) = uStack_18._4_4_;
          *(undefined4 *)((long)puVar6 + lVar1 + -8) = (undefined4)uStack_10;
          *(undefined4 *)((long)puVar6 + lVar1 + -4) = uStack_10._4_4_;
          puVar2 = puStack_50;
          lVar1 = lStack_130;
        }
        puVar2 = puVar2 + 2;
      }
      if (uVar7 != 0) {
        return puVar6;
      }
    }
  }
  uVar3 = uStack0000000000000018;
  plVar8 = plStack0000000000000028;
  uVar9 = uStack0000000000000020;
  lVar1 = lStack0000000000000030;
  uVar10 = uStack0000000000000038;
  uStack_c8 = warp_MapToolToClaudeCode();
  uStack_38 = uStack0000000000000010;
  uStack_c0 = uStack0000000000000010;
  uStack_18._0_4_ = (undefined4)lVar1;
  uStack_18._4_4_ = (undefined4)((ulong)lVar1 >> 0x20);
  uStack_10._0_4_ = (undefined4)uVar10;
  uStack_10._4_4_ = (undefined4)((ulong)uVar10 >> 0x20);
  uStack_a0 = (undefined4)uStack_18;
  uStack_9c = uStack_18._4_4_;
  uStack_98 = (undefined4)uStack_10;
  uStack_94 = uStack_10._4_4_;
  uStack_b8 = uVar3;
  uStack_b0 = uVar9;
  plStack_a8 = plVar8;
  puStack_40 = (undefined *)uStack_c8;
  uStack_30 = uVar3;
  lStack_28 = uVar9;
  plStack_20 = plVar8;
  uStack_18 = lVar1;
  uStack_10 = uVar10;
  puStack_48 = (undefined8 *)runtime_newobject();
  if (DAT_02e5e450 != 0) {
    runtime_wbMove();
  }
  *puStack_48 = uStack_c8;
  puStack_48[1] = uStack_c0;
  puStack_48[2] = uStack_b8;
  puStack_48[3] = uStack_b0;
  puStack_48[4] = plStack_a8;
  puStack_48[5] = CONCAT44(uStack_9c,uStack_a0);
  puStack_48[6] = CONCAT44(uStack_94,uStack_98);
  return puStack_48;
}




// === warp.RefreshToken @ 0x1712f40 ===

/* WARNING: Removing unreachable block (ram,0x0171364e) */
/* WARNING: Removing unreachable block (ram,0x01713a3a) */
/* WARNING: Removing unreachable block (ram,0x01713667) */
/* WARNING: Removing unreachable block (ram,0x017136aa) */
/* WARNING: Removing unreachable block (ram,0x017136b5) */
/* WARNING: Removing unreachable block (ram,0x017136b9) */
/* WARNING: Removing unreachable block (ram,0x017136f3) */
/* WARNING: Removing unreachable block (ram,0x01713706) */
/* WARNING: Removing unreachable block (ram,0x01713734) */
/* WARNING: Removing unreachable block (ram,0x01713782) */
/* WARNING: Removing unreachable block (ram,0x01713791) */
/* WARNING: Removing unreachable block (ram,0x017137c5) */
/* WARNING: Removing unreachable block (ram,0x0171382a) */
/* WARNING: Removing unreachable block (ram,0x01713846) */
/* WARNING: Removing unreachable block (ram,0x017138d1) */
/* WARNING: Removing unreachable block (ram,0x01713857) */
/* WARNING: Removing unreachable block (ram,0x01713864) */
/* WARNING: Removing unreachable block (ram,0x0171385d) */
/* WARNING: Removing unreachable block (ram,0x01713899) */
/* WARNING: Removing unreachable block (ram,0x017138cd) */
/* WARNING: Removing unreachable block (ram,0x0171389d) */
/* WARNING: Removing unreachable block (ram,0x017138b2) */
/* WARNING: Removing unreachable block (ram,0x017138c2) */
/* WARNING: Removing unreachable block (ram,0x017138d3) */
/* WARNING: Removing unreachable block (ram,0x017138e5) */
/* WARNING: Removing unreachable block (ram,0x017138f6) */
/* WARNING: Removing unreachable block (ram,0x0171390f) */
/* WARNING: Removing unreachable block (ram,0x01713913) */
/* WARNING: Removing unreachable block (ram,0x01713952) */
/* WARNING: Removing unreachable block (ram,0x01713969) */
/* WARNING: Removing unreachable block (ram,0x01713985) */
/* WARNING: Removing unreachable block (ram,0x0171399b) */
/* WARNING: Removing unreachable block (ram,0x01713995) */
/* WARNING: Removing unreachable block (ram,0x0171399e) */
/* WARNING: Removing unreachable block (ram,0x017139e6) */
/* WARNING: Removing unreachable block (ram,0x017139e8) */
/* WARNING: Removing unreachable block (ram,0x01713a0c) */
/* WARNING: Removing unreachable block (ram,0x01713a19) */

undefined8 warp_RefreshToken(long param_1,undefined8 param_2,undefined8 param_3,long param_4)

{
  ulong uVar1;
  long *plVar2;
  long lVar3;
  undefined8 uVar4;
  undefined8 uVar5;
  undefined8 *puVar6;
  long lVar7;
  ulong uVar8;
  long lVar9;
  undefined8 extraout_RDX;
  ulong uVar10;
  long extraout_RDX_00;
  undefined8 extraout_RDX_01;
  long unaff_RBX;
  long *in_R11;
  long unaff_R14;
  undefined1 auVar11 [16];
  undefined1 auVar12 [16];
  undefined1 auVar13 [16];
  long lStack0000000000000010;
  long lStack0000000000000018;
  long lStack0000000000000020;
  ulong auStack_270 [2];
  long lStack_260;
  long lStack_258;
  long lStack_250;
  undefined8 *puStack_248;
  undefined8 uStack_240;
  long lStack_230;
  long lStack_220;
  long lStack_218;
  undefined8 uStack_210;
  undefined1 auStack_208 [328];
  undefined8 uStack_c0;
  undefined8 *puStack_b8;
  undefined8 uStack_98;
  undefined8 uStack_90;
  undefined8 *puStack_88;
  undefined **ppuStack_80;
  undefined8 *puStack_78;
  undefined **ppuStack_70;
  long lStack_68;
  long lStack_60;
  long *plStack_58;
  
  lStack0000000000000018 = param_4;
  lStack0000000000000010 = unaff_RBX;
  lStack0000000000000020 = param_1;
  while (auStack_270 <= *(ulong **)(unaff_R14 + 0x10)) {
    runtime_morestack_noctxt();
  }
  (*(code *)*DAT_02e33480)();
  (*(code *)*DAT_02e33488)();
  if (*(long *)(lStack0000000000000020 + 0x10) == 0) {
    uVar4 = fmt_Errorf(0,0,extraout_RDX,0);
    return uVar4;
  }
  FUN_00488c9d(auStack_208);
  uStack_210 = 0x8080808080808080;
  puStack_b8 = &uStack_210;
  uStack_c0 = runtime_rand();
  plStack_58 = (long *)runtime_newobject();
  plStack_58[1] = 0xd;
  *plStack_58 = (long)&DAT_01c49a06;
  plVar2 = (long *)runtime_mapassign_faststr(10);
  plVar2[1] = 1;
  plVar2[2] = 1;
  if (DAT_02e5e450 != 0) {
    lVar7 = *plVar2;
    plVar2 = (long *)runtime_gcWriteBarrier2();
    *in_R11 = (long)plStack_58;
    in_R11[1] = lVar7;
  }
  *plVar2 = (long)plStack_58;
  lVar7 = *(long *)(lStack0000000000000020 + 0x10);
  lStack_250 = *(long *)(lStack0000000000000020 + 8);
  plVar2 = (long *)runtime_newobject();
  plVar2[1] = lVar7;
  if (DAT_02e5e450 != 0) {
    plVar2 = (long *)runtime_gcWriteBarrier1();
    *in_R11 = lStack_250;
  }
  *plVar2 = lStack_250;
  plStack_58 = plVar2;
  plVar2 = (long *)runtime_mapassign_faststr(0xd);
  plVar2[1] = 1;
  plVar2[2] = 1;
  if (DAT_02e5e450 != 0) {
    auVar11 = runtime_gcWriteBarrier2();
    plVar2 = auVar11._0_8_;
    *in_R11 = (long)plStack_58;
    in_R11[1] = auVar11._8_8_;
  }
  *plVar2 = (long)plStack_58;
  puStack_88 = &DAT_0194e220;
  ppuStack_80 = &PTR_DAT_01f3a310;
  puStack_78 = &DAT_0194e220;
  ppuStack_70 = &PTR_DAT_01f3a320;
  uStack_240 = fmt_Sprintf(2,2,&PTR_DAT_01f3a320,&puStack_88);
  lVar3 = lStack0000000000000018;
  lStack_230 = kiro2api_internal_logic_warp_GetWarpProxyURL();
  lStack_220 = github_com_imroc_req_v3_Client_Clone();
  lVar9 = lStack_230;
  lVar7 = 0;
  if (lVar3 != 0) {
    github_com_imroc_req_v3_Client_SetProxyURL();
    lVar7 = lVar9;
  }
  if (*(undefined8 **)(lStack_220 + 0x60) == (undefined8 *)0x0) {
    lStack_260 = 0;
  }
  else {
    puStack_248 = *(undefined8 **)(lStack_220 + 0x60);
    puVar6 = (undefined8 *)runtime_newobject();
    *puVar6 = *puStack_248;
    auVar11._8_8_ = puStack_248[1];
    auVar11._0_8_ = puVar6;
    puVar6 = puStack_248;
    if (DAT_02e5e450 != 0) {
      auVar11 = runtime_gcWriteBarrier1();
      *in_R11 = auVar11._8_8_;
    }
    lStack_260 = auVar11._0_8_;
    *(long *)(lStack_260 + 8) = auVar11._8_8_;
    auStack_270[0] = *(ulong *)(lStack_260 + 0x18);
    uVar8 = *(ulong *)(lStack_260 + 0x20);
    lVar7 = puVar6[3];
    uVar1 = auStack_270[0] + lVar7;
    lVar3 = *(long *)(lStack_260 + 0x10);
    lStack_60 = puVar6[2];
    if (uVar8 < uVar1) {
      lVar3 = runtime_growslice(lVar7,&DAT_019ea040);
    }
    lVar9 = uVar1 - auStack_270[0];
    uVar10 = (long)(auStack_270[0] - uVar8) >> 0x3f;
    in_R11 = (long *)(auStack_270[0] << 3 & uVar10);
    auStack_270[0] = uVar1;
    uVar4 = lStack_60;
    lStack_60 = lVar3;
    runtime_typedslicecopy(uVar4,lVar7,uVar10,lVar9);
    *(ulong *)(lStack_260 + 0x18) = auStack_270[0];
    *(ulong *)(lStack_260 + 0x20) = uVar8;
    lVar7 = lStack_260;
    if (DAT_02e5e450 != 0) {
      runtime_gcWriteBarrier2();
      *in_R11 = lStack_60;
      in_R11[1] = extraout_RDX_00;
    }
    *(long *)(lVar7 + 0x10) = lStack_60;
    lVar3 = *(long *)(lVar7 + 0x30);
    uVar8 = *(ulong *)(lVar7 + 0x38);
    auStack_270[0] = puStack_248[6];
    uVar1 = lVar3 + auStack_270[0];
    lVar9 = *(long *)(lVar7 + 0x28);
    lStack_68 = puStack_248[5];
    if (uVar8 < uVar1) {
      lVar9 = runtime_growslice(auStack_270[0],&DAT_019cbd00);
    }
    lVar7 = lVar9 + (lVar3 << 3 & (long)(lVar3 - uVar8) >> 0x3f);
    uVar10 = auStack_270[0];
    auStack_270[0] = uVar1;
    uVar4 = lStack_68;
    lStack_68 = lVar9;
    runtime_typedslicecopy(uVar4,uVar10,lVar7,uVar1 - lVar3);
    *(ulong *)(lStack_260 + 0x30) = auStack_270[0];
    *(ulong *)(lStack_260 + 0x38) = uVar8;
    if (DAT_02e5e450 != 0) {
      lVar3 = *(long *)(lStack_260 + 0x28);
      runtime_gcWriteBarrier2();
      *in_R11 = lStack_68;
      in_R11[1] = lVar3;
    }
    *(long *)(lStack_260 + 0x28) = lStack_68;
  }
  lVar3 = runtime_newobject();
  if (DAT_02e5e450 != 0) {
    lVar3 = runtime_gcWriteBarrier2();
    *in_R11 = lStack_220;
    in_R11[1] = lStack_260;
  }
  *(long *)(lVar3 + 0xf8) = lStack_220;
  *(long *)(lVar3 + 0x130) = lStack_260;
  lStack_258 = lVar3;
  if (lStack0000000000000010 != 0) {
    *(long *)(lVar3 + 0x160) = lStack0000000000000010;
    if (DAT_02e5e450 != 0) {
      lVar3 = runtime_gcWriteBarrier1();
      *in_R11 = lStack0000000000000018;
    }
    *(long *)(lVar3 + 0x168) = lStack0000000000000018;
  }
  uVar4 = net_url_Values_Encode();
  uVar5 = runtime_stringtoslicebyte();
  auVar12._8_8_ = lStack_258;
  auVar12._0_8_ = uVar5;
  *(undefined8 *)(lStack_258 + 0xc0) = uVar4;
  *(long *)(lStack_258 + 200) = lVar7;
  if (DAT_02e5e450 != 0) {
    lVar3 = *(long *)(lStack_258 + 0xb8);
    auVar12 = runtime_gcWriteBarrier2();
    *in_R11 = auVar12._0_8_;
    in_R11[1] = lVar3;
  }
  lStack_218 = auVar12._0_8_;
  *(long *)(auVar12._8_8_ + 0xb8) = lStack_218;
  puVar6 = (undefined8 *)runtime_newobject();
  auVar13._8_8_ = lStack_258;
  auVar13._0_8_ = puVar6;
  *puVar6 = &LAB_01713b40;
  puVar6[2] = uVar4;
  puVar6[3] = lVar7;
  if (DAT_02e5e450 != 0) {
    lVar7 = *(long *)(lStack_258 + 0xd0);
    auVar13 = runtime_gcWriteBarrier3();
    *in_R11 = lStack_218;
    in_R11[1] = auVar13._0_8_;
    in_R11[2] = lVar7;
  }
  *(long *)(auVar13._0_8_ + 8) = lStack_218;
  *(long *)(auVar13._8_8_ + 0xd0) = auVar13._0_8_;
  uVar4 = 4;
  github_com_imroc_req_v3_Request_Send(uStack_240,9);
  uStack_98 = DAT_01c3979a;
  uStack_90 = uVar4;
  uVar4 = fmt_Errorf(1,1,extraout_RDX_01,&uStack_98);
  return uVar4;
}




// === warp.RefundCredits @ 0x171f220 ===

/* WARNING: Removing unreachable block (ram,0x0171fe38) */
/* WARNING: Removing unreachable block (ram,0x0171fe70) */
/* WARNING: Removing unreachable block (ram,0x0171ff48) */
/* WARNING: Removing unreachable block (ram,0x0171fe8e) */
/* WARNING: Removing unreachable block (ram,0x0171ffc5) */
/* WARNING: Removing unreachable block (ram,0x0171ffce) */
/* WARNING: Removing unreachable block (ram,0x0171fde2) */

void warp_RefundCredits(long param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
                       long param_5,long param_6,undefined8 param_7,long param_8)

{
  ulong uVar1;
  undefined8 uVar2;
  undefined8 *puVar3;
  long *plVar4;
  undefined8 uVar5;
  long lVar6;
  long lVar7;
  undefined *puVar8;
  ulong uVar9;
  ulong uVar10;
  long extraout_RDX;
  undefined8 extraout_RDX_00;
  undefined8 extraout_RDX_01;
  undefined8 extraout_RDX_02;
  undefined8 extraout_RDX_03;
  undefined8 extraout_RDX_04;
  undefined8 extraout_RDX_05;
  undefined8 extraout_RDX_06;
  undefined8 extraout_RDX_07;
  undefined8 extraout_RDX_08;
  long lVar11;
  long in_R10;
  long *in_R11;
  long unaff_R14;
  undefined1 auVar12 [16];
  undefined1 auVar13 [16];
  undefined1 auVar14 [16];
  undefined8 uStack0000000000000028;
  undefined8 uStack0000000000000038;
  long lStack0000000000000040;
  long lStack0000000000000048;
  long lStack0000000000000050;
  undefined8 *apuStack_e8 [4];
  undefined8 uStack_c8;
  undefined8 *puStack_c0;
  undefined *puStack_b8;
  undefined8 uStack_b0;
  undefined8 uStack_a8;
  undefined *puStack_a0;
  undefined8 uStack_98;
  long lStack_90;
  long lStack_88;
  long lStack_80;
  long lStack_78;
  undefined8 uStack_70;
  long lStack_68;
  undefined8 *puStack_60;
  undefined8 uStack_58;
  undefined8 *puStack_50;
  undefined8 uStack_48;
  undefined8 uStack_40;
  long lStack_38;
  long lStack_30;
  long lStack_28;
  long lStack_20;
  long lStack_18;
  undefined8 uStack_10;
  
  uStack0000000000000028 = param_4;
  uStack0000000000000038 = param_2;
  lStack0000000000000040 = param_5;
  lStack0000000000000048 = param_6;
  lStack0000000000000050 = in_R10;
  while (apuStack_e8 <= *(undefined8 ***)(unaff_R14 + 0x10)) {
    runtime_morestack_noctxt();
  }
  if ((lStack0000000000000040 == 0) || (lStack0000000000000050 == 0)) {
    uStack_c8 = github_com_gogf_gf_v2_frame_gins_Log();
    uStack_58 = runtime_convTstring();
    puStack_60 = &DAT_0194e220;
    uStack_48 = runtime_convTstring();
    puStack_50 = &DAT_0194e220;
    github_com_gogf_gf_v2_os_glog_Logger_Debugf(&DAT_01c970d7,0x41,&DAT_0194e220,uStack0000000000000028,&puStack_60,2);
    return;
  }
  uStack_10 = runtime_makemap_small();
  lStack_18 = runtime_makemap_small();
  lStack_20 = runtime_convTstring();
  puVar3 = (undefined8 *)runtime_mapassign_faststr(0xe);
  *puVar3 = &DAT_0194e220;
  if (DAT_02e5e450 != 0) {
    auVar12 = runtime_gcWriteBarrier2();
    puVar3 = auVar12._0_8_;
    *in_R11 = lStack_20;
    in_R11[1] = auVar12._8_8_;
  }
  puVar3[1] = lStack_20;
  plVar4 = (long *)runtime_newobject();
  plVar4[1] = lStack0000000000000050;
  if (DAT_02e5e450 != 0) {
    plVar4 = (long *)runtime_gcWriteBarrier1();
    *in_R11 = lStack0000000000000048;
  }
  *plVar4 = lStack0000000000000048;
  lStack_20 = runtime_convTslice();
  puVar3 = (undefined8 *)runtime_mapassign_faststr(10);
  auVar12._8_8_ = &DAT_0192e8e0;
  auVar12._0_8_ = puVar3;
  *puVar3 = &DAT_0192e8e0;
  if (DAT_02e5e450 != 0) {
    auVar12 = runtime_gcWriteBarrier2();
    *in_R11 = lStack_20;
    in_R11[1] = auVar12._8_8_;
  }
  *(long *)(auVar12._0_8_ + 8) = lStack_20;
  lVar7 = lStack_20;
  puVar3 = (undefined8 *)runtime_mapassign_faststr(5,lStack_20,auVar12._8_8_,&DAT_01c3a5e4);
  *puVar3 = &DAT_01a233a0;
  if (DAT_02e5e450 != 0) {
    lVar11 = puVar3[1];
    puVar3 = (undefined8 *)runtime_gcWriteBarrier2();
    *in_R11 = lStack_18;
    in_R11[1] = lVar11;
  }
  puVar3[1] = lStack_18;
  lStack_18 = runtime_makemap_small();
  lStack_28 = runtime_makemap_small();
  puVar3 = (undefined8 *)runtime_mapassign_faststr(7);
  *puVar3 = &DAT_0194e220;
  if (DAT_02e5e450 != 0) {
    auVar12 = runtime_gcWriteBarrier1();
    puVar3 = auVar12._0_8_;
    *in_R11 = auVar12._8_8_;
  }
  puVar3[1] = &PTR_DAT_01f3a350;
  puVar3 = (undefined8 *)runtime_mapassign_faststr(0xd);
  *puVar3 = &DAT_01a233a0;
  if (DAT_02e5e450 != 0) {
    lVar11 = puVar3[1];
    puVar3 = (undefined8 *)runtime_gcWriteBarrier2();
    *in_R11 = lStack_28;
    in_R11[1] = lVar11;
  }
  puVar3[1] = lStack_28;
  lStack_28 = runtime_makemap_small();
  puVar3 = (undefined8 *)runtime_mapassign_faststr(0x12);
  *puVar3 = 0;
  if (DAT_02e5e450 != 0) {
    auVar12 = runtime_gcWriteBarrier1();
    puVar3 = auVar12._0_8_;
    *in_R11 = auVar12._8_8_;
  }
  puVar3[1] = 0;
  puVar3 = (undefined8 *)runtime_mapassign_faststr(8);
  *puVar3 = &DAT_0194e220;
  if (DAT_02e5e450 != 0) {
    lVar7 = puVar3[1];
    puVar3 = (undefined8 *)runtime_gcWriteBarrier1();
    *in_R11 = lVar7;
  }
  puVar3[1] = &DAT_01f3a360;
  puVar3 = (undefined8 *)runtime_mapassign_faststr(4);
  *puVar3 = &DAT_0194e220;
  if (DAT_02e5e450 != 0) {
    lVar7 = puVar3[1];
    puVar3 = (undefined8 *)runtime_gcWriteBarrier1();
    *in_R11 = lVar7;
  }
  puVar3[1] = &DAT_01f3a360;
  puVar3 = (undefined8 *)runtime_mapassign_faststr(7);
  *puVar3 = &DAT_0194e220;
  if (DAT_02e5e450 != 0) {
    lVar7 = puVar3[1];
    puVar3 = (undefined8 *)runtime_gcWriteBarrier1();
    *in_R11 = lVar7;
  }
  puVar3[1] = &DAT_01f3a3c0;
  puVar3 = (undefined8 *)runtime_mapassign_faststr(9);
  *puVar3 = &DAT_01a233a0;
  if (DAT_02e5e450 != 0) {
    lVar7 = puVar3[1];
    puVar3 = (undefined8 *)runtime_gcWriteBarrier2();
    *in_R11 = lStack_28;
    in_R11[1] = lVar7;
  }
  puVar3[1] = lStack_28;
  lVar11 = 0xe;
  puVar3 = (undefined8 *)runtime_mapassign_faststr();
  *puVar3 = &DAT_01a233a0;
  if (DAT_02e5e450 != 0) {
    lVar6 = puVar3[1];
    puVar3 = (undefined8 *)runtime_gcWriteBarrier2();
    *in_R11 = lStack_18;
    in_R11[1] = lVar6;
  }
  puVar3[1] = lStack_18;
  puStack_b8 = &DAT_01cabada;
  uStack_b0 = 0x221;
  uStack_a8 = uStack_10;
  puVar8 = &DAT_01c86809;
  puStack_a0 = &DAT_01c86809;
  uStack_98 = 0x30;
  uVar5 = runtime_convT();
  lStack_88 = encoding_json_Marshal();
  if (lVar11 == 0) {
    lStack_78 = kiro2api_internal_logic_warp_NewGraphQLClient();
    *(undefined8 *)(*(long *)(lStack_78 + 200) + 0x28) = 15000000000;
    if (param_8 != 0) {
      github_com_imroc_req_v3_Client_SetProxyURL();
    }
    if (*(undefined8 **)(lStack_78 + 0x60) == (undefined8 *)0x0) {
      apuStack_e8[0] = (undefined8 *)0x0;
    }
    else {
      puStack_c0 = *(undefined8 **)(lStack_78 + 0x60);
      puVar3 = (undefined8 *)runtime_newobject();
      *puVar3 = *puStack_c0;
      auVar13._8_8_ = puStack_c0[1];
      auVar13._0_8_ = puVar3;
      puVar3 = puStack_c0;
      if (DAT_02e5e450 != 0) {
        auVar13 = runtime_gcWriteBarrier1();
        *in_R11 = auVar13._8_8_;
      }
      apuStack_e8[0] = auVar13._0_8_;
      apuStack_e8[0][1] = auVar13._8_8_;
      lVar7 = apuStack_e8[0][3];
      uVar9 = apuStack_e8[0][4];
      lVar11 = puVar3[3];
      uVar1 = lVar7 + lVar11;
      lVar6 = apuStack_e8[0][2];
      lStack_30 = puVar3[2];
      if (uVar9 < uVar1) {
        lVar6 = runtime_growslice(lVar11,&DAT_019ea040);
      }
      uVar10 = (long)(lVar7 - uVar9) >> 0x3f;
      in_R11 = (long *)(lVar7 << 3 & uVar10);
      uVar2 = lStack_30;
      lStack_30 = lVar6;
      runtime_typedslicecopy(uVar2,lVar11,uVar10,uVar1 - lVar7);
      apuStack_e8[0][3] = uVar1;
      apuStack_e8[0][4] = uVar9;
      puVar3 = apuStack_e8[0];
      if (DAT_02e5e450 != 0) {
        runtime_gcWriteBarrier2();
        *in_R11 = lStack_30;
        in_R11[1] = extraout_RDX;
      }
      puVar3[2] = lStack_30;
      lVar7 = puVar3[6];
      uVar9 = puVar3[7];
      lVar11 = puStack_c0[6];
      uVar1 = lVar7 + lVar11;
      lVar6 = puVar3[5];
      lStack_38 = puStack_c0[5];
      if (uVar9 < uVar1) {
        lVar6 = runtime_growslice(lVar11,&DAT_019cbd00);
      }
      uVar2 = lStack_38;
      lStack_38 = lVar6;
      runtime_typedslicecopy(uVar2,lVar11,lVar6 + (lVar7 << 3 & (long)(lVar7 - uVar9) >> 0x3f),uVar1 - lVar7);
      apuStack_e8[0][6] = uVar1;
      apuStack_e8[0][7] = uVar9;
      if (DAT_02e5e450 != 0) {
        lVar7 = apuStack_e8[0][5];
        runtime_gcWriteBarrier2();
        *in_R11 = lStack_38;
        in_R11[1] = lVar7;
      }
      apuStack_e8[0][5] = lStack_38;
    }
    lVar7 = runtime_newobject();
    if (DAT_02e5e450 != 0) {
      lVar7 = runtime_gcWriteBarrier2();
      *in_R11 = lStack_78;
      in_R11[1] = (long)apuStack_e8[0];
    }
    *(long *)(lVar7 + 0xf8) = lStack_78;
    *(undefined8 **)(lVar7 + 0x130) = apuStack_e8[0];
    github_com_imroc_req_v3_Request_SetHeader(&DAT_01c40057,8,lStack_78,0x10);
    github_com_imroc_req_v3_Request_SetHeader(&DAT_01c66e9c,0x1d,extraout_RDX_00,0x15);
    github_com_imroc_req_v3_Request_SetHeader("macOStasksstartMacOSnanos%s_%ddiffsplansskill.jsonPATCHx-appuser_ravenbytesQuery3.0.0ROUTE%s#%d</tr>debug%s:%d*fuzz*listPOST:HEAD:IndexInputshort%s,%s=j=02=G=15-0700%dh%sdefersweeptestRtestWexecWhchanexecRschedsudogtimergscanmheaptracepanicsleepamd64gcing MB,  got= ...\n max=scav  ptr ] = (trap:init  ms, fault and  tab= tag= top=[...], fp:deny"
                 ,5,extraout_RDX_01,0x12);
    github_com_imroc_req_v3_Request_SetHeader("macOStasksstartMacOSnanos%s_%ddiffsplansskill.jsonPATCHx-appuser_ravenbytesQuery3.0.0ROUTE%s#%d</tr>debug%s:%d*fuzz*listPOST:HEAD:IndexInputshort%s,%s=j=02=G=15-0700%dh%sdefersweeptestRtestWexecWhchanexecRschedsudogtimergscanmheaptracepanicsleepamd64gcing MB,  got= ...\n max=scav  ptr ] = (trap:init  ms, fault and  tab= tag= top=[...], fp:deny"
                 ,5,extraout_RDX_02,0xe);
    github_com_imroc_req_v3_Request_SetHeader("15.6.1inputsimagesoffset0.70.0system/usagev2.9.7%s[%d]ServerConfigSERVERDOMAINMETHOD%s#%d,Logger<html><head><body><hr />/traceactiondomainmethod/[^/]+PATCH:TRACE:/indexUSAGE\n-/--%sOutput-07:00000000 Valuesysmontimersefenceselectscalar, not       unused objs\n next= jobs= goid sweep  B -> % util alloc free  span= prev= list=, i =  code= addr=], sp= m->p= p->m=SCHED  curg= ctxt: min=  max= bad ts(...)\n m=nil base hangupkilledallow"
                 ,6,extraout_RDX_03,0x11);
    uStack_40 = github_com_imroc_req_v3_Request_SetHeader(&DAT_01c4edb3,0x10,extraout_RDX_04,0xc);
    auVar12 = runtime_concatstring2(*(undefined8 *)(param_1 + 0x38),*(undefined8 *)(param_1 + 0x40),param_1,7
                          );
    github_com_imroc_req_v3_Request_SetHeader(auVar12._0_8_,&DAT_01c3ddc9,auVar12._8_8_,0xd);
    github_com_imroc_req_v3_Request_SetHeader(&DAT_01c38e63,3,extraout_RDX_05,6);
    github_com_imroc_req_v3_Request_SetHeader(&DAT_01c3df2e,7,extraout_RDX_06,0xf);
    github_com_imroc_req_v3_Request_SetHeader(&DAT_01c48208,0xc,extraout_RDX_07,4);
    lStack_90 = github_com_imroc_req_v3_Request_SetHeader(0,0,extraout_RDX_08,10);
    *(undefined8 *)(lStack_90 + 0xc0) = uVar5;
    *(undefined **)(lStack_90 + 200) = puVar8;
    if (DAT_02e5e450 != 0) {
      lVar7 = *(long *)(lStack_90 + 0xb8);
      lStack_90 = runtime_gcWriteBarrier2();
      *in_R11 = lStack_88;
      in_R11[1] = lVar7;
    }
    *(long *)(lStack_90 + 0xb8) = lStack_88;
    puVar3 = (undefined8 *)runtime_newobject();
    auVar14._8_8_ = lStack_90;
    auVar14._0_8_ = puVar3;
    *puVar3 = &LAB_017200e0;
    puVar3[2] = uVar5;
    puVar3[3] = puVar8;
    if (DAT_02e5e450 != 0) {
      lVar7 = *(long *)(lStack_90 + 0xd0);
      auVar14 = runtime_gcWriteBarrier3();
      *in_R11 = lStack_88;
      in_R11[1] = auVar14._0_8_;
      in_R11[2] = lVar7;
    }
    *(long *)(auVar14._0_8_ + 8) = lStack_88;
    *(long *)(auVar14._8_8_ + 0xd0) = auVar14._0_8_;
    uVar5 = 4;
    github_com_imroc_req_v3_Request_Send(&DAT_01ca0232,0x53);
    lStack_80 = uVar5;
    github_com_gogf_gf_v2_frame_gins_Log();
    uStack_70 = DAT_01c3979a;
    lStack_68 = lStack_80;
    github_com_gogf_gf_v2_os_glog_Logger_Warningf(&DAT_01c68ce0,0x1e,lStack_80,uStack0000000000000028,&uStack_70,1);
    return;
  }
  lStack_80 = lVar7;
  github_com_gogf_gf_v2_frame_gins_Log();
  if (lVar11 == 0) {
    uStack_70 = 0;
  }
  else {
    uStack_70 = *(undefined8 *)(lVar11 + 8);
  }
  lStack_68 = lStack_80;
  github_com_gogf_gf_v2_os_glog_Logger_Warningf(&DAT_01c79a91,0x27,lStack_80,uStack0000000000000028,&uStack_70,1);
  return;
}




// === warp.GetQuotaInfo @ 0x1713b80 ===

/* WARNING: Removing unreachable block (ram,0x0171434b) */
/* WARNING: Removing unreachable block (ram,0x017145fd) */
/* WARNING: Removing unreachable block (ram,0x0171435c) */
/* WARNING: Removing unreachable block (ram,0x0171439d) */
/* WARNING: Removing unreachable block (ram,0x017143a8) */
/* WARNING: Removing unreachable block (ram,0x017143ac) */
/* WARNING: Removing unreachable block (ram,0x017143ee) */
/* WARNING: Removing unreachable block (ram,0x017143fd) */
/* WARNING: Removing unreachable block (ram,0x0171440f) */
/* WARNING: Removing unreachable block (ram,0x01714418) */
/* WARNING: Removing unreachable block (ram,0x0171444e) */
/* WARNING: Removing unreachable block (ram,0x0171449a) */
/* WARNING: Removing unreachable block (ram,0x017144a9) */
/* WARNING: Removing unreachable block (ram,0x0171452c) */
/* WARNING: Removing unreachable block (ram,0x01714546) */
/* WARNING: Removing unreachable block (ram,0x01714569) */
/* WARNING: Removing unreachable block (ram,0x01714573) */
/* WARNING: Removing unreachable block (ram,0x0171457c) */
/* WARNING: Removing unreachable block (ram,0x01714583) */
/* WARNING: Removing unreachable block (ram,0x017145cb) */
/* WARNING: Removing unreachable block (ram,0x017145da) */
/* WARNING: Removing unreachable block (ram,0x017144af) */
/* WARNING: Removing unreachable block (ram,0x01714502) */
/* WARNING: Removing unreachable block (ram,0x01714511) */
/* WARNING: Removing unreachable block (ram,0x017145f0) */
/* WARNING: Removing unreachable block (ram,0x01714425) */

undefined8 warp_GetQuotaInfo(long param_1,undefined8 param_2,undefined8 param_3,long param_4)

{
  ulong uVar1;
  long lVar2;
  long lVar3;
  long lVar4;
  undefined8 *puVar5;
  undefined8 uVar6;
  undefined8 *puVar7;
  long lVar8;
  ulong uVar9;
  undefined8 uVar10;
  undefined8 extraout_RDX;
  undefined8 extraout_RDX_00;
  long unaff_RBX;
  undefined1 (*in_R11) [16];
  long unaff_R14;
  undefined1 auVar11 [16];
  long lStack0000000000000010;
  long lStack0000000000000018;
  long lStack0000000000000020;
  long lStack_58;
  undefined8 uStack_50;
  undefined8 uStack_48;
  long lStack_38;
  undefined8 uStack_30;
  undefined8 uStack_28;
  undefined8 uStack_20;
  undefined8 uStack_18;
  
  lStack0000000000000018 = param_4;
  lStack0000000000000010 = unaff_RBX;
  lStack0000000000000020 = param_1;
  while (&lStack_58 <= *(long **)(unaff_R14 + 0x10)) {
    runtime_morestack_noctxt();
  }
  (**(code **)PTR_PTR_02ddf1a8)();
  (**(code **)PTR_PTR_02ddf1b0)();
  lVar4 = kiro2api_internal_logic_warp_sWarp_CheckToken(lStack0000000000000020);
  if (lVar4 != 0) {
    return 0;
  }
  runtime_makemap_small();
  puVar5 = (undefined8 *)runtime_mapassign_faststr(5);
  *puVar5 = &DAT_0194e220;
  if (DAT_02e5e450 != 0) {
    auVar11 = runtime_gcWriteBarrier1();
    puVar5 = auVar11._0_8_;
    *(long *)*in_R11 = auVar11._8_8_;
  }
  puVar5[1] = &PTR_DAT_01f3a330;
  puVar5 = (undefined8 *)runtime_mapassign_faststr(0xd);
  *puVar5 = &DAT_0194e220;
  if (DAT_02e5e450 != 0) {
    uVar10 = puVar5[1];
    puVar5 = (undefined8 *)runtime_gcWriteBarrier1();
    *(undefined8 *)*in_R11 = uVar10;
  }
  puVar5[1] = &PTR_DAT_01f3a340;
  uStack_18 = runtime_makemap_small();
  uStack_20 = runtime_makemap_small();
  uStack_28 = runtime_makemap_small();
  puVar5 = (undefined8 *)runtime_mapassign_faststr(7);
  *puVar5 = &DAT_0194e220;
  if (DAT_02e5e450 != 0) {
    auVar11 = runtime_gcWriteBarrier1();
    puVar5 = auVar11._0_8_;
    *(long *)*in_R11 = auVar11._8_8_;
  }
  puVar5[1] = &PTR_DAT_01f3a350;
  puVar5 = (undefined8 *)runtime_mapassign_faststr(0xd);
  *puVar5 = &DAT_01a233a0;
  if (DAT_02e5e450 != 0) {
    uVar10 = puVar5[1];
    puVar5 = (undefined8 *)runtime_gcWriteBarrier2();
    *(undefined8 *)*in_R11 = uStack_28;
    *(undefined8 *)(*in_R11 + 8) = uVar10;
  }
  puVar5[1] = uStack_28;
  uStack_28 = runtime_makemap_small();
  puVar5 = (undefined8 *)runtime_mapassign_faststr(8);
  *puVar5 = &DAT_0194e220;
  if (DAT_02e5e450 != 0) {
    auVar11 = runtime_gcWriteBarrier1();
    puVar5 = auVar11._0_8_;
    *(long *)*in_R11 = auVar11._8_8_;
  }
  puVar5[1] = &DAT_01f3a360;
  puVar5 = (undefined8 *)runtime_mapassign_faststr(4);
  *puVar5 = &DAT_0194e220;
  if (DAT_02e5e450 != 0) {
    auVar11 = runtime_gcWriteBarrier1();
    puVar5 = auVar11._0_8_;
    *(long *)*in_R11 = auVar11._8_8_;
  }
  puVar5[1] = &DAT_01f3a360;
  puVar5 = (undefined8 *)runtime_mapassign_faststr(9);
  *puVar5 = &DAT_01a233a0;
  if (DAT_02e5e450 != 0) {
    uVar10 = puVar5[1];
    puVar5 = (undefined8 *)runtime_gcWriteBarrier2();
    *(undefined8 *)*in_R11 = uStack_28;
    *(undefined8 *)(*in_R11 + 8) = uVar10;
  }
  puVar5[1] = uStack_28;
  puVar5 = (undefined8 *)runtime_mapassign_faststr(0xe);
  *puVar5 = &DAT_01a233a0;
  if (DAT_02e5e450 != 0) {
    uVar10 = puVar5[1];
    puVar5 = (undefined8 *)runtime_gcWriteBarrier2();
    *(undefined8 *)*in_R11 = uStack_20;
    *(undefined8 *)(*in_R11 + 8) = uVar10;
  }
  puVar5[1] = uStack_20;
  puVar5 = (undefined8 *)runtime_mapassign_faststr(9);
  *puVar5 = &DAT_01a233a0;
  if (DAT_02e5e450 != 0) {
    uVar10 = puVar5[1];
    puVar5 = (undefined8 *)runtime_gcWriteBarrier2();
    *(undefined8 *)*in_R11 = uStack_18;
    *(undefined8 *)(*in_R11 + 8) = uVar10;
  }
  lVar4 = lStack0000000000000018;
  puVar5[1] = uStack_18;
  uVar6 = kiro2api_internal_logic_warp_GetWarpProxyURL();
  lStack_58 = kiro2api_internal_logic_warp_NewGraphQLClient();
  uVar10 = 0;
  if (lVar4 != 0) {
    github_com_imroc_req_v3_Client_SetProxyURL();
    uVar10 = uVar6;
  }
  if (*(long *)(lStack0000000000000020 + 0x58) == 0) {
    uVar6 = github_com_google_uuid_NewString();
    *(undefined8 *)(lStack0000000000000020 + 0x58) = uVar10;
    lVar4 = lStack0000000000000020;
    if (DAT_02e5e450 != 0) {
      auVar11 = runtime_gcWriteBarrier2();
      uVar6 = auVar11._0_8_;
      *in_R11 = auVar11;
    }
    *(undefined8 *)(lVar4 + 0x50) = uVar6;
    kiro2api_internal_dao_WarpAccountDao_Update();
  }
  puVar5 = *(undefined8 **)(lStack_58 + 0x60);
  if (puVar5 == (undefined8 *)0x0) {
    lVar8 = 0;
  }
  else {
    puVar7 = (undefined8 *)runtime_newobject();
    *puVar7 = *puVar5;
    auVar11._8_8_ = puVar5[1];
    auVar11._0_8_ = puVar7;
    puVar7 = puVar5;
    if (DAT_02e5e450 != 0) {
      auVar11 = runtime_gcWriteBarrier1();
      *(long *)*in_R11 = auVar11._8_8_;
    }
    lVar8 = auVar11._0_8_;
    *(long *)(lVar8 + 8) = auVar11._8_8_;
    lVar4 = *(long *)(lVar8 + 0x18);
    uVar9 = *(ulong *)(lVar8 + 0x20);
    lVar2 = puVar7[3];
    uVar1 = lVar4 + lVar2;
    uVar10 = *(undefined8 *)(lVar8 + 0x10);
    uStack_30 = puVar7[2];
    if (uVar9 < uVar1) {
      uVar10 = runtime_growslice(lVar2,&DAT_019ea040);
    }
    in_R11 = (undefined1 (*) [16])(lVar4 << 3);
    uVar6 = uStack_30;
    uStack_30 = uVar10;
    runtime_typedslicecopy(uVar6,lVar2,(long)(lVar4 - uVar9) >> 0x3f & (ulong)in_R11,uVar1 - lVar4);
    *(ulong *)(lVar8 + 0x18) = uVar1;
    *(ulong *)(lVar8 + 0x20) = uVar9;
    lVar4 = lVar8;
    if (DAT_02e5e450 != 0) {
      runtime_gcWriteBarrier2();
      *(undefined8 *)*in_R11 = uStack_30;
      *(undefined8 *)(*in_R11 + 8) = extraout_RDX;
    }
    *(undefined8 *)(lVar4 + 0x10) = uStack_30;
    lVar2 = *(long *)(lVar4 + 0x30);
    uVar9 = *(ulong *)(lVar4 + 0x38);
    lVar3 = puVar5[6];
    uVar1 = lVar2 + lVar3;
    lVar4 = *(long *)(lVar4 + 0x28);
    lStack_38 = puVar5[5];
    if (uVar9 < uVar1) {
      lVar4 = runtime_growslice(lVar3,&DAT_019cbd00);
    }
    uVar10 = lStack_38;
    lStack_38 = lVar4;
    runtime_typedslicecopy(uVar10,lVar3,((long)(lVar2 - uVar9) >> 0x3f & lVar2 << 3) + lVar4,uVar1 - lVar2);
    *(ulong *)(lVar8 + 0x30) = uVar1;
    *(ulong *)(lVar8 + 0x38) = uVar9;
    if (DAT_02e5e450 != 0) {
      uVar10 = *(undefined8 *)(lVar8 + 0x28);
      runtime_gcWriteBarrier2();
      *(long *)*in_R11 = lStack_38;
      *(undefined8 *)(*in_R11 + 8) = uVar10;
    }
    *(long *)(lVar8 + 0x28) = lStack_38;
  }
  lVar4 = runtime_newobject();
  if (DAT_02e5e450 != 0) {
    lVar4 = runtime_gcWriteBarrier2();
    *(long *)*in_R11 = lStack_58;
    *(long *)(*in_R11 + 8) = lVar8;
  }
  *(long *)(lVar4 + 0xf8) = lStack_58;
  *(long *)(lVar4 + 0x130) = lVar8;
  if (lStack0000000000000010 != 0) {
    *(long *)(lVar4 + 0x160) = lStack0000000000000010;
    if (DAT_02e5e450 != 0) {
      lVar4 = runtime_gcWriteBarrier1();
      *(long *)*in_R11 = lStack0000000000000018;
    }
    *(long *)(lVar4 + 0x168) = lStack0000000000000018;
  }
  auVar11 = runtime_concatstring2(*(undefined8 *)(lStack0000000000000020 + 0x38),
                         *(undefined8 *)(lStack0000000000000020 + 0x40),lStack0000000000000020,7);
  github_com_imroc_req_v3_Request_SetHeader(auVar11._0_8_,&DAT_01c3ddc9,auVar11._8_8_,0xd);
  github_com_imroc_req_v3_Request_SetHeader(*(undefined8 *)(lStack0000000000000020 + 0x50),
               *(undefined8 *)(lStack0000000000000020 + 0x58),lStack0000000000000020,0x14);
  github_com_imroc_req_v3_Request_SetBodyJsonMarshal();
  uVar10 = 4;
  github_com_imroc_req_v3_Request_Send(&DAT_01c86749,0x30);
  uStack_50 = DAT_01c3979a;
  uStack_48 = uVar10;
  fmt_Errorf(1,1,extraout_RDX_00,&uStack_50);
  return 0;
}



