/*
* Copyright (c) 2013 Qualcomm Technologies, Inc.
* All Rights Reserved.
* Qualcomm Technologies, Inc. Confidential and Proprietary.
*/

/*
 * hal_clkrgm.c
 *
 *  Created on: Feb 13, 2012
 *      Author: yrusakov
 */

#include "adsppm.h"
#include "ULog.h"
#include "ULogFront.h"
#include "adsppm_utils.h"
#include "hal_clkrgm.h"
#include "hal_interrupt.h"
#include "asic.h"
#include "DDIClock.h"
#include "DALStdDef.h"
#include "DALSys.h"
#include "DALDeviceId.h"
#include "ClockDefs.h"
#include "npa.h"
#include "string.h"
#include "qurt_memory.h"
#include "stdlib.h"


#define ADSPPM_ADSP_POWER_ENABLE 1

/* this global flag set to 1 to disable AsicFeatureId_LpassCore_PC_TZ_Handshake feature for standalone adsp image loading */
static volatile uint32 gDISABLETZHANDSHAKE = 0;

/*
 * Data type definitions
 */
typedef struct{
    const AsicClkDescriptorType *pClkDescriptor; //!< Pointer to the clock descriptor from ACM
    union{
        ClockIdType       clkId;     //!< Clock Id for DAL clocks
        npa_client_handle npaHandle; //!< NPA handle for NPA clocks
    } clkHandle;
    uint32                      currentFreq;     //!< Clock frequency currently set
    Hal_ClkRgmEnableDisableType currentState;    //!< Clock enablement state
    Hal_ClkRgmClkSrcType        currentSrc;      //!< Clock source
    uint32                      requestCount;    //!< Number of clients requesting this clock
} HalClk_ClockDescriptorType;

typedef struct{
    const AsicPowerDomainDescriptorType *pPwrDescriptor;
    union{
        ClockPowerDomainIdType domainId;
        npa_client_handle      npaHandle;
    } pwrHandle;
    DALSYSEventHandle                   evtSecure;          //!< Event to signal that XPU configuration has been applied by TZ
    Hal_ClkRgmEnableDisableType         *pSecurityClkState; //!< Array to keep state of the security clocks for TZ handshake
} HalClk_PwrDomainDescriptorType;

typedef struct{
    DALSYSSyncHandle               ctxLock;
    DalDeviceHandle                *pHandle;
    HalClk_ClockDescriptorType     clockDesc[AdsppmClk_EnumMax];
    HalClk_PwrDomainDescriptorType pwrDesc[AsicPowerDomain_EnumMax];
} Hal_ClkRgmCtxType;

static Hal_ClkRgmCtxType gClkRgmCtx;

static void NpaADSPPowerAvailableCb(void *context, unsigned int event_type, void *data, unsigned int data_size);


Adsppm_Status clkrgm_MemCache_Flush(AdsppmMemIdType mem)
{
    Adsppm_Status result = Adsppm_Status_Success;
    AsicAddressRangeType *pAddrRange = ACM_GetVirtMemAddressRange(mem);
    if(NULL != pAddrRange)
    {
        if(pAddrRange->size > 0)
        {
            //flush memory
            int res = QURT_EOK;
            ADSPPM_LOG_PRINTF_3(ADSPPM_LOG_LEVEL_INFO, "Flushing cache for memory %u (addr = 0x%X, size = %u)",
                                mem, (uint32)pAddrRange->startAddr, pAddrRange->size);
            res = qurt_mem_cache_clean(pAddrRange->startAddr, pAddrRange->size, QURT_MEM_CACHE_FLUSH, QURT_MEM_DCACHE);

            if(res != QURT_EOK)
            {
                ADSPPM_LOG_PRINTF_1(ADSPPM_LOG_LEVEL_ERROR, "Cannot flush cache for memory %u", mem);
                result = Adsppm_Status_Failed;
            }
        }
        else
        {
            ADSPPM_LOG_PRINTF_1(ADSPPM_LOG_LEVEL_INFO, "Skipping cache flush for memory %u (mapping not specified)", mem);
        }
    }
    else
    {
        ADSPPM_LOG_PRINTF_1(ADSPPM_LOG_LEVEL_ERROR, "NULL descriptor for memory ID %u", mem);
        result = Adsppm_Status_ResourceNotFound;
    }
    return result;
}


Adsppm_Status clkrgm_EnableDalClock(HalClk_ClockDescriptorType* pClk)
{
    Adsppm_Status result = Adsppm_Status_Success;
    ADSPPM_LOG_PRINTF_1(ADSPPM_LOG_LEVEL_INFO, "Enabled %s", pClk->pClkDescriptor->clkName);
    if(DAL_SUCCESS != DalClock_EnableClock(gClkRgmCtx.pHandle, pClk->clkHandle.clkId))
    {
        ADSPPM_LOG_PRINTF_0(ADSPPM_LOG_LEVEL_ERROR, "DalClock_EnableClock returned failure");
        result = Adsppm_Status_Failed;
    }
    return result;
}


Adsppm_Status clkrgm_DisableDalClock(HalClk_ClockDescriptorType* pClk)
{
    Adsppm_Status result = Adsppm_Status_Success;
    ADSPPM_LOG_PRINTF_1(ADSPPM_LOG_LEVEL_INFO, "Disabled %s", pClk->pClkDescriptor->clkName);
    if(DAL_SUCCESS != DalClock_DisableClock(gClkRgmCtx.pHandle, pClk->clkHandle.clkId))
    {
        ADSPPM_LOG_PRINTF_0(ADSPPM_LOG_LEVEL_ERROR, "DalClock_DisableClock returned failure");
        result = Adsppm_Status_Failed;
    }
    return result;
}


Adsppm_Status clkrgm_EnableDalClockHwCtl(HalClk_ClockDescriptorType* pClk)
{
    Adsppm_Status result = Adsppm_Status_Success;
    ADSPPM_LOG_PRINTF_1(ADSPPM_LOG_LEVEL_INFO_EXT, "Enabled DCG for %s", pClk->pClkDescriptor->clkName);
    if(DAL_SUCCESS != DalClock_ConfigClock(gClkRgmCtx.pHandle, pClk->clkHandle.clkId, CLOCK_CONFIG_LPASS__HW_CTL_ON))
    {
        ADSPPM_LOG_PRINTF_0(ADSPPM_LOG_LEVEL_ERROR, "DalClock_ConfigClock returned failure");
        result = Adsppm_Status_Failed;
    }
    return result;
}


Adsppm_Status clkrgm_DisableDalClockHwCtl(HalClk_ClockDescriptorType* pClk)
{
    Adsppm_Status result = Adsppm_Status_Success;
    ADSPPM_LOG_PRINTF_1(ADSPPM_LOG_LEVEL_INFO_EXT, "Disabled DCG for %s", pClk->pClkDescriptor->clkName);
    if(DAL_SUCCESS != DalClock_ConfigClock(gClkRgmCtx.pHandle, pClk->clkHandle.clkId, CLOCK_CONFIG_LPASS__HW_CTL_OFF))
    {
        ADSPPM_LOG_PRINTF_0(ADSPPM_LOG_LEVEL_ERROR, "DalClock_ConfigClock returned failure");
        result = Adsppm_Status_Failed;
    }
    return result;
}


