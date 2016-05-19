/*==============================================================================
  FILE:         HALspmPlatform.c

  OVERVIEW:     This is the generic hardware abstraction layer implementation
                for the SPMv2 (SAW2) Hardware.

  DEPENDENCIES: None
  
                Copyright (c) 2010-2014 Qualcomm Technologies, Inc. (QTI).
                All Rights Reserved.
                Qualcomm Technologies Confidential and Proprietary
================================================================================
$Header: //components/rel/core.adsp/2.6.1/power/spm/src/hal/HALspmPlatform.c#1 $
$DateTime: 2014/10/16 12:45:40 $
==============================================================================*/

/* -----------------------------------------------------------------------
**                           INCLUDES
** ----------------------------------------------------------------------- */
#include <stdlib.h>
#include "BSPspm.h"
#include "HALspm.h"
#include "HALspmPlatform.h"
#include "CoreVerify.h"
#include "spm.h"

/* -----------------------------------------------------------------------
**                                TYPES
** ----------------------------------------------------------------------- */
typedef void (*spm_rpm_handshake_ptr_type)(uint32               core_num,
                                           spm_rpm_bypass_type  rpm_bypass);

/* -----------------------------------------------------------------------
**                           Declarations
** ----------------------------------------------------------------------- */
void spm_hwio_mmap(void);

void static HAL_spm_ConfigPMICData 
( 
  uint32 coreNum,
  BSP_spm_PmicModeData pmicMode,
  uint8 pmicData
);

void static HAL_spm_ConfigPMICDelay
( 
  uint32 coreNum,
  BSP_spm_PmicModeData pmicMode,
  uint8 pmicDly
);

void static HAL_spm_ConfigLowPowerMode
( 
  uint32 coreNum,
  BSP_spm_CmdSequenceType *seqData
);

void static HAL_spm_SetLowPowerModeRunTime
(
  uint32 coreNum,
  BSP_spm_CmdSequenceType *seqData
);

static void HALSPM_setRPMHandshakeModeIndex
( 
  uint32 coreNum,
  spm_rpm_bypass_type rpmHandshakeMode
);

static void HALSPM_setRPMHandshakeModeSawctl
(
  uint32               coreNum, 
  spm_rpm_bypass_type  rpmHandshakeMode
) USPM_CODE_SECTION;

/* -----------------------------------------------------------------------
**                           Internal variables
** ----------------------------------------------------------------------- */
/* Set default handshake function to 'index' method. If the saw supports bit-wise
 * setting it will be updated at init time */
static spm_rpm_handshake_ptr_type  g_rpmHandshakeFcn USPM_DATA_SECTION = HALSPM_setRPMHandshakeModeIndex;

/* -----------------------------------------------------------------------
**                           TYPES
** ----------------------------------------------------------------------- */

/* Identifier string for this HAL */
#define HAL_SPM_VERSION_STRING "HAL_SPM_V2"

/* -----------------------------------------------------------------------
**                           DATA
** ----------------------------------------------------------------------- */

/* Consolidated data */
HAL_spm_PlatformType spmPlatform = 
{
  /* Placeholder for BSP config data. */
  NULL,
  /* Placeholders for some custom functions (unused). */
  NULL,
  NULL,
  NULL
};

/**
 * Array containing information about command sequence programming on each spm
 */
static HAL_spm_CSProgramInfoType *csInfo = NULL;

/* -----------------------------------------------------------------------
**                        INTERNAL FUNCTIONS
** ----------------------------------------------------------------------- */

/**
 * Downloads the SPM commands in cmdBlk starting at specified offset into
 * the SPM_SLP_SEQ_ENTRY_n register.
 * 
 * @param coreNum[in]         Which SPM.
 * @param cmdBlk[in]          Command sequence to program
 * @param hwRegByteOffset[in] SPM_SLP_SEQ_ENTRY_n byte offset at which the
 *                            sequence will be loaded.
 * 
 * @return TRUE if successful
 */
