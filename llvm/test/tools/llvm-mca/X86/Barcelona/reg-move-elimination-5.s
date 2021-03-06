# NOTE: Assertions have been autogenerated by utils/update_mca_test_checks.py
# RUN: llvm-mca -mtriple=x86_64-unknown-unknown -mcpu=x86-64 -iterations=3 -timeline -register-file-stats < %s | FileCheck %s

xor %rax, %rax
mov %rax, %rbx
mov %rbx, %rcx
mov %rcx, %rdx
mov %rdx, %rax

# CHECK:      Iterations:        3
# CHECK-NEXT: Instructions:      15
# CHECK-NEXT: Total Cycles:      9
# CHECK-NEXT: Total uOps:        15

# CHECK:      Dispatch Width:    4
# CHECK-NEXT: uOps Per Cycle:    1.67
# CHECK-NEXT: IPC:               1.67
# CHECK-NEXT: Block RThroughput: 1.3

# CHECK:      Instruction Info:
# CHECK-NEXT: [1]: #uOps
# CHECK-NEXT: [2]: Latency
# CHECK-NEXT: [3]: RThroughput
# CHECK-NEXT: [4]: MayLoad
# CHECK-NEXT: [5]: MayStore
# CHECK-NEXT: [6]: HasSideEffects (U)

# CHECK:      [1]    [2]    [3]    [4]    [5]    [6]    Instructions:
# CHECK-NEXT:  1      0     0.25                        xorq	%rax, %rax
# CHECK-NEXT:  1      1     0.33                        movq	%rax, %rbx
# CHECK-NEXT:  1      1     0.33                        movq	%rbx, %rcx
# CHECK-NEXT:  1      1     0.33                        movq	%rcx, %rdx
# CHECK-NEXT:  1      1     0.33                        movq	%rdx, %rax

# CHECK:      Register File statistics:
# CHECK-NEXT: Total number of mappings created:    12
# CHECK-NEXT: Max number of mappings used:         11

# CHECK:      Resources:
# CHECK-NEXT: [0]   - SBDivider
# CHECK-NEXT: [1]   - SBFPDivider
# CHECK-NEXT: [2]   - SBPort0
# CHECK-NEXT: [3]   - SBPort1
# CHECK-NEXT: [4]   - SBPort4
# CHECK-NEXT: [5]   - SBPort5
# CHECK-NEXT: [6.0] - SBPort23
# CHECK-NEXT: [6.1] - SBPort23

# CHECK:      Resource pressure per iteration:
# CHECK-NEXT: [0]    [1]    [2]    [3]    [4]    [5]    [6.0]  [6.1]
# CHECK-NEXT:  -      -     1.33   1.33    -     1.33    -      -

# CHECK:      Resource pressure by instruction:
# CHECK-NEXT: [0]    [1]    [2]    [3]    [4]    [5]    [6.0]  [6.1]  Instructions:
# CHECK-NEXT:  -      -      -      -      -      -      -      -     xorq	%rax, %rax
# CHECK-NEXT:  -      -     0.67    -      -     0.33    -      -     movq	%rax, %rbx
# CHECK-NEXT:  -      -     0.33   0.67    -      -      -      -     movq	%rbx, %rcx
# CHECK-NEXT:  -      -      -     0.67    -     0.33    -      -     movq	%rcx, %rdx
# CHECK-NEXT:  -      -     0.33    -      -     0.67    -      -     movq	%rdx, %rax

# CHECK:      Timeline view:
# CHECK-NEXT: Index     012345678

# CHECK:      [0,0]     DR   .  .   xorq	%rax, %rax
# CHECK-NEXT: [0,1]     DeER .  .   movq	%rax, %rbx
# CHECK-NEXT: [0,2]     D=eER.  .   movq	%rbx, %rcx
# CHECK-NEXT: [0,3]     D==eER  .   movq	%rcx, %rdx
# CHECK-NEXT: [0,4]     .D==eER .   movq	%rdx, %rax
# CHECK-NEXT: [1,0]     .D----R .   xorq	%rax, %rax
# CHECK-NEXT: [1,1]     .DeE--R .   movq	%rax, %rbx
# CHECK-NEXT: [1,2]     .D=eE-R .   movq	%rbx, %rcx
# CHECK-NEXT: [1,3]     . D=eER .   movq	%rcx, %rdx
# CHECK-NEXT: [1,4]     . D==eER.   movq	%rdx, %rax
# CHECK-NEXT: [2,0]     . D----R.   xorq	%rax, %rax
# CHECK-NEXT: [2,1]     . DeE--R.   movq	%rax, %rbx
# CHECK-NEXT: [2,2]     .  DeE-R.   movq	%rbx, %rcx
# CHECK-NEXT: [2,3]     .  D=eER.   movq	%rcx, %rdx
# CHECK-NEXT: [2,4]     .  D==eER   movq	%rdx, %rax

# CHECK:      Average Wait times (based on the timeline view):
# CHECK-NEXT: [0]: Executions
# CHECK-NEXT: [1]: Average time spent waiting in a scheduler's queue
# CHECK-NEXT: [2]: Average time spent waiting in a scheduler's queue while ready
# CHECK-NEXT: [3]: Average time elapsed from WB until retire stage

# CHECK:            [0]    [1]    [2]    [3]
# CHECK-NEXT: 0.     3     0.0    0.0    2.7       xorq	%rax, %rax
# CHECK-NEXT: 1.     3     1.0    1.0    1.3       movq	%rax, %rbx
# CHECK-NEXT: 2.     3     1.7    0.0    0.7       movq	%rbx, %rcx
# CHECK-NEXT: 3.     3     2.3    0.0    0.0       movq	%rcx, %rdx
# CHECK-NEXT: 4.     3     3.0    0.0    0.0       movq	%rdx, %rax
# CHECK-NEXT:        3     1.6    0.2    0.9       <total>
