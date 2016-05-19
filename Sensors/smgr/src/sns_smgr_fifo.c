/*=============================================================================
  @file sns_smgr_fifo.c

  This file contains the logic for managing sensor FIFO in SMGR

*******************************************************************************
* Copyright (c) 2014-2015 Qualcomm Technologies, Inc.
* All Rights Reserved.
* Confidential and Proprietary - Qualcomm Technologies, Inc.
********************************************************************************/

/* $Header: //components/rel/ssc.adsp/2.6.1/smgr/src/sns_smgr_fifo.c#2 $ */
/* $DateTime: 2015/05/22 16:04:29 $ */
/* $Author: pwbldsvc $ */

/*============================================================================
  EDIT HISTORY FOR FILE

  when        who  what, where, why
  ----------  ---  -----------------------------------------------------------
  2015-03-10  jms  - Calculate unified FIFO WM from max report rate of sensors in this FIFO
                   - Removed unused/ineffective discrete FIFO synch code
  2014-10-22  pn   Triggers update of report interval when updating watermark 
  2014-10-16  vy   Updated EWUR api to handle interrupt latency est
  2014-09-25  pn   Uses depth of appropriate depot
  2014-09-14  vy   Dynamically allocate Shared fifo data struct 
  2014-09-08  pn   Turns on QuP clock before triggering FIFO
  2014-08-05  pn   Separated FIFO flushing from watermark setting
  2014-04-23  pn   Initial version

============================================================================*/


/*----------------------------------------------------------------------------
 * Include Files
 * -------------------------------------------------------------------------*/
#include "sns_em.h"
#include "sns_log_types.h"
#include "sns_log_api.h"
#include "sns_memmgr.h"
#include "sns_profiling.h"
#include "sns_rh_util.h"
#include "sns_smgr_depot.h"
#include "sns_smgr_ddf_if.h"
#include "sns_smgr_hw.h"
#include "sns_smgr_main.h"
#include "sns_smgr_util.h"
#include "sns_smgr_pm_if.h"

/*----------------------------------------------------------------------------
 * Preprocessor Definitions and Constants
 * -------------------------------------------------------------------------*/
//#define SNS_SMGR_FIFO_DEBUG
#ifdef SNS_SMGR_FIFO_DEBUG
#define SNS_SMGR_FIFO_DBG0 SNS_SMGR_PRINTF0
#define SNS_SMGR_FIFO_DBG1 SNS_SMGR_PRINTF1
#define SNS_SMGR_FIFO_DBG2 SNS_SMGR_PRINTF2
#define SNS_SMGR_FIFO_DBG3 SNS_SMGR_PRINTF3
#else
#define SNS_SMGR_FIFO_DBG0(level,msg)
#define SNS_SMGR_FIFO_DBG1(level,msg,p1)
#define SNS_SMGR_FIFO_DBG2(level,msg,p1,p2)
#define SNS_SMGR_FIFO_DBG3(level,msg,p1,p2,p3)
#endif

//suitable_max_watermark = SNS_SMGR_FIFO_CALC_SUITABLE_MAX_WM(max_watermark);
#define SNS_SMGR_FIFO_SAFE_WM_PERCENT 90
#define SNS_SMGR_FIFO_CALC_SUITABLE_MAX_WM(max_wm)\
  ((max_wm * SNS_SMGR_FIFO_SAFE_WM_PERCENT) / 100)


/*----------------------------------------------------------------------------
 *  Variables
 * -------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------
 *  Function Prototypes
 * -------------------------------------------------------------------------*/

SMGR_STATIC sns_ddf_status_e sns_smgr_fifo_set_watermark
(
  sns_smgr_sensor_s*    sensor_ptr,
  sns_ddf_sensor_e      sensor
);

SMGR_STATIC uint16_t sns_smgr_fifo_calculate_suitable_max_watermark( 
  sns_smgr_sensor_s* sensor_ptr );

SMGR_STATIC void sns_smgr_fifo_discrete_configure( sns_smgr_sensor_s* sensor_ptr );

SMGR_STATIC sns_err_code_e sns_smgr_fifo_unified_configure( 
  sns_smgr_sensor_s* sensor_ptr );


/*----------------------------------------------------------------------------
 * Function Declarations and Documentation
 * -------------------------------------------------------------------------*/


//============================================================================
//============================================================================
//                       I N I T    F I F O
//============================================================================
//============================================================================

/*===========================================================================
  FUNCTION:   sns_smgr_find_sensor_by_ddf_sensor_type_and_dd_handle
===========================================================================*/
/*!
  @brief finds sns_smgr_sensor_s* - pointer to sensor
  @details Identifies sensor by ddf_sensor_type and dd_handle_ptr

  @param[in] sns_ddf_sensor_e  ddf_sensor_type
  @param[in] sns_ddf_handle_t  dd_handle_ptr
  @return
   sns_smgr_sensor_s* - pointer to the sensor of interest
 */
/*=====================================================================*/
SMGR_STATIC sns_smgr_sensor_s* sns_smgr_find_sensor_by_ddf_sensor_type_and_dd_handle
(
  sns_ddf_sensor_e       ddf_sensor_type,
  const sns_ddf_handle_t dd_handle_ptr
)
{
  uint8_t k;
  for ( k=0; k<ARR_SIZE(sns_smgr.sensor); k++ )
  {
    sns_smgr_sensor_s* sensor_ptr = &sns_smgr.sensor[k];
    uint8_t i;
    for ( i=0; i<ARR_SIZE(sensor_ptr->ddf_sensor_ptr); i++ )
    {
      if ( sensor_ptr->dd_handle           == dd_handle_ptr &&
           SMGR_SENSOR_TYPE(sensor_ptr, i) == ddf_sensor_type )
      {
        return sensor_ptr;
      }
    }
  }
  return NULL;
}

