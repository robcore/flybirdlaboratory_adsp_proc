/**
@file rcevt_posix_void.c
@brief This file contains the API for the Run Control Event Notification, API 2.0
*/
/*=============================================================================
NOTE: The @brief description above does not appear in the PDF.
The tms_mainpage.dox file contains the group/module descriptions that
are displayed in the output PDF generated using Doxygen and LaTeX. To
edit or update any of the group/module text in the PDF, edit the
tms_mainpage.dox file or contact Tech Pubs.
===============================================================================*/
/*=============================================================================
Copyright (c) 2013 Qualcomm Technologies Incorporated.
All rights reserved.
Qualcomm Confidential and Proprietary
=============================================================================*/
/*=============================================================================
Edit History
$Header: //components/rel/core.adsp/2.6.1/debugtools/rcevt/src/rcevt_posix_void.c#1 $
$DateTime: 2014/10/16 12:45:40 $
$Change: 6781644 $
$Author: pwbldsvc $
===============================================================================*/

#include "rcevt.h"
#include "rcevt_internal.h"

#include "err.h"

RCEVT_BOOL rce_nfy_eq_posix(rce_nfy_p nfy_p, RCEVT_SIGEX sigex)
{
   if (RCE_NULL != nfy_p)
   {
      ERR_FATAL("no implementation", 0, 0, 0);
      return RCEVT_FALSE;
   }
   else
   {
      ERR_FATAL("null handle use", 0, 0, 0);
      return RCEVT_FALSE;
   }
}

void rce_nfy_init_posix(rce_nfy_p nfy_p, RCEVT_SIGEX sigex)
{
   if (RCE_NULL != nfy_p)
   {
      ERR_FATAL("no implementation", 0, 0, 0);
   }
   else
   {
      ERR_FATAL("null handle use", 0, 0, 0);
   }
   sigex = sigex;                                                                // unused
}

void rce_nfy_term_posix(rce_nfy_p nfy_p)
{
   if (RCE_NULL != nfy_p)
   {
      ERR_FATAL("no implementation", 0, 0, 0);
   }
   else
   {
      ERR_FATAL("null handle use", 0, 0, 0);
   }
}

rce_nde_p rce_nfy_sig_posix(rce_nde_p nde_p, rce_nfy_p nfy_p)
{
   if (RCE_NULL != nfy_p)
   {
      nde_p = nde_p;
      ERR_FATAL("no implementation", 0, 0, 0);
      return RCE_NULL;
   }
   else
   {
      ERR_FATAL("null handle use", 0, 0, 0);
      return RCE_NULL;
   }
}

rce_nde_p rce_nfy_wait_posix(rce_nde_p nde_p, rce_nfy_p nfy_p)
{
   if (RCE_NULL != nfy_p)
   {
      nde_p = nde_p;
      ERR_FATAL("no implementation", 0, 0, 0);
      return RCE_NULL;
   }
   else
   {
      ERR_FATAL("null handle use", 0, 0, 0);
      return RCE_NULL;
   }
}
