; NOTE: Assertions have been autogenerated by utils/update_llc_test_checks.py
; RUN: llc < %s -mtriple=x86_64-unknown | FileCheck %s -check-prefix=X64
; RUN: llc < %s -mtriple=i686-unknown   | FileCheck %s -check-prefix=X86

%struct.SA = type { i32 , i32  , i32 , i32 ,i32 }

define void @test_func(ptr nocapture %ctx, i32 %n) local_unnamed_addr {
; X64-LABEL: test_func:
; X64:       # %bb.0: # %entry
; X64-NEXT:    movl (%rdi), %eax
; X64-NEXT:    movl 16(%rdi), %ecx
; X64-NEXT:    leal (%rax,%rcx), %edx
; X64-NEXT:    leal 1(%rax,%rcx), %eax
; X64-NEXT:    movl %eax, 12(%rdi)
; X64-NEXT:    leal 1(%rcx,%rdx), %eax
; X64-NEXT:    movl %eax, 16(%rdi)
; X64-NEXT:    retq
;
; X86-LABEL: test_func:
; X86:       # %bb.0: # %entry
; X86-NEXT:    pushl %esi
; X86-NEXT:    .cfi_def_cfa_offset 8
; X86-NEXT:    .cfi_offset %esi, -8
; X86-NEXT:    movl {{[0-9]+}}(%esp), %eax
; X86-NEXT:    movl (%eax), %ecx
; X86-NEXT:    movl 16(%eax), %edx
; X86-NEXT:    leal 1(%ecx,%edx), %esi
; X86-NEXT:    addl %edx, %ecx
; X86-NEXT:    movl %esi, 12(%eax)
; X86-NEXT:    leal 1(%edx,%ecx), %ecx
; X86-NEXT:    movl %ecx, 16(%eax)
; X86-NEXT:    popl %esi
; X86-NEXT:    .cfi_def_cfa_offset 4
; X86-NEXT:    retl
 entry:
   %0 = load i32, ptr %ctx, align 8
   %h3 = getelementptr inbounds %struct.SA, ptr %ctx, i64 0, i32 3
   %h4 = getelementptr inbounds %struct.SA, ptr %ctx, i64 0, i32 4
   %1 = load i32, ptr %h4, align 8
   %add = add i32 %0, 1
   %add4 = add i32 %add, %1
   store i32 %add4, ptr %h3, align 4
   %add29 = add i32 %add4 , %1
   store i32 %add29, ptr %h4, align 8
   ret void
}
