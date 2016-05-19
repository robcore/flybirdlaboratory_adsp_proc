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
$Header: //components/rel/core.adsp/2.6.1/debugtools/dog/src/dog_hb_user.c#3 $
$DateTime: 2014/12/22 14:16:52 $
$Change: 7184280 $
$Author: pwbldsvc $
===============================================================================*/

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

#if defined(FEATURE_REX)
#include "rex.h"
#endif

#if defined(DOG_TRACER_SWEVT)
#include "tracer.h"
#include "dog_tracer_swe.h"
#endif

/**
INTERNAL: Common Module Sizing Information; Do not directly reference as a client user.
*/

#define DOG_HB_DEVICE_PATH_LEN                    32                             /**< INTERNAL, Maximum Device Path Length */
#define DOG_HB_DEVICE_NAME_LEN                    QURT_MAX_NAME_LEN              /**< INTERNAL, Maximum Device Basename Length */
#define DOG_HB_DEVICE_NAME_RESERVED               "doghb"                        /**< INTERNAL, Reserved Device Name */

#define DOG_HB_FREQ_CNT                           5000                           /**< INTERNAL, Ping Frequency Time, MSEC */
#define DOG_HB_PING_ERROR_CNT                     3                              /**< INTERNAL, Ping No Response Error Count */

#define DOG_HB_DEVICE                              "doghb/"                      /**< INTERNAL, Device Prefix */

enum
{
   DOG_HB_METHOD_PING_CHECK = QDI_PRIVATE,                                       /**< API, dog_hb_ping_check(), Manager Only */
   DOG_HB_METHOD_PONG,                                                           /**< API, dog_hb_ping_check() */
   DOG_HB_METHOD_PONG_CHECK,                                                     /**< API, dog_hb_pong_check(), Manager Only */
   DOG_HB_METHOD_PING,
   DOG_HB_METHOD_MAX = DOG_HB_METHOD_PING
};

/////////////////////////////////////////////////////////////////////
// Localized Type Declarations
/////////////////////////////////////////////////////////////////////

struct dog_hb_device_s
{
   qurt_qdi_obj_t qdiobj;                                                        // required to be first

   char name[DOG_HB_DEVICE_NAME_LEN];

   uint32_t hash;

   int lock;                                                                     // resources in use

   struct dog_hb_device_s* next;

   // driver object specific

   int sig_t;

   void* sig_p;

   unsigned int sig_m;                                                           // client supplied

   unsigned int ping;                                                            // ping count

};

enum
{
   DOG_HB_DEVICE_PING_MASK = 0x00000001
};

void dog_hb_user_term(void);                                                     // forward reference
static DOG_HB_STATUS dog_hb_pong_check(DOG_HB_HANDLE handle);                    // forward reference
static DOG_HB_STATUS dog_hb_ping_check(DOG_HB_HANDLE handle);                    // forward reference

/////////////////////////////////////////////////////////////////////
// Localized Storage
/////////////////////////////////////////////////////////////////////

static struct dog_hb_internal_s
{
   qurt_mutex_t mutex;                                                           // serialize

   struct dog_hb_device_s* head;                                                 // head of device list

   timer_type timer;                                                             // internal timer

   DOG_HB_HANDLE handle;                                                         // internal handle

   qurt_anysignal_t anysignal;                                                   // internal anysignal

} dog_hb_internal;

/////////////////////////////////////////////////////////////////////
// Implementation Details
/////////////////////////////////////////////////////////////////////

static void DOG_HB_RELEASE(qurt_qdi_obj_t* qdiobj)
{
   struct dog_hb_device_s* device_p_curr;
   struct dog_hb_device_s* device_p_prev;

   device_p_curr = NULL;
   device_p_prev = NULL;

   qurt_pimutex_lock(&dog_hb_internal.mutex);                                    // serialize driver access

   for (device_p_curr = dog_hb_internal.head; NULL != device_p_curr; device_p_curr = device_p_curr->next)
   {
      if (qdiobj == (qurt_qdi_obj_t*)device_p_curr)
      {
         if (dog_hb_internal.head == device_p_curr)                              // head check
         {
            dog_hb_internal.head = device_p_curr->next;
         }

         else if (NULL != device_p_prev)
         {
            device_p_prev->next = device_p_curr->next;
         }

         // release device tracked resources

         // not driver owned : device_p_curr->sig_p

         if (0 != device_p_curr->lock)                                           // Lock still held
         {
            MSG_SPRINTF_3(MSG_SSID_TMS, MSG_LEGACY_ERROR, "device release abandoned %s %x %d", device_p_curr->name, device_p_curr->hash, 0);
         }

         else
         {
            MSG_SPRINTF_3(MSG_SSID_TMS, MSG_LEGACY_HIGH, "device release %s %x %d", device_p_curr->name, device_p_curr->hash, 0);
         }

         free(device_p_curr);

         break;                                                                  // for ()
      }

      device_p_prev = device_p_curr;
   }

   qurt_pimutex_unlock(&dog_hb_internal.mutex);                                  // serialize driver access
}

