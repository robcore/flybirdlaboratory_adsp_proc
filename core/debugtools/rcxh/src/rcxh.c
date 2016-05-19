/** vi: tw=128 ts=3 sw=3 et
@file rcxh.c
@brief This file contains the API for the Exception Handling Service, API 1.0
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
$Header: //components/rel/core.adsp/2.6.1/debugtools/rcxh/src/rcxh.c#1 $
$DateTime: 2014/10/16 12:45:40 $
$Change: 6781644 $
$Author: pwbldsvc $
===============================================================================*/

#include "err.h"
#include "msg.h"

#if defined(RCXH_TRACER_SWEVT)
#include "tracer.h"
#include "rcxh_tracer_swe.h"
#endif

#include "rcxh.h"
#include "rcinit_internal.h"

/////////////////////////////////////////////////////////////////////
// Localized Type Declarations
/////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////
// Localized Storage
/////////////////////////////////////////////////////////////////////

/**
Internal, Structure of states and variables useful for instrumentation by debugger
*/
static struct rcxh_internal_s
{
   int tls_key;

} rcxh_internal;

/**
Internal, Scope of current exception handler Try/Catch/Finally/EndTry
@returns
Current scope of active exception handler Try/Catch/Finally/EndTry
*/
static _rcxh_scope_p _rcxh_get_scope(void)                                       /**< TLS accessor */
{
   return rcinit_internal_tls_get_specific(rcxh_internal.tls_key);
}

/**
Internal, Scope of current exception handler Try/Catch/Finally/EndTry
@param[in] scope Sets current scope for active exception handler Try/Catch/Finally/EndTry
@returns
NHLOS TLS return status
*/
static int _rcxh_set_scope(_rcxh_scope_p scope)                                  /**< TLS accessor */
{
   return rcinit_internal_tls_set_specific(rcxh_internal.tls_key, (void*)scope);
}

/**
Internal, Exception handler root "class" for all derived exception "class"
*/
struct _rcxh_s __rcxh_undef = { "undef", NULL };                                 /**< Exception handler root class "undef" */
struct _rcxh_s* _rcxh_undef = &__rcxh_undef;                                     /**< Exception handler root class "undef" */

/**
Internal, Handler routine of Try/Catch/Finally/EndTry Throw implementation
@param[in] file NULL terminated string, file name of throw
@param[in] line Integer, line number of throw
@param[in] handle Handle to the exception "class" of throw
@returns
None.
*/
void _rcxh_throw(char* file, int line, RCXH_HANDLE handle)
{
   unsigned long task_hash;
   char task_name[RCINIT_NAME_MAX];
   _rcxh_scope_p scope = _rcxh_get_scope();                                      /**< TLS accessor */

   task_hash = rcinit_internal_task_name(task_name, sizeof(task_name));

   if (NULL != scope)                                                            /**< NULL check */
   {
#if defined(RCXH_TRACER_SWEVT)
      tracer_event_simple_vargs(RCXH_SWE_THROW, 2, 0, task_hash);
#endif

      MSG_SPRINTF_5(MSG_SSID_TMS, MSG_LEGACY_HIGH, "RCXH_THROW check %s %s#%d task_hash %x task_name %s",
                    NULL != handle && NULL != handle->name ? handle->name : "*",
                    NULL != file ? file : "*", line, task_hash, task_name);

      if (_rcxh_where_finally == scope->where || _rcxh_where_exp == scope->where) /**< throw upward from from any where Finally or Expression */
      {
         _rcxh_set_scope(scope->old);                                            /**< TLS accessor */

         _rcxh_throw(file, line, handle);                                        /**< throw upward from from any where Finally or Expression */
      }

      scope->src = scope->where;                                                 /**< record source of throw */

      scope->file = file;                                                        /**< record source of throw */

      scope->line = line;                                                        /**< record source of throw */

      scope->handle = handle;                                                    /**< record source of throw */

      if (NULL == scope->frame)                                                  /**< react to the possiblity of NULL storage space to appease static analysis tools, scope is not dynamic */
      {
#if defined(RCXH_TRACER_SWEVT)
         tracer_event_simple_vargs(RCXH_SWE_UNCAUGHT, 2, 0, task_hash);
#endif

         ERR_FATAL("RCXH uncaught %d task_hash %x", 0, task_hash, 0);
      }

      else
      {
         MSG_SPRINTF_5(MSG_SSID_TMS, MSG_LEGACY_HIGH, "RCXH_THROW unwind %s %s#%d task_hash %x task_name %s",
                       NULL != handle && NULL != handle->name ? handle->name : "*",
                       NULL != file ? file : "*", line, task_hash, task_name);

         scope->where = _rcxh_where_exp;                                         /**< record current scope where */

         scope->state = _rcxh_state_thrown;                                      /**< record current scope state */

         if (_rcxh_frame_check_ok == scope->check)                               /**< register file check */
         {
            longjmp(scope->frame, RCXH_TRUE);                                    /**< unwind scope by longjmp */
         }

         else
         {
#if defined(RCXH_TRACER_SWEVT)
            tracer_event_simple_vargs(RCXH_SWE_UNCAUGHT, 2, 0, task_hash);
#endif

            ERR_FATAL("RCXH uncaught %d task_hash %x", 0, task_hash, 0);
         }
      }
   }

   else
   {
#if defined(RCXH_TRACER_SWEVT)
      tracer_event_simple_vargs(RCXH_SWE_UNCAUGHT, 2, 0, task_hash);
#endif

      ERR_FATAL("RCXH uncaught %d task_hash %x", 0, task_hash, 0);
   }
}

