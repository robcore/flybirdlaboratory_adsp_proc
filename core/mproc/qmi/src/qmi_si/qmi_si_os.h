#ifndef __QMI_SI_OS_H_
#define __QMI_SI_OS_H_
/******************************************************************************
  @file    qmi_si_os.h
  @brief   OS Specific routines internal to QMI SI

  DESCRIPTION
  This header provides an OS abstraction to QMI SI

  ---------------------------------------------------------------------------
  Copyright (c) 2010-2011 Qualcomm Technologies Incorporated. All Rights Reserved. 
  QUALCOMM Proprietary and Confidential.
  ---------------------------------------------------------------------------
*******************************************************************************/
#include "comdef.h"
#include "qurt.h"
#include "stdlib.h"

typedef qurt_mutex_t qmi_si_os_sem_type;

#define qmi_si_os_sem_init(sem) qurt_mutex_init((sem))
#define qmi_si_os_sem_deinit(sem) qurt_mutex_destroy((sem))
#define qmi_si_os_sem_lock(sem) qurt_mutex_lock((sem))
#define qmi_si_os_sem_unlock(sem) qurt_mutex_unlock((sem))

#define qmi_si_os_malloc(ptr) malloc(ptr)
#define qmi_si_os_free(ptr) free(ptr)
#define qmi_si_os_memcpy(dest, src, siz) memcpy(dest, src, siz)

#endif
