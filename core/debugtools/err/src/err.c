/*====*====*====*====*====*====*====*====*====*====*====*====*====*====*====*

         E R R O R     R E P O R T I N G    S E R V I C E S

GENERAL DESCRIPTION
  This module provides error reporting services for both fatal and
  non-fatal errors.  This module is not a task, but rather a set of
  callable procedures which run in the context of the calling task.

Copyright (c) 1992-2014 by Qualcomm Technologies Incorporated.  All Rights Reserved.

*====*====*====*====*====*====*====*====*====*====*====*====*====*====*====*/

/*===========================================================================

                        Edit History

$Header: //components/rel/core.adsp/2.6.1/debugtools/err/src/err.c#3 $

when       who     what, where, why
--------   ---     ----------------------------------------------------------
08/28/14   din     Fixed compilation issue for Non island mode scenarios.
08/27/14   din     Replaced snprintf with mutex free calls.
07/31/14   din     Made some changes to support User PD.
07/22/14   din     Moved initialization of some members of coredump to err_init.
07/02/14   din     Accomodate Qurt argument change to complete ERR_FATAL call flow.
04/18/14   din     Added changes for ADSP island mode.
10/03/11   mcg     Stripping to a minimal set of functionality to support 
                   Subsystem Restart on qurt wo/rex emulation (LPASS)

===========================================================================*/


/*===========================================================================

                     INCLUDE FILES FOR MODULE

===========================================================================*/

#include "comdef.h"
#include "qurt.h"
#include "qurt_event.h"
#include "err.h"
#include "erri.h"
#include <stdlib.h>
#include <stringl.h>
#include "sys_m.h"
#include "tms_utils.h"

#ifdef FEATURE_SMEM
#include "smem.h"
#endif /* FEATURE_SMEM */



/*===========================================================================

                      Prototypes for internal functions

===========================================================================*/
static void err_emergency_error_recovery(void) ERR_NORETURN_ATTRIBUTE UERR_CODE_SECTION ;
extern void err_halt_execution( void ) ERR_NORETURN_ATTRIBUTE; //from err_jettison_core.s
static void err_log_ssr_failure_reason(void);
static void err_reentrancy_violated(void) ERR_NORETURN_ATTRIBUTE UERR_CODE_SECTION;
static void err_raise_to_kernel(void) ERR_NORETURN_ATTRIBUTE UERR_CODE_SECTION;
void err_fatal_handler( void ) ERR_NORETURN_ATTRIBUTE;

void err_fatal_lock(void) UERR_CODE_SECTION;
static void err_minimal_logging (const msg_const_type* const_blk, uint32 code1, 
		         uint32 code2, uint32 code3) UERR_CODE_SECTION;

/*===========================================================================

                 Defines and variable declarations for module

===========================================================================*/

static boolean err_services_init_complete = FALSE;

/* Struct used to hold coredump data */
coredump_type coredump;
uint32 coredump_count=0;


typedef struct 
{
  uint32 array[SIZEOF_ARCH_COREDUMP_REGISTERS];
  const msg_const_type* const_blk;
  uint32 param[ERR_LOG_NUM_PARAMS];
} uerr_tcm_data_t;

static uerr_tcm_data_t uerr_tcm_data UERR_DATA_SECTION;

extern void err_dog_force_bite(void);

/* Ptr used by assembly routines to grab registers */
/*  (update this as needed if struct changes)      */
arch_coredump_type* UERR_DATA_SECTION arch_coredump_ptr = (arch_coredump_type*)(&uerr_tcm_data.array);


//+++++++++++++++++++++++
// LPASS PORTING DECLS
//+++++++++++++++++++++++
// 
static ERR_MUTEX_TYPE err_fatal_mutex UERR_DATA_SECTION;
static boolean err_fatal_mutex_init UERR_DATA_SECTION;


