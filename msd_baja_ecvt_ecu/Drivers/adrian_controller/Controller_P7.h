/*
 * Controller_P7.h
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

#ifndef Controller_P7_h_
#define Controller_P7_h_
#ifndef Controller_P7_COMMON_INCLUDES_
#define Controller_P7_COMMON_INCLUDES_
#include "rtwtypes.h"
#include "rtw_continuous.h"
#include "rtw_solver.h"
#include "rt_logging.h"
#include "rt_nonfinite.h"
#include "math.h"
#endif                                 /* Controller_P7_COMMON_INCLUDES_ */

#include "Controller_P7_types.h"
#include <float.h>
#include <string.h>
#include <stddef.h>

/* Macros for accessing real-time model data structure */
#ifndef rtmGetFinalTime
#define rtmGetFinalTime(rtm)           ((rtm)->Timing.tFinal)
#endif

#ifndef rtmGetRTWLogInfo
#define rtmGetRTWLogInfo(rtm)          ((rtm)->rtwLogInfo)
#endif

#ifndef rtmGetErrorStatus
#define rtmGetErrorStatus(rtm)         ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatus
#define rtmSetErrorStatus(rtm, val)    ((rtm)->errorStatus = (val))
#endif

#ifndef rtmGetStopRequested
#define rtmGetStopRequested(rtm)       ((rtm)->Timing.stopRequestedFlag)
#endif

#ifndef rtmSetStopRequested
#define rtmSetStopRequested(rtm, val)  ((rtm)->Timing.stopRequestedFlag = (val))
#endif

#ifndef rtmGetStopRequestedPtr
#define rtmGetStopRequestedPtr(rtm)    (&((rtm)->Timing.stopRequestedFlag))
#endif

#ifndef rtmGetT
#define rtmGetT(rtm)                   ((rtm)->Timing.taskTime0)
#endif

#ifndef rtmGetTFinal
#define rtmGetTFinal(rtm)              ((rtm)->Timing.tFinal)
#endif

#ifndef rtmGetTPtr
#define rtmGetTPtr(rtm)                (&(rtm)->Timing.taskTime0)
#endif

/* Block signals (default storage) */
typedef struct {
  real_T Merge;                        /* '<S1>/Merge' */
  real_T Saturation;                   /* '<S1>/Saturation' */
  real_T Add;                          /* '<S8>/Add' */
  real_T DerivativeGain;               /* '<S146>/Derivative Gain' */
  real_T Filter;                       /* '<S148>/Filter' */
  real_T SumD;                         /* '<S148>/SumD' */
  real_T IntegralGain;                 /* '<S150>/Integral Gain' */
  real_T Integrator;                   /* '<S153>/Integrator' */
  real_T FilterCoefficient;            /* '<S156>/Filter Coefficient' */
  real_T ProportionalGain;             /* '<S158>/Proportional Gain' */
  real_T Add_b;                        /* '<S11>/Add' */
  real_T Filter_p;                     /* '<S254>/Filter' */
  real_T FilterCoefficient_i;          /* '<S262>/Filter Coefficient' */
  real_T SumD_i;                       /* '<S254>/SumD' */
  real_T IntegralGain_a;               /* '<S256>/Integral Gain' */
  real_T Integrator_f;                 /* '<S259>/Integrator' */
  real_T ProportionalGain_g;           /* '<S264>/Proportional Gain' */
  real_T Add_bo;                       /* '<S7>/Add' */
  real_T DerivativeGain_f;             /* '<S93>/Derivative Gain' */
  real_T Filter_k;                     /* '<S95>/Filter' */
  real_T SumD_e;                       /* '<S95>/SumD' */
  real_T IntegralGain_h;               /* '<S97>/Integral Gain' */
  real_T Integrator_l;                 /* '<S100>/Integrator' */
  real_T FilterCoefficient_m;          /* '<S103>/Filter Coefficient' */
  real_T ProportionalGain_o;           /* '<S105>/Proportional Gain' */
  real_T Add_c;                        /* '<S10>/Add' */
  real_T Filter_e;                     /* '<S201>/Filter' */
  real_T FilterCoefficient_ip;         /* '<S209>/Filter Coefficient' */
  real_T SumD_d;                       /* '<S201>/SumD' */
  real_T IntegralGain_d;               /* '<S203>/Integral Gain' */
  real_T Integrator_li;                /* '<S206>/Integrator' */
  real_T ProportionalGain_b;           /* '<S211>/Proportional Gain' */
  real_T Add_l;                        /* '<S6>/Add' */
  real_T DerivativeGain_p;             /* '<S40>/Derivative Gain' */
  real_T Filter_d;                     /* '<S42>/Filter' */
  real_T SumD_dl;                      /* '<S42>/SumD' */
  real_T IntegralGain_f;               /* '<S44>/Integral Gain' */
  real_T Integrator_d;                 /* '<S47>/Integrator' */
  real_T FilterCoefficient_g;          /* '<S50>/Filter Coefficient' */
  real_T ProportionalGain_p;           /* '<S52>/Proportional Gain' */
  real_T mode;                         /* '<S1>/Chart' */
  real32_T UnitDelay2[4];              /* '<S277>/Unit Delay2' */
  real32_T UnitDelay3[16];             /* '<S277>/Unit Delay3' */
  real32_T Selector2[16];              /* '<S280>/Selector2' */
  real32_T P_prdTrans[16];             /* '<S281>/P_prd Trans' */
  real32_T HP_prdt[8];                 /* '<S281>/H*P_prdt' */
  real32_T HP_prdtHt[4];               /* '<S281>/H*P_prdt*Ht' */
  real32_T HP_prdtHtR[4];              /* '<S281>/H*P_prdt*Ht+R' */
  real32_T LDLFactorization[4];        /* '<S285>/LDL Factorization' */
  real32_T y[8];                       /* '<S285>/Forward Substitution' */
  real32_T d[2];                       /* '<S285>/Extract Diagonal' */
  real32_T MathFunction[2];            /* '<S285>/Math Function' */
  real32_T MatrixScaling[8];           /* '<S285>/Matrix Scaling' */
  real32_T BackwardSubstitution[8];    /* '<S285>/Backward Substitution' */
  real32_T KTrans[8];                  /* '<S281>/K Trans' */
  real32_T KHP_prd[16];                /* '<S281>/K*H*P_prd' */
  real32_T P_prdKHP_prd[16];           /* '<S281>/P_prd-K*H*P_prd' */
  real32_T APAt[16];                   /* '<S281>/A*P*At' */
  real32_T APAtQ[16];                  /* '<S281>/A*P*At+Q' */
  real32_T Selector1[4];               /* '<S280>/Selector1' */
  real32_T TmpSignalConversionAtSelectorIn[2];
  real32_T Selector[2];                /* '<S280>/Selector' */
  real32_T HX_prd[2];                  /* '<S281>/H*X_prd' */
  real32_T ZHX_prd[2];                 /* '<S281>/Z-H*X_prd' */
  real32_T KZHX_prd[4];                /* '<S281>/K*(Z-H*X_prd)' */
  real32_T X_prdKZHX_prd[4];           /* '<S281>/X_prd+K*(Z-H*X_prd)' */
  real32_T AX[4];                      /* '<S281>/A*X' */
  real32_T Assignment[16];             /* '<S282>/Assignment' */
  real32_T Assignment_c[4];            /* '<S283>/Assignment' */
  real32_T Assignment_a[4];            /* '<S284>/Assignment' */
  real32_T UnaryMinus;                 /* '<S253>/Unary Minus' */
  real32_T DerivativeGain_f1;          /* '<S252>/Derivative Gain' */
  real32_T UnaryMinus_o;               /* '<S200>/Unary Minus' */
  real32_T DerivativeGain_b;           /* '<S199>/Derivative Gain' */
  int32_T Iterator;                    /* '<S279>/Iterator' */
  boolean_T GreaterThan;               /* '<S9>/GreaterThan' */
  boolean_T LessThan;                  /* '<S9>/Less Than' */
  boolean_T AND;                       /* '<S9>/AND' */
  boolean_T GreaterThan1;              /* '<S9>/GreaterThan1' */
  boolean_T GreaterThan2;              /* '<S9>/GreaterThan2' */
  boolean_T AND1;                      /* '<S9>/AND1' */
  boolean_T OR;                        /* '<S9>/OR' */
} B_Controller_P7_T;

