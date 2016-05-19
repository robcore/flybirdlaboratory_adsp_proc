/*! \file
 *  
 *  \brief  dal_rpm_settings_registers.cpp ----This file contains target specific driver settings & PMIC registers.
 *  \details This file contains target specific 
 * driver settings & PMIC registers. This file is generated from database functional
 * configuration information that is maintained for each of the targets.
 *  
 *    PMIC code generation Version: 1.0.0.0
 *    PMIC code generation Resource Setting Information Version: VU.Please Provide Valid Label - Not Approved
 *    PMIC code generation Software Register Information Version: VU.Please Provide Valid Label - Not Approved
 *    PMIC code generation Processor Allocation Information Version: VU.Please Provide Valid Label - Not Approved
 *    This file contains code for Target specific settings and modes.
 *  
 *  &copy; Copyright 2012 Qualcomm Technologies Incorporated, All Rights Reserved
 */

/*===========================================================================

                        EDIT HISTORY FOR MODULE

  This document is created by a code generator, therefore this section will
  not contain comments describing changes made to the module.

$Header: //components/rel/core.adsp/2.6.1/systemdrivers/pmic/npa/inc/pm_lpass_dal.h#1 $ 

===========================================================================*/

/*===========================================================================

                     INCLUDE FILES 

===========================================================================*/
#include "rpm.h" // rpm_resource_type

typedef enum LUTInfoType
{
    VoltLevel, //LDO voltage levels
    VoltRange, // LDO voltage ranges
    MX, // MX config
    CX, // CX config
    NUM_OF_RSRC,//num of resources
    DEP, // power grid dependency 
    SAW, // is SAW controled
    PAM, // PAM
    REMOTE_RSRC_LDO, // Remote resources
    REMOTE_RSRC_VS, // Remote resources
    REMOTE_RSRC_SMPS, // Remote resources
    RSRC_PUB,
}LUTInfoType;

typedef struct PwrResourceInfoType
{
    rpm_resource_type ResourceType;
    unsigned          ResourceIndex; //internal resource index
    void*             data1; // data associated with this rail
    void*             data2; // data associated with this rail
    void*             data3; // data associated with this rail
}PwrResourceInfoType;

/*************************************
NOTE: VIRTUAL METHOD PROTOTYPES
**************************************/
void* pmiC_DalSettingsRegisters_GetModuleLUTInfo(LUTInfoType infoType, void* helper);

/*************************************
NOTE: Initializer IMPLEMENTATION
**************************************/
void pmiC_DalSettingsRegisters_Init(void);

