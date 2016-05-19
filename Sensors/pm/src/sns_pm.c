/*============================================================================

  @file sns_pm.c

  @brief
  This file contains the implementation of the Sensors Power Manager

  Copyright (c) 2015 Qualcomm Technologies, Inc.  All Rights Reserved.
  Qualcomm Technologies Proprietary and Confidential.

============================================================================*/

/*============================================================================

                        EDIT HISTORY FOR MODULE

This section contains comments describing changes made to the module.
Notice that changes are listed in reverse chronological order.

$Header: //components/rel/ssc.adsp/2.6.1/pm/src/sns_pm.c#5 $


when         who     what, where, why
----------   ---     ---------------------------------------------------------
03-20-2015   jhh     Fix corner case for aggregating mips requirement
02-26-2015   vy      Add signaling to debug thread while changing image mode
01-28-2015   agk     Release MIPS and BW vote if NO_CLIENT
11-19-2014   jhh     Keep minimum DDR BW for sensors
11-11-2014   jhh     Reduce only DDR AB upon entering uImage
10-10-2014   agk     Release/Restore DDR BW when entering/exiting uImage
10-06-2014   jhh     Add QDSS events for img mode change and spare 
09-16-2014   jhh     Enable xo in micro image. Make sure NPA calls to be serialized
09-10-2014   jhh     Add MACRO for excluding power feature
09-06-2014   sc      Comment out resume_tmr_obj to quickly fix a crash
09-03-2014   jhh     Clean up client_init 
08-26-2014   jhh     Added hysteresis timer for entering micro image 
08-24-2014   jhh     Add client_name parameter to client_init  
08-22-2014   jhh     Split functions for big image 
08-19-2014   jhh     Fix no_client logic not to prevent micro image
08-15-2014   asj     Ensuring that exit to bigImage always works.
07-28-2014   jhh     Support new log packet for micro image
07-27-2014   vy      Enabled uImage voting
06-25-2014   jhh     Update the current image state when it actually changes
06-20-2014   ps      Disable uimage entry/exit
06-12-2014   vy      Updated for island mode
05-28-2014   jhh     Add micro image featurization
05-24-2014   jhh     Use micro malloc and timer. Add debug message
05-08-2014   jhh     Include sns_pm_init into sensors init sequence
03-03-2014   jhh     Initial Version for 8994

============================================================================*/

/*=====================================================================
                               INCLUDES
=======================================================================*/
#include <stdbool.h>
#include "sns_memmgr.h"
#include "sns_init.h"
#include "sns_common.h"
#include "sns_pm.h"
#include "sns_pm_priv.h"
#include "sns_debug_str.h"

#include "npa.h"
#include "npa_resource.h"
#include "pmapp_npa.h"
#include "mmpm.h"

#include "sns_log_types.h"
#include "sns_log_api.h"
#include "log.h"
#include "log_codes.h"

#include "uSleep.h"
#include "sns_profiling.h"

/*======================================================================
                     INTERNAL DEFINITIONS AND TYPES
========================================================================*/

/* Init variables */
bool sns_pm_mips_initial_vote = true;
bool sns_pm_bw_initial_vote = true;


/* Externs */
extern uint8_t sns_pm_uimg_enabled;
extern bool sns_pm_initialized;
extern sns_pm_internal_s sns_pm;
extern uSleep_notification_cb_handle uSleep_handle;
extern bool sns_pm_uimg_enter_hysteresis_started;

/*======================================================================
                            GLOBAL VARIABLES
========================================================================*/

/*======================================================================
                               FUNCTIONS
========================================================================*/

