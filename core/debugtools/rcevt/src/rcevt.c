/**
@file rcevt.c
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
$Header: //components/rel/core.adsp/2.6.1/debugtools/rcevt/src/rcevt.c#1 $
$DateTime: 2014/10/16 12:45:40 $
$Change: 6781644 $
$Author: pwbldsvc $
===============================================================================*/

#include "rcevt_dal.h"
#include "rcevt_internal.h"
#include "stringl/stringl.h"

/**
API, Map opaque handle to name
@param[in] handle Opaque handle of the event
@return
RCEVT_NULL -- Error
RCEVT_NAME -- Pointer to NULL terminated string, name of the event
*/
RCEVT_NAME rcevt_map_handle(RCEVT_HANDLE const handle)
{
   RCEVT_NAME rc = RCE_NULL;                                                     // return result
   rce_nde_p nde_p;

   nde_p = rcevt2nde(handle);

   rcevt_init();

   rc = nde_p->name;                                                             // return result

   return rc;                                                                    // return status or failure
}

/**
API, Map name to opaque handle
@param[in] name NULL terminated string, name of the event
@return
RCEVT_NULL -- Error
RCEVT_HANDLE -- Opaque handle to existing event
*/
RCEVT_HANDLE rcevt_map_name(RCEVT_NAME const name)
{
   RCEVT_HANDLE rc = RCE_NULL;                                                   // return result
   rce_nde_p nde_p;

   rcevt_init();

   nde_p = rce_nde_hashtab_get(rce_nmehash(name));

   while (RCE_NULL != nde_p)                                                     // search for existing node
   {
      if (nde_p->name != name)                                                   // same address compare
      {
         int len = rce_nmelen(nde_p->name);                                      // string compare required

         if (0 == rce_nmecmp(nde_p->name, name, len))                            // lexical comparision
         {
            rc = nde2rcevt(nde_p);                                               // return result

            break;                                                               // break loop for return
         }
      }

      else                                                                       // same address
      {
         rc = nde2rcevt(nde_p);                                                  // return result

         break;                                                                  // break loop for return
      }

      nde_p = nde_p->next;                                                       // iterate to locate
   }

   return rc;                                                                    // return status or failure
}

/**
API, Create an event, with name

Prerequsite call before posting event -- create the event
before use to avoid a potential "race condition" between
contexts that will post the event and concurrently wait on
the event being posted.

For performance, cache the resulting handle for use within
the API. Name based use cases will take a penalty when doing
a dictionary lookup on every call.

@param[in] name NULL terminated string, name of the event
@return
RCEVT_NULL -- Error
RCEVT_HANDLE -- Opaque handle to existing event
*/
RCEVT_HANDLE rcevt_create_name(RCEVT_NAME const name)
{
   RCEVT_HANDLE rc = RCE_NULL;                                                   // return result
   RCEVT_HANDLE handle;

   rce_mutex_lock_dal(&(rce_internal.mutex_create));

   handle = rcevt_map_name(name);

   if (RCE_NULL != handle)                                                       // check succes of loop for found node
   {
      rc = handle;                                                               // return result
   }

   else                                                                          // create new
   {
      rce_nde_p nde_p;

      nde_p = rce_nde_pool_alloc();                                              // allocate new node

      if (RCE_NULL != nde_p)
      {
         // potential optimization would be to perform these allocations from a pool; help prevent heap fragments
         // as events are persistent for the duration of execution, this allocation is also persistent

         unsigned long buf_s = rce_nmelen(name) + 1;                             // length of RCEVT_NAME
         char* buf_p = rce_malloc(buf_s);                                        // space for RCEVT_NAME

         if (RCE_NULL != buf_p)
         {
            strlcpy(buf_p, name, buf_s);                                         // private copy of name

            nde_p->name = buf_p;                                                 // memorize name address

            nde_p->notify_head = RCE_NULL;                                       // initialize notify queue

            rce_nde_hashtab_put(nde_p, rce_nmehash(nde_p->name));

            rc = nde2rcevt(nde_p);                                               // return result
         }
         else
         {
            rce_nde_pool_free(nde_p);                                            // prevent pool leak
         }
      }
   }

   rce_mutex_unlock_dal(&(rce_internal.mutex_create));

   return rc;                                                                    // return result
}

