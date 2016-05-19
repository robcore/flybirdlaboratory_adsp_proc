/**
@file sys_m.c
@brief This file contains the implementation details for ...
*/
/*=============================================================================
NOTE: The @brief description above does not appear in the PDF.
The tms_mainpage.dox file contains the group/module descriptions that
are displayed in the output PDF generated using Doxygen and LaTeX. To
edit or update any of the group/module text in the PDF, edit the
tms_mainpage.dox file or contact Tech Pubs.
===============================================================================*/
/*=============================================================================
Copyright (c) 2013 -2014 Qualcomm Technologies Incorporated.
All rights reserved.
Qualcomm Confidential and Proprietary.
===============================================================================*/
/*=============================================================================
Edit History
$Header: //components/rel/core.adsp/2.6.1/debugtools/sys_m/src/sys_m_lpass.c#1 $
$DateTime: 2014/10/16 12:45:40 $
$Author: pwbldsvc $
===============================================================================*/

#include "err.h"
#include "rcecb.h"
#include "rcevt_internal.h"
#include "rcevt_dal.h"
#include "sys_m.h"
#include "sys_m_messages.h"
#include "smd_lite.h"
#include "rcinit.h"
#include "stringl/stringl.h"
#include "DALSys.h"
#include "smsm.h"
#include "smem.h"
#include "dog_messages.h"
#include "sys_m_smsm.h"
#include "qurt.h"
#ifdef SYS_M_ISLAND_MODE
#include "uSleep.h"
#endif /* SYS_M_ISLAND_MODE */



extern void err_halt_execution(void);

#define USYS_M_CODE_SECTION __attribute__((section (".text.uSysm")))

#define SYS_M_BUFFER_LEN 50

char sys_m_buffer[SYS_M_BUFFER_LEN];

smdl_handle_type sys_m_port_LPASS_AP = NULL;
int sys_m_notification_id = -1;
int sys_m_read_return = -1;
int sys_m_write_return = -1;

int sys_m_forced_shutdown = 0;

DALSYSEventHandle sys_m_ap_notify_rcv_evt;
DALSYSEventHandle sys_m_tasks_complete_evt;
RCEVT_SIGEX_SIGDAL sys_m_dog_hw_init_evt;



char *accepted_messages[] = {
    SYS_M_SSR_MODEM_BEFORE_SHUTDOWN,
    SYS_M_SSR_WCNSS_BEFORE_SHUTDOWN,
    SYS_M_SSR_DSPS_BEFORE_SHUTDOWN,
    SYS_M_SSR_GSS_BEFORE_SHUTDOWN,
    SYS_M_SSR_EXT_MODEM_BEFORE_SHUTDOWN,


    SYS_M_SSR_MODEM_AFTER_POWERUP,
    SYS_M_SSR_WCNSS_AFTER_POWERUP,
    SYS_M_SSR_DSPS_AFTER_POWERUP,
    SYS_M_SSR_GSS_AFTER_POWERUP,
    SYS_M_SSR_EXT_MODEM_AFTER_POWERUP,

    SYS_M_SSR_MODEM_BEFORE_POWERUP,
    SYS_M_SSR_WCNSS_BEFORE_POWERUP,
    SYS_M_SSR_DSPS_BEFORE_POWERUP,
    SYS_M_SSR_GSS_BEFORE_POWERUP,
    SYS_M_SSR_EXT_MODEM_BEFORE_POWERUP,


    SYS_M_SSR_MODEM_AFTER_SHUTDOWN,
    SYS_M_SSR_WCNSS_AFTER_SHUTDOWN,
    SYS_M_SSR_DSPS_AFTER_SHUTDOWN,
    SYS_M_SSR_GSS_AFTER_SHUTDOWN,
    SYS_M_SSR_EXT_MODEM_AFTER_SHUTDOWN
};
#define SYS_M_NUM_NOTIFICATION sizeof(accepted_messages)/sizeof(char*)

char *sys_m_msg_types[] = {
    "ssr",
    "info"
};
#define SYS_M_NUM_MSGTYPES sizeof(sys_m_msg_types)/sizeof(char*)

void sys_m_signal_modules(void);
void sys_m_unknown_msgs(void);
void sys_m_register_fatal_notification(void);
void sys_m_qurt_fatal_notification(void* no_param) USYS_M_CODE_SECTION;

