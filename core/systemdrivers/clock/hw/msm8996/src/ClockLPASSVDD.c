/*
===========================================================================
*/
/**
  @file ClockLPASSVDD.c 
  
  The file contains the resource definitions for VDD management on the
  Low Power Audio Subsystem processor.
*/
/*  
  ====================================================================

  Copyright (c) 2013 Qualcomm Technologies Incorporated.  All Rights Reserved.  
  QUALCOMM Proprietary and Confidential. 

  ==================================================================== 
  $Header: //components/rel/core.adsp/2.6.1/systemdrivers/clock/hw/msm8996/src/ClockLPASSVDD.c#1 $
  $DateTime: 2014/10/16 12:45:40 $
  $Author: pwbldsvc $

  when       who     what, where, why
  --------   ---     -------------------------------------------------
  02/07/12   dcf     Created for LPASS on 8974.

  ====================================================================
*/ 


/*=========================================================================
      Include Files
==========================================================================*/

/*
 * External header files.
 */
#include <npa.h>
#include <npa_resource.h>
#include <npa_remote.h>
#include <npa_remote_resource.h>

/*
 * Clock regime headers.
 */
#include "ClockDriver.h"
#include "ClockLPASS.h"


/*=========================================================================
      Externally defined functions
==========================================================================*/

extern ClockDrvCtxt *Clock_GetDrvCtxt(void);

/*=========================================================================
      Type Definitions
==========================================================================*/

static npa_client_handle hNPAeLDOHandle = NULL;

/*
 * Clock_VDDType
 *
 * Structure containing the VDD NPA node and resource data.
 *
 *  VDDNode       - VDD node data
 *  VDDResources  - VDD resource data: /clk/vdd_restrict
 */ 
typedef struct
{
  npa_resource_definition   VDDResource;
  npa_node_definition       VDDNode;
} ClockVDDType;


/*=========================================================================
      Prototypes
==========================================================================*/

static npa_resource_state Clock_VddDriver
(
  npa_resource *pResource,
  npa_client   *pClient,
  npa_resource_state nState
);


/*=========================================================================
      Variables
==========================================================================*/


/*
 * Clock_VDD
 *
 * Low power resource data.
 */
static ClockVDDType Clock_VDD =
{
  /*
   * VDDResource
   */
  {
    "/vdd/thermal", 
    "on/off",
    CLOCK_SOURCE_REQUIRED,      /* max state */
    &npa_max_plugin, 
    NPA_RESOURCE_DEFAULT,
    NULL
  },

  /*
   * VDDNode
   */
  { 
    "/node/vdd/thermal",        /* name */
    Clock_VddDriver,            /* driver_fcn */
    NPA_NODE_DEFAULT,           /* attributes */
    NULL,                       /* data */
    0,                          /* dependency count */
    NULL,                       /* dependency */
    1, &Clock_VDD.VDDResource   /* resource */
  }
};


/*=========================================================================
      Functions
==========================================================================*/


/* =========================================================================
**  Function : Clock_VddDriver
** =========================================================================*/
/**
  Handle voltage floor restrictions for low temperature extensions.
 
  Stubbed function on 8996.  eLDO is not supported.

  @param pResource [in] -- The NPA resource being requested.
  @param pClient [in]   -- Pointer to the client making the request.
  @param nState [in]    -- New state of the resource.

  @return
  New state of the resource.

  @dependencies
  None.
*/ 

static npa_resource_state Clock_VddDriver
(
  npa_resource      *pResource,
  npa_client        *pClient,
  npa_resource_state nState
)
{

  return nState;

} /* END Clock_VddDriver */


/* =========================================================================
**  Function : Clock_VddCreateClientCB
** =========================================================================*/
/**
  Callback when an VDD node is created.
 
  This function is called by the NPA framework when the given VDD node is
  created.  The creation is delayed until all dependencies are also
  created.
 
  @param *pContext [in] -- Context passed in npa_define_node_cb
  @param nEventType [in] -- Zero.
  @param *pNodeName [in] -- Name of the node being created.
  @param nNodeNameSize [in] -- Length of the name.

  @return
  None.

  @dependencies
  None.
*/ 

static void Clock_VddCreateClientCB
(
  void        *pContext,
  unsigned int nEventType,
  void        *pNodeName,
  unsigned int nNodeNameSize
)
{
  npa_node_definition *pNode = (npa_node_definition *)pContext;
  uint32 nState;

  /*-----------------------------------------------------------------------*/
  /* Create the appropriate NPA client.                                    */
  /*-----------------------------------------------------------------------*/

  if (pNode == &Clock_VDD.VDDNode)
  {
    hNPAeLDOHandle = 
      npa_create_sync_client(
        Clock_VDD.VDDResource.name, "/clk/vdd", NPA_CLIENT_REQUIRED);
  }

  /*-----------------------------------------------------------------------*/
  /* Send current state info to VDD NPA driver function.                   */
  /*-----------------------------------------------------------------------*/

  nState = CLOCK_SOURCE_NOT_REQUIRED;

  npa_issue_scalar_request(hNPAeLDOHandle, nState); 

} /* END Clock_VddCreateClientCB */


/* =========================================================================
**  Function : Clock_InitVdd
** =========================================================================*/
/*
  See ClockLPASS.h
*/

DALResult Clock_InitVdd
(
  ClockDrvCtxt *pCtxt
)
{
  npa_resource_state nInitialState;

  /*-----------------------------------------------------------------------*/
  /* Init VDD node.                                                        */
  /*-----------------------------------------------------------------------*/

  Clock_VDD.VDDNode.data = (npa_user_data)pCtxt;

  nInitialState = CLOCK_SOURCE_NOT_REQUIRED;

  npa_define_node_cb(
    &Clock_VDD.VDDNode, &nInitialState, Clock_VddCreateClientCB,
    &Clock_VDD.VDDNode);


  /*-----------------------------------------------------------------------*/
  /* Good to go.                                                           */
  /*-----------------------------------------------------------------------*/

  return DAL_SUCCESS;

} /* END Clock_InitVdd */

