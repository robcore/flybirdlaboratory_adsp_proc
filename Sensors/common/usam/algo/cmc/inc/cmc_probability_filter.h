#ifndef CMC_PROBABILITY_FILTER_H
#define CMC_PROBABILITY_FILTER_H
/*=============================================================================
 Qualcomm Motion Classifier (CMC) probability filtering block

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
 * 2014-05-15  abhinand   Initial version
 *
 *============================================================================*/

#include "cmc.h"

void cmc_filter_combined_probabilities(cmc_state_s *cmc_state);

#endif // CMC_PROBABILITY_FILTER_H
