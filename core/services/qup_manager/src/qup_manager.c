/*====*====*====*====*====*====*====*====*====*====*====*====*====*====*====*

    P H R I P H E R A L    A C C E S S    C O N T R O L    M A N A G E R     

GENERAL DESCRIPTION
  This module maintains a QUP table which contains registration
  information about the drivers who register for it. This module also provides
  a QMI service listen to the commands from APPs.

Copyright (c) 2014 by Qualcomm Technologies Incorporated.  All Rights Reserved.

  EDIT HISTORY FOR MODULE

  when        who     what, where, why
  ----------  ---     -----------------------------------------------------------
  2014-06-28  davlee  test code to verify QUP_MANAGER QMI services 

*====*====*====*====*====*====*====*====*====*====*====*====*====*====*====*/


#include "qup_manager.h"
#include <stdlib.h>
#include <comdef.h>
#include <qurt.h>
#include "msg_diag_service.h"
#include "qmi_csi.h"

#include "qup_manager_v01.h"

#define DEBUG

/* Debug printf configuration */
#ifdef DEBUG
  #define DEBUG_PRINTF(fmt, arg1, arg2) \
     MSG_SPRINTF_2(MSG_SSID_TMS, MSG_LEGACY_HIGH, fmt, arg1, arg2); \
     qurt_printf(fmt, arg1, arg2);
#else
  #define DEBUG_PRINTF(fmt, arg1, arg2) {}
#endif

/* Error printf configuration */
#define ERR_PRINTF(fmt, arg1, arg2) \
   MSG_SPRINTF_2(MSG_SSID_TMS, MSG_LEGACY_HIGH, fmt, arg1, arg2); \
   qurt_printf(fmt, arg1, arg2);

typedef struct {
	int id;						  /* QUP ID - set to -1 if invalid or disabled */
	int (*driver_enable)(void);	  /* Enable driver callback */
	int (*driver_disable)(void);  /* Disable driver callback */
} qup_instance_t;

#define QUPM_QMI_SVC_WAIT_MASK 0x2
#define QUPM_QMI_SVC_STACK_SIZE 1024 
#define NUM_QUPS 12 /* Number of QUPs supported */

/*========================================
            GLOBAL VARIABLES
========================================*/
qurt_anysignal_t   qupm_qmi_service_sig;
qurt_thread_t      qupm_qmi_service_tcb;
qurt_thread_attr_t qupm_qmi_service_attr;
qup_instance_t QUP_TABLE[NUM_QUPS];

/*============================================ 
 This structure stores general context 
 used with QMI service handle.
 Currently doesn't have other implementation.
=============================================*/
typedef struct
{
  qmi_csi_service_handle service_handle;
} service_context_type;

//void qup_manager_framework_init(void);
/*=========================================================================
FUNCTION qup_manager_framework_init

DESCRIPTION
  Initialize the QUP_TABLE 
===========================================================================*/
void qup_manager_framework_init(void)
{
	int i;
	DEBUG_PRINTF("%s: Number of QUPs = %i\n", __func__, NUM_QUPS);

	/* Initialize Global QUP Table */
	for (i = 0; i < NUM_QUPS; i++) {
		QUP_TABLE[i].id = -1;
		QUP_TABLE[i].driver_enable = NULL;
		QUP_TABLE[i].driver_disable = NULL;
	}
}

/*=========================================================================
FUNCTION qup_manager_register_driver

DESCRIPTION
  API for drivers to register for QUP Manager

DEPENDENCIES
  Must be called after module has been fully initialized

RETURN VALUE
  0 on success, -1 on failure
===========================================================================*/
int qup_manager_register_driver(
    unsigned qup_id,             /*Indicate which QUP ID was used by the driver*/
	int (*driver_enable)(void),  /*Callback function to enable the driver*/
	int (*driver_disable)(void)) /*Callback function to disable the driver*/
{
	DEBUG_PRINTF("%s: QUP ID=%u\n", __func__, qup_id);

	if (qup_id < 0 || qup_id >= NUM_QUPS || NULL == driver_enable ||
			NULL == driver_disable) {
	  DEBUG_PRINTF("%s: ERROR\n", __func__, 0);
	    return -1;
	}

	QUP_TABLE[qup_id].driver_enable = driver_enable;
	QUP_TABLE[qup_id].driver_disable = driver_disable;

	return 0;
}

/*=========================================================================
FUNCTION qup_manager_unregister_driver

DESCRIPTION
  API for drivers to unregister for QUP Manager
===========================================================================*/
void qup_manager_unregister_driver(unsigned qup_id)
{
	DEBUG_PRINTF("%s: QUP ID=%u\n", __func__, qup_id);

	if (qup_id < NUM_QUPS) {
		QUP_TABLE[qup_id].driver_enable = NULL;
		QUP_TABLE[qup_id].driver_disable = NULL;
	} else {
		DEBUG_PRINTF("%s: ERROR QUP ID invalid\n", __func__, 0);
	}
}


