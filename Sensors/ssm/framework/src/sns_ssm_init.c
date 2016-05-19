/*=============================================================================
  FILE: sns_ssm_init.c

  This file contains the initialization subroutine for the Sensors Service 
  Manager implementation.

  Copyright (c) 2014 Qualcomm Technologies, Inc.  All Rights Reserved.
  Qualcomm Technologies Proprietary and Confidential.
=============================================================================*/

/* $Header: //components/rel/ssc.adsp/2.6.1/ssm/framework/src/sns_ssm_init.c#1 $  */
/* $DateTime: 2014/12/01 08:57:58 $ */
/* $Author: pwbldsvc $ */

/*=============================================================================
  EDIT HISTORY FOR MODULE

  This section contains comments describing changes made to the module.
  Notice that changes are listed in reverse chronological order. 

  when        who  what, where, why
  ----------  ---  ------------------------------------------------------------
  2014-01-22  dk   Initial version

=============================================================================*/


#define __SNS_MODULE__ SNS_SSM

/*-----------------------------------------------------------------------------
* Include Files
* ---------------------------------------------------------------------------*/

#include "qurt_elite.h"
#include "sns_common.h"
#include "sns_osa.h"
#include "qmi_csi.h"
#include <qmi_client.h>
#include <qmi_idl_lib_internal.h>
#include "sns_init.h"
#include "sensor1.h"


// Time service
#include "sns_time_api_v02.h"
#include "sns_ssm_time.h"

// Sync Proxy service
#include "sns_sync_proxy_v01.h"
#include "sns_ssm_sync_proxy.h"

// ADSP error codes
#include "adsp_error_codes.h"

// SSM header files
#include "sns_ssm_priv.h"

/* -----------------------------------------------------------------------
** Static variables
** ----------------------------------------------------------------------- */
static OS_STK ssm_stack[SNS_MODULE_STK_SIZE_DSPS_SSM];               // Stack memory for the SSM Thread

sns_ssm_type_s sns_ssm;               // Primary data structure used by 
                                      // SSM framework

/*=============================================================================
  FUNCTION:  sns_ssm_handle_req_cb
=============================================================================*/
/*!
   @brief    qmi_csi_process_req callback for SSM

   @detail  This Function implements the qmi_csi_process_req_callback function 
            as defined in qmi_csi.h. When SSM receives an signal indicating a
            new event has been received, SSM calls qmi_csi_handle_event. The
            QCSI framework then decodes the received message and then calls 
            this function.

   @param[i]   *connection_handle  Handle provided to QCSI in 
                                   sns_ssm_qmi_csi_connect_cb
   @param[i]   req_handle          Handle provided by framework to identify
                                   this transaction
   @param[i]   msg_id              Message ID for the received message
   @param[i]   req_c_struct        C structure with decoded message
   @param[i]   req_c_struct_len    C data structure size
   @param[i]   service_cookie      Handle provided by SSM to QCSI to when
                                   registering service

   @return     err                 Returns QMI_CSI_CB_NO_ERR if successful.
                                   Otherwise returns QMI_CSI_CB_UNSUPPORTED_ERR

 */
