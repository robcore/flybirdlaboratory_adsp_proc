/*========================================================================*/
/** @file EliteSvc_Util.h

This file contains structures and message ID's for communication between
Elite services.
*/
/*===========================================================================
NOTE: The @brief description above does not appear in the PDF. 
      The description that displays in the PDF is located in the
      Elite_mainpage.dox file. Contact Tech Pubs for assistance.
===========================================================================*/

/*======================================================================
Copyright (c) 2009-2010, 2013-2014 Qualcomm Technologies, Inc.  All rights reserved.
Confidential and Proprietary - Qualcomm Technologies, Inc.  
Export of this technology or software is regulated
by the U.S. Government, Diversion contrary to U.S. law prohibited.
===========================================================================*/

/*========================================================================
Edit History

when       who     what, where, why
--------   ---     -------------------------------------------------------
09/05/14   sw      (Tech Pubs) Merged Doxygen markup/comments from 2.4.
03/20/13   sw      (Tech Pubs) Updated Doxygen markup/comments for 2.0.
10/28/10   sw      (Tech Pubs) Edited/added Doxygen comments and markup.
7/26/09    mwc      Created file.

========================================================================== */
#ifndef ELITESVC_UTIL_H
#define ELITESVC_UTIL_H


/* =======================================================================
INCLUDE FILES FOR MODULE
========================================================================== */
#include "qurt_elite.h"
#include "EliteMsg.h"

