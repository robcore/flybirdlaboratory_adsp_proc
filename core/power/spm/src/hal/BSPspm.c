/*===========================================================================

FILE:         BSPspm.c

DESCRIPTION:  This file contains initializing/obtaining target specific SPM 
              data and related functions. Depending on the target, these 
              data can be obtained in different way like through device 
              config or by direct initialization.


              Copyright (c) 2010-2013 Qualcomm Technologies Incorporated.
              All Rights Reserved.
              Qualcomm Confidential and Proprietary

$Header: //components/rel/core.adsp/2.6.1/power/spm/src/hal/BSPspm.c#1 $

============================================================================*/


/* -----------------------------------------------------------------------
**                           INCLUDES
** ----------------------------------------------------------------------- */
#include "DalDevice.h"
#include "DALDeviceId.h"
#include "DALSys.h"
#include "DALSysTypes.h"
#include <DDIChipInfo.h>

#include "spm.h"
#include "BSPspm.h"
#include "CoreVerify.h"

/* -----------------------------------------------------------------------
**                           Function Declarations
** ----------------------------------------------------------------------- */
typedef struct {
  DalChipInfoFamilyType family; 
  DalChipInfoVersionType version;
} spm_chip_info ;

extern BSP_spm_ConfigDataType devcfgSpmBspData_8974v2[];
extern BSP_spm_CmdSequenceType devcfgSpmCmdSeqArray_8974v2[][SPM_NUM_LOW_POWER_MODES];
static spm_chip_info spm_get_chip_info(void);

/* -----------------------------------------------------------------------
**                           GLOBAL TARGET DATA
** ----------------------------------------------------------------------- */

/**
 * g_spmNumCores
 */
unsigned int g_spmNumCores USPM_DATA_SECTION = 0;

/**
 * g_spmBspData
 */
BSP_spm_ConfigDataType *g_spmBspData = NULL;

/**
 * g_spmCmdSeqArray
 */
BSP_spm_CmdSequenceType (*g_spmCmdSeqArray)[SPM_NUM_LOW_POWER_MODES] = NULL;
    

/* -----------------------------------------------------------------------
**                         Functions  
** ----------------------------------------------------------------------- */
static spm_chip_info spm_get_chip_info()
{
  static spm_chip_info chip = {DALCHIPINFO_FAMILY_UNKNOWN,0};

  if(chip.family == DALCHIPINFO_FAMILY_UNKNOWN)
  {
    chip.family = DalChipInfo_ChipFamily();
    CORE_VERIFY( chip.family != DALCHIPINFO_FAMILY_UNKNOWN );
    chip.version = DalChipInfo_ChipVersion();
    CORE_VERIFY(chip.version != NULL);
  }
  return chip;
}

/**
 * BSP_spm_InitTargetData
 */
void BSP_spm_InitTargetData( void )
{
  DALSYS_PROPERTY_HANDLE_DECLARE(hSpmDevCfg);
  DALSYSPropertyVar prop;
  spm_chip_info ci = spm_get_chip_info();

  if( (ci.family == DALCHIPINFO_FAMILY_MSM8974 &&
       ci.version >= DALCHIPINFO_VERSION(2,0)) || 
      (ci.family == DALCHIPINFO_FAMILY_MSM8974_PRO) )
  {
    g_spmNumCores = 1;
    g_spmBspData = devcfgSpmBspData_8974v2;
    g_spmCmdSeqArray = 
      (BSP_spm_CmdSequenceType (*)[SPM_NUM_LOW_POWER_MODES])
      devcfgSpmCmdSeqArray_8974v2;
  }
  else
  {
    CORE_DAL_VERIFY(DALSYS_GetDALPropertyHandleStr("/dev/core/power/spm", 
                                                   hSpmDevCfg));
  
    CORE_DAL_VERIFY(DALSYS_GetPropertyValue( hSpmDevCfg, "spm_num_cores", 0, 
                                             &prop));
    g_spmNumCores = (unsigned int)prop.Val.dwVal;
  
    CORE_DAL_VERIFY(DALSYS_GetPropertyValue( hSpmDevCfg, "spm_bsp_data", 0, 
                                             &prop)); 
    g_spmBspData = (BSP_spm_ConfigDataType *)prop.Val.pStruct;
  
    CORE_DAL_VERIFY(DALSYS_GetPropertyValue( hSpmDevCfg, "spm_cmd_seq_info_array",
                                             0, &prop));
    g_spmCmdSeqArray = 
      (BSP_spm_CmdSequenceType (*)[SPM_NUM_LOW_POWER_MODES])prop.Val.pStruct;
  }
  return;
}

/**
 * BSP_spm_GetNumSupportedLPMs
 */
uint32 BSP_spm_GetNumSupportedLPMs( uint32 coreNum )
{
  int i = 0;

  CORE_VERIFY( coreNum < g_spmNumCores );
  CORE_VERIFY_PTR( g_spmCmdSeqArray );

  while ( i < SPM_NUM_LOW_POWER_MODES ) 
  {
    if ( 0 == g_spmCmdSeqArray[coreNum][i].len )
    {
      break;
    }
    i++;
  }

  return i;
}
 
