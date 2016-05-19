/**
  @file bamtgtcfgdata_lpass.h
  @brief
  This file contains configuration data for the BAM driver for the 
  8974 lpass system.

*/
/*
===============================================================================

                             Edit History

 $Header: //components/rel/core.adsp/2.6.1/hwengines/bam/8084/bamtgtcfgdata_lpass.h#1 $

when       who     what, where, why
--------   ---     ------------------------------------------------------------
03/25/12   rl      branched from 8974 

===============================================================================
                   Copyright (c) 2013 QUALCOMM Technologies Incorporated.
                          All Rights Reserved.
                        Qualcomm Confidential and Proprietary.
===============================================================================
*/

/** Configs supported for
    BAMDMA
    BLSP1
    BLSP2
    LPASS Slimbus BAM-Lite
    BAM_TGT_CFG_LAST
   */

#define BAM_CNFG_BITS_VAL 0x7FFFF004

const bam_target_config_type  bam_tgt_config[] = {
    {   //BAMDMA : PERIPH_SS_BASE_PHYS+0x00180000+0x4000
        0xf9984000,
        BAM_TGT_CFG_SHARABLE,
        BAM_CNFG_BITS_VAL,         // default chicken bits
        1,
        NULL
    },
    {   //BLSP1_BAM : PERIPH_SS_PERIPH_SS_BASE_PHYS+0x00100000+0x4000
        0xf9904000,
        BAM_TGT_CFG_SHARABLE,
        BAM_CNFG_BITS_VAL,         // default chicken bits
        1,
        NULL
    },
    {   //BLSP2_BAM : PERIPH_SS_PERIPH_SS_BASE_PHYS+0x00140000+0x4000
        0xf9944000,
        BAM_TGT_CFG_SHARABLE,
        BAM_CNFG_BITS_VAL,         // default chicken bits
        1,
        NULL
    },
    {   //SLIMBUS_BAM : LPASS+0x00104000
        0xfe184000,
        0x0,
        BAM_CNFG_BITS_VAL,         // default chicken bits
        0,
        NULL
    },
    { //dummy config
        BAM_TGT_CFG_LAST,
        0,
        0,
        0,
        NULL
    },
};


