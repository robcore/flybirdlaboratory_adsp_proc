/*============================================================================
@file npa_resource.c

Routines that constitute NPA's resource request pipeline

Copyright (c) 2009-2013 Qualcomm Technologies Incorporated.
All Rights Reserved.
QUALCOMM Proprietary/GTDR

$Header: //components/rel/core.adsp/2.6.1/power/npa/src/framework/npa_resource.c#1 $
============================================================================*/

#include "npa_internal.h"
#include "npa_inlines.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * <!-- _npa_update_resource_state -->
 */
static NPA_INLINE void _npa_update_resource_state( npa_resource      *resource,
                                                   npa_resource_state new_state )
{
  npa_resource_state       old_state    = resource->active_state;
  npa_resource_state_delta old_headroom = resource->active_headroom;

  resource->active_state    = new_state;
  resource->active_headroom = resource->request_state - resource->active_max;

  if ( resource->events.header && resource->events.header->reg_count > 0 &&
       ( resource->active_state != old_state || 
         resource->active_headroom != old_headroom ) )
  {
    npa_event_action  *action;
    npa_resource_state in_stm_state;
    npa_event_trigger *trigger;

    CORE_DAL_VERIFY( 
      Core_WorkQueueAlloc( npa.event_queue, (void **)&action ) );

    action->function = npa_event_action_trigger;
    trigger = &action->state.trigger;

    trigger->resource     = resource;
    trigger->old_state    = old_state;
    trigger->new_state    = resource->active_state;
    trigger->old_headroom = old_headroom;
    trigger->new_headroom = resource->active_headroom;

    npa_lock_resource( npa.in_stm_resource );

    in_stm_state = npa_resource_get_current_state( npa.in_stm_resource );

  /* If in_stm_state is non-zero (i.e. we are in Sleep or STM), ensure
     the insert does not signal the workloop */
    CORE_DAL_VERIFY( 
      Core_WorkQueueInsert( npa.event_queue, action,
                            CORE_WORKQ_TAIL, in_stm_state ? TRUE : FALSE ) );

    npa_unlock_resource( npa.in_stm_resource );
  }
}


/**
 * <!-- npa_update_resource_state -->
 */ 
void npa_update_resource_state( npa_resource      *resource,
                                npa_resource_state new_state )
{
  _npa_update_resource_state( resource, new_state );
}


/**
 * <!-- npa_invoke_update_function -->
 *
 * @brief Call the resource's active plugin's update function.
 *
 * @param resource : The resource to update.
 * @param client : The client causing the update. 
 */
static NPA_INLINE void npa_invoke_update_function( npa_resource *resource,
                                                   npa_client   *client )
{
  resource->request_state = 
    resource->active_plugin->update_fcn( resource, client );
}


/**
 * <!-- npa_invoke_driver_function -->
 *
 * @brief Resource short circuiting logic and call to resource's driver function
 *
 * @param resource : The resource to update.
 * @param client : The client causing the update. 
 */
static NPA_INLINE void npa_invoke_driver_function( npa_resource *resource,
                                                   npa_client   *client )
{
  npa_resource_state new_state = 
    ( npa_resource_has_attribute( resource, NPA_RESOURCE_VECTOR_STATE ) ) ?
    resource->request_state : MIN( resource->request_state, 
                                   resource->active_max );

  /* Call the driver function in the following cases -
   * - the resource has the DRIVER_UNCONDITIONAL attribute set
   * - the overall aggregation changes
   * - the required aggregation changes
   * - the resource has dependencies and the suppressible aggregation changes
   * - the current client changed its request type
   */
  if ( npa_resource_has_attribute( resource, NPA_RESOURCE_DRIVER_UNCONDITIONAL )
       || ( new_state != resource->active_state )
       || ( resource->required_state != 
                      NPA_RESOURCE_REQUIRED_REQUEST(resource) )
       || ( resource->node->dependency_count &&
            resource->suppressible_state != 
                      NPA_RESOURCE_SUPPRESSIBLE_REQUEST(resource) )
       || ( client->request_attr & NPA_REQUEST_CHANGED_TYPE ) )
  {
    uint64 start_time = CoreTimetick_Get64();
    new_state = resource->node->driver_fcn( resource, client, new_state );
    /* update stats */
    npa_calc_duration( start_time, CoreTimetick_Get64(),
                       &resource->_internal->driver_duration );
    /* update the required and suppressible aggregations for scalars */                       
    resource->required_state = NPA_RESOURCE_REQUIRED_REQUEST(resource);
    resource->suppressible_state = NPA_RESOURCE_SUPPRESSIBLE_REQUEST(resource);
  }

  /* Do this anyway - active max may have changed without
   * hitting driver function/changing resource state */
  _npa_update_resource_state( resource, new_state );
}


