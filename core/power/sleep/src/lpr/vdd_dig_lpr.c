/*==============================================================================
  FILE:         vdd_dig_lpr.c

  OVERVIEW:     This file provides the LPR definition for the VDD_DIG clock 
                low-power modes.

  DEPENDENCIES: None

                Copyright (c) 2012-2013 QUALCOMM Technologies Incorporated.
                All Rights Reserved.
                Qualcomm Confidential and Proprietary
================================================================================
$Header: //components/rel/core.adsp/2.6.1/power/sleep/src/lpr/vdd_dig_lpr.c#1 $
$DateTime: 2014/10/16 12:45:40 $
==============================================================================*/
#include "rpm.h"
#include "rpmclient.h"
#include "kvp.h"
#include "sleep_target.h"
#include "pm_version.h"

static kvp_t* p_vdd_kvp;
static uint32 vdd_req;

static rpm_resource_type vdd_dig_res_type;
static uint32            vdd_dig_res_id;

void vdd_dig_init( void )
{
  DalChipInfoFamilyType   cpuFam;
  DalChipInfoVersionType  cpuVer;
  uint8 pm_model;

  sleep_target_get_CPU_arch(&cpuFam, &cpuVer);

  if (cpuFam == DALCHIPINFO_FAMILY_MDM9x25)
  {
    vdd_dig_res_type = RPM_LDO_A_REQ;
    vdd_dig_res_id = 10;
  }
  else if ( cpuFam == DALCHIPINFO_FAMILY_MSM8x10 ||
            cpuFam == DALCHIPINFO_FAMILY_MSM8x26 ||
            cpuFam == DALCHIPINFO_FAMILY_MSM8926)
  {
    vdd_dig_res_type = RPM_SMPS_A_REQ;
    vdd_dig_res_id = 1;
  }
  else if ( cpuFam == DALCHIPINFO_FAMILY_MSM8974_PRO )
  {
    pm_model = pm_get_pmic_model((uint8)0);
    if( PMIC_IS_PMA8084 == pm_model )
    {
      vdd_dig_res_type = RPM_SMPS_A_REQ;
      vdd_dig_res_id = 2;
    }
    else
    {
      vdd_dig_res_type = RPM_SMPS_B_REQ;
      vdd_dig_res_id = 2;
    }
  }
  else if ( cpuFam == DALCHIPINFO_FAMILY_APQ8084 )
  {
    vdd_dig_res_type = RPM_SMPS_A_REQ;
    vdd_dig_res_id = 2;
  }
  else if (cpuFam == DALCHIPINFO_FAMILY_MPQ8092)
  {
    vdd_dig_res_type = RPM_SMPS_A_REQ;
    vdd_dig_res_id = 8;
  }
  else 
  {
    /* Default it to 8974 */
    vdd_dig_res_type = RPM_SMPS_B_REQ;
    vdd_dig_res_id = 2;
  }

  /* 1 resources * 3 fields (set,key,value) * 4 bytes per field */
  p_vdd_kvp = kvp_create(1*4*3);
  vdd_req = 1;
  kvp_put(p_vdd_kvp, /* PM_NPA_KEY_CORNER_LEVEL_KEY */ 0x6E726F63,
          sizeof(vdd_req), (void *)&vdd_req);
  return;
}

void vdd_dig_min_enter( uint64 wakeup_tick )
{
  kvp_reset(p_vdd_kvp);

  rpm_post_request(RPM_SLEEP_SET, vdd_dig_res_type, vdd_dig_res_id, p_vdd_kvp);

  return;
}

void vdd_dig_min_exit( void )
{
  /* Cancelling vdd dig request in case we just do cxo shutdown next time */
  rpm_post_request(RPM_SLEEP_SET, vdd_dig_res_type, vdd_dig_res_id, NULL);  
}