Adsppm_Status clkrgm_EnableClockBranch(AdsppmClkIdType clk)
{
    Adsppm_Status result = Adsppm_Status_Success;
    HalClk_ClockDescriptorType *pClk = &gClkRgmCtx.clockDesc[clk];

    //Call clock regime to enable clock
    switch(pClk->pClkDescriptor->clkCntlType)
    {
    case AsicClk_CntlOff: //don't enable Always OFF clocks
        break;
    default: //enable clock and disable HW control for all other clocks
        result = clkrgm_EnableDalClock(pClk);
        if(Adsppm_Status_Success == result)
        {
            //Disable HW gating for SW and DCG clocks unconditionally to force the clock On
            result = clkrgm_DisableDalClockHwCtl(pClk);
        }
        if(Adsppm_Status_Success == result)
        {
            ADSPPM_QDSS_EVENT_1(ADSPPM_CLK_ENABLE, clk);
            pClk->currentState = Hal_ClkRgmEnable;
        }
        break;
    }

    return result;
}


Adsppm_Status clkrgm_DisableClockBranch(AdsppmClkIdType clk)
{
    Adsppm_Status result = Adsppm_Status_Success;
    HalClk_ClockDescriptorType *pClk = &gClkRgmCtx.clockDesc[clk];

    if((Adsppm_Mem_None != pClk->pClkDescriptor->memoryId))
    {
        //flush cache before disabling memory clock
        result = clkrgm_MemCache_Flush(pClk->pClkDescriptor->memoryId);
    }

    if(Adsppm_Status_Success == result)
    {
        switch(pClk->pClkDescriptor->clkCntlType)
        {
        case AsicClk_CntlOff:
        case AsicClk_CntlSW:
            //Disable clock
            result = clkrgm_DisableDalClock(pClk);
            if(Adsppm_Status_Success == result)
            {
                ADSPPM_QDSS_EVENT_1(ADSPPM_CLK_DISABLE, clk);
                pClk->currentState = Hal_ClkRgmDisable;
            }
            break;
        case AsicClk_CntlAlwaysON:
            //Don't disable AON clocks
            break;
        case AsicClk_CntlSW_DCG:
            //Put clock under HW control if DCG is Enabled
            //Or disable it if DCG is not enabled
            if(AsicFeatureState_Enabled == ACM_GetFeatureStatus(AsicFeatureId_Ahb_DCG))
            {
                //Enable clock
                result = clkrgm_EnableDalClock(pClk);
                if(Adsppm_Status_Success == result)
                {
                    //Enable HW control
                    result = clkrgm_EnableDalClockHwCtl(pClk);
                }
            }
            else
            {
                //Disable clock
                result = clkrgm_DisableDalClock(pClk);
            }
            if(Adsppm_Status_Success == result)
            {
                ADSPPM_QDSS_EVENT_1(ADSPPM_CLK_DISABLE, clk);
                pClk->currentState = Hal_ClkRgmDisable;
            }
            break;
        case AsicClk_CntlAlwaysON_DCG:
            //Enable clock
            result = clkrgm_EnableDalClock(pClk);
            //Put clock under HW control if DCG is Enabled
            if((Adsppm_Status_Success == result) && (AsicFeatureState_Enabled == ACM_GetFeatureStatus(AsicFeatureId_Ahb_DCG)))
            {
                //Enable HW control
                result = clkrgm_EnableDalClockHwCtl(pClk);
            }
            break;
        default:
            break;
        }
    }

    return result;
}


Adsppm_Status clkrgm_MemCore_Retention(AdsppmClkIdType clk, Hal_ClkRgmMemStateType pwrState)
{
    Adsppm_Status result = Adsppm_Status_Success;
    HalClk_ClockDescriptorType *pClk = &gClkRgmCtx.clockDesc[clk];
    Hal_ClkRgmEnableDisableType currentClkState = Hal_ClkRgmEnable;

    if((AdsppmClk_None < clk) && (AdsppmClk_EnumMax > clk))
    {
        currentClkState = pClk->currentState;

        //Call clock driver to enable the clock
        if(Hal_ClkRgmEnable != currentClkState)
        {
            result = clkrgm_EnableClockBranch(clk);
        }
        //Call clock regime to enable/disable mem core retention
        if(Adsppm_Status_Success == result)
        {
            DALResult dalResult = DAL_SUCCESS;
            ADSPPM_QDSS_EVENT_2(ADSPPM_MEM_PWR, clk, pwrState);
            if(Hal_ClkRgmMemRetain == pwrState)
            {
                ADSPPM_LOG_PRINTF_1(ADSPPM_LOG_LEVEL_INFO, "Memory retention for %s", pClk->pClkDescriptor->clkName);
                dalResult = DalClock_ConfigClock(gClkRgmCtx.pHandle, pClk->clkHandle.clkId, CLOCK_CONFIG_LPASS_CORE_MEM_ON);
            }
            else
            {
                ADSPPM_LOG_PRINTF_1(ADSPPM_LOG_LEVEL_INFO, "Memory collapse for %s", pClk->pClkDescriptor->clkName);
                dalResult = DalClock_ConfigClock(gClkRgmCtx.pHandle, pClk->clkHandle.clkId , CLOCK_CONFIG_LPASS_CORE_MEM_OFF);
            }
            if(DAL_SUCCESS != dalResult)
            {
                ADSPPM_LOG_PRINTF_0(ADSPPM_LOG_LEVEL_ERROR, "DalClock_ConfigClock returned failure");
                result = Adsppm_Status_Failed;
            }
        }
        //restore previous clock state
        if(Adsppm_Status_Success == result)
        {
            if(Hal_ClkRgmEnable != currentClkState)
            {
                result = clkrgm_DisableClockBranch(clk);
            }
        }
    }
    else
    {
        ADSPPM_LOG_PRINTF_0(ADSPPM_LOG_LEVEL_ERROR, "AdsppmClkId out of range");
        result = Adsppm_Status_Failed;
    }

    return result;
}


