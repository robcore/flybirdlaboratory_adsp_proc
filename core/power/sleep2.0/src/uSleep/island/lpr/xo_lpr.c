/*==============================================================================
  FILE:         xo_lpr.c

  OVERVIEW:     This file provides uSleep XO shutdown LPR functions

  DEPENDENCIES: Object file generated from source is marked as island section
  
                Copyright (c) 2014 Qualcomm Technologies, Inc. (QTI).
                All Rights Reserved.
                Qualcomm Technologies Confidential and Proprietary
================================================================================
$Header: //components/rel/core.adsp/2.6.1/power/sleep2.0/src/uSleep/island/lpr/xo_lpr.c#2 $
$DateTime: 2014/11/06 11:48:29 $
==============================================================================*/
#include "DALStdDef.h"
#include "uSleep.h"
#include "uSleepi.h"
#include "sleep_statsi.h"
#include "spm.h"
#include "umpm.h"
#include "uSleep_lpr.h"
#include "uSleep_log.h"
#include "uTimetick.h"
#include "utimer.h"
#include "qurt.h"
#include "uSleep_util.h"

/*==============================================================================
                             INTERNAL VARIABLES
 =============================================================================*/
static uint64 g_rpmWakeupTime;

/*==============================================================================
                       EXTERNAL FUNCTION DEFINITIONS
 =============================================================================*/
/* 
 * uSleepLPR_cxoEnter
 */
void uSleepLPR_cxoEnter(uint64 wakeupTime)
{
  /* Enable RPM handshake */
  spm_set_rpm_bypass(0, SPM_RPM_PERFORM_HANDSHAKE);
  
  /* TODO: possibly ramp AHB bus */
    
  uSleepLog_printf(USLEEP_LOG_LEVEL_PROFILING, (1*2),
                   " Set RPM wakeup (match: 0x%llx)",
                   MICRO_ULOG64_DATA(wakeupTime) );

  /* Save the last wakeup time */
  g_rpmWakeupTime = wakeupTime;

  /* Tell RPM the wakeup time */
  umpm_setWakeupTimetick(wakeupTime);

  CORE_VERIFY(uTimetick_Get() < wakeupTime);
  
  /* Enter all wait */
  qurt_power_apcr_enter();
  return;
}

/* 
 * uSleepLPR_cxoExit 
 */
void uSleepLPR_cxoExit(void)
{
  int64            wakeupErr;
  RPM_master_stats *rpmStats = sleepStats_getRpmDataPtr();

  CORE_VERIFY_PTR(rpmStats);

  /* TODO: possibly ramp AHB bus */

  /* Set the time of the wakeup using the bringup ack from SPM as reported 
   * via RPM */
  uSleep_setLastSleepWakeupInternal(rpmStats->bringup_ack);

  if(g_rpmWakeupTime > rpmStats->bringup_ack)
  {
    /* Early wakeup */
    wakeupErr = -((int64)(g_rpmWakeupTime - rpmStats->bringup_ack));
  }
  else
  {
    /* Late wakeup */
    wakeupErr = (int64)(rpmStats->bringup_ack - g_rpmWakeupTime);
  }

  /* Disable RPM handshake */
  spm_set_rpm_bypass(0, SPM_RPM_BYPASS_HANDSHAKE);
  
  /* Retrigger interrupts */  
  umpm_triggerInterrupts();

  uSleepLog_QDSSPrintf(USLEEP_LOG_LEVEL_PROFILING, 
                       USLEEP_RPM_WAKE_REASON_NUM_ARGS,
                       USLEEP_RPM_WAKE_REASON_STR, 
                       USLEEP_RPM_WAKE_REASON,
                       0 == rpmStats->wakeup_reason ? "Rude" : "Timer",
                       MICRO_ULOG64_DATA(rpmStats->shutdown_req),
                       MICRO_ULOG64_DATA(rpmStats->bringup_ack),
                       rpmStats->last_sleep_transition_duration,
                       rpmStats->last_wake_transition_duration,
                       (int32)wakeupErr);
  return;
}

