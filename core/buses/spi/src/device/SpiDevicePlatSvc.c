/*
===========================================================================

FILE:   SpiDevicePlatSvc.c

DESCRIPTION:

===========================================================================

        Edit History

$Header: //components/rel/core.adsp/2.6.1/buses/spi/src/device/SpiDevicePlatSvc.c#3 $

When     Who    What, where, why
-------- ---    -----------------------------------------------------------
07/19/13 lk	Added xpu protection call. 
05/15/13 ag	Created 

===========================================================================
        Copyright c 2013 Qualcomm Technologies Incorporated.
            All Rights Reserved.
            Qualcomm Proprietary/GTDR

===========================================================================
*/

#include "SpiDevice.h"
#include "SpiDevicePlatSvc.h"
#include "SpiDeviceOsSvc.h"
#include "SpiDriver.h"

#include "stddef.h"
#include "stdio.h"

#include "DALStdDef.h"
#include "DALSys.h"
#include "uClock.h"
#include "DDIHWIO.h"
#include "DDIClock.h"

typedef enum SpiDevicePlat_Error
{
   SPIDEVICE_PLAT_ERROR_DAL_GET_PROPERTY_HANDLE = SPI_ERROR_CLS_PLATFORM,
   SPIDEVICE_PLAT_ERROR_ATTACH_TO_CLOCKS,
   SPIDEVICE_PLAT_ERROR_GETTING_CLK_ID,
   SPIDEVICE_PLAT_ERROR_INVALID_POWER_STATE,
   SPIDEVICE_PLAT_ERROR_FAILED_TO_SET_APPCLK_FREQ,
   SPIDEVICE_PLAT_ERROR_FAILED_TO_ENABLE_APPCLK,
   SPIDEVICE_PLAT_ERROR_FAILED_TO_DISABLE_APPCLK,
   SPIDEVICE_PLAT_ERROR_FAILED_TO_ENABLE_HCLK,
   SPIDEVICE_PLAT_ERROR_FAILED_TO_DISABLE_HCLK,
   SPIDEVICE_PLAT_ERROR_NULL_PTR,
} SpiDevicePlat_Error;

extern SpiDevicePlat_DevCfg Spi_DeviceCfg[];
static int32 SpiDevicePlat_ClkCtrl(SpiDevicePlat_DevCfg *pDev, boolean enable);

static SpiDevicePlat_DevCfg* SpiDevicePlat_GetTargetConfig(uint32 qup_core_num)
{
   SpiDevicePlat_DevCfg *tgtCfg = NULL;
   int32 index = -1, i;

   for (i = 0; i < SPIPD_DEVICE_COUNT; i++)
   {
      if (Spi_DeviceCfg[i].uQupCoreNum == qup_core_num)
      {
         index = i;
      }
   }
   if (index == -1)
   {
      return NULL;
   }
   tgtCfg = &(Spi_DeviceCfg[index]);

   return tgtCfg;
}

int32 SpiDevicePlat_InitTarget(uint32 qup_core_num, SPIDEVICE_PLAT_HANDLE *phPlat)
{
   int32 res = -1;
   SpiDevicePlat_DevCfg *tgtCfg = NULL;

   tgtCfg = SpiDevicePlat_GetTargetConfig(qup_core_num);

   if (NULL != tgtCfg)
   {
      *phPlat = (SPIDEVICE_PLAT_HANDLE)tgtCfg;

      do
      {
         if (SPI_SUCCESS != (res = SpiDevicePlat_ClkCtrl(tgtCfg, TRUE)))
         {
            break;
         }
         res = SPI_SUCCESS;
      }
      while (0);
   }
   return res;
}

int32 SpiDevicePlat_DeInitTarget(SPIDEVICE_PLAT_HANDLE hPlat)
{
   /* SpiDevicePlat_InitTarget, just does data structure allocation.
   * The allocated data structures will be available for the life-time 
   * of the driver. There is no point in allocating and de-allocating 
   * them.
   */
   SpiDevicePlat_DevCfg *tgtCfg = (SpiDevicePlat_DevCfg *)hPlat;

   (void)SpiDevicePlat_ClkCtrl(tgtCfg, FALSE);
   
   return SPI_SUCCESS;
}