Adsppm_Status ClkRgm_Init(void)
{
    Adsppm_Status result = Adsppm_Status_Success;
    int i = 0;
    ADSPPM_LOG_FUNC_ENTER;
    ADSPPM_LOG_FUNC_PROFILESTART;

    //Create mutex
    if(DAL_SUCCESS != DALSYS_SyncCreate(DALSYS_SYNC_ATTR_RESOURCE, (DALSYSSyncHandle *)&(gClkRgmCtx.ctxLock), NULL))
    {
        ADSPPM_LOG_PRINTF_0(ADSPPM_LOG_LEVEL_ERROR, "Failed to create lock");
        result = Adsppm_Status_NotInitialized;
    }
    else
    {
        //Register handle for ClkRegime
        if(DAL_SUCCESS != DAL_ClockDeviceAttach(DALDEVICEID_CLOCK, &(gClkRgmCtx.pHandle)))
        {
            ADSPPM_LOG_PRINTF_0(ADSPPM_LOG_LEVEL_ERROR, "DAL_ClockDeviceAttach failed");
            result = Adsppm_Status_Failed;
        }
        else
        {
            //Get information for each power domain from ClkRegime
            for(i = AsicPowerDomain_AON; (Adsppm_Status_Success == result) && (i < AsicPowerDomain_EnumMax); i++)
            {
                HalClk_PwrDomainDescriptorType *pPwr = &gClkRgmCtx.pwrDesc[i];
                pPwr->pPwrDescriptor = ACMClk_GetPwrDomainDescriptor((AsicPowerDomainType)i);

                if(NULL != pPwr->pPwrDescriptor)
                {
                    switch(pPwr->pPwrDescriptor->pwrDomainType)
                    {
                    case AsicRsc_Power_ADSP:
                        //Register with NPA node for vdd voting
                        //Require ClkRegime to be initialized before ADSPPM, so the npa clocks have to be available at this point
                        npa_resource_available_cb(pPwr->pPwrDescriptor->pwrDomainName, NpaADSPPowerAvailableCb, NULL);
                        break;
                    case AsicRsc_Power_Mem:
                        break;
                    case AsicRsc_Power_Core:
                        //Get domain Id from ClkRegime based on clock name
                        //Ignore domains with empty name
                        if(strncmp(pPwr->pPwrDescriptor->pwrDomainName, "", MAX_ADSPPM_CLIENT_NAME))
                        {
                            if(DAL_SUCCESS != DalClock_GetPowerDomainId(gClkRgmCtx.pHandle, pPwr->pPwrDescriptor->pwrDomainName, &(pPwr->pwrHandle.domainId)))
                            {
                                ADSPPM_LOG_PRINTF_1(ADSPPM_LOG_LEVEL_ERROR, "Failed to get Power domain ID for %s", pPwr->pPwrDescriptor->pwrDomainName);
                                result = Adsppm_Status_Failed;
                            }
                            else
                            {
                                if((AsicFeatureState_Enabled == ACM_GetFeatureStatus(AsicFeatureId_LpassCore_PC_TZ_Handshake)) && (0 == gDISABLETZHANDSHAKE))
                                {
                                    if(DAL_SUCCESS != DALSYS_EventCreate(DALSYS_EVENT_ATTR_CLIENT_DEFAULT, &(pPwr->evtSecure), NULL))
                                    {
                                        ADSPPM_LOG_PRINTF_1(ADSPPM_LOG_LEVEL_ERROR, "Failed to create Event for %s", pPwr->pPwrDescriptor->pwrDomainName);
                                        result = Adsppm_Status_Failed;
                                    }
                                    else
                                    {
                                        //Register event and Enable TZ ack interrupt
                                        result = Intr_RegisterEvent(pPwr->pPwrDescriptor->intrReinitDone, pPwr->evtSecure);
                                    }
                                    pPwr->pSecurityClkState = malloc(sizeof(Hal_ClkRgmEnableDisableType) * pPwr->pPwrDescriptor->securityClocks.numClocks);
                                    if(NULL == pPwr->pSecurityClkState)
                                    {
                                        result = Adsppm_Status_Failed;
                                    }
                                }
                            }
                        }
                        break;
                    default:
                        break;
                    }
                }
                else
                {
                    ADSPPM_LOG_PRINTF_1(ADSPPM_LOG_LEVEL_ERROR, "Failed to get Pwr descriptor for power domain %u", i);
                    result = Adsppm_Status_Failed;
                }
            }

            //Get information for each clock from ClkRegime
            for(i = AdsppmClk_None; (Adsppm_Status_Success == result) && (i < AdsppmClk_EnumMax); i++)
            {
                HalClk_ClockDescriptorType *pClk = &gClkRgmCtx.clockDesc[i];
                pClk->pClkDescriptor = ACMClk_GetClockDescriptor((AdsppmClkIdType)i);
                pClk->currentFreq = 0;
                pClk->currentSrc = Hal_ClkRgmClkSrc_Primary;
                pClk->requestCount = 0;

                if(NULL != pClk->pClkDescriptor)
                {
                    switch(pClk->pClkDescriptor->clkType)
                    {
                    case AsicClk_TypeNpa:
                        //Register with NPA node
                        //Require ClkRegime to be initialized before ADSPPM,
                        //so the npa clocks have to be available at this point
                        //npa_resource_available_cb(pClk->pClkDescriptor->clkName, NpaClkAvailableCb, NULL);
                        pClk->clkHandle.npaHandle = npa_create_sync_client(pClk->pClkDescriptor->clkName, "ADSPPM", NPA_CLIENT_REQUIRED);
                        if(NULL == pClk->clkHandle.npaHandle)
                        {
                            ADSPPM_LOG_PRINTF_1(ADSPPM_LOG_LEVEL_ERROR, "Failed to create NPA client for %s", pClk->pClkDescriptor->clkName);
                            result = Adsppm_Status_Failed;
                        }
                        break;
                    case AsicClk_TypeDalFreqSet:
                    case AsicClk_TypeDalEnable:
                    case AsicClk_TypeDalDomainSrc:
                        //Get clock Id from ClkRegime based on clock name
                        if(DAL_SUCCESS != DalClock_GetClockId(gClkRgmCtx.pHandle, pClk->pClkDescriptor->clkName, &(pClk->clkHandle.clkId)))
                        {
                            ADSPPM_LOG_PRINTF_1(ADSPPM_LOG_LEVEL_ERROR, "Failed to get ClkId for %s", pClk->pClkDescriptor->clkName);
                            result = Adsppm_Status_Failed;
                        }
                        break;
                    default:
                        break;
                    }
                }
                else
                {
                    ADSPPM_LOG_PRINTF_1(ADSPPM_LOG_LEVEL_ERROR, "Failed to get Clk descriptor for clk %u", i);
                    result = Adsppm_Status_Failed;
                }

                //Set initial state for each clock
                if(Adsppm_Status_Success == result)
                {
                    //Only proceed for clocks that are present in the chip.
                    //Otherwise just skip the setting
                    switch(pClk->pClkDescriptor->clkCntlType)
                    {
                    case AsicClk_CntlAlwaysON:
                        //Enable AON clock
                        pClk->currentState = Hal_ClkRgmDisable;
                        result = ClkRgm_EnableClock(i, Hal_ClkRgmEnable);
                        break;
                    case AsicClk_CntlOff:
                        //Disable AOFF clock
                        pClk->currentState = Hal_ClkRgmEnable;
                        result = ClkRgm_EnableClock(i, Hal_ClkRgmDisable);
                        break;
                    case AsicClk_CntlAlwaysON_DCG:
                        if(AsicFeatureState_Enabled == ACM_GetFeatureStatus(AsicFeatureId_Ahb_DCG))
                        {
                            //Enable clock and enable HW control
                            //That will be handled by ClkRgm_EnableClock internally if clock supports DCG and is disabled
                            pClk->currentState = Hal_ClkRgmEnable;
                            result = ClkRgm_EnableClock(i, Hal_ClkRgmDisable);
                        }
                        else
                        {
                            //Enable AON clock
                            pClk->currentState = Hal_ClkRgmDisable;
                            result = ClkRgm_EnableClock(i, Hal_ClkRgmEnable);
                        }
                        break;
                    case AsicClk_CntlSW:
                    case AsicClk_CntlSW_DCG:
                        //Disable clock or Enable clock and enable HW control
                        //That will be handled by ClkRgm_EnableClock internally if clock supports DCG and is disabled
                        pClk->currentState = Hal_ClkRgmEnable;
                        result = ClkRgm_EnableClock(i, Hal_ClkRgmDisable);
                        break;
                    default: //Don't touch other clocks here
                        break;
                    }

                    if(Adsppm_Status_Success == result)
                    {
                        switch(pClk->pClkDescriptor->clkMemCntlType)
                        {
                        case AsicClk_MemCntlAlwaysRetain:
                            //Call clock regime to enable mem core retention
                            result = clkrgm_MemCore_Retention(i, Hal_ClkRgmMemRetain);
                            break;
                        default: //Don't touch other clocks here
                            break;
                        }
                    }
                }
            }
        }
        if(Adsppm_Status_Success != result)
        {
            DALSYS_DestroyObject((DALSYSSyncHandle *)&(gClkRgmCtx.ctxLock));
            gClkRgmCtx.ctxLock = NULL;
        }
    }
    ADSPPM_LOG_FUNC_PROFILEEND;
    ADSPPM_LOG_FUNC_EXIT(result);
    return result;
}


