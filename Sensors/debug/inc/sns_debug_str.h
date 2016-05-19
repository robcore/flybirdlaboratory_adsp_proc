#ifndef SNS_DEBUG_STR_H
#define SNS_DEBUG_STR_H

/*============================================================================

@file
sns_debug_str.h

@brief
Contains macros and definitions required for printing
debug strings on the DSPS. The file has the same name as the apps
counterpart

  Copyright (c) 2010-2014 Qualcomm Technologies, Inc.  All Rights Reserved.
  Qualcomm Technologies Proprietary and Confidential.

============================================================================*/

/*===========================================================================

                     EDIT HISTORY FOR MODULE

This section contains comments describing changes made to the module.
Notice that changes are listed in reverse chronological order.

$Header: //components/rel/ssc.adsp/2.6.1/debug/inc/sns_debug_str.h#3 $

when        who    what, where, why
(mm/dd/yyyy)
--------   ----    ----------------------------------------------------------
02/26/2015   VY     Moved uImage logging to debug thread
11/26/2014   VY     Added api to disable logging
2014-07-22   ps     Fix compiler warnings
07/20/2014   VY     Disabled logging in uImage
07/15/2013   vh     Changed MODULE definition FILE to FILENAME
11/21/2012   ps     Added SNS_PRINTF_STRING_<PRI>_X Macros
01/26/2012   ag     Pass only the filename rather than filename with path, in debug messages
12/22/2010   sj     Fixed incorrect array index
12/09/2010   sj     Fixed debug.idl file based on code review comments. Hence changes
                    to C code to match those.
09/28/2010   sj     Compilation fixes
09/27/2010   sj     Fixes for capturing the appropriate
                    filename of caller
09/21/2010   sj     Created to support debug strings from DSPS
===========================================================================*/

/*=====================================================================
                 INCLUDE FILES
=======================================================================*/
#include "sns_debug_interface_v01.h"
#include "sns_debug_api.h"
#include "sns_smgr_ddf_if.h"
#include <stdbool.h>
#include <stddef.h>

#define __MODULE__ __FILENAME__

/* Debug string priority defines */
#define SNS_MSG_LOW 0
#define SNS_MSG_MEDIUM 1
#define SNS_MSG_HIGH 2
#define SNS_MSG_FATAL 3
#define SNS_MSG_ERROR 4

/* Originating processor defines */
#define PROCESSOR_DSPS 1

#ifdef UIMG_LOG
#define SNS_DEBUG_LOGPKT_COMMIT_SIG          0x00800000
#define SNS_DEBUG_LOGPKT_DROP_SIG            0x01000000

typedef struct 
{
  sns_q_link_s   link;
  void          *log_pkt_msg;
  uint32_t       pkt_type;
  uint32_t       pkt_size;
} logpkt_hold_item_s;

typedef struct
{
  sns_q_s     hold_queue;
  OS_EVENT   *q_mutex_ptr;
} logpkt_hold_buffer_s; 
#endif /* UIMG_LOG */

/*===========================================================================

  FUNCTION:   sns_debug_printf_dsps_string_id

===========================================================================*/

/*===========================================================================*/
/*!
  @brief
  Sends a QMI message containing all the information regarding the string
  so that it can be printed out on the apps processor.

  @param[i] msg_ptr         : Pointer to the QMI message (contains info
                              about the string to be printed.
  @param[i] file_name_ptr   : Pointer to name of file from where the debug
                              string is being printed

  @return
  No return value.
*/
/*=========================================================================*/
void sns_debug_printf_dsps_string_id(void* msg_ptr,const char* file_name_ptr);

uint8_t sns_debug_is_module_disabled(sns_debug_module_id_e module_id);

void sns_logging_status_override(bool log_override);

/* Enable the required Module ID in /data/misc/sensors/sensors_dbg_config.txt */
/* Low Priority */
#define SNS_PRINTF_STRING_LOW_0(mod_id,str) \
       {  \
          if(!sns_ddf_smgr_is_in_uimage() && !sns_debug_is_module_disabled(mod_id))  \
          {  \
              MSG(MSG_SSID_SNS,DBG_LOW_PRIO,str);   \
          }  \
       }
