/** vi: tw=128 ts=3 sw=3 et
@file rcinit_lookup.c
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
$Header: //components/rel/core.adsp/2.6.1/debugtools/rcinit/src/rcinit_lookup.c#1 $
$DateTime: 2014/10/16 12:45:40 $
$Change: 6781644 $
$Author: pwbldsvc $
===============================================================================*/

#include "ctype.h"
#include "rcinit_dal.h"
#include "rcinit_internal.h"

/////////////////////////////////////////////////////////////////////
// Localized Type Declarations
/////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////
// Localized Storage
/////////////////////////////////////////////////////////////////////

/*===========================================================================

 FUNCTION rcinit_internal_nmelen

 DESCRIPTION
 internal key handling routine to obtain length

 DEPENDENCIES
 none

 RETURN VALUE
 length of result sans terminator

 SIDE EFFECTS
 none

 ===========================================================================*/
int rcinit_internal_nmelen(RCINIT_NAME name)
{
   RCINIT_NAME ptr = name;                                                       // return result

   while ('\0' != *ptr)                                                          // iterate to locate NULL terminator
   {
      ptr++;                                                                     // setup for next comparision
   }

   return ptr - name;                                                            // return length of name (sans NULL terminator)
}

/*===========================================================================

 FUNCTION rcevt_internal_nmecmp

 DESCRIPTION
 internal key handling routine to lexical compare two names

 DEPENDENCIES
 none

 RETURN VALUE
 lexical comparision result

 SIDE EFFECTS
 will not exceed length passed in, should be sizeof() destination buffer

 ===========================================================================*/
int rcinit_internal_nmecmp(RCINIT_NAME name1, RCINIT_NAME name2, int len)
{
   if (0 == len)                                                                 // no work; return
   {
      return 0;                                                                  // lexical compare identical
   }

   while (len-- > 0 && tolower(*name1) == tolower(*name2))                       // iterate comparing names
   {
      if (0 == len || '\0' == *name1)                                            // len hits zero or NULL terminator
      {
         return 0;                                                               // lexical compare identical
      }

      name1++, name2++;                                                          // setup for next comparision
   }

   return(tolower(*name1) < tolower(*name2)) ? -1 : (tolower(*name1) > tolower(*name2)); // lexical analysis and return result (-1, 0, 1)
}

/*===========================================================================

 FUNCTION rcinit_internal_name_map_search

 DESCRIPTION
 internal name map search to locate rcinit_info offset in the internal
 rcinit_info database

 DEPENDENCIES
 none

 RETURN VALUE
 zero based offset on success
 -1 on failure

 SIDE EFFECTS
 none

 ===========================================================================*/
int rcinit_internal_name_map_search(RCINIT_NAME value, int len, int low, int high)
{
   while (low <= high)
   {
      int compare;
      int mid = (low + high) / 2;

      compare = rcinit_internal_nmecmp(rcinit_internal_name_map[mid].name, value, len); // compare array[mid] to value

      if (0 == compare)                                                          // array[mid] == value
      {
         return mid;
      }
      else if (compare > 0)                                                      // array[mid] > value
      {
         high = mid - 1;
      }
      else                                                                       // array[mid] < value
      {
         low = mid + 1;
      }
   }
   return -1;
}

int rcinit_internal_policy_map_search(RCINIT_NAME value, int len, int low, int high)
{
   while (low <= high)
   {
      int compare;
      int mid = (low + high) / 2;

      compare = rcinit_internal_nmecmp(rcinit_internal_policy_map[mid].name, value, len); // compare array[mid] to value

      if (0 == compare)                                                          // array[mid] == value
      {
         return mid;
      }
      else if (compare > 0)                                                      // array[mid] > value
      {
         high = mid - 1;
      }
      else                                                                       // array[mid] < value
      {
         low = mid + 1;
      }
   }
   return RCINIT_POLICY_NONE;
}

/*===========================================================================

 FUNCTION rcinit_lookup

 DESCRIPTION
 rcinit task database lookup accessor functions

 DEPENDENCIES
 none

 RETURN VALUE
 operation success

 SIDE EFFECTS
 none

 ===========================================================================*/

RCINIT_INFO rcinit_lookup(RCINIT_NAME name)
{
   int offset = rcinit_internal_name_map_search(name, rcinit_internal_nmelen(name) + 1, 0, rcinit_internal_name_map_size - 2);

   if (-1 != offset)
   {
      return(RCINIT_INFO)(rcinit_internal_name_map[offset].info_p);
   }

   return RCINIT_NULL;
}

RCINIT_INFO rcinit_lookup_self(void)
{
   const rcinit_info_t* rc = (const rcinit_info_t*)rcinit_internal_tls_get_specific(rcinit_internal.tls_key);

   return(RCINIT_INFO)rc;
}

RCINIT_NAME rcinit_lookup_name_info(RCINIT_INFO info)
{
   rcinit_info_t* rcinit_p = (rcinit_info_t*)info;

   return rcinit_p->name;
}

