/*
 *@file requestmgr.c - adsppm request manager implementation

INITIALIZATION AND SEQUENCING REQUIREMENTS:  N/A

* Copyright (c) 2014 Qualcomm Technologies, Inc.
* All Rights Reserved.
* Qualcomm Technologies, Inc. Confidential and Proprietary.

==============================================================================

                           EDIT HISTORY FOR MODULE

$Header: //components/rel/core.adsp/2.6.1/power/adsppm/src/common/core/src/requestmgr.c#1 $

This section contains comments describing changes made to the module.
Notice that changes are listed in reverse chronological order.

when       who     what, where, why
--------   ---     ---------------------------------------------------------------
07/20/11   alisonc      Initial version
===================================================================================*/

#include "adsppm.h"
#include "adsppm_utils.h"
#include "core.h"
#include "core_internal.h"
#include "coreUtils.h"
#include "requestmgr.h"
#include "clkmgr.h"
#include "mipsmgr.h"
#include "busmgr.h"
#include "pwrmgr.h"
#include "latencymgr.h"
#include "thermalmgr.h"
#include "stdlib.h"
#include "mempwrmgr.h"


static void freeSetParameter(AdsppmHandleType *pAdsppmHandle);

/**
 * @fn findReqMgrHandle - find the findReqMgrHandle in rscReqQ
 */
int findReqMgrHandle(RMHandleType *pRMHandle, uint32 *clientId)
{
    int match = 0;
    if(pRMHandle->clientId == *clientId)
    {
        match = 1;
    }
    return match;
}


/**
 * @fn getRequestDataSize - return size of request data structure per resource
 */
uint32 getRequestDataSize(AdsppmRscIdType resourceId)
{
    uint32 result = 0;
    switch(resourceId)
    {
    case Adsppm_Rsc_Id_Power:
        result = sizeof(uint32);
        break;
    case Adsppm_Rsc_Id_Core_Clk:
        result = sizeof(AdsppmClkRequestType);
        break;
    case Adsppm_Rsc_Id_BW:
        result = sizeof(AdsppmBwReqType);
        break;
    case Adsppm_Rsc_Id_Mips:
        result = sizeof(AdsppmMipsRequestType);
        break;
    case Adsppm_Rsc_Id_Sleep_Latency:
        result = sizeof(uint32);
        break;
    case Adsppm_Rsc_Id_Thermal:
        result = sizeof(uint32);
        break;
    case Adsppm_Rsc_Id_MemPower:
        result = sizeof(AdsppmMemPowerReqParamType);
        break;
    case Adsppm_Rsc_Id_Core_Clk_Domain:
        result = sizeof(AdsppmClkDomainReqType);
        break;
    default :
        break;
    }
    return result;
}


/**
 * @fn getRequestData_ExtSize - return size of extended request data structure per resource
 */
uint32 getRequestData_ExtSize(AdsppmRscIdType resourceId)
{
    uint32 result = 0;
    switch(resourceId)
    {
    case Adsppm_Rsc_Id_Power:
        break;
    case Adsppm_Rsc_Id_Core_Clk:
        break;
    case Adsppm_Rsc_Id_BW:
        result = sizeof(AdsppmBusBWRequestValueType);
        break;
    case Adsppm_Rsc_Id_Mips:
        break;
    case Adsppm_Rsc_Id_Sleep_Latency:
        break;
    case Adsppm_Rsc_Id_Thermal:
        break;
    case Adsppm_Rsc_Id_MemPower:
        break;
    case Adsppm_Rsc_Id_Core_Clk_Domain:
        break;
    default :
        break;
    }
    return result;
}


/**
 * @fn RM_Init
 * @Brief - init mutex for RM
 * @param input AdsppmCoreIdType coreId - core Id in LPASS
 * @param input uint32 *callback - call back function for this client.
 * @return uint32 clientId
 */
Adsppm_Status RM_Init(void)
{
    Adsppm_Status sts = Adsppm_Status_Success;
    AdsppmCoreCtxType *pAdsppmCoreCtx = GetAdsppmCoreContext();
    AdsppmRscIdType index;
    ADSPPM_LOG_FUNC_ENTER;
    coreUtils_Q_Init(&pAdsppmCoreCtx->adsppmHandleQ);
    for(index = Adsppm_Rsc_Id_Power; index < Adsppm_Rsc_Id_Max; index++)
    {
        coreUtils_Q_Init(&pAdsppmCoreCtx->rscReqQ[index-1]);
        if(DAL_SUCCESS != DALSYS_SyncCreate(DALSYS_SYNC_ATTR_RESOURCE, (DALSYSSyncHandle *)&pAdsppmCoreCtx->resourceLock[index-1], NULL))
        {
            sts = Adsppm_Status_Failed;
            break;
        }
    }
    ADSPPM_LOG_FUNC_EXIT(sts);
    return sts;
}


