; RUN: llc -x86-discriminate-memops  < %s | FileCheck %s
;
; original source, compiled with -O3 -gmlt -fdebug-info-for-profiling:
; int sum(int* arr, int pos1, int pos2) {
;   return arr[pos1] + arr[pos2];
; }
;
; ModuleID = 'test.cc'
source_filename = "test.cc"
target datalayout = "e-m:e-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

declare void @llvm.prefetch(ptr, i32, i32, i32)
; Function Attrs: norecurse nounwind readonly uwtable
define i32 @sum(ptr %arr, i32 %pos1, i32 %pos2) !dbg !7 {
entry:
  %idxprom = sext i32 %pos1 to i64
  %arrayidx = getelementptr inbounds i32, ptr %arr, i64 %idxprom
  %0 = load i32, ptr %arrayidx, align 4
  %idxprom1 = sext i32 %pos2 to i64
  %arrayidx2 = getelementptr inbounds i32, ptr %arr, i64 %idxprom1
  %1 = load i32, ptr %arrayidx2, align 4
  %add = add nsw i32 %1, %0, !dbg !15
  ret i32 %add
}

attributes #0 = { "target-cpu"="x86-64" }

!llvm.dbg.cu = !{!0}
!llvm.module.flags = !{!3, !4, !5}
!llvm.ident = !{!6}

!0 = distinct !DICompileUnit(language: DW_LANG_C_plus_plus, file: !1, isOptimized: true, runtimeVersion: 0, emissionKind: LineTablesOnly, enums: !2, debugInfoForProfiling: true)
!1 = !DIFile(filename: "test.cc", directory: "/tmp")
!2 = !{}
!3 = !{i32 2, !"Dwarf Version", i32 4}
!4 = !{i32 2, !"Debug Info Version", i32 3}
!5 = !{i32 1, !"wchar_size", i32 4}
!6 = !{!"clang version 7.0.0 (trunk 322155) (llvm/trunk 322159)"}
!7 = distinct !DISubprogram(name: "sum", linkageName: "sum", scope: !1, file: !1, line: 1, type: !8, isLocal: false, isDefinition: true, scopeLine: 1, flags: DIFlagPrototyped, isOptimized: true, unit: !0)
!8 = !DISubroutineType(types: !2)
!9 = !DILocation(line: 2, column: 10, scope: !7)
!10 = !{!11, !11, i64 0}
!11 = !{!"int", !12, i64 0}
!12 = !{!"omnipotent char", !13, i64 0}
!13 = !{!"Simple C++ TBAA"}
!15 = !DILocation(line: 2, column: 20, scope: !7)


;CHECK-LABEL: sum:
;CHECK:       # %bb.0:
;CHECK:       .loc 1 1 0 {{.*}} discriminator 2
;CHECK-NEXT:  movl (%rdi,%rax,4), %eax
;CHECK-NEXT:  .loc 1 2 20
;CHECK-NEXT:  addl (%rdi,%rcx,4), %eax