#ifndef SNS_PM_EXCLUDE_POWER
/*===========================================================================

FUNCTION sns_pm_client_init

DESCRIPTION
  This function returns a handle to the clients. Clients shall use this
  handle in all subsequent PM operations. Cb function is expected to be
  provided if client want to get notification when apps suspend or awake.

===========================================================================*/
sns_pm_err_code_e sns_pm_client_init( sns_pm_handle_t *client_handle,
                                          suspend_cb_t callback,
                                          char *client_name)
{
  uint8_t os_err;
  int i = 0;

  /* Limit the number of clients */
  /* TODO : do we allow client init in uimage? (it doesn't use uMemMgr */
  if(sns_pm.status.num_clients >= NUM_MAX_PM_CLIENTS || sns_pm_initialized == false)
  {
    //PM_MSG_0(MED, "Client Init : SNS_PM is not ready / reached max num client");
    return SNS_PM_ERR_NOT_ALLOWED;
  }

  sns_os_mutex_pend(sns_pm.pm_mutex_ptr, 0, &os_err);

  /* Initialize client handle */
  sns_pm_client_info_s *pm_client_handle;
  pm_client_handle = SNS_OS_U_MALLOC(SNS_DBG_MOD_DSPS_PWR, sizeof(sns_pm_client_info_s));
  if(pm_client_handle == NULL)
  {
    sns_os_mutex_post(sns_pm.pm_mutex_ptr);
    return SNS_PM_ERR_NO_MEM;
  }

  // limit client_name to NUM_MAX_CLIENT_NAME_LENGTH
  for(i = 0; client_name[i] != '\0' && (i < NUM_MAX_CLIENT_NAME_LENGTH); i++)
  {
    pm_client_handle->client_name[i] = client_name[i];
  }
  pm_client_handle->mips = 0;
  pm_client_handle->bw = 0;
  pm_client_handle->max_tolerable_delay = MAX_TOLERABLE_LATENCY;
  pm_client_handle->current_vote = SNS_IMG_MODE_UNKNOWN;
  pm_client_handle->callback = callback;

  /* Store client handle next to the last element exist in array */
  sns_pm.status.client_handle[sns_pm.status.num_clients] = pm_client_handle;
  sns_pm.status.num_clients++;

  *client_handle = pm_client_handle;

  //PM_MSG_1(LOW, "Client Init : num client[%d]", sns_pm.status.num_clients);

  sns_os_mutex_post(sns_pm.pm_mutex_ptr);

  return SNS_PM_SUCCESS;
}

/*===========================================================================

FUNCTION sns_pm_client_close

DESCRIPTION
  This function deregisters the associated client.

===========================================================================*/
void sns_pm_client_close( sns_pm_handle_t client_handle )
{
  /* TODO : do we allow client_close in uimage? */
  uint8_t os_err;
  sns_os_mutex_pend(sns_pm.pm_mutex_ptr, 0, &os_err);

  int i;

  /* Remove the client */
  for(i = 0; i < NUM_MAX_PM_CLIENTS; i++)
  {
    if(sns_pm.status.client_handle[i] == client_handle)
    {
      /* Bring the last element to current position */
      sns_pm.status.client_handle[i] = sns_pm.status.client_handle[sns_pm.status.num_clients];
      sns_pm.status.client_handle[sns_pm.status.num_clients] = NULL;
      sns_pm.status.num_clients--;
      break;
    }
  }

  SNS_OS_U_FREE(client_handle);

  //PM_MSG_1(LOW, "Client Close : num client[%d]", sns_pm.status.num_clients);

  sns_os_mutex_post(sns_pm.pm_mutex_ptr);
}

/*===========================================================================

FUNCTION sns_pm_vote_power_rail

DESCRIPTION
  This function votes for power rail to be turned ON/OFF.

===========================================================================*/
sns_pm_err_code_e sns_pm_vote_power_rail( sns_pm_handle_t client_handle,
                                          sns_pm_pwr_rail_e state )
{

  /* Not allowed in Micro Image Mode */
  if(sns_pm.status.current_mode == SNS_IMG_MODE_MICRO)
  {
    //PM_MSG_0(MED, "Vote Power Rail : not allowed in Micro Image");
    return SNS_PM_ERR_NOT_ALLOWED;
  }
  else
  {
    //PM_MSG_1(LOW, "Vote Power Rail : voted for [%d]", state);
    /* Always turn on LOD before LVS
       Always turn off LVS before LDO */
    if(state == SNS_PWR_RAIL_OFF)
    {
      npa_issue_required_request (sns_pm.core_handle.pmic_client_lvs, PMIC_NPA_MODE_ID_SENSOR_POWER_OFF);
      npa_issue_required_request (sns_pm.core_handle.pmic_client_ldo, PMIC_NPA_MODE_ID_SENSOR_POWER_OFF);
    }
    else if(state == SNS_PWR_RAIL_ON_LPM)
    {
      npa_issue_required_request (sns_pm.core_handle.pmic_client_ldo, PMIC_NPA_MODE_ID_SENSOR_LPM);
      npa_issue_required_request (sns_pm.core_handle.pmic_client_lvs, PMIC_NPA_MODE_ID_SENSOR_LPM);
    }
    else if(state == SNS_PWR_RAIL_ON_NPM)
    {
      npa_issue_required_request (sns_pm.core_handle.pmic_client_ldo, PMIC_NPA_MODE_ID_SENSOR_POWER_ON);
      npa_issue_required_request (sns_pm.core_handle.pmic_client_lvs, PMIC_NPA_MODE_ID_SENSOR_POWER_ON);
    }
    else
    {
      return SNS_PM_ERR_INVALID_PARAM;
    }

    return SNS_PM_SUCCESS;
  }
}

