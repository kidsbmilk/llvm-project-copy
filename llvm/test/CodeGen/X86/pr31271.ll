; NOTE: Assertions have been autogenerated by utils/update_llc_test_checks.py
; RUN: llc -mtriple=i386-unknown-linux-gnu < %s | FileCheck %s

@c = external dso_local global [1 x i32], align 4

define void @fn1(i32 %k, ptr %p) {
; CHECK-LABEL: fn1:
; CHECK:       # %bb.0:
; CHECK-NEXT:    movl {{[0-9]+}}(%esp), %eax
; CHECK-NEXT:    shll $2, %eax
; CHECK-NEXT:    leal c(%eax), %ecx
; CHECK-NEXT:    xorl %edx, %edx
; CHECK-NEXT:    cmpl %ecx, {{[0-9]+}}(%esp)
; CHECK-NEXT:    setne %dl
; CHECK-NEXT:    addl $c, %eax
; CHECK-NEXT:    movl %edx, (%eax)
; CHECK-NEXT:    je .LBB0_1
; CHECK-NEXT:  # %bb.2: # %r
; CHECK-NEXT:    retl
; CHECK-NEXT:  .LBB0_1: # %u
  %g = getelementptr inbounds [1 x i32], ptr @c, i32 0, i32 %k
  %cmp = icmp ne ptr %p, %g
  %z = zext i1 %cmp to i32
  store i32 %z, ptr undef, align 4
  %cmp2 = icmp eq ptr %g, null
  br i1 %cmp2, label %u, label %r

u:
  unreachable

r:
  ret void
}
