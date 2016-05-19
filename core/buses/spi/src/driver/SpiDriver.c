/**
@file SpiDriver.c
@brief Serial Peripheral Interface (SPI) BUS API implementation 
*/

/*===========================================================================
Copyright (c) 2014 Qualcomm Technologies, Inc.  All Rights Reserved.
Qualcomm Technologies Proprietary and Confidential.
===========================================================================*/

/*===========================================================================

                            EDIT HISTORY FOR FILE

  $Header: //components/rel/core.adsp/2.6.1/buses/spi/src/driver/SpiDriver.c#4 $
  $DateTime: 2015/02/18 18:24:35 $
  $Author: pwbldsvc $

when         who      what, where, why
----------   ---      ------------------------------------
05/06/2014   vmk      Created

===========================================================================*/
#include "SpiDriverTypes.h"
#include "SpiDriver.h"
#include "SpiDevice.h"
#include "SpiLog.h"
#include "qurt_island.h"

#define SPI_MAX_NUM_DEVICES 12

enum spi_driver_errors 
{
   SPI_ERROR_INVALID_PARAM = SPI_ERROR_CLS_DRIVER,
   SPI_ERROR_DEVICE_UNAVAILABLE, //core is not meant for this core/pd/board
   SPI_ERROR_DEVICE_IN_USE, // 1 or more clients have opened this device, close first
   SPI_ERROR_DEVICE_NOT_OPEN,
   SPI_ERROR_INVALID_MODE //invalid power mode (e.g. this function can only be executed in big img mode)
};

extern spiDevice spiDevices[];
void SpiInit_DeviceInstance(spi_device_id_t device_id);
void SpiDeInit_DeviceInstance(spi_device_id_t device_id);

static int map_id_2_arr_idx(spi_device_id_t device_id)
{
   uint32 i;
   for (i = 0; i < SPIPD_DEVICE_COUNT; i++)
   {
      if (spiDevices[i].qup_core_num == device_id)
      {
         return i;
      }
   }
   return -1;
}

static void set_spi_device_params (const spi_config_t *p_config, SpiDeviceInfoType *p_spi_info)
{
   p_spi_info->deviceParameters.eClockMode = (SpiClockModeType)p_config->spi_clk_always_on;
   p_spi_info->deviceParameters.eClockPolarity = (SpiClockPolarityType)p_config->spi_clk_polarity;
   p_spi_info->deviceParameters.eShiftMode = (SpiShiftModeType)p_config->spi_shift_mode;
   p_spi_info->deviceParameters.u32DeassertionTime = p_config->deassertion_time_ns;
   p_spi_info->deviceParameters.u32MinSlaveFrequencyHz = p_config->min_slave_freq_hz;
   p_spi_info->deviceParameters.u32MaxSlaveFrequencyHz = p_config->max_slave_freq_hz;
   p_spi_info->deviceParameters.eCSPolarity = (SpiCSPolarityType)p_config->spi_cs_polarity;
   p_spi_info->deviceParameters.eCSMode = (SpiCSModeType)p_config->spi_cs_mode;
   p_spi_info->nSlaveNumber = p_config->spi_slave_index;
   p_spi_info->transferParameters.nNumBits = p_config->spi_bits_per_word;
   p_spi_info->transferParameters.eTransferMode = SPI_TRANSFER_MODE_DEFAULT;
   p_spi_info->transferParameters.eLoopbackMode = p_config->loopback_mode; 
   p_spi_info->transferParameters.eInputPacking = SPI_INPUT_PACKING_DISABLED;
   p_spi_info->transferParameters.eOutputUnpacking = SPI_OUTPUT_UNPACKING_DISABLED;
   p_spi_info->transferParameters.slaveTimeoutUs = 0;
}