#define SNS_PRINTF_STRING_LOW_1(mod_id,str,parameter1) \
       {  \
          if(!sns_ddf_smgr_is_in_uimage() && !sns_debug_is_module_disabled(mod_id))  \
          {  \
              MSG_1(MSG_SSID_SNS,DBG_LOW_PRIO,str,parameter1); \
          }  \
       }
#define SNS_PRINTF_STRING_LOW_2(mod_id,str,parameter1,parameter2) \
       { \
          if(!sns_ddf_smgr_is_in_uimage() && !sns_debug_is_module_disabled(mod_id))  \
          {  \
              MSG_2(MSG_SSID_SNS, DBG_LOW_PRIO, str,parameter1,parameter2); \
          }  \
       }
#define SNS_PRINTF_STRING_LOW_3(mod_id,str,parameter1,parameter2,parameter3) \
       { \
          if(!sns_ddf_smgr_is_in_uimage() && !sns_debug_is_module_disabled(mod_id))  \
          {  \
              MSG_3(MSG_SSID_SNS, DBG_LOW_PRIO, str,parameter1,parameter2,parameter3); \
          }  \
       }

/* Medium priority */
#define SNS_PRINTF_STRING_MEDIUM_0(mod_id,str)  \
       {  \
          if(!sns_ddf_smgr_is_in_uimage() && !sns_debug_is_module_disabled(mod_id))  \
          {  \
              MSG(MSG_SSID_SNS, DBG_MED_PRIO, str);  \
          }  \
       }
#define SNS_PRINTF_STRING_MEDIUM_1(mod_id,str,parameter1) \
       {  \
          if(!sns_ddf_smgr_is_in_uimage() && !sns_debug_is_module_disabled(mod_id))   \
          {  \
              MSG_1(MSG_SSID_SNS,DBG_MED_PRIO,str,parameter1); \
          }  \
       }
#define SNS_PRINTF_STRING_MEDIUM_2(mod_id,str,parameter1,parameter2) \
       { \
          if(!sns_ddf_smgr_is_in_uimage() && !sns_debug_is_module_disabled(mod_id))  \
          {  \
              MSG_2(MSG_SSID_SNS, DBG_MED_PRIO, str,parameter1,parameter2); \
          }  \
       }
#define SNS_PRINTF_STRING_MEDIUM_3(mod_id,str,parameter1,parameter2,parameter3) \
       { \
          if(!sns_ddf_smgr_is_in_uimage() && !sns_debug_is_module_disabled(mod_id))  \
          {  \
              MSG_3(MSG_SSID_SNS, DBG_MED_PRIO, str,parameter1,parameter2,parameter3); \
          }  \
       }

/* High priority */
#define SNS_PRINTF_STRING_HIGH_0(mod_id,str) \
       {  \
          if(!sns_ddf_smgr_is_in_uimage() && !sns_debug_is_module_disabled(mod_id))  \
          {  \
              MSG(MSG_SSID_SNS, DBG_HIGH_PRIO, str); \
          }  \
       }
#define SNS_PRINTF_STRING_HIGH_1(mod_id,str,parameter1) \
       {  \
          if(!sns_ddf_smgr_is_in_uimage() && !sns_debug_is_module_disabled(mod_id))   \
          {  \
              MSG_1(MSG_SSID_SNS,DBG_HIGH_PRIO,str,parameter1); \
          }  \
       }
#define SNS_PRINTF_STRING_HIGH_2(mod_id,str,parameter1,parameter2) \
       { \
          if(!sns_ddf_smgr_is_in_uimage() && !sns_debug_is_module_disabled(mod_id))  \
          {  \
              MSG_2(MSG_SSID_SNS, DBG_HIGH_PRIO, str,parameter1,parameter2); \
          }  \
       }
#define SNS_PRINTF_STRING_HIGH_3(mod_id,str,parameter1,parameter2,parameter3) \
       { \
          if(!sns_ddf_smgr_is_in_uimage() && !sns_debug_is_module_disabled(mod_id))  \
          {  \
              MSG_3(MSG_SSID_SNS, DBG_HIGH_PRIO, str,parameter1,parameter2,parameter3); \
          }  \
       }