/**
API, Search an event, with handle
See prerequsite note with rcevt_create_name
@param[in] handle Opaque handle of the event
@return
RCEVT_BOOL -- Boolean reflecting event previously created
*/
RCEVT_BOOL rcevt_search_handle(RCEVT_HANDLE const handle)
{
   RCEVT_BOOL rc = RCEVT_FALSE;                                                  // return result

   if (RCE_NULL != rcevt_map_handle(handle))
   {
      rc = RCEVT_TRUE;                                                           // return result
   }

   return rc;                                                                    // return status or failure
}

/**
API, Search an event, with name
See prerequsite note with rcevt_create_name
@param[in] name NULL terminated string, name of the event
@return
RCEVT_BOOL -- Boolean reflecting event previously created
*/
RCEVT_BOOL rcevt_search_name(RCEVT_NAME const name)
{
   RCEVT_BOOL rc = RCEVT_FALSE;                                                  // return result

   if (RCE_NULL != rcevt_map_name(name))
   {
      rc = RCEVT_TRUE;                                                           // return result
   }

   return rc;                                                                    // return status or failure
}

/**
API, Count of registrants for event, with handle
See prerequsite note with rcevt_create_name
@param[in] handle Opaque handle of the event
@return
int -- Count of registrants for specific event
*/
int rcevt_getcontexts_handle(RCEVT_HANDLE const handle)
{
   int rc = 0;                                                                   // return result
   rce_nde_p nde_p = rcevt2nde(handle);

   if (RCE_NULL != nde_p)
   {
      rce_nfy_p nfy_p;

      rce_mutex_lock_dal(&(nde_p->mutex));

      nfy_p = nde_p->notify_head;                                                // locate notify context

      while (RCE_NULL != nfy_p)                                                  // loop for check
      {
         if ((RCEVT_SIGEX_TYPE_SIGDAL == nfy_p->sigex_type) ||                   // types utilized by rcevt
             (RCEVT_SIGEX_TYPE_SIGPOSIX == nfy_p->sigex_type) ||
             (RCEVT_SIGEX_TYPE_SIGQURT == nfy_p->sigex_type) ||
             (RCEVT_SIGEX_TYPE_SIGREX == nfy_p->sigex_type))
         {
            rc++;                                                                // return result
         }

         nfy_p = nfy_p->next;                                                    // iterate to next
      }

      rce_mutex_unlock_dal(&(nde_p->mutex));
   }

   return rc;                                                                    // return status or failure
}

/**
API, Count of registrants for event, with name
See prerequsite note with rcevt_create_name
@param[in] name NULL terminated string, name of the event
@return
int -- Count of registrants for specific event
*/
int rcevt_getcontexts_name(RCEVT_NAME const name)
{
   int rc = 0;                                                                   // return result
   RCEVT_HANDLE handle = rcevt_create_name(name);

   if (RCE_NULL != handle)
   {
      rc = rcevt_getcontexts_handle(handle);
   }

   return rc;                                                                    // return status or failure
}

/**
API, Count of times event signaled, with handle
See prerequsite note with rcevt_create_name
@param[in] handle Opaque handle of the event
@return
RCEVT_THRESHOLD -- Count of registrants for specific event
*/
RCEVT_THRESHOLD rcevt_getcount_handle(RCEVT_HANDLE const handle)
{
   RCEVT_THRESHOLD rc = RCE_THRESHOLD_INIT;                                      // default
   rce_nde_p nde_p = rcevt2nde(handle);

   rce_mutex_lock_dal(&(nde_p->mutex));

   rc = nde_p->threshold;

   rce_mutex_unlock_dal(&(nde_p->mutex));

   return rc;                                                                    // return result
}

