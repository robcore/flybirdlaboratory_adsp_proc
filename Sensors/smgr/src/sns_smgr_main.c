/*=============================================================================
  @file sns_smgr_main.c

  This file implements SMGR task loop

*******************************************************************************
* Copyright (c) 2014 Qualcomm Technologies, Inc.  All Rights Reserved.
* Qualcomm Technologies Proprietary and Confidential.
********************************************************************************/

/* $Header: //components/rel/ssc.adsp/2.6.1/smgr/src/sns_smgr_main.c#1 $ */
/* $DateTime: 2014/12/01 08:57:58 $ */
/* $Author: pwbldsvc $ */

/*============================================================================
  EDIT HISTORY FOR FILE

  when        who  what, where, why
  ----------  ---  -----------------------------------------------------------
  2014-11-19  pn   Sets event_done_tick when processing MD requests
  2014-09-25  pn   Added support for copying uImage depot to bigImage depot
  2014-09-14  vy   Moved app sleep and wake sig processing to BigImage
  2014-09-08  pn   Moved PM interface functions to PM_IF module
  2014-09-03  jhh  Added client name on pm client
  2014-07-31  pn   Enabled power control; removed obsolete code
  2014-07-22  VY   Fixed compiler warnings
  2014-07-09  vy   Clean up during bringup
  2014-06-16  pn   sns_smgr_hw_init() returns when last registry response is received
  2014-06-11  ps   add Power rail voting, fix hang at sns_smgr_hw_init
  2014-06-11  vy   Further refactored to support uImage  
  2014-05-24  vy   Introduced utimers
  2014-05-09  vy   Refactored for uImage and PM support
  2014-04-24  pn   Initial version

============================================================================*/

/*----------------------------------------------------------------------------
 * Include Files
 * -------------------------------------------------------------------------*/
#include <stringl.h>

#include "sensor1.h"
#include "sns_em.h"
#include "sns_osa.h"
#include "sns_memmgr.h"
#include "sns_init.h"
#include "sns_profiling.h"
#include "sns_rh_util.h"
#include "sns_smgr.h"
#include "sns_smgr_hw.h"
#include "sns_smgr_main.h"
#include "sns_smgr_mr.h"
#include "sns_smgr_pm_if.h"
#include "sns_smgr_reg.h"
#include "sns_smgr_util.h"

/*----------------------------------------------------------------------------
 * Preprocessor Definitions and Constants
 * -------------------------------------------------------------------------*/
#define __SNS_MODULE__ SNS_SMGR

/*----------------------------------------------------------------------------
 * Type Declarations
 * -------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
 *  Global Variables
 * -------------------------------------------------------------------------*/
extern sns_smgr_s              sns_smgr;

#ifdef SNS_QDSP_SIM
extern sns_dri_sim_s           sns_dri_sim;
#endif

/*----------------------------------------------------------------------------
 * Function prototypes
 * -------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------
 * Function Declarations and Documentation
 * -------------------------------------------------------------------------*/

/*===========================================================================

  FUNCTION:   sns_smgr_process_msg

===========================================================================*/
/*!
  @brief This function processes the given incoming message for SMGR
  @param   none
  @return  none
 */
/*=========================================================================*/
SMGR_STATIC void sns_smgr_process_msg(void)
{
  sns_smgr_mr_msg_s* msg_ptr;

  sns_profiling_log_qdss(SNS_SMGR_FUNC_ENTER, 1, SNS_SMGR_QMI_MSG_SIG);
  (void)sns_smgr_get_tick64();

  while ( NULL != (msg_ptr = sns_smgr_mr_get_msg()) )
  {
    sns_smgr_mr_header_s* hdr_ptr = &msg_ptr->header;
    SNS_SMGR_PRINTF3(
      MED, "process_msg - svc=%d msg=0x%x now=%u",
      hdr_ptr->svc_num, hdr_ptr->msg_id, (unsigned)sns_smgr.last_tick.u.low_tick);

    if ( SNS_REG2_SVC_ID_V01 == hdr_ptr->svc_num )
    {
      sns_smgr_process_reg_resp_msg(msg_ptr);
    }
    else
    {
      SNS_SMGR_PRINTF0(ERROR, "process_msg - unexpected message");
    }
  }
}


/*===========================================================================

  FUNCTION:   sns_smgr_copy_uimg_depots

===========================================================================*/
/*!
  @brief  Copies contents of uImage depots to bigImage depots if necessary
  @param  none
  @return none
 */
