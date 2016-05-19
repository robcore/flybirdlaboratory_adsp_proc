/**
  @file bamtgtcfgdata_lpass.h
  @brief
  This file contains configuration data for the BAM driver for the 
  8974 lpass system.

*/
/*
===============================================================================

                             Edit History

 $Header: //components/rel/core.adsp/2.6.1/hwengines/bam/8994/bamtgtcfgdata_lpass.h#1 $

when       who     what, where, why
--------   ---     ------------------------------------------------------------
12/04/12   SS      Added BAM_TGT_CFG_LAST as Dummy config
07/02/12   SS      Added Crypto1 and Crypto2
03/20/12   MK      Created

===============================================================================
                   Copyright (c) 2012 Qualcomm Technologies Incorporated.
                          All Rights Reserved.
                        Qualcomm Confidential and Proprietary.
===============================================================================
*/

/** Configs supported for
    BAMDMA
    BLSP1
    BLSP2
    LPASS Slimbus BAM-Lite
    NDP-Crypto1
    NDP-Crypto2
    BAM_TGT_CFG_LAST
   */

#define BAM_CNFG_BITS_VAL 0x7FFFF004

const bam_target_config_type  bam_tgt_config[] = {
    { //BAMDMA
        0xf9984000, // PERIPH_SS_PERIPH_SS_BASE_PHYS+0x00180000+0x4000
        0, // No BAM_CFG options
        BAM_CNFG_BITS_VAL,         // default chicken bits
        1,    // EE index
        NULL  // Security Config
    },
    { // BLSP1_BAM
        0xf9904000, // PERIPH_SS_PERIPH_SS_BASE_PHYS+0x00100000+0x4000
        BAM_TGT_CFG_SHARABLE, // BAM CFG OPTIONS
        BAM_CNFG_BITS_VAL,         // default chicken bits
        1,   // EE index
        NULL // Security Config
    },
    { // BLSP2_BAM
        0xf9944000, // PERIPH_SS_PERIPH_SS_BASE_PHYS+0x00140000+0x4000
        BAM_TGT_CFG_SHARABLE, // BAM CFG OPTIONS
        BAM_CNFG_BITS_VAL,         // default chicken bits
        1,   // EE index
        NULL // Security Config
    },
    { // LPASS_BAM_LITE
        0xfe104000, // LPASS_LPASS_BASE_PHYS+0x00100000+0x4000
        0x0, // EE 0 (LPASS) initializes Slimbus
        BAM_CNFG_BITS_VAL,         // default chicken bits
        0,   // EE index (lpass)
        NULL // Security Config
    },
    { // LPASS_BAM_LITE
        0xfe184000, // LPASS_LPASS_BASE_PHYS+0x00100000+0x4000
        0x0, // EE 0 (LPASS) initializes Slimbus
        BAM_CNFG_BITS_VAL,         // default chicken bits
        0,   // EE index (lpass)
        NULL // Security Config
    },
    { //NDP CRYPTO1
        0xFD404000, // CRYPTO1_TOP_BASE + 0x00004000
        0, // No BAM_CFG options
        BAM_CNFG_BITS_VAL,         // default chicken bits
        0,    // EE index
        NULL  // Security Config
    },
    { //NDP CRYPTO2
        0xFD444000, // CRYPTO2_TOP_BASE + 0x00004000
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