/**
API, Count of times event signaled, with name
See prerequsite note with rcevt_create_name
@param[in] name NULL terminated string, name of the event
@return
RCEVT_THRESHOLD -- Count of registrants for specific event
*/
RCEVT_THRESHOLD rcevt_getcount_name(RCEVT_NAME const name)
{
   RCEVT_THRESHOLD rc = RCE_THRESHOLD_INIT;                                      // default
   RCEVT_HANDLE handle = rcevt_create_name(name);

   if (RCE_NULL != handle)
   {
      rce_nde_p nde_p = rcevt2nde(handle);

      rce_mutex_lock_dal(&(nde_p->mutex));

      rc = nde_p->threshold;

      rce_mutex_unlock_dal(&(nde_p->mutex));
   }

   return rc;                                                                    // return result
}

/**
INTERNAL, Not Exposed for API Use
*/
rce_nfy_p rcevt_internal_register_sigex_update(RCEVT_HANDLE const handle, RCEVT_THRESHOLD threshold, RCEVT_SIGEX_TYPE type, RCEVT_SIGEX sigex)
{
   rce_nfy_p rc = RCE_NULL;                                                      // return result
   rce_nde_p nde_p;
   rce_nfy_p nfy_p;

   nde_p = rcevt2nde(handle);
   nfy_p = nde_p->notify_head;                                                   // locate notify context

   while (RCE_NULL != nfy_p)                                                     // loop for check
   {
      if (type == nfy_p->sigex_type)                                             // comparision based on type
      {
         if (RCEVT_SIGEX_TYPE_SIGDAL == nfy_p->sigex_type && RCEVT_TRUE == rce_nfy_eq_dal(nfy_p, sigex))
         {
            rce_nfy_init_dal(nfy_p, sigex);
            nfy_p->threshold = threshold;                                        // update member
            rc = nfy_p;                                                          // return result
            break;
         }

         else if (RCEVT_SIGEX_TYPE_SIGPOSIX == nfy_p->sigex_type && RCEVT_TRUE == rce_nfy_eq_posix(nfy_p, sigex))
         {
            rce_nfy_init_posix(nfy_p, sigex);
            nfy_p->threshold = threshold;                                        // update member
            rc = nfy_p;                                                          // return result
            break;
         }

         else if (RCEVT_SIGEX_TYPE_SIGQURT == nfy_p->sigex_type && RCEVT_TRUE == rce_nfy_eq_qurt(nfy_p, sigex))
         {
            rce_nfy_init_qurt(nfy_p, sigex);
            nfy_p->threshold = threshold;                                        // update member
            rc = nfy_p;                                                          // return result
            break;
         }

         else if (RCEVT_SIGEX_TYPE_SIGREX == nfy_p->sigex_type && RCEVT_TRUE == rce_nfy_eq_rex(nfy_p, sigex))
         {
            rce_nfy_init_rex(nfy_p, sigex);
            nfy_p->threshold = threshold;                                        // update member
            rc = nfy_p;                                                          // return result
            break;
         }
      }

      nfy_p = nfy_p->next;                                                       // iterate to next
   }

   return rc;
}

