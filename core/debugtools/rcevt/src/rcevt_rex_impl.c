/**
@file rcevt_rex_impl.c
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
$Header: //components/rel/core.adsp/2.6.1/debugtools/rcevt/src/rcevt_rex_impl.c#1 $
$DateTime: 2014/10/16 12:45:40 $
$Change: 6781644 $
$Author: pwbldsvc $
===============================================================================*/

#include "stringl/stringl.h"

#include "rcevt_rex.h"
#include "rcevt_internal.h"

RCEVT_BOOL rce_nfy_eq_rex(rce_nfy_p nfy_p, RCEVT_SIGEX sigex)
{
   if (RCE_NULL != nfy_p)
   {
      RCEVT_SIGEX_SIGREX* sigex_p = (RCEVT_SIGEX_SIGREX*)(&(nfy_p->sigex));
      if (sigex_p->signal == ((RCEVT_SIGEX_SIGREX*)sigex)->signal)
      {
         return RCEVT_TRUE;
      }
      return RCEVT_FALSE;
   }
   else
   {
      ERR_FATAL("null handle use", 0, 0, 0);
      return RCEVT_FALSE;
   }
}

void rce_nfy_init_rex(rce_nfy_p nfy_p, RCEVT_SIGEX sigex)
{
   if (RCE_NULL != nfy_p)
   {
      RCEVT_SIGEX_SIGREX* sigex_p = (RCEVT_SIGEX_SIGREX*)(&(nfy_p->sigex));
      if (sizeof(struct rce_nfy_sigex_s) < sizeof(RCEVT_SIGEX_SIGREX))
      {
         ERR_FATAL("payload size configuration", 0, 0, 0);
      }
      secure_memset((void*)(&nfy_p->sigex), 0, sizeof(struct rce_nfy_sigex_s));
      sigex_p->mask = ((RCEVT_SIGEX_SIGREX*)sigex)->mask;
      sigex_p->signal = ((RCEVT_SIGEX_SIGREX*)sigex)->signal;
   }
   else
   {
      ERR_FATAL("null handle use", 0, 0, 0);
   }
}

void rce_nfy_term_rex(rce_nfy_p nfy_p)
{
   if (RCE_NULL != nfy_p)
   {
      secure_memset((void*)(&nfy_p->sigex), 0, sizeof(struct rce_nfy_sigex_s));
   }
   else
   {
      ERR_FATAL("null handle use", 0, 0, 0);
   }
}

rce_nde_p rce_nfy_sig_rex(rce_nde_p nde_p, rce_nfy_p nfy_p)
{
   if (RCE_NULL != nfy_p)
   {
      RCEVT_SIGEX_SIGREX* sigex_p = (RCEVT_SIGEX_SIGREX*)(&(nfy_p->sigex));
      rce_nde_p rc = RCE_NULL;
      rex_set_sigs(sigex_p->signal, sigex_p->mask);
      rc = nde_p;
      return rc;
   }
   else
   {
      ERR_FATAL("null handle use", 0, 0, 0);
      return RCE_NULL;
   }
}

rce_nde_p rce_nfy_wait_rex(rce_nde_p nde_p, rce_nfy_p nfy_p)
{
   if (RCE_NULL != nfy_p)
   {
      RCEVT_SIGEX_SIGREX* sigex_p = (RCEVT_SIGEX_SIGREX*)(&(nfy_p->sigex));
      rce_nde_p rc = RCE_NULL;
      if (rex_self() == sigex_p->signal)
      {
         rex_wait(sigex_p->mask);
         rex_clr_sigs(sigex_p->signal, sigex_p->mask);
         rc = nde_p;
      }
      else
      {
         ERR_FATAL("cannot wait event", 0, 0, 0);
      }
      return rc;
   }
   else
   {
      ERR_FATAL("null handle use", 0, 0, 0);
      return RCE_NULL;
   }
}
