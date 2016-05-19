/*=============================================================================

  FILE:     spi_adsp_8994.c

  OVERVIEW: Contains target specific SPI configuration for 8994 ADSP 
 
            Copyright (c) 2009 - 2014 Qualcomm Technologies Incorporated.
            All Rights Reserved.
            Qualcomm Confidential and Proprietary 

  ===========================================================================*/

/*=========================================================================
  EDIT HISTORY FOR MODULE

  $Header: //components/rel/core.adsp/2.6.1/buses/spi/src/config/spi_adsp_8994.c#4 $
  $DateTime: 2015/02/18 18:24:35 $$Author: pwbldsvc $

  When        Who    What, where, why
  --------    ---    -----------------------------------------------------------
  2014/11/25   vk    Updated with config for all QUP instances
  2014/04/01   vk    Initial version

  ===========================================================================*/
#include "SpiDevicePlatSvc.h"
#include "SpiDriverTypes.h"
#include "SpiDriver.h"
#include "DALDeviceId.h"
#include "DDIHWIO.h"
#include "DDITlmm.h"

spiDevice spiDevices[SPIPD_DEVICE_COUNT] ATTRIBUTE_ISLAND_DATA = {
   { NULL, 0, 0 }, //device handle, core number, current status
   { NULL, 11, 0 }
   //Add entry here to initialize an SPI core, format {NULL, QUPCORENUMBER, 0}
   //Valid range for QUPCORENUMBER is 0 to 11.
};


SpiDevicePlat_DevCfg Spi_DeviceCfg[SPIPD_DEVICE_COUNT] ATTRIBUTE_ISLAND_DATA;

#define SPI_PERIPH_SS_BASE_PHYS_ADDR 0xF9800000
//#define SPI_OPERATING_FREQ_HZ  1000000 // 1 MHz
#define SPI_OPERATING_FREQ_HZ  5000000 // 5 MHz
//#define SPI_OPERATING_FREQ_HZ  8000000 // 8 MHz
//#define SPI_OPERATING_FREQ_HZ 10000000 // 10 MHz

const uint32 SpiQupPhysAddrOffset[] ATTRIBUTE_ISLAND_DATA = {0x123000, 0x124000, 0x125000, 0x126000, 0x127000, 0x128000, 0x163000, 0x164000, 0x165000, 0x166000, 0x167000, 0x168000};

char *SpiClks[] ATTRIBUTE_ISLAND_DATA = { "gcc_blsp1_qup1_spi_apps_clk","gcc_blsp1_qup2_spi_apps_clk", "gcc_blsp1_qup3_spi_apps_clk", "gcc_blsp1_qup4_spi_apps_clk",
   "gcc_blsp1_qup5_spi_apps_clk", "gcc_blsp1_qup6_spi_apps_clk", "gcc_blsp2_qup1_spi_apps_clk", "gcc_blsp2_qup2_spi_apps_clk", "gcc_blsp2_qup3_spi_apps_clk", "gcc_blsp2_qup4_spi_apps_clk",
   "gcc_blsp2_qup5_spi_apps_clk", "gcc_blsp2_qup6_spi_apps_clk" };

const uint32 SpiGpioClk[] ATTRIBUTE_ISLAND_CONST = {0x2006C031, 0x2006C071, 0x2006C0B2, 0x2006C142, 0x2006C183, 0x2006C1C1, 0x2006C2C1, 0x2006C301, 0x2006C342, 0x2006C382, 0x2006C541, 0x2006C581};
const uint32 SpiGpioCS[] ATTRIBUTE_ISLAND_CONST = {0x2006C021, 0x2006C061, 0x2006C0A2, 0x2006C132, 0x2006C172, 0x2006C1B1, 0x2006C2B1, 0x2006C2F1, 0x2006C332, 0x2006C372, 0x2006C531, 0x2006C571};
const uint32 SpiClkGpioMISO[] ATTRIBUTE_ISLAND_CONST = {0x2006C011, 0x2006C051, 0x2006C091, 0x2006C122, 0x2006C162, 0x2006C1A2, 0x2006C2A1, 0x2006C2E1, 0x2006C322, 0x2006C363, 0x2006C522, 0x2006C561};
const uint32 SpiClkGpioMOSI[] ATTRIBUTE_ISLAND_CONST = {0x2006C001, 0x2006C041, 0x2006C081, 0x2006C112, 0x2006C152, 0x2006C193, 0x2006C291, 0x2006C2D1, 0x2006C312, 0x2006C353, 0x2006C512, 0x2006C551};

static DalDeviceHandle  ATTRIBUTE_ISLAND_DATA *pClkHandle;
static DalDeviceHandle  ATTRIBUTE_ISLAND_DATA *pTlmmHandle;

