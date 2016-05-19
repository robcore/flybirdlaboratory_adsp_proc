/*===========================================================================

FILE:         SPMDevCfgData.c

DESCRIPTION:  
  This is the BSP data for the SPM driver.
  This data is for the 9x25 ADSP processor.

                Copyright (c) 2012-2013 QUALCOMM Technologies Incorporated.
                All Rights Reserved.
                Qualcomm Confidential and Proprietary

$Header: //components/rel/core.adsp/2.6.1/power/spm/config/asic/9x35/SPMDevCfgData.c#1 $

============================================================================*/


/* -----------------------------------------------------------------------
**                           INCLUDES
** ----------------------------------------------------------------------- */
#include "BSPspm.h"

/* -----------------------------------------------------------------------
**                           Constants
** ----------------------------------------------------------------------- */


/* -----------------------------------------------------------------------
**             START - QDSP6 SAW2 POWER OUTPUT CONTROL BITS
** The bits are toggled using the bit index (not bitmask). So the initial
** value of each bit at boot time is crucial to the command sequence.
** ----------------------------------------------------------------------- */

typedef enum 
{
  QDSP6_RESET,               /* 0 */
  QDSP6_CLAMP,               /* 1 */
  QDSP6_CLOCK,               /* 2 */
  QDSP6_MEM_SLEEP,           /* 3 */
  QDSP6_BHS,                 /* 4 */
  QDSP6_LDO_BYPASS,          /* 5 */
  QDSP6_LDO,                 /* 6 */
  LPASS_PLL_VOTE,            /* 7 */
  QDSP6_LDO_RET_VREF = 15,   /* 15 */
  QDSP6_CLAMP_WL,            /* 16 */
  QDSP6_CLAMP_QMC_MEM,       /* 17 */
  QPSP6_RESERVED_BIT18,      /* 18 */
  QDSP6_MEM_SRC_BIAS         /* 19 */
} SPM_SEQ_PWR_CTL_BITS;

#define SPM_CMD_BIT7_4(bit)   (((bit) & 0xF) << 4)
#define SPM_CMD_BIT3(bit)     (((bit) & 0x10) >> 1)
#define SPM_CMD_BIT2_1(delay) ((delay) << 1)
#define SPM_SEQ_PWR_CTL(bit,delay) ( SPM_CMD_BIT7_4(bit)   | \
                                     SPM_CMD_BIT3(bit)     | \
                                     SPM_CMD_BIT2_1(delay) ) 

typedef enum
{
  DATA_0,
  DATA_1,
  DATA_2,
} SPM_SEQ_PMIC_DATA_BITS;

#define SPM_SEQ_PMIC_CTL(bit,delay) (bit<<4)|(0x1)
  
typedef enum
{
  NO_RPM_HS,
  RPM_HS
} SPM_SEQ_SLEEP_BITS;

#define SPM_SEQ_SLEEP_CTL(bit,delay) (bit<<2)|(0x3)
  
typedef enum
{
  EVENT_0,
  EVENT_1,
  EVENT_2,
  EVENT_3
} SPM_SEQ_EVENT_BITS;

#define SPM_SEQ_EVENT_CTL(bit,delay) (bit<<4)|(0xB)

#define SPM_SEQ_END_CTL(bit,delay)   (0xF)
    
/* -----------------------------------------------------------------------
**                           TYPES
** ----------------------------------------------------------------------- */

/* -----------------------------------------------------------------------
**                           DATA
** ----------------------------------------------------------------------- */

/*
 * Target specific SPM Hardware configuration.
 */
BSP_spm_ConfigDataType devcfgSpmBspData[] =
{
  {
    /* Saw2SecureCfg
     * ------------
     * sawCtl                  pwrCtl                   vltCtl */
    {  BSP_SPM_SAW_NONSECURE,  BSP_SPM_SAW_NONSECURE,   BSP_SPM_SAW_NONSECURE },
 
    /* Saw2Cfg
     * ------
     * frcRefClkOn  clkDiv   */     
    {  0x0,         0x1F },

    /* Saw2SpmCtlCfg
     * ------------
     * inhibitStartAddrReset wakeupConfig */
    {  0x0,                  BSP_SPM_SAW_WAKEUP_CONFIG_0 },

    /* Saw2SpmDlyType
     * -------------
     * delay_1, delay_2, delay_3 */
    {  0x0,     0x0,     0x0 },

    /* Saw2SpmPmicData[]
     * ----------
     *  pmicSel                      , pmicData, pmicDly, pmicDataSize, adrIdx */
    {
      { BSP_SPM_SAW_PMIC_DATA_NOMINAL, 0x80    , 0x7    , 0           , 0 },
      { BSP_SPM_SAW_PMIC_DATA_PC     , 0x00    , 0x0    , 0           , 0 },
      { BSP_SPM_SAW_PMIC_DATA_VDD_MIN, 0x00    , 0x0    , 0           , 0 },
    }
  }
}; /* SPM_BSP_DATA */

