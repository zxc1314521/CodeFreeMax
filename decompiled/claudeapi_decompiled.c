// CodeFreeMax - CLAUDEAPI Channel Decompiled Functions
// 3 functions

// === claudeapi.ChatController.Messages @ 0x139ce00 ===

void claudeapi_ChatController_Messages(undefined *param_1)

{
  bool bVar1;
  undefined **ppuVar2;
  long lVar3;
  undefined **ppuVar4;
  undefined8 uVar5;
  undefined *puVar6;
  long *plVar7;
  undefined **ppuVar8;
  undefined8 *puVar9;
  char cVar10;
  undefined **ppuVar11;
  long lVar12;
  undefined *extraout_RDX;
  long lVar13;
  ulong uVar14;
  long extraout_RDX_00;
  undefined **extraout_RDX_01;
  undefined **unaff_RBX;
  ulong uVar15;
  long *plVar16;
  undefined **ppuVar17;
  undefined *puVar18;
  undefined **in_R11;
  long unaff_R14;
  undefined1 auVar19 [16];
  undefined1 auVar20 [16];
  undefined **ppuStack0000000000000010;
  undefined *puStack_288;
  ulong uStack_280;
  undefined **ppuStack_278;
  undefined8 uStack_270;
  undefined **ppuStack_268;
  undefined **ppuStack_260;
  long lStack_258;
  undefined **ppuStack_250;
  undefined **ppuStack_248;
  long lStack_240;
  ulong uStack_238;
  ulong uStack_230;
  long lStack_228;
  undefined **ppuStack_220;
  undefined **ppuStack_218;
  undefined **ppuStack_210;
  undefined **ppuStack_208;
  undefined8 uStack_200;
  undefined8 uStack_1f8;
  undefined8 uStack_1f0;
  undefined8 uStack_1e8;
  undefined8 uStack_1e0;
  undefined8 uStack_1d8;
  undefined8 uStack_1d0;
  undefined *puStack_1c8;
  undefined8 uStack_1c0;
  undefined **ppuStack_1b8;
  undefined *puStack_1b0;
  undefined **ppuStack_1a8;
  undefined *puStack_1a0;
  undefined *puStack_198;
  undefined **ppuStack_190;
  undefined8 uStack_188;
  undefined8 uStack_180;
  undefined *puStack_178;
  undefined **ppuStack_170;
  undefined **ppuStack_168;
  undefined8 uStack_160;
  undefined8 uStack_158;
  undefined **ppuStack_150;
  undefined *puStack_148;
  undefined8 uStack_140;
  long *plStack_138;
  undefined *puStack_130;
  long *plStack_128;
  long *plStack_120;
  undefined **ppuStack_118;
  undefined **ppuStack_110;
  undefined **ppuStack_108;
  undefined8 uStack_100;
  undefined **ppuStack_f8;
  undefined8 uStack_f0;
  undefined **ppuStack_e8;
  undefined8 uStack_e0;
  undefined **ppuStack_d8;
  undefined8 *puStack_d0;
  undefined8 *puStack_c8;
  undefined *puStack_70;
  undefined8 uStack_68;
  undefined8 *puStack_60;
  undefined8 uStack_58;
  undefined8 *puStack_50;
  undefined8 uStack_48;
  undefined8 *puStack_40;
  undefined *puStack_38;
  undefined **ppuStack_30;
  undefined **ppuStack_28;
  undefined8 *puStack_20;
  undefined8 uStack_18;
  long *plStack_10;
  
  ppuStack_170 = unaff_RBX;
  while (ppuStack0000000000000010 = ppuStack_170, &puStack_288 <= *(undefined ***)(unaff_R14 + 0x10)
        ) {
    runtime_morestack_noctxt();
    ppuStack_170 = ppuStack0000000000000010;
  }
  ppuStack_260 = (undefined **)github_com_gogf_gf_v2_net_ghttp_Request_Context();
  xdZLD7_Ho6qQX();
  lVar3 = *(long *)(*ppuStack0000000000000010 + 0x40);
  ppuVar17 = *(undefined ***)(*ppuStack0000000000000010 + 0x48);
  ppuVar8 = ppuStack0000000000000010;
  if (lVar3 != 0) {
    uVar14 = (ulong)*(uint *)(lVar3 + 0x10);
    do {
      in_R11 = *(undefined ***)(PTR_DAT_02de5900 + (uVar14 & *(ulong *)PTR_DAT_02de5900) * 0x10 + 8)
      ;
      param_1 = PTR_DAT_02de5900;
      if (in_R11 == *(undefined ***)(lVar3 + 8)) goto LAB_0139ce7d;
      uVar14 = uVar14 + 1;
    } while (in_R11 != (undefined **)0x0);
    ppuStack_108 = ppuVar17;
    runtime_typeAssert();
    ppuVar17 = ppuStack_108;
  }
LAB_0139ce7d:
  uStack_158 = io_ReadAll();
  if (param_1 != (undefined *)0x0) {
    uStack_140 = runtime_makemap_small();
    puVar9 = (undefined8 *)runtime_mapassign_faststr(4);
    *puVar9 = &DAT_0194e220;
    if (DAT_02e5e450 != 0) {
      auVar19 = runtime_gcWriteBarrier1();
      puVar9 = auVar19._0_8_;
      *in_R11 = auVar19._8_8_;
    }
    puVar9[1] = &PTR_DAT_01f39850;
    puStack_148 = (undefined *)runtime_makemap_small();
    puVar9 = (undefined8 *)runtime_mapassign_faststr(4);
    *puVar9 = &DAT_0194e220;
    if (DAT_02e5e450 != 0) {
      auVar19 = runtime_gcWriteBarrier1();
      puVar9 = auVar19._0_8_;
      *in_R11 = auVar19._8_8_;
    }
    puVar9[1] = &PTR_DAT_01f397e0;
    puVar9 = (undefined8 *)runtime_mapassign_faststr(7);
    *puVar9 = &DAT_0194e220;
    if (DAT_02e5e450 != 0) {
      auVar19 = runtime_gcWriteBarrier1();
      puVar9 = auVar19._0_8_;
      *in_R11 = auVar19._8_8_;
    }
    puVar9[1] = &PTR_DAT_01f399f0;
    puVar9 = (undefined8 *)runtime_mapassign_faststr(5);
    *puVar9 = &DAT_01a233a0;
    if (DAT_02e5e450 != 0) goto LAB_0139e58e;
    do {
      puVar9[1] = puStack_148;
      puStack_198 = ppuStack0000000000000010[4];
      github_com_gogf_gf_v2_net_ghttp_Response_WriteJson();
      runtime_gopanic();
LAB_0139e58e:
      auVar19 = runtime_gcWriteBarrier2();
      puVar9 = auVar19._0_8_;
      *in_R11 = puStack_148;
      in_R11[1] = auVar19._8_8_;
    } while( true );
  }
  ppuStack_250 = ppuVar17;
  ppuStack_248 = ppuVar8;
  (**(code **)(*(long *)(*ppuStack0000000000000010 + 0x40) + 0x18))();
  auVar19 = github_com_gogf_gf_v2_frame_gins_Log();
  uStack_1d0 = auVar19._0_8_;
  github_com_gogf_gf_v2_net_ghttp_Request_GetHeader(0,0,auVar19._8_8_,0xe,0);
  auVar19 = runtime_convTstring();
  uStack_18 = auVar19._0_8_;
  puStack_20 = &DAT_0194e220;
  github_com_gogf_gf_v2_os_glog_Logger_Infof(&DAT_01c75cf2,0x25,auVar19._8_8_,ppuStack_170,&puStack_20,1);
  uStack_1d8 = github_com_gogf_gf_v2_frame_gins_Log();
  runtime_slicebytetostring();
  lVar3 = internal_stringslite_Index(10);
  puStack_40 = (undefined8 *)&DAT_0194e620;
  puStack_38 = &DAT_01f8a680 + (ulong)(-1 < lVar3) * 8;
  auVar19 = runtime_convT64();
  ppuStack_28 = auVar19._0_8_;
  ppuStack_30 = (undefined **)&DAT_0194e460;
  github_com_gogf_gf_v2_os_glog_Logger_Infof(&DAT_01c94827,0x3e,auVar19._8_8_,ppuStack_170,&puStack_40,2);
  if ((long)ppuStack_250 < 2000) {
    uStack_1e0 = github_com_gogf_gf_v2_frame_gins_Log();
    runtime_slicebytetostring();
    uStack_18 = runtime_convTstring();
    puStack_20 = &DAT_0194e220;
    github_com_gogf_gf_v2_os_glog_Logger_Infof(&DAT_01c635f0,0x1b,&DAT_0194e220,ppuStack_170,&puStack_20,1);
  }
  ppuVar2 = ppuStack_250;
  uStack_1c0 = kiro2api_internal_logic_claudeapi_ExtractSessionId();
  ppuStack_168 = (undefined **)kiro2api_internal_common_NewRetryConfig();
  uStack_160 = kiro2api_internal_logic_GetConcurrencyManager();
  lVar3 = 0;
  ppuVar17 = (undefined **)0x0;
  ppuVar8 = (undefined **)0x0;
  do {
    if ((long)ppuStack_168[1] <= lVar3) {
LAB_0139e140:
      if (ppuVar17 == (undefined **)0x0) {
        ppuVar8 = (undefined **)&DAT_0000001b;
        puStack_178 = &DAT_01c6360b;
      }
      else {
        puStack_178 = (undefined *)(*(code *)ppuVar17[3])();
      }
      ppuStack_268 = ppuVar8;
      uStack_200 = github_com_gogf_gf_v2_frame_gins_Log();
      puStack_38 = (undefined *)runtime_convTstring();
      puStack_40 = &DAT_0194e220;
      ppuStack_28 = (undefined **)runtime_convTslice();
      ppuStack_30 = (undefined **)&DAT_0192e460;
      github_com_gogf_gf_v2_os_glog_Logger_Warningf(&DAT_01c8ada3,0x34,&DAT_0192e460,ppuStack_170,&puStack_40,2);
      FtTgl3_ZQHMyB7();
      uStack_140 = runtime_makemap_small();
      puVar9 = (undefined8 *)runtime_mapassign_faststr(4);
      *puVar9 = &DAT_0194e220;
      if (DAT_02e5e450 != 0) {
        puVar6 = (undefined *)puVar9[1];
        puVar9 = (undefined8 *)runtime_gcWriteBarrier1();
        *in_R11 = puVar6;
      }
      puVar9[1] = &PTR_DAT_01f39850;
      puStack_148 = (undefined *)runtime_makemap_small();
      puVar9 = (undefined8 *)runtime_mapassign_faststr(4);
      *puVar9 = &DAT_0194e220;
      if (DAT_02e5e450 != 0) {
        auVar19 = runtime_gcWriteBarrier1();
        puVar9 = auVar19._0_8_;
        *in_R11 = auVar19._8_8_;
      }
      puVar9[1] = &PTR_DAT_01f39a00;
      plStack_120 = (long *)runtime_convTstring();
      puVar9 = (undefined8 *)runtime_mapassign_faststr(7);
      *puVar9 = &DAT_0194e220;
      if (DAT_02e5e450 != 0) {
        auVar19 = runtime_gcWriteBarrier2();
        puVar9 = auVar19._0_8_;
        *in_R11 = (undefined *)plStack_120;
        in_R11[1] = auVar19._8_8_;
      }
      puVar9[1] = plStack_120;
      puVar9 = (undefined8 *)runtime_mapassign_faststr(5);
      *puVar9 = &DAT_01a233a0;
      if (DAT_02e5e450 != 0) goto LAB_0139e3a7;
      do {
        puVar9[1] = puStack_148;
        puStack_1a0 = ppuStack0000000000000010[4];
        github_com_gogf_gf_v2_net_ghttp_Response_WriteJson();
        runtime_gopanic();
LAB_0139e3a7:
        auVar19 = runtime_gcWriteBarrier2();
        puVar9 = auVar19._0_8_;
        *in_R11 = puStack_148;
        in_R11[1] = auVar19._8_8_;
      } while( true );
    }
    in_R11 = ppuVar2;
    ppuStack_278 = ppuVar17;
    lStack_258 = lVar3;
    ppuStack_190 = ppuVar8;
    if (ppuVar2 == (undefined **)0x0) {
      puVar18 = (undefined *)0x0;
    }
    else {
      uStack_e0 = uStack_1c0;
      ppuStack_d8 = ppuVar2;
      cVar10 = ' ';
      puVar6 = (undefined *)internal_sync_HashTrieMap[go_shape_interface {},go_shape_interface {}]_Load(&uStack_e0);
      if (cVar10 == '\0') {
        puVar18 = (undefined *)0x0;
      }
      else {
        puVar18 = PTR_LOOP_01f80180;
        if (puVar6 != &DAT_0194e420) {
          ppuVar8 = (undefined **)&DAT_0194e420;
          runtime_panicdottypeE();
          ppuVar17 = extraout_RDX_01;
          goto LAB_0139e140;
        }
      }
    }
    ppuVar8 = ppuStack_260;
    ppuVar17 = (undefined **)ppuStack_168[3];
    ppuVar11 = ppuStack_170;
    puStack_288 = puVar18;
    ppuVar4 = (undefined **)kiro2api_internal_logic_AccountConcurrencyManager_GetClaudeApiAccountWithSlot();
    if (ppuVar17 == (undefined **)0x0) {
      ppuStack_1a8 = ppuVar8;
      puVar6 = ppuStack_168[5];
      puVar18 = ppuStack_168[4] + 1;
      auVar19._8_8_ = ppuStack_168;
      auVar19._0_8_ = ppuStack_168[3];
      in_R11 = (undefined **)*ppuVar4;
      ppuStack_1b8 = ppuVar11;
      ppuStack_150 = ppuVar4;
      if (puVar6 < puVar18) {
        ppuStack_208 = in_R11;
        uVar5 = runtime_growslice(1,&DAT_0194e420);
        auVar19._8_8_ = ppuStack_168;
        auVar19._0_8_ = uVar5;
        ppuStack_168[5] = puVar6;
        if (DAT_02e5e450 != 0) {
          puVar6 = ppuStack_168[3];
          auVar19 = runtime_gcWriteBarrier2();
          *in_R11 = auVar19._0_8_;
          in_R11[1] = puVar6;
        }
        *(long *)(auVar19._8_8_ + 0x18) = auVar19._0_8_;
        in_R11 = ppuStack_208;
      }
      *(undefined **)(auVar19._8_8_ + 0x20) = puVar18;
      *(undefined ***)(auVar19._0_8_ + -8 + (long)puVar18 * 8) = in_R11;
      uStack_1e8 = github_com_gogf_gf_v2_frame_gins_Log();
      uStack_68 = runtime_convT64();
      puStack_70 = &DAT_0194e420;
      uStack_58 = runtime_convTstring();
      puStack_60 = &DAT_0194e220;
      uStack_48 = runtime_convT64();
      puStack_50 = &DAT_0194e460;
      ppuVar17 = (undefined **)&DAT_01c8bd7c;
      github_com_gogf_gf_v2_os_glog_Logger_Infof(&DAT_01c8bd7c,0x35,&DAT_0194e460,ppuStack_170,&puStack_70);
      lVar3 = xdZLD7_I72MS_J1x();
      if (lVar3 != 0) {
        kiro2api_internal_model_ClaudeApiAccount_LoadGateCredentials();
      }
      ppuVar8 = ppuStack_260;
      if (DAT_02e34d50 == 0) {
LAB_0139e125:
        ppuVar8 = &PTR_DAT_01f39990;
        runtime_gopanic();
        goto LAB_0139e140;
      }
      ppuVar17 = (undefined **)(**(code **)(DAT_02e34d50 + 0x18))(ppuStack_150);
      if (ppuVar17 == (undefined **)0x0) {
        bVar1 = false;
        lVar3 = 0;
        ppuVar17 = ppuStack_278;
        ppuStack_118 = ppuStack_190;
        puVar6 = (undefined *)0x0;
        while (ppuVar8 = ppuStack_260, lVar3 < (long)*ppuStack_168) {
          if (DAT_02e34d50 == 0) {
            ppuVar17 = ppuStack_150;
            in_R11 = ppuStack_168;
            runtime_gopanic();
            goto LAB_0139e125;
          }
          ppuVar11 = ppuStack_170;
          lStack_240 = lVar3;
          ppuStack_218 = ppuVar17;
          ppuStack_110 = ppuStack_118;
          puVar6 = (undefined *)(**(code **)(DAT_02e34d50 + 0x38))();
          puStack_1b0 = puVar6;
          if (ppuVar8 == (undefined **)0x0) {
            lVar3 = *(long *)(puVar6 + 0x10);
            ppuVar17 = ppuStack_218;
            ppuStack_118 = ppuStack_110;
            if (lVar3 - 200U < 100) break;
            if (lVar3 == 0x191) {
              bVar1 = true;
            }
            else if (lVar3 == 0x193) {
              bVar1 = true;
            }
            else if (lVar3 == 0x1ad) {
              bVar1 = true;
            }
            else {
              bVar1 = false;
            }
            if (bVar1) {
              (**(code **)(*(long *)(puVar6 + 0x40) + 0x18))();
              ppuVar17 = (undefined **)0x0;
              ppuStack_118 = (undefined **)0x0;
              puVar6 = puStack_1b0;
              break;
            }
            if ((lVar3 < 500) || ((long)(*ppuStack_168 + -1) <= lStack_240)) {
              ppuVar17 = (undefined **)0x0;
              ppuStack_118 = (undefined **)0x0;
              break;
            }
            (**(code **)(*(long *)(puVar6 + 0x40) + 0x18))();
            time_Sleep();
            ppuStack_118 = (undefined **)0x0;
            ppuVar17 = (undefined **)0x0;
          }
          else {
            ppuStack_118 = ppuVar11;
            ppuVar17 = ppuVar8;
            if (lStack_240 < (long)(*ppuStack_168 + -1)) {
              ppuStack_220 = ppuVar8;
              time_Sleep();
              ppuVar17 = ppuStack_220;
            }
          }
          puVar6 = puStack_1b0;
          lVar3 = lStack_240 + 1;
        }
        ppuStack_210 = ppuVar17;
        puStack_1b0 = puVar6;
        ppuStack_108 = ppuStack_118;
        if (bVar1) {
          uStack_1f8 = github_com_gogf_gf_v2_frame_gins_Log(ppuStack_150,uStack_158,ppuVar17,0,ppuStack_250,ppuStack_248);
          puStack_38 = (undefined *)runtime_convT64();
          puStack_40 = (undefined8 *)&DAT_0194e420;
          if (ppuStack_210 == (undefined **)0x0) {
            in_R11 = (undefined **)0x0;
          }
          else {
            in_R11 = (undefined **)ppuStack_210[1];
          }
          ppuStack_28 = ppuStack_108;
          ppuStack_30 = in_R11;
          github_com_gogf_gf_v2_os_glog_Logger_Warningf(&DAT_01c865c9,0x30,ppuStack_108,ppuStack_170,&puStack_40,2);
          if (ppuVar2 != (undefined **)0x0) {
            uStack_100 = uStack_1c0;
            ppuStack_f8 = ppuVar2;
            internal_sync_HashTrieMap[go_shape_interface {},go_shape_interface {}]_LoadAndDelete(&uStack_100,uStack_1c0,ppuVar2,&DAT_0194e220);
          }
          if (DAT_02e34d50 == 0) {
            runtime_gopanic();
            goto LAB_0139dc4a;
          }
          lStack_228 = DAT_02e34d50;
          uStack_230 = *(ulong *)(puStack_1b0 + 0x10);
          puStack_130 = DAT_02e34d58;
          puVar9 = (undefined8 *)runtime_newobject();
          *puVar9 = &LAB_0139e7c0;
          puVar9[1] = lStack_228;
          if (DAT_02e5e450 != 0) {
            puVar9 = (undefined8 *)runtime_gcWriteBarrier2();
            *in_R11 = puStack_130;
            in_R11[1] = (undefined *)ppuStack_150;
          }
          puVar9[2] = puStack_130;
          puVar9[3] = &PTR_DAT_01f524f8;
          puVar9[4] = &DAT_02e5d6a0;
          puVar9[5] = ppuStack_150;
          puVar9[6] = uStack_230;
          runtime_newproc();
          (*(code *)*ppuStack_1a8)();
          ppuVar17 = ppuStack_210;
          ppuVar8 = ppuStack_108;
        }
        else {
          in_R11 = ppuStack_168;
          if (puVar6 != (undefined *)0x0) {
            ppuStack_210 = *(undefined ***)(puVar6 + 0x40);
            ppuStack_108 = *(undefined ***)(puVar6 + 0x48);
            puVar9 = (undefined8 *)runtime_newobject();
            *puVar9 = &LAB_0139e760;
            puVar9[1] = ppuStack_210;
            if (DAT_02e5e450 != 0) {
              puVar9 = (undefined8 *)runtime_gcWriteBarrier1();
              *in_R11 = (undefined *)ppuStack_108;
            }
            puVar9[2] = ppuStack_108;
            runtime_deferproc();
            if ((*(long *)(puStack_1b0 + 0x10) < 300) && (ppuVar2 != (undefined **)0x0)) {
              plStack_120 = (long *)runtime_convTstring();
              auVar19 = runtime_convT64();
              internal_sync_HashTrieMap[go_shape_interface {},go_shape_interface {}]_Swap(plStack_120,&DAT_0194e420,auVar19._8_8_,&DAT_0194e220,auVar19._0_8_);
            }
            (*(code *)*ppuStack_1a8)();
            (*(code *)*ppuStack_1b8)();
            plStack_128 = (long *)**(undefined8 **)ppuStack0000000000000010[4];
            FUN_00488ceb(&uStack_f0);
            runtime_mapIterStart();
            while (puStack_d0 != (undefined8 *)0x0) {
              plVar7 = (long *)*puStack_c8;
              uStack_188 = *puStack_d0;
              uStack_270 = puStack_d0[1];
              uVar14 = puStack_c8[1];
              while (0 < (long)uVar14) {
                puStack_1c8 = (undefined *)*plVar7;
                lVar3 = plVar7[1];
                uStack_230 = uVar14;
                plStack_120 = plVar7;
                uStack_180 = (**(code **)(*plStack_128 + 0x18))();
                uVar5 = uStack_270;
                net_textproto_CanonicalMIMEHeaderKey();
                plVar7 = (long *)runtime_mapassign_faststr(uVar5);
                uVar14 = plVar7[2];
                lVar12 = plVar7[1];
                uVar15 = lVar12 + 1;
                auVar20._8_8_ = plVar7;
                auVar20._0_8_ = *plVar7;
                if (uVar14 < uVar15) {
                  plStack_138 = plVar7;
                  uVar5 = runtime_growslice(1,&DAT_0194e220);
                  auVar20._8_8_ = plStack_138;
                  auVar20._0_8_ = uVar5;
                  plStack_138[2] = uVar14;
                  if (DAT_02e5e450 != 0) {
                    puVar6 = (undefined *)*plStack_138;
                    auVar20 = runtime_gcWriteBarrier2();
                    *in_R11 = auVar20._0_8_;
                    in_R11[1] = puVar6;
                  }
                  *auVar20._8_8_ = auVar20._0_8_;
                }
                lVar13 = auVar20._0_8_;
                *(ulong *)(auVar20._8_8_ + 8) = uVar15;
                lVar12 = lVar12 * 0x10;
                *(long *)(lVar13 + 8 + lVar12) = lVar3;
                if (DAT_02e5e450 != 0) {
                  puVar6 = *(undefined **)(lVar13 + lVar12);
                  runtime_gcWriteBarrier2();
                  *in_R11 = puStack_1c8;
                  in_R11[1] = puVar6;
                  lVar13 = extraout_RDX_00;
                }
                *(undefined **)(lVar13 + lVar12) = puStack_1c8;
                plVar7 = plStack_120 + 2;
                uVar14 = uStack_230 - 1;
              }
LAB_0139dc4a:
              runtime_mapIterNext();
            }
            github_com_gogf_gf_v2_net_ghttp_internal_response_Writer_WriteHeader();
            plStack_10 = (long *)runtime_newobject();
            ppuStack_208 = *(undefined ***)(puStack_1b0 + 0x10);
            plStack_120 = (long *)runtime_makeslice();
            do {
              plVar7 = plStack_120;
              uVar14 = (**(code **)(*(long *)(puStack_1b0 + 0x40) + 0x20))
                                 (0x20000,*(code **)(*(long *)(puStack_1b0 + 0x40) + 0x20),
                                  *(undefined8 *)(puStack_1b0 + 0x48));
              if (0 < (long)uVar14) {
                if (0x20000 < uVar14) {
LAB_0139dfb0:
                    /* WARNING: Subroutine does not return */
                  runtime_panicSliceAcap();
                }
                uStack_280 = uVar14;
                github_com_gogf_gf_v2_net_ghttp_internal_response_Writer_Write(0x20000);
                uVar14 = (ulong)DAT_01f4f430;
                do {
                  lVar3 = (uVar14 & *(ulong *)PTR_DAT_02de5920) * 0x10;
                  if (*(undefined **)(PTR_DAT_02de5920 + lVar3 + 8) == &DAT_01b25160) {
                    lVar3 = *(long *)(PTR_DAT_02de5920 + lVar3 + 0x10);
                    goto LAB_0139dd8e;
                  }
                  uVar14 = uVar14 + 1;
                } while (*(undefined **)(PTR_DAT_02de5920 + lVar3 + 8) != (undefined *)0x0);
                lVar3 = runtime_typeAssert();
LAB_0139dd8e:
                if (lVar3 != 0) {
                  (**(code **)(lVar3 + 0x18))();
                }
                if (399 < (long)ppuStack_208) {
                  plVar16 = plStack_10;
                  if ((long *)*plStack_10 == (long *)0x0) {
                    if (DAT_02e5e450 != 0) {
                      puVar6 = (undefined *)*plStack_10;
                      runtime_gcWriteBarrier2();
                      *in_R11 = (undefined *)plVar16;
                      in_R11[1] = puVar6;
                    }
                    *plVar16 = (long)plVar16;
                  }
                  else if (plStack_10 != (long *)*plStack_10) {
                    runtime_gopanic();
                    goto LAB_0139dfb0;
                  }
                  uVar15 = plVar16[3];
                  uStack_230 = plVar16[2];
                  uVar14 = uStack_230 + uStack_280;
                  ppuVar17 = (undefined **)plVar16[1];
                  if (uVar15 < uVar14) {
                    ppuVar17 = (undefined **)runtime_growslice(uStack_280,&DAT_0194e2a0);
                  }
                  uStack_238 = uVar14;
                  uStack_230 = uVar15;
                  ppuStack_108 = ppuVar17;
                  runtime_memmove();
                  plStack_10[2] = uStack_238;
                  plStack_10[3] = uStack_230;
                  plVar16 = plStack_10;
                  if (DAT_02e5e450 != 0) {
                    runtime_gcWriteBarrier2();
                    *in_R11 = (undefined *)ppuStack_108;
                    in_R11[1] = extraout_RDX;
                  }
                  plVar16[1] = (long)ppuStack_108;
                }
              }
              if (plVar7 != (long *)0x0) {
                puVar9 = (undefined8 *)runtime_newobject();
                *puVar9 = &LAB_0139e660;
                *(bool *)(puVar9 + 1) = 399 < (long)ppuStack_208;
                if (DAT_02e5e450 != 0) {
                  puVar9 = (undefined8 *)runtime_gcWriteBarrier3();
                  *in_R11 = (undefined *)ppuStack_150;
                  in_R11[1] = puStack_1b0;
                  in_R11[2] = (undefined *)plStack_10;
                }
                puVar9[2] = ppuStack_150;
                puVar9[3] = puStack_1b0;
                puVar9[4] = plStack_10;
                runtime_newproc();
                runtime_deferreturn();
                return;
              }
            } while( true );
          }
          (*(code *)*ppuStack_1a8)();
          (*(code *)*ppuStack_1b8)();
          ppuVar17 = ppuStack_210;
          ppuVar8 = ppuStack_108;
        }
      }
      else {
        ppuStack_108 = ppuVar8;
        ppuStack_210 = ppuVar17;
        uStack_1f0 = github_com_gogf_gf_v2_frame_gins_Log();
        puStack_38 = (undefined *)runtime_convT64();
        puStack_40 = (undefined8 *)&DAT_0194e420;
        if (ppuStack_210 == (undefined **)0x0) {
          ppuStack_30 = (undefined **)0x0;
        }
        else {
          ppuStack_30 = (undefined **)ppuStack_210[1];
        }
        ppuStack_28 = ppuStack_108;
        github_com_gogf_gf_v2_os_glog_Logger_Errorf(&DAT_01c81833,0x2c,ppuStack_108,ppuStack_170,&puStack_40,2);
        (*(code *)*ppuStack_1a8)();
        in_R11 = (undefined **)*ppuStack_1b8;
        (*(code *)in_R11)();
        ppuVar17 = ppuStack_210;
        ppuVar8 = ppuStack_108;
      }
    }
    else {
      if (puStack_288 == (undefined *)0x0) goto LAB_0139e140;
      uStack_f0 = uStack_1c0;
      ppuStack_e8 = ppuVar2;
      internal_sync_HashTrieMap[go_shape_interface {},go_shape_interface {}]_LoadAndDelete(&uStack_f0);
      ppuVar17 = ppuStack_278;
      ppuVar8 = ppuStack_190;
    }
    lVar3 = lStack_258 + 1;
  } while( true );
}