static bool32 HAL_spm_WriteCmdBlock
(
  uint32                  coreNum,
  BSP_spm_CmdSequenceType *cmdBlk,
  uint8                   hwRegByteOffset
)
{
  uint32 i = 0;                  /* Index to the command sequence block */
  uint32 tmask = 0;              /* Register mask for a given command */
  uint32 mask = 0;               /* Mask when we actually write to register. It
                                    is 'OR'd value of multiple command masks */
  uint8 cmd = 0;                 /* Command last read from block */
  uint32 cmdShift;               /* Shift for the last command */
  uint32 val = 0;                /* Value that will be written to register. It
                                    is an 'OR'd value of commands */

  uint8 cmdLen = cmdBlk->len;    /* Length of command sequence block */
  uint8 anyCmdCopied = 0;        /* Indicates if we started reading cmd seq */

  const uint8 numCmdSeq = csInfo[coreNum].numRegisters * 
                          SPM_HAL_COMMANDS_PER_REGISTER;

  /* Command sequence of length zero */
  CORE_VERIFY( cmdLen != 0 );

  /* Ensure that we have enough registers left to write this command sequence */
  if( ( hwRegByteOffset >= numCmdSeq ) ||
      ( cmdLen > (numCmdSeq - hwRegByteOffset) ) )
  {
    return FALSE;
  }

  /* Start copying command sequence to spm registers */
  for( i = 0; i < cmdLen; i++, hwRegByteOffset++ )
  {
    switch(hwRegByteOffset % 4)
    {
      case 0:
        /* We reached 4-byte register boundary. Write to actual register if we
         * had copied any command */
        if( 0 != anyCmdCopied )
        {
          SPM_HWIO_OUTMI_W( coreNum, SPM_SLP_SEQ_ENTRY_n, 
                            ((hwRegByteOffset-1) >> 2), mask, val);
          mask = val = 0;
        }

        tmask = SPM_HWIO_BMSK_W( coreNum, SPM_SLP_SEQ_ENTRY_n, CMD0);
        cmdShift = SPM_HWIO_SHFT_W( coreNum, SPM_SLP_SEQ_ENTRY_n, CMD0);
        break;

      case 1:
        tmask = SPM_HWIO_BMSK_W( coreNum, SPM_SLP_SEQ_ENTRY_n, CMD1);
        cmdShift = SPM_HWIO_SHFT_W( coreNum, SPM_SLP_SEQ_ENTRY_n, CMD1);
        break;

      case 2:
        tmask = SPM_HWIO_BMSK_W( coreNum, SPM_SLP_SEQ_ENTRY_n, CMD2);
        cmdShift = SPM_HWIO_SHFT_W( coreNum, SPM_SLP_SEQ_ENTRY_n, CMD2);
        break;

      case 3:
        tmask = SPM_HWIO_BMSK_W( coreNum, SPM_SLP_SEQ_ENTRY_n, CMD3);
        cmdShift = SPM_HWIO_SHFT_W( coreNum, SPM_SLP_SEQ_ENTRY_n, CMD3);
        break;
    }
    
    /* Reading actual command */
    cmd = cmdBlk->sequence[i];

    /* We have read at least one command */
    anyCmdCopied = 1;

    mask |= tmask;
    val  |= (cmd << cmdShift);
  }

  SPM_HWIO_OUTMI_W( coreNum, SPM_SLP_SEQ_ENTRY_n, 
                    ((hwRegByteOffset-1) >> 2), mask, val);

  return TRUE;
}

/**
 * Returns the number of registers (of 4 byte) required for command
 * sequences of all modes combined on that particular core.
 *
 * @param coreNum[in] Which SPM
 *
 * @return Returns the number of registers to accomodate all command
 *         sequences.
 *
 * @Note Used by HAL_spm_DwnldAllSlpSeqEntry (see below) to determine
 *       if we will need one time or run time CS programming.
 */
static uint32 HAL_spm_TotalCSRRequired( uint32 coreNum )
{
  uint32 i = 0, total_length = 0;
  uint32 supported_modes = BSP_spm_GetNumSupportedLPMs(coreNum);
  uint32 regs_required = 0;

  for(i=0; i < supported_modes; i++)
  {
    total_length += g_spmCmdSeqArray[coreNum][i].len;
  }

  regs_required = (total_length + SPM_HAL_COMMANDS_PER_REGISTER - 1) /
                  SPM_HAL_COMMANDS_PER_REGISTER;

  return regs_required;
}