/*===========================================================================

FUNCTION sns_pm_vote_mips

DESCRIPTION
  This function sets the clocks on Q6 for sensors based on client
  MIPS. MIPS from all clients will be aggregated and it will scale to the
  appropriate value to meet SVS2 / SVS / NOMINAL / TURBO clks.

===========================================================================*/
sns_pm_err_code_e sns_pm_vote_mips( sns_pm_handle_t client_handle,
                                    uint32 mips)
{

  /* Not allowed in Micro Image Mode */
  if(sns_pm.status.current_mode == SNS_IMG_MODE_MICRO)
  {
    //PM_MSG_0(MED, "Vote MIPs : not allowed in Micro Image");
    return SNS_PM_ERR_NOT_ALLOWED;
  }
  else
  {
    uint8_t os_err;
    sns_os_mutex_pend(sns_pm.pm_mutex_ptr, 0, &os_err);

    sns_pm_client_info_s *client_info = (sns_pm_client_info_s *)client_handle;

    /* Due to initial clk required for init, if it's the very fist vote from client,
       directly assign it to total mips to remove initial value offset */
    if(sns_pm_mips_initial_vote == true)
    {
      sns_pm.status.total_mips = mips;
      sns_pm_mips_initial_vote = false;
    }
    else
    {
      /* Only need to update the difference of the requested client */
      sns_pm.status.total_mips += mips;
      sns_pm.status.total_mips -= client_info->mips;
    }

    /* Update the client info */
    client_info->mips = mips;


    /* Send vote to ADSP PM */
    sns_pm_internal_vote_mips(sns_pm.status.total_mips);

    sns_os_mutex_post(sns_pm.pm_mutex_ptr);
        
    return SNS_PM_SUCCESS;
  }
}