// === claudeapi.checkSessionKey @ 0x1394f00 ===

undefined **
claudeapi_checkSessionKey(long param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4)

{
  char cVar1;
  undefined8 *puVar2;
  ulong *puVar3;
  long lVar4;
  long *plVar5;
  undefined **ppuVar6;
  undefined8 uVar7;
  undefined8 uVar8;
  undefined8 uVar9;
  ulong *puVar10;
  undefined *puVar11;
  undefined8 uVar12;
  undefined8 extraout_RDX;
  ulong uVar13;
  ulong uVar14;
  undefined8 extraout_RDX_00;
  undefined8 extraout_RDX_01;
  long extraout_RDX_02;
  long extraout_RDX_03;
  long extraout_RDX_04;
  long unaff_RBX;
  undefined *puVar15;
  long lVar16;
  undefined *puVar17;
  undefined8 uVar18;
  ulong uVar19;
  ulong uVar20;
  ulong *puVar21;
  undefined1 (*in_R11) [16];
  long unaff_R14;
  undefined1 auVar22 [16];
  undefined1 auVar23 [16];
  undefined1 auVar24 [16];
  undefined1 auVar25 [16];
  undefined1 auVar26 [16];
  long lStack0000000000000010;
  undefined8 uStack0000000000000018;
  long lStack0000000000000020;
  undefined1 auStack_1d8 [32];
  undefined8 uStack_1b8;
  undefined8 uStack_1b0;
  undefined1 *puStack_1a8;
  undefined *puStack_1a0;
  long lStack_198;
  undefined *puStack_190;
  undefined *puStack_188;
  undefined *puStack_180;
  undefined *puStack_178;
  undefined *puStack_170;
  long lStack_168;
  undefined *puStack_160;
  undefined *puStack_158;
  undefined8 uStack_150;
  long lStack_148;
  long lStack_140;
  long lStack_138;
  undefined8 uStack_130;
  undefined8 uStack_128;
  undefined8 uStack_120;
  undefined8 uStack_118;
  undefined8 *puStack_110;
  undefined8 *puStack_108;
  long lStack_100;
  undefined8 uStack_f8;
  undefined8 uStack_f0;
  undefined8 uStack_e8;
  undefined8 uStack_e0;
  long lStack_d8;
  long lStack_d0;
  undefined8 uStack_c8;
  ulong *puStack_c0;
  ulong *puStack_b8;
  long lStack_b0;
  undefined8 uStack_a8;
  undefined8 uStack_a0;
  undefined8 uStack_98;
  undefined8 uStack_90;
  undefined8 *puStack_88;
  undefined8 uStack_80;
  undefined8 uStack_78;
  undefined8 uStack_70;
  long lStack_68;
  undefined8 *puStack_50;
  long lStack_48;
  long lStack_30;
  long lStack_28;
  undefined8 uStack_20;
  undefined8 *puStack_18;
  undefined8 uStack_10;
  
  uStack0000000000000018 = param_4;
  lStack_198 = unaff_RBX;
  lStack0000000000000020 = param_1;
  while (lStack0000000000000010 = lStack_198, &puStack_190 <= *(undefined ***)(unaff_R14 + 0x10)) {
    runtime_morestack_noctxt();
    lStack_198 = lStack0000000000000010;
  }
  uStack_f0 = kiro2api_internal_logic_claudeapi_sClaudeApi_getProxyURL();
  auVar22 = kiro2api_internal_logic_claudeapi_sClaudeApi_getAccountInfo(*(undefined8 *)(lStack0000000000000020 + 0x38),
                         *(undefined8 *)(lStack0000000000000020 + 0x40),lStack0000000000000020,
                         uStack0000000000000018,uStack_f0,lStack_198);
  lStack_100 = auVar22._0_8_;
  if (*(char *)(lStack_100 + 8) == '\0') {
    ppuVar6 = (undefined **)kiro2api_internal_proxy_Response_Error();
    return ppuVar6;
  }
  github_com_gogf_gf_v2_encoding_gjson_Json_Get(0,0,auVar22._8_8_,0xd,0);
  uStack_e0 = github_com_gogf_gf_v2_container_gvar_Var_String();
  puStack_188 = &DAT_01c49c69;
  github_com_gogf_gf_v2_encoding_gjson_Json_Get(0,0,lStack_100,4,0);
  uStack_120 = github_com_gogf_gf_v2_container_gvar_Var_String();
  uStack_1b0 = 0x1c397be;
  puVar15 = &DAT_01c463d3;
  github_com_gogf_gf_v2_encoding_gjson_Json_Get(0);
  puVar2 = (undefined8 *)github_com_gogf_gf_v2_container_gvar_Var_Interfaces();
  uStack_e8 = 0;
  puStack_190 = (undefined *)0x0;
  do {
    if ((long)puVar15 < 1) {
      if ((*(long *)(lStack0000000000000020 + 0xb0) == 0) ||
         ((*(long *)(lStack0000000000000020 + 0xb0) == 4 &&
          (**(int **)(lStack0000000000000020 + 0xa8) == 0x65657266)))) {
        puVar2 = (undefined8 *)runtime_newobject();
        puVar2[1] = 0x41;
        *puVar2 = &DAT_01c9719a;
        return &PTR_DAT_01f42e00;
      }
      crypto_rand_Read();
      uStack_118 = encoding_base64_Encoding_EncodeToString(0x20);
      puStack_1a8 = auStack_1d8;
      uStack_128 = github_com_nirasan_go-oauth-pkce-code-verifier_CreateCodeVerifierWithLength();
      lStack_30 = github_com_imroc_req_v3_Client_Clone();
      lStack_28 = lStack0000000000000010;
      uStack_20 = uStack0000000000000018;
      if (lStack_198 != 0) {
        kiro2api_internal_proxy_Client_SetProxy(*(undefined8 *)(lStack0000000000000020 + 0x38),
                     *(undefined8 *)(lStack0000000000000020 + 0x40));
      }
      lStack_d0 = lStack_30;
      if (*(undefined8 **)(lStack_30 + 0x60) == (undefined8 *)0x0) {
        lStack_140 = 0;
      }
      else {
        puStack_108 = *(undefined8 **)(lStack_30 + 0x60);
        puVar2 = (undefined8 *)runtime_newobject();
        *puVar2 = *puStack_108;
        auVar22._8_8_ = puStack_108[1];
        auVar22._0_8_ = puVar2;
        puVar2 = puStack_108;
        if (DAT_02e5e450 != 0) {
          auVar22 = runtime_gcWriteBarrier1();
          *(long *)*in_R11 = auVar22._8_8_;
        }
        lStack_140 = auVar22._0_8_;
        *(long *)(lStack_140 + 8) = auVar22._8_8_;
        puStack_160 = *(undefined **)(lStack_140 + 0x18);
        uVar19 = *(ulong *)(lStack_140 + 0x20);
        puStack_158 = (undefined *)puVar2[3];
        uVar13 = (long)puStack_160 + (long)puStack_158;
        uVar9 = *(undefined8 *)(lStack_140 + 0x10);
        uStack_90 = puVar2[2];
        if (uVar19 < uVar13) {
          uVar9 = runtime_growslice(puStack_158,&DAT_019ea040);
        }
        lVar16 = uVar13 - (long)puStack_160;
        uVar14 = (long)((long)puStack_160 - uVar19) >> 0x3f;
        in_R11 = (undefined1 (*) [16])((long)puStack_160 << 3 & uVar14);
        puStack_160 = (undefined *)uVar19;
        lVar4 = (long)puStack_158;
        puStack_158 = (undefined *)uVar13;
        uVar8 = uStack_90;
        uStack_90 = uVar9;
        runtime_typedslicecopy(uVar8,lVar4,uVar14,lVar16);
        *(undefined **)(lStack_140 + 0x18) = puStack_158;
        *(undefined **)(lStack_140 + 0x20) = puStack_160;
        lVar4 = lStack_140;
        if (DAT_02e5e450 != 0) {
          runtime_gcWriteBarrier2();
          *(undefined8 *)*in_R11 = uStack_90;
          *(undefined8 *)(*in_R11 + 8) = extraout_RDX;
        }
        *(undefined8 *)(lVar4 + 0x10) = uStack_90;
        puStack_158 = *(undefined **)(lVar4 + 0x30);
        puVar11 = *(undefined **)(lVar4 + 0x38);
        puStack_160 = (undefined *)puStack_108[6];
        puVar15 = (undefined *)((long)puStack_160 + (long)puStack_158);
        uVar9 = *(undefined8 *)(lVar4 + 0x28);
        uStack_98 = puStack_108[5];
        if (puVar11 < puVar15) {
          uVar9 = runtime_growslice(puStack_160,&DAT_019cbd00);
        }
        lVar16 = (long)puVar15 - (long)puStack_158;
        uVar19 = (long)puStack_158 << 3;
        uVar13 = (long)puStack_158 - (long)puVar11 >> 0x3f;
        lVar4 = (long)puStack_160;
        puStack_160 = puVar11;
        puStack_158 = puVar15;
        uVar8 = uStack_98;
        uStack_98 = uVar9;
        runtime_typedslicecopy(uVar8,lVar4,uVar13,lVar16,uVar19 & uVar13);
        *(undefined **)(lStack_140 + 0x30) = puStack_158;
        *(undefined **)(lStack_140 + 0x38) = puStack_160;
        if (DAT_02e5e450 != 0) {
          uVar9 = *(undefined8 *)(lStack_140 + 0x28);
          runtime_gcWriteBarrier2();
          *(undefined8 *)*in_R11 = uStack_98;
          *(undefined8 *)(*in_R11 + 8) = uVar9;
        }
        *(undefined8 *)(lStack_140 + 0x28) = uStack_98;
      }
      lStack_138 = runtime_newobject();
      if (DAT_02e5e450 != 0) {
        lStack_138 = runtime_gcWriteBarrier2();
        *(long *)*in_R11 = lStack_d0;
        *(long *)(*in_R11 + 8) = lStack_140;
      }
      auVar23._8_8_ = uStack_20;
      auVar23._0_8_ = lStack_138;
      *(long *)(lStack_138 + 0xf8) = lStack_d0;
      *(long *)(lStack_138 + 0x130) = lStack_140;
      if (lStack_28 != 0) {
        *(long *)(lStack_138 + 0x160) = lStack_28;
        if (DAT_02e5e450 != 0) {
          auVar23 = runtime_gcWriteBarrier1();
          *(long *)*in_R11 = auVar23._8_8_;
        }
        lStack_138 = auVar23._0_8_;
        *(long *)(lStack_138 + 0x168) = auVar23._8_8_;
      }
      puStack_50 = (undefined8 *)0x0;
      lStack_48 = lStack_138;
      lVar4 = runtime_newobject();
      auVar24._8_8_ = PTR_DAT_02de13f0;
      auVar24._0_8_ = lVar4;
      *(undefined8 *)(lVar4 + 8) = DAT_02de13f8;
      if (DAT_02e5e450 != 0) {
        auVar24 = runtime_gcWriteBarrier1();
        *(long *)*in_R11 = auVar24._8_8_;
      }
      puVar2 = auVar24._0_8_;
      *puVar2 = auVar24._8_8_;
      uVar9 = *(undefined8 *)(lStack0000000000000020 + 0x38);
      puVar2[3] = *(undefined8 *)(lStack0000000000000020 + 0x40);
      if (DAT_02e5e450 != 0) {
        puVar2 = (undefined8 *)runtime_gcWriteBarrier1();
        *(undefined8 *)*in_R11 = uVar9;
      }
      puVar2[2] = uVar9;
      puStack_158 = *(undefined **)(lStack_138 + 0x40);
      uVar13 = (long)puStack_158 + 1;
      uVar19 = *(ulong *)(lStack_138 + 0x48);
      uStack_a0 = *(undefined8 *)(lStack_138 + 0x38);
      puStack_50 = puVar2;
      if (uVar19 < uVar13) {
        uStack_a0 = runtime_growslice(1,&DAT_019f9d40);
      }
      lVar16 = (long)puStack_158 - uVar19;
      lVar4 = uVar13 - (long)puStack_158;
      uVar14 = (long)puStack_158 << 3;
      puStack_160 = (undefined *)uVar19;
      puStack_158 = (undefined *)uVar13;
      runtime_typedslicecopy(&puStack_50,1,uVar14 & lVar16 >> 0x3f,lVar4);
      *(undefined **)(lStack_138 + 0x40) = puStack_158;
      *(undefined **)(lStack_138 + 0x48) = puStack_160;
      lVar4 = lStack_138;
      if (DAT_02e5e450 != 0) {
        uVar9 = runtime_gcWriteBarrier2();
        *(undefined8 *)*in_R11 = uStack_a0;
        *(undefined8 *)(*in_R11 + 8) = uVar9;
      }
      *(undefined8 *)(lVar4 + 0x38) = uStack_a0;
      uStack_a8 = runtime_makemap_small();
      puVar2 = (undefined8 *)runtime_mapassign_faststr(0xd);
      *puVar2 = &DAT_0194e220;
      if (DAT_02e5e450 != 0) {
        auVar22 = runtime_gcWriteBarrier1();
        puVar2 = auVar22._0_8_;
        *(long *)*in_R11 = auVar22._8_8_;
      }
      puVar2[1] = &PTR_DAT_01f3a3f0;
      puStack_88 = (undefined8 *)runtime_convTstring();
      puVar2 = (undefined8 *)runtime_mapassign_faststr(9);
      *puVar2 = &DAT_0194e220;
      if (DAT_02e5e450 != 0) {
        auVar22 = runtime_gcWriteBarrier2();
        puVar2 = auVar22._0_8_;
        *(undefined8 **)*in_R11 = puStack_88;
        *(long *)(*in_R11 + 8) = auVar22._8_8_;
      }
      puVar2[1] = puStack_88;
      puStack_88 = (undefined8 *)runtime_convTstring();
      auVar22 = runtime_mapassign_faststr(0x11);
      *auVar22._0_8_ = &DAT_0194e220;
      if (DAT_02e5e450 != 0) {
        auVar22 = runtime_gcWriteBarrier2();
        *(undefined8 **)*in_R11 = puStack_88;
        *(long *)(*in_R11 + 8) = auVar22._8_8_;
      }
      *(undefined8 **)(auVar22._0_8_ + 8) = puStack_88;
      puVar2 = (undefined8 *)runtime_mapassign_faststr(0xc,puStack_88,auVar22._8_8_,&DAT_01c47e6c);
      *puVar2 = &DAT_0194e220;
      if (DAT_02e5e450 != 0) {
        uVar9 = puVar2[1];
        puVar2 = (undefined8 *)runtime_gcWriteBarrier1();
        *(undefined8 *)*in_R11 = uVar9;
      }
      puVar2[1] = &PTR_DAT_01f3a400;
      puVar2 = (undefined8 *)runtime_mapassign_faststr(5);
      *puVar2 = &DAT_0194e220;
      if (DAT_02e5e450 != 0) {
        uVar9 = puVar2[1];
        puVar2 = (undefined8 *)runtime_gcWriteBarrier1();
        *(undefined8 *)*in_R11 = uVar9;
      }
      puVar2[1] = &PTR_DAT_01f3a410;
      puStack_88 = (undefined8 *)runtime_convTstring();
      puVar2 = (undefined8 *)runtime_mapassign_faststr(5);
      *puVar2 = &DAT_0194e220;
      if (DAT_02e5e450 != 0) {
        auVar22 = runtime_gcWriteBarrier2();
        puVar2 = auVar22._0_8_;
        *(undefined8 **)*in_R11 = puStack_88;
        *(long *)(*in_R11 + 8) = auVar22._8_8_;
      }
      puVar2[1] = puStack_88;
      github_com_nirasan_go-oauth-pkce-code-verifier_CodeVerifier_CodeChallengeS256();
      puStack_88 = (undefined8 *)runtime_convTstring();
      auVar22 = runtime_mapassign_faststr(0xe);
      *auVar22._0_8_ = &DAT_0194e220;
      if (DAT_02e5e450 != 0) {
        auVar22 = runtime_gcWriteBarrier2();
        *(undefined8 **)*in_R11 = puStack_88;
        *(long *)(*in_R11 + 8) = auVar22._8_8_;
      }
      *(undefined8 **)(auVar22._0_8_ + 8) = puStack_88;
      puVar2 = (undefined8 *)runtime_mapassign_faststr(0x15,puStack_88,auVar22._8_8_,&DAT_01c58df6);
      *puVar2 = &DAT_0194e220;
      if (DAT_02e5e450 != 0) {
        uVar9 = puVar2[1];
        puVar2 = (undefined8 *)runtime_gcWriteBarrier1();
        *(undefined8 *)*in_R11 = uVar9;
      }
      puVar2[1] = &PTR_DAT_01f3a420;
      github_com_imroc_req_v3_Request_SetBody();
      uStack_10 = runtime_convTstring();
      puStack_18 = &DAT_0194e220;
      auVar22 = fmt_Sprintf(1,1,&DAT_0194e220,&puStack_18);
      auVar22 = kiro2api_internal_proxy_Request_Fetch(auVar22._0_8_,0x16,auVar22._8_8_,4);
      if (*(char *)(auVar22._0_8_ + 8) != '\0') {
        github_com_gogf_gf_v2_encoding_gjson_Json_Get(0,0,auVar22._8_8_,0xc);
        github_com_gogf_gf_v2_container_gvar_Var_String();
        net_url_Parse();
        net_url_URL_Query();
        plVar5 = (long *)runtime_mapaccess1_faststr(4);
        if (plVar5[1] == 0) {
          uStack_1b8 = 0;
          uStack_150 = 0;
        }
        else {
          uStack_1b8 = ((undefined8 *)*plVar5)[1];
          uStack_150 = *(undefined8 *)*plVar5;
        }
        lStack_d8 = lStack_30;
        if (*(undefined8 **)(lStack_30 + 0x60) == (undefined8 *)0x0) {
          lStack_148 = 0;
        }
        else {
          puStack_110 = *(undefined8 **)(lStack_30 + 0x60);
          puVar2 = (undefined8 *)runtime_newobject();
          *puVar2 = *puStack_110;
          auVar25._8_8_ = puStack_110[1];
          auVar25._0_8_ = puVar2;
          puVar2 = puStack_110;
          if (DAT_02e5e450 != 0) {
            auVar25 = runtime_gcWriteBarrier1();
            *(long *)*in_R11 = auVar25._8_8_;
          }
          lStack_148 = auVar25._0_8_;
          *(long *)(lStack_148 + 8) = auVar25._8_8_;
          puStack_160 = *(undefined **)(lStack_148 + 0x18);
          uVar19 = *(ulong *)(lStack_148 + 0x20);
          puStack_158 = (undefined *)puVar2[3];
          uVar13 = (long)puStack_160 + (long)puStack_158;
          uVar9 = *(undefined8 *)(lStack_148 + 0x10);
          uStack_90 = puVar2[2];
          if (uVar19 < uVar13) {
            uVar9 = runtime_growslice(puStack_158,&DAT_019ea040);
          }
          lVar16 = uVar13 - (long)puStack_160;
          uVar14 = (long)((long)puStack_160 - uVar19) >> 0x3f;
          in_R11 = (undefined1 (*) [16])((long)puStack_160 << 3 & uVar14);
          puStack_160 = (undefined *)uVar13;
          lVar4 = (long)puStack_158;
          puStack_158 = (undefined *)uVar19;
          uVar8 = uStack_90;
          uStack_90 = uVar9;
          runtime_typedslicecopy(uVar8,lVar4,uVar14,lVar16);
          *(undefined **)(lStack_148 + 0x18) = puStack_160;
          *(undefined **)(lStack_148 + 0x20) = puStack_158;
          lVar4 = lStack_148;
          if (DAT_02e5e450 != 0) {
            runtime_gcWriteBarrier2();
            *(undefined8 *)*in_R11 = uStack_90;
            *(undefined8 *)(*in_R11 + 8) = extraout_RDX_00;
          }
          *(undefined8 *)(lVar4 + 0x10) = uStack_90;
          puStack_160 = *(undefined **)(lVar4 + 0x30);
          uVar19 = *(ulong *)(lVar4 + 0x38);
          puStack_158 = (undefined *)puStack_110[6];
          uVar13 = (long)puStack_160 + (long)puStack_158;
          uVar9 = *(undefined8 *)(lVar4 + 0x28);
          uStack_98 = puStack_110[5];
          if (uVar19 < uVar13) {
            uVar9 = runtime_growslice(puStack_158,&DAT_019cbd00);
          }
          lVar16 = uVar13 - (long)puStack_160;
          uVar20 = (long)puStack_160 << 3;
          uVar14 = (long)((long)puStack_160 - uVar19) >> 0x3f;
          puStack_160 = (undefined *)uVar13;
          lVar4 = (long)puStack_158;
          puStack_158 = (undefined *)uVar19;
          uVar8 = uStack_98;
          uStack_98 = uVar9;
          runtime_typedslicecopy(uVar8,lVar4,uVar14,lVar16,uVar20 & uVar14);
          *(undefined **)(lStack_148 + 0x30) = puStack_160;
          *(undefined **)(lStack_148 + 0x38) = puStack_158;
          if (DAT_02e5e450 != 0) {
            uVar9 = *(undefined8 *)(lStack_148 + 0x28);
            runtime_gcWriteBarrier2();
            *(undefined8 *)*in_R11 = uStack_98;
            *(undefined8 *)(*in_R11 + 8) = uVar9;
          }
          *(undefined8 *)(lStack_148 + 0x28) = uStack_98;
        }
        lStack_68 = runtime_newobject();
        if (DAT_02e5e450 != 0) {
          lStack_68 = runtime_gcWriteBarrier2();
          *(long *)*in_R11 = lStack_d8;
          *(long *)(*in_R11 + 8) = lStack_148;
        }
        auVar26._8_8_ = uStack_20;
        auVar26._0_8_ = lStack_68;
        *(long *)(lStack_68 + 0xf8) = lStack_d8;
        *(long *)(lStack_68 + 0x130) = lStack_148;
        if (lStack_28 != 0) {
          *(long *)(lStack_68 + 0x160) = lStack_28;
          if (DAT_02e5e450 != 0) {
            auVar26 = runtime_gcWriteBarrier1();
            *(long *)*in_R11 = auVar26._8_8_;
          }
          lStack_68 = auVar26._0_8_;
          *(long *)(lStack_68 + 0x168) = auVar26._8_8_;
        }
        uStack_a8 = runtime_makemap_small();
        puStack_88 = (undefined8 *)runtime_convTstring();
        puVar2 = (undefined8 *)runtime_mapassign_faststr(9);
        *puVar2 = &DAT_0194e220;
        if (DAT_02e5e450 != 0) {
          auVar22 = runtime_gcWriteBarrier2();
          puVar2 = auVar22._0_8_;
          *(undefined8 **)*in_R11 = puStack_88;
          *(long *)(*in_R11 + 8) = auVar22._8_8_;
        }
        puVar2[1] = puStack_88;
        puStack_88 = (undefined8 *)runtime_convTstring();
        puVar2 = (undefined8 *)runtime_mapassign_faststr(4);
        *puVar2 = &DAT_0194e220;
        if (DAT_02e5e450 != 0) {
          auVar22 = runtime_gcWriteBarrier2();
          puVar2 = auVar22._0_8_;
          *(undefined8 **)*in_R11 = puStack_88;
          *(long *)(*in_R11 + 8) = auVar22._8_8_;
        }
        puVar2[1] = puStack_88;
        puStack_88 = (undefined8 *)runtime_convTstring();
        auVar22 = runtime_mapassign_faststr(0xd);
        *auVar22._0_8_ = &DAT_0194e220;
        if (DAT_02e5e450 != 0) {
          auVar22 = runtime_gcWriteBarrier2();
          *(undefined8 **)*in_R11 = puStack_88;
          *(long *)(*in_R11 + 8) = auVar22._8_8_;
        }
        *(undefined8 **)(auVar22._0_8_ + 8) = puStack_88;
        puVar2 = (undefined8 *)runtime_mapassign_faststr(10,puStack_88,auVar22._8_8_,&DAT_01c440e9);
        *puVar2 = &DAT_0194e220;
        if (DAT_02e5e450 != 0) {
          uVar9 = puVar2[1];
          puVar2 = (undefined8 *)runtime_gcWriteBarrier1();
          *(undefined8 *)*in_R11 = uVar9;
        }
        puVar2[1] = &PTR_DAT_01f3a430;
        puVar2 = (undefined8 *)runtime_mapassign_faststr(0xc);
        *puVar2 = &DAT_0194e220;
        if (DAT_02e5e450 != 0) {
          uVar9 = puVar2[1];
          puVar2 = (undefined8 *)runtime_gcWriteBarrier1();
          *(undefined8 *)*in_R11 = uVar9;
        }
        puVar2[1] = &PTR_DAT_01f3a400;
        puStack_88 = (undefined8 *)runtime_convTstring();
        puVar2 = (undefined8 *)runtime_mapassign_faststr(5);
        *puVar2 = &DAT_0194e220;
        if (DAT_02e5e450 != 0) {
          auVar22 = runtime_gcWriteBarrier2();
          puVar2 = auVar22._0_8_;
          *(undefined8 **)*in_R11 = puStack_88;
          *(long *)(*in_R11 + 8) = auVar22._8_8_;
        }
        puVar2[1] = puStack_88;
        github_com_imroc_req_v3_Request_SetBody();
        auVar22 = kiro2api_internal_proxy_Request_Fetch(&DAT_01c4d5ee,0xf,extraout_RDX_01,4);
        lStack_b0 = auVar22._0_8_;
        if (*(char *)(lStack_b0 + 8) != '\0') {
          github_com_gogf_gf_v2_encoding_gjson_Json_Get(0,0,auVar22._8_8_,0xc,0);
          uStack_c8 = github_com_gogf_gf_v2_container_gvar_Var_String();
          puStack_180 = &DAT_01c47e48;
          github_com_gogf_gf_v2_encoding_gjson_Json_Get(0,0,lStack_b0,0xd,0);
          uStack_f8 = github_com_gogf_gf_v2_container_gvar_Var_String();
          puStack_1a0 = &DAT_01c49a06;
          github_com_gogf_gf_v2_encoding_gjson_Json_Get(0,0,lStack_b0,10,0);
          lVar4 = github_com_gogf_gf_v2_container_gvar_Var_Int();
          *(undefined **)(lStack0000000000000020 + 0x20) = puStack_180;
          lStack_168 = lVar4 * 1000000000 + -300000000000;
          uVar8 = uStack_f8;
          uVar12 = uStack_e8;
          uVar9 = uStack_e0;
          uVar18 = uStack_c8;
          lVar4 = lStack0000000000000020;
          if (DAT_02e5e450 != 0) {
            uVar8 = *(undefined8 *)(lStack0000000000000020 + 0x68);
            uVar12 = *(undefined8 *)(lStack0000000000000020 + 0x88);
            uVar18 = *(undefined8 *)(lStack0000000000000020 + 8);
            uVar7 = runtime_gcWriteBarrier8();
            uVar9 = uStack_e0;
            *(undefined8 *)*in_R11 = uStack_c8;
            *(undefined8 *)(*in_R11 + 8) = uVar7;
            *(undefined8 *)in_R11[1] = uStack_f8;
            *(undefined8 *)(in_R11[1] + 8) = uVar8;
            *(undefined8 *)in_R11[2] = uStack_e8;
            *(undefined8 *)(in_R11[2] + 8) = uVar12;
            *(undefined8 *)in_R11[3] = uStack_e0;
            *(undefined8 *)(in_R11[3] + 8) = uVar18;
            uVar7 = *(undefined8 *)(lVar4 + 0x98);
            uVar12 = uStack_e8;
            uVar18 = uStack_c8;
            uVar8 = runtime_gcWriteBarrier2();
            *(undefined8 *)*in_R11 = uStack_120;
            *(undefined8 *)(*in_R11 + 8) = uVar7;
          }
          *(undefined8 *)(lVar4 + 0x18) = uVar18;
          *(undefined **)(lVar4 + 0x70) = puStack_1a0;
          *(undefined8 *)(lVar4 + 0x68) = uVar8;
          *(undefined **)(lVar4 + 0x90) = puStack_190;
          *(undefined8 *)(lVar4 + 0x88) = uVar12;
          *(undefined **)(lVar4 + 0x10) = puStack_188;
          *(undefined8 *)(lVar4 + 8) = uVar9;
          *(undefined8 *)(lVar4 + 0xa0) = uStack_1b0;
          *(undefined8 *)(lVar4 + 0x98) = uStack_120;
          time_Now();
          uStack_80 = time_Time_Add(lStack_168);
          uStack_78 = uVar9;
          uStack_70 = uVar12;
          uStack_10 = runtime_convT();
          puStack_18 = (undefined8 *)&DAT_01bf6dc0;
          uVar9 = github_com_gogf_gf_v2_os_gtime_New();
          lVar4 = lStack0000000000000020;
          if (DAT_02e5e450 != 0) {
            uVar8 = *(undefined8 *)(lStack0000000000000020 + 0xb8);
            auVar22 = runtime_gcWriteBarrier3();
            uVar9 = auVar22._0_8_;
            *in_R11 = auVar22;
            *(undefined8 *)in_R11[1] = uVar8;
          }
          *(undefined8 *)(lVar4 + 0xe0) = uVar9;
          *(undefined8 *)(lVar4 + 0xc0) = 6;
          *(undefined **)(lVar4 + 0xb8) = &DAT_01c3bc33;
          kiro2api_internal_model_ClaudeApiAccount_EncryptAndSetCredentials();
          kiro2api_internal_dao_ClaudeApiAccountDao_UpdateTokenInfo(lStack0000000000000020);
          return (undefined **)0x0;
        }
      }
      ppuVar6 = (undefined **)kiro2api_internal_proxy_Response_Error();
      return ppuVar6;
    }
    puStack_158 = puVar15;
    puStack_88 = puVar2;
    auVar22 = github_com_gogf_gf_v2_encoding_gjson_NewWithTag(4,0,*puVar2,&DAT_01c397a6,0,0);
    uStack_130 = auVar22._0_8_;
    puVar15 = &DAT_01c5fd26;
    github_com_gogf_gf_v2_encoding_gjson_Json_Get(0,0,auVar22._8_8_,0x19);
    puVar3 = (ulong *)github_com_gogf_gf_v2_container_gvar_Var_Strings();
    puVar10 = puVar3;
    while( true ) {
      if ((long)puVar15 < 1) goto LAB_0139503e;
      if ((puVar10[1] == 4) &&
         (in_R11 = (undefined1 (*) [16])*puVar10, *(int *)*in_R11 == 0x74616863)) break;
      puVar10 = puVar10 + 2;
      puVar15 = puVar15 + -1;
    }
    puStack_160 = &DAT_01c5fd26;
    puVar15 = &DAT_01c5fd26;
    puStack_170 = &DAT_01c5fd26;
    puVar10 = puVar3;
    puStack_b8 = puVar3;
    while ((puVar11 = puStack_170, puVar17 = puVar15, puVar21 = puVar3, 0 < (long)puStack_170 &&
           ((puVar10[1] != 10 ||
            (puStack_c0 = puVar10, cVar1 = runtime_memequal(), puVar15 = puStack_160,
            puVar11 = puStack_170, puVar3 = puStack_b8, puVar17 = puStack_160, puVar10 = puStack_c0,
            puVar21 = puStack_b8, cVar1 == '\0'))))) {
      puVar10 = puVar10 + 2;
      puStack_170 = puStack_170 + -1;
    }
    while ((puStack_178 = puVar15, puVar15 = puStack_178, 0 < (long)puStack_178 &&
           ((puVar3[1] != 10 ||
            (puStack_c0 = puVar3, cVar1 = runtime_memequal(), puVar15 = puStack_178,
            puVar11 = puStack_170, puVar3 = puStack_c0, puVar17 = puStack_160, puVar21 = puStack_b8,
            cVar1 == '\0'))))) {
      puVar15 = puStack_178 + -1;
      puVar3 = puVar3 + 2;
    }
    while ((0 < (long)puVar17 &&
           ((puVar21[1] != 5 ||
            (puStack_160 = puVar17, puStack_c0 = puVar21, cVar1 = runtime_memequal(),
            puVar15 = puStack_178, puVar11 = puStack_170, puVar17 = puStack_160,
            puVar21 = puStack_c0, cVar1 == '\0'))))) {
      puVar17 = puVar17 + -1;
      puVar21 = puVar21 + 2;
    }
    lVar4 = lStack0000000000000020;
    if ((long)puVar11 < 1) {
      if (0 < (long)puVar15) {
        *(undefined8 *)(lStack0000000000000020 + 0xb0) = 3;
        if (DAT_02e5e450 != 0) {
          uVar9 = *(undefined8 *)(lStack0000000000000020 + 0xa8);
          runtime_gcWriteBarrier1();
          *(undefined8 *)*in_R11 = uVar9;
          lVar4 = extraout_RDX_03;
        }
        *(undefined **)(lVar4 + 0xa8) = &DAT_01c38f02;
        goto LAB_013965c1;
      }
      if (0 < (long)puVar17) {
        *(undefined8 *)(lStack0000000000000020 + 0xb0) = 4;
        if (DAT_02e5e450 != 0) {
          uVar9 = *(undefined8 *)(lStack0000000000000020 + 0xa8);
          runtime_gcWriteBarrier1();
          *(undefined8 *)*in_R11 = uVar9;
          lVar4 = extraout_RDX_02;
        }
        *(undefined **)(lVar4 + 0xa8) = &DAT_01c398d2;
        goto LAB_013965c1;
      }
    }
    else {
      *(undefined8 *)(lStack0000000000000020 + 0xb0) = 3;
      if (DAT_02e5e450 != 0) {
        uVar9 = *(undefined8 *)(lStack0000000000000020 + 0xa8);
        runtime_gcWriteBarrier1();
        *(undefined8 *)*in_R11 = uVar9;
        lVar4 = extraout_RDX_04;
      }
      *(undefined **)(lVar4 + 0xa8) = &DAT_01c38db8;
LAB_013965c1:
      github_com_gogf_gf_v2_encoding_gjson_Json_Get(0,0,lVar4,0x11);
      uStack_e8 = github_com_gogf_gf_v2_container_gvar_Var_String();
      puStack_190 = &DAT_01c51180;
    }
LAB_0139503e:
    puVar2 = puStack_88 + 2;
    puVar15 = puStack_158 + -1;
  } while( true );
}