/**
 * @brief q6_smd_cb
 *
 * System monitor SMD callback function.   Internal to System Monitor
 *
 * @param[in] port: SMD port
 * @param[in] event: SMD event
 * @param[in] data: CB data
 *
*/
void q6_smd_cb(smdl_handle_type port, smdl_event_type event, void *data)
{
    if (event == SMDL_EVENT_READ)
    {
        if (DAL_SUCCESS != DALSYS_EventCtrl(sys_m_ap_notify_rcv_evt, DALSYS_EVENT_CTRL_TRIGGER))
            ERR_FATAL("DAL EventCtrl error in sys_m", 0, 0, 0);
    }
    return;
}

/**
 *
 * @brief sys_m_apps_errfatal_cb
 *
 * Callback for a forced error fatal from apps
 *
 * @param[in] entry: SMSM type
 * @param[in] prev_state: SMSM's previous state
 * @param[in] curr_state: SMSM's current state
 * @param[in] *cb_data: callback data
*/
void sys_m_apps_errfatal_cb(smsm_entry_type entry, uint32 prev_state, uint32 curr_state, void * cb_data)
{
    ERR_FATAL("APPS error fatal", 0, 0, 0);
}

/**
 *
 * @brief sys_m_init
 *
 * System monitor initialization function
 *
*/
void sys_m_init(void)
{
    sys_m_port_LPASS_AP = smdl_open(sys_m_smd_port, SMD_APPS_QDSP, 0, SMD_MIN_FIFO, q6_smd_cb, NULL);
    smsm_cb_register( SMSM_APPS_STATE, SMSM_RESET, sys_m_apps_errfatal_cb, NULL);

}

