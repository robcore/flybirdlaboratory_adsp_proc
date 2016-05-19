/*==============================================================================

  D A L I N T E R R U P T   C O N T R O L L E R    

DESCRIPTION
 This file Contains the Interrupt configuration data for all the interrupts for 
 this platform.

REFERENCES

        Copyright © 2011 QUALCOMM Technologies Incorporated.
               All Rights Reserved.
            QUALCOMM Proprietary/GTDR
===========================================================================*/

/*===========================================================================

                      EDIT HISTORY FOR FILE

This section contains comments describing changes made to this file.
Notice that changes are listed in reverse chronological order.

$Header: //components/rel/core.adsp/2.6.1/systemdrivers/InterruptController/config/8996/InterruptConfigData.c#1 $

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
  {0 , "qdsp6_etm_irq" },
  {1 , "qdsp6_isdb_irq" },
  {2 , "qtmr_phy_irq[0]" },
  {3 , "qtmr_phy_irq[1]" },
  {5 , "rpm_ipc[9]" },
  {7 , "rpm_ipc[8]" },
  {8 , "APCS_adspHlosIPCInterrupt[1]" },
  {11 , "slimbus_core_ee0_irq" },
  {12 , "bam_irq[0]" },
  {13 , "rpm_ipc[10]" },
  {14 , "rpm_ipc[11]" },
  {18 , "APCS_adspHlosIPCInterrupt[0]" },
  {19 , "audio_out2_irq" },
  {20 , "bus_irq" },
  {23 , "dm_irq" },
  {24 , "dir_conn_irq_lpa_dsp[0]" },
  {25 , "dir_conn_irq_lpa_dsp[1]" },
  {26 , "dir_conn_irq_lpa_dsp[2]" },
  {27 , "dir_conn_irq_lpa_dsp[3]" },
  {28 , "dir_conn_irq_lpa_dsp[4]" },
  {29 , "dir_conn_irq_lpa_dsp[5]" },
  {30 , "q6ss_idle_timer_irq" },
  {30 , "qtmr_phy_irq[2]" },
  {31 , "q6ss_cti_irq" },
  {32 , "q6ss_wdog_irq" },
  {33 , "APCS_adspHlosIPCInterrupt[2]" },
  {37 , "adsp_ext_vfr_irq" },
  {38 , "summary_irq_lpa_dsp" },
  {41 , "q6ss_avs_irq" },
  {42 , "q6ss_avs_cpu_up_irq" },
  {42 , "usb20s_power_event_irq" },
  {43 , "q6ss_avs_cpu_dn_irq" },
  {44 , "usb30_power_event_irq" },
  {45 , "usb30_ee1_irq" },
  {46 , "APCS_adspHlosIPCInterrupt[3]" },
  {47 , "usb30_ee2_irq" },
  {48 , "ee3_lpass_spmi_periph_irq" },
  {49 , "channel3_lpass_trans_done_irq" },
  {50 , "avtimer_int_0" },
  {51 , "vfr_irq_mux_out[0]" },
  {53 , "resampler_irq[1]" },
  {54 , "usb20s_ee1_irq" },
  {55 , "blsp1_bam_irq[1]" },
  {56 , "blsp2_bam_irq[1]" },
  {57 , "o_hwe_sof_stb_vfe_0_lpass" },
  {58 , "o_hwe_eof_stb_vfe_0_lpass" },
  {60 , "ao_pen_irq" },
  {61 , "spdm_realtime_irq[2]" },
  {63 , "q6ss_avs_sw_done_irq" },
  {64 , "blsp1_qup_irq(0)" },
  {65 , "blsp1_qup_irq(1)" },
  {66 , "blsp1_qup_irq(2)" },
  {67 , "blsp1_qup_irq(3)" },
  {68 , "blsp1_qup_irq(4)" },
  {69 , "blsp1_qup_irq(5)" },
  {72 , "pcie20_2_int_msi_dev5" },
  {73 , "pcie20_2_int_msi_dev4" },
  {74 , "pcie20_1_int_msi_dev5" },
  {75 , "pcie20_1_int_msi_dev4" },
  {76 , "pcie20_0_int_msi_dev5" },
  {77 , "pcie20_0_int_msi_dev4" },
  {79 , "ssc_irq_out_lpass[0]" },
  {80 , "blsp2_qup_irq(0)" },
  {81 , "blsp2_qup_irq(1)" },
  {82 , "blsp2_qup_irq(2)" },
  {83 , "blsp2_qup_irq(3)" },
  {84 , "blsp2_qup_irq(4)" },
  {85 , "blsp2_qup_irq(5)" },
  {86 , "slimbus_core_ee0_irq" },
  {87 , "bam_irq[0]" },
  {90 , "o_timeout_slave_lpass_summary_intr" },
  {91 , "o_hwe_sof_stb_vfe_1_lpass" },
  {92 , "o_hwe_eof_stb_vfe_1_lpass" },
  {93 , "ssc_irq_out_lpass[3]" },
  {93 , "ssc_irq_out_lpass[3]" },
  {94 , "lpass_hdmitx_interrupt" },
  {96 , "crypto_core_irq[0]" },
  {96 , "crypto_core_irq[1]" },
  {97 , "crypto_bam_irq[0]" },
  {97 , "crypto_bam_irq[1]" },
  {104 , "phss_uart_lpass_int[0]" },
  {105 , "phss_uart_lpass_int[1]" },
  {112 , "lpass_core_qos_q6_interrupt" },
  {113 , "lpass_qos_q6_interrupt" },
  {114 , "APCS_adspHypIPCInterrupt[0]" },
  {115 , "APCS_adspHypIPCInterrupt[1]" },
  {116 , "APCS_adspHypIPCInterrupt[2]" },
  {117 , "APCS_adspHypIPCInterrupt[3]" },
  {118 , "ssc_irq_out_lpass[1]" },
  {118 , "ssc_irq_out_lpass[1]" },
  {119 , "ssc_irq_out_lpass[2]" },
  {119 , "ssc_irq_out_lpass[2]" },
  {124 , "vfr_irq_mux_out[1]" },
  {125 , "camss_irq0" },
  {126 , "camss_irq1" },
  {127 , "camss_irq2" },
  {128 , "camss_irq3" },
  {129 , "camss_irq4" },
  {130 , "camss_irq5" },
  {131 , "camss_irq6" },
  {132 , "camss_irq7" },
  {133 , "camss_irq8" },
  {134 , "camss_irq9" },
  {135 , "camss_irq10" },
  {137 , "camss_irq12" },
  {138 , "camss_irq13" },
  {139 , "camss_irq14" },
  {140 , "camss_irq15" },
  {141 , "camss_irq16" },
  {142 , "camss_irq17" },
  {143 , "camss_irq18" },
  {144 , "camss_dsp_streaming_0_irq" },
  {145 , "camss_dsp_streaming_1_irq" },
  {146 , "lcc_spkr_ext_clk_detect_inactive_irq" },
  {147 , "lcc_pri_ext_clk_detect_inactive_irq" },
  {148 , "lcc_sec_ext_clk_detect_inactive_irq" },
  {149 , "lcc_ter_ext_clk_detect_inactive_irq" },
  {150 , "lcc_quad_ext_clk_detect_inactive_irq" },
  {151 , "lcc_audio_core_smmu_gds_hw_ctrl_sequence_abort_irq" },
  {152 , "lcc_audio_wrapper_q6_smmu_gds_hw_ctrl_seq_abort" },

  /* 
   * This marks the end of the BSP data. 
   * This is a place holder for data processing.
   */
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
    154
  }
};




  
