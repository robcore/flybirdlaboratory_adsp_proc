/*
* Copyright (c) 2013-2015 Qualcomm Technologies, Inc.
* All Rights Reserved.
* Qualcomm Technologies, Inc. Confidential and Proprietary.
*/

/*
 * hal_sleep.c
 *
 *  Created on: Feb 13, 2012
 *      Author: yrusakov
 */

#include "adsppm.h"
#include "adsppm_utils.h"
#include "hal_sleep.h"
#include "npa.h"


#define SLEEP_LATENCY_NODE_NAME "/core/cpu/latency/usec"
#define USLEEP_NODE_NAME "/core/uSleep"
#define USLEEP_ALLOW 1
#define USLEEP_DISALLOW 0

typedef struct
{
    DALSYSSyncHandle  lock;
    boolean           initSuccess;
    npa_client_handle latencyNpaHandle;
    boolean           uSleepNodeAvailable;
    npa_client_handle uSleepNpaHandle;
} sleepDriverInfoType;

static sleepDriverInfoType gSleepDriverInfo;

static void NpaLatencyAvailableCb(
    void *context,
    unsigned int event_type,
    void *data,
    unsigned int data_size);

static void NpaUSleepAvailableCb(
    void *context,
    unsigned int event_type,
    void *data,
    unsigned int data_size);


AdsppmStatusType Slp_Init(void)
{
    AdsppmStatusType sts = Adsppm_Status_Success;
    ADSPPM_LOG_FUNC_ENTER;
    ADSPPM_LOG_FUNC_PROFILESTART;
    gSleepDriverInfo.initSuccess = FALSE;
    gSleepDriverInfo.uSleepNodeAvailable = FALSE;
    if(DAL_SUCCESS != DALSYS_SyncCreate(
        DALSYS_SYNC_ATTR_RESOURCE,
        (DALSYSSyncHandle *)&gSleepDriverInfo.lock,
        NULL))
    {
        sts = Adsppm_Status_Failed;
    }
    else
    {
        // Register for sleep latency NPA node availability notice
        npa_resource_available_cb(
            SLEEP_LATENCY_NODE_NAME, NpaLatencyAvailableCb, NULL);
        // Register for uSleep NPA node availability notice
        npa_resource_available_cb(
            USLEEP_NODE_NAME, NpaUSleepAvailableCb, NULL);
    }
    ADSPPM_LOG_FUNC_PROFILEEND;
    ADSPPM_LOG_FUNC_EXIT(sts);
    return sts;
}


static void NpaLatencyAvailableCb(
    void *context,
    unsigned int event_type,
    void *data,
    unsigned int data_size)
{
    ADSPPM_LOG_FUNC_ENTER;
    ADSPPM_LOG_FUNC_PROFILESTART;
    gSleepDriverInfo.latencyNpaHandle = npa_create_sync_client(
        SLEEP_LATENCY_NODE_NAME,
        "Adsppm_latency",
        NPA_CLIENT_REQUIRED);
    if(NULL != gSleepDriverInfo.latencyNpaHandle)
    {
        gSleepDriverInfo.initSuccess = TRUE;
    }
    ADSPPM_LOG_FUNC_PROFILEEND;
    ADSPPM_LOG_FUNC_EXIT(gSleepDriverInfo.initSuccess);
}


AdsppmStatusType Slp_RequestLatency(uint32 latency)
{
    AdsppmStatusType sts = Adsppm_Status_Success;
    ADSPPM_LOG_FUNC_ENTER;
    ADSPPM_LOG_FUNC_PROFILESTART;
    if(FALSE == gSleepDriverInfo.initSuccess)
    {
        sts = Adsppm_Status_NotInitialized;
    }
    else
    {
        adsppm_lock(gSleepDriverInfo.lock);
        if(HAL_SLEEP_LATENCY_DONT_CARE == latency)
        {
            ADSPPM_LOG_PRINTF_1(ADSPPM_LOG_LEVEL_INFO,
                "Complete NPA request for %s",
                SLEEP_LATENCY_NODE_NAME);
            npa_complete_request(gSleepDriverInfo.latencyNpaHandle);
        }
        else
        {
            ADSPPM_LOG_PRINTF_2(ADSPPM_LOG_LEVEL_INFO,
                "NPA request for %s, latency: %d",
                SLEEP_LATENCY_NODE_NAME, latency);
            npa_issue_required_request(
                gSleepDriverInfo.latencyNpaHandle, latency);
        }
        adsppm_unlock(gSleepDriverInfo.lock);
    }
    ADSPPM_LOG_FUNC_PROFILEEND;
    ADSPPM_LOG_FUNC_EXIT(sts);
    return sts;
}


