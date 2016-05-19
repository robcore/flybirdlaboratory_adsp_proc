/*============================================================================
  FILE: sns_playback_utils.c

  This file contains the utility functions for sensors playback

Copyright (c) 2011,2013 Qualcomm Technologies, Inc.  All Rights Reserved.
Qualcomm Technologies Proprietary and Confidential.

============================================================================*/

/* $Header: //components/rel/ssc.adsp/2.6.1/playback/src/sns_playback_utils.c#1 $ */
/* $DateTime: 2014/12/01 08:57:58 $ */
/* $Author: pwbldsvc $ */

/*============================================================================
  EDIT HISTORY FOR MODULE

  This section contains comments describing changes made to the module.
  Notice that changes are listed in reverse chronological order. 

  when        who  what, where, why
  ----------  ---  -----------------------------------------------------------
  2013-01-29  gju  Include different file for SMR utlity functions.
  2012-10-14  sc   Use AMD enable request structure instead of common QMD struct
  2012-09-13  vh   Eliminated compiler warnings
  2012-07-06  sc   Featurize out the registry part for QDSP6 target build
  2012-02-07  pd   Added support for gestures: Basic Gestures, Facing
  2012-01-02  ks   Added support for 150B log packet
  2011-12-21  ks   Added support for single output dlf
  2011-12-18  ks   Added support for SCM Gyro Cal
  2011-11-18  ad   Updated free and alloc calls to use new API
  2011-10-03  ks   Added support for Rotation Vector Playback
  2011-09-26  ks   Added support for QFusion Playback
  2011-08-26  sc   Fixed issues with memory leak
                   Featurized rotation vector playback
  2011-08-26  pd   Added support for Rotation Vector QFusion 1.0
  2011-07-12  sc   Fixed compilation error for Apps playback
  2011-07-01  sc   Added function to enable/disable logging service
  2011-06-27  sc   Reinstated support for quaternion; added gravity logging
  2011-05-17  sc   Added registry service, which is then used to support for
                   tuning internal parameters in playback configuration.
  2011-05-09  sc   Support playback of offline data at full speed.
  2011-04-18  sc   Moved quaternion to Apps Playback
  2011-03-30  sc   Added support for quaternion logging
  2011-03-18  sc   Added support for quaternion algo
  2011-03-10  sc   Added support for BtE logging
  2011-03-07  sc   Added support for BtE algo
  2011-02-18  sc   Added support for FnS algo
  2011-01-24  sc   Added support for multiple log files
  2011-01-17  sc   Initial version

============================================================================*/

#include <stdio.h>
#include <stdlib.h>

#include "sns_osa.h"
#include "sns_smr_util.h"
#include "sns_em.h"

#include "sns_smgr_api_v01.h"

#include "sns_sam_amd_v01.h"
#include "sns_sam_vmd_v01.h"
#include "sns_sam_rmd_v01.h"
#include "sns_sam_fns_v01.h"
#include "sns_sam_bte_v01.h"
#include "sns_sam_quaternion_v01.h"
#include "sns_sam_gravity_vector_v01.h"
#include "sns_sam_rotation_vector_v01.h"
#include "sns_sam_filtered_mag_v01.h"
#include "sns_sam_mag_cal_v01.h"
#include "sns_sam_orientation_v01.h"

#ifdef FEATURE_GESTURES_REL_1
#include "sns_sam_basic_gestures_v01.h"
#include "sns_sam_facing_v01.h"
#include "sns_sam_integ_angle_v01.h"
#include "sns_sam_gyro_tap_v01.h"
#endif /* FEATURE_GESTURES_REL_1 */

#include "sns_diag_dsps_v01.h"
#include "sns_log_types.h"
#include "sns_log_api.h"

#ifndef QDSP6
#include "sns_fsa.h"
#include "sns_reg.h"
#include "sns_reg_common.h"
#include "sns_reg_api_v01.h"
#endif

#include "sns_playback.h"

// Calibration - GYRO_CAL
#include "sns_smgr_define.h"

/*---------------------------------------------------------------------------
* Preprocessor Definitions and Constants
* -------------------------------------------------------------------------*/
#define PB_GYRO_CAL_SVC_ID_V01 99 // Service ID for GYRO_CAL since this is not exposed to the Sensor 1 API

#define MAX_ALGO_NUM 10

#ifdef ENABLE_APPS_PLAYBACK
#define SNS_SAM_MODULE           SNS_MODULE_APPS_SAM
#else
#define SNS_SAM_MODULE           SNS_MODULE_DSPS_SAM
#endif

/*---------------------------------------------------------------------------
* Type Declarations
* -------------------------------------------------------------------------*/
typedef struct
{
   uint8_t svc_id;
   uint8_t num_config_elem; 
   int32_t algo_config[8];   /* should be enough to hold config for one algo */
} pb_algo_attrib_s;

/*---------------------------------------------------------------------------
* Global Data Definitions
* -------------------------------------------------------------------------*/
bool log_150B_detected=false;
/*---------------------------------------------------------------------------
* Static Variable Definitions
* -------------------------------------------------------------------------*/
static FILE *fp_accel_input, *fp_gyro_input, *fp_mag_input, *fp_sensor_input;
static FILE *fp_log_qmd_report, *fp_log_qmd_result, *fp_log_qmd_config;
static FILE *fp_log_fns_report, *fp_log_fns_result, *fp_log_fns_config;
static FILE *fp_log_bte_report, *fp_log_bte_result, *fp_log_bte_config;
static FILE *fp_log_quaternion_report, *fp_log_quaternion_result, *fp_log_quaternion_config;
static FILE *fp_log_gravity_report, *fp_log_gravity_result, *fp_log_gravity_config;
static FILE *fp_log_fmv_config,*fp_log_fmv_report,*fp_log_fmv_quat_update,*fp_log_fmv_mag_update,*fp_log_fmv_gyro_update;
static FILE *fp_log_rotation_vector_report, *fp_log_rotation_vector_result, *fp_log_rotation_vector_config;
static FILE *fp_log_orientation_report, *fp_log_orientation_result, *fp_log_orientation_config;
static FILE *fp_log_mag_cal_config, *fp_log_mag_cal_result, *fp_log_mag_cal_report;
static FILE *fp_log_gyro_cal_config, *fp_log_gyro_cal_result, *fp_log_gyro_cal_report;

#ifdef FEATURE_GESTURES_REL_1
static FILE *fp_log_basic_gestures_report, *fp_log_basic_gestures_result, *fp_log_basic_gestures_config;
static FILE *fp_log_facing_report, *fp_log_facing_result, *fp_log_facing_config;
static FILE *fp_log_integ_angle_report, *fp_log_integ_angle_result, *fp_log_integ_angle_config;
static FILE *fp_log_gyro_tap_report, *fp_log_gyro_tap_result, *fp_log_gyro_tap_config;
#endif /* FEATURE_GESTURES_REL_1 */

static FILE *fp_single_output;
static pb_algo_attrib_s pb_algo_svc[MAX_ALGO_NUM];
static int pb_algo_count = 0;
static uint64_t pb_log_mask = ~0; /* default is not to log anything */

static FILE *fp_simstatus;


/*---------------------------------------------------------------------------
* Static Function Definitions
* -------------------------------------------------------------------------*/
/*=========================================================================
  FUNCTION:  sns_playback_send_smgr_start_req_gyro
  =========================================================================*/
/*!
  @brief Send a request to sensors manager for sensor data gyro

*/
/*=======================================================================*/
static void sns_playback_send_smgr_start_req_gyro(void)
{
   sns_smr_header_s msgHdr;
   sns_smgr_periodic_report_req_msg_v01 *msgPtr;
   uint8_t msgSize = 0;
   sns_err_code_e err;

   msgSize = sizeof(sns_smgr_periodic_report_req_msg_v01);
   msgPtr =
   (sns_smgr_periodic_report_req_msg_v01 *)sns_smr_msg_alloc(SNS_DBG_NUM_MOD_IDS,msgSize);
   SNS_ASSERT(msgPtr != NULL);

   msgHdr.src_module = SNS_MODULE_DSPS_PLAYBACK;
   msgHdr.svc_num = SNS_SMGR_SVC_ID_V01;
   msgHdr.msg_type = SNS_SMR_MSG_TYPE_REQ;
   msgHdr.priority = SNS_SMR_MSG_PRI_LOW;
   msgHdr.msg_id = SNS_SMGR_REPORT_REQ_V01;
   msgHdr.body_len = msgSize;

   msgHdr.txn_id = 0;
   msgHdr.ext_clnt_id = 0;

   msgPtr->BufferFactor = 1;

   msgPtr->ReportId = 0;
   msgPtr->Action = SNS_SMGR_REPORT_ACTION_ADD_V01;

   msgPtr->ReportRate = 25;

   msgPtr->cal_sel_valid = true;
   msgPtr->cal_sel_len = 1;

   msgPtr->Item_len = 1;

   msgPtr->Item[0].SensorId = 10;
   msgPtr->Item[0].DataType = 0;      

   msgPtr->Item[0].Decimation = SNS_SMGR_DECIMATION_FILTER_V01;

   msgPtr->cal_sel[0] = SNS_SMGR_CAL_SEL_FACTORY_CAL_V01;


   sns_smr_set_hdr(&msgHdr, msgPtr);
   err = sns_smr_send(msgPtr);
   if (err != SNS_SUCCESS)
   {
      //free the message
      sns_smr_msg_free(msgPtr);
   }
}

/*=========================================================================
  FUNCTION:  playback_get_algo_svc_id
=========================================================================*/
/*!
    @brief
    Convert string into algorithm service ID

    @return
    Algorithm service ID (-1 for error)
*/
/*=======================================================================*/
static int playback_get_algo_svc_id(char *str)
{
   if (!strcmp(str, "AMD"))
      return SNS_SAM_AMD_SVC_ID_V01;
   else if (!strcmp(str, "VMD"))
      return SNS_SAM_VMD_SVC_ID_V01;
   else if (!strcmp(str, "RMD"))
      return SNS_SAM_RMD_SVC_ID_V01;
   else if (!strcmp(str, "GYRO_CAL"))
      return PB_GYRO_CAL_SVC_ID_V01;
#ifdef ENABLE_APPS_PLAYBACK
   else if (!strcmp(str, "FNS"))
      return SNS_SAM_FNS_SVC_ID_V01;
   else if (!strcmp(str, "BTE"))
      return SNS_SAM_BTE_SVC_ID_V01;
   else if (!strcmp(str, "QUATERNION"))
      return SNS_SAM_QUATERNION_SVC_ID_V01;
   else if (!strcmp(str, "GRAVITY"))
      return SNS_SAM_GRAVITY_VECTOR_SVC_ID_V01;
   else if (!strcmp(str, "FMV"))
      return SNS_SAM_FILTERED_MAG_SVC_ID_V01;
   else if (!strcmp(str, "ROTATION_VECTOR"))
      return SNS_SAM_ROTATION_VECTOR_SVC_ID_V01;
   else if (!strcmp(str, "ORIENTATION"))
      return SNS_SAM_ORIENTATION_SVC_ID_V01;
#ifdef FEATURE_GESTURES_REL_1
   else if (!strcmp(str, "BASIC_GESTURES"))
      return SNS_SAM_BASIC_GESTURES_SVC_ID_V01;
   else if (!strcmp(str, "FACING"))
      return SNS_SAM_FACING_SVC_ID_V01;
   else if (!strcmp(str, "INTEG_ANGLE"))
      return SNS_SAM_INTEG_ANGLE_SVC_ID_V01;
   else if (!strcmp(str, "GYRO_TAP"))
      return SNS_SAM_GYRO_TAP_SVC_ID_V01;
#endif /* FEATURE_GESTURES_REL_1 */
#endif /* ENABLE_APPS_PLAYBACK */

   else
      return -1;
}

/*=========================================================================
  FUNCTION:  playback_exit
=========================================================================*/
/*!
    @brief
    Exit routine to end playback program

    @return
    None
*/
/*=======================================================================*/
static void playback_exit(void)
{
   //TODO: send request for disabling algo, etc., from playback thread.
   //TODO: then clean up threads...
   // wait for some time
   uint8_t err;
   uint32_t timeout = sns_em_convert_usec_to_localtick(2000000);
   OS_FLAG_GRP *sig_ptr = sns_os_sigs_create((OS_FLAGS)0x0, &err);
   sns_os_sigs_pend(sig_ptr, 0x1, OS_FLAG_WAIT_SET_ANY, timeout, &err);

   if (fp_accel_input != NULL)
      fclose(fp_accel_input);
   if (fp_gyro_input != NULL)
      fclose(fp_gyro_input);
   if (fp_mag_input != NULL)
      fclose(fp_mag_input);
   if (fp_sensor_input != NULL)
      fclose(fp_sensor_input);

   if (fp_log_qmd_report != NULL)
      fclose(fp_log_qmd_report);
   if (fp_log_qmd_result != NULL)
      fclose(fp_log_qmd_result);
   if (fp_log_qmd_config != NULL)
      fclose(fp_log_qmd_config);
   if (fp_log_fns_report != NULL)
      fclose(fp_log_fns_report);
   if (fp_log_fns_result != NULL)
      fclose(fp_log_fns_result);
   if (fp_log_fns_config != NULL)
      fclose(fp_log_fns_config);
   if (fp_log_bte_report != NULL)
      fclose(fp_log_bte_report);
   if (fp_log_bte_result != NULL)
      fclose(fp_log_bte_result);
   if (fp_log_bte_config != NULL)
      fclose(fp_log_bte_config);
   if (fp_log_quaternion_report != NULL)
      fclose(fp_log_quaternion_report);
   if (fp_log_quaternion_result != NULL)
      fclose(fp_log_quaternion_result);
   if (fp_log_quaternion_config != NULL)
      fclose(fp_log_quaternion_config);
   if (fp_log_gravity_report != NULL)
      fclose(fp_log_gravity_report);
   if (fp_log_gravity_result != NULL)
      fclose(fp_log_gravity_result);
   if (fp_log_gravity_config != NULL)
      fclose(fp_log_gravity_config);
   if (fp_log_fmv_config != NULL)
      fclose(fp_log_fmv_config);
   if (fp_log_fmv_report != NULL)
      fclose(fp_log_fmv_report);
   if (fp_log_fmv_quat_update != NULL)
      fclose(fp_log_fmv_quat_update);
   if (fp_log_fmv_mag_update != NULL)
      fclose(fp_log_fmv_mag_update);
   if (fp_log_fmv_gyro_update != NULL)
      fclose(fp_log_fmv_gyro_update);
   if (fp_log_rotation_vector_report != NULL)
      fclose(fp_log_rotation_vector_report);
   if (fp_log_rotation_vector_result != NULL)
      fclose(fp_log_rotation_vector_result);
   if (fp_log_rotation_vector_config != NULL)
      fclose(fp_log_rotation_vector_config);
   if (fp_log_orientation_report != NULL)
      fclose(fp_log_orientation_report);
   if (fp_log_orientation_result != NULL)
      fclose(fp_log_orientation_result);
   if (fp_log_orientation_config != NULL)
      fclose(fp_log_orientation_config);
   if (fp_log_mag_cal_report != NULL)
      fclose(fp_log_mag_cal_report);
   if (fp_log_mag_cal_result != NULL)
      fclose(fp_log_mag_cal_result);
   if (fp_log_mag_cal_config != NULL)
      fclose(fp_log_mag_cal_config);
   if (fp_log_gyro_cal_report != NULL)
      fclose(fp_log_gyro_cal_report);
   if (fp_log_gyro_cal_result != NULL)
      fclose(fp_log_gyro_cal_result);
   if (fp_log_gyro_cal_config != NULL)
      fclose(fp_log_gyro_cal_config);
#ifdef FEATURE_GESTURES_REL_1
   if (fp_log_basic_gestures_report != NULL)
      fclose(fp_log_basic_gestures_report);
   if (fp_log_basic_gestures_result != NULL)
      fclose(fp_log_basic_gestures_result);
   if (fp_log_basic_gestures_config != NULL)
      fclose(fp_log_basic_gestures_config);
   if (fp_log_facing_report != NULL)
      fclose(fp_log_facing_report);
   if (fp_log_facing_result != NULL)
      fclose(fp_log_facing_result);
   if (fp_log_facing_config != NULL)
      fclose(fp_log_facing_config);
   if (fp_log_integ_angle_report != NULL)
      fclose(fp_log_integ_angle_report);
   if (fp_log_integ_angle_result != NULL)
      fclose(fp_log_integ_angle_result);
   if (fp_log_integ_angle_config != NULL)
      fclose(fp_log_integ_angle_config);
   if (fp_log_gyro_tap_report != NULL)
      fclose(fp_log_gyro_tap_report);
   if (fp_log_gyro_tap_result != NULL)
      fclose(fp_log_gyro_tap_result);
   if (fp_log_gyro_tap_config != NULL)
      fclose(fp_log_gyro_tap_config);
#endif /* FEATURE_GESTURES_REL_1 */

   if (fp_single_output != NULL)
      fclose(fp_single_output);

   fp_simstatus=fopen("simstatus.csv","w");
   fprintf(fp_simstatus,"1");
   fclose(fp_simstatus);

   exit(0);
}

