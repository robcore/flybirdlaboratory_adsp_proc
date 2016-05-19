/*============================================================================
  FILE:         cxo_lpr.c

  OVERVIEW:     This file provides the LPR definition for the CXO clock 
                low-power modes.

  DEPENDENCIES: None

                Copyright (c) 2012-2014 Qualcomm Technologies, Inc. (QTI).
                All Rights Reserved.
                Qualcomm Technologies Confidential and Proprietary
================================================================================
$Header: //components/rel/core.adsp/2.6.1/power/sleep2.0/src/lpr/cxo_lpr.c#1 $
$DateTime: 2014/10/16 12:45:40 $
==============================================================================*/
#include "sleep_lpr.h"
#include "kvp.h"
#include "rpmclient.h"
#include "vmpm.h"
#include "sleep_target.h"
#include "DDIChipInfo.h"
#include "DDIPlatformInfo.h"
#include "CoreVerify.h"

/*==============================================================================
                              INTERNAL FUNCTIONS
 =============================================================================*/
/** 
 * CXOShutdownLPR_initializeTarget
 * 
 * @brief Performs target/platform specific initialization for a cxo
 *        shutdown lpr.
 *
 * @note This may no longer be necessary but keeping it just in case some 
 *       MDM target based on sleep2.0 requires it. We will have to add
 *       chip id in that case.
 */
static void CXOShutdownLPR_initializeTarget(void)
{
  DalChipInfoFamilyType   chipFamily;
  DalChipInfoVersionType  chipVersion;

  /* Querying the Chip ID */
  sleepTarget_getCPUArchitecture(&chipFamily, &chipVersion);

  if( DALCHIPINFO_FAMILY_MDM9x25 == chipFamily )
  {
    DalDeviceHandle                 *platformHandle = NULL;
    DalPlatformInfoPlatformInfoType platformType;

    /* Getting DAL platform handle */
    CORE_DAL_VERIFY(DAL_DeviceAttach(DALDEVICEID_PLATFORMINFO, &platformHandle));

    DalPlatformInfo_GetPlatformInfo(platformHandle, &platformType);

    if( DalPlatformInfo_IsFusion() && 
        !( DALPLATFORMINFO_TYPE_MTP_MDM == platformType.platform &&
           DALPLATFORMINFO_SUBTYPE_CSFB == platformType.subtype &&
           DALPLATFORMINFO_VERSION(1, 1) == platformType.version ) )
    {
      /* Specific set of fusion targets where we need to send GPIO voting 
       * during xo shutdown */

      /* Sleep set kvp for GPIO resource */
      kvp_t *gpioSleepKVP  = kvp_create(4 * 3 * 2); 
      /* Active set kvp for GPIO resource */
      kvp_t *gpioActiveKVP = kvp_create(4 * 3 * 2); 

      /* numb and stat(e) keys in little endian for gpio resource */
      const unsigned int gpioNumberKey  = 0x626d756e;  
      const unsigned int gpioStateKey   = 0x74617473;

      const int gpioNumber      = 18;   /* GPIO number to vote for */
      const int gpioActiveState = 1;    /* GPIO state: 1 - set */
      const int gpioSleepState  = 0;    /* GPIO state: 1 - clear */

      /* Preparing and sending one time active set vote for GPIO */
      kvp_put( gpioActiveKVP, gpioNumberKey, 
               sizeof(gpioNumber), (void *)&gpioNumber );
      kvp_put( gpioActiveKVP, gpioStateKey, 
               sizeof(gpioActiveState), (void *)&gpioActiveState );

      rpm_post_request(RPM_ACTIVE_SET, RPM_GPIO_TOGGLE_REQ, 0, gpioActiveKVP);

      /* Preparing and sending Sleep set vote for GPIO.
       * Since we are not clearing our vote while exiting from Sleep,
       * it is okay to send it only once. */
      kvp_put( gpioSleepKVP, gpioNumberKey,
               sizeof(gpioNumber), (void *)&gpioNumber );
      kvp_put( gpioSleepKVP, gpioStateKey,
               sizeof(gpioSleepState), (void *)&gpioSleepState );

      rpm_post_request( RPM_SLEEP_SET, RPM_GPIO_TOGGLE_REQ, 0, gpioSleepKVP );

      /* Relesing KVPs */
      kvp_destroy( gpioActiveKVP );
      kvp_destroy( gpioSleepKVP );
    }

    /* Releasing platform handle */
    (void)DAL_DeviceDetach( platformHandle );
  }

  return;
}

/*==============================================================================
                               GLOBAL FUNCTIONS
 =============================================================================*/
/** 
 * CXOShutdownLPR_initialize
 * 
 * @brief Performs required initialization for cxo lpr.
 */
void CXOShutdownLPR_initialize(void)
{
  /* Target specific initialization - if any */
  CXOShutdownLPR_initializeTarget();

  return;
}

/** 
 * CXOShutdownLPR_enter 
 *  
 * @brief Function that gets called when Master is voting for cxo shutdown 
 *        during a Sleep cycle.
 *
 * @param wakeup_tick: Absolute time tick (in 19.2 Mhz) when Master is 
 *                     expected to wake up.
 */
void CXOShutdownLPR_enter(uint64 wakeup_tick)
{
  return;
}

/** 
 * CXOShutdownLPR_exit 
 *  
 * @brief Exit function which gets called while exiting from Sleep on master 
 *        side for a Sleep cycle when master voted for cxo shutdown.
 */
void CXOShutdownLPR_exit( void )
{
  vmpm_TriggerInterrupts();

  return;
}

