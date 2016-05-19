#ifndef DOG_REX_H
#define DOG_REX_H
/**
@file dog.h
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
Qualcomm Confidential and Proprietary.
===============================================================================*/
/*=============================================================================
Edit History
$Header: //components/rel/core.adsp/2.6.1/api/debugtools/dog_rex.h#1 $
$DateTime: 2014/10/16 12:45:40 $
$Change: 6781644 $
$Author: pwbldsvc $
===============================================================================*/

#include "rex.h"
#include "dog_qurt.h"

/**

LEGACY NOTES, POTENTIAL IMPACT TO CLIENT API USE. Note, legacy API are
supplied only as linkable routines that perform no operations. Client
API use of the deprecated interfaces are to be removed by the client.

NO LONGER SUPPLIED: extern dog_report_type dog_*_rpt;
NO LONGER SUPPLIED: extern const rex_timer_cnt_type dog_*_rpt_time;
NO LONGER SUPPLIED: dog_get_report_period()
NO LONGER SUPPLIED: dog_register(), arguments for TCB ptr, and DeadlockCheck
NO LONGER SUPPLIED: dog_monitor_pause(), dog_monitor_resume()
NO LONGER SUPPLIED: dog_set_startup_time()
NO LONGER SUPPLIED: dog_crash_report()
NO LONGER SUPPLIED: dog_kick(), dog_autokick()

1. Clients will supply their own storage locations and declarations to utilize the API.
No longer does the API supply any convenience externs for Client use.

2. Clients will determine their own report period, and select from DOG_FAST_TIMEOUT, or
DOG_DEFAULT_TIMEOUT. Other values are not encouraged or directly supported.

3. Clients will not be allowed to supply any proxy arguments (different rex TCB pointer);
or deadlockcheck type values which were never implemented or supported by the API.

4. Clients will be required to register/deregister if participation in the API is not
desired. There is no concept of remaining registered and disabled in the API.

5. Clients do not get to adjust or impact the startup timers. The ownership of startup
time is not relegated to any Client API user.

6. Protection Domains are not allowed to take information from OS Domain. The crash
report pretty output is deprecated. Obtain starvation information from the QXDM F3 logging
mechanism -- only the information about detected starvation is actually relevant to triage
efforts.

7. dog_kick, dog_autokick mechanisms are not exported to Clients. Interfaces to any
WDT hardware mechanisms are not supplied to Clients for direct manipulation.

*/

#define EXTERN_DOG_RPT(x)        extern dog_report_type dog_##x##_rpt __attribute__((deprecated))
#define EXTERN_DOG_RPT_TIME(x)   extern rex_timer_cnt_type dog_##x##_rpt_time __attribute__((deprecated))

#define DOG_DYNAMIC_API 0x00000150 /**< LEGACY */

#if defined(__cplusplus)
extern "C"
{
#endif

/**
 Deprecated Client Convenience
 Remediation Instructions : Clients will remove references to storage locations
 supplied by this header file. Clients will define their own storage locations, and
 manage and use those storage locations as a client requried resource. Resources are
 not allocated by DOG.
*/
//EXTERN_DOG_RPT(dummy); /*<< Deprecated Client Convenience */
//EXTERN_DOG_RPT_TIME(dummy); /*<< Deprecated Client Convenience */

enum
{
   DOG_FAST_TIMEOUT = 2000,                                                      /**< MSEC, FAST, FASTER THAN THIS MAY NOT BE CHECKED */
   DOG_DEFAULT_TIMEOUT = 60000                                                   /**< MSEC, DEFAULT, USE THIS */
};

typedef enum                                                                     /**< deprecated, unused, remove references */
{
   DOG_RESET_MONITOR,                                                            /**< Resets the montior. */
   DOG_TURN_OFF_MONITOR                                                          /**< Turns off the montior. */

} dog_monitor_state;

typedef enum                                                                     /**< deprecated, unused, utilize DOG_DEADLKCHK_UNDEF only */
{
   DOG_DEADLKCHK_DISABLE = 0,                                                    /**< Disable. */
   DOG_DEADLKCHK_ENABLE = 1,                                                     /**< Enable. */
   DOG_DEADLKCHK_UNDEF = 0xff,                                                   /**< Undefined. */

} dog_deadlockcheck_type;

#if (defined(__GNUC__) && __GNUC__ >= 4) || defined(__clang__)
__attribute__((warn_unused_result, nonnull(1)))
#endif
static inline dog_report_type dog_register(void* unused1, unsigned int timeout, dog_deadlockcheck_type unused2)
{
   char task_name[QURT_MAX_NAME_LEN];
   time_timetick_type client_timeout;

   qurt_thread_get_name(task_name, sizeof(task_name));

   client_timeout = (time_timetick_type)timeout;

   return (dog_report_type)dog_sw_init(task_name, &client_timeout);
}

static inline void dog_report(dog_report_type ident)
{
   if (DOG_SW_STATUS_SUCCESS <= dog_sw_report((DOG_SW_HANDLE)ident))
   {
      ;
   }
}

static inline void dog_deregister(dog_report_type ident)
{
   if (DOG_SW_STATUS_SUCCESS <= dog_sw_destroy((DOG_SW_HANDLE)ident))
   {
      ;
   }
}

#undef DOG_HAS_CRASH_REPORT_API
static inline void dog_crash_report(void (*print_ptr)(char*))
{
   // NOT SUPPORTED FOR CLIENT CALLERS
   print_ptr("DOG: NO_DATA_WILL_BE_SUPPLIED\n");
}

static inline void dog_monitor_pause(dog_report_type ident)
{
   // NOT SUPPORTED FOR CLIENT CALLERS
}

static inline void dog_monitor_resume(dog_report_type ident)
{
   // NOT SUPPORTED FOR CLIENT CALLERS
}

static inline void dog_set_startup_time(unsigned int startup_time)
{
   // NOT SUPPORTED FOR CLIENT CALLERS
}

static inline unsigned int dog_get_report_period(dog_report_type ident)
{
   // NOT SUPPORTED FOR CLIENT CALLERS
   return 0;
}

static inline void dog_task_disable(boolean disable)
{
   // NOT SUPPORTED FOR CLIENT CALLERS
}

static inline void dog_gsm_autokick(boolean enable)
{
   // NOT SUPPORTED FOR CLIENT CALLERS
}

static inline void dog_autokick(boolean enable)
{
   // NOT SUPPORTED FOR CLIENT CALLERS
}

static inline void dog_kick(void)
{
   // NOT SUPPORTED FOR CLIENT CALLERS
}

static void dog_force_kick(void)
{
   // NOT SUPPORTED FOR CLIENT CALLERS
}

#if defined(__cplusplus)
}
#endif

#endif
