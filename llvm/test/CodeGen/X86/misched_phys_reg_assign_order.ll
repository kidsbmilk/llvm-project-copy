; NOTE: Assertions have been autogenerated by utils/update_llc_test_checks.py
; RUN: llc %s -O2 -mtriple=i686-unknown-linux-gnu -o - | FileCheck %s

@f = global ptr zeroinitializer

; PR39391 - The load of %v1 should be scheduled before the zeroing of the A-D registers.

define void @g() #0 {
; CHECK-LABEL: g:
; CHECK:       # %bb.0: # %entry
; CHECK-NEXT:    pushl %ebp
; CHECK-NEXT:    .cfi_def_cfa_offset 8
; CHECK-NEXT:    .cfi_offset %ebp, -8
; CHECK-NEXT:    movl %esp, %ebp
; CHECK-NEXT:    .cfi_def_cfa_register %ebp
; CHECK-NEXT:    pushl %ebx
; CHECK-NEXT:    pushl %esi
; CHECK-NEXT:    subl $16, %esp
; CHECK-NEXT:    .cfi_offset %esi, -16
; CHECK-NEXT:    .cfi_offset %ebx, -12
; CHECK-NEXT:    movl f, %esi
; CHECK-NEXT:    movb (%esi), %al
; CHECK-NEXT:    movb %al, {{[-0-9]+}}(%e{{[sb]}}p) # 1-byte Spill
; CHECK-NEXT:    xorl %eax, %eax
; CHECK-NEXT:    xorl %edx, %edx
; CHECK-NEXT:    xorl %ecx, %ecx
; CHECK-NEXT:    xorl %ebx, %ebx
; CHECK-NEXT:    lock cmpxchg8b (%esi)
; CHECK-NEXT:    cmpb $0, {{[-0-9]+}}(%e{{[sb]}}p) # 1-byte Folded Reload
; CHECK-NEXT:    je .LBB0_2
; CHECK-NEXT:  # %bb.1: # %.
; CHECK-NEXT:    calll m@PLT
; CHECK-NEXT:  .LBB0_2: # %k.end
entry:
  %p = load ptr, ptr @f
  %v1 = load atomic i8, ptr %p monotonic, align 1
  %v2 = load atomic i64, ptr %p monotonic, align 8
  %j.h = icmp eq i8 %v1, 0
  br i1 %j.h, label %k.end, label %.

.:                                                ; preds = %entry
  %v3 = call i32 @m()
  unreachable

k.end:                                            ; preds = %entry
  unreachable
}

declare i32 @m()

attributes #0 = { noimplicitfloat "frame-pointer"="non-leaf" }
