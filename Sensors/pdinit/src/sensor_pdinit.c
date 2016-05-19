/*============================================================================
  FILE: sensor_pdinit.c

  This file contains the Sensors PD init implementation

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

#include "sensor_pdinit.h"

void pd_sensor_init(void){
  DEBUG_PRINTF("%s: multi_pd_spawn start...pid is %d\n", __func__, qurt_getpid());
  int count = 5;

  PD_MON_HANDLE hPdSensor = pd_mon_spawn(&count, SENSOR_IMG_NAME);

  if (hPdSensor == 0){
    qurt_printf("%s: failed to spwan ... count: %d \n", __func__, count);
  }
  qurt_printf("%s: Protection Domain Launched %s\n", __func__, SENSOR_IMG_NAME);
}