static void NpaADSPPowerAvailableCb(void *context, unsigned int event_type, void *data, unsigned int data_size)
{
    ADSPPM_LOG_FUNC_ENTER;
    ADSPPM_LOG_FUNC_PROFILESTART;
    HalClk_PwrDomainDescriptorType *pPwr = &gClkRgmCtx.pwrDesc[AsicPowerDomain_Adsp];
    pPwr->pwrHandle.npaHandle = npa_create_sync_client(pPwr->pPwrDescriptor->pwrDomainName, "adsppmadsppower", NPA_CLIENT_REQUIRED);
    if(NULL == pPwr->pwrHandle.npaHandle)
    {
        ADSPPM_LOG_PRINTF_0(ADSPPM_LOG_LEVEL_ERROR, "Failed to create client for ADSP power");
    }
    ADSPPM_LOG_FUNC_PROFILEEND;
    ADSPPM_LOG_FUNC_EXIT(0);
}


/**
 * @fn ClkRgm_CalcClockFrequency - get clock frequency through clock regime calculate from oscillator
 * @param pFreq - out put frequency in Hz
 */
Adsppm_Status ClkRgm_CalcClockFrequency(AdsppmClkIdType clk, uint32 *pFreq)
{
    Adsppm_Status result = Adsppm_Status_Success;
    ADSPPM_LOG_FUNC_ENTER;
    ADSPPM_LOG_FUNC_PROFILESTART;
    if((AdsppmClk_None < clk) && (AdsppmClk_EnumMax > clk) && (NULL != pFreq))
    {
        if(NULL != gClkRgmCtx.ctxLock)
        {
            //TODO: USE calulate clock now, later on will use getfreq api from clock regime
            HalClk_ClockDescriptorType *pClk = &gClkRgmCtx.clockDesc[clk];
            if((NULL != pClk->pClkDescriptor) && (AdsppmClk_None != pClk->pClkDescriptor->clkId))
            {
                if(pClk->currentState == Hal_ClkRgmEnable)
                {
                    if(pClk->clkHandle.clkId != NULL)
                    {
                        if(DAL_SUCCESS != DalClock_CalcClockFrequency(gClkRgmCtx.pHandle, pClk->clkHandle.clkId, pFreq))
                        {
                            ADSPPM_LOG_PRINTF_0(ADSPPM_LOG_LEVEL_ERROR, "DalClock_CalcClockFrequency returned failure");
                            result = Adsppm_Status_Failed;
                        }
                        else
                        {
                            ADSPPM_LOG_PRINTF_3(ADSPPM_LOG_LEVEL_INFO, "Got clock frequency %u for %s. currentset freq=%u",
                                    *pFreq, pClk->pClkDescriptor->clkName, pClk->currentFreq);
                        }
                    }
                    else
                    {
                        if(AdsppmClk_None != pClk->pClkDescriptor->clkSrcId)
                        {
                            //Recursive call here.
                            //We are relying on the lock to work in recursive cases as it is stated in the API description
                            result = ClkRgm_CalcClockFrequency(pClk->pClkDescriptor->clkSrcId, pFreq);
                        }
                    }
                }
                else
                {
                    *pFreq = 0;
                }
            }
            else
            {
                ADSPPM_LOG_PRINTF_0(ADSPPM_LOG_LEVEL_INFO, "bad pClk->pClkDescriptor->clkId");
                result = Adsppm_Status_BadParm;
            }
        }
        else
        {
            result = Adsppm_Status_NotInitialized;
        }
    }
    else
    {
        result = Adsppm_Status_BadParm;
        ADSPPM_LOG_PRINTF_0(ADSPPM_LOG_LEVEL_ERROR, "bad clk or pFreq");
    }
    ADSPPM_LOG_FUNC_PROFILEEND;
    ADSPPM_LOG_FUNC_EXIT(result);
    return result;
}


Adsppm_Status ClkRgm_GetClockFrequency(AdsppmClkIdType clk, uint32 *pFreq)
{
    Adsppm_Status result = Adsppm_Status_Success;
    npa_query_type sQueryResult;
    npa_query_status eNpaStatus = NPA_QUERY_SUCCESS;
    ADSPPM_LOG_FUNC_ENTER;
    ADSPPM_LOG_FUNC_PROFILESTART;
    if((AdsppmClk_None < clk) && (AdsppmClk_EnumMax > clk) && (NULL != pFreq))
    {
        if(NULL != gClkRgmCtx.ctxLock)
        {
            HalClk_ClockDescriptorType *pClk = &gClkRgmCtx.clockDesc[clk];
            if(pClk->currentState)
            {
                if(AsicClk_TypeNpa == pClk->pClkDescriptor->clkType)
                {
                     eNpaStatus = npa_query_by_name(pClk->pClkDescriptor->clkName, NPA_QUERY_CURRENT_STATE, &sQueryResult);
                     if(0 != eNpaStatus)
                     {
                         ADSPPM_LOG_PRINTF_1(ADSPPM_LOG_LEVEL_ERROR, "npa_query_by_name: Failed due to NPA error %u", eNpaStatus);
                         result = Adsppm_Status_Failed;
                     }
                     else
                     {
                         *pFreq = sQueryResult.data.state;
                     }
                }
                else
                {
                    *pFreq = pClk->currentFreq;
                }
            }
            else
            {
                *pFreq = 0;
            }
        }
        else
        {
            result = Adsppm_Status_NotInitialized;
        }
    }
    else
    {
        result = Adsppm_Status_NullPointer;
    }
    ADSPPM_LOG_FUNC_PROFILEEND;
    ADSPPM_LOG_FUNC_EXIT(result);
    return result;
}


