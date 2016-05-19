#ifndef CLOCKLPASS_H
#define CLOCKLPASS_H
/*
===========================================================================
*/
/**
  @file ClockLPASS.h 
  
  Internal header file for the clock device driver on the LPASS image.
*/
/*  
  ====================================================================

  Copyright (c) 2012 Qualcomm Technologies Incorporated.  All Rights Reserved.  
  QUALCOMM Proprietary and Confidential. 

  ==================================================================== 
  $Header: //components/rel/core.adsp/2.6.1/systemdrivers/clock/hw/mdm9x35/src/ClockLPASS.h#1 $
  $DateTime: 2014/10/16 12:45:40 $
  $Author: pwbldsvc $

  when       who     what, where, why
  --------   ---     -------------------------------------------------
  09/07/11   dcf     Created.

  ====================================================================
*/ 


/*=========================================================================
      Include Files
==========================================================================*/

#include "DDIClock.h"
#include "ClockBSP.h"
#include "ClockLPASSCPU.h"


/*=========================================================================
      Macro Definitions
==========================================================================*/


/*=========================================================================
      Type Definitions
==========================================================================*/


/*
 * QDSP6 saved configuration
 */
typedef struct
{
  ClockCPUConfigType        *pCPUConfig;
  boolean                   bDisableDVS;
}ClockQDSP6SavedConfigType;


/*
 * QDSP6 clock driver context.
 */
typedef struct
{
  ClockNodeType             *pQDSP6Clock;
  ClockCPUConfigType        *pCPUConfig;
  ClockQDSP6SavedConfigType QDSP6SavedConfig;
  uint32                    nLDOVoltageBuffer;
  npa_client_handle         NPAImpulseHandle;
} ClockQDSP6CtxtType;


/**
 * LPASS clock driver context.
 */
typedef struct
{
  ClockQDSP6CtxtType     QDSP6Ctxt;
  ClockImageConfigType   *pImageConfig;
} ClockLPASSCtxtType;



/*=========================================================================
      Function Definitions
==========================================================================*/

/* =========================================================================
**  Function : Clock_InitPLL
** =========================================================================*/
/**
  Initialize the modem PLL management subsystem.
 
  This function initializes NPA nodes and resources to control modem PLLs.
 
  @param *pDrvCtxt [in] -- The driver context.

  @return
  DAL_SUCCESS

  @dependencies
  None.
*/ 

DALResult Clock_InitPLL
(
  ClockDrvCtxt *pDrvCtxt
);


/* =========================================================================
**  Function : Clock_InitXO
** =========================================================================*/
/**
  Initialize the XO management subsystem.
 
  This function initializes the XO LPR nodes required for communicating 
  resource requests to the RPM.
 
  @param *pDrvCtxt [in] -- The driver context.

  @return
  DAL_SUCCESS

  @dependencies
  None.
*/ 

DALResult Clock_InitXO
(
  ClockDrvCtxt *pDrvCtxt
);


/* =========================================================================
**  Function : Clock_SetQDSP6Config
** =========================================================================*/
/**
  Set QDSP6 configuration.
 
  This function sets QDSP6 configuration based on input parameters.
 
  @param *pDrvCtxt [in] -- Pointer to driver context.
  @param  pConfig  [in] -- New configuration.

  @return
  npa_resource_state -- The new active state of the resource.

  @dependencies
  None.
*/ 

void Clock_SetQDSP6Config
(
  ClockDrvCtxt          *pDrvCtxt,
  ClockCPUConfigType  *pConfig
);


/* =========================================================================
**  Function : Clock_QDSP6TriggerStateUpdate
** =========================================================================*/
/**
  Trigger function to update QDSP6 LPASS states.
 
  This function updates QDSP6 LPASS states (frequencies) and then
  synchronizes them with NPA framework.
 
  @param *pDrvCtxt [in] -- Pointer to the clock driver context.

  @return
  None.

  @dependencies
  None.
*/

void Clock_QDSP6TriggerStateUpdate
( 
  ClockDrvCtxt *pDrvCtxt 
);


/* =========================================================================
**  Function : Clock_NPACPUResourceOverwriteActiveState
** =========================================================================*/
/**
  This Function overwrites the CPU resource's active state. It should ONLY
  be invoked during the Sleep sequence when in Single Threaded Mode (STM).

  We invoke this function after directly configuring the CPU without
  going through the NPA. This results in the CPU resource's active state
  being different from the requested state. Upon wake-up, Sleep must make
  an NPA Impulse request which will re-aggregate the CPU requests and
  trigger our driver function.

  @param nState [in] -- Active state of the CPU resource.

  @return
  DAL_SUCCESS -- Resource active state is set. \n
  DAL_ERROR  --  Resource handle is NULL.

  @dependencies
  None.
*/
DALResult Clock_NPACPUResourceOverwriteActiveState
(
  npa_resource_state nState
);


/* =========================================================================
**  Function : Clock_InitVdd
** =========================================================================*/
/**
  This Function overwrites the CPU resource's active state. It should ONLY
  be invoked during the Sleep sequence when in Single Threaded Mode (STM).

  We invoke this function after directly configuring the CPU without
  going through the NPA. This results in the CPU resource's active state
  being different from the requested state. Upon wake-up, Sleep must make
  an NPA Impulse request which will re-aggregate the CPU requests and
  trigger our driver function.

  @param nState [in] -- Active state of the CPU resource.

  @return
  DAL_SUCCESS -- Resource active state is set. \n
  DAL_ERROR  --  Resource handle is NULL.

  @dependencies
  None.
*/
DALResult Clock_InitVdd
(
  ClockDrvCtxt *pCtxt
);


ClockLPASSCtxtType* Clock_GetImageCtxt(void);
boolean Clock_SupportsLDO(void);
boolean Clock_SupportsSPMCTL(void);
boolean Clock_IsBHSMode(void);

#endif /* !CLOCKLPASS_H */

