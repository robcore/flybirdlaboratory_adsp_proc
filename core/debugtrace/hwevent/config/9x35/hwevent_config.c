/*=============================================================================

FILE:         hwevent_config.c

DESCRIPTION:    This file has chip specific HW Event configuration

================================================================================
            Copyright (c) 2013 Qualcomm Technologies, Inc.
                         All Rights Reserved.
          Qualcomm Technologies Proprietary and Confidential
==============================================================================*/

/*===========================================================================

                      EDIT HISTORY FOR FILE

This section contains comments describing changes made to this file.
Notice that changes are listed in reverse chronological order.

$Header: //components/rel/core.adsp/2.6.1/debugtrace/hwevent/config/9x35/hwevent_config.c#1 $

when       who     what, where, why
--------   ---     ----------------------------------------------------------
2/7/2011   prasads  First draft created.
===========================================================================*/
#include "com_dtypes.h"

typedef struct HWEventRegisterValue_t HWEventRegisterValue;
typedef struct HWEventAddrRange_t HWEventAddrRange;

/*
This structure defines the topology of a funnel configuration.
*/
struct HWEventRegisterValue_t{
   uint32 reg_phys_addr;
   uint32 reg_value;
};

struct HWEventAddrRange_t
{
   uint32 lower_range;
   uint32 higher_range;
   uint32 unlock_value;
};

typedef struct HWEventTableSize_t HWEventTableSize;
struct HWEventTableSize_t {
   uint32 size;
};


const HWEventRegisterValue hwevent_config_table[]={
   {NULL,NULL} /*indicates end of table*/
};


#ifndef HWEVENT_CONFIG_TABLE_SIZE
#define HWEVENT_CONFIG_TABLE_SIZE sizeof(hwevent_config_table)/sizeof(HWEventRegisterValue)
#endif


const HWEventTableSize table_size_array[]={
   {HWEVENT_CONFIG_TABLE_SIZE},
};

const HWEventAddrRange hwevent_addr_table[]={
   {0xfe027000,0xfe027000,0x0},//HWIO_LPASS_AUDIO_WRAPPER_STM_XO_CBCR_ADDR
   {0xFE20200C,0xFE20200C,0x0},//HWIO_LPASS_QDSP6SS_PWRDBG_CTL_ADDR
   {0xFE03E000,0xFE03E07C,0x0},//HWIO_LPASS_STM_MUXSEL_n_ADDR
   {NULL,NULL,NULL}
};

#define HWEVENT_ADDR_RANGE_TABLE_SIZE  sizeof(hwevent_addr_table)/sizeof(HWEventAddrRange)


const HWEventTableSize addr_range_table_size[]={
   {HWEVENT_ADDR_RANGE_TABLE_SIZE}
};