int32 SpiDevicePlat_GetPlatformInfo(SPIDEVICE_PLAT_HANDLE hPlat, SpiDevicePlatInfoType *platInfo)
{
   SpiDevicePlat_DevCfg *pDev;

   pDev = (SpiDevicePlat_DevCfg *)hPlat;
   platInfo->qupVirtBlockAddr = pDev->qupVirtBlockAddr; //This has to be derived from some DAL Mem info call
   platInfo->qupPhysBlockAddr = pDev->qupPhysBlockAddr;
   platInfo->bInterruptBased = pDev->bInterruptBased;
   return SPI_SUCCESS;
}


/** @brief Sets the power state of the device.

    @param[in] hPlat platform device handle.

    @return          int32 .
  */
int32 SpiDevicePlat_SetPowerState(SPIDEVICE_PLAT_HANDLE hPlat, uint32 state)
{
/*   int32 res = SPI_SUCCESS;

   pDev = (SpiDevicePlat_DevCfg *)hPlat;

   switch (state)
   {
   case SPIDEVICE_POWER_STATE_2:
      break;
   case SPIDEVICE_POWER_STATE_1:
   case SPIDEVICE_POWER_STATE_0:
      break;
   default:
      break;
   }
   return res;*/
   return 0;
}

static int32 SpiDevicePlat_ClkCtrl(SpiDevicePlat_DevCfg *pDev, boolean enable)
{
   DALResult dalRes;
   int32 res = SPI_SUCCESS;

   do
   {
      dalRes = DalClock_GetClockId(pDev->pClkHandle,pDev->pQupAppClkName, &pDev->QupAppClkId);

      if (DAL_SUCCESS != dalRes)
      {
         res = SPIDEVICE_PLAT_ERROR_GETTING_CLK_ID;
         break;
      }

      dalRes = DalClock_GetClockId(pDev->pClkHandle, pDev->pQupHClkName, &pDev->QupHClkId);

      if (DAL_SUCCESS != dalRes)
      {
         res = SPIDEVICE_PLAT_ERROR_GETTING_CLK_ID;
         break;
      }

      /* Enable QUP Clock */
      if(enable)
      {
         dalRes = DalClock_EnableClock(pDev->pClkHandle, pDev->QupAppClkId);
         if (DAL_SUCCESS != dalRes)
         {
            res = SPIDEVICE_PLAT_ERROR_FAILED_TO_ENABLE_APPCLK;
            break;
         }

         /* Enable HCLK */
         dalRes = DalClock_EnableClock(pDev->pClkHandle, pDev->QupHClkId);
         if (DAL_SUCCESS != dalRes)
         {
            res = SPIDEVICE_PLAT_ERROR_FAILED_TO_ENABLE_HCLK;
            break;
         }
      }
      else
      {
         dalRes = DalClock_DisableClock(pDev->pClkHandle, pDev->QupAppClkId);
         if (DAL_SUCCESS != dalRes)
         {
            res = SPIDEVICE_PLAT_ERROR_FAILED_TO_DISABLE_APPCLK;
            break;
         }

         /* Enable HCLK */
         dalRes = DalClock_DisableClock(pDev->pClkHandle, pDev->QupHClkId);
         if (DAL_SUCCESS != dalRes)
         {
            res = SPIDEVICE_PLAT_ERROR_FAILED_TO_DISABLE_HCLK;
            break;
         }
      }
   }
   while (0);
   return res;
}

uint32 SpiDevicePlat_SetAppClkHz (SPIDEVICE_PLAT_HANDLE hPlat,
                                  uint32 reqFrequencyHz,
                                  uint32 *pFinalFrequencyHz)
{
   SpiDevicePlat_DevCfg *pDev = (SpiDevicePlat_DevCfg *)hPlat;

   DALResult dalRes;

   dalRes = DalClock_SetClockFrequency(pDev->pClkHandle, 
                            pDev->QupAppClkId,
                            reqFrequencyHz,
                            CLOCK_FREQUENCY_HZ_AT_MOST,
                            pFinalFrequencyHz);
   
   if (DAL_SUCCESS != dalRes)
   {
      return SPIDEVICE_PLAT_ERROR_FAILED_TO_SET_APPCLK_FREQ; 
   }

   return SPI_SUCCESS;
}

uint32 SpiDevicePlat_RemovePnocVote(SPIDEVICE_PLAT_HANDLE hPlat)
{
   //npa_issue_suppressible_request(hNpaClient, 0);
   return SPI_SUCCESS;
}

uint32 SpiDevicePlat_AddPnocVote(SPIDEVICE_PLAT_HANDLE hPlat, uint32 freq)
{
   //npa_issue_suppressible_request(hNpaClient, freq);
   return SPI_SUCCESS;
}
