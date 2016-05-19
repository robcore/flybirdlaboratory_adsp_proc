/*============================================================================
  @file therm_mitigation_device_service.c

  Thermal mitigation device QMI service implementation
  
 
* Copyright (c) 2013 Qualcomm Technologies, Inc.
* All Rights Reserved.
* Qualcomm Technologies, Inc. Confidential and Proprietary.

============================================================================*/
/*=======================================================================
$Header: //components/rel/core.adsp/2.6.1/power/adsppm/src/thermal/adsppm_therm_mitigation_device_service.c#1 $
$DateTime: 2014/10/16 12:45:40 $
$Author: pwbldsvc $
========================================================================*/
/*===========================================================================

                     INCLUDE FILES FOR MODULE

===========================================================================*/

#include "comdef.h"
#include "qmi_csi.h"
#include "qmi_sap.h"
#include "thermal_mitigation_device_service_v01.h"
#include "adsppm_therm_target.h"
#include "npa.h"
#include "npa_resource.h"
#include "ULog.h"
#include "ULogFront.h"
#include "adsppm_utils.h"
#include "rcinit.h"


/*===========================================================================

            LOCAL DEFINITIONS AND DECLARATIONS FOR MODULE

This section contains local definitions for constants, macros, types,
variables and other items needed by this module.

=============================================================================*/

#define ADSPPM_THERM_QMI_MITIGATION_MAX_CLIENT_NUM 8
#define ADSPPM_THERM_QMI_SERVICE_STACK_SIZE  (4096)
#define ADSPPM_THERM_QMI_MITIGATION_DEV_SIG  0x00000004

typedef struct 
{
  unsigned int  device_index;
  void         *client;
} adsppm_therm_qmi_mitigation_dev_cb_type;

extern const unsigned int adsppm_therm_mitigation_devices_count;

/* Structure to hold service context */
typedef struct
{
  /** QMI service handle */
  qmi_csi_service_handle service_handle;
  /** Number of requests that the service has handled */
  uint32 num_requests;
} adsppm_therm_service_context_type;


typedef struct 
{
  qmi_client_handle  qmi_client_handle;
  npa_event_handle   event_handle[QMI_TMD_MITIGATION_DEV_LIST_MAX_V01];
  npa_client_handle  client_handle[QMI_TMD_MITIGATION_DEV_LIST_MAX_V01];
  npa_query_handle   query_handle[QMI_TMD_MITIGATION_DEV_LIST_MAX_V01];
  unsigned int       requested_level[QMI_TMD_MITIGATION_DEV_LIST_MAX_V01];
  boolean            connected;
  adsppm_therm_qmi_mitigation_dev_cb_type  cb_context[QMI_TMD_MITIGATION_DEV_LIST_MAX_V01];
} adsppm_therm_qmi_mitigation_dev_client_type;

static adsppm_therm_qmi_mitigation_dev_client_type therm_qmi_mitigation_dev_client[ADSPPM_THERM_QMI_MITIGATION_MAX_CLIENT_NUM];


typedef union {
  qmi_response_type_v01                                     resp;
  tmd_get_mitigation_device_list_resp_msg_v01               dev_list;
  tmd_set_mitigation_level_resp_msg_v01                     set_level;
  tmd_get_mitigation_level_resp_msg_v01                     get_level;
  tmd_register_notification_mitigation_level_resp_msg_v01   reg_notify;
  tmd_deregister_notification_mitigation_level_resp_msg_v01 dereg_notify;
} adsppm_therm_qmi_general_resp_v01_type;


/* service thread structures */
static qurt_anysignal_t     adsppm_therm_qmi_service_sig;
static qurt_thread_t        adsppm_therm_qmi_service_tcb;
static qurt_thread_attr_t   adsppm_therm_qmi_service_attr;


/* Allocate response an indication message bodies outside of stack space */
static adsppm_therm_qmi_general_resp_v01_type therm_qmi_resp;

static tmd_mitigation_level_report_ind_msg_v01 therm_qmi_ind_msg;

extern const char *adsppm_therm_mitigation_devices[];

extern npa_node_definition adsppm_therm_mitigate_node;

static boolean adsppm_therm_qmi_validate_connection_handle(void *connection_handle);

