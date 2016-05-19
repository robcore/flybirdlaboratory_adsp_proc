/**
@file rcevt_posix_impl.c
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
$Header: //components/rel/core.adsp/2.6.1/debugtools/rcevt/src/rcevt_posix_impl.c#1 $
$DateTime: 2014/10/16 12:45:40 $
$Change: 6781644 $
$Author: pwbldsvc $
===============================================================================*/

#include "stringl/stringl.h"
#include "pthread.h"

#include "rcevt.h"
#include "rcevt_posix.h"
#include "rcevt_internal.h"

RCEVT_BOOL rce_nfy_eq_posix(rce_nfy_p nfy_p, RCEVT_SIGEX sigex)
{
   if (RCE_NULL != nfy_p)
   {
      RCEVT_SIGEX_SIGPOSIX* sigex_p = (RCEVT_SIGEX_SIGPOSIX*)(&(nfy_p->sigex));
      if (sigex_p->mutex_p == ((RCEVT_SIGEX_SIGPOSIX*)sigex)->mutex_p)
      { 
         return RCEVT_TRUE;
      }
      return RCEVT_FALSE;
   }
   else
   {
      return RCEVT_FALSE;
   }
}

void rce_nfy_init_posix(rce_nfy_p nfy_p, RCEVT_SIGEX sigex)
{
   if (RCE_NULL != nfy_p)
   {
      RCEVT_SIGEX_SIGPOSIX* sigex_p = (RCEVT_SIGEX_SIGPOSIX*)(&(nfy_p->sigex));
      secure_memset((void*)(&nfy_p->sigex), 0, sizeof(struct rce_nfy_sigex_s));
      sigex_p->mutex_p = ((RCEVT_SIGEX_SIGPOSIX*)sigex)->mutex_p;
      sigex_p->cond_p = ((RCEVT_SIGEX_SIGPOSIX*)sigex)->cond_p;
   }
}

void rce_nfy_term_posix(rce_nfy_p nfy_p)
{
   if (RCE_NULL != nfy_p)
   {
      secure_memset((void*)(&nfy_p->sigex), 0, sizeof(struct rce_nfy_sigex_s));
   }
}

rce_nde_p rce_nfy_sig_posix(rce_nde_p nde_p, rce_nfy_p nfy_p)
{
   if (RCE_NULL != nfy_p)
   {
      RCEVT_SIGEX_SIGPOSIX* sigex_p = (RCEVT_SIGEX_SIGPOSIX*)(&(nfy_p->sigex));
      rce_nde_p rc = RCE_NULL;
      pthread_mutex_lock(sigex_p->mutex_p);
      pthread_cond_broadcast(sigex_p->cond_p);
      pthread_mutex_unlock(sigex_p->mutex_p);
      rc = nde_p;
      return rc;
   }
   else
   {
      return RCE_NULL;
   }
}

rce_nde_p rce_nfy_wait_posix(rce_nde_p nde_p, rce_nfy_p nfy_p)
{
   if (RCE_NULL != nfy_p)
   {
      RCEVT_SIGEX_SIGPOSIX* sigex_p = (RCEVT_SIGEX_SIGPOSIX*)(&(nfy_p->sigex));
      rce_nde_p rc = RCE_NULL;
      pthread_mutex_lock(sigex_p->mutex_p);
      pthread_cond_wait(sigex_p->cond_p, sigex_p->mutex_p);
      pthread_mutex_unlock(sigex_p->mutex_p);
      rc = nde_p;
      return rc;
   }
   else
   {
      return RCE_NULL;
   }
}