/*=========================================================================
  FUNCTION:  playback_get_data
=========================================================================*/
/*!
    @brief
    Read from playback file and fill in the given sensor data structure

    @return
    sns_ddf_status_e
*/
/*=======================================================================*/
static sns_ddf_status_e playback_get_data(
   FILE **input_fpp,
   sns_ddf_sensor_data_s *data_ptr)
{
   char line[256];
   char *end_ptr;
   uint8_t i;

   if ( (input_fpp == NULL) || (*input_fpp == NULL) )
      return SNS_DDF_EBUS;

   if (fgets(line, sizeof(line), *input_fpp) != NULL)
   {
      /* sensor type */
      data_ptr->sensor = strtol(line, &end_ptr, 10);

      if (data_ptr->sensor==5387) // 150B Log 
      {

         uint8_t field8;
         uint16_t field16;
         uint32_t field32;
         uint64_t field64;

         log_150B_detected=true;

         field16=52; // $real_packet_len
         fwrite(&field16 , 1 , 2 , fp_single_output); //$ver

         field16=5387; // 150B $packet_type
         fwrite(&field16 , 1 , 2 , fp_single_output); //$ver

         field64=0; // $ts
         fwrite(&field64 , 1 , 8 , fp_single_output); //$ver

         field8=(uint8_t)strtol(end_ptr+1,&end_ptr,10);
         fwrite(&field8 , 1 , 1 , fp_single_output); //$ver

         field8=(uint8_t)strtol(end_ptr+1,&end_ptr,10);
         fwrite(&field8 , 1 , 1 , fp_single_output); //$pe_InfoValid

         field8=(uint8_t)strtol(end_ptr+1,&end_ptr,10);
         fwrite(&field8 , 1 , 1 , fp_single_output);//$pe_TTValid

         field8=(uint8_t)strtol(end_ptr+1,&end_ptr,10);
         fwrite(&field8 , 1 , 1 , fp_single_output); //$pe_ComputeValid

         field32=(uint32_t)strtol(end_ptr+1,&end_ptr,10);
         fwrite(&field32 , 1 , 4 , fp_single_output); //$q_TimeTickAtGpsTOA

         field16=(uint16_t)strtol(end_ptr+1,&end_ptr,10);
         fwrite(&field16 , 1 , 2 , fp_single_output); //$w_GpsWeek

         field32=(uint32_t)strtol(end_ptr+1,&end_ptr,10);
         fwrite(&field32 , 1 , 4 , fp_single_output); //$q_GpsMs

         field32=(uint32_t)strtol(end_ptr+1,&end_ptr,10);
         fwrite(&field32 , 1 , 4 , fp_single_output);//$q_OurTxMs

         field32=(uint32_t)strtol(end_ptr+1,&end_ptr,10);
         fwrite(&field32 , 1 , 4 , fp_single_output); //$q_TheirRxMs

         field32=(uint32_t)strtol(end_ptr+1,&end_ptr,10);
         fwrite(&field32 , 1 , 4 , fp_single_output); //$q_TheirTxMs

         field32=(uint32_t)strtol(end_ptr+1,&end_ptr,10);
         fwrite(&field32 , 1 , 4 , fp_single_output); //$q_OurRxMs

         field16=(uint16_t)strtol(end_ptr+1,&end_ptr,10);
         fwrite(&field16 , 1 , 2 , fp_single_output); //$w_Rtt

         field16=(uint16_t)strtol(end_ptr+1,&end_ptr,10);
         fwrite(&field16  , 1 , 2 , fp_single_output); //$gps_week_offset

         field32=(uint32_t)strtol(end_ptr+1,&end_ptr,10);
         fwrite(&field32 , 1 , 4 , fp_single_output); //$gps_ms_in_week_offset

         field16=(uint16_t)0;
         fwrite(&field16  , 1 , 2 , fp_single_output); //UncPpm

      }
      else
      {
         /* data type */
         strtol(end_ptr+1, &end_ptr, 10);
         /* data status */
         data_ptr->status = strtol(end_ptr+1, &end_ptr, 10);
         /* timestamp */
         data_ptr->timestamp = strtol(end_ptr+1, &end_ptr, 10);
         //axis cnt
         data_ptr->num_samples = strtol(end_ptr+1, &end_ptr, 10);

         for (i = 0; i < data_ptr->num_samples; i++)
         {
            data_ptr->samples[i].sample = strtol(end_ptr+1, &end_ptr, 10);
            data_ptr->samples[i].status = SNS_DDF_SUCCESS;
         }
      }
      return SNS_DDF_SUCCESS;
   }

   /* otherwise we've reached end of playback: close the file */
   else
   {
      fclose(*input_fpp);
      *input_fpp = 0;
      if ( (fp_accel_input==0) && (fp_gyro_input==0) && (fp_mag_input==0) && (fp_sensor_input==0) )
      {
         /* playback finishes; exit */
         playback_exit();
      }
      return SNS_DDF_EBUS;
   }
}

#ifdef SNS_PLAYBACK_SKIP_SMGR

/*=========================================================================
  FUNCTION:  playback_send_data_to_algo
=========================================================================*/
/*!
    @brief
    Send data to the algorithm (SAM) on behalf of SMGR

    @return
    none
*/
/*=======================================================================*/
static void playback_send_data_to_algo(void)
{

   sns_smr_header_s msg_header;
   sns_ddf_sensor_data_s sensor_data;
   sns_ddf_sensor_sample_s sensor_samples[3];
   sns_smgr_periodic_report_ind_msg_v01  *smgr_report_p;

   sensor_data.samples = sensor_samples;

   while (1)
   {
      uint8_t *msg_ptr;

      smgr_report_p = sns_smr_msg_alloc(SNS_DBG_NUM_MOD_IDS, sizeof(sns_smgr_periodic_report_ind_msg_v01));
      if ( smgr_report_p == NULL )
      {
         printf("Error allocating for sensor data report\n");
         exit(1);
      }

      if (fp_accel_input != NULL)
      {
         playback_get_data(&fp_accel_input, &sensor_data);
         smgr_report_p->CurrentRate = 25;
         smgr_report_p->Item_len = 1;
         smgr_report_p->Item[0].SensorId = SNS_SMGR_ID_ACCEL_V01;
      }
      else if (fp_gyro_input != NULL)
      {
         playback_get_data(&fp_gyro_input, &sensor_data);
         smgr_report_p->CurrentRate = 25;
         smgr_report_p->Item_len = 1;
         smgr_report_p->Item[0].SensorId = SNS_SMGR_ID_GYRO_V01;
      }
      else if (fp_mag_input != NULL)
      {
         playback_get_data(&fp_mag_input, &sensor_data);
         smgr_report_p->CurrentRate = 30;
         smgr_report_p->Item_len = 1;
         smgr_report_p->Item[0].SensorId = SNS_SMGR_ID_MAG_V01;
      }
      else if (fp_sensor_input != NULL)
      {
         playback_get_data(&fp_sensor_input, &sensor_data);     
         smgr_report_p->CurrentRate = 25;
         smgr_report_p->Item_len = 1;
         if (sensor_data.sensor==SNS_DDF_SENSOR_ACCEL)
            smgr_report_p->Item[0].SensorId = SNS_SMGR_ID_ACCEL_V01;
         else if (sensor_data.sensor== SNS_DDF_SENSOR_GYRO)
            smgr_report_p->Item[0].SensorId = SNS_SMGR_ID_GYRO_V01;
         else if (sensor_data.sensor==SNS_DDF_SENSOR_MAG )
            smgr_report_p->Item[0].SensorId = SNS_SMGR_ID_MAG_V01;
      }
      else
      {
         break;
      }

      if (log_150B_detected==true)
      {
         sns_smr_msg_free(smgr_report_p);
         log_150B_detected=false;
         continue;
      }


      // Report ID assignment based on specific sensor
      if (pb_algo_svc[0].svc_id==PB_GYRO_CAL_SVC_ID_V01)
      {
         if (sensor_data.sensor==SNS_DDF_SENSOR_ACCEL)
         {
            smgr_report_p->ReportId = 0; 
         }
         else if (sensor_data.sensor== SNS_DDF_SENSOR_GYRO)
         {
            smgr_report_p->ReportId = 0; 
         }
      }
      else if (pb_algo_svc[0].svc_id==SNS_SAM_GRAVITY_VECTOR_SVC_ID_V01)
      {
         if (sensor_data.sensor==SNS_DDF_SENSOR_ACCEL)
         {
            smgr_report_p->ReportId = 0; 
         }
         else if (sensor_data.sensor== SNS_DDF_SENSOR_GYRO)
         {
            smgr_report_p->ReportId = 1; 
         }
      }
      else if (pb_algo_svc[0].svc_id==SNS_SAM_FILTERED_MAG_SVC_ID_V01)
      {
         if (sensor_data.sensor==SNS_DDF_SENSOR_GYRO)
         {
            smgr_report_p->ReportId = 0; 
         }
         else if (sensor_data.sensor== SNS_DDF_SENSOR_MAG)
         {
            smgr_report_p->ReportId = 1; 
         }
      }
      else if (pb_algo_svc[0].svc_id==SNS_SAM_ROTATION_VECTOR_SVC_ID_V01)
      {
         if (sensor_data.sensor==SNS_DDF_SENSOR_ACCEL)
         {
            smgr_report_p->ReportId = 0; 
         }
         else if (sensor_data.sensor== SNS_DDF_SENSOR_GYRO)
         {
            smgr_report_p->ReportId = 1;
         }
         else if (sensor_data.sensor== SNS_DDF_SENSOR_MAG)
         {
            smgr_report_p->ReportId = 2; 
         }
      }
      else if (pb_algo_svc[0].svc_id==SNS_SAM_ORIENTATION_SVC_ID_V01)
      {
         if (sensor_data.sensor==SNS_DDF_SENSOR_ACCEL)
         {
            smgr_report_p->ReportId = 0; 
         }
         else if (sensor_data.sensor== SNS_DDF_SENSOR_MAG)
         {
            smgr_report_p->ReportId = 1; 
         }
      }
/*
#ifdef FEATURE_GESTURES_REL_1
      else if (pb_algo_svc[0].svc_id==SNS_SAM_GYRO_TAP_SVC_ID_V01)
      {
         if (sensor_data.sensor==SNS_DDF_SENSOR_ACCEL)
         {
            smgr_report_p->ReportId = 0; 
         }
         else if (sensor_data.sensor== SNS_DDF_SENSOR_GYRO)
         {
            smgr_report_p->ReportId = 1; 
         }

      }
#endif // FEATURE_GESTURES_REL_1
*/
      else  // Other Algos
      {
         smgr_report_p->ReportId = 0;
      }

      smgr_report_p->status = SNS_SMGR_REPORT_OK_V01;
      smgr_report_p->Item[0].DataType = SNS_SMGR_DATA_TYPE_PRIMARY_V01;
      smgr_report_p->Item[0].ItemFlags = 0;
      smgr_report_p->Item[0].ItemQuality = SNS_SMGR_ITEM_QUALITY_CURRENT_SAMPLE_V01;
      smgr_report_p->Item[0].TimeStamp = sensor_data.timestamp;
      smgr_report_p->Item[0].ItemData[0] = sensor_data.samples[0].sample;
      smgr_report_p->Item[0].ItemData[1] = sensor_data.samples[1].sample;
      smgr_report_p->Item[0].ItemData[2] = sensor_data.samples[2].sample;


#ifdef FEATURE_GESTURES_REL_1
	 if (pb_algo_svc[0].svc_id==SNS_SAM_GYRO_TAP_SVC_ID_V01)
	 {
        // default rate is 200Hz
		smgr_report_p->CurrentRate = 200;

	    // get gyro from data set, in addition to accel
		playback_get_data(&fp_sensor_input, &sensor_data);   
        if (sensor_data.sensor== SNS_DDF_SENSOR_GYRO)
		{
		   smgr_report_p->Item_len = 2;

		   smgr_report_p->Item[1].SensorId = SNS_SMGR_ID_GYRO_V01;
		   smgr_report_p->Item[1].DataType = SNS_SMGR_DATA_TYPE_PRIMARY_V01;
		   smgr_report_p->Item[1].ItemFlags = 0;
		   smgr_report_p->Item[1].ItemQuality = SNS_SMGR_ITEM_QUALITY_CURRENT_SAMPLE_V01;
		   smgr_report_p->Item[1].TimeStamp = sensor_data.timestamp;
		   smgr_report_p->Item[1].ItemData[0] = sensor_data.samples[0].sample;
		   smgr_report_p->Item[1].ItemData[1] = sensor_data.samples[1].sample;
		   smgr_report_p->Item[1].ItemData[2] = sensor_data.samples[2].sample;
		}
    }
#endif // FEATURE_GESTURES_REL_1


      msg_header.src_module = SNS_MODULE_DSPS_SMGR;

      if (pb_algo_svc[0].svc_id==PB_GYRO_CAL_SVC_ID_V01)
      {
         if (sensor_data.sensor==SNS_DDF_SENSOR_ACCEL)
         {
            msg_header.dst_module = SNS_SAM_MODULE; //SNS_MODULE_DSPS_SAM; 
         }
         else if (sensor_data.sensor== SNS_DDF_SENSOR_GYRO)
         {
            msg_header.dst_module = SNS_MODULE_DSPS_SCM; 
         }
      }
      else
      {
         msg_header.dst_module = SNS_SAM_MODULE; /* TODO: also support APPS_SAM */
      }

      msg_header.priority = SNS_SMR_MSG_PRI_LOW;
      msg_header.msg_type = SNS_SMR_MSG_TYPE_IND;
      msg_header.svc_num = SNS_SMGR_SVC_ID_V01;
      msg_header.msg_id = SNS_SMGR_REPORT_IND_V01;
      msg_header.ext_clnt_id = 0;
      msg_header.txn_id = 0;
      msg_header.body_len = sizeof(sns_smgr_periodic_report_ind_msg_v01);

      sns_smr_set_hdr (&msg_header, smgr_report_p);
      if (sns_smr_send(smgr_report_p)!= SNS_SUCCESS)
      {
         sns_smr_msg_free(smgr_report_p);
      }

      //check for messages and free them
      while ( (msg_ptr = (uint8_t*)sns_smr_rcv(SNS_MODULE_DSPS_PLAYBACK)) )
      {
         sns_smr_msg_free(msg_ptr);
      }
   }
}
#endif