AdsppmStatusType Slp_ReleaseLatency()
{
    AdsppmStatusType sts = Adsppm_Status_Success;
    ADSPPM_LOG_FUNC_ENTER;
    ADSPPM_LOG_FUNC_PROFILESTART;
    if(FALSE == gSleepDriverInfo.initSuccess)
    {
        sts = Adsppm_Status_NotInitialized;
    }
    else
    {
        adsppm_lock(gSleepDriverInfo.lock);
        ADSPPM_LOG_PRINTF_1(ADSPPM_LOG_LEVEL_INFO,
            "Complete NPA request for %s",
            SLEEP_LATENCY_NODE_NAME);
        npa_complete_request(gSleepDriverInfo.latencyNpaHandle);
        adsppm_unlock(gSleepDriverInfo.lock);
    }
    ADSPPM_LOG_FUNC_PROFILEEND;
    ADSPPM_LOG_FUNC_EXIT(sts);
    return sts;
}


static void NpaUSleepAvailableCb(
    void *context,
    unsigned int event_type,
    void *data,
    unsigned int data_size)
{
    ADSPPM_LOG_FUNC_ENTER;
    ADSPPM_LOG_FUNC_PROFILESTART;
    gSleepDriverInfo.uSleepNpaHandle = npa_create_sync_client(
        USLEEP_NODE_NAME,
        "Adsppm_uSleep",
        NPA_CLIENT_REQUIRED);
    if(NULL == gSleepDriverInfo.uSleepNpaHandle)
    {
        ADSPPM_LOG_PRINTF_1(ADSPPM_LOG_LEVEL_ERROR,
            "Failed to create NPA client for %s", USLEEP_NODE_NAME);
    }
    else
    {
        gSleepDriverInfo.uSleepNodeAvailable = TRUE;
    }
    ADSPPM_LOG_FUNC_PROFILEEND;
    ADSPPM_LOG_FUNC_EXIT(0);
}


boolean Slp_IsUSleepNpaAvailable(void)
{
    boolean sts = FALSE;
    ADSPPM_LOG_FUNC_ENTER;
    ADSPPM_LOG_FUNC_PROFILESTART;
    if(gSleepDriverInfo.initSuccess == TRUE)
    {
        adsppm_lock(gSleepDriverInfo.lock);
        if(gSleepDriverInfo.uSleepNodeAvailable)
        {
            sts = TRUE;
        }
        adsppm_unlock(gSleepDriverInfo.lock);
    }
    ADSPPM_LOG_FUNC_PROFILEEND;
    ADSPPM_LOG_FUNC_EXIT(sts);
    return sts;
}


AdsppmStatusType Slp_AllowUSleep(void)
{
    AdsppmStatusType sts = Adsppm_Status_Success;
    ADSPPM_LOG_FUNC_ENTER;
    ADSPPM_LOG_FUNC_PROFILESTART;
    if(gSleepDriverInfo.initSuccess == FALSE)
    {
        sts = Adsppm_Status_NotInitialized;
    }
    else
    {
        adsppm_lock(gSleepDriverInfo.lock);
        if(gSleepDriverInfo.uSleepNodeAvailable)
        {
            ADSPPM_LOG_PRINTF_0(ADSPPM_LOG_LEVEL_INFO,
                "NPA request to allow uSleep");
            npa_issue_required_request(
                gSleepDriverInfo.uSleepNpaHandle, USLEEP_ALLOW);
        }
        adsppm_unlock(gSleepDriverInfo.lock);
    }
    ADSPPM_LOG_FUNC_PROFILEEND;
    ADSPPM_LOG_FUNC_EXIT(sts);
    return sts;
}


AdsppmStatusType Slp_DisallowUSleep(void)
{
    AdsppmStatusType sts = Adsppm_Status_Success;
    ADSPPM_LOG_FUNC_ENTER;
    ADSPPM_LOG_FUNC_PROFILESTART;
    if(gSleepDriverInfo.initSuccess == FALSE)
    {
        sts = Adsppm_Status_NotInitialized;
    }
    else
    {
        adsppm_lock(gSleepDriverInfo.lock);
        if(gSleepDriverInfo.uSleepNodeAvailable)
        {
            ADSPPM_LOG_PRINTF_0(ADSPPM_LOG_LEVEL_INFO,
                "NPA request to disallow uSleep");
            npa_issue_required_request(
                gSleepDriverInfo.uSleepNpaHandle, USLEEP_DISALLOW);
        }
        adsppm_unlock(gSleepDriverInfo.lock);
    }
    ADSPPM_LOG_FUNC_PROFILEEND;
    ADSPPM_LOG_FUNC_EXIT(sts);
    return sts;
}

