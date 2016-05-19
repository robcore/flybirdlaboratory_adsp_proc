#ifndef PD_DUMP_H
#define PD_DUMP_H
/** vi: tw=128 ts=3 sw=3 et
@file pd_dump.h
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
$Header: //components/rel/core.adsp/2.6.1/debugtools/pd_mon/src/pd_dump.h#1 $
$DateTime: 2014/10/16 12:45:40 $
$Change: 6781644 $
$Author: pwbldsvc $
===============================================================================*/

#include "stdlib.h"
#include "stringl/stringl.h"

#include "qurt.h"
#include "qurt_qdi_driver.h"

#include "msg.h"
#include "tms_utils.h"
#include "rfsa_client.h"


// COMMON
#define PD_DUMP_FILE_ENABLE_TEMPLATE   "%s%s.enable"
#define PD_DUMP_FILE_COUNT_TEMPLATE    "%s%s.count"
#define PD_DUMP_FILE_ELF_TEMPLATE      "%s%s.%02d.elf"

#define PD_DUMP_DEVICE_PATH_LEN     64
#define PD_DUMP_DEVICE_NAME_LEN     16
#define PD_DUMP_DEVICE_ASID_MAX     32 /*QURT_MAX_ASIDS*/
#define PD_DUMP_FILE_NAME_MAX       128

#define PD_DUMP_DEVICE "dump/"

#if defined(__cplusplus)
extern "C" {
#endif

#if defined(__cplusplus)
}
#endif

#endif
