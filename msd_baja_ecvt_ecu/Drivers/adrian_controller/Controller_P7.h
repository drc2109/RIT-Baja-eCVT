/*
 * Controller_P7.h
 *
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * Code generation for model "Controller_P7".
 *
 * Model version              : 5.18
 * Simulink Coder version : 25.2 (R2025b) 28-Jul-2025
 * C source code generated on : Wed Apr  8 18:52:52 2026
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
  real_T Add;                          /* '<S6>/Add' */
  real_T Filter;                       /* '<S196>/Filter' */
  real_T FilterCoefficient;            /* '<S204>/Filter Coefficient' */
  real_T SumD;                         /* '<S196>/SumD' */
  real_T IntegralGain;                 /* '<S198>/Integral Gain' */
  real_T Integrator;                   /* '<S201>/Integrator' */
  real_T ProportionalGain;             /* '<S206>/Proportional Gain' */
  real_T Add_m;                        /* '<S4>/Add' */
  real_T DerivativeGain;               /* '<S88>/Derivative Gain' */
  real_T Filter_l;                     /* '<S90>/Filter' */
  real_T SumD_d;                       /* '<S90>/SumD' */
  real_T IntegralGain_b;               /* '<S92>/Integral Gain' */
  real_T Integrator_o;                 /* '<S95>/Integrator' */
  real_T FilterCoefficient_i;          /* '<S98>/Filter Coefficient' */
  real_T ProportionalGain_k;           /* '<S100>/Proportional Gain' */
  real_T Add_h;                        /* '<S5>/Add' */
  real_T Filter_j;                     /* '<S143>/Filter' */
  real_T FilterCoefficient_a;          /* '<S151>/Filter Coefficient' */
  real_T SumD_o;                       /* '<S143>/SumD' */
  real_T IntegralGain_a;               /* '<S145>/Integral Gain' */
  real_T Integrator_j;                 /* '<S148>/Integrator' */
  real_T ProportionalGain_l;           /* '<S153>/Proportional Gain' */
  real_T Add_j;                        /* '<S3>/Add' */
  real_T DerivativeGain_a;             /* '<S35>/Derivative Gain' */
  real_T Filter_i;                     /* '<S37>/Filter' */
  real_T SumD_a;                       /* '<S37>/SumD' */
  real_T IntegralGain_d;               /* '<S39>/Integral Gain' */
  real_T Integrator_a;                 /* '<S42>/Integrator' */
  real_T FilterCoefficient_b;          /* '<S45>/Filter Coefficient' */
  real_T ProportionalGain_h;           /* '<S47>/Proportional Gain' */
  real32_T UnitDelay2[4];              /* '<S219>/Unit Delay2' */
  real32_T UnitDelay3[16];             /* '<S219>/Unit Delay3' */
  real32_T SheaveDisplacementin;       /* '<S2>/1-D Lookup Table1' */
  real32_T phi1;                       /* '<S2>/1-D Lookup Table' */
  real32_T Phi2;                       /* '<S2>/Divide' */
  real32_T UnitDelay2_o[2];            /* '<S220>/Unit Delay2' */
  real32_T UnitDelay3_c[4];            /* '<S220>/Unit Delay3' */
  real32_T Selector2[4];               /* '<S234>/Selector2' */
  real32_T P_prdTrans[4];              /* '<S235>/P_prd Trans' */
  real32_T HP_prdt[4];                 /* '<S235>/H*P_prdt' */
  real32_T HP_prdtHt[4];               /* '<S235>/H*P_prdt*Ht' */
  real32_T HP_prdtHtR[4];              /* '<S235>/H*P_prdt*Ht+R' */
  real32_T LDLFactorization[4];        /* '<S239>/LDL Factorization' */
  real32_T y[4];                       /* '<S239>/Forward Substitution' */
  real32_T d[2];                       /* '<S239>/Extract Diagonal' */
  real32_T MathFunction[2];            /* '<S239>/Math Function' */
  real32_T MatrixScaling[4];           /* '<S239>/Matrix Scaling' */
  real32_T BackwardSubstitution[4];    /* '<S239>/Backward Substitution' */
  real32_T KTrans[4];                  /* '<S235>/K Trans' */
  real32_T KHP_prd[4];                 /* '<S235>/K*H*P_prd' */
  real32_T P_prdKHP_prd[4];            /* '<S235>/P_prd-K*H*P_prd' */
  real32_T APAt[4];                    /* '<S235>/A*P*At' */
  real32_T APAtQ[4];                   /* '<S235>/A*P*At+Q' */
  real32_T Selector1[2];               /* '<S234>/Selector1' */
  real32_T TmpSignalConversionAtSelectorIn[2];
  real32_T Selector[2];                /* '<S234>/Selector' */
  real32_T HX_prd[2];                  /* '<S235>/H*X_prd' */
  real32_T ZHX_prd[2];                 /* '<S235>/Z-H*X_prd' */
  real32_T KZHX_prd[2];                /* '<S235>/K*(Z-H*X_prd)' */
  real32_T X_prdKZHX_prd[2];           /* '<S235>/X_prd+K*(Z-H*X_prd)' */
  real32_T AX[2];                      /* '<S235>/A*X' */
  real32_T Assignment[4];              /* '<S236>/Assignment' */
  real32_T Assignment_j[2];            /* '<S237>/Assignment' */
  real32_T Assignment_m[2];            /* '<S238>/Assignment' */
  real32_T Selector2_j[16];            /* '<S223>/Selector2' */
  real32_T P_prdTrans_f[16];           /* '<S224>/P_prd Trans' */
  real32_T HP_prdt_p[8];               /* '<S224>/H*P_prdt' */
  real32_T HP_prdtHt_l[4];             /* '<S224>/H*P_prdt*Ht' */
  real32_T HP_prdtHtR_i[4];            /* '<S224>/H*P_prdt*Ht+R' */
  real32_T LDLFactorization_g[4];      /* '<S228>/LDL Factorization' */
  real32_T y_e[8];                     /* '<S228>/Forward Substitution' */
  real32_T d_e[2];                     /* '<S228>/Extract Diagonal' */
  real32_T MathFunction_l[2];          /* '<S228>/Math Function' */
  real32_T MatrixScaling_m[8];         /* '<S228>/Matrix Scaling' */
  real32_T BackwardSubstitution_d[8];  /* '<S228>/Backward Substitution' */
  real32_T KTrans_c[8];                /* '<S224>/K Trans' */
  real32_T KHP_prd_p[16];              /* '<S224>/K*H*P_prd' */
  real32_T P_prdKHP_prd_k[16];         /* '<S224>/P_prd-K*H*P_prd' */
  real32_T APAt_g[16];                 /* '<S224>/A*P*At' */
  real32_T APAtQ_h[16];                /* '<S224>/A*P*At+Q' */
  real32_T Selector1_b[4];             /* '<S223>/Selector1' */
  real32_T TmpSignalConversionAtSelector_l[2];
  real32_T Selector_f[2];              /* '<S223>/Selector' */
  real32_T HX_prd_b[2];                /* '<S224>/H*X_prd' */
  real32_T ZHX_prd_h[2];               /* '<S224>/Z-H*X_prd' */
  real32_T KZHX_prd_c[4];              /* '<S224>/K*(Z-H*X_prd)' */
  real32_T X_prdKZHX_prd_i[4];         /* '<S224>/X_prd+K*(Z-H*X_prd)' */
  real32_T AX_f[4];                    /* '<S224>/A*X' */
  real32_T Assignment_d[16];           /* '<S225>/Assignment' */
  real32_T Assignment_dh[4];           /* '<S226>/Assignment' */
  real32_T Assignment_g[4];            /* '<S227>/Assignment' */
  real32_T UnaryMinus;                 /* '<S195>/Unary Minus' */
  real32_T DerivativeGain_af;          /* '<S194>/Derivative Gain' */
  real32_T UnaryMinus_j;               /* '<S142>/Unary Minus' */
  real32_T DerivativeGain_n;           /* '<S141>/Derivative Gain' */
  int32_T Iterator;                    /* '<S233>/Iterator' */
  int32_T Iterator_i;                  /* '<S222>/Iterator' */
} B_Controller_P7_T;

