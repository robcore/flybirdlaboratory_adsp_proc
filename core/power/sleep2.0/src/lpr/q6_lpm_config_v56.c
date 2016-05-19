/*==============================================================================
  FILE:         q6_lpm_config_v55.c

  OVERVIEW:     This file implements the APIs from q6_lpm_config header file
                on ADSP/LPASS subsystems for Q6v56 version. It may be 
                shared for targets with same Q6 version.

  NOTE:         This file depends on how Q6 core is integrated within a 
                subystem. So LPASS/ADSP implementation may vary from MPSS.

  DEPENDENCIES: None

                Copyright (c) 2014 QUALCOMM Technologies Incorporated.
                All Rights Reserved.
                Qualcomm Confidential and Proprietary
================================================================================
$Header: //components/rel/core.adsp/2.6.1/power/sleep2.0/src/lpr/q6_lpm_config_v56.c#1 $
$DateTime: 2014/10/16 12:45:40 $
==============================================================================*/

#include "DALStdDef.h"
#include "spm.h"
#include "q6_lpm_config.h"
#include "HALhwio.h"
#include "HALsleep_hwio.h"
#include "CoreVerify.h"

/*==============================================================================
 *                             GLOBAL FUNCTIONS
 *============================================================================*/

/**
 * q6LPMConfig_setupBase
 */
void q6LPMConfig_setupBase(void)
{
  /* Configure Q6SS registers as HPG recommended. */
  HWIO_OUT( LPASS_QDSP6SS_SPMCTL_EN_CLAMP, 0x01 );
  HWIO_OUT( LPASS_QDSP6SS_SPMCTL_EN_CLK,   0x7F );
  HWIO_OUT( LPASS_QDSP6SS_SPMCTL_EN_BHS,   0x01 ); 
  HWIO_OUT( LPASS_QDSP6SS_SPMCTL_EN_LDO,   
            HWIO_FVAL( LPASS_QDSP6SS_SPMCTL_EN_LDO, VREF_SEL,    0x0 ) |
            HWIO_FVAL( LPASS_QDSP6SS_SPMCTL_EN_LDO, FORCEOFF,    0x1 ) |
            HWIO_FVAL( LPASS_QDSP6SS_SPMCTL_EN_LDO, FORCEON,     0x0 ) |
            HWIO_FVAL( LPASS_QDSP6SS_SPMCTL_EN_LDO, BYPASS_OPEN, 0x1 ) );

  /* Configure LPASS Q6 PLL for OFF MODE.
   * There are two types of modes
   *   1) Don't vote for Q6 PLL off: "clk_gate" and "apcr". These modes will 
   *      not have spm commands for voting pll off.
   *   2) Vote for Q6 PLL off : "apcr_pll_lpm" and "pc_l2_noret". These modes
   *      will have spm commands to vote for pll off.
   *
   * By configuring Q6 PLL related registers for OFF at init time, we 
   * eliminate the need to perform PLL configuration as part of any mode's
   * enter function. */
  HWIO_OUT( LPASS_QDSP6SS_SPMCTL_EN_PLL, 
            HWIO_FVAL( LPASS_QDSP6SS_SPMCTL_EN_PLL, PLL_FREEZE, 0x1 ) |
            HWIO_FVAL( LPASS_QDSP6SS_SPMCTL_EN_PLL, PLL_VOTE,   0x1 ) |
            HWIO_FVAL( LPASS_QDSP6SS_SPMCTL_EN_PLL, PLL_OUTDIS, 0x1 ) |
            HWIO_FVAL( LPASS_QDSP6SS_SPMCTL_EN_PLL, PLL_BYPASS, 0x1 ) |
            HWIO_FVAL( LPASS_QDSP6SS_SPMCTL_EN_PLL, PLL_RESET,  0x1 ) );
}

