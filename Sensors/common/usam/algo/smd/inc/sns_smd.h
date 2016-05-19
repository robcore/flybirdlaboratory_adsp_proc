#ifndef SMD_H
#define SMD_H

/*============================================================================
   @file smd.h

   Significant Motion Detection header file

   Copyright (c) 2013-2014 Qualcomm Technologies, Inc.  All Rights Reserved.
   Qualcomm Confidential and Proprietary
============================================================================*/

/* $Header: //components/rel/ssc.adsp/2.6.1/common/usam/algo/smd/inc/sns_smd.h#2 $ */
/* $DateTime: 2014/12/05 22:23:17 $ */
/* $Author: pwbldsvc $ */

#include <stdint.h>
#include "sns_buffer.h"
#include "sns_sam_qmd_v01.h"
#include "sns_sam_ped_v01.h"
#include "sns_sam_amd_v01.h"
#include "sns_sam_smd_v01.h"
#include "sns_smgr_api_v01.h"
#include "sns_sam_algo_utils.h"
#include "sns_sam_algo_api.h"
#include "sns_reg_common.h"
#include "sns_reg_api_v02.h"

#define SMD_SUID              SNS_SAM_SMD_SUID_V01
#define SMGR_ACCEL_UID        SNS_SMGR_SUID_ACCEL_1_V01
#define SAM_PED_UID           SNS_SAM_PED_SUID_V01
#define SAM_AMD_UID           SNS_SAM_AMD_SUID_V01

#define SMD_ACCEL_COLS                3                   // accel columm number
#define SMD_STEP_BUF_SIZE             32


/* SMD algorithm attributes */
#define SMD_ATTR_MIN_REPORT   0
#define SMD_ATTR_MAX_REPORT   0
#define SMD_ATTR_REVISION     1
#define SMD_ATTR_MAX_BATCH    0
#define SMD_DEF_ACCEL_BATCH_REPORT_RATE_Q16 FX_CONV_Q16(1,0)


/* SMD algorithm macros */
#define SMD_SELF_TRANSITION_PROB_NM	 (0.9999f)	// sefl transtion prob for NM, Q16
#define SMD_STEP_STEP_CONF_THRES      90           // step confidence threshold
#define SMD_PROB_THRESH      (0.5f)			// probability threshold, Q16
#define SMD_XCOR_TIME_WINDOW 10                    // autocorrelation window in sec
#define SMD_XCOR_THRESH      (0.5f)  			// autocorrelation threshold, Q16
#define SMD_MIN_ACC_VAR      (0.2f*0.2f) 		// Min accel standard variance, Q16

#define DSPS_TICKS_PER_SEC   32768
#define SMD_RETENTION_TIME   1*DSPS_TICKS_PER_SEC  // 1 sec in DSPS ticks

#define MIN_EIG_P            (0.001f)
#define Q16_MIN_EIG_P        FX_FLTTOFIX_Q16(MIN_EIG_P)
#define Q16_PI_OVER_3        FX_FLTTOFIX_Q16(PI/3)
#define Q16_2PI_OVER_3       (Q16_PI_OVER_3 << 1)
#define MATRIX_RIGHT_SHIFT   7

// constants for probability computation
#define Q16_ONE          (FX_ONE_Q16)
#define Q16_FIVE         (Q16_ONE * 5)
#define Q16_TEN          (Q16_FIVE << 1)
#define Q16_TWENTY       (Q16_TEN << 1)
#define Q16_ONE_HUNDRED	 (Q16_TWENTY * 5)
#define Q16_POINT_ONE    (Q16_ONE / 10)
#define Q16_POINT_TWO    (Q16_POINT_ONE << 1)
#define Q16_POINT_TWO_SQ (FX_FLTTOFIX_Q16(0.04))
#define Q16_POINT_THREE	 (Q16_POINT_ONE * 3)
#define Q16_POINT_FOUR   (Q16_POINT_ONE << 2)
#define Q16_POINT_FIVE   (Q16_ONE >> 1)
#define Q16_POINT_SIX    (Q16_POINT_THREE << 1)
#define Q16_POINT_SEVEN  (Q16_POINT_ONE * 7)
#define Q16_POINT_EIGHT  (Q16_POINT_ONE << 3)
#define Q16_POINT_NINE   (Q16_POINT_ONE * 9)

