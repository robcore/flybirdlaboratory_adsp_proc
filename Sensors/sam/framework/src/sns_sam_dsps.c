/*============================================================================
  FILE: sns_sam_dsps.c

  This file contains Sensors Algorithm Manager implementation specific to DSPS

  Copyright (c) 2010-2014 Qualcomm Technologies, Inc.  All Rights Reserved.
  Qualcomm Technologies Proprietary and Confidential.
 ============================================================================*/

/* $Header: //components/rel/ssc.adsp/2.6.1/sam/framework/src/sns_sam_dsps.c#1 $ */
/* $DateTime: 2014/12/01 08:57:58 $ */
/* $Author: pwbldsvc $ */

/*============================================================================
  EDIT HISTORY FOR MODULE

  This section contains comments describing changes made to the module.
  Notice that changes are listed in reverse chronological order.

  when        who  what, where, why
  ----------  ---  -----------------------------------------------------------
  2014-09-22  sc   Fix KW errors
  2014-09-14  sc   Remove legacy algorithm management
  2014-09-04  hw   Remove/comment out log packet support in legacy SAM
  2014-07-22  ps   Fix compiler warnings
  2014-05-04  hw   Propagating data type checking for each algorithm's algo input update
  2014-03-24  pk   Prevent bad input from being fed to RV and Game RV
  2014-03-11  rt   Fix SAM memory leak. Free request msg ptr for dep. co-located algos
  2014-02-19  pk   Add enable request validation
  2014-02-05  ks   Integrated Feature Motion Classifier support
  2014-01-30  pk   Allow sns_sam_prep_algo_report_ind() to return error code
  2014-01-27  hw   Patch QDSS SW logging into SAM framework 
  2014-01-23  pk   Support direct function calls (non QMI) for ALGO_UPDATE_REQ
  2013-12-17  lka  Refactored sns_sam_update_input_type()
  2013-12-10  ad   Support config of min default sample rate of fusion algorithms
  2013-10-29  pk   Removed event flag from output structure of Facing algorithm
  2013-10-24  ad   Fix Gyro tap integration
  2013-10-20  ad   Fixed klocwork errors
  2013-10-18  ad   Fix bug in updating batch period
  2013-10-14  sc   Added support for oem_1 algo
  2013-10-10  sc   Add relative threshold support
  2013-10-03  pk   Add support for batch indicator
  2013-09-18  pk   Rework sns_sam_algo_send_batch_ind()
  2013-09-18  pk   Use client specified coordinate system for Rotation vector
  2013-09-11  ad   Fix suspend behavior for SMD and Gravity
  2013-09-09  ad   Update default behavior to not wakeup Apps from suspend for indications
  2013-09-06  dk   Increased logging support for SMD
  2013-09-03  ag   Remove double free when sam_mr_send fails
  2013-08-15  vh   Eliminated Klocwork warnings
  2013-08-27  dk   Added logging support for SMD's step inference
  2013-08-22  pk   Changed max back to back batch indications per target
  2013-07-31  hw   Fix Klocwork warning error  
  2013-07-26  vh   Eliminated compiler warnings
  2013-07-13  asj  Limit mag data requests from FMV to 50 Hz
  2013-07-12  gju  Limit mag data requests from FMV to 60 Hz
  2013-06-27  gju  Remove Mag cal and use SMGR for mag instead
  2103-06-06  pd   Added Significant Motion Detection
  2013-06-05  tc   Added support for Game Rotation Vector
  2013-05-16 asr   Removed unused log types.
  2013-05-14  sc   Fixed an issue with updating sensor threshold configuration
                   for the case of magnetometer streaming
  2013-05-01  dc   Set default notification to true to support clients
                   on the Modem processor who do not use the notify field.
  2013-03-16  lka  Modified logic related to MD interrupt processing
  2013-02-19  dc   Retrieve info about notifications during suspend that is
                   passed by the client.
  2013-02-15  asj  added modem scn algo
  2013-02-12  gju  Use SMR message allocation functions
  2013-02-07  asj  added time salt to gyrobuf
  2012-12-08  lka  added support for multiple clients to MD interrupt
  2012-12-07  gju  Use updated SAM framework API
  2012-11-20  vh   Eliminated compiler warnings
  2012-11-15  hw   Migrates Gestures Features from APPS to ADSP
  2012-10-14  sc   Use AMD enable request structure instead of common QMD struct
  2012-10-10  hw   Added ACCEL part in sansor algorithm configuration update
  2012-09-13  vh   Eliminated compiler warnings
  2012-08-10  sc   Merged from mainline the gyrobuf algo service
  2012-08-09  ag   Updated to use official QMI service IDs
  2012-08-09  rp   Add threshold detection support for pressure sensor(windows requirement)
  2012-07-23  ag   Porting from SMR to QMI
  2012-06-13  lka  Increased buffer size in gyrobuf indication message
  2012-05-08  lka  Fixed (gyrobuf algorithm) fixed-point conversion and buffer
                   limit issues
  2012-04-17  lka  Added support for Gyrobuf algorithm
  2012-03-07  ad   Support motion detect algo sample rate config via registry
  2011-11-14  jhh  Updated alloc and free function calls to meet new API
  2011-11-04  sc   Added support for sensor threshold algorithm
  2011-09-21  ad   disable interrupt mode when non-AMD algorithms are active
  2011-07-18  ad   refactor SAM for memory optimization
  2011-07-05  sc   Use timestamp from sensor data for algo report and logging
  2011-06-08  ad   changed the accel sampling rate for QMD to 25Hz
  2011-05-06  ad   support algorithm configuration using sensors registry
  2011-05-02  sc   Modified with updated function prototype for processing
                   messages from another SAM module
  2011-04-20  ad   added support for low power QMD
  2011-04-19  sc   Removed quaternion and gravity algorithm from DSPS
  2011-04-18  ad   move target specific code to target file
  2011-04-12  ad   support SAM power vote
  2011-04-04  sc   Added support for gravity algorithm
  2011-03-31  ad   update algorithm registration
  2011-03-30  sc   Added support for quaternion logging
  2011-03-18  sc   Added support for quaternion algorithm
  2011-03-11  ad   initialize QMD internal config params
  2011-03-11  ad   update algorithm configuration per client specification
  2011-01-28  br   changed constant names for deploying QMI tool ver#2
  2011-01-21  sc   Added support for PCSIM playback
  2011-01-11  ad   initial version

 ============================================================================*/

/*---------------------------------------------------------------------------
 * Include Files
 * -------------------------------------------------------------------------*/
#include "sns_sam_priv.h"

#include "sns_osa.h"
#include "sns_memmgr.h"
#include "sns_debug_str.h"
#include "sns_log_types.h"
#include "sns_reg_common.h"
#include "sns_log_api.h"
#include "sns_profiling.h"

#include "sns_smgr_api_v01.h"

#ifdef FEATURE_SNS_SAM_TILT
#include "integ_angle.h"
#include "sns_sam_integ_angle_v01.h"
#endif /* FEATURE_SNS_SAM_TILT */

#include "sns_sam_modem_scn_v01.h"
#include "modem_scn.h"

/*---------------------------------------------------------------------------
 * Preprocessor Definitions and Constants
 * -------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------
 * Type Declarations
 * -------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------
 * Static Variable Definitions
 * -------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------
 * Function Definitions
 * -------------------------------------------------------------------------*/
extern sns_err_code_e sns_sam_send_modem_scenario(uint8_t scn);

/*=========================================================================
  FUNCTION:  sns_sam_prep_algo_enable_err
  =========================================================================*/
/*!
  @brief Prepare error message to client for algorithm enable request

  @param[i] clientReqMsgPtr: pointer to client request message
  @param[o] clientRespMsgPtr: Pointer to the response message created.
  @param[i] algoSvcId: algorithm service id
  @param[i] errCode: error code

  @return None
*/
/*=======================================================================*/
void sns_sam_prep_algo_enable_err(
   const void* clientReqMsgPtr,
   void** clientRespMsgPtr,
   uint8_t algoSvcId,
   sns_err_code_e errCode)
{
   *clientRespMsgPtr = NULL;

   SNS_SAM_PRINTF2(LOW,
                  "sns_sam_prep_algo_enable_err: algo service id %d, error %d",
                  algoSvcId, errCode);

   if (algoSvcId == SNS_SAM_MODEM_SCN_SVC_ID_V01)
   {
      sns_sam_modem_scn_enable_resp_msg_v01 *enableRespMsgPtr =
         sns_smr_msg_alloc(SNS_SAM_DBG_MOD,sizeof(sns_sam_modem_scn_enable_resp_msg_v01));
      SNS_ASSERT(enableRespMsgPtr != NULL);

      enableRespMsgPtr->resp.sns_result_t = SNS_RESULT_FAILURE_V01;
      enableRespMsgPtr->resp.sns_err_t = errCode;
      enableRespMsgPtr->instance_id_valid = 0;
      sns_sam_prep_resp_msg(clientReqMsgPtr,
                            enableRespMsgPtr,
                            sizeof(sns_sam_modem_scn_enable_resp_msg_v01));
      *clientRespMsgPtr = enableRespMsgPtr;
   }

#ifdef FEATURE_SNS_SAM_TILT
   else if (SNS_SAM_INTEG_ANGLE_SVC_ID_V01 == algoSvcId)
   {
      sns_sam_integ_angle_enable_resp_msg_v01 *enableRespMsgPtr =
         sns_smr_msg_alloc(SNS_SAM_DBG_MOD, sizeof(sns_sam_integ_angle_enable_resp_msg_v01));
      SNS_ASSERT(enableRespMsgPtr != NULL);

      enableRespMsgPtr->resp.sns_result_t = SNS_RESULT_FAILURE_V01;
      enableRespMsgPtr->resp.sns_err_t = errCode;
      enableRespMsgPtr->instance_id_valid = false;
      enableRespMsgPtr->instance_id = SNS_SAM_INVALID_ID;
      sns_sam_prep_resp_msg(clientReqMsgPtr,
                            enableRespMsgPtr,
                            sizeof(sns_sam_integ_angle_enable_resp_msg_v01));
      *clientRespMsgPtr = enableRespMsgPtr;
   }
#endif /* FEATURE_SNS_SAM_TILT */

   else
   {
     SNS_SAM_PRINTF1(HIGH,
                     "sns_sam_prep_algo_enable_err: Cannot handle algo service id %d",
                     algoSvcId);
   }
}

/*=========================================================================
  FUNCTION:  sns_sam_prep_algo_disable_err
  =========================================================================*/