/**
 * <!-- _npa_request_serviced -->
 *
 * @brief Log that client request has been serviced and reset client 
 * request attributes.  If client is async, call callback
 *
 * @param client : The client that has just issued the request
 */
static NPA_INLINE void _npa_request_serviced( npa_client *client )
{
  npa_resource *resource = client->resource;

  /* Clear request attributes - they only apply to the first issue_request
     after npa_set_request_attribute */
  client->request_attr = NPA_REQUEST_DEFAULT;

  /* If vector logging is enabled and this is a vector resource */
  if ( npa_vector_logging_limit != 0 && 
       npa_resource_has_attribute( resource, NPA_RESOURCE_VECTOR_STATE ) )
  {
    unsigned int log_vector_len = MIN( resource->definition->max,
                                       npa_vector_logging_limit );

    ULogFront_RealTimeMultipartMsgBegin( client->log_handle );
    ULOG_RT_PRINTF_2( client->log_handle,
                      "\trequest complete "
                      "(handle: 0x%08x) (sequence: 0x%08x) "
                      "(state vector: %m)",
                      client, client->sequence );
    ULogFront_RealTimeVector( client->log_handle,
                              "0x%08x ",
                              ( unsigned short )sizeof(npa_resource_state),
                              ( unsigned short )log_vector_len,
                              resource->state_vector );
    ULogFront_RealTimeMultipartMsgEnd( client->log_handle );
  }
  else
  {
    ULOG_RT_PRINTF_4( client->log_handle,
                      "\trequest complete "
                      "(handle: 0x%08x) (sequence: 0x%08x) "
                      "(request state: %d) (active state: %d)",
                      client, client->sequence,
                      resource->request_state, resource->active_state );
  }

  /* Invoke Async Client Completion Event */
  if ( client->continuation && client->continuation->callback.callback )
  {
    npa_dispatch_event_callback( &client->continuation->callback, 0,
                                 client, sizeof(npa_client_handle) );
  }
}


/**
 * <!-- npa_request_serviced -->
 */
void npa_request_serviced( npa_client_handle client )
{
  _npa_request_serviced( client );
}

/**
 * <!-- npa_set_next_request_passthrough -->
 *
 * @brief Disables short-circuiting of the next request to this resource.
 * Both the given client and client->resource are modified to circumvent
 * NPA short-circuiting (client redundancy and new_agg == active_state)
 *
 * A different client to the resource will still be subject to the client
 * redundancy short-circuit.
 *
 * If the next request from this client is fire-and-forget, then that request
 * is still subject to the client redundancy shortcircuit. Only the next
 * synchronous request from this client will be passed through.
 *
 * @param client : A client to the resource
 */
static NPA_INLINE
void npa_set_next_request_passthrough( npa_client_handle client )
{
  /* Bypass the new_agg == active_state shortcircuit */
  npa_set_resource_attribute_for_current_request( 
                   client->resource, NPA_RESOURCE_DRIVER_UNCONDITIONAL );

  /* Bypass the client redundant request shortcircuit for THIS client */
	if ( client->issue_request == npa_enqueue_async_request )
  {
    client->issue_request = npa_enqueue_async_request_unconditional;
  }
  else if ( client->issue_request == npa_issue_sync_request )
  {
    client->issue_request = npa_issue_sync_request_unconditional;
  }
}

/**
 * <!-- npa_resource_has_client -->
 *
 * @brief Check if the given client is a client of the given resource
 *
 * @param resource : The resource in question
 * @param client : The client to check
 * 
 * @return : 1 if client is a client of the resource, else 0
 */
