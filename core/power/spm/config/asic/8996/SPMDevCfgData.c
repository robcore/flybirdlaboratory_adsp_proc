/*===========================================================================

FILE:         SPMDevCfgData.c

DESCRIPTION:  This is the BSP data for the SPM driver. The data is for the 
              8996 LPASS processor.

              Copyright (c) 2014 QUALCOMM Technologies Incorporated.
              All Rights Reserved.
              Qualcomm Confidential and Proprietary

$Header: //components/rel/core.adsp/2.6.1/power/spm/config/asic/8996/SPMDevCfgData.c#1 $

============================================================================*/


/*==========================================================================
 *                            INCLUDES
 *==========================================================================*/
#include "BSPspm.h"

/*==========================================================================
 *                         INTERNAL TYPES
 *=========================================================================*/

/**
 * @brief Enumeration containing SPM control signal mapping for this target.
 *
 * The bits are toggled using the bit index (not bitmask)
 */
typedef enum 
{
  QDSP6_RESET,               /* 0 */
  QDSP6_CLAMP,               /* 1 */
  QDSP6_CLOCK,               /* 2 */
  QDSP6_MEM_SLEEP,           /* 3 */
  QDSP6_BHS,                 /* 4 */
  QDSP6_LDO_BYPASS,          /* 5 */
  QDSP6_LDO,                 /* 6 */
  QDSP6_PLL_VOTE,            /* 7 */
  QDSP6_SMMU_PD_VOTE = 13,   /* 13 */
  QDSP6_CLAMP_WL = 16,       /* 16 */
  QDSP6_QMC_MEM_CLAMP,       /* 17 */
  QDSP6_MEM_SRC_BIAS = 19,   /* 19 */
  QDSP6_RETAIN_SAVE,         /* 20 */
  QDSP6_RETAIN_RESTORE,      /* 21 */
  QDSP6_PMI,                 /* 22 */
  QDSP6_MEM_RET_SLEEP = 30   /* 30 */
} SPM_SEQ_PWR_CTL_BITS;

/**
 * @brief Set of macros to create SPM command to toggle power control bits
 *        defined in @SPM_SEQ_PWR_CTL_BITS
 */
#define SPM_CMD_BIT7_4(bit)   (((bit) & 0xF) << 4)
#define SPM_CMD_BIT3(bit)     (((bit) & 0x10) >> 1)
#define SPM_CMD_BIT2_1(delay) ((delay) << 1)
#define SPM_SEQ_PWR_CTL(bit,delay) ( SPM_CMD_BIT7_4(bit)   | \
                                     SPM_CMD_BIT3(bit)     | \
                                     SPM_CMD_BIT2_1(delay) ) 

/**
 * @brief Enumeration to indicate bit for different PMIC data in 
 *        SPM command.
 */
typedef enum
{
  DATA_0,
  DATA_1,
  DATA_2,
} SPM_SEQ_PMIC_DATA_BITS;

/**
 * @brief Macro to create SPM command to send PMIC data based on 
 *        @SPM_SEQ_PMIC_DATA_BITS.
 */
#define SPM_SEQ_PMIC_CTL(bit,delay) (bit<<4)|(0x1)

/**
 * @brief Enumeration to indicate bit settings for RPM interaction
 *        during Sleep in SPM command.
 */
typedef enum
{
  NO_RPM_HS,
  RPM_HS
} SPM_SEQ_SLEEP_BITS;

/**
 * @brief Macro to set up SPM command for RPM interaction while waiting for
 *        wake up event.
 */
#define SPM_SEQ_SLEEP_CTL(bit,delay) (bit<<2)|(0x3)

/**
 * @brief Event bits for SPM command.
 */
typedef enum
{
  EVENT_0,
  EVENT_1,
  EVENT_2,
  EVENT_3,
  EVENT_4
} SPM_SEQ_EVENT_BITS;

/**
 * @brief Macro to create SPM command to wait for events defined in 
 *        @SPM_SEQ_EVENT_BITS.
 */
#define SPM_SEQ_EVENT_CTL(bit,delay) (bit<<4)|(0xB)

/**
 * @brief Enumeration to be used for delay field selection.
 */ 
typedef enum
{
  DLY_1 = 1,
  DLY_2,
  DLY_3
} SPM_SEQ_DLY_BITS;

/**
 * @brief Macro to create SPM command for waiting by time specified
 *        in delay registers.
 */ 