/*!
  @brief Prepare error message to client for algorithm disable request

  @param[i] clientReqMsgPtr: pointer to client request message
  @param[o] clientRespMsgPtr: Pointer to the response message created.
  @param[i] algoSvcId: algorithm service id
  @param[i] errCode: error code

  @return None
*/
/*=======================================================================*/
void sns_sam_prep_algo_disable_err(
   const void* clientReqMsgPtr,
   void** clientRespMsgPtr,
   uint8_t algoSvcId,
   sns_err_code_e errCode)
{
   *clientRespMsgPtr = NULL;

   SNS_SAM_PRINTF2(LOW,
                  "sns_sam_prep_algo_disable_err: algo serviceid %d, error %d",
                  algoSvcId, errCode);

   if (algoSvcId == SNS_SAM_MODEM_SCN_SVC_ID_V01)
   {
      sns_sam_modem_scn_disable_resp_msg_v01 *disableRespMsgPtr =
         sns_smr_msg_alloc(SNS_SAM_DBG_MOD,sizeof(sns_sam_modem_scn_disable_resp_msg_v01));
      SNS_ASSERT(disableRespMsgPtr != NULL);

      disableRespMsgPtr->resp.sns_result_t = SNS_RESULT_FAILURE_V01;
      disableRespMsgPtr->resp.sns_err_t = errCode;
      disableRespMsgPtr->instance_id_valid = 1;
      disableRespMsgPtr->instance_id =
         ((sns_sam_modem_scn_disable_req_msg_v01 *)clientReqMsgPtr)->instance_id;
      sns_sam_prep_resp_msg(clientReqMsgPtr,
                            disableRespMsgPtr,
                            sizeof(sns_sam_modem_scn_disable_resp_msg_v01));
      *clientRespMsgPtr = disableRespMsgPtr;
   }

#ifdef FEATURE_SNS_SAM_TILT
   else if (SNS_SAM_INTEG_ANGLE_SVC_ID_V01 == algoSvcId)
   {
      sns_sam_integ_angle_disable_resp_msg_v01 *disableRespMsgPtr =
         sns_smr_msg_alloc(SNS_SAM_DBG_MOD, sizeof(sns_sam_integ_angle_disable_resp_msg_v01));
      SNS_ASSERT(disableRespMsgPtr != NULL);

      disableRespMsgPtr->resp.sns_result_t = SNS_RESULT_FAILURE_V01;
      disableRespMsgPtr->resp.sns_err_t = errCode;
      disableRespMsgPtr->instance_id_valid = true;
      disableRespMsgPtr->instance_id =
         ((sns_sam_integ_angle_disable_req_msg_v01 *)clientReqMsgPtr)->instance_id;
      sns_sam_prep_resp_msg(clientReqMsgPtr,
                            disableRespMsgPtr,
                            sizeof(sns_sam_integ_angle_disable_resp_msg_v01));
      *clientRespMsgPtr = disableRespMsgPtr;
   }
#endif /* FEATURE_SNS_SAM_TILT */

   else
   {
     SNS_SAM_PRINTF1(HIGH,
                     "sns_sam_prep_algo_disable_err: Cannot handle algo service id %d",
                     algoSvcId);
   }
}

/*=========================================================================
  FUNCTION:  sns_sam_prep_algo_report_err
  =========================================================================*/
/*!
  @brief Prepare error message to client for algorithm report request

  @param[i] clientReqMsgPtr: pointer to client request message
  @param[o] clientRespMsgPtr: Pointer to the response message created.
  @param[i] algoSvcId: algorithm service id
  @param[i] errCode: error code

  @return None
*/
/*=======================================================================*/
void sns_sam_prep_algo_report_err(
   const void* clientReqMsgPtr,
   void **clientRespMsgPtr,
   uint8_t algoSvcId,
   sns_err_code_e errCode)
{
   *clientRespMsgPtr = NULL;
   SNS_SAM_PRINTF2(LOW,
                  "sns_sam_prep_algo_report_err: algo serviceid %d, error %d",
                  algoSvcId, errCode);

   /* Tilt does not have a get report response  */

   if (algoSvcId == SNS_SAM_MODEM_SCN_SVC_ID_V01)
   {
      sns_sam_modem_scn_get_report_resp_msg_v01 *reportRespMsgPtr =
         sns_smr_msg_alloc(SNS_SAM_DBG_MOD,sizeof(sns_sam_modem_scn_get_report_resp_msg_v01));
      SNS_ASSERT(reportRespMsgPtr != NULL);

      reportRespMsgPtr->resp.sns_result_t = SNS_RESULT_FAILURE_V01;
      reportRespMsgPtr->resp.sns_err_t = errCode;
      /* respond with instance ID, other optional fields are not needed */
      reportRespMsgPtr->instance_id_valid = 1;
      reportRespMsgPtr->instance_id =
         ((sns_sam_modem_scn_get_report_req_msg_v01 *)clientReqMsgPtr)->instance_id;
      reportRespMsgPtr->timestamp_valid = 0;
      reportRespMsgPtr->scenario_valid = 0;
      sns_sam_prep_resp_msg(clientReqMsgPtr,
                            reportRespMsgPtr,
                            sizeof(sns_sam_modem_scn_get_report_resp_msg_v01));
      *clientRespMsgPtr = reportRespMsgPtr;
   }
   else
   {
     SNS_SAM_PRINTF1(HIGH,
                     "sns_sam_prep_algo_report_err: Cannot handle algo service id %d",
                     algoSvcId);
   }
}

/*=========================================================================
  FUNCTION:  sns_sam_prep_algo_update_err
  =========================================================================*/
/*!
  @brief Send error message to client for algorithm update request

  @param[i] clientReqMsgPtr: pointer to client request message
  @param[o] clientRespMsgPtr: Pointer to the response message created.
  @param[i] algoSvcId: algorithm service id
  @param[i] errCode: error code

  @return None
*/
/*=======================================================================*/
void sns_sam_prep_algo_update_err(
   const void* clientReqMsgPtr,
   void **clientRespMsgPtr,
   uint8_t algoSvcId,
   sns_err_code_e errCode)
{
}

/*=========================================================================
  FUNCTION:  sns_sam_prep_algo_batch_err
  =========================================================================*/
/*!
  @brief Send error message to client for algorithm batch request

  @param[i] clientReqMsgPtr: pointer to client request message
  @param[o] clientRespMsgPtr: Pointer to the response message created.
  @param[i] algoSvcId: algorithm service id
  @param[i] errCode: error code

  @return None
*/
/*=======================================================================*/
void sns_sam_prep_algo_batch_err(
   const void* clientReqMsgPtr,
   void **clientRespMsgPtr,
   uint8_t algoSvcId,
   sns_err_code_e errCode)
{
}

/*=========================================================================
  FUNCTION:  sns_sam_prep_algo_update_batch_period_err
  =========================================================================*/
/*!
  @brief Send error message to client for algorithm update batch period req

  @param[i] clientReqMsgPtr: pointer to client request message
  @param[o] clientRespMsgPtr: Pointer to the response message created.
  @param[i] algoSvcId: algorithm service id
  @param[i] errCode: error code

  @return None
*/
/*=======================================================================*/
void sns_sam_prep_algo_update_batch_period_err(
   const void* clientReqMsgPtr,
   void **clientRespMsgPtr,
   uint8_t algoSvcId,
   sns_err_code_e errCode)
{
}

/*=========================================================================
  FUNCTION:  sns_sam_get_algo_version_resp
  =========================================================================*/
/*!
  @brief Send response message to client for algorithm version request

  @param[i] algoSvcId: algorithm service id
  @param[o] versionRespMsgPtr: pointer to version response message

  @return None
*/
/*=======================================================================*/
void sns_sam_get_algo_version_resp(
   uint8_t algoSvcId,
   sns_common_version_resp_msg_v01 *versionRespMsgPtr)
{
   SNS_SAM_PRINTF1(LOW, "sns_sam_get_algo_version_resp: algo service id %d",
                   algoSvcId);

   switch (algoSvcId)
   {
#ifdef FEATURE_SNS_SAM_TILT
   case SNS_SAM_INTEG_ANGLE_SVC_ID_V01:
      versionRespMsgPtr->interface_version_number =
         SNS_SAM_INTEG_ANGLE_SVC_V01_IDL_MINOR_VERS;
      versionRespMsgPtr->max_message_id = SNS_SAM_INTEG_ANGLE_SVC_V01_MAX_MESSAGE_ID;
      break;
#endif /* FEATURE_SNS_SAM_TILT */

   case SNS_SAM_MODEM_SCN_SVC_ID_V01:
      versionRespMsgPtr->interface_version_number =
         SNS_SAM_MODEM_SCN_SVC_V01_IDL_MINOR_VERS;
      versionRespMsgPtr->max_message_id = SNS_SAM_MODEM_SCN_SVC_V01_MAX_MESSAGE_ID;
      break;

  default:
      versionRespMsgPtr->interface_version_number = 0;
      versionRespMsgPtr->max_message_id = 0;
      SNS_SAM_DEBUG1(ERROR, DBG_SAM_PROCESS_REQ_INVALID_ALGOREQ, algoSvcId);
      break;
   }
}

/*=========================================================================
  FUNCTION:  sns_sam_get_algo_attrib_resp
  =========================================================================*/
/*!
  @brief Send response message to client for algorithm attributes request

  @param[i] algoSvcId: algorithm service id
  @param[o] attribRespMsgPtr: pointer to attributes query response message

  @return SNS_SUCCESS, if successful
          SNS_ERR_BAD_MSG_ID, if request is unsupported
          SNS_ERR_BAD_PARM, if service is unsupported
*/
/*=======================================================================*/
sns_err_code_e sns_sam_get_algo_attrib_resp(
   sns_sam_algo_s* algoPtr,
   sns_sam_get_algo_attrib_resp_msg_v01 *attribRespMsgPtr)
{
   sns_err_code_e err = SNS_ERR_BAD_PARM;
   if( !algoPtr )
   {
      return err;
   }

   SNS_SAM_PRINTF1(LOW, "sns_sam_get_algo_attrib_resp: algo service id %d",
                   algoPtr->serviceId);

   switch( algoPtr->serviceId )
   {
#ifdef FEATURE_SNS_SAM_TILT
   case SNS_SAM_INTEG_ANGLE_SVC_ID_V01:
      err = SNS_SUCCESS;
      attribRespMsgPtr->algorithm_revision = algoPtr->algorithm_revision;
      attribRespMsgPtr->proc_type = SNS_PROC_SSC_V01;
      attribRespMsgPtr->supported_reporting_modes = algoPtr->supported_reporting_modes;
      attribRespMsgPtr->min_report_rate = algoPtr->min_report_rate;
      attribRespMsgPtr->max_report_rate = algoPtr->max_report_rate;
      attribRespMsgPtr->min_sample_rate = algoPtr->min_sample_rate;
      attribRespMsgPtr->max_sample_rate = algoPtr->max_sample_rate;
      attribRespMsgPtr->max_batch_size = algoPtr->max_batch_size;
      attribRespMsgPtr->power = algoPtr->power;
      break;
#endif /* FEATURE_SNS_SAM_TILT */

   default:
      err = SNS_ERR_BAD_MSG_ID;
      attribRespMsgPtr->algorithm_revision = 0;
      attribRespMsgPtr->proc_type = 0;
      attribRespMsgPtr->supported_reporting_modes = 0;
      attribRespMsgPtr->min_report_rate = 0;
      attribRespMsgPtr->max_report_rate = 0;
      attribRespMsgPtr->min_sample_rate = 0;
      attribRespMsgPtr->max_sample_rate = 0;
      attribRespMsgPtr->max_batch_size = 0;
      attribRespMsgPtr->power = 0;
      SNS_SAM_PRINTF1(ERROR, "sns_sam_get_algo_attrib_resp: algo service id %d not supported",
                   algoPtr->serviceId);
      break;
   }

   return err;
}

