/*=============================================================================
  @file sns_rh_mr_uimg.c

  This file implements the Message Router module of Request Handler task
  that executes in microImage

*******************************************************************************
* Copyright (c) 2014 Qualcomm Technologies, Inc.  All Rights Reserved.
* Qualcomm Technologies Proprietary and Confidential.
********************************************************************************/

/* $Header: //components/rel/ssc.adsp/2.6.1/smgr/src/sns_rh_mr_uimg.c#2 $ */
/* $DateTime: 2015/02/04 16:31:36 $ */
/* $Author: pwbldsvc $ */

/*============================================================================
  EDIT HISTORY FOR FILE

  when        who  what, where, why
  ----------  ---  -----------------------------------------------------------
  2015-02-03  pn   Only SMR_NO_ERR and SMR_CONN_BUSY_ERR mean indication is sent
  2014-06-16  pn   Unshared sns_rh_uimg
  2014-06-05  vy   Added a workaround to run in Virtio
  2014-05-02  aj   Replaced QMI with SMR
  2014-04-29  pn   Initial version

============================================================================*/
/*----------------------------------------------------------------------------
 * Include Files
 * -------------------------------------------------------------------------*/
#include "sns_memmgr.h"
#include "sns_rh_mr.h"
#include "sns_usmr.h"

/*----------------------------------------------------------------------------
 * Preprocessor Definitions and Constants
 * -------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
 * Type Declarations
 * -------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
 *  Variables
 * -------------------------------------------------------------------------*/
sns_rh_mr_connection_s  sns_rh_connection_list[SNS_RH_MR_MAX_CONNECTIONS];

/*----------------------------------------------------------------------------
 * Macro
 * -------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------
 * Function Declarations and Documentation
 * -------------------------------------------------------------------------*/
/*===========================================================================

  FUNCTION:   sns_rh_mr_send_indication

===========================================================================*/
/*!
  @brief This function populates message header and sends the given indication
   over the given connection

  @param[i]  conn_handle - connection over which to send indication
  @param[i]  ind_msg_ptr - the indication message to send
  @param[i]  msg_id      - indication ID
  @param[i]  len         - length of the indication body
  @param[i]  free_me     - whether to free the indication memory
 
  @return   true if indication was sent or will be sent
 */
/*=========================================================================*/
bool sns_rh_mr_send_indication(
   const void*  conn_handle,
   void*        ind_msg_ptr,
   uint16_t     msg_id, 
   uint16_t     len,
   bool         free_me)
{
  smr_err err = SMR_XPORT_ERR;
  uint32_t i = (uint32_t)conn_handle;

  if ( (i < ARR_SIZE(sns_rh_connection_list)) && sns_rh_connection_list[i].is_valid )
  {
    err = smr_service_send_ind(sns_rh_connection_list[i].client_handle, 
                               msg_id, (void *)ind_msg_ptr, len);
  }

  if ( free_me )
  {
    SNS_OS_ANY_FREE(ind_msg_ptr);
  }
  return (err == SMR_NO_ERR || err == SMR_CONN_BUSY_ERR) ? true : false;
}

