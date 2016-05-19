
/*========================================================================
   This file contains HWD device configuration functions

  Copyright (c) 2009-2013 QUALCOMM Technologies, Inc. (QTI).  All Rights Reserved.
  QUALCOMM Technologies, Inc. (QTI) Proprietary.  Export of this technology or software is regulated
  by the U.S. Government, Diversion contrary to U.S. law prohibited.
 
  $Header: //components/rel/avs.adsp/2.6.1/afe/drivers/hw/lpasshwio/devcfg/inc/lpasshwio_devcfg.h#3 $
 ====================================================================== */

#ifndef LPASSHWIO_DEVCFG_H
#define LPASSHWIO_DEVCFG_H

#include "typedef_drivers.h"

#define MAX_AUDIF_TYPE_NUM   12

#define NUM_MAX_VFR_SRC    4

#define AUDIOIF_DEVCFG_DIR_SINK         0x1
#define AUDIOIF_DEVCFG_DIR_SOURCE       0x2

#define LPASS_HW_VER_3_0_2    (0x30000002) /* BIT: 31:28, Major verion 
                                              BIT: 27:16, Minor verion
                                              BIT: 15:0, step */


#define LPASS_HW_VER_3_5_0    (0x30050000) /* BIT: 31:28, Major verion 
                                              BIT: 27:16, Minor verion
                                              BIT: 15:0, step */
                                           

#define LPASS_HW_VER_4_0_0    (0x40000000) /* BIT: 31:28, Major verion 
                                              BIT: 27:16, Minor verion
                                              BIT: 15:0, step */


#define NUM_MAX_AVTIMER_HW_INSTANCE      3

#define NUM_MAX_LPASS_PLL_TYPE           2

enum
{
   TIMESTAMP_LATCH_TYPE_SOFTWARE = 0,
   TIMESTAMP_LATCH_TYPE_HARDWARE
};

typedef struct
{
   uint32 hw_ver_reg_base;   /* LPASS hw version reg base addr */
}HwdLpassPropertyType;

typedef struct
{
   uint32 audHwRegBase;   // lpaif reg base addr
   uint32 audHwRegSize;   // lpaif reg page size
   uint32 hdmiAudHwRegBase;   // hdmi audio reg base addr
   uint32 hdmiAudHwRegSize;   // hdmi audio reg page size
   uint32 dmaWordSize;   // DMA word size based on byte
   uint32 outgoingDmaChCnt;   // read DMA channel count
   uint32 incomingDmaChCnt;   // write DMA channel count
   uint32 infTypeCnt;   // # of lpaif interface type count
   uint32 infTypeList[MAX_AUDIF_TYPE_NUM];    // cast to AudioHWInterfaceType
   uint32 infTypeDataLineCaps[MAX_AUDIF_TYPE_NUM]; // maximum # of channel for audio if.
   uint32 infTypeDirection[MAX_AUDIF_TYPE_NUM];  // 0x1 spacker path only,  0x2 mic path only,   0x3: bidirectional 
   uint32 isrHookPinNum;   // lpaif intr irq #
   uint32 intrOutputIndex;   // interrupt line #
   uint32 hw_revision;   // lpaif hw revision
   uint32 avtimer_latch_type;  // Indicates if hardware latching support for AV-timer present
} HwdAudioIfPropertyType;

typedef struct
{
   uint32 baseRegAddr[NUM_MAX_AVTIMER_HW_INSTANCE];   // avtimer reg base addr
   uint32 regSize[NUM_MAX_AVTIMER_HW_INSTANCE];   // avtimer reg page size
   uint32 rootClk[NUM_MAX_AVTIMER_HW_INSTANCE];   // avtimer reg page size
   uint32 isrHookPinNum;   // avtimer intr irq #
   uint32 hw_revision;   // avtimer hw revision
} HwdAvtimerPropertyType;

typedef struct
{
   uint32 baseRegAddr;   // dmlite reg base addr
   uint32 regSize;   // dmlite reg page size
   uint32 intPinNo;   // dmlite intr irq #
   uint32 hw_revision;   // dmlite hw revision
} HwdDmlitePropertyType;

typedef struct
{
   uint32 baseRegAddr;   // hw resampler reg base addr
   uint32 regSize;   // hw resampler reg page size
   uint32 isrHookPinNum;   // hw resampler intr irq #
   uint32 hw_revision;   // resampler hw revision
} HwdResamplerPropertyType;

