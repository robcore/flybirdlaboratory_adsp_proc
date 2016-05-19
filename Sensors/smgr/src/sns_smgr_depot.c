/*=============================================================================
  @file sns_smgr_depot.c

  This file implements the sample depot management functions for SMGR

*******************************************************************************
* Copyright (c) 2014 Qualcomm Technologies, Inc.  All Rights Reserved.
* Qualcomm Technologies Proprietary and Confidential.
********************************************************************************/

/* $Header: //components/rel/ssc.adsp/2.6.1/smgr/src/sns_smgr_depot.c#2 $ */
/* $DateTime: 2015/05/14 20:46:38 $ */
/* $Author: pwbldsvc $ */

/*============================================================================
  EDIT HISTORY FOR FILE

  when        who  what, where, why
  ----------  ---  -----------------------------------------------------------
  2015-04-21  pn   Fixed deficient depot copy method
  2014-10-26  pn   Updated sns_smgr_depot_dump()
  2014-09-25  pn   Added sns_smgr_depot_dump()
  2014-06-05  vy   Further refactored to support uImage  
  2014-04-23  pn   Initial version

============================================================================*/

/*----------------------------------------------------------------------------
 * Include Files
 * -------------------------------------------------------------------------*/
#include "sns_smgr_depot.h"

/*----------------------------------------------------------------------------
 * Preprocessor Definitions and Constants
 * -------------------------------------------------------------------------*/
//#define SNS_SMGR_DEPOT_DEBUG
#ifdef SNS_SMGR_DEPOT_DEBUG
#define SNS_SMGR_DEPOT_DBG0 SNS_SMGR_PRINTF0
#define SNS_SMGR_DEPOT_DBG1 SNS_SMGR_PRINTF1
#define SNS_SMGR_DEPOT_DBG2 SNS_SMGR_PRINTF2
#define SNS_SMGR_DEPOT_DBG3 SNS_SMGR_PRINTF3
#define SNS_SMGR_DEPOT_DBG4 SNS_SMGR_PRINTF4
#else
#define SNS_SMGR_DEPOT_DBG0(level,msg)
#define SNS_SMGR_DEPOT_DBG1(level,msg,p1)
#define SNS_SMGR_DEPOT_DBG2(level,msg,p1,p2)
#define SNS_SMGR_DEPOT_DBG3(level,msg,p1,p2,p3)
#define SNS_SMGR_DEPOT_DBG4(level,msg,p1,p2,p3,p4)
#endif

/*----------------------------------------------------------------------------
 *  Variables
 * -------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
 * Function Declarations and Documentation
 * -------------------------------------------------------------------------*/
/*===========================================================================

  FUNCTION:   sns_smgr_depot_clear

===========================================================================*/
/*!
  @brief Clears sample depot for given sensors

  @param[i] sensor_ptr - the sensor of interest

  @return none
*/
/*=========================================================================*/
void sns_smgr_depot_clear(sns_smgr_sample_depot_s* depot_ptr, uint16_t num_save)
{
  if ( (depot_ptr != NULL) && (depot_ptr->used_bufs > num_save) )
  {
    SNS_SMGR_PRINTF3(
      LOW, "depot_clear - used=%d first_ts=%u last_ts=%u", depot_ptr->used_bufs,
      depot_ptr->used_bufs ? 
      (unsigned)depot_ptr->samples[depot_ptr->first_idx].time_stamp : 0,
      depot_ptr->used_bufs ? 
      (unsigned)depot_ptr->samples[depot_ptr->last_idx].time_stamp : 0 );
    depot_ptr->first_idx = (depot_ptr->last_idx + depot_ptr->max_bufs -
                            num_save + 1) % depot_ptr->max_bufs;
    depot_ptr->used_bufs = num_save;
    SNS_SMGR_PRINTF3(
      LOW, "depot_clear - used=%d first_idx=%d last_idx=%d",
      depot_ptr->used_bufs, depot_ptr->first_idx, depot_ptr->last_idx);
  }
}

