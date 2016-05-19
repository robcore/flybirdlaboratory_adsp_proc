/*====*====*====*====*====*====*====*====*====*====*====*====*====*====*====*

                          Error Logging Code

General Description
  The routines in this file handle writing a simple text log with crash
  information to a designated buffer in memory.  The information in these
  logs should in most cases be enough to help identify where a crash
  occurred, but it is not anticipated that there will be enough information
  available in the log to fully debug the crash itself.

Copyright (c) 2009 by Qualcomm Technologies Incorporated.  All Rights Reserved.
All Rights Reserved.
*====*====*====*====*====*====*====*====*====*====*====*====*====*====*====*/

/*===========================================================================

                               Edit History

 $Header: //components/rel/core.adsp/2.6.1/debugtools/err/src/errlog.c#2 $ $DateTime: 2014/10/20 14:33:38 $ $Author: pwbldsvc $

when       who     what, where, why
--------   ---     ----------------------------------------------------------
08/27/14   din     Replaced snprintf with mutex free calls.
02/19/09   tbg     File Created

===========================================================================*/


#include "comdef.h"
#include "customer.h"
#include "target.h"
#include "errlog.h"
#include "err.h"
#include "erri.h"
#include "stdlib.h"
#include <stdio.h>
#include "tms_utils.h"
//#include "time_svc.h"
//#include "dog.h"

/* Misc labels for log printing.
   Should match any correspoding structs in errlog.h
 */
#define COREDUMP_SP_REG QDSP6_SP


/* Maximum number of words dumped from the stack */
#define ERR_STACK_DUMP_SIZE 0x64 

/* Version number of errlog format */
#define EXT_STORE_VERSION 3

//static boolean buf_init=FALSE;
//static char *buf_base_ptr=NULL;
//static char *buf_ptr=NULL;
//static uint32 buf_size=0;
//static uint32 buf_unused=0;
//static uint32 written;

/*===========================================================================
MACRO WRITE_BUF

DESCRIPTION
  MACRO to be used when printing to the log buffer.  Should be called using
  the same arguments you would pass to a printf() call.  Checks first to see
  if space is available in the buffer, then passes the buffer location, size,
  and VA_ARGS parameters to the tms_utils_fmt function. Upon returning, the
  various buffer pionters and size variables are updated as needed.
============================================================================*/
#define WRITE_BUF(...) \
  if(buf_unused != 0) { \
    written = tms_utils_fmt(buf_ptr, buf_unused, __VA_ARGS__); \
    if ( written > 0) \
      written--; \
    buf_ptr+=written; \
    buf_unused-=MIN(written,buf_unused); \
  }
#if 0
/*===========================================================================
FUNCTION REX_LOG_CORE_DUMP

DESCRIPTION
  Stub for deprecated function
============================================================================*/
void rex_log_core_dump(uint16      line,
                       const char *filename,
                       const char *fmt,
                       uint32      p1,
                       uint32      p2,
                       uint32      p3)
{
};

/*===========================================================================
FUNCTION ERR_LOG_REGISTERS (Static)

DESCRIPTION
  Logs register information to buffer
============================================================================*/
static void err_log_registers(void)
{
  uint32 i;
  uint32 *regs=(uint32*)&coredump.arch.regs.array[0];

  WRITE_BUF("Register values from coredump:\n");

  for(i=0; i<SIZEOF_ARCH_COREDUMP_REGISTERS; i++)
  {
	/* Print out register names and values */
	WRITE_BUF("%12s : 0x%08x\n", arch_coredump_register_label[i], (unsigned int)regs[i]);
  }

  WRITE_BUF("\n");

  return;
}

