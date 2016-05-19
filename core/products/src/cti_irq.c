/*==============================================================================
  FILE:         sleep_target.c

  OVERVIEW:     This file provides target-specific functionality for the 8960
                Modem Subsystem.

  DEPENDENCIES: None

                Copyright (c) 2011-2013 QUALCOMM Technologies Incorporated.
                All Rights Reserved.
                Qualcomm Confidential and Proprietary
================================================================================
$Header: //components/rel/core.adsp/2.6.1/products/src/cti_irq.c#1 $
$DateTime: 2014/10/16 12:45:40 $
==============================================================================*/
#include <stdint.h>
#include "cti.h"
#include "timer.h"
#include "CoreVerify.h"
#include "com_dtypes.h"
#include "DDIInterruptController.h"
#include "DALDeviceId.h"
#include "DALStdErr.h"
#include "DALSys.h"
#include "err.h"
#include "CoreVerify.h"
#include "msg.h"
/* ==================================================================
                     GLOBAL DATA DECLARATIONS
   ================================================================== */
#define CTI_BUSYWAIT_DELAY 20000000 //about 20 seconds
#define CTI_INTERRUPT_PORT 31
#define CTI_WORKLOOP_PRIORITY   (3)
#define CTI_WORKLOOP_MAX_EVENTS (10)
#define CTI_WORKLOOP_STACK_SIZE 0x00001000

/* ==================================================================
                     CTI Config Parameters
   ================================================================== */

static cti_target_config cti_cfg;

static void CTI_Wakeup_Handler(uint32 param);

/* ==================================================================
                     FUNCTIONS
   ================================================================== */
static DalDeviceHandle *hDALIntCtl;


static void CTI_Wakeup_Handler(uint32 param)
{
    //populate cti struct with IMEM contents
    if (DAL_SUCCESS != cti_read_imem() )
        ERR_FATAL("CTI interrupt handler - could not read from Shared-IMEM!", 0, 0, 0);
    

    if (PROCESSOR_SELECT_MASK & cti_cfg.processor_select)
    {
        switch(cti_cfg.cookie_action){
            case COOKIE_BUSYWAIT:
                if (DAL_SUCCESS != DALSYS_EventCtrl(cti_cfg.event, DALSYS_EVENT_CTRL_TRIGGER))
                    ERR_FATAL("Couldn't Trigger CTI Workloop EVENT", 0, 0, 0);
                break;
            case COOKIE_BKRPT:
                MSG_3(MSG_SSID_DIAG, MSG_LEGACY_HIGH, "CTI - Cookie BKRPT.", 0, 0, 0);
                __asm__ __volatile__ ("brkpt \n");
                break;
            case COOKIE_CRASH:
                MSG_3(MSG_SSID_DIAG, MSG_LEGACY_HIGH, "CTI - Cookie Crash.", 0, 0, 0);
                ERR_FATAL("CTI - Triggered Crash", 0, 0, 0);
                break;
            case COOKIE_TRACE:
                MSG_3(MSG_SSID_DIAG, MSG_LEGACY_HIGH, "CTI - Cookie Trace.", 0, 0, 0);
                break;
            case COOKIE_ETM_COMPARATOR:
                MSG_3(MSG_SSID_DIAG, MSG_LEGACY_HIGH, "CTI - Cookie ETM Comparator.", 0, 0, 0);
                // ETM COMPARE THING
                break;
            case COOKIE_DISABLE_SLEEP:
                MSG_3(MSG_SSID_DIAG, MSG_LEGACY_HIGH, "CTI - Cookie Disable Sleep.", 0, 0, 0);
                // Sleep Enable+Disable DONT FORGET.
                break;
            case COOKIE_READ_REG:
                cti_read_registers();
                MSG_3(MSG_SSID_DIAG, MSG_LEGACY_HIGH, "CTI - Read Registers. R1= 0x%x, R2= 0x%x, R3= 0x%x", cti_cfg.reg1, cti_cfg.reg2, cti_cfg.reg3);
                // Sleep Enable+Disable DONT FORGET.
                break;
            default:
                MSG_3(MSG_SSID_DIAG, MSG_LEGACY_HIGH, "CTI - Invalid Cookie", 0, 0, 0);
                break;
            }
    }
    return;
}

