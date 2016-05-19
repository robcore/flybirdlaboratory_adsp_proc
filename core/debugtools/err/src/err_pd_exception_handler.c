/*====*====*====*====*====*====*====*====*====*====*====*====*====*====*====*

                        M A I N   M O D U L E

GENERAL DESCRIPTION
  This module contains the AMSS exception handler

EXTERNALIZED FUNCTIONS
  None

INITIALIZATION AND SEQUENCING REQUIREMENTS
  None

Copyright(c) 2014 by Qualcomm Technologies, Incorporated. All Rights Reserved.
*====*====*====*====*====*====*====*====*====*====*====*====*====*====*====*/

/*===========================================================================

                        EDIT HISTORY FOR MODULE

$Header: //components/rel/core.adsp/2.6.1/debugtools/err/src/err_pd_exception_handler.c#1 $

when       who     what, where, why
--------   ---     ----------------------------------------------------------
08/27/14   din     Replaced snprintf with mutex free calls.
07/31/14   din     File created to support Error on User PD.
===========================================================================*/

#include <stdio.h>
#include "comdef.h"
#include "stringl/stringl.h"
#include "msg.h"
#include "qurt_event.h"
#include "erri.h"
#include "err_qdi_client.h"
#include "tms_utils.h"

#define SWI_NUM_DIVIDE_BY_0     0xD0  /* SWI # used in __default_signal_handler
                                         for DivideByZero exception */
/* The following offset is calculated out from SP(stack pointer) to the saved 
   pointer/address in stack, which points to the next instruction after the
   instruction of <blx __rt_sdiv>. */
/* Note: === This might change if __rt_sdiv() changes. === */
#define SWI_DIVISION_OFFSET     0x14

typedef enum {
  EXCP_UNKNOWN,
  EXCP_SWI,
  EXCP_UNDEF_INST,
  EXCP_MIS_ALIGN,
  EXCP_PAGE_FAULT,
  EXCP_EXE_FAULT,
  EXCP_DIV_BY_0,
  EXCP_MAX_NUM
} exception_type;

char  exception_info[EXCP_MAX_NUM][14] = {
  "    :Excep  ",
  "    :No SWI ",
  "    :Undef  ",
  "    :MisAlgn",
  "    :PFault ",
  "    :XFault ",
  "    :DivBy0 ",
};

#define           LEN_QXDM_DBG_MSG  80
char              qxdm_dbg_msg[LEN_QXDM_DBG_MSG];

extern coredump_type coredump;
void err_exception_handler( void );
extern void err_fatal_handler( void );
extern void err_copy_tcm_data_into_coredump(void);

#define MAX_FAILURE_COUNT 10

/*===========================================================================
FUNCTION has_err_fatal_occured

DESCRIPTION
  Checks if exception is raised because of error fatal

===========================================================================*/

static boolean has_err_fatal_occured
(
  unsigned int badva,
  unsigned int cause
)
{
   if ( QURT_EXCEPT_EXIT != cause ||
     ( ERR_GET_ERR_TYPE_FROM_EXCEPTION_ARG(badva) != ERR_TYPE_ERR_FATAL ) )
   {
     return FALSE;
   }

   return TRUE;
} /* has_err_fatal_occured */


/*===========================================================================
FUNCTION err_exception_handler

DESCRIPTION
  Handle IPC from L4 Kernel when exceptions occur.

===========================================================================*/
void err_exception_handler(void)
{
  unsigned int     tid, ip, sp, badva, cause;
  union arch_coredump_union *p_regs=&coredump.arch.regs;
  unsigned int failure_count=0;
  
  for (;;)
  {
    /* Register self as Exception_Handler. */
    tid = qurt_exception_wait(&ip, &sp, &badva, &cause);

    if (-1==tid)
    {
      if ( sizeof(qxdm_dbg_msg) <= tms_utils_fmt(qxdm_dbg_msg, sizeof(qxdm_dbg_msg),
        "Failed to register with qurt_reg_error_handler: tid=%x", tid))
      {
        MSG(MSG_SSID_TMS, MSG_LEGACY_ERROR,"Failed to copy failure result in qxdm_dbg_msg ");
      }
      MSG_1(MSG_SSID_TMS, MSG_LEGACY_FATAL,"Failed to register with qurt_reg_error_handler: tid=%x", tid);
      failure_count++;
      if(failure_count >= MAX_FAILURE_COUNT)
      {
        ERR_FATAL("Failed to register with qurt_reg_error_handler",0,0,0);
      }
      continue;
    }

    /* There are four ways to reach here 
     * 1. Exception Caused by Main thread. ( Handled by if Part )
     * 2. Non recoverable exception raised by island exception handler. ( Handled by if Part )
     * 3. Error fatal in Main image. ( Handled by else Part )
     * 4. Error fatal in uImage. ( Handled by else Part )
     * */

    if ( !has_err_fatal_occured(badva, cause) )
    {
      /* enter critical section */
      err_fatal_lock();
    
      p_regs->name.pc = ip;
      p_regs->name.sp = sp;
      p_regs->name.badva = badva;
      p_regs->name.ssr = cause;
    
      if ( sizeof(qxdm_dbg_msg) <= tms_utils_fmt(qxdm_dbg_msg, sizeof(qxdm_dbg_msg),
        "ExIPC: Exception recieved tid=%x inst=%x", tid, ip) )
      {
        MSG(MSG_SSID_TMS, MSG_LEGACY_ERROR,"Failed to copy exception in qxdm_dbg_msg ");
      }

      /* Inform PFR reason to root PD */
      err_qdi_invoke_inform_pfr(strnlen(qxdm_dbg_msg, LEN_QXDM_DBG_MSG), qxdm_dbg_msg);

      /* Cannot hold other cores for User PD */
      //ERR_FATAL_ENTER_SINGLE_THREADED_MODE();
      /* perform higher level error logging - no return */
      err_fatal_jettison_core ( 0, exception_info[EXCP_UNKNOWN], "Exception detected", 0, 0, 0);
    }
    else 
    {
      err_copy_tcm_data_into_coredump();
      
      /* Inform PFR reason to root PD */
      err_qdi_invoke_inform_pfr(strnlen(coredump.err.message, ERR_LOG_MAX_MSG_LEN),coredump.err.message);
      
      err_fatal_handler();
    }
  }
} /* end of err_exception_handler */



