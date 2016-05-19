/** vi: tw=128 ts=3 sw=3 et
@file dog_sw_user.c
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
$Header: //components/rel/core.adsp/2.6.1/debugtools/dog/src/dog_sw_user.c#3 $
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
#include "dog_qurt.h"
#include "timer.h"
#include "tms_utils.h"

#if defined(DOG_TRACER_SWEVT)
#include "tracer.h"
#include "dog_tracer_swe.h"
#endif

/**
INTERNAL: Common Module Sizing Information; Do not directly reference as a client user.
*/

#define DOG_SW_DEVICE_PATH_LEN                    32                             /**< INTERNAL, Maximum Device Path Length */
#define DOG_SW_DEVICE_NAME_LEN                    QURT_MAX_NAME_LEN              /**< INTERNAL, Maximum Device Basename Length */
#define DOG_SW_DEVICE_NAME_RESERVED               "dogsw"                        /**< INTERNAL, Reserved Device Name */

#define DOG_SW_FREQ_CNT                           500                            /**< INTERNAL, Ping Frequency Time, MSEC */

#define DOG_SW_DEVICE                              "dogsw/"                      /**< INTERNAL, Device Prefix */

enum
{
   DOG_SW_METHOD_REPORT = QDI_PRIVATE,                                           /**< API, dog_sw_ping_check() */
   DOG_SW_METHOD_REPORT_CHECK,                                                   /**< API, dog_sw_report_check(), Manager Only */
   DOG_SW_METHOD_PING,
   DOG_SW_METHOD_MAX = DOG_SW_METHOD_PING
};

/////////////////////////////////////////////////////////////////////
// Localized Type Declarations
/////////////////////////////////////////////////////////////////////

struct dog_sw_device_s
{
   qurt_qdi_obj_t qdiobj;                                                        // required to be first

   char name[DOG_SW_DEVICE_NAME_LEN];

   uint32_t hash;

   int lock;                                                                     // resources in use

   struct dog_sw_device_s* next;

   // driver object specific

   time_timetick_type timeout;                                                   // client supplied timeout

   time_timetick_type count;                                                     // count down time

};

void dog_sw_user_term(void);                                                     // forward reference
static DOG_SW_STATUS dog_sw_report_check(DOG_SW_HANDLE handle);                  // forward reference

/////////////////////////////////////////////////////////////////////
// Localized Storage
/////////////////////////////////////////////////////////////////////

static struct dog_sw_internal_s
{
   qurt_mutex_t mutex;                                                           // serialize

   struct dog_sw_device_s* head;                                                 // head of device list

   timer_type timer;                                                             // internal timer

   DOG_SW_HANDLE handle;                                                         // internal handle

} dog_sw_internal;

/////////////////////////////////////////////////////////////////////
// Implementation Details
/////////////////////////////////////////////////////////////////////

static void DOG_SW_RELEASE(qurt_qdi_obj_t* qdiobj)
{
   struct dog_sw_device_s* device_p_curr;
   struct dog_sw_device_s* device_p_prev;

   device_p_curr = NULL;
   device_p_prev = NULL;

   qurt_pimutex_lock(&dog_sw_internal.mutex);                                    // serialize driver access

   for (device_p_curr = dog_sw_internal.head; NULL != device_p_curr; device_p_curr = device_p_curr->next)
   {
      if (qdiobj == (qurt_qdi_obj_t*)device_p_curr)
      {
         if (dog_sw_internal.head == device_p_curr)                              // head check
         {
            dog_sw_internal.head = device_p_curr->next;
         }

         else if (NULL != device_p_prev)
         {
            device_p_prev->next = device_p_curr->next;
         }

         // release device tracked resources

         // not driver owned : device_p_curr->anysignal_p

         if (0 != device_p_curr->lock)                                           // Lock still held
         {
            MSG_SPRINTF_3(MSG_SSID_TMS, MSG_LEGACY_ERROR, "device release abandoned %s %x %d", device_p_curr->name, device_p_curr->hash, 0);
         }

         else
         {
            MSG_SPRINTF_3(MSG_SSID_TMS, MSG_LEGACY_HIGH, "device release %s %x %d", device_p_curr->name, device_p_curr->hash, 0);
         }

         secure_memset(device_p_curr, 0, sizeof(*device_p_curr));

         free(device_p_curr);

         break;                                                                  // for ()
      }

      device_p_prev = device_p_curr;
   }

   qurt_pimutex_unlock(&dog_sw_internal.mutex);                                  // serialize driver access
}