/*===========================================================================

                     INTERNAL FUNCTION DECLARATIONS
                     
===========================================================================*/
/**
  @brief adsppm_therm_qmi_dev_send_indication_cb

  This function handles NPA event changes for mitigation resources.  Sends
  indications to registered connections.  Sanitizing function.

  @param  : context: User callback data provided to notify the correct qmi
                     connection
            event_type: Ignored
            data: New mitigation state information.
            data_size: Ignored

  @return : None.
*/
static void adsppm_therm_qmi_dev_send_indication_cb( void         *context,
                                              unsigned int  event_type, 
                                              void         *data,
                                              unsigned int  data_size )
{
  adsppm_therm_qmi_mitigation_dev_cb_type     *cb_data = NULL;
  adsppm_therm_qmi_mitigation_dev_client_type *client  = NULL;
  npa_event_data *event_data_ptr                = NULL;
  qmi_csi_error qmi_error;
  ADSPPM_LOG_FUNC_ENTER;  

  if ((context == NULL) || (data == NULL))
  {
    ADSPPM_LOG_PRINTF_0(ADSPPM_LOG_LEVEL_ERROR,
                     "indication_cb: NULL context param or NULL data");
  }
  else
  {
	  cb_data = (adsppm_therm_qmi_mitigation_dev_cb_type *)context;
	  client = (adsppm_therm_qmi_mitigation_dev_client_type *)cb_data->client;
	  if (FALSE == adsppm_therm_qmi_validate_connection_handle(cb_data->client))
	  {
		ADSPPM_LOG_PRINTF_0(ADSPPM_LOG_LEVEL_ERROR,
						 "indication_cb: Invalid client handle.");
	  }
	  else
	  {

		event_data_ptr = (npa_event_data*)data;

		if (cb_data->device_index >= adsppm_therm_mitigation_devices_count)
		{
			ADSPPM_LOG_PRINTF_1(ADSPPM_LOG_LEVEL_ERROR,
							 "indication_cb: Invalid index %d",
							 cb_data->device_index);
		}
		else
		{

		  therm_qmi_ind_msg.current_mitigation_level = event_data_ptr->state;
		  strlcpy(therm_qmi_ind_msg.mitigation_device.mitigation_dev_id,
				  adsppm_therm_mitigation_devices[cb_data->device_index],
				  sizeof(therm_qmi_ind_msg.mitigation_device.mitigation_dev_id));

		  qmi_error = qmi_csi_send_ind(client->qmi_client_handle, 
									   QMI_TMD_MITIGATION_LEVEL_REPORT_IND_V01,
									   &therm_qmi_ind_msg, 
									   sizeof(tmd_mitigation_level_report_ind_msg_v01)); 
		  if (qmi_error != QMI_CSI_NO_ERR)
		  {
			ADSPPM_LOG_PRINTF_1(ADSPPM_LOG_LEVEL_ERROR, 
							 "Failure to send indication, Err: %d",
							 qmi_error);
		  }
		  else
		  {
			ADSPPM_LOG_PRINTF_2(ADSPPM_LOG_LEVEL_INFO, 
							 "Indication sent %s change to %d",
							 adsppm_therm_mitigation_devices[cb_data->device_index], 
							 event_data_ptr->state);
		  }
		} //device index too big
	  }//invalid clent handle
	}// NULL pointer
	ADSPPM_LOG_FUNC_EXIT(0);
}

/**
  @brief adsppm_therm_qmi_validate_request

  This function validates a request size and the device id.

  @param  : response: qmi_response_type_v01 
            idx: message index
            req_c_struct_len: request struct
                                       length
            expected_req_c_struct_len: expected request struct
            length dev_id: Device ID log_str: Unique log string

  @return : TRUE if valid, FALSE otherwise
*/
static boolean adsppm_therm_qmi_validate_request( qmi_response_type_v01  *response,
                                           unsigned int           *idx,
                                           unsigned int            req_c_struct_len,
                                           unsigned int            expected_req_c_struct_len,
                                           const char             *dev_id,
                                           const char             *log_str)
{
  unsigned int i;
  boolean retval = TRUE;
  ADSPPM_LOG_FUNC_ENTER;

  do
  {
    /* Validate request. */
    if (req_c_struct_len != expected_req_c_struct_len)
    {
       ADSPPM_LOG_PRINTF_2(ADSPPM_LOG_LEVEL_ERROR,"%s request wrong size: %d",
                       log_str, req_c_struct_len);
      response->result = QMI_RESULT_FAILURE_V01;
      response->error = QMI_ERR_MALFORMED_MSG_V01;
      retval = FALSE;
      break;
    }
  
    /* Does cooling device exist. */
    for (i = 0; i < adsppm_therm_mitigation_devices_count; i++ )
    {
      if (strcasecmp(adsppm_therm_mitigation_devices[i], dev_id) == 0)
      {
        /* Found a match */
        *idx = i;
        break;
      }
    }
  
    if (i >= adsppm_therm_mitigation_devices_count)
    {
      ADSPPM_LOG_PRINTF_1(ADSPPM_LOG_LEVEL_ERROR,
                       "%s request on non-existent thermal device",
                       log_str);
      response->result = QMI_RESULT_FAILURE_V01;
      response->error = QMI_ERR_INVALID_ID_V01;
      retval = FALSE;
      break;
    }
  } while (0);
  ADSPPM_LOG_FUNC_EXIT(retval);
  return retval;
}

