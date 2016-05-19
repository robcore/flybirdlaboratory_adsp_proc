#ifndef WLS_SERVICE_01_H
#define WLS_SERVICE_01_H
/**
  @file wlan_location_service_v01.h

  @brief This is the public header file which defines the wls service Data structures.

  This header file defines the types and structures that were defined in
  wls. It contains the constant values defined, enums, structures,
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


  $Header: //components/rel/qmimsgs.adsp/2.6.1/wls/api/wlan_location_service_v01.h#1 $
 *====*====*====*====*====*====*====*====*====*====*====*====*====*====*====*/
/*====*====*====*====*====*====*====*====*====*====*====*====*====*====*====* 
 *THIS IS AN AUTO GENERATED FILE. DO NOT ALTER IN ANY WAY
 *====*====*====*====*====*====*====*====*====*====*====*====*====*====*====*/

/* This file was generated with Tool version 6.7 
   It was generated on: Sat Jun 21 2014 (Spin 0)
   From IDL File: wlan_location_service_v01.idl */

/** @defgroup wls_qmi_consts Constant values defined in the IDL */
/** @defgroup wls_qmi_msg_ids Constant values for QMI message IDs */
/** @defgroup wls_qmi_enums Enumerated types used in QMI messages */
/** @defgroup wls_qmi_messages Structures sent as QMI messages */
/** @defgroup wls_qmi_aggregates Aggregate types used in QMI messages */
/** @defgroup wls_qmi_accessor Accessor for QMI service object */
/** @defgroup wls_qmi_version Constant values for versioning information */

#include <stdint.h>
#include "qmi_idl_lib.h"
#include "common_v01.h"