//SFR (Subsystem restart Failure Reason) decl's
#ifdef FEATURE_SMEM
  char* err_ssr_smem_buf_ptr;
  #define ERR_SSR_REASON_SIZE_BYTES 80
  static const char err_sfr_init_string[]="SFR Init: wdog or kernel error suspected.";
#endif

//dynamic message scratch buffer
#ifdef FEATURE_SMEM
  // must fit into both SFR and coredump.err.aux_msg
  #define ERR_DYNAMIC_MSG_SIZE ( MIN(ERR_SSR_REASON_SIZE_BYTES, ERR_LOG_MAX_MSG_LEN) )
#else
  #define ERR_DYNAMIC_MSG_SIZE ( ERR_LOG_MAX_MSG_LEN )
#endif  //FEATURE_SMEM
static char* err_dynamic_msg_scratch_buf = 0;

/* The function tables below are processed by the error handler
 * in the following order:
 *   1. err_preflush_internal (one time)
 *   2. err_preflush_external (one time)
 *   3. err_flush_internal (one time)
 *   4. err_postflush_internal (called repeatedly in a loop)
 */
 
static const err_cb_ptr err_preflush_internal[] = 
{
  err_log_ssr_failure_reason,
  /* NULL must be last in the array */
  NULL
};

#define ERR_MAX_PREFLUSH_CB 5
static err_cb_ptr err_preflush_external[ERR_MAX_PREFLUSH_CB] = {NULL};

/* Flush will be done by kernel */
static const err_cb_ptr err_flush_internal[] =
{
  err_raise_to_kernel,
  /* NULL must be last in the array */  
  NULL
};



/*===========================================================================

                              Function definitions

===========================================================================*/




/*===========================================================================

FUNCTION ERR_INIT

DESCRIPTION
  This function checks if NV has been built.  If so then it loads up the
  error log cache from NV, it initializes error counts and local variables,
  and it sets error services to online.  If NV has not been built then
  error log is not loaded and error services remain offline and error
  logging does not take place.  Any access to NV is performed here directly,
  without relying on the NV task.  Thus error service can be initialized
  and used early in the life of the DMSS and right after boot.  Note
  that if NV has not been built, error services provide no error logging
  capabilities.  However NV is built once, after initial factory startup,
  and rarely thereafter.  Thus except for the first ever powerup of the
  unit after NV build or re-build, error logging will take place as usual.

DEPENDENCIES
  None.

RETURN VALUE
  None.

SIDE EFFECTS
  Error log is loaded from NVM into RAM resident cache.

===========================================================================*/

void err_init (void)
{


  ERR_MUTEX_INIT(&err_fatal_mutex);
  err_fatal_mutex_init = TRUE;


#ifdef FEATURE_SMEM
  err_ssr_smem_buf_ptr = sys_m_init_sfr_buffer();
  if (NULL != err_ssr_smem_buf_ptr)
  {
    strlcpy (err_ssr_smem_buf_ptr, err_sfr_init_string, ERR_SSR_REASON_SIZE_BYTES);
  }
#endif

 //We use a scratch buf from the heap to minimize risk of an 
  //overwrite corrupting the coredump structure or stack
  err_dynamic_msg_scratch_buf = (char*)malloc(ERR_DYNAMIC_MSG_SIZE);
  if (err_dynamic_msg_scratch_buf)
  {
    memset (err_dynamic_msg_scratch_buf, 0, ERR_DYNAMIC_MSG_SIZE);
  }

  MSG(MSG_SSID_TMS, MSG_LEGACY_LOW,"Err service initialized.");
  
  err_services_init_complete = TRUE;
  
  /* Set type and version values */
  coredump.version = ERR_COREDUMP_VERSION;
  coredump.arch.type = ERR_ARCH_COREDUMP_TYPE;
  coredump.arch.version = ERR_ARCH_COREDUMP_VER;  
  coredump.os.type = ERR_OS_COREDUMP_TYPE;
  coredump.os.version = ERR_OS_COREDUMP_VER;
  coredump.err.version = ERR_COREDUMP_VER;
  
} /* err_init */