/**
 * @fn ClkRgm_SetClock - Set clock frequency via ClkRegime. Applicable to non ahb branches only
 * @param freq - frequency in Hz
 */
Adsppm_Status ClkRgm_SetClock(AdsppmClkIdType clk, uint32 freq)
{
    Adsppm_Status result = Adsppm_Status_Success;
    ADSPPM_LOG_FUNC_ENTER;
    ADSPPM_LOG_FUNC_PROFILESTART;

    if((AdsppmClk_None < clk) && (AdsppmClk_EnumMax > clk))
    {
        if(NULL != gClkRgmCtx.ctxLock)
        {
            HalClk_ClockDescriptorType *pClk = &gClkRgmCtx.clockDesc[clk];
            if(NULL != pClk->pClkDescriptor)
            {
                //Lock HW layer
                adsppm_lock(gClkRgmCtx.ctxLock);

                if(pClk->currentFreq != freq)
                {
                    uint32 previousFreq = pClk->currentFreq;
                    switch(pClk->pClkDescriptor->clkType)
                    {
                    case AsicClk_TypeNpa:
                        //Use NPA node
                        if(NULL != pClk->clkHandle.npaHandle)
                        {
                            if(0 < freq)
                            {
                                ADSPPM_LOG_PRINTF_2(ADSPPM_LOG_LEVEL_INFO, "NPA request for %s, state: %u", pClk->pClkDescriptor->clkName, freq);
                                ADSPPM_QDSS_EVENT_3(ADSPPM_CLK_SET, clk, freq, freq);
                                //issue NPA request for specified frequency
                                //Translate from Hz to kHz first
                                npa_issue_required_request(pClk->clkHandle.npaHandle, freq/1000);
                            }
                        }
                        else
                        {
                            ADSPPM_LOG_PRINTF_0(ADSPPM_LOG_LEVEL_ERROR, "NULL NPA handle");
                            result = Adsppm_Status_Failed;
                        }
                        break;
                    case AsicClk_TypeDalEnable:
                        //Use clock source from clock descriptor
                        if(AdsppmClk_None != pClk->pClkDescriptor->clkSrcId)
                        {
                            ADSPPM_LOG_PRINTF_2(ADSPPM_LOG_LEVEL_INFO, "Requested freq %u for %s", freq, pClk->pClkDescriptor->clkName);
                            result = ClkRgm_SetClock(pClk->pClkDescriptor->clkSrcId, freq);
                        }
                        break;
                    case AsicClk_TypeDalFreqSet:
                    case AsicClk_TypeDalDomainSrc:
                        //Call clock regime to set at least requested frequency
                        //Disable clock branch if 0 frequency is requested
                        if(0 < freq)
                        {
                            //attempt to set frequency at least as requested
                            if(DAL_SUCCESS != DalClock_SetClockFrequency(gClkRgmCtx.pHandle, pClk->clkHandle.clkId, freq, CLOCK_FREQUENCY_HZ_AT_LEAST, &pClk->currentFreq))
                            {
                                //Try to request cap the frequency if the previous request has failed because of exceeding max for this clock
                                if(DAL_SUCCESS != DalClock_SetClockFrequency(gClkRgmCtx.pHandle, pClk->clkHandle.clkId, freq, CLOCK_FREQUENCY_HZ_CLOSEST, &pClk->currentFreq))
                                {
                                    ADSPPM_LOG_PRINTF_0(ADSPPM_LOG_LEVEL_ERROR, "DalClock_SetClockFrequency returned failure");
                                    result = Adsppm_Status_Failed;
                                }
                                else
                                {
                                    ADSPPM_LOG_PRINTF_3(ADSPPM_LOG_LEVEL_INFO, "Failed to set freq %u for %s. Capped freq=%u", freq, pClk->pClkDescriptor->clkName, pClk->currentFreq);
                                }
                            }
                            else
                            {
                                ADSPPM_LOG_PRINTF_3(ADSPPM_LOG_LEVEL_INFO, "Requested frequency %u for %s. Set freq=%u", freq, pClk->pClkDescriptor->clkName, pClk->currentFreq);
                                ADSPPM_QDSS_EVENT_3(ADSPPM_CLK_SET, pClk->pClkDescriptor->clkId, freq, pClk->currentFreq);
                            }
                        }
                        break;
                    default:
                        break;
                    }

                    if(Adsppm_Status_Success == result)
                    {
                        pClk->currentFreq = freq;
                        if((0 < freq) && (0 == previousFreq))
                        {
                            result = ClkRgm_EnableClock(clk, Hal_ClkRgmEnable);
                        }
                        if(0 == freq)
                        {
                            result = ClkRgm_EnableClock(clk, Hal_ClkRgmDisable);
                        }
                    }
                }

                //Unlock HW layer
                adsppm_unlock(gClkRgmCtx.ctxLock);
            }
            else
            {
                ADSPPM_LOG_PRINTF_0(ADSPPM_LOG_LEVEL_ERROR, "invalid HalClk_ClockDescriptor");
                result = Adsppm_Status_BadParm;
            }
        }
        else
        {
            result = Adsppm_Status_NotInitialized;
        }
    }
    else
    {
        ADSPPM_LOG_PRINTF_0(ADSPPM_LOG_LEVEL_ERROR, "AdsppmClkId out of range");
        result = Adsppm_Status_BadParm;
    }

    ADSPPM_LOG_FUNC_PROFILEEND;
    ADSPPM_LOG_FUNC_EXIT(result);
    return result;
}


