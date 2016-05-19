/*====*====*====*====*====*====*====*====*====*====*====*====*====*====*====*

                      ERR service crash simulator
                
GENERAL DESCRIPTION
  Command handler for injecting various types of crashes for testing

INITIALIZATION AND SEQUENCING REQUIREMENTS
  Diag must be initialized

Copyright (c) 2013 -2014 by QUALCOMM Technologies, Incorporated.  All Rights Reserved.
*====*====*====*====*====*====*====*====*====*====*====*====*====*====*====*/


/*==========================================================================

                        EDIT HISTORY FOR MODULE
$Header: //components/rel/core.adsp/2.6.1/debugtools/eic/src/err_inject_crash.c#2 $

when       who     what, where, why
--------   ---     ------------------------------------------------------------
07/23/14   din     Removed warnings for llvm .
04/18/14   din     Added changes for ADSP island mode.
08/01/13   rks     Incorporated the timer API changes
10/28/11   mcg     File created.

===========================================================================*/

#ifndef ERR_INJECT_CRASH
  #error Required definition is missing, check configuration
#endif //ERR_INJECT_CRASH

/*===========================================================================

                     INCLUDE FILES FOR MODULE

===========================================================================*/

#include "err.h"
#include "err_inject_crash.h"
#include "diagpkt.h"
#include "tms_diag.h"
#include "diagcmd.h"
#include "osal.h"
#include "msg.h"
#include "timer.h"
#include "utimer.h"
#include "uTimetick.h"
#include "qurt.h"
#include <stdint.h>
#include "DALSysTypes.h"
#include "DALPropDef.h"




/*===========================================================================

                     EXTERNAL FUNCTION PROTOTYPES

===========================================================================*/
void * err_inject_crash_diag (void *, uint16);
void * err_inject_crash_diag_uimg (void * req_ptr, uint16 pkt_len);


/*===========================================================================

                     INTERNAL DATA DECLARATIONS

===========================================================================*/
// default value if no delay is provided (min value for device config input)
#define ERR_INJECT_CRASH_DELAY_DIAG_DEFAULT  1
#define ERR_INJECT_CRASH_DELAY_DEVCFG_MIN   60

/* table for diag packet command handler registration */
static diagpkt_user_table_entry_type err_inject_crash_diagpkt_tbl[TMS_DIAG_TBLSIZE];

typedef PACK(struct) 
{
  diagpkt_subsys_header_type hdr;
  uint8 crash_type;
  uint8 crash_delay;
} err_inject_crash_req_type;


static volatile int err_inject_crash_zero = 0;

static timer_type       eicTimer;
static timer_group_type eic_timer_group;
static boolean          crash_pending = FALSE;

typedef enum
{
  ERR_UIMAGE_MODE,
  ERR_MAINIMAGE_MODE
} err_image_mode_t;

/* Data Declarations for uImage */
typedef struct err_uImage_crash_info_s
{
  boolean               is_crash_set;
  err_inject_crash_type crash;
  uint8                 delay;
  err_image_mode_t      image_mode;
} err_uImage_crash_info_t;

static err_uImage_crash_info_t crash_info UERR_DATA_SECTION;
static utimer_type      uImage_timer      UERR_DATA_SECTION;
#define ERR_UIMAGE_TIMER_PERIOD_REPEAT 1   

/*===========================================================================

                        Private function prototypes

===========================================================================*/
extern void err_dog_force_bite(void);

static void err_inject_crash_err_fatal(void) UERR_CODE_SECTION;
static void err_inject_crash_wdog(void) UERR_CODE_SECTION;
static void err_inject_null_access(void) UERR_CODE_SECTION;
static void err_inject_crash_div0(void) UERR_CODE_SECTION;

static void err_inject_crash_initiate(err_inject_crash_type, uint32, 
		                      err_image_mode_t image_mode);
static void err_inject_crash_execute(timer_cb_data_type);
static void err_inject_crash_devcfg_check(void);
void err_inject_uImage_crash_execute( utimer_cb_data_type crash_type) UERR_CODE_SECTION;


/*===========================================================================

                              Function definitions

===========================================================================*/


