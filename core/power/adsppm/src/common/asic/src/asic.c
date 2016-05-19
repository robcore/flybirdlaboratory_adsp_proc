/*
* Copyright (c) 2014 Qualcomm Technologies, Inc.
* All Rights Reserved.
* Qualcomm Technologies, Inc. Confidential and Proprietary.
*/

/*
 * asic.c - File contains definitions of all generic ASIC Config Manager's functions
 *
 *
 *  Created on: Feb 13, 2012
 *      Author: yrusakov
 */

#include "adsppm.h"
#include "adsppm_utils.h"
#include "asic.h"
#include "asic_internal.h"
#include "ULogFront.h"
#include "DALSys.h"
#include "asic_8974.h"
#include "qurt_memory.h"


static AsicConfigType g_AsicConfig; //!< global structure holding ASIC configuration

#define ASIC_SCLK_FREQ_KHZ 32
#define ASIC_QCLK_FREQ_KHZ 19200

/**
 * this global variable is used for change debug level on
 * runtime to get adsppm ulog default ulog level is 3.
 * #define ADSPPM_LOG_LEVEL_PROFILE  0   profiling log message, set gDEBUGLEVEL = ADSPPM_LOG_LEVEL_MAX to get this debug level
 * #define ADSPPM_LOG_LEVEL_ERROR    1   Error log messages
 * #define ADSPPM_LOG_LEVEL_WARNING  2   Warnings
 * #define ADSPPM_LOG_LEVEL_INFO     3   Critical info messages
 * #define ADSPPM_LOG_LEVEL_INFO_EXT 4   Extended info messages
 * #define ADSPPM_LOG_LEVEL_FN_ENTRY 5   Function entry/exit messages
 * #define ADSPPM_LOG_LEVEL_DEBUG    6   All debug messages
 * #define ADSPPM_LOG_LEVEL_MAX      7
 */
static volatile uint32 gDEBUGLEVEL = 0;

/**
 * this global variable is used for enable/disable ADSPPM power feature before MMPM_Init
 *  gADSPPMPOWERFEATURE = 0xff  get feature definition from config file
 *  gADSPPMPOWERFEATURE = 0     disable all adsppm power feature
 *  gADSPPMPOWERFEATURE = 1     enable all adsppm power feature except some features not supported.
 *
 * @author alisonc (3/1/2013)
 */
static volatile uint32 gADSPPMPOWERFEATURE = 0xff;


Adsppm_Status asicInitConfigData(AsicConfigType *pConfig)
{
    Adsppm_Status result = Adsppm_Status_Success;

    //Get Chip configuration from Device Config image
    result = asicGetAsicConfig(pConfig);

    //Fill in ASIC specific functions
    //Only default functions are used at the moment
    switch(pConfig->functionSet)
    {
    case AsicFnSetId_Default:
        pConfig->pFn_GetBWFromMips = getBWFromMips_8974;
        pConfig->pFn_GetClockFromMips = getClockFromMips_8974;
        pConfig->pFn_GetClockFromBW = getClockFromBW_8974;
        pConfig->pFn_BusBWAggregate = aggregateBusBW_8974;
        break;
    default:
        ADSPPM_LOG_PRINTF_1(ADSPPM_LOG_LEVEL_ERROR, "ERROR: Unsupported function set ID %u", pConfig->functionSet);
        result = Adsppm_Status_Failed;
        break;
    }

    return result;
}


/**
 * @fn ACM_Init - initializes global ASIC configuration structure
 *
 * Function gets ASIC information (Family, ID, version) from ChipInfo.
 * The ASIC information is then used to populate the global configuration with
 * ASIC-specific data.
 *
 * @return completion status
 */
Adsppm_Status ACM_Init()
{
    Adsppm_Status result = Adsppm_Status_Success;
    ADSPPM_LOG_FUNC_ENTER;
    memset(&g_AsicConfig, 0, sizeof(g_AsicConfig));

    //Populate ASIC config with chip-specific data
    //All properties will be versioned in the device config XML,
    //so no need to know about chip family and revision
    result = asicInitConfigData(&g_AsicConfig);

    ADSPPM_LOG_FUNC_EXIT(result);
    return result;
}


AsicHwRscIdType ACM_GetHwRscId(AdsppmCoreIdType core, AdsppmRscIdType rsc)
{
    AsicHwRscIdType resType = AsicRsc_None;
    if((core > Adsppm_Core_Id_None) && (core < g_AsicConfig.cores->numElements) &&
            (rsc > Adsppm_Rsc_Id_None) && (rsc < Adsppm_Rsc_Id_Max))
    {
        resType = g_AsicConfig.cores->pCores[core].hwResourceId[rsc];
    }
    return resType;
}


