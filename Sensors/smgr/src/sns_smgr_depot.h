#ifndef SNS_SMGR_DEPOT_H
#define SNS_SMGR_DEPOT_H
/*=============================================================================
  @file sns_smgr_depot.h

  This header file contains the definitions for internal depot in which sensor
  samples are stored by Sensor Manager (SMGR)

******************************************************************************
* Copyright (c) 2014 Qualcomm Technologies, Inc.  All Rights Reserved.
* Qualcomm Technologies Proprietary and Confidential.
******************************************************************************/

/* $Header: //components/rel/ssc.adsp/2.6.1/smgr/src/sns_smgr_depot.h#2 $ */
/* $DateTime: 2015/05/14 20:46:38 $ */
/* $Author: pwbldsvc $ */

/*============================================================================
  EDIT HISTORY FOR FILE

  when        who  what, where, why
  ----------  ---  -----------------------------------------------------------
  2015-04-21  pn   Fixed deficient depot copy method
  2014-10-26  pn   Updated sns_smgr_depot_dump()
  2014-09-25  pn   Added sns_smgr_depot_dump()
  2014-04-23  pn   Initial revision

============================================================================*/

/*----------------------------------------------------------------------------
 * Include Files
 * -------------------------------------------------------------------------*/
#include "sns_smgr.h"
#include "sns_smgr_priv.h"

/*----------------------------------------------------------------------------
 * Preprocessor Definitions and Constants
 * -------------------------------------------------------------------------*/
typedef struct 
{
  q16_t              data[SNS_SMGR_SENSOR_DIMENSION_V01];
  sns_ddf_time_t     time_stamp;
  sns_ddf_status_e   status;
} sns_smgr_sample_s;

typedef struct 
{
  uint16_t           max_bufs;
  uint16_t           used_bufs;
  uint16_t           first_idx;  /* index to oldest sample */
  uint16_t           last_idx;   /* index to latest sample */
  uint8_t            num_axes;   /* depending on sensor type */
  sns_smgr_sample_s  samples[1]; /* many to be saved */
} sns_smgr_sample_depot_s;

typedef struct
{
  const sns_smgr_sample_depot_s* depot_ptr;
  uint16_t                   idx;
} sns_smgr_sample_depot_iter_s;

/*----------------------------------------------------------------------------
 * Function Declarations and Documentation
 * -------------------------------------------------------------------------*/
void sns_smgr_depot_clear(
   sns_smgr_sample_depot_s* depot_ptr, 
   uint16_t                 num_save);

uint16_t sns_smgr_depot_get_depth(
   const sns_smgr_sample_depot_s*);

uint16_t sns_smgr_depot_get_sample_count(
   const sns_smgr_sample_depot_s*);

const sns_smgr_sample_s* sns_smgr_depot_get_latest_sample(
   const sns_smgr_sample_depot_s*);

const sns_smgr_sample_s* sns_smgr_depot_get_oldest_sample(
   const sns_smgr_sample_depot_s*);

const sns_smgr_sample_s* sns_smgr_depot_init_iter(
   const sns_smgr_sample_depot_s*, 
   sns_ddf_time_t, 
   sns_smgr_sample_depot_iter_s*);

const sns_smgr_sample_s* sns_smgr_depot_get_sample(
   sns_smgr_sample_depot_iter_s*, 
   int8_t);

const sns_smgr_sample_s* sns_smgr_depot_put_sample(
   sns_smgr_sample_depot_s*     depot_ptr, 
   const sns_ddf_sensor_data_s* src_ptr);

void sns_smgr_depot_dump(
  sns_smgr_sample_depot_s* src_depot_ptr, 
  sns_smgr_sample_depot_s* dest_depot_ptr);

#endif /* #ifndef SNS_SMGR_DEPOT_H */

