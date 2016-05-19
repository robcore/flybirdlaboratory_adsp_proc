#ifndef SNS_SMGR_MR_H
#define SNS_SMGR_MR_H
/*=============================================================================
  @file sns_smgr_mr.h

  This header file contains the data definitions used within the DSPS
  Sensor Manager (SMGR) Message Router

******************************************************************************
* Copyright (c) 2014 Qualcomm Technologies, Inc.  All Rights Reserved.
* Qualcomm Technologies Proprietary and Confidential.
******************************************************************************/

/* $Header: //components/rel/ssc.adsp/2.6.1/smgr/src/sns_smgr_mr.h#1 $ */
/* $DateTime: 2014/12/01 08:57:58 $ */
/* $Author: pwbldsvc $ */

/*============================================================================
  EDIT HISTORY FOR FILE

  when        who  what, where, why
  ----------  ---  -----------------------------------------------------------
  2014-04-23  pn   Initial version

============================================================================*/

/*----------------------------------------------------------------------------
 * Include Files
 * -------------------------------------------------------------------------*/
#include "sns_smgr.h"
#include "sns_smgr_priv.h"
#include "sns_osa.h"
#include "sns_queue.h"

/*----------------------------------------------------------------------------
 * Preprocessor Definitions and Constants
 * -------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
 * Structure Definitions
 * -------------------------------------------------------------------------*/
typedef struct
{
  uint32_t       timestamp;   /* timestamp when message is received */
  uint16_t       body_len;
  uint16_t       msg_id;      /* depending on the service */
  uint8_t        msg_type;    /* req, resp, or ind */
  uint8_t        svc_num;     /* SNS_xxxx_SVC_ID_V01 in sns_common_v01.h */
} sns_smgr_mr_header_s;

typedef struct
{
  sns_q_link_s          q_link;
  sns_smgr_mr_header_s  header;
  void*                 body_ptr;
} sns_smgr_mr_msg_s;

/*----------------------------------------------------------------------------
 * Function Declarations and Documentation
 * -------------------------------------------------------------------------*/
extern void sns_smgr_mr_init(
  OS_FLAG_GRP*                  sig_flags_ptr);

extern sns_smgr_mr_msg_s* sns_smgr_mr_get_msg(void);

sns_err_code_e sns_smgr_mr_send_req(
  const sns_smgr_mr_header_s* msg_header_ptr, 
  void*                       req_ptr,
  void*                       resp_ptr,
  uint16_t                    resp_len,
  void*                       resp_cb_data_ptr);

#endif /* #ifndef SNS_SMGR_MR_H */

