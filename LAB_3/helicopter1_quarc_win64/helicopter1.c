/*
 * helicopter1.c
 *
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * Code generation for model "helicopter1".
 *
 * Model version              : 11.7
 * Simulink Coder version : 9.4 (R2020b) 29-Jul-2020
 * C source code generated on : Thu Mar  9 10:35:24 2023
 *
 * Target selection: quarc_win64.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: 32-bit Generic
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "helicopter1.h"
#include "helicopter1_private.h"
#include "helicopter1_dt.h"

/* Block signals (default storage) */
B_helicopter1_T helicopter1_B;

/* Continuous states */
X_helicopter1_T helicopter1_X;

/* Block states (default storage) */
DW_helicopter1_T helicopter1_DW;

/* Real-time model */
static RT_MODEL_helicopter1_T helicopter1_M_;
RT_MODEL_helicopter1_T *const helicopter1_M = &helicopter1_M_;

/*
 * Writes out MAT-file header.  Returns success or failure.
 * Returns:
 *      0 - success
 *      1 - failure
 */
int_T rt_WriteMat4FileHeader(FILE *fp, int32_T m, int32_T n, const char *name)
{
  typedef enum { ELITTLE_ENDIAN, EBIG_ENDIAN } ByteOrder;

  int16_T one = 1;
  ByteOrder byteOrder = (*((int8_T *)&one)==1) ? ELITTLE_ENDIAN : EBIG_ENDIAN;
  int32_T type = (byteOrder == ELITTLE_ENDIAN) ? 0: 1000;
  int32_T imagf = 0;
  int32_T name_len = (int32_T)strlen(name) + 1;
  if ((fwrite(&type, sizeof(int32_T), 1, fp) == 0) ||
      (fwrite(&m, sizeof(int32_T), 1, fp) == 0) ||
      (fwrite(&n, sizeof(int32_T), 1, fp) == 0) ||
      (fwrite(&imagf, sizeof(int32_T), 1, fp) == 0) ||
      (fwrite(&name_len, sizeof(int32_T), 1, fp) == 0) ||
      (fwrite(name, sizeof(char), name_len, fp) == 0)) {
    return(1);
  } else {
    return(0);
  }
}                                      /* end rt_WriteMat4FileHeader */

/*
 * This function updates continuous states using the ODE1 fixed-step
 * solver algorithm
 */
static void rt_ertODEUpdateContinuousStates(RTWSolverInfo *si )
{
  time_T tnew = rtsiGetSolverStopTime(si);
  time_T h = rtsiGetStepSize(si);
  real_T *x = rtsiGetContStates(si);
  ODE1_IntgData *id = (ODE1_IntgData *)rtsiGetSolverData(si);
  real_T *f0 = id->f[0];
  int_T i;
  int_T nXc = 4;
  rtsiSetSimTimeStep(si,MINOR_TIME_STEP);
  rtsiSetdX(si, f0);
  helicopter1_derivatives();
  rtsiSetT(si, tnew);
  for (i = 0; i < nXc; ++i) {
    x[i] += h * f0[i];
  }

  rtsiSetSimTimeStep(si,MAJOR_TIME_STEP);
}

