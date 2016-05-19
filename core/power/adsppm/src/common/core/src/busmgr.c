/*
* Copyright (c) 2013-2015 Qualcomm Technologies, Inc.
* All Rights Reserved.
* Qualcomm Technologies, Inc. Confidential and Proprietary.
*/

/*
 * busmgr.c
 *
 *  Created on: Feb 13, 2012
 *      Author: yrusakov
 */

#include "adsppm.h"
#include "adsppm_utils.h"
#include "busmgr.h"
#include "asic.h"
#include "hal_clkrgm.h"
#include "ahbmgr.h"
#include "hal_busdrv.h"
#include "stdlib.h"
#include "usleepmgr.h"

// Bare minimal AHB BW to keep AHB always ON. Used in AHB BW aggregation
#define MIN_AHB_BW 32767

/**
 * struct  busMgrCtxType - define bus management context
 */
typedef struct
{
    DALSYSSyncHandle            lock;
    uint32                      extRouteNum;
    AsicBusExtRouteType         *pExtRoutes;
    uint32                      preCurrentIndex; //!< Index used in pExtBwAggregateData and clockState arrays
    AdsppmBusBWRequestValueType *pExtBwAggregateData[2];
    Hal_ClkRgmEnableDisableType clockState[2][AdsppmClk_EnumMax];
    AdsppmBusBWDataIbAbType     curAHBBwData; //!< Current aggregated AHB BW
    AdsppmBusBWDataIbAbType     nonSuppressibleAhbBW; //!< Non-suppressible AHB BW
    boolean                     bPeriodicClientBW2DDR; //!< True if at least 1 periodic client requests BW to DDR
} busMgrCtxType;

/**
 * @enum BUSMgrBwTypeType - define bus bw type
 */
typedef enum
{
    BUSMgr_Bw_None              = 0,
    BUSMgr_Bw_Internal_Only     = 1,
    BUSMgr_Bw_External_Only     = 2,
    BUSMgr_Bw_Internal_External = 3,
    BUSMgr_Bw_ForceTo8bits      = 0x7f
} BUSMgrBwTypeType;

/**
 * @struct BUSMgr_BwDescriptorType - contains bw info for a single request
 */
typedef struct
{
    AdsppmBusPortIdType masterPort;
    AdsppmBusPortIdType slavePort;
    AdsppmBusPortIdType accessPort;
    // Master port descriptor
    const AsicBusPortDescriptorType *pMPortDescriptor;
    // Slave port descriptor
    const AsicBusPortDescriptorType *pSPortDescriptor;
    // Access port descriptor
    const AsicBusPortDescriptorType *pAPortDescriptor;
    AdsppmBusBWOperationType bwOperation;
    AdsppmBusBWDataType bwValue;
} BUSMgr_BwDescriptorType;

static busMgrCtxType gBusMgrCtx;

// Internal function to process bandwidth
static Adsppm_Status busMgrAggregateRequest(AdsppmBusBWRequestValueType *pBwRequest);


/**
 * @fn BUS_Init - bus management init, init mutex and  global variables
 */
