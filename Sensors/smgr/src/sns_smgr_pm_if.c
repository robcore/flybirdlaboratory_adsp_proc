/*=============================================================================
  @file sns_smgr_pm_if_uimg.c

  This file contains interface between SMGR and PM.

*******************************************************************************
* Copyright (c) 2012 - 2014 Qualcomm Technologies, Inc.  All Rights Reserved.
* Qualcomm Technologies Proprietary and Confidential.
********************************************************************************/

/* $Header: //components/rel/ssc.adsp/2.6.1/smgr/src/sns_smgr_pm_if.c#1 $ */
/* $DateTime: 2014/12/01 08:57:58 $ */
/* $Author: pwbldsvc $ */

/*============================================================================
  EDIT HISTORY FOR FILE

  when        who  what, where, why
  ----------  ---  -----------------------------------------------------------
  2014-10-30  vy   Fixed a typo in a macro def
  2014-10-16  vy   Updated EWUR api to handle interrupt latency est
  2014-09-17  vy   Update sns_smgr_update_stay_in_bigimage for self-test info
  2014-09-07  vy   Updates to make MIPS/BW votes correct and meaningful 
  2014-07-31  pn   Removed POWER_INTERFACE featurization
  2014-05-13  vy   Initial version , SMGR-PM interface

============================================================================*/

/*----------------------------------------------------------------------------
 * Include Files
 * -------------------------------------------------------------------------*/
#include "sns_smgr_pm_if.h"
#include "sns_em.h"

#define SMGR_MSEC_PER_SEC_Q16         FX_CONV_Q16(1000,0)

#define SMGR_MAX_BW_REQ               100000
#define SMGR_MAX_WAKEUP_INTVL_USEC    1000000
#define SMGR_MAX_LATENCY_TOL_USEC     100000
#define SMGR_MIN_SENSOR_PER_SAMPLING  1


extern sns_smgr_pm_stats_s smgr_pm_stats;
extern sns_pm_handle_t sns_rh_get_pm_client_handle(void);


/*----------------------------------------------------------------------------
 * Type Declarations
 * -------------------------------------------------------------------------*/

 
/*----------------------------------------------------------------------------
 *  Variables
 * -------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
 * Function prototypes
 * -------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------
 * Function Declarations and Documentation
 * -------------------------------------------------------------------------*/
/*===========================================================================

  FUNCTION:   sns_smgr_pm_stats_init

===========================================================================*/
/*!
  @brief This function intializes smgr pm stat variables.

  @detail

  @param[i]  None
  @return   None
 */
/*=========================================================================*/ 
void sns_smgr_pm_stats_init
(
  void
)
{
  sns_pm_err_code_e pm_err;
  SNS_OS_MEMZERO(&smgr_pm_stats, sizeof(sns_smgr_pm_stats_s));

  pm_err = sns_pm_client_init(&smgr_pm_stats.pm_client_handle, 
                              sns_smgr_app_state_change, "SMGR");
  SNS_ASSERT(pm_err == SNS_PM_SUCCESS && smgr_pm_stats.pm_client_handle != NULL);
  /* Initialize individual fields */
  smgr_pm_stats.max_sens_per_sampling = SMGR_MIN_SENSOR_PER_SAMPLING;
  pm_err = sns_pm_set_latency( smgr_pm_stats.pm_client_handle, SMGR_MAX_LATENCY_TOL_USEC );
  SNS_SMGR_PM_IF_DBG0(HIGH, "sns_smgr_pm_stats_init done");
}  /* sns_smgr_pm_stats_init */


/*===========================================================================

  FUNCTION:   sns_smgr_update_latency_est

===========================================================================*/
/*!
  @brief This function computes latency estimation for SMGR.

  @detail An estimation of latency that can be tolerated is the maximum ODR,
  the interrupt rate, among all DRI sensors. 
 
  Following is the relationship between interrupt rate and latency ticks
  0<= intr_rate < 1Hz => latency_est_ticks = DSPS_SLEEP_CLK = 1000 msec
  1<= intr_rate < 2Hz => latency_est_ticks = DSPS_SLEEP_CLK/2 = 500 msec
  2<= intr_rate < 4Hz => latency_est_ticks = DSPS_SLEEP_CLK/4 = 250 msec
  4<= intr_rate < 8Hz => latency_est_ticks = DSPS_SLEEP_CLK/8 = 125 msec
  8<= intr_rate < 16Hz => latency_est_ticks = DSPS_SLEEP_CLK/16 = 62 msec
  ... 
  ... 
  512<= intr_rate < 1024Hz => latency_est_ticks = DSPS_SLEEP_CLK/1024 < 1 msec 
  and so on 
 
  This latency estimate is further capped by SMGR_MAX_LATENCY_TOL_USEC.
 
  @param[i]  None
  @return   None
 */
