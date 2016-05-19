#ifndef CMC_LR_PROBABILITY_COMPUTATION_H
#define CMC_LR_PROBABILITY_COMPUTATION_H

/*=============================================================================
 Qualcomm Motion Classifier (CMC) LR probability computation block header

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
 * ----------  ---        -----------------------------------------------------------
 * 2014-05-13  abhinand   initial version
 *
 *============================================================================*/

/**----------------------------------------------------------------------------
 * Function Prototypes
 * --------------------------------------------------------------------------*/

/*============================================================================

 FUNCTION:   cmc_compute_lr_unfiltered_probability

 ============================================================================*/
/*!
 @brief Compute the un-filtered probabilities from a logistic regression
 classifier that separate two motion states.

* --------------------------------------------------------------------------*/

void cmc_compute_lr_unfiltered_probability(const float *lr_features, const float *lr_weights,
        const float lr_bias, int num_features, float *output_probs);

#endif //CMC_LR_PROBABILITY_COMPUTATION_H
