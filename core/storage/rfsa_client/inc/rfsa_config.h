/******************************************************************************
 * rfsa_config.h
 *
 * Configuration definition file for remote file system access
 *
 * Copyright (c) 2014
 * Qualcomm Technologies Inc.
 * All Rights Reserved.
 * Qualcomm Confidential and Proprietary
 *
 *****************************************************************************/
/*=============================================================================

                        EDIT HISTORY FOR MODULE

  $Header: //components/rel/core.adsp/2.6.1/storage/rfsa_client/inc/rfsa_config.h#1 $
  $DateTime: 2014/10/16 12:45:40 $ $Author: pwbldsvc $

when         who     what, where, why
----------   ---     ----------------------------------------------------------
2014-05-23   dks     Share shared-memory between MPSS and ADSP.
2014-02-20   nr      Create.
=============================================================================*/

#ifndef __RFSA_CONFIG_H__
#define __RFSA_CONFIG_H__

#ifndef RFSA_CLIENT_ID
  #ifdef RFSA_ADSP
    #define RFSA_CLIENT_ID 0x011013ec
  #elif defined RFSA_MPSS
    #define RFSA_CLIENT_ID 0x011013ed
  #else
    #error "Compiling for unknown processor"
  #endif
#endif

#ifndef RFSA_SUBSYSTEM_ID
  #ifdef RFSA_ADSP
    #define RFSA_SUBSYSTEM_ID "ADSP://"
  #elif defined RFSA_MPSS
    #define RFSA_SUBSYSTEM_ID "MPSS://"
  #else
    #error "Compiling for unknown processor"
  #endif
#endif

#ifndef RFSA_QMI_WAIT_SIGNAL
  #ifdef RFSA_ADSP
    #define RFSA_QMI_WAIT_SIGNAL  0x00010000
  #elif defined RFSA_MPSS
    #define RFSA_QMI_WAIT_SIGNAL  0x80000000
  #else
    #error "Compiling for unknown processor"
  #endif
#endif

#ifndef RFSA_QMI_TIMER_SIGNAL
  #ifdef RFSA_ADSP
    #define RFSA_QMI_TIMER_SIGNAL 0x00000001
  #elif defined RFSA_MPSS
    #define RFSA_QMI_TIMER_SIGNAL 0x20000000
  #else
    #error "Compiling for unknown processor"
  #endif
#endif

#ifndef RFSA_USERSPACE_INSTANCE
  #define RFSA_USERSPACE_INSTANCE 0
#endif

#ifndef RFSA_KERNEL_INSTANCE
  #define RFSA_KERNEL_INSTANCE 1
#endif

#ifndef RFSA_SHARED_BUFFER_SIZE
  #define RFSA_SHARED_BUFFER_SIZE 0x10000
#endif

#if RFSA_USERSPACE_INSTANCE == RFSA_KERNEL_INSTANCE
  #error "The userspace and kernel instances are the same."
#endif

#endif /* __RFSA_CONFIG_H__ */