/*=========================================================================*/
static void sns_smgr_update_latency_est
(
   void 
)
{
  sns_pm_err_code_e smgr_pm_err;
  uint32_t          latency_est_usec;  
  uint32_t          intr_rate = FX_CONV(smgr_pm_stats.tot_int_rate,FX_QFACTOR,0);

  SNS_SMGR_PM_IF_DBG1(HIGH, "sns_smgr_update_latency_est: intr rate: %u", intr_rate);
  
  /* Update Latency estimate */
  smgr_pm_stats.latency_est_ticks = DSPS_SLEEP_CLK;
  while ( intr_rate >= 1 )
  {
    smgr_pm_stats.latency_est_ticks = smgr_pm_stats.latency_est_ticks >> 1;
    intr_rate = intr_rate >> 1;
  }
  latency_est_usec = sns_em_convert_dspstick_to_usec(smgr_pm_stats.latency_est_ticks);
  latency_est_usec = MIN(SMGR_MAX_LATENCY_TOL_USEC, latency_est_usec);
  
  smgr_pm_err = sns_pm_set_latency( smgr_pm_stats.pm_client_handle, latency_est_usec );
  if (smgr_pm_err != SNS_PM_SUCCESS)
  {
    SNS_SMGR_PM_IF_DBG1(HIGH, "SNS_SMGR failed to set_latency: %u", smgr_pm_err);
  }
  else
  {
    SNS_SMGR_PM_IF_DBG1(MED, "sns_smgr_update_latency_est, lat_est_usec = %u", 
                     latency_est_usec);
  }
}   /* sns_smgr_update_latency_est */


/*===========================================================================

  FUNCTION:   sns_smgr_update_ewur_local

===========================================================================*/
/*!
  @brief This function increase or decreases the estimated Effective wakeup
  rate (EWUR). This is called by SMGR whenever a polling or DRI sensor
  is added or removed. 
  Whenever, EWUR_est is updated, it is conveyed to the PM via a PM API.
 
  @detail  

  @param[i]  infreq_Hz: sampling freq of added sensor
  @param[i]  out_freq_Hz: sampling freq of removed sensor
  @return   None
 */
/*=========================================================================*/ 
static void sns_smgr_update_ewur_local
(
  q16_t   in_freq_Hz,
  q16_t   out_freq_Hz,
  q16_t  *pm_ewur_est
)
{
  q16_t prev_eff_wakeup_rate = *pm_ewur_est;
  q16_t new_eff_wakeup_rate = prev_eff_wakeup_rate;
  
    /* Update EWUR */
  new_eff_wakeup_rate += (in_freq_Hz - out_freq_Hz);
  
  /* Handle overflow error */
  if ( (uint32)in_freq_Hz >= (uint32)out_freq_Hz )
  {
    if ( (uint32)new_eff_wakeup_rate < (uint32)prev_eff_wakeup_rate )
    {
      new_eff_wakeup_rate = prev_eff_wakeup_rate;
    }
  }
  else if ( (uint32)new_eff_wakeup_rate > (uint32)prev_eff_wakeup_rate )
  {
    new_eff_wakeup_rate = 0;
  }
  *pm_ewur_est = new_eff_wakeup_rate;

}


/*===========================================================================

  FUNCTION:   sns_smgr_update_ewur

===========================================================================*/
/*!
  @brief This function increase or decreases the estimated Effective wakeup
  rate (EWUR). This is called by SMGR whenever a polling or DRI sensor
  is added or removed. 
  Whenever, EWUR_est is updated, it is conveyed to the PM via a PM API.
 
  @detail  

  @param[i]  infreq_Hz: sampling freq of added sensor
  @param[i]  out_freq_Hz: sampling freq of removed sensor
  @param[i]  is_uimg_refac: true if caller is supported in uimg
  @param[i]  intr_based: true if rate is for interrupt
  @return   None
 */
