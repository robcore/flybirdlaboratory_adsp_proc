#ifndef DOG_MESSAGES_H
#define DOG_MESSAGES_H
/** vi: tw=128 ts=3 sw=3 et
@file dog_messages.h
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
$Header: //components/rel/core.adsp/2.6.1/api/debugtools/dog_messages.h#1 $
$DateTime: 2014/10/16 12:45:40 $
$Change: 6781644 $
$Author: pwbldsvc $
===============================================================================*/

#if defined(__cplusplus)
extern "C"
{
#endif

/** @addtogroup dog_api @{ */

/**
OBSERVERS OK: rcevt or rcecb
*/
#define DOG_HW_INIT_COMPLETE         "dog:hw_init_complete"

/** @} end_addtogroup dog_api */

#if defined(__cplusplus)
}
#endif

#endif
