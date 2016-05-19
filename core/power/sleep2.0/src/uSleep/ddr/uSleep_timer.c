/*==============================================================================
  FILE:         uSleep_timer.c

  OVERVIEW:     This file provides the functions located in the normal section
                to handle exit requirements for a DDR timer

  DEPENDENCIES: None
 
                Copyright (c) 2014 Qualcomm Technologies, Inc. (QTI).
                All Rights Reserved.
                Qualcomm Technologies Confidential and Proprietary
================================================================================
$Header: //components/rel/core.adsp/2.6.1/power/sleep2.0/src/uSleep/ddr/uSleep_timer.c#1 $
$DateTime: 2014/10/16 12:45:40 $
==============================================================================*/
#include "DALStdDef.h"
#include "CoreVerify.h"
#include "uSleep.h"
#include "uSleepi.h"
#include "uSleep_log.h"
#include "utimer.h"
#include "uTimetick.h"
#include "uSleep_timer.h"

/*==============================================================================
                           EXTERNAL VARIABLES
 =============================================================================*/
extern uint8 g_uSleepDDRTimerTaskStack[DDR_TIMER_HANDLER_STACK_SIZE];
extern qurt_anysignal_t g_uSleepDDRTimerSignal;
extern utimer_type g_uSleepTimerClient; 

/*==============================================================================
                       EXTERNAL FUNCTION DEFINITIONS
 =============================================================================*/
/*
 * uSleepTimer_init
 */
void uSleepTimer_init(void)
{
  int                 status;
  qurt_thread_t       tid;
  qurt_thread_attr_t  attr;
  
  /* Initilize the DDR timer thread attributes */ 
  qurt_thread_attr_init(&attr);
  
  /* Initilize the thread signal */  
  qurt_anysignal_init(&g_uSleepDDRTimerSignal);

  /* Initilize the timer client */
  CORE_VERIFY(UTE_SUCCESS == utimer_def_osal(&g_uSleepTimerClient, 
                                             UTIMER_NATIVE_OS_SIGNAL_TYPE, 
                                             &g_uSleepDDRTimerSignal, 0x1));
  
  /* Stack memory has to be statically allocated due to island section
   * location requirement */
  qurt_thread_attr_set_stack_size(&attr, DDR_TIMER_HANDLER_STACK_SIZE);
  qurt_thread_attr_set_stack_addr(&attr, (void *)g_uSleepDDRTimerTaskStack); 

  qurt_thread_attr_set_priority(&attr, DDR_TIMER_HANDLER_PRIORITY);
  qurt_thread_attr_set_tcb_partition(&attr, 1); /* task is located in uImage */
  qurt_thread_attr_set_name(&attr, "uSleep_TmrHnd");

  /* Create the DDR timer handler task in uImage section memory */
  status = qurt_thread_create(&tid, &attr, uSleepTimer_exitSignalTask, NULL);

  CORE_LOG_VERIFY(status == QURT_EOK,
                  uSleepLog_printf(USLEEP_LOG_LEVEL_PROFILING, 0,
                                   "uSleepTimer_init: "
                                   "creation failed"));

  return;
}

/*
 * uSleepTimer_setValue
 */
void uSleepTimer_setValue(uint64 deadline)
{
  uint64 now = uTimetick_Get();

  CORE_VERIFY(deadline > now);

  /* Create a uTimer from the given DDR timer that will fire early enough
   * so that uImage has exited by the time the DDR timer fires */
  CORE_VERIFY(UTE_SUCCESS == utimer_set_64(&g_uSleepTimerClient, 
                                           (deadline - now), 0, UT_TICK)); 
  return;
}