Adsppm_Status BUS_Init(void)
{
    Adsppm_Status sts = Adsppm_Status_Success;
    DALResult dalResult = DAL_SUCCESS;
    uint32 index = 0;
    ADSPPM_LOG_FUNC_ENTER;

    memset(&gBusMgrCtx, 0, sizeof(busMgrCtxType));
    dalResult = DALSYS_SyncCreate(
        DALSYS_SYNC_ATTR_RESOURCE,
        (DALSYSSyncHandle *) &gBusMgrCtx.lock,
        NULL);

    if(DAL_SUCCESS != dalResult)
    {
        ADSPPM_LOG_PRINTF_0(ADSPPM_LOG_LEVEL_ERROR, "Failed to create lock");
        sts = Adsppm_Status_Failed;
    }
    else
    {
        // Get support route pair number from asic manager
        gBusMgrCtx.extRouteNum = ACMBus_GetNumberOfExtRoutes();
        gBusMgrCtx.pExtRoutes =
            malloc(gBusMgrCtx.extRouteNum * sizeof(AsicBusExtRouteType));
        gBusMgrCtx.pExtBwAggregateData[0] =
            malloc(gBusMgrCtx.extRouteNum * sizeof(AdsppmBusBWRequestValueType));
        gBusMgrCtx.pExtBwAggregateData[1] =
            malloc(gBusMgrCtx.extRouteNum * sizeof(AdsppmBusBWRequestValueType));

        // Check for failed malloc
        if((NULL == gBusMgrCtx.pExtRoutes) ||
            (NULL == gBusMgrCtx.pExtBwAggregateData[0]) ||
            (NULL == gBusMgrCtx.pExtBwAggregateData[1]))
        {
            ADSPPM_LOG_PRINTF_0(ADSPPM_LOG_LEVEL_ERROR,
                "Failed to allocate aggregate buffer");

            if(NULL != gBusMgrCtx.pExtRoutes)
            {
                free(gBusMgrCtx.pExtRoutes);
            }
            if(NULL != gBusMgrCtx.pExtBwAggregateData[0])
            {
                free(gBusMgrCtx.pExtBwAggregateData[0]);
            }
            if(NULL != gBusMgrCtx.pExtBwAggregateData[1])
            {
                free(gBusMgrCtx.pExtBwAggregateData[1]);
            }
            sts = Adsppm_Status_NoMemory;
        }
        else
        {
            // Get supported route pairs from asic manager and save
            ACMBus_GetExtRoutes(gBusMgrCtx.pExtRoutes);
            for(index = 0; index < gBusMgrCtx.extRouteNum; index++)
            {
                gBusMgrCtx.pExtBwAggregateData[0][index].busRoute.masterPort =
                    gBusMgrCtx.pExtRoutes[index].masterPort.adsppmMaster;
                gBusMgrCtx.pExtBwAggregateData[0][index].busRoute.slavePort =
                    gBusMgrCtx.pExtRoutes[index].slavePort.adsppmSlave;
                gBusMgrCtx.pExtBwAggregateData[0][index].bwOperation =
                    AdsppmBusBWOperation_BW;

                gBusMgrCtx.pExtBwAggregateData[1][index].busRoute.masterPort =
                    gBusMgrCtx.pExtRoutes[index].masterPort.adsppmMaster;
                gBusMgrCtx.pExtBwAggregateData[1][index].busRoute.slavePort =
                    gBusMgrCtx.pExtRoutes[index].slavePort.adsppmSlave;
                gBusMgrCtx.pExtBwAggregateData[1][index].bwOperation =
                    AdsppmBusBWOperation_BW;
            }
        }
    }

    ADSPPM_LOG_FUNC_EXIT(sts);
    return sts;
}


static Adsppm_Status busMgrProcessClocks(void)
{
    Adsppm_Status sts = Adsppm_Status_Success;
    const AsicClkDescriptorType *pClkDesc = NULL;
    uint32 index = 0;

    for(index = AdsppmClk_Adsp_Hclk;
        (index < AdsppmClk_EnumMax) && (Adsppm_Status_Success == sts);
        index++)
    {
        if(gBusMgrCtx.clockState[gBusMgrCtx.preCurrentIndex^1][index] !=
            gBusMgrCtx.clockState[gBusMgrCtx.preCurrentIndex][index])
        {
            pClkDesc = ACMClk_GetClockDescriptor(index);
            if(NULL == pClkDesc)
            {
                ADSPPM_LOG_PRINTF_1(ADSPPM_LOG_LEVEL_ERROR,
                    "Clock descriptor is NULL, clkId=%u", index);
                sts = Adsppm_Status_Failed;
            }
            else
            {
                switch(pClkDesc->clkCntlType)
                {
                case AsicClk_CntlSW_DCG:
                case AsicClk_CntlAlwaysON_DCG:
                case AsicClk_CntlSW:
                    sts = ClkRgm_EnableClock(
                        (AdsppmClkIdType) index,
                        gBusMgrCtx.clockState[gBusMgrCtx.preCurrentIndex][index]);
                    break;
                default:
                    // Ignore AON and AOFF clocks
                    break;
                }
            }
        }
    }

    return sts;
}


static uint32 busMgrProcessExternalBW(AdsppmBusBWRequestValueType *pUpdateExtBusBwValue)
{
    uint32 index = 0, numOfBW = 0;
    AdsppmBusBWRequestValueType* pCurrentBwVote = NULL;
    AdsppmBusBWRequestValueType* pPreviousBwVote = NULL;

    for(index = 0; index < gBusMgrCtx.extRouteNum; index++)
    {
        pCurrentBwVote = &(gBusMgrCtx.pExtBwAggregateData[gBusMgrCtx.preCurrentIndex][index]);
        pPreviousBwVote = &(gBusMgrCtx.pExtBwAggregateData[gBusMgrCtx.preCurrentIndex^1][index]);

        // Apply BW to DDR optimization if:
        // 1. use case is periodic
        // 2. and at least 1 periodic client requests BW > 0 to DDR from Q6
        if((AdsppmBusPort_Adsp_Master == pCurrentBwVote->busRoute.masterPort) &&
            (AdsppmBusPort_Ddr_Slave == pCurrentBwVote->busRoute.slavePort) &&
            (AsicFeatureState_Enabled == ACM_GetFeatureStatus(AsicFeatureId_TimelineOptimisationBw)))
        {
            if(IsPeriodicUseCase() && gBusMgrCtx.bPeriodicClientBW2DDR &&
                (0 < pCurrentBwVote->bwValue.busBwAbIb.Ib))
            {
                pCurrentBwVote->bwValue.busBwAbIb.Ib =
                    ACM_AdjustParamValue(AsicFeatureId_TimelineOptimisationBw,
                        pCurrentBwVote->bwValue.busBwAbIb.Ib);
            }
        }

        if((pPreviousBwVote->bwValue.busBwAbIb.Ab != pCurrentBwVote->bwValue.busBwAbIb.Ab) ||
            (pPreviousBwVote->bwValue.busBwAbIb.Ib != pCurrentBwVote->bwValue.busBwAbIb.Ib))
        {
            // Copy updated bus vote to buffer
            memscpy(&(pUpdateExtBusBwValue[numOfBW]),
                sizeof(AdsppmBusBWRequestValueType),
                pCurrentBwVote,
                sizeof(AdsppmBusBWRequestValueType));
            ADSPPM_LOG_PRINTF_3(ADSPPM_LOG_LEVEL_INFO_EXT, "ext BW %u updated: Ib=%u, Ab=%u",
                numOfBW,
                (uint32) pUpdateExtBusBwValue[numOfBW].bwValue.busBwAbIb.Ib,
                (uint32) pUpdateExtBusBwValue[numOfBW].bwValue.busBwAbIb.Ab);
            numOfBW++;
        }
    }

    return numOfBW;
}