/*=========================================================================
  FUNCTION:  sns_sam_prep_algo_report_ind
  =========================================================================*/
/*!
  @brief Prepare an algorithm report indication to client

  @param[i] clientReqPtr: pointer to client request
  @param[o] clientIndMsgPtr: pointer to report indication;
                             NULL, if return value is not SNS_SUCCESS
  @param[i] algoRptPtr: pointer to algorithm report
  @param[io] msgHdrPtr: pointer to client request message header

  @return Sensors error code
*/
/*=======================================================================*/
sns_err_code_e sns_sam_prep_algo_report_ind(
   const sns_sam_client_req_s* clientReqPtr,
   void** clientIndMsgPtr,
   const sns_sam_algo_rpt_s *algoRptPtr,
   sns_smr_header_s* msgHdrPtr)
{
  SNS_SAM_PRINTF1(LOW,
                  "sns_sam_prep_algo_report_ind: service num %d",
                  msgHdrPtr->svc_num);

   if (msgHdrPtr->svc_num == SNS_SAM_MODEM_SCN_SVC_ID_V01)
   {
      sns_sam_modem_scn_report_ind_msg_v01 *msgPtr;
      modem_scn_output_s *outPtr = (modem_scn_output_s*)(algoRptPtr->memPtr);

      if (!outPtr->do_report)
      {
         return SNS_ERR_WOULDBLOCK;
      }
      else
      {
         SNS_SAM_PRINTF2(LOW,
                        "Modem scn req_module %d, DSPS module %d",
                        clientReqPtr->reqModule, SNS_SAM_MODULE);
         if (clientReqPtr->reqModule == 0)
         {
            SNS_SAM_PRINTF2(LOW,
                           "Sending modem scenario directly %d, %d",
                           0, 0);
            /* This algo instance was instantiated by the SAM itself, we need
               not send a report indication, instead send an update directly
               to the modem. This saves on a QMI roundtrip.
            */
            sns_sam_send_modem_scenario(outPtr->scn);
            return SNS_ERR_WOULDBLOCK;
         }
         else
         {
            /* This algo instance has been used by some other client, report
               response just as other algorithms.
            */
            SNS_SAM_PRINTF2(LOW,
                           "Sending modem scenario throught SAM %d, %d",
                           0, 0);
            msgPtr = sns_smr_msg_alloc(SNS_SAM_DBG_MOD,sizeof(sns_sam_modem_scn_report_ind_msg_v01));
            SNS_ASSERT(msgPtr != NULL);

            msgPtr->instance_id = clientReqPtr->algoInstId;
            msgPtr->timestamp = algoRptPtr->timestamp;
            msgPtr->scenario  = outPtr->scn;

            msgHdrPtr->body_len = sizeof(sns_sam_modem_scn_report_ind_msg_v01);
            sns_smr_set_hdr(msgHdrPtr, msgPtr);
            *clientIndMsgPtr = msgPtr;
         }
      }
   }

#ifdef FEATURE_SNS_SAM_TILT
   else if (SNS_SAM_INTEG_ANGLE_SVC_ID_V01 == (msgHdrPtr->svc_num))
   {
      sns_sam_integ_angle_report_ind_msg_v01 *msgPtr;
      integ_angle_output_struct * algoOutPtr =
                              (integ_angle_output_struct *)(algoRptPtr->memPtr);

      //Tilt report is always sent to the client

      msgPtr = sns_smr_msg_alloc(SNS_SAM_DBG_MOD,
                               sizeof(sns_sam_integ_angle_report_ind_msg_v01));
      if (msgPtr == NULL) {
        if (msgHdrPtr->priority == SNS_SMR_MSG_PRI_LOW)
        {
          SNS_SAM_DEBUG0( ERROR, DBG_SAM_ALLOC_ERR );
          return SNS_ERR_NOMEM;
        }
        else
        {
          SNS_ASSERT(msgPtr != NULL);
        }
      }

      msgPtr->instance_id = clientReqPtr->algoInstId;
      msgPtr->timestamp = algoOutPtr->ts;

      msgHdrPtr->body_len = sizeof(sns_sam_integ_angle_report_ind_msg_v01);
      msgHdrPtr->msg_id = SNS_SAM_INTEG_ANGLE_REPORT_IND_V01;
      msgPtr->angle[0]    = algoOutPtr->angle_change[0];
      msgPtr->angle[1]    = algoOutPtr->angle_change[1];
      msgPtr->angle[2]    = algoOutPtr->angle_change[2];

      sns_smr_set_hdr(msgHdrPtr, msgPtr);

      /* log the tilt report */
      //sns_sam_log_integ_angle_report(clientReqPtr, msgPtr);
      *clientIndMsgPtr = msgPtr;
   }
#endif /* FEATURE_SNS_SAM_TILT */

   return SNS_SUCCESS;
}

/*=========================================================================
  FUNCTION:  sns_sam_create_batch_item
  =========================================================================*/
/*!
  @brief Create a batch item to buffer

  @param[i] clientReqPtr: pointer to client request
  @param[i] algoRptPtr: pointer to algorithm report
  @param[o] batchItemPtr: pointer to batch item

  @return None
*/
/*=======================================================================*/
void sns_sam_create_batch_item(
   const sns_sam_client_req_s* clientReqPtr,
   const sns_sam_algo_rpt_s *algoRptPtr,
   void** batchItemPtr)
{
    return;
}

/*=========================================================================
  FUNCTION:  sns_sam_send_algo_batch_ind
  =========================================================================*/
/*!
  @brief Prepare and send an algorithm batch indication to client

  @param[i] clientReqPtr: pointer to client request

  @return None
*/
/*=======================================================================*/
void sns_sam_send_algo_batch_ind(
   const sns_sam_client_req_s *clientReqPtr)
{
   sns_sam_algo_inst_s * algoInstPtr = NULL;
   uint8_t serviceId;
   sns_smr_header_s msgHdr;
   int numItems;

   if( !clientReqPtr || !clientReqPtr->batchInfo )
   {
      SNS_SAM_PRINTF0(ERROR, "SAM: Bad client request pointer");
      return;
   }

   algoInstPtr = sns_sam_get_algo_inst_handle(clientReqPtr->algoInstId);
   if( !algoInstPtr )
   {
      SNS_SAM_PRINTF0(ERROR, "SAM: Bad algo inst pointer");
      return;
   }

   serviceId = algoInstPtr->serviceId;
   numItems = sns_circ_buffer_get_count( clientReqPtr->batchInfo->reportBuffer );

   if( !numItems )
   {
      SNS_SAM_PRINTF0(LOW, "SAM: No items in circ buffer");
      return;
   }

   //generate message header
   SNS_OS_MEMZERO(&msgHdr, sizeof(sns_smr_header_s));
   msgHdr.dst_module = clientReqPtr->reqModule;
   msgHdr.src_module = SNS_SAM_MODULE;
   msgHdr.svc_num = serviceId;
   msgHdr.msg_type = SNS_SMR_MSG_TYPE_IND;
   msgHdr.priority = SNS_SMR_MSG_PRI_HIGH;
   msgHdr.txn_id = 0;
   msgHdr.ext_clnt_id = sns_sam_mr_get_client_id(clientReqPtr->mrClientId);
   msgHdr.msg_id = SNS_SAM_ALGO_BATCH_IND;

   // Send all pending batch indications when sending any indication
   sns_sam_send_pending_batch_inds( clientReqPtr->notify_suspend.proc_type );
}

/*=========================================================================
  FUNCTION:  sns_sam_prep_algo_error_ind
  =========================================================================*/
/*!
  @brief Prepare an algorithm error indication to client

  @param[i] algoInstId: algorithm instance id
  @param[i] error: error code
  @param[io] msgHdrPtr: pointer to client request message header

  @return None
*/
/*=======================================================================*/
void sns_sam_prep_algo_error_ind(
   uint8_t algoInstId,
   uint8_t error,
   sns_smr_header_s* msgHdrPtr,
   void** msgIndPtr)
{
   SNS_SAM_PRINTF2(LOW,
                   "sns_sam_prep_algo_error_ind: service num %d  error %d",
                   msgHdrPtr->svc_num, error);

   if (msgHdrPtr->svc_num == SNS_SAM_MODEM_SCN_SVC_ID_V01)
   {
      sns_sam_modem_scn_error_ind_msg_v01 *msgPtr =
         sns_smr_msg_alloc(SNS_SAM_DBG_MOD,sizeof(sns_sam_modem_scn_error_ind_msg_v01));
      SNS_ASSERT(msgPtr != NULL);

      msgPtr->error = error;
      msgPtr->instance_id = algoInstId;

      msgHdrPtr->body_len = sizeof(sns_sam_modem_scn_error_ind_msg_v01);

      sns_smr_set_hdr(msgHdrPtr, msgPtr);
      *msgIndPtr = msgPtr;
   }

#ifdef FEATURE_SNS_SAM_TILT
   else if (SNS_SAM_INTEG_ANGLE_SVC_ID_V01 == (msgHdrPtr->svc_num))
   {
      sns_sam_integ_angle_error_ind_msg_v01 *msgPtr =
         sns_smr_msg_alloc(SNS_SAM_DBG_MOD, sizeof(sns_sam_integ_angle_error_ind_msg_v01));
      if (msgPtr == NULL) {
        if (msgHdrPtr->priority == SNS_SMR_MSG_PRI_LOW)
        {
          SNS_SAM_DEBUG0( ERROR, DBG_SAM_ALLOC_ERR );
          return;
        }
        else
        {
          SNS_ASSERT(msgPtr != NULL);
        }
      }

      msgPtr->error = error;
      msgPtr->instance_id = algoInstId;

      msgHdrPtr->body_len = sizeof(sns_sam_integ_angle_error_ind_msg_v01);

      sns_smr_set_hdr(msgHdrPtr, msgPtr);
      *msgIndPtr = msgPtr;
   }
#endif /* FEATURE_SNS_SAM_TILT */

}

