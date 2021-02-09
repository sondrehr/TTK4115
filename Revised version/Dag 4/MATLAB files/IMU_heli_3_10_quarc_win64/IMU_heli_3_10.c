/*
 * IMU_heli_3_10.c
 *
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * Code generation for model "IMU_heli_3_10".
 *
 * Model version              : 1.7
 * Simulink Coder version : 8.9 (R2015b) 13-Aug-2015
 * C source code generated on : Mon Oct 19 10:24:08 2020
 *
 * Target selection: quarc_win64.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: Intel->x86-64 (Windows64)
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "IMU_heli_3_10.h"
#include "IMU_heli_3_10_private.h"
#include "IMU_heli_3_10_dt.h"

t_stream IMU_heli_3_10_rtZt_stream = NULL;

/* Block signals (auto storage) */
B_IMU_heli_3_10_T IMU_heli_3_10_B;

/* Block states (auto storage) */
DW_IMU_heli_3_10_T IMU_heli_3_10_DW;

/* Real-time model */
RT_MODEL_IMU_heli_3_10_T IMU_heli_3_10_M_;
RT_MODEL_IMU_heli_3_10_T *const IMU_heli_3_10_M = &IMU_heli_3_10_M_;

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

/* Model output function */
void IMU_heli_3_10_output(void)
{
  /* local block i/o variables */
  real_T rtb_Gain2[3];
  t_stream_ptr rtb_StreamCall1_o1;
  t_stream_ptr rtb_StreamFormattedWrite_o1;
  real32_T rtb_StreamRead1_o2[10];
  int32_T rtb_StreamFormattedWrite_o2;
  int32_T rtb_StreamCall1_o3;
  int32_T rtb_StreamRead1_o5;
  boolean_T rtb_StreamRead1_o3;
  int32_T i;

  /* S-Function (stream_call_block): '<S2>/Stream Call1' */

  /* S-Function Block: IMU_heli_3_10/IMU/Stream Call1 (stream_call_block) */
  {
    t_error result = 0;
    t_boolean close_flag = (IMU_heli_3_10_P.Constant_Value != 0);
    rtb_StreamCall1_o1 = NULL;
    switch (IMU_heli_3_10_DW.StreamCall1_State) {
     case STREAM_CALL_STATE_NOT_CONNECTED:
      {
        if (!close_flag) {
          /* Make sure URI is null-terminated */
          if (string_length((char *) IMU_heli_3_10_P.StringConstant_Value, 255) ==
              255) {
            rtmSetErrorStatus(IMU_heli_3_10_M,
                              "URI passed to Stream Call block is not null-terminated!");
            result = -QERR_STRING_NOT_TERMINATED;
          } else {
            result = stream_connect((char *)
              IMU_heli_3_10_P.StringConstant_Value, true,
              IMU_heli_3_10_P.StreamCall1_SendBufferSize,
              IMU_heli_3_10_P.StreamCall1_ReceiveBufferSize,
              &IMU_heli_3_10_DW.StreamCall1_Stream);
            if (result == 0) {
              IMU_heli_3_10_DW.StreamCall1_State = STREAM_CALL_STATE_CONNECTED;
              stream_set_byte_order(IMU_heli_3_10_DW.StreamCall1_Stream,
                                    (t_stream_byte_order)
                                    IMU_heli_3_10_P.StreamCall1_Endian);
              rtb_StreamCall1_o1 = &IMU_heli_3_10_DW.StreamCall1_Stream;
            } else if (result == -QERR_WOULD_BLOCK) {
              IMU_heli_3_10_DW.StreamCall1_State = STREAM_CALL_STATE_CONNECTING;
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

          result = stream_poll(IMU_heli_3_10_DW.StreamCall1_Stream, &timeout,
                               STREAM_POLL_CONNECT);
          if (result > 0) {
            IMU_heli_3_10_DW.StreamCall1_State = STREAM_CALL_STATE_CONNECTED;
            stream_set_byte_order(IMU_heli_3_10_DW.StreamCall1_Stream,
                                  (t_stream_byte_order)
                                  IMU_heli_3_10_P.StreamCall1_Endian);
            rtb_StreamCall1_o1 = &IMU_heli_3_10_DW.StreamCall1_Stream;
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
        rtb_StreamCall1_o1 = &IMU_heli_3_10_DW.StreamCall1_Stream;
        if (!close_flag) {
          break;
        }

        /* Fall through deliberately */
      }

     default:
      {
        t_error close_result = stream_close(IMU_heli_3_10_DW.StreamCall1_Stream);
        if (close_result == 0) {
          IMU_heli_3_10_DW.StreamCall1_State = STREAM_CALL_STATE_NOT_CONNECTED;
          IMU_heli_3_10_DW.StreamCall1_Stream = NULL;
          rtb_StreamCall1_o1 = NULL;
        } else if (result == 0) {
          result = close_result;
        }
        break;
      }
    }

    IMU_heli_3_10_B.StreamCall1_o2 = IMU_heli_3_10_DW.StreamCall1_State;
    rtb_StreamCall1_o3 = (int32_T) result;
  }

  /* S-Function (stream_formatted_write_block): '<S2>/Stream Formatted Write' */
  {
    t_error result;
    if (rtb_StreamCall1_o1 != NULL) {
      result = stream_print_utf8_char_array(*rtb_StreamCall1_o1,
        IMU_heli_3_10_P.StreamFormattedWrite_MaxUnits,
        &rtb_StreamFormattedWrite_o2, "%c\n"
        , (char) IMU_heli_3_10_P.Constant1_Value
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

  /* S-Function (stream_read_block): '<S2>/Stream Read1' */
  /* S-Function Block: IMU_heli_3_10/IMU/Stream Read1 (stream_read_block) */
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

  /* Switch: '<S2>/Switch' incorporates:
   *  DataTypeConversion: '<S2>/Data Type Conversion'
   *  Memory: '<S2>/Memory'
   */
  for (i = 0; i < 10; i++) {
    if (rtb_StreamRead1_o3) {
      IMU_heli_3_10_B.Switch[i] = rtb_StreamRead1_o2[i];
    } else {
      IMU_heli_3_10_B.Switch[i] = IMU_heli_3_10_DW.Memory_PreviousInput[i];
    }
  }

  /* End of Switch: '<S2>/Switch' */

  /* Gain: '<S2>/Gain1' */
  for (i = 0; i < 3; i++) {
    IMU_heli_3_10_B.Gain1[i] = 0.0;
    IMU_heli_3_10_B.Gain1[i] += IMU_heli_3_10_P.Gain1_Gain[i] *
      IMU_heli_3_10_B.Switch[3];
    IMU_heli_3_10_B.Gain1[i] += IMU_heli_3_10_P.Gain1_Gain[i + 3] *
      IMU_heli_3_10_B.Switch[4];
    IMU_heli_3_10_B.Gain1[i] += IMU_heli_3_10_P.Gain1_Gain[i + 6] *
      IMU_heli_3_10_B.Switch[5];
  }

  /* End of Gain: '<S2>/Gain1' */

  /* Gain: '<S2>/Gain2' */
  for (i = 0; i < 3; i++) {
    rtb_Gain2[i] = 0.0;
    rtb_Gain2[i] += IMU_heli_3_10_P.Gain2_Gain[i] * IMU_heli_3_10_B.Switch[0];
    rtb_Gain2[i] += IMU_heli_3_10_P.Gain2_Gain[i + 3] * IMU_heli_3_10_B.Switch[1];
    rtb_Gain2[i] += IMU_heli_3_10_P.Gain2_Gain[i + 6] * IMU_heli_3_10_B.Switch[2];
  }

  /* End of Gain: '<S2>/Gain2' */

  /* ToFile: '<Root>/To File2' */
  {
    if (!(++IMU_heli_3_10_DW.ToFile2_IWORK.Decimation % 1) &&
        (IMU_heli_3_10_DW.ToFile2_IWORK.Count*4)+1 < 100000000 ) {
      FILE *fp = (FILE *) IMU_heli_3_10_DW.ToFile2_PWORK.FilePtr;
      if (fp != (NULL)) {
        real_T u[4];
        IMU_heli_3_10_DW.ToFile2_IWORK.Decimation = 0;
        u[0] = IMU_heli_3_10_M->Timing.t[0];
        u[1] = rtb_Gain2[0];
        u[2] = rtb_Gain2[1];
        u[3] = rtb_Gain2[2];
        if (fwrite(u, sizeof(real_T), 4, fp) != 4) {
          rtmSetErrorStatus(IMU_heli_3_10_M,
                            "Error writing to MAT-file eulerAngles.mat");
          return;
        }

        if (((++IMU_heli_3_10_DW.ToFile2_IWORK.Count)*4)+1 >= 100000000) {
          (void)fprintf(stdout,
                        "*** The ToFile block will stop logging data before\n"
                        "    the simulation has ended, because it has reached\n"
                        "    the maximum number of elements (100000000)\n"
                        "    allowed in MAT-file eulerAngles.mat.\n");
        }
      }
    }
  }

  /* MATLAB Function 'Gyro vector to [pitch rate, elevation rate, travle rate]': '<S1>:1' */
  /* '<S1>:1:3' */
  /* '<S1>:1:4' */
  /* psi = euler_angles(3); */
  /* '<S1>:1:8' */
  /* '<S1>:1:11' */

  /* S-Function (stop_with_error_block): '<S2>/Stop with Call Error' */

  /* S-Function Block: IMU_heli_3_10/IMU/Stop with Call Error (stop_with_error_block) */
  {
    if (rtb_StreamCall1_o3 < 0) {
      msg_get_error_messageA(NULL, rtb_StreamCall1_o3, _rt_error_message, sizeof
        (_rt_error_message));
      rtmSetErrorStatus(IMU_heli_3_10_M, _rt_error_message);
      return;
    }
  }

  /* S-Function (stop_with_error_block): '<S2>/Stop with Read Error' */

  /* S-Function Block: IMU_heli_3_10/IMU/Stop with Read Error (stop_with_error_block) */
  {
    if (rtb_StreamRead1_o5 < 0) {
      msg_get_error_messageA(NULL, rtb_StreamRead1_o5, _rt_error_message, sizeof
        (_rt_error_message));
      rtmSetErrorStatus(IMU_heli_3_10_M, _rt_error_message);
      return;
    }
  }
}

/* Model update function */
void IMU_heli_3_10_update(void)
{
  /* Update for Memory: '<S2>/Memory' */
  memcpy(&IMU_heli_3_10_DW.Memory_PreviousInput[0], &IMU_heli_3_10_B.Switch[0],
         10U * sizeof(real_T));

  /* Update absolute time for base rate */
  /* The "clockTick0" counts the number of times the code of this task has
   * been executed. The absolute time is the multiplication of "clockTick0"
   * and "Timing.stepSize0". Size of "clockTick0" ensures timer will not
   * overflow during the application lifespan selected.
   * Timer of this task consists of two 32 bit unsigned integers.
   * The two integers represent the low bits Timing.clockTick0 and the high bits
   * Timing.clockTickH0. When the low bit overflows to 0, the high bits increment.
   */
  if (!(++IMU_heli_3_10_M->Timing.clockTick0)) {
    ++IMU_heli_3_10_M->Timing.clockTickH0;
  }

  IMU_heli_3_10_M->Timing.t[0] = IMU_heli_3_10_M->Timing.clockTick0 *
    IMU_heli_3_10_M->Timing.stepSize0 + IMU_heli_3_10_M->Timing.clockTickH0 *
    IMU_heli_3_10_M->Timing.stepSize0 * 4294967296.0;
}

/* Model initialize function */
void IMU_heli_3_10_initialize(void)
{
  /* Start for S-Function (stream_call_block): '<S2>/Stream Call1' */

  /* S-Function Block: IMU_heli_3_10/IMU/Stream Call1 (stream_call_block) */
  {
    IMU_heli_3_10_DW.StreamCall1_State = STREAM_CALL_STATE_NOT_CONNECTED;
    IMU_heli_3_10_DW.StreamCall1_Stream = NULL;
  }

  /* Start for ToFile: '<Root>/To File2' */
  {
    FILE *fp = (NULL);
    char fileName[509] = "eulerAngles.mat";
    if ((fp = fopen(fileName, "wb")) == (NULL)) {
      rtmSetErrorStatus(IMU_heli_3_10_M,
                        "Error creating .mat file eulerAngles.mat");
      return;
    }

    if (rt_WriteMat4FileHeader(fp,4,0,"EulerAngles")) {
      rtmSetErrorStatus(IMU_heli_3_10_M,
                        "Error writing mat file header to file eulerAngles.mat");
      return;
    }

    IMU_heli_3_10_DW.ToFile2_IWORK.Count = 0;
    IMU_heli_3_10_DW.ToFile2_IWORK.Decimation = -1;
    IMU_heli_3_10_DW.ToFile2_PWORK.FilePtr = fp;
  }

  /* InitializeConditions for Memory: '<S2>/Memory' */
  memcpy(&IMU_heli_3_10_DW.Memory_PreviousInput[0], &IMU_heli_3_10_P.Memory_X0[0],
         10U * sizeof(real_T));
}

/* Model terminate function */
void IMU_heli_3_10_terminate(void)
{
  /* Terminate for S-Function (stream_call_block): '<S2>/Stream Call1' */

  /* S-Function Block: IMU_heli_3_10/IMU/Stream Call1 (stream_call_block) */
  {
    if (IMU_heli_3_10_DW.StreamCall1_Stream != NULL) {
      stream_close(IMU_heli_3_10_DW.StreamCall1_Stream);
      IMU_heli_3_10_DW.StreamCall1_Stream = NULL;
    }
  }

  /* Terminate for ToFile: '<Root>/To File2' */
  {
    FILE *fp = (FILE *) IMU_heli_3_10_DW.ToFile2_PWORK.FilePtr;
    if (fp != (NULL)) {
      char fileName[509] = "eulerAngles.mat";
      if (fclose(fp) == EOF) {
        rtmSetErrorStatus(IMU_heli_3_10_M,
                          "Error closing MAT-file eulerAngles.mat");
        return;
      }

      if ((fp = fopen(fileName, "r+b")) == (NULL)) {
        rtmSetErrorStatus(IMU_heli_3_10_M,
                          "Error reopening MAT-file eulerAngles.mat");
        return;
      }

      if (rt_WriteMat4FileHeader(fp, 4, IMU_heli_3_10_DW.ToFile2_IWORK.Count,
           "EulerAngles")) {
        rtmSetErrorStatus(IMU_heli_3_10_M,
                          "Error writing header for EulerAngles to MAT-file eulerAngles.mat");
      }

      if (fclose(fp) == EOF) {
        rtmSetErrorStatus(IMU_heli_3_10_M,
                          "Error closing MAT-file eulerAngles.mat");
        return;
      }

      IMU_heli_3_10_DW.ToFile2_PWORK.FilePtr = (NULL);
    }
  }
}

/*========================================================================*
 * Start of Classic call interface                                        *
 *========================================================================*/
void MdlOutputs(int_T tid)
{
  IMU_heli_3_10_output();
  UNUSED_PARAMETER(tid);
}

void MdlUpdate(int_T tid)
{
  IMU_heli_3_10_update();
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
  IMU_heli_3_10_initialize();
}

void MdlTerminate(void)
{
  IMU_heli_3_10_terminate();
}

/* Registration function */
RT_MODEL_IMU_heli_3_10_T *IMU_heli_3_10(void)
{
  /* Registration code */

  /* initialize non-finites */
  rt_InitInfAndNaN(sizeof(real_T));

  /* initialize real-time model */
  (void) memset((void *)IMU_heli_3_10_M, 0,
                sizeof(RT_MODEL_IMU_heli_3_10_T));

  /* Initialize timing info */
  {
    int_T *mdlTsMap = IMU_heli_3_10_M->Timing.sampleTimeTaskIDArray;
    mdlTsMap[0] = 0;
    IMU_heli_3_10_M->Timing.sampleTimeTaskIDPtr = (&mdlTsMap[0]);
    IMU_heli_3_10_M->Timing.sampleTimes =
      (&IMU_heli_3_10_M->Timing.sampleTimesArray[0]);
    IMU_heli_3_10_M->Timing.offsetTimes =
      (&IMU_heli_3_10_M->Timing.offsetTimesArray[0]);

    /* task periods */
    IMU_heli_3_10_M->Timing.sampleTimes[0] = (0.002);

    /* task offsets */
    IMU_heli_3_10_M->Timing.offsetTimes[0] = (0.0);
  }

  rtmSetTPtr(IMU_heli_3_10_M, &IMU_heli_3_10_M->Timing.tArray[0]);

  {
    int_T *mdlSampleHits = IMU_heli_3_10_M->Timing.sampleHitArray;
    mdlSampleHits[0] = 1;
    IMU_heli_3_10_M->Timing.sampleHits = (&mdlSampleHits[0]);
  }

  rtmSetTFinal(IMU_heli_3_10_M, -1);
  IMU_heli_3_10_M->Timing.stepSize0 = 0.002;

  /* External mode info */
  IMU_heli_3_10_M->Sizes.checksums[0] = (130786736U);
  IMU_heli_3_10_M->Sizes.checksums[1] = (3735128819U);
  IMU_heli_3_10_M->Sizes.checksums[2] = (2724536520U);
  IMU_heli_3_10_M->Sizes.checksums[3] = (3046562488U);

  {
    static const sysRanDType rtAlwaysEnabled = SUBSYS_RAN_BC_ENABLE;
    static RTWExtModeInfo rt_ExtModeInfo;
    static const sysRanDType *systemRan[3];
    IMU_heli_3_10_M->extModeInfo = (&rt_ExtModeInfo);
    rteiSetSubSystemActiveVectorAddresses(&rt_ExtModeInfo, systemRan);
    systemRan[0] = &rtAlwaysEnabled;
    systemRan[1] = &rtAlwaysEnabled;
    systemRan[2] = &rtAlwaysEnabled;
    rteiSetModelMappingInfoPtr(IMU_heli_3_10_M->extModeInfo,
      &IMU_heli_3_10_M->SpecialInfo.mappingInfo);
    rteiSetChecksumsPtr(IMU_heli_3_10_M->extModeInfo,
                        IMU_heli_3_10_M->Sizes.checksums);
    rteiSetTPtr(IMU_heli_3_10_M->extModeInfo, rtmGetTPtr(IMU_heli_3_10_M));
  }

  IMU_heli_3_10_M->solverInfoPtr = (&IMU_heli_3_10_M->solverInfo);
  IMU_heli_3_10_M->Timing.stepSize = (0.002);
  rtsiSetFixedStepSize(&IMU_heli_3_10_M->solverInfo, 0.002);
  rtsiSetSolverMode(&IMU_heli_3_10_M->solverInfo, SOLVER_MODE_SINGLETASKING);

  /* block I/O */
  IMU_heli_3_10_M->ModelData.blockIO = ((void *) &IMU_heli_3_10_B);
  (void) memset(((void *) &IMU_heli_3_10_B), 0,
                sizeof(B_IMU_heli_3_10_T));

  /* parameters */
  IMU_heli_3_10_M->ModelData.defaultParam = ((real_T *)&IMU_heli_3_10_P);

  /* states (dwork) */
  IMU_heli_3_10_M->ModelData.dwork = ((void *) &IMU_heli_3_10_DW);
  (void) memset((void *)&IMU_heli_3_10_DW, 0,
                sizeof(DW_IMU_heli_3_10_T));

  /* data type transition information */
  {
    static DataTypeTransInfo dtInfo;
    (void) memset((char_T *) &dtInfo, 0,
                  sizeof(dtInfo));
    IMU_heli_3_10_M->SpecialInfo.mappingInfo = (&dtInfo);
    dtInfo.numDataTypes = 22;
    dtInfo.dataTypeSizes = &rtDataTypeSizes[0];
    dtInfo.dataTypeNames = &rtDataTypeNames[0];

    /* Block I/O transition table */
    dtInfo.B = &rtBTransTable;

    /* Parameters transition table */
    dtInfo.P = &rtPTransTable;
  }

  /* Initialize Sizes */
  IMU_heli_3_10_M->Sizes.numContStates = (0);/* Number of continuous states */
  IMU_heli_3_10_M->Sizes.numY = (0);   /* Number of model outputs */
  IMU_heli_3_10_M->Sizes.numU = (0);   /* Number of model inputs */
  IMU_heli_3_10_M->Sizes.sysDirFeedThru = (0);/* The model is not direct feedthrough */
  IMU_heli_3_10_M->Sizes.numSampTimes = (1);/* Number of sample times */
  IMU_heli_3_10_M->Sizes.numBlocks = (21);/* Number of blocks */
  IMU_heli_3_10_M->Sizes.numBlockIO = (3);/* Number of block outputs */
  IMU_heli_3_10_M->Sizes.numBlockPrms = (291);/* Sum of parameter "widths" */
  return IMU_heli_3_10_M;
}

/*========================================================================*
 * End of Classic call interface                                          *
 *========================================================================*/
