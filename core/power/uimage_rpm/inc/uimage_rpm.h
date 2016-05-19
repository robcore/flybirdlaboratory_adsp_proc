#ifndef UIMAGE_RPM_H
#define UIMAGE_RPM_H
/*=============================================================================
FILE:         uimage_rpm.h

OVERVIEW:     This file provides the public externs and definitions that
are exported by the rpm module for ADSP uImage.

Copyright (c) 2013 - 2014 QUALCOMM Technologies Incorporated.
All Rights Reserved.
Qualcomm Confidential and Proprietary
================================================================================
$Header: //components/rel/core.adsp/2.6.1/power/uimage_rpm/inc/uimage_rpm.h#1 $
$DateTime: 2014/10/16 12:45:40 $
==============================================================================*/
#include "DALStdDef.h"

typedef enum
{
    UIMAGE_RPM_NO_WAIT_MODE = 0, /* don't wait for ACKs */
    UIMAGE_RPM_BUSY_WAIT_MODE,   /* wait for ACKs in busywait */
    UIMAGE_RPM_NUM_WAIT_MODES,
} uImage_rpm_wait_mode_t;

/*--------------------------------------------------------------------------
  FUNCTION PROTOTYPES
  ---------------------------------------------------------------------------*/

/*******************************************************************************
 *
 * uImage_rpm_set_clk_values
 *
 * This function is used to turn DDR on/off.
 * It sends ACTIVE SET requests to RPM Firmware to set values to resources.
 * The resources are SNOC and BIMC.
 *
 *   snoc_freq_khz: SNOC frequency in KHz. To turn DDR off, it should be set to 1
 *   bimc_freq_khz: BIMC frequency in KHz. To turn DDR off, it should be set to 0
 *   wait_mode:     Indicates how to wait for SMD Ack from RPM (TBD)
 */
void uImage_rpm_set_clk_values(uint32 snoc_freq_khz,
                               uint32 bimc_freq_khz,
                               uImage_rpm_wait_mode_t wait_mode);

#endif /* UIMAGE_RPM_H */

