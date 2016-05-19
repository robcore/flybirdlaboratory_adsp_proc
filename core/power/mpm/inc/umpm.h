#ifndef UMPM_H
#define UMPM_H
/*==============================================================================
  FILE:         umpm.h
  
  OVERVIEW:     This file provides the libraries for the micro - virtual MPM
                (uMPM) driver API code required for island modes

  DEPENDENCIES: None

                Copyright (c) 2014 QUALCOMM Technologies, Inc. (QTI).
                All Rights Reserved.
                Qualcomm Confidential and Proprietary

===============================================================================
$Header: //components/rel/core.adsp/2.6.1/power/mpm/inc/umpm.h#1 $
$DateTime: 2014/10/16 12:45:40 $
==============================================================================*/ 
#include "DALStdDef.h"

/*==============================================================================
                       EXTERNAL FUNCTION DEFINITIONS
 =============================================================================*/
/** 
 * umpm_TriggerInterrupts 
 *  
 * @brief Loops through all the latched MPM interrupts and performs an
 *        associated soft-trigger operation so that it looks like the interrupt
 *        was caught in the normal mechanism, rather than by a secondary
 *        interrupt controller during deep sleep.
 * 
 * @note This function is specific to island mode operation
 */
void umpm_triggerInterrupts(void);

/** 
 * umpm_setWakeupTimetick 
 *  
 * @brief Writes a wake up tick for this master into memory region reserved for 
 *        it in the shared message ram during rpm assisted low power modes.
 *  
 * @note This function is specific to island mode operation 
 *
 * @param wakeupTime: Time (in ticks) when this master wants rpm to wake it up.
 */
void umpm_setWakeupTimetick(uint64 wakeupTime);

#endif  /* UMPM_H */
