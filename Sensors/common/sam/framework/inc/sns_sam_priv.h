#ifndef SNS_SAM_PRIV_H
#define SNS_SAM_PRIV_H

/*============================================================================
  @file sns_sam_priv.h

  Sensors Algorithm Manager header

  This header file contains the private interface of Sensors Algorithm Manager

  Copyright (c) 2010-2014 Qualcomm Technologies, Inc.  All Rights Reserved.
  Qualcomm Technologies Proprietary and Confidential.

============================================================================*/

/*---------------------------------------------------------------------------
* Include Files
* -------------------------------------------------------------------------*/
#include "stdbool.h"
#include "sns_common.h"
#include "sns_common_v01.h"
#include "sns_sam_common_v01.h"
#include "sns_debug_api.h"
#include "sns_em.h"
#include "sns_smr_util.h"
#include "sns_sam_algo.h"
#include "sns_sam_mr.h"
#include "sns_circ_buffer.h"
#include "sns_sam_qmd_v01.h"

/*---------------------------------------------------------------------------
* Preprocessor Definitions and Constants
* -------------------------------------------------------------------------*/

#define SNS_SAM_DEBUG

#if defined(SNS_DSPS_BUILD) || (defined(SNS_PCSIM) && !defined(ENABLE_APPS_PLAYBACK))
# define SNS_SAM_MODULE              SNS_MODULE_DSPS_SAM
# define SNS_SAM_MODULE_PRIORITY     SNS_MODULE_PRI_DSPS_SAM
# define SNS_SAM_DBG_MOD             SNS_DBG_MOD_DSPS_SAM
# define SNS_SAM_MODULE_STK_SIZE     SNS_MODULE_STK_SIZE_DSPS_SAM
#else
# define SNS_SAM_MODULE              SNS_MODULE_APPS_SAM
# define SNS_SAM_MODULE_PRIORITY     SNS_MODULE_PRI_APPS_SAM
# define SNS_SAM_MR_MODULE_PRIORITY  SNS_MODULE_PRI_APPS_SAM_MR
# define SNS_SAM_DBG_MOD             SNS_DBG_MOD_APPS_SAM
# define SNS_SAM_MODULE_STK_SIZE     SNS_MODULE_STK_SIZE_APPS_SAM
#endif

#ifdef SNS_SAM_DEBUG
#define SNS_SAM_DEBUG0(level, msg)          SNS_SAM_PRINTF0(level,msg)
#define SNS_SAM_DEBUG1(level, msg, p1)       SNS_SAM_PRINTF1(level,msg,p1)
#define SNS_SAM_DEBUG2(level, msg, p1, p2)    SNS_SAM_PRINTF2(level,msg,p1,p2)
#define SNS_SAM_DEBUG3(level, msg, p1, p2, p3) SNS_SAM_PRINTF3(level,msg,p1,p2,p3)

#if defined QDSP6
#ifndef DBG_MEDIUM_PRIO
#define DBG_MEDIUM_PRIO DBG_MED_PRIO
#endif //DBG_MEDIUM_PRIO
#define SNS_SAM_PRINTF0(level,msg)          MSG(MSG_SSID_SNS,DBG_##level##_PRIO,msg)
#define SNS_SAM_PRINTF1(level,msg,p1)       MSG_1(MSG_SSID_SNS,DBG_##level##_PRIO,msg,p1)
#define SNS_SAM_PRINTF2(level,msg,p1,p2)    MSG_2(MSG_SSID_SNS,DBG_##level##_PRIO,msg,p1,p2)
#define SNS_SAM_PRINTF3(level,msg,p1,p2,p3) MSG_3(MSG_SSID_SNS,DBG_##level##_PRIO,msg,p1,p2,p3)
#elif defined(ADSP_STANDALONE)
#define SNS_SAM_PRINTF0(level,msg)          qurt_printf("\n"); qurt_printf(msg)
#define SNS_SAM_PRINTF1(level,msg,p1)       qurt_printf("\n"); qurt_printf(msg,p1)
#define SNS_SAM_PRINTF2(level,msg,p1,p2)    qurt_printf("\n"); qurt_printf(msg,p1,p2)
#define SNS_SAM_PRINTF3(level,msg,p1,p2,p3) qurt_printf("\n"); qurt_printf(msg,p1,p2,p3)
#else
#define SNS_SAM_PRINTF0(level,msg)          SNS_PRINTF_STRING_##level##_0(SNS_SAM_DBG_MOD,msg)
#define SNS_SAM_PRINTF1(level,msg,p1)       SNS_PRINTF_STRING_##level##_1(SNS_SAM_DBG_MOD,msg,p1)
#define SNS_SAM_PRINTF2(level,msg,p1,p2)    SNS_PRINTF_STRING_##level##_2(SNS_SAM_DBG_MOD,msg,p1,p2)
#define SNS_SAM_PRINTF3(level,msg,p1,p2,p3) SNS_PRINTF_STRING_##level##_3(SNS_SAM_DBG_MOD,msg, p1, p2, p3)
#endif //QDSP6
#else
#define SNS_SAM_DEBUG0(level, msg)
#define SNS_SAM_DEBUG1(level, msg, p1)
#define SNS_SAM_DEBUG2(level, msg, p1, p2)
#define SNS_SAM_DEBUG3(level,msg,p1,p2,p3)

#define SNS_SAM_PRINTF0(level,msg)
#define SNS_SAM_PRINTF1(level,msg,p1)
#define SNS_SAM_PRINTF2(level,msg,p1,p2)
#define SNS_SAM_PRINTF3(level, msg, p1, p2, p3)
#endif //SNS_SAM_DEBUG

// Each signal should use a unique bit
#define SNS_SAM_MSG_SIG 0x01
#define SNS_SAM_REPORT_TIMER_SIG 0x02
#define SNS_SAM_QMI_CLI_SIG 0x04
#define SNS_SAM_QMI_TIMER_SIG 0x08
#define SNS_SAM_QMI_DISC_SIG 0x10
#define SNS_SAM_AP_AWAKE_SIG 0x20   // Used by PM to signal AP wake up (only on SSC)
#define SNS_SAM_AP_SUSPEND_SIG 0x40 // Used by PM to signal AP entering suspend (only on SSC)
#define SNS_SAM_MODEM_INFO_SIG 0x80