/**
Internal, Handler routine of Try/Catch/Finally/EndTry Try clause initialization implementation
@param[in] scope Current exception handler scope
@returns
None.
*/
void _rcxh_scope_init(_rcxh_scope_p scope)
{
   unsigned long task_hash;
   char task_name[RCINIT_NAME_MAX];
   task_hash = rcinit_internal_task_name(task_name, sizeof(task_name));

   if (NULL != scope)                                                            /**< NULL check */
   {
#if defined(RCXH_TRACER_SWEVT)
      tracer_event_simple_vargs(RCXH_SWE_TRY, 2, 0, task_hash);
#endif

      MSG_SPRINTF_3(MSG_SSID_TMS, MSG_LEGACY_HIGH, "RCXH_TRY %s task_hash %x task_name %s", "*", task_hash, task_name);

      scope->old = _rcxh_get_scope();                                            /**< TLS accessor */

      scope->where = _rcxh_where_try;                                            /**< defined */
      scope->state = _rcxh_state_unthrown;                                       /**< defined */
      scope->src = _rcxh_where_none;                                             /**< undefined until _rcxh_state_thrown */
      scope->file = NULL;                                                        /**< undefined until _rcxh_state_thrown */
      scope->line = 0;                                                           /**< undefined until _rcxh_state_thrown */
      scope->handle = NULL;                                                      /**< undefined until _rcxh_state_thrown */

      _rcxh_set_scope(scope);                                                    /**< TLS accessor */
   }

   else
   {
#if defined(RCXH_TRACER_SWEVT)
      tracer_event_simple_vargs(RCXH_SWE_UNCAUGHT, 2, 0, task_hash);
#endif

      ERR_FATAL("RCXH uncaught %d task_hash %x", 0, task_hash, 0);
   }
}

