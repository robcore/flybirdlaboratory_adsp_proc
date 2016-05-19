#ifndef SLEEP_OSI_H
#define SLEEP_OSI_H
/*==============================================================================
  FILE:           sleep_osi.h

  OVERVIEW:       This file contains sleep internal declarations of functions 
                  that are used in the common main sleep subsystem

  DEPENDENCIES: None

                Copyright (c) 2013-2014 Qualcomm Technologies, Inc. (QTI).
                All Rights Reserved.
                Qualcomm Technologies Confidential and Proprietary
================================================================================
$Header: //components/rel/core.adsp/2.6.1/power/sleep2.0/src/os/sleep_osi.h#1 $
$DateTime: 2014/10/16 12:45:40 $
==============================================================================*/
#include "DALStdDef.h"
#include "sleep.h"

/*==============================================================================
                            GLOBAL DEFINITIONS
 =============================================================================*/
/**
 * sleepOS_IdleModeType
 *
 * @brief Enumeration to indicate the Idle Mode Type
 */
typedef enum
{
  SLEEP_OS_IDLE_MODE_DEFAULT   = 0,   /* Configure for single threaded sleep */
  SLEEP_OS_IDLE_MODE_OVERRIDE  = 1,   /* Configure for low overhead sleep    */
  SLEEP_OS_IDLE_MODE_SWFI_ONLY = 
    SLEEP_OS_IDLE_MODE_OVERRIDE   ,   /* Where override is not available     */ 
  SLEEP_OS_IDLE_MODE_USLEEP    = 2,   /* Configure for uImage based sleep    */
  SLEEP_OS_IDLE_MODE_HOLD_OFF  = 3,   /* Configure for busy wait during idle */
  SLEEP_OS_IDLE_MODE_NUM_STATES
} sleepOS_IdleModeType;

/*==============================================================================
                           GLOBAL FUNCTION DECLARATIONS
 =============================================================================*/
/**
 * sleepOS_configIdleMode
 * 
 * @brief This function configures how processor idle is handled within sleep.
 * 
 * @param coreNum: Core on which we want to modify idle time 
 *                 behavior/configuration.
 * @param idleMode: Idle time behavior/configuration for next cycle.
 */
void sleepOS_configIdleMode(uint32 coreNum, sleepOS_IdleModeType idleMode);

/**
 * sleepOS_verifyIdleModeConfig
 *
 * @brief This function checks how processor idle is set to be handled with
 *        the input config.
 *
 * @param coreNum: Core for which we want to query idle time behavior.
 * @param idleMode: Enum for how processor idle is expected to be handled.
 *
 * @return TRUE if processor idle is currently handled in a same way as 
 *         specified by idleMode else FALSE.
 */
boolean sleepOS_verifyIdleModeConfig(uint32 coreNum,
                                     sleepOS_IdleModeType idleMode) USLEEP_CODE_SECTION;

/**
 * sleepOS_getFrequency
 *
 * @brief A query function to return cpu clock frequency in KHz.
 *
 * @return CPU frequency in KHz.
 */
uint32 sleepOS_getFrequency(void);

/**
 * sleepOS_mainTask
 *
 * @brief This is the main sleep task function
 *  
 * @note Function is located in island memory section.
 */
void sleepOS_mainTask(void *ignored) USLEEP_CODE_SECTION;

#endif /* SLEEP_OSI_H */