// This should be the last signal. All algorithms use increasing orthogonal bits
#define SNS_SAM_QMI_SV_MSG_SIG 0x100
#define SNS_SAM_SIGNAL_MASK (SNS_SAM_MSG_SIG | SNS_SAM_REPORT_TIMER_SIG |SNS_SAM_QMI_DISC_SIG | SNS_SAM_AP_AWAKE_SIG | SNS_SAM_AP_SUSPEND_SIG | SNS_SAM_MODEM_INFO_SIG)

#define SNS_SAM_MAX_ALGOS 30         //limit for number of supported algorithms

#define SNS_SAM_MAX_CLIENT_REQS 100
#define SNS_SAM_MAX_ALGO_INSTS 50
#define SNS_SAM_MAX_DATA_REQS 50

#define SNS_SAM_MAX_CLIENT_REQS_PER_ALGO_INST 5
#define SNS_SAM_MAX_ALGO_INSTS_PER_DATA_REQ 10
#define SNS_SAM_MAX_SENSORS_PER_DATA_REQ 3
#define SNS_SAM_MAX_ALGO_INSTS_PER_SENSOR SNS_SAM_MAX_ALGO_INSTS_PER_DATA_REQ

#define SNS_SAM_MAX_REQ_MSG_LEN 256
#define SNS_SAM_MAX_RESP_MSG_LEN 128
#define SNS_SAM_MAX_IND_MSG_LEN 512

//All algorithm services must support the following messages
//with specified message ids
#define SNS_SAM_ALGO_CANCEL_REQ 0x00
#define SNS_SAM_ALGO_CANCEL_RESP 0x00
#define SNS_SAM_ALGO_VERSION_REQ 0x01
#define SNS_SAM_ALGO_VERSION_RESP 0x01
#define SNS_SAM_ALGO_ENABLE_REQ 0x02
#define SNS_SAM_ALGO_ENABLE_RESP 0x02
#define SNS_SAM_ALGO_DISABLE_REQ 0x03
#define SNS_SAM_ALGO_DISABLE_RESP 0x03
#define SNS_SAM_ALGO_GET_REPORT_REQ 0x04
#define SNS_SAM_ALGO_GET_REPORT_RESP 0x04
#define SNS_SAM_ALGO_REPORT_IND 0x05
#define SNS_SAM_ALGO_ERROR_IND 0x06
#define SNS_SAM_ALGO_UPDATE_REQ 0x20
#define SNS_SAM_ALGO_UPDATE_RESP 0x20
#define SNS_SAM_ALGO_BATCH_REQ 0x21
#define SNS_SAM_ALGO_BATCH_RESP 0x21
#define SNS_SAM_ALGO_BATCH_IND 0x22
#define SNS_SAM_ALGO_UPDATE_BATCH_PERIOD_REQ 0x23
#define SNS_SAM_ALGO_UPDATE_BATCH_PERIOD_RESP 0x23
#define SNS_SAM_ALGO_GET_ATTRIB_REQ 0x24
#define SNS_SAM_ALGO_GET_ATTRIB_RESP 0x24

#define SNS_SAM_INVALID_ID 0xFF
#define SNS_SAM_INVALID_PERIOD 0xFFFFFFFF
#define SNS_SAM_INVALID_SAMPLE_RATE     0xFFFF  /* Not supported by any sensor */

#define SNS_SAM_DEFAULT_SAMPLE_QUALITY  0x0000  /* bitmap, all flags disabled */

#define SNS_SAM_DUTY_CYCLE_TIMER_SOURCE_NONE -1

#define SNS_SAM_USEC_PER_SEC 1000000.0

// Max no of client processors that can be monitored
#define SNS_SAM_MAX_CLIENT_PROCESSORS 1
// Max no of clients that can use batching per processor
#define SNS_SAM_MAX_BATCH_CLIENTS_PER_PROC 8

#define SCALED_FLOAT(x) ((int) ((x) * 1000))

#define SNS_SAM_MAX_CLI_ID 40

//#define CONFIG_USE_OEM_1_ALGO

/*---------------------------------------------------------------------------
* Type Declarations
* -------------------------------------------------------------------------*/
/*=======================================================================*/

//algorithm output structure
typedef struct {
   uint32_t timestamp;
   uint32_t memSize;
   void *memPtr;
} sns_sam_algo_rpt_s;

//events handled by SAM
typedef enum {
   SNS_SAM_UNKNOWN_EVENT,
   SNS_SAM_MSG_EVENT,
   SNS_SAM_REPORT_TIMER_EVENT
} sns_sam_event_e;

//reporting types
typedef enum {
   SNS_SAM_UNKNOWN_REPORT,
   SNS_SAM_PERIODIC_REPORT,
   SNS_SAM_ASYNC_REPORT,
   SNS_SAM_SYNC_REPORT,
   SNS_SAM_ONE_SHOT_REPORT
} sns_sam_report_e;

typedef enum {
   SNS_SAM_ACCEL,
   SNS_SAM_GYRO,
   SNS_SAM_MAG,
   SNS_SAM_PROX_LIGHT,
   SNS_SAM_PRESSURE,
   SNS_SAM_NUM_SENSORS
} sns_sam_sensor_e;

//algorithm instance specific information
typedef struct {
   sns_sam_algo_mem_s configData; /*pointer to algorithm config*/
   sns_sam_algo_mem_s stateData;  /*pointer to algorithm state*/
   sns_sam_algo_mem_s inputData;  /*pointer to algorithm input data*/
   sns_sam_algo_rpt_s outputData; /*pointer to algorithm output data*/
   sns_sam_mr_algo_conn_hndl *mrAlgoConnHndl;
   uint8_t serviceId;             /*algorithm service id*/
   uint8_t clientReqCount;        /*client request count*/
   uint8_t clientReqDbase[SNS_SAM_MAX_CLIENT_REQS_PER_ALGO_INST];
                                  /*active client requests*/
   uint8_t algoReqDbase[SNS_SAM_MAX_ALGO_DEPS]; /*algo dependency instance id*/
   sns_sam_motion_state_e_v01 motion_state;     /* Device motion state */
   uint8_t dutycycleOnPercent;    /* duty cycle on percentage*/
   uint32_t dutycycleOnDuration;  /* duty cycle on duration in ticks*/
   int16_t dutycycleTimerSource;  /* index of the client request database
                                     whose timer is used for duty cycling
                                     or
                                     SNS_SAM_DUTY_CYCLE_TIMER_SOURCE_NONE (-1)
                                     if no timer source*/
   uint8_t dutycycleTimeoutCount;  /* number of duty cycle timer timeouts*/
   bool dutycycleStateOn;            /*algo instance duty cycle state: 0-off, 1-on*/
} sns_sam_algo_inst_s;