/*===========================================================================*/
static qmi_csi_cb_error sns_ssm_handle_req_cb
(
  void                     *connection_handle,
  qmi_req_handle           req_handle,
  unsigned int             msg_id,
  void                     *req_c_struct,
  unsigned int             req_c_struct_len,
  void                     *service_cookie
)
{
   uint8_t i;
   bool cookie_valid = false;

   SNS_SSM_PRINTF0(LOW, "SSM: QMI callback");
   sns_ssm_service *srv = (sns_ssm_service *) service_cookie;

   for(i = 0; i < SNS_SSM_MAX_SERVICES; i++)
   {
      if(srv == &sns_ssm.ssm_service[i])
      {
         cookie_valid = true;
         break;
      }
   }

   if(cookie_valid == true)
   {
      // Check if Time Service Request message
      if(srv->service == SNS_SSM_SRV_TIME_SERVICE)
      {
         if(msg_id == SNS_TIME_TIMESTAMP_REQ_V02)
         {
            if( SNS_SUCCESS != sns_ssm_time_proc_req(req_handle))
            {
               return QMI_CSI_CB_INTERNAL_ERR;
            }
         }
         else
         {
            SNS_SSM_PRINTF0(LOW, "SSM: QMI callback: invalid message pointer");
            return QMI_CSI_CB_UNSUPPORTED_ERR;
         }
      }
      else if(srv->service == SNS_SSM_SRV_SYNC_PROXY_SERVICE)
      {
        sns_err_code_e err;
        err = sns_ssm_sync_proxy_proc_req( (sns_ssm_qmi_connection_s*)connection_handle,
                                           req_handle,
                                           msg_id, req_c_struct );
        if( SNS_ERR_BAD_MSG_ID == err )
        {
          SNS_SSM_PRINTF0(HIGH, "SSM: Sync Proxy unknown message ID");
          return QMI_CSI_CB_UNSUPPORTED_ERR;
        }
        else if( SNS_SUCCESS != err )
        {
          SNS_SSM_PRINTF1(ERROR, "SSM: Sync Proxy req error %d", err);
          return QMI_CSI_CB_INTERNAL_ERR;
        }
      }
      else
      {
         SNS_SSM_PRINTF0(LOW, "SSM: QMI callback: invalid Service");
      }

      //TODO: Insert the message into SSM queue and return
   }
   else
   {
      SNS_SSM_PRINTF0(LOW, "SSM: QMI callback: invalid service cookie");
   }
   return QMI_CSI_CB_NO_ERR;
}


/*=============================================================================
  FUNCTION:  sns_ssm_qmi_csi_connect_cb
=============================================================================*/
/*!
  @brief qmi_csi_connect callback for SSM

  @detail   This Function implements the qmi_csi_connect callback function 
            defined in qmi_csi.h. The QCSI framework calls this callback 
            function when it receives a request from each service user (client)

   @param[i]   client_handle        Handle used by QCSI framework to identify 
                                    the client
   @param[i]   service_cookie       Service specific data used by SSM to 
                                    identify a service.
   @param[o]   connection_handle    The SSM service returns this handle to QCSI
                                    framework to represent this client 
                                    connection

   @return     err                  Returns QMI_CSI_CB_NO_ERR if successful.
                                    Otherwise returns QMI_CSI_CB_CONN_REFUSED
 */
/*===========================================================================*/

qmi_csi_cb_error sns_ssm_qmi_csi_connect_cb(
   qmi_client_handle    client_handle,
   void                 *service_cookie,
   void                 **connection_handle)
{
   uint8_t i;
   qmi_csi_cb_error err = QMI_CSI_CB_CONN_REFUSED;
   sns_ssm_service * srv = (sns_ssm_service *) service_cookie;
   bool cookie_valid = false;



   for(i = 0; i < SNS_SSM_MAX_SERVICES; i++)
   {
      if(srv == &sns_ssm.ssm_service[i])
      {
         cookie_valid = true;
         break;
      }
   }

   if (cookie_valid == true)
   {
      for (i = 0; i < SNS_SSM_MAX_CLIENT_CONNECTIONS; i++)
      {
         if(!(srv->connection_handle[i].connection_valid))
         {
            srv->connection_handle[i].connection_valid = true;
            srv->connection_handle[i].client_handle = client_handle;
            *connection_handle = (void*)&(srv->connection_handle[i]);
            err = QMI_CSI_CB_NO_ERR;
            break;
         }
      }
   }

   return err;

}

/*=============================================================================
  FUNCTION:  sns_ssm_qmi_csi_disconnect_cb
=============================================================================*/
/*!
  @brief       qmi_csi_disconnect callback for SSM

  @detail      This callback function is called by QCSI framework when the 
               service user (client) disconnects.

   @param[i]   *connection_handle   Handle provided to QCSI in 
                                    sns_ssm_qmi_csi_connect_cb
   @param[i]   *service_cookie      Handle provided by SSM to QCSI to when 
                                    registering service

  @return   none
 */
/*===========================================================================*/

void sns_ssm_qmi_csi_disconnect_cb
(
  void* connection_handle,
  void* service_cookie
)
{
   sns_ssm_service * srv = (sns_ssm_service *) service_cookie;
   uint8_t i;
   bool cookie_valid = false;

   for(i = 0; i < SNS_SSM_MAX_SERVICES; i++)
   {
      if(srv == &sns_ssm.ssm_service[i])
      {
         cookie_valid = true;
         break;
      }
   }


   if (cookie_valid == true)
   {
      for(i = 0; i < SNS_SSM_MAX_CLIENT_CONNECTIONS; i++)
      {
         if(&srv->connection_handle[i] == connection_handle)
         {
            srv->connection_handle[i].connection_valid = false;
            srv->connection_handle[i].client_handle = NULL;
            if( srv->service_disconnect_fcn != NULL )
            {
              srv->service_disconnect_fcn();
            }
            break;
         }
      }
   }

}


