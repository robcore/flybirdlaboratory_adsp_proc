/*
* Copyright (c) 2013-2015 Qualcomm Technologies, Inc.
* All Rights Reserved.
* Qualcomm Technologies, Inc. Confidential and Proprietary.
*/

/*
 * mipsmgr.c
 *
 *  Created on: Feb 13, 2012
 *      Author: yrusakov
 */

#include "adsppm.h"
#include "adsppm_utils.h"
#include "requestmgr.h"
#include "asic.h"
#include "mipsmgr.h"
#include "ahbmgr.h"
#include "core_internal.h"
#include "hal_clkrgm.h"
#include "hal_busdrv.h"
#include "usleepmgr.h"


typedef struct
{
    AdsppmMIPSToClockAggregateType mipsToClockData;
    AdsppmMIPSToBWAggregateType mipsToBWAggregateDataDdr;
    AdsppmMIPSToBWAggregateType mipsToBWAggregateDataOcmem;
} mipsAggregateDataType;

typedef struct
{
    DALSYSSyncHandle      lock;
    mipsAggregateDataType preMipsAggregateData;
    mipsAggregateDataType mipsAggregateData;
} mipsMgrCtxType;

static mipsMgrCtxType mipsMgrCtx;


/**
 * @fn MIPS_Init - Initialize MIPS management related data structure and mutex
 * @return Adsppm_Status_Failed
 * @return Adsppm_Status_Success
 */
Adsppm_Status MIPS_Init(void)
{
    Adsppm_Status sts = Adsppm_Status_Success;
    ADSPPM_LOG_FUNC_ENTER;

    if(DAL_SUCCESS != DALSYS_SyncCreate(
        DALSYS_SYNC_ATTR_RESOURCE,
        (DALSYSSyncHandle *) &mipsMgrCtx.lock, NULL))
    {
        sts = Adsppm_Status_Failed;
    }
    if((Adsppm_Status_Success == sts) && (NULL != mipsMgrCtx.lock))
    {
        adsppm_lock(mipsMgrCtx.lock);
        memset(&mipsMgrCtx.preMipsAggregateData, 0, sizeof(mipsAggregateDataType));
        memset(&mipsMgrCtx.mipsAggregateData, 0, sizeof(mipsAggregateDataType));
        adsppm_unlock(mipsMgrCtx.lock);
    }

    ADSPPM_LOG_FUNC_EXIT(sts);
    return sts;
}


static Adsppm_Status mipsMgrUpdateUSleepMgr(void)
{
    Adsppm_Status sts = Adsppm_Status_Success;
    AdsppmMIPSToBWAggregateType *pMipsToBWAggregateDataDdr = 
        &mipsMgrCtx.mipsAggregateData.mipsToBWAggregateDataDdr;

    sts = USleepMgr_ProcessRequest(
        USleepMgr_VoterId_MipsMgr,
        pMipsToBWAggregateDataDdr->mipsToBW.bwValue.busBwAbIb.Ab);

    return sts;    
}


