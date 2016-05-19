/*============================================================================

  @file sns_osa_dsps.c

  @brief

  Copyright (c) 2014 Qualcomm Technologies, Inc.  All Rights Reserved.
  Qualcomm Technologies Proprietary and Confidential.

============================================================================*/

/*============================================================================

                        EDIT HISTORY FOR MODULE

This section contains comments describing changes made to the module.
Notice that changes are listed in reverse chronological order.

$Header: //components/rel/ssc.adsp/2.6.1/common/core/src/common/sns_osa_dsps_uimg.c#1 $
$DateTime: 2014/12/01 08:57:58 $ 
$Author: pwbldsvc $ 

when         who     what, where, why
----------   ---     ---------------------------------------------------------
10/26/2014   pn     Made last param to sns_os_mutex_pend() optional
08/24/2014   vy     Replaced MSG_x by UMSG_x
06/05/2014   vy     Moved sns_osa functions to uImage

============================================================================*/

/*=====================================================================
  INCLUDES
  =======================================================================*/
#include "sns_memmgr.h"
#include "sns_osa.h"

/*=====================================================================
  INTERNAL FUNCTION
  =======================================================================*/

sig_node    *sns_os_sigs_add              (OS_FLAG_GRP     *pgrp,
                                           OS_FLAGS         flags)
{
  if (pgrp == NULL)
  {
    UMSG(MSG_SSID_SNS, DBG_ERROR_PRIO, "signal group pointer is NULL" );
    return NULL;
  }

  pgrp->unChannelWaitMask |= flags;

  return &(pgrp->unChannelWaitMask); /* Not used anymore */
}


OS_FLAGS      sns_os_sigs_pend             (OS_FLAG_GRP     *pgrp,
                                            OS_FLAGS         flags,
                                            uint8_t          wait_type,
                                            uint32_t         timeout,
                                            uint8_t         *perr)
{
  uint32_t result = 0;

  //UMSG(MSG_SSID_SNS, DBG_LOW_PRIO, "sig pend : wait on channel");
  // block on channel to wait
  qurt_anysignal_wait(&pgrp->signal, pgrp->unChannelWaitMask);
  result = qurt_anysignal_get(&pgrp->signal);
  // when it receives, clear and exit

  *perr = OS_ERR_EVENT_TYPE;
  qurt_anysignal_clear(&pgrp->signal, result);
  *perr = OS_ERR_NONE;

  return result;
}


OS_FLAGS      sns_os_sigs_post             (OS_FLAG_GRP     *pgrp,
                                            OS_FLAGS         flags,
                                            uint8_t          opt,
                                            uint8_t         *perr)
{
  uint8_t os_err = OS_ERR_NONE;

  if (pgrp == NULL)
  {
    UMSG(MSG_SSID_SNS, DBG_HIGH_PRIO, "pgrp is NULL");
    return 0;
  }

  if (opt == OS_FLAG_SET)
  {
    qurt_anysignal_set(&pgrp->signal, flags);
  }
  else if (opt == OS_FLAG_CLR)
  {
    qurt_anysignal_clear(&pgrp->signal, flags);
  }
  else
  {
    os_err = OS_ERR_INVALID_OPT;
  }
  
  if (perr != NULL)
  {
    *perr = os_err;
  }
  return flags;
}


void          sns_os_mutex_pend            (OS_EVENT        *pevent,
                                            uint32_t         timeout,
                                            uint8_t         *perr)
{
  //UMSG(MSG_SSID_SNS, DBG_HIGH_PRIO, "...... MUTEX LOCK ......");
  qurt_rmutex_lock(&(pevent->mutex));
  if (perr != NULL)
  {
    *perr = OS_ERR_NONE;
  }
}

uint8_t       sns_os_mutex_post            (OS_EVENT        *pevent)
{
  //UMSG(MSG_SSID_SNS, DBG_HIGH_PRIO, "...... MUTEX UNLOCK ......");
  qurt_rmutex_unlock(&(pevent->mutex));
  return 0;
}


//Mutex
OS_EVENT     *sns_os_mutex_create_uimg     (uint8_t          prio,
                                            uint8_t         *perr)
{
      
  //UMSG(MSG_SSID_SNS, DBG_HIGH_PRIO, "mutex create malloc");
  OS_EVENT *mutex_event = SNS_OS_U_MALLOC(SNS_DBG_MOD_OSA, (sizeof(OS_EVENT)));
  
  if (mutex_event == NULL)
  {
    UMSG(MSG_SSID_SNS, DBG_ERROR_PRIO, "mutex create fail");
    *perr = OS_ERR_MEM_FULL;
    return NULL;
  }

  //UMSG(MSG_SSID_SNS, DBG_HIGH_PRIO, "mutex create mutex init");
  qurt_rmutex_init(&(mutex_event->mutex));

  *perr = OS_ERR_NONE;
  //UMSG(MSG_SSID_SNS, DBG_HIGH_PRIO, "mutex create return");
  return mutex_event;
}
