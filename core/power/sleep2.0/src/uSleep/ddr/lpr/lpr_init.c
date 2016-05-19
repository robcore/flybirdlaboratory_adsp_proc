/*==============================================================================
  FILE:         lpr_init.c

  OVERVIEW:     This file provides the uSleep LPR init functions which are
                called while in normal operational mode

  DEPENDENCIES: None
  
                Copyright (c) 2014 Qualcomm Technologies, Inc. (QTI).
                All Rights Reserved.
                Qualcomm Technologies Confidential and Proprietary
================================================================================
$Header: //components/rel/core.adsp/2.6.1/power/sleep2.0/src/uSleep/ddr/lpr/lpr_init.c#2 $
$DateTime: 2014/11/06 11:48:29 $
==============================================================================*/
#include "DALStdDef.h"
#include "CoreVerify.h"
#include "uSleep_lpr.h"
#include "spm.h"
#include "rpm.h"
#include "rpmclient.h"
#include "kvp.h"
#include "uSleep_util.h"
#include "q6_lpm_config.h"

/*==============================================================================
                       INTERNAL FUNCTION DEFINITIONS
 =============================================================================*/
/*
 * uSleepLPR_apcrInit
 */
void uSleepLPR_apcrInit(boolean islandEntry)
{
  /* All modes in uSleep do APCR + PLL off. Setup to perform APCR standalone
   * mode initially on entry and clock gating on exit. */
  if(TRUE == islandEntry)
  {
    q6LPMConfig_setupModeConfig(SPM_MODE_APCR_PLL_LPM, TRUE);
    q6LPMConfig_setupL2RetConfig();
  }
  else
  {
    q6LPMConfig_setupModeConfig(SPM_MODE_CLK_GATE, FALSE);
  }

  return;
}

/* 
 * uSleepLPR_cxoInit
 */
void uSleepLPR_cxoInit(boolean islandEntry)
{
  /* Specifics for 8994 */
  static uint32             vddReq      = 1;
  static rpm_resource_type  vddResType  = RPM_SMPS_A_REQ;
  static uint32             vddResID    = 1;
  static kvp_t              *vddKVP     = NULL;

  /* Normal operational mode has already added the XO vote to the sleep set.
   * This vote is never removed, and all we need to do is add the vdd min KVP values. */
  if(NULL == vddKVP)
  {
    vddKVP = kvp_create(1*4*3);
    kvp_put(vddKVP, /* PM_NPA_KEY_CORNER_LEVEL_KEY */ 0x6E726F63,
            sizeof(vddReq), (void *)&vddReq);
  }

  if(TRUE == islandEntry)
  {
    /* Add vdd min vote to sleep set */
    kvp_reset(vddKVP);
    rpm_post_request(RPM_SLEEP_SET, vddResType, vddResID, vddKVP);
  }
  else
  {
    /* Cancelling vdd min request */
    rpm_post_request(RPM_SLEEP_SET, vddResType, vddResID, NULL);
  }

  return;
}

