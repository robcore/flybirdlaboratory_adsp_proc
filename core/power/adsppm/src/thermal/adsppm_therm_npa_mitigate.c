   /*============================================================================
  @file therm_npa_mitigate.c

  Define NPA nodes representing mitigation states.
  
 
* Copyright (c) 2014 Qualcomm Technologies, Inc.
* All Rights Reserved.
* Qualcomm Technologies, Inc. Confidential and Proprietary.

============================================================================*/
/*=======================================================================
$Header: //components/rel/core.adsp/2.6.1/power/adsppm/src/thermal/adsppm_therm_npa_mitigate.c#1 $
$DateTime: 2014/10/16 12:45:40 $
$Author: pwbldsvc $
========================================================================*/
/*===========================================================================

                     INCLUDE FILES FOR MODULE

===========================================================================*/

#include "npa_resource.h"
#include "CoreVerify.h"
#include "ULog.h"
#include "ULogFront.h"
#include "adsppm_utils.h"
#include "adsppm_therm_npa_mitigate.h"

/*=======================================================================

                  STATIC MEMBER / FUNCTION DECLARATIONS / DEFINITIONS

========================================================================*/


static npa_client_handle eLDOHandle = NULL;

static npa_resource_state adsppm_therm_node_mitigate_driver_fcn(npa_resource *resource,
                                                         npa_client   *client,
                                                         npa_resource_state state);

														 
static void thermalHandleInitCb ( void  *context,
      unsigned int  event_type,
      void         *data,
      unsigned int  data_size );
														 
/*=======================================================================

                  GLOBAL DEFINITIONS

========================================================================*/
/* Supplies device list for QMI request for mitigation device list.
   Must edit if additional mitigation devices are added. */
const char *adsppm_therm_mitigation_devices[] = 
{
  "cpuv_restriction_cold"
};


const unsigned int adsppm_therm_mitigation_devices_count =
 ARR_SIZE(adsppm_therm_mitigation_devices);

/* "/therm/mitigate" node and resource
   Must edit if additional mitigation devices are added. */

static npa_resource_plugin adsppm_therm_mitigate_plugin;

static npa_resource_definition adsppm_therm_mitigate_resource[] =
{
  {
    "/therm/mitigate/cpuv_restriction_cold",               /* name of resource */
    "State Level",                      /* Units of the resource */
    0x1,                                /* Maximum value of resource */
    &adsppm_therm_mitigate_plugin,
    NPA_RESOURCE_DRIVER_UNCONDITIONAL,
    NULL,
    NULL
  }
};

static npa_resource_state adsppm_initial_mitigate_state[] = {1};

npa_node_definition adsppm_therm_mitigate_node = 
{
  "/node/therm/mitigate",            /* Node name - info only */
  adsppm_therm_node_mitigate_driver_fcn,    /* Driver function for temperature */
  NPA_NODE_DEFAULT,                  /* No attributes */
  NULL,                              /* No User Data */
  NPA_EMPTY_ARRAY,                   /* No Dependencies */
  NPA_ARRAY(adsppm_therm_mitigate_resource) /* Resources */
};

/* Used to limit max mitigation to zero for special test cases */
//static boolean limit_max_zero = FALSE;

/*=======================================================================

                  LOCAL FUNCTION DEFINITIONS

========================================================================*/

/**
  @brief adsppm_therm_node_mitigate_driver_fcn

  Mitigate node driver function.  Nothing to update.

  @param  : resource: A dynamic system element that work requests can be made against.
            client: The handle to the clients registered to the
            resource.
            state: Update function state.

  @return : Resource state.
*/
static npa_resource_state adsppm_therm_node_mitigate_driver_fcn(npa_resource *resource,
                                                         npa_client   *client,
                                                         npa_resource_state state)
{
  ADSPPM_LOG_FUNC_ENTER;
  if(client->type == NPA_CLIENT_INITIALIZE)
  {
    // The driver function will be called with this client *before* it is 
    // made publicly available, so you can place any initialization you 
    // need here.

    // The value of state passed here is provided by the 
    // npa_define_node function.
  }
  if(NULL != eLDOHandle)
	{	
		/* issue npa request to clkreigm eldo*/
		npa_issue_required_request(eLDOHandle, state);
  
		ADSPPM_LOG_PRINTF_2(ADSPPM_LOG_LEVEL_INFO, 
                   "Mitigation ( %s:%d )",
                   adsppm_therm_mitigation_devices[resource->index],
                   state);
	}
	else
	{
		 ADSPPM_LOG_PRINTF_0(ADSPPM_LOG_LEVEL_ERROR, "no state request, Failed to create client for eLDO");
	}
  ADSPPM_LOG_FUNC_EXIT(state);  
  return state;
}

/*=======================================================================

                 PUBLIC FUNCTION DEFINITIONS

========================================================================*/

/**
  @brief adsppm_therm_npa_mitigate_init

  Thermal mitigate init function.

  @param  : None

  @return : None.
*/
void adsppm_therm_npa_mitigate_init( void )
{ 
  ADSPPM_LOG_FUNC_ENTER;
  /* Copy all attributes of standard NPA max pluggin */
  memscpy(&adsppm_therm_mitigate_plugin, sizeof(npa_resource_plugin), &npa_max_plugin, sizeof(npa_resource_plugin));
  adsppm_therm_mitigate_plugin.supported_clients |= NPA_CLIENT_CUSTOM1;

  /* check clkregiem eldo resource is available*/
  npa_resource_available_cb(ELDO_NODE_NAME, thermalHandleInitCb, NULL);
   /* Define SW mitigate nodes */ 
  npa_define_node( &adsppm_therm_mitigate_node, adsppm_initial_mitigate_state, NULL );
 
  ADSPPM_LOG_FUNC_EXIT(0);  
}

static void thermalHandleInitCb ( void         *context,
      unsigned int  event_type,
      void         *data,
      unsigned int  data_size )
{
	ADSPPM_LOG_FUNC_ENTER;
    ADSPPM_LOG_FUNC_PROFILESTART;

	ADSPPM_LOG_PRINTF_0(ADSPPM_LOG_LEVEL_INFO, "thermalhandleinitcb");
	
    eLDOHandle = npa_create_sync_client( ELDO_NODE_NAME,
           ELDO_ADSPPM_CLIENT_NAME,
            NPA_CLIENT_REQUIRED);
    if (NULL == eLDOHandle)
    {
        ADSPPM_LOG_PRINTF_0(ADSPPM_LOG_LEVEL_ERROR, "Failed to create NPAclient for eLDO,no thermal mitigate node created!");
    }
	else
	{
		/* issue init npa request to clkreigm eldo*/
		npa_issue_required_request(eLDOHandle, adsppm_initial_mitigate_state[0]);
	}
    ADSPPM_LOG_FUNC_PROFILEEND;
    ADSPPM_LOG_FUNC_EXIT(0);
}