unsigned int npa_resource_has_client( npa_resource     *resource,
                                      npa_client_handle client )
{
  npa_client_handle c;
  
  CORE_VERIFY_PTR( resource );
  CORE_VERIFY_PTR( client );

  for ( c = resource->clients; c != NULL; c = c->next )
  {
    if ( client == c ) break;
  }

  return c ? 1 : 0;
}


/**
 * <!-- npa_process_request -->
 */
static NPA_INLINE void npa_process_request( npa_client_handle client )
{
  npa_resource *resource;
  
  CORE_VERIFY_PTR( client );
  CORE_VERIFY_PTR( resource = client->resource );
  
  Core_MutexLock( resource->node_lock );

  /* Set current_client so it's available for use and debugging. */
  resource->current_client = client;

  /* Aggregate */
  npa_invoke_update_function( resource, client );

  /* Apply */
  npa_invoke_driver_function( resource, client );

  /* Increment sequence number */
  client->sequence = (resource->sequence += NPA_SEQUENCE_INCREMENT);
  
  /* Swap PENDING and ACTIVE work requests */
  client->index ^= 1;

  resource->current_client = NULL;

  /* Reset active attributes to the default on resource */
  resource->_internal->active_attr = resource->definition->attributes;

  /* If the client has the FIRE_AND_FORGET request attribute, set up a
     pass-through for the next sync request from this or another client */
  if ( _npa_request_has_attribute( client, NPA_REQUEST_FIRE_AND_FORGET ) )
  {
    npa_set_next_request_passthrough( client );
  }

  Core_MutexUnlock( resource->node_lock );
  
  _npa_request_serviced( client );
}


/**
 * <!-- npa_issue_sync_request -->
 */
void npa_issue_sync_request( npa_client_handle client, int new_request )
{ 
  if ( new_request )
  {
    npa_process_request( client );
  }
  else 
  {
    client->sequence |= NPA_REDUNDANT_REQUEST;
    _npa_request_serviced( client );
  }
}


/**
 * <!-- npa_issue_async_request -->
 *
 * @brief This function runs in the async client service workloop 
 */
DALResult npa_issue_async_request( DALSYSEventHandle event, void *arg )
{
  npa_client_handle client = (npa_client_handle)arg;

  npa_process_request( client );
  
  return DAL_SUCCESS;
}


/**
 * <!-- npa_enqueue_async_request -->
 */
void npa_enqueue_async_request( npa_client_handle client, int new_request )
{
  if ( new_request )
  {
    CORE_DAL_VERIFY( 
         DALSYS_EventCtrl( client->continuation->data.client.enqueue_event,
                           DALSYS_EVENT_CTRL_TRIGGER ) );
  }
  else
  {
    /* Complete synchronously */
    client->sequence |= NPA_REDUNDANT_REQUEST;
    _npa_request_serviced( client );
  }
}


/**
 * <!-- npa_terminate_request -->
 */
void npa_terminate_request( npa_client_handle client )
{
  npa_set_request_attribute( client, NPA_REQUEST_DROP_VOTE );

  /* TODO: May want to use a complete_request function pointer */
  if ( NPA_CLIENT_LIMIT_MAX == client->type ) 
  {
    npa_issue_limit_max_request( client, 0 );
  }
  else 
  {
    NPA_PENDING_REQUEST(client).state = 0;
    client->issue_request( client, NPA_ACTIVE_REQUEST(client).state != 0 );
  }
}

/**
 * <!-- npa_setup_dependency_request -->
 * 
 * @brief Perform setup operations for dependency requests
 *
 * Performs error checking on client pointers and determine 
 * the type of dependency request needed.  It will set unneeded
 * client handles to NULL
 *
 * @param current_client: Current client of the calling resource
 * @param required_client: Required client to the resource's dependency
 * @param suppressible_client: Suppressible client to the resource's dependency
 * @return Returns a non-null client handle
 */
