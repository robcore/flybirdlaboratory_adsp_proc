/*==============================================================================
  FILE:         uSleep_log_init.c
  
  OVERVIEW:     This file initializes the uSleep logging system.

  DEPENDENCIES: None

                Copyright (c) 2014 Qualcomm Technologies, Inc. (QTI).
                All Rights Reserved.
                Qualcomm Technologies Confidential and Proprietary
================================================================================
$Header: //components/rel/core.adsp/2.6.1/power/sleep2.0/src/uSleep/ddr/usleep_log_init.c#1 $
$DateTime: 2014/10/16 12:45:40 $
==============================================================================*/
#include <stdarg.h>
#include <string.h>
#include "DALStdDef.h"
#include "CoreVerify.h"
#include "uSleep_log.h"

/*==============================================================================
                          VARIABLE DECLARATIONS
 =============================================================================*/
uSleep_log g_uSleepLogs[USLEEP_LOG_TOTAL_NUMBER] = 
{
  {USLEEP_LOG_LEVEL_PROFILING,  "uSleep Profiling",   USLEEP_LOG_SIZE_PROFILE,    TRUE},
  {USLEEP_LOG_LEVEL_TRANSITION, "uSleep Transition",  USLEEP_LOG_SIZE_TRANSITION, TRUE},
};

/*==============================================================================
                           EXTERNAL VARIABLES
 =============================================================================*/
/* Combined log buffer located in island memory */
extern char g_uSleepLogBuffers[USLEEP_TOTAL_LOG_BUFFER_SIZE];

/*==============================================================================
                       GLOBAL FUNCTION DEFINITIONS
 =============================================================================*/
/*
 * uSleepLog_initialize
 */
void uSleepLog_initialize(void)
{
  uint32            nLog;
  uint32            level;
  uint32            effectiveSize;
  micro_ULogResult  status;
  uint32            indexLoc = 0;
  
  CORE_VERIFY(g_uSleepNumberOfLogs == USLEEP_LOG_TOTAL_NUMBER);
  
  for(nLog = 0; nLog < g_uSleepNumberOfLogs; nLog++)
  {
    level = g_uSleepLogs[nLog].level;

    if(USLEEP_LOG_IS_VALID_LEVEL(level) && 0 == g_uSleepLogHandles[level])
    {
      CORE_VERIFY(indexLoc < USLEEP_TOTAL_LOG_BUFFER_SIZE);

      /* Create each log based on the lock type */
      if(TRUE == g_uSleepLogs[level].lock)
      {
        status = micro_ULog_CreateLockableLog(&g_uSleepLogHandles[level],
                                              g_uSleepLogs[level].name,
                                              &g_uSleepLogBuffers[indexLoc],
                                              &effectiveSize,
                                              g_uSleepLogs[level].size);
      }
      else
      {
        status = micro_ULog_CreateLog(&g_uSleepLogHandles[level],
                                      g_uSleepLogs[level].name,
                                      &g_uSleepLogBuffers[indexLoc],
                                      &effectiveSize,
                                      g_uSleepLogs[level].size);
      }
      
      CORE_VERIFY(MICRO_ULOG_SUCCESS == status);

      /* Enabling the log */
      micro_ULog_Enable(g_uSleepLogHandles[level]);

      /* Prepare for next log location in global buffer */
      indexLoc += g_uSleepLogs[level].size;
    }
  }

  return;
}