/**
 * @fn generateClientId
 * @brief - generate ADSPPM client ID
 * @param clientId - uint32 pointer to location of client ID
 * @return ADSPPM status
 */
Adsppm_Status generateClientId(uint32 *clientId)
{
    Adsppm_Status sts = Adsppm_Status_Success;
    AdsppmCoreCtxType *pAdsppmCoreCtx = GetAdsppmCoreContext();
    if(MAX_NUM_OF_ADSPPM_CLIENTS == pAdsppmCoreCtx->clientIdNum)
    {
        uint32 index = 0;
        for(index = 0; index < MAX_NUM_OF_ADSPPM_CLIENTS; index++)
        {
            if(0 == (pAdsppmCoreCtx->clientIdNumMask & (1ULL << index)))
            {
                *clientId = index + 1;
                break;
            }
        }
        if(MAX_NUM_OF_ADSPPM_CLIENTS == index)
        {
            sts = Adsppm_Status_Failed;
            ADSPPM_LOG_PRINTF_2(ADSPPM_LOG_LEVEL_ERROR, "can't find available clientID max=%u, numofclients=%u", MAX_NUM_OF_ADSPPM_CLIENTS, pAdsppmCoreCtx->numOfRegisteredClients);
        }
    }
    else
    {
        pAdsppmCoreCtx->clientIdNum++;
        *clientId = pAdsppmCoreCtx->clientIdNum;
    }
    if(Adsppm_Status_Success == sts)
    {
        pAdsppmCoreCtx->clientIdNumMask |= (1ULL << (*clientId - 1));
    }
    return sts;
}


/**
 * @fn RM_CreateClient
 * @Brief - register a new client, save all informatin to client handle and return clientID.
 * @param input AdsppmCoreIdType coreId - core Id in LPASS
 * @param input name - client name
 * @param input uint32 *callback - call back function for this client.
 * @return uint32 clientId
 */