/**
 * Initializes all command sequence registers 
 * with end of program command
 * 
 * @param coreNum[in]  Which SPM.
 *
 */
void HAL_spm_InvalidateSlpSeqEntry( uint32 coreNum )
{
  uint32 i;

  uint32 csr_mask = SPM_HWIO_BMSK_W(coreNum, SPM_SLP_SEQ_ENTRY_n, CMD0) |
                    SPM_HWIO_BMSK_W(coreNum, SPM_SLP_SEQ_ENTRY_n, CMD1) |
                    SPM_HWIO_BMSK_W(coreNum, SPM_SLP_SEQ_ENTRY_n, CMD2) |
                    SPM_HWIO_BMSK_W(coreNum, SPM_SLP_SEQ_ENTRY_n, CMD3) ;

  uint32 csr_eos_val = ((BSP_SPM_CMD_END_OF_PROGRAM << 
                         SPM_HWIO_SHFT_W(coreNum, SPM_SLP_SEQ_ENTRY_n, CMD0)) |
                        (BSP_SPM_CMD_END_OF_PROGRAM << 
                         SPM_HWIO_SHFT_W(coreNum, SPM_SLP_SEQ_ENTRY_n, CMD1)) |
                        (BSP_SPM_CMD_END_OF_PROGRAM << 
                         SPM_HWIO_SHFT_W(coreNum, SPM_SLP_SEQ_ENTRY_n, CMD2)) |
                        (BSP_SPM_CMD_END_OF_PROGRAM << 
                         SPM_HWIO_SHFT_W(coreNum, SPM_SLP_SEQ_ENTRY_n, CMD3)));

  for( i = 0; i < csInfo[coreNum].numRegisters; i++ )
  {
    SPM_HWIO_OUTMI_W(coreNum, SPM_SLP_SEQ_ENTRY_n, i, csr_mask, csr_eos_val);
  }    
  
}
  

/**
 * Downloads _all_ the power control sequences necessary for the
 * different sleep modes. 
 * 
 * @param coreNum[in]  Which SPM.
 *
 * @return TRUE if successful, FALSE otherwise
 * 
 * @dependencies None.
 */
bool32 HAL_spm_DwnldAllSlpSeqEntry( uint32 coreNum )
{
  uint32 i;
  uint8  hwRegByteOffset = 0;
  bool32 dwnldSucceeded = FALSE;
  uint32 nmodes = BSP_spm_GetNumSupportedLPMs(coreNum);

  for (i = 0 ; i < nmodes ; i++)
  {
    /* Skip this mode if it's invalid */
    if ( 0 == g_spmCmdSeqArray[coreNum][i].len )
    {
      continue;
    }

    dwnldSucceeded = HAL_spm_WriteCmdBlock(coreNum, 
                                           &g_spmCmdSeqArray[coreNum][i],
                                           hwRegByteOffset);
    
    if (FALSE == dwnldSucceeded )
    {
      break;
    }

    /* Update BSP Data with start offset of SLP_SEQ */
    g_spmCmdSeqArray[coreNum][i].seqStartIndex = hwRegByteOffset;
    hwRegByteOffset += g_spmCmdSeqArray[coreNum][i].len;
  }

  return dwnldSucceeded;
}

/**
 * Returns the relative offset for the requested mode in the 
 * SPM_SLQ_SEQ_ENTRY_n HW register array.
 * 
 * @param coreNum[in]  Which SPM.
 * @param mode[in] Power mode for which the start address is required.
 * @param pStartAddr[out] Command start address will be returned here
 *                        (only valid if return value is TRUE).
 * 
 * @return TRUE if a command sequence is supported for the requested mode.
 * 
 * @dependencies None.
 */
