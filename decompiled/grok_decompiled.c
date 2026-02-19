// CodeFreeMax - GROK Channel Decompiled Functions
// 6 functions

// === grok.ProcessLine @ 0x1612e80 ===

long grok_ProcessLine(void)

{
  char cVar1;
  undefined8 uVar2;
  undefined8 uVar3;
  undefined8 uVar4;
  undefined8 in_RAX;
  undefined8 uVar5;
  long lVar6;
  undefined8 *puVar7;
  undefined8 uVar8;
  undefined8 *in_RCX;
  ulong uVar9;
  undefined *puVar10;
  ulong uVar11;
  undefined1 uVar12;
  long lVar13;
  undefined8 extraout_RDX;
  long extraout_RDX_00;
  long lVar14;
  undefined8 *unaff_RBX;
  undefined1 *puVar15;
  undefined1 *unaff_RBP;
  undefined1 *puVar16;
  undefined8 *in_R9;
  undefined8 *in_R11;
  long unaff_R14;
  undefined8 in_XMM15_Qa;
  undefined8 in_XMM15_Qb;
  undefined1 auVar17 [16];
  
  do {
    puVar15 = (undefined1 *)register0x00000020;
    puVar16 = unaff_RBP;
    if (*(undefined1 **)(unaff_R14 + 0x10) < (undefined1 *)((long)register0x00000020 + -0x188)) {
      puVar16 = (undefined1 *)((long)register0x00000020 + -8);
      *(undefined1 **)((long)register0x00000020 + -8) = unaff_RBP;
      puVar15 = (undefined1 *)((long)register0x00000020 + -0x208);
      *(undefined8 **)((long)register0x00000020 + 0x10) = unaff_RBX;
      if (in_RCX == (undefined8 *)0x0) {
        return 0;
      }
      *(undefined8 *)((long)register0x00000020 + 8) = in_RAX;
      *(undefined8 **)((long)register0x00000020 + 0x18) = in_RCX;
      *(undefined8 **)((long)register0x00000020 + 0x10) = unaff_RBX;
      *(undefined8 *)((long)register0x00000020 + -0x210) = 0x1612ed2;
      uVar5 = runtime_newobject();
      *(undefined8 *)((long)register0x00000020 + -0x10) = uVar5;
      *(undefined8 *)((long)register0x00000020 + -0x210) = 0x1612ef1;
      runtime_stringtoslicebyte();
      *(undefined8 *)((long)register0x00000020 + -0x210) = 0x1612f05;
      lVar6 = encoding_json_Unmarshal(&DAT_01928320,*(undefined8 *)((long)register0x00000020 + -0x10));
      if (lVar6 != 0) {
        return 0;
      }
      *(undefined8 *)((long)register0x00000020 + -0x210) = 0x1612f31;
      puVar7 = (undefined8 *)runtime_mapaccess1_faststr(6);
      if ((undefined8 *)*puVar7 != &DAT_01a233a0) {
        return 0;
      }
      *(undefined8 *)((long)register0x00000020 + -0x210) = 0x1612f65;
      puVar7 = (undefined8 *)runtime_mapaccess1_faststr(8);
      if ((undefined8 *)*puVar7 != &DAT_01a233a0) {
        return 0;
      }
      *(undefined8 *)((long)register0x00000020 + -0x38) = puVar7[1];
      *(undefined8 *)((long)register0x00000020 + -0x88) = in_XMM15_Qa;
      *(undefined8 *)((long)register0x00000020 + -0x80) = in_XMM15_Qb;
      *(undefined8 *)((long)register0x00000020 + -0x78) = in_XMM15_Qa;
      *(undefined8 *)((long)register0x00000020 + -0x70) = in_XMM15_Qb;
      *(undefined8 *)((long)register0x00000020 + -0x210) = 0x1612fa7;
      puVar7 = (undefined8 *)runtime_mapaccess1_faststr(7);
      if (((undefined8 *)*puVar7 == &DAT_01a233a0) &&
         (uVar5 = puVar7[1], *(long *)(*(long *)((long)register0x00000020 + 8) + 0x40) == 0)) {
        *(undefined8 *)((long)register0x00000020 + -0x210) = 0x1612fe8;
        puVar7 = (undefined8 *)runtime_mapaccess1_faststr(9,uVar5,&DAT_01a233a0,&DAT_01c41fde);
        if ((undefined8 *)*puVar7 == &DAT_0194e220) {
          uVar5 = *(undefined8 *)puVar7[1];
          in_R9 = *(undefined8 **)((long)register0x00000020 + 8);
          in_R9[8] = ((undefined8 *)puVar7[1])[1];
          if (DAT_02e5e450 != 0) {
            uVar8 = in_R9[7];
            *(undefined8 *)((long)register0x00000020 + -0x210) = 0x161301d;
            runtime_gcWriteBarrier2();
            *in_R11 = uVar5;
            in_R11[1] = uVar8;
          }
          in_R9[7] = uVar5;
        }
        else {
          in_R9 = *(undefined8 **)((long)register0x00000020 + 8);
        }
      }
      *(undefined8 *)((long)register0x00000020 + -0x210) = 0x161305c;
      puVar7 = (undefined8 *)runtime_mapaccess1_faststr(10);
      if ((undefined8 *)*puVar7 == &DAT_0194e220) {
        in_R11 = (undefined8 *)((undefined8 *)puVar7[1])[1];
        uVar5 = *(undefined8 *)puVar7[1];
        lVar6 = *(long *)((long)register0x00000020 + 8);
        *(undefined8 **)(lVar6 + 0x30) = in_R11;
        if (DAT_02e5e450 != 0) {
          puVar7 = *(undefined8 **)(lVar6 + 0x28);
          *(undefined8 *)((long)register0x00000020 + -0x210) = 0x1613094;
          in_R11 = puVar7;
          lVar6 = runtime_gcWriteBarrier2();
          *in_R11 = uVar5;
          in_R11[1] = puVar7;
        }
        *(undefined8 *)(lVar6 + 0x28) = uVar5;
      }
      else {
        lVar6 = *(long *)((long)register0x00000020 + 8);
      }
      if (*(char *)(lVar6 + 0x49) != '\0') {
LAB_016131d8:
        *(undefined8 *)((long)register0x00000020 + -0x210) = 0x16131f8;
        puVar7 = (undefined8 *)runtime_mapaccess1_faststr(0x20);
        if ((undefined8 *)*puVar7 == &DAT_01a233a0) {
          *(undefined8 *)((long)register0x00000020 + -0x58) = puVar7[1];
          lVar6 = *(long *)((long)register0x00000020 + 8);
          if (*(char *)(lVar6 + 0x4a) == '\0') {
            if (*(char *)(lVar6 + 0x48) != '\0') {
LAB_01613fd0:
              *(undefined8 *)((long)register0x00000020 + -0x210) = 0x1613fe7;
              puVar7 = (undefined8 *)runtime_mapaccess1_faststr(10);
              if ((undefined *)*puVar7 == &DAT_0194e5e0) {
                lVar6 = (long)*(double *)puVar7[1] + 1;
              }
              else {
                lVar6 = 1;
              }
              *(long *)((long)register0x00000020 + -0x130) = lVar6;
              *(undefined8 *)((long)register0x00000020 + -0x210) = 0x1614032;
              puVar7 = (undefined8 *)runtime_mapaccess1_faststr(8);
              if ((undefined *)*puVar7 == &DAT_0194e5e0) {
                lVar6 = (long)*(double *)puVar7[1];
              }
              else {
                lVar6 = 0;
              }
              *(long *)((long)register0x00000020 + -0x148) = lVar6;
              *(undefined8 *)((long)register0x00000020 + -0x30) = in_XMM15_Qa;
              *(undefined8 *)((long)register0x00000020 + -0x28) = in_XMM15_Qb;
              *(undefined8 *)((long)register0x00000020 + -0x20) = in_XMM15_Qa;
              *(undefined8 *)((long)register0x00000020 + -0x18) = in_XMM15_Qb;
              *(undefined8 *)((long)register0x00000020 + -0x210) = 0x1614076;
              uVar5 = runtime_convT64();
              *(undefined8 **)((long)register0x00000020 + -0x30) = &DAT_0194e460;
              *(undefined8 *)((long)register0x00000020 + -0x28) = uVar5;
              *(undefined8 *)((long)register0x00000020 + -0x210) = 0x161409a;
              uVar5 = runtime_convT64();
              *(undefined8 **)((long)register0x00000020 + -0x20) = &DAT_0194e460;
              *(undefined8 *)((long)register0x00000020 + -0x18) = uVar5;
              *(undefined8 *)((long)register0x00000020 + -0x210) = 0x16140d2;
              lVar6 = fmt_Sprintf();
              in_R9 = (undefined8 *)0x0;
              *(undefined8 *)((long)register0x00000020 + -0x210) = 0x16140ef;
              uVar5 = kiro2api_internal_logic_grok_StreamProcessor_BuildSSE();
              if (*(undefined1 **)((long)register0x00000020 + -0x88) == (undefined1 *)0x0) {
                *(undefined1 **)((long)register0x00000020 + -0x88) =
                     (undefined1 *)((long)register0x00000020 + -0x88);
LAB_0161411f:
                uVar11 = *(ulong *)((long)register0x00000020 + -0x70);
                uVar9 = lVar6 + *(long *)((long)register0x00000020 + -0x78);
                in_R9 = *(undefined8 **)((long)register0x00000020 + -0x80);
                if (uVar11 < uVar9) {
                  *(long *)((long)register0x00000020 + -0x108) =
                       *(long *)((long)register0x00000020 + -0x78);
                  *(long *)((long)register0x00000020 + -0x168) = lVar6;
                  *(undefined8 *)((long)register0x00000020 + -0xa8) = uVar5;
                  *(undefined8 *)((long)register0x00000020 + -0x210) = 0x1614172;
                  in_R9 = (undefined8 *)runtime_growslice(lVar6,&DAT_0194e2a0);
                }
                *(ulong *)((long)register0x00000020 + -0x108) = uVar9;
                *(ulong *)((long)register0x00000020 + -0x110) = uVar11;
                *(undefined8 **)((long)register0x00000020 + -0x38) = in_R9;
                *(undefined8 *)((long)register0x00000020 + -0x210) = 0x16141b9;
                runtime_memmove();
                *(undefined8 *)((long)register0x00000020 + -0x78) =
                     *(undefined8 *)((long)register0x00000020 + -0x108);
                *(undefined8 *)((long)register0x00000020 + -0x70) =
                     *(undefined8 *)((long)register0x00000020 + -0x110);
                *(undefined8 *)((long)register0x00000020 + -0x80) =
                     *(undefined8 *)((long)register0x00000020 + -0x38);
                goto LAB_01614409;
              }
              if (*(undefined1 **)((long)register0x00000020 + -0x88) ==
                  (undefined1 *)((long)register0x00000020 + -0x88)) goto LAB_0161411f;
              goto LAB_0161449d;
            }
            in_R9 = (undefined8 *)0x0;
            *(undefined8 *)((long)register0x00000020 + -0x210) = 0x1613eb5;
            uVar5 = kiro2api_internal_logic_grok_StreamProcessor_BuildSSE();
            if (*(undefined1 **)((long)register0x00000020 + -0x88) == (undefined1 *)0x0) {
              *(undefined1 **)((long)register0x00000020 + -0x88) =
                   (undefined1 *)((long)register0x00000020 + -0x88);
LAB_01613eef:
              puVar10 = *(undefined **)((long)register0x00000020 + -0x70);
              lVar6 = *(long *)((long)register0x00000020 + -0x78);
              uVar8 = *(undefined8 *)((long)register0x00000020 + -0x80);
              if (puVar10 < &DAT_01c3ff2f + lVar6) {
                *(long *)((long)register0x00000020 + -0x108) = lVar6;
                *(undefined8 *)((long)register0x00000020 + -0xa0) = uVar5;
                *(undefined **)((long)register0x00000020 + -0x160) = &DAT_01c3ff2f;
                *(undefined8 *)((long)register0x00000020 + -0x210) = 0x1613f3d;
                uVar8 = runtime_growslice(&DAT_01c3ff2f,&DAT_0194e2a0,lVar6,puVar10,
                                     (undefined1 *)((long)register0x00000020 + -0x88));
              }
              *(undefined **)((long)register0x00000020 + -0x108) = puVar10;
              *(undefined8 *)((long)register0x00000020 + -0x38) = uVar8;
              *(undefined **)((long)register0x00000020 + -0x110) = &DAT_01c3ff2f + lVar6;
              *(undefined8 *)((long)register0x00000020 + -0x210) = 0x1613f85;
              runtime_memmove();
              *(undefined8 *)((long)register0x00000020 + -0x78) =
                   *(undefined8 *)((long)register0x00000020 + -0x110);
              *(undefined8 *)((long)register0x00000020 + -0x70) =
                   *(undefined8 *)((long)register0x00000020 + -0x108);
              *(undefined8 *)((long)register0x00000020 + -0x80) =
                   *(undefined8 *)((long)register0x00000020 + -0x38);
              *(undefined1 *)(*(long *)((long)register0x00000020 + 8) + 0x48) = 1;
              goto LAB_01613fd0;
            }
            if (*(undefined1 **)((long)register0x00000020 + -0x88) ==
                (undefined1 *)((long)register0x00000020 + -0x88)) goto LAB_01613eef;
          }
          else {
            *(undefined1 *)(lVar6 + 0x48) = 1;
            *(undefined8 *)((long)register0x00000020 + -0x210) = 0x1614209;
            puVar7 = (undefined8 *)runtime_mapaccess1_faststr(10);
            if ((undefined *)*puVar7 == &DAT_0194e5e0) {
              lVar6 = (long)*(double *)puVar7[1] + 1;
            }
            else {
              lVar6 = 1;
            }
            *(long *)((long)register0x00000020 + -0x128) = lVar6;
            *(undefined8 *)((long)register0x00000020 + -0x210) = 0x1614254;
            puVar7 = (undefined8 *)runtime_mapaccess1_faststr(8);
            if ((undefined *)*puVar7 == &DAT_0194e5e0) {
              lVar6 = (long)*(double *)puVar7[1];
            }
            else {
              lVar6 = 0;
            }
            *(long *)((long)register0x00000020 + -0x140) = lVar6;
            *(undefined8 *)((long)register0x00000020 + -0x30) = in_XMM15_Qa;
            *(undefined8 *)((long)register0x00000020 + -0x28) = in_XMM15_Qb;
            *(undefined8 *)((long)register0x00000020 + -0x20) = in_XMM15_Qa;
            *(undefined8 *)((long)register0x00000020 + -0x18) = in_XMM15_Qb;
            *(undefined8 *)((long)register0x00000020 + -0x210) = 0x161429d;
            uVar5 = runtime_convT64();
            *(undefined8 **)((long)register0x00000020 + -0x30) = &DAT_0194e460;
            *(undefined8 *)((long)register0x00000020 + -0x28) = uVar5;
            *(undefined8 *)((long)register0x00000020 + -0x210) = 0x16142c5;
            auVar17 = runtime_convT64();
            *(undefined8 **)((long)register0x00000020 + -0x20) = &DAT_0194e460;
            *(long *)((long)register0x00000020 + -0x18) = auVar17._0_8_;
            *(undefined8 *)((long)register0x00000020 + -0x210) = 0x16142fd;
            lVar6 = fmt_Sprintf(2,2,auVar17._8_8_,(undefined1 *)((long)register0x00000020 + -0x30))
            ;
            *(undefined8 *)((long)register0x00000020 + -0x210) = 0x1614310;
            uVar5 = kiro2api_internal_logic_grok_StreamProcessor_BuildThinkingSSE();
            if (*(undefined1 **)((long)register0x00000020 + -0x88) == (undefined1 *)0x0) {
              *(undefined1 **)((long)register0x00000020 + -0x88) =
                   (undefined1 *)((long)register0x00000020 + -0x88);
LAB_01614340:
              uVar11 = *(ulong *)((long)register0x00000020 + -0x70);
              uVar9 = lVar6 + *(long *)((long)register0x00000020 + -0x78);
              in_R9 = *(undefined8 **)((long)register0x00000020 + -0x80);
              if (uVar11 < uVar9) {
                *(long *)((long)register0x00000020 + -0x108) =
                     *(long *)((long)register0x00000020 + -0x78);
                *(long *)((long)register0x00000020 + -0x158) = lVar6;
                *(undefined8 *)((long)register0x00000020 + -0x98) = uVar5;
                *(undefined8 *)((long)register0x00000020 + -0x210) = 0x1614392;
                in_R9 = (undefined8 *)runtime_growslice(lVar6,&DAT_0194e2a0);
              }
              *(ulong *)((long)register0x00000020 + -0x108) = uVar11;
              *(ulong *)((long)register0x00000020 + -0x110) = uVar9;
              *(undefined8 **)((long)register0x00000020 + -0x38) = in_R9;
              *(undefined8 *)((long)register0x00000020 + -0x210) = 0x16143d9;
              runtime_memmove();
              *(undefined8 *)((long)register0x00000020 + -0x78) =
                   *(undefined8 *)((long)register0x00000020 + -0x110);
              *(undefined8 *)((long)register0x00000020 + -0x70) =
                   *(undefined8 *)((long)register0x00000020 + -0x108);
              *(undefined8 *)((long)register0x00000020 + -0x80) =
                   *(undefined8 *)((long)register0x00000020 + -0x38);
LAB_01614409:
              lVar6 = *(long *)((long)register0x00000020 + -0x80);
              if (*(ulong *)((long)register0x00000020 + -0x78) <= (ulong)-lVar6) {
                return lVar6;
              }
              if (lVar6 != 0) {
                *(undefined8 *)((long)register0x00000020 + -0x210) = 0x1614485;
                runtime_panicunsafestringlen();
              }
              *(undefined8 *)((long)register0x00000020 + -0x210) = 0x161448a;
              runtime_panicunsafestringnilptr();
            }
            else if (*(undefined1 **)((long)register0x00000020 + -0x88) ==
                     (undefined1 *)((long)register0x00000020 + -0x88)) goto LAB_01614340;
            *(undefined8 *)((long)register0x00000020 + -0x210) = 0x161449d;
            runtime_gopanic();
LAB_0161449d:
            *(undefined8 *)((long)register0x00000020 + -0x210) = 0x16144b0;
            runtime_gopanic();
          }
          *(undefined8 *)((long)register0x00000020 + -0x210) = 0x16144c5;
          lVar6 = runtime_gopanic();
LAB_016144c5:
          if (lVar6 != 0) {
            *(undefined8 *)((long)register0x00000020 + -0x210) = 0x16144cf;
            runtime_panicunsafestringlen();
          }
          *(undefined8 *)((long)register0x00000020 + -0x210) = 0x16144d4;
          runtime_panicunsafestringnilptr();
LAB_016144d4:
          *(undefined8 *)((long)register0x00000020 + -0x210) = 0x16144e7;
          runtime_gopanic();
LAB_016144e7:
          *(undefined8 *)((long)register0x00000020 + -0x210) = 0x16144fa;
          runtime_gopanic();
LAB_016144fa:
          *(undefined8 *)((long)register0x00000020 + -0x210) = 0x161450d;
          runtime_gopanic();
LAB_0161450d:
          *(undefined8 *)((long)register0x00000020 + -0x210) = 0x1614525;
          runtime_gopanic();
        }
        else {
          *(undefined8 *)((long)register0x00000020 + -0x210) = 0x1613233;
          puVar7 = (undefined8 *)runtime_mapaccess1_faststr(0xd);
          if ((undefined8 *)*puVar7 == &DAT_01a233a0) {
            uVar5 = puVar7[1];
            *(undefined8 *)((long)register0x00000020 + -0x68) = uVar5;
            cVar1 = *(char *)(*(long *)((long)register0x00000020 + 8) + 0x48);
            if (cVar1 != '\0') {
              if (*(char *)(*(long *)((long)register0x00000020 + 8) + 0x4a) == '\0') {
                if (cVar1 == '\0') goto LAB_016136f7;
                *(undefined8 *)((long)register0x00000020 + -0x210) = 0x16132a9;
                puVar7 = (undefined8 *)runtime_mapaccess1_faststr(7,uVar5,&DAT_01a233a0,&DAT_01c3dd0c);
                if ((undefined8 *)*puVar7 == &DAT_0194e220) {
                  in_RCX = *(undefined8 **)puVar7[1];
                  lVar6 = ((undefined8 *)puVar7[1])[1];
                  in_R11 = in_RCX;
                  if (lVar6 == 0) goto LAB_01613415;
                  *(undefined8 *)((long)register0x00000020 + -0x210) = 0x16132f6;
                  lVar6 = runtime_concatstring2(&DAT_01f34d88,1,&DAT_0194e220,lVar6);
                  in_R9 = (undefined8 *)0x0;
                  *(undefined8 *)((long)register0x00000020 + -0x210) = 0x1613313;
                  uVar5 = kiro2api_internal_logic_grok_StreamProcessor_BuildSSE();
                  if (*(undefined1 **)((long)register0x00000020 + -0x88) == (undefined1 *)0x0) {
                    *(undefined1 **)((long)register0x00000020 + -0x88) =
                         (undefined1 *)((long)register0x00000020 + -0x88);
LAB_0161334f:
                    uVar11 = *(ulong *)((long)register0x00000020 + -0x70);
                    uVar9 = lVar6 + *(long *)((long)register0x00000020 + -0x78);
                    uVar8 = *(undefined8 *)((long)register0x00000020 + -0x80);
                    if (uVar11 < uVar9) {
                      *(long *)((long)register0x00000020 + -0x108) =
                           *(long *)((long)register0x00000020 + -0x78);
                      *(long *)((long)register0x00000020 + -0x178) = lVar6;
                      *(undefined8 *)((long)register0x00000020 + -0xb8) = uVar5;
                      *(undefined8 *)((long)register0x00000020 + -0x210) = 0x161339d;
                      uVar8 = runtime_growslice(lVar6);
                    }
                    *(undefined8 *)((long)register0x00000020 + -0x38) = uVar8;
                    *(ulong *)((long)register0x00000020 + -0x108) = uVar9;
                    *(ulong *)((long)register0x00000020 + -0x110) = uVar11;
                    *(undefined8 *)((long)register0x00000020 + -0x210) = 0x16133e5;
                    runtime_memmove();
                    *(undefined8 *)((long)register0x00000020 + -0x78) =
                         *(undefined8 *)((long)register0x00000020 + -0x108);
                    *(undefined8 *)((long)register0x00000020 + -0x70) =
                         *(undefined8 *)((long)register0x00000020 + -0x110);
                    *(undefined8 *)((long)register0x00000020 + -0x80) =
                         *(undefined8 *)((long)register0x00000020 + -0x38);
                    goto LAB_01613415;
                  }
                  if (*(undefined1 **)((long)register0x00000020 + -0x88) ==
                      (undefined1 *)((long)register0x00000020 + -0x88)) goto LAB_0161334f;
LAB_0161492b:
                  *(undefined8 *)((long)register0x00000020 + -0x210) = 0x161493e;
                  runtime_gopanic();
                  goto LAB_0161493e;
                }
                in_R11 = (undefined8 *)0x0;
LAB_01613415:
                in_RCX = (undefined8 *)&DAT_00000009;
                in_R9 = (undefined8 *)0x0;
                *(undefined8 *)((long)register0x00000020 + -0x210) = 0x1613438;
                uVar5 = kiro2api_internal_logic_grok_StreamProcessor_BuildSSE();
                if (*(undefined1 **)((long)register0x00000020 + -0x88) == (undefined1 *)0x0) {
                  *(undefined1 **)((long)register0x00000020 + -0x88) =
                       (undefined1 *)((long)register0x00000020 + -0x88);
                }
                else if (*(undefined1 **)((long)register0x00000020 + -0x88) !=
                         (undefined1 *)((long)register0x00000020 + -0x88)) goto LAB_01614918;
                puVar10 = *(undefined **)((long)register0x00000020 + -0x70);
                lVar6 = *(long *)((long)register0x00000020 + -0x78);
                uVar8 = *(undefined8 *)((long)register0x00000020 + -0x80);
                if (puVar10 < &DAT_01c41fe7 + lVar6) {
                  *(long *)((long)register0x00000020 + -0x108) = lVar6;
                  *(undefined **)((long)register0x00000020 + -0x180) = &DAT_01c41fe7;
                  *(undefined8 *)((long)register0x00000020 + -0xc0) = uVar5;
                  *(undefined8 *)((long)register0x00000020 + -0x210) = 0x16134be;
                  uVar8 = runtime_growslice(&DAT_01c41fe7,&DAT_0194e2a0,lVar6,puVar10,
                                       (undefined1 *)((long)register0x00000020 + -0x88));
                }
                *(undefined8 *)((long)register0x00000020 + -0x38) = uVar8;
                *(undefined **)((long)register0x00000020 + -0x108) = &DAT_01c41fe7 + lVar6;
                *(undefined **)((long)register0x00000020 + -0x110) = puVar10;
                *(undefined8 *)((long)register0x00000020 + -0x210) = 0x1613505;
                runtime_memmove();
                *(undefined8 *)((long)register0x00000020 + -0x78) =
                     *(undefined8 *)((long)register0x00000020 + -0x108);
                *(undefined8 *)((long)register0x00000020 + -0x70) =
                     *(undefined8 *)((long)register0x00000020 + -0x110);
                *(undefined8 *)((long)register0x00000020 + -0x80) =
                     *(undefined8 *)((long)register0x00000020 + -0x38);
                *(undefined1 *)(*(long *)((long)register0x00000020 + 8) + 0x48) = 0;
                uVar5 = *(undefined8 *)((long)register0x00000020 + -0x68);
              }
              else {
                *(undefined8 *)((long)register0x00000020 + -0x210) = 0x1613574;
                puVar7 = (undefined8 *)runtime_mapaccess1_faststr(7,uVar5,&DAT_01a233a0,&DAT_01c3dd0c);
                if ((undefined8 *)*puVar7 == &DAT_0194e220) {
                  in_RCX = *(undefined8 **)puVar7[1];
                  lVar6 = ((undefined8 *)puVar7[1])[1];
                  if (lVar6 != 0) {
                    *(undefined8 *)((long)register0x00000020 + -0x210) = 0x16135c8;
                    in_R9 = in_RCX;
                    lVar6 = runtime_concatstring2(&DAT_01f34d88,1,&DAT_0194e220,lVar6);
                    *(undefined8 *)((long)register0x00000020 + -0x210) = 0x16135db;
                    uVar5 = kiro2api_internal_logic_grok_StreamProcessor_BuildThinkingSSE();
                    if (*(undefined1 **)((long)register0x00000020 + -0x88) == (undefined1 *)0x0) {
                      *(undefined1 **)((long)register0x00000020 + -0x88) =
                           (undefined1 *)((long)register0x00000020 + -0x88);
LAB_01613613:
                      uVar9 = *(ulong *)((long)register0x00000020 + -0x70);
                      lVar14 = *(long *)((long)register0x00000020 + -0x78);
                      uVar8 = *(undefined8 *)((long)register0x00000020 + -0x80);
                      if (uVar9 < (ulong)(lVar6 + lVar14)) {
                        *(long *)((long)register0x00000020 + -0x108) = lVar14;
                        *(long *)((long)register0x00000020 + -0x170) = lVar6;
                        *(undefined8 *)((long)register0x00000020 + -0xb0) = uVar5;
                        *(undefined8 *)((long)register0x00000020 + -0x210) = 0x1613665;
                        uVar8 = runtime_growslice(lVar6,&DAT_0194e2a0,lVar14,uVar9,
                                             (undefined1 *)((long)register0x00000020 + -0x88));
                      }
                      *(undefined8 *)((long)register0x00000020 + -0x38) = uVar8;
                      *(long *)((long)register0x00000020 + -0x108) = lVar6 + lVar14;
                      *(ulong *)((long)register0x00000020 + -0x110) = uVar9;
                      *(undefined8 *)((long)register0x00000020 + -0x210) = 0x16136ac;
                      runtime_memmove();
                      *(undefined8 *)((long)register0x00000020 + -0x78) =
                           *(undefined8 *)((long)register0x00000020 + -0x108);
                      *(undefined8 *)((long)register0x00000020 + -0x70) =
                           *(undefined8 *)((long)register0x00000020 + -0x110);
                      *(undefined8 *)((long)register0x00000020 + -0x80) =
                           *(undefined8 *)((long)register0x00000020 + -0x38);
                      goto LAB_016136dc;
                    }
                    if (*(undefined1 **)((long)register0x00000020 + -0x88) ==
                        (undefined1 *)((long)register0x00000020 + -0x88)) goto LAB_01613613;
LAB_01614905:
                    *(undefined8 *)((long)register0x00000020 + -0x210) = 0x1614918;
                    runtime_gopanic();
LAB_01614918:
                    *(undefined8 *)((long)register0x00000020 + -0x210) = 0x161492b;
                    runtime_gopanic();
                    goto LAB_0161492b;
                  }
                }
LAB_016136dc:
                *(undefined1 *)(*(long *)((long)register0x00000020 + 8) + 0x48) = 0;
                uVar5 = *(undefined8 *)((long)register0x00000020 + -0x68);
              }
            }
LAB_016136f7:
            *(undefined8 *)((long)register0x00000020 + -0x210) = 0x161370e;
            puVar7 = (undefined8 *)runtime_mapaccess1_faststr(0x12,uVar5,&DAT_01a233a0,&DAT_01c53151);
            if ((undefined8 *)*puVar7 == &DAT_0192e960) {
              in_R9 = *(undefined8 **)puVar7[1];
              lVar6 = ((undefined8 *)puVar7[1])[1];
              goto LAB_01614640;
            }
            in_R9 = (undefined8 *)0x0;
            goto LAB_01614538;
          }
          *(undefined8 *)((long)register0x00000020 + -0x210) = 0x1613759;
          puVar7 = (undefined8 *)runtime_mapaccess1_faststr(5,0,&DAT_01a233a0,&DAT_01c3a57b);
          if ((undefined8 *)*puVar7 != &DAT_0194e220) {
LAB_01613e49:
            lVar6 = *(long *)((long)register0x00000020 + -0x80);
            if (*(ulong *)((long)register0x00000020 + -0x78) <= (ulong)-lVar6) {
              return lVar6;
            }
            goto LAB_016144c5;
          }
          uVar5 = *(undefined8 *)puVar7[1];
          lVar6 = ((undefined8 *)puVar7[1])[1];
          if (lVar6 == 0) goto LAB_01613e49;
          *(long *)((long)register0x00000020 + -0x1b8) = lVar6;
          *(undefined8 *)((long)register0x00000020 + -0xf8) = uVar5;
          *(undefined8 *)((long)register0x00000020 + -0x210) = 0x16137bc;
          puVar7 = (undefined8 *)runtime_mapaccess1_faststr(10,lVar6,&DAT_0194e220,&DAT_01c44305);
          if ((undefined *)*puVar7 == &DAT_0194e620) {
            uVar12 = *(undefined1 *)puVar7[1];
          }
          else {
            uVar12 = 0;
          }
          *(undefined1 *)((long)register0x00000020 + -0x1c1) = uVar12;
          lVar6 = *(long *)((long)register0x00000020 + -0xf8);
          *(undefined8 *)((long)register0x00000020 + -0x210) = 0x16137f1;
          lVar14 = kiro2api_internal_logic_grok_StreamProcessor_filterToken();
          if (lVar6 == 0) goto LAB_01613e49;
          *(long *)((long)register0x00000020 + -0x1b8) = lVar6;
          *(long *)((long)register0x00000020 + -0xf8) = lVar14;
          if (*(char *)((long)register0x00000020 + -0x1c1) == '\0') {
            lVar6 = *(long *)((long)register0x00000020 + 8);
            if ((*(char *)(lVar6 + 0x48) == '\0') || (*(char *)(lVar6 + 0x4a) != '\0')) {
LAB_01613d1a:
              *(undefined1 *)(lVar6 + 0x48) = 0;
              in_R9 = (undefined8 *)0x0;
              *(undefined8 *)((long)register0x00000020 + -0x210) = 0x1613d36;
              uVar5 = kiro2api_internal_logic_grok_StreamProcessor_BuildSSE();
              if (*(undefined1 **)((long)register0x00000020 + -0x88) == (undefined1 *)0x0) {
                *(undefined1 **)((long)register0x00000020 + -0x88) =
                     (undefined1 *)((long)register0x00000020 + -0x88);
LAB_01613d67:
                uVar11 = *(ulong *)((long)register0x00000020 + -0x70);
                uVar9 = *(long *)((long)register0x00000020 + -0x78) + lVar14;
                in_R9 = *(undefined8 **)((long)register0x00000020 + -0x80);
                if (uVar11 < uVar9) {
                  *(long *)((long)register0x00000020 + -0x1b0) = lVar14;
                  *(undefined8 *)((long)register0x00000020 + -0xf0) = uVar5;
                  *(long *)((long)register0x00000020 + -0x108) =
                       *(long *)((long)register0x00000020 + -0x78);
                  *(undefined8 *)((long)register0x00000020 + -0x210) = 0x1613db2;
                  in_R9 = (undefined8 *)runtime_growslice(lVar14,&DAT_0194e2a0);
                }
                *(ulong *)((long)register0x00000020 + -0x108) = uVar11;
                *(undefined8 **)((long)register0x00000020 + -0x38) = in_R9;
                *(ulong *)((long)register0x00000020 + -0x110) = uVar9;
                *(undefined8 *)((long)register0x00000020 + -0x210) = 0x1613df6;
                runtime_memmove();
                *(undefined8 *)((long)register0x00000020 + -0x78) =
                     *(undefined8 *)((long)register0x00000020 + -0x110);
                *(undefined8 *)((long)register0x00000020 + -0x70) =
                     *(undefined8 *)((long)register0x00000020 + -0x108);
                *(undefined8 *)((long)register0x00000020 + -0x80) =
                     *(undefined8 *)((long)register0x00000020 + -0x38);
                if (*(long *)(*(long *)((long)register0x00000020 + 8) + 0x78) != 0) {
                  *(undefined8 *)((long)register0x00000020 + -0x210) = 0x1613e49;
                  kiro2api_internal_tokencount_UsageTracker_AppendTextContent();
                }
                goto LAB_01613e49;
              }
              if (*(undefined1 **)((long)register0x00000020 + -0x88) ==
                  (undefined1 *)((long)register0x00000020 + -0x88)) goto LAB_01613d67;
              goto LAB_016144d4;
            }
            in_R9 = (undefined8 *)0x0;
            *(undefined8 *)((long)register0x00000020 + -0x210) = 0x1613c0e;
            uVar5 = kiro2api_internal_logic_grok_StreamProcessor_BuildSSE();
            if (*(undefined1 **)((long)register0x00000020 + -0x88) == (undefined1 *)0x0) {
              *(undefined1 **)((long)register0x00000020 + -0x88) =
                   (undefined1 *)((long)register0x00000020 + -0x88);
LAB_01613c46:
              puVar10 = *(undefined **)((long)register0x00000020 + -0x70);
              lVar6 = *(long *)((long)register0x00000020 + -0x78);
              uVar8 = *(undefined8 *)((long)register0x00000020 + -0x80);
              if (puVar10 < &DAT_01c41fe7 + lVar6) {
                *(long *)((long)register0x00000020 + -0x108) = lVar6;
                *(undefined **)((long)register0x00000020 + -0x1a8) = &DAT_01c41fe7;
                *(undefined8 *)((long)register0x00000020 + -0xe8) = uVar5;
                *(undefined8 *)((long)register0x00000020 + -0x210) = 0x1613c91;
                uVar8 = runtime_growslice(&DAT_01c41fe7);
              }
              *(undefined **)((long)register0x00000020 + -0x108) = puVar10;
              *(undefined **)((long)register0x00000020 + -0x110) = &DAT_01c41fe7 + lVar6;
              *(undefined8 *)((long)register0x00000020 + -0x38) = uVar8;
              *(undefined8 *)((long)register0x00000020 + -0x210) = 0x1613cd5;
              runtime_memmove();
              *(undefined8 *)((long)register0x00000020 + -0x78) =
                   *(undefined8 *)((long)register0x00000020 + -0x110);
              *(undefined8 *)((long)register0x00000020 + -0x70) =
                   *(undefined8 *)((long)register0x00000020 + -0x108);
              *(undefined8 *)((long)register0x00000020 + -0x80) =
                   *(undefined8 *)((long)register0x00000020 + -0x38);
              lVar14 = *(long *)((long)register0x00000020 + -0xf8);
              lVar6 = *(long *)((long)register0x00000020 + 8);
              goto LAB_01613d1a;
            }
            if (*(undefined1 **)((long)register0x00000020 + -0x88) ==
                (undefined1 *)((long)register0x00000020 + -0x88)) goto LAB_01613c46;
            goto LAB_016144e7;
          }
          lVar13 = *(long *)((long)register0x00000020 + 8);
          if (*(char *)(lVar13 + 0x4a) != '\0') {
            *(undefined1 *)(lVar13 + 0x48) = 1;
            *(undefined8 *)((long)register0x00000020 + -0x210) = 0x1613ab7;
            uVar5 = kiro2api_internal_logic_grok_StreamProcessor_BuildThinkingSSE();
            if (*(undefined1 **)((long)register0x00000020 + -0x88) == (undefined1 *)0x0) {
              *(undefined1 **)((long)register0x00000020 + -0x88) =
                   (undefined1 *)((long)register0x00000020 + -0x88);
LAB_01613ae7:
              uVar11 = *(ulong *)((long)register0x00000020 + -0x70);
              uVar9 = lVar14 + *(long *)((long)register0x00000020 + -0x78);
              in_R9 = *(undefined8 **)((long)register0x00000020 + -0x80);
              if (uVar11 < uVar9) {
                *(long *)((long)register0x00000020 + -0x108) =
                     *(long *)((long)register0x00000020 + -0x78);
                *(undefined8 *)((long)register0x00000020 + -0xd0) = uVar5;
                *(long *)((long)register0x00000020 + -400) = lVar14;
                *(undefined8 *)((long)register0x00000020 + -0x210) = 0x1613b32;
                in_R9 = (undefined8 *)runtime_growslice(lVar14,&DAT_0194e2a0);
              }
              *(undefined8 **)((long)register0x00000020 + -0x38) = in_R9;
              *(ulong *)((long)register0x00000020 + -0x108) = uVar11;
              *(ulong *)((long)register0x00000020 + -0x110) = uVar9;
              *(undefined8 *)((long)register0x00000020 + -0x210) = 0x1613b76;
              runtime_memmove();
              *(undefined8 *)((long)register0x00000020 + -0x78) =
                   *(undefined8 *)((long)register0x00000020 + -0x110);
              *(undefined8 *)((long)register0x00000020 + -0x70) =
                   *(undefined8 *)((long)register0x00000020 + -0x108);
              *(undefined8 *)((long)register0x00000020 + -0x80) =
                   *(undefined8 *)((long)register0x00000020 + -0x38);
              if (*(long *)(*(long *)((long)register0x00000020 + 8) + 0x78) != 0) {
                *(undefined8 *)((long)register0x00000020 + -0x210) = 0x1613bcd;
                kiro2api_internal_tokencount_UsageTracker_AppendThinkingContent();
              }
              goto LAB_01613e49;
            }
            if (*(undefined1 **)((long)register0x00000020 + -0x88) ==
                (undefined1 *)((long)register0x00000020 + -0x88)) goto LAB_01613ae7;
            goto LAB_016144fa;
          }
          if (*(char *)(lVar13 + 0x48) != '\0') {
LAB_01613966:
            in_R9 = (undefined8 *)0x0;
            *(undefined8 *)((long)register0x00000020 + -0x210) = 0x161397e;
            uVar5 = kiro2api_internal_logic_grok_StreamProcessor_BuildSSE(0,0,lVar13,lVar6,0);
            if (*(undefined1 **)((long)register0x00000020 + -0x88) == (undefined1 *)0x0) {
              *(undefined1 **)((long)register0x00000020 + -0x88) =
                   (undefined1 *)((long)register0x00000020 + -0x88);
LAB_016139ae:
              uVar11 = *(ulong *)((long)register0x00000020 + -0x70);
              uVar9 = lVar14 + *(long *)((long)register0x00000020 + -0x78);
              in_R9 = *(undefined8 **)((long)register0x00000020 + -0x80);
              if (uVar11 < uVar9) {
                *(long *)((long)register0x00000020 + -0x108) =
                     *(long *)((long)register0x00000020 + -0x78);
                *(long *)((long)register0x00000020 + -0x1a0) = lVar14;
                *(undefined8 *)((long)register0x00000020 + -0xe0) = uVar5;
                *(undefined8 *)((long)register0x00000020 + -0x210) = 0x16139f9;
                in_R9 = (undefined8 *)runtime_growslice(lVar14,&DAT_0194e2a0);
              }
              *(undefined8 **)((long)register0x00000020 + -0x38) = in_R9;
              *(ulong *)((long)register0x00000020 + -0x108) = uVar9;
              *(ulong *)((long)register0x00000020 + -0x110) = uVar11;
              *(undefined8 *)((long)register0x00000020 + -0x210) = 0x1613a3d;
              runtime_memmove();
              *(undefined8 *)((long)register0x00000020 + -0x78) =
                   *(undefined8 *)((long)register0x00000020 + -0x108);
              *(undefined8 *)((long)register0x00000020 + -0x70) =
                   *(undefined8 *)((long)register0x00000020 + -0x110);
              *(undefined8 *)((long)register0x00000020 + -0x80) =
                   *(undefined8 *)((long)register0x00000020 + -0x38);
              if (*(long *)(*(long *)((long)register0x00000020 + 8) + 0x78) != 0) {
                *(undefined8 *)((long)register0x00000020 + -0x210) = 0x1613a9b;
                kiro2api_internal_tokencount_UsageTracker_AppendThinkingContent();
              }
              goto LAB_01613e49;
            }
            if (*(undefined1 **)((long)register0x00000020 + -0x88) ==
                (undefined1 *)((long)register0x00000020 + -0x88)) goto LAB_016139ae;
            goto LAB_0161450d;
          }
          in_R9 = (undefined8 *)0x0;
          *(undefined8 *)((long)register0x00000020 + -0x210) = 0x161384e;
          uVar5 = kiro2api_internal_logic_grok_StreamProcessor_BuildSSE();
          if (*(undefined1 **)((long)register0x00000020 + -0x88) == (undefined1 *)0x0) {
            *(undefined1 **)((long)register0x00000020 + -0x88) =
                 (undefined1 *)((long)register0x00000020 + -0x88);
LAB_01613886:
            puVar10 = *(undefined **)((long)register0x00000020 + -0x70);
            lVar6 = *(long *)((long)register0x00000020 + -0x78);
            uVar8 = *(undefined8 *)((long)register0x00000020 + -0x80);
            if (puVar10 < &DAT_01c3ff2f + lVar6) {
              *(long *)((long)register0x00000020 + -0x108) = lVar6;
              *(undefined **)((long)register0x00000020 + -0x198) = &DAT_01c3ff2f;
              *(undefined8 *)((long)register0x00000020 + -0xd8) = uVar5;
              *(undefined8 *)((long)register0x00000020 + -0x210) = 0x16138d1;
              uVar8 = runtime_growslice(&DAT_01c3ff2f);
            }
            *(undefined8 *)((long)register0x00000020 + -0x38) = uVar8;
            *(undefined **)((long)register0x00000020 + -0x108) = puVar10;
            *(undefined **)((long)register0x00000020 + -0x110) = &DAT_01c3ff2f + lVar6;
            *(undefined8 *)((long)register0x00000020 + -0x210) = 0x1613915;
            runtime_memmove();
            *(undefined8 *)((long)register0x00000020 + -0x78) =
                 *(undefined8 *)((long)register0x00000020 + -0x110);
            *(undefined8 *)((long)register0x00000020 + -0x70) =
                 *(undefined8 *)((long)register0x00000020 + -0x108);
            *(undefined8 *)((long)register0x00000020 + -0x80) =
                 *(undefined8 *)((long)register0x00000020 + -0x38);
            *(undefined1 *)(*(long *)((long)register0x00000020 + 8) + 0x48) = 1;
            lVar14 = *(long *)((long)register0x00000020 + -0xf8);
            lVar13 = *(long *)((long)register0x00000020 + 8);
            lVar6 = *(long *)((long)register0x00000020 + -0x1b8);
            goto LAB_01613966;
          }
          if (*(undefined1 **)((long)register0x00000020 + -0x88) ==
              (undefined1 *)((long)register0x00000020 + -0x88)) goto LAB_01613886;
        }
        *(undefined8 *)((long)register0x00000020 + -0x210) = 0x1614538;
        runtime_gopanic();
LAB_01614538:
        do {
          *(undefined8 *)((long)register0x00000020 + -0x210) = 0x1614558;
          puVar7 = (undefined8 *)runtime_mapaccess1_faststr(8);
          if ((undefined8 *)*puVar7 == &DAT_01a233a0) {
            uVar5 = puVar7[1];
            *(undefined8 *)((long)register0x00000020 + -0x210) = 0x161458d;
            puVar7 = (undefined8 *)runtime_mapaccess1_faststr(8,uVar5,&DAT_01a233a0,&DAT_01c3ff3f);
            if ((undefined8 *)*puVar7 == &DAT_01a233a0) {
              uVar5 = puVar7[1];
              *(undefined8 *)((long)register0x00000020 + -0x210) = 0x16145bd;
              puVar7 = (undefined8 *)runtime_mapaccess1_faststr(9,uVar5,&DAT_01a233a0,&DAT_01c41fde);
              if ((undefined8 *)*puVar7 == &DAT_0194e220) {
                uVar5 = *(undefined8 *)puVar7[1];
                lVar6 = *(long *)((long)register0x00000020 + 8);
                *(undefined8 *)(lVar6 + 0x40) = ((undefined8 *)puVar7[1])[1];
                if (DAT_02e5e450 != 0) {
                  uVar5 = *(undefined8 *)(lVar6 + 0x38);
                  *(undefined8 *)((long)register0x00000020 + -0x210) = 0x16145f2;
                  runtime_gcWriteBarrier2();
                  *in_R11 = extraout_RDX;
                  in_R11[1] = uVar5;
                  uVar5 = extraout_RDX;
                }
                *(undefined8 *)(lVar6 + 0x38) = uVar5;
              }
            }
          }
          lVar6 = *(long *)((long)register0x00000020 + -0x80);
          if (*(ulong *)((long)register0x00000020 + -0x78) <= (ulong)-lVar6) {
            return lVar6;
          }
          if (lVar6 != 0) {
            *(undefined8 *)((long)register0x00000020 + -0x210) = 0x161462f;
            runtime_panicunsafestringlen();
          }
          *(undefined8 *)((long)register0x00000020 + -0x210) = 0x1614634;
          runtime_panicunsafestringnilptr();
          lVar6 = extraout_RDX_00;
          while( true ) {
            in_R9 = in_R9 + 2;
            lVar6 = lVar6 + -1;
LAB_01614640:
            if (lVar6 < 1) break;
            if ((undefined8 *)*in_R9 == &DAT_0194e220) {
              uVar5 = *(undefined8 *)in_R9[1];
              lVar14 = ((undefined8 *)in_R9[1])[1];
              *(long *)((long)register0x00000020 + -0x108) = lVar6;
              *(undefined8 **)((long)register0x00000020 + -0x48) = in_R9;
              *(long *)((long)register0x00000020 + -0x1c0) = lVar14;
              *(undefined8 *)((long)register0x00000020 + -0x100) = uVar5;
              *(undefined8 *)((long)register0x00000020 + -0x210) = 0x16146ae;
              lVar6 = strings_genSplit(1,0,lVar6,&DAT_01f34f08,0xffffffffffffffff);
              if (lVar14 < 2) {
                uVar5 = 5;
                in_R11 = (undefined8 *)&DAT_01c3a5d0;
              }
              else {
                lVar14 = (lVar14 + -2) * 0x10;
                in_R11 = *(undefined8 **)(lVar6 + lVar14);
                uVar5 = *(undefined8 *)(lVar6 + 8 + lVar14);
              }
              *(undefined8 *)((long)register0x00000020 + -0x138) = uVar5;
              *(undefined8 **)((long)register0x00000020 + -0x60) = in_R11;
              lVar6 = *(long *)((long)register0x00000020 + 8);
              uVar5 = *(undefined8 *)(lVar6 + 0x68);
              uVar8 = *(undefined8 *)(lVar6 + 0x70);
              uVar2 = *(undefined8 *)(lVar6 + 0x10);
              uVar3 = *(undefined8 *)(lVar6 + 0x18);
              uVar4 = *(undefined8 *)((long)register0x00000020 + -0x1c0);
              *(undefined8 *)((long)register0x00000020 + -0x210) = 0x161471a;
              uVar5 = kiro2api_internal_logic_grok_processAssetURLWithDownload(uVar8,uVar2,lVar6,uVar5,uVar3,&DAT_01c3a5d0);
              *(undefined8 *)((long)register0x00000020 + -0x50) = uVar5;
              *(undefined8 *)((long)register0x00000020 + -0x120) = uVar4;
              *(undefined8 *)((long)register0x00000020 + -0x30) = in_XMM15_Qa;
              *(undefined8 *)((long)register0x00000020 + -0x28) = in_XMM15_Qb;
              *(undefined8 *)((long)register0x00000020 + -0x20) = in_XMM15_Qa;
              *(undefined8 *)((long)register0x00000020 + -0x18) = in_XMM15_Qb;
              *(undefined8 *)((long)register0x00000020 + -0x210) = 0x1614751;
              uVar5 = runtime_convTstring();
              *(undefined8 **)((long)register0x00000020 + -0x30) = &DAT_0194e220;
              *(undefined8 *)((long)register0x00000020 + -0x28) = uVar5;
              *(undefined8 *)((long)register0x00000020 + -0x210) = 0x161477d;
              uVar5 = runtime_convTstring();
              *(undefined8 **)((long)register0x00000020 + -0x20) = &DAT_0194e220;
              *(undefined8 *)((long)register0x00000020 + -0x18) = uVar5;
              *(undefined8 *)((long)register0x00000020 + -0x210) = 0x16147b5;
              lVar6 = fmt_Sprintf();
              in_RCX = (undefined8 *)&DAT_0000000a;
              in_R9 = (undefined8 *)0x0;
              *(undefined8 *)((long)register0x00000020 + -0x210) = 0x16147d2;
              uVar5 = kiro2api_internal_logic_grok_StreamProcessor_BuildSSE();
              if (*(undefined1 **)((long)register0x00000020 + -0x88) == (undefined1 *)0x0) {
                *(undefined1 **)((long)register0x00000020 + -0x88) =
                     (undefined1 *)((long)register0x00000020 + -0x88);
              }
              else if (*(undefined1 **)((long)register0x00000020 + -0x88) !=
                       (undefined1 *)((long)register0x00000020 + -0x88)) {
                *(undefined8 *)((long)register0x00000020 + -0x210) = 0x1614905;
                runtime_gopanic();
                goto LAB_01614905;
              }
              uVar11 = *(ulong *)((long)register0x00000020 + -0x70);
              uVar9 = lVar6 + *(long *)((long)register0x00000020 + -0x78);
              uVar8 = *(undefined8 *)((long)register0x00000020 + -0x80);
              if (uVar11 < uVar9) {
                *(long *)((long)register0x00000020 + -0x110) =
                     *(long *)((long)register0x00000020 + -0x78);
                *(long *)((long)register0x00000020 + -0x188) = lVar6;
                *(undefined8 *)((long)register0x00000020 + -200) = uVar5;
                *(undefined8 *)((long)register0x00000020 + -0x210) = 0x161485d;
                uVar8 = runtime_growslice(lVar6);
              }
              *(ulong *)((long)register0x00000020 + -0x110) = uVar11;
              *(undefined8 *)((long)register0x00000020 + -0x38) = uVar8;
              *(ulong *)((long)register0x00000020 + -0x118) = uVar9;
              *(undefined8 *)((long)register0x00000020 + -0x210) = 0x16148a5;
              runtime_memmove();
              *(undefined8 *)((long)register0x00000020 + -0x78) =
                   *(undefined8 *)((long)register0x00000020 + -0x118);
              *(undefined8 *)((long)register0x00000020 + -0x70) =
                   *(undefined8 *)((long)register0x00000020 + -0x110);
              *(undefined8 *)((long)register0x00000020 + -0x80) =
                   *(undefined8 *)((long)register0x00000020 + -0x38);
              lVar6 = *(long *)((long)register0x00000020 + -0x108);
              in_R9 = *(undefined8 **)((long)register0x00000020 + -0x48);
            }
            else {
              in_R11 = (undefined8 *)0x0;
            }
          }
        } while( true );
      }
      in_RCX = (undefined8 *)0x0;
      *(undefined8 *)((long)register0x00000020 + -0x210) = 0x16130cf;
      in_R9 = in_RCX;
      uVar5 = kiro2api_internal_logic_grok_StreamProcessor_BuildSSE(&DAT_01c41e01);
      if (*(undefined1 **)((long)register0x00000020 + -0x88) == (undefined1 *)0x0) {
        *(undefined1 **)((long)register0x00000020 + -0x88) =
             (undefined1 *)((long)register0x00000020 + -0x88);
LAB_01613107:
        puVar7 = *(undefined8 **)((long)register0x00000020 + -0x70);
        in_R9 = *(undefined8 **)((long)register0x00000020 + -0x78);
        uVar8 = *(undefined8 *)((long)register0x00000020 + -0x80);
        if (puVar7 < in_R9) {
          *(undefined8 **)((long)register0x00000020 + -0x108) = in_R9;
          *(undefined8 *)((long)register0x00000020 + -0x150) = 0;
          *(undefined8 *)((long)register0x00000020 + -0x90) = uVar5;
          *(undefined8 *)((long)register0x00000020 + -0x210) = 0x1613155;
          uVar8 = runtime_growslice(0);
        }
        *(undefined8 **)((long)register0x00000020 + -0x108) = in_R9;
        *(undefined8 **)((long)register0x00000020 + -0x110) = puVar7;
        *(undefined8 *)((long)register0x00000020 + -0x40) = uVar8;
        *(undefined8 *)((long)register0x00000020 + -0x210) = 0x161319c;
        runtime_memmove();
        *(undefined8 *)((long)register0x00000020 + -0x78) =
             *(undefined8 *)((long)register0x00000020 + -0x108);
        *(undefined8 *)((long)register0x00000020 + -0x70) =
             *(undefined8 *)((long)register0x00000020 + -0x110);
        *(undefined8 *)((long)register0x00000020 + -0x80) =
             *(undefined8 *)((long)register0x00000020 + -0x40);
        *(undefined1 *)(*(long *)((long)register0x00000020 + 8) + 0x49) = 1;
        goto LAB_016131d8;
      }
      if (*(undefined1 **)((long)register0x00000020 + -0x88) ==
          (undefined1 *)((long)register0x00000020 + -0x88)) goto LAB_01613107;
LAB_0161493e:
      unaff_RBX = &DAT_01f393c0;
      *(undefined8 *)((long)register0x00000020 + -0x210) = 0x1614951;
      in_RAX = runtime_gopanic();
    }
    *(undefined8 *)(puVar15 + 8) = in_RAX;
    *(undefined8 **)(puVar15 + 0x10) = unaff_RBX;
    *(undefined8 **)(puVar15 + 0x18) = in_RCX;
    *(undefined8 *)(puVar15 + -8) = 0x1614966;
    runtime_morestack_noctxt();
    in_RAX = *(undefined8 *)(puVar15 + 8);
    unaff_RBX = *(undefined8 **)(puVar15 + 0x10);
    in_RCX = *(undefined8 **)(puVar15 + 0x18);
    register0x00000020 = (BADSPACEBASE *)puVar15;
    unaff_RBP = puVar16;
  } while( true );
}