RCINIT_POLICY rcinit_lookup_policy(RCINIT_NAME name)
{
   int offset = rcinit_internal_policy_map_search(name, rcinit_internal_nmelen(name) + 1, 0, rcinit_internal_policy_map_size - 2);

   if (-1 != offset)
   {
      return rcinit_internal_policy_map[offset].index;
   }

   return RCINIT_POLICY_NONE;
}

RCINIT_POLICY rcinit_lookup_policy_current(void)
{
   return rcinit_internal.policy_curr;
}

void* rcinit_lookup_entry_info(RCINIT_INFO info)
{
   rcinit_info_t* rcinit_p = (rcinit_info_t*)info;

   return rcinit_p->entry;
}

void* rcinit_lookup_entry(RCINIT_NAME name)
{
   RCINIT_INFO info = rcinit_lookup(name);

   if (RCINIT_NULL != info)
   {
      return rcinit_lookup_entry_info(info);
   }

   return RCINIT_NULL;
}

RCINIT_PRIO rcinit_lookup_prio_info(RCINIT_INFO info)
{
   rcinit_info_t* rcinit_p = (rcinit_info_t*)info;

   return rcinit_p->prio;
}

RCINIT_PRIO rcinit_lookup_prio(RCINIT_NAME name)
{
   RCINIT_INFO info = rcinit_lookup(name);

   if (RCINIT_NULL != info)
   {
      return rcinit_lookup_prio_info(info);
   }

   return RCINIT_ZERO;
}

unsigned long rcinit_lookup_stksz_info(RCINIT_INFO info)
{
   rcinit_info_t* rcinit_p = (rcinit_info_t*)info;

   return rcinit_p->stksz;
}

unsigned long rcinit_lookup_stksz(RCINIT_NAME name)
{
   RCINIT_INFO info = rcinit_lookup(name);

   if (RCINIT_NULL != info)
   {
      return rcinit_lookup_stksz_info(info);
   }

   return RCINIT_ZERO;
}

unsigned long rcinit_lookup_cpu_affinity_info(RCINIT_INFO info)
{
   rcinit_info_t* rcinit_p = (rcinit_info_t*)info;

   return rcinit_p->cpu_affinity;
}

unsigned long rcinit_lookup_cpu_affinity(RCINIT_NAME name)
{
   RCINIT_INFO info = rcinit_lookup(name);

   if (RCINIT_NULL != info)
   {
      return rcinit_lookup_cpu_affinity_info(info);
   }

   return RCINIT_ZERO;
}

RCINIT_GROUP rcinit_lookup_group(RCINIT_NAME name)
{
   RCINIT_GROUP rc = RCINIT_GROUP_0;
   const rcinit_info_t*** rcinit_sequence_group;

   rcinit_sequence_group = rcinit_internal_groups[rcinit_internal.policy_curr];

   while (RCINIT_NULL != *rcinit_sequence_group)
   {
      const rcinit_info_t** rcinit_group = *rcinit_sequence_group;

      while (RCINIT_NULL != *rcinit_group)
      {
         const rcinit_info_t* rcinit_p = *rcinit_group;

         int compare = rcinit_internal_nmecmp(rcinit_p->name, name, rcinit_internal_nmelen(rcinit_p->name) + 1);

         if (0 == compare)
         {
            return rc;
         }

         rcinit_group++;                                                         // next; this group
      }

      rc++;                                                                      // processing next group

      rcinit_sequence_group++;                                                   // next; sequence group
   }

   return RCINIT_GROUP_NONE;                                                     // no task context in framework processing
}

RCINIT_GROUP rcinit_lookup_group_entry(void* entry)
{
   RCINIT_GROUP rc = RCINIT_GROUP_0;
   const rcinit_info_t*** rcinit_sequence_group;

   rcinit_sequence_group = rcinit_internal_groups[rcinit_internal.policy_curr];

   while (RCINIT_NULL != *rcinit_sequence_group)
   {
      const rcinit_info_t** rcinit_group = *rcinit_sequence_group;

      while (RCINIT_NULL != *rcinit_group)
      {
         const rcinit_info_t* rcinit_p = *rcinit_group;

         if (RCINIT_NULL != rcinit_p->entry)
         {
            if (rcinit_p->entry == entry)                                        // entry pointer associates with group
            {
               return rc;
            }
         }

         rcinit_group++;                                                         // next; this group
      }

      rc++;                                                                      // processing next group

      rcinit_sequence_group++;                                                   // next; sequence group
   }

   return RCINIT_GROUP_NONE;                                                     // no task context in framework processing
}

unsigned long rcinit_internal_nmehash(RCINIT_NAME const name)
{
   RCINIT_NAME s = name;
   unsigned long hash = 0;

   while ('\0' != *s)
   {
      unsigned long temp;

      hash = (hash << 4) + (unsigned long)(*s);

      if (0 != (temp = hash & 0xf0000000))
      {
         hash ^= (temp >> 24);
      }

      hash &= (~temp);

      s++;
   }

   return hash;
}

RCINIT_GROUP rcinit_lookup_group_current(void)
{
   return rcinit_internal.group_curr;
}
