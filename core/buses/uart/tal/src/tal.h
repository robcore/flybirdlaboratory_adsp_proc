#ifndef __TAL_H__
#define __TAL_H__
/*==================================================================================================

FILE: tal.h

DESCRIPTION: This header file defines the API for the Target Abstraction Layer.  This is a
             shim layer between the UART DAL layer and the external services required by
             the UART DAL.  Strictly speaking, this layer is redundant since the various
             DAL implementations were intended to provide a consistent interface on all
             targets and all OSes.  However, in practice this goal has failed.  DAL has not
             been implemented on all OSes and there have been differences in the DAL APIs
             between OSes.  This layer is intended to insulate the UART DAL layer from these
             issues.  A "stock" implementation of this layer will be defined that assumes
             all DAL APIs are present and consistent.  On targets and OSes where this
             assumption is false this layer will be customized as necessary.

                            Copyright (c) 2012-2013 Qualcomm Technologies Incorporated
                                        All Rights Reserved
                                     QUALCOMM Proprietary/GTDR

==================================================================================================*/
/*==================================================================================================

$Header: //components/rel/core.adsp/2.6.1/buses/uart/tal/src/tal.h#1 $

==================================================================================================*/
/*==================================================================================================
                                           INCLUDE FILES
==================================================================================================*/
#if ( !defined(_WIN32) )
#include "comdef.h"
#endif
/*==================================================================================================
                                             CONSTANTS
==================================================================================================*/

#define TAL_SUCCESS  0  // no error
#define TAL_ERROR   -1  // general failure

/*==================================================================================================
                                               MACROS
==================================================================================================*/

#define TAL_GPIO_FUNCTION(config)  (((config) & 0x00000F) >>  0)
#define TAL_GPIO_NUMBER(config)    (((config) & 0x003FF0) >>  4)
#define TAL_GPIO_DIRECTION(config) (((config) & 0x004000) >> 14)
#define TAL_GPIO_PULL(config)      (((config) & 0x018000) >> 15)
#define TAL_GPIO_DRIVE(config)     (((config) & 0x1E0000) >> 17)

/*==================================================================================================
                                              TYPEDEFS
==================================================================================================*/

typedef int TAL_RESULT;
typedef struct tal_clock_context     *TAL_CLOCK_HANDLE;
typedef struct tal_dma_context       *TAL_DMA_HANDLE;
typedef struct tal_interrupt_context *TAL_INTERRUPT_HANDLE;
typedef struct tal_tlmm_context      *TAL_TLMM_HANDLE;

typedef void (*TAL_DMA_CALLBACK)(void *);

typedef struct
{
   uint32            client_id;    // DAL ID of the DMA client
   uint32            rx_fifo;      // RX FIFO physical address
   uint32            tx_fifo;      // TX FIFO physical address
   uint32            burst_size;   // number of bytes in DMA burst
   TAL_DMA_CALLBACK  rx_callback;  // callback function for RX DMA events
   TAL_DMA_CALLBACK  tx_callback;  // callback function for TX DMA events
   void *            cb_context;   // context to pass to callbacks
} TAL_DMA_CONFIG;

typedef struct
{
   uint32   physical_address;
   uint32   bytes_to_transfer;
   uint32   bytes_transferred;
   boolean  error;
   boolean  transfer_complete;
} TAL_DMA_DESCRIPTOR;

typedef enum
{
   TAL_INTERRUPT_TYPE_INVALID,
   TAL_INTERRUPT_TYPE_IRQ,
   TAL_INTERRUPT_TYPE_GPIO,
} TAL_INTERRUPT_TYPE;

typedef struct
{
   TAL_INTERRUPT_TYPE type;
   union
   {
      uint32 irq_num;
      uint32 gpio_num;
   } u;
} TAL_INTERRUPT_ID;

typedef enum
{
   TAL_INTERRUPT_TRIGGER_HIGH,
   TAL_INTERRUPT_TRIGGER_LOW,
   TAL_INTERRUPT_TRIGGER_RISING,
   TAL_INTERRUPT_TRIGGER_FALLING,
} TAL_INTERRUPT_TRIGGER;

typedef void * (*TAL_INTERRUPT_ISR)(void *);

/*==================================================================================================
                                        FUNCTION PROTOTYPES
==================================================================================================*/

void       tal_clock_close        (TAL_CLOCK_HANDLE handle);
TAL_RESULT tal_clock_disable      (TAL_CLOCK_HANDLE handle);
TAL_RESULT tal_clock_enable       (TAL_CLOCK_HANDLE handle);
TAL_RESULT tal_clock_open         (TAL_CLOCK_HANDLE *handle_ptr, uint32 client_id);
TAL_RESULT tal_clock_set_frequency(TAL_CLOCK_HANDLE handle, uint32 input_freq);

void       tal_dma_close      (TAL_DMA_HANDLE handle);
TAL_RESULT tal_dma_open       (TAL_DMA_HANDLE *phandle, TAL_DMA_CONFIG *config);
TAL_RESULT tal_dma_rx_cancel  (TAL_DMA_HANDLE handle);
TAL_RESULT tal_dma_rx_transfer(TAL_DMA_HANDLE handle, TAL_DMA_DESCRIPTOR *descriptor);
TAL_RESULT tal_dma_tx_cancel  (TAL_DMA_HANDLE handle);
TAL_RESULT tal_dma_tx_transfer(TAL_DMA_HANDLE handle, TAL_DMA_DESCRIPTOR *descriptor);

void       tal_interrupt_close     (TAL_INTERRUPT_HANDLE handle);
TAL_RESULT tal_interrupt_done      (TAL_INTERRUPT_HANDLE handle, TAL_INTERRUPT_ID *tal_int_id);
TAL_RESULT tal_interrupt_open      (TAL_INTERRUPT_HANDLE *phandle, uint32 client_id);
TAL_RESULT tal_interrupt_register  (TAL_INTERRUPT_HANDLE handle, TAL_INTERRUPT_ID *tal_int_id,
                                    TAL_INTERRUPT_TRIGGER trigger, TAL_INTERRUPT_ISR isr,
                                    void *context);
TAL_RESULT tal_interrupt_trigger   (TAL_INTERRUPT_HANDLE handle, TAL_INTERRUPT_ID *tal_int_id);
TAL_RESULT tal_interrupt_unregister(TAL_INTERRUPT_HANDLE handle, TAL_INTERRUPT_ID *tal_int_id,
                                    TAL_INTERRUPT_ISR isr);

void       tal_tlmm_close       (TAL_TLMM_HANDLE handle);
TAL_RESULT tal_tlmm_gpio_disable(TAL_TLMM_HANDLE handle, uint32 *gpio_group, uint32 num_gpios);
TAL_RESULT tal_tlmm_gpio_enable (TAL_TLMM_HANDLE handle, uint32 *gpio_group, uint32 num_gpios);
TAL_RESULT tal_tlmm_open        (TAL_TLMM_HANDLE *phandle, uint32 client_id);

#endif  // __TAL_H__
