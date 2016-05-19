/*============================================================================
FILE:         uimage_rpm.c

OVERVIEW:     This file provides the master rpm driver functionality for the
uImage on ADSP.

DEPENDENCIES: 

===========================================================================
Copyright (c) 2013 - 2014 QUALCOMM Technologies Incorporated.
All Rights Reserved.
Qualcomm Confidential and Proprietary
=============================================================================
$Header: //components/rel/core.adsp/2.6.1/power/uimage_rpm/src/uimage_rpm.c#4 $
$DateTime: 2015/01/29 19:03:23 $
=============================================================================*/
#include "uimage_rpm.h"
#include "uimage_rpm_smd.h"
#include "uimage_rpm_resource_data.h"
#include "uimage_rpm_assert.h"
#include "uimage_rpm_log.h"
#include "uSleep.h"
#include "busywait.h"

/*******************************************************************************
 *
 * uImage_rpm_set_clk_values
 *
 */
void uImage_rpm_set_clk_values(uint32 snoc_freq_khz,
                               uint32 bimc_freq_khz,
                               uImage_rpm_wait_mode_t wait_mode)
{
    uint32 i;
    uint8  ddrOn = (0 == bimc_freq_khz) ? FALSE : TRUE;
    /*
     * Use 1 and 2 for DDR-OFF request message IDs and
     * use 3 and 4 for DDR-ON request message IDs
     * in order to avoid processing DDR-OFF ACKs as DDR-ON ACKs
     *
     * This issue was observed during bringup when ADSP got an DDR interrupt
     * and woke up immediately after sending DDR-OFF request
     */
    uint32 msg_id_offset = (TRUE == ddrOn) ? 3 : 1;

    UIMAGE_RPM_LOG(4, "set_clk_values (snoc:%d) (bimc:%d) (wait:%d) (ddrOn:%d)",
                   snoc_freq_khz, bimc_freq_khz, wait_mode, ddrOn);

    /*
     * Clear out existing ACKs if waiting for ACKs for this requests.
     */
    if(wait_mode != UIMAGE_RPM_NO_WAIT_MODE)
    {
        UIMAGE_RPM_LOG(0, "clear_acks", NULL);

        while(TRUE == uImage_rpm_readAck(0, TRUE));

        UIMAGE_RPM_LOG(0, "clear_acks_done", NULL);
    }

    uImage_rpm_ddr_resource_data.resources[0].resource_value = snoc_freq_khz;
    uImage_rpm_ddr_resource_data.resources[1].resource_value = bimc_freq_khz;

    /*
     * send resource requests to RPM
     */
    for(i = 0; i < uImage_rpm_ddr_resource_data.num_resources; i++)
    {
        uImage_rpm_sendMessage(i+msg_id_offset, &uImage_rpm_ddr_resource_data.resources[i]);
    }

    /*
     * receive Acks from RPM
     */
    switch(wait_mode)
    {
        case UIMAGE_RPM_NO_WAIT_MODE:
            /*
             * don't wait for ACKs
             */
            break;

        case UIMAGE_RPM_BUSY_WAIT_MODE:
            UIMAGE_RPM_LOG(0, "wait_for_acks (%d, %d)", msg_id_offset, msg_id_offset+1);

            /*
             * wait until receiving ACKs for requests
             */
            for(i = 0; i < uImage_rpm_ddr_resource_data.num_resources; i++)
            {
                while(FALSE == uImage_rpm_readAck(i+msg_id_offset, FALSE));
            }

            /*
             * put in a wait for DDR to warm up
             */
            if(ddrOn==TRUE)
            {
                busywait(700);
            }

            UIMAGE_RPM_LOG(0, "wait_for_acks_done", NULL);
            break;

        default:
            UIMAGE_RPM_ASSERT(0, "invalid wait mode");
    }

    UIMAGE_RPM_LOG(0, "set_clk_values_done", NULL);

    /* Only notify sleep that transition is done. This needs to moved to
     * the point of actual completion when optimizations are implemented. */
    uSleep_notifyDDRTransitionComplete(ddrOn);
}

/*******************************************************************************
 *
 * uImage_rpm_init
 *
 */
void uImage_rpm_init(void)
{
    uImage_rpm_log_init();
    uImage_rpm_smd_init();

    UIMAGE_RPM_LOG(0, "init_all_done", NULL);
}

