/*=============================================================================

  FILE:   I2cPlatSvc.c

  OVERVIEW: This file contains the implementation for the platform services.
 
          Copyright (c) 2011 - 2013 Qualcomm Technologies Incorporated.
          All Rights Reserved.
          Qualcomm Confidential and Proprietary 

=============================================================================*/
/*=============================================================================
EDIT HISTORY FOR MODULE

$Header: //components/rel/core.adsp/2.6.1/buses/i2c/src/drv/I2cPlatSvcInit.c#2 $
$DateTime: 2014/12/23 14:54:01 $$Author: pwbldsvc $
When     Who    What, where, why
-------- ---    -----------------------------------------------------------
07/17/13 LK     Added xml properties.
09/26/11 LK     Created
PLEASE REMOCVE ME: Adding line to fool PW, to allow reverting a change
=============================================================================*/

/*-------------------------------------------------------------------------
 * Include Files
 * ----------------------------------------------------------------------*/

#include "I2cPlatSvc.h"
#include "I2cSys.h"
#include "I2cError.h"

//DEBUG
#include "DALDeviceId.h"
#include "DDITlmm.h"
#include "DDIHWIO.h"
#include "npa.h"
//DEBUG

/*----------------------------------------------------------------------------
 * Preprocessor Definitions and Constants
 * -------------------------------------------------------------------------*/
#define QUP_FREQ_HZ                            19200000

#define I2C_DEVICE_PLATBAM_MAX_BAM_THRESHOLD (32*1024)
#define I2C_DEVICE_PLATBAM_MAX_DESC_SIZE     0x100

#define I2C_ICB_CLIENT_CNT          1
#define I2C_PNOC_MSTRSLV_PAIRS_NUM	1

#if 0
typedef struct I2cOs_IrqType
{
   ISR_HOOK IsrHook;
   IST_HOOK IstHook;
   void     *pIsrData;
   void     *pIstData;
   uint32   uInterruptId;
   uint32   uIrqTriggerCfg;
} I2cOs_IrqType;
#endif


/*-------------------------------------------------------------------------
 * Static Variable Definitions
 * ----------------------------------------------------------------------*/
static uint8                         *pPeriphSsBasePtr  = NULL;
static DalDeviceHandle               *phDalHWIO         = NULL;
static DalDeviceHandle               *hTlmm             = NULL;
static npa_client_handle              hNpaClient        = NULL;
static uint32                         uTgtCnt           = 0;

/*-------------------------------------------------------------------------
 * Static Function Declarations and Definitions
 * ----------------------------------------------------------------------*/

/** @brief Initializes the tlmm handle gpios.
  
    @param[in] pDev     Pointer to platform device structure.
    
    @return             I2C_RES_SUCCESS is successful, otherwise
                        I2cPlat_Error.
  */
static int32
I2cPlat_InitTlmm
(
   I2cPlat_DescType *pPlat
)
{
   DALResult dalRes;

   if (NULL == hTlmm) {
      dalRes = DAL_DeviceAttachEx(NULL, DALDEVICEID_TLMM,
                                  DALTLMM_INTERFACE_VERSION, &hTlmm);
      if ( (DAL_SUCCESS != dalRes) || (NULL == hTlmm) ) {
         hTlmm = NULL;     
         return I2CPLAT_ERROR_FAILED_TO_ATTACH_TO_TLMM;
      }
   
      dalRes = DalDevice_Open(hTlmm, DAL_OPEN_SHARED);
      if ( DAL_SUCCESS != dalRes ) {
         DAL_DeviceDetach(hTlmm);
         hTlmm = NULL;     
         return I2CPLAT_ERROR_FAILED_TO_OPEN_TLMM;
      }
   }
   
   return I2C_RES_SUCCESS;
}

/** @brief releases tlmm handle gpios.
              
    @param[in] pDev     Pointer to platform device structure.
              
    @return             I2C_RES_SUCCESS is successful, otherwise
                        I2cPlat_Error.
  */
static int32
I2cPlat_DeInitTlmm
(
   I2cPlat_DescType *pPlat
)
{
   DALResult dalRes;
   //uint32 uGpioInd;
   int32 res = I2C_RES_SUCCESS;

   if (NULL != hTlmm) {
      dalRes = DalDevice_Close(hTlmm);
      if ( DAL_SUCCESS != dalRes ) {
         res = I2CPLAT_ERROR_FAILED_TO_OPEN_TLMM;
      }
      dalRes = DAL_DeviceDetach(hTlmm);
      if ( DAL_SUCCESS != dalRes ) {
         res = I2CPLAT_ERROR_FAILED_TO_ATTACH_TO_TLMM;
      }
      hTlmm = NULL;
      }
   
   return res;
   }
   