/*===========================================================================

FUNCTION sns_pm_internal_vote_mips

DESCRIPTION
This function forwards MIPS request for sensors based on client
MIPS. MIPS from all clients will be aggregated and it will be forwarded to 
ADSP PM which sets the clocks appropriately.

===========================================================================*/
void sns_pm_internal_vote_mips(uint32_t mips)
{
    MMPM_STATUS req_result = MMPM_STATUS_SUCCESS;
    MmpmRscExtParamType req_rsc_param;
    MMPM_STATUS result_status[1];
    MmpmRscParamType req_param[1];
    MmpmMipsReqType mips_param;


    mips_param.mipsTotal = mips;
    /* unit is in Million cycles per sec */
    /* TODO : 4 HW Thread... */
    mips_param.mipsPerThread = mips / 3;
    mips_param.codeLocation = MMPM_BW_PORT_ID_ADSP_MASTER;
    mips_param.reqOperation = MMPM_MIPS_REQUEST_CPU_CLOCK_ONLY;

    req_param[0].rscId = MMPM_RSC_ID_MIPS_EXT;
    req_param[0].rscParam.pMipsExt = &mips_param;

    /* SYNC type of request requires all clients to take care of stacks during request
    Use ASYNC type of request to reduce risk of stack overflow */
    req_rsc_param.apiType = MMPM_API_TYPE_ASYNC;
    req_rsc_param.numOfReq = 1;
    req_rsc_param.reqTag = SNS_CORE_Q6;
    req_rsc_param.pStsArray = result_status;
    req_rsc_param.pReqArray = req_param;

    req_result = MMPM_Request_Ext(sns_pm.core_handle.adsppm_ddr_client_id, &req_rsc_param);

    if (MMPM_STATUS_SUCCESS != req_result)
    {
        PM_MSG_1(MED, "MIPS voting failed %d", result_status);
    }
}
/*===========================================================================

FUNCTION sns_pm_vote_bw

DESCRIPTION
  This function aggregates BW for clients and forwards the aggregated
  request to clock and bus drivers through ADSP PM.

===========================================================================*/
sns_pm_err_code_e sns_pm_vote_bw( sns_pm_handle_t client_handle,
                                  uint32 bw,
                                  sns_pm_core_e core)
{

  /* Not allowed in Micro Image Mode */
  if(sns_pm.status.current_mode == SNS_IMG_MODE_MICRO)
  {
    //PM_MSG_0(MED, "Vote BW : not allowed in Micro Image");
    return SNS_PM_ERR_NOT_ALLOWED;
  }
  else
  {
    uint8_t os_err;
    sns_os_mutex_pend(sns_pm.pm_mutex_ptr, 0, &os_err);

    uint32_t client_id;
    MmpmBwPortIdType port_type;
    uint32_t bw_req = 0;
    sns_pm_client_info_s *client_info = (sns_pm_client_info_s *)client_handle;

    /* Client is expected to take care of PNOC clk controls */
    if(core == SNS_PNOC_BUS_I2C || core == SNS_PNOC_BUS_SPI)
    {
      //PM_MSG_0(MED, "Vote BW : I2C/SPI vote is not supported");
      sns_os_mutex_post(sns_pm.pm_mutex_ptr);
      return SNS_PM_ERR_NOT_ALLOWED;
    }
    else if(core == SNS_CORE_DDR)
    {
      client_id = sns_pm.core_handle.adsppm_ddr_client_id;
      port_type = MMPM_BW_PORT_ID_DDR_SLAVE;

      /* Due to initial clk required for init, if it's the very fist vote from client,
         directly assign it to total bw to remove initial value offset */
      if(sns_pm_bw_initial_vote == true)
      {
        sns_pm.status.total_bw = bw;
        sns_pm_bw_initial_vote = false;
      }
      else
      {
        /* Only need to update the difference of the requested client */
        sns_pm.status.total_bw += bw;

        if(sns_pm.status.total_bw >= client_info->bw)
        {
          sns_pm.status.total_bw -= client_info->bw;
        }
        else
        {
          sns_os_mutex_post(sns_pm.pm_mutex_ptr);
          return SNS_PM_ERR_FAILED;
        }
      }

      /* Update client info */
      client_info->bw = bw;

      bw_req = sns_pm.status.total_bw;

      //PM_MSG_3(HIGH, "Vote BW : client[%d] voted bw[%d], total bw[%d] for DDR", client_info, bw, bw_req);
    }
    else if(core == SNS_CORE_SRAM)
    {
      /* SRAM requirement will be applied directly */
      client_id = sns_pm.core_handle.adsppm_sram_client_id;
      port_type = MMPM_BW_PORT_ID_SRAM_SLAVE;
      bw_req = bw;
      PM_MSG_1(LOW, "Vote BW : voted bw[%d] for SRAM", bw_req);
    }
    else
    {
      sns_os_mutex_post(sns_pm.pm_mutex_ptr);
      return SNS_PM_ERR_NOT_SUPPORTED;
    }

    MMPM_STATUS req_result = MMPM_STATUS_SUCCESS;
    MmpmRscExtParamType req_rsc_param;
    MMPM_STATUS result_status[1];
    MmpmRscParamType req_param[1];
    MmpmGenBwValType bw_value[1];
    MmpmBwReqType bw_param;

    /* check with ADSPPM team if they still keep the floor vote for sensors */
    bw_value[0].bwValue.busBwValue.bwBytePerSec = bw_req + sns_pm.status.min_bw;
    bw_value[0].bwValue.busBwValue.usagePercentage = 100;
    bw_value[0].bwValue.busBwValue.usageType = MMPM_BW_USAGE_LPASS_DSP;
    bw_value[0].busRoute.masterPort = MMPM_BW_PORT_ID_ADSP_MASTER;
    bw_value[0].busRoute.slavePort = port_type;
    bw_param.numOfBw = 1;
    bw_param.pBandWidthArray = (MmpmBwValType *) bw_value;

    req_param[0].rscId = MMPM_RSC_ID_GENERIC_BW;
    req_param[0].rscParam.pBwReq = &bw_param;

    /* SYNC type of request requires all clients to take care of stacks during request
       Use ASYNC type of request to reduce risk of stack overflow */
    req_rsc_param.apiType = MMPM_API_TYPE_ASYNC;
    req_rsc_param.numOfReq = 1;
    req_rsc_param.reqTag = core;
    req_rsc_param.pStsArray = result_status;
    req_rsc_param.pReqArray = req_param;

    req_result = MMPM_Request_Ext(client_id, &req_rsc_param);

    sns_os_mutex_post(sns_pm.pm_mutex_ptr);

    if(MMPM_STATUS_SUCCESS != req_result)
    {
      return SNS_PM_ERR_INVALID_PARAM;
    }

    return SNS_PM_SUCCESS;
  }
}