Adsppm_Status ClkRgm_EnableClock(AdsppmClkIdType clk, Hal_ClkRgmEnableDisableType stateRequested)
{
    Adsppm_Status result = Adsppm_Status_Success;
    Hal_ClkRgmEnableDisableType state = stateRequested;
    ADSPPM_LOG_FUNC_ENTER;
    ADSPPM_LOG_FUNC_PROFILESTART;

    if((AdsppmClk_None < clk) && (AdsppmClk_EnumMax > clk))
    {
        if(NULL != gClkRgmCtx.ctxLock)
        {
            HalClk_ClockDescriptorType *pClk = &gClkRgmCtx.clockDesc[clk];
            if(NULL != pClk->pClkDescriptor)
            {
                //Lock HW layer
                adsppm_lock(gClkRgmCtx.ctxLock);

                //Update reference count
                ADSPPM_LOG_PRINTF_2(ADSPPM_LOG_LEVEL_INFO_EXT, "Clock=%s, requested state=%u", pClk->pClkDescriptor->clkName, stateRequested);
                ADSPPM_LOG_PRINTF_2(ADSPPM_LOG_LEVEL_DEBUG, "current counter=%u, current state=%u", pClk->requestCount, pClk->currentState);
                if(Hal_ClkRgmEnable == stateRequested)
                {
                    pClk->requestCount++;
                }
                else
                {
                    if(pClk->requestCount > 0) pClk->requestCount--;
                    //Override the requested state if the request counter is not 0
                    if(pClk->requestCount > 0) state = Hal_ClkRgmEnable;
                }
                ADSPPM_LOG_PRINTF_2(ADSPPM_LOG_LEVEL_DEBUG, "resulting counter=%u, resulting state=%u", pClk->requestCount, state);

                if(pClk->currentState != state)
                {
                    switch(pClk->pClkDescriptor->clkType)
                    {
                    case AsicClk_TypeNpa:
                        //Use NPA node
                        //Require ClkRegime to be initialized before ADSPPM, so the npa clocks have to be available at this point
                        if(NULL != pClk->clkHandle.npaHandle)
                        {
                            if(Hal_ClkRgmEnable == state)
                            {
                                if(0 == pClk->currentFreq)
                                {
                                    npa_query_type query;
                                    query.type = NPA_QUERY_TYPE_VALUE;
                                    //Get min frequency for this clock
                                    if(NPA_QUERY_SUCCESS == npa_query_by_client(pClk->clkHandle.npaHandle, CLOCK_NPA_QUERY_MIN_FREQ_KHZ, &query))
                                    {
                                        ADSPPM_LOG_PRINTF_2(ADSPPM_LOG_LEVEL_INFO, "NPA request for %s, state: %u", pClk->pClkDescriptor->clkName, query.data.value);
                                        ADSPPM_QDSS_EVENT_3(ADSPPM_CLK_SET, clk, query.data.value, query.data.value);
                                        //issue NPA request for min frequency
                                        npa_issue_required_request(pClk->clkHandle.npaHandle, query.data.value);
                                        pClk->currentFreq = query.data.value;
                                        pClk->currentState = Hal_ClkRgmEnable;
                                    }
                                    else
                                    {
                                        ADSPPM_LOG_PRINTF_0(ADSPPM_LOG_LEVEL_ERROR, "NPA query returned failure");
                                        result = Adsppm_Status_Failed;
                                    }
                                }
                                else
                                {
                                    pClk->currentState = Hal_ClkRgmEnable;
                                }
                            }
                            else
                            {
                                ADSPPM_LOG_PRINTF_1(ADSPPM_LOG_LEVEL_INFO, "Complete NPA request for %s", pClk->pClkDescriptor->clkName);
                                ADSPPM_QDSS_EVENT_3(ADSPPM_CLK_SET, clk, 0, 0);
                                //release NPA request
                                npa_complete_request(pClk->clkHandle.npaHandle);
                                pClk->currentFreq = 0;
                                pClk->currentState = Hal_ClkRgmDisable;
                            }
                        }
                        else
                        {
                            ADSPPM_LOG_PRINTF_1(ADSPPM_LOG_LEVEL_ERROR, "NULL npa handle for %s", pClk->pClkDescriptor->clkName);
                            result = Adsppm_Status_Failed;
                        }
                        break;
                    case AsicClk_TypeDalFreqSet:
                    case AsicClk_TypeDalEnable:
                    case AsicClk_TypeDalDomainSrc:
                        if(Hal_ClkRgmEnable == state)
                        {
                            result = clkrgm_EnableClockBranch(clk);
                        }
                        else
                        {
                            result = clkrgm_DisableClockBranch(clk);
                        }
                        break;
                    default:
                        break;
                    }
                }

                //Unlock HW layer
                adsppm_unlock(gClkRgmCtx.ctxLock);
            }
            else
            {
                ADSPPM_LOG_PRINTF_0(ADSPPM_LOG_LEVEL_ERROR, "invalid HalClk_ClockDescriptor");
                result = Adsppm_Status_BadParm;
            }
        }
        else
        {
            result = Adsppm_Status_NotInitialized;
        }
    }
    else
    {
        ADSPPM_LOG_PRINTF_0(ADSPPM_LOG_LEVEL_ERROR, "AdsppmClkId out of range");
        result = Adsppm_Status_BadParm;
    }

    ADSPPM_LOG_FUNC_PROFILEEND;
    ADSPPM_LOG_FUNC_EXIT(result);
    return result;
}


Adsppm_Status ClkRgm_SelectClkSource(AdsppmClkIdType clk, Hal_ClkRgmClkSrcType clkSrc)
{
    Adsppm_Status result = Adsppm_Status_Success;
    ADSPPM_LOG_FUNC_ENTER;
    ADSPPM_LOG_FUNC_PROFILESTART;
    if((AdsppmClk_None < clk) && (AdsppmClk_EnumMax > clk))
    {
        if(NULL != gClkRgmCtx.ctxLock)
        {
            HalClk_ClockDescriptorType *pClk = &gClkRgmCtx.clockDesc[clk];
            if(NULL != pClk->pClkDescriptor)
            {
                //Lock HW layer
                adsppm_lock(gClkRgmCtx.ctxLock);
                if(pClk->currentSrc != clkSrc)
                {
                    switch(pClk->pClkDescriptor->clkType)
                    {
                    case AsicClk_TypeNpa:
                    case AsicClk_TypeDalFreqSet:
                    case AsicClk_TypeDalEnable:
                    case AsicClk_TypeDalDomainSrc:
                        ADSPPM_LOG_PRINTF_2(ADSPPM_LOG_LEVEL_INFO, "Requested clkSrc %u for %s", clkSrc, pClk->pClkDescriptor->clkName);
                        if(DAL_SUCCESS != DalClock_SelectClockSource(gClkRgmCtx.pHandle, pClk->clkHandle.clkId, clkSrc))
                        {
                            ADSPPM_LOG_PRINTF_0(ADSPPM_LOG_LEVEL_ERROR, "ClkRegime returned failure for clksrc select");
                            result = Adsppm_Status_Failed;
                        }
                        else
                        {
                            pClk->currentSrc = clkSrc;
                        }
                        break;
                    default:
                        break;
                    }
                }
                //Unlock HW layer
                adsppm_unlock(gClkRgmCtx.ctxLock);
            }
            else
            {
                ADSPPM_LOG_PRINTF_0(ADSPPM_LOG_LEVEL_ERROR, "invalid HalClk_ClockDescriptor");
                result = Adsppm_Status_BadParm;
            }
        }
        else
        {
            result = Adsppm_Status_NotInitialized;
        }
    }
    else
    {
        ADSPPM_LOG_PRINTF_0(ADSPPM_LOG_LEVEL_ERROR, "AdsppmClkId out of range");
        result = Adsppm_Status_BadParm;
    }
    ADSPPM_LOG_FUNC_PROFILEEND;
    ADSPPM_LOG_FUNC_EXIT(result);
    return result;
}


