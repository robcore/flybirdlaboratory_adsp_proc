/******************************************************************************
 * rfsa_log.h
 *
 * Log module for remote file system access
 *
 * Copyright (c) 2014
 * Qualcomm Technologies Inc.
 * All Rights Reserved.
 * Qualcomm Confidential and Proprietary
 *
 *****************************************************************************/
/*=============================================================================

                        EDIT HISTORY FOR MODULE

  $Header: //components/rel/core.adsp/2.6.1/storage/rfsa_client/src/rfsa_log.h#1 $
  $DateTime: 2014/10/16 12:45:40 $ $Author: pwbldsvc $

when         who     what, where, why
----------   ---     ---------------------------------------------------------- 
2014-02-20   nr      Create.
=============================================================================*/

#ifndef __RFSA_LOG_H__
#define __RFSA_LOG_H__

#ifdef RFSA_ANDROID

  #if defined RFSA_LOG_TO_STDIO
    #include <stdio.h>

    #define LOGD(...)       fprintf(stdout,__VA_ARGS__)

    #define LOGD1(...)      fprintf(stdout,__VA_ARGS__)

    #define LOGD2(...)      fprintf(stdout,__VA_ARGS__)

    #define LOGD3(...)      fprintf(stdout,__VA_ARGS__)

    #define LOGE(...)       fprintf(stdout,__VA_ARGS__)

    #define LOGE1(...)      fprintf(stdout,__VA_ARGS__)
    
    #define LOGE2(...)      fprintf(stdout,__VA_ARGS__)

    #define LOGE3(...)      fprintf(stdout,__VA_ARGS__)

  #endif /* RFSA_LOG_TO_STDIO */

#else

  #if defined RFSA_ADSP /* if not RFSA_ANDROID */

    #include "msg_diag_service.h"
    #define LOG_TAG "ADSP: "

  #elif defined RFSA_MPSS

    #include "msg.h"
    #define LOG_TAG "MPSS: "

  #else
    #error "Compiling for unknown processor"
  #endif

  #if defined (RFSA_ADSP) || defined (RFSA_MPSS)

    #define LOGD(fmt)            MSG(MSG_SSID_RFS_ACCESS, MSG_LVL_LOW, LOG_TAG fmt)

    #define LOGD1(fmt, ...)      MSG_1(MSG_SSID_RFS_ACCESS, MSG_LVL_LOW, LOG_TAG fmt, __VA_ARGS__)

    #define LOGD2(fmt, ...)      MSG_2(MSG_SSID_RFS_ACCESS, MSG_LVL_LOW, LOG_TAG fmt, __VA_ARGS__)

    #define LOGD3(fmt, ...)      MSG_3(MSG_SSID_RFS_ACCESS, MSG_LVL_LOW, LOG_TAG fmt, __VA_ARGS__)

    #define LOGM(fmt)            MSG(MSG_SSID_RFS_ACCESS, MSG_LVL_MED, LOG_TAG fmt)

    #define LOGM1(fmt, ...)      MSG_1(MSG_SSID_RFS_ACCESS, MSG_LVL_MED, LOG_TAG fmt, __VA_ARGS__)

    #define LOGM2(fmt, ...)      MSG_2(MSG_SSID_RFS_ACCESS, MSG_LVL_MED, LOG_TAG fmt, __VA_ARGS__)

    #define LOGM3(fmt, ...)      MSG_3(MSG_SSID_RFS_ACCESS, MSG_LVL_MED, LOG_TAG fmt, __VA_ARGS__)

    #define LOGH(fmt)            MSG(MSG_SSID_RFS_ACCESS, MSG_LVL_HIGH, LOG_TAG fmt)

    #define LOGH1(fmt, ...)      MSG_1(MSG_SSID_RFS_ACCESS, MSG_LVL_HIGH, LOG_TAG fmt, __VA_ARGS__)

    #define LOGH2(fmt, ...)      MSG_2(MSG_SSID_RFS_ACCESS, MSG_LVL_HIGH, LOG_TAG fmt, __VA_ARGS__)

    #define LOGH3(fmt, ...)      MSG_3(MSG_SSID_RFS_ACCESS, MSG_LVL_HIGH, LOG_TAG fmt, __VA_ARGS__)

    #define LOGE(fmt)            MSG(MSG_SSID_RFS_ACCESS, MSG_LVL_ERROR, LOG_TAG fmt)

    #define LOGE1(fmt, ...)      MSG_1(MSG_SSID_RFS_ACCESS, MSG_LVL_ERROR, LOG_TAG fmt, __VA_ARGS__)

    #define LOGE2(fmt, ...)      MSG_2(MSG_SSID_RFS_ACCESS, MSG_LVL_ERROR, LOG_TAG fmt, __VA_ARGS__)

    #define LOGE3(fmt, ...)      MSG_3(MSG_SSID_RFS_ACCESS, MSG_LVL_ERROR, LOG_TAG fmt, __VA_ARGS__)

  #endif

#endif  /* if not RFSA_ANDROID */

#endif /* __RFSA_LOG_H__ */

