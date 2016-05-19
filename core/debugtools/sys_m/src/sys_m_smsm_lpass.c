/*===========================================================================

           S Y S _ M . C

DESCRIPTION

Copyright (c) 2011-2014 by Qualcomm Technologies, Incorporated.  All Rights Reserved.

===========================================================================
DESCRIPTION
High level system monitor
===========================================================================

                           EDIT HISTORY FOR FILE

$Header: //components/rel/core.adsp/2.6.1/debugtools/sys_m/src/sys_m_smsm_lpass.c#1 $

when       who     what, where, why
--------   ---     ----------------------------------------------------------


===========================================================================*/

#include "sys_m_smsm.h"
#include "sys_m.h"
#include "rcinit.h"
#include "err.h"
#include "smp2p.h"
#include "DALSys.h"
#include "npa_resource.h"
#include "qurt_timer.h"

void __attribute__((weak)) WDT_trigger_BITE(void) 
{
  MSG_ERROR("No wdog crash handler has been provided",0,0,0);
}

#ifndef SMP2P_WRITE_MAX_RETRY_COUNT
#define SMP2P_WRITE_MAX_RETRY_COUNT 20
#endif

#ifndef SMP2P_WRITE_RETRY_DURATION
#define SMP2P_WRITE_RETRY_DURATION 100
#endif

smp2p_context_type *sys_m_smsm_tx_context = 0;
smp2p_context_type *sys_m_smsm_rx_context = 0;
uint32 sys_m_rx_state = 0;
uint32 sys_m_tx_state = 0;

extern int sys_m_forced_shutdown;
/**
  Sets bit in sys_m point to point array to apps
                        
  @return
  Error codes
  
  @dependencies
  None.
*/
int32 sys_m_smsm_apps_set(uint32 bits)
{
    int32 smp2p_return_val = 0, sys_m_smp2p_return_val = 0;
    int retry_count = 0;
    if (sys_m_smsm_tx_context == 0)
    {
        SYS_M_MSG_HIGH("SMP2P not ready");
        return SYS_M_SMP2P_NOT_READY;
    }

    //write update to array
    sys_m_tx_state |= bits;
    smp2p_return_val = smp2p_write(sys_m_smsm_tx_context, sys_m_tx_state);
    SYS_M_MSG_HIGH_2("SMP2P write state 0x%x return status %d", sys_m_tx_state, smp2p_return_val);

    /*if bit cannot be set, retry every 100 ms at a max of 20 times*/
    while((smp2p_return_val!= SMP2P_STATUS_SUCCESS)
       &&(retry_count < SMP2P_WRITE_MAX_RETRY_COUNT))
    {
       qurt_timer_sleep(SMP2P_WRITE_RETRY_DURATION);
       smp2p_return_val = smp2p_write(sys_m_smsm_tx_context, sys_m_tx_state);
       retry_count++;
    }

    /*if bit cannot be set then do Dog BITE*/
    if(smp2p_return_val!= SMP2P_STATUS_SUCCESS){
        WDT_trigger_BITE();
    }

    switch(smp2p_return_val)
    {
        case SMP2P_STATUS_SUCCESS:
            sys_m_smp2p_return_val = SYS_M_SMP2P_SUCCESS;
            break;
        case SMP2P_STATUS_NOT_INIT:
            sys_m_smp2p_return_val = SYS_M_SMP2P_NOT_READY;
            break;
        case SMP2P_STATUS_INVALID_PARAM:
            sys_m_smp2p_return_val = SYS_M_SMP2P_INVALID_PARAM;
            break;
        default:
            ERR_FATAL("smp2p_write returning invalid code", 0, 0, 0);
            break;
    }
    
    return sys_m_smp2p_return_val;
}
    
