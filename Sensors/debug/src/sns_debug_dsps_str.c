/*============================================================================

@file 
sns_debug_str_dsps.c

@brief
Contains main implementation of receiving and processing 
debug strings on DSPS.

  Copyright (c) 2010-2014 Qualcomm Technologies, Inc.  All Rights Reserved.
  Qualcomm Technologies Proprietary and Confidential.

============================================================================*/

/*===========================================================================

      EDIT HISTORY FOR MODULE

This section contains comments describing changes made to the module.
Notice that changes are listed in reverse chronological order.

$Header: //components/rel/ssc.adsp/2.6.1/debug/src/sns_debug_dsps_str.c#1 $

when        who    what, where, why
(mm/dd/yyyy)
--------    ----  ---------------------------------------------------------- 
07/20/2014   VY   Disabled logging in uImage
01/29/2013   vy   Updated for uImage support.
01/29/2013  gju   Include different file for SMR utlity functions.
01/18/2013   ag   Use the tail end of file name(with path) to get useful information
11/21/2012   ps   Added sns_debug_is_module_disabled() function
10/04/2012   dc   Update priority field. Make request, responses and async indications,
                  and log and debug indications as high priority.
08/08/2012   ag   Fix size param of csi_send_ind
07/30/2012   ag   Porting from SMR to QMI
01/26/2012   ag   Filename parameter of sns_debug_printf_dsps_string_id will 
                  no longer contain entire path 
11/22/2011   br   Use of SNS_OS_MEMXXX instead of OI_MemXXX
11/18/2011   sc   Fix for compilation warnings
11/14/2011   jhh  Updated sns_smr_msg_alloc and sns_smr_msg_free to meet new API
05/23/2011   sj   Disable all print msg masks by default 
                  (this is helpful during 8960 bringup)
03/04/2011   ad   Added SCM debug messages
02/28/2011   br   disable the debug_print feature with SNS_DSPS_PROFILE_ON definition
02/08/2011   ag   Add AKM8975 Magnetometer support (original checkin by osnat)
01/28/2011   br   changed constant names for deploying QMI tool ver#2
01/15/2011   sc   Fix on PCSIM to reflect last change of debug msg interface
11/15/2010   ag   fix memory leak introduced in case of DAL tests
11/09/2010   ad   added support for debug filtering 
10/28/2010   ad   added device driver modules to string database
10/26/2010   ag   sns_smr_send() called only when DAL_UCOS_TEST is not defined
10/11/2010   sj   Added support for SMGR Debug Strings (for PCSIM)
09/30/2010   sj   More error handling and minor fixes
09/29/2010   sj   Support for DSPS style Debug Strings on PCSIM
09/27/2010   sj   Fixes for capturing the appropriate 
                  filename of caller
09/21/2010   sj   Created
===========================================================================*/

/*=====================================================================
                 INCLUDE FILES
=======================================================================*/
#include "sns_common.h"
#include "sns_smr_util.h"
#include "sns_debug_str.h"
#include "sns_debug_api.h"
#include "sns_memmgr.h"
#include "oi_string.h" //For OI_StrLen

#ifdef SNS_PCSIM
#include "sns_string_db.h"
//#include "sns_db_list.h"
#include <stdio.h>
#endif

#ifdef SNS_QMI_ENABLE
#include "sns_memmgr.h"
#include "sns_debug_interface_v01.h"
#include "qmi_csi.h"
#include "qmi_csi_common.h"
#include "qmi_csi_target_ext.h"

extern qmi_client_handle debug_ind_client_handle;
#endif

/* debug mask to filter debug messages on DSPS */
sns_debug_mask_t sns_diag_dsps_debug_mask = 0xffffffffffffffffULL;

#ifdef SNS_PCSIM
/*===========================================================================
                  STRUCTURES
============================================================================*/
/*  Structure capturing a string entry */
typedef struct 
{
    uint16_t string_id;
    const char *dbg_string;
} string_db_entry_s;

typedef struct
{
  sns_debug_module_id_e module_id;
  const string_db_entry_s* db_ptr;
  uint8_t db_size;
} db_list_s;

