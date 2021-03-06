; RUN: llc < %s -mtriple=i686-unknown-unknown -mattr=+xsave | FileCheck %s

define void @test_xsave(ptr %ptr, i32 %hi, i32 %lo) {
; CHECK-LABEL: test_xsave
; CHECK: movl  8(%esp), %edx
; CHECK: movl  12(%esp), %eax
; CHECK: movl  4(%esp), %ecx
; CHECK: xsave (%ecx)
  call void @llvm.x86.xsave(ptr %ptr, i32 %hi, i32 %lo)
  ret void;
}
declare void @llvm.x86.xsave(ptr, i32, i32)

define void @test_xrstor(ptr %ptr, i32 %hi, i32 %lo) {
; CHECK-LABEL: test_xrstor
; CHECK: movl   8(%esp), %edx
; CHECK: movl   12(%esp), %eax
; CHECK: movl   4(%esp), %ecx
; CHECK: xrstor (%ecx)
  call void @llvm.x86.xrstor(ptr %ptr, i32 %hi, i32 %lo)
  ret void;
}
declare void @llvm.x86.xrstor(ptr, i32, i32)