/*=========================================================================*/ 
void sns_smgr_update_ewur
(
  q16_t    in_freq_Hz,
  q16_t    out_freq_Hz,
  bool     is_uimg_refac,
  bool     intr_based
)
{
  sns_pm_err_code_e smgr_pm_err;
  uint32_t          eff_wakeup_intvl_usec = 0;
  
  sns_smgr_update_ewur_local(in_freq_Hz, out_freq_Hz, &smgr_pm_stats.eff_wakeup_rate_hz_est);
  if ( !is_uimg_refac )
  {
    sns_smgr_update_ewur_local(in_freq_Hz, out_freq_Hz, &smgr_pm_stats.eff_wakeup_rate_hz_est_big);
  }
  if ( intr_based )
  {
    sns_smgr_update_ewur_local(in_freq_Hz, out_freq_Hz, &smgr_pm_stats.tot_int_rate);
    sns_smgr_update_latency_est();
  }
  
  if (smgr_pm_stats.eff_wakeup_rate_hz_est > 0)
  {
    eff_wakeup_intvl_usec = 1000*FX_CONV(FX_DIV_Q16(SMGR_MSEC_PER_SEC_Q16,smgr_pm_stats.eff_wakeup_rate_hz_est),FX_QFACTOR,0);
  }
  else
  {
    eff_wakeup_intvl_usec = SMGR_MAX_WAKEUP_INTVL_USEC;
  }
  smgr_pm_err = sns_pm_set_wakeup_interval(smgr_pm_stats.pm_client_handle, 
                                           eff_wakeup_intvl_usec);
  if (smgr_pm_err != SNS_PM_SUCCESS)
  {
    SNS_SMGR_PM_IF_DBG1(HIGH, "SNS_SMGR failed to set_wakeup_interval: %u", smgr_pm_err);
  }
  else
  {
    SNS_SMGR_PM_IF_DBG3(MED, "sns_smgr_update_ewur, SMGR - in_fHz=0x%x, out_fHz=0x%x, wakeup_intvl_us=%u", 
     in_freq_Hz, out_freq_Hz, eff_wakeup_intvl_usec);
    /* Vote MIPS requirement */
    sns_smgr_vote_mips_bw_reqd();
  }
  
}   /* sns_smgr_update_ewur */


/*===========================================================================

  FUNCTION:   sns_smgr_update_proc_rept_rate

===========================================================================*/
static void sns_smgr_update_proc_rept_rate
(
  q16_t   in_rept_rate_Hz,
  q16_t   out_rept_rate_Hz,
  q16_t  *proc_rept_rate_Hz 
)
{
  q16_t prev_eff_report_rate_est = *proc_rept_rate_Hz;
  q16_t new_eff_report_rate_est = prev_eff_report_rate_est;
  
  /* Update Eff Report Rate  */
  new_eff_report_rate_est += (in_rept_rate_Hz - out_rept_rate_Hz);
  /* Handle overflow situation */
  if ((uint32_t)out_rept_rate_Hz > (uint32_t)in_rept_rate_Hz)
  {
    if ((uint32_t)new_eff_report_rate_est > (uint32_t)prev_eff_report_rate_est)
    {
      new_eff_report_rate_est = 0;
    }
  }
  else
  {
    if ((uint32_t)new_eff_report_rate_est < (uint32_t)prev_eff_report_rate_est)
    {
      new_eff_report_rate_est = prev_eff_report_rate_est;
    }
  }
  *proc_rept_rate_Hz = new_eff_report_rate_est;
}


/*===========================================================================

  FUNCTION:   sns_smgr_update_eff_rept_rate_est

===========================================================================*/
/*!
  @brief  The effective report generation rate, ERGR_est, is sum of report
  rates (q16_rpt_rate) of all reports handled by the SMGR. It is updated
  every time a report is activated or deactivated

  @detail

  @param[i]  Report rate of incoming report req
  @param[i]  Report rate of removing report req
  @return   None
 */
