/*==============================================================================

FILE:      api.c

DESCRIPTION: MMPM API wrapper

INITIALIZATION AND SEQUENCING REQUIREMENTS:  N/A



* Copyright (c) 2014 Qualcomm Technologies, Inc.
* All Rights Reserved.

* Qualcomm Technologies, Inc. Confidential and Proprietary.

==============================================================================

                           EDIT HISTORY FOR MODULE

$Header: //components/rel/core.adsp/2.6.1/power/adsppm/src/common/api/src/api.c#1 $

This section contains comments describing changes made to the module.
Notice that changes are listed in reverse chronological order.

when       who     what, where, why
--------   ---     ---------------------------------------------------------------
04/03/12   alisonc      Initial version

===================================================================================*/

//#include "AEEstd.h"
#include "mmpm.h"
#include "adsppm.h"
#include "adsppm_utils.h"
#include "stdlib.h"
#include "core.h"
#include "asyncmgr.h"
#include "coreUtils.h"
#include "asic.h"

#ifdef ADSPPM_TEST
#include "adsppm_test_main.h"
#endif


/** this global flag set to 1 to disable MMPM_Request_Ext at runtime, only return MMPM_STATUS_SUCCESS */
static volatile uint32 gDISABLEADSPPMREQUESTFLAG = 0;

const AdsppmClkIdType mmpmToAdsppmClk[MMPM_CLK_ID_LPASS_ENUM_MAX] =
{
    AdsppmClk_None,
    AdsppmClk_HwRsp_Core,
    AdsppmClk_Midi_Core,
    AdsppmClk_AvSync_Xo,
    AdsppmClk_AvSync_Bt,
    AdsppmClk_AvSync_Fm,
    AdsppmClk_Slimbus_Core,
    AdsppmClk_Avtimer_core,
    AdsppmClk_Atime_core,
    AdsppmClk_Atime2_core,
    AdsppmClk_Adsp_Core,
    AdsppmClk_Ahb_Root
};

const AdsppmBusPortIdType mmpmToAdsppmBusPort[MMPM_BW_PORT_ID_MAX] =
{
    AdsppmBusPort_None,
    AdsppmBusPort_Adsp_Master,
    AdsppmBusPort_Dml_Master,
    AdsppmBusPort_Aif_Master,
    AdsppmBusPort_Slimbus_Master,
    AdsppmBusPort_Midi_Master,
    AdsppmBusPort_HwRsmp_Master,
    AdsppmBusPort_Ext_Ahb_Master,
    AdsppmBusPort_Spdif_Master,
    AdsppmBusPort_Hdmirx_Master,
    AdsppmBusPort_Sif_Master,
    AdsppmBusPort_Dml_Slave,
    AdsppmBusPort_Aif_Slave,
    AdsppmBusPort_Slimbus_Slave,
    AdsppmBusPort_Midi_Slave,
    AdsppmBusPort_HwRsmp_Slave,
    AdsppmBusPort_AvSync_Slave,
    AdsppmBusPort_Lpm_Slave,
    AdsppmBusPort_Sram_Slave,
    AdsppmBusPort_Ext_Ahb_Slave,
    AdsppmBusPort_Ddr_Slave,
    AdsppmBusPort_Ocmem_Slave,
    AdsppmBusPort_PerifNoc_Slave,
    AdsppmBusPort_Spdif_Slave,
    AdsppmBusPort_Hdmirx_Slave,
    AdsppmBusPort_Sif_Slave,
    AdsppmBusPort_Bstc_Slave,
    AdsppmBusPort_Dcodec_Slave,
    AdsppmBusPort_Core,
};

/**
 * @const busPortName - defines Bus ports name to be used by MMPM ULOG internally
 *                      keep updated with MmpmBwPortIdType in mmpm.h
 */
const char *MMPMBusPortName[MMPM_BW_PORT_ID_MAX] =
{
    "NONE",
    "ADSP_MASTER",
    "DML_MASTER",
    "AIF_MASTER",
    "SLIMBUS_MASTER",
    "MIDI_MASTER",
    "HWRSMP_MASTER",
    "EXT_AHB_MASTER",
    "SPDIF_MASTER",
    "HDMIRX_MASTER",
    "SIF_MASTER",
    "DML_SLAVE",
    "AIF_SLAVE",
    "SLIMBUS_SLAVE",
    "MIDI_SLAVE",
    "HWRSMP_SLAVE",
    "AVSYNC_SLAVE",
    "LPM_SLAVE",
    "SRAM_SLAVE",
    "EXT_AHB_SLAVE",
    "DDR_SLAVE",
    "OCMEM_SLAVE",
    "PERIFNOC_SLAVE",
    "SPDIF_SLAVE",
    "HDMIRX_SLAVE",
    "SIF_SLAVE",
    "BSTC_SLAVE",
    "DCODEC_SLAVE",
    "CORE",
};


/******************************************************************************
 *                     MMPM_Register_Ext
 *****************************************************************************/
uint32 MMPM_Register_Ext(MmpmRegParamType *pRegParam)
{
    MMPM_STATUS sts = MMPM_STATUS_SUCCESS;
    uint32 clientId = 0;
    ADSPPM_LOG_FUNC_ENTER;
    ADSPPM_LOG_FUNC_PROFILESTART;

    if(!gDISABLEADSPPMREQUESTFLAG)
    {
        if(ADSPPM_IsInitialized())
        {
            if(NULL == pRegParam)
            {
                sts = MMPM_STATUS_NULLPOINTER;
            }
            else
            {
                if((MMPM_CORE_ID_LPASS_START >= pRegParam->coreId) ||
                        (MMPM_CORE_ID_LPASS_END <= pRegParam->coreId) ||
                        (NULL == pRegParam->pClientName) ||
                        (MAX_ADSPPM_CLIENT_NAME <= strlen(pRegParam->pClientName)) ||
                        (MMPM_CORE_INSTANCE_NONE == pRegParam->instanceId) ||
                        (MMPM_CORE_INSTANCE_MAX <= pRegParam->instanceId))
                {
                    sts = MMPM_STATUS_BADPARM;
                    ADSPPM_LOG_PRINTF_1(ADSPPM_LOG_LEVEL_ERROR, "bad parameters or nullclientname or clientname is too long, coreId=%u", pRegParam->coreId);
                }
                else
                {
                    AdsppmClientTypeType clientType = ((pRegParam->pwrCtrlFlag & PWR_CTRL_PERIODIC_CLIENT) == PWR_CTRL_PERIODIC_CLIENT)?
                            Adsppm_ClientType_Periodic:Adsppm_ClientType_Normal;

                    //keep MMPM core ID and ADSPPM core id enum definition identical
                    clientId = RM_CreateClient((AdsppmCoreIdType)(pRegParam->coreId - MMPM_CORE_ID_LPASS_START),
                            (AdsppmInstanceIdType)(pRegParam->instanceId), pRegParam->pClientName, (void*)pRegParam->MMPM_Callback, clientType);
                }
            }
        }
        else
        {
            sts = MMPM_STATUS_NOTINITIALIZED;
            ADSPPM_LOG_PRINTF_0(ADSPPM_LOG_LEVEL_ERROR, "MMPM not initialized");
        }
    }
    else
    {
        return 1;
    }

    ADSPPM_LOG_FUNC_PROFILEEND;
    ADSPPM_LOG_FUNC_EXIT(sts);
    return clientId;
}