/*===========================================================================
  FUNCTION:   sns_smgr_init_fifo_cfg
===========================================================================*/
/*!
  @brief Initializes the fifo configuration of given sensor.
  @param[in/out] sensor_ptr - the sensor of interest
  @return
   none
 */
/*=========================================================================*/
sns_err_code_e sns_smgr_fifo_init_fifo_cfg( sns_smgr_sensor_s *sensor_ptr )
{
  uint8_t  i    = 0;
  uint32_t len  = 0;
  //uint16_t shared_sensor_cnt = 0;
  sns_ddf_fifo_attrib_get_s* fifo_attr_ptr = NULL;
  sns_ddf_status_e           ddf_status    = SNS_DDF_SUCCESS;

  SNS_OS_MEMSET(&(sensor_ptr->fifo_cfg),0,sizeof(smgr_sensor_fifo_cfg_s));

  if ( !SMGR_SENSOR_FIFO_IS_ENABLE(sensor_ptr) )
  {
    return SNS_ERR_NOTALLOWED;
  }

  ddf_status = sns_smgr_get_attr( sensor_ptr,
                                  SMGR_SENSOR_TYPE_PRIMARY(sensor_ptr),
                                  SNS_DDF_ATTRIB_FIFO,
                                  (void**)&fifo_attr_ptr,
                                  &len );

  if ( SNS_DDF_SUCCESS != ddf_status )
  {
    SNS_SMGR_PRINTF1( ERROR, "FIFO Init: get_attr ERROR, SensId=%d",
                      SMGR_SENSOR_ID(sensor_ptr) );
    return SNS_ERR_FAILED;
  }
  sensor_ptr->fifo_cfg.is_fifo_supported  = fifo_attr_ptr->is_supported;
  sensor_ptr->fifo_cfg.is_hw_watermark_int_supported = !(fifo_attr_ptr->is_sw_watermark);
  sensor_ptr->fifo_cfg.max_watermark      = fifo_attr_ptr->max_watermark;
  sensor_ptr->fifo_cfg.is_fifo_enabled    = false;
  if ( fifo_attr_ptr->is_supported )
  {
    sensor_ptr->fifo_cfg.can_fifo_be_used = true;
  }
  
  if ( !sensor_ptr->fifo_cfg.is_fifo_supported ||
        sensor_ptr->fifo_cfg.max_watermark == 0 )
  {
    SNS_SMGR_PRINTF3( ERROR,
                      "FIFO Init: fifoSupported=%d maxWM=%d, SensId=%d",
                      sensor_ptr->fifo_cfg.is_fifo_supported,
                      sensor_ptr->fifo_cfg.max_watermark, SMGR_SENSOR_ID(sensor_ptr) );
    sns_ddf_memhandler_free_ex(&sensor_ptr->memhandler, sensor_ptr);
    return SNS_ERR_NOTALLOWED;
  }

  //----------------- Shared fifo - sensor siblings ------------------------
  //shared_sensor_cnt = 0;
  sns_q_init(&sensor_ptr->fifo_cfg.shared_ddf_sens_q);

  for ( i=0; i < fifo_attr_ptr->share_sensor_cnt; i++ )
  {
    smgr_fifo_shared_sensor_s *shared_sen_ptr;
    
    if (sensor_ptr->is_uimg_refac)
    {
      shared_sen_ptr 
        = SNS_OS_ANY_MALLOC(SNS_DBG_MOD_DSPS_SMGR, sizeof(smgr_fifo_shared_sensor_s));
    }
    else
    {
      shared_sen_ptr
        = SNS_OS_MALLOC(SNS_DBG_MOD_DSPS_SMGR, sizeof(smgr_fifo_shared_sensor_s));
    }
    if (shared_sen_ptr == NULL)
    {
      sns_ddf_memhandler_free_ex(&sensor_ptr->memhandler, sensor_ptr);
      return SNS_ERR_NOMEM;
    }
    SNS_OS_MEMZERO(shared_sen_ptr, sizeof(smgr_fifo_shared_sensor_s));
    sns_q_link(shared_sen_ptr, &shared_sen_ptr->sibling_link);
    
    shared_sen_ptr->sibling_ddf_sensor_type = fifo_attr_ptr->share_sensors[i]->sensor;
    shared_sen_ptr->sibling_dd_handle_ptr   = fifo_attr_ptr->share_sensors[i]->dd_handle;

    if ( shared_sen_ptr->sibling_dd_handle_ptr == NULL )
    {
      SNS_SMGR_PRINTF1( ERROR,
                        "FIFO Init: sibling_dd_handle_ptr == NULL, SensType=%d",
                        shared_sen_ptr->sibling_ddf_sensor_type );
      continue;
    }

    shared_sen_ptr->sensor_ptr = sns_smgr_find_sensor_by_ddf_sensor_type_and_dd_handle(
          shared_sen_ptr->sibling_ddf_sensor_type,
          shared_sen_ptr->sibling_dd_handle_ptr );

    if ( shared_sen_ptr->sensor_ptr == NULL )
    {
      SNS_SMGR_PRINTF1( ERROR,
                        "FIFO Init: Cannot find shared sensor, SensType=%d",
                        shared_sen_ptr->sibling_ddf_sensor_type );
      continue;
    }

    if ( !SMGR_SENSOR_FIFO_IS_ENABLE(shared_sen_ptr->sensor_ptr) )
    {
      SNS_SMGR_PRINTF1( ERROR,
                        "FIFO Init: FIFO NOT ENABLE, SensType=%d",
                        shared_sen_ptr->sibling_ddf_sensor_type );
      continue;
    }

    shared_sen_ptr->sibling_sensor_id = shared_sen_ptr->sensor_ptr->const_ptr->sensor_id;

    //shared_sensor_cnt++;
    sns_q_put(&sensor_ptr->fifo_cfg.shared_ddf_sens_q, &shared_sen_ptr->sibling_link);
    
  }
  //sensor_ptr->fifo_cfg.shared_sensor_cnt = shared_sensor_cnt;
  //-------------------------------------------------------------------------

  sns_smgr_fifo_calculate_suitable_max_watermark( sensor_ptr );

  sns_ddf_memhandler_free_ex(&sensor_ptr->memhandler, sensor_ptr);
  return SNS_SUCCESS;
}

