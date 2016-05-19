/*
===========================================================================

FILE:   SpiDevice.c

DESCRIPTION:
    Device layer for SPI Bus Driver

===========================================================================

        Edit History

$Header: //components/rel/core.adsp/2.6.1/buses/spi/src/device/SpiDevice.c#3 $

When        Who    What, where, why
--------    --    -----------------------------------------------------------
05/06/2014  vmk   Created
===========================================================================
        Copyright c 2014 Qualcomm Technologies Incorporated.
            All Rights Reserved.
            Qualcomm Proprietary/GTDR
===========================================================================
*/

#include "SpiDriver.h"
#include "SpiDevice.h"
#include "SpiDeviceTransfer.h"
#include "SpiDevicePlatSvc.h"
#include "SpiDeviceOsSvc.h"
#include "HALqupe.h"
#include "SpiLog.h"

#define QUP_RUN_STATE_CHANGE_TIME_OUT_US         100
#define QUP_OP_STATE_READY_TIME_US               25
#define QUP_BUSY_WAIT_STEP_US                    5
#define QUP_BUSY_WAIT_POLL_STEP_US               1
#define QUP_BUSY_WAIT_POLL_MAX_US                10000

#define SPIDEVICE_MAX(a,b) ((a)>(b))?(a):(b)

enum SpiDevice_Error
{
   SPIDEVICE_ERR_BASE = SPI_ERROR_CLS_DEVICE,
   SPIDEVICE_ERR_INVALID_DEVICE_ID,
   SPIDEVICE_ERR_INVALID_PTR,
   SPIDEVICE_ERR_IN_SEQ_OUT_OF_SYNC,
   SPIDEVICE_ERR_INVALID_RUNSTATE,
   SPIDEVICE_ERR_RUNSTATE_CHANGE_TIMEOUT,
   SPIDEVICE_ERR_INVALID_POWER_STATE,
   SPIDEVICE_ERR_BUS_BUSY,
   SPIDEVICE_ERR_INVALID_DEV_HANDLE,
   SPIDEVICE_ERR_INVALID_BUFFER_POINTER,
   SPIDEVICE_ERR_INVALID_BUFFER_LEN,
   SPIDEVICE_ERR_INVALID_CONFIG_POINTER,
   SPIDEVICE_ERR_INVALID_TRAN_RESULT_POINTER,
   SPIDEVICE_ERR_INVALID_CALLBACK_FN_POINTER,
   SPIDEVICE_ERR_INVALID_CALLBACK_ARG_POINTER,
   SPIDEVICE_ERR_INVALID_NUM_BATCH_TRANSFER_VECS,
   SPIDEVICE_ERR_OPERATION_MODE_UNSUPPORTED,
   SPIDEVICE_ERR_NULL_PTR,
   SPIDEVICE_ERR_QUP_TIMEOUT,
   SPIDEVICE_ERR_CLOCK_SETTING_FAILED
};


#define SPIDEVICE_VALIDATE_WR_PARAMS(pDev,cfg, pReadBuffer, uReadBufLen, pWriteBuffer, uWriteBufLen )\
   {if(NULL == pDev) return SPIDEVICE_ERR_INVALID_DEV_HANDLE;\
    if(NULL == cfg) return SPIDEVICE_ERR_INVALID_CONFIG_POINTER;\
    if((NULL == pReadBuffer) && (NULL == pWriteBuffer)) return SPIDEVICE_ERR_INVALID_BUFFER_POINTER;\
    if((0 == uReadBufLen) && (0 == uWriteBufLen)) return SPIDEVICE_ERR_INVALID_BUFFER_LEN;}

#define SPIDEVICE_CHK_RESULT_BREAK(res) if ((res != SPI_SUCCESS)) break;

typedef enum SpiDevice_InitState
{
   SPIDEVICE_INITSTATE_UNINITIALIZED = 0x0,
   SPIDEVICE_INITSTATE_TARGETINIT_DONE = 0x1,
   SPIDEVICE_INITSTATE_EVENTS_DONE = 0x2,
   SPIDEVICE_INITSTATE_DEVICEINIT_DONE = 0x4,
   SPIDEVICE_INITSTATE_HARDWAREINIT_DONE = 0x8,
} SpiDevice_InitState;

typedef struct SpiDeviceClientConfig
{
   uint32 uBusFreqKhz;
   uint32 uByteTransferTimeoutUs;
} SpiDeviceClientConfig;

typedef struct SpiDevice_AsyncCallData
{
   SPI_DEV_ASYNC_CB pCallbackFn;
   SpiDevice_AsyncResult asyncResult;
} SpiDevice_AsyncCallData;

typedef struct SpiDevice_RegInfo
{
   uint32 uInFreeSlotReqCnt;
   uint32 uOutFreeSlotReqCnt;
   uint32 uQupErrors;
   uint32 uOperational;
   uint32 uInFreeSlotServicedCnt;
   uint32 uOutFreeSlotServicedCnt;
   uint32 uCurOutTransfers;
   uint32 uCurInTransfers;
   boolean uMaxInputDone;
   boolean uMaxOutputDone;
} SpiDevice_RegInfo;

typedef struct SpiDevice_DeviceCtxt
{
   uint32 uQupCoreNum;
   SpiDevicePlatInfoType platInfo;
   HAL_qupe_HwInfoType devHwInfo;
   char *pHalVer;
   SpiDevice_InitState devInitState;
   SpiDevice_RegInfo qupInfo;
   SPIDEVICEOSSVC_EVENT_HANDLE hQupEvt;
   SPIDEVICE_PLAT_HANDLE hDevTgt;
   SpiDeviceInfoType pClntCfg;
   SpiDevice_PowerStates devPowerState;
   SpiDevice_AsyncCallData asyncCall;
   SpiDeviceTransferType transferInfo;
   uint32 uPollXferComplete;
} SpiDevice_DeviceCtxt;

static SpiDevice_DeviceCtxt SpiDevCtxt[SPIPD_DEVICE_COUNT] ATTRIBUTE_ISLAND_DATA;

static uint32 QUP_ServiceQUP(SpiDevice_DeviceCtxt *pDev);
static uint32 QUP_PerformInputOutput(SpiDevice_DeviceCtxt *pDev);

