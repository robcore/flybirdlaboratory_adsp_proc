/*
===========================================================================
*/
/**
  @file ClockLPASSXO.c 
  
  The file contains the resource definitions for XO management on the
  Low Power Audio Subsystem processor for 8974.
*/
/*  
  ====================================================================

  Copyright (c) 2011 Qualcomm Technologies Incorporated.  All Rights Reserved.  
  QUALCOMM Proprietary and Confidential. 

  ==================================================================== 
  $Header: //components/rel/core.adsp/2.6.1/systemdrivers/clock/hw/mdm9x35/src/ClockLPASSXO.c#1 $
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
#include <sleep_lpr.h>
#include <npa.h>
#include <npa_resource.h>
#include <npa_remote.h>
#include <npa_remote_resource.h>

/*
 * Clock regime headers.
 */
#include "ClockDriver.h"
#include "ClockSWEVT.h"
#include "HALclk.h"



/*=========================================================================
      Type Definitions
==========================================================================*/

/*
 * Clock_XOType
 *
 * Structure containing the XO NPA node and resource data.
 *
 *  CXONode       - CXO node data
 *  CXOResources  - CXO resource data: /xo/cxo
 *  pRPMHandle    - RPM DAL handle
 */
typedef struct
{
  npa_resource_definition   CXOResource;
  npa_node_definition       CXONode;
  npa_node_dependency       aDependency_cxo[1];
} ClockXOType;


/*=========================================================================
      Prototypes
==========================================================================*/

static npa_resource_state Clock_XODriver
(
  npa_resource *pResource,
  npa_client   *pClient,
  npa_resource_state nState
);


/*=========================================================================
      Variables
==========================================================================*/


/*
 * NPA remote XO resource.
 */
static npa_remote_resource_definition Clock_XORemote =
{
  "/clkregim/lpass/xo/cxo",
  "clk0\x00\x00\x00\x00",
  "/protocol/rpm/rpm",
  &npa_max_plugin,
  npa_remote_resource_local_aggregation_driver_fcn, 
  "Enable/Disable",
  1
};


/*
 * ClockXO
 *
 * Low power resource data.
 */
static ClockXOType Clock_XO =
{
  /*
   * CXOResource
   */
  {
    "/xo/cxo", 
    "on/off",
    CLOCK_SOURCE_REQUIRED,  /* max state */
    &npa_max_plugin, 
    NPA_RESOURCE_DEFAULT,
    (npa_user_data)HAL_CLK_SOURCE_XO
  },

  /*
   * CXONode
   */
  { 
    "/node/xo/cxo",     /* name */
    Clock_XODriver,     /* driver_fcn */
    NPA_NODE_DEFAULT,   /* attributes */
    NULL,               /* data */
    NPA_ARRAY(Clock_XO.aDependency_cxo),
    1, &Clock_XO.CXOResource
  },

  /*
   * aDependency_cxo
   */
  {
    {
      SLEEP_LPR_NODE_NAME,
      NPA_CLIENT_REQUIRED,
    }
  }
};


/*=========================================================================
      Functions
==========================================================================*/


/* =========================================================================
**  Function : Clock_XODriver
** =========================================================================*/
/**
  Handle state changes on the CXO node.
 
  This function handles state changes on the XO node and will forward
  updates to the low-power-resource.
 
  @param pResource [in] -- The NPA resource being requested.
  @param pClient [in]   -- Pointer to the client making the request.
  @param nState [in]    -- New state of the resource.

  @return
  New state of the resource.

  @dependencies
  None.
*/ 