//============================================================================
//============================================================================
//            F I F O     E V E N T     P R O C E S S I N G
//============================================================================
//============================================================================

/*===========================================================================
  FUNCTION:   sns_smgr_fifo_on_sns_ddf_event_odr_changed
===========================================================================*/
/*!
  @brief configuring fifo on SNS_DDF_EVENT_ODR_CHANGED
  @param[in/out] ddf_sensor_ptr
  @param[in] sensor
  @return none
*/
/*=========================================================================*/
void sns_smgr_fifo_on_event_odr_changed
(
  sns_smgr_ddf_sensor_s* ddf_sensor_ptr,
  sns_ddf_sensor_e   sensor
)
{
  SNS_SMGR_PRINTF1(MED, "on_event_odr_changed - ddf_sensor=%d", sensor);
  sns_smgr_fifo_configure( ddf_sensor_ptr->sensor_ptr );
  sns_smgr_fifo_log_event( ddf_sensor_ptr, SNS_DDF_FIFO_ODR_CHANGED );
}


/*===========================================================================
  FUNCTION:   sns_smgr_fifo_on_event_fifo_available
===========================================================================*/
/*!
  @brief Fifo is available since the DD enabled fifo
         - configuring fifo on SNS_DDF_EVENT_FIFO_AVAILABLE event
  @param[in/out] sensor_ptr
  @param[in] sensor
  @return sns_ddf_status_e
*/
/*=========================================================================*/
sns_ddf_status_e sns_smgr_fifo_on_event_fifo_available
(
  sns_smgr_sensor_s* sensor_ptr,
  sns_ddf_sensor_e   sensor
)
{
  sns_smgr_ddf_sensor_s* ddf_sensor_ptr = sns_smgr_match_ddf_sensor( sensor_ptr, sensor );
  SNS_SMGR_FIFO_DBG1( MED, "FIFO SNS_DDF_EVENT_FIFO_AVAILABLE ddf_sensor=%d", sensor );
  if ( ddf_sensor_ptr == NULL )
  {
    return SNS_DDF_EINVALID_PARAM;
  }
  sns_smgr_fifo_configure( sensor_ptr );
  sns_smgr_fifo_log_event( ddf_sensor_ptr, SNS_DDF_FIFO_AVAILABLE );
  return SNS_DDF_SUCCESS;
}

/*===========================================================================
  FUNCTION:   sns_smgr_fifo_on_event_fifo_unavailable
===========================================================================*/
/*!
  @brief Fifo is unavailable since the DD disabled fifo
         - clearing fifo structures onSNS_DDF_EVENT_FIFO_UNAVAILABLE
  @param[i] sensor_ptr
  @param[i] sensor
  @return sns_ddf_status_e
*/
/*=========================================================================*/
sns_ddf_status_e sns_smgr_fifo_on_event_fifo_unavailable
(
  sns_smgr_sensor_s* sensor_ptr,
  sns_ddf_sensor_e   sensor
)
{
  sns_smgr_ddf_sensor_s* ddf_sensor_ptr = sns_smgr_match_ddf_sensor( sensor_ptr, sensor );
  SNS_SMGR_FIFO_DBG1( MED, "FIFO SNS_DDF_EVENT_FIFO_UNAVAILABLE ddf_sensor=%d", sensor );
  if ( ddf_sensor_ptr == NULL )
  {
    return SNS_DDF_EINVALID_PARAM;
  }
  //TODO: erase all fields -> sns_smgr_fifo_discrete_clean_sync_info();
  sensor_ptr->fifo_cfg.can_fifo_be_used  = false;
  sensor_ptr->fifo_cfg.current_watermark = 0;
  sensor_ptr->fifo_cfg.is_fifo_enabled   = false;

  sns_smgr_fifo_log_event( ddf_sensor_ptr, SNS_DDF_FIFO_DISABLED );
  return SNS_DDF_SUCCESS;
}


/*===========================================================================
  FUNCTION:   sns_smgr_fifo_on_sns_ddf_event_fifo_overflow
===========================================================================*/
/*!
  @brief reconfiguring fifo on SNS_DDF_EVENT_FIFO_OVERFLOW
  @param [in/out] sensor_ptr
  @param [in] sensor
  @return sns_ddf_status_e
*/
/*=========================================================================*/
sns_ddf_status_e sns_smgr_fifo_on_event_fifo_overflow
(
  sns_smgr_sensor_s*   sensor_ptr,
  sns_ddf_sensor_e     sensor
)
{
  sns_smgr_ddf_sensor_s* ddf_sensor_ptr = sns_smgr_match_ddf_sensor( sensor_ptr, sensor );
  SNS_SMGR_PRINTF1(MED, "on_event_fifo_overflow - ddf_sensor=%d", sensor );
  if ( ddf_sensor_ptr == NULL )
  {
    return SNS_DDF_EINVALID_PARAM;
  }
  sns_smgr_fifo_log_event( ddf_sensor_ptr, SNS_DDF_FIFO_OVERFLOW );

  //Reduce desired_watermark by 50%
  uint16_t desired_watermark = (sensor_ptr->fifo_cfg.current_watermark >> 1);

  sns_smgr_fifo_flush( sensor_ptr );
  if ( desired_watermark > 0 )
  {
    sensor_ptr->fifo_cfg.desired_watermark = desired_watermark;

    /* Set the new desired watermark only if it's value is  1 or more */
    sns_smgr_fifo_set_watermark( sensor_ptr, sensor );
  }
  return SNS_DDF_SUCCESS;
}