static int32 SpiDevice_SetRunState(uint8 *pQupAddr, const HAL_qupe_RunStateType cRunState);

/** @brief Wait for state to go valid or timeout.
           
    @param[in] pQupAddr       QUP block address.
    @return           Returns timeout error if the previous state is invalid,
                      success otherwise.
  */

static int32 SpiDevice_WaitForRunStateValid(uint8 *pQupAddr)
{
   uint32 uWaitTimeUs = QUP_RUN_STATE_CHANGE_TIME_OUT_US;

   while ((!HAL_qupe_RunStateIsValid(pQupAddr)) && (0 != uWaitTimeUs))
   {
      SpiDeviceOsSvc_BusyWait(QUP_BUSY_WAIT_STEP_US);
      uWaitTimeUs -= QUP_BUSY_WAIT_STEP_US;
   }
   if (0 == uWaitTimeUs)
   {
      return SPIDEVICE_ERR_INVALID_RUNSTATE;
   }
   return SPI_SUCCESS;
}

uint32 SpiDevice_IstHook(void *pdata)
{
   if (NULL == pdata) return 0;
   return (QUP_PerformInputOutput((SpiDevice_DeviceCtxt *)pdata));
}

uint32  SpiDevice_IsrHook(void *pdata)
{
   if (NULL == pdata) return 0;
   return (QUP_ServiceQUP((SpiDevice_DeviceCtxt*)pdata));
}

int32 SpiDevice_InitHw(SpiDevice_DeviceCtxt *pDev)
{
   int32 res;

   HAL_qupe_Init((uint8 *)pDev->platInfo.qupVirtBlockAddr, &pDev->pHalVer);
   res = SpiDevice_WaitForRunStateValid((uint8 *)pDev->platInfo.qupVirtBlockAddr);

   if (SPI_SUCCESS != res)
   {
      SPIDEVICE_LOG(ERROR, "SpiDevice_InitHw: Invalid state after reset 0x%x\n", (unsigned int)res);
      return (int32)res;
   }

   HAL_qupe_GetHwInfo((uint8*)pDev->platInfo.qupVirtBlockAddr, &pDev->devHwInfo);

   HAL_qupe_SetSelectedMinicore((uint8 *)pDev->platInfo.qupVirtBlockAddr, HAL_QUPE_MINI_CORE_SPI);

   pDev->devInitState |= SPIDEVICE_INITSTATE_HARDWAREINIT_DONE;

   return SPI_SUCCESS;
}

static int32 get_free_device_idx(uint32 qup_core_num)
{
   uint32 i;
   for (i = 0; i < SPIPD_DEVICE_COUNT; i++)
   {
      if (SpiDevCtxt[i].devInitState == SPIDEVICE_INITSTATE_UNINITIALIZED)
      {
         SpiDevCtxt[i].uQupCoreNum = qup_core_num;
         return i;
      }
   }
   return -1;
}

/** @brief Initializes the device.

    This function initializes the device and creates the
    necessary data structures to support other calls into the
    device. This function may be called multiple times under 
    different conditions so what fails one time may succeed th
    next time.

    @param[in] uDevOsId    Device index.
    @param[in] phDev     Pointer to device handle.

    @return int32 - SPI_SUCCESS  on success, error
            code on error.
  */
int32 SpiDevice_Init(uint32 qup_core_num, SPIDEVICE_HANDLE *phDev)
{
   int32 res = SPI_SUCCESS, device_idx = 0;
   int32 return_value = SPI_SUCCESS;
   SpiDevice_DeviceCtxt *pDev;

   if (NULL == phDev)
   {
      SPIDEVICE_LOG(ERROR, "SpiDevice_Init: Null pointer passed \n");
      return SPIDEVICE_ERR_INVALID_DEV_HANDLE;
   }

   if ((device_idx = get_free_device_idx(qup_core_num)) < 0)
   {
      SPIDEVICE_LOG(ERROR, "SpiDevice_Init() invalid qup_core_num: %08x", qup_core_num);
      return SPIDEVICE_ERR_INVALID_DEVICE_ID;
   }
   pDev = &(SpiDevCtxt[device_idx]);

   do
   {
      res = (int32)SpiDevicePlat_InitTarget(qup_core_num, &pDev->hDevTgt);

      if (SPI_SUCCESS != res)
      {
         SPIDEVICE_LOG(ERROR, "SpiDevice_Init:SpiDevicePlat_InitTarget Failure err 0x%x\n", (unsigned int)res);
         break;
      }
      pDev->devInitState |= SPIDEVICE_INITSTATE_TARGETINIT_DONE;

      res = (int32)SpiDevicePlat_GetPlatformInfo(pDev->hDevTgt, &pDev->platInfo);

      if (SPI_SUCCESS != res)
      {
         SPIDEVICE_LOG(ERROR,
                       "SpiDevice_Init:SpiDevicePlat_GetPlatformInfo Failure err 0x%x\n",
                       (unsigned int)res);
         break;
      }

      if (pDev->platInfo.bInterruptBased)
      {
         res = (int32)SpiDeviceOsSvc_CreateEvent(&pDev->hQupEvt);
         if (SPI_SUCCESS != res)
         {
            break;
         }
      }

      if (SPI_SUCCESS != res)
      {
         SPIDEVICE_LOG(ERROR,
                       "SpiDevice_Init: SpiDeviceOsSvc_CreateEvent Failure err 0x%x\n",
                       (unsigned int)res);
         break;
      }

      pDev->devInitState |= SPIDEVICE_INITSTATE_EVENTS_DONE;
      pDev->devInitState |= SPIDEVICE_INITSTATE_DEVICEINIT_DONE;
      pDev->devPowerState = SPIDEVICE_POWER_STATE_0;
      *phDev = pDev;
      res = SpiDevice_InitHw(pDev);

      if (res != SPI_SUCCESS)
      {
         SPIDEVICE_LOG(ERROR, "SpiDevice_Init: SpiDevice_InitHw Failure err 0x%x\n", (unsigned int)res);
         break;
      }
   }
   while (0);

   if (SPI_SUCCESS != res)
   {
      return_value = res;

      /*  in case of error undo initialization */
      if (SPIDEVICE_INITSTATE_TARGETINIT_DONE & pDev->devInitState)
      {
         res = SpiDevicePlat_DeInitTarget(pDev->hDevTgt);

         if (SPI_SUCCESS != res) SPIDEVICE_LOG(ERROR, "SpiDevice_Init: SpiDevicePlat_DeInitTarget Failure err 0x%x\n", (unsigned int)res);
      }
   }
   return return_value;
}


