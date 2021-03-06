; NOTE: Assertions have been autogenerated by utils/update_llc_test_checks.py
; RUN: llc < %s -mtriple=x86_64-unknown-unknown | FileCheck %s

; Various tests for ands that should be implemented with movzx, but aren't due
; demanded bits shortcomings.

; The backend will insert a zext to promote the shift to i32.
define i16 @test1(i16 %x) {
; CHECK-LABEL: test1:
; CHECK:       # %bb.0:
; CHECK-NEXT:    movzwl %di, %eax
; CHECK-NEXT:    shrl %eax
; CHECK-NEXT:    # kill: def $ax killed $ax killed $eax
; CHECK-NEXT:    retq
  %y = lshr i16 %x, 1
  ret i16 %y
}

define i32 @test2(i32 %x) {
; CHECK-LABEL: test2:
; CHECK:       # %bb.0:
; CHECK-NEXT:    movzwl %di, %eax
; CHECK-NEXT:    shrl %eax
; CHECK-NEXT:    retq
  %y = and i32 %x, 65535
  %z = lshr i32 %y, 1
  ret i32 %z
}

define i32 @test3(i32 %x) {
; CHECK-LABEL: test3:
; CHECK:       # %bb.0:
; CHECK-NEXT:    movzbl %dil, %eax
; CHECK-NEXT:    shrl %eax
; CHECK-NEXT:    retq
  %y = and i32 %x, 255
  %z = lshr i32 %y, 1
  ret i32 %z
}

define i16 @test4(i16 %x) {
; CHECK-LABEL: test4:
; CHECK:       # %bb.0:
; CHECK-NEXT:    movzbl %dil, %eax
; CHECK-NEXT:    shrl %eax
; CHECK-NEXT:    # kill: def $ax killed $ax killed $eax
; CHECK-NEXT:    retq
  %y = and i16 %x, 255
  %z = lshr i16 %y, 1
  ret i16 %z
}

define i16 @test5(i16 %x) {
; CHECK-LABEL: test5:
; CHECK:       # %bb.0:
; CHECK-NEXT:    movzwl %di, %eax
; CHECK-NEXT:    shrl $9, %eax
; CHECK-NEXT:    # kill: def $ax killed $ax killed $eax
; CHECK-NEXT:    retq
  %y = lshr i16 %x, 9
  ret i16 %y
}

define i32 @test6(i32 %x) {
; CHECK-LABEL: test6:
; CHECK:       # %bb.0:
; CHECK-NEXT:    movzwl %di, %eax
; CHECK-NEXT:    shrl $9, %eax
; CHECK-NEXT:    retq
  %y = and i32 %x, 65535
  %z = lshr i32 %y, 9
  ret i32 %z
}

; TODO: We could turn this and into a zero extend.
define i32 @test7(i32 %x) {
; CHECK-LABEL: test7:
; CHECK:       # %bb.0:
; CHECK-NEXT:    orl $1, %edi
; CHECK-NEXT:    movzwl %di, %eax
; CHECK-NEXT:    retq
  %y = and i32 %x, 65534
  %z = or i32 %y, 1
  ret i32 %z
}

; We actually get a movzx on this one, but only because we canonicalize the and
; after the or before SimplifyDemandedBits messes it up.
define i32 @test8(i32 %x) {
; CHECK-LABEL: test8:
; CHECK:       # %bb.0:
; CHECK-NEXT:    orl $1, %edi
; CHECK-NEXT:    movzwl %di, %eax
; CHECK-NEXT:    retq
  %y = and i32 %x, 65535
  %z = or i32 %y, 1
  ret i32 %z
}

define i64 @add_neg_one(i64 %x) {
; CHECK-LABEL: add_neg_one:
; CHECK:       # %bb.0:
; CHECK-NEXT:    leal -1(%rdi), %eax
; CHECK-NEXT:    andl %edi, %eax
; CHECK-NEXT:    movzwl %ax, %eax
; CHECK-NEXT:    retq
  %a1 = and i64 %x, 65535
  %a2 = add i64 %x, 65535
  %r = and i64 %a1, %a2
  ret i64 %r
}

define i64 @sub_neg_one(i64 %x) {
; CHECK-LABEL: sub_neg_one:
; CHECK:       # %bb.0:
; CHECK-NEXT:    leal -65535(%rdi), %eax
; CHECK-NEXT:    andl %edi, %eax
; CHECK-NEXT:    movzwl %ax, %eax
; CHECK-NEXT:    retq
  %a1 = and i64 %x, 65535
  %a2 = sub i64 %x, 65535
  %r = and i64 %a1, %a2
  ret i64 %r
}

define i64 @mul_neg_one(i64 %x) {
; CHECK-LABEL: mul_neg_one:
; CHECK:       # %bb.0:
; CHECK-NEXT:    movl %edi, %eax
; CHECK-NEXT:    negl %eax
; CHECK-NEXT:    andl %edi, %eax
; CHECK-NEXT:    movzwl %ax, %eax
; CHECK-NEXT:    retq
  %a1 = and i64 %x, 65535
  %a2 = mul i64 %x, 65535
  %r = and i64 %a1, %a2
  ret i64 %r
}

define i32 @PR36689(ptr) {
; CHECK-LABEL: PR36689:
; CHECK:       # %bb.0:
; CHECK-NEXT:    movzwl (%rdi), %eax
; CHECK-NEXT:    orl $255, %eax
; CHECK-NEXT:    retq
  %2 = load i32, ptr %0
  %3 = and i32 %2, 65280
  %4 = or i32 %3, 255
  ret i32 %4
}
