#ifndef QDSSC_SERVICE_01_H
#define QDSSC_SERVICE_01_H
/**
  @file qualcomm_debug_subsystem_control_v01.h

  @brief This is the public header file which defines the qdssc service Data structures.

  This header file defines the types and structures that were defined in
  qdssc. It contains the constant values defined, enums, structures,
  messages, and service message IDs (in that order) Structures that were
  defined in the IDL as messages contain mandatory elements, optional
  elements, a combination of mandatory and optional elements (mandatory
  always come before optionals in the structure), or nothing (null message)

  An optional element in a message is preceded by a uint8_t value that must be
  set to true if the element is going to be included. When decoding a received
  message, the uint8_t values will be set to true or false by the decode
  routine, and should be checked before accessing the values that they
  correspond to.

  Variable sized arrays are defined as static sized arrays with an unsigned
  integer (32 bit) preceding it that must be set to the number of elements
  in the array that are valid. For Example:

  uint32_t test_opaque_len;
  uint8_t test_opaque[16];

  If only 4 elements are added to test_opaque[] then test_opaque_len must be
  set to 4 before sending the message.  When decoding, the _len value is set 
  by the decode routine and should be checked so that the correct number of
  elements in the array will be accessed.

*/
/*====*====*====*====*====*====*====*====*====*====*====*====*====*====*====*
  Copyright (c) 2014 Qualcomm Technologies, Inc.
  All rights reserved.
  Confidential and Proprietary - Qualcomm Technologies, Inc.


  $Header: //components/rel/qmimsgs.adsp/2.6.1/qdssc/api/qualcomm_debug_subsystem_control_v01.h#1 $
 *====*====*====*====*====*====*====*====*====*====*====*====*====*====*====*/
/*====*====*====*====*====*====*====*====*====*====*====*====*====*====*====* 
 *THIS IS AN AUTO GENERATED FILE. DO NOT ALTER IN ANY WAY
 *====*====*====*====*====*====*====*====*====*====*====*====*====*====*====*/

/* This file was generated with Tool version 6.7 
   It was generated on: Tue Feb 18 2014 (Spin 1)
   From IDL File: qualcomm_debug_subsystem_control_v01.idl */

/** @defgroup qdssc_qmi_consts Constant values defined in the IDL */
/** @defgroup qdssc_qmi_msg_ids Constant values for QMI message IDs */
/** @defgroup qdssc_qmi_enums Enumerated types used in QMI messages */
/** @defgroup qdssc_qmi_messages Structures sent as QMI messages */
/** @defgroup qdssc_qmi_aggregates Aggregate types used in QMI messages */
/** @defgroup qdssc_qmi_accessor Accessor for QMI service object */
/** @defgroup qdssc_qmi_version Constant values for versioning information */

#include <stdint.h>
#include "qmi_idl_lib.h"
#include "common_v01.h"


