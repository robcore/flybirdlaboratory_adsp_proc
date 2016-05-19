/*======================================================================
Copyright (c) 2010-2011, 2013-2014 Qualcomm Technologies, Inc.
All Rights Reserved.
Confidential and Proprietary - Qualcomm Technologies, Inc.
======================================================================== */
/**
@file qurt_elite_bufmgr.h
*/
/** @weakgroup weakf_qurt_elite_bufmgr_descr
  This utility library is used to manage a set of preallocated
  buffers among multiple clients. The client is responsible for allocating the
  memory. The only constraint is the managed buffers must be in multiples of
  2 bytes, and they must be a minimum of 8 bytes. Any number of each size
  buffer can be managed.

  The protocol for the client to use this buffer manager is:
  -# Form an array of 32 integers, where the value of each a[n] is the number
     of buffers of size 2^n to be managed by the buffer manager.
  -# Call #QURT_ELITE_BUFMGR_REQUIRED_SIZE, passing in this array. \n
     This macro does a sanity check on the array for validity, and it returns
     the memory block size required to populate the buffer manager.
  -# Allocate the memory block from the specified memory pool.
  -# Call qurt_elite_bufmgr_create() with the allocated memory and 
    configuration array.
  -# When a buffer is needed, call qurt_elite_bufmgr_poll_for_buffer() along
     with a specified size.\n
     The function returns a node corresponding to the smallest available buffer
     that can accommodate the requested size. The node is 8 bytes: \n
       - The first 4 bytes are the pointer to the buffer.
       - The second 4 bytes are the qurt_elite_queue_t, where the node must
         be returned when the buffer is consumed.
  -# When the client finishes with a buffer, call qurt_elite_queue_push_back()
     to return the node to its queue.
  -# When completely finished, call qurt_elite_bufmgr_destroy() and free the
     memory block.

  @note1hang Clients are trusted to not corrupt the nodes that are given to
             them and then returned to the buffer manager queues.

  @note1hang Currently, ADSP_ENEEDMORE is returned if a buffer is requested but
             none are available. There is no blocking, and there is no setup
             for a signal on a free buffer. @newpage
*/
/*========================================================================
Edit History

$Header: //components/rel/avs.adsp/2.6.1/elite/qurt_elite/inc/qurt_elite_bufmgr.h#3 $

when       who     what, where, why
--------   ---     -------------------------------------------------------
09/05/14    sw     (Tech Pubs) Merged Doxygen comments from 2.4; modified
                   discussion above for 2.6.
03/25/13   sw      (Tech Pubs) Edited Doxygen comments/markup for 2.0.
05/03/11   leo     (Tech Pubs) Edited doxygen comments and markup.
02/04/10   mwc     Created file.
03/09/10   brs     Edited for doxygen-to-latex process.
========================================================================== */

#ifndef QURT_ELITE_BUFMGR_H
#define QURT_ELITE_BUFMGR_H
#include "qurt_elite_types.h"
#include "qurt_elite_channel.h"