#ifndef QDSP6
static void playback_upload_reg_data(uint8_t *data, int offset, int size)
{
   uint32_t bytes;
   sns_err_code_e err;
   void *file_handle;

   file_handle = sns_fsa_open(sns_reg_filename, "r+");
   if (NULL == file_handle)
   {
      file_handle = sns_fsa_open(sns_reg_filename, "w");
   }

   if (NULL != file_handle)
   {
      /* start at offset bytes from the beginning of file */
      err = sns_fsa_seek(file_handle, (int64_t)offset, 0); 
      if (SNS_SUCCESS == err)
      {
         err = sns_fsa_write(file_handle, data, (uint32_t)size, &bytes);
      }
      sns_fsa_close(file_handle);
   }

   printf("Uploaded registry at offset %d with size %d\n", offset, size);
}
#endif

/*=========================================================================
  FUNCTION:  sns_playback_parse_config
=========================================================================*/
/*!
    @brief
    Parse config file for playback

    @return
    None
*/
/*=======================================================================*/
void sns_playback_parse_config(char *fname)
{
   char line[256];
   char *pch;
   char key[60], val[60];
   int algo_svc_id;
   FILE *fp_config;

   if ((fp_config = fopen(fname, "r")) == NULL)
   {
      printf("Cannot open %s\n", fname);
      exit(1);
   }

   while (fgets(line, sizeof(line), fp_config) != NULL)
   {
      int nchar;
      /* skip comments */
      if ( (pch = strstr(line, "//")) )
         continue;

      if (sscanf(line, "%s %s %n", key, val, &nchar) == 2)
      {

         if (!strcmp(key, "ALGO_SVC"))
         {
            algo_svc_id = playback_get_algo_svc_id(val);
            if (algo_svc_id != -1)
            {
               int config_param;
               int num_elem = 0;
               pb_algo_svc[pb_algo_count].svc_id = algo_svc_id;
               pb_algo_svc[pb_algo_count].num_config_elem = 0;

               /* fill in pb_algo_svc[pb_algo_count].algo_config */
               pch = line + nchar;  /* skip directly to algo_config part */
               while (sscanf(pch, "%d%n", &config_param, &nchar) == 1)
               {
                  pb_algo_svc[pb_algo_count].algo_config[num_elem] = config_param;
                  num_elem++;
                  pch += nchar;
               }
               pb_algo_svc[pb_algo_count].num_config_elem = num_elem;
               if (num_elem < 1)
               {
                  printf("Error: algo should take at least one parameter\n");
                  exit(1);
               }

               pb_algo_count++;
               if (pb_algo_count >= MAX_ALGO_NUM)
               {
                  printf("Error: exceeds maximum number of algorithms\n");
                  exit(1);
               }
            }
         }
#ifndef QDSP6
         else if (!strcmp(key, "REG_FILE"))
         {
            void *file_handle = NULL;

            /* obtain registry file name, ensure null ending */
            strncpy(sns_reg_filename, val, sizeof(sns_reg_filename)-1);
            sns_reg_filename[sizeof(sns_reg_filename)-1] = '\0';

            file_handle = sns_fsa_open( sns_reg_filename, "r" );
            if (NULL != file_handle)
            {
               /* registry file already exists, don't touch it */
               sns_fsa_close( file_handle );
            }
            else
            {
               /* if the file doesn't exist, create one with default items */
               for (i = 0; i < SNS_REG_GROUP_COUNT; i++)
               {
                  sns_group_data_init(sns_reg_group_info[i].group_id,
                                      (void *)reg_data);
                  playback_upload_reg_data((uint8_t*)reg_data,
                                           sns_reg_group_info[i].offset,
                                           sns_reg_group_info[i].size);
               }
            }
         }
         else if (!strcmp(key, "REG_GROUP_AMD"))
         {
            reg_index = -1;
            reg_data[0] = atol(val);
            reg_data_elem = 1;
            pch = line + nchar;
            while (sscanf(pch, "%d%n", (int*)&reg_data[reg_data_elem], &nchar) == 1)
            {
               reg_data_elem++;
               pch += nchar;
            }

            for (i = 0; i < SNS_REG_GROUP_COUNT; i++)
            {
               if (SNS_REG_SAM_GROUP_AMD_V01 == sns_reg_group_info[i].group_id)
               {
                  reg_index = i;
                  break;
               }
            }
            if ( (reg_index == -1) || (reg_data_elem != 3) )
            {
               printf("Error: registry group and items don't match\n");
               continue;
            }

            playback_upload_reg_data((uint8 *)reg_data,
                                     sns_reg_group_info[reg_index].offset,
                                     sns_reg_group_info[reg_index].size);
         }
         else if (!strcmp(key, "REG_GROUP_VMD"))
         {
            reg_index = -1;
            reg_data[0] = atol(val);
            reg_data_elem = 1;
            pch = line + nchar;
            while (sscanf(pch, "%d%n", (int*)&reg_data[reg_data_elem], &nchar) == 1)
            {
               reg_data_elem++;
               pch += nchar;
            }
            for (i = 0; i < SNS_REG_GROUP_COUNT; i++)
            {
               if (SNS_REG_SAM_GROUP_VMD_V01 == sns_reg_group_info[i].group_id)
               {
                  reg_index = i;
                  break;
               }
            }
            if ( (reg_index == -1) || (reg_data_elem != 3) )
            {
               printf("Error: registry group and items don't match\n");
               continue;
            }

            playback_upload_reg_data((uint8 *)reg_data,
                                     sns_reg_group_info[reg_index].offset,
                                     sns_reg_group_info[reg_index].size);
         }
         else if (!strcmp(key, "REG_GROUP_RMD"))
         {
            reg_index = -1;
            reg_data[0] = atol(val);
            reg_data_elem = 1;
            pch = line + nchar;
            while (sscanf(pch, "%d%n", (int*)&reg_data[reg_data_elem], &nchar) == 1)
            {
               reg_data_elem++;
               pch += nchar;
            }

            for (i = 0; i < SNS_REG_GROUP_COUNT; i++)
            {
               if (SNS_REG_SAM_GROUP_RMD_V01 == sns_reg_group_info[i].group_id)
               {
                  reg_index = i;
                  break;
               }
            }
            if ( (reg_index == -1) || (reg_data_elem != 5) )
            {
               printf("Error: registry group and items don't match\n");
               continue;
            }

            playback_upload_reg_data((uint8 *)reg_data,
                                     sns_reg_group_info[reg_index].offset,
                                     sns_reg_group_info[reg_index].size);
         }
#endif
         else if (!strcmp(key, "INPUT_ACCEL"))
         {
            fp_accel_input = fopen(val, "r");
            if (fp_accel_input == NULL)
            {
               printf("Cannot open %s\n", val);
               exit(1);
            }
         }
         else if (!strcmp(key, "INPUT_GYRO"))
         {
            fp_gyro_input = fopen(val, "r");
            if (fp_gyro_input == NULL)
            {
               printf("Cannot open %s\n", val);
               exit(1);
            }

         }
         else if (!strcmp(key, "INPUT_MAG"))
         {
            fp_mag_input = fopen(val, "r");
            if (fp_mag_input == NULL)
            {
               printf("Cannot open %s\n", val);
               exit(1);
            }

         }
         else if (!strcmp(key, "INPUT_SENSOR"))
         {
            fp_sensor_input = fopen(val, "r");
            if (fp_sensor_input == NULL)
            {
               printf("Cannot open %s\n", val);
               exit(1);
            }

         }
         else if (!strcmp(key, "LOG_SINGLE_OUTPUT"))
         {
            fp_single_output = fopen(val, "wb");
            if (fp_single_output == NULL)
            {
               printf("Cannot open %s\n", val);
               exit(1);
            }
         }
         else if (!strcmp(key, "LOG_QMD_REPORT"))
         {
            pb_log_mask &= ~((uint64_t)1 << SNS_LOG_QMD_REPORT);

            // If Single Output file has been requested use that file ptr
            if (fp_single_output==NULL)
               fp_log_qmd_report = fopen(val, "wb");
            else
               fp_log_qmd_report = fp_single_output;

            if (fp_log_qmd_report == NULL)
            {
               printf("Cannot open %s\n", val);
               exit(1);
            }
         }
         else if (!strcmp(key, "LOG_QMD_RESULT"))
         {
            pb_log_mask &= ~((uint64_t)1 << SNS_LOG_QMD_RESULT);

            // If Single Output file has been requested use that file ptr
            if (fp_single_output==NULL)
               fp_log_qmd_result = fopen(val, "wb");
            else
               fp_log_qmd_result = fp_single_output;

            if (fp_log_qmd_result == NULL)
            {
               printf("Cannot open %s\n", val);
               exit(1);
            }
         }
         else if (!strcmp(key, "LOG_QMD_CONFIG"))
         {
            pb_log_mask &= ~((uint64_t)1 << SNS_LOG_QMD_CONFIG);

            // If Single Output file has been requested use that file ptr
            if (fp_single_output==NULL)
               fp_log_qmd_config = fopen(val, "wb");
            else
               fp_log_qmd_config = fp_single_output;

            if (fp_log_qmd_config == NULL)
            {
               printf("Cannot open %s\n", val);
               exit(1);
            }
         }
#ifdef ENABLE_APPS_PLAYBACK
         else if (!strcmp(key, "LOG_FNS_REPORT"))
         {
            pb_log_mask &= ~((uint64_t)1 << SNS_LOG_FNS_REPORT);

            // If Single Output file has been requested use that file ptr
            if (fp_single_output==NULL)
               fp_log_fns_report = fopen(val, "wb");
            else
               fp_log_fns_report = fp_single_output;

            if (fp_log_fns_report == NULL)
            {
               printf("Cannot open %s\n", val);
               exit(1);
            }
         }
         else if (!strcmp(key, "LOG_FNS_RESULT"))
         {
            pb_log_mask &= ~((uint64_t)1 << SNS_LOG_FNS_RESULT);

            // If Single Output file has been requested use that file ptr
            if (fp_single_output==NULL)
               fp_log_fns_result = fopen(val, "wb");
            else
               fp_log_fns_result = fp_single_output;

            if (fp_log_fns_result == NULL)
            {
               printf("Cannot open %s\n", val);
               exit(1);
            }
         }
         else if (!strcmp(key, "LOG_FNS_CONFIG"))
         {
            pb_log_mask &= ~((uint64_t)1 << SNS_LOG_FNS_CONFIG);

            // If Single Output file has been requested use that file ptr
            if (fp_single_output==NULL)
               fp_log_fns_config = fopen(val, "wb");
            else
               fp_log_fns_config = fp_single_output;

            if (fp_log_fns_config == NULL)
            {
               printf("Cannot open %s\n", val);
               exit(1);
            }
         }
         else if (!strcmp(key, "LOG_BTE_REPORT"))
         {
            pb_log_mask &= ~((uint64_t)1 << SNS_LOG_BTE_REPORT);

            // If Single Output file has been requested use that file ptr
            if (fp_single_output==NULL)
               fp_log_bte_report = fopen(val, "wb");
            else
               fp_log_bte_report = fp_single_output;

            if (fp_log_bte_report == NULL)
            {
               printf("Cannot open %s\n", val);
               exit(1);
            }
         }
         else if (!strcmp(key, "LOG_BTE_RESULT"))
         {
            pb_log_mask &= ~((uint64_t)1 << SNS_LOG_BTE_RESULT);

            // If Single Output file has been requested use that file ptr
            if (fp_single_output==NULL)
               fp_log_bte_result = fopen(val, "wb");
            else
               fp_log_bte_result = fp_single_output;

            if (fp_log_bte_result == NULL)
            {
               printf("Cannot open %s\n", val);
               exit(1);
            }
         }
         else if (!strcmp(key, "LOG_BTE_CONFIG"))
         {
            pb_log_mask &= ~((uint64_t)1 << SNS_LOG_BTE_CONFIG);

            // If Single Output file has been requested use that file ptr
            if (fp_single_output==NULL)
               fp_log_bte_config = fopen(val, "wb");
            else
               fp_log_bte_config = fp_single_output;

            if (fp_log_bte_config == NULL)
            {
               printf("Cannot open %s\n", val);
               exit(1);
            }
         }
         else if (!strcmp(key, "LOG_QUATERNION_REPORT"))
         {
            pb_log_mask &= ~((uint64_t)1 << SNS_LOG_QUAT_REPORT);

            // If Single Output file has been requested use that file ptr
            if (fp_single_output==NULL)
               fp_log_quaternion_report = fopen(val, "wb");
            else
               fp_log_quaternion_report = fp_single_output;

            if (fp_log_quaternion_report == NULL)
            {
               printf("Cannot open %s\n", val);
               exit(1);
            }
         }
         else if (!strcmp(key, "LOG_QUATERNION_RESULT"))
         {
            pb_log_mask &= ~((uint64_t)1 << SNS_LOG_QUAT_RESULT);

            // If Single Output file has been requested use that file ptr
            if (fp_single_output==NULL)
               fp_log_quaternion_result = fopen(val, "wb");
            else
               fp_log_quaternion_result = fp_single_output;

            if (fp_log_quaternion_result == NULL)
            {
               printf("Cannot open %s\n", val);
               exit(1);
            }
         }
         else if (!strcmp(key, "LOG_QUATERNION_CONFIG"))
         {
            pb_log_mask &= ~((uint64_t)1 << SNS_LOG_QUAT_CONFIG);

            // If Single Output file has been requested use that file ptr
            if (fp_single_output==NULL)
               fp_log_quaternion_config = fopen(val, "wb");
            else
               fp_log_quaternion_config = fp_single_output;

            if (fp_log_quaternion_config == NULL)
            {
               printf("Cannot open %s\n", val);
               exit(1);
            }
         }
         else if (!strcmp(key, "LOG_GRAVITY_REPORT"))
         {
            pb_log_mask &= ~((uint64_t)1 << SNS_LOG_GRAVITY_REPORT);

            // If Single Output file has been requested use that file ptr
            if (fp_single_output==NULL)
               fp_log_gravity_report = fopen(val, "wb");
            else
               fp_log_gravity_report = fp_single_output;

            if (fp_log_gravity_report == NULL)
            {
               printf("Cannot open %s\n", val);
               exit(1);
            }
         }
         else if (!strcmp(key, "LOG_GRAVITY_RESULT"))
         {
            pb_log_mask &= ~((uint64_t)1 << SNS_LOG_GRAVITY_RESULT);

            // If Single Output file has been requested use that file ptr
            if (fp_single_output==NULL)
               fp_log_gravity_result = fopen(val, "wb");
            else
               fp_log_gravity_result = fp_single_output;


            if (fp_log_gravity_result == NULL)
            {
               printf("Cannot open %s\n", val);
               exit(1);
            }
         }
         else if (!strcmp(key, "LOG_GRAVITY_CONFIG"))
         {
            pb_log_mask &= ~((uint64_t)1 << SNS_LOG_GRAVITY_CONFIG);

            // If Single Output file has been requested use that file ptr
            if (fp_single_output==NULL)
               fp_log_gravity_config = fopen(val, "wb");
            else
               fp_log_gravity_config = fp_single_output;

            if (fp_log_gravity_config == NULL)
            {
               printf("Cannot open %s\n", val);
               exit(1);
            }
         }
         else if (!strcmp(key, "LOG_FMV_REPORT"))
         {
            pb_log_mask &= ~((uint64_t)1 << SNS_LOG_FMV_REPORT);

            // If Single Output file has been requested use that file ptr
            if (fp_single_output==NULL)
               fp_log_fmv_report = fopen(val, "wb");
            else
               fp_log_fmv_report = fp_single_output;

            if (fp_log_fmv_report == NULL)
            {
               printf("Cannot open %s\n", val);
               exit(1);
            }
         }
         else if (!strcmp(key, "LOG_FMV_CONFIG"))
         {
            pb_log_mask &= ~((uint64_t)1 << SNS_LOG_FMV_CONFIG);

            // If Single Output file has been requested use that file ptr
            if (fp_single_output==NULL)
               fp_log_fmv_config = fopen(val, "wb");
            else
               fp_log_fmv_config = fp_single_output;

            if (fp_log_fmv_config == NULL)
            {
               printf("Cannot open %s\n", val);
               exit(1);
            }
         }
         else if (!strcmp(key, "LOG_FMV_QUAT_UPDATE"))
         {
            pb_log_mask &= ~((uint64_t)1 << SNS_LOG_FMV_QUAT_UPDATE);

            // If Single Output file has been requested use that file ptr
            if (fp_single_output==NULL)
               fp_log_fmv_quat_update = fopen(val, "wb");
            else
               fp_log_fmv_quat_update = fp_single_output;

            if (fp_log_fmv_quat_update == NULL)
            {
               printf("Cannot open %s\n", val);
               exit(1);
            }
         }
         else if (!strcmp(key, "LOG_FMV_MAG_UPDATE"))
         {
            pb_log_mask &= ~((uint64_t)1 << SNS_LOG_FMV_MAG_UPDATE);

            // If Single Output file has been requested use that file ptr
            if (fp_single_output==NULL)
               fp_log_fmv_mag_update = fopen(val, "wb");
            else
               fp_log_fmv_mag_update = fp_single_output;

            if (fp_log_fmv_mag_update == NULL)
            {
               printf("Cannot open %s\n", val);
               exit(1);
            }
         }
         else if (!strcmp(key, "LOG_FMV_GYRO_UPDATE"))
         {
            pb_log_mask &= ~((uint64_t)1 << SNS_LOG_FMV_GYRO_UPDATE);

            // If Single Output file has been requested use that file ptr
            if (fp_single_output==NULL)
               fp_log_fmv_gyro_update = fopen(val, "wb");
            else
               fp_log_fmv_gyro_update = fp_single_output;

            if (fp_log_fmv_gyro_update == NULL)
            {
               printf("Cannot open %s\n", val);
               exit(1);
            }
         }
         else if (!strcmp(key, "LOG_ROTATION_VECTOR_REPORT"))
         {
            pb_log_mask &= ~((uint64_t)1 << SNS_LOG_ROTATION_VECTOR_REPORT);

            // If Single Output file has been requested use that file ptr
            if (fp_single_output==NULL)
               fp_log_rotation_vector_report = fopen(val, "wb");
            else
               fp_log_rotation_vector_report = fp_single_output;

            if (fp_log_rotation_vector_report == NULL)
            {
               printf("Cannot open %s\n", val);
               exit(1);
            }
         }
         else if (!strcmp(key, "LOG_ROTATION_VECTOR_RESULT"))
         {
            pb_log_mask &= ~((uint64_t)1 << SNS_LOG_ROTATION_VECTOR_RESULT);

            // If Single Output file has been requested use that file ptr
            if (fp_single_output==NULL)
               fp_log_rotation_vector_result = fopen(val, "wb");
            else
               fp_log_rotation_vector_result = fp_single_output;

            if (fp_log_rotation_vector_result == NULL)
            {
               printf("Cannot open %s\n", val);
               exit(1);
            }
         }
         else if (!strcmp(key, "LOG_ROTATION_VECTOR_CONFIG"))
         {
            pb_log_mask &= ~((uint64_t)1 << SNS_LOG_ROTATION_VECTOR_CONFIG);

            // If Single Output file has been requested use that file ptr
            if (fp_single_output==NULL)
               fp_log_rotation_vector_config = fopen(val, "wb");
            else
               fp_log_rotation_vector_config = fp_single_output;

            if (fp_log_rotation_vector_config == NULL)
            {
               printf("Cannot open %s\n", val);
               exit(1);
            }
         }
         else if (!strcmp(key, "LOG_ORIENTATION_REPORT"))
         {
            pb_log_mask &= ~((uint64_t)1 << SNS_LOG_ROTATION_VECTOR_REPORT);

            // If Single Output file has been requested use that file ptr
            if (fp_single_output==NULL)
               fp_log_orientation_report = fopen(val, "wb");
            else
               fp_log_orientation_report = fp_single_output;

            if (fp_log_orientation_report == NULL)
            {
               printf("Cannot open %s\n", val);
               exit(1);
            }
         }
         else if (!strcmp(key, "LOG_ORIENTATION_RESULT"))
         {
            pb_log_mask &= ~((uint64_t)1 << SNS_LOG_ROTATION_VECTOR_RESULT);

            // If Single Output file has been requested use that file ptr
            if (fp_single_output==NULL)
               fp_log_orientation_result = fopen(val, "wb");
            else
               fp_log_orientation_result = fp_single_output;

            if (fp_log_orientation_result == NULL)
            {
               printf("Cannot open %s\n", val);
               exit(1);
            }
         }
         else if (!strcmp(key, "LOG_ORIENTATION_CONFIG"))
         {
            pb_log_mask &= ~((uint64_t)1 << SNS_LOG_ROTATION_VECTOR_CONFIG);

            // If Single Output file has been requested use that file ptr
            if (fp_single_output==NULL)
               fp_log_orientation_config = fopen(val, "wb");
            else
               fp_log_orientation_config = fp_single_output;

            if (fp_log_orientation_config == NULL)
            {
               printf("Cannot open %s\n", val);
               exit(1);
            }
         }
         else if (!strcmp(key, "LOG_MAG_CAL_CONFIG"))
         {
            pb_log_mask &= ~((uint64_t)1 << SNS_LOG_MAG_CAL_CONFIG);

            // If Single Output file has been requested use that file ptr
            if (fp_single_output==NULL)
               fp_log_mag_cal_config = fopen(val, "wb");
            else
               fp_log_mag_cal_config = fp_single_output;

            if (fp_log_mag_cal_config == NULL)
            {
               printf("Cannot open %s\n", val);
               exit(1);
            }
         }
         else if (!strcmp(key, "LOG_MAG_CAL_RESULT"))
         {
            pb_log_mask &= ~((uint64_t)1 << SNS_LOG_MAG_CAL_RESULT);

            // If Single Output file has been requested use that file ptr
            if (fp_single_output==NULL)
               fp_log_mag_cal_result = fopen(val, "wb");
            else
               fp_log_mag_cal_result = fp_single_output;

            if (fp_log_mag_cal_result == NULL)
            {
               printf("Cannot open %s\n", val);
               exit(1);
            }
         }
         else if (!strcmp(key, "LOG_MAG_CAL_REPORT"))
         {
            pb_log_mask &= ~((uint64_t)1 << SNS_LOG_MAG_CAL_REPORT);

            // If Single Output file has been requested use that file ptr
            if (fp_single_output==NULL)
               fp_log_mag_cal_report = fopen(val, "wb");
            else
               fp_log_mag_cal_report = fp_single_output;

            if (fp_log_mag_cal_report == NULL)
            {
               printf("Cannot open %s\n", val);
               exit(1);
            }
         }
#ifdef FEATURE_GESTURES_REL_1
         else if (!strcmp(key, "LOG_BASIC_GESTURES_REPORT"))
         {
            pb_log_mask &= ~((uint64_t)1 << SNS_LOG_BASIC_GESTURES_REPORT);

            // If Single Output file has been requested use that file ptr
            if (fp_single_output==NULL)
               fp_log_basic_gestures_report = fopen(val, "wb");
            else
               fp_log_basic_gestures_report = fp_single_output;

            if (fp_log_basic_gestures_report == NULL)
            {
               printf("Cannot open %s\n", val);
               exit(1);
            }
         }
         else if (!strcmp(key, "LOG_BASIC_GESTURES_RESULT"))
         {
            pb_log_mask &= ~((uint64_t)1 << SNS_LOG_BASIC_GESTURES_RESULT);

            // If Single Output file has been requested use that file ptr
            if (fp_single_output==NULL)
               fp_log_basic_gestures_result = fopen(val, "wb");
            else
               fp_log_basic_gestures_result = fp_single_output;

            if (fp_log_basic_gestures_result == NULL)
            {
               printf("Cannot open %s\n", val);
               exit(1);
            }
         }
         else if (!strcmp(key, "LOG_BASIC_GESTURES_CONFIG"))
         {
            pb_log_mask &= ~((uint64_t)1 << SNS_LOG_BASIC_GESTURES_CONFIG);

            // If Single Output file has been requested use that file ptr
            if (fp_single_output==NULL)
               fp_log_basic_gestures_config = fopen(val, "wb");
            else
               fp_log_basic_gestures_config = fp_single_output;

            if (fp_log_basic_gestures_config == NULL)
            {
               printf("Cannot open %s\n", val);
               exit(1);
            }
         }
         else if (!strcmp(key, "LOG_FACING_REPORT"))
         {
            pb_log_mask &= ~((uint64_t)1 << SNS_LOG_FACING_REPORT);

            // If Single Output file has been requested use that file ptr
            if (fp_single_output==NULL)
               fp_log_facing_report = fopen(val, "wb");
            else
               fp_log_facing_report = fp_single_output;

            if (fp_log_facing_report == NULL)
            {
               printf("Cannot open %s\n", val);
               exit(1);
            }
         }
         else if (!strcmp(key, "LOG_FACING_RESULT"))
         {
            pb_log_mask &= ~((uint64_t)1 << SNS_LOG_FACING_RESULT);

            // If Single Output file has been requested use that file ptr
            if (fp_single_output==NULL)
               fp_log_facing_result = fopen(val, "wb");
            else
               fp_log_facing_result = fp_single_output;

            if (fp_log_facing_result == NULL)
            {
               printf("Cannot open %s\n", val);
               exit(1);
            }
         }
         else if (!strcmp(key, "LOG_FACING_CONFIG"))
         {
            pb_log_mask &= ~((uint64_t)1 << SNS_LOG_FACING_CONFIG);

            // If Single Output file has been requested use that file ptr
            if (fp_single_output==NULL)
               fp_log_facing_config = fopen(val, "wb");
            else
               fp_log_facing_config = fp_single_output;

            if (fp_log_facing_config == NULL)
            {
               printf("Cannot open %s\n", val);
               exit(1);
            }
         }
         else if (!strcmp(key, "LOG_INTEG_ANGLE_CONFIG"))
         {
            pb_log_mask &= ~((uint64_t)1 << SNS_LOG_INTEG_ANGLE_CONFIG);

            // If Single Output file has been requested use that file ptr
            if (fp_single_output==NULL)
               fp_log_integ_angle_config = fopen(val, "wb");
            else
               fp_log_integ_angle_config = fp_single_output;

            if (fp_log_integ_angle_config == NULL)
            {
               printf("Cannot open %s\n", val);
               exit(1);
            }
         }
         else if (!strcmp(key, "LOG_INTEG_ANGLE_REPORT"))
         {
            pb_log_mask &= ~((uint64_t)1 << SNS_LOG_INTEG_ANGLE_REPORT);

            // If Single Output file has been requested use that file ptr
            if (fp_single_output==NULL)
               fp_log_integ_angle_report = fopen(val, "wb");
            else
               fp_log_integ_angle_report = fp_single_output;

            if (fp_log_integ_angle_report == NULL)
            {
               printf("Cannot open %s\n", val);
               exit(1);
            }
         }
         else if (!strcmp(key, "LOG_INTEG_ANGLE_RESULT"))
         {
            pb_log_mask &= ~((uint64_t)1 << SNS_LOG_INTEG_ANGLE_RESULT);

            // If Single Output file has been requested use that file ptr
            if (fp_single_output==NULL)
               fp_log_integ_angle_result = fopen(val, "wb");
            else
               fp_log_integ_angle_result = fp_single_output;

            if (fp_log_integ_angle_result == NULL)
            {
               printf("Cannot open %s\n", val);
               exit(1);
            }
         }
         else if (!strcmp(key, "LOG_GYRO_TAP_CONFIG"))
         {
            pb_log_mask &= ~((uint64_t)1 << SNS_LOG_GYRO_TAP_CONFIG);

            // If Single Output file has been requested use that file ptr
            if (fp_single_output==NULL)
               fp_log_integ_angle_config = fopen(val, "wb");
            else
               fp_log_integ_angle_config = fp_single_output;

            if (fp_log_integ_angle_config == NULL)
            {
               printf("Cannot open %s\n", val);
               exit(1);
            }
         }
         else if (!strcmp(key, "LOG_GYRO_TAP_REPORT"))
         {
            pb_log_mask &= ~((uint64_t)1 << SNS_LOG_GYRO_TAP_REPORT);

            // If Single Output file has been requested use that file ptr
            if (fp_single_output==NULL)
               fp_log_gyro_tap_report = fopen(val, "wb");
            else
               fp_log_gyro_tap_report = fp_single_output;

            if (fp_log_gyro_tap_report == NULL)
            {
               printf("Cannot open %s\n", val);
               exit(1);
            }
         }
         else if (!strcmp(key, "LOG_GYRO_TAP_RESULT"))
         {
            pb_log_mask &= ~((uint64_t)1 << SNS_LOG_GYRO_TAP_RESULT);

            // If Single Output file has been requested use that file ptr
            if (fp_single_output==NULL)
               fp_log_gyro_tap_result = fopen(val, "wb");
            else
               fp_log_gyro_tap_result = fp_single_output;

            if (fp_log_gyro_tap_result == NULL)
            {
               printf("Cannot open %s\n", val);
               exit(1);
            }
         }

#endif /* FEATURE_GESTURES_REL_1 */
#endif /* ENABLE_APPS_PLAYBACK */
         else if (!strcmp(key, "LOG_GYRO_CAL_CONFIG"))
         {
            pb_log_mask &= ~((uint64_t)1 << SNS_LOG_GYRO_CAL_CONFIG);

            // If Single Output file has been requested use that file ptr
            if (fp_single_output==NULL)
               fp_log_gyro_cal_config = fopen(val, "wb");
            else
               fp_log_gyro_cal_config = fp_single_output;

            if (fp_log_gyro_cal_config == NULL)
            {
               printf("Cannot open %s\n", val);
               exit(1);
            }
         }
         else if (!strcmp(key, "LOG_GYRO_CAL_RESULT"))
         {
            pb_log_mask &= ~((uint64_t)1 << SNS_LOG_GYRO_CAL_RESULT);

            // If Single Output file has been requested use that file ptr
            if (fp_single_output==NULL)
               fp_log_gyro_cal_result = fopen(val, "wb");
            else
               fp_log_gyro_cal_result = fp_single_output;

            if (fp_log_gyro_cal_result == NULL)
            {
               printf("Cannot open %s\n", val);
               exit(1);
            }
         }
         else if (!strcmp(key, "LOG_GYRO_CAL_REPORT"))
         {
            pb_log_mask &= ~((uint64_t)1 << SNS_LOG_GYRO_CAL_REPORT);

            // If Single Output file has been requested use that file ptr
            if (fp_single_output==NULL)
               fp_log_gyro_cal_report = fopen(val, "wb");
            else
               fp_log_gyro_cal_report = fp_single_output;

            if (fp_log_gyro_cal_report == NULL)
            {
               printf("Cannot open %s\n", val);
               exit(1);
            }
         }
      }
   }

   fclose(fp_config);
   return;
}