/*===========================================================================

FUNCTION ERROR_FATAL_HANDLER

DESCRIPTION
  This function is invoked from err_fatal_jettison_core. When using JTAG,
  default breakpoint for ERR_FATAL should be placed at this function.
  Will log error to SMEM, kill the PA, and copy the coredump data into
  the err_data structure in unintialized memory.
 

DEPENDENCIES

RETURN VALUE
  No return.

SIDE EFFECTS
  **************************************************************
  ************ THERE IS NO RETURN FROM THIS FUNCTION ***********
  **************************************************************

===========================================================================*/
void err_fatal_handler ( void )
{
  int fptr_index;
  static uint32 err_count=0;

  err_count++;

  fptr_index=0;
  while(err_preflush_internal[fptr_index] != NULL)
  {
	/* Cycle through internal functions */
	err_preflush_internal[fptr_index]();
	fptr_index++;
  }

  for(fptr_index=0; fptr_index<ERR_MAX_PREFLUSH_CB; fptr_index++)
  {
	/* Cycle through external functions */
	if(err_preflush_external[fptr_index]!= 0)
	{
	  err_preflush_external[fptr_index]();
	}
  }

  /* Main loop (cache flush happens here) */
  fptr_index=0;
  while(err_flush_internal[fptr_index] != NULL)
  {
	/* Cycle through internal functions */
	err_flush_internal[fptr_index]();
	fptr_index++;
  }
  
  // We must not reach here
  err_halt_execution();  

} /* err_fatal_handler */


/*===========================================================================

FUNCTION ERR_FATAL_LOCK
DESCRIPTION
  Gets mutex for err_fatal to prevent multiple and/or cascading errors
============================================================================*/
void err_fatal_lock(void) 
{
  static boolean err_reentrancy_flag UERR_DATA_SECTION ;
  if(err_fatal_mutex_init==TRUE)
  {
    ERR_MUTEX_LOCK(&err_fatal_mutex);

    //mutex does not prevent the same thread being routed back into err_fatal by a bad callback
    if(err_reentrancy_flag)
    {
      //does not return
      err_reentrancy_violated();
    }
    else
    {
      err_reentrancy_flag = TRUE;
    }
  }
  else
  {
    /* If not intialized then this is an early ERR_FATAL */
    /* Proceed anyway so it can be handled */
  }
}


/*===========================================================================

FUNCTION ERR_FATAL_CORE_DUMP
DESCRIPTION
  Logs fatal error information, including a core dump.

  NOTE: There is no return from this function.
============================================================================*/
void err_fatal_core_dump (
  unsigned int line,      /* From __LINE__ */
  const char   *file_name, /* From __FILE__ */
  const char   *format   /* format string */
)
{
  err_fatal_lock();
  err_fatal_jettison_core(line, file_name, format, 0, 0, 0);
}

  
/*===========================================================================

FUNCTION ERR_FATAL_JETTISON_CORE
DESCRIPTION
  Logs fatal error information, including a core dump.
  Not to be called directly by outside code -- for that, use the function
  err_fatal_core_dump().

  NOTE: There is no return from this function.
============================================================================*/
void err_fatal_jettison_core (
  unsigned int line,       /* From __LINE__ */
  const char   *file_name, /* From __FILE__ */
  const char   *format,    /* format string */
  uint32 param1,
  uint32 param2,
  uint32 param3
)
{

  /* NOTE: register information should already be saved prior to
   * calling this function.
   */
#if 0
  /* Get timestamp of error */
  #warning porting issue: timestamp format
  coredump.err.timestamp = sns_em_get_timestamp();
#endif

#if 0
  /* Get tcb_ptr (if not pre-filled by err_exception_handler) */
  if (!coredump.os.tcb_ptr) {
//  coredump.os.tcb_ptr = (ERR_OS_TCB_TYPE*)rex_self();
    #warning bring up hack: err needs a context pointer
    coredump.os.tcb_ptr = (ERR_OS_TCB_TYPE*)NULL;
  }
#endif


  /* Store line number */
  coredump.err.linenum = line;

  /* Copy file name */
  if(file_name != 0)
  {
    (void) strlcpy((char *)coredump.err.filename,
                       (char *)file_name,    
                       ERR_LOG_MAX_FILE_LEN);
  }

  /* Copy message string */
  if(format != 0)
  {
    (void) strlcpy((char *)coredump.err.message,
                       (char *)format,
                       ERR_LOG_MAX_MSG_LEN);
  }
  
  coredump.err.param[0]=param1;
  coredump.err.param[1]=param2;
  coredump.err.param[2]=param3;
  
  /* Call ERR_FATAL handler (no return) */
  err_fatal_handler();

}