/**
INTERNAL, Not Exposed for API Use
*/
rce_nfy_p rcevt_internal_register_sigex_add(RCEVT_HANDLE const handle, RCEVT_THRESHOLD threshold, RCEVT_SIGEX_TYPE type, RCEVT_SIGEX sigex)
{
   rce_nfy_p rc = RCE_NULL;                                                      // return result
   rce_nfy_p nfy_p;

   nfy_p = rce_nfy_pool_alloc();

   if (RCE_NULL != nfy_p)                                                        // populate
   {
      rce_nde_p nde_p = rcevt2nde(handle);

      nfy_p->next = nde_p->notify_head;                                          // insert to head of list

      nde_p->notify_head = nfy_p;                                                // update head

      nfy_p->sigex_type = type;                                                  // update member

      nfy_p->threshold = threshold;                                              // update member

      if (RCEVT_SIGEX_TYPE_SIGDAL == type)
      {
         rce_nfy_init_dal(nfy_p, sigex);
      }

      else if (RCEVT_SIGEX_TYPE_SIGPOSIX == type)
      {
         rce_nfy_init_posix(nfy_p, sigex);
      }

      else if (RCEVT_SIGEX_TYPE_SIGQURT == type)
      {
         rce_nfy_init_qurt(nfy_p, sigex);
      }

      else if (RCEVT_SIGEX_TYPE_SIGREX == type)
      {
         rce_nfy_init_rex(nfy_p, sigex);
      }

      rc = nfy_p;                                                                // return result
   }

   return rc;                                                                    // return result
}

/**
API, Register notification to event, with handle
See prerequsite note with rcevt_create_name
@param[in] handle Opaque handle of the event
@param[in] type Notification type (DAL, POSIX, QURT, REX)
@param[in] signal Notification sigex structure pointer, type specific values
@return
RCEVT_NULL -- Error
RCEVT_HANDLE -- Opaque handle to existing event
*/
RCEVT_HANDLE rcevt_register_sigex_handle(RCEVT_HANDLE const handle, RCEVT_SIGEX_TYPE type, RCEVT_SIGEX sigex)
{
   RCEVT_HANDLE rc = RCE_NULL;                                                   // return result
   RCEVT_THRESHOLD threshold = RCE_THRESHOLD_DEFAULT;                            // default
   rce_nde_p nde_p = rcevt2nde(handle);

   if (RCE_NULL != handle)
   {
      rce_nfy_p nfy_p = RCE_NULL;

      rce_mutex_lock_dal(&(nde_p->mutex));

      nfy_p = rcevt_internal_register_sigex_update(handle, threshold, type, sigex); // update an existing

      if (RCE_NULL != nfy_p)
      {
         rc = handle;                                                            // return result
      }
      else
      {
         nfy_p = rcevt_internal_register_sigex_add(handle, threshold, type, sigex); // add a new

         if (RCE_NULL != nfy_p)
         {
            rc = handle;                                                         // return result
         }
         else
         {
            ERR_FATAL("cannot update/add event in register", 0, 0, 0);
         }
      }

      rce_mutex_unlock_dal(&(nde_p->mutex));
   }

   return rc;                                                                    // return result
}

/**
API, Register notification to event, with name
See prerequsite note with rcevt_create_name
@param[in] name NULL terminated string, name of the event
@param[in] type Notification type (DAL, POSIX, QURT, REX)
@param[in] signal Notification sigex structure pointer, type specific values
@return
RCEVT_NULL -- Error
RCEVT_HANDLE -- Opaque handle to existing event
*/
RCEVT_HANDLE rcevt_register_sigex_name(RCEVT_NAME const name, RCEVT_SIGEX_TYPE type, RCEVT_SIGEX sigex)
{
   RCEVT_HANDLE rc = RCE_NULL;                                                   // return result
   RCEVT_HANDLE handle = rcevt_create_name(name);

   if (RCE_NULL != handle)
   {
      rc = rcevt_register_sigex_handle(handle, type, sigex);
   }

   return rc;                                                                    // return result
}