Adsppm_Status mipsAggregateClientMIPS(coreUtils_Q_Type *pMipsReqQ)
{
    Adsppm_Status sts = Adsppm_Status_Success;
    RMHandleType *pRMHandle = NULL;
    AdsppmMipsRequestType *pMipsReqData = NULL;
    AdsppmClientTypeType clientType = Adsppm_ClientType_Normal;
    uint32 index = 0;

    AdsppmMIPSToClockAggregateType *pMipsToClockData =
        &mipsMgrCtx.mipsAggregateData.mipsToClockData;
    AdsppmMIPSToBWAggregateType *pMipsToBWAggregateDataDdr = 
        &mipsMgrCtx.mipsAggregateData.mipsToBWAggregateDataDdr;
    AdsppmMIPSToBWAggregateType *pMipsToBWAggregateDataOcmem = 
        &mipsMgrCtx.mipsAggregateData.mipsToBWAggregateDataOcmem;

    ADSPPM_LOCK_RESOURCE(Adsppm_Rsc_Id_Mips);

    // Go through all client request
    pRMHandle = (RMHandleType *) coreUtils_Q_Check(pMipsReqQ);
    for(index = 0; (index < pMipsReqQ->nCnt) && (NULL != pRMHandle); index++)
    {
        if(RM_Valid == pRMHandle->validFlag)
        {
            if((NULL == (AdsppmMipsRequestType *) (pRMHandle->pRequestData)) ||
                (NULL == pRMHandle->pAdsppmHandle))
            {
                sts = Adsppm_Status_BadParm;
                ADSPPM_LOG_PRINTF_2(ADSPPM_LOG_LEVEL_ERROR,
                    "pRequestData(%u) or pAdsppmHandle(%u) is NULL",
                    (AdsppmMipsRequestType *) (pRMHandle->pRequestData),
                    pRMHandle->pAdsppmHandle);
                break;
            }
            else
            {
                pMipsReqData = (AdsppmMipsRequestType *) (pRMHandle->pRequestData);
                clientType = pRMHandle->pAdsppmHandle->clientType;

                if((pMipsReqData->mipsTotal > 0) || (pMipsReqData->mipsPerThread > 0))
                {
                    pMipsToClockData->numOfClients++;
                    pMipsToClockData->mipsTotal += pMipsReqData->mipsTotal;
                    pMipsToClockData->mipsPerThread =
                        MAX(pMipsToClockData->mipsPerThread, pMipsReqData->mipsPerThread);
                    if(Adsppm_ClientType_Periodic == clientType)
                    {
                        pMipsToClockData->numOfPeriodicClients++;
                    }

                    if(MipsRequestOperation_BWandMIPS == pMipsReqData->reqOperation)
                    {
                        if(AdsppmBusPort_Ddr_Slave == pMipsReqData->codeLocation)
                        {
                            pMipsToBWAggregateDataDdr->numOfClients++;
                            pMipsToBWAggregateDataDdr->mipsTotal += pMipsReqData->mipsTotal;
                            pMipsToBWAggregateDataDdr->mipsPerThread =
                                MAX(pMipsToBWAggregateDataDdr->mipsPerThread, pMipsReqData->mipsPerThread);
                            if(Adsppm_ClientType_Periodic == clientType)
                            {
                                pMipsToBWAggregateDataDdr->numOfPeriodicClients++;
                            }
                        }
                        else if(AdsppmBusPort_Ocmem_Slave == pMipsReqData->codeLocation)
                        {
                            pMipsToBWAggregateDataOcmem->numOfClients++;
                            pMipsToBWAggregateDataOcmem->mipsTotal += pMipsReqData->mipsTotal;
                            pMipsToBWAggregateDataOcmem->mipsPerThread =
                                MAX(pMipsToBWAggregateDataOcmem->mipsPerThread, pMipsReqData->mipsPerThread);
                            if(Adsppm_ClientType_Periodic == clientType)
                            {
                                pMipsToBWAggregateDataOcmem->numOfPeriodicClients++;
                            }
                        }
                    }
                }
            }
        }
        pRMHandle = (RMHandleType *)coreUtils_Q_Next(pMipsReqQ, &(pRMHandle->rmHandleQLink));
    }

    if(Adsppm_Status_Success == sts)
    {
        // Specify whether only periodic clients are running
        // This has to be done before calling ACM and AHBM functions
        if((pMipsToClockData->numOfPeriodicClients == pMipsToClockData->numOfClients) &&
            (pMipsToClockData->numOfPeriodicClients > 0))
        {
            SetPeriodicUseCase(1);
        }
        else
        {
            SetPeriodicUseCase(0);
        }
    }

    ADSPPM_UNLOCK_RESOURCE(Adsppm_Rsc_Id_Mips);

    return sts;
}


