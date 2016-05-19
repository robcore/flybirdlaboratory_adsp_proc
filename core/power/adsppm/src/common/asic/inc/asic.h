/*
 * @file asic.h
 * @brief ASIC Config manager's header file
 * This file contains ASIC Config Manager specific declarations exposed to all
 * components within ADSPPM. The header will not be exposed outside of ADSPPM.
 *
 * Created on: Feb 13, 2012
 * Author: yrusakov
*/
/*==============================================================================

INITIALIZATION AND SEQUENCING REQUIREMENTS:  N/A

Imaginary Buffer Line

* Copyright (c) 2014 Qualcomm Technologies, Inc.
* All Rights Reserved.
* Qualcomm Technologies, Inc. Confidential and Proprietary.

==============================================================================

                           EDIT HISTORY FOR MODULE

$Header: //components/rel/core.adsp/2.6.1/power/adsppm/src/common/asic/inc/asic.h#1 $

This section contains comments describing changes made to the module.
Notice that changes are listed in reverse chronological order.

when       who          what, where, why
--------   ---          ---------------------------------------------------------
03/18/12   yrusakov          Initial version

==============================================================================*/

#ifndef ASIC_H_
#define ASIC_H_

#include "adsppm.h"
#include "icbarb.h"
#include "DDIIPCInt.h"
#include "qurt_memory.h"


/**
 * Default log level set for ADSPPM code
 * Note: overridden by device config value
 */
#define ADSPPM_LOG_LEVEL ADSPPM_LOG_LEVEL_DEBUG

/**
 * Number of HW threads
 * Note: overridden by device config value
 */
#define ADSP_HW_THREAD_NUMBER_DEFAULT 3

/**
 * Default delay for overhang requests in QTImer ticks.
 * Corresponds to 5ms
 */
#define ADSPPM_LPR_VOTE_TIMEOUT_DEFAULT 96000

#define NPA_SCHEDULER_NODE_NAME "/init/npa_scheduled_requests"


/******************************************************************************************/
/*               ASIC Config Mgr type definitions                                         */
/******************************************************************************************/
/**
 * @enum AsicHwRscIdType - defines HW resources, which will be controlled by resource managers.
 * The values can be combined in a bitmap
 */
typedef enum{
    AsicRsc_None = 0,                    //!< AsicRsc_None
    AsicRsc_Power_Mem = 1,               //!< Asic_Rsc_Power_Mem
    AsicRsc_Power_ADSP = 2,              //!< Asic_Rsc_Power_ADSP
    AsicRsc_Power_Core = 4,              //!< Asic_Rsc_Power_Core
    AsicRsc_MIPS_Clk =8,                 //!< Asic_Rsc_MIPS_Clk
    AsicRsc_MIPS_BW = 0x10,              //!< Asic_Rsc_MIPS_BW
    AsicRsc_BW_Internal = 0x20,          //!< Asic_Rsc_BW_Internal
    AsicRsc_BW_External = 0x40,          //!< Asic_Rsc_BW_External
    AsicRsc_Core_Clk = 0x80,             //!< Asic_Rsc_Core_Clk
    AsicRsc_Latency = 0x100,             //!< Asic_Rsc_Latency
    AsicRsc_Thermal = 0x200,             //!< Asic_Rsc_Thremal
    AsicRsc_Power_Ocmem = 0x400,         //!< Asic_Rsc_Power_Ocmem
    AsicRsc_EnumForce32bit = 0x7fffffff  //!< Forcing enum to be 32 bit
} AsicHwRscIdType;

/**
 * Type definition for Aggregation function pointer
 * @param pInputData - [IN] pointer to resource-specific list of the requests
 * @param pOutputData - [OUT] pointer to resource-specific value to return aggregation results
 */
typedef void (*Asic_Rsc_AggregationFnType)(void *pInputData, void *pOutputData);

