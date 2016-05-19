/**
@file rcevt_qurt_impl.c
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
$Header: //components/rel/core.adsp/2.6.1/debugtools/rcevt/src/rcevt_qurt_impl.c#1 $
$DateTime: 2014/10/16 12:45:40 $
$Change: 6781644 $
$Author: pwbldsvc $
===============================================================================*/

#include "stringl/stringl.h"

#include "rcevt_qurt.h"
#include "rcevt_internal.h"

RCEVT_BOOL rce_nfy_eq_qurt(rce_nfy_p nfy_p, RCEVT_SIGEX sigex)
{
   if (RCE_NULL != nfy_p)
   {
      RCEVT_SIGEX_SIGQURT* sigex_p = (RCEVT_SIGEX_SIGQURT*)(&(nfy_p->sigex));
      if (sigex_p->signal == ((RCEVT_SIGEX_SIGQURT*)sigex)->signal)
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

void rce_nfy_init_qurt(rce_nfy_p nfy_p, RCEVT_SIGEX sigex)
{
   if (RCE_NULL != nfy_p)
   {
      RCEVT_SIGEX_SIGQURT* sigex_p = (RCEVT_SIGEX_SIGQURT*)(&(nfy_p->sigex));
      if (sizeof(struct rce_nfy_sigex_s) < sizeof(RCEVT_SIGEX_SIGQURT))
      {
         ERR_FATAL("payload size configuration", 0, 0, 0);
      }
      secure_memset((void*)(&nfy_p->sigex), 0, sizeof(struct rce_nfy_sigex_s));
      sigex_p->mask = ((RCEVT_SIGEX_SIGQURT*)sigex)->mask;
      sigex_p->signal = ((RCEVT_SIGEX_SIGQURT*)sigex)->signal;
   }
   else
   {
      ERR_FATAL("null handle use", 0, 0, 0);
   }
}

void rce_nfy_term_qurt(rce_nfy_p nfy_p)
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

rce_nde_p rce_nfy_sig_qurt(rce_nde_p nde_p, rce_nfy_p nfy_p)
{
   if (RCE_NULL != nfy_p)
   {
      RCEVT_SIGEX_SIGQURT* sigex_p = (RCEVT_SIGEX_SIGQURT*)(&(nfy_p->sigex));
      rce_nde_p rc = RCE_NULL;
      qurt_anysignal_set(sigex_p->signal, sigex_p->mask);
      rc = nde_p;
      return rc;
   }
   else
   {
      ERR_FATAL("null handle use", 0, 0, 0);
      return RCE_NULL;
   }
}

rce_nde_p rce_nfy_wait_qurt(rce_nde_p nde_p, rce_nfy_p nfy_p)
{
   if (RCE_NULL != nfy_p)
   {
      RCEVT_SIGEX_SIGQURT* sigex_p = (RCEVT_SIGEX_SIGQURT*)(&(nfy_p->sigex));
      rce_nde_p rc = RCE_NULL;
      qurt_anysignal_wait(sigex_p->signal, sigex_p->mask);
      qurt_anysignal_clear(sigex_p->signal, sigex_p->mask);
      rc = nde_p;
      return rc;
   }
   else
   {
      ERR_FATAL("null handle use", 0, 0, 0);
      return RCE_NULL;
   }
}