/* Fatal Priority */
#define SNS_PRINTF_STRING_FATAL_0(mod_id,str) \
       {  \
          if(!sns_ddf_smgr_is_in_uimage() && !sns_debug_is_module_disabled(mod_id))  \
          {  \
              MSG(MSG_SSID_SNS, DBG_FATAL_PRIO, str); \
          }  \
       }
#define SNS_PRINTF_STRING_FATAL_1(mod_id,str,parameter1) \
       {  \
          if(!sns_ddf_smgr_is_in_uimage() && !sns_debug_is_module_disabled(mod_id))   \
          {  \
              MSG_1(MSG_SSID_SNS,DBG_FATAL_PRIO,str,parameter1); \
          }  \
       }
#define SNS_PRINTF_STRING_FATAL_2(mod_id,str,parameter1,parameter2) \
       { \
          if(!sns_ddf_smgr_is_in_uimage() && !sns_debug_is_module_disabled(mod_id))  \
          {  \
              MSG_2(MSG_SSID_SNS, DBG_FATAL_PRIO, str,parameter1,parameter2); \
          }  \
       }
#define SNS_PRINTF_STRING_FATAL_3(mod_id,str,parameter1,parameter2,parameter3) \
       { \
          if(!sns_ddf_smgr_is_in_uimage() && !sns_debug_is_module_disabled(mod_id))  \
          {  \
              MSG_3(MSG_SSID_SNS, DBG_FATAL_PRIO, str,parameter1,parameter2,parameter3); \
          }  \
       }

/* Error priority */
#define SNS_PRINTF_STRING_ERROR_0(mod_id,str) \
       {  \
          if(!sns_ddf_smgr_is_in_uimage() && !sns_debug_is_module_disabled(mod_id))  \
          {  \
              MSG(MSG_SSID_SNS, DBG_ERROR_PRIO, str); \
          }  \
       }
#define SNS_PRINTF_STRING_ERROR_1(mod_id,str,parameter1) \
       {  \
          if(!sns_ddf_smgr_is_in_uimage() && !sns_debug_is_module_disabled(mod_id))   \
          {  \
              MSG_1(MSG_SSID_SNS,DBG_ERROR_PRIO,str,parameter1); \
          }  \
       }
#define SNS_PRINTF_STRING_ERROR_2(mod_id,str,parameter1,parameter2) \
       { \
          if(!sns_ddf_smgr_is_in_uimage() && !sns_debug_is_module_disabled(mod_id))  \
          {  \
              MSG_2(MSG_SSID_SNS, DBG_ERROR_PRIO, str,parameter1,parameter2); \
          }  \
       }
#define SNS_PRINTF_STRING_ERROR_3(mod_id,str,parameter1,parameter2,parameter3) \
       { \
          if(!sns_ddf_smgr_is_in_uimage() && !sns_debug_is_module_disabled(mod_id))  \
          {  \
              MSG_3(MSG_SSID_SNS, DBG_ERROR_PRIO, str,parameter1,parameter2,parameter3); \
          }  \
       }


/* The debug printf macros for DSPS and Apps processor where only the string ID is provided.
 * These macros send a QMI indication message to apps processor to print out the debug
 * string.
 */

#define SNS_PRINTF_STRING_ID_LOW_0(mod_id,str_id) \
                     { \
                       sns_debug_string_id_ind_msg_v01 debug_msg_params; \
                       debug_msg_params.string_identifier    = str_id;   \
                       debug_msg_params.module_id            = mod_id;   \
                       debug_msg_params.str_priority         = SNS_MSG_LOW; \
                       debug_msg_params.param_values_len     = 0;        \
                       debug_msg_params.param_values[0]      = 0;        \
                       debug_msg_params.param_values[1]      = 0;        \
                       debug_msg_params.param_values[2]      = 0;        \
                       debug_msg_params.line_number          = __LINE__; \
                       sns_debug_printf_dsps_string_id((void*)&debug_msg_params,(const char*)__MODULE__); \
                     }