bool32 HAL_spm_GetLPMSequenceData
(
  uint32       coreNum,
  unsigned int mode,
  BSP_spm_CmdSequenceType** seqData
)
{
  uint32 i;
  bool32 status = FALSE;
  uint32 nmodes = BSP_spm_GetNumSupportedLPMs(coreNum);

  /* Make sure we are looking for a valid mode */
  CORE_VERIFY( mode < SPM_NUM_LOW_POWER_MODES );
  
  /* Search the array of modes for the one passed in.  Keep track of
   * the length of command sequences that are passed along the way, in
   * order to determine the start address of this mode. */

  for ( i = 0; i < nmodes; i++ )
  {
    if ( g_spmCmdSeqArray[coreNum][i].mode == mode )
    {
      *seqData = &g_spmCmdSeqArray[coreNum][i];
      status = TRUE; 
      break;
    }
  }

  return status;
}

/* ===========================================================================
**  HAL_spm_Set_LPM_HandshakeMode
**
** ======================================================================== */
static void HAL_spm_Set_LPM_HandshakeMode
( 
  uint32 coreNum,
  uint8 newRpmMode,
  BSP_spm_CmdSequenceType * seqData
  )
{
  uint8 rpmHwRegByteOffset;
  uint8 slp_seq_index;

  /* Set the RPMHS bit in the in-memory copy of sequence */
  *(seqData->sequence + seqData->rpmModeIndex) = newRpmMode;

  /* Update RPMHS bit in SLP_SEQ_ENTRY register if sequence programmed
     init time */
  if( /*HAL_spm_ConfigLowPowerMode*/ NULL == csInfo[coreNum].progFcnPtr )
  {
    rpmHwRegByteOffset = seqData->seqStartIndex + seqData->rpmModeIndex;
    slp_seq_index = rpmHwRegByteOffset >> 2;

    switch (rpmHwRegByteOffset & 0x3)
    {
      case 0:
        SPM_HWIO_OUTFI_W( coreNum, SPM_SLP_SEQ_ENTRY_n, 
                          slp_seq_index, CMD0, newRpmMode );
        break;
      case 1:
        SPM_HWIO_OUTFI_W( coreNum, SPM_SLP_SEQ_ENTRY_n, 
                          slp_seq_index, CMD1, newRpmMode );
        break;
      case 2:
        SPM_HWIO_OUTFI_W( coreNum, SPM_SLP_SEQ_ENTRY_n, 
                          slp_seq_index, CMD2, newRpmMode );
        break;
      case 3:
        SPM_HWIO_OUTFI_W( coreNum, SPM_SLP_SEQ_ENTRY_n, 
                          slp_seq_index, CMD3, newRpmMode );
        break;
    }
  }
}

/* ===========================================================================
**  HALSPM_setRPMHandshakeModeIndex
**
** ======================================================================== */
static void HALSPM_setRPMHandshakeModeIndex
( 
  uint32 coreNum,
  spm_rpm_bypass_type rpmHandshakeMode
)
{
  BSP_spm_CmdSequenceType * seqData;
  uint32 i;
  uint32 nmodes = BSP_spm_GetNumSupportedLPMs(coreNum);
  uint8  newRpmMode = (SPM_RPM_BYPASS_HANDSHAKE == rpmHandshakeMode) ?
    BSP_SPM_CMD_SLEEP_NO_RPM_HANDSHAKE : BSP_SPM_CMD_SLEEP_RPM_HANDSHAKE;

  for ( i = 0; i < nmodes ; i++ )
  {
    seqData = &g_spmCmdSeqArray[coreNum][i];
      
    /* Sequence includes command with option to RPM HS */
    if ( seqData->rpmModeIndex != -1 )
    {
      HAL_spm_Set_LPM_HandshakeMode( coreNum, newRpmMode, seqData );
    }
  }

  return;
}

/* ===========================================================================
**  HALSPM_setRPMHandshakeModeSawctl
**
** ======================================================================== */
static void HALSPM_setRPMHandshakeModeSawctl
(
  uint32               coreNum, 
  spm_rpm_bypass_type  rpmHandshakeMode
)
{
#if (SPM_HWIO_BMSK(SPM_CTL, SLP_CMD_MODE) != 0)
  uint8 bypassBit = (SPM_RPM_BYPASS_HANDSHAKE == rpmHandshakeMode) ? 0 : 1;
  SPM_HWIO_OUTF(SPM_CTL, SLP_CMD_MODE, bypassBit);
#else
  /* This function should be used only when above macro was defined. Ensure 
   * HWIO header is upto date. */
  CORE_VERIFY(0);
#endif
  return;
}