/*===========================================================================

FUNCTION sns_pm_internal_vote_ddr_bw

DESCRIPTION
  This function is used by PM only to release and restore DDR BW while entering and exiting uImage respectively.
  This API is not exposed to clients. 

===========================================================================*/
void sns_pm_internal_vote_ddr_bw ( uint32_t bw , int percentage )
{
  MMPM_STATUS req_result = MMPM_STATUS_SUCCESS;
  MmpmRscExtParamType req_rsc_param;
  MMPM_STATUS result_status[1];
  MmpmRscParamType req_param[1];
  MmpmGenBwValType bw_value[1];
  MmpmBwReqType bw_param;
  uint32_t client_id;
    
  bw_value[0].bwValue.busBwValue.bwBytePerSec = bw + sns_pm.status.min_bw;
  bw_value[0].bwValue.busBwValue.usagePercentage = percentage;
  bw_value[0].bwValue.busBwValue.usageType = MMPM_BW_USAGE_LPASS_DSP;
  bw_value[0].busRoute.masterPort = MMPM_BW_PORT_ID_ADSP_MASTER;
  bw_value[0].busRoute.slavePort = MMPM_BW_PORT_ID_DDR_SLAVE;

  /* ADSP PM shall ignore these values if BW is 0. 
   * Retaining it for the sake of simplicity and completeness
   */

  bw_param.numOfBw = 1;
  bw_param.pBandWidthArray = (MmpmBwValType *) bw_value;
    
  req_param[0].rscId = MMPM_RSC_ID_GENERIC_BW;
  req_param[0].rscParam.pBwReq = &bw_param;
    
  /* SYNC type of request requires all clients to take care of stacks during request
     Use ASYNC type of request to reduce risk of stack overflow */
  req_rsc_param.apiType = MMPM_API_TYPE_SYNC;
  req_rsc_param.numOfReq = 1;
  req_rsc_param.reqTag = SNS_CORE_DDR;
  req_rsc_param.pStsArray = result_status;
  req_rsc_param.pReqArray = req_param;
    
  client_id = sns_pm.core_handle.adsppm_ddr_client_id;
    
  PM_MSG_1(MED, "Voting DDR BW bytesperSec %d", bw);

  req_result = MMPM_Request_Ext(client_id, &req_rsc_param);
    
  if(MMPM_STATUS_SUCCESS != req_result)
  {
     PM_MSG_1(MED, "Releasing/Restoring DDR BW vote failed %d", req_result);
  }

}

/*===========================================================================

FUNCTION sns_pm_set_wakeup_interval

DESCRIPTION
  This function provides effective wakeup interval information to sleep
  driver's /core/max_duration node in the appropriate format.This function
  should be thread safe as multiple clients will call the API.
  Effective wakeup interval refers to how often ADSP actually wakes up to
  any operation

===========================================================================*/
/* TODO : keep track of wakeup interval of each client */
sns_pm_err_code_e sns_pm_set_wakeup_interval( sns_pm_handle_t client_handle,
                                              uint32 wakeup_interval )
{

  /* Not allowed in Micro Image Mode */
  if(sns_pm.status.current_mode == SNS_IMG_MODE_MICRO)
  {
    //PM_MSG_0(MED, "Set Wakeup Interval : not allowed in Micro Image");
    return SNS_PM_ERR_NOT_ALLOWED;
  }
  else
  {
    uint8_t os_err;
    sns_os_mutex_pend(sns_pm.pm_mutex_ptr, 0, &os_err);

    //PM_MSG_1(LOW, "Set Wakeup Interval : voted wakeup_interval[%d]", wakeup_interval);
    /* Wakeup rate requirement of 0 is to remove the requirement */
    if ( wakeup_interval == 0 )
    {
      npa_complete_request(sns_pm.core_handle.req_max_duration_client);
    }
    else
    {
      npa_issue_required_request(sns_pm.core_handle.req_max_duration_client, wakeup_interval);
    }

    sns_os_mutex_post(sns_pm.pm_mutex_ptr);

    return SNS_PM_SUCCESS;
  }
}