static Adsppm_Status busMgrUpdateUSleepMgr(void)
{
    Adsppm_Status sts = Adsppm_Status_Success;
    uint32 index = 0;
    AdsppmBusBWRequestValueType* pCurrentBwVote = NULL;
    uint64 ddrAb = 0;

    for(index = 0; index < gBusMgrCtx.extRouteNum; index++)
    {
        pCurrentBwVote = &(gBusMgrCtx.pExtBwAggregateData[gBusMgrCtx.preCurrentIndex][index]);
        if(pCurrentBwVote->busRoute.slavePort == AdsppmBusPort_Ddr_Slave)
        {
            ddrAb += pCurrentBwVote->bwValue.busBwAbIb.Ab;
        }
    }

    sts = USleepMgr_ProcessRequest(USleepMgr_VoterId_BusMgr, ddrAb);

    return sts;
}


/**
 * @fn BUS_ProcessRequest - bus management main function,
 *                          separate bw to external and internal bw and do external bw aggregate
 * @param input: coreUtils_Q_Type *pBWReqQ
 * @return Adsppm_Status
 */
Adsppm_Status BUS_ProcessRequest(coreUtils_Q_Type *pBWReqQ)
{
    Adsppm_Status sts = Adsppm_Status_Success;
    uint32 index = 0, bwNum = 0, numUpdatedExtBwVotes = 0;
    RMHandleType *pRMHandle = NULL;
    AdsppmBusBWRequestValueType updateExtBusBwValue[gBusMgrCtx.extRouteNum];
    ADSPPM_LOG_FUNC_ENTER;

    if(NULL == pBWReqQ)
    {
        sts = Adsppm_Status_BadParm;
        ADSPPM_LOG_PRINTF_0(ADSPPM_LOG_LEVEL_ERROR, "Pointer is NULL");
    }
    else
    {
        if(NULL == gBusMgrCtx.lock)
        {
            ADSPPM_LOG_PRINTF_0(ADSPPM_LOG_LEVEL_ERROR, "Not initialized");
            sts = Adsppm_Status_NotInitialized;
        }
        else
        {
            // Lock for bus manager global data update
            adsppm_lock(gBusMgrCtx.lock);
            ADSPPM_LOCK_RESOURCE(Adsppm_Rsc_Id_BW);

            // Init variables
            memset(updateExtBusBwValue, 0, gBusMgrCtx.extRouteNum*sizeof(AdsppmBusBWRequestValueType));
            gBusMgrCtx.curAHBBwData.Ib = gBusMgrCtx.nonSuppressibleAhbBW.Ib = MIN_AHB_BW;
            gBusMgrCtx.curAHBBwData.Ab = gBusMgrCtx.nonSuppressibleAhbBW.Ab = 0;
            gBusMgrCtx.bPeriodicClientBW2DDR = FALSE;

            for(index = 0; index < gBusMgrCtx.extRouteNum; index++)
            {
                gBusMgrCtx.pExtBwAggregateData[gBusMgrCtx.preCurrentIndex][index].bwValue.busBwAbIb.Ab = 0;
                gBusMgrCtx.pExtBwAggregateData[gBusMgrCtx.preCurrentIndex][index].bwValue.busBwAbIb.Ib = 0;
            }

            for(index = AdsppmClk_Adsp_Hclk; index < AdsppmClk_Audio_Core_AON; index++)
            {
                gBusMgrCtx.clockState[gBusMgrCtx.preCurrentIndex][index] =
                    (AsicFeatureState_Enabled != ACM_GetFeatureStatus(AsicFeatureId_Ahb_Sw_CG))?
                    Hal_ClkRgmEnable:Hal_ClkRgmDisable;
            }

            for(index = AdsppmClk_HwRsp_Core; index < AdsppmClk_EnumMax; index++)
            {
                gBusMgrCtx.clockState[gBusMgrCtx.preCurrentIndex][index] =
                    (AsicFeatureState_Enabled != ACM_GetFeatureStatus(AsicFeatureId_CoreClk_Scaling))?
                    Hal_ClkRgmEnable:Hal_ClkRgmDisable;
            }

            // Go through each client's bw request
            pRMHandle = (RMHandleType *)coreUtils_Q_Check(pBWReqQ);

            for(index = 0; (index < pBWReqQ->nCnt) && (NULL != pRMHandle); index++)
            {
                // Generic BW Request
                if(RM_Valid == pRMHandle->validFlag)
                {
                    ADSPPM_LOG_PRINTF_0(ADSPPM_LOG_LEVEL_INFO_EXT, "Generic BW Request");
                    if((NULL == (AdsppmBwReqType *)(pRMHandle->pRequestData)) ||
                        (NULL == pRMHandle->pAdsppmHandle))
                    {
                        ADSPPM_LOG_PRINTF_2(ADSPPM_LOG_LEVEL_ERROR,
                            "pRequestData(%u) or pAdsppmHandle(%u) is NULL",
                            (AdsppmBwReqType *) (pRMHandle->pRequestData), pRMHandle->pAdsppmHandle);
                        sts = Adsppm_Status_BadParm;
                        break;
                    }
                    else
                    {
                        AdsppmBwReqType *pBwReqData = (AdsppmBwReqType *) (pRMHandle->pRequestData);
                        // Go through each bw request for this client
                        for(bwNum = 0; (bwNum < pBwReqData->numOfBw) && (Adsppm_Status_Success == sts); bwNum++)
                        {
                            AdsppmBusBWRequestValueType *pBwRequest = &pBwReqData->pBwArray[bwNum];

                            // Get bus port IDs corresponding to this core instance if applicable
                            pBwRequest->busRoute.masterPort = ACMBus_GetInstanceMasterBusPortId(
                                pRMHandle->pAdsppmHandle->coreId,
                                pRMHandle->pAdsppmHandle->instanceId,
                                pBwRequest->busRoute.masterPort);
                            pBwRequest->busRoute.slavePort = ACMBus_GetInstanceSlaveBusPortId(
                                pRMHandle->pAdsppmHandle->coreId,
                                pRMHandle->pAdsppmHandle->instanceId,
                                pBwRequest->busRoute.slavePort);

                            // Filter out requests with bus ports that have no connections
                            // meaning they do not exit in current chip set
                            const AsicBusPortDescriptorType *pMasterPortDescriptor = 
                                ACMBus_GetPortDescriptor(pBwRequest->busRoute.masterPort);
                            const AsicBusPortDescriptorType *pSlavePortDescriptor = 
                                ACMBus_GetPortDescriptor(pBwRequest->busRoute.slavePort);

                            if((pMasterPortDescriptor == NULL) || (pSlavePortDescriptor == NULL))
                            {
                                ADSPPM_LOG_PRINTF_4(ADSPPM_LOG_LEVEL_INFO_EXT,
                                    "NULL bus port descriptors: from %s(%u) to %s(%u)",
                                    adsppm_getBusPortName(pBwRequest->busRoute.masterPort),
                                    pBwRequest->busRoute.masterPort,
                                    adsppm_getBusPortName(pBwRequest->busRoute.slavePort),
                                    pBwRequest->busRoute.slavePort);
                                sts = Adsppm_Status_UnSupported;
                                break;
                            }
                            else
                            {
                                if((pMasterPortDescriptor->portConnection == AsicBusPort_None) ||
                                    (pSlavePortDescriptor->portConnection == AsicBusPort_None))
                                {
                                    ADSPPM_LOG_PRINTF_4(ADSPPM_LOG_LEVEL_INFO_EXT,
                                        "BW request with non-existing ports: from %s(%u) to %s(%u)",
                                        adsppm_getBusPortName(pBwRequest->busRoute.masterPort),
                                        pBwRequest->busRoute.masterPort,
                                        adsppm_getBusPortName(pBwRequest->busRoute.slavePort),
                                        pBwRequest->busRoute.slavePort);
                                    sts = Adsppm_Status_UnSupported;
                                    break;
                                }
                                else
                                {
                                    // Filter out BW values of Zero
                                    if(0 == pBwRequest->bwValue.busBwValue.bwBytePerSec)
                                    {
                                        ADSPPM_LOG_PRINTF_4(ADSPPM_LOG_LEVEL_INFO_EXT,
                                            "BW request of Zero from %s(%u) to %s(%u), exclude from aggregation",
                                            adsppm_getBusPortName(pBwRequest->busRoute.masterPort),
                                            pBwRequest->busRoute.masterPort,
                                            adsppm_getBusPortName(pBwRequest->busRoute.slavePort),
                                            pBwRequest->busRoute.slavePort);
                                    }
                                    else
                                    {
                                        // Check if at least 1 periodic client requests BW to DDR
                                        if(!gBusMgrCtx.bPeriodicClientBW2DDR)
                                        {
                                            if((Adsppm_ClientType_Periodic == pRMHandle->pAdsppmHandle->clientType) &&
                                                (AdsppmBusPort_Adsp_Master == pBwRequest->busRoute.masterPort) &&
                                                (AdsppmBusPort_Ddr_Slave == pBwRequest->busRoute.slavePort))
                                            {
                                                gBusMgrCtx.bPeriodicClientBW2DDR = TRUE;
                                            }
                                        }
                                        sts = busMgrAggregateRequest(pBwRequest);
                                    }
                                }
                            }
                        }
                    }
                }

                // Register Programming
                if(RM_Valid == pRMHandle->validFlag_Ext)
                {
                    ADSPPM_LOG_PRINTF_0(ADSPPM_LOG_LEVEL_INFO_EXT, "Register Programming");
                    if((NULL == (AdsppmBusBWRequestValueType *) (pRMHandle->pRequestData_Ext)) ||
                        (NULL == pRMHandle->pAdsppmHandle))
                    {
                        ADSPPM_LOG_PRINTF_2(ADSPPM_LOG_LEVEL_ERROR,
                            "pRequestData_Ext(%u) or pAdsppmHandle(%u) is NULL",
                            (AdsppmBusBWRequestValueType *) (pRMHandle->pRequestData_Ext),
                            pRMHandle->pAdsppmHandle);
                        sts = Adsppm_Status_BadParm;
                        break;
                    }
                    else
                    {
                        AdsppmBusBWRequestValueType *pRegBwReqData =
                            (AdsppmBusBWRequestValueType *) (pRMHandle->pRequestData_Ext);

                        // Get slave port for this core instance
                        pRegBwReqData->busRoute.slavePort = ACMBus_GetCoreSlavePort(
                            pRMHandle->pAdsppmHandle->coreId,
                            pRMHandle->pAdsppmHandle->instanceId);

                        ADSPPM_LOG_PRINTF_5(ADSPPM_LOG_LEVEL_INFO_EXT,
                            "RegProg: M=%s(%u), S=%s(%u), bw=%u",
                            adsppm_getBusPortName(pRegBwReqData->busRoute.masterPort),
                            pRegBwReqData->busRoute.masterPort,
                            adsppm_getBusPortName(pRegBwReqData->busRoute.slavePort),
                            pRegBwReqData->busRoute.slavePort,
                            (uint32) pRegBwReqData->bwValue.busBwValue.bwBytePerSec);

                        // Filter out requests with bus ports that have no connections
                        // meaning they do not exit in current chip set
                        // and requests with AdsppmBusPort_None
                        const AsicBusPortDescriptorType *pSlavePortDescriptor = 
                            ACMBus_GetPortDescriptor(pRegBwReqData->busRoute.slavePort);

                        if(pSlavePortDescriptor == NULL)
                        {
                            ADSPPM_LOG_PRINTF_2(ADSPPM_LOG_LEVEL_ERROR,
                                "NULL bus port descriptor for coreID %u instanceID %u",
                                pRMHandle->pAdsppmHandle->coreId,
                                pRMHandle->pAdsppmHandle->instanceId);
                            sts = Adsppm_Status_UnSupported;
                            break;
                        }
                        else
                        {
                            if((pSlavePortDescriptor->portConnection == AsicBusPort_None) ||
                                (pRegBwReqData->busRoute.slavePort == AdsppmBusPort_None))
                            {
                                ADSPPM_LOG_PRINTF_2(ADSPPM_LOG_LEVEL_ERROR,
                                    "Reg prog for coreID %u instanceID %u not supported",
                                    pRMHandle->pAdsppmHandle->coreId,
                                    pRMHandle->pAdsppmHandle->instanceId);
                                sts = Adsppm_Status_UnSupported;
                                break;
                            }
                        }

                        sts = busMgrAggregateRequest(pRegBwReqData);
                    }
                }

                if(Adsppm_Status_Success != sts)
                {
                    ADSPPM_LOG_PRINTF_0(ADSPPM_LOG_LEVEL_ERROR, "BW aggregation failed");
                    break;
                }

                pRMHandle = (RMHandleType *) coreUtils_Q_Next(pBWReqQ, &(pRMHandle->rmHandleQLink));
            }

            // Process Internal AHB bandwidth
            if(Adsppm_Status_Success == sts)
            {
                sts = AHBM_ProcessRequest(&(gBusMgrCtx.curAHBBwData), &(gBusMgrCtx.nonSuppressibleAhbBW));
            }
            // Process clocks
            if(Adsppm_Status_Success == sts)
            {
                sts = busMgrProcessClocks();
            }

            // Process External Bandwidth
            if(Adsppm_Status_Success == sts)
            {
                numUpdatedExtBwVotes = busMgrProcessExternalBW(&updateExtBusBwValue[0]);
            }

            // Update uSleep manager
            if(Adsppm_Status_Success == sts)
            {
                sts = busMgrUpdateUSleepMgr();
            }

            // Update the index for next iteration
            gBusMgrCtx.preCurrentIndex ^= 1;

            ADSPPM_UNLOCK_RESOURCE(Adsppm_Rsc_Id_BW);
            adsppm_unlock(gBusMgrCtx.lock);

            // Issue external bw request to hal
            if((Adsppm_Status_Success == sts) && (0 < numUpdatedExtBwVotes))
            {
                sts = Bus_IssueBWRequest(numUpdatedExtBwVotes, &updateExtBusBwValue[0]);
            }
        }
    }

    ADSPPM_LOG_FUNC_EXIT(sts);
    return sts;
}


