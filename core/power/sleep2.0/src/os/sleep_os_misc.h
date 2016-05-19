#ifndef SLEEP_OS_MISC_H
#define SLEEP_OS_MISC_H

/*==============================================================================
  FILE:         sleep_os_misc.h

  OVERVIEW:     This file contains miscellaneous functions and types 
                declarations for a given processor.

  DEPENDENCIES: None

                Copyright (c) 2014 Qualcomm Technologies, Inc. (QTI).
                All Rights Reserved.
                Qualcomm Technologies Confidential and Proprietary
================================================================================
$Header: //components/rel/core.adsp/2.6.1/power/sleep2.0/src/os/sleep_os_misc.h#1 $
$DateTime: 2014/10/16 12:45:40 $
==============================================================================*/

#include "sleep_osi.h"

/*==============================================================================
                            TYPE DEFINITIONS
 =============================================================================*/
/**
 * sleep_PMI_handler_ptr_type
 *
 * @brief PMI ISR function pointer that is called durring APCR exiting. The 
 *        pointer will be modified to point to the correct handler based on if
 *        the system is in uImage or normal operational modes. 
 */
typedef void (*sleep_PMI_handler_ptr_type)(void);

/*==============================================================================
                           GLOBAL FUNCTION DECLARATIONS
 =============================================================================*/

/** 
 * sleepOS_uSleepPerformDefault
 *  
 * @brief This function is the main entry into uSleep mode. It will switch to 
 *        uSleep when restrictions allow it.        
 */
uint32 sleepOS_uSleepPerformDefault(void);

/** 
 * sleepOS_uSleepPerformError 
 *  
 * @brief This function is the fatal exit from uImage function. There is no
 *        execution or recovery from this function. The OS should never allow
 *        this function to run. 
 */
uint32 sleepOS_uSleepPerformError(void);

/**
 * sleepOSMisc_setPMIHandlerFunctionPTR
 *
 * @brief This function sets the PMI handler that will be called from the ISR        
 *  
 * @param coreNum:    Core number to change the PMI function for.
 * @param newPMIPtr:  Pointer to the function to call when the PMI ISR is 
 *                    invoked.
 */
void sleepOSMisc_setPMIHandlerFunctionPTR(uint32                     coreNum,
                                          sleep_PMI_handler_ptr_type newPMIPtr);

/**
 * sleepOS_PMIPerformer
 *
 * @brief PMI handler code for normal operational image.
 */
void sleepOS_PMIPerformer(void);

#endif /* SLEEP_OS_MISC_H */
