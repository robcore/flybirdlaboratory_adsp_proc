/*==============================================================================
  FILE:         uSleep_util.c

  OVERVIEW:     This file provides uSleep helper functions that are located in
                DDR memory space

  DEPENDENCIES: None
  
                Copyright (c) 2014 Qualcomm Technologies, Inc. (QTI).
                All Rights Reserved.
                Qualcomm Technologies Confidential and Proprietary
================================================================================
$Header: //components/rel/core.adsp/2.6.1/power/sleep2.0/src/uSleep/ddr/uSleep_util.c#1 $
$DateTime: 2014/10/16 12:45:40 $
==============================================================================*/
#include "DALStdDef.h"
#include "CoreVerify.h"
#include "uSleep_timer.h"
#include "uSleep_util.h"
#include "uSleep_lpr.h"
#include "sleep_os_misc.h"
#include "rpm.h"
#include "rpmclient.h"
#include "npa.h"
#include "smd.h"
#include "island_mgr.h"

/*==============================================================================
                             EXTERNAL VARIABLES
 =============================================================================*/
extern uSleep_global_data   g_uSleepData;

/*==============================================================================
                             INTERNAL VARIABLES
 =============================================================================*/
/* NPA query handles for BIMC and SNOC frequencies so DDR can be turned on/off */
static npa_query_handle g_uSleepBIMCQueryHandle;
static npa_query_handle g_uSleepSNOCQueryHandle;

/*==============================================================================
                       EXTERNAL FUNCTION DEFINITIONS
 =============================================================================*/
/*
 * uSleep_createQueryHandles
 */
void uSleep_createQueryHandles(void)
{
  /* Create frequency query handles for DDR on/off ability */
  CORE_VERIFY_PTR(g_uSleepBIMCQueryHandle = 
                  npa_create_query_handle(USLEEP_NPA_RESOURCE_BIMC));

  CORE_VERIFY_PTR(g_uSleepSNOCQueryHandle = 
                  npa_create_query_handle(USLEEP_NPA_RESOURCE_SNOC));

  return;
}

/*
 * uSleep_setDDRWakeupTimeInternal
 */
void uSleep_setDDRWakeupTimeInternal(uint64 wakeupTimer)
{
  /* Backoff the normal operational deadline by the time it takes to exit
   * uSleep */
  g_uSleepData.ddr_wakeup_timer = 
    wakeupTimer - g_uSleepData.transition_data.exit_latency;

  uSleepTimer_setValue(g_uSleepData.ddr_wakeup_timer);

  return;
}

/*
 * uSleep_setupIslandEntry
 */
void uSleep_setupIslandEntry(uint32 *BIMCFreq, uint32 *SNOCFreq)
{
  npa_query_type          qres;

  /* Set uImage active state as we are about to turn DDR off */
  uSleep_setStateInternal(uSLEEP_INTERNAL_STATE_ACTIVE);

  /* Get current snoc & bimc frequency votes. Note that we still have access
   * to NPA while we are normal operational mode */
  CORE_VERIFY(NPA_QUERY_SUCCESS == npa_query(g_uSleepBIMCQueryHandle,
                                             NPA_QUERY_CURRENT_STATE,
                                             &qres));
  *BIMCFreq = qres.data.value;

  CORE_VERIFY(NPA_QUERY_SUCCESS == npa_query(g_uSleepSNOCQueryHandle,
                                             NPA_QUERY_CURRENT_STATE,
                                             &qres));
  *SNOCFreq = qres.data.value;

  /* Disable the RPM SMD interrupt so sync and DDR API's do not cause us to
   * exit uImage */
  CORE_VERIFY(smd_disable_intr(SMEM_RPM) == SMD_STATUS_SUCCESS);

  /* Send sleep set */
  rpm_force_sync(RPM_SLEEP_SET);

  return;
}

/*
 * uSleep_completeTransitionToDDR
 */
void uSleep_completeTransitionToDDR(void)
{
  /* Indicate we have fully exited uSleep and are back in normal operational
   * mode */
  uSleep_setStateInternal(uSLEEP_INTERNAL_STATE_IN_DDR);

  /* Set sleep function pointer to uSleep perform function so we may  
   * re-enter island mode */
  uSleep_setIdleFunctionPtr(sleepOS_uSleepPerformDefault);

  /* Set PMI handler back to main image handler */
  sleepOSMisc_setPMIHandlerFunctionPTR(0, sleepOS_PMIPerformer);

  /* Clear pending RPM acks from the sleep set flush */
  rpm_clear_pending_acks(); 

  /* Uninitialize LPRs */
  uSleepLPR_init(FALSE);

  /* Reenable SMD interrupt */
  CORE_VERIFY(SMD_STATUS_SUCCESS == smd_enable_intr(SMEM_RPM));

  /* Call notification CB's when in normal operational mode */
  uSleep_transitionNotify(USLEEP_STATE_EXIT);

  return;
}

