/*
* Copyright (c) 2014 Qualcomm Technologies, Inc.
* All Rights Reserved.
* Qualcomm Technologies, Inc. Confidential and Proprietary.
*/

/*
 *  @file: asic_internal.h contains internal Asic Config Manager's definitions
 *
 *  Created on: Mar 23, 2012
 *  @author: yrusakov
 */

#ifndef ASIC_INTERNAL_H_
#define ASIC_INTERNAL_H_

#include "asic.h"


#define PERCENTS_IN_A_WHOLE  256
#define ASIC_CONFIG_DEVICE_NAME "/core/power/adsppm"

typedef struct{
    const int numElements;
    const AsicCoreDescType *pCores;
} AsicCoreDescriptorArrayType;

typedef struct{
    int numElements;
    AsicMemDescriptorFullType pMemories[Adsppm_Mem_Max];
} AsicMemDescriptorFullArrayType;

typedef struct{
    const int numElements;
    const AsicMemDescriptorType *pPwrDomainDesc;
} AsicMemDescriptorArrayType;

typedef struct{
    const int numElements;
    const AsicClkDescriptorType *pClocks;
} AsicClockDescriptorArrayType;

typedef struct{
    const int numElements;
    const AsicBusPortDescriptorType *pPorts;
} AsicBusPortDescriptorArrayType;

typedef struct{
    const int numElements;
    const AdsppmBusRouteType *pRoutes;
} AsicBusRouteArrayType;

typedef struct{
    const int numElements;
    const uint64 *pRegProgSpeeds;
} AsicRegProgSpeedArrayType;

typedef struct{
    const int numElements;
    const AsicPowerDomainDescriptorType *pPwrDomains;
} AsicPwrDescriptorArrayType;

/**
 * Enumeration to indicate function set used for this chip
 */
typedef enum{
    AsicFnSetId_Default = 0 //!< AsicFnID_Default
} AsicFnSetIdType;

typedef struct{
    AsicFnSetIdType functionSet;
    uint32  debugLevel;
    uint32  adspHwThreadNumber;
    uint64  adsppmLprTimeoutValue; //!<LPR timeout value in QTimer ticks (19.2Mhz)
    AsicCoreDescriptorArrayType *cores;
    AsicMemDescriptorFullArrayType memories;
    AsicClockDescriptorArrayType *clocks;
    AsicBusPortDescriptorArrayType *busPorts;
    AsicBusRouteArrayType *extBusRoutes;
    AsicBusRouteArrayType *mipsBusRoutes;
    AsicRegProgSpeedArrayType *regProgSpeeds;
    AsicPwrDescriptorArrayType *pwrDomains;
    Adsppm_Status (*pFn_GetBWFromMips)(AdsppmMIPSToBWAggregateType *pMipsAggregateData);
    Adsppm_Status (*pFn_GetClockFromMips)(AdsppmMIPSToClockAggregateType *pMipsAggregateData);
    Adsppm_Status (*pFn_GetClockFromBW)(uint32 *pClocks, AdsppmBusBWDataIbAbType *pAHBBwData);
    Adsppm_Status (*pFn_BusBWAggregate)(AdsppmBusBWDataIbAbType *pAggregateBwIbAbValue, AdsppmBusBWDataType *pBwValue);
    AsicFeatureDescType features[AsicFeatureId_enum_max]; //!< Feature enablement status
} AsicConfigType;

typedef struct{
    uint32 numClients;
    uint32 factor;
} AsicFactorType;

/**
 * @fn asicGetAsicConfig - fill in ASIC configuration from Device Config image
 * @param pConfig - [OUT] pointer to ASIC configuration structure
 * @return completion status
 */
Adsppm_Status asicGetAsicConfig(AsicConfigType *pConfig);


#endif /* ASIC_INTERNAL_H_ */

