; NOTE: Assertions have been autogenerated by utils/update_llc_test_checks.py
; RUN: llc -O0 < %s -mtriple=x86_64-linux-generic -verify-machineinstrs -mattr=sse2 | FileCheck --check-prefixes=CHECK,CHECK-O0 %s
; RUN: llc -O3 < %s -mtriple=x86_64-linux-generic -verify-machineinstrs -mattr=sse2 | FileCheck --check-prefixes=CHECK,CHECK-O3 %s

define i8 @load_i8(ptr %ptr) {
; CHECK-LABEL: load_i8:
; CHECK:       # %bb.0:
; CHECK-NEXT:    movb (%rdi), %al
; CHECK-NEXT:    retq
  %v = load atomic i8, ptr %ptr monotonic, align 1
  ret i8 %v
}

define void @store_i8(ptr %ptr, i8 %v) {
; CHECK-O0-LABEL: store_i8:
; CHECK-O0:       # %bb.0:
; CHECK-O0-NEXT:    movb %sil, %al
; CHECK-O0-NEXT:    movb %al, (%rdi)
; CHECK-O0-NEXT:    retq
;
; CHECK-O3-LABEL: store_i8:
; CHECK-O3:       # %bb.0:
; CHECK-O3-NEXT:    movb %sil, (%rdi)
; CHECK-O3-NEXT:    retq
  store atomic i8 %v, ptr %ptr monotonic, align 1
  ret void
}

define i16 @load_i16(ptr %ptr) {
; CHECK-O0-LABEL: load_i16:
; CHECK-O0:       # %bb.0:
; CHECK-O0-NEXT:    movw (%rdi), %ax
; CHECK-O0-NEXT:    retq
;
; CHECK-O3-LABEL: load_i16:
; CHECK-O3:       # %bb.0:
; CHECK-O3-NEXT:    movzwl (%rdi), %eax
; CHECK-O3-NEXT:    retq
  %v = load atomic i16, ptr %ptr monotonic, align 2
  ret i16 %v
}


define void @store_i16(ptr %ptr, i16 %v) {
; CHECK-O0-LABEL: store_i16:
; CHECK-O0:       # %bb.0:
; CHECK-O0-NEXT:    movw %si, %ax
; CHECK-O0-NEXT:    movw %ax, (%rdi)
; CHECK-O0-NEXT:    retq
;
; CHECK-O3-LABEL: store_i16:
; CHECK-O3:       # %bb.0:
; CHECK-O3-NEXT:    movw %si, (%rdi)
; CHECK-O3-NEXT:    retq
  store atomic i16 %v, ptr %ptr monotonic, align 2
  ret void
}

define i32 @load_i32(ptr %ptr) {
; CHECK-LABEL: load_i32:
; CHECK:       # %bb.0:
; CHECK-NEXT:    movl (%rdi), %eax
; CHECK-NEXT:    retq
  %v = load atomic i32, ptr %ptr monotonic, align 4
  ret i32 %v
}

define void @store_i32(ptr %ptr, i32 %v) {
; CHECK-LABEL: store_i32:
; CHECK:       # %bb.0:
; CHECK-NEXT:    movl %esi, (%rdi)
; CHECK-NEXT:    retq
  store atomic i32 %v, ptr %ptr monotonic, align 4
  ret void
}

define i64 @load_i64(ptr %ptr) {
; CHECK-LABEL: load_i64:
; CHECK:       # %bb.0:
; CHECK-NEXT:    movq (%rdi), %rax
; CHECK-NEXT:    retq
  %v = load atomic i64, ptr %ptr monotonic, align 8
  ret i64 %v
}

define void @store_i64(ptr %ptr, i64 %v) {
; CHECK-LABEL: store_i64:
; CHECK:       # %bb.0:
; CHECK-NEXT:    movq %rsi, (%rdi)
; CHECK-NEXT:    retq
  store atomic i64 %v, ptr %ptr monotonic, align 8
  ret void
}