/**
 * q6LPMConfig_setupModeConfig
 *
 * Based on QDSP6v56 HPG
 *
 * Reg[Field]                       PC     APCR     APCRCached     ClockGating
 *
 * SLPC_CFG[WAKEUP_IN_EN]           0        1          1              0
 *   Enables QDSP6_wakeup_in
 *   handshaking signal.
 *
 * SLPC_CFG[CLK_GATING_MODE]        0        0          0              1
 *   Bit to indicate clock 
 *   gating only on allwait.
 * 
 * STATERET[WAKE_IRQ]               0        1          0              0
 *   If 1, PMI interrupt is
 *   triggered from spm exit
 *   sequence, else not.
 * 
 * STATERET[SAVE|RESTORE]           0        1          1              0
 *   If 1, Q6 state save/restore   
 *   is needed around core off,   
 *   else not.
 * 
 * SPMCTL_EN_ARES                  0x1FF    0x7F       0x7F            0
 *   Async reset of various
 *   subcomponents indicated
 *   by each bit of this reg.
 */
void q6LPMConfig_setupModeConfig( spm_low_power_mode_type coreMode, 
                                  boolean triggerPMI )
{
  uint32 wakeup_in_en;
  uint32 clk_gating_mode; 
  uint32 wake_irq;
  uint32 save_restore;
  uint32 en_ares;
  uint32 spm_config_lpm;

  switch( coreMode )
  {
    case SPM_MODE_APCR_PLL_ON:
    case SPM_MODE_APCR_PLL_LPM:
    {
      wakeup_in_en    = 0x1;
      clk_gating_mode = 0x0;
      wake_irq        = ( triggerPMI == TRUE ) ? 0x1 : 0x0;
      save_restore    = 0x1;
      en_ares         = 0x7F;
      spm_config_lpm  = 0x1; /* Configure SPM low-power mode */
      break;
    }
    case SPM_MODE_PWRC:
    {
      wakeup_in_en    = 0x0;
      clk_gating_mode = 0x0;
      wake_irq        = 0x0;
      save_restore    = 0x0;
      en_ares         = 0x1FF;
      spm_config_lpm  = 0x1; /* Configure SPM low-power mode */
      break;
    }
    case SPM_MODE_CLK_GATE:
    {
      wakeup_in_en    = 0x0; 
      clk_gating_mode = 0x1;
      wake_irq        = 0x0; 
      save_restore    = 0x0; 
      en_ares         = 0x0; 
      spm_config_lpm  = 0x0; /* SPM configuration not required */
      break;
    }
    default:
    {
      CORE_VERIFY(0);
      break;
    }
  }
  
  HWIO_OUT( LPASS_QDSP6SS_SLPC_CFG, 
            HWIO_FVAL( LPASS_QDSP6SS_SLPC_CFG, WAKEUP_IN_EN,    wakeup_in_en    ) |
            HWIO_FVAL( LPASS_QDSP6SS_SLPC_CFG, SLP_DELAY_CTL,   0x1             ) |
            HWIO_FVAL( LPASS_QDSP6SS_SLPC_CFG, CLK_GATING_MODE, clk_gating_mode ) |
            HWIO_FVAL( LPASS_QDSP6SS_SLPC_CFG, PD_HS_MODE,      0x1             ) |
            HWIO_FVAL( LPASS_QDSP6SS_SLPC_CFG, SAW_DBG,         0x0             ) |
            HWIO_FVAL( LPASS_QDSP6SS_SLPC_CFG, PD_SRC_SEL,      0x0             ) |
            HWIO_FVAL( LPASS_QDSP6SS_SLPC_CFG, EXT_WAKEUP_ENA,  0x0             ) );

  HWIO_OUT( LPASS_QDSP6SS_SPMCTL_EN_STATERET,
            HWIO_FVAL( LPASS_QDSP6SS_SPMCTL_EN_STATERET, WAKE_IRQ, wake_irq     ) |
            HWIO_FVAL( LPASS_QDSP6SS_SPMCTL_EN_STATERET, RESTORE,  save_restore ) |
            HWIO_FVAL( LPASS_QDSP6SS_SPMCTL_EN_STATERET, SAVE,     save_restore ) );

  HWIO_OUT( LPASS_QDSP6SS_SPMCTL_EN_ARES, en_ares );

  /* Configure SPM if required by lprm */
  if ( spm_config_lpm )
  { 
    spm_set_low_power_mode( 0, coreMode );
  } 
}

