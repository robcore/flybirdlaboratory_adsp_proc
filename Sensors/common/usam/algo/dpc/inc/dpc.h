#ifndef DPC_H
#define DPC_H

/*============================================================================
  @file dpc.h

  Device Position Classifier header file

  Copyright (c) 2010-2014 Qualcomm Technologies, Inc. All Rights Reserved.
  Qualcomm Technologies Proprietary and Confidential
============================================================================*/

/*============================================================================
 * EDIT HISTORY
 *
 * This section contains comments describing changes made to the module.
 * Notice that changes are listed in reverse chronological order.
 *
 * when        who  what, where, why
 * ----------  ---  -----------------------------------------------------------
 * 2013-03-26  yg   initial version
 * 2014-09-07  nc   updated algo and added motion gating
 *
 *============================================================================*/
/**----------------------------------------------------------------------------
 * Include Files
 * --------------------------------------------------------------------------*/

#include <stdint.h>
#include <stdbool.h>
#include "log.h"

#include "sns_sam_algo_api.h"
#include "sns_sam_dpc_v01.h"
#include "sns_sam_algo_api.h"
#include "sns_sam_algo_utils.h"
#include "sns_smgr_internal_api_v02.h"

/* Target specific stuff */
#ifndef OFFTARGET_UNIT_TESTING

#include <fixed_point.h>
#include "sns_memmgr.h"
#define DPC_MEMZERO(x,y) SNS_OS_MEMZERO(x,y)

#endif

/**----------------------------------------------------------------------------
 * Macro Declarations
 * --------------------------------------------------------------------------*/
#define SMGR_GATEDACCEL_UID   (SNS_SMGR_SUID_ACCEL_1_V01 ^ SNS_SMGR_SENSOR_EVENT_ID_MOTION_DETECT_1_V02)

/*Macro for QXDM ids only defined if QXDM has not defined already*/
#ifndef LOG_SNS_DPC_CONFIG_C

#define LOG_SNS_DPC_CONFIG_C                              (0x189B)
#define LOG_SNS_DPC_RESULT_C                              (0x189C)
#define LOG_SNS_DPC_REPORT_C                              (0x189D)

#endif

/*default accel sample rate*/
#define DPC_SAMPLE_RATE_DEF_Q16 FX_CONV_Q16(20, 0) // Default sample rate
#define DPC_PROXIMITY_SAMPLE_RATE_DEF_Q16 FX_CONV_Q16(5, 0) // Default sample rate

/*number of accel input items*/
#define DPC_ACCEL_COLS (3)

/* Thresholds for z-axis angle "criterion" to declare a desk on desk */
#define DPC_ON_DESK_Z_AXIS_THRES_BEGIN 10
#define DPC_ON_DESK_Z_AXIS_THRES_END 170

/* Number of seconds the z-axis criterion needs to be met before declaring that the
   device is on desk. Input timestamp in Accel data arrival is used as a source of clock */
#define DPC_ON_DESK_TIME_TO_STABLE_IN_SECS (3)

/*number of secs to wait before running desk entry detector after pick up*/
#define DPC_DESK_ENTRY_DELAY_AFTER_PICK_UP (3)

#define DPC_DESK_EXIT_SLIDING_WINDOW_SIZE (9) /* Sliding window size needed by Desk Exit detector. T-0.2 to T+0.05+0.2 */
/* Thresholds for Desk exit criteria */
#define DPC_DESK_EXIT_D1 (0.1f)
/* This is N/N-1, where N is 4, as how matlab computes standard deviation */
#define DPC_DESK_EXIT_D2_ADJUSTMENT (1.333f)
#define DPC_DESK_EXIT_D2 (1.0f)
#define DPC_DESK_EXIT_D3 (2.0f)
#define DPC_DESK_EXIT_D4 (2.4376f)
#define DPC_DESK_EXIT_GRAVITY_FILTER (0.025f)
#define DPC_DESK_EXIT_D3_K (3)
/* This is N/N-1, where N is 7, how matlab computes standard deviation */
#define DPC_POCKET_EXIT_D5_ADJUSTMENT (1.1666f)

/* Number of seconds the pocket-entry criterion needs to be met before declaring that the
   device is in pocket. Input timestamp in Accel and proximity data arrival is used as a source of clock*/