/* Block states (default storage) for system '<Root>' */
typedef struct {
  real_T Filter_DSTATE;                /* '<S148>/Filter' */
  real_T Integrator_DSTATE;            /* '<S153>/Integrator' */
  real_T Filter_DSTATE_j;              /* '<S254>/Filter' */
  real_T Integrator_DSTATE_p;          /* '<S259>/Integrator' */
  real_T Filter_DSTATE_i;              /* '<S95>/Filter' */
  real_T Integrator_DSTATE_g;          /* '<S100>/Integrator' */
  real_T Filter_DSTATE_b;              /* '<S201>/Filter' */
  real_T Integrator_DSTATE_c;          /* '<S206>/Integrator' */
  real_T Filter_DSTATE_c;              /* '<S42>/Filter' */
  real_T Integrator_DSTATE_e;          /* '<S47>/Integrator' */
  real_T Add_DWORK1;                   /* '<S8>/Add' */
  real32_T UnitDelay2_DSTATE[4];       /* '<S277>/Unit Delay2' */
  real32_T UnitDelay3_DSTATE[16];      /* '<S277>/Unit Delay3' */
  real32_T LDLFactorization_VMX[2];    /* '<S285>/LDL Factorization' */
  real32_T APAt_DWORK1[16];            /* '<S281>/A*P*At' */
  uint8_T is_active_c3_Controller_P7;  /* '<S1>/Chart' */
  uint8_T is_c3_Controller_P7;         /* '<S1>/Chart' */
  boolean_T LDLFactorization_STATE;    /* '<S285>/LDL Factorization' */
} DW_Controller_P7_T;

/* External inputs (root inport signals with default storage) */
typedef struct {
  real32_T Omega_Primary;              /* '<Root>/Omega_Primary' */
  real32_T Omega_Secondary;            /* '<Root>/Omega_Secondary' */
  real32_T Theta_Helix;                /* '<Root>/Theta_Helix' */
} ExtU_Controller_P7_T;

/* External outputs (root outports fed by signals with default storage) */
typedef struct {
  real_T Command;                      /* '<Root>/Command' */
  real32_T CVT_Ratio;                  /* '<Root>/CVT_Ratio' */
  real32_T Primary_Speed;              /* '<Root>/Primary_Speed' */
  real32_T Secondary_Speed;            /* '<Root>/Secondary_Speed' */
} ExtY_Controller_P7_T;