/** @brief Deinitializes the device.

    This Function Deinitializes the device and releases
    resources acquired during init.

    @param[in] hDev      Device handle.

    @return int32 - SPI_SUCCESS on success, error code
            on error.
  */
int32 SpiDevice_DeInit(SPIDEVICE_HANDLE hDev)
{
   int32 res = SPI_SUCCESS;
   int32 tgtDeinitRes = SPI_SUCCESS;
   int32 closeHRes = SPI_SUCCESS;
   SpiDevice_DeviceCtxt *pDev = (SpiDevice_DeviceCtxt *)hDev;

   if (NULL == hDev)
   {
      SPIDEVICE_LOG(ERROR, "SpiDevice_DeInit: Null pointer passed \n");
      return SPIDEVICE_ERR_INVALID_DEV_HANDLE;
   }

   if (SPIDEVICE_INITSTATE_EVENTS_DONE & pDev->devInitState)
   {
      if (pDev->platInfo.bInterruptBased)
      {
         closeHRes = (int32)SpiDeviceOsSvc_CloseHandle(pDev->hQupEvt);
         if (SPI_SUCCESS != closeHRes)
         {
            SPIDEVICE_LOG(ERROR,
                          "SpiDevice_DeInit:SpiDeviceOsSvc_CloseHandle Failure err 0x%x\n",
                          (unsigned int)closeHRes);
         }
      }
   }

   if (SPIDEVICE_INITSTATE_TARGETINIT_DONE & pDev->devInitState)
   {
      tgtDeinitRes = (int32)SpiDevicePlat_DeInitTarget(pDev->hDevTgt);
   }

   if (SPI_SUCCESS != tgtDeinitRes)
   {
      SPIDEVICE_LOG(ERROR,
                    "SpiDevice_DeInit:SpiDevicePlat_DeInitTarget Failure err 0x%x\n",
                    (unsigned int)tgtDeinitRes);
   }

   pDev->devInitState = SPIDEVICE_INITSTATE_UNINITIALIZED;
   if (SPI_SUCCESS != closeHRes) /*  return the first error */
   {
      return closeHRes;
   } else if (SPI_SUCCESS != tgtDeinitRes)
   {
      return tgtDeinitRes;
   }

   return res;
}


/** @brief Sets the runstate. It will wait untill the state is valid
           before trying to set the new state or timeout.
           After setting the state QUP_GetRunState() to check that the new
           state is valid.
    @param[in] uQupId       QUP index.
    @param[in] cRunState    The new run state.
    @return           Returns timeout error if the previous state is invalid,
                      success otherwise.
  */
static int32 SpiDevice_SetRunState(uint8 *pQupAddr, const HAL_qupe_RunStateType cRunState)
{
   uint32 uWaitTimeUs = QUP_RUN_STATE_CHANGE_TIME_OUT_US;
   while ((!HAL_qupe_RunStateIsValid(pQupAddr)) && (0 != uWaitTimeUs))
   {
      SpiDeviceOsSvc_BusyWait(QUP_BUSY_WAIT_STEP_US);
      uWaitTimeUs -= QUP_BUSY_WAIT_STEP_US;
   }
   if (0 == uWaitTimeUs)
   {
      return SPIDEVICE_ERR_INVALID_RUNSTATE;
   }

   HAL_qupe_SetRunState(pQupAddr, cRunState);
   while ((!HAL_qupe_RunStateIsValid(pQupAddr)) && (0 != uWaitTimeUs))
   {
      SpiDeviceOsSvc_BusyWait(QUP_BUSY_WAIT_STEP_US);
      uWaitTimeUs -= QUP_BUSY_WAIT_STEP_US;
   }
   if (0 == uWaitTimeUs)
   {
      return SPIDEVICE_ERR_RUNSTATE_CHANGE_TIMEOUT;
   }

   return SPI_SUCCESS;
}

/** @brief waits for any of the events specifiend it the argument.
    @param[in] pDev         Pointer to device structure.
    @return                 Nothing.
  */
static void QUP_WaitForCompletion(SpiDevice_DeviceCtxt *pDev)
{
   int32 res;

   uint32 uTmpTimeout = QUP_BUSY_WAIT_POLL_MAX_US;
   pDev->uPollXferComplete = 0;
   /* loop until either an event happens or timeout */
   do
   {
      SpiDevice_IsrHook((void *)pDev);
      SpiDevice_IstHook((void *)pDev);
      SpiDeviceOsSvc_BusyWait(QUP_BUSY_WAIT_POLL_STEP_US);
      uTmpTimeout = (uTmpTimeout > QUP_BUSY_WAIT_STEP_US) ? (uTmpTimeout - QUP_BUSY_WAIT_STEP_US) : 0;
   }
   while ((!pDev->uPollXferComplete) && (uTmpTimeout > 0));

   if (pDev->uPollXferComplete)
   {
      pDev->transferInfo.transferResult = SPI_SUCCESS;
   } 
   else
   {
      pDev->transferInfo.transferResult = SPIDEVICE_ERR_QUP_TIMEOUT;
   }

   res = SpiDevice_SetRunState((uint8 *)pDev->platInfo.qupVirtBlockAddr, HAL_QUPE_RUNSTATE_PAUSE);

   if (SPI_SUCCESS != res)
   {
      SPIDEVICE_LOG(ERROR,
                    "QUP_WaitForCompletion:SpiDevice_SetRunState Failure err 0x%x\n",
                    (unsigned int)res);
   }

   SpiDevice_WaitForRunStateValid((uint8 *)pDev->platInfo.qupVirtBlockAddr);
   res = SpiDevice_SetRunState((uint8 *)pDev->platInfo.qupVirtBlockAddr, HAL_QUPE_RUNSTATE_RESET);

   if (SPI_SUCCESS != res)
   {
      SPIDEVICE_LOG(ERROR,
                    "QUP_WaitForCompletion:SpiDevice_SetRunState Failure err 0x%x\n",
                    (unsigned int)res);
   }
   SpiDevice_WaitForRunStateValid((uint8 *)pDev->platInfo.qupVirtBlockAddr);
}

