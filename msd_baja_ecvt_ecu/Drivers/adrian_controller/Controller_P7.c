/*
 * Controller_P7.c
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

#include "Controller_P7.h"
#include "rtwtypes.h"
#include <string.h>
#include "Controller_P7_private.h"

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
real32_T look1_iflf_binlxpw(real32_T u0, const real32_T bp0[], const real32_T
  table[], uint32_T maxIndex)
{
  real32_T frac;
  real32_T yL_0d0;
  uint32_T iLeft;

  /* Column-major Lookup 1-D
     Search method: 'binary'
     Use previous index: 'off'
     Interpolation method: 'Linear point-slope'
     Extrapolation method: 'Linear'
     Use last breakpoint for index at or above upper limit: 'off'
     Remove protection against out-of-range input in generated code: 'off'
   */
  /* Prelookup - Index and Fraction
     Index Search method: 'binary'
     Extrapolation method: 'Linear'
     Use previous index: 'off'
     Use last breakpoint for index at or above upper limit: 'off'
     Remove protection against out-of-range input in generated code: 'off'
   */
  if (u0 <= bp0[0U]) {
    iLeft = 0U;
    frac = (u0 - bp0[0U]) / (bp0[1U] - bp0[0U]);
  } else if (u0 < bp0[maxIndex]) {
    uint32_T bpIdx;
    uint32_T iRght;

    /* Binary Search */
    bpIdx = maxIndex >> 1U;
    iLeft = 0U;
    iRght = maxIndex;
    while (iRght - iLeft > 1U) {
      if (u0 < bp0[bpIdx]) {
        iRght = bpIdx;
      } else {
        iLeft = bpIdx;
      }

      bpIdx = (iRght + iLeft) >> 1U;
    }

    frac = (u0 - bp0[iLeft]) / (bp0[iLeft + 1U] - bp0[iLeft]);
  } else {
    iLeft = maxIndex - 1U;
    frac = (u0 - bp0[maxIndex - 1U]) / (bp0[maxIndex] - bp0[maxIndex - 1U]);
  }

  /* Column-major Interpolation 1-D
     Interpolation method: 'Linear point-slope'
     Use last breakpoint for index at or above upper limit: 'off'
     Overflow mode: 'portable wrapping'
   */
  yL_0d0 = table[iLeft];
  return (table[iLeft + 1U] - yL_0d0) * frac + yL_0d0;
}

