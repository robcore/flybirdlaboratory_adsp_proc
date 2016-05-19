/*==============================================================================
$Header: //components/rel/avs.adsp/2.6.1/afe/drivers/hw/lpasshwio/devcfg/src/lpasshwio_devcfg_8994.c#3 $
$DateTime: 2014/12/26 03:33:20 $
$Author: svutukur $
$Change: 7198050 $
$Revision: #3 $

FILE: lpasshwio_devcfg_8994.c 

DESCRIPTION: 8994 Device Config

Copyright 2014 QUALCOMM Technologies, Inc. (QTI).
All Rights Reserved.
QUALCOMM Proprietary/GTDR
==============================================================================*/

/*=====================================================================
 Includes
 ======================================================================*/
#include "lpasshwio_devcfg.h"

HwdLpassPropertyType lpass_prop ={0xFE04F000};
HwdAudioIfPropertyType audioif_prop = {0xFE0C0000, (128*1024), 0xFD9A8000, 
   (4*1024), 4, 5, 4, 8, {0,1,2,3,4,5,6,7}, {4,8,8,4,4,8,2,8}, {3,3,3,3,3,3,1,1}, 19, 2, 0x30080000, 1};
HwdAvtimerPropertyType avtimer_prop = {{0xFE09C000, 0, 0}, {0x1000, 0, 0}, {19200000, 0, 0}, 50, 0x30040000};
HwdDmlitePropertyType dmlite_prop = {0xFE092000, 0x1000, 23, 0x30080000};
HwdResamplerPropertyType resampler_prop = {0xFE0B0000, 0x4000, 53, 0x30080000};
lpasshwio_vfr_prop_t vfr_prop = {0xFE03C000, 0x9000, 0x20001000, 0x1, 0x0000001F, 0x2, 2, {51, 124, 0, 0}, {{0x0, 0x1}, {0x7, 0x1}, {0, 0x0}, {0, 0x0}}};
lpasshwio_prop_riva_struct_t afe_riva_prop = {0, 0, 0, 0, 0, 0, 0, 0};
lpasshwio_prop_slimbus_struct_t afe_slimbus_prop = {1, 1}; 
HwdMidiPropertyType midi_prop = {0,0, 0, 0, 0,0 };
lpasshwio_prop_spdif_struct_t spdiftx_prop = {0, 0, 0, 0, 0, 0, 0};
lpasshwio_prop_hdmi_input_struct_t hdmi_input_prop = {0x0, 0x0, 0x0, 0x0}; 
HwdPullablePllPropertyType ppll_prop = {0, {0, 0}, {0, 0}}; 
HwdBstcMgrPropertyType bstc_mgr_prop = {0x0, 0x0, 0x0}; 
lpasshwio_prop_sif_struct_t sif_prop = {0x0, 0x0, 0x0}; 