//============================================================================
//============================================================================
//                      P U B L I C     U T I L S
//============================================================================
//============================================================================

/*===========================================================================
FUNCTION:   sns_smgr_config_fifo
===========================================================================*/
/*!
  @brief configure FIFO for the sensor
  @details
  - This Function configures FIFO if necessary by
    recalculating watermark and sets it if it has changed.
  - Call this function for any change
    in report rates or the sensor ODR properties.
  @param[in/out] sensor_ptr - the sensor leader structure
  @return NONE
 */
/*=========================================================================*/
void sns_smgr_fifo_configure( sns_smgr_sensor_s* sensor_ptr )
{
  if ( SMGR_SENSOR_FIFO_IS_SUPPORTED(sensor_ptr) &&
       SMGR_SENSOR_IS_SELF_SCHED(sensor_ptr) )
  {
    if ( SNS_SMGR_FIFO_IS_UNIFIED(sensor_ptr) )
    {
      sns_smgr_fifo_unified_configure(sensor_ptr);
    }
    else
    {
      sns_smgr_fifo_discrete_configure(sensor_ptr);
    }
  }
}

//============================================================================
//============================================================================
//                   P R O T E C T E D     U T I L S
//============================================================================
//============================================================================

/*===========================================================================
FUNCTION:   sns_smgr_fifo_clean_sensor_cfg
===========================================================================*/
/*!
  @brief clean fifo_cfg for sensor
  @details
  @param[in/out] sensor_ptr   - sns_smgr_sensor_s
  @return NONE
 */
/*=====================================================================*/
SMGR_STATIC void sns_smgr_fifo_clean_sensor_cfg( sns_smgr_sensor_s* sensor_ptr )
{
  sensor_ptr->fifo_cfg.desired_watermark = 0;
}

/*===========================================================================
FUNCTION:   sns_smgr_fifo_unified_calc_max_rpt_rate
===========================================================================*/
/*!
  @brief find max report rate of all sensors on this unified fifo
  @details
  @param[in/out] sensor_ptr   - sns_smgr_sensor_s
  @return  max rpt rate for all sensors on the shared fifo
 */
/*=====================================================================*/
SMGR_STATIC q16_t sns_smgr_fifo_unified_calc_max_rpt_rate( sns_smgr_sensor_s* sensor_ptr )
{
  smgr_fifo_shared_sensor_s *shared_sens_ptr;
  q16_t max_rpt_rate = sns_rh_get_max_report_rate_for_sensor(sensor_ptr);

  SMGR_FOR_EACH_Q_ITEM(&sensor_ptr->fifo_cfg.shared_ddf_sens_q,
                       shared_sens_ptr, sibling_link)
  {
    if ( SMGR_SENSOR_FIFO_IS_SUPPORTED(sensor_ptr) && 
         SMGR_SENSOR_IS_SELF_SCHED(sensor_ptr)     &&
         sensor_ptr->sensor_state > SENSOR_STATE_IDLE )
    {
      q16_t max_rr = sns_rh_get_max_report_rate_for_sensor(shared_sens_ptr->sensor_ptr);
      max_rpt_rate = MAX( max_rpt_rate, max_rr );
    }
  }

  SNS_SMGR_PRINTF1(MED, "unified max_rpt_rate[Hz]=%u/100",
                   (unsigned)max_rpt_rate*100/65536);

  return max_rpt_rate;
}



//============================================================================
//============================================================================
//                          W A T E R  M A R K
//============================================================================
//============================================================================

/*===========================================================================
FUNCTION:   sns_smgr_fifo_set_watermark
===========================================================================*/
/*!
  @brief Set Watermark level for the sensor
  @details
  - This Function sets the watermark for sensor.
  - Watermark Value 0 means disable fifo. Value > 0 means fifo is enabled.
  @param[in] sensor_ptr        - the sensor leader structure
  @param[in] sensor            - sensor type
  @return  sns_ddf_status_e
 */
