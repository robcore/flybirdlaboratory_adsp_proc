/** 
 * @file sns_ddf_util.c
 * @brief Utility library providing common services to drivers.
 *  
 * Copyright (c) 2010 - 2014 Qualcomm Technologies, Inc.  All Rights Reserved.
 * Qualcomm Technologies Proprietary and Confidential.
 
*/

/*==============================================================================
  Edit History

  This section contains comments describing changes made to the module. Notice
  that changes are listed in reverse chronological order. Please use ISO format
  for dates.

  $Header: //components/rel/ssc.adsp/2.6.1/ddf/src/sns_ddf_uimg_util.c#2 $
  $DateTime: 2014/12/12 18:16:56 $

  when       who  what, where, why 
  ---------- ---  -----------------------------------------------------------
  2014-12-10 MW   Included sns_ddf_signal_priv.h
  2014-09-17 vy   Updated mfree/malloc_ex to handle NULL sensor_handle
  2014-09-14 vy   Moved ddf_mfree to BigImage
  2014-09-08 pn   Fixed crash caused by double freeing memory
  2014-08-23 vy   Added QDSS logs and added data access protection in uImage
  2014-08-23 vy   Used new DDF apis to allocate/free mem supported in uImage
  2014-07-22 ps   Fix compiler warnings
  2014-07-09 vy   Added support for non-uimage dd
  2014-06-05 vy   Refactored for uImage 
==============================================================================*/

#include "sns_ddf_util.h"
#include "sns_ddf_util_priv.h"
#include "sns_smgr_ddf_if.h"


#define __SNS_MODULE__ SNS_DDF


sns_ddf_status_e sns_ddf_malloc_ex(void** ptr, uint16_t size, sns_ddf_handle_t sensor_handle)
{
    bool  is_uimg_refac = sns_smgr_get_uimg_refac(sensor_handle); 
    
    if ( sensor_handle == NULL || is_uimg_refac  )
    {
      *ptr = SNS_OS_ANY_MALLOC(SNS_DBG_MOD_DSPS_DDF, size);
    }
    else
    {
      if( sns_ddf_smgr_is_in_uimage() )
          return SNS_DDF_EFAIL;
      *ptr = SNS_OS_MALLOC(SNS_DBG_MOD_DSPS_DDF, size);
    }
    return (*ptr != NULL) ? SNS_DDF_SUCCESS : SNS_DDF_ENOMEM;
}


sns_ddf_status_e sns_ddf_mfree_ex(void* ptr, sns_ddf_handle_t sensor_handle)
{
    bool  is_uimg_refac = sns_smgr_get_uimg_refac(sensor_handle); 

    if(ptr == NULL )
    {
      return SNS_DDF_EFAIL;
    }
    if ( sensor_handle == NULL || is_uimg_refac )
    {
        SNS_OS_ANY_FREE(ptr);
    }
    else
    {
      if( sns_ddf_smgr_is_in_uimage() )
          return SNS_DDF_EFAIL;
      SNS_OS_FREE(ptr);
    }
    return SNS_DDF_SUCCESS;
}


/** Helper function to convert common error codes to DDF error codes. */
sns_ddf_status_e sns_ddf_convert_common_status(sns_err_code_e err)
{
    /* For now all we need is pass/fail. */
    return (err == SNS_SUCCESS) ? SNS_DDF_SUCCESS : SNS_DDF_EFAIL;
}

   
sns_ddf_time_t sns_ddf_get_timestamp(void)
{
    return sns_em_get_timestamp();
}


uint32_t sns_ddf_convert_usec_to_tick(uint32_t usec)
{
    return sns_em_convert_usec_to_dspstick(usec);
}


void sns_ddf_delay(uint32_t usec)
{
  uint64_t  usec_long;
  uint32_t  start_tick, wait_tick;

#ifdef VIRTIO_BRINGUP
  /* it takes long time to busy-wait on Virtio */
  if (usec > 1000)
    usec = 1000;
#endif

#if !defined(SNS_PCSIM)
# if !defined(QDSP6)
    DALSYS_BusyWait(usec);
# else
    usec_long = usec;
    start_tick = sns_ddf_get_timestamp();
    wait_tick = (usec_long * 32768 + (1000000-1)) / 1000000;  /* at least one tick */
    while ( ( sns_ddf_get_timestamp() - start_tick ) < wait_tick )
    {
      ;
    }
# endif
#endif
}


