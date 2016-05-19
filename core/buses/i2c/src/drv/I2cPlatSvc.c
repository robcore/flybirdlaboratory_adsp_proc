/*=============================================================================

  FILE:   I2cPlatSvc.c

  OVERVIEW: This file contains the implementation for the platform services.
 
          Copyright (c) 2011 - 2013 Qualcomm Technologies Incorporated.
          All Rights Reserved.
          Qualcomm Confidential and Proprietary 

=============================================================================*/
/*=============================================================================
EDIT HISTORY FOR MODULE

$Header: //components/rel/core.adsp/2.6.1/buses/i2c/src/drv/I2cPlatSvc.c#1 $
$DateTime: 2014/10/16 12:45:40 $$Author: pwbldsvc $
When     Who    What, where, why
-------- ---    -----------------------------------------------------------
07/17/13 LK     Added xml properties.
09/26/11 LK     Created
=============================================================================*/

/*-------------------------------------------------------------------------
 * Include Files
 * ----------------------------------------------------------------------*/

#include "I2cPlatSvc.h"
//#include "I2cSys.h"
#include "I2cError.h"
#include "uClock.h"


//DEBUG
//#include "DALStdDef.h"
//#include "DALSys.h"
//#include "ClockBoot.h"
//#include "DALDeviceId.h"
//#include "DDITlmm.h"
//DEBUG
/*----------------------------------------------------------------------------
 * Preprocessor Definitions and Constants
 * -------------------------------------------------------------------------*/
#define QUP_FREQ_HZ                            19200000

#define I2C_DEVICE_PLATBAM_MAX_BAM_THRESHOLD (32*1024)
#define I2C_DEVICE_PLATBAM_MAX_DESC_SIZE     0x100



/*-------------------------------------------------------------------------
 * Static Variable Definitions
 * ----------------------------------------------------------------------*/



/*-------------------------------------------------------------------------
 * Static Function Declarations and Definitions
 * ----------------------------------------------------------------------*/

/*-------------------------------------------------------------------------
 * Externalized Function Definitions
 * ----------------------------------------------------------------------*/

/** @brief Enables the I2C clocks.
   
    @param[in] pPlat platform device pointer.
    
    @return             I2C_RES_SUCCESS is successful, otherwise
                        I2cPlat_Error.
  */
int32 I2cPlat_VoteI2cClkOn
(
   I2cPlat_DescType *pPlat
)
{
   
   if ( !uClock_EnableClock(pPlat->props.ahbClkId) ) {
      return I2CPLAT_ERROR_FAILED_TO_ENABLE_AHB_CLK;     
   }
   if ( !uClock_EnableClock(pPlat->props.appsClkId) ) {
      return I2CPLAT_ERROR_FAILED_TO_ENABLE_APPS_CLK;     
}

   return I2C_RES_SUCCESS;    
}

/** @brief Disables the I2C clocks.
  
    @param[in] pPlat platform device pointer.
    
    @return             I2C_RES_SUCCESS is successful, otherwise
                        I2cPlat_Error.
  */
int32 I2cPlat_VoteI2cClkOff
(
   I2cPlat_DescType      *pPlat
)
{
   
   if ( !uClock_DisableClock(pPlat->props.ahbClkId) ) {
      return I2CPLAT_ERROR_FAILED_TO_DISABLE_AHB_CLK;     
   }
   if ( !uClock_DisableClock(pPlat->props.appsClkId) ) {
      return I2CPLAT_ERROR_FAILED_TO_DISABLE_APPS_CLK;     
}

   return I2C_RES_SUCCESS;
}