// === grok.CollectProcessorProcessWithUsage @ 0x1616000 ===

undefined8 grok_CollectProcessorProcessWithUsage(void)

{
  char cVar1;
  undefined8 in_RAX;
  undefined8 uVar2;
  long lVar3;
  undefined8 *puVar4;
  undefined8 uVar5;
  long *plVar6;
  undefined8 in_RCX;
  undefined8 uVar7;
  undefined8 *puVar8;
  long lVar9;
  undefined **unaff_RBX;
  undefined *puVar10;
  undefined1 *puVar11;
  undefined8 unaff_RBP;
  undefined8 uVar12;
  long lVar13;
  undefined8 uVar14;
  long in_R8;
  undefined8 *in_R11;
  long unaff_R14;
  undefined8 in_XMM15_Qa;
  undefined8 in_XMM15_Qb;
  undefined1 auVar15 [16];
  undefined1 auVar16 [16];
  
  do {
    puVar11 = (undefined1 *)register0x00000020;
    if (*(undefined1 **)(unaff_R14 + 0x10) < (undefined1 *)((long)register0x00000020 + -0x1e8)) {
      *(undefined8 *)((long)register0x00000020 + -8) = unaff_RBP;
      puVar11 = (undefined1 *)((long)register0x00000020 + -0x268);
      *(undefined ***)((long)register0x00000020 + 0x10) = unaff_RBX;
      *(undefined8 *)((long)register0x00000020 + 0x18) = in_RCX;
      *(undefined8 *)((long)register0x00000020 + 8) = in_RAX;
      *(undefined1 **)((long)register0x00000020 + -0x278) =
           (undefined1 *)((long)register0x00000020 + -8);
      *(undefined8 *)((long)register0x00000020 + -0x270) = 0x161604f;
      FUN_00488ce2();
      unaff_RBP = *(undefined8 *)((long)register0x00000020 + -0x278);
      *(undefined ***)((long)register0x00000020 + -0xb0) = unaff_RBX;
      *(undefined8 *)((long)register0x00000020 + -0xa8) = in_RCX;
      *(undefined **)((long)register0x00000020 + -0xa0) = &DAT_01d35230;
      *(undefined8 *)((long)register0x00000020 + -0x98) = 0x10000;
      in_RCX = 0x10000;
      *(undefined8 *)((long)register0x00000020 + -0x270) = 0x1616091;
      uVar2 = runtime_makeslice();
      if (*(char *)((long)register0x00000020 + -0x38) == '\0') {
        *(undefined8 *)((long)register0x00000020 + -0x70) = 0x10000;
        *(undefined8 *)((long)register0x00000020 + -0x68) = 0x10000;
        *(undefined8 *)((long)register0x00000020 + -0x78) = uVar2;
        *(undefined8 *)((long)register0x00000020 + -0x98) = 0x100000;
        uVar2 = 0;
        uVar5 = 0;
        uVar7 = 0;
        lVar3 = 0;
        uVar12 = 0;
        uVar14 = 0;
        while( true ) {
          *(undefined8 *)((long)register0x00000020 + -0xf0) = uVar14;
          *(undefined8 *)((long)register0x00000020 + -0x160) = uVar12;
          *(undefined8 *)((long)register0x00000020 + -0x110) = uVar5;
          *(undefined8 *)((long)register0x00000020 + -0x178) = uVar2;
          *(long *)((long)register0x00000020 + -0xe0) = lVar3;
          *(undefined8 *)((long)register0x00000020 + -0x150) = uVar7;
          *(undefined8 *)((long)register0x00000020 + -0x270) = 0x161611c;
          cVar1 = bufio_Scanner_Scan();
          if (cVar1 == '\0') break;
          lVar3 = *(long *)((long)register0x00000020 + -0x90);
          *(undefined8 *)((long)register0x00000020 + -0x270) = 0x1616146;
          uVar2 = runtime_slicebytetostring();
          if (lVar3 == 0) {
            uVar2 = *(undefined8 *)((long)register0x00000020 + -0x178);
            uVar5 = *(undefined8 *)((long)register0x00000020 + -0x110);
            uVar7 = *(undefined8 *)((long)register0x00000020 + -0x150);
            lVar3 = *(long *)((long)register0x00000020 + -0xe0);
            uVar12 = *(undefined8 *)((long)register0x00000020 + -0x160);
            uVar14 = *(undefined8 *)((long)register0x00000020 + -0xf0);
            in_R8 = lVar3;
          }
          else {
            *(long *)((long)register0x00000020 + -0x1a0) = lVar3;
            *(undefined8 *)((long)register0x00000020 + -0x130) = uVar2;
            *(undefined8 *)((long)register0x00000020 + -0x270) = 0x16161a5;
            uVar2 = runtime_newobject();
            *(undefined8 *)((long)register0x00000020 + -0x10) = uVar2;
            *(undefined8 *)((long)register0x00000020 + -0x270) = 0x16161c5;
            runtime_stringtoslicebyte();
            *(undefined8 *)((long)register0x00000020 + -0x270) = 0x16161d9;
            lVar3 = encoding_json_Unmarshal(&DAT_01928320,*(undefined8 *)((long)register0x00000020 + -0x10));
            if (lVar3 == 0) {
              *(undefined8 *)((long)register0x00000020 + -0x270) = 0x161623d;
              puVar4 = (undefined8 *)runtime_mapaccess1_faststr(6);
              if ((undefined8 *)*puVar4 == &DAT_01a233a0) {
                uVar2 = puVar4[1];
                *(undefined8 *)((long)register0x00000020 + -0x270) = 0x16162a9;
                puVar4 = (undefined8 *)runtime_mapaccess1_faststr(8,uVar2,&DAT_01a233a0,&DAT_01c3ff27);
                if ((undefined8 *)*puVar4 == &DAT_01a233a0) {
                  uVar2 = puVar4[1];
                  *(undefined8 *)((long)register0x00000020 + -0x108) = uVar2;
                  *(undefined8 *)((long)register0x00000020 + -0x270) = 0x161631d;
                  puVar4 = (undefined8 *)runtime_mapaccess1_faststr(7,uVar2,&DAT_01a233a0,&DAT_01c3de7f);
                  puVar8 = &DAT_01a233a0;
                  if ((undefined8 *)*puVar4 == &DAT_01a233a0) {
                    uVar2 = puVar4[1];
                    lVar3 = *(long *)((long)register0x00000020 + -0x160);
                    if (lVar3 == 0) {
                      *(undefined8 *)((long)register0x00000020 + -0x270) = 0x1616369;
                      puVar4 = (undefined8 *)runtime_mapaccess1_faststr(9,uVar2,&DAT_01a233a0,&DAT_01c41fde);
                      puVar8 = &DAT_0194e220;
                      if ((undefined8 *)*puVar4 == &DAT_0194e220) {
                        uVar2 = *(undefined8 *)puVar4[1];
                        lVar3 = ((undefined8 *)puVar4[1])[1];
                      }
                      else {
                        lVar3 = *(long *)((long)register0x00000020 + -0x160);
                        uVar2 = *(undefined8 *)((long)register0x00000020 + -0xf0);
                      }
                    }
                    else {
                      uVar2 = *(undefined8 *)((long)register0x00000020 + -0xf0);
                    }
                  }
                  else {
                    lVar3 = *(long *)((long)register0x00000020 + -0x160);
                    uVar2 = *(undefined8 *)((long)register0x00000020 + -0xf0);
                  }
                  *(long *)((long)register0x00000020 + -0x160) = lVar3;
                  *(undefined8 *)((long)register0x00000020 + -0xf0) = uVar2;
                  *(undefined8 *)((long)register0x00000020 + -0x270) = 0x16163d4;
                  puVar4 = (undefined8 *)runtime_mapaccess1_faststr(5,lVar3,puVar8,&DAT_01c3a57b);
                  if ((undefined8 *)*puVar4 == &DAT_0194e220) {
                    uVar2 = *(undefined8 *)puVar4[1];
                    lVar3 = ((undefined8 *)puVar4[1])[1];
                    if (lVar3 != 0) {
                      *(long *)((long)register0x00000020 + -0x180) = lVar3;
                      *(undefined8 *)((long)register0x00000020 + -0x118) = uVar2;
                      *(undefined8 *)((long)register0x00000020 + -0x270) = 0x161643f;
                      puVar4 = (undefined8 *)runtime_mapaccess1_faststr(10,lVar3,&DAT_0194e220,&DAT_01c44305);
                      if ((undefined *)*puVar4 == &DAT_0194e620) {
                        cVar1 = *(char *)puVar4[1];
                      }
                      else {
                        cVar1 = '\0';
                      }
                      if (*(long *)(*(long *)((long)register0x00000020 + 8) + 0x50) != 0) {
                        if (cVar1 == '\0') {
                          *(undefined8 *)((long)register0x00000020 + -0x270) = 0x161649c;
                          kiro2api_internal_tokencount_UsageTracker_AppendTextContent();
                        }
                        else {
                          *(undefined8 *)((long)register0x00000020 + -0x270) = 0x1616485;
                          kiro2api_internal_tokencount_UsageTracker_AppendThinkingContent();
                        }
                      }
                    }
                  }
                  *(undefined8 *)((long)register0x00000020 + -0x270) = 0x16164cb;
                  puVar4 = (undefined8 *)runtime_mapaccess1_faststr(0xd);
                  if ((undefined8 *)*puVar4 == &DAT_01a233a0) {
                    uVar2 = puVar4[1];
                    *(undefined8 *)((long)register0x00000020 + -0x100) = uVar2;
                    *(undefined8 *)((long)register0x00000020 + -0x270) = 0x1616545;
                    puVar4 = (undefined8 *)runtime_mapaccess1_faststr(10,uVar2,&DAT_01a233a0,&DAT_01c442e7);
                    if ((undefined8 *)*puVar4 == &DAT_0194e220) {
                      uVar2 = *(undefined8 *)puVar4[1];
                      uVar5 = ((undefined8 *)puVar4[1])[1];
                    }
                    else {
                      uVar5 = *(undefined8 *)((long)register0x00000020 + -0x178);
                      uVar2 = *(undefined8 *)((long)register0x00000020 + -0x110);
                    }
                    *(undefined8 *)((long)register0x00000020 + -0x178) = uVar5;
                    *(undefined8 *)((long)register0x00000020 + -0x110) = uVar2;
                    *(undefined8 *)((long)register0x00000020 + -0x270) = 0x161659e;
                    puVar4 = (undefined8 *)runtime_mapaccess1_faststr(7);
                    if ((undefined8 *)*puVar4 == &DAT_0194e220) {
                      uVar2 = *(undefined8 *)puVar4[1];
                      uVar5 = ((undefined8 *)puVar4[1])[1];
                    }
                    else {
                      uVar5 = *(undefined8 *)((long)register0x00000020 + -0x150);
                      uVar2 = *(undefined8 *)((long)register0x00000020 + -0xe0);
                    }
                    *(undefined8 *)((long)register0x00000020 + -0x150) = uVar5;
                    *(undefined8 *)((long)register0x00000020 + -0xe0) = uVar2;
                    *(undefined8 *)((long)register0x00000020 + -0x270) = 0x16165f7;
                    puVar4 = (undefined8 *)runtime_mapaccess1_faststr(0x12,uVar5,&DAT_0194e220,&DAT_01c53151);
                    if ((undefined8 *)*puVar4 == &DAT_0192e960) {
                      uVar2 = *(undefined8 *)puVar4[1];
                      lVar3 = ((undefined8 *)puVar4[1])[1];
                      if (lVar3 == 0) {
                        lVar3 = *(long *)((long)register0x00000020 + -0x150);
                        uVar2 = *(undefined8 *)((long)register0x00000020 + -0xe0);
                      }
                      else {
                        *(long *)((long)register0x00000020 + -0x198) = lVar3;
                        *(undefined8 *)((long)register0x00000020 + -0x128) = uVar2;
                        lVar3 = *(long *)((long)register0x00000020 + -0xe0);
                        *(undefined8 *)((long)register0x00000020 + -0x270) = 0x161666c;
                        uVar2 = runtime_concatstring2(&DAT_01f34d88,1,&DAT_0192e960,
                                             *(undefined8 *)((long)register0x00000020 + -0x150));
                        puVar4 = *(undefined8 **)((long)register0x00000020 + -0x128);
                        for (in_R8 = *(long *)((long)register0x00000020 + -0x198);
                            auVar16._8_8_ = puVar4, auVar16._0_8_ = uVar2, 0 < in_R8;
                            in_R8 = in_R8 + -1) {
                          if ((undefined8 *)*puVar4 == &DAT_0194e220) {
                            uVar5 = *(undefined8 *)puVar4[1];
                            lVar9 = ((undefined8 *)puVar4[1])[1];
                            *(long *)((long)register0x00000020 + -0x138) = in_R8;
                            *(undefined8 **)((long)register0x00000020 + -0xc0) = puVar4;
                            *(long *)((long)register0x00000020 + -400) = lVar9;
                            *(long *)((long)register0x00000020 + -0x140) = lVar3;
                            *(undefined8 *)((long)register0x00000020 + -0x120) = uVar5;
                            *(undefined8 *)((long)register0x00000020 + -0xd8) = uVar2;
                            *(undefined8 *)((long)register0x00000020 + -0x270) = 0x16173d6;
                            lVar3 = strings_genSplit(1,0,puVar4,&DAT_01f34f08,0xffffffffffffffff);
                            if (lVar9 < 2) {
                              uVar2 = 5;
                              in_R11 = (undefined8 *)&DAT_01c3a5d0;
                            }
                            else {
                              lVar9 = (lVar9 + -2) * 0x10;
                              in_R11 = *(undefined8 **)(lVar3 + lVar9);
                              uVar2 = *(undefined8 *)(lVar3 + 8 + lVar9);
                            }
                            *(undefined8 *)((long)register0x00000020 + -0x168) = uVar2;
                            *(undefined8 **)((long)register0x00000020 + -0xf8) = in_R11;
                            lVar3 = *(long *)((long)register0x00000020 + 8);
                            uVar2 = *(undefined8 *)(lVar3 + 0x28);
                            uVar5 = *(undefined8 *)(lVar3 + 0x30);
                            uVar7 = *(undefined8 *)(lVar3 + 0x10);
                            uVar12 = *(undefined8 *)(lVar3 + 0x18);
                            uVar14 = *(undefined8 *)((long)register0x00000020 + -400);
                            *(undefined8 *)((long)register0x00000020 + -0x270) = 0x1617445;
                            uVar2 = kiro2api_internal_logic_grok_processAssetURLWithDownload(uVar5,uVar7,lVar3,uVar2,uVar12,&DAT_01c3a5d0);
                            *(undefined8 *)((long)register0x00000020 + -0xe8) = uVar2;
                            *(undefined8 *)((long)register0x00000020 + -0x158) = uVar14;
                            *(undefined8 *)((long)register0x00000020 + -0x30) = in_XMM15_Qa;
                            *(undefined8 *)((long)register0x00000020 + -0x28) = in_XMM15_Qb;
                            *(undefined8 *)((long)register0x00000020 + -0x20) = in_XMM15_Qa;
                            *(undefined8 *)((long)register0x00000020 + -0x18) = in_XMM15_Qb;
                            *(undefined8 *)((long)register0x00000020 + -0x270) = 0x161747c;
                            uVar2 = runtime_convTstring();
                            *(undefined8 **)((long)register0x00000020 + -0x30) = &DAT_0194e220;
                            *(undefined8 *)((long)register0x00000020 + -0x28) = uVar2;
                            *(undefined8 *)((long)register0x00000020 + -0x270) = 0x16174a8;
                            uVar2 = runtime_convTstring();
                            *(undefined8 **)((long)register0x00000020 + -0x20) = &DAT_0194e220;
                            *(undefined8 *)((long)register0x00000020 + -0x18) = uVar2;
                            *(undefined8 *)((long)register0x00000020 + -0x270) = 0x16174e5;
                            auVar16 = fmt_Sprintf(2,2,&DAT_0194e220,
                                                   (undefined1 *)((long)register0x00000020 + -0x30))
                            ;
                            lVar3 = *(long *)((long)register0x00000020 + -0xd8);
                            *(undefined8 *)((long)register0x00000020 + -0x270) = 0x1617505;
                            uVar2 = runtime_concatstring2(auVar16._0_8_,10,auVar16._8_8_,
                                                 *(undefined8 *)((long)register0x00000020 + -0x140))
                            ;
                            auVar16._8_8_ = *(undefined8 *)((long)register0x00000020 + -0xc0);
                            auVar16._0_8_ = uVar2;
                            in_R8 = *(long *)((long)register0x00000020 + -0x138);
                          }
                          else {
                            in_R11 = (undefined8 *)0x0;
                          }
LAB_0161734e:
                          uVar2 = auVar16._0_8_;
                          puVar4 = (undefined8 *)(auVar16._8_8_ + 0x10);
                        }
                      }
                    }
                    else {
                      lVar3 = *(long *)((long)register0x00000020 + -0x150);
                      uVar2 = *(undefined8 *)((long)register0x00000020 + -0xe0);
                    }
                    *(long *)((long)register0x00000020 + -0x150) = lVar3;
                    *(undefined8 *)((long)register0x00000020 + -0xe0) = uVar2;
                    *(undefined8 *)((long)register0x00000020 + -0x270) = 0x16166c5;
                    puVar4 = (undefined8 *)runtime_mapaccess1_faststr(8);
                    if ((undefined8 *)*puVar4 == &DAT_01a233a0) {
                      uVar2 = puVar4[1];
                      *(undefined8 *)((long)register0x00000020 + -0x270) = 0x1616711;
                      puVar4 = (undefined8 *)runtime_mapaccess1_faststr(8,uVar2,&DAT_01a233a0,&DAT_01c3ff3f);
                      if ((undefined8 *)*puVar4 == &DAT_01a233a0) {
                        uVar2 = puVar4[1];
                        *(undefined8 *)((long)register0x00000020 + -0x270) = 0x161675a;
                        puVar4 = (undefined8 *)runtime_mapaccess1_faststr(9,uVar2,&DAT_01a233a0,&DAT_01c41fde);
                        if ((undefined8 *)*puVar4 == &DAT_0194e220) {
                          uVar14 = *(undefined8 *)puVar4[1];
                          uVar12 = ((undefined8 *)puVar4[1])[1];
                        }
                        else {
                          uVar12 = *(undefined8 *)((long)register0x00000020 + -0x160);
                          uVar14 = *(undefined8 *)((long)register0x00000020 + -0xf0);
                        }
                      }
                      else {
                        uVar12 = *(undefined8 *)((long)register0x00000020 + -0x160);
                        uVar14 = *(undefined8 *)((long)register0x00000020 + -0xf0);
                      }
                    }
                    else {
                      uVar12 = *(undefined8 *)((long)register0x00000020 + -0x160);
                      uVar14 = *(undefined8 *)((long)register0x00000020 + -0xf0);
                    }
                    uVar2 = *(undefined8 *)((long)register0x00000020 + -0x178);
                    uVar5 = *(undefined8 *)((long)register0x00000020 + -0x110);
                    uVar7 = *(undefined8 *)((long)register0x00000020 + -0x150);
                    lVar3 = *(long *)((long)register0x00000020 + -0xe0);
                    in_R8 = lVar3;
                  }
                  else {
                    uVar2 = *(undefined8 *)((long)register0x00000020 + -0x178);
                    uVar5 = *(undefined8 *)((long)register0x00000020 + -0x110);
                    uVar7 = *(undefined8 *)((long)register0x00000020 + -0x150);
                    lVar3 = *(long *)((long)register0x00000020 + -0xe0);
                    uVar12 = *(undefined8 *)((long)register0x00000020 + -0x160);
                    uVar14 = *(undefined8 *)((long)register0x00000020 + -0xf0);
                    in_R8 = lVar3;
                  }
                }
                else {
                  uVar2 = *(undefined8 *)((long)register0x00000020 + -0x178);
                  uVar5 = *(undefined8 *)((long)register0x00000020 + -0x110);
                  uVar7 = *(undefined8 *)((long)register0x00000020 + -0x150);
                  lVar3 = *(long *)((long)register0x00000020 + -0xe0);
                  uVar12 = *(undefined8 *)((long)register0x00000020 + -0x160);
                  uVar14 = *(undefined8 *)((long)register0x00000020 + -0xf0);
                  in_R8 = lVar3;
                }
              }
              else {
                uVar2 = *(undefined8 *)((long)register0x00000020 + -0x178);
                uVar5 = *(undefined8 *)((long)register0x00000020 + -0x110);
                uVar7 = *(undefined8 *)((long)register0x00000020 + -0x150);
                lVar3 = *(long *)((long)register0x00000020 + -0xe0);
                uVar12 = *(undefined8 *)((long)register0x00000020 + -0x160);
                uVar14 = *(undefined8 *)((long)register0x00000020 + -0xf0);
                in_R8 = lVar3;
              }
            }
            else {
              uVar2 = *(undefined8 *)((long)register0x00000020 + -0x178);
              uVar5 = *(undefined8 *)((long)register0x00000020 + -0x110);
              uVar7 = *(undefined8 *)((long)register0x00000020 + -0x150);
              lVar3 = *(long *)((long)register0x00000020 + -0xe0);
              uVar12 = *(undefined8 *)((long)register0x00000020 + -0x160);
              uVar14 = *(undefined8 *)((long)register0x00000020 + -0xf0);
              in_R8 = lVar3;
            }
          }
        }
        puVar10 = *(undefined **)((long)register0x00000020 + -0x178);
        if (puVar10 == (undefined *)0x0) {
          *(undefined8 *)((long)register0x00000020 + -0x270) = 0x16167ca;
          lVar9 = github_com_google_uuid_NewRandom();
          *(undefined4 *)((long)register0x00000020 + -0x1b0) =
               *(undefined4 *)((long)register0x00000020 + -0x268);
          *(undefined4 *)((long)register0x00000020 + -0x1ac) =
               *(undefined4 *)((long)register0x00000020 + -0x264);
          *(undefined4 *)((long)register0x00000020 + -0x1a8) =
               *(undefined4 *)((long)register0x00000020 + -0x260);
          *(undefined4 *)((long)register0x00000020 + -0x1a4) =
               *(undefined4 *)((long)register0x00000020 + -0x25c);
          if (lVar9 != 0) {
            *(undefined8 *)((long)register0x00000020 + -0x270) = 0x161734e;
            auVar16 = runtime_gopanic();
            goto LAB_0161734e;
          }
          *(undefined8 *)((long)register0x00000020 + -0x224) =
               *(undefined8 *)((long)register0x00000020 + -0x1b0);
          *(undefined8 *)((long)register0x00000020 + -0x21c) =
               *(undefined8 *)((long)register0x00000020 + -0x1a8);
          *(undefined8 *)((long)register0x00000020 + -0x214) = in_XMM15_Qa;
          *(undefined8 *)((long)register0x00000020 + -0x20c) = in_XMM15_Qb;
          *(undefined8 *)((long)register0x00000020 + -0x210) = in_XMM15_Qa;
          *(undefined8 *)((long)register0x00000020 + -0x208) = in_XMM15_Qb;
          *(undefined8 *)((long)register0x00000020 + -0x200) = in_XMM15_Qa;
          *(undefined8 *)((long)register0x00000020 + -0x1f8) = in_XMM15_Qb;
          *(undefined4 *)((long)register0x00000020 + -0x268) =
               *(undefined4 *)((long)register0x00000020 + -0x224);
          *(undefined4 *)((long)register0x00000020 + -0x264) =
               *(undefined4 *)((long)register0x00000020 + -0x220);
          *(undefined4 *)((long)register0x00000020 + -0x260) =
               *(undefined4 *)((long)register0x00000020 + -0x21c);
          *(undefined4 *)((long)register0x00000020 + -0x25c) =
               *(undefined4 *)((long)register0x00000020 + -0x218);
          *(undefined8 *)((long)register0x00000020 + -0x270) = 0x1616819;
          github_com_google_uuid_encodeHex();
          *(undefined8 *)((long)register0x00000020 + -0x270) = 0x161682d;
          auVar16 = runtime_slicebytetostring();
          if ((undefined1 *)((long)register0x00000020 + -0x214) < &DAT_00000018) {
                    /* WARNING: Subroutine does not return */
            *(undefined8 *)((long)register0x00000020 + -0x270) = 0x1617345;
            runtime_panicSliceAlen();
          }
          puVar10 = &DAT_01c41f06;
          *(undefined8 *)((long)register0x00000020 + -0x270) = 0x1616852;
          uVar2 = runtime_concatstring2(auVar16._0_8_,0x18,auVar16._8_8_,9);
        }
        else {
          uVar2 = *(undefined8 *)((long)register0x00000020 + -0x110);
        }
        *(undefined **)((long)register0x00000020 + -0x178) = puVar10;
        *(undefined8 *)((long)register0x00000020 + -0x110) = uVar2;
        uVar2 = *(undefined8 *)((long)register0x00000020 + -0xe0);
        *(undefined8 *)((long)register0x00000020 + -0x270) = 0x161687f;
        uVar5 = kiro2api_internal_logic_grok_CollectProcessor_filterContent();
        *(undefined8 *)((long)register0x00000020 + -0xe0) = uVar5;
        *(undefined8 *)((long)register0x00000020 + -0x150) = uVar2;
        if (*(long *)(*(long *)((long)register0x00000020 + 8) + 0x50) == 0) {
          lVar9 = 0;
          lVar13 = 0;
          lVar3 = 0;
        }
        else {
          *(undefined8 *)((long)register0x00000020 + -0x270) = 0x16168b5;
          plVar6 = (long *)kiro2api_internal_tokencount_UsageTracker_GetUsage();
          lVar9 = *plVar6;
          lVar13 = plVar6[1];
          lVar3 = lVar9 + lVar13;
        }
        *(long *)((long)register0x00000020 + -0x188) = lVar3;
        *(long *)((long)register0x00000020 + -0x148) = lVar13;
        *(long *)((long)register0x00000020 + -0x170) = lVar9;
        *(undefined8 *)((long)register0x00000020 + -0x270) = 0x16168e5;
        uVar2 = runtime_makemap_small();
        *(undefined8 *)((long)register0x00000020 + -0xb8) = uVar2;
        *(undefined8 *)((long)register0x00000020 + -0x270) = 0x1616905;
        uVar2 = runtime_convTstring();
        *(undefined8 *)((long)register0x00000020 + -0xc0) = uVar2;
        *(undefined8 *)((long)register0x00000020 + -0x270) = 0x161692d;
        auVar16 = runtime_mapassign_faststr(2);
        *auVar16._0_8_ = &DAT_0194e220;
        if (DAT_02e5e450 == 0) {
          uVar2 = *(undefined8 *)((long)register0x00000020 + -0xc0);
        }
        else {
          *(undefined8 *)((long)register0x00000020 + -0x270) = 0x1616955;
          auVar16 = runtime_gcWriteBarrier2();
          uVar2 = *(undefined8 *)((long)register0x00000020 + -0xc0);
          *in_R11 = uVar2;
          in_R11[1] = auVar16._8_8_;
        }
        *(undefined8 *)(auVar16._0_8_ + 8) = uVar2;
        *(undefined8 *)((long)register0x00000020 + -0x270) = 0x1616988;
        puVar4 = (undefined8 *)runtime_mapassign_faststr(6,uVar2,auVar16._8_8_,&DAT_01c3bc27);
        *puVar4 = &DAT_0194e220;
        if (DAT_02e5e450 != 0) {
          uVar2 = puVar4[1];
          *(undefined8 *)((long)register0x00000020 + -0x270) = 0x16169a5;
          puVar4 = (undefined8 *)runtime_gcWriteBarrier1();
          *in_R11 = uVar2;
        }
        puVar4[1] = &PTR_DAT_01f39830;
        *(undefined8 *)((long)register0x00000020 + -0x270) = 0x16169c5;
        uVar2 = runtime_convT64();
        *(undefined8 *)((long)register0x00000020 + -0xc0) = uVar2;
        *(undefined8 *)((long)register0x00000020 + -0x270) = 0x16169ed;
        puVar4 = (undefined8 *)runtime_mapassign_faststr(7);
        *puVar4 = &DAT_0194e3e0;
        if (DAT_02e5e450 == 0) {
          uVar2 = *(undefined8 *)((long)register0x00000020 + -0xc0);
        }
        else {
          uVar5 = puVar4[1];
          *(undefined8 *)((long)register0x00000020 + -0x270) = 0x1616a15;
          puVar4 = (undefined8 *)runtime_gcWriteBarrier2();
          uVar2 = *(undefined8 *)((long)register0x00000020 + -0xc0);
          *in_R11 = uVar2;
          in_R11[1] = uVar5;
        }
        puVar4[1] = uVar2;
        *(undefined8 *)((long)register0x00000020 + -0x270) = 0x1616a3c;
        uVar2 = runtime_convTstring();
        *(undefined8 *)((long)register0x00000020 + -0xc0) = uVar2;
        *(undefined8 *)((long)register0x00000020 + -0x270) = 0x1616a65;
        puVar4 = (undefined8 *)runtime_mapassign_faststr(5);
        *puVar4 = &DAT_0194e220;
        if (DAT_02e5e450 == 0) {
          uVar2 = *(undefined8 *)((long)register0x00000020 + -0xc0);
        }
        else {
          *(undefined8 *)((long)register0x00000020 + -0x270) = 0x1616a8b;
          auVar16 = runtime_gcWriteBarrier2();
          puVar4 = auVar16._0_8_;
          uVar2 = *(undefined8 *)((long)register0x00000020 + -0xc0);
          *in_R11 = uVar2;
          in_R11[1] = auVar16._8_8_;
        }
        puVar4[1] = uVar2;
        *(undefined8 *)((long)register0x00000020 + -0x270) = 0x1616ab3;
        uVar2 = runtime_convTstring();
        *(undefined8 *)((long)register0x00000020 + -0xc0) = uVar2;
        *(undefined8 *)((long)register0x00000020 + -0x270) = 0x1616adb;
        puVar4 = (undefined8 *)runtime_mapassign_faststr(0x12);
        *puVar4 = &DAT_0194e220;
        if (DAT_02e5e450 == 0) {
          uVar2 = *(undefined8 *)((long)register0x00000020 + -0xc0);
        }
        else {
          *(undefined8 *)((long)register0x00000020 + -0x270) = 0x1616b05;
          auVar16 = runtime_gcWriteBarrier2();
          puVar4 = auVar16._0_8_;
          uVar2 = *(undefined8 *)((long)register0x00000020 + -0xc0);
          *in_R11 = uVar2;
          in_R11[1] = auVar16._8_8_;
        }
        puVar4[1] = uVar2;
        *(undefined8 *)((long)register0x00000020 + -0x270) = 0x1616b1d;
        uVar2 = runtime_makemap_small();
        *(undefined8 *)((long)register0x00000020 + -200) = uVar2;
        *(undefined8 *)((long)register0x00000020 + -0x270) = 0x1616b45;
        puVar4 = (undefined8 *)runtime_mapassign_faststr(5);
        *puVar4 = &DAT_0194e460;
        if (DAT_02e5e450 != 0) {
          *(undefined8 *)((long)register0x00000020 + -0x270) = 0x1616b65;
          auVar16 = runtime_gcWriteBarrier1();
          puVar4 = auVar16._0_8_;
          *in_R11 = auVar16._8_8_;
        }
        puVar4[1] = &DAT_01f385c0;
        *(undefined8 *)((long)register0x00000020 + -0x270) = 0x1616b78;
        uVar2 = runtime_makemap_small();
        *(undefined8 *)((long)register0x00000020 + -0xd0) = uVar2;
        *(undefined8 *)((long)register0x00000020 + -0x270) = 0x1616b9b;
        puVar4 = (undefined8 *)runtime_mapassign_faststr(7);
        *puVar4 = 0;
        if (DAT_02e5e450 != 0) {
          *(undefined8 *)((long)register0x00000020 + -0x270) = 0x1616bb4;
          auVar16 = runtime_gcWriteBarrier1();
          puVar4 = auVar16._0_8_;
          *in_R11 = auVar16._8_8_;
        }
        puVar4[1] = 0;
        *(undefined8 *)((long)register0x00000020 + -0x270) = 0x1616bdf;
        puVar4 = (undefined8 *)runtime_mapassign_faststr(4);
        *puVar4 = &DAT_0194e220;
        if (DAT_02e5e450 != 0) {
          uVar2 = puVar4[1];
          *(undefined8 *)((long)register0x00000020 + -0x270) = 0x1616bfb;
          puVar4 = (undefined8 *)runtime_gcWriteBarrier1();
          *in_R11 = uVar2;
        }
        puVar4[1] = &PTR_DAT_01f39840;
        *(undefined8 *)((long)register0x00000020 + -0x270) = 0x1616c1e;
        uVar2 = runtime_convTstring();
        *(undefined8 *)((long)register0x00000020 + -0xc0) = uVar2;
        *(undefined8 *)((long)register0x00000020 + -0x270) = 0x1616c46;
        puVar4 = (undefined8 *)runtime_mapassign_faststr(7);
        *puVar4 = &DAT_0194e220;
        if (DAT_02e5e450 == 0) {
          uVar2 = *(undefined8 *)((long)register0x00000020 + -0xc0);
        }
        else {
          *(undefined8 *)((long)register0x00000020 + -0x270) = 0x1616c6c;
          auVar16 = runtime_gcWriteBarrier2();
          puVar4 = auVar16._0_8_;
          uVar2 = *(undefined8 *)((long)register0x00000020 + -0xc0);
          *in_R11 = uVar2;
          in_R11[1] = auVar16._8_8_;
        }
        puVar4[1] = uVar2;
        *(undefined8 *)((long)register0x00000020 + -0x270) = 0x1616c90;
        uVar2 = runtime_convTslice();
        *(undefined8 *)((long)register0x00000020 + -0xc0) = uVar2;
        *(undefined8 *)((long)register0x00000020 + -0x270) = 0x1616cb8;
        puVar4 = (undefined8 *)runtime_mapassign_faststr(0xb);
        auVar15._8_8_ = &DAT_0192e960;
        auVar15._0_8_ = puVar4;
        *puVar4 = &DAT_0192e960;
        if (DAT_02e5e450 == 0) {
          uVar2 = *(undefined8 *)((long)register0x00000020 + -0xc0);
        }
        else {
          *(undefined8 *)((long)register0x00000020 + -0x270) = 0x1616cde;
          auVar15 = runtime_gcWriteBarrier2();
          uVar2 = *(undefined8 *)((long)register0x00000020 + -0xc0);
          *in_R11 = uVar2;
          in_R11[1] = auVar15._8_8_;
        }
        *(undefined8 *)(auVar15._0_8_ + 8) = uVar2;
        *(undefined8 *)((long)register0x00000020 + -0x270) = 0x1616d11;
        puVar4 = (undefined8 *)runtime_mapassign_faststr(7,uVar2,auVar15._8_8_,&DAT_01c3dd0c);
        *puVar4 = &DAT_01a233a0;
        if (DAT_02e5e450 == 0) {
          uVar2 = *(undefined8 *)((long)register0x00000020 + -0xd0);
        }
        else {
          uVar5 = puVar4[1];
          *(undefined8 *)((long)register0x00000020 + -0x270) = 0x1616d37;
          puVar4 = (undefined8 *)runtime_gcWriteBarrier2();
          uVar2 = *(undefined8 *)((long)register0x00000020 + -0xd0);
          *in_R11 = uVar2;
          in_R11[1] = uVar5;
        }
        puVar4[1] = uVar2;
        *(undefined8 *)((long)register0x00000020 + -0x270) = 0x1616d66;
        puVar4 = (undefined8 *)runtime_mapassign_faststr(0xd);
        *puVar4 = &DAT_0194e220;
        if (DAT_02e5e450 != 0) {
          uVar2 = puVar4[1];
          *(undefined8 *)((long)register0x00000020 + -0x270) = 0x1616d85;
          puVar4 = (undefined8 *)runtime_gcWriteBarrier1();
          *in_R11 = uVar2;
        }
        puVar4[1] = &PTR_DAT_01f39810;
        *(undefined8 *)((long)register0x00000020 + -0x270) = 0x1616d9f;
        puVar4 = (undefined8 *)runtime_newobject();
        if (DAT_02e5e450 == 0) {
          uVar2 = *(undefined8 *)((long)register0x00000020 + -200);
        }
        else {
          *(undefined8 *)((long)register0x00000020 + -0x270) = 0x1616db7;
          puVar4 = (undefined8 *)runtime_gcWriteBarrier1();
          uVar2 = *(undefined8 *)((long)register0x00000020 + -200);
          *in_R11 = uVar2;
        }
        *puVar4 = uVar2;
        *(undefined8 *)((long)register0x00000020 + -0x270) = 0x1616dd2;
        uVar2 = runtime_convTslice();
        *(undefined8 *)((long)register0x00000020 + -0xc0) = uVar2;
        *(undefined8 *)((long)register0x00000020 + -0x270) = 0x1616dfa;
        puVar4 = (undefined8 *)runtime_mapassign_faststr(7);
        *puVar4 = &DAT_0192a2e0;
        if (DAT_02e5e450 == 0) {
          uVar2 = *(undefined8 *)((long)register0x00000020 + -0xc0);
        }
        else {
          uVar5 = puVar4[1];
          *(undefined8 *)((long)register0x00000020 + -0x270) = 0x1616e25;
          puVar4 = (undefined8 *)runtime_gcWriteBarrier2();
          uVar2 = *(undefined8 *)((long)register0x00000020 + -0xc0);
          *in_R11 = uVar2;
          in_R11[1] = uVar5;
        }
        puVar4[1] = uVar2;
        *(undefined8 *)((long)register0x00000020 + -0x270) = 0x1616e3d;
        uVar2 = runtime_makemap_small();
        *(undefined8 *)((long)register0x00000020 + -200) = uVar2;
        *(undefined8 *)((long)register0x00000020 + -0x270) = 0x1616e52;
        uVar2 = runtime_convT64();
        *(undefined8 *)((long)register0x00000020 + -0xc0) = uVar2;
        *(undefined8 *)((long)register0x00000020 + -0x270) = 0x1616e7a;
        puVar4 = (undefined8 *)runtime_mapassign_faststr(0xd);
        *puVar4 = &DAT_0194e460;
        if (DAT_02e5e450 == 0) {
          uVar2 = *(undefined8 *)((long)register0x00000020 + -0xc0);
        }
        else {
          *(undefined8 *)((long)register0x00000020 + -0x270) = 0x1616ea5;
          auVar16 = runtime_gcWriteBarrier2();
          puVar4 = auVar16._0_8_;
          uVar2 = *(undefined8 *)((long)register0x00000020 + -0xc0);
          *in_R11 = uVar2;
          in_R11[1] = auVar16._8_8_;
        }
        puVar4[1] = uVar2;
        *(undefined8 *)((long)register0x00000020 + -0x270) = 0x1616ec5;
        uVar2 = runtime_convT64();
        *(undefined8 *)((long)register0x00000020 + -0xc0) = uVar2;
        *(undefined8 *)((long)register0x00000020 + -0x270) = 0x1616eed;
        puVar4 = (undefined8 *)runtime_mapassign_faststr(0x11);
        *puVar4 = &DAT_0194e460;
        if (DAT_02e5e450 == 0) {
          uVar2 = *(undefined8 *)((long)register0x00000020 + -0xc0);
        }
        else {
          *(undefined8 *)((long)register0x00000020 + -0x270) = 0x1616f15;
          auVar16 = runtime_gcWriteBarrier2();
          puVar4 = auVar16._0_8_;
          uVar2 = *(undefined8 *)((long)register0x00000020 + -0xc0);
          *in_R11 = uVar2;
          in_R11[1] = auVar16._8_8_;
        }
        puVar4[1] = uVar2;
        *(undefined8 *)((long)register0x00000020 + -0x270) = 0x1616f35;
        uVar2 = runtime_convT64();
        *(undefined8 *)((long)register0x00000020 + -0xc0) = uVar2;
        *(undefined8 *)((long)register0x00000020 + -0x270) = 0x1616f5d;
        puVar4 = (undefined8 *)runtime_mapassign_faststr(0xc);
        *puVar4 = &DAT_0194e460;
        if (DAT_02e5e450 == 0) {
          uVar2 = *(undefined8 *)((long)register0x00000020 + -0xc0);
        }
        else {
          *(undefined8 *)((long)register0x00000020 + -0x270) = 0x1616f85;
          auVar16 = runtime_gcWriteBarrier2();
          puVar4 = auVar16._0_8_;
          uVar2 = *(undefined8 *)((long)register0x00000020 + -0xc0);
          *in_R11 = uVar2;
          in_R11[1] = auVar16._8_8_;
        }
        puVar4[1] = uVar2;
        *(undefined8 *)((long)register0x00000020 + -0x270) = 0x1616f9d;
        uVar2 = runtime_makemap_small();
        *(undefined8 *)((long)register0x00000020 + -0xd0) = uVar2;
        *(undefined8 *)((long)register0x00000020 + -0x270) = 0x1616fc5;
        puVar4 = (undefined8 *)runtime_mapassign_faststr(0xd);
        *puVar4 = &DAT_0194e460;
        if (DAT_02e5e450 != 0) {
          *(undefined8 *)((long)register0x00000020 + -0x270) = 0x1616fe5;
          auVar16 = runtime_gcWriteBarrier1();
          puVar4 = auVar16._0_8_;
          *in_R11 = auVar16._8_8_;
        }
        puVar4[1] = &DAT_01f385c0;
        *(undefined8 *)((long)register0x00000020 + -0x270) = 0x1617005;
        uVar2 = runtime_convT64();
        *(undefined8 *)((long)register0x00000020 + -0xc0) = uVar2;
        *(undefined8 *)((long)register0x00000020 + -0x270) = 0x161702d;
        auVar16 = runtime_mapassign_faststr(0xb);
        *auVar16._0_8_ = &DAT_0194e460;
        if (DAT_02e5e450 == 0) {
          uVar2 = *(undefined8 *)((long)register0x00000020 + -0xc0);
        }
        else {
          *(undefined8 *)((long)register0x00000020 + -0x270) = 0x1617055;
          auVar16 = runtime_gcWriteBarrier2();
          uVar2 = *(undefined8 *)((long)register0x00000020 + -0xc0);
          *in_R11 = uVar2;
          in_R11[1] = auVar16._8_8_;
        }
        *(undefined8 *)(auVar16._0_8_ + 8) = uVar2;
        *(undefined8 *)((long)register0x00000020 + -0x270) = 0x1617088;
        puVar4 = (undefined8 *)runtime_mapassign_faststr(0xc,uVar2,auVar16._8_8_,&DAT_01c48064);
        *puVar4 = &DAT_0194e460;
        if (DAT_02e5e450 != 0) {
          uVar2 = puVar4[1];
          *(undefined8 *)((long)register0x00000020 + -0x270) = 0x16170a5;
          puVar4 = (undefined8 *)runtime_gcWriteBarrier1();
          *in_R11 = uVar2;
        }
        puVar4[1] = &DAT_01f385c0;
        *(undefined8 *)((long)register0x00000020 + -0x270) = 0x16170d3;
        puVar4 = (undefined8 *)runtime_mapassign_faststr(0xc);
        *puVar4 = &DAT_0194e460;
        if (DAT_02e5e450 != 0) {
          uVar2 = puVar4[1];
          *(undefined8 *)((long)register0x00000020 + -0x270) = 0x16170ef;
          puVar4 = (undefined8 *)runtime_gcWriteBarrier1();
          *in_R11 = uVar2;
        }
        puVar4[1] = &DAT_01f385c0;
        *(undefined8 *)((long)register0x00000020 + -0x270) = 0x161711d;
        puVar4 = (undefined8 *)runtime_mapassign_faststr(0x15);
        *puVar4 = &DAT_01a233a0;
        if (DAT_02e5e450 == 0) {
          uVar2 = *(undefined8 *)((long)register0x00000020 + -0xd0);
        }
        else {
          uVar5 = puVar4[1];
          *(undefined8 *)((long)register0x00000020 + -0x270) = 0x1617145;
          puVar4 = (undefined8 *)runtime_gcWriteBarrier2();
          uVar2 = *(undefined8 *)((long)register0x00000020 + -0xd0);
          *in_R11 = uVar2;
          in_R11[1] = uVar5;
        }
        puVar4[1] = uVar2;
        *(undefined8 *)((long)register0x00000020 + -0x270) = 0x161715d;
        uVar2 = runtime_makemap_small();
        *(undefined8 *)((long)register0x00000020 + -0xd0) = uVar2;
        *(undefined8 *)((long)register0x00000020 + -0x270) = 0x1617172;
        uVar2 = runtime_convT64();
        *(undefined8 *)((long)register0x00000020 + -0xc0) = uVar2;
        *(undefined8 *)((long)register0x00000020 + -0x270) = 0x161719a;
        auVar16 = runtime_mapassign_faststr(0xb);
        *auVar16._0_8_ = &DAT_0194e460;
        if (DAT_02e5e450 == 0) {
          uVar2 = *(undefined8 *)((long)register0x00000020 + -0xc0);
        }
        else {
          *(undefined8 *)((long)register0x00000020 + -0x270) = 0x16171c5;
          auVar16 = runtime_gcWriteBarrier2();
          uVar2 = *(undefined8 *)((long)register0x00000020 + -0xc0);
          *in_R11 = uVar2;
          in_R11[1] = auVar16._8_8_;
        }
        *(undefined8 *)(auVar16._0_8_ + 8) = uVar2;
        *(undefined8 *)((long)register0x00000020 + -0x270) = 0x16171f8;
        puVar4 = (undefined8 *)runtime_mapassign_faststr(0xc,uVar2,auVar16._8_8_,&DAT_01c48064);
        *puVar4 = &DAT_0194e460;
        if (DAT_02e5e450 != 0) {
          uVar2 = puVar4[1];
          *(undefined8 *)((long)register0x00000020 + -0x270) = 0x1617214;
          puVar4 = (undefined8 *)runtime_gcWriteBarrier1();
          *in_R11 = uVar2;
        }
        puVar4[1] = &DAT_01f385c0;
        *(undefined8 *)((long)register0x00000020 + -0x270) = 0x1617245;
        puVar4 = (undefined8 *)runtime_mapassign_faststr(0x10);
        *puVar4 = &DAT_0194e460;
        if (DAT_02e5e450 != 0) {
          *(undefined8 *)((long)register0x00000020 + -0x270) = 0x1617265;
          auVar16 = runtime_gcWriteBarrier1();
          puVar4 = auVar16._0_8_;
          *in_R11 = auVar16._8_8_;
        }
        puVar4[1] = &DAT_01f385c0;
        *(undefined8 *)((long)register0x00000020 + -0x270) = 0x1617293;
        puVar4 = (undefined8 *)runtime_mapassign_faststr(0x19);
        *puVar4 = &DAT_01a233a0;
        if (DAT_02e5e450 == 0) {
          uVar2 = *(undefined8 *)((long)register0x00000020 + -0xd0);
        }
        else {
          uVar5 = puVar4[1];
          *(undefined8 *)((long)register0x00000020 + -0x270) = 0x16172b9;
          puVar4 = (undefined8 *)runtime_gcWriteBarrier2();
          uVar2 = *(undefined8 *)((long)register0x00000020 + -0xd0);
          *in_R11 = uVar2;
          in_R11[1] = uVar5;
        }
        puVar4[1] = uVar2;
        *(undefined8 *)((long)register0x00000020 + -0x270) = 0x16172e8;
        puVar4 = (undefined8 *)runtime_mapassign_faststr(5);
        *puVar4 = &DAT_01a233a0;
        if (DAT_02e5e450 == 0) {
          uVar2 = *(undefined8 *)((long)register0x00000020 + -200);
        }
        else {
          *(undefined8 *)((long)register0x00000020 + -0x270) = 0x161730e;
          auVar16 = runtime_gcWriteBarrier2();
          puVar4 = auVar16._0_8_;
          uVar2 = *(undefined8 *)((long)register0x00000020 + -200);
          *in_R11 = uVar2;
          in_R11[1] = auVar16._8_8_;
        }
        puVar4[1] = uVar2;
        return *(undefined8 *)((long)register0x00000020 + -0xb8);
      }
      unaff_RBX = &PTR_DAT_01f39ae0;
      *(undefined8 *)((long)register0x00000020 + -0x270) = 0x1617545;
      in_RAX = runtime_gopanic();
    }
    *(undefined8 *)(puVar11 + 8) = in_RAX;
    *(undefined ***)(puVar11 + 0x10) = unaff_RBX;
    *(undefined8 *)(puVar11 + 0x18) = in_RCX;
    *(undefined8 *)(puVar11 + -8) = 0x161755a;
    runtime_morestack_noctxt();
    in_RAX = *(undefined8 *)(puVar11 + 8);
    unaff_RBX = *(undefined ***)(puVar11 + 0x10);
    in_RCX = *(undefined8 *)(puVar11 + 0x18);
    register0x00000020 = (BADSPACEBASE *)puVar11;
  } while( true );
}