/*===========================================================================
                  GLOBAL VARIABLES
============================================================================*/
/* Define each modules global array */
static const string_db_entry_s diag_debug_str_db[]       = DIAG_STR_DB;
static const string_db_entry_s smgr_debug_str_db[]       = SMGR_STR_DB;
static const string_db_entry_s dd_alsprx_debug_str_db[]  = DD_ALPRX_STR_DB;
static const string_db_entry_s dd_mag8975_debug_str_db[] = DD_MAG8975_STR_DB;
static const string_db_entry_s dd_accel_debug_str_db[]   = DD_ACCEL_STR_DB;
static const string_db_entry_s dd_gyro_debug_str_db[]    = DD_GYRO_STR_DB;
static const string_db_entry_s sam_debug_str_db[]        = SAM_STR_DB;
static const string_db_entry_s smr_debug_str_db[]        = SMR_STR_DB;
static const string_db_entry_s scm_debug_str_db[]        = SCM_STR_DB;

/* Pointer to debug string databases of sensor modules */
static const db_list_s sensor_dbg_db_ptrs[] = {
                                          // DIAG module
                                         {SNS_DBG_MOD_APPS_DIAG, diag_debug_str_db, (sizeof(diag_debug_str_db)/sizeof(diag_debug_str_db[0]))},
                                               //SAM Module
                                               {SNS_DBG_MOD_DSPS_SAM, sam_debug_str_db,(sizeof(sam_debug_str_db)/sizeof(sam_debug_str_db[0]))},
                                               //SMGR Module
                                               {SNS_DBG_MOD_DSPS_SMGR, smgr_debug_str_db,(sizeof(smgr_debug_str_db)/sizeof(smgr_debug_str_db[0]))},
                                               //SMR Apps Module
                                               {SNS_DBG_MOD_APPS_SMR, smr_debug_str_db,(sizeof(smr_debug_str_db)/sizeof(smr_debug_str_db[0]))},
                                               //SMR DSPS Module
                                               {SNS_DBG_MOD_DSPS_SMR, smr_debug_str_db,(sizeof(smr_debug_str_db)/sizeof(smr_debug_str_db[0]))},
                                               //ALS Proximity Device Driver Module
                                               {SNS_DBG_MOD_DSPS_DD_ALSPRX, dd_alsprx_debug_str_db,(sizeof(dd_alsprx_debug_str_db)/sizeof(dd_alsprx_debug_str_db[0]))},
                                               //AKM8975 Magnetometer Device Driver Module
                                               {SNS_DBG_MOD_DSPS_DD_MAG8975, dd_mag8975_debug_str_db,(sizeof(dd_mag8975_debug_str_db)/sizeof(dd_mag8975_debug_str_db[0]))},
                                               //Accel Device Driver Module
                                               {SNS_DBG_MOD_DSPS_DD_ACCEL, dd_accel_debug_str_db,(sizeof(dd_accel_debug_str_db)/sizeof(dd_accel_debug_str_db[0]))},
                                               //Gyro Device Driver Module
                                               {SNS_DBG_MOD_DSPS_DD_GYRO, dd_gyro_debug_str_db,(sizeof(dd_gyro_debug_str_db)/sizeof(dd_gyro_debug_str_db[0]))},
                                               //SCM Module
                                               {SNS_DBG_MOD_DSPS_SCM, scm_debug_str_db,(sizeof(scm_debug_str_db)/sizeof(scm_debug_str_db[0]))}                                       };
