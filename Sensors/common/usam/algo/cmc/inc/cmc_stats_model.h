/*=============================================================================
 Qualcomm Motion Classifier (CMC) algorithm model header

 Copyright (c) 2014 Qualcomm Technologies, Inc. All Rights Reserved.
 Qualcomm Technologies Proprietary and Confidential.
============================================================================*/

/*=============================================================================
 * THIS IS AN AUTO-GENERATED FILE. DO NOT ALTER IN ANY WAY.
 * Time at which file was generated: 10-Jun-2014 18:20:46
 *============================================================================*/


#ifndef CMC_STATS_MODEL_H
#define CMC_STATS_MODEL_H

#include <stdint.h>

#define CMC_STATS_MODEL_ID_IQR 0
#define CMC_STATS_MODEL_ID_MODRM 1
#define CMC_STATS_MODEL_ID_MM3 2
#define CMC_STATS_MODEL_ID_DIFFSUM 3
#define CMC_STATS_MODEL_ID_DIFF10P 4
#define CMC_STATS_MODEL_ID_NUM 5
#define CMC_STATS_MODEL_PARAM1_STATES 5
#define CMC_STATS_MODEL_PARAM2_STATES 9
#define LINEAR_ACCEL_TIME_CONSTANT 307
#define LIKELIHOOD_REGULARIZATION_CONSTANT 0.000000
#define STAT_DRIVE_LR_WINDOW_LENGTH 200
#define WALK_BIKE_LR_WINDOW_LENGTH 200

#define CMC_NUM_MOTION_STATES 5
#define CMC_NUM_HYSTERESIS_STATES (CMC_NUM_MOTION_STATES + 1)
#define CMC_NUM_DEVICE_POSITIONS 9

#define CMC_LR_STAT_DRIVE_FEATURE_SIZE 8
#define CMC_LR_STAT_DRIVE_MODEL_SIZE (CMC_LR_STAT_DRIVE_FEATURE_SIZE + 1)

#define CMC_LR_WALK_BIKE_FEATURE_SIZE 21
#define CMC_LR_WALK_BIKE_MODEL_SIZE (CMC_LR_WALK_BIKE_FEATURE_SIZE + 1)

#define CMC_EMISSION_FIX_ROWS 5
#define CMC_EMISSION_FIX_COLUMNS 5

#define DRIVE_ENTRY_WINDOW 6
#define DRIVE_ENTRY_THRESHOLD 0.900000f

#define DRIVE_LOGIC_PROB_THRESHOLD 0.500000f
#define DRIVE_LOGIC_HISTORY_LENGTH 180
#define DRIVE_LOGIC_NUM_HIGH_OUTPUTS_LOWER_BOUND 6
#define DRIVE_LOGIC_NUM_HIGH_OUTPUTS_UPPER_BOUND 50
#define DRIVE_LOGIC_MAX_TIMER_VAL 150

#define BIKE_LOGIC_PROB_THRESHOLD 0.500000f
#define BIKE_LOGIC_HISTORY_LENGTH 150
#define BIKE_LOGIC_NUM_HIGH_OUTPUTS_LOWER_BOUND 6
#define BIKE_LOGIC_NUM_HIGH_OUTPUTS_UPPER_BOUND 85
#define BIKE_LOGIC_MAX_TIMER_VAL 120


extern const float prior_probability[CMC_STATS_MODEL_PARAM1_STATES][CMC_STATS_MODEL_PARAM2_STATES];

extern const float stats_model_iqr_mean[CMC_STATS_MODEL_PARAM1_STATES][CMC_STATS_MODEL_PARAM2_STATES];

extern const float stats_model_iqr_covariance[CMC_STATS_MODEL_PARAM1_STATES][CMC_STATS_MODEL_PARAM2_STATES];

extern const float stats_model_iqr_covariance_divsqrt2pi[CMC_STATS_MODEL_PARAM1_STATES][CMC_STATS_MODEL_PARAM2_STATES];

