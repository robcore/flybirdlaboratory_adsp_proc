#ifndef SYS_M_SMSM_H
#define SYS_M_SMSM_H
/*===========================================================================

           S Y S _ M _ S M S M. H

DESCRIPTION

Copyright (c) 2011 by Qualcomm Technologies, Incorporated.  All Rights Reserved.

===========================================================================
DESCRIPTION
High level system monitor
===========================================================================

                           EDIT HISTORY FOR FILE

$Header: //components/rel/core.adsp/2.6.1/api/debugtools/sys_m_smsm.h#1 $

when       who     what, where, why
--------   ---     ----------------------------------------------------------


===========================================================================*/
#include "comdef.h"

#define SYS_M_SMP2P_SUCCESS         0
#define SYS_M_SMP2P_NOT_READY       1
#define SYS_M_SMP2P_INVALID_PARAM   2

#define SYS_M_AP2SUBSYS_SMSM_ERRFATAL       0x1
#define SYS_M_AP2SUBSYS_SMSM_SHUT_DWN       0x2

#define SYS_M_SUBSYS2AP_SMSM_ERRFATAL       0x1
#define SYS_M_SUBSYS2AP_SMSM_ERR_HDL_RDY    0x2
#define SYS_M_SUBSYS2AP_SMSM_PWR_CLK_RDY    0x4
#define SYS_M_SUBSYS2AP_SMSM_SHUT_DWN_ACK   0x8


/**
  Sets bit in sys_m point to point array to apps

  @param[in] bit       Bit to set
  
  @return
  SYS_M_SMP2P_SUCCESS – successful entry of the bit
  SYS_M_SMP2P_NOT_READY – SYS_M entry is not yet ready
  SYS_M_SMP2P_INVALID_PARAM – SYS_M transport detects invalid parameter

  
  @dependencies
  None.
*/
int32 sys_m_smsm_apps_set(uint32 bit);

/** 
  Single threaded mode version of above (no mutex operations) 
  Sets bit in sys_m point to point array to apps 
                        
  @return
  Error codes
  
  @dependencies
  None.
*/
int32 sys_m_smsm_apps_set_stm(uint32 bits);

#endif  /* SYS_M_SMSM_H */