/**
 * @fn ClkRgm_EnableHWClockCntl - enables/disables HW clock control for the specified clock
 * Function will return success if the clock doesn't support DCG
 * @param clk - clock ID
 * @param state - specifies whether or not HW control should be enabled
 * @return completion status
 */
Adsppm_Status ClkRgm_EnableHWClockCntl(AdsppmClkIdType clk, Hal_ClkRgmEnableDisableType state)
{
    Adsppm_Status result = Adsppm_Status_Success;
    ADSPPM_LOG_FUNC_ENTER;
    ADSPPM_LOG_FUNC_PROFILESTART;
    if((AdsppmClk_None < clk) && (AdsppmClk_EnumMax > clk))
    {
        if(NULL != gClkRgmCtx.ctxLock)
        {
            HalClk_ClockDescriptorType *pClk = &gClkRgmCtx.clockDesc[clk];
            if(NULL != pClk->pClkDescriptor)
            {
                //Lock HW layer
                adsppm_lock(gClkRgmCtx.ctxLock);
                switch(pClk->pClkDescriptor->clkType)
                {
                case AsicClk_TypeNpa:
                    break;
                default:
                    switch (pClk->pClkDescriptor->clkCntlType)
                    {
                    case AsicClk_CntlSW_DCG:
                    case AsicClk_CntlAlwaysON_DCG:
                        //Call clock regime to enable/disable HW control for the clock
                        if(Hal_ClkRgmEnable == state)
                        {
                            result = clkrgm_EnableDalClockHwCtl(pClk);
                        }
                        else
                        {
                            result = clkrgm_DisableDalClockHwCtl(pClk);
                        }
                        break;
                    default:
                        break;
                    }
                    break;
                }
                //Unlock HW layer
                adsppm_unlock(gClkRgmCtx.ctxLock);
            }
            else
            {
                ADSPPM_LOG_PRINTF_0(ADSPPM_LOG_LEVEL_ERROR, "invalid HalClk_ClockDescriptor");
                result = Adsppm_Status_BadParm;
            }
        }
        else
        {
            result = Adsppm_Status_NotInitialized;
        }
    }
    else
    {
        ADSPPM_LOG_PRINTF_0(ADSPPM_LOG_LEVEL_ERROR, "AdsppmClkId out of range");
        result = Adsppm_Status_BadParm;
    }
    ADSPPM_LOG_FUNC_PROFILEEND;
    ADSPPM_LOG_FUNC_EXIT(result);
    return result;
}


/**
 * @fn clkrgm_ReinitPwrDomain - trigger an interrupt to notify the power island is UP and wait for acknowledgment
 * @param clkrgm_Reinit - pointer to power domain descriptor
 */
Adsppm_Status clkrgm_ReinitPwrDomain(HalClk_PwrDomainDescriptorType *pPwrDesc)
{
    Adsppm_Status result = Adsppm_Status_Success;
    int i = 0;
    ADSPPM_LOG_FUNC_ENTER;
    ADSPPM_LOG_FUNC_PROFILESTART;

    if((AsicFeatureState_Enabled == ACM_GetFeatureStatus(AsicFeatureId_LpassCore_PC_TZ_Handshake)) && (0 == gDISABLETZHANDSHAKE))
    {
        if((pPwrDesc->pPwrDescriptor->intrReinitTrigger < DALIPCINT_NUM_INTS) && (pPwrDesc->pPwrDescriptor->intrReinitDone > 0))
        {
            ADSPPM_LOG_PRINTF_0(ADSPPM_LOG_LEVEL_INFO_EXT, "Acquiring event ownership");
            //Take event ownership so we can wait on the event
            if(DAL_SUCCESS != DALSYS_EventCtrl(pPwrDesc->evtSecure, DALSYS_EVENT_CTRL_ACCQUIRE_OWNERSHIP))
            {
                ADSPPM_LOG_PRINTF_0(ADSPPM_LOG_LEVEL_ERROR, "Failed to acquire the event ownership");
                result = Adsppm_Status_Failed;
            }
            else
            {
                //Only try handshake if interrupts are specified
                if(DAL_SUCCESS != DALSYS_EventCtrl(pPwrDesc->evtSecure, DALSYS_EVENT_CTRL_RESET))
                {
                    ADSPPM_LOG_PRINTF_0(ADSPPM_LOG_LEVEL_ERROR, "Failed to reset event before interrupt");
                    result = Adsppm_Status_Failed;
                }
                else
                {
                    //Enable clocks required for xPU access
                    //remember state of the clocks before enabling
                    if(NULL != pPwrDesc->pPwrDescriptor->securityClocks.pClocks)
                    {
                        for(i = 0; (i < pPwrDesc->pPwrDescriptor->securityClocks.numClocks) && (Adsppm_Status_Success == result); i++)
                        {
                            pPwrDesc->pSecurityClkState[i] = gClkRgmCtx.clockDesc[pPwrDesc->pPwrDescriptor->securityClocks.pClocks[i]].currentState;
                            result = ClkRgm_EnableClock(pPwrDesc->pPwrDescriptor->securityClocks.pClocks[i], Hal_ClkRgmEnable);
                        }
                    }
                    if(Adsppm_Status_Success == result)
                    {
                        //Trigger TZ interrupt
                        ADSPPM_LOG_PRINTF_0(ADSPPM_LOG_LEVEL_INFO, "Triggering TZ interrupt");
                        result = Intr_TriggerInterrupt(pPwrDesc->pPwrDescriptor->intrReinitTrigger);
                        if(Adsppm_Status_Success == result)
                        {
                            ADSPPM_LOG_PRINTF_0(ADSPPM_LOG_LEVEL_INFO_EXT, "Waiting for TZ ack...");
                            if(DAL_SUCCESS ==DALSYS_EventWait(pPwrDesc->evtSecure))
                            {
                                ADSPPM_LOG_PRINTF_0(ADSPPM_LOG_LEVEL_INFO, "Ack received from TZ");
                                if(DAL_SUCCESS != DALSYS_EventCtrl(pPwrDesc->evtSecure, DALSYS_EVENT_CTRL_RESET))
                                {
                                    ADSPPM_LOG_PRINTF_0(ADSPPM_LOG_LEVEL_ERROR,"Failed to reset event");
                                    result = Adsppm_Status_Failed;
                                }
                            }
                            else
                            {
                                ADSPPM_LOG_PRINTF_0(ADSPPM_LOG_LEVEL_ERROR, "Event wait failed");
                                result = Adsppm_Status_Failed;
                            }
                        }
                        if(NULL != pPwrDesc->pPwrDescriptor->securityClocks.pClocks)
                        {
                            //Restore original state ofr clocks required for xPU access
                            for(i = 0; (i < pPwrDesc->pPwrDescriptor->securityClocks.numClocks) && (Adsppm_Status_Success == result); i++)
                            {
                                result = ClkRgm_EnableClock(pPwrDesc->pPwrDescriptor->securityClocks.pClocks[i], pPwrDesc->pSecurityClkState[i]);
                            }
                        }
                    }
                }
            }
        }
    }

    ADSPPM_LOG_FUNC_PROFILEEND;
    ADSPPM_LOG_FUNC_EXIT(result);
    return result;
}


