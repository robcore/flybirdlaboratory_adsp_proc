#ifndef EGS_H
#define EGS_H

/*=============================================================================
  Event Gated Sensor Service header file 
 
  Copyright (c) 2014 Qualcomm Technologies, Inc.  All Rights Reserved.
  Qualcomm Technologies Proprietary and Confidential.
=============================================================================*/

/*===========================================================================
  Include Files
  ===========================================================================*/
#include <stdint.h>
#include <stdbool.h>
#include "sns_buffer.h"
#include "sns_sam_qmd_v01.h"
#include "sns_memmgr.h"
#include "sns_sam_algo_api.h"
#include "sns_smgr_api_v01.h"


/*============================================================================
  Type Declarations
  ===========================================================================*/

typedef struct
{
  uint64_t eventSuid;               // SUID of the event sensor
  uint8_t  gatingCondition;         // When event sensor is in this state, stream is gated
  uint32_t streamingItemLen;       // Buffering request of the streaming sensor
  sns_smgr_buffering_req_item_s_v01 streamingItem[SNS_SMGR_BUFFERING_REQUEST_MAX_ITEMS_V01];
  q16_t reportPeriod;               // Report period
} egs_config_s;

// Event Gated Stream algorithm input type enumeration
typedef enum
{
  EGS_INPUT_STREAM = 0,
  EGS_INPUT_EVENT    = 1
} egs_input_type_e;

/* Event Gated Sensor input data */
typedef struct
{
  union
  {
    sns_sam_motion_state_e_v01 motionState;
	sns_smgr_buffering_ind_msg_v01 bufferingInd;
  } inputData;
  egs_input_type_e inputType;       // Input type - EGS_INPUT_EVENT/EGS_INPUT_STREAM 
  uint32_t bufferingIndSize;        // Size of buffering indication
} egs_input_s;

/* Event Gated Sensor output data */
typedef struct
{
  sns_smgr_buffering_ind_msg_v01 bufferingInd;       // Buferring Indication
  uint32_t bufferingIndSize;
} egs_output_s;

/* Event Gated Sensor state data */
typedef struct
{
  egs_config_s config;
  uint8_t  eventState;            // Current state of the event sensor
  bool streamStatus;              // Whether stream should be enabled
} egs_state_s;

/* Event Gated Sensor persisitent data */
typedef struct {
  uint64_t power;
  bool eventAvailable;             // Event sensor is available 
  sns_sam_sensor_uid const *accelSUID;
  sns_sam_sensor_uid const *eventSUID;
} egs_persist_s;

#endif