/** @brief Configures and enables I2C gpios.
  
    @param[in] pDev     Pointer to platform device structure.
    
    @return             I2C_RES_SUCCESS is successful, otherwise
                        I2cPlat_Error.
  */
int32
I2cPlat_EnableI2cGpios
(
   I2cPlat_DescType *pPlat
)
{
   DALResult dalRes;
   uint32 uGpioInd;

   for (uGpioInd = 0; uGpioInd <  pPlat->props.uNumGpios ; uGpioInd++) {
      dalRes = DalTlmm_ConfigGpio(hTlmm, pPlat->props.aGpioCfg[uGpioInd],
                                  DAL_TLMM_GPIO_ENABLE);
      if ( DAL_SUCCESS != dalRes ) {
         return I2CPLAT_ERROR_FAILED_TO_CONFIGURE_GPIO;
      }
   }
   return I2C_RES_SUCCESS;
}

/** @brief disables I2C gpios.
  
    @param[in] pDev     Pointer to platform device structure.
    
    @return             I2C_RES_SUCCESS is successful, otherwise
                        I2cPlat_Error.
  */
int32
I2cPlat_DisableI2cGpios
(
   I2cPlat_DescType *pPlat
)
{
   DALResult dalRes;
   uint32 uGpioInd;

      for (uGpioInd = 0; uGpioInd <  pPlat->props.uNumGpios ; uGpioInd++) {
         dalRes = DalTlmm_ConfigGpio(hTlmm, pPlat->props.aGpioCfg[uGpioInd],
                                  DAL_TLMM_GPIO_DISABLE);
         if ( DAL_SUCCESS != dalRes ) {
            return I2CPLAT_ERROR_FAILED_TO_CONFIGURE_GPIO;
         }
      }
   return I2C_RES_SUCCESS; 
}


/** @brief Initializes bam.
  
    @param[in]  uPlatDevId  Platform device ID.
    @param[out] pDev        Pointer to platform device
          structure.
    
    @return             I2C_RES_SUCCESS is successful, otherwise
                        I2cPlat_Error.
  */
int32
I2cPlat_ReadPlatConfig
(
   uint32                    uPlatDevId,
   I2cPlat_DescType    *pPlat
)
{
#if 0
   DALSYS_PROPERTY_HANDLE_DECLARE(hProp);
   DALSYSPropertyVar               PropVar;
   int32 result;

   if ( DAL_SUCCESS != DALSYS_GetDALPropertyHandle(uPlatDevId, hProp ) ) {
      return I2CPLAT_ERROR_DAL_GET_PROPERTY_HANDLE;
   }

   result = I2CPLAT_ERROR_DAL_GET_PROPERTY_VALUE; /* set the error. */
   do {
      if ( DAL_SUCCESS !=
            DALSYS_GetPropertyValue(hProp, "CHIP_BUS_INDEX", 0, &PropVar) ) {
         break;
      }
      pPlat->uBusIdx = (uint32)PropVar.Val.dwVal;

      if ( DAL_SUCCESS !=
            DALSYS_GetPropertyValue(hProp, "CHIP_QUP_BASE_ADDR", 0, &PropVar) ) {
         break;
      }
      pPlat->devProp.virtBlockAddr = (uint8 *)PropVar.Val.dwVal;

      if ( DAL_SUCCESS ==
            DALSYS_GetPropertyValue(hProp, "CHIP_GPIO_CONFIG_ARR", 0, &PropVar )) {
         pPlat->aGpioCfg = PropVar.Val.pdwVal;
         pPlat->uNumGpios = PropVar.dwLen;
      }
      else {
         pPlat->uNumGpios = 0;
      }

      if ( DAL_SUCCESS !=
            DALSYS_GetPropertyValue(hProp, "CHIP_APPS_CLK_FREQ_KHZ", 0, &PropVar) ) {
         break;
      }
      pPlat->devProp.uI2cInputClkKhz = (uint32)PropVar.Val.dwVal;

      result = I2C_RES_SUCCESS;
   } while ( 0 );

   return result;
#endif
   return I2C_RES_SUCCESS;
}

/** @brief Maps the hwio address space.
  
    @param[in] pPlat    Pointer to platform struct.
    @param[in] pProps   Pointer to platform properties.
    
    @return             I2C_RES_SUCCESS is successful, otherwise
                        I2CPLAT_Error.
  */
