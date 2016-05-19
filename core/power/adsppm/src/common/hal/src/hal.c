/*
* Copyright (c) 2013-2015 Qualcomm Technologies, Inc.
* All Rights Reserved.
* Qualcomm Technologies, Inc. Confidential and Proprietary.
*/

/*
 * hal.c
 *
 *  Created on: Feb 13, 2012
 *      Author: yrusakov
 */

#include "adsppm.h"
#include "adsppm_utils.h"
#include "hal_interrupt.h"
#include "hal_clkrgm.h"
#include "hal_busdrv.h"
#include "hal_sleep.h"
#include "hal_debug.h"
#include "hal_regengine.h"


extern uint32 gADSPPMINITSTATE;


Adsppm_Status Hal_Init(void)
{
    Adsppm_Status result;
    ADSPPM_LOG_FUNC_ENTER;
    ADSPPM_LOG_FUNC_PROFILESTART;
    result = Intr_Init();
    if(Adsppm_Status_Success == result)
    {
        gADSPPMINITSTATE |= Adspmm_State_HalIntrInit;
        result = ClkRgm_Init();
        if(Adsppm_Status_Success == result)
        {
            gADSPPMINITSTATE |= Adsppm_State_HalClkRgmInit;
            result = Bus_Init();
            if(Adsppm_Status_Success == result)
            {
                gADSPPMINITSTATE |= Adsppm_State_HalBusInit;
                result = Slp_Init();
                if(Adsppm_Status_Success == result)
                {
                    gADSPPMINITSTATE |= Adsppm_State_HalSlpInit;
                }
            }
        }
    }
    ADSPPM_LOG_FUNC_PROFILEEND;
    ADSPPM_LOG_FUNC_EXIT(result);
    return result;
}