uint32 RM_CreateClient(AdsppmCoreIdType coreId, AdsppmInstanceIdType instanceId, char *name, void *callback, AdsppmClientTypeType clientType)
{
    Adsppm_Status sts = Adsppm_Status_Success;
    AdsppmCoreCtxType *pAdsppmCoreCtx = GetAdsppmCoreContext();
    const AsicCoreDescType *pCoreDesc = ACM_GetCoreDescriptor(coreId);
    uint32 clientId = 0;
    AdsppmRscIdType resourceId = Adsppm_Rsc_Id_None;
    AdsppmHandleType *pAdsppmHandle = NULL;
    RMHandleType *pRMHandle = NULL;
    ADSPPM_LOG_FUNC_ENTER;

    if((Adsppm_Core_Id_None == coreId) || (Adsppm_Core_Id_Max <= coreId) ||
            (Adsppm_Instance_Id_None == instanceId) || (Adsppm_Instance_Id_Max <= instanceId) ||
            (NULL == name) || (NULL == pCoreDesc))
    {
        sts = Adsppm_Status_BadParm;
        ADSPPM_LOG_PRINTF_3(ADSPPM_LOG_LEVEL_ERROR, "Invalid coreId=%u or instanceId=%u requested by client %s", coreId, instanceId, name);
    }
    else
    {
        if(pCoreDesc->numInstances < instanceId)
        {
            sts = Adsppm_Status_BadParm;
            ADSPPM_LOG_PRINTF_2(ADSPPM_LOG_LEVEL_ERROR, "Invalid instanceId=%u requested by client %s", instanceId, name);
        }
        else
        {
            ADSPPM_LOG_PRINTF_2(ADSPPM_LOG_LEVEL_INFO, "coreId=%u instanceId=%u", coreId, instanceId);
            if(NULL == pAdsppmCoreCtx->lock)
            {
                sts = Adsppm_Status_NotInitialized;
                ADSPPM_LOG_PRINTF_0(ADSPPM_LOG_LEVEL_ERROR, "Not initialized");
            }
            else
            {
                if(MAX_NUM_OF_ADSPPM_CLIENTS == pAdsppmCoreCtx->numOfRegisteredClients)
                {
                    /* no more room for clients */
                    sts = Adsppm_Status_Failed;
                    ADSPPM_LOG_PRINTF_2(ADSPPM_LOG_LEVEL_ERROR, "Registered clients exceed max=%u, clients=%u", MAX_NUM_OF_ADSPPM_CLIENTS, pAdsppmCoreCtx->numOfRegisteredClients);
                }
                else
                {
                    adsppm_lock(pAdsppmCoreCtx->lock);
                    //allocate client handle and put into clienthandle queue
                    pAdsppmHandle = malloc(sizeof(AdsppmHandleType));
                    if(NULL == pAdsppmHandle)
                    {
                        sts = Adsppm_Status_Failed;
                        ADSPPM_LOG_PRINTF_0(ADSPPM_LOG_LEVEL_ERROR, "Malloc failed for pAdsppmHandle");
                    }
                    else
                    {
                        coreUtils_Q_Link(pAdsppmHandle, &(pAdsppmHandle->adsppmHandleQLink));
                        coreUtils_Q_Put(&(pAdsppmCoreCtx->adsppmHandleQ), &(pAdsppmHandle->adsppmHandleQLink));
                        sts = generateClientId(&clientId);
                        if(Adsppm_Status_Success == sts)
                        {
                            pAdsppmHandle->clientId = clientId;
                            pAdsppmHandle->coreId = coreId;
                            pAdsppmHandle->instanceId = instanceId;
                            pAdsppmHandle->ADSPPM_Callback = callback;
                            strlcpy (pAdsppmHandle->clientName, name, MAX_ADSPPM_CLIENT_NAME);
                            pAdsppmHandle->pSetParamConfig = NULL;
                            pAdsppmHandle->clientType = clientType;
                            ADSPPM_LOG_PRINTF_3(ADSPPM_LOG_LEVEL_INFO, "Client %s (type %u) registered with ID %u", pAdsppmHandle->clientName, pAdsppmHandle->clientType, clientId);
                            pAdsppmCoreCtx->numOfRegisteredClients++;
                        }
                    }

                    if(Adsppm_Status_Success == sts)
                    {
                        //allocate RMCtx for each resource and put into resource RMCtx Queue
                        for(resourceId = Adsppm_Rsc_Id_Power; resourceId < Adsppm_Rsc_Id_Max; resourceId++)
                        {
                            if(NULL == pAdsppmCoreCtx->resourceLock[resourceId-1])
                            {
                                sts = Adsppm_Status_NotInitialized;
                                ADSPPM_LOG_PRINTF_0(ADSPPM_LOG_LEVEL_ERROR, "resourceLock[resourceId-1] is NULL");
                            }
                            else
                            {
                                ADSPPM_LOCK_RESOURCE(resourceId);
                                pRMHandle = malloc(sizeof(RMHandleType));
                                if(NULL == pRMHandle)
                                {
                                    sts = Adsppm_Status_Failed;
                                    ADSPPM_LOG_PRINTF_0(ADSPPM_LOG_LEVEL_ERROR, "Malloc failed for pRMHandle");
                                    break;
                                }
                                else
                                {
                                    memset(pRMHandle, 0, sizeof(RMHandleType));
                                    pRMHandle->pRequestData = malloc(getRequestDataSize(resourceId));
                                    if(NULL == pRMHandle->pRequestData)
                                    {
                                        sts = Adsppm_Status_Failed;
                                        ADSPPM_LOG_PRINTF_0(ADSPPM_LOG_LEVEL_ERROR, "Malloc failed for pRMHandle->pRequestData");
                                        free(pRMHandle);
                                        break;
                                    }
                                    else
                                    {
                                        memset(pRMHandle->pRequestData, 0, getRequestDataSize(resourceId));
                                        if(getRequestData_ExtSize(resourceId))
                                        {
                                            pRMHandle->pRequestData_Ext = malloc(getRequestData_ExtSize(resourceId));
                                            if(NULL == pRMHandle->pRequestData_Ext)
                                            {
                                                 sts = Adsppm_Status_Failed;
                                                 ADSPPM_LOG_PRINTF_0(ADSPPM_LOG_LEVEL_ERROR, "Malloc failed for pRMHandle->pRequestData");
                                                 free(pRMHandle->pRequestData);
                                                 free(pRMHandle);
                                                 break;
                                            }
                                            else
                                            {
                                                memset(pRMHandle->pRequestData_Ext, 0, getRequestData_ExtSize(resourceId));
                                            }
                                        }
                                        pRMHandle->clientId = clientId;
                                        pRMHandle->rmRscId = resourceId;
                                        pRMHandle->pAdsppmHandle = pAdsppmHandle;
                                        coreUtils_Q_Link(pRMHandle, &pRMHandle->rmHandleQLink);
                                        coreUtils_Q_Put(&(pAdsppmCoreCtx->rscReqQ[resourceId-1]), &pRMHandle->rmHandleQLink);
                                    }
                                }
                                ADSPPM_UNLOCK_RESOURCE(resourceId);
                            }
                        }
                    }
                    adsppm_unlock(pAdsppmCoreCtx->lock);
                    if(Adsppm_Status_Success != sts)
                    {
                        RM_DeleteClient(clientId);
                        clientId = 0;
                    }
                }
            } /* lock null failed */
        }
    } /* parameter check failed */

    ADSPPM_LOG_FUNC_EXIT(clientId);
    return clientId;
}