/*=============================================================================
  FUNCTION:  sns_ssm_task
=============================================================================*/
/*!
  @brief       Main loop for the SSM thread

  @detail      This function containst the main loop for the SSM thread.
               Control never returns from this function. The SSM thread waits
               for an event and then calls the appropriate function to handle
               each event.

   @param[i]   *sns_ssm   The Primary data structure used by the SSM framework


  @return   none
 */
/*===========================================================================*/



void sns_ssm_task(sns_ssm_type_s *sns_ssm)
{
   uint8_t ssm_task_index;

   while(true)
   {
      OS_FLAGS    sig_flags = 0;
      OS_FLAGS    wait_flags = 0;
      uint8_t     err;

      wait_flags = SNS_SSM_QMI_WAIT_SIG | SNS_SSM_SYNC_PROXY_DISCON_SIG;
      // The OS will wait for a signal. When a signal is recieved, it will 
      // consume it and also return the signal that was recieved. 
      sig_flags = sns_os_sigs_pend(sns_ssm->ssm_flag_grp,
                                   wait_flags,
                                   OS_FLAG_WAIT_SET_ANY + OS_FLAG_CONSUME,
                                   0,
                                   &err);
      if(SSM_BIT_TEST(sig_flags, SNS_SSM_SYNC_PROXY_DISCON_SIG))
      {
        sns_ssm_sync_proxy_proc_discon();
      }
      if(SSM_BIT_TEST(sig_flags, SNS_SSM_QMI_WAIT_SIG))
      {
         for(ssm_task_index = 0; ssm_task_index < SNS_SSM_MAX_SERVICES; ssm_task_index++)
         {
            if(sns_ssm->ssm_service[ssm_task_index].service_valid == true)
            {
              qmi_csi_handle_event(sns_ssm->ssm_service[ssm_task_index].service_handle,
                                   &sns_ssm->ssm_service[ssm_task_index].os_params);
            }
         }
      }
      /* Insert future functions here */

   }

}


/*=============================================================================
  FUNCTION:  ssm_init_thread
==============================================================================*/
/*!
  @brief       Initializes the SSM thread

  @detail      This function performs all the initializations required by the
               SSM thread Registering for QCCI and QCSI also occurs in this
               function.

  @param[i]    *arg      NULL pointer that is not used

  @return   none
 */
/*===========================================================================*/