static NPA_INLINE npa_client_handle
npa_setup_dependency_request( npa_client_handle  cur_client,
                              npa_client_handle *req_client,
                              npa_client_handle *sup_client )
{
  CORE_VERIFY( NULL != cur_client );

  /* If NPA_REQUEST_CHANGED_TYPE is set, we need both required 
     and suppressible clients */
  if ( cur_client->request_attr & NPA_REQUEST_CHANGED_TYPE ) 
  {
    CORE_VERIFY( *req_client && *sup_client );
    CORE_VERIFY( (*req_client)->resource == (*sup_client)->resource );
    return *req_client;
  }
  else if ( cur_client->type == NPA_CLIENT_VECTOR || 
      cur_client->type == NPA_CLIENT_REQUIRED )
  {
    CORE_VERIFY_PTR( *req_client && (*req_client)->resource );
    *sup_client = NULL;
    return *req_client;
  }
  else
  {
    CORE_VERIFY_PTR( *sup_client && (*sup_client)->resource );
    *req_client = NULL;
    return *sup_client;
  }
}

/**
 * <!-- npa_teardown_dependency_request -->
 * 
 * @brief Perform cleanup operations for dependency requests
 *
 * Swaps pending and active work requests for the clients and logs
 * completion
 *
 * @param req_dep_client: Required client to the dependency
 * @param sup_dep_client: Suppressible client to the dependency
 */
static NPA_INLINE void
npa_teardown_dependency_request( npa_client_handle req_dep_client,
                                 npa_client_handle sup_dep_client )
{
  /* Swap PENDING and ACTIVE work requests and log completion */
  if ( req_dep_client )
  {
    req_dep_client->index ^= 1;
    _npa_request_serviced( req_dep_client );
  }

  if ( sup_dep_client )
  {
    sup_dep_client->index ^= 1;
    _npa_request_serviced( sup_dep_client );
  }
}


/** 
 * <!-- npa_issue_dependency_request -->
 *
 * @brief Issue a request to a dependency 
 *
 * A resource may have either/both a required client or/and a suppressible
 * client to a dependency. This function may be used by the resource to issue
 * an appropriate request to a dependency, in response to a request to itself,
 * without needing to consider in its code which handle to use.
 *
 * This function takes the current client to the calling resource as argument
 * and depending on its type and request attributes, issues either a required
 * request, a suppressible request or both on the dependency client(s) of that
 * type.
 *
 * If requests are to be issued on both the required and suppressible
 * dependency handles, the routine ensures that the driver of the dependency
 * is only invoked once with the required client as argument. The update
 * function of the dependency is invoked twice.
 *
 * @param cur_client: Current client to the calling resource
 * @param dep_req_client: Required client handle to the resource's 
 * dependency. If there is no required dependency, this can be NULL.
 * @param dep_req_state: Request on the required dependency client
 * @param dep_sup_client: Suppressible client handle to the resource's 
 * dependency. If there is no suppressible dependency, this can be NULL
 * @param dep_sup_state: Request on the suppressible dependency client 
 */
