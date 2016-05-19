/*====*====*====*====*====*====*====*====*====*====*====*====*====*====*====*

    P H R I P H E R A L    A C C E S S    C O N T R O L    M A N A G E R     

GENERAL DESCRIPTION
  This module maintains a QUP table which contains registration
  information about the drivers who register for it. This module also provides
  a QMI service listen to the commands from APPs.

Copyright (c) 2014 by Qualcomm Technologies Incorporated.  All Rights Reserved.

  EDIT HISTORY FOR MODULE

  when        who     what, where, why
  ----------  ---     -----------------------------------------------------------
  2014-06-28  davlee  test code to verify PACman QMI services 

*====*====*====*====*====*====*====*====*====*====*====*====*====*====*====*/

#ifndef __QUP_MANAGER_H
#define __QUP_MANAGER_H

#include <stdio.h>



int qup_manager_register_driver(unsigned qup_id, int (*driver_enable)(void),
				           int (*driver_disable)(void));
void qup_manager_unregister_driver(unsigned qup_id);

#endif /*__QUP_MANAGER_H */