static BUSMgrBwTypeType busMgrGetBwType(
    AsicBusPortConnectionType masterPortConnection,
    AsicBusPortConnectionType slavePortConnection)
{
    BUSMgrBwTypeType bwType = BUSMgr_Bw_None;

    if((0 != (masterPortConnection & AsicBusPort_Ext_Any)) &&
        (0 != (slavePortConnection & AsicBusPort_Ext_Any)))
    {
        bwType = BUSMgr_Bw_External_Only;
    }
    else if((0 != (masterPortConnection & AsicBusPort_Ahb_Any)) &&
        (0 != (slavePortConnection & AsicBusPort_Ahb_Any)))
    {
        bwType = BUSMgr_Bw_Internal_Only;
    }
    else if(((0 != (masterPortConnection & AsicBusPort_Ext_Any)) ||
            (0 != (masterPortConnection & AsicBusPort_Ahb_Any))) &&
        ((0 != (slavePortConnection & AsicBusPort_Ext_Any)) ||
            (0 != (slavePortConnection & AsicBusPort_Ahb_Any))))
    {
        bwType = BUSMgr_Bw_Internal_External;
    }

    ADSPPM_LOG_PRINTF_3(ADSPPM_LOG_LEVEL_INFO_EXT,
        "connectM=%u, connectS=%u, bwType=%u",
        masterPortConnection, slavePortConnection, bwType);

    return bwType;
}