/**
INTERNAL, Not Exposed for API Use
*/
RCEVT_HANDLE rcevt_internal_unregister_sigex(RCEVT_HANDLE const handle, RCEVT_SIGEX_TYPE type, RCEVT_SIGEX sigex)
{
   RCEVT_HANDLE rc = RCE_NULL;                                                   // return result
   rce_nfy_p nfy_prev = RCE_NULL;
   rce_nde_p nde_p = rcevt2nde(handle);
   rce_nfy_p nfy_p;

   nfy_p = nde_p->notify_head;                                                   // search out on notify queue

   while (RCE_NULL != nfy_p)                                                     // loop for next
   {
      if (type == nfy_p->sigex_type)                                             // check based on type
      {
         if (RCEVT_SIGEX_TYPE_SIGDAL == type && RCEVT_TRUE == rce_nfy_eq_dal(nfy_p, sigex))
         {
            if (RCE_NULL == nfy_prev)                                            // head of list check
            {
               nde_p->notify_head = nfy_p->next;                                 // remove from head
            }
            else
            {
               nfy_prev->next = nfy_p->next;                                     // remove from list
            }

            nfy_p->next = RCE_NULL;                                              // depopulate

            rce_nfy_term_dal(nfy_p);                                             // signal internals

            rce_nfy_pool_free(nfy_p);                                            // restore to pool

            rc = nde2rcevt(nde_p);                                               // return result

            break;
         }

         else if (RCEVT_SIGEX_TYPE_SIGPOSIX == type && RCEVT_TRUE == rce_nfy_eq_posix(nfy_p, sigex))
         {
            if (RCE_NULL == nfy_prev)                                            // head of list check
            {
               nde_p->notify_head = nfy_p->next;                                 // remove from head
            }
            else
            {
               nfy_prev->next = nfy_p->next;                                     // remove from list
            }

            nfy_p->next = RCE_NULL;                                              // depopulate

            rce_nfy_term_posix(nfy_p);                                           // signal internals

            rce_nfy_pool_free(nfy_p);                                            // restore to pool

            rc = nde2rcevt(nde_p);                                               // return result

            break;
         }

         else if (RCEVT_SIGEX_TYPE_SIGQURT == type && RCEVT_TRUE == rce_nfy_eq_qurt(nfy_p, sigex))
         {
            if (RCE_NULL == nfy_prev)                                            // head of list check
            {
               nde_p->notify_head = nfy_p->next;                                 // remove from head
            }
            else
            {
               nfy_prev->next = nfy_p->next;                                     // remove from list
            }

            nfy_p->next = RCE_NULL;                                              // depopulate

            rce_nfy_term_qurt(nfy_p);                                            // signal internals

            rce_nfy_pool_free(nfy_p);                                            // restore to pool

            rc = nde2rcevt(nde_p);                                               // return result

            break;
         }

         else if (RCEVT_SIGEX_TYPE_SIGREX == type && RCEVT_TRUE == rce_nfy_eq_rex(nfy_p, sigex))
         {
            if (RCE_NULL == nfy_prev)                                            // head of list check
            {
               nde_p->notify_head = nfy_p->next;                                 // remove from head
            }
            else
            {
               nfy_prev->next = nfy_p->next;                                     // remove from list
            }

            nfy_p->next = RCE_NULL;                                              // depopulate

            rce_nfy_term_rex(nfy_p);                                             // signal internals

            rce_nfy_pool_free(nfy_p);                                            // restore to pool

            rc = nde2rcevt(nde_p);                                               // return result

            break;
         }
      }

      nfy_prev = nfy_p;

      nfy_p = nfy_p->next;                                                       // iterate to check next
   }

   return rc;                                                                    // return result
}

/**
API, Unegister notification to event, with handle
See prerequsite note with rcevt_create_name
@param[in] handle Opaque handle of the event
@param[in] type Notification type (DAL, POSIX, QURT, REX)
@param[in] signal Notification sigex structure pointer, type specific values
@return
RCEVT_NULL -- Error
RCEVT_HANDLE -- Opaque handle to existing event
*/
RCEVT_HANDLE rcevt_unregister_sigex_handle(RCEVT_HANDLE const handle, RCEVT_SIGEX_TYPE type, RCEVT_SIGEX sigex)
{
   RCEVT_HANDLE rc = RCE_NULL;                                                   // return result
   rce_nde_p nde_p = rcevt2nde(handle);

   rce_mutex_lock_dal(&(nde_p->mutex));

   rc = rcevt_internal_unregister_sigex(handle, type, sigex);                    // existing

   rce_mutex_unlock_dal(&(nde_p->mutex));

   return rc;                                                                    // return result
}