// batching information
typedef struct {
   uint32_t batchPeriod;            /*batch period in ticks - 0 if batching is off*/
   uint32_t activeBatchPeriod;      /*active batch period in ticks - 0 if batching is off*/
   uint32_t numTimeoutsToBatch;     /*number of timeouts needed to send a batch -
                                      only used in batching periodic reports*/
   uint32_t numTimeouts;            /*number of timeouts since last batch - only used
                                      in batching periodic reports*/
   sns_circ_buffer_type* reportBuffer;    /*circular buffer of reports -
                                      only used when batching is on*/
   bool wakeClient;                 /*indicates if client has to be woken up when
                                      buffer is full*/
} sns_sam_batch_req_s;

//client request information
struct sns_sam_client_req {
   uint32_t period;                 /*requested period for periodic reports*/
   uint32_t timestamp;              /*timestamp of last reported output*/
   sns_em_timer_obj_t timer;        /*timer for periodic reports*/
   sns_sam_mr_conn_hndl mrClientId; /*Client identifier provided by sam_mr*/
   uint8_t algoInstId;              /*algorithm instance servicing the request*/
   uint8_t reportId;                /*monotonically increasing report id*/
   uint8_t reqModule;               /*module from which the request is made*/
   bool timeout;                    /*timer timeout indication*/
   sns_sam_report_e reportType;     /*client report type*/
   uint8_t dutycycleOnPercent;      /* percentage of time the on period is active*/
   sns_sam_notify_suspend_s notify_suspend; /*represents if notifications should be sent
                                              during proc suspend */
   bool directReportReq;            /*indicates if reporting using messages can be
                                      bypassed using a direct function call instead*/
   sns_sam_batch_req_s * batchInfo; /*batching related info*/
};
typedef struct sns_sam_client_req sns_sam_client_req_s;

//sensor information
typedef struct {
   uint8_t sensorId;             /*sensor id*/
   uint8_t dataType;             /*sensor data type*/
   uint16_t sampleRate;          /*sample rate*/
   uint16_t sampleQual;          /*sample quality*/
   uint8_t algoInstCount;        /*algorithm instance count*/
   uint8_t algoInstIds[SNS_SAM_MAX_ALGO_INSTS_PER_SENSOR]; /*ids of algo instances that are
                                                             dependent on this sensor - used
                                                             only for cumulative data reqs*/
} sns_sam_sensor_req_s;

//sensor data request
typedef struct {
   uint32_t reportRate;          /*sensor data report rate*/
   uint8_t sensorCount;          /*sensor count*/
   uint8_t algoInstCount;        /*algorithm instance count*/
   sns_sam_sensor_req_s sensorDbase[SNS_SAM_MAX_SENSORS_PER_DATA_REQ];
                                 /*sensors whose data is requested*/
   uint8_t algoInstDbase[SNS_SAM_MAX_ALGO_INSTS_PER_DATA_REQ];
                                 /*algorithm instances requesting data*/
   bool registerMDInterrupt;     /*indicates dependency on MD interrupt*/
} sns_sam_data_req_s;

// State received or calculated from the time service
typedef struct sns_sam_time_state_s {
  /* time service */
  uint64_t  ts_offset;
  uint8_t   ts_cnt;
  bool      ts_offset_valid;

  /* DSPS rollover detection */
  uint64_t  ts_dsps_prev;       /* previous DSPS usec time (from time service) */
  uint32_t   ts_dsps_ro_cnt;     /* count of DSPS clock rollover */
} sns_sam_time_state_s;

// Client processor state monitoring info
typedef struct {
   bool suspendState;              /* Current suspend state */
   int clientCount;                /* No of interested clients */
   uint8_t clientReqIds[SNS_SAM_MAX_BATCH_CLIENTS_PER_PROC];
                                   /* Array of interested client request ids */
} sns_sam_proc_monitor_s;

// Sensor info from SMGR
typedef struct {
   bool valid;
   uint8_t sensorId;
   int32_t maxPower;
   int32_t maxSampleRate;
} sns_sam_sensor_info_s;

/*---------------------------------------------------------------------------
* Common Function Declarations
* -------------------------------------------------------------------------*/

/*=========================================================================
  FUNCTION:  sns_sam_get_time_state
  =========================================================================*/
/*!
  @brief Accessor function to the SAM time state.
*/
/*=======================================================================*/
sns_sam_time_state_s sns_sam_get_time_state(void);

/*=========================================================================
  FUNCTION:  sns_sam_set_time_state
  =========================================================================*/
/*!
  @brief Mutator function to the SAM time state.
*/
/*=======================================================================*/
void sns_sam_set_time_state(
    sns_sam_time_state_s *sam_time_state);

/*=========================================================================
  FUNCTION:  sns_sam_start_sensor_data
  =========================================================================*/
/*!
  @brief Request sensor data according to the algorithm needs

  @param[i] algoInstId: algorithm instance id
  @param[i] dataReq: sensor data request

  @return  Index to data request matching the specified configuration
  SNS_SAM_INVALID_ID if match is not found
*/
/*=======================================================================*/
uint8_t sns_sam_start_sensor_data(
   uint8_t algoInstId,
   const sns_sam_data_req_s * dataReq);

/*=========================================================================
  FUNCTION:  sns_sam_get_algo_report
  =========================================================================*/
/*!
  @brief get the current algorithm report

  @param[i] algoInstId: index to the algorithm instance in the database

  @return Algorithm report for the specified algorithm instance
*/
/*=======================================================================*/
sns_sam_algo_rpt_s *sns_sam_get_algo_report(
   uint8_t algoInstId);

/*=========================================================================
  FUNCTION:  sns_sam_get_algo_config
  =========================================================================*/
/*!
  @brief get the current algorithm configuration

  @param[i] algoInstId: index to the algorithm instance in the database

  @return Algorithm configuration for the specified algorithm instance
*/
/*=======================================================================*/
sns_sam_algo_mem_s *sns_sam_get_algo_config(
   uint8_t algoInstId);

/*=========================================================================
  FUNCTION:  sns_sam_get_algo_input
  =========================================================================*/