/*===========================================================================

FUNCTION err_inject_crash_init

DESCRIPTION
  Initializes the crash injection feature

DEPENDENCIES
  diag must be available to register command handler

RETURN VALUE
  None

SIDE EFFECTS
  None

===========================================================================*/
void err_inject_crash_init (void)
{
#ifndef ERR_USES_DEVCFG
  ERR_FATAL("Device Config must be enabled for crash injection",0,0,0);
#endif //ERR_USES_DEVCFG
  //Check for device config method before registering with diag (thus avoiding a mutex)
  err_inject_crash_devcfg_check();
  err_inject_crash_diagpkt_tbl[0] = tms_diag_build_table_entry( TMS_DIAGPKT_ERR_CORE_DUMP, err_inject_crash_diag);
  #ifdef USES_ISLAND
    err_inject_crash_diagpkt_tbl[1] = tms_diag_build_table_entry_uimg( TMS_DIAGPKT_ERR_CORE_DUMP, err_inject_crash_diag_uimg);
  #endif
  DIAGPKT_DISPATCH_TABLE_REGISTER_PROC (ERR_DIAG_PROC_ID, DIAG_SUBSYS_DEBUG, err_inject_crash_diagpkt_tbl);
                                         
  //initialize timer group to be safe
  memset(&eic_timer_group, 0, sizeof(eic_timer_group)); 
  timer_def_osal(&eicTimer, &eic_timer_group, TIMER_FUNC1_CB_TYPE, err_inject_crash_execute, (timer_cb_data_type)&crash_info);
                                       
}

/*===========================================================================

FUNCTION err_inject_crash_diag

DESCRIPTION
  Force a crash to occur remotely by calling ERR_FATAL

DEPENDENCIES
  err_init must be called prior

RETURN VALUE
  Pointer to the response packet of the req_ptr

SIDE EFFECTS

===========================================================================*/
void *
err_inject_crash_diag (void * req_ptr, uint16 pkt_len)
{
  err_inject_crash_req_type *req;
  err_inject_crash_type injected_crash = ERR_INJECT_ERR_FATAL;
  uint8 injected_delay = ERR_INJECT_CRASH_DELAY_DIAG_DEFAULT;

  // Diag only handles one request at a time, and dalcfg is checked before we register with diag
  // so simple mutual exclusion is sufficient (for now)  
  if (crash_pending)
  {
    MSG(MSG_SSID_TMS, MSG_LEGACY_HIGH,"err_inject_crash: crash pending, ignoring subsequent request");
    tms_diag_send_generic_response(req_ptr);
    return(NULL);
  }
  else
  {
    crash_pending = TRUE;  //set before diag response to guarantee no reentrancy issues
    tms_diag_send_generic_response(req_ptr);
  }
  
  // decode request
  req = (err_inject_crash_req_type *) req_ptr;

  // default parameters
  if (pkt_len <= sizeof(req->hdr)) 
  {
    injected_crash = ERR_INJECT_ERR_FATAL;
    injected_delay = ERR_INJECT_CRASH_DELAY_DIAG_DEFAULT;
  }
  // default delay parameter
  else if (pkt_len <= (sizeof(req->hdr) + sizeof(req->crash_type)) )
  {
    injected_crash = (err_inject_crash_type)(req->crash_type);
    injected_delay = ERR_INJECT_CRASH_DELAY_DIAG_DEFAULT;
  }
  else
  {
    injected_crash = (err_inject_crash_type)(req->crash_type);
    injected_delay = (err_inject_crash_type)(req->crash_delay);
  }

  err_inject_crash_initiate(injected_crash, injected_delay, ERR_MAINIMAGE_MODE);

  return(NULL);  //return NULL since we already called diagpkt_commit above
}