/*===========================================================================

FUNCTION sns_pm_uSleep_notification_cb

DESCRIPTION
  Callback registered with micro image. This callback is called to indicate
  that the system is about to enter micro image. Transition to micro image
  is yet to occur but is guaranteed to occur.
 
===========================================================================*/
void sns_pm_uSleep_notification_cb(uSleep_state_notification state)
{
  uint8_t os_err;
  uint64_t last_entry_ts = sns_pm.status.last_uimg_entry_ts;
  uint64_t curr_ts = sns_em_get_timestamp();

  if (!sns_pm_uimg_enabled)
  {
    return;
  }

  sns_profiling_log_qdss(SNS_PM_UIMG_CB, 1, state);

  if(state == USLEEP_STATE_ENTER)
  {
    int uSleep_xo_err;
    /* We cannot be here unles we have voted for uImage */
    /* Update the current_mode upon micro image confirmation */
    sns_os_mutex_pend(sns_pm.pm_mutex_ptr, 0, &os_err);
    sns_pm.status.current_mode = SNS_IMG_MODE_MICRO;
    sns_pm.status.last_uimg_entry_ts = curr_ts;
    if (sns_pm.status.first_uimg_entry_ts == 0)
    {
      sns_pm.status.first_uimg_entry_ts = curr_ts;
    }
    sns_os_mutex_post(sns_pm.pm_mutex_ptr);

    /* Allow/disallow xo_shutdown for the very first time based on latency
       Rest of the allow/disallow operation will happen when clients votes
       for latency in MICRO MODE */
    /* TODO : add eff wakeup rate check */
    if(sns_pm.status.max_tolerable_delay > 5000)
    {
      uSleep_xo_err = uSleep_setCXOMode(USLEEP_CXO_SHUTDOWN_ENABLE);
      if(uSleep_xo_err != USLEEP_SUCCESS)
      {
        PM_MSG_1(MED, "XO_ENABLE return err %d", uSleep_xo_err);
      } 
    }
    else
    {
      /* CXO_SHUTDOWN is enabled by default in micro image
         upon first entry, it should be disabled if it's not required */
      uSleep_xo_err = uSleep_setCXOMode(USLEEP_CXO_SHUTDOWN_DISABLE);
      if(uSleep_xo_err != USLEEP_SUCCESS)
      {
        PM_MSG_1(MED, "XO_DISABLE return err %d", uSleep_xo_err);
      } 
    }
  }
 
  if(state == USLEEP_STATE_EXIT)
  {
    if (last_entry_ts != 0)
    {
      sns_pm.status.time_spent_in_uimg += curr_ts - last_entry_ts;
    }

    /* Other system events cann pull us out of uImage */
    if (sns_pm.status.current_vote == SNS_IMG_MODE_MICRO)
  {
      /* stop accumulating uImage time */
      sns_pm.status.last_uimg_entry_ts = 0;
      sns_pm.status.num_exits_from_uimg++;
    }
  }
}

/*===========================================================================

FUNCTION sns_pm_uimg_enter_timer_cb

DESCRIPTION
  Callback that gets called after micro image enter hysteresis time expired
  This cb will eventually vote for micro image.

===========================================================================*/
void sns_pm_uimg_enter_timer_cb(void *arg)
{
  uint8_t os_err;
  sns_os_mutex_pend(sns_pm.pm_mutex_ptr, 0, &os_err);
  if(sns_pm_uimg_enter_hysteresis_started == true)
  {
    //PM_MSG_0(MED, "timer expired : vote for uimg");
    sns_profiling_log_qdss(SNS_PM_VOTE_IMG_MODE, 1, SNS_IMG_MODE_MICRO);
    sns_pm.status.last_uimg_vote_ts = sns_em_get_timestamp();
    
#ifdef UIMG_LOG
    /* Un-signal debug task as we are entering uImage */
    sns_debug_unsignal_me(SNS_DEBUG_LOGPKT_COMMIT_SIG);
#endif /* UIMG_LOG */

    npa_issue_required_request(sns_pm.core_handle.req_usleep_client, 1);
    sns_pm_uimg_enter_hysteresis_started = false;

    /* Release DDR BW before entering uImage */
    sns_pm_internal_vote_ddr_bw(sns_pm.status.total_bw, 0);
  }
  sns_os_mutex_post(sns_pm.pm_mutex_ptr);
}

/*===========================================================================

FUNCTION sns_pm_adsppm_cb

DESCRIPTION
  Callback registerd with ADSPPM. This callback is called when ADSPPM reqeust
  has been processed. Sensors uses ADSPPM to request for MIPS and BW.

===========================================================================*/
uint32 sns_pm_adsppm_cb(MmpmCallbackParamType *pCbParam)
{
  MmpmCompletionCallbackDataType *p_cb_data;

  p_cb_data = (MmpmCompletionCallbackDataType *) pCbParam->callbackData;

  if(p_cb_data->result == MMPM_STATUS_SUCCESS)
  {
    /* TODO : print out tag ID */
    PM_MSG_1(LOW, "ADSPPM CB : vote success on tag id[%d]", p_cb_data->reqTag);
  }
  else
  {
    /* TODO : CB failed, print out the reason */
  }

  return 0;
}

/*===========================================================================

FUNCTION sns_pm_smsm_init

DESCRIPTION
  Initialize timer and callback for smsm. This module forwards the Apps
  Process suspend info.

===========================================================================*/
static void sns_pm_smsm_init(void)
{
  sns_em_create_utimer_obj( &sns_pm_resume_timer_cb, NULL, SNS_EM_TIMER_TYPE_ONESHOT, &resume_tmr_obj );
  smsm_cb_register( SMSM_APPS_STATE, SMSM_PROC_AWAKE, sns_pm_smsm_cb, NULL);
}

