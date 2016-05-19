/*===========================================================================

FILE:         BSPspm.c

DESCRIPTION:  
  This is the BSP data for the SPM driver.
  This data is for the 8960 Riva processor.

                Copyright (c) 2010-2012 Qualcomm Technologies Incorporated.
                All Rights Reserved.
                Qualcomm Confidential and Proprietary

$Header: //components/rel/core.adsp/2.6.1/power/spm/config/asic/8974/SPMDevCfgData.c#1 $

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
  QDSP6_RESET,
  QDSP6_CLAMP,
  QDSP6_CLOCK,
  QDSP6_MEM_SLEEP,
  QDSP6_BHS,
  QDSP6_RES5,
  QDSP6_RES6,
} SPM_SEQ_PWR_CTL_BITS;

#define SPM_SEQ_PWR_CTL(bit,delay) (bit<<4)|(delay<<1)|(0x0)

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
    /* SawSecureCfg
     * ------------
     * sawCtl                  pwrCtl                   vltCtl */
    {  BSP_SPM_SAW_NONSECURE,  BSP_SPM_SAW_NONSECURE,   BSP_SPM_SAW_NONSECURE },
 
    /* SawCfg
     * ------
     * frcRefClkOn  clkDiv   */     
    {  0x0,         0x1F },

    /* SawSpmCtlCfg
     * ------------
     * inhibitStartAddrReset wakeupConfig */
    {  0x0,                  BSP_SPM_SAW_WAKEUP_CONFIG_0 },

    /* SawSpmDlyType
     * -------------
     * delay_1, delay_2, delay_3 */
    {  0x0,     0x0,     0x0 },

    /* SawSpmPmicData[]
     * ----------
     *  pmicSel                      , pmicData, pmicDly, pmicDataSize, adrIdx */
    {
      { BSP_SPM_SAW_PMIC_DATA_NOMINAL, 0x80    , 0x7    , 0           , 0 },
      { BSP_SPM_SAW_PMIC_DATA_PC     , 0x00    , 0x0    , 0           , 0 },
      { BSP_SPM_SAW_PMIC_DATA_VDD_MIN, 0x00    , 0x0    , 0           , 0 },
    }
  }
}; /* SPM_BSP_DATA */


/* SPM command sequence for Modem QDSP6 PC without RPM Handshake */
static uint8 spmCmdSeqBHS[] =
{ /* index 0 */
  SPM_SEQ_PWR_CTL   (QDSP6_CLOCK     ,1), /* QDSP6 Clock Off    */
  SPM_SEQ_PWR_CTL   (QDSP6_CLAMP    ,1),  /* QDSP6 Assert Clamp */
  SPM_SEQ_PWR_CTL   (QDSP6_MEM_SLEEP,1),  /* QDSP6 Memory Sleep */
  SPM_SEQ_PWR_CTL   (QDSP6_BHS       ,1), /* QDSP6 BHS */
  /* index 4 */
  SPM_SEQ_SLEEP_CTL (NO_RPM_HS       ,0), /*-SLEEP-NO-RPM-HS----*/
  SPM_SEQ_PWR_CTL   (QDSP6_RESET     ,1), /* QDSP6 Assert Reset */
  SPM_SEQ_PWR_CTL   (QDSP6_BHS       ,1), /* QDSP6 BHS */
  SPM_SEQ_PWR_CTL   (QDSP6_MEM_SLEEP ,1), /* De-assert QDSP6 Memory Sleep */
  /* index 8 */
  SPM_SEQ_PWR_CTL   (QDSP6_CLAMP    ,1),  /* De-assert QDSP6 Clamp        */
  SPM_SEQ_PWR_CTL   (QDSP6_RESET    ,1),  /* QDSP6 Assert Reset */
  SPM_SEQ_PWR_CTL   (QDSP6_CLOCK    ,1),  /* Turn ON QDSP6 Clock          */
  SPM_SEQ_END_CTL   (0              ,0),  /* End of Program               */
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
      4, /* Index of the RPM handshake mode cmd in the command sequence array */
      -1
    }
  }
};

