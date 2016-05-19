#ifndef SENSOR_PDINIT_H_
#define SENSOR_PDINIT_H_

/*============================================================================
  FILE: sensor_pdinit.h

  This file contains the Sensors PD init API

  Copyright (c) 2014 Qualcomm Technologies, Inc.  All Rights Reserved.
  Qualcomm Technologies Proprietary and Confidential.
============================================================================*/

/*============================================================================
  EDIT HISTORY FOR MODULE

  This section contains comments describing changes made to the module.
  Notice that changes are listed in reverse chronological order. 

  when        who  what, where, why
  ----------  ---  -----------------------------------------------------------
  6/17/2014  davlee Initial development

============================================================================*/
#include "pd_mon_qurt.h"
#include "qurt.h"
 
/* Debug printf configuration */
#ifdef DEBUG
  #define DEBUG_PRINTF(fmt, arg1, arg2) \
     qurt_printf(fmt, arg1, arg2);
#else
  #define DEBUG_PRINTF(fmt, arg1, arg2) {}
#endif

void pd_sensor_init(void);

#endif /* SENSOR_PDINIT_H_ */