#define SNS_PRINTF_STRING_ID_LOW_1(mod_id,str_id,parameter1) \
                     { \
                       sns_debug_string_id_ind_msg_v01 debug_msg_params; \
                       debug_msg_params.string_identifier    = str_id;   \
                       debug_msg_params.module_id            = mod_id;   \
                       debug_msg_params.str_priority         = SNS_MSG_LOW; \
                       debug_msg_params.param_values_len     = 1;        \
                       debug_msg_params.param_values[0]      = (uint32_t)(parameter1); \
                       debug_msg_params.param_values[1]      = 0;        \
                       debug_msg_params.param_values[2]      = 0;        \
                       debug_msg_params.line_number          = __LINE__; \
                       sns_debug_printf_dsps_string_id((void*)&debug_msg_params,(const char*)__MODULE__); \
                     }


#define SNS_PRINTF_STRING_ID_LOW_2(mod_id,str_id,parameter1,parameter2) \
                     { \
                       sns_debug_string_id_ind_msg_v01 debug_msg_params; \
                       debug_msg_params.string_identifier    = str_id;   \
                       debug_msg_params.module_id            = mod_id;   \
                       debug_msg_params.str_priority         = SNS_MSG_LOW; \
                       debug_msg_params.param_values_len     = 2;        \
                       debug_msg_params.param_values[0]      = (uint32_t)(parameter1); \
                       debug_msg_params.param_values[1]      = (uint32_t)(parameter2); \
                       debug_msg_params.param_values[2]      = 0;        \
                       debug_msg_params.line_number          = __LINE__; \
                       sns_debug_printf_dsps_string_id((void*)&debug_msg_params,(const char*)__MODULE__); \
                     }


#define SNS_PRINTF_STRING_ID_LOW_3(mod_id,str_id,parameter1,parameter2,parameter3) \
                     { \
                       sns_debug_string_id_ind_msg_v01 debug_msg_params; \
                       debug_msg_params.string_identifier    = str_id;   \
                       debug_msg_params.module_id            = mod_id;   \
                       debug_msg_params.str_priority         = SNS_MSG_LOW; \
                       debug_msg_params.param_values_len     = 3;        \
                       debug_msg_params.param_values[0]      = (uint32_t)(parameter1); \
                       debug_msg_params.param_values[1]      = (uint32_t)(parameter2); \
                       debug_msg_params.param_values[2]      = (uint32_t)(parameter3); \
                       debug_msg_params.line_number          = __LINE__; \
                       sns_debug_printf_dsps_string_id((void*)&debug_msg_params,(const char*)__MODULE__); \
                     }

// Mediums
#define SNS_PRINTF_STRING_ID_MEDIUM_0(mod_id,str_id)  \
                     { \
                       sns_debug_string_id_ind_msg_v01 debug_msg_params; \
                       debug_msg_params.string_identifier    = str_id;   \
                       debug_msg_params.module_id            = mod_id;   \
                       debug_msg_params.str_priority         = SNS_MSG_MEDIUM; \
                       debug_msg_params.param_values_len     = 0;        \
                       debug_msg_params.param_values[0]      = 0;        \
                       debug_msg_params.param_values[1]      = 0;        \
                       debug_msg_params.param_values[2]      = 0;        \
                       debug_msg_params.line_number          = __LINE__; \
                       sns_debug_printf_dsps_string_id((void*)&debug_msg_params,(const char*)__MODULE__); \
                     }


#define SNS_PRINTF_STRING_ID_MEDIUM_1(mod_id,str_id,parameter1) \
                     { \
                       sns_debug_string_id_ind_msg_v01 debug_msg_params; \
                       debug_msg_params.string_identifier    = str_id;   \
                       debug_msg_params.module_id            = mod_id;   \
                       debug_msg_params.str_priority         = SNS_MSG_MEDIUM; \
                       debug_msg_params.param_values_len     = 1;        \
                       debug_msg_params.param_values[0]      = (uint32_t)(parameter1); \
                       debug_msg_params.param_values[1]      = 0;        \
                       debug_msg_params.param_values[2]      = 0;        \
                       debug_msg_params.line_number          = __LINE__; \
                       sns_debug_printf_dsps_string_id((void*)&debug_msg_params,(const char*)__MODULE__); \
                     }