/*=========================================================================*/
SMGR_STATIC void sns_smgr_copy_uimg_depots(void)
{
  uint8_t s, d;

  for ( s=0; s<ARR_SIZE(sns_smgr.sensor); s++ )
  {
    sns_smgr_sensor_s* sensor_ptr = &sns_smgr.sensor[s];
    for ( d=0; d<ARR_SIZE(sensor_ptr->ddf_sensor_ptr); d++ )
    {
      sns_smgr_ddf_sensor_s* ddf_sensor_ptr = sensor_ptr->ddf_sensor_ptr[d];
      if ( ddf_sensor_ptr != NULL && ddf_sensor_ptr->uimg_depot_ptr != NULL &&
           ddf_sensor_ptr->uimg_depot_full_alert )
      {
        sns_smgr_copy_uimg_depot(ddf_sensor_ptr);
      }
    }
  }
}

/*===========================================================================

  FUNCTION:   sns_smgr_ltcy_measure_check(void)

===========================================================================*/
/*!
  @brief Check whether latency measurement is enabled or not.

  @detial
  @param[i] none
  @return  none
 */
/*=========================================================================*/
SMGR_STATIC void sns_smgr_ltcy_measure_check(void)
{
  uint8_t i;

  sns_latency.ltcy_measure_enabled = false;
  for ( i=0; i<ARR_SIZE(sns_smgr.sensor); i++ )
  {
    if( sns_smgr.sensor[i].const_ptr->flags == SNS_REG_SSI_FLAG_LTCY_ENABLE )
    {
      sns_latency.ltcy_measure_enabled = true;
      break;
    }
  }
}


/*===========================================================================

  FUNCTION:   sns_smgr_handle_app_wake_sig

===========================================================================*/
/*!
  @brief Handles APP_WAKE signal

  @detail
  @param  none
  @return none
 */
/*=========================================================================*/
SMGR_STATIC void sns_smgr_handle_app_wake_sig(void)
{
  sns_pm_pwr_rail_e curr_powerrail = sns_hw_powerrail_status();

  SNS_SMGR_PRINTF3(
    HIGH, "WAKE_SIG curr state(%d) powerrail(%d) change count(%u)",
    sns_smgr.app_is_awake, curr_powerrail, (unsigned)sns_smgr.app_state_toggle_count);

  sns_smgr.app_is_awake = true;
  sns_smgr.app_state_toggle_count++;

  if ( curr_powerrail == SNS_PWR_RAIL_OFF )
  {
    uint8_t i;
    for ( i=0; i<ARR_SIZE(sns_smgr.sensor); i++ )
    {
      if ( sns_smgr.sensor[i].sensor_state == SENSOR_STATE_OFF )
      {
        sns_smgr.sensor[i].event_done_tick = sns_em_get_timestamp();
        sns_smgr_schedule_sensor_event(1);
        break; /* one is enough */
      }
    }
  }
  sns_smgr_vote_mips_bw_reqd();
}


/*===========================================================================

  FUNCTION:   sns_smgr_handle_app_sleep_sig

===========================================================================*/
/*!
  @brief Handles APP_SLEEP signal

  @detail
  @param  none
  @return none
 */
/*=========================================================================*/
SMGR_STATIC void sns_smgr_handle_app_sleep_sig(void)
{
  SNS_SMGR_PRINTF2(
    HIGH, "SLEEP_SIG curr state(%d), change count(%d)",
    sns_smgr.app_is_awake, (unsigned)sns_smgr.app_state_toggle_count);
  sns_smgr.app_is_awake = false;
  sns_smgr.app_state_toggle_count++;
  sns_smgr_vote_mips_bw_reqd();
}


/*===========================================================================

  FUNCTION:   sns_smgr_hw_init

===========================================================================*/
/*!
  @brief Waits for registry responses that carry HW config info and applies
         the HW config before returning

  @param[i] none
  @return  none
 */
/*=========================================================================*/
#ifndef ADSP_STANDALONE
SMGR_STATIC void sns_smgr_hw_init(void)
{
  OS_FLAGS sig_mask = SNS_SMGR_QMI_MSG_SIG;

  sns_os_sigs_add(sns_smgr.sig_grp, sig_mask);
  sns_hw_bd_config();
  sns_smgr_dd_init();

  while ( sns_smgr.all_init_state != SENSOR_ALL_INIT_DONE )
  {
    uint8_t  err;
    OS_FLAGS sig_flags;
    sig_flags = sns_os_sigs_pend(sns_smgr.sig_grp, sig_mask,
                                 OS_FLAG_WAIT_SET_ANY + OS_FLAG_CONSUME, 0, &err);
    SNS_SMGR_PRINTF1(LOW, "hw_init - sig_flags=0x%x", sig_flags);

    if ( sig_flags & SNS_SMGR_QMI_MSG_SIG )
    {
      sns_smgr_process_msg();
    }
    sns_smgr_dd_init();
  }

  //check the registry flags if latency measurement enabled
  sns_smgr_ltcy_measure_check();

  // Let RH task know to proceed
  sns_rh_signal_me(SNS_RH_SMGR_INIT_DONE_SIG);
}
#else
void sns_smgr_hw_init(void)
{
  sns_hw_bd_config();
  sns_smgr_dd_init();
  sns_smgr_ltcy_measure_check();
  sns_rh_signal_me(SNS_RH_SMGR_INIT_DONE_SIG);
}
#endif