/*=========================================================================
  FUNCTION:  sns_playback_enable_log
=========================================================================*/
/*!
    @brief
    Enable output logging

    @return
    None
*/
/*=======================================================================*/
void sns_playback_enable_log(void)
{
   sns_diag_set_log_mask_req_msg_v01 msgPtr;

   msgPtr.log_mask.mask = pb_log_mask;
   sns_diag_dsps_set_log_mask(&msgPtr);
#ifndef ENABLE_APPS_PLAYBACK

#endif
   return;
}

/*=========================================================================
  FUNCTION:  sns_playback_disable_log
=========================================================================*/
/*!
    @brief
    Disable output logging

    @return
    None
*/
/*=======================================================================*/
void sns_playback_disable_log(void)
{
#ifndef ENABLE_APPS_PLAYBACK
   sns_diag_set_log_mask_req_msg_v01 msgPtr;

   msgPtr.log_mask.mask = ~0;
   sns_diag_dsps_set_log_mask(&msgPtr);
#endif
   return;
}

/*=========================================================================
  FUNCTION:  sns_playback_enable_algo
=========================================================================*/
/*!
    @brief
    Sends message enabling specified algorithm service

    @return
    None
*/
/*=======================================================================*/
void sns_playback_enable_algo(void)
{
   uint8_t *msgPtr = NULL;
   sns_smr_header_s msgHdr;
   uint16_t svcNum;
   uint8_t i;

   msgHdr.src_module = SNS_MODULE_DSPS_PLAYBACK;
   msgHdr.msg_type = SNS_SMR_MSG_TYPE_REQ;
   msgHdr.priority = SNS_SMR_MSG_PRI_LOW;
   msgHdr.txn_id = 0;
   msgHdr.ext_clnt_id = 0;

   for (i=0; i < pb_algo_count; i++)
   {
      svcNum = pb_algo_svc[i].svc_id;
      msgHdr.svc_num = svcNum;

      switch (svcNum)
      {
      case SNS_SAM_AMD_SVC_ID_V01:
         msgHdr.msg_id = SNS_SAM_AMD_ENABLE_REQ_V01;
         msgHdr.body_len = sizeof(sns_sam_amd_enable_req_msg_v01);
         msgPtr = (uint8_t *)sns_smr_msg_alloc(SNS_DBG_NUM_MOD_IDS, msgHdr.body_len);
         if (msgPtr != NULL)
         {
            ((sns_sam_amd_enable_req_msg_v01 *)msgPtr)->report_period =
            (uint32_t)pb_algo_svc[i].algo_config[0];
            ((sns_sam_amd_enable_req_msg_v01 *)msgPtr)->config_valid = 0;
         }
         break;

      case SNS_SAM_VMD_SVC_ID_V01:
         msgHdr.msg_id = SNS_SAM_VMD_ENABLE_REQ_V01;
         msgHdr.body_len = sizeof(sns_sam_qmd_enable_req_msg_v01);
         msgPtr = (uint8_t *)sns_smr_msg_alloc(SNS_DBG_NUM_MOD_IDS, msgHdr.body_len);
         if (msgPtr != NULL)
         {
            ((sns_sam_qmd_enable_req_msg_v01 *)msgPtr)->report_period =
            (uint32_t)pb_algo_svc[i].algo_config[0];
         }
         break;

      case SNS_SAM_RMD_SVC_ID_V01:
         msgHdr.msg_id = SNS_SAM_RMD_ENABLE_REQ_V01;
         msgHdr.body_len = sizeof(sns_sam_qmd_enable_req_msg_v01);
         msgPtr = (uint8_t *)sns_smr_msg_alloc(SNS_DBG_NUM_MOD_IDS, msgHdr.body_len);
         if (msgPtr != NULL)
         {
            ((sns_sam_qmd_enable_req_msg_v01 *)msgPtr)->report_period =
            (uint32_t)pb_algo_svc[i].algo_config[0];
         }
         break;

#ifdef ENABLE_APPS_PLAYBACK
      case SNS_SAM_FNS_SVC_ID_V01:
         msgHdr.msg_id = SNS_SAM_FNS_ENABLE_REQ_V01;
         msgHdr.body_len = sizeof(sns_sam_fns_enable_req_msg_v01);
         msgPtr = (uint8_t *)sns_smr_msg_alloc(SNS_DBG_NUM_MOD_IDS, msgHdr.body_len);
         if (msgPtr != NULL)
         {
            sns_sam_fns_enable_req_msg_v01 *req =
            (sns_sam_fns_enable_req_msg_v01 *)msgPtr;
            req->sample_rate_valid = 0;
            req->facing_angle_threshold_valid = 0;
            req->basic_sleep_valid = 0;
            req->basic_shake_threshold_valid = 0;
            req->timeout_valid = 0; 
         }
         break;

      case SNS_SAM_BTE_SVC_ID_V01:
         msgHdr.msg_id = SNS_SAM_BTE_ENABLE_REQ_V01;
         msgHdr.body_len = sizeof(sns_sam_bte_enable_req_msg_v01);
         msgPtr = (uint8_t *)sns_smr_msg_alloc(SNS_DBG_NUM_MOD_IDS, msgHdr.body_len);
         if (msgPtr != NULL)
         {
            sns_sam_bte_enable_req_msg_v01 *req = 
            (sns_sam_bte_enable_req_msg_v01 *)msgPtr;
            req->sample_rate_valid = 0;
            req->facing_angle_threshold_valid = 0;
            req->horiz_angle_threshold_valid = 0;
            req->vert_angle_threshold_valid = 0;
            req->prox_enabled_valid = 0;
         }
         break;

      case SNS_SAM_QUATERNION_SVC_ID_V01:
         msgHdr.msg_id = SNS_SAM_QUAT_ENABLE_REQ_V01;
         msgHdr.body_len = sizeof(sns_sam_quat_enable_req_msg_v01);
         msgPtr = (uint8_t *)sns_smr_msg_alloc(SNS_DBG_NUM_MOD_IDS, msgHdr.body_len);
         if (msgPtr != NULL)
         {
            sns_sam_quat_enable_req_msg_v01 *req = 
            (sns_sam_quat_enable_req_msg_v01 *)msgPtr;
            req->report_period = (uint32_t)pb_algo_svc[i].algo_config[0];

            // edit kaushiks
            req->sample_rate_valid = (uint32_t)pb_algo_svc[i].algo_config[1];
            req->sample_rate = (uint32_t)pb_algo_svc[i].algo_config[2];

            //req->sample_rate_valid = 0;

         }
         break;

      case SNS_SAM_GRAVITY_VECTOR_SVC_ID_V01:
         msgHdr.msg_id = SNS_SAM_GRAVITY_ENABLE_REQ_V01;
         msgHdr.body_len = sizeof(sns_sam_gravity_enable_req_msg_v01);
         msgPtr = (uint8_t *)sns_smr_msg_alloc(SNS_DBG_NUM_MOD_IDS, msgHdr.body_len);
         if (msgPtr != NULL)
         {
            sns_sam_gravity_enable_req_msg_v01 *req = 
            (sns_sam_gravity_enable_req_msg_v01 *)msgPtr;
            req->report_period = (uint32_t)pb_algo_svc[i].algo_config[0];
            req->sample_rate_valid = (uint32_t)pb_algo_svc[i].algo_config[1];
            req->sample_rate = (uint32_t)pb_algo_svc[i].algo_config[2];
         }
         break;

      case SNS_SAM_FILTERED_MAG_SVC_ID_V01:
         msgHdr.msg_id = SNS_SAM_FILTERED_MAG_ENABLE_REQ_V01;
         msgHdr.body_len = sizeof(sns_sam_filtered_mag_enable_req_msg_v01);
         msgPtr = (uint8_t *)sns_smr_msg_alloc(SNS_DBG_NUM_MOD_IDS, msgHdr.body_len);
         if (msgPtr != NULL)
         {
            sns_sam_filtered_mag_enable_req_msg_v01 *req = 
            (sns_sam_filtered_mag_enable_req_msg_v01 *)msgPtr;
            req->report_period = (uint32_t)pb_algo_svc[i].algo_config[0];
            req->sample_rate_valid = (uint32_t)pb_algo_svc[i].algo_config[1];
            req->sample_rate = (uint32_t)pb_algo_svc[i].algo_config[2];
         }
         break;

      case SNS_SAM_ROTATION_VECTOR_SVC_ID_V01:
         msgHdr.msg_id = SNS_SAM_ROTATION_VECTOR_ENABLE_REQ_V01;
         msgHdr.body_len = sizeof(sns_sam_rotation_vector_enable_req_msg_v01);
         msgPtr = (uint8_t *)sns_smr_msg_alloc(SNS_DBG_NUM_MOD_IDS, msgHdr.body_len);
         if (msgPtr != NULL)
         {
            sns_sam_rotation_vector_enable_req_msg_v01 *req = 
            (sns_sam_rotation_vector_enable_req_msg_v01 *)msgPtr;
            req->report_period = (uint32_t)pb_algo_svc[i].algo_config[0];
            req->sample_rate_valid = (uint32_t)pb_algo_svc[i].algo_config[1];
            req->sample_rate = (uint32_t)pb_algo_svc[i].algo_config[2];
         }
         break;

      case SNS_SAM_ORIENTATION_SVC_ID_V01:
         msgHdr.msg_id = SNS_SAM_ORIENTATION_ENABLE_REQ_V01;
         msgHdr.body_len = sizeof(sns_sam_orientation_enable_req_msg_v01);
         msgPtr = (uint8_t *)sns_smr_msg_alloc(SNS_DBG_NUM_MOD_IDS,msgHdr.body_len);
         if (msgPtr != NULL)
         {
            sns_sam_orientation_enable_req_msg_v01 *req = 
            (sns_sam_orientation_enable_req_msg_v01 *)msgPtr;
            req->report_period = (uint32_t)pb_algo_svc[i].algo_config[0];
            req->sample_rate_valid = (uint32_t)pb_algo_svc[i].algo_config[1];
            req->sample_rate = (uint32_t)pb_algo_svc[i].algo_config[2];
         }
         break;
#ifdef FEATURE_GESTURES_REL_1
      case SNS_SAM_BASIC_GESTURES_SVC_ID_V01:
         msgHdr.msg_id = SNS_SAM_BASIC_GESTURES_ENABLE_REQ_V01;
         msgHdr.body_len = sizeof(sns_sam_basic_gestures_enable_req_msg_v01);
         msgPtr = (uint8_t *)sns_smr_msg_alloc(SNS_DBG_NUM_MOD_IDS, msgHdr.body_len);
         if (msgPtr != NULL)
         {
            sns_sam_basic_gestures_enable_req_msg_v01 *req =
            (sns_sam_basic_gestures_enable_req_msg_v01 *)msgPtr;
         }
         break;
      case SNS_SAM_FACING_SVC_ID_V01:
         msgHdr.msg_id = SNS_SAM_FACING_ENABLE_REQ_V01;
         msgHdr.body_len = sizeof(sns_sam_facing_enable_req_msg_v01);
         msgPtr = (uint8_t *)sns_smr_msg_alloc(SNS_DBG_NUM_MOD_IDS, msgHdr.body_len);
         if (msgPtr != NULL)
         {
            sns_sam_facing_enable_req_msg_v01 *req =
            (sns_sam_facing_enable_req_msg_v01 *)msgPtr;
         }
         break;
      case SNS_SAM_INTEG_ANGLE_SVC_ID_V01:
         msgHdr.msg_id = SNS_SAM_INTEG_ANGLE_ENABLE_REQ_V01;
         msgHdr.body_len = sizeof(sns_sam_integ_angle_enable_req_msg_v01);
         msgPtr = (uint8_t *)sns_smr_msg_alloc(SNS_DBG_NUM_MOD_IDS, msgHdr.body_len);
         if (msgPtr != NULL)
         {
            sns_sam_integ_angle_enable_req_msg_v01 *req =
            (sns_sam_integ_angle_enable_req_msg_v01 *)msgPtr;
         }
         break;
      case SNS_SAM_GYRO_TAP_SVC_ID_V01:
         msgHdr.msg_id = SNS_SAM_GYRO_TAP_ENABLE_REQ_V01;
         msgHdr.body_len = sizeof(sns_sam_gyro_tap_enable_req_msg_v01);
         msgPtr = (uint8_t *)sns_smr_msg_alloc(SNS_DBG_NUM_MOD_IDS, msgHdr.body_len);
         if (msgPtr != NULL)
         {
            sns_sam_gyro_tap_enable_req_msg_v01 *req =
            (sns_sam_gyro_tap_enable_req_msg_v01 *)msgPtr;
         }
         break;
#endif /* FEATURE_GESTURES_REL_1 */
#endif /* ENABLE_APPS_PLAYBACK */

      case PB_GYRO_CAL_SVC_ID_V01:
         sns_playback_send_smgr_start_req_gyro();
         break;

         /** Add handling of additional algo service here... **/

      default:
         printf("Error: received unsupported algo service id %d", svcNum);
         return;
      }

      if (svcNum==PB_GYRO_CAL_SVC_ID_V01)
      {
         // Do Nothing
      }
      else
      {
         sns_smr_set_hdr(&msgHdr, msgPtr);
         if (sns_smr_send(msgPtr)!= SNS_SUCCESS)
         {
            sns_smr_msg_free(msgPtr);
         }
         printf("Sent algo enable request message id %d from module %d for algo service %d\n",
                msgHdr.msg_id, msgHdr.src_module, msgHdr.svc_num);
      }

      printf("\nPlayback Pause before sending data to allow algos to initialize \n");

#ifdef SNS_PLAYBACK_SKIP_SMGR
      /* Delay for some time to ensure that the algo enable request is processed */
      {
         uint8_t err;
         uint32_t timeout = sns_em_convert_usec_to_localtick(2000000);
         OS_FLAG_GRP *sig_ptr = sns_os_sigs_create((OS_FLAGS)0x0, &err);
         sns_os_sigs_pend(sig_ptr, 0x1, OS_FLAG_WAIT_SET_ANY, timeout, &err);

         playback_send_data_to_algo();
      }
#endif
   }
}

