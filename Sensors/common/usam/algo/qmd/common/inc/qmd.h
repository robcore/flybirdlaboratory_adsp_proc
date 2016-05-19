#ifndef QMD_H
#define QMD_H

/*============================================================================
  @file qmd.h

  Absolute motion detector header file

  Copyright (c) 2010-2014 Qualcomm Technologies, Inc. All Rights Reserved.
  Qualcomm Technologies Proprietary and Confidential
============================================================================*/

#include <stdint.h>
#include "sns_sam_qmd_v01.h"
#include "sns_smgr_api_v01.h"
#include "sns_smgr_internal_api_v02.h"
#include "sns_sam_algo_utils.h"
#include "sns_sam_algo_api.h"
#include "spi.h"

#define QMD_ACCEL_COLS (3)

/* QMD algorithm attributes */
#define QMD_ATTR_MIN_REPORT   0
#define QMD_ATTR_MAX_REPORT_Q16   FX_CONV_Q16(1, 0)
#define QMD_ATTR_REVISION     1
#define QMD_ATTR_MAX_BATCH    0

#define SMGR_ACCEL_UID        SNS_SMGR_SUID_ACCEL_1_V01
#define SMGR_MD_UID           SNS_SMGR_SENSOR_EVENT_ID_MOTION_DETECT_1_V02
#define SMGR_GATEDACCEL_UID   (SNS_SMGR_SUID_ACCEL_1_V01 ^ SNS_SMGR_SENSOR_EVENT_ID_MOTION_DETECT_1_V02)


#ifdef SNS_USES_ISLAND
#define SNS_SAM_UIMAGE_CODE __attribute__((section ("text.QMD")))
#define SNS_SAM_UIMAGE_DATA __attribute__((section ("data.QMD")))
#else
#define SNS_SAM_UIMAGE_CODE
#define SNS_SAM_UIMAGE_DATA
#endif /* SNS_USES_ISLAND */


typedef enum
{
  QMD_MIN_VALUE = -2147483647, // To force signed 32 bit value
  QMD_UNKNOWN = 0,
  QMD_REST    = 1,
  QMD_MOTION  = 2,
  QMD_MAX_VALUE = 2147483647 // To force signed 32 bit value
} qmd_motion_state;

typedef enum
{
  QMD_STREAM_ACCEL_PERIODIC,
  QMD_STREAM_ACCEL_BUFFERED,
  QMD_STREAM_ACCEL_PAUSE
} qmd_accel_stream_type;

typedef enum
{
  QMD_INPUT_ACCEL,
  QMD_INPUT_MD
} qmd_input_data_type;

/**
* qmd_config
* Passed to the algorithm instance upon algo reset.
*
* These values were parsed from the enable request message, registry data, and
* internal defaults
*/
typedef struct
{
  int32_t sample_rate;                   // In Hz, Q16
  int32_t internal_config_param1;        // In radians, Q16
  int32_t internal_config_param2;        // In seconds, Q16
  int32_t internal_config_param3;        // In radians, Q16
  int32_t internal_config_param4;        // In seconds, Q16
  bool mdIntAvailable;
} qmd_config;

/**
* qmd_input
* Contains input to the QMD algorithms.
*/
typedef struct
{
  qmd_input_data_type input_type;
  int32_t accel[QMD_ACCEL_COLS];  // accel, m/s/s, Q16
} qmd_input;

/**
* qmd_output
* Will be used to generate output indication messages
*/
typedef struct
{
  qmd_motion_state rest_state; // unknown=0, rest=1, motion=2
  sns_sam_timestamp timestamp;
} qmd_output;

/**
* amd_persist
* AMD algorithm information to be stored in persitant memory
*
* This structure does not need to be protected against concurrent access
*/
typedef struct {
  qmd_config     qmdConfig;         /**< Default algorithm configuration */
  q16_t          reportRate;    /**< Default reporting rate */
  bool           accelAvailable;        /**< Accel availibility */
  bool           regDataAvailable;     /**< Registry data available*/
  bool           mdIntAvailable;      /**< SMGR Motion detect interrupt available*/
  bool           gatedAccelAvailable;      /**< SMGR Motion detect interrupt available*/
  uint64_t       power;
  uint64_t       minSample;
  uint64_t       maxSample;
  sns_sam_sensor_uid const *accelSUID;
  sns_sam_sensor_uid const *mdIntSUID;
  sns_sam_sensor_uid const *GatedAccelSUID;
} qmd_persist;

/* QMD Message API */

/**
* Generates the memory requirements algorithm data buffers that are
* independent of algorithm configuration.
*
* See sns_sam_algo_mem_const_req
*
*/
 void qmd_mem_const_req( sns_sam_algo_const_buf_size *bufferSizes );

/**
* Obtain all attributes of an algorithm.
*
* See sns_sam_algo_get_attr
*/
void qmd_get_attr( sns_sam_algo_persist const *persistData,
                   sns_sam_algo_attr attributes[] );

/**
* Determine whether the algorithm's sensor dependencies have been met.
*
* See sns_sam_algo_dep_sensors_met
*/
void qmd_dep_sensors_met( struct sns_sam_sensor_algo const *algo,
                          sns_sam_algo_all_dep_met depMetFunc,
                          sns_sam_algo_persist *persistData,
                          sns_sam_sensor_uid const *sensorUID,
                          sns_sam_algo_attr const (*sns_sam_attr_array)[ SAM_ALGO_ATTR_CNT ] );


/**
* Provide a list of an algorithm's dependent sensors.
*
* See sns_sam_algo_dep_sensors
*/
sns_sam_err qmd_dep_sensors( uint32_t *sensorCount,
                             struct sns_sam_algo_dep_sensor dependentSensors[] );

/**
* Process an incoming indication from one of this algorithm's sensor
* dependencies.
*
* See sns_sam_algo_process_ind
*/
sns_sam_err qmd_process_ind( sns_sam_algo_callback const *cbFunc,
                             sns_sam_ind_msg const *indMsg,
                             sns_sam_input_q *inputData );

/**
* Generate an indication from a piece of algorithm output data.
*
* See sns_sam_algo_gen_ind
*/
sns_sam_err qmd_gen_ind( sns_sam_algo_callback const *cbFunc,
                         sns_sam_algo_output const *outputData,
                         uint8_t extInstanceID,
                         sns_sam_ind_msg *indMsg );

/**
* Generates the report response message.
*
* See sns_sam_algo_gen_report
*/
sns_sam_err qmd_gen_report( sns_sam_algo_output const *outputData,
  sns_sam_resp_msg *respMsg );


/**
* Generates the enable request message for the given dependent sensor.
*
* See sns_sam_algo_gen_req
*/
sns_sam_err qmd_gen_req( sns_sam_algo_state const *algoState,
                              sns_sam_sensor_uid const *sensorUID,
                              sns_sam_enable_req *enableReqMsg );

/**
* Check if a proposed sensor dependency request is acceptable to this
* algorithm instance.
*
* There shall always be only one acceptable QMD configuration, therefore this
* function shall return false always.
*
* See sns_sam_algo_check_sensor
*/
 bool qmd_check_sensor( sns_sam_algo_state const *algoState,
                        sns_sam_enable_req const *enableReq );


#endif /* QMD_H */
