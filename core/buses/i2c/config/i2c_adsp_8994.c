/*=============================================================================

  FILE:     I2cDriverDevices_lpass_8994.c

  OVERVIEW: This file has the devices for 8994 platform for adsp. 
 
            Copyright (c) 2009 - 2011 Qualcomm Technologies Incorporated.
            All Rights Reserved.
            Qualcomm Confidential and Proprietary 

  ===========================================================================*/

/*=========================================================================
  EDIT HISTORY FOR MODULE

  $Header: //components/rel/core.adsp/2.6.1/buses/i2c/config/i2c_adsp_8994.c#2 $
  $DateTime: 2014/11/26 09:36:21 $$Author: pwbldsvc $

  When     Who    What, where, why
  -------- ---    -----------------------------------------------------------
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
   //I2CPLAT_PROPERTY_INIT(0x2001c023,0x2001c033,2,"PERIPH_SS",0x123000,CLOCK_GCC_BLSP1_AHB_CLK,CLOCK_GCC_BLSP1_QUP1_APPS_CLK), //GPIO 2 & 3
   //I2CPLAT_PROPERTY_INIT(0x2001c063,0x2001c073,2,"PERIPH_SS",0x124000,CLOCK_GCC_BLSP1_AHB_CLK,CLOCK_GCC_BLSP1_QUP2_APPS_CLK), //GPIO 6 & 7
   //I2CPLAT_PROPERTY_INIT(0x2001c0a4,0x2001c0b4,2,"PERIPH_SS",0x125000,CLOCK_GCC_BLSP1_AHB_CLK,CLOCK_GCC_BLSP1_QUP3_APPS_CLK), //GPIO 10 & 11
   //I2CPLAT_PROPERTY_INIT(0x2001c134,0x2001c144,2,"PERIPH_SS",0x126000,CLOCK_GCC_BLSP1_AHB_CLK,CLOCK_GCC_BLSP1_QUP4_APPS_CLK), //GPIO 19 & 20

   I2CPLAT_PROPERTY_INIT(0x2001c174,0x2001c185,2,"PERIPH_SS",0x127000,CLOCK_GCC_BLSP1_AHB_CLK,CLOCK_GCC_BLSP1_QUP5_APPS_CLK), //GPIO 23 & 24
   //I2CPLAT_PROPERTY_INIT(0x2001c023,0x2001c1c3,2,"PERIPH_SS",0x128000,CLOCK_GCC_BLSP1_AHB_CLK,CLOCK_GCC_BLSP1_QUP6_APPS_CLK), //GPIO 27 & 28

   I2CPLAT_PROPERTY_INIT(0x2001c2b3,0x2001c2c3,2,"PERIPH_SS",0x163000,CLOCK_GCC_BLSP2_AHB_CLK,CLOCK_GCC_BLSP2_QUP1_APPS_CLK) //GPIO 43 & 44
   //I2CPLAT_PROPERTY_INIT(0x2001c2f3,0x2001c303,2,"PERIPH_SS",0x163000,CLOCK_GCC_BLSP2_AHB_CLK,CLOCK_GCC_BLSP2_QUP2_APPS_CLK) // GPIO 47 & 48
   //I2CPLAT_PROPERTY_INIT(0x2001c334,0x2001c344,2,"PERIPH_SS",0x163000,CLOCK_GCC_BLSP2_AHB_CLK,CLOCK_GCC_BLSP2_QUP3_APPS_CLK) // GPIO 51 & 52
   //I2CPLAT_PROPERTY_INIT(0x2001c374,0x2001c384,2,"PERIPH_SS",0x163000,CLOCK_GCC_BLSP2_AHB_CLK,CLOCK_GCC_BLSP2_QUP4_APPS_CLK) // GPIO 55 & 56
   //I2CPLAT_PROPERTY_INIT(0x2001c533,0x2001c553,2,"PERIPH_SS",0x163000,CLOCK_GCC_BLSP2_AHB_CLK,CLOCK_GCC_BLSP2_QUP5_APPS_CLK) // GPIO 83 & 84
   //I2CPLAT_PROPERTY_INIT(0x2001c573,0x2001c583,2,"PERIPH_SS",0x163000,CLOCK_GCC_BLSP2_AHB_CLK,CLOCK_GCC_BLSP2_QUP6_APPS_CLK) // GPIO 87 & 88


};

I2cDev_PropertyType i2cDevPropertyArray[] ATTRIBUTE_ISLAND_DATA =
{
   //I2CDEV_PROPERTY_INIT(I2CDEV_PROPVALUE_INPUT_CLK_19200_KHZ),
   //I2CDEV_PROPERTY_INIT(I2CDEV_PROPVALUE_INPUT_CLK_19200_KHZ),
   //I2CDEV_PROPERTY_INIT(I2CDEV_PROPVALUE_INPUT_CLK_19200_KHZ),
   //I2CDEV_PROPERTY_INIT(I2CDEV_PROPVALUE_INPUT_CLK_19200_KHZ),
   //I2CDEV_PROPERTY_INIT(I2CDEV_PROPVALUE_INPUT_CLK_19200_KHZ),
   //I2CDEV_PROPERTY_INIT(I2CDEV_PROPVALUE_INPUT_CLK_19200_KHZ),
   //I2CDEV_PROPERTY_INIT(I2CDEV_PROPVALUE_INPUT_CLK_19200_KHZ),
   //I2CDEV_PROPERTY_INIT(I2CDEV_PROPVALUE_INPUT_CLK_19200_KHZ),
   //I2CDEV_PROPERTY_INIT(I2CDEV_PROPVALUE_INPUT_CLK_19200_KHZ),
   //I2CDEV_PROPERTY_INIT(I2CDEV_PROPVALUE_INPUT_CLK_19200_KHZ),

   I2CDEV_PROPERTY_INIT(I2CDEV_PROPVALUE_INPUT_CLK_19200_KHZ),
   I2CDEV_PROPERTY_INIT(I2CDEV_PROPVALUE_INPUT_CLK_19200_KHZ)
};

I2cDrv_DriverProperty i2cDrvPropertyArray[] ATTRIBUTE_ISLAND_DATA =
{
   //I2CDRV_DRIVERPROPERTY_INIT(I2CDRV_I2C_1, FALSE, 0),
   //I2CDRV_DRIVERPROPERTY_INIT(I2CDRV_I2C_2, FALSE, 0),
   //I2CDRV_DRIVERPROPERTY_INIT(I2CDRV_I2C_3, FALSE, 0),
   //I2CDRV_DRIVERPROPERTY_INIT(I2CDRV_I2C_4, FALSE, 0),
   I2CDRV_DRIVERPROPERTY_INIT(I2CDRV_I2C_5, FALSE, 0),
   //I2CDRV_DRIVERPROPERTY_INIT(I2CDRV_I2C_6, FALSE, 0),

   I2CDRV_DRIVERPROPERTY_INIT(I2CDRV_I2C_7, FALSE, 0)
   //I2CDRV_DRIVERPROPERTY_INIT(I2CDRV_I2C_8, FALSE, 0),
   //I2CDRV_DRIVERPROPERTY_INIT(I2CDRV_I2C_9, FALSE, 0),
   //I2CDRV_DRIVERPROPERTY_INIT(I2CDRV_I2C_10, FALSE, 0),
   //I2CDRV_DRIVERPROPERTY_INIT(I2CDRV_I2C_11, FALSE, 0),
   //I2CDRV_DRIVERPROPERTY_INIT(I2CDRV_I2C_12, FALSE, 0),
      
};

I2cDrv_DescType i2cDrvDescArray[I2C_NUM_PLATFORM_DEVICES] ATTRIBUTE_ISLAND_DATA ;