/* TODO switch to using this instead of direct function calls
Asic_Rsc_AggregationFnType ACM_GetAggregationFn(AsicHwRscIdType, AdsppmCoreIdType)
{
    return NULL;
}*/


/**
 * Request number of supported routes (master/slave pairs) for external BW requests
 * @return number of supported routes (master/slave pairs) for external BW requests
 */
int ACMBus_GetNumberOfExtRoutes(void)
{
    return g_AsicConfig.extBusRoutes->numElements;
}


/**
 * Request supported routes (master/slave pairs) for external BW requests
 * @param pExtRoutes - [OUT] array to be filled with supported routes (master/slave pairs) for external BW requests
 */
void ACMBus_GetExtRoutes(AsicBusExtRouteType *pExtRoutes)
{
    int i = 0;
    const AsicBusPortDescriptorType *pMasterBusPortDescriptor = NULL;
    const AsicBusPortDescriptorType *pSlaveBusPortDescriptor = NULL;
    if(NULL != pExtRoutes)
    {
        for(i = 0; i < g_AsicConfig.extBusRoutes->numElements; i++)
        {
            pExtRoutes[i].masterPort.adsppmMaster = g_AsicConfig.extBusRoutes->pRoutes[i].masterPort;
            pMasterBusPortDescriptor = ACMBus_GetPortDescriptor(pExtRoutes[i].masterPort.adsppmMaster);
            pExtRoutes[i].slavePort.adsppmSlave = g_AsicConfig.extBusRoutes->pRoutes[i].slavePort;
            pSlaveBusPortDescriptor = ACMBus_GetPortDescriptor(pExtRoutes[i].slavePort.adsppmSlave);
            if((NULL != pMasterBusPortDescriptor) && (NULL != pSlaveBusPortDescriptor))
            {
                pExtRoutes[i].masterPort.icbarbMaster = pMasterBusPortDescriptor->icbarbId.icbarbMaster;
                pExtRoutes[i].slavePort.icbarbSlave = pSlaveBusPortDescriptor->icbarbId.icbarbSlave;
            }
        }
    }
}


/**
 * Get core clock ID for corresponding core instance
 * @param coreId
 * @param instanceId
 * @param coreClock
 * @return if core clock is associated to this core, return associated core instance core clock ID, else no change
 */
AdsppmClkIdType ACMClk_GetInstanceCoreClockId(AdsppmCoreIdType coreId, AdsppmInstanceIdType instanceId, AdsppmClkIdType coreClock)
{
    AdsppmClkIdType newClock = coreClock;
    if((Adsppm_Core_Id_None < coreId) && (Adsppm_Core_Id_Max > coreId) &&
            (Adsppm_Instance_Id_0 < instanceId) && (Adsppm_Instance_Id_Max > instanceId) &&
            (AdsppmClk_HwRsp_Core <= coreClock) && (AdsppmClk_EnumMax > coreClock))
    {
        if((g_AsicConfig.cores->pCores[coreId].coreClockInstances.numClocks > (instanceId - Adsppm_Instance_Id_0)) &&
                (g_AsicConfig.cores->pCores[coreId].coreClockInstances.pClocks[0] == coreClock))
        {
            newClock = g_AsicConfig.cores->pCores[coreId].coreClockInstances.pClocks[instanceId - Adsppm_Instance_Id_0];
        }
    }
    return newClock;
}


/**
 * Get master bus port ID for corresponding core instance
 * @param coreId
 * @param instanceId
 * @param masterBusPort
 * @return if master bus port is associated to this core, return associated core instance master bus port ID, else no change
 */
AdsppmBusPortIdType ACMBus_GetInstanceMasterBusPortId(AdsppmCoreIdType coreId, AdsppmInstanceIdType instanceId, AdsppmBusPortIdType masterBusPort)
{
    AdsppmBusPortIdType newMaster = masterBusPort;
    if((Adsppm_Core_Id_None < coreId) && (Adsppm_Core_Id_Max > coreId) &&
            (Adsppm_Instance_Id_0 < instanceId) && (Adsppm_Instance_Id_Max > instanceId) &&
            (AdsppmBusPort_None < masterBusPort) && (AdsppmBusPort_EnumMax > masterBusPort))
    {
        if((g_AsicConfig.cores->pCores[coreId].masterBusPortInstances.numBusPorts > (instanceId - Adsppm_Instance_Id_0)) &&
                (g_AsicConfig.cores->pCores[coreId].masterBusPortInstances.pBusPorts[0] == masterBusPort))
        {
            newMaster = g_AsicConfig.cores->pCores[coreId].masterBusPortInstances.pBusPorts[instanceId - Adsppm_Instance_Id_0];
        }
    }
    return newMaster;
}