/**
API, Unegister notification to event, with name
See prerequsite note with rcevt_create_name
@param[in] name NULL terminated string, name of the event
@param[in] type Notification type (DAL, POSIX, QURT, REX)
@param[in] signal Notification sigex structure pointer, type specific values
@return
RCEVT_NULL -- Error
RCEVT_HANDLE -- Opaque handle to existing event
*/
RCEVT_HANDLE rcevt_unregister_sigex_name(RCEVT_NAME const name, RCEVT_SIGEX_TYPE type, RCEVT_SIGEX sigex)
{
   RCEVT_HANDLE rc = RCE_NULL;                                                   // return result
   RCEVT_HANDLE handle = rcevt_create_name(name);

   if (RCE_NULL != handle)
   {
      rc = rcevt_unregister_sigex_handle(handle, type, sigex);                   // existing
   }

   return rc;                                                                    // return result
}

/**
API, Signal event, with handle
See prerequsite note with rcevt_create_name
@param[in] handle Opaque handle of the event
@return
RCEVT_NULL -- Error
RCEVT_HANDLE -- Opaque handle to existing event
*/
RCEVT_HANDLE rcevt_signal_handle(RCEVT_HANDLE const handle)
{
   RCEVT_HANDLE rc = RCE_NULL;                                                   // return result
   rce_nde_p nde_p = rcevt2nde(handle);

   if (RCE_NULL != nde_p)
   {
      if (RCE_NDE_COOKIE == nde_p->nde_cookie)
      {
         rce_nfy_p nfy_p;

         rce_mutex_lock_dal(&(nde_p->mutex));

         nde_p->threshold += 1;                                                  // increment threshold

         nfy_p = nde_p->notify_head;                                             // traverse notify queue

         while (RCE_NULL != nfy_p)                                               // iterate
         {
            if (RCE_NFY_COOKIE == nfy_p->nfy_cookie)                             // corruption check before use
            {
               if (nde_p->threshold >= nfy_p->threshold)                         // signal on condition
               {
                  if (RCEVT_SIGEX_TYPE_SIGDAL == nfy_p->sigex_type)
                  {
                     rce_nfy_sig_dal(nde_p, nfy_p);
                  }

                  else if (RCEVT_SIGEX_TYPE_SIGPOSIX == nfy_p->sigex_type)
                  {
                     rce_nfy_sig_posix(nde_p, nfy_p);
                  }

                  else if (RCEVT_SIGEX_TYPE_SIGQURT == nfy_p->sigex_type)
                  {
                     rce_nfy_sig_qurt(nde_p, nfy_p);
                  }

                  else if (RCEVT_SIGEX_TYPE_SIGREX == nfy_p->sigex_type)
                  {
                     rce_nfy_sig_rex(nde_p, nfy_p);
                  }
               }
            }
            else
            {
               ERR_FATAL("cookie mismatch in signal", 0, 0, 0);                  // corruption check fails
            }

            nfy_p = nfy_p->next;                                                 // iterate looking for context
         }

         rce_mutex_unlock_dal(&(nde_p->mutex));

         rc = nde2rcevt(nde_p);
      }
      else
      {
         ERR_FATAL("cookie mismatch in signal", 0, 0, 0);                        // corruption check fails
      }
   }

   return rc;                                                                    // return result
}

/**
API, Signal event, with name
See prerequsite note with rcevt_create_name
@param[in] name NULL terminated string, name of the event
@return
RCEVT_NULL -- Error
RCEVT_HANDLE -- Opaque handle to existing event
*/
RCEVT_HANDLE rcevt_signal_name(RCEVT_NAME const name)
{
   RCEVT_HANDLE rc = RCE_NULL;                                                   // return result
   RCEVT_HANDLE handle = rcevt_create_name(name);

   if (RCE_NULL != handle)
   {
      rc = rcevt_signal_handle(handle);                                          // signal handle
   }

   return rc;                                                                    // return result
}