/*!
  @brief get the current algorithm input

  @param[i] algoInstId: index to the algorithm instance in the database

  @return Algorithm input for the specified algorithm instance
*/
/*=======================================================================*/
sns_sam_algo_mem_s *sns_sam_get_algo_input(
   uint8_t algoInstId);

/*=========================================================================
  FUNCTION:  sns_sam_get_algo_state
  =========================================================================*/
/*!
  @brief get the current algorithm state

  @param[i] algoInstId: index to the algorithm instance in the database

  @return Algorithm state for the specified algorithm instance
*/
/*=======================================================================*/
sns_sam_algo_mem_s *sns_sam_get_algo_state(
   uint8_t algoInstId);

/*=========================================================================
  FUNCTION:  sns_sam_prep_resp_msg
  =========================================================================*/
/*!
  @brief Sends response message for the specified request

  @param[i] reqMsgPtr: Pointer to request message for which
            response needs to be sent
  @param[i] respMsgPtr: Pointer to response message body,
            to be sent with header
  @param[i] respMsgBodyLen: Response message body length
            (excluding the header part)

  @return None
*/
/*=======================================================================*/
void sns_sam_prep_resp_msg(
   const uint8_t *reqMsgPtr,
   void         *respMsgPtr,
   uint16_t     respMsgBodyLen);

/*=========================================================================
  FUNCTION:  sns_sam_reg_algo_svc
  =========================================================================*/
/*!
  @brief Register the algorithm with SAM. This is expected to be done
         at SAM initialization for all algorithms to be handled by SAM

  @param[i] algoSvcId: Algorithm service id

  @return Sensors error code
*/
/*=======================================================================*/
sns_err_code_e sns_sam_reg_algo_svc(
   uint8_t algoSvcId);

/*=========================================================================
  FUNCTION:  sns_sam_get_algo_handle
  =========================================================================*/
/*!
  @brief Get the handle to the specified algorithm in the algorithm database

  @param[i] algoSvcId: algorithm service id

  @return handle to the specified algorithm if found,
          NULL otherwise
*/
/*=======================================================================*/
sns_sam_algo_s* sns_sam_get_algo_handle(
   uint8_t algoSvcId);

/*=========================================================================
 FUNCTION:  sns_sam_get_algo_index
 =========================================================================*/
/*!
  @brief Get the index into the algorithm database for the specified algorithm

  @param[i] algoSvcId: algorithm service id

  @return algorithm index for the specified algorithm if found,
          SNS_SAM_INVALID_ID otherwise
*/
/*=======================================================================*/
uint8_t sns_sam_get_algo_index(
   uint8_t algoSvcId);

/*---------------------------------------------------------------------------
* Module Function Declarations
* -------------------------------------------------------------------------*/

/*=========================================================================
  FUNCTION:  sns_sam_prep_algo_enable_err
  =========================================================================*/
/*!
  @brief Prepare an error message to client for algorithm enable request

  @param[i] clientReqMsgPtr: pointer to client request message
  @param[o] clientRespMsgPtr: Pointer to the response message created.
  @param[i] algoSvcId: algorithm service id
  @param[i] errCode: error code

  @return None
*/
/*=======================================================================*/
void sns_sam_prep_algo_enable_err(
   const void     *clientReqMsgPtr,
   void           **clientRespMsgPtr,
   uint8_t        algoSvcId,
   sns_err_code_e errCode);

/*=========================================================================
  FUNCTION:  sns_sam_prep_algo_disable_err
  =========================================================================*/
/*!
  @brief Prepare an error message to client for algorithm disable request

  @param[i] clientReqMsgPtr: pointer to client request message
  @param[o] clientRespMsgPtr: Pointer to the response message created.
  @param[i] algoSvcId: algorithm service id
  @param[i] errCode: error code

  @return None
*/
/*=======================================================================*/
void sns_sam_prep_algo_disable_err(
   const void     *clientReqMsgPtr,
   void           **clientRespMsgPtr,
   uint8_t        algoSvcId,
   sns_err_code_e errCode);

/*=========================================================================
  FUNCTION:  sns_sam_prep_algo_report_err
  =========================================================================*/
/*!
  @brief Prepare an error message to client for algorithm report request

  @param[i] clientReqMsgPtr: pointer to client request message
  @param[o] clientRespMsgPtr: Pointer to the response message created.
  @param[i] algoSvcId: algorithm service id
  @param[i] errCode: error code

  @return None
*/
/*=======================================================================*/
void sns_sam_prep_algo_report_err(
   const void     *clientReqMsgPtr,
   void           **clientRespMsgPtr,
   uint8_t        algoSvcId,
   sns_err_code_e errCode);

/*=========================================================================
  FUNCTION:  sns_sam_prep_algo_update_err
  =========================================================================*/
/*!
  @brief Prepare an error message to client for algorithm update request

  @param[i] clientReqMsgPtr: pointer to client request message
  @param[o] clientRespMsgPtr: Pointer to the response message created.
  @param[i] algoSvcId: algorithm service id
  @param[i] errCode: error code

  @return None
*/
/*=======================================================================*/
void sns_sam_prep_algo_update_err(
   const void     *clientReqMsgPtr,
   void           **clientRespMsgPtr,
   uint8_t        algoSvcId,
   sns_err_code_e errCode);

/*=========================================================================
  FUNCTION:  sns_sam_prep_algo_batch_err
  =========================================================================*/
/*!
  @brief Prepare an error message to client for algorithm batch request

  @param[i] clientReqMsgPtr: pointer to client request message
  @param[o] clientRespMsgPtr: Pointer to the response message created.
  @param[i] algoSvcId: algorithm service id
  @param[i] errCode: error code

  @return None
*/
/*=======================================================================*/
void sns_sam_prep_algo_batch_err(
   const void     *clientReqMsgPtr,
   void           **clientRespMsgPtr,
   uint8_t        algoSvcId,
   sns_err_code_e errCode);

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
   sns_err_code_e errCode);

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
   uint8_t                         algoSvcId,
   sns_common_version_resp_msg_v01 *versionRespMsgPtr);

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
   sns_sam_algo_s                       *algoPtr,
   sns_sam_get_algo_attrib_resp_msg_v01 *attribRespMsgPtr);

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
   const sns_sam_client_req_s *clientReqPtr,
   void                       **clientIndMsgPtr,
   const sns_sam_algo_rpt_s   *algoRptPtr,
   sns_smr_header_s           *msgHdrPtr);

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
   const sns_sam_client_req_s *clientReqPtr);

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
   uint8_t          algoInstId,
   uint8_t          error,
   sns_smr_header_s *msgHdrPtr,
   void             **msgIndPtr);