/*===========================================================================
FUNCTION ERR_LOG_STACK (Static)

DESCRIPTION
  Logs stack information to buffer, printing both address and data.
  Will not print stack addresses that fall outside of the stack range based
  on the TCB of the faulting task (in the case no TCB is reported, the TCB
  of the current task is used)
============================================================================*/
static void err_log_stack(void)
{
  uint32 i;
  uint32 *sp, stack_end;
  void *tcb_ptr = (void *)NULL;
  #ifdef FEATURE_REX_OPAQUE_TCB_APIS
  rex_task_attributes_type attr;
	rex_stack_pointer_type stack_start_ptr = NULL;
	rex_stack_size_type stack_size = 0;
  #else
  uint32 *stack_start_ptr = NULL;
  uint32 stack_size = 0;
  #endif //FEATURE_REX_OPAQUE_TCB_APIS

  /* Get stack pointer from rex_core */
  sp=(uint32*)coredump.arch.regs.array[COREDUMP_SP_REG];

  if (sp!=0)
  {
  #warning bring up hack: err needs a context
  #if 0
  	if(tcb_ptr == 0)
  	{
  	  /* Use tcb_ptr from rex_core if available, otherwise get current task tcb_ptr */
  	   tcb_ptr = rex_self();
  	}
  
    #ifdef FEATURE_REX_OPAQUE_TCB_APIS
    rex_task_get_attr(tcb_ptr, &attr);
    rex_task_attr_get_stack_attr(&attr, &stack_start_ptr, &stack_size);
    #else
    stack_start_ptr=tcb_ptr->stack_limit;
    stack_size=tcb_ptr->stack_size;
    #endif //FEATURE_REX_OPAQUE_TCB_APIS
  #endif 

	/* Get the address of the end of the stack for this task, and make sure
       we don't read beyond it.*/
	stack_end = (uint32)(stack_start_ptr) + stack_size;

  /*Copy the stack.  Only do the copy if the stack pointer is within the 
     stack for the TCB*/
  if((sp < (uint32*)stack_end) && (sp > (uint32*)stack_start_ptr))
  {
	  WRITE_BUF("Stack Dump (from 0x%08x):\n",(unsigned int)sp);
	  WRITE_BUF("Addr        Data\n");
	  for(i=0; (i<ERR_STACK_DUMP_SIZE) && (sp<(uint32*)stack_end); i++)
	  {
		  WRITE_BUF("0x%08x  0x%08x\n",(unsigned int)sp,(unsigned int)*sp);
		  sp++;
	  }
	}
	else
	{
	  WRITE_BUF("Stack pointer (0x%08x) out of range of current tcb stack limits\n",(unsigned int)sp);
	  WRITE_BUF("Stack data not dumped.\n");
	}
  }
  else
  {
	/* No stack poitner recorded. This could be due to a dog timeout (no rex_core),
	   or some other error that bypassed the saving of registers. */
	WRITE_BUF("No stack pointer recorded (or SP is NULL)...stack data not dumped.\n");
  }

  WRITE_BUF("\n");
  return;
}

/*===========================================================================
FUNCTION ERR_LOG_OS (Static)

DESCRIPTION
  Function to log information relevant to the OS being used.
  Currently assumes REX/L4 and accesses minimal information from the TCB.

============================================================================*/
static void err_log_os(void)
{
#warning bring up hack: err needs a context
#if 0
    rex_tcb_type *tcb_ptr = (rex_tcb_type*)coredump.os.tcb_ptr;
  #ifdef FEATURE_REX_OPAQUE_TCB_APIS
    char rex_task_name[REX_TASK_NAME_LEN+1];
  #endif //FEATURE_REX_OPAQUE_TCB_APIS
  
    if(tcb_ptr == 0)
    {
  	  /* Use tcb_ptr from coredump if available, otherwise get current task tcb_ptr */
  	  tcb_ptr = rex_self();
    }
  #ifdef FEATURE_REX_OPAQUE_TCB_APIS
    rex_get_task_name(tcb_ptr, rex_task_name, sizeof(rex_task_name), NULL);
    WRITE_BUF("REX_TCB ptr: 0x%08x\n",tcb_ptr);
    WRITE_BUF("tcb.task_name: %s\n",rex_task_name);
  #else
    WRITE_BUF("REX_TCB ptr: 0x%08x\n",tcb_ptr);
    WRITE_BUF("tcb.task_name: %s\n",tcb_ptr->task_name);
  #endif //FEATURE_REX_OPAQUE_TCB_APIS
  
    WRITE_BUF("\n");
#endif
  WRITE_BUF("NO CONTEXT\n");
}

/*===========================================================================
FUNCTION ERR_LOG_ARCH (Static)

DESCRIPTION
  Function to log information relevant to CPU architecture being used.
  Currently suppots only ARM.
============================================================================*/
static void err_log_arch(void)
{
  WRITE_BUF("Coredump ARCH type is: %s\n",
    arch_coredump_type_label[coredump.arch.type]);
  /* Call helper functions to print registers and stack */
  err_log_registers();
  err_log_stack();
}