DALResult cti_workloop(DALSYSEventHandle hEvent, void *pCtx)
{
    DALSYS_EventCtrl(cti_cfg.event, DALSYS_EVENT_CTRL_RESET);

    while ( 1 )
    {
        DALSYS_EventWait(cti_cfg.event);
        DALSYS_EventCtrl(cti_cfg.event, DALSYS_EVENT_CTRL_RESET);

	    if (DAL_SUCCESS != cti_read_imem() )
    	    ERR_FATAL("CTI interrupt handler - could not read from Shared-IMEM!", 0, 0, 0);
        MSG_3(MSG_SSID_DIAG, MSG_LEGACY_HIGH, "CTI - Cookie BusyWait.", 0, 0, 0);
        DALSYS_BusyWait(CTI_BUSYWAIT_DELAY);
        
    }
}

void cti_irq_init(void)
{
    uint32                 CTI_Interrupt_Number;

    CTI_Interrupt_Number = CTI_INTERRUPT_PORT;
    
    /* Attaching to interrupt controller and registering interrupt handlers */
    CORE_VERIFY( DAL_DeviceAttach( DALDEVICEID_INTERRUPTCONTROLLER,
                                 &hDALIntCtl ) == DAL_SUCCESS );

    CORE_VERIFY( DalInterruptController_RegisterISR( 
                hDALIntCtl,
                (uint32)CTI_Interrupt_Number,
                (DALIRQ)CTI_Wakeup_Handler,
                (const DALIRQCtx) 0,
                (DALINTRCTRL_ENABLE_RISING_EDGE_TRIGGER)
              ) == DAL_SUCCESS );
              
    cti_init_workloop();
}

void cti_init_workloop(void)
{
    DALSYS_InitMod(NULL);

    if (DAL_SUCCESS != DALSYS_EventCreate(DALSYS_EVENT_ATTR_CLIENT_DEFAULT,
                                          &(cti_cfg.event),
                                          NULL))
        ERR_FATAL("Couldn't Create CTI workloop EVENT", 0, 0, 0);

    if (DAL_SUCCESS != DALSYS_EventCreate(DALSYS_EVENT_ATTR_WORKLOOP_EVENT,
                                          &(cti_cfg.start_event),
                                          NULL))
        ERR_FATAL("Couldn't Create CTI workloop Start EVENT", 0, 0, 0);

    if (DAL_SUCCESS != DALSYS_RegisterWorkLoopEx("cti_workloop",
                                                 CTI_WORKLOOP_STACK_SIZE,
                                                 CTI_WORKLOOP_PRIORITY,
                                                 CTI_WORKLOOP_MAX_EVENTS,
                                                 &(cti_cfg.handle), NULL))
        ERR_FATAL("Couldn't Register CTI workloop", 0, 0, 0);

    if (DAL_SUCCESS != DALSYS_AddEventToWorkLoop(cti_cfg.handle,
                                                 cti_workloop,
                                                 NULL,
                                                 cti_cfg.start_event,
                                                 NULL))
        ERR_FATAL("Couldn't Add CTI workloop Start EVENT", 0, 0, 0);

    if (DAL_SUCCESS != DALSYS_EventCtrl(cti_cfg.start_event,
                                        DALSYS_EVENT_CTRL_TRIGGER))
        ERR_FATAL("Couldn't Trigger CTI workloop Start EVENT", 0, 0, 0);

    //*hEvent = cti_cfg.event;
}

volatile unsigned int cti_read_imem(void)
{
    volatile unsigned int* debug_cookie = (volatile unsigned int*)(COOKIE_LOCATION);
    
    cti_cfg.cookie = *debug_cookie;
    cti_cfg.processor_select= (cti_cfg.cookie & 0xF0000000)>>28;
    cti_cfg.cookie_action = cti_cfg.cookie & 0x0FFFFFFF;
   
   
   //return (*debug_cookie);
   return DAL_SUCCESS;
}

void cti_read_registers(void)
{
    
   cti_cfg.reg1 =(*  ((volatile unsigned int*)(*((volatile unsigned int*)(CTI_IMEM_1))))  );
   cti_cfg.reg2 =(*  ((volatile unsigned int*)(*((volatile unsigned int*)(CTI_IMEM_2))))  );
   cti_cfg.reg3 =(*  ((volatile unsigned int*)(*((volatile unsigned int*)(CTI_IMEM_3))))  );
   
   
   /*
   cti_cfg.reg1 = in_dword((*CTI_REG_1));
   cti_cfg.reg2 = in_dword((*CTI_REG_2));
   cti_cfg.reg3 = in_dword((*CTI_REG_3));
   cti_cfg.reg3 = in_dword((*CTI_REG_3));
   */
   return;
}