/**
  @brief adsppm_therm_qmi_validate_connection_handle.

  This function validates a connection handle.

  @param  : connection_handle: Handle to validate.
   
  @return : TRUE if valid, FALSE otherwise
*/
static boolean adsppm_therm_qmi_validate_connection_handle(void *connection_handle)
{
  unsigned int i;
  boolean retval = TRUE;
  ADSPPM_LOG_FUNC_ENTER;
  do
  {
    /* Validate handle. */
    if (connection_handle == NULL)
    {
      ADSPPM_LOG_PRINTF_0(ADSPPM_LOG_LEVEL_ERROR, "Connection handle NULL");
      retval = FALSE;
      break;
    }

    /* Find empty client slot */
    for (i = 0; i < ADSPPM_THERM_QMI_MITIGATION_MAX_CLIENT_NUM; i++)
    {
      if (&therm_qmi_mitigation_dev_client[i] == 
          (adsppm_therm_qmi_mitigation_dev_client_type *)connection_handle)
      {
        /* Found client */
        break;
      }
    }

    if (i >= ADSPPM_THERM_QMI_MITIGATION_MAX_CLIENT_NUM)
    {
      ADSPPM_LOG_PRINTF_0(ADSPPM_LOG_LEVEL_ERROR, "Invalid connection handle");
      retval = FALSE;
      break;
    }

  } while (0);
  ADSPPM_LOG_FUNC_EXIT(retval);
  return retval;
}


/**
  @brief adsppm_therm_qmi_dev_connect

  This function processes incoming requests for the QMI thermal
  mitigation device services to connect a client.

  @param  : client_handle: Handle used by the infrastructure 
                           to identify different services.
            service_cookie: Ignored
            connection_handle: Client connection to created
                               internally.

  @return : None.
*/
static qmi_csi_cb_error adsppm_therm_qmi_dev_connect(qmi_client_handle  client_handle,
                                              void              *service_cookie,
                                              void             **connection_handle)
{
  unsigned int i;
  qmi_csi_cb_error retval = QMI_CSI_CB_NO_ERR;
  adsppm_therm_qmi_mitigation_dev_client_type *client = NULL;
   
   ADSPPM_LOG_FUNC_ENTER;
  do
  {
    /* Find empty client slot */
    for (i = 0; i < ADSPPM_THERM_QMI_MITIGATION_MAX_CLIENT_NUM; i++)
    {
      if (therm_qmi_mitigation_dev_client[i].connected == FALSE)
      {
        /* Found empty slot */
        ADSPPM_LOG_PRINTF_1(ADSPPM_LOG_LEVEL_ERROR, "Fould empty client slot: %d", i);
        break;
      }
    }

    if (i >= ADSPPM_THERM_QMI_MITIGATION_MAX_CLIENT_NUM)
    {
      ADSPPM_LOG_PRINTF_0(ADSPPM_LOG_LEVEL_ERROR, "No client connections available");
      retval = QMI_CSI_CB_NO_MEM;
      break;
    }
  
    /* Fill out slot data */
    memset(&therm_qmi_mitigation_dev_client[i], 0, sizeof(therm_qmi_mitigation_dev_client[0]));
    client = &therm_qmi_mitigation_dev_client[i];

    for (i = 0; i < adsppm_therm_mitigate_node.resource_count; i++)
    {
      client->client_handle[i] = npa_create_sync_client(adsppm_therm_mitigate_node.resources[i].name,
                                                       "QMI MITIGATION DEV",
                                                       NPA_CLIENT_REQUIRED);
      client->query_handle[i] = npa_create_query_handle(adsppm_therm_mitigate_node.resources[i].name);
    }

    client->qmi_client_handle = client_handle;
    client->connected = TRUE;
    *connection_handle = client;
    ADSPPM_LOG_PRINTF_0(ADSPPM_LOG_LEVEL_INFO, "Connect client");
  } while (0);
  ADSPPM_LOG_FUNC_EXIT(retval);
  return retval;
}

