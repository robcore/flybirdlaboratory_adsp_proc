/*=============================================================================
  @file sns_smgr_main_uimg.c

  This file implements the portion of SMGR task that executes in microImage

*******************************************************************************
* Copyright (c) 2014 Qualcomm Technologies, Inc.  All Rights Reserved.
* Qualcomm Technologies Proprietary and Confidential.
********************************************************************************/

/* $Header: //components/rel/ssc.adsp/2.6.1/smgr/src/sns_smgr_main_uimg.c#1 $ */
/* $DateTime: 2014/12/01 08:57:58 $ */
/* $Author: pwbldsvc $ */

/*============================================================================
  EDIT HISTORY FOR FILE

  when        who  what, where, why
  ----------  ---  -----------------------------------------------------------
  2014-09-25  pn   Handled SNS_SMGR_DEPOT_COPY_SIG
  2014-09-14  vy   Moved app sleep and wake sig processing to BigImage
  2014-09-08  pn   Moved PM interface functions to PM_IF module
  2014-09-03  vy   Fixed KW error
  2014-08-25  vy   Enabled QDSS logging
  2014-08-18  pn   Removed KW error
  2014-07-31  pn   Replaced smgr_power_state_type_e with sns_pm_pwr_rail_e
  2014-07-14  VY   Fixed compiler warnings
  2014-07-09  vy   Cleanup during bringup
  2014-06-05  vy   Further refactored to support uImage  
  2014-05-24  vy   Removed uimage transition hysteresis timer
  2014-05-13  vy   Refactored for uImage with PM support
  2014-05-07  pn   Added support for MD deregistration
  2014-04-24  pn   Initial version

============================================================================*/

/*----------------------------------------------------------------------------
 * Include Files
 * -------------------------------------------------------------------------*/
#include "sns_ddf_signal.h"
#include "sns_em.h"
#include "sns_pm.h"
#include "sns_profiling.h"
#include "sns_rh_util.h"
#include "sns_smgr.h"
#include "sns_smgr_hw.h"
#include "sns_smgr_main.h"
#include "sns_smgr_pm_if.h"
#include "sns_smgr_util.h"

/*----------------------------------------------------------------------------
 * Preprocessor Definitions and Constants
 * -------------------------------------------------------------------------*/
#define __SNS_MODULE__ SNS_SMGR_UIMG

/*----------------------------------------------------------------------------
 * Type Declarations
 * -------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
 *  Global Variables
 * -------------------------------------------------------------------------*/
sns_smgr_s              sns_smgr;
OS_STK                  sns_smgr_task_stack[SNS_MODULE_STK_SIZE_DSPS_SMGR];
sns_profiling_latency_s sns_latency;

/*----------------------------------------------------------------------------
 * Function prototypes
 * -------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
 * Function Declarations and Documentation
 * -------------------------------------------------------------------------*/
/*===========================================================================

  FUNCTION:   sns_smgr_dd_service

===========================================================================*/
/*!
  @brief This function Enter the device driver framework for each queued DD
         timer expiration or IRQ handling

  @detail

  @param[i]  none
  @return   none
 */
/*=========================================================================*/
SMGR_STATIC void sns_smgr_dd_service(void)
{
  sns_profiling_log_qdss(SNS_SMGR_FUNC_ENTER, 1, SNS_SMGR_DD_SERVICE_SIG);
  if(sns_hw_powerrail_status() != SNS_PWR_RAIL_OFF)
  {
    sns_hw_set_qup_clk(true);

    sns_ddf_signal_dispatch();
#ifndef SNS_QDSP_SIM  
    while ( sns_smgr.timer_que_out != sns_smgr.timer_que_in )
    {
      /* turn on qup clock now and turn off after sns_ddf_smgr_notify_data */
      sns_ddf_timer_dispatch((sns_ddf_timer_s)sns_smgr.timer_que[sns_smgr.timer_que_out]);
      sns_smgr.timer_que_out++;
      if ( sns_smgr.timer_que_out >= SNS_SMGR_TIMER_QUEUE_SIZE )
      {
         sns_smgr.timer_que_out = 0;
      }
    }
#else
    {
      uint8_t err = 0; 
      sns_os_sigs_post(sns_dri_sim.sns_dri_sig_grp, SNS_DRI_SIMULATE, OS_FLAG_SET, &err);
    }
#endif //SNS_QDSP_SIM  
    
    sns_hw_set_qup_clk(false);
  }
  else
  {
    SNS_SMGR_PRINTF0(ERROR, "Spurious signal detected by SMGR");
  }
}


