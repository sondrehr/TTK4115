/*
 * heli_q8.c
 *
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * Code generation for model "heli_q8".
 *
 * Model version              : 1.84
 * Simulink Coder version : 8.9 (R2015b) 13-Aug-2015
 * C source code generated on : Tue Nov 17 14:52:55 2020
 *
 * Target selection: quarc_win64.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: 32-bit Generic
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "heli_q8.h"
#include "heli_q8_private.h"
#include "heli_q8_dt.h"

t_stream heli_q8_rtZt_stream = NULL;

/* Block signals (auto storage) */
B_heli_q8_T heli_q8_B;

/* Continuous states */
X_heli_q8_T heli_q8_X;

/* Block states (auto storage) */
DW_heli_q8_T heli_q8_DW;

/* Real-time model */
RT_MODEL_heli_q8_T heli_q8_M_;
RT_MODEL_heli_q8_T *const heli_q8_M = &heli_q8_M_;
static void rate_monotonic_scheduler(void);

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

time_T rt_SimUpdateDiscreteEvents(
  int_T rtmNumSampTimes, void *rtmTimingData, int_T *rtmSampleHitPtr, int_T
  *rtmPerTaskSampleHits )
{
  rtmSampleHitPtr[1] = rtmStepTask(heli_q8_M, 1);
  rtmSampleHitPtr[2] = rtmStepTask(heli_q8_M, 2);
  UNUSED_PARAMETER(rtmNumSampTimes);
  UNUSED_PARAMETER(rtmTimingData);
  UNUSED_PARAMETER(rtmPerTaskSampleHits);
  return(-1);
}

/*
 *   This function updates active task flag for each subrate
 * and rate transition flags for tasks that exchange data.
 * The function assumes rate-monotonic multitasking scheduler.
 * The function must be called at model base rate so that
 * the generated code self-manages all its subrates and rate
 * transition flags.
 */
static void rate_monotonic_scheduler(void)
{
  /* To ensure a deterministic data transfer between two rates,
   * data is transferred at the priority of a fast task and the frequency
   * of the slow task.  The following flags indicate when the data transfer
   * happens.  That is, a rate interaction flag is set true when both rates
   * will run, and false otherwise.
   */

  /* tid 1 shares data with slower tid rate: 2 */
  if (heli_q8_M->Timing.TaskCounters.TID[1] == 0) {
    heli_q8_M->Timing.RateInteraction.TID1_2 =
      (heli_q8_M->Timing.TaskCounters.TID[2] == 0);

    /* update PerTaskSampleHits matrix for non-inline sfcn */
    heli_q8_M->Timing.perTaskSampleHits[5] =
      heli_q8_M->Timing.RateInteraction.TID1_2;
  }

  /* Compute which subrates run during the next base time step.  Subrates
   * are an integer multiple of the base rate counter.  Therefore, the subtask
   * counter is reset when it reaches its limit (zero means run).
   */
  (heli_q8_M->Timing.TaskCounters.TID[2])++;
  if ((heli_q8_M->Timing.TaskCounters.TID[2]) > 4) {/* Sample time: [0.01s, 0.0s] */
    heli_q8_M->Timing.TaskCounters.TID[2] = 0;
  }
}

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
  int_T nXc = 10;
  rtsiSetSimTimeStep(si,MINOR_TIME_STEP);
  rtsiSetdX(si, f0);
  heli_q8_derivatives();
  rtsiSetT(si, tnew);
  for (i = 0; i < nXc; ++i) {
    x[i] += h * f0[i];
  }

  rtsiSetSimTimeStep(si,MAJOR_TIME_STEP);
}

/*
 * Output and update for atomic system:
 *    '<S4>/Gyro vector to [pitch rate, elevation rate, travle rate]'
 *    '<S4>/Gyro vector to [pitch rate, elevation rate, travle rate]1'
 */
void Gyrovectortopitchrateelevationr(const real_T rtu_gyro_vec[3], real_T
  rtu_euler_angles, real_T rtu_euler_angles_o, B_Gyrovectortopitchrateelevat_T
  *localB)
{
  real_T tmp[9];
  int32_T i;

  /* MATLAB Function 'Math logic/Gyro vector to [pitch rate, elevation rate, travle rate]': '<S6>:1' */
  /* '<S6>:1:3' */
  /* '<S6>:1:4' */
  /* psi = euler_angles(3); */
  /* '<S6>:1:8' */
  /* '<S6>:1:11' */
  tmp[0] = 1.0;

  /* SignalConversion: '<S6>/TmpSignal ConversionAt SFunction Inport2' */
  tmp[3] = sin(rtu_euler_angles) * tan(rtu_euler_angles_o);
  tmp[6] = cos(rtu_euler_angles) * tan(rtu_euler_angles_o);
  tmp[1] = 0.0;

  /* SignalConversion: '<S6>/TmpSignal ConversionAt SFunction Inport2' */
  tmp[4] = cos(rtu_euler_angles);
  tmp[7] = -sin(rtu_euler_angles);
  tmp[2] = 0.0;

  /* SignalConversion: '<S6>/TmpSignal ConversionAt SFunction Inport2' */
  tmp[5] = sin(rtu_euler_angles) / cos(rtu_euler_angles_o);
  tmp[8] = cos(rtu_euler_angles) / cos(rtu_euler_angles_o);
  for (i = 0; i < 3; i++) {
    localB->euler_rates[i] = 0.0;
    localB->euler_rates[i] += tmp[i] * rtu_gyro_vec[0];
    localB->euler_rates[i] += tmp[i + 3] * rtu_gyro_vec[1];
    localB->euler_rates[i] += tmp[i + 6] * rtu_gyro_vec[2];
  }
}