/**
  @brief adsppm_therm_qmi_dev_disconnect

  This function processes incoming requests for the QMI thermal
  mitigation device services to disconnect a client. Sanitizing 
  function. 

  @param  : connection_handle: Client connection to 
                               disconnect.
            service_cookie: Ignored

  @return : None.
*/
static void adsppm_therm_qmi_dev_disconnect(void  *connection_handle,
                                     void  *service_cookie)
{
  unsigned int i;
  adsppm_therm_qmi_mitigation_dev_client_type *client = connection_handle;
  
  ADSPPM_LOG_FUNC_ENTER;
  if (adsppm_therm_qmi_validate_connection_handle(client) == FALSE)
  {
    ADSPPM_LOG_PRINTF_0(ADSPPM_LOG_LEVEL_ERROR, 
                     "Disconnect invalid client");
  }
  else
  {
	  /* Destroy NPA handles */
	  for (i = 0; i < adsppm_therm_mitigate_node.resource_count; i++)
	  {
		if (client->event_handle[i] != NULL)
		{
		  npa_destroy_event_handle(client->event_handle[i]);
		  client->event_handle[i] = NULL;
		}

		if (client->client_handle[i] != NULL)
		{
		  npa_destroy_client(client->client_handle[i]);
		  client->client_handle[i] = NULL;
		}

		if (client->query_handle[i])
		{
		  npa_destroy_query_handle(client->query_handle[i]);
		  client->query_handle[i] = NULL;
		}
	  }

	  /* Free client slot from being connected */
	  client->connected = FALSE;
  }
  ADSPPM_LOG_FUNC_EXIT(0);

}

/**
  @brief adsppm_therm_handle_dev_list_req

  This function processes incoming requests for the QMI thermal
  mitigation device services with msg_id 
  QMI_TMD_GET_MITIGATION_DEVICE_LIST_REQ_V01. 

  @param  : connection_handle: Client connection making request. 
            req_handle: QMI request handle
            msg_id: QMI msg request ID
            req_c_struct: QMI request structure
            req_c_struct_len: QMI request structure length
            service_cookie: Ignored

  @return : qmi_csi_cb_error.
*/
static qmi_csi_cb_error adsppm_therm_handle_dev_list_req(void           *connection_handle,
                                                  qmi_req_handle  req_handle,
                                                  unsigned int    msg_id,
                                                  void           *req_c_struct,
                                                  unsigned int    req_c_struct_len,
                                                  void           *service_cookie)
{
  tmd_get_mitigation_device_list_resp_msg_v01 *response = 
    (tmd_get_mitigation_device_list_resp_msg_v01 *)&therm_qmi_resp;
  unsigned int i;
     ADSPPM_LOG_FUNC_ENTER;
  /* Init response data */
  memset( response, 0, 
          sizeof(tmd_get_mitigation_device_list_resp_msg_v01));

  do
  {
    response->mitigation_device_list_valid = 1;
    response->mitigation_device_list_len = adsppm_therm_mitigation_devices_count;
    
     ADSPPM_LOG_PRINTF_0(ADSPPM_LOG_LEVEL_INFO, 
                     "Get device list request");

    /* Copy cooling device info over to response. */
    for (i = 0; i < adsppm_therm_mitigation_devices_count; i++ )
    {
      ADSPPM_LOG_PRINTF_2(ADSPPM_LOG_LEVEL_INFO, 
                     "Device %d %s", i, adsppm_therm_mitigation_devices[i]);
      strlcpy(response->mitigation_device_list[i].mitigation_dev_id.mitigation_dev_id,
              adsppm_therm_mitigation_devices[i],
              sizeof(response->mitigation_device_list[0].mitigation_dev_id));
      response->mitigation_device_list[i].max_mitigation_level = adsppm_therm_mitigate_node.resources[i].max;
    }

    response->resp.result = QMI_RESULT_SUCCESS_V01;
    response->resp.error  = QMI_ERR_NONE_V01;
  } while (0);
  
  qmi_csi_send_resp(req_handle, msg_id, response, 
                    sizeof(tmd_get_mitigation_device_list_resp_msg_v01));
  ADSPPM_LOG_FUNC_EXIT(QMI_CSI_CB_NO_ERR);
  return QMI_CSI_CB_NO_ERR;
}