void SpiInit(void)
{
   int32 i;
   SpiDevicePlat_DevCfg *tgtCfg;
   DALResult dalRes;
   uint8 *periph_base = NULL;
   DalDeviceHandle *phDalHWIO = NULL;
   ClockIdType QupAppClkId;

   memset(Spi_DeviceCfg, 0, sizeof(Spi_DeviceCfg));

   dalRes = DAL_DeviceAttach(DALDEVICEID_HWIO, &phDalHWIO);
   if ((DAL_SUCCESS != dalRes) || (NULL == phDalHWIO))
   {
      return;
   }
   if (DAL_SUCCESS != DalHWIO_MapRegion(phDalHWIO, "PERIPH_SS", &periph_base))
   {
      return;
   }

   if (NULL == pClkHandle)
   {
      dalRes = DAL_ClockDeviceAttach(DALDEVICEID_CLOCK, &pClkHandle);
      if ((DAL_SUCCESS != dalRes) || (NULL == pClkHandle))
      {
         return;
      }
   }
   
   if (NULL == pTlmmHandle)
   {
      if (DAL_SUCCESS != DAL_DeviceAttachEx(NULL, DALDEVICEID_TLMM, DALTLMM_INTERFACE_VERSION, &pTlmmHandle))
      {
         return;
      }

      if (DAL_SUCCESS != DalDevice_Open(pTlmmHandle, DAL_OPEN_SHARED))
      {
         DAL_DeviceDetach(pTlmmHandle);
         pTlmmHandle = NULL;
         return;
      }
   }

   for (i = 0; i < SPIPD_DEVICE_COUNT; i++)
   {
      tgtCfg = &(Spi_DeviceCfg[i]);
      tgtCfg->uQupCoreNum = spiDevices[i].qup_core_num;
      tgtCfg->bInterruptBased = 0;
      tgtCfg->pQupAppClkName = SpiClks[tgtCfg->uQupCoreNum];
      tgtCfg->pQupHClkName = ((tgtCfg->uQupCoreNum <= 5) ? "gcc_blsp1_ahb_clk" : "gcc_blsp2_ahb_clk");
      tgtCfg->qupPhysBlockAddr = SPI_PERIPH_SS_BASE_PHYS_ADDR + SpiQupPhysAddrOffset[tgtCfg->uQupCoreNum];
      tgtCfg->qupVirtBlockAddr = (uint32)periph_base + SpiQupPhysAddrOffset[tgtCfg->uQupCoreNum];
      tgtCfg->pClkHandle = pClkHandle;
	  
	  //set up the initial CLK frequency. This does not turn on the clocks, just sets the frequency, 
	  //the clocks are turned on during SPI transfers.
	  dalRes = DalClock_GetClockId(pClkHandle, tgtCfg->pQupAppClkName, &QupAppClkId);
      if ((DAL_SUCCESS != dalRes) || (NULL == QupAppClkId))
      {
         return;
      }
	  dalRes = DalClock_SetClockFrequency (pClkHandle, QupAppClkId, SPI_OPERATING_FREQ_HZ, CLOCK_FREQUENCY_HZ_AT_MOST, NULL);
      if (DAL_SUCCESS != dalRes)
      {
         return;
      }
   }
}

void SpiInit_DeviceInstance(spi_device_id_t device_id)
{
   static uint32 SpiInitDone = FALSE;
   uint32 clkSig, mosiSig, misoSig, csSig;
   
   if (SpiInitDone == FALSE)
   {
      SpiInit();
      SpiInitDone = TRUE;
   }
   
   clkSig = SpiGpioClk[device_id];
   csSig = SpiGpioCS[device_id];
   misoSig = SpiClkGpioMISO[device_id];
   mosiSig = SpiClkGpioMOSI[device_id];
   do
   {
      if(DAL_SUCCESS != DalTlmm_ConfigGpio(pTlmmHandle, (DALGpioSignalType) clkSig, DAL_TLMM_GPIO_ENABLE))
         break;
      if(DAL_SUCCESS != DalTlmm_ConfigGpio(pTlmmHandle, (DALGpioSignalType) mosiSig, DAL_TLMM_GPIO_ENABLE))
         break;
      if(DAL_SUCCESS != DalTlmm_ConfigGpio(pTlmmHandle, (DALGpioSignalType) misoSig, DAL_TLMM_GPIO_ENABLE))
         break;
      if(csSig)
      {
         if(DAL_SUCCESS != DalTlmm_ConfigGpio(pTlmmHandle, (DALGpioSignalType) csSig, DAL_TLMM_GPIO_ENABLE))
            break;
      }
   }
   while (0); 
}

void SpiDeInit_DeviceInstance(spi_device_id_t device_id)
{
   uint32 clkSig, mosiSig, misoSig, csSig;
   
   clkSig = SpiGpioClk[device_id];
   csSig = SpiGpioCS[device_id];
   misoSig = SpiClkGpioMISO[device_id];
   mosiSig = SpiClkGpioMOSI[device_id];

   do
   {
      if(DAL_SUCCESS != DalTlmm_ConfigGpio(pTlmmHandle, (DALGpioSignalType) clkSig, DAL_TLMM_GPIO_DISABLE))
         break;
      if(DAL_SUCCESS != DalTlmm_ConfigGpio(pTlmmHandle, (DALGpioSignalType) mosiSig, DAL_TLMM_GPIO_DISABLE))
         break;
      if(DAL_SUCCESS != DalTlmm_ConfigGpio(pTlmmHandle, (DALGpioSignalType) misoSig, DAL_TLMM_GPIO_DISABLE))
         break;
      if(csSig)
      {
         if(DAL_SUCCESS != DalTlmm_ConfigGpio(pTlmmHandle, (DALGpioSignalType) csSig, DAL_TLMM_GPIO_DISABLE))
            break;
      }
   }
   while (0); 
}

