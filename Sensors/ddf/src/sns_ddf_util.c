/** 
 * @file sns_ddf_util.c
 * @brief Utility library providing common services to drivers.
 *  
 * Copyright (c) 2010 - 2013 Qualcomm Technologies, Inc.  All Rights Reserved.
 * Qualcomm Technologies Proprietary and Confidential.
 
*/

/*==============================================================================
  Edit History

  This section contains comments describing changes made to the module. Notice
  that changes are listed in reverse chronological order. Please use ISO format
  for dates.

  $Header: //components/rel/ssc.adsp/2.6.1/ddf/src/sns_ddf_util.c#2 $
  $DateTime: 2014/12/12 18:16:56 $

  when       who  what, where, why 
  ---------- ---  -----------------------------------------------------------
  2014-12-10 MW   Included sns_ddf_signal_priv.h
  2014-09-14 vy   Moved ddf_mfree to BigImage
  2014-08-23 vy   Used new DDF apis to allocate/free mem supported in uImage
  2014-07-09 vy   Added support for non-uimage dd
  2014-06-05 vy   Refactored for uImage
  2013-11-18 pn   Added sns_ddf_convert_usec_to_tick()
  2013-10-31 hw   add QDSS SW events
  2013-09-06 pn   Added sns_ddf_map_axes_multiple()
  2013-06-11 ae   Added QDSP SIM playback support
  2013-01-31 br   Updated sns_ddf_delay()
  2012-01-19 jh   Updated definition of sensor axes mapping
  2011-12-13 yk   Replaced call to memcpy with SNS_OS_MEMCOPY.
  2011-11-14 jhh  Updated sns_os_free call to meet new API
  2011-10-02 yk   Made the timer object definition internal to this module.
  2011-08-27 yk   Added check for null pointers in timer_init.
  2011-01-21 sc   Use local ticks instead of hard-coded DSPS ticks.
  2010-12-03 pg   Added __SNS_MODULE__ to be used by OI mem mgr in debug builds.
  2010-09-24 yk   Implemented timer functions. Added timer_dispatch().
  2010-08-25 yk   Implemented sns_ddf_delay() for target builds.
  2010-08-04 yk   Initial revision
==============================================================================*/

#include "sns_ddf_util.h"
#include "sns_ddf_util_priv.h"

#define __SNS_MODULE__ SNS_DDF

extern sns_ddf_status_e sns_ddf_convert_common_status(sns_err_code_e err);


sns_ddf_status_e sns_ddf_malloc(void** ptr, uint16_t size)
{
    *ptr = SNS_OS_MALLOC(SNS_DBG_MOD_DSPS_DDF, size);
    return (*ptr != NULL) ? SNS_DDF_SUCCESS : SNS_DDF_ENOMEM;
}


sns_ddf_status_e sns_ddf_mfree(void* ptr)
{
    if(ptr == NULL)
    {
        return SNS_DDF_EFAIL;
    }

    SNS_OS_FREE(ptr);
    return SNS_DDF_SUCCESS;
}


sns_ddf_status_e sns_ddf_timer_init(
    sns_ddf_timer_s*      timer_ptr,
    sns_ddf_handle_t      dd_handle,
    sns_ddf_driver_if_s*  dd_interface,
    void*                 arg,
    bool                  periodic)
{
    sns_err_code_e   status;
    sns_ddf_status_e ddf_status;
    sns_ddf_timer_s  timer;
    bool             is_uimg_refac = sns_ddf_smgr_get_uimg_refac(dd_handle);

    if(dd_interface->handle_timer == NULL)
        return SNS_DDF_EINVALID_PARAM;

    if ( is_uimg_refac )
    {
      timer = SNS_OS_ANY_MALLOC(SNS_DBG_MOD_DSPS_DDF, sizeof(sns_ddf_timer_obj_s));
    }
    else
    {
      timer = SNS_OS_MALLOC(SNS_DBG_MOD_DSPS_DDF, sizeof(sns_ddf_timer_obj_s));
    }
    ddf_status = (timer != NULL) ? SNS_DDF_SUCCESS : SNS_DDF_ENOMEM;
    if(ddf_status != SNS_DDF_SUCCESS)
        return ddf_status;

    timer->dd_handle = dd_handle;
    timer->dd_interface = dd_interface;
    timer->arg = arg;
    timer->is_uimg_refac = is_uimg_refac;

    /* Create the timer with SMGR's callback function since it is responsible
     * for dispatching the driver's actual callback at its discretion. */
    if ( is_uimg_refac )
    {
      status = sns_em_create_utimer_obj(
          sns_ddf_smgr_notify_timer,
          timer,
          periodic ? SNS_EM_TIMER_TYPE_PERIODIC : SNS_EM_TIMER_TYPE_ONESHOT,
          &timer->em_timer);
      ddf_status = sns_ddf_convert_common_status(status);
    }
    else
    {
      status = sns_em_create_timer_obj(
          sns_ddf_smgr_notify_timer,
          timer,
          periodic ? SNS_EM_TIMER_TYPE_PERIODIC : SNS_EM_TIMER_TYPE_ONESHOT,
          &timer->em_timer);
      ddf_status = sns_ddf_convert_common_status(status);
    }

    if ( ddf_status == SNS_DDF_EFAIL )
    {
      if (is_uimg_refac)
      {
        SNS_OS_ANY_FREE(timer->em_timer);
        SNS_OS_ANY_FREE(timer);
      }
      else
      {
        SNS_OS_FREE(timer->em_timer);
        SNS_OS_FREE(timer);
      }
      return ddf_status;
    }

    *timer_ptr = timer;
    return ddf_status; 
}


sns_ddf_handle_t sns_ddf_mutex_create(void)
{
    return NULL;
}


sns_ddf_status_e sns_ddf_mutex_delete(sns_ddf_handle_t handle)
{
    return SNS_DDF_EFAIL;
}


/** Returns true if 'value' is a valid axes map registry value. */
static bool sns_ddf_axes_map_is_reg_value_valid(const int8_t value)
{
    return (value != 0) && (value >= -3) && (value <= 3);
}


/** Returns true if 'registry_data' contains all valid axes map values. */
static bool sns_ddf_axes_map_is_reg_data_valid(const int8_t* registry_data)
{
    return (registry_data != NULL) &&
        sns_ddf_axes_map_is_reg_value_valid(registry_data[0]) &&
        sns_ddf_axes_map_is_reg_value_valid(registry_data[1]) &&
        sns_ddf_axes_map_is_reg_value_valid(registry_data[2]);
}


void sns_ddf_axes_map_init(sns_ddf_axes_map_s* axes_map, uint8_t* registry_data)
{
    const int8_t* registry_axes_map = (int8_t*)registry_data;

    if(!sns_ddf_axes_map_is_reg_data_valid(registry_axes_map))
    {
        // Default to no change in orientation.
        axes_map->indx_x = 0;
        axes_map->indx_y = 1;
        axes_map->indx_z = 2;
        axes_map->sign_x = 1;
        axes_map->sign_y = 1;
        axes_map->sign_z = 1;
        return;
    }

    axes_map->sign_x = SIGN_OF_INT8(registry_axes_map[0]);
    axes_map->indx_x = registry_axes_map[0] * axes_map->sign_x - 1;

    axes_map->sign_y = SIGN_OF_INT8(registry_axes_map[1]);
    axes_map->indx_y = registry_axes_map[1] * axes_map->sign_y - 1;

    axes_map->sign_z = SIGN_OF_INT8(registry_axes_map[2]);
    axes_map->indx_z = registry_axes_map[2] * axes_map->sign_z - 1;
}

