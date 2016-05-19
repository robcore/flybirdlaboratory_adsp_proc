
/*
===========================================================================

FILE:   I2cULog.c

DESCRIPTION:
    This file contains functions for I2c logging  driver
 
===========================================================================

        Edit History

$Header: //components/rel/core.adsp/2.6.1/buses/i2c/src/logs/I2cUlog.c#1 $

When     Who    What, where, why
-------- ---    -----------------------------------------------------------
02/22/13 LK     Added Buffer logging.
11/02/11 sg     Created

===========================================================================
        Copyright c 2011 - 2013 Qualcomm Technologies Incorporated.
            All Rights Reserved.
            Qualcomm Proprietary/GTDR

===========================================================================
*/

#include "ULogFront.h"
#include "I2cLog.h"

#include "QupLog.h"
#include "DALSys.h"

static I2CLOG_DevType *pLogListHead = NULL;

QUPLOG_DEV_IMP_HANDLE GetQupLogRegReadHandle(uint32 uDevAddr);
QUPLOG_DEV_IMP_HANDLE GetQupLogRegWriteHandle(uint32 uDevAddr);



QupLogSvcType _gQupLog = {GetQupLogRegReadHandle, GetQupLogRegWriteHandle};

const char *pTmpI2cLogName = "I2C_LOG";

/** @brief Searches for a log device in the list.
  
    @param[in] uPlatDevId    Platform id for the device.
    
    @return             Pointer to log dev if found, otherwise NULL.
  */
I2CLOG_DevType * 
I2cLog_SearchDevice
(
   uint32          uPlatDevId 
)
{
   I2CLOG_DevType *pLog = pLogListHead;
   while ( pLog ) {
      if ( pLog->uPlatDevId == uPlatDevId ) {
         return pLog;
      }
      pLog = pLog->pNext;
   }

   return NULL;
}

void I2cLog_LinkLogHandle(I2CLOG_DevType *pLogDev)
{
   pLogDev->pNext = pLogListHead;
   pLogListHead = pLogDev;
}

void I2cLog_UnlinkLogHandle(I2CLOG_DevType *pLogDev)
{
   I2CLOG_DevType *pLog = pLogListHead;
   I2CLOG_DevType **ppPrevLog =  &pLogListHead;

   // go up to the log
   while(pLog && (pLog != pLogDev)) {
      ppPrevLog = &pLog->pNext;    
      pLog = pLog->pNext;
   }
   if (pLog && (pLog == pLogDev)) {
      *ppPrevLog =  pLog->pNext;
   }
}

QUPLOG_DEV_IMP_HANDLE GetQupLogRegWriteHandle(uint32 uDevAddr)
{
   I2CLOG_DevType *pLog = pLogListHead;
   while(pLog) 
   {
      if ((pLog->uDevAddr == uDevAddr) &&
           pLog->uEnableQupRegWriteLogging) {
         return (QUPLOG_DEV_IMP_HANDLE)pLog->gI2cDynLogHandle;
      }
      pLog = pLog->pNext;
   }
   return (QUPLOG_DEV_IMP_HANDLE)NULL;
}

QUPLOG_DEV_IMP_HANDLE GetQupLogRegReadHandle(uint32 uDevAddr)
{
   I2CLOG_DevType *pLog = pLogListHead;
   while(pLog) 
   {
      if ((pLog->uDevAddr == uDevAddr) &&
           pLog->uEnableQupRegReadLogging) {
         return (QUPLOG_DEV_IMP_HANDLE)pLog->gI2cDynLogHandle;
      }
      pLog = pLog->pNext;
   }
   return (QUPLOG_DEV_IMP_HANDLE)NULL;
}