#define SPM_SEQ_DLY_CTL(bit, unused) (((bit & 0x7) << 4)|(0xF))

/**
 * @brief SPM end of sequence command.
 */
#define SPM_SEQ_END_CTL(bit,delay)   (0xF)

/*==========================================================================
 *                                   NOTE
 *=========================================================================*/

/**
 * Even though different low power modes share some commands, for some 
 * of them actual impact at the HW level will be determined by special control
 * registers values (e.g. SPMCTL) which are programmed as part of enter 
 * functions of low power modes. Below is the list of such known 
 * commands/toggles.
 *
 * QDSP6_RESET
 * -----------
 * Depending on how SPMCTL_EN_ARES register is programed, this command may 
 * reset core differently (partially or full).
 * 
 * QDSP6_RETAIN_SAVE
 * -----------------
 * If SAVE field in SPMCTL_EN_STATERET is programed zero, this command/toggle 
 * may not take impact. (For example in Power collapse - but we removed this 
 * toggle itself from sequence).
 *
 * QDSP6_RETAIN_RESTORE 
 * --------------------
 * Same as QDSP6_RETAIN_SAVE but with RESTORE field.
 *
 * QDSP6_PMI
 * ---------
 * Same as QDSP6_RETAIN_SAVE but with WAKEUP_IRQ field.
 */
    
/*==========================================================================
 *                                   DATA
 *=========================================================================*/

/**
 * @brief Target specific SPM Hardware configuration.
 */
BSP_spm_ConfigDataType devcfgSpmBspData[] =
{
  {
    /* Saw3SecureCfg
     * ------------
     * sawCtl                  pwrCtl                   vltCtl */
    {  BSP_SPM_SAW_NONSECURE,  BSP_SPM_SAW_NONSECURE,   BSP_SPM_SAW_NONSECURE },
 
    /* Saw3Cfg
     * ------
     * frcRefClkOn  clkDiv   */     
    {  0x0,         0x1F },

    /* Saw3SpmCtlCfg
     * ------------
     * inhibitStartAddrReset wakeupConfig */
    {  0x1,                  BSP_SPM_SAW_WAKEUP_CONFIG_0 },

    /* Saw3SpmDlyType
     * -------------
     * delay_1, delay_2, delay_3 */
    {  0x0,     0x0,     0x0 },

    /* Saw3SpmPmicData[]
     * ----------
     *  pmicSel                      , pmicData, pmicDly, pmicDataSize, adrIdx */
    {
      { BSP_SPM_SAW_PMIC_DATA_NOMINAL, 0x0     , 0x0    , 0           , 0 },
      { BSP_SPM_SAW_PMIC_DATA_PC     , 0x0     , 0x0    , 0           , 0 },
      { BSP_SPM_SAW_PMIC_DATA_VDD_MIN, 0x0     , 0x0    , 0           , 0 },
    }
  }
}; /* SPM_BSP_DATA */

/**
 * @brief SPM command sequence for ADSP APCR with PLL on
 */
