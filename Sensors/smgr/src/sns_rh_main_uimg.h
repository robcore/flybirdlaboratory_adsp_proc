#ifndef SNS_RH_MAIN_UIMG_H
#define SNS_RH_MAIN_UIMG_H
/*============================================================================

  @file sns_rh_main_uimg.h

  @brief
  This file contains definitions for the uImage portion of Request Handler

 Copyright (c) 2014-2015 Qualcomm Technologies, Inc.  All Rights Reserved.
 Qualcomm Technologies Proprietary and Confidential.

============================================================================*/
/* $Header: //components/rel/ssc.adsp/2.6.1/smgr/src/sns_rh_main_uimg.h#2 $ */
/* $DateTime: 2015/02/04 16:31:36 $ */
/* $Author: pwbldsvc $ */

/*============================================================================
  EDIT HISTORY FOR FILE

  when        who  what, where, why
  ----------  ---  -----------------------------------------------------------
  2015-01-13  hw   Make sns_rh_prepare_report_for_flushing as an API
  2014-09-08  pn   Maintains external report rate 
  2014-07-21  pn   Added unsignal_me()
  2014-06-16  pn   Unshared sns_rh_uimg
  2014-06-05  vy   Further refactored to support uImage  
  2014-04-29  pn   Initial version
============================================================================*/
#include "sns_osa.h"
#include "sns_queue.h"
#include "sns_rh.h"
#include "sns_smgr_api_v01.h"

/*===========================================================================

                   SMGR MACRO

===========================================================================*/

/*===========================================================================

                   EXTERNAL DEFINITIONS AND TYPES

===========================================================================*/

/*===========================================================================

                          FUNCTIONS

===========================================================================*/
extern OS_FLAG_GRP* sns_rh_init_uimg(void);

extern void sns_rh_task_loop(void);

extern void sns_rh_leave_island(void);

extern void sns_rh_enter_island(void);

extern sns_q_s* sns_rh_get_report_queue(void);

extern sns_smgr_periodic_report_ind_msg_v01* sns_rh_get_periodic_ind_buf(void);

extern sns_smgr_buffering_ind_msg_v01* sns_rh_get_buffering_ind_buf(void);

extern sns_smgr_buffering_query_ind_msg_v01* sns_rh_get_query_ind_buf(void);

extern sns_err_code_e sns_rh_get_latest_sample_timestamp(
  const sns_rh_rpt_item_s* item_ptr,
  sns_ddf_time_t*          ts_ptr);

extern void sns_rh_update_report_timer(void);

extern bool sns_rh_add_to_ready_list(
  sns_rh_rpt_spec_s*  report_ptr);

extern void sns_rh_rpt_gen_remove_from_ready_list(
  sns_rh_rpt_spec_s* report_ptr);

extern bool sns_rh_ok_to_send_report(
  const sns_rh_rpt_spec_s *rpt_ptr);

extern void sns_rh_unsignal_me(uint32_t sig);

#endif /* SNS_RH_MAIN_UIMG_H */

