/*=============================================================================
  @file sns_smgr_depot.c

  This file implements the sample depot management functions for SMGR

*******************************************************************************
* Copyright (c) 2014 Qualcomm Technologies, Inc.  All Rights Reserved.
* Qualcomm Technologies Proprietary and Confidential.
********************************************************************************/

/* $Header: //components/rel/ssc.adsp/2.6.1/smgr/src/sns_smgr_depot_uimg.c#1 $ */
/* $DateTime: 2014/12/01 08:57:58 $ */
/* $Author: pwbldsvc $ */

/*============================================================================
  EDIT HISTORY FOR FILE

  when        who  what, where, why
  ----------  ---  -----------------------------------------------------------
  2014-09-25  pn   Moved sns_smgr_depot_get_depth() to uImage
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

  FUNCTION:   sns_smgr_depot_get_depth

===========================================================================*/
/*!
  @brief Returns max number of samples that can be saved in the given depot.

  @param[i] depot_ptr - the sample depot

  @return Count of buffers
*/
/*=========================================================================*/
uint16_t sns_smgr_depot_get_depth(const sns_smgr_sample_depot_s* depot_ptr)
{
  uint16_t count = 0;
  if ( depot_ptr != NULL )
  {
    count = depot_ptr->max_bufs;
  }
  return count;
}


/*===========================================================================

  FUNCTION:   sns_smgr_depot_get_latest_sample

===========================================================================*/
/*!
  @brief Returns pointer to latest buffered sample of a given sensor/data type pair.

  @param[i] sensor_ptr - the sensor of interest
  @param[i] type       - primary or secondary

  @return Read-only poinnter to latest sample, or NULL if no sample available
*/
/*=========================================================================*/
const sns_smgr_sample_s* sns_smgr_depot_get_latest_sample(
  const sns_smgr_sample_depot_s* depot_ptr)
{
  const sns_smgr_sample_s* sample_ptr = NULL;
  if ( (depot_ptr != NULL) && (depot_ptr->used_bufs > 0) )
  {
    sample_ptr = &depot_ptr->samples[depot_ptr->last_idx];
  }
  return sample_ptr;
}


/*===========================================================================

  FUNCTION:   sns_smgr_depot_put_sample

===========================================================================*/
/*!
  @brief Stores the given sample in the given depot.

  @param[i] depot_ptr - sample depot of a sensor
  @param[i] type       - primary or secondary

  @return Read-only poinnter to oldest sample, or NULL if no sample available
*/
/*=========================================================================*/
const sns_smgr_sample_s* sns_smgr_depot_put_sample(
  sns_smgr_sample_depot_s*     depot_ptr,
  const sns_ddf_sensor_data_s* src_ptr)
{
  depot_ptr->last_idx  = (depot_ptr->last_idx + 1) % depot_ptr->max_bufs;
  depot_ptr->used_bufs = MIN(depot_ptr->used_bufs+1, depot_ptr->max_bufs);
  if ( depot_ptr->used_bufs == depot_ptr->max_bufs )
  {
    depot_ptr->first_idx = (depot_ptr->last_idx + depot_ptr->max_bufs -
                            depot_ptr->used_bufs + 1) % depot_ptr->max_bufs;
  }

  depot_ptr->samples[depot_ptr->last_idx].time_stamp = src_ptr->timestamp;
  depot_ptr->samples[depot_ptr->last_idx].status     = src_ptr->status;
  if (src_ptr->samples != NULL)
  {
    uint8_t i;
    for ( i=0; i<depot_ptr->num_axes; i++ )
    {
      depot_ptr->samples[depot_ptr->last_idx].data[i] = src_ptr->samples[i].sample;
    }
  }
  SNS_SMGR_DEPOT_DBG3(
     LOW, "deposit_sample - 1st=%d last=%d ts=%u",
     depot_ptr->first_idx, depot_ptr->last_idx, 
     depot_ptr->samples[depot_ptr->last_idx].time_stamp);
  return &depot_ptr->samples[depot_ptr->last_idx];
}

/*===========================================================================

  FUNCTION:   sns_smgr_depot_bsearch

===========================================================================*/
/*!
  @brief Performs binary search to find the sample of desired timesamp 
         within the given range of indices.

  @param[i/o] iter_ptr   the iterator on which to operate
  @param[i]   desired_ts the desired timestamp
  @param[i]   low_idx    index of first sample in the series
  @param[i]   hi_idx     index of last sample in the series

  @return Pointer to the sample if found, NULL if not
*/
/*=========================================================================*/
SMGR_STATIC const sns_smgr_sample_s* sns_smgr_depot_bsearch(
  sns_smgr_sample_depot_iter_s* iter_ptr,
  sns_ddf_time_t            desired_ts,
  uint16_t                  low_idx,
  uint16_t                  hi_idx)
{
  const sns_smgr_sample_s* sample_ptr = NULL;
  SNS_SMGR_DEPOT_DBG4(
     MED, "bsearch - idx=%d/%d ts=%u/%u", low_idx, hi_idx,
     iter_ptr->depot_ptr->samples[low_idx].time_stamp,
     iter_ptr->depot_ptr->samples[hi_idx].time_stamp);

  if ( (hi_idx - low_idx) < 2 )
  {
    if ( TICK1_GEQ_TICK2(iter_ptr->depot_ptr->samples[low_idx].time_stamp, desired_ts) )
    {
      iter_ptr->idx = low_idx;
      sample_ptr = &iter_ptr->depot_ptr->samples[iter_ptr->idx];
    }
    else if ( TICK1_GEQ_TICK2(iter_ptr->depot_ptr->samples[hi_idx].time_stamp, desired_ts) )
    {
      iter_ptr->idx = hi_idx;
      sample_ptr = &iter_ptr->depot_ptr->samples[iter_ptr->idx];
    }
  }
  else if ( TICK1_GEQ_TICK2(iter_ptr->depot_ptr->samples[hi_idx].time_stamp, desired_ts) )
  {
    uint16_t mid_idx = low_idx + ((hi_idx - low_idx) >> 1);
    if ( TICK1_GTR_TICK2(iter_ptr->depot_ptr->samples[mid_idx].time_stamp, desired_ts) )
    {
      /* desired timestamp is within lower portion */
      sample_ptr = sns_smgr_depot_bsearch(iter_ptr, desired_ts, low_idx, mid_idx);
    }
    else if ( TICK1_GTR_TICK2(desired_ts, 
                              iter_ptr->depot_ptr->samples[mid_idx].time_stamp) )
    {
      /* desired timestamp is within upper portion */
      sample_ptr = sns_smgr_depot_bsearch(iter_ptr, desired_ts, mid_idx, hi_idx);
    }
    else
    {
      iter_ptr->idx = mid_idx;
      sample_ptr = &iter_ptr->depot_ptr->samples[iter_ptr->idx];
    }
  }
  return sample_ptr;
}