/******************************************************************************
 *                     MMPM_Deregister_Ext
 *****************************************************************************/
MMPM_STATUS MMPM_Deregister_Ext(uint32 clientId)
{
    MMPM_STATUS sts = MMPM_STATUS_NOTINITIALIZED;
    ADSPPM_LOG_FUNC_ENTER;
    ADSPPM_LOG_FUNC_PROFILESTART;

    if(!gDISABLEADSPPMREQUESTFLAG)
    {
        if(ADSPPM_IsInitialized())
        {
            if(clientId)
            {
                sts = (MMPM_STATUS)RM_DeleteClient(clientId);
                if(MMPM_STATUS_SUCCESS == sts)
                {
                    AdsppmRscIdType rsc;
                    for(rsc = Adsppm_Rsc_Id_Power; rsc < Adsppm_Rsc_Id_Max; rsc++)
                    {
                        sts = (MMPM_STATUS)RM_RequestResource(rsc);
                        if(MMPM_STATUS_SUCCESS != sts)
                        {
                            break;
                        }
                    }
                }
            }
            else
            {
                sts = MMPM_STATUS_BADPARM;
                ADSPPM_LOG_PRINTF_1(ADSPPM_LOG_LEVEL_ERROR, "bad clientid in deregister=%u", clientId);
            }
        }
        else
        {
            sts = MMPM_STATUS_NOTINITIALIZED;
            ADSPPM_LOG_PRINTF_0(ADSPPM_LOG_LEVEL_ERROR, "Not initialized");
        }
    }
    else
    {
        sts = Adsppm_Status_Success;
    }

    ADSPPM_LOG_FUNC_PROFILEEND;
    ADSPPM_LOG_FUNC_EXIT(sts);
    return sts;
}


/******************************************************************************
 *                     MMPM_Request_Ext
 *****************************************************************************/
