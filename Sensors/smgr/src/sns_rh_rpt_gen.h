#ifndef SNS_RH_RPT_GEN_H
#define SNS_RH_RPT_GEN_H
/*============================================================================

  @file sns_rh_rpt_gen.h

  @brief
  This file contains definitions for the Report Generation functions
  of the Request Handler

 Copyright (c) 2014 Qualcomm Technologies, Inc.  All Rights Reserved.
 Qualcomm Technologies Proprietary and Confidential.

============================================================================*/
/* $Header: //components/rel/ssc.adsp/2.6.1/smgr/src/sns_rh_rpt_gen.h#1 $ */
/* $DateTime: 2014/12/01 08:57:58 $*/
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

                          FUNCTIONS

===========================================================================*/
extern bool sns_rh_rpt_gen_send_query_indication(
  sns_rh_rpt_spec_s* rpt_ptr);

extern bool sns_rh_rpt_gen_send_empty_query_indication(
  const sns_rh_query_s* query_ptr);

extern bool sns_rh_rpt_gen_generate_periodic_report(
  sns_rh_rpt_spec_s* rpt_spec_ptr);

extern bool sns_rh_rpt_gen_send_buffering_indications(
  sns_rh_rpt_spec_s* rpt_spec_ptr);

#endif /* SNS_RH_RPT_GEN_H */

