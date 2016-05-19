/**
 * @file ul_int.c
 *
 * @note This file implements the internal arbitration functions
 *
 *  Copyright (c) 2010-2014 Qualcomm Technologies Incorporated.
 *             All Rights Reserved.
 *          QUALCOMM Proprietary/GTDR
 *
 * $Header: //components/rel/core.adsp/2.6.1/buses/icb/src/common/ul_int.c#1 $
 * $DateTime: 2014/10/16 12:45:40 $
 * $Author: pwbldsvc $
 * $Change: 6781644 $
 *                     EDIT HISTORY FOR FILE
 *
 * This section contains comments describing changes made to the module.
 * Notice that changes are listed in reverse chronological order.
 *
 * when       who     what, where, why
 * --------   ---     -----------------------------------------------------------
 * 03/21/14   sds     Modify AGG_SCHEME_0 slightly - don't divide IB by ports.
 * 03/11/14   sds     Extend query function - slave port count.
 * 11/05/13   jc      Add support for client type change.
 * 07/12/13   sds     Add support for BKE thresholding and static configuration.
 * 04/29/13   sds     Fix AB/IB aggregation to clock frequency. Make sure to divide
 *                    the AB by the number of ports.
 * 11/27/12   sds     Fix NAS attribute check.
 * 11/15/12   sds     Fix NAS handling and move all RPM interactions out of this layer.
 *                    Also remove usage of unnecessary slave id array.
 * 10/03/12   sds     Clock cleanup and master clock aggregation added.
 * 08/21/12   sds     remove support for npa fork/join and add support for npa's
 *                    fire and forget
 * 04/25/12   dj      add dal config support
 * 03/16/12   pm      Removed SIGN macro to eliminate compiler warning
 * 04/29/11   rng     Added support for requested bandwidth tier
 * 04/27/11   rng     Changed bandwidth to 64 bits
 * 04/27/11   sds     Cleanup compiler warning
 * 02/11/11   rng     Add debug log messages
 * 08/17/10   rng     Slave resources cannot have subnode dependencies
 * 07/15/10   pm      Revisions to get basic functionality on WINSIM
 * 04/27/10   rng     Initial version
 *
 */

#include "ul_i.h"
#include "ddiaxicfgint.h"
#include "icb_rpm_types.h"
#include "DALStdDef.h"
#include "DALSys.h"
#include "ULogFront.h"
#include "ul_tree.h"

/*============================================================================
                          DEFINES
============================================================================*/

/* Divide and round up to the nearest integer */
#define CEIL_DIV(dividend, divisor) (((dividend)/(divisor))+(((dividend)%(divisor))?1:0))

#define MAX(x,y) ((x)>(y)?(x):(y))

#define BW_TO_CLK_FREQ_KHZ( bw, bus_width ) \
          (CEIL_DIV(CEIL_DIV((bw),(bus_width)), 1000 ))

#define UL_BW_REQUEST_LIST_SIZE    10

/**
 * Slave Request Type
 *
 * Structure of Ib and Ab values, to pass to a Slave node when
 * requesting bandwidth 
 */
typedef struct
{
  int32                i32IntMasterID;
  int32                i32IntSlaveID;
  uint64               uIb;       /**< Instantaneous BW request in Bytes/Sec */
  uint64               uAb;       /**< Arbitrated BW request in Bytes/Sec */
} ul_slave_bw_request_type;

typedef struct
{
  ul_treeNodeType       * routeTreeRoot; /* Route tree root */
  uint32                  uNumMasters;
  uint32                  uNumSlaves;
  ul_master_data_type  ** aMasterList;
  ul_slave_data_type   ** aSlaveList;
} ul_int_data_type;

/* forward declarations */
void process_master_request( ul_request_type * );
void process_slave_request( ul_request_type * );

/* extern the Arbiter Internal Log */
extern ULogHandle icbArbLog;

/*============================================================================
                          STATIC INTERNAL DATA
============================================================================*/

static ul_int_data_type ul_int;