static uint8 spmCmdSeqAPCRPLLOn[] =
{ 
  /* index 0x0 */
  SPM_SEQ_PWR_CTL( QDSP6_CLOCK, 0 ),          /* QDSP6 Clock Off */
  SPM_SEQ_PWR_CTL( QDSP6_CLAMP, 0 ),          /* QDSP6 Assert Clamp */
  SPM_SEQ_PWR_CTL( QDSP6_RETAIN_SAVE, 0 ),    /* Assert QDSP6 retain save*/
  SPM_SEQ_PWR_CTL( QDSP6_RETAIN_SAVE, 0 ),    /* Deassert QDSP6 retain save */

  /* index 0x4 */  
  SPM_SEQ_PWR_CTL( QDSP6_CLAMP_WL, 0 ),       /* QDSP6 Assert Clamp WL */
  SPM_SEQ_PWR_CTL( QDSP6_MEM_RET_SLEEP, 0 ),  /* Retention memory sleep */
  SPM_SEQ_DLY_CTL( DLY_1, 0 ),                /* Delay for in-rush current */
  SPM_SEQ_PWR_CTL( QDSP6_QMC_MEM_CLAMP, 0 ),  /* QDSP6 QMC Mem Clamp */
  
  /* index 0x8 */  
  SPM_SEQ_PWR_CTL( QDSP6_LDO_BYPASS, 0 ),     /* Force LDO Bypass Off */
  SPM_SEQ_PWR_CTL( QDSP6_BHS, 1 ),            /* Force BHS Off */
  SPM_SEQ_PWR_CTL( QDSP6_LDO, 0 ),            /* Force LDO Off */
  SPM_SEQ_SLEEP_CTL( NO_RPM_HS, 0 ),          /* Init Sleep to NO RPM HS */
  
  /* index 0xC */  
  SPM_SEQ_PWR_CTL( QDSP6_RESET, 0 ),          /* Assert Reset */
  SPM_SEQ_PWR_CTL( QDSP6_LDO, 0 ),            /* Deassert LDO Off */
  SPM_SEQ_PWR_CTL( QDSP6_BHS, 1 ),            /* Deassert BHS Off */
  SPM_SEQ_PWR_CTL( QDSP6_LDO_BYPASS, 0 ),     /* Deassert LDO Bypass Off */
  
  /* index 0x10 */  
  SPM_SEQ_PWR_CTL( QDSP6_QMC_MEM_CLAMP, 0 ),  /* Deassert QMC Mem Clamp */
  SPM_SEQ_PWR_CTL( QDSP6_MEM_RET_SLEEP, 1 ),  /* Retention memory sleep */
  SPM_SEQ_PWR_CTL( QDSP6_CLAMP_WL, 0 ),       /* Deassert QDSP6 Clamp WL */
  SPM_SEQ_PWR_CTL( QDSP6_RETAIN_RESTORE, 0 ), /* Assert QDSP6 retain restore */
  
  /* index 0x14 */
  SPM_SEQ_PWR_CTL( QDSP6_RETAIN_RESTORE, 0 ), /* Deassert QDSP6 retain restore */
  SPM_SEQ_PWR_CTL( QDSP6_CLAMP, 0 ),          /* Deassert QDSP6 Clamp */
  SPM_SEQ_PWR_CTL( QDSP6_RESET, 0 ),          /* Deassert Reset */
  SPM_SEQ_PWR_CTL( QDSP6_PMI, 0 ),            /* Assert Power Manager Interrupt (PMI) */

  /* index 0x18 */  
  SPM_SEQ_PWR_CTL( QDSP6_PMI, 0 ),            /* Deassert PMI */
  SPM_SEQ_PWR_CTL( QDSP6_CLOCK, 0 ),          /* Deassert QDSP6 Clock Off */
  SPM_SEQ_END_CTL( 0, 0 ),                    /* End of Program */
};

/**
 * @brief SPM command sequence for ADSP APCR PLL in low power mode.
 */
