#ifndef SYS_M_H
#define SYS_M_H
/*===========================================================================

           S Y S _ M . H

DESCRIPTION

Copyright (c) 2011-2014 by Qualcomm Technologies, Incorporated.  All Rights Reserved.

===========================================================================
DESCRIPTION
High level system monitor
===========================================================================

                           EDIT HISTORY FOR FILE

$Header: //components/rel/core.adsp/2.6.1/debugtools/sys_m/src/sys_m.h#1 $

when       who     what, where, why
--------   ---     ----------------------------------------------------------


===========================================================================*/
#include "msg.h"

#define SYS_M_PREFIX " ADSP: "

#if defined(MSG_SSID_TMS)
#define SYS_M_MSG_HIGH(fmt)  \
   MSG(MSG_SSID_TMS, MSG_LEGACY_HIGH, SYS_M_PREFIX fmt)
#define SYS_M_MSG_HIGH_1(fmt, a)  \
   MSG_1(MSG_SSID_TMS, MSG_LEGACY_HIGH, SYS_M_PREFIX fmt, a)
#define SYS_M_MSG_HIGH_2(fmt, a, b)  \
   MSG_2(MSG_SSID_TMS, MSG_LEGACY_HIGH, SYS_M_PREFIX fmt, a, b)
#define SYS_M_MSG_HIGH_3(fmt, a, b, c)  \
      MSG_3(MSG_SSID_TMS, MSG_LEGACY_HIGH, SYS_M_PREFIX fmt, a, b, c)
#define SYS_M_MSG_MED(fmt, a, b, c)  \
   MSG_SPRINTF_3(MSG_SSID_TMS, MSG_LEGACY_MED, SYS_M_PREFIX fmt, a, b, c)
#define SYS_M_MSG_LOW(fmt, a, b, c)  \
   MSG_SPRINTF_3(MSG_SSID_TMS, MSG_LEGACY_LOW, SYS_M_PREFIX fmt, a, b, c)
#else
#define SYS_M_MSG_HIGH(fmt, a, b, c)  \
   MSG_SPRINTF_3(MSG_SSID_DFLT, MSG_LEGACY_HIGH, SYS_M_PREFIX fmt, a, b, c)
#define SYS_M_MSG_MED(fmt, a, b, c)  \
   MSG_SPRINTF_3(MSG_SSID_DFLT, MSG_LEGACY_MED, SYS_M_PREFIX fmt, a, b, c)
#define SYS_M_MSG_LOW(fmt, a, b, c)  \
   MSG_SPRINTF_3(MSG_SSID_DFLT, MSG_LEGACY_LOW, SYS_M_PREFIX fmt, a, b, c)
#endif

typedef enum SYS_M_SPECIAL_MSG_T
{
    SYS_M_NONSPECIAL_MSG = 0,
    SYS_M_SHUTDOWN_MSG   = 1,
    SYS_M_UNKNOWN_MSG    = 3
} SYS_M_SPECIAL_MSG_TYPE;

typedef enum SYS_M_COMMUNICATION_T
{
    SYS_M_SMSM_P2P       = 0,
    SYS_M_SMD            = 1
} SYS_M_COMMUNICATION_TYPE;

//init function
void sys_m_init(void);


//reset function
void sys_m_reset(void);

//begin shutdown
void sys_m_shutdown(SYS_M_COMMUNICATION_TYPE);

//shutdown function
void sys_m_shutdown_internal(void);

//spin function, for apps break
void sys_m_spin(void);

//function for error handler to initialize SFR buffer
void *sys_m_init_sfr_buffer(void);

#define SYS_M_AP_NOTIFY_RCV   0x00000002
#define SYS_M_TASKS_COMPLETE  0x00000004
#define SYS_M_RESET           0x00000100
#define SYS_M_MODE_RESET      0x00001000

#define SYS_M_VER_STR               "info:version:0:1"
#define sys_m_smd_port              "sys_mon"
#define SYS_M_SMP2P_PORT_OUT        "slave-kernel"
#define SYS_M_SMP2P_PORT_IN         "master-kernel"
#define SYS_M_ERR_UNKNOWN_MSG       "err:unknown"
#define ERR_SSR_REASON_SIZE_BYTES   80

#endif  /* SYS_M_H */
