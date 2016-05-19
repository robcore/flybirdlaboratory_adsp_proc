/*
* Copyright (c) 2013-2015 Qualcomm Technologies, Inc.
* All Rights Reserved.
* Qualcomm Technologies, Inc. Confidential and Proprietary.
*/

/*
 * core.c
 *
 *  Created on: Feb 13, 2012
 *      Author: yrusakov
 */

#include "core.h"
#include "adsppm_utils.h"
#include "core_internal.h"
#include "clkmgr.h"
#include "mipsmgr.h"
#include "pwrmgr.h"
#include "latencymgr.h"
#include "thermalmgr.h"
#include "requestmgr.h"
#include "busmgr.h"
#include "ahbmgr.h"
#include "asyncmgr.h"
#include "mempwrmgr.h"
#include "usleepmgr.h"


static AdsppmCoreCtxType gAdsppmCoreCtx;

extern uint32 gADSPPMINITSTATE;


/**
 * @fn GetAdsppmCoreContext - retrieves pointer to the global ADSPPM context
 * @return pointer to the global ADSPPM context
 */
AdsppmCoreCtxType *GetAdsppmCoreContext(void)
{
    return &gAdsppmCoreCtx;
}


/**
 * @fn findAdsppmHandle - find the client context or handle in linklist
 */
int findAdsppmHandle(AdsppmHandleType *pAdsppmHandle, uint32 *clientId)
{
    int match = 0;
    if(pAdsppmHandle->clientId == *clientId)
    {
         match = 1;
    }
    return match;
}


uint32 IsPeriodicUseCase(void)
{
    return gAdsppmCoreCtx.periodicUseCase;
}


void SetPeriodicUseCase(uint32 periodic)
{
    gAdsppmCoreCtx.periodicUseCase = periodic;
}


/**
 * @fn Core_EnterSleep - Prepare LPASS resources for power collapse.
 * Currently it will just ramp down AHB clock.
 * TODO: Handle the clock gates as well
 * @return completion status
 */
Adsppm_Status Core_EnterSleep(void)
{
    Adsppm_Status result = Adsppm_Status_Success;
    ADSPPM_LOG_FUNC_ENTER;
    result = AHBM_SetSleepAHBClock();
    ADSPPM_LOG_FUNC_EXIT(result);
    return result;
}


/**
 * @fn Core_ExitSleep - Restore LPASS resources after power collapse.
 * Currently it will just ramp up AHB clock.
 * TODO: Handle the clock gates as well
 * @return completion status
 */
Adsppm_Status Core_ExitSleep(void)
{
    Adsppm_Status result = Adsppm_Status_Success;
    ADSPPM_LOG_FUNC_ENTER;
    result = AHBM_SetActiveAHBClock();
    ADSPPM_LOG_FUNC_EXIT(result);
    return result;
}


/**
 * @fn Core_Init - Initialize all components within ADSPPM Core
 * @return completion status @see Adsppm_Status
 */
Adsppm_Status Core_Init(void)
{
    Adsppm_Status result = Adsppm_Status_Success;
    ADSPPM_LOG_FUNC_ENTER;

    memset(&gAdsppmCoreCtx, 0, sizeof(AdsppmCoreCtxType));

    // Set periodic usecase by default to ensure quick powerdown
    gAdsppmCoreCtx.periodicUseCase = 1;

    if(DAL_SUCCESS != DALSYS_SyncCreate(DALSYS_SYNC_ATTR_RESOURCE, (DALSYSSyncHandle *)&gAdsppmCoreCtx.lock, NULL))
    {
        result = Adsppm_Status_Failed;
    }
    if(Adsppm_Status_Success == result)
    {
        gADSPPMINITSTATE |= Adsppm_State_CoreCtxLockInit;
        result = RM_Init();
        if(Adsppm_Status_Success == result)
        {
            gADSPPMINITSTATE |= Adsppm_State_CoreRMInit;
            result = AM_AsyncInit();
            if(Adsppm_Status_Success == result)
            {
                gADSPPMINITSTATE |= Adsppm_State_CoreAMAsyncInit;
                result = MIPS_Init();
                if(Adsppm_Status_Success == result)
                {
                    gADSPPMINITSTATE |= Adsppm_State_CoreMIPSInit;
                    result = BUS_Init();
                    if(Adsppm_Status_Success == result)
                    {
                        gADSPPMINITSTATE |= Adsppm_State_CoreBUSInit;
                        result = AHBM_Init();
                        if(Adsppm_Status_Success == result)
                        {
                            gADSPPMINITSTATE |= Adsppm_State_CoreAHBMInit;
                            result = PWR_Init();
                            if(Adsppm_Status_Success == result)
                            {
                                gADSPPMINITSTATE |= Adsppm_State_CorePWRInit;
                                result = CLK_Init();
                                if(Adsppm_Status_Success == result)
                                {
                                    gADSPPMINITSTATE |= Adsppm_State_CoreCLKInit;
                                    result = SLEEP_Init();
                                    if(Adsppm_Status_Success == result)
                                    {
                                        gADSPPMINITSTATE |= Adsppm_State_CoreSLEEPInit;
                                        result = THERMAL_Init();
                                        if(Adsppm_Status_Success == result)
                                        {
                                            gADSPPMINITSTATE |= Adsppm_State_CoreTHERMALInit;
                                            result = MEMPWR_Init();
                                            if(Adsppm_Status_Success == result)
                                            {
                                                gADSPPMINITSTATE |= Adsppm_State_CoreMEMPWRInit;
                                                result = USleepMgr_Init();
                                                if(Adsppm_Status_Success == result)
                                                {
                                                    gADSPPMINITSTATE |= Adsppm_State_CoreUSLEEPInit;
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    if((Adsppm_Status_Success == result) && (AsicFeatureState_Enabled == ACM_GetFeatureStatus(AsicFeatureId_InitialState)))
    {
        AdsppmRscIdType rsc;
        for(rsc = Adsppm_Rsc_Id_Power; rsc < Adsppm_Rsc_Id_Max; rsc++)
        {
            result = RM_RequestResource(rsc);
            if(Adsppm_Status_Success != result)
            {
                // Put failed resource ID in high 4 bits
                gADSPPMINITSTATE |= rsc << 28;
                break;
            }
        }
    }
    ADSPPM_LOG_FUNC_EXIT(result);
    return result;
}