static uint8 spmCmdSeqAPCRPLLLPM[] =
{
  /* index 0x0 */
  SPM_SEQ_PWR_CTL( QDSP6_CLOCK, 1 ),         /* QDSP6 Clock Off */
  SPM_SEQ_EVENT_CTL( EVENT_2, 0 ),           /* Wait for clock off event */
  SPM_SEQ_PWR_CTL( QDSP6_CLAMP, 0 ),         /* Assert clamp */
  SPM_SEQ_PWR_CTL( QDSP6_RETAIN_SAVE, 0 ),   /* Assert QDSP6 retain save */

  /* index 0x4 */
  SPM_SEQ_PWR_CTL( QDSP6_RETAIN_SAVE, 0 ),   /* Deassert QDSP6 retain save */
  SPM_SEQ_PWR_CTL( QDSP6_CLAMP_WL, 0 ),      /* Assert QDSP6 Clamp WL */
  SPM_SEQ_PWR_CTL( QDSP6_MEM_SRC_BIAS, 0 ),  /* Assert memory biasing */
  SPM_SEQ_PWR_CTL( QDSP6_MEM_RET_SLEEP, 0 ), /* Assert ret memory sleep */

  /* index 0x8 */  
  SPM_SEQ_PWR_CTL( QDSP6_MEM_SLEEP, 1 ),     /* Assert non ret memory sleep */
  SPM_SEQ_PWR_CTL( QDSP6_QMC_MEM_CLAMP, 0 ), /* Assert Q6 memory clamp */
  SPM_SEQ_PWR_CTL( QDSP6_LDO_BYPASS, 0 ),    /* Assert LDO bypass */
  SPM_SEQ_PWR_CTL( QDSP6_BHS, 0 ),           /* Assert BHS off */

  /* index 0xC */  
  SPM_SEQ_PWR_CTL( QDSP6_LDO, 0 ),           /* Assert LDO off */
  SPM_SEQ_PWR_CTL( QDSP6_SMMU_PD_VOTE, 0 ),  /* Vote off SMMU GDHS */
  SPM_SEQ_PWR_CTL( QDSP6_PLL_VOTE, 0 ),      /* LPASS vote on PLL mode */
  SPM_SEQ_SLEEP_CTL( NO_RPM_HS, 0 ),         /* Sleep w/o RPM handshake */

  /* index 0x10 */   
  SPM_SEQ_PWR_CTL( QDSP6_RESET, 0 ),         /* Assert QDSP6 reset */
  SPM_SEQ_PWR_CTL( QDSP6_PLL_VOTE, 0 ),      /* LPASS vote on PLL restore */
  SPM_SEQ_PWR_CTL( QDSP6_SMMU_PD_VOTE, 0 ),  /* Vote off SMMU GDHS */  
  SPM_SEQ_PWR_CTL( QDSP6_LDO, 0 ),           /* Deassert LDO force off */

  /* index 0x14 */  
  SPM_SEQ_PWR_CTL( QDSP6_BHS, 1 ),           /* Deassert BHS off */
  SPM_SEQ_PWR_CTL( QDSP6_LDO_BYPASS, 0 ),    /* Deassert LDO Bypass off */
  SPM_SEQ_PWR_CTL( QDSP6_QMC_MEM_CLAMP, 0 ), /* Deassert QMC memory clamp */
  SPM_SEQ_PWR_CTL( QDSP6_MEM_SLEEP, 1 ),     /* Deassert non ret memory sleep */

  /* index 0x18 */  
  SPM_SEQ_PWR_CTL( QDSP6_MEM_RET_SLEEP, 1 ), /* Deassert ret memory sleep */
  SPM_SEQ_PWR_CTL( QDSP6_MEM_SRC_BIAS, 0 ),  /* Deassert source biasing */
  SPM_SEQ_PWR_CTL( QDSP6_CLAMP_WL, 0 ),      /* Deassert QDSP6 Clamp WL */
  SPM_SEQ_PWR_CTL( QDSP6_RETAIN_RESTORE, 0 ),/* Assert QDSP6 retain restore */

  /* index 0x1C */  
  SPM_SEQ_PWR_CTL( QDSP6_RETAIN_RESTORE, 0 ),/* Deassert QDSP6 retain restore */
  SPM_SEQ_PWR_CTL( QDSP6_CLAMP, 0 ),         /* Deassert QDSP6 clamp */
  SPM_SEQ_PWR_CTL( QDSP6_RESET, 0 ),         /* Deassert QDSP6 reset */
  SPM_SEQ_PWR_CTL( QDSP6_PMI, 0 ),           /* Assert PMI */

  /* index 0x20 */  
  SPM_SEQ_PWR_CTL( QDSP6_PMI, 0 ),           /* Deassert PMI */
  SPM_SEQ_EVENT_CTL( EVENT_0, 0 ),           /* Wait for PLL lock */
  SPM_SEQ_EVENT_CTL( EVENT_4, 0 ),           /* Wait for SMMU power up */
  SPM_SEQ_PWR_CTL( QDSP6_CLOCK, 0 ),         /* Deassert Clock off */

  /* index 0x24 */  
  SPM_SEQ_END_CTL( 0, 0 )                    /* End of command sequence */
};

/**
 * @brief SPM command sequence for ADSP APCR PLL in low power mode.
 */