/*===========================================================================

FUNCTION err_inject_crash_diag_uimg

DESCRIPTION
  Force a crash to occur remotely by calling ERR_FATAL

DEPENDENCIES
  err_init must be called prior

RETURN VALUE
  Pointer to the response packet of the req_ptr

SIDE EFFECTS

===========================================================================*/
void *
err_inject_crash_diag_uimg (void * req_ptr, uint16 pkt_len)
{
  err_inject_crash_req_type *req;
  err_inject_crash_type injected_crash = ERR_INJECT_ERR_FATAL;
  uint8 injected_delay = ERR_INJECT_CRASH_DELAY_DIAG_DEFAULT;

  // Diag only handles one request at a time, and dalcfg is checked before we register with diag
  // so simple mutual exclusion is sufficient (for now)  
  if (crash_pending)
  {
    MSG(MSG_SSID_TMS, MSG_LEGACY_HIGH,"err_inject_crash: crash pending, ignoring subsequent request");
    tms_diag_send_generic_response(req_ptr);
    return(NULL);
  }
  else
  {
    crash_pending = TRUE;  //set before diag response to guarantee no reentrancy issues
    tms_diag_send_generic_response(req_ptr);
  }

  // decode request
  req = (err_inject_crash_req_type *) req_ptr;

  // default parameters
  if (pkt_len <= sizeof(req->hdr)) 
  {
    injected_crash = ERR_INJECT_ERR_FATAL;
    injected_delay = ERR_INJECT_CRASH_DELAY_DIAG_DEFAULT;
  }
  // default delay parameter
  else if (pkt_len <= (sizeof(req->hdr) + sizeof(req->crash_type)) )
  {
    injected_crash = (err_inject_crash_type)(req->crash_type);
    injected_delay = ERR_INJECT_CRASH_DELAY_DIAG_DEFAULT;
  }
  else
  {
    injected_crash = (err_inject_crash_type)(req->crash_type);
    injected_delay = (err_inject_crash_type)(req->crash_delay);
  }

  err_inject_crash_initiate(injected_crash, injected_delay, ERR_UIMAGE_MODE);

  return(NULL);
}



/*===========================================================================

FUNCTION err_inject_crash_initiate

DESCRIPTION
  Initiates the crash task which will perform the actual crash once timer expires

DEPENDENCIES
  err_init must be called prior

RETURN VALUE

SIDE EFFECTS

===========================================================================*/
void err_inject_crash_initiate
(
  err_inject_crash_type req_crash, 
  uint32 req_delay,
  err_image_mode_t image_mode
)
{
  // validate crash cause
  if (req_crash >= SIZEOF_ERR_INJECT_CRASH_TYPE) 
  {
    //do not err_fatal, as this may present false positives
    MSG_1(MSG_SSID_TMS, MSG_LEGACY_ERROR,"err_inject_crash: invalid crash ID %#x", req_crash);
    return;
  }

  crash_info.crash      = req_crash;
  crash_info.delay      = req_delay;
  crash_info.image_mode = image_mode;
  //check for immediate crash (from caller context)
  if (0==req_delay)
  {
    err_inject_crash_execute((timer_cb_data_type)&crash_info);
  }
  else
  {
    //set cb timer to trigger actual crash
    timer_set_64(&eicTimer, (timetick_type)req_delay, 0, T_SEC);
  }

}


static void err_inject_crash_err_fatal(void)
{
  ERR_FATAL("Crash injected via Diag",0,0,0);
}

static void err_inject_crash_wdog(void)
{
  err_dog_force_bite();
}

static void err_inject_null_access(void)
{
  static int result;

  result = *(int*)err_inject_crash_zero;

  MSG_2(MSG_SSID_TMS, MSG_LEGACY_ERROR,"Should have crashed due to null access: %#x->%#x", err_inject_crash_zero, result);
}

static void err_inject_crash_div0(void)
{
  static float result;

  result = 7/err_inject_crash_zero;

  MSG_2(MSG_SSID_TMS, MSG_LEGACY_ERROR,"Should have crashed due to div0: 7/%u=%d", err_inject_crash_zero, result);
}


void err_inject_uImage_crash_execute( utimer_cb_data_type crash_type) 
{
  if ( qurt_island_get_status() == TRUE )
  {
    switch(crash_type)
    {
    case ERR_INJECT_DIV0: 
      err_inject_crash_div0();
      break;
    case ERR_INJECT_WDOG_TIMEOUT:
      err_inject_crash_wdog();
      break;
    case ERR_INJECT_NULLPTR:
      err_inject_null_access();
      break;
    case ERR_INJECT_ERR_FATAL :
      err_inject_crash_err_fatal();
    default:
      MSG_ERROR("err_inject_crash: unhandled crash ID %#x", crash_type, 0, 0);
    }
  }

  crash_pending = FALSE;
}