MMPM_STATUS MMPM_Request_Ext(uint32 clientId, MmpmRscExtParamType *pRscExtParam)
{
    MMPM_STATUS sts = MMPM_STATUS_SUCCESS;
    AdsppmRscIdType adsppmRscId = Adsppm_Rsc_Id_None;
    ADSPPM_LOG_FUNC_ENTER;
    ADSPPM_LOG_FUNC_PROFILESTART;

    if(!gDISABLEADSPPMREQUESTFLAG)
    {
        if(ADSPPM_IsInitialized())
        {
            if((NULL == pRscExtParam) || (0 == clientId))
            {
                sts = MMPM_STATUS_BADPARM;
                ADSPPM_LOG_PRINTF_1(ADSPPM_LOG_LEVEL_ERROR, "null pointer of pRscExtParam or clientid is 0, clientid=%u", clientId);
            }
            else
            {
                if((NULL == pRscExtParam->pReqArray) || (NULL == pRscExtParam->pStsArray))
                {
                    sts = MMPM_STATUS_NULLPOINTER;
                }
                else
                {
                    if(Adsppm_Rsc_Id_Max > pRscExtParam->numOfReq)
                    {
                        uint32 index = 0;
                        uint32 asyncRscMap = 0;

                        // For each request in the array, do initial validation of the request
                        // and pass valid requests to the resource manager
                        for(index = 0; index < pRscExtParam->numOfReq; index++)
                        {
                            MmpmRscParamType *pRequest = &pRscExtParam->pReqArray[index]; // Current request from array
                            MmpmRscParamStructType *pParams = &pRequest->rscParam; // Parameters for current request
                            MMPM_STATUS *pStatus = &pRscExtParam->pStsArray[index]; // Status for current request
                            *pStatus = MMPM_STATUS_SUCCESS; //init return sts array

                            switch(pRequest->rscId)
                            {
                            case MMPM_RSC_ID_POWER:
                            {
                                uint32 powerOn = 1;
                                adsppmRscId = Adsppm_Rsc_Id_Power;
                                ADSPPM_LOG_PRINTF_1(ADSPPM_LOG_LEVEL_INFO, "Client %u: Power request", clientId);
                                *pStatus = RM_AddRequest(clientId, Adsppm_Rsc_Id_Power, &powerOn, 0);
                                ADSPPM_QDSS_EVENT_1(ADSPPM_API_PWR_REQ, clientId);
                            }
                                break;
                            case MMPM_RSC_ID_REG_PROG:
                            {
                                //covert to bw request
                                AdsppmBusBWRequestValueType adsppmBwReqData;
                                ADSPPM_LOG_PRINTF_1(ADSPPM_LOG_LEVEL_INFO, "Client %u: Register programming request", clientId);
                                adsppmRscId = Adsppm_Rsc_Id_BW;
                                memset(&adsppmBwReqData, 0, sizeof(AdsppmBusBWRequestValueType));
                                AdsppmRegProgMatchType regProgMatch = pParams->regProgMatch;
                                if((Adsppm_RegProg_None >= regProgMatch) || (Adsppm_RegProg_Enum_Max <= regProgMatch))
                                {
                                    ADSPPM_LOG_PRINTF_1(ADSPPM_LOG_LEVEL_ERROR, "Reg Prog: bad param regProgMatch=%u", regProgMatch);
                                    *pStatus = MMPM_STATUS_BADPARM;
                                }
                                else
                                {
                                    uint64 regProgSpeed = ACMBus_GetRegProgSpeed(regProgMatch);
                                    if(0 == regProgSpeed)
                                    {
                                        ADSPPM_LOG_PRINTF_0(ADSPPM_LOG_LEVEL_ERROR, "Reg Prog: Register Programming speed returned 0");
                                        *pStatus = MMPM_STATUS_FAILED;
                                    }
                                    else
                                    {
                                        adsppmBwReqData.busRoute.masterPort = AdsppmBusPort_Adsp_Master;
                                        //adsppmBwReqData.busRoute.slavePort will be identified in BUS_ProcessRequest()
                                        adsppmBwReqData.bwValue.busBwValue.bwBytePerSec = regProgSpeed;
                                        adsppmBwReqData.bwValue.busBwValue.usagePercentage = ADSPPM_REG_PROC_CLOCK_BW_PERCENTAGE;
                                        adsppmBwReqData.bwValue.busBwValue.usageType = Adsppm_BwUsage_DSP;
                                        adsppmBwReqData.bwOperation = AdsppmBusBWOperation_RegAccess;
                                        ADSPPM_LOG_PRINTF_2(ADSPPM_LOG_LEVEL_INFO, "    Adsppm Reg Prog: match=%u -> bw=%u", regProgMatch, regProgSpeed);
                                        *pStatus = RM_AddRequest(clientId, Adsppm_Rsc_Id_BW, &adsppmBwReqData, 1);
                                        ADSPPM_QDSS_EVENT_3(ADSPPM_API_REG_REQ, clientId, adsppmBwReqData.busRoute.masterPort, adsppmBwReqData.busRoute.slavePort);
                                    }
                                }
                            }
                                break;
                            case MMPM_RSC_ID_CORE_CLK:
                            {
                                AdsppmClkRequestType adsppmClkReqData;
                                uint32 clkNum = 0;
                                MmpmClkReqType *pCoreClkParams = pParams->pCoreClk;
                                adsppmRscId = Adsppm_Rsc_Id_Core_Clk;
                                ADSPPM_LOG_PRINTF_1(ADSPPM_LOG_LEVEL_INFO, "Client %u: Clock request", clientId);
                                if(MAX_NUM_OF_ADSPPM_CLOCK_ARRAY < pCoreClkParams->numOfClk)
                                {
                                    *pStatus = MMPM_STATUS_BADPARM;
                                    ADSPPM_LOG_PRINTF_1(ADSPPM_LOG_LEVEL_ERROR, "numbofclk exceed max numofclk=%u", pCoreClkParams->numOfClk);
                                }
                                else
                                {
                                    memset(&adsppmClkReqData, 0, sizeof(AdsppmClkRequestType));
                                    adsppmClkReqData.numOfClk = pCoreClkParams->numOfClk;
                                    //translate clock Id to ADSPPM
                                    //And copy all the request values
                                    for(clkNum = 0; clkNum < pCoreClkParams->numOfClk; clkNum++)
                                    {
                                        MmpmClkValType *pClkInfo = &pCoreClkParams->pClkArray[clkNum];
                                        if((MMPM_CLK_ID_LPASS_NONE == pClkInfo->clkId.clkIdLpass)
                                                || (MMPM_CLK_ID_LPASS_ADSP_CORE <= pClkInfo->clkId.clkIdLpass)
                                                || (MMPM_FREQ_MAX <= pClkInfo->freqMatch))
                                        {
                                            *pStatus = MMPM_STATUS_BADPARM;
                                            ADSPPM_LOG_PRINTF_2(ADSPPM_LOG_LEVEL_ERROR, "bad lpassclkid=%u or freqmatch=%u",
                                                    pClkInfo->clkId.clkIdLpass,
                                                    pClkInfo->freqMatch);
                                            break;
                                        }
                                        else
                                        {
                                            adsppmClkReqData.pClkArray[clkNum].clkId = mmpmToAdsppmClk[pClkInfo->clkId.clkIdLpass];
                                            adsppmClkReqData.pClkArray[clkNum].clkFreqHz = pClkInfo->clkFreqHz;
                                            adsppmClkReqData.pClkArray[clkNum].freqMatch = pClkInfo->freqMatch;
                                            ADSPPM_LOG_PRINTF_3(ADSPPM_LOG_LEVEL_INFO, "    clkId=%u, freqHz=%u, match=%u",
                                                    adsppmClkReqData.pClkArray[clkNum].clkId,
                                                    adsppmClkReqData.pClkArray[clkNum].clkFreqHz,
                                                    adsppmClkReqData.pClkArray[clkNum].freqMatch);
                                        }
                                    }
                                    if(MMPM_STATUS_SUCCESS == *pStatus)
                                    {
                                        *pStatus = RM_AddRequest(clientId, Adsppm_Rsc_Id_Core_Clk, &adsppmClkReqData, 0);
                                    }
                                }
                            }
                                break;
                            case MMPM_RSC_ID_SLEEP_LATENCY:
                            {
                                uint32 sleepMicroSec = pParams->sleepMicroSec;
                                adsppmRscId = Adsppm_Rsc_Id_Sleep_Latency;
                                ADSPPM_LOG_PRINTF_2(ADSPPM_LOG_LEVEL_INFO, "Client %u: Latency request: latency=%u", clientId, sleepMicroSec);
                                if(sleepMicroSec == 0)
                                {
                                    // 0 is not valid to underlying sleep driver
                                    *pStatus = MMPM_STATUS_BADPARM;
                                    ADSPPM_LOG_PRINTF_1(ADSPPM_LOG_LEVEL_ERROR, "bad parameter: sleepMicroSec=%u",
                                        sleepMicroSec);
                                }
                                else
                                {
                                    *pStatus = RM_AddRequest(clientId, Adsppm_Rsc_Id_Sleep_Latency, &sleepMicroSec, 0);
                                    ADSPPM_QDSS_EVENT_2(ADSPPM_API_LATENCY_REQ, clientId, sleepMicroSec);
                                }
                            }
                                break;
                            case MMPM_RSC_ID_MIPS_EXT:
                            {
                                AdsppmMipsRequestType adsppmMipsReqData;
                                MmpmMipsReqType *pMipsParams = pParams->pMipsExt;
                                adsppmRscId = Adsppm_Rsc_Id_Mips;
                                ADSPPM_LOG_PRINTF_1(ADSPPM_LOG_LEVEL_INFO, "Client %u: MIPS request", clientId);
                                if((MMPM_BW_PORT_ID_MAX <= pMipsParams->codeLocation)
                                        || ( MMPM_MIPS_REQUEST_NONE == pMipsParams->reqOperation)
                                        || ( MMPM_MIPS_REQUEST_ENUM_MAX <= pMipsParams->reqOperation))
                                {
                                     *pStatus = MMPM_STATUS_BADPARM;
                                     ADSPPM_LOG_PRINTF_2(ADSPPM_LOG_LEVEL_ERROR, "bad parameters in codelocation or reqoperation: codelocation=%u, reqoperation=%u",
                                             pMipsParams->codeLocation,
                                             pMipsParams->reqOperation);
                                }
                                else
                                {
                                    memset(&adsppmMipsReqData,0, sizeof(AdsppmMipsRequestType));
                                    //make sure MMPM MIPS request data structure is the same as ADSPPM mips request data structure
                                    memscpy(&adsppmMipsReqData, sizeof(AdsppmMipsRequestType), pMipsParams, sizeof(MmpmMipsReqType));
                                    ADSPPM_LOG_PRINTF_4(ADSPPM_LOG_LEVEL_INFO, "    total=%u, floor=%u, location=%u, operation=%u",
                                            adsppmMipsReqData.mipsTotal,
                                            adsppmMipsReqData.mipsPerThread,
                                            adsppmMipsReqData.codeLocation,
                                            adsppmMipsReqData.reqOperation);
                                    *pStatus = RM_AddRequest(clientId, Adsppm_Rsc_Id_Mips, &adsppmMipsReqData, 0);
                                    ADSPPM_QDSS_EVENT_5(ADSPPM_API_MIPS_REQ, clientId, adsppmMipsReqData.mipsTotal, adsppmMipsReqData.mipsPerThread, adsppmMipsReqData.codeLocation, adsppmMipsReqData.reqOperation);
                                }
                            }
                                break;
                            case MMPM_RSC_ID_GENERIC_BW:
                            {
                                AdsppmBwReqType adsppmBwReqData;
                                uint32 bwNum;
                                MmpmGenBwReqType *pBwParams = pParams->pGenBwReq;
                                adsppmRscId = Adsppm_Rsc_Id_BW;
                                ADSPPM_LOG_PRINTF_1(ADSPPM_LOG_LEVEL_INFO, "Client %u: BW request", clientId);
                                if(MAX_NUM_OF_ADSPPM_BW_ARRAY < pBwParams->numOfBw)
                                {
                                    ADSPPM_LOG_PRINTF_1(ADSPPM_LOG_LEVEL_ERROR, "Number of BW entries (%u) is too big",
                                            pBwParams->numOfBw);
                                    *pStatus = MMPM_STATUS_BADPARM;
                                }
                                else
                                {
                                    memset(&adsppmBwReqData, 0, sizeof(AdsppmBwReqType));
                                    adsppmBwReqData.numOfBw = pBwParams->numOfBw;
                                    //CHECK PORT id and translate port ID to adsppm
                                    for(bwNum = 0; bwNum < pBwParams->numOfBw; bwNum++)
                                    {
                                        MmpmGenBwValType *pBwInfo = &pBwParams->pBandWidthArray[bwNum];
                                        if((MMPM_BW_PORT_ID_NONE == pBwInfo->busRoute.masterPort)
                                                || (MMPM_BW_PORT_ID_DML_SLAVE <= pBwInfo->busRoute.masterPort)
                                                || (MMPM_BW_PORT_ID_DML_SLAVE > pBwInfo->busRoute.slavePort)
                                                || (MMPM_BW_PORT_ID_CORE <= pBwInfo->busRoute.slavePort)
                                                || (MMPM_BW_USAGE_LPASS_NONE == pBwInfo->bwValue.busBwValue.usageType)
                                                || (MMPM_BW_USAGE_LPASS_ENUM_MAX <= pBwInfo->bwValue.busBwValue.usageType))
                                        {
                                            *pStatus = MMPM_STATUS_BADPARM;
                                            ADSPPM_LOG_PRINTF_3(ADSPPM_LOG_LEVEL_ERROR, "BW route or usageType is invalid: master=%u, slave=%u, usageType=%u",
                                                    pBwInfo->busRoute.masterPort,
                                                    pBwInfo->busRoute.slavePort,
                                                    pBwInfo->bwValue.busBwValue.usageType);
                                            break;
                                        }
                                        else
                                        {
                                            adsppmBwReqData.pBwArray[bwNum].busRoute.masterPort = mmpmToAdsppmBusPort[pBwInfo->busRoute.masterPort];
                                            adsppmBwReqData.pBwArray[bwNum].busRoute.slavePort = mmpmToAdsppmBusPort[pBwInfo->busRoute.slavePort];
                                            adsppmBwReqData.pBwArray[bwNum].bwValue.busBwValue.bwBytePerSec = pBwInfo->bwValue.busBwValue.bwBytePerSec;
                                            adsppmBwReqData.pBwArray[bwNum].bwValue.busBwValue.usagePercentage = pBwInfo->bwValue.busBwValue.usagePercentage;
                                            adsppmBwReqData.pBwArray[bwNum].bwValue.busBwValue.usageType = (AdsppmBwUsageLpassType)pBwInfo->bwValue.busBwValue.usageType;
                                            adsppmBwReqData.pBwArray[bwNum].bwOperation = AdsppmBusBWOperation_BW;
                                            ADSPPM_LOG_PRINTF_5(ADSPPM_LOG_LEVEL_INFO, "    MMPM   M=%s(%u), S=%s(%u), Operation=%u",
                                                    MMPMBusPortName[pBwInfo->busRoute.masterPort],
                                                    pBwInfo->busRoute.masterPort,
                                                    MMPMBusPortName[pBwInfo->busRoute.slavePort],
                                                    pBwInfo->busRoute.slavePort,
                                                    adsppmBwReqData.pBwArray[bwNum].bwOperation);
                                            ADSPPM_LOG_PRINTF_5(ADSPPM_LOG_LEVEL_INFO, "    ADSPPM M=%s(%u), S=%s(%u), Operation=%u",
                                                    adsppm_getBusPortName(adsppmBwReqData.pBwArray[bwNum].busRoute.masterPort), adsppmBwReqData.pBwArray[bwNum].busRoute.masterPort,
                                                    adsppm_getBusPortName(adsppmBwReqData.pBwArray[bwNum].busRoute.slavePort), adsppmBwReqData.pBwArray[bwNum].busRoute.slavePort,
                                                    adsppmBwReqData.pBwArray[bwNum].bwOperation);
                                            ADSPPM_LOG_PRINTF_3(ADSPPM_LOG_LEVEL_INFO, "    BW=%u at %u, usage=%u",
                                                    (uint32)adsppmBwReqData.pBwArray[bwNum].bwValue.busBwValue.bwBytePerSec,
                                                    adsppmBwReqData.pBwArray[bwNum].bwValue.busBwValue.usagePercentage,
                                                    adsppmBwReqData.pBwArray[bwNum].bwValue.busBwValue.usageType);
                                        }
                                    }
                                    if(MMPM_STATUS_SUCCESS == *pStatus)
                                    {
                                        *pStatus = RM_AddRequest(clientId, Adsppm_Rsc_Id_BW, &adsppmBwReqData, 0);
                                        ADSPPM_QDSS_EVENT_5(ADSPPM_API_BW_REQ, clientId, adsppmBwReqData.pBwArray[bwNum].busRoute.masterPort,
                                                adsppmBwReqData.pBwArray[bwNum].busRoute.slavePort, (uint32)adsppmBwReqData.pBwArray[bwNum].bwValue.busBwValue.bwBytePerSec,
                                                adsppmBwReqData.pBwArray[bwNum].bwValue.busBwValue.usagePercentage);
                                    }
                                }
                            }
                                break;
                            case MMPM_RSC_ID_THERMAL:
                            {
                                //CHECK AND TRANSLATE THERMAL LEVEL TO ADSPPM
                                AdsppmThermalType adsppmThermalLevel = pParams->thermalMitigation;
                                adsppmRscId = Adsppm_Rsc_Id_Thermal;
                                ADSPPM_LOG_PRINTF_2(ADSPPM_LOG_LEVEL_INFO, "Client %u: Thermal request: level=%u", clientId, adsppmThermalLevel);
                                *pStatus = RM_AddRequest(clientId, Adsppm_Rsc_Id_Thermal, &adsppmThermalLevel, 0);
                            }
                                break;
                            case MMPM_RSC_ID_MEM_POWER:
                            {
                                AdsppmMemPowerReqParamType adsppmMemPwrReqData;
                                MmpmMemPowerReqParamType *pMemPwrParams = pParams->pMemPowerState;
                                ADSPPM_LOG_PRINTF_1(ADSPPM_LOG_LEVEL_INFO, "Client %u: Memory power request", clientId);
                                adsppmRscId = Adsppm_Rsc_Id_MemPower;
                                if((MMPM_MEM_NONE == pMemPwrParams->memory)
                                        || (MMPM_MEM_MAX <=  pMemPwrParams->memory)
                                        || (MMPM_MEM_POWER_NONE == pMemPwrParams->powerState)
                                        || (MMPM_MEM_POWER_MAX <= pMemPwrParams->powerState))
                                {
                                    *pStatus = MMPM_STATUS_BADPARM;
                                    ADSPPM_LOG_PRINTF_2(ADSPPM_LOG_LEVEL_ERROR, "bad memoryid=%u or bad powerstate=%u", pMemPwrParams->memory,
                                            pMemPwrParams->powerState);
                                }
                                else
                                {
                                    //check for LPM retention feature
                                    if((MMPM_MEM_LPASS_LPM == pMemPwrParams->memory)
                                            && (MMPM_MEM_POWER_RETENTION == pMemPwrParams->powerState)
                                            && (AsicFeatureState_Disabled == ACM_GetFeatureStatus(AsicFeatureId_LPMRetention)))
                                    {
                                        *pStatus = MMPM_STATUS_UNSUPPORTED;
                                        ADSPPM_LOG_PRINTF_0(ADSPPM_LOG_LEVEL_ERROR, "request LPM retention not supported");
                                        break;
                                    }
                                    else if(MMPM_MEM_OCMEM == pMemPwrParams->memory)
                                    {
                                        *pStatus = MMPM_STATUS_UNSUPPORTED;
                                        ADSPPM_LOG_PRINTF_0(ADSPPM_LOG_LEVEL_ERROR, "request OCMEM retention not supported");
                                        break;
                                    }
                                    else
                                    {
                                        memset(&adsppmMemPwrReqData, 0, sizeof(AdsppmMemPowerReqParamType));
                                        //make sure mmpm mem power request parameter is the same structure with adsppm
                                        memscpy(&adsppmMemPwrReqData, sizeof(AdsppmMemPowerReqParamType), pMemPwrParams, sizeof(AdsppmMemPowerReqParamType));
                                        *pStatus = RM_AddRequest(clientId, Adsppm_Rsc_Id_MemPower, &adsppmMemPwrReqData, 0);
                                        ADSPPM_QDSS_EVENT_3(ADSPPM_API_MEM_PWR_REQ, clientId, adsppmMemPwrReqData.memory, adsppmMemPwrReqData.powerState);
                                    }
                                }
                            }
                                break;
                            case MMPM_RSC_ID_CORE_CLK_DOMAIN:
                            {
                                AdsppmClkDomainReqType adsppmClkDomainReqData;
                                MmpmClkDomainReqType *pClkDomParams = pParams->pCoreClkDomain;
                                uint32 clkNum = 0;
                                adsppmRscId = Adsppm_Rsc_Id_Core_Clk_Domain;
                                ADSPPM_LOG_PRINTF_1(ADSPPM_LOG_LEVEL_INFO, "Client %u: Clock Domain request", clientId);
                                if(MAX_NUM_OF_ADSPPM_CLOCK_ARRAY < pClkDomParams->numOfClk)
                                {
                                    *pStatus = MMPM_STATUS_BADPARM;
                                    ADSPPM_LOG_PRINTF_1(ADSPPM_LOG_LEVEL_ERROR, "numbofclk in clkdomain exceed max numofclk=%u", pClkDomParams->numOfClk);
                                }
                                else
                                {
                                    memset(&adsppmClkDomainReqData, 0, sizeof(AdsppmClkDomainReqType));
                                    adsppmClkDomainReqData.numOfClk = pClkDomParams->numOfClk;
                                    //translate clock Id to ADSPPM
                                    //And copy all the request values
                                    for(clkNum = 0; clkNum < pClkDomParams->numOfClk; clkNum++)
                                    {
                                        MmpmClkDomainType *pClkDomInfo = &pClkDomParams->pClkDomainArray[clkNum];
                                        if((MMPM_CLK_ID_LPASS_NONE == pClkDomInfo->clkId.clkIdLpass)
                                                || (MMPM_CLK_ID_LPASS_ADSP_CORE <= pClkDomInfo->clkId.clkIdLpass)
                                                || (MMPM_CLK_DOMAIN_SRC_ID_LPASS_NONE == pClkDomInfo->clkDomainSrc.clkDomainSrcIdLpass)
                                                || (MMPM_CLK_DOMAIN_SRC_ID_LPASS_MAX <= pClkDomInfo->clkDomainSrc.clkDomainSrcIdLpass))
                                        {
                                            *pStatus = MMPM_STATUS_BADPARM;
                                            ADSPPM_LOG_PRINTF_2(ADSPPM_LOG_LEVEL_ERROR, "bad lpassclkid=%u or clkdomainsource=%u",
                                                    pClkDomInfo->clkId.clkIdLpass,
                                                    pClkDomInfo->clkDomainSrc.clkDomainSrcIdLpass);
                                            break;
                                        }
                                        else
                                        {
                                            adsppmClkDomainReqData.pClkDomainArray[clkNum].clkId = mmpmToAdsppmClk[pClkDomInfo->clkId.clkIdLpass];
                                            adsppmClkDomainReqData.pClkDomainArray[clkNum].clkDomainSrc.clkDomainSrcIdLpass = pClkDomInfo->clkDomainSrc.clkDomainSrcIdLpass;

                                            ADSPPM_LOG_PRINTF_3(ADSPPM_LOG_LEVEL_INFO, "    clkId=%u, clkfreq=%u, clockdomainsrc=%u",
                                                    adsppmClkDomainReqData.pClkDomainArray[clkNum].clkId, adsppmClkDomainReqData.pClkDomainArray[clkNum].clkFreqHz,
                                                    adsppmClkDomainReqData.pClkDomainArray[clkNum].clkDomainSrc.clkDomainSrcIdLpass);
                                        }
                                    }
                                    if(MMPM_STATUS_SUCCESS == *pStatus)
                                    {
                                        *pStatus = RM_AddRequest(clientId, Adsppm_Rsc_Id_Core_Clk_Domain, &adsppmClkDomainReqData, 0);
                                    }
                                }
                            }
                                break;
                            default:
                                *pStatus = MMPM_STATUS_UNSUPPORTED;
                                ADSPPM_LOG_PRINTF_2(ADSPPM_LOG_LEVEL_ERROR, "Client %u: Unsupported resource %u requested", clientId, pRequest->rscId);
                                break;
                            }
                            if(MMPM_STATUS_SUCCESS == *pStatus)
                            {
                                if(MMPM_API_TYPE_ASYNC == pRscExtParam->apiType)
                                {
                                    asyncRscMap |= (1<<adsppmRscId);
                                }
                                else
                                {
                                    *pStatus = (MMPM_STATUS)RM_RequestResource(adsppmRscId);
                                }
                            }
                        }

                        if(MMPM_API_TYPE_ASYNC == pRscExtParam->apiType)
                        {
                            sts = (MMPM_STATUS)AM_AsyncRequest(clientId, asyncRscMap, pRscExtParam->reqTag);
                        }

                        //update return sts
                        for(index = 0; index < pRscExtParam->numOfReq; index++)
                        {
                            if(MMPM_STATUS_SUCCESS != pRscExtParam->pStsArray[index])
                            {
                                sts = MMPM_STATUS_FAILED;
                                ADSPPM_LOG_PRINTF_3(ADSPPM_LOG_LEVEL_ERROR, "Request for rscId %u failed (%u) for client %u",
                                        pRscExtParam->pReqArray[index].rscId, pRscExtParam->pStsArray[index], clientId);
                            }
                        }
                    }
                    else
                    {
                        sts = MMPM_STATUS_BADPARM;
                        ADSPPM_LOG_PRINTF_1(ADSPPM_LOG_LEVEL_ERROR, "Invalid number of requests in bundle %u", pRscExtParam->numOfReq);
                    }
                } //pRscExtParam->pReqArray; pRscExtParam->pStsArray NULL pointer
            } //pRscExtParam NULL pointer
        }
        else
        {
            sts = MMPM_STATUS_NOTINITIALIZED;
            ADSPPM_LOG_PRINTF_0(ADSPPM_LOG_LEVEL_ERROR, "Not initialized");
        }
    }

    ADSPPM_LOG_FUNC_PROFILEEND;
    ADSPPM_LOG_FUNC_EXIT(sts);
    return sts;
}


