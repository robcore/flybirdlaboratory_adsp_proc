#ifndef CMC_HYSTERESIS_H
#define CMC_HYSTERESIS_H
/*=============================================================================
 Qualcomm Motion Classifier (CMC) hysteresis block

 Copyright (c) 2014 Qualcomm Technologies, Inc. All Rights Reserved.
 Qualcomm Technologies Proprietary and Confidential.
 =============================================================================*/

/*============================================================================
 * EDIT HISTORY
 *
 * This section contains comments describing changes made to the module.
 * Notice that changes are listed in reverse chronological order.
 *
 * when        who        what, where, why
 * ----------  ---        -----------------------------------------------------
 * 2014-05-20  abhinand   Initial version
 *
 *============================================================================*/

#include "cmc.h"

void cmc_apply_hysteresis_filter(cmc_state_s *cmc_state);

#endif // CMC_HYSTERESIS_H
