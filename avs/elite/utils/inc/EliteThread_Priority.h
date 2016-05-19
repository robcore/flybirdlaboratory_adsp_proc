/*========================================================================*/
/** @file EliteThread_Priority.h

This file contains definitions of thread priority of
Elite services.  The thread priority is represented by a number,
and the number increases as the thread priority increases.
*/
/*===========================================================================
NOTE: The @brief description above does not appear in the PDF. 
      The description that displays in the PDF is located in the
      Elite_mainpage.dox file. Contact Tech Pubs for assistance.
===========================================================================*/

/*======================================================================
Copyright (c) 2010-2011, 2013-2014 Qualcomm Technologies, Inc.  All rights reserved.
Confidential and Proprietary - Qualcomm Technologies, Inc.
Export of this technology or software is regulated
by the U.S. Government, Diversion contrary to U.S. law prohibited.
===========================================================================*/

/*========================================================================
Edit History


when       who     what, where, why
--------   ---     -------------------------------------------------------
09/05/14   sw      (Tech Pubs) Merged Doxygen markup from 2.4.
03/20/13   sw      (Tech Pubs) Updated Doxygen markup/comments for 2.0.
01/14/11   dc      Added (featurized) thread priorities for 8200A
10/28/10   sw      (Tech Pubs) Edited/added Doxygen comments and markup.
02/22/10   WJ       Created file.

========================================================================== */
#ifndef ELITETHREAD_PRIORITY_H
#define ELITETHREAD_PRIORITY_H

#include "../../../../qdsp6/tp/inc/tp.h"


#ifdef AUDIOFW_8200A_PL3

#include "task_priority.h"

#else

/** @addtogroup elite_svc_thread_priorities
@{ */
/** @name &nbsp;
    @vertspace{-26}
@{ */

#define ELITETHREAD_AVTIMER_SERVER_PRIO               (255 - (IST_HIGH + 0))
#define ELITETHREAD_DEFAULT_IST_PRIO                  (255 - (IST_HIGH + 1))
#define ELITETHREAD_DYNA_AFE_INTERNAL_BT_PRIO         (255 - (IST_HIGH + 1))
    
#define ELITETHREAD_STAT_AFE_VFR_PRIO                 (255 - (AVS_CRITICAL_PRIO_HIGH + 0))
#define ELITETHREAD_STAT_VOICE_TIMER_SVC_PRIO         (255 - (AVS_CRITICAL_PRIO_HIGH + 1))
#define ELITETHREAD_STAT_VOICE_DELIVERY_SVC_PRIO      (255 - (AVS_CRITICAL_PRIO_HIGH + 2))
    
#define ELITETHREAD_STAT_AFE_PORT_MANAGER_PRIO        (255 - (AVS_HIGH_PRIO_HIGH + 0))
#define ELITETHREAD_DYNA_AFE_INTERNAL_FM_PRIO         (255 - (AVS_HIGH_PRIO_HIGH + 0))
#define ELITETHREAD_STAT_VOICE_MIXER_SVC_PRIO         (255 - (AVS_HIGH_PRIO_HIGH + 1))
#define ELITETHREAD_STAT_AFE_PSEUDOPORT_PRIO          (255 - (AVS_HIGH_PRIO_HIGH + 2))
#define ELITETHREAD_STAT_AFE_DEV_SVC_PRIO             (255 - (AVS_HIGH_PRIO_HIGH + 3))
#define ELITETHREAD_STAT_VOICE_STREAM_SVC_PRIO        (255 - (AVS_HIGH_PRIO_HIGH + 4))
#define ELITETHREAD_STAT_VOICE_PROC_SVC_PRIO          (255 - (AVS_HIGH_PRIO_HIGH + 5))
#define ELITETHREAD_STAT_AUDIO_STREAM_SVC_PRIO        (255 - (AVS_HIGH_PRIO_HIGH + 6))
#define ELITETHREAD_STAT_AUDIO_DEV_SVC_PRIO           (255 - (AVS_HIGH_PRIO_HIGH + 6))
#define ELITETHREAD_STAT_ADSP_CORE_SVC_PRIO           (255 - (AVS_HIGH_PRIO_HIGH + 6))
#define ELITETHREAD_STAT_AFE_CDC_INT_SVC_PRIO         (255 - (AVS_HIGH_PRIO_HIGH + 6))
#define ELITETHREAD_DYNA_MIXER_SVC_PRIO               (255 - (AVS_HIGH_PRIO_HIGH + 7))
#define ELITETHREAD_DYNA_MTMX_PSPD_SVC_PRIO           (255 - (AVS_HIGH_PRIO_HIGH + 7))
#define ELITETHREAD_DYNA_STREAM_ROUTER_SVC_PRIO       (255 - (AVS_HIGH_PRIO_HIGH + 7))
#define ELITETHREAD_PULABLE_PLL_SERVER_PRIO           (255 - (AVS_HIGH_PRIO_HIGH + 8))

