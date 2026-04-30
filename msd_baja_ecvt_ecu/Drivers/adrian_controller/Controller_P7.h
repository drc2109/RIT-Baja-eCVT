/*
 * Controller_P7.h
 *
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * Code generation for model "Controller_P7".
 *
 * Model version              : 5.19
 * Simulink Coder version : 25.2 (R2025b) 28-Jul-2025
 * C source code generated on : Fri Apr 24 22:16:54 2026
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
  real_T Saturation1;                  /* '<S1>/Saturation1' */
  real_T Add;                          /* '<S7>/Add' */
  real_T Filter;                       /* '<S197>/Filter' */
  real_T FilterCoefficient;            /* '<S205>/Filter Coefficient' */
  real_T SumD;                         /* '<S197>/SumD' */
  real_T IntegralGain;                 /* '<S199>/Integral Gain' */
  real_T Integrator;                   /* '<S202>/Integrator' */
  real_T ProportionalGain;             /* '<S207>/Proportional Gain' */
  real_T Add_m;                        /* '<S4>/Add' */
  real_T DerivativeGain;               /* '<S89>/Derivative Gain' */
  real_T Filter_l;                     /* '<S91>/Filter' */
  real_T SumD_d;                       /* '<S91>/SumD' */
  real_T IntegralGain_b;               /* '<S93>/Integral Gain' */
  real_T Integrator_o;                 /* '<S96>/Integrator' */
  real_T FilterCoefficient_i;          /* '<S99>/Filter Coefficient' */
  real_T ProportionalGain_k;           /* '<S101>/Proportional Gain' */
  real_T Add_h;                        /* '<S6>/Add' */
  real_T Filter_j;                     /* '<S144>/Filter' */
  real_T FilterCoefficient_a;          /* '<S152>/Filter Coefficient' */
  real_T SumD_o;                       /* '<S144>/SumD' */
  real_T IntegralGain_a;               /* '<S146>/Integral Gain' */
  real_T Integrator_j;                 /* '<S149>/Integrator' */
  real_T ProportionalGain_l;           /* '<S154>/Proportional Gain' */
  real_T Add_j;                        /* '<S3>/Add' */
  real_T DerivativeGain_a;             /* '<S36>/Derivative Gain' */
  real_T Filter_i;                     /* '<S38>/Filter' */
  real_T SumD_a;                       /* '<S38>/SumD' */
  real_T IntegralGain_d;               /* '<S40>/Integral Gain' */
  real_T Integrator_a;                 /* '<S43>/Integrator' */
  real_T FilterCoefficient_b;          /* '<S46>/Filter Coefficient' */
  real_T ProportionalGain_h;           /* '<S48>/Proportional Gain' */
  real32_T UnitDelay2[4];              /* '<S220>/Unit Delay2' */
  real32_T UnitDelay3[16];             /* '<S220>/Unit Delay3' */
  real32_T Multiply;                   /* '<S2>/Multiply' */
  real32_T SheaveDisplacementin;       /* '<S2>/1-D Lookup Table1' */
  real32_T phi1;                       /* '<S2>/1-D Lookup Table' */
  real32_T Phi2;                       /* '<S2>/Divide' */
  real32_T UnitDelay2_o[2];            /* '<S221>/Unit Delay2' */
  real32_T UnitDelay3_c[4];            /* '<S221>/Unit Delay3' */
  real32_T Selector2[4];               /* '<S235>/Selector2' */
  real32_T P_prdTrans[4];              /* '<S236>/P_prd Trans' */
  real32_T HP_prdt[4];                 /* '<S236>/H*P_prdt' */
  real32_T HP_prdtHt[4];               /* '<S236>/H*P_prdt*Ht' */
  real32_T HP_prdtHtR[4];              /* '<S236>/H*P_prdt*Ht+R' */
  real32_T LDLFactorization[4];        /* '<S240>/LDL Factorization' */
  real32_T y[4];                       /* '<S240>/Forward Substitution' */
  real32_T d[2];                       /* '<S240>/Extract Diagonal' */
  real32_T MathFunction[2];            /* '<S240>/Math Function' */
  real32_T MatrixScaling[4];           /* '<S240>/Matrix Scaling' */
  real32_T BackwardSubstitution[4];    /* '<S240>/Backward Substitution' */
  real32_T KTrans[4];                  /* '<S236>/K Trans' */
  real32_T KHP_prd[4];                 /* '<S236>/K*H*P_prd' */
  real32_T P_prdKHP_prd[4];            /* '<S236>/P_prd-K*H*P_prd' */
  real32_T APAt[4];                    /* '<S236>/A*P*At' */
  real32_T APAtQ[4];                   /* '<S236>/A*P*At+Q' */
  real32_T Selector1[2];               /* '<S235>/Selector1' */
  real32_T TmpSignalConversionAtSelectorIn[2];
  real32_T Selector[2];                /* '<S235>/Selector' */
  real32_T HX_prd[2];                  /* '<S236>/H*X_prd' */
  real32_T ZHX_prd[2];                 /* '<S236>/Z-H*X_prd' */
  real32_T KZHX_prd[2];                /* '<S236>/K*(Z-H*X_prd)' */
  real32_T X_prdKZHX_prd[2];           /* '<S236>/X_prd+K*(Z-H*X_prd)' */
  real32_T AX[2];                      /* '<S236>/A*X' */
  real32_T Assignment[4];              /* '<S237>/Assignment' */
  real32_T Assignment_j[2];            /* '<S238>/Assignment' */
  real32_T Assignment_m[2];            /* '<S239>/Assignment' */
  real32_T Selector2_j[16];            /* '<S224>/Selector2' */
  real32_T P_prdTrans_f[16];           /* '<S225>/P_prd Trans' */
  real32_T HP_prdt_p[8];               /* '<S225>/H*P_prdt' */
  real32_T HP_prdtHt_l[4];             /* '<S225>/H*P_prdt*Ht' */
  real32_T HP_prdtHtR_i[4];            /* '<S225>/H*P_prdt*Ht+R' */
  real32_T LDLFactorization_g[4];      /* '<S229>/LDL Factorization' */
  real32_T y_e[8];                     /* '<S229>/Forward Substitution' */
  real32_T d_e[2];                     /* '<S229>/Extract Diagonal' */
  real32_T MathFunction_l[2];          /* '<S229>/Math Function' */
  real32_T MatrixScaling_m[8];         /* '<S229>/Matrix Scaling' */
  real32_T BackwardSubstitution_d[8];  /* '<S229>/Backward Substitution' */
  real32_T KTrans_c[8];                /* '<S225>/K Trans' */
  real32_T KHP_prd_p[16];              /* '<S225>/K*H*P_prd' */
  real32_T P_prdKHP_prd_k[16];         /* '<S225>/P_prd-K*H*P_prd' */
  real32_T APAt_g[16];                 /* '<S225>/A*P*At' */
  real32_T APAtQ_h[16];                /* '<S225>/A*P*At+Q' */
  real32_T Selector1_b[4];             /* '<S224>/Selector1' */
  real32_T TmpSignalConversionAtSelector_l[2];
  real32_T Selector_f[2];              /* '<S224>/Selector' */
  real32_T HX_prd_b[2];                /* '<S225>/H*X_prd' */
  real32_T ZHX_prd_h[2];               /* '<S225>/Z-H*X_prd' */
  real32_T KZHX_prd_c[4];              /* '<S225>/K*(Z-H*X_prd)' */
  real32_T X_prdKZHX_prd_i[4];         /* '<S225>/X_prd+K*(Z-H*X_prd)' */
  real32_T AX_f[4];                    /* '<S225>/A*X' */
  real32_T Assignment_d[16];           /* '<S226>/Assignment' */
  real32_T Assignment_dh[4];           /* '<S227>/Assignment' */
  real32_T Assignment_g[4];            /* '<S228>/Assignment' */
  real32_T UnaryMinus;                 /* '<S196>/Unary Minus' */
  real32_T DerivativeGain_af;          /* '<S195>/Derivative Gain' */
  real32_T UnaryMinus_j;               /* '<S143>/Unary Minus' */
  real32_T DerivativeGain_n;           /* '<S142>/Derivative Gain' */
  int32_T Iterator;                    /* '<S234>/Iterator' */
  int32_T Iterator_i;                  /* '<S223>/Iterator' */
  boolean_T GreaterThan;               /* '<S5>/GreaterThan' */
  boolean_T LessThan;                  /* '<S5>/Less Than' */
  boolean_T AND;                       /* '<S5>/AND' */
  boolean_T GreaterThan1;              /* '<S5>/GreaterThan1' */
  boolean_T GreaterThan2;              /* '<S5>/GreaterThan2' */
  boolean_T AND1;                      /* '<S5>/AND1' */
  boolean_T OR;                        /* '<S5>/OR' */
} B_Controller_P7_T;