#define DPC_IN_POCKET_TIME_TO_STABLE_IN_SECS (4.5f)

/* Sliding window size needed by Pocket Exit detector. T-0.1 to T+0.2 */
#define DPC_POCKET_EXIT_SLIDING_WINDOW_SIZE (7)

/* Thresholds for Pocket exit criteria */
#define DPC_POCKET_EXIT_D5 (0.6461f)
/* Window of accel data (after the proximity transitions from NEAR to FAR ) needed to compute pocket-exit */
#define DPC_POCKET_EXIT_RIGHT_WINDOW_SIZE_IN_SECS (0.2f)
/* 4 accel samples typically consitues 0.2s */
#define DPC_POCKET_EXIT_RIGHT_WINDOW_SIZE (4)

/* Number of seconds the unknown criterion needs to be met before declaring that the
   device is in UNKNOWN state. Input timestamp in Accel and proximity data arrival is used as a source of clock*/
#define DPC_UNKNOWN_TIME_TO_STABLE_IN_SECS (1.5f)


#define DPC_PROXIMITY_NEAR(proximity) (proximity == 65536)
#define DPC_PROXIMITY_FAR(proximity) (proximity == 0)

#define DPC_DEF_SENSOR_REPORT_RATE     4
#define DPC_DEF_SENSOR_REPORT_RATE_Q16 (FX_CONV_Q16(DPC_DEF_SENSOR_REPORT_RATE, 0))
/**----------------------------------------------------------------------------
 * Type Declarations
 * --------------------------------------------------------------------------*/
#define DPC_SLIDING_WINDOW_MAX_SIZE 9
typedef struct
{
  struct {
    float x[DPC_SLIDING_WINDOW_MAX_SIZE];
    float y[DPC_SLIDING_WINDOW_MAX_SIZE];
    float z[DPC_SLIDING_WINDOW_MAX_SIZE];
    int cnt;
    int accel_cnt_after_proximity_toggle;
  } buf;
  uint32_t current_pos;
} dpc_accel_sliding_window;

typedef enum
{
  DPC_ACCEL_INPUT = 1,         // Accel input
  DPC_PROXIMITY_INPUT = 2,     // Proximity input
  DPC_MD_INPUT = 3             // Motion Interrupt
} dpc_input_e;

typedef enum
{
  DPC_STREAM_ACCEL_PERIODIC,
  DPC_STREAM_ACCEL_BUFFERED,
  DPC_STREAM_ACCEL_PAUSE
} dpc_accel_stream_type;

typedef struct
{
  sns_sam_dpc_event_mode_e_v01 event_mode;
  uint32_t accel_sample_rate;     // accel sample rate, Hz, Q16
  uint32_t proximity_sample_rate; // proximity sample rate, Hz, Q16
  bool mdIntAvailable;            //Motion interrupt is available
} dpc_config_s;

/**< Events detected by the DPC Detectors */
typedef enum
{
  DPC_DESK_DETECTOR_NONE = 0,
  DPC_DESK_DETECTOR_DESK_ENTRY_DETECTED = 1,
  DPC_DESK_DETECTOR_DESK_EXIT_DETECTED = 2,
  DPC_DESK_DETECTOR_UNKNOWN_DETECTED = 3,
  DPC_POCKET_DETECTOR_NONE = 4,
  DPC_POCKET_DETECTOR_POCKET_ENTRY_DETECTED = 5,
  DPC_POCKET_DETECTOR_POCKET_EXIT_DETECTED = 6,
  DPC_POCKET_DETECTOR_UNKNOWN_DETECTED = 7,
  DPC_DETECTOR_NUM_EVENT_TYPES = 8,
} dpc_detector_event_e;

/**< Operational state of Detector */
typedef enum
{
  DPC_DETECTOR_OFF = 1,
  DPC_DETECTOR_ON = 2,
} dpc_detector_op_state_e;

/**< Device Position */
typedef enum
{
  DPC_DEVICE_POSITION_ON_DESK = 0,
  DPC_DEVICE_POSITION_IN_POCKET = 1,
  DPC_DEVICE_POSITION_UNKNOWN = 2,
  DPC_NUM_DEVICE_POSITIONS = 3
} dpc_device_position_e;