typedef struct vfr_src_prop
{
   uint32 irq_mux_ctl_sel;    // Mux control for VFR source selection
   uint32 is_supported;       // If this VFR source is hw supported or not
} vfr_src_prop_t;

typedef struct
{
   uint32            reg_base_addr;       // VFR reg base addr
   uint32            reg_size;            // VFR reg page size
   uint32            hw_revision;         // VFR hw revision
   uint32            hw_latch_ver;        // VFR hw latching version
   uint32            mux_ctl_mask;        // Mask value for configuring VFR Mux
   uint32            num_vfr_ts_mux;                  // Number of VFR timestamp mux
   uint32            num_gp_ts_mux;                   // Number of General Purpose timestamp mux
   uint32            l2vic_num[NUM_MAX_VFR_SRC];      // Available L2VIC # for VFR interrupts
   vfr_src_prop_t    vfr_src_prop[NUM_MAX_VFR_SRC];
}lpasshwio_vfr_prop_t;

typedef struct
{
    uint32 hw_revision; // hw revision, 0-not supported
    uint32 ccu_mb0_ctrl_reg_phy_addr;
    uint16 ipc_send_mail_box_offset; // mail box offset from mb0 ctrl register addr
    uint16 internal_bt_tx_int; // BT Mic path interrupt number
    uint16 internal_bt_rx_int; // BT Speaker path interrupt number
    uint16 internal_fm_tx_rx_int; // FM interrupt number
    uint16 internal_bt_fm_ipc_int; // IPC interrupt
    uint16 hw_timestamp_available; //indicates if hardware timestamp block is available
}lpasshwio_prop_riva_struct_t;

typedef struct
{
    uint32 hw_revision; // hw revision, 0-not supported
    uint32 avtimer_latch_type; // Indicates if hardware latching support for AV-timer present
}lpasshwio_prop_slimbus_struct_t;

typedef struct
{
   uint32 baseRegAddr;   	// MIDI reg base addr
   uint32 baseRegVirtAddr;  // MIDI reg base virtual addr
   uint32 virtOffset;		// MIDI virtual address base offset
   uint32 regSize;   		// MIDI registers size
   uint32 intPinNo;   		// MIDI intr irq #
   uint32 hw_revision;   	// MIDI hw revision
} HwdMidiPropertyType;

typedef struct
{
   uint32 base_reg_phy_addr;  // spdiftx reg base addr
   uint32 reg_size;           // spdiftx reg page size
   uint32 reset_reg_phy_addr; // spdiftx reset reg base addr
   uint32 reset_reg_size;     // spdiftx rest reg page size;
   uint32 int_irq_no;         // spdiftx intr irq #
   uint32 num_hw_buf;         // num of hw buffer    
   uint32 hw_revision;        // spdiftx hw revision
} lpasshwio_prop_spdif_struct_t;

typedef struct
{   
   uint32 reg_base_addr;      // hdmi input reg base addr
   uint32 reg_size;           // hdmi input reg page size
   uint32 int_irq_no;         // l2vic id for hdmi interrupt
   uint32 hw_revision;        // hdmi input hw revision
} lpasshwio_prop_hdmi_input_struct_t;

typedef struct
{
   uint32 hw_revision;                                    // hw revision
   uint32 lpass_pll_type[NUM_MAX_LPASS_PLL_TYPE];           // 0 - PLL_UNDEFINED, 1 - LPAAUDIO_PLL, 2 - LPAQ6_PLL 
   uint32 lpass_pll_type_pullable[NUM_MAX_LPASS_PLL_TYPE];  // 0 - NOT PULLABLE, 1 - PULLABLE 
} HwdPullablePllPropertyType;

typedef struct
{   
   uint32 reg_base_addr;      // BSTC Manager reg base addr
   uint32 reg_size;           // BSTC Manager reg page size
   uint32 hw_revision;        // BSTC Manager hw revision
} HwdBstcMgrPropertyType;

typedef struct
{
   uint32 base_reg_phy_addr;  // sif reg base addr
   uint32 reg_size;           // sif reg page size
   uint32 hw_revision;        // sif hw revision
} lpasshwio_prop_sif_struct_t;
#endif // #ifndef LPASSHWIODEVCFG_H
