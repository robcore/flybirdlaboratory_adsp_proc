/*==========================================================================

  FILE:         spm.c

  DESCRIPTION:  This file contains the implementation of APIs for 
                subsystem power manager (SPM). Essentially it makes call to
                corresponding HAL functions for SPM.

  This module contains routines for the subsystem power manager (SPM).

                Copyright (c) 2011-2012 Qualcomm Technologies Incorporated.
                All Rights Reserved.
                Qualcomm Confidential and Proprietary

  $Header: //components/rel/core.adsp/2.6.1/power/spm/src/spm.c#1 $
============================================================================*/

/*============================================================================
                           INCLUDE FILES FOR MODULE
============================================================================*/

#include "spm.h"
#include "HALspm.h"
#include "CoreVerify.h"

/*============================================================================
                   DEFINITIONS AND DECLARATIONS FOR MODULE

This section contains local definitions for constants, macros, typedefs,
and other items needed by this module.
============================================================================*/

/*=============================================================================
                    EXTERNAL FUNCTION DEFINITIONS
=============================================================================*/

/*============================================================================
 FUNCTION SPM_SET_LOW_POWER_MODE
  
 DESCRIPTION
   This function is used to set the low power mode of the SPM HW.  The low
   power mode will be valid the next time the SPM HW receives a SW_DONE_EN
   signal from the processor.  This function should be used to set the low
   power mode before every halt in order to guarantee that the SW_DONE_EN
   signal is regarded in the desired way.
 
 PARAMETERS
   low_power_mode  Desired low power mode during the next halt. 
   core_num        This tells the SPM driver which core to program the
                   SPM for.  The first core starts at 0, and the core
                   numbers go up from there.  This function will do
                   nothing if given an invalid core number.  
 
 DEPENDENCIES
   None
 
 RETURN VALUE
   None
 
 SIDE EFFECTS
   None
 ============================================================================*/
void spm_set_low_power_mode
( 
  uint32 core_num,
  spm_low_power_mode_type low_power_mode
)
{
  CORE_VERIFY( core_num < g_spmNumCores );
  CORE_VERIFY( low_power_mode < SPM_NUM_LOW_POWER_MODES );
  HAL_spm_SetLowPowerMode( core_num, low_power_mode );
} /* spm_set_low_power_mode */

/*============================================================================
 FUNCTION SPM_SET_RPM_BYPASS
 
 DESCRIPTION
   This function is used to tell the SPM driver whether or not the RPM
   handshaking should be performed during the next power savings sequence.
   This function should be called before halting the processor.
 
 PARAMETERS
   rpm_bypass   Indicates whether or not the RPM handshaking should be
                performed.  The choices are:
                  SPM_RPM_PERFORM_HANDSHAKE  - Perform the RPM handshake.
                  SPM_RPM_BYPASS_HANDSHAKE -    Bypass the RPM handshake.
 
   core_num     This tells the SPM driver which core to program the
                SPM for.  The first core starts at 0, and the core
                numbers go up from there.  This function will do
                nothing if given an invalid core number.  

 DEPENDENCIES
   None
 
 RETURN VALUE
   None
 
 SIDE EFFECTS
   None
 ============================================================================*/
void spm_set_rpm_bypass
( 
  uint32              core_num,
  spm_rpm_bypass_type rpm_bypass
)
{
  CORE_VERIFY(core_num < g_spmNumCores);
  HAL_spm_Set_RPM_HandshakeMode( core_num, rpm_bypass );
} /* spm_set_rpm_bypass */

/*============================================================================
 FUNCTION spm_enable
  
 DESCRIPTION
   Enable/Disable the SPM HW.
 
 PARAMETERS
   core_num     Which core's SPM (0,1,2,...)
   spm_enable   TRUE to enable; FALSE to disable.

 DEPENDENCIES
   None
 
 RETURN VALUE
   None
 
 SIDE EFFECTS
   None
 ============================================================================*/
void spm_enable( uint32 core_num, boolean spm_enable )
{
  CORE_VERIFY(core_num < g_spmNumCores);
  HAL_spm_Enable( core_num, spm_enable );
}

/*============================================================================
 FUNCTION spm_initialize
  
 DESCRIPTION
   This is the init function for the SPM driver.  It initializes the HAL 
   layer as well as the driver layer.
 
 PARAMETERS
   None

 DEPENDENCIES
   None
 
 RETURN VALUE
   None
 
 SIDE EFFECTS
   None
 ============================================================================*/
void spm_initialize( void )
{
  char **ppszVersion    = NULL;
  
  /* Initialize the HAL layer */
  CORE_VERIFY( TRUE == HAL_spm_Init( SPM_CURR_CORE, ppszVersion ) );
} /* spm_initialize */