#define SNS_PRINTF_STRING_ID_MEDIUM_2(mod_id,str_id,parameter1,parameter2) \
                     { \
                       sns_debug_string_id_ind_msg_v01 debug_msg_params; \
                       debug_msg_params.string_identifier    = str_id;   \
                       debug_msg_params.module_id            = mod_id;   \
                       debug_msg_params.str_priority         = SNS_MSG_MEDIUM; \
                       debug_msg_params.param_values_len     = 2;        \
                       debug_msg_params.param_values[0]      = (uint32_t)(parameter1); \
                       debug_msg_params.param_values[1]      = (uint32_t)(parameter2); \
                       debug_msg_params.param_values[2]      = 0;        \
                       debug_msg_params.line_number          = __LINE__; \
                       sns_debug_printf_dsps_string_id((void*)&debug_msg_params,(const char*)__MODULE__); \
                     }

#define SNS_PRINTF_STRING_ID_MEDIUM_3(mod_id,str_id,parameter1,parameter2,parameter3) \
                     { \
                       sns_debug_string_id_ind_msg_v01 debug_msg_params; \
                       debug_msg_params.string_identifier    = str_id;   \
                       debug_msg_params.module_id            = mod_id;   \
                       debug_msg_params.str_priority         = SNS_MSG_MEDIUM; \
                       debug_msg_params.param_values_len     = 3;        \
                       debug_msg_params.param_values[0]      = (uint32_t)(parameter1); \
                       debug_msg_params.param_values[1]      = (uint32_t)(parameter2); \
                       debug_msg_params.param_values[2]      = (uint32_t)(parameter3); \
                       debug_msg_params.line_number          = __LINE__; \
                       sns_debug_printf_dsps_string_id((void*)&debug_msg_params,(const char*)__MODULE__); \
                     }

// Highs
#define SNS_PRINTF_STRING_ID_HIGH_0(mod_id,str_id) \
                     { \
                       sns_debug_string_id_ind_msg_v01 debug_msg_params; \
                       debug_msg_params.string_identifier    = str_id;   \
                       debug_msg_params.module_id            = mod_id;   \
                       debug_msg_params.str_priority         = SNS_MSG_HIGH; \
                       debug_msg_params.param_values_len     = 0;        \
                       debug_msg_params.param_values[0]      = 0;        \
                       debug_msg_params.param_values[1]      = 0;        \
                       debug_msg_params.param_values[2]      = 0;        \
                       debug_msg_params.line_number          = __LINE__; \
                       sns_debug_printf_dsps_string_id((void*)&debug_msg_params,(const char*)__MODULE__); \
                     }


#define SNS_PRINTF_STRING_ID_HIGH_1(mod_id,str_id,parameter1) \
                     { \
                       sns_debug_string_id_ind_msg_v01 debug_msg_params; \
                       debug_msg_params.string_identifier    = str_id;   \
                       debug_msg_params.module_id            = mod_id;   \
                       debug_msg_params.str_priority         = SNS_MSG_HIGH; \
                       debug_msg_params.param_values_len     = 1;        \
                       debug_msg_params.param_values[0]      = (uint32_t)(parameter1); \
                       debug_msg_params.param_values[1]      = 0;        \
                       debug_msg_params.param_values[2]      = 0;        \
                       debug_msg_params.line_number          = __LINE__; \
                       sns_debug_printf_dsps_string_id((void*)&debug_msg_params,(const char*)__MODULE__); \
                     }


#define SNS_PRINTF_STRING_ID_HIGH_2(mod_id,str_id,parameter1,parameter2) \
                     { \
                       sns_debug_string_id_ind_msg_v01 debug_msg_params; \
                       debug_msg_params.string_identifier    = str_id;   \
                       debug_msg_params.module_id            = mod_id;   \
                       debug_msg_params.str_priority         = SNS_MSG_HIGH; \
                       debug_msg_params.param_values_len     = 2;        \
                       debug_msg_params.param_values[0]      = (uint32_t)(parameter1); \
                       debug_msg_params.param_values[1]      = (uint32_t)(parameter2); \
                       debug_msg_params.param_values[2]      = 0;        \
                       debug_msg_params.line_number          = __LINE__; \
                       sns_debug_printf_dsps_string_id((void*)&debug_msg_params,(const char*)__MODULE__); \
                     }