/**
 * @fn RM_GetClientInfo
 * @Brief -  based on clientid, retrieve information about coreID and callback function.
 * @param input uint32 clientId - client ID.
 * @param output AdsppmCoreIdType *pCoreId - core ID that client registered.
 * @param output uint32 *callback - client call back function pointer.
 * @return Adsppm_Status_BadParm
 * @return Adsppm_Status_Success
 */
Adsppm_Status RM_GetClientInfo(uint32 clientId, AdsppmCoreIdType *pCoreId, uint32 *callback, AdsppmClientTypeType *clientType)
{
    Adsppm_Status sts = Adsppm_Status_Success;
    ADSPPM_LOG_FUNC_ENTER;
    if(0 == clientId)
    {
        sts = Adsppm_Status_BadParm;
    }
    else
    {
        sts = Adsppm_Status_UnSupported;
        //*pCoreId = gAdsppmCtx.pAdsppmHandle[clientId-1].coreId;
        //callback = gAdsppmCtx.pAdsppmHandle[clientId-1].ADSPPM_Callback;
    }
    ADSPPM_LOG_FUNC_EXIT(sts);
    return sts;
}


/**
 * @fn RM_GetResourceInfo
 * @Brief -  based on clientid, retrieve information about coreID and callback function.
 * @param input uint32 clientId - client ID.
 * @param output AdsppmCoreIdType *pCoreId - core ID that client registered.
 * @param output uint32 *callback - client call back function pointer.
 * @return Adsppm_Status_BadParm
 * @return Adsppm_Status_Success
 */
Adsppm_Status RM_GetResourceInfo(AdsppmRscIdType rsc_Id, void *pInfo, AdsppmInfoType infoType)
{
    Adsppm_Status sts = Adsppm_Status_Success;
    AsicFeatureDescType *pDesc = NULL;
    ADSPPM_LOG_FUNC_ENTER;
    if(NULL == pInfo)
    {
        sts = Adsppm_Status_NullPointer;
        ADSPPM_LOG_PRINTF_0(ADSPPM_LOG_LEVEL_ERROR, "NULL pointer for pInfo");
    }
    else
    {
        switch(rsc_Id)
        {
        case Adsppm_Rsc_Id_Core_Clk:
            if(Adsppm_Info_Type_Current_Value == infoType)
            {
                sts = CLK_GetInfo((AdsppmInfoClkFreqType *)pInfo);
            }
            else if(Adsppm_Info_Type_Max_Value == infoType)
            {
                pDesc = ACM_GetFeatureDescriptor(AsicFeatureId_CoreClk_Scaling);
                ((AdsppmInfoClkFreqType *)pInfo)->clkFreqHz = pDesc->max;
            }
            else
            {
                sts = Adsppm_Status_UnSupported;
            }
            break;
        case Adsppm_Rsc_Id_Mips:
            if(Adsppm_Info_Type_Max_Value == infoType)
            {
                pDesc = ACM_GetFeatureDescriptor(AsicFeatureId_Adsp_Clock_Scaling);
                *(uint32 *)pInfo = pDesc->max;
            }
            else
            {
                sts = Adsppm_Status_UnSupported;
            }
            break;
        case Adsppm_Rsc_Id_BW:
            if(Adsppm_Info_Type_Max_Value == infoType)
            {
                pDesc = ACM_GetFeatureDescriptor(AsicFeatureId_Ahb_Scaling);
                *(uint64 *)pInfo = pDesc->max;
            }
            else
            {
                sts = Adsppm_Status_UnSupported;
            }
            break;
        default:
            sts = Adsppm_Status_UnSupported;
            break;
        }
    }
    ADSPPM_LOG_FUNC_EXIT(sts);
    return sts;
}


/**
 * @fn RM_DeleteClient
 * @Brief -  mark client as invalid and free all client’s resources.
 * @param input uint32 clientId - client ID.
 * @return Adsppm_Status_BadParm
 * @return Adsppm_Status_Success
 */
