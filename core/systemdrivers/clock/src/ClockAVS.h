#ifndef __CLOCKAVS_H__
#define __CLOCKAVS_H__

/*===========================================================================

                    C L O C K   D E V I C E   D R I V E R

               A D A P T I V E   V O L T A G E   S C A L I N G

GENERAL DESCRIPTION
  This file contains prototypes for the Adaptive Voltage Scaling (AVS)
  API for use within the clock driver.
  
INITIALIZATION AND SEQUENCING REQUIREMENTS
  Call Clock_InitAVS and ensure return value is successful before calling
  any other APIs in this module.

      Copyright (c) 2011 by Qualcomm Technologies, Inc.  All Rights Reserved.

============================================================================*/

/*==========================================================================

                        EDIT HISTORY FOR MODULE

  This section contains comments describing changes made to the module.
  Notice that changes are listed in reverse chronological order.
 
$Header: //components/rel/core.adsp/2.6.1/systemdrivers/clock/src/ClockAVS.h#1 $

when       who     what, where, why 
--------   ---     --------------------------------------------------------- 
03/15/11   dcf     Ported and redesigned for 8x60 from 7x30.

============================================================================*/ 


/*==========================================================================
      Include Files
============================================================================*/

#include <HALavs.h>
#include <DALSys.h>
#include <ClockDriver.h>


/*==========================================================================
      Type Definitions
============================================================================*/

/**
 * ClockAVSInitType 
 *  
 * Image specific clock initialization data structure.  This structure is 
 * used to provide the AVS image with setting it needs to initialize. 
 *  
 * eCore - The core to apply settings to. 
 * pCurrCfg - The voltage/delay synthesizer settings for the peroformance level.
 */

typedef struct
{
  HAL_avs_CoreType        eCore;
  ClockAVSCoreFreqCfgType *pCurrCfg;
}ClockAVSInitType;



/*==========================================================================
      Function Definitions
============================================================================*/


/* =========================================================================
**  Function : Clock_SetVoltageLevel
** =========================================================================*/
/**
  Sets a core voltage.

  This function sets a voltage for a particular core to a desired voltage.

  @param eCore [in] -- Core for which to program the voltage to.
  @param nVoltage [in] -- The voltage in mV to program.

  @return
  DAL_SUCCESS -- The voltage was successfully programmed.
  DAL_ERROR -- An error occurred while attempting to program the voltage.

  @dependencies
  The clock mutex must be locked by the caller.
*/

DALResult Clock_SetVoltageLevel
(
  HAL_avs_CoreType eCore, 
  uint32           nVoltage
);



/* =========================================================================
**  Function : Clock_InitAVS
** =========================================================================*/
/**
  Initializes the AVS data structures and circuitry.

  This function must be the firt API to be called in order to initialize the
  AVS HW and internal data structures.
 
  @param pDrvCtxt [in] -- Pointer to the driver context. 
  @param pInit [in] -- Clock-specific initialization parameters.
 
  @return
  DAL_SUCCESS -- AVS was initialized successfully.
  DAL_ERROR -- An error occurred while attempting to initialize AVS.

  @dependencies
  The clock mutex must be locked by the caller.
*/

DALResult Clock_InitAVS
(
  ClockDrvCtxt *pDrvCtxt,
  ClockAVSInitType *pInit
);


/* =========================================================================
**  Function : Clock_HaltAVS
** =========================================================================*/
/**
  Halt one of the AVS cores.

  This function disables AVS monitoring as required before such actions as
  setting voltage levels or changing CPU frequencies.
 
  @param pDrvCtxt [in] -- Pointer to the driver context. 
  @param eCore [in] -- Core for which to halt AVS functionality.

  @return
  DAL_SUCCESS -- The core was halted successfully.

  @dependencies
  The clock mutex must be locked by the caller.
*/

DALResult Clock_HaltAVS
(
  ClockDrvCtxt     *pDrvCtxt,
  HAL_avs_CoreType eCore
);


/* =========================================================================
**  Function : Clock_ResumeAVS
** =========================================================================*/
/**
  Resumes AVS monitoring on a particular core.

  This function resumes the AVS HW monitoring of voltage after such actions
  as software controlled voltage or CPU frequency changing.
 
  @param pDrvCtxt [in] -- Pointer to the driver context.
  @param eCore [in] -- Core for which to resume AVS functionality.
  @param pResumeData [in] -- AVS configuration data for current frequency.

  @return
  DAL_SUCCESS -- The core was halted successfully.

  @dependencies
  The clock mutex must be locked by the caller.
*/

DALResult Clock_ResumeAVS
(
  ClockDrvCtxt            *pDrvCtxt,
  HAL_avs_CoreType        eCore,
  ClockAVSCoreFreqCfgType *pResumeData
);


/* =========================================================================
**  Function : Clock_UpdateAVSDelaySynth
** =========================================================================*/
/**
  Programs the Delay Synthesizer for AVS on the CPU.

  This function updates the delay synthesizer for a particular CPU so that 
  HW can model the critical path efficiently.

  @param pDrvCtxt [in] -- Pointer to the driver context.
  @param eCore [in] -- Core for which to resume AVS functionality.
  @param nNewDelaySynth [in] -- The delay synthesizer value to program to HW.
 
  @return
  None.

  @dependencies
  The clock mutex must be locked by the caller and AVS must be disabled.
*/

void Clock_UpdateAVSDelaySynth
(
  ClockDrvCtxt     *pDrvCtxt,
  HAL_avs_CoreType eCore,
  uint32           nNewDelaySynth
);



/* =========================================================================
**  Function : Clock_AVSInitImage
** =========================================================================*/
/*
  Initializes image-specific portions of AVS.
 
  This API will initialize APPS image specific portions of AVS before calling
  the generic initialization API.
 
  @param *pDrvCtxt [in] -- Context pointer, the driver context in this case.

  @return
  NULL

  @dependencies
  Must be synchronous.
*/

DALResult Clock_AVSInitImage
(
  ClockDrvCtxt *pDrvCtxt
);

#endif  /* __CLOCKAVS_H__ */ 