boolean I2cLog_ReadConfig(I2CLOG_DevType *pLog)
{
   DALSYS_PROPERTY_HANDLE_DECLARE(hProp);
   DALSYSPropertyVar               PropVar;

   if (DAL_SUCCESS != DALSYS_GetDALPropertyHandle(pLog->uPlatDevId, hProp )) {
      return FALSE;
   }

   if (DAL_SUCCESS !=
            DALSYS_GetPropertyValue(hProp, "SW_ENABLE_DEVICE_LOGS",0, &PropVar)) {
      return FALSE;
   }
   if (0 == (uint32)PropVar.Val.dwVal) {
      return FALSE;
   }
   if (DAL_SUCCESS !=
            DALSYS_GetPropertyValue(hProp, "SW_DEVICE_NAME",0, &PropVar)) {
      return FALSE;
   }
   //pLog->pDevName = PropVar.Val.pszVal;
   pLog->pDevName = (char*)pTmpI2cLogName;
      
   if (DAL_SUCCESS !=
            DALSYS_GetPropertyValue(hProp, "SW_LOGS_CALL_TRACE_LEVEL",0, &PropVar)) {
      pLog->uI2cCallTraceLogLevel = 0;
   }
   else {
      pLog->uI2cCallTraceLogLevel = (uint32)PropVar.Val.dwVal;
   }
   if (DAL_SUCCESS !=
            DALSYS_GetPropertyValue(hProp, "SW_LOGS_CALL_DATA_LEVEL",0, &PropVar)) {
      pLog->uI2cCallDataLogLevel = 0;
   }
   else {
      pLog->uI2cCallDataLogLevel = (uint32)PropVar.Val.dwVal;
   }

   if (DAL_SUCCESS !=
            DALSYS_GetPropertyValue(hProp, "SW_LOGS_QUP_WRITES_ENABLED",0,
               &PropVar)) {
      pLog->uEnableQupRegWriteLogging = 0;
   }
   else {
      pLog->uEnableQupRegWriteLogging = (uint32)PropVar.Val.dwVal;
   }

   if (DAL_SUCCESS !=
            DALSYS_GetPropertyValue(hProp, "SW_LOGS_QUP_READS_ENABLED",0,
               &PropVar)) {
      pLog->uEnableQupRegReadLogging = 0;
   }
   else {
      pLog->uEnableQupRegReadLogging = (uint32)PropVar.Val.dwVal;
   }
   return TRUE; 
}

// Initialization 
void 
I2cLog_Init
(
   uint32 uPlatDevId,
   I2CLOG_DevType **ppLogDev
)
{
   ULogResult      ures;
   int32           res;
   I2CLOG_DevType *pLog;

   pLog = I2cLog_SearchDevice(uPlatDevId);
   if ( NULL != pLog) {
      *ppLogDev = pLog;
      return;    
   }

   res = (int32)DALSYS_Malloc(sizeof(I2CLOG_DevType),(void **)&pLog);
   if ( (DAL_SUCCESS != res ) || (NULL == pLog) ) {
      *ppLogDev = NULL;
      return;
   }

   do {
      pLog->uPlatDevId = uPlatDevId; 
      if ( !I2cLog_ReadConfig(pLog) ) {
         res = DAL_ERROR;
         break;
      }

      /* Size of I2c Log - Defaults to 2048 so that logging is enabled */
      pLog->I2cDynLogBufSize = 16384;

      ures = ULogFront_RealTimeInit( 
            &pLog->gI2cDynLogHandle,  /* Log Handle*/
            pLog->pDevName,          /* Name of the log */
            pLog->I2cDynLogBufSize,  /* Initial Buffer. Normally
                                           set to 0 for a disabled log. */
            ULOG_MEMORY_LOCAL, /* Local memory (normal case) */
            ULOG_LOCK_OS);     /* No lock is necessary since this 
                                    case is always run 
                                    within a lock.*/
      if (DAL_SUCCESS != ures) {
         res = ures;
         break;
      }

      I2cLog_LinkLogHandle(pLog);
      *ppLogDev = pLog;
   } while ( 0 );

   if ( DAL_SUCCESS != res ) {
      DALSYS_Free(pLog);
      *ppLogDev = NULL;
   }
}

void I2cLog_DeInit(I2CLOG_DevType *pLogDev)
{
}

void I2cLog_AssociateBlockAddress(I2CLOG_DevType *pLogDev, uint32 uDevAddr)
{
   if ( NULL == pLogDev ) {
      return;     
   } 
   pLogDev->uDevAddr = uDevAddr;
}

/** @brief logs the transfers in a sequence.

    @param[in] pLogDev        Pointer to log structure.
    @param[in] pClntCfg       Pointer to Client configuration.
  
    @return                   Nothing.
  */
