#ifndef SMD_BRIDGE_INTERNAL_H
#define SMD_BRIDGE_INTERNAL_H

/*---------------------------------------------------------------------------
   SMD_BRIDGE_INTERNAL.H - Definition of smd_bridge interprocessor interface
---------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------
     Copyright  2009-2011 Qualcomm Technologies Incorporated. 
     All rights reserve.
---------------------------------------------------------------------------*/

/*===========================================================================

                           EDIT HISTORY FOR FILE

$Header: //components/rel/core.adsp/2.6.1/api/mproc/smd_bridge_internal.h#1 $

when       who     what, where, why
--------   ---     ---------------------------------------------------------- 
04/28/11   bt      Resolve compiler warning in SMD_BRIDGE_TO_SMD_SIO_ID macro.
02/16/10   tl/esh  Added Doxygen tags
02/10/10   rs      + Added function for SMD Bridge remote registration 
                   + Changed return type of smd_bridge_server_receive_f_type to
                     support sync and async close callbacks
12/29/09   rs      Removed SMD Bridge RPC server on APPS
12/24/08   jlk     Initial version
===========================================================================*/

/** \defgroup smd_bridge SMD Bridge
 * \ingroup SMD
 *
 * The Shared Memory Driver Bridge allows SIO clients on one processor to
 * access SIO devices on another processor.
 */

/** \defgroup smd_bridge_internal SMD-Bridge Internal
 * \ingroup smd_bridge
 *
 * This module contain the interface definition, data types, commands, and
 * definitions of SMD Bridge.
 *
 * Among the various definitions, this module also includes the RPC
 * meta-comments to create the data types used in remote procedure calls
 * between SMD Bridge server and clients.
 *
 * Note: This header file shall only be include in smd_brige_apps.h and
 * smd_bridge_modem.h.
 *
 */
/*@{*/

/*===========================================================================
                        INCLUDE FILES
===========================================================================*/
#include "sio.h"

/*===========================================================================
                      DATA DEFINITIONS
===========================================================================*/

/** \name SMD Bridge Version Definitions
 *
 * SMD Bridge checks for version in order to:
 * - Ensure data structures are compatible
 * - The number of bridges do not exceed its capacity, note that for each bridge
 *   there exists one data and one control port
 * - SIO/SMD bridge mappings are correct
 */
/*@{*/

/** SMD Bridge version. */
#define SMD_BRIDGE_VERSION 0x00000001

/** Maximum number of SMD Bridges. */
#define SMD_BRIDGE_MAX_BRIDGES  (7 * 2) 

/** SIO/SMD Bridge mappings. */
#define SIO_MINOR_SMD_BRIDGE0  (SIO_MINOR_SMD_MAX + 1)
#define SIO_MINOR_SMD_BRIDGE1  (SIO_MINOR_SMD_MAX + 2)
#define SIO_MINOR_SMD_BRIDGE2  (SIO_MINOR_SMD_MAX + 3)
#define SIO_MINOR_SMD_BRIDGE3  (SIO_MINOR_SMD_MAX + 4)
#define SIO_MINOR_SMD_BRIDGE4  (SIO_MINOR_SMD_MAX + 5)
#define SIO_MINOR_SMD_BRIDGE5  (SIO_MINOR_SMD_MAX + 6)
#define SIO_MINOR_SMD_BRIDGE6  (SIO_MINOR_SMD_MAX + 7)
#define SIO_MINOR_SMD_BRIDGE7  (SIO_MINOR_SMD_MAX + 8)
#define SIO_MINOR_SMD_BRIDGE8  (SIO_MINOR_SMD_MAX + 9)
#define SIO_MINOR_SMD_BRIDGE9  (SIO_MINOR_SMD_MAX + 10)
#define SIO_MINOR_SMD_BRIDGE10 (SIO_MINOR_SMD_MAX + 11)
#define SIO_MINOR_SMD_BRIDGE11 (SIO_MINOR_SMD_MAX + 12)
#define SIO_MINOR_SMD_BRIDGE12 (SIO_MINOR_SMD_MAX + 13)
#define SIO_MINOR_SMD_BRIDGE13 (SIO_MINOR_SMD_MAX + 14)

/** Number of entries in the SMD Bridge clients info table. */
#define SMD_BRIDGE_MAX_ENTRIES        2 * SMD_BRIDGE_MAX_BRIDGES
/*@}*/

/*===========================================================================
                      MACRO DEFINITIONS
===========================================================================*/

/** Maps SMD Bridge Id to SIO Port Id. */
#define SMD_BRIDGE_TO_SMD_SIO_ID(major_id, bridge_id)                   \
  (sio_port_id_type)DEVICE_ID(major_id, ((SIO_MINOR_SMD_MAX + 1) + bridge_id))

/*===========================================================================
                      ENUMERATED TYPES
===========================================================================*/
/** Commands supported by the SMD Bridge server. */
typedef enum
{
  /** Opens bridge port. */
  SMD_BRIDGE_CMD_CONNECT = 0,

  /** Closes bridge port. */
  SMD_BRIDGE_CMD_DISCONNECT,

  /** I/O control command. */
  SMD_BRIDGE_CMD_IOCTL
}smd_bridge_remote_cmd_type;

/** Callback types supported by the SMD Bridge. */
typedef enum
{
  /** Server callback. */
  SMD_BRIDGE_SERVER_CALLBACK = 0,

  /** Close callback. */
  SMD_BRIDGE_CLOSE_CALLBACK,

  /** IOCTL callback. */
  SMD_BRIDGE_IOCTL_CALLBACK
}smd_bridge_callback_type;

