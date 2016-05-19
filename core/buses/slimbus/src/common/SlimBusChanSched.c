/*
===========================================================================

FILE:         SlimBusChanSched.c

DESCRIPTION:  This file implements the SLIMbus core driver 
              channel scheduling functionality.

===========================================================================

                             Edit History

$Header: //components/rel/core.adsp/2.6.1/buses/slimbus/src/common/SlimBusChanSched.c#1 $

when       who     what, where, why
--------   ---     --------------------------------------------------------
04/23/14   MJS     Support for ultrasound high-concurrency use case.
04/30/13   MJS     Support for spcifying minimum clock gear for scheduling.
07/24/12   MJS     Make sure open slots are not less than zero after scheduling.
04/09/12   MJS     Fix SAL warnings.
04/04/12   MJS     Fixes for level 4 warnings.
03/28/12   MJS     Compatibility with WPP logging.
01/07/12   MJS     Fix klocwork issues.
12/11/11   MJS     Remove references to DAL.
11/23/11   MJS     Fix issue where scheduling was improperly succeeding
                   when both slot buckets had exactly zero open slots.
11/15/11   MJS     Fix klocwork issues.
01/21/11   MJS     Initial revision.

===========================================================================
             Copyright (c) 2011, 2012, 2013, 2014 Qualcomm Technologies Incorporated.
                    All Rights Reserved.
                  QUALCOMM Proprietary/GTDR
===========================================================================
*/

#include "SlimBusTarget.h"
#include SLIMBUS_OS_H
#include "SlimBus.h"
#include "SlimBusConsts.h"
#include "SlimBusLists.h"
#include SB_TRACE_HEADER(SlimBusChanSched)

/**
 * @brief Gets the Subframe Mode (SM) encoding based on the 
 *        width of the shared message channel and the length of
 *        the subframe in slots.  Also computes the number of
 *        slots per superframe dedicated to the message channel.
 *
 * This function gets the Subframe Mode (SM) based on the width 
 * of the shared message channel and the length of the subframe 
 * in slots.  Also computes the number of slots per superframe 
 * dedicated to the message channel. 
 * 
 * @param[in] uCtrlWidth  Width of the message channel in slots
 * @param[in] uSubFrmLen  Length of the subframe in slots
 * @param[in] uMsgSlots  Number of slots per superframe 
 *       dedicated to messaging
 * 
 * @return The encoded Subframe Mode 
 */
static uint32 GetSubFrameCoding(uint32 *uCtrlWidth, uint32 *uSubFrmLen, uint32 *uMsgSlots)
{
  uint32 uCode = 0;
  
  if ( *uCtrlWidth == *uSubFrmLen )
  {
    *uCtrlWidth = 8;
    *uSubFrmLen = 8;
    *uMsgSlots = 
      SB_SLOTS_PER_SUPERFRAME - 
      SB_FRAME_SLOTS_PER_SUPERFRAME -
      SB_GUIDE_SLOTS_PER_SUPERFRAME;
    return 0;
  }
  
  if ( *uSubFrmLen == 6 )
  {
    uCode = 0;
    *uMsgSlots = 256;
  }
  else if ( *uSubFrmLen == 8 )
  {
    uCode = 1;
    *uMsgSlots = 192;
  }
  else if ( *uSubFrmLen == 24 )
  {
    uCode = 2;
    *uMsgSlots = 64;
  }
  else /* 32 */
  {
    uCode = 3;
    *uMsgSlots = 48;
  }
  
  if (*uCtrlWidth < 8)
  {
    if ( *uCtrlWidth >= 6 )
    {
      *uCtrlWidth = 6;
      uCode |= 0x14;
    }
    else /* <= 5 */
    {
      if ( *uCtrlWidth == 5)
      {
        *uCtrlWidth = 4;
      }
      uCode |= (*uCtrlWidth << 2);
    }
  }
  else 
  {
    uCode -= 2;
    
    if ( *uCtrlWidth >= 24 )
    {
      *uCtrlWidth = 24;
      uCode |= 0x1e;
    }
    else if ( *uCtrlWidth >= 16 )
    {
      *uCtrlWidth = 16;
      uCode |= 0x1c;
    }
    else if ( *uCtrlWidth >= 12 )
    {
      *uCtrlWidth = 12;
      uCode |= 0x1a;
    }
    else /* >= 8 */
    {
      *uCtrlWidth = 8;
      uCode |= 0x18;
    }
  }
  
  *uMsgSlots  =
    (*uMsgSlots * *uCtrlWidth) - 
    SB_FRAME_SLOTS_PER_SUPERFRAME -
    SB_GUIDE_SLOTS_PER_SUPERFRAME;
  return uCode;
}