void
I2CLOG_LogCltCfgData
(
   I2CLOG_DevType                      *pLogDev,
   I2cClientConfig                     *pClntCfg         
)
{
        
}


/** @brief logs the vector in a transfer.

    @param[in] pLogDev        Pointer to log structure.
    @param[in] pTransfer      Pointer to transfer data.
  
    @return                   Nothing.
  */
void
I2CLOG_LogVectorData
(
   I2CLOG_DevType                      *pLogDev,
   I2cBuffDesc                         *pTrIOVec 
)
{
#if 0
   uint8                           *pIoVecBuff;
   uint32                           uBuffSize;
   uint32                           uLogSize = 0;
   const uint32                     uMaxLogSize = 64;
   uint32                           uMemWds[4];
   uint32                           uWdIndex;
   uint32                           uWdByteIndex;
   uint32                           uRecordSize;
    

   pIoVecBuff = pTrIOVec->pBuff;
   uBuffSize  = pTrIOVec->uBuffSize;

   if (pTrIOVec->uBuffSize > uMaxLogSize) {
      uLogSize = uMaxLogSize;   
   }
   else {
       uLogSize =  pTrIOVec->uBuffSize;
   }
   I2C_CALLDATA_LEVEL1(pLogDev, 3,
                       "[%s]\tVector(address=0x%x, size=%d)",
                       pLogDev->pDevName,pIoVecBuff, uBuffSize);

   while (uLogSize)
   {
      // make the record
      uRecordSize = 0;
      uWdIndex = 0;
      do {
         // make next word     
         uWdByteIndex = 0;
         uMemWds[uWdIndex] = 0;

         while(uLogSize && (uWdByteIndex<4)) {
            uMemWds[uWdIndex] |= *pIoVecBuff++ >> (8 * uWdByteIndex++);
            uRecordSize++;
            uLogSize--;  
         }
              
         uWdIndex++;  
      } while(uLogSize && (uWdIndex < 4));

      if (uWdIndex == 4) {
         I2C_CALLDATA_LEVEL1(pLogDev, 6,
                       "[%s]\t\tBytes:%d : %x %x %x %x)",
                       pLogDev->pDevName,uRecordSize,
                       uMemWds[0],uMemWds[1],uMemWds[2],uMemWds[3]);    
      }
      else if (uWdIndex == 3) {
         I2C_CALLDATA_LEVEL1(pLogDev, 5,
                       "[%s]\t\tBytes:%d : %x %x %x)",
                       pLogDev->pDevName,uRecordSize,
                       uMemWds[0],uMemWds[1],uMemWds[2]);     
      }
      else if (uWdIndex == 2) {
         I2C_CALLDATA_LEVEL1(pLogDev, 4,
                       "[%s]\t\tBytes:%d : %x %x)",
                       pLogDev->pDevName,uRecordSize,
                       uMemWds[0],uMemWds[1]);     
      }
      else {
         I2C_CALLDATA_LEVEL1(pLogDev, 3,
                       "[%s]\t\tBytes:%d : %x)",
                       pLogDev->pDevName,uRecordSize,
                       uMemWds[0]);     
      }
   }
#endif   

}

/** @brief logs the transfers in a sequence.

    @param[in] pLogDev        Pointer to log structure.
    @param[in] pTransfer      Pointer to transfer data.
  
    @return                   Nothing.
  */
void
I2CLOG_LogTransferData
(
   I2CLOG_DevType                      *pLogDev,
   I2cTransfer                         *pTransfer         
)
{
#if 0   
   uint32                           uLogBuffMax = 256;
   uint32                           uLogCnt = 0;
   I2cBuffDesc                     *pTrIOVec;
   
   I2C_CALLDATA_LEVEL1(pLogDev, 5,
                       "[%s]\tTransfer(address,eTranDirection,eTranCtxt,uTrSize,%)",
                       pLogDev->pDevName,pTransfer->tranCfg.uSlaveAddr,
                       pTransfer->eTranDirection,pTransfer->eTranCtxt,
                       pTransfer->uTrSize);
   if (pTransfer->uTrSize < uLogBuffMax) {
      uLogBuffMax = pTransfer->uTrSize;
   }

   pTrIOVec = pTransfer->pI2cBuffDesc;
   
   // foreach buffer print content
   do {
      I2CLOG_LogVectorData(pLogDev,pTrIOVec);
      uLogCnt += pTrIOVec->uBuffSize;
      pTrIOVec++;
   } while ( uLogCnt < uLogBuffMax );
#endif
}

