#ifndef _SPIDEVICEPLATSVC_H_
#define _SPIDEVICEPLATSVC_H_
/*
===========================================================================

FILE:   SpiDevicePlatSvc.h

DESCRIPTION:
    This file contains the API for the platform services.

===========================================================================

        Edit History

$Header: //components/rel/core.adsp/2.6.1/buses/spi/src/device/inc/SpiDevicePlatSvc.h#2 $

When     Who    What, where, why
-------- ---    -----------------------------------------------------------
05/15/13 ag     Created
===========================================================================
        Copyright c 2013 Qualcomm Technologies Incorporated.
            All Rights Reserved.
            Qualcomm Proprietary/GTDR

===========================================================================*/
#include "DDIClock.h"
#include "DALSys.h"
#include "SpiDevice.h"

#ifdef BUILD_FOR_ISLAND
#define ATTRIBUTE_ISLAND_CODE __attribute__((section("RX.island")))
#define ATTRIBUTE_ISLAND_CONST __attribute__((section("RO.island")))
#define ATTRIBUTE_ISLAND_DATA __attribute__((section("RW.island")))
#else
#define ATTRIBUTE_ISLAND_CODE /* empty */
#define ATTRIBUTE_ISLAND_CONST /* empty */
#define ATTRIBUTE_ISLAND_DATA /* empty */
#endif

typedef struct _SpiDevicePlatInfoType
{
   uint32 qupVirtBlockAddr;
   uint32 qupPhysBlockAddr;
   boolean bInterruptBased;
}SpiDevicePlatInfoType;

typedef struct SpiGpioCfg_s
{
   uint32      gpio_sig_spi_clk;
   uint32      gpio_sig_spi_cs;
   uint32      gpio_sig_spi_mosi;
   uint32      gpio_sig_spi_miso;
} SpiGpioCfg_t;

typedef struct
{
   char *pQupHClkName;
   char *pQupAppClkName;
   ClockIdType QupHClkId;
   ClockIdType QupAppClkId;
   uint32 uQupCoreNum;
   uint32 qupVirtBlockAddr;
   uint32 qupPhysBlockAddr;
   boolean bInterruptBased;
   DalDeviceHandle *pClkHandle;
   SpiGpioCfg_t spiGpio;
} SpiDevicePlat_DevCfg; //was SpiDevicePlat_DevTargetCfgType;


/** @brief Releases data structures necessary to support the target calls.

    @param[in] hPlat platform device handle.

    @return          int32 .
  */
int32 SpiDevicePlat_DeInitTarget(SPIDEVICE_PLAT_HANDLE hPlat);

//Interface: IBusPlatCfg
/** @brief Initializes data structures necessary to support the target calls.

    @param[in] phPlat pointer to platform device handle.

    @return          int32 .
  */
int32 SpiDevicePlat_InitTarget(uint32 qup_core_num, SPIDEVICE_PLAT_HANDLE *phPlat);


/** @brief Gets the app clock frequency in Hz.

    @param[in] hPlat platform device handle.
    @param[out] pFrequencyHz Frequency of the core.

    @return          int32 .
  */
uint32 SpiDevicePlat_GetAppClkHz
(
   SPIDEVICE_PLAT_HANDLE hPlat,
   uint32 *pFrequencyHz
   );

/** @brief Sets the app clock frequency in Hz.

    @param[in] hPlat platform device handle.
    @param[in] reqFrequencyHz Frequency requested
    @param[out] pFinalFrequencyHz Frequency after the request.

    @return          int32 .
  */
uint32 SpiDevicePlat_SetAppClkHz
(
   SPIDEVICE_PLAT_HANDLE hPlat,
   uint32 reqFrequencyHz,
   uint32 *pFinalFrequencyHz
);

//Interface: IBusPower
/** @brief Sets the power state of the device.

    @param[in] hPlat platform device handle.

    @return          int32 .
  */
int32 SpiDevicePlat_SetPowerState(SPIDEVICE_PLAT_HANDLE hPlat, uint32 state);

/** @brief Gets the power state of the device.

    @param[in] hPlat platform device handle.

    @return          int32 .
  */
int32 SpiDevicePlat_GetPowerState(SPIDEVICE_PLAT_HANDLE hPlat, uint32 state);

//Interface: IBusStore
/** @brief Reads the properties for this device.

    @param[in] hPlat platform device handle.
    @param[in] pDevProp       Pointer to properties structure.

    @return          int32 .
  */
int32 SpiDevicePlat_GetPlatformInfo (SPIDEVICE_PLAT_HANDLE hPlat, SpiDevicePlatInfoType *pDevProp);

uint32 SpiDevicePlat_RemovePnocVote(SPIDEVICE_PLAT_HANDLE hPlat);
uint32 SpiDevicePlat_AddPnocVote(SPIDEVICE_PLAT_HANDLE hPlat, uint32 freq);

#endif // _SPIDEVICEPLATSVC_H_