/**
 * Get slave bus port ID for corresponding core instance
 * @param coreId
 * @param instanceId
 * @param slaveBusPort
 * @return if slave bus port is associated to this core, return associated core instance slave bus port ID, else no change
 */
AdsppmBusPortIdType ACMBus_GetInstanceSlaveBusPortId(AdsppmCoreIdType coreId, AdsppmInstanceIdType instanceId, AdsppmBusPortIdType slaveBusPort)
{
    AdsppmBusPortIdType newSlave = slaveBusPort;
    if((Adsppm_Core_Id_None < coreId) && (Adsppm_Core_Id_Max > coreId) &&
            (Adsppm_Instance_Id_0 < instanceId) && (Adsppm_Instance_Id_Max > instanceId) &&
            (AdsppmBusPort_None < slaveBusPort) && (AdsppmBusPort_EnumMax > slaveBusPort))
    {
        if((g_AsicConfig.cores->pCores[coreId].slaveBusPortInstances.numBusPorts > (instanceId - Adsppm_Instance_Id_0)) &&
                (g_AsicConfig.cores->pCores[coreId].slaveBusPortInstances.pBusPorts[0] == slaveBusPort))
        {
            newSlave = g_AsicConfig.cores->pCores[coreId].slaveBusPortInstances.pBusPorts[instanceId - Adsppm_Instance_Id_0];
        }
    }
    return newSlave;
}


/**
 * @fn ACMBus_GetCoreSlavePort - returns slave bus port associated with the core the client is registered for
 * @param coreId
 * @param instanceId
 * @return slave bus port ID associated with the registered core
 */
AdsppmBusPortIdType ACMBus_GetCoreSlavePort(AdsppmCoreIdType coreId, AdsppmInstanceIdType instanceId)
{
    AdsppmBusPortIdType port = AdsppmBusPort_None;
    if((Adsppm_Core_Id_None < coreId) && (Adsppm_Core_Id_Max > coreId) &&
            (Adsppm_Instance_Id_None < instanceId) && (Adsppm_Instance_Id_Max > instanceId))
    {
        if(g_AsicConfig.cores->pCores[coreId].slaveBusPortInstances.numBusPorts > (instanceId - Adsppm_Instance_Id_0))
        {
            port = g_AsicConfig.cores->pCores[coreId].slaveBusPortInstances.pBusPorts[instanceId - Adsppm_Instance_Id_0];
        }
    }
    return port;
}


/**
 * Get register programming speed
 * @param Register Programming Match
 * @return Speed in bytes per sec
 */
uint64 ACMBus_GetRegProgSpeed(AdsppmRegProgMatchType match)
{
    uint64 speed = 0;
    if((match > Adsppm_RegProg_None) && (match < Adsppm_RegProg_Enum_Max))
    {
        speed = g_AsicConfig.regProgSpeeds->pRegProgSpeeds[match];
    }
    return speed;
}


/**
 * Request number of supported routes (master/slave pairs) for MIPS BW requests
 * @return number of supported routes (master/slave pairs) for MIPS BW requests
 */
const int ACMBus_GetNumberOfMipsBwRoutes(void)
{
    return g_AsicConfig.mipsBusRoutes->numElements;
}


/**
 * Request list supported routes (master/slave pairs) for MIPS BW requests
 * @return pointer to array of supported routes (master/slave pairs) for MIPS BW requests
 */
const AdsppmBusRouteType *ACMBus_GetMipsBwRoutes(void)
{
    return g_AsicConfig.mipsBusRoutes->pRoutes;
}


/**
 * Returns pointer to the the descriptor for the specified bus port.
 * @param port
 * @return pointer to the bus port descriptor
 */
const AsicBusPortDescriptorType *ACMBus_GetPortDescriptor(AdsppmBusPortIdType port)
{
    const AsicBusPortDescriptorType *pDesc = NULL;
    if((port >= AdsppmBusPort_None) && (port < g_AsicConfig.busPorts->numElements))
    {
        pDesc = &(g_AsicConfig.busPorts->pPorts[port]);
    }
    return pDesc;
}


/**
 * Get type of the clock
 * @param Clock Id
 * @return Type of the clock (enable/disable, frequency set, npa)
 */