/**
 *
 * @brief sys_m_task
 *
 * System Monitor main task
 *
 * @param[in] hEvent: Task init paramter
 * @param[in] tid: task id
 *
*/
DALResult sys_m_task(DALSYSEventHandle hEvent, void* tid)
{
    int i = 0;
    uint32 index;
    SYS_M_SPECIAL_MSG_TYPE sys_m_msg_type;
    DALResult res;
    //DAL event array
    DALSYSEventHandle hEvents[3];

    //register kernel fatal notification handler
    sys_m_register_fatal_notification();

    res = DALSYS_EventCreate(DALSYS_EVENT_ATTR_NORMAL, &sys_m_ap_notify_rcv_evt, NULL);
    if (res != DAL_SUCCESS)
        ERR_FATAL("DAL EventCreate error in sys_m", 0, 0, 0);

    res = DALSYS_EventCreate(DALSYS_EVENT_ATTR_NORMAL, &sys_m_tasks_complete_evt, NULL);
    if (res != DAL_SUCCESS)
        ERR_FATAL("DAL EventCreate error in sys_m", 0, 0, 0);

    //register dog hw initialization event with RCEVT
    res = DALSYS_EventCreate(DALSYS_EVENT_ATTR_NORMAL, &(sys_m_dog_hw_init_evt.signal), NULL);
    if (res != DAL_SUCCESS)
        ERR_FATAL("DAL EventCreate error in sys_m", 0, 0, 0);
    if (rcevt_register_sigex_name(DOG_HW_INIT_COMPLETE, RCEVT_SIGEX_TYPE_SIGDAL, &sys_m_dog_hw_init_evt) == RCEVT_NULL)
        ERR_FATAL("RCEVT register error in sys_m", 0, 0, 0);


    //rcevt_register_name("rcinit:initgroups", SYS_M_TASKS_COMPLETE);
    //block for start signal
    rcinit_handshake_startup();

    //place dal events into array

    //formerly SYS_M_AP_NOTIFY_RCV
    hEvents[0] = sys_m_ap_notify_rcv_evt;

    //formerly SYS_M_TASKS_COMPLETE
    hEvents[1] = sys_m_tasks_complete_evt;

    //event for HW wdog initialization
    hEvents[2] = sys_m_dog_hw_init_evt.signal;

    //task forever loop
    for (;;)
    {
        res = DALSYS_EventMultipleWait(hEvents, sizeof(hEvents)/sizeof(DALSYSEventHandle), DALSYS_EVENT_TIMEOUT_INFINITE, &index);
        if (res != DAL_SUCCESS)
            ERR_FATAL("DAL EventMultipleWait error in sys_m", 0, 0, 0);
        switch(index)
        {
            //AP notify event received (formerly SYS_M_AP_NOTIFY_RCV)
            case 0:
                res = DALSYS_EventCtrl(sys_m_ap_notify_rcv_evt, DALSYS_EVENT_CTRL_RESET);
                if (res != DAL_SUCCESS)
                    ERR_FATAL("DAL EventCtrl error in sys_m", 0, 0, 0);
                //clear buffer before reading
                secure_memset(sys_m_buffer, 0, sizeof(sys_m_buffer));
                sys_m_read_return = smdl_read(sys_m_port_LPASS_AP, SYS_M_BUFFER_LEN, sys_m_buffer, 0);
                if (sys_m_read_return < 0)
                    ERR_FATAL("Sys_m smdl_read failed", 0, 0, 0);

                //data available to read.  ignore 0 length packets
                else if (sys_m_read_return > 0)
                {
                    sys_m_msg_type = SYS_M_UNKNOWN_MSG;
                    MSG_SPRINTF_1(MSG_SSID_TMS, MSG_LEGACY_HIGH, "ADSP:smdl buf read: %s", sys_m_buffer);
                    //look for nonspecial messages
                    for (i = 0; i < SYS_M_NUM_NOTIFICATION; i++)
                    {
                        if (strncmp(sys_m_buffer, accepted_messages[i], SYS_M_BUFFER_LEN) == 0)
                        {
                            sys_m_notification_id = i;
                            sys_m_msg_type = SYS_M_NONSPECIAL_MSG;
                            break;
                        }
                    }
                    //look for special messages
                    if (strncmp(sys_m_buffer, SYS_M_SHUTDOWN, SYS_M_BUFFER_LEN) == 0)
                        sys_m_msg_type = SYS_M_SHUTDOWN_MSG;
                    switch(sys_m_msg_type)
                    {
                        case SYS_M_NONSPECIAL_MSG:
                            SYS_M_MSG_HIGH("smdl msg notify modules");
                            sys_m_signal_modules();
                            break;
                        case SYS_M_SHUTDOWN_MSG:
                            SYS_M_MSG_HIGH("smdl msg initiate shutdown");
                            sys_m_shutdown(SYS_M_SMD);
                            break;
                        case SYS_M_UNKNOWN_MSG:
                            SYS_M_MSG_HIGH("smdl msg unknown message");
                            sys_m_unknown_msgs();
                            break;

                    }
                }
                //end case 0
                break;

            //tasks complete event received (formerly SYS_M_TASKS_COMPLETE)
            case 1:
                 SYS_M_MSG_HIGH("tasks complete");
                res = DALSYS_EventCtrl(sys_m_tasks_complete_evt, DALSYS_EVENT_CTRL_RESET);
                if (res != DAL_SUCCESS)
                    ERR_FATAL("DAL EventCtrl error in sys_m", 0, 0, 0);
                break;

            //dog hardware initialized
            case 2:
                SYS_M_MSG_HIGH("dog ready");
                res = DALSYS_EventCtrl(sys_m_dog_hw_init_evt.signal, DALSYS_EVENT_CTRL_RESET);
                if (res != DAL_SUCCESS)
                    ERR_FATAL("DAL EventCtrl error in sys_m", 0, 0, 0);
                smsm_state_set(SMSM_Q6_STATE, SMSM_SUBSYS2AP_STATUS);
                sys_m_smsm_apps_set(SYS_M_SUBSYS2AP_SMSM_ERR_HDL_RDY);
                if (rcevt_unregister_sigex_name(DOG_HW_INIT_COMPLETE, RCEVT_SIGEX_TYPE_SIGDAL, &sys_m_dog_hw_init_evt) == RCEVT_NULL)
                    ERR_FATAL("RCEVT unregister erorr in sys_m", 0, 0, 0);
        }

    }

    //should never get here
    return DAL_SUCCESS;
}