#endif
/*===========================================================================
                  FUNCTIONS
============================================================================*/

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
void sns_debug_printf_dsps_string_id(void* msg_ptr,const char* file_name_ptr)
{
/*===================================
   IMPLEMENTATION FOR TARGET
====================================*/
#ifndef SNS_PCSIM
  uint32_t file_name_size_instruct,file_name_size, copy_len, tail_start_pos;
  void* qmi_msg_ptr;
  uint32 qmi_msg_size;
  sns_debug_string_id_ind_msg_v01 *str_ptr = (sns_debug_string_id_ind_msg_v01*) msg_ptr;
  
#ifdef SNS_DSPS_PROFILE_ON
  return;
#endif
  /* Input parameters validity check */
  if ( (msg_ptr == NULL) || (file_name_ptr == NULL) || 
       (str_ptr->module_id >= SNS_DBG_NUM_MOD_IDS))
  {
    return;
  }

  /* Filter debug messages based on debug mask */
  if (((sns_debug_mask_t)1 << str_ptr->module_id) & sns_diag_dsps_debug_mask)
  {
     return;
  }

  /* Copy the filename */
  file_name_size_instruct = sizeof(((sns_debug_string_id_ind_msg_v01*)0)->file_name);
  file_name_size = OI_StrLen(file_name_ptr);
  SNS_OS_MEMZERO((void*)str_ptr->file_name,file_name_size_instruct);

  if ((file_name_size + 1) > file_name_size_instruct)
    copy_len = (file_name_size_instruct - 1);
  else
    copy_len = file_name_size;

  tail_start_pos = file_name_size - copy_len;

  SNS_OS_MEMCOPY((void*)str_ptr->file_name,
                 (void*)(&file_name_ptr[tail_start_pos]),
                 copy_len);
  str_ptr->file_name_len = (copy_len + 1);

  /* Size of qmi message is size of debug_string_qmi msg struct - size of filename + 
   * actual size of filename 
   */
  qmi_msg_size = sizeof(sns_debug_string_id_ind_msg_v01) - file_name_size_instruct
                 + str_ptr->file_name_len;
#ifdef SNS_QMI_ENABLE
  qmi_msg_ptr = (sns_debug_string_id_ind_msg_v01 *)SNS_OS_MALLOC(SNS_DBG_MOD_DSPS_DIAG,qmi_msg_size);
  if (qmi_msg_ptr != NULL)
  {
    SNS_OS_MEMCOPY(qmi_msg_ptr,msg_ptr,qmi_msg_size);

    if (debug_ind_client_handle != 0)
    {
      qmi_csi_send_ind(debug_ind_client_handle,
                       SNS_DEBUG_STRING_ID_IND_V01,
                       qmi_msg_ptr,
                       sizeof(sns_debug_string_id_ind_msg_v01)); //qmi_msg_size);
    }

    SNS_OS_FREE( qmi_msg_ptr );
  }
#else
  qmi_msg_ptr = sns_smr_msg_alloc(SNS_DBG_MOD_DSPS_DIAG,qmi_msg_size);
  if (qmi_msg_ptr != NULL)
  {
    sns_smr_header_s smr_hdr;

    /* Mempy the qmi message in the allocated space */
    SNS_OS_MEMCOPY(qmi_msg_ptr,msg_ptr,qmi_msg_size);

    /*  Fill in SMR header details from diag command packet */
    smr_hdr.dst_module = SNS_MODULE_APPS_DIAG;  
    smr_hdr.src_module = SNS_MODULE_DSPS;
    smr_hdr.priority = SNS_SMR_MSG_PRI_HIGH;
    smr_hdr.txn_id = 0;
    smr_hdr.ext_clnt_id = 0;
    smr_hdr.msg_type = SNS_SMR_MSG_TYPE_IND;
    smr_hdr.svc_num = SNS_DEBUG_SVC_ID_V01;
    smr_hdr.msg_id = SNS_DEBUG_STRING_ID_IND_V01;
    smr_hdr.body_len = qmi_msg_size;

    if (sns_smr_set_hdr(&smr_hdr,qmi_msg_ptr) == SNS_SUCCESS)
    {
#ifndef DAL_UCOS_TEST
      if (sns_smr_send(qmi_msg_ptr) == SNS_SUCCESS)
      {
        return;
      }
#endif
    }
    sns_smr_msg_free(qmi_msg_ptr);
  }
#endif //SNS_QMI_ENABLE
#endif //SNS_PCSIM

/*===================================
   IMPLEMENTATION FOR PC-SIM
====================================*/
/* Implementation for PC sim */
#ifdef SNS_PCSIM
  uint16_t                         i,j,str_db_size;
  static uint8_t                   db_size;
  const string_db_entry_s          *db_ptr = NULL;
  const char                       *str_ptr;
  uint32_t                         file_name_size_instruct,file_name_size;
  sns_debug_string_id_ind_msg_v01  *msg_str_ptr = (sns_debug_string_id_ind_msg_v01*) msg_ptr;

  /* Input parameters validity check */
  if ( (msg_ptr == NULL) || (file_name_ptr == NULL) )
  {
    return;
  }

  /* Get string database pointer from module id */
  if (db_size == 0) 
  {
    db_size = sizeof(sensor_dbg_db_ptrs)/sizeof(sensor_dbg_db_ptrs[1]);
  }
  
  for (i = 0; i < db_size; i++)
  {
    if ( sensor_dbg_db_ptrs[i].module_id == msg_str_ptr->module_id )
    {
      db_ptr = sensor_dbg_db_ptrs[i].db_ptr;
      break;
    }
  }
  /* IMPORTANT : Do NOT ReUSE i in the code after this point */
  if ( (db_ptr == NULL) ||                                 // NULL check for pointer
       (msg_str_ptr->string_identifier > sensor_dbg_db_ptrs[i].db_size )  // Check if string id is greater maximum string id in the db
     )		 
  {
    printf("\ndb ptr NULL (%d) OR string ID not valid (%d)",db_ptr,msg_str_ptr->string_identifier);
    return;
  }

  str_ptr = db_ptr[msg_str_ptr->string_identifier].dbg_string;
  /* Does the string id match the right location in the string database */
  if (msg_str_ptr->string_identifier != db_ptr[msg_str_ptr->string_identifier].string_id)
  {
    /* The string does not match, search the database for the right string entry */
    str_db_size = sensor_dbg_db_ptrs[i].db_size;
    for(j = 0; j <= str_db_size; j++)
    {
      if ( db_ptr[j].string_id == msg_str_ptr->string_identifier )
      {
        str_ptr = db_ptr[j].dbg_string;  
        break;
      }
    } // end of for

    /* String was not found print message and return */
    if (j > str_db_size)
    {
      printf("\n%s(%d): String not found in DB = %d. FIX it\n",
             file_name_ptr,
             msg_str_ptr->line_number,
             msg_str_ptr->string_identifier);
      return;
    } //end of nested if
  } // end of if

  /* Extract the filename */
  file_name_size_instruct = sizeof(((sns_debug_string_id_ind_msg_v01*)0)->file_name);
  file_name_size = OI_StrLen(file_name_ptr);
  SNS_OS_MEMZERO((void*)msg_str_ptr->file_name,file_name_size_instruct);

  /* From the end of the string check when the first backslash or forward appears */
  for( i = file_name_size - 1; i >= 0; i--)
  {
    if ((file_name_ptr[i] == '\\') || (file_name_ptr[i] == '/') )
      break;
  }

  /* Doing this just in case i is negative and we dont want to index into file_name_ptr
     from a negative index */
  if (i < 0)
  {
    j = 0;
  }
  else
  {
    /* ith location is the backlash or forward slash */
    j = i+1;
  }

  /* If filename is bigger than our destination
   * copy only destination num of characters
   * else copy entire filename */
  if ( (file_name_size-i-1) >= file_name_size_instruct)
  {
    SNS_OS_MEMCOPY((void*)msg_str_ptr->file_name,
               (void*)(&file_name_ptr[j]),
               file_name_size_instruct - 1); //-1 is subtracted so to have space for null char
  }
  else
  {
    SNS_OS_MEMCOPY((void*)msg_str_ptr->file_name,
                 (void*)(&file_name_ptr[j]),
               (file_name_size-i-1));
  }

  printf("\n%s(%d):",msg_str_ptr->file_name,msg_str_ptr->line_number);

  switch (msg_str_ptr->param_values_len)
  {
    case 0:
      printf("%s",str_ptr);
        break;
    case 1:
        printf((const char*)str_ptr,msg_str_ptr->param_values[0]);
        break;
    case 2:
        printf((const char*)str_ptr,msg_str_ptr->param_values[0],msg_str_ptr->param_values[1]);
        break;
    case 3:
        printf((const char*)str_ptr,msg_str_ptr->param_values[0],msg_str_ptr->param_values[1],msg_str_ptr->param_values[2]);
        break;
  };
  printf("\n");
#endif //SNS_PCSIM
}