/*************************************************************************************************/
/*                            Clock definitions                                                  */
/*************************************************************************************************/
/**
 * @enum AsicClkTypeType - defines how a particular clock is exposed by ClkRegime
 */
typedef enum{
    AsicClk_TypeNone = 0,
    AsicClk_TypeNpa,          //!< AsicClk_TypeNpa - Clock exposed as an NPA node
    AsicClk_TypeDalFreqSet,   //!< AsicClk_TypeDalFreqSet - Clock exposed through DALSys and allows to set frequency
    AsicClk_TypeDalEnable,    //!< AsicClk_TypeDalEnable - Clock exposed through DALSys and only allows to enable/disable it
    AsicClk_TypeDalDomainSrc
} AsicClkTypeType;

/**
 * @enum AsicClkCntlTypeType - defines how a particular clock is controlled
 */
typedef enum{
    AsicClk_CntlNone = 0,
    AsicClk_CntlOff,          //!< Clock should be OFF during init time
    AsicClk_CntlAlwaysON,     //!< Clock should be always on
    AsicClk_CntlAlwaysON_DCG, //!< Clock supports DCG but should be AON when DCG is disabled
    AsicClk_CntlSW,           //!< Clock is SW clock gated
    AsicClk_CntlSW_DCG        //!< Clock supports DCG and can be controlled by SW
} AsicClkCntlTypeType;

/**
 * @enum AsicClkMemRetentionType - defines how a memory core for particular clock is controlled
 */
typedef enum{
    AsicClk_MemCntlNone = 0,
    AsicClk_MemCntlAlwaysRetain, //!< Memory core for this clock should be always retained.
} AsicClkMemRetentionType;

/**
 * @struct AsicClkDesctiptorType - defines a descriptor for a particular clock.
 * The descriptor will be used by ClkRegime Wrapper to determine proper handling
 * of the requests for a particular clock.
 */
typedef struct{
    AdsppmClkIdType clkId;                  //!< Internal ADSPPM Clock Id
    AsicClkTypeType clkType;                //!< Type of the clock as exposed by ClkRegime
    AsicClkCntlTypeType clkCntlType;        //!< Type of clock control scheme
    AsicClkMemRetentionType clkMemCntlType; //!< How memory core is controlled
    char clkName[MAX_ADSPPM_CLIENT_NAME];   //!< Name of the clock as exposed by ClkRegime
    AdsppmClkIdType clkSrcId;               //!< Clock Id for frequency setting if the clock is enable/disable only
    AdsppmMemIdType memoryId;               //!< Memory ID if the clock is sourcing memory
} AsicClkDescriptorType;

/**
 * @struct AsicClockArrayType - defines a generic structure wchich members are a
 * pointer to an array of clock Ids and the number of clock IDs in it.
 */
typedef struct{
    const uint32 numClocks;
    const AdsppmClkIdType *pClocks;
} AsicClockArrayType;

/*************************************************************************************************/
/*                            Bus definitions                                                    */
/*************************************************************************************************/
typedef struct{
    AdsppmBusPortIdType adsppmMaster;
    ICBId_MasterType  icbarbMaster;
} AsicBusExtMasterType;

typedef struct{
    AdsppmBusPortIdType adsppmSlave;
    ICBId_SlaveType  icbarbSlave;
} AsicBusExtSlaveType;

typedef struct{
    AsicBusExtMasterType masterPort;
    AsicBusExtSlaveType slavePort;
} AsicBusExtRouteType;

/**
 * @enum AsicBusPortConnectionType - specifies which of the buses the port is
 * connected to. The enum is a bitmap and the values can be combined together
 * if an endpoint has more than one connection.
 */
