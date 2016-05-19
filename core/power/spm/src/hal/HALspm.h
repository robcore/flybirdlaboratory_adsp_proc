#ifndef HALSPM_H
#define HALSPM_H
/*==============================================================================
  FILE:         HALspm.h

  OVERVIEW:     This is the hardware abstraction layer interface for the
                SPM block.

  DEPENDENCIES: None
  
                Copyright (c) 2009-2014 Qualcomm Technologies, Inc. (QTI).
                All Rights Reserved.
                Qualcomm Technologies Confidential and Proprietary
================================================================================
$Header: //components/rel/core.adsp/2.6.1/power/spm/src/hal/HALspm.h#1 $
$DateTime: 2014/10/16 12:45:40 $
==============================================================================*/
#ifdef __cplusplus
extern "C" {
#endif

/* -----------------------------------------------------------------------
** Includes
** ----------------------------------------------------------------------- */
#include <HALcomdef.h>
#include "spm.h"

/* -----------------------------------------------------------------------
** Constants
** ----------------------------------------------------------------------- */

/* -----------------------------------------------------------------------
** Types
** ----------------------------------------------------------------------- */

/* -----------------------------------------------------------------------
** Interface
** ----------------------------------------------------------------------- */

/**
 * HAL_spm_Init
 *
 * This is the init function for the HAL SPM layer.
 *
 * @param[in] coreNum  Which SPM.
 *
 * @param  None
 *
 * @return TRUE if successful; FALSE otherwise.
 */
bool32 HAL_spm_Init( uint32 coreNum, char **ppszVersion );

/**
 * HAL_spm_GetSawStatus
 *
 * This function returns the contents of the SAW_STS register.  The caller
 * must know how to interpret the data returned.
 *
 * @param coreNum     Which SPM.
 * @param *sawStatus  Output parameter - pointer to the location to put the
 *                    status in.
 *
 * @return None
 */
void HAL_spm_GetSawStatus
(
  uint32 coreNum,
  uint32 *sawStatus
);

/**
 * HAL_spm_Set_RPM_HandshakeMode
 *
 * This function indicates whether to perform the RPM handshaking, or
 * to bypass the RPM.
 *
 * @param coreNum              Which SPM.
 * @param rpmHandshakeMode[in] RPM handshake mode.
 *
 * @return None.
 */
void HAL_spm_Set_RPM_HandshakeMode
(
  uint32 coreNum,
  spm_rpm_bypass_type rpmHandshakeMode
) USPM_CODE_SECTION;

/**
 * HAL_spm_SetLowPowerMode
 *
 * This function indicates which low power mode is desired on the
 * next SW DONE signal.
 *
 * @param coreNum  Which SPM.
 * @param mode  Indicates which low power mode to set.
 *              These should align with BSP_spm_LpmType.
 *
 * @return None
 *
 * @see
 */
void HAL_spm_SetLowPowerMode
(
  uint32 coreNum,
  spm_low_power_mode_type mode
);

/**
 * HAL_spm_ConfigVddWakeLevel
 *
 * This function is used to program the VDD value to use when the system
 * is awake (normal operation).  This value may change at run time as the
 * system active voltage changes.
 *
 * @param wake  VDD value to use when awake.
 *
 * @return None
 *
 * @see
 */
void HAL_spm_ConfigVddWakeLevel
(
  uint8 wake
);

/**
 * Enable/Disable the SPM HW.
 *
 * @param coreNum   : Which SPM.
 * @param spmEnable : TRUE to enable, FALSE to disable.
 */
void HAL_spm_Enable( uint32 coreNum, bool32 spmEnable ) USPM_CODE_SECTION;

/**
 * Updates the contents of the SAW2 SPM register that contains the
 * PMIC data for active voltage level. This function retrieves the
 * current active voltage level from another SAW2 SPM hardware
 * register.
 *
 * @param coreNum[in]   - Which SPM.
 *
 * @return None.
 *
 * @dependencies None.
 */
void HAL_spm_UpdateActiveVoltageLevel
(
  uint32 coreNum
);

/*============================================================================
   INTERFACES DOCUMENTATION
=============================================================================*/

#ifdef __cplusplus
}
#endif

#endif /* HALSPM_H */
