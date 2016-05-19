/*==============================================================================

  D A L I N T E R R U P T   C O N T R O L L E R    

DESCRIPTION
 This file Contains the Interrupt configuration data for all the interrupts for 
 this platform.

REFERENCES

        Copyright © 2011 Qualcomm Technologies Incorporated.
               All Rights Reserved.
            QUALCOMM Proprietary/GTDR
===========================================================================*/

/*===========================================================================

                      EDIT HISTORY FOR FILE

This section contains comments describing changes made to this file.
Notice that changes are listed in reverse chronological order.

$Header: //components/rel/core.adsp/2.6.1/systemdrivers/InterruptController/config/8094/InterruptConfigData.c#1 $

when       who     what, where, why
--------   ---     ----------------------------------------------------------
1/1/2010   aratin  First draft created. 
===========================================================================*/

#include "DALReg.h"
#include "DALDeviceId.h"
#include "DDIInterruptController.h"
#include "DALInterruptControllerConfig.h"



/*=========================================================================

                           DATA DEFINITIONS

===========================================================================*/

/*
 * Interrupt_Configs
 * BSP data for this target's interrupts.
 * The data layout is the following :
 * {  l2VIC interrupt vector number , Interrupt name }
 *
 */
static InterruptConfigType InterruptConfigs[] = 
{
 {5 ,    "rpm_ipc[9]"},
 {7 ,    "rpm_ipc[8]"},
 {8 ,    "APCS_adspIPCInterrupt[1]"},
 {13 ,    "rpm_ipc[10]"},
 {14 ,    "rpm_ipc[11]"},
 {18 ,    "APCS_adspIPCInterrupt[0]"},
 {24 ,    "dir_conn_irq_lpa_dsp[0]"},
 {25 ,    "dir_conn_irq_lpa_dsp[1]"},
 {26 ,    "dir_conn_irq_lpa_dsp[2]"},
 {27 ,    "dir_conn_irq_lpa_dsp[3]"},
 {28 ,    "dir_conn_irq_lpa_dsp[4]"},
 {29 ,    "dir_conn_irq_lpa_dsp[5]"},
 {33 ,    "APCS_adspIPCInterrupt[2]"},
 {37 ,    "adsp_ext_vfr_irq"},
 {38 ,    "summary_irq_lpa_dsp"},
 {45 ,    "usb30_ee1_irq"},
 {46 ,    "APCS_adspIPCInterrupt[3]"},
 {47 ,    "usb30_ee2_irq"},
 {48 ,    "ee3_lpass_spmi_periph_irq"},
 {49 ,    "channel3_lpass_trans_done_irq"},
 {53 ,    "resampler_irq[1]"},
 {54 ,    "usb1_hs_irq"},
 {55 ,    "blsp1_bam_irq[1]"},
 {56 ,    "blsp2_bam_irq[1]"},
 {57 ,    "o_camera_lpass_vfe_0_sof_stb"},
 {58 ,    "o_camera_lpass_vfe_0_eof_stb"},
 {59 ,    "bam_dma_irq[1]"},
 {60 ,    "ao_pen_irq"},
 {61 ,    "spdm_realtime_irq[2]"},
 {62 ,    "summary_irq_sensors"},
 {64 ,    "blsp1_qup_1_irq"},
 {65 ,    "blsp1_qup_2_irq"},
 {66 ,    "blsp1_qup_3_irq"},
 {67 ,    "blsp1_qup_4_irq"},
 {68 ,    "blsp1_qup_5_irq"},
 {69 ,    "blsp1_qup_6_irq"},
 {70 ,    "dir_conn_irq_sensors[0]"},
 {71 ,    "dir_conn_irq_sensors[1]"},
 {72 ,    "dir_conn_irq_sensors[2]"},
 {73 ,    "dir_conn_irq_sensors[3]"},
 {74 ,    "dir_conn_irq_sensors[4]"},
 {75 ,    "dir_conn_irq_sensors[5]"},
 {76 ,    "dir_conn_irq_sensors[6]"},
 {77 ,    "dir_conn_irq_sensors[7]"},
 {80 ,    "blsp2_qup_1_irq"},
 {81 ,    "blsp2_qup_2_irq"},
 {82 ,    "blsp2_qup_3_irq"},
 {83 ,    "blsp2_qup_4_irq"},
 {84 ,    "blsp2_qup_5_irq"},
 {85 ,    "blsp2_qup_6_irq"},
 {90 ,    "o_timeout_slave_lpass_summary_intr"},
 {91 ,    "o_camera_lpass_vfe_1_sof_stb"},
 {92 ,    "o_camera_lpass_vfe_1_eof_stb"},
 {96 ,    "crypto_core_irq[0]"},
 {97 ,    "crypto_bam_irq[0]"},
 {98 ,    "crypto_core_irq[0]"},
 {99 ,    "crypto_bam_irq[0]"},
 {102 ,    "dir_conn_irq_sensors[8]"},
 {103 ,    "dir_conn_irq_sensors[9]"},
 {104 ,    "phss_uart_lpass_int[0]"},
 {105 ,    "phss_uart_lpass_int[1]"},
 {INVALID_INTERRUPT , ""}
};

/*
 * InterruptPlatformDataType 
 * This is used by the Interrupt controller platform to query platform specific data. 
 */
InterruptPlatformDataType  pInterruptControllerConfigData[] =
{
  {
    InterruptConfigs,           /* pIRQConfigs */
    106
  }
};




  