typedef enum{
    AsicBusPort_None = 0,
    AsicBusPort_AhbE_M = 0x1,     //!< Master on AHB-E
    AsicBusPort_AhbE_S = 0x2,     //!< Slave on AHB-E
    AsicBusPort_AhbI_M = 0x4,     //!< Master on AHB-I
    AsicBusPort_AhbI_S = 0x8,     //!< Slave on AHB-I
    AsicBusPort_AhbX_M = 0x10,    //!< Master on AHB-X
    AsicBusPort_AhbX_S = 0x20,    //!< Slave on AHB-X
    AsicBusPort_Ahb_Any = 0x3F,   //!< Any connection on AHB
    AsicBusPort_Ext_M = 0x40,     //!< External Master
    AsicBusPort_Ext_S = 0x80,     //!< External Slave
    AsicBusPort_Ext_Any = 0xC0,   //!< Any external connection
    AsicBusPort_Any = 0xFF
} AsicBusPortConnectionType;

/**
 * @struct AsicBusPortDescriptorType - Bus port descriptor defining connections of the port and corresponding controls.
 */
typedef struct{
    AdsppmBusPortIdType port;
    AsicBusPortConnectionType portConnection; //!< Defines a bitmap of port connections to the buses
    AdsppmClkIdType busClk;                   //!< Bus clock for the port. Applicable only for AHB connected ports
    AsicClockArrayType regProgClocks;         //!< Ponter to array of clocks for register programming
    union {
        ICBId_MasterType icbarbMaster;        //!< ICBArb master definition for the port. Applicable only for external master connections
        ICBId_SlaveType  icbarbSlave;         //!< ICBArb slave definition for the port. Applicable only for external slave connections
    } icbarbId;                               //!< Descriptor for the port.  ICB definitions for external ports and for NOC port for internal ones
    AdsppmBusPortIdType accessPort;           //!< Access port. Port used to access from/to external NOC
} AsicBusPortDescriptorType;

/**
 * @struct AsicBusPortArrayType - defines a generic structure wchich members are a
 * pointer to an array of bus port Ids and the number of bus port IDs in it.
 */
typedef struct{
    const uint32 numBusPorts;
    const AdsppmBusPortIdType *pBusPorts;
} AsicBusPortArrayType;

/*************************************************************************************************/
/*                            Power definitions                                                  */
/*************************************************************************************************/
typedef enum{
    AsicPowerDomain_AON = 0,       //!< Always On
    AsicPowerDomain_Adsp = 1,      //!< ADSP (Q6SS) Power Island
    AsicPowerDomain_LpassCore = 2, //!< LPASS Core Power Island
    AsicPowerDomain_Lpm = 3,       //!< LPM memory core
    AsicPowerDomain_SRam = 4,      //!< Sensors RAM Memory core
    AsicPowerDomain_Ocmem = 5,     //!< OCMEM
    AsicPowerDomain_EnumMax
} AsicPowerDomainType;

typedef struct{
    AsicPowerDomainType pwrDomain;
    char pwrDomainName[MAX_ADSPPM_CLIENT_NAME];
    AsicHwRscIdType pwrDomainType;
    AdsppmClkIdType clkId;
    DalIPCIntInterruptType intrReinitTrigger;   //!< Interrupt Id to trigger re-initialization (TZ) after power up
    uint32 intrReinitDone;                      //!< Interrupt Id acknowledging re-init (TZ) completion after power up
    AsicClockArrayType securityClocks;          //!< Pointer to the array of security clocks for the domain
} AsicPowerDomainDescriptorType;

/*************************************************************************************************/
/*                            Core definitions                                                   */
/*************************************************************************************************/
/**
 * @struct AsicCoreDescType - Defines entry in the ASIC config table defining Core Descriptor
 */
typedef struct{
    AdsppmCoreIdType coreId;
    AsicHwRscIdType hwResourceId[Adsppm_Rsc_Id_Max]; //!< Array of HW Resource Ids by Resource Id
    AsicPowerDomainType pwrDomain;
    AsicClockArrayType coreClockInstances;
    AsicBusPortArrayType masterBusPortInstances;
    AsicBusPortArrayType slaveBusPortInstances;
    AdsppmInstanceIdType numInstances;
    //TODO: include aggregation function pointer here?
    //Asic_Rsc_AggregationFnType aggregateFn;
} AsicCoreDescType;

