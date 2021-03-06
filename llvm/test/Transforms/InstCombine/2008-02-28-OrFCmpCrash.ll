; NOTE: Assertions have been autogenerated by utils/update_test_checks.py
; RUN: opt < %s -passes=instcombine -S | FileCheck %s

; rdar://5771353

define float @test(float %x, x86_fp80 %y) nounwind readonly  {
; CHECK-LABEL: @test(
; CHECK-NEXT:  entry:
; CHECK-NEXT:    [[TMP67:%.*]] = fcmp uno x86_fp80 [[Y:%.*]], 0xK00000000000000000000
; CHECK-NEXT:    [[TMP71:%.*]] = fcmp uno float [[X:%.*]], 0.000000e+00
; CHECK-NEXT:    [[BOTHCOND:%.*]] = or i1 [[TMP67]], [[TMP71]]
; CHECK-NEXT:    br i1 [[BOTHCOND]], label [[BB74:%.*]], label [[BB80:%.*]]
; CHECK:       bb74:
; CHECK-NEXT:    ret float 0.000000e+00
; CHECK:       bb80:
; CHECK-NEXT:    ret float 0.000000e+00
;
entry:
  %tmp67 = fcmp uno x86_fp80 %y, 0xK00000000000000000000		; <i1> [#uses=1]
  %tmp71 = fcmp uno float %x, 0.000000e+00		; <i1> [#uses=1]
  %bothcond = or i1 %tmp67, %tmp71		; <i1> [#uses=1]
  br i1 %bothcond, label %bb74, label %bb80

bb74:		; preds = %entry
  ret float 0.000000e+00

bb80:		; preds = %entry
  ret float 0.000000e+00
}

define float @test_logical(float %x, x86_fp80 %y) nounwind readonly  {
; CHECK-LABEL: @test_logical(
; CHECK-NEXT:  entry:
; CHECK-NEXT:    [[TMP67:%.*]] = fcmp uno x86_fp80 [[Y:%.*]], 0xK00000000000000000000
; CHECK-NEXT:    [[TMP71:%.*]] = fcmp uno float [[X:%.*]], 0.000000e+00
; CHECK-NEXT:    [[BOTHCOND:%.*]] = select i1 [[TMP67]], i1 true, i1 [[TMP71]]
; CHECK-NEXT:    br i1 [[BOTHCOND]], label [[BB74:%.*]], label [[BB80:%.*]]
; CHECK:       bb74:
; CHECK-NEXT:    ret float 0.000000e+00
; CHECK:       bb80:
; CHECK-NEXT:    ret float 0.000000e+00
;
entry:
  %tmp67 = fcmp uno x86_fp80 %y, 0xK00000000000000000000		; <i1> [#uses=1]
  %tmp71 = fcmp uno float %x, 0.000000e+00		; <i1> [#uses=1]
  %bothcond = select i1 %tmp67, i1 true, i1 %tmp71		; <i1> [#uses=1]
  br i1 %bothcond, label %bb74, label %bb80

bb74:		; preds = %entry
  ret float 0.000000e+00

bb80:		; preds = %entry
  ret float 0.000000e+00
}