/* Parameters (default storage) */
struct P_Controller_P7_T_ {
  real_T Der_GR_High;                  /* Variable: Der_GR_High
                                        * Referenced by: '<S40>/Derivative Gain'
                                        */
  real_T Der_GR_Low;                   /* Variable: Der_GR_Low
                                        * Referenced by:
                                        *   '<S93>/Derivative Gain'
                                        *   '<S146>/Derivative Gain'
                                        */
  real_T Int_GR_High;                  /* Variable: Int_GR_High
                                        * Referenced by: '<S44>/Integral Gain'
                                        */
  real_T Int_GR_Low;                   /* Variable: Int_GR_Low
                                        * Referenced by:
                                        *   '<S97>/Integral Gain'
                                        *   '<S150>/Integral Gain'
                                        */
  real_T Int_RPM_High;                 /* Variable: Int_RPM_High
                                        * Referenced by: '<S203>/Integral Gain'
                                        */
  real_T Int_RPM_Low;                  /* Variable: Int_RPM_Low
                                        * Referenced by: '<S256>/Integral Gain'
                                        */
  real_T Omega_High;                   /* Variable: Omega_High
                                        * Referenced by: '<S10>/RPM_Hi'
                                        */
  real_T Omega_Low;                    /* Variable: Omega_Low
                                        * Referenced by: '<S11>/Constant'
                                        */
  real_T Phi_max;                      /* Variable: Phi_max
                                        * Referenced by: '<S7>/Ratio Max'
                                        */
  real_T Phi_min;                      /* Variable: Phi_min
                                        * Referenced by: '<S6>/Ratio Min'
                                        */
  real_T Prop_GR_High;                 /* Variable: Prop_GR_High
                                        * Referenced by: '<S52>/Proportional Gain'
                                        */
  real_T Prop_GR_Low;                  /* Variable: Prop_GR_Low
                                        * Referenced by:
                                        *   '<S105>/Proportional Gain'
                                        *   '<S158>/Proportional Gain'
                                        */
  real_T Prop_RPM_High;                /* Variable: Prop_RPM_High
                                        * Referenced by: '<S211>/Proportional Gain'
                                        */
  real_T Prop_RPM_Low;                 /* Variable: Prop_RPM_Low
                                        * Referenced by: '<S264>/Proportional Gain'
                                        */
  real32_T Der_RPM_High;               /* Variable: Der_RPM_High
                                        * Referenced by: '<S199>/Derivative Gain'
                                        */
  real32_T Der_RPM_Low;                /* Variable: Der_RPM_Low
                                        * Referenced by: '<S252>/Derivative Gain'
                                        */
  real_T PIDController_InitialConditionF;
                              /* Mask Parameter: PIDController_InitialConditionF
                               * Referenced by: '<S42>/Filter'
                               */
  real_T PIDController_InitialConditio_f;
                              /* Mask Parameter: PIDController_InitialConditio_f
                               * Referenced by: '<S201>/Filter'
                               */
  real_T PIDController_InitialConditi_fp;
                              /* Mask Parameter: PIDController_InitialConditi_fp
                               * Referenced by: '<S95>/Filter'
                               */
  real_T PIDController_InitialConditio_p;
                              /* Mask Parameter: PIDController_InitialConditio_p
                               * Referenced by: '<S254>/Filter'
                               */
  real_T PIDController_InitialConditio_b;
                              /* Mask Parameter: PIDController_InitialConditio_b
                               * Referenced by: '<S148>/Filter'
                               */
  real_T PIDController_InitialConditio_n;
                              /* Mask Parameter: PIDController_InitialConditio_n
                               * Referenced by: '<S47>/Integrator'
                               */
  real_T PIDController_InitialConditio_a;
                              /* Mask Parameter: PIDController_InitialConditio_a
                               * Referenced by: '<S206>/Integrator'
                               */
  real_T PIDController_InitialConditio_d;
                              /* Mask Parameter: PIDController_InitialConditio_d
                               * Referenced by: '<S100>/Integrator'
                               */
  real_T PIDController_InitialConditi_nx;
                              /* Mask Parameter: PIDController_InitialConditi_nx
                               * Referenced by: '<S259>/Integrator'
                               */
  real_T PIDController_InitialConditio_k;
                              /* Mask Parameter: PIDController_InitialConditio_k
                               * Referenced by: '<S153>/Integrator'
                               */
  real_T PIDController_N;              /* Mask Parameter: PIDController_N
                                        * Referenced by: '<S50>/Filter Coefficient'
                                        */
  real_T PIDController_N_e;            /* Mask Parameter: PIDController_N_e
                                        * Referenced by: '<S209>/Filter Coefficient'
                                        */
  real_T PIDController_N_i;            /* Mask Parameter: PIDController_N_i
                                        * Referenced by: '<S103>/Filter Coefficient'
                                        */
  real_T PIDController_N_k;            /* Mask Parameter: PIDController_N_k
                                        * Referenced by: '<S262>/Filter Coefficient'
                                        */
  real_T PIDController_N_d;            /* Mask Parameter: PIDController_N_d
                                        * Referenced by: '<S156>/Filter Coefficient'
                                        */
  real_T Filter_gainval;               /* Computed Parameter: Filter_gainval
                                        * Referenced by: '<S42>/Filter'
                                        */
  real_T Integrator_gainval;           /* Computed Parameter: Integrator_gainval
                                        * Referenced by: '<S47>/Integrator'
                                        */
  real_T Filter_gainval_j;             /* Computed Parameter: Filter_gainval_j
                                        * Referenced by: '<S201>/Filter'
                                        */
  real_T Integrator_gainval_d;       /* Computed Parameter: Integrator_gainval_d
                                      * Referenced by: '<S206>/Integrator'
                                      */
  real_T Filter_gainval_jr;            /* Computed Parameter: Filter_gainval_jr
                                        * Referenced by: '<S95>/Filter'
                                        */
  real_T Integrator_gainval_c;       /* Computed Parameter: Integrator_gainval_c
                                      * Referenced by: '<S100>/Integrator'
                                      */
  real_T Filter_gainval_l;             /* Computed Parameter: Filter_gainval_l
                                        * Referenced by: '<S254>/Filter'
                                        */
  real_T Integrator_gainval_p;       /* Computed Parameter: Integrator_gainval_p
                                      * Referenced by: '<S259>/Integrator'
                                      */
  real_T u2_Value;                     /* Expression: -12
                                        * Referenced by: '<S3>/-12'
                                        */
  real_T Constant_Value;               /* Expression: 0
                                        * Referenced by: '<S8>/Constant'
                                        */
  real_T Filter_gainval_f;             /* Computed Parameter: Filter_gainval_f
                                        * Referenced by: '<S148>/Filter'
                                        */
  real_T Integrator_gainval_i;       /* Computed Parameter: Integrator_gainval_i
                                      * Referenced by: '<S153>/Integrator'
                                      */
  real_T RatioMax1_Value;              /* Expression: 0
                                        * Referenced by: '<S5>/Ratio Max1'
                                        */
  real_T Constant2_Value;              /* Expression: 0
                                        * Referenced by: '<S9>/Constant2'
                                        */
  real_T Constant_Value_c;             /* Expression: 0
                                        * Referenced by: '<S9>/Constant'
                                        */
  real_T Saturation_UpperSat;          /* Expression: 12
                                        * Referenced by: '<S1>/Saturation'
                                        */
  real_T Saturation_LowerSat;          /* Expression: -12
                                        * Referenced by: '<S1>/Saturation'
                                        */
  real_T Constant1_Value;              /* Expression: 0
                                        * Referenced by: '<S9>/Constant1'
                                        */
  real_T Constant3_Value;              /* Expression: 0
                                        * Referenced by: '<S9>/Constant3'
                                        */
  real_T Constant4_Value;              /* Expression: 4.85
                                        * Referenced by: '<S9>/Constant4'
                                        */
  int32_T Iterator_IterationLimit;/* Computed Parameter: Iterator_IterationLimit
                                   * Referenced by: '<S279>/Iterator'
                                   */
  real32_T X_est_Y0;                   /* Computed Parameter: X_est_Y0
                                        * Referenced by: '<S279>/X_est'
                                        */
  real32_T X_prd_Y0;                   /* Computed Parameter: X_prd_Y0
                                        * Referenced by: '<S279>/X_prd'
                                        */
  real32_T P_prd_Y0;                   /* Computed Parameter: P_prd_Y0
                                        * Referenced by: '<S279>/P_prd'
                                        */
  real32_T Constant3_Value_a[16];      /* Computed Parameter: Constant3_Value_a
                                        * Referenced by: '<S281>/Constant3'
                                        */
  real32_T Hcst_Value[8];              /* Computed Parameter: Hcst_Value
                                        * Referenced by: '<S281>/Hcst'
                                        */
  real32_T Hcst_t_Value[8];            /* Computed Parameter: Hcst_t_Value
                                        * Referenced by: '<S281>/Hcst_t'
                                        */
  real32_T Constant2_Value_k[4];       /* Computed Parameter: Constant2_Value_k
                                        * Referenced by: '<S281>/Constant2'
                                        */
  real32_T Constant4_Value_j[16];      /* Computed Parameter: Constant4_Value_j
                                        * Referenced by: '<S281>/Constant4'
                                        */
  real32_T Constant5_Value[16];        /* Computed Parameter: Constant5_Value
                                        * Referenced by: '<S281>/Constant5'
                                        */
  real32_T UnitDelay2_InitialCondition[4];
                              /* Computed Parameter: UnitDelay2_InitialCondition
                               * Referenced by: '<S277>/Unit Delay2'
                               */
  real32_T UnitDelay3_InitialCondition[16];
                              /* Computed Parameter: UnitDelay3_InitialCondition
                               * Referenced by: '<S277>/Unit Delay3'
                               */
};

