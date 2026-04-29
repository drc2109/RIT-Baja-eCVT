/*
 * Controller_P7.c
 *
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * Code generation for model "Controller_P7".
 *
 * Model version              : 5.40
 * Simulink Coder version : 25.2 (R2025b) 28-Jul-2025
 * C source code generated on : Tue Apr 28 23:59:44 2026
 *
 * Target selection: grt.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: ARM Compatible->ARM Cortex-M
 * Code generation objective: Debugging
 * Validation result: Not run
 */

#include "Controller_P7.h"
#include "rtwtypes.h"
#include <string.h>
#include "Controller_P7_private.h"

/* Named constants for Chart: '<S1>/Chart' */
#define Controller_P7_IN_Clamping      ((uint8_T)1U)
#define Controller_P7_IN_EngineOff     ((uint8_T)2U)
#define Controller_P7_IN_Idle          ((uint8_T)3U)
#define Controller_P7_IN_Overdrive     ((uint8_T)4U)
#define Controller_P7_IN_Reving        ((uint8_T)5U)
#define Controller_P7_IN_Shifting      ((uint8_T)6U)
#define Controller_P7_Omega_High       (314.15926535897933)
#define Controller_P7_Phi_max          (3.15)
#define Controller_P7_Phi_min          (0.8)
#define Controller_P_IN_NO_ACTIVE_CHILD ((uint8_T)0U)

/* Block signals (default storage) */
B_Controller_P7_T Controller_P7_B;

/* Block states (default storage) */
DW_Controller_P7_T Controller_P7_DW;

/* External inputs (root inport signals with default storage) */
ExtU_Controller_P7_T Controller_P7_U;

/* External outputs (root outports fed by signals with default storage) */
ExtY_Controller_P7_T Controller_P7_Y;

/* Real-time model */
static RT_MODEL_Controller_P7_T Controller_P7_M_;
RT_MODEL_Controller_P7_T *const Controller_P7_M = &Controller_P7_M_;
void LDLf_int32_Treal32_T(real32_T out[], real32_T vArray[], int32_T nRows,
  const real32_T in[])
{
  int32_T c;
  int32_T k;
  int32_T r;
  real32_T mYTmp;
  boolean_T done;

  /* S-Function (sdspldl2): '<S285>/LDL Factorization' */
  done = false;

  /* use done to control the for loop return early  */
  /* when non-positive definite eigenvalue is detected */
  c = 0;
  while ((c < nRows) && (!done)) {
    int32_T idx1;
    int32_T idx2;
    int32_T mYTmp_tmp;
    real32_T mYTmpR;
    real32_T prod;
    idx2 = c * nRows;
    for (r = 0; r < c; r++) {
      idx1 = r * nRows;
      mYTmp = out[idx1 + c];
      mYTmpR = out[idx1 + r];
      vArray[r] = mYTmp * mYTmpR;
    }

    mYTmp_tmp = idx2 + c;
    mYTmp = in[mYTmp_tmp];
    idx1 = c;
    for (r = 0; r < c; r++) {
      prod = out[idx1] * vArray[r];
      mYTmp -= prod;
      idx1 += nRows;
    }

    mYTmpR = mYTmp;
    if (mYTmpR <= 0.0F) {
      done = true;
    } else {
      out[mYTmp_tmp] = mYTmp;
      for (r = c + 1; r < nRows; r++) {
        mYTmp_tmp = idx2 + r;
        mYTmp = in[mYTmp_tmp];
        idx1 = r;
        for (k = 0; k < c; k++) {
          prod = out[idx1] * vArray[k];
          mYTmp -= prod;
          idx1 += nRows;
        }

        out[mYTmp_tmp] = mYTmp / mYTmpR;
      }
    }

    c++;
  }

  /* transpose and copy lower sub-triang to upper */
  c = 0;
  while ((c < nRows) && (!done)) {
    for (r = c + 1; r < nRows; r++) {
      mYTmp = out[c * nRows + r];
      out[r * nRows + c] = mYTmp;
    }

    c++;
  }

  /* End of S-Function (sdspldl2): '<S285>/LDL Factorization' */
}