void ssm_init_thread( void * args)
{

   uint8_t err;
   sns_err_code_e sns_err;
   uint8_t i;


   for(i = 0; i < SNS_SSM_MAX_SERVICES; i++)
   {
      sns_ssm.ssm_service[i].service_valid = NULL;
   }

   /*=============Initialize services========================================*/

   // Time Service
   SNS_SSM_PRINTF0(LOW, "SSM: Starting Time Service");
   sns_err = sns_ssm_time_init();
   if(sns_err == SNS_SUCCESS)
   {
      sns_ssm.ssm_service[0].service = SNS_SSM_SRV_TIME_SERVICE;
      sns_ssm.ssm_service[0].service_cookie_ptr = 
                                      (void *)&sns_ssm.ssm_service[0];
      sns_ssm.ssm_service[0].service_disconnect_fcn = NULL;
      
      sns_os_sigs_add(sns_ssm.ssm_flag_grp, SNS_SSM_QMI_WAIT_SIG);
      sns_os_set_qmi_csi_params(sns_ssm.ssm_flag_grp,
                                SNS_SSM_QMI_WAIT_SIG,
                                &sns_ssm.ssm_service[0].os_params,&err);
      SNS_ASSERT(err == OS_ERR_NONE);

      QMI_CSI_OPTIONS_INIT(sns_ssm.ssm_service[0].service_options);
      QMI_CSI_OPTIONS_SET_INSTANCE_ID(sns_ssm.ssm_service[0].service_options,
                                      SNS_SSC_IMPL_V02);
      sns_ssm.ssm_service[0].service_status = 
                 (uint32_t) qmi_csi_register_with_options(
                                      sns_smr_get_svc_obj(SNS_TIME2_SVC_ID_V01),
                                      sns_ssm_qmi_csi_connect_cb,
                                      sns_ssm_qmi_csi_disconnect_cb,
                                      sns_ssm_handle_req_cb,
                                      sns_ssm.ssm_service[0].service_cookie_ptr,
                                      &sns_ssm.ssm_service[0].os_params,
                                      &sns_ssm.ssm_service[0].service_options,
                                      &sns_ssm.ssm_service[0].service_handle);
      sns_ssm.ssm_service[0].service_valid = true;
   }

   // Sync Proxy Service
   SNS_SSM_PRINTF0(LOW, "SSM: Starting Sync Proxy");
   sns_err = sns_ssm_sync_proxy_init();
   if(sns_err == SNS_SUCCESS)
   {
      sns_ssm.ssm_service[1].service = SNS_SSM_SRV_SYNC_PROXY_SERVICE;
      sns_ssm.ssm_service[1].service_cookie_ptr = 
                                      (void *)&sns_ssm.ssm_service[1];
      sns_ssm.ssm_service[1].service_disconnect_fcn = sns_ssm_sync_proxy_proc_discon;

      sns_os_sigs_add(sns_ssm.ssm_flag_grp, SNS_SSM_QMI_WAIT_SIG);
      sns_os_sigs_add(sns_ssm.ssm_flag_grp, SNS_SSM_SYNC_PROXY_RESP_MSG_SIG);
      sns_os_sigs_add(sns_ssm.ssm_flag_grp, SNS_SSM_SYNC_PROXY_DISCON_SIG);
      sns_os_set_qmi_csi_params(sns_ssm.ssm_flag_grp,
                                SNS_SSM_QMI_WAIT_SIG,
                                &sns_ssm.ssm_service[1].os_params,&err);
      SNS_ASSERT(err == OS_ERR_NONE);

      QMI_CSI_OPTIONS_INIT(sns_ssm.ssm_service[1].service_options);
      /*
      QMI_CSI_OPTIONS_SET_INSTANCE_ID(sns_ssm.ssm_service[1].service_options,
                                      SNS_SSC_IMPL_V02);
      */
      sns_ssm.ssm_service[1].service_status = 
                 (uint32_t) qmi_csi_register_with_options(
                                      sns_smr_get_svc_obj(SNS_SYNC_PROXY_SVC_ID_V01),
                                      sns_ssm_qmi_csi_connect_cb,
                                      sns_ssm_qmi_csi_disconnect_cb,
                                      sns_ssm_handle_req_cb,
                                      sns_ssm.ssm_service[1].service_cookie_ptr,
                                      &sns_ssm.ssm_service[1].os_params,
                                      &sns_ssm.ssm_service[1].service_options,
                                      &sns_ssm.ssm_service[1].service_handle);
      sns_ssm.ssm_service[1].service_valid = true;
   }

   // Init done
   sns_init_done();

   sns_ssm_task(&sns_ssm);

   // Main task loop, does not return
}

/*=============================================================================
  FUNCTION:  sns_ssm_init
=============================================================================*/
/*!
  @brief    Creates SSM thread

  @detail   This function creates the SSM thread. See sns_init.h

  @return   err   Returns SNS_SUCCESS if successful.
 */
/*===========================================================================*/

sns_err_code_e sns_ssm_init( void )
{
   uint8_t        err;

   SNS_SSM_PRINTF0(LOW, "SSM: Creating SSM thread");
   //initialize events

   sns_ssm.ssm_flag_grp = sns_os_sigs_create(SNS_SSM_TIMER_SIG, &err);
   SNS_ASSERT(sns_ssm.ssm_flag_grp != NULL);

   err = sns_os_task_create_ext( ssm_init_thread,
                                 NULL,
                                 &ssm_stack[SNS_MODULE_STK_SIZE_DSPS_SSM-1],
                                 SNS_MODULE_PRI_DSPS_SSM,
                                 SNS_MODULE_PRI_DSPS_SSM,
                                 &ssm_stack[0],
                                 SNS_MODULE_STK_SIZE_DSPS_SSM,
                                 (void *)0,
                                 OS_TASK_OPT_STK_CHK | OS_TASK_OPT_STK_CLR,
                                 (uint8_t *)"SNS_SSM");
   return err;
}