/*************************************************************************************************/
/*                            Memory type definitions                                            */
/*************************************************************************************************/
typedef struct{
    uint64 startAddr; //!< Start address
    uint32 size;      //!< memory range size
} AsicAddressRangeType;

/**
 * @struct AsicMemDescType - Defines entry in the ASIC config table defining Memory Descriptor
 */
typedef struct{
    AdsppmMemIdType memId;
    AsicPowerDomainType pwrDomain;
} AsicMemDescriptorType;

/**
 * @struct AsicMemDescFullType - Defines entry in the ASIC config table defining Memory Descriptor
 */
typedef struct{
    const AsicMemDescriptorType *pDescriptor; //!< pointer to memory descriptor
    AsicAddressRangeType virtAddr;            //!< virtual address range
} AsicMemDescriptorFullType;

/******************************************************************************************/
/*                            Feature definitions                                         */
/******************************************************************************************/
typedef enum{
    AsicFeatureId_Adsp_Clock_Scaling,
    AsicFeatureId_Adsp_LowTemp_Voltage_Restriction,
    AsicFeatureId_Adsp_PC,
    AsicFeatureId_Ahb_Scaling,
    AsicFeatureId_Ahb_Sw_CG,
    AsicFeatureId_Ahb_DCG,
    AsicFeatureId_LpassCore_PC,
    AsicFeatureId_LpassCore_PC_TZ_Handshake,
    AsicFeatureId_Bus_Scaling,
    AsicFeatureId_CoreClk_Scaling,           //!< Feature to control core clocks. If disabled the clocks will be forced to max
    AsicFeatureId_Min_Adsp_BW_Vote,          //!< Feature to issue min ext BW vote to support min MIPS
    AsicFeatureId_InitialState,              //!< Feature to set up initial state during init. If enabled ADSPPM will bring down all resources to the min state
    AsicFeatureId_TimelineOptimisationMips,  //!< Feature to enable MIPS vote optimization for periodic clients
    AsicFeatureId_TimelineOptimisationBw,    //!< Feature to enable BW vote optimization for periodic clients
    AsicFeatureId_TimelineOptimisationAhb,   //!< Feature to enable AHB clock optimization for periodic clients
    AsicFeatureId_LpassClkSleepOptimization, //!< Feature to enable gating of some of the LPASS clocks when Q6 is going into sleep
    AsicFeatureId_LPMRetention,              //!< Feature to control LPM retention
    AsicFeatureId_enum_max,
    AsicFeatureId_force_32bit = 0x7FFFFFFF
} AsicFeatureIdType;

typedef enum{
    AsicFeatureState_Disabled, //!< Feature completely disabled
    AsicFeatureState_Enabled,  //!< Feature enabled
    AsicFeatureState_Limited   //!< Feature behaviour limited
} AsicFeatureStateType;

typedef struct{
    AsicFeatureStateType state;
    uint64 min;
    uint64 max;
} AsicFeatureDescType;

/******************************************************************************************/
/*               Restricted functions definitions                                         */
/******************************************************************************************/
Adsppm_Status ACM_Init(void);

uint32 ACM_GetDebugLevel(void);

AsicHwRscIdType ACM_GetHwRscId(AdsppmCoreIdType, AdsppmRscIdType);

//Asic_Rsc_AggregationFnType ACM_GetAggregationFn(AsicHwRscIdType, AdsppmCoreIdType);

/**
 * @fn ACM_BusBWAggregate - Aggregate bw
 */
Adsppm_Status ACM_BusBWAggregate(AdsppmBusBWDataIbAbType *pAggregateBwIbAbValue, AdsppmBusBWDataType *pBwValue);

