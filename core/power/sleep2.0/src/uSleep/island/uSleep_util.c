/*==============================================================================
  FILE:         uSleep_util.c

  OVERVIEW:     This file provides uSleep helper functions that are located in
                island memory space

  DEPENDENCIES: Object file generated from source is marked as island section
  
                Copyright (c) 2014 Qualcomm Technologies, Inc. (QTI).
                All Rights Reserved.
                Qualcomm Technologies Confidential and Proprietary
================================================================================
$Header: //components/rel/core.adsp/2.6.1/power/sleep2.0/src/uSleep/island/uSleep_util.c#2 $
$DateTime: 2014/11/19 11:30:59 $
==============================================================================*/
#include "DALStdDef.h"
#include "CoreVerify.h"
#include "qurt.h"
#include "sleepi.h"
#include "uSleepi.h"
#include "uSleep_log.h"
#include "uSleep_lpr.h"
#include "uSleep_timer.h"
#include "uimage_rpm.h"
#include "uSleep_util.h"
#include "rpm.h"
#include "rpmclient.h"
#include "island_mgr.h"

/*==============================================================================
                             EXTERNAL VARIABLES
 =============================================================================*/
/* Main uSleep data structure that stores state & other internal data */
uSleep_global_data g_uSleepData = {0};

/*==============================================================================
                             INTERNAL VARIABLES
 =============================================================================*/
/* Variable to control DDR on/off when entering island mode */
static volatile boolean g_uSleepKeepDDROn = FALSE;

/*==============================================================================
                       EXTERNAL FUNCTION DEFINITIONS
 =============================================================================*/
/*
 * uSleep_islandControl
 */
void uSleep_islandControl(uSleep_RPM_set_mode mode)
{
  static uint32           BIMCFreq = 0;
  static uint32           SNOCFreq = 0;
  uImage_rpm_wait_mode_t  rpmMode;
  char                    *msg;

  switch(mode)
  {
    case UIMAGE_ENTER:
      msg = "Off";
    break;

    case UIMAGE_EXIT:
      msg = "On";
    break;

    default:
      msg = "Fast On";
  }

  uSleepLog_QDSSPrintf(USLEEP_LOG_LEVEL_TRANSITION, 
                       USLEEP_DDR_TRANS_START_NUM_ARGS,
                       USLEEP_DDR_TRANS_START_STR, 
                       USLEEP_DDR_TRANS_START,
                       msg);

  if(UIMAGE_ENTER == mode)
  {
    /* Perform the setup required to enter island mode */
    uSleep_setupIslandEntry(&BIMCFreq, &SNOCFreq);

    /* Ensure that we have a valid current frequency */
    CORE_VERIFY((0 != BIMCFreq) && (0 != SNOCFreq));

    /* Enter island mode */
    CORE_VERIFY(ISLAND_MGR_EOK == island_mgr_island_enter());

    if(FALSE == g_uSleepKeepDDROn)
    {
      /* Turn DDR off and do not wait since island mode can operate even while DDR
       * is still on */
      uImage_rpm_set_clk_values(1, 0, UIMAGE_RPM_NO_WAIT_MODE);
    }
    else
    {
      /* If we are not actually turning off DDR, then we need to notify 
       * ourselves that the transition is complete. */ 
      uSleep_notifyDDRTransitionComplete(FALSE);
    }
  }
  else
  {
    if(UIMAGE_EXIT == mode)
    {
      /* Set normal exit stage 1 state */ 
      uSleep_setStateInternal(uSLEEP_INTERNAL_STATE_REQ_TRANS_EXIT);
      
      /* Do not wait for RPM to turn on DDR which allows us to sleep during
       * this time.
       * 
       * TODO: update this to NO WAIT when RPM optimizations are added. For 
       * now we must wait */
      rpmMode = UIMAGE_RPM_BUSY_WAIT_MODE;
    }
    else
    {
      /* Set fast exit state */
      uSleep_setStateInternal(uSLEEP_INTERNAL_STATE_REQ_FAST_EXIT);      

      /* In fast exit mode, we must always wait for DDR on as we do not want
       * to introduce any additional possibilities of errors in the code. */
      rpmMode = UIMAGE_RPM_BUSY_WAIT_MODE; 
    }

    if(FALSE == g_uSleepKeepDDROn)
    {
      /* Turn DDR on */
      uImage_rpm_set_clk_values(SNOCFreq, BIMCFreq, rpmMode);
    }
    else
    {
      /* Notify transition is complete in the case where we are not actually
       * turning off DDR. */
      uSleep_notifyDDRTransitionComplete(TRUE);
    }
    
    /* Reset the frequency values which will be updated when we re-enter
     * island mode */
    BIMCFreq = 0;
    SNOCFreq = 0;
  }
 
  return;
}