void LDLf_int32_Treal32_T(real32_T out[], real32_T vArray[], int32_T nRows,
  const real32_T in[])
{
  int32_T c;
  int32_T k;
  int32_T r;
  real32_T mYTmp;
  boolean_T done;

  /* S-Function (sdspldl2): '<S228>/LDL Factorization' */
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

  /* End of S-Function (sdspldl2): '<S228>/LDL Factorization' */
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
  int32_T s222_iter;
  real32_T tmp_0[16];
  real32_T tmp_2[16];
  real32_T v1_0[16];
  real32_T tmp[8];
  real32_T tmp_1[8];
  real32_T v1[8];
  real32_T tmp_3[4];
  real32_T tmp_4[4];
  real32_T tmp_5[4];
  real32_T tmp_6[4];
  real32_T v1_1[4];
  real32_T tmp_7[2];
  real32_T HP_prdt;
  real32_T HP_prdt_0;
  real32_T HP_prdt_p;
  real32_T HP_prdt_p_0;
  real32_T KHP_prd_p;
  real32_T KHP_prd_p_0;
  real32_T UnitDelay3;
  real32_T tmp_8;
  real32_T tmp_9;
  real32_T tmp_a;
  real32_T tmp_b;

  /* UnitDelay: '<S219>/Unit Delay2' */
  Controller_P7_B.UnitDelay2[0] = Controller_P7_DW.UnitDelay2_DSTATE[0];
  Controller_P7_B.UnitDelay2[1] = Controller_P7_DW.UnitDelay2_DSTATE[1];
  Controller_P7_B.UnitDelay2[2] = Controller_P7_DW.UnitDelay2_DSTATE[2];
  Controller_P7_B.UnitDelay2[3] = Controller_P7_DW.UnitDelay2_DSTATE[3];

  /* Outputs for Iterator SubSystem: '<S219>/Control' incorporates:
   *  ForIterator: '<S222>/Iterator'
   */
  for (i = 0; i < 16; i++) {
    /* UnitDelay: '<S219>/Unit Delay3' */
    UnitDelay3 = Controller_P7_DW.UnitDelay3_DSTATE[i];
    Controller_P7_B.UnitDelay3[i] = UnitDelay3;

    /* Assignment: '<S225>/Assignment' incorporates:
     *  UnitDelay: '<S219>/Unit Delay3'
     */
    Controller_P7_B.Assignment_d[i] = UnitDelay3;
  }

  /* Assignment: '<S227>/Assignment' incorporates:
   *  UnitDelay: '<S219>/Unit Delay2'
   */
  Controller_P7_B.Assignment_g[0] = Controller_P7_B.UnitDelay2[0];
  Controller_P7_B.Assignment_g[1] = Controller_P7_B.UnitDelay2[1];
  Controller_P7_B.Assignment_g[2] = Controller_P7_B.UnitDelay2[2];
  Controller_P7_B.Assignment_g[3] = Controller_P7_B.UnitDelay2[3];
  s222_iter = 1;
  if (Controller_P7_P.Iterator_IterationLimit >= 1) {
    /* Selector: '<S223>/Selector1' incorporates:
     *  UnitDelay: '<S219>/Unit Delay2'
     */
    Controller_P7_B.Selector1_b[0] = Controller_P7_B.UnitDelay2[0];
    Controller_P7_B.Selector1_b[1] = Controller_P7_B.UnitDelay2[1];
    Controller_P7_B.Selector1_b[2] = Controller_P7_B.UnitDelay2[2];
    Controller_P7_B.Selector1_b[3] = Controller_P7_B.UnitDelay2[3];

    /* SignalConversion generated from: '<S223>/Selector' incorporates:
     *  Inport: '<Root>/Omega_Primary'
     *  Inport: '<Root>/Omega_Secondary'
     */
    Controller_P7_B.TmpSignalConversionAtSelector_l[0] =
      Controller_P7_U.Omega_Primary;
    Controller_P7_B.TmpSignalConversionAtSelector_l[1] =
      Controller_P7_U.Omega_Secondary;

    /* Selector: '<S223>/Selector' incorporates:
     *  SignalConversion generated from: '<S223>/Selector'
     */
    Controller_P7_B.Selector_f[0] =
      Controller_P7_B.TmpSignalConversionAtSelector_l[0];
    Controller_P7_B.Selector_f[1] =
      Controller_P7_B.TmpSignalConversionAtSelector_l[1];

    /* Selector: '<S223>/Selector2' incorporates:
     *  UnitDelay: '<S219>/Unit Delay3'
     */
    memcpy(&Controller_P7_B.Selector2_j[0], &Controller_P7_B.UnitDelay3[0],
           sizeof(real32_T) << 4U);
    for (i = 0; i < 4; i++) {
      /* Math: '<S224>/P_prd Trans' */
      idxS = i << 2;

      /* Math: '<S224>/P_prd Trans' incorporates:
       *  Selector: '<S223>/Selector2'
       */
      Controller_P7_B.P_prdTrans_f[idxS] = Controller_P7_B.Selector2_j[i];
      Controller_P7_B.P_prdTrans_f[idxS + 1] = Controller_P7_B.Selector2_j[i + 4];
      Controller_P7_B.P_prdTrans_f[idxS + 2] = Controller_P7_B.Selector2_j[i + 8];
      Controller_P7_B.P_prdTrans_f[idxS + 3] = Controller_P7_B.Selector2_j[i +
        12];
    }

    /* Product: '<S224>/H*P_prdt' incorporates:
     *  Constant: '<S224>/Hcst'
     */
    for (i = 0; i < 8; i++) {
      tmp[i] = Controller_P7_P.Hcst_Value[i];
    }
  }

  while (s222_iter <= Controller_P7_P.Iterator_IterationLimit) {
    /* Outputs for Iterator SubSystem: '<S219>/Control' incorporates:
     *  ForIterator: '<S222>/Iterator'
     */
    Controller_P7_B.Iterator_i = s222_iter;

    /* Product: '<S224>/H*P_prdt' incorporates:
     *  Math: '<S224>/P_prd Trans'
     */
    memcpy(&tmp_0[0], &Controller_P7_B.P_prdTrans_f[0], sizeof(real32_T) << 4U);
    for (i = 0; i < 4; i++) {
      HP_prdt_p = 0.0F;
      HP_prdt_p_0 = 0.0F;
      for (idxS = 0; idxS < 4; idxS++) {
        UnitDelay3 = tmp_0[(i << 2) + idxS];
        idxV = idxS << 1;
        HP_prdt_p += tmp[idxV] * UnitDelay3;
        HP_prdt_p_0 += tmp[idxV + 1] * UnitDelay3;
      }

      idxV = i << 1;
      Controller_P7_B.HP_prdt_p[idxV + 1] = HP_prdt_p_0;
      Controller_P7_B.HP_prdt_p[idxV] = HP_prdt_p;
    }

    /* Product: '<S224>/H*P_prdt*Ht' incorporates:
     *  Constant: '<S224>/Hcst_t'
     *  Product: '<S224>/H*P_prdt'
     */
    for (i = 0; i < 8; i++) {
      tmp_1[i] = Controller_P7_B.HP_prdt_p[i];
      v1[i] = Controller_P7_P.Hcst_t_Value[i];
    }

    for (i = 0; i < 2; i++) {
      HP_prdt_p = 0.0F;
      HP_prdt_p_0 = 0.0F;
      for (idxS = 0; idxS < 4; idxS++) {
        UnitDelay3 = v1[(i << 2) + idxS];
        idxV = idxS << 1;
        HP_prdt_p += tmp_1[idxV] * UnitDelay3;
        HP_prdt_p_0 += tmp_1[idxV + 1] * UnitDelay3;
      }

      idxV = i << 1;
      Controller_P7_B.HP_prdtHt_l[idxV + 1] = HP_prdt_p_0;
      Controller_P7_B.HP_prdtHt_l[idxV] = HP_prdt_p;
    }

    /* End of Product: '<S224>/H*P_prdt*Ht' */

    /* Sum: '<S224>/H*P_prdt*Ht+R' incorporates:
     *  Constant: '<S224>/Constant2'
     *  Product: '<S224>/H*P_prdt*Ht'
     */
    UnitDelay3 = Controller_P7_B.HP_prdtHt_l[0] +
      Controller_P7_P.Constant2_Value[0];
    Controller_P7_B.HP_prdtHtR_i[0] = UnitDelay3;

    /* S-Function (sdspldl2): '<S228>/LDL Factorization' incorporates:
     *  Sum: '<S224>/H*P_prdt*Ht+R'
     */
    Controller_P7_B.LDLFactorization_g[0] = UnitDelay3;

    /* Sum: '<S224>/H*P_prdt*Ht+R' incorporates:
     *  Constant: '<S224>/Constant2'
     *  Product: '<S224>/H*P_prdt*Ht'
     */
    UnitDelay3 = Controller_P7_B.HP_prdtHt_l[1] +
      Controller_P7_P.Constant2_Value[1];
    Controller_P7_B.HP_prdtHtR_i[1] = UnitDelay3;

    /* S-Function (sdspldl2): '<S228>/LDL Factorization' incorporates:
     *  Sum: '<S224>/H*P_prdt*Ht+R'
     */
    Controller_P7_B.LDLFactorization_g[1] = UnitDelay3;

    /* Sum: '<S224>/H*P_prdt*Ht+R' incorporates:
     *  Constant: '<S224>/Constant2'
     *  Product: '<S224>/H*P_prdt*Ht'
     */
    UnitDelay3 = Controller_P7_B.HP_prdtHt_l[2] +
      Controller_P7_P.Constant2_Value[2];
    Controller_P7_B.HP_prdtHtR_i[2] = UnitDelay3;

    /* S-Function (sdspldl2): '<S228>/LDL Factorization' incorporates:
     *  Sum: '<S224>/H*P_prdt*Ht+R'
     */
    Controller_P7_B.LDLFactorization_g[2] = UnitDelay3;

    /* Sum: '<S224>/H*P_prdt*Ht+R' incorporates:
     *  Constant: '<S224>/Constant2'
     *  Product: '<S224>/H*P_prdt*Ht'
     */
    UnitDelay3 = Controller_P7_B.HP_prdtHt_l[3] +
      Controller_P7_P.Constant2_Value[3];
    Controller_P7_B.HP_prdtHtR_i[3] = UnitDelay3;

    /* S-Function (sdspldl2): '<S228>/LDL Factorization' incorporates:
     *  Sum: '<S224>/H*P_prdt*Ht+R'
     */
    Controller_P7_B.LDLFactorization_g[3] = UnitDelay3;

    /* S-Function (sdspldl2): '<S228>/LDL Factorization' incorporates:
     *  Sum: '<S224>/H*P_prdt*Ht+R'
     */
    LDLf_int32_Treal32_T(&Controller_P7_B.LDLFactorization_g[0U],
                         &Controller_P7_DW.LDLFactorization_VMX_a[0U], 2,
                         &Controller_P7_B.HP_prdtHtR_i[0U]);

    /* S-Function (sdspfbsub2): '<S228>/Forward Substitution' incorporates:
     *  Product: '<S224>/H*P_prdt'
     *  S-Function (sdspldl2): '<S228>/LDL Factorization'
     */
    Controller_P7_B.y_e[0] = Controller_P7_B.HP_prdt_p[0];
    UnitDelay3 = Controller_P7_B.HP_prdt_p[1];
    UnitDelay3 -= Controller_P7_B.y_e[0] * Controller_P7_B.LDLFactorization_g[1];
    Controller_P7_B.y_e[1] = UnitDelay3;
    Controller_P7_B.y_e[2] = Controller_P7_B.HP_prdt_p[2];
    UnitDelay3 = Controller_P7_B.HP_prdt_p[3];
    UnitDelay3 -= Controller_P7_B.LDLFactorization_g[1] * Controller_P7_B.y_e[2];
    Controller_P7_B.y_e[3] = UnitDelay3;
    Controller_P7_B.y_e[4] = Controller_P7_B.HP_prdt_p[4];
    UnitDelay3 = Controller_P7_B.HP_prdt_p[5];
    UnitDelay3 -= Controller_P7_B.LDLFactorization_g[1] * Controller_P7_B.y_e[4];
    Controller_P7_B.y_e[5] = UnitDelay3;
    Controller_P7_B.y_e[6] = Controller_P7_B.HP_prdt_p[6];
    UnitDelay3 = Controller_P7_B.HP_prdt_p[7];
    UnitDelay3 -= Controller_P7_B.LDLFactorization_g[1] * Controller_P7_B.y_e[6];
    Controller_P7_B.y_e[7] = UnitDelay3;

    /* S-Function (sdspdiag2): '<S228>/Extract Diagonal' incorporates:
     *  S-Function (sdspldl2): '<S228>/LDL Factorization'
     */
    Controller_P7_B.d_e[0] = Controller_P7_B.LDLFactorization_g[0];

    /* Math: '<S228>/Math Function'
     *
     * About '<S228>/Math Function':
     *  Operator: reciprocal
     */
    UnitDelay3 = Controller_P7_B.d_e[0];
    UnitDelay3 = 1.0F / UnitDelay3;

    /* Math: '<S228>/Math Function'
     *
     * About '<S228>/Math Function':
     *  Operator: reciprocal
     */
    Controller_P7_B.MathFunction_l[0] = UnitDelay3;

    /* S-Function (sdspdiag2): '<S228>/Extract Diagonal' incorporates:
     *  S-Function (sdspldl2): '<S228>/LDL Factorization'
     */
    Controller_P7_B.d_e[1] = Controller_P7_B.LDLFactorization_g[3];

    /* Math: '<S228>/Math Function'
     *
     * About '<S228>/Math Function':
     *  Operator: reciprocal
     */
    UnitDelay3 = Controller_P7_B.d_e[1];
    UnitDelay3 = 1.0F / UnitDelay3;

    /* Math: '<S228>/Math Function'
     *
     * About '<S228>/Math Function':
     *  Operator: reciprocal
     */
    Controller_P7_B.MathFunction_l[1] = UnitDelay3;

    /* S-Function (sdspdmult2): '<S228>/Matrix Scaling' incorporates:
     *  S-Function (sdspfbsub2): '<S228>/Forward Substitution'
     */
    idxS = 0;
    for (i = 0; i < 4; i++) {
      idxV = 0;
      for (k = 0; k < 2; k++) {
        Controller_P7_B.MatrixScaling_m[idxS] = Controller_P7_B.y_e[idxS] *
          Controller_P7_B.MathFunction_l[idxV];
        idxS++;
        idxV++;
      }
    }

    /* End of S-Function (sdspdmult2): '<S228>/Matrix Scaling' */

    /* S-Function (sdspfbsub2): '<S228>/Backward Substitution' incorporates:
     *  S-Function (sdspdmult2): '<S228>/Matrix Scaling'
     *  S-Function (sdspldl2): '<S228>/LDL Factorization'
     */
    Controller_P7_B.BackwardSubstitution_d[1] = Controller_P7_B.MatrixScaling_m
      [1];
    UnitDelay3 = Controller_P7_B.MatrixScaling_m[0];
    UnitDelay3 -= Controller_P7_B.BackwardSubstitution_d[1] *
      Controller_P7_B.LDLFactorization_g[2];
    Controller_P7_B.BackwardSubstitution_d[0] = UnitDelay3;
    Controller_P7_B.BackwardSubstitution_d[3] = Controller_P7_B.MatrixScaling_m
      [3];
    UnitDelay3 = Controller_P7_B.MatrixScaling_m[2];
    UnitDelay3 -= Controller_P7_B.LDLFactorization_g[2] *
      Controller_P7_B.BackwardSubstitution_d[3];
    Controller_P7_B.BackwardSubstitution_d[2] = UnitDelay3;
    Controller_P7_B.BackwardSubstitution_d[5] = Controller_P7_B.MatrixScaling_m
      [5];
    UnitDelay3 = Controller_P7_B.MatrixScaling_m[4];
    UnitDelay3 -= Controller_P7_B.LDLFactorization_g[2] *
      Controller_P7_B.BackwardSubstitution_d[5];
    Controller_P7_B.BackwardSubstitution_d[4] = UnitDelay3;
    Controller_P7_B.BackwardSubstitution_d[7] = Controller_P7_B.MatrixScaling_m
      [7];
    UnitDelay3 = Controller_P7_B.MatrixScaling_m[6];
    UnitDelay3 -= Controller_P7_B.LDLFactorization_g[2] *
      Controller_P7_B.BackwardSubstitution_d[7];
    Controller_P7_B.BackwardSubstitution_d[6] = UnitDelay3;
    for (i = 0; i < 2; i++) {
      /* Math: '<S224>/K Trans' */
      idxS = i << 2;

      /* Math: '<S224>/K Trans' incorporates:
       *  S-Function (sdspfbsub2): '<S228>/Backward Substitution'
       */
      Controller_P7_B.KTrans_c[idxS] = Controller_P7_B.BackwardSubstitution_d[i];
      Controller_P7_B.KTrans_c[idxS + 1] =
        Controller_P7_B.BackwardSubstitution_d[i + 2];
      Controller_P7_B.KTrans_c[idxS + 2] =
        Controller_P7_B.BackwardSubstitution_d[i + 4];
      Controller_P7_B.KTrans_c[idxS + 3] =
        Controller_P7_B.BackwardSubstitution_d[i + 6];
    }

    /* Product: '<S224>/K*H*P_prd' incorporates:
     *  Math: '<S224>/K Trans'
     *  Selector: '<S223>/Selector2'
     */
    memcpy(&tmp_0[0], &Controller_P7_B.Selector2_j[0], sizeof(real32_T) << 4U);
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
      tmp_1[i] = Controller_P7_B.KTrans_c[i];
    }

    for (i = 0; i < 4; i++) {
      HP_prdt_p = 0.0F;
      HP_prdt_p_0 = 0.0F;
      KHP_prd_p = 0.0F;
      KHP_prd_p_0 = 0.0F;
      for (idxS = 0; idxS < 2; idxS++) {
        UnitDelay3 = v1[(i << 1) + idxS];
        idxV = idxS << 2;
        HP_prdt_p += tmp_1[idxV] * UnitDelay3;
        HP_prdt_p_0 += tmp_1[idxV + 1] * UnitDelay3;
        KHP_prd_p += tmp_1[idxV + 2] * UnitDelay3;
        KHP_prd_p_0 += tmp_1[idxV + 3] * UnitDelay3;
      }

      idxV = i << 2;
      Controller_P7_B.KHP_prd_p[idxV + 3] = KHP_prd_p_0;
      Controller_P7_B.KHP_prd_p[idxV + 2] = KHP_prd_p;
      Controller_P7_B.KHP_prd_p[idxV + 1] = HP_prdt_p_0;
      Controller_P7_B.KHP_prd_p[idxV] = HP_prdt_p;
    }

    /* End of Product: '<S224>/K*H*P_prd' */
    for (i = 0; i < 16; i++) {
      /* Sum: '<S224>/P_prd-K*H*P_prd' incorporates:
       *  Product: '<S224>/K*H*P_prd'
       *  Selector: '<S223>/Selector2'
       */
      UnitDelay3 = Controller_P7_B.Selector2_j[i] - Controller_P7_B.KHP_prd_p[i];
      Controller_P7_B.P_prdKHP_prd_k[i] = UnitDelay3;

      /* Product: '<S224>/A*P*At' incorporates:
       *  Constant: '<S224>/Constant4'
       *  Sum: '<S224>/P_prd-K*H*P_prd'
       */
      tmp_0[i] = UnitDelay3;
      tmp_2[i] = Controller_P7_P.Constant4_Value[i];
    }

    /* Product: '<S224>/A*P*At' incorporates:
     *  Constant: '<S224>/Constant3'
     */
    for (i = 0; i < 4; i++) {
      HP_prdt = 0.0F;
      HP_prdt_0 = 0.0F;
      HP_prdt_p = 0.0F;
      HP_prdt_p_0 = 0.0F;
      for (idxS = 0; idxS < 4; idxS++) {
        UnitDelay3 = tmp_2[(i << 2) + idxS];
        idxV = idxS << 2;
        HP_prdt += tmp_0[idxV] * UnitDelay3;
        HP_prdt_0 += tmp_0[idxV + 1] * UnitDelay3;
        HP_prdt_p += tmp_0[idxV + 2] * UnitDelay3;
        HP_prdt_p_0 += tmp_0[idxV + 3] * UnitDelay3;
      }

      idxV = i << 2;
      v1_0[idxV + 3] = HP_prdt_p_0;
      v1_0[idxV + 2] = HP_prdt_p;
      v1_0[idxV + 1] = HP_prdt_0;
      v1_0[idxV] = HP_prdt;
    }

    memcpy(&tmp_0[0], &Controller_P7_P.Constant3_Value[0], sizeof(real32_T) <<
           4U);
    for (i = 0; i < 4; i++) {
      HP_prdt_p = 0.0F;
      HP_prdt_p_0 = 0.0F;
      KHP_prd_p = 0.0F;
      KHP_prd_p_0 = 0.0F;
      for (idxS = 0; idxS < 4; idxS++) {
        UnitDelay3 = v1_0[(i << 2) + idxS];
        idxV = idxS << 2;
        HP_prdt_p += tmp_0[idxV] * UnitDelay3;
        HP_prdt_p_0 += tmp_0[idxV + 1] * UnitDelay3;
        KHP_prd_p += tmp_0[idxV + 2] * UnitDelay3;
        KHP_prd_p_0 += tmp_0[idxV + 3] * UnitDelay3;
      }

      idxV = i << 2;
      Controller_P7_B.APAt_g[idxV + 3] = KHP_prd_p_0;
      Controller_P7_B.APAt_g[idxV + 2] = KHP_prd_p;
      Controller_P7_B.APAt_g[idxV + 1] = HP_prdt_p_0;
      Controller_P7_B.APAt_g[idxV] = HP_prdt_p;
    }

    for (i = 0; i < 16; i++) {
      /* Sum: '<S224>/A*P*At+Q' incorporates:
       *  Constant: '<S224>/Constant5'
       *  Product: '<S224>/A*P*At'
       */
      Controller_P7_B.APAtQ_h[i] = Controller_P7_B.APAt_g[i] +
        Controller_P7_P.Constant5_Value[i];
    }

    /* Product: '<S224>/H*X_prd' incorporates:
     *  Selector: '<S223>/Selector1'
     */
    tmp_3[0] = Controller_P7_B.Selector1_b[0];
    tmp_3[1] = Controller_P7_B.Selector1_b[1];
    tmp_3[2] = Controller_P7_B.Selector1_b[2];
    tmp_3[3] = Controller_P7_B.Selector1_b[3];
    HP_prdt_p = 0.0F;
    HP_prdt_p_0 = 0.0F;
    for (i = 0; i < 4; i++) {
      UnitDelay3 = tmp_3[i];
      idxS = i << 1;
      HP_prdt_p += tmp[idxS] * UnitDelay3;
      HP_prdt_p_0 += tmp[idxS + 1] * UnitDelay3;
    }

    Controller_P7_B.HX_prd_b[1] = HP_prdt_p_0;
    Controller_P7_B.HX_prd_b[0] = HP_prdt_p;

    /* End of Product: '<S224>/H*X_prd' */

    /* Sum: '<S224>/Z-H*X_prd' incorporates:
     *  Product: '<S224>/H*X_prd'
     *  Selector: '<S223>/Selector'
     */
    UnitDelay3 = Controller_P7_B.Selector_f[0] - Controller_P7_B.HX_prd_b[0];
    Controller_P7_B.ZHX_prd_h[0] = UnitDelay3;

    /* Product: '<S224>/K*(Z-H*X_prd)' incorporates:
     *  Sum: '<S224>/Z-H*X_prd'
     */
    tmp_7[0] = UnitDelay3;

    /* Sum: '<S224>/Z-H*X_prd' incorporates:
     *  Product: '<S224>/H*X_prd'
     *  Selector: '<S223>/Selector'
     */
    UnitDelay3 = Controller_P7_B.Selector_f[1] - Controller_P7_B.HX_prd_b[1];
    Controller_P7_B.ZHX_prd_h[1] = UnitDelay3;

    /* Product: '<S224>/K*(Z-H*X_prd)' incorporates:
     *  Sum: '<S224>/Z-H*X_prd'
     */
    tmp_7[1] = UnitDelay3;
    HP_prdt_p = 0.0F;
    HP_prdt_p_0 = 0.0F;
    KHP_prd_p = 0.0F;
    KHP_prd_p_0 = 0.0F;
    for (i = 0; i < 2; i++) {
      UnitDelay3 = tmp_7[i];
      idxS = i << 2;
      HP_prdt_p += tmp_1[idxS] * UnitDelay3;
      HP_prdt_p_0 += tmp_1[idxS + 1] * UnitDelay3;
      KHP_prd_p += tmp_1[idxS + 2] * UnitDelay3;
      KHP_prd_p_0 += tmp_1[idxS + 3] * UnitDelay3;
    }

    Controller_P7_B.KZHX_prd_c[3] = KHP_prd_p_0;
    Controller_P7_B.KZHX_prd_c[2] = KHP_prd_p;
    Controller_P7_B.KZHX_prd_c[1] = HP_prdt_p_0;
    Controller_P7_B.KZHX_prd_c[0] = HP_prdt_p;

    /* Sum: '<S224>/X_prd+K*(Z-H*X_prd)' incorporates:
     *  Product: '<S224>/K*(Z-H*X_prd)'
     *  Selector: '<S223>/Selector1'
     */
    UnitDelay3 = Controller_P7_B.Selector1_b[0] + Controller_P7_B.KZHX_prd_c[0];
    Controller_P7_B.X_prdKZHX_prd_i[0] = UnitDelay3;

    /* Product: '<S224>/A*X' incorporates:
     *  Sum: '<S224>/X_prd+K*(Z-H*X_prd)'
     */
    tmp_3[0] = UnitDelay3;

    /* Sum: '<S224>/X_prd+K*(Z-H*X_prd)' incorporates:
     *  Product: '<S224>/K*(Z-H*X_prd)'
     *  Selector: '<S223>/Selector1'
     */
    UnitDelay3 = Controller_P7_B.Selector1_b[1] + Controller_P7_B.KZHX_prd_c[1];
    Controller_P7_B.X_prdKZHX_prd_i[1] = UnitDelay3;

    /* Product: '<S224>/A*X' incorporates:
     *  Sum: '<S224>/X_prd+K*(Z-H*X_prd)'
     */
    tmp_3[1] = UnitDelay3;

    /* Sum: '<S224>/X_prd+K*(Z-H*X_prd)' incorporates:
     *  Product: '<S224>/K*(Z-H*X_prd)'
     *  Selector: '<S223>/Selector1'
     */
    UnitDelay3 = Controller_P7_B.Selector1_b[2] + Controller_P7_B.KZHX_prd_c[2];
    Controller_P7_B.X_prdKZHX_prd_i[2] = UnitDelay3;

    /* Product: '<S224>/A*X' incorporates:
     *  Sum: '<S224>/X_prd+K*(Z-H*X_prd)'
     */
    tmp_3[2] = UnitDelay3;

    /* Sum: '<S224>/X_prd+K*(Z-H*X_prd)' incorporates:
     *  Product: '<S224>/K*(Z-H*X_prd)'
     *  Selector: '<S223>/Selector1'
     */
    UnitDelay3 = Controller_P7_B.Selector1_b[3] + Controller_P7_B.KZHX_prd_c[3];
    Controller_P7_B.X_prdKZHX_prd_i[3] = UnitDelay3;

    /* Product: '<S224>/A*X' incorporates:
     *  Sum: '<S224>/X_prd+K*(Z-H*X_prd)'
     */
    tmp_3[3] = UnitDelay3;
    HP_prdt_p = 0.0F;
    HP_prdt_p_0 = 0.0F;
    KHP_prd_p = 0.0F;
    KHP_prd_p_0 = 0.0F;
    for (i = 0; i < 4; i++) {
      UnitDelay3 = tmp_3[i];
      idxS = i << 2;
      HP_prdt_p += tmp_0[idxS] * UnitDelay3;
      HP_prdt_p_0 += tmp_0[idxS + 1] * UnitDelay3;
      KHP_prd_p += tmp_0[idxS + 2] * UnitDelay3;
      KHP_prd_p_0 += tmp_0[idxS + 3] * UnitDelay3;
    }

    Controller_P7_B.AX_f[3] = KHP_prd_p_0;
    Controller_P7_B.AX_f[2] = KHP_prd_p;
    Controller_P7_B.AX_f[1] = HP_prdt_p_0;
    Controller_P7_B.AX_f[0] = HP_prdt_p;

    /* Assignment: '<S225>/Assignment' incorporates:
     *  Sum: '<S224>/A*P*At+Q'
     */
    memcpy(&Controller_P7_B.Assignment_d[0], &Controller_P7_B.APAtQ_h[0], sizeof
           (real32_T) << 4U);

    /* Assignment: '<S226>/Assignment' incorporates:
     *  Sum: '<S224>/X_prd+K*(Z-H*X_prd)'
     */
    Controller_P7_B.Assignment_dh[0] = Controller_P7_B.X_prdKZHX_prd_i[0];

    /* Assignment: '<S227>/Assignment' incorporates:
     *  Product: '<S224>/A*X'
     */
    Controller_P7_B.Assignment_g[0] = Controller_P7_B.AX_f[0];

    /* Assignment: '<S226>/Assignment' incorporates:
     *  Sum: '<S224>/X_prd+K*(Z-H*X_prd)'
     */
    Controller_P7_B.Assignment_dh[1] = Controller_P7_B.X_prdKZHX_prd_i[1];

    /* Assignment: '<S227>/Assignment' incorporates:
     *  Product: '<S224>/A*X'
     */
    Controller_P7_B.Assignment_g[1] = Controller_P7_B.AX_f[1];

    /* Assignment: '<S226>/Assignment' incorporates:
     *  Sum: '<S224>/X_prd+K*(Z-H*X_prd)'
     */
    Controller_P7_B.Assignment_dh[2] = Controller_P7_B.X_prdKZHX_prd_i[2];

    /* Assignment: '<S227>/Assignment' incorporates:
     *  Product: '<S224>/A*X'
     */
    Controller_P7_B.Assignment_g[2] = Controller_P7_B.AX_f[2];

    /* Assignment: '<S226>/Assignment' incorporates:
     *  Sum: '<S224>/X_prd+K*(Z-H*X_prd)'
     */
    Controller_P7_B.Assignment_dh[3] = Controller_P7_B.X_prdKZHX_prd_i[3];

    /* Assignment: '<S227>/Assignment' incorporates:
     *  Product: '<S224>/A*X'
     */
    Controller_P7_B.Assignment_g[3] = Controller_P7_B.AX_f[3];
    s222_iter++;
  }

  /* End of Outputs for SubSystem: '<S219>/Control' */

  /* Lookup_n-D: '<S2>/1-D Lookup Table1' incorporates:
   *  Inport: '<Root>/Theta_Helix'
   */
  Controller_P7_B.SheaveDisplacementin = look1_iflf_binlxpw
    (Controller_P7_U.Theta_Helix, Controller_P7_P.uDLookupTable1_bp01Data,
     Controller_P7_P.uDLookupTable1_tableData, 31U);

  /* Lookup_n-D: '<S2>/1-D Lookup Table' incorporates:
   *  Lookup_n-D: '<S2>/1-D Lookup Table1'
   */
  Controller_P7_B.phi1 = look1_iflf_binlxpw(Controller_P7_B.SheaveDisplacementin,
    Controller_P7_P.uDLookupTable_bp01Data,
    Controller_P7_P.uDLookupTable_tableData, 140U);

  /* Product: '<S2>/Divide' */
  Controller_P7_B.Phi2 = Controller_P7_B.Assignment_dh[0] /
    Controller_P7_B.Assignment_dh[2];

  /* UnitDelay: '<S220>/Unit Delay2' */
  Controller_P7_B.UnitDelay2_o[0] = Controller_P7_DW.UnitDelay2_DSTATE_b[0];
  Controller_P7_B.UnitDelay2_o[1] = Controller_P7_DW.UnitDelay2_DSTATE_b[1];

  /* UnitDelay: '<S220>/Unit Delay3' */
  UnitDelay3 = Controller_P7_DW.UnitDelay3_DSTATE_f[0];
  Controller_P7_B.UnitDelay3_c[0] = UnitDelay3;

  /* Outputs for Iterator SubSystem: '<S220>/Control' incorporates:
   *  ForIterator: '<S233>/Iterator'
   */
  /* Assignment: '<S236>/Assignment' incorporates:
   *  UnitDelay: '<S220>/Unit Delay3'
   */
  Controller_P7_B.Assignment[0] = UnitDelay3;

  /* End of Outputs for SubSystem: '<S220>/Control' */

  /* UnitDelay: '<S220>/Unit Delay3' */
  UnitDelay3 = Controller_P7_DW.UnitDelay3_DSTATE_f[1];
  Controller_P7_B.UnitDelay3_c[1] = UnitDelay3;

  /* Outputs for Iterator SubSystem: '<S220>/Control' incorporates:
   *  ForIterator: '<S233>/Iterator'
   */
  /* Assignment: '<S236>/Assignment' incorporates:
   *  UnitDelay: '<S220>/Unit Delay3'
   */
  Controller_P7_B.Assignment[1] = UnitDelay3;

  /* End of Outputs for SubSystem: '<S220>/Control' */

  /* UnitDelay: '<S220>/Unit Delay3' */
  UnitDelay3 = Controller_P7_DW.UnitDelay3_DSTATE_f[2];
  Controller_P7_B.UnitDelay3_c[2] = UnitDelay3;

  /* Outputs for Iterator SubSystem: '<S220>/Control' incorporates:
   *  ForIterator: '<S233>/Iterator'
   */
  /* Assignment: '<S236>/Assignment' incorporates:
   *  UnitDelay: '<S220>/Unit Delay3'
   */
  Controller_P7_B.Assignment[2] = UnitDelay3;

  /* End of Outputs for SubSystem: '<S220>/Control' */

  /* UnitDelay: '<S220>/Unit Delay3' */
  UnitDelay3 = Controller_P7_DW.UnitDelay3_DSTATE_f[3];
  Controller_P7_B.UnitDelay3_c[3] = UnitDelay3;

  /* Outputs for Iterator SubSystem: '<S220>/Control' incorporates:
   *  ForIterator: '<S233>/Iterator'
   */
  /* Assignment: '<S236>/Assignment' incorporates:
   *  UnitDelay: '<S220>/Unit Delay3'
   */
  Controller_P7_B.Assignment[3] = UnitDelay3;

  /* Assignment: '<S238>/Assignment' incorporates:
   *  UnitDelay: '<S220>/Unit Delay2'
   */
  Controller_P7_B.Assignment_m[0] = Controller_P7_B.UnitDelay2_o[0];
  Controller_P7_B.Assignment_m[1] = Controller_P7_B.UnitDelay2_o[1];
  s222_iter = 1;
  if (Controller_P7_P.Iterator_IterationLimit_n >= 1) {
    /* Selector: '<S234>/Selector2' incorporates:
     *  UnitDelay: '<S220>/Unit Delay3'
     */
    Controller_P7_B.Selector2[0] = Controller_P7_B.UnitDelay3_c[0];
    Controller_P7_B.Selector2[1] = Controller_P7_B.UnitDelay3_c[1];
    Controller_P7_B.Selector2[2] = Controller_P7_B.UnitDelay3_c[2];
    Controller_P7_B.Selector2[3] = Controller_P7_B.UnitDelay3_c[3];

    /* Math: '<S235>/P_prd Trans' incorporates:
     *  Selector: '<S234>/Selector2'
     */
    Controller_P7_B.P_prdTrans[0] = Controller_P7_B.Selector2[0];
    Controller_P7_B.P_prdTrans[1] = Controller_P7_B.Selector2[2];
    Controller_P7_B.P_prdTrans[2] = Controller_P7_B.Selector2[1];
    Controller_P7_B.P_prdTrans[3] = Controller_P7_B.Selector2[3];

    /* Product: '<S235>/H*P_prdt' incorporates:
     *  Constant: '<S235>/Hcst'
     */
    tmp_3[0] = Controller_P7_P.Hcst_Value_e[0];
    tmp_3[1] = Controller_P7_P.Hcst_Value_e[1];
    tmp_3[2] = Controller_P7_P.Hcst_Value_e[2];
    tmp_3[3] = Controller_P7_P.Hcst_Value_e[3];

    /* Product: '<S235>/A*P*At' incorporates:
     *  Constant: '<S235>/Constant4'
     */
    tmp_6[0] = Controller_P7_P.Constant4_Value_l[0];
    tmp_6[1] = Controller_P7_P.Constant4_Value_l[1];
    tmp_6[2] = Controller_P7_P.Constant4_Value_l[2];
    tmp_6[3] = Controller_P7_P.Constant4_Value_l[3];

    /* SignalConversion generated from: '<S234>/Selector' */
    Controller_P7_B.TmpSignalConversionAtSelectorIn[0] = Controller_P7_B.phi1;
    Controller_P7_B.TmpSignalConversionAtSelectorIn[1] = Controller_P7_B.Phi2;

    /* Selector: '<S234>/Selector' incorporates:
     *  SignalConversion generated from: '<S234>/Selector'
     */
    Controller_P7_B.Selector[0] =
      Controller_P7_B.TmpSignalConversionAtSelectorIn[0];
    Controller_P7_B.Selector[1] =
      Controller_P7_B.TmpSignalConversionAtSelectorIn[1];
  }

  while (s222_iter <= Controller_P7_P.Iterator_IterationLimit_n) {
    /* Outputs for Iterator SubSystem: '<S220>/Control' incorporates:
     *  ForIterator: '<S233>/Iterator'
     */
    Controller_P7_B.Iterator = s222_iter;

    /* Product: '<S235>/H*P_prdt' incorporates:
     *  Math: '<S235>/P_prd Trans'
     */
    tmp_4[0] = Controller_P7_B.P_prdTrans[0];
    tmp_4[1] = Controller_P7_B.P_prdTrans[1];
    tmp_4[2] = Controller_P7_B.P_prdTrans[2];
    tmp_4[3] = Controller_P7_B.P_prdTrans[3];
    UnitDelay3 = tmp_3[0];
    HP_prdt_p = tmp_3[1];
    HP_prdt_p_0 = tmp_3[2];
    KHP_prd_p = tmp_3[3];
    for (i = 0; i < 2; i++) {
      idxS = i << 1;
      KHP_prd_p_0 = tmp_4[idxS];
      HP_prdt = UnitDelay3 * KHP_prd_p_0;
      HP_prdt_0 = HP_prdt_p * KHP_prd_p_0;
      idxV = idxS + 1;
      KHP_prd_p_0 = tmp_4[idxV];
      HP_prdt += HP_prdt_p_0 * KHP_prd_p_0;
      Controller_P7_B.HP_prdt[idxS] = HP_prdt;
      HP_prdt_0 += KHP_prd_p * KHP_prd_p_0;
      Controller_P7_B.HP_prdt[idxV] = HP_prdt_0;
    }

    /* Product: '<S235>/H*P_prdt*Ht' incorporates:
     *  Constant: '<S235>/Hcst_t'
     *  Product: '<S235>/H*P_prdt'
     */
    tmp_4[0] = Controller_P7_B.HP_prdt[0];
    tmp_5[0] = Controller_P7_P.Hcst_t_Value_c[0];
    tmp_4[1] = Controller_P7_B.HP_prdt[1];
    tmp_5[1] = Controller_P7_P.Hcst_t_Value_c[1];
    tmp_4[2] = Controller_P7_B.HP_prdt[2];
    tmp_5[2] = Controller_P7_P.Hcst_t_Value_c[2];
    tmp_4[3] = Controller_P7_B.HP_prdt[3];
    tmp_5[3] = Controller_P7_P.Hcst_t_Value_c[3];
    UnitDelay3 = tmp_4[0];
    HP_prdt_p = tmp_4[1];
    HP_prdt_p_0 = tmp_4[2];
    KHP_prd_p = tmp_4[3];
    for (i = 0; i < 2; i++) {
      idxS = i << 1;
      KHP_prd_p_0 = tmp_5[idxS];
      HP_prdt = UnitDelay3 * KHP_prd_p_0;
      HP_prdt_0 = HP_prdt_p * KHP_prd_p_0;
      idxV = idxS + 1;
      KHP_prd_p_0 = tmp_5[idxV];
      HP_prdt += HP_prdt_p_0 * KHP_prd_p_0;
      Controller_P7_B.HP_prdtHt[idxS] = HP_prdt;
      HP_prdt_0 += KHP_prd_p * KHP_prd_p_0;
      Controller_P7_B.HP_prdtHt[idxV] = HP_prdt_0;
    }

    /* End of Product: '<S235>/H*P_prdt*Ht' */

    /* Sum: '<S235>/H*P_prdt*Ht+R' incorporates:
     *  Constant: '<S235>/Constant2'
     *  Product: '<S235>/H*P_prdt*Ht'
     */
    UnitDelay3 = Controller_P7_B.HP_prdtHt[0] +
      Controller_P7_P.Constant2_Value_l[0];
    Controller_P7_B.HP_prdtHtR[0] = UnitDelay3;

    /* S-Function (sdspldl2): '<S239>/LDL Factorization' incorporates:
     *  Sum: '<S235>/H*P_prdt*Ht+R'
     */
    Controller_P7_B.LDLFactorization[0] = UnitDelay3;

    /* Sum: '<S235>/H*P_prdt*Ht+R' incorporates:
     *  Constant: '<S235>/Constant2'
     *  Product: '<S235>/H*P_prdt*Ht'
     */
    UnitDelay3 = Controller_P7_B.HP_prdtHt[1] +
      Controller_P7_P.Constant2_Value_l[1];
    Controller_P7_B.HP_prdtHtR[1] = UnitDelay3;

    /* S-Function (sdspldl2): '<S239>/LDL Factorization' incorporates:
     *  Sum: '<S235>/H*P_prdt*Ht+R'
     */
    Controller_P7_B.LDLFactorization[1] = UnitDelay3;

    /* Sum: '<S235>/H*P_prdt*Ht+R' incorporates:
     *  Constant: '<S235>/Constant2'
     *  Product: '<S235>/H*P_prdt*Ht'
     */
    UnitDelay3 = Controller_P7_B.HP_prdtHt[2] +
      Controller_P7_P.Constant2_Value_l[2];
    Controller_P7_B.HP_prdtHtR[2] = UnitDelay3;

    /* S-Function (sdspldl2): '<S239>/LDL Factorization' incorporates:
     *  Sum: '<S235>/H*P_prdt*Ht+R'
     */
    Controller_P7_B.LDLFactorization[2] = UnitDelay3;

    /* Sum: '<S235>/H*P_prdt*Ht+R' incorporates:
     *  Constant: '<S235>/Constant2'
     *  Product: '<S235>/H*P_prdt*Ht'
     */
    UnitDelay3 = Controller_P7_B.HP_prdtHt[3] +
      Controller_P7_P.Constant2_Value_l[3];
    Controller_P7_B.HP_prdtHtR[3] = UnitDelay3;

    /* S-Function (sdspldl2): '<S239>/LDL Factorization' incorporates:
     *  Sum: '<S235>/H*P_prdt*Ht+R'
     */
    Controller_P7_B.LDLFactorization[3] = UnitDelay3;

    /* S-Function (sdspldl2): '<S239>/LDL Factorization' incorporates:
     *  Sum: '<S235>/H*P_prdt*Ht+R'
     */
    LDLf_int32_Treal32_T(&Controller_P7_B.LDLFactorization[0U],
                         &Controller_P7_DW.LDLFactorization_VMX[0U], 2,
                         &Controller_P7_B.HP_prdtHtR[0U]);

    /* S-Function (sdspfbsub2): '<S239>/Forward Substitution' incorporates:
     *  Product: '<S235>/H*P_prdt'
     *  S-Function (sdspldl2): '<S239>/LDL Factorization'
     */
    Controller_P7_B.y[0] = Controller_P7_B.HP_prdt[0];
    UnitDelay3 = Controller_P7_B.HP_prdt[1];
    UnitDelay3 -= Controller_P7_B.y[0] * Controller_P7_B.LDLFactorization[1];
    Controller_P7_B.y[1] = UnitDelay3;

    /* S-Function (sdspdiag2): '<S239>/Extract Diagonal' incorporates:
     *  S-Function (sdspldl2): '<S239>/LDL Factorization'
     */
    Controller_P7_B.d[0] = Controller_P7_B.LDLFactorization[0];

    /* Math: '<S239>/Math Function'
     *
     * About '<S239>/Math Function':
     *  Operator: reciprocal
     */
    UnitDelay3 = Controller_P7_B.d[0];
    UnitDelay3 = 1.0F / UnitDelay3;

    /* Math: '<S239>/Math Function'
     *
     * About '<S239>/Math Function':
     *  Operator: reciprocal
     */
    Controller_P7_B.MathFunction[0] = UnitDelay3;

    /* S-Function (sdspfbsub2): '<S239>/Forward Substitution' incorporates:
     *  Product: '<S235>/H*P_prdt'
     *  S-Function (sdspldl2): '<S239>/LDL Factorization'
     */
    Controller_P7_B.y[2] = Controller_P7_B.HP_prdt[2];
    UnitDelay3 = Controller_P7_B.HP_prdt[3];
    UnitDelay3 -= Controller_P7_B.LDLFactorization[1] * Controller_P7_B.y[2];
    Controller_P7_B.y[3] = UnitDelay3;

    /* S-Function (sdspdiag2): '<S239>/Extract Diagonal' incorporates:
     *  S-Function (sdspldl2): '<S239>/LDL Factorization'
     */
    Controller_P7_B.d[1] = Controller_P7_B.LDLFactorization[3];

    /* Math: '<S239>/Math Function'
     *
     * About '<S239>/Math Function':
     *  Operator: reciprocal
     */
    UnitDelay3 = Controller_P7_B.d[1];
    UnitDelay3 = 1.0F / UnitDelay3;

    /* Math: '<S239>/Math Function'
     *
     * About '<S239>/Math Function':
     *  Operator: reciprocal
     */
    Controller_P7_B.MathFunction[1] = UnitDelay3;

    /* S-Function (sdspdmult2): '<S239>/Matrix Scaling' incorporates:
     *  S-Function (sdspfbsub2): '<S239>/Forward Substitution'
     */
    idxS = 0;
    for (i = 0; i < 2; i++) {
      idxV = 0;
      for (k = 0; k < 2; k++) {
        Controller_P7_B.MatrixScaling[idxS] = Controller_P7_B.y[idxS] *
          Controller_P7_B.MathFunction[idxV];
        idxS++;
        idxV++;
      }
    }

    /* End of S-Function (sdspdmult2): '<S239>/Matrix Scaling' */

    /* S-Function (sdspfbsub2): '<S239>/Backward Substitution' incorporates:
     *  S-Function (sdspdmult2): '<S239>/Matrix Scaling'
     *  S-Function (sdspldl2): '<S239>/LDL Factorization'
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

    /* Math: '<S235>/K Trans' incorporates:
     *  S-Function (sdspfbsub2): '<S239>/Backward Substitution'
     */
    Controller_P7_B.KTrans[0] = Controller_P7_B.BackwardSubstitution[0];
    Controller_P7_B.KTrans[1] = Controller_P7_B.BackwardSubstitution[2];
    Controller_P7_B.KTrans[2] = Controller_P7_B.BackwardSubstitution[1];
    Controller_P7_B.KTrans[3] = Controller_P7_B.BackwardSubstitution[3];

    /* Product: '<S235>/K*H*P_prd' incorporates:
     *  Math: '<S235>/K Trans'
     *  Selector: '<S234>/Selector2'
     */
    tmp_4[0] = Controller_P7_B.Selector2[0];
    tmp_4[1] = Controller_P7_B.Selector2[1];
    tmp_4[2] = Controller_P7_B.Selector2[2];
    tmp_4[3] = Controller_P7_B.Selector2[3];
    UnitDelay3 = tmp_3[0];
    HP_prdt_p = tmp_3[1];
    HP_prdt_p_0 = tmp_3[2];
    KHP_prd_p = tmp_3[3];
    for (i = 0; i < 2; i++) {
      idxS = i << 1;
      KHP_prd_p_0 = tmp_4[idxS];
      HP_prdt = UnitDelay3 * KHP_prd_p_0;
      HP_prdt_0 = HP_prdt_p * KHP_prd_p_0;
      idxV = idxS + 1;
      KHP_prd_p_0 = tmp_4[idxV];
      HP_prdt += HP_prdt_p_0 * KHP_prd_p_0;
      v1_1[idxS] = HP_prdt;
      HP_prdt_0 += KHP_prd_p * KHP_prd_p_0;
      v1_1[idxV] = HP_prdt_0;
    }

    tmp_4[0] = Controller_P7_B.KTrans[0];
    tmp_4[1] = Controller_P7_B.KTrans[1];
    tmp_4[2] = Controller_P7_B.KTrans[2];
    tmp_4[3] = Controller_P7_B.KTrans[3];
    UnitDelay3 = tmp_4[0];
    HP_prdt_p = tmp_4[1];
    HP_prdt_p_0 = tmp_4[2];
    KHP_prd_p = tmp_4[3];
    for (i = 0; i < 2; i++) {
      idxS = i << 1;
      KHP_prd_p_0 = v1_1[idxS];
      HP_prdt = UnitDelay3 * KHP_prd_p_0;
      HP_prdt_0 = HP_prdt_p * KHP_prd_p_0;
      idxV = idxS + 1;
      KHP_prd_p_0 = v1_1[idxV];
      HP_prdt += HP_prdt_p_0 * KHP_prd_p_0;
      Controller_P7_B.KHP_prd[idxS] = HP_prdt;
      HP_prdt_0 += KHP_prd_p * KHP_prd_p_0;
      Controller_P7_B.KHP_prd[idxV] = HP_prdt_0;
    }

    /* End of Product: '<S235>/K*H*P_prd' */

    /* Sum: '<S235>/P_prd-K*H*P_prd' incorporates:
     *  Product: '<S235>/K*H*P_prd'
     *  Selector: '<S234>/Selector2'
     */
    UnitDelay3 = Controller_P7_B.Selector2[0] - Controller_P7_B.KHP_prd[0];
    Controller_P7_B.P_prdKHP_prd[0] = UnitDelay3;

    /* Product: '<S235>/A*P*At' incorporates:
     *  Sum: '<S235>/P_prd-K*H*P_prd'
     */
    tmp_5[0] = UnitDelay3;

    /* Sum: '<S235>/P_prd-K*H*P_prd' incorporates:
     *  Product: '<S235>/K*H*P_prd'
     *  Selector: '<S234>/Selector2'
     */
    UnitDelay3 = Controller_P7_B.Selector2[1] - Controller_P7_B.KHP_prd[1];
    Controller_P7_B.P_prdKHP_prd[1] = UnitDelay3;

    /* Product: '<S235>/A*P*At' incorporates:
     *  Sum: '<S235>/P_prd-K*H*P_prd'
     */
    tmp_5[1] = UnitDelay3;

    /* Sum: '<S235>/P_prd-K*H*P_prd' incorporates:
     *  Product: '<S235>/K*H*P_prd'
     *  Selector: '<S234>/Selector2'
     */
    UnitDelay3 = Controller_P7_B.Selector2[2] - Controller_P7_B.KHP_prd[2];
    Controller_P7_B.P_prdKHP_prd[2] = UnitDelay3;

    /* Product: '<S235>/A*P*At' incorporates:
     *  Sum: '<S235>/P_prd-K*H*P_prd'
     */
    tmp_5[2] = UnitDelay3;

    /* Sum: '<S235>/P_prd-K*H*P_prd' incorporates:
     *  Product: '<S235>/K*H*P_prd'
     *  Selector: '<S234>/Selector2'
     */
    UnitDelay3 = Controller_P7_B.Selector2[3] - Controller_P7_B.KHP_prd[3];
    Controller_P7_B.P_prdKHP_prd[3] = UnitDelay3;

    /* Product: '<S235>/A*P*At' incorporates:
     *  Constant: '<S235>/Constant3'
     *  Sum: '<S235>/P_prd-K*H*P_prd'
     */
    tmp_5[3] = UnitDelay3;
    UnitDelay3 = tmp_5[0];
    HP_prdt_p = tmp_5[1];
    HP_prdt_p_0 = tmp_5[2];
    KHP_prd_p = tmp_5[3];
    tmp_5[0] = Controller_P7_P.Constant3_Value_m[0];
    tmp_5[1] = Controller_P7_P.Constant3_Value_m[1];
    tmp_5[2] = Controller_P7_P.Constant3_Value_m[2];
    tmp_5[3] = Controller_P7_P.Constant3_Value_m[3];
    KHP_prd_p_0 = tmp_5[0];
    tmp_9 = tmp_5[1];
    tmp_a = tmp_5[2];
    tmp_b = tmp_5[3];
    for (i = 0; i < 2; i++) {
      idxS = i << 1;
      tmp_8 = tmp_6[idxS];
      HP_prdt = UnitDelay3 * tmp_8;
      HP_prdt_0 = HP_prdt_p * tmp_8;
      idxV = idxS + 1;
      tmp_8 = tmp_6[idxV];
      HP_prdt += HP_prdt_p_0 * tmp_8;
      v1_1[idxS] = HP_prdt;
      HP_prdt_0 += KHP_prd_p * tmp_8;
      v1_1[idxV] = HP_prdt_0;
      tmp_8 = v1_1[idxS];
      HP_prdt = KHP_prd_p_0 * tmp_8;
      HP_prdt_0 = tmp_9 * tmp_8;
      idxV = idxS + 1;
      tmp_8 = v1_1[idxV];
      HP_prdt += tmp_a * tmp_8;
      Controller_P7_B.APAt[idxS] = HP_prdt;
      HP_prdt_0 += tmp_b * tmp_8;
      Controller_P7_B.APAt[idxV] = HP_prdt_0;
    }

    /* Sum: '<S235>/A*P*At+Q' incorporates:
     *  Constant: '<S235>/Constant5'
     *  Product: '<S235>/A*P*At'
     */
    Controller_P7_B.APAtQ[0] = Controller_P7_B.APAt[0] +
      Controller_P7_P.Constant5_Value_k[0];
    Controller_P7_B.APAtQ[1] = Controller_P7_B.APAt[1] +
      Controller_P7_P.Constant5_Value_k[1];
    Controller_P7_B.APAtQ[2] = Controller_P7_B.APAt[2] +
      Controller_P7_P.Constant5_Value_k[2];
    Controller_P7_B.APAtQ[3] = Controller_P7_B.APAt[3] +
      Controller_P7_P.Constant5_Value_k[3];

    /* Selector: '<S234>/Selector1' incorporates:
     *  UnitDelay: '<S220>/Unit Delay2'
     */
    UnitDelay3 = Controller_P7_B.UnitDelay2_o[0];
    Controller_P7_B.Selector1[0] = UnitDelay3;

    /* Product: '<S235>/H*X_prd' incorporates:
     *  Selector: '<S234>/Selector1'
     */
    tmp_7[0] = UnitDelay3;

    /* Selector: '<S234>/Selector1' incorporates:
     *  UnitDelay: '<S220>/Unit Delay2'
     */
    UnitDelay3 = Controller_P7_B.UnitDelay2_o[1];
    Controller_P7_B.Selector1[1] = UnitDelay3;

    /* Product: '<S235>/H*X_prd' incorporates:
     *  Selector: '<S234>/Selector1'
     */
    tmp_7[1] = UnitDelay3;
    UnitDelay3 = tmp_7[0];
    Controller_P7_B.HX_prd[0] = tmp_3[0] * UnitDelay3;
    Controller_P7_B.HX_prd[1] = tmp_3[1] * UnitDelay3;
    UnitDelay3 = tmp_7[1];
    Controller_P7_B.HX_prd[0] += tmp_3[2] * UnitDelay3;
    Controller_P7_B.HX_prd[1] += tmp_3[3] * UnitDelay3;

    /* Sum: '<S235>/Z-H*X_prd' incorporates:
     *  Product: '<S235>/H*X_prd'
     *  Selector: '<S234>/Selector'
     */
    UnitDelay3 = Controller_P7_B.Selector[0] - Controller_P7_B.HX_prd[0];
    Controller_P7_B.ZHX_prd[0] = UnitDelay3;

    /* Product: '<S235>/K*(Z-H*X_prd)' incorporates:
     *  Sum: '<S235>/Z-H*X_prd'
     */
    tmp_7[0] = UnitDelay3;

    /* Sum: '<S235>/Z-H*X_prd' incorporates:
     *  Product: '<S235>/H*X_prd'
     *  Selector: '<S234>/Selector'
     */
    UnitDelay3 = Controller_P7_B.Selector[1] - Controller_P7_B.HX_prd[1];
    Controller_P7_B.ZHX_prd[1] = UnitDelay3;

    /* Product: '<S235>/K*(Z-H*X_prd)' incorporates:
     *  Sum: '<S235>/Z-H*X_prd'
     */
    tmp_7[1] = UnitDelay3;
    UnitDelay3 = tmp_7[0];
    Controller_P7_B.KZHX_prd[0] = tmp_4[0] * UnitDelay3;
    Controller_P7_B.KZHX_prd[1] = tmp_4[1] * UnitDelay3;
    UnitDelay3 = tmp_7[1];
    Controller_P7_B.KZHX_prd[0] += tmp_4[2] * UnitDelay3;
    Controller_P7_B.KZHX_prd[1] += tmp_4[3] * UnitDelay3;

    /* Sum: '<S235>/X_prd+K*(Z-H*X_prd)' incorporates:
     *  Product: '<S235>/K*(Z-H*X_prd)'
     *  Selector: '<S234>/Selector1'
     */
    UnitDelay3 = Controller_P7_B.Selector1[0] + Controller_P7_B.KZHX_prd[0];
    Controller_P7_B.X_prdKZHX_prd[0] = UnitDelay3;

    /* Product: '<S235>/A*X' incorporates:
     *  Sum: '<S235>/X_prd+K*(Z-H*X_prd)'
     */
    tmp_7[0] = UnitDelay3;

    /* Sum: '<S235>/X_prd+K*(Z-H*X_prd)' incorporates:
     *  Product: '<S235>/K*(Z-H*X_prd)'
     *  Selector: '<S234>/Selector1'
     */
    UnitDelay3 = Controller_P7_B.Selector1[1] + Controller_P7_B.KZHX_prd[1];
    Controller_P7_B.X_prdKZHX_prd[1] = UnitDelay3;

    /* Product: '<S235>/A*X' incorporates:
     *  Sum: '<S235>/X_prd+K*(Z-H*X_prd)'
     */
    tmp_7[1] = UnitDelay3;
    UnitDelay3 = tmp_7[0];
    Controller_P7_B.AX[0] = tmp_5[0] * UnitDelay3;
    Controller_P7_B.AX[1] = tmp_5[1] * UnitDelay3;
    UnitDelay3 = tmp_7[1];
    Controller_P7_B.AX[0] += tmp_5[2] * UnitDelay3;
    Controller_P7_B.AX[1] += tmp_5[3] * UnitDelay3;

    /* Assignment: '<S236>/Assignment' incorporates:
     *  Sum: '<S235>/A*P*At+Q'
     */
    Controller_P7_B.Assignment[0] = Controller_P7_B.APAtQ[0];
    Controller_P7_B.Assignment[1] = Controller_P7_B.APAtQ[1];
    Controller_P7_B.Assignment[2] = Controller_P7_B.APAtQ[2];
    Controller_P7_B.Assignment[3] = Controller_P7_B.APAtQ[3];

    /* Assignment: '<S237>/Assignment' incorporates:
     *  Sum: '<S235>/X_prd+K*(Z-H*X_prd)'
     */
    Controller_P7_B.Assignment_j[0] = Controller_P7_B.X_prdKZHX_prd[0];

    /* Assignment: '<S238>/Assignment' incorporates:
     *  Product: '<S235>/A*X'
     */
    Controller_P7_B.Assignment_m[0] = Controller_P7_B.AX[0];

    /* Assignment: '<S237>/Assignment' incorporates:
     *  Sum: '<S235>/X_prd+K*(Z-H*X_prd)'
     */
    Controller_P7_B.Assignment_j[1] = Controller_P7_B.X_prdKZHX_prd[1];

    /* Assignment: '<S238>/Assignment' incorporates:
     *  Product: '<S235>/A*X'
     */
    Controller_P7_B.Assignment_m[1] = Controller_P7_B.AX[1];
    s222_iter++;
  }

  /* End of Outputs for SubSystem: '<S220>/Control' */

  /* If: '<S1>/If1' */
  if (Controller_P7_B.Assignment_dh[2] > 420.0F) {
    /* Outputs for IfAction SubSystem: '<S1>/GR HI' incorporates:
     *  ActionPort: '<S3>/Action Port'
     */
    /* Sum: '<S3>/Add' incorporates:
     *  Constant: '<S3>/Ratio Min'
     */
    Controller_P7_B.Add_j = Controller_P7_P.Phi_min -
      Controller_P7_B.Assignment_j[0];

    /* Gain: '<S35>/Derivative Gain' */
    Controller_P7_B.DerivativeGain_a = Controller_P7_P.Der_GR_High *
      Controller_P7_B.Add_j;

    /* DiscreteIntegrator: '<S37>/Filter' */
    Controller_P7_B.Filter_i = Controller_P7_DW.Filter_DSTATE_dz;

    /* Sum: '<S37>/SumD' */
    Controller_P7_B.SumD_a = Controller_P7_B.DerivativeGain_a -
      Controller_P7_B.Filter_i;

    /* Gain: '<S39>/Integral Gain' */
    Controller_P7_B.IntegralGain_d = Controller_P7_P.Int_GR_High *
      Controller_P7_B.Add_j;

    /* DiscreteIntegrator: '<S42>/Integrator' */
    Controller_P7_B.Integrator_a = Controller_P7_DW.Integrator_DSTATE_n;

    /* Gain: '<S45>/Filter Coefficient' */
    Controller_P7_B.FilterCoefficient_b = Controller_P7_P.PIDController_N *
      Controller_P7_B.SumD_a;

    /* Gain: '<S47>/Proportional Gain' */
    Controller_P7_B.ProportionalGain_h = Controller_P7_P.Prop_GR_High *
      Controller_P7_B.Add_j;

    /* Merge: '<S1>/Merge' incorporates:
     *  Sum: '<S51>/Sum'
     */
    Controller_P7_B.Merge = (Controller_P7_B.ProportionalGain_h +
      Controller_P7_B.Integrator_a) + Controller_P7_B.FilterCoefficient_b;

    /* Update for DiscreteIntegrator: '<S37>/Filter' */
    Controller_P7_DW.Filter_DSTATE_dz += Controller_P7_P.Filter_gainval *
      Controller_P7_B.FilterCoefficient_b;

    /* Update for DiscreteIntegrator: '<S42>/Integrator' */
    Controller_P7_DW.Integrator_DSTATE_n += Controller_P7_P.Integrator_gainval *
      Controller_P7_B.IntegralGain_d;

    /* End of Outputs for SubSystem: '<S1>/GR HI' */
  } else if (Controller_P7_B.Assignment_dh[2] > 101.12F) {
    /* Outputs for IfAction SubSystem: '<S1>/Omega HI' incorporates:
     *  ActionPort: '<S5>/Action Port'
     */
    /* Sum: '<S5>/Add' incorporates:
     *  Constant: '<S5>/RPM_Hi'
     */
    Controller_P7_B.Add_h = Controller_P7_B.Assignment_dh[0] -
      Controller_P7_P.Omega_High;

    /* UnaryMinus: '<S142>/Unary Minus' */
    Controller_P7_B.UnaryMinus_j = -Controller_P7_B.Assignment_dh[1];

    /* Gain: '<S141>/Derivative Gain' */
    Controller_P7_B.DerivativeGain_n = Controller_P7_P.Der_RPM_High *
      Controller_P7_B.UnaryMinus_j;

    /* DiscreteIntegrator: '<S143>/Filter' */
    Controller_P7_B.Filter_j = Controller_P7_DW.Filter_DSTATE_i;

    /* Gain: '<S151>/Filter Coefficient' */
    Controller_P7_B.FilterCoefficient_a = Controller_P7_P.PIDController_N_k *
      Controller_P7_B.Filter_j;

    /* Sum: '<S143>/SumD' */
    Controller_P7_B.SumD_o = Controller_P7_B.DerivativeGain_n -
      Controller_P7_B.FilterCoefficient_a;

    /* Gain: '<S145>/Integral Gain' */
    Controller_P7_B.IntegralGain_a = Controller_P7_P.Int_RPM_High *
      Controller_P7_B.Add_h;

    /* DiscreteIntegrator: '<S148>/Integrator' */
    Controller_P7_B.Integrator_j = Controller_P7_DW.Integrator_DSTATE_j;

    /* Gain: '<S153>/Proportional Gain' */
    Controller_P7_B.ProportionalGain_l = Controller_P7_P.Prop_RPM_High *
      Controller_P7_B.Add_h;

    /* Merge: '<S1>/Merge' incorporates:
     *  Sum: '<S157>/Sum'
     */
    Controller_P7_B.Merge = (Controller_P7_B.ProportionalGain_l +
      Controller_P7_B.Integrator_j) + Controller_P7_B.FilterCoefficient_a;

    /* Update for DiscreteIntegrator: '<S143>/Filter' */
    Controller_P7_DW.Filter_DSTATE_i += Controller_P7_P.Filter_gainval_i *
      Controller_P7_B.SumD_o;

    /* Update for DiscreteIntegrator: '<S148>/Integrator' */
    Controller_P7_DW.Integrator_DSTATE_j += Controller_P7_P.Integrator_gainval_i
      * Controller_P7_B.IntegralGain_a;

    /* End of Outputs for SubSystem: '<S1>/Omega HI' */
  } else if (Controller_P7_B.Assignment_dh[2] > 60.67F) {
    /* Outputs for IfAction SubSystem: '<S1>/GR LO' incorporates:
     *  ActionPort: '<S4>/Action Port'
     */
    /* Sum: '<S4>/Add' incorporates:
     *  Constant: '<S4>/Ratio Max'
     */
    Controller_P7_B.Add_m = Controller_P7_P.Phi_max -
      Controller_P7_B.Assignment_j[0];

    /* Gain: '<S88>/Derivative Gain' */
    Controller_P7_B.DerivativeGain = Controller_P7_P.Der_GR_Low *
      Controller_P7_B.Add_m;

    /* DiscreteIntegrator: '<S90>/Filter' */
    Controller_P7_B.Filter_l = Controller_P7_DW.Filter_DSTATE_d;

    /* Sum: '<S90>/SumD' */
    Controller_P7_B.SumD_d = Controller_P7_B.DerivativeGain -
      Controller_P7_B.Filter_l;

    /* Gain: '<S92>/Integral Gain' */
    Controller_P7_B.IntegralGain_b = Controller_P7_P.Int_GR_Low *
      Controller_P7_B.Add_m;

    /* DiscreteIntegrator: '<S95>/Integrator' */
    Controller_P7_B.Integrator_o = Controller_P7_DW.Integrator_DSTATE_l;

    /* Gain: '<S98>/Filter Coefficient' */
    Controller_P7_B.FilterCoefficient_i = Controller_P7_P.PIDController_N_j *
      Controller_P7_B.SumD_d;

    /* Gain: '<S100>/Proportional Gain' */
    Controller_P7_B.ProportionalGain_k = Controller_P7_P.Prop_GR_Low *
      Controller_P7_B.Add_m;

    /* Merge: '<S1>/Merge' incorporates:
     *  Sum: '<S104>/Sum'
     */
    Controller_P7_B.Merge = (Controller_P7_B.ProportionalGain_k +
      Controller_P7_B.Integrator_o) + Controller_P7_B.FilterCoefficient_i;

    /* Update for DiscreteIntegrator: '<S90>/Filter' */
    Controller_P7_DW.Filter_DSTATE_d += Controller_P7_P.Filter_gainval_h *
      Controller_P7_B.FilterCoefficient_i;

    /* Update for DiscreteIntegrator: '<S95>/Integrator' */
    Controller_P7_DW.Integrator_DSTATE_l += Controller_P7_P.Integrator_gainval_d
      * Controller_P7_B.IntegralGain_b;

    /* End of Outputs for SubSystem: '<S1>/GR LO' */
  } else {
    /* Outputs for IfAction SubSystem: '<S1>/Omega LO' incorporates:
     *  ActionPort: '<S6>/Action Port'
     */
    /* Sum: '<S6>/Add' incorporates:
     *  Constant: '<S6>/Constant'
     */
    Controller_P7_B.Add = Controller_P7_B.Assignment_dh[0] -
      Controller_P7_P.Omega_Low;

    /* UnaryMinus: '<S195>/Unary Minus' */
    Controller_P7_B.UnaryMinus = -Controller_P7_B.Assignment_dh[1];

    /* Gain: '<S194>/Derivative Gain' */
    Controller_P7_B.DerivativeGain_af = Controller_P7_P.Der_RPM_Low *
      Controller_P7_B.UnaryMinus;

    /* DiscreteIntegrator: '<S196>/Filter' */
    Controller_P7_B.Filter = Controller_P7_DW.Filter_DSTATE;

    /* Gain: '<S204>/Filter Coefficient' */
    Controller_P7_B.FilterCoefficient = Controller_P7_P.PIDController_N_f *
      Controller_P7_B.Filter;

    /* Sum: '<S196>/SumD' */
    Controller_P7_B.SumD = Controller_P7_B.DerivativeGain_af -
      Controller_P7_B.FilterCoefficient;

    /* Gain: '<S198>/Integral Gain' */
    Controller_P7_B.IntegralGain = Controller_P7_P.Int_RPM_Low *
      Controller_P7_B.Add;

    /* DiscreteIntegrator: '<S201>/Integrator' */
    Controller_P7_B.Integrator = Controller_P7_DW.Integrator_DSTATE;

    /* Gain: '<S206>/Proportional Gain' */
    Controller_P7_B.ProportionalGain = Controller_P7_P.Prop_RPM_Low *
      Controller_P7_B.Add;

    /* Merge: '<S1>/Merge' incorporates:
     *  Sum: '<S210>/Sum'
     */
    Controller_P7_B.Merge = (Controller_P7_B.ProportionalGain +
      Controller_P7_B.Integrator) + Controller_P7_B.FilterCoefficient;

    /* Update for DiscreteIntegrator: '<S196>/Filter' */
    Controller_P7_DW.Filter_DSTATE += Controller_P7_P.Filter_gainval_n *
      Controller_P7_B.SumD;

    /* Update for DiscreteIntegrator: '<S201>/Integrator' */
    Controller_P7_DW.Integrator_DSTATE += Controller_P7_P.Integrator_gainval_a *
      Controller_P7_B.IntegralGain;

    /* End of Outputs for SubSystem: '<S1>/Omega LO' */
  }

  /* End of If: '<S1>/If1' */

  /* Saturate: '<S1>/Saturation1' */
  u0 = Controller_P7_B.Merge;
  u1 = Controller_P7_P.V_lower;
  u2 = Controller_P7_P.V_upper;
  if (u0 > u2) {
    /* Outport: '<Root>/Command' */
    Controller_P7_Y.Command = u2;
  } else if (u0 < u1) {
    /* Outport: '<Root>/Command' */
    Controller_P7_Y.Command = u1;
  } else {
    /* Outport: '<Root>/Command' */
    Controller_P7_Y.Command = u0;
  }

  /* End of Saturate: '<S1>/Saturation1' */
  /* Update for UnitDelay: '<S219>/Unit Delay2' incorporates:
   *  Assignment: '<S227>/Assignment'
   */
  Controller_P7_DW.UnitDelay2_DSTATE[0] = Controller_P7_B.Assignment_g[0];
  Controller_P7_DW.UnitDelay2_DSTATE[1] = Controller_P7_B.Assignment_g[1];
  Controller_P7_DW.UnitDelay2_DSTATE[2] = Controller_P7_B.Assignment_g[2];
  Controller_P7_DW.UnitDelay2_DSTATE[3] = Controller_P7_B.Assignment_g[3];

  /* Update for UnitDelay: '<S219>/Unit Delay3' incorporates:
   *  Assignment: '<S225>/Assignment'
   */
  memcpy(&Controller_P7_DW.UnitDelay3_DSTATE[0], &Controller_P7_B.Assignment_d[0],
         sizeof(real32_T) << 4U);

  /* Update for UnitDelay: '<S220>/Unit Delay2' incorporates:
   *  Assignment: '<S238>/Assignment'
   */
  Controller_P7_DW.UnitDelay2_DSTATE_b[0] = Controller_P7_B.Assignment_m[0];
  Controller_P7_DW.UnitDelay2_DSTATE_b[1] = Controller_P7_B.Assignment_m[1];

  /* Update for UnitDelay: '<S220>/Unit Delay3' incorporates:
   *  Assignment: '<S236>/Assignment'
   */
  Controller_P7_DW.UnitDelay3_DSTATE_f[0] = Controller_P7_B.Assignment[0];
  Controller_P7_DW.UnitDelay3_DSTATE_f[1] = Controller_P7_B.Assignment[1];
  Controller_P7_DW.UnitDelay3_DSTATE_f[2] = Controller_P7_B.Assignment[2];
  Controller_P7_DW.UnitDelay3_DSTATE_f[3] = Controller_P7_B.Assignment[3];

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
// Controller_P7_P.Prop_GR_High = 25.0;
/* Model initialize function */
void Controller_P7_initialize(void)
{
  /* Registration code */

  /* initialize real-time model */
  (void) memset((void *)Controller_P7_M, 0,
                sizeof(RT_MODEL_Controller_P7_T));
  rtmSetTFinal(Controller_P7_M, 5.0);
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
  Controller_P7_Y.Command = 0.0;

  /* Matfile logging */
  rt_StartDataLoggingWithStartTime(Controller_P7_M->rtwLogInfo, 0.0,
    rtmGetTFinal(Controller_P7_M), Controller_P7_M->Timing.stepSize0,
    (&rtmGetErrorStatus(Controller_P7_M)));

  {
    int32_T i;

    /* InitializeConditions for UnitDelay: '<S219>/Unit Delay2' */
    Controller_P7_DW.UnitDelay2_DSTATE[0] =
      Controller_P7_P.UnitDelay2_InitialCondition[0];
    Controller_P7_DW.UnitDelay2_DSTATE[1] =
      Controller_P7_P.UnitDelay2_InitialCondition[1];
    Controller_P7_DW.UnitDelay2_DSTATE[2] =
      Controller_P7_P.UnitDelay2_InitialCondition[2];
    Controller_P7_DW.UnitDelay2_DSTATE[3] =
      Controller_P7_P.UnitDelay2_InitialCondition[3];

    /* InitializeConditions for UnitDelay: '<S220>/Unit Delay2' */
    Controller_P7_DW.UnitDelay2_DSTATE_b[0] =
      Controller_P7_P.UnitDelay2_InitialCondition_j[0];
    Controller_P7_DW.UnitDelay2_DSTATE_b[1] =
      Controller_P7_P.UnitDelay2_InitialCondition_j[1];

    /* InitializeConditions for UnitDelay: '<S220>/Unit Delay3' */
    Controller_P7_DW.UnitDelay3_DSTATE_f[0] =
      Controller_P7_P.UnitDelay3_InitialCondition_m[0];

    /* SystemInitialize for Iterator SubSystem: '<S219>/Control' */
    /* SystemInitialize for Assignment: '<S226>/Assignment' incorporates:
     *  Outport: '<S222>/X_est'
     */
    Controller_P7_B.Assignment_dh[0] = Controller_P7_P.X_est_Y0;

    /* SystemInitialize for Assignment: '<S227>/Assignment' incorporates:
     *  Outport: '<S222>/X_prd'
     */
    Controller_P7_B.Assignment_g[0] = Controller_P7_P.X_prd_Y0;

    /* End of SystemInitialize for SubSystem: '<S219>/Control' */

    /* InitializeConditions for UnitDelay: '<S220>/Unit Delay3' */
    Controller_P7_DW.UnitDelay3_DSTATE_f[1] =
      Controller_P7_P.UnitDelay3_InitialCondition_m[1];

    /* SystemInitialize for Iterator SubSystem: '<S219>/Control' */
    /* SystemInitialize for Assignment: '<S226>/Assignment' incorporates:
     *  Outport: '<S222>/X_est'
     */
    Controller_P7_B.Assignment_dh[1] = Controller_P7_P.X_est_Y0;

    /* SystemInitialize for Assignment: '<S227>/Assignment' incorporates:
     *  Outport: '<S222>/X_prd'
     */
    Controller_P7_B.Assignment_g[1] = Controller_P7_P.X_prd_Y0;

    /* End of SystemInitialize for SubSystem: '<S219>/Control' */

    /* InitializeConditions for UnitDelay: '<S220>/Unit Delay3' */
    Controller_P7_DW.UnitDelay3_DSTATE_f[2] =
      Controller_P7_P.UnitDelay3_InitialCondition_m[2];

    /* SystemInitialize for Iterator SubSystem: '<S219>/Control' */
    /* SystemInitialize for Assignment: '<S226>/Assignment' incorporates:
     *  Outport: '<S222>/X_est'
     */
    Controller_P7_B.Assignment_dh[2] = Controller_P7_P.X_est_Y0;

    /* SystemInitialize for Assignment: '<S227>/Assignment' incorporates:
     *  Outport: '<S222>/X_prd'
     */
    Controller_P7_B.Assignment_g[2] = Controller_P7_P.X_prd_Y0;

    /* End of SystemInitialize for SubSystem: '<S219>/Control' */

    /* InitializeConditions for UnitDelay: '<S220>/Unit Delay3' */
    Controller_P7_DW.UnitDelay3_DSTATE_f[3] =
      Controller_P7_P.UnitDelay3_InitialCondition_m[3];

    /* SystemInitialize for Iterator SubSystem: '<S219>/Control' */
    /* SystemInitialize for Assignment: '<S226>/Assignment' incorporates:
     *  Outport: '<S222>/X_est'
     */
    Controller_P7_B.Assignment_dh[3] = Controller_P7_P.X_est_Y0;

    /* SystemInitialize for Assignment: '<S227>/Assignment' incorporates:
     *  Outport: '<S222>/X_prd'
     */
    Controller_P7_B.Assignment_g[3] = Controller_P7_P.X_prd_Y0;
    for (i = 0; i < 16; i++) {
      /* InitializeConditions for UnitDelay: '<S219>/Unit Delay3' */
      Controller_P7_DW.UnitDelay3_DSTATE[i] =
        Controller_P7_P.UnitDelay3_InitialCondition[i];

      /* SystemInitialize for Assignment: '<S225>/Assignment' incorporates:
       *  Outport: '<S222>/P_prd'
       */
      Controller_P7_B.Assignment_d[i] = Controller_P7_P.P_prd_Y0;
    }

    /* End of SystemInitialize for SubSystem: '<S219>/Control' */

    /* SystemInitialize for Iterator SubSystem: '<S220>/Control' */
    /* SystemInitialize for Assignment: '<S237>/Assignment' incorporates:
     *  Outport: '<S233>/X_est'
     */
    Controller_P7_B.Assignment_j[0] = Controller_P7_P.X_est_Y0_f;

    /* SystemInitialize for Assignment: '<S238>/Assignment' incorporates:
     *  Outport: '<S233>/X_prd'
     */
    Controller_P7_B.Assignment_m[0] = Controller_P7_P.X_prd_Y0_l;

    /* SystemInitialize for Assignment: '<S237>/Assignment' incorporates:
     *  Outport: '<S233>/X_est'
     */
    Controller_P7_B.Assignment_j[1] = Controller_P7_P.X_est_Y0_f;

    /* SystemInitialize for Assignment: '<S238>/Assignment' incorporates:
     *  Outport: '<S233>/X_prd'
     */
    Controller_P7_B.Assignment_m[1] = Controller_P7_P.X_prd_Y0_l;

    /* SystemInitialize for Assignment: '<S236>/Assignment' incorporates:
     *  Outport: '<S233>/P_prd'
     */
    Controller_P7_B.Assignment[0] = Controller_P7_P.P_prd_Y0_e;
    Controller_P7_B.Assignment[1] = Controller_P7_P.P_prd_Y0_e;
    Controller_P7_B.Assignment[2] = Controller_P7_P.P_prd_Y0_e;
    Controller_P7_B.Assignment[3] = Controller_P7_P.P_prd_Y0_e;

    /* End of SystemInitialize for SubSystem: '<S220>/Control' */

    /* SystemInitialize for IfAction SubSystem: '<S1>/GR HI' */
    /* InitializeConditions for DiscreteIntegrator: '<S37>/Filter' */
    Controller_P7_DW.Filter_DSTATE_dz =
      Controller_P7_P.PIDController_InitialConditionF;

    /* InitializeConditions for DiscreteIntegrator: '<S42>/Integrator' */
    Controller_P7_DW.Integrator_DSTATE_n =
      Controller_P7_P.PIDController_InitialConditio_e;

    /* End of SystemInitialize for SubSystem: '<S1>/GR HI' */

    /* SystemInitialize for IfAction SubSystem: '<S1>/Omega HI' */
    /* InitializeConditions for DiscreteIntegrator: '<S143>/Filter' */
    Controller_P7_DW.Filter_DSTATE_i =
      Controller_P7_P.PIDController_InitialConditio_k;

    /* InitializeConditions for DiscreteIntegrator: '<S148>/Integrator' */
    Controller_P7_DW.Integrator_DSTATE_j =
      Controller_P7_P.PIDController_InitialConditio_i;

    /* End of SystemInitialize for SubSystem: '<S1>/Omega HI' */

    /* SystemInitialize for IfAction SubSystem: '<S1>/GR LO' */
    /* InitializeConditions for DiscreteIntegrator: '<S90>/Filter' */
    Controller_P7_DW.Filter_DSTATE_d =
      Controller_P7_P.PIDController_InitialConditio_n;

    /* InitializeConditions for DiscreteIntegrator: '<S95>/Integrator' */
    Controller_P7_DW.Integrator_DSTATE_l =
      Controller_P7_P.PIDController_InitialConditio_g;

    /* End of SystemInitialize for SubSystem: '<S1>/GR LO' */

    /* SystemInitialize for IfAction SubSystem: '<S1>/Omega LO' */
    /* InitializeConditions for DiscreteIntegrator: '<S196>/Filter' */
    Controller_P7_DW.Filter_DSTATE =
      Controller_P7_P.PIDController_InitialConditio_h;

    /* InitializeConditions for DiscreteIntegrator: '<S201>/Integrator' */
    Controller_P7_DW.Integrator_DSTATE =
      Controller_P7_P.PIDController_InitialConditio_m;

    /* End of SystemInitialize for SubSystem: '<S1>/Omega LO' */
  }
}

/* Model terminate function */
void Controller_P7_terminate(void)
{
  /* (no terminate code required) */
}
