; NOTE: Assertions have been autogenerated by utils/update_llc_test_checks.py
; RUN: llc < %s -mtriple=i686-- -tailcallopt | FileCheck %s

; Bug 4396. This tail call can NOT be optimized.

declare fastcc ptr @_D3gcx2GC12mallocNoSyncMFmkZPv() nounwind

define fastcc ptr @_D3gcx2GC12callocNoSyncMFmkZPv() nounwind {
; CHECK-LABEL: _D3gcx2GC12callocNoSyncMFmkZPv:
; CHECK:       # %bb.0: # %entry
; CHECK-NEXT:    pushl %esi
; CHECK-NEXT:    calll _D3gcx2GC12mallocNoSyncMFmkZPv@PLT
; CHECK-NEXT:    movl %eax, %esi
; CHECK-NEXT:    pushl $0
; CHECK-NEXT:    pushl $2
; CHECK-NEXT:    pushl $0
; CHECK-NEXT:    pushl %eax
; CHECK-NEXT:    calll memset@PLT
; CHECK-NEXT:    addl $16, %esp
; CHECK-NEXT:    movl %esi, %eax
; CHECK-NEXT:    popl %esi
; CHECK-NEXT:    retl
entry:
	%tmp6 = tail call fastcc ptr @_D3gcx2GC12mallocNoSyncMFmkZPv()		; <ptr> [#uses=2]
	%tmp9 = tail call ptr @memset(ptr %tmp6, i32 0, i64 2)		; <ptr> [#uses=0]
	ret ptr %tmp6
}

declare ptr @memset(ptr, i32, i64)