Adsppm_Status RM_DeleteClient(uint32 clientId)
{
    Adsppm_Status sts = Adsppm_Status_Success;
    AdsppmCoreCtxType *pAdsppmCoreCtx = GetAdsppmCoreContext();
    AdsppmRscIdType index;
    RMHandleType *pRMHandle = NULL;
    AdsppmHandleType *pAdsppmHandle = NULL;
    ADSPPM_LOG_FUNC_ENTER;
    ADSPPM_LOG_PRINTF_1(ADSPPM_LOG_LEVEL_INFO, "Delete clientId=%u", clientId);

    if(0 == clientId)
    {
        sts = Adsppm_Status_BadParm;
        ADSPPM_LOG_PRINTF_0(ADSPPM_LOG_LEVEL_ERROR, "Invalid ClientId 0");
    }
    else
    {
        if(NULL == pAdsppmCoreCtx->lock)
        {
            sts = Adsppm_Status_NotInitialized;
            ADSPPM_LOG_PRINTF_0(ADSPPM_LOG_LEVEL_ERROR, "Not initialized");
        }
        else
        {
            adsppm_lock(pAdsppmCoreCtx->lock);
            pAdsppmHandle = coreUtils_Q_LinearSearch(&pAdsppmCoreCtx->adsppmHandleQ, (coreUtils_Q_CompareFuncType)findAdsppmHandle, (void *)&clientId);
            if(NULL != pAdsppmHandle)
            {
                /* release resource */
                for(index = Adsppm_Rsc_Id_Power; index < Adsppm_Rsc_Id_Max; index++)
                {
                    if(NULL == pAdsppmCoreCtx->resourceLock[index-1])
                    {
                        sts = Adsppm_Status_NotInitialized;
                        ADSPPM_LOG_PRINTF_0(ADSPPM_LOG_LEVEL_ERROR, "resourceLock[index-1] is NULL");
                    }
                    else
                    {
                        ADSPPM_LOCK_RESOURCE(index);
                        pRMHandle = coreUtils_Q_LinearSearch(&(pAdsppmCoreCtx->rscReqQ[index-1]), (coreUtils_Q_CompareFuncType)findReqMgrHandle, (void *)&clientId);
                        if(NULL != pRMHandle)
                        {
                            pRMHandle->validFlag = RM_InValid;
                            if(NULL != pRMHandle->pRequestData)
                            {
                                free(pRMHandle->pRequestData);
                                pRMHandle->pRequestData = NULL;
                            }
                            pRMHandle->validFlag_Ext = RM_InValid;
                            if(NULL != pRMHandle->pRequestData_Ext)
                            {
                                free(pRMHandle->pRequestData_Ext);
                                pRMHandle->pRequestData_Ext = NULL;
                            }
                            coreUtils_Q_Delete(&(pAdsppmCoreCtx->rscReqQ[index-1]), &pRMHandle->rmHandleQLink);
                            free(pRMHandle);
                        }
                        ADSPPM_UNLOCK_RESOURCE(index);
                    }
                }
                /* free set paramter memory*/
                freeSetParameter(pAdsppmHandle);
                /* set client handle to invalid */
                coreUtils_Q_Delete(&pAdsppmCoreCtx->adsppmHandleQ, &pAdsppmHandle->adsppmHandleQLink);
                free(pAdsppmHandle);
            }
            else
            {
                sts = Adsppm_Status_Failed;
                ADSPPM_LOG_PRINTF_1(ADSPPM_LOG_LEVEL_ERROR, "can't find handle for clientid=%u", clientId);
            }
            /* Update the counter for registered clients */
            pAdsppmCoreCtx->clientIdNumMask = pAdsppmCoreCtx->clientIdNumMask & (~(1ULL << (clientId -1)));
            pAdsppmCoreCtx->numOfRegisteredClients--;
            adsppm_unlock(pAdsppmCoreCtx->lock);
        }
    } /* client id point out of range? */

    ADSPPM_LOG_FUNC_EXIT(sts);
    return sts;
}


/**
 * @fn RM_AddRequest
 * @Brief - fill in the client’s request data for the specified resource and mark the request as valid.
 * @param input uint32 clientId - client ID.
 * @param input AdsppmRscIdType resourceId - resource ID that client request.
 * @param input void* pAdsppmReqData - pointer for request data, it'll cast to different data structure based on resource ID.
 * @param input uint32 extData - if non-zero extended data will be updated instead of request data.
 * @return Adsppm_Status_BadParm
 * @return Adsppm_Status_NotInitialized
 * @return Adsppm_Status_Success
 */