extern const float stats_model_modrm_mean[CMC_STATS_MODEL_PARAM1_STATES][CMC_STATS_MODEL_PARAM2_STATES];

extern const float stats_model_modrm_covariance[CMC_STATS_MODEL_PARAM1_STATES][CMC_STATS_MODEL_PARAM2_STATES];

extern const float stats_model_modrm_covariance_divsqrt2pi[CMC_STATS_MODEL_PARAM1_STATES][CMC_STATS_MODEL_PARAM2_STATES];

extern const float stats_model_mm3_mean[CMC_STATS_MODEL_PARAM1_STATES][CMC_STATS_MODEL_PARAM2_STATES];

extern const float stats_model_mm3_covariance[CMC_STATS_MODEL_PARAM1_STATES][CMC_STATS_MODEL_PARAM2_STATES];

extern const float stats_model_mm3_covariance_divsqrt2pi[CMC_STATS_MODEL_PARAM1_STATES][CMC_STATS_MODEL_PARAM2_STATES];

extern const float stats_model_diffsum_mean[CMC_STATS_MODEL_PARAM1_STATES][CMC_STATS_MODEL_PARAM2_STATES];

extern const float stats_model_diffsum_covariance[CMC_STATS_MODEL_PARAM1_STATES][CMC_STATS_MODEL_PARAM2_STATES];

extern const float stats_model_diffsum_covariance_divsqrt2pi[CMC_STATS_MODEL_PARAM1_STATES][CMC_STATS_MODEL_PARAM2_STATES];

extern const float stats_model_diff10p_mean[CMC_STATS_MODEL_PARAM1_STATES][CMC_STATS_MODEL_PARAM2_STATES];

extern const float stats_model_diff10p_covariance[CMC_STATS_MODEL_PARAM1_STATES][CMC_STATS_MODEL_PARAM2_STATES];

extern const float stats_model_diff10p_covariance_divsqrt2pi[CMC_STATS_MODEL_PARAM1_STATES][CMC_STATS_MODEL_PARAM2_STATES];

extern const uint16_t gmm_feature_window_lengths[CMC_STATS_MODEL_PARAM1_STATES];

extern const float stat_dr_lr_model_weights[CMC_LR_STAT_DRIVE_MODEL_SIZE];

extern const float walk_bike_lr_model_weights[CMC_LR_WALK_BIKE_MODEL_SIZE];

extern const float emission_fix[CMC_EMISSION_FIX_ROWS][CMC_EMISSION_FIX_COLUMNS];

extern const float initial_filt_probs[CMC_NUM_MOTION_STATES];

extern const float iir_transition_matrix[CMC_EMISSION_FIX_ROWS][CMC_EMISSION_FIX_COLUMNS];

extern const uint8_t use_max_for_components[CMC_NUM_MOTION_STATES][CMC_NUM_DEVICE_POSITIONS];

extern const float unknown_confidence_thresholds[CMC_NUM_MOTION_STATES][CMC_NUM_MOTION_STATES];

extern const float confidence_thresholds_while_in_drive[CMC_NUM_MOTION_STATES];

extern const float confidence_thresholds_while_in_bike[CMC_NUM_MOTION_STATES];

extern const float confidence_thresholds_while_not_in_commute[CMC_NUM_MOTION_STATES];

extern const uint16_t hysteresis_thresholds_while_in_drive[CMC_NUM_HYSTERESIS_STATES][CMC_NUM_HYSTERESIS_STATES];

extern const uint16_t hysteresis_thresholds_while_in_bike[CMC_NUM_HYSTERESIS_STATES][CMC_NUM_HYSTERESIS_STATES];

extern const uint16_t hysteresis_thresholds_while_not_in_commute[CMC_NUM_HYSTERESIS_STATES][CMC_NUM_HYSTERESIS_STATES];

#endif // CMC_STATS_MODEL_H