/*===========================================================================

  FUNCTION:   sns_smgr_depot_get_sample_count

===========================================================================*/
/*!
  @brief Returns number of samples in the given depot.

  @param[i] depot_ptr - the sample depot

  @return Count of used buffers
*/
/*=========================================================================*/
uint16_t sns_smgr_depot_get_sample_count(const sns_smgr_sample_depot_s* depot_ptr)
{
  uint16_t count = 0;
  if ( depot_ptr != NULL )
  {
    count = depot_ptr->used_bufs;
  }
  return count;
}


/*===========================================================================

  FUNCTION:   sns_smgr_depot_get_oldest_sample

===========================================================================*/
/*!
  @brief Returns pointer to oldest sample in then given depot.

  @param[i] depot_ptr - the sample depot

  @return Read-only poinnter to oldest sample, or NULL if no sample available
*/
/*=========================================================================*/
const sns_smgr_sample_s* sns_smgr_depot_get_oldest_sample(
  const sns_smgr_sample_depot_s* depot_ptr)
{
  const sns_smgr_sample_s* sample_ptr = NULL;
  if ( (depot_ptr != NULL) && (depot_ptr->used_bufs > 0) )
  {
    sample_ptr = &depot_ptr->samples[depot_ptr->first_idx];
  }
  return sample_ptr;
}


/*===========================================================================

  FUNCTION:   sns_smgr_depot_copy_samples

===========================================================================*/
/*!
  @brief Copies @num_samples of samples starting at @src_ptr on to
         the given depot

  @param[i]  src_ptr       - sample array from which to copy
  @param[i]  num_samples   - number of samples in sample array
  @param[io] dst_depot_ptr - destination depot

  @return none
*/
/*=========================================================================*/
SMGR_STATIC void sns_smgr_depot_copy_samples(
  sns_smgr_sample_depot_s* src_depot_ptr, 
  sns_smgr_sample_depot_s* dst_depot_ptr,
  uint16_t                 sample_idx,
  uint16_t                 num_samples)
{
  uint16_t num_slots = dst_depot_ptr->max_bufs - 1 - dst_depot_ptr->last_idx;
  size_t src_size = num_samples*sizeof(sns_smgr_sample_s);
  size_t dst_size;
  SNS_SMGR_DEPOT_DBG4(
     MED, "copy_samples - src idx=%u/%u ts=%u/%u",
     sample_idx, sample_idx+num_samples-1, 
     src_depot_ptr->samples[sample_idx].time_stamp,
     src_depot_ptr->samples[sample_idx+num_samples-1].time_stamp);
  SNS_SMGR_DEPOT_DBG2(
     LOW, "copy_samples - count=%u slots=%u", num_samples, num_slots);
  if ( num_slots >= num_samples )
  {
    SNS_SMGR_DEPOT_DBG3(
       LOW, "copy_samples - src_idx=%u dst_idx=%u #samples=%u",
       sample_idx, dst_depot_ptr->last_idx+1, num_samples);
    SNS_OS_MEMSCPY(
      &dst_depot_ptr->samples[dst_depot_ptr->last_idx+1], 
      num_slots*sizeof(sns_smgr_sample_s), 
      &src_depot_ptr->samples[sample_idx], src_size);
    dst_depot_ptr->last_idx  += num_samples;
  }
  else
  {
    SNS_SMGR_DEPOT_DBG3(
       LOW, "copy_samples - src_idx=%u dst_idx=%u #samples=%u",
       sample_idx, dst_depot_ptr->last_idx+1, num_slots);
    dst_size = num_slots*sizeof(sns_smgr_sample_s);
    SNS_OS_MEMSCPY(
      &dst_depot_ptr->samples[dst_depot_ptr->last_idx+1], dst_size, 
      &src_depot_ptr->samples[sample_idx], dst_size);
    SNS_SMGR_DEPOT_DBG3(
       LOW, "copy_samples - src_idx=%u dst_idx=%u #samples=%u",
       sample_idx+num_slots, 0, num_samples-num_slots);
    SNS_OS_MEMSCPY(
      &dst_depot_ptr->samples[0], 
      (dst_depot_ptr->max_bufs - num_slots)*sizeof(sns_smgr_sample_s), 
      &src_depot_ptr->samples[sample_idx+num_slots], src_size-dst_size);
    dst_depot_ptr->last_idx  = (num_samples - num_slots - 1) % dst_depot_ptr->max_bufs;
  }
  dst_depot_ptr->used_bufs = 
    MIN(dst_depot_ptr->used_bufs + num_samples, dst_depot_ptr->max_bufs);
  if ( dst_depot_ptr->used_bufs == dst_depot_ptr->max_bufs )
  {
    dst_depot_ptr->first_idx = 
      (dst_depot_ptr->last_idx + 1) % dst_depot_ptr->max_bufs;
  }
}


