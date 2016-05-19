#ifndef DISTANCE_BOUND_H
#define DISTANCE_BOUND_H

/*=============================================================================
Qualcomm Distance Bound header file 

Copyright (c) 2013-2014 Qualcomm Technologies Incorporated.  All Rights Reserved.
QUALCOMM Proprietary and Confidential.
=============================================================================*/

/*============================================================================
* EDIT HISTORY
*
* This section contains comments describing changes made to the module.
* Notice that changes are listed in reverse chronological order.
*
* when        who  what, where, why
* ----------  ---  -----------------------------------------------------------
* 2014-04-04  MW   Removed log.h inclusion
* 2013-03-26  yg   initial version
*
*============================================================================*/
/**----------------------------------------------------------------------------
* Include Files
* --------------------------------------------------------------------------*/

#include <stdint.h>
#include <stdbool.h>
#include "sns_sam_distance_bound_v01.h"
#include "sns_sam_algo_api.h"

/* Target specific stuff */
#ifndef OFFTARGET_UNIT_TESTING

//#include "sns_sam_priv.h"
#include "sns_sam_algo_utils.h"
#include <fixed_point.h>
#include "sns_memmgr.h"

#define DB_MEMZERO(x,y) SNS_OS_MEMZERO(x,y)

#else

#define DB_MEMZERO(x,y) memset(x,0,y)

#endif

/**----------------------------------------------------------------------------
* Macro Declarations
* --------------------------------------------------------------------------*/

//TODO: Move them to right file
#define SNS_SAM_ONE_SHOT_PERIOD_REQ_NONE  -1
#define SNS_SAM_ONE_SHOT_PERIOD_REQ_DISABLE  -2
#define SNS_SAM_ONE_SHOT_PERIOD_REQ_ENABLE  -3
#define SNS_SAM_MIN_ONE_SHOT_PERIOD  5 // in microseconds
#define SNS_SAM_PROCESSING_DELAY  1

#define DISTANCE_BOUND_MOTION_STATE_NUM 9

// The max limit is due to the system limitation of a uint32 timer.
// Because the timer is in microseconds, the max the timer can be set for is 4294
// seconds. With a min speed of 2 meters/sec, the maximum distance bound ends being
// ~ 8500 meters
#define DISTANCE_BOUND_MAX_BOUND_ALLOWED_IN_METERS 8500
#define DISTANCE_BOUND_MIN_BOUND_ALLOWED_IN_METERS 0

#define DISTANCE_BOUND_DELAYED_BREACH_TRUE  1
#define DISTANCE_BOUND_DELAYED_BREACH_FALSE 0

/**----------------------------------------------------------------------------
* Type Declarations
* --------------------------------------------------------------------------*/

/* input datatypes */
typedef enum 
{
  DISTANCE_BOUND_INACTIVE = 0,
  DISTANCE_BOUND_ACTIVE = 1 
} distance_bound_algo_state_e;

typedef enum 
{
  DISTANCE_BOUND_SET_DISTANCE_BOUND = 0, // Set distance bound from client
  DISTANCE_BOUND_MOTION_STATE_INPUT = 1, // motion state input from CMC
  DISTANCE_BOUND_REFRESH_OUTPUT = 2,      // Refresh algo output
} distance_bound_input_e;
  
typedef struct
{
   float motion_state_speed_bounds[DISTANCE_BOUND_MOTION_STATE_NUM];
} distance_bound_config_s;

/**
* Distance Bound persistant data
*/
typedef struct {
  bool cmcAvailable; /* CMC availibility */
  bool regDataAvailable; /* Registry data available*/
  uint64_t power;
  uint64_t minSample;
  uint64_t maxSample;
  sns_sam_sensor_uid const *cmcSUID;
  float motionStateSpeedBounds[DISTANCE_BOUND_MOTION_STATE_NUM];
} distance_bound_persist_s;

// client specific state structure
typedef struct
{
   uint8_t               client_id;
   boolean               is_registered;                /**< false: client not registered; true: client is registered */
   uint8_t               algo_state;                   /**< 0: inactive 1: active                          */
   uint8_t               prev_cmc_motion_state;        /**< Motion State used at last distance bound computation */
   sns_sam_timestamp     prev_motion_state_predated_timestamp;               /**< Time stamp at last distance bound computation  */
   sns_sam_timestamp     prev_motion_state_received_timestamp;               /**< Time stamp at last distance bound computation  */
   float                 prev_speed;                   /**< Speed at last distance bound computation       */
   boolean               is_simultaneous_state;        /**< true: CMC last reported simultaneous states; false: CMC did not last report simultaneous states  */
   uint8_t               prev_simultaneous_cmc_state;  /**< Previous simultaneous CMC state                */
   float                 time_to_breach;               /**< Time to breach of client set bound             */
   float                 distance_bound;               /**< Initial distance bound value in meters         */
   float                 remaining_distance;           /**< Remaining distance in meters                   */
   uint8_t               session_key;
   int32_t               one_shot_period_status;
   uint32_t              one_shot_period;
   float                 distance_accumulated;        /**< distance accumulated in meters */
   sns_sam_distance_bound_breach_event_e_v01 is_distance_bound_breached;
   uint8_t               is_delayed_breach;            /**< is delayed breach              */
} distance_bound_client_state_s;