/** SMD Bridge remote command status */
typedef enum
{
  SMD_BRIDGE_CMD_SUCCEEDED = 0,
  SMD_BRIDGE_CMD_INVOKE_CB,
  SMD_BRIDGE_CMD_FAILED,
}smd_bridge_remote_cmd_ret_type;

/*===========================================================================
                      TYPE DEFINITIONS
===========================================================================*/

/** SMD Bridge version of an sio_open_type struct (ensures compatibility with different versions of SIO. */
typedef struct smd_bridge_open
{
  /** Stream mode type. */
  sio_stream_mode_type  stream_mode;

  /** Bit-rate for reception. */
  sio_bitrate_type      rx_bitrate;

  /** Bit-rate for transmission. */
  sio_bitrate_type      tx_bitrate;

  /** SIO port which needs to be used. */
  sio_port_id_type      port_id;

  /** Indicates if tail character used. */
  boolean               tail_char_used;

  /** Tail character (if used). */
  byte                  tail_char;

  /* TX flow control method. */
  sio_flow_ctl_type     tx_flow;

  /** RX flow control method. */
  sio_flow_ctl_type     rx_flow;

  /** Indicates if this is a control port. */
  boolean               control;         
}smd_bridge_open_type;

/** SMD Bridge version of an sio_open_type struct (bundles the command and parameter fields. */
typedef struct smd_bridge_ioctl_cmd{
   /** SIO IOCTl command. */
   sio_ioctl_cmd_type   cmd;

   /** SIO IOCTL parameter. */
   sio_ioctl_param_type *param; /*~ FIELD smd_bridge_ioctl_cmd.param 
                                 POINTER DISC smd_bridge_ioctl_cmd_type.cmd */
}smd_bridge_ioctl_cmd_type;

/** Callback function pointer type used in SMD Bridge close functions. */
typedef void (*smd_bridge_close_cb_f_type) (void *);

/** SMD Bridge command sent from client to server. */
typedef struct smd_bridge_remote_cmd_param{
 /** Command. */
 smd_bridge_remote_cmd_type cmd;

 /** Id number of the port. */
 uint32 bridge_id;

 /** SIO major Id for SMD ports to the client processor. */
 uint32 proc_major_id;

 /** Reserved for future use. */
 uint32 rsvd;

 /** Union of possible arguments to server calls so that a single call can
   be made. */
 union{
  smd_bridge_open_type      open_struct;  /*~ CASE SMD_BRIDGE_CMD_CONNECT 
                               smd_bridge_remote_cmd_param.param.open_struct */
  smd_bridge_ioctl_cmd_type ioctl_struct; /*~ CASE SMD_BRIDGE_CMD_IOCTL 
                              smd_bridge_remote_cmd_param.param.ioctl_struct */
  uint8                     dummy;        
                         /*~ DEFAULT smd_bridge_remote_cmd_param.param.dummy */
 }param; /*~ FIELD smd_bridge_remote_cmd_param.param DISC 
                                             smd_bridge_remote_cmd_param.cmd */
}smd_bridge_remote_cmd_param_type;

/** Pointer to SMD Bridge server receive command function. */
typedef smd_bridge_remote_cmd_ret_type (*smd_bridge_server_receive_f_type)
                      (smd_bridge_remote_cmd_param_type,
                       void *);
/*~ CALLBACK smd_bridge_server_receive_f_type 
    POINTER
    ONERROR  err_fatal
*/

/** Pointer to SMD Bridge server forwrad callback function. */
typedef boolean (*smd_bridge_forward_callback_f_type)
                      ( uint32,
                        smd_bridge_callback_type,
                        void *);
/*~ CALLBACK smd_bridge_forward_callback_f_type 
    POINTER
    ONERROR  err_fatal
*/

/** Pointer to SMD Bridge register server function. */
typedef boolean (*smd_bridge_register_server_f_type)
                      (smd_bridge_server_receive_f_type,
                       void*);
/*~ CALLBACK smd_bridge_register_server_f_type 
    POINTER
    ONERROR  err_fatal
*/

/** Pointer to a SMD Bridge register fowrad callback function. */
typedef boolean (*smd_bridge_register_forward_callback_f_type)
                      (smd_bridge_forward_callback_f_type,
                       void *);
/*~ CALLBACK smd_bridge_register_forward_callback_f_type 
    POINTER
    ONERROR  err_fatal
*/                      

/*===========================================================================
FUNCTION      smd_bridge_server_init
===========================================================================*/
/*!
@brief        Initializes the SMD Bridge server and its static variables.

              This function should only be called in smd_bridge_client_driver_init()

@return       None

@sideeffect   None
*/
/*=========================================================================*/
void smd_bridge_server_init(void);

/*===========================================================================
FUNCTION      smd_bridge_remote_registration
===========================================================================*/
/*!
@brief        Initializes the SMD Bridge server and its static variables.

              This function should only be called in smd_bridge_client_driver_init()
 *      * SMD task is running
 *      * RPC mechanism is running
 *
@return       None

@sideeffect   None
*/
/*=========================================================================*/
void smd_bridge_remote_registration(void);

/*===========================================================================
FUNCTION      smd_bridge_get_port_id_from_stream_id
===========================================================================*/
/*!
@brief        Gets the smd sio port id of a given SIO stream and returns the
              corresponding sio port id.
@param[in]    stream_id   SIO stream identifier

@return       The SMD SIO port identifier

@sideeffect   None
*/
/*=========================================================================*/
uint32 smd_bridge_get_port_id_from_stream_id(sio_stream_id_type stream_id);

/*@}*/

#endif /* SMD_BRIDGE_INTERNAL_H */