/*======================================================================

  FUNCTION   

  DESCRIPTION  This function gets the device parameters for the specified
               device and returns them in the format required for the HAL.

  DEPENDENCIES    None
  PARAMETERS      pDeviceConfiguration - Pointer to the DAL device config
                     specified by the client.
                  pmHalDeviceParameters - Pointer to the HAL parameters
                     that will be returned.

  RETURN VALUE    None

  SIDE EFFECTS    None
======================================================================*/
static void SpiDevice_GetHalDeviceParameters
(
   const SpiDeviceInfoType *pDeviceConfiguration,
   HAL_QUPE_SPI_DeviceParametersType *pmHalDeviceParameters
   )
{
   const SpiDeviceParametersType *pmDeviceParameters
      = &(pDeviceConfiguration->deviceParameters);

   switch (pmDeviceParameters->eClockPolarity)
   {
   case SPI_CLK_IDLE_HIGH:
      pmHalDeviceParameters->eClockPolarity = HAL_QUPE_SPI_CLK_IDLE_HIGH;
      break;

   case SPI_CLK_IDLE_LOW:
      pmHalDeviceParameters->eClockPolarity = HAL_QUPE_SPI_CLK_IDLE_LOW;
      break;

   default:
      pmHalDeviceParameters->eClockPolarity = HAL_QUPE_SPI_CLK_IDLE_HIGH;
      break;
   }

   switch (pmDeviceParameters->eShiftMode)
   {
   case SPI_INPUT_FIRST_MODE:
      pmHalDeviceParameters->eTransferMode = HAL_QUPE_SPI_INPUT_FIRST_MODE;
      break;

   case SPI_OUTPUT_FIRST_MODE:
      /* fallthrough */
   default:
      pmHalDeviceParameters->eTransferMode = HAL_QUPE_SPI_OUTPUT_FIRST_MODE;
   }

   switch (pmDeviceParameters->eClockMode)
   {
   case SPI_CLK_ALWAYS_ON:
      pmHalDeviceParameters->bClockAlwaysOn = TRUE;
      break;
   case SPI_CLK_NORMAL:
      /* fallthrough */
   default:
      pmHalDeviceParameters->bClockAlwaysOn = FALSE;
   }

   switch (pmDeviceParameters->eCSMode)
   {
   case SPI_CS_KEEP_ASSERTED:
      pmHalDeviceParameters->bChipSelectAlwaysOn = TRUE;
      break;
   case SPI_CS_DEASSERT:
      /* fallthough */
   default:
      pmHalDeviceParameters->bChipSelectAlwaysOn = FALSE;
   }

   switch (pmDeviceParameters->eCSPolarity)
   {
   case SPI_CS_ACTIVE_LOW:
      pmHalDeviceParameters->eCSPolarity = HAL_QUPE_SPI_CS_ACTIVE_LOW;
      break;

   case SPI_CS_ACTIVE_HIGH:
      pmHalDeviceParameters->eCSPolarity = HAL_QUPE_SPI_CS_ACTIVE_HIGH;
      break;

   default:
      pmHalDeviceParameters->eCSPolarity = HAL_QUPE_SPI_CS_ACTIVE_LOW;
      break;
   }
   pmHalDeviceParameters->nChipSelectId = pDeviceConfiguration->nSlaveNumber;
}

/*======================================================================

  FUNCTION   

  DESCRIPTION  This function gets the transfer parameters for the specified
               device and returns them in the format required for the HAL.

  DEPENDENCIES    None
  PARAMETERS      pQupConfig- Pointer to the DAL device config
                     specified by the client.
                  pmHalTransferParameters - Pointer to the HAL parameters
                     that will be returned.

  RETURN VALUE    None

  SIDE EFFECTS    None
======================================================================*/
static void SpiDevice_GetHalTransferParameters
(
   const SpiDeviceInfoType *pQupConfig,
   HAL_QUPE_SPI_TransferParametersType *pmHalTransferParameters
   )
{
   const SpiTransferParametersType *pmTransferParameters
      = &(pQupConfig->transferParameters);

   pmHalTransferParameters->nNumBits = (uint8)pmTransferParameters->nNumBits;

   if (SPI_LOOPBACK_ENABLED == pmTransferParameters->eLoopbackMode)
   {
      pmHalTransferParameters->eLoopbackMode = HAL_QUPE_SPI_LOOPBACK_ENABLED;
   } else
   {
      pmHalTransferParameters->eLoopbackMode = HAL_QUPE_SPI_LOOPBACK_DISABLED;
   }
   pmHalTransferParameters->bReceivedDataPacked = TRUE;
   pmHalTransferParameters->bTransmitDataPacked = TRUE;
   if (pmHalTransferParameters->nNumBits > 16)
   {
      pmHalTransferParameters->bReceivedDataPacked = FALSE;
      pmHalTransferParameters->bTransmitDataPacked = FALSE;
   }

   pmHalTransferParameters->eIOMode = HAL_QUPE_IO_MODE_BLOCK;

   /*
    * Always enable output bit shift enable so that there is
    * less confusion about how unpacked data is to be placed in the
    * user buffer.
    */
   pmHalTransferParameters->bOutputBitShift = TRUE;
}

/** @brief Initializes transfer info structures.

    Initializes transfer info structures.

    @param[in] pDev           Pointer to device struct.
    @param[in] pTransfer      Pointer to transfer.
    @param[in] uNumTransfers  Number of transfers.

    @return                   Nothing.
  */
