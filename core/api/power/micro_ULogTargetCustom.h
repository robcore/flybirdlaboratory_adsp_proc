#ifndef MICRO_ULOGTARGETCUSTOM_H
#define MICRO_ULOGTARGETCUSTOM_H
/*============================================================================
  micro_ULogTargetCustom.h

  Target-specific type definitions.

  Copyright (c) 2012 Qualcomm Technologies Incorporated.
  All Rights Reserved.
  Qualcomm Confidential and Proprietary
============================================================================*/

#ifndef TRUE
#define TRUE   1
#endif

#ifndef FALSE
#define FALSE  0
#endif

#ifndef NULL
#define NULL  0
#endif

#ifndef _UINT32_DEFINED
typedef  unsigned long int  uint32;      /* Unsigned 32 bit value */
#define _UINT32_DEFINED
#endif

#ifndef _UINT16_DEFINED
typedef  unsigned short     uint16;      /* Unsigned 16 bit value */
#define _UINT16_DEFINED
#endif

#ifndef _UINT8_DEFINED
typedef  unsigned char      uint8;       /* Unsigned 8  bit value */
#define _UINT8_DEFINED
#endif

#ifndef _INT32_DEFINED
typedef  signed long int    int32;       /* Signed 32 bit value */
#define _INT32_DEFINED
#endif

#ifndef _INT16_DEFINED
typedef  signed short       int16;       /* Signed 16 bit value */
#define _INT16_DEFINED
#endif

#ifndef _INT8_DEFINED
typedef  signed char        int8;        /* Signed 8  bit value */
#define _INT8_DEFINED
#endif

#if defined(__GNUC__)
#define __int64 long long
#endif

#ifndef _UINT64_DEFINED
typedef  unsigned __int64   uint64;      /* Unsigned 64 bit value */
#define _UINT64_DEFINED
#endif

#ifndef _INT64_DEFINED
typedef  __int64            int64;       /* Signed 64 bit value */
#define _INT64_DEFINED
#endif

#ifndef _BYTE_DEFINED
typedef  unsigned char      byte;        /* byte type */
#define  _BYTE_DEFINED
#endif

#if defined(__cplusplus)
#define MICRO_ULOG_INLINE inline
#else
#define MICRO_ULOG_INLINE __inline
#endif

/*----------------------------------------------------------------------------
  Depending on the processor/OS, each micro image will have a unique method 
  for obtaining timestamps and locks. Hence we need to detect the OS and select
  the appropriate macros
----------------------------------------------------------------------------*/

#ifdef WINSIM 

#define MICRO_ULOG_GETTIME64              ( 0 )
#define MICRO_ULOG_MUTEX_HANDLE_TYPE      void*
#define MICRO_ULOG_MUTEX_TYPE             void
#define MICRO_ULOG_LOCK_INIT( x )         ( x = 1 ) //sga need to update for PC tests
#define MICRO_ULOG_LOCK_GET( x )          ( 0 )
#define MICRO_ULOG_LOCK_RELEASE( x )      ( 0 )

#elif 1 //defined(ADSP_8994) Working with Chris/Spencer to define a global flag for use in code. Hardcoded for now
#include "uTimetick.h"
#include "qurt_mutex.h"

#define LOCKABLE_LOGS_SUPPORTED
#define MICRO_ULOG_GETTIME64             (uint64)uTimetick_Get()
#define MICRO_ULOG_MUTEX_HANDLE_TYPE     qurt_mutex_t*
#define MICRO_ULOG_MUTEX_TYPE            qurt_mutex_t
#define MICRO_ULOG_LOCK_INIT( x )        qurt_mutex_init( x )
#define MICRO_ULOG_LOCK_GET( x )         qurt_mutex_lock( x ) 
#define MICRO_ULOG_LOCK_RELEASE( x )     qurt_mutex_unlock( x )

#elif defined(FEATURE_REX) || defined(FEATURE_RIVAIMG) //WCNSS
#include "ubsp_timers.h"

#define MICRO_ULOG_GETTIME64             (ubsp_timer_get_tick(&timestamp),timestamp)
#define MICRO_ULOG_MUTEX_HANDLE_TYPE     void* 
#define MICRO_ULOG_MUTEX_TYPE            void
#define MICRO_ULOG_LOCK_INIT( x )        ( 0 )
#define MICRO_ULOG_LOCK_GET( x )         ( 0 )
#define MICRO_ULOG_LOCK_RELEASE( x )     ( 0 )
#endif

/*----------------------------------------------------------------------------
  Each system may have a unique QDSS send packet API.  
  ULog requires the 2 QDSS APIs to include and not include 
  a QDSS timestamp.  Lack of a QDSS timestamp is used as 
  an indicator of secondary packets for multi packet message formats.
  Customize these values and functions for your system. 
 ----------------------------------------------------------------------------*/
//defines for how the QDSS functions return success of failure
#define MICRO_ULOG_QDSS_SUCCESS  0
#define MICRO_ULOG_QDSS_FAIL     -1

//include the correct header file for the QDSS API
//example: #include “QDSSLite.h”

//Allocate the QDSS port.  Return MICRO_ULOG_QDSS_SUCCESS or MICRO_ULOG_QDSS_FAIL
#define MICRO_ULOG_QDSS_ALLOC(x)  (0) /* example: QDSSAllocPort(x) */

//free the QDSS port if necessary
#define MICRO_ULOG_QDSS_FREE(x)       /* TBD */ 

//QDSS write functions
#define MICRO_ULOG_QDSS_TS_WRITE(log, firstContent, firstCount)   /* example  QDSSWriteOSTPacket(log->stmPort, QDSSOSTHeader(TRACER_ENTITY_ULOG, log->protocol_num), firstContent, firstCount);*/
#define MICRO_ULOG_QDSS_NO_TS_WRITE(log, secondContent, secondCount)  /* example QDSSWriteOSTPacket(log->stmPort, QDSSOSTHeader(TRACER_ENTITY_ULOG, log->protocol_num), secondContent, secondCount);*/

//strlcpy
#if defined (WINSIM) || defined (WIN_DEBUGGER_EXTENSION)
#include "stdio.h"
#define MICRO_ULOG_STRLCPY(a, b, c) strcpy_s(a, c, b)

#elif defined (__GNUC__)

#include "stdio.h"
#include <stringl/stringl.h>
#define MICRO_ULOG_STRLCPY strlcpy 

#else

#include <string.h>
#define MICRO_ULOG_STRLCPY strlcpy

#endif

#endif /* MICRO_ULOGTARGETCUSTOM_H */

