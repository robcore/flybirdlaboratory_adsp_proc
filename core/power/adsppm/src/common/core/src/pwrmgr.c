/*
* Copyright (c) 2013 Qualcomm Technologies, Inc.
* All Rights Reserved.
* Qualcomm Technologies, Inc. Confidential and Proprietary.
*/

/*
 * pwrmgr.c
 *
 *  Created on: Feb 13, 2012
 *      Author: yrusakov
 */

#include "adsppm.h"
#include "ULog.h"
#include "ULogFront.h"
#include "asic.h"
#include "pwrmgr.h"
#include "DALSys.h"
#include "hal_clkrgm.h"
#include "requestmgr.h"
#include "adsppm_utils.h"


/**
 * Definition of the Power Manager Context.
 */
typedef struct{
    DALSYSSyncHandle            lock;
    Hal_ClkRgmEnableDisableType pwrDomainState[AsicPowerDomain_EnumMax][2];
    uint32                      activeStateIndex;
} powerMgrCtxType;

static powerMgrCtxType gPowerMgrCtx; //!< Global context for the power manager


Adsppm_Status PWR_Init(void)
{
    Adsppm_Status result = Adsppm_Status_Success;
    AsicPowerDomainType i = AsicPowerDomain_AON;
    ADSPPM_LOG_FUNC_ENTER;
    for(i = AsicPowerDomain_AON; i < AsicPowerDomain_EnumMax; i++)
    {
        gPowerMgrCtx.pwrDomainState[i][0] = Hal_ClkRgmDisable;
        gPowerMgrCtx.pwrDomainState[i][1] = Hal_ClkRgmDisable;
    }
    // If LPASS Core PC feature is enabled
    // set previous status as enabled
    // so that, regardless of LPASS Core POR state,
    // ADSPPM makes a call to disable it during init
    if((AsicFeatureState_Enabled == ACM_GetFeatureStatus(AsicFeatureId_LpassCore_PC)))
    {
        gPowerMgrCtx.pwrDomainState[AsicPowerDomain_LpassCore][1] = Hal_ClkRgmEnable;
    }
    gPowerMgrCtx.activeStateIndex = 0;
    if(DAL_SUCCESS != DALSYS_SyncCreate(DALSYS_SYNC_ATTR_RESOURCE, &gPowerMgrCtx.lock, NULL))
    {
        result = Adsppm_Status_Failed;
    }
    ADSPPM_LOG_FUNC_EXIT(result);
    return result;
}

Adsppm_Status PWR_ProcessRequest(coreUtils_Q_Type *pPwrReqQ)
{
    Adsppm_Status result = Adsppm_Status_Success;
    RMHandleType *pRMHandle = NULL;
    ADSPPM_LOG_FUNC_ENTER;

    if(NULL == pPwrReqQ)
    {
        result = Adsppm_Status_BadParm;
        ADSPPM_LOG_PRINTF_0(ADSPPM_LOG_LEVEL_ERROR, "Bad parameter");
    }
    else
    {
        if(NULL == gPowerMgrCtx.lock)
        {
            result = Adsppm_Status_NotInitialized;
            ADSPPM_LOG_PRINTF_0(ADSPPM_LOG_LEVEL_ERROR, "Not initialized");
        }
        else
        {
            int index = 0;
            AsicPowerDomainType pwrDomain = AsicPowerDomain_AON;
            adsppm_lock(gPowerMgrCtx.lock); //lock Pwr Manager's data
            ADSPPM_LOCK_RESOURCE(Adsppm_Rsc_Id_Power); //Lock Request manager's data
            //Clear current state
            for(pwrDomain = AsicPowerDomain_AON; pwrDomain < AsicPowerDomain_EnumMax; pwrDomain++)
            {
                gPowerMgrCtx.pwrDomainState[pwrDomain][gPowerMgrCtx.activeStateIndex] = Hal_ClkRgmDisable;
            }
            //Loop through all clients
            pRMHandle = (RMHandleType *)coreUtils_Q_Check(pPwrReqQ);
            for(index = 0; index < pPwrReqQ->nCnt; index++)
            {
                if(NULL != pRMHandle)
                {
                    if(NULL == pRMHandle->pAdsppmHandle)
                    {
                        result = Adsppm_Status_BadParm;
                        ADSPPM_LOG_PRINTF_0(ADSPPM_LOG_LEVEL_ERROR, "pAdsppmHandle is NULL");
                    }
                    else
                    {
                        //If request is valid that means that power has to be On
                        if(RM_Valid == pRMHandle->validFlag)
                        {
                            //get the power domain based on core ID for this client
                            pwrDomain = ACMPwr_GetPowerDomain(pRMHandle->pAdsppmHandle->coreId);
                            gPowerMgrCtx.pwrDomainState[pwrDomain][gPowerMgrCtx.activeStateIndex] = Hal_ClkRgmEnable;
                        }
                    }
                    pRMHandle = (RMHandleType *)coreUtils_Q_Next(pPwrReqQ, &(pRMHandle->rmHandleQLink));
                }
            }
            ADSPPM_UNLOCK_RESOURCE(Adsppm_Rsc_Id_Power); //unlock Request manager's data

            for(pwrDomain = AsicPowerDomain_AON; pwrDomain < AsicPowerDomain_EnumMax; pwrDomain++)
            {
                //Apply overrides if feature is disabled.
                switch(pwrDomain)
                {
                case AsicPowerDomain_Adsp:
                    if((AsicFeatureState_Enabled != ACM_GetFeatureStatus(AsicFeatureId_Adsp_PC)))
                    {
                        gPowerMgrCtx.pwrDomainState[pwrDomain][gPowerMgrCtx.activeStateIndex] = Hal_ClkRgmEnable;
                    }
                    break;
                case AsicPowerDomain_LpassCore:
                    if((AsicFeatureState_Enabled != ACM_GetFeatureStatus(AsicFeatureId_LpassCore_PC)))
                    {
                        gPowerMgrCtx.pwrDomainState[pwrDomain][gPowerMgrCtx.activeStateIndex] = Hal_ClkRgmEnable;
                    }
                    break;
                default:
                    break;
                }

                ADSPPM_LOG_PRINTF_2(ADSPPM_LOG_LEVEL_DEBUG, "Power domain %u state %u: ", pwrDomain, gPowerMgrCtx.pwrDomainState[pwrDomain][gPowerMgrCtx.activeStateIndex]);

                if(gPowerMgrCtx.pwrDomainState[pwrDomain][gPowerMgrCtx.activeStateIndex] !=
                        gPowerMgrCtx.pwrDomainState[pwrDomain][gPowerMgrCtx.activeStateIndex ^ 1])
                {
                    ADSPPM_LOG_PRINTF_2(ADSPPM_LOG_LEVEL_INFO, "Power domain %u requested state %u", pwrDomain, gPowerMgrCtx.pwrDomainState[pwrDomain][gPowerMgrCtx.activeStateIndex]);
                    //Only Call Clk regime wrapper to enable/disable power domains if the state changes
                    result = ClkRgm_RequestPower(pwrDomain, gPowerMgrCtx.pwrDomainState[pwrDomain][gPowerMgrCtx.activeStateIndex]);
                    if(Adsppm_Status_Success != result)
                    {
                        break;
                    }
                }
            }
            //Flip active/previous request
            gPowerMgrCtx.activeStateIndex ^= 1;
            adsppm_unlock(gPowerMgrCtx.lock); //Unlock request data as we'll work only on local PwrManager's data further
        }
    }

    ADSPPM_LOG_FUNC_EXIT(result);
    return result;
}
