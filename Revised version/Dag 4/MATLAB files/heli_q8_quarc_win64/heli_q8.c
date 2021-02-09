/*
 * heli_q8.c
 *
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * Code generation for model "heli_q8".
 *
 * Model version              : 1.101
 * Simulink Coder version : 8.9 (R2015b) 13-Aug-2015
 * C source code generated on : Sat Nov 14 13:44:05 2020
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

/* Forward declaration for local functions */
static void heli_q8_invNxN(const real_T x[25], real_T y[25]);
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

/* Function for MATLAB Function: '<S4>/LabDag4_3Correction' */
static void heli_q8_invNxN(const real_T x[25], real_T y[25])
{
  int8_T p[5];
  real_T A[25];
  int8_T ipiv[5];
  int32_T b_j;
  real_T smax;
  real_T s;
  int32_T iy;
  int32_T c_ix;
  int32_T d;
  int32_T ijA;
  int32_T jBcol;
  int32_T kAcol;
  int32_T c_i;
  for (b_j = 0; b_j < 25; b_j++) {
    y[b_j] = 0.0;
    A[b_j] = x[b_j];
  }

  for (b_j = 0; b_j < 5; b_j++) {
    ipiv[b_j] = (int8_T)(1 + b_j);
  }

  for (b_j = 0; b_j < 4; b_j++) {
    jBcol = b_j * 6;
    iy = 0;
    kAcol = jBcol;
    smax = fabs(A[jBcol]);
    for (c_i = 2; c_i <= 5 - b_j; c_i++) {
      kAcol++;
      s = fabs(A[kAcol]);
      if (s > smax) {
        iy = c_i - 1;
        smax = s;
      }
    }

    if (A[jBcol + iy] != 0.0) {
      if (iy != 0) {
        ipiv[b_j] = (int8_T)((b_j + iy) + 1);
        kAcol = b_j;
        iy += b_j;
        for (c_i = 0; c_i < 5; c_i++) {
          smax = A[kAcol];
          A[kAcol] = A[iy];
          A[iy] = smax;
          kAcol += 5;
          iy += 5;
        }
      }

      iy = (jBcol - b_j) + 5;
      for (kAcol = jBcol + 1; kAcol + 1 <= iy; kAcol++) {
        A[kAcol] /= A[jBcol];
      }
    }

    iy = jBcol;
    kAcol = jBcol + 5;
    for (c_i = 1; c_i <= 4 - b_j; c_i++) {
      smax = A[kAcol];
      if (A[kAcol] != 0.0) {
        c_ix = jBcol + 1;
        d = (iy - b_j) + 10;
        for (ijA = 6 + iy; ijA + 1 <= d; ijA++) {
          A[ijA] += A[c_ix] * -smax;
          c_ix++;
        }
      }

      kAcol += 5;
      iy += 5;
    }
  }

  for (b_j = 0; b_j < 5; b_j++) {
    p[b_j] = (int8_T)(1 + b_j);
  }

  if (ipiv[0] > 1) {
    jBcol = p[ipiv[0] - 1];
    p[ipiv[0] - 1] = p[0];
    p[0] = (int8_T)jBcol;
  }

  if (ipiv[1] > 2) {
    jBcol = p[ipiv[1] - 1];
    p[ipiv[1] - 1] = p[1];
    p[1] = (int8_T)jBcol;
  }

  if (ipiv[2] > 3) {
    jBcol = p[ipiv[2] - 1];
    p[ipiv[2] - 1] = p[2];
    p[2] = (int8_T)jBcol;
  }

  if (ipiv[3] > 4) {
    jBcol = p[ipiv[3] - 1];
    p[ipiv[3] - 1] = p[3];
    p[3] = (int8_T)jBcol;
  }

  for (b_j = 0; b_j < 5; b_j++) {
    jBcol = p[b_j] - 1;
    y[b_j + 5 * (p[b_j] - 1)] = 1.0;
    for (iy = b_j; iy + 1 < 6; iy++) {
      if (y[5 * jBcol + iy] != 0.0) {
        for (kAcol = iy + 1; kAcol + 1 < 6; kAcol++) {
          y[kAcol + 5 * jBcol] -= y[5 * jBcol + iy] * A[5 * iy + kAcol];
        }
      }
    }
  }

  for (b_j = 0; b_j < 5; b_j++) {
    jBcol = 5 * b_j;
    for (iy = 4; iy >= 0; iy += -1) {
      kAcol = 5 * iy;
      if (y[iy + jBcol] != 0.0) {
        y[iy + jBcol] /= A[iy + kAcol];
        for (c_i = 0; c_i + 1 <= iy; c_i++) {
          y[c_i + jBcol] -= y[iy + jBcol] * A[c_i + kAcol];
        }
      }
    }
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
  real_T rtb_HILReadEncoderTimebase_o3;
  real_T rtb_TmpSignalConversionAtToFile[6];
  real_T rtb_TmpSignalConversionAtToFi_n[5];
  real_T rtb_TmpSignalConversionAtToF_nc[2];
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
  real_T K[30];
  int8_T I[36];
  int32_T k;
  int8_T b_I[36];
  static const int8_T b[30] = { 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0,
    0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1 };

  static const real_T R_d[25] = { 0.00308334045570657, 0.000889505690261113,
    0.00458158706383691, -0.00208010289555366, 7.47152031805293E-5,
    0.000889505690261113, 0.00106007806656211, 0.000251077821456741,
    -0.000737535109803567, 0.00239816442344825, 0.00458158706383691,
    0.000251077821456741, 0.0109822436698733, -0.00275568957994756,
    -0.000294579518024999, -0.00208010289555366, -0.000737535109803567,
    -0.00275568957994756, 0.00213206756543553, 0.000437760629677585,
    7.47152031805293E-5, 0.00239816442344825, -0.000294579518024999,
    0.000437760629677585, 0.0195556088857044 };

  static const int8_T a[30] = { 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0,
    0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 };

  static const real_T Q_d[36] = { 4.0E-7, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 2.0E-6,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0E-6, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 6.0E-7,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0E-6, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0E-6 };

  static const real_T a_0[36] = { 1.0, 0.0, 0.0, 0.0, 0.0, 0.0012, 0.002, 1.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.002, 1.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.002, 1.0 };

  static const real_T b_a[12] = { 0.0, 0.0, 0.0, 0.0008, 0.0, 0.0, 0.0, 0.001,
    0.0, 0.0, 0.0, 0.0 };

  static const real_T b_0[36] = { 1.0, 0.002, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.002, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 1.0, 0.002, 0.0012, 0.0, 0.0, 0.0, 0.0, 1.0 };

  real_T rtb_e_c_dot;
  real_T rtb_Sum[2];
  int32_T i;
  real_T a_1[25];
  real_T tmp[25];
  real_T tmp_0[9];
  real_T a_2[30];
  real_T tmp_1[5];
  real_T a_3[5];
  real_T tmp_2[5];
  real_T I_0[36];
  real_T I_1[36];
  real_T b_I_0[36];
  real_T K_0[36];
  real_T tmp_3[5];
  real_T tmp_4[2];
  real_T tmp_5[2];
  real_T a_4[6];
  real_T b_a_0[6];
  real_T tmp_6[5];
  int32_T i_0;
  real_T u0;
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
        rtb_HILReadEncoderTimebase_o3 =
          heli_q8_DW.HILReadEncoderTimebase_Buffer[2];
      }
    }

    /* DiscretePulseGenerator: '<Root>/e_c_dot' */
    rtb_e_c_dot = (heli_q8_DW.clockTickCounter < heli_q8_P.e_c_dot_Duty) &&
      (heli_q8_DW.clockTickCounter >= 0) ? heli_q8_P.e_c_dot_Amp : 0.0;
    if (heli_q8_DW.clockTickCounter >= heli_q8_P.e_c_dot_Period - 1.0) {
      heli_q8_DW.clockTickCounter = 0;
    } else {
      heli_q8_DW.clockTickCounter++;
    }

    /* End of DiscretePulseGenerator: '<Root>/e_c_dot' */

    /* RateTransition: '<S3>/Rate Transition: y' */
    if (heli_q8_M->Timing.RateInteraction.TID1_2) {
      heli_q8_B.RateTransitiony = heli_q8_DW.RateTransitiony_Buffer0;
    }

    /* End of RateTransition: '<S3>/Rate Transition: y' */

    /* DeadZone: '<S3>/Dead Zone: y' */
    if (heli_q8_B.RateTransitiony > heli_q8_P.DeadZoney_End) {
      u0 = heli_q8_B.RateTransitiony - heli_q8_P.DeadZoney_End;
    } else if (heli_q8_B.RateTransitiony >= heli_q8_P.DeadZoney_Start) {
      u0 = 0.0;
    } else {
      u0 = heli_q8_B.RateTransitiony - heli_q8_P.DeadZoney_Start;
    }

    /* End of DeadZone: '<S3>/Dead Zone: y' */

    /* Gain: '<S3>/Joystick_gain_y' incorporates:
     *  Gain: '<S3>/Gain: y'
     */
    heli_q8_B.Joystick_gain_y = heli_q8_P.Gainy_Gain * u0 *
      heli_q8_P.Joystick_gain_y;

    /* ManualSwitch: '<Root>/Manual Switch3' incorporates:
     *  Gain: '<Root>/Gain5'
     */
    if (heli_q8_P.ManualSwitch3_CurrentSetting == 1) {
      heli_q8_B.ManualSwitch3 = heli_q8_P.Gain5_Gain * rtb_e_c_dot;
    } else {
      heli_q8_B.ManualSwitch3 = heli_q8_B.Joystick_gain_y;
    }

    /* End of ManualSwitch: '<Root>/Manual Switch3' */

    /* S-Function (stream_call_block): '<S11>/Stream Call1' */

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

    /* S-Function (stream_formatted_write_block): '<S11>/Stream Formatted Write' */
    {
      t_error result;
      if (rtb_StreamCall1_o1 != NULL) {
        result = stream_print_utf8_char_array(*rtb_StreamCall1_o1,
          heli_q8_P.StreamFormattedWrite_MaxUnits, &rtb_StreamFormattedWrite_o2,
          "%c\n"
          , (char) heli_q8_P.Constant1_Value
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

    /* S-Function (stream_read_block): '<S11>/Stream Read1' */
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

    /* Switch: '<S11>/Switch' incorporates:
     *  DataTypeConversion: '<S11>/Data Type Conversion'
     *  Memory: '<S11>/Memory'
     */
    for (i = 0; i < 10; i++) {
      if (rtb_StreamRead1_o3) {
        heli_q8_B.Switch[i] = rtb_StreamRead1_o2[i];
      } else {
        heli_q8_B.Switch[i] = heli_q8_DW.Memory_PreviousInput[i];
      }
    }

    /* End of Switch: '<S11>/Switch' */

    /* Gain: '<S11>/Gain2' */
    for (i = 0; i < 3; i++) {
      rtb_Gain2[i] = 0.0;
      rtb_Gain2[i] += heli_q8_P.Gain2_Gain[i] * heli_q8_B.Switch[0];
      rtb_Gain2[i] += heli_q8_P.Gain2_Gain[i + 3] * heli_q8_B.Switch[1];
      rtb_Gain2[i] += heli_q8_P.Gain2_Gain[i + 6] * heli_q8_B.Switch[2];
    }

    /* End of Gain: '<S11>/Gain2' */

    /* Switch: '<S12>/Switch1' incorporates:
     *  Constant: '<S12>/Constant2'
     *  Product: '<S12>/Divide'
     *  Trigonometry: '<S12>/Trigonometric Function'
     */
    if (rtb_Gain2[2] != 0.0) {
      heli_q8_B.Switch1 = atan(rtb_Gain2[1] / rtb_Gain2[2]);
    } else {
      heli_q8_B.Switch1 = heli_q8_P.Constant2_Value_f;
    }

    /* End of Switch: '<S12>/Switch1' */

    /* Gain: '<S11>/Gain1' */
    for (i = 0; i < 3; i++) {
      rtb_Gain1[i] = 0.0;
      rtb_Gain1[i] += heli_q8_P.Gain1_Gain[i] * heli_q8_B.Switch[3];
      rtb_Gain1[i] += heli_q8_P.Gain1_Gain[i + 3] * heli_q8_B.Switch[4];
      rtb_Gain1[i] += heli_q8_P.Gain1_Gain[i + 6] * heli_q8_B.Switch[5];
    }

    /* End of Gain: '<S11>/Gain1' */

    /* Gain: '<S2>/Pitch: Count to rad' */
    heli_q8_B.PitchCounttorad = heli_q8_P.PitchCounttorad_Gain *
      rtb_HILReadEncoderTimebase_o2;

    /* Gain: '<S2>/Elevation: Count to rad' */
    heli_q8_B.ElevationCounttorad = heli_q8_P.ElevationCounttorad_Gain *
      rtb_HILReadEncoderTimebase_o3;

    /* Sum: '<Root>/Sum1' incorporates:
     *  Constant: '<Root>/Constant1'
     */
    heli_q8_B.Sum1 = heli_q8_B.ElevationCounttorad - heli_q8_P.Constant1_Value_l;

    /* MATLAB Function: '<S6>/Gyro vector to [pitch rate, elevation rate, travle rate]' incorporates:
     *  SignalConversion: '<S10>/TmpSignal ConversionAt SFunction Inport2'
     */
    /* MATLAB Function 'Math logic/Gyro vector to [pitch rate, elevation rate, travle rate]': '<S10>:1' */
    /* '<S10>:1:3' */
    /* '<S10>:1:4' */
    /* psi = euler_angles(3); */
    /* '<S10>:1:8' */
    /* '<S10>:1:11' */
    tmp_0[0] = 1.0;
    tmp_0[3] = sin(heli_q8_B.PitchCounttorad) * tan(heli_q8_B.Sum1);
    tmp_0[6] = cos(heli_q8_B.PitchCounttorad) * tan(heli_q8_B.Sum1);
    tmp_0[1] = 0.0;
    tmp_0[4] = cos(heli_q8_B.PitchCounttorad);
    tmp_0[7] = -sin(heli_q8_B.PitchCounttorad);
    tmp_0[2] = 0.0;
    tmp_0[5] = sin(heli_q8_B.PitchCounttorad) / cos(heli_q8_B.Sum1);
    tmp_0[8] = cos(heli_q8_B.PitchCounttorad) / cos(heli_q8_B.Sum1);
    for (i = 0; i < 3; i++) {
      heli_q8_B.euler_rates[i] = 0.0;
      heli_q8_B.euler_rates[i] += tmp_0[i] * rtb_Gain1[0];
      heli_q8_B.euler_rates[i] += tmp_0[i + 3] * rtb_Gain1[1];
      heli_q8_B.euler_rates[i] += tmp_0[i + 6] * rtb_Gain1[2];
    }

    /* End of MATLAB Function: '<S6>/Gyro vector to [pitch rate, elevation rate, travle rate]' */

    /* Sqrt: '<S12>/Sqrt' incorporates:
     *  Math: '<S12>/Math Function'
     *  Math: '<S12>/Math Function1'
     *  Sum: '<S12>/Add'
     */
    rtb_e_c_dot = sqrt(rtb_Gain2[1] * rtb_Gain2[1] + rtb_Gain2[2] * rtb_Gain2[2]);

    /* Switch: '<S12>/Switch2' incorporates:
     *  Constant: '<S12>/Constant3'
     *  Product: '<S12>/Divide1'
     *  Trigonometry: '<S12>/Trigonometric Function1'
     */
    if (rtb_e_c_dot != 0.0) {
      heli_q8_B.Switch2 = atan(rtb_Gain2[0] / rtb_e_c_dot);
    } else {
      heli_q8_B.Switch2 = heli_q8_P.Constant3_Value;
    }

    /* End of Switch: '<S12>/Switch2' */

    /* ManualSwitch: '<S4>/Manual Switch' incorporates:
     *  Constant: '<S4>/Constant2'
     */
    /* MATLAB Function 'Kalman filter/LabDag4_3Correction': '<S8>:1' */
    /*  Vi kan legge inn matriser direkte i input, dersom vi s� trykker p� edit */
    /*  data, kan vi endre den til � lese fra to workspace.  */
    /* '<S8>:1:7' */
    if (heli_q8_P.ManualSwitch_CurrentSetting == 1) {
      u0 = rtb_StreamRead1_o3;
    } else {
      u0 = heli_q8_P.Constant2_Value;
    }

    /* End of ManualSwitch: '<S4>/Manual Switch' */

    /* MATLAB Function: '<S4>/LabDag4_3Correction' incorporates:
     *  UnitDelay: '<S4>/Unit Delay'
     *  UnitDelay: '<S4>/Unit Delay1'
     */
    if (u0 != 0.0) {
      /* '<S8>:1:22' */
      for (i = 0; i < 5; i++) {
        for (i_0 = 0; i_0 < 6; i_0++) {
          a_2[i + 5 * i_0] = 0.0;
          for (k = 0; k < 6; k++) {
            a_2[i + 5 * i_0] += (real_T)a[5 * k + i] *
              heli_q8_DW.UnitDelay1_DSTATE[6 * i_0 + k];
          }
        }
      }

      for (i = 0; i < 5; i++) {
        for (i_0 = 0; i_0 < 5; i_0++) {
          u0 = 0.0;
          for (k = 0; k < 6; k++) {
            u0 += a_2[5 * k + i] * (real_T)b[6 * i_0 + k];
          }

          a_1[i + 5 * i_0] = R_d[5 * i_0 + i] + u0;
        }
      }

      heli_q8_invNxN(a_1, tmp);
      for (i = 0; i < 6; i++) {
        for (i_0 = 0; i_0 < 5; i_0++) {
          a_2[i + 6 * i_0] = 0.0;
          for (k = 0; k < 6; k++) {
            a_2[i + 6 * i_0] += heli_q8_DW.UnitDelay1_DSTATE[6 * k + i] *
              (real_T)b[6 * i_0 + k];
          }
        }
      }

      for (i = 0; i < 6; i++) {
        for (i_0 = 0; i_0 < 5; i_0++) {
          K[i + 6 * i_0] = 0.0;
          for (k = 0; k < 5; k++) {
            K[i + 6 * i_0] += a_2[6 * k + i] * tmp[5 * i_0 + k];
          }
        }
      }

      /* SignalConversion: '<S8>/TmpSignal ConversionAt SFunction Inport4' incorporates:
       *  UnitDelay: '<S4>/Unit Delay1'
       */
      /* '<S8>:1:23' */
      tmp_1[0] = heli_q8_B.Switch1;
      tmp_1[1] = heli_q8_B.euler_rates[0];
      tmp_1[2] = heli_q8_B.Switch2;
      tmp_1[3] = heli_q8_B.euler_rates[1];
      tmp_1[4] = heli_q8_B.euler_rates[2];
      for (i = 0; i < 5; i++) {
        a_3[i] = 0.0;
        for (i_0 = 0; i_0 < 6; i_0++) {
          a_3[i] += (real_T)a[5 * i_0 + i] * heli_q8_DW.UnitDelay_DSTATE[i_0];
        }

        tmp_2[i] = tmp_1[i] - a_3[i];
      }

      for (i = 0; i < 6; i++) {
        u0 = 0.0;
        for (i_0 = 0; i_0 < 5; i_0++) {
          u0 += K[6 * i_0 + i] * tmp_2[i_0];
        }

        heli_q8_B.x_now[i] = heli_q8_DW.UnitDelay_DSTATE[i] + u0;
      }

      /* '<S8>:1:24' */
      for (i = 0; i < 36; i++) {
        I[i] = 0;
      }

      for (k = 0; k < 6; k++) {
        I[k + 6 * k] = 1;
      }

      for (i = 0; i < 36; i++) {
        b_I[i] = 0;
      }

      for (k = 0; k < 6; k++) {
        b_I[k + 6 * k] = 1;
        for (i = 0; i < 6; i++) {
          u0 = 0.0;
          for (i_0 = 0; i_0 < 5; i_0++) {
            u0 += K[6 * i_0 + k] * (real_T)a[5 * i + i_0];
          }

          I_0[k + 6 * i] = (real_T)I[6 * i + k] - u0;
        }
      }

      for (i = 0; i < 6; i++) {
        for (i_0 = 0; i_0 < 6; i_0++) {
          I_1[i + 6 * i_0] = 0.0;
          for (k = 0; k < 6; k++) {
            I_1[i + 6 * i_0] += I_0[6 * k + i] * heli_q8_DW.UnitDelay1_DSTATE[6 *
              i_0 + k];
          }

          u0 = 0.0;
          for (k = 0; k < 5; k++) {
            u0 += K[6 * k + i_0] * (real_T)a[5 * i + k];
          }

          b_I_0[i + 6 * i_0] = (real_T)b_I[6 * i + i_0] - u0;
        }

        for (i_0 = 0; i_0 < 5; i_0++) {
          a_2[i + 6 * i_0] = 0.0;
          for (k = 0; k < 5; k++) {
            a_2[i + 6 * i_0] += K[6 * k + i] * R_d[5 * i_0 + k];
          }
        }
      }

      for (i = 0; i < 6; i++) {
        for (i_0 = 0; i_0 < 6; i_0++) {
          I_0[i + 6 * i_0] = 0.0;
          for (k = 0; k < 6; k++) {
            I_0[i + 6 * i_0] += I_1[6 * k + i] * b_I_0[6 * i_0 + k];
          }

          K_0[i + 6 * i_0] = 0.0;
          for (k = 0; k < 5; k++) {
            K_0[i + 6 * i_0] += a_2[6 * k + i] * K[6 * k + i_0];
          }
        }
      }

      for (i = 0; i < 6; i++) {
        for (i_0 = 0; i_0 < 6; i_0++) {
          heli_q8_B.P_now[i_0 + 6 * i] = I_0[6 * i + i_0] + K_0[6 * i + i_0];
        }
      }
    } else {
      /* '<S8>:1:27' */
      for (i = 0; i < 6; i++) {
        heli_q8_B.x_now[i] = heli_q8_DW.UnitDelay_DSTATE[i];
      }

      /* '<S8>:1:28' */
      memcpy(&heli_q8_B.P_now[0], &heli_q8_DW.UnitDelay1_DSTATE[0], 36U * sizeof
             (real_T));
    }

    /* End of MATLAB Function: '<S4>/LabDag4_3Correction' */
  }

  /* Integrator: '<S5>/Integrator2' */
  for (i = 0; i < 5; i++) {
    heli_q8_B.Integrator2[i] = heli_q8_X.Integrator2_CSTATE[i];
  }

  /* End of Integrator: '<S5>/Integrator2' */

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

  /* ManualSwitch: '<Root>/Manual Switch' */
  if (heli_q8_P.ManualSwitch_CurrentSetting_f == 1) {
    /* ManualSwitch: '<Root>/Manual Switch1' */
    if (heli_q8_P.ManualSwitch1_CurrentSetting == 1) {
      heli_q8_B.ManualSwitch[0] = heli_q8_B.x_now[0];
      heli_q8_B.ManualSwitch[1] = heli_q8_B.x_now[1];
      heli_q8_B.ManualSwitch[2] = heli_q8_B.x_now[2];
      heli_q8_B.ManualSwitch[3] = heli_q8_B.x_now[3];
      heli_q8_B.ManualSwitch[4] = heli_q8_B.x_now[5];
    } else {
      heli_q8_B.ManualSwitch[0] = heli_q8_B.Integrator2[0];
      heli_q8_B.ManualSwitch[1] = heli_q8_B.Integrator2[1];
      heli_q8_B.ManualSwitch[2] = heli_q8_B.Integrator2[2];
      heli_q8_B.ManualSwitch[3] = heli_q8_B.Integrator2[3];
      heli_q8_B.ManualSwitch[4] = heli_q8_B.Integrator2[4];
    }

    /* End of ManualSwitch: '<Root>/Manual Switch1' */
  } else {
    heli_q8_B.ManualSwitch[0] = heli_q8_B.PitchCounttorad;
    heli_q8_B.ManualSwitch[1] = heli_q8_B.PitchTransferFcn;
    heli_q8_B.ManualSwitch[2] = heli_q8_B.Sum1;
    heli_q8_B.ManualSwitch[3] = heli_q8_B.ElevationTransferFcn;
    heli_q8_B.ManualSwitch[4] = heli_q8_B.TravelTransferFcn;
  }

  /* End of ManualSwitch: '<Root>/Manual Switch' */

  /* RateTransition: '<S3>/Rate Transition: x' */
  if (rtmIsMajorTimeStep(heli_q8_M)) {
    /* SignalConversion: '<Root>/TmpSignal ConversionAtTo FileInport1' */
    rtb_TmpSignalConversionAtToF_nc[0] = heli_q8_B.ManualSwitch3;
    rtb_TmpSignalConversionAtToF_nc[1] = heli_q8_B.ManualSwitch[3];

    /* ToFile: '<Root>/To File' */
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

    if (heli_q8_M->Timing.RateInteraction.TID1_2) {
      heli_q8_B.RateTransitionx = heli_q8_DW.RateTransitionx_Buffer0;
    }

    /* DeadZone: '<S3>/Dead Zone: x' */
    if (heli_q8_B.RateTransitionx > heli_q8_P.DeadZonex_End) {
      u0 = heli_q8_B.RateTransitionx - heli_q8_P.DeadZonex_End;
    } else if (heli_q8_B.RateTransitionx >= heli_q8_P.DeadZonex_Start) {
      u0 = 0.0;
    } else {
      u0 = heli_q8_B.RateTransitionx - heli_q8_P.DeadZonex_Start;
    }

    /* End of DeadZone: '<S3>/Dead Zone: x' */

    /* Gain: '<S3>/Joystick_gain_x' incorporates:
     *  Gain: '<S3>/Gain: x'
     */
    heli_q8_B.Joystick_gain_x = heli_q8_P.Gainx_Gain * u0 *
      heli_q8_P.Joystick_gain_x;
  }

  /* End of RateTransition: '<S3>/Rate Transition: x' */

  /* Step: '<S7>/Step1' */
  rtb_e_c_dot = heli_q8_M->Timing.t[0];

  /* Step: '<S7>/Step2' */
  currentTime = heli_q8_M->Timing.t[0];

  /* Step: '<S7>/Step3' */
  currentTime_0 = heli_q8_M->Timing.t[0];

  /* Step: '<S7>/Step4' */
  currentTime_1 = heli_q8_M->Timing.t[0];

  /* Step: '<S7>/Step5' */
  currentTime_2 = heli_q8_M->Timing.t[0];

  /* Step: '<S7>/Step6' */
  currentTime_3 = heli_q8_M->Timing.t[0];

  /* Step: '<S7>/Step7' */
  currentTime_4 = heli_q8_M->Timing.t[0];

  /* ManualSwitch: '<Root>/Manual Switch2' incorporates:
   *  Gain: '<Root>/Gain3'
   *  Sum: '<S7>/Sum1'
   *  Sum: '<S7>/Sum2'
   *  Sum: '<S7>/Sum3'
   *  Sum: '<S7>/Sum4'
   *  Sum: '<S7>/Sum5'
   *  Sum: '<S7>/Sum6'
   *  Sum: '<S7>/Sum7'
   */
  if (heli_q8_P.ManualSwitch2_CurrentSetting == 1) {
    /* Step: '<S7>/Step' */
    if (heli_q8_M->Timing.t[0] < heli_q8_P.Step_Time) {
      u0 = heli_q8_P.Step_Y0;
    } else {
      u0 = heli_q8_P.Step_YFinal;
    }

    /* End of Step: '<S7>/Step' */

    /* Step: '<S7>/Step1' */
    if (rtb_e_c_dot < heli_q8_P.Step1_Time) {
      rtb_e_c_dot = heli_q8_P.Step1_Y0;
    } else {
      rtb_e_c_dot = heli_q8_P.Step1_YFinal;
    }

    /* Step: '<S7>/Step2' */
    if (currentTime < heli_q8_P.Step2_Time) {
      currentTime = heli_q8_P.Step2_Y0;
    } else {
      currentTime = heli_q8_P.Step2_YFinal;
    }

    /* Step: '<S7>/Step3' */
    if (currentTime_0 < heli_q8_P.Step3_Time) {
      currentTime_0 = heli_q8_P.Step3_Y0;
    } else {
      currentTime_0 = heli_q8_P.Step3_YFinal;
    }

    /* Step: '<S7>/Step4' */
    if (currentTime_1 < heli_q8_P.Step4_Time) {
      currentTime_1 = heli_q8_P.Step4_Y0;
    } else {
      currentTime_1 = heli_q8_P.Step4_YFinal;
    }

    /* Step: '<S7>/Step5' */
    if (currentTime_2 < heli_q8_P.Step5_Time) {
      currentTime_2 = heli_q8_P.Step5_Y0;
    } else {
      currentTime_2 = heli_q8_P.Step5_YFinal;
    }

    /* Step: '<S7>/Step6' */
    if (currentTime_3 < heli_q8_P.Step6_Time) {
      currentTime_3 = heli_q8_P.Step6_Y0;
    } else {
      currentTime_3 = heli_q8_P.Step6_YFinal;
    }

    /* Step: '<S7>/Step7' */
    if (currentTime_4 < heli_q8_P.Step7_Time) {
      currentTime_4 = heli_q8_P.Step7_Y0;
    } else {
      currentTime_4 = heli_q8_P.Step7_YFinal;
    }

    heli_q8_B.ManualSwitch2 = ((((0.0 - currentTime) - currentTime_0) + (u0 +
      rtb_e_c_dot)) - ((currentTime_1 - currentTime_2) + (currentTime_3 -
      currentTime_4))) * heli_q8_P.Gain3_Gain;
  } else {
    heli_q8_B.ManualSwitch2 = heli_q8_B.Joystick_gain_x;
  }

  /* End of ManualSwitch: '<Root>/Manual Switch2' */
  if (rtmIsMajorTimeStep(heli_q8_M)) {
    /* SignalConversion: '<Root>/TmpSignal ConversionAtTo File1Inport1' */
    rtb_TmpSignalConversionAtToF_nc[0] = heli_q8_B.ManualSwitch2;
    rtb_TmpSignalConversionAtToF_nc[1] = heli_q8_B.ManualSwitch[0];

    /* ToFile: '<Root>/To File1' */
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
              rtmSetErrorStatus(heli_q8_M, "Error writing to MAT-file pitch.mat");
              return;
            }

            if (((++heli_q8_DW.ToFile1_IWORK.Count)*3)+1 >= 100000000) {
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

    /* Constant: '<Root>/Constant' */
    heli_q8_B.Constant = heli_q8_P.V_0;
  }

  /* SignalConversion: '<Root>/TmpSignal ConversionAtGain1Inport1' incorporates:
   *  Gain: '<Root>/Gain1'
   *  Integrator: '<Root>/Integrator'
   *  Integrator: '<Root>/Integrator1'
   */
  tmp_3[2] = heli_q8_B.ManualSwitch[3];
  tmp_3[3] = heli_q8_X.Integrator_CSTATE;
  tmp_3[4] = heli_q8_X.Integrator1_CSTATE;
  tmp_3[0] = heli_q8_B.ManualSwitch[0];

  /* Gain: '<Root>/Gain2' incorporates:
   *  SignalConversion: '<Root>/TmpSignal ConversionAtGain2Inport1'
   *  Sum: '<Root>/Sum'
   */
  tmp_4[0] = heli_q8_P.F[0] * heli_q8_B.ManualSwitch2 + heli_q8_P.F[2] *
    heli_q8_B.ManualSwitch3;

  /* SignalConversion: '<Root>/TmpSignal ConversionAtGain1Inport1' incorporates:
   *  Gain: '<Root>/Gain1'
   */
  tmp_3[1] = heli_q8_B.ManualSwitch[1];

  /* Gain: '<Root>/Gain2' incorporates:
   *  SignalConversion: '<Root>/TmpSignal ConversionAtGain2Inport1'
   *  Sum: '<Root>/Sum'
   */
  tmp_4[1] = heli_q8_P.F[1] * heli_q8_B.ManualSwitch2;
  tmp_4[1] += heli_q8_P.F[3] * heli_q8_B.ManualSwitch3;
  for (i = 0; i < 2; i++) {
    /* Gain: '<Root>/Gain1' incorporates:
     *  Sum: '<Root>/Sum'
     */
    tmp_5[i] = 0.0;
    for (i_0 = 0; i_0 < 5; i_0++) {
      tmp_5[i] += heli_q8_P.K[(i_0 << 1) + i] * tmp_3[i_0];
    }

    /* Sum: '<Root>/Sum' */
    rtb_Sum[i] = tmp_4[i] - tmp_5[i];
  }

  /* Sum: '<Root>/Sum2' */
  rtb_e_c_dot = rtb_Sum[0] + heli_q8_B.Constant;
  if (rtmIsMajorTimeStep(heli_q8_M)) {
  }

  /* Gain: '<S1>/Front gain' incorporates:
   *  Sum: '<S1>/Add'
   */
  u0 = (rtb_e_c_dot - rtb_Sum[1]) * heli_q8_P.Frontgain_Gain;

  /* Saturate: '<S2>/Front motor: Saturation' */
  if (u0 > heli_q8_P.FrontmotorSaturation_UpperSat) {
    heli_q8_B.FrontmotorSaturation = heli_q8_P.FrontmotorSaturation_UpperSat;
  } else if (u0 < heli_q8_P.FrontmotorSaturation_LowerSat) {
    heli_q8_B.FrontmotorSaturation = heli_q8_P.FrontmotorSaturation_LowerSat;
  } else {
    heli_q8_B.FrontmotorSaturation = u0;
  }

  /* End of Saturate: '<S2>/Front motor: Saturation' */

  /* Gain: '<S1>/Back gain' incorporates:
   *  Sum: '<S1>/Subtract'
   */
  u0 = (rtb_e_c_dot + rtb_Sum[1]) * heli_q8_P.Backgain_Gain;

  /* Saturate: '<S2>/Back motor: Saturation' */
  if (u0 > heli_q8_P.BackmotorSaturation_UpperSat) {
    heli_q8_B.BackmotorSaturation = heli_q8_P.BackmotorSaturation_UpperSat;
  } else if (u0 < heli_q8_P.BackmotorSaturation_LowerSat) {
    heli_q8_B.BackmotorSaturation = heli_q8_P.BackmotorSaturation_LowerSat;
  } else {
    heli_q8_B.BackmotorSaturation = u0;
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

    /* ToFile: '<S4>/To File2' */
    if (rtmIsMajorTimeStep(heli_q8_M)) {
      {
        if (!(++heli_q8_DW.ToFile2_IWORK.Decimation % 1) &&
            (heli_q8_DW.ToFile2_IWORK.Count*7)+1 < 100000000 ) {
          FILE *fp = (FILE *) heli_q8_DW.ToFile2_PWORK.FilePtr;
          if (fp != (NULL)) {
            real_T u[7];
            heli_q8_DW.ToFile2_IWORK.Decimation = 0;
            u[0] = heli_q8_M->Timing.t[1];
            u[1] = heli_q8_B.x_now[0];
            u[2] = heli_q8_B.x_now[1];
            u[3] = heli_q8_B.x_now[2];
            u[4] = heli_q8_B.x_now[3];
            u[5] = heli_q8_B.x_now[4];
            u[6] = heli_q8_B.x_now[5];
            if (fwrite(u, sizeof(real_T), 7, fp) != 7) {
              rtmSetErrorStatus(heli_q8_M,
                                "Error writing to MAT-file Kalman.mat");
              return;
            }

            if (((++heli_q8_DW.ToFile2_IWORK.Count)*7)+1 >= 100000000) {
              (void)fprintf(stdout,
                            "*** The ToFile block will stop logging data before\n"
                            "    the simulation has ended, because it has reached\n"
                            "    the maximum number of elements (100000000)\n"
                            "    allowed in MAT-file Kalman.mat.\n");
            }
          }
        }
      }
    }
  }

  /* MATLAB Function: '<S4>/LabDag4_3Predition' */
  /* MATLAB Function 'Kalman filter/LabDag4_3Predition': '<S9>:1' */
  /* '<S9>:1:18' */
  /* Tuning2 */
  /*   */
  /*  Q_d =[0.000004 0 0 0 0 0; */
  /*        0 0.000004 0 0 0 0;  */
  /*        0 0 0.000005 0 0 0;         */
  /*        0 0 0 0.0000003 0 0;  */
  /*        0 0 0 0 0.000006 0; */
  /*        0 0 0 0 0 0.000007];  */
  /* '<S9>:1:34' */
  /* '<S9>:1:35' */
  for (i = 0; i < 6; i++) {
    a_4[i] = 0.0;
    b_a_0[i] = 0.0;
    b_a_0[i] += b_a[i] * rtb_Sum[0];
    b_a_0[i] += b_a[i + 6] * rtb_Sum[1];
    for (i_0 = 0; i_0 < 6; i_0++) {
      a_4[i] += a_0[6 * i_0 + i] * heli_q8_B.x_now[i_0];
      I_0[i + 6 * i_0] = 0.0;
      for (k = 0; k < 6; k++) {
        I_0[i + 6 * i_0] += a_0[6 * k + i] * heli_q8_B.P_now[6 * i_0 + k];
      }
    }

    heli_q8_B.x_future[i] = a_4[i] + b_a_0[i];
  }

  for (i = 0; i < 6; i++) {
    for (i_0 = 0; i_0 < 6; i_0++) {
      u0 = 0.0;
      for (k = 0; k < 6; k++) {
        u0 += I_0[6 * k + i] * b_0[6 * i_0 + k];
      }

      heli_q8_B.P_future[i + 6 * i_0] = Q_d[6 * i_0 + i] + u0;
    }
  }

  /* End of MATLAB Function: '<S4>/LabDag4_3Predition' */
  if (rtmIsMajorTimeStep(heli_q8_M)) {
    /* ToFile: '<S5>/To File2' */
    if (rtmIsMajorTimeStep(heli_q8_M)) {
      {
        if (!(++heli_q8_DW.ToFile2_IWORK_m.Decimation % 1) &&
            (heli_q8_DW.ToFile2_IWORK_m.Count*6)+1 < 100000000 ) {
          FILE *fp = (FILE *) heli_q8_DW.ToFile2_PWORK_k.FilePtr;
          if (fp != (NULL)) {
            real_T u[6];
            heli_q8_DW.ToFile2_IWORK_m.Decimation = 0;
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

            if (((++heli_q8_DW.ToFile2_IWORK_m.Count)*6)+1 >= 100000000) {
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
  }

  /* Sum: '<S5>/Sum6' */
  tmp_6[0] = heli_q8_B.Switch1;
  tmp_6[1] = heli_q8_B.euler_rates[0];
  tmp_6[2] = heli_q8_B.Switch2;
  tmp_6[3] = heli_q8_B.euler_rates[1];
  tmp_6[4] = heli_q8_B.euler_rates[2];
  for (i = 0; i < 5; i++) {
    /* Gain: '<S5>/Gain6' incorporates:
     *  Sum: '<S5>/Sum5'
     */
    tmp_1[i] = 0.0;
    for (i_0 = 0; i_0 < 5; i_0++) {
      tmp_1[i] += heli_q8_P.A_2[5 * i_0 + i] * heli_q8_B.Integrator2[i_0];
    }

    /* End of Gain: '<S5>/Gain6' */

    /* Gain: '<S5>/Gain' incorporates:
     *  Sum: '<S5>/Sum5'
     */
    tmp_3[i] = 0.0;
    tmp_3[i] += heli_q8_P.B_2[i] * rtb_Sum[0];
    tmp_3[i] += heli_q8_P.B_2[i + 5] * rtb_Sum[1];

    /* Sum: '<S5>/Sum6' incorporates:
     *  Gain: '<S5>/Gain4'
     */
    tmp_2[i] = tmp_6[i] - heli_q8_B.Integrator2[i];
  }

  /* Sum: '<S5>/Sum5' incorporates:
   *  Gain: '<S5>/Gain4'
   */
  for (i = 0; i < 5; i++) {
    u0 = 0.0;
    for (i_0 = 0; i_0 < 5; i_0++) {
      u0 += heli_q8_P.Gain4_Gain[5 * i_0 + i] * tmp_2[i_0];
    }

    heli_q8_B.Sum5[i] = (tmp_1[i] + tmp_3[i]) + u0;
  }

  if (rtmIsMajorTimeStep(heli_q8_M)) {
    /* ToFile: '<S6>/To File4' */
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

    /* ToFile: '<S6>/To File5' */
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

    /* ToFile: '<S6>/To File6' */
    if (rtmIsMajorTimeStep(heli_q8_M)) {
      {
        if (!(++heli_q8_DW.ToFile6_IWORK.Decimation % 1) &&
            (heli_q8_DW.ToFile6_IWORK.Count*4)+1 < 100000000 ) {
          FILE *fp = (FILE *) heli_q8_DW.ToFile6_PWORK.FilePtr;
          if (fp != (NULL)) {
            real_T u[4];
            heli_q8_DW.ToFile6_IWORK.Decimation = 0;
            u[0] = heli_q8_M->Timing.t[1];
            u[1] = heli_q8_B.euler_rates[0];
            u[2] = heli_q8_B.euler_rates[1];
            u[3] = heli_q8_B.euler_rates[2];
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

    /* SignalConversion: '<S6>/TmpSignal ConversionAtTo File7Inport1' */
    rtb_TmpSignalConversionAtToFi_n[0] = heli_q8_B.Switch1;
    rtb_TmpSignalConversionAtToFi_n[1] = heli_q8_B.euler_rates[0];
    rtb_TmpSignalConversionAtToFi_n[2] = heli_q8_B.Switch2;
    rtb_TmpSignalConversionAtToFi_n[3] = heli_q8_B.euler_rates[1];
    rtb_TmpSignalConversionAtToFi_n[4] = heli_q8_B.euler_rates[2];

    /* ToFile: '<S6>/To File7' */
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
              rtmSetErrorStatus(heli_q8_M,
                                "Error writing to MAT-file Measurement.mat");
              return;
            }

            if (((++heli_q8_DW.ToFile7_IWORK.Count)*6)+1 >= 100000000) {
              (void)fprintf(stdout,
                            "*** The ToFile block will stop logging data before\n"
                            "    the simulation has ended, because it has reached\n"
                            "    the maximum number of elements (100000000)\n"
                            "    allowed in MAT-file Measurement.mat.\n");
            }
          }
        }
      }
    }

    /* S-Function (stop_with_error_block): '<S11>/Stop with Call Error' */

    /* S-Function Block: heli_q8/Math logic/IMU/Stop with Call Error (stop_with_error_block) */
    {
      if (rtb_StreamCall1_o3 < 0) {
        msg_get_error_messageA(NULL, rtb_StreamCall1_o3, _rt_error_message,
          sizeof(_rt_error_message));
        rtmSetErrorStatus(heli_q8_M, _rt_error_message);
        return;
      }
    }

    /* S-Function (stop_with_error_block): '<S11>/Stop with Read Error' */

    /* S-Function Block: heli_q8/Math logic/IMU/Stop with Read Error (stop_with_error_block) */
    {
      if (rtb_StreamRead1_o5 < 0) {
        msg_get_error_messageA(NULL, rtb_StreamRead1_o5, _rt_error_message,
          sizeof(_rt_error_message));
        rtmSetErrorStatus(heli_q8_M, _rt_error_message);
        return;
      }
    }
  }

  /* Sum: '<Root>/Sum3' */
  heli_q8_B.Sum3 = heli_q8_B.ManualSwitch[0] - heli_q8_B.ManualSwitch2;

  /* Sum: '<Root>/Sum4' */
  heli_q8_B.Sum4 = heli_q8_B.ManualSwitch[3] - heli_q8_B.ManualSwitch3;
}

/* Model update function for TID0 */
void heli_q8_update0(void)             /* Sample time: [0.0s, 0.0s] */
{
  int32_T i;
  if (rtmIsMajorTimeStep(heli_q8_M)) {
    /* Update for UnitDelay: '<S4>/Unit Delay' */
    for (i = 0; i < 6; i++) {
      heli_q8_DW.UnitDelay_DSTATE[i] = heli_q8_B.x_future[i];
    }

    /* End of Update for UnitDelay: '<S4>/Unit Delay' */

    /* Update for UnitDelay: '<S4>/Unit Delay1' */
    memcpy(&heli_q8_DW.UnitDelay1_DSTATE[0], &heli_q8_B.P_future[0], 36U *
           sizeof(real_T));

    /* Update for Memory: '<S11>/Memory' */
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

  /* Derivatives for Integrator: '<S5>/Integrator2' */
  for (i = 0; i < 5; i++) {
    _rtXdot->Integrator2_CSTATE[i] = heli_q8_B.Sum5[i];
  }

  /* End of Derivatives for Integrator: '<S5>/Integrator2' */

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
  /* S-Function (game_controller_block): '<S3>/Game Controller' */

  /* S-Function Block: heli_q8/Joystick/Game Controller (game_controller_block) */
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
  /* Update for RateTransition: '<S3>/Rate Transition: y' */
  heli_q8_DW.RateTransitiony_Buffer0 = heli_q8_B.GameController_o5;

  /* Update for RateTransition: '<S3>/Rate Transition: x' */
  heli_q8_DW.RateTransitionx_Buffer0 = heli_q8_B.GameController_o4;

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

  /* Start for DiscretePulseGenerator: '<Root>/e_c_dot' */
  heli_q8_DW.clockTickCounter = -5000;

  /* Start for RateTransition: '<S3>/Rate Transition: y' */
  heli_q8_B.RateTransitiony = heli_q8_P.RateTransitiony_X0;

  /* Start for S-Function (stream_call_block): '<S11>/Stream Call1' */

  /* S-Function Block: heli_q8/Math logic/IMU/Stream Call1 (stream_call_block) */
  {
    heli_q8_DW.StreamCall1_State = STREAM_CALL_STATE_NOT_CONNECTED;
    heli_q8_DW.StreamCall1_Stream = NULL;
  }

  /* Start for ToFile: '<Root>/To File' */
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

  /* Start for RateTransition: '<S3>/Rate Transition: x' */
  heli_q8_B.RateTransitionx = heli_q8_P.RateTransitionx_X0;

  /* Start for ToFile: '<Root>/To File1' */
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

    heli_q8_DW.ToFile1_IWORK.Count = 0;
    heli_q8_DW.ToFile1_IWORK.Decimation = -1;
    heli_q8_DW.ToFile1_PWORK.FilePtr = fp;
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

  /* Start for S-Function (game_controller_block): '<S3>/Game Controller' */

  /* S-Function Block: heli_q8/Joystick/Game Controller (game_controller_block) */
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

  /* Start for ToFile: '<S4>/To File2' */
  {
    FILE *fp = (NULL);
    char fileName[509] = "Kalman.mat";
    if ((fp = fopen(fileName, "wb")) == (NULL)) {
      rtmSetErrorStatus(heli_q8_M, "Error creating .mat file Kalman.mat");
      return;
    }

    if (rt_WriteMat4FileHeader(fp,7,0,"Kalman")) {
      rtmSetErrorStatus(heli_q8_M,
                        "Error writing mat file header to file Kalman.mat");
      return;
    }

    heli_q8_DW.ToFile2_IWORK.Count = 0;
    heli_q8_DW.ToFile2_IWORK.Decimation = -1;
    heli_q8_DW.ToFile2_PWORK.FilePtr = fp;
  }

  /* Start for ToFile: '<S5>/To File2' */
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

    heli_q8_DW.ToFile2_IWORK_m.Count = 0;
    heli_q8_DW.ToFile2_IWORK_m.Decimation = -1;
    heli_q8_DW.ToFile2_PWORK_k.FilePtr = fp;
  }

  /* Start for ToFile: '<S6>/To File4' */
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

  /* Start for ToFile: '<S6>/To File5' */
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

  /* Start for ToFile: '<S6>/To File6' */
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

  /* Start for ToFile: '<S6>/To File7' */
  {
    FILE *fp = (NULL);
    char fileName[509] = "Measurement.mat";
    if ((fp = fopen(fileName, "wb")) == (NULL)) {
      rtmSetErrorStatus(heli_q8_M, "Error creating .mat file Measurement.mat");
      return;
    }

    if (rt_WriteMat4FileHeader(fp,6,0,"Measurement")) {
      rtmSetErrorStatus(heli_q8_M,
                        "Error writing mat file header to file Measurement.mat");
      return;
    }

    heli_q8_DW.ToFile7_IWORK.Count = 0;
    heli_q8_DW.ToFile7_IWORK.Decimation = -1;
    heli_q8_DW.ToFile7_PWORK.FilePtr = fp;
  }

  {
    int32_T i;

    /* InitializeConditions for RateTransition: '<S3>/Rate Transition: y' */
    heli_q8_DW.RateTransitiony_Buffer0 = heli_q8_P.RateTransitiony_X0;

    /* InitializeConditions for UnitDelay: '<S4>/Unit Delay' */
    for (i = 0; i < 6; i++) {
      heli_q8_DW.UnitDelay_DSTATE[i] = heli_q8_P.UnitDelay_InitialCondition[i];
    }

    /* End of InitializeConditions for UnitDelay: '<S4>/Unit Delay' */

    /* InitializeConditions for UnitDelay: '<S4>/Unit Delay1' */
    memcpy(&heli_q8_DW.UnitDelay1_DSTATE[0],
           &heli_q8_P.UnitDelay1_InitialCondition[0], 36U * sizeof(real_T));

    /* InitializeConditions for Memory: '<S11>/Memory' */
    memcpy(&heli_q8_DW.Memory_PreviousInput[0], &heli_q8_P.Memory_X0[0], 10U *
           sizeof(real_T));

    /* InitializeConditions for Integrator: '<S5>/Integrator2' */
    for (i = 0; i < 5; i++) {
      heli_q8_X.Integrator2_CSTATE[i] = heli_q8_P.Integrator2_IC;
    }

    /* End of InitializeConditions for Integrator: '<S5>/Integrator2' */

    /* InitializeConditions for TransferFcn: '<S2>/Pitch: Transfer Fcn' */
    heli_q8_X.PitchTransferFcn_CSTATE = 0.0;

    /* InitializeConditions for TransferFcn: '<S2>/Elevation: Transfer Fcn' */
    heli_q8_X.ElevationTransferFcn_CSTATE = 0.0;

    /* InitializeConditions for TransferFcn: '<S2>/Travel: Transfer Fcn' */
    heli_q8_X.TravelTransferFcn_CSTATE = 0.0;

    /* InitializeConditions for RateTransition: '<S3>/Rate Transition: x' */
    heli_q8_DW.RateTransitionx_Buffer0 = heli_q8_P.RateTransitionx_X0;

    /* InitializeConditions for Integrator: '<Root>/Integrator' */
    heli_q8_X.Integrator_CSTATE = heli_q8_P.Integrator_IC;

    /* InitializeConditions for Integrator: '<Root>/Integrator1' */
    heli_q8_X.Integrator1_CSTATE = heli_q8_P.Integrator1_IC;
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

  /* Terminate for S-Function (stream_call_block): '<S11>/Stream Call1' */

  /* S-Function Block: heli_q8/Math logic/IMU/Stream Call1 (stream_call_block) */
  {
    if (heli_q8_DW.StreamCall1_Stream != NULL) {
      stream_close(heli_q8_DW.StreamCall1_Stream);
      heli_q8_DW.StreamCall1_Stream = NULL;
    }
  }

  /* Terminate for ToFile: '<Root>/To File' */
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

  /* Terminate for ToFile: '<Root>/To File1' */
  {
    FILE *fp = (FILE *) heli_q8_DW.ToFile1_PWORK.FilePtr;
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

      if (rt_WriteMat4FileHeader(fp, 3, heli_q8_DW.ToFile1_IWORK.Count, "pitch"))
      {
        rtmSetErrorStatus(heli_q8_M,
                          "Error writing header for pitch to MAT-file pitch.mat");
      }

      if (fclose(fp) == EOF) {
        rtmSetErrorStatus(heli_q8_M, "Error closing MAT-file pitch.mat");
        return;
      }

      heli_q8_DW.ToFile1_PWORK.FilePtr = (NULL);
    }
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

  /* Terminate for S-Function (game_controller_block): '<S3>/Game Controller' */

  /* S-Function Block: heli_q8/Joystick/Game Controller (game_controller_block) */
  {
    if (heli_q8_P.GameController_Enabled) {
      game_controller_close(heli_q8_DW.GameController_Controller);
      heli_q8_DW.GameController_Controller = NULL;
    }
  }

  /* Terminate for ToFile: '<S4>/To File2' */
  {
    FILE *fp = (FILE *) heli_q8_DW.ToFile2_PWORK.FilePtr;
    if (fp != (NULL)) {
      char fileName[509] = "Kalman.mat";
      if (fclose(fp) == EOF) {
        rtmSetErrorStatus(heli_q8_M, "Error closing MAT-file Kalman.mat");
        return;
      }

      if ((fp = fopen(fileName, "r+b")) == (NULL)) {
        rtmSetErrorStatus(heli_q8_M, "Error reopening MAT-file Kalman.mat");
        return;
      }

      if (rt_WriteMat4FileHeader(fp, 7, heli_q8_DW.ToFile2_IWORK.Count, "Kalman"))
      {
        rtmSetErrorStatus(heli_q8_M,
                          "Error writing header for Kalman to MAT-file Kalman.mat");
      }

      if (fclose(fp) == EOF) {
        rtmSetErrorStatus(heli_q8_M, "Error closing MAT-file Kalman.mat");
        return;
      }

      heli_q8_DW.ToFile2_PWORK.FilePtr = (NULL);
    }
  }

  /* Terminate for ToFile: '<S5>/To File2' */
  {
    FILE *fp = (FILE *) heli_q8_DW.ToFile2_PWORK_k.FilePtr;
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

      if (rt_WriteMat4FileHeader(fp, 6, heli_q8_DW.ToFile2_IWORK_m.Count,
           "Estimators")) {
        rtmSetErrorStatus(heli_q8_M,
                          "Error writing header for Estimators to MAT-file Estimators.mat");
      }

      if (fclose(fp) == EOF) {
        rtmSetErrorStatus(heli_q8_M, "Error closing MAT-file Estimators.mat");
        return;
      }

      heli_q8_DW.ToFile2_PWORK_k.FilePtr = (NULL);
    }
  }

  /* Terminate for ToFile: '<S6>/To File4' */
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

  /* Terminate for ToFile: '<S6>/To File5' */
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

  /* Terminate for ToFile: '<S6>/To File6' */
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

  /* Terminate for ToFile: '<S6>/To File7' */
  {
    FILE *fp = (FILE *) heli_q8_DW.ToFile7_PWORK.FilePtr;
    if (fp != (NULL)) {
      char fileName[509] = "Measurement.mat";
      if (fclose(fp) == EOF) {
        rtmSetErrorStatus(heli_q8_M, "Error closing MAT-file Measurement.mat");
        return;
      }

      if ((fp = fopen(fileName, "r+b")) == (NULL)) {
        rtmSetErrorStatus(heli_q8_M, "Error reopening MAT-file Measurement.mat");
        return;
      }

      if (rt_WriteMat4FileHeader(fp, 6, heli_q8_DW.ToFile7_IWORK.Count,
           "Measurement")) {
        rtmSetErrorStatus(heli_q8_M,
                          "Error writing header for Measurement to MAT-file Measurement.mat");
      }

      if (fclose(fp) == EOF) {
        rtmSetErrorStatus(heli_q8_M, "Error closing MAT-file Measurement.mat");
        return;
      }

      heli_q8_DW.ToFile7_PWORK.FilePtr = (NULL);
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
  heli_q8_M->Sizes.checksums[0] = (577879452U);
  heli_q8_M->Sizes.checksums[1] = (2809443814U);
  heli_q8_M->Sizes.checksums[2] = (2249115166U);
  heli_q8_M->Sizes.checksums[3] = (4072644055U);

  {
    static const sysRanDType rtAlwaysEnabled = SUBSYS_RAN_BC_ENABLE;
    static RTWExtModeInfo rt_ExtModeInfo;
    static const sysRanDType *systemRan[13];
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
    systemRan[10] = &rtAlwaysEnabled;
    systemRan[11] = &rtAlwaysEnabled;
    systemRan[12] = &rtAlwaysEnabled;
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
    for (i = 0; i < 10; i++) {
      heli_q8_B.Switch[i] = 0.0;
    }

    for (i = 0; i < 5; i++) {
      heli_q8_B.Integrator2[i] = 0.0;
    }

    for (i = 0; i < 5; i++) {
      heli_q8_B.ManualSwitch[i] = 0.0;
    }

    for (i = 0; i < 5; i++) {
      heli_q8_B.Sum5[i] = 0.0;
    }

    for (i = 0; i < 6; i++) {
      heli_q8_B.x_future[i] = 0.0;
    }

    for (i = 0; i < 36; i++) {
      heli_q8_B.P_future[i] = 0.0;
    }

    for (i = 0; i < 6; i++) {
      heli_q8_B.x_now[i] = 0.0;
    }

    for (i = 0; i < 36; i++) {
      heli_q8_B.P_now[i] = 0.0;
    }

    heli_q8_B.RateTransitiony = 0.0;
    heli_q8_B.Joystick_gain_y = 0.0;
    heli_q8_B.ManualSwitch3 = 0.0;
    heli_q8_B.Switch1 = 0.0;
    heli_q8_B.PitchCounttorad = 0.0;
    heli_q8_B.ElevationCounttorad = 0.0;
    heli_q8_B.Sum1 = 0.0;
    heli_q8_B.Switch2 = 0.0;
    heli_q8_B.PitchTransferFcn = 0.0;
    heli_q8_B.ElevationTransferFcn = 0.0;
    heli_q8_B.TravelCounttorad = 0.0;
    heli_q8_B.TravelTransferFcn = 0.0;
    heli_q8_B.RateTransitionx = 0.0;
    heli_q8_B.Joystick_gain_x = 0.0;
    heli_q8_B.ManualSwitch2 = 0.0;
    heli_q8_B.Constant = 0.0;
    heli_q8_B.FrontmotorSaturation = 0.0;
    heli_q8_B.BackmotorSaturation = 0.0;
    heli_q8_B.GameController_o4 = 0.0;
    heli_q8_B.GameController_o5 = 0.0;
    heli_q8_B.Sum3 = 0.0;
    heli_q8_B.Sum4 = 0.0;
    heli_q8_B.euler_rates[0] = 0.0;
    heli_q8_B.euler_rates[1] = 0.0;
    heli_q8_B.euler_rates[2] = 0.0;
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
    for (i = 0; i < 6; i++) {
      heli_q8_DW.UnitDelay_DSTATE[i] = 0.0;
    }
  }

  {
    int32_T i;
    for (i = 0; i < 36; i++) {
      heli_q8_DW.UnitDelay1_DSTATE[i] = 0.0;
    }
  }

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

  heli_q8_DW.RateTransitiony_Buffer0 = 0.0;

  {
    int32_T i;
    for (i = 0; i < 10; i++) {
      heli_q8_DW.Memory_PreviousInput[i] = 0.0;
    }
  }

  heli_q8_DW.RateTransitionx_Buffer0 = 0.0;
  heli_q8_DW.HILWriteAnalog_Buffer[0] = 0.0;
  heli_q8_DW.HILWriteAnalog_Buffer[1] = 0.0;

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
  heli_q8_M->Sizes.numBlocks = (134);  /* Number of blocks */
  heli_q8_M->Sizes.numBlockIO = (32);  /* Number of block outputs */
  heli_q8_M->Sizes.numBlockPrms = (586);/* Sum of parameter "widths" */
  return heli_q8_M;
}

/*========================================================================*
 * End of Classic call interface                                          *
 *========================================================================*/
