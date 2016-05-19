/*==============================================================================
$Header: //components/rel/avs.adsp/2.6.1/afe/drivers/hw/lpasshwio/devcfg/src/lpasshwio_devcfg_8x26.c#3 $
$DateTime: 2014/12/26 03:33:20 $
$Author: svutukur $
$Change: 7198050 $
$Revision: #3 $

FILE: lpasshwio_devcfg_8x26.c 

DESCRIPTION: 8x26 Device Config

Copyright 2014 QUALCOMM Technologies, Inc. (QTI).
All Rights Reserved.
QUALCOMM Proprietary/GTDR
==============================================================================*/

/*=====================================================================
 Includes
 ======================================================================*/
#include "lpasshwio_devcfg.h"

HwdLpassPropertyType lpass_prop ={0xFE037000};
HwdAudioIfPropertyType audioif_prop = {0xFE0C0000, (128*1024), 0, 
   0, 4, 5, 4, 6, {0,1,2,3,4,5},{4,4,4,4,4,2}, {3,3,3,3,3,3}, 19, 2, 0x30020000, 0};
HwdAvtimerPropertyType avtimer_prop = {{0xFE053000, 0, 0}, {0x1000, 0, 0}, {19200000, 0, 0}, 50, 0x30000001};
HwdDmlitePropertyType dmlite_prop = {0xFE04A000, 0x1000, 23, 0x30020000};
HwdResamplerPropertyType resampler_prop = {0, 0, 0, 0};
lpasshwio_vfr_prop_t vfr_prop = {0xFE033000, 0x1000, 0x10000000, 0x0, 0x7, 0x1, 0, {36, 40, 0, 0}, {{0x0, 0x1}, {0x7, 0x1}, {0, 0x0}, {0, 0x0}}};
lpasshwio_prop_riva_struct_t afe_riva_prop =  {1, 0xFB206008, 0x20, 17, 10, 16, 15, 0};
lpasshwio_prop_slimbus_struct_t afe_slimbus_prop = {0, 0};
HwdMidiPropertyType midi_prop = {0, 0, 0, 0, 0, 0};
lpasshwio_prop_spdif_struct_t spdiftx_prop = {0, 0, 0, 0, 0, 0, 0};
lpasshwio_prop_hdmi_input_struct_t hdmi_input_prop = {0, 0, 0, 0};
HwdPullablePllPropertyType ppll_prop = {0, {0, 0}, {0, 0}};
HwdBstcMgrPropertyType bstc_mgr_prop = {0, 0, 0};
lpasshwio_prop_sif_struct_t sif_prop = {0x0, 0x0, 0x0};