/*=========================================================================*/
void sns_smgr_update_eff_rept_rate_est
(
  q16_t               in_rep_rate_Hz,
  q16_t               out_rep_rate_Hz,
  sns_proc_type_e_v01 proc_type
)
{
  switch ( proc_type ) {
    case SNS_PROC_SSC_V01:
      sns_smgr_update_proc_rept_rate(in_rep_rate_Hz, out_rep_rate_Hz,
                                     &smgr_pm_stats.eff_report_rate_est_int);
      break;
    case SNS_PROC_APPS_V01:
      sns_smgr_update_proc_rept_rate(in_rep_rate_Hz, out_rep_rate_Hz,
                                     &smgr_pm_stats.eff_report_rate_est_aps);
      break;
    case SNS_PROC_MODEM_V01:
      sns_smgr_update_proc_rept_rate(in_rep_rate_Hz, out_rep_rate_Hz,
                                     &smgr_pm_stats.eff_report_rate_est_nonaps);
      break;
    default:
      // do nothing
      break;
  }
  
  SNS_SMGR_PM_IF_DBG2(
    MED, "update_eff_rept_rate_est RH - in_fHz=0x%x out_fHz=0x%x", 
    in_rep_rate_Hz, out_rep_rate_Hz);
  SNS_SMGR_PM_IF_DBG3(
    MED, "update_eff_rept_rate_est RH - rpt_rate_int=0x%x, rpt_rate_aps=0x%x, rpt_rate_nonaps=0x%x", 
    smgr_pm_stats.eff_report_rate_est_int, smgr_pm_stats.eff_report_rate_est_aps, 
    smgr_pm_stats.eff_report_rate_est_nonaps);
  
}   /* sns_smgr_update_eff_rept_rate_est */


/*===========================================================================

  FUNCTION:   sns_smgr_update_bw_reqd

===========================================================================*/
/*!
  @brief This function estimates the SMGR bandwith requirement, which is
  defined as the desired data rate of the system bus (DDR) to send data back
  to clients.
  Whenever a report request is added to the SMGR or deleted from the SMGR,
  the BW requirement (in bytes per sec Bps) is updated 
 
  @detail

  @param[i]  infreq_Hz: sampling freq of added sensor
  @param[i]  out_freq_Hz: sampling freq of removed sensor
  @return   None
 */
/*=========================================================================*/
void sns_smgr_update_bw_reqd
(
  uint16_t            in_freq_Hz,
  uint16_t            out_freq_Hz
)
{
  static uint32_t  total_rate_Hz = 0;
  uint32_t         prev_rate_Hz = total_rate_Hz;
  uint32_t         new_bw_reqd_est = 0;
  uint32_t         prev_bw_reqd_est = smgr_pm_stats.bw_reqd_est;
  q16_t            eff_rpt_rate_q16 = 0;
  uint32_t         eff_rpt_rate = 0;
  
  total_rate_Hz += (in_freq_Hz - out_freq_Hz);
  
  /* Handle overflow situation */
  if( in_freq_Hz > out_freq_Hz )
  {
    if ( total_rate_Hz < prev_rate_Hz )
    {
      total_rate_Hz = prev_rate_Hz;
    }
  }
  else
  {
    if ( total_rate_Hz > prev_rate_Hz )
    {
      total_rate_Hz = 0;
    }
  }

  eff_rpt_rate_q16 = smgr_pm_stats.eff_report_rate_est_aps + 
      smgr_pm_stats.eff_report_rate_est_nonaps;

  eff_rpt_rate = FX_CONV(eff_rpt_rate_q16, FX_QFACTOR, 0);
  if ( smgr_pm_stats.eff_report_rate_est != 0 && eff_rpt_rate == 0 )
    eff_rpt_rate = 1;
  
  new_bw_reqd_est = total_rate_Hz*sizeof(sns_smgr_sample_s)*eff_rpt_rate;
  new_bw_reqd_est = MIN(SMGR_MAX_BW_REQ, new_bw_reqd_est);
  
  smgr_pm_stats.bw_reqd_est = new_bw_reqd_est; 
  

  SNS_SMGR_PM_IF_DBG3(MED,"smgr update bw reqd: in_freq_Hz=%u, out_freq_Hz=%u, total_rate=%u", 
                   in_freq_Hz, out_freq_Hz, total_rate_Hz);
  
  SNS_SMGR_PM_IF_DBG2(MED, "smgr update bw reqd: prev bw=%u, new_bw=%u", 
                   prev_bw_reqd_est, new_bw_reqd_est); 

}   /* sns_smgr_update_bw_reqd */


/*===========================================================================

  FUNCTION:   sns_smgr_update_avgitems

===========================================================================*/
/*!
  @brief Computes average/sensor over all report items getting samples

  @detail

  @param[i]  None
  @return   None
 */