/**
  @brief adsppm_therm_handle_dev_get_level_req

  This function processes incoming requests for the QMI thermal
  mitigation device services with msg_id 
  QMI_TMD_GET_MITIGATION_LEVEL_REQ_V01. 

  @param  : connection_handle: Client connection making request. 
            req_handle: QMI request handle
            msg_id: QMI msg request ID
            req_c_struct: QMI request structure
            req_c_struct_len: QMI request structure length
            service_cookie: Ignored

  @return : qmi_csi_cb_error.
*/
static qmi_csi_cb_error adsppm_therm_handle_dev_get_level_req(void           *connection_handle,
                                                       qmi_req_handle  req_handle,
                                                       unsigned int    msg_id,
                                                       void           *req_c_struct,
                                                       unsigned int    req_c_struct_len,
                                                       void           *service_cookie)
{
  tmd_get_mitigation_level_req_msg_v01  *request = 
    (tmd_get_mitigation_level_req_msg_v01 *)req_c_struct;
  tmd_get_mitigation_level_resp_msg_v01 *response = 
    (tmd_get_mitigation_level_resp_msg_v01 *)&therm_qmi_resp;
  adsppm_therm_qmi_mitigation_dev_client_type *client = connection_handle;
  npa_query_type query_result;

  unsigned int i;
  
  ADSPPM_LOG_FUNC_ENTER;

  /* Init response data */
  memset( response, 0, sizeof(tmd_get_mitigation_level_resp_msg_v01) );

  do
  {
    /* Validate request. */
    if (adsppm_therm_qmi_validate_request(&(response->resp), &i, req_c_struct_len, 
                                   sizeof(tmd_get_mitigation_level_req_msg_v01),
                                   request->mitigation_device.mitigation_dev_id,
                                   "Get level") == FALSE)
    {
      break;
    }
    
    if (npa_query(client->query_handle[i], NPA_QUERY_CURRENT_STATE, 
                  &query_result) == NPA_QUERY_SUCCESS)
    {
      response->current_mitigation_level_valid = 1;
      response->current_mitigation_level = (uint8_t)query_result.data.state;
    }
    response->requested_mitigation_level_valid = 1;
    response->requested_mitigation_level = (uint8_t)client->requested_level[i];

    ADSPPM_LOG_PRINTF_3(ADSPPM_LOG_LEVEL_INFO, 
                     "Get level request on %s, current level %d, requested level %d",
                     adsppm_therm_mitigate_node.resources[i].name,
                     query_result.data.state,
                     client->requested_level[i]);

    response->resp.result = QMI_RESULT_SUCCESS_V01;
    response->resp.error  = QMI_ERR_NONE_V01;    
  } while (0);
  
  qmi_csi_send_resp(req_handle, msg_id, response, 
                    sizeof(tmd_get_mitigation_level_resp_msg_v01));
					
  ADSPPM_LOG_FUNC_EXIT(QMI_CSI_CB_NO_ERR); 
  return QMI_CSI_CB_NO_ERR;
}

/**
  @brief adsppm_therm_handle_dev_set_level_req

  This function processes incoming requests for the QMI thermal
  mitigation device services with msg_id 
  QMI_TMD_SET_MITIGATION_LEVEL_REQ_V01. 

  @param  : connection_handle: Client connection making request. 
            req_handle: QMI request handle
            msg_id: QMI msg request ID
            req_c_struct: QMI request structure
            req_c_struct_len: QMI request structure length
            service_cookie: Ignored

  @return : qmi_csi_cb_error.
*/
static qmi_csi_cb_error adsppm_therm_handle_dev_set_level_req(void           *connection_handle,
                                                       qmi_req_handle  req_handle,
                                                       unsigned int    msg_id,
                                                       void           *req_c_struct,
                                                       unsigned int    req_c_struct_len,
                                                       void           *service_cookie)
{
  tmd_set_mitigation_level_req_msg_v01  *request = 
    (tmd_set_mitigation_level_req_msg_v01 *)req_c_struct;
  tmd_set_mitigation_level_resp_msg_v01 *response = 
    (tmd_set_mitigation_level_resp_msg_v01 *)&therm_qmi_resp;
  adsppm_therm_qmi_mitigation_dev_client_type *client = connection_handle;

  unsigned int i;
  ADSPPM_LOG_FUNC_ENTER;

  /* Init response data */
  memset( response, 0, sizeof(tmd_set_mitigation_level_resp_msg_v01) );

  do
  {
    /* Validate request. */
    if (adsppm_therm_qmi_validate_request(&(response->resp), &i, req_c_struct_len, 
                                   sizeof(tmd_set_mitigation_level_req_msg_v01),
                                   request->mitigation_dev_id.mitigation_dev_id,
                                   "Set level") == FALSE)
    {
      break;
    }
 
    client->requested_level[i] = request->mitigation_level;
    npa_issue_required_request(client->client_handle[i],
                               client->requested_level[i]);

    ADSPPM_LOG_PRINTF_2(ADSPPM_LOG_LEVEL_INFO, 
                     "Set level request on %s of %d",
                     adsppm_therm_mitigate_node.resources[i].name,
                     client->requested_level[i]);

    response->resp.result = QMI_RESULT_SUCCESS_V01;
    response->resp.error  = QMI_ERR_NONE_V01;
    
  } while (0);
  
  qmi_csi_send_resp(req_handle, msg_id, response, 
                    sizeof(tmd_set_mitigation_level_resp_msg_v01));
					
  ADSPPM_LOG_FUNC_EXIT(QMI_CSI_CB_NO_ERR);  
  return QMI_CSI_CB_NO_ERR;
}

