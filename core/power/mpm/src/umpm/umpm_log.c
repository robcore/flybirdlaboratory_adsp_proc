/*============================================================================
  FILE:         umpm_log.c
  
  OVERVIEW:     This file implements the functions for logging umpm messages.

  DEPENDENCIES: None

                Copyright (c) 2014 Qualcomm Technologies, Inc. (QTI).
                All Rights Reserved.
                Qualcomm Technologies Confidential and Proprietary
=============================================================================
$Header: //components/rel/core.adsp/2.6.1/power/mpm/src/umpm/umpm_log.c#1 $
$DateTime: 2014/10/16 12:45:40 $
============================================================================*/
#include <stdarg.h>
#include "DALStdDef.h"
#include "umpm_log.h"
#include "micro_ULog.h"
#include "CoreVerify.h"

/*==============================================================================
                            INTERNAL VARIABLES
 =============================================================================*/
/* uMPM log handle */
static micro_ULogHandle g_umpmLogHandle = 0;

/* Pre-allocated log buffers required for island mode */
static char g_umpmLogBuffers[UMPM_LOG_SIZE];

/*==============================================================================
                        EXTERNAL FUNCTION DEFINITIONS
 =============================================================================*/
/*
 * umpm_logInit
 */
void umpm_logInit( void )
{
  uint32 effectiveSize;

  if(!g_umpmLogHandle)
  {
    /* Creating a log handle */
    CORE_VERIFY(MICRO_ULOG_SUCCESS == micro_ULog_CreateLog(&g_umpmLogHandle,
                                                           "uMPM Driver Log",
                                                           g_umpmLogBuffers,
                                                           &effectiveSize,
                                                           UMPM_LOG_SIZE));

    /* Enabling the log */
    micro_ULog_Enable(g_umpmLogHandle);
  }

  return;
}

/*
 * umpm_LogPrintf
 */
void umpm_LogPrintf(int arg_count, const char *format, ...)
{
  va_list args;

  va_start(args, format);
  micro_ULog_RealTimeVprintf(g_umpmLogHandle, arg_count, format, args);
  va_end(args);

  return;
}