#ifdef __cplusplus
extern "C" {
#endif

/** @addtogroup qdssc_qmi_version
    @{
  */
/** Major Version Number of the IDL used to generate this file */
#define QDSSC_V01_IDL_MAJOR_VERS 0x01
/** Revision Number of the IDL used to generate this file */
#define QDSSC_V01_IDL_MINOR_VERS 0x00
/** Major Version Number of the qmi_idl_compiler used to generate this file */
#define QDSSC_V01_IDL_TOOL_VERS 0x06
/** Maximum Defined Message ID */
#define QDSSC_V01_MAX_MESSAGE_ID 0x002D
/**
    @}
  */


/** @addtogroup qdssc_qmi_consts 
    @{ 
  */

/** 

 SW event tag format: mmddyyyyhhmm */
#define QDSSC_SWEVT_TAG_MAX_LEN_V01 12
/**
    @}
  */

/** @addtogroup qdssc_qmi_enums
    @{
  */
typedef enum {
  QDSSC_SVC_INSTANCE_ID_ENUM_TYPE_MIN_ENUM_VAL_V01 = -2147483647, /**< To force a 32 bit signed enum.  Do not change or use*/
  QDSSC_SVC_INSTANCE_ID_UNKNOWN_V01 = 0, /**<  Unknown */
  QDSSC_SVC_INSTANCE_ID_APPS_V01 = 1, /**<  Apps */
  QDSSC_SVC_INSTANCE_ID_MODEM_V01 = 2, /**<  Modem */
  QDSSC_SVC_INSTANCE_ID_WCN_V01 = 3, /**<  WCN/Pronto */
  QDSSC_SVC_INSTANCE_ID_RPM_V01 = 4, /**<  RPM */
  QDSSC_SVC_INSTANCE_ID_ADSP_V01 = 5, /**<  ADSP */
  QDSSC_SVC_INSTANCE_ID_VENUS_V01 = 6, /**<  Venus */
  QDSSC_SVC_INSTANCE_ID_GNSS_V01 = 7, /**<  GNSS */
  QDSSC_SVC_INSTANCE_ID_SENSOR_V01 = 8, /**<  Sensor */
  QDSSC_SVC_INSTANCE_ID_AUDIO_V01 = 9, /**<  Audio */
  QDSSC_SVC_INSTANCE_ID_VPU_V01 = 10, /**<  Maple */
  QDSSC_SVC_INSTANCE_ID_ENUM_TYPE_MAX_ENUM_VAL_V01 = 2147483647 /**< To force a 32 bit signed enum.  Do not change or use*/
}qdssc_svc_instance_id_enum_type_v01;
/**
    @}
  */

/** @addtogroup qdssc_qmi_enums
    @{
  */
typedef enum {
  QDSSC_SWT_OUTPUT_STATE_ENUM_TYPE_MIN_ENUM_VAL_V01 = -2147483647, /**< To force a 32 bit signed enum.  Do not change or use*/
  QDSSC_SWT_OUTPUT_STATE_DISABLED_V01 = 0, /**<  Disabled */
  QDSSC_SWT_OUTPUT_STATE_ENABLED_V01 = 1, /**<  Enabled */
  QDSSC_SWT_OUTPUT_STATE_ENUM_TYPE_MAX_ENUM_VAL_V01 = 2147483647 /**< To force a 32 bit signed enum.  Do not change or use*/
}qdssc_swt_output_state_enum_type_v01;
/**
    @}
  */

typedef struct {
  /* This element is a placeholder to prevent the declaration of 
     an empty struct.  DO NOT USE THIS FIELD UNDER ANY CIRCUMSTANCE */
  char __placeholder;
}qdssc_get_swt_req_msg_v01;

/** @addtogroup qdssc_qmi_messages
    @{
  */
/** Response Message; Get the state of SW tracing on the processor. This state reflect
           the global control of all SW instrumented trace. */
typedef struct {

  /* Mandatory */
  /*  Result Code */
  qmi_response_type_v01 resp;
  /**<   Standard response type.*/

  /* Optional */
  /*  SW Trace Output State */
  uint8_t state_valid;  /**< Must be set to true if state is being passed */
  qdssc_swt_output_state_enum_type_v01 state;
  /**<   Present when result code in response is QMI_RESULT_SUCCESS.
 Values:
      - QDSSC_SWT_OUTPUT_STATE_DISABLED (0) --  Disabled
      - QDSSC_SWT_OUTPUT_STATE_ENABLED (1) --  Enabled
 */
}qdssc_get_swt_resp_msg_v01;  /* Message */
/**
    @}
  */

/** @addtogroup qdssc_qmi_messages
    @{
  */
/** Request Message; Enable or disable all SW instrumented tracing on the processor. */
typedef struct {

  /* Mandatory */
  /*  SW Trace Output State */
  qdssc_swt_output_state_enum_type_v01 state;
  /**<   State to configure SW trace output.
 Values:
      - QDSSC_SWT_OUTPUT_STATE_DISABLED (0) --  Disabled
      - QDSSC_SWT_OUTPUT_STATE_ENABLED (1) --  Enabled
 */
}qdssc_set_swt_req_msg_v01;  /* Message */
/**
    @}
  */

/** @addtogroup qdssc_qmi_messages
    @{
  */
/** Response Message; Enable or disable all SW instrumented tracing on the processor. */
typedef struct {

  /* Mandatory */
  /*  Result Code */
  qmi_response_type_v01 resp;
  /**<   Standard response type.*/
}qdssc_set_swt_resp_msg_v01;  /* Message */
/**
    @}
  */

/** @addtogroup qdssc_qmi_enums
    @{
  */
typedef enum {
  QDSSC_ENTITY_ENUM_TYPE_MIN_ENUM_VAL_V01 = -2147483647, /**< To force a 32 bit signed enum.  Do not change or use*/
  QDSSC_ENTITY_NONE_V01 = 0, /**<  None */
  QDSSC_ENTITY_TDS_V01 = 1, /**<  Standard trace */
  QDSSC_ENTITY_ULOG_V01 = 11, /**<  Ulog */
  QDSSC_ENTITY_PROF_V01 = 12, /**<  Prof */
  QDSSC_ENTITY_DIAG_V01 = 13, /**<  Diag */
  QDSSC_ENTITY_ENUM_TYPE_MAX_ENUM_VAL_V01 = 2147483647 /**< To force a 32 bit signed enum.  Do not change or use*/
}qdssc_entity_enum_type_v01;
/**
    @}
  */

/** @addtogroup qdssc_qmi_enums
    @{
  */
typedef enum {
  QDSSC_ENTITY_STATE_ENUM_TYPE_MIN_ENUM_VAL_V01 = -2147483647, /**< To force a 32 bit signed enum.  Do not change or use*/
  QDSSC_ENTITY_STATE_DISABLED_V01 = 0, /**<  Disabled */
  QDSSC_ENTITY_STATE_ENABLED_V01 = 1, /**<  Enabled */
  QDSSC_ENTITY_STATE_ENUM_TYPE_MAX_ENUM_VAL_V01 = 2147483647 /**< To force a 32 bit signed enum.  Do not change or use*/
}qdssc_entity_state_enum_type_v01;
/**
    @}
  */

/** @addtogroup qdssc_qmi_messages
    @{
  */
/** Request Message; Get the state of SW tracing from an entity on the processor. */
typedef struct {

  /* Mandatory */
  /*  Entity ID */
  qdssc_entity_enum_type_v01 entity_id;
  /**<   Entity value associated with a type of SW trace.
 Values:
      - QDSSC_ENTITY_NONE (0) --  None
      - QDSSC_ENTITY_TDS (1) --  Standard trace
      - QDSSC_ENTITY_ULOG (11) --  Ulog
      - QDSSC_ENTITY_PROF (12) --  Prof
      - QDSSC_ENTITY_DIAG (13) --  Diag
 */
}qdssc_get_entity_req_msg_v01;  /* Message */
/**
    @}
  */

/** @addtogroup qdssc_qmi_messages
    @{
  */
/** Response Message; Get the state of SW tracing from an entity on the processor. */
typedef struct {

  /* Mandatory */
  /*  Result Code */
  qmi_response_type_v01 resp;
  /**<   Standard response type.*/

  /* Optional */
  /*  Entity State */
  uint8_t state_valid;  /**< Must be set to true if state is being passed */
  qdssc_entity_state_enum_type_v01 state;
  /**<   State of the entity's SW trace output.
 Values:
      - QDSSC_ENTITY_STATE_DISABLED (0) --  Disabled
      - QDSSC_ENTITY_STATE_ENABLED (1) --  Enabled
 */
}qdssc_get_entity_resp_msg_v01;  /* Message */
/**
    @}
  */

/** @addtogroup qdssc_qmi_messages
    @{
  */
/** Request Message; Enable or disable SW trace from an entity on the processor. */
typedef struct {

  /* Mandatory */
  /*  Entity ID */
  qdssc_entity_enum_type_v01 entity_id;
  /**<   Entity value associated with a type of SW trace*/

  /* Mandatory */
  /*  Entity State */
  qdssc_entity_state_enum_type_v01 state;
  /**<   State to configure SW tracing associated with the entity.
 Values:
      - QDSSC_ENTITY_STATE_DISABLED (0) --  Disabled
      - QDSSC_ENTITY_STATE_ENABLED (1) --  Enabled
 */
}qdssc_set_entity_req_msg_v01;  /* Message */
/**
    @}
  */

/** @addtogroup qdssc_qmi_messages
    @{
  */
/** Response Message; Enable or disable SW trace from an entity on the processor. */
typedef struct {

  /* Mandatory */
  /*  Result Code */
  qmi_response_type_v01 resp;
  /**<   Standard response type.*/
}qdssc_set_entity_resp_msg_v01;  /* Message */
/**
    @}
  */

typedef struct {
  /* This element is a placeholder to prevent the declaration of 
     an empty struct.  DO NOT USE THIS FIELD UNDER ANY CIRCUMSTANCE */
  char __placeholder;
}qdssc_get_entity_all_req_msg_v01;

/** @addtogroup qdssc_qmi_messages
    @{
  */
/** Response Message; Get the state of SW tracing for all entities on the processor. */
typedef struct {

  /* Mandatory */
  /*  Result Code */
  qmi_response_type_v01 resp;
  /**<   Standard response type.*/

  /* Optional */
  /*  Mask of Entity States */
  uint8_t mask_valid;  /**< Must be set to true if mask is being passed */
  uint32_t mask[8];
  /**<   Bit mask of the state of SW trace output for all entities.
    */
}qdssc_get_entity_all_resp_msg_v01;  /* Message */
/**
    @}
  */

/** @addtogroup qdssc_qmi_messages
    @{
  */
/** Request Message; Enable or disable SW trace from all entities on the processor. */
typedef struct {

  /* Mandatory */
  /*  Entity State */
  qdssc_entity_state_enum_type_v01 state;
  /**<   State to configure SW tracing of all entities.
 Values:
      - QDSSC_ENTITY_STATE_DISABLED (0) --  Disabled
      - QDSSC_ENTITY_STATE_ENABLED (1) --  Enabled
 */
}qdssc_set_entity_all_req_msg_v01;  /* Message */
/**
    @}
  */

/** @addtogroup qdssc_qmi_messages
    @{
  */
/** Response Message; Enable or disable SW trace from all entities on the processor. */
typedef struct {

  /* Mandatory */
  /*  Result Code */
  qmi_response_type_v01 resp;
  /**<   Standard response type.*/
}qdssc_set_entity_all_resp_msg_v01;  /* Message */
/**
    @}
  */

typedef struct {
  /* This element is a placeholder to prevent the declaration of 
     an empty struct.  DO NOT USE THIS FIELD UNDER ANY CIRCUMSTANCE */
  char __placeholder;
}qdssc_get_swevt_tag_req_msg_v01;

/** @addtogroup qdssc_qmi_messages
    @{
  */
/** Response Message; Get the SW event tag of the processor. */
typedef struct {

  /* Mandatory */
  /*  Result Code */
  qmi_response_type_v01 resp;
  /**<   Standard response type.*/

  /* Optional */
  /*  SW Event Tag String */
  uint8_t tag_str_valid;  /**< Must be set to true if tag_str is being passed */
  char tag_str[QDSSC_SWEVT_TAG_MAX_LEN_V01 + 1];
}qdssc_get_swevt_tag_resp_msg_v01;  /* Message */
/**
    @}
  */

/** @addtogroup qdssc_qmi_enums
    @{
  */
typedef enum {
  QDSSC_EVENT_STATE_ENUM_TYPE_MIN_ENUM_VAL_V01 = -2147483647, /**< To force a 32 bit signed enum.  Do not change or use*/
  QDSSC_EVENT_STATE_DISABLED_V01 = 0, /**<  Disabled */
  QDSSC_EVENT_STATE_ENABLED_V01 = 1, /**<  Enabled */
  QDSSC_EVENT_STATE_ENUM_TYPE_MAX_ENUM_VAL_V01 = 2147483647 /**< To force a 32 bit signed enum.  Do not change or use*/
}qdssc_event_state_enum_type_v01;
/**
    @}
  */

/** @addtogroup qdssc_qmi_messages
    @{
  */
/** Request Message; Get the state of SW tracing for a SW event on the processor. */
typedef struct {

  /* Mandatory */
  /*  SW Event ID */
  uint32_t event_id;
  /**<   Value identifying a SW trace event. */
}qdssc_get_swevt_req_msg_v01;  /* Message */
/**
    @}
  */

/** @addtogroup qdssc_qmi_messages
    @{
  */
/** Response Message; Get the state of SW tracing for a SW event on the processor. */
typedef struct {

  /* Mandatory */
  /*  Result Code */
  qmi_response_type_v01 resp;
  /**<   Standard response type.*/

  /* Optional */
  /*  SW Event State */
  uint8_t state_valid;  /**< Must be set to true if state is being passed */
  qdssc_event_state_enum_type_v01 state;
  /**<   State of SW tracing for the event.
 Values:
      - QDSSC_EVENT_STATE_DISABLED (0) --  Disabled
      - QDSSC_EVENT_STATE_ENABLED (1) --  Enabled
 */
}qdssc_get_swevt_resp_msg_v01;  /* Message */
/**
    @}
  */

/** @addtogroup qdssc_qmi_messages
    @{
  */
/** Request Message; Enable or disable tracing of a SW event on the processor. */
typedef struct {

  /* Mandatory */
  /*  SW Event ID */
  uint32_t event_id;
  /**<   Value identifying a SW trace event. */

  /* Mandatory */
  /*  SW Event State */
  qdssc_event_state_enum_type_v01 state;
  /**<   State to configure tracing of the SW event.
 Values:
      - QDSSC_EVENT_STATE_DISABLED (0) --  Disabled
      - QDSSC_EVENT_STATE_ENABLED (1) --  Enabled
 */
}qdssc_set_swevt_req_msg_v01;  /* Message */
/**
    @}
  */

/** @addtogroup qdssc_qmi_messages
    @{
  */
/** Response Message; Enable or disable tracing of a SW event on the processor. */
typedef struct {

  /* Mandatory */
  /*  Result Code */
  qmi_response_type_v01 resp;
  /**<   Standard response type.*/
}qdssc_set_swevt_resp_msg_v01;  /* Message */
/**
    @}
  */

/** @addtogroup qdssc_qmi_enums
    @{
  */
typedef enum {
  QDSSC_RPM_SWE_LOG_ENUM_TYPE_MIN_ENUM_VAL_V01 = -2147483647, /**< To force a 32 bit signed enum.  Do not change or use*/
  QDSSC_RPM_SWE_LOG_RAM_V01 = 0, /**<  Log to RAM (memory) */
  QDSSC_RPM_SWE_LOG_QDSS_V01 = 1, /**<  Lot to QDSS */
  QDSSC_RPM_SWE_LOG_ENUM_TYPE_MAX_ENUM_VAL_V01 = 2147483647 /**< To force a 32 bit signed enum.  Do not change or use*/
}qdssc_rpm_swe_log_enum_type_v01;
/**
    @}
  */

/** @addtogroup qdssc_qmi_messages
    @{
  */
/** Request Message; Configure SW events on the RPM processor. */
typedef struct {

  /* Mandatory */
  /*  RPM's SW Event Log */
  qdssc_rpm_swe_log_enum_type_v01 log;
  /**<   Location where RPM's SW events are logged.
 Values:
      - QDSSC_RPM_SWE_LOG_RAM (0) --  Log to RAM (memory)
      - QDSSC_RPM_SWE_LOG_QDSS (1) --  Lot to QDSS
 */

  /* Mandatory */
  /*  RPM's SW Event Group */
  uint8_t group;
  /**<   Group of SW events being configured. Valid values are 0 to 15. */

  /* Mandatory */
  /*  RPM's SW Events Bitmask */
  uint64_t bitmask;
  /**<    Bitmask of SW events within the group to be disabled (bit value 0)
          and enabled (bit value 1). Bit position corresponds to event within
          the group. For example: bit position 0 (lsb) corresponds to
          event 0 in group N where "group" value = N.
    */
}qdssc_set_rpm_swe_req_msg_v01;  /* Message */
/**
    @}
  */

/** @addtogroup qdssc_qmi_messages
    @{
  */
/** Response Message; Configure SW events on the RPM processor. */
typedef struct {

  /* Mandatory */
  /*  Result Code */
  qmi_response_type_v01 resp;
  /**<   Standard response type.*/
}qdssc_set_rpm_swe_resp_msg_v01;  /* Message */
/**
    @}
  */

/** @addtogroup qdssc_qmi_messages
    @{
  */
/** Request Message; Configure device for a HW event. */
typedef struct {

  /* Mandatory */
  /*  Register Address */
  uint32_t regaddr;
  /**<   Address of HW event register to be set. */

  /* Mandatory */
  /*  Register Value */
  uint32_t value;
  /**<   Configuration value to set register to. */
}qdssc_set_hwe_reg_req_msg_v01;  /* Message */
/**
    @}
  */

/** @addtogroup qdssc_qmi_messages
    @{
  */
/** Response Message; Configure device for a HW event. */
typedef struct {

  /* Mandatory */
  /*  Result Code */
  qmi_response_type_v01 resp;
  /**<   Standard response type.*/
}qdssc_set_hwe_reg_resp_msg_v01;  /* Message */
/**
    @}
  */

/** @addtogroup qdssc_qmi_enums
    @{
  */
typedef enum {
  QDSSC_ETM_STATE_ENUM_TYPE_MIN_ENUM_VAL_V01 = -2147483647, /**< To force a 32 bit signed enum.  Do not change or use*/
  QDSSC_ETM_STATE_DISABLED_V01 = 0, /**<  Disabled */
  QDSSC_ETM_STATE_ENABLED_V01 = 1, /**<  Enabled */
  QDSSC_ETM_STATE_ENUM_TYPE_MAX_ENUM_VAL_V01 = 2147483647 /**< To force a 32 bit signed enum.  Do not change or use*/
}qdssc_etm_state_enum_type_v01;
/**
    @}
  */

typedef struct {
  /* This element is a placeholder to prevent the declaration of 
     an empty struct.  DO NOT USE THIS FIELD UNDER ANY CIRCUMSTANCE */
  char __placeholder;
}qdssc_get_etm_req_msg_v01;

/** @addtogroup qdssc_qmi_messages
    @{
  */
/** Response Message; Get the state of ETM's trace for the processor. */
typedef struct {

  /* Mandatory */
  /*  Result Code */
  qmi_response_type_v01 resp;
  /**<   Standard response type.*/

  /* Optional */
  /*  ETM Output State */
  uint8_t state_valid;  /**< Must be set to true if state is being passed */
  qdssc_etm_state_enum_type_v01 state;
  /**<   Present when the result code is QMI_RESULT_SUCCESS.
 Values:
      - QDSSC_ETM_STATE_DISABLED (0) --  Disabled
      - QDSSC_ETM_STATE_ENABLED (1) --  Enabled
 */
}qdssc_get_etm_resp_msg_v01;  /* Message */
/**
    @}
  */

/** @addtogroup qdssc_qmi_messages
    @{
  */
/** Request Message; Enable or disable ETM's trace on the processor. */
typedef struct {

  /* Mandatory */
  /*  ETM Output State */
  qdssc_etm_state_enum_type_v01 state;
  /**<   State to configure ETM's output.
 Values:
      - QDSSC_ETM_STATE_DISABLED (0) --  Disabled
      - QDSSC_ETM_STATE_ENABLED (1) --  Enabled
 */
}qdssc_set_etm_req_msg_v01;  /* Message */
/**
    @}
  */

/** @addtogroup qdssc_qmi_messages
    @{
  */
/** Response Message; Enable or disable ETM's trace on the processor. */
typedef struct {

  /* Mandatory */
  /*  Result Code */
  qmi_response_type_v01 resp;
  /**<   Standard response type.*/
}qdssc_set_etm_resp_msg_v01;  /* Message */
/**
    @}
  */

/** @addtogroup qdssc_qmi_messages
    @{
  */
/** Request Message; Enable or disable ETM's trace on the RPM processor. */
typedef struct {

  /* Mandatory */
  /*  RPM's ETM Output State */
  qdssc_etm_state_enum_type_v01 state;
  /**<   State to configure ETM output of the RPM.
 Values:
      - QDSSC_ETM_STATE_DISABLED (0) --  Disabled
      - QDSSC_ETM_STATE_ENABLED (1) --  Enabled
 */
}qdssc_set_rpm_etm_req_msg_v01;  /* Message */
/**
    @}
  */

/** @addtogroup qdssc_qmi_messages
    @{
  */
/** Response Message; Enable or disable ETM's trace on the RPM processor. */
typedef struct {

  /* Mandatory */
  /*  Result Code */
  qmi_response_type_v01 resp;
  /**<   Standard response type.*/
}qdssc_set_rpm_etm_resp_msg_v01;  /* Message */
/**
    @}
  */

/*Service Message Definition*/
/** @addtogroup qdssc_qmi_msg_ids
    @{
  */
#define QMI_QDSSC_GET_SWT_REQ_V01 0x0020
#define QMI_QDSSC_GET_SWT_RESP_V01 0x0020
#define QMI_QDSSC_SET_SWT_REQ_V01 0x0021
#define QMI_QDSSC_SET_SWT_RESP_V01 0x0021
#define QMI_QDSSC_GET_ENTITY_REQ_V01 0x0022
#define QMI_QDSSC_GET_ENTITY_RESP_V01 0x0022
#define QMI_QDSSC_SET_ENTITY_REQ_V01 0x0023
#define QMI_QDSSC_SET_ENTITY_RESP_V01 0x0023
#define QMI_QDSSC_GET_ENTITY_ALL_REQ_V01 0x0024
#define QMI_QDSSC_GET_ENTITY_ALL_RESP_V01 0x0024
#define QMI_QDSSC_SET_ENTITY_ALL_REQ_V01 0x0025
#define QMI_QDSSC_SET_ENTITY_ALL_RESP_V01 0x0025
#define QMI_QDSSC_GET_SWEVT_TAG_REQ_V01 0x0026
#define QMI_QDSSC_GET_SWEVT_TAG_RESP_V01 0x0026
#define QMI_QDSSC_GET_SWEVT_REQ_V01 0x0027
#define QMI_QDSSC_GET_SWEVT_RESP_V01 0x0027
#define QMI_QDSSC_SET_SWEVT_REQ_V01 0x0028
#define QMI_QDSSC_SET_SWEVT_RESP_V01 0x0028
#define QMI_QDSSC_SET_RPM_SWE_REQ_V01 0x0029
#define QMI_QDSSC_SET_RPM_SWE_RESP_V01 0x0029
#define QMI_QDSSC_SET_HWE_REG_REQ_V01 0x002A
#define QMI_QDSSC_SET_HWE_REG_RESP_V01 0x002A
#define QMI_QDSSC_GET_ETM_REQ_V01 0x002B
#define QMI_QDSSC_GET_ETM_RESP_V01 0x002B
#define QMI_QDSSC_SET_ETM_REQ_V01 0x002C
#define QMI_QDSSC_SET_ETM_RESP_V01 0x002C
#define QMI_QDSSC_SET_RPM_ETM_REQ_V01 0x002D
#define QMI_QDSSC_SET_RPM_ETM_RESP_V01 0x002D
/**
    @}
  */

/* Service Object Accessor */
/** @addtogroup wms_qmi_accessor 
    @{
  */
/** This function is used internally by the autogenerated code.  Clients should use the
   macro qdssc_get_service_object_v01( ) that takes in no arguments. */
qmi_idl_service_object_type qdssc_get_service_object_internal_v01
 ( int32_t idl_maj_version, int32_t idl_min_version, int32_t library_version );
 
/** This macro should be used to get the service object */ 
#define qdssc_get_service_object_v01( ) \
          qdssc_get_service_object_internal_v01( \
            QDSSC_V01_IDL_MAJOR_VERS, QDSSC_V01_IDL_MINOR_VERS, \
            QDSSC_V01_IDL_TOOL_VERS )
/** 
    @} 
  */


#ifdef __cplusplus
}
#endif
#endif

