#ifndef SNS_SSM_SYNC_PROXY_H
#define SNS_SSM_SYNC_PROXY_H
/*=============================================================================
  @file sns_ssm_sync_proxy

  Sensors Service Manager's Sync_Proxy Service header file

  This header file contains the functions required by the Sync_Proxy Service

  Copyright (c) 2014 Qualcomm Technologies, Inc.  All Rights Reserved.
  Qualcomm Technologies Proprietary and Confidential.

=============================================================================*/

/* $Header: //components/rel/ssc.adsp/2.6.1/ssm/framework/inc/sns_ssm_sync_proxy.h#1 $  */
/* $DateSync_Proxy: 2014/09/22 15:13:41 $ */
/* $Author: pwbldsvc $ */

/*=============================================================================
  EDIT HISTORY FOR MODULE

  This section contains comments describing changes made to the module.
  Notice that changes are listed in reverse chronological order. 

  when        who  what, where, why
  ----------  ---  ------------------------------------------------------------
  2014-09-23  jtl   Initial version

=============================================================================*/


/*-----------------------------------------------------------------------------
* Include Files
* ---------------------------------------------------------------------------*/

#include "sns_common.h"
#include "sns_common_v01.h"
#include "sns_sync_proxy_v01.h"
#include "sns_ssm_priv.h"

/*-----------------------------------------------------------------------------
* sns_ssm_sync_proxy_init
* ---------------------------------------------------------------------------*/
sns_err_code_e sns_ssm_sync_proxy_init(void);

/*-----------------------------------------------------------------------------
* sns_ssm_sync_proxy_proc_req
* ---------------------------------------------------------------------------*/
sns_err_code_e sns_ssm_sync_proxy_proc_req
(
 sns_ssm_qmi_connection_s *connection_handle,
 qmi_req_handle req_handle,
 unsigned int msg_id,
 void *req_c_struct
);

/*-----------------------------------------------------------------------------
* sns_ssm_sync_proxy_proc_discon
* ---------------------------------------------------------------------------*/
sns_err_code_e sns_ssm_sync_proxy_proc_discon(void);
#endif /* #ifndef SNS_SSM_SYNC_PROXY_H */