#define ELITETHREAD_CVS_PRIO                          (255 - (AVS_MEDIUM_PRIO_HIGH + 0))
#define ELITETHREAD_CVP_PRIO                          (255 - (AVS_MEDIUM_PRIO_HIGH + 1))
#define ELITETHREAD_DYNA_VOICE_DEC_PRIO               (255 - (AVS_MEDIUM_PRIO_HIGH + 2))
#define ELITETHREAD_DYNA_VOICE_DEC_PP_PRIO            (255 - (AVS_MEDIUM_PRIO_HIGH + 3))
#define ELITETHREAD_DYNA_VOICE_PROC_RX_PRIO           (255 - (AVS_MEDIUM_PRIO_HIGH + 4))
#define ELITETHREAD_DYNA_VOICE_PROC_TX_PRIO           (255 - (AVS_MEDIUM_PRIO_HIGH + 5))
#define ELITETHREAD_DYNA_VOICE_ENC_PRIO               (255 - (AVS_MEDIUM_PRIO_HIGH + 6))
#define ELITETHREAD_DYNA_LL_PP_SVC_PRIO               (255 - (AVS_MEDIUM_PRIO_HIGH + 7))
#define ELITETHREAD_DYNA_LL_DEC_SVC_PRIO              (255 - (AVS_MEDIUM_PRIO_HIGH + 8))
#define ELITETHREAD_DYNA_LL_ENC_SVC_PRIO              (255 - (AVS_MEDIUM_PRIO_HIGH + 8))
#define ELITETHREAD_DYNA_PP_SVC_PRIO                  (255 - (AVS_MEDIUM_PRIO_HIGH + 9))
#define ELITETHREAD_DYNA_DEC_SVC_PRIO                 (255 - (AVS_MEDIUM_PRIO_HIGH + 10))
#define ELITETHREAD_DYNA_SWITCH_SVC_PRIO              (255 - (AVS_MEDIUM_PRIO_HIGH + 10))
#define ELITETHREAD_DYNA_ENC_SVC_PRIO                 (255 - (AVS_MEDIUM_PRIO_HIGH + 10))
#define ELITETHREAD_DYNA_LISTEN_SVC_PRIO              (255 - (AVS_MEDIUM_PRIO_HIGH + 10))
#define ELITETHREAD_DYNA_SYNTH_HIGH_PRIO              (255 - (AVS_MEDIUM_PRIO_LOW - 4))
#define ELITETHREAD_DYNA_SYNTH_MIPSCTRL_THREAD_PRIO   (255 - (AVS_MEDIUM_PRIO_LOW - 3))
#define ELITETHREAD_DYNA_SYNTH_SVC_PRIO               (255 - (AVS_MEDIUM_PRIO_LOW - 2))
#define ELITETHREAD_MVM_PRIO                          (255 - (AVS_MEDIUM_PRIO_LOW - 1))
#define ELITETHREAD_STAT_ULTRASOUND_STREAM_SVC_PRIO   (255 - (AVS_MEDIUM_PRIO_LOW + 0))
#define ELITETHREAD_VOICE_TEST_PRIO                   (255 - (AVS_MEDIUM_PRIO_LOW + 0))
#define ELITETHREAD_AUDENCDEC_TEST_PRIO               (255 - (AVS_MEDIUM_PRIO_LOW + 0))
#define ELITETHREAD_COMMON_TEST_PRIO                  (255 - (AVS_MEDIUM_PRIO_LOW + 0))
    
#define ELITETHREAD_STAT_AFE_FFSP_PRIO                (255 - (AVS_LOW_PRIO_HIGH + 0))
#define ELITETHREAD_STAT_LISTEN_STREAM_SVC_PRIO       (255 - (AVS_LOW_PRIO_HIGH + 1))
    
#define ELITETHREAD_STAT_AFE_SW_MAD_PRIO              (255 - (AVS_VERY_LOW_PRIO_HIGH + 0))
#define ELITETHREAD_STAT_AFE_AANC_PRIO                (255 - (AVS_VERY_LOW_PRIO_HIGH + 0))
#define ELITETHREAD_STAT_AFE_FBSP_EXCUR_PRIO          (255 - (AVS_VERY_LOW_PRIO_HIGH + 10))
#define ELITETHREAD_VOCSVC_PRIO                       (255 - (AVS_VERY_LOW_PRIO_HIGH + 11))
#define ELITETHREAD_STAT_AFE_SW_DUTY_CYCLE_PRIO       (255 - (AVS_VERY_LOW_PRIO_HIGH + 0))



#endif  // AUDIOFW_8200A

/** @} */ /* end_name */
/** @} */ /* end_addtogroup elite_svc_thread_priorities */

#endif