/*=========================================================================

FUNCTION err_emergency_error_recovery

DESCRIPTION
  Action to be taken when more than one error has occurred, or if an
  error occurs before err_init has completed.

DEPENDENCIES
  None
 
RETURN VALUE
  None
  
SIDE EFFECTS
  No return from this function

===========================================================================*/
static void err_emergency_error_recovery( void )
{
  /* Define action to be taken when multiple crashes occur */

  /* flush cache, etc - does not return*/
  err_raise_to_kernel();

  /* Stop active thread - will not reach here*/
  err_halt_execution();
}

/*=========================================================================

FUNCTION err_crash_cb_register

DESCRIPTION
  Registers a function (ptr type err_cb_ptr) to be called after an ERR_FATAL
  Function should NOT rely on any messaging, task switching (or system calls
  that may invoke task switching), interrupts, etc.

  !!!These functions MUST NOT call ERR_FATAL/ASSERT under ANY circumstances!!!

DEPENDENCIES
  None
 
RETURN VALUE
  TRUE if function added to table successfully
  FALSE if function not added.
  
SIDE EFFECTS
  None

===========================================================================*/
boolean err_crash_cb_register(err_cb_ptr cb)
{
  int i;
  boolean rval = FALSE;

  for(i=0; i<ERR_MAX_PREFLUSH_CB; i++)
  {
	if(err_preflush_external[i] == NULL)
	{
	  err_preflush_external[i] = cb;
	  rval = TRUE;
	  break;
	}
  }

  return rval;
}


/*=========================================================================

FUNCTION err_crash_cb_dereg

DESCRIPTION
 Deregisters a function from the error callback table.

DEPENDENCIES
  None
 
RETURN VALUE
  TRUE if removed
  FALSE if function is not found in table
  
SIDE EFFECTS
  None

===========================================================================*/
boolean err_crash_cb_dereg(err_cb_ptr cb)
{
  int i;
  boolean rval = FALSE;

  for(i=0; i<ERR_MAX_PREFLUSH_CB; i++)
  {
	if(err_preflush_external[i] == cb)
	{
	  err_preflush_external[i] = NULL;
	  rval = TRUE;
	  break;
	}
  }
  
  return rval;
}
/*===========================================================================

FUNCTION       err_copy_tcm_data_into_coredump

DESCRIPTION

DEPENDENCIES
  None.

RETURN VALUE
  None.

SIDE EFFECTS
  None.

===========================================================================*/

void err_copy_tcm_data_into_coredump(void)
{
  /* Copy line number */
  coredump.err.linenum = uerr_tcm_data.const_blk -> desc.line;

  /* Copy file name */
  if(uerr_tcm_data.const_blk -> fname != 0)
  {
    (void) strlcpy((char *)coredump.err.filename,
                       (char *)uerr_tcm_data.const_blk -> fname,    
                       ERR_LOG_MAX_FILE_LEN);
  }

  /* Copy message string */
  if(uerr_tcm_data.const_blk -> fmt != 0)
  {
    (void) strlcpy((char *)coredump.err.message,
                       (char *)uerr_tcm_data.const_blk -> fmt,
                       ERR_LOG_MAX_MSG_LEN);
  }
  
  coredump.err.param[0]=uerr_tcm_data.param[0];
  coredump.err.param[1]=uerr_tcm_data.param[1];
  coredump.err.param[2]=uerr_tcm_data.param[2];


  /* Copy register content */
  memscpy( coredump.arch.regs.array, SIZEOF_ARCH_COREDUMP_REGISTERS,
             uerr_tcm_data.array,  SIZEOF_ARCH_COREDUMP_REGISTERS );

}

	

