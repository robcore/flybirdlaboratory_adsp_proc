/*==============================================================================

  D A L   G P I O   I N T E R R U P T   C O N T R O L L E R    

DESCRIPTION
  This file has the direct connect GPIO interrupt support for the 8960 target.

REFERENCES

        Copyright © 2011 Qualcomm Technologies Incorporated.
               All Rights Reserved.
            QUALCOMM Proprietary/GTDR
===========================================================================*/

/*===========================================================================

                      EDIT HISTORY FOR FILE

This section contains comments describing changes made to this file.
Notice that changes are listed in reverse chronological order.

$Header: //components/rel/core.adsp/2.6.1/systemdrivers/GPIOInt/config/kernel/apq8084/GPIOInt_ConfigData.c#1 $

when       who     what, where, why
--------   ---     ----------------------------------------------------------
1/1/2010   aratin  First draft created. 
===========================================================================*/

#include "DALReg.h"
#include "DALDeviceId.h"
#include "DDIGPIOInt.h"
#include "HALgpioint.h"
#include "GPIOInt.h"

/*
 * LPASS Interrupt Config Map
 */

GPIOIntConfigMapType interrupt_config_map[] =
{
  {GPIOINT_NONE, HAL_GPIOINT_DIRECTCONNECT_0, 24,GPIOINTF_EXTERNAL_CONFIG}, /* Direct connect  0 owned by audio Codec*/
  {GPIOINT_NONE, HAL_GPIOINT_DIRECTCONNECT_1, 25,GPIOINTF_EXTERNAL_CONFIG}, /* Direct connect  1 owned by audio Codec*/
  {GPIOINT_NONE, HAL_GPIOINT_DIRECTCONNECT_2, 26,0}, /* Direct connect  2*/
  {GPIOINT_NONE, HAL_GPIOINT_DIRECTCONNECT_3, 27,0}, /* Direct connect  3*/
  {GPIOINT_NONE, HAL_GPIOINT_DIRECTCONNECT_4, 28,0}, /* Direct connect  4*/
  {GPIOINT_NONE, HAL_GPIOINT_DIRECTCONNECT_5, 29,0}, /* Direct connect  5*/
  {53,          HAL_GPIOINT_SUMMARY,         GPIOINT_NONE,0}, /* Sensors GPIO in MultiPD is a summary interrupt*/
  {54,          HAL_GPIOINT_SUMMARY,         GPIOINT_NONE,0}, /* Sensors GPIO in MultiPD is a summary interrupt*/
  {49,          HAL_GPIOINT_SUMMARY,         GPIOINT_NONE,0}, /* Sensors GPIO in MultiPD is a summary interrupt*/
  {50,          HAL_GPIOINT_SUMMARY,         GPIOINT_NONE,0}, /* Sensors GPIO in MultiPD is a summary interrupt*/
  {8 ,          HAL_GPIOINT_SUMMARY,         GPIOINT_NONE,0}, /* Sensors GPIO in MultiPD is a summary interrupt*/
  {76,          HAL_GPIOINT_SUMMARY,         GPIOINT_NONE,0}, /* Sensors GPIO in MultiPD is a summary interrupt*/
  {77,          HAL_GPIOINT_SUMMARY,         GPIOINT_NONE,0}, /* Sensors GPIO in MultiPD is a summary interrupt*/
  {78,          HAL_GPIOINT_SUMMARY,         GPIOINT_NONE,0}, /* Sensors GPIO in MultiPD is a summary interrupt*/
  {55,          HAL_GPIOINT_SUMMARY,         GPIOINT_NONE,0}, /* Sensors GPIO in MultiPD is a summary interrupt*/
  {60,          HAL_GPIOINT_SUMMARY,         GPIOINT_NONE,0}, /* Sensors GPIO in MultiPD is a summary interrupt*/
  {56,          HAL_GPIOINT_SUMMARY,         GPIOINT_NONE,0}, /* Sensors GPIO in MultiPD is a summary interrupt*/
  {57,          HAL_GPIOINT_SUMMARY,         GPIOINT_NONE,0}, /* Sensors GPIO in MultiPD is a summary interrupt*/
  {79,          HAL_GPIOINT_SUMMARY,         GPIOINT_NONE,0}, /* Sensors GPIO in MultiPD is a summary interrupt*/
  {95,          HAL_GPIOINT_SUMMARY,         GPIOINT_NONE,0}, /* Sensors GPIO in MultiPD is a summary interrupt*/
  {6 ,          HAL_GPIOINT_SUMMARY,         GPIOINT_NONE,0}, /* Sensors GPIO in MultiPD is a summary interrupt*/
  {7 ,          HAL_GPIOINT_SUMMARY,         GPIOINT_NONE,0}, /* Sensors GPIO in MultiPD is a summary interrupt*/
  {4 ,          HAL_GPIOINT_SUMMARY,         GPIOINT_NONE,0}, /* Sensors GPIO in MultiPD is a summary interrupt*/   
  {5 ,          HAL_GPIOINT_SUMMARY,         GPIOINT_NONE,0}, /* Sensors GPIO in MultiPD is a summary interrupt*/   
  {84,          HAL_GPIOINT_SUMMARY,         GPIOINT_NONE,0}, /* Sensors GPIO in MultiPD is a summary interrupt*/   
  {80,          HAL_GPIOINT_SUMMARY,         GPIOINT_NONE,0}, /* Sensors GPIO in MultiPD is a summary interrupt*/   
};