int32 spi_open(spi_device_id_t device_id)
{
   SPI_RESULT result = SPI_SUCCESS;
   int device_idx;

   if (device_id >= SPI_MAX_NUM_DEVICES)
   {
      return SPI_ERROR_INVALID_PARAM;
   }

   if ((device_idx = map_id_2_arr_idx(device_id)) < 0)
   {
      SPIDEVICE_LOG(ERROR, "spi_open() invalid device_id: %08x", device_id);
      return SPI_ERROR_DEVICE_UNAVAILABLE;
   }
   
   if (qurt_island_get_status() == 0)
   {
      SpiInit_DeviceInstance(device_id);
   }
   else
   {
      return SPI_ERROR_INVALID_MODE;
   }

   /* Check if there is already an open client. This wrapper supports
    * only one open client per device */
   if (spiDevices[device_idx].status & SPI_DEVICE_OPEN)
   {
      SPIDEVICE_LOG(ERROR, "spi_open() device_id already open: %08x", device_id);
      return SPI_ERROR_DEVICE_IN_USE;
   }

   if (NULL == spiDevices[device_idx].hSpiDev)
   {
      // call into device layer to configure the SPI device
      result = SpiDevice_Init(spiDevices[device_idx].qup_core_num, &spiDevices[device_idx].hSpiDev);

      if (result != SPI_SUCCESS)
      {
         SPIDEVICE_LOG(ERROR, "spi_open() init error: %08x", spiResult);
      }
      else
      {
         /* Device is now open */
         spiDevices[device_idx].status |= SPI_DEVICE_OPEN;
      }
   }

   if (result != SPI_SUCCESS)
   {
      /* Clean up everything that we can. Ignore the return value from
       * spi_close() as we want to return the reason the spi_open()
       * failed */
      (void)spi_close(device_id);
   }

   return result;
}

/* @copydoc spi_read */
int32 spi_read (spi_device_id_t device_id, const spi_config_t *p_config, spi_transaction_t *p_read_info)
{
   SPIDEVICE_HANDLE hSpi;
   int result = SPI_SUCCESS;
   int device_idx = -1;
   SpiDeviceInfoType spi_info;
   SpiDataAddrType readBuf;

   do
   {
      /* Check for valid input parameters */
      if (((uint32)device_id >= SPI_MAX_NUM_DEVICES) ||
          (p_config == NULL) ||
          (p_read_info == NULL))
      {
         SPIDEVICE_LOG(ERROR, "spi_read() invalid input parameters");
         result = SPI_ERROR_INVALID_PARAM;
         break;
      }

      if ((device_idx = map_id_2_arr_idx(device_id)) < 0) {
         SPIDEVICE_LOG(ERROR, "spi_read() invalid device_id: %08x", device_id);
         return SPI_ERROR_DEVICE_UNAVAILABLE;
      }

      /* Check the device is open for writing */
      if (!(spiDevices[device_idx].status & SPI_DEVICE_OPEN))
      {
         SPIDEVICE_LOG(ERROR, "spi_read() SPI device not open");
         result = SPI_ERROR_DEVICE_NOT_OPEN;
         break;
      }

      /*Set SPI config*/
      set_spi_device_params(p_config, &spi_info);

      /*Set up SPI buffers*/
      readBuf.virtualAddr = p_read_info->buf_virt_addr;
      readBuf.physicalAddr = p_read_info->buf_phys_addr;

      hSpi = spiDevices[device_idx].hSpiDev;

      //vin - so we dont really populate p_read_info->total_bytes (this should hold resulting bytes read
      result = SpiDevice_WriteRead(hSpi, &spi_info, &readBuf, p_read_info->buf_len, NULL, 0);

      if (result != SPI_SUCCESS)
      {
         SPIDEVICE_LOG(ERROR, "spi_read() error: %08x", result);
         break;
      }
   }
   while (0);

   return result;
}

/* @copydoc spi_write */
int32 spi_write(spi_device_id_t device_id, const spi_config_t *p_config, spi_transaction_t *p_write_info)
{
   SPIDEVICE_HANDLE hSpi;
   int32 result = SPI_SUCCESS;
   int device_idx = -1;
   SpiDeviceInfoType spi_info;
   SpiDataAddrType writeBuf;

   /* Check for valid input parameters */
   if (((uint32)device_id >= SPI_MAX_NUM_DEVICES) ||
       (p_config == NULL) ||
       (p_write_info == NULL))
   {
      SPIDEVICE_LOG(ERROR, "spi_write() invalid input parameters");
      return SPI_ERROR_INVALID_PARAM;
   }

   if ((device_idx = map_id_2_arr_idx(device_id)) < 0)
   {
      SPIDEVICE_LOG(ERROR, "spi_write() invalid device_id: %08x", device_id);
      return SPI_ERROR_DEVICE_UNAVAILABLE;
   }

   /* Check the device is open for writing */
   if (!(spiDevices[device_idx].status & SPI_DEVICE_OPEN))
   {
      SPIDEVICE_LOG(ERROR, "spi_write() SPI device not open");
      return SPI_ERROR_DEVICE_NOT_OPEN;
   }
   /*set SPI config*/
   set_spi_device_params(p_config, &spi_info);

   /*Set up SPI buffers*/
   writeBuf.virtualAddr = p_write_info->buf_virt_addr;
   writeBuf.physicalAddr = p_write_info->buf_phys_addr;

   hSpi = spiDevices[device_idx].hSpiDev;

   result = SpiDevice_WriteRead(hSpi, &spi_info, NULL, 0, &writeBuf, p_write_info->buf_len);

   if (result != SPI_SUCCESS)
   {
      SPIDEVICE_LOG(ERROR, "spi_write() init error: %08x", result);
   }

   return result;
}

