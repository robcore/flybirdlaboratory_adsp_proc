/*
* Copyright (c) 2013 Qualcomm Technologies, Inc.
* All Rights Reserved.
* Qualcomm Technologies, Inc. Confidential and Proprietary.
*/

/*
 * ahbmgr.c
 *
 *  Created on: Feb 10, 2012
 *      Author: yrusakov
 */

#include "adsppm.h"
#include "ULog.h"
#include "ULogFront.h"
#include "adsppm_utils.h"
#include "asic.h"
#include "ahbmgr.h"
#include "core_internal.h"
#include "hal_clkrgm.h"


/**
 * @struct ahb management context
 */
typedef struct{
   uint32           preAHBClock; //!< Clock currently set
   uint32           activeAHBClock; //!< Clock calculated based on aggregated clock accounting for execution state (periodic vs non-periodic)
   uint32           aggregatedAHBClock; //!< Clock calculated based on BW requirements only for all clients
   uint32           nonSuppressibleAHBClock; //!< Clock calculated based on BW requirements only for non-suppressible clients
   DALSYSSyncHandle lock;
} ahbMgrCtxType;

static ahbMgrCtxType gAhbMgrCtx;


/**
 * @fn AHBM_Init - init AHB management related data structure and mutex
 * @return Adsppm_Status_Failed
 * @return Adsppm_Status_Success
 */
Adsppm_Status AHBM_Init(void)
{
    Adsppm_Status sts = Adsppm_Status_Success;
    ADSPPM_LOG_FUNC_ENTER;

    gAhbMgrCtx.preAHBClock = gAhbMgrCtx.activeAHBClock = gAhbMgrCtx.aggregatedAHBClock = gAhbMgrCtx.nonSuppressibleAHBClock = 0;
    gAhbMgrCtx.lock = NULL;

    if(DAL_SUCCESS != DALSYS_SyncCreate(DALSYS_SYNC_ATTR_RESOURCE, (DALSYSSyncHandle *)&gAhbMgrCtx.lock, NULL))
    {
        ADSPPM_LOG_PRINTF_0(ADSPPM_LOG_LEVEL_ERROR, "Failed to create lock");
        sts = Adsppm_Status_Failed;
    }

    ADSPPM_LOG_FUNC_EXIT(sts);
    return sts;
}

Adsppm_Status ahbm_SetAHBClock(uint32 ahbClock)
{
    Adsppm_Status sts = Adsppm_Status_Success;
    ADSPPM_LOG_PRINTF_1(ADSPPM_LOG_LEVEL_INFO_EXT, "AHB clock: %u", ahbClock);
    if(gAhbMgrCtx.preAHBClock != ahbClock)
    {
        sts = ClkRgm_SetClock(AdsppmClk_Ahb_Root, ahbClock);
        if(Adsppm_Status_Success == sts)
        {
            gAhbMgrCtx.preAHBClock = ahbClock;
        }
    }
    return sts;
}

Adsppm_Status AHBM_SetSleepAHBClock(void)
{
    //WORKAROUND: for HW issue QCTDD00667975
    //Slimbus requires AHB bus freq to be at least 7.4 MHz even in sleep
    //The following logic uses adsppm internal counters to check whether slimbus core clocks are ON
    //If they are found to be ON, choose the max between 7.4 MHz and current aggregated ahb freq
    //Otherwise, use current aggregated ahb freq

    uint32 slimbusCore1ClockFreq = 0;
    uint32 slimbusCore2ClockFreq = 0;
    uint32 sleepAhbClockFreq = gAhbMgrCtx.nonSuppressibleAHBClock;

    //Note: Targets with no Slimbus HW will return Freq = 0 on ClkRgm_GetClockFrequency() call
    ClkRgm_GetClockFrequency(AdsppmClk_Slimbus_Core, &slimbusCore1ClockFreq);
    ClkRgm_GetClockFrequency(AdsppmClk_Slimbus2_Core, &slimbusCore2ClockFreq);
    sleepAhbClockFreq = ((0 < slimbusCore1ClockFreq) || (0 < slimbusCore2ClockFreq))?MAX(gAhbMgrCtx.nonSuppressibleAHBClock, 7400000):gAhbMgrCtx.nonSuppressibleAHBClock;

    return ahbm_SetAHBClock(sleepAhbClockFreq);
}