static int DOG_HB_INVOCATION(int client_handle, qurt_qdi_obj_t* obj, int method, qurt_qdi_arg_t a1, qurt_qdi_arg_t a2, qurt_qdi_arg_t a3, qurt_qdi_arg_t a4, qurt_qdi_arg_t a5, qurt_qdi_arg_t a6, qurt_qdi_arg_t a7, qurt_qdi_arg_t a8, qurt_qdi_arg_t a9)
{
   int rc = DOG_HB_STATUS_ERROR;                                                 // failure
   struct dog_hb_device_s* device_p = (struct dog_hb_device_s*)obj;
   qurt_sysenv_procname_t pn;
   char task_name[QURT_MAX_NAME_LEN];

   /* client_handle means that we're asking this particular client handle to answer the question about its process */
   /* QDI_OS_SYSENV is the standard method for requesting this type of information */
   /* QDI_HANDLE_LOCAL_CLIENT means that this request originated locally */
   /* QURT_SYSENV_PROCNAME_TYPE is the specific piece of data being requested to fill in a qurt_sysenv_procname_t structure */
   /* &pn is the structure we want filled in */

   qurt_thread_get_name(task_name, sizeof(task_name));

   if (0 > (rc = qurt_qdi_handle_invoke(client_handle, QDI_OS_SYSENV, QDI_HANDLE_LOCAL_CLIENT, QURT_SYSENV_PROCNAME_TYPE, &pn)))
   {
      MSG_SPRINTF_2(MSG_SSID_TMS, MSG_LEGACY_HIGH, "cannot obtain client asid %s %d", task_name, rc);

      return rc;
   }

   rc = DOG_HB_STATUS_ERROR;                                                     // failure

   /* Driver Methods */

   switch (method)
   {
      /**
      INTERNAL, Default Method Handler
      */
      default:
      {
         rc = qurt_qdi_method_default(client_handle, obj, method, a1, a2, a3, a4, a5, a6, a7, a8, a9); // pass along

         break;                                                                     // switch ()
      }

      /**
      INTERNAL, Device Check
      */
      case DOG_HB_METHOD_PING:
      {
         rc = DOG_HB_STATUS_SUCCESS;                                                // success

         break;                                                                     // switch ()
      }

      /**
      API, dog_hb_init
      */
      case QDI_OPEN:
      {
         qurt_pimutex_lock(&dog_hb_internal.mutex);                                 // serialize driver access

         do
         {
            char const* name = NULL == a1.ptr ? NULL : tms_utils_chr_last(a1.ptr, DOG_HB_DEVICE_PATH_LEN + DOG_HB_DEVICE_NAME_LEN, '/');

            if (NULL == name || 1 >= tms_utils_chr_length(name, sizeof(device_p->name))) // insures device name length minimum of 2 ("/?")
            {
               device_p = NULL;

               break;                                                               // do while ()
            }

            name++;                                                                 // skips the trailing '/' component of the device path prefix

            if (DOG_HB_SIG_REXSIGNAL > a2.num || NULL == a3.ptr || 0 == a4.num)
            {
               device_p = NULL;

               break;                                                               // do while ()
            }

            // locate existing named device

            for (device_p = dog_hb_internal.head; NULL != device_p; device_p = device_p->next)
            {
               if (0 == tms_utils_chr_compare(device_p->name, sizeof(device_p->name), name, sizeof(device_p->name)))
               {
                  break;                                                            // for ()
               }
            }

            if (NULL == device_p)
            {
               // allocate new

               if (NULL == (device_p = malloc(sizeof(*device_p))))
               {
                  device_p = NULL;

                  break;                                                            // do while ()
               }

               // initialize new

               secure_memset(device_p, 0, sizeof(*device_p));

               device_p->qdiobj.invoke = DOG_HB_INVOCATION;
               device_p->qdiobj.refcnt = QDI_REFCNT_INIT;
               device_p->qdiobj.release = DOG_HB_RELEASE;

               // device object init

               memsmove(device_p->name, sizeof(device_p->name), name, tms_utils_chr_length(name, sizeof(device_p->name)));

               device_p->hash = tms_utils_hash(device_p->name, sizeof(device_p->name));

               device_p->lock = 0;

               device_p->sig_t = a2.num;

               device_p->sig_p = a3.ptr;

               device_p->sig_m = a4.num;

               device_p->ping = 0;

               // link new into device list

               device_p->next = dog_hb_internal.head;
               dog_hb_internal.head = device_p;
            }

            else
            {
               // operate on existing
            }

         } while (0);

         qurt_pimutex_unlock(&dog_hb_internal.mutex);                               // serialize driver access

         if (NULL == device_p)
         {
            rc = DOG_HB_STATUS_ERROR;                                               // failure

            MSG_SPRINTF_3(MSG_SSID_TMS, MSG_LEGACY_HIGH, "device open %d %s == %d", pn.asid, task_name, rc);
         }

         else
         {
            rc = qurt_qdi_handle_create_from_obj_t(client_handle, (qurt_qdi_obj_t*)device_p); // return handle

            MSG_SPRINTF_5(MSG_SSID_TMS, MSG_LEGACY_HIGH, "device open %s %x %d %s == %d", device_p->name, device_p->hash, pn.asid, task_name, rc);
         }

         break;                                                                     // switch ()
      }

      /**
      API, dog_hb_destroy
      */
      case QDI_CLOSE:
      {
         qurt_pimutex_lock(&dog_hb_internal.mutex);                                 // serialize driver access

         // operate on existing

         qurt_pimutex_unlock(&dog_hb_internal.mutex);                               // serialize driver access

         if (0 != device_p->lock)                                                   // device still active on closure
         {
            MSG_SPRINTF_5(MSG_SSID_TMS, MSG_LEGACY_ERROR, "device close on active %s %x %d %s == %d", device_p->name, device_p->hash, pn.asid, task_name, rc);
         }

         else
         {
            rc = qurt_qdi_method_default(client_handle, obj, method, a1, a2, a3, a4, a5, a6, a7, a8, a9); // pass along

            MSG_SPRINTF_5(MSG_SSID_TMS, MSG_LEGACY_HIGH, "device close %s %x %d %s == %d", device_p->name, device_p->hash, pn.asid, task_name, rc);
         }

         break;                                                                     // switch ()
      }

      /**
      API, dog_hb_ping_check
      */
      case DOG_HB_METHOD_PING_CHECK:
      {
         struct dog_hb_device_s* device_p_curr;

         qurt_pimutex_lock(&dog_hb_internal.mutex);                                 // serialize driver access

         for (device_p_curr = dog_hb_internal.head; NULL != device_p_curr; device_p_curr = device_p_curr->next)
         {
            if (NULL != device_p_curr->sig_p)
            {
               // driver is expected to be supplied to every protection domain, this logic fails
               // if the condition is not met. shows up typically as a TLB miss.

               if (DOG_HB_SIG_ANYSIGNAL == device_p_curr->sig_t)
               {
                  qurt_anysignal_set(device_p_curr->sig_p, device_p_curr->sig_m);
               }
#if defined(FEATURE_REX)
               else if (DOG_HB_SIG_REXSIGNAL == device_p_curr->sig_t)
               {
                  rex_sig_set(device_p_curr->sig_p, device_p_curr->sig_m);
               }
#endif

               device_p_curr->ping++;                                               // increment ping
            }
         }

         qurt_pimutex_unlock(&dog_hb_internal.mutex);                               // serialize driver access

         rc = DOG_HB_STATUS_SUCCESS;                                                // success

         MSG_SPRINTF_5(MSG_SSID_TMS, MSG_LEGACY_HIGH, "device ping check %s %x %d %s == %d", device_p->name, device_p->hash, pn.asid, task_name, rc);

         break;                                                                     // switch ()
      }

      /**
      API, dog_hb_pong
      */
      case DOG_HB_METHOD_PONG:
      {
         qurt_pimutex_lock(&dog_hb_internal.mutex);                                 // serialize driver access

         device_p->ping = 0;                                                        // clear ping

         qurt_pimutex_unlock(&dog_hb_internal.mutex);                               // serialize driver access

         rc = DOG_HB_STATUS_SUCCESS;                                                // success

         MSG_SPRINTF_5(MSG_SSID_TMS, MSG_LEGACY_HIGH, "device pong %s %x %d %s == %d", device_p->name, device_p->hash, pn.asid, task_name, rc);

         break;                                                                     // switch ()
      }

      /**
      API, dog_hb_pong_check
      */
      case DOG_HB_METHOD_PONG_CHECK:
      {
         struct dog_hb_device_s* device_p_curr;

         rc = DOG_HB_STATUS_SUCCESS;                                                // success

         qurt_pimutex_lock(&dog_hb_internal.mutex);                                 // serialize driver access

         for (device_p_curr = dog_hb_internal.head; NULL != device_p_curr; device_p_curr = device_p_curr->next)
         {
            if (DOG_HB_PING_ERROR_CNT < device_p_curr->ping)
            {
               rc = DOG_HB_STATUS_ERROR;                                            // failure

#if defined(DOG_FATAL_ERROR)
               MSG_SPRINTF_4(MSG_SSID_TMS, MSG_LEGACY_FATAL, "DOG_HB detects starvation symptom of %s %x %d %s, seek triage with its owner", device_p_curr->name, device_p_curr->hash, pn.asid, task_name);
#else
               MSG_SPRINTF_4(MSG_SSID_TMS, MSG_LEGACY_ERROR, "DOG_HB detects starvation symptom of %s %x %d %s, seek triage with its owner", device_p_curr->name, device_p_curr->hash, pn.asid, task_name);
#endif

               break;                                                               // for ()
            }
         }

         qurt_pimutex_unlock(&dog_hb_internal.mutex);                               // serialize driver access

         break;                                                                     // switch ()
      }
   }

   return rc;
}