/*===========================================================================

  FUNCTION:   sns_smgr_timer_cb

===========================================================================*/
/*!
  @brief timer call back. Entered on interrupt

  @detail

  @param[i]  cb_arg  callback argument
  @return   none
 */
/*=========================================================================*/
void sns_smgr_timer_cb(void *cb_arg)
{
  sns_profiling_log_qdss(SNS_SMGR_TIMER_CB, 1, SNS_SMGR_SENSOR_READ_SIG);
  if( sns_latency.ltcy_measure_enabled )
  {
    //latency measurement under polling mode
    sns_latency.polling_cb_ts = sns_em_get_timestamp();
  }
  sns_smgr_signal_me(SNS_SMGR_SENSOR_READ_SIG);
}


/*===========================================================================

  FUNCTION:   sns_smgr_sensor_ev_timer_cb

===========================================================================*/
/*!
  @brief Sensor event timer call back

  @param[i]  cb_arg - unused callback argument
  @return   none
 */
/*=========================================================================*/
void sns_smgr_sensor_ev_timer_cb(void *cb_arg)
{
  sns_smgr_signal_me(SNS_SMGR_SENSOR_STATE_SIG);
}


/*===========================================================================

  FUNCTION:   sns_smgr_task_main

===========================================================================*/
/*!
  @brief SMGRT task

  @detail

  @param[i]  none
  @return   none
 */
/*=========================================================================*/
void sns_smgr_task_main(void)
{
  uint8_t   err;
  OS_FLAGS  sig_flags;
  /* Union of uImage and BigImage signals */
  OS_FLAGS  OS_FLAGS_sig_type =
     SNS_SMGR_SENSOR_READ_SIG     |
     SNS_SMGR_DD_SERVICE_SIG      |
     SNS_SMGR_SENSOR_STATE_SIG    |
     SNS_SMGR_ENABLE_MD_SIG       |
     SNS_SMGR_DISABLE_MD_SIG      |
     SNS_SMGR_PWR_RAIL_SIG        |
     SNS_SMGR_VOTE_MIPS_BW        |
     SNS_SMGR_DEPOT_COPY_SIG      |
     SNS_SMGR_APP_WAKE_SIG        |
     SNS_SMGR_APP_SLEEP_SIG       |
     SNS_SMGR_QMI_MSG_SIG; 

  /* Only BigImage signals */
  OS_FLAGS  OS_FLAGS_sig_type_big =
     SNS_SMGR_SENSOR_STATE_SIG  |
     SNS_SMGR_ENABLE_MD_SIG     | 
     SNS_SMGR_DISABLE_MD_SIG    |
     SNS_SMGR_PWR_RAIL_SIG      |
     SNS_SMGR_VOTE_MIPS_BW      |
     SNS_SMGR_DEPOT_COPY_SIG    |
     SNS_SMGR_APP_WAKE_SIG      |
     SNS_SMGR_APP_SLEEP_SIG     |
     SNS_SMGR_QMI_MSG_SIG;

  (void)sns_os_sigs_add(sns_smgr.sig_grp, OS_FLAGS_sig_type);
  
  sns_smgr_vote_image_mode(SNS_IMG_MODE_NOCLIENT);

  /* ========================= MAIN TASK LOOP ===============================*/
  while ( 1 )
  {
    //sns_profiling_log_timestamp((uint64_t) SNS_SMGR_LATENCY_PROFILE_END);
    sns_profiling_log_qdss(SNS_SMGR_EXIT, 0);

    sig_flags = sns_os_sigs_pend(sns_smgr.sig_grp, OS_FLAGS_sig_type,
                                 OS_FLAG_WAIT_SET_ANY + OS_FLAG_CONSUME, 0, &err);

    sns_profiling_log_qdss(SNS_SMGR_ENTER, 1, sig_flags);
    //sns_profiling_log_timestamp((uint64_t) SNS_SMGR_LATENCY_PROFILE_START);

    if ( sig_flags & SNS_SMGR_DD_SERVICE_SIG )
    {
      sns_smgr_dd_service();
    }
#ifndef SNS_PLAYBACK_SKIP_SMGR
    if ( sig_flags & SNS_SMGR_SENSOR_READ_SIG )
    {
      sns_smgr_sampling_cycle();
    }
#endif
    if ( sig_flags & OS_FLAGS_sig_type_big )
    {
      sns_smgr_enter_bigimage();
      sns_smgr_handle_bigimage_signals(sig_flags);
      sns_smgr_exit_bigimage();
    }
    if ( sig_flags & (~OS_FLAGS_sig_type))
    {
      SNS_SMGR_PRINTF1(ERROR, "unknown signal(s) 0x%x", 
                       sig_flags & ~OS_FLAGS_sig_type);
    }
    sig_flags = 0;
  } /* while */
}


