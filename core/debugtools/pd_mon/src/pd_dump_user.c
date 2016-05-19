/** vi: tw=128 ts=3 sw=3 et
@file pd_dump_user.c
@brief This file contains the API details for the Protection Domain Monitor, API 1.0
*/
/*=============================================================================
NOTE: The @brief description above does not appear in the PDF.
The tms_mainpage.dox file contains the group/module descriptions that
are displayed in the output PDF generated using Doxygen and LaTeX. To
edit or update any of the group/module text in the PDF, edit the
tms_mainpage.dox file or contact Tech Pubs.
===============================================================================*/
/*=============================================================================
Copyright (c) 2014 Qualcomm Technologies Incorporated.
All rights reserved.
Qualcomm Confidential and Proprietary
=============================================================================*/
/*=============================================================================
Edit History
$Header: //components/rel/core.adsp/2.6.1/debugtools/pd_mon/src/pd_dump_user.c#1 $
$DateTime: 2014/10/16 12:45:40 $
$Change: 6781644 $
$Author: pwbldsvc $
===============================================================================*/

#include "pd_mon_qurt.h"
#include "pd_dump.h"

/**
API, pd_dump_init
@param[in] PD_DUMP_NAME NULL Terminated Device Name
@return
PD_DUMP_HANDLE Opaque Device Handle
*/
PD_DUMP_HANDLE pd_dump_init(PD_DUMP_NAME name)
{
   PD_DUMP_HANDLE rc = -1;

   if (PD_DUMP_DEVICE_NAME_LEN > strnlen(name, PD_DUMP_DEVICE_NAME_LEN))
   {
      char device[PD_DUMP_DEVICE_PATH_LEN + PD_DUMP_DEVICE_NAME_LEN];

      strlcpy(device, PD_DUMP_DEVICE, sizeof(device));
      strlcat(device, name, sizeof(device));

      rc = qurt_qdi_open(device);

      qurt_printf("%s, device name %s, return %d\n", __func__, device, rc);
   }

   return rc;
}

/**
API, pd_dump_destroy
@param[in] PD_DUMP_HANDLE Opaque Device Handle
@return
PD_DUMP_STATUS Error Indication
*/
PD_DUMP_STATUS pd_dump_destroy(PD_DUMP_HANDLE handle)
{
   PD_DUMP_STATUS rc = PD_DUMP_STATUS_ERROR;

   rc = 0 <= qurt_qdi_close(handle) ? PD_DUMP_STATUS_SUCCESS : PD_DUMP_STATUS_ERROR;

   qurt_printf("%s, return %d\n", __func__, rc);

   return rc;
}