/* Model output function for TID0 */
void heli_q8_output0(void)             /* Sample time: [0.0s, 0.0s] */
{
  /* local block i/o variables */
  real_T rtb_Gain2[3];
  real_T rtb_Gain1[3];
  real_T rtb_HILReadEncoderTimebase_o1;
  real_T rtb_HILReadEncoderTimebase_o2;
  real_T rtb_TmpSignalConversionAtToFile[6];
  real_T rtb_TmpSignalConversionAtToFi_n[5];
  real_T rtb_TmpSignalConversionAtToF_nc[2];
  real_T rtb_Add_m;
  t_stream_ptr rtb_StreamCall1_o1;
  t_stream_ptr rtb_StreamFormattedWrite_o1;
  real32_T rtb_StreamRead1_o2[10];
  int32_T rtb_StreamFormattedWrite_o2;
  int32_T rtb_StreamCall1_o3;
  int32_T rtb_StreamRead1_o5;
  boolean_T rtb_StreamRead1_o3;
  real_T currentTime;
  real_T currentTime_0;
  real_T currentTime_1;
  real_T currentTime_2;
  real_T currentTime_3;
  real_T currentTime_4;
  real_T rtb_e_c_dot;
  real_T rtb_Sum[2];
  int32_T i;
  real_T tmp[5];
  real_T tmp_0[2];
  real_T tmp_1[2];
  real_T tmp_2[5];
  real_T tmp_3[5];
  real_T tmp_4[5];
  int32_T i_0;
  real_T tmp_5;
  if (rtmIsMajorTimeStep(heli_q8_M)) {
    /* set solver stop time */
    if (!(heli_q8_M->Timing.clockTick0+1)) {
      rtsiSetSolverStopTime(&heli_q8_M->solverInfo,
                            ((heli_q8_M->Timing.clockTickH0 + 1) *
        heli_q8_M->Timing.stepSize0 * 4294967296.0));
    } else {
      rtsiSetSolverStopTime(&heli_q8_M->solverInfo,
                            ((heli_q8_M->Timing.clockTick0 + 1) *
        heli_q8_M->Timing.stepSize0 + heli_q8_M->Timing.clockTickH0 *
        heli_q8_M->Timing.stepSize0 * 4294967296.0));
    }

    {                                  /* Sample time: [0.0s, 0.0s] */
      rate_monotonic_scheduler();
    }
  }                                    /* end MajorTimeStep */

  /* Update absolute time of base rate at minor time step */
  if (rtmIsMinorTimeStep(heli_q8_M)) {
    heli_q8_M->Timing.t[0] = rtsiGetT(&heli_q8_M->solverInfo);
  }

  if (rtmIsMajorTimeStep(heli_q8_M)) {
    /* S-Function (hil_read_encoder_timebase_block): '<S2>/HIL Read Encoder Timebase' */

    /* S-Function Block: heli_q8/Heli 3D/HIL Read Encoder Timebase (hil_read_encoder_timebase_block) */
    {
      t_error result;
      result = hil_task_read_encoder(heli_q8_DW.HILReadEncoderTimebase_Task, 1,
        &heli_q8_DW.HILReadEncoderTimebase_Buffer[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(heli_q8_M, _rt_error_message);
      } else {
        rtb_HILReadEncoderTimebase_o1 =
          heli_q8_DW.HILReadEncoderTimebase_Buffer[0];
        rtb_HILReadEncoderTimebase_o2 =
          heli_q8_DW.HILReadEncoderTimebase_Buffer[1];
        rtb_Add_m = heli_q8_DW.HILReadEncoderTimebase_Buffer[2];
      }
    }
  }

  /* Integrator: '<S3>/Integrator2' */
  for (i = 0; i < 5; i++) {
    heli_q8_B.Integrator2[i] = heli_q8_X.Integrator2_CSTATE[i];
  }

  /* End of Integrator: '<S3>/Integrator2' */
  if (rtmIsMajorTimeStep(heli_q8_M)) {
    /* Gain: '<S2>/Pitch: Count to rad' */
    heli_q8_B.PitchCounttorad = heli_q8_P.PitchCounttorad_Gain *
      rtb_HILReadEncoderTimebase_o2;

    /* Gain: '<S2>/Elevation: Count to rad' */
    heli_q8_B.ElevationCounttorad = heli_q8_P.ElevationCounttorad_Gain *
      rtb_Add_m;

    /* Sum: '<Root>/Sum1' incorporates:
     *  Constant: '<Root>/Constant1'
     */
    heli_q8_B.Sum1 = heli_q8_B.ElevationCounttorad - heli_q8_P.Constant1_Value;
  }

  /* TransferFcn: '<S2>/Pitch: Transfer Fcn' */
  heli_q8_B.PitchTransferFcn = 0.0;
  heli_q8_B.PitchTransferFcn += heli_q8_P.PitchTransferFcn_C *
    heli_q8_X.PitchTransferFcn_CSTATE;
  heli_q8_B.PitchTransferFcn += heli_q8_P.PitchTransferFcn_D *
    heli_q8_B.PitchCounttorad;

  /* TransferFcn: '<S2>/Elevation: Transfer Fcn' */
  heli_q8_B.ElevationTransferFcn = 0.0;
  heli_q8_B.ElevationTransferFcn += heli_q8_P.ElevationTransferFcn_C *
    heli_q8_X.ElevationTransferFcn_CSTATE;
  heli_q8_B.ElevationTransferFcn += heli_q8_P.ElevationTransferFcn_D *
    heli_q8_B.ElevationCounttorad;
  if (rtmIsMajorTimeStep(heli_q8_M)) {
    /* Gain: '<S2>/Travel: Count to rad' */
    heli_q8_B.TravelCounttorad = heli_q8_P.TravelCounttorad_Gain *
      rtb_HILReadEncoderTimebase_o1;
  }

  /* TransferFcn: '<S2>/Travel: Transfer Fcn' */
  heli_q8_B.TravelTransferFcn = 0.0;
  heli_q8_B.TravelTransferFcn += heli_q8_P.TravelTransferFcn_C *
    heli_q8_X.TravelTransferFcn_CSTATE;
  heli_q8_B.TravelTransferFcn += heli_q8_P.TravelTransferFcn_D *
    heli_q8_B.TravelCounttorad;

  /* ManualSwitch: '<Root>/Manual Switch2' */
  if (heli_q8_P.ManualSwitch2_CurrentSetting == 1) {
    heli_q8_B.ManualSwitch2[0] = heli_q8_B.Integrator2[0];
    heli_q8_B.ManualSwitch2[1] = heli_q8_B.Integrator2[1];
    heli_q8_B.ManualSwitch2[2] = heli_q8_B.Integrator2[2];
    heli_q8_B.ManualSwitch2[3] = heli_q8_B.Integrator2[3];
    heli_q8_B.ManualSwitch2[4] = heli_q8_B.Integrator2[4];
  } else {
    heli_q8_B.ManualSwitch2[0] = heli_q8_B.PitchCounttorad;
    heli_q8_B.ManualSwitch2[1] = heli_q8_B.PitchTransferFcn;
    heli_q8_B.ManualSwitch2[2] = heli_q8_B.Sum1;
    heli_q8_B.ManualSwitch2[3] = heli_q8_B.ElevationTransferFcn;
    heli_q8_B.ManualSwitch2[4] = heli_q8_B.TravelTransferFcn;
  }

  /* End of ManualSwitch: '<Root>/Manual Switch2' */

  /* RateTransition: '<S10>/Rate Transition: x' incorporates:
   *  Constant: '<Root>/Constant'
   */
  if (rtmIsMajorTimeStep(heli_q8_M)) {
    /* SignalConversion: '<Root>/TmpSignal ConversionAtTo File3Inport1' */
    rtb_TmpSignalConversionAtToFile[0] = heli_q8_B.TravelCounttorad;
    rtb_TmpSignalConversionAtToFile[1] = heli_q8_B.TravelTransferFcn;
    rtb_TmpSignalConversionAtToFile[2] = heli_q8_B.PitchCounttorad;
    rtb_TmpSignalConversionAtToFile[3] = heli_q8_B.PitchTransferFcn;
    rtb_TmpSignalConversionAtToFile[4] = heli_q8_B.Sum1;
    rtb_TmpSignalConversionAtToFile[5] = heli_q8_B.ElevationTransferFcn;

    /* ToFile: '<Root>/To File3' */
    if (rtmIsMajorTimeStep(heli_q8_M)) {
      {
        if (!(++heli_q8_DW.ToFile3_IWORK.Decimation % 1) &&
            (heli_q8_DW.ToFile3_IWORK.Count*7)+1 < 100000000 ) {
          FILE *fp = (FILE *) heli_q8_DW.ToFile3_PWORK.FilePtr;
          if (fp != (NULL)) {
            real_T u[7];
            heli_q8_DW.ToFile3_IWORK.Decimation = 0;
            u[0] = heli_q8_M->Timing.t[1];
            u[1] = rtb_TmpSignalConversionAtToFile[0];
            u[2] = rtb_TmpSignalConversionAtToFile[1];
            u[3] = rtb_TmpSignalConversionAtToFile[2];
            u[4] = rtb_TmpSignalConversionAtToFile[3];
            u[5] = rtb_TmpSignalConversionAtToFile[4];
            u[6] = rtb_TmpSignalConversionAtToFile[5];
            if (fwrite(u, sizeof(real_T), 7, fp) != 7) {
              rtmSetErrorStatus(heli_q8_M,
                                "Error writing to MAT-file Encoder.mat");
              return;
            }

            if (((++heli_q8_DW.ToFile3_IWORK.Count)*7)+1 >= 100000000) {
              (void)fprintf(stdout,
                            "*** The ToFile block will stop logging data before\n"
                            "    the simulation has ended, because it has reached\n"
                            "    the maximum number of elements (100000000)\n"
                            "    allowed in MAT-file Encoder.mat.\n");
            }
          }
        }
      }
    }

    heli_q8_B.Constant = heli_q8_P.V_0;
    if (heli_q8_M->Timing.RateInteraction.TID1_2) {
      heli_q8_B.RateTransitionx = heli_q8_DW.RateTransitionx_Buffer0;
    }

    /* DeadZone: '<S10>/Dead Zone: x' incorporates:
     *  Constant: '<Root>/Constant'
     */
    if (heli_q8_B.RateTransitionx > heli_q8_P.DeadZonex_End) {
      rtb_Add_m = heli_q8_B.RateTransitionx - heli_q8_P.DeadZonex_End;
    } else if (heli_q8_B.RateTransitionx >= heli_q8_P.DeadZonex_Start) {
      rtb_Add_m = 0.0;
    } else {
      rtb_Add_m = heli_q8_B.RateTransitionx - heli_q8_P.DeadZonex_Start;
    }

    /* End of DeadZone: '<S10>/Dead Zone: x' */

    /* Gain: '<S10>/Joystick_gain_x' incorporates:
     *  Gain: '<S10>/Gain: x'
     */
    heli_q8_B.Joystick_gain_x = heli_q8_P.Gainx_Gain * rtb_Add_m *
      heli_q8_P.Joystick_gain_x;
  }

  /* End of RateTransition: '<S10>/Rate Transition: x' */

  /* Step: '<S11>/Step1' */
  rtb_e_c_dot = heli_q8_M->Timing.t[0];

  /* Step: '<S11>/Step2' */
  currentTime = heli_q8_M->Timing.t[0];

  /* Step: '<S11>/Step3' */
  currentTime_0 = heli_q8_M->Timing.t[0];

  /* Step: '<S11>/Step4' */
  currentTime_1 = heli_q8_M->Timing.t[0];

  /* Step: '<S11>/Step5' */
  currentTime_2 = heli_q8_M->Timing.t[0];

  /* Step: '<S11>/Step6' */
  currentTime_3 = heli_q8_M->Timing.t[0];

  /* Step: '<S11>/Step7' */
  currentTime_4 = heli_q8_M->Timing.t[0];

  /* ManualSwitch: '<S5>/Manual Switch' incorporates:
   *  Gain: '<S5>/Gain3'
   *  Sum: '<S11>/Sum1'
   *  Sum: '<S11>/Sum2'
   *  Sum: '<S11>/Sum3'
   *  Sum: '<S11>/Sum4'
   *  Sum: '<S11>/Sum5'
   *  Sum: '<S11>/Sum6'
   *  Sum: '<S11>/Sum7'
   */
  if (heli_q8_P.ManualSwitch_CurrentSetting == 1) {
    /* Step: '<S11>/Step' */
    if (heli_q8_M->Timing.t[0] < heli_q8_P.Step_Time) {
      tmp_5 = heli_q8_P.Step_Y0;
    } else {
      tmp_5 = heli_q8_P.Step_YFinal;
    }

    /* End of Step: '<S11>/Step' */

    /* Step: '<S11>/Step1' */
    if (rtb_e_c_dot < heli_q8_P.Step1_Time) {
      rtb_e_c_dot = heli_q8_P.Step1_Y0;
    } else {
      rtb_e_c_dot = heli_q8_P.Step1_YFinal;
    }

    /* Step: '<S11>/Step2' */
    if (currentTime < heli_q8_P.Step2_Time) {
      currentTime = heli_q8_P.Step2_Y0;
    } else {
      currentTime = heli_q8_P.Step2_YFinal;
    }

    /* Step: '<S11>/Step3' */
    if (currentTime_0 < heli_q8_P.Step3_Time) {
      currentTime_0 = heli_q8_P.Step3_Y0;
    } else {
      currentTime_0 = heli_q8_P.Step3_YFinal;
    }

    /* Step: '<S11>/Step4' */
    if (currentTime_1 < heli_q8_P.Step4_Time) {
      currentTime_1 = heli_q8_P.Step4_Y0;
    } else {
      currentTime_1 = heli_q8_P.Step4_YFinal;
    }

    /* Step: '<S11>/Step5' */
    if (currentTime_2 < heli_q8_P.Step5_Time) {
      currentTime_2 = heli_q8_P.Step5_Y0;
    } else {
      currentTime_2 = heli_q8_P.Step5_YFinal;
    }

    /* Step: '<S11>/Step6' */
    if (currentTime_3 < heli_q8_P.Step6_Time) {
      currentTime_3 = heli_q8_P.Step6_Y0;
    } else {
      currentTime_3 = heli_q8_P.Step6_YFinal;
    }

    /* Step: '<S11>/Step7' */
    if (currentTime_4 < heli_q8_P.Step7_Time) {
      currentTime_4 = heli_q8_P.Step7_Y0;
    } else {
      currentTime_4 = heli_q8_P.Step7_YFinal;
    }

    heli_q8_B.ManualSwitch = ((((0.0 - currentTime) - currentTime_0) + (tmp_5 +
      rtb_e_c_dot)) - ((currentTime_1 - currentTime_2) + (currentTime_3 -
      currentTime_4))) * heli_q8_P.Gain3_Gain;
  } else {
    heli_q8_B.ManualSwitch = heli_q8_B.Joystick_gain_x;
  }

  /* End of ManualSwitch: '<S5>/Manual Switch' */
  if (rtmIsMajorTimeStep(heli_q8_M)) {
    /* DiscretePulseGenerator: '<S5>/e_c_dot' */
    rtb_e_c_dot = (heli_q8_DW.clockTickCounter < heli_q8_P.e_c_dot_Duty) &&
      (heli_q8_DW.clockTickCounter >= 0) ? heli_q8_P.e_c_dot_Amp : 0.0;
    if (heli_q8_DW.clockTickCounter >= heli_q8_P.e_c_dot_Period - 1.0) {
      heli_q8_DW.clockTickCounter = 0;
    } else {
      heli_q8_DW.clockTickCounter++;
    }

    /* End of DiscretePulseGenerator: '<S5>/e_c_dot' */

    /* RateTransition: '<S10>/Rate Transition: y' */
    if (heli_q8_M->Timing.RateInteraction.TID1_2) {
      heli_q8_B.RateTransitiony = heli_q8_DW.RateTransitiony_Buffer0;
    }

    /* End of RateTransition: '<S10>/Rate Transition: y' */

    /* DeadZone: '<S10>/Dead Zone: y' */
    if (heli_q8_B.RateTransitiony > heli_q8_P.DeadZoney_End) {
      rtb_Add_m = heli_q8_B.RateTransitiony - heli_q8_P.DeadZoney_End;
    } else if (heli_q8_B.RateTransitiony >= heli_q8_P.DeadZoney_Start) {
      rtb_Add_m = 0.0;
    } else {
      rtb_Add_m = heli_q8_B.RateTransitiony - heli_q8_P.DeadZoney_Start;
    }

    /* End of DeadZone: '<S10>/Dead Zone: y' */

    /* Gain: '<S10>/Joystick_gain_y' incorporates:
     *  Gain: '<S10>/Gain: y'
     */
    heli_q8_B.Joystick_gain_y = heli_q8_P.Gainy_Gain * rtb_Add_m *
      heli_q8_P.Joystick_gain_y;

    /* ManualSwitch: '<S5>/Manual Switch1' incorporates:
     *  Gain: '<S5>/Gain5'
     */
    if (heli_q8_P.ManualSwitch1_CurrentSetting == 1) {
      heli_q8_B.ManualSwitch1 = heli_q8_P.Gain5_Gain * rtb_e_c_dot;
    } else {
      heli_q8_B.ManualSwitch1 = heli_q8_B.Joystick_gain_y;
    }

    /* End of ManualSwitch: '<S5>/Manual Switch1' */
  }

  /* SignalConversion: '<Root>/TmpSignal ConversionAtGain1Inport1' incorporates:
   *  Gain: '<Root>/Gain1'
   *  Integrator: '<Root>/Integrator'
   *  Integrator: '<Root>/Integrator1'
   */
  tmp[2] = heli_q8_B.ManualSwitch2[3];
  tmp[3] = heli_q8_X.Integrator_CSTATE;
  tmp[4] = heli_q8_X.Integrator1_CSTATE;
  tmp[0] = heli_q8_B.ManualSwitch2[0];

  /* Gain: '<Root>/Gain2' incorporates:
   *  SignalConversion: '<Root>/TmpSignal ConversionAtGain2Inport1'
   *  Sum: '<Root>/Sum'
   */
  tmp_0[0] = heli_q8_P.F[0] * heli_q8_B.ManualSwitch + heli_q8_P.F[2] *
    heli_q8_B.ManualSwitch1;

  /* SignalConversion: '<Root>/TmpSignal ConversionAtGain1Inport1' incorporates:
   *  Gain: '<Root>/Gain1'
   */
  tmp[1] = heli_q8_B.ManualSwitch2[1];

  /* Gain: '<Root>/Gain2' incorporates:
   *  SignalConversion: '<Root>/TmpSignal ConversionAtGain2Inport1'
   *  Sum: '<Root>/Sum'
   */
  tmp_0[1] = heli_q8_P.F[1] * heli_q8_B.ManualSwitch;
  tmp_0[1] += heli_q8_P.F[3] * heli_q8_B.ManualSwitch1;
  for (i = 0; i < 2; i++) {
    /* Gain: '<Root>/Gain1' incorporates:
     *  Sum: '<Root>/Sum'
     */
    tmp_1[i] = 0.0;
    for (i_0 = 0; i_0 < 5; i_0++) {
      tmp_1[i] += heli_q8_P.K[(i_0 << 1) + i] * tmp[i_0];
    }

    /* Sum: '<Root>/Sum' */
    rtb_Sum[i] = tmp_0[i] - tmp_1[i];
  }

  /* Sum: '<Root>/Sum2' */
  rtb_e_c_dot = rtb_Sum[0] + heli_q8_B.Constant;
  if (rtmIsMajorTimeStep(heli_q8_M)) {
  }

  /* Gain: '<S1>/Front gain' incorporates:
   *  Sum: '<S1>/Add'
   */
  currentTime = (rtb_e_c_dot - rtb_Sum[1]) * heli_q8_P.Frontgain_Gain;

  /* Saturate: '<S2>/Front motor: Saturation' */
  if (currentTime > heli_q8_P.FrontmotorSaturation_UpperSat) {
    heli_q8_B.FrontmotorSaturation = heli_q8_P.FrontmotorSaturation_UpperSat;
  } else if (currentTime < heli_q8_P.FrontmotorSaturation_LowerSat) {
    heli_q8_B.FrontmotorSaturation = heli_q8_P.FrontmotorSaturation_LowerSat;
  } else {
    heli_q8_B.FrontmotorSaturation = currentTime;
  }

  /* End of Saturate: '<S2>/Front motor: Saturation' */

  /* Gain: '<S1>/Back gain' incorporates:
   *  Sum: '<S1>/Subtract'
   */
  currentTime = (rtb_e_c_dot + rtb_Sum[1]) * heli_q8_P.Backgain_Gain;

  /* Saturate: '<S2>/Back motor: Saturation' */
  if (currentTime > heli_q8_P.BackmotorSaturation_UpperSat) {
    heli_q8_B.BackmotorSaturation = heli_q8_P.BackmotorSaturation_UpperSat;
  } else if (currentTime < heli_q8_P.BackmotorSaturation_LowerSat) {
    heli_q8_B.BackmotorSaturation = heli_q8_P.BackmotorSaturation_LowerSat;
  } else {
    heli_q8_B.BackmotorSaturation = currentTime;
  }

  /* End of Saturate: '<S2>/Back motor: Saturation' */
  if (rtmIsMajorTimeStep(heli_q8_M)) {
    /* S-Function (hil_write_analog_block): '<S2>/HIL Write Analog' */

    /* S-Function Block: heli_q8/Heli 3D/HIL Write Analog (hil_write_analog_block) */
    {
      t_error result;
      heli_q8_DW.HILWriteAnalog_Buffer[0] = heli_q8_B.FrontmotorSaturation;
      heli_q8_DW.HILWriteAnalog_Buffer[1] = heli_q8_B.BackmotorSaturation;
      result = hil_write_analog(heli_q8_DW.HILInitialize_Card,
        heli_q8_P.HILWriteAnalog_channels, 2, &heli_q8_DW.HILWriteAnalog_Buffer
        [0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(heli_q8_M, _rt_error_message);
      }
    }

    /* ToFile: '<S3>/To File2' */
    if (rtmIsMajorTimeStep(heli_q8_M)) {
      {
        if (!(++heli_q8_DW.ToFile2_IWORK.Decimation % 1) &&
            (heli_q8_DW.ToFile2_IWORK.Count*6)+1 < 100000000 ) {
          FILE *fp = (FILE *) heli_q8_DW.ToFile2_PWORK.FilePtr;
          if (fp != (NULL)) {
            real_T u[6];
            heli_q8_DW.ToFile2_IWORK.Decimation = 0;
            u[0] = heli_q8_M->Timing.t[1];
            u[1] = heli_q8_B.Integrator2[0];
            u[2] = heli_q8_B.Integrator2[1];
            u[3] = heli_q8_B.Integrator2[2];
            u[4] = heli_q8_B.Integrator2[3];
            u[5] = heli_q8_B.Integrator2[4];
            if (fwrite(u, sizeof(real_T), 6, fp) != 6) {
              rtmSetErrorStatus(heli_q8_M,
                                "Error writing to MAT-file Estimators.mat");
              return;
            }

            if (((++heli_q8_DW.ToFile2_IWORK.Count)*6)+1 >= 100000000) {
              (void)fprintf(stdout,
                            "*** The ToFile block will stop logging data before\n"
                            "    the simulation has ended, because it has reached\n"
                            "    the maximum number of elements (100000000)\n"
                            "    allowed in MAT-file Estimators.mat.\n");
            }
          }
        }
      }
    }

    /* S-Function (stream_call_block): '<S8>/Stream Call1' */

    /* S-Function Block: heli_q8/Math logic/IMU/Stream Call1 (stream_call_block) */
    {
      t_error result = 0;
      t_boolean close_flag = (heli_q8_P.Constant_Value != 0);
      rtb_StreamCall1_o1 = NULL;
      switch (heli_q8_DW.StreamCall1_State) {
       case STREAM_CALL_STATE_NOT_CONNECTED:
        {
          if (!close_flag) {
            /* Make sure URI is null-terminated */
            if (string_length((char *) heli_q8_P.StringConstant_Value, 255) ==
                255) {
              rtmSetErrorStatus(heli_q8_M,
                                "URI passed to Stream Call block is not null-terminated!");
              result = -QERR_STRING_NOT_TERMINATED;
            } else {
              result = stream_connect((char *) heli_q8_P.StringConstant_Value,
                true, heli_q8_P.StreamCall1_SendBufferSize,
                heli_q8_P.StreamCall1_ReceiveBufferSize,
                &heli_q8_DW.StreamCall1_Stream);
              if (result == 0) {
                heli_q8_DW.StreamCall1_State = STREAM_CALL_STATE_CONNECTED;
                stream_set_byte_order(heli_q8_DW.StreamCall1_Stream,
                                      (t_stream_byte_order)
                                      heli_q8_P.StreamCall1_Endian);
                rtb_StreamCall1_o1 = &heli_q8_DW.StreamCall1_Stream;
              } else if (result == -QERR_WOULD_BLOCK) {
                heli_q8_DW.StreamCall1_State = STREAM_CALL_STATE_CONNECTING;
                result = 0;
              }
            }
          }
          break;
        }

       case STREAM_CALL_STATE_CONNECTING:
        {
          if (!close_flag) {
            const t_timeout timeout = { 0, 0, false };/* zero seconds */

            result = stream_poll(heli_q8_DW.StreamCall1_Stream, &timeout,
                                 STREAM_POLL_CONNECT);
            if (result > 0) {
              heli_q8_DW.StreamCall1_State = STREAM_CALL_STATE_CONNECTED;
              stream_set_byte_order(heli_q8_DW.StreamCall1_Stream,
                                    (t_stream_byte_order)
                                    heli_q8_P.StreamCall1_Endian);
              rtb_StreamCall1_o1 = &heli_q8_DW.StreamCall1_Stream;
              result = 0;
              break;
            } else if (result == 0) {
              break;
            }
          }

          /* Fall through deliberately */
        }

       case STREAM_CALL_STATE_CONNECTED:
        {
          rtb_StreamCall1_o1 = &heli_q8_DW.StreamCall1_Stream;
          if (!close_flag) {
            break;
          }

          /* Fall through deliberately */
        }

       default:
        {
          t_error close_result = stream_close(heli_q8_DW.StreamCall1_Stream);
          if (close_result == 0) {
            heli_q8_DW.StreamCall1_State = STREAM_CALL_STATE_NOT_CONNECTED;
            heli_q8_DW.StreamCall1_Stream = NULL;
            rtb_StreamCall1_o1 = NULL;
          } else if (result == 0) {
            result = close_result;
          }
          break;
        }
      }

      heli_q8_B.StreamCall1_o2 = heli_q8_DW.StreamCall1_State;
      rtb_StreamCall1_o3 = (int32_T) result;
    }

    /* S-Function (stream_formatted_write_block): '<S8>/Stream Formatted Write' */
    {
      t_error result;
      if (rtb_StreamCall1_o1 != NULL) {
        result = stream_print_utf8_char_array(*rtb_StreamCall1_o1,
          heli_q8_P.StreamFormattedWrite_MaxUnits, &rtb_StreamFormattedWrite_o2,
          "%c\n"
          , (char) heli_q8_P.Constant1_Value_e
          );
        if (result > 0) {
          result = stream_flush(*rtb_StreamCall1_o1);
        }

        if (result == -QERR_WOULD_BLOCK) {
          result = 0;
        }
      }

      rtb_StreamFormattedWrite_o1 = rtb_StreamCall1_o1;
    }

    /* S-Function (stream_read_block): '<S8>/Stream Read1' */
    /* S-Function Block: heli_q8/Math logic/IMU/Stream Read1 (stream_read_block) */
    {
      t_error result;
      memset(&rtb_StreamRead1_o2[0], 0, 10 * sizeof(real32_T));
      if (rtb_StreamFormattedWrite_o1 != NULL) {
        result = stream_receive_unit_array(*rtb_StreamFormattedWrite_o1,
          &rtb_StreamRead1_o2[0], sizeof(real32_T), 10);
        rtb_StreamRead1_o3 = (result > 0);
        if (result > 0 || result == -QERR_WOULD_BLOCK) {
          result = 0;
        }
      } else {
        rtb_StreamRead1_o3 = false;
        result = 0;
      }

      rtb_StreamRead1_o5 = (int32_T) result;
    }

    /* Switch: '<S8>/Switch' incorporates:
     *  DataTypeConversion: '<S8>/Data Type Conversion'
     *  Memory: '<S8>/Memory'
     */
    for (i = 0; i < 10; i++) {
      if (rtb_StreamRead1_o3) {
        heli_q8_B.Switch[i] = rtb_StreamRead1_o2[i];
      } else {
        heli_q8_B.Switch[i] = heli_q8_DW.Memory_PreviousInput[i];
      }
    }

    /* End of Switch: '<S8>/Switch' */

    /* Gain: '<S8>/Gain2' */
    for (i = 0; i < 3; i++) {
      rtb_Gain2[i] = 0.0;
      rtb_Gain2[i] += heli_q8_P.Gain2_Gain[i] * heli_q8_B.Switch[0];
      rtb_Gain2[i] += heli_q8_P.Gain2_Gain[i + 3] * heli_q8_B.Switch[1];
      rtb_Gain2[i] += heli_q8_P.Gain2_Gain[i + 6] * heli_q8_B.Switch[2];
    }

    /* End of Gain: '<S8>/Gain2' */

    /* Switch: '<S9>/Switch1' incorporates:
     *  Constant: '<S9>/Constant2'
     *  Product: '<S9>/Divide'
     *  Trigonometry: '<S9>/Trigonometric Function'
     */
    if (rtb_Gain2[2] != 0.0) {
      heli_q8_B.Switch1 = atan(rtb_Gain2[1] / rtb_Gain2[2]);
    } else {
      heli_q8_B.Switch1 = heli_q8_P.Constant2_Value;
    }

    /* End of Switch: '<S9>/Switch1' */

    /* Gain: '<S8>/Gain1' */
    for (i = 0; i < 3; i++) {
      rtb_Gain1[i] = 0.0;
      rtb_Gain1[i] += heli_q8_P.Gain1_Gain[i] * heli_q8_B.Switch[3];
      rtb_Gain1[i] += heli_q8_P.Gain1_Gain[i + 3] * heli_q8_B.Switch[4];
      rtb_Gain1[i] += heli_q8_P.Gain1_Gain[i + 6] * heli_q8_B.Switch[5];
    }

    /* End of Gain: '<S8>/Gain1' */

    /* MATLAB Function: '<S4>/Gyro vector to [pitch rate, elevation rate, travle rate]' incorporates:
     *  Constant: '<S4>/Constant2'
     */
    Gyrovectortopitchrateelevationr(rtb_Gain1, heli_q8_B.PitchCounttorad,
      heli_q8_B.Sum1, &heli_q8_B.sf_Gyrovectortopitchrateelevati);

    /* Sum: '<S9>/Add' incorporates:
     *  Math: '<S9>/Math Function'
     *  Math: '<S9>/Math Function1'
     */
    rtb_Add_m = rtb_Gain2[1] * rtb_Gain2[1] + rtb_Gain2[2] * rtb_Gain2[2];

    /* Sqrt: '<S9>/Sqrt' */
    rtb_e_c_dot = sqrt(rtb_Add_m);

    /* Switch: '<S9>/Switch2' incorporates:
     *  Constant: '<S9>/Constant3'
     *  Product: '<S9>/Divide1'
     *  Trigonometry: '<S9>/Trigonometric Function1'
     */
    if (rtb_e_c_dot != 0.0) {
      heli_q8_B.Switch2 = atan(rtb_Gain2[0] / rtb_e_c_dot);
    } else {
      heli_q8_B.Switch2 = heli_q8_P.Constant3_Value;
    }

    /* End of Switch: '<S9>/Switch2' */

    /* MATLAB Function: '<S4>/Gyro vector to [pitch rate, elevation rate, travle rate]1' incorporates:
     *  Constant: '<S4>/Constant3'
     */
    Gyrovectortopitchrateelevationr(rtb_Gain1, heli_q8_B.Switch1,
      heli_q8_B.Switch2, &heli_q8_B.sf_Gyrovectortopitchrateeleva_f);

    /* ManualSwitch: '<S4>/Manual Switch' */
    if (heli_q8_P.ManualSwitch_CurrentSetting_o == 1) {
      heli_q8_B.ManualSwitch_k[0] =
        heli_q8_B.sf_Gyrovectortopitchrateelevati.euler_rates[0];
      heli_q8_B.ManualSwitch_k[1] =
        heli_q8_B.sf_Gyrovectortopitchrateelevati.euler_rates[1];
      heli_q8_B.ManualSwitch_k[2] =
        heli_q8_B.sf_Gyrovectortopitchrateelevati.euler_rates[2];
    } else {
      heli_q8_B.ManualSwitch_k[0] =
        heli_q8_B.sf_Gyrovectortopitchrateeleva_f.euler_rates[0];
      heli_q8_B.ManualSwitch_k[1] =
        heli_q8_B.sf_Gyrovectortopitchrateeleva_f.euler_rates[1];
      heli_q8_B.ManualSwitch_k[2] =
        heli_q8_B.sf_Gyrovectortopitchrateeleva_f.euler_rates[2];
    }

    /* End of ManualSwitch: '<S4>/Manual Switch' */
  }

  /* Sum: '<S3>/Sum6' */
  tmp_3[0] = heli_q8_B.Switch1;
  tmp_3[1] = heli_q8_B.ManualSwitch_k[0];
  tmp_3[2] = heli_q8_B.Switch2;
  tmp_3[3] = heli_q8_B.ManualSwitch_k[1];
  tmp_3[4] = heli_q8_B.ManualSwitch_k[2];
  for (i = 0; i < 5; i++) {
    /* Gain: '<S3>/Gain6' incorporates:
     *  Sum: '<S3>/Sum5'
     */
    tmp[i] = 0.0;
    for (i_0 = 0; i_0 < 5; i_0++) {
      tmp[i] += heli_q8_P.A_2[5 * i_0 + i] * heli_q8_B.Integrator2[i_0];
    }

    /* End of Gain: '<S3>/Gain6' */

    /* Gain: '<S3>/Gain' incorporates:
     *  Sum: '<S3>/Sum5'
     */
    tmp_2[i] = 0.0;
    tmp_2[i] += heli_q8_P.B_2[i] * rtb_Sum[0];
    tmp_2[i] += heli_q8_P.B_2[i + 5] * rtb_Sum[1];

    /* Sum: '<S3>/Sum6' incorporates:
     *  Gain: '<S3>/Gain4'
     */
    tmp_4[i] = tmp_3[i] - heli_q8_B.Integrator2[i];
  }

  /* Sum: '<S3>/Sum5' incorporates:
   *  Gain: '<S3>/Gain4'
   */
  for (i = 0; i < 5; i++) {
    tmp_5 = 0.0;
    for (i_0 = 0; i_0 < 5; i_0++) {
      tmp_5 += heli_q8_P.Gain4_Gain[5 * i_0 + i] * tmp_4[i_0];
    }

    heli_q8_B.Sum5[i] = (tmp[i] + tmp_2[i]) + tmp_5;
  }

  if (rtmIsMajorTimeStep(heli_q8_M)) {
    /* SignalConversion: '<S4>/TmpSignal ConversionAtTo File1Inport1' */
    rtb_TmpSignalConversionAtToF_nc[0] = heli_q8_B.Switch1;
    rtb_TmpSignalConversionAtToF_nc[1] = heli_q8_B.Switch2;

    /* ToFile: '<S4>/To File1' */
    if (rtmIsMajorTimeStep(heli_q8_M)) {
      {
        if (!(++heli_q8_DW.ToFile1_IWORK.Decimation % 1) &&
            (heli_q8_DW.ToFile1_IWORK.Count*3)+1 < 100000000 ) {
          FILE *fp = (FILE *) heli_q8_DW.ToFile1_PWORK.FilePtr;
          if (fp != (NULL)) {
            real_T u[3];
            heli_q8_DW.ToFile1_IWORK.Decimation = 0;
            u[0] = heli_q8_M->Timing.t[1];
            u[1] = rtb_TmpSignalConversionAtToF_nc[0];
            u[2] = rtb_TmpSignalConversionAtToF_nc[1];
            if (fwrite(u, sizeof(real_T), 3, fp) != 3) {
              rtmSetErrorStatus(heli_q8_M,
                                "Error writing to MAT-file AngleTF.mat");
              return;
            }

            if (((++heli_q8_DW.ToFile1_IWORK.Count)*3)+1 >= 100000000) {
              (void)fprintf(stdout,
                            "*** The ToFile block will stop logging data before\n"
                            "    the simulation has ended, because it has reached\n"
                            "    the maximum number of elements (100000000)\n"
                            "    allowed in MAT-file AngleTF.mat.\n");
            }
          }
        }
      }
    }

    /* ToFile: '<S4>/To File4' */
    if (rtmIsMajorTimeStep(heli_q8_M)) {
      {
        if (!(++heli_q8_DW.ToFile4_IWORK.Decimation % 1) &&
            (heli_q8_DW.ToFile4_IWORK.Count*4)+1 < 100000000 ) {
          FILE *fp = (FILE *) heli_q8_DW.ToFile4_PWORK.FilePtr;
          if (fp != (NULL)) {
            real_T u[4];
            heli_q8_DW.ToFile4_IWORK.Decimation = 0;
            u[0] = heli_q8_M->Timing.t[1];
            u[1] = rtb_Gain2[0];
            u[2] = rtb_Gain2[1];
            u[3] = rtb_Gain2[2];
            if (fwrite(u, sizeof(real_T), 4, fp) != 4) {
              rtmSetErrorStatus(heli_q8_M,
                                "Error writing to MAT-file eulerAngles.mat");
              return;
            }

            if (((++heli_q8_DW.ToFile4_IWORK.Count)*4)+1 >= 100000000) {
              (void)fprintf(stdout,
                            "*** The ToFile block will stop logging data before\n"
                            "    the simulation has ended, because it has reached\n"
                            "    the maximum number of elements (100000000)\n"
                            "    allowed in MAT-file eulerAngles.mat.\n");
            }
          }
        }
      }
    }

    /* ToFile: '<S4>/To File5' */
    if (rtmIsMajorTimeStep(heli_q8_M)) {
      {
        if (!(++heli_q8_DW.ToFile5_IWORK.Decimation % 1) &&
            (heli_q8_DW.ToFile5_IWORK.Count*4)+1 < 100000000 ) {
          FILE *fp = (FILE *) heli_q8_DW.ToFile5_PWORK.FilePtr;
          if (fp != (NULL)) {
            real_T u[4];
            heli_q8_DW.ToFile5_IWORK.Decimation = 0;
            u[0] = heli_q8_M->Timing.t[1];
            u[1] = rtb_Gain1[0];
            u[2] = rtb_Gain1[1];
            u[3] = rtb_Gain1[2];
            if (fwrite(u, sizeof(real_T), 4, fp) != 4) {
              rtmSetErrorStatus(heli_q8_M, "Error writing to MAT-file Gyro.mat");
              return;
            }

            if (((++heli_q8_DW.ToFile5_IWORK.Count)*4)+1 >= 100000000) {
              (void)fprintf(stdout,
                            "*** The ToFile block will stop logging data before\n"
                            "    the simulation has ended, because it has reached\n"
                            "    the maximum number of elements (100000000)\n"
                            "    allowed in MAT-file Gyro.mat.\n");
            }
          }
        }
      }
    }

    /* ToFile: '<S4>/To File6' */
    if (rtmIsMajorTimeStep(heli_q8_M)) {
      {
        if (!(++heli_q8_DW.ToFile6_IWORK.Decimation % 1) &&
            (heli_q8_DW.ToFile6_IWORK.Count*4)+1 < 100000000 ) {
          FILE *fp = (FILE *) heli_q8_DW.ToFile6_PWORK.FilePtr;
          if (fp != (NULL)) {
            real_T u[4];
            heli_q8_DW.ToFile6_IWORK.Decimation = 0;
            u[0] = heli_q8_M->Timing.t[1];
            u[1] = heli_q8_B.sf_Gyrovectortopitchrateelevati.euler_rates[0];
            u[2] = heli_q8_B.sf_Gyrovectortopitchrateelevati.euler_rates[1];
            u[3] = heli_q8_B.sf_Gyrovectortopitchrateelevati.euler_rates[2];
            if (fwrite(u, sizeof(real_T), 4, fp) != 4) {
              rtmSetErrorStatus(heli_q8_M,
                                "Error writing to MAT-file EulerRates.mat");
              return;
            }

            if (((++heli_q8_DW.ToFile6_IWORK.Count)*4)+1 >= 100000000) {
              (void)fprintf(stdout,
                            "*** The ToFile block will stop logging data before\n"
                            "    the simulation has ended, because it has reached\n"
                            "    the maximum number of elements (100000000)\n"
                            "    allowed in MAT-file EulerRates.mat.\n");
            }
          }
        }
      }
    }

    /* SignalConversion: '<S4>/TmpSignal ConversionAtTo File7Inport1' */
    rtb_TmpSignalConversionAtToFi_n[0] = heli_q8_B.Switch1;
    rtb_TmpSignalConversionAtToFi_n[1] = heli_q8_B.ManualSwitch_k[0];
    rtb_TmpSignalConversionAtToFi_n[2] = heli_q8_B.Switch2;
    rtb_TmpSignalConversionAtToFi_n[3] = heli_q8_B.ManualSwitch_k[1];
    rtb_TmpSignalConversionAtToFi_n[4] = heli_q8_B.ManualSwitch_k[2];

    /* ToFile: '<S4>/To File7' */
    if (rtmIsMajorTimeStep(heli_q8_M)) {
      {
        if (!(++heli_q8_DW.ToFile7_IWORK.Decimation % 1) &&
            (heli_q8_DW.ToFile7_IWORK.Count*6)+1 < 100000000 ) {
          FILE *fp = (FILE *) heli_q8_DW.ToFile7_PWORK.FilePtr;
          if (fp != (NULL)) {
            real_T u[6];
            heli_q8_DW.ToFile7_IWORK.Decimation = 0;
            u[0] = heli_q8_M->Timing.t[1];
            u[1] = rtb_TmpSignalConversionAtToFi_n[0];
            u[2] = rtb_TmpSignalConversionAtToFi_n[1];
            u[3] = rtb_TmpSignalConversionAtToFi_n[2];
            u[4] = rtb_TmpSignalConversionAtToFi_n[3];
            u[5] = rtb_TmpSignalConversionAtToFi_n[4];
            if (fwrite(u, sizeof(real_T), 6, fp) != 6) {
              rtmSetErrorStatus(heli_q8_M, "Error writing to MAT-file IMU.mat");
              return;
            }

            if (((++heli_q8_DW.ToFile7_IWORK.Count)*6)+1 >= 100000000) {
              (void)fprintf(stdout,
                            "*** The ToFile block will stop logging data before\n"
                            "    the simulation has ended, because it has reached\n"
                            "    the maximum number of elements (100000000)\n"
                            "    allowed in MAT-file IMU.mat.\n");
            }
          }
        }
      }
    }

    /* ToFile: '<S4>/To File8' */
    if (rtmIsMajorTimeStep(heli_q8_M)) {
      {
        if (!(++heli_q8_DW.ToFile8_IWORK.Decimation % 1) &&
            (heli_q8_DW.ToFile8_IWORK.Count*4)+1 < 100000000 ) {
          FILE *fp = (FILE *) heli_q8_DW.ToFile8_PWORK.FilePtr;
          if (fp != (NULL)) {
            real_T u[4];
            heli_q8_DW.ToFile8_IWORK.Decimation = 0;
            u[0] = heli_q8_M->Timing.t[1];
            u[1] = heli_q8_B.sf_Gyrovectortopitchrateeleva_f.euler_rates[0];
            u[2] = heli_q8_B.sf_Gyrovectortopitchrateeleva_f.euler_rates[1];
            u[3] = heli_q8_B.sf_Gyrovectortopitchrateeleva_f.euler_rates[2];
            if (fwrite(u, sizeof(real_T), 4, fp) != 4) {
              rtmSetErrorStatus(heli_q8_M,
                                "Error writing to MAT-file NoEncoder.mat");
              return;
            }

            if (((++heli_q8_DW.ToFile8_IWORK.Count)*4)+1 >= 100000000) {
              (void)fprintf(stdout,
                            "*** The ToFile block will stop logging data before\n"
                            "    the simulation has ended, because it has reached\n"
                            "    the maximum number of elements (100000000)\n"
                            "    allowed in MAT-file NoEncoder.mat.\n");
            }
          }
        }
      }
    }

    /* S-Function (stop_with_error_block): '<S8>/Stop with Call Error' */

    /* S-Function Block: heli_q8/Math logic/IMU/Stop with Call Error (stop_with_error_block) */
    {
      if (rtb_StreamCall1_o3 < 0) {
        msg_get_error_messageA(NULL, rtb_StreamCall1_o3, _rt_error_message,
          sizeof(_rt_error_message));
        rtmSetErrorStatus(heli_q8_M, _rt_error_message);
        return;
      }
    }

    /* S-Function (stop_with_error_block): '<S8>/Stop with Read Error' */

    /* S-Function Block: heli_q8/Math logic/IMU/Stop with Read Error (stop_with_error_block) */
    {
      if (rtb_StreamRead1_o5 < 0) {
        msg_get_error_messageA(NULL, rtb_StreamRead1_o5, _rt_error_message,
          sizeof(_rt_error_message));
        rtmSetErrorStatus(heli_q8_M, _rt_error_message);
        return;
      }
    }

    /* SignalConversion: '<S5>/TmpSignal ConversionAtTo FileInport1' */
    rtb_TmpSignalConversionAtToF_nc[0] = heli_q8_B.ManualSwitch1;
    rtb_TmpSignalConversionAtToF_nc[1] = heli_q8_B.ManualSwitch2[3];

    /* ToFile: '<S5>/To File' */
    if (rtmIsMajorTimeStep(heli_q8_M)) {
      {
        if (!(++heli_q8_DW.ToFile_IWORK.Decimation % 1) &&
            (heli_q8_DW.ToFile_IWORK.Count*3)+1 < 100000000 ) {
          FILE *fp = (FILE *) heli_q8_DW.ToFile_PWORK.FilePtr;
          if (fp != (NULL)) {
            real_T u[3];
            heli_q8_DW.ToFile_IWORK.Decimation = 0;
            u[0] = heli_q8_M->Timing.t[1];
            u[1] = rtb_TmpSignalConversionAtToF_nc[0];
            u[2] = rtb_TmpSignalConversionAtToF_nc[1];
            if (fwrite(u, sizeof(real_T), 3, fp) != 3) {
              rtmSetErrorStatus(heli_q8_M,
                                "Error writing to MAT-file elevation_rate.mat");
              return;
            }

            if (((++heli_q8_DW.ToFile_IWORK.Count)*3)+1 >= 100000000) {
              (void)fprintf(stdout,
                            "*** The ToFile block will stop logging data before\n"
                            "    the simulation has ended, because it has reached\n"
                            "    the maximum number of elements (100000000)\n"
                            "    allowed in MAT-file elevation_rate.mat.\n");
            }
          }
        }
      }
    }

    /* SignalConversion: '<S5>/TmpSignal ConversionAtTo File1Inport1' */
    rtb_TmpSignalConversionAtToF_nc[0] = heli_q8_B.ManualSwitch;
    rtb_TmpSignalConversionAtToF_nc[1] = heli_q8_B.ManualSwitch2[0];

    /* ToFile: '<S5>/To File1' */
    if (rtmIsMajorTimeStep(heli_q8_M)) {
      {
        if (!(++heli_q8_DW.ToFile1_IWORK_p.Decimation % 1) &&
            (heli_q8_DW.ToFile1_IWORK_p.Count*3)+1 < 100000000 ) {
          FILE *fp = (FILE *) heli_q8_DW.ToFile1_PWORK_h.FilePtr;
          if (fp != (NULL)) {
            real_T u[3];
            heli_q8_DW.ToFile1_IWORK_p.Decimation = 0;
            u[0] = heli_q8_M->Timing.t[1];
            u[1] = rtb_TmpSignalConversionAtToF_nc[0];
            u[2] = rtb_TmpSignalConversionAtToF_nc[1];
            if (fwrite(u, sizeof(real_T), 3, fp) != 3) {
              rtmSetErrorStatus(heli_q8_M, "Error writing to MAT-file pitch.mat");
              return;
            }

            if (((++heli_q8_DW.ToFile1_IWORK_p.Count)*3)+1 >= 100000000) {
              (void)fprintf(stdout,
                            "*** The ToFile block will stop logging data before\n"
                            "    the simulation has ended, because it has reached\n"
                            "    the maximum number of elements (100000000)\n"
                            "    allowed in MAT-file pitch.mat.\n");
            }
          }
        }
      }
    }
  }

  /* Sum: '<Root>/Sum3' */
  heli_q8_B.Sum3 = heli_q8_B.ManualSwitch2[0] - heli_q8_B.ManualSwitch;

  /* Sum: '<Root>/Sum4' */
  heli_q8_B.Sum4 = heli_q8_B.ManualSwitch2[3] - heli_q8_B.ManualSwitch1;
}

/* Model update function for TID0 */
void heli_q8_update0(void)             /* Sample time: [0.0s, 0.0s] */
{
  if (rtmIsMajorTimeStep(heli_q8_M)) {
    /* Update for Memory: '<S8>/Memory' */
    memcpy(&heli_q8_DW.Memory_PreviousInput[0], &heli_q8_B.Switch[0], 10U *
           sizeof(real_T));
  }

  if (rtmIsMajorTimeStep(heli_q8_M)) {
    rt_ertODEUpdateContinuousStates(&heli_q8_M->solverInfo);
  }

  /* Update absolute time */
  /* The "clockTick0" counts the number of times the code of this task has
   * been executed. The absolute time is the multiplication of "clockTick0"
   * and "Timing.stepSize0". Size of "clockTick0" ensures timer will not
   * overflow during the application lifespan selected.
   * Timer of this task consists of two 32 bit unsigned integers.
   * The two integers represent the low bits Timing.clockTick0 and the high bits
   * Timing.clockTickH0. When the low bit overflows to 0, the high bits increment.
   */
  if (!(++heli_q8_M->Timing.clockTick0)) {
    ++heli_q8_M->Timing.clockTickH0;
  }

  heli_q8_M->Timing.t[0] = rtsiGetSolverStopTime(&heli_q8_M->solverInfo);

  /* Update absolute time */
  /* The "clockTick1" counts the number of times the code of this task has
   * been executed. The absolute time is the multiplication of "clockTick1"
   * and "Timing.stepSize1". Size of "clockTick1" ensures timer will not
   * overflow during the application lifespan selected.
   * Timer of this task consists of two 32 bit unsigned integers.
   * The two integers represent the low bits Timing.clockTick1 and the high bits
   * Timing.clockTickH1. When the low bit overflows to 0, the high bits increment.
   */
  if (!(++heli_q8_M->Timing.clockTick1)) {
    ++heli_q8_M->Timing.clockTickH1;
  }

  heli_q8_M->Timing.t[1] = heli_q8_M->Timing.clockTick1 *
    heli_q8_M->Timing.stepSize1 + heli_q8_M->Timing.clockTickH1 *
    heli_q8_M->Timing.stepSize1 * 4294967296.0;
}

/* Derivatives for root system: '<Root>' */
void heli_q8_derivatives(void)
{
  int32_T i;
  XDot_heli_q8_T *_rtXdot;
  _rtXdot = ((XDot_heli_q8_T *) heli_q8_M->ModelData.derivs);

  /* Derivatives for Integrator: '<S3>/Integrator2' */
  for (i = 0; i < 5; i++) {
    _rtXdot->Integrator2_CSTATE[i] = heli_q8_B.Sum5[i];
  }

  /* End of Derivatives for Integrator: '<S3>/Integrator2' */

  /* Derivatives for TransferFcn: '<S2>/Pitch: Transfer Fcn' */
  _rtXdot->PitchTransferFcn_CSTATE = 0.0;
  _rtXdot->PitchTransferFcn_CSTATE += heli_q8_P.PitchTransferFcn_A *
    heli_q8_X.PitchTransferFcn_CSTATE;
  _rtXdot->PitchTransferFcn_CSTATE += heli_q8_B.PitchCounttorad;

  /* Derivatives for TransferFcn: '<S2>/Elevation: Transfer Fcn' */
  _rtXdot->ElevationTransferFcn_CSTATE = 0.0;
  _rtXdot->ElevationTransferFcn_CSTATE += heli_q8_P.ElevationTransferFcn_A *
    heli_q8_X.ElevationTransferFcn_CSTATE;
  _rtXdot->ElevationTransferFcn_CSTATE += heli_q8_B.ElevationCounttorad;

  /* Derivatives for TransferFcn: '<S2>/Travel: Transfer Fcn' */
  _rtXdot->TravelTransferFcn_CSTATE = 0.0;
  _rtXdot->TravelTransferFcn_CSTATE += heli_q8_P.TravelTransferFcn_A *
    heli_q8_X.TravelTransferFcn_CSTATE;
  _rtXdot->TravelTransferFcn_CSTATE += heli_q8_B.TravelCounttorad;

  /* Derivatives for Integrator: '<Root>/Integrator' */
  _rtXdot->Integrator_CSTATE = heli_q8_B.Sum3;

  /* Derivatives for Integrator: '<Root>/Integrator1' */
  _rtXdot->Integrator1_CSTATE = heli_q8_B.Sum4;
}

/* Model output function for TID2 */
void heli_q8_output2(void)             /* Sample time: [0.01s, 0.0s] */
{
  /* S-Function (game_controller_block): '<S10>/Game Controller' */

  /* S-Function Block: heli_q8/Subsystem/Joystick/Game Controller (game_controller_block) */
  {
    if (heli_q8_P.GameController_Enabled) {
      t_game_controller_states state;
      t_boolean new_data;
      t_error result;
      result = game_controller_poll(heli_q8_DW.GameController_Controller, &state,
        &new_data);
      if (result == 0) {
        heli_q8_B.GameController_o4 = state.x;
        heli_q8_B.GameController_o5 = state.y;
      }
    } else {
      heli_q8_B.GameController_o4 = 0;
      heli_q8_B.GameController_o5 = 0;
    }
  }
}

/* Model update function for TID2 */
void heli_q8_update2(void)             /* Sample time: [0.01s, 0.0s] */
{
  /* Update for RateTransition: '<S10>/Rate Transition: x' */
  heli_q8_DW.RateTransitionx_Buffer0 = heli_q8_B.GameController_o4;

  /* Update for RateTransition: '<S10>/Rate Transition: y' */
  heli_q8_DW.RateTransitiony_Buffer0 = heli_q8_B.GameController_o5;

  /* Update absolute time */
  /* The "clockTick2" counts the number of times the code of this task has
   * been executed. The absolute time is the multiplication of "clockTick2"
   * and "Timing.stepSize2". Size of "clockTick2" ensures timer will not
   * overflow during the application lifespan selected.
   * Timer of this task consists of two 32 bit unsigned integers.
   * The two integers represent the low bits Timing.clockTick2 and the high bits
   * Timing.clockTickH2. When the low bit overflows to 0, the high bits increment.
   */
  if (!(++heli_q8_M->Timing.clockTick2)) {
    ++heli_q8_M->Timing.clockTickH2;
  }

  heli_q8_M->Timing.t[2] = heli_q8_M->Timing.clockTick2 *
    heli_q8_M->Timing.stepSize2 + heli_q8_M->Timing.clockTickH2 *
    heli_q8_M->Timing.stepSize2 * 4294967296.0;
}

/* Model output wrapper function for compatibility with a static main program */
void heli_q8_output(int_T tid)
{
  switch (tid) {
   case 0 :
    heli_q8_output0();
    break;

   case 2 :
    heli_q8_output2();
    break;

   default :
    break;
  }
}

/* Model update wrapper function for compatibility with a static main program */
void heli_q8_update(int_T tid)
{
  switch (tid) {
   case 0 :
    heli_q8_update0();
    break;

   case 2 :
    heli_q8_update2();
    break;

   default :
    break;
  }
}

/* Model initialize function */
void heli_q8_initialize(void)
{
  /* Start for S-Function (hil_initialize_block): '<Root>/HIL Initialize' */

  /* S-Function Block: heli_q8/HIL Initialize (hil_initialize_block) */
  {
    t_int result;
    t_boolean is_switching;
    result = hil_open("q8_usb", "0", &heli_q8_DW.HILInitialize_Card);
    if (result < 0) {
      msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
        (_rt_error_message));
      rtmSetErrorStatus(heli_q8_M, _rt_error_message);
      return;
    }

    is_switching = false;
    result = hil_set_card_specific_options(heli_q8_DW.HILInitialize_Card,
      "update_rate=normal;decimation=1", 32);
    if (result < 0) {
      msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
        (_rt_error_message));
      rtmSetErrorStatus(heli_q8_M, _rt_error_message);
      return;
    }

    result = hil_watchdog_clear(heli_q8_DW.HILInitialize_Card);
    if (result < 0 && result != -QERR_HIL_WATCHDOG_CLEAR) {
      msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
        (_rt_error_message));
      rtmSetErrorStatus(heli_q8_M, _rt_error_message);
      return;
    }

    if ((heli_q8_P.HILInitialize_set_analog_input_ && !is_switching) ||
        (heli_q8_P.HILInitialize_set_analog_inpu_m && is_switching)) {
      {
        int_T i1;
        real_T *dw_AIMinimums = &heli_q8_DW.HILInitialize_AIMinimums[0];
        for (i1=0; i1 < 8; i1++) {
          dw_AIMinimums[i1] = heli_q8_P.HILInitialize_analog_input_mini;
        }
      }

      {
        int_T i1;
        real_T *dw_AIMaximums = &heli_q8_DW.HILInitialize_AIMaximums[0];
        for (i1=0; i1 < 8; i1++) {
          dw_AIMaximums[i1] = heli_q8_P.HILInitialize_analog_input_maxi;
        }
      }

      result = hil_set_analog_input_ranges(heli_q8_DW.HILInitialize_Card,
        heli_q8_P.HILInitialize_analog_input_chan, 8U,
        &heli_q8_DW.HILInitialize_AIMinimums[0],
        &heli_q8_DW.HILInitialize_AIMaximums[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(heli_q8_M, _rt_error_message);
        return;
      }
    }

    if ((heli_q8_P.HILInitialize_set_analog_output && !is_switching) ||
        (heli_q8_P.HILInitialize_set_analog_outp_b && is_switching)) {
      {
        int_T i1;
        real_T *dw_AOMinimums = &heli_q8_DW.HILInitialize_AOMinimums[0];
        for (i1=0; i1 < 8; i1++) {
          dw_AOMinimums[i1] = heli_q8_P.HILInitialize_analog_output_min;
        }
      }

      {
        int_T i1;
        real_T *dw_AOMaximums = &heli_q8_DW.HILInitialize_AOMaximums[0];
        for (i1=0; i1 < 8; i1++) {
          dw_AOMaximums[i1] = heli_q8_P.HILInitialize_analog_output_max;
        }
      }

      result = hil_set_analog_output_ranges(heli_q8_DW.HILInitialize_Card,
        heli_q8_P.HILInitialize_analog_output_cha, 8U,
        &heli_q8_DW.HILInitialize_AOMinimums[0],
        &heli_q8_DW.HILInitialize_AOMaximums[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(heli_q8_M, _rt_error_message);
        return;
      }
    }

    if ((heli_q8_P.HILInitialize_set_analog_outp_e && !is_switching) ||
        (heli_q8_P.HILInitialize_set_analog_outp_j && is_switching)) {
      {
        int_T i1;
        real_T *dw_AOVoltages = &heli_q8_DW.HILInitialize_AOVoltages[0];
        for (i1=0; i1 < 8; i1++) {
          dw_AOVoltages[i1] = heli_q8_P.HILInitialize_initial_analog_ou;
        }
      }

      result = hil_write_analog(heli_q8_DW.HILInitialize_Card,
        heli_q8_P.HILInitialize_analog_output_cha, 8U,
        &heli_q8_DW.HILInitialize_AOVoltages[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(heli_q8_M, _rt_error_message);
        return;
      }
    }

    if (heli_q8_P.HILInitialize_set_analog_outp_p) {
      {
        int_T i1;
        real_T *dw_AOVoltages = &heli_q8_DW.HILInitialize_AOVoltages[0];
        for (i1=0; i1 < 8; i1++) {
          dw_AOVoltages[i1] = heli_q8_P.HILInitialize_watchdog_analog_o;
        }
      }

      result = hil_watchdog_set_analog_expiration_state
        (heli_q8_DW.HILInitialize_Card,
         heli_q8_P.HILInitialize_analog_output_cha, 8U,
         &heli_q8_DW.HILInitialize_AOVoltages[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(heli_q8_M, _rt_error_message);
        return;
      }
    }

    if ((heli_q8_P.HILInitialize_set_encoder_param && !is_switching) ||
        (heli_q8_P.HILInitialize_set_encoder_par_m && is_switching)) {
      {
        int_T i1;
        int32_T *dw_QuadratureModes = &heli_q8_DW.HILInitialize_QuadratureModes
          [0];
        for (i1=0; i1 < 8; i1++) {
          dw_QuadratureModes[i1] = heli_q8_P.HILInitialize_quadrature;
        }
      }

      result = hil_set_encoder_quadrature_mode(heli_q8_DW.HILInitialize_Card,
        heli_q8_P.HILInitialize_encoder_channels, 8U, (t_encoder_quadrature_mode
        *) &heli_q8_DW.HILInitialize_QuadratureModes[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(heli_q8_M, _rt_error_message);
        return;
      }
    }

    if ((heli_q8_P.HILInitialize_set_encoder_count && !is_switching) ||
        (heli_q8_P.HILInitialize_set_encoder_cou_k && is_switching)) {
      {
        int_T i1;
        int32_T *dw_InitialEICounts = &heli_q8_DW.HILInitialize_InitialEICounts
          [0];
        for (i1=0; i1 < 8; i1++) {
          dw_InitialEICounts[i1] = heli_q8_P.HILInitialize_initial_encoder_c;
        }
      }

      result = hil_set_encoder_counts(heli_q8_DW.HILInitialize_Card,
        heli_q8_P.HILInitialize_encoder_channels, 8U,
        &heli_q8_DW.HILInitialize_InitialEICounts[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(heli_q8_M, _rt_error_message);
        return;
      }
    }

    if ((heli_q8_P.HILInitialize_set_pwm_params_at && !is_switching) ||
        (heli_q8_P.HILInitialize_set_pwm_params__f && is_switching)) {
      uint32_T num_duty_cycle_modes = 0;
      uint32_T num_frequency_modes = 0;

      {
        int_T i1;
        int32_T *dw_POModeValues = &heli_q8_DW.HILInitialize_POModeValues[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POModeValues[i1] = heli_q8_P.HILInitialize_pwm_modes;
        }
      }

      result = hil_set_pwm_mode(heli_q8_DW.HILInitialize_Card,
        heli_q8_P.HILInitialize_pwm_channels, 8U, (t_pwm_mode *)
        &heli_q8_DW.HILInitialize_POModeValues[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(heli_q8_M, _rt_error_message);
        return;
      }

      {
        int_T i1;
        const uint32_T *p_HILInitialize_pwm_channels =
          heli_q8_P.HILInitialize_pwm_channels;
        int32_T *dw_POModeValues = &heli_q8_DW.HILInitialize_POModeValues[0];
        for (i1=0; i1 < 8; i1++) {
          if (dw_POModeValues[i1] == PWM_DUTY_CYCLE_MODE || dw_POModeValues[i1] ==
              PWM_ONE_SHOT_MODE || dw_POModeValues[i1] == PWM_TIME_MODE) {
            heli_q8_DW.HILInitialize_POSortedChans[num_duty_cycle_modes] =
              p_HILInitialize_pwm_channels[i1];
            heli_q8_DW.HILInitialize_POSortedFreqs[num_duty_cycle_modes] =
              heli_q8_P.HILInitialize_pwm_frequency;
            num_duty_cycle_modes++;
          } else {
            heli_q8_DW.HILInitialize_POSortedChans[7U - num_frequency_modes] =
              p_HILInitialize_pwm_channels[i1];
            heli_q8_DW.HILInitialize_POSortedFreqs[7U - num_frequency_modes] =
              heli_q8_P.HILInitialize_pwm_frequency;
            num_frequency_modes++;
          }
        }
      }

      if (num_duty_cycle_modes > 0) {
        result = hil_set_pwm_frequency(heli_q8_DW.HILInitialize_Card,
          &heli_q8_DW.HILInitialize_POSortedChans[0], num_duty_cycle_modes,
          &heli_q8_DW.HILInitialize_POSortedFreqs[0]);
        if (result < 0) {
          msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
            (_rt_error_message));
          rtmSetErrorStatus(heli_q8_M, _rt_error_message);
          return;
        }
      }

      if (num_frequency_modes > 0) {
        result = hil_set_pwm_duty_cycle(heli_q8_DW.HILInitialize_Card,
          &heli_q8_DW.HILInitialize_POSortedChans[num_duty_cycle_modes],
          num_frequency_modes,
          &heli_q8_DW.HILInitialize_POSortedFreqs[num_duty_cycle_modes]);
        if (result < 0) {
          msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
            (_rt_error_message));
          rtmSetErrorStatus(heli_q8_M, _rt_error_message);
          return;
        }
      }

      {
        int_T i1;
        int32_T *dw_POModeValues = &heli_q8_DW.HILInitialize_POModeValues[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POModeValues[i1] = heli_q8_P.HILInitialize_pwm_configuration;
        }
      }

      {
        int_T i1;
        int32_T *dw_POAlignValues = &heli_q8_DW.HILInitialize_POAlignValues[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POAlignValues[i1] = heli_q8_P.HILInitialize_pwm_alignment;
        }
      }

      {
        int_T i1;
        int32_T *dw_POPolarityVals = &heli_q8_DW.HILInitialize_POPolarityVals[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POPolarityVals[i1] = heli_q8_P.HILInitialize_pwm_polarity;
        }
      }

      result = hil_set_pwm_configuration(heli_q8_DW.HILInitialize_Card,
        heli_q8_P.HILInitialize_pwm_channels, 8U,
        (t_pwm_configuration *) &heli_q8_DW.HILInitialize_POModeValues[0],
        (t_pwm_alignment *) &heli_q8_DW.HILInitialize_POAlignValues[0],
        (t_pwm_polarity *) &heli_q8_DW.HILInitialize_POPolarityVals[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(heli_q8_M, _rt_error_message);
        return;
      }

      {
        int_T i1;
        real_T *dw_POSortedFreqs = &heli_q8_DW.HILInitialize_POSortedFreqs[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POSortedFreqs[i1] = heli_q8_P.HILInitialize_pwm_leading_deadb;
        }
      }

      {
        int_T i1;
        real_T *dw_POValues = &heli_q8_DW.HILInitialize_POValues[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POValues[i1] = heli_q8_P.HILInitialize_pwm_trailing_dead;
        }
      }

      result = hil_set_pwm_deadband(heli_q8_DW.HILInitialize_Card,
        heli_q8_P.HILInitialize_pwm_channels, 8U,
        &heli_q8_DW.HILInitialize_POSortedFreqs[0],
        &heli_q8_DW.HILInitialize_POValues[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(heli_q8_M, _rt_error_message);
        return;
      }
    }

    if ((heli_q8_P.HILInitialize_set_pwm_outputs_a && !is_switching) ||
        (heli_q8_P.HILInitialize_set_pwm_outputs_g && is_switching)) {
      {
        int_T i1;
        real_T *dw_POValues = &heli_q8_DW.HILInitialize_POValues[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POValues[i1] = heli_q8_P.HILInitialize_initial_pwm_outpu;
        }
      }

      result = hil_write_pwm(heli_q8_DW.HILInitialize_Card,
        heli_q8_P.HILInitialize_pwm_channels, 8U,
        &heli_q8_DW.HILInitialize_POValues[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(heli_q8_M, _rt_error_message);
        return;
      }
    }

    if (heli_q8_P.HILInitialize_set_pwm_outputs_o) {
      {
        int_T i1;
        real_T *dw_POValues = &heli_q8_DW.HILInitialize_POValues[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POValues[i1] = heli_q8_P.HILInitialize_watchdog_pwm_outp;
        }
      }

      result = hil_watchdog_set_pwm_expiration_state
        (heli_q8_DW.HILInitialize_Card, heli_q8_P.HILInitialize_pwm_channels, 8U,
         &heli_q8_DW.HILInitialize_POValues[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(heli_q8_M, _rt_error_message);
        return;
      }
    }
  }

  /* Start for S-Function (hil_read_encoder_timebase_block): '<S2>/HIL Read Encoder Timebase' */

  /* S-Function Block: heli_q8/Heli 3D/HIL Read Encoder Timebase (hil_read_encoder_timebase_block) */
  {
    t_error result;
    result = hil_task_create_encoder_reader(heli_q8_DW.HILInitialize_Card,
      heli_q8_P.HILReadEncoderTimebase_samples_,
      heli_q8_P.HILReadEncoderTimebase_channels, 3,
      &heli_q8_DW.HILReadEncoderTimebase_Task);
    if (result < 0) {
      msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
        (_rt_error_message));
      rtmSetErrorStatus(heli_q8_M, _rt_error_message);
    }
  }

  /* Start for ToFile: '<Root>/To File3' */
  {
    FILE *fp = (NULL);
    char fileName[509] = "Encoder.mat";
    if ((fp = fopen(fileName, "wb")) == (NULL)) {
      rtmSetErrorStatus(heli_q8_M, "Error creating .mat file Encoder.mat");
      return;
    }

    if (rt_WriteMat4FileHeader(fp,7,0,"Encoder")) {
      rtmSetErrorStatus(heli_q8_M,
                        "Error writing mat file header to file Encoder.mat");
      return;
    }

    heli_q8_DW.ToFile3_IWORK.Count = 0;
    heli_q8_DW.ToFile3_IWORK.Decimation = -1;
    heli_q8_DW.ToFile3_PWORK.FilePtr = fp;
  }

  /* Start for RateTransition: '<S10>/Rate Transition: x' */
  heli_q8_B.RateTransitionx = heli_q8_P.RateTransitionx_X0;

  /* Start for DiscretePulseGenerator: '<S5>/e_c_dot' */
  heli_q8_DW.clockTickCounter = -5000;

  /* Start for RateTransition: '<S10>/Rate Transition: y' */
  heli_q8_B.RateTransitiony = heli_q8_P.RateTransitiony_X0;

  /* Start for ToFile: '<S3>/To File2' */
  {
    FILE *fp = (NULL);
    char fileName[509] = "Estimators.mat";
    if ((fp = fopen(fileName, "wb")) == (NULL)) {
      rtmSetErrorStatus(heli_q8_M, "Error creating .mat file Estimators.mat");
      return;
    }

    if (rt_WriteMat4FileHeader(fp,6,0,"Estimators")) {
      rtmSetErrorStatus(heli_q8_M,
                        "Error writing mat file header to file Estimators.mat");
      return;
    }

    heli_q8_DW.ToFile2_IWORK.Count = 0;
    heli_q8_DW.ToFile2_IWORK.Decimation = -1;
    heli_q8_DW.ToFile2_PWORK.FilePtr = fp;
  }

  /* Start for S-Function (stream_call_block): '<S8>/Stream Call1' */

  /* S-Function Block: heli_q8/Math logic/IMU/Stream Call1 (stream_call_block) */
  {
    heli_q8_DW.StreamCall1_State = STREAM_CALL_STATE_NOT_CONNECTED;
    heli_q8_DW.StreamCall1_Stream = NULL;
  }

  /* Start for ToFile: '<S4>/To File1' */
  {
    FILE *fp = (NULL);
    char fileName[509] = "AngleTF.mat";
    if ((fp = fopen(fileName, "wb")) == (NULL)) {
      rtmSetErrorStatus(heli_q8_M, "Error creating .mat file AngleTF.mat");
      return;
    }

    if (rt_WriteMat4FileHeader(fp,3,0,"AngleTF")) {
      rtmSetErrorStatus(heli_q8_M,
                        "Error writing mat file header to file AngleTF.mat");
      return;
    }

    heli_q8_DW.ToFile1_IWORK.Count = 0;
    heli_q8_DW.ToFile1_IWORK.Decimation = -1;
    heli_q8_DW.ToFile1_PWORK.FilePtr = fp;
  }

  /* Start for ToFile: '<S4>/To File4' */
  {
    FILE *fp = (NULL);
    char fileName[509] = "eulerAngles.mat";
    if ((fp = fopen(fileName, "wb")) == (NULL)) {
      rtmSetErrorStatus(heli_q8_M, "Error creating .mat file eulerAngles.mat");
      return;
    }

    if (rt_WriteMat4FileHeader(fp,4,0,"eulerAngles")) {
      rtmSetErrorStatus(heli_q8_M,
                        "Error writing mat file header to file eulerAngles.mat");
      return;
    }

    heli_q8_DW.ToFile4_IWORK.Count = 0;
    heli_q8_DW.ToFile4_IWORK.Decimation = -1;
    heli_q8_DW.ToFile4_PWORK.FilePtr = fp;
  }

  /* Start for ToFile: '<S4>/To File5' */
  {
    FILE *fp = (NULL);
    char fileName[509] = "Gyro.mat";
    if ((fp = fopen(fileName, "wb")) == (NULL)) {
      rtmSetErrorStatus(heli_q8_M, "Error creating .mat file Gyro.mat");
      return;
    }

    if (rt_WriteMat4FileHeader(fp,4,0,"Gyro")) {
      rtmSetErrorStatus(heli_q8_M,
                        "Error writing mat file header to file Gyro.mat");
      return;
    }

    heli_q8_DW.ToFile5_IWORK.Count = 0;
    heli_q8_DW.ToFile5_IWORK.Decimation = -1;
    heli_q8_DW.ToFile5_PWORK.FilePtr = fp;
  }

  /* Start for ToFile: '<S4>/To File6' */
  {
    FILE *fp = (NULL);
    char fileName[509] = "EulerRates.mat";
    if ((fp = fopen(fileName, "wb")) == (NULL)) {
      rtmSetErrorStatus(heli_q8_M, "Error creating .mat file EulerRates.mat");
      return;
    }

    if (rt_WriteMat4FileHeader(fp,4,0,"EulerRates")) {
      rtmSetErrorStatus(heli_q8_M,
                        "Error writing mat file header to file EulerRates.mat");
      return;
    }

    heli_q8_DW.ToFile6_IWORK.Count = 0;
    heli_q8_DW.ToFile6_IWORK.Decimation = -1;
    heli_q8_DW.ToFile6_PWORK.FilePtr = fp;
  }

  /* Start for ToFile: '<S4>/To File7' */
  {
    FILE *fp = (NULL);
    char fileName[509] = "IMU.mat";
    if ((fp = fopen(fileName, "wb")) == (NULL)) {
      rtmSetErrorStatus(heli_q8_M, "Error creating .mat file IMU.mat");
      return;
    }

    if (rt_WriteMat4FileHeader(fp,6,0,"IMU")) {
      rtmSetErrorStatus(heli_q8_M,
                        "Error writing mat file header to file IMU.mat");
      return;
    }

    heli_q8_DW.ToFile7_IWORK.Count = 0;
    heli_q8_DW.ToFile7_IWORK.Decimation = -1;
    heli_q8_DW.ToFile7_PWORK.FilePtr = fp;
  }

  /* Start for ToFile: '<S4>/To File8' */
  {
    FILE *fp = (NULL);
    char fileName[509] = "NoEncoder.mat";
    if ((fp = fopen(fileName, "wb")) == (NULL)) {
      rtmSetErrorStatus(heli_q8_M, "Error creating .mat file NoEncoder.mat");
      return;
    }

    if (rt_WriteMat4FileHeader(fp,4,0,"NoEncoder")) {
      rtmSetErrorStatus(heli_q8_M,
                        "Error writing mat file header to file NoEncoder.mat");
      return;
    }

    heli_q8_DW.ToFile8_IWORK.Count = 0;
    heli_q8_DW.ToFile8_IWORK.Decimation = -1;
    heli_q8_DW.ToFile8_PWORK.FilePtr = fp;
  }

  /* Start for ToFile: '<S5>/To File' */
  {
    FILE *fp = (NULL);
    char fileName[509] = "elevation_rate.mat";
    if ((fp = fopen(fileName, "wb")) == (NULL)) {
      rtmSetErrorStatus(heli_q8_M, "Error creating .mat file elevation_rate.mat");
      return;
    }

    if (rt_WriteMat4FileHeader(fp,3,0,"elevation_rate")) {
      rtmSetErrorStatus(heli_q8_M,
                        "Error writing mat file header to file elevation_rate.mat");
      return;
    }

    heli_q8_DW.ToFile_IWORK.Count = 0;
    heli_q8_DW.ToFile_IWORK.Decimation = -1;
    heli_q8_DW.ToFile_PWORK.FilePtr = fp;
  }

  /* Start for ToFile: '<S5>/To File1' */
  {
    FILE *fp = (NULL);
    char fileName[509] = "pitch.mat";
    if ((fp = fopen(fileName, "wb")) == (NULL)) {
      rtmSetErrorStatus(heli_q8_M, "Error creating .mat file pitch.mat");
      return;
    }

    if (rt_WriteMat4FileHeader(fp,3,0,"pitch")) {
      rtmSetErrorStatus(heli_q8_M,
                        "Error writing mat file header to file pitch.mat");
      return;
    }

    heli_q8_DW.ToFile1_IWORK_p.Count = 0;
    heli_q8_DW.ToFile1_IWORK_p.Decimation = -1;
    heli_q8_DW.ToFile1_PWORK_h.FilePtr = fp;
  }

  /* Start for S-Function (game_controller_block): '<S10>/Game Controller' */

  /* S-Function Block: heli_q8/Subsystem/Joystick/Game Controller (game_controller_block) */
  {
    if (heli_q8_P.GameController_Enabled) {
      t_double deadzone[6];
      t_double saturation[6];
      t_int index;
      t_error result;
      for (index = 0; index < 6; index++) {
        deadzone[index] = -1;
      }

      for (index = 0; index < 6; index++) {
        saturation[index] = -1;
      }

      result = game_controller_open(heli_q8_P.GameController_ControllerNumber,
        heli_q8_P.GameController_BufferSize, deadzone, saturation,
        heli_q8_P.GameController_AutoCenter, 0, 1.0,
        &heli_q8_DW.GameController_Controller);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(heli_q8_M, _rt_error_message);
      }
    }
  }

  {
    int32_T i;

    /* InitializeConditions for Integrator: '<S3>/Integrator2' */
    for (i = 0; i < 5; i++) {
      heli_q8_X.Integrator2_CSTATE[i] = heli_q8_P.Integrator2_IC;
    }

    /* End of InitializeConditions for Integrator: '<S3>/Integrator2' */

    /* InitializeConditions for TransferFcn: '<S2>/Pitch: Transfer Fcn' */
    heli_q8_X.PitchTransferFcn_CSTATE = 0.0;

    /* InitializeConditions for TransferFcn: '<S2>/Elevation: Transfer Fcn' */
    heli_q8_X.ElevationTransferFcn_CSTATE = 0.0;

    /* InitializeConditions for TransferFcn: '<S2>/Travel: Transfer Fcn' */
    heli_q8_X.TravelTransferFcn_CSTATE = 0.0;

    /* InitializeConditions for RateTransition: '<S10>/Rate Transition: x' */
    heli_q8_DW.RateTransitionx_Buffer0 = heli_q8_P.RateTransitionx_X0;

    /* InitializeConditions for RateTransition: '<S10>/Rate Transition: y' */
    heli_q8_DW.RateTransitiony_Buffer0 = heli_q8_P.RateTransitiony_X0;

    /* InitializeConditions for Integrator: '<Root>/Integrator' */
    heli_q8_X.Integrator_CSTATE = heli_q8_P.Integrator_IC;

    /* InitializeConditions for Integrator: '<Root>/Integrator1' */
    heli_q8_X.Integrator1_CSTATE = heli_q8_P.Integrator1_IC;

    /* InitializeConditions for Memory: '<S8>/Memory' */
    memcpy(&heli_q8_DW.Memory_PreviousInput[0], &heli_q8_P.Memory_X0[0], 10U *
           sizeof(real_T));
  }
}

/* Model terminate function */
void heli_q8_terminate(void)
{
  /* Terminate for S-Function (hil_initialize_block): '<Root>/HIL Initialize' */

  /* S-Function Block: heli_q8/HIL Initialize (hil_initialize_block) */
  {
    t_boolean is_switching;
    t_int result;
    t_uint32 num_final_analog_outputs = 0;
    t_uint32 num_final_pwm_outputs = 0;
    hil_task_stop_all(heli_q8_DW.HILInitialize_Card);
    hil_monitor_stop_all(heli_q8_DW.HILInitialize_Card);
    is_switching = false;
    if ((heli_q8_P.HILInitialize_set_analog_out_ex && !is_switching) ||
        (heli_q8_P.HILInitialize_set_analog_outp_c && is_switching)) {
      {
        int_T i1;
        real_T *dw_AOVoltages = &heli_q8_DW.HILInitialize_AOVoltages[0];
        for (i1=0; i1 < 8; i1++) {
          dw_AOVoltages[i1] = heli_q8_P.HILInitialize_final_analog_outp;
        }
      }

      num_final_analog_outputs = 8U;
    }

    if ((heli_q8_P.HILInitialize_set_pwm_output_ap && !is_switching) ||
        (heli_q8_P.HILInitialize_set_pwm_outputs_p && is_switching)) {
      {
        int_T i1;
        real_T *dw_POValues = &heli_q8_DW.HILInitialize_POValues[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POValues[i1] = heli_q8_P.HILInitialize_final_pwm_outputs;
        }
      }

      num_final_pwm_outputs = 8U;
    }

    if (0
        || num_final_analog_outputs > 0
        || num_final_pwm_outputs > 0
        ) {
      /* Attempt to write the final outputs atomically (due to firmware issue in old Q2-USB). Otherwise write channels individually */
      result = hil_write(heli_q8_DW.HILInitialize_Card
                         , heli_q8_P.HILInitialize_analog_output_cha,
                         num_final_analog_outputs
                         , heli_q8_P.HILInitialize_pwm_channels,
                         num_final_pwm_outputs
                         , NULL, 0
                         , NULL, 0
                         , &heli_q8_DW.HILInitialize_AOVoltages[0]
                         , &heli_q8_DW.HILInitialize_POValues[0]
                         , (t_boolean *) NULL
                         , NULL
                         );
      if (result == -QERR_HIL_WRITE_NOT_SUPPORTED) {
        t_error local_result;
        result = 0;

        /* The hil_write operation is not supported by this card. Write final outputs for each channel type */
        if (num_final_analog_outputs > 0) {
          local_result = hil_write_analog(heli_q8_DW.HILInitialize_Card,
            heli_q8_P.HILInitialize_analog_output_cha, num_final_analog_outputs,
            &heli_q8_DW.HILInitialize_AOVoltages[0]);
          if (local_result < 0) {
            result = local_result;
          }
        }

        if (num_final_pwm_outputs > 0) {
          local_result = hil_write_pwm(heli_q8_DW.HILInitialize_Card,
            heli_q8_P.HILInitialize_pwm_channels, num_final_pwm_outputs,
            &heli_q8_DW.HILInitialize_POValues[0]);
          if (local_result < 0) {
            result = local_result;
          }
        }

        if (result < 0) {
          msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
            (_rt_error_message));
          rtmSetErrorStatus(heli_q8_M, _rt_error_message);
        }
      }
    }

    hil_task_delete_all(heli_q8_DW.HILInitialize_Card);
    hil_monitor_delete_all(heli_q8_DW.HILInitialize_Card);
    hil_close(heli_q8_DW.HILInitialize_Card);
    heli_q8_DW.HILInitialize_Card = NULL;
  }

  /* Terminate for ToFile: '<Root>/To File3' */
  {
    FILE *fp = (FILE *) heli_q8_DW.ToFile3_PWORK.FilePtr;
    if (fp != (NULL)) {
      char fileName[509] = "Encoder.mat";
      if (fclose(fp) == EOF) {
        rtmSetErrorStatus(heli_q8_M, "Error closing MAT-file Encoder.mat");
        return;
      }

      if ((fp = fopen(fileName, "r+b")) == (NULL)) {
        rtmSetErrorStatus(heli_q8_M, "Error reopening MAT-file Encoder.mat");
        return;
      }

      if (rt_WriteMat4FileHeader(fp, 7, heli_q8_DW.ToFile3_IWORK.Count,
           "Encoder")) {
        rtmSetErrorStatus(heli_q8_M,
                          "Error writing header for Encoder to MAT-file Encoder.mat");
      }

      if (fclose(fp) == EOF) {
        rtmSetErrorStatus(heli_q8_M, "Error closing MAT-file Encoder.mat");
        return;
      }

      heli_q8_DW.ToFile3_PWORK.FilePtr = (NULL);
    }
  }

  /* Terminate for ToFile: '<S3>/To File2' */
  {
    FILE *fp = (FILE *) heli_q8_DW.ToFile2_PWORK.FilePtr;
    if (fp != (NULL)) {
      char fileName[509] = "Estimators.mat";
      if (fclose(fp) == EOF) {
        rtmSetErrorStatus(heli_q8_M, "Error closing MAT-file Estimators.mat");
        return;
      }

      if ((fp = fopen(fileName, "r+b")) == (NULL)) {
        rtmSetErrorStatus(heli_q8_M, "Error reopening MAT-file Estimators.mat");
        return;
      }

      if (rt_WriteMat4FileHeader(fp, 6, heli_q8_DW.ToFile2_IWORK.Count,
           "Estimators")) {
        rtmSetErrorStatus(heli_q8_M,
                          "Error writing header for Estimators to MAT-file Estimators.mat");
      }

      if (fclose(fp) == EOF) {
        rtmSetErrorStatus(heli_q8_M, "Error closing MAT-file Estimators.mat");
        return;
      }

      heli_q8_DW.ToFile2_PWORK.FilePtr = (NULL);
    }
  }

  /* Terminate for S-Function (stream_call_block): '<S8>/Stream Call1' */

  /* S-Function Block: heli_q8/Math logic/IMU/Stream Call1 (stream_call_block) */
  {
    if (heli_q8_DW.StreamCall1_Stream != NULL) {
      stream_close(heli_q8_DW.StreamCall1_Stream);
      heli_q8_DW.StreamCall1_Stream = NULL;
    }
  }

  /* Terminate for ToFile: '<S4>/To File1' */
  {
    FILE *fp = (FILE *) heli_q8_DW.ToFile1_PWORK.FilePtr;
    if (fp != (NULL)) {
      char fileName[509] = "AngleTF.mat";
      if (fclose(fp) == EOF) {
        rtmSetErrorStatus(heli_q8_M, "Error closing MAT-file AngleTF.mat");
        return;
      }

      if ((fp = fopen(fileName, "r+b")) == (NULL)) {
        rtmSetErrorStatus(heli_q8_M, "Error reopening MAT-file AngleTF.mat");
        return;
      }

      if (rt_WriteMat4FileHeader(fp, 3, heli_q8_DW.ToFile1_IWORK.Count,
           "AngleTF")) {
        rtmSetErrorStatus(heli_q8_M,
                          "Error writing header for AngleTF to MAT-file AngleTF.mat");
      }

      if (fclose(fp) == EOF) {
        rtmSetErrorStatus(heli_q8_M, "Error closing MAT-file AngleTF.mat");
        return;
      }

      heli_q8_DW.ToFile1_PWORK.FilePtr = (NULL);
    }
  }

  /* Terminate for ToFile: '<S4>/To File4' */
  {
    FILE *fp = (FILE *) heli_q8_DW.ToFile4_PWORK.FilePtr;
    if (fp != (NULL)) {
      char fileName[509] = "eulerAngles.mat";
      if (fclose(fp) == EOF) {
        rtmSetErrorStatus(heli_q8_M, "Error closing MAT-file eulerAngles.mat");
        return;
      }

      if ((fp = fopen(fileName, "r+b")) == (NULL)) {
        rtmSetErrorStatus(heli_q8_M, "Error reopening MAT-file eulerAngles.mat");
        return;
      }

      if (rt_WriteMat4FileHeader(fp, 4, heli_q8_DW.ToFile4_IWORK.Count,
           "eulerAngles")) {
        rtmSetErrorStatus(heli_q8_M,
                          "Error writing header for eulerAngles to MAT-file eulerAngles.mat");
      }

      if (fclose(fp) == EOF) {
        rtmSetErrorStatus(heli_q8_M, "Error closing MAT-file eulerAngles.mat");
        return;
      }

      heli_q8_DW.ToFile4_PWORK.FilePtr = (NULL);
    }
  }

  /* Terminate for ToFile: '<S4>/To File5' */
  {
    FILE *fp = (FILE *) heli_q8_DW.ToFile5_PWORK.FilePtr;
    if (fp != (NULL)) {
      char fileName[509] = "Gyro.mat";
      if (fclose(fp) == EOF) {
        rtmSetErrorStatus(heli_q8_M, "Error closing MAT-file Gyro.mat");
        return;
      }

      if ((fp = fopen(fileName, "r+b")) == (NULL)) {
        rtmSetErrorStatus(heli_q8_M, "Error reopening MAT-file Gyro.mat");
        return;
      }

      if (rt_WriteMat4FileHeader(fp, 4, heli_q8_DW.ToFile5_IWORK.Count, "Gyro"))
      {
        rtmSetErrorStatus(heli_q8_M,
                          "Error writing header for Gyro to MAT-file Gyro.mat");
      }

      if (fclose(fp) == EOF) {
        rtmSetErrorStatus(heli_q8_M, "Error closing MAT-file Gyro.mat");
        return;
      }

      heli_q8_DW.ToFile5_PWORK.FilePtr = (NULL);
    }
  }

  /* Terminate for ToFile: '<S4>/To File6' */
  {
    FILE *fp = (FILE *) heli_q8_DW.ToFile6_PWORK.FilePtr;
    if (fp != (NULL)) {
      char fileName[509] = "EulerRates.mat";
      if (fclose(fp) == EOF) {
        rtmSetErrorStatus(heli_q8_M, "Error closing MAT-file EulerRates.mat");
        return;
      }

      if ((fp = fopen(fileName, "r+b")) == (NULL)) {
        rtmSetErrorStatus(heli_q8_M, "Error reopening MAT-file EulerRates.mat");
        return;
      }

      if (rt_WriteMat4FileHeader(fp, 4, heli_q8_DW.ToFile6_IWORK.Count,
           "EulerRates")) {
        rtmSetErrorStatus(heli_q8_M,
                          "Error writing header for EulerRates to MAT-file EulerRates.mat");
      }

      if (fclose(fp) == EOF) {
        rtmSetErrorStatus(heli_q8_M, "Error closing MAT-file EulerRates.mat");
        return;
      }

      heli_q8_DW.ToFile6_PWORK.FilePtr = (NULL);
    }
  }

  /* Terminate for ToFile: '<S4>/To File7' */
  {
    FILE *fp = (FILE *) heli_q8_DW.ToFile7_PWORK.FilePtr;
    if (fp != (NULL)) {
      char fileName[509] = "IMU.mat";
      if (fclose(fp) == EOF) {
        rtmSetErrorStatus(heli_q8_M, "Error closing MAT-file IMU.mat");
        return;
      }

      if ((fp = fopen(fileName, "r+b")) == (NULL)) {
        rtmSetErrorStatus(heli_q8_M, "Error reopening MAT-file IMU.mat");
        return;
      }

      if (rt_WriteMat4FileHeader(fp, 6, heli_q8_DW.ToFile7_IWORK.Count, "IMU"))
      {
        rtmSetErrorStatus(heli_q8_M,
                          "Error writing header for IMU to MAT-file IMU.mat");
      }

      if (fclose(fp) == EOF) {
        rtmSetErrorStatus(heli_q8_M, "Error closing MAT-file IMU.mat");
        return;
      }

      heli_q8_DW.ToFile7_PWORK.FilePtr = (NULL);
    }
  }

  /* Terminate for ToFile: '<S4>/To File8' */
  {
    FILE *fp = (FILE *) heli_q8_DW.ToFile8_PWORK.FilePtr;
    if (fp != (NULL)) {
      char fileName[509] = "NoEncoder.mat";
      if (fclose(fp) == EOF) {
        rtmSetErrorStatus(heli_q8_M, "Error closing MAT-file NoEncoder.mat");
        return;
      }

      if ((fp = fopen(fileName, "r+b")) == (NULL)) {
        rtmSetErrorStatus(heli_q8_M, "Error reopening MAT-file NoEncoder.mat");
        return;
      }

      if (rt_WriteMat4FileHeader(fp, 4, heli_q8_DW.ToFile8_IWORK.Count,
           "NoEncoder")) {
        rtmSetErrorStatus(heli_q8_M,
                          "Error writing header for NoEncoder to MAT-file NoEncoder.mat");
      }

      if (fclose(fp) == EOF) {
        rtmSetErrorStatus(heli_q8_M, "Error closing MAT-file NoEncoder.mat");
        return;
      }

      heli_q8_DW.ToFile8_PWORK.FilePtr = (NULL);
    }
  }

  /* Terminate for ToFile: '<S5>/To File' */
  {
    FILE *fp = (FILE *) heli_q8_DW.ToFile_PWORK.FilePtr;
    if (fp != (NULL)) {
      char fileName[509] = "elevation_rate.mat";
      if (fclose(fp) == EOF) {
        rtmSetErrorStatus(heli_q8_M, "Error closing MAT-file elevation_rate.mat");
        return;
      }

      if ((fp = fopen(fileName, "r+b")) == (NULL)) {
        rtmSetErrorStatus(heli_q8_M,
                          "Error reopening MAT-file elevation_rate.mat");
        return;
      }

      if (rt_WriteMat4FileHeader(fp, 3, heli_q8_DW.ToFile_IWORK.Count,
           "elevation_rate")) {
        rtmSetErrorStatus(heli_q8_M,
                          "Error writing header for elevation_rate to MAT-file elevation_rate.mat");
      }

      if (fclose(fp) == EOF) {
        rtmSetErrorStatus(heli_q8_M, "Error closing MAT-file elevation_rate.mat");
        return;
      }

      heli_q8_DW.ToFile_PWORK.FilePtr = (NULL);
    }
  }

  /* Terminate for ToFile: '<S5>/To File1' */
  {
    FILE *fp = (FILE *) heli_q8_DW.ToFile1_PWORK_h.FilePtr;
    if (fp != (NULL)) {
      char fileName[509] = "pitch.mat";
      if (fclose(fp) == EOF) {
        rtmSetErrorStatus(heli_q8_M, "Error closing MAT-file pitch.mat");
        return;
      }

      if ((fp = fopen(fileName, "r+b")) == (NULL)) {
        rtmSetErrorStatus(heli_q8_M, "Error reopening MAT-file pitch.mat");
        return;
      }

      if (rt_WriteMat4FileHeader(fp, 3, heli_q8_DW.ToFile1_IWORK_p.Count,
           "pitch")) {
        rtmSetErrorStatus(heli_q8_M,
                          "Error writing header for pitch to MAT-file pitch.mat");
      }

      if (fclose(fp) == EOF) {
        rtmSetErrorStatus(heli_q8_M, "Error closing MAT-file pitch.mat");
        return;
      }

      heli_q8_DW.ToFile1_PWORK_h.FilePtr = (NULL);
    }
  }

  /* Terminate for S-Function (game_controller_block): '<S10>/Game Controller' */

  /* S-Function Block: heli_q8/Subsystem/Joystick/Game Controller (game_controller_block) */
  {
    if (heli_q8_P.GameController_Enabled) {
      game_controller_close(heli_q8_DW.GameController_Controller);
      heli_q8_DW.GameController_Controller = NULL;
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
  if (tid == 1)
    tid = 0;
  heli_q8_output(tid);
}

void MdlUpdate(int_T tid)
{
  if (tid == 1)
    tid = 0;
  heli_q8_update(tid);
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
  heli_q8_initialize();
}

void MdlTerminate(void)
{
  heli_q8_terminate();
}

/* Registration function */
RT_MODEL_heli_q8_T *heli_q8(void)
{
  /* Registration code */

  /* initialize non-finites */
  rt_InitInfAndNaN(sizeof(real_T));

  /* initialize real-time model */
  (void) memset((void *)heli_q8_M, 0,
                sizeof(RT_MODEL_heli_q8_T));

  {
    /* Setup solver object */
    rtsiSetSimTimeStepPtr(&heli_q8_M->solverInfo, &heli_q8_M->Timing.simTimeStep);
    rtsiSetTPtr(&heli_q8_M->solverInfo, &rtmGetTPtr(heli_q8_M));
    rtsiSetStepSizePtr(&heli_q8_M->solverInfo, &heli_q8_M->Timing.stepSize0);
    rtsiSetdXPtr(&heli_q8_M->solverInfo, &heli_q8_M->ModelData.derivs);
    rtsiSetContStatesPtr(&heli_q8_M->solverInfo, (real_T **)
                         &heli_q8_M->ModelData.contStates);
    rtsiSetNumContStatesPtr(&heli_q8_M->solverInfo,
      &heli_q8_M->Sizes.numContStates);
    rtsiSetNumPeriodicContStatesPtr(&heli_q8_M->solverInfo,
      &heli_q8_M->Sizes.numPeriodicContStates);
    rtsiSetPeriodicContStateIndicesPtr(&heli_q8_M->solverInfo,
      &heli_q8_M->ModelData.periodicContStateIndices);
    rtsiSetPeriodicContStateRangesPtr(&heli_q8_M->solverInfo,
      &heli_q8_M->ModelData.periodicContStateRanges);
    rtsiSetErrorStatusPtr(&heli_q8_M->solverInfo, (&rtmGetErrorStatus(heli_q8_M)));
    rtsiSetRTModelPtr(&heli_q8_M->solverInfo, heli_q8_M);
  }

  rtsiSetSimTimeStep(&heli_q8_M->solverInfo, MAJOR_TIME_STEP);
  heli_q8_M->ModelData.intgData.f[0] = heli_q8_M->ModelData.odeF[0];
  heli_q8_M->ModelData.contStates = ((real_T *) &heli_q8_X);
  rtsiSetSolverData(&heli_q8_M->solverInfo, (void *)
                    &heli_q8_M->ModelData.intgData);
  rtsiSetSolverName(&heli_q8_M->solverInfo,"ode1");

  /* Initialize timing info */
  {
    int_T *mdlTsMap = heli_q8_M->Timing.sampleTimeTaskIDArray;
    mdlTsMap[0] = 0;
    mdlTsMap[1] = 1;
    mdlTsMap[2] = 2;
    heli_q8_M->Timing.sampleTimeTaskIDPtr = (&mdlTsMap[0]);
    heli_q8_M->Timing.sampleTimes = (&heli_q8_M->Timing.sampleTimesArray[0]);
    heli_q8_M->Timing.offsetTimes = (&heli_q8_M->Timing.offsetTimesArray[0]);

    /* task periods */
    heli_q8_M->Timing.sampleTimes[0] = (0.0);
    heli_q8_M->Timing.sampleTimes[1] = (0.002);
    heli_q8_M->Timing.sampleTimes[2] = (0.01);

    /* task offsets */
    heli_q8_M->Timing.offsetTimes[0] = (0.0);
    heli_q8_M->Timing.offsetTimes[1] = (0.0);
    heli_q8_M->Timing.offsetTimes[2] = (0.0);
  }

  rtmSetTPtr(heli_q8_M, &heli_q8_M->Timing.tArray[0]);

  {
    int_T *mdlSampleHits = heli_q8_M->Timing.sampleHitArray;
    int_T *mdlPerTaskSampleHits = heli_q8_M->Timing.perTaskSampleHitsArray;
    heli_q8_M->Timing.perTaskSampleHits = (&mdlPerTaskSampleHits[0]);
    mdlSampleHits[0] = 1;
    heli_q8_M->Timing.sampleHits = (&mdlSampleHits[0]);
  }

  rtmSetTFinal(heli_q8_M, -1);
  heli_q8_M->Timing.stepSize0 = 0.002;
  heli_q8_M->Timing.stepSize1 = 0.002;
  heli_q8_M->Timing.stepSize2 = 0.01;

  /* External mode info */
  heli_q8_M->Sizes.checksums[0] = (3368685337U);
  heli_q8_M->Sizes.checksums[1] = (1366901922U);
  heli_q8_M->Sizes.checksums[2] = (568905221U);
  heli_q8_M->Sizes.checksums[3] = (2925179478U);

  {
    static const sysRanDType rtAlwaysEnabled = SUBSYS_RAN_BC_ENABLE;
    static RTWExtModeInfo rt_ExtModeInfo;
    static const sysRanDType *systemRan[10];
    heli_q8_M->extModeInfo = (&rt_ExtModeInfo);
    rteiSetSubSystemActiveVectorAddresses(&rt_ExtModeInfo, systemRan);
    systemRan[0] = &rtAlwaysEnabled;
    systemRan[1] = &rtAlwaysEnabled;
    systemRan[2] = &rtAlwaysEnabled;
    systemRan[3] = &rtAlwaysEnabled;
    systemRan[4] = &rtAlwaysEnabled;
    systemRan[5] = &rtAlwaysEnabled;
    systemRan[6] = &rtAlwaysEnabled;
    systemRan[7] = &rtAlwaysEnabled;
    systemRan[8] = &rtAlwaysEnabled;
    systemRan[9] = &rtAlwaysEnabled;
    rteiSetModelMappingInfoPtr(heli_q8_M->extModeInfo,
      &heli_q8_M->SpecialInfo.mappingInfo);
    rteiSetChecksumsPtr(heli_q8_M->extModeInfo, heli_q8_M->Sizes.checksums);
    rteiSetTPtr(heli_q8_M->extModeInfo, rtmGetTPtr(heli_q8_M));
  }

  heli_q8_M->solverInfoPtr = (&heli_q8_M->solverInfo);
  heli_q8_M->Timing.stepSize = (0.002);
  rtsiSetFixedStepSize(&heli_q8_M->solverInfo, 0.002);
  rtsiSetSolverMode(&heli_q8_M->solverInfo, SOLVER_MODE_MULTITASKING);

  /* block I/O */
  heli_q8_M->ModelData.blockIO = ((void *) &heli_q8_B);
  (void) memset(((void *) &heli_q8_B), 0,
                sizeof(B_heli_q8_T));

  {
    int32_T i;
    for (i = 0; i < 5; i++) {
      heli_q8_B.Integrator2[i] = 0.0;
    }

    for (i = 0; i < 5; i++) {
      heli_q8_B.ManualSwitch2[i] = 0.0;
    }

    for (i = 0; i < 10; i++) {
      heli_q8_B.Switch[i] = 0.0;
    }

    for (i = 0; i < 5; i++) {
      heli_q8_B.Sum5[i] = 0.0;
    }

    heli_q8_B.PitchCounttorad = 0.0;
    heli_q8_B.PitchTransferFcn = 0.0;
    heli_q8_B.ElevationCounttorad = 0.0;
    heli_q8_B.Sum1 = 0.0;
    heli_q8_B.ElevationTransferFcn = 0.0;
    heli_q8_B.TravelCounttorad = 0.0;
    heli_q8_B.TravelTransferFcn = 0.0;
    heli_q8_B.Constant = 0.0;
    heli_q8_B.RateTransitionx = 0.0;
    heli_q8_B.Joystick_gain_x = 0.0;
    heli_q8_B.ManualSwitch = 0.0;
    heli_q8_B.RateTransitiony = 0.0;
    heli_q8_B.Joystick_gain_y = 0.0;
    heli_q8_B.ManualSwitch1 = 0.0;
    heli_q8_B.FrontmotorSaturation = 0.0;
    heli_q8_B.BackmotorSaturation = 0.0;
    heli_q8_B.Switch1 = 0.0;
    heli_q8_B.Switch2 = 0.0;
    heli_q8_B.ManualSwitch_k[0] = 0.0;
    heli_q8_B.ManualSwitch_k[1] = 0.0;
    heli_q8_B.ManualSwitch_k[2] = 0.0;
    heli_q8_B.GameController_o4 = 0.0;
    heli_q8_B.GameController_o5 = 0.0;
    heli_q8_B.Sum3 = 0.0;
    heli_q8_B.Sum4 = 0.0;
    heli_q8_B.sf_Gyrovectortopitchrateeleva_f.euler_rates[0] = 0.0;
    heli_q8_B.sf_Gyrovectortopitchrateeleva_f.euler_rates[1] = 0.0;
    heli_q8_B.sf_Gyrovectortopitchrateeleva_f.euler_rates[2] = 0.0;
    heli_q8_B.sf_Gyrovectortopitchrateelevati.euler_rates[0] = 0.0;
    heli_q8_B.sf_Gyrovectortopitchrateelevati.euler_rates[1] = 0.0;
    heli_q8_B.sf_Gyrovectortopitchrateelevati.euler_rates[2] = 0.0;
  }

  /* parameters */
  heli_q8_M->ModelData.defaultParam = ((real_T *)&heli_q8_P);

  /* states (continuous) */
  {
    real_T *x = (real_T *) &heli_q8_X;
    heli_q8_M->ModelData.contStates = (x);
    (void) memset((void *)&heli_q8_X, 0,
                  sizeof(X_heli_q8_T));
  }

  /* states (dwork) */
  heli_q8_M->ModelData.dwork = ((void *) &heli_q8_DW);
  (void) memset((void *)&heli_q8_DW, 0,
                sizeof(DW_heli_q8_T));

  {
    int32_T i;
    for (i = 0; i < 8; i++) {
      heli_q8_DW.HILInitialize_AIMinimums[i] = 0.0;
    }
  }

  {
    int32_T i;
    for (i = 0; i < 8; i++) {
      heli_q8_DW.HILInitialize_AIMaximums[i] = 0.0;
    }
  }

  {
    int32_T i;
    for (i = 0; i < 8; i++) {
      heli_q8_DW.HILInitialize_AOMinimums[i] = 0.0;
    }
  }

  {
    int32_T i;
    for (i = 0; i < 8; i++) {
      heli_q8_DW.HILInitialize_AOMaximums[i] = 0.0;
    }
  }

  {
    int32_T i;
    for (i = 0; i < 8; i++) {
      heli_q8_DW.HILInitialize_AOVoltages[i] = 0.0;
    }
  }

  {
    int32_T i;
    for (i = 0; i < 8; i++) {
      heli_q8_DW.HILInitialize_FilterFrequency[i] = 0.0;
    }
  }

  {
    int32_T i;
    for (i = 0; i < 8; i++) {
      heli_q8_DW.HILInitialize_POSortedFreqs[i] = 0.0;
    }
  }

  {
    int32_T i;
    for (i = 0; i < 8; i++) {
      heli_q8_DW.HILInitialize_POValues[i] = 0.0;
    }
  }

  heli_q8_DW.RateTransitionx_Buffer0 = 0.0;
  heli_q8_DW.RateTransitiony_Buffer0 = 0.0;
  heli_q8_DW.HILWriteAnalog_Buffer[0] = 0.0;
  heli_q8_DW.HILWriteAnalog_Buffer[1] = 0.0;

  {
    int32_T i;
    for (i = 0; i < 10; i++) {
      heli_q8_DW.Memory_PreviousInput[i] = 0.0;
    }
  }

  /* data type transition information */
  {
    static DataTypeTransInfo dtInfo;
    (void) memset((char_T *) &dtInfo, 0,
                  sizeof(dtInfo));
    heli_q8_M->SpecialInfo.mappingInfo = (&dtInfo);
    dtInfo.numDataTypes = 25;
    dtInfo.dataTypeSizes = &rtDataTypeSizes[0];
    dtInfo.dataTypeNames = &rtDataTypeNames[0];

    /* Block I/O transition table */
    dtInfo.B = &rtBTransTable;

    /* Parameters transition table */
    dtInfo.P = &rtPTransTable;
  }

  /* Initialize Sizes */
  heli_q8_M->Sizes.numContStates = (10);/* Number of continuous states */
  heli_q8_M->Sizes.numPeriodicContStates = (0);/* Number of periodic continuous states */
  heli_q8_M->Sizes.numY = (0);         /* Number of model outputs */
  heli_q8_M->Sizes.numU = (0);         /* Number of model inputs */
  heli_q8_M->Sizes.sysDirFeedThru = (0);/* The model is not direct feedthrough */
  heli_q8_M->Sizes.numSampTimes = (3); /* Number of sample times */
  heli_q8_M->Sizes.numBlocks = (132);  /* Number of blocks */
  heli_q8_M->Sizes.numBlockIO = (30);  /* Number of block outputs */
  heli_q8_M->Sizes.numBlockPrms = (543);/* Sum of parameter "widths" */
  return heli_q8_M;
}

/*========================================================================*
 * End of Classic call interface                                          *
 *========================================================================*/