/*===========================================================================

  FUNCTION:   sns_smgr_depot_dump

===========================================================================*/
/*!
  @brief Empties contents of src_depot into dest_depot.

  @param[io] src_depot_ptr  - source
  @param[io] dst_depot_ptr - destination

  @return none
*/
/*=========================================================================*/
void sns_smgr_depot_dump(
  sns_smgr_sample_depot_s* src_depot_ptr, 
  sns_smgr_sample_depot_s* dst_depot_ptr)
{
  if ( src_depot_ptr != NULL && dst_depot_ptr != NULL && 
       src_depot_ptr != dst_depot_ptr && 
       src_depot_ptr->max_bufs < dst_depot_ptr->max_bufs &&
       src_depot_ptr->used_bufs > 0 )
  {
    uint16_t count;
    sns_smgr_sample_depot_iter_s iter;
    sns_ddf_time_t ts = 0;

    SNS_SMGR_DEPOT_DBG4(
       LOW, "depot_dump - src(f/l/u/m)=%u/%u/%u/%u",
       src_depot_ptr->first_idx, src_depot_ptr->last_idx, 
       src_depot_ptr->used_bufs, src_depot_ptr->max_bufs);
    SNS_SMGR_DEPOT_DBG4(
       LOW, "depot_dump - dst(f/l/u/m)=%u/%u/%u/%u",
       dst_depot_ptr->first_idx, dst_depot_ptr->last_idx, 
       dst_depot_ptr->used_bufs, dst_depot_ptr->max_bufs);

    /* iterate to oldest sample in src_depot not already in dest_depot */
    if ( dst_depot_ptr->used_bufs > 0 )
    {
      ts = dst_depot_ptr->samples[dst_depot_ptr->last_idx].time_stamp + 1;
    }
    sns_smgr_depot_init_iter(src_depot_ptr, ts, &iter);

    if ( iter.idx <= src_depot_ptr->last_idx) /* not wrapped around */
    {
      count = src_depot_ptr->last_idx - iter.idx + 1;
      sns_smgr_depot_copy_samples(
        src_depot_ptr, dst_depot_ptr, iter.idx, count );
    }
    else
    {
      count = src_depot_ptr->max_bufs - iter.idx;
      sns_smgr_depot_copy_samples(
        src_depot_ptr, dst_depot_ptr, iter.idx, count );
      sns_smgr_depot_copy_samples(
        src_depot_ptr, dst_depot_ptr, 0, src_depot_ptr->last_idx + 1 );
      count += (src_depot_ptr->last_idx + 1);
    }
    SNS_SMGR_DEPOT_DBG4(
       HIGH, "depot_dump - dst(f/l/u/new)=%u/%u/%u/%u",
       dst_depot_ptr->first_idx, dst_depot_ptr->last_idx, dst_depot_ptr->used_bufs,
       count);
  }
  else if ( src_depot_ptr == NULL || dst_depot_ptr == NULL || 
            src_depot_ptr == dst_depot_ptr )
  {
    SNS_SMGR_PRINTF2(
       ERROR, "depot_dump - src=0x%x dst=0x%x", src_depot_ptr, dst_depot_ptr);
  }
  else /* src and dst are valid and different */
  {
    SNS_SMGR_PRINTF4(
       ERROR, "depot_dump - src(max/used)=%u/%u dst(max/used)=%u/%u",
       src_depot_ptr->max_bufs, src_depot_ptr->used_bufs,
       dst_depot_ptr->max_bufs, dst_depot_ptr->used_bufs);
  }
}