/*=========================================================================
  FUNCTION:  sns_sam_get_algo_report_period
  =========================================================================*/
/*!
  @brief Get the algorithm report period

  @param[i] algoSvcId: algorithm service id
  @param[i] clientReqMsgPtr: pointer to client request message
  @param[i] algoCfgPtr: pointer to algorithm configuration

  @return Algorithm report period. 0 if report is not periodic
*/
/*=======================================================================*/
uint32_t sns_sam_get_algo_report_period(
   uint8_t    algoSvcId,
   const void *clientReqMsgPtr,
   const void *algoCfgPtr);

/*=========================================================================
  FUNCTION:  sns_sam_prep_algo_enable_resp
  =========================================================================*/
/*!
  @brief Prepare a response to algorithm enable request

  @param[i] algoInstId: algorithm instance id
  @param[i] algoSvcId: algorithm service id
  @param[i] clientReqMsgPtr: pointer to client request message
  @param[o] clientRespMsgPtr: Pointer to the response message created.

  @return Sensors error code
*/
/*=======================================================================*/
sns_err_code_e sns_sam_prep_algo_enable_resp(
   uint8_t              algoInstId,
   uint8_t              algoSvcId,
   const void           *clientReqMsgPtr,
   void                 **clientRespMsgPtr);

/*=========================================================================
  FUNCTION:  sns_sam_send_algo_disable_resp
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
   uint8_t    algoInstId,
   uint8_t    algoSvcId,
   const void *clientReqMsgPtr,
   void       **clientRespMsgPtr);

/*=========================================================================
  FUNCTION:  sns_sam_send_algo_report_resp
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
   const sns_sam_client_req_s *clientReqPtr,
   const void                 *clientReqMsgPtr,
   void                       **clientRespMsgPtr,
   uint8_t                    algoSvcId);

/*=========================================================================
  FUNCTION:  sns_sam_prep_algo_update_resp
  =========================================================================*/
/*!
  @brief Prepare a response to algorithm update request

  @param[i] clientReqMsgPtr: pointer to client request message
  @param[o] clientRespMsgPtr: Pointer to the response message created.
  @param[i] algoSvcId: algorithm service id

  @return Sensors error code
*/
/*=======================================================================*/
sns_err_code_e sns_sam_prep_algo_update_resp(
   const void *clientReqMsgPtr,
   void       **clientRespMsgPtr,
   uint8_t    algoSvcId);

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
   sns_sam_algo_s* algoPtr);

/*=========================================================================
  FUNCTION:  sns_sam_prep_algo_upd_batch_period_resp
  =========================================================================*/
/*!
  @brief Prepare a response to algorithm update batch period request

  @param[i] clientReqMsgPtr: pointer to client request message
  @param[o] clientRespMsgPtr: Pointer to the response message created.
  @param[i] algoSvcId: algorithm service id

  @return Sensors error code
*/
/*=======================================================================*/
sns_err_code_e sns_sam_prep_algo_upd_batch_period_resp(
   const void *clientReqMsgPtr,
   void       **clientRespMsgPtr,
   uint8_t    algoSvcId);

/*=========================================================================
  FUNCTION:  sns_sam_req_sensor_data
  =========================================================================*/
/*!
  @brief Request sensor data for algorithm

  @param[i] algoInstId: algorithm instance id
  @param[i] clientReqId: client request id

  @return data request id used for the request
*/
/*=======================================================================*/
uint8_t sns_sam_req_sensor_data(
   uint8_t algoInstId,
   uint8_t clientReqId);

/*=========================================================================
  FUNCTION:  sns_sam_add_sensor_for_algo
  =========================================================================*/
/*!
  @brief Add a sensor to a data request for a particular algorithm. This 
  function is limited only to algorithms that have existing data requests.

  @param[i] algoInstId: algorithm instance id
  @param[i] sensorReq: Individual sensor request

  @return data request id for the request
*/
/*=======================================================================*/
uint8_t sns_sam_add_sensor_for_algo(
   uint8_t algoInstId,
   sns_sam_sensor_req_s *sensorReq);

/*=========================================================================
  FUNCTION:  sns_sam_rm_sensor_for_algo
  =========================================================================*/
/*!
  @brief Remove a sensor from a data request for a particular algorithm.

  @param[i] algoInstId: algorithm instance id
  @param[i] sensorId: ID of the sensor to be disabled

  @return data request id for the request
*/
/*=======================================================================*/
uint8_t sns_sam_rm_sensor_for_algo(
   uint8_t algoInstId,
   uint8_t sensorId);

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
   sns_sam_data_req_s *dataReq);

/*=========================================================================
  FUNCTION:  sns_sam_stop_sensor_data
  =========================================================================*/
/*!
  @brief Stop sensor data received for specified algorithm instance

  @param[i] algoInstId: Index of algorithm instance in database

  @return None
*/
/*=======================================================================*/
void sns_sam_stop_sensor_data(
   uint8_t algoInstId);

/*=========================================================================
  FUNCTION:  sns_sam_reg_algo
  =========================================================================*/
/*!
  @brief Register specified algorithm

  @param[i/o] algoPtr: pointer to algorithm
  @param[i] uuids: UUIDs of detected sensors

  @return None
*/
/*=======================================================================*/
sns_err_code_e sns_sam_reg_algo(
   sns_sam_algo_s* algoPtr,
   const sns_sam_sensor_uuid_s* uuids);

/*=========================================================================
  FUNCTION:  sns_sam_reg_algos
  =========================================================================*/
/*!
  @brief Register all algorithms

  @return None
*/
/*=======================================================================*/
void sns_sam_reg_algos(void);

/*=========================================================================
  FUNCTION:  sns_sam_sensor_info_dbase_acc
  =========================================================================*/
/*!
  @brief Gets sensor info for specified type

  @param[i] type: sensor type from sns_sam_sensor_e

  @return Sensor info structure
*/
/*=======================================================================*/
sns_sam_sensor_info_s * sns_sam_sensor_info_dbase_acc(
   uint8_t type);

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
   uint8_t                    algoInstId,
   const sns_sam_algo_inst_s  *algoInstPtr,
   uint8_t algoIndex);