Adsppm_Status ACM_GetBWFromMips(AdsppmMIPSToBWAggregateType *pMipsAggregateData);

Adsppm_Status ACM_GetClockFromMips(AdsppmMIPSToClockAggregateType *pMipsAggregateData);

Adsppm_Status ACM_GetClockFromBW(uint32 *pClock, AdsppmBusBWDataIbAbType *pAHBBwData);

/**
 * Request number of supported routes (master/slave pairs) for external BW requests
 * @return number of supported routes (master/slave pairs) for external BW requests
 */
int ACMBus_GetNumberOfExtRoutes(void);

/**
 * Request supported routes (master/slave pairs) for external BW requests
 * @param pExtRoutes - [OUT] array to be filled with supported routes (master/slave pairs) for external BW requests
 */
void ACMBus_GetExtRoutes(AsicBusExtRouteType *pExtRoutes);

/**
 * Get core clock ID for corresponding core instance
 * @param coreId
 * @param instanceId
 * @param coreClock
 * @return if core clock is associated to this core, return associated core instance core clock ID
 *         else return core clock ID passed in coreClock
 */
AdsppmClkIdType ACMClk_GetInstanceCoreClockId(AdsppmCoreIdType coreId, AdsppmInstanceIdType instanceId, AdsppmClkIdType coreClock);

/**
 * Get master bus port ID for corresponding core instance
 * @param coreId
 * @param instanceId
 * @param masterBusPort
 * @return if master bus port is associated to this core, return associated core instance master bus port ID
 *         else return bus port ID passed in masterBusPort
 */
AdsppmBusPortIdType ACMBus_GetInstanceMasterBusPortId(AdsppmCoreIdType coreId, AdsppmInstanceIdType instanceId, AdsppmBusPortIdType masterBusPort);

/**
 * Get slave bus port ID for corresponding core instance
 * @param coreId
 * @param instanceId
 * @param slaveBusPort
 * @return if slave bus port is associated to this core, return associated core instance slave bus port ID
 *         else return bus port ID passed in slaveBusPort
 */
AdsppmBusPortIdType ACMBus_GetInstanceSlaveBusPortId(AdsppmCoreIdType coreId, AdsppmInstanceIdType instanceId, AdsppmBusPortIdType slaveBusPort);

/**
 * @fn ACMBus_GetCoreSlavePort - returns slave bus port associated with the core the client is registered for
 * @param coreId
 * @param instanceId
 * @return slave bus port ID associated with the registered core
 */
AdsppmBusPortIdType ACMBus_GetCoreSlavePort(AdsppmCoreIdType coreId, AdsppmInstanceIdType instanceId);

/**
 * Returns pointer to the the descriptor for the specified bus port.
 * @param port
 * @return pointer to the bus port descriptor
 */
const AsicBusPortDescriptorType *ACMBus_GetPortDescriptor(AdsppmBusPortIdType);

/**
 * Get type of the clock
 * @param Clock Id
 * @return Type of the clock (enable/disable, frequency set, npa)
 */
AsicClkTypeType ACMClk_GetClockType(AdsppmClkIdType);

/**
 * Get descriptor the clock
 * @param Clock Id
 * @return Type of the clock (enable/disable, frequency set, npa)
 */
const AsicClkDescriptorType *ACMClk_GetClockDescriptor(AdsppmClkIdType);

/**
 * Get info about the power domain
 * @param Domain Id
 * @return Power Domain Info
 */
const AsicPowerDomainDescriptorType *ACMClk_GetPwrDomainDescriptor(AsicPowerDomainType);

/**
 * Get power domain for the specified core
 * @param Core ID
 * @return Power Domain
 */
AsicPowerDomainType ACMPwr_GetPowerDomain(AdsppmCoreIdType);

/**
 * Get power domain for the specified memory
 * @param Memory ID
 * @return Power Domain
 */
AsicPowerDomainType ACMPwr_GetMemPowerDomain(AdsppmMemIdType mem);

