#ifndef DOG_HB_QURT_H
#define DOG_HB_QURT_H
/**
@file dog_hb_qurt.h
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
Qualcomm Confidential and Proprietary.
===============================================================================*/
/*=============================================================================
Edit History
$Header: //components/rel/core.adsp/2.6.1/api/debugtools/dog_hb_qurt.h#1 $
$DateTime: 2014/10/16 12:45:40 $
$Change: 6781644 $
$Author: pwbldsvc $
===============================================================================*/

#include "dog_qurt.h"

#if defined(__cplusplus)
extern "C"
{
#endif

/** @addtogroup dog_api @{ */

/**
  Dynamically registers tasks for watchdog services. A replacement for hard coded
  timeouts in dog.c for common modem interface (CMI) compliance.

  @param[in] anysignal_p qurt anysignal object pointer
  @param[in] anysignal_m qurt anysignal mask

  @return
  Handle for tasks to be identified with the watchdog.

  @dependencies
  None.
*/
#if (defined(__GNUC__) && __GNUC__ >= 4) || defined(__clang__)
__attribute__((warn_unused_result, nonnull(1)))
#endif
dog_report_type dog_hb_register_qurt(qurt_anysignal_t* sig_p, unsigned int sig_m);

/**
  Reports to the watchdog task whether the monitored task is
  functioning properly.

  @param[in]     handle             Dog handle used to tell the watchdog which task is reporting.

  @return
  None.

  @dependencies
  None.
*/
void dog_hb_report(dog_report_type ident);

/**
  Dynamically de-registers tasks for watchdog services for CMI compliance.

  @param[in] handle  Dog handle that the watchdog uses to identify the task.

  @return
  None.

  @dependencies
  None.
*/
void dog_hb_deregister(dog_report_type ident);

/** @} end_addtogroup dog_api */

#if defined(__cplusplus)
}
#endif

#endif