/*=========================================================================*/
void sns_smgr_update_avgitems
(
   void
)
{
  uint8_t  i, j;
  uint32_t num_sens = 0;
  uint8_t  num_items = 0;

  smgr_pm_stats.avg_items_per_sens = 0;
  
  /* Go through all the sensors to take avg */
  for ( i=0; i<ARR_SIZE(sns_smgr.sensor); i++ )
  {
    sns_smgr_sensor_s *sensor_ptr = &sns_smgr.sensor[i];
    for ( j=0; j<ARR_SIZE(sensor_ptr->ddf_sensor_ptr); j++ )
    {
      if ( sensor_ptr->ddf_sensor_ptr[j] != NULL )
      {
        num_items = sensor_ptr->ddf_sensor_ptr[j]->client_stat.num_rpt_items;
        if (num_items > 0)
        {
          num_sens++;
          smgr_pm_stats.avg_items_per_sens += num_items;
        }
      }
    }
  }
  if ( num_sens > 0 )
  {
    smgr_pm_stats.avg_items_per_sens /= num_sens;
  }

  SNS_SMGR_PM_IF_DBG1(MED, "sns_smgr_update_avgitems, SMGR - #avg items/sensors = %u", 
                   smgr_pm_stats.avg_items_per_sens);
  
  /* Signal to vote MIPS BW requirement */
  sns_smgr_signal_me(SNS_SMGR_VOTE_MIPS_BW);
  
}   /* sns_smgr_update_avgitems */


/*===========================================================================

  FUNCTION:   sns_smgr_update_maxsensors

===========================================================================*/
/*!
  @brief Computes the max number of sensors sampled at any sampling instance

  @detail This is maximum number of sensors getting sampled at any sampling
  instance. It is computed by taking max of all sensors in a sensor queue of
  each schedule block in the schedule queue.
  It is updated every time a new report is activated or deactivated

  @param[i]  None
  @return   None
 */
/*=========================================================================*/
void sns_smgr_update_maxsensors
(
  void
)
{
  smgr_sched_block_s  *sched_blk_ptr;
  int queue_count = 0;

  SMGR_FOR_EACH_Q_ITEM(&sns_smgr.sched_que, sched_blk_ptr, sched_link)
  {
    if (sched_blk_ptr != NULL)
    {
      queue_count = sns_q_cnt(&sched_blk_ptr->ddf_sensor_queue);
      if ( queue_count < 0 )
      {
        SNS_SMGR_PM_IF_DBG1(HIGH, "SNS_SMGR queue count ddf sensor is below 0, queue_cnt = %d", 
                            queue_count);
      }
      if( smgr_pm_stats.max_sens_per_sampling < queue_count )
      {
        smgr_pm_stats.max_sens_per_sampling = queue_count;
      }
    }
  }

  SNS_SMGR_PM_IF_DBG1(MED, "sns_smgr_update_maxsensors, Max sensors/sampling (>0) = %u", 
                   smgr_pm_stats.max_sens_per_sampling);

  /* Vote MIPS BW requirement */
  sns_smgr_vote_mips_bw_reqd();
  
}   /* sns_smgr_update_maxsensors */


/*===========================================================================

  FUNCTION:   sns_smgr_update_stay_in_bigimage

===========================================================================*/
/*!
  @brief Updates stay in bigimage info

  @param  none
 
  @return none
 */
/*=========================================================================*/
void sns_smgr_update_stay_in_bigimage
(
  void
)
{
  #define SNS_SMGR_U_EXIT_HI_THRESH_Q16 FX_CONV_Q16(10,0)

  q16_t eff_exit_rate_est = smgr_pm_stats.eff_report_rate_est_nonaps;
  if ( sns_smgr.app_is_awake ) 
    eff_exit_rate_est += smgr_pm_stats.eff_report_rate_est_aps;
  eff_exit_rate_est += smgr_pm_stats.eff_wakeup_rate_hz_est_big;
  
  if ((uint32_t)eff_exit_rate_est > (uint32_t)SNS_SMGR_U_EXIT_HI_THRESH_Q16
      || sns_smgr.self_test.self_test_req != NULL 
      || smgr_pm_stats.stay_in_bigimage_ext)
  {
    smgr_pm_stats.stay_in_bigimage = true;
  }
  else
  {
    smgr_pm_stats.stay_in_bigimage = false;
  }

}