/*============================================================================
                      STATIC FUNCTIONS - CLOCKS
============================================================================*/
/**=============================================================================

  ul_clock_create_clients

  @brief Performs creation of clock handles for all clocks

  @param None

  @return None

==============================================================================*/
static void ul_clock_create_clients
(
  ul_clock_type *    clock,
  const char * const clientName
)
{
  clock->normal =
    npa_create_sync_client( clock->name, clientName, NPA_CLIENT_REQUIRED );
  clock->suppressible =
    npa_create_sync_client( clock->name, clientName, NPA_CLIENT_SUPPRESSIBLE );
}

/**=============================================================================

  ul_clock_issue_request

  @brief Issues requests on the clock to the appropriate handle

  @param None

  @return None

==============================================================================*/
static void ul_clock_issue_request
(
  ul_clock_type *       clock,
  npa_request_attribute reqAttrs,
  DALBOOL               bSuppressible,
  uint32                uFreq
)
{
  npa_client_handle hClient;

  /* Get the proper client, accounting for suppressible clients. */
  if( bSuppressible )
  {
    hClient = clock->suppressible;
  }
  else
  {
    hClient = clock->normal;
  }

  /* Set our request attributes, and go. */
  npa_set_request_attribute( hClient, reqAttrs );
  npa_issue_required_request( hClient, uFreq );
}

/*============================================================================
                          STATIC FUNCTIONS
============================================================================*/
/**=============================================================================

  ul_target_init_cb

  @brief Performs post master node creation initialization

  @param None

  @return None

==============================================================================*/
static void ul_target_init_cb
(
  void *       pContext,
  unsigned int u32EventType,
  void *       pData,
  unsigned int u32DataSize
)
{
  uint32 uIdx, uClockIdx;

  /* Unused parameters */
  (void)pContext;
  (void)u32EventType;
  (void)pData;
  (void)u32DataSize;

  /* Create necessary bus and clock NPA clients */
  for( uIdx = 0;
       uIdx < ul_int.uNumMasters;
       uIdx++ )
   {
    ul_master_data_type *pMaster = ul_int.aMasterList[uIdx];
    pMaster->masterRequest.req_func = process_master_request;
    /* Slave clocks. */
    for( uClockIdx = 0;
         uClockIdx < pMaster->u32MstrClockCount;
         uClockIdx++ )
    {
      ul_clock_create_clients( &pMaster->aMstrClocks[uClockIdx],
                                pMaster->clientName );
    }
  }

  for( uIdx = 0;
       uIdx < ul_int.uNumSlaves;
       uIdx++ )
  {
    ul_slave_data_type *pSlave = ul_int.aSlaveList[uIdx];
    pSlave->slvRequest.req_func= process_slave_request;
    /* Slave clocks. */
    for( uClockIdx = 0;
         uClockIdx < pSlave->u32SlvClockCount;
         uClockIdx++ )
    {
      ul_clock_create_clients( &pSlave->aSlvClocks[uClockIdx],
                                pSlave->clientName );
    }

    /* Memory clocks. */
    for( uClockIdx = 0;
         uClockIdx < pSlave->u32MemClockCount;
         uClockIdx++ )          
    {
      ul_clock_create_clients( &pSlave->aMemClocks[uClockIdx],
                                pSlave->clientName );
    }
  }

  /* All master nodes have been defined so issue the marker */
  npa_define_marker( UL_MASTERS_CREATED );
}

