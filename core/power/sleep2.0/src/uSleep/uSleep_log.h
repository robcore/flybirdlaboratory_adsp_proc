#ifndef USLEEP_LOG_H
#define USLEEP_LOG_H
/*==============================================================================
  FILE:         uSleep_log.h
  
  OVERVIEW:     Contains internal variables and functions declarations for the
                uSleep logging system
 
  DEPENDENCIES: None

                Copyright (c) 2014 Qualcomm Technologies, Inc. (QTI).
                All Rights Reserved.
                Qualcomm Technologies Confidential and Proprietary
================================================================================
$Header: //components/rel/core.adsp/2.6.1/power/sleep2.0/src/uSleep/uSleep_log.h#1 $
$DateTime: 2014/10/16 12:45:40 $
==============================================================================*/
#include <stdarg.h>
#include "DALStdDef.h"
#include "micro_ULog.h"

/*==============================================================================
                                TYPE DEFINITIONS
 =============================================================================*/
/**
 * uSleep_log_level
 * 
 * @brief uSleep log levels
 */
typedef enum uSleep_log_level
{
  USLEEP_LOG_LEVEL_PROFILING    = 0,
  USLEEP_LOG_LEVEL_TRANSITION,

  USLEEP_LOG_TOTAL_NUMBER
} uSleep_log_level;

/**
 * uSleep_log
 * 
 * @brief Main log data structure used to declare the logs
 */
typedef struct uSleep_log_s
{
  uSleep_log_level      level;
  const char            *name;
  uint32                size;
  boolean               lock;
}uSleep_log;

/*==============================================================================
                            DEFINITIONS & TYPES
 =============================================================================*/
/* Macros indicating size of various uSleep logs in bytes */
#define USLEEP_LOG_SIZE_PROFILE     MICRO_ULOG_MEM_NEEDED(1024)
#define USLEEP_LOG_SIZE_TRANSITION  MICRO_ULOG_MEM_NEEDED_LOCK(512)

/* Total size of all log buffers. This will be used to create one large static
 * memory space for the uSleep logs. */
#define USLEEP_TOTAL_LOG_BUFFER_SIZE (USLEEP_LOG_SIZE_PROFILE     + \
                                      USLEEP_LOG_SIZE_TRANSITION)

/**
 * USLEEP_LOG_IS_VALID_LEVEL
 *
 * @brief Macro to ensure that the passed log level is valid. If the level is
 *        valid, the condition will be TRUE else FALSE.
 *
 * @param level: sleep_log_level we want to verify.
 */
#define USLEEP_LOG_IS_VALID_LEVEL(level) (level < USLEEP_LOG_TOTAL_NUMBER)

/*==============================================================================
                             DATA DECLARATIONS
 =============================================================================*/
extern micro_ULogHandle   g_uSleepLogHandles[USLEEP_LOG_TOTAL_NUMBER];
extern const uint32       g_uSleepNumberOfLogs;

/*==============================================================================
                              INTERNAL FUNCTIONS
 =============================================================================*/
/**
 * uSleepLog_initialize
 *
 * @brief Initializes the uSleep log system
 */
void uSleepLog_initialize(void);

/**
 * uSleepLog_printf
 *
 * @brief Function that will log the messages.
 *
 * @param level: Level at which want to log the message.
 * @param arg_count: Number of parameteres that are being logged.
 * @param format: Format string for logging function.
 */
void uSleepLog_printf(uSleep_log_level level, int arg_count, 
                      const char *format, ...);

/**
 * uSleepLog_QDSSPrintf
 *
 * @brief This function is used to log an event both to QDSS, 
 *        as well as to the usleep log indicated in the first
 *        parameter.
 *  
 * @note If QDSS is not enabled, the normal log function will be called instead, 
 *       to minimize timeline impact.
 *
 * @param logLvl:   Log level severity of current message
 * @param numArg:   Number of parameters that are being logged.
 * @param str:      The format string for printing log.
 * @param eventID:  QDSS tracer ID to use.
 */
#ifdef USLEEP_ENABLE_QDSS
#include "tracer_event_ids.h"
#include "tracer_micro.h"

#define uSleepLog_QDSSEvent(numArg, eventID, ...)               \
  UTRACER_EVENT((tracer_event_id_t)eventID, ## __VA_ARGS__)

#define uSleepLog_QDSSPrintf(logLvl, numArg, str, eventID, ...) \
  do                                                            \
  {                                                             \
    UTRACER_EVENT((tracer_event_id_t)eventID, ## __VA_ARGS__);  \
    uSleepLog_printf(logLvl, numArg, str, ## __VA_ARGS__);      \
  } while (0)

#else 

#define uSleepLog_QDSSEvent(numArg, eventID, ...)
#define uSleepLog_QDSSPrintf(logLvl, numArg, str, eventID, ...) \
  uSleepLog_printf(logLvl, numArg, str, ## __VA_ARGS__ )

#endif /* USLEEP_ENABLE_QDSS */

#endif  /* USLEEP_LOG_H */

