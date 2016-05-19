/*
* Copyright (c) 2013 Qualcomm Technologies, Inc.
* All Rights Reserved.
* Qualcomm Technologies, Inc. Confidential and Proprietary.
*/

/*
 * clkmgr.c
 *
 *  Created on: Feb 13, 2012
 *      Author: yrusakov
 */

#include "adsppm.h"
#include "ULog.h"
#include "ULogFront.h"
#include "adsppm_utils.h"
#include "requestmgr.h"
#include "asic.h"
#include "clkmgr.h"
#include "core_internal.h"
#include "hal_clkrgm.h"


//Enumeration for core clock index
//Has to be in exactly the same order as core clocks arranged in the AdsppmClkIdType
typedef enum{
    HwRsp_Core = 0,
    Midi_Core,
    AvSync_Xo,
    AvSync_Bt,
    AvSync_Fm,
    Slimbus_Core,
    Slimbus2_Core,
    Avtimer_Core,
    Atime_Core,
    Atime2_Core
} ReqArrayIndexType;

typedef struct{
    AsicClkTypeType          ClkType;
    AdsppmClkIdType          CoreClkId;
    uint32                   value;             //current freq
    uint32                   last;              //last set freq
    AdsppmClkDomainSrcIdType clkDomainSrc;      //current clock source
    AdsppmClkDomainSrcIdType clkDomainSrc_last; //last set clock source
} CLKAggaregateType;

static CLKAggaregateType gCLKReqArray[] =
{
   {.CoreClkId = AdsppmClk_HwRsp_Core,    .value = 0, .last = 0, .clkDomainSrc.clkDomainSrcIdLpass = Adsppm_Clk_Domain_Src_Id_Primary_PLL, .clkDomainSrc_last.clkDomainSrcIdLpass = Adsppm_Clk_Domain_Src_Id_Primary_PLL},
   {.CoreClkId = AdsppmClk_Midi_Core,     .value = 0, .last = 0, .clkDomainSrc.clkDomainSrcIdLpass = Adsppm_Clk_Domain_Src_Id_Primary_PLL, .clkDomainSrc_last.clkDomainSrcIdLpass = Adsppm_Clk_Domain_Src_Id_Primary_PLL},
   {.CoreClkId = AdsppmClk_AvSync_Xo,     .value = 0, .last = 0, .clkDomainSrc.clkDomainSrcIdLpass = Adsppm_Clk_Domain_Src_Id_Primary_PLL, .clkDomainSrc_last.clkDomainSrcIdLpass = Adsppm_Clk_Domain_Src_Id_Primary_PLL},
   {.CoreClkId = AdsppmClk_AvSync_Bt,     .value = 0, .last = 0, .clkDomainSrc.clkDomainSrcIdLpass = Adsppm_Clk_Domain_Src_Id_Primary_PLL, .clkDomainSrc_last.clkDomainSrcIdLpass = Adsppm_Clk_Domain_Src_Id_Primary_PLL},
   {.CoreClkId = AdsppmClk_AvSync_Fm,     .value = 0, .last = 0, .clkDomainSrc.clkDomainSrcIdLpass = Adsppm_Clk_Domain_Src_Id_Primary_PLL, .clkDomainSrc_last.clkDomainSrcIdLpass = Adsppm_Clk_Domain_Src_Id_Primary_PLL},
   {.CoreClkId = AdsppmClk_Slimbus_Core,  .value = 0, .last = 0, .clkDomainSrc.clkDomainSrcIdLpass = Adsppm_Clk_Domain_Src_Id_Primary_PLL, .clkDomainSrc_last.clkDomainSrcIdLpass = Adsppm_Clk_Domain_Src_Id_Primary_PLL},
   {.CoreClkId = AdsppmClk_Slimbus2_Core, .value = 0, .last = 0, .clkDomainSrc.clkDomainSrcIdLpass = Adsppm_Clk_Domain_Src_Id_Primary_PLL, .clkDomainSrc_last.clkDomainSrcIdLpass = Adsppm_Clk_Domain_Src_Id_Primary_PLL},
   {.CoreClkId = AdsppmClk_Avtimer_core,  .value = 0, .last = 0, .clkDomainSrc.clkDomainSrcIdLpass = Adsppm_Clk_Domain_Src_Id_Primary_PLL, .clkDomainSrc_last.clkDomainSrcIdLpass = Adsppm_Clk_Domain_Src_Id_Primary_PLL},
   {.CoreClkId = AdsppmClk_Atime_core,    .value = 0, .last = 0, .clkDomainSrc.clkDomainSrcIdLpass = Adsppm_Clk_Domain_Src_Id_Primary_PLL, .clkDomainSrc_last.clkDomainSrcIdLpass = Adsppm_Clk_Domain_Src_Id_Primary_PLL},
   {.CoreClkId = AdsppmClk_Atime2_core,   .value = 0, .last = 0, .clkDomainSrc.clkDomainSrcIdLpass = Adsppm_Clk_Domain_Src_Id_Primary_PLL, .clkDomainSrc_last.clkDomainSrcIdLpass = Adsppm_Clk_Domain_Src_Id_Primary_PLL}
};