/*=========================================================================
  FUNCTION:  sns_sam_log_algo_result
  =========================================================================*/
/*!
  @brief Log algorithm result

  @param[i] algoInstId: algorithm instance id
  @param[i] algoInstPtr: pointer to algorithm instance
  @param[i] clientId: client id

  @return None
*/
/*=======================================================================*/
void sns_sam_log_algo_result(
   uint8_t                    algoInstId,
   const sns_sam_algo_inst_s  *algoInstPtr,
   uint8_t                    clientId);

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
   uint8_t                    algoInstId,
   const sns_sam_algo_inst_s  *algoInstPtr);

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
   uint8_t    algoSvcId,
   const void *clientReqMsgPtr,
   void       *algoCfgPtr);

/*=========================================================================
  FUNCTION:  sns_sam_update_algo_input
  =========================================================================*/
/*!
  @brief Update algorithm input structure

  @param[i] algoSvcId: algorithm service Id
  @param[i] indMsgType: indication message type
  @param[i] indPtr: pointer to SMGR report indication message
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
   const void *indPtr,
   void       *algoInpPtr,
   uint32_t   algoInpSize,
   uint32_t   timestamp,
   uint8_t   sensorID);

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
   const void *samRespPtr);

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
   const void          *samIndPtr,
   sns_sam_algo_inst_s *clientAlgoInstPtr,
   uint8_t             algoSvcId,
   uint8_t             algoInstId);

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
                                 uint8_t algoInstId);

/*=========================================================================
  FUNCTION:  sns_sam_time_send_sync_req
  =========================================================================*/
/*!
  @brief    Sends a message to Time Service within SAM framework

  @return   None
*/
/*=======================================================================*/
void sns_sam_time_send_sync_req(void);

/*=========================================================================
  FUNCTION:  sns_sam_process_time_response
  =========================================================================*/
/*!
  @brief Process the response received from time service

  @param[i]   msgPtr        pointer to message
  @param[i]   msgHdr        pointer to message header

  @return   SNS error code
*/
/*=======================================================================*/
sns_err_code_e sns_sam_process_time_response(
    const void             *msgPtr,
    const sns_smr_header_s *msgHdr);

/*=========================================================================
  FUNCTION:  sns_sam_process_reg_data
  =========================================================================*/
/*!
  @brief Process data received from registry

  @param[i] regItemType - registry item type
  @param[i] regItemId - registry item identifier
  @param[i] regDataLen - registry data length
  @param[i] regDataPtr - registry data pointer

  @return None
*/
/*=======================================================================*/
void sns_sam_process_reg_data(
   sns_sam_reg_item_type_e regItemType,
   uint16_t                regItemId,
   uint32_t                regDataLen,
   const uint8_t           *regDataPtr);


/*---------------------------------------------------------------------------
* Target Dependent Function Declarations
* -------------------------------------------------------------------------*/

/*=========================================================================
  FUNCTION:  sns_sam_init_gpios
  =========================================================================*/
/*!
  @brief Initialize GPIOs

  @return None
*/
/*=======================================================================*/
void sns_sam_init_gpios(void);

/*=========================================================================
  FUNCTION:  sns_sam_update_power_vote
  =========================================================================*/
/*!
  @brief Update SAM power vote to power module

  @param[i] clientReqPtr: pointer to client request
  @param[i] addClientReq: indication if request is to add client

  @return None
*/
/*=======================================================================*/
void sns_sam_update_power_vote(
   const sns_sam_client_req_s *clientReqPtr,
   bool                       addClientReq);

/*=========================================================================
  FUNCTION:  sns_sam_sensor_data_stop_ind
  =========================================================================*/
/*!
  @brief Data request stop indication

  @param[i] dataReqId: index to data request in database

  @return None
*/
/*=======================================================================*/
void sns_sam_sensor_data_stop_ind(
   uint8_t dataReqId);

/*=========================================================================
  FUNCTION:  sns_sam_process_smgr_mot_int_resp
  =========================================================================*/
/*!
  @brief Process motion interrupt registration/deregistration response

  @param[i] smgrRespPtr: Pointer to motion interrupt registration
            response message from sensors manager

  @return None
*/
/*=======================================================================*/
void sns_sam_process_smgr_mot_int_resp(
   const void *smgrRespPtr);

/*=========================================================================
  FUNCTION:  sns_sam_process_smgr_mot_int_ind
  =========================================================================*/
/*!
  @brief Process motion interrupt indication for a specific target

  @param[i] smgrIndPtr: Pointer to motion interrupt indication message
            from sensors manager

  @return algorithm service ID associated with the message
*/
/*=======================================================================*/
uint8_t sns_sam_process_smgr_mot_int_ind(
   const void *smgrIndPtr);

/*=========================================================================
  FUNCTION:  sns_sam_reg_init_timer
  =========================================================================*/
/*!
  @brief Register timer for for SAM initialization

  @param[i] sigEventFlags: Event signal flags
  @param[i] timeout: timeout value in microseconds

  @return Sensors error code
*/
/*=======================================================================*/
sns_err_code_e sns_sam_reg_init_timer(
   OS_FLAG_GRP *sigEventFlags,
   uint32_t timeout);

/*=========================================================================
  FUNCTION:  sns_sam_dereg_init_timer
  =========================================================================*/
/*!
  @brief Deregister timer for SAM initialization

  @return Sensors error code
*/
/*=======================================================================*/
sns_err_code_e sns_sam_dereg_init_timer(void);

/*=========================================================================
  FUNCTION:  sns_sam_timer_get_remaining_time
  =========================================================================*/
/*!
  @brief Gets the timer remaining duration in microseconds

  @param[i] clientReqId: client request id
  @param[o] remaining: remaining duration
 
  @return Sensors error code
*/
/*=======================================================================*/
sns_err_code_e sns_sam_timer_get_remaining_time(
   uint8_t clientReqId, uint32_t *remaining);

/*=========================================================================
  FUNCTION:  sns_sam_req_reg_data
  =========================================================================*/
/*!
  @brief Request registry data

  @param[i] regItemType: Registry item type (single / group)
  @param[i] regItemId: Registry item identifier

  @return Sensors error code
*/
/*=======================================================================*/
sns_err_code_e sns_sam_req_reg_data(
   sns_sam_reg_item_type_e regItemType,
   uint32_t                regItemId);

/*=========================================================================
  FUNCTION:  sns_sam_get_registry_read_resp
  =========================================================================*/