#define SNS_PRINTF_STRING_ID_HIGH_3(mod_id,str_id,parameter1,parameter2,parameter3) \
                     { \
                       sns_debug_string_id_ind_msg_v01 debug_msg_params; \
                       debug_msg_params.string_identifier    = str_id;   \
                       debug_msg_params.module_id            = mod_id;   \
                       debug_msg_params.str_priority         = SNS_MSG_HIGH; \
                       debug_msg_params.param_values_len     = 3;        \
                       debug_msg_params.param_values[0]      = (uint32_t)(parameter1); \
                       debug_msg_params.param_values[1]      = (uint32_t)(parameter2); \
                       debug_msg_params.param_values[2]      = (uint32_t)(parameter3); \
                       debug_msg_params.line_number          = __LINE__; \
                       sns_debug_printf_dsps_string_id((void*)&debug_msg_params,(const char*)__MODULE__); \
                     }
// Fatals
#define SNS_PRINTF_STRING_ID_FATAL_0(mod_id,str_id) \
                     { \
                       sns_debug_string_id_ind_msg_v01 debug_msg_params; \
                       debug_msg_params.string_identifier    = str_id;   \
                       debug_msg_params.module_id            = mod_id;   \
                       debug_msg_params.str_priority         = SNS_MSG_FATAL; \
                       debug_msg_params.param_values_len     = 0;        \
                       debug_msg_params.param_values[0]      = 0;        \
                       debug_msg_params.param_values[1]      = 0;        \
                       debug_msg_params.param_values[2]      = 0;        \
                       debug_msg_params.line_number          = __LINE__; \
                       sns_debug_printf_dsps_string_id((void*)&debug_msg_params,(const char*)__MODULE__); \
                     }


#define SNS_PRINTF_STRING_ID_FATAL_1(mod_id,str_id,parameter1) \
                     { \
                       sns_debug_string_id_ind_msg_v01 debug_msg_params; \
                       debug_msg_params.string_identifier    = str_id;   \
                       debug_msg_params.module_id            = mod_id;   \
                       debug_msg_params.str_priority         = SNS_MSG_FATAL; \
                       debug_msg_params.param_values_len     = 1;        \
                       debug_msg_params.param_values[0]      = (uint32_t)(parameter1); \
                       debug_msg_params.param_values[1]      = 0;        \
                       debug_msg_params.param_values[2]      = 0;        \
                       debug_msg_params.line_number          = __LINE__; \
                       sns_debug_printf_dsps_string_id((void*)&debug_msg_params,(const char*)__MODULE__); \
                     }


#define SNS_PRINTF_STRING_ID_FATAL_2(mod_id,str_id,parameter1,parameter2) \
                     { \
                       sns_debug_string_id_ind_msg_v01 debug_msg_params; \
                       debug_msg_params.string_identifier    = str_id;   \
                       debug_msg_params.module_id            = mod_id;   \
                       debug_msg_params.str_priority         = SNS_MSG_FATAL; \
                       debug_msg_params.param_values_len     = 2;        \
                       debug_msg_params.param_values[0]      = (uint32_t)(parameter1); \
                       debug_msg_params.param_values[1]      = (uint32_t)(parameter2); \
                       debug_msg_params.param_values[2]      = 0;        \
                       debug_msg_params.line_number          = __LINE__; \
                       sns_debug_printf_dsps_string_id((void*)&debug_msg_params,(const char*)__MODULE__); \
                     }

#define SNS_PRINTF_STRING_ID_FATAL_3(mod_id,str_id,parameter1,parameter2,parameter3) \
                     { \
                       sns_debug_string_id_ind_msg_v01 debug_msg_params; \
                       debug_msg_params.string_identifier    = str_id;   \
                       debug_msg_params.module_id            = mod_id;   \
                       debug_msg_params.str_priority         = SNS_MSG_FATAL; \
                       debug_msg_params.param_values_len     = 3;        \
                       debug_msg_params.param_values[0]      = (uint32_t)(parameter1); \
                       debug_msg_params.param_values[1]      = (uint32_t)(parameter2); \
                       debug_msg_params.param_values[2]      = (uint32_t)(parameter3); \
                       debug_msg_params.line_number          = __LINE__; \
                       sns_debug_printf_dsps_string_id((void*)&debug_msg_params,(const char*)__MODULE__); \
                     }