/* Model step function */
void Controller_P7_step(void)
{
  real_T u0;
  real_T u1;
  real_T u2;
  int32_T i;
  int32_T idxS;
  int32_T idxV;
  int32_T k;
  int32_T s279_iter;
  real32_T tmp_0[16];
  real32_T tmp_2[16];
  real32_T v1_0[16];
  real32_T tmp[8];
  real32_T tmp_1[8];
  real32_T v1[8];
  real32_T tmp_3[4];
  real32_T tmp_4[2];
  real32_T HP_prdt;
  real32_T HP_prdt_0;
  real32_T KHP_prd;
  real32_T KHP_prd_0;
  real32_T UnitDelay3;

  /* RelationalOperator: '<S9>/GreaterThan' incorporates:
   *  Constant: '<S9>/Constant'
   *  Inport: '<Root>/Theta_Helix'
   */
  Controller_P7_B.GreaterThan = (Controller_P7_U.Theta_Helix <
    Controller_P7_P.Constant_Value_c);

  /* UnitDelay: '<S277>/Unit Delay2' */
  Controller_P7_B.UnitDelay2[0] = Controller_P7_DW.UnitDelay2_DSTATE[0];
  Controller_P7_B.UnitDelay2[1] = Controller_P7_DW.UnitDelay2_DSTATE[1];
  Controller_P7_B.UnitDelay2[2] = Controller_P7_DW.UnitDelay2_DSTATE[2];
  Controller_P7_B.UnitDelay2[3] = Controller_P7_DW.UnitDelay2_DSTATE[3];

  /* Outputs for Iterator SubSystem: '<S277>/Control' incorporates:
   *  ForIterator: '<S279>/Iterator'
   */
  for (i = 0; i < 16; i++) {
    /* UnitDelay: '<S277>/Unit Delay3' */
    UnitDelay3 = Controller_P7_DW.UnitDelay3_DSTATE[i];
    Controller_P7_B.UnitDelay3[i] = UnitDelay3;

    /* Assignment: '<S282>/Assignment' incorporates:
     *  UnitDelay: '<S277>/Unit Delay3'
     */
    Controller_P7_B.Assignment[i] = UnitDelay3;
  }

  /* Assignment: '<S284>/Assignment' incorporates:
   *  UnitDelay: '<S277>/Unit Delay2'
   */
  Controller_P7_B.Assignment_a[0] = Controller_P7_B.UnitDelay2[0];
  Controller_P7_B.Assignment_a[1] = Controller_P7_B.UnitDelay2[1];
  Controller_P7_B.Assignment_a[2] = Controller_P7_B.UnitDelay2[2];
  Controller_P7_B.Assignment_a[3] = Controller_P7_B.UnitDelay2[3];
  s279_iter = 1;
  if (Controller_P7_P.Iterator_IterationLimit >= 1) {
    /* Selector: '<S280>/Selector1' incorporates:
     *  UnitDelay: '<S277>/Unit Delay2'
     */
    Controller_P7_B.Selector1[0] = Controller_P7_B.UnitDelay2[0];
    Controller_P7_B.Selector1[1] = Controller_P7_B.UnitDelay2[1];
    Controller_P7_B.Selector1[2] = Controller_P7_B.UnitDelay2[2];
    Controller_P7_B.Selector1[3] = Controller_P7_B.UnitDelay2[3];

    /* SignalConversion generated from: '<S280>/Selector' incorporates:
     *  Inport: '<Root>/Omega_Primary'
     *  Inport: '<Root>/Omega_Secondary'
     */
    Controller_P7_B.TmpSignalConversionAtSelectorIn[0] =
      Controller_P7_U.Omega_Primary;
    Controller_P7_B.TmpSignalConversionAtSelectorIn[1] =
      Controller_P7_U.Omega_Secondary;

    /* Selector: '<S280>/Selector' incorporates:
     *  SignalConversion generated from: '<S280>/Selector'
     */
    Controller_P7_B.Selector[0] =
      Controller_P7_B.TmpSignalConversionAtSelectorIn[0];
    Controller_P7_B.Selector[1] =
      Controller_P7_B.TmpSignalConversionAtSelectorIn[1];

    /* Selector: '<S280>/Selector2' incorporates:
     *  UnitDelay: '<S277>/Unit Delay3'
     */
    memcpy(&Controller_P7_B.Selector2[0], &Controller_P7_B.UnitDelay3[0], sizeof
           (real32_T) << 4U);
    for (i = 0; i < 4; i++) {
      /* Math: '<S281>/P_prd Trans' */
      idxS = i << 2;

      /* Math: '<S281>/P_prd Trans' incorporates:
       *  Selector: '<S280>/Selector2'
       */
      Controller_P7_B.P_prdTrans[idxS] = Controller_P7_B.Selector2[i];
      Controller_P7_B.P_prdTrans[idxS + 1] = Controller_P7_B.Selector2[i + 4];
      Controller_P7_B.P_prdTrans[idxS + 2] = Controller_P7_B.Selector2[i + 8];
      Controller_P7_B.P_prdTrans[idxS + 3] = Controller_P7_B.Selector2[i + 12];
    }

    /* Product: '<S281>/H*P_prdt' incorporates:
     *  Constant: '<S281>/Hcst'
     */
    for (i = 0; i < 8; i++) {
      tmp[i] = Controller_P7_P.Hcst_Value[i];
    }
  }

  while (s279_iter <= Controller_P7_P.Iterator_IterationLimit) {
    /* Outputs for Iterator SubSystem: '<S277>/Control' incorporates:
     *  ForIterator: '<S279>/Iterator'
     */
    Controller_P7_B.Iterator = s279_iter;

    /* Product: '<S281>/H*P_prdt' incorporates:
     *  Math: '<S281>/P_prd Trans'
     */
    memcpy(&tmp_0[0], &Controller_P7_B.P_prdTrans[0], sizeof(real32_T) << 4U);
    for (i = 0; i < 4; i++) {
      HP_prdt = 0.0F;
      HP_prdt_0 = 0.0F;
      for (idxS = 0; idxS < 4; idxS++) {
        UnitDelay3 = tmp_0[(i << 2) + idxS];
        idxV = idxS << 1;
        HP_prdt += tmp[idxV] * UnitDelay3;
        HP_prdt_0 += tmp[idxV + 1] * UnitDelay3;
      }

      idxV = i << 1;
      Controller_P7_B.HP_prdt[idxV + 1] = HP_prdt_0;
      Controller_P7_B.HP_prdt[idxV] = HP_prdt;
    }

    /* Product: '<S281>/H*P_prdt*Ht' incorporates:
     *  Constant: '<S281>/Hcst_t'
     *  Product: '<S281>/H*P_prdt'
     */
    for (i = 0; i < 8; i++) {
      tmp_1[i] = Controller_P7_B.HP_prdt[i];
      v1[i] = Controller_P7_P.Hcst_t_Value[i];
    }

    for (i = 0; i < 2; i++) {
      HP_prdt = 0.0F;
      HP_prdt_0 = 0.0F;
      for (idxS = 0; idxS < 4; idxS++) {
        UnitDelay3 = v1[(i << 2) + idxS];
        idxV = idxS << 1;
        HP_prdt += tmp_1[idxV] * UnitDelay3;
        HP_prdt_0 += tmp_1[idxV + 1] * UnitDelay3;
      }

      idxV = i << 1;
      Controller_P7_B.HP_prdtHt[idxV + 1] = HP_prdt_0;
      Controller_P7_B.HP_prdtHt[idxV] = HP_prdt;
    }

    /* End of Product: '<S281>/H*P_prdt*Ht' */

    /* Sum: '<S281>/H*P_prdt*Ht+R' incorporates:
     *  Constant: '<S281>/Constant2'
     *  Product: '<S281>/H*P_prdt*Ht'
     */
    UnitDelay3 = Controller_P7_B.HP_prdtHt[0] +
      Controller_P7_P.Constant2_Value_k[0];
    Controller_P7_B.HP_prdtHtR[0] = UnitDelay3;

    /* S-Function (sdspldl2): '<S285>/LDL Factorization' incorporates:
     *  Sum: '<S281>/H*P_prdt*Ht+R'
     */
    Controller_P7_B.LDLFactorization[0] = UnitDelay3;

    /* Sum: '<S281>/H*P_prdt*Ht+R' incorporates:
     *  Constant: '<S281>/Constant2'
     *  Product: '<S281>/H*P_prdt*Ht'
     */
    UnitDelay3 = Controller_P7_B.HP_prdtHt[1] +
      Controller_P7_P.Constant2_Value_k[1];
    Controller_P7_B.HP_prdtHtR[1] = UnitDelay3;

    /* S-Function (sdspldl2): '<S285>/LDL Factorization' incorporates:
     *  Sum: '<S281>/H*P_prdt*Ht+R'
     */
    Controller_P7_B.LDLFactorization[1] = UnitDelay3;

    /* Sum: '<S281>/H*P_prdt*Ht+R' incorporates:
     *  Constant: '<S281>/Constant2'
     *  Product: '<S281>/H*P_prdt*Ht'
     */
    UnitDelay3 = Controller_P7_B.HP_prdtHt[2] +
      Controller_P7_P.Constant2_Value_k[2];
    Controller_P7_B.HP_prdtHtR[2] = UnitDelay3;

    /* S-Function (sdspldl2): '<S285>/LDL Factorization' incorporates:
     *  Sum: '<S281>/H*P_prdt*Ht+R'
     */
    Controller_P7_B.LDLFactorization[2] = UnitDelay3;

    /* Sum: '<S281>/H*P_prdt*Ht+R' incorporates:
     *  Constant: '<S281>/Constant2'
     *  Product: '<S281>/H*P_prdt*Ht'
     */
    UnitDelay3 = Controller_P7_B.HP_prdtHt[3] +
      Controller_P7_P.Constant2_Value_k[3];
    Controller_P7_B.HP_prdtHtR[3] = UnitDelay3;

    /* S-Function (sdspldl2): '<S285>/LDL Factorization' incorporates:
     *  Sum: '<S281>/H*P_prdt*Ht+R'
     */
    Controller_P7_B.LDLFactorization[3] = UnitDelay3;

    /* S-Function (sdspldl2): '<S285>/LDL Factorization' incorporates:
     *  Sum: '<S281>/H*P_prdt*Ht+R'
     */
    LDLf_int32_Treal32_T(&Controller_P7_B.LDLFactorization[0U],
                         &Controller_P7_DW.LDLFactorization_VMX[0U], 2,
                         &Controller_P7_B.HP_prdtHtR[0U]);

    /* S-Function (sdspfbsub2): '<S285>/Forward Substitution' incorporates:
     *  Product: '<S281>/H*P_prdt'
     *  S-Function (sdspldl2): '<S285>/LDL Factorization'
     */
    Controller_P7_B.y[0] = Controller_P7_B.HP_prdt[0];
    UnitDelay3 = Controller_P7_B.HP_prdt[1];
    UnitDelay3 -= Controller_P7_B.y[0] * Controller_P7_B.LDLFactorization[1];
    Controller_P7_B.y[1] = UnitDelay3;
    Controller_P7_B.y[2] = Controller_P7_B.HP_prdt[2];
    UnitDelay3 = Controller_P7_B.HP_prdt[3];
    UnitDelay3 -= Controller_P7_B.LDLFactorization[1] * Controller_P7_B.y[2];
    Controller_P7_B.y[3] = UnitDelay3;
    Controller_P7_B.y[4] = Controller_P7_B.HP_prdt[4];
    UnitDelay3 = Controller_P7_B.HP_prdt[5];
    UnitDelay3 -= Controller_P7_B.LDLFactorization[1] * Controller_P7_B.y[4];
    Controller_P7_B.y[5] = UnitDelay3;
    Controller_P7_B.y[6] = Controller_P7_B.HP_prdt[6];
    UnitDelay3 = Controller_P7_B.HP_prdt[7];
    UnitDelay3 -= Controller_P7_B.LDLFactorization[1] * Controller_P7_B.y[6];
    Controller_P7_B.y[7] = UnitDelay3;

    /* S-Function (sdspdiag2): '<S285>/Extract Diagonal' incorporates:
     *  S-Function (sdspldl2): '<S285>/LDL Factorization'
     */
    Controller_P7_B.d[0] = Controller_P7_B.LDLFactorization[0];

    /* Math: '<S285>/Math Function'
     *
     * About '<S285>/Math Function':
     *  Operator: reciprocal
     */
    UnitDelay3 = Controller_P7_B.d[0];
    UnitDelay3 = 1.0F / UnitDelay3;

    /* Math: '<S285>/Math Function'
     *
     * About '<S285>/Math Function':
     *  Operator: reciprocal
     */
    Controller_P7_B.MathFunction[0] = UnitDelay3;

    /* S-Function (sdspdiag2): '<S285>/Extract Diagonal' incorporates:
     *  S-Function (sdspldl2): '<S285>/LDL Factorization'
     */
    Controller_P7_B.d[1] = Controller_P7_B.LDLFactorization[3];

    /* Math: '<S285>/Math Function'
     *
     * About '<S285>/Math Function':
     *  Operator: reciprocal
     */
    UnitDelay3 = Controller_P7_B.d[1];
    UnitDelay3 = 1.0F / UnitDelay3;

    /* Math: '<S285>/Math Function'
     *
     * About '<S285>/Math Function':
     *  Operator: reciprocal
     */
    Controller_P7_B.MathFunction[1] = UnitDelay3;

    /* S-Function (sdspdmult2): '<S285>/Matrix Scaling' incorporates:
     *  S-Function (sdspfbsub2): '<S285>/Forward Substitution'
     */
    idxS = 0;
    for (i = 0; i < 4; i++) {
      idxV = 0;
      for (k = 0; k < 2; k++) {
        Controller_P7_B.MatrixScaling[idxS] = Controller_P7_B.y[idxS] *
          Controller_P7_B.MathFunction[idxV];
        idxS++;
        idxV++;
      }
    }

    /* End of S-Function (sdspdmult2): '<S285>/Matrix Scaling' */

    /* S-Function (sdspfbsub2): '<S285>/Backward Substitution' incorporates:
     *  S-Function (sdspdmult2): '<S285>/Matrix Scaling'
     *  S-Function (sdspldl2): '<S285>/LDL Factorization'
     */
    Controller_P7_B.BackwardSubstitution[1] = Controller_P7_B.MatrixScaling[1];
    UnitDelay3 = Controller_P7_B.MatrixScaling[0];
    UnitDelay3 -= Controller_P7_B.BackwardSubstitution[1] *
      Controller_P7_B.LDLFactorization[2];
    Controller_P7_B.BackwardSubstitution[0] = UnitDelay3;
    Controller_P7_B.BackwardSubstitution[3] = Controller_P7_B.MatrixScaling[3];
    UnitDelay3 = Controller_P7_B.MatrixScaling[2];
    UnitDelay3 -= Controller_P7_B.LDLFactorization[2] *
      Controller_P7_B.BackwardSubstitution[3];
    Controller_P7_B.BackwardSubstitution[2] = UnitDelay3;
    Controller_P7_B.BackwardSubstitution[5] = Controller_P7_B.MatrixScaling[5];
    UnitDelay3 = Controller_P7_B.MatrixScaling[4];
    UnitDelay3 -= Controller_P7_B.LDLFactorization[2] *
      Controller_P7_B.BackwardSubstitution[5];
    Controller_P7_B.BackwardSubstitution[4] = UnitDelay3;
    Controller_P7_B.BackwardSubstitution[7] = Controller_P7_B.MatrixScaling[7];
    UnitDelay3 = Controller_P7_B.MatrixScaling[6];
    UnitDelay3 -= Controller_P7_B.LDLFactorization[2] *
      Controller_P7_B.BackwardSubstitution[7];
    Controller_P7_B.BackwardSubstitution[6] = UnitDelay3;
    for (i = 0; i < 2; i++) {
      /* Math: '<S281>/K Trans' */
      idxS = i << 2;

      /* Math: '<S281>/K Trans' incorporates:
       *  S-Function (sdspfbsub2): '<S285>/Backward Substitution'
       */
      Controller_P7_B.KTrans[idxS] = Controller_P7_B.BackwardSubstitution[i];
      Controller_P7_B.KTrans[idxS + 1] = Controller_P7_B.BackwardSubstitution[i
        + 2];
      Controller_P7_B.KTrans[idxS + 2] = Controller_P7_B.BackwardSubstitution[i
        + 4];
      Controller_P7_B.KTrans[idxS + 3] = Controller_P7_B.BackwardSubstitution[i
        + 6];
    }

    /* Product: '<S281>/K*H*P_prd' incorporates:
     *  Math: '<S281>/K Trans'
     *  Selector: '<S280>/Selector2'
     */
    memcpy(&tmp_0[0], &Controller_P7_B.Selector2[0], sizeof(real32_T) << 4U);
    for (i = 0; i < 4; i++) {
      HP_prdt = 0.0F;
      HP_prdt_0 = 0.0F;
      for (idxS = 0; idxS < 4; idxS++) {
        UnitDelay3 = tmp_0[(i << 2) + idxS];
        idxV = idxS << 1;
        HP_prdt += tmp[idxV] * UnitDelay3;
        HP_prdt_0 += tmp[idxV + 1] * UnitDelay3;
      }

      idxV = i << 1;
      v1[idxV + 1] = HP_prdt_0;
      v1[idxV] = HP_prdt;
    }

    for (i = 0; i < 8; i++) {
      tmp_1[i] = Controller_P7_B.KTrans[i];
    }

    for (i = 0; i < 4; i++) {
      HP_prdt = 0.0F;
      HP_prdt_0 = 0.0F;
      KHP_prd = 0.0F;
      KHP_prd_0 = 0.0F;
      for (idxS = 0; idxS < 2; idxS++) {
        UnitDelay3 = v1[(i << 1) + idxS];
        idxV = idxS << 2;
        HP_prdt += tmp_1[idxV] * UnitDelay3;
        HP_prdt_0 += tmp_1[idxV + 1] * UnitDelay3;
        KHP_prd += tmp_1[idxV + 2] * UnitDelay3;
        KHP_prd_0 += tmp_1[idxV + 3] * UnitDelay3;
      }

      idxV = i << 2;
      Controller_P7_B.KHP_prd[idxV + 3] = KHP_prd_0;
      Controller_P7_B.KHP_prd[idxV + 2] = KHP_prd;
      Controller_P7_B.KHP_prd[idxV + 1] = HP_prdt_0;
      Controller_P7_B.KHP_prd[idxV] = HP_prdt;
    }

    /* End of Product: '<S281>/K*H*P_prd' */
    for (i = 0; i < 16; i++) {
      /* Sum: '<S281>/P_prd-K*H*P_prd' incorporates:
       *  Product: '<S281>/K*H*P_prd'
       *  Selector: '<S280>/Selector2'
       */
      UnitDelay3 = Controller_P7_B.Selector2[i] - Controller_P7_B.KHP_prd[i];
      Controller_P7_B.P_prdKHP_prd[i] = UnitDelay3;

      /* Product: '<S281>/A*P*At' incorporates:
       *  Constant: '<S281>/Constant4'
       *  Sum: '<S281>/P_prd-K*H*P_prd'
       */
      tmp_0[i] = UnitDelay3;
      tmp_2[i] = Controller_P7_P.Constant4_Value_j[i];
    }

    /* Product: '<S281>/A*P*At' incorporates:
     *  Constant: '<S281>/Constant3'
     */
    for (i = 0; i < 4; i++) {
      HP_prdt = 0.0F;
      HP_prdt_0 = 0.0F;
      KHP_prd = 0.0F;
      KHP_prd_0 = 0.0F;
      for (idxS = 0; idxS < 4; idxS++) {
        UnitDelay3 = tmp_2[(i << 2) + idxS];
        idxV = idxS << 2;
        HP_prdt += tmp_0[idxV] * UnitDelay3;
        HP_prdt_0 += tmp_0[idxV + 1] * UnitDelay3;
        KHP_prd += tmp_0[idxV + 2] * UnitDelay3;
        KHP_prd_0 += tmp_0[idxV + 3] * UnitDelay3;
      }

      idxV = i << 2;
      v1_0[idxV + 3] = KHP_prd_0;
      v1_0[idxV + 2] = KHP_prd;
      v1_0[idxV + 1] = HP_prdt_0;
      v1_0[idxV] = HP_prdt;
    }

    memcpy(&tmp_0[0], &Controller_P7_P.Constant3_Value_a[0], sizeof(real32_T) <<
           4U);
    for (i = 0; i < 4; i++) {
      HP_prdt = 0.0F;
      HP_prdt_0 = 0.0F;
      KHP_prd = 0.0F;
      KHP_prd_0 = 0.0F;
      for (idxS = 0; idxS < 4; idxS++) {
        UnitDelay3 = v1_0[(i << 2) + idxS];
        idxV = idxS << 2;
        HP_prdt += tmp_0[idxV] * UnitDelay3;
        HP_prdt_0 += tmp_0[idxV + 1] * UnitDelay3;
        KHP_prd += tmp_0[idxV + 2] * UnitDelay3;
        KHP_prd_0 += tmp_0[idxV + 3] * UnitDelay3;
      }

      idxV = i << 2;
      Controller_P7_B.APAt[idxV + 3] = KHP_prd_0;
      Controller_P7_B.APAt[idxV + 2] = KHP_prd;
      Controller_P7_B.APAt[idxV + 1] = HP_prdt_0;
      Controller_P7_B.APAt[idxV] = HP_prdt;
    }

    for (i = 0; i < 16; i++) {
      /* Sum: '<S281>/A*P*At+Q' incorporates:
       *  Constant: '<S281>/Constant5'
       *  Product: '<S281>/A*P*At'
       */
      Controller_P7_B.APAtQ[i] = Controller_P7_B.APAt[i] +
        Controller_P7_P.Constant5_Value[i];
    }

    /* Product: '<S281>/H*X_prd' incorporates:
     *  Selector: '<S280>/Selector1'
     */
    tmp_3[0] = Controller_P7_B.Selector1[0];
    tmp_3[1] = Controller_P7_B.Selector1[1];
    tmp_3[2] = Controller_P7_B.Selector1[2];
    tmp_3[3] = Controller_P7_B.Selector1[3];
    HP_prdt = 0.0F;
    HP_prdt_0 = 0.0F;
    for (i = 0; i < 4; i++) {
      UnitDelay3 = tmp_3[i];
      idxS = i << 1;
      HP_prdt += tmp[idxS] * UnitDelay3;
      HP_prdt_0 += tmp[idxS + 1] * UnitDelay3;
    }

    Controller_P7_B.HX_prd[1] = HP_prdt_0;
    Controller_P7_B.HX_prd[0] = HP_prdt;

    /* End of Product: '<S281>/H*X_prd' */

    /* Sum: '<S281>/Z-H*X_prd' incorporates:
     *  Product: '<S281>/H*X_prd'
     *  Selector: '<S280>/Selector'
     */
    UnitDelay3 = Controller_P7_B.Selector[0] - Controller_P7_B.HX_prd[0];
    Controller_P7_B.ZHX_prd[0] = UnitDelay3;

    /* Product: '<S281>/K*(Z-H*X_prd)' incorporates:
     *  Sum: '<S281>/Z-H*X_prd'
     */
    tmp_4[0] = UnitDelay3;

    /* Sum: '<S281>/Z-H*X_prd' incorporates:
     *  Product: '<S281>/H*X_prd'
     *  Selector: '<S280>/Selector'
     */
    UnitDelay3 = Controller_P7_B.Selector[1] - Controller_P7_B.HX_prd[1];
    Controller_P7_B.ZHX_prd[1] = UnitDelay3;

    /* Product: '<S281>/K*(Z-H*X_prd)' incorporates:
     *  Sum: '<S281>/Z-H*X_prd'
     */
    tmp_4[1] = UnitDelay3;
    HP_prdt = 0.0F;
    HP_prdt_0 = 0.0F;
    KHP_prd = 0.0F;
    KHP_prd_0 = 0.0F;
    for (i = 0; i < 2; i++) {
      UnitDelay3 = tmp_4[i];
      idxS = i << 2;
      HP_prdt += tmp_1[idxS] * UnitDelay3;
      HP_prdt_0 += tmp_1[idxS + 1] * UnitDelay3;
      KHP_prd += tmp_1[idxS + 2] * UnitDelay3;
      KHP_prd_0 += tmp_1[idxS + 3] * UnitDelay3;
    }

    Controller_P7_B.KZHX_prd[3] = KHP_prd_0;
    Controller_P7_B.KZHX_prd[2] = KHP_prd;
    Controller_P7_B.KZHX_prd[1] = HP_prdt_0;
    Controller_P7_B.KZHX_prd[0] = HP_prdt;

    /* Sum: '<S281>/X_prd+K*(Z-H*X_prd)' incorporates:
     *  Product: '<S281>/K*(Z-H*X_prd)'
     *  Selector: '<S280>/Selector1'
     */
    UnitDelay3 = Controller_P7_B.Selector1[0] + Controller_P7_B.KZHX_prd[0];
    Controller_P7_B.X_prdKZHX_prd[0] = UnitDelay3;

    /* Product: '<S281>/A*X' incorporates:
     *  Sum: '<S281>/X_prd+K*(Z-H*X_prd)'
     */
    tmp_3[0] = UnitDelay3;

    /* Sum: '<S281>/X_prd+K*(Z-H*X_prd)' incorporates:
     *  Product: '<S281>/K*(Z-H*X_prd)'
     *  Selector: '<S280>/Selector1'
     */
    UnitDelay3 = Controller_P7_B.Selector1[1] + Controller_P7_B.KZHX_prd[1];
    Controller_P7_B.X_prdKZHX_prd[1] = UnitDelay3;

    /* Product: '<S281>/A*X' incorporates:
     *  Sum: '<S281>/X_prd+K*(Z-H*X_prd)'
     */
    tmp_3[1] = UnitDelay3;

    /* Sum: '<S281>/X_prd+K*(Z-H*X_prd)' incorporates:
     *  Product: '<S281>/K*(Z-H*X_prd)'
     *  Selector: '<S280>/Selector1'
     */
    UnitDelay3 = Controller_P7_B.Selector1[2] + Controller_P7_B.KZHX_prd[2];
    Controller_P7_B.X_prdKZHX_prd[2] = UnitDelay3;

    /* Product: '<S281>/A*X' incorporates:
     *  Sum: '<S281>/X_prd+K*(Z-H*X_prd)'
     */
    tmp_3[2] = UnitDelay3;

    /* Sum: '<S281>/X_prd+K*(Z-H*X_prd)' incorporates:
     *  Product: '<S281>/K*(Z-H*X_prd)'
     *  Selector: '<S280>/Selector1'
     */
    UnitDelay3 = Controller_P7_B.Selector1[3] + Controller_P7_B.KZHX_prd[3];
    Controller_P7_B.X_prdKZHX_prd[3] = UnitDelay3;

    /* Product: '<S281>/A*X' incorporates:
     *  Sum: '<S281>/X_prd+K*(Z-H*X_prd)'
     */
    tmp_3[3] = UnitDelay3;
    HP_prdt = 0.0F;
    HP_prdt_0 = 0.0F;
    KHP_prd = 0.0F;
    KHP_prd_0 = 0.0F;
    for (i = 0; i < 4; i++) {
      UnitDelay3 = tmp_3[i];
      idxS = i << 2;
      HP_prdt += tmp_0[idxS] * UnitDelay3;
      HP_prdt_0 += tmp_0[idxS + 1] * UnitDelay3;
      KHP_prd += tmp_0[idxS + 2] * UnitDelay3;
      KHP_prd_0 += tmp_0[idxS + 3] * UnitDelay3;
    }

    Controller_P7_B.AX[3] = KHP_prd_0;
    Controller_P7_B.AX[2] = KHP_prd;
    Controller_P7_B.AX[1] = HP_prdt_0;
    Controller_P7_B.AX[0] = HP_prdt;

    /* Assignment: '<S282>/Assignment' incorporates:
     *  Sum: '<S281>/A*P*At+Q'
     */
    memcpy(&Controller_P7_B.Assignment[0], &Controller_P7_B.APAtQ[0], sizeof
           (real32_T) << 4U);

    /* Assignment: '<S283>/Assignment' incorporates:
     *  Sum: '<S281>/X_prd+K*(Z-H*X_prd)'
     */
    Controller_P7_B.Assignment_c[0] = Controller_P7_B.X_prdKZHX_prd[0];

    /* Assignment: '<S284>/Assignment' incorporates:
     *  Product: '<S281>/A*X'
     */
    Controller_P7_B.Assignment_a[0] = Controller_P7_B.AX[0];

    /* Assignment: '<S283>/Assignment' incorporates:
     *  Sum: '<S281>/X_prd+K*(Z-H*X_prd)'
     */
    Controller_P7_B.Assignment_c[1] = Controller_P7_B.X_prdKZHX_prd[1];

    /* Assignment: '<S284>/Assignment' incorporates:
     *  Product: '<S281>/A*X'
     */
    Controller_P7_B.Assignment_a[1] = Controller_P7_B.AX[1];

    /* Assignment: '<S283>/Assignment' incorporates:
     *  Sum: '<S281>/X_prd+K*(Z-H*X_prd)'
     */
    Controller_P7_B.Assignment_c[2] = Controller_P7_B.X_prdKZHX_prd[2];

    /* Assignment: '<S284>/Assignment' incorporates:
     *  Product: '<S281>/A*X'
     */
    Controller_P7_B.Assignment_a[2] = Controller_P7_B.AX[2];

    /* Assignment: '<S283>/Assignment' incorporates:
     *  Sum: '<S281>/X_prd+K*(Z-H*X_prd)'
     */
    Controller_P7_B.Assignment_c[3] = Controller_P7_B.X_prdKZHX_prd[3];

    /* Assignment: '<S284>/Assignment' incorporates:
     *  Product: '<S281>/A*X'
     */
    Controller_P7_B.Assignment_a[3] = Controller_P7_B.AX[3];
    s279_iter++;
  }

  /* End of Outputs for SubSystem: '<S277>/Control' */

  /* Outport: '<Root>/CVT_Ratio' incorporates:
   *  Product: '<S2>/Divide'
   */
  Controller_P7_Y.CVT_Ratio = Controller_P7_B.Assignment_c[0] /
    Controller_P7_B.Assignment_c[2];

  /* Chart: '<S1>/Chart' incorporates:
   *  Outport: '<Root>/CVT_Ratio'
   */
  if (Controller_P7_DW.temporalCounter_i1 < 8191) {
    Controller_P7_DW.temporalCounter_i1++;
  }

  if (Controller_P7_DW.is_active_c3_Controller_P7 == 0) {
    Controller_P7_DW.is_active_c3_Controller_P7 = 1U;
    Controller_P7_DW.is_c3_Controller_P7 = Controller_P7_IN_EngineOff;

    /* :  mode = 0; */
    Controller_P7_B.mode = 0.0;
  } else {
    switch (Controller_P7_DW.is_c3_Controller_P7) {
     case Controller_P7_IN_Clamping:
      /* :  sf_internal_predicateOutput = 0 | (Phi<Phi_max); */
      if (Controller_P7_Y.CVT_Ratio < Controller_P7_Phi_max) {
        Controller_P7_DW.is_c3_Controller_P7 = Controller_P7_IN_Reving;

        /* :  mode = 4; */
        Controller_P7_B.mode = 4.0;

        /* :  sf_internal_predicateOutput = 0 | (Omega_prim < 173); */
      } else if (Controller_P7_B.Assignment_c[0] < 173.0F) {
        Controller_P7_DW.temporalCounter_i1 = 0U;
        Controller_P7_DW.is_c3_Controller_P7 = Controller_P7_IN_Idle;

        /* :  mode = 1 */
        Controller_P7_B.mode = 1.0;
      } else {
        /* :  mode = 3; */
        Controller_P7_B.mode = 3.0;
      }
      break;

     case Controller_P7_IN_EngineOff:
      /* :  sf_internal_predicateOutput = 0 | (Omega_prim > 155); */
      if (Controller_P7_B.Assignment_c[0] > 155.0F) {
        Controller_P7_DW.temporalCounter_i1 = 0U;
        Controller_P7_DW.is_c3_Controller_P7 = Controller_P7_IN_Idle;

        /* :  mode = 1 */
        Controller_P7_B.mode = 1.0;
      } else {
        /* :  mode = 0; */
        Controller_P7_B.mode = 0.0;
      }
      break;

     case Controller_P7_IN_Idle:
      /* :  sf_internal_predicateOutput = 0 | (Omega_prim < 5 & after(5, sec)); */
      if ((Controller_P7_B.Assignment_c[0] < 5.0F) &&
          (Controller_P7_DW.temporalCounter_i1 >= 5000)) {
        Controller_P7_DW.is_c3_Controller_P7 = Controller_P7_IN_EngineOff;

        /* :  mode = 0; */
        Controller_P7_B.mode = 0.0;

        /* :  sf_internal_predicateOutput = 0 | (Omega_prim > 178); */
      } else if (Controller_P7_B.Assignment_c[0] > 178.0F) {
        Controller_P7_DW.is_c3_Controller_P7 = Controller_P7_IN_Clamping;

        /* :  mode = 3; */
        Controller_P7_B.mode = 3.0;
      } else {
        /* :  mode = 1 */
        Controller_P7_B.mode = 1.0;
      }
      break;

     case Controller_P7_IN_Overdrive:
      /* :  sf_internal_predicateOutput = 0 | (Omega_prim < Omega_High*0.97); */
      if (Controller_P7_B.Assignment_c[0] < 304.73448739820992) {
        Controller_P7_DW.is_c3_Controller_P7 = Controller_P7_IN_Shifting;

        /* :  mode = 5; */
        Controller_P7_B.mode = 5.0;
      } else {
        /* :  mode = 6; */
        Controller_P7_B.mode = 6.0;
      }
      break;

     case Controller_P7_IN_Reving:
      /* :  sf_internal_predicateOutput = 0 | (Omega_prim < Omega_Low*0.97); */
      if (Controller_P7_B.Assignment_c[0] < 182.84069243892594) {
        Controller_P7_DW.is_c3_Controller_P7 = Controller_P7_IN_Clamping;

        /* :  mode = 3; */
        Controller_P7_B.mode = 3.0;

        /* :  sf_internal_predicateOutput = 0 | (Omega_prim > Omega_High); */
      } else if (Controller_P7_B.Assignment_c[0] > Controller_P7_Omega_High) {
        Controller_P7_DW.is_c3_Controller_P7 = Controller_P7_IN_Shifting;

        /* :  mode = 5; */
        Controller_P7_B.mode = 5.0;
      } else {
        /* :  mode = 4; */
        Controller_P7_B.mode = 4.0;
      }
      break;

     default:
      /* case IN_Shifting: */
      /* :  sf_internal_predicateOutput = 0 | (Phi > Phi_max*1.02); */
      if (Controller_P7_Y.CVT_Ratio > 3.213) {
        Controller_P7_DW.is_c3_Controller_P7 = Controller_P7_IN_Reving;

        /* :  mode = 4; */
        Controller_P7_B.mode = 4.0;

        /* :  sf_internal_predicateOutput = 0 | (Phi < Phi_min); */
      } else if (Controller_P7_Y.CVT_Ratio < Controller_P7_Phi_min) {
        Controller_P7_DW.is_c3_Controller_P7 = Controller_P7_IN_Overdrive;

        /* :  mode = 6; */
        Controller_P7_B.mode = 6.0;

        /* :  sf_internal_predicateOutput = 0 | (Omega_prim<173); */
      } else if (Controller_P7_B.Assignment_c[0] < 173.0F) {
        Controller_P7_DW.temporalCounter_i1 = 0U;
        Controller_P7_DW.is_c3_Controller_P7 = Controller_P7_IN_Idle;

        /* :  mode = 1 */
        Controller_P7_B.mode = 1.0;
      } else {
        /* :  mode = 5; */
        Controller_P7_B.mode = 5.0;
      }
      break;
    }
  }

  /* End of Chart: '<S1>/Chart' */

  /* If: '<S1>/If' */
  if (Controller_P7_B.mode > 5.9) {
    /* Outputs for IfAction SubSystem: '<S1>/GR HI' incorporates:
     *  ActionPort: '<S6>/Action Port'
     */
    /* Sum: '<S6>/Add' incorporates:
     *  Constant: '<S6>/Ratio Min'
     *  Outport: '<Root>/CVT_Ratio'
     */
    Controller_P7_B.Add_l = Controller_P7_Y.CVT_Ratio - Controller_P7_P.Phi_min;

    /* Gain: '<S40>/Derivative Gain' */
    Controller_P7_B.DerivativeGain_p = Controller_P7_P.Der_GR_High *
      Controller_P7_B.Add_l;

    /* DiscreteIntegrator: '<S42>/Filter' */
    Controller_P7_B.Filter_d = Controller_P7_DW.Filter_DSTATE_c;

    /* Sum: '<S42>/SumD' */
    Controller_P7_B.SumD_dl = Controller_P7_B.DerivativeGain_p -
      Controller_P7_B.Filter_d;

    /* Gain: '<S44>/Integral Gain' */
    Controller_P7_B.IntegralGain_f = Controller_P7_P.Int_GR_High *
      Controller_P7_B.Add_l;

    /* DiscreteIntegrator: '<S47>/Integrator' */
    Controller_P7_B.Integrator_d = Controller_P7_DW.Integrator_DSTATE_e;

    /* Gain: '<S50>/Filter Coefficient' */
    Controller_P7_B.FilterCoefficient_g = Controller_P7_P.PIDController_N *
      Controller_P7_B.SumD_dl;

    /* Gain: '<S52>/Proportional Gain' */
    Controller_P7_B.ProportionalGain_p = Controller_P7_P.Prop_GR_High *
      Controller_P7_B.Add_l;

    /* Merge: '<S1>/Merge' incorporates:
     *  Sum: '<S56>/Sum'
     */
    Controller_P7_B.Merge = (Controller_P7_B.ProportionalGain_p +
      Controller_P7_B.Integrator_d) + Controller_P7_B.FilterCoefficient_g;

    /* Update for DiscreteIntegrator: '<S42>/Filter' */
    Controller_P7_DW.Filter_DSTATE_c += Controller_P7_P.Filter_gainval *
      Controller_P7_B.FilterCoefficient_g;

    /* Update for DiscreteIntegrator: '<S47>/Integrator' */
    Controller_P7_DW.Integrator_DSTATE_e += Controller_P7_P.Integrator_gainval *
      Controller_P7_B.IntegralGain_f;

    /* End of Outputs for SubSystem: '<S1>/GR HI' */
  } else if (Controller_P7_B.mode > 4.9) {
    /* Outputs for IfAction SubSystem: '<S1>/Omega HI' incorporates:
     *  ActionPort: '<S10>/Action Port'
     */
    /* Sum: '<S10>/Add' incorporates:
     *  Constant: '<S10>/RPM_Hi'
     */
    Controller_P7_B.Add_c = Controller_P7_B.Assignment_c[0] -
      Controller_P7_P.Omega_High;

    /* UnaryMinus: '<S200>/Unary Minus' */
    Controller_P7_B.UnaryMinus_o = -Controller_P7_B.Assignment_c[1];

    /* Gain: '<S199>/Derivative Gain' */
    Controller_P7_B.DerivativeGain_b = Controller_P7_P.Der_RPM_High *
      Controller_P7_B.UnaryMinus_o;

    /* DiscreteIntegrator: '<S201>/Filter' */
    Controller_P7_B.Filter_e = Controller_P7_DW.Filter_DSTATE_b;

    /* Gain: '<S209>/Filter Coefficient' */
    Controller_P7_B.FilterCoefficient_ip = Controller_P7_P.PIDController_N_e *
      Controller_P7_B.Filter_e;

    /* Sum: '<S201>/SumD' */
    Controller_P7_B.SumD_d = Controller_P7_B.DerivativeGain_b -
      Controller_P7_B.FilterCoefficient_ip;

    /* Gain: '<S203>/Integral Gain' */
    Controller_P7_B.IntegralGain_d = Controller_P7_P.Int_RPM_High *
      Controller_P7_B.Add_c;

    /* DiscreteIntegrator: '<S206>/Integrator' */
    Controller_P7_B.Integrator_li = Controller_P7_DW.Integrator_DSTATE_c;

    /* Gain: '<S211>/Proportional Gain' */
    Controller_P7_B.ProportionalGain_b = Controller_P7_P.Prop_RPM_High *
      Controller_P7_B.Add_c;

    /* Merge: '<S1>/Merge' incorporates:
     *  Sum: '<S215>/Sum'
     */
    Controller_P7_B.Merge = (Controller_P7_B.ProportionalGain_b +
      Controller_P7_B.Integrator_li) + Controller_P7_B.FilterCoefficient_ip;

    /* Update for DiscreteIntegrator: '<S201>/Filter' */
    Controller_P7_DW.Filter_DSTATE_b += Controller_P7_P.Filter_gainval_j *
      Controller_P7_B.SumD_d;

    /* Update for DiscreteIntegrator: '<S206>/Integrator' */
    Controller_P7_DW.Integrator_DSTATE_c += Controller_P7_P.Integrator_gainval_d
      * Controller_P7_B.IntegralGain_d;

    /* End of Outputs for SubSystem: '<S1>/Omega HI' */
  } else if (Controller_P7_B.mode > 3.9) {
    /* Outputs for IfAction SubSystem: '<S1>/GR LO' incorporates:
     *  ActionPort: '<S7>/Action Port'
     */
    /* Sum: '<S7>/Add' incorporates:
     *  Constant: '<S7>/Ratio Max'
     *  Outport: '<Root>/CVT_Ratio'
     */
    Controller_P7_B.Add_bo = Controller_P7_P.Phi_max - Controller_P7_Y.CVT_Ratio;

    /* Gain: '<S93>/Derivative Gain' */
    Controller_P7_B.DerivativeGain_f = Controller_P7_P.Der_GR_Low *
      Controller_P7_B.Add_bo;

    /* DiscreteIntegrator: '<S95>/Filter' */
    Controller_P7_B.Filter_k = Controller_P7_DW.Filter_DSTATE_i;

    /* Sum: '<S95>/SumD' */
    Controller_P7_B.SumD_e = Controller_P7_B.DerivativeGain_f -
      Controller_P7_B.Filter_k;

    /* Gain: '<S97>/Integral Gain' */
    Controller_P7_B.IntegralGain_h = Controller_P7_P.Int_GR_Low *
      Controller_P7_B.Add_bo;

    /* DiscreteIntegrator: '<S100>/Integrator' */
    Controller_P7_B.Integrator_l = Controller_P7_DW.Integrator_DSTATE_g;

    /* Gain: '<S103>/Filter Coefficient' */
    Controller_P7_B.FilterCoefficient_m = Controller_P7_P.PIDController_N_i *
      Controller_P7_B.SumD_e;

    /* Gain: '<S105>/Proportional Gain' */
    Controller_P7_B.ProportionalGain_o = Controller_P7_P.Prop_GR_Low *
      Controller_P7_B.Add_bo;

    /* Merge: '<S1>/Merge' incorporates:
     *  Sum: '<S109>/Sum'
     */
    Controller_P7_B.Merge = (Controller_P7_B.ProportionalGain_o +
      Controller_P7_B.Integrator_l) + Controller_P7_B.FilterCoefficient_m;

    /* Update for DiscreteIntegrator: '<S95>/Filter' */
    Controller_P7_DW.Filter_DSTATE_i += Controller_P7_P.Filter_gainval_jr *
      Controller_P7_B.FilterCoefficient_m;

    /* Update for DiscreteIntegrator: '<S100>/Integrator' */
    Controller_P7_DW.Integrator_DSTATE_g += Controller_P7_P.Integrator_gainval_c
      * Controller_P7_B.IntegralGain_h;

    /* End of Outputs for SubSystem: '<S1>/GR LO' */
  } else if (Controller_P7_B.mode > 2.9) {
    /* Outputs for IfAction SubSystem: '<S1>/Omega LO' incorporates:
     *  ActionPort: '<S11>/Action Port'
     */
    /* Sum: '<S11>/Add' incorporates:
     *  Constant: '<S11>/Constant'
     */
    Controller_P7_B.Add_b = Controller_P7_B.Assignment_c[0] -
      Controller_P7_P.Omega_Low;

    /* UnaryMinus: '<S253>/Unary Minus' */
    Controller_P7_B.UnaryMinus = -Controller_P7_B.Assignment_c[1];

    /* Gain: '<S252>/Derivative Gain' */
    Controller_P7_B.DerivativeGain_f1 = Controller_P7_P.Der_RPM_Low *
      Controller_P7_B.UnaryMinus;

    /* DiscreteIntegrator: '<S254>/Filter' */
    Controller_P7_B.Filter_p = Controller_P7_DW.Filter_DSTATE_j;

    /* Gain: '<S262>/Filter Coefficient' */
    Controller_P7_B.FilterCoefficient_i = Controller_P7_P.PIDController_N_k *
      Controller_P7_B.Filter_p;

    /* Sum: '<S254>/SumD' */
    Controller_P7_B.SumD_i = Controller_P7_B.DerivativeGain_f1 -
      Controller_P7_B.FilterCoefficient_i;

    /* Gain: '<S256>/Integral Gain' */
    Controller_P7_B.IntegralGain_a = Controller_P7_P.Int_RPM_Low *
      Controller_P7_B.Add_b;

    /* DiscreteIntegrator: '<S259>/Integrator' */
    Controller_P7_B.Integrator_f = Controller_P7_DW.Integrator_DSTATE_p;

    /* Gain: '<S264>/Proportional Gain' */
    Controller_P7_B.ProportionalGain_g = Controller_P7_P.Prop_RPM_Low *
      Controller_P7_B.Add_b;

    /* Merge: '<S1>/Merge' incorporates:
     *  Sum: '<S268>/Sum'
     */
    Controller_P7_B.Merge = (Controller_P7_B.ProportionalGain_g +
      Controller_P7_B.Integrator_f) + Controller_P7_B.FilterCoefficient_i;

    /* Update for DiscreteIntegrator: '<S254>/Filter' */
    Controller_P7_DW.Filter_DSTATE_j += Controller_P7_P.Filter_gainval_l *
      Controller_P7_B.SumD_i;

    /* Update for DiscreteIntegrator: '<S259>/Integrator' */
    Controller_P7_DW.Integrator_DSTATE_p += Controller_P7_P.Integrator_gainval_p
      * Controller_P7_B.IntegralGain_a;

    /* End of Outputs for SubSystem: '<S1>/Omega LO' */
  } else if (Controller_P7_B.mode > 1.9) {
    /* Outputs for IfAction SubSystem: '<S1>/BreakCheck' incorporates:
     *  ActionPort: '<S3>/Action Port'
     */
    /* Merge: '<S1>/Merge' incorporates:
     *  Constant: '<S3>/-12'
     *  SignalConversion generated from: '<S3>/Voltage Comand'
     */
    Controller_P7_B.Merge = Controller_P7_P.u2_Value;

    /* End of Outputs for SubSystem: '<S1>/BreakCheck' */
  } else if (Controller_P7_B.mode > 0.9) {
    /* Outputs for IfAction SubSystem: '<S1>/Idle' incorporates:
     *  ActionPort: '<S8>/Action Port'
     */
    /* Sum: '<S8>/Add' incorporates:
     *  Constant: '<S8>/Constant'
     *  Inport: '<Root>/Theta_Helix'
     */
    Controller_P7_B.Add = Controller_P7_U.Theta_Helix -
      Controller_P7_P.Constant_Value;

    /* Gain: '<S146>/Derivative Gain' */
    Controller_P7_B.DerivativeGain = Controller_P7_P.Der_GR_Low *
      Controller_P7_B.Add;

    /* DiscreteIntegrator: '<S148>/Filter' */
    Controller_P7_B.Filter = Controller_P7_DW.Filter_DSTATE;

    /* Sum: '<S148>/SumD' */
    Controller_P7_B.SumD = Controller_P7_B.DerivativeGain -
      Controller_P7_B.Filter;

    /* Gain: '<S150>/Integral Gain' */
    Controller_P7_B.IntegralGain = Controller_P7_P.Int_GR_Low *
      Controller_P7_B.Add;

    /* DiscreteIntegrator: '<S153>/Integrator' */
    Controller_P7_B.Integrator = Controller_P7_DW.Integrator_DSTATE;

    /* Gain: '<S156>/Filter Coefficient' */
    Controller_P7_B.FilterCoefficient = Controller_P7_P.PIDController_N_d *
      Controller_P7_B.SumD;

    /* Gain: '<S158>/Proportional Gain' */
    Controller_P7_B.ProportionalGain = Controller_P7_P.Prop_GR_Low *
      Controller_P7_B.Add;

    /* Merge: '<S1>/Merge' incorporates:
     *  Sum: '<S162>/Sum'
     */
    Controller_P7_B.Merge = (Controller_P7_B.ProportionalGain +
      Controller_P7_B.Integrator) + Controller_P7_B.FilterCoefficient;

    /* Update for DiscreteIntegrator: '<S148>/Filter' */
    Controller_P7_DW.Filter_DSTATE += Controller_P7_P.Filter_gainval_f *
      Controller_P7_B.FilterCoefficient;

    /* Update for DiscreteIntegrator: '<S153>/Integrator' */
    Controller_P7_DW.Integrator_DSTATE += Controller_P7_P.Integrator_gainval_i *
      Controller_P7_B.IntegralGain;

    /* End of Outputs for SubSystem: '<S1>/Idle' */
  } else {
    /* Outputs for IfAction SubSystem: '<S1>/Engine Off' incorporates:
     *  ActionPort: '<S5>/Action Port'
     */
    /* Merge: '<S1>/Merge' incorporates:
     *  Constant: '<S5>/Ratio Max1'
     *  SignalConversion generated from: '<S5>/Voltage Comand'
     */
    Controller_P7_B.Merge = Controller_P7_P.RatioMax1_Value;

    /* End of Outputs for SubSystem: '<S1>/Engine Off' */
  }

  /* End of If: '<S1>/If' */

  /* Saturate: '<S1>/Saturation' */
  u0 = Controller_P7_B.Merge;
  u1 = Controller_P7_P.Saturation_LowerSat;
  u2 = Controller_P7_P.Saturation_UpperSat;
  if (u0 > u2) {
    /* Saturate: '<S1>/Saturation' */
    Controller_P7_B.Saturation = u2;
  } else if (u0 < u1) {
    /* Saturate: '<S1>/Saturation' */
    Controller_P7_B.Saturation = u1;
  } else {
    /* Saturate: '<S1>/Saturation' */
    Controller_P7_B.Saturation = u0;
  }

  /* End of Saturate: '<S1>/Saturation' */

  /* RelationalOperator: '<S9>/Less Than' incorporates:
   *  Constant: '<S9>/Constant1'
   */
  Controller_P7_B.LessThan = (Controller_P7_B.Saturation <
    Controller_P7_P.Constant1_Value);

  /* Logic: '<S9>/AND' */
  Controller_P7_B.AND = (Controller_P7_B.GreaterThan && Controller_P7_B.LessThan);

  /* RelationalOperator: '<S9>/GreaterThan1' incorporates:
   *  Constant: '<S9>/Constant3'
   */
  Controller_P7_B.GreaterThan1 = (Controller_P7_B.Saturation >
    Controller_P7_P.Constant3_Value);

  /* RelationalOperator: '<S9>/GreaterThan2' incorporates:
   *  Constant: '<S9>/Constant4'
   *  Inport: '<Root>/Theta_Helix'
   */
  Controller_P7_B.GreaterThan2 = (Controller_P7_U.Theta_Helix >
    Controller_P7_P.Constant4_Value);

  /* Logic: '<S9>/AND1' */
  Controller_P7_B.AND1 = (Controller_P7_B.GreaterThan1 &&
    Controller_P7_B.GreaterThan2);

  /* Logic: '<S9>/OR' */
  Controller_P7_B.OR = (Controller_P7_B.AND || Controller_P7_B.AND1);

  /* Switch: '<S9>/Switch' */
  if (Controller_P7_B.OR) {
    /* Outport: '<Root>/Command' incorporates:
     *  Constant: '<S9>/Constant2'
     */
    Controller_P7_Y.Command = Controller_P7_P.Constant2_Value;
  } else {
    /* Outport: '<Root>/Command' */
    Controller_P7_Y.Command = Controller_P7_B.Saturation;
  }

  /* End of Switch: '<S9>/Switch' */

  /* Outport: '<Root>/Primary_Speed' */
  Controller_P7_Y.Primary_Speed = Controller_P7_B.Assignment_c[0];

  /* Outport: '<Root>/Secondary_Speed' */
  Controller_P7_Y.Secondary_Speed = Controller_P7_B.Assignment_c[1];

  /* Update for UnitDelay: '<S277>/Unit Delay2' incorporates:
   *  Assignment: '<S284>/Assignment'
   */
  Controller_P7_DW.UnitDelay2_DSTATE[0] = Controller_P7_B.Assignment_a[0];
  Controller_P7_DW.UnitDelay2_DSTATE[1] = Controller_P7_B.Assignment_a[1];
  Controller_P7_DW.UnitDelay2_DSTATE[2] = Controller_P7_B.Assignment_a[2];
  Controller_P7_DW.UnitDelay2_DSTATE[3] = Controller_P7_B.Assignment_a[3];

  /* Update for UnitDelay: '<S277>/Unit Delay3' incorporates:
   *  Assignment: '<S282>/Assignment'
   */
  memcpy(&Controller_P7_DW.UnitDelay3_DSTATE[0], &Controller_P7_B.Assignment[0],
         sizeof(real32_T) << 4U);

  /* Matfile logging */
  rt_UpdateTXYLogVars(Controller_P7_M->rtwLogInfo,
                      (&Controller_P7_M->Timing.taskTime0));

  /* signal main to stop simulation */
  {                                    /* Sample time: [0.001s, 0.0s] */
    if ((rtmGetTFinal(Controller_P7_M)!=-1) &&
        !((rtmGetTFinal(Controller_P7_M)-Controller_P7_M->Timing.taskTime0) >
          Controller_P7_M->Timing.taskTime0 * (DBL_EPSILON))) {
      rtmSetErrorStatus(Controller_P7_M, "Simulation finished");
    }
  }

  /* Update absolute time for base rate */
  /* The "clockTick0" counts the number of times the code of this task has
   * been executed. The absolute time is the multiplication of "clockTick0"
   * and "Timing.stepSize0". Size of "clockTick0" ensures timer will not
   * overflow during the application lifespan selected.
   * Timer of this task consists of two 32 bit unsigned integers.
   * The two integers represent the low bits Timing.clockTick0 and the high bits
   * Timing.clockTickH0. When the low bit overflows to 0, the high bits increment.
   */
  if (!(++Controller_P7_M->Timing.clockTick0)) {
    ++Controller_P7_M->Timing.clockTickH0;
  }

  Controller_P7_M->Timing.taskTime0 = Controller_P7_M->Timing.clockTick0 *
    Controller_P7_M->Timing.stepSize0 + Controller_P7_M->Timing.clockTickH0 *
    Controller_P7_M->Timing.stepSize0 * 4294967296.0;
}