// === claudeapi.injectClaudeCodeContext @ 0x13934c0 ===

undefined8
claudeapi_injectClaudeCodeContext
          (long param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4)

{
  ulong uVar1;
  char cVar2;
  byte bVar3;
  undefined8 in_RAX;
  long lVar4;
  undefined8 *puVar5;
  undefined8 *puVar6;
  undefined8 uVar7;
  long lVar8;
  undefined8 *extraout_RDX;
  ulong uVar9;
  ulong uVar10;
  undefined8 *in_R11;
  undefined8 *puVar11;
  long unaff_R14;
  undefined1 auVar12 [16];
  undefined8 uStack0000000000000008;
  undefined8 uStack0000000000000018;
  long lStack0000000000000020;
  byte abStack_152 [33];
  char cStack_131;
  undefined1 auStack_118 [40];
  long lStack_f0;
  long lStack_e8;
  ulong uStack_e0;
  ulong uStack_d8;
  ulong uStack_d0;
  undefined8 *puStack_c8;
  ulong uStack_c0;
  long lStack_b8;
  undefined8 uStack_b0;
  undefined8 uStack_a8;
  undefined8 *puStack_a0;
  long lStack_98;
  undefined8 uStack_90;
  undefined *puStack_88;
  long lStack_80;
  undefined *puStack_78;
  long lStack_70;
  undefined8 uStack_68;
  undefined8 *puStack_60;
  undefined8 uStack_58;
  undefined8 *puStack_50;
  undefined8 uStack_48;
  undefined8 uStack_40;
  char *pcStack_38;
  undefined8 uStack_30;
  undefined *puStack_28;
  undefined8 uStack_20;
  undefined *puStack_18;
  undefined8 *puStack_10;
  
  uStack0000000000000008 = in_RAX;
  uStack0000000000000018 = param_4;
  lStack0000000000000020 = param_1;
  while (auStack_118 <= *(undefined1 **)(unaff_R14 + 0x10)) {
    runtime_morestack_noctxt();
  }
  auVar12 = runtime_newobject();
  puStack_10 = auVar12._0_8_;
  lVar4 = encoding_json_Unmarshal(&DAT_01928320,puStack_10,auVar12._8_8_,uStack0000000000000018);
  if (lVar4 != 0) {
    return uStack0000000000000008;
  }
  uVar7 = *puStack_10;
  puVar5 = (undefined8 *)runtime_mapaccess2_faststr();
  if ((char)uVar7 == '\0') {
    uVar9 = 0;
    puVar5 = (undefined8 *)0x0;
    bVar3 = '\0';
  }
  else {
    puVar6 = (undefined8 *)*puVar5;
    if (puVar6 == (undefined8 *)0x0) {
      bVar3 = '\0';
      uVar9 = 0;
      puVar5 = (undefined8 *)0x0;
    }
    else {
      puVar11 = (undefined8 *)puVar5[1];
      if (*(int *)(puVar6 + 2) == -0xd99de8a) {
        if (puVar6 == &DAT_0192e960) {
          puVar6 = (undefined8 *)*puVar11;
          bVar3 = '\0';
          uVar10 = 0;
          puVar5 = (undefined8 *)0x0;
          uVar9 = 0;
          for (lVar4 = puVar11[1]; 0 < lVar4; lVar4 = lVar4 + -1) {
            puVar11 = &DAT_01a233a0;
            if ((undefined8 *)*puVar6 == &DAT_01a233a0) {
              puStack_78 = PTR_DAT_02de02b0;
              lStack_70 = DAT_02de02b8;
              abStack_152[0x20] = bVar3;
              uStack_d8 = uVar10;
              puStack_c8 = (undefined8 *)*puVar6;
              uStack_c0 = uVar9;
              lStack_b8 = lVar4;
              uStack_90 = puVar6[1];
              uStack_68 = puVar6[1];
              puStack_60 = puVar5;
              puStack_50 = puVar6;
              puVar5 = (undefined8 *)runtime_mapaccess1_faststr(4,DAT_02de02b8,PTR_DAT_02de02b0,&DAT_01c397b2);
              if ((undefined8 *)*puVar5 == &DAT_0194e220) {
                cVar2 = runtime_efaceeq();
              }
              else {
                cVar2 = '\0';
              }
              if (cVar2 == '\0') {
                puStack_88 = PTR_DAT_02de02c0;
                lStack_80 = DAT_02de02c8;
                puVar5 = (undefined8 *)runtime_mapaccess1_faststr(4,DAT_02de02c8,PTR_DAT_02de02c0,&DAT_01c397b2);
                if ((undefined8 *)*puVar5 == &DAT_0194e220) {
                  cVar2 = runtime_efaceeq();
                }
                else {
                  cVar2 = '\0';
                }
                bVar3 = abStack_152[0x20];
                if (cVar2 != '\0') goto LAB_01394104;
              }
              else {
LAB_01394104:
                bVar3 = '\x01';
              }
              uVar1 = uStack_c0;
              uVar9 = uStack_c0 + 1;
              uVar10 = uStack_d8;
              puVar5 = puStack_60;
              if (uStack_d8 < uVar9) {
                cStack_131 = bVar3;
                puVar5 = (undefined8 *)runtime_growslice(1,&DAT_019b39a0,&DAT_0194e220);
                bVar3 = cStack_131;
              }
              lVar4 = uVar1 * 0x10;
              puVar5[uVar1 * 2] = puStack_c8;
              if (DAT_02e5e450 != 0) {
                uVar7 = puVar5[uVar1 * 2 + 1];
                bVar3 = runtime_gcWriteBarrier2();
                *puVar11 = uStack_68;
                puVar11[1] = uVar7;
              }
              *(undefined8 *)((long)puVar5 + lVar4 + 8) = uStack_68;
              puVar6 = puStack_50;
              lVar4 = lStack_b8;
            }
            in_R11 = &DAT_01a233a0;
            puVar6 = puVar6 + 2;
          }
        }
        else {
LAB_0139386c:
          uVar9 = 0;
          puVar5 = (undefined8 *)0x0;
          bVar3 = '\0';
        }
      }
      else {
        if ((*(int *)(puVar6 + 2) != -0x778cd48) || (puVar6 != &DAT_0194e220)) goto LAB_0139386c;
        lStack_e8 = puVar11[1];
        uStack_a8 = *puVar11;
        if (DAT_02de02b8 == lStack_e8) {
          cVar2 = runtime_memequal();
        }
        else {
          cVar2 = '\0';
        }
        if (cVar2 == '\0') {
          if (DAT_02de02c8 == lStack_e8) {
            cVar2 = runtime_memequal();
          }
          else {
            cVar2 = '\0';
          }
          if (cVar2 != '\0') goto LAB_0139366c;
          abStack_152[0x20] = '\0';
        }
        else {
LAB_0139366c:
          abStack_152[0x20] = '\x01';
        }
        uStack_48 = runtime_makemap_small();
        puVar5 = (undefined8 *)runtime_mapassign_faststr(4);
        *puVar5 = &DAT_0194e220;
        if (DAT_02e5e450 != 0) {
          auVar12 = runtime_gcWriteBarrier1();
          puVar5 = auVar12._0_8_;
          *in_R11 = auVar12._8_8_;
        }
        puVar5[1] = &PTR_DAT_01f398c0;
        puStack_50 = (undefined8 *)runtime_convTstring();
        puVar5 = (undefined8 *)runtime_mapassign_faststr(4);
        *puVar5 = &DAT_0194e220;
        if (DAT_02e5e450 != 0) {
          auVar12 = runtime_gcWriteBarrier2();
          puVar5 = auVar12._0_8_;
          *in_R11 = puStack_50;
          in_R11[1] = auVar12._8_8_;
        }
        puVar5[1] = puStack_50;
        uStack_58 = runtime_makemap_small();
        puVar5 = (undefined8 *)runtime_mapassign_faststr(4);
        *puVar5 = &DAT_0194e220;
        if (DAT_02e5e450 != 0) {
          auVar12 = runtime_gcWriteBarrier1();
          puVar5 = auVar12._0_8_;
          *in_R11 = auVar12._8_8_;
        }
        puVar5[1] = &PTR_DAT_01f3a3d0;
        puVar5 = (undefined8 *)runtime_mapassign_faststr(0xd);
        auVar12._8_8_ = &DAT_01a233a0;
        auVar12._0_8_ = puVar5;
        *puVar5 = &DAT_01a233a0;
        if (DAT_02e5e450 != 0) {
          uVar7 = puVar5[1];
          auVar12 = runtime_gcWriteBarrier2();
          *in_R11 = uStack_58;
          in_R11[1] = uVar7;
        }
        *(undefined8 *)(auVar12._0_8_ + 8) = uStack_58;
        puVar5 = (undefined8 *)runtime_growslice(1,&DAT_019b39a0,auVar12._8_8_,0);
        *puVar5 = &DAT_01a233a0;
        if (DAT_02e5e450 != 0) {
          uVar7 = puVar5[1];
          puVar5 = (undefined8 *)runtime_gcWriteBarrier2();
          *in_R11 = uStack_48;
          in_R11[1] = uVar7;
        }
        puVar5[1] = uStack_48;
        uVar9 = 1;
        bVar3 = abStack_152[0x20];
      }
    }
  }
  if (bVar3 == '\0') {
    uStack_e0 = uVar9;
    puStack_a0 = puVar5;
    uStack_48 = runtime_makemap_small();
    puVar5 = (undefined8 *)runtime_mapassign_faststr(4);
    *puVar5 = &DAT_0194e220;
    if (DAT_02e5e450 != 0) {
      auVar12 = runtime_gcWriteBarrier1();
      puVar5 = auVar12._0_8_;
      *in_R11 = auVar12._8_8_;
    }
    puVar5[1] = &PTR_DAT_01f398c0;
    puStack_50 = (undefined8 *)runtime_convTstring();
    puVar5 = (undefined8 *)runtime_mapassign_faststr(4);
    *puVar5 = &DAT_0194e220;
    if (DAT_02e5e450 != 0) {
      auVar12 = runtime_gcWriteBarrier2();
      puVar5 = auVar12._0_8_;
      *in_R11 = puStack_50;
      in_R11[1] = auVar12._8_8_;
    }
    puVar5[1] = puStack_50;
    puVar5 = (undefined8 *)runtime_newobject();
    *puVar5 = &DAT_01a233a0;
    if (DAT_02e5e450 != 0) {
      puVar5 = (undefined8 *)runtime_gcWriteBarrier1();
      *in_R11 = uStack_48;
    }
    puVar5[1] = uStack_48;
    uVar9 = uStack_e0 + 1;
    if (uVar9 < 2) {
      uVar9 = 1;
      uVar10 = 1;
    }
    else {
      uVar10 = 1;
      puVar5 = (undefined8 *)runtime_growslice(uStack_e0,&DAT_019b39a0);
    }
    uVar1 = uStack_e0;
    uStack_e0 = uVar9;
    uStack_d8 = uVar10;
    puStack_60 = puVar5;
    runtime_typedslicecopy(puStack_a0,uVar1,(ulong)((uint)((long)-(uVar10 - 1) >> 0x3f) & 0x10) + (long)puVar5
                 ,uVar9 - 1);
  }
  puStack_50 = (undefined8 *)runtime_convTslice();
  puVar5 = (undefined8 *)runtime_mapassign_faststr(6);
  *puVar5 = &DAT_0192e960;
  if (DAT_02e5e450 != 0) {
    auVar12 = runtime_gcWriteBarrier2();
    puVar5 = auVar12._0_8_;
    *in_R11 = puStack_50;
    in_R11[1] = auVar12._8_8_;
  }
  puVar5[1] = puStack_50;
  runtime_stringtoslicebyte();
  crypto_sha256_Sum256();
  lVar4 = runtime_makeslice();
  uVar9 = 0;
  for (lVar8 = 0; lVar8 < 0x20; lVar8 = lVar8 + 1) {
    bVar3 = abStack_152[lVar8];
    if (0x3f < uVar9) {
                    /* WARNING: Subroutine does not return */
      runtime_panicIndex();
    }
    *(undefined *)(lVar4 + uVar9) = (&DAT_01c4ed43)[bVar3 >> 4];
    if (0x3f < uVar9 + 1) {
                    /* WARNING: Subroutine does not return */
      runtime_panicIndex();
    }
    *(undefined *)(uVar9 + 1 + lVar4) = (&DAT_01c4ed43)[bVar3 & 0xf];
    uVar9 = uVar9 + 2;
  }
  uStack_b0 = runtime_slicebytetostring();
  lStack_f0 = lVar4;
  puVar5 = (undefined8 *)runtime_mapaccess1_faststr(10);
  if ((undefined8 *)*puVar5 == &DAT_0194e220) {
    lStack_98 = *(long *)puVar5[1];
    uStack_d0 = ((long *)puVar5[1])[1];
    if (uStack_d0 != 0) {
      runtime_mapdelete_faststr(10,uStack_d0,puStack_10,&DAT_01c44157);
      puVar5 = extraout_RDX;
      goto LAB_01393d7a;
    }
  }
  puVar6 = (undefined8 *)runtime_mapaccess1_faststr(8,0,puStack_10,&DAT_01c3ff37);
  puVar5 = &DAT_01a233a0;
  if ((undefined8 *)*puVar6 == &DAT_01a233a0) {
    puVar5 = (undefined8 *)runtime_mapaccess1_faststr(7);
    if ((undefined8 *)*puVar5 == &DAT_0194e220) {
      lStack_98 = *(long *)puVar5[1];
      uStack_d0 = ((long *)puVar5[1])[1];
      lVar4 = internal_stringslite_Index(9);
      if (-1 < lVar4) {
        if (uStack_d0 < lVar4 + 9U) {
                    /* WARNING: Subroutine does not return */
          runtime_panicSliceB();
        }
        uStack_d0 = (uStack_d0 - lVar4) - 9;
        lStack_98 = lStack_98 + (lVar4 + 9U & (long)-uStack_d0 >> 0x3f);
      }
    }
    else {
      uStack_d0 = 0;
      lStack_98 = 0;
    }
    puVar5 = &DAT_01a233a0;
  }
  else {
    uStack_d0 = 0;
    lStack_98 = 0;
  }
LAB_01393d7a:
  uStack_40 = runtime_concatstring2(uStack_b0,lStack_f0,puVar5,5);
  pcStack_38 = 
  "user_ravenbytesQuery3.0.0ROUTE%s#%d</tr>debug%s:%d*fuzz*listPOST:HEAD:IndexInputshort%s,%s=j=02=G=15-0700%dh%sdefersweeptestRtestWexecWhchanexecRschedsudogtimergscanmheaptracepanicsleepamd64gcing MB,  got= ...\n max=scav  ptr ] = (trap:init  ms, fault and  tab= tag= top=[...], fp:deny"
  ;
  auVar12 = runtime_concatstring2(*(undefined8 *)(lStack0000000000000020 + 0x98),
                         *(undefined8 *)(lStack0000000000000020 + 0xa0),lStack0000000000000020,8);
  uStack_30 = auVar12._0_8_;
  puStack_28 = &DAT_01c4007f;
  uStack_20 = runtime_concatstring2(lStack_98,uStack_d0,auVar12._8_8_,8);
  puStack_18 = &DAT_01c40087;
  auVar12 = runtime_makemap_small();
  uStack_48 = auVar12._0_8_;
  strings_Join(&DAT_01f38610,1,auVar12._8_8_,3);
  puStack_50 = (undefined8 *)runtime_convTstring();
  puVar5 = (undefined8 *)runtime_mapassign_faststr(7);
  *puVar5 = &DAT_0194e220;
  if (DAT_02e5e450 != 0) {
    auVar12 = runtime_gcWriteBarrier2();
    puVar5 = auVar12._0_8_;
    *in_R11 = puStack_50;
    in_R11[1] = auVar12._8_8_;
  }
  puVar5[1] = puStack_50;
  lVar4 = 8;
  puVar5 = (undefined8 *)runtime_mapassign_faststr();
  *puVar5 = &DAT_01a233a0;
  if (DAT_02e5e450 != 0) {
    uVar7 = puVar5[1];
    puVar5 = (undefined8 *)runtime_gcWriteBarrier2();
    *in_R11 = uStack_48;
    in_R11[1] = uVar7;
  }
  puVar5[1] = uStack_48;
  uVar7 = encoding_json_Marshal();
  if (lVar4 == 0) {
    return uVar7;
  }
  return uStack0000000000000008;
}