static Adsppm_Status busMgrAggregateInternalBW(BUSMgr_BwDescriptorType *pBwDesc)
{
    Adsppm_Status sts = Adsppm_Status_Success;

    sts = ACM_BusBWAggregate(&(gBusMgrCtx.curAHBBwData), &(pBwDesc->bwValue));

    if(Adsppm_Status_Success != sts)
    {
        ADSPPM_LOG_PRINTF_1(ADSPPM_LOG_LEVEL_ERROR,
            "Internal BW aggregation failed: %u", sts);
    }

    // Aggregate all Non-suppressible BW requests
    // All BW requirements originating from ADSP are considered suppressible and should be excluded
    if((Adsppm_Status_Success == sts) && (AdsppmBusPort_Adsp_Master != pBwDesc->masterPort))
    {
        sts = ACM_BusBWAggregate(&(gBusMgrCtx.nonSuppressibleAhbBW), &(pBwDesc->bwValue));
        if(Adsppm_Status_Success != sts)
        {
            ADSPPM_LOG_PRINTF_1(ADSPPM_LOG_LEVEL_ERROR,
                "Internal nonSupressible BW aggregation failed: %u", sts);
        }
    }

    return sts;
}


static Adsppm_Status busMgrAggregateExternalBW(BUSMgr_BwDescriptorType *pBwDesc)
{
    Adsppm_Status sts = Adsppm_Status_Success;
    uint32 extRouteIndex = 0;

    // Search corresponding external route
    for(extRouteIndex = 0; extRouteIndex < gBusMgrCtx.extRouteNum; extRouteIndex++)
    {
        if((gBusMgrCtx.pExtRoutes[extRouteIndex].masterPort.adsppmMaster == pBwDesc->masterPort) &&
           (gBusMgrCtx.pExtRoutes[extRouteIndex].slavePort.adsppmSlave == pBwDesc->slavePort))
        {
            sts = ACM_BusBWAggregate(
                &(gBusMgrCtx.pExtBwAggregateData[gBusMgrCtx.preCurrentIndex][extRouteIndex].bwValue.busBwAbIb),
                &(pBwDesc->bwValue));
            if(Adsppm_Status_Success != sts)
            {
                ADSPPM_LOG_PRINTF_1(ADSPPM_LOG_LEVEL_ERROR,
                    "External BW aggregation failed: %u", sts);
            }
            break;
        }
    }

    if(gBusMgrCtx.extRouteNum == extRouteIndex)
    {
        ADSPPM_LOG_PRINTF_2(ADSPPM_LOG_LEVEL_ERROR,
            "Invalid external route, M=%u, S=%u",
            pBwDesc->masterPort, pBwDesc->slavePort);
        sts = Adsppm_Status_BadParm;
    }

    return sts;
}