void err_inject_crash_execute(timer_cb_data_type data)
{

  err_uImage_crash_info_t * temp_crash_info = 
	                (err_uImage_crash_info_t *)data; 

  //crash  
  if ( temp_crash_info->image_mode == ERR_MAINIMAGE_MODE )
  {
    switch(temp_crash_info->crash)
    {
    case ERR_INJECT_DIV0: 
      err_inject_crash_div0();
      break;
    case ERR_INJECT_WDOG_TIMEOUT:
      err_inject_crash_wdog();
      break;
    case ERR_INJECT_NULLPTR:
      err_inject_null_access();
      break;
    case ERR_INJECT_ERR_FATAL :
      err_inject_crash_err_fatal();
    default:
    MSG_1(MSG_SSID_TMS, MSG_LEGACY_ERROR,"err_inject_crash: unhandled crash ID %#x", temp_crash_info->crash);
    }
  }
  else
  {
    utimer_def_osal(&uImage_timer, UTIMER_FUNC1_CB_TYPE, err_inject_uImage_crash_execute, (utimer_cb_data_type)temp_crash_info->crash);
    utimer_set_64(&uImage_timer, (utimer_timetick_type)ERR_UIMAGE_TIMER_PERIOD_REPEAT, (utimer_timetick_type)ERR_UIMAGE_TIMER_PERIOD_REPEAT, UT_SEC);
  }

  crash_pending = FALSE;
}

static void err_inject_crash_devcfg_check(void)
{
  err_inject_crash_type eic_type;
  uint32 eic_delay = ERR_INJECT_CRASH_DELAY_DEVCFG_MIN;

  DALSYSPropertyVar propValue;
  DALSYS_PROPERTY_HANDLE_DECLARE(pHandle);

  DALSYS_GetDALPropertyHandleStr("tms_eic",pHandle);

  // Check for devcfg crashing enabled
  if (DAL_SUCCESS == DALSYS_GetPropertyValue(pHandle,"eic_crash_enable", 0, &propValue))
  {
    
    if(0 == propValue.Val.dwVal)
    {
      return;
    }
  }
  else
  {
    MSG(MSG_SSID_TMS, MSG_LEGACY_HIGH,"Could not read eic_crash_enable devcfg");
    return;
  }

  // Crashing enabled, read eic_crash_type parameter
  if (DAL_SUCCESS == DALSYS_GetPropertyValue(pHandle,"eic_crash_type", 0, &propValue))
  {
    if (SIZEOF_ERR_INJECT_CRASH_TYPE <= propValue.Val.dwVal)
    {
      MSG(MSG_SSID_TMS, MSG_LEGACY_HIGH,"Bad enum in eic_crash_type dalconfig");
      return;
    }

    eic_type = (err_inject_crash_type)propValue.Val.dwVal;
  }
  else
  {
    MSG(MSG_SSID_TMS, MSG_LEGACY_HIGH,"Could not read eic_crash_type devcfg");
    return;
  }

  // Read eic_crash_delay parameter (initialized to DEFAULT above)
  if (DAL_SUCCESS == DALSYS_GetPropertyValue(pHandle,"eic_crash_delay", 0, &propValue))
  {
    if (ERR_INJECT_CRASH_DELAY_DEVCFG_MIN > propValue.Val.dwVal)        
    {
      MSG_1(MSG_SSID_TMS, MSG_LEGACY_LOW,"Small eic_crash_delay dalconfig, using %d", ERR_INJECT_CRASH_DELAY_DEVCFG_MIN);
      eic_delay = ERR_INJECT_CRASH_DELAY_DEVCFG_MIN;
    }
    else
    {
      eic_delay = propValue.Val.dwVal;
    }
  }
  else
  {
    MSG_1(MSG_SSID_TMS, MSG_LEGACY_HIGH,"Could not read eic_crash_delay devcfg, using %d ", ERR_INJECT_CRASH_DELAY_DEVCFG_MIN);
    eic_delay = ERR_INJECT_CRASH_DELAY_DEVCFG_MIN;
  }
    
  //good to initiate timer
  if ((!crash_pending))  //this should *ALWAYS* be true since devcfg is first in eic_init()
  {
      crash_pending= TRUE;  // prevent diag packets from causing re-entrancy
      err_inject_crash_initiate(eic_type, eic_delay, ERR_MAINIMAGE_MODE);
  }
}


