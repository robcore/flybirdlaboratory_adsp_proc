#ifndef __DALUART_H__
#define __DALUART_H__
/*==================================================================================================

FILE: DalUart.h

DESCRIPTION: UART DAL (OS-independent layer)

                           Copyright (c) 2009-2013 Qualcomm Technologies Incorporated
                                        All Rights Reserved
                                     QUALCOMM Proprietary/GTDR

==================================================================================================*/
/*==================================================================================================

$Header: //components/rel/core.adsp/2.6.1/buses/uart/dal/src/DalUart.h#1 $

==================================================================================================*/
/*==================================================================================================
                                           INCLUDE FILES
==================================================================================================*/

#if ( defined(_WIN32) && !defined(_WIN32_WCE) )
#include "dal.h"
#else
#include "comdef.h"
#include "DALFramework.h"
#include "DALSysTypes.h"
#endif

#include "tal.h"
#include "DDIUart.h"
#include "HALuart.h"

/*==================================================================================================
                                             CONSTANTS
==================================================================================================*/

#define STALE_DEFAULT  0x04  // characters (10 x bit time) until stale timeout

#define TX_BUF_SIZE    4096  // size of the TX buffer
                             // must be less than 65535 due to DMOV limitations

#define RX_BUF_SIZE    4096  // size of each RX buffer
                             // must be at least as large as RXFIFO due to UART HW bug that
                             // disallows writing a value to DMRX that is less than the number
                             // of bytes presently in RXFIFO

#define RX_BUF_CNT        4  // number of RX buffers - must be a power of 2

#define RXLEV_MARGIN     16  // number of empty bytes remaining in RXFIFO when an RXLEV interrupt
                             // fires (must be a multiple of 4)

#define TXLEV_MARGIN     16  // number of full bytes remaining in TXFIFO when a TXLEV interrupt
                             // fires (must be a multiple of 4)

#define AUTORFR_MARGIN    4  // number of empty bytes remaining in RXFIFO when we automatically
                             // deassert RTS (must be a multiple of 4 and less than RXLEV_MARGIN)

#define DMA_BURST_SIZE   16  // do not change; this is hard-wired to 16 in DMOV UARTs but
                             // configurable in BAM UARTs; we will use the same value for both

/*==================================================================================================
                                              TYPEDEFS
==================================================================================================*/

typedef struct
{
   DALSYSMemHandle  data_handle;   // buffer (uncached in DMA mode) that contains RX data
   TAL_DMA_DESCRIPTOR  descriptor;    // buffer descriptor used for DMA operations
   uint32           read_offset;   // offset of next byte to read
   uint32           write_offset;  // offset of next byte to write
} MSM_UART_RX_BUF;

typedef struct
{
   TAL_INTERRUPT_HANDLE interrupt_handle;    // handle used for TAL interrupt operations
   TAL_TLMM_HANDLE      tlmm_handle;         // handle to TLMM device
   TAL_CLOCK_HANDLE     clock_handle;        // handle used for clock operations
   DALSYSSyncHandle     register_sync;       // protects UART Registers (enforces atomic access)
   DALSYSEventHandle    line_event;          // used for callback to client line event handler
   uint32               uart_physical;       // (from XML props) UART physical base address
   uint32               gsbi_physical;       // (from XML props) GSBI physical base address
   uint32               gpio_rfrn;           // (from XML props) GPIO configuration for RTS
   uint32               gpio_ctsn;           // (from XML props) GPIO configuration for CTS
   uint32               gpio_rx_data;        // (from XML props) GPIO configuration for RX DATA
   uint32               gpio_tx_data;        // (from XML props) GPIO configuration for TX DATA
   uint32               gsbi_control;        // (from XML props) GSBI control register
   uint32               detect_break;        // (from XML props) whether to detect RX break
   uint32               is_cxm;              // (from XML props) whether UART supports coexistence
   DALSYSMemHandle      uart_mem_handle;     // contains virtual address mapping for UART block
   DALSYSMemHandle      gsbi_mem_handle;     // contains virtual address mapping for GSBI block
   uint32               baud_rate;           // current HW baud rate
   UartRtsControlType   rts_control;         // client-specified inbound HW flow control setting
   boolean              clock_on;            // indicates whether the input clock is enabled
   UartPowerType        power_state;         // power state of the driver
   DALDEVICEID          dal_id;              // UART DAL device identifier
   HALUartObject        uart_hal;            // UART HAL object
   TAL_INTERRUPT_ID     uart_irq;            // TAL_INTERRUPT_ID for UART generated events
   TAL_INTERRUPT_ID     rx_irq;              // TAL_INTERRUPT_ID for the raw RX signal
   boolean              uart_isr_registered;        // flag to track ISR registration
   boolean              rx_falling_isr_registered;  // flag to track ISR registration
   boolean              rx_rising_isr_registered;   // flag to track ISR registration
   boolean              break_notified;      // last break notification was a break start
   HALUartType          uart_type;           // specifies the UART type (legacy/DM/BAM)
   boolean              use_dma;             // whether to use DMA transfers to/from FIFOs
   void                 *dma_ctxt;           // DMA context (opaque pointer)

   DALSYSSyncHandle     tx_sync;             // protects transmit operations
   DALSYSEventHandle    tx_event;            // used for callback to client tx event handler
   DALSYSEventHandle    tx_idle_event;       // used to indicate IST has exited TX path
   uint32               tx_fifo_size;        // size of TXFIFO (in bytes)
   DALSYSMemHandle      tx_handle;           // buffer (uncached in DMA mode) that contains TX data
   TAL_DMA_DESCRIPTOR   tx_descriptor;       // buffer descriptor used for DMA operations
   const uint8          *tx_ptr;             // pointer to unsent data in TX buffer
   uint32               tx_bytes_left;       // unsent bytes remaining in TX buffer
   boolean              tx_in_progress;      // flag to indicate TX transaction is in progress
   boolean              tx_halt;             // flag used to halt a TX transfer in progress
   boolean              tx_wait;             // flag used to wait for a TX transfer to complete
   boolean              tx_dma_flag;         // flag to indicate TX DMA callback occurred

   DALSYSSyncHandle     rx_sync;             // protects receive operations
   DALSYSEventHandle    rx_event;            // used for callback to client rx event handler
   DALSYSEventHandle    rx_idle_event;       // used to indicate IST has exited RX path
   uint32               rx_fifo_size;        // size of RXFIFO (in bytes)
   MSM_UART_RX_BUF      rx_buf[RX_BUF_CNT];  // array of buffers to hold incoming data until read
   uint32               rx_head;             // index of next RX buffer to be written
   uint32               rx_tail;             // index of next RX buffer to be read
   uint32               rx_out_of_buffers;   // no RX buffer is available for writing
   uint32               rx_watermark;        // current RX watermark (expressed in bytes)
   uint32               rx_xfer_size;        // number of bytes in current RX transfer
   uint32               rx_overruns;         // count of RXFIFO overrun events detected
   uint32               rx_cached_status;    // cached RX status (overrun/parity/framing/break)
   boolean              rx_activated;        // the first RX transfer has been activated
   boolean              rx_halt;             // flag used to halt an RX transfer in progress
   boolean              rx_dma_flag;         // flag to indicate RX DMA callback occurred
} UART_CONTEXT;