static int32
I2cPlat_InitHwio
(
   I2cPlat_DescType *pPlat,
   I2cPlat_PropertyType  *pProps
)
{
   DALResult dalRes;

   if ( NULL == pPeriphSsBasePtr ) {
      dalRes = DAL_DeviceAttach(DALDEVICEID_HWIO, &phDalHWIO);
      if ( (DAL_SUCCESS != dalRes) || (NULL == phDalHWIO) ) {
         return I2CPLAT_ERROR_ATTACH_TO_DALHWIO;
      }
      pPlat->initState |= I2CPLAT_TGT_INIT_HWIO_ALLOCATED;

      if ( DAL_SUCCESS !=
             DalHWIO_MapRegion(phDalHWIO,
                               pProps->pPeriphSsAddrName,
                               &pPeriphSsBasePtr) ) {
         return I2CPLAT_ERROR_FAILED_TO_MAP_BLOCK_HWIO;
      }
   }
   pPlat->pQupAddr = pPeriphSsBasePtr + pPlat->props.coreOffset;
   return I2C_RES_SUCCESS;
}


/** @brief Registers a suppressible client for i2c.
    
    @return             I2C_RES_SUCCESS is successful, otherwise
                        I2CPLAT_Error.
  */


static int32
I2cPlat_RegisterSuppressibleClient
(
   void
)
{
   if ( NULL == hNpaClient ) {
      hNpaClient = npa_create_sync_client("/clk/pnoc", "I2C", NPA_CLIENT_SUPPRESSIBLE);
      if( hNpaClient == NULL ) 
      {
         return I2CPLAT_ERROR_FAILED_TO_CREATE_PNOC_CLIENT;
      }
   }
   
   return I2C_RES_SUCCESS;
}

/** @brief Unregisters suppressible client for i2c.
 
    @return             I2C_RES_SUCCESS is successful, otherwise
                        I2CPLAT_Error.
  */

static int32
I2cPlat_UnregisterSuppresibleClient
(
   void
)
{
   if ( NULL != hNpaClient ) {
      npa_destroy_client (hNpaClient);
     hNpaClient = NULL;  
   }
   
   return I2C_RES_SUCCESS; 
}

/** @brief sets the vote for PNOC.
  
    @param[in] pDev     Pointer to platform device structure.
    @param[in] hClnt    Npa client handle.
    @param[in] uIb      PNOC IB value.
    @param[in] uAb      PNOC AB value.
    
    @return             I2C_RES_SUCCESS is successful, otherwise
                        I2CPLAT_Error.
  */

int32
I2cPlat_AddPnocVote
(
   I2cPlat_DescType             *pPlat,
   uint64         uPeakBandwidthBps,
   uint64         uAvgBandwidthBps
)
{
   uint32 uPnocFreqKHz;

   //Convert peak bandwidth data to frequency since npa calls accept frequency.
   //Average bandwidth data is not used when calling npa calls as in below. Its used only
   //when calling intp ICB layer on other platforms.

   //Bus is 8 Bytes wide.
   uPnocFreqKHz = uPeakBandwidthBps/(8 * 1000);
   if (uPeakBandwidthBps && !uPnocFreqKHz){
      uPnocFreqKHz = 1;
   }
   npa_issue_suppressible_request( hNpaClient, uPnocFreqKHz); //Data is frequency in KHz
   return I2C_RES_SUCCESS; //npa calls return void
}

/** @brief unvote for PNOC.
  
    
    @return             I2C_RES_SUCCESS is successful, otherwise
                        I2CPLAT_Error.
  */

int32
I2cPlat_RemovePnocVote
(
   void
)
{ 
   npa_issue_suppressible_request( hNpaClient, 0); //Set frequency to 0
   return I2C_RES_SUCCESS; 
}

/** @brief detaches from DALDEVICEID_HWIO.
  
    @param[in] pDev     Pointer to platform device structure.
    
    @return             I2C_RES_SUCCESS is successful, otherwise
                        I2CPLAT_Error.
  */
static int32
I2cPlat_DeInitHwio
(
   I2cPlat_DescType     *pDev
)
{
   DALResult dalRes;

   if ( NULL != phDalHWIO ) {
      dalRes = DAL_DeviceDetach(phDalHWIO);
      if ( DAL_SUCCESS != dalRes ) {
         return I2CPLAT_ERROR_DETACH_FROM_DALHWIO;
      }
   }
   return I2C_RES_SUCCESS;
}

/*-------------------------------------------------------------------------
 * Externalized Function Definitions
 * ----------------------------------------------------------------------*/



/** @brief Initializes data structures necessary to support the target calls.
 
 @param[in] pPlat  pointer to platform device structure.
 @param[in] pProps pointer to platform properties.
 
 @return          int32 .
 */
