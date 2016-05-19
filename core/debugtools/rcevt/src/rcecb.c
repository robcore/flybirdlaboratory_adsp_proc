/**
@file rcecb.c
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
Copyright (c) 2013 QUALCOMM Technologies Incorporated.
All rights reserved.
QUALCOMM Confidential and Proprietary.
=============================================================================*/
/*=============================================================================
Edit History
$Header: //components/rel/core.adsp/2.6.1/debugtools/rcevt/src/rcecb.c#1 $
$DateTime: 2014/10/16 12:45:40 $
$Change: 6781644 $
$Author: pwbldsvc $
===============================================================================*/

#include "stringl/stringl.h"

#include "rcecb.h"
#include "rcevt_internal.h"

/**
API, Map opaque handle to name
@param[in] handle Opaque handle of the event
@return
RCECB_NULL -- Error
RCECB_NAME -- Pointer to NULL terminated string, name of the event
*/
RCECB_NAME rcecb_map_handle(RCECB_HANDLE const handle)
{
   RCECB_NAME rc = RCE_NULL;                                                     // return result

   rce_init();

   rc = rcecb2nde(handle)->name;                                                 // return result

   return rc;                                                                    // return status or failure
}

/**
API, Map name to opaque handle
@param[in] name NULL terminated string, name of the event
@return
RCECB_NULL -- Error
RCECB_HANDLE -- Opaque handle to existing event
*/
RCECB_HANDLE rcecb_map_name(RCECB_NAME const name)
{
   RCECB_HANDLE rc = RCE_NULL;                                                   // return result
   rce_nde_p nde_p;

   rce_init();

   nde_p = rce_nde_hashtab_get(rce_nmehash(name));

   while (RCE_NULL != nde_p)                                                     // search for existing node
   {
      if (nde_p->name != name)                                                   // same address compare
      {
         int len = rce_nmelen(nde_p->name);                                      // string compare required

         if (0 == rce_nmecmp(nde_p->name, name, len))                            // lexical comparision
         {
            rc = nde2rcecb(nde_p);                                               // return result

            break;                                                               // break loop for return
         }
      }

      else                                                                       // same address
      {
         rc = nde2rcecb(nde_p);                                                  // return result

         break;                                                                  // break loop for return
      }

      nde_p = nde_p->next;                                                       // iterate to locate
   }

   return rc;                                                                    // return status or failure
}

extern rce_nde_p rce_hashtab[RCEVT_HASHTABLE_BUCKETS];                           // forward reference