/*=========================================================================*/
SMGR_STATIC sns_ddf_status_e sns_smgr_fifo_set_watermark
(
  sns_smgr_sensor_s*       sensor_ptr,
  sns_ddf_sensor_e         sensor
)
{
  sns_ddf_status_e   ddf_status = SNS_DDF_SUCCESS;
  uint16_t           curr_wm = sensor_ptr->fifo_cfg.current_watermark;
  uint16_t           desired_wm = sensor_ptr->fifo_cfg.desired_watermark;
  uint32_t           curr_odr;
  q16_t              new_intr_rate;
  q16_t              old_intr_rate;
  
  curr_odr = SMGR_PRIMARY_SENSOR(sensor_ptr)->current_odr;  

  if( SMGR_SENSOR_FIFO_IS_SUPPORTED(sensor_ptr) &&
      sensor_ptr->fifo_cfg.can_fifo_be_used)
  {
    sns_ddf_fifo_set_s fifo_attr;
    SNS_OS_MEMZERO(&fifo_attr,sizeof(sns_ddf_fifo_set_s));

    fifo_attr.watermark = desired_wm;
    SNS_SMGR_PRINTF1(MED, "set_watermark - desired_wm=%u", fifo_attr.watermark);
    ddf_status = sns_smgr_set_attr(sensor_ptr, sensor, SNS_DDF_ATTRIB_FIFO, &fifo_attr);

    if ( ddf_status == SNS_DDF_SUCCESS )
    {
      new_intr_rate = FX_CONV_Q16((desired_wm == 0) ? 0 : (curr_odr/desired_wm), 0);
      old_intr_rate = FX_CONV_Q16((curr_wm == 0 ) ? 0 : (curr_odr/curr_wm), 0);
      sensor_ptr->fifo_cfg.is_fifo_enabled = (desired_wm > 0) ? true : false;
      sensor_ptr->fifo_cfg.current_watermark = desired_wm;
      sns_smgr_update_ewur(new_intr_rate, old_intr_rate,sensor_ptr->is_uimg_refac, true );
    }
  }
  return ddf_status;
}

/*===========================================================================
FUNCTION:   sns_smgr_fifo_calculate_suitable_max_watermark
===========================================================================*/
/*!
  @brief Calculate suitable Maximum Watermark for the sensor
  @details
  - This function calculates suitable max size of watermark as 90% of max watermark.
  - Reading sensor FIFO with big WM takes a few ms and may cause FIFO overflow!
    Suitable_max_wm is safe WM size to prevent FIFO overflow while reading from it.
  - TODO: This function should calculate suitable max size of watermark base on
    current ODR and maximum report rate
  - TODO: Should be called every time before calculating a watermark

  @param[in/out] sensor_ptr - the sensor leader structure

  @return
  uint16_t suitable maximum watermark
 */
/*=====================================================================*/
SMGR_STATIC uint16_t sns_smgr_fifo_calculate_suitable_max_watermark
( 
  sns_smgr_sensor_s* sensor_ptr 
)
{
  sensor_ptr->fifo_cfg.suitable_max_watermark =
      SNS_SMGR_FIFO_CALC_SUITABLE_MAX_WM(sensor_ptr->fifo_cfg.max_watermark);

  SNS_SMGR_PRINTF2(HIGH , "FIFO Calc & SET suitable_max_wmark to %u  SensId=%d",
                   sensor_ptr->fifo_cfg.suitable_max_watermark,SMGR_SENSOR_ID(sensor_ptr));

  return sensor_ptr->fifo_cfg.suitable_max_watermark;
}
/*===========================================================================
FUNCTION:   sns_smgr_fifo_get_suitable_max_watermark
===========================================================================*/
/*!
  @brief Returns suitable Maximum Watermark for the sensor
  @details
  - This Function returns suitable max size of safe watermark
  @param[in] sensor_ptr - the sensor leader structure
  @return  uint16_t suitable maximum watermark
 */
/*=====================================================================*/
uint16_t sns_smgr_fifo_get_suitable_max_watermark
( 
  const sns_smgr_sensor_s* sensor_ptr 
)
{
  uint16_t suitable_max_wm = sensor_ptr->fifo_cfg.suitable_max_watermark;
  if ( smgr_sensor_type_max_odr(sensor_ptr) > 200 )
  {
    /* to prevent fifo overflow, reduce the suitable wm by 1/2 if ODR is large */
    suitable_max_wm >>= 1;
  }
  return suitable_max_wm;
}

/*===========================================================================
FUNCTION:   sns_smgr_fifo_calculate_wm_and_div
===========================================================================*/
/*!
  @brief calculate FIFO watermarks and discrete watermark divider for fifo
  @details
  - Calculates watermark = SensorODR / max_report_rate
  - Calculates discrete watermark divider = desired_watermark / suitable_max_wm + 1
  - Stores result in ddf_sensor_ptr->sensor_ptr->fifo_cfg.desired_watermark
  - It's a common function for discrete and unified fifo.
  @param[in/out] ddf_sensor_ptr    - sns_smgr_ddf_sensor_s
  @param[in]     max_req_rpt_rate  - max rpt rate for discrete fifo sensor or for
                                     sensors on one unified fifo
  @return (used in discrete fifo)
  - Returns watermark divider for discrete fifo or 1
 */
/*=====================================================================*/
SMGR_STATIC uint16_t sns_smgr_fifo_calculate_wm_and_div
(
  sns_smgr_ddf_sensor_s* ddf_sensor_ptr,
  q16_t                  max_rpt_rate
)
{
  uint16_t discrete_wmark_div = 1;
  uint16_t suitable_max_wm    = 0;
  uint16_t desired_watermark  = 0;
  sns_smgr_sensor_s* sn_ptr   = NULL;

  sn_ptr = ddf_sensor_ptr->sensor_ptr;

  SNS_SMGR_PRINTF1(MED, "calc_wm_and_div - sensor=%u", SMGR_SENSOR_ID(sn_ptr));

  suitable_max_wm  = sns_smgr_fifo_get_suitable_max_watermark(sn_ptr);

  if ( max_rpt_rate > 0 && suitable_max_wm > 0 ) //div by 0 checks!
  {
    uint32_t max_sample_count = sns_smgr_get_max_sample_count(ddf_sensor_ptr);
    desired_watermark = FX_FLTTOFIX_Q16(smgr_sensor_type_max_odr(sn_ptr)) / max_rpt_rate;
    if ( desired_watermark > max_sample_count )
    {
      desired_watermark = max_sample_count - 1; //avoid filling buffer to full due to interpolation, etc
    }
    desired_watermark = MAX(1, desired_watermark);

    if ( desired_watermark >= suitable_max_wm )
    {
      //div by 0 check done earlier: if ( suitable_max_wm > 0 )
      discrete_wmark_div = desired_watermark / suitable_max_wm + 1;
    }
  }

  sn_ptr->fifo_cfg.desired_watermark = desired_watermark;

  SNS_SMGR_FIFO_DBG2(
    MED, "calc_wm_and_div - MaxRepRate[Hz]=%u/100 DiscreteDiv=%u",
    max_rpt_rate*100/65536, discrete_wmark_div );

  SNS_SMGR_PRINTF4(
    MED, "calc_wm_and_div - suitable=%u desired=%u current=%u MaxRepRate[Hz]=0x%x",
    suitable_max_wm, desired_watermark, sn_ptr->fifo_cfg.current_watermark,
    max_rpt_rate);

  return discrete_wmark_div;
}