/**
 *
 * @brief sys_m_unknown_msgs
 *
 * Handle messages that could not be understood.  Internal to system monitor
 *
*/
void sys_m_unknown_msgs(void)
{
    char *savePtr, *retStr;
    int i = 0;
    //version
    if (strstr(sys_m_buffer, SYS_M_VER) != NULL)
    {
        sys_m_write_return = smdl_write(sys_m_port_LPASS_AP, SYS_M_BUFFER_LEN, SYS_M_VER_STR, SMDL_WRITE_FLAGS_NONE);
        return;
    }
    //unknown msg
    retStr = strtok_r(sys_m_buffer, ":", &savePtr);
    if (retStr != NULL)
    {
        for (i = 0; i < SYS_M_NUM_MSGTYPES; i++)
        {
            if (strncmp(retStr, sys_m_msg_types[i], SYS_M_BUFFER_LEN) == 0)
            {
                strlcat(retStr, ":unknown", SYS_M_BUFFER_LEN);
                sys_m_write_return = smdl_write(sys_m_port_LPASS_AP, SYS_M_BUFFER_LEN, retStr, SMDL_WRITE_FLAGS_NONE);
                return;
            }
        }
    }
    sys_m_write_return = smdl_write(sys_m_port_LPASS_AP, SYS_M_BUFFER_LEN, "err:unknown", SMDL_WRITE_FLAGS_NONE);
    return;
}

/**
 *
 * @brief sys_m_signal_modules
 *
 * Signal interested modules of a system monitor event.  After all clients have completed
 * notification, acknowledge to apps
 *
*/
void sys_m_signal_modules(void)
{
    int orig_ack_count = 0;
    int req_count = 0;

    //callbacks
    rcecb_signal_name(accepted_messages[sys_m_notification_id]);

    //get count of current clients
    req_count = rcevt_getcontexts_name(accepted_messages[sys_m_notification_id]);
    orig_ack_count = rcevt_getcount_name(SYS_M_ACK);
    //signal
    rcevt_signal_name(accepted_messages[sys_m_notification_id]);
    //wait for all clients to ack
    rcevt_wait_count_name(SYS_M_ACK, req_count + orig_ack_count);
    //tell AP that notification is serviced
    sys_m_notification_id = -1;
    sys_m_write_return = smdl_write(sys_m_port_LPASS_AP, SYS_M_BUFFER_LEN, SYS_M_ACK, SMDL_WRITE_FLAGS_NONE);
    SYS_M_MSG_HIGH("smdl msg notify modules exit");
}


void sys_m_reset(void)
{

}


/*
 *
 * @brief sys_m_begin_shutdown
 *
 * Begin shutdown process
 *
*/
void sys_m_shutdown(SYS_M_COMMUNICATION_TYPE sys_m_comm)
{
    
   // commanded shutdown begins, this is a time sensitive operation, with
   // the time of the operation not under control of the peripheral shutting down.
   // all operations must be expedient and complete in the minimum amount of time
   // possible. technology areas must not prolong their "cleanup," the shutdown
   // process must be considered a software exception, and the technology areas
   // do not get infinite time to handle their part of the software exception.

   SYS_M_MSG_HIGH_1("sys_m_shutdown process begins, expect degraded runtime operation sys_m_comm = %d", sys_m_comm);
    //shutdown
    sys_m_shutdown_internal();

    //acknowledge
    switch(sys_m_comm)
    {
        case SYS_M_SMSM_P2P:
            break;
        case SYS_M_SMD:
             smdl_write(sys_m_port_LPASS_AP, SYS_M_BUFFER_LEN, SYS_M_SHUTDOWN_ACK, SMDL_WRITE_FLAGS_NONE);
            break;
        default:
            break;
    }

    //always set SMP2P bit after completion
    sys_m_smsm_apps_set(SYS_M_SUBSYS2AP_SMSM_SHUT_DWN_ACK);
    
   // at this point, the peripheral is operating in a degraded state. technology
   // areas cannot make any assumptions about the availability of any specific
   // services. all technology areas at this point should have parked their services
   // into a logical non-processing state.

   SYS_M_MSG_HIGH("sys_m_shutdown process ends, expect degraded runtime operation");
}


