/*====*====*====*====*====*====*====*====*====*====*====*====*====*====*====*

                         Diagnostic Fwd Task

General Description
This routines in this file pertain to the task called diag_fwd_task
that on the master processor process traffic from slave processors.
This is a more robust design and will help diag_task be more efficient.

Copyright (c) 2010, 2014 by QUALCOMM Technologies, Incorporated.
All Rights Reserved.
Qualcomm Confidential and Proprietary

*====*====*====*====*====*====*====*====*====*====*====*====*====*====*====*/

/*===========================================================================

                              Edit History

 $Header: //components/rel/core.adsp/2.6.1/services/diag/DCM/common/src/diag_fwd.c#1 $

when       who     what, where, why
--------   ---     ----------------------------------------------------------
01/28/14   ph      Added start signal to be used for handshake with osal
                   in the new task created using osal_create_thread().
09/14/10   is      New control channel and central routing features
06/16/10   VG      Added DIAG_FWD_RPT_TIMER_SIG to osal_wait
05/26/10   JV      Featurized dog functionality for WM and aDSP
04/06/10   JV      Created
===========================================================================*/

#include "diag_fwd_v.h"
#include "diagi_v.h"
#include "diagcomm_v.h"
#include "diagcomm_smd.h"
#include "diag_v.h"

#if defined (DIAG_QDSP6_APPS_PROC)
#include "diagstub.h"
#else
#include "dog.h"
#include "assert.h"
#endif /* (!DIAG_QDSP6_APPS_PROC) */


extern osal_tcb_t diag_fwd_task_tcb;

#if defined (DIAG_DOG_SUPPORT)

dog_report_type diag_fwd_dog_rpt_var = 0;
uint32 diag_fwd_dog_rpt_time_var = 0xffff;

osal_timer_t diag_fwd_rpt_timer;
#endif

void diag_fwd_task_start(uint32 params)
{
  int ret_val;

  ret_val=osal_handshake_start(&diag_fwd_task_tcb);
  ASSERT(OSAL_SUCCESS == ret_val);

#if defined (DIAG_DOG_SUPPORT)
    int return_val = 0;

    diag_fwd_dog_rpt_var = dog_register(&diag_fwd_task_tcb, DOG_DEFAULT_TIMEOUT, DOG_DEADLKCHK_ENABLE);

    diag_fwd_dog_rpt_time_var = dog_get_report_period(diag_fwd_dog_rpt_var);


    /* If the return value from dog_get_report_period() was zero, then we MUST
    NOT report to dog directly, as DOG will monitor us in a different manner.
    Hence we won't initialize or start any timer. */
    if (diag_fwd_dog_rpt_time_var > 0)
    {
        /*  Initialize watchdog report timer  */
        return_val = osal_create_timer(&diag_fwd_rpt_timer, &diag_fwd_task_tcb, DIAG_FWD_RPT_TIMER_SIG);
        ASSERT(OSAL_SUCCESS == return_val);
    }
#endif
/* Start the dog timer */
    diag_fwd_kick_watchdog ();
    diag_fwd_handle_sigs();

}

void diag_fwd_kick_watchdog(void)
{
#if defined (DIAG_DOG_SUPPORT)
    int return_val = 0;
    dog_report(diag_fwd_dog_rpt_var);
    return_val = osal_set_timer(&diag_fwd_rpt_timer, diag_fwd_dog_rpt_time_var);
    ASSERT(OSAL_SUCCESS == return_val);
#endif
}

void diag_fwd_handle_sigs()
{
    osal_sigs_t sigs = 0;
    osal_sigs_t return_sigs = 0;

    while (1)
    {
        sigs = osal_thread_wait (&diag_fwd_task_tcb, (DIAG_TX_SLAVE_SIG | DIAG_FWD_RPT_TIMER_SIG));

        /* Pet the dog before doing any work. */
        diag_fwd_kick_watchdog ();

        if (sigs & DIAG_TX_SLAVE_SIG)
        {
            (void) osal_reset_sigs (&diag_fwd_task_tcb, DIAG_TX_SLAVE_SIG, &return_sigs);

            if(diagcomm_smd_get_rx_wmq_cnt(DIAGCOMM_PORT_1))
               diagcomm_smd_process_slave_tx (DIAGCOMM_PORT_1);

            if(diagcomm_smd_get_rx_wmq_cnt(DIAGCOMM_PORT_2))
               diagcomm_smd_process_slave_tx(DIAGCOMM_PORT_2);

        }
        if( diagcomm_status() &&
           (diagcomm_smd_get_rx_wmq_cnt(DIAGCOMM_PORT_1) || diagcomm_smd_get_rx_wmq_cnt(DIAGCOMM_PORT_2))
          )
        {
            osal_set_sigs(&diag_fwd_task_tcb, DIAG_TX_SLAVE_SIG, &return_sigs);
        }
    }
}