#ifdef __cplusplus
extern "C" {
#endif

/** @addtogroup wls_qmi_version
    @{
  */
/** Major Version Number of the IDL used to generate this file */
#define WLS_V01_IDL_MAJOR_VERS 0x01
/** Revision Number of the IDL used to generate this file */
#define WLS_V01_IDL_MINOR_VERS 0x00
/** Major Version Number of the qmi_idl_compiler used to generate this file */
#define WLS_V01_IDL_TOOL_VERS 0x06
/** Maximum Defined Message ID */
#define WLS_V01_MAX_MESSAGE_ID 0x0026
/**
    @}
  */


/** @addtogroup wls_qmi_consts 
    @{ 
  */
#define WLS_MAX_SSID_LEN_V01 32
#define WLS_MAX_BSSID_LEN_V01 6
#define WLS_MAX_CHIP_VER_LEN_V01 31
#define WLS_MAX_VER_LEN_V01 31
#define WLS_MAX_FREQ_LIST_LEN_V01 32
#define WLS_MAX_AP_NUM_V01 24
#define WLS_MAX_COUNTRY_CODE_LEN_V01 3
#define WLS_MAX_ERR_INFO_LEN_V01 31
/**
    @}
  */

typedef uint64_t wls_ap_bitmask_t_v01;
#define WLS_AP_TX_POWER_V01 ((wls_ap_bitmask_t_v01)0x00000001ull) /**<  TX power  */
#define WLS_AP_TX_RATE_V01 ((wls_ap_bitmask_t_v01)0x00000002ull) /**<  TX rate  */
#define WLS_AP_TSF_V01 ((wls_ap_bitmask_t_v01)0x00000004ull) /**<  Timing synchronization function  */
#define WLS_AP_AGE_V01 ((wls_ap_bitmask_t_v01)0x00000008ull) /**<  Age  */
#define WLS_AP_802_11_MC_V01 ((wls_ap_bitmask_t_v01)0x00000010ull) /**<  Wi-Fi 802.11 MC  */
#define WLS_AP_MSAP_V01 ((wls_ap_bitmask_t_v01)0x00000020ull) /**<  MSAP  */
typedef uint64_t wls_sub_bitmask_t_v01;
#define WLS_SUB_EVENTS_V01 ((wls_sub_bitmask_t_v01)0x00000001ull) /**<  Wi-Fi Events  */
#define WLS_SUB_SNOOP_V01 ((wls_sub_bitmask_t_v01)0x00000002ull) /**<  Snooping  */
/** @addtogroup wls_qmi_enums
    @{
  */
typedef enum {
  WLS_SNOOP_MODE_T_MIN_ENUM_VAL_V01 = -2147483647, /**< To force a 32 bit signed enum.  Do not change or use*/
  WLS_NO_SCAN_RESULT_V01 = 0, /**<  No scan results to be sent to clients  */
  WLS_ALL_SCAN_RESULT_V01 = 1, /**<  All scan results to be sent to clients  */
  WLS_EXCLUDE_SCAN_RESULT_FOR_APSS_V01 = 2, /**<  Only those scan results not sent to APSS to be sent to clients  */
  WLS_SNOOP_MODE_T_MAX_ENUM_VAL_V01 = 2147483647 /**< To force a 32 bit signed enum.  Do not change or use*/
}wls_snoop_mode_t_v01;
/**
    @}
  */

typedef uint64_t wls_event_t_v01;
#define WLS_EVENT_HOST_STATUS_V01 ((wls_event_t_v01)0x00000001ull) /**<  WLAN host driver is ON/OFF  */
#define WLS_EVENT_FW_SVC_STATUS_V01 ((wls_event_t_v01)0x00000002ull) /**<  WLAN FW service is ON/OFF  */
#define WLS_EVENT_CONN_STATUS_V01 ((wls_event_t_v01)0x00000004ull) /**<  Connected/disconnected to an AP  */
#define WLS_EVENT_HANDOFF_V01 ((wls_event_t_v01)0x00000008ull) /**<  Handoff event  */
#define WLS_EVENT_FREQ_LIST_V01 ((wls_event_t_v01)0x00000010ull) /**<  Updated frequency list  */
/** @addtogroup wls_qmi_enums
    @{
  */
typedef enum {
  WLS_ERR_T_MIN_ENUM_VAL_V01 = -2147483647, /**< To force a 32 bit signed enum.  Do not change or use*/
  WLS_ERR_NONE_V01 = 0, /**<  No error  */
  WLS_ERR_INFO_UNAVAIL_V01 = 1, /**<  Information is unavailable  */
  WLS_ERR_INVALID_PARAM_V01 = 2, /**<  Invalid request parameter(s) detected  */
  WLS_ERR_HOST_OFF_V01 = 3, /**<  WLAN host driver is not loaded  */
  WLS_ERR_FW_SVC_OFF_V01 = 4, /**<  WLAN FW service is OFF  */
  WLS_ERR_TIMEOUT_V01 = 5, /**<  Request processing not completed within timeout value  */
  WLS_ERR_HOST_DRV_RELOADED_V01 = 6, /**<  WLAN host driver reloaded  */
  WLS_ERR_SSR_V01 = 7, /**<  WLAN sub-system restart  */
  WLS_ERR_T_MAX_ENUM_VAL_V01 = 2147483647 /**< To force a 32 bit signed enum.  Do not change or use*/
}wls_err_t_v01;
/**
    @}
  */

/** @addtogroup wls_qmi_enums
    @{
  */
typedef enum {
  WLS_WLAN_DEV_T_MIN_ENUM_VAL_V01 = -2147483647, /**< To force a 32 bit signed enum.  Do not change or use*/
  WLS_WLAN_DEV_STA_V01 = 0, /**<  WLAN device is in station mode  */
  WLS_WLAN_DEV_P2P_CLI_V01 = 1, /**<  WLAN device is in P2P client mode  */
  WLS_WLAN_DEV_ANY_V01 = 2, /**<  WLAN device is in any mode (used for subscription purpose)  */
  WLS_WLAN_DEV_T_MAX_ENUM_VAL_V01 = 2147483647 /**< To force a 32 bit signed enum.  Do not change or use*/
}wls_wlan_dev_t_v01;
/**
    @}
  */

/** @addtogroup wls_qmi_aggregates
    @{
  */
typedef struct {

  char country_code[WLS_MAX_COUNTRY_CODE_LEN_V01 + 1];
  /**<   country code */

  uint32_t freq_list_len;  /**< Must be set to # of elements in freq_list */
  uint16_t freq_list[WLS_MAX_FREQ_LIST_LEN_V01];
  /**<   frequency list (unit: KHz) */
}wls_freq_list_t_v01;  /* Type */
/**
    @}
  */

/** @addtogroup wls_qmi_aggregates
    @{
  */
typedef struct {

  char ssid[WLS_MAX_SSID_LEN_V01 + 1];
  /**<   SSID */
}wls_ssid_t_v01;  /* Type */
/**
    @}
  */

/** @addtogroup wls_qmi_aggregates
    @{
  */
typedef struct {

  char bssid[WLS_MAX_BSSID_LEN_V01];
  /**<   bssid */

  uint32_t ssid_len;  /**< Must be set to # of elements in ssid */
  char ssid[WLS_MAX_SSID_LEN_V01];
  /**<   SSID */

  uint32_t frequency;
  /**<   frequency (kHz) */

  int32_t rssi;
  /**<   Received signal strengh indication (dBm) */
}wls_ap_base_t_v01;  /* Type */
/**
    @}
  */

/** @addtogroup wls_qmi_aggregates
    @{
  */
typedef struct {

  wls_ap_base_t_v01 base;
  /**<   AP base values */

  uint8_t cur_connected;
  /**<   Is the Wi-Fi device connected to this AP currently? */

  wls_ap_bitmask_t_v01 valid_mask;
  /**<   Bitmask that indicates which fields below have valid data
 Values: \n
      - WLS_AP_TX_POWER (0x00000001) --  TX power 
      - WLS_AP_TX_RATE (0x00000002) --  TX rate 
      - WLS_AP_TSF (0x00000004) --  Timing synchronization function 
      - WLS_AP_AGE (0x00000008) --  Age 
      - WLS_AP_802_11_MC (0x00000010) --  Wi-Fi 802.11 MC 
      - WLS_AP_MSAP (0x00000020) --  MSAP 
 */

  uint32_t tx_power;
  /**<   TX power (dBm) */

  uint32_t tx_rate;
  /**<   TX rate (mbps) */

  uint64_t tsf;
  /**<   Timing synchronization function */

  uint32_t age;
  /**<   Age */

  uint8_t wifi_802_11_mc;
  /**<   RTT3 support advertised by the AP beacons */

  char msap[6];
  /**<   Mobility services advertisement protocol */
}wls_ap_t_v01;  /* Type */
/**
    @}
  */

typedef struct {
  /* This element is a placeholder to prevent the declaration of 
     an empty struct.  DO NOT USE THIS FIELD UNDER ANY CIRCUMSTANCE */
  char __placeholder;
}wls_ver_req_msg_v01;

/** @addtogroup wls_qmi_messages
    @{
  */
/** Response Message; Fetch the WLAN location service related version information */
typedef struct {

  /* Mandatory */
  /*  Result Code */
  qmi_response_type_v01 resp;
  /**<   Standard response type. Contains the following data members:
       - qmi_result_type -- QMI_RESULT_SUCCESS or QMI_RESULT_FAILURE \n
       - qmi_error_type  -- Error code. Possible error code values are described
                            in the error codes section of each message definition.
    */

  /* Optional */
  /*  WLS Version */
  uint8_t wls_version_valid;  /**< Must be set to true if wls_version is being passed */
  char wls_version[WLS_MAX_VER_LEN_V01 + 1];
  /**<   WLAN location service version */

  /* Optional */
  /*  WLAN Chipset OEM */
  uint8_t wlan_chip_oem_valid;  /**< Must be set to true if wlan_chip_oem is being passed */
  char wlan_chip_oem[WLS_MAX_CHIP_VER_LEN_V01 + 1];
  /**<   WLAN chipset manufacturer */

  /* Optional */
  /*  WLAN Chipset Name */
  uint8_t wlan_chip_name_valid;  /**< Must be set to true if wlan_chip_name is being passed */
  char wlan_chip_name[WLS_MAX_CHIP_VER_LEN_V01 + 1];
  /**<   WLAN chipset name */

  /* Optional */
  /*  WLAN Chipset ID */
  uint8_t wlan_chip_id_valid;  /**< Must be set to true if wlan_chip_id is being passed */
  uint32_t wlan_chip_id;
  /**<   WLAN chipset ID */

  /* Optional */
  /*  WLAN Host Driver Version */
  uint8_t wlan_host_ver_valid;  /**< Must be set to true if wlan_host_ver is being passed */
  char wlan_host_ver[WLS_MAX_VER_LEN_V01 + 1];
  /**<   APSS WLAN host driver version */

  /* Optional */
  /*  WLAN FW Version */
  uint8_t wlan_fw_ver_valid;  /**< Must be set to true if wlan_fw_ver is being passed */
  char wlan_fw_ver[WLS_MAX_VER_LEN_V01 + 1];
  /**<   WLAN FW version */

  /* Optional */
  /*  Error ID */
  uint8_t err_id_valid;  /**< Must be set to true if err_id is being passed */
  wls_err_t_v01 err_id;
  /**<   WLS error type, if any
 Values: \n
      - WLS_ERR_NONE (0) --  No error 
      - WLS_ERR_INFO_UNAVAIL (1) --  Information is unavailable 
      - WLS_ERR_INVALID_PARAM (2) --  Invalid request parameter(s) detected 
      - WLS_ERR_HOST_OFF (3) --  WLAN host driver is not loaded 
      - WLS_ERR_FW_SVC_OFF (4) --  WLAN FW service is OFF 
      - WLS_ERR_TIMEOUT (5) --  Request processing not completed within timeout value 
      - WLS_ERR_HOST_DRV_RELOADED (6) --  WLAN host driver reloaded 
      - WLS_ERR_SSR (7) --  WLAN sub-system restart 
 */
}wls_ver_resp_msg_v01;  /* Message */
/**
    @}
  */

/** @addtogroup wls_qmi_messages
    @{
  */
/** Request Message; Query latest WLAN location service status information */
typedef struct {

  /* Mandatory */
  /*  Request ID */
  uint32_t req_id;
  /**<   Request ID */
}wls_status_query_req_msg_v01;  /* Message */
/**
    @}
  */

/** @addtogroup wls_qmi_messages
    @{
  */
/** Response Message; Query latest WLAN location service status information */
typedef struct {

  /* Mandatory */
  /*  Result Code */
  qmi_response_type_v01 resp;
  /**<   Standard response type. Contains the following data members:
       - qmi_result_type -- QMI_RESULT_SUCCESS or QMI_RESULT_FAILURE \n
       - qmi_error_type  -- Error code. Possible error code values are described
                            in the error codes section of each message definition.
    */

  /* Optional */
  /*  Request ID */
  uint8_t req_id_valid;  /**< Must be set to true if req_id is being passed */
  uint32_t req_id;
  /**<   Request ID in the received request */
}wls_status_query_resp_msg_v01;  /* Message */
/**
    @}
  */

/** @addtogroup wls_qmi_messages
    @{
  */
/** Request Message; Issue discovery scan command and receive scan results */
typedef struct {

  /* Mandatory */
  /*  Request ID */
  uint32_t req_id;
  /**<   Request ID */

  /* Mandatory */
  /*  Frequency List */
  wls_freq_list_t_v01 freq_list;
  /**<   List of frequencies to scan */

  /* Mandatory */
  /*  Use Active Scan or Passive */
  uint8_t is_active;
  /**<   Use active or passive scan */

  /* Mandatory */
  /*  Dwell Time */
  uint32_t dwell_time_ms;
  /**<   Dwell time on each frequency in milli-seconds */

  /* Mandatory */
  /*  Scan Time-Out */
  uint32_t time_out_sec;
  /**<   Time-out on the whole scan operation in seconds */

  /* Optional */
  /*  SSID List */
  uint8_t ssid_list_valid;  /**< Must be set to true if ssid_list is being passed */
  wls_ssid_t_v01 ssid_list[WLS_MAX_AP_NUM_V01];
  /**<   List of the SSID to scan */

  /* Optional */
  /*  Use Cached Scan Results */
  uint8_t use_cached_valid;  /**< Must be set to true if use_cached is being passed */
  uint8_t use_cached;
  /**<   ignored in phase 1 */
}wls_disc_scan_req_msg_v01;  /* Message */
/**
    @}
  */

/** @addtogroup wls_qmi_messages
    @{
  */
/** Response Message; Issue discovery scan command and receive scan results */
typedef struct {

  /* Mandatory */
  /*  Result Code */
  qmi_response_type_v01 resp;
  /**<   Standard response type. Contains the following data members:
       - qmi_result_type -- QMI_RESULT_SUCCESS or QMI_RESULT_FAILURE \n
       - qmi_error_type  -- Error code. Possible error code values are described
                            in the error codes section of each message definition.
    */

  /* Optional */
  /*  Request ID */
  uint8_t req_id_valid;  /**< Must be set to true if req_id is being passed */
  uint32_t req_id;
  /**<   Request ID in the received request */
}wls_disc_scan_resp_msg_v01;  /* Message */
/**
    @}
  */

/** @addtogroup wls_qmi_messages
    @{
  */
/** Request Message; Subscribe WLAN Location Services */
typedef struct {

  /* Mandatory */
  /*  Request ID */
  uint32_t req_id;
  /**<   Request ID */

  /* Optional */
  /*  Enable or Disable Subscription */
  uint8_t is_enable_valid;  /**< Must be set to true if is_enable is being passed */
  uint8_t is_enable;
  /**<   Set to TRUE to add subscription. Set to FALSE to remove subscription */

  /* Optional */
  /*  Subscription Type */
  uint8_t sub_type_valid;  /**< Must be set to true if sub_type is being passed */
  wls_sub_bitmask_t_v01 sub_type;
  /**<   Bit masks for subscription
 Values: \n
      - WLS_SUB_EVENTS (0x00000001) --  Wi-Fi Events 
      - WLS_SUB_SNOOP (0x00000002) --  Snooping 
 */

  /* Optional */
  /*  WLAN Interface Type */
  uint8_t wlan_intf_type_valid;  /**< Must be set to true if wlan_intf_type is being passed */
  wls_wlan_dev_t_v01 wlan_intf_type;
  /**<   WLAN interface type
 Values: \n
      - WLS_WLAN_DEV_STA (0) --  WLAN device is in station mode 
      - WLS_WLAN_DEV_P2P_CLI (1) --  WLAN device is in P2P client mode 
      - WLS_WLAN_DEV_ANY (2) --  WLAN device is in any mode (used for subscription purpose) 
 */

  /* Optional */
  /*  Snoop Mode */
  uint8_t snoop_mode_valid;  /**< Must be set to true if snoop_mode is being passed */
  wls_snoop_mode_t_v01 snoop_mode;
  /**<   Snoop scan mode
 Values: \n
      - WLS_NO_SCAN_RESULT (0) --  No scan results to be sent to clients 
      - WLS_ALL_SCAN_RESULT (1) --  All scan results to be sent to clients 
      - WLS_EXCLUDE_SCAN_RESULT_FOR_APSS (2) --  Only those scan results not sent to APSS to be sent to clients 
 */
}wls_sub_req_msg_v01;  /* Message */
/**
    @}
  */

/** @addtogroup wls_qmi_messages
    @{
  */
/** Response Message; Subscribe WLAN Location Services */
typedef struct {

  /* Mandatory */
  /*  Result Code */
  qmi_response_type_v01 resp;
  /**<   Standard response type. Contains the following data members:
       - qmi_result_type -- QMI_RESULT_SUCCESS or QMI_RESULT_FAILURE \n
       - qmi_error_type  -- Error code. Possible error code values are described
                            in the error codes section of each message definition.
    */

  /* Optional */
  /*  Error ID */
  uint8_t err_id_valid;  /**< Must be set to true if err_id is being passed */
  wls_err_t_v01 err_id;
  /**<   WLS error type
 Values: \n
      - WLS_ERR_NONE (0) --  No error 
      - WLS_ERR_INFO_UNAVAIL (1) --  Information is unavailable 
      - WLS_ERR_INVALID_PARAM (2) --  Invalid request parameter(s) detected 
      - WLS_ERR_HOST_OFF (3) --  WLAN host driver is not loaded 
      - WLS_ERR_FW_SVC_OFF (4) --  WLAN FW service is OFF 
      - WLS_ERR_TIMEOUT (5) --  Request processing not completed within timeout value 
      - WLS_ERR_HOST_DRV_RELOADED (6) --  WLAN host driver reloaded 
      - WLS_ERR_SSR (7) --  WLAN sub-system restart 
 */

  /* Optional */
  /*  Request ID */
  uint8_t req_id_valid;  /**< Must be set to true if req_id is being passed */
  uint32_t req_id;
  /**<   Request ID in the received request */
}wls_sub_resp_msg_v01;  /* Message */
/**
    @}
  */

/** @addtogroup wls_qmi_messages
    @{
  */
/** Indication Message; Indication sent by the WLAN location service to inform the
                     location client the latest WLAN events & status. */
typedef struct {

  /* Optional */
  /*  Event Type */
  uint8_t event_type_valid;  /**< Must be set to true if event_type is being passed */
  wls_event_t_v01 event_type;
  /**<   WLS event type
 Values: \n
      - WLS_EVENT_HOST_STATUS (0x00000001) --  WLAN host driver is ON/OFF 
      - WLS_EVENT_FW_SVC_STATUS (0x00000002) --  WLAN FW service is ON/OFF 
      - WLS_EVENT_CONN_STATUS (0x00000004) --  Connected/disconnected to an AP 
      - WLS_EVENT_HANDOFF (0x00000008) --  Handoff event 
      - WLS_EVENT_FREQ_LIST (0x00000010) --  Updated frequency list 
 */

  /* Optional */
  /*  Request ID */
  uint8_t req_id_valid;  /**< Must be set to true if req_id is being passed */
  uint32_t req_id;
  /**<   Request ID in the received request */

  /* Optional */
  /*  Host Driver Status */
  uint8_t host_is_on_valid;  /**< Must be set to true if host_is_on is being passed */
  uint8_t host_is_on;
  /**<   Host status */

  /* Optional */
  /*  FW Service Status */
  uint8_t fw_svc_is_on_valid;  /**< Must be set to true if fw_svc_is_on is being passed */
  uint8_t fw_svc_is_on;
  /**<   WLAN FW service is ON or OFF */

  /* Optional */
  /*  WLAN Device Connection Status */
  uint8_t is_connected_valid;  /**< Must be set to true if is_connected is being passed */
  uint8_t is_connected;
  /**<   Is the WLAN device connected to an AP */

  /* Optional */
  /*  Handoff Event Status */
  uint8_t handoff_happened_valid;  /**< Must be set to true if handoff_happened is being passed */
  uint8_t handoff_happened;
  /**<   Handoff happened? */

  /* Optional */
  /*  WLAN Interface ID */
  uint8_t intf_id_valid;  /**< Must be set to true if intf_id is being passed */
  uint32_t intf_id;
  /**<   WLAN device interface ID */

  /* Optional */
  /*  WLAN Interface Mode */
  uint8_t intf_mode_valid;  /**< Must be set to true if intf_mode is being passed */
  wls_wlan_dev_t_v01 intf_mode;
  /**<   WLAN device interface mode
 Values: \n
      - WLS_WLAN_DEV_STA (0) --  WLAN device is in station mode 
      - WLS_WLAN_DEV_P2P_CLI (1) --  WLAN device is in P2P client mode 
      - WLS_WLAN_DEV_ANY (2) --  WLAN device is in any mode (used for subscription purpose) 
 */

  /* Optional */
  /*  AP Information */
  uint8_t ap_info_valid;  /**< Must be set to true if ap_info is being passed */
  wls_ap_base_t_v01 ap_info;

  /* Optional */
  /*  Frequency List Supported for Scan */
  uint8_t supported_scan_freq_list_valid;  /**< Must be set to true if supported_scan_freq_list is being passed */
  wls_freq_list_t_v01 supported_scan_freq_list;
}wls_event_ind_msg_v01;  /* Message */
/**
    @}
  */

/** @addtogroup wls_qmi_messages
    @{
  */
/** Indication Message; Indication sent by the WLAN location service to inform the
                     location client the scan results */
typedef struct {

  /* Optional */
  /*  Request ID */
  uint8_t req_id_valid;  /**< Must be set to true if req_id is being passed */
  uint32_t req_id;
  /**<   Request ID in the received request */

  /* Optional */
  /*  Scanned Frequency List */
  uint8_t scanned_freq_list_valid;  /**< Must be set to true if scanned_freq_list is being passed */
  wls_freq_list_t_v01 scanned_freq_list;
  /**<   List of freqencies scanned */

  /* Optional */
  /*  AP Array */
  uint8_t ap_array_valid;  /**< Must be set to true if ap_array is being passed */
  uint32_t ap_array_len;  /**< Must be set to # of elements in ap_array */
  wls_ap_t_v01 ap_array[WLS_MAX_AP_NUM_V01];
  /**<   Information of APs found during the scan operation */
}wls_scan_result_ind_msg_v01;  /* Message */
/**
    @}
  */

/** @addtogroup wls_qmi_messages
    @{
  */
/** Indication Message; Indication sent by the WLAN location service to inform the
                     location client whenever there is an error detected. */
typedef struct {

  /* Optional */
  /*  Error ID */
  uint8_t err_id_valid;  /**< Must be set to true if err_id is being passed */
  wls_err_t_v01 err_id;
  /**<   WLS error type
 Values: \n
      - WLS_ERR_NONE (0) --  No error 
      - WLS_ERR_INFO_UNAVAIL (1) --  Information is unavailable 
      - WLS_ERR_INVALID_PARAM (2) --  Invalid request parameter(s) detected 
      - WLS_ERR_HOST_OFF (3) --  WLAN host driver is not loaded 
      - WLS_ERR_FW_SVC_OFF (4) --  WLAN FW service is OFF 
      - WLS_ERR_TIMEOUT (5) --  Request processing not completed within timeout value 
      - WLS_ERR_HOST_DRV_RELOADED (6) --  WLAN host driver reloaded 
      - WLS_ERR_SSR (7) --  WLAN sub-system restart 
 */

  /* Optional */
  /*  Error Information */
  uint8_t err_info_valid;  /**< Must be set to true if err_info is being passed */
  char err_info[WLS_MAX_ERR_INFO_LEN_V01 + 1];
  /**<   Detailed error information */

  /* Optional */
  /*  Request ID */
  uint8_t req_id_valid;  /**< Must be set to true if req_id is being passed */
  uint32_t req_id;
  /**<   Request ID if the error is related to an explicit request */
}wls_err_ind_msg_v01;  /* Message */
/**
    @}
  */

/*Service Message Definition*/
/** @addtogroup wls_qmi_msg_ids
    @{
  */
#define QMI_WLS_VER_REQ_V01 0x0020
#define QMI_WLS_VER_RESP_V01 0x0020
#define QMI_WLS_STS_QUERY_REQ_V01 0x0021
#define QMI_WLS_STS_QUERY_RESP_V01 0x0021
#define QMI_WLS_STS_IND_V01 0x0021
#define QMI_WLS_SCAN_REQ_V01 0x0022
#define QMI_WLS_SCAN_RESP_V01 0x0022
#define QMI_WLS_SUB_REQ_V01 0x0023
#define QMI_WLS_SUB_RESP_V01 0x0023
#define QMI_WLS_EVENT_IND_V01 0x0024
#define QMI_WLS_SCAN_RESULT_IND_V01 0x0025
#define QMI_WLS_ERR_IND_V01 0x0026
/**
    @}
  */

/* Service Object Accessor */
/** @addtogroup wms_qmi_accessor 
    @{
  */
/** This function is used internally by the autogenerated code.  Clients should use the
   macro wls_get_service_object_v01( ) that takes in no arguments. */
qmi_idl_service_object_type wls_get_service_object_internal_v01
 ( int32_t idl_maj_version, int32_t idl_min_version, int32_t library_version );
 
/** This macro should be used to get the service object */ 
#define wls_get_service_object_v01( ) \
          wls_get_service_object_internal_v01( \
            WLS_V01_IDL_MAJOR_VERS, WLS_V01_IDL_MINOR_VERS, \
            WLS_V01_IDL_TOOL_VERS )
/** 
    @} 
  */


#ifdef __cplusplus
}
#endif
#endif