/**
 *
 * @brief sys_m_shutdown_internal
 *
 * Signal interested modules to prepare for shutdown.  After all clients have completed
 * notification, acknowledge to apps
 *
*/
void sys_m_shutdown_internal(void)
{
    int req_count = 0;
    int orig_ack_count = 0;

    //callbacks
    rcecb_signal_name(SYS_M_SHUTDOWN);

    req_count = rcevt_getcontexts_name(SYS_M_SHUTDOWN);
    orig_ack_count = rcevt_getcount_name(SYS_M_SHUTDOWN_ACK);
    rcevt_signal_name(SYS_M_SHUTDOWN);
    rcevt_wait_count_name(SYS_M_SHUTDOWN_ACK, req_count + orig_ack_count);
}

/**
 *
 * @brief sys_m_err_cb_preflush
 *
 * Issue callbacks before cache has been flushed in an ERR_FATAL
 *
*/
void sys_m_err_cb_preflush(void)
{
    rcecb_signal_name_nolocks(SYS_M_ERR_CB_PREFLUSH);
}

/**
 *
 * @brief sys_m_err_cb_postflush
 *
 * Issue callbacks after cache has been flushed in an ERR_FATAL
 *
*/
void sys_m_err_cb_postflush(void)
{
    rcecb_signal_name_nolocks(SYS_M_ERR_CB_POSTFLUSH);
}


/**
 *
 * @brief sys_m_initiate_shutdown
 *
 * Request apps for a reset of the device
 *
 *
*/
void sys_m_initiate_shutdown(void)
{
    SYS_M_MSG_HIGH_1("sys_m_initiate_shutdown forward request thread_id %x", qurt_thread_get_id());
    smsm_state_set(SMSM_Q6_STATE, SMSM_SYSTEM_REBOOT);
}

/**
 *
 * @brief sys_m_initiate_poweroff
 *
 * Request apps for a poweroff of the device
 *
 *
 *
*/
void sys_m_initiate_poweroff(void)
{
    SYS_M_MSG_HIGH_1("sys_m_initiate_poweroff request thread_id %x", qurt_thread_get_id());
    smsm_state_set(SMSM_Q6_STATE, SMSM_SYSTEM_DOWNLOAD);
}

/**
 *
 * @brief sys_m_init_sfr_buffer
 *
 * Initialize the SFR buffer.  Only error services should call
 * this function
 *
 *  @return
 *  NULL if smem_boot_init has not been called yet
 *  Otherwise, returns either a valid SMEM address to the requested buffer or a
 *  fatal error
 *
*/
void *sys_m_init_sfr_buffer(void)
{
    return smem_alloc (SMEM_SSR_REASON_LPASS0, ERR_SSR_REASON_SIZE_BYTES);
}

static uint32 wait_counter = 10;

/**
 *
 * @brief sys_m_qurt_fatal_notification
 *
 * Special function run in a unique context by qurt post error
 * handling to notify apps of failure
 *
*/
void sys_m_qurt_fatal_notification(void* no_param)
{
    // prevent warnings
    no_param = NULL;

    #ifdef SYS_M_ISLAND_MODE
    if ( qurt_island_get_status() == TRUE )
    {
      uSleep_exitOnError();
      qurt_exception_shutdown_fatal();
    }
    #endif /* SYS_M_ISLAND_MODE */

    smsm_set_reset(0);
    if (!sys_m_forced_shutdown)
   {
      SYS_M_MSG_HIGH("fatal notifier cb, ERR FATAL");
      sys_m_smsm_apps_set_stm(SYS_M_SUBSYS2AP_SMSM_ERRFATAL);
   }
    else
   {
      SYS_M_MSG_HIGH("fatal notifier cb, forced shutdown");
      sys_m_smsm_apps_set_stm(SYS_M_SUBSYS2AP_SMSM_SHUT_DWN_ACK);
   }

    // Per requirement, delay 2 seconds before letting wdog expire
    while (--wait_counter > 0)
    {
      //dog_force_kick();
      DALSYS_BusyWait(200000); //wait 200ms
    }

    while (1)
    {
      DALSYS_BusyWait(200000); //wait 200ms
    }
}

/**
 *
 * @brief sys_m_register_fatal_notification
 *
 * Registers fatal notification handler with the kernel
 *
*/
void sys_m_register_fatal_notification(void)
{
    // as long as we do not get an error, we are done
    if ( QURT_EVAL == qurt_exception_register_fatal_notification(sys_m_qurt_fatal_notification, NULL) )
    {
        ERR_FATAL("Could not register qurt fatal notification handler",0,0,0);
    }
}


