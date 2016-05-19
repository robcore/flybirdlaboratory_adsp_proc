/*========================================================================
qurt_elite_signal.cpp

This file contains signals utilities.

Copyright (c) 2010 Qualcomm Technologies, Incorporated.  All Rights Reserved.
QUALCOMM Proprietary.  Export of this technology or software is regulated
by the U.S. Government, Diversion contrary to U.S. law prohibited.
*//*====================================================================== */

/*========================================================================
Edit History

$Header: //components/rel/avs.adsp/2.6.1/elite/qurt_elite/src/qurt_elite_signal.cpp#3 $

when       who     what, where, why
--------   ---     -------------------------------------------------------
02/04/10   mwc     Created file.

========================================================================== */


/* =======================================================================
INCLUDE FILES FOR MODULE
========================================================================== */
#include "qurt_elite.h"

/*--------------------------------------------------------------*/
/* Macro definitions                                            */
/* -------------------------------------------------------------*/

/* -----------------------------------------------------------------------
** Constant / Define Declarations
** ----------------------------------------------------------------------- */

/* =======================================================================
**                          Function Definitions
** ======================================================================= */

/****************************************************************************
** Signals
*****************************************************************************/
ADSPResult qurt_elite_signal_create(qurt_elite_signal_t** ppSignal)
{
   // allocate space
   if (NULL == (*ppSignal = (qurt_elite_signal_t*) qurt_elite_memory_malloc(sizeof(qurt_elite_signal_t), QURT_ELITE_HEAP_DEFAULT)))
   {
      return ADSP_ENOMEMORY;
   }

   QURT_ELITE_ZEROAT(*ppSignal);
#ifdef DEBUG_QURT_ELITE_SIGNAL
   MSG_1(MSG_SSID_QDSP6, DBG_LOW_PRIO, "SIGNAL CREATE: SIG=0x%x \n", *ppSignal);
#endif //DEBUG_QURT_ELITE_SIGNAL
   // return.
   return ADSP_EOK;
}

void qurt_elite_signal_destroy(qurt_elite_signal_t* pSignal)
{
   qurt_elite_channel_t* pChannel = pSignal->pChannel;

   //release the channel bit
   if (pChannel) pChannel->unBitsUsedMask ^= pSignal->unMyChannelBit;

   qurt_elite_memory_free(pSignal);
}

ADSPResult qurt_elite_signal_init(qurt_elite_signal_t* pSignal)
{
   if (NULL == pSignal)
   {
      return ADSP_EBADPARAM;
   }

   QURT_ELITE_ZEROAT(pSignal);
#ifdef DEBUG_QURT_ELITE_SIGNAL
   MSG_1(MSG_SSID_QDSP6, DBG_HIGH_PRIO, "SIGNAL INIT: SIG=0x%x \n", pSignal);
#endif //DEBUG_QURT_ELITE_SIGNAL
   // return.
   return ADSP_EOK;
}

void qurt_elite_signal_deinit(qurt_elite_signal_t* pSignal)
{
   QURT_ELITE_ASSERT(NULL != pSignal);
   qurt_elite_channel_t* pChannel = pSignal->pChannel;

   //release the channel bit
   if (pChannel) pChannel->unBitsUsedMask ^= pSignal->unMyChannelBit;
}
