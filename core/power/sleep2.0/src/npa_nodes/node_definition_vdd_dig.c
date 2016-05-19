/*============================================================================
  FILE:         node_definition_vdd_dig.c

  OVERVIEW:     This file provides the NPA node definition for the
                /rail/vdd_dig node.

  DEPENDENCIES: None

                Copyright (c) 2011-2012 Qualcomm Technologies Incorporated.
                All Rights Reserved.
                Qualcomm Confidential and Proprietary
============================================================================*/
#include "comdef.h"
#include "npa.h"
#include "npa_resource.h"
#include "sleep_lpr.h"
#include "CoreVerify.h"

/* ==================================================================
                   INTERNAL VARIABLE DECLARATIONS
   ================================================================== */
const uint32 VDD_DIG_MIN_LEVEL_ZERO_VOLTAGE = 1100;

/* ==================================================================
              INTERNAL FUNCTION DECLARATIONS
   ================================================================== */
/**
 *
 * @brief sleep_vdd_dig_driver
 *
 * Driver function for the vdd_dig node.  This function gets called
 * every time a client request is made that changes the state of the node.
 *
 * @param resource: The NPA resource being requested.
 * @param client:   Pointer to the client making the request.
 * @param state:    New state of the resource.
 *
 * @return: New state of the resource.
 *
*/
static npa_resource_state sleep_vdd_dig_driver ( npa_resource *resource,
                                                 npa_client *client,
                                                 npa_resource_state state )
{
  /* Get the vdd_dig node's client handle to the sleep LPR node. */
  npa_client_handle client_handle = NPA_DEPENDENCY( resource, 0 );

  /* At init time, register the LPR with the sleep LPR node. */
  if( client->type == NPA_CLIENT_INITIALIZE )
  {
    sleep_define_lpr_str( "vdd_dig", client_handle );
  }

  if ( state <= VDD_DIG_MIN_LEVEL_ZERO_VOLTAGE )
  {
    /* OK to enable only VDD dig minimization level zero. */
    npa_issue_required_request( client_handle, SLEEP_LPRM_NUM( 0 ) );
  }
  else
  {
    /* Not OK to enable any VDD dig minimization levels. */
    npa_cancel_request( client_handle );
  }

  return state;
}


/* ==================================================================
                        NODE DEFINITION
   ================================================================== */
/**
 *
 * @brief sleep_lpr_dependency
 *
 * The dependency array for the vdd_dig node.  This node depends
 * on the sleep LPR node, as it makes requests to that node when the state
 * of this node changes.
 *
*/
static npa_node_dependency sleep_lpr_dependency[1] =
{
  {
    SLEEP_LPR_NODE_NAME,
    NPA_CLIENT_REQUIRED,
  },
};

/**
 *
 * @brief sleep_vdd_dig_resource
 *
 * Resource definition for the /rail/vdd_dig resource.
 *
*/
static npa_resource_definition sleep_vdd_dig_resource[] =
{
  {
    "/rail/vdd_dig",           /* Name       */
    "millivolts",              /* Units      */
    1100,                      /* Max State  */
    &npa_max_plugin,           /* Plugin     */
    NPA_RESOURCE_DEFAULT,      /* Attributes */
    NULL,                      /* User Data  */
  }
};

/**
 *
 * @brief sleep_vdd_dig_node
 *
 * Node definition for the /rail/vdd_dig resource.
 *
*/
npa_node_definition sleep_vdd_dig_node =
{
  "/node/rail/vdd_dig",              /* Name         */
  sleep_vdd_dig_driver,              /* Driver_fcn   */
  NPA_NODE_DEFAULT,                  /* Attributes   */
  NULL,                              /* Data         */
  NPA_ARRAY(sleep_lpr_dependency),   /* Dependencies */
  NPA_ARRAY(sleep_vdd_dig_resource)  /* Resources    */
};
