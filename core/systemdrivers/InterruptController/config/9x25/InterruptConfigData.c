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

$Header: //components/rel/core.adsp/2.6.1/systemdrivers/InterruptController/config/9x25/InterruptConfigData.c#1 $

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
  {4 ,    "mss_to_lpass_irq[0]"},
  {5 ,    "rpm_ipc[9]"},
  {6 ,    "mss_to_lpass_irq[1]"},
  {7 ,    "rpm_ipc[8]"},
  {8 ,    "APCS_sysIPCInterrupt[9]"},
  {9 ,    "mss_to_lpass_irq[2]"},
  {10 ,    "audio_out2_irq"},
  {10 ,    "avtimer_int_0"},
  {10 ,    "bam_irq[0]"},
  {10 ,    "vfr_irq_mux_out"},
  {10 ,    "bus_irq"},
  {10 ,    "dm_irq"},
  {10 ,    "q6ss_wdog_irq"},
  {10 ,    "q6ss_avs_irq"},
  {10 ,    "q6ss_avs_cpu_up_irq"},
  {10 ,    "q6ss_avs_cpu_dn_irq"},
  {10 ,    "q6ss_idle_timer_irq"},
  {10 ,    "q6ss_avs_sw_done_irq"},
  {10 ,    "qdsp6_isdb_irq"},
  {10 ,    "qdsp6_etm_irq"},
  {10 ,    "q6ss_cti_irq"},
  {10 ,    "qtmr_phy_irq[0]"},
  {10 ,    "qtmr_phy_irq[1]"},
  {10 ,    "qtmr_phy_irq[2]"},
  {10 ,    "slimbus_core_ee0_irq"},
  {13 ,    "rpm_ipc[10]"},
  {14 ,    "rpm_ipc[11]"},
  {18 ,    "APCS_sysIPCInterrupt[8]"},
  {24 ,    "dir_conn_irq_lpa_dsp[0]"},
  {25 ,    "dir_conn_irq_lpa_dsp[1]"},
  {26 ,    "dir_conn_irq_lpa_dsp[2]"},
  {27 ,    "dir_conn_irq_lpa_dsp[3]"},
  {28 ,    "dir_conn_irq_lpa_dsp[4]"},
  {29 ,    "dir_conn_irq_lpa_dsp[5]"},
  {33 ,    "APCS_sysIPCInterrupt[10]"},
  {34 ,    "mss_to_lpass_irq[3]"},
  {36 ,    "vfr"},
  {37 ,    "adsp_ext_vfr_irq"},
  {38 ,    "summary_irq_lpa_dsp"},
  {39 ,    "tsync"},
  {46 ,    "APCS_sysIPCInterrupt[11]"},
  {48 ,    "ee3_lpass_spmi_periph_irq"},
  {49 ,    "channel3_lpass_trans_done_irq"},
  {54 ,    "usb1_hs_irq"},
  {55 ,    "blsp1_bam_irq[1]"},
  {59 ,    "bam_dma_irq[1]"},
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
  {90 ,    "o_timeout_slave_lpass_summary_intr"},
  {96 ,    "crypto_core_irq[0]"},
  {97 ,    "crypto_bam_irq[0]"},
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
    245
  }
};




  