// === grok.BuildChatPayload @ 0x1606520 ===

undefined8
grok_BuildChatPayload
          (undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
          undefined8 param_5,undefined8 param_6,long param_7,long param_8,undefined8 param_9,
          undefined8 *param_10,long param_11)

{
  undefined8 uVar1;
  undefined8 *puVar2;
  undefined8 uVar3;
  undefined8 uVar4;
  undefined8 uVar5;
  ulong uVar6;
  long lVar7;
  long unaff_R14;
  undefined1 auVar8 [16];
  undefined8 uStack0000000000000048;
  undefined8 uStack0000000000000050;
  undefined8 uStack0000000000000058;
  undefined8 uStack0000000000000060;
  
  uStack0000000000000048 = param_4;
  uStack0000000000000058 = param_2;
  uStack0000000000000050 = param_1;
  uStack0000000000000060 = param_5;
  while (&stack0x00000000 <= *(undefined1 **)(unaff_R14 + 0x10)) {
    runtime_morestack_noctxt();
  }
  if (param_7 == 0) {
    lVar7 = 0;
    uVar6 = 0;
  }
  else {
    if (param_8 == 0) {
      uVar6 = 0;
      lVar7 = 0;
    }
    else {
      uVar6 = 0;
      runtime_growslice(param_8,&DAT_0194e220);
      lVar7 = param_8;
    }
    runtime_typedslicecopy(param_7,param_8,param_7,lVar7);
  }
  if (param_10 != (undefined8 *)0x0) {
    if (uVar6 < (ulong)(lVar7 + param_11)) {
      runtime_growslice(param_11,&DAT_0194e220,lVar7,uVar6,uStack0000000000000060);
    }
    runtime_typedslicecopy(param_10,param_11,(long)(lVar7 - uVar6) >> 0x3f & lVar7 << 4,
                 (lVar7 + param_11) - lVar7);
  }
  uVar1 = runtime_makemap();
  puVar2 = (undefined8 *)runtime_mapassign_faststr(9);
  *puVar2 = &DAT_0194e620;
  if (DAT_02e5e450 != 0) {
    uVar3 = puVar2[1];
    puVar2 = (undefined8 *)runtime_gcWriteBarrier1();
    *param_10 = uVar3;
  }
  puVar2[1] = &DAT_01f8a688;
  uVar3 = runtime_convTstring();
  puVar2 = (undefined8 *)runtime_mapassign_faststr(9);
  *puVar2 = &DAT_0194e220;
  if (DAT_02e5e450 != 0) {
    auVar8 = runtime_gcWriteBarrier2();
    puVar2 = auVar8._0_8_;
    *param_10 = uVar3;
    param_10[1] = auVar8._8_8_;
  }
  puVar2[1] = uVar3;
  uVar3 = runtime_convTstring();
  puVar2 = (undefined8 *)runtime_mapassign_faststr(9);
  *puVar2 = &DAT_0194e220;
  if (DAT_02e5e450 != 0) {
    auVar8 = runtime_gcWriteBarrier2();
    puVar2 = auVar8._0_8_;
    *param_10 = uVar3;
    param_10[1] = auVar8._8_8_;
  }
  puVar2[1] = uVar3;
  uVar3 = runtime_convTstring();
  puVar2 = (undefined8 *)runtime_mapassign_faststr(7);
  *puVar2 = &DAT_0194e220;
  if (DAT_02e5e450 != 0) {
    auVar8 = runtime_gcWriteBarrier2();
    puVar2 = auVar8._0_8_;
    *param_10 = uVar3;
    param_10[1] = auVar8._8_8_;
  }
  puVar2[1] = uVar3;
  uVar3 = runtime_convTslice();
  puVar2 = (undefined8 *)runtime_mapassign_faststr(0xf);
  *puVar2 = &DAT_0192e8e0;
  if (DAT_02e5e450 != 0) {
    uVar4 = puVar2[1];
    puVar2 = (undefined8 *)runtime_gcWriteBarrier2();
    *param_10 = uVar3;
    param_10[1] = uVar4;
  }
  puVar2[1] = uVar3;
  uVar3 = runtime_convTslice();
  puVar2 = (undefined8 *)runtime_mapassign_faststr(0x10);
  auVar8._8_8_ = &DAT_0192e8e0;
  auVar8._0_8_ = puVar2;
  *puVar2 = &DAT_0192e8e0;
  if (DAT_02e5e450 != 0) {
    auVar8 = runtime_gcWriteBarrier2();
    *param_10 = uVar3;
    param_10[1] = auVar8._8_8_;
  }
  *(undefined8 *)(auVar8._0_8_ + 8) = uVar3;
  puVar2 = (undefined8 *)runtime_mapassign_faststr(0xd,uVar3,auVar8._8_8_,&DAT_01c49b0a);
  *puVar2 = &DAT_0194e620;
  if (DAT_02e5e450 != 0) {
    uVar3 = puVar2[1];
    puVar2 = (undefined8 *)runtime_gcWriteBarrier1();
    *param_10 = uVar3;
  }
  puVar2[1] = &DAT_01f8a680;
  puVar2 = (undefined8 *)runtime_mapassign_faststr(0x15);
  *puVar2 = &DAT_0194e620;
  if (DAT_02e5e450 != 0) {
    uVar3 = puVar2[1];
    puVar2 = (undefined8 *)runtime_gcWriteBarrier1();
    *param_10 = uVar3;
  }
  puVar2[1] = &DAT_01f8a688;
  puVar2 = (undefined8 *)runtime_mapassign_faststr(0x10);
  *puVar2 = &DAT_0194e620;
  if (DAT_02e5e450 != 0) {
    uVar3 = puVar2[1];
    puVar2 = (undefined8 *)runtime_gcWriteBarrier1();
    *param_10 = uVar3;
  }
  puVar2[1] = &DAT_01f8a680;
  puVar2 = (undefined8 *)runtime_mapassign_faststr(0x19);
  *puVar2 = &DAT_0194e620;
  if (DAT_02e5e450 != 0) {
    uVar3 = puVar2[1];
    puVar2 = (undefined8 *)runtime_gcWriteBarrier1();
    *param_10 = uVar3;
  }
  puVar2[1] = &DAT_01f8a680;
  puVar2 = (undefined8 *)runtime_mapassign_faststr(0x14);
  *puVar2 = &DAT_0194e620;
  if (DAT_02e5e450 != 0) {
    uVar3 = puVar2[1];
    puVar2 = (undefined8 *)runtime_gcWriteBarrier1();
    *param_10 = uVar3;
  }
  puVar2[1] = &DAT_01f8a688;
  puVar2 = (undefined8 *)runtime_mapassign_faststr(0x14);
  *puVar2 = &DAT_0194e460;
  if (DAT_02e5e450 != 0) {
    uVar3 = puVar2[1];
    puVar2 = (undefined8 *)runtime_gcWriteBarrier1();
    *param_10 = uVar3;
  }
  puVar2[1] = &DAT_01f34d38;
  puVar2 = (undefined8 *)runtime_mapassign_faststr(0xc);
  *puVar2 = &DAT_0194e620;
  if (DAT_02e5e450 != 0) {
    uVar3 = puVar2[1];
    puVar2 = (undefined8 *)runtime_gcWriteBarrier1();
    *param_10 = uVar3;
  }
  puVar2[1] = &DAT_01f8a680;
  uVar3 = runtime_makemap_small();
  auVar8 = runtime_mapassign_faststr(0xd);
  *auVar8._0_8_ = &DAT_01a233a0;
  if (DAT_02e5e450 != 0) {
    auVar8 = runtime_gcWriteBarrier2();
    *param_10 = uVar3;
    param_10[1] = auVar8._8_8_;
  }
  *(undefined8 *)(auVar8._0_8_ + 8) = uVar3;
  puVar2 = (undefined8 *)runtime_mapassign_faststr(0x10,uVar3,auVar8._8_8_,&DAT_01c4efc3);
  *puVar2 = &DAT_0194e620;
  if (DAT_02e5e450 != 0) {
    uVar3 = puVar2[1];
    puVar2 = (undefined8 *)runtime_gcWriteBarrier1();
    *param_10 = uVar3;
  }
  puVar2[1] = &DAT_01f8a688;
  puVar2 = (undefined8 *)runtime_mapassign_faststr(0x11);
  *puVar2 = &DAT_0194e620;
  if (DAT_02e5e450 != 0) {
    uVar3 = puVar2[1];
    puVar2 = (undefined8 *)runtime_gcWriteBarrier1();
    *param_10 = uVar3;
  }
  puVar2[1] = &DAT_01f8a688;
  puVar2 = (undefined8 *)runtime_mapassign_faststr(0xb);
  *puVar2 = &DAT_0194e620;
  if (DAT_02e5e450 != 0) {
    uVar3 = puVar2[1];
    puVar2 = (undefined8 *)runtime_gcWriteBarrier1();
    *param_10 = uVar3;
  }
  puVar2[1] = &DAT_01f8a680;
  puVar2 = (undefined8 *)runtime_mapassign_faststr(0x14);
  *puVar2 = &DAT_0194e620;
  if (DAT_02e5e450 != 0) {
    uVar3 = puVar2[1];
    puVar2 = (undefined8 *)runtime_gcWriteBarrier1();
    *param_10 = uVar3;
  }
  puVar2[1] = &DAT_01f8a680;
  puVar2 = (undefined8 *)runtime_mapassign_faststr(0xd);
  *puVar2 = &DAT_0194e620;
  if (DAT_02e5e450 != 0) {
    uVar3 = puVar2[1];
    puVar2 = (undefined8 *)runtime_gcWriteBarrier1();
    *param_10 = uVar3;
  }
  puVar2[1] = &DAT_01f8a680;
  puVar2 = (undefined8 *)runtime_mapassign_faststr(0xf);
  *puVar2 = &DAT_0194e620;
  if (DAT_02e5e450 != 0) {
    uVar3 = puVar2[1];
    puVar2 = (undefined8 *)runtime_gcWriteBarrier1();
    *param_10 = uVar3;
  }
  puVar2[1] = &DAT_01f8a680;
  puVar2 = (undefined8 *)runtime_mapassign_faststr(0xb);
  *puVar2 = &DAT_0194e620;
  if (DAT_02e5e450 != 0) {
    uVar3 = puVar2[1];
    puVar2 = (undefined8 *)runtime_gcWriteBarrier1();
    *param_10 = uVar3;
  }
  puVar2[1] = &DAT_01f8a680;
  puVar2 = (undefined8 *)runtime_mapassign_faststr(0x1b);
  *puVar2 = &DAT_0194e620;
  if (DAT_02e5e450 != 0) {
    uVar3 = puVar2[1];
    puVar2 = (undefined8 *)runtime_gcWriteBarrier1();
    *param_10 = uVar3;
  }
  puVar2[1] = &DAT_01f8a680;
  uVar3 = runtime_makemap_small();
  uVar4 = runtime_makemap_small();
  uVar5 = runtime_makemap_small();
  auVar8 = runtime_mapassign_faststr(8);
  *auVar8._0_8_ = &DAT_01a233a0;
  if (DAT_02e5e450 != 0) {
    auVar8 = runtime_gcWriteBarrier2();
    *param_10 = uVar5;
    param_10[1] = auVar8._8_8_;
  }
  *(undefined8 *)(auVar8._0_8_ + 8) = uVar5;
  puVar2 = (undefined8 *)runtime_mapassign_faststr(0x13,uVar5,auVar8._8_8_,&DAT_01c54ea1);
  *puVar2 = &DAT_01a233a0;
  if (DAT_02e5e450 != 0) {
    uVar5 = puVar2[1];
    puVar2 = (undefined8 *)runtime_gcWriteBarrier2();
    *param_10 = uVar4;
    param_10[1] = uVar5;
  }
  puVar2[1] = uVar4;
  uVar4 = runtime_makemap_small();
  uVar5 = runtime_convTstring();
  auVar8 = runtime_mapassign_faststr(7);
  *auVar8._0_8_ = &DAT_0194e220;
  if (DAT_02e5e450 != 0) {
    auVar8 = runtime_gcWriteBarrier2();
    *param_10 = uVar5;
    param_10[1] = auVar8._8_8_;
  }
  *(undefined8 *)(auVar8._0_8_ + 8) = uVar5;
  puVar2 = (undefined8 *)runtime_mapassign_faststr(0x13,uVar5,auVar8._8_8_,&DAT_01c54eb4);
  *puVar2 = &DAT_01a233a0;
  if (DAT_02e5e450 != 0) {
    uVar5 = puVar2[1];
    puVar2 = (undefined8 *)runtime_gcWriteBarrier2();
    *param_10 = uVar4;
    param_10[1] = uVar5;
  }
  puVar2[1] = uVar4;
  puVar2 = (undefined8 *)runtime_mapassign_faststr(0x10);
  *puVar2 = &DAT_01a233a0;
  if (DAT_02e5e450 != 0) {
    uVar4 = puVar2[1];
    puVar2 = (undefined8 *)runtime_gcWriteBarrier2();
    *param_10 = uVar3;
    param_10[1] = uVar4;
  }
  puVar2[1] = uVar3;
  uVar3 = runtime_makemap_small();
  puVar2 = (undefined8 *)runtime_mapassign_faststr(0xf);
  *puVar2 = &DAT_0194e620;
  if (DAT_02e5e450 != 0) {
    auVar8 = runtime_gcWriteBarrier1();
    puVar2 = auVar8._0_8_;
    *param_10 = auVar8._8_8_;
  }
  puVar2[1] = &DAT_01f8a680;
  puVar2 = (undefined8 *)runtime_mapassign_faststr(0x10);
  *puVar2 = &DAT_0194e460;
  if (DAT_02e5e450 != 0) {
    uVar4 = puVar2[1];
    puVar2 = (undefined8 *)runtime_gcWriteBarrier1();
    *param_10 = uVar4;
  }
  puVar2[1] = &DAT_01f34d38;
  puVar2 = (undefined8 *)runtime_mapassign_faststr(0xb);
  *puVar2 = &DAT_0194e460;
  if (DAT_02e5e450 != 0) {
    uVar4 = puVar2[1];
    puVar2 = (undefined8 *)runtime_gcWriteBarrier1();
    *param_10 = uVar4;
  }
  puVar2[1] = &DAT_01f38730;
  puVar2 = (undefined8 *)runtime_mapassign_faststr(0xc);
  *puVar2 = &DAT_0194e460;
  if (DAT_02e5e450 != 0) {
    uVar4 = puVar2[1];
    puVar2 = (undefined8 *)runtime_gcWriteBarrier1();
    *param_10 = uVar4;
  }
  puVar2[1] = &DAT_01f38738;
  puVar2 = (undefined8 *)runtime_mapassign_faststr(0xd);
  *puVar2 = &DAT_0194e460;
  if (DAT_02e5e450 != 0) {
    uVar4 = puVar2[1];
    puVar2 = (undefined8 *)runtime_gcWriteBarrier1();
    *param_10 = uVar4;
  }
  puVar2[1] = &DAT_01f38730;
  puVar2 = (undefined8 *)runtime_mapassign_faststr(0xe);
  *puVar2 = &DAT_0194e460;
  if (DAT_02e5e450 != 0) {
    auVar8 = runtime_gcWriteBarrier1();
    puVar2 = auVar8._0_8_;
    *param_10 = auVar8._8_8_;
  }
  puVar2[1] = &DAT_01f38740;
  puVar2 = (undefined8 *)runtime_mapassign_faststr(0xd);
  *puVar2 = &DAT_01a233a0;
  if (DAT_02e5e450 != 0) {
    uVar4 = puVar2[1];
    puVar2 = (undefined8 *)runtime_gcWriteBarrier2();
    *param_10 = uVar3;
    param_10[1] = uVar4;
  }
  puVar2[1] = uVar3;
  return uVar1;
}