/**
 * @brief Shift the segments offsets for all the allocated data 
 *        channels by a fixed amount
 *
 * This function shifts the segment offset for all the allocated 
 * data channels by a fixed amount. 
 * 
 * @param[in] pRoot  Pointer to the head of the linked list of 
 *       data channel parameter structures
 * @param[in] uShft  Shift amount in slots
 */
static void ShiftSegmentOffsets( SlimBusLinkNodeType *pRoot, uint32 uShft )
{
  SlimBusChannelParamType *pParam = NULL;

  while ( NULL != (pParam = NextParamNode(pRoot, pParam)) )
  {
    /* No need to shift channels that are pending removal */
    if (pParam->eStatus == SB_CHANNEL_PENDING_REMOVAL)
    {
      continue;
    }
    
    pParam->uNewOffset += uShft;
    /* Segment offset must be <= the segment interval */
    if ( pParam->uNewOffset >= pParam->uNewInterval )
    {
      pParam->uNewOffset -= pParam->uNewInterval;
    }
  }
}

/**
 * @brief Perform data channel scheduling
 *
 * This function schedules data channels within the frame 
 * structure, based on a given root frequency and clock gear. 
 * 
 * @param[in] pDevCtxt  Pointer to the device context
 * @param[in] uClkGear  Clock gear to use for scheduling
 * @param[out] puCtrlWidth  Location to store the scheduled 
 *       message channel width
 * @param[out] puSubFrmLen  Location to store the scheduled 
 *       subframe mode
 * 
 * @return SB_SUCCESS on success, an error code if there was a 
 *         scheduling error
 */