/* -----------------------------------------------------------------------
**                        EXTERNAL FUNCTIONS
** ----------------------------------------------------------------------- */

/* ===========================================================================
**  HAL_spm_PlatformInitEarly
**
** ======================================================================== */
void HAL_spm_PlatformInitEarly 
( 
  uint32 coreNum, 
  HAL_spm_PlatformType *spmPlatform 
)
{
  uint32 numRegRequired;
  uint32 numRegAvailable;

  /* Allocating memory for command seq info structure if not aleady done. 
   * We need this check as this function will be called multiple times in 
   * multicore environment. */
  if( NULL == csInfo )
  {
    CORE_VERIFY_PTR(csInfo = (HAL_spm_CSProgramInfoType *)
                    malloc(sizeof(HAL_spm_CSProgramInfoType) * g_spmNumCores));
  }

  /* Check if we have enough CS registers to write all command sequences
   * at once. If not, we will need to program SPM every time we enter into
   * LPM instead of simply indexing into registers */
  numRegRequired = HAL_spm_TotalCSRRequired(coreNum);
  numRegAvailable = SPM_HWIO_INF_W( coreNum, ID, NUM_SPM_ENTRY );

  /* Initializing last programmed modes array to invalid mode. This is used 
   * only for run time CS programming */
  csInfo[coreNum].lastSeq = NULL;
  csInfo[coreNum].numRegisters = numRegAvailable;

  if( numRegRequired > numRegAvailable )
  {
    /* Run time Command sequence register programming. Initialize all CS
     * registers to end of sequence commands otherwise SPM can wind up
     * in unknown state */
    csInfo[coreNum].progFcnPtr = HAL_spm_SetLowPowerModeRunTime;
    HAL_spm_InvalidateSlpSeqEntry( coreNum );
  }
  else
  {
    /* We can write (or download) command sequences for all modes at once and
     * then index into registers during runtime. */
    csInfo[coreNum].progFcnPtr = NULL /*HAL_spm_ConfigLowPowerMode*/;
    CORE_VERIFY( TRUE == HAL_spm_DwnldAllSlpSeqEntry( coreNum ) );
  }

} 

/* ===========================================================================
**  HAL_spm_Reset
**
** ======================================================================== */
inline void HAL_spm_Reset( uint32 coreNum )
{
  SPM_HWIO_OUTF_W( coreNum, RST, RST, 0x1 );
}

