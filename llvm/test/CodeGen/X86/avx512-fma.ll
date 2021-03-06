; NOTE: Assertions have been autogenerated by utils/update_llc_test_checks.py
; RUN: llc < %s -mtriple=x86_64-apple-darwin -mattr=+avx512f -fp-contract=fast | FileCheck %s --check-prefix=ALL --check-prefix=KNL
; RUN: llc < %s -mtriple=x86_64-apple-darwin -mcpu=skx -fp-contract=fast | FileCheck %s --check-prefix=ALL --check-prefix=SKX

define <16 x float> @test_x86_fmadd_ps_z(<16 x float> %a0, <16 x float> %a1, <16 x float> %a2) {
; ALL-LABEL: test_x86_fmadd_ps_z:
; ALL:       ## %bb.0:
; ALL-NEXT:    vfmadd213ps {{.*#+}} zmm0 = (zmm1 * zmm0) + zmm2
; ALL-NEXT:    retq
  %x = fmul <16 x float> %a0, %a1
  %res = fadd <16 x float> %x, %a2
  ret <16 x float> %res
}

define <16 x float> @test_x86_fmsub_ps_z(<16 x float> %a0, <16 x float> %a1, <16 x float> %a2) {
; ALL-LABEL: test_x86_fmsub_ps_z:
; ALL:       ## %bb.0:
; ALL-NEXT:    vfmsub213ps {{.*#+}} zmm0 = (zmm1 * zmm0) - zmm2
; ALL-NEXT:    retq
  %x = fmul <16 x float> %a0, %a1
  %res = fsub <16 x float> %x, %a2
  ret <16 x float> %res
}

define <16 x float> @test_x86_fnmadd_ps_z(<16 x float> %a0, <16 x float> %a1, <16 x float> %a2) {
; ALL-LABEL: test_x86_fnmadd_ps_z:
; ALL:       ## %bb.0:
; ALL-NEXT:    vfnmadd213ps {{.*#+}} zmm0 = -(zmm1 * zmm0) + zmm2
; ALL-NEXT:    retq
  %x = fmul <16 x float> %a0, %a1
  %res = fsub <16 x float> %a2, %x
  ret <16 x float> %res
}

define <16 x float> @test_x86_fnmsub_ps_z(<16 x float> %a0, <16 x float> %a1, <16 x float> %a2) {
; ALL-LABEL: test_x86_fnmsub_ps_z:
; ALL:       ## %bb.0:
; ALL-NEXT:    vfnmsub213ps {{.*#+}} zmm0 = -(zmm1 * zmm0) - zmm2
; ALL-NEXT:    retq
  %x = fmul <16 x float> %a0, %a1
  %y = fsub <16 x float> <float -0.000000e+00, float -0.000000e+00, float -0.000000e+00, float -0.000000e+00, float -0.000000e+00,
                          float -0.000000e+00, float -0.000000e+00, float -0.000000e+00, float -0.000000e+00, float -0.000000e+00,
                          float -0.000000e+00, float -0.000000e+00, float -0.000000e+00, float -0.000000e+00, float -0.000000e+00,
                          float -0.000000e+00>, %x
  %res = fsub <16 x float> %y, %a2
  ret <16 x float> %res
}

define <8 x double> @test_x86_fmadd_pd_z(<8 x double> %a0, <8 x double> %a1, <8 x double> %a2) {
; ALL-LABEL: test_x86_fmadd_pd_z:
; ALL:       ## %bb.0:
; ALL-NEXT:    vfmadd213pd {{.*#+}} zmm0 = (zmm1 * zmm0) + zmm2
; ALL-NEXT:    retq
  %x = fmul <8 x double> %a0, %a1
  %res = fadd <8 x double> %x, %a2
  ret <8 x double> %res
}

define <8 x double> @test_x86_fmsub_pd_z(<8 x double> %a0, <8 x double> %a1, <8 x double> %a2) {
; ALL-LABEL: test_x86_fmsub_pd_z:
; ALL:       ## %bb.0:
; ALL-NEXT:    vfmsub213pd {{.*#+}} zmm0 = (zmm1 * zmm0) - zmm2
; ALL-NEXT:    retq
  %x = fmul <8 x double> %a0, %a1
  %res = fsub <8 x double> %x, %a2
  ret <8 x double> %res
}

define double @test_x86_fmsub_213(double %a0, double %a1, double %a2) {
; ALL-LABEL: test_x86_fmsub_213:
; ALL:       ## %bb.0:
; ALL-NEXT:    vfmsub213sd {{.*#+}} xmm0 = (xmm1 * xmm0) - xmm2
; ALL-NEXT:    retq
  %x = fmul double %a0, %a1
  %res = fsub double %x, %a2
  ret double %res
}

define double @test_x86_fmsub_213_m(double %a0, double %a1, ptr %a2_ptr) {
; ALL-LABEL: test_x86_fmsub_213_m:
; ALL:       ## %bb.0:
; ALL-NEXT:    vfmsub213sd {{.*#+}} xmm0 = (xmm1 * xmm0) - mem
; ALL-NEXT:    retq
  %a2 = load double , ptr%a2_ptr
  %x = fmul double %a0, %a1
  %res = fsub double %x, %a2
  ret double %res
}

define double @test_x86_fmsub_231_m(double %a0, double %a1, ptr %a2_ptr) {
; ALL-LABEL: test_x86_fmsub_231_m:
; ALL:       ## %bb.0:
; ALL-NEXT:    vfmsub132sd {{.*#+}} xmm0 = (xmm0 * mem) - xmm1
; ALL-NEXT:    retq
  %a2 = load double , ptr%a2_ptr
  %x = fmul double %a0, %a2
  %res = fsub double %x, %a1
  ret double %res
}

define <16 x float> @test231_br(<16 x float> %a1, <16 x float> %a2) nounwind {
; ALL-LABEL: test231_br:
; ALL:       ## %bb.0:
; ALL-NEXT:    vfmadd132ps {{.*#+}} zmm0 = (zmm0 * mem) + zmm1
; ALL-NEXT:    retq
  %b1 = fmul <16 x float> %a1, <float 0x3FB99999A0000000, float 0x3FB99999A0000000, float 0x3FB99999A0000000, float 0x3FB99999A0000000, float 0x3FB99999A0000000, float 0x3FB99999A0000000, float 0x3FB99999A0000000, float 0x3FB99999A0000000, float 0x3FB99999A0000000, float 0x3FB99999A0000000, float 0x3FB99999A0000000, float 0x3FB99999A0000000, float 0x3FB99999A0000000, float 0x3FB99999A0000000, float 0x3FB99999A0000000, float 0x3FB99999A0000000>
  %b2 = fadd <16 x float> %b1, %a2
  ret <16 x float> %b2
}

define <16 x float> @test213_br(<16 x float> %a1, <16 x float> %a2) nounwind {
; ALL-LABEL: test213_br:
; ALL:       ## %bb.0:
; ALL-NEXT:    vfmadd213ps {{.*#+}} zmm0 = (zmm1 * zmm0) + mem
; ALL-NEXT:    retq
  %b1 = fmul <16 x float> %a1, %a2
  %b2 = fadd <16 x float> %b1, <float 0x3FB99999A0000000, float 0x3FB99999A0000000, float 0x3FB99999A0000000, float 0x3FB99999A0000000, float 0x3FB99999A0000000, float 0x3FB99999A0000000, float 0x3FB99999A0000000, float 0x3FB99999A0000000, float 0x3FB99999A0000000, float 0x3FB99999A0000000, float 0x3FB99999A0000000, float 0x3FB99999A0000000, float 0x3FB99999A0000000, float 0x3FB99999A0000000, float 0x3FB99999A0000000, float 0x3FB99999A0000000>
  ret <16 x float> %b2
}

;mask (a*c+b , a)
define <16 x float> @test_x86_fmadd132_ps(<16 x float> %a0, <16 x float> %a1, ptr%a2_ptrt, <16 x i1> %mask) {
; KNL-LABEL: test_x86_fmadd132_ps:
; KNL:       ## %bb.0:
; KNL-NEXT:    vpmovsxbd %xmm2, %zmm2
; KNL-NEXT:    vpslld $31, %zmm2, %zmm2
; KNL-NEXT:    vptestmd %zmm2, %zmm2, %k1
; KNL-NEXT:    vfmadd132ps {{.*#+}} zmm0 {%k1} = (zmm0 * mem) + zmm1
; KNL-NEXT:    retq
;
; SKX-LABEL: test_x86_fmadd132_ps:
; SKX:       ## %bb.0:
; SKX-NEXT:    vpsllw $7, %xmm2, %xmm2
; SKX-NEXT:    vpmovb2m %xmm2, %k1
; SKX-NEXT:    vfmadd132ps {{.*#+}} zmm0 {%k1} = (zmm0 * mem) + zmm1
; SKX-NEXT:    retq
  %a2   = load <16 x float>,ptr%a2_ptrt,align 1
  %x = fmul <16 x float> %a0, %a2
  %y = fadd <16 x float> %x, %a1
  %res = select <16 x i1> %mask, <16 x float> %y, <16 x float> %a0
  ret <16 x float> %res
}

;mask (a*c+b , b)
define <16 x float> @test_x86_fmadd231_ps(<16 x float> %a0, <16 x float> %a1, ptr%a2_ptrt, <16 x i1> %mask) {
; KNL-LABEL: test_x86_fmadd231_ps:
; KNL:       ## %bb.0:
; KNL-NEXT:    vpmovsxbd %xmm2, %zmm2
; KNL-NEXT:    vpslld $31, %zmm2, %zmm2
; KNL-NEXT:    vptestmd %zmm2, %zmm2, %k1
; KNL-NEXT:    vfmadd231ps {{.*#+}} zmm1 {%k1} = (zmm0 * mem) + zmm1
; KNL-NEXT:    vmovaps %zmm1, %zmm0
; KNL-NEXT:    retq
;
; SKX-LABEL: test_x86_fmadd231_ps:
; SKX:       ## %bb.0:
; SKX-NEXT:    vpsllw $7, %xmm2, %xmm2
; SKX-NEXT:    vpmovb2m %xmm2, %k1
; SKX-NEXT:    vfmadd231ps {{.*#+}} zmm1 {%k1} = (zmm0 * mem) + zmm1
; SKX-NEXT:    vmovaps %zmm1, %zmm0
; SKX-NEXT:    retq
  %a2   = load <16 x float>,ptr%a2_ptrt,align 1
  %x = fmul <16 x float> %a0, %a2
  %y = fadd <16 x float> %x, %a1
  %res = select <16 x i1> %mask, <16 x float> %y, <16 x float> %a1
  ret <16 x float> %res
}

;mask (b*a+c , b)
define <16 x float> @test_x86_fmadd213_ps(<16 x float> %a0, <16 x float> %a1, ptr%a2_ptrt, <16 x i1> %mask) {
; KNL-LABEL: test_x86_fmadd213_ps:
; KNL:       ## %bb.0:
; KNL-NEXT:    vpmovsxbd %xmm2, %zmm2
; KNL-NEXT:    vpslld $31, %zmm2, %zmm2
; KNL-NEXT:    vptestmd %zmm2, %zmm2, %k1
; KNL-NEXT:    vfmadd213ps {{.*#+}} zmm1 {%k1} = (zmm0 * zmm1) + mem
; KNL-NEXT:    vmovaps %zmm1, %zmm0
; KNL-NEXT:    retq
;
; SKX-LABEL: test_x86_fmadd213_ps:
; SKX:       ## %bb.0:
; SKX-NEXT:    vpsllw $7, %xmm2, %xmm2
; SKX-NEXT:    vpmovb2m %xmm2, %k1
; SKX-NEXT:    vfmadd213ps {{.*#+}} zmm1 {%k1} = (zmm0 * zmm1) + mem
; SKX-NEXT:    vmovaps %zmm1, %zmm0
; SKX-NEXT:    retq
  %a2   = load <16 x float>,ptr%a2_ptrt,align 1
  %x = fmul <16 x float> %a1, %a0
  %y = fadd <16 x float> %x, %a2
  %res = select <16 x i1> %mask, <16 x float> %y, <16 x float> %a1
  ret <16 x float> %res
}

