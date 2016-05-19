/** vi: tw=128 ts=3 sw=3 et
@file rcinit_rex_void.c
@brief This file contains the API for the Run Control Framework, API 2.0
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
$Header: //components/rel/core.adsp/2.6.1/debugtools/rcinit/src/rcinit_rex_void.c#1 $
$DateTime: 2014/10/16 12:45:40 $
$Change: 6781644 $
$Author: pwbldsvc $
===============================================================================*/

typedef unsigned int rex_tcb_type;

#include "rcinit_internal.h"

rex_tcb_type* rcinit_lookup_rextask_info(RCINIT_INFO info)
{
   ERR_FATAL("no implementation", 0, 0, 0);
   return RCINIT_NULL;
}

rex_tcb_type* rcinit_lookup_rextask(RCINIT_NAME name)
{
   ERR_FATAL("no implementation", 0, 0, 0);
   return RCINIT_NULL;
}

RCINIT_GROUP rcinit_lookup_group_rextask(rex_tcb_type* tid)
{
   ERR_FATAL("no implementation", 0, 0, 0);
   return RCINIT_GROUP_NONE;
}

RCINIT_INFO rcinit_lookup_info_rextask(rex_tcb_type* tid)
{
   ERR_FATAL("no implementation", 0, 0, 0);
   return RCINIT_NULL;
}

void rcinit_internal_start_rextask(const rcinit_info_t* rcinit_p, void* entry)
{
   ERR_FATAL("no implementation", 0, 0, 0);
}