/*!
  @brief Gets response to registry read request

  @detail
  Waits for a maximum of tiemout microseconds to get and process response
  to one registry read request

  @param[i] timeout: time in microseconds to wait for response

  @return None
*/
/*=======================================================================*/
void sns_sam_get_registry_read_resp(
   uint32_t timeout);

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
   sns_sam_algo_inst_s *algoInstPtr,
   const void          *clientReqMsgPtr,
   sns_smr_header_s    *msgHdrPtr);

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
   uint8_t          instanceId,
   sns_smr_header_s *msgHdrPtr);

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
   const void                         *clientReqMsgPtr);

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
   sns_sam_algo_inst_s *algoInstPtr,
   uint8_t             clientId);

/*=========================================================================
  FUNCTION:  sns_sam_process_one_shot_algo_report
  =========================================================================*/
/*!
  @brief Process one-shot report from specified algorithm

  @param[i] clientReqId: index to the client request in the database
  @param[i] algoRptPtr: pointer to algorithm report

  @return Sensors error code
*/
/*=======================================================================*/
void sns_sam_process_one_shot_algo_report(
   uint8_t clientReqId,
   const sns_sam_algo_rpt_s *algoRptPtr);

/*=========================================================================
  FUNCTION:  sns_sam_get_sensor_info
  =========================================================================*/
/*!
  @brief Get sensor information from sensor manager

  @param[i] sigEventPtr: pointer to the signal group flag
  @param[o] sensorInfo: pointer to sensor information

  @return true, if response was received from SMGR; false, otherwise
*/
/*=======================================================================*/
bool sns_sam_get_sensor_info(
   OS_FLAG_GRP *sigEventPtr,
   sns_sam_sensor_info_s sensorInfo[]);

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
   sns_sam_sensor_uuid_s uuids[SNS_SAM_NUM_SENSORS]);

/*=========================================================================
  FUNCTION:  sns_sam_is_sensor_report_rate_available
  =========================================================================*/
/*!
  @brief    Detects sensor report rate availability in Registry

  @param[i] algoSvcId: algorithm service ID

  @return   'true' if sensor report rate is expected to be available;
            'false' otherwise.
*/
/*=======================================================================*/
bool sns_sam_is_sensor_report_rate_available(
   uint8_t algoSvcId);

/*=========================================================================
  FUNCTION:  sns_sam_get_smgr_msg_req_type
  =========================================================================*/
/*!
  @brief  Determines the type of message request used to communicate with
          Sensor Manager.

  @param[i] algoSvcId: algorithm service ID

  @return  message request ID
*/
/*=======================================================================*/
uint8_t sns_sam_get_smgr_msg_req_type(
   uint8_t algoSvcId);

/*=========================================================================
  FUNCTION:  sns_sam_send_smgr_start_req
  =========================================================================*/
/*!
  @brief Send a request to sensors manager for sensor data

  @param[i] dataReqId: Index of data request in database
  @param[i] algoSvcId: algorithm service ID

  @return Sensors error code
*/
/*=======================================================================*/
sns_err_code_e sns_sam_send_smgr_start_req(
   uint8_t dataReqId,
   uint8_t algoSvcId);

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
   uint8_t dataReqType);

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
   const void* currOutputPtr );

/*=========================================================================
  FUNCTION:  sns_sam_data_req_dbase_acc
  =========================================================================*/
/*!
  @brief Accessor function for the sns_sam_data_req_dbase array.

  @param[i] index: Index into the request database.

  @return Database entry, or NULL, if index is out of bounds.
*/
/*=======================================================================*/
sns_sam_data_req_s* sns_sam_data_req_dbase_acc(
    int32_t index);

/*=========================================================================
  FUNCTION:  sns_sam_sig_event_acc
  =========================================================================*/
OS_FLAG_GRP* sns_sam_sig_event_acc(void);

/*=========================================================================
  FUNCTION:  sns_sam_algo_dbase_acc
  =========================================================================*/
sns_sam_algo_s* sns_sam_algo_dbase_acc(
    int32_t index);

/*=========================================================================
  FUNCTION:  sns_sam_process_client_req
  =========================================================================*/
sns_err_code_e sns_sam_process_client_req(
   const void           *clientReqMsgPtr,
   sns_sam_mr_conn_hndl mrClntId,
   void                 **clientRespMsgPtr);

/*=========================================================================
  FUNCTION:  sns_sam_report_client_error
  =========================================================================*/
void sns_sam_report_client_error(
   const void     *clientReqMsgPtr,
   void           **clientRespMsgPtr,
   sns_err_code_e errCode);

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
   uint8_t             algoInstId,
   sns_sam_algo_inst_s *algoInstPtr);

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
   uint8_t    algoSvcId,
   const void *clientReqMsgPtr);

/*=========================================================================
  FUNCTION:  sns_sam_get_algo_inst_handle
  =========================================================================*/
/*!
  @brief Get the handle to the specified algorithm instance

  @param[i] algoInstId: index to the algorithm instance in the database

  @return handle to the specified algorithm instance if found,
          NULL otherwise
*/
/*=======================================================================*/
sns_sam_algo_inst_s* sns_sam_get_algo_inst_handle(
   uint8_t algoInstId);

/*=========================================================================
  FUNCTION:  sns_sam_process_algo_disable_req
  =========================================================================*/
/*!
  @brief Processes the disable request for specified algorithm

  @param[i] algoInstId: algorithm instance id
  @param[i] algoIndex: index of algorithm in algo database
  @param[i] clientReqId: client request id id

  @return Sensors error code
*/
/*=======================================================================*/
sns_err_code_e sns_sam_process_algo_disable_req(
   uint8_t algoInstId,
   uint8_t algoIndex,
   uint8_t clientReqId);

/*=========================================================================
  FUNCTION:  sns_sam_find_client_req
  =========================================================================*/
uint8_t sns_sam_find_client_req(
    const sns_smr_header_s *msgHdrPtr,
    sns_sam_mr_conn_hndl   mrClntId);

/*=========================================================================
  FUNCTION:  sns_sam_get_client_req_handle
  =========================================================================*/
/*!
  @brief Get the handle to the specified client request

  @param[i] clientReqId: index to the client request in the database

  @return handle to the specified client request if found,
          NULL otherwise
*/
/*=======================================================================*/
sns_sam_client_req_s* sns_sam_get_client_req_handle(
   uint8_t clientReqId);