/* ===========================================================================
**  HAL_spm_Init_internal
**
** ======================================================================== */
static bool32 HAL_spm_Init_internal( uint32 coreNum, char **ppszVersion )
{
  BSP_spm_SawCfgType              *sawCfgPtr              = NULL;
  BSP_spm_SawSpmCtlCfgType        *sawSpmCtlCfgPtr        = NULL;
  BSP_spm_SawSpmDlyType           *sawSpmDlyCfgPtr        = NULL;
  BSP_spm_SawPmicDataType         *sawSpmPmicDataPtr      = NULL;
  uint32                          sawVersion;

  /* Obtaining target specific data */
  BSP_spm_InitTargetData();

  /* Determine whether SPM_SLP_SEQ_ENTRY_n is sufficient in size to
     accomodate all supported sequence commands */
  HAL_spm_PlatformInitEarly( coreNum, &spmPlatform );

  spmPlatform.spmConfig = &( g_spmBspData[coreNum] );

  sawCfgPtr           = &((spmPlatform.spmConfig)->sawCfg);
  sawSpmCtlCfgPtr     = &((spmPlatform.spmConfig)->sawSpmCtlCfg);
  sawSpmDlyCfgPtr     = &((spmPlatform.spmConfig)->sawSpmDlyCfg);
  sawSpmPmicDataPtr   = (spmPlatform.spmConfig)->sawSpmPmicData;  

  HAL_spm_ConfigClkDiv      ( coreNum,
                              sawCfgPtr->clkDiv );
  
  HAL_spm_ConfigSpmCtl      ( coreNum,
                              sawSpmCtlCfgPtr->inhibitStartAddrReset,
                              sawSpmCtlCfgPtr->wakeupConfig );

  HAL_spm_ConfigSpmDly      ( coreNum,
                              sawSpmDlyCfgPtr->delay_1,
                              sawSpmDlyCfgPtr->delay_2,
                              sawSpmDlyCfgPtr->delay_3 );
  
  HAL_spm_ConfigPMIC        ( coreNum,
                              sawSpmPmicDataPtr );

  sawVersion = SPM_HWIO_IN_W(SPM_CURR_CORE, VERSION);

  /* Set RPM handshake function based on SAW version. Version 3.0.0 and greater
   * contain a new bit-wise handshake enable, so use that rather than updating
   * the command sequence itself. */
  if(sawVersion >= 0x30000000)
  {
    g_rpmHandshakeFcn = HALSPM_setRPMHandshakeModeSawctl;
  }
  else
  {
#ifdef USPM_ISLAND_MODE_ENABLE
    ERR_FATAL("HAL_spm_Init_internal: "
              "Island mode is enabled and requires SAW version >= 3.0.0", 
              sawVersion, 0, 0);
#endif
  }

  /* Fill in return value */
  if (ppszVersion != NULL)
  {
    *ppszVersion = (char*)HAL_SPM_VERSION_STRING;
  }

  return TRUE;
}

/* ===========================================================================
**  HAL_spm_Init
**
** ======================================================================== */
bool32 HAL_spm_Init( uint32 coreNum, char **ppszVersion )
{
  /* Map HWIO base address */
  spm_hwio_mmap();

  if ( FALSE == HAL_spm_Init_internal( coreNum, ppszVersion ) )
  {
    return FALSE;
  }

  return TRUE;
}

/* ===========================================================================
**  HAL_spm_UpdateActiveVoltageLevel
**
** Reads the currently set voltage level (set by AVS) and updates the
** PMIC data for the restore voltage level.
** ======================================================================== */
void HAL_spm_UpdateActiveVoltageLevel
( 
  uint32 coreNum
)
{
  uint8 vctl;

  /* get currently set active voltage level */
  HAL_spm_GetVctl( coreNum, &vctl );
  
  CORE_VERIFY( vctl != 0 );

  /* update NOMINAL PMIC config with current voltage level */
  HAL_spm_ConfigPMICData( coreNum, BSP_SPM_SAW_PMIC_DATA_NOMINAL, vctl );
}

/* ===========================================================================
**  HAL_spm_GetSawStatus0
**
** ======================================================================== */
void HAL_spm_GetSawStatus0
( 
  uint32 coreNum,
  uint32 *sawStatus 
)
{
  *sawStatus = SPM_HWIO_IN_W( coreNum, SPM_STS );
}

/* ===========================================================================
**  HAL_spm_GetSawInfo
**
** ======================================================================== */
void HAL_spm_GetSawInfo
( 
  uint32 coreNum,
  uint32 *sawInfo 
)
{
  *sawInfo = SPM_HWIO_IN_W( coreNum, ID );
}

/**
 *  @brief HAL_spm_ConfigLowPowerMode
 *   
 *  Confguration SPM_CTL and Wakeup Votlage
 *  (in case of SPM_VDD_MIN)
 *  
 */