/**
INTERNAL, Not Exposed for API Use
*/
RCEVT_HANDLE rcevt_wait_common(RCEVT_HANDLE const handle, RCEVT_THRESHOLD threshold, RCEVT_SIGEX_TYPE type, RCEVT_SIGEX sigex)
{
   RCEVT_HANDLE rc = RCE_NULL;                                                   // return result
   rce_nde_p nde_p = rcevt2nde(handle);
   rce_nfy_p nfy_p = RCE_NULL;

   rce_mutex_lock_dal(&(nde_p->mutex));

   if (nde_p->threshold < threshold)                                             // implicit register
   {
      nfy_p = rcevt_internal_register_sigex_update(handle, threshold, type, sigex); // update an existing

      if (RCE_NULL != nfy_p)
      {
         rc = handle;                                                            // return result
      }
      else
      {
         nfy_p = rcevt_internal_register_sigex_add(handle, threshold, type, sigex); // add a new

         if (RCE_NULL != nfy_p)
         {
            rc = handle;                                                         // return result
         }
         else
         {
            ERR_FATAL("cannot update/add event in wait", 0, 0, 0);
         }
      }

      if (RCE_NFY_COOKIE == nfy_p->nfy_cookie)                                   // corruption check before use
      {
         rce_mutex_unlock_dal(&(nde_p->mutex));

         if (RCEVT_SIGEX_TYPE_SIGDAL == nfy_p->sigex_type)
         {
            rce_nfy_wait_dal(nde_p, nfy_p);
         }

         else if (RCEVT_SIGEX_TYPE_SIGPOSIX == nfy_p->sigex_type)
         {
            rce_nfy_wait_posix(nde_p, nfy_p);
         }

         else if (RCEVT_SIGEX_TYPE_SIGQURT == nfy_p->sigex_type)
         {
            rce_nfy_wait_qurt(nde_p, nfy_p);
         }

         else if (RCEVT_SIGEX_TYPE_SIGREX == nfy_p->sigex_type)
         {
            rce_nfy_wait_rex(nde_p, nfy_p);
         }

         rce_mutex_lock_dal(&(nde_p->mutex));
      }
      else
      {
         ERR_FATAL("cookie mismatch in wait", 0, 0, 0);                          // corruption check fails
      }

      rcevt_internal_unregister_sigex(handle, type, sigex);                      // implicit unregister
   }

   rce_mutex_unlock_dal(&(nde_p->mutex));

   return rc;                                                                    // return result
}

/**
API, Wait for event at specific threshold, with handle
See prerequsite note with rcevt_create_name
@param[in] handle Opaque handle of the event
@param[in] threshold Notification begins with threshold and continues until unregistered
@param[in] type Notification type (DAL, POSIX, QURT, REX)
@param[in] signal Notification sigex structure pointer, type specific values
@return
RCEVT_NULL -- Error
RCEVT_HANDLE -- Opaque handle to existing event
*/
RCEVT_HANDLE rcevt_wait_sigex_handle(RCEVT_HANDLE const handle, RCEVT_THRESHOLD threshold, RCEVT_SIGEX_TYPE type, RCEVT_SIGEX sigex)
{
   RCEVT_HANDLE rc = RCE_NULL;                                                   // return result

   if (RCE_NULL != handle)
   {
      rc = rcevt_wait_common(handle, threshold, type, sigex);                    // wait
   }

   return rc;
}