// === grok.extractMessages @ 0x1603860 ===

undefined8 grok_extractMessages(char param_1)

{
  undefined8 uVar1;
  undefined8 *in_RAX;
  undefined8 uVar2;
  undefined8 *puVar3;
  ulong uVar4;
  undefined8 *puVar5;
  long lVar6;
  undefined8 *puVar7;
  uint uVar8;
  ulong uVar9;
  uint uVar10;
  ulong uVar11;
  long lVar12;
  long unaff_RBX;
  ulong uVar13;
  ulong uVar14;
  undefined8 *puVar15;
  ulong uVar16;
  ulong uVar17;
  long *plVar18;
  long lVar19;
  undefined8 *puVar20;
  long unaff_R14;
  undefined8 in_XMM15_Qa;
  undefined8 in_XMM15_Qb;
  undefined1 auVar21 [16];
  undefined1 auVar22 [16];
  undefined1 auVar23 [16];
  undefined1 auVar24 [16];
  undefined1 auVar25 [12];
  undefined8 *puStack0000000000000018;
  char cStack0000000000000030;
  ulong uStack_1e0;
  ulong uStack_1d8;
  ulong uStack_1d0;
  undefined8 *puStack_1c8;
  undefined8 *puStack_1c0;
  ulong uStack_1b8;
  ulong uStack_1b0;
  ulong uStack_1a8;
  ulong uStack_1a0;
  ulong uStack_198;
  long lStack_190;
  long lStack_188;
  long lStack_180;
  ulong uStack_178;
  undefined8 *puStack_170;
  undefined8 *puStack_168;
  ulong uStack_160;
  ulong uStack_158;
  undefined8 *puStack_150;
  ulong uStack_148;
  ulong uStack_140;
  undefined8 *puStack_138;
  ulong uStack_130;
  long lStack_128;
  undefined8 uStack_120;
  undefined8 uStack_118;
  undefined8 *puStack_110;
  undefined8 uStack_108;
  undefined8 *puStack_100;
  undefined8 uStack_f8;
  long lStack_f0;
  undefined8 uStack_e8;
  long lStack_e0;
  undefined8 *puStack_d8;
  undefined8 uStack_d0;
  undefined8 uStack_c8;
  undefined8 uStack_c0;
  undefined8 uStack_b8;
  undefined8 uStack_b0;
  undefined8 uStack_a8;
  undefined8 uStack_a0;
  undefined8 uStack_98;
  undefined8 uStack_90;
  undefined8 uStack_88;
  undefined8 uStack_80;
  undefined8 uStack_78;
  undefined8 uStack_70;
  undefined8 uStack_68;
  undefined8 uStack_60;
  undefined8 *puStack_58;
  undefined8 uStack_50;
  undefined8 *puStack_48;
  undefined8 uStack_40;
  long lStack_38;
  undefined8 *puStack_30;
  undefined8 uStack_28;
  long lStack_20;
  undefined8 uStack_18;
  undefined8 *puStack_10;
  
  puStack0000000000000018 = in_RAX;
  cStack0000000000000030 = param_1;
  while (&uStack_1d0 <= *(ulong **)(unaff_R14 + 0x10)) {
    runtime_morestack_noctxt();
  }
  uVar11 = 0;
  puVar5 = (undefined8 *)0x0;
  uVar13 = 0;
  uVar14 = 0;
  puVar20 = (undefined8 *)0x0;
  puVar3 = (undefined8 *)0x0;
  uVar9 = 0;
  lVar6 = 0;
  lStack_f0 = 0;
  uVar16 = 0;
  uVar8 = 0;
  while (uVar17 = uVar11, puStack_1c8 = puVar20, puStack_1c0 = puVar3, uStack_1b0 = uVar14,
        uStack_1a8 = uVar9, uStack_1a0 = uVar11, lStack_e0 = lVar6, 0 < unaff_RBX) {
    puStack_10 = puStack0000000000000018;
    puVar7 = (undefined8 *)puStack0000000000000018[2];
    uStack_18 = *puStack0000000000000018;
    uStack_130 = puStack0000000000000018[1];
    uVar17 = uVar16;
    uStack_198 = uVar13;
    lStack_128 = unaff_RBX;
    puStack_d8 = puVar5;
    uVar10 = uVar8;
    if (puVar7 == (undefined8 *)0x0) {
      uStack_1d8 = 0;
      puStack_100 = (undefined8 *)0x0;
      uStack_1e0 = 0;
    }
    else {
      puVar15 = (undefined8 *)puStack0000000000000018[3];
      if (*(int *)(puVar7 + 2) == -0xd99de8a) {
        if (puVar7 == &DAT_0192e960) {
          puVar7 = (undefined8 *)*puVar15;
          uVar4 = puVar15[1];
          uStack_1d8 = 0;
          puStack_100 = (undefined8 *)0x0;
          uStack_1e0 = 0;
          for (; 0 < (long)uVar4; uVar4 = uVar4 - 1) {
            if ((undefined8 *)*puVar7 == &DAT_01a233a0) {
              uStack_f8 = puVar7[1];
              uStack_178 = uVar14;
              puStack_170 = puVar20;
              puStack_168 = puVar3;
              uStack_160 = uVar9;
              uStack_158 = uVar4;
              lStack_38 = lVar6;
              puStack_30 = puVar7;
              puVar5 = (undefined8 *)runtime_mapaccess1_faststr(4,puVar5,&DAT_01a233a0,&DAT_01c397aa);
              if ((undefined8 *)*puVar5 == &DAT_0194e220) {
                plVar18 = *(long **)puVar5[1];
                lVar12 = ((undefined8 *)puVar5[1])[1];
              }
              else {
                lVar12 = 0;
                plVar18 = (long *)0x0;
              }
              lVar6 = lStack_38;
              uVar9 = uStack_160;
              puVar3 = puStack_168;
              puVar15 = puStack_170;
              uVar14 = uStack_178;
              if (lVar12 == 4) {
                if ((int)*plVar18 == 0x656c6966) {
                  if (cStack0000000000000030 != '\0') {
                    fmt_Errorf(0,0,cStack0000000000000030,0);
                    return 0;
                  }
                  puVar5 = (undefined8 *)runtime_mapaccess1_faststr(4,&DAT_0194e220,0,&DAT_01c39732);
                  if ((undefined8 *)*puVar5 == &DAT_01a233a0) {
                    uStack_e8 = puVar5[1];
                  }
                  else {
                    uStack_e8 = 0;
                  }
                  puVar5 = (undefined8 *)runtime_mapaccess1_faststr(3,uStack_e8,&DAT_01a233a0,&DAT_01c38e3c);
                  uVar11 = uStack_178;
                  if ((undefined8 *)*puVar5 == &DAT_0194e220) {
                    uVar2 = *(undefined8 *)puVar5[1];
                    lVar12 = ((undefined8 *)puVar5[1])[1];
                    if (lVar12 != 0) {
                      uVar14 = uStack_178 + 1;
                      lVar6 = lStack_38;
                      uVar9 = uStack_160;
                      if (uStack_160 < uVar14) {
                        uStack_120 = uVar2;
                        lVar6 = runtime_growslice(1);
                        uVar2 = uStack_120;
                      }
                      lVar19 = uVar11 * 0x10;
                      *(long *)(lVar6 + 8 + lVar19) = lVar12;
                      if (DAT_02e5e450 != 0) {
                        auVar24 = runtime_gcWriteBarrier2();
                        lVar6 = auVar24._0_8_;
                        *puVar20 = uVar2;
                        puVar20[1] = auVar24._8_8_;
                      }
                      *(undefined8 *)(lVar6 + lVar19) = uVar2;
                      puVar15 = puStack_170;
                      puVar3 = puStack_168;
                      goto LAB_016048c8;
                    }
                  }
                  puVar5 = (undefined8 *)runtime_mapaccess1_faststr(4,&DAT_0194e220,0,&DAT_01c3977e);
                  uVar11 = uStack_178;
                  puVar15 = puStack_170;
                  uVar9 = uStack_160;
                  uVar14 = uStack_178;
                  puVar3 = puStack_168;
                  lVar6 = lStack_38;
                  if ((undefined8 *)*puVar5 == &DAT_0194e220) {
                    uVar2 = *(undefined8 *)puVar5[1];
                    lVar12 = ((undefined8 *)puVar5[1])[1];
                    if (lVar12 != 0) {
                      uVar14 = uStack_178 + 1;
                      if (uStack_160 < uVar14) {
                        lStack_190 = lVar12;
                        uStack_d0 = uVar2;
                        lVar6 = runtime_growslice(1);
                        lVar12 = lStack_190;
                        uVar2 = uStack_d0;
                      }
                      lVar19 = uVar11 * 0x10;
                      *(long *)(lVar6 + 8 + lVar19) = lVar12;
                      if (DAT_02e5e450 != 0) {
                        auVar24 = runtime_gcWriteBarrier2();
                        lVar6 = auVar24._0_8_;
                        *puVar20 = uVar2;
                        puVar20[1] = auVar24._8_8_;
                      }
                      *(undefined8 *)(lVar6 + lVar19) = uVar2;
                      puVar15 = puStack_170;
                      puVar3 = puStack_168;
                    }
                  }
                }
                else if (((int)*plVar18 == 0x74786574) &&
                        (puVar5 = (undefined8 *)runtime_mapaccess1_faststr(4,&DAT_0194e220,4,&DAT_01c397b2),
                        puVar15 = puStack_170, uVar9 = uStack_160, uVar14 = uStack_178,
                        puVar3 = puStack_168, lVar6 = lStack_38,
                        (undefined8 *)*puVar5 == &DAT_0194e220)) {
                  uStack_108 = *(undefined8 *)puVar5[1];
                  lVar12 = ((undefined8 *)puVar5[1])[1];
                  strings_TrimSpace();
                  puVar15 = puStack_170;
                  uVar9 = uStack_160;
                  uVar14 = uStack_178;
                  puVar3 = puStack_168;
                  lVar6 = lStack_38;
                  if (lVar12 != 0) {
                    puVar5 = puStack_100;
                    if (uStack_1d8 < uStack_1e0 + 1) {
                      puVar5 = (undefined8 *)runtime_growslice(1,&DAT_0194e220);
                    }
                    auVar24._8_8_ = uStack_1e0 * 0x10;
                    auVar24._0_8_ = puVar5;
                    puVar5[uStack_1e0 * 2 + 1] = lVar12;
                    if (DAT_02e5e450 != 0) {
                      uVar2 = puVar5[uStack_1e0 * 2];
                      auVar24 = runtime_gcWriteBarrier2();
                      *puVar20 = uStack_108;
                      puVar20[1] = uVar2;
                    }
                    puStack_100 = auVar24._0_8_;
                    *(undefined8 *)((long)puStack_100 + auVar24._8_8_) = uStack_108;
                    puVar15 = puStack_170;
                    uStack_1e0 = uStack_1e0 + 1;
                    uVar9 = uStack_160;
                    uVar14 = uStack_178;
                    puVar3 = puStack_168;
                    lVar6 = lStack_38;
                  }
                }
              }
              else if (lVar12 == 9) {
                if ((*plVar18 == 0x72755f6567616d69) && ((char)plVar18[1] == 'l')) {
                  puVar5 = (undefined8 *)
                           runtime_mapaccess1_faststr(9,&DAT_0194e220,0x72755f6567616d69,&DAT_01c41e49);
                  if ((undefined8 *)*puVar5 == &DAT_01a233a0) {
                    uVar2 = puVar5[1];
                  }
                  else {
                    uVar2 = 0;
                  }
                  puVar7 = (undefined8 *)runtime_mapaccess1_faststr(3,uVar2,&DAT_01a233a0,&DAT_01c38e3c);
                  puVar5 = puStack_170;
                  puVar15 = puStack_170;
                  uVar9 = uStack_160;
                  uVar14 = uStack_178;
                  puVar3 = puStack_168;
                  lVar6 = lStack_38;
                  if ((undefined8 *)*puVar7 == &DAT_0194e220) {
                    uVar2 = *(undefined8 *)puVar7[1];
                    lVar12 = ((undefined8 *)puVar7[1])[1];
                    if (lVar12 != 0) {
                      puVar15 = (undefined8 *)((long)puStack_170 + 1);
                      lVar6 = lStack_f0;
                      if (puStack_168 < puVar15) {
                        uStack_118 = uVar2;
                        lVar6 = runtime_growslice(1);
                        uVar2 = uStack_118;
                      }
                      lVar19 = (long)puVar5 * 0x10;
                      *(long *)(lVar6 + 8 + lVar19) = lVar12;
                      if (DAT_02e5e450 != 0) {
                        auVar24 = runtime_gcWriteBarrier2();
                        lVar6 = auVar24._0_8_;
                        *puVar20 = uVar2;
                        puVar20[1] = auVar24._8_8_;
                      }
                      *(undefined8 *)(lVar6 + lVar19) = uVar2;
                      uVar9 = uStack_160;
                      uVar14 = uStack_178;
                      lStack_f0 = lVar6;
                      lVar6 = lStack_38;
                    }
                  }
                }
              }
              else if ((((lVar12 == 0xb) && (*plVar18 == 0x75615f7475706e69)) &&
                       ((short)plVar18[1] == 0x6964)) && (*(char *)((long)plVar18 + 10) == 'o')) {
                if (cStack0000000000000030 != '\0') {
                  fmt_Errorf(0,0,0x75615f7475706e69,0);
                  return 0;
                }
                puVar5 = (undefined8 *)
                         runtime_mapaccess1_faststr(0xb,&DAT_0194e220,0x75615f7475706e69,&DAT_01c461ad);
                if ((undefined8 *)*puVar5 == &DAT_01a233a0) {
                  uVar2 = puVar5[1];
                }
                else {
                  uVar2 = 0;
                }
                puVar5 = (undefined8 *)runtime_mapaccess1_faststr(4,uVar2,&DAT_01a233a0,&DAT_01c3977e);
                uVar11 = uStack_178;
                puVar15 = puStack_170;
                uVar9 = uStack_160;
                uVar14 = uStack_178;
                puVar3 = puStack_168;
                lVar6 = lStack_38;
                if ((undefined8 *)*puVar5 == &DAT_0194e220) {
                  uVar2 = *(undefined8 *)puVar5[1];
                  lVar12 = ((undefined8 *)puVar5[1])[1];
                  if (lVar12 != 0) {
                    uVar14 = uStack_178 + 1;
                    if (uStack_160 < uVar14) {
                      lStack_188 = lVar12;
                      uStack_c8 = uVar2;
                      lVar6 = runtime_growslice(1);
                      lVar12 = lStack_188;
                      uVar2 = uStack_c8;
                    }
                    lVar19 = uVar11 * 0x10;
                    *(long *)(lVar6 + 8 + lVar19) = lVar12;
                    if (DAT_02e5e450 != 0) {
                      auVar24 = runtime_gcWriteBarrier2();
                      lVar6 = auVar24._0_8_;
                      *puVar20 = uVar2;
                      puVar20[1] = auVar24._8_8_;
                    }
                    *(undefined8 *)(lVar6 + lVar19) = uVar2;
                    puVar15 = puStack_170;
                    puVar3 = puStack_168;
                  }
                }
              }
LAB_016048c8:
              uVar10 = uVar8 & 0xff;
              uVar17 = uVar16 & 0xff;
              uVar4 = uStack_158;
              uVar11 = uStack_1a0;
              puVar5 = puStack_d8;
              puVar7 = puStack_30;
              uVar13 = uStack_198;
            }
            else {
              uStack_f8 = 0;
              puVar15 = puVar20;
            }
            puVar7 = puVar7 + 2;
            puVar20 = puVar15;
          }
        }
        else {
LAB_01603b0a:
          uStack_1e0 = 0;
          uStack_1d8 = 0;
          puStack_100 = (undefined8 *)0x0;
        }
      }
      else {
        if ((*(int *)(puVar7 + 2) != -0x778cd48) || (puVar7 != &DAT_0194e220)) goto LAB_01603b0a;
        uStack_c0 = *puVar15;
        lVar6 = puVar15[1];
        lStack_180 = lVar6;
        strings_TrimSpace();
        if (lVar6 == 0) {
          uVar10 = uVar8 & 0xff;
          uStack_1d8 = 0;
          uStack_1e0 = 0;
          puStack_100 = (undefined8 *)0x0;
        }
        else {
          if ((char)uVar8 == '\0') {
            uStack_78 = in_XMM15_Qa;
            uStack_70 = in_XMM15_Qb;
            uStack_68 = in_XMM15_Qa;
            uStack_60 = in_XMM15_Qb;
            puVar5 = &uStack_78;
            uStack_1d8 = 2;
          }
          else {
            uStack_1d8 = 0;
            puVar5 = (undefined8 *)runtime_growslice(1,&DAT_0194e220);
          }
          auVar25._8_4_ = uVar8 & 0xff;
          auVar25._0_8_ = puVar5;
          puVar5[1] = lStack_180;
          if (DAT_02e5e450 != 0) {
            uVar2 = *puVar5;
            auVar25 = runtime_gcWriteBarrier2();
            *puVar20 = uStack_c0;
            puVar20[1] = uVar2;
          }
          puStack_100 = auVar25._0_8_;
          *puStack_100 = uStack_c0;
          uVar10 = auVar25._8_4_ | 1;
          uStack_1e0 = 1;
        }
        uVar11 = uStack_1a0;
        puVar5 = puStack_d8;
        uVar17 = uVar16 & 0xff;
        uVar13 = uStack_198;
        uVar14 = uStack_1b0;
        puVar20 = puStack_1c8;
        puVar3 = puStack_1c0;
        uVar9 = uStack_1a8;
        lVar6 = lStack_e0;
      }
    }
    if (uStack_1e0 != 0) {
      puStack_150 = puVar20;
      uStack_148 = uVar9;
      uStack_140 = uVar14;
      puStack_138 = puVar3;
      lStack_20 = lVar6;
      uVar2 = strings_Join(&DAT_01f34d88,1,uVar11,uStack_1d8);
      uVar9 = uStack_1a0;
      uVar11 = uStack_1a0 + 1;
      uVar14 = uStack_198;
      if (uStack_198 < uVar11) {
        uStack_28 = uVar2;
        uStack_158 = uStack_1e0;
        if ((((long)uVar11 < 2) && ((char)uVar16 == '\0')) && (uStack_1a0 == 0)) {
          uStack_98 = in_XMM15_Qa;
          uStack_90 = in_XMM15_Qb;
          uStack_88 = in_XMM15_Qa;
          uStack_80 = in_XMM15_Qb;
          puVar5 = &uStack_98;
          uVar14 = 1;
          uVar16 = 1;
        }
        else {
          puVar5 = (undefined8 *)runtime_growslice(1,&DAT_01a92980);
          uVar16 = uVar16 & 0xff;
          uVar2 = uStack_28;
          uStack_1e0 = uStack_158;
        }
      }
      else {
        uVar16 = uVar16 & 0xff;
        puVar5 = puStack_d8;
      }
      auVar21._8_8_ = uVar14;
      auVar21._0_8_ = uVar2;
      lVar6 = uVar9 * 0x20;
      puVar5[uVar9 * 4 + 1] = uStack_130;
      puVar5[uVar9 * 4 + 3] = uStack_1e0;
      if (DAT_02e5e450 != 0) {
        uVar2 = puVar5[uVar9 * 4];
        puVar3 = (undefined8 *)puVar5[uVar9 * 4 + 2];
        puVar20 = puVar3;
        auVar21 = runtime_gcWriteBarrier4();
        *puVar20 = uStack_18;
        puVar20[1] = uVar2;
        puVar20[2] = auVar21._0_8_;
        puVar20[3] = puVar3;
      }
      uVar13 = auVar21._8_8_;
      *(undefined8 *)((long)puVar5 + lVar6) = uStack_18;
      *(long *)((long)puVar5 + lVar6 + 0x10) = auVar21._0_8_;
      uVar17 = uVar16 & 0xffffffff;
      uVar10 = uVar10 & 0xff;
      uVar14 = uStack_140;
      puVar20 = puStack_150;
      puVar3 = puStack_138;
      uVar9 = uStack_148;
      lVar6 = lStack_20;
    }
    puStack0000000000000018 = puStack_10 + 4;
    uVar16 = uVar17;
    uVar8 = uVar10;
    unaff_RBX = lStack_128 + -1;
  }
  do {
    uVar17 = uVar17 - 1;
    if ((long)uVar17 < 0) {
      uVar17 = 0xffffffffffffffff;
      break;
    }
  } while ((puVar5[uVar17 * 4 + 1] != 4) || (*(int *)puVar5[uVar17 * 4] != 0x72657375));
  uVar16 = 0;
  uVar13 = 0;
  uVar9 = 0;
  puVar3 = (undefined8 *)0x0;
  uVar14 = 0;
  uStack_1d0 = uVar17;
  while ((long)uVar14 < (long)uVar11) {
    puStack_10 = puVar5;
    uStack_18 = puVar5[2];
    lStack_128 = puVar5[3];
    puVar5 = &DAT_01c3978a;
    uStack_1b8 = uVar14;
    if (uVar17 == uVar14) {
      uVar14 = uVar9 + 1;
      if (uVar13 < uVar14) {
        if ((((long)uVar14 < 3) && ((char)uVar16 == '\0')) && (uVar9 == 0)) {
          uStack_b8 = in_XMM15_Qa;
          uStack_b0 = in_XMM15_Qb;
          uStack_a8 = in_XMM15_Qa;
          uStack_a0 = in_XMM15_Qb;
          puVar3 = &uStack_b8;
          uVar13 = 2;
          uVar16 = 1;
        }
        else {
          puVar3 = (undefined8 *)runtime_growslice(1,&DAT_0194e220);
          uVar16 = uVar16 & 0xff;
          uVar11 = uStack_1a0;
          uVar17 = uStack_1d0;
        }
      }
      puVar5 = puStack_10;
      uVar2 = uStack_18;
      auVar22._8_8_ = uVar11;
      auVar22._0_8_ = uStack_1b8;
      puVar20 = &DAT_01c3978a;
      lVar6 = uVar9 * 0x10;
      puVar3[uVar9 * 2 + 1] = lStack_128;
      if (DAT_02e5e450 != 0) {
        uVar1 = puVar3[uVar9 * 2];
        auVar22 = runtime_gcWriteBarrier2();
        *puVar20 = uVar2;
        puVar20[1] = uVar1;
      }
      *(undefined8 *)((long)puVar3 + lVar6) = uVar2;
      uVar9 = uVar14;
    }
    else {
      uStack_130 = uVar9 + 1;
      puStack_110 = puVar3;
      uStack_50 = runtime_convTstring();
      puStack_58 = &DAT_0194e220;
      auVar24 = runtime_convTstring();
      uStack_40 = auVar24._0_8_;
      puStack_48 = &DAT_0194e220;
      lVar6 = 6;
      uVar2 = fmt_Sprintf(2,2,auVar24._8_8_,&puStack_58);
      uVar11 = uStack_130;
      puVar3 = puStack_110;
      if (uVar13 < uStack_130) {
        lStack_128 = 6;
        uStack_18 = uVar2;
        puVar3 = (undefined8 *)runtime_growslice(1,&DAT_0194e220);
        uVar2 = uStack_18;
        lVar6 = lStack_128;
      }
      auVar23._8_8_ = uVar11;
      auVar23._0_8_ = uVar2;
      lVar12 = uVar11 - 1;
      lVar19 = lVar12 * 0x10;
      puVar3[lVar12 * 2 + 1] = lVar6;
      if (DAT_02e5e450 != 0) {
        uVar2 = puVar3[lVar12 * 2];
        auVar23 = runtime_gcWriteBarrier2();
        *puVar5 = auVar23._0_8_;
        puVar5[1] = uVar2;
      }
      uVar9 = auVar23._8_8_;
      auVar22._8_8_ = uStack_1a0;
      auVar22._0_8_ = uStack_1b8;
      *(long *)((long)puVar3 + lVar19) = auVar23._0_8_;
      uVar16 = uVar16 & 0xff;
      puVar5 = puStack_10;
      uVar17 = uStack_1d0;
    }
    uVar11 = auVar22._8_8_;
    puVar5 = puVar5 + 4;
    uVar14 = auVar22._0_8_ + 1;
  }
  uVar2 = strings_Join(&DAT_01f35098,2,uVar11,uVar13);
  return uVar2;
}




