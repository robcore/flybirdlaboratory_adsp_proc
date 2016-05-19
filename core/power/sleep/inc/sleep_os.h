#ifndef SLEEP_OS_H
#define SLEEP_OS_H
/*==============================================================================
  FILE:           sleep_os.h

  OVERVIEW:       This file contains declarations of functions that are used
                  in the common main sleep subsystem

  DEPENDENCIES: None

                Copyright (c) 2013 Qualcomm Technologies, Inc. (QTI).
                All Rights Reserved.
                Qualcomm Technologies Confidential and Proprietary
================================================================================
$Header: //components/rel/core.adsp/2.6.1/power/sleep/inc/sleep_os.h#1 $
$DateTime: 2014/10/16 12:45:40 $
==============================================================================*/
#include "DALStdDef.h"
#include "npa.h"

/*==============================================================================
                                MACRO DEFINITIONS
 =============================================================================*/
/**
 * @brief SLEEP_QUERY_WAKEUP_TIME
 *
 * Macro to use when querying the wakeup node for soft (hint of) wakeup time
 * settings.
 */
#define SLEEP_QUERY_WAKEUP_TIME      (NPA_QUERY_RESERVED_END+1)

/*==============================================================================
                           GLOBAL FUNCTION DECLARATIONS
 =============================================================================*/
/**
 * sleep_perform_lpm
 *
 * @brief Put the system into the lowest power state possible.
 *
 * This function will eventually call the sleep subsystem and solver to
 * determine the list of low power modes that can be entered during idle time.
 *
 * @return Non-zero on failure.
 */
uint32 sleep_perform_lpm(void);

/**
 * sleepOS_getHardDeadline 
 *  
 * @brief Returns the hard deadline that the sleep task must be 
 *        awake by, in absolute ticks.  This is the time that
 *        sleep expects to exit by.
 *  
 *        NOTE:  It only makes sense to call this function from
 *               within the idle context (i.e., from within an
 *               LPR).
 *  
 * @return The hard deadline, in absolute ticks, that sleep 
 *         expects to exit by.
 */
uint64 sleepOS_getHardDeadline(void);

/**
 * sleepOS_getSoftDeadline 
 *  
 * @brief Returns the soft deadline that the sleep task must use
 *        as a hint of when the next wakeup might occur, in absolute ticks.
 *
 *        NOTE:  It only makes sense to call this function from
 *               within the idle context (i.e., from within an
 *               LPR).
 *  
 * @return The soft deadline, in absolute ticks, that sleep is hinted of the
 *         next wakeup.
 */
uint64 sleepOS_getSoftDeadline(void);

#endif /* SLEEP_OS_H */