static SBResult SlimBus_DoScheduleChannels
(
  SlimBusDevCtxt *pDevCtxt,
  uint32 uClkGear,
  uint32 *puCtrlWidth,
  uint32 *puSubFrmLen
)
{
  SlimBusChannelParamType *pParam3 = NULL, *pParam1 = NULL;
  SlimBusRateCoeffType eBias;

  /* Find the first data channel for the coefficient 1 and 3 lists that are 
     not pending removal, the first data channels will be used as a starting
     point for the segment rate exponent */
  while (NULL != (pParam3 = NextParamNode(&pDevCtxt->pSched->ChanParamList3, pParam3)) &&
         pParam3->eStatus == SB_CHANNEL_PENDING_REMOVAL)
  {
    /* do nothing */
  }
  while (NULL != (pParam1 = NextParamNode(&pDevCtxt->pSched->ChanParamList1, pParam1)) &&
         pParam1->eStatus == SB_CHANNEL_PENDING_REMOVAL)
  {
    /* do nothing */
  }

  /* Decide if we should usea coefficient 1 or 3 bias for channel scheduling.
     If there are no channels to schedule, just set the subframe mode to 100%
     message channel and return. */
  if ( NULL == pParam3 && NULL == pParam1 )
  {
    *puCtrlWidth = 8;
    *puSubFrmLen = 8;
    return SB_SUCCESS;
  }
  else if ( NULL == pParam3 )
  {
    /* Default is to do coefficient 3 biased scheduling, unless there are 
       no coefficient 3 channels to schedule */
    eBias = SB_RATE_COEFF_1;
  }
  else
  {
    eBias = SB_RATE_COEFF_3;
  }
  
  if ( eBias == SB_RATE_COEFF_1 )
  {
    uint32 uExpShft = SB_MAX_CLK_GEAR - uClkGear;
    int32 iCurExp, iFinalExp;
    uint32 uCurInterval, uCurMaxSlots;
    int32 iOpenSlots1[2] = { 0 };
    SlimBusChannelParamType *pParamTemp;

    /* Find the last channel in the coefficient 1 list, we will use to know
       when we have scheduled all the coefficient 1 channels */
    pParamTemp = PeekTailParam(&pDevCtxt->pSched->ChanParamList1);
    while ( NULL != pParamTemp &&
            pParamTemp->eStatus == SB_CHANNEL_PENDING_REMOVAL )
    {
      pParamTemp = PeekTailParam(&pParamTemp->LinkNode);
    }
    if ( NULL == pParamTemp )
    {
      /* This should never be NULL due to check at beginning of function */
      return SB_ERROR;
    }
    iFinalExp = pParamTemp->ucRootExp;
    
    /* -1 to account for incrementing iCurExp during first time through loop */
    iCurExp = (int32)uExpShft - 1;

    /* Note: use (iCurExp+1) because can't right shift by a negative value */
    uCurInterval = (SB_MAX_INTERVAL_COEFF_1*2)>>(iCurExp+1);
    uCurMaxSlots = uCurInterval/2;
    iOpenSlots1[0] = iOpenSlots1[1] = uCurMaxSlots;

    while ( NULL != pParam1 ||
            uCurInterval > 24 )
    {
      uCurInterval /= 2;
      uCurMaxSlots /= 2;

      /* Update 4k family open slot records (eCoeff == 1) */
      if ( iOpenSlots1[1] < iOpenSlots1[0] )
      {
        iOpenSlots1[1] = iOpenSlots1[1] - uCurMaxSlots;
      }
      else
      {
        iOpenSlots1[1] = iOpenSlots1[0] - uCurMaxSlots;
      }
      iOpenSlots1[0] = uCurMaxSlots;
      if ( iOpenSlots1[1] < 0 )
      {
        iOpenSlots1[0] += iOpenSlots1[1];
        iOpenSlots1[1] = 0;
      }
      if ( iOpenSlots1[0] <= 0 )
      {
        /* error */
        return SB_ERROR;
      }
      iCurExp++;

      /* Schedule 4k family channels (eCoeff == 1) */
      while ( NULL != pParam1 &&
              iCurExp == (int32)(pParam1->ucRootExp + uExpShft) )
      {
        if (pParam1->eStatus == SB_CHANNEL_PENDING_REMOVAL)
        {
          pParam1 = NextParamNode(&pDevCtxt->pSched->ChanParamList1, pParam1);
          continue;
        }
        if ( iOpenSlots1[1] >= iOpenSlots1[0] ||
             ( iFinalExp == (int32)pParam1->ucRootExp &&
               uCurInterval <= 24 &&
               iOpenSlots1[0] == (int32) uCurMaxSlots ) )
        {
          iOpenSlots1[1] -= pParam1->ucSegLen;
          pParam1->uNewOffset = uCurMaxSlots + iOpenSlots1[1];
          if ( iOpenSlots1[1] < 0 && iOpenSlots1[0] == (int32) uCurMaxSlots )
          {
            iOpenSlots1[0] += iOpenSlots1[1];
            iOpenSlots1[1] = 0;
            if (iOpenSlots1[0] < 0)
            {
              /*error*/
              return SB_ERROR;
            }
          }
        }
        else
        {
          if ( pParam1->ucSegLen > iOpenSlots1[0] )
          {
            /* error */
            return SB_ERROR;
          }
          iOpenSlots1[0] = pParam1->uNewOffset = iOpenSlots1[0] - pParam1->ucSegLen;
        }
        pParam1->uNewInterval = uCurInterval;
        pParam1 = NextParamNode(&pDevCtxt->pSched->ChanParamList1, pParam1);
      }
    }
    /* We need one of the buckets to have slots remaining for message channel */
    if ( iOpenSlots1[0] <= 0 &&
         iOpenSlots1[1] <= 0 )
    {
      return SB_ERROR;
    }
    if ( iOpenSlots1[1] > iOpenSlots1[0] )
    {
      /* Do the electric shuffle */
      int32 iTemp = iOpenSlots1[0];
      iOpenSlots1[0] = iOpenSlots1[1];
      iOpenSlots1[1] = iTemp;
      ShiftSegmentOffsets(&pDevCtxt->pSched->ChanParamList1, uCurMaxSlots);
    }

    /* Choose subframe mode to maximize available bandwidth */
    {
      int32 iMaxCtrlWidth1 = iOpenSlots1[0];
      if (iOpenSlots1[0] == (int32) uCurMaxSlots)
      {
        iMaxCtrlWidth1 += iOpenSlots1[1];
      }
      if ( uCurInterval >= 24 )
      {
        *puSubFrmLen = 24;
        *puCtrlWidth = iMaxCtrlWidth1;
      }
      else if ( uCurInterval == 12 )
      {
        if (iMaxCtrlWidth1 > iOpenSlots1[1]*4)
        {
          *puSubFrmLen = 24;
          *puCtrlWidth = iMaxCtrlWidth1;
        }
        else
        {
          *puSubFrmLen = 6;
          *puCtrlWidth = iOpenSlots1[1];
        }
      }
      else 
      {
        *puSubFrmLen = 6;
        *puCtrlWidth = iMaxCtrlWidth1;
      }
    }
  }
  else
  {
    uint32 uExpShft = SB_MAX_CLK_GEAR - uClkGear;
    int32 iCurExp, iFinalExp;
    uint32 uCurInterval, uCurMaxSlots;
    int32 iOpenSlots3[4] = { 0 };
    int32 iOpenSlots1[6] = { 0 };
    SBBOOL iOpenSlots1Valid = FALSE;
    uint32 uNumBuckets3 = 2;
    uint32 uNumCurParams3 = 0, uNumCurParams1 = 0;
    uint32 uNextExpDiff3 = 0;
    int32 i;
    SlimBusChannelParamType *pParamTemp;

    pParamTemp = PeekTailParam(&pDevCtxt->pSched->ChanParamList3);
    while ( NULL != pParamTemp &&
            pParamTemp->eStatus == SB_CHANNEL_PENDING_REMOVAL )
    {
      pParamTemp = PeekTailParam(&pParamTemp->LinkNode);
    }
    if ( NULL == pParamTemp )
    {
      /* This should never be NULL due to check at beginning of function */
      return SB_ERROR;
    }
    iFinalExp = pParamTemp->ucRootExp;
    if (NULL != pParam1)
    {
      int32 iExp;
      pParamTemp = PeekTailParam(&pDevCtxt->pSched->ChanParamList1);
      while ( NULL != pParamTemp &&
              pParamTemp->eStatus == SB_CHANNEL_PENDING_REMOVAL )
      {
        pParamTemp = PeekTailParam(&pParamTemp->LinkNode);
      }
      if ( NULL == pParamTemp )
      {
        /* This should never be NULL due to check at beginning of function */
        return SB_ERROR;
      }
      iExp = pParamTemp->ucRootExp;
      if (iExp > iFinalExp)
      {
        iFinalExp = iExp;
      }
    }
    
    /* -1 to account for incrementing iCurExp during first time through loop */
    iCurExp = (int32)uExpShft - 1;

    /* Note: use (iCurExp+1) because can't right shift by a negative value */
    uCurInterval = (SB_MAX_INTERVAL_COEFF_3*2)>>(iCurExp+1);
    uCurMaxSlots = uCurInterval/2;
    iOpenSlots3[0] = iOpenSlots3[1] = uCurMaxSlots;

    while ( NULL != pParam3 ||
            NULL != pParam1 ||
            uCurInterval > 32 )
    {
      uCurInterval /= 2;
      
      /* Update 12k family open slot records (eCoeff == 3) */
      if ( uNumBuckets3 > 2 )
      {
        /* Reduce back to 2 buckets from 4 */
        uNumBuckets3 = 2;
        if ( iOpenSlots3[3] < iOpenSlots3[1] )
        {
          iOpenSlots3[1] = iOpenSlots3[3];
        }
        if ( iOpenSlots3[2] < iOpenSlots3[0] )
        {
          iOpenSlots3[0] = iOpenSlots3[2];
        }
        iOpenSlots3[3] = iOpenSlots3[2] = 0;
      }
      else
      {
        /* Halve the bucket size */
        uCurMaxSlots /= 2;

        if ( iOpenSlots3[1] < iOpenSlots3[0] )
        {
          iOpenSlots3[1] = iOpenSlots3[1] - uCurMaxSlots;
        }
        else
        {
          iOpenSlots3[1] = iOpenSlots3[0] - uCurMaxSlots;
        }
        iOpenSlots3[0] = uCurMaxSlots;
        if ( iOpenSlots3[1] < 0 )
        {
          iOpenSlots3[0] += iOpenSlots3[1];
          iOpenSlots3[1] = 0;
        }
        if ( iOpenSlots3[0] <= 0 )
        {
          /* error */
          return SB_ERROR;
        }
      }
      iCurExp++;

      /* Check the number of channels to schedule for this value of iCurExp */
      uNumCurParams3 = uNumCurParams1 = 0;
      uNextExpDiff3 = 0;
      pParamTemp = pParam3;
      while (NULL != pParamTemp &&
             iCurExp == (int32)(pParamTemp->ucRootExp + uExpShft))
      {
        if (pParamTemp->eStatus != SB_CHANNEL_PENDING_REMOVAL)
        {
          uNumCurParams3++;
        }
        pParamTemp = NextParamNode(&pDevCtxt->pSched->ChanParamList3, pParamTemp);
      }
      if ( uNumCurParams3 > 0 )
      {
        while (NULL != pParamTemp)
        {
          if (pParamTemp->eStatus != SB_CHANNEL_PENDING_REMOVAL)
          {
            uNextExpDiff3 = pParamTemp->ucRootExp - pParam3->ucRootExp;
            break;
          }
          pParamTemp = NextParamNode(&pDevCtxt->pSched->ChanParamList3, pParamTemp);
        }
      }
      pParamTemp = pParam1;
      while (NULL != pParamTemp &&
             iCurExp == (int32)(pParamTemp->ucRootExp + uExpShft))
      {
        if (pParamTemp->eStatus != SB_CHANNEL_PENDING_REMOVAL)
        {
          uNumCurParams1++;
        }
        pParamTemp = NextParamNode(&pDevCtxt->pSched->ChanParamList1, pParamTemp);
      }
      if ( uNumCurParams3 > 2 &&
           uNumCurParams1 == 0 &&
           iOpenSlots3[1] > (int32)uCurMaxSlots/2 &&
           iOpenSlots3[0] > (int32)uCurMaxSlots/2 &&
           NULL != pParam3 &&
           ( uCurInterval > 64 ||
             uNextExpDiff3 > 1 ) )
      {
        /* Increase the number of buckets to 4 if we have many 12k family channels */
        uNumBuckets3 = 4;
        uCurMaxSlots /= 2;
        iOpenSlots3[3] = iOpenSlots3[1] - uCurMaxSlots;
        iOpenSlots3[2] = uCurMaxSlots;
        iOpenSlots3[1] = iOpenSlots3[0] - uCurMaxSlots;
        iOpenSlots3[0] = uCurMaxSlots;
      }

      /* Schedule 12k family channels (eCoeff == 3) */
      while ( NULL != pParam3 &&
              iCurExp == (int32)(pParam3->ucRootExp + uExpShft) )
      {
        static const int32 iSrchOrder[] = { 3, 1, 2, 0 };
        int32 maxOpenSlots = 0;
        int32 max_i = 0, i = 0;
        
        if (pParam3->eStatus == SB_CHANNEL_PENDING_REMOVAL)
        {
          pParam3 = NextParamNode(&pDevCtxt->pSched->ChanParamList3, pParam3);
          continue;
        }
        iOpenSlots1Valid = FALSE;
        if ( uNumBuckets3 == 2 &&
             iFinalExp == (int32)pParam3->ucRootExp &&
             uCurInterval <= 32 &&
             iOpenSlots3[0] == (int32) uCurMaxSlots &&
             NULL == pParam1/*TODO: revisit*/ )
        {
          max_i = 1;
        }
        else
        {
          for ( i = 0; i < 4; i++ )
          {
            if ( iOpenSlots3[iSrchOrder[i]] > maxOpenSlots )
            {
              maxOpenSlots = iOpenSlots3[iSrchOrder[i]];
              max_i = iSrchOrder[i];
            }
          }
        }
        iOpenSlots3[max_i] -= pParam3->ucSegLen;
        pParam3->uNewOffset = (uCurMaxSlots*max_i) + iOpenSlots3[max_i];
        if ( iOpenSlots3[max_i] < 0 )
        {
          if ( max_i > 0 && iOpenSlots3[max_i-1] == uCurMaxSlots )
          {
            iOpenSlots3[max_i-1] += iOpenSlots3[max_i];
            iOpenSlots3[max_i] = 0;
            if ( iOpenSlots3[max_i-1] < 0 )
            {
              return SB_ERROR;
            }
          }
          else
          {
            return SB_ERROR;
          }
        }
        pParam3->uNewInterval = uCurInterval;
        pParam3 = NextParamNode(&pDevCtxt->pSched->ChanParamList3, pParam3);
      }
      while (NULL != pParam3 &&
             pParam3->eStatus == SB_CHANNEL_PENDING_REMOVAL)
      {
        pParam3 = NextParamNode(&pDevCtxt->pSched->ChanParamList3, pParam3);
      }

      /* Update 4k family open slot records (eCoeff == 1) */
      if (!iOpenSlots1Valid)
      {
        iOpenSlots1[0] = iOpenSlots1[2] = iOpenSlots1[4] = iOpenSlots3[0];
        iOpenSlots1[1] = iOpenSlots1[3] = iOpenSlots1[5] = iOpenSlots3[1];
      }
      else
      {
        int32 iOpenSlots1p[6];
        memcpy(iOpenSlots1p, iOpenSlots1, sizeof(iOpenSlots1));
        for (i = 0; i < 3; i++)
        {
          if (iOpenSlots1p[i] < iOpenSlots1p[i+3])
          {
            iOpenSlots1[i*2+1] = iOpenSlots1p[i];
          }
          else
          {
            iOpenSlots1[i*2+1] = iOpenSlots1p[i+3];
          }
        }
        for (i = 0; i < 3; i++)
        {
          iOpenSlots1[i*2+1] -= uCurMaxSlots;
          iOpenSlots1[i*2] = uCurMaxSlots;
          if (iOpenSlots1[i*2+1] < 0)
          {
            iOpenSlots1[i*2] += iOpenSlots1[i*2+1];
            iOpenSlots1[i*2+1] = 0;
          }
          if (iOpenSlots1[i*2] < 0)
          {
            /* error */
            return SB_ERROR;
          }
        }
      }

      /* Schedule 4k family channels (eCoeff == 1) */
      while ( NULL != pParam1 &&
              iCurExp == (int32)(pParam1->ucRootExp + uExpShft) )
      {
        /* Note: search order only has effect when iOpenSlots1Valid is TRUE */
        static const int32 iSrchOrder1[] = { 5, 2, 4, 1, 3, 0 };
        static const int32 iSrchOrder2[] = { 5, 3, 1, 4, 2, 0 };
        static const int32 *iSrchOrder;
        int32 maxOpenSlots = 0;
        int32 max_i = 0, i = 0;

        if (pParam1->eStatus == SB_CHANNEL_PENDING_REMOVAL)
        {
          pParam1 = NextParamNode(&pDevCtxt->pSched->ChanParamList1, pParam1);
          continue;
        }
        iOpenSlots1Valid = TRUE;
        if (NULL != pParam3 && 
            pParam3->ucRootExp == pParam1->ucRootExp+1)
        {
          iSrchOrder = iSrchOrder2;
        }
        else
        {
          iSrchOrder = iSrchOrder1;
        }
        for (i=0; i<6; i++)
        {
          if (iOpenSlots1[iSrchOrder[i]] > maxOpenSlots)
          {
            maxOpenSlots = iOpenSlots1[iSrchOrder[i]];
            max_i = iSrchOrder[i];
          }
        }
        iOpenSlots1[max_i] -= pParam1->ucSegLen;
        pParam1->uNewOffset = (uCurMaxSlots*max_i) + iOpenSlots1[max_i];
        if (iOpenSlots1[max_i] < 0)
        {
          if (((max_i&1)==1) && (iOpenSlots1[max_i-1] == (int32) uCurMaxSlots))
          {
            iOpenSlots1[max_i-1] += iOpenSlots1[max_i];
            if (iOpenSlots3[0] > iOpenSlots1[max_i-1])
            {
              iOpenSlots3[0] = iOpenSlots1[max_i-1];
            }
            iOpenSlots3[1] = iOpenSlots1[max_i] = 0;
            if (iOpenSlots1[max_i-1] < 0)
            {
              /* error */
              return SB_ERROR;
            }
          }
          else
          {
            /*error*/
            return SB_ERROR;
          }
        }
        else
        {
          if (iOpenSlots3[max_i&1] > iOpenSlots1[max_i])
          {
            iOpenSlots3[max_i&1] = iOpenSlots1[max_i];
          }
        }
        pParam1->uNewInterval = uCurInterval*3;
        pParam1 = NextParamNode(&pDevCtxt->pSched->ChanParamList1, pParam1);
      }
      while (NULL != pParam1 &&
             pParam1->eStatus == SB_CHANNEL_PENDING_REMOVAL)
      {
        pParam1 = NextParamNode(&pDevCtxt->pSched->ChanParamList1, pParam1);
      }
    }
    /* We need one of the buckets to have slots remaining for message channel */
    if ( iOpenSlots3[0] <= 0 &&
         iOpenSlots3[1] <= 0 )
    {
      return SB_ERROR;
    }
    /* If the second open slot bucket has more available slots than the first
       bucket, shift the segment offsets so that the first and second buckets
       are swapped */
    if ( iOpenSlots3[1] > iOpenSlots3[0] )
    {
      /* Do the electric shuffle */
      int32 iTemp = iOpenSlots3[0];
      iOpenSlots3[0] = iOpenSlots3[1];
      iOpenSlots3[1] = iTemp;
      iTemp = iOpenSlots1[5];
      iOpenSlots1[5] = iOpenSlots1[4];
      iOpenSlots1[4] = iOpenSlots1[3];
      iOpenSlots1[3] = iOpenSlots1[2];
      iOpenSlots1[2] = iOpenSlots1[1];
      iOpenSlots1[1] = iOpenSlots1[0];
      iOpenSlots1[0] = iTemp;
      ShiftSegmentOffsets(&pDevCtxt->pSched->ChanParamList1, uCurMaxSlots);
      ShiftSegmentOffsets(&pDevCtxt->pSched->ChanParamList3, uCurMaxSlots);
    }
    
    /* Choose subframe mode to maximize available bandwidth */
    {
      int32 iMaxCtrlWidth3 = iOpenSlots3[0];
      int32 iMaxCtrlWidth1 = iOpenSlots1[0];
      if (iOpenSlots3[0] == (int32) uCurMaxSlots)
      {
        iMaxCtrlWidth3 += iOpenSlots3[1];
      }
      for (i = 0; i < 5 && iOpenSlots1[i] == (int32) uCurMaxSlots; i++)
      {
        iMaxCtrlWidth1 += iOpenSlots1[i+1];
      }
      if ( uCurInterval >= 32 )
      {
        *puSubFrmLen = 32;
        *puCtrlWidth = iMaxCtrlWidth3;
      }
      else if ( uCurInterval == 16 )
      {
        if (iMaxCtrlWidth3 > iOpenSlots3[1]*4)
        {
          *puSubFrmLen = 32;
          *puCtrlWidth = iMaxCtrlWidth3;
        }
        else
        {
          *puSubFrmLen = 8;
          *puCtrlWidth = iOpenSlots3[1];
        }
      }
      else 
      {
        if (iMaxCtrlWidth1*8 >= iMaxCtrlWidth3*24)
        {
          *puSubFrmLen = 24;
          *puCtrlWidth = iMaxCtrlWidth1;
        }
        else
        {
          *puSubFrmLen = 8;
          *puCtrlWidth = iMaxCtrlWidth3;
        }
      }
    }
  }
  
  return SB_SUCCESS;
}