static int DOG_SW_INVOCATION(int client_handle, qurt_qdi_obj_t* obj, int method, qurt_qdi_arg_t a1, qurt_qdi_arg_t a2, qurt_qdi_arg_t a3, qurt_qdi_arg_t a4, qurt_qdi_arg_t a5, qurt_qdi_arg_t a6, qurt_qdi_arg_t a7, qurt_qdi_arg_t a8, qurt_qdi_arg_t a9)
{
   int rc = DOG_SW_STATUS_ERROR;                                                 // failure
   struct dog_sw_device_s* device_p = (struct dog_sw_device_s*)obj;
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

   rc = DOG_SW_STATUS_ERROR;                                                     // failure

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
      case DOG_SW_METHOD_PING:
      {
         rc = DOG_SW_STATUS_SUCCESS;                                                // success

         break;                                                                     // switch ()
      }

      /**
      API, dog_sw_init
      */
      case QDI_OPEN:
      {
         qurt_pimutex_lock(&dog_sw_internal.mutex);                                 // serialize driver access

         do
         {
            char const* name = NULL == a1.ptr ? NULL : tms_utils_chr_last(a1.ptr, DOG_SW_DEVICE_PATH_LEN + DOG_SW_DEVICE_NAME_LEN, '/');

            if (NULL == name || 1 >= tms_utils_chr_length(name, sizeof(device_p->name))) // insures device name length minimum of 2 ("/?")
            {
               device_p = NULL;

               break;                                                               // do while ()
            }

            name++;                                                                 // skips the trailing '/' component of the device path prefix

            if (NULL == a2.ptr)
            {
               device_p = NULL;

               break;                                                               // do while ()
            }

            // locate existing named device

            for (device_p = dog_sw_internal.head; NULL != device_p; device_p = device_p->next)
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

               device_p->qdiobj.invoke = DOG_SW_INVOCATION;
               device_p->qdiobj.refcnt = QDI_REFCNT_INIT;
               device_p->qdiobj.release = DOG_SW_RELEASE;

               // device object init

               memsmove(device_p->name, sizeof(device_p->name), name, tms_utils_chr_length(name, sizeof(device_p->name)));

               device_p->hash = tms_utils_hash(device_p->name, sizeof(device_p->name));

               device_p->lock = 0;

               device_p->timeout = *(time_timetick_type*)a2.ptr;

               device_p->count = device_p->timeout + DOG_SW_FREQ_CNT;

               // link new into device list

               device_p->next = dog_sw_internal.head;
               dog_sw_internal.head = device_p;
            }

            else
            {
               // operate on existing
            }

         } while (0);

         qurt_pimutex_unlock(&dog_sw_internal.mutex);                               // serialize driver access

         if (NULL == device_p)
         {
            rc = DOG_SW_STATUS_ERROR;                                               // failure

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
      API, dog_sw_destroy
      */
      case QDI_CLOSE:
      {
         qurt_pimutex_lock(&dog_sw_internal.mutex);                                 // serialize driver access

         do
         {
            // operate on existing

         } while (0);

         qurt_pimutex_unlock(&dog_sw_internal.mutex);                               // serialize driver access

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
      API, dog_sw_report
      */
      case DOG_SW_METHOD_REPORT:
      {
         qurt_pimutex_lock(&dog_sw_internal.mutex);                                 // serialize driver access

         device_p->count = device_p->timeout;

         qurt_pimutex_unlock(&dog_sw_internal.mutex);                               // serialize driver access

         rc = DOG_SW_STATUS_SUCCESS;                                                // success

         MSG_SPRINTF_5(MSG_SSID_TMS, MSG_LEGACY_HIGH, "device report %s %x %d %s == %d", device_p->name, device_p->hash, pn.asid, task_name, rc);

         break;                                                                     // switch ()
      }

      /**
      API, dog_sw_report_check
      */
      case DOG_SW_METHOD_REPORT_CHECK:
      {
         struct dog_sw_device_s* device_p_curr;

         rc = DOG_SW_STATUS_SUCCESS;                                                // success

         qurt_pimutex_lock(&dog_sw_internal.mutex);                                 // serialize driver access

         for (device_p_curr = dog_sw_internal.head; NULL != device_p_curr; device_p_curr = device_p_curr->next)
         {
            if (DOG_SW_FREQ_CNT <= device_p_curr->timeout)                          // timeout check
            {
               if (DOG_SW_FREQ_CNT <= device_p_curr->count)                         // expire check
               {
                  device_p_curr->count = device_p_curr->count - DOG_SW_FREQ_CNT;
               }

               else
               {
                  rc = DOG_SW_STATUS_ERROR;                                         // failure

#if defined(DOG_FATAL_ERROR)
                  MSG_SPRINTF_4(MSG_SSID_TMS, MSG_LEGACY_FATAL, "DOG_SW detects starvation symptom of %s %x %d %s, seek triage with its owner", device_p_curr->name, device_p_curr->hash, pn.asid, task_name);
#else
                  MSG_SPRINTF_4(MSG_SSID_TMS, MSG_LEGACY_ERROR, "DOG_SW detects starvation symptom of %s %x %d %s, seek triage with its owner", device_p_curr->name, device_p_curr->hash, pn.asid, task_name);
#endif

                  break;                                                            // for ()
               }
            }

#if 0
            else
            {
               // Period Too Short, "always fail"

               MSG_SPRINTF_4(MSG_SSID_TMS, MSG_LEGACY_ERROR, "device report check impossible on %s %x %d %s, seek triage with its owner", device_p_curr->name, device_p_curr->hash, pn.asid, task_name);
            }
#endif
         }

         qurt_pimutex_unlock(&dog_sw_internal.mutex);                               // serialize driver access

         break;                                                                     // switch ()
      }
   }

   return rc;
}

static void dog_sw_timer_callback(timer_cb_data_type data)
{
   if (DOG_SW_STATUS_SUCCESS == dog_sw_report(dog_sw_internal.handle))           // self report
   {
      if (DOG_SW_STATUS_SUCCESS == dog_sw_report_check(dog_sw_internal.handle))
      {
         // DOG_SW_STATUS_SUCCESS

         return;
      }
   }

   // DOG_SW_STATUS_ERROR
}

/**
INTERNAL, QDI Opener Invocation Object
*/
static struct
{
   qurt_qdi_obj_t qdiobj;

} opener = { { DOG_SW_INVOCATION, QDI_REFCNT_PERM, 0 } };

/**
API, Initialization of service prior to use
@return
None.
*/
void dog_sw_user_init(void)
{
   time_timetick_type timeout = DOG_SW_FREQ_CNT * 3;

   qurt_pimutex_init(&dog_sw_internal.mutex);                                    // serialize driver access

   qurt_pimutex_lock(&dog_sw_internal.mutex);                                    // serialize driver access

   timer_def_osal(&dog_sw_internal.timer, NULL, TIMER_FUNC1_CB_TYPE, dog_sw_timer_callback, 0);

   timer_set_64(&dog_sw_internal.timer, DOG_SW_FREQ_CNT, DOG_SW_FREQ_CNT, T_MSEC); // periodic timer, never stops

   qurt_qdi_devname_register(DOG_SW_DEVICE, &opener.qdiobj);                     // register driver

   qurt_pimutex_unlock(&dog_sw_internal.mutex);                                  // serialize driver access

   // interface test

   if (DOG_SW_STATUS_SUCCESS < (dog_sw_internal.handle = dog_sw_init((char const*)DOG_SW_DEVICE_NAME_RESERVED, &timeout)) &&
       DOG_SW_STATUS_SUCCESS == dog_sw_report(dog_sw_internal.handle) &&         // self report
       DOG_SW_STATUS_SUCCESS == dog_sw_report_check(dog_sw_internal.handle))     // manager
   {
      // success
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
void dog_sw_user_term(void)
{
   /* NULL */                                                                    /* DECISION TO NOT CLEANUP SERVICE FOR POST MORTEM REASONS */
}

DOG_SW_HANDLE dog_sw_init(char const* name, time_timetick_type* timeout)
{
   DOG_SW_HANDLE rc = -1;
   char device[DOG_SW_DEVICE_PATH_LEN + DOG_SW_DEVICE_NAME_LEN];

   if (DOG_SW_DEVICE_NAME_LEN > tms_utils_chr_length(name, DOG_SW_DEVICE_NAME_LEN) &&
       NULL != timeout && DOG_SW_FREQ_CNT <= *timeout &&
       sizeof(device) > tms_utils_chr_copy(device, sizeof(device), (char const*)DOG_SW_DEVICE, sizeof(device)) &&
       sizeof(device) > tms_utils_chr_append(device, sizeof(device), name, sizeof(device)))
   {
      rc = qurt_qdi_open(device, timeout);
   }

   return rc;
}

DOG_SW_STATUS dog_sw_destroy(DOG_SW_HANDLE handle)
{
   DOG_SW_STATUS rc = DOG_SW_STATUS_ERROR;

   rc = 0 <= qurt_qdi_close(handle) ? DOG_SW_STATUS_SUCCESS : DOG_SW_STATUS_ERROR;

   return rc;
}

DOG_SW_STATUS dog_sw_report(DOG_SW_HANDLE handle)
{
   DOG_SW_STATUS rc = DOG_SW_STATUS_ERROR;

   rc = 0 <= qurt_qdi_handle_invoke(handle, DOG_SW_METHOD_REPORT) ? DOG_SW_STATUS_SUCCESS : DOG_SW_STATUS_ERROR;

   return rc;
}

static DOG_SW_STATUS dog_sw_report_check(DOG_SW_HANDLE handle)
{
   DOG_SW_STATUS rc = DOG_SW_STATUS_ERROR;

   rc = 0 <= qurt_qdi_handle_invoke(handle, DOG_SW_METHOD_REPORT_CHECK) ? DOG_SW_STATUS_SUCCESS : DOG_SW_STATUS_ERROR;

   return rc;
}