int32 SpiDevice_ConfigureQupSpiDevice_BlockMode(
   SpiDevice_DeviceCtxt *pDev, 
   SpiDeviceInfoType     *pQupConfig) 
{
   int32 res;
   
   HAL_QUPE_SPI_DeviceParametersType mHalDeviceParameters;
   uint32 u32MaxSlaveFrequency, u32MinSlaveFrequency, u32ActualClkSpeed = 0;
   uint32 ns_per_tick, deassert_ticks;
   SpiDeviceParametersType *pDeviceParameters;   

   HAL_qupe_Spi_SetCoreMode((uint8*)pDev->platInfo.qupVirtBlockAddr, HAL_QUPE_SPI_MASTER);

   pDeviceParameters = &(pQupConfig->deviceParameters);
   
   u32MaxSlaveFrequency = pDeviceParameters->u32MaxSlaveFrequencyHz;
   u32MinSlaveFrequency = pDeviceParameters->u32MinSlaveFrequencyHz;

   res = SpiDevicePlat_SetAppClkHz(pDev->hDevTgt, u32MaxSlaveFrequency, &u32ActualClkSpeed);
   
   if(res != SPI_SUCCESS || (u32MinSlaveFrequency > 0 && u32ActualClkSpeed < u32MinSlaveFrequency))  
   {
      SPIDEVICE_LOG(ERROR,"Failed to set frequency matching to slave spec");
      //return SPIDEVICE_ERR_CLOCK_SETTING_FAILED; //jmsx
   }
   
   // Convert deassertion time from nanoseconds to clock ticks (rounding up).  Ticks must
   // be in the range from 1 to 64.
   ns_per_tick = 1000000000 / u32ActualClkSpeed;
   deassert_ticks = (pDeviceParameters->u32DeassertionTime + (ns_per_tick - 1)) / ns_per_tick;
   if (deassert_ticks < 1) deassert_ticks =  1;
   if (deassert_ticks > 64) deassert_ticks = 64;

   mHalDeviceParameters.nDeassertionClockTicks = deassert_ticks;
   
   SpiDevice_GetHalDeviceParameters(pQupConfig, &mHalDeviceParameters);
   HAL_qupe_Spi_SetDeviceParameters((uint8*)pDev->platInfo.qupVirtBlockAddr, &mHalDeviceParameters);

   return 0;
}

/** @brief This function selects the number of transfers needed.

    This function selects the number of transfers needed based on 
    the value of N size passed.

    @param[in] len            Length pased by user.
    @param[in] numBits     Value of N in bits.

    @return      uint32 No: of transfers needed..
  */
static uint32 SpiDevice_GetNumQUPTransfers(uint32 len, uint8 numBits)
{
   uint32 numTransfers = 0;
   if (numBits > 16)
   {
      numTransfers = len / sizeof(uint32);
   } else if (numBits > 8)
   {
      numTransfers = len / sizeof(uint16);
   } else
   {
      numTransfers = len;
   }
   return numTransfers;
}

int32 SpiDevice_ValidateDeviceParams(SpiDevice_DeviceCtxt *pDev, SpiDeviceInfoType *pQupConfig)
{
   if (pQupConfig == NULL)
   {
      SPIDEVICE_LOG(ERROR, "pQupConfig cannot be NULL");
      return(SPIDEVICE_ERR_INVALID_PTR);
   }

   if ((pQupConfig->deviceParameters.eClockMode == SPI_CLK_ALWAYS_ON) &&
        (pQupConfig->deviceParameters.eCSMode == SPI_CS_KEEP_ASSERTED) )
   {
      SPIDEVICE_LOG(ERROR, "SPI_CLK_ALWAYS_ON and SPI_CS_KEEP_ASSERTED cannot both be selected");
      return(SPIDEVICE_ERR_INVALID_PTR);
   }

   return SPI_SUCCESS;
}

int32 SpiDevice_ValidateTransferParams(SpiDevice_DeviceCtxt *pDev, SpiDeviceInfoType *pQupConfig,
                                       SpiDataAddrType *pReadBuffer, uint32 uReadBufLen,
                                       SpiDataAddrType *pWriteBuffer, uint32 uWriteBufLen)
{
   //FIXME: Function in-complete
   return SPI_SUCCESS;
}

int32 SpiDevice_ConfigureQupSpiTransfer_BlockMode (SpiDevice_DeviceCtxt *pDev,
                                                   SpiDeviceInfoType *pQupConfig,
                                                   SpiDataAddrType *pReadBuffer,
                                                   uint32 uReadBufLen,
                                                   SpiDataAddrType *pWriteBuffer,
                                                   uint32 uWriteBufLen)
{
   HAL_QUPE_SPI_TransferParametersType mHalTransferParameters;

   /*Setup output transfer params for HAL and QupTransferInfo*/
   mHalTransferParameters.nNumOutputTransfers = 0;
   pDev->transferInfo.bWriteTransferDone = TRUE;
   pDev->transferInfo.bWriteBufferEmpty = TRUE;

   if((pWriteBuffer) && (pWriteBuffer->virtualAddr) && (uWriteBufLen)) 
   {
      mHalTransferParameters.nNumOutputTransfers = 
         SpiDevice_GetNumQUPTransfers(uWriteBufLen,
                                      (uint8)pQupConfig->transferParameters.nNumBits);
      pDev->transferInfo.bWriteTransferDone = FALSE;
      pDev->transferInfo.bWriteBufferEmpty = FALSE;
   }

   /*Setup input transfer params for HAL and QupTransferInfo*/
   mHalTransferParameters.nNumInputTransfers = 0;
   pDev->transferInfo.bReadTransferDone = TRUE;
   pDev->transferInfo.bReadBufferFull = TRUE;

   if((pReadBuffer) && (pReadBuffer->virtualAddr) && (uReadBufLen)){
      mHalTransferParameters.nNumInputTransfers = 
         SpiDevice_GetNumQUPTransfers(uReadBufLen,
                                      (uint8)pQupConfig->transferParameters.nNumBits);
      pDev->transferInfo.bReadTransferDone = FALSE;
      pDev->transferInfo.bReadBufferFull = FALSE;
   }

   if (0 == mHalTransferParameters.nNumInputTransfers)
   {
      mHalTransferParameters.eTransferDirection = HAL_QUPE_SPI_OUTPUT_ONLY;
	  pDev->transferInfo.direction = SPI_OUT;
   }
   else if (0 == mHalTransferParameters.nNumOutputTransfers)
   {
      mHalTransferParameters.eTransferDirection = HAL_QUPE_SPI_INPUT_ONLY;
	  pDev->transferInfo.direction = SPI_IN;
   } 
   else
   {
      mHalTransferParameters.eTransferDirection = HAL_QUPE_SPI_BI_DIRECTIONAL;
	  pDev->transferInfo.direction = SPI_BI_DIRECTIONAL;
   }

   SpiDevice_GetHalTransferParameters(pQupConfig, &mHalTransferParameters);
   HAL_qupe_Spi_SetTransferParameters((uint8*)pDev->platInfo.qupVirtBlockAddr, &mHalTransferParameters);

   return SPI_SUCCESS;
}