void npa_issue_dependency_request( npa_client* cur_client,
                                   npa_client* req_dep_client,
                                   npa_resource_state req_dep_state,
                                   npa_client* sup_dep_client,
                                   npa_resource_state sup_dep_state )
{
  npa_resource *dep_resource;
  npa_client *dep_client;

  /* Determine which dependency handles we need to issue requests on.
   *
   * npa_setup_dependency_request will set one of either req_dep_client or
   * sup_dep_client to NULL, if NPA_REQUEST_CHANGED_TYPE is not set and (so)
   * we only need to issue a request on one of the 2 handles. In that case,
   * dep_client is set to the remaining non-NULL handle i.e. the one we will
   * issue a request on.
   *
   * If NPA_REQUEST_CHANGED_TYPE is set, dep_client is set to req_dep_client
   */
  dep_client = npa_setup_dependency_request( cur_client, 
                                             &req_dep_client,
                                             &sup_dep_client );

  dep_resource = dep_client->resource;

  if ( cur_client->request_attr & NPA_REQUEST_CHANGED_TYPE )
  {
    ULOG_RT_PRINTF_6( dep_client->log_handle,
                      "npa_issue_dependency_request (cur_client: 0x%08x) "
                      "(req_dep_client: 0x%08x) (req_dep_state: %u) "
                      "(sup_dep_client: 0x%08x) (sup_dep_state: %u) "
                      "(resource: \"%s\")",
                      cur_client,
                      req_dep_client, req_dep_state, 
                      sup_dep_client, sup_dep_state,
                      dep_client->resource_name );
  }
  else
  {
    ULOG_RT_PRINTF_4( dep_client->log_handle,
                      "npa_issue_dependency_request (cur_client: 0x%08x) "
                      "(dep_client: 0x%08x) (request: %u) (resource: \"%s\")",
                      cur_client, dep_client,
                      req_dep_client ? req_dep_state : sup_dep_state,
                      dep_client->resource_name );
  }

  /* Lock the dependency */
  Core_MutexLock( dep_resource->node_lock );

  /* Increment its sequence once */
  dep_resource->sequence += NPA_SEQUENCE_INCREMENT;

  /* If a required request needs to be issued to the dependency, set up
     the client's work request and call the dependency's update function */
  if ( req_dep_client )
  {
    NPA_PENDING_REQUEST(req_dep_client).state = req_dep_state;
    if ( NPA_ACTIVE_REQUEST(req_dep_client).state != req_dep_state )
    {
      dep_resource->current_client = req_dep_client;
      npa_invoke_update_function( dep_resource, req_dep_client );
      req_dep_client->sequence = dep_resource->sequence;
    }
    else
    {
      /* Mark request as redundant */
      req_dep_client->sequence |= NPA_REDUNDANT_REQUEST;
    }
  }

  /* If a suppressible request needs to be issued to the dependency, set up
     the client's work request and call the dependency's update function */
  if ( sup_dep_client )
  {
    NPA_PENDING_REQUEST(sup_dep_client).state = sup_dep_state;
    if ( NPA_ACTIVE_REQUEST(sup_dep_client).state != sup_dep_state )
    {
      dep_resource->current_client = sup_dep_client;
      npa_invoke_update_function( dep_resource, sup_dep_client );
      sup_dep_client->sequence = dep_resource->sequence;
    }
    else
    {
      /* Mark request as redundant */
      sup_dep_client->sequence |= NPA_REDUNDANT_REQUEST;
    }
  }

  /* Invoke the driver */
  npa_invoke_driver_function( dep_resource, dep_client );

  /* Reset current_client */
  dep_resource->current_client = NULL;

  /* Reset active attributes to the default on resource */
  dep_resource->_internal->active_attr = dep_resource->definition->attributes;

  /* Update the clients' ACTIVE request field and log completion */
  npa_teardown_dependency_request( req_dep_client, sup_dep_client );

  /* Unlock the dependency */
  Core_MutexUnlock( dep_resource->node_lock );
}
                                   

/** 
 * <!-- npa_issue_dependency_vector_request -->
 *
 * @brief Issue a vector request to a dependency. This is the vector
 * request equivalent to npa_issue_dependency_request
 *
 * A resource may have either/both a required client or/and a suppressible
 * client to a dependency. This function may be used by the resource to issue
 * an appropriate request to a dependency, in response to a request to itself,
 * without needing to consider in its code which handle to use.
 *
 * This function takes the current client to the calling resource as argument
 * and depending on its type and request attributes, issues either a required
 * request, a suppressible request or both on the dependency client(s) of that
 * type.
 *
 * If requests are to be issued on both the required and suppressible
 * dependency handles, the routine ensures that the driver of the dependency
 * is only invoked once with the required client as argument. The update
 * function of the dependency is invoked twice.
 *
 * @param cur_client: Current client to the calling resource
 * @param req_dep_client: Required client handle to the resource's 
 * dependency. If there is no required dependency, this can be NULL.
 * @param req_num_elems: Number of elements in vector request on 
 * the required dependency client
 * @param req_dep_vector: The vector request on the required
 * dependency client
 * @param sup_dep_client: Suppressible client handle to the resource's 
 * dependency. If there is no suppressible dependency, this can be NULL
 * @param sup_num_elems: Number of elements in vector request on 
 * the suppressible dependency client
 * @param sup_dep_vector: The vector request on the suppressible
 * dependency client
 */
