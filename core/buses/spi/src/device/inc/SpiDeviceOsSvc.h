#ifndef _SPIDEVICEOSSVC_H_
#define _SPIDEVICEOSSVC_H_
/*
===========================================================================

FILE:   SpiDeviceOs.h

DESCRIPTION:
    This file contains the API for the QUP OS Services 
    Interface: IQupSpiDevice 

===========================================================================

        Edit History

$Header: //components/rel/core.adsp/2.6.1/buses/spi/src/device/inc/SpiDeviceOsSvc.h#2 $

When     Who    What, where, why
-------- ---    -----------------------------------------------------------
05/15/13 ag     Created

===========================================================================
        Copyright c 2013 Qualcomm Technologies Incorporated.
            All Rights Reserved.
            Qualcomm Proprietary/GTDR

===========================================================================
*/
#include "SpiDriver.h"
/**
   Some of the most common errors may be defined here.
   Each OS defines its own values which will be interpreted
   differently based on OS.
 */
typedef enum {
   SPIDEVICEOSSVC_ERROR_TIMEOUT = SPI_ERROR_CLS_OS,
   SPIDEVICEOSSVC_ERROR_EVT_CREATE_FAILED,
   SPIDEVICEOSSVC_ERROR_EVT_DESTROY_FAILED,
   SPIDEVICEOSSVC_ERROR_MEM_FREE_FAILED,
   SPIDEVICEOSSVC_ERROR_MEM_MALLOC_FAILED,
   SPIDEVICEOSSVC_ERROR_EVT_CLEAR_FAILED,
   SPIDEVICEOSSVC_ERROR_EVT_CTRL_FAILED,
   SPIDEVICEOSSVC_ERROR_EVT_WAIT_FAILED,
   SPIDEVICEOSSVC_ERROR_SYNC_CREATE_FAILED,
   SPIDEVICEOSSVC_ERROR_SYNC_DESTROY_FAILED,
   SPIDEVICEOSSVC_ERROR_INVALID_HANDLE_TYPE,
   SPIDEVICEOSSVC_ERROR_NULL_PTR,
   SPIDEVICEOSSVC_ERROR_REGISTER_IST,
} SpiDeviceOsSvc_Result;

typedef void* SPIDEVICEOSSVC_EVENT_HANDLE;

typedef void* SPIDEVICEOSSVC_CRITSECTION_HANDLE;

typedef uint32 (*IST_HOOK)(void *pdata);
typedef uint32 (*ISR_HOOK)(void *pdata);

/** @brief Creates an event object and sets handle pointer.

    @param[out] pEventHandle  Pointer to event handle.
    @return          SpiDeviceOsSvc_Result .
  */
SpiDeviceOsSvc_Result
SpiDeviceOsSvc_CreateEvent(SPIDEVICEOSSVC_EVENT_HANDLE *pEventHandle);

/** @brief Closes a handle destroying the object associated with it.

    @param[in] hEvent  Event handle.
    @return          SpiDeviceOsSvc_Result .
  */
SpiDeviceOsSvc_Result
SpiDeviceOsSvc_CloseHandle(SPIDEVICEOSSVC_EVENT_HANDLE hEvent);

/** @brief Signals the event object pointed to by the handle.

    @param[in] hEvent  Event handle.
    @return          SpiDeviceOsSvc_Result .
  */
SpiDeviceOsSvc_Result
SpiDeviceOsSvc_SetEvent(SPIDEVICEOSSVC_EVENT_HANDLE hEvent);

/** @brief Clears outstanding signals on the event object.

    @param[in] hEvent  Event handle.
    @return          SpiDeviceOsSvc_Result .
  */
SpiDeviceOsSvc_Result
SpiDeviceOsSvc_ClearEvent(SPIDEVICEOSSVC_EVENT_HANDLE hEvent);

/** @brief Wait with a timeout on the event object.

    @param[in] hEvent  Event handle.
    @param[in] dwMilliseconds  Event wait timeout.
    @return          SpiDeviceOsSvc_Result .
  */
SpiDeviceOsSvc_Result
SpiDeviceOsSvc_Wait(SPIDEVICEOSSVC_EVENT_HANDLE hEvent, uint32 dwMilliseconds);

/** @brief Creates a critical section object and sets the handle pointer.

    @param[out] pCritSecHandle  Pointer to critical section handle.
    @return          SpiDeviceOsSvc_Result .
  */
SpiDeviceOsSvc_Result
SpiDeviceOsSvc_CreateCriticalSection(SPIDEVICEOSSVC_CRITSECTION_HANDLE *pCritSecHandle);

/** @brief Enters the critical section.

    @param[in] hCriticalSection  Critical section handle handle.
    @return          SpiDeviceOsSvc_Result .
  */
SpiDeviceOsSvc_Result
SpiDeviceOsSvc_EnterCriticalSection(SPIDEVICEOSSVC_CRITSECTION_HANDLE hCriticalSection);

/** @brief Leaves the critical section.

    @param[in] hCriticalSection  Critical section handle handle.
    @return          SpiDeviceOsSvc_Result .
  */
SpiDeviceOsSvc_Result
SpiDeviceOsSvc_LeaveCriticalSection(SPIDEVICEOSSVC_CRITSECTION_HANDLE hCriticalSection);
SpiDeviceOsSvc_Result
SpiDeviceOsSvc_RegisterISTHooks(uint32 uDevId, ISR_HOOK IsrHook, void* pIsrData, IST_HOOK IstHook, void* pIstData);

/** @brief Unregisters IST/ISR hooks for the indicated device.

    @param[in] uDevId   Device index.
  @return          SpiDeviceOsSvc_Result .
  */
SpiDeviceOsSvc_Result
SpiDeviceOsSvc_UnRegisterISTHooks(uint32 uDevId);

/** @brief Busy waits the uTimeMicrosec microseconds before returning.

  @return          Nothing.
  */
void
SpiDeviceOsSvc_BusyWait(uint32 uTimeMicrosec);
#endif // _SPIDEVICEOSSVC_H_
