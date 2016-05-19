/*==============================================================================
  FILE:         uSleep_api.c

  OVERVIEW:     This file provides uSleep API functions for user PD that are
                located in the ISLAND section

  DEPENDENCIES: None
  
                Copyright (c) 2014 Qualcomm Technologies, Inc. (QTI).
                All Rights Reserved.
                Qualcomm Technologies Confidential and Proprietary
================================================================================
$Header: //components/rel/core.adsp/2.6.1/power/sleep2.0/src/uSleep/client_user/island/client_API.c#1 $
$DateTime: 2014/10/16 12:45:40 $
==============================================================================*/
#include "DALStdDef.h"
#include "uSleep.h"
#include "uSleepi.h"
#include "uSleep_util.h"
#include "uSleep_qdi.h"
#include "qurt.h"
/*==============================================================================
                           INTERNAL VARIABLES
 =============================================================================*/
/* QDI Client Handle to communicate with Guest OS layer. This variable needs to
 * be located in island section memory, but is initialized while in normal
 * operational mode */
int g_uSleepQDIClientHandle = -1;

/*==============================================================================
                          EXTERNAL API FUNCTIONS
 =============================================================================*/
/*
 * uSleep_exit
 */
uint32 uSleep_exit(void)
{
  return qurt_qdi_handle_invoke(g_uSleepQDIClientHandle, USLEEP_QDI_EXIT);
}

/*
 * uSleep_setCXOMode
 */
uint32 uSleep_setCXOMode(uSleep_CXO_mode mode)
{
  return qurt_qdi_handle_invoke(g_uSleepQDIClientHandle, 
                                USLEEP_QDI_SET_CXO, mode); 
}