/*=========================================================================
  FUNCTION:  sns_playback_disable_algo
=========================================================================*/
/*!
    @brief
    Sends message disabling specified algo service

    @return
    None
*/
/*=======================================================================*/
void sns_playback_disable_algo()
{
   uint8_t *msgPtr;
   sns_smr_header_s msgHdr;
   uint16_t svcNum;
   uint8_t i;

   msgHdr.src_module = SNS_MODULE_DSPS_PLAYBACK;

   msgHdr.msg_type = SNS_SMR_MSG_TYPE_REQ;
   msgHdr.priority = SNS_SMR_MSG_PRI_LOW;
   msgHdr.txn_id = 1;
   msgHdr.ext_clnt_id = 0;

   for (i=0; i < pb_algo_count; i++)
   {
      svcNum = pb_algo_svc[i].svc_id;
      msgHdr.svc_num = svcNum;

      switch (svcNum)
      {
      case SNS_SAM_AMD_SVC_ID_V01:
      case SNS_SAM_VMD_SVC_ID_V01:
      case SNS_SAM_RMD_SVC_ID_V01:
         msgHdr.msg_id = SNS_SAM_AMD_DISABLE_REQ_V01; /* same for all 3 services */
         msgHdr.body_len = sizeof(sns_sam_qmd_disable_req_msg_v01);
         msgPtr = (uint8_t *)sns_smr_msg_alloc(SNS_DBG_NUM_MOD_IDS, msgHdr.body_len);
         if (msgPtr != NULL)
         {
            /* TODO: get algo instand id from SAM response instead */
            ((sns_sam_qmd_disable_req_msg_v01 *)msgPtr)->instance_id = 0;
         }
         break;

#ifdef ENABLE_APPS_PLAYBACK
      case SNS_SAM_FNS_SVC_ID_V01:
         msgHdr.msg_id = SNS_SAM_FNS_DISABLE_REQ_V01;
         msgHdr.body_len = sizeof(sns_sam_fns_disable_req_msg_v01);
         msgPtr = (uint8_t *)sns_smr_msg_alloc(SNS_DBG_NUM_MOD_IDS, msgHdr.body_len);
         if (msgPtr != NULL)
         {
            /* TODO: get algo instand id from SAM response instead */
            ((sns_sam_fns_disable_req_msg_v01 *)msgPtr)->instance_id = 0;
         }
         break;

      case SNS_SAM_BTE_SVC_ID_V01:
         msgHdr.msg_id = SNS_SAM_BTE_DISABLE_REQ_V01;
         msgHdr.body_len = sizeof(sns_sam_bte_disable_req_msg_v01);
         msgPtr = (uint8_t *)sns_smr_msg_alloc(SNS_DBG_NUM_MOD_IDS, msgHdr.body_len);
         if (msgPtr != NULL)
         {
            /* TODO: get algo instand id from SAM response instead */
            ((sns_sam_bte_disable_req_msg_v01 *)msgPtr)->instance_id = 0;
         }
         break;

      case SNS_SAM_QUATERNION_SVC_ID_V01:
         msgHdr.msg_id = SNS_SAM_QUAT_DISABLE_REQ_V01;
         msgHdr.body_len = sizeof(sns_sam_quat_disable_req_msg_v01);
         msgPtr = (uint8_t *)sns_smr_msg_alloc(SNS_DBG_NUM_MOD_IDS, msgHdr.body_len);
         if (msgPtr != NULL)
         {
            /* TODO: get algo instand id from SAM response instead */
            ((sns_sam_quat_disable_req_msg_v01 *)msgPtr)->instance_id = 0;
         }
         break;

      case SNS_SAM_GRAVITY_VECTOR_SVC_ID_V01:
         msgHdr.msg_id = SNS_SAM_GRAVITY_DISABLE_REQ_V01;
         msgHdr.body_len = sizeof(sns_sam_gravity_disable_req_msg_v01);
         msgPtr = (uint8_t *)sns_smr_msg_alloc(SNS_DBG_NUM_MOD_IDS, msgHdr.body_len);
         if (msgPtr != NULL)
         {
            /* TODO: get algo instand id from SAM response instead */
            ((sns_sam_gravity_disable_req_msg_v01 *)msgPtr)->instance_id = 0;
         }
         break;

      case SNS_SAM_FILTERED_MAG_SVC_ID_V01:
         msgHdr.msg_id = SNS_SAM_FILTERED_MAG_DISABLE_REQ_V01;
         msgHdr.body_len = sizeof(sns_sam_filtered_mag_disable_req_msg_v01);
         msgPtr = (uint8_t *)sns_smr_msg_alloc(SNS_DBG_NUM_MOD_IDS, msgHdr.body_len);
         if (msgPtr != NULL)
         {
            /* TODO: get algo instand id from SAM response instead */
            ((sns_sam_filtered_mag_disable_req_msg_v01 *)msgPtr)->instance_id = 0;
         }
         break;

      case SNS_SAM_ROTATION_VECTOR_SVC_ID_V01:
         msgHdr.msg_id = SNS_SAM_ROTATION_VECTOR_DISABLE_REQ_V01;
         msgHdr.body_len = sizeof(sns_sam_rotation_vector_disable_req_msg_v01);
         msgPtr = (uint8_t *)sns_smr_msg_alloc(SNS_DBG_NUM_MOD_IDS, msgHdr.body_len);
         if (msgPtr != NULL)
         {
            /* TODO: get algo instand id from SAM response instead */
            ((sns_sam_rotation_vector_disable_req_msg_v01 *)msgPtr)->instance_id = 0;
         }
         break;

      case SNS_SAM_ORIENTATION_SVC_ID_V01:
         msgHdr.msg_id = SNS_SAM_ORIENTATION_DISABLE_REQ_V01;
         msgHdr.body_len = sizeof(sns_sam_orientation_disable_req_msg_v01);
         msgPtr = (uint8_t *)sns_smr_msg_alloc(SNS_DBG_NUM_MOD_IDS,msgHdr.body_len);
         if (msgPtr != NULL)
         {
            /* TODO: get algo instand id from SAM response instead */
            ((sns_sam_orientation_disable_req_msg_v01 *)msgPtr)->instance_id = 0;
         }
         break;
#ifdef FEATURE_GESTURES_REL_1
      case SNS_SAM_BASIC_GESTURES_SVC_ID_V01:
         msgHdr.msg_id = SNS_SAM_BASIC_GESTURES_DISABLE_REQ_V01;
         msgHdr.body_len = sizeof(sns_sam_basic_gestures_disable_req_msg_v01);
         msgPtr = (uint8_t *)sns_smr_msg_alloc(SNS_DBG_NUM_MOD_IDS,msgHdr.body_len);
         if (msgPtr != NULL)
         {
            /* TODO: get algo instand id from SAM response instead */
            ((sns_sam_basic_gestures_disable_req_msg_v01 *)msgPtr)->instance_id = 0;
         }
         break;
      case SNS_SAM_FACING_SVC_ID_V01:
         msgHdr.msg_id = SNS_SAM_FACING_DISABLE_REQ_V01;
         msgHdr.body_len = sizeof(sns_sam_facing_disable_req_msg_v01);
         msgPtr = (uint8_t *)sns_smr_msg_alloc(SNS_DBG_NUM_MOD_IDS,msgHdr.body_len);
         if (msgPtr != NULL)
         {
            /* TODO: get algo instand id from SAM response instead */
            ((sns_sam_facing_disable_req_msg_v01 *)msgPtr)->instance_id = 0;
         }
         break;
      case SNS_SAM_INTEG_ANGLE_SVC_ID_V01:
         msgHdr.msg_id = SNS_SAM_INTEG_ANGLE_DISABLE_REQ_V01;
         msgHdr.body_len = sizeof(sns_sam_integ_angle_disable_req_msg_v01);
         msgPtr = (uint8_t *)sns_smr_msg_alloc(SNS_DBG_NUM_MOD_IDS,msgHdr.body_len);
         if (msgPtr != NULL)
         {
            /* TODO: get algo instand id from SAM response instead */
            ((sns_sam_integ_angle_disable_req_msg_v01 *)msgPtr)->instance_id = 0;
         }
         break;
      case SNS_SAM_GYRO_TAP_SVC_ID_V01:
         msgHdr.msg_id = SNS_SAM_GYRO_TAP_DISABLE_REQ_V01;
         msgHdr.body_len = sizeof(sns_sam_gyro_tap_disable_req_msg_v01);
         msgPtr = (uint8_t *)sns_smr_msg_alloc(SNS_DBG_NUM_MOD_IDS,msgHdr.body_len);
         if (msgPtr != NULL)
         {
            /* TODO: get algo instand id from SAM response instead */
            ((sns_sam_gyro_tap_disable_req_msg_v01 *)msgPtr)->instance_id = 0;
         }
         break;
#endif /* FEATURE_GESTURES_REL_1 */
#endif /* ENABLE_APPS_PLAYBACK */

         /** Add handling of additional algo services here... **/

      default:
         printf("Error: received unsupported algo service id %d", svcNum);
         return;
      }

      sns_smr_set_hdr(&msgHdr, msgPtr);
      if (sns_smr_send(msgPtr) != SNS_SUCCESS)
      {
         sns_smr_msg_free(msgPtr);
      }

      printf("Sent disable request message id %d from module %d for algo service %d\n", 
             msgHdr.msg_id, msgHdr.src_module, msgHdr.svc_num);
   }

   pb_algo_count = 0;
}