/* Real-time Model Data Structure */
struct tag_RTM_Controller_P7_T {
  const char_T *errorStatus;
  RTWLogInfo *rtwLogInfo;

  /*
   * Timing:
   * The following substructure contains information regarding
   * the timing information for the model.
   */
  struct {
    time_T taskTime0;
    uint32_T clockTick0;
    uint32_T clockTickH0;
    time_T stepSize0;
    time_T tFinal;
    boolean_T stopRequestedFlag;
  } Timing;
};

/* Block parameters (default storage) */
extern P_Controller_P7_T Controller_P7_P;

/* Block signals (default storage) */
extern B_Controller_P7_T Controller_P7_B;

/* Block states (default storage) */
extern DW_Controller_P7_T Controller_P7_DW;

/* External inputs (root inport signals with default storage) */
extern ExtU_Controller_P7_T Controller_P7_U;

/* External outputs (root outports fed by signals with default storage) */
extern ExtY_Controller_P7_T Controller_P7_Y;

/* Model entry point functions */
extern void Controller_P7_initialize(void);
extern void Controller_P7_step(void);
extern void Controller_P7_terminate(void);

/* Real-time Model object */
extern RT_MODEL_Controller_P7_T *const Controller_P7_M;

/*-
 * These blocks were eliminated from the model due to optimizations:
 *
 * Block '<S278>/Check Signal Attributes' : Unused code path elimination
 * Block '<S286>/Check Signal Attributes' : Unused code path elimination
 * Block '<S287>/Check Signal Attributes' : Unused code path elimination
 * Block '<S288>/Check Signal Attributes' : Unused code path elimination
 * Block '<S1>/Reshape' : Reshape block reduction
 * Block '<S281>/P_Reshape' : Reshape block reduction
 * Block '<S281>/P_prd_Reshape' : Reshape block reduction
 * Block '<S2>/Reshape' : Reshape block reduction
 */

