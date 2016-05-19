/*==============================================================================
$Header: //components/rel/avs.adsp/2.6.1/afe/drivers/hw/lpasshwio/devcfg/src/lpasshwio_devcfg_8996.c#3 $
$DateTime: 2014/12/26 03:33:20 $
$Author: svutukur $
$Change: 7198050 $
$Revision: #3 $

FILE: lpasshwio_devcfg_8996.c 

DESCRIPTION: 8092 Device Config

Copyright 2014 QUALCOMM Technologies, Inc. (QTI).
All Rights Reserved.
QUALCOMM Proprietary/GTDR
==============================================================================*/

/*=====================================================================
 Includes
 ======================================================================*/
#include "lpasshwio_devcfg.h"

HwdLpassPropertyType lpass_prop ={0x09080000};

/* Istari, 8996 */
HwdAudioIfPropertyType audioif_prop = {
   0x09100000, // audHWRegBase [ The is the base address ]
   (128*1024), // audHwRegSize
   0x009A0000, //hdmiAudHwRegBase
   (4*1024),  // hdmiAudHwRegSize
   4,         // dmaWordSize in bytes [DMA word is 32-bits, 4 bytes]
   5,         // outgoingDmaChCnt (read DMA channel count)
   4,         // incomingDmaChCnt (write DMA channel count)
   12,         // infTypecnt ( The total number below, how many interface, max is 12 )
   {0, 1, 2,3,4,5,6,7,8, 9, 10,11}, // AudioHWInterfaceType, 0: PRI_MI2S, 1: PCM, 2: 2ndPCM, etc
   {4, 4, 4,4,4,8,2,8,4, 2, 4, 4}, // maximum # of channel for audio if.
   {3, 3, 3,3,3,3,1,1,2, 2, 3, 3}, // 0x1 speaker path only,  0x2 mic path only,  0x3: bidirectional 
   19,                  // lpaif intr irq #
   2,                   // intrOutputIndex
   0x40000000,          // lpaif hw revision
   1};                  // Indicate if hardware latching support for AV-timer present
HwdAvtimerPropertyType avtimer_prop = {{0x090F7000, 0, 0}, {0x1000, 0, 0}, {19200000, 0, 0}, 50, 0x30040000};
HwdDmlitePropertyType dmlite_prop = {0x090C2000, 0x1000, 23, 0x20000001};
HwdResamplerPropertyType resampler_prop = {0x09138000, 0x8000, 53, 0x30000000};

lpasshwio_vfr_prop_t vfr_prop = {0x0908F000, 0x9000, 0x20001000, 0x1, 0x0000001F, 0x2, 2, {51, 124, 0, 0}, {{0x0, 0x1}, {0x7, 0x1}, {0, 0x0}, {0, 0x0}}};
lpasshwio_prop_riva_struct_t afe_riva_prop = {0, 0, 0, 0, 0, 0, 0, 0};
lpasshwio_prop_slimbus_struct_t afe_slimbus_prop = {1, 1}; 
HwdMidiPropertyType midi_prop = {0,0, 0, 0, 0,0 };
lpasshwio_prop_spdif_struct_t spdiftx_prop = {0, 0, 0, 0, 0, 0, 0};
lpasshwio_prop_hdmi_input_struct_t hdmi_input_prop = {0x0, 0x0, 0x0, 0x0}; 
HwdPullablePllPropertyType ppll_prop = {0, {0, 0}, {0, 0}}; 
HwdBstcMgrPropertyType bstc_mgr_prop = {0x0, 0x0, 0x0}; 
lpasshwio_prop_sif_struct_t sif_prop = {0x0, 0x0, 0x0}; 