/*=========================================================================
  FUNCTION:  sns_sam_get_request_suspend_notif_info
  =========================================================================*/
/*!
  @brief Get information about processor type and about sending indications
         during suspend that is passed in by the client.

  @param[i] algoSvcId: algorithm service id
  @param[i] clientReqMsgPtr: pointer to client request message
  @param[o] procType: processor type
  @param[o] notifySuspend: if indications should be sent during suspend.

  @return Processor type information
*/
/*=======================================================================*/
void sns_sam_get_request_suspend_notif_info(
   uint8_t algoSvcId,
   const void* clientReqMsgPtr,
   uint32_t* procType,
   bool* notifySuspend)
{
  /* set default behavior if the client does not specify */
  /* default behavior is to not wakeup Apps from suspend for indications */
  *procType = SNS_PROC_APPS_V01;
  *notifySuspend = false;

  return;
}

/*=========================================================================
  FUNCTION:  sns_sam_validate_algo_report_period
  =========================================================================*/
/*!
  @brief Validate the requested algorithm report period

  @param[i] algoSvcId: algorithm service id
  @param[i] clientReqMsgPtr: pointer to client request message

  @return SNS_SUCCESS, if requested report period is supported
          SNS_ERR_BAD_PARM, otherwise
*/
/*=======================================================================*/
static sns_err_code_e sns_sam_validate_algo_report_period(
   uint8_t algoSvcId,
   const void* clientReqMsgPtr)
{
   uint32_t reportPeriod = 0;

   if (NULL == clientReqMsgPtr)
   {
      return SNS_ERR_BAD_PARM;
   }

   if (NULL == sns_sam_algo_dbase_acc(sns_sam_get_algo_index(algoSvcId)))
   {
      return SNS_ERR_BAD_PARM;
   }

   SNS_SAM_PRINTF1(LOW, "sns_sam_validate_algo_report_period: algo service id %d",
                   algoSvcId);

   switch(algoSvcId)
   {
#ifdef FEATURE_SNS_SAM_TILT
      case SNS_SAM_INTEG_ANGLE_SVC_ID_V01:
      {
         reportPeriod =
            ((sns_sam_integ_angle_enable_req_msg_v01 *)clientReqMsgPtr)->report_period;
         break;
      }
#endif /* FEATURE_SNS_SAM_TILT */
      default:
         break;
   }

   // Range check
   if( reportPeriod != 0 )
   {
      uint8_t algoIndex = sns_sam_get_algo_index(algoSvcId);
      float minReportRate = (float)FX_FIXTOFLT_Q16(sns_sam_algo_dbase_acc(algoIndex)->min_report_rate);
      float maxReportRate = (float)FX_FIXTOFLT_Q16(sns_sam_algo_dbase_acc(algoIndex)->max_report_rate);
      uint32_t minReportPeriod = FX_FLTTOFIX_Q16(1.0f/maxReportRate);
      uint32_t maxReportPeriod = FX_FLTTOFIX_Q16(1.0f/minReportRate);

      SNS_SAM_PRINTF3(LOW,"reportPeriod:%d, minReportPeriod:%d, maxReportPeriod:%d",reportPeriod,minReportPeriod,maxReportPeriod);
      if( reportPeriod < minReportPeriod || reportPeriod > maxReportPeriod )
      {
         return SNS_ERR_BAD_PARM;
      }
   }

   return SNS_SUCCESS;
}

/*=========================================================================
  FUNCTION:  sns_sam_validate_algo_sample_rate
  =========================================================================*/
/*!
  @brief Validate the requested algorithm sample rate

  @param[i] algoSvcId: algorithm service id
  @param[i] clientReqMsgPtr: pointer to client request message

  @return SNS_SUCCESS, if requested sample rate is supported
          SNS_ERR_BAD_PARM, otherwise
*/
/*=======================================================================*/
static sns_err_code_e sns_sam_validate_algo_sample_rate(
   uint8_t algoSvcId,
   const void* clientReqMsgPtr)
{
   uint32_t sampleRate = 0;

   if (NULL == clientReqMsgPtr)
   {
      return SNS_ERR_BAD_PARM;
   }

   if (NULL == sns_sam_algo_dbase_acc(sns_sam_get_algo_index(algoSvcId)))
   {
      return SNS_ERR_BAD_PARM;
   }

   SNS_SAM_PRINTF1(LOW, "sns_sam_validate_algo_sample_rate: algo service id %d",
                   algoSvcId);

   switch (algoSvcId)
   {
#ifdef FEATURE_SNS_SAM_TILT
      case SNS_SAM_INTEG_ANGLE_SVC_ID_V01:
      {
         sns_sam_integ_angle_enable_req_msg_v01 *enable_ptr =
           (sns_sam_integ_angle_enable_req_msg_v01 *)clientReqMsgPtr;
         if (enable_ptr->sample_rate_valid)
         {
            sampleRate = enable_ptr->sample_rate;
         }
         break;
      }
#endif /* FEATURE_SNS_SAM_TILT */

      default:
         break;
   }  /* End switch */

   // Range check
   if( sampleRate != 0 )
   {
      uint8_t algoIndex = sns_sam_get_algo_index(algoSvcId);
      uint32_t minSampleRate = sns_sam_algo_dbase_acc(algoIndex)->min_sample_rate;
      uint32_t maxSampleRate = sns_sam_algo_dbase_acc(algoIndex)->max_sample_rate;

      SNS_SAM_PRINTF3(LOW,"sampleRate:%d, minSampleRate:%d, maxSampleRate:%d",sampleRate,minSampleRate,maxSampleRate);
      if( sampleRate < minSampleRate || sampleRate > maxSampleRate )
      {
         return SNS_ERR_BAD_PARM;
      }
   }

   return SNS_SUCCESS;
}

/*=========================================================================
  FUNCTION:  sns_sam_get_algo_report_period
  =========================================================================*/
/*!
  @brief Get the algorithm report period

  @param[i] algoSvcId: algorithm service id
  @param[i] clientReqMsgPtr: pointer to client request message
  @param[i] algoCfgPtr: pointer to algorithm configuration

  @return Algorithm report period. 0 if report is not periodic OR
          algorithm not supported
*/
/*=======================================================================*/
uint32_t sns_sam_get_algo_report_period(
   uint8_t algoSvcId,
   const void* clientReqMsgPtr,
   const void* algoCfgPtr)
{
   uint32_t reportPeriod = 0, sampleRate = 0;

   if (NULL == clientReqMsgPtr || NULL == algoCfgPtr)
   {
      return SNS_SAM_INVALID_PERIOD;
   }
   SNS_SAM_PRINTF1(LOW, "sns_sam_get_algo_report_period: algo service id %d",
                   algoSvcId);

   switch(algoSvcId)
   {
#ifdef FEATURE_SNS_SAM_TILT
      case SNS_SAM_INTEG_ANGLE_SVC_ID_V01:
      {
         reportPeriod =
            ((sns_sam_integ_angle_enable_req_msg_v01 *)clientReqMsgPtr)->report_period;
         sampleRate = ((integ_angle_config_struct *)algoCfgPtr)->sample_rate;
         break;
      }
#endif /* FEATURE_SNS_SAM_TILT */
      default:
         break;
   }

   if (sampleRate > 0)
   {
      float samplePer = (float)(1. / FX_FIXTOFLT_Q16(sampleRate));
      float reportPer = (float)FX_FIXTOFLT_Q16(reportPeriod);

      //sample period will be less than or equal to report period
      //check for sync reporting
      if (reportPer - samplePer < .001)
      {
         reportPeriod = 0;
      }

      if (reportPeriod == 0)
      {
         return reportPeriod;
      }
   }
   SNS_SAM_PRINTF2(LOW, "sns_sam_get_algo_report_period: algo service id %d, report period %d",
                   algoSvcId, reportPeriod);

   if (reportPeriod == SNS_SAM_INVALID_PERIOD)
   {
      return reportPeriod;
   }
   else
   {
      return (sns_em_convert_sec_in_q16_to_localtick(reportPeriod));
   }
}

/*=========================================================================
  FUNCTION:  sns_sam_get_sensor_buf_req
  =========================================================================*/
/*!
  @brief Gets sensor data requirements for algorithm

  @param[i] algoSvcId: algorithm service id
  @param[i] algoCfgPtr: pointer to algorithm configuration
  @param[o] dataReq: sensor data required by algorithm

  @return None
*/
/*=======================================================================*/
static void sns_sam_get_sensor_buf_req(
   uint8_t algoSvcId,
   void *algoCfgPtr,
   sns_sam_data_req_s *dataReq)
{
   return;
}

/*=========================================================================
  FUNCTION:  sns_sam_get_sensor_samp_req
  =========================================================================*/
/*!
  @brief Gets sensor data requirements for algorithm

  @param[i] algoSvcId: algorithm service id
  @param[i] algoCfgPtr: pointer to algorithm configuration
  @param[o] dataReq: sensor data required by algorithm

  @return None
*/
/*=======================================================================*/
static void sns_sam_get_sensor_samp_req(
   uint8_t algoSvcId,
   void *algoCfgPtr,
   sns_sam_data_req_s *dataReq)
{
   if( !dataReq )
   {
      SNS_SAM_PRINTF0(ERROR,"sns_sam_get_sensor_samp_req: Bad data req pointer");
      return;
   }

   switch (algoSvcId)
   {
      case SNS_SAM_MODEM_SCN_SVC_ID_V01:
      {
         modem_scn_config_s *cfgPtr = (modem_scn_config_s *)algoCfgPtr;
         dataReq->reportRate = FX_CONV(cfgPtr->sample_rate, 16, 0);  /* convert to Hz */
         dataReq->sensorCount = 1;
         dataReq->sensorDbase[0].sensorId = SNS_SMGR_ID_PROX_LIGHT_V01;
         dataReq->sensorDbase[0].dataType = SNS_SMGR_DATA_TYPE_PRIMARY_V01;
         break;
      }
#ifdef FEATURE_SNS_SAM_TILT
      case SNS_SAM_INTEG_ANGLE_SVC_ID_V01:
      {
         integ_angle_config_struct *cfgPtr = (integ_angle_config_struct *)algoCfgPtr;
         dataReq->reportRate = FX_CONV(cfgPtr->sample_rate, 16, 0);  /* convert to Hz */
         dataReq->sensorCount = 1;
         dataReq->sensorDbase[0].sensorId = SNS_SMGR_ID_GYRO_V01;
         dataReq->sensorDbase[0].dataType = SNS_SMGR_DATA_TYPE_PRIMARY_V01;
         break;
      }
#endif /* FEATURE_SNS_SAM_TILT */
      default:
         break;
   }
}

