/*=============================================================================

                 err_qdi.c

GENERAL DESCRIPTION
   Implements QDI layer for Err that goes into main image

INITIALIZATION AND SEQUENCING REQUIREMENTS
   None.

Copyright (c) 2014
by QUALCOMM Technologies Incorporated.  All Rights Reserved.

=============================================================================*/


/*=============================================================================

                        EDIT HISTORY FOR MODULE

 This section contains comments describing changes made to the module.
 Notice that changes are listed in reverse chronological order.
 
$Header: //components/rel/core.adsp/2.6.1/debugtools/err/src/err_qdi.c#1 $ 
$DateTime: 2014/10/16 12:45:40 $ $Author: pwbldsvc $

when       who     what, where, why
--------   ---     ------------------------------------------------------------
08/27/14   din     Replaced snprintf with mutex free calls.
07/31/14   din     File created to support Error on User PD.

=============================================================================*/


/*****************************************************************************/
/*                           INCLUDE FILES                                   */
/*****************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <stringl/stringl.h>
#include "err_qdi.h"
#include "pd_mon_restart.h"
#include "err.h"
#include "tms_utils.h"


/*****************************************************************************/
/*                         DATA DECLARATIONS                                 */
/*****************************************************************************/
static err_qdi_s err_qdi_pfr[ERR_QDI_MAX_PDS];
static err_qdi_opener_s err_qdi_clients[ERR_QDI_MAX_PDS];
static uint32 err_qdi_pd_ctr;

qurt_mutex_t err_qdi_mutex;

/* MACRO for locking/unlocking the qmutex*/
#define ERR_QDI_LOCK()  \
   qurt_rmutex_lock(&err_qdi_mutex); 
  
#define ERR_QDI_FREE()  \
   qurt_rmutex_unlock(&err_qdi_mutex); 

#define ERR_QDI_MUTEX_INIT() \
   qurt_rmutex_init ( &err_qdi_mutex );

static boolean pd_restart_enabled;

/*****************************************************************************/
/*                      FUNCTION DECLARATIONS                                */
/*****************************************************************************/
int err_qdi_invoke(int client_handle,
                          qurt_qdi_obj_t *pobj,
                          int method,
                          qurt_qdi_arg_t a1,
                          qurt_qdi_arg_t a2,
                          qurt_qdi_arg_t a3,
                          qurt_qdi_arg_t a4,
                          qurt_qdi_arg_t a5,
                          qurt_qdi_arg_t a6,
                          qurt_qdi_arg_t a7,
                          qurt_qdi_arg_t a8,
                          qurt_qdi_arg_t a9);


/*=============================================================================

FUNCTION ERR_QDI_RELEASE

DESCRIPTION
 Releases the Qdi object that corresponding to a process that got destroyed

DEPENDENCIES
  None

RETURN VALUE
 None

SIDE EFFECTS
  None.

=============================================================================*/
void err_qdi_release(qurt_qdi_obj_t *obj)
{
   err_qdi_opener_s *clntobj = (err_qdi_opener_s *)obj;
  
   err_qdi_pfr[clntobj->process_idx].err_initiated = FALSE;
   err_qdi_pfr[clntobj->process_idx].initialized = FALSE;
   free(err_qdi_pfr[clntobj->process_idx].pfr);

} /* err_qdi_release */


/*=============================================================================

FUNCTION ERR_QDI_SEND_PID_INFO

DESCRIPTION
 Sends PID info to Root PD during err_qdi_client_init

DEPENDENCIES
  None

RETURN VALUE
 ERR_QDI_SUCCESS - for success
 ERR_QDI_FAIL    - for failure

SIDE EFFECTS
  None

=============================================================================*/
err_qdi_e err_qdi_send_pid_info(int client_handle, uint32 process_idx, uint32 pid)
{
  err_qdi_s            *dataobj;
  
  dataobj = &err_qdi_pfr[process_idx];
  
  if(dataobj->initialized == FALSE)
  {
    //TODO : ADD err_fatal
    return ERR_QDI_NOT_INITIALIZED;
  } 

  dataobj->pid = pid;
  
  return ERR_QDI_SUCCESS;

} /* err_qdi_send_pid_info */
	