/*==================================================================================================
                                        FUNCTION PROTOTYPES
==================================================================================================*/

DALResult Uart_DeviceInit        (DalDeviceHandle *);
DALResult Uart_DeviceDeInit      (DalDeviceHandle *);
DALResult Uart_Open              (DalDeviceHandle *, uint32);
DALResult Uart_Close             (DalDeviceHandle *);
DALResult Uart_Info              (DalDeviceHandle *, DalDeviceInfo *, uint32);
DALResult Uart_PowerEvent        (DalDeviceHandle *, DalPowerCmd, DalPowerDomain);

DALResult Uart_PostInit          (DalDeviceHandle *, UartInitConfig *);
DALResult Uart_OpenEx            (DalDeviceHandle *, UartOpenConfig *);
DALResult Uart_Read              (DalDeviceHandle *, uint8 *, uint32, uint32 *, uint32 *);
DALResult Uart_Write             (DalDeviceHandle *, const uint8 *, uint32, uint32 *);
DALResult Uart_SetRate           (DalDeviceHandle *, uint32);
DALResult Uart_SetCharFormat     (DalDeviceHandle *, UartCharFormat *);
DALResult Uart_PurgeTx           (DalDeviceHandle *);
DALResult Uart_PurgeRx           (DalDeviceHandle *);
DALResult Uart_SetBreak          (DalDeviceHandle *);
DALResult Uart_ClearBreak        (DalDeviceHandle *);
DALResult Uart_TxSingleChar      (DalDeviceHandle *, uint8);
DALResult Uart_GetStatus         (DalDeviceHandle *, uint32 *);
DALResult Uart_TxComplete        (DalDeviceHandle *, uint32 *);
DALResult Uart_SetRtsControl     (DalDeviceHandle *, UartRtsControlType);
DALResult Uart_SetCtsControl     (DalDeviceHandle *, UartCtsControlType);
DALResult Uart_GetCTS            (DalDeviceHandle *, uint32 *);
DALResult Uart_PowerCapabilities (DalDeviceHandle *, uint32 *);
DALResult Uart_PowerGet          (DalDeviceHandle *, UartPowerType *);
DALResult Uart_PowerSet          (DalDeviceHandle *, UartPowerType);
DALResult Uart_LoopbackSet       (DalDeviceHandle *, uint32);
DALResult Uart_SetCxm            (DalDeviceHandle *, uint32, uint32);
DALResult Uart_DumpRegs          (DalDeviceHandle *);
DALResult Uart_GetCxmTxSticky    (DalDeviceHandle *, uint32 *, uint32);
DALResult Uart_CxmTxDirectChar   (DalDeviceHandle *, uint8);

#endif  // __DALUART_H__