/*
 * uSleep_setStateInternal
 */
void SLEEP_INLINE uSleep_setStateInternal(uSleep_internal_state state)
{
  /* Only one state can be set, so ensure only 1 bit is set */
  CORE_VERIFY(state == (state & -state));
  g_uSleepData.state = state;
  return;
}

/*
 * uSleep_getStateInternal
 */
uSleep_internal_state SLEEP_INLINE uSleep_getStateInternal(void)
{
  return(g_uSleepData.state);
}

/*
 * uSleep_getDDRWakeupTimeInternal
 */
uint64 SLEEP_INLINE uSleep_getDDRWakeupTimeInternal(void)
{
  return(g_uSleepData.ddr_wakeup_timer);
}

/*
 * uSleep_setLastSleepWakeupInternal
 */
void SLEEP_INLINE uSleep_setLastSleepWakeupInternal(uint64 wakeupTime)
{
  g_uSleepData.last_wakeup_timestamp = wakeupTime;
}

/*
 * uSleep_getLastPMITimestampInternal
 */
uint64 SLEEP_INLINE uSleep_getLastPMITimestampInternal(void)
{
  return(g_uSleepData.last_pmi_timestamp);
}

/*
 * uSleep_setLastPMITimestampInternal
 */
void SLEEP_INLINE uSleep_setLastPMITimestampInternal(uint64 PMITime)
{
  g_uSleepData.last_pmi_timestamp = PMITime;
}

/*
 * uSleep_getLastSleepWakeupInternal
 */
uint64 SLEEP_INLINE uSleep_getLastSleepWakeupInternal(void)
{
  return(g_uSleepData.last_wakeup_timestamp);
}

/*
 * uSleep_setCXOModeInternal
 */
void uSleep_setCXOModeInternal(uSleep_CXO_mode mode)
{
  uSleep_internal_state state = uSleep_getStateInternal();

  CORE_VERIFY(mode < USLEEP_CXO_SHUTDOWN_MAX_MODE);

  /* Only change XO setting if we are not in an exit state. This ensures we
   * have exited the cached mode so allow uSleep to exit. */
  if(state & (uSLEEP_INTERNAL_STATE_ACTIVE      |
              uSLEEP_INTERNAL_STATE_FAST_ENTRY  |
              uSLEEP_INTERNAL_STATE_FULL_ENTRY))
  {
    uSleepLog_printf(USLEEP_LOG_LEVEL_PROFILING, 1,
                     "Set XO (State: %s)",
                     USLEEP_CXO_SHUTDOWN_DISABLE == mode ? "Disable" : "Enable");

    /* Set the XO mode */
    g_uSleepData.XO_mode = mode;

    /* Enable/disabled APCR override*/
    if(USLEEP_CXO_SHUTDOWN_DISABLE == mode)
    {
      /* If XO is disabled, set the current LPR mode to cached so APCR is entered
       * immediately */ 
      uSleepLPR_setActiveMode(usleep_lpr_cached_idx);
    }
    else
    {
      /* Set to un-cached mode so the cached exit function is run. Actual mode
       * entered will be selected when system goes idle. */
      uSleepLPR_setActiveMode(usleep_lpr_apcr_idx);
    }
  }

  return;
}

/*
 * uSleep_getCXOModeInternal
 */
uSleep_CXO_mode SLEEP_INLINE uSleep_getCXOModeInternal(void)
{
  return(g_uSleepData.XO_mode);
}

/*
 * uSleep_getProfilingDataPtr
 */
uSleep_transition_profiling* uSleep_getProfilingDataPtr(void)
{
  return &g_uSleepData.transition_data;
}

/*
 * uSleep_transitionToNormalOperation
 */
void uSleep_transitionToNormalOperation(void)
{
  /* Exit island mode */
  CORE_VERIFY(ISLAND_MGR_EOK == island_mgr_island_exit());
  
  /* Finish the transition */
  uSleep_completeTransitionToDDR();

  return;
}

