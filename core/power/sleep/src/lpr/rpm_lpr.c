/*==============================================================================
  FILE:         rpm_lpr.c

  OVERVIEW:     This file provides the LPR definition for the RPM  
                low-power modes.

  DEPENDENCIES: None

                Copyright (c) 2011-2013 QUALCOMM Technologies Incorporated.
                All Rights Reserved.
                Qualcomm Confidential and Proprietary
================================================================================
$Header: //components/rel/core.adsp/2.6.1/power/sleep/src/lpr/rpm_lpr.c#1 $
$DateTime: 2014/10/16 12:45:40 $
==============================================================================*/
#include <stdbool.h>
#include "HALcomdef.h"
#include "sleepi.h"
#include "sleep_lpr.h"
#include "rpm.h"
#include "rpmclient.h"
#include "kvp.h"
#include "CoreVerify.h"
#include "smd.h"
#include "vmpm_utils.h"
#include "spm.h"
#include "sleep_log.h"
#include "sleep_statsi.h"
#include "sleep_target.h"

static uint32 nas_result;
static uint32 ss_result;

void rpm_sync_init( void )
{
  return;
}

void rpm_sync_enter( uint64 wakeup_tick )
{
  sleep_target_set_rpm_assisted_mode(TRUE);
  spm_set_rpm_bypass(0, SPM_RPM_PERFORM_HANDSHAKE);
  vmpm_SetWakeupTimetick(wakeup_tick);
  ss_result = rpm_force_sync(RPM_SLEEP_SET);

  sleep_log_printf_qdss( SLEEP_LOG_LEVEL_INFO, SLEEP_SET_SEND_NUM_ARGS,
                         SLEEP_SET_SEND_STR, SLEEP_SET_SEND,
                         ULOG64_DATA(wakeup_tick) );

  nas_result = rpm_force_sync(RPM_NEXT_ACTIVE_SET);

  if(ss_result || nas_result)
  {
    CORE_VERIFY(smd_disable_intr(SMEM_RPM) == SMD_STATUS_SUCCESS);
  }

  return;
}

void rpm_sync_exit( void )
{
  RPM_master_stats *rpmStats = sleepStats_getRpmDataPtr();

  CORE_VERIFY_PTR(rpmStats);

    /* Ensure churn_queue uses nas_result if valid, else ss_result */
  rpm_churn_queue(nas_result?nas_result:ss_result);

  if(ss_result || nas_result)
  {
    CORE_VERIFY(smd_enable_intr(SMEM_RPM) == SMD_STATUS_SUCCESS);
  }

    /* Change SPM to bypass RPM handshake */
  spm_set_rpm_bypass(0, SPM_RPM_BYPASS_HANDSHAKE);

  /* Set wakeup reason as given from RPM */
  sleepStats_putMiscData(inpdw(&rpmStats->wakeup_reason), 
                         SLEEP_STATS_MISC_WAKEUP_REASON_TYPE);

  /* In RPM assisted modes, the wakeup time will come from RPM. Overwrite the 
   * previously put standalone PC time */
  sleepStats_putLprTimeData(inp64(&rpmStats->bringup_ack), 
                            SLEEP_STATS_TIME_WAKEUP_TYPE);
  
  sleep_target_set_rpm_assisted_mode(FALSE);

  return;
}