/*=============================================================================

FUNCTION ERR_QDI_INFORM_PFR

DESCRIPTION
 Communicates PFR to Root PD in case of error/exceptions in User PD

DEPENDENCIES
  None

RETURN VALUE
 ERR_QDI_SUCCESS - for success
 ERR_QDI_FAIL    - for failure

SIDE EFFECTS
  None

=============================================================================*/
err_qdi_e err_qdi_inform_pfr
(
   int client_handle, 
   uint32 process_idx, 
   uint32 pfr_len, 
   char * pfr 
)
{
  int                  result;
  err_qdi_s            *dataobj;
  
  dataobj = &err_qdi_pfr[process_idx];
  
  if(dataobj->initialized == FALSE)
  {
    //TODO : ADD err_fatal
    return ERR_QDI_NOT_INITIALIZED;
  }

  /* Not Checking for err_initialized. If this routine is called, 
   * pfr would be udpated */

  dataobj->pfr_len = pfr_len > ERR_QDI_PFR_LEN ? ERR_QDI_PFR_LEN : pfr_len ;

  memset(dataobj->pfr,0,ERR_QDI_PFR_LEN);

  result = qurt_qdi_copy_from_user(client_handle, dataobj->pfr, pfr, dataobj->pfr_len);

  if (result)
  {
    //TODO : ADD err_fatal
    return ERR_QDI_INVALID_PARAMETERS;
  }

  dataobj->err_initiated = TRUE;

  return ERR_QDI_SUCCESS; 

} /* err_qdi_inform_pfr */

/*=============================================================================

FUNCTION ERR_QDI_CB_POPULATE_AUX_MSG

DESCRIPTION
 Generates Dynamic message with PD info to be poluated in aux msg.
 This function is a callback called from ERR_FATAL_DYNAMIC.

DEPENDENCIES
  None

RETURN VALUE
 None

SIDE EFFECTS
 None

=============================================================================*/
void err_qdi_cb_populate_aux_msg
(
  char* const buf, 
  const uint16 buf_len, 
  const uint32 idx
)
{
  err_qdi_s            *dataobj;
  char                 *temp = buf;

  dataobj = &err_qdi_pfr[idx];
  if ( buf_len <= tms_utils_fmt(temp, buf_len,"PID %u : %s ", 
                  (unsigned int )dataobj->pid, dataobj->pfr ))
  {
    MSG(MSG_SSID_TMS, MSG_LEGACY_ERROR,"Failed to populate aux message in buf ");
  }

} /* err_qdi_cb_populate_aux_msg */

/*=============================================================================

FUNCTION ERR_QDI_ERR_HANDLING_DONE

DESCRIPTION
 Communicates to Root PD that handling routine on User PD is complete.

DEPENDENCIES
  None

RETURN VALUE
 ERR_QDI_SUCCESS - for success
 ERR_QDI_FAIL    - for failure

SIDE EFFECTS
  None

=============================================================================*/
err_qdi_e err_qdi_err_handling_done(int client_handle, uint32 process_idx)
{
  err_qdi_s            *dataobj;

  dataobj = &err_qdi_pfr[process_idx];
  
  if(dataobj->initialized == FALSE)
  {
    //TODO : ADD err_fatal
    return ERR_QDI_NOT_INITIALIZED;
  } 

  if ( dataobj->err_initiated != TRUE )
  {
    //PFR not communicated
  }

  if ( !pd_restart_enabled )
  {
    /* This branch will not return */
    ERR_FATAL_DYNAMIC_MSG(" USER PD crashed, see coredump.aux_msg for more details", 
		            err_qdi_cb_populate_aux_msg, process_idx);

  }
  else
  {
    MSG_SPRINTF_2(MSG_SSID_TMS, MSG_LEGACY_HIGH, " PID %u crashed : %s", 
                  (unsigned int )dataobj->pid, dataobj->pfr );
  }

  //TODO : Add dynamic message to report error over QXDM.
  
  return ERR_QDI_SUCCESS;

} /* err_qdi_err_handling_done */