/*===========================================================================

  FUNCTION:   sns_diag_dsps_set_debug_mask

===========================================================================*/
/*!
  @brief
  Sets the debug mask on the DSPS processor
  
  @param[i] 
  msg_ptr: pointer to message containing debug mask that indicates which
           debug messages are enabled/disabled.

  @return
  none
*/
/*=========================================================================*/
void sns_diag_dsps_set_debug_mask(sns_diag_set_debug_mask_req_msg_v01* msg_ptr)
{
  if (msg_ptr != NULL)
  {
    sns_diag_dsps_debug_mask = msg_ptr->debug_mask.mask;
  }
}


/*===========================================================================

  FUNCTION:   sns_debug_is_module_disabled

===========================================================================*/
/*===========================================================================*/
/*!
  @brief
  Returns 1 if the the module's debug strings need to be filtered.

  @param[i] module_id        : Debug module id

  @return
  uint8_t : 1 - Module's messages should be filtered
            0 - Module's messages should NOT be filtered
*/
/*=========================================================================*/
uint8_t sns_debug_is_module_disabled(sns_debug_module_id_e module_id)
{
  uint64_t   temp_i=1;
  uint8_t    ret_value=0;
  
  /* Check if the messages from the module are enabled
   * based on the debug string filter mask
   */
  if ( SNS_DBG_MOD_DSPS_SAM == module_id )
  {
    ret_value = 0;
  }
  else if ((sns_diag_dsps_debug_mask & (temp_i << module_id)) != 0)
  {
    ret_value = 1;
  }
  
  return ret_value;
} 