void static HAL_spm_ConfigLowPowerMode
( 
  uint32 coreNum,
  BSP_spm_CmdSequenceType *seqData
)
{
  /* Set SPM_START_ADR for mode */
  SPM_HWIO_OUTF_W( coreNum, SPM_CTL, SPM_START_ADR, seqData->seqStartIndex );

  switch(seqData->mode)
  {
    case SPM_MODE_CLK_GATE:
    case SPM_MODE_L2_RETENTION:
    case SPM_MODE_L2_GDHS:
    case SPM_MODE_L2_OFF:
      break;

    case SPM_MODE_VDD_MIN:
      /* Update wake-up voltage to current voltage */
      HAL_spm_UpdateActiveVoltageLevel(coreNum);
      break;

    case SPM_MODE_PWRC:
    case SPM_MODE_APCR_PLL_ON:
    case SPM_MODE_APCR_PLL_LPM:
      /* Q6 HPG dictates SYS_PC_MODE = 1 */
      SPM_HWIO_OUTF_W( coreNum, SPM_CTL, SPM_SYS_PC_MODE, 0x1 );
      break;

    default:
      ERR_FATAL("HAL_spm_SetLowPowerMode: Low Power Mode %d. Not supported",
                seqData->mode, 0, 0);
      break;
  }

}

/**
 *  @brief HAL_spm_SetLowPowerModeRunTime
 *  
 *  There are insufficient SLP_SEQ registers to pre-program all
 *  supported low-power modes at init time.
 *  This function programs the requested low-power mode at 
 *  SLP_SEQ_ENTRY_0[CMD0] -- index 0 location
 *
 *  @see HAL_spm_ConfigLowPowerMode
 */
void static HAL_spm_SetLowPowerModeRunTime
(
  uint32 coreNum,
  BSP_spm_CmdSequenceType *seqData
)
{
  /* Program SLP_SEQ Registers */
  CORE_VERIFY(TRUE == HAL_spm_WriteCmdBlock(coreNum, seqData, 0 /* Idx 0 */ ));
  
  /* Run-time programming of SLP_SEQ_ENTRY_n is adone at index 0 */
  seqData->seqStartIndex = 0;

  /* Update the mode last programmed mode */
  if( csInfo[coreNum].lastSeq != seqData && csInfo[coreNum].lastSeq != NULL )
  {
    csInfo[coreNum].lastSeq->seqStartIndex = -1;
  }
  
  csInfo[coreNum].lastSeq = seqData;

}

/* ===========================================================================
**  HAL_spm_SetLowPowerMode
**
** ======================================================================== */
void HAL_spm_SetLowPowerMode
(
  uint32 coreNum,
  spm_low_power_mode_type spm_mode
)
{
  BSP_spm_CmdSequenceType *seqData;

  /* Lookup low-power mode data in BSP Data */
  CORE_VERIFY( TRUE == 
               HAL_spm_GetLPMSequenceData( coreNum, spm_mode, &seqData ) );

  /* Program low-power sequence in SLP_SEQ_ENTRY_n if required */
  if(csInfo[coreNum].progFcnPtr != NULL)
  {
    (csInfo[coreNum].progFcnPtr)(coreNum, seqData);
  }

  /* Perform Mode specific configuration */
  HAL_spm_ConfigLowPowerMode(coreNum, seqData);
  
}

/* ===========================================================================
**  HAL_spm_Set_RPM_HandshakeMode
**
** ======================================================================== */
void HAL_spm_Set_RPM_HandshakeMode
( 
  uint32 coreNum,
  spm_rpm_bypass_type rpmHandshakeMode
)
{
  g_rpmHandshakeFcn(coreNum, rpmHandshakeMode);
  return;
}

/* ===========================================================================
**  HAL_spm_SetSecurity
**
** ======================================================================== */
void HAL_spm_SetSecurity
( 
  uint32 coreNum,
  uint8 sawCtl, 
  uint8 pwrCtl, 
  uint8 vltCtl
)
{
  /* Not supported. */
}

/* ===========================================================================
**  HAL_spm_ConfigClkDiv
**
** ======================================================================== */
void HAL_spm_ConfigClkDiv
( 
  uint32 coreNum,
  uint8 clkDiv
)
{
  SPM_HWIO_OUTF_W( coreNum, CFG, CLK_DIV, clkDiv);
}

/* ===========================================================================
**  HAL_spm_GetVctl
**
** ======================================================================== */
void HAL_spm_GetVctl
( 
  uint32 coreNum,
  uint8 *pmicData
)
{
  *pmicData = (uint8)SPM_HWIO_INF_W( coreNum, VCTL, PMIC_DATA );
}

