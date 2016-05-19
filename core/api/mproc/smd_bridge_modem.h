#ifndef SMD_BRIDGE_MODEM_H
#define SMD_BRIDGE_MODEM_H

/*---------------------------------------------------------------------------
   SMD_BRIDGE_MODEM.H  - Modem processor specific smd bridge header
---------------------------------------------------------------------------*/

/**
  @file smd_bridge_modem.h
*/


/* NOTE: For the output PDF generated using Doxygen and Latex, all file and group 
         descriptions are maintained in the SMD_mainpage file. To change any of the 
         the file/group text for the PDF, edit the SMD_mainpage file, or contact 
         Tech Pubs.
*/


/*--------------------------------------------------------------------------
Copyright (c) 2009-2010 Qualcomm Technologies Incorporated.
All Rights Reserved.
Qualcomm Confidential and Proprietary.
---------------------------------------------------------------------------*/

/*===========================================================================

                           EDIT HISTORY FOR FILE

$Header: //components/rel/core.adsp/2.6.1/api/mproc/smd_bridge_modem.h#1 $

when       who     what, where, why
--------   ---     ---------------------------------------------------------- 
08/12/10   sw     (Tech Pubs) Edited/added Doxygen comments and markup.
02/19/10   rs      Changed return type of smd_bridge_receive_cmd_modem to support 
                   sync and async close callbacks
02/16/10   tl/esh  Added Doxygen tags
12/29/09   rs      Removed SMD Bridge RPC server on APPS
04/06/09   jlk     initial version
===========================================================================*/



/*===========================================================================
                        INCLUDE FILES
===========================================================================*/
#include "smd_bridge_internal.h"

/** @addtogroup smd_bridge_modem 
@{ */

/*===========================================================================
                   PUBLIC FUNCTION DECLARATIONS
===========================================================================*/

/*===========================================================================
FUNCTION      smd_bridge_receive_cmd_modem
===========================================================================*/
/**
  Receives a command from an SMD Bridge client.

  SMD Bridge clients send command requests to the server through an RPC call. 
  Each command is remotely executed and the status is returned.

  The supported commands are:
  - SMD_BRIDGE_CMD_CONNECT -- Opens an SMD Bridge port.
  - SMD_BRIDGE_CMD_DISCONNECT -- Closes an SMD Bridge port.
  - SMD_BRIDGE_CMD_IOCTL -- Contains I/O control commands. 

  @param[in] param    Contains all of the information for the command.
  @param[in] data     Extra data used in callbacks.

  @return 
  smd_bridge_remote_cmd_ret_type -- Status of the command.


  @dependencies
  None.
  
  @sideeffects
  The RPC blocks the processor until the command is completed on the remote 
  processor.\n
  The client shall close its side of the SMD Bridge if there is a failure while 
  opening the port (i.e., the client shall check the return status of the 
  function).
*/
/*=========================================================================*/
smd_bridge_remote_cmd_ret_type smd_bridge_receive_cmd_modem
(
  smd_bridge_remote_cmd_param_type param,
  void                             *data
);
/*~ FUNCTION smd_bridge_receive_cmd_modem */

/*===========================================================================
FUNCTION      smd_bridge_register_server_modem
===========================================================================*/
/**
  Registers a callback-based SMD Bridge server for remote processors that have 
  no RPC server support.

  @param[in] server_cb     Pointer to the SMD Bridge server callback.
  @param[in] proc_id       Processor identifier.
  @param[in] data          Extra data used for server registration.

  @return       
  TRUE  -- Successful registration.\n
  FALSE -- Registration failure.
  
  @dependencies
  None.

  @sideeffects   
  The RPC blocks the processor until the command is completed on the remote 
  processor.
*/
/*=========================================================================*/
boolean smd_bridge_register_server_modem
(
  smd_bridge_server_receive_f_type  server_cb,
  uint32                            proc_id,
  void                              *data
);
/*~ FUNCTION smd_bridge_register_server_modem */

/*===========================================================================
FUNCTION      smd_bridge_register_forward_callback_modem
===========================================================================*/
/**
  Registers a forward callback function for remote processors that have no RPC 
  server support.

  @param[in] forward_cb    Pointer to the SMD Bridge forward callback function.
  @param[in] proc_id       Processor identifier.
  @param[in] data          Extra data used for forward callback registration.

  @return       
  TRUE  -- Successful registration.\n 
  FALSE -- Registration failure.

  @dependencies
  None.
  
  @sideeffects   
  The RPC blocks the processor until the command is completed on the remote 
  processor.
*/
/*=========================================================================*/
boolean smd_bridge_register_forward_callback_modem
(
  smd_bridge_forward_callback_f_type forward_cb,
  uint32                             proc_id,
  void                               *data
);
/*~ FUNCTION smd_bridge_register_forward_callback_modem */

/*===========================================================================
FUNCTION      smd_bridge_forward_callback_modem
===========================================================================*/
/**
  Forwards a callback invocation from SMD Bridge clients. The callback is a 
  result of an event in the SMD Bridge port.

  @param[in] bridge_id    SMD Bridge port identifier.
  @param[in] callback     Type of callback (SERVER, CLOSE, or IOCTL).
  @param[in] data         Extra data used by the callback.

  @return       
  TRUE  -- Successful callback execution.\n 
  FALSE -- Callback execution failure.

  @dependencies
  None.

  @sideeffects   
  The RPC blocks the processor until the command is completed on remote processor.
*/
/*=========================================================================*/
boolean smd_bridge_forward_callback_modem
(
  uint32                   bridge_id,
  smd_bridge_callback_type callback, 
  void                     *data
);
/*~ FUNCTION smd_bridge_forward_callback_modem */

/** @} */ /* end_addtogroup smd_bridge_modem */

#endif /* SMD_BRIDGE_MODEM_H */