/*=========================================================================
FUNCTION qup_manager_connect_cb

DESCRIPTION
  This function implements the callback for when a client 
  connects to the QUP_MANAGER QMI service 

RETURN VALUE
  QMI_CSI_NO_ERR on success, error code on error
===========================================================================*/
static qmi_csi_cb_error 
qup_manager_connect_cb
(
  qmi_client_handle  client_handle,       /*QMI client handle*/
  void               *service_cookie,     /*Pointer to the service cookie*/
  void               **connection_handle  /*Pointer to the location to store the 
                                            client connection handle*/
)
{
  DEBUG_PRINTF("%s: here\n", __func__, 0);
  if(!connection_handle)
  {
    ERR_PRINTF("%s: connection refused", __func__, 0);
    return QMI_CSI_CB_CONN_REFUSED;
  }

  return QMI_CSI_NO_ERR;
}

/*=========================================================================
FUNCTION qup_manager_disconnect_cb

DESCRIPTION
  This function implements the callback for when a client 
  disconnect to the QUP_MANAGER QMI service 

===========================================================================*/
static void 
qup_manager_disconnect_cb
(
  void *connection_handle,  /*Pointer to the client connection handle*/
  void *service_cookie      /*Pointer to the service cookie*/
)
{
  //Free any memory allocated in connect_cb (If there's any)

  DEBUG_PRINTF("%s: here", __func__, 0);
  return;
}

/*=========================================================================
FUNCTION qup_manager_handle_req_cb

DESCRIPTION
  This function implements the callback for when a client sends 
  a request to the qup_manager QMI service 
  === Standard QMI Response type ===
   typedef struct {
     qmi_result_type_v01 result;
               - QMI_RESULT_SUCCESS				0
               - QMI_RESULT_FAILURE				1
     qmi_error_type_v01 error;
               - QMI_ERR_NONE_V01               0x0000
               - QMI_ERR_DEVICE_NOT_READY_V01   0x0034
               - QMI_ERR_GENERAL_V01            0x002E 
   }qmi_response_type_v01;  

RETURN VALUE
  QMI_CSI_NO_ERR on success, error code on error 
===========================================================================*/
static qmi_csi_cb_error 
qup_manager_handle_req_cb
(
  void               *connection_handle, /*Pointer to the client connection handle*/ 
  qmi_req_handle     req_handle,     	 /*The request handle*/
  unsigned int       msg_id,  		     /*The message id*/
  void               *req_c_struct,      /*Pointer to the request messages structure*/
  unsigned int       req_c_struct_len,   /*The length of req_c_struct*/
  void               *service_cookie     /*Pointer to the service cookie*/
)
{
  DEBUG_PRINTF("%s: here\n", __func__, 0);

  qmi_csi_cb_error rc = QMI_CSI_CB_INTERNAL_ERR;

  if( (NULL == service_cookie) ||
      (NULL == req_c_struct) )
  {
    return rc;
  }

  switch ( msg_id )
  {
    case QMI_QUPM_READY_REQ_V01:
	{
      qupm_ready_req_msg_v01 *req_msg = (qupm_ready_req_msg_v01*) req_c_struct;
	  uint32_t id =  req_msg->qup_id;

      qupm_ready_resp_msg_v01 resp_msg;

      DEBUG_PRINTF("SVC: Received ready req on QUP %d\n", id, 0);

      if (QUP_TABLE[id].driver_enable != NULL &&
	      QUP_TABLE[id].driver_disable != NULL)
      {
	     resp_msg.resp.result = QMI_RESULT_SUCCESS_V01;
	     resp_msg.resp.error = QMI_ERR_NONE_V01;
	  }else {
	     resp_msg.resp.result = QMI_RESULT_FAILURE_V01;
	     resp_msg.resp.error = QMI_ERR_DEVICE_NOT_READY_V01;
		 ERR_PRINTF("SVC: QUP %d not ready\n", id, 0);
	  }
	  rc = qmi_csi_send_resp(req_handle, msg_id, (void *) &resp_msg, 
							 sizeof(qupm_ready_resp_msg_v01));
	}
	break;

    case QMI_QUPM_TAKE_OWNERSHIP_REQ_V01: 
    {
      qupm_take_ownership_req_msg_v01 *req_msg = (qupm_take_ownership_req_msg_v01*) req_c_struct;
      qupm_take_ownership_resp_msg_v01 resp_msg;
	  uint32_t id = req_msg->qup_id;

	  DEBUG_PRINTF("SVC: Received take ownership req on QUP %d\n", id, 0);

	  rc = QUP_TABLE[id].driver_enable();

      if ( !rc )
      {
	     resp_msg.resp.result = QMI_RESULT_SUCCESS_V01;
	     resp_msg.resp.error = QMI_ERR_NONE_V01;
         DEBUG_PRINTF("SVC: Driver enabled on QUP %d\n", id, 0);
	  }else {
	     resp_msg.resp.result = QMI_RESULT_FAILURE_V01;
	     resp_msg.resp.error = QMI_ERR_GENERAL_V01;
         ERR_PRINTF("SVC: Failed to enable driver on QUP %d\n", id, 0);
	  }
		
	  rc = qmi_csi_send_resp(req_handle, msg_id, (void *) &resp_msg, sizeof(qupm_take_ownership_resp_msg_v01));
    }
	break;

    case QMI_QUPM_GIVE_OWNERSHIP_REQ_V01: 
    {
      qupm_give_ownership_req_msg_v01 *req_msg = (qupm_give_ownership_req_msg_v01*) req_c_struct;
      qupm_give_ownership_resp_msg_v01 resp_msg; 
	  uint32_t id = req_msg->qup_id;

	  DEBUG_PRINTF("SVC: Received give ownership req on QUP %d\n", id, 0);

	  rc = QUP_TABLE[id].driver_disable();

      if ( !rc )
      {
	     resp_msg.resp.result = QMI_RESULT_SUCCESS_V01;
	     resp_msg.resp.error = QMI_ERR_NONE_V01;
         DEBUG_PRINTF("SVC: Driver disabled on QUP %d\n", id, 0);
	  }else {
	     resp_msg.resp.result = QMI_RESULT_FAILURE_V01;
	     resp_msg.resp.error = QMI_ERR_GENERAL_V01;
         ERR_PRINTF("SVC: Failed to disable driver on QUP %d\n", id, 0);
	  }
	  rc = qmi_csi_send_resp(req_handle, msg_id, (void *) &resp_msg, sizeof(qupm_give_ownership_resp_msg_v01));
    }
	break;
  }
  DEBUG_PRINTF("%s: rc=%d", __func__, rc);

  return rc;
}

