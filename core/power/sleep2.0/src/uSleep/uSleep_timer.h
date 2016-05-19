#ifndef USLEEP_TIMER_H
#define USLEEP_TIMER_H
/*==============================================================================
  FILE:         uSleep_timer.h

  OVERVIEW:     Internal types and definitions for the handling of the normal
                operational mode timer

  DEPENDENCIES: None
  
                Copyright (c) 2014 Qualcomm Technologies, Inc. (QTI).
                All Rights Reserved.
                Qualcomm Technologies Confidential and Proprietary
================================================================================
$Header: //components/rel/core.adsp/2.6.1/power/sleep2.0/src/uSleep/uSleep_timer.h#1 $
$DateTime: 2014/10/16 12:45:40 $
==============================================================================*/
#include "DALStdDef.h"

/*==============================================================================
                                  DEFINES
 =============================================================================*/
#define DDR_TIMER_HANDLER_STACK_SIZE  1024
#define DDR_TIMER_HANDLER_PRIORITY    9

/*==============================================================================
                            FUNCTION DECLARATIONS
 =============================================================================*/
/**
 * uSleepTimer_init
 * 
 * @brief Initializes the uSleep timer handler task that will allow uSleep
 *        to exit early enough to service the first non-deferrable DDR timer.
 */
void uSleepTimer_init(void);

/**
 * uSleepTimer_setValue
 * 
 * @brief Adds a non-deferrable uTimer in order to exit uSleep mode in time to 
 *        service the DDR timer.
 *  
 * @param deadline: Absolute timer value in ticks
 */
void uSleepTimer_setValue(uint64 deadline);

/**
 * uSleepTimer_clearTimer 
 *  
 * @brief Clears the uTimer that was created based on normal mode timer that
 *        is used to trigger island exit.
 *        This function should be called on the exit transition.
 */
void uSleepTimer_clearTimer(void);

/**
 * uSleepTimer_exitSignalTask 
 *  
 * @brief Main uSleep timer task that handles exiting island mode when a DDR 
 *        timer triggers the exit.   
 */
void uSleepTimer_exitSignalTask(void *ignored);

#endif /* USLEEP_TIMER_H */

