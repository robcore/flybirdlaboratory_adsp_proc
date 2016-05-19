/*=============================================================================

                UTimer_Qdi_v.h  --  Header File

GENERAL DESCRIPTION
      UTimer QDI Layer Header File

EXTERNAL FUNCTIONS

INITIALIZATION AND SEQUENCING REQUIREMENTS
   None.

      Copyright (c) 2009 - 2014
      by QUALCOMM Technologies Incorporated.  All Rights Reserved.

=============================================================================*/

/*=============================================================================

                        EDIT HISTORY FOR MODULE

 This section contains comments describing changes made to the module.
 Notice that changes are listed in reverse chronological order.


$Header: //components/rel/core.adsp/2.6.1/services/utimers/src/utimer_qdi_v.h#1 $ 
$DateTime: 2014/10/16 12:45:40 $ $Author: pwbldsvc $

when       who     what, where, why
--------   ---     ------------------------------------------------------------
06/20/13   ab      Added header file
=============================================================================*/
#ifndef UTIMER_QDI_V_H
#define UTIMER_QDI_V_H

#include "qurt_qdi.h"
#include "qurt_qdi_driver.h"
#include "qurt.h"
#include "utimer.h"

#define UTIMER_ERR_NONE                       0x0
#define UTIMER_ERR_QDI_CPY_FAIL               0x1
#define UTIMER_ERR_CANCEL_WAIT                0x2

#define UTIMER_DRIVER_NAME                    "/dev/utimers"

#define UTIMER_QDI_DEF_OSAL                   (0+QDI_PRIVATE)
#define UTIMER_QDI_SET_DEFERRABLE             (1+UTIMER_QDI_DEF_OSAL)
#define UTIMER_QDI_SET_64                     (1+UTIMER_QDI_SET_DEFERRABLE)
#define UTIMER_QDI_GET_64                     (1+UTIMER_QDI_SET_64)
#define UTIMER_QDI_CLR_64                     (1+UTIMER_QDI_GET_64)
#define UTIMER_QDI_UNDEF                      (1+UTIMER_QDI_CLR_64)

#define UTIMER_QDI_GET_FIRST_NON_DEFERRABLE_TIMER_EXPIRY  (1+UTIMER_QDI_UNDEF)
#define UTIMER_QDI_DEFER_MATCH_INTERRUPT_64       (1+UTIMER_QDI_GET_FIRST_NON_DEFERRABLE_TIMER_EXPIRY)
#define UTIMER_QDI_UNDEFER_MATCH_INTERRUPT_64     (1+UTIMER_QDI_DEFER_MATCH_INTERRUPT_64)

/* Call back method */
#define UTIMER_QDI_GET_CB_INFO                (1+UTIMER_QDI_UNDEFER_MATCH_INTERRUPT_64)
/* Last Method */
#define UTIMER_QDI_ATS_LAST_METHOD            UTIMER_QDI_GET_CB_INFO


#define UTIMER_CLIENT_PIPE_SIZE     30
#define UTIMER_MAX_CLIENTS          3

typedef struct utimer_qdi_opener_type {
  qurt_qdi_obj_t  qdiobj;
  uint32          process_idx;
  boolean         opener_allocated;
  qurt_pipe_t     pipe;
}utimer_qdi_opener;

typedef struct utimer_cb_info_type {
   utimer_ptr_type timer;
   uint32 seq;
   uint32 cb_type;
   uint32 sig_func_addr;
   uint32 mask_data1;
   uint32 data2; /* For padding */
}utimer_cb_info;


/*==============================================================================

                            DEFER-UNDEFER INTERNAL INLINE MACROS

=============================================================================*/

static inline int utimer_invoke_get_first_non_deferrable_timer_expiry(int handle, utimer_timetick_type *tick)
{
   return qurt_qdi_handle_invoke(handle, UTIMER_QDI_GET_FIRST_NON_DEFERRABLE_TIMER_EXPIRY, tick);
}

static inline int utimer_invoke_defer_match_interrupt_64(int handle, utimer_timetick_type *tick)
{
   return qurt_qdi_handle_invoke(handle, UTIMER_QDI_DEFER_MATCH_INTERRUPT_64, tick);
}

static inline int utimer_invoke_undefer_match_interrupt_64(int handle)
{
   return qurt_qdi_handle_invoke(handle, UTIMER_QDI_UNDEFER_MATCH_INTERRUPT_64);
}


/*==============================================================================

                            TIMER INTERNAL INLINE MACROS

=============================================================================*/
static inline utimer_error_type utimer_invoke_def_osal(
                                   int                              handle, 
                                   utimer_ptr_type                  timer,
                                   utimer_notify_type               cb_type,
                                   utimer_osal_notify_obj_ptr       sigs_func_addr,
                                   utimer_osal_notify_data          sigs_mask_data)
{
   return qurt_qdi_handle_invoke(handle, UTIMER_QDI_DEF_OSAL, timer, cb_type, sigs_func_addr, sigs_mask_data);
}

static inline int utimer_invoke_set_deferrable(int handle, utimer_ptr_type timer, boolean condition)
{
   return qurt_qdi_handle_invoke(handle, UTIMER_QDI_SET_DEFERRABLE, timer, condition);
}

static inline utimer_error_type utimer_invoke_set_64(
                                   int                             handle,
                                   utimer_ptr_type                 timer,
                                   utimer_timetick_type            time,
                                   utimer_timetick_type            reload,
                                   utimer_unit_type                 unit)
{
   return qurt_qdi_handle_invoke(handle, UTIMER_QDI_SET_64, timer, time>>32, time, reload>>32, reload, unit);
}

static inline int utimer_invoke_get_64(
                                   int                             handle,
                                   utimer_ptr_type                 timer,
                                   utimer_unit_type                 unit,
                                   utimer_timetick_type           *tick)
{
   return qurt_qdi_handle_invoke(handle, UTIMER_QDI_GET_64, timer, unit, tick);
}

static inline int utimer_invoke_clr_64(
                                   int                             handle,
                                   utimer_ptr_type                 timer,
                                   utimer_unit_type                 unit,
                                   utimer_timetick_type           *tick)
{
   return qurt_qdi_handle_invoke(handle, UTIMER_QDI_CLR_64, timer, unit, tick);
}

static inline utimer_error_type utimer_invoke_undef(
                                   int                             handle,
                                   utimer_ptr_type                 timer)
{
   return qurt_qdi_handle_invoke(handle, UTIMER_QDI_UNDEF, timer);
}

static inline int utimer_invoke_get_cb_info(int handle, utimer_cb_info *cb_details)
{
   return qurt_qdi_handle_invoke(handle, UTIMER_QDI_GET_CB_INFO, cb_details);
}

#endif /* UTIMER_QDI_V_H */