/**
INTERNAL, Not Exposed for API Use, Specialized, no mutex protections, single thread only
*/
RCECB_HANDLE rcecb_map_name_nolocks(RCECB_NAME const name)
{
   RCECB_HANDLE rc = RCE_NULL;                                                   // return result
   rce_hash_t hash = rce_nmehash(name);                                          // map name to hash
   rce_nde_p nde_p;

   nde_p = rce_hashtab[hash];                                                    // hashtable offset

   while (RCE_NULL != nde_p)                                                     // search for existing node
   {
      if (nde_p->name != name)                                                   // same address compare
      {
         int len = rce_nmelen(nde_p->name);                                      // string compare required

         if (0 == rce_nmecmp(nde_p->name, name, len))                            // lexical comparision
         {
            rc = nde2rcecb(nde_p);                                               // return result

            break;                                                               // break loop for return
         }
      }

      else                                                                       // same address
      {
         rc = nde2rcecb(nde_p);                                                  // return result

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
RCECB_NULL -- Error
RCECB_HANDLE -- Opaque handle to existing event
*/
RCECB_HANDLE rcecb_create_name(RCECB_NAME const name)
{
   RCECB_HANDLE rc = RCE_NULL;                                                   // return result
   RCECB_HANDLE handle;

   rce_mutex_lock_dal(&(rce_internal.mutex_create));

   handle = rcecb_map_name(name);

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

         unsigned long buf_s = rce_nmelen(name) + 1;                             // length of RCECB_NAME
         char* buf_p = rce_malloc(buf_s);                                        // space for RCECB_NAME

         if (RCE_NULL != buf_p)
         {
            strlcpy(buf_p, name, buf_s);                                         // private copy of name

            nde_p->name = buf_p;                                                 // memorize name address

            nde_p->notify_head = RCE_NULL;                                       // initialize notify queue

            rce_nde_hashtab_put(nde_p, rce_nmehash(nde_p->name));

            rc = nde2rcecb(nde_p);                                               // return result
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
See prerequsite note with rcecb_create_name
@param[in] handle Opaque handle of the event
@return
RCECB_BOOL -- Boolean reflecting event previously created
*/
RCECB_BOOL rcecb_search_handle(RCECB_HANDLE const handle)
{
   RCECB_BOOL rc = RCECB_FALSE;                                                  // return result

   if (RCE_NULL != rcecb_map_handle(handle))
   {
      rc = RCECB_TRUE;                                                           // return result
   }

   return rc;                                                                    // return status or failure
}

/**
API, Search an event, with name
See prerequsite note with rcecb_create_name
@param[in] name NULL terminated string, name of the event
@return
RCECB_BOOL -- Boolean reflecting event previously created
*/
RCECB_BOOL rcecb_search_name(RCECB_NAME const name)
{
   RCECB_BOOL rc = RCECB_FALSE;                                                  // return result

   if (RCE_NULL != rcecb_map_name(name))
   {
      rc = RCECB_TRUE;                                                           // return result
   }

   return rc;                                                                    // return status or failure
}

/**
API, Search an event, with handle
See prerequsite note with rcecb_create_name
@param[in] handle Opaque handle of the event
@param[in] context Callback function pointer
@return
RCECB_BOOL -- Boolean reflecting event previously created
*/
RCECB_BOOL rcecb_search_context_handle(RCECB_HANDLE const handle, RCECB_CONTEXT const context)
{
   RCECB_BOOL rc = RCECB_FALSE;                                                  // return result
   rce_nde_p nde_p = rcecb2nde(handle);

   if (RCE_NULL != nde_p)
   {
      rce_nfy_p nfy_p;

      rce_mutex_lock_dal(&(nde_p->mutex));                                       // lock mutex

      nfy_p = nde_p->notify_head;                                                // locate notify context

      while (RCE_NULL != nfy_p)                                                  // loop for check
      {
         if ((RCEVT_SIGEX_TYPE_CALLBACK == nfy_p->sigex_type) &&
             (context == (RCECB_CONTEXT)nfy_p->sigex.parm[0]))
         {
            rc = RCECB_TRUE;                                                     // return result

            break;                                                               // break loop
         }

         nfy_p = nfy_p->next;                                                    // iterate to next
      }

      rce_mutex_unlock_dal(&(nde_p->mutex));                                     // unlock mutex
   }

   return rc;                                                                    // return status or failure
}

/**
API, Search an event, with name
See prerequsite note with rcecb_create_name
@param[in] name NULL terminated string, name of the event
@param[in] context Callback function pointer
@return
RCECB_BOOL -- Boolean reflecting event previously created
*/
RCECB_BOOL rcecb_search_context_name(RCECB_NAME const name, RCECB_CONTEXT const context)
{
   RCECB_BOOL rc = RCECB_FALSE;                                                  // return result
   RCECB_HANDLE handle = rcecb_map_name(name);

   rc = rcecb_search_context_handle(handle, context);

   return rc;                                                                    // return status or failure
}

/**
API, Count of registrants for event, with handle
See prerequsite note with rcecb_create_name
@param[in] handle Opaque handle of the event
@return
int -- Count of registrants for specific event
*/
int rcecb_getcontexts_handle(RCECB_HANDLE const handle)
{
   int rc = 0;                                                                   // return result
   rce_nde_p nde_p = rcecb2nde(handle);

   if (RCE_NULL != nde_p)
   {
      rce_nfy_p nfy_p;

      rce_mutex_lock_dal(&(nde_p->mutex));                                       // lock mutex

      nfy_p = nde_p->notify_head;                                                // locate notify context

      while (RCE_NULL != nfy_p)                                                  // loop for check
      {
         if (RCEVT_SIGEX_TYPE_CALLBACK == nfy_p->sigex_type)
         {
            rc++;                                                                // return result
         }

         nfy_p = nfy_p->next;                                                    // iterate to next
      }

      rce_mutex_unlock_dal(&(nde_p->mutex));                                     // unlock mutex
   }

   return rc;                                                                    // return status or failure
}

/**
API, Count of registrants for event, with name
See prerequsite note with rcecb_create_name
@param[in] name NULL terminated string, name of the event
@return
int -- Count of registrants for specific event
*/
int rcecb_getcontexts_name(RCECB_NAME const name)
{
   int rc = 0;                                                                   // return result
   RCECB_HANDLE handle = rcecb_map_name(name);

   rc = rcecb_getcontexts_handle(handle);

   return rc;                                                                    // return status or failure
}

/**
INTERNAL, Not Exposed for API Use
*/
rce_nfy_p rcecb_register_upd(RCECB_HANDLE const handle, RCECB_CONTEXT const context)
{
   rce_nfy_p rc = RCE_NULL;                                                      // return result
   rce_nfy_p nfy_p;

   nfy_p = rcecb2nde(handle)->notify_head;                                       // locate notify context

   while (RCE_NULL != nfy_p)                                                     // loop for check
   {
      if ((RCEVT_SIGEX_TYPE_CALLBACK == nfy_p->sigex_type) &&
          (context == (RCECB_CONTEXT)nfy_p->sigex.parm[0]))
      {
         rc = nfy_p;                                                             // return result

         break;                                                                  // break loop
      }

      nfy_p = nfy_p->next;                                                       // iterate to next
   }

   return rc;
}

/**
INTERNAL, Not Exposed for API Use
*/
rce_nfy_p rcecb_register_add(RCECB_HANDLE const handle, RCECB_CONTEXT const context)
{
   rce_nfy_p rc = RCE_NULL;                                                      // return result
   rce_nfy_p nfy_p;

   nfy_p = rce_nfy_pool_alloc();

   if (RCE_NULL != nfy_p)                                                        // populate
   {
      rce_nde_p nde_p = rcecb2nde(handle);

      nfy_p->next = nde_p->notify_head;                                          // insert to head of list

      nde_p->notify_head = nfy_p;                                                // update head

      nfy_p->sigex_type = RCEVT_SIGEX_TYPE_CALLBACK;

      secure_memset(nfy_p->sigex.parm, 0, sizeof(nfy_p->sigex.parm));

      nfy_p->sigex.parm[0] = context;

      rc = nfy_p;                                                                // return result
   }

   return rc;                                                                    // return result
}

/**
API, Register callback to event, with handle
See prerequsite note with rcecb_create_name
@param[in] handle Opaque handle of the event
@param[in] context Callback function pointer
@return
RCECB_NULL -- Error
RCECB_HANDLE -- Opaque handle to existing event
*/
RCECB_HANDLE rcecb_register_handle(RCECB_HANDLE const handle, RCECB_CONTEXT const context)
{
   RCECB_HANDLE rc = RCE_NULL;                                                   // return result
   rce_nde_p nde_p = rcecb2nde(handle);

   rce_mutex_lock_dal(&(nde_p->mutex));                                          // lock mutex

   if (RCE_NULL != rcecb_register_upd(handle, context)                           // update existing registration
       || RCE_NULL != rcecb_register_add(handle, context))                       // add new registration
   {
      rc = handle;                                                               // return result
   }

   rce_mutex_unlock_dal(&(nde_p->mutex));                                        // unlock mutex

   return rc;                                                                    // return result
}

/**
API, Register callback to event, with name
See prerequsite note with rcecb_create_name
@param[in] name NULL terminated string, name of the event
@param[in] context Callback function pointer
@return
RCECB_NULL -- Error
RCECB_HANDLE -- Opaque handle to existing event
*/
RCECB_HANDLE rcecb_register_name(RCECB_NAME const name, RCECB_CONTEXT const context)
{
   RCECB_HANDLE rc = RCE_NULL;                                                   // return result
   RCECB_HANDLE handle = (RCECB_HANDLE)rcecb_map_name(name);
   rce_nde_p nde_p;

   if (RCE_NULL == handle)                                                       // check for existing
   {
      handle = rcecb_create_name(name);                                          // implicit creation
   }

   if (RCE_NULL != handle)                                                       // check for existing
   {
      nde_p = rcecb2nde(handle);

      rce_mutex_lock_dal(&(nde_p->mutex));                                       // lock mutex

      if (RCE_NULL != rcecb_register_upd(handle, context)                        // update existing registration
          || RCE_NULL != rcecb_register_add(handle, context))                    // add new registration
      {
         rc = handle;                                                            // return result
      }

      rce_mutex_unlock_dal(&(nde_p->mutex));                                     // unlock mutex
   }

   return rc;                                                                    // return result
}

/**
INTERNAL, Not Exposed for API Use
*/
RCECB_HANDLE rcecb_internal_unregister(RCECB_HANDLE const handle, RCECB_CONTEXT const context)
{
   RCECB_HANDLE rc = RCE_NULL;                                                   // return result
   rce_nfy_p nfy_prev = RCE_NULL;
   rce_nfy_p nfy_p;
   rce_nde_p nde_p = rcecb2nde(handle);

   nfy_p = nde_p->notify_head;                                                   // search out on notify queue

   while (RCE_NULL != nfy_p)                                                     // loop for next
   {
      if ((RCEVT_SIGEX_TYPE_CALLBACK == nfy_p->sigex_type) &&
          (context == (RCECB_CONTEXT)nfy_p->sigex.parm[0]))
      {
         if (RCE_NULL == nfy_prev)                                               // head of list check
         {
            nde_p->notify_head = nfy_p->next;                                    // remove from head
         }
         else
         {
            nfy_prev->next = nfy_p->next;                                        // remove from list
         }

         nfy_p->next = RCE_NULL;                                                 // depopulate

         rce_nfy_pool_free(nfy_p);                                               // restore to pool

         rc = nde2rcecb(nde_p);                                                  // return result

         break;                                                                  // exit loop
      }

      nfy_prev = nfy_p;

      nfy_p = nfy_p->next;                                                       // iterate to check next
   }

   return rc;                                                                    // return result
}

/**
API, Unegister callback to event, with handle
@param[in] handle Opaque handle of the event
@param[in] context Callback function pointer
@return
RCECB_NULL -- Error
RCECB_HANDLE -- Opaque handle to existing event
*/
RCECB_HANDLE rcecb_unregister_handle(RCECB_HANDLE const handle, RCECB_CONTEXT const context)
{
   RCECB_HANDLE rc = RCE_NULL;                                                   // return result
   rce_nde_p nde_p = rcecb2nde(handle);

   rce_mutex_lock_dal(&(nde_p->mutex));                                          // lock mutex

   rc = rcecb_internal_unregister(handle, context);                              // existing

   rce_mutex_unlock_dal(&(nde_p->mutex));                                        // unlock mutex

   return rc;                                                                    // return result
}

/**
API, Unegister callback to event, with name
@param[in] name NULL terminated string, name of the event
@param[in] context Callback function pointer
@return
RCECB_NULL -- Error
RCECB_HANDLE -- Opaque handle to existing event
*/
RCECB_HANDLE rcecb_unregister_name(RCECB_NAME const name, RCECB_CONTEXT const context)
{
   RCECB_HANDLE rc = RCE_NULL;                                                   // return result
   RCECB_HANDLE handle = rcecb_map_name(name);
   rce_nde_p nde_p;

   if (RCE_NULL == handle)                                                       // check for existing
   {
      handle = rcecb_create_name(name);                                          // implicit creation
   }

   if (RCE_NULL != handle)                                                       // use of handle, or return failure upwards
   {
      nde_p = rcecb2nde(handle);

      rce_mutex_lock_dal(&(nde_p->mutex));                                       // lock mutex

      rc = rcecb_internal_unregister(handle, context);                           // existing

      rce_mutex_unlock_dal(&(nde_p->mutex));                                     // unlock mutex
   }

   return rc;                                                                    // return result
}

/**
INTERNAL, Not Exposed for API Use
*/
rce_nde_p rcecb_signal_common(rce_nde_p nde_p)
{
   rce_nde_p rc = RCE_NULL;                                                      // return result
   rce_nfy_p nfy_p;

   rce_mutex_lock_dal(&(nde_p->mutex));                                          // lock mutex

   nfy_p = nde_p->notify_head;                                                   // traverse notify queue

   while (RCE_NULL != nfy_p)                                                     // iterate
   {
      if (RCEVT_SIGEX_TYPE_CALLBACK == nfy_p->sigex_type)                        // only callback
      {
         void (*callback)(void) = (void (*)(void))(nfy_p->sigex.parm[0]);

         callback();                                                             // <<- other tech team callbacks running this context

         rc = nde_p;                                                             // return result
      }

      nfy_p = nfy_p->next;                                                       // iterate looking for context
   }

   rce_mutex_unlock_dal(&(nde_p->mutex));                                        // unlock mutex

   return rc;                                                                    // return result
}

/**
INTERNAL, Not Exposed for API Use, Specialized, no mutex protections, single thread only
*/
rce_nde_p rcecb_signal_common_nolocks(rce_nde_p nde_p)
{
   rce_nde_p rc = RCE_NULL;                                                      // return result
   rce_nfy_p nfy_p;

   nfy_p = nde_p->notify_head;                                                   // traverse notify queue

   while (RCE_NULL != nfy_p)                                                     // iterate
   {
      if (RCEVT_SIGEX_TYPE_CALLBACK == nfy_p->sigex_type)
      {
         void (*callback)(void) = (void (*)(void))(nfy_p->sigex.parm[0]);

         callback();                                                             // <<- other tech team callbacks running this context

         rc = nde_p;                                                             // return result
      }

      nfy_p = nfy_p->next;                                                       // iterate looking for context
   }

   return rc;                                                                    // return result
}

/**
API, Signal event, with handle
See prerequsite note with rcecb_create_name
@param[in] handle Opaque handle of the event
@return
RCECB_NULL -- Error
RCECB_HANDLE -- Opaque handle to existing event
*/
RCECB_HANDLE rcecb_signal_handle(RCECB_HANDLE const handle)
{
   RCECB_HANDLE rc = RCE_NULL;                                                   // return result

   rc = nde2rcecb(rcecb_signal_common(rcecb2nde(handle)));                       // signal handle

   return rc;                                                                    // return result
}

/**
INTERNAL, Not Exposed for API Use, Specialized, no mutex protections, single thread only
*/
RCECB_HANDLE rcecb_signal_handle_nolocks(RCECB_HANDLE const handle)
{
   RCECB_HANDLE rc = RCE_NULL;                                                   // return result

   rc = nde2rcecb(rcecb_signal_common_nolocks(rcecb2nde(handle)));               // signal handle

   return rc;                                                                    // return result
}

/**
API, Signal event, with name
See prerequsite note with rcecb_create_name
@param[in] name NULL terminated string, name of the event
@return
RCECB_NULL -- Error
RCECB_HANDLE -- Opaque handle to existing event
*/
RCECB_HANDLE rcecb_signal_name(RCECB_NAME const name)
{
   RCECB_HANDLE rc = RCE_NULL;                                                   // return result
   RCECB_HANDLE handle = rcecb_map_name(name);

   if (RCE_NULL == handle)                                                       // check for existing
   {
      handle = rcecb_create_name(name);                                          // implicit creation
   }

   if (RCE_NULL != handle)                                                       // check for existing
   {
      rc = rcecb_signal_handle(handle);                                          // signal handle
   }

   return rc;                                                                    // return result
}

/**
INTERNAL, Not Exposed for API Use, Specialized, no mutex protections, single thread only
*/
RCECB_HANDLE rcecb_signal_name_nolocks(RCECB_NAME const name)
{
   RCECB_HANDLE rc = RCE_NULL;                                                   // return result
   RCECB_HANDLE handle = rcecb_map_name_nolocks(name);

   if (RCE_NULL != handle)                                                       // check for existing
   {
      rc = rcecb_signal_handle_nolocks(handle);                                  // signal handle
   }

   return rc;                                                                    // return result
}

/**
API, Service initialization
@param
None
@return
None
*/
void rcecb_init(void)
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
void rcecb_term(void)
{
   rce_term();
}
