#ifndef __SPI_DEFS_H__
#define __SPI_DEFS_H__
/**
  @file spi_defs.h 
  @brief 
  This file contains definitions common betwee DAL1 and DAL0.
*/ 

/*===========================================================================

FILE:   spi_defs.h

DESCRIPTION:
    This file contains DAL interface declaration for SPI device driver, 

===========================================================================

        Edit History

$Header: 

When     Who    What, where, why
-------- ---    -----------------------------------------------------------
06/06/12 dk	Added minor review comments.
03/27/12 ag	Added batch transfer updates.
06/05/11 ag	Doxygen Markups.

===========================================================================
        Copyright (c) 2010-2014 Qualcomm Technologies Incorporated.
            All Rights Reserved.
            Qualcomm Proprietary/GTDR

===========================================================================*/

#include "comdef.h"
#include "spi_errors.h"

typedef enum 
{
   SPI_CLK_NORMAL, /**< Turns off SPI CLK during idle state.*/
   SPI_CLK_ALWAYS_ON, /**< Runs SPI CLK during idle state.*/
   SPI_CLK_INVALID = 0x7FFFFFFF
}SpiClockModeType;
 /** 
@} 
*/

/**
@addtogroup spi_dal_enum
@{ */
/**
 In the idle state whether the SPI clk is high or low. 
*/ 
typedef enum 
{
   SPI_CLK_IDLE_LOW,/**< CLK signal is low when idle.*/
   SPI_CLK_IDLE_HIGH,/**< CLK signal is high when idle.*/
   SPI_CLK_IDLE_INVALID = 0x7FFFFFFF
}SpiClockPolarityType;
 /** 
@} 
*/

/**
@addtogroup spi_dal_enum
@{ */
/**
Shift mode, detemines which signal (input or output) is sampled first.
*/ 
typedef enum SpiShiftModeType
{
   SPI_INPUT_FIRST_MODE,/**< In both Master and slave input Bit is shifted in first.*/
   SPI_OUTPUT_FIRST_MODE,/**< In both Master and slave  output Bit is shifted in first*/
   SPI_SHIFT_INVALID = 0x7FFFFFFF
}SpiShiftModeType;
 /** 
@} 
*/

/**
@addtogroup spi_dal_enum
@{ */
/**
 In idle state whether the Chip Select is high or low.
*/ 
typedef enum 
{
   SPI_CS_ACTIVE_LOW,/**< During idle state CS  line is held low*/
   SPI_CS_ACTIVE_HIGH,/**< During idle state CS line is held high*/
   SPI_CS_ACTIVE_INVALID = 0x7FFFFFFF
}SpiCSPolarityType;
 /** 
@} 
*/

/**
@addtogroup spi_dal_enum
@{ */
/**
 List of values that inidicates, whether the Chip select is always active or if it's brought back to its idle state
 after N clock cycles.
*/ 
typedef enum 
{
   SPI_CS_DEASSERT,/**< CS is deasserted after transferring data for N clock cycles*/
   SPI_CS_KEEP_ASSERTED,/**< CS is asserted as long as the core is in Run state*/
   SPI_CS_MODE_INVALID = 0x7FFFFFFF
}SpiCSModeType;

/**
@addtogroup spi_dal_data_structures 
@{ */
/**
 Data structure that contains information regarding the SPI device settings.
*/ 
typedef struct SpiDeviceParametersType
{
   /* This parameter determines if the Clock could be running even if there is
    * no ongoing transfer */
   SpiClockModeType eClockMode;/**< Clock mode type to be used for the SPI core.*/
   SpiClockPolarityType eClockPolarity;/**< Clock polarity  type to be used for the SPI core.*/
   
   /* This parameter specifies whether the SPI core operates in OUTPUT
    * or INPUT FIRST Mode. This specifies whether the shift register
    * latches the DATA at the input pin on the rising or falling edge */
   SpiShiftModeType eShiftMode;/**< Shift mode type to be used for SPI core.*/
   
   /* This sets the minimum time in nanoseconds that the
    * chip select is deasserted between SPI transfers (in master mode). 
    *
    * The deassertion clock ticks will be configured so that the
    * deassertion time will be as close as possible to, but not less than,
    * the time specified by this parameter.
    *
    */
   uint32 u32DeassertionTime;/**< The minimum time delay in nano second, between two word(N-bits) transfers.*/

   /* These are the minimum and maximum frequencies (in Hz) at which the slave can shift data in/out.
    * 
    * The driver will select a clock frequency that is equal to or less than nMaxSlaveFrequency
    * depending on the frequencies available in the clkregim SPI clock steps configuration.
    */
   uint32 u32MinSlaveFrequencyHz;/**< The Minmum frequency above which the spi core should be run. 
								   Normally this is set to zero.*/
   uint32 u32MaxSlaveFrequencyHz;/**< This is desired frequency of operation. If the core cannot run 
								   at this frequency, a value below this but greater than 
								   u32MinSlaveFrequencyHz will be chosen.*/

   /* This field tells whethere the Chip select is active high or active low */
   SpiCSPolarityType eCSPolarity;/**< CS polarity type to be used for the SPI core.*/

   /* This specifies whether the Chip select is asserted through the 
    * entire Transaction or whether it is deasserted in between SPI 
    * transfers of each transaction */ 
   SpiCSModeType eCSMode;/**< CS Mode to be used for the SPI core.*/
  
}SpiDeviceParametersType;