Adsppm_Status RM_AddRequest(uint32 clientId, AdsppmRscIdType resourceId, void *pAdsppmReqData, uint32 extData)
{
    Adsppm_Status sts = Adsppm_Status_Success;
    AdsppmCoreCtxType *pAdsppmCoreCtx = GetAdsppmCoreContext();
    RMHandleType *pRMHandle = NULL;
    ADSPPM_LOG_FUNC_ENTER;

    if((0 == clientId) || (Adsppm_Rsc_Id_None == resourceId) || (Adsppm_Rsc_Id_Max <= resourceId) || (NULL == pAdsppmReqData))
    {
        sts = Adsppm_Status_BadParm;
        ADSPPM_LOG_PRINTF_2(ADSPPM_LOG_LEVEL_ERROR, "Invalid clientId or resourceId,clientId=%u, resourceId=%u", clientId, resourceId);
    }
    else
    {
        if(NULL == pAdsppmCoreCtx->resourceLock[resourceId-1])
        {
            sts = Adsppm_Status_NotInitialized;
            ADSPPM_LOG_PRINTF_0(ADSPPM_LOG_LEVEL_ERROR, "pAdsppmCoreCtx->resourceLock[resourceId-1] is NULL");
        }
        else
        {
            ADSPPM_LOCK_RESOURCE(resourceId);
            pRMHandle = coreUtils_Q_LinearSearch(&(pAdsppmCoreCtx->rscReqQ[resourceId-1]), (coreUtils_Q_CompareFuncType)findReqMgrHandle, (void *)&clientId);
            if(NULL == pRMHandle)
            {
                sts = Adsppm_Status_BadParm;
                ADSPPM_LOG_PRINTF_2(ADSPPM_LOG_LEVEL_ERROR, "can't find RMHandle: clientId=%u, resourceId=%u", clientId, resourceId);
            }
            else
            {
                if(NULL == pRMHandle->pAdsppmHandle)
                {
                    sts = Adsppm_Status_BadParm;
                    ADSPPM_LOG_PRINTF_2(ADSPPM_LOG_LEVEL_ERROR, "pAdsppmHandle is NULL: clientId=%u, resourceId=%u", clientId, resourceId);
                }
                else
                {
                    ADSPPM_LOG_PRINTF_3(ADSPPM_LOG_LEVEL_INFO, "Adding request: clientId=%u (%s), resourceId=%u", clientId, pRMHandle->pAdsppmHandle->clientName, resourceId);
                    if((pRMHandle->clientId == clientId) && (pRMHandle->rmRscId == resourceId))
                    {
                        //the first time new resource request from client ID, need allocate item for that
                        if(0 == extData)
                        {
                            if(NULL != pRMHandle->pRequestData)
                            {
                                memscpy(pRMHandle->pRequestData, getRequestDataSize(resourceId), pAdsppmReqData, getRequestDataSize(resourceId));
                                pRMHandle->validFlag = RM_Valid;
                                ADSPPM_LOG_PRINTF_3(ADSPPM_LOG_LEVEL_INFO_EXT, "Set request valid for clientId=%u (%s), resourceId=%u", clientId, pRMHandle->pAdsppmHandle->clientName, resourceId);
                            }
                        }
                        else
                        {
                            if(NULL != pRMHandle->pRequestData_Ext)
                            {
                                memscpy(pRMHandle->pRequestData_Ext, getRequestData_ExtSize(resourceId), pAdsppmReqData, getRequestData_ExtSize(resourceId));
                                pRMHandle->validFlag_Ext = RM_Valid;
                                ADSPPM_LOG_PRINTF_3(ADSPPM_LOG_LEVEL_INFO_EXT, "Set ext request valid for clientId=%u (%s), resourceId=%u", clientId, pRMHandle->pAdsppmHandle->clientName, resourceId);
                            }
                        }
                    }
                    else
                    {
                        sts = Adsppm_Status_BadParm;
                        ADSPPM_LOG_PRINTF_2(ADSPPM_LOG_LEVEL_INFO_EXT, "release request with invalid clientId=%u, resourceid=%u", clientId, resourceId);
                    }
                }
            }
            ADSPPM_UNLOCK_RESOURCE(resourceId);
        }
    }

    ADSPPM_LOG_FUNC_EXIT(sts);
    return sts;
}


/**@fn RM_ReleaseRequest
 * @Brief - mark request for the client/resource pair as invalid.
 * @param input uint32 clientId - client ID.
 * @param input AdsppmRscIdType resourceId - resource ID that client request.
 * @param input uint32 extData - if non-zero extended data will be updated instead of request data.
 * @return Adsppm_Status_BadParm
 * @return Adsppm_Status_Success
 */
