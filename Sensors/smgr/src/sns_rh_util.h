#ifndef SNS_RH_UTIL_H
#define SNS_RH_UTIL_H

/*============================================================================

  @file sns_rh_util.h

  @brief
  This file contains definition for Request Handler

 Copyright (c) 2014 Qualcomm Technologies, Inc.  All Rights Reserved.
 Qualcomm Technologies Proprietary and Confidential.

============================================================================*/
/* $Header: //components/rel/ssc.adsp/2.6.1/smgr/src/sns_rh_util.h#1 $ */
/* $DateTime: */
/* $Author: pwbldsvc $ */

/*============================================================================
  EDIT HISTORY FOR FILE

  when        who  what, where, why
  ----------  ---  -----------------------------------------------------------
  2014-09-08  pn   Maintains external report rate
  2014-04-23  pn   Initial version
============================================================================*/
#include "sns_common.h"
#include "sns_smgr.h"

/*===========================================================================

                   SMGR MACRO

===========================================================================*/


/*===========================================================================

                   EXTERNAL DEFINITIONS AND TYPES

===========================================================================*/


/*===========================================================================

                          INLINE FUNCTIONS

===========================================================================*/

/*===========================================================================

                          FUNCTIONS

===========================================================================*/
extern q16_t sns_rh_get_max_report_rate_for_ddf_sensor(
  sns_smgr_ddf_sensor_s*  ddf_sensor_ptr);

extern q16_t sns_rh_get_max_report_rate_for_sensor(
  const sns_smgr_sensor_s*      sensor_ptr);

extern void sns_rh_put_next_response(
  sns_smgr_request_response_s*  resp_ptr);

extern sns_smgr_request_response_s* sns_rh_get_next_response(void);

extern void sns_rh_put_next_indication(
  sns_smgr_indication_s*    ind_ptr);

extern sns_smgr_indication_s* sns_rh_get_next_indication(void);

extern int sns_rh_get_report_count(void);

extern void sns_rh_signal_me(uint32_t sig);

#endif /* SNS_RH_UTIL_H */