/*=============================================================================

FUNCTION ERR_QDI_OPEN

DESCRIPTION
 Creates err driver object for the client and initializes required details.

DEPENDENCIES
  None

RETURN VALUE
 QURT_EOK if the driver obj is defined and set correctly.

SIDE EFFECTS
  None

=============================================================================*/
int err_qdi_open(int client_handle)
{
   err_qdi_opener_s *clntobj;
   err_qdi_s        *dataobj;
   uint32 temp,idx;
   
   ERR_QDI_LOCK();
   if(err_qdi_pd_ctr == ERR_QDI_MAX_PDS)
   {
      ERR_QDI_FREE();
      ERR_FATAL("Max Processes %d reached", err_qdi_pd_ctr, 0, 0);
      return -1;
   }
   idx = err_qdi_pd_ctr++;
   ERR_QDI_FREE();
   
   dataobj                   = &err_qdi_pfr[idx];
   clntobj                   = &err_qdi_clients[idx];
   clntobj->qdiobj.invoke    = err_qdi_invoke;
   clntobj->qdiobj.refcnt    = QDI_REFCNT_INIT;
   clntobj->qdiobj.release   = err_qdi_release;
   clntobj->process_idx      = idx;

   dataobj->pfr              = malloc(ERR_QDI_PFR_LEN);
   
   if( dataobj->pfr == NULL )
   {
      return -1;
   }
   dataobj->err_initiated = FALSE;
   dataobj->initialized = TRUE;

   temp = strlen(ERR_QDI_INITIAL_STRING);
   
   strlcpy( dataobj->pfr, ERR_QDI_INITIAL_STRING, 
	    (temp > ERR_QDI_PFR_LEN ? ERR_QDI_PFR_LEN : temp) );
   
   return qurt_qdi_handle_create_from_obj_t(client_handle, &clntobj->qdiobj);

} /* err_qdi_open */

/*=============================================================================

FUNCTION ERR_QDI_INVOKE

DESCRIPTION
 This function contains the switch which maps to all methods

DEPENDENCIES
  None

RETURN VALUE


SIDE EFFECTS
  None

=============================================================================*/
int err_qdi_invoke(int client_handle,
                          qurt_qdi_obj_t *pobj,
                          int method,
                          qurt_qdi_arg_t a1,
                          qurt_qdi_arg_t a2,
                          qurt_qdi_arg_t a3,
                          qurt_qdi_arg_t a4,
                          qurt_qdi_arg_t a5,
                          qurt_qdi_arg_t a6,
                          qurt_qdi_arg_t a7,
                          qurt_qdi_arg_t a8,
                          qurt_qdi_arg_t a9)
{
   err_qdi_opener_s *clntobj = (err_qdi_opener_s *)pobj;
   unsigned int      process_idx = clntobj->process_idx;
   
   switch(method)
   {
      case QDI_OPEN: 
         return err_qdi_open(client_handle);
      
      case ERR_QDI_SEND_PID_INFO:
	 return err_qdi_send_pid_info(client_handle, process_idx, a1.num);
			 
      case ERR_QDI_INFORM_PFR:  
         return err_qdi_inform_pfr(client_handle, process_idx, a1.num, a2.ptr );

      case ERR_QDI_ERR_HANDLING_DONE:  
         return err_qdi_err_handling_done(client_handle, process_idx);

      default:
         return qurt_qdi_method_default(client_handle, pobj, method,
                                     a1, a2, a3, a4, a5, a6, a7, a8, a9);
   }
} /* err_qdi_invoke */


/*=============================================================================

FUNCTION ERR_QDI_INIT

DESCRIPTION
 Registers with QDI Framework for ERR QDI
 
DEPENDENCIES
  None

RETURN VALUE
 None

SIDE EFFECTS
  None

=============================================================================*/

static qurt_qdi_obj_t err_qdi_opener_obj;

void err_qdi_init 
(
  void
) 
{
   qurt_qdi_obj_t *p_opener = &err_qdi_opener_obj;
  
   /* Initialize the mutex here */
   ERR_QDI_MUTEX_INIT();

   p_opener->invoke = err_qdi_invoke;
   p_opener->refcnt = QDI_REFCNT_INIT;
   p_opener->release = err_qdi_release;
   qurt_qdi_register_devname(ERR_DRIVER_NAME, p_opener);

   if (pd_mon_restart_dalcfg_check() )
   {
     pd_restart_enabled = TRUE;
   }
   
} /* err_qdi_init */