/*=========================================================================
  FUNCTION:  sns_sam_get_sensor_requirements
  =========================================================================*/
/*!
  @brief Gets sensor data requirements for algorithm

  @param[i] algoSvcId: algorithm service id
  @param[i] algoCfgPtr: pointer to algorithm configuration
  @param[o] dataReq: sensor data required by algorithm

  @return None
*/
/*=======================================================================*/
void sns_sam_get_sensor_requirements(
   uint8_t algoSvcId,
   void *algoCfgPtr,
   sns_sam_data_req_s *dataReq)
{
   uint32_t i, j;

   if( !dataReq )
   {
      SNS_SAM_PRINTF0(ERROR,"sns_sam_get_sensor_requirements: Bad data req pointer");
      return;
   }

   for( i = 0; i < SNS_SAM_MAX_SENSORS_PER_DATA_REQ; i++ )
   {
      dataReq->sensorDbase[i].sampleRate = SNS_SAM_INVALID_SAMPLE_RATE;
      dataReq->sensorDbase[i].sampleQual = SNS_SAM_DEFAULT_SAMPLE_QUALITY;
      dataReq->sensorDbase[i].algoInstCount = 0;

      for(j = 0; j < SNS_SAM_MAX_ALGO_INSTS_PER_SENSOR; j++)
      {
         dataReq->sensorDbase[i].algoInstIds[j] = SNS_SAM_INVALID_ID;
      }
   }

   dataReq->reportRate = 0;
   dataReq->sensorCount = 0;
   dataReq->algoInstCount = 0;
   dataReq->registerMDInterrupt = false;

   if (sns_sam_get_smgr_msg_req_type(algoSvcId) == SNS_SMGR_BUFFERING_REQ_V01)
   {
      sns_sam_get_sensor_buf_req(algoSvcId, algoCfgPtr, dataReq);
   }
   else
   {
      sns_sam_get_sensor_samp_req(algoSvcId, algoCfgPtr, dataReq);
   }
}

/*=========================================================================
  FUNCTION:  sns_sam_send_algo_report_req
  =========================================================================*/
/*!
  @brief Sends a report request to the desired module

  @param[i] algoInstId: algorithm instance ID
  @param[i] algoInstPtr: pointer to algorithm instance
  @param[i] clientReqMsgPtr: pointer to client request message

  @return   error code
*/
/*=======================================================================*/
sns_err_code_e sns_sam_send_algo_report_req(
   uint8_t                            algoInstId,
   const sns_sam_algo_inst_s          *algoInstPtr,
   const void                         *clientReqMsgPtr)
{
  /* Empty Stub; do nothing */
  return SNS_SUCCESS;
}

/*=========================================================================
  FUNCTION:  sns_sam_prep_algo_enable_resp
  =========================================================================*/
/*!
  @brief Send response to algorithm enable request

  @param[i] algoInstId: algorithm instance id
  @param[i] algoSvcId: algorithm service id
  @param[i] clientReqMsgPtr: pointer to client request message
  @param[o] clientRespMsgPtr: Pointer to the response message created.

  @return Sensors error code
*/
/*=======================================================================*/
sns_err_code_e sns_sam_prep_algo_enable_resp(
   uint8_t algoInstId,
   uint8_t algoSvcId,
   const void* clientReqMsgPtr,
   void** clientRespMsgPtr)
{
       SNS_SAM_PRINTF2(LOW,
                      "sns_sam_prep_algo_enable_resp: algo inst %d, algo svc %d",
                      algoInstId, algoSvcId);

   if (algoSvcId == SNS_SAM_MODEM_SCN_SVC_ID_V01)
   {
      sns_sam_modem_scn_enable_resp_msg_v01 *enableRespMsgPtr =
         sns_smr_msg_alloc(SNS_SAM_DBG_MOD,sizeof(sns_sam_modem_scn_enable_resp_msg_v01));
      SNS_ASSERT(enableRespMsgPtr != NULL);

      enableRespMsgPtr->resp.sns_result_t = SNS_RESULT_SUCCESS_V01;
      enableRespMsgPtr->resp.sns_err_t = SNS_SUCCESS;
      enableRespMsgPtr->instance_id_valid = 1;
      enableRespMsgPtr->instance_id = algoInstId;
      sns_sam_prep_resp_msg(clientReqMsgPtr,
                            enableRespMsgPtr,
                            sizeof(sns_sam_modem_scn_enable_resp_msg_v01));
      *clientRespMsgPtr = enableRespMsgPtr;
      return SNS_SUCCESS;
   }
#ifdef FEATURE_SNS_SAM_TILT
   else if (SNS_SAM_INTEG_ANGLE_SVC_ID_V01  == algoSvcId)
   {
      sns_sam_integ_angle_enable_resp_msg_v01 *enableRespMsgPtr =
         sns_smr_msg_alloc(SNS_SAM_DBG_MOD, sizeof(sns_sam_integ_angle_enable_resp_msg_v01));
      SNS_ASSERT(enableRespMsgPtr != NULL);

      enableRespMsgPtr->resp.sns_result_t = SNS_RESULT_SUCCESS_V01;
      enableRespMsgPtr->resp.sns_err_t = SNS_SUCCESS;
      enableRespMsgPtr->instance_id_valid = true;
      enableRespMsgPtr->instance_id = algoInstId;
      sns_sam_prep_resp_msg(clientReqMsgPtr,
                            enableRespMsgPtr,
                            sizeof(sns_sam_integ_angle_enable_resp_msg_v01));
      *clientRespMsgPtr = enableRespMsgPtr;
      return SNS_SUCCESS;
   }
#endif /* FEATURE_SNS_SAM_TILT */
   else
   {
      return SNS_ERR_BAD_PARM;
   }
}

/*=========================================================================
  FUNCTION:  sns_sam_prep_algo_disable_resp
  =========================================================================*/
/*!
  @brief Prepare a response to algorithm disable request

  @param[i] algoInstId: algorithm instance id
  @param[i] algoSvcId: algorithm service id
  @param[i] clientReqMsgPtr: pointer to client request message
  @param[o] clientRespMsgPtr: Pointer to the response message created.

  @return Sensors error code
*/
/*=======================================================================*/
sns_err_code_e sns_sam_prep_algo_disable_resp(
   uint8_t algoInstId,
   uint8_t algoSvcId,
   const void* clientReqMsgPtr,
   void** clientRespMsgPtr)
{
   *clientRespMsgPtr = NULL;

   SNS_SAM_PRINTF2(LOW,
                  "sns_sam_prep_algo_disable_resp: algo inst %d, algo svc %d",
                  algoInstId, algoSvcId);

   if (algoSvcId == SNS_SAM_MODEM_SCN_SVC_ID_V01)
   {
      sns_sam_modem_scn_disable_req_msg_v01 *disableReqMsgPtr =
         (sns_sam_modem_scn_disable_req_msg_v01 *)clientReqMsgPtr;
      sns_sam_modem_scn_disable_resp_msg_v01 *disableRespMsgPtr;

      if (algoInstId != disableReqMsgPtr->instance_id)
      {
         SNS_SAM_DEBUG2(ERROR, DBG_SAM_PROCESS_REQ_DISABLE_ERR,
                        disableReqMsgPtr->instance_id, algoInstId);
         return SNS_ERR_BAD_PARM;
      }

      disableRespMsgPtr = sns_smr_msg_alloc(SNS_SAM_DBG_MOD,sizeof(sns_sam_modem_scn_disable_resp_msg_v01));
      SNS_ASSERT(disableRespMsgPtr != NULL);

      disableRespMsgPtr->resp.sns_result_t = SNS_RESULT_SUCCESS_V01;
      disableRespMsgPtr->resp.sns_err_t = SNS_SUCCESS;
      disableRespMsgPtr->instance_id_valid = 1;
      disableRespMsgPtr->instance_id = algoInstId;
      sns_sam_prep_resp_msg(clientReqMsgPtr,
                            disableRespMsgPtr,
                            sizeof(sns_sam_modem_scn_disable_resp_msg_v01));
      *clientRespMsgPtr = disableRespMsgPtr;
      return SNS_SUCCESS;
   }

#ifdef FEATURE_SNS_SAM_TILT
   else if (SNS_SAM_INTEG_ANGLE_SVC_ID_V01 == algoSvcId)
   {
      sns_sam_integ_angle_disable_req_msg_v01 *disableReqPtr =
         (sns_sam_integ_angle_disable_req_msg_v01 *)clientReqMsgPtr;
      sns_sam_integ_angle_disable_resp_msg_v01 *disableRespMsgPtr;

      if (algoInstId != disableReqPtr->instance_id)
      {
         SNS_SAM_DEBUG2(ERROR, DBG_SAM_PROCESS_REQ_DISABLE_ERR,
                        disableReqPtr->instance_id, algoInstId);
         return SNS_ERR_BAD_PARM;
      }

      disableRespMsgPtr = sns_smr_msg_alloc(SNS_SAM_DBG_MOD, sizeof(sns_sam_integ_angle_disable_resp_msg_v01));
      SNS_ASSERT(disableRespMsgPtr != NULL);

      disableRespMsgPtr->resp.sns_result_t = SNS_RESULT_SUCCESS_V01;
      disableRespMsgPtr->resp.sns_err_t = SNS_SUCCESS;
      disableRespMsgPtr->instance_id_valid = true;
      disableRespMsgPtr->instance_id = algoInstId;
      sns_sam_prep_resp_msg(clientReqMsgPtr,
                            disableRespMsgPtr,
                            sizeof(sns_sam_integ_angle_disable_resp_msg_v01));
      *clientRespMsgPtr = disableRespMsgPtr;
      return SNS_SUCCESS;
   }
#endif /* FEATURE_SNS_SAM_TILT */
   else
   {
      return SNS_ERR_BAD_PARM;
   }
}

/*=========================================================================
  FUNCTION:  sns_sam_prep_algo_report_resp
  =========================================================================*/
