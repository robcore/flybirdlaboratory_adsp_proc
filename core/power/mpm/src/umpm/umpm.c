/*===========================================================================
  FILE:         umpm.c
  
  OVERVIEW:     This file contains the necessary uMPM API functions to interface
                to the Virtual MPM (vMPM) driver in island mode

  DEPENDENCIES: None

                Copyright (c) 2014 QUALCOMM Technologies, Inc. (QTI).
                All Rights Reserved.
                Qualcomm Confidential and Proprietary

===============================================================================
$Header: //components/rel/core.adsp/2.6.1/power/mpm/src/umpm/umpm.c#1 $
$DateTime: 2014/10/16 12:45:40 $
=============================================================================*/ 
#include "DALStdDef.h"
#include "CoreVerify.h"
#include "vmpm.h"
#include "umpm.h"
#include "vmpm_internal.h"
#include "vmpm_utils.h"
#include "umpm_log.h"
#include "uInterruptController.h"
#include "uGPIOInt.h"
#include "CoreIntrinsics.h"

/*==============================================================================
                            FORWARD DECLARATIONS
 =============================================================================*/
static void umpm_RetriggerGpio(uint32 gpioNum);
static void umpm_RetriggerIrq(uint32 intNum);

/*==============================================================================
                            INTERNAL VARIABLES
 =============================================================================*/
static mpm_retrigger_functions g_umpmRetriggerFunctions = 
{
  umpm_RetriggerGpio,
  umpm_RetriggerIrq,
  umpm_LogPrintf,
};

/*==============================================================================
                       INTERNAL FUNCTION DEFINITIONS
 =============================================================================*/
/**
 * umpm_RetriggerGpio
 * 
 * @brief uMPM version of the GPIO retrigger function.
 * 
 * @param gpioNUM: GPIO number to retrigger.
 */
static void umpm_RetriggerGpio(uint32 gpioNum)
{
  /* Triggering GPIO on the master */
  CORE_VERIFY(UGPIOINT_SUCCESS == uGPIOInt_TriggerInterrupt(gpioNum));
  return;
}

/**
 * umpm_RetriggerIrq 
 *  
 * @brief uMPM version of the interrupt retrigger function.
 * 
 * @param gpioNUM: Interrupt number to retrigger. 
 */
static void umpm_RetriggerIrq(uint32 intNum)
{
  /* Triggering interrupt on the master */
  CORE_VERIFY(UINTERRUPT_SUCCESS == 
                    uInterruptController_TriggerInterrupt(intNum));

  return;
}

/*==============================================================================
                       EXTERNAL FUNCTION DEFINITIONS
 =============================================================================*/
/*
 * umpm_TriggerInterrupts
 */
void umpm_triggerInterrupts(void)
{
  vmpm_retriggerInternal(&g_umpmRetriggerFunctions);
  return;
}

/*
 * umpm_SetWakeupTimetick
 */
void umpm_setWakeupTimetick(uint64 wakeupTime)
{
  vmpm_SetWakeupTimetick(wakeupTime);
  return;
}