/******************************************************************************
 *                     MMPM_Release_Ext
 *****************************************************************************/
MMPM_STATUS MMPM_Release_Ext(uint32 clientId, MmpmRscExtParamType *pRscExtParam)
{
    MMPM_STATUS sts = MMPM_STATUS_NOTINITIALIZED;
    AdsppmRscIdType adsppmRscId = Adsppm_Rsc_Id_None;
    ADSPPM_LOG_FUNC_ENTER;
    ADSPPM_LOG_FUNC_PROFILESTART;

    if(!gDISABLEADSPPMREQUESTFLAG)
    {
        if(ADSPPM_IsInitialized())
        {
            if((NULL == pRscExtParam) || (0 == clientId))
            {
                sts = MMPM_STATUS_BADPARM;
                ADSPPM_LOG_PRINTF_1(ADSPPM_LOG_LEVEL_ERROR, "NULL pointer for pRscExtParam or clientID=0, clientid=%u", clientId);
            }
            else
            {
                if((NULL == pRscExtParam->pReqArray) || (NULL == pRscExtParam->pStsArray))
                {
                    sts = MMPM_STATUS_NULLPOINTER;
                }
                else
                {
                    if(Adsppm_Rsc_Id_Max > pRscExtParam->numOfReq)
                    {
                        uint32 index = 0;
                        uint32 asyncRscMap = 0;
                        sts = MMPM_STATUS_SUCCESS;

                        for(index = 0; index < pRscExtParam->numOfReq; index++)
                        {
                            //init return sts array
                            pRscExtParam->pStsArray[index] = MMPM_STATUS_SUCCESS;

                            uint32 extData = 0;
                            switch(pRscExtParam->pReqArray[index].rscId)
                            {
                            case MMPM_RSC_ID_POWER:
                                adsppmRscId = Adsppm_Rsc_Id_Power;
                                ADSPPM_LOG_PRINTF_1(ADSPPM_LOG_LEVEL_INFO, "Client %u: power release", clientId);
                                ADSPPM_QDSS_EVENT_1(ADSPPM_API_PWR_REL, clientId);
                                break;
                            case MMPM_RSC_ID_REG_PROG:
                                adsppmRscId = Adsppm_Rsc_Id_BW;
                                ADSPPM_LOG_PRINTF_1(ADSPPM_LOG_LEVEL_INFO, "Client %u: regprog release", clientId);
                                ADSPPM_QDSS_EVENT_1(ADSPPM_API_REG_REL, clientId);
                                extData = 1;
                                break;
                            case MMPM_RSC_ID_CORE_CLK:
                                adsppmRscId = Adsppm_Rsc_Id_Core_Clk;
                                ADSPPM_LOG_PRINTF_1(ADSPPM_LOG_LEVEL_INFO, "Client %u: coreclk release", clientId);
                                break;
                            case MMPM_RSC_ID_SLEEP_LATENCY:
                                adsppmRscId = Adsppm_Rsc_Id_Sleep_Latency;
                                ADSPPM_LOG_PRINTF_1(ADSPPM_LOG_LEVEL_INFO, "Client %u: sleeplatency release", clientId);
                                ADSPPM_QDSS_EVENT_1(ADSPPM_API_LATENCY_REL, clientId);
                                break;
                            case MMPM_RSC_ID_MIPS_EXT:
                                adsppmRscId = Adsppm_Rsc_Id_Mips;
                                ADSPPM_LOG_PRINTF_1(ADSPPM_LOG_LEVEL_INFO, "Client %u: mipsext release", clientId);
                                ADSPPM_QDSS_EVENT_1(ADSPPM_API_MIPS_REL, clientId);
                                break;
                            case MMPM_RSC_ID_GENERIC_BW:
                                adsppmRscId = Adsppm_Rsc_Id_BW;
                                ADSPPM_LOG_PRINTF_1(ADSPPM_LOG_LEVEL_INFO, "Client %u: genBW release", clientId);
                                ADSPPM_QDSS_EVENT_1(ADSPPM_API_BW_REL, clientId);
                                break;
                            case MMPM_RSC_ID_THERMAL:
                                adsppmRscId = Adsppm_Rsc_Id_Thermal;
                                ADSPPM_LOG_PRINTF_1(ADSPPM_LOG_LEVEL_INFO, "Client %u: thermal release", clientId);
                                break;
                            case MMPM_RSC_ID_MEM_POWER:
                                adsppmRscId = Adsppm_Rsc_Id_MemPower;
                                ADSPPM_LOG_PRINTF_1(ADSPPM_LOG_LEVEL_INFO, "Client %u: mempower release", clientId);
                                ADSPPM_QDSS_EVENT_1(ADSPPM_API_MEM_PWR_REL, clientId);
                                break;
                            case MMPM_RSC_ID_CORE_CLK_DOMAIN:
                                adsppmRscId = Adsppm_Rsc_Id_Core_Clk_Domain;
                                ADSPPM_LOG_PRINTF_1(ADSPPM_LOG_LEVEL_INFO, "Client %u: clkdomain release", clientId);
                                break;
                            default:
                                sts = MMPM_STATUS_UNSUPPORTED;
                                ADSPPM_LOG_PRINTF_1(ADSPPM_LOG_LEVEL_ERROR, "Unsupported rscId = %u", pRscExtParam->pReqArray[index].rscId);
                                break;
                            }
                            ADSPPM_LOG_PRINTF_2(ADSPPM_LOG_LEVEL_INFO_EXT, "Releasing rscId=%u for clientId %u", adsppmRscId, clientId);
                            pRscExtParam->pStsArray[index] = RM_ReleaseRequest(clientId, adsppmRscId, extData);

                            if(MMPM_STATUS_SUCCESS == pRscExtParam->pStsArray[index])
                            {
                                if(MMPM_API_TYPE_ASYNC == pRscExtParam->apiType)
                                {
                                    asyncRscMap |= (1<<adsppmRscId);
                                }
                                else
                                {
                                    pRscExtParam->pStsArray[index] = RM_RequestResource(adsppmRscId);
                                }
                            }
                        }

                        if(MMPM_API_TYPE_ASYNC == pRscExtParam->apiType)
                        {
                            sts = AM_AsyncRequest(clientId, asyncRscMap, pRscExtParam->reqTag);
                        }

                        //update return sts
                        for(index = 0; index < pRscExtParam->numOfReq; index++)
                        {
                            if(MMPM_STATUS_SUCCESS != pRscExtParam->pStsArray[index])
                            {
                                sts = MMPM_STATUS_FAILED;
                                ADSPPM_LOG_PRINTF_3(ADSPPM_LOG_LEVEL_ERROR, "Release for rscId %u failed (%u) for client %u",
                                        pRscExtParam->pReqArray[index].rscId, pRscExtParam->pStsArray[index], clientId);
                            }
                        }
                    }
                    else
                    {
                        sts = MMPM_STATUS_BADPARM;
                        ADSPPM_LOG_PRINTF_1(ADSPPM_LOG_LEVEL_ERROR, "Invalid number of requests in bundle %u", pRscExtParam->numOfReq);
                    }
                } //pRscExtParam->pReqArray, pRscExtParam->pStsArray NULL pointer
            } //pRscExtParam NULL pointer
        }
        else
        {
            sts = MMPM_STATUS_NOTINITIALIZED;
            ADSPPM_LOG_PRINTF_0(ADSPPM_LOG_LEVEL_ERROR, "Not initialized");
        }
    }
    else
    {
        sts = MMPM_STATUS_SUCCESS;
    }

    ADSPPM_LOG_FUNC_PROFILEEND;
    ADSPPM_LOG_FUNC_EXIT(sts);
    return sts;
}


