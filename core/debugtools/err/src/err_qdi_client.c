/*=============================================================================

                err_qdi_client.c

GENERAL DESCRIPTION
      ERR QDI Client Process Code that goes to main image

EXTERNAL FUNCTIONS

INITIALIZATION AND SEQUENCING REQUIREMENTS
   None.

Copyright (c) 2014
by QUALCOMM Technologies Incorporated.  All Rights Reserved.

=============================================================================*/

/*=============================================================================

                        EDIT HISTORY FOR MODULE

 This section contains comments describing changes made to the module.
 Notice that changes are listed in reverse chronological order.


$Header: //components/rel/core.adsp/2.6.1/debugtools/err/src/err_qdi_client.c#1 $ 
$DateTime: 2014/10/16 12:45:40 $ $Author: pwbldsvc $

when       who     what, where, why
--------   ---     ------------------------------------------------------------
07/31/14   din     Added qdi calls for err on User PD.
=============================================================================*/

#include <stdio.h>
#include <stdlib.h>
#include "err_qdi_client.h"
#include "err.h"

static int err_qdi_client_handle = -1;
boolean err_qdi_client_initialized = FALSE;

/*===========================================================================

FUNCTION    ERR_QDI_CLIENT_INIT

DESCRIPTION
  Initialize the err client qdi service.

DEPENDENCIES
  None.

RETURN VALUE
  
SIDE EFFECTS
  None

===========================================================================*/
void err_qdi_client_init(void) 
{
 
   uint32 err_qdi_client_pid = qurt_getpid();
    
   err_qdi_client_handle = qurt_qdi_open(ERR_DRIVER_NAME);
   
   if(err_qdi_client_handle < 0)
   {
     ERR_FATAL("err_qdi_client_init :qdi_open failed\n", 0, 0, 0);
     return;
   }

   err_qdi_client_initialized = TRUE;

   err_qdi_invoke_send_pid_info(err_qdi_client_pid);

}  /* err_qdi_client_init */


/*===========================================================================

FUNCTION    ERR_QDI_CLIENT_IS_INITIALIZED

DESCRIPTION
  Initialize the err client qdi service.

DEPENDENCIES
  None.

RETURN VALUE
  TRUE/FALSE
  
SIDE EFFECTS
  None

===========================================================================*/
boolean err_qdi_client_is_initialized(void) 
{
 
   return err_qdi_client_initialized;

}  /* err_qdi_client_is_initialized */



/*===========================================================================

FUNCTION    ERR_QDI_INVOKE_SEND_PID_INFO

DESCRIPTION
  Sends Pid info after initialization.

DEPENDENCIES
  None.

RETURN VALUE
  
SIDE EFFECTS
  None

===========================================================================*/

err_qdi_e err_qdi_invoke_send_pid_info
(
  uint32                        pid
)
{
  return qurt_qdi_handle_invoke(err_qdi_client_handle, ERR_QDI_SEND_PID_INFO,pid);

} /* err_qdi_invoke_send_pid_info*/

/*===========================================================================

FUNCTION    ERR_QDI_INVOKE_INFORM_PFR

DESCRIPTION
  Sends PFR after a crash . Sends the info in expception handler.

DEPENDENCIES
  None.

RETURN VALUE
  
SIDE EFFECTS
  None

===========================================================================*/

err_qdi_e err_qdi_invoke_inform_pfr
(
  uint32                        pfr_len,
  char *                        pfr
)
{
  return qurt_qdi_handle_invoke(err_qdi_client_handle, ERR_QDI_INFORM_PFR, pfr_len, pfr );

} /* err_qdi_invoke_inform_pfr */

/*===========================================================================

FUNCTION    ERR_QDI_INVOKE_ERR_HANDLING_DONE

DESCRIPTIONT
  Tells QDI on ROOT PD that err completion routine on User PD has completed.
  Root PD checks if PD restart is enabled. If so, it returns. Otherwise, 
  it brings the system down.

DEPENDENCIES
  None.

RETURN VALUE
  
SIDE EFFECTS
  None

===========================================================================*/

err_qdi_e err_qdi_invoke_err_handling_done(void)
{
  return qurt_qdi_handle_invoke(err_qdi_client_handle, ERR_QDI_ERR_HANDLING_DONE);

} /* err_qdi_invoke_err_handling_done */