Adsppm_Status CLK_Init(void)
{
    uint32 i;
    Adsppm_Status sts = Adsppm_Status_Success;
    ADSPPM_LOG_FUNC_ENTER;
    for(i = AdsppmClk_HwRsp_Core; i < AdsppmClk_EnumMax; i++)
    {
        gCLKReqArray[i-AdsppmClk_HwRsp_Core].ClkType = ACMClk_GetClockType(i);
    }
    ADSPPM_LOG_FUNC_EXIT(sts);
    return sts;
}


Adsppm_Status CLK_ProcessRequest(coreUtils_Q_Type *pClkReqQ)
{
    Adsppm_Status sts = Adsppm_Status_Success;
    AdsppmClkRequestType *pClkReqData;
    RMHandleType *pRMHandle = NULL;
    uint32 index_a;
    uint32 index_b;
    uint32 index_c;
    ADSPPM_LOG_FUNC_ENTER;

    if(NULL == pClkReqQ)
    {
        sts = Adsppm_Status_BadParm;
    }
    else
    {
        ADSPPM_LOCK_RESOURCE(Adsppm_Rsc_Id_Core_Clk);
        gCLKReqArray[HwRsp_Core].value = 0;
        gCLKReqArray[Midi_Core].value = 0;
        gCLKReqArray[AvSync_Xo].value = 0;
        gCLKReqArray[AvSync_Bt].value = 0;
        gCLKReqArray[AvSync_Fm].value = 0;
        gCLKReqArray[Slimbus_Core].value = 0;
        gCLKReqArray[Slimbus2_Core].value = 0;
        gCLKReqArray[Avtimer_Core].value = 0;
        gCLKReqArray[Atime_Core].value = 0;
        gCLKReqArray[Atime2_Core].value = 0;

        //checks with all clients
        pRMHandle = (RMHandleType *)coreUtils_Q_Check(pClkReqQ);
        for(index_a = 0; index_a < pClkReqQ->nCnt; index_a++)
        {
            if(NULL != pRMHandle)
            {
                if(RM_Valid == pRMHandle->validFlag)
                {
                    if((NULL == (AdsppmClkRequestType *)(pRMHandle->pRequestData)) || (NULL == pRMHandle->pAdsppmHandle))
                    {
                        ADSPPM_LOG_PRINTF_2(ADSPPM_LOG_LEVEL_ERROR, "pRequestData(%u) or pAdsppmHandle(%u) is NULL",
                                (AdsppmClkRequestType *)(pRMHandle->pRequestData), pRMHandle->pAdsppmHandle);
                        sts = Adsppm_Status_BadParm;
                        break;
                    }
                    else
                    {
                        pClkReqData = (AdsppmClkRequestType *)(pRMHandle->pRequestData);
                        //checks array of clock settings
                        for(index_b = 0; index_b < pClkReqData->numOfClk; index_b++)
                        {
                            //get core clock ID corresponding to this core instance if applicable
                            pClkReqData->pClkArray[index_b].clkId = ACMClk_GetInstanceCoreClockId(pRMHandle->pAdsppmHandle->coreId,
                                    pRMHandle->pAdsppmHandle->instanceId, pClkReqData->pClkArray[index_b].clkId);
                            ReqArrayIndexType clkIdx = pClkReqData->pClkArray[index_b].clkId-AdsppmClk_HwRsp_Core;
                            gCLKReqArray[clkIdx].value = MAX(gCLKReqArray[clkIdx].value, pClkReqData->pClkArray[index_b].clkFreqHz);
                        }
                    }
                }
                pRMHandle = (RMHandleType *)coreUtils_Q_Next(pClkReqQ, &(pRMHandle->rmHandleQLink));
            }
        }
        for(index_c = AdsppmClk_HwRsp_Core; index_c < AdsppmClk_EnumMax; index_c++)
        {
            ReqArrayIndexType clkIdx = index_c-AdsppmClk_HwRsp_Core;
            //Adjust based on feature parameters
            gCLKReqArray[clkIdx].value = ACM_AdjustParamValue(AsicFeatureId_CoreClk_Scaling, gCLKReqArray[clkIdx].value);
            switch(gCLKReqArray[clkIdx].ClkType)
            {
            case AsicClk_TypeNpa:
            case AsicClk_TypeDalFreqSet:
                if(gCLKReqArray[clkIdx].last != gCLKReqArray[clkIdx].value)
                {
                    if(Adsppm_Status_Success != ClkRgm_SetClock(index_c, gCLKReqArray[clkIdx].value))
                    {
                        sts = Adsppm_Status_Failed;
                        break;
                    }
                    else
                    {
                        gCLKReqArray[clkIdx].last = gCLKReqArray[clkIdx].value;
                    }
                }
                break;
            case AsicClk_TypeDalEnable:
                if(gCLKReqArray[clkIdx].last != gCLKReqArray[clkIdx].value)
                {
                    Hal_ClkRgmEnableDisableType enable = (gCLKReqArray[clkIdx].value > 0)?Hal_ClkRgmEnable:Hal_ClkRgmDisable;
                    if(Adsppm_Status_Success != ClkRgm_EnableClock(index_c, enable))
                    {
                        sts = Adsppm_Status_Failed;
                        break;
                    }
                    else
                    {
                        gCLKReqArray[clkIdx].last = gCLKReqArray[clkIdx].value;
                    }
                }
                break;
            default:
                break;
            }
        }
        ADSPPM_UNLOCK_RESOURCE(Adsppm_Rsc_Id_Core_Clk);
    }

    ADSPPM_LOG_FUNC_EXIT(sts);
    return sts;
}