// === grok.ImagineGenerations @ 0x160cd00 ===

void grok_ImagineGenerations
               (undefined8 param_1,undefined8 param_2,long param_3,undefined8 param_4,
               undefined **param_5)

{
  long lVar1;
  bool bVar2;
  char cVar3;
  undefined8 uVar4;
  long lVar5;
  undefined **ppuVar6;
  long *plVar7;
  undefined8 *puVar8;
  undefined8 *puVar9;
  code *pcVar10;
  undefined8 *extraout_RDX;
  byte *pbVar11;
  long extraout_RDX_00;
  undefined **ppuVar12;
  undefined8 uVar13;
  int *piVar14;
  undefined8 *in_R11;
  long unaff_R14;
  undefined1 auVar15 [16];
  code *pcStack_460;
  undefined8 uStack_458;
  long *plStack_450;
  undefined8 uStack_448;
  undefined8 uStack_440;
  undefined8 uStack_438;
  undefined8 uStack_430;
  undefined **ppuStack_428;
  long lStack_420;
  long lStack_418;
  long *plStack_410;
  undefined8 uStack_408;
  long *plStack_400;
  undefined8 uStack_3f8;
  undefined **ppuStack_3d8;
  undefined1 **ppuStack_3a8;
  undefined8 uStack_390;
  undefined8 uStack_388;
  undefined8 uStack_380;
  long *plStack_378;
  undefined8 *puStack_370;
  undefined **ppuStack_368;
  long lStack_360;
  undefined8 uStack_358;
  undefined8 uStack_350;
  byte *pbStack_348;
  undefined *puStack_340;
  undefined8 uStack_338;
  undefined *puStack_2f0;
  undefined8 uStack_2e8;
  undefined *puStack_2e0;
  undefined8 uStack_2d8;
  undefined8 uStack_2d0;
  undefined8 uStack_2c8;
  undefined8 uStack_2c0;
  long *plStack_2b8;
  undefined8 uStack_2b0;
  undefined1 *puStack_2a8;
  undefined8 uStack_2a0;
  undefined8 *puStack_298;
  undefined8 uStack_290;
  undefined8 *puStack_288;
  undefined8 uStack_280;
  undefined8 *puStack_278;
  undefined **ppuStack_270;
  undefined1 auStack_268 [112];
  undefined **ppuStack_1f8;
  undefined1 *puStack_1f0;
  undefined **ppuStack_1e8;
  undefined **ppuStack_1e0;
  undefined8 uStack_1d8;
  undefined1 *puStack_1d0;
  undefined8 uStack_1c8;
  undefined8 uStack_1b8;
  undefined1 *puStack_1b0;
  undefined8 uStack_1a8;
  undefined8 uStack_198;
  undefined1 *puStack_190;
  undefined8 uStack_188;
  undefined8 uStack_178;
  undefined1 *puStack_170;
  undefined8 uStack_168;
  undefined8 uStack_158;
  undefined1 *puStack_150;
  undefined8 uStack_148;
  undefined8 uStack_138;
  undefined1 *puStack_130;
  undefined8 uStack_128;
  undefined8 uStack_118;
  undefined1 auStack_110 [192];
  undefined1 auStack_50 [8];
  undefined8 uStack_48;
  undefined8 *puStack_40;
  undefined *puStack_20;
  long *plStack_18;
  undefined8 uStack_10;
  
  while (&pcStack_460 <= *(code ***)(unaff_R14 + 0x10)) {
    runtime_morestack();
    param_3 = extraout_RDX_00;
  }
  uStack_2b0 = *(undefined8 *)(param_3 + 8);
  lStack_420 = *(long *)(param_3 + 0x18);
  uStack_2c0 = *(undefined8 *)(param_3 + 0x20);
  plVar7 = *(long **)(param_3 + 0x10);
  lVar1 = *(long *)(param_3 + 0x28);
  puStack_2a8 = &LAB_0160dfe0;
  ppuStack_3a8 = &puStack_2a8;
  plStack_2b8 = plVar7;
  uStack_2a0 = uStack_2b0;
  runtime_deferprocStack();
  puStack_20 = &DAT_0160df60;
  plStack_18 = plStack_2b8;
  ppuVar6 = &puStack_20;
  ppuStack_3d8 = ppuVar6;
  runtime_deferprocStack();
  FUN_00488ccb(auStack_110);
  uStack_118 = 0x8080808080808080;
  puStack_40 = &uStack_118;
  uStack_48 = runtime_rand();
  uStack_3f8 = time_Now();
  plStack_400 = plVar7;
  ppuStack_1e0 = ppuVar6;
  uVar4 = time_Now();
  lStack_418 = 0;
  puStack_370 = (undefined8 *)0x0;
  do {
    while( true ) {
      uStack_458 = uVar4;
      plStack_450 = plVar7;
      ppuStack_368 = ppuVar6;
      lVar5 = time_Since();
      if (119999999999 < lVar5) {
        github_com_gogf_gf_v2_frame_gins_Log();
        puStack_278 = (undefined8 *)&DAT_01b53c60;
        ppuStack_270 = (undefined **)&DAT_01f38748;
        github_com_gogf_gf_v2_os_glog_Logger_Warningf(&DAT_01c7d101,0x29,&DAT_01f38748,uStack_2c0,&puStack_278,1);
        puStack_278 = (undefined8 *)&DAT_01b53c60;
        ppuStack_270 = (undefined **)&DAT_01f38748;
        fmt_Sprintf(1,1,&DAT_01f38748,&puStack_278);
        puStack_2e0 = (undefined *)FUN_00488ce6(&uStack_350);
        puStack_340 = &DAT_01c3a5a3;
        uStack_338 = 5;
        puStack_2f0 = &DAT_01c3dcfe;
        uStack_2e8 = 7;
        uStack_2d8 = 0x22;
        FUN_0048903e(auStack_268,&puStack_340);
        uStack_1c8 = (**(code **)(lStack_420 + 0x20))();
        uStack_1d8 = uStack_2b0;
        puStack_1d0 = auStack_268;
        runtime_selectgo(1,1,puStack_1d0,0,1);
        runtime_deferreturn();
        return;
      }
      pcVar10 = *(code **)(lStack_420 + 0x20);
      ppuVar6 = (undefined **)(*pcVar10)();
      cVar3 = runtime_selectnbrecv();
      if (cVar3 != '\0') {
        runtime_deferreturn();
        return;
      }
      time_Now();
      plVar7 = (long *)time_Time_Add(5000000000);
      ppuVar12 = *(undefined ***)(*plStack_2b8 + 0x40);
      (*(code *)ppuVar12)(pcVar10,ppuVar12,plStack_2b8[1]);
      github_com_gorilla_websocket_Conn_ReadMessage();
      if (ppuVar12 != (undefined **)0x0) break;
      pcStack_460 = pcVar10;
      plStack_378 = plVar7;
      uStack_408 = time_Now();
      plStack_410 = plVar7;
      ppuStack_1e8 = ppuVar6;
      auVar15 = runtime_newobject();
      uStack_10 = auVar15._0_8_;
      lVar5 = encoding_json_Unmarshal(&DAT_01928320,uStack_10,auVar15._8_8_,pcStack_460);
      uVar4 = uStack_408;
      ppuVar6 = ppuStack_1e8;
      plVar7 = plStack_410;
      param_5 = ppuStack_1e8;
      if (lVar5 == 0) {
        puVar8 = (undefined8 *)runtime_mapaccess1_faststr(4);
        if ((undefined8 *)*puVar8 == &DAT_0194e220) {
          piVar14 = *(int **)puVar8[1];
          lVar5 = ((undefined8 *)puVar8[1])[1];
        }
        else {
          lVar5 = 0;
          piVar14 = (int *)0x0;
        }
        uVar4 = uStack_408;
        ppuVar6 = ppuStack_1e8;
        plVar7 = plStack_410;
        param_5 = ppuStack_1e8;
        if (lVar5 == 5) {
          if ((*piVar14 == 0x6f727265) && ((char)piVar14[1] == 'r')) {
            puVar8 = (undefined8 *)runtime_mapaccess1_faststr(8,5,uStack_10,&DAT_01c3ff17);
            if ((undefined8 *)*puVar8 == &DAT_0194e220) {
              uStack_2c8 = *(undefined8 *)puVar8[1];
              uStack_430 = ((undefined8 *)puVar8[1])[1];
            }
            else {
              uStack_430 = 0;
              uStack_2c8 = 0;
            }
            puVar8 = (undefined8 *)runtime_mapaccess1_faststr();
            if ((undefined8 *)*puVar8 == &DAT_0194e220) {
              uStack_2d0 = *(undefined8 *)puVar8[1];
              uStack_438 = ((undefined8 *)puVar8[1])[1];
            }
            else {
              uStack_438 = 0;
              uStack_2d0 = 0;
            }
            uStack_390 = github_com_gogf_gf_v2_frame_gins_Log();
            uStack_290 = runtime_convTstring();
            puStack_298 = &DAT_0194e220;
            uStack_280 = runtime_convTstring();
            puStack_288 = &DAT_0194e220;
            github_com_gogf_gf_v2_os_glog_Logger_Warningf(&DAT_01c798e4,0x27,&DAT_0194e220,uStack_2c0,&puStack_298,2);
            FUN_00488ce6(&uStack_350);
            puStack_340 = &DAT_01c3a5a3;
            uStack_338 = 5;
            puStack_2f0 = (undefined *)uStack_2c8;
            uStack_2e8 = uStack_430;
            puStack_2e0 = (undefined *)uStack_2d0;
            uStack_2d8 = uStack_438;
            FUN_0048903e(auStack_268,&puStack_340);
            uStack_1a8 = (**(code **)(lStack_420 + 0x20))();
            uStack_1b8 = uStack_2b0;
            puStack_1b0 = auStack_268;
            runtime_selectgo(1,1,puStack_1b0,0,1);
            runtime_deferreturn();
            return;
          }
          if ((*piVar14 == 0x67616d69) && ((char)piVar14[1] == 'e')) {
            puVar8 = (undefined8 *)runtime_mapaccess1_faststr(3,5,uStack_10,&DAT_01c38e3c);
            if ((undefined8 *)*puVar8 == &DAT_0194e220) {
              uStack_358 = *(undefined8 *)puVar8[1];
              uStack_448 = ((undefined8 *)puVar8[1])[1];
            }
            else {
              uStack_448 = 0;
              uStack_358 = 0;
            }
            puVar8 = (undefined8 *)runtime_mapaccess1_faststr(4,uStack_448,uStack_10,&DAT_01c3984e);
            if ((undefined8 *)*puVar8 == &DAT_0194e220) {
              uVar4 = *(undefined8 *)puVar8[1];
              uVar13 = ((undefined8 *)puVar8[1])[1];
            }
            else {
              uVar13 = 0;
              uVar4 = 0;
            }
            lVar5 = kiro2api_internal_logic_grok_classifyImage(uVar13,uVar13,&DAT_0194e220,uVar4);
            uVar4 = uStack_408;
            ppuVar6 = ppuStack_1e8;
            plVar7 = plStack_410;
            param_5 = ppuStack_1e8;
            if (lVar5 != 0) {
              uStack_350 = *(undefined8 *)(lVar5 + 0x10);
              uStack_440 = *(undefined8 *)(lVar5 + 0x18);
              lStack_360 = lVar5;
              puVar8 = (undefined8 *)runtime_mapaccess1_faststr();
              pbVar11 = (byte *)*puVar8;
              if ((((*(long *)(lStack_360 + 0x28) == 6) &&
                   (**(int **)(lStack_360 + 0x20) == 0x6964656d)) &&
                  ((short)(*(int **)(lStack_360 + 0x20))[1] == 0x6d75)) &&
                 (puStack_370 == (undefined8 *)0x0)) {
                pbStack_348 = pbVar11;
                puVar9 = (undefined8 *)runtime_newobject();
                puVar8 = puStack_370;
                puStack_370 = puVar9;
                uVar4 = time_Now();
                *puStack_370 = uVar4;
                puStack_370[1] = auStack_50;
                puVar9 = puStack_370;
                if (DAT_02e5e450 != 0) {
                  uVar4 = puStack_370[2];
                  runtime_gcWriteBarrier2();
                  *in_R11 = puVar8;
                  in_R11[1] = uVar4;
                  puVar9 = extraout_RDX;
                }
                puVar9[2] = puVar8;
                pbVar11 = pbStack_348;
              }
              if ((*(byte *)(lStack_360 + 0x48) != 0) &&
                 ((pbVar11 == (byte *)0x0 || (*pbVar11 == 0)))) {
                lStack_418 = lStack_418 + 1;
              }
              if (pbVar11 == (byte *)0x0) {
                puStack_1f0 = (undefined1 *)runtime_newobject();
                *puStack_1f0 = *(undefined1 *)(lStack_360 + 0x48);
                puVar8 = (undefined8 *)runtime_mapassign_faststr(uStack_440);
                if (DAT_02e5e450 != 0) {
                  uVar4 = *puVar8;
                  puVar8 = (undefined8 *)runtime_gcWriteBarrier2();
                  *in_R11 = puStack_1f0;
                  in_R11[1] = uVar4;
                }
                *puVar8 = puStack_1f0;
              }
              else {
                *pbVar11 = *pbVar11 | *(byte *)(lStack_360 + 0x48);
              }
              FUN_0048903e(&puStack_340,lStack_360);
              FUN_0048903e(auStack_268,&puStack_340);
              auVar15 = (**(code **)(lStack_420 + 0x20))();
              uStack_168 = auVar15._0_8_;
              uStack_178 = uStack_2b0;
              puStack_170 = auStack_268;
              lVar5 = runtime_selectgo(1,1,auVar15._8_8_,0,1);
              if (lVar5 != 0) {
                runtime_deferreturn();
                return;
              }
              if (lVar1 <= lStack_418) {
                uStack_388 = github_com_gogf_gf_v2_frame_gins_Log();
                ppuStack_270 = (undefined **)runtime_convT64();
                puStack_278 = &DAT_0194e460;
                github_com_gogf_gf_v2_os_glog_Logger_Infof(&DAT_01c88c7b,0x32,&DAT_0194e460,uStack_2c0,&puStack_278,1);
                runtime_deferreturn();
                return;
              }
              uVar4 = uStack_408;
              ppuVar6 = ppuStack_1e8;
              plVar7 = plStack_410;
              param_5 = ppuStack_1e8;
              if (((puStack_370 != (undefined8 *)0x0) && (lStack_418 == 0)) &&
                 (lVar5 = time_Since(), uVar4 = uStack_408, ppuVar6 = ppuStack_1e8,
                 plVar7 = plStack_410, param_5 = ppuStack_1e8, 15000000000 < lVar5)) {
                FUN_00488ce6(&uStack_350);
                puStack_340 = &DAT_01c3a5a3;
                uStack_338 = 5;
                puStack_2f0 = &DAT_01c3ddde;
                uStack_2e8 = 7;
                puStack_2e0 = &DAT_01c5a5c1;
                uStack_2d8 = 0x16;
                FUN_0048903e(auStack_268,&puStack_340);
                auVar15 = (**(code **)(lStack_420 + 0x20))();
                uStack_188 = auVar15._0_8_;
                uStack_198 = uStack_2b0;
                puStack_190 = auStack_268;
                runtime_selectgo(1,1,auVar15._8_8_,0,1);
                runtime_deferreturn();
                return;
              }
            }
          }
        }
      }
    }
    if (ppuVar12 == &PTR_DAT_01f43240) {
      bVar2 = false;
      while (!bVar2) {
        if (*param_5 == (undefined *)0x3e8) {
          runtime_deferreturn();
          return;
        }
        bVar2 = true;
      }
    }
    ppuStack_428 = ppuVar12;
    ppuStack_1f8 = param_5;
    cVar3 = kiro2api_internal_logic_grok_isTimeoutError();
    if (cVar3 == '\0') {
      github_com_gogf_gf_v2_frame_gins_Log();
      if (ppuStack_428 == (undefined **)0x0) {
        puStack_278 = (undefined8 *)0x0;
      }
      else {
        puStack_278 = (undefined8 *)ppuStack_428[1];
      }
      ppuStack_270 = ppuStack_1f8;
      github_com_gogf_gf_v2_os_glog_Logger_Warningf(&DAT_01c798bd,0x27,ppuStack_1f8,uStack_2c0,&puStack_278,1);
      if (ppuStack_428 == (undefined **)0x0) {
        puStack_278 = (undefined8 *)0x0;
      }
      else {
        puStack_278 = (undefined8 *)ppuStack_428[1];
      }
      ppuStack_270 = ppuStack_1f8;
      fmt_Sprintf(1,1,ppuStack_1f8,&puStack_278);
      puStack_2e0 = (undefined *)FUN_00488ce6(&uStack_350);
      puStack_340 = &DAT_01c3a5a3;
      uStack_338 = 5;
      puStack_2f0 = &DAT_01c41fd5;
      uStack_2e8 = 9;
      uStack_2d8 = 0x13;
      FUN_0048903e(auStack_268,&puStack_340);
      uStack_148 = (**(code **)(lStack_420 + 0x20))();
      uStack_158 = uStack_2b0;
      puStack_150 = auStack_268;
      runtime_selectgo(1,1,puStack_150,0,1);
      runtime_deferreturn();
      return;
    }
    if (((puStack_370 != (undefined8 *)0x0) && (lStack_418 == 0)) &&
       (lVar5 = time_Since(), 15000000000 < lVar5)) {
      FUN_00488ce6(&uStack_350);
      puStack_340 = &DAT_01c3a5a3;
      uStack_338 = 5;
      puStack_2f0 = &DAT_01c3ddde;
      uStack_2e8 = 7;
      puStack_2e0 = &DAT_01c5a5c1;
      uStack_2d8 = 0x16;
      FUN_0048903e(auStack_268,&puStack_340);
      auVar15 = (**(code **)(lStack_420 + 0x20))();
      uStack_128 = auVar15._0_8_;
      uStack_138 = uStack_2b0;
      puStack_130 = auStack_268;
      runtime_selectgo(1,1,auVar15._8_8_,0,1);
      runtime_deferreturn();
      return;
    }
    if (lStack_418 < 1) {
      bVar2 = false;
    }
    else {
      lVar5 = time_Since();
      bVar2 = 10000000000 < lVar5;
    }
    uVar4 = uStack_458;
    ppuVar6 = ppuStack_368;
    plVar7 = plStack_450;
    param_5 = ppuStack_368;
  } while (!bVar2);
  uStack_380 = github_com_gogf_gf_v2_frame_gins_Log();
  ppuStack_270 = (undefined **)runtime_convT64();
  puStack_278 = &DAT_0194e460;
  github_com_gogf_gf_v2_os_glog_Logger_Infof(&DAT_01c91504,0x3a,&DAT_0194e460,uStack_2c0,&puStack_278,1);
  runtime_deferreturn();
  return;
}