/*===========================================================================

FUNCTION       err_minimal_logging

DESCRIPTION

DEPENDENCIES
  None.

RETURN VALUE
  None.

SIDE EFFECTS
  None.

===========================================================================*/

static void err_minimal_logging (const msg_const_type* const_blk, uint32 code1, uint32 code2, uint32 code3)
{
   uerr_tcm_data.const_blk = const_blk;
   uerr_tcm_data.param[0]  = code1;
   uerr_tcm_data.param[1]  = code2;
   uerr_tcm_data.param[2]  = code3;

} /* err_minimal_logging*/


/*===========================================================================

FUNCTION       err_SaveFatal

DESCRIPTION

DEPENDENCIES
  None.

RETURN VALUE
  None.

SIDE EFFECTS
  None.

===========================================================================*/
void err_SaveFatal3 (const msg_const_type* const_blk, uint32 code1, uint32 code2, uint32 code3) 
{
 /* enter critical section */
 err_fatal_lock();
 
 /* Capture registers */
 jettison_core();
 
 /* Capture minimal log */
 err_minimal_logging( const_blk, code1, code2, code3 );
 
 /*  Raise an exception to qurt */
 qurt_exception_raise_nonfatal( ERR_RAISE_EXCEPTION_ARG(ERR_TYPE_ERR_FATAL) );

 /* Must not reach here */
 err_dog_force_bite();

 while(1)
 {
 }
 
}

void err_SaveFatal0 (const msg_const_type* const_blk) 
{
 /* enter critical section */
 err_fatal_lock();

 /* Capture registers */
 jettison_core();
 
 /* Capture minimal log */
 err_minimal_logging( const_blk,0, 0, 0 );

 /*  Raise an exception to qurt */
 qurt_exception_raise_nonfatal( ERR_RAISE_EXCEPTION_ARG(ERR_TYPE_ERR_FATAL) );

 /* Must not reach here */
 err_dog_force_bite();

 while(1)
 {
 }

}

/*===========================================================================

FUNCTION       err_Fatal_dynamic

DESCRIPTION
  Do not call any of these functions directly.  They should be accessed by
  macros defined in err.h exclusively.

DEPENDENCIES
  None.

RETURN VALUE
  None.

SIDE EFFECTS
  None.

===========================================================================*/
void err_process_dynamic_callback(err_dynamic_msg_cb callback, const uint32 cb_param)
{
  if (err_services_init_complete && callback && err_dynamic_msg_scratch_buf)
  {
    callback(err_dynamic_msg_scratch_buf, ERR_DYNAMIC_MSG_SIZE, cb_param);

  //was something written?
  if (err_dynamic_msg_scratch_buf[0] != 0)
  {
    //guarantee null termination
    err_dynamic_msg_scratch_buf[ERR_DYNAMIC_MSG_SIZE-1]=0;

    //copy to relevant structures
    memscpy(coredump.err.aux_msg, sizeof(coredump.err.aux_msg), err_dynamic_msg_scratch_buf, ERR_DYNAMIC_MSG_SIZE);
#ifdef FEATURE_SMEM
    if (err_ssr_smem_buf_ptr )
    {
      memscpy(err_ssr_smem_buf_ptr, ERR_SSR_REASON_SIZE_BYTES, err_dynamic_msg_scratch_buf, ERR_DYNAMIC_MSG_SIZE);
    }
#endif //FEATURE_SMEM
  }
}
}