static void busMgrVoteForAhbBusClocks(AsicBusPortConnectionType portConnection)
{
    if(portConnection & (AsicBusPort_AhbE_M | AsicBusPort_AhbE_S))
    {
        gBusMgrCtx.clockState[gBusMgrCtx.preCurrentIndex][AdsppmClk_AhbE_Hclk] = Hal_ClkRgmEnable;
    }
    if(portConnection & (AsicBusPort_AhbI_M | AsicBusPort_AhbI_S))
    {
        gBusMgrCtx.clockState[gBusMgrCtx.preCurrentIndex][AdsppmClk_AhbI_Hclk] = Hal_ClkRgmEnable;
    }
    if(portConnection & (AsicBusPort_AhbX_M | AsicBusPort_AhbX_S))
    {
        gBusMgrCtx.clockState[gBusMgrCtx.preCurrentIndex][AdsppmClk_AhbX_Hclk] = Hal_ClkRgmEnable;
    }
}


static Adsppm_Status busMgrVoteForRegProgClock(AdsppmClkIdType clkId)
{
    Adsppm_Status sts = Adsppm_Status_Success;
    const AsicClkDescriptorType *pClkDesc = ACMClk_GetClockDescriptor(clkId);

    if(NULL == pClkDesc)
    {
        ADSPPM_LOG_PRINTF_1(ADSPPM_LOG_LEVEL_ERROR,
            "Clock descriptor is NULL, clkId=%u", clkId);
        sts = Adsppm_Status_Failed;
    }
    else
    {
        switch(pClkDesc->clkCntlType)
        {
        case AsicClk_CntlSW:
            gBusMgrCtx.clockState[gBusMgrCtx.preCurrentIndex][clkId] = Hal_ClkRgmEnable;
            break;

        case AsicClk_CntlSW_DCG:
            if(AsicFeatureState_Enabled != ACM_GetFeatureStatus(AsicFeatureId_Ahb_DCG))
            {
                gBusMgrCtx.clockState[gBusMgrCtx.preCurrentIndex][clkId] = Hal_ClkRgmEnable;
            }
            break;

        default:
            break;
        }
    }

    return sts;
}