/*=========================================================================
FUNCTION qup_manager_qmi_service_thread

DESCRIPTION
 This function implements the servie thread for the qup_manager
 QMI service 
===========================================================================*/
void qup_manager_qmi_service_thread(void *unused)
{
  
  qmi_idl_service_object_type qupm_service_object = qupm_get_service_object_v01();
  static service_context_type service_cookie;
  qmi_csi_options opt;

  qmi_csi_os_params os_params;
  os_params.sig = QUPM_QMI_SVC_WAIT_MASK;
  os_params.signal = &qupm_qmi_service_sig;

  qmi_csi_error rc = QMI_CSI_INTERNAL_ERR;
  QMI_CSI_OPTIONS_INIT(opt);
  QMI_CSI_OPTIONS_SET_INSTANCE_ID(opt, QUPM_INSTANCE_ADSP_V01);

  if ( NULL != qupm_service_object )
  {
	rc = qmi_csi_register_with_options( 
	            qupm_service_object, qup_manager_connect_cb,
		        qup_manager_disconnect_cb, qup_manager_handle_req_cb,
		        &service_cookie, &os_params,&opt,
		        &service_cookie.service_handle                
		      );
  }

  if ( QMI_CSI_NO_ERR != rc ) {
    ERR_PRINTF("Unable to start QUP MANAGER QMI service\n", 0, 0);
	return;
  }

  DEBUG_PRINTF("QUP MANAGER QMI service started...\n", 0, 0);
  while (1) {
	qurt_anysignal_wait(os_params.signal, QUPM_QMI_SVC_WAIT_MASK);
	qurt_anysignal_clear(os_params.signal, QUPM_QMI_SVC_WAIT_MASK);
	rc = qmi_csi_handle_event(service_cookie.service_handle, &os_params);
    DEBUG_PRINTF("Received QUP MANGER QMI EVENT, rc=%d\n", rc, 0);
  }
}

/*=========================================================================
FUNCTION qup_manager_init

DESCRIPTION
 This function implements the initialization code for the qup_manager
 QMI service 
===========================================================================*/
void qup_manager_init(void)
{
  DEBUG_PRINTF("%s: Initialization...pid is %d\n", __func__, qurt_getpid());
  static char qupm_qmi_service_stack[QUPM_QMI_SVC_STACK_SIZE];

  // Initialize QUP_TABLE
  qup_manager_framework_init();

  // Start QMI Service
  qurt_anysignal_init(&qupm_qmi_service_sig);
  qurt_thread_attr_init(&qupm_qmi_service_attr);
  qurt_thread_attr_set_name(&qupm_qmi_service_attr, "QUP_MQmiSvc");
  qurt_thread_attr_set_priority(&qupm_qmi_service_attr, 10);
  qurt_thread_attr_set_stack_size(&qupm_qmi_service_attr, 
                                  QUPM_QMI_SVC_STACK_SIZE);
  qurt_thread_attr_set_stack_addr(&qupm_qmi_service_attr, qupm_qmi_service_stack);
  qurt_thread_create(&qupm_qmi_service_tcb, &qupm_qmi_service_attr, 
                     qup_manager_qmi_service_thread, NULL);
  return;
}