// === grok.VideoGenerations @ 0x161bc00 ===

/* WARNING: Removing unreachable block (ram,0x0161c5c9) */
/* WARNING: Removing unreachable block (ram,0x0161c689) */
/* WARNING: Removing unreachable block (ram,0x0161c662) */
/* WARNING: Removing unreachable block (ram,0x0161c673) */
/* WARNING: Removing unreachable block (ram,0x0161ca68) */
/* WARNING: Removing unreachable block (ram,0x0161caac) */
/* WARNING: Removing unreachable block (ram,0x0161ca7c) */
/* WARNING: Removing unreachable block (ram,0x0161ca85) */
/* WARNING: Removing unreachable block (ram,0x0161c838) */
/* WARNING: Removing unreachable block (ram,0x0161c8ca) */
/* WARNING: Removing unreachable block (ram,0x0161c8ce) */
/* WARNING: Removing unreachable block (ram,0x0161c94d) */
/* WARNING: Removing unreachable block (ram,0x0161c975) */
/* WARNING: Removing unreachable block (ram,0x0161c988) */
/* WARNING: Removing unreachable block (ram,0x0161c99c) */
/* WARNING: Removing unreachable block (ram,0x0161c9ad) */
/* WARNING: Removing unreachable block (ram,0x0161c9b9) */
/* WARNING: Removing unreachable block (ram,0x0161c9c4) */
/* WARNING: Removing unreachable block (ram,0x0161ca07) */
/* WARNING: Removing unreachable block (ram,0x0161ca0b) */
/* WARNING: Removing unreachable block (ram,0x0161c782) */
/* WARNING: Removing unreachable block (ram,0x0161c7eb) */