Adsppm_Status RM_ReleaseRequest(uint32 clientId, AdsppmRscIdType resourceId, uint32 extData)
{
    Adsppm_Status sts = Adsppm_Status_Success;
    AdsppmCoreCtxType *pAdsppmCoreCtx = GetAdsppmCoreContext();
    RMHandleType *pRMHandle = NULL;
    ADSPPM_LOG_FUNC_ENTER;

    if((0 == clientId) || (0 == resourceId) || (Adsppm_Rsc_Id_Max-1 < resourceId))
    {
        sts = Adsppm_Status_BadParm;
        ADSPPM_LOG_PRINTF_2(ADSPPM_LOG_LEVEL_ERROR, "Invalid clientId or resourceId: clientId=%u, resourceId=%u", clientId, resourceId);
    }
    else
    {
        if(NULL == pAdsppmCoreCtx->resourceLock[resourceId-1])
        {
            sts = Adsppm_Status_NotInitialized;
            ADSPPM_LOG_PRINTF_0(ADSPPM_LOG_LEVEL_ERROR, "resourceLock[resourceId-1] is NULL");
        }
        else
        {
            ADSPPM_LOCK_RESOURCE(resourceId);
            pRMHandle = coreUtils_Q_LinearSearch(&(pAdsppmCoreCtx->rscReqQ[resourceId-1]), (coreUtils_Q_CompareFuncType)findReqMgrHandle, (void *)&clientId);
            if(NULL == pRMHandle)
            {
                sts = Adsppm_Status_BadParm;
                ADSPPM_LOG_PRINTF_2(ADSPPM_LOG_LEVEL_ERROR, "can't find RMCtx: clientId=%u, resourceId=%u", clientId, resourceId);
            }
            else
            {
                if(NULL == pRMHandle->pAdsppmHandle)
                {
                    sts = Adsppm_Status_BadParm;
                    ADSPPM_LOG_PRINTF_2(ADSPPM_LOG_LEVEL_ERROR, "pAdsppmHandle is NULL: clientId=%u, resourceId=%u", clientId, resourceId);
                }
                else
                {
                    ADSPPM_LOG_PRINTF_3(ADSPPM_LOG_LEVEL_INFO, "Releasing request: clientId=%u (%s), resourceId=%u", clientId, pRMHandle->pAdsppmHandle->clientName, resourceId);
                    if((pRMHandle->clientId == clientId) && (pRMHandle->rmRscId == resourceId))
                    {
                        if(0 == extData)
                        {
                            pRMHandle->validFlag = RM_InValid;
                            ADSPPM_LOG_PRINTF_3(ADSPPM_LOG_LEVEL_INFO_EXT, "Set request to invalid: clientId=%u (%s), resourceId=%u", clientId, pRMHandle->pAdsppmHandle->clientName, resourceId);
                        }
                        else
                        {
                            pRMHandle->validFlag_Ext = RM_InValid;
                            ADSPPM_LOG_PRINTF_3(ADSPPM_LOG_LEVEL_INFO_EXT, "Set ext request to invalid: clientId=%u (%s), resourceId=%u", clientId, pRMHandle->pAdsppmHandle->clientName, resourceId);
                        }
                    }
                    else
                    {
                        sts = Adsppm_Status_BadParm;
                        ADSPPM_LOG_PRINTF_2(ADSPPM_LOG_LEVEL_INFO_EXT, "release request with invalid clientId=%u, resourceid=%u", clientId, resourceId);
                    }
                }
            }
            ADSPPM_UNLOCK_RESOURCE(resourceId);
        }
    }

    ADSPPM_LOG_FUNC_EXIT(sts);
    return sts;
}


/**@fn RM_RequestResource
 * @Brief - send request to resource managers, based on resource ID.
 * @param input AdsppmRscIdType resourceId - resource ID that client request.
 * @return Adsppm_Status_BadParm
 * @return Adsppm_Status_Success
 */