/*===========================================================================
FUNCTION ERR_LOG_ERR (Static)

DESCRIPTION
  Function to log general information relevant to the error being handled.
  Includes information such as error line number and file, time of crash, etc.
============================================================================*/
//extern const char mob_sw_rev[];
static void err_log_err(void)
{
//  uint32 up_time;
//  uint32 up_h, up_m, up_s;

  if(coredump.err.filename[0]!=NULL)
  {
	WRITE_BUF("Error in file %s, line %u\n",
      coredump.err.filename, (unsigned int)coredump.err.linenum);
  }
  if(coredump.err.param[0]!=NULL)
  {
	WRITE_BUF("Error message: %s\n", coredump.err.message);
  }

  /* Report time information */
#warning bring up hack: err has no Julian time, uptime, mob_sw_rev
#if 0
  #ifndef FEATURE_ERR_Q6_CLIENT
  {
    time_julian_type sys_time;
    
    time_get_julian(&sys_time);
    WRITE_BUF("Time of crash (m-d-y h:m:s): %02d-%02d-%d %d:%02d:%02d\n",sys_time.month,sys_time.day,sys_time.year,sys_time.hour,sys_time.minute,sys_time.second);
  }
  #endif

  up_time=time_get_uptime_secs();
  up_h=up_time/3600;
  up_m=(up_time-(up_h*3600))/60;
  up_s=up_time-(up_h*3600)-(up_m*60);
  WRITE_BUF("Uptime (h:m:s): %d:%02d:%02d\n",up_h,up_m,up_s);

  /* Report Build ID */
  WRITE_BUF("Build ID: %s\n", mob_sw_rev);
#endif

  WRITE_BUF("\n");
  return;
}

/*===========================================================================
FUNCTION ERR_LOG_HEADER (Static)

DESCRIPTION
  Function to place any needed header information that should go at the
  top of the log report. 
============================================================================*/
static void err_log_header(void)
{
  WRITE_BUF("ERR crash log report.  Version %d.\n\n",EXT_STORE_VERSION);
  return;
}

/*===========================================================================
FUNCTION ERR_LOG_PRINT_TO_BUF (Static)

DESCRIPTION
  This function is for giving external functions access to print to the log
  report.  It is static and only accessible if passed as a pointer by the
  errlog code to the external function.

  String passed in will only be logged if there is room in the buffer.

PARAMETERS
  char *buf      Pointer to buffer

RETURNS 
  None.

============================================================================*/
static void err_log_print_to_buf(char * buf)
{
  WRITE_BUF(“%s”, buf);
  return;
}

/*===========================================================================
FUNCTION ERR_LOG_INIT

DESCRIPTION
  Initialize buffer to be used for writing log information.
  Calling the function subsequent times will reset the location and size
  of the buffer.

PARAMETERS
  char *buff     Pointer to buffer
  uint32 size    Size of buffer 

RETURNS 

============================================================================*/
void err_log_init(char *buff, uint32 size)
{
  if( buff != 0 )
  {
    // buf_base_ptr = buff; // Base address of buffer 
    buf_ptr = buff;      // Current position in buffer
    buf_size = size;     // Total size of buffer (bytes)
    buf_unused = size;   // Total unused size of buffer (bytes)
    buf_init=TRUE;
  }
}

/*===========================================================================
FUNCTION ERR_GENERATE_LOG

DESCRIPTION
  This is the function called by error services when a log report needs to
  be generated.

  err_log_init() must be called prior to calling this function.

PARAMETERS
  None

RETURNS 
  uint32          Number of bytes written to buffer.

============================================================================*/
uint32 err_generate_log(void)
{
  if ((buf_init!=TRUE) || (buf_unused==0))
  {
	return 0;
  }

  err_log_header();
  err_log_err();
  err_log_os();
  err_log_arch();
  #ifdef DOG_HAS_CRASH_REPORT_API
  dog_crash_report(&err_log_print_to_buf);
  #endif
  
  /* Use err_log_print_to_buf here instead of WRITE_BUF macro
   * to remove compiler warning when err_log_print_to_buf not
   * otherwise referenced. It works the same. */
  err_log_print_to_buf("End of crash log report.\n");

  return (buf_size - buf_unused);
}
#endif