static void dog_hb_timer_callback(timer_cb_data_type data)
{
   if (DOG_HB_STATUS_SUCCESS == dog_hb_ping_check(dog_hb_internal.handle))       // ping check
   {
      if (DOG_HB_STATUS_SUCCESS == dog_hb_pong(dog_hb_internal.handle))          // self pong
      {
         if (DOG_HB_STATUS_SUCCESS == dog_hb_pong_check(dog_hb_internal.handle)) // pong check
         {
            // DOG_HB_STATUS_SUCCESS

            qurt_anysignal_clear(&dog_hb_internal.anysignal, DOG_HB_DEVICE_PING_MASK);

            return;
         }
      }
   }

   // DOG_HB_STATUS_ERROR
}

/**
INTERNAL, QDI Opener Invocation Object
*/
static struct
{
   qurt_qdi_obj_t qdiobj;

} opener = { { DOG_HB_INVOCATION, QDI_REFCNT_PERM, 0 } };

/**
API, Initialization of service prior to use
*/
void dog_hb_user_init(void)
{
   qurt_pimutex_init(&dog_hb_internal.mutex);                                    // serialize driver access

   qurt_pimutex_lock(&dog_hb_internal.mutex);                                    // serialize driver access

   qurt_anysignal_init(&dog_hb_internal.anysignal);

   timer_def_osal(&dog_hb_internal.timer, NULL, TIMER_FUNC1_CB_TYPE, dog_hb_timer_callback, 0);

   timer_set_64(&dog_hb_internal.timer, DOG_HB_FREQ_CNT, DOG_HB_FREQ_CNT, T_MSEC); // periodic timer, never stops

   qurt_qdi_devname_register(DOG_HB_DEVICE, &opener.qdiobj);                     // register driver

   qurt_pimutex_unlock(&dog_hb_internal.mutex);                                  // serialize driver access

   // interface test

   if (DOG_HB_STATUS_SUCCESS < (dog_hb_internal.handle = dog_hb_init((char const*)DOG_HB_DEVICE_NAME_RESERVED, DOG_HB_SIG_ANYSIGNAL, &dog_hb_internal.anysignal, DOG_HB_DEVICE_PING_MASK)) &&
       DOG_HB_STATUS_SUCCESS == dog_hb_ping_check(dog_hb_internal.handle) &&     // manager
       DOG_HB_STATUS_SUCCESS == dog_hb_pong(dog_hb_internal.handle) &&           // self pong
       DOG_HB_STATUS_SUCCESS == dog_hb_pong_check(dog_hb_internal.handle))       // manager
   {
      unsigned int mask;

      if (DOG_HB_DEVICE_PING_MASK == ((mask = qurt_anysignal_get(&dog_hb_internal.anysignal)) & DOG_HB_DEVICE_PING_MASK))
      {
         // success
      }

      else
      {
         // fail
      }

      qurt_anysignal_clear(&dog_hb_internal.anysignal, DOG_HB_DEVICE_PING_MASK);
   }

   else
   {
      // fail
   }
}

