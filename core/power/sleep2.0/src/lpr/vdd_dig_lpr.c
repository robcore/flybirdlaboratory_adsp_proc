/*==============================================================================
  FILE:         vdd_dig_lpr.c

  OVERVIEW:     This file provides the LPR definition for the VDD_DIG clock 
                low-power modes.

  DEPENDENCIES: None

                Copyright (c) 2012-2013 QUALCOMM Technologies Incorporated.
                All Rights Reserved.
                Qualcomm Confidential and Proprietary
================================================================================
$Header: //components/rel/core.adsp/2.6.1/power/sleep2.0/src/lpr/vdd_dig_lpr.c#1 $
$DateTime: 2014/10/16 12:45:40 $
==============================================================================*/
#include "rpm.h"
#include "rpmclient.h"
#include "kvp.h"
#include "sleep_target.h"
#include "pm_version.h"

/*==============================================================================
                              INTERNAL VARIABLES
 =============================================================================*/
static kvp_t*             g_vddKVP;
static uint32             g_vddReq;
static rpm_resource_type  g_vddResType;
static uint32             g_vddResID;

/*==============================================================================
                              INTERNAL FUNCTIONS
 =============================================================================*/
/** 
 * VDDDigLPR_initialize
 * 
 * @brief Init function for vdd minimization low power mode.
 */
void VDDDigLPR_initialize( void )
{
  DalChipInfoFamilyType   cpuFam;
  DalChipInfoVersionType  cpuVer;
  uint8                   pmicModel;

  sleepTarget_getCPUArchitecture(&cpuFam, &cpuVer);

  if (cpuFam == DALCHIPINFO_FAMILY_MDM9x25)
  {
    g_vddResType = RPM_LDO_A_REQ;
    g_vddResID = 10;
  }
  else if ( cpuFam == DALCHIPINFO_FAMILY_MSM8x10 ||
            cpuFam == DALCHIPINFO_FAMILY_MSM8x26 ||
            cpuFam == DALCHIPINFO_FAMILY_MSM8926 ||
            cpuFam == DALCHIPINFO_FAMILY_MSM8994)
  {
    g_vddResType = RPM_SMPS_A_REQ;
    g_vddResID = 1;
  }
  else if ( cpuFam == DALCHIPINFO_FAMILY_MSM8974_PRO )
  {
    pmicModel = pm_get_pmic_model((uint8)0);

    if( PMIC_IS_PMA8084 == pmicModel )
    {
      g_vddResType = RPM_SMPS_A_REQ;
      g_vddResID = 2;
    }
    else
    {
      g_vddResType = RPM_SMPS_B_REQ;
      g_vddResID = 2;
    }
  }
  else if ( cpuFam == DALCHIPINFO_FAMILY_APQ8084 )
  {
    g_vddResType = RPM_SMPS_A_REQ;
    g_vddResID = 2;
  }
  else 
  {
    /* Default it to 8974 */
    g_vddResType = RPM_SMPS_B_REQ;
    g_vddResID = 2;
  }

  /* 1 resources * 3 fields (set,key,value) * 4 bytes per field */
  g_vddKVP = kvp_create(1*4*3);
  g_vddReq = 1;
  kvp_put(g_vddKVP, /* PM_NPA_KEY_CORNER_LEVEL_KEY */ 0x6E726F63,
          sizeof(g_vddReq), (void *)&g_vddReq);
  return;
}

/** 
 * VDDDigLPR_enter 
 *  
 * @brief Enter function for vdd minimization low power mode.
 */
void VDDDigLPR_enter( uint64 wakeup_tick )
{
  kvp_reset(g_vddKVP);

  rpm_post_request(RPM_SLEEP_SET, g_vddResType, g_vddResID, g_vddKVP);

  return;
}

/** 
 * VDDDigLPR_exit 
 *  
 * @brief Exit function for vdd minimization low power mode.
 */
void VDDDigLPR_exit( void )
{
  /* Cancelling vdd dig request in case we just do cxo shutdown next time */
  rpm_post_request(RPM_SLEEP_SET, g_vddResType, g_vddResID, NULL);  
  return;
}