/**
 * Get power resource type  for the specified memory
 * @param Memory ID
 * @return Power Domain
 */
AsicHwRscIdType ACMPwr_GetMemPowerType(AdsppmMemIdType mem);

/**
 * Get descriptor for the specified core
 * @param Core ID
 * @return pointer to the descriptor for this core
 */
const AsicCoreDescType *ACM_GetCoreDescriptor(AdsppmCoreIdType);

/**
 * Get Interrupt ID for the TZ secure interrupt
 */
uint32 ACM_GetTZSecureInterrupt(void);

/**
 * Get feature enablement status for a particular feature
 */
AsicFeatureStateType ACM_GetFeatureStatus(AsicFeatureIdType);

/**
 * Get feature descriptor for a particular feature
 */
AsicFeatureDescType *ACM_GetFeatureDescriptor(AsicFeatureIdType featureId);

/**
 * Adjust parameter value based on feature enablement and configuration data
 * @param featureId - feature ID.
 * @param value - value, which needs to be adjusted
 * @return - adjusted value
 */
uint64 ACM_AdjustParamValue(AsicFeatureIdType featureId, uint64 value);

/**
 * Convert time in ms to sclk
 * @param ms - time in ms.
 * @return - number of sclks
 */
uint64 ACM_ms_to_sclk(uint64 ms);

/**
 * Convert time in us to qclk (QTimer clock ticks)
 * @param us - time in us.
 * @return - number of qclks
 */
uint64 ACM_us_to_qclk(uint64 us);

/**
 * Request number of supported routes (master/slave pairs) for MIPS BW requests
 * @return number of supported routes (master/slave pairs) for MIPS BW requests
 */
const int ACMBus_GetNumberOfMipsBwRoutes(void);

/**
 * Request list supported routes (master/slave pairs) for MIPS BW requests
 * @return pointer to array of supported routes (master/slave pairs) for MIPS BW requests
 */
const AdsppmBusRouteType *ACMBus_GetMipsBwRoutes(void);

/**
 * Get number of HW threads for the ASIC's ADSP
 * @return number of threads
 */
uint32 ACM_GetHwThreadNumber(void);

/**
 * Get a timeout value in ms for MIPS/BW optimization LPR
 * @return timeout value in ms
 */
uint64 ACM_GetLprVoteTimeoutValue(void);

/**
 * Get info about the power domain
 * @param Memory Id
 * @return Memory Info
 */
AsicMemDescriptorFullType *ACM_GetMemoryDescriptor(AdsppmMemIdType mem);

/**
 * Get address range for the specified memory
 * @param Memory ID
 * @return address range
 */
AsicAddressRangeType *ACM_GetVirtMemAddressRange(AdsppmMemIdType mem);

/**
 * Set address range for the specified memory
 * @param mem - Memory ID
 * @param addr - start address
 * @param size - address range size
 * @return operation status
 */
AdsppmStatusType ACM_SetVirtMemAddressRange(AdsppmMemIdType mem, uint64 addr, uint32 size);

/**
 * check core id is existing in special chipset
 * @param Core ID
 * @return failure for not existing
 *         success for existing
 */
Adsppm_Status ACM_CheckCoreId(AdsppmCoreIdType core);

/**
 * check memory is existing in special chipset
 * @param memory id
 * @return failure for not existing
 *         success for existing
 */
Adsppm_Status ACM_CheckMemoryId(AdsppmMemIdType mem);

/**
 * check clockid is existing in special chipset
 * @param clock id
 * @return failure for not existing
 *         success for existing
 */
Adsppm_Status ACM_CheckClockId(AdsppmClkIdType clock);

/**
 * check busport is existing in special chipset
 * @param busport id
 * @return failure for not existing
 *         success for existing
 */
Adsppm_Status ACM_CheckBusPort(AdsppmBusPortIdType busport);


#endif /* ASIC_H_ */