/* Block states (default storage) for system '<Root>' */
typedef struct {
  real_T Filter_DSTATE;                /* '<S196>/Filter' */
  real_T Integrator_DSTATE;            /* '<S201>/Integrator' */
  real_T Filter_DSTATE_d;              /* '<S90>/Filter' */
  real_T Integrator_DSTATE_l;          /* '<S95>/Integrator' */
  real_T Filter_DSTATE_i;              /* '<S143>/Filter' */
  real_T Integrator_DSTATE_j;          /* '<S148>/Integrator' */
  real_T Filter_DSTATE_dz;             /* '<S37>/Filter' */
  real_T Integrator_DSTATE_n;          /* '<S42>/Integrator' */
  real_T Add_DWORK1;                   /* '<S6>/Add' */
  real32_T UnitDelay2_DSTATE[4];       /* '<S219>/Unit Delay2' */
  real32_T UnitDelay3_DSTATE[16];      /* '<S219>/Unit Delay3' */
  real32_T UnitDelay2_DSTATE_b[2];     /* '<S220>/Unit Delay2' */
  real32_T UnitDelay3_DSTATE_f[4];     /* '<S220>/Unit Delay3' */
  real32_T LDLFactorization_VMX[2];    /* '<S239>/LDL Factorization' */
  real32_T LDLFactorization_VMX_a[2];  /* '<S228>/LDL Factorization' */
  real32_T APAt_DWORK1[16];            /* '<S224>/A*P*At' */
  boolean_T LDLFactorization_STATE;    /* '<S239>/LDL Factorization' */
  boolean_T LDLFactorization_STATE_m;  /* '<S228>/LDL Factorization' */
} DW_Controller_P7_T;

/* External inputs (root inport signals with default storage) */
typedef struct {
  real32_T Omega_Secondary;            /* '<Root>/Omega_Secondary' */
  real32_T Omega_Primary;              /* '<Root>/Omega_Primary' */
  real32_T Theta_Helix;                /* '<Root>/Theta_Helix' */
} ExtU_Controller_P7_T;

/* External outputs (root outports fed by signals with default storage) */
typedef struct {
  real_T Command;                      /* '<Root>/Command' */
} ExtY_Controller_P7_T;