int32
I2cPlat_InitTarget
(
 I2cPlat_DescType      *pPlat ,
 I2cPlat_PropertyType  *pProps
 )
{
   int32                           res;

   do
   {
	   uTgtCnt++;
      
      pPlat->initState = I2CPLAT_TGT_INIT_NOT_DONE;
      
      pPlat->props = *pProps;
      res = I2cPlat_InitTlmm(pPlat);
      if ( I2C_RES_SUCCESS != res ) {
         break;
      }
      /* //GPIOs are now enabled in Drv_Open to avoid gpio inits when not used.
      res = I2cPlat_EnableI2cGpios(pPlat);
      if ( I2C_RES_SUCCESS != res ) {
         break;
      }
      */
      res = I2cPlat_RegisterSuppressibleClient();
      if ( I2C_RES_SUCCESS != res ) {
         break;
      }

      res = I2cPlat_InitHwio(pPlat, pProps);
      if ( I2C_RES_SUCCESS != res ) {
         break;
      }
     
      res = I2C_RES_SUCCESS;
    } while ( 0 );

   if ( I2C_RES_SUCCESS != res ) {
      I2cPlat_DeInitTarget(pPlat);
   }
   return res;
}


/** @brief Releases data structures necessary to support the target calls.

    @param[in] pPlat platform device pointer.

    @return          int32 .
  */
int32
I2cPlat_DeInitTarget
(
   I2cPlat_DescType *pPlat
)
{
   int32      res, ret = I2C_RES_SUCCESS;

   uTgtCnt--;
   /*
   res = I2cPlat_DisableI2cGpios(pPlat);
   if ( I2C_RES_SUCCESS != res ) {
      ret = res;     
   }
   */
   if ( 0 == uTgtCnt) {
      res = I2cPlat_DeInitTlmm(pPlat);
      if ( I2C_RES_SUCCESS != res ) {
         ret = res;     
   }
      res = I2cPlat_UnregisterSuppresibleClient();     
      if ( I2C_RES_SUCCESS != res ) {
         ret = res;     
      }
      
      res = I2cPlat_DeInitHwio(pPlat);
      if ( I2C_RES_SUCCESS != res ) {
         ret = res;     
   }
   }

   return ret;
}

/** @brief Returns the QUP virtual address.

    @param[in]  pPlat platform device pointer.

    @return          int32 .
  */
uint8*
I2cPlat_GetQupAddress
(
   I2cPlat_DescType      *pPlat
)
{
   return pPlat->pQupAddr;

}

/**
    This Function registers IST callback.

    @param[in]  pPlat        Platform device pointer.
    @param[in]  IsrHook      ISR function pointer.
    @param[in]  pIsrData     pointer to ISR callback data.
    @param[in]  IstHook      IST function pointer.
    @param[in]  pIstData     pointer to IST callback data.

    @return             I2C_RES_SUCCESS is successful, otherwise
                        I2cPlat_Error.
  */
int32
I2cPlat_RegisterIstHooks
(
   I2cPlat_DescType  *pDev,
   ISR_HOOK                IsrHook,
   void*                   pIsrData,
   IST_HOOK                IstHook,
   void*                   pIstData
)
{
#if 0
   DALResult                     dalRes;
   
   if ( NULL == pDev->hInterruptCtrl ) {
      dalRes =
          DAL_InterruptControllerDeviceAttach(DALDEVICEID_INTERRUPTCONTROLLER,
                                              &pDev->hIrqCtrl);
      if( (DAL_SUCCESS != dalRes) || (NULL == pDev->hIrqCtrl) ) {
         return I2CPLAT_ERROR_FAILED_ATTACH_TO_IRQCTRL; 
      }
   }

   dalRes = DalInterruptController_RegisterISR(
                        pDev->hIrqCtrl,
                        pDev->props.uInterruptId,
                        IstHook,
                        (DALISRCtx)pIstData,
                        DALINTRCTRL_ENABLE_LEVEL_HIGH_TRIGGER);
   if ( DAL_SUCCESS != dalRes ) {
      return I2CPLAT_ERROR_FAILED_TO_REGISTER_IST;
   }
#endif
   return I2C_RES_SUCCESS;
}

/**
    This Function unregisters IST and ISR callbacks.

    @param[in]  hPlatDev     Platform handle.

    @return             I2C_RES_SUCCESS is successful, otherwise
                        I2cPlat_Error.
  */
int32
I2cPlat_UnRegisterIstHooks
(
   I2cPlat_DescType  *pDev
)
{
#if 0
   DALResult                     dalRes;
   
   if ( NULL == pDev->hInterruptCtrl ) {
      return I2CPLAT_ERROR_IRQCTRL_NOT_INITIALISED; 
   }

   dalRes = DalInterruptController_Unregister(pDev->hIrqCtrl, pDev->props.uInterruptId);
   if ( DAL_SUCCESS != dalRes ) {
      return I2CPLAT_ERROR_FAILED_TO_UNREGISTER_IST;
   }
#endif
   return I2C_RES_SUCCESS;
}

#if 0

#endif


