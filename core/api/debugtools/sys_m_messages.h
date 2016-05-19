#ifndef SYS_M_MESSAGES_H
#define SYS_M_MESSAGES_H
/*===========================================================================

           S Y S _ M . H

DESCRIPTION

Copyright (c) 2011 by Qualcomm Technologies, Incorporated.  All Rights Reserved.

===========================================================================
DESCRIPTION
High level system monitor
===========================================================================

                           EDIT HISTORY FOR FILE

$Header: //components/rel/core.adsp/2.6.1/api/debugtools/sys_m_messages.h#1 $

when       who     what, where, why
--------   ---     ----------------------------------------------------------


===========================================================================*/

//Notifications that you may register for
#define SYS_M_SSR_LPASS_BEFORE_SHUTDOWN      "ssr:lpass:before_shutdown"
#define SYS_M_SSR_ADSP_BEFORE_SHUTDOWN       "ssr:adsp:before_shutdown"
#define SYS_M_SSR_WCNSS_BEFORE_SHUTDOWN      "ssr:wcnss:before_shutdown"
#define SYS_M_SSR_DSPS_BEFORE_SHUTDOWN       "ssr:dsps:before_shutdown"
#define SYS_M_SSR_MODEM_BEFORE_SHUTDOWN      "ssr:modem:before_shutdown"
#define SYS_M_SSR_GSS_BEFORE_SHUTDOWN        "ssr:gnss:before_shutdown"
#define SYS_M_SSR_EXT_MODEM_BEFORE_SHUTDOWN  "ssr:ext_modem:before_shutdown"

#define SYS_M_SSR_LPASS_BEFORE_POWERUP       "ssr:lpass:before_powerup"
#define SYS_M_SSR_ADSP_BEFORE_POWERUP        "ssr:adsp:before_powerup"
#define SYS_M_SSR_WCNSS_BEFORE_POWERUP       "ssr:wcnss:before_powerup"
#define SYS_M_SSR_DSPS_BEFORE_POWERUP        "ssr:dsps:before_powerup"
#define SYS_M_SSR_MODEM_BEFORE_POWERUP       "ssr:modem:before_powerup"
#define SYS_M_SSR_GSS_BEFORE_POWERUP         "ssr:gnss:before_powerup"
#define SYS_M_SSR_EXT_MODEM_BEFORE_POWERUP   "ssr:ext_modem:before_powerup"

#define SYS_M_SSR_LPASS_AFTER_POWERUP        "ssr:lpass:after_powerup"
#define SYS_M_SSR_ADSP_AFTER_POWERUP         "ssr:adsp:after_powerup"
#define SYS_M_SSR_WCNSS_AFTER_POWERUP        "ssr:wcnss:after_powerup"
#define SYS_M_SSR_DSPS_AFTER_POWERUP         "ssr:dsps:after_powerup"
#define SYS_M_SSR_MODEM_AFTER_POWERUP        "ssr:modem:after_powerup"
#define SYS_M_SSR_GSS_AFTER_POWERUP          "ssr:gnss:after_powerup"
#define SYS_M_SSR_EXT_MODEM_AFTER_POWERUP    "ssr:ext_modem:after_powerup"

#define SYS_M_SSR_LPASS_AFTER_SHUTDOWN       "ssr:lpass:after_shutdown"
#define SYS_M_SSR_ADSP_AFTER_SHUTDOWN        "ssr:adsp:after_shutdown"
#define SYS_M_SSR_WCNSS_AFTER_SHUTDOWN       "ssr:wcnss:after_shutdown"
#define SYS_M_SSR_DSPS_AFTER_SHUTDOWN        "ssr:dsps:after_shutdown"
#define SYS_M_SSR_MODEM_AFTER_SHUTDOWN       "ssr:modem:after_shutdown"
#define SYS_M_SSR_GSS_AFTER_SHUTDOWN         "ssr:gnss:after_shutdown"
#define SYS_M_SSR_EXT_MODEM_AFTER_SHUTDOWN   "ssr:ext_modem:after_shutdown"

#define SYS_M_ACK                            "ssr:ack"
#define SYS_M_VER                            "info:version"



//Internal error callback 
#define SYS_M_ERR_CB_PREFLUSH                "sys_m_err_cb_preflush"
#define SYS_M_ERR_CB_POSTFLUSH               "sys_m_err_cb_postflush"

//Internal shutdown notifications
//Do NOT use these messages - leverage rcinit/tmc shutdown mechanism
#define SYS_M_SHUTDOWN                       "ssr:shutdown"
#define SYS_M_SHUTDOWN_ACK                   SYS_M_ACK

#endif  /* SYS_M_MESSAGES_H */
