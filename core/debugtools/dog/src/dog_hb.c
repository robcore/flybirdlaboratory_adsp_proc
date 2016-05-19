/** vi: tw=128 ts=3 sw=3 et
@file dog_hb.c
@brief This file contains the API details for the Dog Services, API 2.0
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
$Header: //components/rel/core.adsp/2.6.1/debugtools/dog/src/dog_hb.c#1 $
$DateTime: 2014/10/16 12:45:40 $
$Change: 6781644 $
$Author: pwbldsvc $
===============================================================================*/

#include "msg.h"
#include "dog_qurt.h"
#include "dog_hb_qurt.h"

#if defined(DOG_TRACER_SWEVT)
#include "tracer.h"
#include "dog_tracer_swe.h"
#endif

void dog_hb_root_init(void)
{
}

void dog_hb_root_term(void)
{
}