/* Parameters (default storage) */
struct P_Controller_P7_T_ {
  real_T Der_GR_High;                  /* Variable: Der_GR_High
                                        * Referenced by: '<S35>/Derivative Gain'
                                        */
  real_T Der_GR_Low;                   /* Variable: Der_GR_Low
                                        * Referenced by: '<S88>/Derivative Gain'
                                        */
  real_T Int_GR_High;                  /* Variable: Int_GR_High
                                        * Referenced by: '<S39>/Integral Gain'
                                        */
  real_T Int_GR_Low;                   /* Variable: Int_GR_Low
                                        * Referenced by: '<S92>/Integral Gain'
                                        */
  real_T Int_RPM_High;                 /* Variable: Int_RPM_High
                                        * Referenced by: '<S145>/Integral Gain'
                                        */
  real_T Int_RPM_Low;                  /* Variable: Int_RPM_Low
                                        * Referenced by: '<S198>/Integral Gain'
                                        */
  real_T Omega_High;                   /* Variable: Omega_High
                                        * Referenced by: '<S5>/RPM_Hi'
                                        */
  real_T Omega_Low;                    /* Variable: Omega_Low
                                        * Referenced by: '<S6>/Constant'
                                        */
  real_T Phi_max;                      /* Variable: Phi_max
                                        * Referenced by: '<S4>/Ratio Max'
                                        */
  real_T Phi_min;                      /* Variable: Phi_min
                                        * Referenced by: '<S3>/Ratio Min'
                                        */
  real_T Prop_GR_High;                 /* Variable: Prop_GR_High
                                        * Referenced by: '<S47>/Proportional Gain'
                                        */
  real_T Prop_GR_Low;                  /* Variable: Prop_GR_Low
                                        * Referenced by: '<S100>/Proportional Gain'
                                        */
  real_T Prop_RPM_High;                /* Variable: Prop_RPM_High
                                        * Referenced by: '<S153>/Proportional Gain'
                                        */
  real_T Prop_RPM_Low;                 /* Variable: Prop_RPM_Low
                                        * Referenced by: '<S206>/Proportional Gain'
                                        */
  real_T V_lower;                      /* Variable: V_lower
                                        * Referenced by: '<S1>/Saturation1'
                                        */
  real_T V_upper;                      /* Variable: V_upper
                                        * Referenced by: '<S1>/Saturation1'
                                        */
  real32_T Der_RPM_High;               /* Variable: Der_RPM_High
                                        * Referenced by: '<S141>/Derivative Gain'
                                        */
  real32_T Der_RPM_Low;                /* Variable: Der_RPM_Low
                                        * Referenced by: '<S194>/Derivative Gain'
                                        */
  real_T PIDController_InitialConditionF;
                              /* Mask Parameter: PIDController_InitialConditionF
                               * Referenced by: '<S37>/Filter'
                               */
  real_T PIDController_InitialConditio_k;
                              /* Mask Parameter: PIDController_InitialConditio_k
                               * Referenced by: '<S143>/Filter'
                               */
  real_T PIDController_InitialConditio_n;
                              /* Mask Parameter: PIDController_InitialConditio_n
                               * Referenced by: '<S90>/Filter'
                               */
  real_T PIDController_InitialConditio_h;
                              /* Mask Parameter: PIDController_InitialConditio_h
                               * Referenced by: '<S196>/Filter'
                               */
  real_T PIDController_InitialConditio_e;
                              /* Mask Parameter: PIDController_InitialConditio_e
                               * Referenced by: '<S42>/Integrator'
                               */
  real_T PIDController_InitialConditio_i;
                              /* Mask Parameter: PIDController_InitialConditio_i
                               * Referenced by: '<S148>/Integrator'
                               */
  real_T PIDController_InitialConditio_g;
                              /* Mask Parameter: PIDController_InitialConditio_g
                               * Referenced by: '<S95>/Integrator'
                               */
  real_T PIDController_InitialConditio_m;
                              /* Mask Parameter: PIDController_InitialConditio_m
                               * Referenced by: '<S201>/Integrator'
                               */
  real_T PIDController_N;              /* Mask Parameter: PIDController_N
                                        * Referenced by: '<S45>/Filter Coefficient'
                                        */
  real_T PIDController_N_k;            /* Mask Parameter: PIDController_N_k
                                        * Referenced by: '<S151>/Filter Coefficient'
                                        */
  real_T PIDController_N_j;            /* Mask Parameter: PIDController_N_j
                                        * Referenced by: '<S98>/Filter Coefficient'
                                        */
  real_T PIDController_N_f;            /* Mask Parameter: PIDController_N_f
                                        * Referenced by: '<S204>/Filter Coefficient'
                                        */
  real_T Filter_gainval;               /* Computed Parameter: Filter_gainval
                                        * Referenced by: '<S37>/Filter'
                                        */
  real_T Integrator_gainval;           /* Computed Parameter: Integrator_gainval
                                        * Referenced by: '<S42>/Integrator'
                                        */
  real_T Filter_gainval_i;             /* Computed Parameter: Filter_gainval_i
                                        * Referenced by: '<S143>/Filter'
                                        */
  real_T Integrator_gainval_i;       /* Computed Parameter: Integrator_gainval_i
                                      * Referenced by: '<S148>/Integrator'
                                      */
  real_T Filter_gainval_h;             /* Computed Parameter: Filter_gainval_h
                                        * Referenced by: '<S90>/Filter'
                                        */
  real_T Integrator_gainval_d;       /* Computed Parameter: Integrator_gainval_d
                                      * Referenced by: '<S95>/Integrator'
                                      */
  real_T Filter_gainval_n;             /* Computed Parameter: Filter_gainval_n
                                        * Referenced by: '<S196>/Filter'
                                        */
  real_T Integrator_gainval_a;       /* Computed Parameter: Integrator_gainval_a
                                      * Referenced by: '<S201>/Integrator'
                                      */
  int32_T Iterator_IterationLimit;/* Computed Parameter: Iterator_IterationLimit
                                   * Referenced by: '<S222>/Iterator'
                                   */
  int32_T Iterator_IterationLimit_n;
                                /* Computed Parameter: Iterator_IterationLimit_n
                                 * Referenced by: '<S233>/Iterator'
                                 */
  real32_T X_est_Y0;                   /* Computed Parameter: X_est_Y0
                                        * Referenced by: '<S222>/X_est'
                                        */
  real32_T X_prd_Y0;                   /* Computed Parameter: X_prd_Y0
                                        * Referenced by: '<S222>/X_prd'
                                        */
  real32_T P_prd_Y0;                   /* Computed Parameter: P_prd_Y0
                                        * Referenced by: '<S222>/P_prd'
                                        */
  real32_T Constant3_Value[16];        /* Computed Parameter: Constant3_Value
                                        * Referenced by: '<S224>/Constant3'
                                        */
  real32_T Hcst_Value[8];              /* Computed Parameter: Hcst_Value
                                        * Referenced by: '<S224>/Hcst'
                                        */
  real32_T Hcst_t_Value[8];            /* Computed Parameter: Hcst_t_Value
                                        * Referenced by: '<S224>/Hcst_t'
                                        */
  real32_T Constant2_Value[4];         /* Computed Parameter: Constant2_Value
                                        * Referenced by: '<S224>/Constant2'
                                        */
  real32_T Constant4_Value[16];        /* Computed Parameter: Constant4_Value
                                        * Referenced by: '<S224>/Constant4'
                                        */
  real32_T Constant5_Value[16];        /* Computed Parameter: Constant5_Value
                                        * Referenced by: '<S224>/Constant5'
                                        */
  real32_T X_est_Y0_f;                 /* Computed Parameter: X_est_Y0_f
                                        * Referenced by: '<S233>/X_est'
                                        */
  real32_T X_prd_Y0_l;                 /* Computed Parameter: X_prd_Y0_l
                                        * Referenced by: '<S233>/X_prd'
                                        */
  real32_T P_prd_Y0_e;                 /* Computed Parameter: P_prd_Y0_e
                                        * Referenced by: '<S233>/P_prd'
                                        */
  real32_T Constant3_Value_m[4];       /* Computed Parameter: Constant3_Value_m
                                        * Referenced by: '<S235>/Constant3'
                                        */
  real32_T Hcst_Value_e[4];            /* Computed Parameter: Hcst_Value_e
                                        * Referenced by: '<S235>/Hcst'
                                        */
  real32_T Hcst_t_Value_c[4];          /* Computed Parameter: Hcst_t_Value_c
                                        * Referenced by: '<S235>/Hcst_t'
                                        */
  real32_T Constant2_Value_l[4];       /* Computed Parameter: Constant2_Value_l
                                        * Referenced by: '<S235>/Constant2'
                                        */
  real32_T Constant4_Value_l[4];       /* Computed Parameter: Constant4_Value_l
                                        * Referenced by: '<S235>/Constant4'
                                        */
  real32_T Constant5_Value_k[4];       /* Computed Parameter: Constant5_Value_k
                                        * Referenced by: '<S235>/Constant5'
                                        */
  real32_T UnitDelay2_InitialCondition[4];
                              /* Computed Parameter: UnitDelay2_InitialCondition
                               * Referenced by: '<S219>/Unit Delay2'
                               */
  real32_T UnitDelay3_InitialCondition[16];
                              /* Computed Parameter: UnitDelay3_InitialCondition
                               * Referenced by: '<S219>/Unit Delay3'
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
                             * Referenced by: '<S220>/Unit Delay2'
                             */
  real32_T UnitDelay3_InitialCondition_m[4];
                            /* Computed Parameter: UnitDelay3_InitialCondition_m
                             * Referenced by: '<S220>/Unit Delay3'
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
 * Block '<S221>/Check Signal Attributes' : Unused code path elimination
 * Block '<S229>/Check Signal Attributes' : Unused code path elimination
 * Block '<S230>/Check Signal Attributes' : Unused code path elimination
 * Block '<S231>/Check Signal Attributes' : Unused code path elimination
 * Block '<S232>/Check Signal Attributes' : Unused code path elimination
 * Block '<S240>/Check Signal Attributes' : Unused code path elimination
 * Block '<S241>/Check Signal Attributes' : Unused code path elimination
 * Block '<S242>/Check Signal Attributes' : Unused code path elimination
 * Block '<S224>/P_Reshape' : Reshape block reduction
 * Block '<S224>/P_prd_Reshape' : Reshape block reduction
 * Block '<S235>/P_Reshape' : Reshape block reduction
 * Block '<S235>/P_prd_Reshape' : Reshape block reduction
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
 * '<S5>'   : 'Controller_P7/Controller/Omega HI'
 * '<S6>'   : 'Controller_P7/Controller/Omega LO'
 * '<S7>'   : 'Controller_P7/Controller/GR HI/PID Controller'
 * '<S8>'   : 'Controller_P7/Controller/GR HI/PID Controller/Anti-windup'
 * '<S9>'   : 'Controller_P7/Controller/GR HI/PID Controller/D Gain'
 * '<S10>'  : 'Controller_P7/Controller/GR HI/PID Controller/External Derivative'
 * '<S11>'  : 'Controller_P7/Controller/GR HI/PID Controller/Filter'
 * '<S12>'  : 'Controller_P7/Controller/GR HI/PID Controller/Filter ICs'
 * '<S13>'  : 'Controller_P7/Controller/GR HI/PID Controller/I Gain'
 * '<S14>'  : 'Controller_P7/Controller/GR HI/PID Controller/Ideal P Gain'
 * '<S15>'  : 'Controller_P7/Controller/GR HI/PID Controller/Ideal P Gain Fdbk'
 * '<S16>'  : 'Controller_P7/Controller/GR HI/PID Controller/Integrator'
 * '<S17>'  : 'Controller_P7/Controller/GR HI/PID Controller/Integrator ICs'
 * '<S18>'  : 'Controller_P7/Controller/GR HI/PID Controller/N Copy'
 * '<S19>'  : 'Controller_P7/Controller/GR HI/PID Controller/N Gain'
 * '<S20>'  : 'Controller_P7/Controller/GR HI/PID Controller/P Copy'
 * '<S21>'  : 'Controller_P7/Controller/GR HI/PID Controller/Parallel P Gain'
 * '<S22>'  : 'Controller_P7/Controller/GR HI/PID Controller/Reset Signal'
 * '<S23>'  : 'Controller_P7/Controller/GR HI/PID Controller/Saturation'
 * '<S24>'  : 'Controller_P7/Controller/GR HI/PID Controller/Saturation Fdbk'
 * '<S25>'  : 'Controller_P7/Controller/GR HI/PID Controller/Sum'
 * '<S26>'  : 'Controller_P7/Controller/GR HI/PID Controller/Sum Fdbk'
 * '<S27>'  : 'Controller_P7/Controller/GR HI/PID Controller/Tracking Mode'
 * '<S28>'  : 'Controller_P7/Controller/GR HI/PID Controller/Tracking Mode Sum'
 * '<S29>'  : 'Controller_P7/Controller/GR HI/PID Controller/Tsamp - Integral'
 * '<S30>'  : 'Controller_P7/Controller/GR HI/PID Controller/Tsamp - Ngain'
 * '<S31>'  : 'Controller_P7/Controller/GR HI/PID Controller/postSat Signal'
 * '<S32>'  : 'Controller_P7/Controller/GR HI/PID Controller/preInt Signal'
 * '<S33>'  : 'Controller_P7/Controller/GR HI/PID Controller/preSat Signal'
 * '<S34>'  : 'Controller_P7/Controller/GR HI/PID Controller/Anti-windup/Passthrough'
 * '<S35>'  : 'Controller_P7/Controller/GR HI/PID Controller/D Gain/Internal Parameters'
 * '<S36>'  : 'Controller_P7/Controller/GR HI/PID Controller/External Derivative/Error'
 * '<S37>'  : 'Controller_P7/Controller/GR HI/PID Controller/Filter/Disc. Forward Euler Filter'
 * '<S38>'  : 'Controller_P7/Controller/GR HI/PID Controller/Filter ICs/Internal IC - Filter'
 * '<S39>'  : 'Controller_P7/Controller/GR HI/PID Controller/I Gain/Internal Parameters'
 * '<S40>'  : 'Controller_P7/Controller/GR HI/PID Controller/Ideal P Gain/Passthrough'
 * '<S41>'  : 'Controller_P7/Controller/GR HI/PID Controller/Ideal P Gain Fdbk/Disabled'
 * '<S42>'  : 'Controller_P7/Controller/GR HI/PID Controller/Integrator/Discrete'
 * '<S43>'  : 'Controller_P7/Controller/GR HI/PID Controller/Integrator ICs/Internal IC'
 * '<S44>'  : 'Controller_P7/Controller/GR HI/PID Controller/N Copy/Disabled'
 * '<S45>'  : 'Controller_P7/Controller/GR HI/PID Controller/N Gain/Internal Parameters'
 * '<S46>'  : 'Controller_P7/Controller/GR HI/PID Controller/P Copy/Disabled'
 * '<S47>'  : 'Controller_P7/Controller/GR HI/PID Controller/Parallel P Gain/Internal Parameters'
 * '<S48>'  : 'Controller_P7/Controller/GR HI/PID Controller/Reset Signal/Disabled'
 * '<S49>'  : 'Controller_P7/Controller/GR HI/PID Controller/Saturation/Passthrough'
 * '<S50>'  : 'Controller_P7/Controller/GR HI/PID Controller/Saturation Fdbk/Disabled'
 * '<S51>'  : 'Controller_P7/Controller/GR HI/PID Controller/Sum/Sum_PID'
 * '<S52>'  : 'Controller_P7/Controller/GR HI/PID Controller/Sum Fdbk/Disabled'
 * '<S53>'  : 'Controller_P7/Controller/GR HI/PID Controller/Tracking Mode/Disabled'
 * '<S54>'  : 'Controller_P7/Controller/GR HI/PID Controller/Tracking Mode Sum/Passthrough'
 * '<S55>'  : 'Controller_P7/Controller/GR HI/PID Controller/Tsamp - Integral/TsSignalSpecification'
 * '<S56>'  : 'Controller_P7/Controller/GR HI/PID Controller/Tsamp - Ngain/Passthrough'
 * '<S57>'  : 'Controller_P7/Controller/GR HI/PID Controller/postSat Signal/Forward_Path'
 * '<S58>'  : 'Controller_P7/Controller/GR HI/PID Controller/preInt Signal/Internal PreInt'
 * '<S59>'  : 'Controller_P7/Controller/GR HI/PID Controller/preSat Signal/Forward_Path'
 * '<S60>'  : 'Controller_P7/Controller/GR LO/PID Controller'
 * '<S61>'  : 'Controller_P7/Controller/GR LO/PID Controller/Anti-windup'
 * '<S62>'  : 'Controller_P7/Controller/GR LO/PID Controller/D Gain'
 * '<S63>'  : 'Controller_P7/Controller/GR LO/PID Controller/External Derivative'
 * '<S64>'  : 'Controller_P7/Controller/GR LO/PID Controller/Filter'
 * '<S65>'  : 'Controller_P7/Controller/GR LO/PID Controller/Filter ICs'
 * '<S66>'  : 'Controller_P7/Controller/GR LO/PID Controller/I Gain'
 * '<S67>'  : 'Controller_P7/Controller/GR LO/PID Controller/Ideal P Gain'
 * '<S68>'  : 'Controller_P7/Controller/GR LO/PID Controller/Ideal P Gain Fdbk'
 * '<S69>'  : 'Controller_P7/Controller/GR LO/PID Controller/Integrator'
 * '<S70>'  : 'Controller_P7/Controller/GR LO/PID Controller/Integrator ICs'
 * '<S71>'  : 'Controller_P7/Controller/GR LO/PID Controller/N Copy'
 * '<S72>'  : 'Controller_P7/Controller/GR LO/PID Controller/N Gain'
 * '<S73>'  : 'Controller_P7/Controller/GR LO/PID Controller/P Copy'
 * '<S74>'  : 'Controller_P7/Controller/GR LO/PID Controller/Parallel P Gain'
 * '<S75>'  : 'Controller_P7/Controller/GR LO/PID Controller/Reset Signal'
 * '<S76>'  : 'Controller_P7/Controller/GR LO/PID Controller/Saturation'
 * '<S77>'  : 'Controller_P7/Controller/GR LO/PID Controller/Saturation Fdbk'
 * '<S78>'  : 'Controller_P7/Controller/GR LO/PID Controller/Sum'
 * '<S79>'  : 'Controller_P7/Controller/GR LO/PID Controller/Sum Fdbk'
 * '<S80>'  : 'Controller_P7/Controller/GR LO/PID Controller/Tracking Mode'
 * '<S81>'  : 'Controller_P7/Controller/GR LO/PID Controller/Tracking Mode Sum'
 * '<S82>'  : 'Controller_P7/Controller/GR LO/PID Controller/Tsamp - Integral'
 * '<S83>'  : 'Controller_P7/Controller/GR LO/PID Controller/Tsamp - Ngain'
 * '<S84>'  : 'Controller_P7/Controller/GR LO/PID Controller/postSat Signal'
 * '<S85>'  : 'Controller_P7/Controller/GR LO/PID Controller/preInt Signal'
 * '<S86>'  : 'Controller_P7/Controller/GR LO/PID Controller/preSat Signal'
 * '<S87>'  : 'Controller_P7/Controller/GR LO/PID Controller/Anti-windup/Passthrough'
 * '<S88>'  : 'Controller_P7/Controller/GR LO/PID Controller/D Gain/Internal Parameters'
 * '<S89>'  : 'Controller_P7/Controller/GR LO/PID Controller/External Derivative/Error'
 * '<S90>'  : 'Controller_P7/Controller/GR LO/PID Controller/Filter/Disc. Forward Euler Filter'
 * '<S91>'  : 'Controller_P7/Controller/GR LO/PID Controller/Filter ICs/Internal IC - Filter'
 * '<S92>'  : 'Controller_P7/Controller/GR LO/PID Controller/I Gain/Internal Parameters'
 * '<S93>'  : 'Controller_P7/Controller/GR LO/PID Controller/Ideal P Gain/Passthrough'
 * '<S94>'  : 'Controller_P7/Controller/GR LO/PID Controller/Ideal P Gain Fdbk/Disabled'
 * '<S95>'  : 'Controller_P7/Controller/GR LO/PID Controller/Integrator/Discrete'
 * '<S96>'  : 'Controller_P7/Controller/GR LO/PID Controller/Integrator ICs/Internal IC'
 * '<S97>'  : 'Controller_P7/Controller/GR LO/PID Controller/N Copy/Disabled'
 * '<S98>'  : 'Controller_P7/Controller/GR LO/PID Controller/N Gain/Internal Parameters'
 * '<S99>'  : 'Controller_P7/Controller/GR LO/PID Controller/P Copy/Disabled'
 * '<S100>' : 'Controller_P7/Controller/GR LO/PID Controller/Parallel P Gain/Internal Parameters'
 * '<S101>' : 'Controller_P7/Controller/GR LO/PID Controller/Reset Signal/Disabled'
 * '<S102>' : 'Controller_P7/Controller/GR LO/PID Controller/Saturation/Passthrough'
 * '<S103>' : 'Controller_P7/Controller/GR LO/PID Controller/Saturation Fdbk/Disabled'
 * '<S104>' : 'Controller_P7/Controller/GR LO/PID Controller/Sum/Sum_PID'
 * '<S105>' : 'Controller_P7/Controller/GR LO/PID Controller/Sum Fdbk/Disabled'
 * '<S106>' : 'Controller_P7/Controller/GR LO/PID Controller/Tracking Mode/Disabled'
 * '<S107>' : 'Controller_P7/Controller/GR LO/PID Controller/Tracking Mode Sum/Passthrough'
 * '<S108>' : 'Controller_P7/Controller/GR LO/PID Controller/Tsamp - Integral/TsSignalSpecification'
 * '<S109>' : 'Controller_P7/Controller/GR LO/PID Controller/Tsamp - Ngain/Passthrough'
 * '<S110>' : 'Controller_P7/Controller/GR LO/PID Controller/postSat Signal/Forward_Path'
 * '<S111>' : 'Controller_P7/Controller/GR LO/PID Controller/preInt Signal/Internal PreInt'
 * '<S112>' : 'Controller_P7/Controller/GR LO/PID Controller/preSat Signal/Forward_Path'
 * '<S113>' : 'Controller_P7/Controller/Omega HI/PID Controller'
 * '<S114>' : 'Controller_P7/Controller/Omega HI/PID Controller/Anti-windup'
 * '<S115>' : 'Controller_P7/Controller/Omega HI/PID Controller/D Gain'
 * '<S116>' : 'Controller_P7/Controller/Omega HI/PID Controller/External Derivative'
 * '<S117>' : 'Controller_P7/Controller/Omega HI/PID Controller/Filter'
 * '<S118>' : 'Controller_P7/Controller/Omega HI/PID Controller/Filter ICs'
 * '<S119>' : 'Controller_P7/Controller/Omega HI/PID Controller/I Gain'
 * '<S120>' : 'Controller_P7/Controller/Omega HI/PID Controller/Ideal P Gain'
 * '<S121>' : 'Controller_P7/Controller/Omega HI/PID Controller/Ideal P Gain Fdbk'
 * '<S122>' : 'Controller_P7/Controller/Omega HI/PID Controller/Integrator'
 * '<S123>' : 'Controller_P7/Controller/Omega HI/PID Controller/Integrator ICs'
 * '<S124>' : 'Controller_P7/Controller/Omega HI/PID Controller/N Copy'
 * '<S125>' : 'Controller_P7/Controller/Omega HI/PID Controller/N Gain'
 * '<S126>' : 'Controller_P7/Controller/Omega HI/PID Controller/P Copy'
 * '<S127>' : 'Controller_P7/Controller/Omega HI/PID Controller/Parallel P Gain'
 * '<S128>' : 'Controller_P7/Controller/Omega HI/PID Controller/Reset Signal'
 * '<S129>' : 'Controller_P7/Controller/Omega HI/PID Controller/Saturation'
 * '<S130>' : 'Controller_P7/Controller/Omega HI/PID Controller/Saturation Fdbk'
 * '<S131>' : 'Controller_P7/Controller/Omega HI/PID Controller/Sum'
 * '<S132>' : 'Controller_P7/Controller/Omega HI/PID Controller/Sum Fdbk'
 * '<S133>' : 'Controller_P7/Controller/Omega HI/PID Controller/Tracking Mode'
 * '<S134>' : 'Controller_P7/Controller/Omega HI/PID Controller/Tracking Mode Sum'
 * '<S135>' : 'Controller_P7/Controller/Omega HI/PID Controller/Tsamp - Integral'
 * '<S136>' : 'Controller_P7/Controller/Omega HI/PID Controller/Tsamp - Ngain'
 * '<S137>' : 'Controller_P7/Controller/Omega HI/PID Controller/postSat Signal'
 * '<S138>' : 'Controller_P7/Controller/Omega HI/PID Controller/preInt Signal'
 * '<S139>' : 'Controller_P7/Controller/Omega HI/PID Controller/preSat Signal'
 * '<S140>' : 'Controller_P7/Controller/Omega HI/PID Controller/Anti-windup/Passthrough'
 * '<S141>' : 'Controller_P7/Controller/Omega HI/PID Controller/D Gain/Internal Parameters'
 * '<S142>' : 'Controller_P7/Controller/Omega HI/PID Controller/External Derivative/External Ydot'
 * '<S143>' : 'Controller_P7/Controller/Omega HI/PID Controller/Filter/Disc. Forward Euler Filter Only'
 * '<S144>' : 'Controller_P7/Controller/Omega HI/PID Controller/Filter ICs/Internal IC - Filter'
 * '<S145>' : 'Controller_P7/Controller/Omega HI/PID Controller/I Gain/Internal Parameters'
 * '<S146>' : 'Controller_P7/Controller/Omega HI/PID Controller/Ideal P Gain/Passthrough'
 * '<S147>' : 'Controller_P7/Controller/Omega HI/PID Controller/Ideal P Gain Fdbk/Disabled'
 * '<S148>' : 'Controller_P7/Controller/Omega HI/PID Controller/Integrator/Discrete'
 * '<S149>' : 'Controller_P7/Controller/Omega HI/PID Controller/Integrator ICs/Internal IC'
 * '<S150>' : 'Controller_P7/Controller/Omega HI/PID Controller/N Copy/Disabled'
 * '<S151>' : 'Controller_P7/Controller/Omega HI/PID Controller/N Gain/Internal Parameters'
 * '<S152>' : 'Controller_P7/Controller/Omega HI/PID Controller/P Copy/Disabled'
 * '<S153>' : 'Controller_P7/Controller/Omega HI/PID Controller/Parallel P Gain/Internal Parameters'
 * '<S154>' : 'Controller_P7/Controller/Omega HI/PID Controller/Reset Signal/Disabled'
 * '<S155>' : 'Controller_P7/Controller/Omega HI/PID Controller/Saturation/Passthrough'
 * '<S156>' : 'Controller_P7/Controller/Omega HI/PID Controller/Saturation Fdbk/Disabled'
 * '<S157>' : 'Controller_P7/Controller/Omega HI/PID Controller/Sum/Sum_PID'
 * '<S158>' : 'Controller_P7/Controller/Omega HI/PID Controller/Sum Fdbk/Disabled'
 * '<S159>' : 'Controller_P7/Controller/Omega HI/PID Controller/Tracking Mode/Disabled'
 * '<S160>' : 'Controller_P7/Controller/Omega HI/PID Controller/Tracking Mode Sum/Passthrough'
 * '<S161>' : 'Controller_P7/Controller/Omega HI/PID Controller/Tsamp - Integral/TsSignalSpecification'
 * '<S162>' : 'Controller_P7/Controller/Omega HI/PID Controller/Tsamp - Ngain/Passthrough'
 * '<S163>' : 'Controller_P7/Controller/Omega HI/PID Controller/postSat Signal/Forward_Path'
 * '<S164>' : 'Controller_P7/Controller/Omega HI/PID Controller/preInt Signal/Internal PreInt'
 * '<S165>' : 'Controller_P7/Controller/Omega HI/PID Controller/preSat Signal/Forward_Path'
 * '<S166>' : 'Controller_P7/Controller/Omega LO/PID Controller'
 * '<S167>' : 'Controller_P7/Controller/Omega LO/PID Controller/Anti-windup'
 * '<S168>' : 'Controller_P7/Controller/Omega LO/PID Controller/D Gain'
 * '<S169>' : 'Controller_P7/Controller/Omega LO/PID Controller/External Derivative'
 * '<S170>' : 'Controller_P7/Controller/Omega LO/PID Controller/Filter'
 * '<S171>' : 'Controller_P7/Controller/Omega LO/PID Controller/Filter ICs'
 * '<S172>' : 'Controller_P7/Controller/Omega LO/PID Controller/I Gain'
 * '<S173>' : 'Controller_P7/Controller/Omega LO/PID Controller/Ideal P Gain'
 * '<S174>' : 'Controller_P7/Controller/Omega LO/PID Controller/Ideal P Gain Fdbk'
 * '<S175>' : 'Controller_P7/Controller/Omega LO/PID Controller/Integrator'
 * '<S176>' : 'Controller_P7/Controller/Omega LO/PID Controller/Integrator ICs'
 * '<S177>' : 'Controller_P7/Controller/Omega LO/PID Controller/N Copy'
 * '<S178>' : 'Controller_P7/Controller/Omega LO/PID Controller/N Gain'
 * '<S179>' : 'Controller_P7/Controller/Omega LO/PID Controller/P Copy'
 * '<S180>' : 'Controller_P7/Controller/Omega LO/PID Controller/Parallel P Gain'
 * '<S181>' : 'Controller_P7/Controller/Omega LO/PID Controller/Reset Signal'
 * '<S182>' : 'Controller_P7/Controller/Omega LO/PID Controller/Saturation'
 * '<S183>' : 'Controller_P7/Controller/Omega LO/PID Controller/Saturation Fdbk'
 * '<S184>' : 'Controller_P7/Controller/Omega LO/PID Controller/Sum'
 * '<S185>' : 'Controller_P7/Controller/Omega LO/PID Controller/Sum Fdbk'
 * '<S186>' : 'Controller_P7/Controller/Omega LO/PID Controller/Tracking Mode'
 * '<S187>' : 'Controller_P7/Controller/Omega LO/PID Controller/Tracking Mode Sum'
 * '<S188>' : 'Controller_P7/Controller/Omega LO/PID Controller/Tsamp - Integral'
 * '<S189>' : 'Controller_P7/Controller/Omega LO/PID Controller/Tsamp - Ngain'
 * '<S190>' : 'Controller_P7/Controller/Omega LO/PID Controller/postSat Signal'
 * '<S191>' : 'Controller_P7/Controller/Omega LO/PID Controller/preInt Signal'
 * '<S192>' : 'Controller_P7/Controller/Omega LO/PID Controller/preSat Signal'
 * '<S193>' : 'Controller_P7/Controller/Omega LO/PID Controller/Anti-windup/Passthrough'
 * '<S194>' : 'Controller_P7/Controller/Omega LO/PID Controller/D Gain/Internal Parameters'
 * '<S195>' : 'Controller_P7/Controller/Omega LO/PID Controller/External Derivative/External Ydot'
 * '<S196>' : 'Controller_P7/Controller/Omega LO/PID Controller/Filter/Disc. Forward Euler Filter Only'
 * '<S197>' : 'Controller_P7/Controller/Omega LO/PID Controller/Filter ICs/Internal IC - Filter'
 * '<S198>' : 'Controller_P7/Controller/Omega LO/PID Controller/I Gain/Internal Parameters'
 * '<S199>' : 'Controller_P7/Controller/Omega LO/PID Controller/Ideal P Gain/Passthrough'
 * '<S200>' : 'Controller_P7/Controller/Omega LO/PID Controller/Ideal P Gain Fdbk/Disabled'
 * '<S201>' : 'Controller_P7/Controller/Omega LO/PID Controller/Integrator/Discrete'
 * '<S202>' : 'Controller_P7/Controller/Omega LO/PID Controller/Integrator ICs/Internal IC'
 * '<S203>' : 'Controller_P7/Controller/Omega LO/PID Controller/N Copy/Disabled'
 * '<S204>' : 'Controller_P7/Controller/Omega LO/PID Controller/N Gain/Internal Parameters'
 * '<S205>' : 'Controller_P7/Controller/Omega LO/PID Controller/P Copy/Disabled'
 * '<S206>' : 'Controller_P7/Controller/Omega LO/PID Controller/Parallel P Gain/Internal Parameters'
 * '<S207>' : 'Controller_P7/Controller/Omega LO/PID Controller/Reset Signal/Disabled'
 * '<S208>' : 'Controller_P7/Controller/Omega LO/PID Controller/Saturation/Passthrough'
 * '<S209>' : 'Controller_P7/Controller/Omega LO/PID Controller/Saturation Fdbk/Disabled'
 * '<S210>' : 'Controller_P7/Controller/Omega LO/PID Controller/Sum/Sum_PID'
 * '<S211>' : 'Controller_P7/Controller/Omega LO/PID Controller/Sum Fdbk/Disabled'
 * '<S212>' : 'Controller_P7/Controller/Omega LO/PID Controller/Tracking Mode/Disabled'
 * '<S213>' : 'Controller_P7/Controller/Omega LO/PID Controller/Tracking Mode Sum/Passthrough'
 * '<S214>' : 'Controller_P7/Controller/Omega LO/PID Controller/Tsamp - Integral/TsSignalSpecification'
 * '<S215>' : 'Controller_P7/Controller/Omega LO/PID Controller/Tsamp - Ngain/Passthrough'
 * '<S216>' : 'Controller_P7/Controller/Omega LO/PID Controller/postSat Signal/Forward_Path'
 * '<S217>' : 'Controller_P7/Controller/Omega LO/PID Controller/preInt Signal/Internal PreInt'
 * '<S218>' : 'Controller_P7/Controller/Omega LO/PID Controller/preSat Signal/Forward_Path'
 * '<S219>' : 'Controller_P7/Filter/Kalman Filter'
 * '<S220>' : 'Controller_P7/Filter/Kalman Filter1'
 * '<S221>' : 'Controller_P7/Filter/Kalman Filter/Check Signal Attributes'
 * '<S222>' : 'Controller_P7/Filter/Kalman Filter/Control'
 * '<S223>' : 'Controller_P7/Filter/Kalman Filter/Control/Options'
 * '<S224>' : 'Controller_P7/Filter/Kalman Filter/Control/Options/Core'
 * '<S225>' : 'Controller_P7/Filter/Kalman Filter/Control/Options/P_prd_Assign'
 * '<S226>' : 'Controller_P7/Filter/Kalman Filter/Control/Options/X_est_Assign'
 * '<S227>' : 'Controller_P7/Filter/Kalman Filter/Control/Options/X_prd_Assign'
 * '<S228>' : 'Controller_P7/Filter/Kalman Filter/Control/Options/Core/LDL Solver'
 * '<S229>' : 'Controller_P7/Filter/Kalman Filter/Control/Options/Core/LDL Solver/Check Signal Attributes'
 * '<S230>' : 'Controller_P7/Filter/Kalman Filter/Control/Options/Core/LDL Solver/Check Signal Attributes1'
 * '<S231>' : 'Controller_P7/Filter/Kalman Filter/Control/Options/Core/LDL Solver/Check Signal Attributes2'
 * '<S232>' : 'Controller_P7/Filter/Kalman Filter1/Check Signal Attributes'
 * '<S233>' : 'Controller_P7/Filter/Kalman Filter1/Control'
 * '<S234>' : 'Controller_P7/Filter/Kalman Filter1/Control/Options'
 * '<S235>' : 'Controller_P7/Filter/Kalman Filter1/Control/Options/Core'
 * '<S236>' : 'Controller_P7/Filter/Kalman Filter1/Control/Options/P_prd_Assign'
 * '<S237>' : 'Controller_P7/Filter/Kalman Filter1/Control/Options/X_est_Assign'
 * '<S238>' : 'Controller_P7/Filter/Kalman Filter1/Control/Options/X_prd_Assign'
 * '<S239>' : 'Controller_P7/Filter/Kalman Filter1/Control/Options/Core/LDL Solver'
 * '<S240>' : 'Controller_P7/Filter/Kalman Filter1/Control/Options/Core/LDL Solver/Check Signal Attributes'
 * '<S241>' : 'Controller_P7/Filter/Kalman Filter1/Control/Options/Core/LDL Solver/Check Signal Attributes1'
 * '<S242>' : 'Controller_P7/Filter/Kalman Filter1/Control/Options/Core/LDL Solver/Check Signal Attributes2'
 */
#endif                                 /* Controller_P7_h_ */