static uint8 spmCmdSeqBHS[] =
{
  /* index 0x0 */
  SPM_SEQ_PWR_CTL( QDSP6_CLOCK, 1 ),         /* QDSP6 Clock Off */
  SPM_SEQ_EVENT_CTL( EVENT_2, 0 ),           /* Wait for clock off event */
  SPM_SEQ_PWR_CTL( QDSP6_CLAMP, 0 ),         /* Assert clamp */
  SPM_SEQ_PWR_CTL( QDSP6_CLAMP_WL, 0 ),      /* Assert QDSP6 Clamp WL */

  /* index 0x4 */
  SPM_SEQ_PWR_CTL( QDSP6_MEM_SRC_BIAS, 0 ),  /* Assert memory biasing */
  SPM_SEQ_PWR_CTL( QDSP6_MEM_RET_SLEEP, 0 ), /* Assert ret memory sleep */
  SPM_SEQ_PWR_CTL( QDSP6_MEM_SLEEP, 0 ),     /* Assert non ret memory sleep */
  SPM_SEQ_PWR_CTL( QDSP6_QMC_MEM_CLAMP, 0 ), /* Assert Q6 memory clamp */

  /* index 0x8 */
  SPM_SEQ_PWR_CTL( QDSP6_LDO_BYPASS, 0 ),    /* Assert LDO bypass */
  SPM_SEQ_PWR_CTL( QDSP6_BHS, 0 ),           /* Assert BHS off */
  SPM_SEQ_PWR_CTL( QDSP6_LDO, 0 ),           /* Assert LDO off */
  SPM_SEQ_PWR_CTL( QDSP6_SMMU_PD_VOTE, 0 ),  /* Vote for SMMU GDHS */

  /* index 0xC */
  SPM_SEQ_PWR_CTL( QDSP6_PLL_VOTE, 0 ),      /* LPASS vote on PLL mode */
  SPM_SEQ_SLEEP_CTL( NO_RPM_HS, 0 ),         /* Sleep w/o RPM handshake */
  SPM_SEQ_PWR_CTL( QDSP6_RESET, 0 ),         /* Assert QDSP6 reset */
  SPM_SEQ_PWR_CTL( QDSP6_PLL_VOTE, 0 ),      /* LPASS vote on PLL restore */

  /* index 0x10 */
  SPM_SEQ_PWR_CTL( QDSP6_SMMU_PD_VOTE, 0 ),  /* Vote for SMMU GDHS */
  SPM_SEQ_PWR_CTL( QDSP6_LDO, 0 ),           /* Deassert LDO force off */
  SPM_SEQ_PWR_CTL( QDSP6_BHS, 1 ),           /* Deassert BHS off */
  SPM_SEQ_PWR_CTL( QDSP6_LDO_BYPASS, 0 ),    /* Deassert LDO Bypass off */

  /* index 0x14 */  
  SPM_SEQ_PWR_CTL( QDSP6_QMC_MEM_CLAMP, 0 ), /* Deassert QMC memory clamp */
  SPM_SEQ_PWR_CTL( QDSP6_MEM_SLEEP, 1 ),     /* Deassert non ret memory sleep */
  SPM_SEQ_PWR_CTL( QDSP6_MEM_RET_SLEEP, 1),  /* Deassert ret memory sleep */
  SPM_SEQ_PWR_CTL( QDSP6_MEM_SRC_BIAS, 0 ),  /* Deassert source biasing */

  /* index 0x18 */  
  SPM_SEQ_PWR_CTL( QDSP6_CLAMP_WL, 0 ),      /* Deassert QDSP6 Clamp WL */
  SPM_SEQ_PWR_CTL( QDSP6_CLAMP, 0 ),         /* Deassert QDSP6 clamp */
  SPM_SEQ_PWR_CTL( QDSP6_RESET, 0 ),         /* Deassert QDSP6 reset */
  SPM_SEQ_EVENT_CTL( EVENT_0, 0 ),           /* Wait for PLL lock */

  /* index 0x1C */  
  SPM_SEQ_EVENT_CTL( EVENT_4, 0 ),           /* Wait for SMMU power up */
  SPM_SEQ_PWR_CTL( QDSP6_CLOCK, 0 ),         /* Deassert Clock off */
  SPM_SEQ_END_CTL( 0, 0 )                    /* End of command sequence */
};

/**
 * @brief Array containing SPM command sequences for supported low power
 *        modes and associated information.
 */
BSP_spm_CmdSequenceType devcfgSpmCmdSeqArray[][SPM_NUM_LOW_POWER_MODES] =
{
  /* ADSP has only one core */
  {
    { 
      SPM_MODE_APCR_PLL_ON,
      spmCmdSeqAPCRPLLOn,
      sizeof(spmCmdSeqAPCRPLLOn),
      11, /* Index of the RPM handshake cmd in the command sequence array */
      -1
    },
    {
      SPM_MODE_APCR_PLL_LPM,
      spmCmdSeqAPCRPLLLPM,
      sizeof(spmCmdSeqAPCRPLLLPM),
      15, /* Index of the RPM handshake cmd in the command sequence array */
      -1
    },
    {
      SPM_MODE_PWRC,
      spmCmdSeqBHS,
      sizeof(spmCmdSeqBHS),
      13, /* Index of the RPM handshake cmd in the command sequence array */
      -1
    }
  }
};