#ifdef __cplusplus
extern "C" {
#endif //__cplusplus


/* -----------------------------------------------------------------------
** Global definitions/forward declarations
** ----------------------------------------------------------------------- */

/* -----------------------------------------------------------------------
** Type definitions
** ----------------------------------------------------------------------- */

/** @ingroup elite_svc_datatypes
  Defines a function pointer signature for a message handler function.

  @datatypes
  elite_msg_any_t

  @param[in] pInstance   Pointer to the instance structure of the calling 
                         service.
  @param[in] pMsg        Pointer to the message to process.

  @return
  Depends on the message, which is implicitly agreed upon between the caller
  and callee.

  @dependencies
  None.
 */
typedef ADSPResult (*elite_svc_msg_handler_func) (void* /*pInstance*/, elite_msg_any_t* /*pMsg*/);

/****************************************************************************
** Service utility functions.
*****************************************************************************/

/** @ingroup elitesvc_func_process_cmd_q
  Loops through the command queue and calls the handler for each function. This
  function finds the handler function via the table lookup from the message ID.

  @datatypes
  elite_svc_handle_t \n
  #elite_svc_msg_handler_func

  @param[in] pInstance   Pointer to the instance of the calling service, to
                         be passed to the handler.
  @param[in] pHandle     Pointer to the service handle of the calling service.
  @param[in] pHandler    Handler function lookup table of the calling service.
  @param[in] handler_table_size  Number of elements in the lookup table.

  @return
  None.

  @dependencies
  None.
*/
ADSPResult elite_svc_process_cmd_queue(void* pInstance, elite_svc_handle_t *pHandle,
   elite_svc_msg_handler_func pHandler[], uint32_t handler_table_size);

/** @ingroup elitesvc_unsupported
  Returns the ADSP_UNSUPPORTED error code. This function can be referenced by
  a service's handler table for unsupported messages.

  @datatypes
  elite_msg_any_t

  @param[in] pInstance   Pointer to the instance structure of the calling
                         service.
  @param[in] pMsg        Pointer to the message that needs handling.

  @return
  ADSP_UNSUPPORTED.

  @dependencies
  None.
*/
ADSPResult elite_svc_unsupported (void* pInstance, elite_msg_any_t* pMsg);

/** @ingroup elitesvc_func_return_success
  Referenced by a service's handler table to simply return an ADSP_EOK
  error code for a message.

  @datatypes
  elite_msg_any_t

  @param[in] pInstance   Pointer to the instance structure of the calling
                         service.
  @param[in] pMsg        Pointer to the message that needs handling.

  @return
  ADSP_EOK.

  @dependencies
  None.
*/
ADSPResult elite_svc_return_success (void* pInstance, elite_msg_any_t* pMsg);

/** @ingroup elitesvc_func_destroy_data_q
  Flushes and destroys a data queue. This function is called by typical service
  destructors.      

  @datatypes
  qurt_elite_queue_t (refer to @xhyperref{Q5,[Q5]})

  @param[in] pDataQ    Pointer to the data queue of the service.

  @return
  None.

  @dependencies
  None.
*/ /* Q5 = Hex Multimedia: QuRT_Elite API Interface Spec for 2.4 (80-NF769-7) */
void elite_svc_destroy_data_queue (qurt_elite_queue_t* pDataQ);

/** @ingroup elitesvc_func_destroy_cmd_q
  Flushes and destroys a command queue. This function is called by typical
  service destructors.

  @datatypes
  qurt_elite_queue_t (refer to @xhyperref{Q5,[Q5]})

  @param[in] cmdQ    Pointer to the command queue of the service.

  @return
  None.

  @dependencies
  None.
*/
void elite_svc_destroy_cmd_queue (qurt_elite_queue_t* cmdQ);

/** @ingroup elitesvc_func_free_buf_q
  Awaits the return of outstanding buffers to their queue, and then frees the
  buffers but does not destroy the buffer queue. 

  This function is to be called when needed to free buffers but 
  not destroy the queue 

  @datatypes
  qurt_elite_queue_t (refer to @xhyperref{Q5,[Q5]})

  @param[in] bufQ    Pointer to the buffer queue descriptor.
  @param[in] nBufs   String identifier, which is required to unlink the queue.

  @return
  None.

  @dependencies
  None.
*/
void elite_svc_free_buffers_in_buf_queue (qurt_elite_queue_t* bufQ, int nBufs);


/** @ingroup elitesvc_func_destroy_buf_q
  Awaits the return of outstanding buffers to their queue, and then destroys
  the buffer queue, thus freeing the buffers.

  This function is to be called by typical service destructors.

  @datatypes
  qurt_elite_queue_t (refer to @xhyperref{Q5,[Q5]})

  @param[in] bufQ     Pointer to the buffer queue descriptor.
  @param[in] nBufs    String identifier, which is required to unlink the queue.

  @return
  None.

  @dependencies
  None.
*/
void elite_svc_destroy_buf_queue (qurt_elite_queue_t* bufQ, int nBufs);

/** @ingroup elitesvc_func_deinit_cmd_q
  Flushes and destroys a command queue. This function is to be used when
  qurt_elite_queue_init() is used to create the command queue.

  @note1hang For information on qurt_elite_queue_init(), refer to
             @xhyperref{Q5,[Q5]}.

  This function is to be called by typical service destructors.

  @datatypes
  qurt_elite_queue_t (refer to @xhyperref{Q5,[Q5]})

  @param[in] cmdQ    Pointer to the queue descriptor.

  @return
  None.

  @dependencies
  None.
*/
void elite_svc_deinit_cmd_queue (qurt_elite_queue_t* cmdQ);

/** @ingroup elitesvc_func_deinit_buf_q
  Awaits the return of outstanding buffers to their queue, and then destroys
  the buffer queue, freeing the buffers. This function is to be used when
  qurt_elite_queue_init is used to create the buffer queue.

  @note1hang For information on qurt_elite_queue_init(), refer to
             @xhyperref{Q5,[Q5]}.

  This function is to be called by typical service destructors.

  @datatypes
  qurt_elite_queue_t (refer to @xhyperref{Q5,[Q5]})

  @param[in] bufQ     Pointer to the buffer queue descriptor.
  @param[in] nBufs    String identifier, which is required to unlink the queue.

  @return
  None.

  @dependencies
  None.
*/
void elite_svc_deinit_buf_queue (qurt_elite_queue_t* bufQ, int nBufs);


/** @ingroup elitesvc_func_deinit_data_q
  Flushes and destroys a data queue. This function is to be used when
  qurt_elite_queue_init() was used to create the data queue.

  @note1hang For information on qurt_elite_queue_init(), refer to
             @xhyperref{Q5,[Q5]}.

  This function is to be called by typical service destructors.

  @datatypes
  qurt_elite_queue_t (refer to @xhyperref{Q5,[Q5]})

  @param[in] pDataQ     Pointer to the data queue descriptor.

  @return
  None.

  @dependencies
  None.
*/
void elite_svc_deinit_data_queue (qurt_elite_queue_t* pDataQ);

/** @ingroup elitesvc_func_send_ack
  Forms and sends an acknowledgment to a command if the command has requested
  an acknowledgment.

  If the command did not request an acknowledgment, this function does nothing.
  This means the function can be called without checking whether an
  acknowledgment is required.

  @datatypes
  elite_msg_any_t

  @param[in] pMsg     Pointer to the message that may need an acknowledgment.
  @param[in] result   Error status to report in the acknowledgment.

  @return
  None.

  @dependencies
  None.
*/
void elite_svc_send_ack (elite_msg_any_t *pMsg, ADSPResult result);

/** @ingroup elitesvc_func_wait_ack
  Called after sending a message to await an acknowledgment.

  @datatypes
  elite_msg_any_t

  @param[in] pMsg    Pointer to the message that may need an acknowledgment.

  @return
  Error status is returned in the acknowledgment.

  @dependencies
  None.
*/
ADSPResult elite_svc_wait_for_ack(elite_msg_any_t *pMsg);

/** @ingroup elitesvc_func_wait_ack_get_msg
  Called after sending a message to await an acknowledgment. On a successful
  return, the response contains the new message, and it might contain a payload.

  @datatypes
  elite_msg_any_t

  @param[in]  pMsg        Pointer to the message that may need an acknowledgment.
  @param[out] pResponse   Pointer to the response message that is sent as an
                          acknowledgment.

  @return
  Error status is returned in the acknowledgment.

  @dependencies
  None.
*/
ADSPResult elite_svc_wait_for_ack_and_get_msg(elite_msg_any_t *pMsg, elite_msg_any_t *pResponse);


#ifdef __cplusplus
}
#endif //__cplusplus

#endif // #ifndef ELITESVC_UTIL_H