/**
 * @brief Verify that the scheduled data channels do not overlap 
 *        each other or overlap the message channel
 *
 * This function verifies that the scheduled data channels do 
 * not overlap each other or overlap the message channel. 
 * 
 * @param[in] pDevCtxt  Pointer to the device context
 * @param[in] uCtrlWidth  Width of the message channel in slots
 * @param[in] uSubFrmLen  Length of the subframe mode in slots
 * 
 * @return SB_SUCCESS if the data channel schedule is valid, or
 *         an error code if the schedule has overlaps
 */
static SBResult SlimBus_VerifyChannelSchedule
(
  SlimBusDevCtxt *pDevCtxt,
  uint32 uCtrlWidth,
  uint32 uSubFrmLen
)
{
  SlimBusChannelParamType *pParam = NULL;
  SlimBusLinkNodeType *pList, *pNextList;
  uint32 uSlotStartNum, uSlotNum;
  
  /* First zero-out the slot array */
  memset(pDevCtxt->pSched->aSlotArr, 0, SB_SLOTS_PER_SUPERFRAME);
  
  /* Mark all the slots belonging to the message channel as used */
  for ( uSlotStartNum = 0; uSlotStartNum < SB_SLOTS_PER_SUPERFRAME; uSlotStartNum += uSubFrmLen )
  {
    for ( uSlotNum = uSlotStartNum; 
          (uSlotNum < uSlotStartNum+uCtrlWidth) &&
          (uSlotNum < SB_SLOTS_PER_SUPERFRAME);
          uSlotNum++ )
    {
      pDevCtxt->pSched->aSlotArr[uSlotNum] = 1;
    }
  }
  
  pList = &pDevCtxt->pSched->ChanParamList1;
  pNextList = &pDevCtxt->pSched->ChanParamList3;
  /* For all the data channels, mark their slots as used, and verify
     that none of the slots that would be used by the data channels
     have already been used */
  for ( ; pList != NULL; pList = pNextList, pNextList = NULL )
  {
    pParam = NULL;
    while (NULL != (pParam = NextParamNode(pList, pParam)) )
    {
      if (pParam->eStatus != SB_CHANNEL_PENDING_REMOVAL)
      {
        for ( uSlotStartNum = pParam->uNewOffset; 
              uSlotStartNum < SB_SLOTS_PER_SUPERFRAME;
              uSlotStartNum += pParam->uNewInterval )
        {
          for ( uSlotNum = uSlotStartNum;
                (uSlotNum < uSlotStartNum+pParam->ucSegLen) && 
                (uSlotNum < SB_SLOTS_PER_SUPERFRAME); 
                uSlotNum++)
          {
            if (pDevCtxt->pSched->aSlotArr[uSlotNum] != 0)
            {
              return SB_ERROR;
            }
            pDevCtxt->pSched->aSlotArr[uSlotNum] = 1;
          }
        }
      }
    }
  }

  /* If we've gotten here then we've verified there are no channel overlaps */
  return SB_SUCCESS;
}