void sns_ddf_map_axes(sns_ddf_axes_map_s* axes_map, q16_t* device_data)
{
    static q16_t tmp[3];
#if 0
    SNS_OS_MEMSCPY(tmp, sizeof(tmp), device_data, sizeof(tmp));
    device_data[0] = tmp[axes_map->indx_x] * axes_map->sign_x;
    device_data[1] = tmp[axes_map->indx_y] * axes_map->sign_y;
    device_data[2] = tmp[axes_map->indx_z] * axes_map->sign_z;
#endif
    tmp[0] = device_data[axes_map->indx_x] * axes_map->sign_x;
    tmp[1] = device_data[axes_map->indx_y] * axes_map->sign_y;
    tmp[2] = device_data[axes_map->indx_z] * axes_map->sign_z;
    device_data[0] = tmp[0];
    device_data[1] = tmp[1];
    device_data[2] = tmp[2];	
}


void sns_ddf_map_axes_multiple(const sns_ddf_axes_map_s* axes_map, 
                               sns_ddf_sensor_data_s* data_ptr)
{
    q16_t tmp[3];
    uint16_t i;
    for (i=0; i<data_ptr->num_samples; i+=3) /* num_samples is multiple of 3 */
    {
        tmp[0] = data_ptr->samples[i].sample;
        tmp[1] = data_ptr->samples[i+1].sample;
        tmp[2] = data_ptr->samples[i+2].sample;
        data_ptr->samples[i].sample   = tmp[axes_map->indx_x] * axes_map->sign_x;
        data_ptr->samples[i+1].sample = tmp[axes_map->indx_y] * axes_map->sign_y;
        data_ptr->samples[i+2].sample = tmp[axes_map->indx_z] * axes_map->sign_z;
    }
}



sns_ddf_status_e sns_ddf_timer_start(sns_ddf_timer_s timer, uint32_t usec)
{
    sns_err_code_e status;
    
    if ( sns_em_is_utimer(timer->em_timer) )
    {
        status = sns_em_register_utimer(
            timer->em_timer, 
            sns_em_convert_usec_to_localtick(usec));
    }
    else
    {
        sns_smgr_enter_bigimage();
        status = sns_em_register_timer(
            timer->em_timer, 
            sns_em_convert_usec_to_localtick(usec));
        sns_smgr_exit_bigimage();
    }
    return sns_ddf_convert_common_status(status);
}


sns_ddf_status_e sns_ddf_timer_cancel(sns_ddf_timer_s timer)
{
    sns_err_code_e status;
    
    if ( sns_em_is_utimer(timer->em_timer) )
    {
      status = sns_em_cancel_utimer(timer->em_timer);
    }
    else
    {
      sns_smgr_enter_bigimage();
      status = sns_em_cancel_timer(timer->em_timer);
      sns_smgr_exit_bigimage();
    }

    return sns_ddf_convert_common_status(status);
}


sns_ddf_status_e sns_ddf_timer_release(sns_ddf_timer_s timer)
{
    sns_err_code_e status;

    sns_smgr_enter_bigimage();
    if ( sns_em_is_utimer(timer->em_timer) )
    {
      status = sns_em_delete_utimer_obj(timer->em_timer);
      if ( status == SNS_SUCCESS )
      {
        SNS_OS_ANY_FREE(timer);
      }
    }
    else
    {
      status = sns_em_delete_timer_obj(timer->em_timer);
      if ( status == SNS_SUCCESS )
      {
        SNS_OS_FREE(timer);
      }
    }
    sns_smgr_exit_bigimage();

    return sns_ddf_convert_common_status(status);
}


void sns_ddf_timer_dispatch(sns_ddf_timer_s timer)
{
#ifndef SNS_QDSP_SIM
    sns_profiling_log_qdss(SNS_SMGR_DD_ENTER_HANDLE_TIME, 0);
    if( timer->is_uimg_refac == FALSE )
    {
      sns_smgr_enter_bigimage();
    }
    timer->dd_interface->handle_timer(timer->dd_handle, timer->arg);
    if( timer->is_uimg_refac == FALSE )
    {
      sns_smgr_exit_bigimage();
    }
    sns_profiling_log_qdss(SNS_SMGR_DD_EXIT, 1, SNS_QDSS_DD_HANDLE_TIMER);
#endif
}


sns_ddf_status_e sns_ddf_mutex_lock(sns_ddf_handle_t handle)
{
    return SNS_DDF_EFAIL;
}


sns_ddf_status_e sns_ddf_mutex_release(sns_ddf_handle_t handle)
{
    return SNS_DDF_EFAIL;
}

