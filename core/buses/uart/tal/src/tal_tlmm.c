/*==================================================================================================

FILE: tal_tlmm.c

DESCRIPTION: This module defines the "stock" implementation of the TLMM APIs for the
             Target Abstraction Layer.  This implementation simply forwards requests
             to the DAL TLMM.

                            Copyright (c) 2012-2013 Qualcomm Technologies Incorporated
                                        All Rights Reserved
                                     QUALCOMM Proprietary/GTDR

==================================================================================================*/
/*==================================================================================================

$Header: //components/rel/core.adsp/2.6.1/buses/uart/tal/src/tal_tlmm.c#1 $

==================================================================================================*/
/*==================================================================================================
                                            DESCRIPTION
====================================================================================================

GLOBAL FUNCTIONS:
   tal_tlmm_close
   tal_tlmm_gpio_disable
   tal_tlmm_gpio_enable
   tal_tlmm_open

==================================================================================================*/
/*==================================================================================================
                                           INCLUDE FILES
==================================================================================================*/

#if ( defined(_WIN32) && !defined(_WIN32_WCE) )
#include "dal.h"
#else
#include "comdef.h"
#include "DALDeviceId.h"
#include "DALSys.h"
#include "DDITlmm.h"
#endif

#include "tal.h"

/*==================================================================================================
                                              TYPEDEFS
==================================================================================================*/

typedef struct tal_tlmm_context
{
   DALDEVICEID       client_id;
   DalDeviceHandle  *tlmm_dal;
} TAL_TLMM_CONTEXT;

/*==================================================================================================
                                          GLOBAL FUNCTIONS
==================================================================================================*/
/*==================================================================================================

FUNCTION: tal_tlmm_close

DESCRIPTION:

==================================================================================================*/
void tal_tlmm_close(TAL_TLMM_HANDLE handle)
{
   DalDevice_Close(handle->tlmm_dal);
   DAL_DeviceDetach(handle->tlmm_dal);
   DALSYS_Free(handle);
}

/*==================================================================================================

FUNCTION: tal_tlmm_gpio_disable

DESCRIPTION:

==================================================================================================*/
TAL_RESULT tal_tlmm_gpio_disable(TAL_TLMM_HANDLE handle, uint32 *gpio_group, uint32 num_gpios)
{
   DALResult result = DAL_SUCCESS;

   if (num_gpios)
   {
      result = DalTlmm_ConfigGpioGroup(handle->tlmm_dal, DAL_TLMM_GPIO_DISABLE,
                                       gpio_group, num_gpios);
   }

   return (result == DAL_SUCCESS) ? (TAL_SUCCESS) : (TAL_ERROR);
}

/*==================================================================================================

FUNCTION: tal_tlmm_gpio_enable

DESCRIPTION:

==================================================================================================*/
TAL_RESULT tal_tlmm_gpio_enable(TAL_TLMM_HANDLE handle, uint32 *gpio_group, uint32 num_gpios)
{
   DALResult result = DAL_SUCCESS;

   if (num_gpios)
   {
      result = DalTlmm_ConfigGpioGroup(handle->tlmm_dal, DAL_TLMM_GPIO_ENABLE,
                                       gpio_group, num_gpios);
   }

   return (result == DAL_SUCCESS) ? (TAL_SUCCESS) : (TAL_ERROR);
}

/*==================================================================================================

FUNCTION: tal_tlmm_open

DESCRIPTION:

==================================================================================================*/
TAL_RESULT tal_tlmm_open(TAL_TLMM_HANDLE *phandle, uint32 client_id)
{
   TAL_TLMM_CONTEXT *tlmm_ctxt = NULL;
   DalDeviceHandle *tlmm_dal = NULL;
   DALResult result;

   result = DALSYS_Malloc(sizeof(TAL_TLMM_CONTEXT), (void **)&tlmm_ctxt);
   if (result != DAL_SUCCESS) { goto error; }

   result = DAL_DeviceAttach(DALDEVICEID_TLMM, &tlmm_dal);
   if (result != DAL_SUCCESS) { goto error; }

   result = DalDevice_Open(tlmm_dal, DAL_OPEN_SHARED);
   if (result != DAL_SUCCESS) { goto error; }

   tlmm_ctxt->client_id = client_id;
   tlmm_ctxt->tlmm_dal = tlmm_dal;
   *phandle = tlmm_ctxt;
   return TAL_SUCCESS;
error:
   if (tlmm_ctxt) { DALSYS_Free(tlmm_ctxt); }
   if (tlmm_dal)  { DAL_DeviceDetach(tlmm_dal); }
   *phandle = NULL;
   return TAL_ERROR;
}