/**
Termination of service following use
@return
None.
*/
void dog_hb_user_term(void)
{
   /* NULL */                                                                    /* DECISION TO NOT CLEANUP SERVICE FOR POST MORTEM REASONS */
}

DOG_HB_HANDLE dog_hb_init(char const* name, DOG_HB_SIG sig_t, void* sig_p, unsigned int sig_m)
{
   DOG_HB_HANDLE rc = -1;
   char device[DOG_HB_DEVICE_PATH_LEN + DOG_HB_DEVICE_NAME_LEN];

   if (DOG_HB_DEVICE_NAME_LEN > tms_utils_chr_length(name, DOG_HB_DEVICE_NAME_LEN) &&
       NULL != sig_p && 0 != sig_m &&
       sizeof(device) > tms_utils_chr_copy(device, sizeof(device), (char const*)DOG_HB_DEVICE, sizeof(device)) &&
       sizeof(device) > tms_utils_chr_append(device, sizeof(device), name, sizeof(device)))
   {
      rc = qurt_qdi_open(device, sig_t, sig_p, sig_m);
   }

   return rc;
}

DOG_HB_STATUS dog_hb_destroy(DOG_HB_HANDLE handle)
{
   DOG_HB_STATUS rc = DOG_HB_STATUS_ERROR;

   rc = 0 <= qurt_qdi_close(handle) ? DOG_HB_STATUS_SUCCESS : DOG_HB_STATUS_ERROR;

   return rc;
}

