/*
 * Controller_P7_data.c
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

/* Block parameters (default storage) */
P_Controller_P7_T Controller_P7_P = {
  /* Variable: Der_GR_High
   * Referenced by: '<S35>/Derivative Gain'
   */
  0.0,

  /* Variable: Der_GR_Low
   * Referenced by: '<S88>/Derivative Gain'
   */
  0.0,

  /* Variable: Int_GR_High
   * Referenced by: '<S39>/Integral Gain'
   */
  0.0,

  /* Variable: Int_GR_Low
   * Referenced by: '<S92>/Integral Gain'
   */
  0.0,

  /* Variable: Int_RPM_High
   * Referenced by: '<S145>/Integral Gain'
   */
  0.0,

  /* Variable: Int_RPM_Low
   * Referenced by: '<S198>/Integral Gain'
   */
  0.0,

  /* Variable: Omega_High
   * Referenced by: '<S5>/RPM_Hi'
   */
  314.15926535897933,

  /* Variable: Omega_Low
   * Referenced by: '<S6>/Constant'
   */
  188.49555921538757,

  /* Variable: Phi_max
   * Referenced by: '<S4>/Ratio Max'
   */
  3.15,

  /* Variable: Phi_min
   * Referenced by: '<S3>/Ratio Min'
   */
  0.8,

  /* Variable: Prop_GR_High
   * Referenced by: '<S47>/Proportional Gain'
   */
  20.0,

  /* Variable: Prop_GR_Low
   * Referenced by: '<S100>/Proportional Gain'
   */
  0.5,

  /* Variable: Prop_RPM_High
   * Referenced by: '<S153>/Proportional Gain'
   */
  0.55,

  /* Variable: Prop_RPM_Low
   * Referenced by: '<S206>/Proportional Gain'
   */
  0.25,

  /* Variable: V_lower
   * Referenced by: '<S1>/Saturation1'
   */
  -12.0,

  /* Variable: V_upper
   * Referenced by: '<S1>/Saturation1'
   */
  12.0,

  /* Variable: Der_RPM_High
   * Referenced by: '<S141>/Derivative Gain'
   */
  -0.005F,

  /* Variable: Der_RPM_Low
   * Referenced by: '<S194>/Derivative Gain'
   */
  0.001F,

  /* Mask Parameter: PIDController_InitialConditionF
   * Referenced by: '<S37>/Filter'
   */
  0.0,

  /* Mask Parameter: PIDController_InitialConditio_k
   * Referenced by: '<S143>/Filter'
   */
  0.0,

  /* Mask Parameter: PIDController_InitialConditio_n
   * Referenced by: '<S90>/Filter'
   */
  0.0,

  /* Mask Parameter: PIDController_InitialConditio_h
   * Referenced by: '<S196>/Filter'
   */
  0.0,

  /* Mask Parameter: PIDController_InitialConditio_e
   * Referenced by: '<S42>/Integrator'
   */
  0.0,

  /* Mask Parameter: PIDController_InitialConditio_i
   * Referenced by: '<S148>/Integrator'
   */
  0.0,

  /* Mask Parameter: PIDController_InitialConditio_g
   * Referenced by: '<S95>/Integrator'
   */
  0.0,

  /* Mask Parameter: PIDController_InitialConditio_m
   * Referenced by: '<S201>/Integrator'
   */
  0.0,

  /* Mask Parameter: PIDController_N
   * Referenced by: '<S45>/Filter Coefficient'
   */
  100.0,

  /* Mask Parameter: PIDController_N_k
   * Referenced by: '<S151>/Filter Coefficient'
   */
  100.0,

  /* Mask Parameter: PIDController_N_j
   * Referenced by: '<S98>/Filter Coefficient'
   */
  100.0,

  /* Mask Parameter: PIDController_N_f
   * Referenced by: '<S204>/Filter Coefficient'
   */
  100.0,

  /* Computed Parameter: Filter_gainval
   * Referenced by: '<S37>/Filter'
   */
  0.001,

  /* Computed Parameter: Integrator_gainval
   * Referenced by: '<S42>/Integrator'
   */
  0.001,

  /* Computed Parameter: Filter_gainval_i
   * Referenced by: '<S143>/Filter'
   */
  0.001,

  /* Computed Parameter: Integrator_gainval_i
   * Referenced by: '<S148>/Integrator'
   */
  0.001,

  /* Computed Parameter: Filter_gainval_h
   * Referenced by: '<S90>/Filter'
   */
  0.001,

  /* Computed Parameter: Integrator_gainval_d
   * Referenced by: '<S95>/Integrator'
   */
  0.001,

  /* Computed Parameter: Filter_gainval_n
   * Referenced by: '<S196>/Filter'
   */
  0.001,

  /* Computed Parameter: Integrator_gainval_a
   * Referenced by: '<S201>/Integrator'
   */
  0.001,

  /* Computed Parameter: Iterator_IterationLimit
   * Referenced by: '<S222>/Iterator'
   */
  1,

  /* Computed Parameter: Iterator_IterationLimit_n
   * Referenced by: '<S233>/Iterator'
   */
  1,

  /* Computed Parameter: X_est_Y0
   * Referenced by: '<S222>/X_est'
   */
  0.0F,

  /* Computed Parameter: X_prd_Y0
   * Referenced by: '<S222>/X_prd'
   */
  0.0F,

  /* Computed Parameter: P_prd_Y0
   * Referenced by: '<S222>/P_prd'
   */
  0.0F,

  /* Computed Parameter: Constant3_Value
   * Referenced by: '<S224>/Constant3'
   */
  { 1.0F, 0.0F, 0.0F, 0.0F, 0.0001F, 1.0F, 0.0F, 0.0F, 0.0F, 0.0F, 1.0F, 0.0F,
    0.0F, 0.0F, 0.0001F, 1.0F },

  /* Computed Parameter: Hcst_Value
   * Referenced by: '<S224>/Hcst'
   */
  { 1.0F, 0.0F, 0.0F, 0.0F, 0.0F, 1.0F, 0.0F, 0.0F },

  /* Computed Parameter: Hcst_t_Value
   * Referenced by: '<S224>/Hcst_t'
   */
  { 1.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 1.0F, 0.0F },

  /* Computed Parameter: Constant2_Value
   * Referenced by: '<S224>/Constant2'
   */
  { 16.0F, 0.0F, 0.0F, 16.0F },

  /* Computed Parameter: Constant4_Value
   * Referenced by: '<S224>/Constant4'
   */
  { 1.0F, 0.0001F, 0.0F, 0.0F, 0.0F, 1.0F, 0.0F, 0.0F, 0.0F, 0.0F, 1.0F, 0.0001F,
    0.0F, 0.0F, 0.0F, 1.0F },

  /* Computed Parameter: Constant5_Value
   * Referenced by: '<S224>/Constant5'
   */
  { 0.1F, 0.0F, 0.0F, 0.0F, 0.0F, 1.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.1F, 0.0F, 0.0F,
    0.0F, 0.0F, 1.0F },

  /* Computed Parameter: X_est_Y0_f
   * Referenced by: '<S233>/X_est'
   */
  0.0F,

  /* Computed Parameter: X_prd_Y0_l
   * Referenced by: '<S233>/X_prd'
   */
  0.0F,

  /* Computed Parameter: P_prd_Y0_e
   * Referenced by: '<S233>/P_prd'
   */
  0.0F,

  /* Computed Parameter: Constant3_Value_m
   * Referenced by: '<S235>/Constant3'
   */
  { 1.0F, 0.0F, 0.0001F, 1.0F },

  /* Computed Parameter: Hcst_Value_e
   * Referenced by: '<S235>/Hcst'
   */
  { 1.0F, 1.0F, 0.0F, 0.0F },

  /* Computed Parameter: Hcst_t_Value_c
   * Referenced by: '<S235>/Hcst_t'
   */
  { 1.0F, 0.0F, 1.0F, 0.0F },

  /* Computed Parameter: Constant2_Value_l
   * Referenced by: '<S235>/Constant2'
   */
  { 16.0F, 0.0F, 0.0F, 16.0F },

  /* Computed Parameter: Constant4_Value_l
   * Referenced by: '<S235>/Constant4'
   */
  { 1.0F, 0.0001F, 0.0F, 1.0F },

  /* Computed Parameter: Constant5_Value_k
   * Referenced by: '<S235>/Constant5'
   */
  { 0.1F, 0.0F, 0.0F, 1.0F },

  /* Computed Parameter: UnitDelay2_InitialCondition
   * Referenced by: '<S219>/Unit Delay2'
   */
  { 0.0F, 0.0F, 0.0F, 0.0F },

  /* Computed Parameter: UnitDelay3_InitialCondition
   * Referenced by: '<S219>/Unit Delay3'
   */
  { 10.1F, 0.001F, 0.0F, 0.0F, 0.001F, 11.0F, 0.0F, 0.0F, 0.0F, 0.0F, 10.1F,
    0.001F, 0.0F, 0.0F, 0.001F, 11.0F },

  /* Computed Parameter: uDLookupTable1_tableData
   * Referenced by: '<S2>/1-D Lookup Table1'
   */
  { 0.0F, 0.06837F, 0.124636114F, 0.145096526F, 0.170672029F, 0.196247533F,
    0.221823037F, 0.24739854F, 0.272974044F, 0.298549563F, 0.324125051F,
    0.34970057F, 0.375276089F, 0.400851578F, 0.426427096F, 0.452002585F,
    0.477578104F, 0.503153622F, 0.528729141F, 0.5543046F, 0.579880118F,
    0.605455637F, 0.631031156F, 0.656606674F, 0.682182133F, 0.707757652F,
    0.73333317F, 0.758908689F, 0.784484148F, 0.810059667F, 0.835635185F,
    0.861210704F },

  /* Computed Parameter: uDLookupTable1_bp01Data
   * Referenced by: '<S2>/1-D Lookup Table1'
   */
  { 0.0F, 0.131665155F, 0.263526F, 0.315966606F, 0.383546561F, 0.448433489F,
    0.510875225F, 0.570885539F, 0.628730655F, 0.684593618F, 0.738594294F,
    0.790841758F, 0.841472745F, 0.8905074F, 0.938130379F, 0.984350622F,
    1.02929866F, 1.07303298F, 1.11561072F, 1.15708208F, 1.19754589F, 1.23701942F,
    1.27549696F, 1.31308532F, 1.34981823F, 1.38572729F, 1.42084205F, 1.45524693F,
    1.48892868F, 1.52189326F, 1.55025899F, 1.57601988F },

  /* Computed Parameter: uDLookupTable_tableData
   * Referenced by: '<S2>/1-D Lookup Table'
   */
  { 3.10682154F, 3.06502962F, 3.02412033F, 2.98406506F, 2.94483662F, 2.90640855F,
    2.86875606F, 2.83185482F, 2.79568172F, 2.76021504F, 2.72543287F, 2.69131541F,
    2.6578424F, 2.62499547F, 2.59275627F, 2.56110764F, 2.53003216F, 2.49951434F,
    2.46953797F, 2.44008875F, 2.41115165F, 2.38271284F, 2.35475922F, 2.32727766F,
    2.3002553F, 2.27368069F, 2.24754167F, 2.22182703F, 2.19652629F, 2.17162848F,
    2.14712381F, 2.12300205F, 2.09925389F, 2.07587028F, 2.05284214F, 2.0301609F,
    2.00781822F, 1.98580599F, 1.96411645F, 1.94274187F, 1.92167497F, 1.90090871F,
    1.88043606F, 1.86025035F, 1.84034503F, 1.82071376F, 1.80135047F, 1.78224921F,
    1.76340425F, 1.74480987F, 1.72646058F, 1.70835114F, 1.69047642F, 1.6728313F,
    1.65541112F, 1.63821089F, 1.62122619F, 1.60445249F, 1.58788526F, 1.57152057F,
    1.55535388F, 1.5393815F, 1.52359939F, 1.50800371F, 1.49259079F, 1.47735691F,
    1.46229863F, 1.44741249F, 1.43269503F, 1.41814315F, 1.4037534F, 1.38952291F,
    1.37544858F, 1.36152732F, 1.34775639F, 1.33413291F, 1.32065415F, 1.30731726F,
    1.29411972F, 1.28105903F, 1.26813269F, 1.25533807F, 1.24267292F, 1.23013484F,
    1.21772158F, 1.20543087F, 1.19326043F, 1.18120837F, 1.16927242F, 1.15745056F,
    1.14574075F, 1.13414121F, 1.12264979F, 1.11126471F, 1.09998417F, 1.08880627F,
    1.07772946F, 1.06675184F, 1.05587173F, 1.04508746F, 1.03439748F, 1.02380025F,
    1.0132941F, 1.00287759F, 0.992549241F, 0.982307434F, 0.972150922F,
    0.962078154F, 0.952087879F, 0.942178607F, 0.932349145F, 0.922598124F,
    0.91292423F, 0.903326273F, 0.893803F, 0.884353161F, 0.874975681F,
    0.86566925F, 0.856432855F, 0.847265303F, 0.838165522F, 0.829132378F,
    0.820164859F, 0.811261892F, 0.802422464F, 0.79364562F, 0.784930229F,
    0.776275456F, 0.767680228F, 0.75914371F, 0.75066489F, 0.742242873F,
    0.733876765F, 0.725565732F, 0.717308819F, 0.709105253F, 0.700954139F,
    0.692854643F, 0.684806F, 0.676807344F, 0.668857932F },

  /* Computed Parameter: uDLookupTable_bp01Data
   * Referenced by: '<S2>/1-D Lookup Table'
   */
  { 0.00249608839F, 0.00699760951F, 0.0115145324F, 0.0160469115F, 0.020594798F,
    0.0251582507F, 0.0297373198F, 0.034332063F, 0.0389425345F, 0.0435687937F,
    0.0482108966F, 0.0528688952F, 0.0575428531F, 0.0622328259F, 0.0669388771F,
    0.0716610551F, 0.0763994232F, 0.0811540484F, 0.085924983F, 0.0907122865F,
    0.0955160335F, 0.100336269F, 0.105173066F, 0.110026494F, 0.114896595F,
    0.119783454F, 0.12468712F, 0.129607677F, 0.134545162F, 0.139499679F,
    0.144471258F, 0.149459988F, 0.154465929F, 0.159489155F, 0.164529726F,
    0.169587731F, 0.174663216F, 0.179756254F, 0.184866935F, 0.189995334F,
    0.195141494F, 0.200305507F, 0.205487445F, 0.210687384F, 0.215905413F,
    0.221141577F, 0.22639598F, 0.231668681F, 0.236959755F, 0.242269307F,
    0.247597396F, 0.252944112F, 0.258309513F, 0.26369372F, 0.269096762F,
    0.274518788F, 0.279959828F, 0.28542F, 0.290899366F, 0.296398F, 0.301916063F,
    0.307453543F, 0.313010603F, 0.318587273F, 0.324183702F, 0.32979995F,
    0.335436106F, 0.341092288F, 0.346768558F, 0.352465034F, 0.358181775F,
    0.36391893F, 0.36967656F, 0.375454783F, 0.38125369F, 0.387073368F,
    0.392913938F, 0.398775488F, 0.404658139F, 0.410561979F, 0.416487128F,
    0.422433674F, 0.428401709F, 0.434391409F, 0.440402806F, 0.446436048F,
    0.452491254F, 0.458568513F, 0.464667976F, 0.470789701F, 0.476933867F,
    0.483100533F, 0.48928988F, 0.495501965F, 0.501736939F, 0.50799495F,
    0.514276087F, 0.520580471F, 0.526908278F, 0.533259571F, 0.539634466F,
    0.546033204F, 0.552455783F, 0.558902442F, 0.565373302F, 0.57186842F,
    0.578388035F, 0.584932208F, 0.591501117F, 0.598094881F, 0.604713678F,
    0.611357629F, 0.618026912F, 0.624721587F, 0.631441951F, 0.638188F,
    0.644960046F, 0.651758075F, 0.658582389F, 0.665433049F, 0.672310293F,
    0.679214239F, 0.686145067F, 0.693102956F, 0.700088084F, 0.707100511F,
    0.714140594F, 0.721208334F, 0.728304F, 0.735427797F, 0.742579818F,
    0.74976033F, 0.756969512F, 0.764207482F, 0.771474481F, 0.778770745F,
    0.786096394F, 0.793451667F, 0.800836742F, 0.808251798F, 0.815697134F },

  /* Computed Parameter: UnitDelay2_InitialCondition_j
   * Referenced by: '<S220>/Unit Delay2'
   */
  { 0.0F, 0.0F },

  /* Computed Parameter: UnitDelay3_InitialCondition_m
   * Referenced by: '<S220>/Unit Delay3'
   */
  { 10.1F, 0.001F, 0.001F, 11.0F }
};