/**
API, Wait for event at specific threshold, with name
See prerequsite note with rcevt_create_name
@param[in] name NULL terminated string, name of the event
@param[in] threshold Notification begins with threshold and continues until unregistered
@param[in] type Notification type (DAL, POSIX, QURT, REX)
@param[in] signal Notification sigex structure pointer, type specific values
@return
RCEVT_NULL -- Error
RCEVT_HANDLE -- Opaque handle to existing event
*/
RCEVT_HANDLE rcevt_wait_sigex_name(RCEVT_NAME const name, RCEVT_THRESHOLD threshold, RCEVT_SIGEX_TYPE type, RCEVT_SIGEX sigex)
{
   RCEVT_HANDLE rc = RCE_NULL;                                                   // return result
   RCEVT_HANDLE handle = rcevt_create_name(name);

   if (RCE_NULL != handle)
   {
      rc = rcevt_wait_common(handle, threshold, type, sigex);                    // wait
   }

   return rc;
}

/**
API, Wait for event, one time per call, until threshold met, with handle
See prerequsite note with rcevt_create_name
@param[in] handle Opaque handle of the event
@return
RCEVT_NULL -- Error
RCEVT_HANDLE -- Opaque handle to existing event
*/
RCEVT_HANDLE rcevt_wait_count_handle(RCEVT_HANDLE const handle, RCEVT_THRESHOLD threshold)
{
   RCEVT_HANDLE rc = RCE_NULL;                                                   // return result

   DALSYSEventObj signalObject;
   RCEVT_SIGEX_SIGDAL sig;

   // DAL Event Objects Are Protected on Context Allowed to Wait (Create/Wait/Destroy)
   if (DAL_SUCCESS != DALSYS_EventCreate(DALSYS_EVENT_ATTR_NORMAL, &(sig.signal), &(signalObject)))
   {
      ERR_FATAL("event create", 0, 0, 0);
   }

   rc = rcevt_wait_common(handle, threshold, RCEVT_SIGEX_TYPE_SIGDAL, &sig);

   // DAL Event Objects Are Protected on Context Allowed to Wait (Create/Wait/Destroy)
   if (DAL_SUCCESS != DALSYS_DestroyObject(sig.signal))
   {
      ERR_FATAL("event destroy", 0, 0, 0);
   }

   return rc;                                                                    // return result
}

/**
API, Wait for event, one time per call, with handle
See prerequsite note with rcevt_create_name
@param[in] handle Opaque handle of the event
@return
RCEVT_NULL -- Error
RCEVT_HANDLE -- Opaque handle to existing event
*/
RCEVT_HANDLE rcevt_wait_handle(RCEVT_HANDLE const handle)
{
   RCEVT_HANDLE rc = RCE_NULL;                                                   // return result

   rc = rcevt_wait_count_handle(handle, RCE_THRESHOLD_DEFAULT);

   return rc;                                                                    // return result
}

/**
API, Wait for event, one time per call, until threshold met, with name
See prerequsite note with rcevt_create_name
@param[in] name NULL terminated string, name of the event
@return
RCEVT_NULL -- Error
RCEVT_HANDLE -- Opaque handle to existing event
*/
RCEVT_HANDLE rcevt_wait_count_name(RCEVT_NAME const name, RCEVT_THRESHOLD threshold)
{
   RCEVT_HANDLE rc = RCE_NULL;                                                   // return result
   RCEVT_HANDLE handle = rcevt_create_name(name);

   if (RCE_NULL != handle)
   {
      rc = rcevt_wait_count_handle(handle, threshold);
   }

   return rc;                                                                    // return result
}

/**
API, Wait for event, one time per call, with name
See prerequsite note with rcevt_create_name
@param[in] name NULL terminated string, name of the event
@return
RCEVT_NULL -- Error
RCEVT_HANDLE -- Opaque handle to existing event
*/
RCEVT_HANDLE rcevt_wait_name(RCEVT_NAME const name)
{
   RCEVT_HANDLE rc = RCE_NULL;                                                   // return result

   rc = rcevt_wait_count_name(name, RCE_THRESHOLD_DEFAULT);

   return rc;                                                                    // return result
}

/**
API, Service initialization
@param
None
@return
None
*/
void rcevt_init(void)
{
   rce_init();
}

/**
API, Service termination
@param
None
@return
None
*/
void rcevt_term(void)
{
   rce_term();
}