/******************************************************************************
 *                     MMPM_GetInfo
 *****************************************************************************/
MMPM_STATUS MMPM_GetInfo(MmpmInfoDataType *pInfoData)
{
    MMPM_STATUS sts = MMPM_STATUS_NOTINITIALIZED;
    AdsppmCoreIdType coreId;
    uint32 clientId = 0;
    uint32 callBackFunc;
    AdsppmInfoClkFreqType clkInfoFreq;
    AdsppmClientTypeType clientType;
    uint32 mipsValue;
    uint64 bwValue;
    ADSPPM_LOG_FUNC_ENTER;
    ADSPPM_LOG_FUNC_PROFILESTART;

    if(!gDISABLEADSPPMREQUESTFLAG)
    {
        //TODO: getinfo is different with MMPM, need to discuss
        //put unsupported
        if(ADSPPM_IsInitialized())
        {
            switch(pInfoData->infoId)
            {
            case MMPM_INFO_ID_CLK_FREQ:
            case MMPM_INFO_ID_CORE_CLK_MAX:
                if((MMPM_CLK_ID_LPASS_NONE == pInfoData->info.pInfoClkFreqType->clkId)
                        || (MMPM_CLK_ID_LPASS_ENUM_MAX <= pInfoData->info.pInfoClkFreqType->clkId))
                {
                    sts = MMPM_STATUS_BADPARM;
                }
                else
                {
                    clkInfoFreq.clkId = mmpmToAdsppmClk[pInfoData->info.pInfoClkFreqType->clkId];
                    clkInfoFreq.forceMeasure = pInfoData->info.pInfoClkFreqType->forceMeasure;
                    clkInfoFreq.clkFreqHz = 0;
                    if(MMPM_INFO_ID_CLK_FREQ == pInfoData->infoId)
                    {
                        sts = RM_GetResourceInfo(Adsppm_Rsc_Id_Core_Clk, (void *)&clkInfoFreq, Adsppm_Info_Type_Current_Value);
                    }
                    else
                    {
                        sts = RM_GetResourceInfo(Adsppm_Rsc_Id_Core_Clk, (void *)&clkInfoFreq, Adsppm_Info_Type_Max_Value);
                    }
                    if(MMPM_STATUS_SUCCESS == sts)
                    {
                        pInfoData->info.pInfoClkFreqType->clkFreqHz = clkInfoFreq.clkFreqHz;
                    }
                }
                break;
            case MMPM_INFO_ID_MIPS_MAX:
                sts = RM_GetResourceInfo(Adsppm_Rsc_Id_Mips, (void *)&mipsValue, Adsppm_Info_Type_Max_Value);
                if(MMPM_STATUS_SUCCESS == sts)
                {
                    pInfoData->info.mipsValue= mipsValue;
                }
                break;
            case MMPM_INFO_ID_BW_MAX:
                sts = RM_GetResourceInfo(Adsppm_Rsc_Id_BW, (void *)&bwValue, Adsppm_Info_Type_Max_Value);
                if(MMPM_STATUS_SUCCESS == sts)
                {
                    pInfoData->info.bwValue= bwValue;
                }
                break;
            default:
                sts = RM_GetClientInfo(clientId, &coreId, &callBackFunc, &clientType);
                break;
            }
        }
        else
        {
            sts = MMPM_STATUS_NOTINITIALIZED;
            ADSPPM_LOG_PRINTF_0(ADSPPM_LOG_LEVEL_ERROR, "Not initialized");
        }
    }
    else
    {
        sts = MMPM_STATUS_SUCCESS;
    }

    ADSPPM_LOG_FUNC_PROFILEEND;
    ADSPPM_LOG_FUNC_EXIT(sts);
    return sts;
}