/*=========================================================================
  FUNCTION:  sns_playback_accel_data
=========================================================================*/
/*!
    @brief
    Playback accel and fill input data structure for one sampling period

    @return
    sns_ddf_status_e
*/
/*=======================================================================*/
sns_ddf_status_e sns_playback_accel_data(sns_ddf_sensor_data_s *data_ptr)
{
   return(playback_get_data(&fp_accel_input, data_ptr));
}

/*=========================================================================
  FUNCTION:  sns_playback_gyro_data
=========================================================================*/
/*!
    @brief
    Playback gyro and fill input data structure for one sampling period

    @return
    sns_ddf_status_e
*/
/*=======================================================================*/
sns_ddf_status_e sns_playback_gyro_data(sns_ddf_sensor_data_s *data_ptr)
{
   return(playback_get_data(&fp_gyro_input, data_ptr));
}

/*=========================================================================
  FUNCTION:  sns_playback_mag_data
=========================================================================*/
/*!
    @brief
    Playback mag and fill input data structure for one sampling period

    @return
    sns_ddf_status_e
*/
/*=======================================================================*/
sns_ddf_status_e sns_playback_mag_data(sns_ddf_sensor_data_s *data_ptr)
{
   return(playback_get_data(&fp_mag_input, data_ptr));
}
/*=========================================================================
  FUNCTION:  sns_playback_sensor_data
=========================================================================*/
/*!
    @brief
    Playback sensor data input ( accel + gyro )  and fill input data structure for one sampling period

    @return
    sns_ddf_status_e
*/
/*=======================================================================*/
sns_ddf_status_e sns_playback_sensor_data(sns_ddf_sensor_data_s *data_ptr)
{
   return(playback_get_data(&fp_sensor_input, data_ptr));
}

