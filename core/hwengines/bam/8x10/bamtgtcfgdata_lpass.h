#ifndef BAMTGTCFGDATA_LPASS_H_
#define BAMTGTCFGDATA_LPASS_H_

/**
  @file bamtgtcfgdata_lpass.h
  @brief
  This file contains configuration data for the BAM driver for the 
  8974 lpass system.

*/
/*
===============================================================================

                             Edit History

 $Header: //components/rel/core.adsp/2.6.1/hwengines/bam/8x10/bamtgtcfgdata_lpass.h#1 $

when       who     what, where, why
--------   ---     ------------------------------------------------------------
01/23/13   SS      Brached from 8974

===============================================================================
                   Copyright (c) 2012-2013 QUALCOMM Technologies Inc.
                          All Rights Reserved.
                        Qualcomm Confidential and Proprietary.
===============================================================================
*/

/** Configs supported for
    BLSP1
    NDP-Crypto1
    BAM_TGT_CFG_LAST
   */

#define BAM_CNFG_BITS_VAL 0x7FFFF004

const bam_target_config_type  bam_tgt_config[] = {
    { // BLSP1_BAM
        0xf9904000, // PERIPH_SS_PERIPH_SS_BASE_PHYS+0x00100000+0x4000
        BAM_TGT_CFG_SHARABLE, // BAM CFG OPTIONS
        BAM_CNFG_BITS_VAL,         // default chicken bits
        1,   // EE index
        NULL // Security Config
    },
    { //NDP CRYPTO1
        0xFD404000, // CRYPTO1_TOP_BASE + 0x00004000
        0, // No BAM_CFG options
        BAM_CNFG_BITS_VAL,         // default chicken bits
        0,    // EE index
        NULL  // Security Config
    },
    { //dummy config
        BAM_TGT_CFG_LAST,
        0,
        0,
        1,
        NULL
    },
};
#endif /* #define BAMTGTCFGDATA_LPASS_H_*/