/* Distance Bound algorithm state structure */
typedef struct
{
  boolean                 is_configured;                /**< false: not configured; true: configured */
  distance_bound_config_s config; // algorithm configuration
  sns_sam_timestamp       config_timestamp;                 /**< Time in SSC ticks when algorithm is configured */
  distance_bound_client_state_s client_data; // client data
} distance_bound_state_s;

typedef struct
{
  uint8_t motion_state;
  uint8_t motion_event;
  uint32_t predated_event_timestamp;
} cmc_motion_event_s;

/* Distance Bound algorithm input structure */
typedef struct
{
  union
  {
    uint8_t                  session_key;           /**< A unique key provided by the client that identifies the session associated
                                                        with the sns_sam_distance_bound_set_bound_req_msg. A session is defined as
                                                        the period between the arrival of a sns_sam_distance_bound_set_bound_req_msg
                                                        and the generation of a sns_sam_distance_bound_report_ind_msg associated with
                                                        it. */
    float                    distance_bound;        /**< distance bound setting from client  */
    cmc_motion_event_s       cmc_motion_event;      /**< Motion event input from CMC         */
    uint8_t                  client_req_id;         /**< client request id                   */
  } data;
  distance_bound_input_e datatype; // type of input data
} distance_bound_input_s;

// client specific output structure
typedef struct
{
  uint8_t client_id;
  uint8_t session_key;                   /**< A unique key provided by the client that identifies the session associated
                                                with the sns_sam_distance_bound_set_bound_req_msg. A session is defined as
                                                the period between the arrival of a sns_sam_distance_bound_set_bound_req_msg
                                                and the generation of a sns_sam_distance_bound_report_ind_msg associated with
                                                it. */
  int32_t one_shot_period_status;        /* Set to one of:
                                                SNS_SAM_ONE_SHOT_PERIOD_REQ_NONE
                                                SNS_SAM_ONE_SHOT_PERIOD_REQ_DISABLE
                                                SNS_SAM_ONE_SHOT_PERIOD_REQ_ENABLE */
  uint32_t one_shot_period;              /* Valid only when one_shot_period_status is set to SNS_SAM_ONE_SHOT_PERIOD_REQ_ENABLE (in microseconds) */
  sns_sam_timestamp timestamp; // Timestamp of input with which latest distance bound report was computed in SSC ticks
  float        distance_accumulated;        /**< distance accumulated in meters */
  sns_sam_distance_bound_breach_event_e_v01 is_distance_bound_breached;
                    /*
                      Indicates if the distance bound set by client has been breached.
                      Set to SNS_SAM_DISTANCE_BOUND_BREACH_EVENT_UNKNOWN if
                      no sns_sam_distance_bound_set_bound_req_msg has been received. All other
                      output fields are to be ignored.
                      Set to SNS_SAM_DISTANCE_BOUND_BREACH_EVENT_TRUE if breach has occurred.
                      Set to SNS_SAM_DISTANCE_BOUND_BREACH_EVENT_FALSE if breach has not occurred.
                    */
  uint8_t       is_delayed_breach;            /**< is delayed breach              */
} distance_bound_client_output_s;

// Distance Bound output structure
typedef struct
{
  distance_bound_client_output_s client_data; // client data
} distance_bound_output_s;

/* Process Set Distance bound request from client */
void set_distance_bound(distance_bound_state_s *state,
    const distance_bound_input_s *input,
    distance_bound_output_s *output,
    sns_sam_timestamp input_timestamp);

/* Handle timer logic for distance bound */
sns_sam_err distance_bound_handle_timer_logic(
    sns_sam_algo_callback const *cbFunc,
    distance_bound_state_s* state);

/* Logging functionality */
void db_log_result(
    sns_sam_algo_callback const *cbFunc,
    distance_bound_input_s const *input,
    distance_bound_state_s const *state,
    sns_sam_timestamp inputBufferTimestamp);

float distance_bound_process_get_max_distance_supported(void);

#endif // DISTANCE_BOUND_H

