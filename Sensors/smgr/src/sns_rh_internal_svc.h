#ifndef SNS_RH_INTERNAL_SVC_H
#define SNS_RH_INTERNAL_SVC_H

/*============================================================================

  @file sns_rh_internal_svc.h

  @brief
  This file contains definition for the service provided by SMGR to internal clients.

 Copyright (c) 2014 Qualcomm Technologies, Inc.  All Rights Reserved.
 Qualcomm Technologies Proprietary and Confidential.

============================================================================*/
/* $Header: //components/rel/ssc.adsp/2.6.1/smgr/src/sns_rh_internal_svc.h#2 $ */
/* $DateTime: 2014/12/19 12:27:50 $*/
/* $Author: pwbldsvc $ */

/*============================================================================
  EDIT HISTORY FOR FILE

  when        who  what, where, why
  ----------  ---  -----------------------------------------------------------
  2014-12-19  pn   Renamed sns_rh_enable_sensor_event() to sns_rh_update_sensor_event()
  2014-11-04  pn   sns_rh_enable_sensor_event() takes DDF sensor as input
  2014-07-21  pn   Changed signature of enable_sensor_event()
  2014-05-07  pn   Added support for MD deregistration
  2014-04-23  pn   Initial version
============================================================================*/
#include "sns_rh.h"
#include "sns_smgr.h"

/*===========================================================================

                   SMGR MACRO

===========================================================================*/

/*===========================================================================

                   EXTERNAL DEFINITIONS AND TYPES

===========================================================================*/

/*===========================================================================

                   STRUCTURE DEFINITIONS

===========================================================================*/

/*===========================================================================

                          FUNCTIONS

===========================================================================*/
extern void sns_rh_internal_svc_init(void);

extern sns_err_code_e sns_rh_process_internal_smgr_request(
  sns_rh_mr_req_q_item_s**  msg_ptr_ptr);

extern void sns_rh_cancel_internal_service(const void*);

extern void sns_rh_process_md_int_enabled_sig(void);

extern void sns_rh_process_md_int_disabled_sig(void);

extern void sns_rh_process_md_int_sig(void);

extern void sns_rh_update_sensor_event(
  sns_smgr_ddf_sensor_s*  ddf_sensor_ptr);

extern void sns_rh_generate_sensor_status_ind(
  sns_smgr_ddf_sensor_s*  ddf_sensor_ptr,
  sns_rh_mr_req_q_item_s* msg_ptr);

#endif /* SNS_RH_INTERNAL_SVC_H */