/******************************************************************************
 *                     MMPM_SetParameter
 *****************************************************************************/
MMPM_STATUS MMPM_SetParameter(uint32 clientId, MmpmParameterConfigType *pParamConfigData)
{
    MMPM_STATUS sts = MMPM_STATUS_SUCCESS;
    ADSPPM_LOG_FUNC_ENTER;
    ADSPPM_LOG_FUNC_PROFILESTART;

    if(!gDISABLEADSPPMREQUESTFLAG)
    {
        if(ADSPPM_IsInitialized())
        {
            if((NULL == pParamConfigData) || (0 == clientId))
            {
                sts = MMPM_STATUS_BADPARM;
                ADSPPM_LOG_PRINTF_1(ADSPPM_LOG_LEVEL_ERROR, "NULL pointer for pParamConfigData or clientid is 0, clientId=%u", clientId);
            }
            else
            {
                AdsppmParameterConfigType paramConfig;
                MmpmMemoryMapType *pMemoryMap;
                switch(pParamConfigData->paramId)
                {
                case MMPM_PARAM_ID_RESOURCE_LIMIT:
                    paramConfig.paramId = Adsppm_Param_Id_Resource_Limit;
                    ADSPPM_LOG_PRINTF_2(ADSPPM_LOG_LEVEL_INFO_EXT, "Setting parameter %u for clientId %u", paramConfig.paramId, clientId);
                    sts = RM_SetParameter(clientId, &paramConfig);
                    break;
                case MMPM_PARAM_ID_CLIENT_OCMEM_MAP:
                    sts = MMPM_STATUS_UNSUPPORTED;
                    ADSPPM_LOG_PRINTF_1(ADSPPM_LOG_LEVEL_ERROR, "Fatal Error:setprameter for OCMEM is unsupported! clientId= %u", clientId);
                    break;
                case MMPM_PARAM_ID_MEMORY_MAP:
                    paramConfig.paramId = Adsppm_Param_Id_Memory_Map;
                    paramConfig.pParamConfig = pParamConfigData->pParamConfig;
                    pMemoryMap = (MmpmMemoryMapType*) pParamConfigData->pParamConfig;
                    if(NULL != pMemoryMap)
                    {
                        ADSPPM_LOG_PRINTF_4(ADSPPM_LOG_LEVEL_INFO, "Setting memory map for clientId %u, memory %u: addr = 0x%X, size = %u",
                                clientId, pMemoryMap->memory, (uint32)pMemoryMap->startAddress, pMemoryMap->size);
                        sts = ACM_SetVirtMemAddressRange(pMemoryMap->memory, pMemoryMap->startAddress, pMemoryMap->size);
                    }
                    else
                    {
                        sts = MMPM_STATUS_BADPARM;
                        ADSPPM_LOG_PRINTF_0(ADSPPM_LOG_LEVEL_ERROR, "Parameter pointer is NULL");
                    }
                    break;
                default:
                    sts = MMPM_STATUS_UNSUPPORTED;
                    ADSPPM_LOG_PRINTF_1(ADSPPM_LOG_LEVEL_ERROR, "Unsupported paramId = %u", pParamConfigData->paramId);
                    break;
                }
            }
        }
        else
        {
            sts = MMPM_STATUS_NOTINITIALIZED;
            ADSPPM_LOG_PRINTF_0(ADSPPM_LOG_LEVEL_ERROR, "Not initialized");
        }
    }
    else
    {
        sts = MMPM_STATUS_SUCCESS;
    }

    ADSPPM_LOG_FUNC_PROFILEEND;
    ADSPPM_LOG_FUNC_EXIT(sts);
    return sts;
}


