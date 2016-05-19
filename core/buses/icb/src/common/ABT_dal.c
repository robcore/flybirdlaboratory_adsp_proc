/*==============================================================================

FILE:      ABT_dal.c

DESCRIPTION: This file implements DAL platform specific ABT driver.

PUBLIC CLASSES:  Not Applicable

INITIALIZATION AND SEQUENCING REQUIREMENTS:  N/A
 
Edit History

//#CHANGE - Update when put in the depot
$Header: //components/rel/core.adsp/2.6.1/buses/icb/src/common/ABT_dal.c#1 $ 
$DateTime: 2014/10/16 12:45:40 $
$Author: pwbldsvc $
$Change: 6781644 $ 

When        Who    What, where, why
----------  ---    -----------------------------------------------------------
2013/08/30  pm     Split out interrupt reg from ABT_init
2013/04/16  pm     Added interrupt priority and split out interrupt registration
2012/05/31  av     Created
 
        Copyright (c) 2013 Qualcomm Technologies Incorporated.
               All Rights Reserved.
            QUALCOMM Proprietary/GTDR
==============================================================================*/

#include "ABTimeout.h"
#include "ABT_internal.h"
#include "ABT_platform.h"
#include "DALSys.h"
#include "DALStdErr.h"
#include "DALDeviceId.h"
#include "DDIInterruptController.h"
#include "DDIClock.h"
#include "err.h"

/*============================================================================
                          DEFINEs/MACROs
============================================================================*/

/*============================================================================
                          TYPE DEFINITION
============================================================================*/

/*============================================================================
                                 FUNCTIONS
============================================================================*/

//*============================================================================*/
/**
@brief 
      Performs platform specific initialization for AHB Timeout driver.
      It enables clock/interrupts required for AHB timeout slave.
 
@param[in]  *PropData Pointer to property data structure.

@return    
      ABT_error_type indicating success or error.

@dependencies
      None.
 
@sideeffects 
      None. 
*/ 
/*============================================================================*/
ABT_error_type ABT_Platform_Init( ABT_propdata_type * PropData )
{
  DalDeviceHandle *pHandle;
  ClockIdType nId;
  uint32 i;

  // Enable Slave Clocks
  if(DAL_SUCCESS != DAL_DeviceAttach(DALDEVICEID_CLOCK, &pHandle))
  {
      ERR_FATAL("ABTimeout: Device attach to Clock failed.", 0, 0, 0);
      return ABT_ERROR_INIT_FAILURE;
  }

  for(i = 0; i < PropData->len; i++)
  {     
      if(DAL_SUCCESS != DalClock_GetClockId(pHandle, PropData->slave_info[i].clk_name, &nId))
      {
          ERR_FATAL("ABTimeout: Could not get ClockId.", 0, 0, 0);
          return ABT_ERROR_INIT_FAILURE;
      }

      if(DAL_SUCCESS != DalClock_EnableClock(pHandle, nId))
      {
          ERR_FATAL("ABTimeout: Could not enable clock.", 0, 0, 0);
          return ABT_ERROR_INIT_FAILURE;
      }
  }

  return ABT_SUCCESS;
}

//*============================================================================*/
/**
@brief 
      Performs platform specific initialization for AHB Timeout driver.
      It enables clock/interrupts required for AHB timeout slave.
 
@param[in]  *PropData Pointer to property data structure.

@return    
      ABT_error_type indicating success or error.

@dependencies
      None.
 
@sideeffects 
      None. 
*/ 
/*============================================================================*/
ABT_error_type ABT_Platform_Register_Interrupt( ABT_propdata_type * PropData )
{
  // Register IRQs
  return ABT_Platform_Register_Interrupt_OS(
     PropData->platform_info->intr_vector, 
     ABT_Handle_Interrupt,
     NULL, 
     DALINTRCTRL_ENABLE_CONFIG(DALINTRCTRL_ENABLE_LEVEL_HIGH_TRIGGER, 
                               PropData->platform_info->intr_priority)
     );
}

//*============================================================================*/
/**
@brief 
      Logs syndrome register infomration using platform specific APIs.
 
@param[in]  *syndrome Pointer to syndrome info structure

@return    
      ABT_error_type indicating success or error.

@dependencies
      None.
 
@sideeffects 
      None. 
*/ 
/*============================================================================*/
ABT_error_type ABT_Platform_Log_Syndrome(ABT_syndrome_info_type *syndrome)
{
    ERR("ABTimeout: Bus %s hang; Syndrome ID: 0x%x", 
                  syndrome->slave_name, syndrome->id, 0);
    ERR("ABTimeout: Bus %s hang; Syndrome ADDR0: 0x%x", 
                  syndrome->slave_name, syndrome->addr0, 0);
    ERR("ABTimeout: Bus %s hang; Syndrome ADDR1: 0x%x", 
                  syndrome->slave_name, syndrome->addr1, 0);
    ERR("ABTimeout: Bus %s hang; Syndrome HREADY: 0x%x", 
                  syndrome->slave_name, syndrome->hready, 0);
    ERR("ABTimeout: Bus %s hang; Number of Slaves: %d", 
                  syndrome->slave_name, syndrome->num_slaves, 0);
    return ABT_SUCCESS;
}

//*============================================================================*/
/**
@brief 
      Logs syndrome register infomration using platform specific APIs.
 
@param[in]  hung_slaves Number of hung slaves.

@return    
      ABT_error_type indicating success or error.

@dependencies
      None.
 
@sideeffects 
      None. 
*/ 
/*============================================================================*/
ABT_error_type ABT_Platform_Report_Hang(uint32 hung_slaves)
{
      ERR_FATAL("ABTimeout: AHB Bus hang is detected, Number of bus hang detected := %d !!!",
                 hung_slaves, 0, 0);
      return ABT_SUCCESS;
}

//*============================================================================*/
/**
@brief 
      Gets platfrom specific property data structure for configuration.
 
@param[in]  None.

@return    
      ABT_propdata_type* Pointer to property data structure.

@dependencies
      None.
 
@sideeffects 
      None. 
*/ 
/*============================================================================*/
ABT_propdata_type* ABT_Platform_Get_Propdata(void)
{
   DALSYSPropertyVar ABTPropVar;
   DALSYS_PROPERTY_HANDLE_DECLARE(hABTProp);

   /* Get default configuration from config data */
   if (DAL_SUCCESS != DALSYS_GetDALPropertyHandleStr( "/dev/ABTimeout",
                                                      hABTProp ))
   {
     // Can't get property handle
     ERR("ABTimeout: Can't get DAL property handle.", 0, 0, 0);
     return NULL;
   }

   if ((DAL_SUCCESS == DALSYS_GetPropertyValue(hABTProp,
                                              "ABT_Propdata", 0, &ABTPropVar)))
   {
       if((0 >= ABTPropVar.dwLen))
       {
           ERR("ABTimeout: Invalid property data length", 0, 0, 0);
           return NULL;
       }
       return (ABT_propdata_type*) ABTPropVar.Val.pStruct;
   }

   ERR("ABTimeout: Can't get DAL property value", 0, 0, 0);
   return NULL;
}