/*!
  @brief Prepare a response to algorithm enable request

  @param[i] clientReqPtr: pointer to client request
  @param[i] clientReqMsgPtr: pointer to client request message
  @param[o] clientRespMsgPtr: Pointer to the response message created.
  @param[i] algoSvcId: algorithm service id

  @return Sensors error code
*/
/*=======================================================================*/
sns_err_code_e sns_sam_prep_algo_report_resp(
   const sns_sam_client_req_s* clientReqPtr,
   const void* clientReqMsgPtr,
   void** clientRespMsgPtr,
   uint8_t algoSvcId)
{
   sns_sam_algo_rpt_s *algoRptPtr;

   uint8_t algoInstId = clientReqPtr->algoInstId;
   *clientRespMsgPtr = NULL;

   SNS_SAM_PRINTF2(LOW,
                  "sns_sam_prep_algo_report_resp: client %d, algo service %d",
                  clientReqPtr->mrClientId, algoSvcId);

   if (algoSvcId == SNS_SAM_MODEM_SCN_SVC_ID_V01)
   {
      modem_scn_output_s *rptPtr;

      sns_sam_modem_scn_get_report_resp_msg_v01 *reportRespMsgPtr;
      sns_sam_modem_scn_get_report_req_msg_v01 *reportReqPtr =
         (sns_sam_modem_scn_get_report_req_msg_v01 *)clientReqMsgPtr;

      algoInstId = reportReqPtr->instance_id;

      // get report
      algoRptPtr = sns_sam_get_algo_report(algoInstId);
      if(algoRptPtr == NULL)
      {
         return SNS_ERR_FAILED;
      }
      rptPtr = (modem_scn_output_s *)(algoRptPtr->memPtr);

      reportRespMsgPtr =
         sns_smr_msg_alloc(SNS_SAM_DBG_MOD,sizeof(sns_sam_modem_scn_get_report_resp_msg_v01));
      SNS_ASSERT(reportRespMsgPtr != NULL);

      reportRespMsgPtr->resp.sns_result_t = SNS_RESULT_SUCCESS_V01;
      reportRespMsgPtr->resp.sns_err_t = SNS_SUCCESS;
      reportRespMsgPtr->instance_id_valid = 1;
      reportRespMsgPtr->instance_id = algoInstId;
      reportRespMsgPtr->timestamp_valid = 1;
      reportRespMsgPtr->timestamp = algoRptPtr->timestamp;
      reportRespMsgPtr->scenario_valid = 1;
      reportRespMsgPtr->scenario = rptPtr->scn;

      //send algo report response to client
      sns_sam_prep_resp_msg(clientReqMsgPtr,
                            reportRespMsgPtr,
                            sizeof(sns_sam_modem_scn_get_report_resp_msg_v01));
      *clientRespMsgPtr = reportRespMsgPtr;
      return SNS_SUCCESS;
   }

   else
   {
      return SNS_ERR_BAD_PARM;
   }
}

/*=========================================================================
  FUNCTION:  sns_sam_prep_algo_update_resp
  =========================================================================*/
/*!
  @brief Send response to algorithm update request

  @param[i] clientReqMsgPtr: pointer to client request message
  @param[o] clientRespMsgPtr: Pointer to the response message created.
  @param[i] algoSvcId: algorithm service id

  @return Sensors error code
*/
/*=======================================================================*/
sns_err_code_e sns_sam_prep_algo_update_resp(
   const void* clientReqMsgPtr,
   void** clientRespMsgPtr,
   uint8_t algoSvcId)
{
   return SNS_ERR_BAD_PARM;
}

/*=========================================================================
  FUNCTION:  sns_sam_prep_algo_batch_resp
  =========================================================================*/
/*!
  @brief Prepare response to algorithm batch request

  @param[i] clientReqMsgPtr: pointer to client request message
  @param[o] clientRespMsgPtr: Pointer to the response message created
  @param[i] algoPtr: pointer to algorithm structure

  @return Sensors error code
*/
/*=======================================================================*/
sns_err_code_e sns_sam_prep_algo_batch_resp(
   const void* clientReqMsgPtr,
   void** clientRespMsgPtr,
   sns_sam_algo_s* algoPtr)
{
   if( !algoPtr )
   {
      SNS_SAM_PRINTF0(ERROR, "sns_sam_prep_algo_batch_resp: Invalid algo ptr");
      return SNS_ERR_BAD_PTR;
   }

   return SNS_ERR_NOTSUPPORTED;
}

/*=========================================================================
  FUNCTION:  sns_sam_prep_algo_upd_batch_period_resp
  =========================================================================*/
/*!
  @brief Send response to algorithm update batch period request

  @param[i] clientReqMsgPtr: pointer to client request message
  @param[o] clientRespMsgPtr: Pointer to the response message created
  @param[i] algoSvcId: algorithm service id

  @return Sensors error code
*/
/*=======================================================================*/
sns_err_code_e sns_sam_prep_algo_upd_batch_period_resp(
   const void* clientReqMsgPtr,
   void** clientRespMsgPtr,
   uint8_t algoSvcId)
{
   return SNS_ERR_NOTSUPPORTED;
}

/*=========================================================================
  FUNCTION:  sns_sam_process_client_duty_cycle_req
  =========================================================================*/
/*!
  @brief
  enables specified algorithm with the specified configuration

  @param[i] algoSvcId: algorithm service Id
  @param[i] clientReqMsgPtr: pointer to client request message

  @return dutycycleOnPercent: On Percentage requested
*/
/*=======================================================================*/
uint8_t sns_sam_process_client_duty_cycle_req(
   uint8_t algoSvcId,
   const void *clientReqMsgPtr)
{
   return 100;
}

/*=========================================================================
  FUNCTION:  sns_sam_log_algo_config
  =========================================================================*/
/*!
  @brief Log algorithm configuration

  @param[i] algoInstId: algorithm instance id
  @param[i] algoInstPtr: pointer to algorithm instance
  @param[i] algoIndex: index to algorithm in the algorithm database

  @return None
*/
/*=======================================================================*/
void sns_sam_log_algo_config(
   uint8_t algoInstId,
   const sns_sam_algo_inst_s* algoInstPtr,
   uint8_t algoIndex)
{
   SNS_SAM_PRINTF2(LOW,
                   "sns_sam_log_algo_config: algo instance %d, algo service %d",
                   algoInstId, algoInstPtr->serviceId);
   switch (algoInstPtr->serviceId)
   {
#ifdef FEATURE_SNS_SAM_TILT
      case SNS_SAM_INTEG_ANGLE_SVC_ID_V01:
        //sns_sam_log_integ_angle_config(algoInstId, algoInstPtr);
         break;
#endif /* FEATURE_SNS_SAM_TILT */

      default:
         break;
   }
}

/*=========================================================================
  FUNCTION:  sns_sam_log_algo_result
  =========================================================================*/
/*!
  @brief Log algorithm result

  @param[i] algoInstId: algorithm instance id
  @param[i] algoInstPtr: pointer to algorithm instance
  @param[i] clientId: Client id

  @return None
*/
/*=======================================================================*/
void sns_sam_log_algo_result(
   uint8_t algoInstId,
   const sns_sam_algo_inst_s* algoInstPtr,
   uint8_t clientId)
{
   sns_err_code_e err = SNS_SUCCESS;

       switch (algoInstPtr->serviceId)
       {
#ifdef FEATURE_SNS_SAM_TILT
       case SNS_SAM_INTEG_ANGLE_SVC_ID_V01:
          //err = sns_sam_log_integ_angle_result( algoInstId, algoInstPtr);
          break;
#endif /* FEATURE_SNS_SAM_TILT */

       default:
          err = SNS_ERR_FAILED;
          break;
       }

   SNS_SAM_PRINTF3(LOW,
      "sns_sam_log_algo_result: algo instance %d, algo service %d, err %d",
      algoInstId, algoInstPtr->serviceId, err);
}

/*=========================================================================
  FUNCTION:  sns_sam_log_dep_algo_result
  =========================================================================*/
/*!
  @brief Log dependent algorithm result

  @param[i] algoInstId: algorithm instance id
  @param[i] algoInstPtr: pointer to algorithm instance

  @return None
*/
/*=======================================================================*/
void sns_sam_log_dep_algo_result(
   uint8_t algoInstId,
   const sns_sam_algo_inst_s* algoInstPtr)
{
   sns_err_code_e err = SNS_ERR_FAILED;

   SNS_SAM_PRINTF2(LOW,
     "sns_sam_log_dep_algo_result: algo instance %d, algo service %d",
     algoInstId, algoInstPtr->serviceId);

   if (err != SNS_SUCCESS) {
      SNS_SAM_PRINTF1(MED, "sns_sam_log_dep_algo_result: %d", err);
   }
}

/*=========================================================================
  FUNCTION:  sns_sam_update_algo_config
  =========================================================================*/
/*!
  @brief Update algorithm configuration per client specification

  @param[i] algoSvcId: algorithm service Id
  @param[i] clientReqMsgPtr: pointer to client request message
  @param[io] algoCfgPtr: pointer to algorithm configuration
  @return None
*/
/*=======================================================================*/
void sns_sam_update_algo_config(
   uint8_t algoSvcId,
   const void* clientReqMsgPtr,
   void *algoCfgPtr)
{
   int32_t* sampleRatePtr = NULL;
   uint32_t reportPeriod = 0;

   if (NULL == clientReqMsgPtr || NULL == algoCfgPtr)
   {
      return;
   }

   switch (algoSvcId)
   {
#ifdef FEATURE_SNS_SAM_TILT
      case SNS_SAM_INTEG_ANGLE_SVC_ID_V01:
      {
         integ_angle_config_struct *cfg_ptr = (integ_angle_config_struct *)algoCfgPtr;
         sns_sam_integ_angle_enable_req_msg_v01 *enable_ptr =
           (sns_sam_integ_angle_enable_req_msg_v01 *)clientReqMsgPtr;

         if (enable_ptr->sample_rate_valid)
         {
            /* start with what is specified */
            cfg_ptr->sample_rate = enable_ptr->sample_rate;

            /* clip the sample rate */
            if (cfg_ptr->sample_rate < IA_MIN_GYRO_RATE_Q16)
            {
               cfg_ptr->sample_rate = IA_MIN_GYRO_RATE_Q16;
            }
            else
            {
               if (cfg_ptr->sample_rate > IA_MAX_GYRO_RATE_Q16)
               {
                 cfg_ptr->sample_rate = IA_MAX_GYRO_RATE_Q16;
               }
               else
               {
                 /* avoid a dangling else */
               }
            }
         }
         else
         {
            cfg_ptr->sample_rate = IA_DEF_GYRO_RATE_Q16;
         }

         /* Not that the FDD deines the clip theshrhold as configurable - but
           not exposed to the use - so - we do not apply the setting from the
           QMI message.                                                       */
         /*
         if(enable_ptr->integ_angle_angle_threshold_valid)
         {
           cfg_ptr->clip_threshold = enable_ptr->integ_angle_angle_threshold;
         }
         */

         cfg_ptr->clip_threshold = FX_IA_RES_LIMIT;
         cfg_ptr->init_ts        = sns_em_get_timestamp();

         sampleRatePtr = &(cfg_ptr->sample_rate);
         break;
      }
#endif /* FEATURE_SNS_SAM_TILT */

      case SNS_SAM_MODEM_SCN_SVC_ID_V01:
      {
         modem_scn_config_s *cfgPtr = (modem_scn_config_s *)algoCfgPtr;
         sns_sam_modem_scn_enable_req_msg_v01 *enablePtr =
                    (sns_sam_modem_scn_enable_req_msg_v01 *)clientReqMsgPtr;

         cfgPtr->sample_rate = enablePtr->sample_rate;
         cfgPtr->quiet_period = MODEM_SCN_DEF_QUIET_PERIOD;
         cfgPtr->thresh = MODEM_SCN_DEF_THRESH;
         break;
      }

      default:
         return;
   }  /* End switch */

   // if sampling rate is slower than report rate, make it match
   if (sampleRatePtr != NULL && *sampleRatePtr > 0 && reportPeriod > 0)
   {
      float sampleRate = (float)FX_FIXTOFLT_Q16(*sampleRatePtr);

      float reportRate = (float)(1. / FX_FIXTOFLT_Q16(reportPeriod));

      if (reportRate - sampleRate > .1)
      {
         *sampleRatePtr = FX_FLTTOFIX_Q16(reportRate);
      }
   }
}

