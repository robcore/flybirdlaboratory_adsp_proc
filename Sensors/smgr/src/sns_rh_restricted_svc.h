#ifndef SNS_RH_RESTRICTED_SVC_H
#define SNS_RH_RESTRICTED_SVC_H

/*============================================================================

  @file sns_rh_restricted_svc.h

  @brief
  This file contains definition for the Restricted service support in
  the Request Handler

 Copyright (c) 2014 Qualcomm Technologies, Inc.  All Rights Reserved.
 Qualcomm Technologies Proprietary and Confidential.

============================================================================*/
/* $Header: //components/rel/ssc.adsp/2.6.1/smgr/src/sns_rh_restricted_svc.h#1 $ */
/* $DateTime: 2014/12/01 08:57:58 $ */
/* $Author: pwbldsvc $ */

/*============================================================================
  EDIT HISTORY FOR FILE

  when        who  what, where, why
  ----------  ---  -----------------------------------------------------------
  2014-04-23  pn    Initial version
============================================================================*/
#include "sns_rh.h"

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
extern sns_err_code_e sns_rh_process_restricted_smgr_request(
  sns_rh_mr_req_q_item_s**  msg_ptr_ptr);

extern void sns_rh_process_restricted_smgr_response(
  sns_smgr_request_response_s* req_resp_ptr);

extern void sns_rh_cancel_restricted_service(void* connection_handle);

#endif /* SNS_RH_RESTRICTED_SVC_H */

