#ifndef ERRI_H
#define ERRI_H
 
/*===========================================================================

                    Error Handling Service Internal Header File

Description
 
Copyright (c) 2009 - 2014 by Qualcomm Technologies Incorporated.  All Rights Reserved.

$Header: //components/rel/core.adsp/2.6.1/debugtools/err/src/erri.h#1 $
 
===========================================================================*/

#ifdef CUST_H
#include "customer.h"
#endif

#include "comdef.h"
#include "err.h"
#include "errlog.h"

#if defined(ERR_HW_QDSP6)
  #include "err_hw_qdsp6.h"
#else
  #include "err_hw_arm.h"
#endif

#if defined(ERR_IMG_ADSP)
  #include "err_img_adsp.h"
#else
  #error "bad configuration"
#endif

#ifdef ERR_CFG_QURT
  #include "err_qurt.h"
#endif //ERR_CFG_QURT

#include "qurt_qdi.h"
#include "qurt_qdi_driver.h"
#include "qurt.h"

/* Number of info files stored before we begin overwriting them. */
/* Only applicacable if FEATURE_SAVE_TACE_EXTENDED is not defined. */
/* Otherwise, we use the same value as diag_debug_max_files */
//#ifndef FEATURE_SAVE_TRACE_EXTENDED
//#define ERR_DATA_NUM_FILES 4
//#endif

extern coredump_type coredump;


/* Magic number that determine whether the data in uninitialized RAM has
 * already been saved to flash or not.
 */
#define ERR_DATA_MAGIC_NUMBER       (uint64)0x5252452041544144ULL
#define ERR_DATA_RESET_MAGIC_NUMBER (uint64)0xABCD06261974EA29ULL

#define ERR_LOOP_DELAY_USEC 10000
#define ERR_CLK_PAUSE_SMALL 500
#define ERR_CLK_PAUSE_KICK 100


#define ERR_MIN_POLL_TIME_MS 500


//Err log definitions
  /* Maximum number of error logs to store per session */
  // no longer configurable, being deprecated
  #define ERR_DATA_MAX_LOGS 1
  
  /* Maximum size of the extended info written out to flash. */
  #ifndef ERR_DATA_MAX_SIZE  
  #define ERR_DATA_MAX_SIZE 0x4000
  #endif

#define UERR_CODE_SECTION __attribute__((section (".text.uErr")))
#define UERR_DATA_SECTION __attribute__((section (".data.uErr")))

/* Following values should be accomodated only in a byte. 
 * Cannot be greater than 255  */

typedef enum
{
  ERR_TYPE_ERR_FATAL = 0,
  ERR_TYPE_NON_RECOVERABLE_EXCEPTION = 1,
  ERR_TYPE_MAX = 255
} err_type_e;

#define ERR_GET_PID_TO_UPPER_8_BITS             ( (qurt_getpid()<<8) & 0xFF00 )
#define ERR_RAISE_EXCEPTION_ARG(x)              ( QURT_ECODE_UPPER_ERR_SERVICES | ERR_GET_PID_TO_UPPER_8_BITS | (x) )
#define ERR_GET_ERR_TYPE_FROM_EXCEPTION_ARG(x)  (0xFF & x )
#define ERR_GET_PID_FROM_EXCEPTION_ARG(x)       ( (0xFF00 & x ) >> 8 )


/* Temporary Definition .. modify it after kernel change */
#ifndef QURT_ECODE_UPPER_ERR_SERVICES
#define QURT_ECODE_UPPER_ERR_SERVICES QURT_ECORE_UPPER_ERR_SERVICES
#endif 

  typedef uint64 err_data_flag_type;

  typedef struct {
    err_data_flag_type flag;
    uint32 length;
    char   data[ERR_DATA_MAX_SIZE];
  } err_data_log_type;
  
  typedef struct {
    err_data_flag_type reset_flag;
    err_data_log_type err_log[ERR_DATA_MAX_LOGS];
  } err_data_type;


void err_pause_usec(uint32 usec);

void err_fatal_jettison_core (unsigned int line, const char *file_name,
  const char *format, uint32 param1, uint32 param2, uint32 param3) ;

#endif /* ERRI_H */