/**
 * q6LPMConfig_setupL2NonRetConfig
 */
void q6LPMConfig_setupL2NonRetConfig(void)
{
  /* Preparing reg value from Q6 HPG 80-N1733-6H Rev.A - 
   * With this configuration, cache related logic can be turned off/reset. */
  const uint32 regNonRetSPMCtlEnMem = 
    ( HWIO_FVAL(LPASS_QDSP6SS_SPMCTL_EN_MEM, CLAMP_QMC_MEM, 0x1 ) |
      HWIO_FVAL(LPASS_QDSP6SS_SPMCTL_EN_MEM, CLAMP_WL,      0x1 ) |
      HWIO_FVAL(LPASS_QDSP6SS_SPMCTL_EN_MEM, MEM_PERIPH,    0x1 ) |
      HWIO_FVAL(LPASS_QDSP6SS_SPMCTL_EN_MEM, L2DATA_STBY,   0x0 ) |
      HWIO_FVAL(LPASS_QDSP6SS_SPMCTL_EN_MEM, ETB,           0x1 ) |
      HWIO_FVAL(LPASS_QDSP6SS_SPMCTL_EN_MEM, L2TAG,         0x1 ) |
      HWIO_FVAL(LPASS_QDSP6SS_SPMCTL_EN_MEM, L1IU,          0x1 ) |
      HWIO_FVAL(LPASS_QDSP6SS_SPMCTL_EN_MEM, L1DU,          0x1 ) |
      HWIO_FVAL(LPASS_QDSP6SS_SPMCTL_EN_MEM, L2PLRU,        0x1 ) |
      HWIO_FVAL(LPASS_QDSP6SS_SPMCTL_EN_MEM, L2DATA,        0xFF ) );

  HWIO_OUT(LPASS_QDSP6SS_SPMCTL_EN_MEM, regNonRetSPMCtlEnMem);  
}

/**
 * q6LPMConfig_setupL2RetConfig
 */
void q6LPMConfig_setupL2RetConfig(void)
{
  /* Preparing reg value from Q6 HPG 80-N1733-6H Rev.A - 
   * With this configuration, cache related logic will remain on
   * during core off/reset. */  
  const uint32 regSPMCtlEnMem = 
    ( HWIO_FVAL(LPASS_QDSP6SS_SPMCTL_EN_MEM, CLAMP_QMC_MEM,  0x1) |
      HWIO_FVAL(LPASS_QDSP6SS_SPMCTL_EN_MEM, CLAMP_WL,       0x1) |
      HWIO_FVAL(LPASS_QDSP6SS_SPMCTL_EN_MEM, MEM_PERIPH,     0x1) |
      HWIO_FVAL(LPASS_QDSP6SS_SPMCTL_EN_MEM, L2DATA_STBY,    0x0) |
      HWIO_FVAL(LPASS_QDSP6SS_SPMCTL_EN_MEM, ETB,            0x0) |
      HWIO_FVAL(LPASS_QDSP6SS_SPMCTL_EN_MEM, L2TAG,          0x0) |
      HWIO_FVAL(LPASS_QDSP6SS_SPMCTL_EN_MEM, L1IU,           0x0) |
      HWIO_FVAL(LPASS_QDSP6SS_SPMCTL_EN_MEM, L1DU,           0x0) |
      HWIO_FVAL(LPASS_QDSP6SS_SPMCTL_EN_MEM, L2PLRU,         0x0) |
      HWIO_FVAL(LPASS_QDSP6SS_SPMCTL_EN_MEM, L2DATA,         0x0) );

  HWIO_OUT(LPASS_QDSP6SS_SPMCTL_EN_MEM, regSPMCtlEnMem);
}

