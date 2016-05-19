/*==============================================================================
  FILE:         apcr_lpr.c

  OVERVIEW:     This file provides uSleep APCR LPR functions

  DEPENDENCIES: Object file generated from source is marked as island section
  
                Copyright (c) 2014 Qualcomm Technologies, Inc. (QTI).
                All Rights Reserved.
                Qualcomm Technologies Confidential and Proprietary
================================================================================
$Header: //components/rel/core.adsp/2.6.1/power/sleep2.0/src/uSleep/island/lpr/apcr_lpr.c#1 $
$DateTime: 2014/10/16 12:45:40 $
==============================================================================*/
#include "DALStdDef.h"
#include "CoreVerify.h"
#include "HALhwio.h"
#include "HALsleep_hwio.h"
#include "uSleep.h"
#include "uSleepi.h"
#include "uSleep_lpr.h"
#include "uSleep_log.h"
#include "uTimetick.h"
#include "utimer.h"
#include "qurt.h"
#include "uSleep_util.h"

/*==============================================================================
                       EXTERNAL FUNCTION DEFINITIONS
 =============================================================================*/
/* 
 * uSleepLPR_apcrEnter 
 */
void uSleepLPR_apcrEnter(uint64 wakeupTime)
{
  /* Set the local wakeup time */
  uTimetick_SetWakeUpTimerInterrupt(wakeupTime);
  uTimetick_EnableWakeUpTimerInterrupt(TRUE);

  uSleepLog_printf(USLEEP_LOG_LEVEL_PROFILING, (1*2),
                   " Set QTMR (match: 0x%llx)",
                   MICRO_ULOG64_DATA(wakeupTime) );

  /* TODO: possibly ramp AHB bus */

  /* In non-RPM assisted modes, assume the programmed wakeup time is the actual
   * wakeup time */
  uSleep_setLastSleepWakeupInternal(wakeupTime);

  CORE_VERIFY(uTimetick_Get() < wakeupTime);

  /* Enter all wait */
  qurt_power_apcr_enter();

  return;
}

/* 
 * uSleepLPR_apcrCachedEnter 
 */
void uSleepLPR_apcrCachedEnter(uint64 wakeupTime)
{
  /* Set override bit so APCR is entered immediately at all-wait */
  qurt_power_override_wait_for_idle(1);

  /* In APCR cached mode, we do not need to run the exit function until
   * we change to an un-cached mode so disable the PMI interrupt. */
  HWIO_OUT(LPASS_QDSP6SS_SPMCTL_EN_STATERET,
           HWIO_FVAL(LPASS_QDSP6SS_SPMCTL_EN_STATERET, WAKE_IRQ,  0)   |
           HWIO_FVAL(LPASS_QDSP6SS_SPMCTL_EN_STATERET, RESTORE,   1)   |
           HWIO_FVAL(LPASS_QDSP6SS_SPMCTL_EN_STATERET, SAVE,      1)); 
  return;
}

/* 
 * uSleepLPR_apcrExit 
 */
void uSleepLPR_apcrExit(void)
{
  /* TODO: possibly ramp AHB bus */

  /* Disable the wakeup timer */
  uTimetick_EnableWakeUpTimerInterrupt(FALSE);

  return;
}

/* 
 * uSleepLPR_apcrCachedExit 
 */
void uSleepLPR_apcrCachedExit(void)
{
  qurt_power_override_wait_for_idle(0);

  /* Enable PMI interrupt so the exit functions can be called. */
  HWIO_OUT(LPASS_QDSP6SS_SPMCTL_EN_STATERET,
           HWIO_FVAL(LPASS_QDSP6SS_SPMCTL_EN_STATERET, WAKE_IRQ,  1)   |
           HWIO_FVAL(LPASS_QDSP6SS_SPMCTL_EN_STATERET, RESTORE,   1)   |
           HWIO_FVAL(LPASS_QDSP6SS_SPMCTL_EN_STATERET, SAVE,      1)); 
  return;
}