Adsppm_Status AHBM_SetActiveAHBClock(void)
{
    return ahbm_SetAHBClock(gAhbMgrCtx.activeAHBClock);
}

Adsppm_Status AHBM_AdjustAndSetAHBClock(void)
{
    Adsppm_Status sts = Adsppm_Status_Success;
    adsppm_lock(gAhbMgrCtx.lock);

    //Adjust AHB clock if ADSP is active
    //The timeline optimization by keeping AHB clock not lower than predefined frequency (19.2MHz) is applied
    //also to non-periodic clients in order to compensate for inadequate BW voting from audio clients.
    //Periodic usecases may have different (higher) AHB clock requirements to optimize their timeline
    if((AsicFeatureState_Enabled == ACM_GetFeatureStatus(AsicFeatureId_TimelineOptimisationAhb)) && IsPeriodicUseCase())
    {
        //Select baseline or aggregated value if it is higher
        gAhbMgrCtx.activeAHBClock = ACM_AdjustParamValue(AsicFeatureId_TimelineOptimisationAhb, gAhbMgrCtx.aggregatedAHBClock);
    }
    else
    {
        gAhbMgrCtx.activeAHBClock = gAhbMgrCtx.aggregatedAHBClock;
    }

    sts = AHBM_SetActiveAHBClock();
    adsppm_unlock(gAhbMgrCtx.lock);
    return sts;
}

/**
 * @fn AHBM_ProcessRequest - Convert AHB bandwidth  to AHB clock
 * @param input AdsppmBusBWDataIbAbType *pCurAHBBwData
 * @param input AdsppmBusBWDataIbAbType *pNonSuppressibleAhbBW
 * @return Adsppm_Status
 */
Adsppm_Status AHBM_ProcessRequest(AdsppmBusBWDataIbAbType *pCurAHBBwData, AdsppmBusBWDataIbAbType *pNonSuppressibleAhbBW)
{
    Adsppm_Status sts = Adsppm_Status_Success;
    ADSPPM_LOG_FUNC_ENTER;

    if((NULL == pCurAHBBwData) || (NULL == pNonSuppressibleAhbBW))
    {
        ADSPPM_LOG_PRINTF_2(ADSPPM_LOG_LEVEL_ERROR, "pCurAHBBwData=%u, pNonSuppressibleAhbBW=%u", pCurAHBBwData, pNonSuppressibleAhbBW);
        sts = Adsppm_Status_BadParm;
    }
    else
    {
        if(NULL == gAhbMgrCtx.lock)
        {
            ADSPPM_LOG_PRINTF_0(ADSPPM_LOG_LEVEL_ERROR, "Not initialized");
            sts = Adsppm_Status_NotInitialized;
        }
        else
        {
            adsppm_lock(gAhbMgrCtx.lock);
            ADSPPM_LOG_PRINTF_2(ADSPPM_LOG_LEVEL_INFO_EXT, "Aggregated BW: Ab=%u, Ib=%u", (uint32)(pCurAHBBwData->Ab), (uint32)(pCurAHBBwData->Ib));
            ADSPPM_LOG_PRINTF_2(ADSPPM_LOG_LEVEL_INFO_EXT, "Aggregated non-suppressible BW: Ab=%u, Ib=%u", (uint32)(pNonSuppressibleAhbBW->Ab), (uint32)(pNonSuppressibleAhbBW->Ib));

            sts = ACM_GetClockFromBW(&gAhbMgrCtx.nonSuppressibleAHBClock, pNonSuppressibleAhbBW);
            if(Adsppm_Status_Success == sts)
            {
                //Adjust BW based on feature config
                pCurAHBBwData->Ib = ACM_AdjustParamValue(AsicFeatureId_Ahb_Scaling, pCurAHBBwData->Ib);
                sts = ACM_GetClockFromBW(&gAhbMgrCtx.aggregatedAHBClock, pCurAHBBwData);
            }
            adsppm_unlock(gAhbMgrCtx.lock);

            if(Adsppm_Status_Success == sts)
            {
                sts = AHBM_AdjustAndSetAHBClock();
            }
        }
    }

    ADSPPM_LOG_FUNC_EXIT(sts);
    return sts;
}
