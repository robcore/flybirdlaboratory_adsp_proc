/*=============================================================================

FILE:         tfunnel_config.c

DESCRIPTION:  
  This file has port configurations for trace funnels for a given chipset.
================================================================================
            Copyright (c) 2013 Qualcomm Technologies, Inc.
                         All Rights Reserved.
          Qualcomm Technologies Proprietary and Confidential
==============================================================================*/
/*===========================================================================

                      EDIT HISTORY FOR FILE

This section contains comments describing changes made to this file.
Notice that changes are listed in reverse chronological order.

$Header: //components/rel/core.adsp/2.6.1/debugtrace/tfunnel/config/9x35/tfunnel_config.c#1 $

when       who     what, where, why
--------   ---     ----------------------------------------------------------
2/7/2011   prasads  First draft created. 
===========================================================================*/
#include "com_dtypes.h"

#define IN_FUN0  0
#define IN_FUN1  1
#define MERG_FUN 2

typedef struct TypeTFunnelPortEnableConfig TFunnelPortEnableConfig;

/*
This structure defines the topology of a funnel configuration.
*/
struct TypeTFunnelPortEnableConfig{
   uint32 funnel_id;
   uint32 port_id;
   TFunnelPortEnableConfig *pFunnelConfig;
};

/*
Define supported funnel configurations.
*/
static TFunnelPortEnableConfig tfunnel_merge_port0[]={
   {MERG_FUN,0,NULL}
};

static TFunnelPortEnableConfig tfunnel_merge_port1[]={
{MERG_FUN,1,NULL}
};



TFunnelPortEnableConfig tfunnel_port_rpm[]={
   {IN_FUN0,0,tfunnel_merge_port0}
};

TFunnelPortEnableConfig tfunnel_port_mpss[]={
   {IN_FUN0,1,tfunnel_merge_port0}
};

TFunnelPortEnableConfig tfunnel_port_adsp[]={
   {IN_FUN0,2,tfunnel_merge_port0}
};

TFunnelPortEnableConfig tfunnel_port_system_noc[]={
   {IN_FUN0,3,tfunnel_merge_port0}
};

TFunnelPortEnableConfig tfunnel_port_apps_etm[]={
   {IN_FUN0,4,tfunnel_merge_port0}
};

TFunnelPortEnableConfig tfunnel_port_mmss_noc[]={
   {IN_FUN0,5,tfunnel_merge_port0}
};

TFunnelPortEnableConfig tfunnel_port_peripheral_noc[]={
   {IN_FUN0,6,tfunnel_merge_port0}
};

TFunnelPortEnableConfig tfunnel_port_stm[]={
   {IN_FUN0,7,tfunnel_merge_port0}
};

TFunnelPortEnableConfig tfunnel_port_rpm_itm[]={
   {IN_FUN1,1,tfunnel_merge_port1}
};


TFunnelPortEnableConfig tfunnel_port_mmss[]={
   {IN_FUN1,2,tfunnel_merge_port1}
};

TFunnelPortEnableConfig tfunnel_port_pronto[]={
   {IN_FUN1,2,tfunnel_merge_port1}
};


TFunnelPortEnableConfig tfunnel_port_bimc[]={
   {IN_FUN1,3,tfunnel_merge_port1}
};

TFunnelPortEnableConfig tfunnel_port_modem[]={
   {IN_FUN1,4,tfunnel_merge_port1}
};

TFunnelPortEnableConfig tfunnel_port_ocmem_noc[]={
   {IN_FUN1,5,tfunnel_merge_port1}
};




