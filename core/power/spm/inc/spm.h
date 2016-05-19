#ifndef SPM_H
#define SPM_H
/*==============================================================================
  FILE:         spm.h

  OVERVIEW:     This module contains routines for the subsystem power
                manager (SPM).

  DEPENDENCIES: None
                
                Copyright (c) 2009-2014 Qualcomm Technologies, Inc. (QTI).
                All Rights Reserved.
                Qualcomm Technologies Confidential and Proprietary
================================================================================
$Header: //components/rel/core.adsp/2.6.1/power/spm/inc/spm.h#1 $
$DateTime: 2014/10/16 12:45:40 $
==============================================================================*/
#include "comdef.h"

/*==============================================================================
                              DEFINES & TYPES
 =============================================================================*/
#ifdef USPM_ISLAND_MODE_ENABLE
/* Macros to define memory sections. These will be used to locate specific
 * functions & data in the island memory section. Note that the API's marked
 * as a uspm section are public. */
#define USPM_CODE_SECTION __attribute__((section (USPM_ISLAND_CODE_STR)))
#define USPM_DATA_SECTION __attribute__((section (USPM_ISLAND_DATA_STR)))

#else
/* Define empty macros */
#define USPM_CODE_SECTION 
#define USPM_DATA_SECTION 

#endif /* USPM_ISLAND_MODE_ENABLE */

/*=============================================================================
 *                          INTERNAL MACROS
 *============================================================================*/

/**
 * @brief Function call to obtain core id on which this instruction is 
 *        getting executed based on platform.
 *
 * @Note:
 * Power utils does not have getCurrCpuID for NON-HLOSes which is used for
 * multicore targets. Since it is not even present, if we have that here, it 
 * can result in to compile time error even if it is not ever being called for
 * single core targets.
 */
#define SPM_CURR_CORE (g_spmNumCores > 1 ? /* getCurrCpuID() */ 0 : 0)

/*===========================================================================
 *                   DEFINITIONS AND DECLARATIONS FOR MODULE
 *===========================================================================*/

/**
 * @brief Variable indicating how many spm cores the given master has. 
 *        Technically it is a constant but value is obtained through 
 *        different methods. But once assigned, it should never be changed.
 *
 * Initial value will be zero and then later assigned a value during 
 * initialization.
 */
extern unsigned int g_spmNumCores;

/** 
 * @brief This enum reflects the low power modes that are supported by the 
 *        SPM driver. Not all of these low power modes may be supported on
 *        every target. Supported low-power modes are listen in the BSP 
 *        configuration for the target.
 */
typedef enum
{
  SPM_MODE_CLK_GATE,         /* Gate Clock to Processor Core            */
  SPM_MODE_VDD_MIN,          /* Minimize the Processor Core Voltage     */
  SPM_MODE_APCR_PLL_ON,      /* APCR/Fast PC with PLL on                */
  SPM_MODE_APCR_PLL_LPM,     /* APCR/Fast PC with PLL stand by or off   */
  SPM_MODE_PWRC,             /* PC Processor Core using PMIC            */
  SPM_MODE_PWRC_L2RET,       /* PC with L2 retention                    */
  SPM_MODE_L2_RETENTION,     /* Retain Power to L2 Cache Memory         */
  SPM_MODE_L2_GDHS,          /* Power Off L2 Cache using Local Switch   */
  SPM_MODE_L2_OFF,           /* Power Off L2 Cache                      */
  SPM_NUM_LOW_POWER_MODES
} spm_low_power_mode_type;

/**
 * @brief This enum is for bypassing RPM to expediate some of SPM functions 
 *        for an individual subsystem like Scorpion.
 */
typedef enum
{
  SPM_RPM_PERFORM_HANDSHAKE,
  SPM_RPM_BYPASS_HANDSHAKE,
} spm_rpm_bypass_type;

/**
 * @brief Enumeration for different cores on the processor.
 */
typedef enum
{
  SPM_CORE_NUM_0,
  SPM_CORE_NUM_1,
  SPM_CORE_NUM_2,
  SPM_CORE_NUM_L2 = SPM_CORE_NUM_2
} spm_core_num_type;

/*===========================================================================
 *                    EXTERNAL FUNCTION DEFINITIONS
 *==========================================================================*/

/**
 * @brief This function is used to set the low power mode of the SPM HW.  
 *        The low power mode will be valid the next time the SPM HW receives 
 *        a SW_DONE_EN signal from the processor. This function should be 
 *        used to set the low power mode before every halt in order to 
 *        guarantee that the SW_DONE_EN signal is regarded in the desired 
 *        way.
 *
 * @param core_num This tells the SPM driver which core to program the
 *                 SPM for.  The first core starts at 0, and the core
 *                 numbers go up from there.  This function will do
 *                 nothing if given an invalid core number.  
 * 
 * @param low_power_mode Desired low power mode during the next halt.
 * 
 * @return nothing.
 */
void spm_set_low_power_mode
( 
  uint32 core_num,
  spm_low_power_mode_type low_power_mode
);

/**
 * @brief This function is used to tell the SPM driver whether or not the 
 *        RPM handshaking should be performed during the next power savings
 *        sequence. This function should be called before halting the 
 *        processor.
 *  
 *        Note: Located in island section memory if feature is enabled 
 *
 * @param core_num  This tells the SPM driver which core to program the
 *                  SPM for.  The first core starts at 0, and the core
 *                  numbers go up from there.  This function will do
 *                  nothing if given an invalid core number.
 *  
 * @param rpm_bypass Indicates whether or not the RPM handshaking should be
 *                   performed.  The choices are:
 *                     SPM_RPM_PERFORM_HANDSHAKE  - Perform the RPM handshake.
 *                     SPM_RPM_BYPASS_HANDSHAKE - Bypass the RPM handshake.
 */
void spm_set_rpm_bypass(uint32 core_num, 
                        spm_rpm_bypass_type rpm_bypass) USPM_CODE_SECTION;

/**
 * @brief Enable/Disable the SPM HW.
 *
 * @param core_num: Which core's SPM (0,1,2,...)
 * @spm_enable : TRUE to enable; FALSE to disable.
 *
 * @return nothing
 */
void spm_enable( uint32 core_num, boolean spm_enable ) USPM_CODE_SECTION;

/**
 * @brief This is the init function for the SPM driver. It initializes the 
 *        HAL layer as well as the driver layer.
 */
void spm_initialize( void );

#endif /* !SPM_H */

