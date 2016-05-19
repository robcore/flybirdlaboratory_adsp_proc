#ifndef CMC_GMM_PROBABILITY_COMPUTATION_H
#define CMC_GMM_PROBABILITY_COMPUTATION_H

/*=============================================================================
 Qualcomm Motion Classifier (CMC) GMM probability computation block header

 Copyright (c) 2014 Qualcomm Technologies, Inc. All Rights Reserved.
 Qualcomm Technologies Proprietary and Confidential.
 =============================================================================*/

/*============================================================================
 * EDIT HISTORY
 *
 * This section contains comments describing changes made to the module.
 * Notice that changes are listed in reverse chronological order.
 *
 * when        who  what, where, why
 * ----------  ---  -----------------------------------------------------------
 * 2014-09-05  jayarama   initial version
 *
 *============================================================================*/

#include "cmc.h"

/**----------------------------------------------------------------------------
 * Function Prototypes
 * --------------------------------------------------------------------------*/

/*============================================================================

 FUNCTION:   cmc_compute_gmm_feature_likelihood

 ============================================================================*/
/*!
 @brief Compute the feature likelihoods for the GMM features.

* --------------------------------------------------------------------------*/

void gmm_compute_feature_likelihood(cmc_state_s* cmc_state);

/*============================================================================

 FUNCTION:   cmc_compute_gmm_unfiltered_probability

 ============================================================================*/
/*!
 @brief Compute the un-filtered probabilities for the motion states using the GMM
 likelihoods.

* --------------------------------------------------------------------------*/

void gmm_compute_unfiltered_probability(cmc_state_s* cmc_state);

#endif //CMC_GMM_PROBABILITY_COMPUTATION_H