/*-
 * The generated code includes comments that allow you to trace directly
 * back to the appropriate location in the model.  The basic format
 * is <system>/block_name, where system is the system number (uniquely
 * assigned by Simulink) and block_name is the name of the block.
 *
 * Use the MATLAB hilite_system command to trace the generated code back
 * to the model.  For example,
 *
 * hilite_system('<S3>')    - opens system 3
 * hilite_system('<S3>/Kp') - opens and selects block Kp which resides in S3
 *
 * Here is the system hierarchy for this model
 *
 * '<Root>' : 'Controller_P7'
 * '<S1>'   : 'Controller_P7/Controller'
 * '<S2>'   : 'Controller_P7/Filter'
 * '<S3>'   : 'Controller_P7/Controller/BreakCheck'
 * '<S4>'   : 'Controller_P7/Controller/Chart'
 * '<S5>'   : 'Controller_P7/Controller/Engine Off'
 * '<S6>'   : 'Controller_P7/Controller/GR HI'
 * '<S7>'   : 'Controller_P7/Controller/GR LO'
 * '<S8>'   : 'Controller_P7/Controller/Idle'
 * '<S9>'   : 'Controller_P7/Controller/Limit Check'
 * '<S10>'  : 'Controller_P7/Controller/Omega HI'
 * '<S11>'  : 'Controller_P7/Controller/Omega LO'
 * '<S12>'  : 'Controller_P7/Controller/GR HI/PID Controller'
 * '<S13>'  : 'Controller_P7/Controller/GR HI/PID Controller/Anti-windup'
 * '<S14>'  : 'Controller_P7/Controller/GR HI/PID Controller/D Gain'
 * '<S15>'  : 'Controller_P7/Controller/GR HI/PID Controller/External Derivative'
 * '<S16>'  : 'Controller_P7/Controller/GR HI/PID Controller/Filter'
 * '<S17>'  : 'Controller_P7/Controller/GR HI/PID Controller/Filter ICs'
 * '<S18>'  : 'Controller_P7/Controller/GR HI/PID Controller/I Gain'
 * '<S19>'  : 'Controller_P7/Controller/GR HI/PID Controller/Ideal P Gain'
 * '<S20>'  : 'Controller_P7/Controller/GR HI/PID Controller/Ideal P Gain Fdbk'
 * '<S21>'  : 'Controller_P7/Controller/GR HI/PID Controller/Integrator'
 * '<S22>'  : 'Controller_P7/Controller/GR HI/PID Controller/Integrator ICs'
 * '<S23>'  : 'Controller_P7/Controller/GR HI/PID Controller/N Copy'
 * '<S24>'  : 'Controller_P7/Controller/GR HI/PID Controller/N Gain'
 * '<S25>'  : 'Controller_P7/Controller/GR HI/PID Controller/P Copy'
 * '<S26>'  : 'Controller_P7/Controller/GR HI/PID Controller/Parallel P Gain'
 * '<S27>'  : 'Controller_P7/Controller/GR HI/PID Controller/Reset Signal'
 * '<S28>'  : 'Controller_P7/Controller/GR HI/PID Controller/Saturation'
 * '<S29>'  : 'Controller_P7/Controller/GR HI/PID Controller/Saturation Fdbk'
 * '<S30>'  : 'Controller_P7/Controller/GR HI/PID Controller/Sum'
 * '<S31>'  : 'Controller_P7/Controller/GR HI/PID Controller/Sum Fdbk'
 * '<S32>'  : 'Controller_P7/Controller/GR HI/PID Controller/Tracking Mode'
 * '<S33>'  : 'Controller_P7/Controller/GR HI/PID Controller/Tracking Mode Sum'
 * '<S34>'  : 'Controller_P7/Controller/GR HI/PID Controller/Tsamp - Integral'
 * '<S35>'  : 'Controller_P7/Controller/GR HI/PID Controller/Tsamp - Ngain'
 * '<S36>'  : 'Controller_P7/Controller/GR HI/PID Controller/postSat Signal'
 * '<S37>'  : 'Controller_P7/Controller/GR HI/PID Controller/preInt Signal'
 * '<S38>'  : 'Controller_P7/Controller/GR HI/PID Controller/preSat Signal'
 * '<S39>'  : 'Controller_P7/Controller/GR HI/PID Controller/Anti-windup/Passthrough'
 * '<S40>'  : 'Controller_P7/Controller/GR HI/PID Controller/D Gain/Internal Parameters'
 * '<S41>'  : 'Controller_P7/Controller/GR HI/PID Controller/External Derivative/Error'
 * '<S42>'  : 'Controller_P7/Controller/GR HI/PID Controller/Filter/Disc. Forward Euler Filter'
 * '<S43>'  : 'Controller_P7/Controller/GR HI/PID Controller/Filter ICs/Internal IC - Filter'
 * '<S44>'  : 'Controller_P7/Controller/GR HI/PID Controller/I Gain/Internal Parameters'
 * '<S45>'  : 'Controller_P7/Controller/GR HI/PID Controller/Ideal P Gain/Passthrough'
 * '<S46>'  : 'Controller_P7/Controller/GR HI/PID Controller/Ideal P Gain Fdbk/Disabled'
 * '<S47>'  : 'Controller_P7/Controller/GR HI/PID Controller/Integrator/Discrete'
 * '<S48>'  : 'Controller_P7/Controller/GR HI/PID Controller/Integrator ICs/Internal IC'
 * '<S49>'  : 'Controller_P7/Controller/GR HI/PID Controller/N Copy/Disabled'
 * '<S50>'  : 'Controller_P7/Controller/GR HI/PID Controller/N Gain/Internal Parameters'
 * '<S51>'  : 'Controller_P7/Controller/GR HI/PID Controller/P Copy/Disabled'
 * '<S52>'  : 'Controller_P7/Controller/GR HI/PID Controller/Parallel P Gain/Internal Parameters'
 * '<S53>'  : 'Controller_P7/Controller/GR HI/PID Controller/Reset Signal/Disabled'
 * '<S54>'  : 'Controller_P7/Controller/GR HI/PID Controller/Saturation/Passthrough'
 * '<S55>'  : 'Controller_P7/Controller/GR HI/PID Controller/Saturation Fdbk/Disabled'
 * '<S56>'  : 'Controller_P7/Controller/GR HI/PID Controller/Sum/Sum_PID'
 * '<S57>'  : 'Controller_P7/Controller/GR HI/PID Controller/Sum Fdbk/Disabled'
 * '<S58>'  : 'Controller_P7/Controller/GR HI/PID Controller/Tracking Mode/Disabled'
 * '<S59>'  : 'Controller_P7/Controller/GR HI/PID Controller/Tracking Mode Sum/Passthrough'
 * '<S60>'  : 'Controller_P7/Controller/GR HI/PID Controller/Tsamp - Integral/TsSignalSpecification'
 * '<S61>'  : 'Controller_P7/Controller/GR HI/PID Controller/Tsamp - Ngain/Passthrough'
 * '<S62>'  : 'Controller_P7/Controller/GR HI/PID Controller/postSat Signal/Forward_Path'
 * '<S63>'  : 'Controller_P7/Controller/GR HI/PID Controller/preInt Signal/Internal PreInt'
 * '<S64>'  : 'Controller_P7/Controller/GR HI/PID Controller/preSat Signal/Forward_Path'
 * '<S65>'  : 'Controller_P7/Controller/GR LO/PID Controller'
 * '<S66>'  : 'Controller_P7/Controller/GR LO/PID Controller/Anti-windup'
 * '<S67>'  : 'Controller_P7/Controller/GR LO/PID Controller/D Gain'
 * '<S68>'  : 'Controller_P7/Controller/GR LO/PID Controller/External Derivative'
 * '<S69>'  : 'Controller_P7/Controller/GR LO/PID Controller/Filter'
 * '<S70>'  : 'Controller_P7/Controller/GR LO/PID Controller/Filter ICs'
 * '<S71>'  : 'Controller_P7/Controller/GR LO/PID Controller/I Gain'
 * '<S72>'  : 'Controller_P7/Controller/GR LO/PID Controller/Ideal P Gain'
 * '<S73>'  : 'Controller_P7/Controller/GR LO/PID Controller/Ideal P Gain Fdbk'
 * '<S74>'  : 'Controller_P7/Controller/GR LO/PID Controller/Integrator'
 * '<S75>'  : 'Controller_P7/Controller/GR LO/PID Controller/Integrator ICs'
 * '<S76>'  : 'Controller_P7/Controller/GR LO/PID Controller/N Copy'
 * '<S77>'  : 'Controller_P7/Controller/GR LO/PID Controller/N Gain'
 * '<S78>'  : 'Controller_P7/Controller/GR LO/PID Controller/P Copy'
 * '<S79>'  : 'Controller_P7/Controller/GR LO/PID Controller/Parallel P Gain'
 * '<S80>'  : 'Controller_P7/Controller/GR LO/PID Controller/Reset Signal'
 * '<S81>'  : 'Controller_P7/Controller/GR LO/PID Controller/Saturation'
 * '<S82>'  : 'Controller_P7/Controller/GR LO/PID Controller/Saturation Fdbk'
 * '<S83>'  : 'Controller_P7/Controller/GR LO/PID Controller/Sum'
 * '<S84>'  : 'Controller_P7/Controller/GR LO/PID Controller/Sum Fdbk'
 * '<S85>'  : 'Controller_P7/Controller/GR LO/PID Controller/Tracking Mode'
 * '<S86>'  : 'Controller_P7/Controller/GR LO/PID Controller/Tracking Mode Sum'
 * '<S87>'  : 'Controller_P7/Controller/GR LO/PID Controller/Tsamp - Integral'
 * '<S88>'  : 'Controller_P7/Controller/GR LO/PID Controller/Tsamp - Ngain'
 * '<S89>'  : 'Controller_P7/Controller/GR LO/PID Controller/postSat Signal'
 * '<S90>'  : 'Controller_P7/Controller/GR LO/PID Controller/preInt Signal'
 * '<S91>'  : 'Controller_P7/Controller/GR LO/PID Controller/preSat Signal'
 * '<S92>'  : 'Controller_P7/Controller/GR LO/PID Controller/Anti-windup/Passthrough'
 * '<S93>'  : 'Controller_P7/Controller/GR LO/PID Controller/D Gain/Internal Parameters'
 * '<S94>'  : 'Controller_P7/Controller/GR LO/PID Controller/External Derivative/Error'
 * '<S95>'  : 'Controller_P7/Controller/GR LO/PID Controller/Filter/Disc. Forward Euler Filter'
 * '<S96>'  : 'Controller_P7/Controller/GR LO/PID Controller/Filter ICs/Internal IC - Filter'
 * '<S97>'  : 'Controller_P7/Controller/GR LO/PID Controller/I Gain/Internal Parameters'
 * '<S98>'  : 'Controller_P7/Controller/GR LO/PID Controller/Ideal P Gain/Passthrough'
 * '<S99>'  : 'Controller_P7/Controller/GR LO/PID Controller/Ideal P Gain Fdbk/Disabled'
 * '<S100>' : 'Controller_P7/Controller/GR LO/PID Controller/Integrator/Discrete'
 * '<S101>' : 'Controller_P7/Controller/GR LO/PID Controller/Integrator ICs/Internal IC'
 * '<S102>' : 'Controller_P7/Controller/GR LO/PID Controller/N Copy/Disabled'
 * '<S103>' : 'Controller_P7/Controller/GR LO/PID Controller/N Gain/Internal Parameters'
 * '<S104>' : 'Controller_P7/Controller/GR LO/PID Controller/P Copy/Disabled'
 * '<S105>' : 'Controller_P7/Controller/GR LO/PID Controller/Parallel P Gain/Internal Parameters'
 * '<S106>' : 'Controller_P7/Controller/GR LO/PID Controller/Reset Signal/Disabled'
 * '<S107>' : 'Controller_P7/Controller/GR LO/PID Controller/Saturation/Passthrough'
 * '<S108>' : 'Controller_P7/Controller/GR LO/PID Controller/Saturation Fdbk/Disabled'
 * '<S109>' : 'Controller_P7/Controller/GR LO/PID Controller/Sum/Sum_PID'
 * '<S110>' : 'Controller_P7/Controller/GR LO/PID Controller/Sum Fdbk/Disabled'
 * '<S111>' : 'Controller_P7/Controller/GR LO/PID Controller/Tracking Mode/Disabled'
 * '<S112>' : 'Controller_P7/Controller/GR LO/PID Controller/Tracking Mode Sum/Passthrough'
 * '<S113>' : 'Controller_P7/Controller/GR LO/PID Controller/Tsamp - Integral/TsSignalSpecification'
 * '<S114>' : 'Controller_P7/Controller/GR LO/PID Controller/Tsamp - Ngain/Passthrough'
 * '<S115>' : 'Controller_P7/Controller/GR LO/PID Controller/postSat Signal/Forward_Path'
 * '<S116>' : 'Controller_P7/Controller/GR LO/PID Controller/preInt Signal/Internal PreInt'
 * '<S117>' : 'Controller_P7/Controller/GR LO/PID Controller/preSat Signal/Forward_Path'
 * '<S118>' : 'Controller_P7/Controller/Idle/PID Controller'
 * '<S119>' : 'Controller_P7/Controller/Idle/PID Controller/Anti-windup'
 * '<S120>' : 'Controller_P7/Controller/Idle/PID Controller/D Gain'
 * '<S121>' : 'Controller_P7/Controller/Idle/PID Controller/External Derivative'
 * '<S122>' : 'Controller_P7/Controller/Idle/PID Controller/Filter'
 * '<S123>' : 'Controller_P7/Controller/Idle/PID Controller/Filter ICs'
 * '<S124>' : 'Controller_P7/Controller/Idle/PID Controller/I Gain'
 * '<S125>' : 'Controller_P7/Controller/Idle/PID Controller/Ideal P Gain'
 * '<S126>' : 'Controller_P7/Controller/Idle/PID Controller/Ideal P Gain Fdbk'
 * '<S127>' : 'Controller_P7/Controller/Idle/PID Controller/Integrator'
 * '<S128>' : 'Controller_P7/Controller/Idle/PID Controller/Integrator ICs'
 * '<S129>' : 'Controller_P7/Controller/Idle/PID Controller/N Copy'
 * '<S130>' : 'Controller_P7/Controller/Idle/PID Controller/N Gain'
 * '<S131>' : 'Controller_P7/Controller/Idle/PID Controller/P Copy'
 * '<S132>' : 'Controller_P7/Controller/Idle/PID Controller/Parallel P Gain'
 * '<S133>' : 'Controller_P7/Controller/Idle/PID Controller/Reset Signal'
 * '<S134>' : 'Controller_P7/Controller/Idle/PID Controller/Saturation'
 * '<S135>' : 'Controller_P7/Controller/Idle/PID Controller/Saturation Fdbk'
 * '<S136>' : 'Controller_P7/Controller/Idle/PID Controller/Sum'
 * '<S137>' : 'Controller_P7/Controller/Idle/PID Controller/Sum Fdbk'
 * '<S138>' : 'Controller_P7/Controller/Idle/PID Controller/Tracking Mode'
 * '<S139>' : 'Controller_P7/Controller/Idle/PID Controller/Tracking Mode Sum'
 * '<S140>' : 'Controller_P7/Controller/Idle/PID Controller/Tsamp - Integral'
 * '<S141>' : 'Controller_P7/Controller/Idle/PID Controller/Tsamp - Ngain'
 * '<S142>' : 'Controller_P7/Controller/Idle/PID Controller/postSat Signal'
 * '<S143>' : 'Controller_P7/Controller/Idle/PID Controller/preInt Signal'
 * '<S144>' : 'Controller_P7/Controller/Idle/PID Controller/preSat Signal'
 * '<S145>' : 'Controller_P7/Controller/Idle/PID Controller/Anti-windup/Passthrough'
 * '<S146>' : 'Controller_P7/Controller/Idle/PID Controller/D Gain/Internal Parameters'
 * '<S147>' : 'Controller_P7/Controller/Idle/PID Controller/External Derivative/Error'
 * '<S148>' : 'Controller_P7/Controller/Idle/PID Controller/Filter/Disc. Forward Euler Filter'
 * '<S149>' : 'Controller_P7/Controller/Idle/PID Controller/Filter ICs/Internal IC - Filter'
 * '<S150>' : 'Controller_P7/Controller/Idle/PID Controller/I Gain/Internal Parameters'
 * '<S151>' : 'Controller_P7/Controller/Idle/PID Controller/Ideal P Gain/Passthrough'
 * '<S152>' : 'Controller_P7/Controller/Idle/PID Controller/Ideal P Gain Fdbk/Disabled'
 * '<S153>' : 'Controller_P7/Controller/Idle/PID Controller/Integrator/Discrete'
 * '<S154>' : 'Controller_P7/Controller/Idle/PID Controller/Integrator ICs/Internal IC'
 * '<S155>' : 'Controller_P7/Controller/Idle/PID Controller/N Copy/Disabled'
 * '<S156>' : 'Controller_P7/Controller/Idle/PID Controller/N Gain/Internal Parameters'
 * '<S157>' : 'Controller_P7/Controller/Idle/PID Controller/P Copy/Disabled'
 * '<S158>' : 'Controller_P7/Controller/Idle/PID Controller/Parallel P Gain/Internal Parameters'
 * '<S159>' : 'Controller_P7/Controller/Idle/PID Controller/Reset Signal/Disabled'
 * '<S160>' : 'Controller_P7/Controller/Idle/PID Controller/Saturation/Passthrough'
 * '<S161>' : 'Controller_P7/Controller/Idle/PID Controller/Saturation Fdbk/Disabled'
 * '<S162>' : 'Controller_P7/Controller/Idle/PID Controller/Sum/Sum_PID'
 * '<S163>' : 'Controller_P7/Controller/Idle/PID Controller/Sum Fdbk/Disabled'
 * '<S164>' : 'Controller_P7/Controller/Idle/PID Controller/Tracking Mode/Disabled'
 * '<S165>' : 'Controller_P7/Controller/Idle/PID Controller/Tracking Mode Sum/Passthrough'
 * '<S166>' : 'Controller_P7/Controller/Idle/PID Controller/Tsamp - Integral/TsSignalSpecification'
 * '<S167>' : 'Controller_P7/Controller/Idle/PID Controller/Tsamp - Ngain/Passthrough'
 * '<S168>' : 'Controller_P7/Controller/Idle/PID Controller/postSat Signal/Forward_Path'
 * '<S169>' : 'Controller_P7/Controller/Idle/PID Controller/preInt Signal/Internal PreInt'
 * '<S170>' : 'Controller_P7/Controller/Idle/PID Controller/preSat Signal/Forward_Path'
 * '<S171>' : 'Controller_P7/Controller/Omega HI/PID Controller'
 * '<S172>' : 'Controller_P7/Controller/Omega HI/PID Controller/Anti-windup'
 * '<S173>' : 'Controller_P7/Controller/Omega HI/PID Controller/D Gain'
 * '<S174>' : 'Controller_P7/Controller/Omega HI/PID Controller/External Derivative'
 * '<S175>' : 'Controller_P7/Controller/Omega HI/PID Controller/Filter'
 * '<S176>' : 'Controller_P7/Controller/Omega HI/PID Controller/Filter ICs'
 * '<S177>' : 'Controller_P7/Controller/Omega HI/PID Controller/I Gain'
 * '<S178>' : 'Controller_P7/Controller/Omega HI/PID Controller/Ideal P Gain'
 * '<S179>' : 'Controller_P7/Controller/Omega HI/PID Controller/Ideal P Gain Fdbk'
 * '<S180>' : 'Controller_P7/Controller/Omega HI/PID Controller/Integrator'
 * '<S181>' : 'Controller_P7/Controller/Omega HI/PID Controller/Integrator ICs'
 * '<S182>' : 'Controller_P7/Controller/Omega HI/PID Controller/N Copy'
 * '<S183>' : 'Controller_P7/Controller/Omega HI/PID Controller/N Gain'
 * '<S184>' : 'Controller_P7/Controller/Omega HI/PID Controller/P Copy'
 * '<S185>' : 'Controller_P7/Controller/Omega HI/PID Controller/Parallel P Gain'
 * '<S186>' : 'Controller_P7/Controller/Omega HI/PID Controller/Reset Signal'
 * '<S187>' : 'Controller_P7/Controller/Omega HI/PID Controller/Saturation'
 * '<S188>' : 'Controller_P7/Controller/Omega HI/PID Controller/Saturation Fdbk'
 * '<S189>' : 'Controller_P7/Controller/Omega HI/PID Controller/Sum'
 * '<S190>' : 'Controller_P7/Controller/Omega HI/PID Controller/Sum Fdbk'
 * '<S191>' : 'Controller_P7/Controller/Omega HI/PID Controller/Tracking Mode'
 * '<S192>' : 'Controller_P7/Controller/Omega HI/PID Controller/Tracking Mode Sum'
 * '<S193>' : 'Controller_P7/Controller/Omega HI/PID Controller/Tsamp - Integral'
 * '<S194>' : 'Controller_P7/Controller/Omega HI/PID Controller/Tsamp - Ngain'
 * '<S195>' : 'Controller_P7/Controller/Omega HI/PID Controller/postSat Signal'
 * '<S196>' : 'Controller_P7/Controller/Omega HI/PID Controller/preInt Signal'
 * '<S197>' : 'Controller_P7/Controller/Omega HI/PID Controller/preSat Signal'
 * '<S198>' : 'Controller_P7/Controller/Omega HI/PID Controller/Anti-windup/Passthrough'
 * '<S199>' : 'Controller_P7/Controller/Omega HI/PID Controller/D Gain/Internal Parameters'
 * '<S200>' : 'Controller_P7/Controller/Omega HI/PID Controller/External Derivative/External Ydot'
 * '<S201>' : 'Controller_P7/Controller/Omega HI/PID Controller/Filter/Disc. Forward Euler Filter Only'
 * '<S202>' : 'Controller_P7/Controller/Omega HI/PID Controller/Filter ICs/Internal IC - Filter'
 * '<S203>' : 'Controller_P7/Controller/Omega HI/PID Controller/I Gain/Internal Parameters'
 * '<S204>' : 'Controller_P7/Controller/Omega HI/PID Controller/Ideal P Gain/Passthrough'
 * '<S205>' : 'Controller_P7/Controller/Omega HI/PID Controller/Ideal P Gain Fdbk/Disabled'
 * '<S206>' : 'Controller_P7/Controller/Omega HI/PID Controller/Integrator/Discrete'
 * '<S207>' : 'Controller_P7/Controller/Omega HI/PID Controller/Integrator ICs/Internal IC'
 * '<S208>' : 'Controller_P7/Controller/Omega HI/PID Controller/N Copy/Disabled'
 * '<S209>' : 'Controller_P7/Controller/Omega HI/PID Controller/N Gain/Internal Parameters'
 * '<S210>' : 'Controller_P7/Controller/Omega HI/PID Controller/P Copy/Disabled'
 * '<S211>' : 'Controller_P7/Controller/Omega HI/PID Controller/Parallel P Gain/Internal Parameters'
 * '<S212>' : 'Controller_P7/Controller/Omega HI/PID Controller/Reset Signal/Disabled'
 * '<S213>' : 'Controller_P7/Controller/Omega HI/PID Controller/Saturation/Passthrough'
 * '<S214>' : 'Controller_P7/Controller/Omega HI/PID Controller/Saturation Fdbk/Disabled'
 * '<S215>' : 'Controller_P7/Controller/Omega HI/PID Controller/Sum/Sum_PID'
 * '<S216>' : 'Controller_P7/Controller/Omega HI/PID Controller/Sum Fdbk/Disabled'
 * '<S217>' : 'Controller_P7/Controller/Omega HI/PID Controller/Tracking Mode/Disabled'
 * '<S218>' : 'Controller_P7/Controller/Omega HI/PID Controller/Tracking Mode Sum/Passthrough'
 * '<S219>' : 'Controller_P7/Controller/Omega HI/PID Controller/Tsamp - Integral/TsSignalSpecification'
 * '<S220>' : 'Controller_P7/Controller/Omega HI/PID Controller/Tsamp - Ngain/Passthrough'
 * '<S221>' : 'Controller_P7/Controller/Omega HI/PID Controller/postSat Signal/Forward_Path'
 * '<S222>' : 'Controller_P7/Controller/Omega HI/PID Controller/preInt Signal/Internal PreInt'
 * '<S223>' : 'Controller_P7/Controller/Omega HI/PID Controller/preSat Signal/Forward_Path'
 * '<S224>' : 'Controller_P7/Controller/Omega LO/PID Controller'
 * '<S225>' : 'Controller_P7/Controller/Omega LO/PID Controller/Anti-windup'
 * '<S226>' : 'Controller_P7/Controller/Omega LO/PID Controller/D Gain'
 * '<S227>' : 'Controller_P7/Controller/Omega LO/PID Controller/External Derivative'
 * '<S228>' : 'Controller_P7/Controller/Omega LO/PID Controller/Filter'
 * '<S229>' : 'Controller_P7/Controller/Omega LO/PID Controller/Filter ICs'
 * '<S230>' : 'Controller_P7/Controller/Omega LO/PID Controller/I Gain'
 * '<S231>' : 'Controller_P7/Controller/Omega LO/PID Controller/Ideal P Gain'
 * '<S232>' : 'Controller_P7/Controller/Omega LO/PID Controller/Ideal P Gain Fdbk'
 * '<S233>' : 'Controller_P7/Controller/Omega LO/PID Controller/Integrator'
 * '<S234>' : 'Controller_P7/Controller/Omega LO/PID Controller/Integrator ICs'
 * '<S235>' : 'Controller_P7/Controller/Omega LO/PID Controller/N Copy'
 * '<S236>' : 'Controller_P7/Controller/Omega LO/PID Controller/N Gain'
 * '<S237>' : 'Controller_P7/Controller/Omega LO/PID Controller/P Copy'
 * '<S238>' : 'Controller_P7/Controller/Omega LO/PID Controller/Parallel P Gain'
 * '<S239>' : 'Controller_P7/Controller/Omega LO/PID Controller/Reset Signal'
 * '<S240>' : 'Controller_P7/Controller/Omega LO/PID Controller/Saturation'
 * '<S241>' : 'Controller_P7/Controller/Omega LO/PID Controller/Saturation Fdbk'
 * '<S242>' : 'Controller_P7/Controller/Omega LO/PID Controller/Sum'
 * '<S243>' : 'Controller_P7/Controller/Omega LO/PID Controller/Sum Fdbk'
 * '<S244>' : 'Controller_P7/Controller/Omega LO/PID Controller/Tracking Mode'
 * '<S245>' : 'Controller_P7/Controller/Omega LO/PID Controller/Tracking Mode Sum'
 * '<S246>' : 'Controller_P7/Controller/Omega LO/PID Controller/Tsamp - Integral'
 * '<S247>' : 'Controller_P7/Controller/Omega LO/PID Controller/Tsamp - Ngain'
 * '<S248>' : 'Controller_P7/Controller/Omega LO/PID Controller/postSat Signal'
 * '<S249>' : 'Controller_P7/Controller/Omega LO/PID Controller/preInt Signal'
 * '<S250>' : 'Controller_P7/Controller/Omega LO/PID Controller/preSat Signal'
 * '<S251>' : 'Controller_P7/Controller/Omega LO/PID Controller/Anti-windup/Passthrough'
 * '<S252>' : 'Controller_P7/Controller/Omega LO/PID Controller/D Gain/Internal Parameters'
 * '<S253>' : 'Controller_P7/Controller/Omega LO/PID Controller/External Derivative/External Ydot'
 * '<S254>' : 'Controller_P7/Controller/Omega LO/PID Controller/Filter/Disc. Forward Euler Filter Only'
 * '<S255>' : 'Controller_P7/Controller/Omega LO/PID Controller/Filter ICs/Internal IC - Filter'
 * '<S256>' : 'Controller_P7/Controller/Omega LO/PID Controller/I Gain/Internal Parameters'
 * '<S257>' : 'Controller_P7/Controller/Omega LO/PID Controller/Ideal P Gain/Passthrough'
 * '<S258>' : 'Controller_P7/Controller/Omega LO/PID Controller/Ideal P Gain Fdbk/Disabled'
 * '<S259>' : 'Controller_P7/Controller/Omega LO/PID Controller/Integrator/Discrete'
 * '<S260>' : 'Controller_P7/Controller/Omega LO/PID Controller/Integrator ICs/Internal IC'
 * '<S261>' : 'Controller_P7/Controller/Omega LO/PID Controller/N Copy/Disabled'
 * '<S262>' : 'Controller_P7/Controller/Omega LO/PID Controller/N Gain/Internal Parameters'
 * '<S263>' : 'Controller_P7/Controller/Omega LO/PID Controller/P Copy/Disabled'
 * '<S264>' : 'Controller_P7/Controller/Omega LO/PID Controller/Parallel P Gain/Internal Parameters'
 * '<S265>' : 'Controller_P7/Controller/Omega LO/PID Controller/Reset Signal/Disabled'
 * '<S266>' : 'Controller_P7/Controller/Omega LO/PID Controller/Saturation/Passthrough'
 * '<S267>' : 'Controller_P7/Controller/Omega LO/PID Controller/Saturation Fdbk/Disabled'
 * '<S268>' : 'Controller_P7/Controller/Omega LO/PID Controller/Sum/Sum_PID'
 * '<S269>' : 'Controller_P7/Controller/Omega LO/PID Controller/Sum Fdbk/Disabled'
 * '<S270>' : 'Controller_P7/Controller/Omega LO/PID Controller/Tracking Mode/Disabled'
 * '<S271>' : 'Controller_P7/Controller/Omega LO/PID Controller/Tracking Mode Sum/Passthrough'
 * '<S272>' : 'Controller_P7/Controller/Omega LO/PID Controller/Tsamp - Integral/TsSignalSpecification'
 * '<S273>' : 'Controller_P7/Controller/Omega LO/PID Controller/Tsamp - Ngain/Passthrough'
 * '<S274>' : 'Controller_P7/Controller/Omega LO/PID Controller/postSat Signal/Forward_Path'
 * '<S275>' : 'Controller_P7/Controller/Omega LO/PID Controller/preInt Signal/Internal PreInt'
 * '<S276>' : 'Controller_P7/Controller/Omega LO/PID Controller/preSat Signal/Forward_Path'
 * '<S277>' : 'Controller_P7/Filter/Kalman Filter'
 * '<S278>' : 'Controller_P7/Filter/Kalman Filter/Check Signal Attributes'
 * '<S279>' : 'Controller_P7/Filter/Kalman Filter/Control'
 * '<S280>' : 'Controller_P7/Filter/Kalman Filter/Control/Options'
 * '<S281>' : 'Controller_P7/Filter/Kalman Filter/Control/Options/Core'
 * '<S282>' : 'Controller_P7/Filter/Kalman Filter/Control/Options/P_prd_Assign'
 * '<S283>' : 'Controller_P7/Filter/Kalman Filter/Control/Options/X_est_Assign'
 * '<S284>' : 'Controller_P7/Filter/Kalman Filter/Control/Options/X_prd_Assign'
 * '<S285>' : 'Controller_P7/Filter/Kalman Filter/Control/Options/Core/LDL Solver'
 * '<S286>' : 'Controller_P7/Filter/Kalman Filter/Control/Options/Core/LDL Solver/Check Signal Attributes'
 * '<S287>' : 'Controller_P7/Filter/Kalman Filter/Control/Options/Core/LDL Solver/Check Signal Attributes1'
 * '<S288>' : 'Controller_P7/Filter/Kalman Filter/Control/Options/Core/LDL Solver/Check Signal Attributes2'
 */
#endif                                 /* Controller_P7_h_ */
