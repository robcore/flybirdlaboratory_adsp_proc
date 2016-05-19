#ifndef _SPIDEVICE_H_
#define _SPIDEVICE_H_
/*
===========================================================================

FILE:   SpiDevice.h

DESCRIPTION:

===========================================================================

        Edit History

$Header: //components/rel/core.adsp/2.6.1/buses/spi/src/device/inc/SpiDevice.h#1 $

When     Who    What, where, why
-------- ---    -----------------------------------------------------------
07/19/13 lk     Added SpiDevice_SetPowerState API.
06/11/12 dk     Added review comments.
03/27/12 ag     Added batch transfer updates.
09/26/11 ag     Created

===========================================================================
        Copyright c 2011-2013 Qualcomm Technologies Incorporated.
            All Rights Reserved.
            Qualcomm Proprietary/GTDR

===========================================================================
*/
#include "SpiDriver.h"
#include "SpiDriverTypes.h"
#define SPIDEVICE_DEFAULT_BUS_FREQ_KHZ               10000
#define SPIDEVICE_DEFAULT_BYTE_TRANSFER_TIMEOUT_US   200

typedef void* SPIDEVICE_PLAT_HANDLE;

typedef struct
{
   SpiDataAddrType *pData;
   uint32 uLen;
}SpiBufferType;

typedef struct
{
   int32 nTransferStatus;
   void  *pArg;
}SpiDevice_AsyncResult;

typedef void (*SPI_DEV_ASYNC_CB)(SpiDevice_AsyncResult *pResult);
typedef void* SpiPlatBuffer;


typedef enum SpiDevice_PowerStates
{
   SPIDEVICE_POWER_STATE_0,/**< Bus and clocks off. */
   SPIDEVICE_POWER_STATE_1,/**< Bus on clocks off. */
   SPIDEVICE_POWER_STATE_2,/**< Bus on clocks on. */
} SpiDevice_PowerStates;


/** @brief Initializes the device.

    This Function Initializes the device and creates the
    necessary data structures to support other calls into the
    device.

    @param[in] uDevId    Device index.
    @param[in] phDev     Pointer to device handle.

    @return int32 - SPI_DEVICE_SUCCESS on success, error code on error.
  */
int32
SpiDevice_Init
(
   uint32           qup_core_num,
   SPIDEVICE_HANDLE *phDev 
);

/** @brief Deinitializes the device.

    This Function Deinitializes the device and releases
    resources acquired during init.

    @param[in] hDev      Device handle.

    @return int32 - SPI_DEVICE_SUCCESS on success, error code on error.
  */
int32
SpiDevice_DeInit
(
   SPIDEVICE_HANDLE                        hDev 
);

/** @brief Set client Configuration for the subsequent 
           transfers.

    @param[in] hDev      Device handle.
    @param[in] *pQupConfig   Pointer to the QUP config for data transfer.

    @return int32 - SPI_DEVICE_SUCCESS on success, error code on error.
  */
int32
SpiDevice_Configure
(
   SPIDEVICE_HANDLE   hDev,
   SpiDeviceInfoType *pQupConfig
);

/** @brief Set the power state of the device.

    This Function sets the power state for the device.

    @param[in] hDev           Device handle.
    @param[in] ePowerState    the new power state

    @return          int32 .
  */
int32
SpiDevice_SetPowerState (SPIDEVICE_HANDLE hDev, 
                         SpiDevice_PowerStates ePowerState);


/** @brief Peform a bi-direction transfer

    Read a buffer from SPI device and/or Write a buffer of 
   data to a SPI device

    @param[in] hDev           Device handle.
    @param[in] *pQupConfig   Pointer to the QUP config for data transfer.
                                           Client function can set it to NULL 
                                           if it need to use the settings used 
                                           by previous call with the same 
                                           device context.
    @param[in] pReadBuffer    Pointer where incoming data will
          be stored.
    @param[in] uReadBufLen    Number of bytes of valid data to be 
        stored in pReadbuffer
    @param[in] pWriteBuffer    Pointer where outgoing data is  
          stored.
    @param[in] uWriteBufLen    Number of bytes of valid data stored in 
        pWritebuffer
    @return int32 - SPI_DEVICE_SUCCESS on success, error code on error.
  */
int32
SpiDevice_WriteRead
(
   SPIDEVICE_HANDLE                          hDev,
   SpiDeviceInfoType                         *pQupConfig,
   SpiDataAddrType                           *pReadBuffer,
   uint32                                    uReadBufLen,
   SpiDataAddrType                           *pWriteBuffer,
   uint32                                    uWriteBufLen
); 
#endif /* _SPIDEVICE_H_ */