/**
  @brief adsppm_therm_handle_dev_reg_notify

  This function processes incoming requests for the QMI thermal
  mitigation device services with msg_id 
  QMI_TMD_REGISTER_NOTIFICATION_MITIGATION_LEVEL_REQ_V01. 

  @param  : connection_handle: Client connection making request. 
            req_handle: QMI request handle
            msg_id: QMI msg request ID
            req_c_struct: QMI request structure
            req_c_struct_len: QMI request structure length
            service_cookie: Ignored

  @return : qmi_csi_cb_error.
*/
static qmi_csi_cb_error adsppm_therm_handle_dev_reg_notify(void           *connection_handle,
                                                    qmi_req_handle  req_handle,
                                                    unsigned int    msg_id,
                                                    void           *req_c_struct,
                                                    unsigned int    req_c_struct_len,
                                                    void           *service_cookie)
{
  tmd_register_notification_mitigation_level_req_msg_v01  *request = 
    (tmd_register_notification_mitigation_level_req_msg_v01 *)req_c_struct;
  tmd_register_notification_mitigation_level_resp_msg_v01 *response = 
    (tmd_register_notification_mitigation_level_resp_msg_v01 *)&therm_qmi_resp;
  adsppm_therm_qmi_mitigation_dev_client_type *client = connection_handle;

  unsigned int i;
  ADSPPM_LOG_FUNC_ENTER;

  /* Init response data */
  memset( response, 0,
          sizeof(tmd_register_notification_mitigation_level_resp_msg_v01) );

  do
  {
    /* Validate request. */
    if (adsppm_therm_qmi_validate_request(&(response->resp), &i, req_c_struct_len, 
                                   sizeof(tmd_register_notification_mitigation_level_req_msg_v01),
                                   request->mitigation_device.mitigation_dev_id,
                                   "Register notify") == FALSE)
    {
      break;
    }
    
    /* Store data needed to handle chagne event correctly */
    client->cb_context[i].device_index = i;
    client->cb_context[i].client = client;

    client->event_handle[i] = 
      npa_create_change_event_cb( adsppm_therm_mitigate_node.resources[i].name, 
                                  "Mitigation Notify", 
                                  adsppm_therm_qmi_dev_send_indication_cb, 
                                  (void *) &client->cb_context[i]);
    
    if (client->event_handle[i] == NULL)
    {
      response->resp.result = QMI_RESULT_FAILURE_V01;
      response->resp.error = QMI_ERR_INTERNAL_V01;
      ADSPPM_LOG_PRINTF_1(ADSPPM_LOG_LEVEL_ERROR,  
                       "Failed to register change event handle for %s",
                       adsppm_therm_mitigate_node.resources[i].name);
      break;
    }

   ADSPPM_LOG_PRINTF_1(ADSPPM_LOG_LEVEL_INFO, 
                     "Registered change event handle for %s",
                     adsppm_therm_mitigate_node.resources[i].name);
    
    response->resp.result = QMI_RESULT_SUCCESS_V01;
    response->resp.error  = QMI_ERR_NONE_V01;
    
  } while (0);
  
  qmi_csi_send_resp(req_handle, msg_id, response, 
                    sizeof(tmd_register_notification_mitigation_level_resp_msg_v01));
   
  ADSPPM_LOG_FUNC_EXIT(QMI_CSI_CB_NO_ERR);     
  return QMI_CSI_CB_NO_ERR;
}

