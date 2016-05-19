#ifndef SLEEP_H
#define SLEEP_H
/*==============================================================================
  FILE:         sleep.h

  OVERVIEW:     This file contains public APIs related to Sleep task.

  DEPENDENCIES: None

                Copyright (c) 2012-2014 Qualcomm Technologies, Inc. (QTI).
                All Rights Reserved.
                Qualcomm Technologies Confidential and Proprietary
================================================================================
$Header: //components/rel/core.adsp/2.6.1/api/power/sleep2.0/sleep.h#1 $
$DateTime: 2014/10/16 12:45:40 $
==============================================================================*/
#ifdef __cplusplus
extern "C" {
#endif

#include "DALStdDef.h"
#include "sleep_stats.h"
#include "sleep_lpr.h"

/*==============================================================================
                              DEFINES & TYPES
 =============================================================================*/
#ifdef USLEEP_ISLAND_MODE_ENABLE
/* Macros to define memory sections. These will be used to locate specific
 * functions & data in the island memory section. */
#define USLEEP_CODE_SECTION __attribute__((section (USLEEP_ISLAND_CODE_STR)))
#define USLEEP_DATA_SECTION __attribute__((section (USLEEP_ISLAND_DATA_STR)))

#else
/* Define empty macros */
#define USLEEP_CODE_SECTION 
#define USLEEP_DATA_SECTION

#endif /* FEATURE_ISLAND_MODE_ENABLE */

/*==============================================================================
                            GLOBAL FUNCTION DECLARATIONS
 =============================================================================*/ 
/**
 * sleepOS_isProcessorInSTM
 *
 * @brief Checks if the processor is in Single threaded mode (also known
 *        as INTLOCK'd or Sleep context) when this function is called.
 *
 * For multicore (HLOS) targets, it should gives the status of core 
 * on which this function was called.
 *
 * @NOTE 
 * This function is more like a query function which returns the value 
 * at any given point. It may have changed immediately after calling it.
 *
 * @return Non-zero if processor in sleep context otherwise zero.
 */
uint32 sleepOS_isProcessorInSTM(void);

#ifdef __cplusplus
}
#endif

#endif /* SLEEP_H */