static Adsppm_Status busMgrAggregateClocks(BUSMgr_BwDescriptorType *pBwDesc)
{
    Adsppm_Status sts = Adsppm_Status_Success;
    ADSPPM_LOG_PRINTF_3(ADSPPM_LOG_LEVEL_INFO_EXT,
        "clkM=%u, clkS=%u, clkA=%u",
        pBwDesc->pMPortDescriptor->busClk,
        pBwDesc->pSPortDescriptor->busClk,
        pBwDesc->pAPortDescriptor->busClk);

    if(AdsppmBusBWOperation_RegAccess == pBwDesc->bwOperation)
    {
        uint32 index = 0;
        sts = busMgrVoteForRegProgClock(pBwDesc->pMPortDescriptor->busClk);

        // Aggregate register programming clocks voting from Slave Port
        ADSPPM_LOG_PRINTF_1(ADSPPM_LOG_LEVEL_INFO_EXT,
            "num of regProgClocks=%u",
            pBwDesc->pSPortDescriptor->regProgClocks.numClocks);

        for(index = 0;
            (Adsppm_Status_Success == sts) &&
                (index < pBwDesc->pSPortDescriptor->regProgClocks.numClocks);
            index++)
        {
            sts = busMgrVoteForRegProgClock(pBwDesc->pSPortDescriptor->regProgClocks.pClocks[index]);
        }
    }
    else // pBwDesc->bwOperation == AdsppmBusBWOperation_BW
    {
         gBusMgrCtx.clockState[gBusMgrCtx.preCurrentIndex][pBwDesc->pMPortDescriptor->busClk] = Hal_ClkRgmEnable;
         gBusMgrCtx.clockState[gBusMgrCtx.preCurrentIndex][pBwDesc->pSPortDescriptor->busClk] = Hal_ClkRgmEnable;
         gBusMgrCtx.clockState[gBusMgrCtx.preCurrentIndex][pBwDesc->pAPortDescriptor->busClk] = Hal_ClkRgmEnable;
    }

    if(Adsppm_Status_Success == sts)
    {
        busMgrVoteForAhbBusClocks(pBwDesc->pMPortDescriptor->portConnection);
        busMgrVoteForAhbBusClocks(pBwDesc->pSPortDescriptor->portConnection);
        busMgrVoteForAhbBusClocks(pBwDesc->pAPortDescriptor->portConnection);
    }

    return sts;
}