/******************************************************************************
 *                     MMPM_Init
 *****************************************************************************/
uint32 MMPM_Init(char *cmd_line)
{
    MMPM_STATUS sts = MMPM_STATUS_SUCCESS;
    if(!gDISABLEADSPPMREQUESTFLAG)
    {
        /* Do initialization only once. This cannot be protected using critical section
        since this is done before initializing the lock for critical section */
        if(!ADSPPM_IsInitialized())
        {
            sts = ADSPPM_Init();
        }
    }
    else
    {
        sts = MMPM_STATUS_SUCCESS;
    }
    return (uint32)sts;
}

/** for corebsp image init */
void MMPM_Init_Ext(void)
{
    MMPM_Init(NULL);
}


/******************************************************************************
 *                     MMPM_Deinit
 *****************************************************************************/
/* Deinitialize core MMPM modules */
void MMPM_Deinit(void)
{
    return;
}


/**
 * Async API completion callback notification
 */
uint32 API_doClientCallback(AsyncMgrPipeDataType *receiveData)
{
    uint32 result = 0;
    AdsppmCallbackParamType callbackParam;
    MmpmCompletionCallbackDataType callbackData;
    AdsppmCoreCtxType *pAdsppmCoreCtx = GetAdsppmCoreContext();
    AdsppmHandleType *pAdsppmHandle = NULL;
    ADSPPM_LOG_FUNC_ENTER;
    ADSPPM_LOG_FUNC_PROFILESTART;

    memset(&callbackParam, 0, sizeof(AdsppmCallbackParamType));
    callbackData.reqTag = receiveData->reqTag;
    callbackData.result = receiveData->result;
    callbackParam.eventId = Adsppm_Callback_Event_Id_Async_Complete;
    callbackParam.clientId = receiveData->clientId;
    callbackParam.callbackDataSize = sizeof(callbackData);
    callbackParam.callbackData = &(callbackData);
    pAdsppmHandle = coreUtils_Q_LinearSearch(&pAdsppmCoreCtx->adsppmHandleQ, (coreUtils_Q_CompareFuncType)findAdsppmHandle, (void *)&(callbackParam.clientId));
    if(NULL != pAdsppmHandle)
    {
        if(0 != pAdsppmHandle->ADSPPM_Callback)
        {
            //callback clents call back function
            result = pAdsppmHandle->ADSPPM_Callback(&callbackParam);
        }
    }

    ADSPPM_LOG_FUNC_PROFILEEND;
    ADSPPM_LOG_FUNC_EXIT(result);
    return result;
}