#define POINT_FIVE		 (0.5f)
#define POINT_ONE		 (0.1f)
#define POINT_NINE		 (0.9f)

#define SMD_MAX_ULONG    (4294967295ULL) // Largest unsigned 32 bit number.

#define SMD_STEP_BUF_IND_INC(i) ((i+1) & (SMD_STEP_BUF_SIZE-1))

// Time lags used to compute autocorrelation
#define NUM_LAG_ELEMENTS  (18)
static const float LAG[NUM_LAG_ELEMENTS] =
{  (0.3f), (0.4f),
   (0.5f), (0.6f),
   (0.7f), (0.8f),
   (0.9f), (1.0f),
   (1.1f), (1.2f),
   (1.3f), (1.4f),
   (1.5f), (1.6f),
   (1.7f), (1.8f),
   (1.9f), (2.0f) };


enum SMD_STATES
{
   SMD_STATE_UNKNOWN   = 0,        // unknown state
   SMD_STATE_NO_MOTION = 1,        // no motion
   SMD_STATE_MOTION    = 2        // siginificant motion
};

typedef enum
{
   SMD_ACCEL_INPUT,
   SMD_AMD_INPUT,
   SMD_PED_INPUT
} smd_input_e;

typedef enum
{
   SNS_SMD_STEP_INFER_NONE   = 0,
   SNS_SMD_STEP_INFER_LOW    = 1,
   SNS_SMD_STEP_INFER_HIGH   = 2
} smd_step_infer_e;

typedef enum
{
  SMD_STREAM_ACCEL_BUFFERED,
  SMD_STREAM_ACCEL_PAUSE
} smd_accel_stream_type;

typedef struct
{
   int32_t sample_rate;               // sample rate, Hz, Q16, 5Hz or 10Hz performance driven, default 10Hz
   int32_t accel_window_time;         // Size of history throughout the algorithm, sec, default 5s
   float detect_threshold;          // accel, m/s/s, (Q16), AMD like std thr, default sqrt(0.05/2);
   float self_transition_prob_sm;   // Self transition probability of significant motion, Q16, default 0.9
   uint8_t variable_decision_latency; // Flag to indicate: (1) use variable latency , (0) use fixed latency and max_latency always, default 1
   uint8_t max_latency;               // Maximum latency if fixed latency is used, in secs, default 10s
   uint8_t step_count_thresh;         // Step count threshold
   uint8_t step_window_time;          // Step confidence window
   float eigen_thresh;              // Threshold for the eigen value
   float accel_norm_std_thresh;     // Accel norm standard deviation threshold
} smd_config;

typedef struct
{
   union {
      int32_t accel[SMD_ACCEL_COLS];         // accel, m/s/s, Q16
      sns_sam_motion_state_e_v01 amd_state;  // state of AMD
      uint8_t step_conf;                     // detection confidence metric of reported step
   } data;
   smd_input_e datatype;                     // type of input data
} smd_input;

typedef struct
{
   int8_t motion_state;               // Motion state, UNKNOWN(0), NO_MOTION(1), MOTION(2)
   uint8_t motion_state_probability;  // Probability of the reported motion state scaled to percentage (range 0 to 100)
   sns_sam_timestamp timestamp;                // timestamp in DSPS ticks
} smd_output;

typedef struct
{
  bool accelAvailable;
  bool AMDAvailable;
  bool pedAvailable;
  bool regDataAvailable;
  uint64_t accel_power;
  sns_sam_sensor_uid const *accelSUID;
  sns_sam_sensor_uid const *pedSUID;
  sns_sam_sensor_uid const *amdSUID;
  smd_config smdDefConfig;
} smd_persist;