/*=========================================================================
  FUNCTION:  sns_playback_log_pkt
=========================================================================*/
/*!
    @brief
    Log packet utility for playback

    @return
    None
*/
/*=======================================================================*/
void sns_playback_log_pkt(sns_debug_log_ind_msg_v01 *pkt_ptr)
{
   /* filter log packets based on log mask */
   if ( pb_log_mask & ((uint64_t)1 << pkt_ptr->log_pkt_type) )
      return;

   switch (pkt_ptr->log_pkt_type)
   {
   case SNS_LOG_QMD_CONFIG:
      if (fp_log_qmd_config != NULL)
      {
         log_hdr_type *hdr_ptr = (log_hdr_type *)(pkt_ptr->log_pkt_contents);
         memset(hdr_ptr, 0, sizeof(log_hdr_type));
         hdr_ptr->len = pkt_ptr->logpkt_size;
         hdr_ptr->code = LOG_SNS_QMD_CONFIG_C;
         hdr_ptr->ts[0] = 0;
         hdr_ptr->ts[1] = sns_em_get_timestamp();
         fwrite(pkt_ptr->log_pkt_contents, 1, pkt_ptr->logpkt_size, fp_log_qmd_config);
      }
      break;

   case SNS_LOG_QMD_RESULT:
      if (fp_log_qmd_result != NULL)
      {
         log_hdr_type *hdr_ptr = (log_hdr_type *)(pkt_ptr->log_pkt_contents);
         memset(hdr_ptr, 0, sizeof(log_hdr_type));
         hdr_ptr->len = pkt_ptr->logpkt_size;
         hdr_ptr->code = LOG_SNS_QMD_RESULT_C;
         hdr_ptr->ts[0] = 0;
         hdr_ptr->ts[1] = sns_em_get_timestamp();
         fwrite(pkt_ptr->log_pkt_contents, 1, pkt_ptr->logpkt_size, fp_log_qmd_result);
      }
      break;

   case SNS_LOG_QMD_REPORT:
      if (fp_log_qmd_report != NULL)
      {
         log_hdr_type *hdr_ptr = (log_hdr_type *)(pkt_ptr->log_pkt_contents);
         memset(hdr_ptr, 0, sizeof(log_hdr_type));
         hdr_ptr->len = pkt_ptr->logpkt_size;
         hdr_ptr->code = LOG_SNS_QMD_REPORT_C;
         hdr_ptr->ts[0] = 0;
         hdr_ptr->ts[1] = sns_em_get_timestamp();
         fwrite(pkt_ptr->log_pkt_contents, 1, pkt_ptr->logpkt_size, fp_log_qmd_report);
      }
      break;

#ifdef ENABLE_APPS_PLAYBACK
   case SNS_LOG_FNS_CONFIG:
      if (fp_log_fns_config != NULL)
      {
         log_hdr_type *hdr_ptr = (log_hdr_type *)(pkt_ptr->log_pkt_contents);
         memset(hdr_ptr, 0, sizeof(log_hdr_type));
         hdr_ptr->len = pkt_ptr->logpkt_size;
         hdr_ptr->code = LOG_SNS_FNS_CONFIG_C;
         hdr_ptr->ts[0] = 0;
         hdr_ptr->ts[1] = sns_em_get_timestamp();
         fwrite(pkt_ptr->log_pkt_contents, 1, pkt_ptr->logpkt_size, fp_log_fns_config);
      }
      break;

   case SNS_LOG_FNS_RESULT:
      if (fp_log_fns_result != NULL)
      {
         log_hdr_type *hdr_ptr = (log_hdr_type *)(pkt_ptr->log_pkt_contents);
         memset(hdr_ptr, 0, sizeof(log_hdr_type));
         hdr_ptr->len = pkt_ptr->logpkt_size;
         hdr_ptr->code = LOG_SNS_FNS_RESULT_C;
         hdr_ptr->ts[0] = 0;
         hdr_ptr->ts[1] = sns_em_get_timestamp();
         fwrite(pkt_ptr->log_pkt_contents, 1, pkt_ptr->logpkt_size, fp_log_fns_result);
      }
      break;

   case SNS_LOG_FNS_REPORT:
      if (fp_log_fns_report != NULL)
      {
         log_hdr_type *hdr_ptr = (log_hdr_type *)(pkt_ptr->log_pkt_contents);
         memset(hdr_ptr, 0, sizeof(log_hdr_type));
         hdr_ptr->len = pkt_ptr->logpkt_size;
         hdr_ptr->code = LOG_SNS_FNS_REPORT_C;
         hdr_ptr->ts[0] = 0;
         hdr_ptr->ts[1] = sns_em_get_timestamp();
         fwrite(pkt_ptr->log_pkt_contents, 1, pkt_ptr->logpkt_size, fp_log_fns_report);
      }
      break;

   case SNS_LOG_BTE_CONFIG:
      if (fp_log_bte_config != NULL)
      {
         log_hdr_type *hdr_ptr = (log_hdr_type *)(pkt_ptr->log_pkt_contents);
         memset(hdr_ptr, 0, sizeof(log_hdr_type));
         hdr_ptr->len = pkt_ptr->logpkt_size;
         hdr_ptr->code = LOG_SNS_BTE_CONFIG_C;
         hdr_ptr->ts[0] = 0;
         hdr_ptr->ts[1] = sns_em_get_timestamp();
         fwrite(pkt_ptr->log_pkt_contents, 1, pkt_ptr->logpkt_size, fp_log_bte_config);
      }
      break;

   case SNS_LOG_BTE_RESULT:
      if (fp_log_bte_result != NULL)
      {
         log_hdr_type *hdr_ptr = (log_hdr_type *)(pkt_ptr->log_pkt_contents);
         memset(hdr_ptr, 0, sizeof(log_hdr_type));
         hdr_ptr->len = pkt_ptr->logpkt_size;
         hdr_ptr->code = LOG_SNS_BTE_RESULT_C;
         hdr_ptr->ts[0] = 0;
         hdr_ptr->ts[1] = sns_em_get_timestamp();
         fwrite(pkt_ptr->log_pkt_contents, 1, pkt_ptr->logpkt_size, fp_log_bte_result);
      }
      break;

   case SNS_LOG_BTE_REPORT:
      if (fp_log_bte_report != NULL)
      {
         log_hdr_type *hdr_ptr = (log_hdr_type *)(pkt_ptr->log_pkt_contents);
         memset(hdr_ptr, 0, sizeof(log_hdr_type));
         hdr_ptr->len = pkt_ptr->logpkt_size;
         hdr_ptr->code = LOG_SNS_BTE_REPORT_C;
         hdr_ptr->ts[0] = 0;
         hdr_ptr->ts[1] = sns_em_get_timestamp();
         fwrite(pkt_ptr->log_pkt_contents, 1, pkt_ptr->logpkt_size, fp_log_bte_report);
      }
      break;

   case SNS_LOG_QUAT_CONFIG:
      if (fp_log_quaternion_config != NULL)
      {
         log_hdr_type *hdr_ptr = (log_hdr_type *)(pkt_ptr->log_pkt_contents);
         memset(hdr_ptr, 0, sizeof(log_hdr_type));
         hdr_ptr->len = pkt_ptr->logpkt_size;
         hdr_ptr->code = LOG_SNS_QUAT_CONFIG_C;
         hdr_ptr->ts[0] = 0;
         hdr_ptr->ts[1] = sns_em_get_timestamp();
         fwrite(pkt_ptr->log_pkt_contents, 1, pkt_ptr->logpkt_size, fp_log_quaternion_config);
      }
      break;

   case SNS_LOG_QUAT_RESULT:
      if (fp_log_quaternion_result != NULL)
      {
         log_hdr_type *hdr_ptr = (log_hdr_type *)(pkt_ptr->log_pkt_contents);
         memset(hdr_ptr, 0, sizeof(log_hdr_type));
         hdr_ptr->len = pkt_ptr->logpkt_size;
         hdr_ptr->code = LOG_SNS_QUAT_RESULT_C;
         hdr_ptr->ts[0] = 0;
         hdr_ptr->ts[1] = sns_em_get_timestamp();
         fwrite(pkt_ptr->log_pkt_contents, 1, pkt_ptr->logpkt_size, fp_log_quaternion_result);
      }
      break;

   case SNS_LOG_QUAT_REPORT:
      if (fp_log_quaternion_report != NULL)
      {
         log_hdr_type *hdr_ptr = (log_hdr_type *)(pkt_ptr->log_pkt_contents);
         memset(hdr_ptr, 0, sizeof(log_hdr_type));
         hdr_ptr->len = pkt_ptr->logpkt_size;
         hdr_ptr->code = LOG_SNS_QUAT_REPORT_C;
         hdr_ptr->ts[0] = 0;
         hdr_ptr->ts[1] = sns_em_get_timestamp();
         fwrite(pkt_ptr->log_pkt_contents, 1, pkt_ptr->logpkt_size, fp_log_quaternion_report);
      }
      break;

   case SNS_LOG_GRAVITY_CONFIG:
      if (fp_log_gravity_config != NULL)
      {
         log_hdr_type *hdr_ptr = (log_hdr_type *)(pkt_ptr->log_pkt_contents);
         memset(hdr_ptr, 0, sizeof(log_hdr_type));
         hdr_ptr->len = pkt_ptr->logpkt_size;
         hdr_ptr->code = LOG_SNS_GRAVITY_CONFIG_C;
         hdr_ptr->ts[0] = 0;
         hdr_ptr->ts[1] = sns_em_get_timestamp();
         fwrite(pkt_ptr->log_pkt_contents, 1, pkt_ptr->logpkt_size, fp_log_gravity_config);
      }
      break;

   case SNS_LOG_GRAVITY_RESULT:
      if (fp_log_gravity_result != NULL)
      {
         log_hdr_type *hdr_ptr = (log_hdr_type *)(pkt_ptr->log_pkt_contents);
         memset(hdr_ptr, 0, sizeof(log_hdr_type));
         hdr_ptr->len = pkt_ptr->logpkt_size;
         hdr_ptr->code = LOG_SNS_GRAVITY_RESULT_C;
         hdr_ptr->ts[0] = 0;
         hdr_ptr->ts[1] = sns_em_get_timestamp();
         fwrite(pkt_ptr->log_pkt_contents, 1, pkt_ptr->logpkt_size, fp_log_gravity_result);
      }
      break;

   case SNS_LOG_GRAVITY_REPORT:
      if (fp_log_gravity_report != NULL)
      {
         log_hdr_type *hdr_ptr = (log_hdr_type *)(pkt_ptr->log_pkt_contents);
         memset(hdr_ptr, 0, sizeof(log_hdr_type));
         hdr_ptr->len = pkt_ptr->logpkt_size;
         hdr_ptr->code = LOG_SNS_GRAVITY_REPORT_C;
         hdr_ptr->ts[0] = 0;
         hdr_ptr->ts[1] = sns_em_get_timestamp();
         fwrite(pkt_ptr->log_pkt_contents, 1, pkt_ptr->logpkt_size, fp_log_gravity_report);
      }
      break;

   case SNS_LOG_FMV_REPORT:
      if (fp_log_fmv_report != NULL)
      {
         log_hdr_type *hdr_ptr = (log_hdr_type *)(pkt_ptr->log_pkt_contents);
         memset(hdr_ptr, 0, sizeof(log_hdr_type));
         hdr_ptr->len = pkt_ptr->logpkt_size;
         hdr_ptr->code = LOG_SNS_FMV_REPORT_C;
         hdr_ptr->ts[0] = 0;
         hdr_ptr->ts[1] = sns_em_get_timestamp();
         fwrite(pkt_ptr->log_pkt_contents, 1, pkt_ptr->logpkt_size, fp_log_fmv_report);
      }
      break;

   case SNS_LOG_FMV_CONFIG:
      if (fp_log_fmv_config != NULL)
      {
         log_hdr_type *hdr_ptr = (log_hdr_type *)(pkt_ptr->log_pkt_contents);
         memset(hdr_ptr, 0, sizeof(log_hdr_type));
         hdr_ptr->len = pkt_ptr->logpkt_size;
         hdr_ptr->code = LOG_SNS_FMV_CONFIG_C;
         hdr_ptr->ts[0] = 0;
         hdr_ptr->ts[1] = sns_em_get_timestamp();
         fwrite(pkt_ptr->log_pkt_contents, 1, pkt_ptr->logpkt_size, fp_log_fmv_config);
      }
      break;

   case SNS_LOG_FMV_QUAT_UPDATE:
      if (fp_log_fmv_quat_update != NULL)
      {
         log_hdr_type *hdr_ptr = (log_hdr_type *)(pkt_ptr->log_pkt_contents);
         memset(hdr_ptr, 0, sizeof(log_hdr_type));
         hdr_ptr->len = pkt_ptr->logpkt_size;
         hdr_ptr->code = LOG_SNS_FMV_QUAT_UPDATE_C;
         hdr_ptr->ts[0] = 0;
         hdr_ptr->ts[1] = sns_em_get_timestamp();
         fwrite(pkt_ptr->log_pkt_contents, 1, pkt_ptr->logpkt_size, fp_log_fmv_quat_update);
      }
      break;

   case SNS_LOG_FMV_MAG_UPDATE:
      if (fp_log_fmv_mag_update != NULL)
      {
         log_hdr_type *hdr_ptr = (log_hdr_type *)(pkt_ptr->log_pkt_contents);
         memset(hdr_ptr, 0, sizeof(log_hdr_type));
         hdr_ptr->len = pkt_ptr->logpkt_size;
         hdr_ptr->code = LOG_SNS_FMV_MAG_UPDATE_C;
         hdr_ptr->ts[0] = 0;
         hdr_ptr->ts[1] = sns_em_get_timestamp();
         fwrite(pkt_ptr->log_pkt_contents, 1, pkt_ptr->logpkt_size, fp_log_fmv_mag_update);
      }
      break;

   case SNS_LOG_FMV_GYRO_UPDATE:
      if (fp_log_fmv_gyro_update != NULL)
      {
         log_hdr_type *hdr_ptr = (log_hdr_type *)(pkt_ptr->log_pkt_contents);
         memset(hdr_ptr, 0, sizeof(log_hdr_type));
         hdr_ptr->len = pkt_ptr->logpkt_size;
         hdr_ptr->code = LOG_SNS_FMV_GYRO_UPDATE_C;
         hdr_ptr->ts[0] = 0;
         hdr_ptr->ts[1] = sns_em_get_timestamp();
         fwrite(pkt_ptr->log_pkt_contents, 1, pkt_ptr->logpkt_size, fp_log_fmv_gyro_update);
      }
      break;

   case SNS_LOG_ROTATION_VECTOR_CONFIG:
      if (fp_log_rotation_vector_config != NULL)
      {
         log_hdr_type *hdr_ptr = (log_hdr_type *)(pkt_ptr->log_pkt_contents);
         memset(hdr_ptr, 0, sizeof(log_hdr_type));
         hdr_ptr->len = pkt_ptr->logpkt_size;
         hdr_ptr->code = LOG_SNS_ROTATION_VECTOR_CONFIG_C;
         hdr_ptr->ts[0] = 0;
         hdr_ptr->ts[1] = sns_em_get_timestamp();
         fwrite(pkt_ptr->log_pkt_contents, 1, pkt_ptr->logpkt_size, fp_log_rotation_vector_config);
      }
      break;

   case SNS_LOG_ROTATION_VECTOR_RESULT:
      if (fp_log_rotation_vector_result != NULL)
      {
         log_hdr_type *hdr_ptr = (log_hdr_type *)(pkt_ptr->log_pkt_contents);
         memset(hdr_ptr, 0, sizeof(log_hdr_type));
         hdr_ptr->len = pkt_ptr->logpkt_size;
         hdr_ptr->code = LOG_SNS_ROTATION_VECTOR_RESULT_C;
         hdr_ptr->ts[0] = 0;
         hdr_ptr->ts[1] = sns_em_get_timestamp();
         fwrite(pkt_ptr->log_pkt_contents, 1, pkt_ptr->logpkt_size, fp_log_rotation_vector_result);
      }
      break;

   case SNS_LOG_ROTATION_VECTOR_REPORT:
      if (fp_log_rotation_vector_report != NULL)
      {
         log_hdr_type *hdr_ptr = (log_hdr_type *)(pkt_ptr->log_pkt_contents);
         memset(hdr_ptr, 0, sizeof(log_hdr_type));
         hdr_ptr->len = pkt_ptr->logpkt_size;
         hdr_ptr->code = LOG_SNS_ROTATION_VECTOR_REPORT_C;
         hdr_ptr->ts[0] = 0;
         hdr_ptr->ts[1] = sns_em_get_timestamp();
         fwrite(pkt_ptr->log_pkt_contents, 1, pkt_ptr->logpkt_size, fp_log_rotation_vector_report);
      }
      break;

   case SNS_LOG_MAG_CAL_CONFIG:
      if (fp_log_mag_cal_config != NULL)
      {
         log_hdr_type *hdr_ptr = (log_hdr_type *)(pkt_ptr->log_pkt_contents);
         memset(hdr_ptr, 0, sizeof(log_hdr_type));
         hdr_ptr->len = pkt_ptr->logpkt_size;
         hdr_ptr->code = LOG_SNS_MAG_CAL_CONFIG_C;
         hdr_ptr->ts[0] = 0;
         hdr_ptr->ts[1] = sns_em_get_timestamp();
         fwrite(pkt_ptr->log_pkt_contents, 1, pkt_ptr->logpkt_size, fp_log_mag_cal_config);
      }
      break;

   case SNS_LOG_MAG_CAL_RESULT:
      if (fp_log_mag_cal_result != NULL)
      {
         log_hdr_type *hdr_ptr = (log_hdr_type *)(pkt_ptr->log_pkt_contents);
         memset(hdr_ptr, 0, sizeof(log_hdr_type));
         hdr_ptr->len = pkt_ptr->logpkt_size;
         hdr_ptr->code = LOG_SNS_MAG_CAL_RESULT_C;
         hdr_ptr->ts[0] = 0;
         hdr_ptr->ts[1] = sns_em_get_timestamp();
         fwrite(pkt_ptr->log_pkt_contents, 1, pkt_ptr->logpkt_size, fp_log_mag_cal_result);
      }
      break;

   case SNS_LOG_MAG_CAL_REPORT:
      if (fp_log_mag_cal_report != NULL)
      {
         log_hdr_type *hdr_ptr = (log_hdr_type *)(pkt_ptr->log_pkt_contents);
         memset(hdr_ptr, 0, sizeof(log_hdr_type));
         hdr_ptr->len = pkt_ptr->logpkt_size;
         hdr_ptr->code = LOG_SNS_MAG_CAL_REPORT_C;
         hdr_ptr->ts[0] = 0;
         hdr_ptr->ts[1] = sns_em_get_timestamp();
         fwrite(pkt_ptr->log_pkt_contents, 1, pkt_ptr->logpkt_size, fp_log_mag_cal_report);
      }
      break;

#ifdef FEATURE_GESTURES_REL_1
   case SNS_LOG_BASIC_GESTURES_CONFIG:
      if (fp_log_basic_gestures_config != NULL)
      {
         log_hdr_type *hdr_ptr = (log_hdr_type *)(pkt_ptr->log_pkt_contents);
         memset(hdr_ptr, 0, sizeof(log_hdr_type));
         hdr_ptr->len = pkt_ptr->logpkt_size;
         hdr_ptr->code = LOG_SNS_BASIC_GESTURES_CONFIG_C;
         hdr_ptr->ts[0] = 0;
         hdr_ptr->ts[1] = sns_em_get_timestamp();
         fwrite(pkt_ptr->log_pkt_contents, 1, pkt_ptr->logpkt_size, fp_log_basic_gestures_config);
      }
      break;

   case SNS_LOG_BASIC_GESTURES_RESULT:
      if (fp_log_basic_gestures_result != NULL)
      {
         log_hdr_type *hdr_ptr = (log_hdr_type *)(pkt_ptr->log_pkt_contents);
         memset(hdr_ptr, 0, sizeof(log_hdr_type));
         hdr_ptr->len = pkt_ptr->logpkt_size;
         hdr_ptr->code = LOG_SNS_BASIC_GESTURES_RESULT_C;
         hdr_ptr->ts[0] = 0;
         hdr_ptr->ts[1] = sns_em_get_timestamp();
         fwrite(pkt_ptr->log_pkt_contents, 1, pkt_ptr->logpkt_size, fp_log_basic_gestures_result);
      }
      break;

   case SNS_LOG_BASIC_GESTURES_REPORT:
      if (fp_log_basic_gestures_report != NULL)
      {
         log_hdr_type *hdr_ptr = (log_hdr_type *)(pkt_ptr->log_pkt_contents);
         memset(hdr_ptr, 0, sizeof(log_hdr_type));
         hdr_ptr->len = pkt_ptr->logpkt_size;
         hdr_ptr->code = LOG_SNS_BASIC_GESTURES_REPORT_C;
         hdr_ptr->ts[0] = 0;
         hdr_ptr->ts[1] = sns_em_get_timestamp();
         fwrite(pkt_ptr->log_pkt_contents, 1, pkt_ptr->logpkt_size, fp_log_basic_gestures_report);
      }
      break;

   case SNS_LOG_FACING_CONFIG:
      if (fp_log_facing_config != NULL)
      {
         log_hdr_type *hdr_ptr = (log_hdr_type *)(pkt_ptr->log_pkt_contents);
         memset(hdr_ptr, 0, sizeof(log_hdr_type));
         hdr_ptr->len = pkt_ptr->logpkt_size;
         hdr_ptr->code = LOG_SNS_FACING_CONFIG_C;
         hdr_ptr->ts[0] = 0;
         hdr_ptr->ts[1] = sns_em_get_timestamp();
         fwrite(pkt_ptr->log_pkt_contents, 1, pkt_ptr->logpkt_size, fp_log_facing_config);
      }
      break;

   case SNS_LOG_FACING_RESULT:
      if (fp_log_facing_result != NULL)
      {
         log_hdr_type *hdr_ptr = (log_hdr_type *)(pkt_ptr->log_pkt_contents);
         memset(hdr_ptr, 0, sizeof(log_hdr_type));
         hdr_ptr->len = pkt_ptr->logpkt_size;
         hdr_ptr->code = LOG_SNS_FACING_RESULT_C;
         hdr_ptr->ts[0] = 0;
         hdr_ptr->ts[1] = sns_em_get_timestamp();
         fwrite(pkt_ptr->log_pkt_contents, 1, pkt_ptr->logpkt_size, fp_log_facing_result);
      }
      break;

   case SNS_LOG_FACING_REPORT:
      if (fp_log_facing_report != NULL)
      {
         log_hdr_type *hdr_ptr = (log_hdr_type *)(pkt_ptr->log_pkt_contents);
         memset(hdr_ptr, 0, sizeof(log_hdr_type));
         hdr_ptr->len = pkt_ptr->logpkt_size;
         hdr_ptr->code = LOG_SNS_FACING_REPORT_C;
         hdr_ptr->ts[0] = 0;
         hdr_ptr->ts[1] = sns_em_get_timestamp();
         fwrite(pkt_ptr->log_pkt_contents, 1, pkt_ptr->logpkt_size, fp_log_facing_report);
      }
      break;

   case SNS_LOG_INTEG_ANGLE_CONFIG:
      if (fp_log_integ_angle_config != NULL)
      {
         log_hdr_type *hdr_ptr = (log_hdr_type *)(pkt_ptr->log_pkt_contents);
         memset(hdr_ptr, 0, sizeof(log_hdr_type));
         hdr_ptr->len = pkt_ptr->logpkt_size;
         hdr_ptr->code = LOG_INTEG_ANGLE_CONFIG_C;
         hdr_ptr->ts[0] = 0;
         hdr_ptr->ts[1] = sns_em_get_timestamp();
         fwrite(pkt_ptr->log_pkt_contents, 1, pkt_ptr->logpkt_size, fp_log_integ_angle_config);
      }
      break;

   case SNS_LOG_INTEG_ANGLE_RESULT:
      if (fp_log_integ_angle_result != NULL)
      {
         log_hdr_type *hdr_ptr = (log_hdr_type *)(pkt_ptr->log_pkt_contents);
         memset(hdr_ptr, 0, sizeof(log_hdr_type));
         hdr_ptr->len = pkt_ptr->logpkt_size;
         hdr_ptr->code = LOG_INTEG_ANGLE_RESULT_C;
         hdr_ptr->ts[0] = 0;
         hdr_ptr->ts[1] = sns_em_get_timestamp();
         fwrite(pkt_ptr->log_pkt_contents, 1, pkt_ptr->logpkt_size, fp_log_integ_angle_result);
      }
      break;

   case SNS_LOG_INTEG_ANGLE_REPORT:
      if (fp_log_integ_angle_report != NULL)
      {
         log_hdr_type *hdr_ptr = (log_hdr_type *)(pkt_ptr->log_pkt_contents);
         memset(hdr_ptr, 0, sizeof(log_hdr_type));
         hdr_ptr->len = pkt_ptr->logpkt_size;
         hdr_ptr->code = LOG_INTEG_ANGLE_REPORT_C;
         hdr_ptr->ts[0] = 0;
         hdr_ptr->ts[1] = sns_em_get_timestamp();
         fwrite(pkt_ptr->log_pkt_contents, 1, pkt_ptr->logpkt_size, fp_log_integ_angle_report);
      }
      break;

   case SNS_LOG_GYRO_TAP_CONFIG:
      if (fp_log_gyro_tap_config != NULL)
      {
         log_hdr_type *hdr_ptr = (log_hdr_type *)(pkt_ptr->log_pkt_contents);
         memset(hdr_ptr, 0, sizeof(log_hdr_type));
         hdr_ptr->len = pkt_ptr->logpkt_size;
         hdr_ptr->code = LOG_GTAP_CONFIG_C;
         hdr_ptr->ts[0] = 0;
         hdr_ptr->ts[1] = sns_em_get_timestamp();
         fwrite(pkt_ptr->log_pkt_contents, 1, pkt_ptr->logpkt_size, fp_log_gyro_tap_config);
      }
      break;

   case SNS_LOG_GYRO_TAP_RESULT:
      if (fp_log_gyro_tap_result != NULL)
      {
         log_hdr_type *hdr_ptr = (log_hdr_type *)(pkt_ptr->log_pkt_contents);
         memset(hdr_ptr, 0, sizeof(log_hdr_type));
         hdr_ptr->len = pkt_ptr->logpkt_size;
         hdr_ptr->code = LOG_GTAP_RESULT_C;
         hdr_ptr->ts[0] = 0;
         hdr_ptr->ts[1] = sns_em_get_timestamp();
         fwrite(pkt_ptr->log_pkt_contents, 1, pkt_ptr->logpkt_size, fp_log_gyro_tap_result);
      }
      break;

   case SNS_LOG_GYRO_TAP_REPORT:
      if (fp_log_gyro_tap_report != NULL)
      {
         log_hdr_type *hdr_ptr = (log_hdr_type *)(pkt_ptr->log_pkt_contents);
         memset(hdr_ptr, 0, sizeof(log_hdr_type));
         hdr_ptr->len = pkt_ptr->logpkt_size;
         hdr_ptr->code = LOG_GTAP_REPORT_C;
         hdr_ptr->ts[0] = 0;
         hdr_ptr->ts[1] = sns_em_get_timestamp();
         fwrite(pkt_ptr->log_pkt_contents, 1, pkt_ptr->logpkt_size, fp_log_gyro_tap_report);
      }
      break;

#endif /* FEATURE_GESTURES_REL_1 */
#endif /* ENABLE_APPS_PLAYBACK */

   case SNS_LOG_GYRO_CAL_CONFIG:
      if (fp_log_gyro_cal_config != NULL)
      {
         log_hdr_type *hdr_ptr = (log_hdr_type *)(pkt_ptr->log_pkt_contents);
         memset(hdr_ptr, 0, sizeof(log_hdr_type));
         hdr_ptr->len = pkt_ptr->logpkt_size;
         hdr_ptr->code = LOG_SNS_GYRO_SIMP_CAL_CONFIG_C;
         hdr_ptr->ts[0] = 0;
         hdr_ptr->ts[1] = sns_em_get_timestamp();
         fwrite(pkt_ptr->log_pkt_contents, 1, pkt_ptr->logpkt_size, fp_log_gyro_cal_config);
      }
      break;

   case SNS_LOG_GYRO_CAL_RESULT:
      if (fp_log_gyro_cal_result != NULL)
      {
         log_hdr_type *hdr_ptr = (log_hdr_type *)(pkt_ptr->log_pkt_contents);
         memset(hdr_ptr, 0, sizeof(log_hdr_type));
         hdr_ptr->len = pkt_ptr->logpkt_size;
         hdr_ptr->code = LOG_SNS_GYRO_SIMP_CAL_RESULT_C;
         hdr_ptr->ts[0] = 0;
         hdr_ptr->ts[1] = sns_em_get_timestamp();
         fwrite(pkt_ptr->log_pkt_contents, 1, pkt_ptr->logpkt_size, fp_log_gyro_cal_result);
      }
      break;

   case SNS_LOG_GYRO_CAL_REPORT:
      if (fp_log_gyro_cal_report != NULL)
      {
         log_hdr_type *hdr_ptr = (log_hdr_type *)(pkt_ptr->log_pkt_contents);
         memset(hdr_ptr, 0, sizeof(log_hdr_type));
         hdr_ptr->len = pkt_ptr->logpkt_size;
         hdr_ptr->code = LOG_SNS_GYRO_SIMP_CAL_REPORT_C;
         hdr_ptr->ts[0] = 0;
         hdr_ptr->ts[1] = sns_em_get_timestamp();
         fwrite(pkt_ptr->log_pkt_contents, 1, pkt_ptr->logpkt_size, fp_log_gyro_cal_report);
      }
      break;

   default:
      /* do nothing yet */
      break;
   }
}