static DOG_HB_STATUS dog_hb_ping_check(DOG_HB_HANDLE handle)                     // manager
{
   DOG_HB_STATUS rc = DOG_HB_STATUS_ERROR;

   rc = 0 <= qurt_qdi_handle_invoke(handle, DOG_HB_METHOD_PING) ? DOG_HB_STATUS_SUCCESS : DOG_HB_STATUS_ERROR;

   return rc;
}

DOG_HB_STATUS dog_hb_pong(DOG_HB_HANDLE handle)                                  // client
{
   DOG_HB_STATUS rc = DOG_HB_STATUS_ERROR;

   rc = 0 <= qurt_qdi_handle_invoke(handle, DOG_HB_METHOD_PONG) ? DOG_HB_STATUS_SUCCESS : DOG_HB_STATUS_ERROR;

   return rc;
}

static DOG_HB_STATUS dog_hb_pong_check(DOG_HB_HANDLE handle)                     // manager
{
   DOG_HB_STATUS rc = DOG_HB_STATUS_ERROR;

   rc = 0 <= qurt_qdi_handle_invoke(handle, DOG_HB_METHOD_PONG_CHECK) ? DOG_HB_STATUS_SUCCESS : DOG_HB_STATUS_ERROR;

   return rc;
}

dog_report_type dog_hb_register_qurt(qurt_anysignal_t* sig_p, unsigned int sig_m)
{
   char task_name[QURT_MAX_NAME_LEN];

   qurt_thread_get_name(task_name, sizeof(task_name));

   return (dog_report_type)dog_hb_init((char const*)task_name, DOG_HB_SIG_ANYSIGNAL, sig_p, sig_m);
}

void dog_hb_report(dog_report_type ident)
{
   if (DOG_HB_STATUS_SUCCESS <= dog_hb_pong((DOG_HB_HANDLE)ident))
   {
   }
}

void dog_hb_deregister(dog_report_type ident)
{
   if (DOG_HB_STATUS_SUCCESS <= dog_hb_destroy((DOG_HB_HANDLE)ident))
   {
   }
}