/* Block states (default storage) for system '<Root>' */
typedef struct {
  real_T Filter_DSTATE;                /* '<S197>/Filter' */
  real_T Integrator_DSTATE;            /* '<S202>/Integrator' */
  real_T Filter_DSTATE_d;              /* '<S91>/Filter' */
  real_T Integrator_DSTATE_l;          /* '<S96>/Integrator' */
  real_T Filter_DSTATE_i;              /* '<S144>/Filter' */
  real_T Integrator_DSTATE_j;          /* '<S149>/Integrator' */
  real_T Filter_DSTATE_dz;             /* '<S38>/Filter' */
  real_T Integrator_DSTATE_n;          /* '<S43>/Integrator' */
  real_T Add_DWORK1;                   /* '<S7>/Add' */
  real32_T UnitDelay2_DSTATE[4];       /* '<S220>/Unit Delay2' */
  real32_T UnitDelay3_DSTATE[16];      /* '<S220>/Unit Delay3' */
  real32_T UnitDelay2_DSTATE_b[2];     /* '<S221>/Unit Delay2' */
  real32_T UnitDelay3_DSTATE_f[4];     /* '<S221>/Unit Delay3' */
  real32_T LDLFactorization_VMX[2];    /* '<S240>/LDL Factorization' */
  real32_T LDLFactorization_VMX_a[2];  /* '<S229>/LDL Factorization' */
  real32_T APAt_DWORK1[16];            /* '<S225>/A*P*At' */
  boolean_T LDLFactorization_STATE;    /* '<S240>/LDL Factorization' */
  boolean_T LDLFactorization_STATE_m;  /* '<S229>/LDL Factorization' */
} DW_Controller_P7_T;

/* External inputs (root inport signals with default storage) */
typedef struct {
  real32_T Omega_Secondary;            /* '<Root>/Omega_Secondary' */
  real32_T Omega_Primary;              /* '<Root>/Omega_Primary' */
  real_T Theta_Helix;                  /* '<Root>/Theta_Helix' */
} ExtU_Controller_P7_T;

/* External outputs (root outports fed by signals with default storage) */
typedef struct {
  real_T Command;                      /* '<Root>/Command' */
} ExtY_Controller_P7_T;

