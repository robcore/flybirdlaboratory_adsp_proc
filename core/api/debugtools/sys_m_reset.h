#ifndef SYS_M_RESET_H
#define SYS_M_RESET_H
/*===========================================================================

           S Y S _ M _ R E S E T. H

DESCRIPTION

Copyright (c) 2011 by Qualcomm Technologies, Incorporated.  All Rights Reserved.

===========================================================================
DESCRIPTION
High level system monitor
===========================================================================

                           EDIT HISTORY FOR FILE

$Header: //components/rel/core.adsp/2.6.1/api/debugtools/sys_m_reset.h#1 $

when       who     what, where, why
--------   ---     ----------------------------------------------------------


===========================================================================*/


/**
  Initiates shutdown of the subsystem
                        
  @return
  None.
  
  @dependencies
  None.
*/
extern void sys_m_initiate_shutdown(void);

#endif  /* SYS_M_RESET_H */