/**=============================================================================

  compute_bw

  @brief Performs post master node creation initialization

  @param state - a pointer to the node state to work with

  @return The total bandwidth on the node.

==============================================================================*/
uint64 compute_bw( icb_bus_def_type *pBus, ul_node_state_type *state, uint32 uPorts )
{
  uint64 uAB, uSuppAB, uTotalBW;

  /* First, calculate the total bandwidth per port on this node. */
  if(state->uSuppAb == 0)
  {
    uSuppAB = 0;
  }
  else
  {
    uSuppAB = CEIL_DIV(state->uAb + state->uSuppAb, MAX(1, uPorts));
  }
  uAB      = CEIL_DIV(state->uAb, MAX(1, uPorts));
  uTotalBW = MAX(MAX(state->uIb, state->uSuppIb), MAX(uAB, uSuppAB));

  /* Update the input for the aggregation scheme. */
  switch(pBus->aggType)
  {
    case ICB_AGG_SCHEME_0:
      if(state->uSuppAb != 0)
      {
        state->uSuppAb = CEIL_DIV((state->uAb + state->uSuppAb) * pBus->uP0, 100);
        state->uSuppAb = CEIL_DIV(state->uSuppAb, MAX(1, uPorts));
      }
      state->uAb     = CEIL_DIV(state->uAb * pBus->uP0, 100);
      state->uAb     = CEIL_DIV(state->uAb, MAX(1, uPorts));
      
      state->uIb     = CEIL_DIV(state->uIb * 100,  pBus->uP1);
      state->uSuppIb = CEIL_DIV(state->uSuppIb * 100,  pBus->uP1);
      break;
    
    case ICB_AGG_SCHEME_LEGACY:
    /* Use the legacy scheme if we don't know what scheme we have. */
    default:
      state->uAb = uAB;
      state->uSuppAb = uSuppAB;
      break;
  }


  return uTotalBW;
}

void process_master_request( ul_request_type * pRequest )
{
  uint64 uBW, uSuppBW, uTotalBW;
  uint32 uReqIdx;
  ul_master_data_type  * pMasterData;
  bool is_nas;
  npa_request_attribute reqAttrs;
  bool is_max_suppressible, is_min_suppressible;
  uint64 uMaxBW, uMinBW;
  ul_node_state_type state;

  /* Set the nas flag */
  is_nas = (pRequest->hClient->request_attr & NPA_REQUEST_NEXT_AWAKE);

  /* Collect request attributes to forward. */
  reqAttrs = (npa_request_attribute)pRequest->hClient->request_attr;
  reqAttrs &= ~NPA_REQUEST_CHANGED_TYPE;  /* Mask client type change attribute */

  pMasterData = (ul_master_data_type*)pRequest->pRequest;

  /* Search the request list to get the MAX Ib */
  for( uBW = 0, uSuppBW = 0, uReqIdx = 0; uReqIdx < pMasterData->requestList.uEntryCount; uReqIdx++ )
  {
    if( NPA_CLIENT_SUPPRESSIBLE_VECTOR == pMasterData->requestList.aRequestList[uReqIdx]->hClient->type )
    {
      if (pMasterData->requestList.aRequestList[uReqIdx]->uIb > uSuppBW)
      {
        uSuppBW = pMasterData->requestList.aRequestList[uReqIdx]->uIb;
      }
    }
    else
    {
      if (pMasterData->requestList.aRequestList[uReqIdx]->uIb > uBW)
      {
        uBW = pMasterData->requestList.aRequestList[uReqIdx]->uIb;
      }
    }
  }
  pMasterData->mstrState.uSuppIb = uSuppBW;
  pMasterData->mstrState.uIb = uBW;

  /* Compute effective bandwidth based on aggregation scheme. */
  state = pMasterData->mstrState;
  uTotalBW = compute_bw( pMasterData->pMasterDef->pBus,
                         &state,
                         pMasterData->pMasterDef->uNumPorts );
  uSuppBW = MAX(state.uSuppIb, state.uSuppAb);
  uBW = MAX(state.uIb, state.uAb);

  /* Update QoS HW */
  (void) AxiCfgInt_QoSSetMasterBW( pMasterData->eExtMasterID,
                                   uTotalBW,
                                   pMasterData->mstrState.uAb +
                                   pMasterData->mstrState.uSuppAb,
                                   pMasterData->mstrState.uAb,
                                   is_nas );

  /* Issue the highest BW clock request first, to insure clock does not
   * glitch down.
   */
  if (uBW >= uSuppBW)
  {
    is_max_suppressible = false;
    uMaxBW = uBW;
    is_min_suppressible = true;
    uMinBW = uSuppBW;
  }
  else
  {
    is_max_suppressible = true;
    uMaxBW = uSuppBW;
    is_min_suppressible = false;
    uMinBW = uBW;
  }
  for( uReqIdx = 0; uReqIdx < pMasterData->u32MstrClockCount; uReqIdx++)
  {
    ul_clock_issue_request( &pMasterData->aMstrClocks[uReqIdx],
                             reqAttrs,
                             is_max_suppressible,
                             (uint32) BW_TO_CLK_FREQ_KHZ( uMaxBW, pMasterData->u32SlaveWidth) );
    ul_clock_issue_request( &pMasterData->aMstrClocks[uReqIdx],
                             reqAttrs,
                             is_min_suppressible,
                             (uint32) BW_TO_CLK_FREQ_KHZ( uMinBW, pMasterData->u32SlaveWidth) );
  }
}

