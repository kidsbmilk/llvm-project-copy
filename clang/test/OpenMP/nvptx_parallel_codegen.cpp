// NOTE: Assertions have been autogenerated by utils/update_cc_test_checks.py UTC_ARGS: --function-signature --include-generated-funcs --replace-value-regex "__omp_offloading_[0-9a-z]+_[0-9a-z]+" "reduction_size[.].+[.]" "pl_cond[.].+[.|,]" --prefix-filecheck-ir-name _
// Test target codegen - host bc file has to be created first.
// RUN: %clang_cc1 -no-opaque-pointers -verify -fopenmp -x c++ -triple powerpc64le-unknown-unknown -fopenmp-targets=nvptx64-nvidia-cuda -emit-llvm-bc %s -o %t-ppc-host.bc
// RUN: %clang_cc1 -no-opaque-pointers -verify -fopenmp -x c++ -triple nvptx64-unknown-unknown -aux-triple powerpc64le-unknown-unknown -fopenmp-targets=nvptx64-nvidia-cuda -emit-llvm %s -fopenmp-is-device -fopenmp-host-ir-file-path %t-ppc-host.bc -o - -disable-llvm-optzns | FileCheck %s --check-prefix=CHECK1
// RUN: %clang_cc1 -no-opaque-pointers -verify -fopenmp -x c++ -triple i386-unknown-unknown -fopenmp-targets=nvptx-nvidia-cuda -emit-llvm-bc %s -o %t-x86-host.bc
// RUN: %clang_cc1 -no-opaque-pointers -verify -fopenmp -fexceptions -fcxx-exceptions -x c++ -triple nvptx-unknown-unknown -aux-triple i386-unknown-unknown -fopenmp-targets=nvptx-nvidia-cuda -emit-llvm %s -fopenmp-is-device -fopenmp-host-ir-file-path %t-x86-host.bc -o - -disable-llvm-optzns -disable-O0-optnone | FileCheck %s --check-prefix=CHECK2
// expected-no-diagnostics
#ifndef HEADER
#define HEADER

template<typename tx>
tx ftemplate(int n) {
  tx a = 0;
  short aa = 0;
  tx b[10];

  #pragma omp target if(0)
  {
    #pragma omp parallel
    {
      int a = 41;
    }
    a += 1;
  }

  #pragma omp target
  {
    #pragma omp parallel
    {
      int a = 42;
    }
    #pragma omp parallel if(0)
    {
      int a = 43;
    }
    #pragma omp parallel if(1)
    {
      int a = 44;
    }
    a += 1;
  }

  #pragma omp target if(n>40)
  {
    #pragma omp parallel if(n>1000)
    {
      int a = 45;
#pragma omp barrier
    }
    a += 1;
    aa += 1;
    b[2] += 1;
  }

  #pragma omp target
  {
    #pragma omp parallel
    {
    #pragma omp critical
    ++a;
    }
    ++a;
  }
  return a;
}

int bar(int n){
  int a = 0;

  a += ftemplate<int>(n);

  return a;
}