AsicClkTypeType ACMClk_GetClockType(AdsppmClkIdType clk)
{
    AsicClkTypeType clkType = AsicClk_TypeDalEnable;
    if ((clk >= AdsppmClk_None) && (clk < g_AsicConfig.clocks->numElements))
    {
        clkType = g_AsicConfig.clocks->pClocks[clk].clkType;
    }
    return clkType;
}


/**
 * Get descriptor the clock
 * @param Clock Id
 * @return Type of the clock (enable/disable, frequency set, npa)
 */
const AsicClkDescriptorType *ACMClk_GetClockDescriptor(AdsppmClkIdType clk)
{
    const AsicClkDescriptorType *pDesc = NULL;
    if((clk >= AdsppmClk_None) && (clk < g_AsicConfig.clocks->numElements))
    {
        pDesc = &(g_AsicConfig.clocks->pClocks[clk]);
    }
    return pDesc;
}


/**
 * Get info about the power domain
 * @param Domain Id
 * @return Power Domain Info
 */
const AsicPowerDomainDescriptorType *ACMClk_GetPwrDomainDescriptor(AsicPowerDomainType domain)
{
    const AsicPowerDomainDescriptorType *pDesc = NULL;
    if((domain >= AsicPowerDomain_AON) && (domain < g_AsicConfig.pwrDomains->numElements))
    {
        pDesc = &(g_AsicConfig.pwrDomains->pPwrDomains[domain]);
    }
    return pDesc;
}


/**
 * Get power domain for the specified core
 * @param Core ID
 * @return Power Domain
 */
AsicPowerDomainType ACMPwr_GetPowerDomain(AdsppmCoreIdType core)
{
    AsicPowerDomainType domain = AsicPowerDomain_AON;
    if((core > Adsppm_Core_Id_None) && (core < g_AsicConfig.cores->numElements))
    {
        domain = g_AsicConfig.cores->pCores[core].pwrDomain;
    }
    return domain;
}


/**
 * Get info about the memory
 * @param Memory Id
 * @return Memory Info
 */
AsicMemDescriptorFullType *ACM_GetMemoryDescriptor(AdsppmMemIdType mem)
{
    AsicMemDescriptorFullType *pDesc = NULL;
    if((mem >= Adsppm_Mem_None) && (mem < g_AsicConfig.memories.numElements))
    {
        pDesc = &(g_AsicConfig.memories.pMemories[mem]);
    }
    return pDesc;
}


/**
 * Get address range for the specified memory
 * @param Memory ID
 * @return address range
 */
AsicAddressRangeType *ACM_GetVirtMemAddressRange(AdsppmMemIdType mem)
{
    AsicAddressRangeType *addrRange = NULL;
    if((mem >= Adsppm_Mem_None) && (mem < g_AsicConfig.memories.numElements))
    {
        addrRange = &g_AsicConfig.memories.pMemories[mem].virtAddr;
    }
    return addrRange;
}


/**
 * Set address range for the specified memory
 * @param mem - Memory ID
 * @param addr - start address
 * @param size - address range size
 * @return operation status
 */
AdsppmStatusType ACM_SetVirtMemAddressRange(AdsppmMemIdType mem, uint64 addr, uint32 size)
{
    AdsppmStatusType result = Adsppm_Status_BadParm;
    if((mem >= Adsppm_Mem_None) && (mem < g_AsicConfig.memories.numElements))
    {
        g_AsicConfig.memories.pMemories[mem].virtAddr.startAddr = addr;
        g_AsicConfig.memories.pMemories[mem].virtAddr.size = size;
        result = Adsppm_Status_Success;
    }
    return result;
}


/**
 * Get power domain for the specified memory
 * @param Memory ID
 * @return Power Domain
 */
AsicPowerDomainType ACMPwr_GetMemPowerDomain(AdsppmMemIdType mem)
{
    AsicPowerDomainType domain = AsicPowerDomain_AON;
    if((mem > Adsppm_Mem_None) && (mem < g_AsicConfig.memories.numElements))
    {
        domain = g_AsicConfig.memories.pMemories[mem].pDescriptor->pwrDomain;
    }
    return domain;
}


/**
 * Get power resource type  for the specified memory
 * @param Memory ID
 * @return Power Domain
 */
AsicHwRscIdType ACMPwr_GetMemPowerType(AdsppmMemIdType mem)
{
    AsicHwRscIdType rsc = AsicRsc_None;
    if((mem > Adsppm_Mem_None) && (mem < g_AsicConfig.memories.numElements))
    {
        const AsicPowerDomainDescriptorType *pPwrDesc = ACMClk_GetPwrDomainDescriptor(g_AsicConfig.memories.pMemories[mem].pDescriptor->pwrDomain);
        if(NULL != pPwrDesc)
        {
            rsc = pPwrDesc->pwrDomainType;
        }
    }
    return rsc;
}


