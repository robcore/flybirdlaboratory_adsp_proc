#ifndef SNS_SVC_H
#define SNS_SVC_H
/*============================================================================
  @file sns_svc.h

  @brief
  Contains typedef used to map QMI service numbers to the service objects.

  <br><br>

  Copyright (c) 2011 Qualcomm Technologies Incorporated.
  All Rights Reserved.
  Qualcomm Confidential and Proprietary
  ============================================================================*/

/*============================================================================
  EDIT HISTORY FOR MODULE

  This section contains comments describing changes made to the module.
  Notice that changes are listed in reverse chronological order. Please
  use ISO format for dates.

  $Header: //components/rel/ssc.adsp/2.6.1/common/inc/sns_svc.h#1 $
  $DateTime: 2014/12/01 08:57:58 $

  when       who    what, where, why
  ---------- --- -----------------------------------------------------------
  2011-02-28 jtl Added copyright header.
  ============================================================================*/


/*===========================================================================

                   EXTERNAL DEFINITIONS AND TYPES

===========================================================================*/
typedef struct sns_smr_svc_s
{
  uint32_t               qmi_svc;         /* QMI service number */
  const service_object  *qmi_svc_obj_ptr; /* Pointer to the QMI service object */
} sns_smr_svc_t;

#endif /* SNS_SVC_H*/
