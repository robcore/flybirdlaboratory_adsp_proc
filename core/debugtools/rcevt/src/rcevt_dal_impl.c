/**
@file rcevt_dal_impl.c
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
$Header: //components/rel/core.adsp/2.6.1/debugtools/rcevt/src/rcevt_dal_impl.c#1 $
$DateTime: 2014/10/16 12:45:40 $
$Change: 6781644 $
$Author: pwbldsvc $
===============================================================================*/

#include "stringl/stringl.h"

#include "rcevt_dal.h"
#include "rcevt_internal.h"

void rce_mutex_init_dal(rce_mutex_p mutex_p)
{
   if (RCE_NULL != mutex_p)
   {
      secure_memset((void*)mutex_p, 0, sizeof(rce_mutex_t));
      if (DAL_SUCCESS != DALSYS_SyncCreate(DALSYS_SYNC_ATTR_RESOURCE, &(mutex_p->mutex), &(mutex_p->mutexObject)))
      {
         ERR_FATAL("cannot init mutex", 0, 0, 0);
      }
   }
}

void rce_mutex_lock_dal(rce_mutex_p mutex_p)
{
   if (RCE_NULL != mutex_p)
   {
      DALSYS_SyncEnter(mutex_p->mutex);
   }
}

void rce_mutex_unlock_dal(rce_mutex_p mutex_p)
{
   if (RCE_NULL != mutex_p)
   {
      DALSYS_SyncLeave(mutex_p->mutex);
   }
}

RCEVT_BOOL rce_nfy_eq_dal(rce_nfy_p nfy_p, RCEVT_SIGEX sigex)
{
   if (RCE_NULL != nfy_p)
   {
      RCEVT_SIGEX_SIGDAL* sigex_p = (RCEVT_SIGEX_SIGDAL*)(&(nfy_p->sigex));
      if (sigex_p->signal == ((RCEVT_SIGEX_SIGDAL*)sigex)->signal) return RCEVT_TRUE;
      return RCEVT_FALSE;
   }
   else
   {
      ERR_FATAL("null handle use", 0, 0, 0);
      return RCEVT_FALSE;
   }
}

void rce_nfy_init_dal(rce_nfy_p nfy_p, RCEVT_SIGEX sigex)
{
   if (RCE_NULL != nfy_p)
   {
      RCEVT_SIGEX_SIGDAL* sigex_p = (RCEVT_SIGEX_SIGDAL*)(&(nfy_p->sigex));
      if (sizeof(struct rce_nfy_sigex_s) < sizeof(RCEVT_SIGEX_SIGDAL))
      {
         ERR_FATAL("payload size configuration", 0, 0, 0);
      }
      secure_memset((void*)(&nfy_p->sigex), 0, sizeof(struct rce_nfy_sigex_s));
      sigex_p->signal = ((RCEVT_SIGEX_SIGDAL*)sigex)->signal;
   }
   else
   {
      ERR_FATAL("null handle use", 0, 0, 0);
   }
}

void rce_nfy_term_dal(rce_nfy_p nfy_p)
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

rce_nde_p rce_nfy_sig_dal(rce_nde_p nde_p, rce_nfy_p nfy_p)
{
   if (RCE_NULL != nfy_p)
   {
      RCEVT_SIGEX_SIGDAL* sigex_p = (RCEVT_SIGEX_SIGDAL*)(&(nfy_p->sigex));
      rce_nde_p rc = RCE_NULL;
      if (DAL_SUCCESS != DALSYS_EventCtrl(sigex_p->signal, DALSYS_EVENT_CTRL_TRIGGER))
      {
         ERR_FATAL("cannot trigger event", 0, 0, 0);
      }
      rc = nde_p;
      return rc;
   }
   else
   {
      ERR_FATAL("null handle use", 0, 0, 0);
      return RCE_NULL;
   }
}

rce_nde_p rce_nfy_wait_dal(rce_nde_p nde_p, rce_nfy_p nfy_p)
{
   if (RCE_NULL != nfy_p)
   {
      RCEVT_SIGEX_SIGDAL* sigex_p = (RCEVT_SIGEX_SIGDAL*)(&(nfy_p->sigex));
      rce_nde_p rc = RCE_NULL;
      if (DAL_SUCCESS != DALSYS_EventWait(sigex_p->signal))
      {
         ERR_FATAL("cannot wait event", 0, 0, 0);
      }
      if (DAL_SUCCESS != DALSYS_EventCtrl(sigex_p->signal, DALSYS_EVENT_CTRL_RESET))
      {
         ERR_FATAL("cannot reset event", 0, 0, 0);
      }
      rc = nde_p;
      return rc;
   }
   else
   {
      ERR_FATAL("null handle use", 0, 0, 0);
      return RCE_NULL;
   }
}