typedef struct
{
   smd_config config;
   sns_buffer_type accel_buf;                 // buffer to store accel samples (x, y, z)
   sns_buffer_type amag_buf;                  // buffer to store accel mag used for spread computation
   sns_buffer_type xcor_buf;                  // buffer to store accel mag used for aucorrelation computation
   float detect_threshold;              // detect_threshold square, [m2/s4], Q16
   float accel_sum[SMD_ACCEL_COLS];     // sum of accel x,y,z, [m/s2], Q16
   float accel_sq_sum[SMD_ACCEL_COLS];  // sum of accel square x,y,z, [m2/s4], Q16
   float accel_norm_sum;                // sum of the Euclidean accel norm, [m/s2], Q16
   float accel_norm_sq_sum;             // sum of the Euclidean accel norm square, [m2/s4], Q16. Can be negative
   float accel_mag_sum;                 // sum of accel mag
   float accel_mag_sq_sum;              // sum of square accel mag. Can be negative
   float accel_mag_var;                 // accel mag variance
   float variance;                      // variance, Q16
   float eigenvalues[SMD_ACCEL_COLS];   // eigenvalues, Q16
   float xcor;                          // auto correlation, Q16
   float spread_mag;                    // spread magnitude, Q16
   float accel_norm_mean_ratio;         // Ratio of norm of accel mean to mean of accel norm, Q16
   float accel_norm_var;                // Variance of accel norm, Q16
   float pstate[2];                     // HMM states, Q16
   uint16_t filter_delay_cnt;             // filter delay count
   uint16_t filter_delay_time;            // filter delay time, in sec
   uint16_t sample_cnt;                   // sample count
   uint32_t last_xcor_compute_time;       // last time xcor was computed
   uint32_t last_eigenvalue_compute_time; // last time eigenvalue was computed
   uint32_t accel_ts;                     // ts of last sample received
   sns_sam_timestamp step_ts;                      // timestamp of latest step event
   sns_sam_timestamp amd_ts;                       // timestamp of latest AMD input
   int8_t motion_state;                   // transient motion state
   int8_t final_motion_state;             // final motion state as reported to client
   sns_sam_motion_state_e_v01 amd_state;  // state of AMD
   uint8_t step_count;
   uint8_t step_buf_first_ind;
   uint8_t step_buf_last_ind;
   uint8_t step_conf_buf[SMD_STEP_BUF_SIZE];
   uint32_t step_ts_buf[SMD_STEP_BUF_SIZE];
   uint32_t step_conf;                     // detection confidence metric of reported steps
   smd_step_infer_e step_infer;
   float transition_prob[2][2];          // HMM state transition probabilities
                                           // State 1 is Significant motion and state 2 is no motion
                                           // pstate  = [0.5 0.5]'; %initial state
                                           // TP = [0.90 1-0.90; 1-0.9999 0.9999]'; %TP_ij = probability of going from i to j,
                                           // i.e., row i is the source state and column j is the target state
                                           // Note the sw inverts the array and uses computation accordingly.
  smd_accel_stream_type accelStatus;
  smd_output last_output;
  smd_output current_output;
} smd_state;


/**
* Generates memory requirements for algorithm data buffers.
*
* See sns_sam_algo_mem_req
*/
sns_sam_err smd_mem_req( sns_sam_algo_config const *configData,
                         sns_sam_algo_buf_size *bufferSizes );

/**
* Resets and initializes AMD algorithm state data.
*
* See sns_sam_algo_reset
*/
sns_sam_err smd_reset( sns_sam_algo_config const *configData,
                       sns_sam_algo_callback const *cbFunc,
                       sns_sam_algo_persist *persistData,
                       sns_sam_algo_state *algoState );

/**
* Update algorithm with input data and update the algorithm output
*
* See sns_sam_algo_update
*/
sns_sam_err smd_update( sns_sam_algo_state *algoState,
                        sns_sam_algo_callback const *cbFunc,
                        sns_sam_input_q const *inputData,
                        sns_sam_algo_persist *persistData,
                        uint32_t *processedCnt );

/**
* Generate output data based on current state of algorithm.
*
* AMD will only copy the previous output in this function.
* See sns_sam_algo_generate
*/
sns_sam_err smd_generate( sns_sam_algo_state *algoState,
                          sns_sam_algo_callback const *cbFunc,
                          sns_sam_algo_output *outputData );

/**
* Determine if given configuration is compatible with existing algorithm
* instance
*
* See sns_sam_algo_check_config
*/
bool smd_check_config( sns_sam_algo_state const *algoState,
                       sns_sam_algo_config const *configData );


/* AMD Message API */


/**
* Generates the memory requirements algorithm data buffers that are
* independent of algorithm configuration.
*
* See sns_sam_algo_mem_const_req
*
*/
 void smd_mem_const_req( sns_sam_algo_const_buf_size *bufferSizes );