/*===========================================================================

  FUNCTION:   sns_smgr_vote_mips_bw_reqd

===========================================================================*/
/*!
  @brief Computed the estimated MIPS requirement based on the
  current sensors and request demand using the current values of EWUR_est,
  Max_sens_per_sampling, Avg_items_per_sens, and ERR_est along with the
  profiled values of SMGR_INSTR_PER_SENSOR, SMGR_INSTR_PER_ITEM,
  and SMGR_INSTR_PER_REPORT.

  @detail The total SMGR work load in terms of CPU instruction can be divided
  into three parts: 1. Data Sampling and Storage for each sensor, 2. Data
  Filtering and processing for each item with each sensor, and 3. Data Reporting
  to clients for each report request.

  @param[i]  None
  @return   None
 */
/*=========================================================================*/
void sns_smgr_vote_mips_bw_reqd
(
  void
)
{
  
  #define ONE_MILLION_2s_EXP            20
  #define SMGR_INSTR_PER_SENSOR_2s_EXP  17
  #define SMGR_INSTR_PER_ITEM_2s_EXP    17
  #define SMGR_INSTR_PER_REPORT         200000
  #define SMGR_MIPS_THRESH              40
  #define SMGR_MIPS_LEVEL1              40
  #define SMGR_MIPS_LEVEL2              200

  sns_pm_err_code_e smgr_pm_err;
  uint32_t          prev_mips_reqd_est_smgr = smgr_pm_stats.mips_reqd_est_smgr;
  uint32_t          prev_mips_reqd_est_rh = smgr_pm_stats.mips_reqd_est_rh;
  uint32_t          eff_rpt_rate = 0; 
  uint32_t          total_bw_reqd = 0;

  smgr_pm_stats.eff_report_rate_est = smgr_pm_stats.eff_report_rate_est_nonaps; 
  if ( sns_smgr.app_is_awake )
    smgr_pm_stats.eff_report_rate_est += smgr_pm_stats.eff_report_rate_est_aps;
  smgr_pm_stats.eff_report_rate_est += smgr_pm_stats.eff_report_rate_est_int;

  sns_smgr_update_stay_in_bigimage();

  eff_rpt_rate = FX_CONV(smgr_pm_stats.eff_report_rate_est, FX_QFACTOR, 0);
  if ( smgr_pm_stats.eff_report_rate_est != 0 && eff_rpt_rate == 0 )
    eff_rpt_rate = 1;
  
  SNS_SMGR_PM_IF_DBG2(MED, "eff_wake_rate=0x%x, max_sens/sampling=%u",
                   smgr_pm_stats.eff_wakeup_rate_hz_est, smgr_pm_stats.max_sens_per_sampling);
  SNS_SMGR_PM_IF_DBG2(MED, "eff_rpt_rate_total=0x%x, avg_items/sens=%u", 
                   smgr_pm_stats.eff_report_rate_est, smgr_pm_stats.avg_items_per_sens);
  
  /* Update MIPS reqd as per updated EWUR and effective rpt rate */
  smgr_pm_stats.mips_reqd_est_rh = smgr_pm_stats.mips_reqd_est_smgr =
    (FX_CONV(smgr_pm_stats.eff_wakeup_rate_hz_est,FX_QFACTOR,0)*smgr_pm_stats.max_sens_per_sampling);
  smgr_pm_stats.mips_reqd_est_smgr <<= SMGR_INSTR_PER_SENSOR_2s_EXP;
  smgr_pm_stats.mips_reqd_est_smgr >>= ONE_MILLION_2s_EXP;

  SNS_SMGR_PM_IF_DBG2(MED, "prev mips_est_smgr=%u, new mips_est_smgr=%u", 
                   prev_mips_reqd_est_smgr, smgr_pm_stats.mips_reqd_est_smgr);
  if ( smgr_pm_stats.mips_reqd_est_smgr < SMGR_MIPS_THRESH )
  {
    smgr_pm_stats.mips_reqd_est_smgr = SMGR_MIPS_LEVEL1;
  }
  else
  {
    smgr_pm_stats.mips_reqd_est_smgr = SMGR_MIPS_LEVEL2;
  }

  smgr_pm_stats.mips_reqd_est_rh *= smgr_pm_stats.avg_items_per_sens;
  smgr_pm_stats.mips_reqd_est_rh <<= SMGR_INSTR_PER_ITEM_2s_EXP;
  smgr_pm_stats.mips_reqd_est_rh += eff_rpt_rate*SMGR_INSTR_PER_REPORT;
  smgr_pm_stats.mips_reqd_est_rh >>= ONE_MILLION_2s_EXP; 

  SNS_SMGR_PM_IF_DBG2(MED, "prev mips_est_rh=%u, new mips_est_rh=%u", 
                   prev_mips_reqd_est_rh, smgr_pm_stats.mips_reqd_est_rh);
  if ( smgr_pm_stats.mips_reqd_est_rh < SMGR_MIPS_THRESH )
  {
    smgr_pm_stats.mips_reqd_est_rh = SMGR_MIPS_LEVEL1;
  }
  else
  {
    smgr_pm_stats.mips_reqd_est_rh = SMGR_MIPS_LEVEL2;
  }  
  
  /* SMGR Vote MIPS */
  smgr_pm_err = sns_pm_vote_mips( smgr_pm_stats.pm_client_handle, smgr_pm_stats.mips_reqd_est_smgr );
  if (smgr_pm_err != SNS_PM_SUCCESS)
  {
    SNS_SMGR_PM_IF_DBG1(HIGH, "SMGR failed to vote_mips: %u", smgr_pm_err);
  }
  else
  {
    SNS_SMGR_PM_IF_DBG1(MED, "sns_smgr_vote_mips_bw_reqd - SMGR - mips voted = %u", 
                     smgr_pm_stats.mips_reqd_est_smgr);
  }
  
  /* RH Vote MIPS */
  smgr_pm_err = sns_pm_vote_mips( sns_rh_get_pm_client_handle(), smgr_pm_stats.mips_reqd_est_rh );
  if (smgr_pm_err != SNS_PM_SUCCESS)
  {
    SNS_SMGR_PM_IF_DBG1(HIGH, "RH failed to vote_mips: %u", smgr_pm_err);
  }
  else
  {
    SNS_SMGR_PM_IF_DBG1(MED, "sns_smgr_vote_mips_bw_reqd - RH - mips voted = %u", 
                     smgr_pm_stats.mips_reqd_est_rh);
  }
  
  /* RH Vote BW */
  total_bw_reqd = smgr_pm_stats.bw_reqd_est; 
  smgr_pm_err = sns_pm_vote_bw(sns_rh_get_pm_client_handle(), total_bw_reqd, SNS_CORE_DDR);
  if (smgr_pm_err != SNS_PM_SUCCESS)
  {
    SNS_SMGR_PM_IF_DBG1(HIGH, "SNS_SMGR failed to vote_bw: %u", smgr_pm_err);
  }
  else
  {
    SNS_SMGR_PM_IF_DBG1(MED, "sns_smgr_vote_mips_bw_reqd - RH - bw voted = %u", total_bw_reqd);
  }

}   /* sns_smgr_vote_mips_bw_reqd */