/**< Current state of the Desk Entry Detector */
typedef enum
{
  DPC_DESK_ENTRY_DETECTOR_INITIAL = 1,
  DPC_DESK_ENTRY_DETECTOR_WAIT_FOR_STABLE_ON_DESK = 2,
  DPC_DESK_ENTRY_DETECTOR_WAIT_FOR_STABLE_UNKNOWN = 3,
} dpc_desk_entry_state_e;

// client specific state structure for desk entry detector
typedef struct
{
  dpc_desk_entry_state_e   state;
  dpc_detector_op_state_e op_state;     /**< Operational state of Detector */
  uint32_t wait_for_stable_on_desk_entry_time; /**< Time at which detector entered WAIT_FOR_STABLE_ON_DESK state */
  uint32_t wait_for_stable_unknown_entry_time; /**< Time at which detector entered WAIT_FOR_STABLE_UNKNOWN state */
  bool desk_entry_detected;
} dpc_desk_entry_detector_state_s;

// client specific state structure for desk exit detector
typedef struct
{
  dpc_desk_entry_state_e    state;
  dpc_detector_op_state_e   op_state;        /**< Operational state of Detector */
  dpc_accel_sliding_window* window;          /**< Reference to the Common accel sliding window for all detectors */
  dpc_accel_sliding_window* gravity_window;  /**< Reference to the Sliding window for gravity vector */
} dpc_desk_exit_detector_state_s;

/**< Current state of the Pocket Entry Detector */
typedef enum
{
  DPC_POCKET_ENTRY_DETECTOR_INITIAL = 1,
  DPC_POCKET_ENTRY_DETECTOR_WAIT_FOR_STABLE_IN_POCKET = 2,
  DPC_POCKET_ENTRY_DETECTOR_WAIT_FOR_STABLE_UNKNOWN = 3
} dpc_pocket_entry_detector_state_e;

// client specific state structure for Pocket Entry detector
typedef struct
{
  dpc_pocket_entry_detector_state_e state;
  dpc_detector_op_state_e           op_state;                             /**< Operational state of Detector */
  uint32_t                          wait_for_stable_in_pocket_entry_time; /**< Time at which detector entered WAIT_FOR_STABLE_IN_POCKET state */
  uint32_t                          wait_for_stable_unknown_entry_time;   /**< Time at which detector entered WAIT_FOR_STABLE_UNKNOWN state */
  int32_t                           prev_proximity;
} dpc_pocket_entry_detector_state_s;

/**< Current state of the Pocket Exit Detector */
typedef enum
{
  DPC_POCKET_EXIT_DETECTOR_INITIAL = 1,
  DPC_POCKET_EXIT_DETECTOR_TENTATIVE_POCKET_EXIT = 2,
  DPC_POCKET_EXIT_DETECTOR_WAIT_FOR_STABLE_UNKNOWN = 3
} dpc_pocket_exit_detector_state_e;

// client specific state structure for Pocket Exit detector
typedef struct
{
  dpc_pocket_exit_detector_state_e state;
  dpc_detector_op_state_e          op_state;                           /**< Operational state of Detector */
  dpc_accel_sliding_window*        window;                             /**< Reference to the Common accel sliding window for all detectors */
  int32_t                          prev_proximity;                     /**< Used to determine whether proximity transitioned from near to far */
  uint32_t                         prox_near_to_far_trans_time;        /**< Time at which proximity transitioned from near to far */
  uint32_t                         wait_for_stable_unknown_entry_time; /**< Time at which detector entered WAIT_FOR_STABLE_UNKNOWN state */
} dpc_pocket_exit_detector_state_s;

// client specific output structure
typedef struct
{
  uint8_t                      client_id;
  sns_sam_timestamp            timestamp;   /**< Timestamp of input with which latest report was computed in SSC ticks */
  sns_sam_dpc_state_e_v01      dpc_event;   /**< Current DPC Event */
  boolean                      dpc_event_generated;
} dpc_client_output_s;