/*===========================================================================

FUNCTION sns_pm_adsppm_init

DESCRIPTION
  Initialize ADSPPM clients. core_id_type is the master block that BW and MIPS
  are requested for. clinet_name

===========================================================================*/
static uint32 sns_pm_adsppm_init(MmpmCoreIdType core_id_type, char *client_name)
{
  MmpmRegParamType mmpmRegParam;
  mmpmRegParam.rev = MMPM_REVISION;
  mmpmRegParam.coreId = core_id_type;
  mmpmRegParam.instanceId = MMPM_CORE_INSTANCE_0;
  mmpmRegParam.MMPM_Callback = sns_pm_adsppm_cb;
  mmpmRegParam.pClientName = client_name;
  mmpmRegParam.pwrCtrlFlag = PWR_CTRL_PERIODIC_CLIENT;
  mmpmRegParam.callBackFlag = CALLBACK_REQUEST_COMPLETE;
  mmpmRegParam.cbFcnStackSize = 128;
  return MMPM_Register_Ext(&mmpmRegParam);
}

/*===========================================================================

FUNCTION sns_pm_init

DESCRIPTION
  This function initializes pm internal structure and handles needed for
  external power request such as mmpm, npa, and pmic.  This is called in
  boot up init seqeunce.

===========================================================================*/
sns_err_code_e sns_pm_init(void)
{
  if(sns_pm_initialized == false)
  {
    int i;
    uint8_t sns_os_err = 0;

    /* Expected latency of callback execution when entering/exiting
       Micro Image Mode. Exit latency is 0 since no callback.
       Unit is in ticks of 19.2MHz */
    uint32 uimage_enter_latency = 1000;
    uint32 uimage_exit_latency = 0;

    sns_pm_smsm_init();
    sns_em_create_timer_obj( &sns_pm_uimg_enter_timer_cb, NULL, SNS_EM_TIMER_TYPE_ONESHOT, &uimg_enter_tmr_obj );

    /* Initialize sns_pm */
    for(i = 0; i < NUM_MAX_PM_CLIENTS; i++)
    {
      sns_pm.status.client_handle[i] = NULL;
    }

    /* Initialization is expected to happen in Big Image Mode */
    sns_pm.status.current_mode = SNS_IMG_MODE_BIG;
    sns_pm.status.num_clients = 0;
    sns_pm.status.max_tolerable_delay = MAX_TOLERABLE_LATENCY;
    sns_pm.status.total_bw = 6000000;
    sns_pm.status.total_mips = 60;
    sns_pm.status.client_vote_status = 0;
    sns_pm.status.min_bw = 20;

    /* Mutex */
    sns_pm.pm_suspend_resume_mutex_ptr = sns_os_mutex_create_uimg(SNS_PM_QUE_MUTEX, &sns_os_err);
    if(sns_os_err != OS_ERR_NONE)
    {
      return SNS_ERR_FAILED;
    }

    sns_pm.pm_mutex_ptr = sns_os_mutex_create_uimg(SNS_PM_QUE_MUTEX, &sns_os_err);
    if(sns_os_err != OS_ERR_NONE)
    {
      return SNS_ERR_FAILED;
    }

    /* NPA node */
    sns_pm.core_handle.req_max_duration_client   =  npa_create_sync_client(
                 "/sleep/max_duration/usec",
                 "SNS_PM_MaxDuration",
                 NPA_CLIENT_REQUIRED);
    SNS_ASSERT(NULL != sns_pm.core_handle.req_max_duration_client);

    sns_pm.core_handle.req_sync_latency_client  =  npa_create_sync_client(
                 "/core/cpu/latency/usec",
                 "SNS_PM_LatencyNode",
                 NPA_CLIENT_REQUIRED );
    SNS_ASSERT(NULL != sns_pm.core_handle.req_sync_latency_client);

    sns_pm.core_handle.req_usleep_client  =  npa_create_sync_client(
                 "/core/uSleep",
                 "SNS_PM_uSleep",
                 NPA_CLIENT_REQUIRED );
    SNS_ASSERT(NULL != sns_pm.core_handle.req_usleep_client);


    /* PMIC */
    sns_pm.core_handle.pmic_client_lvs = npa_create_sync_client (PMIC_NPA_GROUP_ID_SENSOR_VDDIO, "Sensors", NPA_CLIENT_REQUIRED);
    sns_pm.core_handle.pmic_client_ldo = npa_create_sync_client (PMIC_NPA_GROUP_ID_SENSOR_VDD, "Sensors", NPA_CLIENT_REQUIRED);
    SNS_ASSERT(NULL != sns_pm.core_handle.pmic_client_lvs);
    SNS_ASSERT(NULL != sns_pm.core_handle.pmic_client_ldo);

    /* ADSP PM */
    sns_pm.core_handle.adsppm_ddr_client_id = sns_pm_adsppm_init(MMPM_CORE_ID_LPASS_ADSP, "SENSORS_DDR");
    SNS_ASSERT(0 != sns_pm.core_handle.adsppm_ddr_client_id);
    sns_pm.core_handle.adsppm_sram_client_id = sns_pm_adsppm_init(MMPM_CORE_ID_LPASS_SRAM, "SENSORS_SRAM");
    SNS_ASSERT(0 != sns_pm.core_handle.adsppm_sram_client_id);

    /* Micro Sleep */
    uSleep_handle = uSleep_registerNotificationCallback(uimage_enter_latency, uimage_exit_latency, sns_pm_uSleep_notification_cb);
    SNS_ASSERT(uSleep_handle > 0);

    sns_pm_initialized = true;

    /* sns_pm_init is in the boot up init sequence required to call sns_init_done once init is completed */
    sns_init_done();
  }

  //PM_MSG_0(LOW, "sns_pm_init done");
  return SNS_SUCCESS;
}