#ifdef __cplusplus
extern "C" {
#endif //__cplusplus

/** @addtogroup qurt_elite_bufmgr
@{ */

/*--------------------------------------------------------------*/
/* Macro definitions                                            */
/* -------------------------------------------------------------*/

/** Metadata for freed buffers.

  Upon being freed, all buffers managed by the buffer manager require extra
  metadata to help return the buffers to their proper place in the buffer
  manager, and to detect double free scenarios.
*/
#define QURT_ELITE_BUFMGR_METADATA_SIZE ((uint32_t)(4 * sizeof(uint32_t)))

/** Macro that computes the memory size needed for a specified set of buffers
  to be managed.

  Each input argument <i>bn</i> (b0, b1, etc.) is the number of buffers of
  size 2^n that are required.
*/
#define QURT_ELITE_BUFMGR_REQUIRED_SIZE(b0, b1, b2, b3, b4, b5, b6, b7, b8, b9, b10, \
   b11, b12, b13, b14, b15, b16, b17, b18, b19, b20, b21, b22, b23, b24, b25, b26, \
   b27, b28, b29, b30, b31) \
   ((b0)  * (QURT_ELITE_BUFMGR_METADATA_SIZE + (1 << 0)) + \
   (b1)  * (QURT_ELITE_BUFMGR_METADATA_SIZE + (1 << 1)) + \
   (b2)  * (QURT_ELITE_BUFMGR_METADATA_SIZE + (1 << 2)) + \
   (b3)  * (QURT_ELITE_BUFMGR_METADATA_SIZE + (1 << 3)) + \
   (b4)  * (QURT_ELITE_BUFMGR_METADATA_SIZE + (1 << 4)) + \
   (b5)  * (QURT_ELITE_BUFMGR_METADATA_SIZE + (1 << 5)) + \
   (b6)  * (QURT_ELITE_BUFMGR_METADATA_SIZE + (1 << 6)) + \
   (b7)  * (QURT_ELITE_BUFMGR_METADATA_SIZE + (1 << 7)) + \
   (b8)  * (QURT_ELITE_BUFMGR_METADATA_SIZE + (1 << 8)) + \
   (b9)  * (QURT_ELITE_BUFMGR_METADATA_SIZE + (1 << 9)) + \
   (b10) * (QURT_ELITE_BUFMGR_METADATA_SIZE + (1 << 10)) + \
   (b11) * (QURT_ELITE_BUFMGR_METADATA_SIZE + (1 << 11)) + \
   (b12) * (QURT_ELITE_BUFMGR_METADATA_SIZE + (1 << 12)) + \
   (b13) * (QURT_ELITE_BUFMGR_METADATA_SIZE + (1 << 13)) + \
   (b14) * (QURT_ELITE_BUFMGR_METADATA_SIZE + (1 << 14)) + \
   (b15) * (QURT_ELITE_BUFMGR_METADATA_SIZE + (1 << 15)) + \
   (b16) * (QURT_ELITE_BUFMGR_METADATA_SIZE + (1 << 16)) + \
   (b17) * (QURT_ELITE_BUFMGR_METADATA_SIZE + (1 << 17)) + \
   (b18) * (QURT_ELITE_BUFMGR_METADATA_SIZE + (1 << 18)) + \
   (b19) * (QURT_ELITE_BUFMGR_METADATA_SIZE + (1 << 19)) + \
   (b20) * (QURT_ELITE_BUFMGR_METADATA_SIZE + (1 << 20)) + \
   (b21) * (QURT_ELITE_BUFMGR_METADATA_SIZE + (1 << 21)) + \
   (b22) * (QURT_ELITE_BUFMGR_METADATA_SIZE + (1 << 22)) + \
   (b23) * (QURT_ELITE_BUFMGR_METADATA_SIZE + (1 << 23)) + \
   (b24) * (QURT_ELITE_BUFMGR_METADATA_SIZE + (1 << 24)) + \
   (b25) * (QURT_ELITE_BUFMGR_METADATA_SIZE + (1 << 25)) + \
   (b26) * (QURT_ELITE_BUFMGR_METADATA_SIZE + (1 << 26)) + \
   (b27) * (QURT_ELITE_BUFMGR_METADATA_SIZE + (1 << 27)) + \
   (b28) * (QURT_ELITE_BUFMGR_METADATA_SIZE + (1 << 28)) + \
   (b29) * (QURT_ELITE_BUFMGR_METADATA_SIZE + (1 << 29)) + \
   (b30) * (QURT_ELITE_BUFMGR_METADATA_SIZE + (1 << 30)) + \
   (b31) * (QURT_ELITE_BUFMGR_METADATA_SIZE + (1 << 31)))


/* -----------------------------------------------------------------------
** Global definitions/forward declarations
** ----------------------------------------------------------------------- */

/* Forward declaration. */
typedef struct qurt_elite_bufbin_t qurt_elite_bufbin_t;

/* Forward declaration. */
typedef struct qurt_elite_bufmgr_node_t qurt_elite_bufmgr_node_t;

/* Forward declaration. */
typedef struct qurt_elite_bufmgr_t qurt_elite_bufmgr_t;

/** Node that represents a buffer. When clients request a buffer from the
    buffer manager, this node is provided.
 */
struct qurt_elite_bufmgr_node_t {
   QURT_ELITE_ALIGN(qurt_elite_queue_t*, 8) pReturnQ;
   /**< Queue to which this buffer must be returned. */

   void*                   pBuffer;
   /**< Pointer to the buffer. @newpage */
};