/* ===========================================================================
**  HAL_spm_ConfigSpmCtl
**
** ======================================================================== */
void HAL_spm_ConfigSpmCtl // internal, init with BSP
( 
  uint32                   coreNum,
  bool32                   inhibitStartAddrReset,
  BSP_spm_SawPowerModeType wakeupConfig
)
{  
  SPM_HWIO_OUTM_W( 
    coreNum, SPM_CTL,
    (SPM_HWIO_FMSK_W( coreNum, SPM_CTL, ISAR )) |
    (SPM_HWIO_FMSK_W( coreNum, SPM_CTL, WAKEUP_CONFIG ))
    ,
    (SPM_HWIO_FVAL_W( coreNum, SPM_CTL, ISAR, inhibitStartAddrReset )) |
    (SPM_HWIO_FVAL_W( coreNum, SPM_CTL, WAKEUP_CONFIG, wakeupConfig ))
  );
}

/* ===========================================================================
**  HAL_spm_ConfigSpmDly
**
** ======================================================================== */
void HAL_spm_ConfigSpmDly // internal, init with BSP
( 
 uint32                   coreNum,
 uint16                   delay_1,
 uint16                   delay_2,
 uint16                   delay_3
)
{  
  SPM_HWIO_OUTM_W( coreNum, SPM_DLY,
                   (SPM_HWIO_FMSK_W( coreNum, SPM_DLY, DLY1 )) |
                   (SPM_HWIO_FMSK_W( coreNum, SPM_DLY, DLY2 )) |
                   (SPM_HWIO_FMSK_W( coreNum, SPM_DLY, DLY3 )) 
                   ,
                   (SPM_HWIO_FVAL_W( coreNum, SPM_DLY, DLY1, delay_1 )) |
                   (SPM_HWIO_FVAL_W( coreNum, SPM_DLY, DLY2, delay_2 )) |
                   (SPM_HWIO_FVAL_W( coreNum, SPM_DLY, DLY3, delay_3 )) 
                   );
}

/* ===========================================================================
**  HAL_spm_ConfigPMIC
** ======================================================================== */
void HAL_spm_ConfigPMIC
( 
  uint32 coreNum,
  BSP_spm_SawPmicDataType pmicCfg[]
)
{
  int i;

  for(i = 0; i < BSP_SPM_SAW_PMIC_DATA_NUM; i++)
  {
    SPM_HWIO_OUTFI_W( coreNum, SPM_PMIC_DATA_n, 
                      pmicCfg[i].mode, SIZE, pmicCfg[i].pmicDataSize );
    SPM_HWIO_OUTFI_W( coreNum, SPM_PMIC_DATA_n, 
                      pmicCfg[i].mode, ADR_IDX, pmicCfg[i].adrIdx );

    HAL_spm_ConfigPMICDelay(coreNum, pmicCfg[i].mode, pmicCfg[i].pmicDly);
    HAL_spm_ConfigPMICData(coreNum, pmicCfg[i].mode, pmicCfg[i].pmicData);
  }
}

/* ===========================================================================
**  HAL_spm_ConfigPMICDelay
**
** ======================================================================== */
void static HAL_spm_ConfigPMICDelay
( 
  uint32 coreNum,
  BSP_spm_PmicModeData pmicMode,
  uint8 pmicDly
)
{
  SPM_HWIO_OUTFI_W( coreNum, SPM_PMIC_DATA_n, pmicMode, DLY, pmicDly);
}

/* ===========================================================================
**  HAL_spm_ConfigPMICData
**
** ======================================================================== */
void static HAL_spm_ConfigPMICData
( 
  uint32 coreNum,
  BSP_spm_PmicModeData pmicMode,
  uint8 pmicData
)
{
  SPM_HWIO_OUTFI_W( coreNum, SPM_PMIC_DATA_n, pmicMode, DATA, pmicData);
}

/* ===========================================================================
**  HAL_spm_Enable
**
** ======================================================================== */
void HAL_spm_Enable( uint32 coreNum, bool32 spmEnable )
{
  SPM_HWIO_OUTF_W( coreNum, SPM_CTL, SPM_EN, spmEnable );
}