/**
 * @brief Outer loop for performing data channel bandwidth 
 *        allocation
 *
 * This function implements the outer loop for performing data 
 * channel bandwidth allocation 
 * 
 * @param[in] pDevCtxt  Pointer to the device context
 * @param[out] puSubFrmCode  Location to store the scheduled 
 *       subframe code
 * @param[in,out] puClkGear  Location to receive the minimum
 *       clock gear and store the scheduled clock gear
 * 
 * @return SB_SUCCESS if bandwidth allocation was performed 
 *         sucessfully, or and error code if there an allocation
 *         error 
 */
SBResult SlimBus_DoBandwidthAlloc
(
  SlimBusDevCtxt *pDevCtxt,
  uint32 *puSubFrmCode,
  uint32 *puClkGear
)
{
  uint32 uMsgSlots = 0;
  uint32 uCtrlWidth = 0;
  uint32 uSubFrmLen = 0;
  SBResult result = SB_ERROR;
  uint32 uMinClkGear;
  
  uint32 uSlotsUsed = pDevCtxt->pSched->uSlotsUsed + pDevCtxt->pSched->uMsgSlotReq;

  /* Subtract frame channel and guide channel from available slots */
  uint32 uSlotsAvail =
    SB_SLOTS_PER_SUPERFRAME -
    SB_FRAME_SLOTS_PER_SUPERFRAME -
    SB_GUIDE_SLOTS_PER_SUPERFRAME;
  uMinClkGear = *puClkGear;
  *puClkGear = SB_MAX_CLK_GEAR;
  
  /* Keep decreasing the clock gear as long as the number of used slots is
     less than the number of available slots */
  while ( uSlotsUsed*2 <= uSlotsAvail &&
          *puClkGear > 1 &&
          *puClkGear > uMinClkGear )
  {
    (*puClkGear)--;
    uSlotsUsed *= 2;
  }

  /* Try to schedule the data channels at the current clock gear, if we
     we're able to schedule all the channels at the current clock gear, or
     if we don't satisfy the reserved messaging bandwidth after scheduling
     the data channels, increase the clock gear and try again */
  for( ; *puClkGear <= SB_MAX_CLK_GEAR; (*puClkGear)++ )
  {
    result = SlimBus_DoScheduleChannels(pDevCtxt, *puClkGear, 
                                        &uCtrlWidth, &uSubFrmLen);
    if (SB_SUCCESS == result)
    {
      *puSubFrmCode = GetSubFrameCoding(&uCtrlWidth, &uSubFrmLen, &uMsgSlots);

      if ( uMsgSlots>>(SB_MAX_CLK_GEAR-*puClkGear) < pDevCtxt->pSched->uMsgSlotReq &&
           *puClkGear < SB_MAX_CLK_GEAR )
      {
        continue;
      }
      else
      {
        /* If we are already at the max clock gear but haven't satisfied our
           reserved messaging bandwidth, then we've done the best effort and 
           we have to stop and go with what we have */
        break;
      }
    }
  }

  if (SB_SUCCESS == result)
  {
    result = SlimBus_VerifyChannelSchedule(pDevCtxt, uCtrlWidth, uSubFrmLen);
  }
  
  return result;
}

