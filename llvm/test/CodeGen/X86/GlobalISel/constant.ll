; NOTE: Assertions have been autogenerated by utils/update_llc_test_checks.py
; RUN: llc -mtriple=x86_64-linux-gnu -global-isel -verify-machineinstrs < %s -o - | FileCheck %s

define i8 @const_i8() {
; CHECK-LABEL: const_i8:
; CHECK:       # %bb.0:
; CHECK-NEXT:    movb $2, %al
; CHECK-NEXT:    retq
  ret i8 2
}

define i16 @const_i16() {
; CHECK-LABEL: const_i16:
; CHECK:       # %bb.0:
; CHECK-NEXT:    movw $3, %ax
; CHECK-NEXT:    retq
  ret i16 3
}

define i32 @const_i32() {
; CHECK-LABEL: const_i32:
; CHECK:       # %bb.0:
; CHECK-NEXT:    movl $4, %eax
; CHECK-NEXT:    retq
  ret i32 4
}

define i64 @const_i64() {
; CHECK-LABEL: const_i64:
; CHECK:       # %bb.0:
; CHECK-NEXT:    movabsq $68719476720, %rax # imm = 0xFFFFFFFF0
; CHECK-NEXT:    retq
  ret i64 68719476720
}

;i64 value fit into u32
define i64 @const_i64_u32() {
; CHECK-LABEL: const_i64_u32:
; CHECK:       # %bb.0:
; CHECK-NEXT:    movl $1879048192, %eax # imm = 0x70000000
; CHECK-NEXT:    retq
  ret i64 1879048192
}

;i64 value fit into i32
define i64 @const_i64_i32() {
; CHECK-LABEL: const_i64_i32:
; CHECK:       # %bb.0:
; CHECK-NEXT:    movq $-1, %rax
; CHECK-NEXT:    retq
  ret i64 -1
}

define void @main(ptr %data) {
; CHECK-LABEL: main:
; CHECK:       # %bb.0:
; CHECK-NEXT:    movq $0, %rax
; CHECK-NEXT:    movq %rax, (%rdi)
; CHECK-NEXT:    retq
  store ptr null, ptr %data, align 8
  ret void
}

