/*==============================================================================
  FILE:         lpr_util.c

  OVERVIEW:     This file provides the support for all LPR modes

  DEPENDENCIES: Object file generated from source is marked as island section
  
                Copyright (c) 2014 Qualcomm Technologies, Inc. (QTI).
                All Rights Reserved.
                Qualcomm Technologies Confidential and Proprietary
================================================================================
$Header: //components/rel/core.adsp/2.6.1/power/sleep2.0/src/uSleep/island/lpr/lpr_util.c#3 $
$DateTime: 2014/11/06 11:48:29 $
==============================================================================*/
#include "DALStdDef.h"
#include "CoreVerify.h"
#include "uSleep.h"
#include "uSleepi.h"
#include "spm.h"
#include "uSleep_lpr.h"
#include "uSleep_log.h"
#include "uTimetick.h"
#include "utimer.h"
#include "qurt.h"
#include "uSleep_util.h"

/*==============================================================================
                             INTERNAL VARIABLES
 =============================================================================*/
/* Supported LPR's in uSleep. Note that threshold values are not currently used. */
static uSleep_LPR g_uSleepLPR[USLEEP_NUMBER_LOW_POWER_MODES] =
{
  /* NULL mode
   * Used when latency restriction prevents entering any mode */
  {0,                           /* Minimum threshold duration (unused currently) */
    "NULL",                     /* LPR name */
    0,                          /* Enter + exit latency */
    0,                          /* Backoff latency */
    NULL,                       /* Init function */
    NULL,                       /* Enter & exit functions for the LPR */
    NULL, 
    FALSE},                     /* Cacheable flag */

  /* APCR pll off without RPM handshake.
   * Used when XO is explicitly disabled and will enable the override setting. */
  {1499,
    "Cached",
    5, 2,
    NULL, uSleepLPR_apcrCachedEnter, uSleepLPR_apcrCachedExit, 
    TRUE},

  /* APCR pll off without RPM handshake. Used when XO is enabled, but there
   * is not enough time to enter it. */
  {1500, 
    "Standalone", 
    900, 350,
    uSleepLPR_apcrInit, uSleepLPR_apcrEnter, uSleepLPR_apcrExit, 
    FALSE},

  /* APCR pll off with RPM handshake. */
  {5000, 
    "CXO", 
    12800, 1700,
    uSleepLPR_cxoInit, uSleepLPR_cxoEnter, uSleepLPR_cxoExit, 
    FALSE}
};

/* Chosen LPR mode for current sleep cycle. Initially set to APCR standalone. */
static uSleep_LPR *g_uSleepChosenLPR = &g_uSleepLPR[usleep_lpr_apcr_idx];

/*==============================================================================
                          EXTERNAL FUNCTION DEFINITIONS
 =============================================================================*/
/*
 * uSleepLPR_setActiveMode 
 */
void uSleepLPR_setActiveMode(usleep_lpr_index index)
{
  boolean newCache;
  boolean currentCache;

  CORE_VERIFY(index < USLEEP_NUMBER_LOW_POWER_MODES);

  /* Get current and new LPR's cache mode */
  currentCache = g_uSleepChosenLPR->cached;
  newCache     = g_uSleepLPR[index].cached;

  uSleepLog_printf(USLEEP_LOG_LEVEL_PROFILING, 2,
                   "Set active mode "
                   "(Current: %s) "
                   "(New: %s)",
                   g_uSleepChosenLPR->name,
                   g_uSleepLPR[index].name);

  /* If we are changing to a cached mode from an un-cached, run the cached enter
   * function */ 
  if(FALSE == currentCache &&
     TRUE == newCache)
  {
    /* Update current LPR first so cached enter function is run */
    g_uSleepChosenLPR = &g_uSleepLPR[index];

    /* Cached modes can not use wakeup time since we don't know it yet so just
     * pass 0 */
    uSleepLPR_runLPRFunctions(TRUE, 0);
  }
  else
  {
    /* If we are changing to an un-cached mode from a cached, run the cached
     * exit function first and then update the currently chosen mode. */
    if(TRUE == currentCache &&
       FALSE == newCache)
    {
      uSleepLPR_runLPRFunctions(FALSE, 0);
    }

    /* Update current LPR */
    g_uSleepChosenLPR = &g_uSleepLPR[index];
  }

  return;
}

/*
 * uSleepLPR_runLPRFunctions 
 */
void uSleepLPR_runLPRFunctions(boolean enterFunction,
                               uint64  wakeupDeadline)
{
  if(TRUE == enterFunction)
  {
    uSleepLog_QDSSPrintf(USLEEP_LOG_LEVEL_PROFILING,
                         USLEEP_LPR_ENTER_NUM_ARGS,
                         USLEEP_LPR_ENTER_STR, 
                         USLEEP_LPR_ENTER,
                         g_uSleepChosenLPR->name);

    CORE_VERIFY(NULL != g_uSleepChosenLPR->enter_func);
    g_uSleepChosenLPR->enter_func(wakeupDeadline);
  }
  else
  {
    uSleepLog_QDSSPrintf(USLEEP_LOG_LEVEL_PROFILING,
                         USLEEP_LPR_EXIT_NUM_ARGS,
                         USLEEP_LPR_EXIT_STR, 
                         USLEEP_LPR_EXIT);

    CORE_VERIFY(NULL != g_uSleepChosenLPR->exit_func);
    g_uSleepChosenLPR->exit_func();
  }

  return;
}

/*
 * uSleepLPR_idleSolver
 */
uSleep_LPR *uSleepLPR_idleSolver(uint64 wakeupDeadline)
{
  uint64 now = uTimetick_Get();

  /* Check if there is time to do XO shutdown.
   * Note that if XO was disabled, we would not be at this point; APCR would
   * have automatically run when sleep is waiting for idle. */
  if(wakeupDeadline > (now + g_uSleepLPR[usleep_lpr_cxo_idx].latency))
  {
    /* XO is a valid choice. */ 
    g_uSleepChosenLPR = &g_uSleepLPR[usleep_lpr_cxo_idx];
  }
  else if(wakeupDeadline > (now + g_uSleepLPR[usleep_lpr_apcr_idx].latency))
  {
    /* No time for XO, do manual APCR */
    g_uSleepChosenLPR = &g_uSleepLPR[usleep_lpr_apcr_idx];
  }
  else
  {
    /* No mode chosen */
    g_uSleepChosenLPR = &g_uSleepLPR[usleep_lpr_null_idx];
  }

  return(g_uSleepChosenLPR);
}

/* 
 * uSleepLPR_init
 */
void uSleepLPR_init(boolean islandEntry)
{
  uint32      nLPR;
  uSleep_LPR  *LPRPtr;

  uSleepLog_printf(USLEEP_LOG_LEVEL_PROFILING, 0,
                   "Init uSleep LPR");

  for(nLPR=0; nLPR < USLEEP_NUMBER_LOW_POWER_MODES; nLPR++)
  {
    LPRPtr = &g_uSleepLPR[nLPR];
    CORE_VERIFY_PTR(LPRPtr);

    if(NULL != LPRPtr->init_func)
    {
      /* Call each LPR's init function */
      LPRPtr->init_func(islandEntry);
    }
  }

  return;
}

/* 
 * uSleepLPR_PMIPerformer 
 */
void uSleepLPR_PMIPerformer(void)
{
  uSleep_setLastPMITimestampInternal(uTimetick_Get());

  /* Call exit function */
  uSleep_workerExit();
  return;
}

