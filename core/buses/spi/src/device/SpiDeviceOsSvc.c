/*
===========================================================================

FILE:   SpiDeviceOsSvc.c

DESCRIPTION:
    This file contains the implementation for the QUP OS Services 
    Interface: IQupSpiDevice 

===========================================================================

        Edit History

$Header: //components/rel/core.adsp/2.6.1/buses/spi/src/device/SpiDeviceOsSvc.c#3 $

When     Who    What, where, why
-------- ---    -----------------------------------------------------------
05/15/13 ag Created

===========================================================================
        Copyright c 2013 Qualcomm Technologies Incorporated.
            All Rights Reserved.
            Qualcomm Proprietary/GTDR

===========================================================================
*/

#include "SpiDeviceOsSvc.h"
#include "DALStdDef.h"
#include "DALDeviceId.h"
#include "DALSys.h"
#include "busywait.h"


typedef enum SpiDeviceOs_HandleType
{
   SpiDeviceOs_EventHandleType,
   SpiDeviceOs_CritSecHandleType,
} SpiDeviceOs_HandleType;

typedef struct SpiDeviceOs_EventHandle
{
   SpiDeviceOs_HandleType    hType;
   DALSYSEventHandle      hQupEvents[2];
   DALSYSEventObj         aQupEventObj[2];

} SpiDeviceOs_EventHandle;

typedef struct SpiDeviceOs_SyncHandle
{
   SpiDeviceOs_HandleType    hType;
   DALSYSSyncHandle  hDeviceSynchronization;
   DALSYS_SYNC_OBJECT(DeviceSyncObject);

} SpiDeviceOs_SyncHandle;

typedef struct SpiDeviceOs_Handle
{
   SpiDeviceOs_HandleType    hType;
} SpiDeviceOs_Handle;

typedef struct SpiDeviceOs_IrqHandle
{
   ISR_HOOK IsrHook;
   IST_HOOK IstHook;
   void     *pIsrData;
   void     *pIstData;
   uint32   uInterruptId;
   uint32    uIrqTriggerCfg;
} SpiDeviceOs_IrqHandle;


SpiDeviceOsSvc_Result
SpiDeviceOsSvc_CreateEvent(SPIDEVICEOSSVC_EVENT_HANDLE *phEvt)
{
   return (SpiDeviceOsSvc_Result)SPI_SUCCESS;
}

SpiDeviceOsSvc_Result
SpiDeviceOsSvc_DestroyEvent(SpiDeviceOs_EventHandle *pEvt)
{
   return (SpiDeviceOsSvc_Result)SPI_SUCCESS;
}



SpiDeviceOsSvc_Result
SpiDeviceOsSvc_SetEvent(SPIDEVICEOSSVC_EVENT_HANDLE hEvent)
{
   return (SpiDeviceOsSvc_Result)SPI_SUCCESS;
}

SpiDeviceOsSvc_Result
SpiDeviceOsSvc_ClearEvent(SPIDEVICEOSSVC_EVENT_HANDLE hEvt)
{
   return (SpiDeviceOsSvc_Result)SPI_SUCCESS;
}


SpiDeviceOsSvc_Result
SpiDeviceOsSvc_CloseHandle(SPIDEVICEOSSVC_EVENT_HANDLE hEvt)
{
   return (SpiDeviceOsSvc_Result)SPI_SUCCESS;
}

void SpiDeviceOsSvc_BusyWait(uint32 uTimeMicrosec)
{
   busywait( uTimeMicrosec );
}

