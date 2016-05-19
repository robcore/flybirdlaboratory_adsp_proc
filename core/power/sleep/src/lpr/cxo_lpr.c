/*============================================================================
  FILE:         cxo_lpr.c

  OVERVIEW:     This file provides the LPR definition for the CXO clock 
                low-power modes.

  DEPENDENCIES: None

                Copyright (c) 2012-2013 QUALCOMM Technologies Incorporated.
                All Rights Reserved.
                Qualcomm Confidential and Proprietary
================================================================================
$Header: //components/rel/core.adsp/2.6.1/power/sleep/src/lpr/cxo_lpr.c#1 $
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

/*===========================================================================
 *                        INTERNAL FUNCTIONS
 *==========================================================================*/

/**
 * @brief cxo_shutdown_target_init
 *
 * Performs target/platform specific initialization for a cxo shutdown lpr.
 */
static void cxo_shutdown_target_init(void)
{
  DalChipInfoFamilyType chip_family;
  DalChipInfoVersionType chip_version;

  /* Querying the Chip ID */
  sleep_target_get_CPU_arch(&chip_family, &chip_version);

  if( DALCHIPINFO_FAMILY_MDM9x25 == chip_family )
  {
    DalDeviceHandle *platform_handle = NULL;
    DalPlatformInfoPlatformInfoType platform_type;

    /* Getting DAL platform handle */
    CORE_DAL_VERIFY(
      DAL_DeviceAttach( DALDEVICEID_PLATFORMINFO, &platform_handle )
    );

    DalPlatformInfo_GetPlatformInfo( platform_handle, &platform_type );

    if( DalPlatformInfo_IsFusion() && 
        !( DALPLATFORMINFO_TYPE_MTP_MDM == platform_type.platform &&
           DALPLATFORMINFO_SUBTYPE_CSFB == platform_type.subtype &&
           DALPLATFORMINFO_VERSION(1, 1) == platform_type.version ) )
    {
      /* Specific set of fusion targets where we need to send GPIO voting 
       * during xo shutdown */
      kvp_t *gpio_sleep_kvp = NULL;    /* Sleep set kvp for GPIO resource */
      kvp_t *gpio_active_kvp = NULL;   /* Active set kvp for GPIO resource */

      /* numb and stat(e) keys in little endian for gpio resource */
      const unsigned int gpio_numb_key = 0x626d756e;  
      const unsigned int gpio_state_key = 0x74617473;

      const int gpio_numb = 18;                   /* GPIO number to vote for */
      const int gpio_active_state = 1;            /* GPIO state: 1 - set */
      const int gpio_sleep_state = 0;             /* GPIO state: 1 - clear */

      /* Preparing and sending one time active set vote for GPIO */
      gpio_active_kvp = kvp_create(4 * 3 * 2);
      kvp_put( gpio_active_kvp, gpio_numb_key, 
               sizeof(gpio_numb), (void *)&gpio_numb );
      kvp_put( gpio_active_kvp, gpio_state_key, 
               sizeof(gpio_active_state), (void *)&gpio_active_state );

      rpm_post_request(RPM_ACTIVE_SET, RPM_GPIO_TOGGLE_REQ, 0, gpio_active_kvp);

      /* Preparing and sending Sleep set vote for GPIO.
       * Since we are not clearing our vote while exiting from Sleep,
       * it is okay to send it only once. */
      gpio_sleep_kvp = kvp_create(4 * 3 * 2);
      kvp_put( gpio_sleep_kvp, gpio_numb_key,
               sizeof(gpio_numb), (void *)&gpio_numb );
      kvp_put( gpio_sleep_kvp, gpio_state_key,
               sizeof(gpio_sleep_state), (void *)&gpio_sleep_state );

      rpm_post_request( RPM_SLEEP_SET, RPM_GPIO_TOGGLE_REQ, 0, gpio_sleep_kvp );

      /* Relesing KVPs */
      kvp_destroy( gpio_active_kvp );
      kvp_destroy( gpio_sleep_kvp );
    }

    /* Releasing platform handle */
    (void)DAL_DeviceDetach( platform_handle );
  }
}

/*===========================================================================
 *                        GLOBAL FUNCTIONS
 *==========================================================================*/

/**
 * @brief cxo_shutdown_init
 *
 * Performs required initialization for cxo lpr.
 */
void cxo_shutdown_init(void)
{
  kvp_t *cxo_active_kvp = NULL;                 /* Active Set KVP for CXO */
  kvp_t *cxo_sleep_kvp = NULL;                  /* Sleep set KVP for CXO */
  const unsigned int cxo_enab_key = 0x62616e45; /* Enab key in little endian */
  const unsigned int cxo_req = 0;               /* CXO request for Sleep Set */
  const unsigned int active_cxo_req = 1;        /* CXO request for Active Set */

  /* Creating KVPs for Sleep and active set for cxo resource */
  cxo_active_kvp = kvp_create(4 * 3);
  cxo_sleep_kvp = kvp_create(4 * 3);

  /* Preparing and sending one time active set vote for CXO */
  kvp_put(cxo_active_kvp, cxo_enab_key, 
          sizeof(active_cxo_req), (void *)&active_cxo_req);
  rpm_post_request(RPM_ACTIVE_SET, RPM_CLOCK_0_REQ, 0, cxo_active_kvp);

  /* Preparing and sending Sleep set vote for cxo.
   * Since for cxo, we are not clearing our vote upon exiting from Sleep, it
   * is sufficient to send the Sleep set vote only once */
  kvp_put(cxo_sleep_kvp, cxo_enab_key, sizeof(cxo_req), (void *)&cxo_req);
  rpm_post_request(RPM_SLEEP_SET, RPM_CLOCK_0_REQ, 0, cxo_sleep_kvp);

  /* Target specific initialization - if any */
  cxo_shutdown_target_init();

  /* Relesing KVPs */
  kvp_destroy( cxo_active_kvp );
  kvp_destroy( cxo_sleep_kvp );
}

/**
 * @brief cxo_shutdown_enter
 *
 * Function that gets called when Master is voting for cxo shutdown during
 * a Sleep cycle.
 *
 * @param wakeup_tick: Absolute time tick (in 19.2 Mhz) when Master is 
 *                     expected to wake up.
 */
void cxo_shutdown_enter(uint64 wakeup_tick)
{
}

/**
 * @brief cxo_shutdown_exit
 *
 * Exit function which gets called while exiting from Sleep on master side for
 * a Sleep cycle when master voted for cxo shutdown.
 */
void cxo_shutdown_exit( void )
{
  vmpm_TriggerInterrupts();
  return;
}