/*===========================================================================
FUNCTION:   sns_smgr_fifo_set_wm_and_intr
===========================================================================*/
/*!
  @brief set FIFO watermark and interrupt for the sensor
  @details
  - This Function sets FIFO watermark if it has changed.
    and intr if requested by enable_intr argument
  - Takes watermark value from sensor_ptr->fifo_cfg.desired_watermark
  @param[in/out] sensor_ptr  - the sensor leader structure
  @return  sns_err_code_e
 */
/*=======================================================================*/
SMGR_STATIC 
sns_err_code_e sns_smgr_fifo_set_wm_and_intr(sns_smgr_sensor_s* sensor_ptr)
{
  sns_ddf_sensor_e ddf_sensor_type = SMGR_SENSOR_TYPE_PRIMARY(sensor_ptr);
  sns_smgr_ddf_sensor_s* ddf_sensor_ptr = SMGR_PRIMARY_SENSOR(sensor_ptr);
  bool enable_intr = (sensor_ptr->fifo_cfg.desired_watermark > 0) ? true : false;

  SNS_SMGR_PRINTF4(
    LOW, "set_wm_and_intr - ddf_sensor=%d curr/want=%u/%u enable_intr=%u",
    ddf_sensor_type, sensor_ptr->fifo_cfg.current_watermark, 
    sensor_ptr->fifo_cfg.desired_watermark, enable_intr);

  if ( !sensor_ptr->fifo_cfg.can_fifo_be_used ) //could be temporary unavailable
  {
    SNS_SMGR_PRINTF0(ERROR, "set_wm_and_intr - !can_fifo_be_used");
    return SNS_ERR_NOTALLOWED;
  }

  if ( sensor_ptr->fifo_cfg.desired_watermark >= 
       sensor_ptr->fifo_cfg.max_watermark ) // !tested in WM calc
  {
    SNS_SMGR_PRINTF0(ERROR, "set_wm_and_intr - desired_WM >= max_watermark");
    return SNS_ERR_BAD_PARM;
  }

  if ( sensor_ptr->fifo_cfg.desired_watermark > 0 &&
       sensor_ptr->sensor_state != SENSOR_STATE_READY &&
       sensor_ptr->sensor_state != SENSOR_STATE_CONFIGURING )
  {
    SNS_SMGR_PRINTF0(
      ERROR, "set_wm_and_intr - Sensor not in READY/CONFIGURING state");
    return SNS_ERR_NOTALLOWED;
  }

  if ( sensor_ptr->fifo_cfg.desired_watermark != 
       sensor_ptr->fifo_cfg.current_watermark )
  {
    if ( sensor_ptr->is_self_sched_intr_enabled )
    {
      sns_smgr_dd_enable_sched_data( sensor_ptr, ddf_sensor_type, false );
    }

    sns_smgr_fifo_flush( sensor_ptr );

    if ( sns_smgr_fifo_set_watermark(sensor_ptr, ddf_sensor_type) == SNS_DDF_SUCCESS )
    {
      /* change in FIFO watermark may affect report interval */
      ddf_sensor_ptr->client_stat.client_modifier.last_updated = sns_smgr.last_tick.u.low_tick;
    }
    else
    {
      SNS_SMGR_PRINTF0(
        ERROR,"set_wm_and_intr - failed setting WM; re-enabling INT now");
      return SNS_ERR_FAILED;
    }
  }

  if ( enable_intr != sensor_ptr->is_self_sched_intr_enabled )
  {
    sns_smgr_dd_enable_sched_data( sensor_ptr, ddf_sensor_type, enable_intr );
  }

  sns_smgr_fifo_log_event( 
    SMGR_PRIMARY_SENSOR(sensor_ptr),
    (sensor_ptr->fifo_cfg.desired_watermark > 0) ? 
    SNS_DDF_FIFO_ENABLED : SNS_DDF_FIFO_DISABLED );

  SNS_SMGR_PRINTF3(
    HIGH, "set_wm_and_intr - ddf_sensor=%u fifo_enabled=%u wm=%u",
    ddf_sensor_type, sensor_ptr->fifo_cfg.is_fifo_enabled,
    sensor_ptr->fifo_cfg.current_watermark);

  return SNS_SUCCESS;
}


//============================================================================
//============================================================================
//                   D I S C R E T E    F I F O
//============================================================================
//============================================================================

/*===========================================================================
FUNCTION:   sns_smgr_fifo_flush
===========================================================================*/
/*!
  @brief Flush FIFO for the sensors.
  @details
  - This Function flushes fifo for the respective sensors.
  @param[in/out] sensor_ptr - the sensor leader structure
  @return NONE
 */