void npa_issue_dependency_vector_request( npa_client *cur_client,
                                          npa_client *req_dep_client,
                                          unsigned int req_num_elems,
                                          npa_resource_state *req_dep_vector,
                                          npa_client_handle sup_dep_client,
                                          unsigned int sup_num_elems,
                                          npa_resource_state *sup_dep_vector )
{
  npa_resource *dep_resource;
  npa_client *dep_client;

  /* Determine which dependency handles we need to issue requests on.
   *
   * npa_setup_dependency_request will set one of either req_dep_client or
   * sup_dep_client to NULL, if NPA_REQUEST_CHANGED_TYPE is not set and (so)
   * we only need to issue a request on one of the 2 handles. In that case,
   * dep_client is set to the remaining non-NULL handle i.e. the one we will
   * issue a request on.
   *
   * If NPA_REQUEST_CHANGED_TYPE is set, dep_client is set to req_dep_client
   */
  dep_client = npa_setup_dependency_request( cur_client, 
                                             &req_dep_client,
                                             &sup_dep_client );

  dep_resource = dep_client->resource;

  if ( cur_client->request_attr & NPA_REQUEST_CHANGED_TYPE )
  {
    ULOG_RT_PRINTF_8( dep_client->log_handle,
                      "npa_issue_dependency_vector_request "
                      "(cur_client: 0x%08x) "
                      "(req_dep_client: 0x%08x) (req_dep_vector: 0x%08x, %u) "
                      "(sup_dep_client: 0x%08x) (sup_dep_vector: 0x%08x, %u) "
                      "(resource: \"%s\")",
                      cur_client,
                      req_dep_client, req_dep_vector, req_num_elems,
                      sup_dep_client, sup_dep_vector, sup_num_elems,
                      dep_client->resource_name );
  }
  else
  {
    ULOG_RT_PRINTF_5( dep_client->log_handle,
                      "npa_issue_dependency_vector_request "
                      "(cur_client: 0x%08x) (dep_client: 0x%08x) "
                      "(vector: 0x%08x, %u)"
                      "(resource: \"%s\")",
                      cur_client, dep_client,
                      req_dep_client? req_dep_vector : sup_dep_vector,
                      req_dep_client? req_num_elems : sup_num_elems, 
                      dep_client->resource_name );
  }

  /* Lock the dependency */
  Core_MutexLock( dep_resource->node_lock );

  /* Increment its sequence once */
  dep_resource->sequence += NPA_SEQUENCE_INCREMENT;
  
  /* If a required request needs to be issued to the dependency, set up
     the client's work request and call the dependency's update function */
  if ( req_dep_client )
  {
    NPA_PENDING_REQUEST(req_dep_client).state = req_num_elems;
    NPA_PENDING_REQUEST(req_dep_client).pointer.vector = req_dep_vector;
    dep_resource->current_client = req_dep_client;
    npa_invoke_update_function( dep_resource, req_dep_client );
    req_dep_client->sequence =  dep_resource->sequence;
  }

  /* If a suppressible request needs to be issued to the dependency, set up
     the client's work request and call the dependency's update function */
  if ( sup_dep_client )
  {
    NPA_PENDING_REQUEST(sup_dep_client).state = sup_num_elems;
    NPA_PENDING_REQUEST(sup_dep_client).pointer.vector = sup_dep_vector;
    dep_resource->current_client = sup_dep_client;
    npa_invoke_update_function( dep_resource, sup_dep_client );
    sup_dep_client->sequence = dep_resource->sequence;
  }

  /* Invoke the driver */
  npa_invoke_driver_function( dep_resource, dep_client );

  /* Reset current_client */
  dep_resource->current_client = NULL;

  /* Reset active attributes to the default on resource */
  dep_resource->_internal->active_attr = dep_resource->definition->attributes;

  /* Update the clients' ACTIVE request field and log completion */
  npa_teardown_dependency_request( req_dep_client, sup_dep_client );

  /* Unlock the dependency */
  Core_MutexUnlock( dep_resource->node_lock );
}
                                   

/**
 * <!-- npa_assign_resource_state -->
 *
 * @brief Assign the resource state directly, bypassing the update and
 * driver functions.  This will trigger events as necessary.
 *
 * This function is intended for use in a compound node when one
 * resource's state change can cause another coupled resource's state
 * to change. This function must be called from within the node's
 * atomic section - which means it can be invoked from within the
 * update or driver function.  It require the npa_resource *, which
 * can be retrieved for coupled resources from the current resource
 * by the NPA_RESOURCE macro.
 *
 * @param resource : Resource whose state is changing
 * @param state : New state of the resource
 */