static int32 _SpiDevice_WriteRead_BlockMode(SPIDEVICE_HANDLE hDev, SpiDeviceInfoType *pQupConfig,
                                            SpiDataAddrType *pReadBuffer, uint32 uReadBufLen,
                                            SpiDataAddrType *pWriteBuffer, uint32 uWriteBufLen)
{
   int32 res = SPI_SUCCESS;
   SpiDevice_DeviceCtxt *pDev = (SpiDevice_DeviceCtxt *)hDev;

   do
   {
      res = SpiDevice_InitHw(pDev);

      if (res != SPI_SUCCESS)
      {
         SPIDEVICE_LOG(ERROR, "_SpiDevice_WriteRead_BlockMode: SpiDevice_InitHw Failure err 0x%x\n",
                       (unsigned int)res);
         break;
      }

      if (pDev->platInfo.bInterruptBased)
      {
         res = SpiDeviceOsSvc_ClearEvent(pDev->hQupEvt);

         if (res != SPI_SUCCESS)
         {
            SPIDEVICE_LOG(ERROR, "_SpiDevice_WriteRead_BlockMode: SpiDeviceOsSvc_ClearEvent Failure err 0x%x\n",
                          (unsigned int)res);
            break;
         }
      }

      res = SpiDevice_SetRunState((uint8 *)pDev->platInfo.qupVirtBlockAddr, HAL_QUPE_RUNSTATE_RESET);

      if (SPI_SUCCESS != res)
      {
         SPIDEVICE_LOG(ERROR, "_SpiDevice_WriteRead_BlockMode:SpiDevice_SetRunState Failure err 0x%x\n",
                       (unsigned int)res);
      }
      SpiDevice_WaitForRunStateValid((uint8 *)pDev->platInfo.qupVirtBlockAddr);
      
	  if (pQupConfig)
      {
         res = SpiDevice_ValidateDeviceParams(pDev, pQupConfig);

         if (res != SPI_SUCCESS)
         {
            SPIDEVICE_LOG(ERROR, "_SpiDevice_WriteRead_BlockMode: SpiDevice_ValidateDeviceParams Failure err 0x%x\n",
                          (unsigned int)res);
            break;
         }

         res = SpiDevice_ConfigureQupSpiDevice_BlockMode(pDev, pQupConfig);
         SPIDEVICE_CHK_RESULT_BREAK(res);
      }

      if (NULL == pQupConfig)
      {
         pQupConfig = &(pDev->pClntCfg);
      }

      res = SpiDevice_ValidateTransferParams(pDev, pQupConfig, pReadBuffer, uReadBufLen,
                                             pWriteBuffer, uWriteBufLen);

      if (res != SPI_SUCCESS)
      {
         SPIDEVICE_LOG(ERROR, "_SpiDevice_WriteRead_BlockMode:SpiDevice_ValidateTransferParams Failure err 0x%x\n",
                       (unsigned int)res);
         break;
      }

      res = SpiDevice_ConfigureQupSpiTransfer_BlockMode(pDev, pQupConfig, pReadBuffer, uReadBufLen,
                                                        pWriteBuffer, uWriteBufLen);

      SPIDEVICE_CHK_RESULT_BREAK(res);

      res = SpiDevice_SetRunState((uint8 *)pDev->platInfo.qupVirtBlockAddr,
                                  HAL_QUPE_RUNSTATE_RUN);

      SPIDEVICE_CHK_RESULT_BREAK(res);
   }
   while (0);
   return res;
}

static int32 _SpiDevice_WriteRead(SPIDEVICE_HANDLE hDev, SpiDeviceInfoType *pQupConfig,
                                  SpiDataAddrType *pReadBuffer, uint32 uReadBufLen,
                                  SpiDataAddrType *pWriteBuffer, uint32 uWriteBufLen)
{
   SpiDevice_DeviceCtxt *pDev = (SpiDevice_DeviceCtxt *)hDev;
   uint8 *readBuf = NULL;
   uint8 *readBufPhys = NULL;
   uint32 uTotalReadLen = 0;
   uint8 *writeBuf = NULL;
   uint8 *writeBufPhys = NULL;
   uint32 uTotalWriteLen = 0;

   SPIDEVICE_VALIDATE_WR_PARAMS(pDev, pQupConfig, pReadBuffer, uReadBufLen, pWriteBuffer,
                                uWriteBufLen);

   if ((pReadBuffer != NULL) && (pWriteBuffer != NULL))
   {
      readBuf = (uint8 *)pReadBuffer->virtualAddr;
      readBufPhys = (uint8 *)pReadBuffer->physicalAddr;
      uTotalReadLen = uReadBufLen;
      writeBuf = (uint8 *)pWriteBuffer->virtualAddr;
      writeBufPhys = (uint8 *)pWriteBuffer->physicalAddr;
      uTotalWriteLen = uWriteBufLen;
   } else if ((pReadBuffer == NULL) && (pWriteBuffer != NULL))
   {
      writeBuf = (uint8 *)pWriteBuffer->virtualAddr;
      writeBufPhys = (uint8 *)pWriteBuffer->physicalAddr;
      uTotalWriteLen = uWriteBufLen;
   } else if ((pReadBuffer != NULL) && (pWriteBuffer == NULL))
   {
      readBuf = (uint8 *)pReadBuffer->virtualAddr;
      readBufPhys = (uint8 *)pReadBuffer->physicalAddr;
      uTotalReadLen = uReadBufLen;
   }

   SpiDeviceSingleBufferTransferInit(&pDev->transferInfo,
                                     readBuf, readBufPhys, uTotalReadLen,
                                     writeBuf, writeBufPhys, uTotalWriteLen);

   return _SpiDevice_WriteRead_BlockMode(hDev, pQupConfig, pReadBuffer, uReadBufLen, pWriteBuffer, uWriteBufLen);
}


/** @brief Set the power state of the device.

    This Function sets the power state for the device.

    @param[in] hDev           Device handle.
    @param[in] ePowerState    the new power state

    @return          int32 .
  */
