/** vi: tw=128 ts=3 sw=3 et
@file rcinit_ut.c
@brief This file contains the API for the Run Control Framework, API 2.0
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
$Header: //components/rel/core.adsp/2.6.1/debugtools/rcinit/src/rcinit_ut.c#1 $
$DateTime: 2014/10/16 12:45:40 $
$Change: 6781644 $
$Author: pwbldsvc $
===============================================================================*/

#include "string.h"
#include "stringl/stringl.h"
#include "rcinit_internal.h"

/////////////////////////////////////////////////////////////////////
// Localized Type Declarations
/////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////
// Localized Storage
/////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////
// Implementation
/////////////////////////////////////////////////////////////////////

// Black List : Remove

void rcinit_ut_blacklist(unsigned long list_count, RCINIT_NAME list[])
{
   unsigned long cnt, offset;

   // Iterate internal dictionary
   for (offset = 0; offset < rcinit_internal_name_map_size - 2; offset++)
   {
      // Iterate list
      for (cnt = 0; cnt < list_count; cnt++)
      {
         // Check if dictionary entry on list
         if (0 == strncmp(list[cnt], rcinit_internal_name_map[offset].name, strlen(rcinit_internal_name_map[offset].name)))
         {
            const rcinit_info_t* rcinit_p = rcinit_internal_name_map[offset].info_p;

            // Check if dictionary entry has an info entry
            if (RCINIT_NULL != rcinit_p &&
                (RCINIT_TASK_DALTASK == rcinit_p->type || RCINIT_TASK_POSIX == rcinit_p->type ||
                 RCINIT_TASK_QURTTASK == rcinit_p->type || RCINIT_TASK_REXTASK == rcinit_p->type) &&
                RCINIT_NULL != rcinit_p->handle)
            {
               // Remove Entry
               rcinit_p->handle->entry = RCINIT_ENTRY_NONE;
            }
         }
      }
   }
}

// White List : Retain

void rcinit_ut_whitelist(unsigned long list_count, RCINIT_NAME list[])
{
   unsigned long cnt, offset;

   // Iterate internal dictionary
   for (offset = 0; offset < rcinit_internal_name_map_size - 2; offset++)
   {
      // Iterate list
      for (cnt = 0; cnt < list_count; cnt++)
      {
         // Check if dictionary entry on list
         if (0 == strncmp(list[cnt], rcinit_internal_name_map[offset].name, strlen(rcinit_internal_name_map[offset].name)))
         {
            // Exit Loop
            break;
         }
      }

      // Check if dictionary entry found on list
      if (cnt >= list_count)
      {
         const rcinit_info_t* rcinit_p = rcinit_internal_name_map[offset].info_p;

         // Check if dictionary entry has an info entry
         if (RCINIT_NULL != rcinit_p &&
             (RCINIT_TASK_DALTASK == rcinit_p->type || RCINIT_TASK_POSIX == rcinit_p->type ||
              RCINIT_TASK_QURTTASK == rcinit_p->type || RCINIT_TASK_REXTASK == rcinit_p->type) &&
             RCINIT_NULL != rcinit_p->handle)
         {
            // Remove Entry
            rcinit_p->handle->entry = RCINIT_ENTRY_NONE;
         }
      }
   }
}