void process_slave_request( ul_request_type * pRequest )
{
  uint32 uReqIdx;
  ul_slave_data_type  * pSlaveData;
  bool is_nas;
  npa_request_attribute reqAttrs;
  uint64 uBW, uSuppBW;
  bool is_max_suppressible, is_min_suppressible;
  uint64 uMaxBW, uMinBW;
  ul_node_state_type state;

  /* set the nas flag */
  is_nas = (pRequest->hClient->request_attr & NPA_REQUEST_NEXT_AWAKE);

  /* Collect request attributes to forward. */
  reqAttrs = (npa_request_attribute)pRequest->hClient->request_attr;
  reqAttrs &= ~NPA_REQUEST_CHANGED_TYPE;  /* Mask client type change attribute */

  pSlaveData = (ul_slave_data_type*)pRequest->pRequest;

  /* Update BW to config layer. */
  (void)AxiCfgInt_QoSSetSlaveBW( pSlaveData->eExtSlaveID,
                                 pSlaveData->slvState.uAb +
                                 pSlaveData->slvState.uSuppAb,
                                 pSlaveData->slvState.uAb,
                                 is_nas );

  /* Search the request list to get the MAX Ib */
  for( uBW = 0, uSuppBW = 0, uReqIdx = 0; uReqIdx < pSlaveData->requestList.uEntryCount; uReqIdx++ )
  {
    if( NPA_CLIENT_SUPPRESSIBLE_VECTOR == pSlaveData->requestList.aRequestList[uReqIdx]->hClient->type )
    {
      if( pSlaveData->requestList.aRequestList[uReqIdx]->uIb > uSuppBW )
      {
        uSuppBW = pSlaveData->requestList.aRequestList[uReqIdx]->uIb;
      }
    }
    else
    {
      if( pSlaveData->requestList.aRequestList[uReqIdx]->uIb > uBW )
      {
        uBW = pSlaveData->requestList.aRequestList[uReqIdx]->uIb;
      }
    }
  }
  pSlaveData->slvState.uSuppIb = uSuppBW;
  pSlaveData->slvState.uIb = uBW;

  /* Compute effective bandwidth based on aggregation scheme. */
  state = pSlaveData->slvState;
  (void)compute_bw( pSlaveData->pSlaveDef->pBus,
                    &state,
                    pSlaveData->pSlaveDef->uNumPorts );
  uSuppBW = MAX(state.uSuppIb, state.uSuppAb);
  uBW = MAX(state.uIb, state.uAb);

  /* Issue the highest BW clock request first, to insure clock does not
   * glitch down.
   */
  if (uBW >= uSuppBW)
  {
    is_max_suppressible = false;
    uMaxBW = uBW;
    is_min_suppressible = true;
    uMinBW = uSuppBW;
  }
  else
  {
    is_max_suppressible = true;
    uMaxBW = uSuppBW;
    is_min_suppressible = false;
    uMinBW = uBW;
  }
  for( uReqIdx = 0; uReqIdx < pSlaveData->u32SlvClockCount; uReqIdx++)
  {
    ul_clock_issue_request( &pSlaveData->aSlvClocks[uReqIdx],
                             reqAttrs,
                             is_max_suppressible,
                             (uint32) BW_TO_CLK_FREQ_KHZ( uMaxBW, pSlaveData->u32SlaveWidth) );
    ul_clock_issue_request( &pSlaveData->aSlvClocks[uReqIdx],
                             reqAttrs,
                             is_min_suppressible,
                             (uint32) BW_TO_CLK_FREQ_KHZ( uMinBW, pSlaveData->u32SlaveWidth) );
  }

  for( uReqIdx = 0; uReqIdx < pSlaveData->u32MemClockCount; uReqIdx++)
  {
    ul_clock_issue_request( &pSlaveData->aMemClocks[uReqIdx],
                             reqAttrs,
                             is_max_suppressible,
                             (uint32) BW_TO_CLK_FREQ_KHZ( uMaxBW, pSlaveData->u32SlaveWidth) );
    ul_clock_issue_request( &pSlaveData->aMemClocks[uReqIdx],
                             reqAttrs,
                             is_min_suppressible,
                             (uint32) BW_TO_CLK_FREQ_KHZ( uMinBW, pSlaveData->u32SlaveWidth) );
  }
}