/* Parameters (default storage) */
struct P_Controller_P7_T_ {
  real_T Der_GR_High;                  /* Variable: Der_GR_High
                                        * Referenced by: '<S36>/Derivative Gain'
                                        */
  real_T Der_GR_Low;                   /* Variable: Der_GR_Low
                                        * Referenced by: '<S89>/Derivative Gain'
                                        */
  real_T Int_GR_High;                  /* Variable: Int_GR_High
                                        * Referenced by: '<S40>/Integral Gain'
                                        */
  real_T Int_GR_Low;                   /* Variable: Int_GR_Low
                                        * Referenced by: '<S93>/Integral Gain'
                                        */
  real_T Int_RPM_High;                 /* Variable: Int_RPM_High
                                        * Referenced by: '<S146>/Integral Gain'
                                        */
  real_T Int_RPM_Low;                  /* Variable: Int_RPM_Low
                                        * Referenced by: '<S199>/Integral Gain'
                                        */
  real_T Omega_High;                   /* Variable: Omega_High
                                        * Referenced by: '<S6>/RPM_Hi'
                                        */
  real_T Omega_Low;                    /* Variable: Omega_Low
                                        * Referenced by: '<S7>/Constant'
                                        */
  real_T Phi_max;                      /* Variable: Phi_max
                                        * Referenced by: '<S4>/Ratio Max'
                                        */
  real_T Phi_min;                      /* Variable: Phi_min
                                        * Referenced by: '<S3>/Ratio Min'
                                        */
  real_T Prop_GR_High;                 /* Variable: Prop_GR_High
                                        * Referenced by: '<S48>/Proportional Gain'
                                        */
  real_T Prop_GR_Low;                  /* Variable: Prop_GR_Low
                                        * Referenced by: '<S101>/Proportional Gain'
                                        */
  real_T Prop_RPM_High;                /* Variable: Prop_RPM_High
                                        * Referenced by: '<S154>/Proportional Gain'
                                        */
  real_T Prop_RPM_Low;                 /* Variable: Prop_RPM_Low
                                        * Referenced by: '<S207>/Proportional Gain'
                                        */
  real_T V_lower;                      /* Variable: V_lower
                                        * Referenced by: '<S1>/Saturation1'
                                        */
  real_T V_upper;                      /* Variable: V_upper
                                        * Referenced by: '<S1>/Saturation1'
                                        */
  real32_T Der_RPM_High;               /* Variable: Der_RPM_High
                                        * Referenced by: '<S142>/Derivative Gain'
                                        */
  real32_T Der_RPM_Low;                /* Variable: Der_RPM_Low
                                        * Referenced by: '<S195>/Derivative Gain'
                                        */
  real_T PIDController_InitialConditionF;
                              /* Mask Parameter: PIDController_InitialConditionF
                               * Referenced by: '<S38>/Filter'
                               */
  real_T PIDController_InitialConditio_k;
                              /* Mask Parameter: PIDController_InitialConditio_k
                               * Referenced by: '<S144>/Filter'
                               */
  real_T PIDController_InitialConditio_n;
                              /* Mask Parameter: PIDController_InitialConditio_n
                               * Referenced by: '<S91>/Filter'
                               */
  real_T PIDController_InitialConditio_h;
                              /* Mask Parameter: PIDController_InitialConditio_h
                               * Referenced by: '<S197>/Filter'
                               */
  real_T PIDController_InitialConditio_e;
                              /* Mask Parameter: PIDController_InitialConditio_e
                               * Referenced by: '<S43>/Integrator'
                               */
  real_T PIDController_InitialConditio_i;
                              /* Mask Parameter: PIDController_InitialConditio_i
                               * Referenced by: '<S149>/Integrator'
                               */
  real_T PIDController_InitialConditio_g;
                              /* Mask Parameter: PIDController_InitialConditio_g
                               * Referenced by: '<S96>/Integrator'
                               */
  real_T PIDController_InitialConditio_m;
                              /* Mask Parameter: PIDController_InitialConditio_m
                               * Referenced by: '<S202>/Integrator'
                               */
  real_T PIDController_N;              /* Mask Parameter: PIDController_N
                                        * Referenced by: '<S46>/Filter Coefficient'
                                        */
  real_T PIDController_N_k;            /* Mask Parameter: PIDController_N_k
                                        * Referenced by: '<S152>/Filter Coefficient'
                                        */
  real_T PIDController_N_j;            /* Mask Parameter: PIDController_N_j
                                        * Referenced by: '<S99>/Filter Coefficient'
                                        */
  real_T PIDController_N_f;            /* Mask Parameter: PIDController_N_f
                                        * Referenced by: '<S205>/Filter Coefficient'
                                        */
  real_T Filter_gainval;               /* Computed Parameter: Filter_gainval
                                        * Referenced by: '<S38>/Filter'
                                        */
  real_T Integrator_gainval;           /* Computed Parameter: Integrator_gainval
                                        * Referenced by: '<S43>/Integrator'
                                        */
  real_T Filter_gainval_i;             /* Computed Parameter: Filter_gainval_i
                                        * Referenced by: '<S144>/Filter'
                                        */
  real_T Integrator_gainval_i;       /* Computed Parameter: Integrator_gainval_i
                                      * Referenced by: '<S149>/Integrator'
                                      */
  real_T Filter_gainval_h;             /* Computed Parameter: Filter_gainval_h
                                        * Referenced by: '<S91>/Filter'
                                        */
  real_T Integrator_gainval_d;       /* Computed Parameter: Integrator_gainval_d
                                      * Referenced by: '<S96>/Integrator'
                                      */
  real_T Filter_gainval_n;             /* Computed Parameter: Filter_gainval_n
                                        * Referenced by: '<S197>/Filter'
                                        */
  real_T Integrator_gainval_a;       /* Computed Parameter: Integrator_gainval_a
                                      * Referenced by: '<S202>/Integrator'
                                      */
  real_T Constant2_Value;              /* Expression: 0
                                        * Referenced by: '<S5>/Constant2'
                                        */
  real_T Constant_Value;               /* Expression: 0
                                        * Referenced by: '<S5>/Constant'
                                        */
  real_T Multiply_Gain;                /* Expression: 1/2.8
                                        * Referenced by: '<S2>/Multiply'
                                        */
  real_T Constant1_Value;              /* Expression: 0
                                        * Referenced by: '<S5>/Constant1'
                                        */
  real_T Constant3_Value;              /* Expression: 0
                                        * Referenced by: '<S5>/Constant3'
                                        */
  real_T Constant4_Value;              /* Expression: 4.85
                                        * Referenced by: '<S5>/Constant4'
                                        */
  int32_T Iterator_IterationLimit;/* Computed Parameter: Iterator_IterationLimit
                                   * Referenced by: '<S223>/Iterator'
                                   */
  int32_T Iterator_IterationLimit_n;
                                /* Computed Parameter: Iterator_IterationLimit_n
                                 * Referenced by: '<S234>/Iterator'
                                 */
  real32_T X_est_Y0;                   /* Computed Parameter: X_est_Y0
                                        * Referenced by: '<S223>/X_est'
                                        */
  real32_T X_prd_Y0;                   /* Computed Parameter: X_prd_Y0
                                        * Referenced by: '<S223>/X_prd'
                                        */
  real32_T P_prd_Y0;                   /* Computed Parameter: P_prd_Y0
                                        * Referenced by: '<S223>/P_prd'
                                        */
  real32_T Constant3_Value_h[16];      /* Computed Parameter: Constant3_Value_h
                                        * Referenced by: '<S225>/Constant3'
                                        */
  real32_T Hcst_Value[8];              /* Computed Parameter: Hcst_Value
                                        * Referenced by: '<S225>/Hcst'
                                        */
  real32_T Hcst_t_Value[8];            /* Computed Parameter: Hcst_t_Value
                                        * Referenced by: '<S225>/Hcst_t'
                                        */
  real32_T Constant2_Value_e[4];       /* Computed Parameter: Constant2_Value_e
                                        * Referenced by: '<S225>/Constant2'
                                        */
  real32_T Constant4_Value_l[16];      /* Computed Parameter: Constant4_Value_l
                                        * Referenced by: '<S225>/Constant4'
                                        */
  real32_T Constant5_Value[16];        /* Computed Parameter: Constant5_Value
                                        * Referenced by: '<S225>/Constant5'
                                        */
  real32_T X_est_Y0_f;                 /* Computed Parameter: X_est_Y0_f
                                        * Referenced by: '<S234>/X_est'
                                        */
  real32_T X_prd_Y0_l;                 /* Computed Parameter: X_prd_Y0_l
                                        * Referenced by: '<S234>/X_prd'
                                        */
  real32_T P_prd_Y0_e;                 /* Computed Parameter: P_prd_Y0_e
                                        * Referenced by: '<S234>/P_prd'
                                        */
  real32_T Constant3_Value_m[4];       /* Computed Parameter: Constant3_Value_m
                                        * Referenced by: '<S236>/Constant3'
                                        */
  real32_T Hcst_Value_e[4];            /* Computed Parameter: Hcst_Value_e
                                        * Referenced by: '<S236>/Hcst'
                                        */
  real32_T Hcst_t_Value_c[4];          /* Computed Parameter: Hcst_t_Value_c
                                        * Referenced by: '<S236>/Hcst_t'
                                        */
  real32_T Constant2_Value_l[4];       /* Computed Parameter: Constant2_Value_l
                                        * Referenced by: '<S236>/Constant2'
                                        */
  real32_T Constant4_Value_lj[4];      /* Computed Parameter: Constant4_Value_lj
                                        * Referenced by: '<S236>/Constant4'
                                        */
  real32_T Constant5_Value_k[4];       /* Computed Parameter: Constant5_Value_k
                                        * Referenced by: '<S236>/Constant5'
                                        */
  real32_T UnitDelay2_InitialCondition[4];
                              /* Computed Parameter: UnitDelay2_InitialCondition
                               * Referenced by: '<S220>/Unit Delay2'
                               */
  real32_T UnitDelay3_InitialCondition[16];
                              /* Computed Parameter: UnitDelay3_InitialCondition
                               * Referenced by: '<S220>/Unit Delay3'
                               */
  real32_T uDLookupTable1_tableData[32];
                                 /* Computed Parameter: uDLookupTable1_tableData
                                  * Referenced by: '<S2>/1-D Lookup Table1'
                                  */
  real32_T uDLookupTable1_bp01Data[32];
                                  /* Computed Parameter: uDLookupTable1_bp01Data
                                   * Referenced by: '<S2>/1-D Lookup Table1'
                                   */
  real32_T uDLookupTable_tableData[141];
                                  /* Computed Parameter: uDLookupTable_tableData
                                   * Referenced by: '<S2>/1-D Lookup Table'
                                   */
  real32_T uDLookupTable_bp01Data[141];
                                   /* Computed Parameter: uDLookupTable_bp01Data
                                    * Referenced by: '<S2>/1-D Lookup Table'
                                    */
  real32_T UnitDelay2_InitialCondition_j[2];
                            /* Computed Parameter: UnitDelay2_InitialCondition_j
                             * Referenced by: '<S221>/Unit Delay2'
                             */
  real32_T UnitDelay3_InitialCondition_m[4];
                            /* Computed Parameter: UnitDelay3_InitialCondition_m
                             * Referenced by: '<S221>/Unit Delay3'
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
 * Block '<S222>/Check Signal Attributes' : Unused code path elimination
 * Block '<S230>/Check Signal Attributes' : Unused code path elimination
 * Block '<S231>/Check Signal Attributes' : Unused code path elimination
 * Block '<S232>/Check Signal Attributes' : Unused code path elimination
 * Block '<S233>/Check Signal Attributes' : Unused code path elimination
 * Block '<S241>/Check Signal Attributes' : Unused code path elimination
 * Block '<S242>/Check Signal Attributes' : Unused code path elimination
 * Block '<S243>/Check Signal Attributes' : Unused code path elimination
 * Block '<S225>/P_Reshape' : Reshape block reduction
 * Block '<S225>/P_prd_Reshape' : Reshape block reduction
 * Block '<S236>/P_Reshape' : Reshape block reduction
 * Block '<S236>/P_prd_Reshape' : Reshape block reduction
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
 * '<S3>'   : 'Controller_P7/Controller/GR HI'
 * '<S4>'   : 'Controller_P7/Controller/GR LO'
 * '<S5>'   : 'Controller_P7/Controller/Limit Check'
 * '<S6>'   : 'Controller_P7/Controller/Omega HI'
 * '<S7>'   : 'Controller_P7/Controller/Omega LO'
 * '<S8>'   : 'Controller_P7/Controller/GR HI/PID Controller'
 * '<S9>'   : 'Controller_P7/Controller/GR HI/PID Controller/Anti-windup'
 * '<S10>'  : 'Controller_P7/Controller/GR HI/PID Controller/D Gain'
 * '<S11>'  : 'Controller_P7/Controller/GR HI/PID Controller/External Derivative'
 * '<S12>'  : 'Controller_P7/Controller/GR HI/PID Controller/Filter'
 * '<S13>'  : 'Controller_P7/Controller/GR HI/PID Controller/Filter ICs'
 * '<S14>'  : 'Controller_P7/Controller/GR HI/PID Controller/I Gain'
 * '<S15>'  : 'Controller_P7/Controller/GR HI/PID Controller/Ideal P Gain'
 * '<S16>'  : 'Controller_P7/Controller/GR HI/PID Controller/Ideal P Gain Fdbk'
 * '<S17>'  : 'Controller_P7/Controller/GR HI/PID Controller/Integrator'
 * '<S18>'  : 'Controller_P7/Controller/GR HI/PID Controller/Integrator ICs'
 * '<S19>'  : 'Controller_P7/Controller/GR HI/PID Controller/N Copy'
 * '<S20>'  : 'Controller_P7/Controller/GR HI/PID Controller/N Gain'
 * '<S21>'  : 'Controller_P7/Controller/GR HI/PID Controller/P Copy'
 * '<S22>'  : 'Controller_P7/Controller/GR HI/PID Controller/Parallel P Gain'
 * '<S23>'  : 'Controller_P7/Controller/GR HI/PID Controller/Reset Signal'
 * '<S24>'  : 'Controller_P7/Controller/GR HI/PID Controller/Saturation'
 * '<S25>'  : 'Controller_P7/Controller/GR HI/PID Controller/Saturation Fdbk'
 * '<S26>'  : 'Controller_P7/Controller/GR HI/PID Controller/Sum'
 * '<S27>'  : 'Controller_P7/Controller/GR HI/PID Controller/Sum Fdbk'
 * '<S28>'  : 'Controller_P7/Controller/GR HI/PID Controller/Tracking Mode'
 * '<S29>'  : 'Controller_P7/Controller/GR HI/PID Controller/Tracking Mode Sum'
 * '<S30>'  : 'Controller_P7/Controller/GR HI/PID Controller/Tsamp - Integral'
 * '<S31>'  : 'Controller_P7/Controller/GR HI/PID Controller/Tsamp - Ngain'
 * '<S32>'  : 'Controller_P7/Controller/GR HI/PID Controller/postSat Signal'
 * '<S33>'  : 'Controller_P7/Controller/GR HI/PID Controller/preInt Signal'
 * '<S34>'  : 'Controller_P7/Controller/GR HI/PID Controller/preSat Signal'
 * '<S35>'  : 'Controller_P7/Controller/GR HI/PID Controller/Anti-windup/Passthrough'
 * '<S36>'  : 'Controller_P7/Controller/GR HI/PID Controller/D Gain/Internal Parameters'
 * '<S37>'  : 'Controller_P7/Controller/GR HI/PID Controller/External Derivative/Error'
 * '<S38>'  : 'Controller_P7/Controller/GR HI/PID Controller/Filter/Disc. Forward Euler Filter'
 * '<S39>'  : 'Controller_P7/Controller/GR HI/PID Controller/Filter ICs/Internal IC - Filter'
 * '<S40>'  : 'Controller_P7/Controller/GR HI/PID Controller/I Gain/Internal Parameters'
 * '<S41>'  : 'Controller_P7/Controller/GR HI/PID Controller/Ideal P Gain/Passthrough'
 * '<S42>'  : 'Controller_P7/Controller/GR HI/PID Controller/Ideal P Gain Fdbk/Disabled'
 * '<S43>'  : 'Controller_P7/Controller/GR HI/PID Controller/Integrator/Discrete'
 * '<S44>'  : 'Controller_P7/Controller/GR HI/PID Controller/Integrator ICs/Internal IC'
 * '<S45>'  : 'Controller_P7/Controller/GR HI/PID Controller/N Copy/Disabled'
 * '<S46>'  : 'Controller_P7/Controller/GR HI/PID Controller/N Gain/Internal Parameters'
 * '<S47>'  : 'Controller_P7/Controller/GR HI/PID Controller/P Copy/Disabled'
 * '<S48>'  : 'Controller_P7/Controller/GR HI/PID Controller/Parallel P Gain/Internal Parameters'
 * '<S49>'  : 'Controller_P7/Controller/GR HI/PID Controller/Reset Signal/Disabled'
 * '<S50>'  : 'Controller_P7/Controller/GR HI/PID Controller/Saturation/Passthrough'
 * '<S51>'  : 'Controller_P7/Controller/GR HI/PID Controller/Saturation Fdbk/Disabled'
 * '<S52>'  : 'Controller_P7/Controller/GR HI/PID Controller/Sum/Sum_PID'
 * '<S53>'  : 'Controller_P7/Controller/GR HI/PID Controller/Sum Fdbk/Disabled'
 * '<S54>'  : 'Controller_P7/Controller/GR HI/PID Controller/Tracking Mode/Disabled'
 * '<S55>'  : 'Controller_P7/Controller/GR HI/PID Controller/Tracking Mode Sum/Passthrough'
 * '<S56>'  : 'Controller_P7/Controller/GR HI/PID Controller/Tsamp - Integral/TsSignalSpecification'
 * '<S57>'  : 'Controller_P7/Controller/GR HI/PID Controller/Tsamp - Ngain/Passthrough'
 * '<S58>'  : 'Controller_P7/Controller/GR HI/PID Controller/postSat Signal/Forward_Path'
 * '<S59>'  : 'Controller_P7/Controller/GR HI/PID Controller/preInt Signal/Internal PreInt'
 * '<S60>'  : 'Controller_P7/Controller/GR HI/PID Controller/preSat Signal/Forward_Path'
 * '<S61>'  : 'Controller_P7/Controller/GR LO/PID Controller'
 * '<S62>'  : 'Controller_P7/Controller/GR LO/PID Controller/Anti-windup'
 * '<S63>'  : 'Controller_P7/Controller/GR LO/PID Controller/D Gain'
 * '<S64>'  : 'Controller_P7/Controller/GR LO/PID Controller/External Derivative'
 * '<S65>'  : 'Controller_P7/Controller/GR LO/PID Controller/Filter'
 * '<S66>'  : 'Controller_P7/Controller/GR LO/PID Controller/Filter ICs'
 * '<S67>'  : 'Controller_P7/Controller/GR LO/PID Controller/I Gain'
 * '<S68>'  : 'Controller_P7/Controller/GR LO/PID Controller/Ideal P Gain'
 * '<S69>'  : 'Controller_P7/Controller/GR LO/PID Controller/Ideal P Gain Fdbk'
 * '<S70>'  : 'Controller_P7/Controller/GR LO/PID Controller/Integrator'
 * '<S71>'  : 'Controller_P7/Controller/GR LO/PID Controller/Integrator ICs'
 * '<S72>'  : 'Controller_P7/Controller/GR LO/PID Controller/N Copy'
 * '<S73>'  : 'Controller_P7/Controller/GR LO/PID Controller/N Gain'
 * '<S74>'  : 'Controller_P7/Controller/GR LO/PID Controller/P Copy'
 * '<S75>'  : 'Controller_P7/Controller/GR LO/PID Controller/Parallel P Gain'
 * '<S76>'  : 'Controller_P7/Controller/GR LO/PID Controller/Reset Signal'
 * '<S77>'  : 'Controller_P7/Controller/GR LO/PID Controller/Saturation'
 * '<S78>'  : 'Controller_P7/Controller/GR LO/PID Controller/Saturation Fdbk'
 * '<S79>'  : 'Controller_P7/Controller/GR LO/PID Controller/Sum'
 * '<S80>'  : 'Controller_P7/Controller/GR LO/PID Controller/Sum Fdbk'
 * '<S81>'  : 'Controller_P7/Controller/GR LO/PID Controller/Tracking Mode'
 * '<S82>'  : 'Controller_P7/Controller/GR LO/PID Controller/Tracking Mode Sum'
 * '<S83>'  : 'Controller_P7/Controller/GR LO/PID Controller/Tsamp - Integral'
 * '<S84>'  : 'Controller_P7/Controller/GR LO/PID Controller/Tsamp - Ngain'
 * '<S85>'  : 'Controller_P7/Controller/GR LO/PID Controller/postSat Signal'
 * '<S86>'  : 'Controller_P7/Controller/GR LO/PID Controller/preInt Signal'
 * '<S87>'  : 'Controller_P7/Controller/GR LO/PID Controller/preSat Signal'
 * '<S88>'  : 'Controller_P7/Controller/GR LO/PID Controller/Anti-windup/Passthrough'
 * '<S89>'  : 'Controller_P7/Controller/GR LO/PID Controller/D Gain/Internal Parameters'
 * '<S90>'  : 'Controller_P7/Controller/GR LO/PID Controller/External Derivative/Error'
 * '<S91>'  : 'Controller_P7/Controller/GR LO/PID Controller/Filter/Disc. Forward Euler Filter'
 * '<S92>'  : 'Controller_P7/Controller/GR LO/PID Controller/Filter ICs/Internal IC - Filter'
 * '<S93>'  : 'Controller_P7/Controller/GR LO/PID Controller/I Gain/Internal Parameters'
 * '<S94>'  : 'Controller_P7/Controller/GR LO/PID Controller/Ideal P Gain/Passthrough'
 * '<S95>'  : 'Controller_P7/Controller/GR LO/PID Controller/Ideal P Gain Fdbk/Disabled'
 * '<S96>'  : 'Controller_P7/Controller/GR LO/PID Controller/Integrator/Discrete'
 * '<S97>'  : 'Controller_P7/Controller/GR LO/PID Controller/Integrator ICs/Internal IC'
 * '<S98>'  : 'Controller_P7/Controller/GR LO/PID Controller/N Copy/Disabled'
 * '<S99>'  : 'Controller_P7/Controller/GR LO/PID Controller/N Gain/Internal Parameters'
 * '<S100>' : 'Controller_P7/Controller/GR LO/PID Controller/P Copy/Disabled'
 * '<S101>' : 'Controller_P7/Controller/GR LO/PID Controller/Parallel P Gain/Internal Parameters'
 * '<S102>' : 'Controller_P7/Controller/GR LO/PID Controller/Reset Signal/Disabled'
 * '<S103>' : 'Controller_P7/Controller/GR LO/PID Controller/Saturation/Passthrough'
 * '<S104>' : 'Controller_P7/Controller/GR LO/PID Controller/Saturation Fdbk/Disabled'
 * '<S105>' : 'Controller_P7/Controller/GR LO/PID Controller/Sum/Sum_PID'
 * '<S106>' : 'Controller_P7/Controller/GR LO/PID Controller/Sum Fdbk/Disabled'
 * '<S107>' : 'Controller_P7/Controller/GR LO/PID Controller/Tracking Mode/Disabled'
 * '<S108>' : 'Controller_P7/Controller/GR LO/PID Controller/Tracking Mode Sum/Passthrough'
 * '<S109>' : 'Controller_P7/Controller/GR LO/PID Controller/Tsamp - Integral/TsSignalSpecification'
 * '<S110>' : 'Controller_P7/Controller/GR LO/PID Controller/Tsamp - Ngain/Passthrough'
 * '<S111>' : 'Controller_P7/Controller/GR LO/PID Controller/postSat Signal/Forward_Path'
 * '<S112>' : 'Controller_P7/Controller/GR LO/PID Controller/preInt Signal/Internal PreInt'
 * '<S113>' : 'Controller_P7/Controller/GR LO/PID Controller/preSat Signal/Forward_Path'
 * '<S114>' : 'Controller_P7/Controller/Omega HI/PID Controller'
 * '<S115>' : 'Controller_P7/Controller/Omega HI/PID Controller/Anti-windup'
 * '<S116>' : 'Controller_P7/Controller/Omega HI/PID Controller/D Gain'
 * '<S117>' : 'Controller_P7/Controller/Omega HI/PID Controller/External Derivative'
 * '<S118>' : 'Controller_P7/Controller/Omega HI/PID Controller/Filter'
 * '<S119>' : 'Controller_P7/Controller/Omega HI/PID Controller/Filter ICs'
 * '<S120>' : 'Controller_P7/Controller/Omega HI/PID Controller/I Gain'
 * '<S121>' : 'Controller_P7/Controller/Omega HI/PID Controller/Ideal P Gain'
 * '<S122>' : 'Controller_P7/Controller/Omega HI/PID Controller/Ideal P Gain Fdbk'
 * '<S123>' : 'Controller_P7/Controller/Omega HI/PID Controller/Integrator'
 * '<S124>' : 'Controller_P7/Controller/Omega HI/PID Controller/Integrator ICs'
 * '<S125>' : 'Controller_P7/Controller/Omega HI/PID Controller/N Copy'
 * '<S126>' : 'Controller_P7/Controller/Omega HI/PID Controller/N Gain'
 * '<S127>' : 'Controller_P7/Controller/Omega HI/PID Controller/P Copy'
 * '<S128>' : 'Controller_P7/Controller/Omega HI/PID Controller/Parallel P Gain'
 * '<S129>' : 'Controller_P7/Controller/Omega HI/PID Controller/Reset Signal'
 * '<S130>' : 'Controller_P7/Controller/Omega HI/PID Controller/Saturation'
 * '<S131>' : 'Controller_P7/Controller/Omega HI/PID Controller/Saturation Fdbk'
 * '<S132>' : 'Controller_P7/Controller/Omega HI/PID Controller/Sum'
 * '<S133>' : 'Controller_P7/Controller/Omega HI/PID Controller/Sum Fdbk'
 * '<S134>' : 'Controller_P7/Controller/Omega HI/PID Controller/Tracking Mode'
 * '<S135>' : 'Controller_P7/Controller/Omega HI/PID Controller/Tracking Mode Sum'
 * '<S136>' : 'Controller_P7/Controller/Omega HI/PID Controller/Tsamp - Integral'
 * '<S137>' : 'Controller_P7/Controller/Omega HI/PID Controller/Tsamp - Ngain'
 * '<S138>' : 'Controller_P7/Controller/Omega HI/PID Controller/postSat Signal'
 * '<S139>' : 'Controller_P7/Controller/Omega HI/PID Controller/preInt Signal'
 * '<S140>' : 'Controller_P7/Controller/Omega HI/PID Controller/preSat Signal'
 * '<S141>' : 'Controller_P7/Controller/Omega HI/PID Controller/Anti-windup/Passthrough'
 * '<S142>' : 'Controller_P7/Controller/Omega HI/PID Controller/D Gain/Internal Parameters'
 * '<S143>' : 'Controller_P7/Controller/Omega HI/PID Controller/External Derivative/External Ydot'
 * '<S144>' : 'Controller_P7/Controller/Omega HI/PID Controller/Filter/Disc. Forward Euler Filter Only'
 * '<S145>' : 'Controller_P7/Controller/Omega HI/PID Controller/Filter ICs/Internal IC - Filter'
 * '<S146>' : 'Controller_P7/Controller/Omega HI/PID Controller/I Gain/Internal Parameters'
 * '<S147>' : 'Controller_P7/Controller/Omega HI/PID Controller/Ideal P Gain/Passthrough'
 * '<S148>' : 'Controller_P7/Controller/Omega HI/PID Controller/Ideal P Gain Fdbk/Disabled'
 * '<S149>' : 'Controller_P7/Controller/Omega HI/PID Controller/Integrator/Discrete'
 * '<S150>' : 'Controller_P7/Controller/Omega HI/PID Controller/Integrator ICs/Internal IC'
 * '<S151>' : 'Controller_P7/Controller/Omega HI/PID Controller/N Copy/Disabled'
 * '<S152>' : 'Controller_P7/Controller/Omega HI/PID Controller/N Gain/Internal Parameters'
 * '<S153>' : 'Controller_P7/Controller/Omega HI/PID Controller/P Copy/Disabled'
 * '<S154>' : 'Controller_P7/Controller/Omega HI/PID Controller/Parallel P Gain/Internal Parameters'
 * '<S155>' : 'Controller_P7/Controller/Omega HI/PID Controller/Reset Signal/Disabled'
 * '<S156>' : 'Controller_P7/Controller/Omega HI/PID Controller/Saturation/Passthrough'
 * '<S157>' : 'Controller_P7/Controller/Omega HI/PID Controller/Saturation Fdbk/Disabled'
 * '<S158>' : 'Controller_P7/Controller/Omega HI/PID Controller/Sum/Sum_PID'
 * '<S159>' : 'Controller_P7/Controller/Omega HI/PID Controller/Sum Fdbk/Disabled'
 * '<S160>' : 'Controller_P7/Controller/Omega HI/PID Controller/Tracking Mode/Disabled'
 * '<S161>' : 'Controller_P7/Controller/Omega HI/PID Controller/Tracking Mode Sum/Passthrough'
 * '<S162>' : 'Controller_P7/Controller/Omega HI/PID Controller/Tsamp - Integral/TsSignalSpecification'
 * '<S163>' : 'Controller_P7/Controller/Omega HI/PID Controller/Tsamp - Ngain/Passthrough'
 * '<S164>' : 'Controller_P7/Controller/Omega HI/PID Controller/postSat Signal/Forward_Path'
 * '<S165>' : 'Controller_P7/Controller/Omega HI/PID Controller/preInt Signal/Internal PreInt'
 * '<S166>' : 'Controller_P7/Controller/Omega HI/PID Controller/preSat Signal/Forward_Path'
 * '<S167>' : 'Controller_P7/Controller/Omega LO/PID Controller'
 * '<S168>' : 'Controller_P7/Controller/Omega LO/PID Controller/Anti-windup'
 * '<S169>' : 'Controller_P7/Controller/Omega LO/PID Controller/D Gain'
 * '<S170>' : 'Controller_P7/Controller/Omega LO/PID Controller/External Derivative'
 * '<S171>' : 'Controller_P7/Controller/Omega LO/PID Controller/Filter'
 * '<S172>' : 'Controller_P7/Controller/Omega LO/PID Controller/Filter ICs'
 * '<S173>' : 'Controller_P7/Controller/Omega LO/PID Controller/I Gain'
 * '<S174>' : 'Controller_P7/Controller/Omega LO/PID Controller/Ideal P Gain'
 * '<S175>' : 'Controller_P7/Controller/Omega LO/PID Controller/Ideal P Gain Fdbk'
 * '<S176>' : 'Controller_P7/Controller/Omega LO/PID Controller/Integrator'
 * '<S177>' : 'Controller_P7/Controller/Omega LO/PID Controller/Integrator ICs'
 * '<S178>' : 'Controller_P7/Controller/Omega LO/PID Controller/N Copy'
 * '<S179>' : 'Controller_P7/Controller/Omega LO/PID Controller/N Gain'
 * '<S180>' : 'Controller_P7/Controller/Omega LO/PID Controller/P Copy'
 * '<S181>' : 'Controller_P7/Controller/Omega LO/PID Controller/Parallel P Gain'
 * '<S182>' : 'Controller_P7/Controller/Omega LO/PID Controller/Reset Signal'
 * '<S183>' : 'Controller_P7/Controller/Omega LO/PID Controller/Saturation'
 * '<S184>' : 'Controller_P7/Controller/Omega LO/PID Controller/Saturation Fdbk'
 * '<S185>' : 'Controller_P7/Controller/Omega LO/PID Controller/Sum'
 * '<S186>' : 'Controller_P7/Controller/Omega LO/PID Controller/Sum Fdbk'
 * '<S187>' : 'Controller_P7/Controller/Omega LO/PID Controller/Tracking Mode'
 * '<S188>' : 'Controller_P7/Controller/Omega LO/PID Controller/Tracking Mode Sum'
 * '<S189>' : 'Controller_P7/Controller/Omega LO/PID Controller/Tsamp - Integral'
 * '<S190>' : 'Controller_P7/Controller/Omega LO/PID Controller/Tsamp - Ngain'
 * '<S191>' : 'Controller_P7/Controller/Omega LO/PID Controller/postSat Signal'
 * '<S192>' : 'Controller_P7/Controller/Omega LO/PID Controller/preInt Signal'
 * '<S193>' : 'Controller_P7/Controller/Omega LO/PID Controller/preSat Signal'
 * '<S194>' : 'Controller_P7/Controller/Omega LO/PID Controller/Anti-windup/Passthrough'
 * '<S195>' : 'Controller_P7/Controller/Omega LO/PID Controller/D Gain/Internal Parameters'
 * '<S196>' : 'Controller_P7/Controller/Omega LO/PID Controller/External Derivative/External Ydot'
 * '<S197>' : 'Controller_P7/Controller/Omega LO/PID Controller/Filter/Disc. Forward Euler Filter Only'
 * '<S198>' : 'Controller_P7/Controller/Omega LO/PID Controller/Filter ICs/Internal IC - Filter'
 * '<S199>' : 'Controller_P7/Controller/Omega LO/PID Controller/I Gain/Internal Parameters'
 * '<S200>' : 'Controller_P7/Controller/Omega LO/PID Controller/Ideal P Gain/Passthrough'
 * '<S201>' : 'Controller_P7/Controller/Omega LO/PID Controller/Ideal P Gain Fdbk/Disabled'
 * '<S202>' : 'Controller_P7/Controller/Omega LO/PID Controller/Integrator/Discrete'
 * '<S203>' : 'Controller_P7/Controller/Omega LO/PID Controller/Integrator ICs/Internal IC'
 * '<S204>' : 'Controller_P7/Controller/Omega LO/PID Controller/N Copy/Disabled'
 * '<S205>' : 'Controller_P7/Controller/Omega LO/PID Controller/N Gain/Internal Parameters'
 * '<S206>' : 'Controller_P7/Controller/Omega LO/PID Controller/P Copy/Disabled'
 * '<S207>' : 'Controller_P7/Controller/Omega LO/PID Controller/Parallel P Gain/Internal Parameters'
 * '<S208>' : 'Controller_P7/Controller/Omega LO/PID Controller/Reset Signal/Disabled'
 * '<S209>' : 'Controller_P7/Controller/Omega LO/PID Controller/Saturation/Passthrough'
 * '<S210>' : 'Controller_P7/Controller/Omega LO/PID Controller/Saturation Fdbk/Disabled'
 * '<S211>' : 'Controller_P7/Controller/Omega LO/PID Controller/Sum/Sum_PID'
 * '<S212>' : 'Controller_P7/Controller/Omega LO/PID Controller/Sum Fdbk/Disabled'
 * '<S213>' : 'Controller_P7/Controller/Omega LO/PID Controller/Tracking Mode/Disabled'
 * '<S214>' : 'Controller_P7/Controller/Omega LO/PID Controller/Tracking Mode Sum/Passthrough'
 * '<S215>' : 'Controller_P7/Controller/Omega LO/PID Controller/Tsamp - Integral/TsSignalSpecification'
 * '<S216>' : 'Controller_P7/Controller/Omega LO/PID Controller/Tsamp - Ngain/Passthrough'
 * '<S217>' : 'Controller_P7/Controller/Omega LO/PID Controller/postSat Signal/Forward_Path'
 * '<S218>' : 'Controller_P7/Controller/Omega LO/PID Controller/preInt Signal/Internal PreInt'
 * '<S219>' : 'Controller_P7/Controller/Omega LO/PID Controller/preSat Signal/Forward_Path'
 * '<S220>' : 'Controller_P7/Filter/Kalman Filter'
 * '<S221>' : 'Controller_P7/Filter/Kalman Filter1'
 * '<S222>' : 'Controller_P7/Filter/Kalman Filter/Check Signal Attributes'
 * '<S223>' : 'Controller_P7/Filter/Kalman Filter/Control'
 * '<S224>' : 'Controller_P7/Filter/Kalman Filter/Control/Options'
 * '<S225>' : 'Controller_P7/Filter/Kalman Filter/Control/Options/Core'
 * '<S226>' : 'Controller_P7/Filter/Kalman Filter/Control/Options/P_prd_Assign'
 * '<S227>' : 'Controller_P7/Filter/Kalman Filter/Control/Options/X_est_Assign'
 * '<S228>' : 'Controller_P7/Filter/Kalman Filter/Control/Options/X_prd_Assign'
 * '<S229>' : 'Controller_P7/Filter/Kalman Filter/Control/Options/Core/LDL Solver'
 * '<S230>' : 'Controller_P7/Filter/Kalman Filter/Control/Options/Core/LDL Solver/Check Signal Attributes'
 * '<S231>' : 'Controller_P7/Filter/Kalman Filter/Control/Options/Core/LDL Solver/Check Signal Attributes1'
 * '<S232>' : 'Controller_P7/Filter/Kalman Filter/Control/Options/Core/LDL Solver/Check Signal Attributes2'
 * '<S233>' : 'Controller_P7/Filter/Kalman Filter1/Check Signal Attributes'
 * '<S234>' : 'Controller_P7/Filter/Kalman Filter1/Control'
 * '<S235>' : 'Controller_P7/Filter/Kalman Filter1/Control/Options'
 * '<S236>' : 'Controller_P7/Filter/Kalman Filter1/Control/Options/Core'
 * '<S237>' : 'Controller_P7/Filter/Kalman Filter1/Control/Options/P_prd_Assign'
 * '<S238>' : 'Controller_P7/Filter/Kalman Filter1/Control/Options/X_est_Assign'
 * '<S239>' : 'Controller_P7/Filter/Kalman Filter1/Control/Options/X_prd_Assign'
 * '<S240>' : 'Controller_P7/Filter/Kalman Filter1/Control/Options/Core/LDL Solver'
 * '<S241>' : 'Controller_P7/Filter/Kalman Filter1/Control/Options/Core/LDL Solver/Check Signal Attributes'
 * '<S242>' : 'Controller_P7/Filter/Kalman Filter1/Control/Options/Core/LDL Solver/Check Signal Attributes1'
 * '<S243>' : 'Controller_P7/Filter/Kalman Filter1/Control/Options/Core/LDL Solver/Check Signal Attributes2'
 */
#endif                                 /* Controller_P7_h_ */