/**
@addtogroup spi_dal_enum
@{ */
/**
	LIST of settings for LOOBBACK MODE.
*/ 
typedef enum SpiLoopbackModeType
{
   SPI_LOOPBACK_DISABLED,/**< The loopback mode is disabled.*/
   SPI_LOOPBACK_ENABLED,/**< The loopback mode is enabled.*/
} SpiLoopbackModeType;

/**
@addtogroup spi_dal_enum
@{ */
/**
 LIST of different SPI input packing types.
*/ 
typedef enum 
{
   SPI_INPUT_PACKING_DISABLED,/**< Packing  is disabled in the INPUT FIFO.*/
   SPI_INPUT_PACKING_ENABLED  /**< Packing  is enabled in the INPUT FIFO.*/
}SpiInputPackingType;

/**
@addtogroup spi_dal_enum
@{ */
/**
 LIST of different SPI output unpacking types.
*/ 
typedef enum 
{
   SPI_OUTPUT_UNPACKING_DISABLED,/**< Unpacking is disabled in the OUTPUT FIFO*/
   SPI_OUTPUT_UNPACKING_ENABLED,/**< Unpacking is enabled in the OUTPUT FIFO*/
   SPI_PACKING_INVALID = 0x7fffffff
}SpiOutputUnpackingType;

/**
@addtogroup spi_dal_enum
@{ */
/**
 List of different SPI transfer Modes
*/ 
typedef enum SpiTransferModeType
{
   SPI_TRANSFER_MODE_DEFAULT,/**< Let the SPI DAL driver chose the transfer mode. 
							   If the transfer length is greater than one block size, 
							   DATA MOVER mode is used, otherwise  BLOCK mode is used.*/
   SPI_TRANSFER_MODE_FIFO,/**< FIFO mode is not supported.`*/
   SPI_TRANSFER_MODE_BLOCK,/**< BLOCK mode is used for data transfer.*/
   SPI_TRANSFER_MODE_DATA_MOVER,/**< DATA MOVER mode is used for data transfer.*/
   SPI_TRANSFER_MODE_INVALID = 0x7fffffff
} SpiTransferModeType;

/**
@addtogroup spi_dal_data_structures 
@{ */
/**
 Data stucture that holds different parameters that can be used for SPI transfer.
*/ 
typedef struct SpiTransferParametersType
{
   uint32 nNumBits;/**< Specifies the number bits (N) in one logical SPI transfer.*/
   SpiTransferModeType eTransferMode;/**< Specify which transfer mode to use.*/
   SpiLoopbackModeType eLoopbackMode;/**< Specifies whether loopback mode is enabled or disabled.*/
   SpiInputPackingType eInputPacking;/**< Specifies whether input packing is enabled or disabled.*/
   SpiOutputUnpackingType eOutputUnpacking;/**< Specifies whether output unpacking is enabled or disabled.*/
   uint32 slaveTimeoutUs;/**< Slave timeout in micro-seconds. Ignored by the master.*/
}SpiTransferParametersType;
/**
@addtogroup spi_dal_data_structures 
@{ */
/**
 Data structure that holdes information regarding the SPI device.
*/ 
typedef struct SpiDeviceInfoType
{
   SpiDeviceParametersType deviceParameters;/**< Specifies the device parameters to be used for the SPI core.*/
   uint32 nSlaveNumber;
   SpiTransferParametersType transferParameters;/**< Specfies the transfer parameters to be used for a SPI transfer.*/
}SpiDeviceInfoType;
/**
@addtogroup spi_dal_data_structures 
@{ */
/**
 Data structure to hold the physical and virtual address of the data buffers, 
 which are used for SPI transfers
*/ 
typedef struct SpiDataAddrType
{
  void* virtualAddr;/**< The virtual address of the data buffer.*/
  void* physicalAddr;/**< The physical address of the data buffer.*/
}SpiDataAddrType;

#endif /* __SPI_DEFS_H__ */