/**
  Single threaded mode version of above (no mutex operations) 
  Sets bit in sys_m point to point array to apps 
                        
  @return
  Error codes
  
  @dependencies
  None.
*/
int32 sys_m_smsm_apps_set_stm(uint32 bits)
{
    int32 smp2p_return_val = 0, sys_m_smp2p_return_val = 0;
    
    if (sys_m_smsm_tx_context == 0)
        return SYS_M_SMP2P_NOT_READY;

    //write update to array (not needed, but preserves state for debugging)
    sys_m_tx_state |= bits;
    smp2p_return_val = smp2p_modify_ex(sys_m_smsm_tx_context, 0, bits, SMP2P_FLAGS_STM);
    switch(smp2p_return_val)
    {
        case SMP2P_STATUS_SUCCESS:
            sys_m_smp2p_return_val = SYS_M_SMP2P_SUCCESS;
            break;
        case SMP2P_STATUS_NOT_INIT:
            sys_m_smp2p_return_val = SYS_M_SMP2P_NOT_READY;
            break;
        case SMP2P_STATUS_INVALID_PARAM:
            sys_m_smp2p_return_val = SYS_M_SMP2P_INVALID_PARAM;
            break;
        default:
            ERR_FATAL("smp2p_modify_ex returning invalid code", 0, 0, 0);
            break;
    }
    
    return sys_m_smp2p_return_val;
}

/**
 *
 * @brief sys_m_smsm_init
 *
 * System monitor SMSM initialization function
 *
*/
void sys_m_smsm_init(void)
{

}

/**
 *
 * @brief sys_m_smsm_task
 *
 * System Monitor SMSM handling task
 *
 * @param[in] hEvent: Task init paramter
 * @param[in] tid: task id
 *
*/
DALResult sys_m_smsm_task(DALSYSEventHandle hEvent, void* tid)
{
    int32 return_val;
    uint32 rx_state_received;
    uint32 rx_state_change;
    //block for start signal
    rcinit_handshake_startup();
    //create outbound
    return_val = smp2p_create(&sys_m_smsm_tx_context, SMEM_APPS, SYS_M_SMP2P_PORT_OUT);
    if (return_val != SMP2P_STATUS_SUCCESS && return_val != SMP2P_STATUS_NOT_INIT)
        ERR_FATAL("Sys_m cannot create outbound SMP2P", return_val, 0, 0);
     
    //wait for outbound readiness 
    if (return_val == SMP2P_STATUS_NOT_INIT)
    {
        return_val = smp2p_wait(sys_m_smsm_tx_context);
        if (return_val == SMP2P_STATUS_FAILURE)
            ERR_FATAL("Sys_m cannot wait outbound SMP2P", return_val, 0, 0);
    }
    
    npa_define_marker("/ssr/smp2p/inited");
    
    //register to listen on inbound 
    return_val = smp2p_register(&sys_m_smsm_rx_context, SMEM_APPS, SYS_M_SMP2P_PORT_IN);
    if (return_val != SMP2P_STATUS_SUCCESS && return_val != SMP2P_STATUS_NOT_FOUND)
        ERR_FATAL("Sys_m cannot listen on SMP2P", return_val, 0, 0);
    

    //task forever loop
    for (;;)
    {
        return_val = smp2p_wait(sys_m_smsm_rx_context);
        if (return_val == SMP2P_STATUS_FAILURE)
            ERR_FATAL("Sys_m cannot wait for SMP2P", return_val, 0, 0);
        
        //attempt to read data
        return_val = smp2p_read(sys_m_smsm_rx_context, &rx_state_received);
        SYS_M_MSG_HIGH_2("SMP2P rx state current 0x%x received 0x%x", sys_m_rx_state, rx_state_received);
        //if state has changed, act appropriately
        rx_state_change = rx_state_received ^ sys_m_rx_state;
        //update global state if it has changed
        if (rx_state_change != 0)
            sys_m_rx_state = rx_state_received;
        
        //error fatal
        if (rx_state_change & SYS_M_AP2SUBSYS_SMSM_ERRFATAL)
        {
            SYS_M_MSG_HIGH(" SMP2P force shutdown request");
            sys_m_forced_shutdown = 1;
            ERR_FATAL("APPS force stop", 0, 0, 0);
        }
        //graceful shutdown
        if (rx_state_change & SYS_M_AP2SUBSYS_SMSM_SHUT_DWN)
        {
            SYS_M_MSG_HIGH(" SMP2P graceful shutdown request");
            sys_m_shutdown(SYS_M_SMSM_P2P);
        }
        
        
    }
    
}