/**
* Obtain all attributes of an algorithm.
*
* See sns_sam_algo_get_attr
*/
void smd_get_attr( sns_sam_algo_persist const *persistData,
                   sns_sam_algo_attr attributes[] );

/**
* Determine whether the algorithm's sensor dependencies have been met.
*
* See sns_sam_algo_dep_sensors_met
*/
void smd_dep_sensors_met( struct sns_sam_sensor_algo const *algo,
                          sns_sam_algo_all_dep_met depMetFunc,
                          sns_sam_algo_persist *persistData,
                          sns_sam_sensor_uid const *sensorUID,
                          sns_sam_algo_attr const (*sns_sam_attr_array)[ SAM_ALGO_ATTR_CNT ] );

/**
* Determine whether the algorithm's registry dependencies have been met.
*
* See sns_sam_algo_dep_registry_met
*/
void smd_dep_registry_met( struct sns_sam_sensor_algo const *algo,
                           sns_sam_algo_all_dep_met depMetFunc,
                           sns_sam_algo_persist *persistData,
                           sns_sam_reg_data const *regData );

/**
* Provide a list of an algorithm's dependent sensors.
*
* See sns_sam_algo_dep_sensors
*/
sns_sam_err smd_dep_sensors( uint32_t *sensorCount,
                             struct sns_sam_algo_dep_sensor dependentSensors[] );

/**
* Provide a list of an algorithm's registry groups.
*
* See sns_sam_algo_reg_grps
*/
sns_sam_err smd_reg_grps( uint32_t *registryGrpCount,
                          sns_sam_reg_group registryGroups[] );

/**
* Process incoming registry data.
*
* Not used by AMD
*
* See sns_sam_algo_process_reg
*/
sns_sam_err smd_process_reg( sns_sam_reg_data const *regData,
                             sns_sam_algo_state *algoState );

/**
* Process an incoming enable IDL request message for this algorithm.
*
* See sns_sam_algo_process_enable_req
*/
sns_sam_err smd_process_enable_req( sns_sam_enable_req const *enableReq,
                                    sns_sam_algo_persist *persistData,
                                    sns_sam_client_attr *clientAttr,
                                    sns_sam_algo_config *configData );


/**
* Process an incoming indication from one of this algorithm's sensor
* dependencies.
*
* See sns_sam_algo_process_ind
*/
sns_sam_err smd_process_ind( sns_sam_algo_callback const *cbFunc,
                             sns_sam_ind_msg const *indMsg,
                             sns_sam_input_q *inputData );

/**
* Generate an indication from a piece of algorithm output data.
*
* See sns_sam_algo_gen_ind
*/
sns_sam_err smd_gen_ind( sns_sam_algo_callback const *cbFunc,
                         sns_sam_algo_output const *outputData,
                         uint8_t extInstanceID,
                         sns_sam_ind_msg *indMsg );

/**
* Generates the report response message.
*
* See sns_sam_algo_gen_report
*/
sns_sam_err smd_gen_report( sns_sam_algo_output const *outputData,
  sns_sam_resp_msg *respMsg );


/**
* Generates the enable request message for the given dependent sensor.
*
* See sns_sam_algo_gen_req
*/
sns_sam_err smd_gen_req( sns_sam_algo_state const *algoState,
                              sns_sam_sensor_uid const *sensorUID,
                              sns_sam_enable_req *enableReqMsg );

/**
* Check if a proposed sensor dependency request is acceptable to this
* algorithm instance.
*
* There shall always be only one acceptable AMD configuration, therefore this
* function shall return false always.
*
* See sns_sam_algo_check_sensor
*/
bool smd_check_sensor( sns_sam_algo_state const *algoState,
                        sns_sam_enable_req const *enableReq );

/**
* Register the AMD algorithm
*
*
* See sns_sam_algo_register
*/

sns_sam_err smd_sam_register(
      sns_sam_algo_api **algoAPI,
      sns_sam_algo_msg_api **msgAPI,
      qmi_idl_service_object_type *serviceObj,
      sns_sam_sensor_uid *sensorUID );



int32_t smd_usam_mem_req(
   smd_config *config_data);

smd_state* smd_usam_state_reset(
   smd_config *config_data,
   void *mem);

void smd_usam_update(
   smd_state *smd_algo,
   smd_input *input,
   smd_output *output,
   sns_sam_timestamp timestamp);


#endif /* SMD_H */