void npa_assign_resource_state( npa_resource       *resource,
                                npa_resource_state  new_state )
{
  CORE_VERIFY_PTR( resource );
  CORE_VERIFY( npa_resource_has_attribute( resource, NPA_RESOURCE_VECTOR_STATE ) ?
               1 : ( new_state <= resource->active_max ) );

  ULOG_RT_PRINTF_3( resource->log_handle, 
                    "npa_assign_resource_state "
                    "(handle: 0x%08x) "
                    "(resource: \"%s\") "
                    "(active state: %d)", 
                    resource,
                    resource->definition->name,
                    new_state );

  Core_MutexLock( resource->node_lock );
  npa_update_resource_state( resource, new_state );
  Core_MutexUnlock( resource->node_lock );
}


/**
 * <!-- npa_request_has_attribute -->
 *
 * @brief Returns true if the given attribute is set on the client handle.
 * 
 * Request attributes are set on client handles and are valid for the duration
 * of the current request.
 *
 * @param client : The client handle
 * @param attr : The attribute to test for
 *
 * @return TRUE if the attribute is set on the client handle
 */
unsigned int npa_request_has_attribute( npa_client_handle     client,
                                        npa_request_attribute attr )
{
  CORE_VERIFY_PTR( client );
  return _npa_request_has_attribute( client, attr );
}


/**
 * <!-- npa_get_request_attributes -->
 *
 * @brief Returns a bitset of all request attributes set on the given client.
 *
 * @param client : The client handle
 */
unsigned int npa_get_request_attributes( npa_client_handle client )
{
  CORE_VERIFY_PTR( client );
  return client->request_attr;
}


/**
 * <!-- npa_pass_request_attributes -->
 *
 * @brief Add request attributes of the 'current' client to the 'dependency' client.
 *
 * Does not unset any attributes set previously on the 'dependency' client.
 *
 * @param current : Handle of a npa_client whose attributes will be applied
 *                  to the other.
 * @param dependency : Handle of a npa_client whose attributes will be updated. 
 *
 * @return The dependency client handle passed in
 */
npa_client_handle npa_pass_request_attributes( npa_client_handle current,
                                               npa_client_handle dependency )
{
  CORE_VERIFY_PTR( current ); CORE_VERIFY_PTR( dependency );
  dependency->request_attr |= current->request_attr;
  return dependency;
}


/**
 * <!-- npa_resource_lock -->
 *
 * @brief Lock the resource.
 *
 * If the resource is forked, it will be joined before this function returns.
 * Note that the resource shares its lock with other resources in the node.
 * So this will, in effect, lock the node.
 *
 * @param resource : Handle to the resource
 */
void npa_resource_lock( npa_resource *resource )
{
  CORE_VERIFY_PTR( resource );

  Core_MutexLock( resource->node_lock );
  ULOG_RT_PRINTF_2( npa.log, "npa_resource_lock "
                    "(resource: \"%s\") (sequence: 0x%08x)",
                    resource->definition->name, resource->sequence );
}

/**
 * <!-- npa_resource_trylock -->
 *
 * @brief Try to lock the resource. If another task has acquired the lock,
 * the routine returns immediately without waiting.
 *
 * If the lock was acquired, the routine returns 0. Else, -1.
 *
 * @param resource : Handle to the resource
 *
 * @return 0 if a lock was acquired, -1 otherwise.
 */
int npa_resource_trylock( npa_resource *resource )
{
  int ret;
  CORE_VERIFY_PTR( resource );

  ret = Core_MutexTryLock( resource->node_lock );
  
  ULOG_RT_PRINTF_2( npa.log, "npa_resource_trylock "
                    "(resource: \"%s\") (result: %d)",
                    resource->definition->name, ret );
  return ret;
}
/**
 * <!-- npa_resource_unlock -->
 *
 * @brief  Unlock the resource that was previously locked by
 * npa_resource_lock.
 *   
 * @param resource : Handle to the resource
 */
void npa_resource_unlock( npa_resource *resource )
{
  CORE_VERIFY_PTR( resource );
  Core_MutexUnlock( resource->node_lock );

  ULOG_RT_PRINTF_1( npa.log, "npa_resource_unlock "
                    "(resource: \"%s\")",
                    resource->definition->name );
}

#ifdef __cplusplus
}
#endif