/*=========================================================================
  FUNCTION:  sns_sam_update_algo_input
  =========================================================================*/
/*!
  @brief Update algorithm input structure

  @param[i] algoSvcId: algorithm service Id
  @param[i] indMsgType: indication message type
  @param[i] dataPtr: pointer to data in SMGR report indication
  @param[io] algoInpPtr: pointer to algorithm input structure
  @param[i] algoInpSize: size of algorithm input structure
  @param[i] timestamp: input timestamp
  @param[i] sensorID: SMGR Sensor ID for the indication
                      (invalid unless indMsgType==SNS_SMGR_BUFFERING_IND_V01)

  @return Sensors error code
*/
/*=======================================================================*/
sns_err_code_e sns_sam_update_algo_input(
   uint8_t    algoSvcId,
   uint8_t    indMsgType,
   const void *dataPtr,
   void       *algoInpPtr,
   uint32_t   algoInpSize,
   uint32_t   timestamp,
   uint8_t    sensorID)
{
   if( indMsgType == SNS_SMGR_BUFFERING_IND_V01 )
   {
      // Handle buffering indication
      sns_smgr_buffering_sample_s_v01 * samplePtr =
          (sns_smgr_buffering_sample_s_v01 *)dataPtr;
      uint8_t itemSize = sizeof(samplePtr->Data);

      if( sns_sam_get_smgr_msg_req_type(algoSvcId) != SNS_SMGR_BUFFERING_REQ_V01 )
      {
         // Service did not register for buffering indications
         return SNS_ERR_FAILED;
      }

      //copy sensor data to algorithm input
      if( itemSize > algoInpSize )
      {
         SNS_SAM_DEBUG2(ERROR, DBG_SAM_SMGR_IND_INVALID,
                        algoInpSize, itemSize);
         return SNS_ERR_FAILED;
      }
      SNS_OS_MEMCOPY(algoInpPtr, samplePtr->Data, itemSize);
   }
   else if( indMsgType == SNS_SMGR_REPORT_IND_V01 )
   {
      // Handle periodic report
      sns_smgr_data_item_s_v01* smgrItemPtr =
         (sns_smgr_data_item_s_v01*)dataPtr;

      /* Copies information (other than sensor data) to algorithm input */
      switch(algoSvcId)
      {
#ifdef FEATURE_SNS_SAM_TILT
         case SNS_SAM_INTEG_ANGLE_SVC_ID_V01:
         {
             integ_angle_input_struct* inpPtr = (integ_angle_input_struct *)algoInpPtr;

             if (smgrItemPtr->SensorId != SNS_SMGR_ID_GYRO_V01)
             {
                 return (SNS_ERR_FAILED);
             }

             inpPtr->ts = smgrItemPtr->TimeStamp;

             inpPtr->gyro[0] = smgrItemPtr->ItemData[0];
             inpPtr->gyro[1] = smgrItemPtr->ItemData[1];
             inpPtr->gyro[2] = smgrItemPtr->ItemData[2];

             return SNS_SUCCESS;
         }
#endif /* #ifdef FEATURE_SNS_SAM_TILT */

         case SNS_SAM_MODEM_SCN_SVC_ID_V01:
         {
            modem_scn_input_s *inPtr =  (modem_scn_input_s *)algoInpPtr;
            inPtr->timestamp =  smgrItemPtr->TimeStamp;
            inPtr->sample    = smgrItemPtr->ItemData[0];
            SNS_SAM_PRINTF3(LOW, "%d:ts %u, sample %d",
                            SNS_SAM_MODEM_SCN_SVC_ID_V01,
                            inPtr->timestamp, inPtr->sample);
             return SNS_SUCCESS;
           }

         default:
            break;
      } /* End switch(algoSvcId) */


      //copy sensor data to algorithm input
      if (algoInpSize >= sizeof(smgrItemPtr->ItemData))
      {
         SNS_OS_MEMCOPY(algoInpPtr,
                        smgrItemPtr->ItemData,
                        sizeof(smgrItemPtr->ItemData));
      }
      else
      {
         SNS_SAM_DEBUG2(ERROR, DBG_SAM_SMGR_IND_INVALID,
                        algoInpSize, sizeof(smgrItemPtr->ItemData));
         return SNS_ERR_FAILED;
      }
   }
   else
   {
      // Unknown message type
      SNS_SAM_PRINTF1(ERROR, "SAM: Unknown SMGR ind type %d", indMsgType);
      return SNS_ERR_NOTSUPPORTED;
   }
   return SNS_SUCCESS;
}

/*=========================================================================
  FUNCTION:  sns_sam_process_sam_response
  =========================================================================*/
/*!
  @brief Process the response received from another SAM module

  @param[i] samRespPtr: Pointer to the sam response message

  @return algo instance id of dependent algorithm
*/
/*=======================================================================*/
uint8_t sns_sam_process_sam_response(
   const void *samRespPtr)
{
   return SNS_SAM_INVALID_ID;
}

/*=========================================================================
  FUNCTION:  sns_sam_process_sam_report_ind
  =========================================================================*/
/*!
  @brief Process the indication received from another SAM module

  @param[i] samIndPtr: Pointer to the sam indication message
  @param[i] clientAlgoInstPtr: pointer to client algorithm instance
  @param[i] algoSvcId: algorithm service id
  @param[i] algoInstId: algorithm instance id

  @return Sensors error code
*/
/*=======================================================================*/
sns_err_code_e sns_sam_process_sam_report_ind(
   const void* samIndPtr,
   sns_sam_algo_inst_s* clientAlgoInstPtr,
   uint8_t algoSvcId,
   uint8_t algoInstId)
{
   void *dataPtr = NULL;

   switch (algoSvcId)
   {
      case SNS_SAM_MODEM_SCN_SVC_ID_V01:
      {

         SNS_SAM_PRINTF3(HIGH,
                         "Handling modem scn service indication, %d, %d, %d",
                         0, 0, 0);
         break;
      }

      default:
         return SNS_SUCCESS;
   }

   if (dataPtr != NULL)
   {
      sns_sam_algo_s* algoPtr = sns_sam_get_algo_handle(clientAlgoInstPtr->serviceId);
      if (algoPtr != NULL)
      {
         sns_profiling_log_timestamp((uint64_t) (((uint64_t)(((uint64_t)SNS_SAM_ALGO_EXEC_PROFILE_START)<<32)) |
                                                             ((uint64_t)(clientAlgoInstPtr->serviceId))));
         sns_profiling_log_qdss(SNS_SAM_ALGO_UPDATE_ENTER, 2, clientAlgoInstPtr->serviceId, algoInstId);

         algoPtr->algoApi.sns_sam_algo_update(clientAlgoInstPtr->stateData.memPtr,
            clientAlgoInstPtr->inputData.memPtr,
            clientAlgoInstPtr->outputData.memPtr);

         sns_profiling_log_qdss(SNS_SAM_ALGO_UPDATE_EXIT, 3, clientAlgoInstPtr->serviceId, algoInstId, 1);

         sns_profiling_log_timestamp((uint64_t) (((uint64_t)(((uint64_t)SNS_SAM_ALGO_EXEC_PROFILE_END)<<32)) |
                                                             ((uint64_t)(clientAlgoInstPtr->serviceId))));

         sns_sam_check_config_update(clientAlgoInstPtr, algoInstId);

         // TODO: Passing 0 is incorrect. It must be the clientId.
         sns_sam_update_algo_report_ts(clientAlgoInstPtr,0);

         return SNS_SUCCESS;
      }
   }

   return SNS_ERR_FAILED;
}

/*=========================================================================
  FUNCTION:  sns_sam_check_config_update
  =========================================================================*/
/*!
  @brief Checks if the algorithm configuration has changed and performs
  tasks to address any change

  @param[i] algoInstPtr: Pointer to the algorithm instance
  @param[i] algoInstId: Instance ID of the algorithm

  @return None
*/
/*=======================================================================*/
void sns_sam_check_config_update(sns_sam_algo_inst_s *algoInstPtr, 
                                 uint8_t algoInstId)
{
   return;
}

/*=========================================================================
  FUNCTION:  sns_sam_get_adjusted_sample_rate
  =========================================================================*/
/*!
  @brief Adjusts sample rate to be at least the report rate

  @param[i] sampleRate: sample rate in Hz, Q16
  @param[i] reportPeriod: report period in seconds, Q16

  @return Adjusted sample rate in Hz, Q16
*/
/*=======================================================================*/
/*static q16_t sns_sam_get_adjusted_sample_rate(
   q16_t sampleRate,
   q16_t reportPeriod
   )
{
   float sample_rate = (float)FX_FIXTOFLT_Q16(sampleRate);
   float report_rate = (float)(1. / FX_FIXTOFLT_Q16(reportPeriod));

   if( report_rate - sample_rate > .1 )
   {
      sampleRate = FX_FLTTOFIX_Q16(report_rate);
   }

   return sampleRate;
}*/
/*=========================================================================
  FUNCTION:  sns_sam_gen_algo_enable_msg
  =========================================================================*/
/*!
  @brief Generate the algorithm enable request message

  @param[i] algoInstPtr: algorithm instance pointer
  @param[i] clientReqMsgPtr: client request message pointer
  @param[i] msgHdrPtr: message header pointer

  @return Sensors error code
*/
/*=======================================================================*/
void *sns_sam_gen_algo_enable_msg(
   sns_sam_algo_inst_s* algoInstPtr,
   const void* clientReqMsgPtr,
   sns_smr_header_s* msgHdrPtr)
{
   SNS_SAM_PRINTF2(LOW,
                  "sns_sam_gen_algo_enable_msg: algo serviceid %d, message service num %d",
                  algoInstPtr->serviceId, msgHdrPtr->svc_num);
   return NULL;
}

/*=========================================================================
  FUNCTION:  sns_sam_gen_algo_disable_msg
  =========================================================================*/