/** @brief logs the transfers in a sequence.

    @param[in] pLogDev        Pointer to log structure.
    @param[in] pSeq           Pointer to sequence.
  
    @return                   Nothing.
  */
void
I2CLOG_LogSeqData
(
   I2CLOG_DevType                      *pLogDev,
   I2cSequence                         *pSeq         
)
{
#if 0   
   uint32         uTransferIndex;
   I2cTransfer   *pTransfer;   

   for (uTransferIndex = 0; uTransferIndex < pSeq->uNumTransfers; uTransferIndex++) {
      pTransfer = &pSeq->pTransfer[uTransferIndex];
      I2CLOG_LogTransferData(pLogDev, pTransfer);     
   }
#endif  
}

void I2cLog_LogBuffer
(
   I2CLOG_DevType                      *pLogDev,
   uint8                               *pLogBuff,
   uint8                                uSize
)
{
   uint32 buffSize;
   uint32 logedSize;
   uint8 *pBuff;
   
      buffSize = uSize;
      pBuff = pLogBuff;
      do {
         logedSize = buffSize;
         
	    if (buffSize >= 8) { 
		    I2C_CALLDATA_LEVEL1(pLogDev, 8, "\t%x %x %x %x  %x %x %x %x",
	                           pBuff[0],pBuff[1],pBuff[2],pBuff[3],pBuff[4],pBuff[5],pBuff[6],pBuff[7]);
	       logedSize = 8;
		 }
		 else if (buffSize == 7) { 
		    I2C_CALLDATA_LEVEL1(pLogDev, 7, "\t%x %x %x %x  %x %x %x",
	                           pBuff[0],pBuff[1],pBuff[2],pBuff[3],pBuff[4],pBuff[5],pBuff[6]);
	 	 }
		 else if (buffSize == 6) { 
		    I2C_CALLDATA_LEVEL1(pLogDev, 6, "\t%x %x %x %x  %x %x",
	                           pBuff[0],pBuff[1],pBuff[2],pBuff[3],pBuff[4],pBuff[5]);

		 }
		 else if (buffSize == 5 ) { 
		    I2C_CALLDATA_LEVEL1(pLogDev, 5, "\t%x %x %x %x  %x",
	                           pBuff[0],pBuff[1],pBuff[2],pBuff[3],pBuff[4]);
		 }
		 else if (buffSize == 4 ) { 
		    I2C_CALLDATA_LEVEL1(pLogDev, 4, "\t%x %x %x %x",
	                           pBuff[0],pBuff[1],pBuff[2],pBuff[3]);
		 }
		 else if (buffSize == 3 ) { 
		    I2C_CALLDATA_LEVEL1(pLogDev, 3, "\t%x %x %x", pBuff[0],pBuff[1],pBuff[2]);
	 	 }
		 else if (buffSize == 2) { 
		    I2C_CALLDATA_LEVEL1(pLogDev, 2, "\t%x %x", pBuff[0],pBuff[1]);

		 }
		 else if (buffSize == 1 ) { 
		    I2C_CALLDATA_LEVEL1(pLogDev, 1, "\t%x", pBuff[0]);
		 }
		 pBuff += logedSize;
		 buffSize -= logedSize;
       
      } while ( buffSize );
}

/*
int32 I2cLog_GetErrorLogLevel(void)
{
   return(uI2cErrLogLevel);
}

void *  I2cLog_GetUlogHandle(void)
{
   return(gI2cDynLogHandle);
}



int32 I2cLog_GetInfoLogLevel(void)
{
   return(uI2cInfoLogLevel);
}

int32 I2cLog_GetCallDataLogLevel(void)
{
   return(uI2cCallDataLogLevel);
}

int32 I2cLog_GetCallTraceLogLevel(void)
{
   return(uI2cCallTraceLogLevel);
}

*/

