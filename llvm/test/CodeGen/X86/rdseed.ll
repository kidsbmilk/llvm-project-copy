; NOTE: Assertions have been autogenerated by utils/update_llc_test_checks.py
; RUN: llc < %s -mtriple=i686-unknown-unknown -mcpu=core-avx-i -mattr=+rdseed | FileCheck %s --check-prefix=X86
; RUN: llc < %s -mtriple=x86_64-unknown-unknown -mcpu=core-avx-i -mattr=+rdseed | FileCheck %s --check-prefix=X64

declare {i16, i32} @llvm.x86.rdseed.16()
declare {i32, i32} @llvm.x86.rdseed.32()

define i32 @_rdseed16_step(ptr %random_val) {
; X86-LABEL: _rdseed16_step:
; X86:       # %bb.0:
; X86-NEXT:    movl {{[0-9]+}}(%esp), %ecx
; X86-NEXT:    rdseedw %ax
; X86-NEXT:    movzwl %ax, %edx
; X86-NEXT:    movl $1, %eax
; X86-NEXT:    cmovael %edx, %eax
; X86-NEXT:    movw %dx, (%ecx)
; X86-NEXT:    retl
;
; X64-LABEL: _rdseed16_step:
; X64:       # %bb.0:
; X64-NEXT:    rdseedw %ax
; X64-NEXT:    movzwl %ax, %ecx
; X64-NEXT:    movl $1, %eax
; X64-NEXT:    cmovael %ecx, %eax
; X64-NEXT:    movw %cx, (%rdi)
; X64-NEXT:    retq
  %call = call {i16, i32} @llvm.x86.rdseed.16()
  %randval = extractvalue {i16, i32} %call, 0
  store i16 %randval, ptr %random_val
  %isvalid = extractvalue {i16, i32} %call, 1
  ret i32 %isvalid
}

define i32 @_rdseed32_step(ptr %random_val) {
; X86-LABEL: _rdseed32_step:
; X86:       # %bb.0:
; X86-NEXT:    movl {{[0-9]+}}(%esp), %ecx
; X86-NEXT:    rdseedl %edx
; X86-NEXT:    movl $1, %eax
; X86-NEXT:    cmovael %edx, %eax
; X86-NEXT:    movl %edx, (%ecx)
; X86-NEXT:    retl
;
; X64-LABEL: _rdseed32_step:
; X64:       # %bb.0:
; X64-NEXT:    rdseedl %ecx
; X64-NEXT:    movl $1, %eax
; X64-NEXT:    cmovael %ecx, %eax
; X64-NEXT:    movl %ecx, (%rdi)
; X64-NEXT:    retq
  %call = call {i32, i32} @llvm.x86.rdseed.32()
  %randval = extractvalue {i32, i32} %call, 0
  store i32 %randval, ptr %random_val
  %isvalid = extractvalue {i32, i32} %call, 1
  ret i32 %isvalid
}
