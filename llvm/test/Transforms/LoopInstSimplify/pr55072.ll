; NOTE: Assertions have been autogenerated by utils/update_test_checks.py
; RUN: opt -S %s -passes=loop-instsimplify | FileCheck %s
; RUN: opt -S %s -passes='loop-mssa(loop-instsimplify)' -verify-memoryssa | FileCheck %s

define i32 @test_01() {
; CHECK-LABEL: @test_01(
; CHECK-NEXT:  bb:
; CHECK-NEXT:    br label [[LOOP:%.*]]
; CHECK:       loop:
; CHECK-NEXT:    br label [[LOOP]]
; CHECK:       unreached:
; CHECK-NEXT:    ret i32 0
;
bb:
  br label %loop

loop:                                              ; preds = %bb, %loop
  %tmp = lshr exact i32 undef, 16
  br label %loop

unreached:                                              ; No predecessors!
  ret i32 %tmp
}