/*===========================================================================

  FUNCTION:   sns_smgr_depot_init_iter

===========================================================================*/
/*!
  @brief Initializes the given iterator with the given sample depot and
         returns the sample of given timestamp or first samples in depot if
         given timestamp is in the past.

  @param[in]  depot_ptr sample depot of a sensor
  @param[in]  ts        timestamp of sample to find in depot
  @param[out] iter_ptr  the iterator to be initialized

  @return Pointer to the sample if found, NULL if not
*/
/*=========================================================================*/
const sns_smgr_sample_s* sns_smgr_depot_init_iter(
  const sns_smgr_sample_depot_s* depot_ptr,
  sns_ddf_time_t                 ts,
  sns_smgr_sample_depot_iter_s*  iter_ptr)
{
  const sns_smgr_sample_s* sample_ptr = NULL;
  if ( (depot_ptr != NULL) && (iter_ptr != NULL) && (depot_ptr->used_bufs > 0) )
  {
    SNS_SMGR_DEPOT_DBG4(
      HIGH, "depot_init_iter - desired_ts=%u avail=%d 1st=%d last=%d", 
      ts, depot_ptr->used_bufs, depot_ptr->first_idx, depot_ptr->last_idx);

    iter_ptr->depot_ptr = depot_ptr;
    if ( depot_ptr->first_idx <= depot_ptr->last_idx ) /* not wrapped around */
    {
      sample_ptr = sns_smgr_depot_bsearch(iter_ptr, ts, depot_ptr->first_idx, 
                                          depot_ptr->last_idx);
    }
    else if ( NULL == (sample_ptr = sns_smgr_depot_bsearch(iter_ptr, ts,
                                                           depot_ptr->first_idx, 
                                                           depot_ptr->max_bufs-1)) )
    {
      sample_ptr = sns_smgr_depot_bsearch(iter_ptr, ts, 0, depot_ptr->last_idx);
    }
    if ( sample_ptr == NULL )
    {
      iter_ptr->depot_ptr = NULL;
    }
    SNS_SMGR_DEPOT_DBG4(
       MED, "depot_iter_ext - returning %u idx=%d 1st=%u last=%u", 
       sample_ptr?sample_ptr->time_stamp:0, sample_ptr?iter_ptr->idx:-1,
       depot_ptr->samples[depot_ptr->first_idx].time_stamp, 
       depot_ptr->samples[depot_ptr->last_idx].time_stamp);
  }
  return sample_ptr;
}


/*===========================================================================

  FUNCTION:   sns_smgr_depot_get_sample

===========================================================================*/
/*!
  @brief Returns pointer to the "next" buffered sample from the current sample
  referenced by the iterator.

  @param[i] iter_ptr - the sample depot interator
  @param[i] next     - 0=current,
                       greater than 0=forward "next" indices,
                       less than 0=backward "next" indices

  @return Read-only poinnter to next sample, or NULL if no sample available
*/
/*=========================================================================*/
const sns_smgr_sample_s* sns_smgr_depot_get_sample(
  sns_smgr_sample_depot_iter_s* iter_ptr, 
  int8_t                        next)
{
  const sns_smgr_sample_s* sample_ptr = NULL;
  if ( (iter_ptr != NULL) && (iter_ptr->depot_ptr != NULL) &&
       (iter_ptr->depot_ptr->used_bufs > 0) )
  {
    int8_t i = 0;
    if ( next > 0 )
    {
      while ( (iter_ptr->idx != iter_ptr->depot_ptr->last_idx) && (i < next) )
      {
        iter_ptr->idx = (iter_ptr->idx + 1) % iter_ptr->depot_ptr->max_bufs;
        i++;
      }
    }
    else if ( next < 0 )
    {
      while ( (iter_ptr->idx != iter_ptr->depot_ptr->first_idx) && (i > next) )
      {
        iter_ptr->idx = (iter_ptr->idx + iter_ptr->depot_ptr->max_bufs
                         - 1) % iter_ptr->depot_ptr->max_bufs;
        i--;
      }
    }
    if ( i == next )
    {
      sample_ptr = &iter_ptr->depot_ptr->samples[iter_ptr->idx];
      SNS_SMGR_DEPOT_DBG2(LOW, "get_sample - idx=%d ts=%u",
                          iter_ptr->idx, sample_ptr->time_stamp);
    }
  }
  return sample_ptr;
}

