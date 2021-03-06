; NOTE: Assertions have been autogenerated by utils/update_test_checks.py
; RUN: opt -passes=instcombine -mtriple=arm64-apple-ios -S %s | FileCheck %s

declare <4 x half> @llvm.aarch64.neon.fmaxnm.v4f16(<4 x half>, <4 x half>)
declare <4 x float> @llvm.aarch64.neon.fmaxnm.v4f32(<4 x float>, <4 x float>)
declare <2 x double> @llvm.aarch64.neon.fmaxnm.v2f64(<2 x double>, <2 x double>)

define <4 x half> @fmaxnm_v4f16_same_args(<4 x half> %a) {
; CHECK-LABEL: @fmaxnm_v4f16_same_args(
; CHECK-NEXT:    ret <4 x half> [[A:%.*]]
;
  %r = call <4 x half> @llvm.aarch64.neon.fmaxnm.v4f16(<4 x half> %a, <4 x half> %a)
  ret <4 x half> %r
}

define <4 x half> @fmaxnm_v4f16_different_args(<4 x half> %a, <4 x half> %b) {
; CHECK-LABEL: @fmaxnm_v4f16_different_args(
; CHECK-NEXT:    [[R:%.*]] = call <4 x half> @llvm.aarch64.neon.fmaxnm.v4f16(<4 x half> [[A:%.*]], <4 x half> [[B:%.*]])
; CHECK-NEXT:    ret <4 x half> [[R]]
;
  %r = call <4 x half> @llvm.aarch64.neon.fmaxnm.v4f16(<4 x half> %a, <4 x half> %b)
  ret <4 x half> %r
}

define <4 x float> @fmaxnm_v4f32_same_args(<4 x float> %a) {
; CHECK-LABEL: @fmaxnm_v4f32_same_args(
; CHECK-NEXT:    ret <4 x float> [[A:%.*]]
;
  %r = call <4 x float> @llvm.aarch64.neon.fmaxnm.v4f32(<4 x float> %a, <4 x float> %a)
  ret <4 x float> %r
}

define <4 x float> @fmaxnm_v4f32_different_args(<4 x float> %a, <4 x float> %b) {
; CHECK-LABEL: @fmaxnm_v4f32_different_args(
; CHECK-NEXT:    [[R:%.*]] = call <4 x float> @llvm.aarch64.neon.fmaxnm.v4f32(<4 x float> [[A:%.*]], <4 x float> [[B:%.*]])
; CHECK-NEXT:    ret <4 x float> [[R]]
;
  %r = call <4 x float> @llvm.aarch64.neon.fmaxnm.v4f32(<4 x float> %a, <4 x float> %b)
  ret <4 x float> %r
}

define <2 x double> @fmaxnm_v2f64_same_args(<2 x double> %a) {
; CHECK-LABEL: @fmaxnm_v2f64_same_args(
; CHECK-NEXT:    ret <2 x double> [[A:%.*]]
;
  %r = call <2 x double> @llvm.aarch64.neon.fmaxnm.v2f64(<2 x double> %a, <2 x double> %a)
  ret <2 x double> %r
}

define <2 x double> @fmaxnm_v2f64_different_args(<2 x double> %a, <2 x double> %b) {
; CHECK-LABEL: @fmaxnm_v2f64_different_args(
; CHECK-NEXT:    [[R:%.*]] = call <2 x double> @llvm.aarch64.neon.fmaxnm.v2f64(<2 x double> [[A:%.*]], <2 x double> [[B:%.*]])
; CHECK-NEXT:    ret <2 x double> [[R]]
;
  %r = call <2 x double> @llvm.aarch64.neon.fmaxnm.v2f64(<2 x double> %a, <2 x double> %b)
  ret <2 x double> %r
}

declare <4 x half> @llvm.aarch64.neon.fminnm.v4f16(<4 x half>, <4 x half>)
declare <4 x float> @llvm.aarch64.neon.fminnm.v4f32(<4 x float>, <4 x float>)
declare <2 x double> @llvm.aarch64.neon.fminnm.v2f64(<2 x double>, <2 x double>)

define <4 x half> @fminnm_v4f16_same_args(<4 x half> %a) {
; CHECK-LABEL: @fminnm_v4f16_same_args(
; CHECK-NEXT:    ret <4 x half> [[A:%.*]]
;
  %r = call <4 x half> @llvm.aarch64.neon.fminnm.v4f16(<4 x half> %a, <4 x half> %a)
  ret <4 x half> %r
}

define <4 x half> @fminnm_v4f16_different_args(<4 x half> %a, <4 x half> %b) {
; CHECK-LABEL: @fminnm_v4f16_different_args(
; CHECK-NEXT:    [[R:%.*]] = call <4 x half> @llvm.aarch64.neon.fminnm.v4f16(<4 x half> [[A:%.*]], <4 x half> [[B:%.*]])
; CHECK-NEXT:    ret <4 x half> [[R]]
;
  %r = call <4 x half> @llvm.aarch64.neon.fminnm.v4f16(<4 x half> %a, <4 x half> %b)
  ret <4 x half> %r
}

define <4 x float> @fminnm_v4f32_same_args(<4 x float> %a) {
; CHECK-LABEL: @fminnm_v4f32_same_args(
; CHECK-NEXT:    ret <4 x float> [[A:%.*]]
;
  %r = call <4 x float> @llvm.aarch64.neon.fminnm.v4f32(<4 x float> %a, <4 x float> %a)
  ret <4 x float> %r
}

define <4 x float> @fminnm_v4f32_different_args(<4 x float> %a, <4 x float> %b) {
; CHECK-LABEL: @fminnm_v4f32_different_args(
; CHECK-NEXT:    [[R:%.*]] = call <4 x float> @llvm.aarch64.neon.fminnm.v4f32(<4 x float> [[A:%.*]], <4 x float> [[B:%.*]])
; CHECK-NEXT:    ret <4 x float> [[R]]
;
  %r = call <4 x float> @llvm.aarch64.neon.fminnm.v4f32(<4 x float> %a, <4 x float> %b)
  ret <4 x float> %r
}

define <2 x double> @fminnm_v2f64_same_args(<2 x double> %a) {
; CHECK-LABEL: @fminnm_v2f64_same_args(
; CHECK-NEXT:    ret <2 x double> [[A:%.*]]
;
  %r = call <2 x double> @llvm.aarch64.neon.fminnm.v2f64(<2 x double> %a, <2 x double> %a)
  ret <2 x double> %r
}

define <2 x double> @fminnm_v2f64_different_args(<2 x double> %a, <2 x double> %b) {
; CHECK-LABEL: @fminnm_v2f64_different_args(
; CHECK-NEXT:    [[R:%.*]] = call <2 x double> @llvm.aarch64.neon.fminnm.v2f64(<2 x double> [[A:%.*]], <2 x double> [[B:%.*]])
; CHECK-NEXT:    ret <2 x double> [[R]]
;
  %r = call <2 x double> @llvm.aarch64.neon.fminnm.v2f64(<2 x double> %a, <2 x double> %b)
  ret <2 x double> %r
}