Adsppm_Status ClkRgm_RequestPower(AsicPowerDomainType blk, Hal_ClkRgmEnableDisableType state)
{
    Adsppm_Status result = Adsppm_Status_Success;
    ADSPPM_LOG_FUNC_ENTER;
    ADSPPM_LOG_FUNC_PROFILESTART;

    if(blk < AsicPowerDomain_EnumMax)
    {
        if(NULL != gClkRgmCtx.ctxLock)
        {
            HalClk_PwrDomainDescriptorType *pPwr = &gClkRgmCtx.pwrDesc[blk];
            DALResult dalResult = DAL_SUCCESS;
            if(NULL != pPwr->pPwrDescriptor)
            {
                //Lock HW layer
                adsppm_lock(gClkRgmCtx.ctxLock);

                switch(pPwr->pPwrDescriptor->pwrDomainType)
                {
                case AsicRsc_Power_ADSP:
                    //Use NPA node
                    //Require ClkRegime to be initialized before ADSPPM, so the npa clocks have to be available at this point
                    /* Disabling voting now as the node is not available*/
                    if(NULL != pPwr->pwrHandle.npaHandle)
                    {
                        if(Hal_ClkRgmEnable == state)
                        {
                            //issue NPA request for power
                            npa_issue_required_request(pPwr->pwrHandle.npaHandle, ADSPPM_ADSP_POWER_ENABLE);
                            ADSPPM_LOG_PRINTF_2(ADSPPM_LOG_LEVEL_INFO, "Enabled ADSP power domain, NPA node: %s @ %u", pPwr->pPwrDescriptor->pwrDomainName, ADSPPM_ADSP_POWER_ENABLE);
                            ADSPPM_QDSS_EVENT_1(ADSPPM_PWR_REQ, blk);
                        }
                        else
                        {
                            //release NPA request
                            npa_complete_request(pPwr->pwrHandle.npaHandle);
                            ADSPPM_LOG_PRINTF_1(ADSPPM_LOG_LEVEL_INFO, "Disabled ADSP power domain, NPA node: %s", pPwr->pPwrDescriptor->pwrDomainName);
                            ADSPPM_QDSS_EVENT_1(ADSPPM_PWR_REL, blk);
                        }
                    }
                    else
                    {
                        //result = Adsppm_Status_Failed;
                        ADSPPM_LOG_PRINTF_0(ADSPPM_LOG_LEVEL_ERROR, "ADSP power NPA handle is NULL");
                    }
                    break;
                case AsicRsc_Power_Mem:
                    //Call clock regime to enable/disable mem core retention
                    result = clkrgm_MemCore_Retention(pPwr->pPwrDescriptor->clkId, (state == Hal_ClkRgmEnable)?Hal_ClkRgmMemRetain:Hal_ClkRgmMemCollapse);
                    break;
                case AsicRsc_Power_Core:
                    //Call clock regime to enable/disable power domain
                    //only call disable if the LPASS_Core PC feature is enabled
                    //otherwise keep LPASS Core power enabled
                    if(Hal_ClkRgmEnable == state)
                    {
                        dalResult = DalClock_EnablePowerDomain(gClkRgmCtx.pHandle, pPwr->pwrHandle.domainId);
                        ADSPPM_LOG_PRINTF_1(ADSPPM_LOG_LEVEL_INFO, "Enabled power domain %s", pPwr->pPwrDescriptor->pwrDomainName);
                        ADSPPM_QDSS_EVENT_1(ADSPPM_PWR_REQ, blk);
                        if(DAL_SUCCESS == dalResult)
                        {
                            //Trigger TZ to reprogram LPASS Core xPUs
                            result = clkrgm_ReinitPwrDomain(pPwr);
                        }
                    }
                    else
                    {
                        dalResult = DalClock_DisablePowerDomain(gClkRgmCtx.pHandle, pPwr->pwrHandle.domainId);
                        ADSPPM_LOG_PRINTF_1(ADSPPM_LOG_LEVEL_INFO, "Disabled power domain %s", pPwr->pPwrDescriptor->pwrDomainName);
                        ADSPPM_QDSS_EVENT_1(ADSPPM_PWR_REL, blk);
                    }
                    if(DAL_SUCCESS != dalResult)
                    {
                        ADSPPM_LOG_PRINTF_0(ADSPPM_LOG_LEVEL_ERROR, "ClkRegime returned failure");
                        result = Adsppm_Status_Failed;
                    }
                    break;
                default:
                    break;
                }

                //Unlock HW layer
                adsppm_unlock(gClkRgmCtx.ctxLock);
            }
            else
            {
                ADSPPM_LOG_PRINTF_0(ADSPPM_LOG_LEVEL_ERROR, "invalid HalClk_PwrDomainDescriptor");
                result = Adsppm_Status_BadParm;
            }
        }
        else
        {
            ADSPPM_LOG_PRINTF_0(ADSPPM_LOG_LEVEL_ERROR, "Not initialized");
            result = Adsppm_Status_NotInitialized;
        }
    }
    else
    {
        ADSPPM_LOG_PRINTF_0(ADSPPM_LOG_LEVEL_ERROR, "AsicPowerDomainId out of range");
        result = Adsppm_Status_BadParm;
    }

    ADSPPM_LOG_FUNC_PROFILEEND;
    ADSPPM_LOG_FUNC_EXIT(result);
    return result;
}


Adsppm_Status ClkRgm_MemoryControl(AdsppmMemIdType memCore, Hal_ClkRgmMemStateType pwrState)
{
    Adsppm_Status result = Adsppm_Status_Success;
    ADSPPM_LOG_FUNC_ENTER;
    ADSPPM_LOG_FUNC_PROFILESTART;
    if((Adsppm_Mem_None < memCore) && (Adsppm_Mem_Max > memCore))
    {
        if(NULL != gClkRgmCtx.ctxLock)
        {
            AsicPowerDomainType pwrDomain = ACMPwr_GetMemPowerDomain(memCore);
            adsppm_lock(gClkRgmCtx.ctxLock);
            //Call clock regime to enable/disable mem core retention
            result = clkrgm_MemCore_Retention(gClkRgmCtx.pwrDesc[pwrDomain].pPwrDescriptor->clkId, pwrState);
            adsppm_unlock(gClkRgmCtx.ctxLock);
        }
        else
        {
            ADSPPM_LOG_PRINTF_0(ADSPPM_LOG_LEVEL_ERROR, "Not initialized");
            result = Adsppm_Status_NotInitialized;
        }
    }
    else
    {
        ADSPPM_LOG_PRINTF_0(ADSPPM_LOG_LEVEL_ERROR, "AdsppmMemId out of range");
        result = Adsppm_Status_BadParm;
    }
    ADSPPM_LOG_FUNC_PROFILEEND;
    ADSPPM_LOG_FUNC_EXIT(result);
    return result;
}