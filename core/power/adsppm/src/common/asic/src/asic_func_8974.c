/*
* Copyright (c) 2014 Qualcomm Technologies, Inc.
* All Rights Reserved.
* Qualcomm Technologies, Inc. Confidential and Proprietary.
*/

/*
 * asic_func_8974.c - Contains 8974 specific functions for the Config Manager
 *
 *  Created on: Feb 13, 2012
 *      Author: yrusakov
 */

#include <limits.h>
#include "adsppm.h"
#include "adsppm_utils.h"
#include "asic.h"
#include "asic_internal.h"
#include "asic_8974.h"


#define DSP_BWUSAGE_FACTOR_8974  256
#define DMA_BWUSAGE_FACTOR_8974  256
#define EXTCPU_BWUSAGE_FACTOR_8974 256

#define INSTRUCTION_WIDTH_8974  32
#define BUS_WIDTH_8974  64
#define AHB_BUS_WIDTH_8974  32


/**
 * Array defining MIPS efficiency depending on number of clients
 * the factors are in PERCENTS_IN_A_WHOLE
 * elements should be sorted by number of clients
 */
const AsicFactorType adspMipsFactors_8974[] = {
    {1, 256},
    {2, 256},
    {8, 270}
};

/**
 * Apply scaling of input:
 * output = input * num / denom
 * UINT_MAX is returned if result would overflow 32-bit unsigned integer
 */
static inline uint32 scale32(uint32 input, uint32 num, uint32 denom)
{
    uint64 interm = (uint64)input * num / denom;
    return (interm > UINT_MAX) ? UINT_MAX : interm;
}

Adsppm_Status getBWFromMips_8974(AdsppmMIPSToBWAggregateType *pMipsAggregateData)
{
    Adsppm_Status result = Adsppm_Status_Success;

    if(NULL != pMipsAggregateData)
    {
        AdsppmBusBWRequestValueType *pBw = &pMipsAggregateData->mipsToBW;
        uint32 maxMips = MAX(pMipsAggregateData->mipsTotal, ACM_GetHwThreadNumber() * pMipsAggregateData->mipsPerThread);
        int i = 0;
        uint64 bwVal = 0;
        uint32 factor = 256;

        //find fudge factor
        for(i = 0; i < ADSPPM_ARRAY_SIZE(adspMipsFactors_8974); i++)
        {
            if(adspMipsFactors_8974[i].numClients > pMipsAggregateData->numOfClients)
            {
                break;
            }
            else
            {
                factor = adspMipsFactors_8974[i].factor;
            }
        }
        //Apply fudge factor
        maxMips = scale32(maxMips, factor, PERCENTS_IN_A_WHOLE);

        // Translate MIPS into IPS, then translate IPS into BW in bytes per
        // second
        bwVal = scale32(maxMips, 1000000 * INSTRUCTION_WIDTH_8974, 8);

        if((bwVal > 0) && IsPeriodicUseCase() && (pMipsAggregateData->numOfPeriodicClients > 0) &&
                (AsicFeatureState_Enabled == ACM_GetFeatureStatus(AsicFeatureId_TimelineOptimisationBw)))
        {
            //Only periodic clients are active
            //Select baseline or aggregated value if it is higher
            bwVal = ACM_AdjustParamValue(AsicFeatureId_TimelineOptimisationBw, bwVal);
        }

        pBw->bwValue.busBwAbIb.Ab = bwVal;
        pBw->bwValue.busBwAbIb.Ib = bwVal;

        // Apply minimum IB vote to keep bus clocks ON for DDR accesses
        // from lower level drivers (ADSP clock/sleep/icb/rpm/etc drivers)
        if((ACM_GetFeatureStatus(AsicFeatureId_Min_Adsp_BW_Vote) == AsicFeatureState_Enabled) &&
            (pBw->busRoute.slavePort == AdsppmBusPort_Ddr_Slave))
        {
            pBw->bwValue.busBwAbIb.Ib =
                ACM_AdjustParamValue(AsicFeatureId_Min_Adsp_BW_Vote, pBw->bwValue.busBwAbIb.Ib);
        }
    }
    else
    {
        ADSPPM_LOG_PRINTF_0(ADSPPM_LOG_LEVEL_ERROR, "pMipsAggregateData is NULL");
        result = Adsppm_Status_NullPointer;
    }

    return result;
}