Adsppm_Status RM_RequestResource(AdsppmRscIdType resourceId)
{
    Adsppm_Status sts = Adsppm_Status_Success;
    AdsppmCoreCtxType *pAdsppmCoreCtx = GetAdsppmCoreContext();
    ADSPPM_LOG_FUNC_ENTER;

    ADSPPM_LOG_PRINTF_1(ADSPPM_LOG_LEVEL_INFO_EXT, "Request resourceId=%u", resourceId);
    if((Adsppm_Rsc_Id_None == resourceId) || (Adsppm_Rsc_Id_Max < resourceId))
    {
        sts = Adsppm_Status_BadParm;
        ADSPPM_LOG_PRINTF_1(ADSPPM_LOG_LEVEL_ERROR, "Invalid resourceId=%u", resourceId);
    }
    else
    {
        switch(resourceId)
        {
        case Adsppm_Rsc_Id_Core_Clk:
            sts = CLK_ProcessRequest(&(pAdsppmCoreCtx->rscReqQ[Adsppm_Rsc_Id_Core_Clk-1]));
            break;
        case Adsppm_Rsc_Id_Power:
            sts = PWR_ProcessRequest(&(pAdsppmCoreCtx->rscReqQ[Adsppm_Rsc_Id_Power-1]));
            break;
        case Adsppm_Rsc_Id_Sleep_Latency:
            sts = SLEEP_ProcessRequest(&(pAdsppmCoreCtx->rscReqQ[Adsppm_Rsc_Id_Sleep_Latency-1]));
            break;
        case Adsppm_Rsc_Id_Mips:
            sts = MIPS_ProcessRequest(&(pAdsppmCoreCtx->rscReqQ[Adsppm_Rsc_Id_Mips-1]));
            break;
        case Adsppm_Rsc_Id_BW:
            sts = BUS_ProcessRequest(&(pAdsppmCoreCtx->rscReqQ[Adsppm_Rsc_Id_BW-1]));
            break;
        case Adsppm_Rsc_Id_Thermal:
            sts = THERMAL_ProcessRequest(&(pAdsppmCoreCtx->rscReqQ[Adsppm_Rsc_Id_Thermal-1]));
            break;
        case Adsppm_Rsc_Id_MemPower:
            sts = MEMPWR_ProcessRequest(&(pAdsppmCoreCtx->rscReqQ[Adsppm_Rsc_Id_MemPower-1]));
            break;
        case Adsppm_Rsc_Id_Core_Clk_Domain:
            sts = CLKDomain_ProcessRequest(&(pAdsppmCoreCtx->rscReqQ[Adsppm_Rsc_Id_Core_Clk_Domain-1]));
            break;
        default:
            sts = Adsppm_Status_UnSupported;
            ADSPPM_LOG_PRINTF_1(ADSPPM_LOG_LEVEL_ERROR, "Unsupported resourceId=%u", resourceId);
            break;
        } /* switch resource Id */
    } /* resoureId out of range? */

    ADSPPM_LOG_FUNC_EXIT(sts);
    return sts;
}


/**
 * RM_SetParameter - set parameters for client, allocate memory for parameter and put parameter pointer into client handle context
 */
Adsppm_Status RM_SetParameter(uint32 clientId, AdsppmParameterConfigType *pParamConfigData)
{
    Adsppm_Status sts = Adsppm_Status_Success;
    AdsppmCoreCtxType *pAdsppmCoreCtx = GetAdsppmCoreContext();
    AdsppmHandleType *pAdsppmHandle = NULL;
    ADSPPM_LOG_FUNC_ENTER;

    if(NULL == pParamConfigData)
    {
        sts = Adsppm_Status_BadParm;
    }
    else
    {
        pAdsppmHandle = coreUtils_Q_LinearSearch(&pAdsppmCoreCtx->adsppmHandleQ, (coreUtils_Q_CompareFuncType)findAdsppmHandle, (void *)&clientId);
        if(NULL != pAdsppmHandle)
        {
            switch(pParamConfigData->paramId)
            {
            case Adsppm_Param_Id_Client_Ocmem_Map:
            case Adsppm_Param_Id_Resource_Limit:
            default:
                sts = Adsppm_Status_UnSupported;
                ADSPPM_LOG_PRINTF_1(ADSPPM_LOG_LEVEL_INFO_EXT, "Parameter %u not supported", pParamConfigData->paramId);
                break;
            }
        }
        else
        {
            ADSPPM_LOG_PRINTF_1(ADSPPM_LOG_LEVEL_INFO_EXT, "clientId=%u is invalid", clientId);
            sts = Adsppm_Status_BadParm;
        }
    }

    ADSPPM_LOG_FUNC_EXIT(sts);
    return sts;
}


/**
 * freeSetParameter - free parameter's memory, it'll be called in delete client time
 */
static void freeSetParameter(AdsppmHandleType *pAdsppmHandle)
{
    ADSPPM_LOG_FUNC_ENTER;
    if(NULL != pAdsppmHandle->pSetParamConfig)
    {
        free(pAdsppmHandle->pSetParamConfig);
        pAdsppmHandle->pSetParamConfig = NULL;
    }
    ADSPPM_LOG_FUNC_EXIT(0);
}

