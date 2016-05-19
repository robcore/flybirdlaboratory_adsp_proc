/** vi: tw=128 ts=3 sw=3 et
@file dog_hb_user.c
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
$Header: //components/rel/core.adsp/2.6.1/debugtools/dog/src/dog_hb_user_rex.c#1 $
$DateTime: 2014/10/16 12:45:40 $
$Change: 6781644 $
$Author: pwbldsvc $
===============================================================================*/

/**
DOG_SW Starvation Monitoring via Ping/Pong Signaling
*/

#include "stdarg.h"
#include "stdlib.h"
#include "stringl/stringl.h"

#include "qurt.h"
#include "qurt_qdi_driver.h"

#include "err.h"
#include "msg.h"
#include "dog_hb_qurt.h"
#include "timer.h"
#include "tms_utils.h"

#include "rex.h"

dog_report_type dog_hb_register_rex(rex_sigs_type sig_m)
{
   rex_task_type* tcb_p;
   char task_name[REX_TASK_NAME_LEN + 1];

   tcb_p = rex_self();

   if (NULL != tcb_p && REX_SUCCESS == rex_get_task_name(tcb_p, task_name, sizeof(task_name), NULL))
   {
      return (dog_report_type)dog_hb_init(task_name, 1, tcb_p, sig_m);           // rex_task_type*
   }
   else
   {
      return (dog_report_type) - 1;
   }
}

void dog_hb_report(dog_report_type ident)
{
   if (DOG_HB_STATUS_SUCCESS <= dog_hb_pong((DOG_HB_HANDLE)ident))
   {
      ;
   }
}

void dog_hb_deregister(dog_report_type ident)
{
   if (DOG_HB_STATUS_SUCCESS <= dog_hb_destroy((DOG_HB_HANDLE)ident))
   {
      ;
   }
}