/*!
  @brief Generate the algorithm enable request message

  @param[i] algoInstId: algorithm instance id
  @param[i] msgHdrPtr: message header pointer

  @return Sensors error code
*/
/*=======================================================================*/
void *sns_sam_gen_algo_disable_msg(
   uint8_t instanceId,
   sns_smr_header_s* msgHdrPtr)
{
   SNS_SAM_PRINTF1(LOW,
                  "sns_sam_gen_algo_disable_msg: message service num %d",
                  msgHdrPtr->svc_num);
   return NULL;
}

/*=========================================================================
  FUNCTION:  sns_sam_update_algo_report_ts
  =========================================================================*/
/*!
  @brief Update the algorithm report timestamp

  @param[i] algoInstPtr: pointer to algorithm instance in database
  @param[i] clientId: client identifier

  @return None
*/
/*=======================================================================*/
void sns_sam_update_algo_report_ts(
   sns_sam_algo_inst_s* algoInstPtr,
   uint8_t clientId)
{
    switch (algoInstPtr->serviceId)
    {
       case SNS_SAM_MODEM_SCN_SVC_ID_V01:
         algoInstPtr->outputData.timestamp =
            ((modem_scn_output_s *) algoInstPtr->outputData.memPtr)->timestamp;
        break;

       default:
          break;
    }
}

/*=========================================================================
  FUNCTION:  sns_sam_process_one_shot_algo_report
  =========================================================================*/
/*!
  @brief Process one-shot report from specified algorithm

  @param[i] clientReqPtr: pointer to the client request
  @param[i] algoRptPtr: pointer to algorithm report

  @return Sensors error code
*/
/*=======================================================================*/
void sns_sam_process_one_shot_algo_report(
   uint8_t clientReqId,
   const sns_sam_algo_rpt_s *algoRptPtr)
{
   return;
}

/*=========================================================================
  FUNCTION:  sns_sam_handle_duty_cycle_state_change
  =========================================================================*/
/*!
  @brief Performs algorithm specific actions to duty cycle state change

  @param[i] algoInstId: index to algorithm instance in the database
  @param[i] algoInstPtr: pointer to algorithm instance

  @return Sensors error code
*/
/*=======================================================================*/
sns_err_code_e sns_sam_handle_duty_cycle_state_change(
   uint8_t algoInstId,
   sns_sam_algo_inst_s *algoInstPtr)
{
   if (algoInstPtr == NULL)
   {
      return SNS_ERR_FAILED;
    }

   return SNS_SUCCESS;
}

/*=========================================================================
  FUNCTION:  sns_sam_validate_client_req_parameter
  =========================================================================*/
/*!
  @brief Check if the parameters passed along with client request are valid

  @param[i] msgId: type of client request
  @param[i] clientReqMsgPtr: pointer to client request message
  @param[i] algoSvcId: algorithm service Id number

  @return returns one of the following sensors error codes
          1) SNS_ERR_NOTSUPPORTED if the algorithm service does not support
          parameter validation or a msgId not supported in the function is
          passed
          2) SNS_SUCCESS if the parameters passed along with the client
          request are valid
          3) SNS_ERR_BAD_PARM if the parameters passed along with the client
          request are invalid
*/
/*=======================================================================*/
sns_err_code_e sns_sam_validate_client_req_parameter(
   uint8_t msgId,
   const void* clientReqMsgPtr,
   uint8_t algoSvcId)
{
   switch (msgId)
   {
      case SNS_SAM_ALGO_ENABLE_REQ:
      {
         sns_err_code_e err = sns_sam_validate_algo_report_period(algoSvcId, clientReqMsgPtr);
         if( err != SNS_SUCCESS )
         {
            return err;
         }

         return sns_sam_validate_algo_sample_rate(algoSvcId, clientReqMsgPtr);
      }
      default:
      {
         return SNS_ERR_NOTSUPPORTED;
      }
   }
   return SNS_SUCCESS;
}

/*=========================================================================
  FUNCTION:  sns_sam_update_smgr_req
  =========================================================================*/
/*!
  @brief    Updates parameters associated with a SMGR request.

  @param[i] algoSvcId:  algorithm service id
  @param[i] dataReqId:  index of data request entry in dbase
  @param[i] dataReqType:  SMGR request type

  @return   Sensors error code
*/
/*=======================================================================*/
sns_err_code_e sns_sam_update_smgr_req(
   uint8_t algoSvcId,
   uint8_t dataReqId,
   uint8_t dataReqType)
{
   sns_err_code_e err = SNS_ERR_FAILED;
   sns_sam_data_req_s * dataReqPtr = sns_sam_data_req_dbase_acc(dataReqId);

   if (NULL == sns_sam_algo_dbase_acc(sns_sam_get_algo_index(algoSvcId)))
   {
      return SNS_ERR_BAD_PARM;
   }

   if(dataReqPtr != NULL)
   {
      switch( dataReqType )
      {
         case SNS_SMGR_REPORT_REQ_V01:
         {
            dataReqPtr->reportRate =
                sns_sam_find_max_sample_rate(dataReqId);
            err = sns_sam_send_smgr_start_req( dataReqId, algoSvcId );
            break;
         }
         case SNS_SMGR_BUFFERING_REQ_V01:
         {
            uint8_t algoIndex = sns_sam_get_algo_index( algoSvcId );
            dataReqPtr->reportRate = 
                sns_sam_algo_dbase_acc(algoIndex)->defSensorReportRate;
            err = sns_sam_send_smgr_start_req( dataReqId, algoSvcId );
            break;
         }
         default:
            err = SNS_ERR_FAILED;
            break;
      }
      
      SNS_SAM_PRINTF3(HIGH, "mot_resp: algoSvcId=%d switched to req_type=%d (err=%d)",
                      algoSvcId, dataReqType, err);
   }

   return err;
}

/*=========================================================================
  FUNCTION:  sns_sam_update_input_type
  =========================================================================*/
/*!
  @brief    Switches between buffering and periodic input for algorithms

  @param[i] algoSvcId:  algorithm service id
  @param[i] dataReqId:  index of data request entry in dbase
  @param[i] prevOutputPtr:  previously generated output
  @param[i] currOutputPtr:  newly generated output

  @return   Sensors error code
*/
/*=======================================================================*/
sns_err_code_e sns_sam_update_input_type(
   uint8_t algoSvcId,
   uint8_t dataReqId,
   const void* prevOutputPtr,
   const void* currOutputPtr )
{
   sns_err_code_e err = SNS_ERR_FAILED;

   if( !prevOutputPtr || !currOutputPtr)
   {
      return err;
   }

   return SNS_SUCCESS;
}

/*=========================================================================
  FUNCTION:  sns_sam_process_algo_update_req
  =========================================================================*/
/*!
  @brief Processes the algo update request

  @param[i] algoInstId: algo instance id
  @param[i] clientReqId: client request id
  @param[i] clientReqMsgPtr: pointer to the client request message

  @return   Sensors error code
*/
/*=======================================================================*/
sns_err_code_e sns_sam_process_algo_update_req(
   uint8_t algoInstId,
   uint8_t clientReqId,
   const void* clientReqMsgPtr)
{
   return SNS_ERR_NOTSUPPORTED;
}

/*=========================================================================
  FUNCTION:  sns_sam_process_algo_batch_req
  =========================================================================*/
/*!
  @brief Processes the algo batch request

  @param[i] algoPtr: pointer to algorithm structure
  @param[i] clientReqId: client request id
  @param[i] clientReqMsgPtr: pointer to the client request message

  @return   Sensors error code
*/
/*=======================================================================*/
sns_err_code_e sns_sam_process_algo_batch_req(
   sns_sam_algo_s * algoPtr,
   uint8_t clientReqId,
   const void* clientReqMsgPtr)
{
   return SNS_ERR_NOTSUPPORTED;
}

/*=========================================================================
  FUNCTION:  sns_sam_process_algo_upd_batch_period_req
  =========================================================================*/
/*!
  @brief Processes the algo update batch period request

  @param[i] algoSvcId: algo service id
  @param[i] clientReqId: client request id
  @param[i] clientReqMsgPtr: pointer to the client request message

  @return   Sensors error code
*/
/*=======================================================================*/
sns_err_code_e sns_sam_process_algo_upd_batch_period_req(
   uint8_t algoSvcId,
   uint8_t clientReqId,
   const void* clientReqMsgPtr)
{
   sns_err_code_e err = SNS_ERR_NOTSUPPORTED;
   int32_t activeBatchPeriod = -1;

   SNS_SAM_PRINTF2(LOW,"SAM:Rxd upd batch period request for svc %d, client id %d",algoSvcId,clientReqId);

   if (activeBatchPeriod >= 0)
   {
      err = sns_sam_proc_upd_batch_period_req(clientReqId, activeBatchPeriod);
   }
   return err;
}


/*=========================================================================
  FUNCTION:  sns_sam_refresh_algo_output
  =========================================================================*/
/*!
  @brief Refresh the algorithm output. No new inputs are provided.

  @param[i] algoInstId: algo instance id
  @param[i] clientReqId: client request id

  @return none
*/
/*=======================================================================*/
void sns_sam_refresh_algo_output(
   uint8_t algoInstId,
   uint8_t clientReqId)
{
   return;
}


/*=========================================================================
  FUNCTION:  sns_sam_on_change_report_requirement
  =========================================================================*/
/*!
  @brief Get on change reporting requirement for algo service

  @param[i] algoSvcId: algorithm service Id

  @return true: report only when output has changed since last report
          false: report even if output is unchanged
*/
/*=======================================================================*/
bool sns_sam_on_change_report_requirement(uint8_t algoSvcId)
{
   return true;
}
/*=========================================================================
  FUNCTION:  sns_sam_get_all_sensor_uuids
  =========================================================================*/
/*!
  @brief Get UUIDs of detected sensors from registry

  @param[i] sigEventPtr: pointer to the signal group flag
  @param[o] uuids: UUIDs of all detected sensors

  @return none
*/
/*=======================================================================*/
void sns_sam_get_all_sensor_uuids(
   OS_FLAG_GRP *sigEventPtr,
   sns_sam_sensor_uuid_s uuids[SNS_SAM_NUM_SENSORS])
{
   // No need to read UUIDs on SSC for mag cal registration
   UNREFERENCED_PARAMETER(sigEventPtr);
   UNREFERENCED_PARAMETER(uuids);
}

/*=========================================================================
 FUNCTION:  sns_sam_detect_smgr_buffering
  =========================================================================*/
/*!
  @brief  Detects support for Buffering in Sensor Manager.

  @return  true, since SMGR supports buffering
*/
/*=======================================================================*/
bool sns_sam_detect_smgr_buffering(
   OS_FLAG_GRP *sigEventPtr)
{
   UNREFERENCED_PARAMETER(sigEventPtr);
   return true;
}
