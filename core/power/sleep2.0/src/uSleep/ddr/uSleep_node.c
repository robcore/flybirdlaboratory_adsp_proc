/*==============================================================================
  FILE:         uSleep_node.c

  OVERVIEW:     This file provides the /core/uSleep node setup

  DEPENDENCIES: None
  
                Copyright (c) 2014 Qualcomm Technologies, Inc. (QTI).
                All Rights Reserved.
                Qualcomm Technologies Confidential and Proprietary
================================================================================
$Header: //components/rel/core.adsp/2.6.1/power/sleep2.0/src/uSleep/ddr/uSleep_node.c#1 $
$DateTime: 2014/10/16 12:45:40 $
==============================================================================*/
#include "uSleep.h"
#include "uSleepi.h"
#include "uSleep_util.h"
#include "CoreVerify.h"
#include "npa.h"
#include "npa_resource.h"
#include "sleep_idle_plugin.h"

/*==============================================================================
                             FORWARD DECLARATIONS
 =============================================================================*/
static npa_resource_state uSleepNode_driver(npa_resource       *resource,
                                            npa_client         *client,
                                            npa_resource_state state);

static npa_resource_state uSleep_resourceUpdateFn(npa_resource      *resource,
                                                  npa_client_handle client);

/*==============================================================================
                              NODE DEFINITION
 =============================================================================*/

/**
 * uSleep_resourcePlugin 
 *
 * @brief It is custom AND plugin with internal/custom clients are considered
 *        only in presence of external/default clients.
 *
 * Internal clients are used to control uSleep node based on other sleep
 * restrictions.
 */
const npa_resource_plugin uSleep_resourcePlugin = 
{
  uSleep_resourceUpdateFn,                       /* Update function */
  NPA_CLIENT_REQUIRED | NPA_CLIENT_SUPPRESSIBLE |
    NPA_CLIENT_CUSTOM1,                          /* Supported clients */
  NULL,                                          /* Client creation function */
  NULL                                           /* Client destroy function */
};

/*
 * Dependencies to wait on before setting up uSleep NPA nodes.
 */
static const char *g_uSleepDependencies[] =
{
  "/sleep/idle/plugin",
  USLEEP_NPA_RESOURCE_BIMC,
  USLEEP_NPA_RESOURCE_SNOC
};

/*
 * g_uSleepNodeDependency
 */
static npa_node_dependency g_uSleepNodeDependency[1] =
{
  {
    "/sleep/idle/plugin",
    SLEEP_IDLE_PLUGIN_CLIENT_ALLOW_USLEEP,
  },
};

/* 
 * g_uSleepNodeResource
 */
static npa_resource_definition g_uSleepNodeResource[] =
{
  {
    "/core/uSleep",         /* Name */
    "Allow",                /* Units */
    1,                      /* Max State */
    &uSleep_resourcePlugin, /* Plugin */
    NPA_RESOURCE_INTERPROCESS_ACCESS_ALLOWED, /* Attributes */
    NULL,                   /* User Data */
    NULL                    /* Query Function */
  }
};

/*
 * uSleep_node
 */
npa_node_definition uSleep_node =
{
  "/node/core/uSleep",                /* Name */
  uSleepNode_driver,                  /* Driver_fcn */
  NPA_NODE_DEFAULT,                   /* Attributes */
  NULL,                               /* Data */
  NPA_ARRAY(g_uSleepNodeDependency),  /* Dependencies */
  NPA_ARRAY(g_uSleepNodeResource)     /* Resources */
};

/*==============================================================================
                       INTERNAL FUNCTION DEFINITIONS
 =============================================================================*/
/**
 * uSleepNode_driver
 * 
 * @brief Driver function for the uSleep node
 *
 * @param resource: The NPA resource being requested.
 * @param client:   Pointer to the client making the request.
 * @param state:    New state of the resource.
 *
 * @return: New state of the resource
 */
static npa_resource_state uSleepNode_driver(npa_resource       *resource,
                                            npa_client         *client,
                                            npa_resource_state state)
{
  /* Get the dependency of the uSleep node. */
  npa_client_handle client_handle = NPA_DEPENDENCY(resource, 0);

  if( client->type == NPA_CLIENT_INITIALIZE )
  {
    /* Nothing to do currently. */
  }

  npa_issue_required_request(client_handle, state);

  return state;
}

/**
 * uSleep_resourceUpdateFn
 *
 * @brief Update function for the uSleep NPA resource.
 *
 * @param resouce: Pointer to uSleep npa resource.
 * @param client:  Client whose request is being processed.
 *
 * @return State of uSleep NPA resource after considering client's request.
 */
static npa_resource_state uSleep_resourceUpdateFn(npa_resource      *resource,
                                                  npa_client_handle client)
{
  static npa_resource_state customClientsState = 1;
  static npa_resource_state defaultClientsState = 0;

  /* Initialize internal AND aggregations so that subsequent REQUIRED 
   * requests are aggregated correctly. */
  if(0 == resource->sequence)
  {
    resource->internal_state[NPA_REQUIRED_INDEX] = 0x1;
    resource->internal_state[NPA_SUPPRESSIBLE_INDEX] = 0x1;
  }

  switch(client->type)
  {
    case NPA_CLIENT_CUSTOM1:
    {
      /* Right now we just have one internal client but if we start to
       * have more, we will need a dedicated aggregator for them */
      customClientsState = NPA_PENDING_REQUEST(client).state;
      break;
    }

    default:
    {
      /* All default clients are handled by npa plugin's update function */
      defaultClientsState = npa_binary_and_plugin.update_fcn(resource, client);
      break;
    }
  }

  return ((customClientsState && defaultClientsState) ? 1 : 0);

}

/**
 * uSleepNode_registerCB
 * 
 * @brief Register the uSleep node and initialize node data
 * 
 * @param All unused
 */
static void uSleepNode_registerCB(void         *context,
                                  unsigned int  eventType,
                                  void         *data,
                                  unsigned int  dataSize )
{
  npa_resource_state  initialState = 0;
  
  /* Initially disabled */
  npa_define_node(&uSleep_node, &initialState, NULL);

  /* Create the query handles so we can turn DDR on & off */
  uSleep_createQueryHandles();

  /* Set initial uSleep transition times which will also update the node client */
  uSleep_setTransitionTime(USLEEP_SEED_ENTER_TIME, USLEEP_SEED_EXIT_TIME);

  return;
}

/*==============================================================================
                         EXTERNAL FUNCTION DEFINITIONS
 =============================================================================*/
/*
 * uSleepNode_initialize
 */
void uSleepNode_initialize(void)
{
  /* Register a callback for when the necessary dependencies are available,
   * in order to register the nodes and other requirements that uSleep owns. */
  npa_resources_available_cb(NPA_ARRAY(g_uSleepDependencies),
                             uSleepNode_registerCB, NULL);

  return;
}