// Errors
#define SNS_PRINTF_STRING_ID_ERROR_0(mod_id,str_id) \
                     { \
                       sns_debug_string_id_ind_msg_v01 debug_msg_params; \
                       debug_msg_params.string_identifier    = str_id;   \
                       debug_msg_params.module_id            = mod_id;   \
                       debug_msg_params.str_priority         = SNS_MSG_ERROR; \
                       debug_msg_params.param_values_len     = 0;        \
                       debug_msg_params.param_values[0]      = 0;        \
                       debug_msg_params.param_values[1]      = 0;        \
                       debug_msg_params.param_values[2]      = 0;        \
                       debug_msg_params.line_number          = __LINE__; \
                       sns_debug_printf_dsps_string_id((void*)&debug_msg_params,(const char*)__MODULE__); \
                     }


#define SNS_PRINTF_STRING_ID_ERROR_1(mod_id,str_id,parameter1) \
                     { \
                       sns_debug_string_id_ind_msg_v01 debug_msg_params; \
                       debug_msg_params.string_identifier    = str_id;   \
                       debug_msg_params.module_id            = mod_id;   \
                       debug_msg_params.str_priority         = SNS_MSG_ERROR; \
                       debug_msg_params.param_values_len     = 1;        \
                       debug_msg_params.param_values[0]      = (uint32_t)(parameter1); \
                       debug_msg_params.param_values[1]      = 0;        \
                       debug_msg_params.param_values[2]      = 0;        \
                       debug_msg_params.line_number          = __LINE__; \
                       sns_debug_printf_dsps_string_id((void*)&debug_msg_params,(const char*)__MODULE__); \
                     }


#define SNS_PRINTF_STRING_ID_ERROR_2(mod_id,str_id,parameter1,parameter2) \
                     { \
                       sns_debug_string_id_ind_msg_v01 debug_msg_params; \
                       debug_msg_params.string_identifier    = str_id;   \
                       debug_msg_params.module_id            = mod_id;   \
                       debug_msg_params.str_priority         = SNS_MSG_ERROR; \
                       debug_msg_params.param_values_len     = 2;        \
                       debug_msg_params.param_values[0]      = (uint32_t)(parameter1); \
                       debug_msg_params.param_values[1]      = (uint32_t)(parameter2); \
                       debug_msg_params.param_values[2]      = 0;        \
                       debug_msg_params.line_number          = __LINE__; \
                       sns_debug_printf_dsps_string_id((void*)&debug_msg_params,(const char*)__MODULE__); \
                     }

#define SNS_PRINTF_STRING_ID_ERROR_3(mod_id,str_id,parameter1,parameter2,parameter3) \
                     { \
                       sns_debug_string_id_ind_msg_v01 debug_msg_params; \
                       debug_msg_params.string_identifier    = str_id;   \
                       debug_msg_params.module_id            = mod_id;   \
                       debug_msg_params.str_priority         = SNS_MSG_ERROR; \
                       debug_msg_params.param_values_len     = 3;        \
                       debug_msg_params.param_values[0]      = (uint32_t)(parameter1); \
                       debug_msg_params.param_values[1]      = (uint32_t)(parameter2); \
                       debug_msg_params.param_values[2]      = (uint32_t)(parameter3); \
                       debug_msg_params.line_number          = __LINE__; \
                       sns_debug_printf_dsps_string_id((void*)&debug_msg_params,(const char*)__MODULE__); \
                     }
                     

#ifdef UIMG_LOG
extern sns_err_code_e sns_debug_logpkt_commit_cntl(void *qmi_log_pkt_msg, 
                                                   uint32_t pkt_type, 
                                                   uint32_t pkt_size);

extern void sns_debug_signal_me(uint32_t sig);

extern void sns_debug_unsignal_me(uint32_t sig);

extern void sns_debug_logpkt_drop(void);

extern void sns_debug_logpkt_commit_send(void);

#endif /* UIMG_LOG */


#endif /* SNS_DEBUG_STR_H */