sns_err_code_e sns_pm_log_uimg_mode(void)
{
   sns_log_uimg_mode_s* logPtr;

   /* Allocate log packet */
   logPtr = (sns_log_uimg_mode_s *)log_alloc(LOG_SNS_UIMG_MODE_C, sizeof(sns_log_uimg_mode_s));

   if (logPtr != NULL)
   {
      logPtr->version = SNS_LOG_UIMG_MODE_VERSION;

      /* Generate the log packet */
      logPtr->state_vote_status = sns_pm.status.client_vote_status;
      logPtr->state_vote_timestamp = sns_pm.status.state_vote_timestamp;
      logPtr->bigImage_entry_ts    = sns_pm.status.bigImage_entry_ts;
      logPtr->last_uimg_vote_ts    = sns_pm.status.last_uimg_vote_ts;
      logPtr->first_uimg_entry_ts  = sns_pm.status.first_uimg_entry_ts;
      logPtr->time_spent_in_uimg   = sns_pm.status.time_spent_in_uimg;
      logPtr->num_exits_from_uimg  = sns_pm.status.num_exits_from_uimg;

      /* Commit log (also frees up the log packet memory) */
      log_commit(logPtr);
   }

   /* need to revisit this return value */
   return SNS_SUCCESS;
}

/*=======================================================================
 
  FUNCTION : sns_pm_uimg_vote_override
 
========================================================================*/
void sns_pm_set_uimg_vote_override(bool uimg_override)
{
  sns_pm_uimg_enabled = uimg_override ? 0 : 1;
  PM_MSG_2(MED, "Uimg vote override by diag: from_cfg_file(0=enable)=%d, new_uimg_status(0=disable)=%d", 
                  uimg_override, sns_pm_uimg_enabled);
}

#else
sns_err_code_e sns_pm_init(void)
{
  sns_init_done();
  return SNS_SUCCESS;  
}

sns_pm_err_code_e sns_pm_client_init( sns_pm_handle_t *client_handle,
                                      suspend_cb_t callback,
                                      char* client_name)
{
  return SNS_PM_SUCCESS;
}

void sns_pm_client_close( sns_pm_handle_t client_handle )
{
  return;
}

sns_pm_err_code_e sns_pm_vote_power_rail( sns_pm_handle_t client_handle,
                                          sns_pm_pwr_rail_e state )
{
  return SNS_PM_SUCCESS;
}

sns_pm_err_code_e sns_pm_vote_mips( sns_pm_handle_t client_handle,
                                    uint32 mips )
{
  return SNS_PM_SUCCESS;
}

sns_pm_err_code_e sns_pm_vote_bw( sns_pm_handle_t client_handle,
                                  uint32 bw,
                                  sns_pm_core_e core )
{
  return SNS_PM_SUCCESS;
}

sns_pm_err_code_e sns_pm_set_wakeup_interval( sns_pm_handle_t client_handle,
                                              uint32 wakeup_interval )
{
  return SNS_PM_SUCCESS;
}
                                       
void sns_pm_set_uimg_vote_override(bool uimg_override)
{
  return;
}
#endif /* SNS_PM_EXCLUDE_POWER */