/*=========================================================================*/
void sns_smgr_fifo_flush( sns_smgr_sensor_s* sensor_ptr )
{
  if ( SMGR_SENSOR_FIFO_IS_SUPPORTED(sensor_ptr) &&
       sensor_ptr->fifo_cfg.current_watermark >= 1 &&
       sensor_ptr->fifo_cfg.is_fifo_enabled )
  {
    sns_ddf_status_e ddf_status = SNS_DDF_EFAIL;

    /*Flush now, num_samples=0,return data now.*/
    if ( (SENSOR_STATE_FAILED != sensor_ptr->sensor_state) &&
         (NULL != SMGR_DRV_FN_PTR(sensor_ptr)->trigger_fifo_data) )
    {
      bool qup_clck_state = sns_hw_qup_clck_status();
      sns_ddf_sensor_e ddf_sensor_type = SMGR_SENSOR_TYPE_PRIMARY(sensor_ptr);
      bool toggle_self_sched = false;

      sns_hw_set_qup_clk(true);
      if ( sensor_ptr->is_self_sched_intr_enabled )
      {
        toggle_self_sched = true;
        sns_smgr_dd_enable_sched_data(sensor_ptr, ddf_sensor_type, false);
      }
      ddf_status = SMGR_DRV_FN_PTR(sensor_ptr)->trigger_fifo_data(
        sensor_ptr->dd_handle, ddf_sensor_type, 0, true );
      if( ddf_status == SNS_DDF_SUCCESS )
      {
        sns_smgr_fifo_log_event(
          SMGR_PRIMARY_SENSOR(sensor_ptr), SNS_DDF_FIFO_READ_FLUSH);
      }
      if ( toggle_self_sched )
      {
        sns_smgr_dd_enable_sched_data(sensor_ptr, ddf_sensor_type, true);
      }
      sns_hw_set_qup_clk(qup_clck_state);
    }
  }
}

/*===========================================================================
FUNCTION:   sns_smgr_fifo_discrete_calculate_watermarks
===========================================================================*/
/*!
  @brief calculate watermark for all discrete fifos
  @details
  - Calculates watermarks for all discrete fifos.
  - Configures fifo_active_info struct to sync all discrete fifos on one intr
  @param[in/out] sensor_ptr - the sensor leader structure
  @return none
 */
/*=========================================================================*/
SMGR_STATIC 
void sns_smgr_fifo_discrete_calculate_watermarks(sns_smgr_sensor_s* sensor_ptr)
{
  sns_smgr_ddf_sensor_s* ddf_sensor_ptr = SMGR_PRIMARY_SENSOR(sensor_ptr);
  q16_t max_rpt_rate = sns_rh_get_max_report_rate_for_sensor(sensor_ptr);
  uint16_t wm_div = sns_smgr_fifo_calculate_wm_and_div(ddf_sensor_ptr, max_rpt_rate);

  if ( wm_div > 1 )
  {
    uint16_t desired_wm = ddf_sensor_ptr->sensor_ptr->fifo_cfg.desired_watermark / wm_div;
    if ( desired_wm == 0 )
    {
      desired_wm = 1; //enable fifo on minimum size
    }
    ddf_sensor_ptr->sensor_ptr->fifo_cfg.desired_watermark = desired_wm;
  }

  SNS_SMGR_PRINTF3(
    MED, "discrete_calc_wm - sensor=%u wm=%u div=%u",
    SMGR_SENSOR_ID(sensor_ptr), 
    ddf_sensor_ptr->sensor_ptr->fifo_cfg.desired_watermark, wm_div);
}

/*===========================================================================
FUNCTION:   sns_smgr_fifo_discrete_configure
===========================================================================*/
/*!
  @brief Configures discrete FIFOs
  @details
  - Configures FIFO if necessary recalculates watermarks and sets them up.
  - Call this function for any change in report rates or the sensor ODR properties.
  @param[in/out] sensor_ptr - the sensor leader structure
  @return  void
 */
/*=========================================================================*/
SMGR_STATIC void sns_smgr_fifo_discrete_configure( 
  sns_smgr_sensor_s* sensor_ptr )
{
  SNS_SMGR_PRINTF1(
    HIGH, "discrete_configure - sensor=%u", SMGR_SENSOR_ID(sensor_ptr));

  sns_smgr_fifo_discrete_calculate_watermarks(sensor_ptr);
  sns_smgr_fifo_set_wm_and_intr(sensor_ptr);
}


//============================================================================
//============================================================================
//                   U N I F I E D    F I F O
//============================================================================
//============================================================================

/*===========================================================================
FUNCTION:   sns_smgr_fifo_unified_calculate_watermarks
===========================================================================*/
/*!
  @brief calculate all FIFO watermarks with watermark dividers for the shared sensors
  @details
  - Stores calculated water marks in:
    sensor_ptr->fifo_cfg.shared_ddf_sensor[i].sensor_ptr->fifo_cfg.desired_watermark
    end
    sensor_ptr->fifo_cfg.desired_watermark
  @param[in/out] sensor_ptr   - sns_smgr_sensor_s
  @return sns_err_code_e
 */