static Adsppm_Status busMgrAggregateRequest(AdsppmBusBWRequestValueType *pBwRequest)
{
    Adsppm_Status sts = Adsppm_Status_Success;
    BUSMgr_BwDescriptorType bwDesc;
    BUSMgrBwTypeType busMgrBwType = BUSMgr_Bw_None;

    bwDesc.masterPort = pBwRequest->busRoute.masterPort;
    bwDesc.slavePort = pBwRequest->busRoute.slavePort;
    bwDesc.accessPort = AdsppmBusPort_None;
    bwDesc.pMPortDescriptor = ACMBus_GetPortDescriptor(bwDesc.masterPort);
    bwDesc.pSPortDescriptor = ACMBus_GetPortDescriptor(bwDesc.slavePort);
    bwDesc.pAPortDescriptor = ACMBus_GetPortDescriptor(bwDesc.accessPort);
    bwDesc.bwOperation = pBwRequest->bwOperation;
    bwDesc.bwValue = pBwRequest->bwValue;

    ADSPPM_LOG_PRINTF_4(ADSPPM_LOG_LEVEL_INFO_EXT,
        "M=%s(%u), S=%s(%u)",
        adsppm_getBusPortName(bwDesc.masterPort), bwDesc.masterPort,
        adsppm_getBusPortName(bwDesc.slavePort), bwDesc.slavePort);

    if((NULL == bwDesc.pMPortDescriptor) ||
        (NULL == bwDesc.pSPortDescriptor) ||
        (NULL == bwDesc.pAPortDescriptor))
    {
        ADSPPM_LOG_PRINTF_6(ADSPPM_LOG_LEVEL_ERROR,
            "Bus route descriptor is NULL, M=%s(%u), S=%s(%u), A=%s(%u)",
            adsppm_getBusPortName(bwDesc.masterPort), bwDesc.masterPort,
            adsppm_getBusPortName(bwDesc.slavePort), bwDesc.slavePort,
            adsppm_getBusPortName(bwDesc.accessPort), bwDesc.accessPort);
        sts = Adsppm_Status_BadParm;
    }
    else
    {
        busMgrBwType = busMgrGetBwType(
            bwDesc.pMPortDescriptor->portConnection,
            bwDesc.pSPortDescriptor->portConnection);

        switch(busMgrBwType)
        {
        case BUSMgr_Bw_None:
            ADSPPM_LOG_PRINTF_2(ADSPPM_LOG_LEVEL_ERROR,
                "None BW type, connectM=%u, connectS=%u",
                bwDesc.pMPortDescriptor->portConnection,
                bwDesc.pSPortDescriptor->portConnection);
            sts = Adsppm_Status_Failed;
            break;

        case BUSMgr_Bw_Internal_External:
            if(0 != (AsicBusPort_Ext_M & bwDesc.pMPortDescriptor->portConnection))
            {
                bwDesc.slavePort = bwDesc.pSPortDescriptor->accessPort;
                bwDesc.accessPort = bwDesc.slavePort;
            }
            else if(0 != (AsicBusPort_Ext_S & bwDesc.pSPortDescriptor->portConnection))
            {
                bwDesc.masterPort = bwDesc.pMPortDescriptor->accessPort;
                bwDesc.accessPort = bwDesc.masterPort;
            }
            bwDesc.pAPortDescriptor = ACMBus_GetPortDescriptor(bwDesc.accessPort);
            if(NULL == bwDesc.pAPortDescriptor)
            {
                ADSPPM_LOG_PRINTF_1(ADSPPM_LOG_LEVEL_ERROR,
                    "Access port descriptor is NULL, accessPort:%u",
                    bwDesc.accessPort);
                sts = Adsppm_Status_Failed;
            }

            if(Adsppm_Status_Success == sts)
            {
                sts = busMgrAggregateInternalBW(&bwDesc);
            }
            if(Adsppm_Status_Success == sts)
            {
                sts = busMgrAggregateClocks(&bwDesc);
            }
            if(Adsppm_Status_Success == sts)
            {
                sts = busMgrAggregateExternalBW(&bwDesc);
            }
            break;

        case BUSMgr_Bw_Internal_Only:
            sts = busMgrAggregateInternalBW(&bwDesc);
            if(Adsppm_Status_Success == sts)
            {
                sts = busMgrAggregateClocks(&bwDesc);
            }
            break;

        case BUSMgr_Bw_External_Only:
            sts = busMgrAggregateExternalBW(&bwDesc);
            break;

        default:
             break;
        }
    }

    return sts;
}

