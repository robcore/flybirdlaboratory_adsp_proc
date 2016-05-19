#ifndef SNS_RH_MR_H
#define SNS_RH_MR_H
/*=============================================================================
  @file sns_rh_mr.h

  This header file contains the data definitions used within the
  Message Router module of Request Handler task.

******************************************************************************
* Copyright (c) 2014 Qualcomm Technologies, Inc.  All Rights Reserved.
* Qualcomm Technologies Proprietary and Confidential.
******************************************************************************/

/* $Header: //components/rel/ssc.adsp/2.6.1/smgr/src/sns_rh_mr.h#2 $ */
/* $DateTime: 2014/12/08 21:10:27 $ */
/* $Author: pwbldsvc $ */

/*============================================================================
  EDIT HISTORY FOR FILE

  when        who  what, where, why
  ----------  ---  -----------------------------------------------------------
  2014-12-07  pn   Added sns_rh_mr_validate_connection()
  2014-07-21  pn   Added support for event_gated_buffering
  2014-05-02  aj   Replaced QMI with SMR
  2014-04-29  pn   Refactored to support microImage
  2014-04-23  pn   Initial version

============================================================================*/

/*----------------------------------------------------------------------------
 * Include Files
 * -------------------------------------------------------------------------*/

#include "sns_osa.h"
#include "sns_queue.h"
#include "sns_rh.h"
#include "sns_smgr_api_v01.h"
#include "sns_smgr_internal_api_v02.h"
#include "sns_smgr_restricted_api_v01.h"
#include "sns_smgr.h"
#include "sns_usmr.h"

/*----------------------------------------------------------------------------
 * Preprocessor Definitions and Constants
 * -------------------------------------------------------------------------*/
  /* at most one connection per report and one connection for MD client */
#define SNS_RH_MR_MAX_CONNECTIONS                 SNS_SMGR_MAX_REPORT_CNT+1

#define SNS_RH_MR_MSG_HISTORY_MAX_COUNT           16
#define SNS_RH_MR_MSG_HISTORY_BYTES2SAVE          32

/*----------------------------------------------------------------------------
 * Type Declarations
 * -------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------
 * Structure Definitions
 * -------------------------------------------------------------------------*/
typedef union
{
  /* external services */
  sns_smgr_sensor_cal_req_msg_v01             calibration;
  sns_smgr_all_sensor_info_req_msg_v01        all_sensor_info;
  sns_smgr_single_sensor_info_req_msg_v01     single_sensor_info;
  sns_smgr_single_sensor_test_req_msg_v01     single_sensor_test;
  sns_smgr_periodic_report_req_msg_v01        periodic_report;
  sns_smgr_buffering_req_msg_v01              buffering_report;
  sns_smgr_buffering_query_req_msg_v01        query_report;

  /* deprecated services */
  sns_smgr_sensor_status_req_msg_v01          deprecated_sensor_status;

  /* internal service */
  sns_smgr_sensor_events_query_req_msg_v02    sensor_events_query;
  sns_smgr_sensor_event_req_msg_v02           sensor_event;
  sns_smgr_sensor_status_monitor_req_msg_v02  sensor_status_monitor;
  sns_smgr_event_gated_buffering_req_msg_v02  event_gated_buffering_report;

  /* restricted service */
  sns_smgr_driver_access_req_msg_v01          driver_access;

} sns_rh_request_type_u;

typedef union
{
  /* external service */
  sns_smgr_sensor_cal_resp_msg_v01            calibration;
  sns_smgr_all_sensor_info_resp_msg_v01       all_sensor_info;
  sns_smgr_single_sensor_info_resp_msg_v01    single_sensor_info;
  sns_smgr_single_sensor_test_resp_msg_v01    single_sensor_test;
  sns_smgr_periodic_report_resp_msg_v01       periodic_report;
  sns_smgr_buffering_resp_msg_v01             buffering_report;
  sns_smgr_buffering_query_resp_msg_v01       query_report;

  /* internal service */
  sns_smgr_sensor_events_query_resp_msg_v02   sensor_events_query;
  sns_smgr_sensor_event_resp_msg_v02          sensor_event;
  sns_smgr_sensor_status_monitor_resp_msg_v02 sensor_status_monitor;
  sns_smgr_event_gated_buffering_resp_msg_v02 event_gated_buffering_report;

} sns_rh_response_type_u;

typedef struct
{
  uint8_t             src_module;  /* Source module ID within the Sensors framework */
  uint8_t             svc_num;     /* SNS_xxxx_SVC_ID_V01 in sns_common_v01.h */
  uint16_t            msg_id;      /* depending on the service */
  uint16_t            body_len;
  void*               connection_handle;
  smr_req_handle      req_handle;
  uint32_t            timestamp;
} sns_rh_mr_header_s;

struct sns_rh_mr_req_q_item_s
{
  sns_rh_mr_header_s    header;
  sns_rh_request_type_u request;
  sns_q_link_s          q_link;
};

typedef struct
{
  sns_rh_mr_header_s  msg_header;
  uint8_t             body[SNS_RH_MR_MSG_HISTORY_BYTES2SAVE - sizeof(sns_rh_mr_header_s)];
} sns_rh_mr_msg_content_s;

typedef struct
{
  uint32_t                num_rcvd_msgs;
  sns_rh_mr_msg_content_s msg_contents[SNS_RH_MR_MSG_HISTORY_MAX_COUNT];
} sns_rh_mr_msg_history_s;

typedef struct
{
  smr_qmi_client_handle   client_handle;
  bool                    is_valid; /* set to false in disconnect_cb()*/
} sns_rh_mr_connection_s;

typedef struct  
{
  /* SMR server interface */
  smr_service_hndl            service_handle_ext;
  uint32                      service_cookie_ext;

  smr_service_hndl            service_handle_int;
  uint32                      service_cookie_int;

  smr_service_hndl            service_handle_restricted;
  uint32                      service_cookie_restricted;

  sns_q_s                     req_queue;
  OS_EVENT*                   req_queue_mutex_ptr;

  sns_rh_mr_msg_history_s     msg_history;

} sns_rh_mr_s;

/*----------------------------------------------------------------------------
 * Function Declarations and Documentation
 * -------------------------------------------------------------------------*/
extern void sns_rh_mr_init(void);

extern void sns_rh_mr_handle_disconnect_sig(void);

extern void sns_rh_mr_handle_external_event(void);

extern void sns_rh_mr_handle_internal_event(void);

extern void sns_rh_mr_handle_restricted_event(void);

extern sns_rh_mr_req_q_item_s* sns_rh_mr_get_msg(void);

extern sns_err_code_e sns_rh_mr_send_resp(
  const sns_rh_mr_header_s* msg_header_ptr, 
  void*                     resp_ptr);

extern void sns_rh_mr_send_resp_w_err(
  sns_rh_mr_req_q_item_s*   item_ptr);

extern bool sns_rh_mr_send_indication(
  const void*               conn_handle,
  void*                     ind_msg_ptr, 
  uint16_t                  msg_id, 
  uint16_t                  len, 
  bool                      free_me);

extern bool sns_rh_mr_validate_connection(
  const void*               conn_handle);

#endif /* #ifndef SNS_RH_MR_H */