/*=========================================================================
  FUNCTION:  sns_sam_find_data_req_for_query
  =========================================================================*/
/*!
  @brief Searches the active sensor data request database for an instance
  with the same algorithm instance ID associated with a query request.

  @param[i] algoInstId: algorithm instance ID

  @return  Index to data request matching the specified configuration
           SNS_SAM_INVALID_ID if match is not found
*/
/*=======================================================================*/
uint8_t sns_sam_find_data_req_for_query(
    uint8_t algoInstId);

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
   bool* notifySuspend);

/*=========================================================================
  FUNCTION:  sns_sam_get_modem_info
  =========================================================================*/
/*!
  @brief Get information from modem
         Specifically queries the modem to find out if mulitple RF scenarios
         are supported.

  @return none
*/
/*=======================================================================*/
void sns_sam_get_modem_info(void);

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
   const void* clientReqMsgPtr);

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
   uint8_t clientReqId);

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
   const void* clientReqMsgPtr);

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
   const void* clientReqMsgPtr);

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
   uint8_t algoSvcId);

/*=========================================================================
 FUNCTION:  sns_sam_detect_smgr_buffering
  =========================================================================*/
/*!
  @brief  Detects support for Buffering in Sensor Manager.

  @return  true, if SMGR supports buffering; false, otherwise
*/
/*=======================================================================*/
bool sns_sam_detect_smgr_buffering(
   OS_FLAG_GRP *sigEventPtr);

/*========================================================================
  FUNCTION:  sns_sam_get_registry_version
  =========================================================================*/
/*!
  @brief  Get registry version to check if default sensor report rates are
          available.

  @return  registry version, 0 if unavailable
*/
/*=======================================================================*/
uint32_t sns_sam_get_registry_version(
   OS_FLAG_GRP *sigEventPtr);

/*=========================================================================
  FUNCTION:  sns_sam_find_max_sample_rate
  =========================================================================*/
/*!
  @brief Finds max sample rate in a data request

  @param[i] dataReqId: Index of data request in data request database

  @return sample rate in Hz (Q16 format)
*/
/*=======================================================================*/
int32_t sns_sam_find_max_sample_rate(
   const uint8_t dataReqId);


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
bool sns_sam_on_change_report_requirement(
   uint8_t algoSvcId);

/*=========================================================================
  FUNCTION:  sns_sam_reg_timer
  =========================================================================*/
/*!
  @brief Register timer for client reports

  @param[i] clientReqId: client request id
  @param[i] period: timer period

  @return Sensors error code
*/
/*=======================================================================*/
sns_err_code_e sns_sam_reg_timer(
   uint32_t clientReqId,
   uint32_t period);

/*=========================================================================
  FUNCTION:  sns_sam_dereg_timer
  =========================================================================*/
/*!
  @brief Deregister timer

  @param[i] clientReqId: client request id

  @return Sensors error code
*/
/*=======================================================================*/
sns_err_code_e sns_sam_dereg_timer(
   uint8_t clientReqId);

/*=========================================================================
  FUNCTION:  sns_sam_process_batch_req
  =========================================================================*/
/*!
  @brief Processes a batch request

  @param[i] clientReqId: client request id
  @param[i] batchPeriod: requested batch period
  @param[i] batchSize: batch size
  @param[i] wakeClient: indicates if client should be woken up when FIFO
                        is full

  @return   Sensors error code
*/
/*=======================================================================*/
sns_err_code_e sns_sam_process_batch_req(
   uint8_t clientReqId,
   int32_t batchPeriod,
   uint32_t batchSize,
   bool wakeClient);

/*=========================================================================
  FUNCTION:  sns_sam_proc_upd_batch_period_req
  =========================================================================*/
/*!
  @brief Processes an update batch period request

  @param[i] clientReqId: client request id
  @param[i] activeBatchPeriod: requested active batch period

  @return   Sensors error code
*/
/*=======================================================================*/
sns_err_code_e sns_sam_proc_upd_batch_period_req(
   uint8_t clientReqId,
   int32_t activeBatchPeriod);

/*=========================================================================
  FUNCTION:  sns_sam_send_pending_batch_inds
  =========================================================================*/
/*!
  @brief Send pending batch indications to specific processor

  @return None
*/
/*=======================================================================*/
void sns_sam_send_pending_batch_inds(
   sns_proc_type_e_v01 procType );

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
   void** batchItemPtr);

/*=========================================================================
  FUNCTION:  sns_sam_set_qmd_report_gpio
  =========================================================================*/
/*!
  @brief Set QMD report GPIO. Pulls the GPIO up when device is in motion.
  Pulls it low when in rest.

  @param[i] motionState: current QMD motion state

  @return None
*/
/*=======================================================================*/
void sns_sam_set_qmd_report_gpio(
   int32_t motionState);

/*=========================================================================
  FUNCTION:  sns_sam_set_qmd_result_gpio
  =========================================================================*/
/*!
  @brief Set QMD result GPIO. Pulls the GPIO up when device is in motion.
  Pulls it low when in rest.

  @param[i] motionState: current QMD motion state

  @return None
*/
/*=======================================================================*/
void sns_sam_set_qmd_result_gpio(
   int32_t motionState);

/*=========================================================================
  FUNCTION:  sns_sam_motion_state_start
  =========================================================================*/
/*!
  @brief Initialize the motion state

  @param[i] algoSvcId: algorithm service ID
  @param[i] motionState: new motion state of device

  @return None
*/
/*=======================================================================*/
void sns_sam_motion_state_start(
   uint8_t algoSvcId,
   uint8_t dataReqId);

/*=========================================================================
  FUNCTION:  sns_sam_motion_state_update
  =========================================================================*/
/*!
  @brief Update the motion state

  @param[i] algoSvcId: algorithm service ID
  @param[i] motionState: new motion state of device

  @return None
*/
/*=======================================================================*/
void sns_sam_motion_state_update(
   uint8_t algoSvcId,
   sns_sam_motion_state_e_v01 motionState);

/*=========================================================================
  FUNCTION:  sns_sam_motion_client_update
  =========================================================================*/
/*!
  @brief Update client count for motion state

  @param[i] addClient: true if client is to be added,
                       false if client is to be removed

  @return None
*/
/*=======================================================================*/
void sns_sam_motion_client_update(
   bool addClient);

#endif /*#ifndef SNS_SAM_PRIV_H*/