undefined8 grok_VideoGenerations(long param_1,long param_2,undefined8 param_3,long param_4)

{
  char cVar1;
  long lVar2;
  undefined8 uVar3;
  undefined8 *puVar4;
  long lVar5;
  undefined8 extraout_RDX;
  long unaff_RBX;
  undefined *puVar6;
  long lVar7;
  long lVar8;
  undefined8 *puVar9;
  long unaff_R14;
  undefined1 auVar10 [16];
  long lStack0000000000000010;
  long lStack0000000000000018;
  long lStack0000000000000020;
  long lStack0000000000000028;
  long lStack_108;
  long lStack_100;
  undefined8 uStack_e0;
  undefined8 uStack_d8;
  undefined8 uStack_d0;
  undefined8 uStack_c8;
  undefined8 uStack_c0;
  undefined8 uStack_b0;
  undefined8 uStack_a8;
  undefined8 uStack_a0;
  undefined8 uStack_98;
  undefined8 uStack_90;
  long lStack_88;
  undefined *puStack_78;
  undefined8 *puStack_70;
  undefined8 uStack_68;
  undefined8 *puStack_60;
  undefined8 uStack_58;
  undefined8 *puStack_50;
  undefined8 uStack_48;
  undefined8 *puStack_40;
  long lStack_38;
  undefined8 *puStack_30;
  undefined8 uStack_28;
  undefined *puStack_20;
  undefined *puStack_18;
  undefined8 uStack_10;
  
  lStack0000000000000018 = param_4;
  lStack0000000000000010 = unaff_RBX;
  lStack0000000000000028 = param_2;
  lStack0000000000000020 = param_1;
  while (&lStack_108 <= *(long **)(unaff_R14 + 0x10)) {
    runtime_morestack_noctxt();
  }
  uStack_a8 = *(undefined8 *)(lStack0000000000000028 + 0x10);
  uStack_c0 = github_com_gogf_gf_v2_frame_gins_Log();
  lVar8 = *(long *)(lStack0000000000000028 + 0x28);
  uStack_28 = runtime_convTstring();
  puStack_30 = &DAT_0194e220;
  puStack_20 = &DAT_0194e620;
  puStack_18 = &DAT_01f8a680 + (ulong)(lVar8 != 0) * 8;
  github_com_gogf_gf_v2_os_glog_Logger_Debugf(&DAT_01c9060f,0x39,puStack_18,lStack0000000000000018,&puStack_30,2);
  lVar2 = lStack0000000000000010;
  lVar8 = *(long *)(lStack0000000000000028 + 0x28);
  if (lVar8 == 0) {
    lVar8 = lStack0000000000000018;
    lVar5 = lStack0000000000000020;
    uStack_a0 = kiro2api_internal_logic_grok_sGrok_createMediaPost(lStack0000000000000020,*(undefined8 *)(lStack0000000000000028 + 0x10),
                             lStack0000000000000028,lStack0000000000000018,
                             *(undefined8 *)(lStack0000000000000028 + 0x18),&DAT_01c58c13);
    if (lVar8 != 0) {
      lStack_88 = lVar5;
      github_com_gogf_gf_v2_frame_gins_Log();
      if (lVar8 == 0) {
        puStack_40 = (undefined8 *)0x0;
      }
      else {
        puStack_40 = *(undefined8 **)(lVar8 + 8);
      }
      lStack_38 = lStack_88;
      github_com_gogf_gf_v2_os_glog_Logger_Errorf(&DAT_01c71db0,0x23,lStack_88,lStack0000000000000018,&puStack_40,1);
      if (lVar8 == 0) {
        puStack_40 = (undefined8 *)0x0;
      }
      else {
        puStack_40 = *(undefined8 **)(lVar8 + 8);
      }
      lStack_38 = lStack_88;
      fmt_Errorf(1,1,lStack_88,&puStack_40);
      return 0;
    }
    uStack_d8 = github_com_gogf_gf_v2_frame_gins_Log();
    lStack_38 = runtime_convTstring();
    puStack_40 = &DAT_0194e220;
    github_com_gogf_gf_v2_os_glog_Logger_Debugf(&DAT_01c66d40,0x1d,&DAT_0194e220,lStack0000000000000018,&puStack_40,1);
  }
  else {
    if (lVar8 < 0x17) {
      cVar1 = '\0';
      uVar3 = *(undefined8 *)(lStack0000000000000028 + 0x20);
    }
    else {
      lStack_100 = lVar8;
      uStack_10 = *(undefined8 *)(lStack0000000000000028 + 0x20);
      cVar1 = runtime_memequal();
      uVar3 = uStack_10;
      lVar8 = lStack_100;
    }
    auVar10._8_8_ = lStack0000000000000028;
    auVar10._0_8_ = uVar3;
    if (cVar1 == '\0') {
      uStack_c8 = github_com_gogf_gf_v2_frame_gins_Log();
      lStack_38 = runtime_convTstring();
      puStack_40 = &DAT_0194e220;
      github_com_gogf_gf_v2_os_glog_Logger_Debugf(&DAT_01c700a9,0x22,&DAT_0194e220,lStack0000000000000018,&puStack_40,1);
      lVar8 = lStack0000000000000010;
      lVar2 = lStack0000000000000018;
      lVar5 = lStack0000000000000020;
      auVar10 = kiro2api_internal_logic_grok_sGrok_uploadImage(lStack0000000000000020,*(undefined8 *)(lStack0000000000000028 + 0x20),
                             lStack0000000000000028,lStack0000000000000018,
                             *(undefined8 *)(lStack0000000000000028 + 0x28));
      if (lVar2 != 0) {
        lStack_88 = lVar5;
        github_com_gogf_gf_v2_frame_gins_Log();
        if (lVar2 == 0) {
          puStack_40 = (undefined8 *)0x0;
        }
        else {
          puStack_40 = *(undefined8 **)(lVar2 + 8);
        }
        lStack_38 = lStack_88;
        github_com_gogf_gf_v2_os_glog_Logger_Errorf(&DAT_01c68b5a,0x1e,lStack_88,lStack0000000000000018,&puStack_40,1);
        if (lVar2 == 0) {
          puStack_40 = (undefined8 *)0x0;
        }
        else {
          puStack_40 = *(undefined8 **)(lVar2 + 8);
        }
        lStack_38 = lStack_88;
        fmt_Errorf(1,1,lStack_88,&puStack_40);
        return 0;
      }
    }
    lVar2 = lStack0000000000000010;
    lVar5 = lStack0000000000000018;
    lVar7 = lStack0000000000000020;
    uStack_a0 = kiro2api_internal_logic_grok_sGrok_createImagePost(lStack0000000000000020,auVar10._0_8_,auVar10._8_8_,
                             lStack0000000000000018,lVar8);
    if (lVar5 != 0) {
      lStack_88 = lVar7;
      github_com_gogf_gf_v2_frame_gins_Log();
      if (lVar5 == 0) {
        puStack_40 = (undefined8 *)0x0;
      }
      else {
        puStack_40 = *(undefined8 **)(lVar5 + 8);
      }
      lStack_38 = lStack_88;
      github_com_gogf_gf_v2_os_glog_Logger_Errorf(&DAT_01c71d8d,0x23,lStack_88,lStack0000000000000018,&puStack_40,1);
      if (lVar5 == 0) {
        puStack_40 = (undefined8 *)0x0;
      }
      else {
        puStack_40 = *(undefined8 **)(lVar5 + 8);
      }
      lStack_38 = lStack_88;
      fmt_Errorf(1,1,lStack_88,&puStack_40);
      return 0;
    }
    uStack_d0 = github_com_gogf_gf_v2_frame_gins_Log();
    lStack_38 = runtime_convTstring();
    puStack_40 = &DAT_0194e220;
    github_com_gogf_gf_v2_os_glog_Logger_Debugf(&DAT_01c79932,0x27,&DAT_0194e220,lStack0000000000000018,&puStack_40,1);
  }
  lStack_108 = *(long *)(lStack0000000000000028 + 0x38);
  puStack_78 = *(undefined **)(lStack0000000000000028 + 0x30);
  puVar9 = *(undefined8 **)(lStack0000000000000028 + 0x50);
  uStack_b0 = *(undefined8 *)(lStack0000000000000028 + 0x48);
  uStack_10 = kiro2api_internal_logic_grok_sGrok_GetCfClearance();
  lStack_100 = lStack0000000000000010;
  uVar3 = kiro2api_internal_logic_grok_sGrok_GetBrowserFingerprint();
  uStack_90 = kiro2api_internal_logic_grok_BuildHeaders(lStack_100,uVar3,*(undefined8 *)(lStack0000000000000020 + 0x18),uStack_10
                           ,lStack0000000000000010);
  puVar4 = (undefined8 *)runtime_mapassign_faststr(7);
  puVar4[1] = 0x18;
  puVar6 = puStack_78;
  lVar8 = lStack_108;
  if (lStack_108 == 0) {
    lVar8 = 4;
    puVar6 = &DAT_01c39842;
  }
  uVar3 = uStack_b0;
  if (puVar9 == (undefined8 *)0x0) {
    puVar9 = (undefined8 *)&DAT_00000004;
    uVar3 = 0x1c397d6;
  }
  if (DAT_02e5e450 != 0) {
    auVar10 = runtime_gcWriteBarrier1();
    puVar4 = auVar10._0_8_;
    *puVar9 = auVar10._8_8_;
  }
  *puVar4 = &DAT_01c5dfd0;
  lStack_108 = lVar8;
  uStack_b0 = uVar3;
  puStack_78 = puVar6;
  uStack_98 = kiro2api_internal_logic_grok_buildVideoPayload(lVar2);
  uStack_e0 = github_com_gogf_gf_v2_frame_gins_Log();
  uStack_68 = runtime_convTstring();
  puStack_70 = &DAT_0194e220;
  uStack_58 = runtime_convT64();
  puStack_60 = &DAT_0194e460;
  uStack_48 = runtime_convTstring();
  puStack_50 = &DAT_0194e220;
  github_com_gogf_gf_v2_os_glog_Logger_Debugf(&DAT_01ca085b,0x54,&DAT_0194e220,lStack0000000000000018,&puStack_70,3);
  kiro2api_internal_logic_grok_sGrok_clientForAccount(lStack0000000000000020);
  uVar3 = 0x30;
  kiro2api_internal_logic_grok_GrokClient_PostStream(uStack_90,&DAT_01a233a0,extraout_RDX,0x30,uStack_98);
  lStack_88 = uVar3;
  github_com_gogf_gf_v2_frame_gins_Log();
  puStack_40 = DAT_01c866c1;
  lStack_38 = lStack_88;
  github_com_gogf_gf_v2_os_glog_Logger_Errorf(&DAT_01c7e93c,0x2a,lStack_88,lStack0000000000000018,&puStack_40,1);
  puStack_40 = DAT_01c866c1;
  lStack_38 = lStack_88;
  fmt_Errorf(1,1,lStack_88,&puStack_40);
  return 0;
}



