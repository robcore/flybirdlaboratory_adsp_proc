/*=============================================================================

  FILE:     I2cDriverDevices_lpass_8992.c

  OVERVIEW: This file has the devices for 8992 platform for adsp. 
 
            Copyright (c) 2009 - 2011 Qualcomm Technologies Incorporated.
            All Rights Reserved.
            Qualcomm Confidential and Proprietary 

  ===========================================================================*/

/*=========================================================================
  EDIT HISTORY FOR MODULE

  $Header: //components/rel/core.adsp/2.6.1/buses/i2c/config/i2c_adsp_8992.c#1 $
  $DateTime: 2014/10/16 12:45:40 $$Author: pwbldsvc $

  When     Who    What, where, why
  -------- ---    -----------------------------------------------------------
  08/29/14 NP     Added 8992 support
  07/01/14 SK     Removed all devices except 5 & 7 as 1 & 8 were causing conflicts.
  25/03/11 LK     Removed gsbi11,gsbi12 since they are dedicated to sps.
  12/03/09 LK     Created.

  ===========================================================================*/

/*-------------------------------------------------------------------------
 * Include Files
 * ----------------------------------------------------------------------*/

#include "I2cDriverTypes.h"
#include "I2cPlatSvc.h"
#include "I2cDevice.h"

#define I2C_NUM_PLATFORM_DEVICES         (2)


/*-------------------------------------------------------------------------
 * Preprocessor Definitions and Constants
 * ----------------------------------------------------------------------*/

const uint32              i2cDeviceNum = I2C_NUM_PLATFORM_DEVICES;

/*-------------------------------------------------------------------------
 * Type Declarations
 * ----------------------------------------------------------------------*/


#ifdef BUILD_FOR_ISLAND
#define ATTRIBUTE_ISLAND_CODE __attribute__((section("RX.island")))
#define ATTRIBUTE_ISLAND_CONST __attribute__((section("RO.island")))
#define ATTRIBUTE_ISLAND_DATA __attribute__((section("RW.island")))
#else
#define ATTRIBUTE_ISLAND_CODE /* empty */
#define ATTRIBUTE_ISLAND_CONST /* empty */
#define ATTRIBUTE_ISLAND_DATA /* empty */
#endif


/*-------------------------------------------------------------------------
 * Global Data Definitions
 * ----------------------------------------------------------------------*/
I2cPlat_PropertyType i2cPlatPropertyArray[] ATTRIBUTE_ISLAND_DATA =
{
   I2CPLAT_PROPERTY_INIT(0x2001c174,0x2001c185,2,"PERIPH_SS",0x127000,CLOCK_GCC_BLSP1_AHB_CLK,CLOCK_GCC_BLSP1_QUP5_APPS_CLK),
   I2CPLAT_PROPERTY_INIT(0x2001c2b3,0x2001c2c3,2,"PERIPH_SS",0x163000,CLOCK_GCC_BLSP2_AHB_CLK,CLOCK_GCC_BLSP2_QUP1_APPS_CLK)
};

I2cDev_PropertyType i2cDevPropertyArray[] ATTRIBUTE_ISLAND_DATA =
{
   I2CDEV_PROPERTY_INIT(I2CDEV_PROPVALUE_INPUT_CLK_19200_KHZ),
   I2CDEV_PROPERTY_INIT(I2CDEV_PROPVALUE_INPUT_CLK_19200_KHZ)
};

I2cDrv_DriverProperty i2cDrvPropertyArray[] ATTRIBUTE_ISLAND_DATA =
{
   I2CDRV_DRIVERPROPERTY_INIT(I2CDRV_I2C_5, FALSE, 0),
   I2CDRV_DRIVERPROPERTY_INIT(I2CDRV_I2C_7, FALSE, 0)
};

I2cDrv_DescType i2cDrvDescArray[I2C_NUM_PLATFORM_DEVICES] ATTRIBUTE_ISLAND_DATA ;
