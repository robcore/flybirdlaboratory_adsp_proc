/** vi: tw=128 ts=3 sw=3 et
@file pd_dump.c
@brief This file contains the API details for the Protection Domain Monitor, API 1.0
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
$Header: //components/rel/core.adsp/2.6.1/debugtools/pd_mon/src/pd_dump.c#1 $
$DateTime: 2014/10/16 12:45:40 $
$Change: 6781644 $
$Author: pwbldsvc $
===============================================================================*/

#include "stdlib.h"
#include "stringl/stringl.h"

#include "qurt.h"
#include "qurt_qdi_driver.h"

#include "err.h"
#include "msg.h"
#include "tms_utils.h"
#include "rfsa_client.h"

#include "pd_dump.h"
#include "pd_elf.h"
#include "pd_elf_hexagon.h"
#include "pd_mon_qurt.h"

#if defined(PD_MON_TRACER_SWEVT)
#include "tracer.h"
#include "pd_mon_tracer_swe.h"
#endif

/////////////////////////////////////////////////////////////////////
// Localized Type Declarations
/////////////////////////////////////////////////////////////////////

struct pd_dump_device_s /**< localized driver storage area */
{
   qurt_qdi_obj_t qdiobj; /**< required to be first */

   char name[PD_DUMP_DEVICE_NAME_LEN]; /**< device name */

   uint32_t hash; /**< name hash */

   qurt_sysenv_procname_t pn; /**< client procname on open */

   Elf32_Ehdr elf_hdr; /**< ELF header */

   pd_elf_prgtab_p elf_prgtab_head; /**< linked list builds prgtab */

   pd_elf_sectab_p elf_sectab_head; /**< linked list builds sectab */

   struct pd_dump_device_s* next; /**< next device (one per user domain) */

   unsigned int counter; /**< read elf file counter */

   char filename[PD_DUMP_FILE_NAME_MAX]; /**< temporary filename construction buffer */

   int fd; /**< file descriptor rfsa */
};

struct MemBlock_s /**< qurt supplied with QDI_OS_DUMP_PROCESS_EXIT */
{
   void* addr;
   unsigned long len;
};

struct Thread_s /**< qurt supplied with QDI_OS_DUMP_PROCESS_EXIT */
{
   void* addr;
};

extern const char* pd_mon_internal_prefix; /**< RFSA Volume */

extern const char* pd_mon_internal_basename; /**< RFSA Basename */

/////////////////////////////////////////////////////////////////////
// Localized Storage
/////////////////////////////////////////////////////////////////////

static struct pd_dump_internal_s
{
   struct pd_dump_device_s* head;

   qurt_mutex_t mutex;

} pd_dump_internal;

/////////////////////////////////////////////////////////////////////
// Implementation Details
/////////////////////////////////////////////////////////////////////

static void pd_dump_device_release(qurt_qdi_obj_t* qdiobj)
{
   struct pd_dump_device_s* device_p_curr;
   struct pd_dump_device_s* device_p_prev;
   device_p_curr = NULL;
   device_p_prev = NULL;

   qurt_pimutex_lock(&pd_dump_internal.mutex); /**< serialize driver access */

   for (device_p_curr = pd_dump_internal.head; NULL != device_p_curr; device_p_curr = device_p_curr->next)
   {
      if (qdiobj == (qurt_qdi_obj_t*)device_p_curr)
      {
         if (NULL == device_p_prev) /**< head check */
         {
            pd_dump_internal.head->next = device_p_curr->next;
         }

         else
         {
            device_p_prev->next = device_p_curr->next;
         }

#if defined(PD_MON_TRACER_SWEVT)
         tracer_event_simple_vargs(PD_DUMP_SWE_R, 2, device_p_curr->hash, device_p_curr->pn.asid);
#endif
         MSG_SPRINTF_3(MSG_SSID_TMS, MSG_LEGACY_HIGH, "device release %s %x %d", device_p_curr->name, device_p_curr->hash, device_p_curr->pn.asid);

         free(qdiobj);

         break;
      }

      device_p_prev = device_p_curr;
   }

   if (NULL == device_p_curr)
   {
   }

   qurt_pimutex_unlock(&pd_dump_internal.mutex); /**< serialize driver access */
}