/**
Internal, Handler routine of Try/Catch/Finally/EndTry Catch clause initialization implementation
@param[in] scope Current exception handler scope
@param[in] handle Handle for active exception handler Try/Catch/Finally/EndTry
@returns
RCXH_TRUE -- Catching exception
RCXH_FALSE -- Not catching exception
*/
RCXH_BOOL _rcxh_catching(_rcxh_scope_p scope, RCXH_HANDLE handle)
{
   RCXH_BOOL rc = RCXH_FALSE;                                                    /**< return result */
   unsigned long task_hash;
   char task_name[RCINIT_NAME_MAX];
   task_hash = rcinit_internal_task_name(task_name, sizeof(task_name));

   if (NULL != scope)                                                            /**< NULL check */
   {
#if defined(RCXH_TRACER_SWEVT)
      tracer_event_simple_vargs(RCXH_SWE_CATCH, 2, 0, task_hash);
#endif

      MSG_SPRINTF_3(MSG_SSID_TMS, MSG_LEGACY_HIGH, "RCXH_CATCH check %s task_hash %x task_name %s",
                    NULL != handle && NULL != handle->name ? handle->name : "*", task_hash, task_name);

      if (_rcxh_where_catch != scope->src)                                       /**< evaluate only if not yet caught */
      {
         while (RCXH_FALSE == rc && NULL != handle)                              /**< iterate looking for matching exception "class" */
         {
            RCXH_HANDLE prev;                                                    /**< starting handle */

            for (prev = scope->handle; RCXH_FALSE == rc && NULL != prev; prev = prev->parent) /**< iteration over exception "class" to locate handler */
            {
               if (prev == handle)                                               /**< explict catch */
               {
#if defined(RCXH_TRACER_SWEVT)
                  tracer_event_simple_vargs(RCXH_SWE_CAUGHT, 2, 0, task_hash);
#endif
                  MSG_SPRINTF_3(MSG_SSID_TMS, MSG_LEGACY_HIGH, "RCXH_CATCH caught %s task_hash %x task_name %s",
                                NULL != handle && NULL != handle->name ? handle->name : "*", task_hash, task_name);

                  scope->where = _rcxh_where_catch;                              /**< record current scope where */

                  scope->state = _rcxh_state_caught;                             /**< record current scope state */

                  rc = RCXH_TRUE;                                                /**< has been caught */
               }
            }
         }
      }
   }

   else
   {
#if defined(RCXH_TRACER_SWEVT)
      tracer_event_simple_vargs(RCXH_SWE_UNCAUGHT, 2, 0, task_hash);
#endif

      ERR_FATAL("RCXH uncaught %d task_hash %x", 0, task_hash, 0);
   }

   return rc;                                                                    /**< return result */
}

/**
Internal, Handler routine of Try/Catch/Finally/EndTry Finally clause initialization implementation
@param[in] scope Current exception handler scope
@returns
None.
*/
void _rcxh_finally(_rcxh_scope_p scope)
{
   unsigned long task_hash;
   char task_name[RCINIT_NAME_MAX];
   task_hash = rcinit_internal_task_name(task_name, sizeof(task_name));

   if (NULL != scope)                                                            /**< NULL check */
   {
#if defined(RCXH_TRACER_SWEVT)
      tracer_event_simple_vargs(RCXH_SWE_FINALLY, 2, 0, task_hash);
#endif

      MSG_SPRINTF_3(MSG_SSID_TMS, MSG_LEGACY_HIGH, "RCXH_FINALLY %s task_hash %x task_name %s", "*", task_hash, task_name);

      scope->where = _rcxh_where_finally;                                        /**< record where */
   }

   else
   {
#if defined(RCXH_TRACER_SWEVT)
      tracer_event_simple_vargs(RCXH_SWE_UNCAUGHT, 2, 0, task_hash);
#endif

      ERR_FATAL("RCXH uncaught %d task_hash %x", 0, task_hash, 0);
   }
}

/**
Internal, Handler routine of Try/Catch/Finally/EndTry EndTry clause initialization implementation
@param[in] scope Current exception handler scope
@returns
None.
*/
void _rcxh_end(_rcxh_scope_p scope)
{
   unsigned long task_hash;
   char task_name[RCINIT_NAME_MAX];
   task_hash = rcinit_internal_task_name(task_name, sizeof(task_name));

   if (NULL != scope)                                                            /**< NULL check */
   {
#if defined(RCXH_TRACER_SWEVT)
      tracer_event_simple_vargs(RCXH_SWE_ENDTRY, 2, 0, task_hash);
#endif

      MSG_SPRINTF_3(MSG_SSID_TMS, MSG_LEGACY_HIGH, "RCXH_ENDTRY %s task_hash %x task_name %s", "*", task_hash, task_name);

      _rcxh_set_scope(scope->old);                                               /**< TLS accessor */

      if (_rcxh_state_thrown == scope->state)                                    /**< check state */
      {
         _rcxh_throw(scope->file, scope->line, scope->handle);                   /**< throw upwards */
      }
   }

   else
   {
#if defined(RCXH_TRACER_SWEVT)
      tracer_event_simple_vargs(RCXH_SWE_UNCAUGHT, 2, 0, task_hash);
#endif

      ERR_FATAL("RCXH uncaught %d task_hash %x", 0, task_hash, 0);
   }
}

/**
Initialization of service prior to use
@return
None.
*/
void rcxh_init(void)
{
   rcinit_internal_tls_create_key(&rcxh_internal.tls_key, NULL);
}

/**
Termination of service following use
@return
None.
*/
void rcxh_term(void)
{
   /* NULL */                                                                    /* DECISION TO NOT CLEANUP SERVICE FOR POST MORTEM REASONS */
}