#endif
// CHECK1-LABEL: define {{[^@]+}}@{{__omp_offloading_[0-9a-z]+_[0-9a-z]+}}__Z9ftemplateIiET_i_l26
// CHECK1-SAME: (i64 noundef [[A:%.*]]) #[[ATTR0:[0-9]+]] {
// CHECK1-NEXT:  entry:
// CHECK1-NEXT:    [[A_ADDR:%.*]] = alloca i64, align 8
// CHECK1-NEXT:    [[CAPTURED_VARS_ADDRS:%.*]] = alloca [0 x i8*], align 8
// CHECK1-NEXT:    [[CAPTURED_VARS_ADDRS1:%.*]] = alloca [0 x i8*], align 8
// CHECK1-NEXT:    [[CAPTURED_VARS_ADDRS2:%.*]] = alloca [0 x i8*], align 8
// CHECK1-NEXT:    store i64 [[A]], i64* [[A_ADDR]], align 8
// CHECK1-NEXT:    [[CONV:%.*]] = bitcast i64* [[A_ADDR]] to i32*
// CHECK1-NEXT:    [[TMP0:%.*]] = call i32 @__kmpc_target_init(%struct.ident_t* @[[GLOB1:[0-9]+]], i8 1, i1 true, i1 true)
// CHECK1-NEXT:    [[EXEC_USER_CODE:%.*]] = icmp eq i32 [[TMP0]], -1
// CHECK1-NEXT:    br i1 [[EXEC_USER_CODE]], label [[USER_CODE_ENTRY:%.*]], label [[WORKER_EXIT:%.*]]
// CHECK1:       user_code.entry:
// CHECK1-NEXT:    [[TMP1:%.*]] = call i32 @__kmpc_global_thread_num(%struct.ident_t* @[[GLOB1]])
// CHECK1-NEXT:    [[TMP2:%.*]] = bitcast [0 x i8*]* [[CAPTURED_VARS_ADDRS]] to i8**
// CHECK1-NEXT:    call void @__kmpc_parallel_51(%struct.ident_t* @[[GLOB1]], i32 [[TMP1]], i32 1, i32 -1, i32 -1, i8* bitcast (void (i32*, i32*)* @__omp_outlined__ to i8*), i8* bitcast (void (i16, i32)* @__omp_outlined___wrapper to i8*), i8** [[TMP2]], i64 0)
// CHECK1-NEXT:    [[TMP3:%.*]] = bitcast [0 x i8*]* [[CAPTURED_VARS_ADDRS1]] to i8**
// CHECK1-NEXT:    call void @__kmpc_parallel_51(%struct.ident_t* @[[GLOB1]], i32 [[TMP1]], i32 0, i32 -1, i32 -1, i8* bitcast (void (i32*, i32*)* @__omp_outlined__1 to i8*), i8* bitcast (void (i16, i32)* @__omp_outlined__1_wrapper to i8*), i8** [[TMP3]], i64 0)
// CHECK1-NEXT:    [[TMP4:%.*]] = bitcast [0 x i8*]* [[CAPTURED_VARS_ADDRS2]] to i8**
// CHECK1-NEXT:    call void @__kmpc_parallel_51(%struct.ident_t* @[[GLOB1]], i32 [[TMP1]], i32 1, i32 -1, i32 -1, i8* bitcast (void (i32*, i32*)* @__omp_outlined__2 to i8*), i8* bitcast (void (i16, i32)* @__omp_outlined__2_wrapper to i8*), i8** [[TMP4]], i64 0)
// CHECK1-NEXT:    [[TMP5:%.*]] = load i32, i32* [[CONV]], align 4
// CHECK1-NEXT:    [[ADD:%.*]] = add nsw i32 [[TMP5]], 1
// CHECK1-NEXT:    store i32 [[ADD]], i32* [[CONV]], align 4
// CHECK1-NEXT:    call void @__kmpc_target_deinit(%struct.ident_t* @[[GLOB1]], i8 1, i1 true)
// CHECK1-NEXT:    ret void
// CHECK1:       worker.exit:
// CHECK1-NEXT:    ret void
//
//
// CHECK1-LABEL: define {{[^@]+}}@__omp_outlined__
// CHECK1-SAME: (i32* noalias noundef [[DOTGLOBAL_TID_:%.*]], i32* noalias noundef [[DOTBOUND_TID_:%.*]]) #[[ATTR1:[0-9]+]] {
// CHECK1-NEXT:  entry:
// CHECK1-NEXT:    [[DOTGLOBAL_TID__ADDR:%.*]] = alloca i32*, align 8
// CHECK1-NEXT:    [[DOTBOUND_TID__ADDR:%.*]] = alloca i32*, align 8
// CHECK1-NEXT:    [[A:%.*]] = alloca i32, align 4
// CHECK1-NEXT:    store i32* [[DOTGLOBAL_TID_]], i32** [[DOTGLOBAL_TID__ADDR]], align 8
// CHECK1-NEXT:    store i32* [[DOTBOUND_TID_]], i32** [[DOTBOUND_TID__ADDR]], align 8
// CHECK1-NEXT:    store i32 42, i32* [[A]], align 4
// CHECK1-NEXT:    ret void
//
//
// CHECK1-LABEL: define {{[^@]+}}@__omp_outlined___wrapper
// CHECK1-SAME: (i16 noundef zeroext [[TMP0:%.*]], i32 noundef [[TMP1:%.*]]) #[[ATTR2:[0-9]+]] {
// CHECK1-NEXT:  entry:
// CHECK1-NEXT:    [[DOTADDR:%.*]] = alloca i16, align 2
// CHECK1-NEXT:    [[DOTADDR1:%.*]] = alloca i32, align 4
// CHECK1-NEXT:    [[DOTZERO_ADDR:%.*]] = alloca i32, align 4
// CHECK1-NEXT:    [[GLOBAL_ARGS:%.*]] = alloca i8**, align 8
// CHECK1-NEXT:    store i16 [[TMP0]], i16* [[DOTADDR]], align 2
// CHECK1-NEXT:    store i32 [[TMP1]], i32* [[DOTADDR1]], align 4
// CHECK1-NEXT:    store i32 0, i32* [[DOTZERO_ADDR]], align 4
// CHECK1-NEXT:    call void @__kmpc_get_shared_variables(i8*** [[GLOBAL_ARGS]])
// CHECK1-NEXT:    call void @__omp_outlined__(i32* [[DOTADDR1]], i32* [[DOTZERO_ADDR]]) #[[ATTR3:[0-9]+]]
// CHECK1-NEXT:    ret void
//
//
// CHECK1-LABEL: define {{[^@]+}}@__omp_outlined__1
// CHECK1-SAME: (i32* noalias noundef [[DOTGLOBAL_TID_:%.*]], i32* noalias noundef [[DOTBOUND_TID_:%.*]]) #[[ATTR1]] {
// CHECK1-NEXT:  entry:
// CHECK1-NEXT:    [[DOTGLOBAL_TID__ADDR:%.*]] = alloca i32*, align 8
// CHECK1-NEXT:    [[DOTBOUND_TID__ADDR:%.*]] = alloca i32*, align 8
// CHECK1-NEXT:    [[A:%.*]] = alloca i32, align 4
// CHECK1-NEXT:    store i32* [[DOTGLOBAL_TID_]], i32** [[DOTGLOBAL_TID__ADDR]], align 8
// CHECK1-NEXT:    store i32* [[DOTBOUND_TID_]], i32** [[DOTBOUND_TID__ADDR]], align 8
// CHECK1-NEXT:    store i32 43, i32* [[A]], align 4
// CHECK1-NEXT:    ret void
//
//
// CHECK1-LABEL: define {{[^@]+}}@__omp_outlined__1_wrapper
// CHECK1-SAME: (i16 noundef zeroext [[TMP0:%.*]], i32 noundef [[TMP1:%.*]]) #[[ATTR2]] {
// CHECK1-NEXT:  entry:
// CHECK1-NEXT:    [[DOTADDR:%.*]] = alloca i16, align 2
// CHECK1-NEXT:    [[DOTADDR1:%.*]] = alloca i32, align 4
// CHECK1-NEXT:    [[DOTZERO_ADDR:%.*]] = alloca i32, align 4
// CHECK1-NEXT:    [[GLOBAL_ARGS:%.*]] = alloca i8**, align 8
// CHECK1-NEXT:    store i16 [[TMP0]], i16* [[DOTADDR]], align 2
// CHECK1-NEXT:    store i32 [[TMP1]], i32* [[DOTADDR1]], align 4
// CHECK1-NEXT:    store i32 0, i32* [[DOTZERO_ADDR]], align 4
// CHECK1-NEXT:    call void @__kmpc_get_shared_variables(i8*** [[GLOBAL_ARGS]])
// CHECK1-NEXT:    call void @__omp_outlined__1(i32* [[DOTADDR1]], i32* [[DOTZERO_ADDR]]) #[[ATTR3]]
// CHECK1-NEXT:    ret void
//
//
// CHECK1-LABEL: define {{[^@]+}}@__omp_outlined__2
// CHECK1-SAME: (i32* noalias noundef [[DOTGLOBAL_TID_:%.*]], i32* noalias noundef [[DOTBOUND_TID_:%.*]]) #[[ATTR1]] {
// CHECK1-NEXT:  entry:
// CHECK1-NEXT:    [[DOTGLOBAL_TID__ADDR:%.*]] = alloca i32*, align 8
// CHECK1-NEXT:    [[DOTBOUND_TID__ADDR:%.*]] = alloca i32*, align 8
// CHECK1-NEXT:    [[A:%.*]] = alloca i32, align 4
// CHECK1-NEXT:    store i32* [[DOTGLOBAL_TID_]], i32** [[DOTGLOBAL_TID__ADDR]], align 8
// CHECK1-NEXT:    store i32* [[DOTBOUND_TID_]], i32** [[DOTBOUND_TID__ADDR]], align 8
// CHECK1-NEXT:    store i32 44, i32* [[A]], align 4
// CHECK1-NEXT:    ret void
//
//
// CHECK1-LABEL: define {{[^@]+}}@__omp_outlined__2_wrapper
// CHECK1-SAME: (i16 noundef zeroext [[TMP0:%.*]], i32 noundef [[TMP1:%.*]]) #[[ATTR2]] {
// CHECK1-NEXT:  entry:
// CHECK1-NEXT:    [[DOTADDR:%.*]] = alloca i16, align 2
// CHECK1-NEXT:    [[DOTADDR1:%.*]] = alloca i32, align 4
// CHECK1-NEXT:    [[DOTZERO_ADDR:%.*]] = alloca i32, align 4
// CHECK1-NEXT:    [[GLOBAL_ARGS:%.*]] = alloca i8**, align 8
// CHECK1-NEXT:    store i16 [[TMP0]], i16* [[DOTADDR]], align 2
// CHECK1-NEXT:    store i32 [[TMP1]], i32* [[DOTADDR1]], align 4
// CHECK1-NEXT:    store i32 0, i32* [[DOTZERO_ADDR]], align 4
// CHECK1-NEXT:    call void @__kmpc_get_shared_variables(i8*** [[GLOBAL_ARGS]])
// CHECK1-NEXT:    call void @__omp_outlined__2(i32* [[DOTADDR1]], i32* [[DOTZERO_ADDR]]) #[[ATTR3]]
// CHECK1-NEXT:    ret void
//
//
// CHECK1-LABEL: define {{[^@]+}}@{{__omp_offloading_[0-9a-z]+_[0-9a-z]+}}__Z9ftemplateIiET_i_l43
// CHECK1-SAME: (i64 noundef [[N:%.*]], i64 noundef [[A:%.*]], i64 noundef [[AA:%.*]], [10 x i32]* noundef nonnull align 4 dereferenceable(40) [[B:%.*]]) #[[ATTR0]] {
// CHECK1-NEXT:  entry:
// CHECK1-NEXT:    [[N_ADDR:%.*]] = alloca i64, align 8
// CHECK1-NEXT:    [[A_ADDR:%.*]] = alloca i64, align 8
// CHECK1-NEXT:    [[AA_ADDR:%.*]] = alloca i64, align 8
// CHECK1-NEXT:    [[B_ADDR:%.*]] = alloca [10 x i32]*, align 8
// CHECK1-NEXT:    [[CAPTURED_VARS_ADDRS:%.*]] = alloca [0 x i8*], align 8
// CHECK1-NEXT:    store i64 [[N]], i64* [[N_ADDR]], align 8
// CHECK1-NEXT:    store i64 [[A]], i64* [[A_ADDR]], align 8
// CHECK1-NEXT:    store i64 [[AA]], i64* [[AA_ADDR]], align 8
// CHECK1-NEXT:    store [10 x i32]* [[B]], [10 x i32]** [[B_ADDR]], align 8
// CHECK1-NEXT:    [[CONV:%.*]] = bitcast i64* [[N_ADDR]] to i32*
// CHECK1-NEXT:    [[CONV1:%.*]] = bitcast i64* [[A_ADDR]] to i32*
// CHECK1-NEXT:    [[CONV2:%.*]] = bitcast i64* [[AA_ADDR]] to i16*
// CHECK1-NEXT:    [[TMP0:%.*]] = load [10 x i32]*, [10 x i32]** [[B_ADDR]], align 8
// CHECK1-NEXT:    [[TMP1:%.*]] = call i32 @__kmpc_target_init(%struct.ident_t* @[[GLOB1]], i8 1, i1 true, i1 true)
// CHECK1-NEXT:    [[EXEC_USER_CODE:%.*]] = icmp eq i32 [[TMP1]], -1
// CHECK1-NEXT:    br i1 [[EXEC_USER_CODE]], label [[USER_CODE_ENTRY:%.*]], label [[WORKER_EXIT:%.*]]
// CHECK1:       user_code.entry:
// CHECK1-NEXT:    [[TMP2:%.*]] = call i32 @__kmpc_global_thread_num(%struct.ident_t* @[[GLOB1]])
// CHECK1-NEXT:    [[TMP3:%.*]] = load i32, i32* [[CONV]], align 4
// CHECK1-NEXT:    [[CMP:%.*]] = icmp sgt i32 [[TMP3]], 1000
// CHECK1-NEXT:    [[TMP4:%.*]] = zext i1 [[CMP]] to i32
// CHECK1-NEXT:    [[TMP5:%.*]] = bitcast [0 x i8*]* [[CAPTURED_VARS_ADDRS]] to i8**
// CHECK1-NEXT:    call void @__kmpc_parallel_51(%struct.ident_t* @[[GLOB1]], i32 [[TMP2]], i32 [[TMP4]], i32 -1, i32 -1, i8* bitcast (void (i32*, i32*)* @__omp_outlined__3 to i8*), i8* bitcast (void (i16, i32)* @__omp_outlined__3_wrapper to i8*), i8** [[TMP5]], i64 0)
// CHECK1-NEXT:    [[TMP6:%.*]] = load i32, i32* [[CONV1]], align 4
// CHECK1-NEXT:    [[ADD:%.*]] = add nsw i32 [[TMP6]], 1
// CHECK1-NEXT:    store i32 [[ADD]], i32* [[CONV1]], align 4
// CHECK1-NEXT:    [[TMP7:%.*]] = load i16, i16* [[CONV2]], align 2
// CHECK1-NEXT:    [[CONV3:%.*]] = sext i16 [[TMP7]] to i32
// CHECK1-NEXT:    [[ADD4:%.*]] = add nsw i32 [[CONV3]], 1
// CHECK1-NEXT:    [[CONV5:%.*]] = trunc i32 [[ADD4]] to i16
// CHECK1-NEXT:    store i16 [[CONV5]], i16* [[CONV2]], align 2
// CHECK1-NEXT:    [[ARRAYIDX:%.*]] = getelementptr inbounds [10 x i32], [10 x i32]* [[TMP0]], i64 0, i64 2
// CHECK1-NEXT:    [[TMP8:%.*]] = load i32, i32* [[ARRAYIDX]], align 4
// CHECK1-NEXT:    [[ADD6:%.*]] = add nsw i32 [[TMP8]], 1
// CHECK1-NEXT:    store i32 [[ADD6]], i32* [[ARRAYIDX]], align 4
// CHECK1-NEXT:    call void @__kmpc_target_deinit(%struct.ident_t* @[[GLOB1]], i8 1, i1 true)
// CHECK1-NEXT:    ret void
// CHECK1:       worker.exit:
// CHECK1-NEXT:    ret void
//
//
// CHECK1-LABEL: define {{[^@]+}}@__omp_outlined__3
// CHECK1-SAME: (i32* noalias noundef [[DOTGLOBAL_TID_:%.*]], i32* noalias noundef [[DOTBOUND_TID_:%.*]]) #[[ATTR1]] {
// CHECK1-NEXT:  entry:
// CHECK1-NEXT:    [[DOTGLOBAL_TID__ADDR:%.*]] = alloca i32*, align 8
// CHECK1-NEXT:    [[DOTBOUND_TID__ADDR:%.*]] = alloca i32*, align 8
// CHECK1-NEXT:    [[A:%.*]] = alloca i32, align 4
// CHECK1-NEXT:    store i32* [[DOTGLOBAL_TID_]], i32** [[DOTGLOBAL_TID__ADDR]], align 8
// CHECK1-NEXT:    store i32* [[DOTBOUND_TID_]], i32** [[DOTBOUND_TID__ADDR]], align 8
// CHECK1-NEXT:    store i32 45, i32* [[A]], align 4
// CHECK1-NEXT:    [[TMP0:%.*]] = load i32*, i32** [[DOTGLOBAL_TID__ADDR]], align 8
// CHECK1-NEXT:    [[TMP1:%.*]] = load i32, i32* [[TMP0]], align 4
// CHECK1-NEXT:    call void @__kmpc_barrier(%struct.ident_t* @[[GLOB2:[0-9]+]], i32 [[TMP1]])
// CHECK1-NEXT:    ret void
//
//
// CHECK1-LABEL: define {{[^@]+}}@__omp_outlined__3_wrapper
// CHECK1-SAME: (i16 noundef zeroext [[TMP0:%.*]], i32 noundef [[TMP1:%.*]]) #[[ATTR2]] {
// CHECK1-NEXT:  entry:
// CHECK1-NEXT:    [[DOTADDR:%.*]] = alloca i16, align 2
// CHECK1-NEXT:    [[DOTADDR1:%.*]] = alloca i32, align 4
// CHECK1-NEXT:    [[DOTZERO_ADDR:%.*]] = alloca i32, align 4
// CHECK1-NEXT:    [[GLOBAL_ARGS:%.*]] = alloca i8**, align 8
// CHECK1-NEXT:    store i16 [[TMP0]], i16* [[DOTADDR]], align 2
// CHECK1-NEXT:    store i32 [[TMP1]], i32* [[DOTADDR1]], align 4
// CHECK1-NEXT:    store i32 0, i32* [[DOTZERO_ADDR]], align 4
// CHECK1-NEXT:    call void @__kmpc_get_shared_variables(i8*** [[GLOBAL_ARGS]])
// CHECK1-NEXT:    call void @__omp_outlined__3(i32* [[DOTADDR1]], i32* [[DOTZERO_ADDR]]) #[[ATTR3]]
// CHECK1-NEXT:    ret void
//
//
// CHECK1-LABEL: define {{[^@]+}}@{{__omp_offloading_[0-9a-z]+_[0-9a-z]+}}__Z9ftemplateIiET_i_l55
// CHECK1-SAME: (i64 noundef [[A:%.*]]) #[[ATTR0]] {
// CHECK1-NEXT:  entry:
// CHECK1-NEXT:    [[A_ADDR:%.*]] = alloca i64, align 8
// CHECK1-NEXT:    [[CAPTURED_VARS_ADDRS:%.*]] = alloca [1 x i8*], align 8
// CHECK1-NEXT:    store i64 [[A]], i64* [[A_ADDR]], align 8
// CHECK1-NEXT:    [[CONV:%.*]] = bitcast i64* [[A_ADDR]] to i32*
// CHECK1-NEXT:    [[TMP0:%.*]] = call i32 @__kmpc_target_init(%struct.ident_t* @[[GLOB1]], i8 1, i1 true, i1 true)
// CHECK1-NEXT:    [[EXEC_USER_CODE:%.*]] = icmp eq i32 [[TMP0]], -1
// CHECK1-NEXT:    br i1 [[EXEC_USER_CODE]], label [[USER_CODE_ENTRY:%.*]], label [[WORKER_EXIT:%.*]]
// CHECK1:       user_code.entry:
// CHECK1-NEXT:    [[TMP1:%.*]] = load i32, i32* [[CONV]], align 4
// CHECK1-NEXT:    [[A1:%.*]] = call align 16 i8* @__kmpc_alloc_shared(i64 4)
// CHECK1-NEXT:    [[A_ON_STACK:%.*]] = bitcast i8* [[A1]] to i32*
// CHECK1-NEXT:    store i32 [[TMP1]], i32* [[A_ON_STACK]], align 4
// CHECK1-NEXT:    [[TMP2:%.*]] = call i32 @__kmpc_global_thread_num(%struct.ident_t* @[[GLOB1]])
// CHECK1-NEXT:    [[TMP3:%.*]] = getelementptr inbounds [1 x i8*], [1 x i8*]* [[CAPTURED_VARS_ADDRS]], i64 0, i64 0
// CHECK1-NEXT:    [[TMP4:%.*]] = bitcast i32* [[A_ON_STACK]] to i8*
// CHECK1-NEXT:    store i8* [[TMP4]], i8** [[TMP3]], align 8
// CHECK1-NEXT:    [[TMP5:%.*]] = bitcast [1 x i8*]* [[CAPTURED_VARS_ADDRS]] to i8**
// CHECK1-NEXT:    call void @__kmpc_parallel_51(%struct.ident_t* @[[GLOB1]], i32 [[TMP2]], i32 1, i32 -1, i32 -1, i8* bitcast (void (i32*, i32*, i32*)* @__omp_outlined__4 to i8*), i8* bitcast (void (i16, i32)* @__omp_outlined__4_wrapper to i8*), i8** [[TMP5]], i64 1)
// CHECK1-NEXT:    [[TMP6:%.*]] = load i32, i32* [[A_ON_STACK]], align 4
// CHECK1-NEXT:    [[INC:%.*]] = add nsw i32 [[TMP6]], 1
// CHECK1-NEXT:    store i32 [[INC]], i32* [[A_ON_STACK]], align 4
// CHECK1-NEXT:    call void @__kmpc_free_shared(i8* [[A1]], i64 4)
// CHECK1-NEXT:    call void @__kmpc_target_deinit(%struct.ident_t* @[[GLOB1]], i8 1, i1 true)
// CHECK1-NEXT:    ret void
// CHECK1:       worker.exit:
// CHECK1-NEXT:    ret void
//
//
// CHECK1-LABEL: define {{[^@]+}}@__omp_outlined__4
// CHECK1-SAME: (i32* noalias noundef [[DOTGLOBAL_TID_:%.*]], i32* noalias noundef [[DOTBOUND_TID_:%.*]], i32* noundef nonnull align 4 dereferenceable(4) [[A:%.*]]) #[[ATTR1]] {
// CHECK1-NEXT:  entry:
// CHECK1-NEXT:    [[DOTGLOBAL_TID__ADDR:%.*]] = alloca i32*, align 8
// CHECK1-NEXT:    [[DOTBOUND_TID__ADDR:%.*]] = alloca i32*, align 8
// CHECK1-NEXT:    [[A_ADDR:%.*]] = alloca i32*, align 8
// CHECK1-NEXT:    [[CRITICAL_COUNTER:%.*]] = alloca i32, align 4
// CHECK1-NEXT:    store i32* [[DOTGLOBAL_TID_]], i32** [[DOTGLOBAL_TID__ADDR]], align 8
// CHECK1-NEXT:    store i32* [[DOTBOUND_TID_]], i32** [[DOTBOUND_TID__ADDR]], align 8
// CHECK1-NEXT:    store i32* [[A]], i32** [[A_ADDR]], align 8
// CHECK1-NEXT:    [[TMP0:%.*]] = load i32*, i32** [[A_ADDR]], align 8
// CHECK1-NEXT:    [[TMP1:%.*]] = call i64 @__kmpc_warp_active_thread_mask()
// CHECK1-NEXT:    [[TMP2:%.*]] = call i32 @__kmpc_get_hardware_thread_id_in_block()
// CHECK1-NEXT:    [[NVPTX_NUM_THREADS:%.*]] = call i32 @__kmpc_get_hardware_num_threads_in_block()
// CHECK1-NEXT:    store i32 0, i32* [[CRITICAL_COUNTER]], align 4
// CHECK1-NEXT:    br label [[OMP_CRITICAL_LOOP:%.*]]
// CHECK1:       omp.critical.loop:
// CHECK1-NEXT:    [[TMP3:%.*]] = load i32, i32* [[CRITICAL_COUNTER]], align 4
// CHECK1-NEXT:    [[TMP4:%.*]] = icmp slt i32 [[TMP3]], [[NVPTX_NUM_THREADS]]
// CHECK1-NEXT:    br i1 [[TMP4]], label [[OMP_CRITICAL_TEST:%.*]], label [[OMP_CRITICAL_EXIT:%.*]]
// CHECK1:       omp.critical.test:
// CHECK1-NEXT:    [[TMP5:%.*]] = load i32, i32* [[CRITICAL_COUNTER]], align 4
// CHECK1-NEXT:    [[TMP6:%.*]] = icmp eq i32 [[TMP2]], [[TMP5]]
// CHECK1-NEXT:    br i1 [[TMP6]], label [[OMP_CRITICAL_BODY:%.*]], label [[OMP_CRITICAL_SYNC:%.*]]
// CHECK1:       omp.critical.body:
// CHECK1-NEXT:    [[TMP7:%.*]] = load i32*, i32** [[DOTGLOBAL_TID__ADDR]], align 8
// CHECK1-NEXT:    [[TMP8:%.*]] = load i32, i32* [[TMP7]], align 4
// CHECK1-NEXT:    call void @__kmpc_critical(%struct.ident_t* @[[GLOB1]], i32 [[TMP8]], [8 x i32]* @"_gomp_critical_user_$var")
// CHECK1-NEXT:    [[TMP9:%.*]] = load i32, i32* [[TMP0]], align 4
// CHECK1-NEXT:    [[INC:%.*]] = add nsw i32 [[TMP9]], 1
// CHECK1-NEXT:    store i32 [[INC]], i32* [[TMP0]], align 4
// CHECK1-NEXT:    call void @__kmpc_end_critical(%struct.ident_t* @[[GLOB1]], i32 [[TMP8]], [8 x i32]* @"_gomp_critical_user_$var")
// CHECK1-NEXT:    br label [[OMP_CRITICAL_SYNC]]
// CHECK1:       omp.critical.sync:
// CHECK1-NEXT:    call void @__kmpc_syncwarp(i64 [[TMP1]])
// CHECK1-NEXT:    [[TMP10:%.*]] = add nsw i32 [[TMP5]], 1
// CHECK1-NEXT:    store i32 [[TMP10]], i32* [[CRITICAL_COUNTER]], align 4
// CHECK1-NEXT:    br label [[OMP_CRITICAL_LOOP]]
// CHECK1:       omp.critical.exit:
// CHECK1-NEXT:    ret void
//
//
// CHECK1-LABEL: define {{[^@]+}}@__omp_outlined__4_wrapper
// CHECK1-SAME: (i16 noundef zeroext [[TMP0:%.*]], i32 noundef [[TMP1:%.*]]) #[[ATTR2]] {
// CHECK1-NEXT:  entry:
// CHECK1-NEXT:    [[DOTADDR:%.*]] = alloca i16, align 2
// CHECK1-NEXT:    [[DOTADDR1:%.*]] = alloca i32, align 4
// CHECK1-NEXT:    [[DOTZERO_ADDR:%.*]] = alloca i32, align 4
// CHECK1-NEXT:    [[GLOBAL_ARGS:%.*]] = alloca i8**, align 8
// CHECK1-NEXT:    store i16 [[TMP0]], i16* [[DOTADDR]], align 2
// CHECK1-NEXT:    store i32 [[TMP1]], i32* [[DOTADDR1]], align 4
// CHECK1-NEXT:    store i32 0, i32* [[DOTZERO_ADDR]], align 4
// CHECK1-NEXT:    call void @__kmpc_get_shared_variables(i8*** [[GLOBAL_ARGS]])
// CHECK1-NEXT:    [[TMP2:%.*]] = load i8**, i8*** [[GLOBAL_ARGS]], align 8
// CHECK1-NEXT:    [[TMP3:%.*]] = getelementptr inbounds i8*, i8** [[TMP2]], i64 0
// CHECK1-NEXT:    [[TMP4:%.*]] = bitcast i8** [[TMP3]] to i32**
// CHECK1-NEXT:    [[TMP5:%.*]] = load i32*, i32** [[TMP4]], align 8
// CHECK1-NEXT:    call void @__omp_outlined__4(i32* [[DOTADDR1]], i32* [[DOTZERO_ADDR]], i32* [[TMP5]]) #[[ATTR3]]
// CHECK1-NEXT:    ret void
//
//
// CHECK2-LABEL: define {{[^@]+}}@{{__omp_offloading_[0-9a-z]+_[0-9a-z]+}}__Z9ftemplateIiET_i_l26
// CHECK2-SAME: (i32 noundef [[A:%.*]]) #[[ATTR0:[0-9]+]] {
// CHECK2-NEXT:  entry:
// CHECK2-NEXT:    [[A_ADDR:%.*]] = alloca i32, align 4
// CHECK2-NEXT:    [[CAPTURED_VARS_ADDRS:%.*]] = alloca [0 x i8*], align 4
// CHECK2-NEXT:    [[CAPTURED_VARS_ADDRS1:%.*]] = alloca [0 x i8*], align 4
// CHECK2-NEXT:    [[CAPTURED_VARS_ADDRS2:%.*]] = alloca [0 x i8*], align 4
// CHECK2-NEXT:    store i32 [[A]], i32* [[A_ADDR]], align 4
// CHECK2-NEXT:    [[TMP0:%.*]] = call i32 @__kmpc_target_init(%struct.ident_t* @[[GLOB1:[0-9]+]], i8 1, i1 true, i1 true)
// CHECK2-NEXT:    [[EXEC_USER_CODE:%.*]] = icmp eq i32 [[TMP0]], -1
// CHECK2-NEXT:    br i1 [[EXEC_USER_CODE]], label [[USER_CODE_ENTRY:%.*]], label [[WORKER_EXIT:%.*]]
// CHECK2:       user_code.entry:
// CHECK2-NEXT:    [[TMP1:%.*]] = call i32 @__kmpc_global_thread_num(%struct.ident_t* @[[GLOB1]])
// CHECK2-NEXT:    [[TMP2:%.*]] = bitcast [0 x i8*]* [[CAPTURED_VARS_ADDRS]] to i8**
// CHECK2-NEXT:    call void @__kmpc_parallel_51(%struct.ident_t* @[[GLOB1]], i32 [[TMP1]], i32 1, i32 -1, i32 -1, i8* bitcast (void (i32*, i32*)* @__omp_outlined__ to i8*), i8* bitcast (void (i16, i32)* @__omp_outlined___wrapper to i8*), i8** [[TMP2]], i32 0)
// CHECK2-NEXT:    [[TMP3:%.*]] = bitcast [0 x i8*]* [[CAPTURED_VARS_ADDRS1]] to i8**
// CHECK2-NEXT:    call void @__kmpc_parallel_51(%struct.ident_t* @[[GLOB1]], i32 [[TMP1]], i32 0, i32 -1, i32 -1, i8* bitcast (void (i32*, i32*)* @__omp_outlined__1 to i8*), i8* bitcast (void (i16, i32)* @__omp_outlined__1_wrapper to i8*), i8** [[TMP3]], i32 0)
// CHECK2-NEXT:    [[TMP4:%.*]] = bitcast [0 x i8*]* [[CAPTURED_VARS_ADDRS2]] to i8**
// CHECK2-NEXT:    call void @__kmpc_parallel_51(%struct.ident_t* @[[GLOB1]], i32 [[TMP1]], i32 1, i32 -1, i32 -1, i8* bitcast (void (i32*, i32*)* @__omp_outlined__2 to i8*), i8* bitcast (void (i16, i32)* @__omp_outlined__2_wrapper to i8*), i8** [[TMP4]], i32 0)
// CHECK2-NEXT:    [[TMP5:%.*]] = load i32, i32* [[A_ADDR]], align 4
// CHECK2-NEXT:    [[ADD:%.*]] = add nsw i32 [[TMP5]], 1
// CHECK2-NEXT:    store i32 [[ADD]], i32* [[A_ADDR]], align 4
// CHECK2-NEXT:    call void @__kmpc_target_deinit(%struct.ident_t* @[[GLOB1]], i8 1, i1 true)
// CHECK2-NEXT:    ret void
// CHECK2:       worker.exit:
// CHECK2-NEXT:    ret void
//
//
// CHECK2-LABEL: define {{[^@]+}}@__omp_outlined__
// CHECK2-SAME: (i32* noalias noundef [[DOTGLOBAL_TID_:%.*]], i32* noalias noundef [[DOTBOUND_TID_:%.*]]) #[[ATTR1:[0-9]+]] {
// CHECK2-NEXT:  entry:
// CHECK2-NEXT:    [[DOTGLOBAL_TID__ADDR:%.*]] = alloca i32*, align 4
// CHECK2-NEXT:    [[DOTBOUND_TID__ADDR:%.*]] = alloca i32*, align 4
// CHECK2-NEXT:    [[A:%.*]] = alloca i32, align 4
// CHECK2-NEXT:    store i32* [[DOTGLOBAL_TID_]], i32** [[DOTGLOBAL_TID__ADDR]], align 4
// CHECK2-NEXT:    store i32* [[DOTBOUND_TID_]], i32** [[DOTBOUND_TID__ADDR]], align 4
// CHECK2-NEXT:    store i32 42, i32* [[A]], align 4
// CHECK2-NEXT:    ret void
//
//
// CHECK2-LABEL: define {{[^@]+}}@__omp_outlined___wrapper
// CHECK2-SAME: (i16 noundef zeroext [[TMP0:%.*]], i32 noundef [[TMP1:%.*]]) #[[ATTR1]] {
// CHECK2-NEXT:  entry:
// CHECK2-NEXT:    [[DOTADDR:%.*]] = alloca i16, align 2
// CHECK2-NEXT:    [[DOTADDR1:%.*]] = alloca i32, align 4
// CHECK2-NEXT:    [[DOTZERO_ADDR:%.*]] = alloca i32, align 4
// CHECK2-NEXT:    [[GLOBAL_ARGS:%.*]] = alloca i8**, align 4
// CHECK2-NEXT:    store i16 [[TMP0]], i16* [[DOTADDR]], align 2
// CHECK2-NEXT:    store i32 [[TMP1]], i32* [[DOTADDR1]], align 4
// CHECK2-NEXT:    store i32 0, i32* [[DOTZERO_ADDR]], align 4
// CHECK2-NEXT:    call void @__kmpc_get_shared_variables(i8*** [[GLOBAL_ARGS]])
// CHECK2-NEXT:    call void @__omp_outlined__(i32* [[DOTADDR1]], i32* [[DOTZERO_ADDR]]) #[[ATTR2:[0-9]+]]
// CHECK2-NEXT:    ret void
//
//
// CHECK2-LABEL: define {{[^@]+}}@__omp_outlined__1
// CHECK2-SAME: (i32* noalias noundef [[DOTGLOBAL_TID_:%.*]], i32* noalias noundef [[DOTBOUND_TID_:%.*]]) #[[ATTR1]] {
// CHECK2-NEXT:  entry:
// CHECK2-NEXT:    [[DOTGLOBAL_TID__ADDR:%.*]] = alloca i32*, align 4
// CHECK2-NEXT:    [[DOTBOUND_TID__ADDR:%.*]] = alloca i32*, align 4
// CHECK2-NEXT:    [[A:%.*]] = alloca i32, align 4
// CHECK2-NEXT:    store i32* [[DOTGLOBAL_TID_]], i32** [[DOTGLOBAL_TID__ADDR]], align 4
// CHECK2-NEXT:    store i32* [[DOTBOUND_TID_]], i32** [[DOTBOUND_TID__ADDR]], align 4
// CHECK2-NEXT:    store i32 43, i32* [[A]], align 4
// CHECK2-NEXT:    ret void
//
//
// CHECK2-LABEL: define {{[^@]+}}@__omp_outlined__1_wrapper
// CHECK2-SAME: (i16 noundef zeroext [[TMP0:%.*]], i32 noundef [[TMP1:%.*]]) #[[ATTR1]] {
// CHECK2-NEXT:  entry:
// CHECK2-NEXT:    [[DOTADDR:%.*]] = alloca i16, align 2
// CHECK2-NEXT:    [[DOTADDR1:%.*]] = alloca i32, align 4
// CHECK2-NEXT:    [[DOTZERO_ADDR:%.*]] = alloca i32, align 4
// CHECK2-NEXT:    [[GLOBAL_ARGS:%.*]] = alloca i8**, align 4
// CHECK2-NEXT:    store i16 [[TMP0]], i16* [[DOTADDR]], align 2
// CHECK2-NEXT:    store i32 [[TMP1]], i32* [[DOTADDR1]], align 4
// CHECK2-NEXT:    store i32 0, i32* [[DOTZERO_ADDR]], align 4
// CHECK2-NEXT:    call void @__kmpc_get_shared_variables(i8*** [[GLOBAL_ARGS]])
// CHECK2-NEXT:    call void @__omp_outlined__1(i32* [[DOTADDR1]], i32* [[DOTZERO_ADDR]]) #[[ATTR2]]
// CHECK2-NEXT:    ret void
//
//
// CHECK2-LABEL: define {{[^@]+}}@__omp_outlined__2
// CHECK2-SAME: (i32* noalias noundef [[DOTGLOBAL_TID_:%.*]], i32* noalias noundef [[DOTBOUND_TID_:%.*]]) #[[ATTR1]] {
// CHECK2-NEXT:  entry:
// CHECK2-NEXT:    [[DOTGLOBAL_TID__ADDR:%.*]] = alloca i32*, align 4
// CHECK2-NEXT:    [[DOTBOUND_TID__ADDR:%.*]] = alloca i32*, align 4
// CHECK2-NEXT:    [[A:%.*]] = alloca i32, align 4
// CHECK2-NEXT:    store i32* [[DOTGLOBAL_TID_]], i32** [[DOTGLOBAL_TID__ADDR]], align 4
// CHECK2-NEXT:    store i32* [[DOTBOUND_TID_]], i32** [[DOTBOUND_TID__ADDR]], align 4
// CHECK2-NEXT:    store i32 44, i32* [[A]], align 4
// CHECK2-NEXT:    ret void
//
//
// CHECK2-LABEL: define {{[^@]+}}@__omp_outlined__2_wrapper
// CHECK2-SAME: (i16 noundef zeroext [[TMP0:%.*]], i32 noundef [[TMP1:%.*]]) #[[ATTR1]] {
// CHECK2-NEXT:  entry:
// CHECK2-NEXT:    [[DOTADDR:%.*]] = alloca i16, align 2
// CHECK2-NEXT:    [[DOTADDR1:%.*]] = alloca i32, align 4
// CHECK2-NEXT:    [[DOTZERO_ADDR:%.*]] = alloca i32, align 4
// CHECK2-NEXT:    [[GLOBAL_ARGS:%.*]] = alloca i8**, align 4
// CHECK2-NEXT:    store i16 [[TMP0]], i16* [[DOTADDR]], align 2
// CHECK2-NEXT:    store i32 [[TMP1]], i32* [[DOTADDR1]], align 4
// CHECK2-NEXT:    store i32 0, i32* [[DOTZERO_ADDR]], align 4
// CHECK2-NEXT:    call void @__kmpc_get_shared_variables(i8*** [[GLOBAL_ARGS]])
// CHECK2-NEXT:    call void @__omp_outlined__2(i32* [[DOTADDR1]], i32* [[DOTZERO_ADDR]]) #[[ATTR2]]
// CHECK2-NEXT:    ret void
//
//
// CHECK2-LABEL: define {{[^@]+}}@{{__omp_offloading_[0-9a-z]+_[0-9a-z]+}}__Z9ftemplateIiET_i_l43
// CHECK2-SAME: (i32 noundef [[N:%.*]], i32 noundef [[A:%.*]], i32 noundef [[AA:%.*]], [10 x i32]* noundef nonnull align 4 dereferenceable(40) [[B:%.*]]) #[[ATTR0]] {
// CHECK2-NEXT:  entry:
// CHECK2-NEXT:    [[N_ADDR:%.*]] = alloca i32, align 4
// CHECK2-NEXT:    [[A_ADDR:%.*]] = alloca i32, align 4
// CHECK2-NEXT:    [[AA_ADDR:%.*]] = alloca i32, align 4
// CHECK2-NEXT:    [[B_ADDR:%.*]] = alloca [10 x i32]*, align 4
// CHECK2-NEXT:    [[CAPTURED_VARS_ADDRS:%.*]] = alloca [0 x i8*], align 4
// CHECK2-NEXT:    store i32 [[N]], i32* [[N_ADDR]], align 4
// CHECK2-NEXT:    store i32 [[A]], i32* [[A_ADDR]], align 4
// CHECK2-NEXT:    store i32 [[AA]], i32* [[AA_ADDR]], align 4
// CHECK2-NEXT:    store [10 x i32]* [[B]], [10 x i32]** [[B_ADDR]], align 4
// CHECK2-NEXT:    [[CONV:%.*]] = bitcast i32* [[AA_ADDR]] to i16*
// CHECK2-NEXT:    [[TMP0:%.*]] = load [10 x i32]*, [10 x i32]** [[B_ADDR]], align 4
// CHECK2-NEXT:    [[TMP1:%.*]] = call i32 @__kmpc_target_init(%struct.ident_t* @[[GLOB1]], i8 1, i1 true, i1 true)
// CHECK2-NEXT:    [[EXEC_USER_CODE:%.*]] = icmp eq i32 [[TMP1]], -1
// CHECK2-NEXT:    br i1 [[EXEC_USER_CODE]], label [[USER_CODE_ENTRY:%.*]], label [[WORKER_EXIT:%.*]]
// CHECK2:       user_code.entry:
// CHECK2-NEXT:    [[TMP2:%.*]] = call i32 @__kmpc_global_thread_num(%struct.ident_t* @[[GLOB1]])
// CHECK2-NEXT:    [[TMP3:%.*]] = load i32, i32* [[N_ADDR]], align 4
// CHECK2-NEXT:    [[CMP:%.*]] = icmp sgt i32 [[TMP3]], 1000
// CHECK2-NEXT:    [[TMP4:%.*]] = zext i1 [[CMP]] to i32
// CHECK2-NEXT:    [[TMP5:%.*]] = bitcast [0 x i8*]* [[CAPTURED_VARS_ADDRS]] to i8**
// CHECK2-NEXT:    call void @__kmpc_parallel_51(%struct.ident_t* @[[GLOB1]], i32 [[TMP2]], i32 [[TMP4]], i32 -1, i32 -1, i8* bitcast (void (i32*, i32*)* @__omp_outlined__3 to i8*), i8* bitcast (void (i16, i32)* @__omp_outlined__3_wrapper to i8*), i8** [[TMP5]], i32 0)
// CHECK2-NEXT:    [[TMP6:%.*]] = load i32, i32* [[A_ADDR]], align 4
// CHECK2-NEXT:    [[ADD:%.*]] = add nsw i32 [[TMP6]], 1
// CHECK2-NEXT:    store i32 [[ADD]], i32* [[A_ADDR]], align 4
// CHECK2-NEXT:    [[TMP7:%.*]] = load i16, i16* [[CONV]], align 2
// CHECK2-NEXT:    [[CONV1:%.*]] = sext i16 [[TMP7]] to i32
// CHECK2-NEXT:    [[ADD2:%.*]] = add nsw i32 [[CONV1]], 1
// CHECK2-NEXT:    [[CONV3:%.*]] = trunc i32 [[ADD2]] to i16
// CHECK2-NEXT:    store i16 [[CONV3]], i16* [[CONV]], align 2
// CHECK2-NEXT:    [[ARRAYIDX:%.*]] = getelementptr inbounds [10 x i32], [10 x i32]* [[TMP0]], i32 0, i32 2
// CHECK2-NEXT:    [[TMP8:%.*]] = load i32, i32* [[ARRAYIDX]], align 4
// CHECK2-NEXT:    [[ADD4:%.*]] = add nsw i32 [[TMP8]], 1
// CHECK2-NEXT:    store i32 [[ADD4]], i32* [[ARRAYIDX]], align 4
// CHECK2-NEXT:    call void @__kmpc_target_deinit(%struct.ident_t* @[[GLOB1]], i8 1, i1 true)
// CHECK2-NEXT:    ret void
// CHECK2:       worker.exit:
// CHECK2-NEXT:    ret void
//
//
// CHECK2-LABEL: define {{[^@]+}}@__omp_outlined__3
// CHECK2-SAME: (i32* noalias noundef [[DOTGLOBAL_TID_:%.*]], i32* noalias noundef [[DOTBOUND_TID_:%.*]]) #[[ATTR1]] {
// CHECK2-NEXT:  entry:
// CHECK2-NEXT:    [[DOTGLOBAL_TID__ADDR:%.*]] = alloca i32*, align 4
// CHECK2-NEXT:    [[DOTBOUND_TID__ADDR:%.*]] = alloca i32*, align 4
// CHECK2-NEXT:    [[A:%.*]] = alloca i32, align 4
// CHECK2-NEXT:    store i32* [[DOTGLOBAL_TID_]], i32** [[DOTGLOBAL_TID__ADDR]], align 4
// CHECK2-NEXT:    store i32* [[DOTBOUND_TID_]], i32** [[DOTBOUND_TID__ADDR]], align 4
// CHECK2-NEXT:    store i32 45, i32* [[A]], align 4
// CHECK2-NEXT:    [[TMP0:%.*]] = load i32*, i32** [[DOTGLOBAL_TID__ADDR]], align 4
// CHECK2-NEXT:    [[TMP1:%.*]] = load i32, i32* [[TMP0]], align 4
// CHECK2-NEXT:    call void @__kmpc_barrier(%struct.ident_t* @[[GLOB2:[0-9]+]], i32 [[TMP1]])
// CHECK2-NEXT:    ret void
//
//
// CHECK2-LABEL: define {{[^@]+}}@__omp_outlined__3_wrapper
// CHECK2-SAME: (i16 noundef zeroext [[TMP0:%.*]], i32 noundef [[TMP1:%.*]]) #[[ATTR1]] {
// CHECK2-NEXT:  entry:
// CHECK2-NEXT:    [[DOTADDR:%.*]] = alloca i16, align 2
// CHECK2-NEXT:    [[DOTADDR1:%.*]] = alloca i32, align 4
// CHECK2-NEXT:    [[DOTZERO_ADDR:%.*]] = alloca i32, align 4
// CHECK2-NEXT:    [[GLOBAL_ARGS:%.*]] = alloca i8**, align 4
// CHECK2-NEXT:    store i16 [[TMP0]], i16* [[DOTADDR]], align 2
// CHECK2-NEXT:    store i32 [[TMP1]], i32* [[DOTADDR1]], align 4
// CHECK2-NEXT:    store i32 0, i32* [[DOTZERO_ADDR]], align 4
// CHECK2-NEXT:    call void @__kmpc_get_shared_variables(i8*** [[GLOBAL_ARGS]])
// CHECK2-NEXT:    call void @__omp_outlined__3(i32* [[DOTADDR1]], i32* [[DOTZERO_ADDR]]) #[[ATTR2]]
// CHECK2-NEXT:    ret void
//
//
// CHECK2-LABEL: define {{[^@]+}}@{{__omp_offloading_[0-9a-z]+_[0-9a-z]+}}__Z9ftemplateIiET_i_l55
// CHECK2-SAME: (i32 noundef [[A:%.*]]) #[[ATTR0]] {
// CHECK2-NEXT:  entry:
// CHECK2-NEXT:    [[A_ADDR:%.*]] = alloca i32, align 4
// CHECK2-NEXT:    [[CAPTURED_VARS_ADDRS:%.*]] = alloca [1 x i8*], align 4
// CHECK2-NEXT:    store i32 [[A]], i32* [[A_ADDR]], align 4
// CHECK2-NEXT:    [[TMP0:%.*]] = call i32 @__kmpc_target_init(%struct.ident_t* @[[GLOB1]], i8 1, i1 true, i1 true)
// CHECK2-NEXT:    [[EXEC_USER_CODE:%.*]] = icmp eq i32 [[TMP0]], -1
// CHECK2-NEXT:    br i1 [[EXEC_USER_CODE]], label [[USER_CODE_ENTRY:%.*]], label [[WORKER_EXIT:%.*]]
// CHECK2:       user_code.entry:
// CHECK2-NEXT:    [[TMP1:%.*]] = load i32, i32* [[A_ADDR]], align 4
// CHECK2-NEXT:    [[A1:%.*]] = call align 4 i8* @__kmpc_alloc_shared(i32 4)
// CHECK2-NEXT:    [[A_ON_STACK:%.*]] = bitcast i8* [[A1]] to i32*
// CHECK2-NEXT:    store i32 [[TMP1]], i32* [[A_ON_STACK]], align 4
// CHECK2-NEXT:    [[TMP2:%.*]] = call i32 @__kmpc_global_thread_num(%struct.ident_t* @[[GLOB1]])
// CHECK2-NEXT:    [[TMP3:%.*]] = getelementptr inbounds [1 x i8*], [1 x i8*]* [[CAPTURED_VARS_ADDRS]], i32 0, i32 0
// CHECK2-NEXT:    [[TMP4:%.*]] = bitcast i32* [[A_ON_STACK]] to i8*
// CHECK2-NEXT:    store i8* [[TMP4]], i8** [[TMP3]], align 4
// CHECK2-NEXT:    [[TMP5:%.*]] = bitcast [1 x i8*]* [[CAPTURED_VARS_ADDRS]] to i8**
// CHECK2-NEXT:    call void @__kmpc_parallel_51(%struct.ident_t* @[[GLOB1]], i32 [[TMP2]], i32 1, i32 -1, i32 -1, i8* bitcast (void (i32*, i32*, i32*)* @__omp_outlined__4 to i8*), i8* bitcast (void (i16, i32)* @__omp_outlined__4_wrapper to i8*), i8** [[TMP5]], i32 1)
// CHECK2-NEXT:    [[TMP6:%.*]] = load i32, i32* [[A_ON_STACK]], align 4
// CHECK2-NEXT:    [[INC:%.*]] = add nsw i32 [[TMP6]], 1
// CHECK2-NEXT:    store i32 [[INC]], i32* [[A_ON_STACK]], align 4
// CHECK2-NEXT:    call void @__kmpc_free_shared(i8* [[A1]], i32 4)
// CHECK2-NEXT:    call void @__kmpc_target_deinit(%struct.ident_t* @[[GLOB1]], i8 1, i1 true)
// CHECK2-NEXT:    ret void
// CHECK2:       worker.exit:
// CHECK2-NEXT:    ret void
//
//
// CHECK2-LABEL: define {{[^@]+}}@__omp_outlined__4
// CHECK2-SAME: (i32* noalias noundef [[DOTGLOBAL_TID_:%.*]], i32* noalias noundef [[DOTBOUND_TID_:%.*]], i32* noundef nonnull align 4 dereferenceable(4) [[A:%.*]]) #[[ATTR1]] {
// CHECK2-NEXT:  entry:
// CHECK2-NEXT:    [[DOTGLOBAL_TID__ADDR:%.*]] = alloca i32*, align 4
// CHECK2-NEXT:    [[DOTBOUND_TID__ADDR:%.*]] = alloca i32*, align 4
// CHECK2-NEXT:    [[A_ADDR:%.*]] = alloca i32*, align 4
// CHECK2-NEXT:    [[CRITICAL_COUNTER:%.*]] = alloca i32, align 4
// CHECK2-NEXT:    store i32* [[DOTGLOBAL_TID_]], i32** [[DOTGLOBAL_TID__ADDR]], align 4
// CHECK2-NEXT:    store i32* [[DOTBOUND_TID_]], i32** [[DOTBOUND_TID__ADDR]], align 4
// CHECK2-NEXT:    store i32* [[A]], i32** [[A_ADDR]], align 4
// CHECK2-NEXT:    [[TMP0:%.*]] = load i32*, i32** [[A_ADDR]], align 4
// CHECK2-NEXT:    [[TMP1:%.*]] = call i64 @__kmpc_warp_active_thread_mask()
// CHECK2-NEXT:    [[TMP2:%.*]] = call i32 @__kmpc_get_hardware_thread_id_in_block()
// CHECK2-NEXT:    [[NVPTX_NUM_THREADS:%.*]] = call i32 @__kmpc_get_hardware_num_threads_in_block()
// CHECK2-NEXT:    store i32 0, i32* [[CRITICAL_COUNTER]], align 4
// CHECK2-NEXT:    br label [[OMP_CRITICAL_LOOP:%.*]]
// CHECK2:       omp.critical.loop:
// CHECK2-NEXT:    [[TMP3:%.*]] = load i32, i32* [[CRITICAL_COUNTER]], align 4
// CHECK2-NEXT:    [[TMP4:%.*]] = icmp slt i32 [[TMP3]], [[NVPTX_NUM_THREADS]]
// CHECK2-NEXT:    br i1 [[TMP4]], label [[OMP_CRITICAL_TEST:%.*]], label [[OMP_CRITICAL_EXIT:%.*]]
// CHECK2:       omp.critical.test:
// CHECK2-NEXT:    [[TMP5:%.*]] = load i32, i32* [[CRITICAL_COUNTER]], align 4
// CHECK2-NEXT:    [[TMP6:%.*]] = icmp eq i32 [[TMP2]], [[TMP5]]
// CHECK2-NEXT:    br i1 [[TMP6]], label [[OMP_CRITICAL_BODY:%.*]], label [[OMP_CRITICAL_SYNC:%.*]]
// CHECK2:       omp.critical.body:
// CHECK2-NEXT:    [[TMP7:%.*]] = load i32*, i32** [[DOTGLOBAL_TID__ADDR]], align 4
// CHECK2-NEXT:    [[TMP8:%.*]] = load i32, i32* [[TMP7]], align 4
// CHECK2-NEXT:    call void @__kmpc_critical(%struct.ident_t* @[[GLOB1]], i32 [[TMP8]], [8 x i32]* @"_gomp_critical_user_$var")
// CHECK2-NEXT:    [[TMP9:%.*]] = load i32, i32* [[TMP0]], align 4
// CHECK2-NEXT:    [[INC:%.*]] = add nsw i32 [[TMP9]], 1
// CHECK2-NEXT:    store i32 [[INC]], i32* [[TMP0]], align 4
// CHECK2-NEXT:    call void @__kmpc_end_critical(%struct.ident_t* @[[GLOB1]], i32 [[TMP8]], [8 x i32]* @"_gomp_critical_user_$var")
// CHECK2-NEXT:    br label [[OMP_CRITICAL_SYNC]]
// CHECK2:       omp.critical.sync:
// CHECK2-NEXT:    call void @__kmpc_syncwarp(i64 [[TMP1]])
// CHECK2-NEXT:    [[TMP10:%.*]] = add nsw i32 [[TMP5]], 1
// CHECK2-NEXT:    store i32 [[TMP10]], i32* [[CRITICAL_COUNTER]], align 4
// CHECK2-NEXT:    br label [[OMP_CRITICAL_LOOP]]
// CHECK2:       omp.critical.exit:
// CHECK2-NEXT:    ret void
//
//
// CHECK2-LABEL: define {{[^@]+}}@__omp_outlined__4_wrapper
// CHECK2-SAME: (i16 noundef zeroext [[TMP0:%.*]], i32 noundef [[TMP1:%.*]]) #[[ATTR1]] {
// CHECK2-NEXT:  entry:
// CHECK2-NEXT:    [[DOTADDR:%.*]] = alloca i16, align 2
// CHECK2-NEXT:    [[DOTADDR1:%.*]] = alloca i32, align 4
// CHECK2-NEXT:    [[DOTZERO_ADDR:%.*]] = alloca i32, align 4
// CHECK2-NEXT:    [[GLOBAL_ARGS:%.*]] = alloca i8**, align 4
// CHECK2-NEXT:    store i16 [[TMP0]], i16* [[DOTADDR]], align 2
// CHECK2-NEXT:    store i32 [[TMP1]], i32* [[DOTADDR1]], align 4
// CHECK2-NEXT:    store i32 0, i32* [[DOTZERO_ADDR]], align 4
// CHECK2-NEXT:    call void @__kmpc_get_shared_variables(i8*** [[GLOBAL_ARGS]])
// CHECK2-NEXT:    [[TMP2:%.*]] = load i8**, i8*** [[GLOBAL_ARGS]], align 4
// CHECK2-NEXT:    [[TMP3:%.*]] = getelementptr inbounds i8*, i8** [[TMP2]], i32 0
// CHECK2-NEXT:    [[TMP4:%.*]] = bitcast i8** [[TMP3]] to i32**
// CHECK2-NEXT:    [[TMP5:%.*]] = load i32*, i32** [[TMP4]], align 4
// CHECK2-NEXT:    call void @__omp_outlined__4(i32* [[DOTADDR1]], i32* [[DOTZERO_ADDR]], i32* [[TMP5]]) #[[ATTR2]]
// CHECK2-NEXT:    ret void
//