/* SPM command sequence for Torino LPASS QDSP6 Power Collapse */
static uint8 spmCmdSeqBHS[] =
{ 
  /* index 0 */
  SPM_SEQ_PWR_CTL   (QDSP6_CLOCK         ,1), /* QDSP6 Clock Off */
  SPM_SEQ_PWR_CTL   (QDSP6_CLAMP         ,0), /* QDSP6 Assert Clamp */
  SPM_SEQ_PWR_CTL   (QDSP6_CLAMP_WL      ,0), /* QDSP6 Assert Clamp WL */
  SPM_SEQ_PWR_CTL   (QDSP6_MEM_SRC_BIAS  ,0), /* QDSP6 Enable Mem Src Bias */
  /* index 4 */
  SPM_SEQ_PWR_CTL   (QDSP6_MEM_SLEEP     ,0), /* QDSP6 Assert Mem Sleep */
  SPM_SEQ_PWR_CTL   (QDSP6_CLAMP_QMC_MEM ,0), /* QDSP6 QMC Mem Clamp */
  SPM_SEQ_PWR_CTL   (QDSP6_LDO_BYPASS    ,0), /* Force LDO Bypass Off */
  SPM_SEQ_PWR_CTL   (QDSP6_BHS           ,0), /* Force BHS Off */
  /* index 8 */
  SPM_SEQ_PWR_CTL   (QDSP6_LDO           ,0), /* Force LDO Off */
  SPM_SEQ_PWR_CTL   (LPASS_PLL_VOTE      ,0), /* Vote to turn Off LPASS PLL */
  SPM_SEQ_SLEEP_CTL (NO_RPM_HS           ,0), /* Init Sleep to NO RPM HS */
  SPM_SEQ_PWR_CTL   (LPASS_PLL_VOTE      ,0), /* Vote to turn On LPASS PLL */
  /* index 12 */
  SPM_SEQ_PWR_CTL   (QDSP6_RESET         ,0), /* Assert Reset */
  SPM_SEQ_PWR_CTL   (QDSP6_LDO           ,0), /* De-assert Force LDO Off */
  SPM_SEQ_PWR_CTL   (QDSP6_BHS           ,1), /* De-assert Force BHS Off */
  SPM_SEQ_PWR_CTL   (QDSP6_LDO_BYPASS    ,0), /* De-assert LDO Bypass Off */
  /* index 16 */
  SPM_SEQ_PWR_CTL   (QDSP6_CLAMP_QMC_MEM ,0), /* Assert QMC Mem Clamp */
  SPM_SEQ_PWR_CTL   (QDSP6_MEM_SLEEP     ,0), /* QDSP6 De-assert Mem Sleep */
  SPM_SEQ_PWR_CTL   (QDSP6_MEM_SRC_BIAS  ,0), /* QDSP6 Disable Mem Src Bias */
  SPM_SEQ_PWR_CTL   (QDSP6_CLAMP_WL      ,0), /* QDSP6 Assert Clamp WL */
  /* index 20 */
  SPM_SEQ_PWR_CTL   (QDSP6_CLAMP         ,0), /* QDSP6 De-assert Clamp */
  SPM_SEQ_PWR_CTL   (QDSP6_RESET         ,0), /* De-assert Reset */
  SPM_SEQ_EVENT_CTL (EVENT_0             ,0), /* Wait for PLL Lock */
  SPM_SEQ_PWR_CTL   (QDSP6_CLOCK         ,0), /* QDSP6 Clock On */
  SPM_SEQ_END_CTL   (0                   ,0), /* End of Program */
};

/*                                                              
 * Array of SPM command sequences.
 */
BSP_spm_CmdSequenceType devcfgSpmCmdSeqArray[][SPM_NUM_LOW_POWER_MODES] =
{
  /* ADSP has only one core */
  {
    { 
      SPM_MODE_PWRC,
      spmCmdSeqBHS,
      sizeof(spmCmdSeqBHS),
      10, /* Index of the RPM handshake mode cmd in the command sequence array */
      -1
    }
  }
};

