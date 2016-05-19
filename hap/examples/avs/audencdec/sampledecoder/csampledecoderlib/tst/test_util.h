#ifndef _EXAMPLE_UTILS_H
#define _EXAMPLE_UTILS_H
/*===========================================================================

                  C A P I   E X A M P L E   U T I L I T I E S

  Common definitions, types and functions for CAPI Examples

  Copyright (C) 2012 by QUALCOMM Technologies, Incorporated. All Rights Reserved.
===========================================================================*/

#ifdef CAPI_EXAMPLE_STANDALONE
/* -----------------------------------------------------------------------
** Standard include files
** ----------------------------------------------------------------------- */
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#if defined(__cplusplus)
#include <new>
extern "C" {
#endif // __cplusplus
#include<assert.h>

#define DECODER_FRAME_SIZE 1000

#define ADSP_EOK          ( 0x00000000 )
#define ADSP_EFAILED      ( 0x00000001 )
#define ADSP_EBADPARAM    ( 0x00000002 )
/* -----------------------------------------------------------------------
** ADSP and QURT Elite include files
** ----------------------------------------------------------------------- */
#include "q6sim_timer.h"



#define TRUE   (1)  /* Boolean true value. */
#define FALSE  (0)  /* Boolean false value. */

#define SAMPLEDEC_INP_BUFFER_SIZE 4096*2   /*Maximum Size of Input Buffer*/
#define SAMPLEDEC_OUT_BUFFER_SIZE 8192*2   /*Maximum Size of Output Buffer*/

#ifndef NULL
#define NULL (0)
#endif

typedef int ADSPResult;

typedef struct {
     char *in_fileName;
     char *out_fileName;
} Arg_t;

void   usage ( char * );
void   get_eargs ( int argc, char **argv, Arg_t *args );
/* ------------------------------------------------------------------------
 ** QURT ELITE Memory Definitions
 ** ------------------------------------------------------------------------ */
typedef enum
{
   QURT_ELITE_HEAP_DEFAULT=0,         
   QURT_ELITE_HEAP_OUT_OF_RANGE      //keep at end
}  QURT_ELITE_HEAP_ID;



void* qurt_elite_memory_malloc(uint32_t unBytes, QURT_ELITE_HEAP_ID heapId);
void qurt_elite_memory_free(void *ptr);




#define qurt_elite_memory_new(pObject, typeType, heapId, ...) { \
   void *pObj = qurt_elite_memory_malloc(sizeof(typeType), heapId); \
   (pObject) = (pObj) ? (new (pObj) (typeType)(__VA_ARGS__)) : NULL; \
}

#define qurt_elite_memory_delete(pObject, typeType) { \
   if (pObject) { (pObject)->~typeType(); \
   qurt_elite_memory_free (pObject); \
   (pObject) = NULL; } \
}

/* ------------------------------------------------------------------------
 ** QURT ELITE Diag Definitions
 ** ------------------------------------------------------------------------ */
#define debug_enable    1                  /**< disable or enable debug msg*/
#define lowest_priority DBG_MED_PRIO       /**< lowest debug message level to be shown*/

#define DBG_FATAL_PRIO 0
#define DBG_ERROR_PRIO 1
#define DBG_HIGH_PRIO  2
#define DBG_MED_PRIO   3
#define DBG_LOW_PRIO   4

#define MSG_SSID_QDSP6  0

//if __FILENAME macro is not available, just leave that field blank
#ifndef __FILENAME__
#define __FILENAME__ ""
#endif

// assert is for priority == 0 (i.e on ERROR)
// disable warning "conditional expression is constant" for debug_enable
#define DBG_MSG(ssid, priority, message, ...) \
  do { \
    if (debug_enable && (priority <= lowest_priority)) \
    { \
      uint64_t cycles = q6sim_read_cycles(); \
      int tms = ((cycles >> 10)*1805)>>20; \
      int tsec = ((cycles >> 10)*1805)>>30; \
      int tmin = ((cycles >> 10)*30)>>30; \
      printf(" %dm:%ds:%dms @ %d of %s : " message "\n", tmin, tsec-60*tmin, tms - 1000*tsec, __LINE__, __FILENAME__, ##__VA_ARGS__); \
      QURT_ELITE_ASSERT(priority);\
    } \
  } while(0) \

#define MSG(xx_ss_id, xx_ss_mask, xx_fmt)                       DBG_MSG(0,xx_ss_mask,xx_fmt)
#define MSG_1(xx_ss_id, xx_ss_mask, xx_fmt, xx_arg1)            DBG_MSG(0,xx_ss_mask,xx_fmt,xx_arg1)
#define MSG_2(xx_ss_id, xx_ss_mask, xx_fmt, xx_arg1, xx_arg2)   DBG_MSG(0,xx_ss_mask,xx_fmt,xx_arg1,xx_arg2)


#define MSG_FATAL(x_fmt, a, b, c) \
    MSG_3 (MSG_SSID_QDSP6, DBG_FATAL_PRIO, x_fmt, a, b, c)

/* Original macro cut&paste from AudCmnUtil.h, leave it outside SURF for kernel debugging */
/* This macro prints to QURT buffer */
/* Print macro for debugging */
#define PRINT()   printf("%s %d\n",__FILENAME__, __LINE__);

/*
   Qurt_elite version of assert.
*/
#define QURT_ELITE_ASSERT(x) assert(x)

#if defined(__cplusplus)
} // extern "C"
#endif

#else  // CAPI_EXAMPLE_STANDALONE
#include "qurt_elite.h"

#endif // CAPI_EXAMPLE_STANDALONE
#endif /* _EXAMPLE_UTILS_H */