// client specific state structure
typedef struct
{
  boolean                           is_registered;                     /**< false: client not registered; true: client is registered */
  dpc_device_position_e             device_position;                   /**< Overall Current Device Position */
  uint64_t                          device_position_timestamp;         /**< Time in SSC ticks when device position was set */
  dpc_accel_sliding_window          window;                            /**< Common accel sliding window for all detectors */
  dpc_accel_sliding_window          gravity_window;                    /**< Common gravity vector sliding window for all detectors */
  dpc_desk_entry_detector_state_s   desk_entry_detector_state;         /**< Current State of Desk Entry detector */
  dpc_desk_exit_detector_state_s    desk_exit_detector_state;          /**< Current State of Desk Exit detector */
  dpc_pocket_entry_detector_state_s pocket_entry_detector_state;       /**< Current State of Pocket Entry detector */
  dpc_pocket_exit_detector_state_s  pocket_exit_detector_state;        /**< Current State of Pocket Exit detector */
  dpc_client_output_s               dpc_output;                         /**< DPC Output */
} dpc_client_state_s;

/* DPC algorithm state structure */
typedef struct
{
  dpc_config_s                    config;                       // algorithm configuration
  uint64_t                        config_timestamp;             /**< Time in SSC ticks when algorithm is configured */
  dpc_client_state_s              client_data;                  /**client data*/
  dpc_accel_stream_type           accelStatus;
} dpc_state_s;

/**
 * dpc_persist
 * DPC algorithm information to be stored in persistent memory
 *
 * This structure does not need to be protected against concurrent access
 */
typedef struct {
  q16_t          reportRate;            /**< Default reporting rate */
  uint64_t       accel_power;
  uint64_t       proximity_power;
  uint64_t       minSample;
  uint64_t       maxSample;
  uint64_t       minReport;
  uint64_t       maxReport;
  uint64_t       revision;
  int32_t        accel_sample_rate_def;
  int32_t        proximity_sample_rate_def;
  sns_sam_sensor_uid const *accelSUID;
  sns_sam_sensor_uid const *gatedAccelSUID;
  sns_sam_sensor_uid const *proximitySUID;
} dpc_persist_s;

/* DPC algorithm input structure. Make sure the sensor data input is at the beginning of the input structure since
   SAM makes a generic copy into an algo's input struct */
typedef struct
{
  union
  {
    int32_t      accel[DPC_ACCEL_COLS];  /** accel, m/s/s, Q16*/
    int32_t      proximity;
  } data;
  dpc_input_e datatype;                  /** type of input data */
} dpc_input_s;

// DPC output structure
typedef struct
{
  dpc_client_output_s client_data; // client data
} dpc_output_s;

typedef enum
{
  DPC_DEV_POS_TRANS_TABLE_ENTRY_VALID = 1,                         /**< Table entry is valid. Examine the entry to take action */
  DPC_DEV_POS_TRANS_TABLE_ENTRY_NO_OP = 2,                         /**< Table entry is a no op. No action is needed */
  DPC_DEV_POS_TRANS_TABLE_ENTRY_INVALID = 3,                       /**< Table entry is invalid. Signal error if this entry is accessed */
} dpc_device_position_trans_table_entry_type_e;

// Structure of DPC device position transition table entry
typedef struct
{
  dpc_device_position_trans_table_entry_type_e    type;              /**< Type of table entry */
  dpc_device_position_e        next_device_position;                 /**< Next Device Position */
  sns_sam_dpc_state_e_v01      emit_dpc_event;                       /**< DPC event to emit */
} dpc_device_position_trans_table_entry_s;

// Container for operational state of all DPC detectors
// Used to configure what detectors are on/off in various DPC device positions
typedef struct
{
  dpc_detector_op_state_e      desk_entry_detector_op_state;    /**< op state of Desk entry detector */
  dpc_detector_op_state_e      desk_exit_detector_op_state;     /**< op state of Desk exit detector */
  dpc_detector_op_state_e      pocket_entry_detector_op_state;  /**< op state of Pocket entry detector */
  dpc_detector_op_state_e      pocket_exit_detector_op_state;   /**< op state of Pocket exit detector */
} dpc_detectors_op_state_s;

/**----------------------------------------------------------------------------
 * Function Prototypes
 * --------------------------------------------------------------------------*/

/* DPC algorithm API for SAM to register/deregister a client */
bool dpc_sam_register_client(uint8_t client_id, bool action, dpc_state_s *state,
    dpc_output_s *output, sns_sam_timestamp timestamp);

#endif // DPC_H