/*===========================================================================

  FUNCTION:   sns_smgr_app_state_change

===========================================================================*/
/*!
  @brief Called by Power module when AP state changes

  @detail
  @param[i] app_is_asleep - TRUE if AP entered sleep state, FALSE wake state
  @return   none
 */
/*=========================================================================*/
void sns_smgr_app_state_change(bool app_is_asleep)
{
  uint8_t  err;
  uint32_t set_bit = app_is_asleep ? SNS_SMGR_APP_SLEEP_SIG : SNS_SMGR_APP_WAKE_SIG;
  uint32_t clr_bit = app_is_asleep ? SNS_SMGR_APP_WAKE_SIG  : SNS_SMGR_APP_SLEEP_SIG;
  sns_os_sigs_post ( sns_smgr.sig_grp, clr_bit, OS_FLAG_CLR, &err );
  sns_os_sigs_post ( sns_smgr.sig_grp, set_bit, OS_FLAG_SET, &err );
}


/*===========================================================================

  FUNCTION:   sns_smgr_signal_me

===========================================================================*/
/*!
  @brief Posts a signal to SMGR task

  @detail
  @param[i] sig - the signal to post
  @return   none
 */
/*=========================================================================*/
void sns_smgr_signal_me(uint32_t sig)
{
  uint8_t os_err;
  sns_os_sigs_post(sns_smgr.sig_grp, sig, OS_FLAG_SET, &os_err);
}


/*===========================================================================

  FUNCTION:   sns_smgr_find_sensor

===========================================================================*/
/*!
  @brief Finds the associated sensor structure given a sensor ID.

  @detail
  @param[i] sensor_id - the sensor ID passed in via Sensor1 API
  @return
   sensor structure, or NULL if not found
 */
/*=========================================================================*/
sns_smgr_sensor_s* sns_smgr_find_sensor(smgr_sensor_id_e sensor_id)
{
  sns_smgr_sensor_s* sensor_ptr = NULL;
  uint8_t i;
  for ( i=0; i<ARR_SIZE(sns_smgr.sensor) && sensor_ptr==NULL; i++ )
  {
    if ( SMGR_SENSOR_ID(&sns_smgr.sensor[i]) == sensor_id )
    {
      sensor_ptr = &sns_smgr.sensor[i];
    }
  }
  return sensor_ptr;
}

/*===========================================================================

  FUNCTION:   sns_smgr_init

===========================================================================*/
/*!
  @brief This function starts smgr task

  @detail

  @param   none
  @return  return SNS_SUCCESS always
 */
/*=========================================================================*/
sns_err_code_e sns_smgr_init(void)
{
  sns_os_task_create_ext(sns_smgr_task, NULL,
                         (OS_STK *)&sns_smgr_task_stack[SNS_MODULE_STK_SIZE_DSPS_SMGR-1],
                         SNS_MODULE_PRI_DSPS_SMGR,
                         SNS_MODULE_PRI_DSPS_SMGR,
                         (OS_STK *)&sns_smgr_task_stack[0],
                         SNS_MODULE_STK_SIZE_DSPS_SMGR,
                         (void *)0,
                         OS_TASK_OPT_STK_CHK | OS_TASK_OPT_STK_CLR |
                         OS_TASK_OPT_ISLAND,
                         (uint8_t *)"SNS_SMGR");
  return SNS_SUCCESS;
}