/**
  @brief adsppm_therm_handle_dev_dereg_notify

  This function processes incoming requests for the QMI thermal
  mitigation device services with msg_id 
  QMI_TMD_DEREGISTER_NOTIFICATION_MITIGATION_LEVEL_REQ_V01. 

  @param  : connection_handle: Client connection making request. 
            req_handle: QMI request handle
            msg_id: QMI msg request ID
            req_c_struct: QMI request structure
            req_c_struct_len: QMI request structure length
            service_cookie: Ignored

  @return : qmi_csi_cb_error.
*/
static qmi_csi_cb_error adsppm_therm_handle_dev_dereg_notify(void           *connection_handle,
                                                      qmi_req_handle  req_handle,
                                                      unsigned int    msg_id,
                                                      void           *req_c_struct,
                                                      unsigned int    req_c_struct_len,
                                                      void           *service_cookie)
{
  tmd_deregister_notification_mitigation_level_req_msg_v01  *request = 
    (tmd_deregister_notification_mitigation_level_req_msg_v01 *)req_c_struct;
  tmd_deregister_notification_mitigation_level_resp_msg_v01 *response = 
    (tmd_deregister_notification_mitigation_level_resp_msg_v01 *)&therm_qmi_resp;
  adsppm_therm_qmi_mitigation_dev_client_type *client = connection_handle;

  unsigned int i;
  ADSPPM_LOG_FUNC_ENTER;

  /* Init response data */
  memset( response, 0,
          sizeof(tmd_deregister_notification_mitigation_level_resp_msg_v01) );

  do
  {
    /* Validate request. */
    if (adsppm_therm_qmi_validate_request(&(response->resp), &i, req_c_struct_len, 
                                   sizeof(tmd_deregister_notification_mitigation_level_req_msg_v01),
                                   request->mitigation_device.mitigation_dev_id,
                                   "De-register notify") == FALSE)
    {
      break;
    }
    
    if (client->event_handle[i] !=  NULL)
    {
      npa_destroy_event_handle(client->event_handle[i]);
      client->event_handle[i] = NULL;
    }

    ADSPPM_LOG_PRINTF_1(ADSPPM_LOG_LEVEL_INFO, 
                     "De-register change event handle for %s",
                     adsppm_therm_mitigate_node.resources[i].name);
    
    response->resp.result = QMI_RESULT_SUCCESS_V01;
    response->resp.error  = QMI_ERR_NONE_V01;
    
  } while (0);
  
  qmi_csi_send_resp(req_handle, msg_id, response, 
                    sizeof(tmd_deregister_notification_mitigation_level_resp_msg_v01));
					
  ADSPPM_LOG_FUNC_EXIT(QMI_CSI_CB_NO_ERR);  
  return QMI_CSI_CB_NO_ERR;
}


/**
  @brief adsppm_therm_qmi_dev_process_req

  This function processes incoming requests for the QMI thermal
  mitigation device services handler. Sanitizing function. 
  req_c_struct and req_c_struct_len are validated in handling 
  functions. 

  @param  : connection_handle: Client connection making request. 
            req_handle: QMI request handle
            msg_id: QMI msg request ID
            req_c_struct: QMI request structure
            req_c_struct_len: QMI request structure length
            service_cookie: Ignored

  @return : qmi_csi_cb_error.
*/
static qmi_csi_cb_error adsppm_therm_qmi_dev_process_req(void           *connection_handle,
                                                  qmi_req_handle  req_handle,
                                                  unsigned int    msg_id,
                                                  void           *req_c_struct,
                                                  unsigned int    req_c_struct_len,
                                                  void           *service_cookie)
{
  qmi_csi_cb_error retval = QMI_CSI_CB_NO_ERR;
  qmi_response_type_v01 *response = (qmi_response_type_v01 *)&therm_qmi_resp;
  ADSPPM_LOG_FUNC_ENTER;

  if ((adsppm_therm_qmi_validate_connection_handle(connection_handle) == FALSE) ||
      (req_handle == NULL))
  {
    ADSPPM_LOG_PRINTF_1(ADSPPM_LOG_LEVEL_ERROR, 
                     "Invalid request arguments request id: 0x%x", msg_id);
    response->result = QMI_RESULT_FAILURE_V01;
    response->error  = QMI_ERR_INVALID_MESSAGE_ID_V01;
  }
  else
  {
	  switch(msg_id)
	  {
		case QMI_TMD_GET_MITIGATION_DEVICE_LIST_REQ_V01:
		  retval = adsppm_therm_handle_dev_list_req(connection_handle, req_handle, msg_id,
											 req_c_struct, req_c_struct_len,
											 service_cookie);
		  break;
		case QMI_TMD_SET_MITIGATION_LEVEL_REQ_V01:
		  retval = adsppm_therm_handle_dev_set_level_req(connection_handle, req_handle,  msg_id,
												  req_c_struct, req_c_struct_len,
												  service_cookie);
		  break;
		case QMI_TMD_GET_MITIGATION_LEVEL_REQ_V01:
		  retval = adsppm_therm_handle_dev_get_level_req(connection_handle, req_handle, msg_id,
												  req_c_struct, req_c_struct_len,
												  service_cookie);
		  break;
		case QMI_TMD_REGISTER_NOTIFICATION_MITIGATION_LEVEL_REQ_V01:
		  retval = adsppm_therm_handle_dev_reg_notify(connection_handle, req_handle, msg_id,
											   req_c_struct, req_c_struct_len,
											   service_cookie);
		  break;
		case QMI_TMD_DEREGISTER_NOTIFICATION_MITIGATION_LEVEL_REQ_V01:
		  retval = adsppm_therm_handle_dev_dereg_notify(connection_handle, req_handle, msg_id,
												 req_c_struct, req_c_struct_len,
												 service_cookie);
		  break;
		default:
		  ADSPPM_LOG_PRINTF_1(ADSPPM_LOG_LEVEL_ERROR,  "Unhandled mitigation request id: 0x%x", 
						   msg_id);
		  response->result = QMI_RESULT_FAILURE_V01;
		  response->error  = QMI_ERR_INVALID_MESSAGE_ID_V01;
		  qmi_csi_send_resp(req_handle, msg_id, response, sizeof(qmi_response_type_v01));
		  break;
	  }
  }
  ADSPPM_LOG_FUNC_EXIT(retval);  
  return retval;
}


