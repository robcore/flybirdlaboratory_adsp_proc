#ifndef __CLOCKLPASSLDO_H__
#define __CLOCKLPASSLDO_H__
/*
===========================================================================
*/
/**
  @file ClockLPASSLDO.h 
  
  The file contains the resource definitions for LDO voltage scaling on
  the Low Power Audio Subsystem processor for 9x25.
*/
/*  
  ====================================================================

  Copyright (c) 2012 Qualcomm Technologies Incorporated.  All Rights Reserved.  
  QUALCOMM Proprietary and Confidential. 

  ==================================================================== 
  $Header: //components/rel/core.adsp/2.6.1/systemdrivers/clock/hw/msm8994/src/ClockLPASSLDO.h#1 $
  $DateTime: 2014/10/16 12:45:40 $
  $Author: pwbldsvc $

  when       who     what, where, why
  --------   ---     -------------------------------------------------
  06/12/12   dcf     Created for LPASS on 8974.

  ====================================================================
*/ 


/*=========================================================================
      Include Files
==========================================================================*/

#include "ClockDriver.h"
#include "ClockLPASSCPU.h"

/*=========================================================================
      Type Definitions
==========================================================================*/



/*=========================================================================
      Prototypes
==========================================================================*/



/*=========================================================================
      Variables
==========================================================================*/



/*=========================================================================
      Functions
==========================================================================*/


/* =========================================================================
**  Function : Clock_InitLDOVoltage
** =========================================================================*/
/**
  Initializes the LDO voltage control for DVS at LDO.
 
  This function does required work to initialize the image-specific LDO
  voltage scaling functionality.
 
  @param pDrvCtxt [in] -- The Clock Driver context.

  @return
  DAL_SUCCESS -- Successfully initialized the voltage functionality.
  DAL_ERROR  -- A problem occurred trying to initialize the driver.

  @dependencies
  None.
*/ 
DALResult Clock_InitLDOVoltage
(
  ClockDrvCtxt *pDrvCtxt
);


/* =========================================================================
**  Function : Clock_SetLDOVoltage
** =========================================================================*/
/**
  Sets a voltage for a current performance level.
 
  This function will program the LDO to obtain the desired voltage level.
 
  @param pDrvCtxt [in] -- The Clock Driver context.
  @param pConfig [in] -- Configuration containing the new voltage for the eLDO.
  @param pVRegRequest [in] -- The voltage request type for rail transitions.

  @return
  DAL_SUCCESS -- Successfully set the new voltage.
  DAL_ERROR  -- Unable to set the desired voltage to HW.

  @dependencies
  None.
*/ 
DALResult Clock_SetLDOVoltage
(
  ClockDrvCtxt         *pDrvCtxt,
  ClockCPUConfigType   *pConfig,
  ClockVRegRequestType *pVRegRequest
);


/* =========================================================================
**  Function : Clock_GetLDOVoltage
** =========================================================================*/
/**
  Retrieves the current programmed voltage.
 
  This function returns the current voltage programmed to HW.
 
  @param pDrvCtxt [in] -- The Clock Driver context.

  @return
  The current voltage programmed at the eLDO for the CPU.

  @dependencies
  None.
*/ 
uint32 Clock_GetLDOVoltage
(
    ClockDrvCtxt       *pDrvCtxt
);

/* =========================================================================
**  Function : Clock_EnableLDO
** =========================================================================*/
/**
  Enables the LDO functionality if supported.
 
  This API allows the enablement of the embedded LDO functionality for the
  QDSP6.  By default, if the LDO is supported, the functionality would be
  enabled, but in certain low-temperature restricted circumstances, the system
  must operate at a higher voltage than usual.  This API allows the re-enablement
  of the LDO functionality following the removal of a voltage floor restriction.
 
  @param pDrvCtxt [in] -- The Clock Driver context.
 
  @return
  None.

  @dependencies
  None.
*/
void Clock_EnableLDO
(
   ClockDrvCtxt* pDrvCtxt
);


/* =========================================================================
**  Function : Clock_DisableLDO
** =========================================================================*/
/**
  Disables the embedded LDO functionality
 
  This API disables the embedded LDO functionality where supported.  If the
  system is in a state of low temperature and requires a higher operating
  voltage than normal, this API will be used to ensure the LDO does not
  lower the voltage to the QDSP6.
 
  @param pDrvCtxt [in] -- The Clock Driver context.
 
  @return
  None.

  @dependencies
  None.
*/
void Clock_DisableLDO
(
   ClockDrvCtxt* pDrvCtxt
);

#endif /* __CLOCKLPASSLDO_H__ */