/* Model output function */
void helicopter1_output(void)
{
  /* local block i/o variables */
  real_T rtb_Sum3_h[4];
  real_T rtb_Frontgain;
  real_T rtb_HILReadEncoderTimebase_o1;
  real_T rtb_HILReadEncoderTimebase_o2;
  real_T rtb_HILReadEncoderTimebase_o3;
  real_T rtb_Backgain;
  real_T rtb_Clock;
  real_T rtb_Derivative;
  real_T *lastU;
  int8_T rtAction;
  if (rtmIsMajorTimeStep(helicopter1_M)) {
    /* set solver stop time */
    if (!(helicopter1_M->Timing.clockTick0+1)) {
      rtsiSetSolverStopTime(&helicopter1_M->solverInfo,
                            ((helicopter1_M->Timing.clockTickH0 + 1) *
        helicopter1_M->Timing.stepSize0 * 4294967296.0));
    } else {
      rtsiSetSolverStopTime(&helicopter1_M->solverInfo,
                            ((helicopter1_M->Timing.clockTick0 + 1) *
        helicopter1_M->Timing.stepSize0 + helicopter1_M->Timing.clockTickH0 *
        helicopter1_M->Timing.stepSize0 * 4294967296.0));
    }
  }                                    /* end MajorTimeStep */

  /* Update absolute time of base rate at minor time step */
  if (rtmIsMinorTimeStep(helicopter1_M)) {
    helicopter1_M->Timing.t[0] = rtsiGetT(&helicopter1_M->solverInfo);
  }

  /* Reset subsysRan breadcrumbs */
  srClearBC(helicopter1_DW.IfActionSubsystem_SubsysRanBC);
  if (rtmIsMajorTimeStep(helicopter1_M)) {
    /* S-Function (hil_read_encoder_timebase_block): '<S5>/HIL Read Encoder Timebase' */

    /* S-Function Block: helicopter1/Helicopter_interface/HIL Read Encoder Timebase (hil_read_encoder_timebase_block) */
    {
      t_error result;
      result = hil_task_read_encoder(helicopter1_DW.HILReadEncoderTimebase_Task,
        1, &helicopter1_DW.HILReadEncoderTimebase_Buffer[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(helicopter1_M, _rt_error_message);
      } else {
        rtb_HILReadEncoderTimebase_o1 =
          helicopter1_DW.HILReadEncoderTimebase_Buffer[0];
        rtb_HILReadEncoderTimebase_o2 =
          helicopter1_DW.HILReadEncoderTimebase_Buffer[1];
        rtb_HILReadEncoderTimebase_o3 =
          helicopter1_DW.HILReadEncoderTimebase_Buffer[2];
      }
    }

    /* Gain: '<S5>/Travel: Count to rad' incorporates:
     *  Gain: '<S5>/Travel_gain'
     */
    helicopter1_B.TravelCounttorad = helicopter1_P.travel_gain *
      rtb_HILReadEncoderTimebase_o1 * helicopter1_P.TravelCounttorad_Gain;

    /* Gain: '<S13>/Gain' */
    helicopter1_B.Gain = helicopter1_P.Gain_Gain *
      helicopter1_B.TravelCounttorad;

    /* Sum: '<Root>/Sum5' incorporates:
     *  Constant: '<Root>/Travel offset [deg]'
     */
    helicopter1_B.Sum5 = helicopter1_B.Gain +
      helicopter1_P.Traveloffsetdeg_Value;

    /* Gain: '<S5>/Pitch: Count to rad' */
    helicopter1_B.PitchCounttorad = helicopter1_P.PitchCounttorad_Gain *
      rtb_HILReadEncoderTimebase_o2;

    /* Gain: '<S10>/Gain' */
    helicopter1_B.Gain_i = helicopter1_P.Gain_Gain_a *
      helicopter1_B.PitchCounttorad;
  }

  /* Gain: '<S14>/Gain' incorporates:
   *  TransferFcn: '<S5>/Travel: Transfer Fcn'
   */
  helicopter1_B.Gain_d = (helicopter1_P.TravelTransferFcn_C *
    helicopter1_X.TravelTransferFcn_CSTATE + helicopter1_P.TravelTransferFcn_D *
    helicopter1_B.TravelCounttorad) * helicopter1_P.Gain_Gain_l;

  /* Gain: '<S11>/Gain' incorporates:
   *  TransferFcn: '<S5>/Pitch: Transfer Fcn'
   */
  helicopter1_B.Gain_b = (helicopter1_P.PitchTransferFcn_C *
    helicopter1_X.PitchTransferFcn_CSTATE + helicopter1_P.PitchTransferFcn_D *
    helicopter1_B.PitchCounttorad) * helicopter1_P.Gain_Gain_ae;

  /* Gain: '<S3>/Gain1' */
  helicopter1_B.Gain1[0] = helicopter1_P.Gain1_Gain * helicopter1_B.Sum5;
  helicopter1_B.Gain1[1] = helicopter1_P.Gain1_Gain * helicopter1_B.Gain_d;
  helicopter1_B.Gain1[2] = helicopter1_P.Gain1_Gain * helicopter1_B.Gain_i;
  helicopter1_B.Gain1[3] = helicopter1_P.Gain1_Gain * helicopter1_B.Gain_b;

  /* FromWorkspace: '<Root>/From Workspace1' */
  {
    real_T *pDataValues = (real_T *) helicopter1_DW.FromWorkspace1_PWORK.DataPtr;
    real_T *pTimeValues = (real_T *) helicopter1_DW.FromWorkspace1_PWORK.TimePtr;
    int_T currTimeIndex = helicopter1_DW.FromWorkspace1_IWORK.PrevIndex;
    real_T t = helicopter1_M->Timing.t[0];

    /* Get index */
    if (t <= pTimeValues[0]) {
      currTimeIndex = 0;
    } else if (t >= pTimeValues[140]) {
      currTimeIndex = 139;
    } else {
      if (t < pTimeValues[currTimeIndex]) {
        while (t < pTimeValues[currTimeIndex]) {
          currTimeIndex--;
        }
      } else {
        while (t >= pTimeValues[currTimeIndex + 1]) {
          currTimeIndex++;
        }
      }
    }

    helicopter1_DW.FromWorkspace1_IWORK.PrevIndex = currTimeIndex;

    /* Post output */
    {
      real_T t1 = pTimeValues[currTimeIndex];
      real_T t2 = pTimeValues[currTimeIndex + 1];
      if (t1 == t2) {
        if (t < t1) {
          {
            int_T elIdx;
            for (elIdx = 0; elIdx < 4; ++elIdx) {
              (&rtb_Sum3_h[0])[elIdx] = pDataValues[currTimeIndex];
              pDataValues += 141;
            }
          }
        } else {
          {
            int_T elIdx;
            for (elIdx = 0; elIdx < 4; ++elIdx) {
              (&rtb_Sum3_h[0])[elIdx] = pDataValues[currTimeIndex + 1];
              pDataValues += 141;
            }
          }
        }
      } else {
        real_T f1 = (t2 - t) / (t2 - t1);
        real_T f2 = 1.0 - f1;
        real_T d1;
        real_T d2;
        int_T TimeIndex= currTimeIndex;

        {
          int_T elIdx;
          for (elIdx = 0; elIdx < 4; ++elIdx) {
            d1 = pDataValues[TimeIndex];
            d2 = pDataValues[TimeIndex + 1];
            (&rtb_Sum3_h[0])[elIdx] = (real_T) rtInterpolate(d1, d2, f1, f2);
            pDataValues += 141;
          }
        }
      }
    }
  }

  /* Sum: '<Root>/Sum3' */
  rtb_Sum3_h[0] = helicopter1_B.Gain1[0] - rtb_Sum3_h[0];
  rtb_Sum3_h[1] = helicopter1_B.Gain1[1] - rtb_Sum3_h[1];
  rtb_Sum3_h[2] = helicopter1_B.Gain1[2] - rtb_Sum3_h[2];
  rtb_Sum3_h[3] = helicopter1_B.Gain1[3] - rtb_Sum3_h[3];

  /* FromWorkspace: '<Root>/From Workspace' */
  {
    real_T *pDataValues = (real_T *) helicopter1_DW.FromWorkspace_PWORK.DataPtr;
    real_T *pTimeValues = (real_T *) helicopter1_DW.FromWorkspace_PWORK.TimePtr;
    int_T currTimeIndex = helicopter1_DW.FromWorkspace_IWORK.PrevIndex;
    real_T t = helicopter1_M->Timing.t[0];

    /* Get index */
    if (t <= pTimeValues[0]) {
      currTimeIndex = 0;
    } else if (t >= pTimeValues[140]) {
      currTimeIndex = 139;
    } else {
      if (t < pTimeValues[currTimeIndex]) {
        while (t < pTimeValues[currTimeIndex]) {
          currTimeIndex--;
        }
      } else {
        while (t >= pTimeValues[currTimeIndex + 1]) {
          currTimeIndex++;
        }
      }
    }

    helicopter1_DW.FromWorkspace_IWORK.PrevIndex = currTimeIndex;

    /* Post output */
    {
      real_T t1 = pTimeValues[currTimeIndex];
      real_T t2 = pTimeValues[currTimeIndex + 1];
      if (t1 == t2) {
        if (t < t1) {
          rtb_Frontgain = pDataValues[currTimeIndex];
        } else {
          rtb_Frontgain = pDataValues[currTimeIndex + 1];
        }
      } else {
        real_T f1 = (t2 - t) / (t2 - t1);
        real_T f2 = 1.0 - f1;
        real_T d1;
        real_T d2;
        int_T TimeIndex= currTimeIndex;
        d1 = pDataValues[TimeIndex];
        d2 = pDataValues[TimeIndex + 1];
        rtb_Frontgain = (real_T) rtInterpolate(d1, d2, f1, f2);
        pDataValues += 141;
      }
    }
  }

  /* Sum: '<Root>/Sum4' incorporates:
   *  Gain: '<Root>/Gain'
   */
  helicopter1_B.Sum4 = rtb_Frontgain - (((helicopter1_P.K[0] * rtb_Sum3_h[0] +
    helicopter1_P.K[1] * rtb_Sum3_h[1]) + helicopter1_P.K[2] * rtb_Sum3_h[2]) +
    helicopter1_P.K[3] * rtb_Sum3_h[3]);
  if (rtmIsMajorTimeStep(helicopter1_M)) {
    /* SignalConversion generated from: '<Root>/To File' */
    helicopter1_B.TmpSignalConversionAtToFileInpo[0] = helicopter1_B.Gain1[0];
    helicopter1_B.TmpSignalConversionAtToFileInpo[1] = helicopter1_B.Gain1[1];
    helicopter1_B.TmpSignalConversionAtToFileInpo[2] = helicopter1_B.Gain1[2];
    helicopter1_B.TmpSignalConversionAtToFileInpo[3] = helicopter1_B.Gain1[3];
    helicopter1_B.TmpSignalConversionAtToFileInpo[4] = helicopter1_B.Sum4;

    /* ToFile: '<Root>/To File' */
    {
      if (!(++helicopter1_DW.ToFile_IWORK.Decimation % 1) &&
          (helicopter1_DW.ToFile_IWORK.Count * (5 + 1)) + 1 < 100000000 ) {
        FILE *fp = (FILE *) helicopter1_DW.ToFile_PWORK.FilePtr;
        if (fp != (NULL)) {
          real_T u[5 + 1];
          helicopter1_DW.ToFile_IWORK.Decimation = 0;
          u[0] = helicopter1_M->Timing.t[1];
          u[1] = helicopter1_B.TmpSignalConversionAtToFileInpo[0];
          u[2] = helicopter1_B.TmpSignalConversionAtToFileInpo[1];
          u[3] = helicopter1_B.TmpSignalConversionAtToFileInpo[2];
          u[4] = helicopter1_B.TmpSignalConversionAtToFileInpo[3];
          u[5] = helicopter1_B.TmpSignalConversionAtToFileInpo[4];
          if (fwrite(u, sizeof(real_T), 5 + 1, fp) != 5 + 1) {
            rtmSetErrorStatus(helicopter1_M,
                              "Error writing to MAT-file Lab_3_case_files\\lab_3_case_1_5.mat");
            return;
          }

          if (((++helicopter1_DW.ToFile_IWORK.Count) * (5 + 1))+1 >= 100000000)
          {
            (void)fprintf(stdout,
                          "*** The ToFile block will stop logging data before\n"
                          "    the simulation has ended, because it has reached\n"
                          "    the maximum number of elements (100000000)\n"
                          "    allowed in MAT-file Lab_3_case_files\\lab_3_case_1_5.mat.\n");
          }
        }
      }
    }

    /* Gain: '<S5>/Elevation: Count to rad' incorporates:
     *  Gain: '<S5>/Elevation_gain'
     */
    helicopter1_B.ElevationCounttorad = helicopter1_P.elevation_gain *
      rtb_HILReadEncoderTimebase_o3 * helicopter1_P.ElevationCounttorad_Gain;

    /* Gain: '<S8>/Gain' */
    helicopter1_B.Gain_e = helicopter1_P.Gain_Gain_lv *
      helicopter1_B.ElevationCounttorad;

    /* Sum: '<Root>/Sum' incorporates:
     *  Constant: '<Root>/elavation offset [deg]'
     */
    helicopter1_B.Sum = helicopter1_B.Gain_e +
      helicopter1_P.elavationoffsetdeg_Value;
  }

  /* Gain: '<S1>/Front gain' incorporates:
   *  TransferFcn: '<S5>/Elevation: Transfer Fcn'
   */
  rtb_Frontgain = 0.0;
  rtb_Frontgain += helicopter1_P.ElevationTransferFcn_C *
    helicopter1_X.ElevationTransferFcn_CSTATE;
  rtb_Frontgain += helicopter1_P.ElevationTransferFcn_D *
    helicopter1_B.ElevationCounttorad;

  /* Gain: '<S9>/Gain' */
  helicopter1_B.Gain_dg = helicopter1_P.Gain_Gain_n * rtb_Frontgain;

  /* Gain: '<S1>/Front gain' incorporates:
   *  Gain: '<S2>/Gain1'
   *  Sum: '<S6>/Sum2'
   */
  rtb_Frontgain = helicopter1_B.Sum4 - helicopter1_P.Gain1_Gain_f *
    helicopter1_B.Gain_i;

  /* Gain: '<S6>/K_pp' */
  rtb_Clock = helicopter1_P.K_pp * rtb_Frontgain;

  /* Gain: '<S1>/Front gain' incorporates:
   *  Constant: '<Root>/Vd_bias'
   *  Gain: '<S2>/Gain1'
   *  Gain: '<S6>/K_pd'
   *  Sum: '<Root>/Sum1'
   *  Sum: '<S6>/Sum3'
   */
  rtb_Frontgain = helicopter1_P.Gain1_Gain_f * helicopter1_B.Gain_b *
    helicopter1_P.K_pd;
  rtb_Frontgain = (rtb_Clock - rtb_Frontgain) + helicopter1_P.Vd_ff;

  /* Integrator: '<S4>/Integrator' */
  /* Limited  Integrator  */
  if (helicopter1_X.Integrator_CSTATE >= helicopter1_P.Integrator_UpperSat) {
    helicopter1_X.Integrator_CSTATE = helicopter1_P.Integrator_UpperSat;
  } else {
    if (helicopter1_X.Integrator_CSTATE <= helicopter1_P.Integrator_LowerSat) {
      helicopter1_X.Integrator_CSTATE = helicopter1_P.Integrator_LowerSat;
    }
  }

  /* Sum: '<S4>/Sum' incorporates:
   *  Constant: '<Root>/elevation_ref'
   *  Gain: '<S2>/Gain1'
   */
  rtb_Derivative = helicopter1_P.elevation_ref_Value -
    helicopter1_P.Gain1_Gain_f * helicopter1_B.Sum;

  /* Sum: '<Root>/Sum2' incorporates:
   *  Constant: '<Root>/Vs_bias'
   *  Gain: '<S2>/Gain1'
   *  Gain: '<S4>/K_ed'
   *  Gain: '<S4>/K_ep'
   *  Integrator: '<S4>/Integrator'
   *  Sum: '<S4>/Sum1'
   */
  rtb_Backgain = ((helicopter1_P.K_ep * rtb_Derivative +
                   helicopter1_X.Integrator_CSTATE) - helicopter1_P.Gain1_Gain_f
                  * helicopter1_B.Gain_dg * helicopter1_P.K_ed) +
    helicopter1_P.Vs_ff;

  /* Sum: '<S1>/Subtract' */
  rtb_Clock = rtb_Backgain - rtb_Frontgain;

  /* Gain: '<S1>/Front gain' incorporates:
   *  Sum: '<S1>/Add'
   */
  rtb_Frontgain = (rtb_Frontgain + rtb_Backgain) * helicopter1_P.Frontgain_Gain;

  /* If: '<S4>/If' incorporates:
   *  Clock: '<S4>/Clock'
   *  Gain: '<S4>/K_ei'
   *  Inport: '<S7>/In1'
   */
  if (rtmIsMajorTimeStep(helicopter1_M)) {
    rtAction = (int8_T)!(helicopter1_M->Timing.t[0] >= 2.0);
    helicopter1_DW.If_ActiveSubsystem = rtAction;
  } else {
    rtAction = helicopter1_DW.If_ActiveSubsystem;
  }

  if (rtAction == 0) {
    /* Outputs for IfAction SubSystem: '<S4>/If Action Subsystem' incorporates:
     *  ActionPort: '<S7>/Action Port'
     */
    helicopter1_B.In1 = helicopter1_P.K_ei * rtb_Derivative;
    if (rtmIsMajorTimeStep(helicopter1_M)) {
      srUpdateBC(helicopter1_DW.IfActionSubsystem_SubsysRanBC);
    }

    /* End of Outputs for SubSystem: '<S4>/If Action Subsystem' */
  }

  /* End of If: '<S4>/If' */
  if (rtmIsMajorTimeStep(helicopter1_M)) {
  }

  /* Derivative: '<S5>/Derivative' */
  rtb_Derivative = helicopter1_M->Timing.t[0];
  if ((helicopter1_DW.TimeStampA >= rtb_Derivative) &&
      (helicopter1_DW.TimeStampB >= rtb_Derivative)) {
    rtb_Derivative = 0.0;
  } else {
    rtb_Backgain = helicopter1_DW.TimeStampA;
    lastU = &helicopter1_DW.LastUAtTimeA;
    if (helicopter1_DW.TimeStampA < helicopter1_DW.TimeStampB) {
      if (helicopter1_DW.TimeStampB < rtb_Derivative) {
        rtb_Backgain = helicopter1_DW.TimeStampB;
        lastU = &helicopter1_DW.LastUAtTimeB;
      }
    } else {
      if (helicopter1_DW.TimeStampA >= rtb_Derivative) {
        rtb_Backgain = helicopter1_DW.TimeStampB;
        lastU = &helicopter1_DW.LastUAtTimeB;
      }
    }

    rtb_Derivative = (helicopter1_B.PitchCounttorad - *lastU) / (rtb_Derivative
      - rtb_Backgain);
  }

  /* End of Derivative: '<S5>/Derivative' */

  /* Gain: '<S12>/Gain' */
  helicopter1_B.Gain_l = helicopter1_P.Gain_Gain_a1 * rtb_Derivative;
  if (rtmIsMajorTimeStep(helicopter1_M)) {
  }

  /* Gain: '<S1>/Back gain' */
  rtb_Clock *= helicopter1_P.Backgain_Gain;

  /* Saturate: '<S5>/Back motor: Saturation' */
  if (rtb_Clock > helicopter1_P.BackmotorSaturation_UpperSat) {
    /* Saturate: '<S5>/Back motor: Saturation' */
    helicopter1_B.BackmotorSaturation =
      helicopter1_P.BackmotorSaturation_UpperSat;
  } else if (rtb_Clock < helicopter1_P.BackmotorSaturation_LowerSat) {
    /* Saturate: '<S5>/Back motor: Saturation' */
    helicopter1_B.BackmotorSaturation =
      helicopter1_P.BackmotorSaturation_LowerSat;
  } else {
    /* Saturate: '<S5>/Back motor: Saturation' */
    helicopter1_B.BackmotorSaturation = rtb_Clock;
  }

  /* End of Saturate: '<S5>/Back motor: Saturation' */
  if (rtmIsMajorTimeStep(helicopter1_M)) {
  }

  /* Saturate: '<S5>/Front motor: Saturation' */
  if (rtb_Frontgain > helicopter1_P.FrontmotorSaturation_UpperSat) {
    /* Saturate: '<S5>/Front motor: Saturation' */
    helicopter1_B.FrontmotorSaturation =
      helicopter1_P.FrontmotorSaturation_UpperSat;
  } else if (rtb_Frontgain < helicopter1_P.FrontmotorSaturation_LowerSat) {
    /* Saturate: '<S5>/Front motor: Saturation' */
    helicopter1_B.FrontmotorSaturation =
      helicopter1_P.FrontmotorSaturation_LowerSat;
  } else {
    /* Saturate: '<S5>/Front motor: Saturation' */
    helicopter1_B.FrontmotorSaturation = rtb_Frontgain;
  }

  /* End of Saturate: '<S5>/Front motor: Saturation' */
  if (rtmIsMajorTimeStep(helicopter1_M)) {
    /* S-Function (hil_write_analog_block): '<S5>/HIL Write Analog' */

    /* S-Function Block: helicopter1/Helicopter_interface/HIL Write Analog (hil_write_analog_block) */
    {
      t_error result;
      helicopter1_DW.HILWriteAnalog_Buffer[0] =
        helicopter1_B.FrontmotorSaturation;
      helicopter1_DW.HILWriteAnalog_Buffer[1] =
        helicopter1_B.BackmotorSaturation;
      result = hil_write_analog(helicopter1_DW.HILInitialize_Card,
        helicopter1_P.HILWriteAnalog_channels, 2,
        &helicopter1_DW.HILWriteAnalog_Buffer[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(helicopter1_M, _rt_error_message);
      }
    }
  }
}

/* Model update function */
void helicopter1_update(void)
{
  real_T *lastU;

  /* Update for Derivative: '<S5>/Derivative' */
  if (helicopter1_DW.TimeStampA == (rtInf)) {
    helicopter1_DW.TimeStampA = helicopter1_M->Timing.t[0];
    lastU = &helicopter1_DW.LastUAtTimeA;
  } else if (helicopter1_DW.TimeStampB == (rtInf)) {
    helicopter1_DW.TimeStampB = helicopter1_M->Timing.t[0];
    lastU = &helicopter1_DW.LastUAtTimeB;
  } else if (helicopter1_DW.TimeStampA < helicopter1_DW.TimeStampB) {
    helicopter1_DW.TimeStampA = helicopter1_M->Timing.t[0];
    lastU = &helicopter1_DW.LastUAtTimeA;
  } else {
    helicopter1_DW.TimeStampB = helicopter1_M->Timing.t[0];
    lastU = &helicopter1_DW.LastUAtTimeB;
  }

  *lastU = helicopter1_B.PitchCounttorad;

  /* End of Update for Derivative: '<S5>/Derivative' */
  if (rtmIsMajorTimeStep(helicopter1_M)) {
    rt_ertODEUpdateContinuousStates(&helicopter1_M->solverInfo);
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
  if (!(++helicopter1_M->Timing.clockTick0)) {
    ++helicopter1_M->Timing.clockTickH0;
  }

  helicopter1_M->Timing.t[0] = rtsiGetSolverStopTime(&helicopter1_M->solverInfo);

  {
    /* Update absolute timer for sample time: [0.002s, 0.0s] */
    /* The "clockTick1" counts the number of times the code of this task has
     * been executed. The absolute time is the multiplication of "clockTick1"
     * and "Timing.stepSize1". Size of "clockTick1" ensures timer will not
     * overflow during the application lifespan selected.
     * Timer of this task consists of two 32 bit unsigned integers.
     * The two integers represent the low bits Timing.clockTick1 and the high bits
     * Timing.clockTickH1. When the low bit overflows to 0, the high bits increment.
     */
    if (!(++helicopter1_M->Timing.clockTick1)) {
      ++helicopter1_M->Timing.clockTickH1;
    }

    helicopter1_M->Timing.t[1] = helicopter1_M->Timing.clockTick1 *
      helicopter1_M->Timing.stepSize1 + helicopter1_M->Timing.clockTickH1 *
      helicopter1_M->Timing.stepSize1 * 4294967296.0;
  }
}

/* Derivatives for root system: '<Root>' */
void helicopter1_derivatives(void)
{
  XDot_helicopter1_T *_rtXdot;
  boolean_T lsat;
  boolean_T usat;
  _rtXdot = ((XDot_helicopter1_T *) helicopter1_M->derivs);

  /* Derivatives for TransferFcn: '<S5>/Travel: Transfer Fcn' */
  _rtXdot->TravelTransferFcn_CSTATE = 0.0;
  _rtXdot->TravelTransferFcn_CSTATE += helicopter1_P.TravelTransferFcn_A *
    helicopter1_X.TravelTransferFcn_CSTATE;
  _rtXdot->TravelTransferFcn_CSTATE += helicopter1_B.TravelCounttorad;

  /* Derivatives for TransferFcn: '<S5>/Pitch: Transfer Fcn' */
  _rtXdot->PitchTransferFcn_CSTATE = 0.0;
  _rtXdot->PitchTransferFcn_CSTATE += helicopter1_P.PitchTransferFcn_A *
    helicopter1_X.PitchTransferFcn_CSTATE;
  _rtXdot->PitchTransferFcn_CSTATE += helicopter1_B.PitchCounttorad;

  /* Derivatives for TransferFcn: '<S5>/Elevation: Transfer Fcn' */
  _rtXdot->ElevationTransferFcn_CSTATE = 0.0;
  _rtXdot->ElevationTransferFcn_CSTATE += helicopter1_P.ElevationTransferFcn_A *
    helicopter1_X.ElevationTransferFcn_CSTATE;
  _rtXdot->ElevationTransferFcn_CSTATE += helicopter1_B.ElevationCounttorad;

  /* Derivatives for Integrator: '<S4>/Integrator' */
  lsat = (helicopter1_X.Integrator_CSTATE <= helicopter1_P.Integrator_LowerSat);
  usat = (helicopter1_X.Integrator_CSTATE >= helicopter1_P.Integrator_UpperSat);
  if (((!lsat) && (!usat)) || (lsat && (helicopter1_B.In1 > 0.0)) || (usat &&
       (helicopter1_B.In1 < 0.0))) {
    _rtXdot->Integrator_CSTATE = helicopter1_B.In1;
  } else {
    /* in saturation */
    _rtXdot->Integrator_CSTATE = 0.0;
  }

  /* End of Derivatives for Integrator: '<S4>/Integrator' */
}

/* Model initialize function */
void helicopter1_initialize(void)
{
  /* Start for S-Function (hil_initialize_block): '<Root>/HIL Initialize' */

  /* S-Function Block: helicopter1/HIL Initialize (hil_initialize_block) */
  {
    t_int result;
    t_boolean is_switching;
    result = hil_open("q8_usb", "0", &helicopter1_DW.HILInitialize_Card);
    if (result < 0) {
      msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
        (_rt_error_message));
      rtmSetErrorStatus(helicopter1_M, _rt_error_message);
      return;
    }

    is_switching = false;
    result = hil_set_card_specific_options(helicopter1_DW.HILInitialize_Card,
      "update_rate=normal;decimation=1", 32);
    if (result < 0) {
      msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
        (_rt_error_message));
      rtmSetErrorStatus(helicopter1_M, _rt_error_message);
      return;
    }

    result = hil_watchdog_clear(helicopter1_DW.HILInitialize_Card);
    if (result < 0 && result != -QERR_HIL_WATCHDOG_CLEAR) {
      msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
        (_rt_error_message));
      rtmSetErrorStatus(helicopter1_M, _rt_error_message);
      return;
    }

    if ((helicopter1_P.HILInitialize_AIPStart && !is_switching) ||
        (helicopter1_P.HILInitialize_AIPEnter && is_switching)) {
      {
        int_T i1;
        real_T *dw_AIMinimums = &helicopter1_DW.HILInitialize_AIMinimums[0];
        for (i1=0; i1 < 8; i1++) {
          dw_AIMinimums[i1] = (helicopter1_P.HILInitialize_AILow);
        }
      }

      {
        int_T i1;
        real_T *dw_AIMaximums = &helicopter1_DW.HILInitialize_AIMaximums[0];
        for (i1=0; i1 < 8; i1++) {
          dw_AIMaximums[i1] = helicopter1_P.HILInitialize_AIHigh;
        }
      }

      result = hil_set_analog_input_ranges(helicopter1_DW.HILInitialize_Card,
        helicopter1_P.HILInitialize_AIChannels, 8U,
        &helicopter1_DW.HILInitialize_AIMinimums[0],
        &helicopter1_DW.HILInitialize_AIMaximums[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(helicopter1_M, _rt_error_message);
        return;
      }
    }

    if ((helicopter1_P.HILInitialize_AOPStart && !is_switching) ||
        (helicopter1_P.HILInitialize_AOPEnter && is_switching)) {
      {
        int_T i1;
        real_T *dw_AOMinimums = &helicopter1_DW.HILInitialize_AOMinimums[0];
        for (i1=0; i1 < 8; i1++) {
          dw_AOMinimums[i1] = (helicopter1_P.HILInitialize_AOLow);
        }
      }

      {
        int_T i1;
        real_T *dw_AOMaximums = &helicopter1_DW.HILInitialize_AOMaximums[0];
        for (i1=0; i1 < 8; i1++) {
          dw_AOMaximums[i1] = helicopter1_P.HILInitialize_AOHigh;
        }
      }

      result = hil_set_analog_output_ranges(helicopter1_DW.HILInitialize_Card,
        helicopter1_P.HILInitialize_AOChannels, 8U,
        &helicopter1_DW.HILInitialize_AOMinimums[0],
        &helicopter1_DW.HILInitialize_AOMaximums[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(helicopter1_M, _rt_error_message);
        return;
      }
    }

    if ((helicopter1_P.HILInitialize_AOStart && !is_switching) ||
        (helicopter1_P.HILInitialize_AOEnter && is_switching)) {
      {
        int_T i1;
        real_T *dw_AOVoltages = &helicopter1_DW.HILInitialize_AOVoltages[0];
        for (i1=0; i1 < 8; i1++) {
          dw_AOVoltages[i1] = helicopter1_P.HILInitialize_AOInitial;
        }
      }

      result = hil_write_analog(helicopter1_DW.HILInitialize_Card,
        helicopter1_P.HILInitialize_AOChannels, 8U,
        &helicopter1_DW.HILInitialize_AOVoltages[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(helicopter1_M, _rt_error_message);
        return;
      }
    }

    if (helicopter1_P.HILInitialize_AOReset) {
      {
        int_T i1;
        real_T *dw_AOVoltages = &helicopter1_DW.HILInitialize_AOVoltages[0];
        for (i1=0; i1 < 8; i1++) {
          dw_AOVoltages[i1] = helicopter1_P.HILInitialize_AOWatchdog;
        }
      }

      result = hil_watchdog_set_analog_expiration_state
        (helicopter1_DW.HILInitialize_Card,
         helicopter1_P.HILInitialize_AOChannels, 8U,
         &helicopter1_DW.HILInitialize_AOVoltages[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(helicopter1_M, _rt_error_message);
        return;
      }
    }

    if ((helicopter1_P.HILInitialize_EIPStart && !is_switching) ||
        (helicopter1_P.HILInitialize_EIPEnter && is_switching)) {
      {
        int_T i1;
        int32_T *dw_QuadratureModes =
          &helicopter1_DW.HILInitialize_QuadratureModes[0];
        for (i1=0; i1 < 8; i1++) {
          dw_QuadratureModes[i1] = helicopter1_P.HILInitialize_EIQuadrature;
        }
      }

      result = hil_set_encoder_quadrature_mode(helicopter1_DW.HILInitialize_Card,
        helicopter1_P.HILInitialize_EIChannels, 8U, (t_encoder_quadrature_mode *)
        &helicopter1_DW.HILInitialize_QuadratureModes[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(helicopter1_M, _rt_error_message);
        return;
      }
    }

    if ((helicopter1_P.HILInitialize_EIStart && !is_switching) ||
        (helicopter1_P.HILInitialize_EIEnter && is_switching)) {
      {
        int_T i1;
        int32_T *dw_InitialEICounts =
          &helicopter1_DW.HILInitialize_InitialEICounts[0];
        for (i1=0; i1 < 8; i1++) {
          dw_InitialEICounts[i1] = helicopter1_P.HILInitialize_EIInitial;
        }
      }

      result = hil_set_encoder_counts(helicopter1_DW.HILInitialize_Card,
        helicopter1_P.HILInitialize_EIChannels, 8U,
        &helicopter1_DW.HILInitialize_InitialEICounts[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(helicopter1_M, _rt_error_message);
        return;
      }
    }

    if ((helicopter1_P.HILInitialize_POPStart && !is_switching) ||
        (helicopter1_P.HILInitialize_POPEnter && is_switching)) {
      uint32_T num_duty_cycle_modes = 0;
      uint32_T num_frequency_modes = 0;

      {
        int_T i1;
        int32_T *dw_POModeValues = &helicopter1_DW.HILInitialize_POModeValues[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POModeValues[i1] = helicopter1_P.HILInitialize_POModes;
        }
      }

      result = hil_set_pwm_mode(helicopter1_DW.HILInitialize_Card,
        helicopter1_P.HILInitialize_POChannels, 8U, (t_pwm_mode *)
        &helicopter1_DW.HILInitialize_POModeValues[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(helicopter1_M, _rt_error_message);
        return;
      }

      {
        int_T i1;
        const uint32_T *p_HILInitialize_POChannels =
          helicopter1_P.HILInitialize_POChannels;
        int32_T *dw_POModeValues = &helicopter1_DW.HILInitialize_POModeValues[0];
        for (i1=0; i1 < 8; i1++) {
          if (dw_POModeValues[i1] == PWM_DUTY_CYCLE_MODE || dw_POModeValues[i1] ==
              PWM_ONE_SHOT_MODE || dw_POModeValues[i1] == PWM_TIME_MODE ||
              dw_POModeValues[i1] == PWM_RAW_MODE) {
            helicopter1_DW.HILInitialize_POSortedChans[num_duty_cycle_modes] =
              (p_HILInitialize_POChannels[i1]);
            helicopter1_DW.HILInitialize_POSortedFreqs[num_duty_cycle_modes] =
              helicopter1_P.HILInitialize_POFrequency;
            num_duty_cycle_modes++;
          } else {
            helicopter1_DW.HILInitialize_POSortedChans[7U - num_frequency_modes]
              = (p_HILInitialize_POChannels[i1]);
            helicopter1_DW.HILInitialize_POSortedFreqs[7U - num_frequency_modes]
              = helicopter1_P.HILInitialize_POFrequency;
            num_frequency_modes++;
          }
        }
      }

      if (num_duty_cycle_modes > 0) {
        result = hil_set_pwm_frequency(helicopter1_DW.HILInitialize_Card,
          &helicopter1_DW.HILInitialize_POSortedChans[0], num_duty_cycle_modes,
          &helicopter1_DW.HILInitialize_POSortedFreqs[0]);
        if (result < 0) {
          msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
            (_rt_error_message));
          rtmSetErrorStatus(helicopter1_M, _rt_error_message);
          return;
        }
      }

      if (num_frequency_modes > 0) {
        result = hil_set_pwm_duty_cycle(helicopter1_DW.HILInitialize_Card,
          &helicopter1_DW.HILInitialize_POSortedChans[num_duty_cycle_modes],
          num_frequency_modes,
          &helicopter1_DW.HILInitialize_POSortedFreqs[num_duty_cycle_modes]);
        if (result < 0) {
          msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
            (_rt_error_message));
          rtmSetErrorStatus(helicopter1_M, _rt_error_message);
          return;
        }
      }

      {
        int_T i1;
        int32_T *dw_POModeValues = &helicopter1_DW.HILInitialize_POModeValues[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POModeValues[i1] = helicopter1_P.HILInitialize_POConfiguration;
        }
      }

      {
        int_T i1;
        int32_T *dw_POAlignValues = &helicopter1_DW.HILInitialize_POAlignValues
          [0];
        for (i1=0; i1 < 8; i1++) {
          dw_POAlignValues[i1] = helicopter1_P.HILInitialize_POAlignment;
        }
      }

      {
        int_T i1;
        int32_T *dw_POPolarityVals =
          &helicopter1_DW.HILInitialize_POPolarityVals[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POPolarityVals[i1] = helicopter1_P.HILInitialize_POPolarity;
        }
      }

      result = hil_set_pwm_configuration(helicopter1_DW.HILInitialize_Card,
        helicopter1_P.HILInitialize_POChannels, 8U,
        (t_pwm_configuration *) &helicopter1_DW.HILInitialize_POModeValues[0],
        (t_pwm_alignment *) &helicopter1_DW.HILInitialize_POAlignValues[0],
        (t_pwm_polarity *) &helicopter1_DW.HILInitialize_POPolarityVals[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(helicopter1_M, _rt_error_message);
        return;
      }

      {
        int_T i1;
        real_T *dw_POSortedFreqs = &helicopter1_DW.HILInitialize_POSortedFreqs[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POSortedFreqs[i1] = helicopter1_P.HILInitialize_POLeading;
        }
      }

      {
        int_T i1;
        real_T *dw_POValues = &helicopter1_DW.HILInitialize_POValues[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POValues[i1] = helicopter1_P.HILInitialize_POTrailing;
        }
      }

      result = hil_set_pwm_deadband(helicopter1_DW.HILInitialize_Card,
        helicopter1_P.HILInitialize_POChannels, 8U,
        &helicopter1_DW.HILInitialize_POSortedFreqs[0],
        &helicopter1_DW.HILInitialize_POValues[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(helicopter1_M, _rt_error_message);
        return;
      }
    }

    if ((helicopter1_P.HILInitialize_POStart && !is_switching) ||
        (helicopter1_P.HILInitialize_POEnter && is_switching)) {
      {
        int_T i1;
        real_T *dw_POValues = &helicopter1_DW.HILInitialize_POValues[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POValues[i1] = helicopter1_P.HILInitialize_POInitial;
        }
      }

      result = hil_write_pwm(helicopter1_DW.HILInitialize_Card,
        helicopter1_P.HILInitialize_POChannels, 8U,
        &helicopter1_DW.HILInitialize_POValues[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(helicopter1_M, _rt_error_message);
        return;
      }
    }

    if (helicopter1_P.HILInitialize_POReset) {
      {
        int_T i1;
        real_T *dw_POValues = &helicopter1_DW.HILInitialize_POValues[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POValues[i1] = helicopter1_P.HILInitialize_POWatchdog;
        }
      }

      result = hil_watchdog_set_pwm_expiration_state
        (helicopter1_DW.HILInitialize_Card,
         helicopter1_P.HILInitialize_POChannels, 8U,
         &helicopter1_DW.HILInitialize_POValues[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(helicopter1_M, _rt_error_message);
        return;
      }
    }
  }

  /* Start for S-Function (hil_read_encoder_timebase_block): '<S5>/HIL Read Encoder Timebase' */

  /* S-Function Block: helicopter1/Helicopter_interface/HIL Read Encoder Timebase (hil_read_encoder_timebase_block) */
  {
    t_error result;
    result = hil_task_create_encoder_reader(helicopter1_DW.HILInitialize_Card,
      helicopter1_P.HILReadEncoderTimebase_SamplesI,
      helicopter1_P.HILReadEncoderTimebase_Channels, 3,
      &helicopter1_DW.HILReadEncoderTimebase_Task);
    if (result >= 0) {
      result = hil_task_set_buffer_overflow_mode
        (helicopter1_DW.HILReadEncoderTimebase_Task, (t_buffer_overflow_mode)
         (helicopter1_P.HILReadEncoderTimebase_Overflow - 1));
    }

    if (result < 0) {
      msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
        (_rt_error_message));
      rtmSetErrorStatus(helicopter1_M, _rt_error_message);
    }
  }

  /* Start for FromWorkspace: '<Root>/From Workspace1' */
  {
    static real_T pTimeValues0[] = { 0.0, 0.25, 0.5, 0.75, 1.0, 1.25, 1.5, 1.75,
      2.0, 2.25, 2.5, 2.75, 3.0, 3.25, 3.5, 3.75, 4.0, 4.25, 4.5, 4.75, 5.0,
      5.25, 5.5, 5.75, 6.0, 6.25, 6.5, 6.75, 7.0, 7.25, 7.5, 7.75, 8.0, 8.25,
      8.5, 8.75, 9.0, 9.25, 9.5, 9.75, 10.0, 10.25, 10.5, 10.75, 11.0, 11.25,
      11.5, 11.75, 12.0, 12.25, 12.5, 12.75, 13.0, 13.25, 13.5, 13.75, 14.0,
      14.25, 14.5, 14.75, 15.0, 15.25, 15.5, 15.75, 16.0, 16.25, 16.5, 16.75,
      17.0, 17.25, 17.5, 17.75, 18.0, 18.25, 18.5, 18.75, 19.0, 19.25, 19.5,
      19.75, 20.0, 20.25, 20.5, 20.75, 21.0, 21.25, 21.5, 21.75, 22.0, 22.25,
      22.5, 22.75, 23.0, 23.25, 23.5, 23.75, 24.0, 24.25, 24.5, 24.75, 25.0,
      25.25, 25.5, 25.75, 26.0, 26.25, 26.5, 26.75, 27.0, 27.25, 27.5, 27.75,
      28.0, 28.25, 28.5, 28.75, 29.0, 29.25, 29.5, 29.75, 30.0, 30.25, 30.5,
      30.75, 31.0, 31.25, 31.5, 31.75, 32.0, 32.25, 32.5, 32.75, 33.0, 33.25,
      33.5, 33.75, 34.0, 34.25, 34.5, 34.75, 35.0 } ;

    static real_T pDataValues0[] = { 3.1415926535897931, 3.1415926535897931,
      3.1415926535897931, 3.1415926535897931, 3.1415926535897931,
      3.1415926535897931, 3.1415926535897931, 3.1415926535897931,
      3.1415926535897931, 3.1415926535897931, 3.1415926535897931,
      3.1415926535897931, 3.1415926535897931, 3.1415926535897931,
      3.1415926535897931, 3.1415926535897931, 3.1415926535897931,
      3.1415926535897931, 3.1415926535897931, 3.1415926535897931,
      3.1415926535897931, 3.1415926535897931, 3.1415926535897931,
      3.1415926535897931, 3.1303411169080282, 3.0954613531943616,
      3.0267425929101939, 2.9178917869340095, 2.7686953064803577,
      2.5838208380249137, 2.3708965696746573, 2.1388159769271473,
      1.8965117135758209, 1.6521777768896417, 1.412841763770817,
      1.1841841890686606, 0.97052020693660956, 0.77488104090053422,
      0.59915129954561253, 0.44423270097463574, 0.31021499569009692,
      0.19654198701046718, 0.1021653830036378, 0.025682469167307313,
      -0.034544231778826422, -0.080285701928217532, -0.11336301604167121,
      -0.13558061867460788, -0.14867477380566316, -0.15427547955056797,
      -0.15388007034007162, -0.14883674413115747, -0.14033632712056776,
      -0.12941070375349062, -0.11693648085359178, -0.10364261010868937,
      -0.090120854201463652, -0.076838141937317347, -0.064150011835779036,
      -0.052314488259490879, -0.041505866839455091, -0.031828005243609341,
      -0.023326820514742826, -0.016001785163565478, -0.00981629130417001,
      -0.004706816071506581, -0.0005908733225680388, 0.0026262226840111152,
      0.0050457250981229291, 0.0067708750192032171, 0.0079032811576135124,
      0.0085401563442758129, 0.0087723050319773559, 0.0086827564039842747,
      0.0083459413157726935, 0.0078273172339345665, 0.007183352900946802,
      0.0064617930506466357, 0.0057021326320919668, 0.0049362392689519478,
      0.004189071771403226, 0.00347945118836368, 0.0028208489660512576,
      0.0022221641478799865, 0.0016884681416887135, 0.0012217013638259227,
      0.00082131104751652091, 0.00048482370152040774, 0.00020834916872713484,
      -1.2983979856986252E-5, -0.00018465980705580757, -0.00031246958855649662,
      -0.00040226491229644715, -0.00045976384636902106, -0.00049040430488208058,
      -0.00049923859688659825, -0.00049086321701495138, -0.00046937817715765384,
      -0.00043837054184153441, -0.00040091727758963887, -0.00035960302603326951,
      -0.00031654893510609265, -0.00027344921068571035, -0.00023161256562383343,
      -0.00019200623144562882, -0.00015530065092222761, -0.00012191338108516747,
      -9.2051102447397859E-5, -6.5748949613830436E-5, -4.2906651026402362E-5,
      -2.3321192280200384E-5, -6.7158998572066593E-6, 7.2340180120837125E-6,
      1.8879337935894627E-5, 2.8577901860695411E-5, 3.6678701208029504E-5,
      4.3508781399127963E-5, 4.9362857930061973E-5, 5.4495659622966307E-5,
      5.9117184271185865E-5, 6.339123733983537E-5, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, -0.045006146730963328,
      -0.1395190548549147, -0.27487504113863659, -0.43540322390495784,
      -0.59678592181272028, -0.7394978738242588, -0.85169707340127587,
      -0.9283223709887487, -0.96921705340496378, -0.9773357467432634,
      -0.95734405247513554, -0.91463029880908442, -0.8546559285280827,
      -0.78255666414357816, -0.702918965419767, -0.61967439428423676,
      -0.53607082113803106, -0.45469203471858655, -0.37750641602734791,
      -0.30593165534569566, -0.24090680378456944, -0.18296588059758584,
      -0.13230925645377761, -0.0888704105316064, -0.052376620524106819,
      -0.022402822979669109, 0.0015816368422143549, 0.020173304835660686,
      0.0340016680422269, 0.043702493468339272, 0.049896891599545842,
      0.053175482979572052, 0.054087023628919366, 0.053130849056537657,
      0.050752520406143, 0.047342094305143, 0.0432344856801403,
      0.03871144638339185, 0.034004738915479574, 0.029300141404710378,
      0.0247419754375812, 0.020437900930650413, 0.016463770995749517,
      0.01286838402632489, 0.00967800965646071, 0.00690059968432967,
      0.004529624553647661, 0.0025475007466437636, 0.00092859475079828111,
      -0.00035819451197918549, -0.0013472603528445408, -0.0020744963273574648,
      -0.0025758573319463024, -0.0028862394011967725, -0.0030386416742188903,
      -0.0030635734525589695, -0.0029886699901966679, -0.0028384823321583336,
      -0.0026344088892513934, -0.0023947392726854492, -0.0021347840247649013,
      -0.0018670671114510552, -0.0016015612652380037, -0.0013459493839841461,
      -0.0011058981311724053, -0.00088533259433684348, -0.00068670330879576911,
      -0.000511239126003002, -0.0003591812949598, -0.0002299957362908246,
      -0.00012256183405166056, -3.53371680192642E-5, 3.3501519486032651E-5,
      8.5940159428414623E-5, 0.00012403054126473279, 0.00014981305700729745,
      0.0001652570062257212, 0.00017221636370882897, 0.00017239889768154082,
      0.00016734658024750645, 0.0001584253367127328, 0.00014682232209365268,
      0.00013354907934830064, 0.00011944911455104561, 0.00010520861133427144,
      9.1369194349732175E-5, 7.8341834984803943E-5, 6.6421169691963965E-5,
      5.5799671477148778E-5, 4.6581279695263288E-5, 3.8794255699214848E-5,
      3.2403197389331247E-5, 2.7320320764392569E-5, 2.3416306123744959E-5,
      2.0531206771621445E-5, 1.8486098592880153E-5, 1.7096212274598673E-5,
      1.6185982548550081E-5, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.31808625617684494, 0.66798113797179326, 0.95664441545145085,
      1.13455188635566, 1.1405912730006293, 1.0086335718042774,
      0.79298109113000681, 0.54155833839704215, 0.2890279966768754,
      0.057379823810050246, -0.14129365978614716, -0.30188449754657531,
      -0.42387594354061475, -0.50957006428795193, -0.56284883909974326,
      -0.58834083575110663, -0.59087812484938773, -0.57515418196677348,
      -0.54551847393122088, -0.50586307243909312, -0.45957081633332675,
      -0.40950431610504134, -0.35802167250725736, -0.30700917267561234,
      -0.25792416994825018, -0.21184335335366122, -0.16951300179774842,
      -0.13139880878958254, -0.097733589770130358, -0.068561729140835581,
      -0.043779640208213344, -0.02317183170485948, -0.0064424211706402,
      0.0067578766916009947, 0.01680911856228362, 0.024103589161419192,
      0.029031008970388461, 0.031967114295778254, 0.0332652107824265,
      0.033250298411075407, 0.032215376186276679, 0.030419554789036685,
      0.02808763256722302, 0.025410821938326444, 0.022548347568293936,
      0.019629672925698394, 0.016757146693115565, 0.014008894048866516,
      0.011441809280949622, 0.0090945350546527415, 0.0069903396159802789,
      0.0051398261195667594, 0.00354342809896413, 0.0021936619233773325,
      0.0010771210597342318, 0.00017620828729869586, -0.00052938906465493929,
      -0.001061469006839566, -0.0014423131540988177, -0.0016938933144885482,
      -0.0018372644093582746, -0.0018921208959987723, -0.0018764939181949991,
      -0.0018065671525888671, -0.0016965905737298392, -0.001558872975268244,
      -0.0014038359290693414, -0.0012401138301312287, -0.0010746866753990059,
      -0.000913034189711226, -0.00075930178951466587, -0.0006164706264077946,
      -0.0004865255521917522, -0.00037061627958023813, -0.00026920827121590385,
      -0.00018222097433029383, -0.00010915193466964901, -4.918608075188402E-5,
      -1.2900804040594238E-6, 3.5707850025490373E-5, 6.3051942073455436E-5,
      8.2005675868579431E-5, 9.3810210364031477E-5, 9.9653166082402933E-5,
      0.00010064643795759665, 9.7811713652085075E-5, 9.2072400540210708E-5,
      8.4250709510902411E-5, 7.50686927855071E-5, 6.515207239665699E-5,
      5.5035711558737432E-5, 4.5169559240720858E-5, 3.592383071659988E-5,
      2.7592084446359522E-5, 2.0390780334222924E-5, 1.4454043532952099E-5,
      9.8231856675568E-6, 6.433156065854817E-6, 4.1049580077334724E-6, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.2723450247037376,
      1.3995795271742379, 1.1546531099186139, 0.71162988361408308,
      0.024157546580078119, -0.527830804785797, -0.86260992269688808,
      -1.0056910109313708, -1.0101213668868561, -0.92659269146664525,
      -0.79469393438517566, -0.64236335104083908, -0.48796578397680429,
      -0.34277648299000157, -0.21311509924733038, -0.10196798660549869,
      -0.010149156393032592, 0.062895771530426692, 0.11854283214152757,
      0.15862160596867303, 0.18516902442305369, 0.20026600091304575,
      0.20593057439180695, 0.20404999932647314, 0.19634001090969269,
      0.18432326637781896, 0.16932140622376293, 0.15245677203273217,
      0.13466087607817576, 0.1166874425173411, 0.099128355730523629,
      0.082431234013167987, 0.066917642136832448, 0.052801191448817487,
      0.040204967482751437, 0.029177882396528125, 0.019709679235841132,
      0.011744421301543167, 0.0051923859465975424, -5.9649485396551733E-5,
      -0.0041396888991954983, -0.0071832855889062729, -0.0093276888872152186,
      -0.010707242515568063, -0.011449897480121625, -0.011674698570314659,
      -0.01149010493031192, -0.010993010576975836, -0.010268339071699504,
      -0.00938909690517992, -0.0084167817546659286, -0.007402053985639972,
      -0.0063855920824135489, -0.0053990647023346534, -0.00446616345458464,
      -0.0036036510897421025, -0.0028223894078264187, -0.0021283197687388131,
      -0.0015233765890393771, -0.0010063206415587237, -0.00057348437947754973,
      -0.00021942594656125357, 6.2507911214428676E-5, 0.00027970706242367135,
      0.00043990631543645734, 0.00055087039384765725, 0.00062014818479559435,
      0.00065488839575101134, 0.00066170861892890639, 0.00064660994275269213,
      0.00061492960078579086, 0.000571324652425994, 0.00051978029686273965,
      0.00046363709044822642, 0.000405632033458056, 0.00034794918754163436,
      0.00029227615864487036, 0.00023986341566934453, 0.00019158400139172329,
      0.00014799172171874695, 0.00010937636819248315, 7.5814935179862561E-5,
      4.7218137982254658E-5, 2.3371822873640643E-5, 3.9730875004238283E-6,
      -1.1338897222211492E-5, -2.295725244773485E-5, -3.1286764117033724E-5,
      -3.6728066901578114E-5, -3.9666481555511805E-5, -4.046544335116142E-5,
      -3.9464609272431471E-5, -3.6982914096364248E-5, -3.33269850810927E-5,
      -2.8805216448187637E-5, -2.3746947204975332E-5, -1.852343146054699E-5,
      -1.3560118407630882E-5, -9.3127922316009626E-6, -6.1421356365024973E-6,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0 } ;

    helicopter1_DW.FromWorkspace1_PWORK.TimePtr = (void *) pTimeValues0;
    helicopter1_DW.FromWorkspace1_PWORK.DataPtr = (void *) pDataValues0;
    helicopter1_DW.FromWorkspace1_IWORK.PrevIndex = 0;
  }

  /* Start for FromWorkspace: '<Root>/From Workspace' */
  {
    static real_T pTimeValues0[] = { 0.0, 0.25, 0.5, 0.75, 1.0, 1.25, 1.5, 1.75,
      2.0, 2.25, 2.5, 2.75, 3.0, 3.25, 3.5, 3.75, 4.0, 4.25, 4.5, 4.75, 5.0,
      5.25, 5.5, 5.75, 6.0, 6.25, 6.5, 6.75, 7.0, 7.25, 7.5, 7.75, 8.0, 8.25,
      8.5, 8.75, 9.0, 9.25, 9.5, 9.75, 10.0, 10.25, 10.5, 10.75, 11.0, 11.25,
      11.5, 11.75, 12.0, 12.25, 12.5, 12.75, 13.0, 13.25, 13.5, 13.75, 14.0,
      14.25, 14.5, 14.75, 15.0, 15.25, 15.5, 15.75, 16.0, 16.25, 16.5, 16.75,
      17.0, 17.25, 17.5, 17.75, 18.0, 18.25, 18.5, 18.75, 19.0, 19.25, 19.5,
      19.75, 20.0, 20.25, 20.5, 20.75, 21.0, 21.25, 21.5, 21.75, 22.0, 22.25,
      22.5, 22.75, 23.0, 23.25, 23.5, 23.75, 24.0, 24.25, 24.5, 24.75, 25.0,
      25.25, 25.5, 25.75, 26.0, 26.25, 26.5, 26.75, 27.0, 27.25, 27.5, 27.75,
      28.0, 28.25, 28.5, 28.75, 29.0, 29.25, 29.5, 29.75, 30.0, 30.25, 30.5,
      30.75, 31.0, 31.25, 31.5, 31.75, 32.0, 32.25, 32.5, 32.75, 33.0, 33.25,
      33.5, 33.75, 34.0, 34.25, 34.5, 34.75, 35.0 } ;

    static real_T pDataValues0[] = { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.570796326794258,
      1.5707963267952683, 1.5707963267950409, 1.4039867831860819,
      0.898613005843957, 0.47992650432679573, 0.14080504803986749,
      -0.12646521666696997, -0.329922940714215, -0.4776769144154418,
      -0.57768146658093711, -0.63755098804372845, -0.66441643617234336,
      -0.66482265136406948, -0.644662920019955, -0.60914596142473121,
      -0.56279002148552859, -0.5094387528255151, -0.45229385943152178,
      -0.39395995634383763, -0.33649765439281443, -0.281481469388712,
      -0.23005973695003812, -0.183014264392376, -0.14081795525159868,
      -0.10368909207471999, -0.071641355644644911, -0.044528993587767962,
      -0.022086830347287423, -0.0039650372963531133, 0.010241239216018716,
      0.020967157822344484, 0.028658037243089129, 0.033753387103946375,
      0.036674675542791579, 0.037816377491907582, 0.037539848187204683,
      0.036169580986059158, 0.033991433435134111, 0.031252437653727982,
      0.028161847880384894, 0.024893117301215018, 0.021586536274765145,
      0.018352303397870973, 0.015273838457883659, 0.012411181416961403,
      0.009804353650656461, 0.0074765864023087492, 0.0054373466758286249,
      0.0036851125698398324, 0.0022098684610087904, 0.00099530565937255844,
      2.0726426040340584E-5, -0.00073734115709500614, -0.0013038027459175705,
      -0.0017039118349968518, -0.0019624151116874877, -0.0021029038459785543,
      -0.0021473453759692784, -0.0021157689854254258, -0.0020260814446191322,
      -0.0018939890041345109, -0.0017330045255674609, -0.0015545205610572044,
      -0.0013679314377081919, -0.0011807896682629604, -0.00099898422137068,
      -0.00082693028727875983, -0.00066776212739871887, -0.00052352237227992759,
      -0.00039534271674446231, -0.00028361234730689411, -0.00018813162702091546,
      -0.00010824956373833849, -4.2984410941304674E-5, 8.8725897975372447E-6,
      4.8669802723111388E-5, 7.7823222959683136E-5, 9.775875647211052E-5,
      0.00010986740267981965, 0.00011547188999139202, 0.00011580328010007968,
      0.00011198607104190295, 0.00010503037843068164, 9.5829846429751342E-5,
      8.5164022907147086E-5, 7.3704014839970355E-5, 6.2020307636911909E-5,
      5.0591671540312078E-5, 3.9814073874877565E-5, 3.0008451803453795E-5,
      2.1426066301399871E-5, 1.4249966905355294E-5, 8.5909250779891977E-6,
      4.476277704057452E-6, 1.8310652363240365E-6, 4.5406830917471552E-7, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 } ;

    helicopter1_DW.FromWorkspace_PWORK.TimePtr = (void *) pTimeValues0;
    helicopter1_DW.FromWorkspace_PWORK.DataPtr = (void *) pDataValues0;
    helicopter1_DW.FromWorkspace_IWORK.PrevIndex = 0;
  }

  /* Start for ToFile: '<Root>/To File' */
  {
    FILE *fp = (NULL);
    char fileName[509] = "Lab_3_case_files\\lab_3_case_1_5.mat";
    if ((fp = fopen(fileName, "wb")) == (NULL)) {
      rtmSetErrorStatus(helicopter1_M,
                        "Error creating .mat file Lab_3_case_files\\lab_3_case_1_5.mat");
      return;
    }

    if (rt_WriteMat4FileHeader(fp, 5 + 1, 0, "helidata")) {
      rtmSetErrorStatus(helicopter1_M,
                        "Error writing mat file header to file Lab_3_case_files\\lab_3_case_1_5.mat");
      return;
    }

    helicopter1_DW.ToFile_IWORK.Count = 0;
    helicopter1_DW.ToFile_IWORK.Decimation = -1;
    helicopter1_DW.ToFile_PWORK.FilePtr = fp;
  }

  /* Start for If: '<S4>/If' */
  helicopter1_DW.If_ActiveSubsystem = -1;

  /* InitializeConditions for TransferFcn: '<S5>/Travel: Transfer Fcn' */
  helicopter1_X.TravelTransferFcn_CSTATE = 0.0;

  /* InitializeConditions for TransferFcn: '<S5>/Pitch: Transfer Fcn' */
  helicopter1_X.PitchTransferFcn_CSTATE = 0.0;

  /* InitializeConditions for TransferFcn: '<S5>/Elevation: Transfer Fcn' */
  helicopter1_X.ElevationTransferFcn_CSTATE = 0.0;

  /* InitializeConditions for Integrator: '<S4>/Integrator' */
  helicopter1_X.Integrator_CSTATE = helicopter1_P.Integrator_IC;

  /* InitializeConditions for Derivative: '<S5>/Derivative' */
  helicopter1_DW.TimeStampA = (rtInf);
  helicopter1_DW.TimeStampB = (rtInf);
}

/* Model terminate function */
void helicopter1_terminate(void)
{
  /* Terminate for S-Function (hil_initialize_block): '<Root>/HIL Initialize' */

  /* S-Function Block: helicopter1/HIL Initialize (hil_initialize_block) */
  {
    t_boolean is_switching;
    t_int result;
    t_uint32 num_final_analog_outputs = 0;
    t_uint32 num_final_pwm_outputs = 0;
    hil_task_stop_all(helicopter1_DW.HILInitialize_Card);
    hil_monitor_stop_all(helicopter1_DW.HILInitialize_Card);
    is_switching = false;
    if ((helicopter1_P.HILInitialize_AOTerminate && !is_switching) ||
        (helicopter1_P.HILInitialize_AOExit && is_switching)) {
      {
        int_T i1;
        real_T *dw_AOVoltages = &helicopter1_DW.HILInitialize_AOVoltages[0];
        for (i1=0; i1 < 8; i1++) {
          dw_AOVoltages[i1] = helicopter1_P.HILInitialize_AOFinal;
        }
      }

      num_final_analog_outputs = 8U;
    } else {
      num_final_analog_outputs = 0;
    }

    if ((helicopter1_P.HILInitialize_POTerminate && !is_switching) ||
        (helicopter1_P.HILInitialize_POExit && is_switching)) {
      {
        int_T i1;
        real_T *dw_POValues = &helicopter1_DW.HILInitialize_POValues[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POValues[i1] = helicopter1_P.HILInitialize_POFinal;
        }
      }

      num_final_pwm_outputs = 8U;
    } else {
      num_final_pwm_outputs = 0;
    }

    if (0
        || num_final_analog_outputs > 0
        || num_final_pwm_outputs > 0
        ) {
      /* Attempt to write the final outputs atomically (due to firmware issue in old Q2-USB). Otherwise write channels individually */
      result = hil_write(helicopter1_DW.HILInitialize_Card
                         , helicopter1_P.HILInitialize_AOChannels,
                         num_final_analog_outputs
                         , helicopter1_P.HILInitialize_POChannels,
                         num_final_pwm_outputs
                         , NULL, 0
                         , NULL, 0
                         , &helicopter1_DW.HILInitialize_AOVoltages[0]
                         , &helicopter1_DW.HILInitialize_POValues[0]
                         , (t_boolean *) NULL
                         , NULL
                         );
      if (result == -QERR_HIL_WRITE_NOT_SUPPORTED) {
        t_error local_result;
        result = 0;

        /* The hil_write operation is not supported by this card. Write final outputs for each channel type */
        if (num_final_analog_outputs > 0) {
          local_result = hil_write_analog(helicopter1_DW.HILInitialize_Card,
            helicopter1_P.HILInitialize_AOChannels, num_final_analog_outputs,
            &helicopter1_DW.HILInitialize_AOVoltages[0]);
          if (local_result < 0) {
            result = local_result;
          }
        }

        if (num_final_pwm_outputs > 0) {
          local_result = hil_write_pwm(helicopter1_DW.HILInitialize_Card,
            helicopter1_P.HILInitialize_POChannels, num_final_pwm_outputs,
            &helicopter1_DW.HILInitialize_POValues[0]);
          if (local_result < 0) {
            result = local_result;
          }
        }

        if (result < 0) {
          msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
            (_rt_error_message));
          rtmSetErrorStatus(helicopter1_M, _rt_error_message);
        }
      }
    }

    hil_task_delete_all(helicopter1_DW.HILInitialize_Card);
    hil_monitor_delete_all(helicopter1_DW.HILInitialize_Card);
    hil_close(helicopter1_DW.HILInitialize_Card);
    helicopter1_DW.HILInitialize_Card = NULL;
  }

  /* Terminate for ToFile: '<Root>/To File' */
  {
    FILE *fp = (FILE *) helicopter1_DW.ToFile_PWORK.FilePtr;
    if (fp != (NULL)) {
      char fileName[509] = "Lab_3_case_files\\lab_3_case_1_5.mat";
      if (fclose(fp) == EOF) {
        rtmSetErrorStatus(helicopter1_M,
                          "Error closing MAT-file Lab_3_case_files\\lab_3_case_1_5.mat");
        return;
      }

      if ((fp = fopen(fileName, "r+b")) == (NULL)) {
        rtmSetErrorStatus(helicopter1_M,
                          "Error reopening MAT-file Lab_3_case_files\\lab_3_case_1_5.mat");
        return;
      }

      if (rt_WriteMat4FileHeader(fp, 5 + 1, helicopter1_DW.ToFile_IWORK.Count,
           "helidata")) {
        rtmSetErrorStatus(helicopter1_M,
                          "Error writing header for helidata to MAT-file Lab_3_case_files\\lab_3_case_1_5.mat");
      }

      if (fclose(fp) == EOF) {
        rtmSetErrorStatus(helicopter1_M,
                          "Error closing MAT-file Lab_3_case_files\\lab_3_case_1_5.mat");
        return;
      }

      helicopter1_DW.ToFile_PWORK.FilePtr = (NULL);
    }
  }
}

/*========================================================================*
 * Start of Classic call interface                                        *
 *========================================================================*/

/* Solver interface called by GRT_Main */
#ifndef USE_GENERATED_SOLVER

void rt_ODECreateIntegrationData(RTWSolverInfo *si)
{
  UNUSED_PARAMETER(si);
  return;
}                                      /* do nothing */

void rt_ODEDestroyIntegrationData(RTWSolverInfo *si)
{
  UNUSED_PARAMETER(si);
  return;
}                                      /* do nothing */

void rt_ODEUpdateContinuousStates(RTWSolverInfo *si)
{
  UNUSED_PARAMETER(si);
  return;
}                                      /* do nothing */

#endif

void MdlOutputs(int_T tid)
{
  helicopter1_output();
  UNUSED_PARAMETER(tid);
}

void MdlUpdate(int_T tid)
{
  helicopter1_update();
  UNUSED_PARAMETER(tid);
}

void MdlInitializeSizes(void)
{
}

void MdlInitializeSampleTimes(void)
{
}

void MdlInitialize(void)
{
}

void MdlStart(void)
{
  helicopter1_initialize();
}

void MdlTerminate(void)
{
  helicopter1_terminate();
}

/* Registration function */
RT_MODEL_helicopter1_T *helicopter1(void)
{
  /* Registration code */

  /* initialize non-finites */
  rt_InitInfAndNaN(sizeof(real_T));

  /* non-finite (run-time) assignments */
  helicopter1_P.Integrator_UpperSat = rtInf;
  helicopter1_P.Integrator_LowerSat = rtMinusInf;

  /* initialize real-time model */
  (void) memset((void *)helicopter1_M, 0,
                sizeof(RT_MODEL_helicopter1_T));

  {
    /* Setup solver object */
    rtsiSetSimTimeStepPtr(&helicopter1_M->solverInfo,
                          &helicopter1_M->Timing.simTimeStep);
    rtsiSetTPtr(&helicopter1_M->solverInfo, &rtmGetTPtr(helicopter1_M));
    rtsiSetStepSizePtr(&helicopter1_M->solverInfo,
                       &helicopter1_M->Timing.stepSize0);
    rtsiSetdXPtr(&helicopter1_M->solverInfo, &helicopter1_M->derivs);
    rtsiSetContStatesPtr(&helicopter1_M->solverInfo, (real_T **)
                         &helicopter1_M->contStates);
    rtsiSetNumContStatesPtr(&helicopter1_M->solverInfo,
      &helicopter1_M->Sizes.numContStates);
    rtsiSetNumPeriodicContStatesPtr(&helicopter1_M->solverInfo,
      &helicopter1_M->Sizes.numPeriodicContStates);
    rtsiSetPeriodicContStateIndicesPtr(&helicopter1_M->solverInfo,
      &helicopter1_M->periodicContStateIndices);
    rtsiSetPeriodicContStateRangesPtr(&helicopter1_M->solverInfo,
      &helicopter1_M->periodicContStateRanges);
    rtsiSetErrorStatusPtr(&helicopter1_M->solverInfo, (&rtmGetErrorStatus
      (helicopter1_M)));
    rtsiSetRTModelPtr(&helicopter1_M->solverInfo, helicopter1_M);
  }

  rtsiSetSimTimeStep(&helicopter1_M->solverInfo, MAJOR_TIME_STEP);
  helicopter1_M->intgData.f[0] = helicopter1_M->odeF[0];
  helicopter1_M->contStates = ((real_T *) &helicopter1_X);
  rtsiSetSolverData(&helicopter1_M->solverInfo, (void *)&helicopter1_M->intgData);
  rtsiSetSolverName(&helicopter1_M->solverInfo,"ode1");

  /* Initialize timing info */
  {
    int_T *mdlTsMap = helicopter1_M->Timing.sampleTimeTaskIDArray;
    mdlTsMap[0] = 0;
    mdlTsMap[1] = 1;
    helicopter1_M->Timing.sampleTimeTaskIDPtr = (&mdlTsMap[0]);
    helicopter1_M->Timing.sampleTimes = (&helicopter1_M->
      Timing.sampleTimesArray[0]);
    helicopter1_M->Timing.offsetTimes = (&helicopter1_M->
      Timing.offsetTimesArray[0]);

    /* task periods */
    helicopter1_M->Timing.sampleTimes[0] = (0.0);
    helicopter1_M->Timing.sampleTimes[1] = (0.002);

    /* task offsets */
    helicopter1_M->Timing.offsetTimes[0] = (0.0);
    helicopter1_M->Timing.offsetTimes[1] = (0.0);
  }

  rtmSetTPtr(helicopter1_M, &helicopter1_M->Timing.tArray[0]);

  {
    int_T *mdlSampleHits = helicopter1_M->Timing.sampleHitArray;
    mdlSampleHits[0] = 1;
    mdlSampleHits[1] = 1;
    helicopter1_M->Timing.sampleHits = (&mdlSampleHits[0]);
  }

  rtmSetTFinal(helicopter1_M, 35.0);
  helicopter1_M->Timing.stepSize0 = 0.002;
  helicopter1_M->Timing.stepSize1 = 0.002;

  /* External mode info */
  helicopter1_M->Sizes.checksums[0] = (654500207U);
  helicopter1_M->Sizes.checksums[1] = (2711976089U);
  helicopter1_M->Sizes.checksums[2] = (3618434078U);
  helicopter1_M->Sizes.checksums[3] = (4284343335U);

  {
    static const sysRanDType rtAlwaysEnabled = SUBSYS_RAN_BC_ENABLE;
    static RTWExtModeInfo rt_ExtModeInfo;
    static const sysRanDType *systemRan[2];
    helicopter1_M->extModeInfo = (&rt_ExtModeInfo);
    rteiSetSubSystemActiveVectorAddresses(&rt_ExtModeInfo, systemRan);
    systemRan[0] = &rtAlwaysEnabled;
    systemRan[1] = (sysRanDType *)&helicopter1_DW.IfActionSubsystem_SubsysRanBC;
    rteiSetModelMappingInfoPtr(helicopter1_M->extModeInfo,
      &helicopter1_M->SpecialInfo.mappingInfo);
    rteiSetChecksumsPtr(helicopter1_M->extModeInfo,
                        helicopter1_M->Sizes.checksums);
    rteiSetTPtr(helicopter1_M->extModeInfo, rtmGetTPtr(helicopter1_M));
  }

  helicopter1_M->solverInfoPtr = (&helicopter1_M->solverInfo);
  helicopter1_M->Timing.stepSize = (0.002);
  rtsiSetFixedStepSize(&helicopter1_M->solverInfo, 0.002);
  rtsiSetSolverMode(&helicopter1_M->solverInfo, SOLVER_MODE_SINGLETASKING);

  /* block I/O */
  helicopter1_M->blockIO = ((void *) &helicopter1_B);

  {
    int32_T i;
    for (i = 0; i < 5; i++) {
      helicopter1_B.TmpSignalConversionAtToFileInpo[i] = 0.0;
    }

    helicopter1_B.TravelCounttorad = 0.0;
    helicopter1_B.Gain = 0.0;
    helicopter1_B.Sum5 = 0.0;
    helicopter1_B.Gain_d = 0.0;
    helicopter1_B.PitchCounttorad = 0.0;
    helicopter1_B.Gain_i = 0.0;
    helicopter1_B.Gain_b = 0.0;
    helicopter1_B.Gain1[0] = 0.0;
    helicopter1_B.Gain1[1] = 0.0;
    helicopter1_B.Gain1[2] = 0.0;
    helicopter1_B.Gain1[3] = 0.0;
    helicopter1_B.Sum4 = 0.0;
    helicopter1_B.ElevationCounttorad = 0.0;
    helicopter1_B.Gain_e = 0.0;
    helicopter1_B.Sum = 0.0;
    helicopter1_B.Gain_dg = 0.0;
    helicopter1_B.Gain_l = 0.0;
    helicopter1_B.BackmotorSaturation = 0.0;
    helicopter1_B.FrontmotorSaturation = 0.0;
    helicopter1_B.In1 = 0.0;
  }

  /* parameters */
  helicopter1_M->defaultParam = ((real_T *)&helicopter1_P);

  /* states (continuous) */
  {
    real_T *x = (real_T *) &helicopter1_X;
    helicopter1_M->contStates = (x);
    (void) memset((void *)&helicopter1_X, 0,
                  sizeof(X_helicopter1_T));
  }

  /* states (dwork) */
  helicopter1_M->dwork = ((void *) &helicopter1_DW);
  (void) memset((void *)&helicopter1_DW, 0,
                sizeof(DW_helicopter1_T));

  {
    int32_T i;
    for (i = 0; i < 8; i++) {
      helicopter1_DW.HILInitialize_AIMinimums[i] = 0.0;
    }
  }

  {
    int32_T i;
    for (i = 0; i < 8; i++) {
      helicopter1_DW.HILInitialize_AIMaximums[i] = 0.0;
    }
  }

  {
    int32_T i;
    for (i = 0; i < 8; i++) {
      helicopter1_DW.HILInitialize_AOMinimums[i] = 0.0;
    }
  }

  {
    int32_T i;
    for (i = 0; i < 8; i++) {
      helicopter1_DW.HILInitialize_AOMaximums[i] = 0.0;
    }
  }

  {
    int32_T i;
    for (i = 0; i < 8; i++) {
      helicopter1_DW.HILInitialize_AOVoltages[i] = 0.0;
    }
  }

  {
    int32_T i;
    for (i = 0; i < 8; i++) {
      helicopter1_DW.HILInitialize_FilterFrequency[i] = 0.0;
    }
  }

  {
    int32_T i;
    for (i = 0; i < 8; i++) {
      helicopter1_DW.HILInitialize_POSortedFreqs[i] = 0.0;
    }
  }

  {
    int32_T i;
    for (i = 0; i < 8; i++) {
      helicopter1_DW.HILInitialize_POValues[i] = 0.0;
    }
  }

  helicopter1_DW.TimeStampA = 0.0;
  helicopter1_DW.LastUAtTimeA = 0.0;
  helicopter1_DW.TimeStampB = 0.0;
  helicopter1_DW.LastUAtTimeB = 0.0;
  helicopter1_DW.HILWriteAnalog_Buffer[0] = 0.0;
  helicopter1_DW.HILWriteAnalog_Buffer[1] = 0.0;

  /* data type transition information */
  {
    static DataTypeTransInfo dtInfo;
    (void) memset((char_T *) &dtInfo, 0,
                  sizeof(dtInfo));
    helicopter1_M->SpecialInfo.mappingInfo = (&dtInfo);
    dtInfo.numDataTypes = 16;
    dtInfo.dataTypeSizes = &rtDataTypeSizes[0];
    dtInfo.dataTypeNames = &rtDataTypeNames[0];

    /* Block I/O transition table */
    dtInfo.BTransTable = &rtBTransTable;

    /* Parameters transition table */
    dtInfo.PTransTable = &rtPTransTable;
  }

  /* Initialize Sizes */
  helicopter1_M->Sizes.numContStates = (4);/* Number of continuous states */
  helicopter1_M->Sizes.numPeriodicContStates = (0);
                                      /* Number of periodic continuous states */
  helicopter1_M->Sizes.numY = (0);     /* Number of model outputs */
  helicopter1_M->Sizes.numU = (0);     /* Number of model inputs */
  helicopter1_M->Sizes.sysDirFeedThru = (0);/* The model is not direct feedthrough */
  helicopter1_M->Sizes.numSampTimes = (2);/* Number of sample times */
  helicopter1_M->Sizes.numBlocks = (68);/* Number of blocks */
  helicopter1_M->Sizes.numBlockIO = (18);/* Number of block outputs */
  helicopter1_M->Sizes.numBlockPrms = (150);/* Sum of parameter "widths" */
  return helicopter1_M;
}

/*========================================================================*
 * End of Classic call interface                                          *
 *========================================================================*/