/**
 * @fn MIPS_ProcessRequest - Process clients MIPS request
 * @param input RMHandleType *pMipsReqQ - MIPS request data from clients
 * @return Adsppm_Status
 */
Adsppm_Status MIPS_ProcessRequest(coreUtils_Q_Type *pMipsReqQ)
{
    Adsppm_Status sts = Adsppm_Status_Success;

    AdsppmMIPSToClockAggregateType *pMipsToClockData =
        &mipsMgrCtx.mipsAggregateData.mipsToClockData;
    AdsppmMIPSToBWAggregateType *pMipsToBWAggregateDataDdr = 
        &mipsMgrCtx.mipsAggregateData.mipsToBWAggregateDataDdr;
    AdsppmMIPSToBWAggregateType *pMipsToBWAggregateDataOcmem = 
        &mipsMgrCtx.mipsAggregateData.mipsToBWAggregateDataOcmem;

    AdsppmMIPSToClockAggregateType *pPreMipsToClockData =
        &mipsMgrCtx.preMipsAggregateData.mipsToClockData;
    AdsppmMIPSToBWAggregateType *pPreMipsToBWAggregateDataDdr = 
        &mipsMgrCtx.preMipsAggregateData.mipsToBWAggregateDataDdr;
    AdsppmMIPSToBWAggregateType *pPreMipsToBWAggregateDataOcmem = 
        &mipsMgrCtx.preMipsAggregateData.mipsToBWAggregateDataOcmem;

    ADSPPM_LOG_FUNC_ENTER;

    if(NULL == pMipsReqQ)
    {
        sts = Adsppm_Status_BadParm;
    }
    else
    {
        if(NULL == mipsMgrCtx.lock)
        {
            sts = Adsppm_Status_NotInitialized;
        }
        else
        {
            adsppm_lock(mipsMgrCtx.lock);
            memset(&mipsMgrCtx.mipsAggregateData, 0, sizeof(mipsAggregateDataType));
            pMipsToBWAggregateDataDdr->mipsBWSlavePort = AdsppmBusPort_Ddr_Slave;
            pMipsToBWAggregateDataDdr->mipsToBW.busRoute.masterPort = AdsppmBusPort_Adsp_Master;
            pMipsToBWAggregateDataDdr->mipsToBW.busRoute.slavePort = AdsppmBusPort_Ddr_Slave;
            pMipsToBWAggregateDataOcmem->mipsBWSlavePort = AdsppmBusPort_Ocmem_Slave;
            pMipsToBWAggregateDataOcmem->mipsToBW.busRoute.masterPort = AdsppmBusPort_Adsp_Master;
            pMipsToBWAggregateDataOcmem->mipsToBW.busRoute.slavePort = AdsppmBusPort_Ocmem_Slave;

            // Aggregate clients requests and decide if the use-case is periodic
            sts = mipsAggregateClientMIPS(pMipsReqQ);

            if(Adsppm_Status_Success == sts)
            {
                // Calculate Q6 Clock
                sts = ACM_GetClockFromMips(pMipsToClockData);
                ADSPPM_LOG_PRINTF_3(ADSPPM_LOG_LEVEL_INFO_EXT,
                    "MIPS total=%u, MIPS min=%u, Clock=%u",
                    pMipsToClockData->mipsTotal,
                    pMipsToClockData->mipsPerThread,
                    pMipsToClockData->qDSP6Clock);
            }
            // Set Q6 Clock
            if((pPreMipsToClockData->qDSP6Clock != pMipsToClockData->qDSP6Clock) &&
                (Adsppm_Status_Success == sts))
            {
                sts = ClkRgm_SetClock(AdsppmClk_Adsp_Core, pMipsToClockData->qDSP6Clock);
            }

            // Calculate DDR BW for MIPS
            if(Adsppm_Status_Success == sts)
            {
                sts = ACM_GetBWFromMips(pMipsToBWAggregateDataDdr);
                ADSPPM_LOG_PRINTF_2(ADSPPM_LOG_LEVEL_INFO_EXT,
                    "DDR BW Ab=%u, Ib=%u",
                    (uint32) pMipsToBWAggregateDataDdr->mipsToBW.bwValue.busBwAbIb.Ab,
                    (uint32) pMipsToBWAggregateDataDdr->mipsToBW.bwValue.busBwAbIb.Ib);
            }
            // Calculate OCMEM BW for MIPS
            if(Adsppm_Status_Success == sts)
            {
                sts = ACM_GetBWFromMips(pMipsToBWAggregateDataOcmem);
                ADSPPM_LOG_PRINTF_2(ADSPPM_LOG_LEVEL_INFO_EXT,
                    "OCMEM BW Ab=%u, Ib=%u",
                    (uint32) pMipsToBWAggregateDataOcmem->mipsToBW.bwValue.busBwAbIb.Ab,
                    (uint32) pMipsToBWAggregateDataOcmem->mipsToBW.bwValue.busBwAbIb.Ib);
            }

            // Issue BW request for MIPS
            if((Adsppm_Status_Success == sts) &&
                ((pPreMipsToBWAggregateDataDdr->mipsToBW.bwValue.busBwAbIb.Ab !=
                    pMipsToBWAggregateDataDdr->mipsToBW.bwValue.busBwAbIb.Ab) ||
                (pPreMipsToBWAggregateDataOcmem->mipsToBW.bwValue.busBwAbIb.Ab !=
                    pMipsToBWAggregateDataOcmem->mipsToBW.bwValue.busBwAbIb.Ab) ||
                (pPreMipsToBWAggregateDataDdr->mipsToBW.bwValue.busBwAbIb.Ib !=
                    pMipsToBWAggregateDataDdr->mipsToBW.bwValue.busBwAbIb.Ib) ||
                (pPreMipsToBWAggregateDataOcmem->mipsToBW.bwValue.busBwAbIb.Ib !=
                    pMipsToBWAggregateDataOcmem->mipsToBW.bwValue.busBwAbIb.Ib)))
            {
                AdsppmBusBWRequestValueType busBw[BUS_NUMBER_MIPS_ROUTES];
                busBw[0].bwValue = pMipsToBWAggregateDataOcmem->mipsToBW.bwValue;
                busBw[0].busRoute.masterPort = pMipsToBWAggregateDataOcmem->mipsToBW.busRoute.masterPort;
                busBw[0].busRoute.slavePort = pMipsToBWAggregateDataOcmem->mipsToBW.busRoute.slavePort;
                busBw[1].bwValue = pMipsToBWAggregateDataDdr->mipsToBW.bwValue;
                busBw[1].busRoute.masterPort = pMipsToBWAggregateDataDdr->mipsToBW.busRoute.masterPort;
                busBw[1].busRoute.slavePort = pMipsToBWAggregateDataDdr->mipsToBW.busRoute.slavePort;
                sts = Bus_IssueBWRequest_MIPS(&busBw[0]);
            }

            // Adjust AHB clock for periodic use-cases if required
            if(Adsppm_Status_Success == sts)
            {
                sts = AHBM_AdjustAndSetAHBClock();
            }

            // Update uSleep manager
            if(Adsppm_Status_Success == sts)
            {
                sts = mipsMgrUpdateUSleepMgr();
            }

            if(Adsppm_Status_Success == sts)
            {
                memscpy(
                    &mipsMgrCtx.preMipsAggregateData,
                    sizeof(mipsAggregateDataType),
                    &mipsMgrCtx.mipsAggregateData,
                    sizeof(mipsAggregateDataType));
            }
            adsppm_unlock(mipsMgrCtx.lock);
        }
    }

    ADSPPM_LOG_FUNC_EXIT(sts);
    return sts;
}