/*===========================================================================

  FUNCTION:   smgr_init

===========================================================================*/
/*!
  @brief initialize some flags and variables in sns_smgr

  @detail

  @param[i] none
  @return   none
 */
/*=========================================================================*/
SMGR_STATIC void smgr_init(void)
{
  uint8_t err;

  /* --------------------------------------------------------------------- */
  SNS_OS_MEMZERO(&sns_smgr, sizeof(sns_smgr_s));
  sns_smgr.app_is_awake = true;
  sns_q_init(&sns_smgr.sched_que);

  /* Init signal events */
  sns_smgr.sig_grp = sns_os_sigs_create ( 0, &err);
  SNS_ASSERT(sns_smgr.sig_grp != NULL);

  sns_em_create_utimer_obj(&sns_smgr_timer_cb, &sns_smgr.sig_grp, 
                          SNS_EM_TIMER_TYPE_ONESHOT, &sns_smgr.tmr_obj);

  sns_em_create_utimer_obj(&sns_smgr_sensor_ev_timer_cb, &sns_smgr.sig_grp, 
                          SNS_EM_TIMER_TYPE_ONESHOT, &sns_smgr.sensor_ev_tmr_obj);
  
  /* Initialize interface with PM */
  sns_smgr_pm_stats_init();
}

/*===========================================================================

  FUNCTION:   sns_smgr_task

===========================================================================*/
/*!
  @brief SMGRT task

  @detail This is created by sns_smgr_init, which is called during sns_init

  @param[i]  p_arg
  @return   none
 */
/*=========================================================================*/
void sns_smgr_task(void* p_arg)
{
  
  /* --------------------------------------------------------------------- */
  /* Start initializing SMGR modules */
  smgr_init();
  sns_smgr_sensor_init();

  /* Start RH thread */
  sns_rh_task_init();

  /* Message Router init only returns after successfully connecting to services */
  sns_smgr_mr_init(sns_smgr.sig_grp);

  /* HW init only returns after all device drivers are initialized */
  sns_smgr_hw_init();

  /* Inform init code that SMGR init is done */
  sns_init_done();

  //SMGR_DELAY_US(1000000);
  
  /* Run the main task loop, no return */
  sns_smgr_task_main();
}


/*===========================================================================

  FUNCTION:   sns_smgr_handle_bigimage_signals

===========================================================================*/
/*!
  @brief Handle big image events and messages

  @detail 

  @param[i]  signal
  @return   none
 */
/*=========================================================================*/
void sns_smgr_handle_bigimage_signals(OS_FLAGS sig_flags)
{
  if ( sig_flags & SNS_SMGR_SENSOR_STATE_SIG )
  {
    smgr_process_sensor_event();
  }
  if ( sig_flags & (SNS_SMGR_ENABLE_MD_SIG | SNS_SMGR_DISABLE_MD_SIG)  )
  {
    sns_smgr_sensor_s* sensor_ptr = sns_smgr_find_sensor(SNS_SMGR_ID_ACCEL_V01);
    if ( sensor_ptr != NULL )
    {
      if ( sig_flags & SNS_SMGR_ENABLE_MD_SIG )
      {
        SMGR_BIT_SET(sensor_ptr->flags, SMGR_SENSOR_FLAGS_ENABLE_MD_B);
      }
      else
      {
        SMGR_BIT_SET(sensor_ptr->flags, SMGR_SENSOR_FLAGS_DISABLE_MD_B);
      }
      sensor_ptr->event_done_tick = sns_em_get_timestamp();
      smgr_process_sensor_event();
    }
  }
  if ( sig_flags & SNS_SMGR_PWR_RAIL_SIG )
  {
    sns_hw_send_powerrail_msg_tmr_cb_proc();
  }
  if (sig_flags & SNS_SMGR_QMI_MSG_SIG)
  {
    sns_smgr_process_msg();
  }
  if ( sig_flags & SNS_SMGR_DEPOT_COPY_SIG )
  {
    sns_smgr_copy_uimg_depots();
  }
  if (sig_flags & SNS_SMGR_VOTE_MIPS_BW)
  {
    sns_smgr_vote_mips_bw_reqd();
  }
  if ( sig_flags & SNS_SMGR_APP_WAKE_SIG )
  {
    sns_smgr_handle_app_wake_sig();
  }
  if ( sig_flags & SNS_SMGR_APP_SLEEP_SIG )
  {
    sns_smgr_handle_app_sleep_sig();
  }
}