/**
 * @copydoc
 */
void ul_issue_pair_request
(
  npa_client_handle    client,
  ul_bw_request_type * pBWReq,
  ul_bw_request_type * pOldReq,
  ul_pair_type       * pMSPair,
  DALBOOL              clkOnly
)
{
  ul_slave_data_type       * pSlaveData;
  ul_master_data_type      * pMasterData;
  bool is_suppressible;
  bool is_changed;

  /* Set the suppressible flag for future calculations */
  is_suppressible = (NPA_CLIENT_SUPPRESSIBLE_VECTOR == client->type);

  /* Set the client type change flag */
  is_changed = (client->request_attr & NPA_REQUEST_CHANGED_TYPE);

  pSlaveData = pMSPair->pSlaveData;
  pMasterData = pMSPair->pMasterData;

  if( ( pBWReq->uAb == pOldReq->uAb && pBWReq->uIb == pOldReq->uIb ) && !is_changed )
  {
    /* Nothing to do so return */
    return;
  }

  /* Enqueue the slave request */
  pSlaveData->slvRequest.hClient = client; 
  ul_request_enqueue( &pSlaveData->slvRequest );

  /* Enqueue the master request */
  pMasterData->masterRequest.hClient = client;
  ul_request_enqueue( &pMasterData->masterRequest );

  /* Log the request */
  ULOG_RT_PRINTF_5(icbArbLog,
                   "Issue Pair Request (MID: %d, SID: %d) (request: Ib: 0x%08x Ab: 0x%08x) (clkOnly: %d)",
                   pMasterData->eExtMasterID,
                   pSlaveData->eExtSlaveID,
                   (uint32)pBWReq->uIb,
                   (uint32)pBWReq->uAb,
                   clkOnly );

  /* Update this request */
  if( is_suppressible )
  {
    if( !is_changed )
    {
      pMasterData->mstrState.uSuppAb -= pOldReq->uAb;
      pSlaveData->slvState.uSuppAb   -= pOldReq->uAb;
    }
    else
    {
      pMasterData->mstrState.uAb -= pOldReq->uAb;
      pSlaveData->slvState.uAb   -= pOldReq->uAb;
    }
    pMasterData->mstrState.uSuppAb += pBWReq->uAb;
    pSlaveData->slvState.uSuppAb   += pBWReq->uAb;
  }
  else
  {
    if( !is_changed )
    {
      pMasterData->mstrState.uAb -= pOldReq->uAb;
      pSlaveData->slvState.uAb   -= pOldReq->uAb;
    }
    else
    {
      pMasterData->mstrState.uSuppAb -= pOldReq->uAb;
      pSlaveData->slvState.uSuppAb   -= pOldReq->uAb;
    }
    pMasterData->mstrState.uAb += pBWReq->uAb;
    pSlaveData->slvState.uAb   += pBWReq->uAb;
  }
}

/** ul_add_bw_request
 * 
 * @brief Adds a BW request to the passed request list
 * 
 * @author seansw (09/24/2012)
 * 
 * @param pBWReq 
 * @param pRequestList
 */