/**
  Creates the buffer manager. This function also performs a sanity check on
  the sizes of the requested set of buffers.

  @param[in]  nBufSizeArray Pointer to an array of 32 integers. \n
                            nBufSizeArray[n] is the number of buffers of size
                            2^n bytes to be managed by the buffer manager. The
                            first three elements must be 0 because 8 is the
                            minimum supported buffer size.
  @param[in]  pStartAddr    Pointer to the starting address of the memory for
                            the buffer pool the caller must allocate before
                            calling this function to create the buffer manager
                            described by nBufSizeArray.
  @param[in]  size          Size of the buffer pool in bytes.
  @param[out] ppBufMgr      Double pointer to the buffer manager created if
                            this function returns ADSP_EOK.

  @return
  ADSP_EBADPARAM -- Invalid nBufSizeArray (e.g., a request for buffers smaller
                    than 8 bytes).
  @par
  ADSP_EOK -- nBufSizeArray is valid. The buffer manager is created and its
              pointer is put in the ppBufMgr parameter.
  @par
  For more information, refer to @xhyperref{Q2,[Q2]}.

  @dependencies
  None. @newpage
*/ /* Q2 = Hex Multimedia: Elite API Interface Spec for 2.4 (80-NF770-13) */
ADSPResult qurt_elite_bufmgr_create(const uint32_t* nBufSizeArray, char* pStartAddr, uint32_t size, qurt_elite_bufmgr_t **ppBufMgr);

/**
  Takes the address of a managed buffer, looks up the metadata, and pushes the
  address to the home queue.

  @param[in] pBuf  Pointer to the buffer manager instance.

  @return
  An indication of success (0) or failure (nonzero).

  @dependencies
  The buffer manager must have been created and polled for a buffer before
  calling this function.
*/
ADSPResult qurt_elite_bufmgr_return_buf(void *pBuf);

/**
  Waits for all managed buffers to be returned to their queues and
  then destroys all resources.

  @param[in] pBufMgr  Pointer to the buffer manager instance.

  @return
  None.

  @dependencies
  The buffer manager must have been created before calling this function. @newpage
*/
void qurt_elite_bufmgr_destroy(qurt_elite_bufmgr_t *pBufMgr);

/**
  Requests a buffer from the manager. If a buffer of adequate size is
  available, a node is returned with pointers to the buffer and the buffer's
  return queue.

  @datatypes
  qurt_elite_bufmgr_node_t

  @param[in]  pBufMgr       Pointer to the buffer manager instance.
  @param[in]  nDesiredSize  Number of bytes needed in the requested buffer.
  @param[out] pNode         Returned node that points to the buffer and
                            return queue.
  @param[out] pnActualSize  Pointer to the actual size of the buffer that is
                            becoming available.

  @return
  ADSP_ENEEDMORE -- No buffers of adequate size are available. \n
  ADSP_EOK -- A buffer was found and is becoming available.
  @par
  For more information, refer to @xhyperref{Q2,[Q2]}.

  @dependencies
  The buffer manager must have been created before calling this function. @newpage
*/
ADSPResult qurt_elite_bufmgr_poll_for_buffer(qurt_elite_bufmgr_t *pBufMgr, int nDesiredSize,
   qurt_elite_bufmgr_node_t *pNode, int* pnActualSize);

/**
  Determines if a buffer was allocated by the buffer manager.

  @datatypes
  qurt_elite_queue_t

  @param[in] bufmgr_ptr    Pointer to the buffer manager instance.
  @param[in]  return_q_ptr  Pointer to the return queue of the buffer.
  @param[in] buf_ptr       Pointer to the buffer.
 
  @return
  TRUE  -- The buffer was allocated by the buffer manager. \n
  FALSE -- The buffer was not allocated by the buffer manager.
  @par
  For more information, refer to @xhyperref{Q2,[Q2]}.

  @dependencies
  The buffer manager must have been created before calling this function.
  @newpage
*/
bool_t qurt_elite_is_bufmgr_node(qurt_elite_bufmgr_t *bufmgr_ptr,
                                 qurt_elite_queue_t* return_q_ptr, 
                                 void* buf_ptr);

/** @} */ /* end_addtogroup qurt_elite_bufmgr */

#ifdef __cplusplus
}
#endif //__cplusplus

#endif // #ifndef QURT_ELITE_BUFMGR_H