Adsppm_Status CLKDomain_ProcessRequest(coreUtils_Q_Type *pClkDomainReqQ)
{
    Adsppm_Status sts = Adsppm_Status_Success;
    AdsppmClkDomainReqType *pClkDomainReqData;
    RMHandleType *pRMHandle = NULL;
    uint32 index_a;
    uint32 index_b;
    uint32 index_c;
    ADSPPM_LOG_FUNC_ENTER;

    if(NULL == pClkDomainReqQ)
    {
        sts = Adsppm_Status_BadParm;
    }
    else
    {
        ADSPPM_LOCK_RESOURCE(Adsppm_Rsc_Id_Core_Clk_Domain);

        gCLKReqArray[HwRsp_Core].clkDomainSrc.clkDomainSrcIdLpass = Adsppm_Clk_Domain_Src_Id_Primary_PLL;
        gCLKReqArray[Midi_Core].clkDomainSrc.clkDomainSrcIdLpass = Adsppm_Clk_Domain_Src_Id_Primary_PLL;
        gCLKReqArray[AvSync_Xo].clkDomainSrc.clkDomainSrcIdLpass = Adsppm_Clk_Domain_Src_Id_Primary_PLL;
        gCLKReqArray[AvSync_Bt].clkDomainSrc.clkDomainSrcIdLpass = Adsppm_Clk_Domain_Src_Id_Primary_PLL;
        gCLKReqArray[AvSync_Fm].clkDomainSrc.clkDomainSrcIdLpass = Adsppm_Clk_Domain_Src_Id_Primary_PLL;
        gCLKReqArray[Slimbus_Core].clkDomainSrc.clkDomainSrcIdLpass = Adsppm_Clk_Domain_Src_Id_Primary_PLL;
        gCLKReqArray[Slimbus2_Core].clkDomainSrc.clkDomainSrcIdLpass = Adsppm_Clk_Domain_Src_Id_Primary_PLL;
        gCLKReqArray[Avtimer_Core].clkDomainSrc.clkDomainSrcIdLpass = Adsppm_Clk_Domain_Src_Id_Primary_PLL;
        gCLKReqArray[Atime_Core].clkDomainSrc.clkDomainSrcIdLpass = Adsppm_Clk_Domain_Src_Id_Primary_PLL;
        gCLKReqArray[Atime2_Core].clkDomainSrc.clkDomainSrcIdLpass = Adsppm_Clk_Domain_Src_Id_Primary_PLL;

        //checks with all clients
        pRMHandle = (RMHandleType *)coreUtils_Q_Check(pClkDomainReqQ);
        for(index_a = 0; index_a < pClkDomainReqQ->nCnt; index_a++)
        {
            if(NULL != pRMHandle)
            {
                if(RM_Valid == pRMHandle->validFlag)
                {
                    if((NULL == (AdsppmClkDomainReqType *)(pRMHandle->pRequestData)) || (NULL == pRMHandle->pAdsppmHandle))
                    {
                        ADSPPM_LOG_PRINTF_2(ADSPPM_LOG_LEVEL_ERROR, "pRequestData(%u) or pAdsppmHandle(%u) is NULL",
                                (AdsppmClkDomainReqType *)(pRMHandle->pRequestData), pRMHandle->pAdsppmHandle);
                        sts = Adsppm_Status_BadParm;
                        break;
                    }
                    else
                    {
                        pClkDomainReqData = (AdsppmClkDomainReqType *)(pRMHandle->pRequestData);
                        //checks array of clock settings
                        for(index_b = 0; index_b < pClkDomainReqData->numOfClk; index_b++)
                        {
                            //get core clock ID corresponding to this core instance if applicable
                            pClkDomainReqData->pClkDomainArray[index_b].clkId = ACMClk_GetInstanceCoreClockId(pRMHandle->pAdsppmHandle->coreId,
                                    pRMHandle->pAdsppmHandle->instanceId, pClkDomainReqData->pClkDomainArray[index_b].clkId);
                            ReqArrayIndexType clkIdx = pClkDomainReqData->pClkDomainArray[index_b].clkId - AdsppmClk_HwRsp_Core;
                            gCLKReqArray[clkIdx].clkDomainSrc.clkDomainSrcIdLpass = pClkDomainReqData->pClkDomainArray[index_b].clkDomainSrc.clkDomainSrcIdLpass;
                        }
                    }
                }
                pRMHandle = (RMHandleType *)coreUtils_Q_Next(pClkDomainReqQ, &(pRMHandle->rmHandleQLink));
            }
        }
        for(index_c = AdsppmClk_HwRsp_Core; index_c < AdsppmClk_EnumMax; index_c++)
        {
            ReqArrayIndexType clkIdx = index_c-AdsppmClk_HwRsp_Core;
            switch(gCLKReqArray[clkIdx].ClkType)
            {
            case AsicClk_TypeDalFreqSet:
            case AsicClk_TypeDalEnable:
            case AsicClk_TypeDalDomainSrc:
                if(gCLKReqArray[clkIdx].clkDomainSrc.clkDomainSrcIdLpass != gCLKReqArray[clkIdx].clkDomainSrc_last.clkDomainSrcIdLpass)
                {
                    if(Adsppm_Status_Success !=
                            ClkRgm_SelectClkSource(index_c, gCLKReqArray[clkIdx].clkDomainSrc.clkDomainSrcIdLpass)) //TODO can change source
                    {
                        sts = Adsppm_Status_Failed;
                        break;
                    }
                    else
                    {
                        gCLKReqArray[clkIdx].clkDomainSrc_last.clkDomainSrcIdLpass = gCLKReqArray[clkIdx].clkDomainSrc.clkDomainSrcIdLpass;
                    }
                }
                break;
            default:
                break;
            }
        }
        ADSPPM_UNLOCK_RESOURCE(Adsppm_Rsc_Id_Core_Clk_Domain);
    }

    ADSPPM_LOG_FUNC_EXIT(sts);
    return sts;
}


Adsppm_Status CLK_GetInfo(AdsppmInfoClkFreqType *pClockInfo)
{
    Adsppm_Status sts = Adsppm_Status_Success;
    ADSPPM_LOG_FUNC_ENTER;
    if(NULL == pClockInfo)
    {
        ADSPPM_LOG_PRINTF_0(ADSPPM_LOG_LEVEL_ERROR, "pClockInfo is NULL");
        sts = Adsppm_Status_BadParm;
    }
    else
    {
        if(pClockInfo->forceMeasure)
        {
            sts = ClkRgm_CalcClockFrequency(pClockInfo->clkId, &pClockInfo->clkFreqHz);
        }
        else
        {
            sts = ClkRgm_GetClockFrequency(pClockInfo->clkId, &pClockInfo->clkFreqHz);
        }
    }
    return sts;
    ADSPPM_LOG_FUNC_EXIT(sts);
}