int32
SpiDevice_SetPowerState
(
   SPIDEVICE_HANDLE hDev,
   SpiDevice_PowerStates ePowerState
   )
{
   SpiDevice_DeviceCtxt *pDev = (SpiDevice_DeviceCtxt *)hDev;
   return (int32)SpiDevicePlat_SetPowerState(pDev->hDevTgt, ePowerState);
}


/** @brief Peform a bi-direction transfer

    Read a buffer from SPI device and/or Write a buffer of 
   data to a SPI device

    @param[in] hDev           Device handle.
    @param[in] *pQupConfig   Pointer to the QUP config for data transfer.
    @param[in] pReadBuffer    Pointer where incoming data will
          be stored.
    @param[in] uReadBufLen    Number of bytes of valid data to be 
        stored in pReadbuffer
    @param[in] pWriteBuffer    Pointer where outgoing data is  
          stored.
    @param[in] uWriteBufLen    Number of bytes of valid data stored in 
        pWritebuffer
    @return          int32 .
  */
int32 SpiDevice_WriteRead (SPIDEVICE_HANDLE hDev, SpiDeviceInfoType *pQupConfig,
                           SpiDataAddrType *pReadBuffer, uint32 uReadBufLen, 
                           SpiDataAddrType *pWriteBuffer,uint32 uWriteBufLen)
{
   int32 res;
   SpiDevice_DeviceCtxt *pDev = (SpiDevice_DeviceCtxt *)hDev;
   pDev->asyncCall.pCallbackFn = NULL;
   pDev->asyncCall.asyncResult.pArg = NULL;

   if (SPI_SUCCESS != (res = _SpiDevice_WriteRead(hDev, pQupConfig,
                                                  pReadBuffer, uReadBufLen, pWriteBuffer, uWriteBufLen)))
   {
      SPIDEVICE_LOG(ERROR, "SpiDevice_WriteRead: Failure err 0x%x\n", (unsigned int)res);
      pDev->transferInfo.transferResult = res;
      return pDev->transferInfo.transferResult;
   }

   QUP_WaitForCompletion(pDev);
   return pDev->transferInfo.transferResult;
}

static uint32 QUP_ServiceQUP(SpiDevice_DeviceCtxt *pDev)
{
   SpiDevice_RegInfo *pQupInfo;
   volatile uint32 uOperationalFlags, uSetServiceFlags = 0;
   
   pQupInfo = &pDev->qupInfo;

   SpiDeviceOsSvc_BusyWait(QUP_OP_STATE_READY_TIME_US);

   pQupInfo->uQupErrors = HAL_qupe_GetErrStatusFlags((uint8 *)pDev->platInfo.qupVirtBlockAddr);
   uOperationalFlags = HAL_qupe_GetOpStatusFlags((uint8 *)pDev->platInfo.qupVirtBlockAddr);
   pQupInfo->uOperational = uOperationalFlags;

   // Check for errors 
   if (pQupInfo->uQupErrors & HAL_QUPE_ERRSTATE_FIELD)
   {
      HAL_qupe_Reset((uint8 *)pDev->platInfo.qupVirtBlockAddr);
      SpiDevice_WaitForRunStateValid((uint8 *)pDev->platInfo.qupVirtBlockAddr);
      return (pQupInfo->uOutFreeSlotReqCnt + pQupInfo->uInFreeSlotReqCnt);
   }

   // If output service then fill the output queue with another block
   if ((uOperationalFlags & HAL_QUPE_OPSTATE_OUTPUT_SERVICE) &&
       (uOperationalFlags & HAL_QUPE_OPSTATE_OUT_BLOCK_WRITE_REQ))
   {
      uSetServiceFlags = HAL_QUPE_OPSTATE_OUTPUT_SERVICE;
      pQupInfo->uOutFreeSlotReqCnt += pDev->devHwInfo.uNumOutputBlockSlots;
   }

   if (uOperationalFlags & HAL_QUPE_OPSTATE_MAX_OUTPUT_DONE)
   {
      pQupInfo->uMaxOutputDone = TRUE;
      uSetServiceFlags |= HAL_QUPE_OPSTATE_OUTPUT_SERVICE;
   }

   // If input service then get the blocks from queue
   if ((uOperationalFlags & HAL_QUPE_OPSTATE_INPUT_SERVICE) &&
       (uOperationalFlags & HAL_QUPE_OPSTATE_IN_BLOCK_READ_REQ))
   {
      uSetServiceFlags |= HAL_QUPE_OPSTATE_INPUT_SERVICE;
      pQupInfo->uInFreeSlotReqCnt += pDev->devHwInfo.uNumInputBlockSlots;
   }

   if (pQupInfo->uOperational & HAL_QUPE_OPSTATE_MAX_INPUT_DONE)
   {
      pQupInfo->uMaxInputDone = TRUE;
      uSetServiceFlags |= HAL_QUPE_OPSTATE_INPUT_SERVICE;
   }

   HAL_qupe_ClearOpStatusFlags((uint8 *)pDev->platInfo.qupVirtBlockAddr, uSetServiceFlags);

   return (pQupInfo->uOutFreeSlotReqCnt + pQupInfo->uInFreeSlotReqCnt);
}

/**
    This function services the queue.
    It checks the set operational flags and clears the service flags.

    @param[in, out] pInfo  Pointer to QupInfo structure.
    @return         Nothing.
  */
static uint32 QUP_PerformOutput (SpiDevice_DeviceCtxt *pDev)
{
   SpiDevice_RegInfo *pQupInfo = &(pDev->qupInfo);
   SpiDeviceTransferType *transferInfo = &(pDev->transferInfo);
   SpiDeviceTransferDataResult res;
   uint32 writeData;

   /* If to be qued and space continue state machine
      As we loop through the transfers we update read tr cnt 
      If output is done update the state of the output sequence */
   while (pQupInfo->uOutFreeSlotReqCnt > pQupInfo->uOutFreeSlotServicedCnt)
   {
      if (SPIDEVICE_TRANSFER_GET_DATA_NONE !=
             (res = transferInfo->getNextWord(transferInfo, &writeData)))
      {
         /*  push slot into output fifo */
         HAL_qupe_PutWordIntoOutFifo((uint8 *)pDev->platInfo.qupVirtBlockAddr, writeData);
         pQupInfo->uOutFreeSlotServicedCnt++;
         if (SPIDEVICE_TRANSFER_GET_DATA_DONE == res)
         {
            pDev->transferInfo.bWriteBufferEmpty = TRUE;
         }

      } else if (pQupInfo->uOutFreeSlotReqCnt - pQupInfo->uOutFreeSlotServicedCnt
                 < pDev->devHwInfo.uNumOutputBlockSlots)
      {
         /*Write zeros till we get to the block boundary.*/
         writeData = 0;
         HAL_qupe_PutWordIntoOutFifo((uint8 *)pDev->platInfo.qupVirtBlockAddr, writeData);
         pQupInfo->uOutFreeSlotServicedCnt++;
      } 
      else
      {
         /*We should Error Fatal here or abort tranfer because we're provided with insufficient buffer space*/
      }
   }
   return pQupInfo->uOutFreeSlotServicedCnt;
}

