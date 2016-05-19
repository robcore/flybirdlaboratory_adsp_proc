#ifndef DOG_H
#define DOG_H
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
$Header: //components/rel/core.adsp/2.6.1/api/debugtools/dog.h#1 $
$DateTime: 2014/10/16 12:45:40 $
$Change: 6781644 $
$Author: pwbldsvc $
===============================================================================*/

#if 1

#warning "DEPRECATED INTERFACE. TECH AREA TO SELECT CORRECT NHLOS API HEADER DOG(QURT|REX).H"

#include "dog_qurt.h"   // NHLOS QURT API
#include "dog_rex.h"    // NHLOS REX API

#else

// LEGACY ONLY

#include "comdef.h"     /* Definitions for byte, word, etc. */
#include "task.h"       /* Task definitions                 */

/** @addtogroup dog_api @{ */

#define DOG_DYNAMIC_API   /* DOG 1.5 */

/** Represents the handle used in the Watchdog API. */
typedef unsigned int dog_report_type;

#define DOG_ATTRIBUTE_DEPRECATED __attribute__((deprecated))

/** Default timeouts (in ms) for use in dynamic API */

#define DOG_FAST_TIMEOUT        2000
#define DOG_DEFAULT_TIMEOUT     60000

/*------------------------------------------------------------------------*/

extern dog_report_type dog_hdrmc_rpt DOG_ATTRIBUTE_DEPRECATED;                   // TECH AREAS SUPPLY THEIR OWN TIMERS
extern dog_report_type dog_ftm_rpt DOG_ATTRIBUTE_DEPRECATED;                     // TECH AREAS SUPPLY THEIR OWN TIMERS

#define  DOG_HDRMC_RPT              dog_hdrmc_rpt             /* rpt_def */
#define  DOG_FTM_RPT                dog_ftm_rpt               /* rpt_def */

extern const rex_timer_cnt_type dog_plt_rpt_time DOG_ATTRIBUTE_DEPRECATED;       // TECH AREAS SUPPLY THEIR OWN TIMERS
extern const rex_timer_cnt_type dog_ftm_rpt_time DOG_ATTRIBUTE_DEPRECATED;       // TECH AREAS SUPPLY THEIR OWN TIMERS
extern const rex_timer_cnt_type dog_mgpmc_rpt_time DOG_ATTRIBUTE_DEPRECATED;     // TECH AREAS SUPPLY THEIR OWN TIMERS

#define  DOG_PLT_RPT_TIME                     dog_plt_rpt_time                    /* time_def */
#define  DOG_FTM_RPT_TIME                     dog_ftm_rpt_time                    /* time_def */
#define  DOG_MGPMC_RPT_TIME                   dog_mgpmc_rpt_time                  /* time_def */

/** Supported deadlock types. */
typedef enum {
   DOG_DEADLKCHK_DISABLE = 0,                                                    /**< Disable. */
   DOG_DEADLKCHK_ENABLE = 1,                                                     /**< Enable. */
   DOG_DEADLKCHK_UNDEF = 0xff,                                                   /**< Undefined. */
}
dog_deadlockcheck_type;

void dog_report(dog_report_type report);

void dog_autokick(boolean enable);

void dog_kick(void);

void dog_monitor_pause(dog_report_type report_id) DOG_ATTRIBUTE_DEPRECATED;

void dog_monitor_resume(dog_report_type report_id) DOG_ATTRIBUTE_DEPRECATED;

void dog_crash_report(void (*print_ptr)(char*));

dog_report_type dog_register_rex(rex_tcb_type* p_tcb, uint32 timeout, uint32 unused);
#define dog_register(x,y,z) dog_register_rex(x,y,z)

uint32 dog_get_report_period(dog_report_type dog_report_id) DOG_ATTRIBUTE_DEPRECATED;

void dog_deregister(dog_report_type dog_report_id);

#endif

#endif
