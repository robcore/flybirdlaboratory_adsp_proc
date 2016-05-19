#ifndef Q6_LPM_CONFIG
#define Q6_LPM_CONFIG
/*==============================================================================
  FILE:         q6_lpm_config.h

  OVERVIEW:     This file contains the APIs for configuring Q6 cpu to low 
                power modes. These APIs are may have Q6 version specific
		implementation. 

  DEPENDENCIES: None

                Copyright (c) 2014 QUALCOMM Technologies Incorporated.
                All Rights Reserved.
                Qualcomm Confidential and Proprietary
================================================================================
$Header: //components/rel/core.adsp/2.6.1/power/sleep2.0/src/lpr/q6_lpm_config.h#1 $
$DateTime: 2014/10/16 12:45:40 $
==============================================================================*/

#include "DALStdDef.h"
#include "spm.h"

/*==============================================================================
 *                             GLOBAL FUNCTIONS
 *============================================================================*/

/**
 * q6LPMConfig_setupBase
 *
 * @brief This function configures basic low power mode related Q6 registers 
 *        that remain same across all low power modes Q6 can be put in to.
 */
void q6LPMConfig_setupBase(void);

/**
 * q6LPMConfig_setupModeConfig
 *
 * @brief Performs Q6SS register configuration related to mode passed as
 *        input.
 *
 * @param coreMode  : Specifies the low power mode we want Q6 to put when
 *                    it goes idle next.
 * @param triggerPMI: Boolean indicating if PMI interrupt needs to be 
 *                    triggered upon spm exit from low power mode.
 *                    Currently it is required only for APCR low power
 *                    modes entered from single threaded context.
 */
void q6LPMConfig_setupModeConfig( spm_low_power_mode_type coreMode, 
                                  boolean triggerPMI );

/**
 * q6LPMConfig_setupL2NonRetConfig
 *
 * @brief Configures Q6SS L2 cache related registers for L2 non retention based
 *        low power modes
 */
void q6LPMConfig_setupL2NonRetConfig(void);

/**
 * q6LPMConfig_setupL2RetConfig
 *
 * @brief Configures Q6SS L2 cache related registers for L2 retention based
 *        low power modes
 */
void q6LPMConfig_setupL2RetConfig(void);

#endif