/**
    This function services the queue.
    It checks the set operational flags and clears the service flags.

    @param[in, out] pInfo  Pointer to QupInfo structure.
    @return         Nothing.
  */
static uint32 QUP_PerformInput (SpiDevice_DeviceCtxt *pDev)
{
   int32 res;
   SpiDevice_RegInfo *pQupInfo = &(pDev->qupInfo);
   SpiDeviceTransferType *transferInfo = &(pDev->transferInfo);
   uint32 readData;

   /* If transfer to be queued Check if there is space in the output fifo 
   ** If to be qued and space continue state machine 
   ** As we loop through the transfers we update read tr cnt
   ** If output is done update the state of the output sequence 
   */
   while (pQupInfo->uInFreeSlotReqCnt > pQupInfo->uInFreeSlotServicedCnt)
   {
      /*  get slot from fifo */
      HAL_qupe_GetWordFromInFifo(
         (uint8 *)pDev->platInfo.qupVirtBlockAddr,
         &readData);
      /*Even if there is */
      if (SPIDEVICE_TRANSFER_SET_DATA_NONE !=
             (res = transferInfo->setNextWord(transferInfo, &readData)))
      {
         pQupInfo->uInFreeSlotServicedCnt++;
         if (SPIDEVICE_TRANSFER_SET_DATA_DONE == res)
         {
            pDev->transferInfo.bReadBufferFull = TRUE;
         }
      } 
      else if (pQupInfo->uInFreeSlotReqCnt - pQupInfo->uInFreeSlotServicedCnt < pDev->devHwInfo.uNumInputBlockSlots)
      {
         pQupInfo->uInFreeSlotServicedCnt++;
      } 
      else
      {
         /*We should Error Fatal here or abort tranfer because we're provided with insufficient buffer space*/
      }
   }
   return pQupInfo->uInFreeSlotServicedCnt;
}

static void QUP_Completion (SpiDevice_DeviceCtxt *pDev)
{
   int32 res;
   // if this is an asynchronous transfer then set results and
   // dispatch callback
   // else just signal the waiting thread
   if (NULL != pDev->asyncCall.pCallbackFn) // blocking transfer
   {
      pDev->asyncCall.asyncResult.nTransferStatus = pDev->transferInfo.transferResult;
      pDev->asyncCall.pCallbackFn(&pDev->asyncCall.asyncResult);
   }
   else
   {
      if (pDev->platInfo.bInterruptBased) // Interrupt based wait. 
      {
         res = (int32)SpiDeviceOsSvc_SetEvent(pDev->hQupEvt);

         if (SPI_SUCCESS != res)
         {
            SPIDEVICE_LOG(ERROR, "QUP_Completion:SpiDeviceOsSvc_SetEvent Failure err 0x%x\n", (unsigned int)res);
         }
      } else /* Set Polling mode complete flag*/
      {
         pDev->uPollXferComplete = 1;
      }
   }
}

/**
    This function services the queue.
    It checks the set operational flags and clears the service flags.

    @param[in, out] pInfo  Pointer to QupInfo structure.
    @return         Nothing.
  */
static uint32 QUP_PerformInputOutput
(
   SpiDevice_DeviceCtxt *pDev
)
{
   SpiDeviceTransferType *transferInfo = &(pDev->transferInfo);
   SpiDevice_RegInfo *pQupInfo = &(pDev->qupInfo);
   int32 res;
   uint32 TxRxCount = 0;

   TxRxCount = QUP_PerformOutput(pDev);
   TxRxCount += QUP_PerformInput(pDev);

   if ((pQupInfo->uMaxOutputDone) && (transferInfo->bWriteBufferEmpty))
   {
      transferInfo->bWriteTransferDone = TRUE;
   }

   if ((pQupInfo->uMaxInputDone) && (transferInfo->bReadBufferFull))
   {
      transferInfo->bReadTransferDone = TRUE;
   }

   if ((transferInfo->bWriteTransferDone) && (transferInfo->bReadTransferDone))
   {
      res = SpiDevice_SetRunState((uint8 *)pDev->platInfo.qupVirtBlockAddr,
                                  HAL_QUPE_RUNSTATE_PAUSE);
      SpiDevice_WaitForRunStateValid((uint8 *)pDev->platInfo.qupVirtBlockAddr);
      if (SPI_SUCCESS != res)
      {
         SPIDEVICE_LOG(ERROR, "QUP_PerformInputOutput:SpiDevice_SetRunState Failure err 0x%x\n",
                       (unsigned int)res);
      }

      res = SpiDevice_SetRunState((uint8 *)pDev->platInfo.qupVirtBlockAddr,
                                  HAL_QUPE_RUNSTATE_RESET);
      SpiDevice_WaitForRunStateValid((uint8 *)pDev->platInfo.qupVirtBlockAddr);
      if (SPI_SUCCESS != res)
      {
         SPIDEVICE_LOG(ERROR, "QUP_PerformInputOutput:SpiDevice_SetRunState Failure err 0x%x\n",
                       (unsigned int)res);
      }

      transferInfo->transferResult = SPI_SUCCESS;
      pQupInfo->uOutFreeSlotReqCnt = pQupInfo->uOutFreeSlotServicedCnt = 0;
      pQupInfo->uInFreeSlotReqCnt = pQupInfo->uInFreeSlotServicedCnt = 0;
      pQupInfo->uMaxInputDone = pQupInfo->uMaxOutputDone = FALSE;
      QUP_Completion(pDev);
   }
   return TxRxCount;
}