/* Model initialize function */
void Controller_P7_initialize(void)
{
  /* Registration code */

  /* initialize real-time model */
  (void) memset((void *)Controller_P7_M, 0,
                sizeof(RT_MODEL_Controller_P7_T));
  rtmSetTFinal(Controller_P7_M, 10.0);
  Controller_P7_M->Timing.stepSize0 = 0.001;

  /* Setup for data logging */
  {
    static RTWLogInfo rt_DataLoggingInfo;
    rt_DataLoggingInfo.loggingInterval = (NULL);
    Controller_P7_M->rtwLogInfo = &rt_DataLoggingInfo;
  }

  /* Setup for data logging */
  {
    rtliSetLogXSignalInfo(Controller_P7_M->rtwLogInfo, (NULL));
    rtliSetLogXSignalPtrs(Controller_P7_M->rtwLogInfo, (NULL));
    rtliSetLogT(Controller_P7_M->rtwLogInfo, "");
    rtliSetLogX(Controller_P7_M->rtwLogInfo, "");
    rtliSetLogXFinal(Controller_P7_M->rtwLogInfo, "");
    rtliSetLogVarNameModifier(Controller_P7_M->rtwLogInfo, "rt_");
    rtliSetLogFormat(Controller_P7_M->rtwLogInfo, 4);
    rtliSetLogMaxRows(Controller_P7_M->rtwLogInfo, 0);
    rtliSetLogDecimation(Controller_P7_M->rtwLogInfo, 1);
    rtliSetLogY(Controller_P7_M->rtwLogInfo, "");
    rtliSetLogYSignalInfo(Controller_P7_M->rtwLogInfo, (NULL));
    rtliSetLogYSignalPtrs(Controller_P7_M->rtwLogInfo, (NULL));
  }

  /* block I/O */
  (void) memset(((void *) &Controller_P7_B), 0,
                sizeof(B_Controller_P7_T));

  /* states (dwork) */
  (void) memset((void *)&Controller_P7_DW, 0,
                sizeof(DW_Controller_P7_T));

  /* external inputs */
  (void)memset(&Controller_P7_U, 0, sizeof(ExtU_Controller_P7_T));

  /* external outputs */
  (void)memset(&Controller_P7_Y, 0, sizeof(ExtY_Controller_P7_T));

  /* Matfile logging */
  rt_StartDataLoggingWithStartTime(Controller_P7_M->rtwLogInfo, 0.0,
    rtmGetTFinal(Controller_P7_M), Controller_P7_M->Timing.stepSize0,
    (&rtmGetErrorStatus(Controller_P7_M)));

  {
    int32_T i;

    /* InitializeConditions for UnitDelay: '<S277>/Unit Delay2' */
    Controller_P7_DW.UnitDelay2_DSTATE[0] =
      Controller_P7_P.UnitDelay2_InitialCondition[0];
    Controller_P7_DW.UnitDelay2_DSTATE[1] =
      Controller_P7_P.UnitDelay2_InitialCondition[1];
    Controller_P7_DW.UnitDelay2_DSTATE[2] =
      Controller_P7_P.UnitDelay2_InitialCondition[2];
    Controller_P7_DW.UnitDelay2_DSTATE[3] =
      Controller_P7_P.UnitDelay2_InitialCondition[3];

    /* SystemInitialize for Iterator SubSystem: '<S277>/Control' */
    /* SystemInitialize for Assignment: '<S283>/Assignment' incorporates:
     *  Outport: '<S279>/X_est'
     */
    Controller_P7_B.Assignment_c[0] = Controller_P7_P.X_est_Y0;

    /* SystemInitialize for Assignment: '<S284>/Assignment' incorporates:
     *  Outport: '<S279>/X_prd'
     */
    Controller_P7_B.Assignment_a[0] = Controller_P7_P.X_prd_Y0;

    /* SystemInitialize for Assignment: '<S283>/Assignment' incorporates:
     *  Outport: '<S279>/X_est'
     */
    Controller_P7_B.Assignment_c[1] = Controller_P7_P.X_est_Y0;

    /* SystemInitialize for Assignment: '<S284>/Assignment' incorporates:
     *  Outport: '<S279>/X_prd'
     */
    Controller_P7_B.Assignment_a[1] = Controller_P7_P.X_prd_Y0;

    /* SystemInitialize for Assignment: '<S283>/Assignment' incorporates:
     *  Outport: '<S279>/X_est'
     */
    Controller_P7_B.Assignment_c[2] = Controller_P7_P.X_est_Y0;

    /* SystemInitialize for Assignment: '<S284>/Assignment' incorporates:
     *  Outport: '<S279>/X_prd'
     */
    Controller_P7_B.Assignment_a[2] = Controller_P7_P.X_prd_Y0;

    /* SystemInitialize for Assignment: '<S283>/Assignment' incorporates:
     *  Outport: '<S279>/X_est'
     */
    Controller_P7_B.Assignment_c[3] = Controller_P7_P.X_est_Y0;

    /* SystemInitialize for Assignment: '<S284>/Assignment' incorporates:
     *  Outport: '<S279>/X_prd'
     */
    Controller_P7_B.Assignment_a[3] = Controller_P7_P.X_prd_Y0;
    for (i = 0; i < 16; i++) {
      /* InitializeConditions for UnitDelay: '<S277>/Unit Delay3' */
      Controller_P7_DW.UnitDelay3_DSTATE[i] =
        Controller_P7_P.UnitDelay3_InitialCondition[i];

      /* SystemInitialize for Assignment: '<S282>/Assignment' incorporates:
       *  Outport: '<S279>/P_prd'
       */
      Controller_P7_B.Assignment[i] = Controller_P7_P.P_prd_Y0;
    }

    /* End of SystemInitialize for SubSystem: '<S277>/Control' */

    /* SystemInitialize for Chart: '<S1>/Chart' */
    Controller_P7_DW.temporalCounter_i1 = 0U;
    Controller_P7_B.mode = 0.0;
    Controller_P7_DW.is_active_c3_Controller_P7 = 0U;
    Controller_P7_DW.is_c3_Controller_P7 = Controller_P_IN_NO_ACTIVE_CHILD;

    /* SystemInitialize for IfAction SubSystem: '<S1>/GR HI' */
    /* InitializeConditions for DiscreteIntegrator: '<S42>/Filter' */
    Controller_P7_DW.Filter_DSTATE_c =
      Controller_P7_P.PIDController_InitialConditionF;

    /* InitializeConditions for DiscreteIntegrator: '<S47>/Integrator' */
    Controller_P7_DW.Integrator_DSTATE_e =
      Controller_P7_P.PIDController_InitialConditio_n;

    /* End of SystemInitialize for SubSystem: '<S1>/GR HI' */

    /* SystemInitialize for IfAction SubSystem: '<S1>/Omega HI' */
    /* InitializeConditions for DiscreteIntegrator: '<S201>/Filter' */
    Controller_P7_DW.Filter_DSTATE_b =
      Controller_P7_P.PIDController_InitialConditio_f;

    /* InitializeConditions for DiscreteIntegrator: '<S206>/Integrator' */
    Controller_P7_DW.Integrator_DSTATE_c =
      Controller_P7_P.PIDController_InitialConditio_a;

    /* End of SystemInitialize for SubSystem: '<S1>/Omega HI' */

    /* SystemInitialize for IfAction SubSystem: '<S1>/GR LO' */
    /* InitializeConditions for DiscreteIntegrator: '<S95>/Filter' */
    Controller_P7_DW.Filter_DSTATE_i =
      Controller_P7_P.PIDController_InitialConditi_fp;

    /* InitializeConditions for DiscreteIntegrator: '<S100>/Integrator' */
    Controller_P7_DW.Integrator_DSTATE_g =
      Controller_P7_P.PIDController_InitialConditio_d;

    /* End of SystemInitialize for SubSystem: '<S1>/GR LO' */

    /* SystemInitialize for IfAction SubSystem: '<S1>/Omega LO' */
    /* InitializeConditions for DiscreteIntegrator: '<S254>/Filter' */
    Controller_P7_DW.Filter_DSTATE_j =
      Controller_P7_P.PIDController_InitialConditio_p;

    /* InitializeConditions for DiscreteIntegrator: '<S259>/Integrator' */
    Controller_P7_DW.Integrator_DSTATE_p =
      Controller_P7_P.PIDController_InitialConditi_nx;

    /* End of SystemInitialize for SubSystem: '<S1>/Omega LO' */

    /* SystemInitialize for IfAction SubSystem: '<S1>/Idle' */
    /* InitializeConditions for DiscreteIntegrator: '<S148>/Filter' */
    Controller_P7_DW.Filter_DSTATE =
      Controller_P7_P.PIDController_InitialConditio_b;

    /* InitializeConditions for DiscreteIntegrator: '<S153>/Integrator' */
    Controller_P7_DW.Integrator_DSTATE =
      Controller_P7_P.PIDController_InitialConditio_k;

    /* End of SystemInitialize for SubSystem: '<S1>/Idle' */
  }
}

/* Model terminate function */
void Controller_P7_terminate(void)
{
  /* (no terminate code required) */
}
