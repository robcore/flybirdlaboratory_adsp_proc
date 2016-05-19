/** vi: tw=128 ts=3 sw=3 et
@file rcinit_rex_hs_list.c
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
$Header: //components/rel/core.adsp/2.6.1/debugtools/rcinit/src/rcinit_rex_hs_list.c#1 $
$DateTime: 2014/10/16 12:45:40 $
$Change: 6781644 $
$Author: pwbldsvc $
===============================================================================*/

#include "stringl/stringl.h"

#include "rcinit_rex.h"
#include "rcinit_internal.h"

/////////////////////////////////////////////////////////////////////
// Localized Type Declarations
/////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////
// Localized Storage
/////////////////////////////////////////////////////////////////////

static rex_crit_sect_type hs_mutex;                                              // mutex protection on hs_init/hs_term

/////////////////////////////////////////////////////////////////////
// Init Function Support
/////////////////////////////////////////////////////////////////////

unsigned long rcinit_internal_task_name(char* task_name, int buflen)
{
   rex_get_task_name(rex_self(), task_name, buflen, NULL);

   return rcinit_internal_nmehash(task_name);
}

void rcinit_internal_hs_list_init(void)
{
   unsigned long cnt = RCINIT_TASK_MAX;

   rex_init_crit_sect(&hs_mutex);                                                // mutex protection

   rex_enter_crit_sect(&hs_mutex);                                               // mutex protection

   for (cnt = 0; cnt < RCINIT_TASK_MAX; cnt++)
   {
      rcinit_internal.hs_init[cnt].group = RCINIT_GROUP_NONE;
      rcinit_internal.hs_term[cnt].group = RCINIT_GROUP_NONE;

      strlcpy(rcinit_internal.hs_init[cnt].task_name, "", sizeof(rcinit_internal.hs_init[cnt].task_name));
      strlcpy(rcinit_internal.hs_term[cnt].task_name, "", sizeof(rcinit_internal.hs_term[cnt].task_name));

      rcinit_internal.hs_init[cnt].hs = 0;
      rcinit_internal.hs_term[cnt].hs = 0;

      rcinit_internal.hs_init[cnt].hs_dup = 0;
      rcinit_internal.hs_term[cnt].hs_dup = 0;

      rcinit_internal.hs_init[cnt].hs_oob = 0;
      rcinit_internal.hs_term[cnt].hs_oob = 0;

      rcinit_internal.hs_init[cnt].tid = RCINIT_NULL;
      rcinit_internal.hs_term[cnt].tid = RCINIT_NULL;
   }

   rex_leave_crit_sect(&hs_mutex);                                               // mutex protection
}

unsigned long rcinit_internal_hs_list_add(rcinit_internal_hs_p array, RCINIT_GROUP group, RCINIT_NAME task_name)
{
   unsigned long cnt = RCINIT_TASK_MAX;

   rex_enter_crit_sect(&hs_mutex);                                               // mutex protection

   if (RCINIT_GROUP_7 >= group)
   {
      for (cnt = 0; cnt < RCINIT_TASK_MAX; cnt++)                                // find existing
      {
         if (0 == strncmp(task_name, array[cnt].task_name, sizeof(array[cnt].task_name)))
         {
            if (group == array[cnt].group)
            {
               break;
            }
         }
      }

      if (cnt < RCINIT_TASK_MAX)                                                 // update existing
      {
         // already set array[cnt].group = group;
         // already set strlcpy(array[cnt].task_name, task_name, sizeof(array[cnt].task_name));
         // already set array[cnt].tid = GET_SELF();
         array[cnt].hs = 0;
      }

      else
      {
         for (cnt = 0; cnt < RCINIT_TASK_MAX; cnt++)                             // find empty
         {
            if (array[cnt].group == RCINIT_GROUP_NONE)
            {
               break;
            }
         }

         if (cnt < RCINIT_TASK_MAX)                                              // update empty
         {
            array[cnt].group = group;
            strlcpy(array[cnt].task_name, task_name, sizeof(array[cnt].task_name));
            array[cnt].tid = rex_self();
            array[cnt].hs = 0;
         }
         else
         {
            cnt = RCINIT_TASK_MAX;
         }
      }
   }

   rex_leave_crit_sect(&hs_mutex);                                               // mutex protection

   return cnt;                                                                   // RCINIT_TASK_MAX == Not Present, !RCINIT_TASK_MAX = Present & Added
}