/*===========================================================================

  FUNCTION:   sns_smgr_set_stay_in_big_image

===========================================================================*/
/*!
  @brief Sets or clears stay_in_big_image.
  @param [in] stay - true to set, false to clear
  @return none
 */
/*=========================================================================*/
void sns_smgr_set_stay_in_big_image(bool stay)
{
  smgr_pm_stats.stay_in_bigimage_ext = stay;
  sns_smgr_update_stay_in_bigimage();
}


/*===========================================================================

 FUNCTION:   sns_smgr_pm_vote_powerrail

==========================================================================*/
/*!
  @brief Sending RMP message to change the power state of power rail
 
  @detail
 
  @param[in] state:  the state of power rail needs to be updated to.
  @return
   none
 */
/*=========================================================================*/
sns_err_code_e sns_smgr_pm_vote_powerrail(sns_pm_pwr_rail_e state)
{
  sns_pm_err_code_e pm_result;
 
  pm_result = sns_pm_vote_power_rail(smgr_pm_stats.pm_client_handle, state);
 
  SNS_SMGR_PM_IF_DBG2(HIGH, "vote_powerrail - state=%u result=%u", state, pm_result);
 
  return (pm_result == SNS_PM_SUCCESS) ? SNS_SUCCESS : SNS_ERR_FAILED;
}