/**
 * Get descriptor for the specified core
 * @param Core ID
 * @return pointer to the descriptor for this core
 */
const AsicCoreDescType *ACM_GetCoreDescriptor(AdsppmCoreIdType core)
{
    const AsicCoreDescType *pDesc = NULL;
    if((core > Adsppm_Core_Id_None) && (core < g_AsicConfig.cores->numElements))
    {
        pDesc = &(g_AsicConfig.cores->pCores[core]);
    }
    return pDesc;
}


Adsppm_Status ACM_GetBWFromMips(AdsppmMIPSToBWAggregateType *pMipsAggregateData)
{
    Adsppm_Status result = Adsppm_Status_Failed;
    if(NULL != g_AsicConfig.pFn_GetBWFromMips)
    {
        result = g_AsicConfig.pFn_GetBWFromMips(pMipsAggregateData);
    }
    return result;
}


Adsppm_Status ACM_GetClockFromMips(AdsppmMIPSToClockAggregateType *pMipsAggregateData)
{
    Adsppm_Status result = Adsppm_Status_Failed;
    if(NULL != g_AsicConfig.pFn_GetClockFromMips)
    {
        result = g_AsicConfig.pFn_GetClockFromMips(pMipsAggregateData);
    }
    return result;
}


Adsppm_Status ACM_GetClockFromBW(uint32 *pClock, AdsppmBusBWDataIbAbType *pAHBBwData)
{
    Adsppm_Status result = Adsppm_Status_Failed;
    if(NULL != g_AsicConfig.pFn_GetClockFromBW)
    {
        result = g_AsicConfig.pFn_GetClockFromBW(pClock, pAHBBwData);
    }
    return result;
}


/**
 * @fn ACM_BusBWAggregate - Aggregate bw. So far the function is common for all chips
 * @param input: AdsppmBusBWDataType *pBwValue
 * @param output: AdsppmBusBWDataIbAbType *pAggregateBwIbAbValue
 * @return Adsppm_Status
 */
Adsppm_Status ACM_BusBWAggregate(AdsppmBusBWDataIbAbType *pAggregateBwIbAbValue, AdsppmBusBWDataType *pBwValue)
{
    Adsppm_Status result = Adsppm_Status_Failed;
    if(NULL != g_AsicConfig.pFn_BusBWAggregate)
    {
        result = g_AsicConfig.pFn_BusBWAggregate(pAggregateBwIbAbValue, pBwValue);
    }
    return result;
}


/**
 * Get feature enablement status for a particular feature
 */
AsicFeatureStateType ACM_GetFeatureStatus(AsicFeatureIdType featureId)
{
    return g_AsicConfig.features[featureId].state;
}


/**
 * Get feature descriptor for a particular feature
 */
AsicFeatureDescType *ACM_GetFeatureDescriptor(AsicFeatureIdType featureId)
{
    return &g_AsicConfig.features[featureId];
}


/**
 * Adjust parameter value based on feature enablement and configuration data
 * @param featureId - feature ID.
 * @param value - value, which needs to be adjusted
 * @return - adjusted value
 */
uint64 ACM_AdjustParamValue(AsicFeatureIdType featureId, uint64 value)
{
    AsicFeatureDescType *pDesc = ACM_GetFeatureDescriptor(featureId);
    uint64 result = value;

    switch(pDesc->state)
    {
    case AsicFeatureState_Enabled:
    case AsicFeatureState_Limited:
        //apply min/max limitation
        //Limit from the top
        result = MIN(value, pDesc->max);
        //Limit from bottom
        result = MAX(result, pDesc->min);
        break;
    case AsicFeatureState_Disabled:
        //use max for the parameter
        result = pDesc->max;
        break;
    default:
        break;
    }

    return result;
}


uint32 ACM_GetDebugLevel(void)
{
    return g_AsicConfig.debugLevel;
}


/**
 * Convert time in ms to sclk
 * @param ms - time in ms.
 * @return - number of sclks
 */
uint64 ACM_ms_to_sclk(uint64 ms)
{
    return ms * ASIC_SCLK_FREQ_KHZ;
}


/**
 * Convert time in us to qclk (QTimer clock ticks)
 * @param us - time in us.
 * @return - number of qclks
 */
uint64 ACM_us_to_qclk(uint64 us)
{
    return (us * ASIC_QCLK_FREQ_KHZ)/1000;
}