unsigned long rcinit_internal_hs_list_del(rcinit_internal_hs_p array, RCINIT_GROUP group, RCINIT_NAME task_name)
{
   unsigned long cnt = RCINIT_TASK_MAX;

   rex_enter_crit_sect(&hs_mutex);                                               // mutex protection

   if (RCINIT_GROUP_7 >= group)
   {
      for (cnt = 0; cnt < RCINIT_TASK_MAX; cnt++)                                // find existing
      {
         if (0 == strncmp(task_name, array[cnt].task_name, sizeof(array[cnt].task_name)))
         {
            if (group == array[cnt].group)
            {
               break;
            }
         }
      }

      if (cnt < RCINIT_TASK_MAX)                                                 // update existing
      {
         array[cnt].group = RCINIT_GROUP_NONE;
         //strlcpy(array[cnt].task_name, "", sizeof(array[cnt].task_name));
         //array[cnt].tid = RCINIT_NULL;
         //array[cnt].hs = 0;
      }
   }

   rex_leave_crit_sect(&hs_mutex);                                               // mutex protection

   return cnt;                                                                   // RCINIT_TASK_MAX == Not Present, !RCINIT_TASK_MAX = Present & Removed
}

unsigned long rcinit_internal_hs_list_query(rcinit_internal_hs_p array, RCINIT_GROUP group, RCINIT_NAME task_name)
{
   unsigned long cnt = RCINIT_TASK_MAX;

   rex_enter_crit_sect(&hs_mutex);                                               // mutex protection

   if (RCINIT_GROUP_7 >= group)
   {
      for (cnt = 0; cnt < RCINIT_TASK_MAX; cnt++)                                // find existing
      {
         if (0 == strncmp(task_name, array[cnt].task_name, sizeof(array[cnt].task_name)))
         {
            if (group == array[cnt].group)
            {
               break;
            }
         }
      }
   }

   rex_leave_crit_sect(&hs_mutex);                                               // mutex protection

   return cnt;                                                                   // RCINIT_TASK_MAX == Not Present, !RCINIT_TASK_MAX = Present
}

unsigned long rcinit_internal_hs_list_query_hs(rcinit_internal_hs_p array, RCINIT_GROUP group, RCINIT_NAME task_name)
{
   unsigned long cnt = RCINIT_TASK_MAX;

   rex_enter_crit_sect(&hs_mutex);                                               // mutex protection

   if (RCINIT_GROUP_7 >= group)
   {
      for (cnt = 0; cnt < RCINIT_TASK_MAX; cnt++)                                // find existing
      {
         if (0 == strncmp(task_name, array[cnt].task_name, sizeof(array[cnt].task_name)))
         {
            if (group == array[cnt].group)
            {
               if (1 == array[cnt].hs)
               {
                  break;
               }
            }
         }
      }
   }

   rex_leave_crit_sect(&hs_mutex);                                               // mutex protection

   return cnt;                                                                   // RCINIT_TASK_MAX == Not Present or No HS, !RCINIT_TASK_MAX = HS
}

unsigned long rcinit_internal_hs_list_hs(rcinit_internal_hs_p array, RCINIT_GROUP group, RCINIT_NAME task_name)
{
   unsigned long cnt;
   unsigned long rc = RCINIT_TASK_MAX;

   rex_enter_crit_sect(&hs_mutex);                                               // mutex protection

   if (RCINIT_GROUP_7 >= group)
   {
      for (cnt = 0; cnt < RCINIT_TASK_MAX; cnt++)                                // find existing
      {
         if (0 == strncmp(task_name, array[cnt].task_name, sizeof(array[cnt].task_name))) // check matching task name
         {
            if (group == array[cnt].group)                                       // check matching group
            {
               if (0 == array[cnt].hs)                                           // check first handshake
               {
                  // accept the handshake, it matches the group and is the first one
                  array[cnt].hs = 1;
                  rc = cnt;
               }
               else
               {
                  // statistics indicates this is duplicate; a task is not allowed to
                  // duplicate its handshake within the same group. this is not fatal,
                  // but it must not be counted in the total HS required for the group.
                  array[cnt].hs_dup++;
               }
            }
            else
            {
               // statistics indicates this is out of band; a task that registers for multiple
               // groups will have the OOB counters incremented for any group not current, the
               // behavior is not a problem, it is not fatal, but it must not be counted in the
               // total HS required for the group.
               array[cnt].hs_oob++;
            }
         }
      }
   }

   rex_leave_crit_sect(&hs_mutex);                                               // mutex protection

   return rc;                                                                    // RCINIT_TASK_MAX == Not Present or Spurious HS, !RCINIT_TASK_MAX = HS
}