static npa_resource_state Clock_XODriver
(
  npa_resource      *pResource,
  npa_client        *pClient,
  npa_resource_state nState
)
{
  /*-----------------------------------------------------------------------*/
  /* Get the cxo node's client handle to the sleep LPR node.               */
  /*-----------------------------------------------------------------------*/

  npa_client_handle hClientHandle = NPA_DEPENDENCY(pResource, 0);

  /*-----------------------------------------------------------------------*/
  /* At init time, register the LPR with the sleep LPR node, and request   */
  /* a bit mask to use for the CXO LPRMs from the sleep LPR node.          */
  /*-----------------------------------------------------------------------*/

  if (pClient->type == NPA_CLIENT_INITIALIZE)
  {
    if((HAL_clk_SourceType)pResource->definition->data == HAL_CLK_SOURCE_XO)
    {
      sleep_define_lpr_str("cxo", hClientHandle);
    }
  }

  /*-----------------------------------------------------------------------*/
  /* Issue a request to the sleep node to enable or disable this node's    */
  /* LPRMs during sleep.                                                   */
  /*  0: XO is not required at all by any insuppressible clocks.           */
  /*  1: XO is required by insuppressible clocks.                          */
  /*-----------------------------------------------------------------------*/

  if (nState == CLOCK_SOURCE_REQUIRED)
  {
    npa_complete_request(hClientHandle);
  }
  else
  {
    npa_issue_scalar_request(hClientHandle, SLEEP_LPRM_NUM(0));
  }

  Clock_SWEvent(CLOCK_EVENT_XO, 1, !nState);

  return nState;

} /* END Clock_XODriver */


/* =========================================================================
**  Function : Clock_XOCreateClientCB
** =========================================================================*/
/**
  Callback when an XO node is created.
 
  This function is called by the NPA framework when the given XO node is
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

static void Clock_XOCreateClientCB
(
  void        *pContext,
  unsigned int nEventType,
  void        *pNodeName,
  unsigned int nNodeNameSize
)
{
  npa_node_definition *pNode = (npa_node_definition *)pContext;
  ClockDrvCtxt *pCtxt = (ClockDrvCtxt *)pNode->data;
  uint32 nIndex = 0xFF;
  uint32 nState;

  /*-----------------------------------------------------------------------*/
  /* Create the appropriate NPA client.                                    */
  /*-----------------------------------------------------------------------*/

  if (pNode == &Clock_XO.CXONode)
  {
    nIndex = pCtxt->anSourceIndex[HAL_CLK_SOURCE_XO];

    pCtxt->aSources[nIndex].NPAHandle = 
      npa_create_sync_client(
        Clock_XO.CXOResource.name, "/clock", NPA_CLIENT_REQUIRED);
  }

  /*-----------------------------------------------------------------------*/
  /* Send current state info to XO NPA driver function.                    */
  /*-----------------------------------------------------------------------*/

  if(nIndex != 0xFF)
  {
    if(pCtxt->aSources[nIndex].nReferenceCount > 0)
    {
      nState = CLOCK_SOURCE_REQUIRED;
    }
    else
    {
      nState = CLOCK_SOURCE_NOT_REQUIRED;
    }
  
    npa_issue_scalar_request(pCtxt->aSources[nIndex].NPAHandle, nState); 
  }

} /* END Clock_XOCreateClientCB */


/* =========================================================================
**  Function : Clock_InitXO
** =========================================================================*/
/*
  See ClockMSS.h
*/

DALResult Clock_InitXO
(
  ClockDrvCtxt *pCtxt
)
{
  npa_resource_state nInitialState;

  /*-----------------------------------------------------------------------*/
  /* Init CXO node.                                                        */
  /*-----------------------------------------------------------------------*/

  Clock_XO.CXONode.data = (npa_user_data)pCtxt;

  nInitialState = 0;

  npa_define_node_cb(
    &Clock_XO.CXONode, &nInitialState, Clock_XOCreateClientCB,
    &Clock_XO.CXONode);


  /*-----------------------------------------------------------------------*/
  /* Send initial vote of "1" to keep XO in the active set.                */
  /*-----------------------------------------------------------------------*/

  npa_remote_define_resource(&Clock_XORemote, 1, NULL);

  /*-----------------------------------------------------------------------*/
  /* Good to go.                                                           */
  /*-----------------------------------------------------------------------*/

  return DAL_SUCCESS;

} /* END Clock_InitXO */

