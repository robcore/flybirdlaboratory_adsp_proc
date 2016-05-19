/*
* Copyright (c) 2013-2015 Qualcomm Technologies, Inc.
* All Rights Reserved.
* Qualcomm Technologies, Inc. Confidential and Proprietary.
*/

/*
 * usleepmgr.c
 *
 *  Created on: Jan 30, 2015
 *      Author: ltayleon
 */

#include "adsppm.h"
#include "adsppm_utils.h"
#include "usleepmgr.h"
#include "hal_sleep.h"


typedef enum
{
    USleepMgr_Disallow = 0,
    USleepMgr_Allow
} USleepMgr_VoteType;

typedef struct
{
    DALSYSSyncHandle   lock;
    boolean            npaNodeAvailable;
    USleepMgr_VoteType currentAggrVote[2];
    USleepMgr_VoteType votes[USleepMgr_VoterId_Max - 1];
    uint32             activeStateIndex;
} usleepMgrCtxType;

static usleepMgrCtxType gUSleepMgrCtx;


Adsppm_Status USleepMgr_Init(void)
{
    Adsppm_Status result = Adsppm_Status_Success;
    uint32 i = 0;
    ADSPPM_LOG_FUNC_ENTER;

    // Initialize context
    gUSleepMgrCtx.npaNodeAvailable = Slp_IsUSleepNpaAvailable();
    gUSleepMgrCtx.currentAggrVote[0] = USleepMgr_Allow;
    gUSleepMgrCtx.currentAggrVote[1] = USleepMgr_Allow;
    gUSleepMgrCtx.activeStateIndex = 0;
    for(i = 0; i < (USleepMgr_VoterId_Max - 1); i++)
    {
        gUSleepMgrCtx.votes[i] = USleepMgr_Allow;
    }

    // Initialize lock
    if(DAL_SUCCESS != DALSYS_SyncCreate(
        DALSYS_SYNC_ATTR_RESOURCE,
        &gUSleepMgrCtx.lock,
        NULL))
    {
        ADSPPM_LOG_PRINTF_0(ADSPPM_LOG_LEVEL_ERROR,
            "Failed to create lock");
        result = Adsppm_Status_Failed;
    }
    else
    {
        // Place initial vote to disallow uSleep
        // instead of allow
        // since it messes up with Sensors initialization
        // This will be corrected at the first DDR BW request
        // TODO: Find a better way to handle this syncronization
        adsppm_lock(gUSleepMgrCtx.lock);
        if(gUSleepMgrCtx.npaNodeAvailable)
        {
            result = Slp_DisallowUSleep();
        }
        adsppm_unlock(gUSleepMgrCtx.lock);
    }

    ADSPPM_LOG_FUNC_EXIT(result);
    return result;
}


static Adsppm_Status usleepmgr_updateUSleepVote(void)
{
    Adsppm_Status sts = Adsppm_Status_Success;
    uint32 i = 0;
    USleepMgr_VoteType *pCurrentAggrVote = NULL;
    USleepMgr_VoteType *pPreviousAggrVote = NULL;

    // Initialize parameters
    pCurrentAggrVote =
        &gUSleepMgrCtx.currentAggrVote[gUSleepMgrCtx.activeStateIndex];
    pPreviousAggrVote =
        &gUSleepMgrCtx.currentAggrVote[gUSleepMgrCtx.activeStateIndex^1];
    *pCurrentAggrVote = USleepMgr_Allow;

    // Aggregate all votes
    for(i = 0; i < (USleepMgr_VoterId_Max - 1); i++)
    {
        *pCurrentAggrVote = MIN(*pCurrentAggrVote, gUSleepMgrCtx.votes[i]);
    }

    // Issue vote if needed
    if(*pCurrentAggrVote != *pPreviousAggrVote)
    {
        (*pCurrentAggrVote == USleepMgr_Disallow)?
        (sts = Slp_DisallowUSleep()):
        (sts = Slp_AllowUSleep());
    }

    // Update the index for next iteration
    gUSleepMgrCtx.activeStateIndex ^= 1;

    return sts;
}


Adsppm_Status USleepMgr_ProcessRequest(
    USleepMgr_VoterIdType voterId,
    uint64 ddrAb)
{
    Adsppm_Status sts = Adsppm_Status_Success;
    USleepMgr_VoteType previousVotersVote = USleepMgr_Allow;
    USleepMgr_VoteType currentVotersVote = USleepMgr_Allow;
    ADSPPM_LOG_FUNC_ENTER;
    ADSPPM_LOG_FUNC_PROFILESTART;

    if(gUSleepMgrCtx.lock == NULL)
    {
        ADSPPM_LOG_PRINTF_0(ADSPPM_LOG_LEVEL_ERROR,
            "Not initialized");
        sts = Adsppm_Status_NotInitialized;
    }
    else
    {
        adsppm_lock(gUSleepMgrCtx.lock);

        if(gUSleepMgrCtx.npaNodeAvailable)
        {
            if((voterId == USleepMgr_VoterId_None) ||
                (voterId >= USleepMgr_VoterId_Max))
            {
                ADSPPM_LOG_PRINTF_1(ADSPPM_LOG_LEVEL_ERROR,
                    "Invalid uSleep voter ID: %u", voterId);
                sts = Adsppm_Status_BadParm;
            }
            else
            {
                ADSPPM_LOG_PRINTF_2(ADSPPM_LOG_LEVEL_INFO_EXT,
                    "Voter %u: total DDR BW: %u",
                    voterId, ddrAb);

                // Update vote for current voter
                previousVotersVote = gUSleepMgrCtx.votes[voterId - 1];
                currentVotersVote =
                    (ddrAb == 0)?USleepMgr_Allow:USleepMgr_Disallow;

                // Only proceed if current voter's vote changed 
                if(previousVotersVote != currentVotersVote)
                {
                    ADSPPM_LOG_PRINTF_2(ADSPPM_LOG_LEVEL_INFO,
                        "Voter %u updated its uSleep vote to %u",
                        voterId, currentVotersVote);

                    gUSleepMgrCtx.votes[voterId - 1] = currentVotersVote;
                    sts = usleepmgr_updateUSleepVote();
                }
            }
        }

        adsppm_unlock(gUSleepMgrCtx.lock);
    }

    ADSPPM_LOG_FUNC_PROFILEEND;
    ADSPPM_LOG_FUNC_EXIT(sts);
    return sts;
}