void ul_add_bw_request
(
  ul_bw_request_type      * pBWReq,
  ul_bw_request_list_type * pRequestList
)
{
  void *  oldList;

  if( NULL == pRequestList || NULL == pBWReq )
  {
    return;
  }

  /* Increase the size of the list if necessary */
  if( pRequestList->uEntryCount + 1 >= pRequestList->uListSize )
  {
    /* Save the old list */
    oldList = pRequestList->aRequestList;

    if(DAL_SUCCESS !=
       DALSYS_Malloc( (pRequestList->uListSize + UL_BW_REQUEST_LIST_SIZE) * sizeof(void*),
                      (void **)&pRequestList->aRequestList ))
    {
      pRequestList->aRequestList = oldList;
      return;
    }

    if( NULL != oldList )
    {
      /* Copy and free old buffer. */
      DALSYS_memcpy(
        (void*)pRequestList->aRequestList,
        oldList,
        pRequestList->uListSize * sizeof(void*));
      DALSYS_Free( oldList );
    }
    pRequestList->uListSize += UL_BW_REQUEST_LIST_SIZE;
  }

  pRequestList->aRequestList[pRequestList->uEntryCount++] = pBWReq;
}

/** ul_remove_bw_request
 * 
 * @brief Removes a BW request from the passed request list
 * 
 * @author seansw (09/24/2012)
 * 
 * @param pBWReq 
 * @param pRequestList
 */
void ul_remove_bw_request
(
  ul_bw_request_type      * pBWReq,
  ul_bw_request_list_type * pRequestList
)
{
  uint32 i;

  if( NULL == pRequestList || NULL == pBWReq )
  {
    return;
  }

  for( i = 0; i < pRequestList->uEntryCount; i++ )
  {
    if( pRequestList->aRequestList[i] == pBWReq )
    {
      /* We found the request to remove */
      break;
    }
  }

  if( i < pRequestList->uEntryCount )
  {
    memmove(&pRequestList->aRequestList[i],
            &pRequestList->aRequestList[i+1],
            (--pRequestList->uEntryCount - i)*sizeof(void*));
  }
}

/*==============================================================================

  FUNCTION   ul_int_init

  DESCRIPTION 
    Initialize and define the bus arbiter subnodes

  PARAMETERS
    None

  RETURN VALUE    
    None

==============================================================================*/
void ul_int_init( void )
{
  uint32 u32ul_clk_node_list_size;
  const char ** ul_clock_node_list;

  /* Retrieve from DAL properties. */
  ul_int.routeTreeRoot     = *( (ul_treeNodeType **) AxiCfgInt_GetProperty( "icb_arb_route_tree" ) );
  ul_int.uNumMasters       = *((uint32 * ) AxiCfgInt_GetProperty( "icb_arb_master_count" ) );
  ul_int.uNumSlaves        = *((uint32 * ) AxiCfgInt_GetProperty( "icb_arb_slave_count" ) );
  ul_int.aMasterList       = (ul_master_data_type **)AxiCfgInt_GetProperty( "icb_arb_master_list" );
  ul_int.aSlaveList        = (ul_slave_data_type **) AxiCfgInt_GetProperty( "icb_arb_slave_list" );
  u32ul_clk_node_list_size = *( (uint32 *)AxiCfgInt_GetProperty("icb_arb_clk_count") );
  ul_clock_node_list       = (const char ** )AxiCfgInt_GetProperty("icb_arb_clock_node_list");

  /* Set a callback once all clock nodes have been created */
  npa_resources_available_cb( u32ul_clk_node_list_size,
                              ul_clock_node_list,
                              ul_target_init_cb,
                              NULL );
}

/** @copydoc */
ul_route_list_type *ul_get_route
(
  ICBId_MasterType eMaster,
  ICBId_SlaveType  eSlave
)
{
  uint64   uHashIdx;

  /* Check for invalid masters and slaves */
  if( eMaster & ~0xFFFFFFFF || eSlave & ~0xFFFFFFFF )
  {
    /* This is an internal master or slave and cannot be used as an endpoint */
    return NULL;
  }

  /* Find the route in the tree */
  uHashIdx =  ((uint64)eMaster & 0xFFFFFFFF) << 32;
  uHashIdx |= ((uint64)eSlave & 0xFFFFFFFF);

  return (ul_route_list_type*)ul_TreeLookup( ul_int.routeTreeRoot, uHashIdx );
}

/* @copydoc ul_target_get_slave_list */
void ul_target_get_slave_list
(
  ul_int_slave_list_type *pSlaveList
)
{
  pSlaveList->uNumSlaves = ul_int.uNumSlaves;
  pSlaveList->aSlaveList = ul_int.aSlaveList;
}
