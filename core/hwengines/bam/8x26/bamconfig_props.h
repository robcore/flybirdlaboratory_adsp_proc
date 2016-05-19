#ifndef BAMCONFIG_PROPS_H_
#define BAMCONFIG_PROPS_H_

/**
  @file bamconfig_props.h
  @brief
  This file contains definitions of constants, data structures and
  interfaces of base address and irq vector of BAM hardware.

*/
/*
===============================================================================

                             Edit History

 $Header:

when       who     what, where, why
--------   ---     ------------------------------------------------------------
10/15/12   SS      Created

===============================================================================
                   Copyright (c) 2012 Qualcomm Technologies Incorporated.
                          All Rights Reserved.
                        Qualcomm Confidential and Proprietary.
===============================================================================
*/

#include "DALStdDef.h"

/* Module base address info  */
#define PERIPH_SS_BASE          0xF9800000
#define CRYPTO_TOP_BASE         0xFD400000
#define QDSS_TRACE_BASE         0xFC300000
#define LPASS_TOP_BASE          0xFE000000
#define MSS_TOP_BASE            0xFC800000


/* Bam Module base address info */
#define BAM_NDP_CRYPTO1_BASE        (CRYPTO_TOP_BASE + 0x00004000)
#define BAM_LITE_BLSP1_BASE         (PERIPH_SS_BASE + 0x00104000)
#define BAM_BAMDMA_BASE             (PERIPH_SS_BASE + 0x00184000)
#define BAM_SDC1_BASE               (PERIPH_SS_BASE + 0x00004000)
#define BAM_SDC2_BASE               (PERIPH_SS_BASE + 0x00084000)
#define BAM_SDC3_BASE               (PERIPH_SS_BASE + 0x00044000)
#define BAM_USB2_BASE               (PERIPH_SS_BASE + 0x00244000)
#define BAM_LITE_SLIMBUS_BASE       (LPASS_TOP_BASE + 0x00104000)
#define BAM_NDP_MSS_A2_BASE         (MSS_TOP_BASE + 0x00034000)
#define BAM_NDP_MSS_CRYPTO_BASE     (MSS_TOP_BASE + 0x001C4000)
#define BAM_NDP_QDSS_BASE           (QDSS_TRACE_BASE + 0x0007C000)

/* BAM module irq vector in Apps image */
#ifdef BAM_APPS_CONFIG
#define BAM_NDP_CRYPTO1_IRQVECTOR			239
#define BAM_LITE_BLSP1_IRQVECTOR            270
#define BAM_BAMDMA_IRQVECTOR                126
#define BAM_LITE_SLIMBUS_IRQVECTOR      	196
#define BAM_SDC1_IRQVECTOR              	169
#define BAM_SDC2_IRQVECTOR              	252
#define BAM_SDC3_IRQVECTOR              	255
#define BAM_USB2_IRQVECTOR              	167
#define BAM_NDP_QDSS_IRQVECTOR          	199
#endif/* BAM_APPS_CONFIG */

/* BAM module irq vector in mpass image */
#ifdef BAM_MODEM_CONFIG
#define BAM_BAMDMA_IRQVECTOR	            77
#define BAM_LITE_BLSP1_IRQVECTOR			95
#define BAM_LITE_SLIMBUS_IRQVECTOR			79
#define BAM_NDP_MSS_CRYPTO_IRQVECTOR		74
#define BAM_MSS_A2_IRQVECTOR				61
#endif /* BAM_MODEM_CONFIG */

/* BAM module irq vector in LPASS image */
#ifdef BAM_ADSP_CONFIG
#define BAM_NDP_CRYPTO1_IRQVECTOR			97
#define BAM_LITE_BLSP1_IRQVECTOR		    55
#define BAM_BAMDMA_IRQVECTOR		        59
#define BAM_LITE_SLIMBUS_IRQVECTOR			12
#endif /* BAM_ADSP_CONFIG */

/* BAM module irq vector in TZOS image */
#ifdef BAM_TZOS_CONFIG
#define BAM_NDP_CRYPTO1_IRQVECTOR			238
#define BAM_LITE_BLSP1_IRQVECTOR		    270
#define BAM_BAMDMA_IRQVECTOR		    	126
#define BAM_IRQVECTOR_NONE			    	 0
#endif/* BAM_TZOS_CONFIG */

/* Bam Cilent config info sturcture */
typedef struct
{
   uint32  base_pa;
   uint32  irq_vector;
}bamclient_config_info_type;


#endif /* BAMCONFIG_PROPS_H_ */