int32 spi_full_duplex (spi_device_id_t device_id, const spi_config_t *p_config, spi_transaction_t *p_write_info, spi_transaction_t *p_read_info)
{
   SPIDEVICE_HANDLE hSpi;
   int32 result = SPI_SUCCESS;
   int device_idx = -1;
   SpiDeviceInfoType spi_info;
   SpiDataAddrType writeBuf;
   SpiDataAddrType readBuf;

   do
   {
      /* Check for valid input parameters */
      if (((uint32)device_id >= SPI_MAX_NUM_DEVICES) ||
          (p_config == NULL) ||
          (p_write_info == NULL) ||
          (p_read_info == NULL) ||
		  (p_read_info->buf_len == 0 && p_write_info->buf_len == 0) ||
		  (p_read_info->buf_virt_addr == 0 && p_write_info->buf_virt_addr == 0))
      {
         SPIDEVICE_LOG(ERROR, "spi_full_duplex() invalid input parameters");
         result = SPI_ERROR_INVALID_PARAM;
         break;
      }

      if ((device_idx = map_id_2_arr_idx(device_id)) < 0)
      {
         SPIDEVICE_LOG(ERROR, "spi_open() invalid device_id: %08x", device_id);
         result = SPI_ERROR_DEVICE_UNAVAILABLE;
         break;
      }

      /* Check the device is open for writing */
      if (!(spiDevices[device_idx].status & SPI_DEVICE_OPEN))
      {
         SPIDEVICE_LOG(ERROR, "spi_full_duplex() SPI device not open");
         result = SPI_ERROR_DEVICE_NOT_OPEN;
         break;
      }
      /*set SPI config*/
      set_spi_device_params(p_config, &spi_info);

      /*Set up SPI buffers*/
      writeBuf.virtualAddr = p_write_info->buf_virt_addr;
      writeBuf.physicalAddr = p_write_info->buf_phys_addr;
      readBuf.virtualAddr = p_read_info->buf_virt_addr;
      readBuf.physicalAddr = p_read_info->buf_phys_addr;

      hSpi = spiDevices[device_idx].hSpiDev;

      result = SpiDevice_WriteRead (hSpi, &spi_info, &readBuf, p_read_info->buf_len, &writeBuf, p_write_info->buf_len);

      if (result != SPI_SUCCESS)
      {
         SPIDEVICE_LOG(ERROR,"spi_full_duplex() error: %08x", result);
         break;
      }
      p_write_info->total_bytes = p_write_info->buf_len;
	  p_read_info->total_bytes = p_read_info->buf_len;
   }
   while (0);

   return result;
}

int32 spi_close(spi_device_id_t device_id)
{
   /* Close will attempt to clean up as much as possible. A failure in
    * one step will be recorded, but the other steps will also be
    * executed */
   int32 result = SPI_SUCCESS;
   int device_idx;
   SPIDEVICE_HANDLE hSpi;

   if (device_id >= SPI_MAX_NUM_DEVICES)
   {
      SPIDEVICE_LOG(ERROR, "spi_close() invalid device_id: %08x", device_id);
      return SPI_ERROR_INVALID_PARAM;
   }

   if ((device_idx = map_id_2_arr_idx(device_id)) < 0)
   {
      SPIDEVICE_LOG(ERROR, "spi_close() invalid device_id: %08x", device_id);
      return SPI_ERROR_DEVICE_UNAVAILABLE;
   }

   if (qurt_island_get_status() == 0)
   {
      SpiDeInit_DeviceInstance(device_id);
   }

   /* Close the device */
   if (SPI_DEVICE_OPEN & spiDevices[device_idx].status)
   {
      spiDevices[device_idx].status &= ~SPI_DEVICE_OPEN;
   }

   hSpi = spiDevices[device_idx].hSpiDev;

   if (hSpi != NULL)
   {
      result = SpiDevice_DeInit(hSpi);

      if (result != SPI_SUCCESS)
      {
         SPIDEVICE_LOG(ERROR,"spi_close() de-init error: %08x", result);
      }
   }
   spiDevices[device_idx].hSpiDev = NULL;
   return result;
}