uint32 ACM_GetHwThreadNumber(void)
{
    return g_AsicConfig.adspHwThreadNumber;
}


/**
 * Get a timeout value in ms for MIPS/BW optimization LPR
 * @return timeout value in ms
 */
uint64 ACM_GetLprVoteTimeoutValue(void)
{
    return g_AsicConfig.adsppmLprTimeoutValue;
}


#define DAL_GET_PROPERTY_VALUE_WITH_CHECK(propertyString)                                                      \
{                                                                                                              \
    if(result == Adsppm_Status_Success)                                                                        \
    {                                                                                                          \
        if(DAL_SUCCESS != DALSYS_GetPropertyValue(adsppm_property, propertyString, 0, &system_property_var))   \
        {                                                                                                      \
            ADSPPM_LOG_PRINTF_0(ADSPPM_LOG_LEVEL_ERROR, "Unable to retrieve " propertyString " from config");  \
            result = Adsppm_Status_Failed;                                                                     \
        }                                                                                                      \
    }                                                                                                          \
}


#define DAL_GET_PROPERTY_VALUE_NO_CHECK(propertyString)                                                           \
{                                                                                                                 \
    dalresult = DALSYS_GetPropertyValue(adsppm_property, propertyString, 0, &system_property_var);                \
    if(DAL_SUCCESS != dalresult)                                                                                  \
    {                                                                                                             \
        ADSPPM_LOG_PRINTF_0(ADSPPM_LOG_LEVEL_ERROR, propertyString " is not specified in config, using default"); \
    }                                                                                                             \
}