void err_SaveFatal_dynamic (const msg_const_type* const_blk, err_dynamic_msg_cb callback, const uint32 cb_param)
{

 /* enter critical section */
 err_fatal_lock();

 /* Capture registers */
 jettison_core();
 
 /* Capture minimal log */
 err_minimal_logging( const_blk,0, 0, 0 );
 
 /* Allow callee to fill SFR and aux_msg */
 err_process_dynamic_callback(callback,cb_param);

 /*  Raise an exception to qurt */
 qurt_exception_raise_nonfatal( ERR_RAISE_EXCEPTION_ARG(ERR_TYPE_ERR_FATAL) );

 /* Must not reach here */
 err_dog_force_bite();

 while(1)
 {
 }

}


void err_put_log (word line, const char *file_ptr)
{
  //err logging is not supported in this build
}

/*=========================================================================

FUNCTION err_log_ssr_failure_reason

DESCRIPTION
  Used to log a minimal set of failure reason to smem.  Primarily to assist
  locating faulting subsystem in many-subsystem architectures.

DEPENDENCIES
  smem

RETURN VALUE
  None

SIDE EFFECTS
  None

===========================================================================*/
static void err_log_ssr_failure_reason(void)
{
#ifdef FEATURE_SMEM
  word sfr_line = coredump.err.linenum;
  const char *sfr_file_ptr = coredump.err.filename;
  const char *sfr_msg_ptr = coredump.err.message;
  uint32 sfr_p0 = coredump.err.param[0];
  uint32 sfr_p1 = coredump.err.param[1];
  uint32 sfr_p2 = coredump.err.param[2];
  char *sfr_buf_ptr = err_ssr_smem_buf_ptr;
  int sfr_written = 0;

  if (sfr_buf_ptr && sfr_file_ptr) 
  { 
    // write "__MODULE__:__LINE:"
    sfr_written = tms_utils_fmt(sfr_buf_ptr, ERR_SSR_REASON_SIZE_BYTES, "%s:%d:", sfr_file_ptr, sfr_line);
    ERR_MEMORY_BARRIER();

    if ((sfr_written > 0) && sfr_msg_ptr) 
    {
      // append err fatal message
      sfr_written--;
      sfr_buf_ptr += sfr_written; //increment and overwrite previous null-term
      sfr_written = tms_utils_fmt(sfr_buf_ptr, (ERR_SSR_REASON_SIZE_BYTES-sfr_written), sfr_msg_ptr, sfr_p0, sfr_p1, sfr_p2);
      ERR_MEMORY_BARRIER();
    }

  }

#endif // FEATURE_SMEM
}


/*=========================================================================

FUNCTION err_reentrancy_violated

DESCRIPTION
  This will only be called when ERR_FATAL is called while processing an
  ERR_FATAL.  It usually means that somone has registered a non-compliant
  callback function using 

DEPENDENCIES
  None

RETURN VALUE
  None

SIDE EFFECTS
  None

===========================================================================*/
#define ERR_REENTRANCY_STRING "ERR_FATAL reentrancy violation, remove cb until resolved"
static void err_reentrancy_violated(void)  
{
  if ( qurt_island_get_status() == FALSE )
  {
    /* Record secondary failure to coredump */
    strlcpy(coredump.err.aux_msg, ERR_REENTRANCY_STRING, sizeof(ERR_REENTRANCY_STRING));
  }

  err_emergency_error_recovery();

}

/*=========================================================================

FUNCTION err_raise_to_kernel

DESCRIPTION
  Function which will terminate user space handling and raise to kernel

DEPENDENCIES
  None

RETURN VALUE
  None

SIDE EFFECTS
  None

===========================================================================*/
static void err_raise_to_kernel(void)
{
  #ifdef ERR_FATAL_FLUSH_CACHE_NO_RETURN
    ERR_FATAL_FLUSH_CACHE_NO_RETURN();
  #else
    #error ERR_FATAL_FLUSH_CACHE_NO_RETURN not defined
  #endif

  /* Above should not have returned, let dog expire */
  while(1)
  {
  };

}