Adsppm_Status getClockFromMips_8974(AdsppmMIPSToClockAggregateType *pMipsAggregateData)
{
    Adsppm_Status result = Adsppm_Status_Success;

    if(NULL != pMipsAggregateData)
    {
        uint32 maxMips = MAX(pMipsAggregateData->mipsTotal, ACM_GetHwThreadNumber() * pMipsAggregateData->mipsPerThread);
        int i = 0;
        uint32 factor = 256;

        //Check if only periodic clients are active
        if((AsicFeatureState_Enabled == ACM_GetFeatureStatus(AsicFeatureId_TimelineOptimisationMips)) && IsPeriodicUseCase())
        {
            //Only periodic clients are active
            //Select baseline or aggregated value if it is higher
            maxMips = ACM_AdjustParamValue(AsicFeatureId_TimelineOptimisationMips, maxMips);
        }

        //find fudge factor
        for(i = 0; i < ADSPPM_ARRAY_SIZE(adspMipsFactors_8974); i++)
        {
            if(adspMipsFactors_8974[i].numClients > pMipsAggregateData->numOfClients)
            {
                break;
            }
            else
            {
                factor = adspMipsFactors_8974[i].factor;
            }
        }

        //Apply fudge factor
        maxMips = scale32(maxMips, factor, PERCENTS_IN_A_WHOLE);
        //Adjust MIPS based on feature config
        maxMips = ACM_AdjustParamValue(AsicFeatureId_Adsp_Clock_Scaling, maxMips);
        //Translate MIPS into Hz
        pMipsAggregateData->qDSP6Clock = maxMips * 1000000;
    }
    else
    {
        ADSPPM_LOG_PRINTF_0(ADSPPM_LOG_LEVEL_ERROR, "pMipsAggregateData is NULL");
        result = Adsppm_Status_NullPointer;
    }

    return result;
}


Adsppm_Status getClockFromBW_8974(uint32 *pClock, AdsppmBusBWDataIbAbType *pAHBBwData)
{
    Adsppm_Status result = Adsppm_Status_Success;
    if((NULL != pClock) && (NULL != pAHBBwData))
    {
        uint64 maxBW = MAX(pAHBBwData->Ab, pAHBBwData->Ib);
        // Translate into bits per second, then into clock in Hz by
        // dividing by bus width
        *pClock = scale32(maxBW, 8, AHB_BUS_WIDTH_8974);
    }
    else
    {
        ADSPPM_LOG_PRINTF_0(ADSPPM_LOG_LEVEL_ERROR, "pAHBBwData is NULL");
        result = Adsppm_Status_NullPointer;
    }
    return result;
}


/**
 * @fn aggregateBusBW - aggregate bw. So far the function is common for all chips
 * @param input: AdsppmBusBWDataType *pBwValue. BW is specified in BW, Usage %
 * @param output: AdsppmBusBWDataIbAbType *pAggregateBwIbAbValue. BW output in Ab, Ib form
 * @return Adsppm_Status
 */
Adsppm_Status aggregateBusBW_8974(AdsppmBusBWDataIbAbType *pAggregateBwIbAbValue, AdsppmBusBWDataType *pBwValue)
{
    Adsppm_Status sts = Adsppm_Status_Success;
    uint32 BwUsageFactor = 0;
    uint64 bwValue =  0;
    AdsppmBusBWDataIbAbType bwValueAbIb;

    if((NULL == pAggregateBwIbAbValue) || (NULL == pBwValue))
    {
        ADSPPM_LOG_PRINTF_0(ADSPPM_LOG_LEVEL_ERROR, "pAggregateBwIbAbValue or pBwValue is NULL");
        sts = Adsppm_Status_BadParm;
    }
    else
    {
        bwValue = pBwValue->busBwValue.bwBytePerSec;
        switch(pBwValue->busBwValue.usageType)
        {
        case Adsppm_BwUsage_DSP:
            BwUsageFactor = DSP_BWUSAGE_FACTOR_8974;
            break;
        case Adsppm_BwUsage_DMA:
            BwUsageFactor = DMA_BWUSAGE_FACTOR_8974;
            break;
        case Adsppm_BwUsage_EXT_CPU:
            BwUsageFactor = EXTCPU_BWUSAGE_FACTOR_8974;
            break;
        default:
            ADSPPM_LOG_PRINTF_1(ADSPPM_LOG_LEVEL_ERROR, "Invalid usageType=%u", pBwValue->busBwValue.usageType);
            sts = Adsppm_Status_BadParm;
            break;
        }
        //apply bus usage factor to bw
        bwValue = scale32(bwValue, BwUsageFactor, PERCENTS_IN_A_WHOLE);
        //translate bw to ab and ib
        bwValueAbIb.Ab = scale32(bwValue, pBwValue->busBwValue.usagePercentage, 100);
        bwValueAbIb.Ib = bwValue;
        //aggregate bw
        pAggregateBwIbAbValue->Ab += bwValueAbIb.Ab;
        pAggregateBwIbAbValue->Ib = MAX(pAggregateBwIbAbValue->Ib, bwValueAbIb.Ib);
    }

    return sts;
}

