#ifndef SLIMBUSSAT_H
#define SLIMBUSSAT_H
/*
===========================================================================

FILE:         SlimBusSat.h

DESCRIPTION:  This file contains the SLIMbus satellite function prototypes 
              for the SLIMbus core driver.

===========================================================================

                             Edit History

$Header: //components/rel/core.adsp/2.6.1/buses/slimbus/src/common/SlimBusSat.h#1 $

when       who     what, where, why
--------   ---     --------------------------------------------------------
03/21/13   MJS     Support for standalone satellite hardware configuration.
02/05/13   dj      Fix Code analysis warnings
10/26/12   MJS     Add interrupt disable function.
09/21/12   MJS     Add interrupt enable function.
08/20/12   MJS     Correct bogus NULL check for master driver.
06/13/12   MJS     Support for standlone satellite low-power management.
05/01/12   MJS     Fix Klocwork warning.
12/11/11   MJS     Remove references to DAL.
05/25/11   MJS     Add separate satellite hardware init function.
11/01/10   MJS     Initial revision.

===========================================================================
             Copyright (c) 2010, 2011, 2012, 2013 QUALCOMM Technologies Incorporated.
                    All Rights Reserved.
                  QUALCOMM Proprietary/GTDR
===========================================================================
*/

#include SLIMBUS_OS_H


/**
 * @brief Checks if the driver binary supports satellite-specific logic 
 *
 * This function checks whether the compiled driver binary supports 
 * satellite-specific logic
 * 
 * @return TRUE if satellite-specfic logic is supported, FALSE otherwise 
 */
extern SBBOOL SlimBus_IsSatSupported( void );

/**
 * @brief Process a satellite-specific received message
 *
 * Process a satellite-specific received message 
 * 
 * @param[in] pDevCtxt  Pointer to the device context
 * @param[in] length  Length of the message
 * @param[in] data  First word of the received message
 * @param[in] pDataBuf  Pointer to the second word in the 
 *       received message buffer
 * 
 * @return SB_SUCCESS on success, error code on error 
 */
extern SBResult SlimBus_ProcessSatRxMsg
(
  SlimBusDevCtxt *pDevCtxt,
  uint32 length,
  uint32 data,
  uint32 *pDataBuf
);

/**
 * @brief Wait for acknowledgement response from the master 
 *        driver
 *
 * This function waits for an acknowledgement response from the 
 * master driver 
 * 
 * @param[in] pClientCtxt  Pointer to the client context
 * @param[in] pEventNode  Pointer to event node structure used 
 *       for completion notification
 * @param[in] TID  Transaction ID
 * @param[in] puMarker  Pointer to location to store ack marker 
 *       data
 * 
 * @return SB_SUCCESS on success, error code on error 
 */
_IRQL_requires_(DISPATCH_LEVEL)
extern SBResult SlimBus_WaitForMasterAck
(
  SlimBusClientCtxt *pClientCtxt,
  SlimBusEventNodeType *pEventNode,
  uint8 TID,
  uint32 *puMarker
);

/**
 * @brief Query the master driver for a logical address
 *
 * This function queries the remote master driver for a Slimbus 
 * native device logical address 
 * 
 * @param[in] pClientCtxt  Pointer to the client context
 * @param[in] pEA  Pointer to the enumeration address to query
 * @param[in] uEASize  Size of the enumeration address
 * @param[out] pLA  Pointer to location to store the logical 
 *       address that was looked up
 * 
 * @return SB_SUCCESS on success, error code on error 
 */
extern SBResult SlimBus_QueryRemoteLogicalAddr
(
  SlimBusClientCtxt *pClientCtxt,
  const uint8 *pEA,
  uint32 uEASize,
  SlimBusLogicalAddrType * pLA
);

/**
 * @brief Check for standalone satellite mode and perform
 *        standalone satellite initialization if the mode is
 *        detected
 *
 * This function checks for standalone satellite mode and 
 * performs the standalone satellite initialization if the mode 
 * is detected 
 * 
 * @param[in] pDevCtxt  Pointer to the DAL device context
 */
extern void SlimBus_CheckInitStandaloneSat(SlimBusDevCtxt *pDevCtxt);

/**
 * @brief Perform satellite-specific device driver 
 *        initialization
 *
 * This function performs satellite-specific device driver 
 * initialization 
 * 
 * @param[in] pDevCtxt  Pointer to the device context
 * 
 * @return SB_SUCCESS on sucess, error code on error 
 */
extern SBResult SlimBus_DeviceInitSat(SlimBusDevCtxt *pDevCtxt);

/**
 * @brief Send a sequence of messages that would need to be 
 *        acked by the master
 *
 * This function sends a sequence of messages that would need to
 * be acked by the master, depending on the message FIFO type. 
 * If the driver is a master driver or the message FIFO does not 
 * support acknowledgement (because it is an internal FIFO) then
 * the function will not trigger or wait for acknowledgement. 
 * 
 * @param pClientCtxt[in]  Pointer to the client context
 * @param pMsgFifo[in]  Pointer to the message FIFO
 * @param pBuf[in]  Pointer to the message buffer that needs 
 *                  acknowledgement
 * @param TID[in]  Transaction ID
 * 
 * @return SB_SUCCESS on success, error code otherwise
 */
SLIMBUS_INLINE SBResult SlimBus_SendMasterAckedMsg
(
  SlimBusClientCtxt *pClientCtxt,
  SlimBusMsgFifoType *pMsgFifo,
  uint32 *pBuf,
  uint8 TID
)
{
  SlimBusEventNodeType *pEvent = 
    SlimBus_EnqueueMsgEvent(pMsgFifo, pClientCtxt, pBuf, pClientCtxt->hClientEvent);
  pMsgFifo->sendBufFcn(SB_GET_PDEVCTXT(pClientCtxt->hDevCtxt), pMsgFifo);
  return SlimBus_WaitForMasterAck(pClientCtxt, pEvent, TID, NULL);
}

#endif /* SLIMBUSSAT_H */

