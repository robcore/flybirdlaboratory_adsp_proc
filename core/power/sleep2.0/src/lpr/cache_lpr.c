/*==============================================================================
  FILE:         cache_lpr.c

  OVERVIEW:     This file provides the sleep LPR cache definition for the
                QDSP6V4 ALL WAIT low-power modes.

  DEPENDENCIES: None

                Copyright (c) 2013 Qualcomm Technologies, Inc. (QTI).
                All Rights Reserved.
                Qualcomm Technologies Confidential and Proprietary
================================================================================
$Header: //components/rel/core.adsp/2.6.1/power/sleep2.0/src/lpr/cache_lpr.c#1 $
$DateTime: 2014/10/16 12:45:40 $
==============================================================================*/

#include "q6_lpm_config.h"

/*===========================================================================
                              GLOBAL FUNCTIONS
 ==========================================================================*/
/** 
 * l2CacheLPR_initialize
 *  
 * @brief Initialize l2 cache LPR
 */
void l2CacheLPR_initialize(void)
{ 
  /* Set up various registers for most frequent modes - currently it is
   * L2 retention based on use cases we have but we can change that by 
   * adding target detection if necessary. */
  q6LPMConfig_setupL2RetConfig();
  return;
}

/** 
 * l2CacheLPR_nonRetentionEnter 
 *  
 * @brief Function that will be called while entering L2 non retention 
 *        low power mode.
 *
 * @param wakeup_tick: Time at which master is expected to wake up.
 */
void l2CacheLPR_nonRetentionEnter(uint64 wakeup_tick)
{
  q6LPMConfig_setupL2NonRetConfig();  
  return;
}

/** 
 * l2CacheLPR_nonRetentionExit 
 *  
 * @brief Function that will be called while exiting from L2 non retention mode.
 */
void l2CacheLPR_nonRetentionExit(void)
{
  /* Restore to most frequent configuration of L2 retention. */
  q6LPMConfig_setupL2RetConfig();
  return;
}

/** 
 * l2CacheLPR_retentionEnter 
 *  
 * @brief Function that will be called while entering L2 retention low 
 *        power mode.
 *
 * @param wakeup_tick: Time at which master is expected to wake up.
 */
void l2CacheLPR_retentionEnter(uint64 wakeup_tick)
{
  return;
}

/** 
 * l2CacheLPR_retentionExit 
 *  
 * @brief Function that will be called while exiting from L2 retention mode.
 */
void l2CacheLPR_retentionExit(void)
{
  return;
}

