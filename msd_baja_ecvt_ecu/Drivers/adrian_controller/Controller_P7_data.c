/*
 * Controller_P7_data.c
 *
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * Code generation for model "Controller_P7".
 *
 * Model version              : 5.43
 * Simulink Coder version : 25.2 (R2025b) 28-Jul-2025
 * C source code generated on : Wed Apr 29 14:11:32 2026
 *
 * Target selection: grt.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: ARM Compatible->ARM Cortex-M
 * Code generation objective: Debugging
 * Validation result: Not run
 */

#include "Controller_P7.h"

/* Block parameters (default storage) */
P_Controller_P7_T Controller_P7_P = {
  /* Variable: Der_GR_High
   * Referenced by: '<S40>/Derivative Gain'
   */
  0.0,

  /* Variable: Der_GR_Low
   * Referenced by:
   *   '<S93>/Derivative Gain'
   *   '<S146>/Derivative Gain'
   */
  0.0,

  /* Variable: Int_GR_High
   * Referenced by: '<S44>/Integral Gain'
   */
  0.0,

  /* Variable: Int_GR_Low
   * Referenced by:
   *   '<S97>/Integral Gain'
   *   '<S150>/Integral Gain'
   */
  0.0,

  /* Variable: Int_RPM_High
   * Referenced by: '<S203>/Integral Gain'
   */
  0.0,

  /* Variable: Int_RPM_Low
   * Referenced by: '<S256>/Integral Gain'
   */
  0.0,

  /* Variable: Omega_High
   * Referenced by: '<S10>/RPM_Hi'
   */
  314.15926535897933,

  /* Variable: Omega_Low
   * Referenced by: '<S11>/Constant'
   */
  188.49555921538757,

  /* Variable: Phi_max
   * Referenced by: '<S7>/Ratio Max'
   */
  3.15,

  /* Variable: Phi_min
   * Referenced by: '<S6>/Ratio Min'
   */
  0.8,

  /* Variable: Prop_GR_High
   * Referenced by: '<S52>/Proportional Gain'
   */
  20.0,

  /* Variable: Prop_GR_Low
   * Referenced by:
   *   '<S105>/Proportional Gain'
   *   '<S158>/Proportional Gain'
   */
  0.5,

  /* Variable: Prop_RPM_High
   * Referenced by: '<S211>/Proportional Gain'
   */
  5.55,

  /* Variable: Prop_RPM_Low
   * Referenced by: '<S264>/Proportional Gain'
   */
  0.05,

  /* Variable: Der_RPM_High
   * Referenced by: '<S199>/Derivative Gain'
   */
  -0.005F,

  /* Variable: Der_RPM_Low
   * Referenced by: '<S252>/Derivative Gain'
   */
  0.001F,

  /* Mask Parameter: PIDController_InitialConditionF
   * Referenced by: '<S42>/Filter'
   */
  0.0,

  /* Mask Parameter: PIDController_InitialConditio_f
   * Referenced by: '<S201>/Filter'
   */
  0.0,

  /* Mask Parameter: PIDController_InitialConditi_fp
   * Referenced by: '<S95>/Filter'
   */
  0.0,

  /* Mask Parameter: PIDController_InitialConditio_p
   * Referenced by: '<S254>/Filter'
   */
  0.0,

  /* Mask Parameter: PIDController_InitialConditio_b
   * Referenced by: '<S148>/Filter'
   */
  0.0,

  /* Mask Parameter: PIDController_InitialConditio_n
   * Referenced by: '<S47>/Integrator'
   */
  0.0,

  /* Mask Parameter: PIDController_InitialConditio_a
   * Referenced by: '<S206>/Integrator'
   */
  0.0,

  /* Mask Parameter: PIDController_InitialConditio_d
   * Referenced by: '<S100>/Integrator'
   */
  0.0,

  /* Mask Parameter: PIDController_InitialConditi_nx
   * Referenced by: '<S259>/Integrator'
   */
  0.0,

  /* Mask Parameter: PIDController_InitialConditio_k
   * Referenced by: '<S153>/Integrator'
   */
  0.0,

  /* Mask Parameter: PIDController_N
   * Referenced by: '<S50>/Filter Coefficient'
   */
  100.0,

  /* Mask Parameter: PIDController_N_e
   * Referenced by: '<S209>/Filter Coefficient'
   */
  100.0,

  /* Mask Parameter: PIDController_N_i
   * Referenced by: '<S103>/Filter Coefficient'
   */
  100.0,

  /* Mask Parameter: PIDController_N_k
   * Referenced by: '<S262>/Filter Coefficient'
   */
  100.0,

  /* Mask Parameter: PIDController_N_d
   * Referenced by: '<S156>/Filter Coefficient'
   */
  100.0,

  /* Computed Parameter: Filter_gainval
   * Referenced by: '<S42>/Filter'
   */
  0.001,

  /* Computed Parameter: Integrator_gainval
   * Referenced by: '<S47>/Integrator'
   */
  0.001,

  /* Computed Parameter: Filter_gainval_j
   * Referenced by: '<S201>/Filter'
   */
  0.001,

  /* Computed Parameter: Integrator_gainval_d
   * Referenced by: '<S206>/Integrator'
   */
  0.001,

  /* Computed Parameter: Filter_gainval_jr
   * Referenced by: '<S95>/Filter'
   */
  0.001,

  /* Computed Parameter: Integrator_gainval_c
   * Referenced by: '<S100>/Integrator'
   */
  0.001,

  /* Computed Parameter: Filter_gainval_l
   * Referenced by: '<S254>/Filter'
   */
  0.001,

  /* Computed Parameter: Integrator_gainval_p
   * Referenced by: '<S259>/Integrator'
   */
  0.001,

  /* Expression: -12
   * Referenced by: '<S3>/-12'
   */
  -12.0,

  /* Expression: 0
   * Referenced by: '<S8>/Constant'
   */
  0.0,

  /* Computed Parameter: Filter_gainval_f
   * Referenced by: '<S148>/Filter'
   */
  0.001,

  /* Computed Parameter: Integrator_gainval_i
   * Referenced by: '<S153>/Integrator'
   */
  0.001,

  /* Expression: 0
   * Referenced by: '<S5>/Ratio Max1'
   */
  0.0,

  /* Expression: 0
   * Referenced by: '<S9>/Constant2'
   */
  0.0,

  /* Expression: 0
   * Referenced by: '<S9>/Constant'
   */
  0.0,

  /* Expression: 12
   * Referenced by: '<S1>/Saturation'
   */
  12.0,

  /* Expression: -12
   * Referenced by: '<S1>/Saturation'
   */
  -12.0,

  /* Expression: 0
   * Referenced by: '<S9>/Constant1'
   */
  0.0,

  /* Expression: 0
   * Referenced by: '<S9>/Constant3'
   */
  0.0,

  /* Expression: 4.85
   * Referenced by: '<S9>/Constant4'
   */
  4.85,

  /* Computed Parameter: Iterator_IterationLimit
   * Referenced by: '<S279>/Iterator'
   */
  1,

  /* Computed Parameter: X_est_Y0
   * Referenced by: '<S279>/X_est'
   */
  0.0F,

  /* Computed Parameter: X_prd_Y0
   * Referenced by: '<S279>/X_prd'
   */
  0.0F,

  /* Computed Parameter: P_prd_Y0
   * Referenced by: '<S279>/P_prd'
   */
  0.0F,

  /* Computed Parameter: Constant3_Value_a
   * Referenced by: '<S281>/Constant3'
   */
  { 1.0F, 0.0F, 0.0F, 0.0F, 0.001F, 1.0F, 0.0F, 0.0F, 0.0F, 0.0F, 1.0F, 0.0F,
    0.0F, 0.0F, 0.001F, 1.0F },

  /* Computed Parameter: Hcst_Value
   * Referenced by: '<S281>/Hcst'
   */
  { 1.0F, 0.0F, 0.0F, 0.0F, 0.0F, 1.0F, 0.0F, 0.0F },

  /* Computed Parameter: Hcst_t_Value
   * Referenced by: '<S281>/Hcst_t'
   */
  { 1.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 1.0F, 0.0F },

  /* Computed Parameter: Constant2_Value_k
   * Referenced by: '<S281>/Constant2'
   */
  { 16.0F, 0.0F, 0.0F, 16.0F },

  /* Computed Parameter: Constant4_Value_j
   * Referenced by: '<S281>/Constant4'
   */
  { 1.0F, 0.001F, 0.0F, 0.0F, 0.0F, 1.0F, 0.0F, 0.0F, 0.0F, 0.0F, 1.0F, 0.001F,
    0.0F, 0.0F, 0.0F, 1.0F },

  /* Computed Parameter: Constant5_Value
   * Referenced by: '<S281>/Constant5'
   */
  { 0.1F, 0.0F, 0.0F, 0.0F, 0.0F, 1.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.1F, 0.0F, 0.0F,
    0.0F, 0.0F, 1.0F },

  /* Computed Parameter: UnitDelay2_InitialCondition
   * Referenced by: '<S277>/Unit Delay2'
   */
  { 0.0F, 0.0F, 0.0F, 0.0F },

  /* Computed Parameter: UnitDelay3_InitialCondition
   * Referenced by: '<S277>/Unit Delay3'
   */
  { 10.1000099F, 0.01F, 0.0F, 0.0F, 0.01F, 11.0F, 0.0F, 0.0F, 0.0F, 0.0F,
    10.1000099F, 0.01F, 0.0F, 0.0F, 0.01F, 11.0F }
};
