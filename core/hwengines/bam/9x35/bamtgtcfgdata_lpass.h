/**
  @file bamtgtcfgdata_lpass.h
  @brief
  This file contains configuration data for the BAM driver for the 
  9x35 lpass system.

*/
/*
===============================================================================

                             Edit History

 $Header: //components/rel/core.adsp/2.6.1/hwengines/bam/9x35/bamtgtcfgdata_lpass.h#1 $

when       who     what, where, why
--------   ---     ------------------------------------------------------------
04/24/13   rl      branched from 9x25

===============================================================================
                   Copyright (c) 2013 Qualcomm Technologies Incorporated.
                          All Rights Reserved.
                        Qualcomm Confidential and Proprietary.
===============================================================================
*/

/** Configs supported for
    BAMDMA
    BLSP1
    SLIMBUS
    BAM_TGT_CFG_LAST
 */

#define BAM_CNFG_BITS_VAL 0x7FFFF004
 
const bam_target_config_type  bam_tgt_config[] = {
        {   //BAMDMA
            0xf9984000,         // COPSS_ELAN+0x00184000
            0,                  // BAM_CFG options
            BAM_CNFG_BITS_VAL,  // default chicken bits
            1,                  // EE index        
            NULL                // Security Config 
        },
        {   //BLSP1_BAM
            0xf9904000,           // COPSS_ELAN+0x00104000
            BAM_TGT_CFG_SHARABLE, // BAM CFG OPTIONS 
            BAM_CNFG_BITS_VAL,    // default chicken bits
            1,                    // EE index
            NULL                  // Security Config
        },
        {   //SLIMBUS_BAM_LITE
            0xfe184000,           // LPASS+0x00104000
            0x0,                  // BAM CFG OPTIONS 
            BAM_CNFG_BITS_VAL,    // default chicken bits
            0,                    // EE index
            NULL                  // Security Config
        },
        {   // LAST
            BAM_TGT_CFG_LAST,
            0,
            0,
            0,
            NULL
        },
};