static int pd_dump_device_invocation(int client_handle, qurt_qdi_obj_t* obj, int method, qurt_qdi_arg_t a1, qurt_qdi_arg_t a2, qurt_qdi_arg_t a3, qurt_qdi_arg_t a4, qurt_qdi_arg_t a5, qurt_qdi_arg_t a6, qurt_qdi_arg_t a7, qurt_qdi_arg_t a8, qurt_qdi_arg_t a9)
{
   int rc;
   struct pd_dump_device_s* device_p = (struct pd_dump_device_s*)obj;
   qurt_sysenv_procname_t pn;

   /* client_handle means that we're asking this particular client handle to answer the question about its process */
   /* QDI_OS_SYSENV is the standard method for requesting this type of information */
   /* QDI_HANDLE_LOCAL_CLIENT means that this request originated locally */
   /* QURT_SYSENV_PROCNAME_TYPE is the specific piece of data being requested -- to fill in a qurt_sysenv_procname_t structure */
   /* &pn is the structure we want filled in */

   if (0 > (rc = qurt_qdi_handle_invoke(client_handle, QDI_OS_SYSENV, QDI_HANDLE_LOCAL_CLIENT, QURT_SYSENV_PROCNAME_TYPE, &pn)))
   {
#if defined(PD_MON_TRACER_SWEVT)
      tracer_event_simple_vargs(PD_DUMP_SWE_E, 2, 0, rc);
#endif
      MSG_SPRINTF_1(MSG_SSID_TMS, MSG_LEGACY_ERROR, "cannot obtain client asid %d", rc);

      return rc;
   }

   rc = PD_DUMP_STATUS_ERROR; /**< failure */

   if (NULL == device_p)
   {
      return rc;
   }

   /* Driver Methods */

   switch (method)
   {
      /**
      INTERNAL, Default Method Handler
      */
      default:
      {
         rc = qurt_qdi_method_default(client_handle, obj, method, a1, a2, a3, a4, a5, a6, a7, a8, a9); /**< pass along */

         break; /**< switch () */
      }

      /**
      API, pd_dump_init
      */
      case QDI_OPEN:
      {
         qurt_pimutex_lock(&pd_dump_internal.mutex); /**< serialize driver access */

         do
         {
            char const* name;

            if (NULL == a1.ptr)
            {
               name = NULL;
            }
            else
            {
               name = tms_utils_chr_last(a1.ptr, PD_DUMP_DEVICE_PATH_LEN + PD_DUMP_DEVICE_NAME_LEN, '/');
            }

            if (NULL == name || 1 >= tms_utils_chr_length(name, sizeof(device_p->name))) /**< insures device name length minimum of 2 ("/?") */
            {
               device_p = NULL;

               break; /**< do while () */
            }

            name++; /**< skips the trailing '/' component of the device path prefix */

            for (device_p = pd_dump_internal.head; NULL != device_p; device_p = device_p->next)
            {
               if (0 == tms_utils_chr_compare(device_p->name, sizeof(device_p->name), name, sizeof(device_p->name)))
               {
                  break; /**< for () */
               }
            }

            /** operate on new */

            if (NULL == device_p)
            {
               /** allocate new */

               if (NULL == (device_p = malloc(sizeof(*device_p))))
               {
                  break; /**< do while () */
               }

               /** initialize new */

               secure_memset(device_p, 0, sizeof(*device_p));

               device_p->qdiobj.invoke = pd_dump_device_invocation;
               device_p->qdiobj.refcnt = QDI_REFCNT_INIT;
               device_p->qdiobj.release = pd_dump_device_release;

               /** device object init */

               memsmove(device_p->name, sizeof(device_p->name), name, tms_utils_chr_length(name, sizeof(device_p->name)));

               device_p->hash = tms_utils_hash(device_p->name, sizeof(device_p->name));

               memsmove(&device_p->pn, sizeof(device_p->pn), &pn, sizeof(pn));

               /** link into device list */

               device_p->next = pd_dump_internal.head;
               pd_dump_internal.head = device_p;
            }

            else
            {
               /** operate on existing */
            }

         } while (0);

         qurt_pimutex_unlock(&pd_dump_internal.mutex); /**< serialize driver access */

         if (NULL == device_p)
         {
            rc = PD_DUMP_STATUS_ERROR; /**< failure */

#if defined(PD_MON_TRACER_SWEVT)
            tracer_event_simple_vargs(PD_DUMP_SWE_I, 2, 0, pn.asid);
#endif
            MSG_SPRINTF_2(MSG_SSID_TMS, MSG_LEGACY_ERROR, "device open NULL NA %d == %d", pn.asid, rc);
         }

         else
         {
            rc = qurt_qdi_handle_create_from_obj_t(client_handle, (qurt_qdi_obj_t*)device_p); /**< return handle */

#if defined(PD_MON_TRACER_SWEVT)
            tracer_event_simple_vargs(PD_DUMP_SWE_I, 2, device_p->hash, pn.asid);
#endif
            MSG_SPRINTF_4(MSG_SSID_TMS, MSG_LEGACY_HIGH, "device open %s %x %d == %d", device_p->name, device_p->hash, pn.asid, rc);
         }

         break; /**< switch () */
      }

      /**
      API, pd_dump_destroy
      */
      case QDI_CLOSE:
      {
         qurt_pimutex_lock(&pd_dump_internal.mutex); /**< serialize driver access */

         do
         {
            /** operate on existing */

         } while (0);

         qurt_pimutex_unlock(&pd_dump_internal.mutex); /**< serialize driver access */

         rc = PD_DUMP_STATUS_ERROR; /**< handle does not close */

#if defined(PD_MON_TRACER_SWEVT)
         tracer_event_simple_vargs(PD_DUMP_SWE_D, 2, device_p->hash, pn.asid);
#endif
         MSG_SPRINTF_4(MSG_SSID_TMS, MSG_LEGACY_HIGH, "device close %s %x %d == %d", device_p->name, device_p->hash, pn.asid, rc);

         break; /**< switch () */
      }

      /**
      INTERNAL, OS_DUMP_PROCESS_EXIT Handler
      a1.ptr is a pointer to a list of (address, size) pairs
      a2.num is the number of entries pointed to by a1.ptr
      a3.ptr is a pointer to a list of TCB addresses for the threads
      a4.num is the number of entries pointed to by a3.ptr
      a5.num is the size of each TCB
      */
      case QDI_OS_DUMP_PROCESS_EXIT:
      {
#if 1    // SHORT CIRCUIT

         rc = PD_DUMP_STATUS_SUCCESS; /**< this code path always reports success; check F3 logs for information */
         MSG_SPRINTF_4(MSG_SSID_TMS, MSG_LEGACY_ERROR, "device dump short circuit %s %s %x %d", device_p->filename, device_p->name, device_p->hash, pn.asid);

#else    // SHORT CIRCUIT

         int i;
         struct Thread_s* Thread = (struct Thread_s*)a3.ptr;
         struct MemBlock_s* MemBlock = (struct MemBlock_s*)a1.ptr;

#if defined(PD_MON_TRACER_SWEVT)
         tracer_event_simple_vargs(PD_DUMP_SWE_EDB, 2, device_p->hash, pn.asid);
#endif
         MSG_SPRINTF_3(MSG_SSID_TMS, MSG_LEGACY_HIGH, "device dump begin %s %x %d", device_p->name, device_p->hash, pn.asid);

         qurt_pimutex_lock(&pd_dump_internal.mutex); /**< serialize driver access */

         do
         {
            if (sizeof(device_p->filename) <= tms_utils_fmt(device_p->filename, sizeof(device_p->filename), PD_DUMP_FILE_ENABLE_TEMPLATE, pd_mon_internal_prefix, device_p->name))
            {
#if defined(PD_MON_TRACER_SWEVT)
               tracer_event_simple_vargs(PD_DUMP_SWE_EC, 2, device_p->hash, pn.asid);
#endif
               MSG_SPRINTF_4(MSG_SSID_TMS, MSG_LEGACY_ERROR, "device dump enable filename too long %s %s %x %d", device_p->filename, device_p->name, device_p->hash, pn.asid);

               break; /**< do while () */
            }

            device_p->fd = rfsa_open(device_p->filename, O_RDONLY); /**< opens .enable file (read) */

            if (0 > device_p->fd)
            {
#if defined(PD_MON_TRACER_SWEVT)
               tracer_event_simple_vargs(PD_DUMP_SWE_EC, 2, device_p->hash, pn.asid);
#endif
               MSG_SPRINTF_4(MSG_SSID_TMS, MSG_LEGACY_ERROR, "device dump not enabled %s %s %x %d", device_p->filename, device_p->name, device_p->hash, pn.asid);

               break; /**< do while () */
            }

            rfsa_close(device_p->fd); /**< close .enable file (read) */

            if (sizeof(device_p->filename) <= tms_utils_fmt(device_p->filename, sizeof(device_p->filename), PD_DUMP_FILE_COUNT_TEMPLATE, pd_mon_internal_prefix, device_p->name))
            {
#if defined(PD_MON_TRACER_SWEVT)
               tracer_event_simple_vargs(PD_DUMP_SWE_RC, 2, device_p->hash, pn.asid);
#endif
               MSG_SPRINTF_4(MSG_SSID_TMS, MSG_LEGACY_ERROR, "device dump count read filename too long %s %s %x %d", device_p->filename, device_p->name, device_p->hash, pn.asid);

               break; /**< do while () */
            }

            device_p->fd = rfsa_open(device_p->filename, O_RDONLY); /**< open .count file (read) */

            if (0 > device_p->fd || sizeof(device_p->counter) != rfsa_read(device_p->fd, (char*)&device_p->counter, sizeof(device_p->counter)))
            {
               device_p->counter = 0;

#if defined(PD_MON_TRACER_SWEVT)
               tracer_event_simple_vargs(PD_DUMP_SWE_RC, 2, device_p->hash, pn.asid);
#endif
               MSG_SPRINTF_4(MSG_SSID_TMS, MSG_LEGACY_ERROR, "device dump count read file not available %s %s %x %d", device_p->filename, device_p->name, device_p->hash, pn.asid);
            }

            else
            {
#if defined(PD_MON_TRACER_SWEVT)
               tracer_event_simple_vargs(PD_DUMP_SWE_RC, 2, device_p->hash, pn.asid);
#endif
               MSG_SPRINTF_5(MSG_SSID_TMS, MSG_LEGACY_ERROR, "device dump count read %s %d %s %x %d", device_p->filename, device_p->counter, device_p->name, device_p->hash, pn.asid);
            }

            rfsa_close(device_p->fd); /**< close .count file (read) */

            /**< BEGIN ALLOCATIONS : BE SENSITIVE NOT TO LEAK MEMORY */

            do
            {
               device_p->elf_prgtab_head = NULL; /**< prepare ELF headers */
               device_p->elf_sectab_head = NULL; /**< prepare ELF headers */

               if (PD_ELF_STATUS_SUCCESS != pd_elf_init(&device_p->elf_hdr, &device_p->elf_prgtab_head, &device_p->elf_sectab_head))
               {
#if defined(PD_MON_TRACER_SWEVT)
                  tracer_event_simple_vargs(PD_DUMP_SWE_HIE, 2, device_p->hash, pn.asid);
#endif
                  MSG_SPRINTF_4(MSG_SSID_TMS, MSG_LEGACY_ERROR, "device dump headers init error %s %s %x %d", device_p->filename, device_p->name, device_p->hash, pn.asid);

                  break; /**< do while () */
               }

               if (PD_ELF_STATUS_SUCCESS != pd_elf_prgtab_alloc(&device_p->elf_hdr, &device_p->elf_prgtab_head, PT_NOTE, ".name", NT_HEXAGON_DUMP_NAME, device_p->name, sizeof(device_p->name)))
               {
#if defined(PD_MON_TRACER_SWEVT)
                  tracer_event_simple_vargs(PD_DUMP_SWE_HPE, 2, device_p->hash, pn.asid);
#endif
                  MSG_SPRINTF_4(MSG_SSID_TMS, MSG_LEGACY_ERROR, "device dump headers alloc error in prgtab .name %s %s %x %d", device_p->filename, device_p->name, device_p->hash, pn.asid);

                  break; /**< do while () */
               }

#if 0
               if (PD_ELF_STATUS_SUCCESS != pd_elf_prgtab_alloc(&device_p->elf_hdr, &device_p->elf_prgtab_head, PT_NOTE, ".process", NT_HEXAGON_DUMP_PROCESS, &pn, sizeof(pn)))
               {
#if defined(PD_MON_TRACER_SWEVT)
                  tracer_event_simple_vargs(PD_DUMP_SWE_HPE, 2, device_p->hash, pn.asid);
#endif
                  MSG_SPRINTF_4(MSG_SSID_TMS, MSG_LEGACY_ERROR, "device dump headers alloc error in prgtab .process %s %s %x %d", device_p->filename, device_p->name, device_p->hash, pn.asid);

                  break; /**< do while () */
               }
#endif

               for (i = 0; i < a4.num; i++)
               {
                  char buf[64];

                  if (sizeof(buf) > tms_utils_fmt(buf, sizeof(buf), ".context.0x%x@0x%x", a5.num, (unsigned int)Thread[i].addr))
                  {
                     if (PD_ELF_STATUS_SUCCESS != pd_elf_prgtab_alloc(&device_p->elf_hdr, &device_p->elf_prgtab_head, PT_NOTE, buf, NT_HEXAGON_DUMP_CONTEXT, Thread[i].addr, a5.num))
                     {
#if defined(PD_MON_TRACER_SWEVT)
                        tracer_event_simple_vargs(PD_DUMP_SWE_HPE, 2, device_p->hash, pn.asid);
#endif
                        MSG_SPRINTF_4(MSG_SSID_TMS, MSG_LEGACY_ERROR, "device dump headers alloc error in prgtab .context %s %s %x %d", device_p->filename, device_p->name, device_p->hash, pn.asid);

                        break; /**< for () */
                     }
                  }
               }

               for (i = 0; i < a2.num; i++)
               {
                  char buf[64];

                  if (sizeof(buf) > tms_utils_fmt(buf, sizeof(buf), ".data.0x%x@0x%x", (unsigned int)MemBlock[i].len, (unsigned int)MemBlock[i].addr))
                  {
                     if (PD_ELF_STATUS_SUCCESS != pd_elf_prgtab_alloc(&device_p->elf_hdr, &device_p->elf_prgtab_head, PT_LOAD, buf, NT_NONE, MemBlock[i].addr, MemBlock[i].len))
                     {
#if defined(PD_MON_TRACER_SWEVT)
                        tracer_event_simple_vargs(PD_DUMP_SWE_HPE, 2, device_p->hash, pn.asid);
#endif
                        MSG_SPRINTF_4(MSG_SSID_TMS, MSG_LEGACY_ERROR, "device dump headers alloc error in prgtab .data %s %s %x %d", device_p->filename, device_p->name, device_p->hash, pn.asid);

                        break; /**< for () */
                     }
                  }
               }

               if (PD_ELF_STATUS_SUCCESS != pd_elf_sectab_alloc(&device_p->elf_hdr, &device_p->elf_sectab_head, SHT_NULL, SHN_UNDEF))
               {
#if defined(PD_MON_TRACER_SWEVT)
                  tracer_event_simple_vargs(PD_DUMP_SWE_HSE, 2, device_p->hash, pn.asid);
#endif
                  MSG_SPRINTF_4(MSG_SSID_TMS, MSG_LEGACY_ERROR, "device dump headers alloc error in sectab %s %s %x %d", device_p->filename, device_p->name, device_p->hash, pn.asid);

                  break; /**< do while () */
               }

               if (PD_ELF_STATUS_SUCCESS != pd_elf_prepare_offsets(&device_p->elf_hdr, &device_p->elf_prgtab_head, &device_p->elf_sectab_head))
               {
#if defined(PD_MON_TRACER_SWEVT)
                  tracer_event_simple_vargs(PD_DUMP_SWE_HOE, 2, device_p->hash, pn.asid);
#endif
                  MSG_SPRINTF_4(MSG_SSID_TMS, MSG_LEGACY_ERROR, "device dump headers offsets error %s %s %x %d", device_p->filename, device_p->name, device_p->hash, pn.asid);

                  break; /**< do while () */
               }

               if (sizeof(device_p->filename) <= tms_utils_fmt(device_p->filename, sizeof(device_p->filename), PD_DUMP_FILE_ELF_TEMPLATE, pd_mon_internal_prefix, device_p->name, device_p->counter))
               {
#if defined(PD_MON_TRACER_SWEVT)
                  tracer_event_simple_vargs(PD_DUMP_SWE_OE, 2, device_p->hash, pn.asid);
#endif
                  MSG_SPRINTF_4(MSG_SSID_TMS, MSG_LEGACY_ERROR, "device dump elf filename too long %s %s %x %d", device_p->filename, device_p->name, device_p->hash, pn.asid);

                  break; /**< do while () */
               }

               device_p->fd = rfsa_open(device_p->filename, O_WRONLY | O_CREAT); /**< open .elf file (write) */

               if (0 > device_p->fd)
               {
#if defined(PD_MON_TRACER_SWEVT)
                  tracer_event_simple_vargs(PD_DUMP_SWE_OE, 2, device_p->hash, pn.asid);
#endif
                  MSG_SPRINTF_4(MSG_SSID_TMS, MSG_LEGACY_ERROR, "device dump elf file not available %s %s %x %d", device_p->filename, device_p->name, device_p->hash, pn.asid);

                  break; /**< do while () */
               }

               if (PD_ELF_STATUS_SUCCESS != pd_elf_write(&device_p->elf_hdr, &device_p->elf_prgtab_head, &device_p->elf_sectab_head, device_p->fd))
               {
#if defined(PD_MON_TRACER_SWEVT)
                  tracer_event_simple_vargs(PD_DUMP_SWE_WE, 2, device_p->hash, pn.asid);
#endif
                  MSG_SPRINTF_4(MSG_SSID_TMS, MSG_LEGACY_ERROR, "device dump elf file not written %s %s %x %d", device_p->filename, device_p->name, device_p->hash, pn.asid);

                  rfsa_close(device_p->fd); /**< close .elf file (write) */

                  device_p->fd = rfsa_open(device_p->filename, O_WRONLY | O_CREAT); /**< open .elf file (write) */

                  if (0 > device_p->fd || sizeof(device_p->counter) != rfsa_write(device_p->fd, (char*)&device_p->counter, sizeof(device_p->counter)))
                  {
                     MSG_SPRINTF_4(MSG_SSID_TMS, MSG_LEGACY_ERROR, "device dump elf file truncated, no valid content %s %s %x %d", device_p->filename, device_p->name, device_p->hash, pn.asid);
                  }
                  else
                  {
                     MSG_SPRINTF_4(MSG_SSID_TMS, MSG_LEGACY_ERROR, "device dump elf file truncated, invalid content %s %s %x %d", device_p->filename, device_p->name, device_p->hash, pn.asid);
                  }

                  break; /**< do while () */
               }

            } while (0); /**< memory potentially still allocated */

            rfsa_close(device_p->fd); /**< close .elf file (write) */

            if (PD_ELF_STATUS_SUCCESS != pd_elf_term(&device_p->elf_hdr, &device_p->elf_prgtab_head, &device_p->elf_sectab_head))
            {
#if defined(PD_MON_TRACER_SWEVT)
               tracer_event_simple_vargs(PD_DUMP_SWE_HD, 2, device_p->hash, pn.asid);
#endif
               MSG_SPRINTF_4(MSG_SSID_TMS, MSG_LEGACY_ERROR, "device dump headers destroy error %s %s %x %d", device_p->filename, device_p->name, device_p->hash, pn.asid);

               // ERR_FATAL("resources not released properly", 0, 0, 0);

               break; /**< do while () */
            }

            /**< END ALLOCATIONS : BE SENSITIVE NOT TO LEAK MEMORY */

            device_p->counter++;

            if (sizeof(device_p->filename) <= tms_utils_fmt(device_p->filename, sizeof(device_p->filename), PD_DUMP_FILE_COUNT_TEMPLATE, pd_mon_internal_prefix, device_p->name))
            {
#if defined(PD_MON_TRACER_SWEVT)
               tracer_event_simple_vargs(PD_DUMP_SWE_WC, 2, device_p->hash, pn.asid);
#endif
               MSG_SPRINTF_4(MSG_SSID_TMS, MSG_LEGACY_ERROR, "device dump count write filename too long %s %s %x %d", device_p->filename, device_p->name, device_p->hash, pn.asid);

               break; /**< do while () */
            }

            device_p->fd = rfsa_open(device_p->filename, O_WRONLY | O_CREAT); /**< open .count file (write) */

            if (0 > device_p->fd || sizeof(device_p->counter) != rfsa_write(device_p->fd, (char*)&device_p->counter, sizeof(device_p->counter)))
            {
#if defined(PD_MON_TRACER_SWEVT)
               tracer_event_simple_vargs(PD_DUMP_SWE_WC, 2, device_p->hash, pn.asid);
#endif
               MSG_SPRINTF_4(MSG_SSID_TMS, MSG_LEGACY_ERROR, "device dump count write file not available %s %s %x %d", device_p->filename, device_p->name, device_p->hash, pn.asid);
            }

            else
            {
#if defined(PD_MON_TRACER_SWEVT)
               tracer_event_simple_vargs(PD_DUMP_SWE_WC, 2, device_p->hash, pn.asid);
#endif
               MSG_SPRINTF_5(MSG_SSID_TMS, MSG_LEGACY_ERROR, "device dump count write %s %d %s %x %d", device_p->filename, device_p->counter, device_p->name, device_p->hash, pn.asid);
            }

            rfsa_close(device_p->fd); /**< close .count file (write) */

         } while (0);

         qurt_pimutex_unlock(&pd_dump_internal.mutex); /**< serialize driver access */

         rc = PD_DUMP_STATUS_SUCCESS; /**< this code path always reports success; check F3 logs for information */

         // rc = qurt_qdi_method_default(client_handle, obj, method, a1, a2, a3, a4, a5, a6, a7, a8, a9);

#if defined(PD_MON_TRACER_SWEVT)
         tracer_event_simple_vargs(PD_DUMP_SWE_EDE, 2, device_p->hash, pn.asid);
#endif
         MSG_SPRINTF_4(MSG_SSID_TMS, MSG_LEGACY_HIGH, "device dump process exit %s %x %d == %d", device_p->name, device_p->hash, pn.asid, rc);

#endif   // SHORT CIRCUIT

         break; /**< switch () */
      }
   }

   return rc;
}

/**
INTERNAL, QDI Opener Invocation Object
*/
static struct
{
   qurt_qdi_obj_t qdiobj;

} opener = { { pd_dump_device_invocation, QDI_REFCNT_PERM, 0 } };

/**
API, Initialization of service prior to use
@return
None.
*/
void pd_dump_host_init(void)
{
   qurt_pimutex_init(&pd_dump_internal.mutex); /**< serialize driver access */

   qurt_pimutex_lock(&pd_dump_internal.mutex); /**< serialize driver access */

   qurt_qdi_devname_register(PD_DUMP_DEVICE, &opener.qdiobj); /**< register driver */

   qurt_pimutex_unlock(&pd_dump_internal.mutex); /**< serialize driver access */
}

/**
Termination of service following use
@return
None.
*/
void pd_dump_host_term(void)
{
   /* NULL */ /* DECISION TO NOT CLEANUP SERVICE FOR POST MORTEM REASONS */
}