/*=====================================================================*/
SMGR_STATIC sns_err_code_e sns_smgr_fifo_unified_calculate_watermarks(
    sns_smgr_sensor_s* sensor_ptr )
{
  uint16_t unified_wmark_div = 1;
  uint16_t suitable_max_wm   = 0;
  uint32_t desired_watermark = 0;
  q16_t    max_rpt_rate      = sns_smgr_fifo_unified_calc_max_rpt_rate(sensor_ptr);

  smgr_fifo_shared_sensor_s  *shared_sens_ptr;
      
  sns_smgr_fifo_clean_sensor_cfg(sensor_ptr);
  if ( SMGR_PRIMARY_SENSOR(sensor_ptr)->client_stat.num_rpt_items > 0 )
  {
    sns_smgr_fifo_calculate_wm_and_div(SMGR_PRIMARY_SENSOR(sensor_ptr), max_rpt_rate);
    //NOTE: no fifo WM for secondary sensors
    desired_watermark = sensor_ptr->fifo_cfg.desired_watermark;
  }

  SMGR_FOR_EACH_Q_ITEM(&sensor_ptr->fifo_cfg.shared_ddf_sens_q,
                       shared_sens_ptr, sibling_link)
  {
    sns_smgr_fifo_clean_sensor_cfg(shared_sens_ptr->sensor_ptr);
    if ( SMGR_PRIMARY_SENSOR(shared_sens_ptr->sensor_ptr)->client_stat.num_rpt_items > 0 )
    {
      smgr_sensor_fifo_cfg_s* fifo_cfg_pt = &shared_sens_ptr->sensor_ptr->fifo_cfg;

      sns_smgr_fifo_calculate_wm_and_div(
            SMGR_PRIMARY_SENSOR(shared_sens_ptr->sensor_ptr), max_rpt_rate );
      desired_watermark += //Total Equivalent Sensor Samples
          (sensor_ptr->fifo_cfg.max_watermark * fifo_cfg_pt->desired_watermark
           / fifo_cfg_pt->max_watermark);
    }
  }
  //--> water marks stored in sensor_ptr->fifo_cfg.desired_watermark

  suitable_max_wm = sns_smgr_fifo_get_suitable_max_watermark(sensor_ptr);
  //SNS_SMGR_PRINTF1( MED, "FIFO calc WMs: suitable_max_wm=%d", suitable_max_wm );
  if ( desired_watermark < suitable_max_wm )
  {
    return SNS_SUCCESS;
  }

  if ( suitable_max_wm == 0 )
  {
    sensor_ptr->fifo_cfg.desired_watermark = 0;
    SMGR_FOR_EACH_Q_ITEM(&sensor_ptr->fifo_cfg.shared_ddf_sens_q,
                         shared_sens_ptr, sibling_link)
    {
      shared_sens_ptr->sensor_ptr->fifo_cfg.desired_watermark = 0;
    }
    return SNS_SUCCESS;
  }

  unified_wmark_div = (desired_watermark + suitable_max_wm - 1) / suitable_max_wm ;
  SNS_SMGR_PRINTF1( MED, "FIFO calc WMs: unified_wmark_div=%d", unified_wmark_div );
  if ( unified_wmark_div == 0 )
  {
    return SNS_SUCCESS;
  }

  SMGR_FOR_EACH_Q_ITEM(&sensor_ptr->fifo_cfg.shared_ddf_sens_q,
                       shared_sens_ptr, sibling_link)
  {
    shared_sens_ptr->sensor_ptr->fifo_cfg.desired_watermark /= unified_wmark_div;
  }

  sensor_ptr->fifo_cfg.desired_watermark /= unified_wmark_div;

  return SNS_SUCCESS;
}

/*===========================================================================
FUNCTION:   sns_smgr_fifo_unified_configure
===========================================================================*/
/*!
  @brief configure unified FIFO for the sensor
  @details
  - Configures FIFO if necessary by recalculating watermarks and setting them up.
  - Call this function for any change in report rates or the sensor ODR properties.
  @param[in/out] sensor_ptr - the sensor leader structure
  @return  sns_err_code_e
 */
/*=========================================================================*/
SMGR_STATIC sns_err_code_e sns_smgr_fifo_unified_configure( sns_smgr_sensor_s* sensor_ptr )
{
  uint16_t shared_cnt = 0;
  smgr_fifo_shared_sensor_s  *shared_sens_ptr;

  SNS_SMGR_PRINTF2(
    HIGH, "unified_configure - sensor=%u state=%u",
    SMGR_SENSOR_ID(sensor_ptr), sensor_ptr->sensor_state);

  if ( sns_smgr_fifo_unified_calculate_watermarks( sensor_ptr ) != SNS_SUCCESS )
  {
    SNS_SMGR_PRINTF0( ERROR, "unified_conf - shared WM calc ERROR ");
    return SNS_ERR_FAILED;
  }

  SNS_SMGR_FIFO_DBG1( HIGH, "unified_conf - set WM SensId=%d", SMGR_SENSOR_ID(sensor_ptr) );

  sns_smgr_fifo_set_wm_and_intr(sensor_ptr);

  shared_cnt = sensor_ptr->fifo_cfg.shared_ddf_sens_q.cnt;
  if ( shared_cnt == 0 )
  {
    return SNS_SUCCESS;
  }

  SMGR_FOR_EACH_Q_ITEM(&sensor_ptr->fifo_cfg.shared_ddf_sens_q, shared_sens_ptr, sibling_link)
  {
    sns_smgr_sensor_s* sens_ptr = shared_sens_ptr->sensor_ptr;
    if ( !SMGR_SENSOR_FIFO_IS_SUPPORTED(sens_ptr) ||
         !SMGR_SENSOR_IS_SELF_SCHED(sens_ptr) )
    {
      continue;
    }

    SNS_SMGR_FIFO_DBG1( HIGH, "unified_conf set WM SensId=%d", SMGR_SENSOR_ID(sens_ptr) );

    sns_smgr_fifo_set_wm_and_intr(sens_ptr);
  }

  return SNS_SUCCESS;
}