#define CHECK_ARRAY_SIZE(a, b)                                                 \
{                                                                              \
    if(b != a)                                                                 \
    {                                                                          \
        ADSPPM_LOG_PRINTF_0(ADSPPM_LOG_LEVEL_ERROR, #a " is not of size " #b); \
        result = Adsppm_Status_Failed;                                         \
    }                                                                          \
}


Adsppm_Status asicGetAsicConfig(AsicConfigType *pConfig)
{
    Adsppm_Status result = Adsppm_Status_Success;
    DALSYSPropertyVar system_property_var;
    DALResult dalresult = DAL_SUCCESS;
    AsicFeatureStateType featureState = AsicFeatureState_Disabled;
    AsicFeatureIdType featureIndex = AsicFeatureId_Adsp_Clock_Scaling;
    int i = 0;

    /** Set default values **/
    pConfig->debugLevel = ADSPPM_LOG_LEVEL;
    pConfig->adspHwThreadNumber = ADSP_HW_THREAD_NUMBER_DEFAULT;
    pConfig->adsppmLprTimeoutValue = ADSPPM_LPR_VOTE_TIMEOUT_DEFAULT;
    pConfig->functionSet = AsicFnSetId_Default;

    /** declare property handle variable **/
    DALSYS_PROPERTY_HANDLE_DECLARE(adsppm_property);
    /** Get the property handle **/
    DALSYS_GetDALPropertyHandleStr(ASIC_CONFIG_DEVICE_NAME, adsppm_property);

    DAL_GET_PROPERTY_VALUE_NO_CHECK("FUNCTION_SET")
    if(dalresult == DAL_SUCCESS)
    {
        //No checking for NULL since we are passing pointer to a static variable.
        pConfig->functionSet = system_property_var.Val.dwVal;
    }

    if(!gDEBUGLEVEL)
    {
        DAL_GET_PROPERTY_VALUE_NO_CHECK("DEBUG_LEVEL")
        if(dalresult == DAL_SUCCESS)
        {
            //No checking for NULL since we are passing pointer to a static variable.
            pConfig->debugLevel = system_property_var.Val.dwVal;
        }
    }
    else
    {
        if(gDEBUGLEVEL < ADSPPM_LOG_LEVEL_MAX)
        {
            pConfig->debugLevel = gDEBUGLEVEL;
            ADSPPM_LOG_PRINTF_1(ADSPPM_LOG_LEVEL_ERROR, "DEBUG_LEVEL is set to %u", pConfig->debugLevel);
        }
        else if(ADSPPM_LOG_LEVEL_MAX == gDEBUGLEVEL)
        {
            pConfig->debugLevel = 0;
            ADSPPM_LOG_PRINTF_1(ADSPPM_LOG_LEVEL_ERROR, "DEBUG_LEVEL is set to %u, profiling", pConfig->debugLevel);
        }
        else
        {
            ADSPPM_LOG_PRINTF_1(ADSPPM_LOG_LEVEL_ERROR, "gDEBUGLEVEL setting is wrong = %u", gDEBUGLEVEL);
        }
    }

    DAL_GET_PROPERTY_VALUE_NO_CHECK("THREAD_NUMBER")
    if(dalresult == DAL_SUCCESS)
    {
        //No checking for NULL since we are passing pointer to a static variable.
        pConfig->adspHwThreadNumber = system_property_var.Val.dwVal;
    }

    DAL_GET_PROPERTY_VALUE_NO_CHECK("OVERHANG_VOTE_TIMEOUT_MS")
    if(dalresult == DAL_SUCCESS)
    {
        //No checking for NULL since we are passing pointer to a static variable.
        //Convert ms into QTImer ticks
        pConfig->adsppmLprTimeoutValue = ACM_us_to_qclk(system_property_var.Val.dwVal * 1000);
    }

    DAL_GET_PROPERTY_VALUE_WITH_CHECK("CORE_DESCRIPTORS")
    if(result == Adsppm_Status_Success)
    {
        pConfig->cores = (AsicCoreDescriptorArrayType *)system_property_var.Val.pStruct;
        CHECK_ARRAY_SIZE(pConfig->cores->numElements, Adsppm_Core_Id_Max)
        for(i = Adsppm_Core_Id_None; i < Adsppm_Core_Id_Max; i++)
        {
            AdsppmInstanceIdType numInstances = pConfig->cores->pCores[i].numInstances;
            if(!(((numInstances == pConfig->cores->pCores[i].coreClockInstances.numClocks) ||
                    (0 == pConfig->cores->pCores[i].coreClockInstances.numClocks)) &&
                    ((numInstances == pConfig->cores->pCores[i].masterBusPortInstances.numBusPorts) ||
                    (0 == pConfig->cores->pCores[i].masterBusPortInstances.numBusPorts)) &&
                    ((numInstances == pConfig->cores->pCores[i].slaveBusPortInstances.numBusPorts) ||
                    (0 == pConfig->cores->pCores[i].slaveBusPortInstances.numBusPorts))))
            {
                ADSPPM_LOG_PRINTF_1(ADSPPM_LOG_LEVEL_ERROR, "invalid array size of resource instances, coreId=%u", i);
                result = Adsppm_Status_Failed;
                break;
            }
        }
    }

    DAL_GET_PROPERTY_VALUE_WITH_CHECK("MEMORY_DESCRIPTORS")
    if(result == Adsppm_Status_Success)
    {
        AsicMemDescriptorArrayType *pMemories = (AsicMemDescriptorArrayType *)system_property_var.Val.pStruct;
        pConfig->memories.numElements = pMemories->numElements;
        CHECK_ARRAY_SIZE(pConfig->memories.numElements, Adsppm_Mem_Max)
        //get addresses for each memory
        for(i = Adsppm_Mem_None; i < Adsppm_Mem_Max; i++)
        {
            AsicMemDescriptorFullType *pMem = &pConfig->memories.pMemories[i];
            pMem->pDescriptor = &pMemories->pPwrDomainDesc[i];
            //Initialize address range with zeroes
            pMem->virtAddr.startAddr = 0;
            pMem->virtAddr.size = 0; //We will not flush cache for memories with size of 0
        }
    }

    DAL_GET_PROPERTY_VALUE_WITH_CHECK("CLOCK_DESCRIPTORS")
    if(result == Adsppm_Status_Success)
    {
        pConfig->clocks = (AsicClockDescriptorArrayType *)system_property_var.Val.pStruct;
        CHECK_ARRAY_SIZE(pConfig->clocks->numElements, AdsppmClk_EnumMax)
    }

    DAL_GET_PROPERTY_VALUE_WITH_CHECK("BUS_PORT_DESCRIPTORS")
    if(result == Adsppm_Status_Success)
    {
        pConfig->busPorts = (AsicBusPortDescriptorArrayType *)system_property_var.Val.pStruct;
        CHECK_ARRAY_SIZE(pConfig->busPorts->numElements, AdsppmBusPort_EnumMax)
    }

    DAL_GET_PROPERTY_VALUE_WITH_CHECK("EXTERNAL_BUS_ROUTES")
    if(result == Adsppm_Status_Success)
    {
        pConfig->extBusRoutes = (AsicBusRouteArrayType *)system_property_var.Val.pStruct;
    }

    DAL_GET_PROPERTY_VALUE_WITH_CHECK("MIPS_BUS_ROUTES")
    if(result == Adsppm_Status_Success)
    {
        pConfig->mipsBusRoutes = (AsicBusRouteArrayType *)system_property_var.Val.pStruct;
    }

    DAL_GET_PROPERTY_VALUE_WITH_CHECK("REGISTER_PROGRAMMING_SPEEDS")
    if(result == Adsppm_Status_Success)
    {
        pConfig->regProgSpeeds = (AsicRegProgSpeedArrayType *)system_property_var.Val.pStruct;
        CHECK_ARRAY_SIZE(pConfig->regProgSpeeds->numElements, Adsppm_RegProg_Enum_Max)
    }

    DAL_GET_PROPERTY_VALUE_WITH_CHECK("POWER_DOMAIN_DESCRIPTORS")
    if(result == Adsppm_Status_Success)
    {
        pConfig->pwrDomains = (AsicPwrDescriptorArrayType *)system_property_var.Val.pStruct;
        CHECK_ARRAY_SIZE(pConfig->pwrDomains->numElements, AsicPowerDomain_EnumMax)
    }

    if(result != Adsppm_Status_Failed)
    {
        if(0xff == gADSPPMPOWERFEATURE)
        {
            DAL_GET_PROPERTY_VALUE_WITH_CHECK("FEATURE_DESCRIPTORS")
            if(result == Adsppm_Status_Success)
            {
                memscpy(pConfig->features, AsicFeatureId_enum_max*sizeof(AsicFeatureDescType), system_property_var.Val.pStruct, AsicFeatureId_enum_max*sizeof(AsicFeatureDescType));
            }
        }
        else
        {
            if(0 == gADSPPMPOWERFEATURE)
            {
                featureState = AsicFeatureState_Disabled;
            }
            else if(1 == gADSPPMPOWERFEATURE)
            {
                featureState = AsicFeatureState_Enabled;
            }
            for(featureIndex = AsicFeatureId_Adsp_Clock_Scaling; featureIndex < AsicFeatureId_enum_max; featureIndex++)
            {
                pConfig->features[featureIndex].state = featureState;
            }
            /* some specal feature need to disable now*/
            pConfig->features[AsicFeatureId_Ahb_DCG].state = AsicFeatureState_Disabled;
            pConfig->features[AsicFeatureId_LpassCore_PC].state = AsicFeatureState_Disabled;
            pConfig->features[AsicFeatureId_LpassCore_PC_TZ_Handshake].state = AsicFeatureState_Disabled;  //TZ handshake only enabled in 8974 currently
        }
    }

    return result;
}


/**
 * check core exists in running chipset
 * @param Core ID
 * @return failure for not existing
 *         success for existing
 */
Adsppm_Status ACM_CheckCoreId(AdsppmCoreIdType core)
{
    Adsppm_Status result = Adsppm_Status_Failed;
    if((core > Adsppm_Core_Id_None) && (core < g_AsicConfig.cores->numElements))
    {
        if(Adsppm_Core_Id_None != g_AsicConfig.cores->pCores[core].coreId)
            result = Adsppm_Status_Success;
    }
    return result;
}


/**
 * check memory exists in running chipset
 * @param memory id
 * @return failure for not existing
 *         success for existing
 */
Adsppm_Status ACM_CheckMemoryId(AdsppmMemIdType mem)
{
    Adsppm_Status result = Adsppm_Status_Failed;
    if((mem > Adsppm_Mem_None) && (mem < g_AsicConfig.memories.numElements))
    {
        if(Adsppm_Mem_None != g_AsicConfig.memories.pMemories[mem].pDescriptor->memId)
            result = Adsppm_Status_Success;
    }
    return result;
}


/**
 * check clock exists in running chipset
 * @param clock id
 * @return failure for not existing
 *         success for existing
 */
Adsppm_Status ACM_CheckClockId(AdsppmClkIdType clock)
{
    Adsppm_Status result = Adsppm_Status_Failed;
    if((clock > AdsppmClk_None) && (clock < g_AsicConfig.clocks->numElements))
    {
        if((AsicClk_TypeNone != g_AsicConfig.clocks->pClocks[clock].clkType)
                && (AsicClk_CntlNone != g_AsicConfig.clocks->pClocks[clock].clkCntlType))
            result = Adsppm_Status_Success;
    }
    return result;
}


/**
 * check bus port exists in running chipset
 * @param busport id
 * @return failure for not existing
 *         success for existing
 */
Adsppm_Status ACM_CheckBusPort(AdsppmBusPortIdType busport)
{
    Adsppm_Status result = Adsppm_Status_Failed;
    if((busport > AdsppmBusPort_None) && (busport < g_AsicConfig.busPorts->numElements))
    {
        if(0 != g_AsicConfig.busPorts->pPorts[busport].portConnection)
            result = Adsppm_Status_Success;
    }
    return result;
}