/**
 * @brief Service thread for Thermal QMI service
 *
 * This function implements the servie thread for the Thermal 
 * QMI service 
 * 
 * @param[in] unused  Unused parameter
 */
void adsppm_therm_qmi_service_thread(void *unused)
{
  static adsppm_therm_service_context_type service_cookie; /* QMI service cookie */

  qmi_csi_os_params os_params;
  qmi_csi_options adsppm_therm_qmi_dev_options;
  qmi_idl_service_object_type adsppm_therm_service_object = tmd_get_service_object_v01();
  ADSPPM_LOG_FUNC_ENTER;
  
  /*  Initialize the DEM system on this target. */
  adsppm_therm_target_init();
  
  if(NULL != adsppm_therm_service_object)
  {
	  os_params.sig = ADSPPM_THERM_QMI_MITIGATION_DEV_SIG;
	  os_params.signal = &adsppm_therm_qmi_service_sig;
	  
	  QMI_CSI_OPTIONS_INIT(adsppm_therm_qmi_dev_options);
	  QMI_CSI_OPTIONS_SET_INSTANCE_ID(adsppm_therm_qmi_dev_options, 0x1);
	  QMI_CSI_OPTIONS_SET_MAX_OUTSTANDING_INDS(adsppm_therm_qmi_dev_options, ADSPPM_THERM_QMI_MITIGATION_MAX_CLIENT_NUM);
	 

	  if (qmi_csi_register_with_options(adsppm_therm_service_object, adsppm_therm_qmi_dev_connect, 
					   adsppm_therm_qmi_dev_disconnect, adsppm_therm_qmi_dev_process_req,
					    &service_cookie, &os_params, &adsppm_therm_qmi_dev_options, &service_cookie.service_handle) != QMI_CSI_NO_ERR)
	  {
		ADSPPM_LOG_PRINTF_0(ADSPPM_LOG_LEVEL_ERROR,  "QMI mitigation service register error");
	  }
	  else
	  {
		ADSPPM_LOG_PRINTF_0(ADSPPM_LOG_LEVEL_INFO,  "QMI mitigation service register okay");
	  }

	  while(1)
	  {
		qurt_anysignal_wait(os_params.signal, ADSPPM_THERM_QMI_MITIGATION_DEV_SIG);
		qurt_anysignal_clear(os_params.signal, ADSPPM_THERM_QMI_MITIGATION_DEV_SIG);
		qmi_csi_handle_event(service_cookie.service_handle, &os_params);
	  }
  }
  ADSPPM_LOG_FUNC_EXIT(0);
}


/**
 * @brief Initialization function for the Thermal QMI service
 *
 * This function implements the initialization code for the 
 * Thermal QMI service 
 */
void adsppm_therm_qmi_init(void)
{
  /* Start the task */
  rcinit_handshake_startup(); // required rcinit handshake
  
  if(AsicFeatureState_Enabled == ACM_GetFeatureStatus(AsicFeatureId_Adsp_LowTemp_Voltage_Restriction))
  {
  static char adsppm_therm_qmi_service_stack[ADSPPM_THERM_QMI_SERVICE_STACK_SIZE];

  qurt_anysignal_init(&adsppm_therm_qmi_service_sig);
  qurt_thread_attr_init(&adsppm_therm_qmi_service_attr);
  qurt_thread_attr_set_name(&adsppm_therm_qmi_service_attr, "adsppmThermalQmiSvc");
  qurt_thread_attr_set_priority(&adsppm_therm_qmi_service_attr, 10);
  qurt_thread_attr_set_stack_size(&adsppm_therm_qmi_service_attr,
                                  ADSPPM_THERM_QMI_SERVICE_STACK_SIZE);
  qurt_thread_attr_set_stack_addr(&adsppm_therm_qmi_service_attr, adsppm_therm_qmi_service_stack);
  qurt_thread_create(&adsppm_therm_qmi_service_tcb, &adsppm_therm_qmi_service_attr, 
                     adsppm_therm_qmi_service_thread, NULL);
  }
}


