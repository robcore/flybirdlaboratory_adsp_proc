
#ifndef SNS_SMGR_FIFO_H
#define SNS_SMGR_FIFO_H

/*=============================================================================
  @file sns_smgr_fifo.h

  This file contains the definitions used in SMGR FIFO

******************************************************************************
* Copyright (c) 2014-2015 Qualcomm Technologies, Inc.
* All Rights Reserved.
* Confidential and Proprietary - Qualcomm Technologies, Inc.
******************************************************************************/

/* $Header: //components/rel/ssc.adsp/2.6.1/smgr/src/sns_smgr_fifo.h#2 $ */
/* $DateTime: 2015/05/22 16:04:29 $ */
/* $Author: pwbldsvc $ */

/*============================================================================
  EDIT HISTORY FOR FILE

  when        who  what, where, why
  ----------  ---  -----------------------------------------------------------
  2015-03-10  jms  Removed unused/ineffective discrete FIFO synch code
  2014-09-14  vy   Dynamically allocate Shared fifo data struct 
  2014-04-23  pn   Initial version

============================================================================*/


/*----------------------------------------------------------------------------
 * Include Files
 * -------------------------------------------------------------------------*/
#include "sns_smgr.h"
#include "sns_smgr_sensor_config.h"
#include "sns_ddf_common.h"
#include "sns_log_types.h"

/*----------------------------------------------------------------------------
 * Preprocessor Definitions and Constants
 * -------------------------------------------------------------------------*/

#define SNS_SMGR_FIFO_MAX_DISCR_FIFOS 3

#define SNS_SMGR_FIFO_IS_UNIFIED(sensor_ptr) (sensor_ptr->fifo_cfg.shared_ddf_sens_q.cnt > 0)

/*----------------------------------------------------------------------------
 * Type Declarations
 * -------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------
 * Structure Definitions
 * -------------------------------------------------------------------------*/


//--------------- Unified fifo -----------------
typedef struct
{
  sns_q_link_s        sibling_link;
  sns_smgr_sensor_s*  sensor_ptr;
  smgr_sensor_id_e    sibling_sensor_id;
  sns_ddf_sensor_e    sibling_ddf_sensor_type;
  sns_ddf_handle_t*   sibling_dd_handle_ptr;
} smgr_fifo_shared_sensor_s;

//------------ General fifo support --------------
typedef struct
{
  bool                      is_fifo_enabled;        //true if ( WM > 0 )
  bool                      can_fifo_be_used;
  uint16_t                  suitable_max_watermark; //reserves space for time to read fifo
  uint16_t                  current_watermark;
  uint16_t                  desired_watermark;      //newly requested WM size to set

  //TODO: ----- smgr_fifo_cfg_const_s ------
  //Set only once in sns_smgr_fifo_init_fifo_cfg on get_attr
  bool                      is_fifo_supported;
  bool                      is_hw_watermark_int_supported;
  uint16_t                  max_watermark;          //hardware FIFO size in samples
  //uint16_t                  shared_sensor_cnt;     //sensors sharing unified fifo
  //smgr_fifo_shared_sensor_s shared_ddf_sensor[SNS_SMGR_NUM_SENSORS_DEFINED*SMGR_MAX_DATA_TYPES_PER_DEVICE];
  sns_q_s                   shared_ddf_sens_q;

} smgr_sensor_fifo_cfg_s;

//--------------- Discrete fifo ----------------
typedef struct
{
  /* The lead sensor which interrupt is used as main interrupt for fifo sync. */
  sns_smgr_ddf_sensor_s*   ddf_sensor_sync_intr_ptr;
  /* Fifo sensors active in Report Database */
  sns_smgr_ddf_sensor_s*   ddf_sensors_active_ptr[SNS_SMGR_FIFO_MAX_DISCR_FIFOS];
} sns_smgr_fifo_s;


/*----------------------------------------------------------------------------
 * Public Function Declarations and Documentation
 * -------------------------------------------------------------------------*/
sns_err_code_e sns_smgr_fifo_init_fifo_cfg( sns_smgr_sensor_s *sensor_ptr );

void sns_smgr_fifo_on_event_odr_changed
(
  sns_smgr_ddf_sensor_s*    ddf_sensor_ptr,
  sns_ddf_sensor_e          sensor
);
sns_ddf_status_e sns_smgr_fifo_on_event_fifo_wm_int
(
  const sns_smgr_sensor_s*  sensor_ptr,
  sns_ddf_sensor_e          sensor
);
sns_ddf_status_e sns_smgr_fifo_on_event_fifo_overflow
(
  sns_smgr_sensor_s*        sensor_ptr,
  sns_ddf_sensor_e          sensor
);
sns_ddf_status_e sns_smgr_fifo_on_event_fifo_available
(
  sns_smgr_sensor_s*        sensor_ptr,
  sns_ddf_sensor_e          sensor
);
sns_ddf_status_e sns_smgr_fifo_on_event_fifo_unavailable
(
  sns_smgr_sensor_s*        sensor_ptr,
  sns_ddf_sensor_e          sensor
);


void     sns_smgr_fifo_flush( sns_smgr_sensor_s* sensor_ptr );

uint16_t sns_smgr_fifo_get_suitable_max_watermark( const sns_smgr_sensor_s* sensor_ptr );
void     sns_smgr_fifo_configure( sns_smgr_sensor_s* sensor_ptr );

void sns_smgr_fifo_log_event
(
   const sns_smgr_ddf_sensor_s *ddf_sensor_ptr,
   sns_fifo_event_e             fifo_event
);

/*----------------------------------------------------------------------------
 * Extern Function Declarations
 * -------------------------------------------------------------------------*/
void smgr_get_data(sns_smgr_ddf_sensor_s* in_ddf_sensor_ptr);




#endif /* #ifndef SNS_SMGR_FIFO_H */
